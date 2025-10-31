// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
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
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Üdvözöllek, Charles, az utazó! Már mindent hallottam arról, hogyan gyôzted le azokat a kalózokat Martinique keleti partjainál. Most már teljesen biztos vagyok benne, hogy nem tévedtem veled kapcsolatban, testvér.";
				link.l1 = "A rohadékok csapdába csaltak. De alábecsültek minket. A navigátorom, a legénységem és én kerültünk ki gyôztesen. Bár be kell vallanom, kedves testvérem, az elején... a dolgok homályosan néztek ki.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Üdvözletem, testvér! Értékelem az ôszinte buzgalmadat, hogy kijuttatsz innen, de még nem állsz készen a következô lépésre. A tervem egy tapasztalt kapitányt kíván. Folytasd a Karib-tenger felfedezését, keress díjakat és tanulj! Ha készen állsz, folytatjuk.";
						link.l1 = "Nos, ahogy gondolod, testvér. Te ülsz itt, nem én.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Örülök, hogy látlak, testvér. Ne feledkezz meg a mások iránti elkötelezettségedrôl. Amint szabad leszel, várlak - vannak ötleteim a következô lépésünkre!";
						link.l1 = "Értettem, testvér. Szükségem lesz egy kis idôre a kötelezettségeim miatt, de hamarosan visszajövök!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("12. szint szükséges");
					dialog.text = "Károly, a navigátor! Hallottam a kalandjaidról! Már majdnem készen állsz tervem következô szakaszára. Gyere vissza, amint újabb tapasztalatokat szereztél.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Üdvözletem, testvér! Értékelem az ôszinte buzgalmadat, hogy kijuttatsz innen, de még nem állsz készen a következô lépésre. A tervem egy tapasztalt kapitányt kíván. Folytasd a Karib-tenger felfedezését, keress díjakat és tanulj! Ha készen állsz, folytatjuk.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Jó látni téged, testvér! Hallottam, hogy haladsz! De még nem állsz készen a tervem következô lépésére. Folytasd, amit eddig is csináltál, és gyere vissza hozzám, ha készen állsz.";
						}
					}
					link.l1 = "Nos, ahogy gondolod, testvér. Te ülsz itt, nem én.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "Nem hiszem, testvér. Talán már belaktad magad ebbe a ketrecbe, de nem szándékozom sokáig itt maradni - apánk nem várhat örökké. Köpd ki.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "Jó napot, Charles. A látványod örömöt hoz a szívembe: határozottan jó irányba változol.";
					link.l1 = "Valóban? És ezt hogy gondolod?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "Értem. Látom, hogy híreid vannak számomra, Charles! Nos, mi a helyzet? Remélhetôleg semmi rosszat?";
				link.l1 = "Követtem a tanácsot, amit legutóbb adtál...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Végre itt vagy... Mi a helyzet, kedves testvér?";
				link.l1 = "Követtem a tanácsot, amit legutóbb adtál...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Örülök, hogy látlak, Charles! Láttad Chevalier de Poincy-t? Hogy ment a találkozó?";
				link.l1 = "Igen, kedves bátyám. Találkoztunk. És két jó és két rossz hírem van számodra. Kezdem a jóval. Elintéztem az adósságodat de Poincy felé. A rossz hír az, hogy nem enged el, amíg nem teljesítem az ígéretedet, hogy elrendezed a dolgokat valami eretnekkel...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "Hogy ment La Vegában, testvér?";
				link.l1 = "Nincs mivel dicsekedni, tényleg. Tyrex egy színes egyéniség, de az üzleti modora nem nekem való.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "Hogy ment La Vegában, testvér? Hallottam pletykákat, és hogy teljesen ôszinte legyek, nem örülök nekik... Charlie Prince.";
				link.l1 = "Azt hiszem, tudom, mirôl szóltak ezek a pletykák. De ez már a múlté. Nem dolgozom többé a Tyrexszel, ez a munka egyszerûen túl mocskos lett az ízlésemnek.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Nos, üdvözletem... Charlie Prince korzikai herceg. Mondd csak, Károly, hogy süllyedtél ilyen mélyre? Ezt nem hiszem el. A bátyám, aki finnyás arcot vágott, amikor egyszer megemlítettem egy spanyol kereskedelmi gálya kifosztását, most az egyik legkeresettebb és legveszélyesebb kalóz a térségben! Még én is, aki mélyen a szarban ülök, elvörösödöm, valahányszor a gyalázatod eljut a fülemig. Megátkoztam azt a napot, amikor La Vegába küldtelek. Micsoda szégyen! Egy francia nemes csatlakozott a kalózokhoz, és ilyen rövid idô alatt mind közül a legrosszabbá vált! Most mi lesz, testvér? A kalózbáró állását keresed?";
				link.l1 = "Nem. Én egyszer és mindenkorra végeztem a kalózkodással.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "Mi mást, Charles? Azt hiszem, már mindent megbeszéltünk. Az idô pénz, kedves testvér - siess!";
			link.l1 = "Igen, igen, indulok...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles! Örülök, hogy látlak, testvér! Megértem, persze, hogy nehéz lesz elhinned, de pokolian örülök, hogy itt vagy...";
			link.l1 = "Ha! Nézzétek! Boldog! Szóval amíg te a magas lóról ültél a 'Orden', Károly a család szégyene volt, egy hitvány mûvész, aki kurtizánok pénzébôl élt, és udvari 'lovag', huh? De most, hogy a saját elvtársai rács mögé csaptak, te 'boldog vagy, mint a pokol' , hogy láthatod a semmirekellô bátyádat!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, te...";
			link.l1 = "Még nem végeztem! Miért jelentettél magadról bármit is Franciaországnak?! Megfosztottak a levelezés jogától?! Apánk teljesen megbetegedett a miattad való aggodalomtól! És megkért, hogy legalább valamit tudjak meg a sorsodról!";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, milyen szavakkal mondjam el az apjának, hogy mi történt velem? Mit írnék neki? Nem, testvér, bármennyire is nehéz, jobb, ha apánk még nem tud semmit. Neked pedig felesleges lenne írni - te mindig más-más címen vagy Párizsban... Hogy találtál rám?";
			link.l1 = "Az apa kérésére elmentem Máltára. Ott kaptam némi információt az ön barátjától, chevalier de La Brignais-tól. Ô írt nekem a problémáidról, és arról, hogy valószínûleg valahol Martinique-on vagy. Aztán visszatértem Franciaországba, és meglátogattam az apát. És mindezek után elmentem ebbe a pokoli forróságban, ahol a szúnyogok szó szerint halálra rágják az embert...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Elmondtad mindezt az apának?";
			link.l1 = "Nem. És a chevalier de La Brignais nem válaszolt a leveleire, félve a szomorú következményektôl... Az apja még mindig nem tud semmit a sorsáról. Elhatároztam, hogy megkeresem önt, és a dolgok gyökeréig eljutok. Csak hogy tudd, nem miattad jöttem Martinique-ra, hanem szegény apánk miatt!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Tényleg? Charles, mióta törôdsz a családoddal? Legyünk ôszinték, testvér, Párizsban mindenki tudja, ki az apád. Lehet, hogy a de Maure családnevet viseled, de nem akarod, hogy a de Monper' név becstelen legyen.\nMert ebben az esetben nem tudnád felhasználni a származásodat arra, hogy mindenkinek kitalált történeteket mesélj a hôstetteidrôl, igazam van? Párizs legjobb házainak ajtajai bezárulnak elôtted, és nem engednek közelebb egy mérföldnél közelebb a Louvre-hoz.\nTényleg azt hiszed, hogy az udvarhölgyeid és szeretôid, akiknek férjeidet felszarvaztad, miközben azok a csatatéren harcolnak a hazánkért, örömmel csalják meg uraikat és uraikat egy olyan állami bûnözô testvérével, mint én?.\nGondolom, egyenesen valami férjes asszony ágyából érkeztél ide, igazam van? Charles, mi a baj az arcoddal? Talán eltaláltam az idegeidet?";
			link.l1 = "Te... Te...";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "Rendben, testvér. Elég volt a szurkálódásokból, ennyi elég. Egyetértek, hogy nem vagyok tökéletes. De te sem vagy egy angyal. Charles, ez tényleg nem a veszekedés ideje. Mindkettônknek ugyanaz a célja, hogy megmentsük a Monper család becsületét és méltóságát... függetlenül attól, hogy mik az indítékaink. Testvér, egyszer az életben cseréljük fel az ellenségeskedést békére. Megegyeztünk?";
			link.l1 = "Próbáljuk ki... De el tudod magyarázni, hogy mivel vádolnak?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Hivatalosan úgy hangzik, mintha a Társaság pénzének elköltésérôl lenne szó. A valóságban ez sokkal mélyebb.";
			link.l1 = "Szóval, ön kisajátította a szervezet pénzét? Nos, nos...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "Mondtam, hogy ezek a hivatalos vádak. Nem vettem el egyetlen louis d'or-t sem. Elmondom, hogyan történt... Tudod, nem tudok mindent részletesen elmagyarázni, amíg rács mögött vagyok. Nincs erkölcsi jogom ahhoz, hogy kiteregessem a Társaságunk titkait.";
			link.l1 = "Kérlek, próbáld meg elmagyarázni, kedves testvér. Jogom van tudni, nem gondolod?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "Jól van. Pénzt kaptam egy nagyon veszélyes és kényes mûveletre, amelynek a karibi térség politikai egyensúlyát kellett volna megváltoztatnia. Philippe de Poincy közvetlen parancsára cselekedtem, ô a francia gyarmatok fôkormányzója. De a mûvelet minden erôfeszítésem ellenére kudarcot vallott.\nDe Poincy dührohamot kapott, mert minden hosszúra nyúlt terve a levegôbe repült. Személyesen írta alá a letartóztatási parancsomat, és gondoskodott annak végrehajtásáról. Ezután idejött, és kijelentette, hogy megvádol a rend elleni csalással és árulással, ha a rokonaim vagy én nem adjuk vissza a mûveletre költött pénzt.";
			link.l1 = "Itt van egy szép kis hogyishívják. Hol van az a pénz, amit, ha jól tudom, a családunknak kell fizetnie a muffjaidért?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "A mûtét elôkészítésére költöttük. Megvesztegetések, expedíciók szervezése, mindenféle áru és felszerelés beszerzése. Elég nagy kiadásaim voltak. Ahogy mondtam - egy fillért sem vettem el.";
			link.l1 = "És mi az az összeg, amit követelnek?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "Egymilliót.";
			link.l1 = "Merde! Ugye csak viccelsz?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Úgy nézek ki, mint aki viccelôdik? Nem, kedves testvér, ez a keserû igazság. Egymillió pezót kell átadnunk de Poincy-nak.";
			link.l1 = "De az istenit! A mi családunknak közel sincs ennyi pénze! Húsz év alatt sem tudnánk ennyit összeszedni!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "Ha nem lennék rács mögött, és nem korlátoznának a Társasággal szembeni kötelezettségeim, hat hónap, legfeljebb másfél év alatt megtenném. Charles, ez az Új Világ. Itt minden más. Egy motivált, ambiciózus ember itt meggazdagodhat anélkül, hogy egész életét ennek szentelné, mint Európában.";
			link.l1 = "Egy millió fél év alatt?! Megôrültél? Ha ilyen biztos vagy benne, akkor miért nem mondod el ezt a te de Poincy-dnak? Hadd engedje el magát. Tegye a legjobb formáját...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Ó, ne beszélj hülyeségeket, Charles! Kizárt, hogy Poincy kiengedjen ebbôl a cellából. Ha ilyen egyszerû lenne, nem kérném a segítségedet.";
			link.l1 = "Szóval nekem kell elôteremtenem a pénzt a szabadságodért?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Nem csak a szabadságomat. Vagy elfelejtetted? Térjünk vissza a palotákról, bálokról és a nemesi szajhákkal való szexrôl szóló beszélgetésünkhöz? Igen, Charles, te vagy az, akinek ezt meg kell tennie. Persze csak ha továbbra is folytatni akarod a párizsi meretricitás életedet, mint eddig. Ezt szeretnéd, ugye, testvér?";
			link.l1 = "De az isten verje meg, honnan a fenébôl szerezzem meg?! Ismer errefelé valami öreg erdôt, ahol lomb helyett lúzerek nônek?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "Az egész Újvilág a pénzfák ligetét jelenti, de az emberek túl lusták ahhoz, hogy felemeljék buta fejüket, és kinyújtsák kezüket az ágak felé. Ne aggódj, Charles, minden rendben lesz. Gyermekkorunk óta ismerlek, és soha nem vesztegettem volna az idômet arra, hogy rábeszéljem apánkat, hogy küldjön ide, ha azt gondolnám, hogy buta vagy lusta vagy.\nA korábban említett hátrányaid ellenére bátor vagy, ambiciózus, okos, a nyelved elég jól lóg, és tudsz bánni a pengével, ami itt rendkívül fontos képesség...";
			link.l1 = "Köszönöm szépen. Kedves bátyám valóban méltóztatott dicsérni engem? És én még azt hittem, hogy csak egy szánalmas mûvész vagyok, egy udvaronc...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Hagyd a hülyeséget. Megegyeztünk, vagy sem?";
			link.l1 = "Sajnálom, bátyám. Kicsúszott a számon. Csak már annyira nem szoktam tôled hallani ezeket a szavakat. Mintha egy utcai kurva prédikálna a lélek megmentésérôl.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Folytassuk, testvér. Ahogy mondtam, mindened megvan ahhoz, hogy sikeres legyél itt. Nem csak az, hogy nem vagy egyedül. Segítek neked tanácsokkal, hogy mit és hogyan csináld helyesen. Hallgass rám, és máris repülünk. Hidd el, nem fogsz találni senkit, aki az én tapasztalatomat pótolná. Készen állsz arra, hogy visszatartsd a szemétkedést, és végre a lényegre térj?";
			link.l1 = "Igen, úgy néz ki, hogy itt maradok egy darabig... Jól van, rendben. Csupa fül vagyok, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Igen, testvér, itt fogsz maradni egy ideig. Jó, hogy ezt most már látod. Ha tehát valami udvarhölgy várja, hogy visszatérj Párizsba, azt javaslom, felejtsd el ôt. De ne érezd magad rosszul emiatt, a helyi lányoknak megvan a maguk bája.\nAz igazi férfiakat szeretik, az erôs és rámenôs, sôt durva férfiakat. Szóval ha valami gyarmati lányt akarsz megdugni, ne számíts költészetre, festményekrôl való beszélgetésekre vagy a Hold alatti sétákra. Nem fogják jóváhagyni.";
			link.l1 = "Rendben, testvér. Megcsapott a szélhámosság villáma? Térjünk a lényegre. Hajlandó vagyok meghallgatni a tanácsait, de nem a csúnya célozgatásait.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Nagyszerû. Ahhoz, hogy sikerrel járjon, szüksége van egy hajóra. A Karib-tenger egy szigetcsoport. Ezt ugye tudja? Az élet összefonódik a tengerrel. Akinek saját hajója van, annak a kereseti lehetôségei végtelenek.";
			link.l1 = "De én nem vagyok tengerész!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "Akkor itt az ideje, hogy azzá válj. Úgysincs más választásod. Ugye nem gondoltál arra, hogy kikötôi hivatalnok leszel, vagy hogy a helyôrségnél jelentkezel? Nem? Akkor kapitány leszel.";
			link.l1 = "Micsoda fordulat a karrieremben! És hol találok majd magamnak hajót?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "A helyi hajógyárunkban vár egy kiváló hajó. Nem nagy, de nagyon kényelmes hajó, éppen alkalmas arra, hogy megtegye az elsô lépéseket a vitorlázás terén. Ezt a luggert csak nekem építették. Ötezer pezó elôleget tettem le a hajóra a barátaim segítségével. Menjen el a hajóépítôhöz, és mondja meg neki, hogy Michel de Monper küldte. Meg fogja érteni, hogy miért van ott.";
			link.l1 = "A hajó csak ötezerbe kerül? Ez elég furcsa...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Testvér, figyelsz rám? Ötezer csak a foglaló. A hajó ára húszezer pezó körül van. Szóval a többi pénzt neked kell megkeresned. Ezen kívül szükséged lesz pénzre, hogy felvegyél egy legénységet és egy navigátort.";
			link.l1 = "Nagyszerû! És hogy fogom megszerezni?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Ebben nincs nagy meglepetés. Megkeresed. Hogyan máshogy? A pénz itt minden bokor mögött megtalálható, csak tudni kell, hol keressük, és nem kell félni a viszontagságoktól. Sétáljon körbe a különbözô itteni létesítményekben. Beszélgessen a helyiekkel. Biztosan találsz majd valamilyen munkát. De légy óvatos, sokkal több a szélhámos, mint a becsületes ember. Ha nem vagy becsületes ember, megpróbálhatsz ellopni valami értékeset a házakból.";
			link.l1 = "De hát mi nemesek vagyunk, nem igaz?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "A címek itt szart sem jelentenek. Dolgozz, harcolj, lopj, mint mindenki más. Miután vettél egy hajót, vegyél fel egy legénységet. Kezdetben nem fogod tudni egyedül kormányozni a hajót, ezért szükséged lesz egy navigátorra. Mindezt megbeszélheted a kocsma tulajdonosával, ô majd segít neked. És persze ügyel arra, hogy ne tévedj el. Amikor elindultok a tengerre, egyenesen Guadalupe felé vessétek a vitorlákat...";
			link.l1 = "Az meg mi? Egy város?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "Ez egy sziget, majdnem két napra innen. Próbálj meg minél elôbb beszerezni egy szigetvilágtérképet, és tanulj meg úgy, mint a 'Isten imája' , hogy ne nézzenek hülyének mindenki elôtt, aki meg tudja különböztetni a várost a szigettôl. Sokat kell majd vitorláznod a szigetvilágban, úgyhogy készülj fel elôre.";
			link.l1 = "Hm. Rendben. Szóval mit csináljak ezen a... Guadeloupe-on?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Keressetek ott egy férfit, akit úgy hívnak 'Fadey'. Neki saját háza van nem messze a mólótól. Mondd meg neki, hogy ismersz engem, és kérd meg, hogy fizesse vissza az adósságát - egy kártyapartiban elég nagyot bukott velem szemben. A kapott pénz segít majd talpra állni. Használd fel, hogy beindítsd a dolgokat.";
			link.l1 = "Hogy érti azt, hogy beindítani a dolgokat?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "Úgy értem, hogy ezt a pénzt még több pénz keresésére használd fel, és így tovább. Például kereskedéssel. Erre a beszélgetésre késôbb még visszatérünk. Most a hajóval kellene foglalkoznod, elhajózni Guadeloupe-ra, megkeresni azt a kövér moszkovitát, és kiverni belôle az adósságot.\nNem szó szerint persze, Fadey nagyon tekintélyes ember Guadeloupe-on, és magának a helyi kormányzónak a barátja. Szóval nincs értelme veszekedni. Épp ellenkezôleg, próbáljatok meg összebarátkozni vele. Amint megvan a pénz, jelentkezzen, amint megvan a pénz. Megértetted, testvér?";
			link.l1 = "Értettem. Ó, miért....Mivel érdemeltem ki ezt a büntetést...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Ne bánkódj, Charles. Fogadd el, mint elkerülhetetlen rosszat, vagy... mint jó dolgot. Késôbb hálás leszel a sorsnak, hogy az életed ilyen fordulatot vett. Neked, testvér, végre lehetôséged van arra, hogy bebizonyítsd, hogy igazi férfi vagy. Talán még tisztességes emberré is válhatsz...";
			link.l1 = "(ÚTMUTATÓ ÍNDÍTÁSA) Már megint ez a szarság?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(ÚTMUTATÓ KIHAGYÁSA) Testvér, erre nincs idôm. Szeretném kihagyni az unalmas részt, és azonnal nekivágni a nyílt tengereknek. Minél hamarabb lesz hajóm, annál hamarabb kijutsz ebbôl a szarfészekbôl. Vagy inkább tovább szeretnél itt maradni?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "Nem, nem, nem, nem, nem, nem, nem, nem, nem, nem, nem, nem, nem. Ne értsd félre... Rendben Charles, ne vesztegesd az idôt. Tudod, mit kell tenned. Várni foglak Guadeloupe-ról a saját hajód kapitányaként Fadey pénzével. Sok szerencsét, testvér. Számítok rád.";
			link.l1 = "Megpróbálok nem csalódni benned. Rendben, Michel. Viszlát legközelebb!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh! Ez 'unalmas rész' lehet, hogy egy nap megmenti az életed... Tökmindegy. Van egy egyszerû módja annak, hogy most azonnal hozzájuss a pénzhez.\nMenj el a helyi templomba, és beszélj Benoit apáttal. Ô apánk régi barátja. Mesélj neki a helyzetrôl, borulj térdre, és könyörögj, hogy adjon neked annyi érmét, hogy vehess egy hajót.";
			link.l1 = "(ÚTMUTATÓ KIHAGYÁSA) Most már sokkal jobb! Irány az apát úr.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(ÚTMUTATÓ ÍNDÍTÁSA) Szeretné, ha elkezdeném még magasabb szintre emelni az adósságát? Azt hiszed, hogy hülye vagyok, testvér? Látom, hogy ebben egyáltalán nem tudsz segíteni. Akkor ez az egész az én felelôsségem.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Hûha! Úgy tûnik, nem tévedtem veled kapcsolatban, testvér. Alig várom, hogy visszatérj Guadeloupe-ról, mint a saját hajód kapitánya Fadey pénzébôl. Isten éltessen!";
			link.l1 = "Viszlát. Jó szórakozást itt.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Azt akarod mondani, hogy ez ijesztô volt? Ne izgulj, testvér. Semmi baj. Én sem éreztem magam hôsnek az elsô tengeri csatámban. Ez badarság. Egy-két hónap múlva, az ilyen találkozások olyanok lesznek, mint egy hétköznapi vagy kerti esemény... Jártál már Fadeyben?";
			link.l1 = "Voltam... De ilyen sikerrel... Miért fáradoztam egyáltalán?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Miért van ez?";
			link.l1 = "Mert a sziklák között van. Nemrég kirabolták, és neki is vannak anyagi gondjai. Helyette felajánlott nekem egy tôrt a gyûjteményébôl. Azt mondta, hogy az értékes, és hogy az értéke nagyobb, mint az egész adósság összege. Így hát elfogadtam...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey? A sziklákon? Pénzproblémák? Ha-ha-ha-ha! Jót kuncogtam rajtad, kedves testvér! Az az istenverte moszkvai átlátott rajtad, és rögtön felismerte, hogy kezdô vagy, és... áh az a rohadék! Mutasd meg a tôrt, amit az öreg adott neked az adósságáért cserébe.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Tessék...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "Nincs nálam. Szabad szemmel csak egy átlagos tôr. Fadey azt mondta, hogy egy indián sámán varázsolta el, és úgy hívják, a fônök karma.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Nos, lássuk csak... Isten majd megítéli azt a pufók medvét. Ilyen ócskavasat, Charles, bármelyik helyi boltban megvehetsz. Kihasználva a tapasztalatlanságodat, átvert téged... Tessék, vidd vissza ezt az acéldarabot. Tartsd meg emlékbe. Felakaszthatod az ágyad fölé a kabinodban.";
			link.l1 = "A kurva anyád! Ó, kit érdekel... Visszamegyek hozzá Guadeloupe-ra, és megrázom ezt a zsíros perzselôt!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Elvarázsolta egy sámán? A fônök karma? Igen... minden tiszta. Isten majd megítéli azt a pufók medvét. Ilyen ócskavasat, Charles, bármelyik helyi boltban megvehetsz. Átvert téged, kihasználva a tapasztalatlanságodat... Megpróbált valami meséket mesélni nekem, de én visszavetettem a helyére. Szóval ezt a karmot felakaszthatod a kabinodban az ágyad fölé emlékbe... Ha még nem dobtad ki a kukába.";
			link.l1 = "A kurva anyád! Ó, kit érdekel... Visszamegyek hozzá Guadeloupe-ra, és megrázom ezt a zsíros perzselôt!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Nyugodj meg, kedves testvér, nyugodj meg. Erre semmi szükség, hacsak nem akarsz pár hónapot egy basse-terre-i börtöncellában tölteni. Elfelejtetted, amit mondtam neked? Az a pufók medve Claude Francois de Lyon, Guadeloupe kormányzójának a barátja. Amint elhagyom ezt a helyet, elmegyek hozzá beszélgetni... szívrôl szívre. Nem megy sehova.";
			link.l1 = "Nem megy sehova. Jobb, ha elintézed... Úgy néz ki, hogy az ígért induló pénz nélkül maradok?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Úgy tûnik, Charles. De tartsd fel a fejed. Akinek van hajója és feje a vállán, az nem tehet rosszat a Karib-tengeren. És neked mindkettô megvan, nem igaz?";
			link.l1 = "Mire célozgatsz? Elszúrtam ezt a tôrt, szóval mit kéne...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Nyugodj meg, kedves testvér! Miért vagy hirtelen ilyen ideges? Nyugodj meg, tovább fogsz élni. Nem célozgatok semmire. Nem is voltak ilyen gondolataim!";
			link.l1 = "Sajnálom, Michel. Csak egy kicsit... próbálj meg megérteni engem is!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "Megértem. És tényleg segíteni akarok neked! Úgyhogy figyelj jól. Szerezned kell némi tapasztalatot, és legalább egy kis pénzt meg kell spórolnod, mielôtt komolyabb dolgokba belevágsz. A szükséges felkészülés nélkül belevágni a kalandokba tiszta öngyilkosság. Nem akarom, hogy még most eltapossanak itt téged.";
			link.l1 = "Nagyon inspiráló. Miféle kalandokról mesélsz, Michel? Valamiért elvesztettem a fonalat a zagyvaságaiddal kapcsolatban.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Testvér, hadd emlékeztesselek, hogy én, pontosabban mi tartozunk de Poincy-nak egy millió pezóval. Tényleg azt hiszed, hogy becsületesen meg tudod keresni? Persze, lehet ennyit kereskedni, lehetséges, ha szerencsésen alakulnak a dolgok, de a kereskedelem a Karib-tengeren sem egy békés tevékenység.\nA kalandok akkor is megtalálnak téged, ha nem akarsz részt venni benne, a lényeg az - készen állsz-e rájuk, amikor eljön a pillanat? Jobb, ha elôbb lecsapsz. Si vis pacem, para bellum, Charles...";
			link.l1 = "Már megint a szép szavak? Beszélj franciául, könyörgöm...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Ez latinul van, kedves testvér. Azt mondtam, 'Ha békét akarsz, készülj fel a háborúra'. Vedd ezt a mondatot vezetôi mentalitásként a cselekvés felé. Leírhatod a naplódba, és minden reggel az ima után újraolvashatod. Sok mindent kell még megtanulnod, és sok minden van még hátra, amit meg kell ragadnod...";
			link.l1 = "Rendben, ennyi elég lesz. Már belefáradtam a tudományos dolgozataiba. Térjünk a lényegre.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "Konkrét vagyok, csak te még nem érted. Rendben. Elôször is meg kell ismerkedned a szigetvilággal, és hozzá kell szoknod az új életedhez, mint hajóskapitány. Keményen kell majd dolgoznod, hogy biztosítsd a jólétedet és a legénységed fizetését. Sokféleképpen lehet érmét keresni.\nA legegyszerûbb a teherszállítás és az utasok felvétele a fedélzetre. A kereskedôk a boltokban adhatnak neked fuvarszerzôdéseket, az utasok pedig maguk is megszólítanak az utcán. A kikötôi hivatalokat is érdemes megnézned, egy lugger vagy bármilyen gyors hajó birtokában jó pénzt kereshetsz futármunkával.\nA kikötômesterek nagyon jövedelmezô fuvarmegbízásokat adnak neked, ha egyszer beszereztél magadnak egy nagyobb hajót. Beszélgess az emberekkel, ne dicsekedj a származásoddal, légy barátságos, és a dolgok jól fognak menni. Látogass el a kolóniakormányzókhoz, gyakran kínálnak jól fizetô munkát.\nPróbálkozhatsz a kereskedelemmel, de ebben az esetben fel kell venned egy rendes pénztáros. Légy óvatos a tengeren, kerüld a spanyol katonai századokat és hadihajókat. Ha egyetlen spanyol kereskedôvel vagy egy védtelen konvojjal találkozol - megpróbálhatod elfogni ôket.";
			link.l1 = "Micsoda?! Michel, elvesztettem a hallásomat? Azt akarod mondani, hogy kezdjek kalózként élni? Te, a Társaság büszkesége, Isten és a Szentháromság szolgája, ilyen életmódot javasolsz nekem?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Ó, Charles... Azt tanácsolom, hogy egyszer és mindenkorra szabadulj meg az igényességedtôl, itt nem értékelik. És ami a rendet illeti... ne légy naiv, testvér. Lehet, hogy Európában a Louvre és az Escorial valamiféle békében van, de itt háború van. Bármelyik spanyol fosztogató nem habozna kifosztani a hajódat, és felakasztani téged és a legénységedet, hogy megszáradjatok egy hajógyárban.\nEzért senki sem fog hibáztatni, ha egy ellenséges nemzet kereskedelmi hajóját fosztogatod, biztosíthatlak róla. És egy sétahajólevéllel még hivatalos támogatást is kaptok a hatóságoktól...";
			link.l1 = "Kezdem megérteni az életed alapelveit. Ahogyan azt is megértem, hogy milyen módszerekkel lennél képes látszólag 'fél év alatt' milliót keresni.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "És ezeket a módszereket kell majd használnod, Charles. Végül is ezt az eljáró hatóságok nyíltan vagy zárt ajtók mögött támogatják. Még ha ragaszkodsz is a kereskedelemhez, egy nap kénytelen leszel kalózok vagy spanyol fosztogatók ellen harcolni, mert számukra te vagy a zsákmány.\nAz a legjobb, ha elfelejted a korábbi életszemléletedet. Hidd el, testvér, sok mindent megtehetsz anélkül, hogy elveszítenéd az arcodat, de a hatóságok' kedvét és az emberek szeretetét is kiérdemelheted.";
			link.l1 = "Michel, te mindig meg tudsz lepni engem. Most meg azt mondod, hogy legyek kalóz. Mi a következô lépés?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Ne dramatizáld túl ezt a dolgot, Charles. Ez tényleg egyszerû: vadászni vagy vadásznak rád. Ez az egész filozófia. Én inkább az elsôt választom, és szeretném, ha követnéd a példámat. És nem azt mondom, hogy válj kalózzá, hanem hogy vegyél részt katonai akcióban egy ellenséges nemzet ellen, és csak akkor, ha erre jó okod van.";
			link.l1 = "Úgy érti, hogy elônyös?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "Látod, te megérted, testvér. De elég a szavakból. Itt az ideje, hogy próbára tedd magad. Csak akkor gyere el hozzám, ha úgy érzed, készen állsz. Keress valami tisztességes pénzt, szerezz egy jobb hajót, ismerd meg a szigetvilágot, és fejleszd a képességeidet.\nDe vigyázz, ha a következô hónapokat kocsmákban és bordélyházakban töltöd, és közben semmi hasznosat nem tanulsz... akkor ne is térj vissza. Világos, Charles?";
			link.l1 = "Ne aggódjatok. Nem kikapcsolódni jöttem ide... Mi jön ezután?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Késôbb elmondom, hogy mit kell tenned ezután. Már összeállítottam egy tervet. Fényes jövô áll elôtted, Charles, ha pontosan követed a tanácsaimat és ajánlásaimat.";
			link.l1 = "Inkább a szerény múltamat választanám egy ilyen fényes, nagy jövôvel szemben...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Hidd el, testvér, nevetni fogsz az értéktelen múltadon, és megköszönöd a sorsnak, hogy megmentett tôle. Légy optimista és pozitív. Szeretni fogod ezt az életet. Meglátod.\nOh, még valami: látogasd meg közös barátunkat, Fadeyt, és kérd meg, hogy szerezzen neked munkát. A medvének jó kapcsolatai vannak, biztos vagyok benne, hogy talál neked valamit. Ne húzd az idôt, mert még lemaradsz a lehetôségrôl. És kérlek, ne hagyj cserben.";
			link.l1 = "Már megint erkölcsi tanítások... Uram, mikor lesz már vége ennek az egésznek? Rendben, Michel... Mehetek már?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Várjatok. Még néhány taktikai tanács. Ha átmész valamelyik országon, és törvényen kívülivé válsz, keresd fel a helyi templomot, és beszélj Benoit apáttal. Mondd meg neki, hogy én küldtelek. Vannak kapcsolatai mind a pápista, mind a kálvinista társadalomban, és nem egyszer segített már nekem ilyen ügyekben. De légy tisztában azzal, hogy ez nem könnyû és nem is olcsó, úgyhogy próbáld meg elkerülni, hogy ellenségeket szerezz magadnak.\nVárj, még egy dolog! Nemesek vagyunk, de bolondság, ha idegenkedünk a saját kezû kézmûvességtôl, fôleg itt. Rengeteg hasznos tárgyat lehet kézmûveskedni, feltéve, hogy megvannak a szükséges szerszámok és alkatrészek... Mondd csak, testvér, hogyan töltöd meg valamelyik pisztolyodat?";
			link.l1 = "Hm. Mint mindig, egy golyó és egy puskaporos csukló.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha! Nem is vártam, hogy mást hallok.";
			link.l1 = "Tudsz más módot, kedves testvér?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Hát persze. De kevesen vannak, akik tudatlanságból és egyszerû lustaságból teszik. Néhány órát áldozva az idôdbôl, puskaporból és töltényekbôl papírhüvelyeket készíthetnél. Használatuk felére csökkenti a fegyver újratöltési idejét. Lenyûgözött?";
			link.l1 = "Hm. Azt hiszem, igen. Ez érdekes.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Fogd ezeket a papírhüvelyek készítési utasításokat, tanulmányozd ôket szabadidôdben, és ne légy túl lusta alkalmazni az új tudásodat\Várj, testvér. Ne felejtsd el meglátogatni a mi kedves kormányzónkat.";
			link.l1 = "Van valami alkalom?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "Mindig jó, ha tartod a kapcsolatot a kormányzókkal, különösen, ha a rokonaidat a szigetükön tartják fogva.";
			link.l1 = "Mesélj róla.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Nem mindenki tarthatja meg Martinique trónját. A rend érdekei, a korona, a kalózok... és egy nemes nem feledkezhet meg a saját érdekeirôl sem. Ha Parkett nem lenne ennyire laza és bûnre csábító, még Poincy-t is rávehetné, hogy komolyan vegye ôt.";
			link.l1 = "És mi hasznom lenne belôlem?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "A hivatalnokoknak mindig van munkájuk az ingyen kapitányoknak. De takarékosan fizetnek, és csak akkor, ha közérdekrôl van szó, nem pedig személyes érdekekrôl. Mindenesetre a Karib-tengeren nincs jobb módja a becsület felemelésének és a nemzeti kapcsolatok javításának, mint a kormányzóknak dolgozni. Ragadják meg a pillanatot, különösen, mivel Parkett most éppen bajban van. Miféle bajba?";
			link.l1 = "Miféle baj?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "Sajnálom, testvér. A Rend érdekei is érintettek. Csak annyit mondok, hogy nem csak nekünk van szükségünk a gyors meggazdagodásra.";
			link.l1 = "Már megint rejtélyes vagy... Nos, majd beugrom, ha lesz idôm.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Most menj. Sok szerencsét, testvér!";
			link.l1 = "Köszönöm... Viszlát késôbb, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			DialogExit();
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Sharlie_Mishelle_OpenWorld");
		break;
		
		case "gambitA":
			dialog.text = "Ahogy akarod. Hiszek benned, testvér. Amikor most rád nézek, tudom, hogy a jobbik irányba változol.";
			link.l1 = "Nem mondod. Hogyhogy?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "Látom, kedves testvér. Látom a járásodat és az arckifejezésedet. Végre leolvadt rólad a beképzelt kisfiú álarca, amely szó szerint az ôrületbe kergetett. Az új életed mostanra egyértelmûen jót tett neked.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Nem értem, testvérem, mit kezdjek a szavaiddal, legyen az dicséret vagy sértés. De megmondom az igazat: nem érdekel, mit gondolsz rólam odaátról. Összegyûjtöttem azt a milliót, ami ahhoz szükséges, hogy kifizessem az adósságodat, így hamarosan szabadon sétálhatsz. Hol találom de Poincy-t?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "Nem értem, testvér, mit kezdjek a szavaiddal, akár dicséret, akár sértés. De megmondom az igazat: nem érdekel, mit gondolsz rólam odaátról. Tengernyi, nem egy halom ügyem van, amivel foglalkoznom kell, és nincs idôm itt vitába szállni veled, és szavakat csipkelôdni. Van valami lényeges mondanivalója? Ha nincs, akkor én máris megyek...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "Sikerült összeszednie egy milliót? Szép munka, Charles, egyszerûen kifogástalan! De Philippe de Poincy sajnos már nincs a rezidenciáján, a Társaság ügyeiben titkos expedícióra indult. Úgyhogy várnia kell egy kicsit, mielôtt meglátogatja.";
			link.l1 = "Csessze meg magát és a titkos ügyeit! Azt hittem, végeztem ezzel az egésszel és hazamegyek, és most...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "És most megnyílt a lehetôség, hogy sokkal több pénzt keressen, és nem is akármilyet. Bátyám, az, hogy az öreg róka által kért összeget összegyûjtötted, elképesztô, de én nem lennék ilyen magabiztos és nyugodt... De Poincy, eléggé sikamlós angolna, és elég nagy érdeklôdést mutatott az ön szerény személye iránt, és...";
			link.l1 = "És most attól félsz, hogy egy millió nem lesz elég neki?! Vagy valamit kihagytál a múltkor?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "Nem félek semmitôl, de figyelmeztetnem kell, hogy Poincy nem egy egyszerû ember. Amíg ô távol van, van alkalmad arra, hogy némi tekintélyt építs magadnak, hogy egyenrangú félként beszélhess vele, ne úgy, mint egy úrral és egy kiszolgálóval. Ezért kitartóan felszólítalak, hogy kövesd a tervemet, amelyet most azonnal kifejtek neked.";
			link.l1 = "Rendben van. Nincs értelme sírni a kiömlött tej felett. Még egy kicsit kitartok ebben a pokolban. De Poincy nem fog örökké vitorlázni. Tájékoztass a tervedrôl.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Ó! Dicséretes válasz. Örülök, Charles, hogy férfivá váltál. Azonban ne légy olyan szigorú a bátyáddal szemben. Valamit el kell mondanom neked. Már nagyon vártam, hogy újra találkozzunk, és már ki is dolgoztam egy tervet arra, hogy mit fogsz csinálni legközelebb.";
			link.l1 = "Szép volt. Akkor tájékoztass.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Nézd. Persze, a pénz nagy szerepet játszik a Karib-térségben, mint mindenhol máshol, de a pénz nem old meg mindent. Egy sikeres embernek nemcsak súlyos pénztárcával kell rendelkeznie, hanem kiterjedt és sokféle kapcsolattal is, és nem aljanépekkel, hanem olyan emberekkel, akik jelentenek valamit ebben a világban.\nNem számít, hogy milyen nemzetiségûek vagy milyen birtokról származnak. A kapcsolatok olyan ajtókat nyitnak meg, amelyeket pusztán pénzzel nem lehet kinyitni. A 'pénz és a kapcsolatok' kombinációja adja az embernek a legértékesebb dolgot a világon - a hatalmat.\nAz ilyen kapcsolatok kiépítését érdemes megfontolnod, és ezt nem teheted meg fuvarozással, kereskedelemmel, kisebb kalózkodással vagy akár a kormányzók kegyeinek megszerzésével.";
			link.l1 = "Mit javasolsz?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "A Karib-térségben nincs túl sok erôs szervezet. Az egyik ilyen a Holland Nyugat-indiai Társaság. Csatlakozhatsz hozzájuk. A központjuk Willemstadban van Curacaón. A Társaság gyakran alkalmaz harmadik fél kapitányait, és a leghasznosabbaknak különleges hosszú távú szerzôdéseket kínál.\nHa szerencsés vagy, tisztességes karriert futhatsz be ott. Úgy hallottam, hogy most komoly bajok vannak náluk - néhány angol magánhajós fegyvert fogott a Társaság ellen, és folyamatosan elsüllyeszti a hajóikat. Nem tudnak vele mit kezdeni, tengerésztiszt, így túl kemény nekik.\nAzt mondják, hogy valahogy kapcsolatban áll az angol katonai hírszerzéssel, és ôk nagyon komoly emberek. Szóval, lehet, hogy ennek a kapitánynak az oldalára állni még jobban megéri neked, de a probléma az - nem tudom a nevét, csak azt tudom, hogy Antigua a mûveleti bázisa.\nElhajózhatsz oda, és kérdezôsködhetsz. Hallottam valami furcsa szervezetrôl is, amelyik szintén részt vesz ebben az angol-holland konfliktusban, de nem tudom, melyik oldalon állnak. Csak annyit tudok, hogy a nyomok Barbadosra, Bridgetownba vezetnek...";
			link.l1 = "Tehát azt javasolja, hogy jelentkezzek a hollandoknál szolgálatra, vagy keressek egy kétes kapitányt, vagy egy még kétesebb 'szervezetet'?.";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "A választás a tiéd. Mindenesetre nem lesz más lehetôséged, hogy gyorsan bejuss olyan emberek közé, akik mások sorsáról döntenek a Karib-tengeren, és jelentôs hatalommal rendelkeznek. Remélem, nem vette a fejébe, hogy két-három szívesség a kormányzónak, és máris bekerülhet a királyi haditengerészetbe.";
			link.l1 = "Tudod, kedves testvér. Valójában nem reménykedtem abban, hogy katonai karriert futhatok be a francia haditengerészetnél. Isten ments, hogy úgy végezzem, mint te, egy börtöncellában ragadva valami olyan feladat miatt, amit nem sikerült elvégeznem... Rendben, megértettem. Azt hiszem, a holland társaság fôhadiszállását különösebb akadályok nélkül megtalálom, de fogalmam sincs, hogyan keressem a többi pártot...";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "Ami az angol magánhajót illeti, az antiguai St. John's-ban kérdezôsködhet. Valaki biztosan meg tudja mondani. Mondja meg nekik, hogy az angol flottánál keres munkát. Ami a 'harmadik haderô', illeti, errôl beszélhetsz a bridgetowni emberekkel. Valakinek ott biztosan van kapcsolata ezzel a szervezettel.";
			link.l1 = "Legalább a munkájukat kompenzálják? A Cég, ez a magánvállalkozó... Vagy mindez csak a 'kapcsolatok'?kedvéért lesz?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, meglepsz engem.A Holland Nyugat-indiai Társaság olyan összegekkel dolgozik, amelyeket egy király is megirigyelne. A kalóz, akirôl meséltem neked, annyi holland hajót fosztott ki, hogy már most túlcsordult a vagyonán. És a 'szervezet' emberei nem csak sok pénzzel rendelkeznek. Egy rakás pénzük van.\nHa nekik dolgozol, mindig garantáltan kapsz egy édes szelet tortát. A hozzájuk hasonló emberek mindig nagyban játszanak. És ha okos vagy, mindig játszhatod a saját játékodat, és még többet kereshetsz.";
			link.l1 = "Jól van, rendben. Átgondolom, és eldöntöm, mi a legjobb választásom. Van más utasításod is?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Igen. Meg kell tanulnia a navigációs eszközök használatát. Sajnos sok navigátor csak az iránytû és a csillagok alapján tud tájékozódni, és nem tudja megbecsülni a koordinátákat. És ez kritikus.\nSo. Használj boussole-t a szélesség becsléséhez. Ez egy elég ritka eszköz, és nem fogod megtalálni a boltokban, de két hétköznapi tárgy - egy iránytû és egy asztrolábium - felhasználásával magad is elkészítheted. Itt találod az útmutatót.\nA földrajzi hosszúság becslése egy kicsit trükkösebb. Szükséged lesz egy névleges kronométerre. Készíthetsz egyet egy közönséges hajókronométerbôl, ha homokórával állítod be. A probléma az, hogy egy ilyen eszköz csak egy hónapig mûködik hatékonyan, mielôtt a hibák miatt túlságosan használhatatlanná válik.\nA kronométert mindig újra kell állítani. Homokórákat a holland Nyugat-indiai Társaság irodájában lehet vásárolni. Én is ott vettem kronométereket. Itt vegye ezeket az utasításokat.";
			link.l1 = "Köszönöm. Azonnal nekilátok a tanulásnak.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Próbálja meg minél hamarabb megszerezni ezeket az eszközöket. Minden tapasztalt és elismert kapitány szélességi és hosszúsági fokokkal dolgozik. Mindaddig kezdô tengerésznek számítasz, amíg nem tudod, mit jelentenek ezek a számok.\nHát gyere vissza dicsekedni, amint sikereket értél el a nemrég tárgyalt ügyekben. Isten éltessen, Charles!";
			link.l1 = "Köszönöm, kedves testvér. Úgy érzem, biztosan jól fog jönni!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "És mivel tudsz dicsekedni?";
			link.l1 = "Egyelôre semmivel. Mindhárom szervezetet megtaláltam, és megpróbáltam velük együtt dolgozni, de mint a szivar, szó szerint az elsô lépcsôfokon füstbe ment az egész. Mintha a sors ellenem lett volna kitalálva...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "Szóval a pletykák igazak... Kedves testvér, a sors nem ellened van beállítva. Ezt úgy hívják, hogy tompa agy és görbe kezek. Csalódtam benned. Menj vissza Franciaországba, itt már nincs mit tenned.";
			link.l1 = "De hogyan...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "Ez már nem a te dolgod. Majd én magam elintézem. Vannak más emberek, akik jobban tudnak segíteni a problémám megoldásában. Attól féltem, hogy ha megbízom benned, az életem végéig itt fog tartani. Mindenesetre... Tûnj innen, menj vissza a kurtizánjaidhoz.";
			link.l1 = "Rendben, menj a pokolba...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "Nincs mirôl beszélnem veled. Menjetek.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "A Holland Nyugat-indiai Társaság szolgálatába léptem, és a Társaság helyettes ügyintézôjének, Lucas Rodenburgnak különleges feladatokat ellátó ügynökévé és közeli barátjává váltam. Több komoly küldetést sikerült teljesítenem, különösen az aktuális angol magánhajót likvidáltam. Ráadásul most már saját személyes otthonom van Antiguán, és a zsebemben csörög a pénz."; break;
				
				case "holl_fail": sTemp = "Beléptem a Holland Nyugat-indiai Társaság szolgálatába, azonban a dolgok szerényen alakultak, egy fontos feladatot elbuktam, és kénytelen voltam becstelen leszerelésre, semmivel sem gazdagodva."; break;
				
				case "eng_win": sTemp = "Megtaláltam a valódi angol kalózhajót, Richard Fleetwoodot, és az angol haditengerészet nevében több fontos feladatot is végrehajtottam, különösen felszámoltam a kalóz 'ghost ship' és eltüntettem magát Lucas Rodenburgot, a Társaság helyettes adminisztrátorát. Ezenkívül mostantól saját otthonom van Antiguán, és a zsebem tele van pénzzel."; break;
				
				case "eng_win_half": sTemp = "Megtaláltam az igazi angol kalózhajót, Richard Fleetwoodot, és több fontos feladatot is végrehajtottam az angol haditengerészet nevében, különösen a kalóz 'ghost ship'. kalózhajót likvidáltam... Persze Fleetwood elutazott Angliába, és a vele való szolgálatomnak vége, de azért..."; break;
				
				case "eng_fail": sTemp = "Antiguáról az angol magánhajónál léptem szolgálatba, azonban a dolgok szerényen alakultak, egy fontos feladatot elbuktam, és kénytelen voltam becstelen leszerelésre kényszerülni, semmiséggel."; break;
				
				case "self_win": sTemp = "Felfedeztem a 'titkos szervezetet' Barbadoson, elkezdtem a saját játékomat forgatni, és elég sok mindent elértem: Elintéztem azt az angol magánembert, Richard Fleetwoodot, rács mögé juttattam Lucas Rodenburgot, a Társaság helyettes adminisztrátorát, közeli barátja lettem Matthias Beck kormányzónak és a társaság igazgatójának, Peter Stuyvesantnak. Ráadásul most már saját személyes otthonom van Antiguán, és a zsebemben csörög a pénz."; break;
				
				case "self_fail": sTemp = "Felfedeztem a 'titkos szervezetet' Barbadoson, elkezdtem némi saját játékot forgatni, azonban az igazság pillanatában minden porba hullott..."; break;
			}
			dialog.text = "És? Ugyan már, kedves testvér, ne húzd magaddal. Mi a jó szó? Néhány pletyka suttogva jutott el hozzám a te lelkes szorgalmadról, de én mindent tôled akartam hallani.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Kitûnô! Nagyszerû munka, Charles! Egy percig sem kételkedtem benned! Messzire fogsz jutni, kedves testvér... Hogy így elfoglalod magad, és ilyen fontos emberekkel építesz kapcsolatokat, persze, erre nem számítottam. Gratulálok!";
			}
			else
			{
				dialog.text = "Ne bosszankodj, Charles. Ha nem jött össze, nem tehetsz ellene semmit. Majd más eszközökkel elérjük a kívánt eredményt.";
			}
			link.l1 = "Most mit tegyünk, Michel? Itt az ideje, hogy meglátogassuk Chevalier de Poincy-t? Úgy érzem, eléggé felkészültem a vele való beszélgetésre.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Sikerült már összeszednie a szükséges egymillió pezót?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Igen, jelenleg rendelkezem a szükséges összeggel.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "Nem, még nem rendelkezem ennyi pénzzel.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Kitûnô! Akkor már nem kell sokáig ülnöm ebben a kazamatában... Induljon Capsterville-be, a Szent Kristóf úton van, és kérjen audienciát de Poincy-tól. A kormányzói palotában kell lennie, ahol lakik. Ezen túlmenôen, csak ítélj a helyzet alapján és emlékezz: Poincy ravasz, nagyon ravasz... Van egy rossz érzésem, hogy ez az egész nem fog olyan könnyen menni. Menj, testvér, és légy óvatos!";
			link.l1 = "Majd észben tartom az óvintézkedéseidet, Michel. Ne aggódj, én sem tegnap születtem. Megyek a vén rókához. Viszlát késôbb!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "Akkor nincs értelme beszélni de Poincyval. Még csak be sem engedi magát. Szedd össze a pénzt, testvérem, te már elég tapasztalt vagy, úgyhogy nem lesz nagy gond. Hajózz Capsterville-be a Saint Christopheren, amint megvan.\nA Chevaliernek a kormányzó palotájában kell lennie. Kérj audienciát, és be fognak engedni. Aztán nézd meg magad, és légy óvatos: Poincy ravasz, nagyon ravasz... Valami azt súgja nekem, hogy ez a történet nem így fog véget érni.";
			link.l1 = "Majd észben tartom az óvintézkedéseidet, Michel. Ne aggódjon, én sem tegnap születtem. Amint összeszedem a pénzt, azonnal elmegyek az öreg rókához. Viszlát késôbb!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Nom d'une pipe! Pontosan ettôl féltem. Poincy már régóta a nyomodban van, Charles. Ezért érdeklôdik annyira irántad! Elég jó hírnevet szereztél magadnak a Karib-térségben, és ezért úgy döntött, hogy téged használ fel, hogy teljesítsd azokat a megbízásokat, amik elúsztak...";
			link.l1 = "Az az érzésem, Michel, hogy te nagyon is tisztában voltál vele, csak nem akartál elôbb tájékoztatni. Túlságosan is simán alakult... Elôször a pénz, most a munkád... Ez nem véletlenül történik.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, ne keress valami titkos üzenetet ott, ahol nincs. Ha már az elsô nap odaadtad volna Poincy-nak a pénzt, amikor idejöttél... Vagyis, mondjuk úgy, hogy ha lett volna... A Chevalier nem kért volna tôled semmi mást. De most, hogy érdeklôdött ön iránt, és látta, milyen könnyen beilleszkedett ide, és hogy mire volt képes, úgy döntött, kihasználja a tehetségét.";
			link.l1 = "Igaz... mert a te tehetséged már nem elégíti ki ôt, igaz? Merde! Jól van, rendben. Látom, zsákutcába jutottam. Ki ez az eretnek? Hogyan találhatom meg?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Nem kell keresni ôt! Soha nem hagyja el Tortugát, és az általa épített bástya és a hûséges hugenották hordáinak védelme alatt marad, akik katonaként szolgálnak a helyôrségében. Ezért minden katona hûséges hozzá. Poincy Francois Levasseur-ra, Tortuga kormányzójára gondolt.\nA spanyolok még mindig nem tudják ôt onnan kiszakítani, és de Poincy komolyan hitte, hogy képes leszek rá egyedül, a haditengerészet támogatása nélkül, már csak azért is, mert a polgárháború kirobbantása a santo domingói helyôrség közeli elhelyezkedése miatt is rossz politikai ballépés lenne.\nA vén szarházi túlságosan aggódik a tiszta karrierje és a közelgô nyugdíja miatt ahhoz, hogy mindent így kockáztasson. Mindazonáltal Levasseur túl messzire ment, és veszélyt jelent a koronára.\nDe Poincy, aki maga nevezte ki Levasseurt jelenlegi pozíciójába, személyes ellenségének tekinti ezt a félelmetes hugenottát, és alig várja, hogy leváltsa ôt a máltai Chevalier de Fontenay-vel, a közvetlen felettesemmel, akinek a parancsnoksága alatt érkeztem ide Máltáról.";
			link.l1 = "Dicsôséges! Elôbb keressünk egymilliót, aztán gyilkoljuk meg Tortuga kormányzóját. Mi lesz a következô megbízatásom? Szervezzek összeesküvést az Escorialban? A francba! Nem csodálom, hogy elszúrtad ezt a dolgot. A kormányzó kiiktatása nem olyan, mint a spanyol kereskedôk kirablása. Remélem, volt valami terved, amikor megesküdtél, hogy kihúzod a gesztenyét a tûzbôl?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Hogy teljesen ôszinte legyek, nem volt semmilyen tervem, mivel úgyis ott akartam hagyni a szolgálatot, és a kockázatos vállalkozásom sikere esetén visszatértem volna a családi kúriánkba. Személy szerint fütyülök de Poincy problémáira.\nSokára sokkal rugalmasabb lett volna, amint meglátta volna az indiai aranyat... Hát, jelenleg minden adu ász ellenünk van nála. Azt hiszem, addig maradok itt, amíg Levasseur Tortuga kormányzója.";
			link.l1 = "És a de Fontenay vezette máltaiak, akiknek a kormányzói székre van kilátásuk, miért ne rohamoznák meg maguk Tortugát?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Képzeld el. A rend hadat üzen Louisnak. Ne légy abszurd! Egy ilyen botrány nem jöhet szóba. Tortugát csak egy magánszemély foglalhatja el. Egy kalóz, vagy egy olyan katolikus kalandor, mint te.\nAzt követôen átadhatja a szigetet az új kormányzónak, akit de Poincy küld. Egy ilyen tett jól fog kinézni a nagypolitika szemszögébôl.";
			link.l1 = "Tehát van értelme a kalózokkal tárgyalni?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "A probléma az, hogy Levasseurnek tekintélye van a Testvériség és azon túl is sok kalóz között. Megengedi nekik, hogy elrejtôzhessenek Tortuga ütegei mögött, és a zsákmányból való részesedésért szabadon eladhassák, amit kifosztottak.\nRégebben osztozott de Poincyval, de most már nem osztozik. A kalózhajók megvédik Tortugát és a helyôrséget, ami még nehezebbé teszi az erôd megrohamozását.";
			link.l1 = "Úgy gondolod, hogy ez az ügy veszett ügy?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Mindig van megoldás, kistestvér. Csak nem mindig látható a felszínen. Nem minden kalóz szimpatizál a tortugai hugenottákkal. Legalább két tekintélyes kalózt ismerek, akik Levasseurt árulónak és söpredéknek tartják. Steven Dodsonról, más néven a Cápáról és a Mosquitoes Bay legendás bárójáról, Jan Svensonról beszélek.\nNem tudom, hol találom a Cápát, hallottam olyan pletykákat, hogy valami történt, és el kellett hagynia a bázisát Isla Tesorón. De Svensont mindig megtalálod Blueweldben. Ô ott egy jelentôs figura.";
			link.l1 = "Gondolod, hogy ez... Svenson segíteni fog nekem?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Meg fogja, ha segítesz neki. Jelenleg nem mennek túl jól a dolgai, és az embernek szüksége lenne hûséges és tehetséges emberekre. Elôbb be kell bizonyítanod neki a hasznosságodat, mielôtt komolyabb beszélgetést folytatnál vele. Majd megtalálod a módját, hogy ezt megtedd, ha odaérsz. Nehéz innen tanácsot adnom.\nGondolom, úgy döntöttél, hogy továbbmész, Charles, hiszen folyamatosan kérdezôsködsz?";
			link.l1 = "Tudja, Michel, épp most adtam el egy rakás ezüstöt de Poincy-nak. Vérrel, verejtékkel és könnyekkel gyûjtöttem össze! Nem vagyok benne biztos, hogy a maga helyében akár egyetlen louis d'or-t is kockáztatott volna értem.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Ne szakíts félbe! Hülyeség lenne üres kézzel visszatérni apához. A probléma még mindig nincs megoldva, rácsok mögött vagy, és a Társaság elárulása miatt elítélés fenyegeti. Poincy nem habozna bemocskolni a Monper nevet, ha nem teljesíteném 'kérését'. Ez az arcára volt írva. Úgyhogy én most elmegyek Blueweldbe, hogy megtaláljam a módját annak, hogyan közelítsem meg Svensont. Addig is gondolkodjon el azon, hogy mit 'felejtett még' mondani nekem. Például most hallok elôször tôled valamilyen indián aranyról, amit de Poincynak kellett vinned.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Vannak dolgok, amelyek jobb, ha rejtve maradnak. Igazad van, nem mondtam el mindent, amit tudok. Talán egy nap majd többet is elmondok, de nem azelôtt, hogy Levasseurrel foglalkozol, egyelôre haszontalan tudás lenne.\nNincsenek kétségeim afelôl, hogy az irántam érzett megható törôdésedet csak az a vágy váltja ki, hogy megmentsd a családunk becsületét. Azzal, hogy megmentesz engem, elsôsorban magadat mented meg, másodsorban pedig azt a lehetôséget, hogy Párizs legjobb házait meglátogathasd. Tévedek?";
			link.l1 = "Attól tartok, ez már nem így van, testvér. Igazad volt. Ezek az elmúlt hónapok, amelyeket a Karib-tengeren töltöttem, minden porcikámat és egész szemléletemet megváltoztatták. És biztos vagyok benne, hogy ez jó irányba változott. Már nincs szükségem azokra a párizsi szalonokra, és egy nap képes leszek a Monper név nélkül is továbblépni. De Maure sem rosszabb...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "És most már igazából csak az fáj, hogy a szégyened nyomot hagy öreg apánkon. Ô nem ismeri a valódi helyzetet és azt, hogy mi folyik itt valójában. Továbbá, ahogy helyesen állapítottad meg, a patrimoniát vissza kell állítani az ominózus állapotból. A szabadságodért fizetett millió pedig jelentôsen megkönnyítette a kincstáram, így az nyilvánvalóan újratöltésre szorul.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "Kiválóan megragadta az élet minden leckéjét, Charles. Igazán örülök neked. És örülök, hogy ahelyett, hogy hazahajóztál volna Franciaországba, elfogadtad de Poincy kérését. Remélem, hogy minden jól alakul számodra, és hogy képes leszel véghezvinni azt, amire én magam nem voltam képes.";
			link.l1 = "Attól tartok, nincs más választásom. A Karib-tengeren töltött elsô napom óta mindent egyedül csinálok. Viszlát késôbb, Michel. Azt hiszem, a következô találkozónkban a szabadon bocsátásodról szóló parancs is szerepel majd.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Várjon egy percet! Mielôtt elmegy Jan Svensonhoz, feltétlenül látogassa meg Marcus Tyrexet - ô a kód ôrzôje. Ô uralkodik La Vegán Hispaniolán. Határtalan hatalma van a kalózok között, és a spanyolok halálosan félnek tôle.";
			link.l1 = "Tudna segíteni az ügyünkben?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Kételkedik benne. Nem igazán tudom megmondani, melyik oldalon áll, valószínûleg csak saját magát képviseli. A Cápára és Svensonra mindenképpen szükséged lesz, de jelenleg - Tyrex a leghatalmasabb kalóz idekint. Nem véletlenül választották ôt a kódex ôrzôjének. Nem szabadna figyelmen kívül hagynia egy ilyen fontos személyiséget. Hasznosnak bizonyulhat, ha jobban megismered a kalózokat, mielôtt Svensonnal találkozol. Talán még nevet is szerezhetsz magadnak közöttük...";
			link.l1 = "És már megint visszatértünk a kalózokról szóló beszélgetéshez. Nincs az az isten, hogy megússzam, mi? Hát jó. Meglátogatom ôt.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "Kalóznak lenni és velük üzletelni teljesen más játék, testvér. Remélem, látod a különbséget. Menj La Vegába, és kérj munkát Tyrex-tôl. Ha ti ketten nem jöttök ki egymással - cseszd meg ôt, és gyere vissza hozzám.";
			link.l1 = "Rendben, Michel. Viszlát!";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "Legalább megpróbáltad. Lehetôséged volt arra, hogy 'megismerkedj' egy hírhedt kalózbáróval. Ne is törôdj vele. Menj Jan Svensonhoz, ô Blueweldben van. Próbáld meg ôt a szövetségeseddé tenni, különben a Levasseurrel való üzletelésünk vérre megy.";
			link.l1 = "Jól van, rendben. Máris indulok.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Örülök, hogy megálltál, testvér. Egyszer már mondtam neked, hogy ez egy teljesen más játék - kalóznak lenni és velük üzletelni. És te eltévedtél. Remélem, nem követed el ugyanazt a hibát a Cápával és Svensonnal. Végezd el a munkát, de tartsd magad távol tôlük. Végül is francia nemes vagy, úgyhogy légy fölöttük. Most menj Jan Svensonhoz, ô Blueweldben van. Próbáld meg ôt a szövetségeseddé tenni, különben a Levasseurrel való üzletelésünk vérontásba torkollik.";
			link.l1 = "Jól van, rendben. Máris indulok.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "Nagyon örülök, ha igazat mondasz. De vajon megbízhatok-e egy olyan kalóz szavában, aki városokat gyújt fel, még ha azok spanyolok is, és civileket gyilkol, köztük nôket is?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Állj... Nagyon sajnálom, amit Tyrexszel tettem. A saját szememmel láttam a poklot, testvér... Nem, vége van! Végeztem a kalózkodással, és soha többé nem teszem be a lábam La Vegába. Mindent megteszek, hogy helyreállítsam a jó hírnevemet.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "Hiszed vagy sem. Te vagy rács mögött, nem én.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Hagyd abba... Tényleg megbántam azokat a szörnyûségeket, amiket Tyrexszel együttmûködve tettem. A saját szememmel láttam a poklot, testvér! ...Nem, a kalóz múltamnak vége! Már nem vagyok La Vegában. Minden intézkedést megteszek, hogy helyreállítsam a jó hírnevemet.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Ó, testvér... Ne haragítsd meg Istent... Remélem, hogy ez nem fog megismétlôdni Svensonnal és Sharkkal. Tégy dolgokat, de maradj távolságtartó, és ne feledd, milyen emberek ezek. Egy francia nemesnek nem illik olyanná válnia, mint ôk. Legyen magasabb rendû. Most menj el Jan Swensonhoz Blueweldbe, és próbáld megkeresni az öreg korzót. Nélküle nem lesz lehetséges a Levasseurrel kapcsolatos problémát egy kis vérontással megoldani.";
			link.l1 = "Rendben. Nem fogok késlekedni.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "Nagy erôfeszítéseket kell tenned, testvér. Emlékszel, mit mondtam neked egyszer már? Hogy ez egy teljesen más játék - kalóznak lenni és velük üzletelni. Te... Felejtsd el, remélem, nem követed el ugyanazt a hibát a Cápával és Svensonnal. Végezd el a munkát, de tartsd magad távol tôlük. Végül is francia nemes vagy, úgyhogy állj fölöttük. Most menj Jan Svensonhoz, ô Blueweldben van. Próbáld meg ôt a szövetségeseddé tenni, különben a Levasseurrel való üzletelésünk vérontásba torkollik.";
			link.l1 = "Jól van, rendben. Máris indulok.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Ez nem a megfelelô idô a beszélgetésre, testvér! Az ellenség a menedékünkben van!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "Látom, a haditengerészet kapitánya lettél... Hogy ôszinte legyek, nem gondoltam volna, hogy ez lesz. Ôszintén gratulálok neked!";
			dialog.text = "Épp idôben érkeztél, kedves testvér! Annyira örülök, hogy látlak! Ezek az elhagyott kasztíliaiak már teljesen elfoglalták Saint-Pierre-t. Már azt hittem, hogy végünk van! "+sTemp+"";
			link.l1 = "Még nem vagyunk túl az erdôn, a város tiszta, de a szemétládák hátul ülnek az erôdben, és ott van egy hatalmas hajóraj egy csatahajó vezetésével. De egészen örömteli híreket hozok: Michel, szabad vagy!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "Nem hiszek a fülemnek! Ez tényleg igaz? Szabadság?!";
			link.l1 = "Levasseur halott, Tortuga élén most már a volt parancsnokod áll, és a vén róka Poincy minden vádat levett ellened. Mostantól semmi sem veszélyezteti a jó hírünket.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "Az utolsó pillanatig kételkedtem... Meglepettél, Charles, és sikerrel jártál ott, ahol én szenvedtem el egy kínos fiaskót.";
			link.l1 = "Audaces fortuna juvat, testvér... Mint látod, mostanra már latinul is tudok. Hol van a cellád kulcsa?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "A cellám kulcsa a rendfenntartó tiszt asztalánál van. Ott keresd meg. Talán leesett a földre és lecsúszott valahol...";
			link.l1 = "Megyek, megkeresem ôket, és visszajövök!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Végre - szabadság! Olyan régóta vártam erre a pillanatra!";
			link.l1 = "Fogalmad sincs, hogy én is milyen régóta vártam erre! Michel, tudunk-e embereket gyûjteni, hogy visszavágjunk?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "Mi jár a fejedben, Charles?";
			link.l1 = "A spanyolok által jelentett veszély még nem múlt el. Ki akarom ütni ôket az erôdbôl, aztán egyesíteni az erôinket, hogy a szárazföldrôl és a tengerrôl is megtámadjuk a hajórajokat! A bástya ágyúinak felhasználásával képes leszek megküzdeni a csatahajóval!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "Van embererônk! Nagyszámú lovag indult el, hogy megvédje a kormányzó palotáját. Biztosan találunk majd valakit a városban... Összeszedek mindenkit, akit csak találok. Találkozunk a városkapun túl!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Itt van testvér, a seregünk. Az összes ember, akit találtam. Nem sokan vagyunk, de harcolni fogunk a hazánkért! Kiütjük ezeket a kibaszott betolakodókat az erôdbôl! A meglepetés ereje segíteni fog nekünk - nem számítanak a támadásunkra. Elôre!";
			link.l1 = "Dulce et decorum est pro patria mori! Gyerünk!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "Megtörtént, testvér! Az erôd a miénk!";
			link.l1 = "Kár, hogy a spanyol századdal vívott ütközetben ekkora veszteséget szenvedett... de még így is képes egy csatát vezetni.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "Én is kiveszem a részem. Megtöltjük az ágyúkat, és kemény csapást mérünk az ellenségre! De csak azután, hogy látjuk a hajórajodat közeledni, különben a hadihajó gyorsan fûrészporrá lô minket.";
			link.l1 = "Szedd össze az embereket, Michel! Azonnal indulok vissza a partra!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, ne feledd: a hajóraj legveszélyesebb része a hadihajó! Próbáljátok meg elôbb kiiktatni. Az erôd ütegének maradékával is tüzet összpontosítunk rá.";
			link.l1 = "Rendben, testvér. Talán el kéne fognom.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "A körülményekbôl ítélve, nem én vagyok az, akinek tanítania kellene téged. Most már nem vesztegethetjük tovább az idônket!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Gloria gyôzedelmeskedik! Gratulálok a gyôzelmedhez, testvér! Nagyszerû voltál! A spanyolok teljesen megsemmisültek!";
			link.l1 = "Remélem, ez megtanítja ôket, hogy kétszer is meggondolják, mielôtt megtámadják a francia gyarmatokat.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Most mondd meg nekem, Charles: mit ér az elôzô életed... ehhez képest?";
			link.l1 = "Ne emlékeztess...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Emlékszel, mit mondtam neked az elsô találkozásunkkor? 'Az életet szeretni fogod', , ez az! Igen, és egy hatalmas köszönet neked, testvér, a segítségedért. Nélküled valószínûleg soha nem sikerült volna kiszabadulnom a földalatti bázisról.";
			link.l1 = "Ne is említsd, Michel. Végül is a testvérem vagy, és kötelességem volt segíteni neked.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Csak nézz magadra, testvér, le vagyok nyûgözve: ennyi erô a szemekben, magabiztosság a mozdulatokban, tartás a testtartásban... hová tûnt az a szaros mûvész és udvari bolond? Hát persze! Túlszárnyaltad legmerészebb várakozásaimat, az igazat megvallva, sosem gondoltam volna, hogy ilyen... leszel.\nEz még... egy kicsit meg is ijesztett. Mert te semmitôl sem riadsz vissza, hogy elérd a célodat. Te jó vagy, túl jó...";
			link.l1 = "Valamiért megint nehezen értelek meg. Megint elégedetlen vagy velem?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "Nem! Mirôl beszélsz?... Egyáltalán nem! Csak az izgalmamat adtam ki magamból.";
			link.l1 = "Jól van, rendben. Szóval, mit fogsz csinálni legközelebb, testvér? Továbbra is a Társaságot fogod szolgálni? Vagy visszatérsz a mi örökségünkhöz? Igen, és majdnem elfelejtettem: megígérted, hogy elmondasz nekem egy dolgot.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "Pontosan mirôl?";
			link.l1 = "Ami a de Poincy-nak tett szolgálatodat illeti. Az indiai aranyról, amit el akartál neki vinni. Mindenrôl, ami a bebörtönzésed elôtt történt. Sok mindent nem sikerült elmondanod nekem, Michel, így szinte vakon maradtam. Szóval...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Testvér, tökéletesen emlékszem arra, amit mondtam. Mindent elmondok neked. De nem az égô város közepén!\nMindkettônknek sok dolga van most. Rendbe kell tenned a századodat, rendbe kell hoznod, és újra készenlétbe kell helyezned a hajókat. Én és a kormányzó megszervezzük és megnyugtatjuk a helyieket.\nMajd holnap reggel mindent megbeszélünk egy pohár jó francia bor mellett. Bízz bennem, testvér, nagy tervem van. Egy igazán nagy tervem. De nem most. Holnap reggel kilenckor meglátogatom Benoit apátot, nála fogom tölteni az éjszakát, ô régi barátom.";
			link.l1 = "Rendben, Michel. Akkor el van intézve. Alig várom a holnapi beszélgetésünket.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Párbeszéd 28.";
			link.l1 = "Rendben, Michel. Akkor el van intézve. Alig várom a holnapi beszélgetésünket.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "Nincs szükség búcsúzkodásra, Charles!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("Mindannyian örökre lekötelezettjei vagyunk, kapitány! Megmentette a kolóniánkat a pusztulástól!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("Ön egy bátor és okos tengerésztiszt. Mindazok, akik Saint-Pierre-ben laknak, imádkoznak önért, tudja ezt!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("Ön nemzetünk büszkesége és öröme, és Saint-Pierre hôse. Ezt soha nem fogjuk elfelejteni!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "Tehát újra találkozunk, "+pchar.name+". Figyelmeztetéseim ellenére továbbra is kerestél engem, és a keresésed messzire, messzire vitt...";
			link.l1 = "Michel? Valamiért nem vagyok meglepve. Miguel Dichoso visszatért Tayasalba egy újabb kincsért? Hm-hm-hm. Igen, találkozni akartam veled, kedves testvérem. Már alig vártam, hogy belenézhessek a szemérmetlen szemeidbe. Ráadásul az ellenem a temetôi kriptában elkövetett merényleted csak hab volt a tortán. De elôbb mondd meg, hogyan szólítsalak? Michel de Monper vagy Miguel Dichoso?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "Ezek a nevek már nem fontosak, "+pchar.name+". Ez mind a múlté, ami nagyon hamarosan magából a történelembôl is eltûnik. Most jött el az igazság pillanata, amely felé már negyedszázada, az elsô szárazföldi útjaim óta tartó hosszú negyedszázad alatt egyre csak közeledtem...";
			link.l1 = "Micsoda?! Ez... ez nem lehet!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Igen, "+pchar.name+". Látom az arcodon, hogy érted, ki vagyok, de nem tudod elhinni. Én vagyok az, akire az elmúlt hónapokban vágytál. Az, akivel istened képviselôje, a santiagói inkvizítor harcba áldott téged.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "Egyetértek, "+pchar.name+", hogy ezt nehéz elhinni. Az élet bonyolultabb és meglepôbb, mint bármelyik tündérmese...";
			link.l1 = "Mindenre készen álltam, de... a testvérem!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Testvér? Csak apai vér szerint. Különbözô anyáink vannak, "+pchar.name+". Tudd meg, hogy az anyám Kanek lánya volt, akit Sochikezhalnak hívtak. A híres Nicolas Gotier parancsnoksága alatt álló francia kapitányok elrabolták, miután ostobán elhagyta Tayasalt. Úgy döntöttek, hogy rabszolgasorba taszítják. Egy Serge Benoit nevû férfi is köztük volt.\nA kapitánya tettét megszégyenítve elhagyta ôt, fátylat öltött, és most Benoit apátként ismeritek. Henri de Monper, az apánk, akkoriban tengerésztiszt volt. Megvette Shochikezhal, és elvitte Franciaországba, ahol megszült engem. Nagyjából ugyanekkor születtél te is, "+pchar.name+". Anyád meghalt a szülésbe, és apánk kijelentette, hogy törvényes felesége ikreket szült.\nShochikezhal, az én anyám, mindkettônknek dajkája lett. Téged az itzai néphez tartozó indián asszony tejével tápláltak, "+pchar.name+"! Késôbb nagyanyád anyai ágon úgy döntött, hogy befogad téged nevelésre, és az anyád nevét kaptad - de Maure.";
			link.l1 = "Honnan tudtad meg mindezt?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Nem gondolnád, testvér, hogy többet tudok, mint az átlagemberek? Ráadásul apánk sokat mesélt nekem, és én is sok mindenrôl tudok... Csak, ahogy mondják, a nadrágomban ülve.";
			link.l1 = "Most már minden világos... És mi történt az édesanyáddal? Miért nem láttam ôt soha?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "Ô halt meg az életemet megmentve. Alig több mint egy évvel a születésem után majdnem meghaltam egy betegség miatt. Édesanyám, egy itzai pap lánya, titkos mágikus maja gyógyító szertartást végzett nekem. Meggyógyultam, de ezt a szertartást néhány... pusztító mellékhatás kísérte mennydörgés, villámlás és egy trópusi hurrikán formájában. Shochikezhal feljelentették és megvádolták varázslással, és az inkvizíció tüzén égették...";
			link.l1 = "És jobban lettél...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Ez a rituálé a gyógyulásomon kívül más képességeket is adott nekem, amellett, hogy kapcsolatot nyitott az istenek világával. A többit pedig már tudod. Mint már tudod, a fehér faj tudásának és tapasztalatának fényét a múltba hordozom, és átadom a maja népnek. A történelem újra lesz írva, és ti, fehérek, nem fogjátok uralni ezt a világot. Errôl gondoskodni fogok.";
			link.l1 = "Tehát az egész életed, a legjobb tengerészeti akadémián való tanulás, a hadseregben és a Máltai Lovagrendben való szolgálat lényegében csak katonai tapasztalatok halmozása volt?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Pontosan. Amikor rájöttem, hogy eleget tudok, elintéztem, hogy a Karib-tengerre vezényeljenek. Rábeszéltem Chevalier de Poincy-t, hogy hozzon létre egy bázist Martinique-on. Ezután Tayasalba kellett eljutnom. Ez nem volt éppen egyszerû feladat számomra, mivel ez a fizikai hajó halandó marad, és a karibi portálok nem mûködtek megfelelôen.";
			link.l1 = "És te lettél Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "Kedves testvérem, ezt a becenevet az európai csatamezôkön kaptam. Ott találkoztam Ramon de Mendoza y Ribával is. Azt hiszed, hogy az élet az esélyekbôl áll? Nem, egyáltalán nem, minden esély egy ismeretlen szabályszerûség. Sok minden történt azért, hogy visszatérjek Tayasalba. Két életet kellett élnem. Michel de Monper és Miguel Dichoso. Azt is el kellett érnem, hogy az emberek különbözô embereknek higgyék ôket.\nKellett kalózkodnom, akárcsak önnek, de Poincy szolgálatában, hogy elnyerjem a bizalmát, a kegyeit és a pénzét. Meg kellett gyilkolnom Blaze Sharpot, a kalózok egyik vezetôjét, Ramon de Mendoza szívességeként, hogy katonákat szerezzen az expedícióhoz.\nMeg kellett csábítanom mind de Poincyt, mind de Mendozát a Tayasal kincseirôl szóló mesékkel. Hétszázötvenezer ezüstöt kaptam de Poincy kincstárából, és eladtam a spanyol katonai fregattot Dodson kalóznak. Aztán megtörtént az expedíció. Visszatértem Tayasalba, csakhogy kudarcot vallottam...";
			link.l1 = "Értem... Amíg te még csak ötéves kisfiú voltál, aki apánk örökségében kergette a pillangókat, Kanek, a nagy pap, megijedve Don Alonso de Maldonado Tayasalba való betörésétôl, biztonságosan elrejtette a Kukulcan-maszkot, amely oly fontos a múltba való utazáshoz... bocsánat, a te maszkodra gondoltam!";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Igen, Kanek itt túljárt az eszén. A legnehezebb rituálét hajtotta végre, olyan rituálét, amelyet még az ôsök sem mertek elvégezni. Elrejtette a maszkot a frissen készült lakatlan szigeten, és sikerült elveszítenie a kulcsot Ksocheatemnek - az úgynevezett Igazság Ôrének.\nKénytelen voltam okosan játszani. A rituálé megakadályozta, hogy bármely hajó, amely Taysal kincstárának védett tárgyait szállította a fedélzetén, elhagyja a Karib-térséget, az ilyen hajókat Ksocheatem partjaira dobva. Ezt akartam felhasználni. Elég kincset vittem, hogy megbékítsem Mendozát. Vittem egy különleges, a rituálé által védett tárgyat is.\nEgy hajó, amelynek fedélzetén ez a tárgy volt, arra lenne ítélve, hogy egyenesen Ksocheatembe, egyenesen a maszkomba szállítsák. Így hát tengerre szálltam, és tudattam magam Mendozával.";
			link.l1 = " Szóval egyedül hagytad el Tayasalt?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "Úgy érti, Mendoza katonái nélkül? Persze. Minden spanyolt megöltek itt, Tayasalban. Itzas maga hozta a kincseket a partra, én pedig elmondtam Mendozának, hogy a katonákat a miskitók támadták meg. Hitt nekem, hiszen ôt csak az arany érdekelte, az emberek nem.\nAzt terveztem, hogy a kincsekkel teli hajót a 'Gryffondor', ágyúi alá állítom, de minden sokkal jobban alakult: a báró úgy döntött, hogy a kincseket az én felügyeletem alatt küldi Spanyolországba. Ez volt a lehetô legjobb eredmény, csak meg kellett várnom, amíg a hajó átlépi a Karib-tenger láthatatlan határát.\nMégis kiderült, hogy a kapitánynak más utasításai vannak. Megtudtam, hogy egy különleges fedélzeti egységnek zendülnie kellett volna, amint elérjük az Atlanti-óceánt, megölve a legénységet és az összes tisztet. A kapitánynak az volt a parancsa, hogy utána az indián aranyat juttassa vissza Mendozába.\nA fehér faj egy ilyen szép példánya, ugye, testvér? Meg kellett kockáztatnom, nem tudtam, mikorra várható a lázadás. De minden a terv szerint alakult: a vihar ránk csapott, amint a 'Santa Quiteria' megérkezett Trinidad és Tobago szigetének keleti oldalához. A fregatt visszasodródott a Karib-tengerbe Ksocheatem felé.\nAztán elszenvedtem életem legnagyobb kudarcát - egy hullám lemosott a hajóról, és néhány nappal késôbb Martinique-on, a Le Marin-öbölben találtam magam. Halászok találtak rám, és elvittek Le Francoisba. De de Poincy emberei azonban elfogtak, miközben Cesar Craignél épp visszatértem az életbe. A 'Gryffondor' nem találta 'Santa Quiteria' az általam meghatározott helyen. Chevalier de Poincy dühbe gurult, amint megtudta, hogy az indiai arany eltûnt a rend kincstárából és a saját megtakarításaival együtt.\nAzért letartóztatott. Megölni azonban nem tudott, nem is akart. Az aranyat akarta. Aranyat akart! Ez az egyetlen dolog, amit a néped akar és ami érdekli! Bármit megtesznek érte... Szörnyû helyzetben voltam: Nem volt rajtam maszk, és egy érme nélkül rohadtam egy cellában.\nEkkor hívtalak téged. Igen-igen, kedves testvérem, neked kellett volna kiszabadítanod, hogy azt tehessem, amire születtem. És te rendkívüli munkát végeztél. Úgy tûnik, az itzai tej, amit szoptál, jót tett neked.";
			link.l1 = "Engem az érdekel, hogy mire számítottál akkor, amikor megszöktél Saint-Pierre-bôl? Mi volt a terved?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "Mindvégig te voltál a tervem, testvér. Kukulcan tud olvasni az emberek szívében. A levél, amit az apátnál hagytam neked, arra hivatott, hogy cselekedj. Igazam volt veled kapcsolatban. Azóta figyeltem a fejlôdésedet, amióta elôször találkoztál a santiagói inkvizítorral. Mindent megtettél értem. Megalkottad az Igazság Ôrzôjét. Kiiktattad a versenytársakat. Megtaláltad a Ksocheatem.\nOtt voltam, követtelek. Bár nem számítottam arra, hogy Tayasalba jutsz. Minden várakozásomat felülmúltad. És a segítségeddel megteszem, amire születtem. Az ok, amiért halandó testben születtem.";
			link.l1 = "Csak egy kis kikötés van az érvelésedben, kedves testvérem. Nincs a birtokodban a maszkod, és nélküle semmi sem vagy. Nekem megvan. És nem égek a vágytól, hogy odaadjam neked. Inkább szétrobbantanám, minthogy a kezedbe kerüljön.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "Nem változtathatod meg azt, amit a sors eleve elrendelt. Nem engedem, hogy kárt tegyen a mûtárgyamban. Érzem... Veled van. És te itt vagy, a templomomban, a teljes hatalmam alatt! Soha nem fogod elhagyni ezt a helyet. Itt az ideje a végsô próbatételnek, kedves testvérem, hogy lássuk, mit érsz a Kukulcan elleni csatában!";
			link.l1 = "Feltételezem, hogy a halandó tested még mindig tud vérezni!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha! Rosszul érzem magam miattad, Charles. Ez igazán szomorú. De megérdemelsz egy esélyt, hogy megküzdj egy istennel. Még ha értelmetlen is. Majd késôbb elmondom, ha túléled az elsô felvonást.";
			link.l1 = "Feltételezem, hogy a halandó tested még mindig tud vérezni!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "Úgy tûnik, az erôd elhagy téged, nagy Kukulcan... Lehet, hogy erôs vagy, de a tested még mindig halandó!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "Azt hiszem, ez elég szórakozás lesz. Te valóban mesteri kardforgató és nagyszerû harcos vagy, sôt, azt is meg merném mondani, hogy korod legnagyobb harcosa, de ezt a csatát elvesztetted, "+pchar.name+"...";
				link.l1 = "Mi csak...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Elég, kedves testvér. Nem tudsz ellenállni Kukulcan erejének, amikor együtt van az ereklyéjével! Engedtem, hogy ilyen sokáig életben maradj, csak azért, hogy lássam, mire vagy képes valójában.";
			link.l1 = "Baszd meg... Az utolsó csapás... De milyen ereklyérôl beszélsz? A maszkról? Velem van!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Szegény, szegény kapitány "+GetFullName(pchar)+"... Eljutottál idáig, túléltél minden veszélyt, megöltél sok legerôsebb ellenséget, csakhogy a végén legyôztek!... A jáde maszk, amit a 'Santa Quiteria' on Ksocheatem roncsai közelében lévô fémdobozban találtál, hamisítvány! Ez csak egy ôsi maszk Taysal kincstárából. Ez NEM KUKULCAN ÁRKÁJA!.\nSzemélyesen vettem el innen a sikertelen expedícióm után, az ôsi rituálé ôrzi. Ez a maszk volt az oka annak, hogy a vihar a Santa Quiteria-t Ksocheatembe vitte. Volt egy második célja is. Az volt a célja, hogy megtévesszen mindenkit, aki az IGAZI ereklyémért jött oda.";
			link.l1 = "De... Hol volt akkor az igazi maszk?! Átkutattam egész Ksocheatemet!...";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "Nem tetted, "+pchar.name+". A leletem a szigetnek a 'Santa Quiteria', val szemben lévô oldalán feküdt egy biztonságosan ôrzött szentélyben. Az oda vezetô út földalatti barlangokon keresztül vezet. Bonyolult megtalálni, és nem nyilvánvaló egy halandó kifinomult szeme számára. Ott van! Nézzétek meg alaposan, egy utolsó pillantást...";
			link.l1 = "Ez nem lehet!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "Sok csatát túléltél és megnyertél, testvér. De ezt elvesztetted, "+pchar.name+"...";
			link.l1 = "És most mi lesz?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "Egyenesen a tizedik századba utazom, hét évszázaddal vissza. Ez elég lesz ahhoz, hogy a maja civilizáció megingathatatlan katonai és tudományos fölényt érjen el a fehér faj felett.";
			link.l1 = "És mi fog történni a mi világunkkal? El fog tûnni?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "Nem. Ez meg fog változni. Talán lesz egy hely számodra, de semmire sem fogsz emlékezni abból, ami ezen a világon történt. Néhányan azok közül, akik itt születtek, soha nem fognak ott születni, az ellenkezôje is igaz. A halottak életre kelnek, és az élôk pedig meghalnak, így vagy úgy, mindenki újjászületik. Suum cuique, mindenkinek a sajátja, "+pchar.name+".\nNe félj, kistestvér. Soha nem fogod felfogni, hogy mi történt, és természetesen elfogadod az új valóságot. Csak én, Kukulcan, fogom megôrizni az emlékeket... De elég! Kanek már mindent elôkészített a rituáléhoz.\nKövetni fogsz engem, "+GetFullName(pchar)+", és tanúja leszel e valóság létezésének utolsó pillanatainak, amelyeket annyira szerettél volna megôrizni.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "Az idôk kapui megnyíltak! Örüljetek gyermekeim, mert olyan közel álltok a nagysághoz! Megteremtjük az új világot, egy olyan világot, ahol nincs helye a sápadt betolakodóknak!\nViszontlátásra, "+pchar.name+", és legyetek készen arra, hogy elfogadjátok új sorsotokat, bármi legyen is az. Suum cuique!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "Ennek a csatának még mindig nincs vége, halandó. Jelentôsen kimerültél, és erôsítés érkezik! Át fogod adni az ereklyémet. Vagy így teszel, vagy elveszem a holttestedrôl, nekem mindegy...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan! Megparancsolom, hogy azonnal öljétek meg ezt az embert!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Nem hallottad, amit mondtam? Ismétlem: megparancsolom neked és a harcosaidnak, hogy fogjátok el és öljétek meg ezt az embert!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! Mi a fene? Kanek! Ismételd meg a parancsomat a kibaszott fiadnak!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "Elárultad a népedet, Urakan! Meghátráltál az ilyen jeles átalakulások elôtt! Harcosok, megparancsolom, hogy fogjátok el és öljétek meg nemcsak ezt az embert, aki a testvéremnek nevezi magát, hanem Urakant, az árulót is!";
			link.l1 = "Harcosok, Cavil és Hurakan nevében megparancsolom, hogy maradjatok úgy, ahogy vagytok, ha fontos az életetek! Egyikôtök sem fogja túlélni a Cavil elleni harcot! Hagyjátok, hogy az istenek maguk döntsék el, ki közülük a legerôsebb a Földön!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "Ez a nap egyre jobb és jobb lesz. Nem számítottál ilyen tettekre, igaz, testvér? Az isteneknek maguknak kell eldönteniük, hogy ki a legerôsebb közülük valójában. És mindenki azt kapja, amit megérdemel, Michel. Suum cuique! Mindenki a maga módján...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
