// Акула: Стивен Додсон
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
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, mi a fene!";
				link.l1 = "Steven, volt egy átfedés. Nem tudtam eljönni, és nem tudtalak értesíteni a távollétemrôl...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Örülök, hogy látlak, haver! Miben segíthetek? ";
				link.l1 = "Én is örülök, hogy látlak. Meg akartam köszönni a tökéletesen lebonyolított látványosságot!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Örülök, hogy látlak, haver! Miben segíthetek?";
				link.l1 = "Van egy javaslatom a számodra. Egy kalóz ajánlat, tudod!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Ez a mi ügyfelünk! A munkát elvégeztük, a báród egy jól ôrzött börtönben ül. Talán szeretnéd megnézni, he-he?!";
				link.l1 = "Erre bôven lesz idôm, ha-ha. Jól bánnak vele?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Örülök, hogy látlak, haver! Miben segíthetek?";
				link.l1 = "Azért jöttem újra, hogy a segítségedet kérjem.";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Örülök, hogy látlak, haver! Miben segíthetek?";
				link.l1 = "Steven, van valamim a számodra.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Örülök, hogy látlak, haver! Miben segíthetek?";
				link.l1 = "Steven, kérdeznem kell valamit. Lehet, hogy nem fog tetszeni, de szükségem van a segítségedre.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ha, itt vagy, "+pchar.name+". Már vártam az érkezésedet. Forest Devil mesélt nekem a Tortugával való bajodról...";
				link.l1 = "Azt is mondta, hogy már megtaláltad a megoldást. Ez igaz?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "Hogy állunk, "+pchar.name+"?";
				link.l1 = "Titkok mindenhol... Szükségem van a tanácsodra, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "Igen, szeretnék mutatni neked valamit... Szeretnél velem jönni a mólóhoz?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ah, barátom "+GetFullName(pchar)+"! Gyere be, örülök, hogy látlak! Miért jöttél?";
				link.l1 = "Szia, Steven! Nos, megjelentem, ahogy ígértem. Készen áll a hajód?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "Mi a helyzet a vállalkozásoddal? Nem adta fel ezt a vállalkozást a 'Golden Fleet'?tekintetében.";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ah, barátom "+GetFullName(pchar)+"! Gyere be, örülök, hogy látlak! Miért jöttél?";
			link.l1 = "Igen, üzleti ügyben jártam Isla Tesoro-n, és úgy döntöttem, hogy beugrok egy percre.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha! Gondolom, te vagy az éjszakai látogatónk? Túl késôn értesültem a balesetrôl. Átnéztem a holmidat, és találtam egy levelet Forest Devil-tôl. A pokolba is, majdnem Main dzsungelének szaga volt\nA neve "+GetFullName(pchar)+"? Ne lepôdj meg, a levélbôl olvastam ki. A nevem Steven Dodson. Vagy egyszerûen csak Cápa. A Cápa. Azt hiszem, már hallottál rólam. Jelenleg admirálisi pozíciót töltök be ebben a városban vagy szigeten, mindegy\nBocsánatot kérek az embereim tegnap esti tetteiért. Az én parancsom volt, hogy mindenkit fogjanak el, aki besurran a raktérbe. Túl sok a tolvaj a narwhalok és a rivadók között\nChad elengedett, gondolom? Furcsa. Csak egy parancsot akartam küldeni neki, hogy engedjen el. Hol van a hajód? Remélem, jól van?";
			link.l1 = "Chad? Amennyire én tudom, a hajóskapitányod soha nem engedne el élve a börtönbôl. Én magam tettem meg, és kiszabadítottam egy feketét is ezek közül... Rivadost.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Érdekes dolgokat mesélsz nekem, pajtás. És hogy sikerült kijutnod 'Tartaroszból'? Úgy néz ki, hogy lesz egy kellemes beszélgetésem Chaddal és a börtönôreivel...";
			link.l1 = "Nem fogsz velük beszélgetni. Attól tartok, soha többé nem fognak beszélgetni. Chad megfenyegetett, hogy örökre a ketrecben tart. Azzal vádolt, hogy én vagyok Rivados, és követelte, hogy bizonyítsam be az ellenkezôjét azzal, hogy megölöm a fekete varázslót, Chimiset...";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Mi a fene?! Micsoda ostoba önfejûség! Chimisetre élve van szükségünk, és ezt Chad tökéletesen tudta! És miért feltételezte rólad, hogy Rivados vagy, ha mindannyian feketék? Mire készül, a fene egye meg!";
			link.l1 = "Olyasmire készül, ami biztosan nem fog tetszeni neked, Steven. Chad adott nekem egy machetét, és leküldött, hogy öljem meg Chimiset-et. De az öreg Fekete valami fontosat mondott nekem, és rájöttem, hogy ha megölöm Chimiset-et, én leszek a következô...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Ahelyett, hogy megöltem volna az öreget, kinyitottam egy ládát lôszerrel, és harcoltam Chaddel és a haverjaival. Most már érted, miért nem lehet velük többé beszélni? Mindannyian halottak.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Bassza meg! A hírek egyre rémisztôbbek! És mit csináljak ezzel a sok zûrzavarral?";
			link.l1 = "Figyelj rám, Steve. Chimiset azt mondta, hogy Chadnak volt egy megállapodása néhány narwhallal - ez a másik klán, ha jól értem. Chad azt tervezte, hogy megöl téged és átveszi a helyedet. A narwhalok nagyon szeretnének holtan látni téged, mert biztosak benne, hogy te ölted meg a vezérüket, Allent... vagy Alant, nem emlékszem.";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Lószart! Nem öltem meg Alant! Valaki más tette, talán a narválok. Szerintem a jelenlegi vezetôjük - Donald Greenspen - ölte meg Alant!";
			link.l1 = "Nem. Chad ölte meg. Chimiset szemtanúja volt a bûncselekménynek - ezért akarták ôt is megölni. Chad valamiért nem akarta ezt maga megtenni - úgy tûnik, mintha valamiféle átoktól félt volna. Ezért akarta, hogy én végezzem el a munkát.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "Nem tudom elhinni... Chad ölte meg Alant? De miért?";
			link.l1 = "Hogy rád hagyja a felelôsséget, és hogy ellenséget csináljon belôled a narválokkal. Feltételezem, hogy ô terjesztette a pletykákat, mert miért hibáztatna téged és csak téged a Narwhals? Steven, azt tervezik, hogy megölnek téged. És a Rivados klánt hibáztatnák ezért - bár nem tudom, hogyan fogják ezt megtenni. Chimiset mesélt nekem errôl.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "Emellett ezt a levelet találtam Chad ládájában. Olvasd el. Szilárd bizonyítéknak tûnik, bár közvetett.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(olvasás)... heh! Nem vagyok meglepve Chad árulásán. A rohadék mindig is hatalmat akart ezen a szigeten. De narválok! Komolyan elhinni, hogy én öltem meg Alant! Ez dupla árat fog nekik fizetni az ellátmányért\nAzt terveztem, hogy amúgy is szabadon engedem Chimiset, itt az ideje, hogy békét kössek velük. Megdöbbentettél, haver, hogy ôszinte legyek...";
			link.l1 = "Megértem, Steven. Nekem sem tetszik, hogy valami politikai zûrzavar közepébe keveredtem, mióta a Szigetre érkeztem. Csak azért jöttem ide, hogy téged és Nathaniel Hawkot találjalak...";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Micsoda? Sólyom? Ô nem Jamaikán van? Ô egy báró Maroon városából, miért lenne itt?";
			link.l1 = "Nem. Jackman most ott a parancsnok. Sikerült kiderítenem, hogy Hawk ugyanúgy jutott oda, mint én - Kukulcan portálján keresztül.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "Mi ez az egész ostobaság? Milyen átjáró? És még mindig nem válaszoltál - hol van a hajód?";
			link.l1 = "Nincs hajó. Megértem, Steve, hogy nehéz elhinni, de én tényleg az indián bálványon keresztül jutottam ide a Fôbôl... ne nézz így rám - nem vagyok ôrült! Magam sem értem, hogyan lehetséges ez, de így van!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "";
			link.l1 = "A sámán Miskito faluban látta, ahogy az üldözôk elôl menekülô Nathaniel Hawk odafutott az indián bálványhoz, amelyet Kukulcan szoborként ismernek, és hirtelen eltûnt. Ez a sámán elmondta nekem, hogy ô maga is járt ezen a szigeten, és hogy ugyanezen az úton ment oda a szobron keresztül...";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "";
			link.l1 = "Én Nátánt keresem, ezért kellett az ô nyomdokain járnom. Éjfélkor értem a szoborhoz, ahogy a sámán mondta. Nem fogod elhinni, de a kôszobor teteje aranyszínû volt azon az éjszakán, és egy titokzatos fény ragyogott fölötte!";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "";
			link.l1 = "Amint megérintettem a szobrot, egy fénykör alakult ki a bálvány körül, tûz lobbant fel, majd belevonzott a szoborba. Kirepültem ide, a hajótok rakterébe, lefelé, az orr mellé, a résnél...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "";
			link.l1 = "Alig éltem túl, hála a sámánnak, aki egy különleges bájitalt adott nekem. Végül valami szörnyeteg támadt rám - egy óriás rák. Remélem, most már bízol bennem?";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "A rákos részre gondolsz? Abban hiszek neked. Sok ilyen szörnyeteg van a szigeten. Döglött hallal csalogatjuk ôket, így gyakran ôrzik a hátsó ajtónkat. A tolvajokat szarrá ijesztik. És amit a bálványról meséltél - még nem vagyok ôrült\nDe nem utasítom el a történetedet sem, a helyiek több tucat éve pletykálnak ilyen dolgokról, ráadásul én magam is láttam furcsa dolgokat régen Rivadosnál' ships... na mindegy.";
			link.l1 = "Esküszöm, hogy minden igaz.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Rendben. Akkor legyen. Mondd csak, miért kerestél engem és Nathant? Jan levele szerint azt akartad, hogy én legyek a Parti Testvérek vezetôje?";
			link.l1 = "Pontosan. Sok minden megváltozott a te és Sólyom eltûnése után. Jackman központi szerepet próbál játszani a kalózok között. Azt tervezi, hogy a vezetôjük lesz, és ez sikerülni is fog neki, ha Jan és én nem állítjuk meg.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman komoly és véres játékra készül. Biztos vagyok benne, hogy ô volt az, aki megszervezte a rajtaütést és a Nathaniel elleni vadászatot. Azt is gondolom, hogy ô ölte meg Blaze-t. Csak úgy állíthatjuk meg, ha a Parti Testvérek vezetôjévé tesszük.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Nézd, örülnék neki, de elôbb el kell hagynunk ezt a szigetet. Elegem van belôle. Annál is inkább, hogy Dextert itt hagyhatom, ô el tudja intézni az üzletet a távollétemben. Nem akartam olyan sokáig itt maradni, de a hajóm leégett a klánok elleni harcban\nnem fogok azokon a portálokon keresztül utazni, ne is próbáljatok meggyôzni, szükségem van egy hajóra.";
			link.l1 = "Nem fogom... Steven, a miskitó sámán azt mondta nekem, hogy itt, a szigeten van egy Kukulcan-szobor. Úgy néz ki, mint egy közönséges kôbálvány. Tudod, hol találom?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Nem tudom. Soha nem láttam még ilyen szobrot. Kérdezzen meg valaki mást.";
			link.l1 = "Látod, ha megtalálom ezt a szobrot, akkor hajó nélkül is el tudok majd jutni errôl a szigetrôl. Már nem félek az utazástól. És akkor normális módon visszatérnék ide, és innen elviszlek téged.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "Megértem, de nem tudok segíteni. Ráadásul ez a merénylet dolog eléggé zavaró. Chad halott, de kétlem, hogy a Narwhals elvetné a tervét. Nem akarok úgy élni, hogy minden nap hátba lônek. Mivel élve van szükséged rám, és már belekeveredtél ebbe a zûrzavarba, felajánlom, hogy nyomozz ebben az összeesküvésben\nÚjonc vagy, ez elôny. Találd meg Chad társait, és hozd elém ôket, vagy öld meg ôket ott, ahol állnak, nem érdekel. Beszélj Chimiset, az öreg fekete többet tud, mint amit eddig elmondott\nVigyázz a narválokkal, ne lépd át a határaikat, hacsak nincs jelszavad. Hetente változtatják a jelszavakat.\nHa a veszélyt elhárítottuk, megadom a vitorlázási útvonalat és minden információt, amire szükségetek van\nMenjetek és keressétek meg a felelôsöket. Állítsátok helyre a rendet. Gondoskodom róla, hogy kitakarítsák utánad a börtönt. És szükségünk van egy új börtönôrre. Nekem pedig rum kell, nem érzem jól magam.";
			link.l1 = "Rendben, Steven. Csináljuk...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Képzeld el: valaki megölte az admirális börtönôrét, Chad Kapper-t. Az lehetetlen! Kétségtelen, hogy ez volt a Rivados varázsló feladata...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("Hallottam, hogy Chad Kapper halott. Nem volt hivatalos nyilatkozat, a holttestét sem találták meg. Talán az admirális egyszerûen csak egy titkos küldetést adott neki?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("Nem látom a börtönôrünket, Chad Kappert. Egyesek azt mondják, hogy megölték, mások nem. Mindenesetre senki sem látta holtan.", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy az admirális megduplázta a narválok ellátási árát! Az a kalóz igazán vakmerô!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Nos, mit tudsz, "+pchar.name+"? Van valami hír a narválokról?";
			link.l1 = "Igen. Örülni fogsz, Steve, hogy az összeesküvés leleplezôdött, és az összeesküvôk halottak. Minden bizonyítékom megvan.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "Én is így gondoltam, amikor meghallottam a lövöldözést... Mesélj még, figyelek.";
			else dialog.text = "Tényleg így van? Nagyon örülök, hogy ezt hallom! Mesélj többet, figyelek.";
			link.l1 = "Az egészet a hajóskapitányuk, Chad Kapper tervelte ki. Ô ölte meg Alan Milrow-t a 'Tartarus' börtönben, és pletykákat terjesztett a maga részvételérôl. Azt hiszem, a narválok nagyon dühösek voltak, és ez kemény csapás volt Alan barátnôjének, Red Marynek...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary bosszút akart állni, Chad Kapper pedig a saját céljaira használta fel. Ravasz tervet készítettek az életére irányuló merényletre. Itt mindenki tudja a szokását, hogy minden este a 'San Augustine' a hajó tatján sétálgat.";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Heh! Át fogom gondolni a szokásaimat... Gyerünk, menjetek.";
			link.l1 = "A tervük végrehajtásához szükségük volt egy nagy hatótávolságú és pontos muskétára, és ezt valami Adolf Barbier biztosította. De a stukkerét elzálogosították Giuseppe Faziónak, ezért Mary és Chad elég pénzt adott neki, hogy visszavásárolja. Adolf kivette a zálogból...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "Felbérelték Marcello Küklopszot, egy volt királyi vadászt, hogy megölje magát. Neki kellett átvennie a puskát, és agyonlônie téged. Ezután Mary megölte volna, és a holttestét és a puskát bizonyítékként használta volna fel, hogy Rivados volt a felelôs a támadásért. Marcello küklopsz egy mulatt, tudod...";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "Micsoda okos fattyú!";
			link.l1 = "Ezután a narválok és a kalózok megtámadták volna Rivadost és elpusztították volna ôket. Chad admirálissá válna, Mary pedig a szeretôje lenne. Bár lehet, hogy inkább elvágta volna a torkát, mert túl sokat tudott. Valószínûleg...";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "Akárhogy is, most már vége van. Adolf nem volt elég beszédes, és nekem kellett megölnöm ôt a kabinjában. Maryvel és Küklopszal is meg kellett küzdenem, akik azért jöttek, hogy elhozzák Adolftól a stutzent. Azonnal rájöttek, hogy ki vagyok, és azonnal rám támadtak.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "Tehát a 'Santa Florentina', belsejében fekszenek, ugye?";
			link.l1 = "Igen. Mindhárman.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "Ez jó, hogy nem voltak szemtanúk ebben a zûrzavarban. Majd én gondoskodom a holttestekrôl. Szép munkát végeztél, "+pchar.name+"! Ha az én legénységemben lennél, biztosan az elsôtisztem lennél.";
			link.l1 = "Köszönöm, hogy ilyen jól reagáltál! És végül, vess egy pillantást ezekre a levelekre. Küklopsz és szegény Mary testébôl vettem ki ôket...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Hallottad ezt? A mi veszekedô és bolondos Vörös Máriánk eltûnt. Nem lennék meglepve, ha meghalt volna...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy Red Mary eltûnt. Hallottál róla?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper eltûnt. Néhányan azt mondják, hogy még mindig a kunyhójában van, de én ezt nem hiszem. Túl régen volt már, hogy utoljára fény volt benne.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy Red Mary-t meggyilkolták. Szegény lány! Igen, kemény jelleme volt, de mindenki szerette. Ki tehetett ilyen szörnyûséget?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Mindegy, most már vége van. Adolf nem volt elég beszédes, és nekem kellett megölnöm a kabinjában. Máriával és Küklopszal is meg kellett küzdenem, akik azért jöttek, hogy elhozzák Adolftól a stutzent. Azonnal rájöttek, hogy ki vagyok, és azonnal rám támadtak.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Kár, hogy verekedést kezdtél 'Eva'. Most már a Narwhals is tudja, hogy te vagy a felelôs az embereik megöléséért, az ilyen cselekedetek nem javítanak a hírneveden. Ugyanez elmondható az enyémrôl is. Ne látogasd meg ôket, amíg nem rendezed ezt a konfliktust\náltalában jól csináltad, "+pchar.name+"! Ha az én legénységemben lennél, biztosan az elsôtisztem lennél.";
			link.l1 = "Köszönöm, hogy ilyen jól reagáltál! És végül, vess egy pillantást ezekre a levelekre. Küklopsz és szegény Mary testébôl vettem ki ôket...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Micsoda mészárlást rendezett itt! A narválok nem fogják elfelejteni!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Megértem, hogy a Küklopsz és két narvál bandita megölése... De a lányt, miért ölted meg a lányt? Szegény Mary...", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Szegény Mary? Sajnálod azt a kurvát?";
			link.l1 = "Tényleg sajnálom. Látod, Chad becsapta és kihasználta ôt. Nem tudott ellenállni az érzelmeinek és a természetes forrófejûségének... és ez lett a vége.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("Kaptál 500 dublont.");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Nos, menj Julian testvérhez, és gyújts egy gyertyát... Bár én magam nem fogom megtenni. Rendben, ejtsük a témát. Hálás vagyok neked, "+pchar.name+", a segítségedért. Mostantól számíthatsz a támogatásomra. Szeretnék fizetni a kiváló munkádért. Tessék, itt van ötszáz dublon.";
			link.l1 = "Szép, köszönöm!";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("Azt mondják, hogy az admirális tisztel téged, uram...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy maga az admirális hûséges barátja. Ez igaz?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "Mit akarsz? Nem emlékszem rád...";
			link.l1 = "Persze, hogy nem - még soha nem találkoztunk, és én csak nemrég jöttem ide. Helló, Steven. Micsoda ritka szerencse! Mégiscsak megtaláltalak, kerestelek, bár nem számítottam rá, hogy itt talállak!";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "Várj, haver, nyugodj meg. Engem keresel? Nem tetszik ez nekem. Mi a fenéért kerestél engem?";
			link.l1 = "Értem. Akkor próbáljuk meg újra. Tessék, fogd a levelet. Jan Svenson írta neked. Gondolom, minden gyanúja eloszlik, miután elolvasta.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(olvasás)... Hm. Ez sok mindent megmagyaráz. És én még azt hittem, hogy Blaze haláláért fekete pontot fogsz adni nekem. Tudod, mostanában sokan lelkesedtek ezért. A külsô gyûrûnél hagytad a hajódat? És honnan tudtad, hogy itt vagyok?";
			link.l1 = "Nem tudtam. Az egy szerencsés véletlen volt. És ami Blaze-t illeti... Jan és én úgy gondoljuk, hogy nem te vagy a felelôs a haláláért.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "És igazad van. Nem vagyok. Valaki megpróbál engem hibáztatni, ez igaz. De nem én öltem meg.";
			link.l1 = "Az jó. Érdekes, azért jöttem ide, hogy megtaláljam Nathaniel Hawkot, de helyette téged találtalak, ha-ha!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "Megértem, de nem tudok segíteni. Ezt a sziget öregjeivel kell megbeszélnie. Beszélj Rivados varázslóval, Chimiset-tel. Az öreg fekete ember sokkal többet tud, mint amit mond.";
			link.l1 = "És hol találom ezt a varázslót?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "A börtönömben, a 'Tartarus'. amúgy is terveztem, hogy szabadon engedem, itt az ideje, hogy javítsuk a kapcsolatainkat Rivadossal. Igen, így van! Menj a börtönbe, mondd meg Chad Kappernek, ô a börtönôr, hogy elrendeltem Chimiset\nkiengedését, mondd meg a feketének, miért küldtelek, mondd meg neki, hogy szabadon engedem, ha elég beszédes. Biztos vagyok benne, hogy ez szóra fogja bírni.";
			link.l1 = "Hm... Én még újonc vagyok itt. Hol van a börtön?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Tartsa szem elôtt a következôket. Hagyjátok el a rezidenciámat, menjetek át a hídon, forduljatok balra, a Carolina fregatton keresztül a Gloria gályára, és eljutok az Esmeraldára. Keressetek egy bolt feliratot, és lépjetek be az alatta lévô ajtón. Menjetek be a hajó orr-részében lévô ajtón, és eléritek a Tartarust\nVigyázzatok az Esmeraldán, az a Narwhals klán tulajdona, bár, mások is látogathatják. Ne keresztezze a harcosaikat, és kerülje el a bajt.";
			link.l1 = "Kik ezek a Rivadosok és Narwhalsok?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "A klánok már nagyon régóta itt élnek. Az elsô telepesek utódait képviselik. A narválok többnyire angolok, hollandok és franciák, a rivadók mind négerek. Minden klánnak van egy vezetôje, több hajót tartanak, és nem engednek másokat a területükre\nAzokhoz, hogy meglátogathasd ôket, jelszavakat kell ismerned. Hetente változtatják a jelszavakat.";
			link.l1 = "Jól van. Majd én elintézem. Be fognak engedni a börtönbe?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "Ôk fognak. Itt van a kulcs, így Chad tudni fogja, hogy én küldtelek oda. Vedd el.";
			link.l1 = "Rendben. Akkor majd beszélek azzal a... Chimiset, aztán visszajövök az eredményekkel.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "Szóval, voltál már a 'Tartaruson?'?";
			link.l1 = "Igen. Átadtam a parancsokat Chadnek, és beszéltem a fekete emberrel.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Mondott valami érdekeset a varázsló?";
			link.l1 = "Ó, igen. Elmondta, hol találom Kukulcan teleportáló bálványát. A 'San Geronimo' hajón volt, amely a Narwhals' territorium közelében lévô zátonyon süllyedt el.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha, nagyszerû! Szóval a 'portál' most már a legalján van? Nos, haver, attól tartok, hogy be vagy zárva ezen a szigeten. Szóval csatlakozz hozzám és az embereimhez...";
			link.l1 = " Kitalálom, hogy jutunk el a bálványhoz. Megtalálom az utat. Megtalálom a módját, hogy megtaláljam a bálványt. Chimiset azt mondta nekem, hogy nem szabad bíznod Kapperben, mert saját szemével látta, amint Chad megölt valami Alan Milrow-t, a Narwhals fejét.";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "Micsoda?! Chad megölte Alant? Az a varázsló ôrült! Ez egyszerûen nem lehet igaz!";
			link.l1 = "Tudod, Steve, Chimiset nagyon megijedt. Nem hiszem, hogy hazudott nekem.";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "A fenébe, ez aztán a rossz hír! Alan meggyilkolása máris rontotta a hírnevemet a narwhalok között - néhányan úgy döntöttek, hogy én vagyok a felelôs, és most kiderül, hogy az egyik tisztem tehette!";
			link.l1 = "Úgy tûnik, az emberek szeretnek téged hibáztatni olyan bûnökért, amelyek nem a te bûneid...";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Igen, ez nyugtalanító...";
			link.l1 = "És most a 'nicest' hírek az ön számára - az öreg azt mondta, hogy kihallgatott néhány beszélgetést, és rájött, hogy néhány embere meg akarja önt ölni. Többet csak akkor fog mondani, ha elengeded, és négyszemközt.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Nagyszerû! És mindezt miattad! Ne vegye sértésnek, csak vicceltem. Csak a fejem forog a fejemben: Chad megölte Alant, az embereim merényletet terveznek ellenem... Az öreg fekete ember mondott neked valami részletet?";
			link.l1 = "Nem. Túlságosan fél Chadtôl, ha jól értettem.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Jól van. Megmondom Rivadosnak, hogy találkozni akarok Chimiset-tel. Meglátjuk, mit mond nekem. És ami a kísérletet illeti... rendben, óvatos leszek. Szóval, mit fogsz most tenni, "+pchar.name+"?";
			link.l1 = "Még semmi különöset. Körbejárom a szigetet, és megismerkedem a helyiekkel - talán lesz egy ötletem, hogyan juthatnék ki innen. És elôbb meg kell találnom Nathan Hawkot, ô az oka annak, hogy itt vagyok.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Értem. Ne felejts el meglátogatni, ha megtalálod a kiutat errôl a szigetrôl - megadom a vitorlás útvonalat, anélkül nem fogsz tudni visszajutni ide. Néhány fontos részletet is el fogok mondani.";
			link.l1 = "Jól van. Biztosan meglátogatlak, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = "Jó, hogy eljöttél, "+pchar.name+". Már vártam rád. Rossz hírek. Chimiset meghalt, Chad Kapper nyomtalanul eltûnt.";
			link.l1 = "Bassza meg... Biztos vagyok benne, hogy Chad ölte meg Chimiset-et! Az öreg fekete ember nem ok nélkül ijedt meg annyira.";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Ebben nem kételkedem. A francba, a helyzet óráról órára rosszabbodik. Majdnem megszerveztem a szilárd és egyenes kapcsolatokat Black Eddie-vel, és most ez. Nos, elfelejthetjük a barátságot Rivadossal\nTudják, hogy beszéltél Chimisetszel, mielôtt meghalt, és úgy tekintenek rád, mint az egyik emberemre, úgyhogy kerüld a kapcsolatfelvételt velük.";
			link.l1 = "Igen, milyen kár...";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "Arra kértelek, hogy ne csak azért gyere, hogy híreket mondj. Kaptam egy levelet közvetítônktôl és diplomatánktól, Giuseppe Faziótól, meghívott, hogy éjfélkor látogassam meg a karolinai kabinját. Azt is megemlíti, hogy egyedül kell jönnöm, mert az életem forog kockán, és senkiben sem lehet megbízni\nEz érthetô, Chimiset figyelmeztetett minket egy hozzám közel álló árulóra. Mégis túl gyanús szaga van... egyedül, éjfélkor... Általában maga a kövér ember jön hozzám. Mindenesetre a segítségedet fogom kérni\nTechnikailag nem tartozol az embereim közé, és új vagy itt. Jan leleményes és bátor embernek jellemezte magát, aki jól vív. Szeretném, ha elkísérnél az éjféli találkozóra...";
			link.l1 = "Nem kell megkérdezned engem, Steven. Nem kell kérdezned, Steven. Nekem sem tetszik ez a meghívás - csapda szaga van.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Lehet, hogy tévedek, és nincs csapda, de jobb, ha felkészülök. Örülök, hogy beleegyezett. Gyere a 'San Augustine' fedélzetére éjfélkor, és meglátogatjuk Faziót, az öreg dézsája nincs messze innen.";
			link.l1 = "Megegyeztünk. Éjfélkor a 'San Augustine' fedélzetén leszek, jól felfegyverkezve.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Örülök, hogy látlak, "+pchar.name+". Ne vesztegessük az idôt, nézzük meg, mit mond az a kövér Fazio. Kövessetek!";
			link.l1 = "Menjünk, Steve. Tartsd készenlétben a fegyvered...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "És hol van az a kibaszott kövér ember? Hová tûnt? Mi vagyunk a vendégei, és ô nem fogad minket. Látod ôt, "+pchar.name+"? Talán meg kéne nézni a mellkasát, lehet, hogy benne van...";
			link.l1 = "Úgysem fog tudni bejutni a világ egyetlen ládájába sem. Csitt! Steven! Zaj van odakint...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "Bassza meg! Igazad van. Úgy tûnik, hogy bajban vagyunk."+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Caroline_DlgExit_3");
		break;
		
		case "caroline_5":
			dialog.text = "Argh! Megcsináltuk... Hogy ôszinte legyek, azt hittem, hogy már biztosan halottak vagyunk.";
			link.l1 = "Voltam már ennél nagyobb bajban is. De elismerem, hogy azok a rohadékok kemények voltak. Chimisetnek igaza volt, amikor figyelmeztetett minket - Chad egy áruló. Ki volt az a lány, aki ôket irányította?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "A neve Mary Casper, más néven Red Mary, a néhai Alan Milrow volt barátnôje. Megértem, hogy Chad miért jött ide, meg akarta szerezni a pozíciómat, de mit keresett itt a lány?";
			link.l1 = "Ez elég világos. Azt mondta, hogy a szeretôje volt, a szándékai egyértelmûek - bosszú. Szegény lány nem tudta, hogy egy oldalon harcol a barátja gyilkosával.";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Van értelme. Nos, most már mindenért ôk fognak fizetni! Nem fogok többé ellátmányt és ellátmányt eladni nekik - hadd haljanak éhen. Az embereim bármilyen ostromot kibírnak, ha a Narwhalok megpróbálják megrohamozni a San Augustine-t, lelôjük ôket, mint a kutyákat\nMeg fogják bánni, hogy ilyen aljas módon cselekedtek ellenem. Fazio kövér seggét a falhoz fogom szögezni a székkel a háta mögött!";
			link.l1 = "Várj, Steve! Úgy tûnik, ez nem ilyen egyértelmû. Adj egy napot, és megpróbálom kivizsgálni ezt a zûrzavart. Biztos vagyok benne, hogy Chad az egyetlen felelôs. Megölte Milrow-t, azt a pletykát terjesztette, hogy te voltál, felhasználta Alan barátnôjét...";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "Jól van. Vizsgálja meg. Talán még nem találtuk meg az összes összeesküvôt. Én pedig megyek és iszom egy kis rumot. És, "+pchar.name+": Tartozom neked. Mindenben számíthatsz rám. Ha a legénységemben lettél volna, kaptál volna egy hajóskapitányi pozíciót.";
			link.l1 = "Köszönöm ezt a nagyszerû választ! Úgyis együtt fogunk dolgozni, ha a Parti Testvérek vezetôje leszel. Menj, pihenj egy kicsit, én pedig átnézem ezt a kabint, talán találok valami hasznosat.";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Jól van. Elküldöm ide az embereimet, hogy reggelig takarítsanak - nem akarjuk megijeszteni az embereket a holttestekkel. Nos, a rákok ma este finom vacsorát kapnak! Viszlát!";
			link.l1 = "Viszlát...";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Nos, "+pchar.name+", úgy veszem, hogy a nyomozásod eredményes volt?";
			link.l1 = "Mondhatod. A narváloknak semmi közük az ön elleni merénylethez. Kivéve Mary-t és azokat a fickókat, akik találkoztak velünk a 'Carolina'. szerintem ô uszította ôket, hogy megtámadjanak minket. Fazio kénytelen volt elküldeni a meghívót. Megtaláltam a levelet a kabinjában, ami sok mindent megmagyaráz. Olvassa el.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(olvasás)... Hm. Ez úgy néz ki, mint egy Fazio-féle. Persze, mit tehetett volna Chad ellen... mentette a zsíros bôrét. Úgy tûnik, hogy az egész a csónakosom miatt volt...";
			link.l1 = "Most már magad is láthatod. Az indítékok világosak, és tudjuk, miért ölte meg Chad Chimiset és Alant. Kapper a sziget admirálisa akart lenni. Meglátogattam a Narwhals vezetôjét - Donald Greenspen. Megesküdött, hogy sem ô, sem az emberei közül senki nem szervezkedett ellened.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Megbízik benne?";
			link.l1 = "Én igen. Donald tisztázza a nevét Alan halálával kapcsolatos vádak alól. Készen áll arra, hogy személyesen meglátogasson téged, és hivatalos mentséget hozzon neked. Téged is megvádoltak a semmiért, emlékszel?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Rendben, a háború meghirdetése egy kicsit túlzás lenne. Nem vagyunk abban a helyzetben, hogy vérontásba kezdjünk. Ráadásul úgy tûnik, hogy csak néhány söpredék felelôs ezért, nem az egész klán\nAzt mondod, hogy Donald kész bocsánatot kérni? Rendben, használjuk fel arra, hogy pozitív kapcsolatokat alakítsunk ki a Narwhalokkal, Rivados úgyis elveszett számunkra.";
			link.l1 = "Ez egy jó érv, Steven. Most van itt a tökéletes alkalom rá.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Rendben. Mondd meg Donaldnak, hogy kész vagyok találkozni vele és békét kötni.";
			link.l1 = "Már úton vagyok.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Várj, "+pchar.name+". Jól csináltad, és én finom érmékkel akarok fizetni neked. Tessék, fogd ezt az ötszáz dublont.";
			link.l1 = "Köszönöm!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("Kaptál 500 dublont.");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("Azt mondják, az admirális tiszteli önt, uram...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy maga az admirális hûséges barátja. Ez igaz?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "A börtönömben 'Tartarus'. oda mehetsz és láthatod ôt. Odaadom a kulcsot, és Chad Kapper nem fog akadályokat gördíteni az utadba...";
			link.l1 = "Várj, Steven. Azt hiszem, még nem kéne elmennem Chad Kapperhez...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "És miért ne tennéd? Mi az, nem kedveled ôt?";
			link.l1 = "Valójában, te vagy az, akit nem szeret. Rossz hírem van számodra. Chad Kapper azt tervezi, hogy megkísérli megölni magát.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Micsoda? Micsoda?! Magyarázd meg magad. Ki mondta ezt?";
			link.l1 = "Hadd mondjam el az egész történetet. Az jobb lenne.";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Nos, akkor mondd el...";
			link.l1 = "Miután a vízbefúlt raktérben találtam magam, kijutottam a lyukon keresztül, és a hajóroncsok között úsztam, hogy biztonságos helyet találjak. Végül felmásztam az öreg furulyára, és bejutottam a hajó belsejébe. Valami piros kabátos lány és két nagydarab fickó között dulakodás volt...";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Heh, úgy tûnik, hogy Red Mary végre felbosszantott valakit.";
			link.l1 = "Segítettem neki, és végeztünk azokkal a szemetekkel. Érdekesen elbeszélgettünk utána... Mondd csak, Steve, kik ezek a Narwhals és Rivados - olyan gyakran használta ezeket a szavakat, hogy nem mertem megkérdezni tôle, mit is jelentenek valójában.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "A helyi lakosok csoportjai, akik már régóta itt élnek. Ôk a sziget legelsô telepeseinek utódai. A narválok többnyire angolok, hollandok és franciák, a rivadók mindannyian feketék. Ezeknek a klánoknak saját vezetôik vannak, több saját hajójuk is van, és nem engednek másokat a területükre. Ismerned kell a jelszavaikat, ha meg akarod látogatni a klánok' hajóit. Minden héten megváltoztatják ôket.";
			link.l1 = "Most már értem. Gondolom, Mary a Narwhalokkal van?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Igen, az a kifejezô lány az ô klánjukból való. És mit mondott neked?";
			link.l1 = "Chad Kapper megölte Alan Milrow-t, a szeretôjét, akit maguk fogtak el. Ezután pletykákat terjesztett arról, hogy önnek köze van ehhez. Chad becsapta Mary-t és megpróbálta kihasználni a bosszúvágyát.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "A fenébe is! Megölte Alant? De miért? Hogy engem hibáztasson?";
			link.l1 = "Hogy ellenségessé tegye a narwhalokat önnel szemben, és elnyerje a bizalmukat. Kapper végsô célja, hogy téged likvidáljon és elfoglalja a helyedet. Mary visszautasította, hogy részt vegyen a tervében, és a szeretôje legyen - ezért utasította Narwhalsot, hogy ölje meg.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Elmondta ezt neked?";
			link.l1 = "Igen. És nem úgy tûnt, mintha hazudott volna. Emellett adott nekem egy levelet Chad Kappertôl. Én már elolvastam, úgyhogy neked is ezt kellene tenned.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Hm. Igen, ezek Chad írásai. Nagyon jól ismerem a paraszti kézírását (olvasás) Argh! Hihetetlen! Szemétláda! Áruló! Nos, én felakasztom a saját beleire! Layton! Szedj össze öt embert! Ha jobban meggondolod, Layton, várj, oszolj!\nAzt okosan fogjuk csinálni. Azt terveztem, hogy javítom a kapcsolatainkat Rivadosszal, ez egy lehetôség. A varázslójukat, Chimiset a Tartaroszban tartják fogva. Egy börtönben. Hagyjuk, hogy Rivados maga szabadítsa ki az emberüket, és közben megölik az árulót\nLayton! Menjetek a Tartaroszba, és vegyétek le az összes ôrünket a felsô fedélzetérôl! "+pchar.name+", te is részt fogsz venni ebben, és egy nagyon fontos szerepet fogok rád osztani. Keresd meg Rivados vezetôjét, Fekete Eddie-t, és tárgyalj vele...";
			link.l1 = "Velem? De én nem ismerek itt senkit!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Így hamarosan megismerkedsz néhány emberrel - valójában az egész Rivados klán legelsô emberével fogsz megismerkedni. Te vagy a legalkalmasabb jelölt a tervem diplomáciai részének végrehajtására. A kalózaim nem fognak könnyen átjutni Rivados területein; emellett nincsenek tisztességes szónoki képességekkel rendelkezô embereim.";
			link.l1 = "Nos, rendben. Rajta vagyok. Mit kellene tennem?";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("Kaptál 50 dublont");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Fogd ezt a kulcsot. Ez nyitja ki az összes ajtót 'TartarusTartarus'. Ezen kívül vidd el ezt az ötven dublont. Elôször menj el 'Carolina', vegyél egy jelszót, hogy bejuthass Rivados területére. Beszéljetek Fazióval, ô a közvetítônk, a jelszó ötven dublonnába kerül. Ezután el kell menned a 'Protector'\nFekete Eddie rezidenciájára. Mondd meg neki, hogy Chad Kapper a Narwhals oldalán áll, nem követi tovább a parancsaimat, és Chimiset meg fogja ölni. Add át neki a kulcsot, mondd meg neki, hogy vigyen magával egy tisztességes számú harcost és támadjon 'Tartarus'\nKét legyet ütünk egy csapásra: Rivados a szövetségesének fog tekinteni minket, Kapper pedig a négerek keze által fog meghalni. Nem mondhatnám, hogy irigylem az embert. Megvan?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "Értem - de hol találom 'Protector' és 'Carolina'?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Figyelj, Steve, mondd meg, kik azok a Rivadók és Narwhals. Állandóan róluk beszélsz, de még mindig fogalmam sincs, kik ôk.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "A Narvalok és a Rivadók a helyi klánok. A klánok már nagyon régóta itt élnek. Az elsô telepesek utódait képviselik. A narvalok többnyire angolok, hollandok és franciák, a rivadók mind négerek. Minden klánnak van egy vezetôje, több hajót tartanak, és nem engednek másokat a területükre\nAzokhoz, hogy meglátogathasd ôket, jelszavakat kell ismerned. Hetente változtatják a jelszavakat.";
			link.l1 = "Most már értem. Mondja meg - hol találom 'Protector' és 'Carolina'?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Könnyû, mint a pite. Hagyja el a lakóhelyemet, menjen át egy hídon és forduljon balra. Ez lesz Carolina. Protector megtalálása egy kicsit trükkösebb: miután átmentél egy hídon, fordulj jobbra, és menj Santa Florentina felé a táblákon át\nTaláld meg ott Rivados katonákat. Kérni fogják a jelszót. Mondd ki hangosan és tisztán. Ezután menj be a Furyba, és lépj be a Protectorba a taton keresztül.";
			link.l1 = "Na, most már értem. Azt hiszem, hogy nem fogok hiányozni nekik.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Rendben. Láss hozzá, barátom!";
			link.l1 = "Viszlát!";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Még mindig itt vagy? Menj Rivadosba, most!";
			link.l1 = "Már úton vagyok!";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Heh, úgy tûnik, hogy Red Mary végre felbosszantott valakit.";
			link.l1 = "Igen. Felbosszantotta Chad Kapper-t. Csatlakoztam a harchoz, de sajnos nem tudtam megmenteni a lányt, az egyik támadó megvágta a szablyájával.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Sajnálom a lányt, persze, de kétségtelenül az ô hibája volt. Mary mindig is kereste a bajt. És mi van Chad Kapperrel? Ô tulajdonképpen a csónakmesterem.";
			link.l1 = "A hajóskapitánya? Ô... Tessék, olvassa el ezt a levelet. A lány holttestén találtam. Most már látni fogja, hogy ki és miért rendelte el a megölését. Kapper merényletet tervez az életére.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Hol voltál ilyen sokáig? Azt mondták, hogy Rivados kiszabadította a varázslót...";
			link.l1 = "Túszként tartottak fogva 'Protector' azért, hogy biztosítsam a biztonságukat egy rajtaütéstôl. Igen, kiszabadították Chimiset, de Chadnek sikerült megszöknie.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "A francba! Soha ne üzletelj feketékkel, azt mondják... Még egy ilyen egyszerû feladatra sem voltak képesek! Basszák meg azok a Rivadók!";
			link.l1 = "Chad elrejtôzött a narválok között...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Persze, hogy elrejtôzött! Nem bolond, és rájött, hogy Rivados nem jutott volna be a Tartaroszba a segítségem nélkül. Most elrejtôzik és az árnyékból támad. Layton! Erôsítsétek meg az állásokat! Tartsátok nyitva a szemeteket! Egy vagyont fogok fizetni annak, aki elintézi Kapper-t!";
			link.l1 = "Rendben, Steven. Át kell gondolnom a dolgot. Talán képes leszek megtalálni Chad-et. Viszlát.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "Mi történt, "+pchar.name+"? Úgy nézel ki, mint akit maga Lucefer üldöz.";
			link.l1 = "Hoztak neked egy hordó whiskyt?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Milyen hordót?";
			link.l1 = "HOZTAK NEKED EGY HORDÓ WHISKYT?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Miért kiabálsz így, haver? Nem, nem hoztak. Mi a baj?";
			link.l1 = "Hála Istennek, hogy idôben jöttem... Chad Kapper vett egy hordó Bushmills-t Axel Yost-tól...";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills-t? Ez a kedvencem! Évek óta nem ittam belôle!";
			link.l1 = "Igen-igen. És ezt Kapper is tudja. Megkérte a haverját, Marcello Cyclopsot, hogy vegyen egy kis arzént Sancho Carpentero-tól. Látod miért?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Azt hiszed, hogy meg akar mérgezni?";
			link.l1 = "Kétségtelenül! Ezért siettem annyira. Ha hoznak neked egy hordó whiskyt - ne idd meg. Az mérgezett.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Heh, kösz a figyelmeztetést! Óvatos leszek. Várj, most hová mész?";
			link.l1 = "Meg kell találnom Kapper-t és Cyclops-ot. Van egy ötletem, hogy hol találom meg ôket. Viszlát!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha! Örülök, hogy látlak, haver! Úgy tûnik, az életemmel tartozom neked.";
			link.l1 = "Hoztak whiskyt?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "Megvannak! Bushmills, ahogy mondtad. A mi kedves Fazio-unk olyan kedves volt... Letartóztattam, hogy nyomozzon...";
			link.l1 = "Bevallotta?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Igen. Azt mondja, Kapper kényszerítette erre. Megijedt, és... elhozta nekem a hordót ajándékba Narwhals-tól.";
			link.l1 = "Kapper halott. Megöltem ôt és a narvál barátait. Már csak egy szemétláda maradt - Marcello Küklopsz... Biztos vagyok benne, hogy ez a dagadt disznó tudja, hol van. Hadd lökjem meg egy kicsit!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Persze, csak próbáld meg nem megölni, szegény Fazio elég rossz egészségnek örvend.";
			link.l1 = "Gyengéd leszek... nagyon gyengéd, a fenébe is!";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", barátom, valami nagyon nincs rendben velem...";
			link.l1 = "Steven! Megittad a whiskyt? Bassza meg, tényleg megittad?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Igen... Ez a legjobb ír whiskey... Giuseppe Fazio hozta nekem ma. Azt mondta, hogy ez egy ajándék a Narwhal vezértôl... a béke jelképe... ó, ez fáj... Úgy néz ki, hogy ez a végem.";
			link.l1 = "A francba! A whisky arzénnel volt mérgezve! Chad Kapper és Marcello Cyclops tette ezt!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Argh... a csónakos végre elkapott... bassza meg!";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "Nem fogsz meghalni! Hallasz engem? Nem fogsz meghalni! Gyorsan, vedd el ezt a flaskát. Ez a legerôsebb gyógyító ital a világon, mindent meggyógyít. Idd meg... most!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("A komancsok bájitalt használtak.");
			Log_Info("A méreg meggyógyult!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", ez tényleg segített. Még mindig rosszul érzem magam egy kicsit, de a fájdalom már majdnem elmúlt...";
			link.l1 = "Ez a bájital még a leghalálosabb mérgeket is semlegesíti. Idd meg mindet! Igen...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "Egy csoda... Most már jól vagyok. Köszönöm, barátom, soha nem felejtem el...";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "Most már jobb, ha pihensz. Úgy nézel ki, mint egy halott ember. Az a szemét Kapper nem fog tudni többé fenyegetni minket - birkóztam meg vele és néhány narwhallal is. Csak Marcello Küklopsz maradt. Azt mondtad, hogy Fazio hozta neked a whiskyt, igaz?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "Most már jobb, ha pihensz. Úgy nézel ki, mint egy halott ember. Azt mondtad, hogy Fazio hozta neked a whiskyt, igaz?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Igen. Tényleg figyelnem kellett volna a sápadt arcára és a remegô kezére...";
			link.l1 = "Úgy tûnik, hogy erre kényszerítették. Rendben, meglátogatom azt a kövér disznót, és megszerzem tôle az információt. Biztos vagyok benne, hogy tudja, mire van szükségem. Jobbulást!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Igen. Tényleg figyelnem kellett volna a sápadt arcára és a remegô kezére...";
			link.l1 = "Úgy tûnik, erre kényszerítették. Rendben, elôbb-utóbb megkeresem azt a dagadt disznót, de most Kapperrel és Küklopszal kell foglalkoznom. Tudom, hol rejtôznek. Gyógyulj meg!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Mit mondasz, "+pchar.name+"? Már tudom, hogy Kapperrel már volt dolgod a 'Eva'. És még ott sem takarítottál, ha-ha! Hogy ôszinte legyek, csodálom! Megölni Csádot és az embereit, hát nem semmi! Igen, Jannak igaza volt, amikor megdicsért téged.";
			link.l1 = "Nemcsak Kapperrel bántam el, de még egy merényletet is megakadályoztam ellened. Meg akartak mérgezni, Steven, de én megakadályoztam, hogy a rohadékok ezt tegyék.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Megmérgezni engem? De hogyan?";
			link.l1 = "Chad vett egy hordó ír Bushmills whiskyt Axeltôl...";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills-t? Ez a kedvencem! Évek óta nem ittam belôle!";
			link.l1 = "Igen-igen. És ezt Kapper is tudja. Megkérte a haverját, Marcello Cyclopsot is, hogy vegyen némi arzént Sancho Carpenterótól.  Aztán ô és a haverjai fogták Faziót, és lementek a 'Eva'. rakterébe, hogy megmérgezze a whiskyt, és arra kényszerítse Faziót, hogy elhozza magának Narwhals ajándékaként.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Ha! Természetesen azonnal megittam volna egy korsó whiskyt...";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad számított rá. De nem sikerült neki - még arra sem volt ideje, hogy arzént tegyen bele. Igen, és magammal vittem a hordót. Megkaphatod ajándékba.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad számított erre. De elbukott - még arra sem volt ideje, hogy arzént tegyen bele.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Mutasd meg... "+pchar.name+", ez egy igazi Bushmills! A legjobb ír whisky! Argh, évek óta errôl álmodom! Te, te... A francba! Kizártad Chadet, és ilyen csodás whiskyt találtál!\nAdom neked az egyik legjobb talizmánomat. Ez Thor kalapácsa, örökkévaló. Az ágyúsod imádni fogja!";
			link.l1 = "Köszönöm! Én is nagyon örülök.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("Kaptál egy 'Thor kalapácsa' amulettet.");
			dialog.text = "Alig várom, hogy megigyak egy korsónyit ebbôl a csodálatos whiskybôl... "+pchar.name+", ma este bulizni fogunk! Holnap pedig gyere el hozzám! Addig is elgondolkodom a szavaidon és Chad tettein...";
			link.l1 = "Rendben, Steven, nem zavarlak a... pihenésben, ha-ha!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "Valami nagyon fontosat mondtál nekem. Gondolkodom a szavaidon és Chad tettein... és aztán felhívlak.";
			link.l1 = "Rendben, Steven. Várni fogok!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, hát itt vagy, "+pchar.name+". Most már mindenki itt van és kezdhetjük. Összehívtalak téged és Laytont, hogy megbeszéljük a helyzetet, és eldöntsük, mit tegyünk a Narwhalokkal.";
			link.l1 = "Hogy érted, hogy mit csináljunk a Narwhals-szal?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "Az életem elleni merényletet Chad szervezte, akit a Narwhals közvetlenül támogatott. Ezt nyílt agressziónak ismerem el. Tekintettel arra a tényre, hogy Rivadossal rövid távú szövetségben vagyunk, a következôket ajánlom fel\nSzövetséget kötünk Rivadossal, elôkészítünk egy hadmûveletet és egyszer s mindenkorra eltöröljük a Narvál klánt. Elegem van a bandita viselkedésükbôl. Te, "+pchar.name+", ismét a diplomata szerepét fogod játszani\nbeszélj Fekete Eddie-vel és Chimiset-tel, gyôzd meg ôket, hogy csatlakozzanak hozzánk a közös ellenségünk elleni harcban. Szerintem hallgatni fognak rád, úgy vélik, hogy a szövetségesük vagy\nDexter kidolgoz egy támadási tervet, ô mindent tud a sziget földrajzáról. Layton, van már valami gondolatod?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "Bölcs ötlet. A San Gabrielbe való visszavonulásra kényszerített narválok talán nem adják meg magukat túl hamar a csapatainknak - de ellátmány nélkül gyorsan elpusztulnak, vagy kénytelenek lesznek kétségbeesett támadást indítani. Mit szólsz, "+pchar.name+"?";
			link.l1 = "Mit mondok... Azt mondom, hogy a narválok ellen háborút hirdetni politikailag rossz lépés.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "És ezt azután mondod, hogy megölted Chad összes emberét? Ne felejtsd el, hogy mindegyikük narvál volt!";
			link.l1 = "Nem mindegyikük. Az egyik elsô ilyen szemétláda, Marcello Cyclops, nem volt narvál. Valójában hûséges volt Rivadoshoz, és talán azt tervezte, hogy csatlakozik hozzájuk. Elvégre ô egy mulatt. Szerintem a narválok nem felelôsek az ellened elkövetett merényletért - csak néhány fattyú, akiket Kapper toborzott.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "És mit javasolsz? Ne vegyünk tudomást errôl az egészrôl?";
			link.l1 = "Azt javaslom, hogy maradjak a diplomata szerepemnél - de ezúttal a Narwhals vezetôjével, Donalddal fogok tárgyalni. Emellett hadd mondjam el a véleményemet a Narwhals megtámadásának lehetséges kimenetelérôl.";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "Folytasd.";
			link.l1 = "Amennyire én látom, a béke a Szigeten csak a két, erejükben majdnem egyenlô klán közötti rivalizálás miatt lehetséges. A ti harcosaitok a harmadik erô, és bármelyiküknek segíthetnek a gyôzelemhez. De mind a Rivados, mind a Narwhals erôs, és a gyôzelem mindenképpen túl sokba kerülne a gyôztesnek.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "A Narwhals elpusztításának ára a te és Rivados embereinek sok élete lesz. Emellett Layton azt mondta, hogy San Gabriel ostroma sokáig fog tartani, és Rivados esetleges támadásával is szembe kell néznünk, ha túl sok embert veszítünk...";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "Ne felejtsétek el, hogy mindkét klán uralni akarja a szigetet, és nemrég még az ellenségetek voltak. Szóval véleményem szerint a mészárlás igazi csapás lenne az egyszerû lakosok számára.";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "Hm. Bölcsen hangzanak a szavaid, de még nem gyôztél meg.";
			link.l1 = "Valahogy el kell hagynom a szigetet is, ezért el kell jutnom Kukulcan szobrához a tenger fenekén. A Rivadók nem tudnak segíteni nekem - talán a Narwhalok igen? A velük való harc sem segít rajtam.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "Ha! És azt hiszem, van még egy ok, amiért nem akarod, hogy a narwhalok az ellenségeink legyenek. Az a vörös hajú lány a Ceres Smithybôl, igaz, barátom? Igazam van? Ne aggódj miatta, "+pchar.name+", ha már ennyire törôdsz vele - biztonságos helyre visszük, mielôtt a harcok elkezdôdnek.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" De egyetértek, ha ennyire elszánt vagy. Menj és keresd fel Donald Greenspen-t, a Narwhals vezetôjét. A rezidenciája az Esmeralda hátsó részében van. Lássuk, mit mond nekünk az a gazember.";
			link.l1 = "Jól van. Máris indulok.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Menj Donaldhoz, pajtás, és vedd rá, hogy megnyalja a csizmádat, ha-ha! Várni fogok rád.";
			link.l1 = "Már úton vagyok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "Na és, beszéltél már Donalddal? Látom, hogy beszéltél...";
			link.l1 = "Igen. Nem utasította az embereit, hogy bántsanak téged. Az összes narvált, aki részt vett a merényletben, Chad Kapper szervezte be. Nagyon feldúlt, és biztosít minket, hogy a Narwhaloknak nincsenek rossz szándékai veled szemben. Készen áll arra, hogy személyes bocsánatkérését hozza önnek az ön elleni merényletért és azért, hogy Alan meggyilkolásával gyanúsította önt.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Kész idejönni és elmondani mindezt?";
			link.l1 = "A Bibliára esküdött.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, talán ez megteszi. Úgy tûnik, hogy az egyetlen szemétláda, akit hibáztatni lehet, az az én volt hajóskapitányom.";
			link.l1 = "Ebben teljesen biztos vagyok, Steven. Nincs szükségünk erre a háborúra. Senkinek sincs rá szüksége.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "Jól van! Rendben. Kész vagyok elfogadni Donald bocsánatkérését, de jobb, ha siet. Menj és mondd meg neki.";
			link.l1 = "Azonnal, Steven.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Vigyétek oda a Máriátokat, és éljétek együtt az életeteket, ott van elég szabad hely.";
			else sTemp = "";
			dialog.text = "Várj! "+pchar.name+", nagyon örülök, hogy felbukkantál itt, a Szigeten. Jan nagyon nagy becsben tart téged, de te minden várakozást felülmúltál. Ha a csapatomban lennél... tulajdonképpen felajánlom neked Kapper helyét, amíg itt vagy. Te leszel a helyôrségem parancsnoka a 'Tartarus'. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "Nem, Steven, köszönöm szépen, de nem maradok itt sokáig. Keress valaki mást. És ami Máriát illeti - jól megvagyunk a 'Ceres Smithy'.oldalon.";
			else link.l1 = "Nem, Steven, köszönöm szépen, de nem maradok itt sokáig. Keress valaki mást.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("Kaptál 500 dublont.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ahogy akarod, barátom. Legyen úgy. Kérlek fogadd el ezt az ajándékot tôlem. Úgy gondolom, hogy hasznosnak találod majd ezt az ötszáz dublont.";
			link.l1 = "Köszönjük!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("Azt mondják, az admirális tiszteli önt, uram...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy maga az admirális hûséges barátja. Ez igaz?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Beszéljünk az üzletünkrôl... Vegyük ezeket a vitorlázási irányokat. Használd ôket, hogy épségben és hajón térj vissza ide\nHogy enélkül vagy nem találsz itt átjárót a Sziget körüli zátonyok és viharok miatt, így a hajód valószínûleg itt csatlakozik a testvérekhez. Ne feledd, hogy viszonylag kis hajóval kell áthaladnod a zátonyokon. Lugger, schooner, brigantine, brigg... Negyedik osztály, nem nagyobb\nA célod az, hogy ezekkel a vitorlázási utasításokkal a zsebedben elhagyd ezt a helyet, majd egy hajóval visszatérj értem. Amint visszatértem, csatlakozom hozzád és Svensonhoz a játékban. Arról viszont fogalmam sincs, hogyan tudod elhagyni a szigetet. Ebben a kérdésben csak te tudsz segíteni magadon, és talán az a Kukulcan is...";
			link.l1 = "Vicces, de valójában számítok a segítségére. Köszönöm a hajózási utasításokat, Steven. Még megtalálom a kiutat errôl a szigetrôl.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Akkor sok szerencsét kívánok. Siessetek, ha tudtok, a raktáraim elég gyorsan fogynak, és hamarosan nem lesz semmi ellátmányom. Tudod, hogy mire képesek az éhes és felfegyverzett emberek, ugye?";
			link.l1 = "Tudom. Most mennem kell. Viszlát!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Megtaláltad a kiutat a szigetrôl, "+pchar.name+"?";
			link.l1 = "Még nem, Steven. Még mindig rajta vagyok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Nos, mit tudsz, "+pchar.name+"? Van valami érdekes hír?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, szeretném megkérni, hogy add vissza az elkobzott holmimat.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, mesélj még errôl a szigetrôl.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Biztos vagy benne, hogy Sólyom nincs a szigeten? Átjött a portálon, tehát itt kell lennie.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Ismer egy Fehér Fiú nevû embert?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "Milyen területek tartoznak itt a narválokhoz és a rivadókhoz?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "Honnan tudhatom meg a jelszavakat, hogy feljussak a klán hajóira?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Figyelj, van valami térkép a szigetrôl?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "Milyen érdekes kardod van. Még sosem láttam ehhez hasonlót...";
				link.l8.go = "blade";
			}
			link.l9 = "Egyelôre nincs kérdésem. De lehet, hogy hamarosan lesz néhány...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ah, igen, persze! Teljesen megfeledkeztem róla... A holmid fent van a ládában. Elviheted ôket. Layton nem fog megállítani.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "Ez a sziget nagyon régi lehet. Láttam régi karavellákat a külsô gyûrûnél, több mint száz évesek. Létezése a nagy sekély víz és az erôs áramlás miatt lehetséges, amely a hajókereteket ide hozza. Az emberek már régóta élnek itt. Vannak olyanok, akik itt születtek és soha nem mentek el.\nA klánok közvetlenül azután alakultak ki, hogy de Betancourt expedíciója itt kötött ki. Egyébként a San Augustine és a Tartarus is része volt annak az expedíciónak. A Tartarus rakterében rengeteg fekete szalvétát találtak. Vezetôjük, Pedro Rivados tiszteletére alapították a Rivados klánt. Ô lázadást robbantott ki, és megpróbálta elfoglalni a Tartarust, de nem sikerült nekik. A férfit lassú halálra ítélték\nA rabszolgák itt kapták meg a szabadságukat, és azonnal szembefordultak a többi helybélivel. Uralkodási igényük és afrikai hagyományaik arra késztették a legtöbb keresztényt, hogy egyesüljenek, és megalakítsák a Narwhal klánt\nNarwhal klánnak rengeteg zsoldos, katona, tiszt és kalandor volt a soraiban, ellátmányt gyûjtöttek és egy kisebb, profi hadsereget építettek, amely készen állt arra, hogy számbeli fölényével harcoljon Rivados ellen. Azóta a Narwhals nagyon válogatós lett az újoncok felvételében, Rivados pedig korlátozta az ambícióikat. Az eredményeket most láthatjátok.";
			link.l1 = "Voltak kapcsolatok a sziget és a külvilág között?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "Az elmúlt tíz évben nem voltak kapcsolatok. A helyiek egy idôben kereskedtek Kubával, aranyat és értékes árukat cseréltek élelmiszerre. De ezt már nem csinálják.";
			link.l1 = "Hm. Úgy tûnik, hogy Svensonnak és Fekete Pásztornak is igaza volt... És miért nem hagyták el az emberek a Szigetet, amíg még volt rá lehetôségük?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Néhányan igen, de a többség úgy döntött, hogy marad. Sokan közülük itt találtak otthonra, sokan mások itt születtek. Nem akarnak visszatérni. Úgy tûnik, ez a hely sokkal jobb nekik... Néhányan túlságosan félnek átutazni a viharok övezetén a régi hajókon. Ami a Rivadosokat illeti - nekik nincs más választásuk, mint itt maradni.";
			link.l1 = "És miért jöttél ide? Elhagytad a kiváló fregattodat, és inkább egy brigget választottál...";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "Blaze Sharp meggyilkolásával vádoltak meg. Fogalmam sincs, miért. Nyilvánvaló, hogy valaki mocskos játékot ûz. Az ellenségeim száma rohamosan növekedni kezdett, ezért el kellett hagynom Isla Tesorót, és itt kellett várnom. Már nagyon régóta tudok errôl a helyrôl. Otthagytam a fregattomat, mert túl nagy volt ahhoz, hogy megkerüljem a helyi zátonyokat\nAmint ideértem, azonnal megtámadtak a narwhalok és a rivadók. Nem örültek az érkezésemnek. Éjszaka hosszúhajókon közeledtek a hajómhoz, és felgyújtották. Mi ágyúinkkal és muskétáinkkal szétzúztuk a teknôiket. De a tûz megtette a hatását - a briggem leégett\nMegôrültünk, mint a fene, megszálltuk a szigetet, megrohamoztuk a San Augustine-t, és megmutattuk nekik, hogyan harcolnak a korzárok. Nem bírták a nyomásunkat, és hamarosan gyáván hátat mutattak. Elfoglaltuk a San Augustine-t, kiderült, hogy ezek az idióták ellátmányraktárnak használták. Most meg kell venniük tôlem, olyan áron, amit én nevezek meg\nMegfogtuk a helyi vezetôket is: Alan Milrow-t, a Narwhals egyik fejét és Chimiset Rivados szellemi vezetôjét. Layton a következô napokban felderítette a környéket, és megtámadtuk a Tartarust - a védelmük gyenge pontját\nMost két ilyen hajót tartunk a kezünkben, és a klánoknak hozzá kell szokniuk a jelenlétünkhöz. Mostanra már valamiféle béke van itt. Ami a többi helybelit illeti, úgy tûnik, tetszik nekik a harmadik erô gondolata.";
			link.l1 = "Most már értem. Köszönöm a történetet!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "Nem tudok biztosat mondani, de én amúgy sem láttam itt. Sem az utcán, sem a kocsmában, sem a klánhajókon. Te vagy az elsô, aki azt mondta, hogy Sólyomnak valahol itt kell lennie. De ahogy már mondtam - kétlem.";
			link.l1 = "Értem...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "Fehér fiú? Hm... Nem, még nem hallottam róla. De ez nem jelenti azt, hogy nincs itt. Nem kell ismernem az összes helyi söpredéket, egyetértesz?";
			link.l1 = "De igen. Rendben, akkor megkérdezek valaki mást.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "A szigetet a narválok, a rivadók és az én embereim osztják fel. Van egy semleges terület is. Én ellenôrzöm San Augustine-t és Tartarust\nRivados tartja a Protector-t, ami a rezidenciájuk, Fury - kaszárnya, Velasco - raktár. Idegeneknek tilos az átjárás, egy speciális jelszót kell kimondani, hogy oda bejuthassatok\nNarwhals rengeteg hajó van a birtokukban. Esmeralda a vezetôjük lakhelye és egy raktár. Az úgynevezett 'San Gabriel' tudományi központ és egy Phoenix platform. Végül, de nem utolsósorban a Ceres Smithy - a mûhelyük. Az Esmeralda kivételével minden hajó tiltott terület, egy jelszót kell mondanod, mielôtt beengednek\nA többi hajó semlegesnek számít, helyi lakosok élnek bennük. Sancho kocsmája a Fleron karavellán található, Julian testvér pedig a Gloria gályán a helyi egyház feje.";
			link.l1 = "Köszönöm az információt!";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "Valójában olyan embereknek adják, akik iránt ôk maguk is érdeklôdnek. Sajnos, te nem tartozol közéjük. De ez aligha probléma. Menj egy Carolinea nevû öreg fregattra. Ott lakik egy kövér, ravasz kutya, Giuseppe Fazio. Ô itt valamiféle diplomata. Nem tudom, mit csinált, mielôtt idejött, de az embernek van szakértelme\nMindenkivel üzletel. A klánok közvetítôként használják. Kapzsi. Egyetlen dublónáért is kész felfalni magát, de ezt sosem mutatja ki. Kérj tôle egy aktuális jelszót, bár ez sokba fog kerülni.";
			link.l1 = "Köszönöm! Ezt megjegyzem.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexternek van egy. Ô a helyettesem. Rögtön az érkezésünk után készített egy részletes térképet. Menj fel hozzá, és beszélj vele, ha szükséged lenne rá.";
			link.l1 = "Megvan. Köszönöm. Köszönöm.";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha! Egy szép széles kard. Valamiféle egyedi penge... Egy trófea Alan Milrow-tól, a Narwhal klán fejétôl. Így neveztem el. Jurgen, egy narválfegyverkovács készítette valami csodálatos fémbôl, amit a tenger fenekén találtak\nnem rozsdásodik, sosem tompul, és mindent és mindenkit egyszerre vág el. Nagyon elégedett vagyok ezzel a fegyverrel, és nem fogom hátrahagyni.";
			link.l1 = "Kíváncsi vagyok, hogy Jurgen tud-e még egy ilyen széles kardot készíteni? Jó pénzért, természetesen...";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Nos, biztosan tud még egyet készíteni. De nem fog. Jurgen narvál, hûséges a klánjához, és soha nem fog semmit sem készíteni kívülállóknak. Különben is, nagyon különleges vasra lesz szükséged a második kard elkészítéséhez. Ez a vas csak a mélyben található - és hogyan juthat oda bárki is? Szóval felejtsd el.";
			link.l1 = "Értem. Kár.";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Ha, láttam a vitorláidat a horizonton, "+pchar.name+". Örülök, hogy látlak, barátom! Milyen volt az út?";
			link.l1 = "Jól.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Jól. Nos, készen állok, hogy felszálljak a hajódra és elhajózzak Jan Svensonhoz. Layton itt marad admirálisnak, már elfoglalta a széket, ha-ha! Úgy tûnik, nem fogja elhagyni a szigetet, szereti ezt a helyet.";
			link.l1 = "Egyszer azt mondta, hogy nagyon jól érzi magát.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Igen, valóban így van. Nos, én készen állok. Induljunk?";
			link.l1 = "Szállj fel a hajómra, Steven. Elhajózunk, amint befejeztem az itteni dolgaimat.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Megegyeztünk! Eh, túl régen éreztem már egy rendes hajó fedélzetét a lábam alatt!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Itt vagyunk, barátom. Nos, megyek és meglátogatom Svensont. Neked is találkoznod kellene vele, és megbeszélni a jövôbeli terveinket. Ha-ha! Forró napok várnak ránk, mi?";
			link.l1 = "Kétségtelenül. Viszlát, Steven!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Persze, megteszem, amit tudok! Menj csak.";
			link.l1 = "Steve, nézd meg... Egy cápafog. Ne mondd, hogy nem ismerôs neked!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Okos vagy! Igen, ez az én fogam. Nos, ez egy cápa foga, amit azért öltem meg, hogy lenyûgözzek egy szépséget. Azóta Cápának hívnak. Csak kevesen voltak képesek erre a víz alatt egy egyszerû szablyával, de én fiatal és bolond voltam, és Beatrice Sharp volt a Karib-tenger legszebb lánya... Hogy szerezted meg?";
			link.l1 = "A Szent János egykori hóhérjától kaptam. Egy embert mészároltak le vele. A neve... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Igen, megtettem. Ezzel a foggal vágtam el a torkát. Elborzasztott Beatrice halála, és úgy gondoltam, hogy Leadbeater az egyetlen felelôs, aki életben maradt. Késôbb elolvastam a róla talált papírokat. Nos, minden joga megvolt a bosszúhoz\nBlaze húga csak rosszkor volt rossz helyen. Maszk nem hibáztatható a haláláért, nem ô akarta, csak Mészáros volt a célpontja. Megbántam, hogy megöltem. Az igazság az, hogy az a ribanc Jessica szervezte meg az egészet.";
			link.l1 = "Megôrizted azokat a papírokat?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Miért tenném? Persze, hogy nem. Nem volt rájuk szükségem. De ha van idôd, elmondhatom, miért üldözte Maszk Mészárost.";
			link.l1 = "Megvan. Tudja, hogy nem kíváncsiságból, tényleg érdekel. Még arra is kész vagyok, hogy leírjam a történetét.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Tudom, soha nem vesztegeted az idôdet. Akkor figyelj. Joshua Leadbeater a brit haditengerészet egy átlagos kapitánya volt, és a késôbb legendává vált fregatt 'Neptun', parancsnoka volt...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("Egy órával késôbb...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... Leadbeater azonban túlélte, és egy arra járó hajó mentette meg. Sebei csúnyává tették az arcát, és azóta maszkot viselt. Életének értelmévé vált, hogy megtalálja és megbüntesse minden szerencsétlenségének okozóját.";
			link.l1 = "Értem... Leírtam. Azt hiszem, el kellene olvasnom, hogy lássam, mit kaptam. Nagyon szomorú történet. Láttad azt a Jessicát?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Persze! Butchert minden útjára elkísérte, amíg a férfi nem dobta ôt Beatrice miatt. Jess ezt nem tudta megbocsátani neki. Mészáros talizmánjának hívták, mert mindig szerencséje volt, amíg vele volt\nHiszed vagy sem, de amint Barbadoson megszabadult tôle, az üzletei rosszul mentek, a zsákmány szegényes lett, és a 'Neptungyakran vendégeskedett az Isla Tesoro hajógyárban. Bár ez azzal is magyarázható, hogy Butcher a legtöbb idôt inkább a kabinban töltötte Beatricével, mint a fedélzeten\nBeatrice nem olyan volt, mint Jessica, nem volt a kalandok és a háború rabja, bár Nicolas megtanította ôt vívni és tengerészkedni. Igen, szerette a tengeri romantikát, de nem volt benne elég kemény jellem. A Butcher' s 'Neptun' nem volt neki való hely. Végül megölte ôt.";
			link.l1 = "És mi a helyzet Jessicával?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Ó, nem semmi volt. A 'Neptun' minden tengerésze engedelmeskedett a parancsainak, és nem csak azért, mert a kapitány barátnôje volt. Jess elsajátította a vívást és a tengerészetet, Butcher erôfeszítései nem voltak hiábavalóak. Kemény volt és vakmerô, ráadásul jó külsôvel is megáldott\nSok férfi akart vele szexelni, de ô csak Butchert akarta, ôt zaklatni igazán kockázatos volt - sokan szó szerint a saját hátukon próbálták ki az eredményt, és a legkitartóbbaknak a vívóleckéi bizonyultak az utolsónak az életükben\nJessnek volt egy nagyon különleges kardja, az egyetlen a maga nemében a Karib-tengeren, fogalmam sincs, honnan szerezte. Lángpengés kard. Senki sem tudja megfogni a pengéjét, és a legkisebb érintés is szörnyû sebet hagy\nJess nem születésébôl, hanem hivatásából volt kalandor. Egyébként, ha többet szeretnél megtudni róla, beszélhetsz egy ismerôsöddel. Ô sokkal többet tud róla mondani, mint én.";
			link.l1 = "Tényleg? És ki az az ember?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Forest Devil soha nem fogja bevallani, de tervei voltak Jessicával kapcsolatban. Ez volt az az idô, amikor már magáénak tudhatta Nyugat-Maint, és a hírneve is irigylésre méltó volt, így a tigrisasszony is olyan jó volt, mint ô\nAmikor Mészáros megszabadult Jess-tôl, Jan gyanúsan gyakran kezdte látogatni Barbadost, és gyakran rázendített az angol helyôrségre. Mint tudjuk, Jessica a bridgetowni ültetvényes lánya volt\nMindenesetre a terveit magánkörökben jól ismerték, mégsem merte senki szóvá tenni, Jan manapság talán Blueweldben ül a fenekén, de akkoriban egy rossz szó a megszólításában rosszul végzôdhetett\nA végén nem jött össze nekik. Jess nem tudott együtt élni azzal, ahogy Butcher bánt vele, és egy évvel késôbb bosszút állt a Maszk segítségével. Ez a bosszú mindenki számára szörnyû véget ért: Butcher, Beatrice, a Maszk és saját maga számára is. Mindannyian meghaltak.";
			link.l1 = "Nem mindannyian. Mészáros még mindig életben van.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Mi az? Rosszul hallottam? Életben van?!";
			link.l1 = "Igen. Butcher kapitányt nem végezték ki. Nos, meg kellett volna, de életben maradt, hála Jacob Jackmannek és Henriknek, a hóhérnak, aki megfélemlítette a hóhért. A kivégzés hamis volt. Bizonyítékom van rá.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Az lehetetlen! És hol van most?";
			link.l1 = "Lawrence Beltrope néven ismerik, és Port Royalban él. Még mindig veszélyes. Jackman, aki annyi bajt okozott a Parti Testvérek között, az ô parancsnoksága alatt cselekedett.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "A fenébe! A szállásmester ilyen hosszú idô után megtalálta a kapitányát! Beltrope, azt mondod... várj! Most már értem, miért volt Blaze iratai között egy különös kihallgatási jegyzôkönyv... Úgy tûnik, hogy Blaze is rájött a Mészáros-Beltrope-ra...";
			link.l1 = "Mirôl beszélsz?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Miután elfoglaltam ezt a lakhelyet, átkutattam az öreg Blaze iratait. Találtam egy bizonyos Samuel Brooks kihallgatási jegyzôkönyvét. Sokat írt Thomas Beltrope kalandjairól, és arról, hogy kalózként és Nicolas Sharp közeli barátjaként ismert. Úgy tûnik, hogy ô volt Butcher apja.";
			link.l1 = "Érdekes. Úgy tûnik, Sharp és Beltrope gyerekei folytatták szüleik' munkásságát...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Úgy tûnik... De mondd csak, barátom, miért érdekelnek téged ennyire a néhai emberek tettei? Miért érdekel?";
			link.l1 = "Szükségem van olyan papírokra, amelyek megerôsítik, hogy Helen McArthur Beatrice Sharp lánya, és hogy minden joga megvan ehhez a vezetéknévhez. Nem érdekel, hogy ô is Beltrope.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Sem Leadbeater irataiban, sem Blaze levéltárában nincs semmi Helen McArthurról. Furcsa, hogy Beatrice nem szólt Blaze-nek az unokahúga születésérôl. Nem úgy néz ki, mintha ô lett volna.";
			link.l1 = "Figyelj, talán van valami más is Sharp irataiban? Minden részletre szükségem van!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, azt hiszem. Blaze jegyzetei szerint megpróbálta megtalálni a szigetet, ahol a nôvére meghalt. Leadbeater büntetôexpedíciójára vonatkozó iratok vannak. Semmi érdekes, kivéve néhány szélességi számot\nEz a szélességi kör a Karib-tengert szeli át északi részén. De a földrajzi hosszúságnak semmi jele. Nyilvánvalóan Blaze kutatásai kudarcot vallottak, nem is lehet elképzelni, hány kis sziget van ezen a szélességi fokon.";
			link.l1 = "És mi ez?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Lássuk csak... itt: 21. szélességi fok 32' North. Nem tudom, hogy ez hogyan segíthet neked.";
			link.l1 = "De igen. Rendben, Steven, köszönöm szépen az ôszinte történetedet. Viszlát!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Mondhatnád ezt. Most pedig Tortugáról\nA szigetet azért nevezték el így, mert majdnem úgy néz ki, mint egy teknôs. Levasseur tizenkét évig vastagította a teknôspáncélt - Fort La Roche. A frontális támadás öngyilkosság, az erôd nehéz ágyúi nem hagynak esélyt. Tehát ebbôl a szépségbôl levest fôzni nem lesz könnyû. A spanyolok már nagyon régóta próbálkoznak, és soha nem jártak sikerrel.";
			link.l1 = "Ezért mentem Svensonhoz. Szóval mi a terved? Gyerünk, Steven!";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Az embereim az elmúlt hetekben tisztességes munkát végeztek Tortugán, és sok érdekes információhoz jutottak. Szóval jó híreim vannak számodra, haver! Úgy tûnik, nem kell a La Roche ágyúival foglalkoznod, hiszen nem csak nekünk van elegünk Levasseurbôl. A barátai között is vannak olyanok, akik a halálát akarják.";
			link.l1 = "Gyerünk...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Köztudott, hogy Levasseur rajong a fiatal telepes lányokért. Miután befejezte velük a szórakozást, eltûnnek. Tortuga fô rabszolgaszállítóját Robert Martennek hívják a Voltigeur gályáról\nHelyettese, Levasseur unokaöccse, Henri Thibaut közvetlenül a kikötôben választja ki a legszebb fehér lányokat a patrónusának. Így került Marten kezébe nemrég egy nagyon szép lány az angol briggrôl. A neve Molly Jones. A lányt nem Levasseur-nek, hanem az unokaöccsének adta át éjszaka valami titkos barlangba Tortugán\nA legénységnek azt mondták, hogy a lány szívrohamban meghalt, és a 'testét' a fedélzetre dobták. Úgy tûnik, a haverok úgy döntöttek, hogy magukra hagynak egy csinosat. Ha Levasseur rájön Mollyra, akkor ezeknek a kettônek gondjaik lesznek.";
			link.l1 = "És hogyan bízhatunk meg ebben az információban? Nyilvánvaló, hogy mindketten tisztában vannak vele, hogy a tûzzel játszanak...";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "Igaz. De minden láncnak van gyenge pontja. És találtam neked egy ilyet. Három nappal ezelôtt egy Fernand Lucas nevû volt 'Voltigeur' tengerész túl sokat ivott és sok érdekes dolgot mesélt a Basse-Terre kocsmában\nKiderült, hogy Molly Jones megkérte, hogy kérjen segítséget a Szent Jánosban élô bátyjától. De Lucas nem érte el a célját, megszökött a kapitányától, és most Guadeloupe-on ül a seggén, és rumba fojtja gyávaságát\nAntigua nem biztonságos hely a francia kalózok számára. Ezt ne feledjétek! Fox ezredes kész felakasztani ôket a sziget minden pálmájára, miután a felesége francia korzózó keze által halt meg. Félelmetes tengerészgyalogosai pedig mindent megtesznek, amit a parancsnokuk parancsol.";
			link.l1 = "Még nem értem, mi köze van ennek a mi üzletünkhöz... Beszéljünk a mi embereinkrôl, Martenrôl és Thibaut-ról. Mi értelme van egy ilyen kockázatnak? Ennyire erôs volt a nô varázsa, vagy ezek a rabszolgatartók kegyelmet mutattak?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Nagyon jól ismerem ezt a söpredék Mártont. Ha kockáztat, az azt jelenti, hogy vagy aranyról van szó, vagy félti a bôrét. Nem tudom, mi köze van ehhez a foglyunknak\nTalán Robert hatalmas váltságdíjat vár érte, ami nem valószínû, a lány úgy nézett ki, mint egy szolga. Vagy talán... Ha! Vajon ki lehet Marten számára ijesztôbb, mint Levasseur!";
			link.l1 = "És mit gondolsz, miért rejtegetik még mindig Jones kisasszonyt a kormányzó elôl? Talán megkapták tôle, amit akartak, és átadták Levasseurnek? Igen, van valami konkrét mondanivalója errôl a Thibaut-ról?";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Nem sokat tudok errôl az emberrôl. Csak azt tudom, hogy a nagybátyja eléggé megbízik ebben a kölyökben ahhoz, hogy az örökösévé tegye. Még mindig van egy lánya, különben minek ez a sok összeesküvés?\nNem világos, hol tartják fogva a lányt, és miért engedi Thibaut, hogy Marten vezesse. Van egy rejtély, ami segíthet megnyerni ezt a játékot Tortuga megrohamozása nélkül. Te francia vagy, úgyhogy gondolom, inkább így szeretnéd\nDe sietned kellene, Lucas részeg beszédét meghallhatják Marten és Levasseur ügynökei, el tudod képzelni a következményeket!";
			link.l1 = "Értem én. Tehát Thibaut Levasseur örököse? És egy rabszolgalányt rejteget a nagybátyja elôl? A fenébe, gondolom, a fiatalember alig várja, hogy a nagybácsi minél hamarabb meghaljon!";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Igaz. Lucas szavai szerint ez a Molly egy ritka szépség, a mi bátor Thibaut-nk talán beleszeretne. Tudod, mire képesek az emberek a szerelemért. Menj Basse-Terre-be\nKeresd meg ezt a részeg idiótát, és vedd rá, hogy beszéljen. Ráadásul Mollyról és a bátyjáról is megtudhatnál bármit. Elôbb talán Antiguára érdemes ellátogatnod, Molly oda küldte Lucast, méghozzá céllal. De mi a célja?";
			link.l1 = "Értem. Ne vesztegessük az idôt. Köszönöm, Steven.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Menjetek!";
			link.l1 = "Megtaláltam Molly testvérét St. John's-ban. Ez Fox Batmanje. De van valami furcsa. A húga, Molly egy közismert ronda banya, körülbelül olyan magas, mint te. Ô Fox lányának, Catherine-nek a szobalánya, és egészen a közelmúltig vele volt Angliában...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "Ami Catherine-t illeti, ô valóban híres a szépségérôl, és úgy volt, hogy meglátogatja az apját a születésnapján, de késett, mert a század késett Londonban...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "Apja, aki nehezen viselte felesége halálát a francia korzótámadás miatt, szigorúan megtiltotta neki, hogy magányos hajóval elhagyja Angliát. Molly Jones tehát nem lehet Thibaut foglya. Akkor ki ô?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... A fenébe is, ha tudom. Talán egy másik Molly Jones, nem az, akirôl kérdeztél. Bár... túl sok a véletlen egybeesés. Nem hiszem, hogy ez az egész csak véletlen! Van néhány homályos gyanúm, de... bár sok furcsa dolog történhet!";
			link.l1 = "Hogy érti ezt? Mondd el!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "És mi van, ha a lány nem engedelmeskedik az apa parancsának, és kíséret nélkül hajózik ki? A múlt hónap elég viharos volt, az Albatros megsérülhetett, és könnyû préda lett Marten számára. Gyanítom, hogy Catherine nem árulta el az igazi nevét, meg kell értened, miért, és Molly néven tartják fogva Tortugán\nTudod, mi vár rá, ha az igazi neve kiderül. Kezd értelmet nyerni a dolog!";
			link.l1 = "A fenébe! Erre soha nem gondoltam volna! Molly... Catherine... De ez az egész egybeesik!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "Errôl beszélek, haver. Nem biztos, hogy igazunk van, de...";
			link.l1 = "De ez mindent megváltoztat! Talán az angoloktól kellene támogatást kérnünk? Hogy a tengerészgyalogosok szuronyai szabaddá tegyék számunkra az utat!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Nyugodj meg, "+pchar.name+"! Több szilárd bizonyítékra van szükségünk. Nem tudhatjuk biztosan. Lehet, hogy az igazi Katalin Londonban van, és várja a hajóraj indulását. A briteknek saját problémáik vannak, nem fogják megkockáztatni, hogy megtámadják La Roche-t. De ha a gyanúnk igaz, és Fox ezredes megtudja, mi történt a lányával...\n blokádot állít fel a sziget körül, és megvárja a hajóraj érkezését. Aztán megtámadja a várost. A tengeri rókák félelmetes erôt képviselnek a közelharcban. Biztos vagyok benne, hogy három napon belül kitûzi az angol zászlót Tortuga romjai fölé. Tényleg ezt akarod?";
			link.l1 = "Nem, ez nem a mi utunk. Most már értem, milyen váltságdíjról beszél Marten.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "Körültekintôen kell eljárnunk. Még abban sem vagyunk biztosak, hogy Marten tisztában van Molly valódi kilétével. Fox ezredest zsarolni öngyilkos ötlet lenne. Fôleg, hogy Cromwell osztaga hamarosan megérkezik\nHa Catherine meghal, mi is veszítünk. A testvériségünknek nem érdeke, hogy Fox ezredest a szokásosnál is jobban feldühítse. Ez az ember sok bajt okozhat. Ha Catherine-nek mégis meg kell halnia, gondoskodnunk kell róla, hogy ne a mi kezünk által haljon meg, és miután eljátszotta a szerepét a játékunkban\nDe sokkal jobb lenne, ha szegény lányt átadnánk az apjának. Megmentôje meg fogja kapni a jutalmát. Ha nem is ebben a világban, de a másikban.";
			link.l1 = "Isten akaratából... Steven, te egy zseni vagy! Azonnal Tortugára megyek! Kiderítem, ki az a Molly Jones! Átkozottul biztos vagyok benne, hogy ô Catie Fox!";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Talán... Ne vesztegesse az idejét, "+pchar.name+". És ha igazam volt - gyôzôdjön meg róla, hogy életben marad.";
			link.l1 = "Megteszem, amit tudok. Viszlát!";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho! Köpd ki, barátom! Minden problémát meg fogunk oldani, az biztos!";
			link.l1 = "Akkor rögtön a lényegre térek. Ismeri Miguel Dichosót?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ismerem ôt. Az a spanyol don eladott nekem egy nagyszerû hajót - egy fregattot. Eh, micsoda hajó volt, képzeld csak el...";
			link.l1 = "Hadd találjam ki, egy egyedi hajótest, tizenhat csomós maximális sebesség? 'Santa Quiteria'?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Igazad van a hajótestével és a sebességével kapcsolatban, de a neve más volt - 'San Martin'. Hatalmas mennyiségû aranyat fizettem neki, ez volt mindenem. Minden megtakarításom egyenesen annak a gazembernek a zsebébe ment.";
			link.l1 = "Biztos, hogy San Martin volt a neve, és nem Santa Quiteria? És mikor vette meg? És miért nevezed ôt gazembernek?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Annyi kérdés! Sorrendben válaszolok rájuk: Biztos vagyok benne, hogy San Martin volt. Én személyesen segítettem Alexus munkásainak, hogy megszabaduljanak egy ilyen pápista nevû deszkától a hajó farán. Én neveztem el 'Fortune' - egy ilyen hercegnônek sokkal megfelelôbb nevet\nvettem nem sokkal Blaze Sharp meggyilkolása elôtt, 1654 telén. Miért hívtam Miguelt így? Mert annak a szemétládának sikerült ellopnia a hajót a providence-i spanyol katonai bázisról. Elég nagy mûsort rendeztünk nekik, közvetlenül San Juan erôdje elôtt. Feláldoztam két félholt luggert, hogy hitelesebbé tegyem a harcot. felgyújtottuk és elárasztottuk a hajókat, szimulálva a fregattal való csatát. És ahogy leszállt a sötétség - a San Martint az Isla Tesoro szigetére vezettük. Én megkaptam a hajót, Dichoso pedig a pénzt. Elmondta a fôparancsnokságának, hogy a fregatt elsüllyedt a kalózokkal vívott csatában, a San Juan parancsnoka ezt megerôsítette.";
			link.l1 = "Szóval így töltik meg a spanyol dónok a zsebüket! Micsoda gazember! Mondd csak, ez tényleg 1654 telén történt? Talán tavasszal? És a fregattot megrongálta a vihar?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Télen... A fenébe is, nem vagyok teljesen biztos benne - lehetett tavasszal is. Nem igazán emlékszem. A fregatt nem volt sérült, teljesen új volt. Úgy nézett ki, mintha újonnan épült volna. Ha rá gondolok, legszívesebben sírnék a bosszúságtól...";
			link.l1 = "Miért? Igen, és hol van most a gyönyörû fregattod?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Mert elment tôlem. Felültettek, a talizmánomat Blaze holttestére tették, és elterjesztették, hogy én voltam a gyilkos. Aztán hallottam, hogy Marcus Tyrex - a kódôrünk - fekete jelet fog nekem adni. Ezért úgy döntöttem, hogy egy idôre elmenekülök a zûrzavar elôl az Igazság Szigetére, ahol megtaláltatok\nEgy fregatton nem tudtam odajutni, ezért elzálogosítottam a Fekete Pásztornak egy ellátmánnyal teli briggért cserébe, nem sok pénzem volt a ravasz Dichosóval kötött üzletem után. Azt reméltem, hogy eladhatom az ellátmányt, és egy-két hónap múlva visszatérhetek Isla Tesoróra... Nos, a többit tudod.";
			link.l1 = "És Fekete Pásztor nem várt meg téged, ezért eladta a lányt.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Pontosan. Egy angol, pontosabban egy skót, William Paterson vette meg. Megpróbálhatnám visszaszerezni a lányt, persze, de ez a felföldi komoly madár, a királyi haditengerészet kapitánya, Fox ezredes jó barátja. Ráadásul ugyanúgy üzletelt Jackmannel, mint maga Svensonnal\nA skótnak van egy százada... csessze meg, nem látom többé a hajómat.";
			link.l1 = "Értem, értem. Nem tudod, hol van most az a Dichoso?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Fogalmam sincs. Soha nem láttam ôt, miután megvettem a Fortune-omat.";
			link.l1 = "És Miguel miért nem ajánlotta fel másnak, hogy megveszi? Mit szólnál Tyrexhez, Barbazonhoz, Sharphoz? Vagy Paterson?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Fogalmam sincs. Paterson nem volt itt akkoriban, amennyire emlékszem. Zachariah, Jacques és Marcus sosem egyeztek volna bele, és én... Nagyon tetszett a fregatt!";
			link.l1 = "Megértem, hogy... Nem értek semmit. Mindenütt rejtélyek...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Már megint a múltba merülsz? Ezúttal melyik szigetet akarod elfoglalni? Ha-ha-ha-ha!";
			link.l1 = "Van egy sziget... Bár még nem találom az utat hozzá. Rendben, Steven, köszönöm az információt! Viszontlátásra!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Sok sikert, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "És örülök, hogy segíthetek, mint mindig. Ezúttal mit akarsz, "+pchar.name+"?";
			link.l1 = "Megint a régi barátodról, Miguel Dichoso-ról van szó. Tudom, hogy ismét látták Isla Tesoro-n. Nem tudnál segíteni, hogy megtaláljam?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ho, barátom, ezt nem is tudtam. Nem láttam ôt itt. Azóta nem láttam, mióta megvettem 'Fortune' t tôle. És miért van szükséged arra a spanyol donra?";
			link.l1 = "Szükségem van rá. Miguel tudja az utat egy régi indiai városba. Nagyon szeretnék oda eljutni.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Mint mindig, barátom, most is belerángatod magad a zûrzavarba. Sajnos, nem tudok segíteni. Azt tanácsolom, járd körbe a települést, és kérdezd meg az embereket, talán valaki látta ôt. Tudod, ô egy híres ember itt.";
			link.l1 = "Hé, Steven, legalább azt meg tudnád mondani, hogy néz ki?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Hát, huszonöt-huszonnyolc éves, körülbelül olyan magas, mint te, sötét szemû, nincs parókája. A jobb arcán van egy szablyaheg.";
			link.l1 = "Hm. Tudod, sok ember van, akire illik ez a leírás.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Más egyedi részlet nincs róla. Magabiztos, szemtelen és nagyon veszélyes. Voltak róla pletykák...";
			link.l1 = "Értem. Rendben, majd körbekérdezôsködöm róla. Sok szerencsét, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Jó helyre jöttél! Köpd ki!";
			link.l1 = "Van egy fickó, aki nem fél a kalózoktól. Nem veszi ôket komolyan. Meg kell leckéztetni a tiszteletet. Ne feledd, ne öld meg.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! Ez nem más, mint az öreg Charles! Lefogadom, hogy megint valami viszonyba keveredtél! Térjünk rá a részletekre, ki a célpont ezúttal és mit tanítsunk neki...";
			link.l1 = "Egy vendég Európából, a francia pénzügyminisztérium egyik ellenôre - Noel Forget báró. Francia kereskedelmi társaságot akar itt alapítani, de én és egy közeli barátom ellene tiltakozunk. Próbáltuk meggyôzni a bárót, hogy az itteni kereskedelem nagyon kockázatos lenne a hollandok, az angolok és fôleg a kalózok miatt, miután Levasseurt legyôzték, de nem hallgatott ránk. Félelmet kell belé vernünk, hogy a saját bôrén érezze.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Igen-igen... Egy igazi báró! Megtámadjuk a hajóját?";
			link.l1 = "A terv a következô: a hajója hamarosan elindul Kikötô-au-Prince-bôl Capsterville-be. El kell fognotok a bárót az indulása után, és túszul kell ejtenetek. Jobb lenne, ha nem süllyesztenétek el a hajót, és elkerülnétek a legénység megölését. A franciák végül is a barátaink. Képes leszel ezt megoldani?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Nos, nem ígérhetek semmit. De megpróbálom. Milyen hajóról van szó?";
			link.l1 = "A brigg neve 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Egy brigg nem ellenfél a fregattomnak. Könnyen elbánunk velük. Ha megadja magát, mindenkit életben hagyok.";
			link.l1 = "Tökéletes. Félelmet kelteni és felajánlani nekik, hogy engedjenek. Utána küldd a bárót a patkányoktól hemzsegô raktérbe. Próbáljatok meg a lehetô legmocskosabb helyet keresni, de ne tartsátok ott egy napnál tovább, különben megbetegedhet és meghalhat. Ezután szállásold el a kabinban, menj az Isla Tesoróra, és zárd be valami félreesô helyre. Öltöztesd néhány emberedet foglyul ejtett francia kereskedônek, és vedd rá ôket, hogy úgy viselkedjenek. Három napon keresztül egyfolytában meséljenek neki arról, hogy a kegyetlen kalózok hogyan üldözik ôket, rabolják ki, követelnek váltságdíjat, kínozzák meg ôket... minden szükséges részletre kiterjedôen.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha-ha! Ez lehet a legviccesebb munka, amit nagyon régóta elvállaltam! Hát akkor majd találok ilyen színészeket, pajtás. Ne legyenek kétségeid, a történeteik után a báród összeszarja a gatyáját! Megmutatják majd neki a bicskák és a felhevített rudak okozta sebhelyeket... ";
			link.l1 = "Ez az. Aztán kényszeríteni fogod, hogy írjon egy levelet Poincy-nak, váltságdíjat kérve. Harmincötszázezer egy ilyen nagyágyúért nem is olyan sok.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Jó, rendben. Mi lesz a következô lépés?";
			link.l1 = "Aztán a bárót a törökökhöz viszed. Ott elveszed a váltságdíjat, és átadod nekem a bárót. És emellett meg kell említened, hogy minden francia felelni fog Tortugáért és Levasseurért.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha-ha! Ez aztán a pokoli trükk! Mi személyesen, nos, tudod, mit tettünk Levasseurrel, és most... ha-ha-ha-ha!... Rendben, haver. Meglesz! Azt mondod, hogy a hajó hamarosan megérkezik?";
			link.l1 = "Hamarosan. Figyelnünk kell.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Ne aggódj, nem hagylak cserben. Személyesen fogom elintézni. Ha hallod a pletykát, hogy a bárót elfogták, gyere hozzám.";
			link.l1 = "Jól van. Köszönöm, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Természetesen, haver. Ahogy megbeszéltük. Ijesztô történetek gonosz kalózokról, ártatlan francia kereskedôk lemészárlásáról, ostorcsattogás, nyögések és sikolyok. Szénnel teli tüzelô és perzselô bilincsek. Pontosan úgy, ahogy lennie kell.";
			link.l1 = "Na, most! Vigyázzatok a lovakra! Élve van rá szükségem.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Ne aggódj, életben marad. Remegô kézzel írta a levelet. Itt is van.";
			link.l1 = "Mi van odaírva? Könyörög Poincy-nak, hogy hozza ki ôt ebbôl a helyzetbôl?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Pontosan, haver! Könyörög!";
			link.l1 = "Dobd el ezt a levelet, vagy jobb, ha elégeted. Egy hét múlva találkozunk a törököknél. Úgy kell tûnnie, hogy idôre van szükségünk, hogy begyûjtsük a váltságdíjat.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Megvan. Egy hét múlva, északi öböl. Ne felejtsd el elvinni a pénzt: ez jól fog kinézni. Utána gyere el hozzám, és rendezzük ezt le.";
			link.l1 = "Persze, fogadok, hogy erre még az echinus is rájött volna. Viszlát késôbb! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hé, békaevô! Állj!";
			link.l1 = "Nem mozdulok.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Itt a báród. Kicsit kopottas, de egy darabban van. Ô az?";
			link.l1 = "Igen.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Tökéletes. Most pedig adja át a pénzt, vagy végeztünk! És ne próbálj meg átverni minket, már látunk téged!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Tessék.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "A francba! Elfelejtettem a hajón...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha-ha! Okos kölyök vagy, francia. Fogd a szentséged. És mondd meg Poincy-nak, hogy készítse elô a pénzt: minden francia fattyúnak fizetnie kell azért, amit Levasseurrel és Tortugával tettél. És a kereskedôid fizetni fognak nekünk az áruikkal és a hajóikkal. Ha-ha-ha-ha! Ne felejtsetek el még néhány bárót hozni a szigetvilágba, sok hasznot hoznak nekünk! Ha-ha-ha!";
			link.l1 = "Kérlek, menj a hajómra, báró.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "És eszedbe se jusson üldözni minket, kapitány. Tudod, hogy ki vagyok. Több békafaló foglyot tartok fogva, és ha nem térek haza idôben, mindet megölik az embereim. Megértetted?";
			link.l1 = "Eljön az idô, és elintézünk titeket, átkozott istenkáromlók!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Szórakozol velem?";
			link.l1 = "Egy perc, hozom...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Steven, mit csinált az ostobád!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, mit csináltál? Hol a pénz? Nem mondtam a fiaimnak, hogy ez nem igazi... és ez az idióta úgy döntött, hogy át akarod verni ôket...";
			link.l1 = "Milyen kár! A báró meghalt... Most mit fog Poincy csinálni?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Nos, haver, ez a te hibád, remélem, megérted. Talán még jobb is lesz neked.";
			link.l1 = "Micsoda idióta vagyok! Mindent elrontottam. Rendben, elmegyek Poincyhoz... Bocsáss meg, hogy bolond voltam, Steven, viszlát.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Pihenned kell, kezdesz elveszted az érzéked. Gyere el hozzám valamikor, hozok neked rumot és finom szûzlányokat.";
			link.l1 = "Köszönöm, majd meglátogatlak, ha tudlak.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Szívesen, haver. Nekem ez volt a legszórakoztatóbb az idén! Annyit nevettünk, én és a srácok!... Szóval szeretném megköszönni ezt neked. Itt a pénzed.";
			link.l1 = "Tartsd meg magadnak a részed.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Felejtsd el. A barátságunkért tettem ezt. A Parti Testvériség sokkal többel tartozik neked, mégsem kértél egyetlen dublont sem.";
			link.l1 = "Mégis, legalább ötvenezret vegyél el a szolgáltatásokért és a kártérítésért. Köszönöm, Steven! Örülök, hogy egyszer találkoztam veled az elveszett hajók furcsa szigetén.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Én is. Charles, látogass meg, amikor csak idôd engedi!";
			link.l1 = "Örömmel!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Egy hetet késtél! Nem mondtam a fiaimnak, hogy ez nem a valóság... ! Nem voltak hajlandók tovább várni, és úgy döntöttek, hogy véget vetnek a báródnak!";
			link.l1 = "Micsoda idióta vagyok! Mindent elrontottam! Mit fogok mondani Poincy-nak?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Nos, haver, ez a te hibád, remélem, megérted. Talán még jobb is lesz neked.";
			link.l1 = "Rendben, elmegyek Poincyba... Bocsáss meg, hogy bolond voltam, Steven, viszlát...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "Pihenned kell, kezdesz kifulladni. Gyere el hozzám valamikor, szerzek neked rumot és finom szûzlányokat!";
			link.l1 = "Köszönöm, majd meglátogatlak, ha tudlak.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "Érdekes, kíváncsi vagyok. Nos, menjünk sétálni.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Nyisd ki a lépem! Nem hiszek a szememnek! Tényleg ô az? Mondd, hogy ô az? Is this 'Fortune'?!";
			link.l1 = "Igen, barátom, a szemed nem csal meg. Ez ô. Hiányzott?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ha ha ha ha, nem hiszem el! Ezer ördög! De honnan szerezted?";
			link.l1 = "Egy bizonyos William Paterson nevû skótól. Igen, igen, attól, aki a Fekete Pásztortól vette.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Fújj le... És mi az, eladta neked 'Fortune'? ilyen gyönyörû hajót? Miután megvetted?";
			link.l1 = "Hehe, nos, majdnem. Fogalmazzunk így: nem jöttünk ki jól egymással, és a hajót a konfliktusunk miatt felmerült költségeimért kárpótlásul vettem el. Neki amúgy sincs szüksége hajóra.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "Te még jobban meglepsz engem ... Ô egy katonai kapitány Anglia szolgálatában. A gyarmati századát kirabolhatja, ha akarja. Még én sem kockáztattam meg, hogy kitörjem a fogaimat rajta. És hogyan ellenôrizted? Sikerült letépnie a 'Fortune' századról?";
			link.l1 = "Nem, a hajóraj elsüllyedt. Valójában nem volt könnyû. A csata komoly volt, de lakott helyektôl távol zajlott, és a szemtanúk között csak az én matrózaim és tisztjeim voltak. Általában nem tartok a brit hatóságok üldözésétôl. William Paterson egyszerûen eltûnt valami szabályos kaland során ...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Hûha... Már régen elvesztettem a reményt, hogy újra látom a fecskémet. Nos, remélem, ez a hajó hûségesen szolgálja majd önöket. Igazán örülök neked, barátom!";
			link.l1 = "Micsoda? Nincs szükséged rá? Vissza akartam adni a jogos tulajdonosának...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ha-ha-ha, barátom, tartsd 'Fortune' magadban. Elôször is, te vagy a jogos tulajdonosa. Ôszintén, a csatában szerezted. Nem jó dolog ezek után elhagyni a hajót. Másodszor pedig, már van egy új hajóm. Persze, amikor megvettem 'Fortune', nem gondoltam, hogy valaha is lecserélem valami másra. De mivel már nem számítottam rá, hogy újra látom, rendeltem egy új fregattot az Alexustól. És tudjátok... Rohadtul jó a fickó. Hallottam, és ebben az esetben nem a te közremûködésed nélkül, ha-ha!";
			}
			else
			{
				dialog.text = "Ha-ha-ha, barátom, tartsd 'Fortune' magadban. Elôször is, te vagy a jogos tulajdonosa. Ôszintén, a csatában szerezted. Nem jó, ha ezek után elhagyod a hajót. Másodszor pedig, már épül egy új hajó a számomra. Persze, amikor megvettem 'Fortune', nem gondoltam, hogy valaha is lecserélem valami másra. De mivel már nem számítottam rá, hogy újra látom, rendeltem egy új fregattot az Alexustól. És alig várom, hogy mikor tehetem be a lábam a fedélzetére.";
			}
			link.l1 = "Nos, akkor nincs más választásom, mint megtartani magamnak ezt a gyönyörû hajót, Steven!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Pontosan. Az egyetlen dolog, amit kérek, hogy vigyázzatok 'Fortune'. Higgyétek el, ilyen hajót sehol máshol nem fogtok találni. Egyedülálló. Én pedig emlékként szeretem. És örülnék, ha tudnám, hogy a barátomé ez a hajó, és nem valami gazemberé.";
			link.l1 = "Jó Steven. Megígérem, hogy megvédem 'Fortune'.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Igen, és még valami...";
			link.l1 = "Odafigyelés.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Mivel most 'Fortune', van, szeretnék Önnek egy üzletet ajánlani.";
			link.l1 = "Nagyon figyelmesen hallgatlak.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "Mint mondtam, az Alexus jelenleg egy új fregattot épít nekem. Ô persze nem valószínû, hogy túlszárnyalja a 'Fortune' sebességben, de nem is fog sokat hozni. És csak egy dolog miatt van szükségem pár erôs, de gyors hajóra. Lehet, hogy egyedül is meg tudnám csinálni, de kettô sokkal jobb.";
				link.l1 = "Nagyszerû. És miféle üzlet ez?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "Mint mondtam, Alexus nemrég készített nekem egy új fregattot. Ô persze nem valószínû, hogy felülmúlja a 'Fortune' sebességben, de nem is fog sokat hozni. És csak egy dolog miatt van szükségem pár erôs, de gyors hajóra. Lehet, hogy egyedül is meg tudnám csinálni, de kettô sokkal jobb.";
				link.l1 = "Nagyszerû. És miféle üzlet ez?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "Korai még errôl beszélni, mert még nem tudom, hogy az új hajóm mikor hagyja el a készleteket. Úgy tûnik, Alexusnak vannak nehézségei az anyagok kitermelésével. Egyébként, ha van rá lehetôséged, segíthetnél neki. Biztos vagyok benne, hogy tisztességesen megfizet: Nagyon komoly elôleget adtam neki. Miután megtalálja az összes anyagot, azt hiszem, egy hónapon belül készen lesz a hajóm. Akkor már csak rád várok. De mindenképpen jöjjön a 'Fortune' és szerelje fel elôre, akkor kevés lesz az idô! Igen, és gyôzôdj meg róla, hogy a spanyolok nem akarják ezüsttálcán látni a fejedet. A részleteket majd késôbb elmesélem.";
			link.l1 = "Nos, megkérdezem a hajóépítônket, milyen segítségre lenne szüksége. És visszatérünk a beszélgetésünkre majd egy hónappal azután, hogy segítek Alexusnak, amikor újra hajózni fogsz.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "Túl korai errôl beszélni, mert a hajóm még el sem hagyta a készleteket. Még fel kell szerelnem. Úgyhogy legkorábban egy hónap múlva várom. De mindenképpen gyere a 'Fortune' és szereld fel elôre, akkor kevés lesz az idô! Igen, és gyôzôdj meg róla, hogy a spanyolok nem akarják ezüsttálcán látni a fejedet. A részleteket majd késôbb elmesélem.";
			link.l1 = "Rendben, akkor majd késôbb visszatérünk a beszélgetésünkre, amikor már újra vitorla alatt vagytok.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Nos, rendben. Most megyek a rezidenciára, ha nem bánja. A dolgok, ahogy mondani szokták, nem várnak.";
			link.l1 = "Hamarosan találkozunk, Cápa! Nem búcsúzom el.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Az enyém készen van, a tiéd mi a helyzet? Mondtam, hogy gyere 'Fortune'. Nem tudom, hol hagytad, de túl kockázatos lenne más hajón ilyen kockázatot vállalni. Úgyhogy azon a hajón várom, amelyen megállapodtunk. És ne feszítsd túl a húrt.";
				link.l1 = "A fenébe, teljesen elfelejtettem, te szemétláda! Várj: a megfelelô hajón visszatérek.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, én mondtam, hogy század nélkül jöjjön. Abban az esetben, amit veled akarok csinálni, extra hajókra biztosan nincs szükség. Vigye el a flottilláját valahová, és jöjjön vissza.";
				link.l1 = "Igen, teljesen elfelejtettem. Várj: nemsokára visszajövök század nélkül.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Á, hát itt vagy, barátom! Végre! És akkor elkezdtem aggódni. A hajóm már majdnem kész. Most elküldtem Tiraxhoz: fel kell szerelnie a harminckettes kaliberûvel, amit a múlt hónapban vett el a zsákmányolt nehézgályáról. Már el is lovagoltam vele a törökökig és vissza, és azt kell mondanom, hogy Alekosz remek munkát végzett. Egyébként még nem választottam neki megfelelô nevet, bár több lehetôség is van. Tudnál segíteni a választásban?";
			link.l1 = "Természetesen segítek! Akárhogy is hívod a hajót, úgy fog repülni, nem igaz? Mik a lehetôségeid?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Eddig három lehetôség mellett döntöttem.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Az elsô lehetôség 'Phantom'. A fregatt gyors és erôs, és ezzel a névvel Havannától Cumanáig minden nyomorult megremeg a puszta említésére!";
			link.l1 = "Ja, és még meg is kell jelennie és eltûnnie a ködben, hogy a matrózok biztosan elkezdjenek keresztelkedni, ha-ha! Jó név, tetszik.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Nekem is tetszik. A második lehetôség 'Cápa'. És mi? Miért nem adok a hajómnak saját becenevet? Legyünk névrokonok vele, ha!";
			link.l1 = "Van egy cápa a 'Shark'... Ironikus. De mindenki pontosan tudni fogja, hogy kié a hajó.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Itt én is körülbelül ugyanígy vagyok. És a harmadik lehetôség 'Flurry'. Hogy mindenki féljen még a hajóm közelébe is menni, ha ha ha ha!";
			link.l1 = "Mert oldalról bele lehet futni egy flurry golyóba? És mi, nem rossz.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Pontosan! De most nem tudok dönteni a három név között. Szóval gyerünk, segítsetek! Ahogy akarod.";
			link.l1 = "Javaslom, nevezd el 'Phantom'. Aztán az összes kereskedô kidobja a fehér zászlót, amint meglát a horizonton!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "Tetszik a név 'Cápa'. Mindenkinek tudnia kell, hogy a hajó nem valami újonc, hanem maga a Parti Testvériség feje!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "Szerintem 'Flurry' jó név. Minden harcosnak, magántulajdonosnak vagy kereskedônek tudnia kell, mi fog történni, ha úgy dönt, hogy harcba száll ezzel a hajóval.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "Nézzétek - még a hadsereg is elkezdi ugyanezt csinálni, ha! Szóval, ez eldôlt. Fogd meg a bögrét, barátom. Igyunk az új hajómra. For 'Phantom!'";
			link.l1 = " For 'Phantom!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "És gondolják meg háromszor, mielôtt keresztezik az utamat! Szóval, eldôlt. Fogd meg a bögrét, barátom. Igyunk az új hajómra. For 'Shark'!";
			link.l1 = "For 'Shark'!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "És ha mégis úgy dönt, akkor olyan zivatar fogja elborítani, hogy a trópusi viharok könnyû szellônek fognak tûnni! Tehát eldôlt. Fogd meg a bögrét, barátom. Igyunk az új hajómra. For 'Flurry!'";
			link.l1 = "For 'Flurry!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "És szolgáljon ez a hajó hûségesen, és ne ismerje a vereség keserûségét! Nos, térjünk a lényegre.";
			link.l1 = "Figyelmesen hallgatlak.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Mondd csak, Charles, tudod, mi az az Aranyflotta?";
			link.l1 = "Kha-kha! ...már megfulladtam a rumtól. Steven, ne mondd, hogy két fregatton rabolod ki a Karib-tenger legjobban felfegyverzett konvoját.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "Nos, nem, persze, nem vagyok öngyilkos. Biztosan nem fogjuk kirabolni az egész konvojt. De itt tudunk valamit elcsenni onnan.";
			link.l1 = "Steven, természetesen sajnálom, de erre még nem állok készen. Igen, a spanyolok élve elégetnek minket, ha a flottájukba keveredünk! Gyertek nélkülem.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "Rendben, ha nem tûnünk el... Készen állok a részvételre!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Áááá! Kár érte. Túl kockázatos lenne nélküled. Rendben, most nem fogok gyôzködni, de gondolkodj rajta, rendben? Ha valaha is úgy döntesz, hogy megteszed, kérlek, szólj nekem.";
			link.l1 = "Ha én, akkor persze. Sajnálom, Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Az ilyen vállalkozások nem adják fel! Nos, mi a helyzet veled? Talán meggondoltad magad?";
			link.l1 = "Nem, barátom, sajnálom, de még mindig passzolok.";
			link.l1.go = "exit";
			link.l2 = "Rendben, ha nem tûnünk el... Készen állok a részvételre!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Lehet, hogy te készen állsz, de a hajód nem. Mondtam, hogy gyere 'Fortune'. Nem tudom, hol hagytad, de túl kockázatos lenne ilyen kockázatot vállalni egy másik hajón. Úgyhogy azon a hajón várlak, amelyen megállapodtunk. És ne feszítsd túl a húrt.";
				link.l1 = "A francba, teljesen elfelejtettem, bunkó! Várj: a megfelelô hajón jövök vissza.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "De nem: te még nem állsz készen, Charles. Mondtam, hogy század nélkül jöjjön. Abban az esetben, amit veled akarok csinálni, extra hajókra biztosan nincs szükség. Mozdítsd el a flottádat valahová, és gyere vissza.";
				link.l1 = "Igen, teljesen elfelejtettem. Várj: nemsokára visszajövök század nélkül.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ezer ördög, pontosan ezt akartam hallani! Szóval, azt javaslom, hogy te és én ragadjunk el egy darabot a konvojból. Rengeteg zsákmány...";
			link.l1 = "Úgy érted, elrabolni? Anélkül, hogy elkapnának az ôrhajók?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Pontosan. Nézze, mint valószínûleg tudja, az 'aranyflotta' Porto Bellóban gyülekezik, majd onnan Havannába megy. Havanna után már felesleges elfogni: olyan ôrséggel megy át az Atlanti-óceánon Spanyolországba, hogy csak egy komplett kretén dugja rá a fejét. A Porto Bellóból Havannába való átmenet idején sem sokkal jobb a helyzet. Persze megpróbálhatod, de ehhez össze kell állítanod egy olyan századot, amely képes akár diónyi erôdöket is feltörni. Porto Bellóban azonban Maine egész területérôl gyûlnek össze a hajók, és ott már nem különösebben védettek.";
			link.l1 = "Csak most az átmenet ideje és az ilyen hajók nevei szigorúan titkosak. Nem fogunk valahol Porto Bello környékén lógni fél évig, és elfogni az összes spanyol hajót, amelyik a kikötôbe tart.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Természetesen nem fogjuk. Cartagenából például maguktól mennek a hajók, és ahogy ön helyesen megjegyezte, csak Isten tudja, hogy milyen hajókról van szó, és hogy mikor indulnak. De Caracasból, amely mellett egy spanyol bánya van, és amely Porto Bellótól elég messze van, a hajók nem teljesen egyedül mennek.";
			link.l1 = "Hogyhogy nem teljesen egyedül?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "Azt sikerült megtudnom, hogy egy áruval megrakott hajó egyedül vagy egy kis ôrséggel hagyja el Caracast, de valahol a Maracaibo-öböl hosszában spanyol hadihajók találkoznak vele, hogy gondoskodjanak a további biztonságáról. Mit gondolsz, honnan tudják, hogy mikor és kivel kell ott találkozniuk?";
			link.l1 = "Biztosan mondtak nekik valamit...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "Jól van. Mielôtt a fôhajó elindul, egy futárhajó megy Caracasból Porto Bellóba, és jelenti a találkozó helyét és idôpontját, valamint a spanyol hajó nevét. Aztán visszamegy, és megerôsítést visz, hogy a hajóval a megfelelô idôben és a megfelelô helyen találkoznak. Csak ezt követôen, a célunk Önnel együtt kerül elôre Caracasból.";
			link.l1 = "De ha a futárt elfogjuk, akkor a hajó Caracasban nem kap visszaigazolást, és nem hagyja el a kikötôt. Van valami ötlete ezzel kapcsolatban? Különben is, hogyan fogjuk elkapni magát a futárt? Azt sem tudjuk, hogy mikor indul el.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "És itt van egy kis bökkenô. A spanyolok természetesen futárszállító luggereket használnak ilyen célokra, de ez kockázatos: túl nagy az esélye, hogy az elsô ellenkalóz elfogja ôket. Így aztán sokáig várhatnak a hajó elküldésével. Ezért, ha van rá lehetôség, akkor jó erôs, de nagy sebességû hajókkal együtt továbbítják az utasításokat - például kereskedôk, vagy a megfelelô útvonalon haladó magánhajók. \ncsak úgy, mint egy lezárt levél. Ráadásul sokkal olcsóbb, mintha külön futárhajót, akár egy luggert küldenének. És a kapzsi spanyol hivatalnokok szeretnek spórolni, miközben valamit a zsebükbe tesznek, hehe.";
			link.l1 = "Azt hiszem, megértettem! Kell nekem ilyen kereskedônek lennem?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Pontosan! És szerencsénk volt: egy megbízható forrásból sikerült megtudnom, hogy Caracasban most keresnek egy ilyen futárt, hogy a következô három hétben elküldjék neki egy levéllel. És csak egy erôs és gyors hajójuk van, ráadásul a spanyolok építették! Szerezzen GVIK-engedélyt, a nagyobb hihetôség kedvéért - egyszerre hat hónapra, vásároljon Caracasban annyi árut, hogy Porto Bellóban nyereségesen továbbértékesíthesse, aztán menjen el a kikötôi hatóság helyi vezetôjéhez, és kérdezze meg, hogy kell-e valamit vinni az útra. \nHa a kikötôi hatóság kérdezi, mutatkozz be spanyolként. És igen - eszedbe ne jusson egy századot is magaddal hurcolni. Nem kell túl nagy feltûnést keltenünk, különben az egész vállalkozás fedezékbe kerülhet.";
			link.l1 = "És a dokumentumokból, amelyeket átadnak nekem, megtudom a hajó és a konvoj találkozásának idôpontját és helyét?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "Nem is olyan egyszerû. Én mondom: az iratok le vannak pecsételve. És maga nem nyithatja ki ôket. A Porto Bello-i kikötôi hatóságnál fogják felbontani ôket, aztán írni fognak egy választ, és ha leszel olyan kedves, és azt mondod, hogy visszamész Caracasba, akkor megkérnek, hogy vidd oda. A választ természetesen szintén lepecsételik.";
			link.l1 = "És akkor hogyan tudom meg a találkozó helyét és idôpontját?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "Okosnak kell lenni és valahogy kikukucskálni ... Például abban a pillanatban, amikor Porto Bellóban felbontják az iratokat, és megírják a választ. Vagy csak ellopni ôket, amikor átadják a visszaigazolást, amit Caracasba kell vinni. De ez nem jó megoldás: ezután minden elromolhat.";
			link.l1 = "Ez persze nehéz ... De azt hiszem, meg tudom oldani.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "Én viszont elviszem a hajómat Marcustól, és Curacao Santa Maria-fokánál horgonyozva várom önt. Ha végeztél, csak gyere hozzám. A megadott koordinátáknál elfogjuk a hajót, és azonnal lerakjuk onnan a fenébe. Most már érted, miért van szükség a hajókra, amelyek erôsek, de gyorsak? Egyáltalán nem akarok harcolni a spanyol katonai századdal. El kell távolodni tôlük.";
			link.l1 = "Értsd meg. Nos, akkor én elmegyek. Találkozzunk a Santa Maria-foknál!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "Így van, ott találkozunk. Sok szerencsét, barátom! Remélem, az üzletünk jól megy.";
			link.l1 = "Én is remélem. Mindenesetre, én megyek.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Felfedezô mód: az idôzítô ki van kapcsolva.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Átkozott Charles! Azt hittem, soha többé nem látlak! Hol voltál? Vártalak a megbeszélt helyen, de nem jöttem. És nem kaptam hírt felôled.";
			link.l1 = "Sajnálom, Steven. Nem tudtam elvégezni a feladatomat.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Eh, egy ilyen halat kihagytak... Rendben, ne légy ideges. Legközelebb több szerencsét.";
			link.l1 = "Remélem.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", Mi a fene? Mondtam neked, hogy maradj század nélkül! Értsd meg: nincs szükségünk ballasztra, különben az egész mûvelet kudarcot vallhat! Nem tudom, mi ütött beléd, de ez így nem fog menni. Sürgôsen küldjétek el a karavánotokat valahová, és egy hajóval térjetek vissza. Én itt várok rád.";
				link.l1 = "Igen, csak azt gondoltam, hogy ez valószínûbb... Rendben, megértelek. Várj itt: Mindjárt jövök!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", mi a fene? Mondtam, hogy legyél a 'Fortune'! Érted: két gyors és erôs hajóra van szükségünk, különben az egész mûvelet kudarcba fulladhat! Nem tudom, mi ütött beléd, de ez így nem fog menni. Sürgôsen változtassa meg a vályúját 'Fortune' és jöjjön vissza. Várlak itt téged.";
				link.l1 = "Igen, csak gondoltam, hogy ez a hajó jobb... Rendben, megértelek. Várj itt: Mindjárt jövök!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "És itt vagy, barátom! Nos, hogy tetszik a jóképûm?";
			link.l1 = "Gyönyörû fregatt, Steven! Ezt nem utasítanám vissza...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "Nem, most már 'Fortune', haha! Meséld el, hogy ment!";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Minden hibátlanul ment: Sikerült egy becsületes és megbízható kereskedônek kiadnom magam. Elvittem a dokumentumokat Porto Bellóba, ahol sikerült öt percre elterelnem a kikötôi hatóság helyi vezetôjének figyelmét, és átírnom magamnak a rakományt szállító hajók és a katonai század találkozásának idôpontját és koordinátáit.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "Voltak kisebb bonyodalmak. A levelet futárral küldték el Porto Bellóba. Én elfogtam, átadtam a címzettnek, sôt választ is kaptam, de a kikötôi hatóság vezetôje kitalálta, hogy nem én voltam az, akinek a dokumentumokat kellett volna hoznia. Harcosan kellett kitörnöm onnan. De kiderítettem a rakományt szállító hajó és a katonai század találkozásának idôpontját és koordinátáit, és a választ Caracasba szállítottam, így a produkció vár ránk!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Várj egy percet. Azt mondtad 'ships'?";
			link.l1 = "Igen, Cápa! Kettô lesz belôlük!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ha-ha-ha, igen, megütjük a fônyereményt! Nos, a fenevadam készen áll a tûzkeresztségre. De még nem vett részt a csatákban, úgyhogy vezessük a csatát. Egyelôre pedig csatlakozom a századodhoz.";
			link.l1 = "Magának Steven Dodsonnak, a Parti Testvérek vezetôjének kell parancsolnom? Az üzletben!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Nos, ne légy túlságosan arrogáns: csak azért, mert most elôször fogok a hajómon harcolni. És gondoskodjatok a díjhajók szabad tisztjeinek elérhetôségérôl. Mert a rakterük tele lesz, és a csapatomból senki sem lesz képes egyedül irányítani a hajót ... Rendben, elég a nyelvvakarásból. A zsákmány vár ránk!";
			link.l1 = "Pontosan! Megyek a hajómra.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Igen, megörökölted... Akkor fel kell készülnünk arra, hogy a század a megbeszélt idôpont elôtt odaér, és mindenkivel egyszerre kell majd harcolnunk.";
			link.l1 = "Miért mondod ezt?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "És te agyalsz. Porto Bellóban tudják, hogy a hajó a rakománnyal biztosan el fogja hagyni Caracast, mert oda vitted a válaszlevelet. De mivel elárultad magad, mindent elkövetnek, hogy megakadályozzák, hogy elfogjuk a hajót. Szerintem a század hamarabb fog odaérni. Én ezt tenném. Szóval, készüljünk fel egy kemény harcra. Késôn vonulunk vissza.";
			link.l1 = "Ne aggódjatok. Te és én két tengeri farkas vagyunk, mi nem mentünk át ezen!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "A te igazságod. Nos, a fenevadam készen áll a tûzkeresztségre. De még nem vett részt a harcokban, úgyhogy vezesd te a csatát. Addig is csatlakozom a századodhoz.";
			link.l1 = "Magának Stephen Dodsonnak, a Parti Testvérek vezetôjének parancsoljak? Az üzletben!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "Nincs idô csevegni, "+pchar.name+"! Gyerünk a zsákmányért!";
			link.l1 = "És a szerencse legyen velünk!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Ezer ördög! Szép munka, Charles! A zsákmány sokkal gazdagabbnak bizonyult, mint eredetileg gondoltam! Azt hiszem, ez az egész utazás mindenképpen megérte.";
				link.l1 = "Teljesen egyetértek veled Steven! A mai nap egyértelmûen a mi napunk!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "Szép munka, barátom. Bár be kell vallani, hogy sok zsákmányt vesztettünk.";
					link.l1 = "Egyetértek, Steven, jobban is csinálhatnánk. De ami van, az is jó!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "A francba! Olyan jó ötlet volt... És ennek eredményeképpen a kampány kiadásai több mint a nyereség. Charles, én adtam neked a parancsot, és te mindent elvesztettél!";
					link.l1 = "Ne mondj semmit... Én is rohadtul dühös vagyok. Mennyi préda kicsúszott a kezembôl!...";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Nos, mindketten jó munkát végeztünk. Én kitaláltam egy tervet, és megszereztem az információkat a futárról, te pedig zseniálisan megvalósítottad a tervet. És mindketten egyenlô feltételekkel harcoltunk a zsákmányunkért. Ezért javaslom, hogy a Parti Testvérek törvényei szerint osszuk fel: egyenlôen!";
			link.l1 = "Megcsináljuk!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Nos, most már megyek Isla Tesoro-ba. Meg kell javítanom a hajót, és rendesen meg kell mosnom az elsô sikeres utat az új hajómra. Sok szerencsét, barátom! Mindig örülök, ha látlak a rezidenciámon!";
			link.l1 = "Örülök, hogy az üzletünk ilyen nyereségesnek bizonyult. Egyszer biztosan meglátogatlak majd. Sok szerencsét!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "Rendben, tartsd meg magadnak. Ha egyáltalán maradt még valami. Nem érdekelnek ezek a kicsik. Végül is én vontalak bele ebbe az egészbe.";
			link.l1 = "Igen, az én hibám is... Sajnálom, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Ne kérj bocsánatot, még mindig az életemmel tartozom neked, és nem fogom elfelejteni. És most megyek Isla Tesoro-ba. Meg kell javítanunk a hajót és le kell mosnunk... Bár, mit is kell mosni... Sok szerencsét, haver! Mindig örülök, ha látlak a rezidenciámon!";
			link.l1 = "Rendben, bármi megtörténhet, vereségek is elôfordulnak. A lényeg, hogy életben vagyunk. Egyszer biztosan meglátogatlak, barátom! Sok szerencsét!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
