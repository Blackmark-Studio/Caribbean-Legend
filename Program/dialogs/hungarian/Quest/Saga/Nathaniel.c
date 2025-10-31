// Натаниэль Хоук - пиратский барон Марун-Тауна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "Ah... ki vagy te, a fenébe is?... Khe... (súlyos köhögés rekedtséggel) Átkozott gyengeség...";
			link.l1 = "Üdvözletem, Nathaniel. Te vagy Nathaniel Hawk, ugye?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "Igen, én vagyok az, ha még hívhatom magam így. Valaha Nathaniel Hawk voltam, de most már csak egy szomorú kinézetû szarzsák vagyok. Baszd meg azt a szobrot! Kiszívta belôlem az életet.";
			link.l1 = "Ismerem az érzést...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "Hogy is tehetnéd, fiam, ha még csak fel sem fogod, mirôl beszélek? A-kha... Tudod, milyen érzés félholt, öregemberré változni, amikor egy perce még egészséges és erôs voltam?\nSok mindent láttam már, azt hittem, hogy ez az ôsi indiai templom, amit fiatalon meglátogattam, megölte volna a képességemet, hogy meglepôdjek, de ez... miért nem láttam elôre! Az az átkozott szobor ugyanúgy nézett ki, mint az a régi bálvány, ami a templom ajtaját nyitotta!";
			link.l1 = "Rendben, Nathan, beszéljünk. Hadd mutatkozzam be, a nevem "+GetFullName(pchar)+". Elôször is, nagyon jól megértelek téged, mert ugyanúgy jöttem ide, mint te - a Kukulcan portálon keresztül.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "Tényleg?! Akkor miért nézel ki olyan jól? Vagy ez... Kukulcan csak nekem ártott?";
			link.l1 = "Kígyószem, a miskitó sámán, aki segített neked megszökni, egy nagyon erôs bájitalt adott nekem. Megittam, amint felébredtem a San Augustine-ban. Teljesen meggyógyított. Biztos vagyok benne, hogy Kígyószem neked is tud segíteni. Csak el kell juttatnunk téged hozzá.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "Á, az az indián! Egy bájital? És miért nem adott nekem is egyet?";
			link.l1 = "Azt mondta, hogy nincs rá idô. Üldöztek, és az egyetlen dolog, amit tehetett, hogy megmutatta neked a menekülés útját - a kaput.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "Menekülni? Ó... Nem látod a jelenlegi állapotomat? Még egy szablyát sem tudok tartani. Hogy nevezheted ezt menekülésnek? Hála Istennek, vannak még jó emberek ezen a világon. Ole, Isten áldja ôt... Ismered Ole-t?";
			link.l1 = "Ismered Ole-t? Igazából ô volt az, aki mesélt nekem rólad, mesélte, hogy etetett téged patkányokkal, és hogy iszol, üvegrôl üvegre...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "Gyorsabban meghalok, mint egy égô gyertya, ha nem iszom rumot. Ez az egyetlen dolog, ami életben tart. Rum...";
			link.l1 = "Még mindig ilyen rosszul érzed magad? Ugyanúgy, mint a teleportálás után?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "Hát, nem érzem magam teljesen ugyanúgy... De nem is igazán jobban. Pajtás, mondd meg, miért kellett találkoznod az öreg Nathan-nel? Mi a fenének jöttél ide, erre a vén, rohadt kádra? Hogy beszélgess velem?";
			link.l1 = "Valójában, igen. Nem fogod elhinni, de az ok, amiért ennyit bajlódtam a teleportálással, az az volt, hogy megtaláljalak. A Parti Testvéreknek dolgozom, és Jan Svensont képviselem.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "A fenébe... az erdei ördög? Argh... Azért jöttél ide, hogy végezz velem? Igazából, nem jöttél? Túl beszédes vagy egy bérgyilkoshoz képest. Kérlek - ne kínozz engem. Ha azért kaptál parancsot, hogy kiszedj belôlem valamit - mindent elmondok magam, nincs mit titkolnom.";
			link.l1 = "Hogy érti ezt? A-a, értem. Ön, akárcsak Danielle, úgy gondolja, hogy Svenson volt az, aki megszervezte azt a rajtaütést az életére a Selva-ban. Biztosíthatom, hogy nem Jan tette. Ellenkezôleg, ô a te oldaladon áll, és nagyon aggódik az eltûnésed miatt.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "Tényleg? Átkozottul örülök, hogy ezt hallom. És máris elgondolkodtam... de ki tette? A különítményem percek alatt megsemmisült. Már vártak ránk. Még hajóágyúik is voltak! Az embereim felét elkaszálták grappeshotokkal, aztán a muskétáikkal végeztek velünk...";
			link.l1 = "Hogy ôszinte legyek, nem ismerem a részleteket, de biztos vagyok benne, hogy Jackman áll az egész mögött. Túl sok a véletlen egybeesés, elôször Blaze, aztán te... Jackman meg akarja ragadni a hatalmat, és mindenkit kiiktat, aki az útjába áll. Most már ô uralkodik Maroon Townban helyetted.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "Jackman? Szemétláda! Eh... a Testvériség megosztottá vált az elmúlt néhány évben, korábban minden más volt. Zachariah megbolondult a vallási ügyeivel, Tyrex leszar mindent, Barbazon pedig csak a dublónok érdeklik. Húsz évvel ezelôtt minden más volt...";
			link.l1 = "Hogyan fogtak el téged? Mesélj még!";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "Nincs semmi érdekes mondanivaló! Ahogy mondtam, azok a banditák tervelték ki az egészet. Szépen cselekedtek, összehangoltan és egyértelmûen valakinek a parancsát követve. Százszor is megölhettek volna, de nem tették. Élve akartak engem. Elvittek egy elhagyatott bányába, és bezártak az egyik kunyhóba. 'Míg a fônök meg nem érkezik', mondták.\nAzt hittem, Svenson a fônök, de úgy tûnik, Jackman a fônök. Bár nem tudom, mit akarhatott tôlem, de az biztos, hogy nem sokáig éltem volna a vele való csevegés után.";
			link.l1 = "Ebben nem kételkedem. Svenson biztos benne, hogy Jackman ölte meg Blaze Sharpot... Hogyan tudott elmenekülni?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "Az indiai Kígyószemnek valahogy sikerült beosonnia a bányába. Amennyire én tudom, a miskitók nem szeretik a banditákat. Mindenesetre Kígyószem valamiért megszervezte a szökésemet. Ásott egy alagutat hozzám, bejutott, elvágta a köteleket, és elszöktünk a dzsungelbe.\nA falujába akart vinni, a miskitókhoz. De úgy tûnik, Jackman nagyon akart engem, mert nagy vadászatot szerveztek. A nyomunkban voltak. Kígyószem mindent megtett, hogy átverje ôket, de mindig sikerült ránk találniuk. Kétségtelenül jó nyomkeresôik voltak.\nKözel voltunk Kígyószem falujához, amikor végre ránk találtak. Ekkor már két napja üres volt a gyomrom, és teljesen ki voltam merülve, mivel a lábam is csúnyán megsérült. Éjfél volt, és még mindig emlékszem, milyen fényes volt a csillag a szobor felett... Kígyószem azt mondta, hogy az egyetlen esélyem az, ha eljutok a bálványhoz, és megérintem.\nAzt hittem, hogy a férfi ôrült, de tudjátok, mit mondanak a szalmaszálba kapaszkodásról. Odabicegtem a szoborhoz, megérintettem... és akkor ôrült dolgok kezdtek történni!";
			link.l1 = "Nem kell folytatnod, tudom, mi történt utána.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "Valami hajótörött hajó nedves raktérében találtam magam. Félholt voltam. Nem tudtam járni, csak kúszni. Percrôl percre rosszabbodott az állapotom. Ole épp idôben jelent meg. Valami szar ízû karibi keveréket öntött belém, egy ellenszer és egy gyógyító esszencia keverékét. Aztán rumot adott nekem.\nEzután azonnal jobban lettem. Aztán talált és használt egy régi fatörzset, hogy idehozzon. Már egy ideje itt élek, nem tudom pontosan mióta, elvesztettem az idôérzékem.";
			link.l1 = "Minden rendben lesz, Nathan. Nekem és Svensonnak nagy terveink vannak, és a te szereped ebben nagyon fontos. Vissza kell térned a helyedre Maroon Townban, mi pedig elintézzük azt a söpredék Jackmant.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "Maroon Town? És pontosan hogyan képzeled, hogy ez mûködni fog? Nézz rám, egy rummal átitatott roncs vagyok! Értéktelen... Nem, a Maroon Town feletti hatalmam évei örökre eltûntek. Csapdába estem ezen az átkozott hajótemetôben. Meddig fogom kibírni? Egy hónapig, kettôig, egy évig?\nAztán végül ezeken a rohadt deszkákon fogok feküdni, és Ole a tengerbe dobja, ami Nathaniel Hawkból megmaradt. A legrosszabb az, hogy nem fogom többé látni az én Dannie-met. Eh, vége van, haver.";
			link.l1 = "Ne légy ilyen pesszimista. Kihozlak innen.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "Hogy fogsz kijuttatni innen? És hogy fogjuk elhagyni ezt a helyet? Nincsenek hajók. Akarsz építeni egy tutajt?";
			link.l1 = "Nem. Úgy hagyom el ezt a helyet, ahogy idejöttem. Tudom, hol van a szobor... nagyjából. Megkeresem, aztán visszajövök érted és Shark Dodsonért. Utána elviszünk Kígyószemhez. Ô majd meggyógyít.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "Mit mondtál? Shark Dodson? Steve is itt van? Milyen furcsa hely...";
			link.l1 = "Igen, itt van. Ô a 'kormányzó' a szigetnek, hogy úgy mondjam. Kérdeztem ôt rólad, de nem tud semmit.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "És nem is kéne. Nem akarom, hogy ilyen állapotban lásson. Azt mondta, hogy a sámán meg fog gyógyítani... Alig tudom elhinni. Dannie-t is említetted... Láttad ôt?";
			link.l1 = "Igen. Ô maga talált rám Blueweldben. Kihallgatta a Svensonnal folytatott beszélgetésemet, és megértette, hogy Jannak nem állt szándékában megölni téged, és hogy Jackman ellen dolgozik. Tisztként csatlakozott a hajómhoz, hogy segítsen megtalálni téged.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "Eh, kedves Dannie! Nem változott... ugyanolyan vakmerô, mint fiatalkorában... El sem tudod képzelni, mennyire szeretném látni és megölelni ôt! Sokat gondolkodtam, miközben itt feküdtem. Látod, pajtás, másképp látod a dolgokat, amikor közel vagy a halálhoz. Olyan kevés idôt töltöttem a feleségemmel!\nTengeri razziák, a Testvériség hivatalos üzletei, Maroon Town kormányzása. És ô mindig mindenben támogatott: hetekig egyedül maradt, veszekedett más kalózokkal, amíg távol voltam, parancsnokolt a hajónknak... Az én Dannie-m a legjobb nô a világon! És én... Többször kellett volna mondanom neki, hogy szeretem!\nEmlékszem a napra, amikor elhatároztuk, hogy együtt leszünk! Tulajdonképpen az volt az a nap, amikor elôször találkoztam és természetfeletti dolgokkal harcoltam. Az egész az átkozott bálvány miatt történt, ami pont úgy nézett ki, mint a szobrok. Nem bánod, ha meghallgatsz egy történetet? Elég érdekes.";
			link.l1 = "Egyáltalán nem! Meséld el!";
			link.l1.go = "story";
			link.l2 = "Nathan, nincs idônk kellemes emlékekre. Mesélj róla késôbb, amikor majd a miskitó faluban ülünk egy üveg bor mellett.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "Huszonöt évvel ezelôtt... Fiatal voltam, szenvedélyes és nyugtalan. A Karib-tenger volt a játszóterem. Dannie-t már akkor ismertem. Kedveltem ôt, tényleg kedveltem, és az érzés kölcsönös volt. De gyakran veszekedtünk, veszekedtünk és csipkelôdtünk egymással. Buta fiatalság... Azt hiszem, akkoriban remek szórakozást nyújtottunk a tisztelt tengerészeknek!\nMindenesetre Dannie és én valahogy belekeveredtünk ugyanabba a történetbe. Találtunk egy térképet Khael Roa-ról, és azt mondták nekünk, hogy ez AZ a hely, ahol indiai aranyat lehet találni. Találtunk egy furcsa kinézetû arany bálványt is, a szobrok felsô részének kisebb másolatát.\nA bálvány veszélyes volt, életerôt szívott azokból, akik hordozták. De szükségünk volt erre az elátkozott tárgyra, hogy eljussunk a templomban lévô kincstárba. Az egyetlen probléma az volt, hogy fogalmunk sem volt arról, hogyan kell helyesen használni. Dannie és én elhajóztunk a szigetre. Volt ott egy ôsi templom, fûvel és fákkal borítva. Miután beléptünk, egy hatalmas labirintusban találtuk magunkat.\nSikerült megtalálnunk a helyes utat, és elértük a labirintus központi részét. Azt hittük, hogy zsákutca, de amikor a kétségbeesés kezdett legyôzni minket, megláttunk egy furcsa emelvényt, benne egy kis foglalattal és egy képpel. Beletettem a bálványt a foglalatba és...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "A kôplatform néhány centivel lejjebb ment, és az egyik falról kiderült, hogy egy titkos átjáró. A bálvány az emelvényen belül maradt, nem sikerült visszahúznom. Végül egy hatalmas csarnokba értünk. Micsoda gyönyörû látvány!\nA legpompásabb építmény, amit valaha láttam. Faragványok a falakon, hatalmas szobrok... Átkutattuk az egész csarnokot, de nem találtuk nyomát sem kincseknek.";
			link.l1 = "Heh, ez bizony elég gyakran megesik a magunkfajtákkal. Rengeteg erôfeszítés, és a végén semmi eredmény...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "Nem volt hiábavaló. Hiszen egy trónterembe léptünk be, amelynek a végén egy óriási madárszobor állt. A szobor mellett misztikus fény volt, pont olyan volt, mint a bálvány fölötti fény éjfélkor. Közelebb mentünk, és egy gyönyörû repülô gömböt láttunk. Esküszöm, a színtiszta igazat mondom!\nEz valóságos volt, de ugyanakkor úgy éreztem, hogy nem az. Miközben gondolkodtam, Dannie - ó, az a vakmerô ördög, megérintette a gömböt. Az még fényesebben kezdett izzani, és végül a kezében egy apró tárggyá változott...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "Úgy tûnt, hogy szentségtörést követtünk el. A templom életre kelt: minden mozogni kezdett körülöttünk, a falak megremegtek, és minden összedôlt. Olyan volt, mintha felébresztettük volna az összes indiai démont, és azok minden haragjukat ránk zúdították volna...";
			link.l1 = "Hûha!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "Nehéz elhinni, tudom. De...";
			link.l1 = "Fél évvel ezelôtt még hazugnak neveztem volna. De elég régóta élek a Karib-tengeren ahhoz, hogy tudjam, nincs okom bizalmatlanságra. Folytassa. Hogy élted túl?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "Kirohantunk a templomból, és szerencsére még idôben feljutottunk a hajónkra. Utasítottam, hogy emeljük fel a horgonyt, minél elôbb el akartunk hajózni onnan.";
			link.l1 = "Heh! Szóval végül is csak valami furcsa ereklyét találtál kincsek helyett? Milyen szép és egyenértékû csere, he-he... És rájöttél, hogyan kell használni? Vagy használhatatlan volt?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "Várj egy pillanatot. A történetnek még nincs vége. Dannie-nél volt a lelet, és amint úgy döntöttünk, hogy bemegyünk a kabinba, hogy tanulmányozzuk, az ég elsötétült, és egy hajó bukkant fel. Ó, Istenem! Ez egy...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
		case "story_7":
			dialog.text = "... Maga Van der Decken!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Van der Decken? Hm...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "És ki ô?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "Nem hallottál még a Repülô Hollandiáról?";
			link.l1 = "Ki nem hallott még a Repülô Hollandiáról! Én már találkoztam egy hollanddal, és a kapitányát a tenger fenekére küldtem. Ô csak egy közönséges kalóz volt, aki a hajóját feldíszítette valami álcázott szeméttel, mint algák és szakadt vitorlák.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "Igen, de ez maga Van der Decken volt, a Repülô Hollandi kapitánya!";
			link.l1 = "Érdekes. Kérem, folytassa. Hogy sikerült átvészelnie?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "Eh-heh, barátom... Elsüllyesztettél néhány bolondot, de én az igazi Repülô Hollandiáról beszélek. Egy hatalmas hadihajó. Isten mentsen meg attól, hogy valaha is találkozz vele a nyílt tengeren. Van der Decken kapitányát és legénységét egykor arra átkozták, hogy örökké nyugtalanul hajózzanak a tengeren.\nEmlékszem a szakadt fekete vitorlákra, a fedélzeten álló halott emberekbôl álló legénységre, kihúzott pengével és magára a kapitányra - egy hátborzongató csontvázra, aki fekete kakasos kalapot viselt... Jézusom...";
			link.l1 = "Az igazat mondod?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "A Bibliára esküszöm, hogy nem hazudok... Egy találkozás a 'repülô hollanddal' csak a biztos halált jelenti. Erôs, nagyon erôs, egy sortûz az ágyúiból akár egy nehéz fregattot is elsüllyeszthet a legénységével együtt... de ami még rosszabb, hogyan harcolj az élôholtakkal?";
			link.l1 = "De te túlélted ezt a rémálmot!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "Mindez az én kedves Dannie-mnek és a templomból elvitt indiai leletnek köszönhetô. Megparancsoltam, hogy készüljünk fel a harcra, de tudtam, hogy itt a végállomás. A 'Flying Dutchman' felénk vitorlázott, és én láttam a rettenetes legénységét és magát Van der Decken-t a fedélzeten. A hajó elkezdte ránk irányítani az ágyúit, de...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "Dannie felemelte a leletet, és hagyta, hogy repüljön. Fogalmam sem volt, miért tette ezt. Mondott valamit a nôi megérzéseirôl... Az ereklye visszaváltozott izzó gömbbé, és felrobbant, súlyosan megrongálva a szellemhajót és demoralizálva a legénységet. Utasítottam, hogy nyissanak tüzet a hollandra.\nAz elsô sortûz megrázta ôket. Újra támadtunk, és másodszor is kilôttük a rothadó burkolatukat, pont mielôtt még ki tudtak volna lábalni az ereklye hatásából, és viszonozni kezdték a tüzet...";
			link.l1 = "Szóval mégis harcolni kellett ellenük?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "Hát persze. És esküszöm, ez volt életem legkeményebb harca. Az átkozott kádjuk alig maradt a víz felett, mégis képesek voltak elpusztítani a fél hajótestemet, mielôtt az égbe repítettük ôket azzal, hogy felrobbantottuk az átkozott porkamrájukat.";
			link.l1 = "Szóval elsüllyesztette? Elsüllyesztette a Repülô Hollandiát?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "Igen, a fenébe is! Elsüllyesztettem!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "Az az átkozott hajó elsüllyedt. A nap újra sütni kezdett, és az ég kitisztult. És végre boldogok lettünk... el sem tudod képzelni, milyen boldogok voltunk. Legyôztük magát a halált. Az ilyen pillanatok összehozzák az embereket. És megtettük azt, amit már régen meg kellett volna tennünk a találkozás elôtt - megöleltük egymást, megcsókoltuk egymást, kimondtuk, hogy szeretjük egymást, és megfogadtuk, hogy örökre együtt maradunk.";
			link.l1 = "És még mindig együtt vagytok...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "Igen, így van. Én és Dannie összeházasodtunk, és soha nem bántam meg. Ennél jobb feleséget és testvért nem találsz.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Szóval, most már végre tudom, hogy ki az a titokzatos kapitány, akinek sikerült elsüllyesztenie a 'Flying Dutchman', ... Te egy igazi hôs vagy!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "Akkor ti ketten igazi hôsök vagytok? Sikerült elsüllyeszteniük a híres szellemhajót. Várj! Azt mondtad, hogy a 'repülô holland' még mindig repül... Hogy lehetséges ez, ha a tenger fenekén fekszik?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "Eh, haver, te nem tudsz semmit... Elsüllyesztheted Van der Decken-t, de megölni nem tudod. Az átok rajta és a legénységén túl erôs, sokkal erôsebb, mint a halál...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "Lehet, hogy hôs vagyok, de Van der Decken-t nem lehet megölni. Az átok, ami rajta, a legénységén és a hajóján lóg, erôsebb a halálnál...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "Minden alkalommal, amikor elsüllyeszted a hajót, a legénysége megjavítja a hajóját, felemeli, és folytatja örök útját.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Tudom, Nathaniel, tudom. De a Repülô Hollandi többé senkit sem fog zavarni.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "Hát, tudod, ez úgy hangzik, mint egy mese. Megjavítani egy széthullott és elsüllyedt hajót...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "Az emberek sokszor látták a hajót, miután elsüllyesztettük... Ön dönti el, hogy elhiszi-e a látomásokat.";
			link.l1 = "És hol van az a sziget, ahol a templom található, ahonnan a leletet szereztétek?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "Térképezetlen, és valahol a Karib-tenger keleti részén található. Maroon Townban hagytam egy térképet a szigetrôl, de mint nagyon jól tudod, most nem tudok oda hajózni. És ôszintén szólva nem is akarok. Az egyetlen dolog, amire emlékszem, az a neve - Khael Roa...";
			link.l1 = "Milyen érdekes történet. Szeretném megtalálni azt a szigetet!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "Ó, azt nem ajánlom... Nem fogom még egyszer meglátogatni, az biztos.";
			link.l1 = "Azért én szívesen meglátogatnám... Rendben, köszönöm az érdekes történetet! Most már többet tudok a feleségedrôl. Mindketten élô legendák vagytok!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "Mire célzol, haver? Nem azt mondtam, hogy ôt nem lehet megölni?";
			link.l1 = "Nathaniel, elhajóztam Khael Roa-ba. És meglátogattam a Chavinok templomát, ahol te, Danielle és valami öregember negyedszázaddal ezelôtt jártatok. A leletet, amit akkoriban elvittél a templomból, úgy hívták, 'a felkelô nap koszorúja'. Ez a lelet volt az, ami felhívta rád a 'repülô holland' figyelmét. A kapitánya rajongott a Chavins mûtárgyakért.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "Jártál már Khael Roa-ban? De ez nem lehet! Az igazat mondod?";
			link.l1 = "Esküszöm. Amikor meséltél nekem a labirintusról és az óriásmadár szobráról, azonnal rájöttem, hol van az a hely. A karibi sámán, Tuttuathapak mesélt nekem a kalandjaitokról. Ô vezetett el arra a szigetre. Szent Kristóftól keletre található. Nagyon kicsi, gyûrû alakú. Körülötte sziklák vannak és egy kis öböl a belsejében. És csak egy benôtt ösvény vezet egy templomhoz, amely piramis alakban épült.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "Igen! Ez a Khael Roa. De miért mentél oda?";
			link.l1 = "Megszüntetni a Caleuche átkát... nos, a 'Repülô Hollandi'. Valójában a hajó neve 'Repülô Szív', volt, kapitányát pedig 'Balthazar de Cordes'. Ötven évvel ezelôtt megátkozta Yum Cimil, a halál indián istene. Fogtam Yum Cimil jáde koponyáját, amelyet Balthazar nemrég ellopott a templomból, és visszatettem a talapzatra, a kondor szobra elé...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...a koponya visszaszolgáltatásával megszüntettem a Caleuche átkát. És mivel két másik Chavin amulett is volt nálam, a sziget közelében megtámadott, pont úgy, mint ami akkor veled történt. De az átok nélkül Balthazar már nem volt halhatatlan, ahogy Tuttuathapak mondta. Szóval... a 'repülô Hollandi' nem létezik többé. Személyesen gondoskodtam róla.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "Mennydörgés és villámlás! Meg vagyok döbbenve! Te... Ugye nem viccelsz, öreg Nathan? Nem, látom a szemedben, hogy igazat mondasz! Te egy igazi hôs vagy!";
			link.l1 = "Hôs vagy sem, de én is megéltem már a magam kalandjait, ahogy te is. Nos, biztosan még sokszor fogunk beszélgetni a múltról, mert most már van egy közös témánk.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "Most már itt hagysz, barátom?";
			link.l1 = "Igen, Nathan. Kérlek, tarts ki, amíg vissza nem térek. Vigyázz magadra. És ami a legfontosabb, maradj életben, amíg vissza nem jövök, és minden rendben lesz. A Parti Testvériségnek szüksége van rád, Danielle-nek szüksége van rád.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "Dannie most már a csapatodban van? Könyörgöm, vigyázz rá. Semmit sem változott fiatalkora óta, még mindig fenegyerek, és nem habozik átmenni a poklon. Mondd meg neki, hogy nagyon szeretem...";
			link.l1 = "Persze, hogy megmondom. Együtt térünk vissza érted, ezt megígérem neked, Nathan. Tarts ki, és emeld fel a fejed. Ole majd vigyáz rád. Hamarosan találkozunk!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "Á, te vagy az, "+pchar.name+". Még nem hagytad el a szigetet?";
			link.l1 = "Ne aggódj, Nathan, minden a terv szerint halad. Pihenj most.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "Danielle! Dannie! Az én Dannie-m!";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "Köszönöm, barátom. Köszönök mindent, és különösen az én Dannie-mnek...";
			link.l1 = "Szívesen, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "Nézd csak, ki ugrott be! Maga a "+GetFullName(pchar)+"  ! Gyere be, gyere be, barátom! Hogy vagy?";
			link.l1 = "Jól vagyok. És te, Nathan? Látom, hogy nem maradt semmi komorság. Jól nézel ki. Kígyószem nagyon jól csinálta!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Igen, a sámánod csodatevô. Még jobban érzem magam, mint azelôtt az átkozott teleportálás elôtt! Úgy érzem magam, mintha tíz évvel fiatalabb lennék! "+pchar.name+", nagyon sokat köszönhetek neked. És le vagyok nyûgözve: segítettél egy vadidegen emberen, átmentél az átkozott portálon, megragadtál a halál kezébôl, visszavittél a feleségemhez!\nÉs még ennél is több! Visszahoztad nekünk a hajónkat és az otthonunkat. Mostantól te vagy a legjobb barátunk. Örökre. Ha valaha is szükséged lesz valamire - tudod, kitôl kérdezz! Maroon Town mindig védelmet, támogatást és menedéket nyújt neked, ha szükséged van rá.\nAz egész falu harcol érted, ha veszélyben vagy. Békés idôkben itt barátságot, a legjobb rumot, puha ágyat és finom pihenôhelyet találsz. Dannie és én gondoskodunk róla.";
			link.l1 = "Köszönöm, báró! Ôszintén örülök, hogy jó egészségben és... Dannie-vel látom.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "Már vártam a látogatásodat, "+pchar.name+", és készítettem egy ajándékot - egy ritka és erôs fegyvert. Lehet, hogy egy nap számos ellenséget kell majd egy lövéssel leterítened, és ez a kézi aknavetô segít ebben. 'Sclopetta' különleges gránátokat lô ki, ezért elkészítettem az elkészítésükhöz szükséges utasításokat is. Tessék, fogd meg!";
			link.l1 = "Micsoda kiváló fegyver! Köszönöm!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("Kaptál egy kézi mozsarat");
			Log_Info("Kaptál egy gránátos utasítást");
			PlaySound("interface\important_item.wav");
			dialog.text = "Látogasson meg minket gyakrabban, "+pchar.name+"! Dannie és én bármikor szívesen látunk titeket.";
			link.l1 = "Öröm lesz számomra. Számítsatok arra, hogy hamarosan találkozunk!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "Ah, barátom "+GetFullName(pchar)+"! Jelentkezzen, jelentkezzen, kapitány! Hogy van? Segítségre van szüksége?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "Nathan, nagyon fontos ügyben jöttem hozzád. Emlékszel, amikor az Elhagyott hajók szigetén azt mondtad, hogy Dannie-vel belopóztatok egy indián templomba, és elsüllyesztettétek a 'Flying Dutchman'?";
				link.l2.go = "caleuche";
			}
			link.l1 = "Köszönöm, jól vagyok. Csak látni akartalak titeket.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "Persze, hogy emlékszem.";
			link.l1 = "El kell jutnom arra a szigetre a templommal. Nagyon meg kell találnom. Azt mondtad, van egy térképed róla. Meg tudod mondani a koordinátákat?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Ó, barátom, ez egy nagyon veszélyes vállalkozás, tudod... Khael Roa temploma el van átkozva. Ha tudnád, ki lakik a folyosóin...";
			link.l1 = "Jelenleg sokkal félelmetesebb szörnyek lakják, mint amiket akkoriban láttál. És én még mindig oda fogok menni.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Nem bocsátom meg magamnak, ha ott pusztulsz el. "+pchar.name+", könyörgöm neked: hagyd abba ezt a vállalkozást! Különben is, ott látják leggyakrabban a 'repülô hollandot' ...";
			link.l1 = "Én már találkoztam vele, és tudom, hogyan lehet elmenekülni elôle. Nathan, kérlek, add meg nekem Khael Roa koordinátáit, és mondj el mindent, amit tudsz arról a templomról, azon kívül, hogy élôhalott indiánok lakják.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Ó, nos... Nem utasíthatom vissza, de... fogalmad sincs, mit tapasztaltunk Dannie-vel! Khael Roa Antiguától keletre található. A térképét rögtön megtaláltam, amikor visszatértem Maroon Townba, a... (néz) the coordinates: 19 fok 32' észak, 62 fok 25' nyugat.";
			link.l1 = "Leírom a helyét a naplómba... Köszönöm, Nathan!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Késôbb megköszönheted. Most a részletek. Khael Roa szigete egy sziklagyûrû, benne egy öböllel. Keressétek az átjárót a sziklák között - ott elég mély. Az öbölben horgonyt kell vetni, és a parton kell partra szállni. Keressetek egy régi ösvényt, amely a sziget mélyére vezet - ott csak egy van. Ez egy indiai piramishoz vezet - ez az a templom, amit keresel.\nA sziget maga csendes, de a templomban hemzsegnek a legkülönfélébb förtelmek. A bejárat a piramis tetején található. Odabent három átjáró lesz; a középsôt kell választanod. Ezután végigsétálsz a folyosón, és egy emelvényt találsz, ahol négy be- vagy kijárat van. Itt támadtak rám elôször a templomi lények, úgyhogy legyetek óvatosak.\nAztán egy labirintus következik. Nagyon bonyolult, és én az életemre esküszöm, nem emlékszem a helyes útvonalra. A labirintusban rengeteg csúnya lény van. Mindet meg kell ölni, majd fel kell menni egy csarnokba, ahol két bejárat, hat oszlop és egy emelvény van kilenc kôlapokkal. Ez a szentély elôcsarnoka. A kôfala zárva van, és fogalmam sincs, hogyan fogod kinyitni.\nVan valami mechanizmus, de esküszöm, fogalmam sincs, hogyan mûködik! Egy bálványt használtam kulcsként. Beszúrtam a központi lemezbe, és az ajtó kinyílt. De neked nincs ilyen bálványod, úgyhogy neked kell kitalálnod, hogyan mûködik ez a mechanizmus.";
			link.l1 = "Rendben, mindent megteszek, hogy rájöjjek. Mi a helyzet a szentéllyel?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "A szentély egy hatalmas terem, nagyon magas mennyezettel és nagy kôlépcsôkkel. Ezeket nem lehet használni - túl öregek és nagyrészt szétesett állapotban vannak. De a templom építôi, úgy tûnik, nagy varázslók is voltak. Vannak portálok, mint Kukulcané, és ezek egyik helyrôl a másikra visznek.\nEzeket könnyen felismerheted - úgy néznek ki, mint a színes örvények. Az elsô emeleten két portál lesz, de az egyik csapda, úgyhogy légy óvatos! A megfelelô portál a második emeletre visz. Ott meg kell találnod egy másik portált, hogy még magasabbra juss, majd egyenesen a templom szívébe!\nAhol, a nagy madárszobornál volt elhelyezve az a mágikus ereklye, amit én és Dannie magunkkal vittünk. És már elmondtam, mi történt ezután.";
			link.l1 = "Emlékezni fogok arra, amit most elmondtál. Köszönöm, Nathaniel. Nagyon sokat segítettél nekem.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Vigyázz magadra, "+pchar.name+". A labirintus és a templom csarnokai tele vannak veszélyekkel. Elég egy rossz mozdulat, és biztos, hogy örökre ott maradsz.";
			link.l1 = "Praemonitus praemunitus, barátom. Elôre figyelmeztettek, ami azt jelenti, hogy elôre megfélemlítettek. Most mennem kell. Viszlát!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Sok sikert, "+pchar.name+"!";
			link.l1 = "Köszönjük!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
