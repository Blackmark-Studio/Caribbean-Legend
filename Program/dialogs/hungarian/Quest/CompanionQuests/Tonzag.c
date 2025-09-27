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
			dialog.text = "Mit akarsz?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		case "startoff":
			dialog.text = "De Mor kapitány! Üdvözöllek Tortugán!";
			link.l1 = "Jó napot, hadnagy. Élvezik a kilátást a tengerre a barátaival?";
			link.l1.go = "startoff_joke";
			link.l2 = "Vissza, hadnagy.";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "Kapitány, a hírneve megelôzte, és a felettesek úgy döntöttek, hogy szerveznek egy kis túrát a mi kedves Tortuga-szigetünk szépségeihez. Azonnal kezdjük - a város börtöncelláival. A tisztjei is meghívást kapnak.";
			link.l1 = "Hadnagy úr, én nem valami rühes csempész vagyok, akit a parton fogott el. Ne viccelôdjön, kérem. Magyarázza el a dolgokat rendesen.";
			link.l1.go = "startoff_joke_1";
			link.l2 = "Akkor ne vesztegessük az idôt! Mutassa az utat, hadnagy!";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "Látom, hogy a magukkal való bánásmód, matrózok, más megközelítést igényel. Katonák, készüljetek a csatára! De Maure kapitány, ön és a tisztjei letartóztatva. Adják át a fegyvereiket!";
			link.l1 = "Adhatok egy golyót... hová tegyem, hadnagy úr? Veletek, szárazföldi patkányok, nincs más lehetôség.";
			link.l1.go = "startoff_silence_1";
			link.l2 = "Milyen törvény szerint? Ha vérontás nélkül akar letartóztatni egy fegyveres csoportot, hadnagy úr, akkor jobban kell próbálkoznia.";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = "Számomra mindannyian egyformák vagytok... Sajnálom, de nem lesz magyarázat, kapitány. Fentrôl jött parancs. Adják le a fegyvereiket, ha lennének olyan kedvesek.";
			link.l1 = "Nincs szükségem bajra... most nem. Tegye, amit mondanak.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "Uh... azt hiszem, nem egészen értettél meg. Kapitány, maga és a tisztjei le vannak tartóztatva! Adják le a fegyvereiket és jöjjenek velünk!";
			link.l1 = "Nincs szükségem bajra... most nem. Tegye, amit mondanak.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "Még egy szó, kapitány, és itt temetjük el. Fegyvereket a földre, azonnal!";
			link.l1 = "Nincs szükségem bajra... most nem. Tegye, amit mondanak.";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "Nem félek a vértôl, kapitány. Még ha csodával határos módon túl is éli, soha többé nem teszi be a lábát Tortugára. És a katonai hírszerzésünk úgy véli, hogy önnek nagyon fontos, hogy hozzáférjen ehhez a szigethez.";
			link.l1 = "Nincs szükségem bajra... most nem. Tegye, amit mondanak.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Kapitány, a dolgok szarul állnak! Az ellenség szorosan fogva tart minket, attól tartok, nem engednek el, amíg meg nem halunk! Az embereink most nagy bajban vannak, és az ágyúszemélyzet nagy része kiesett!";
			link.l1 = "Segítek nekik. Vedd át a parancsnokságot és vigyél ki minket innen!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Igenis, uram!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Gyôzelem, kapitány! A partraszálló csapat megsemmisült, az ellenség a visszavonulást választotta, és dél felé vette az irányt. A hajó állapota elfogadható. A legénység él: " + GetCrewQuantity(pchar) + " emberek. Jelentés elkészült!";
			link.l1 = "Köszönjük! Rumot mindenkinek és erôsítsétek az ôrséget, amíg elérjük a kikötôt!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Hurrá! Aye aye!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "És itt van maga az ember! Látta a kinti véres mészárlást? Ez mind a te mûved, áruló! De mindenért felelni fogsz: Porto Bellóért, Gruohért és ezért a bányáért!";
			link.l1 = "Várj, ez meg mit jelent...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "Ááá! Ez nem sok jót ígér...";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "San Santiago, vigyázz rám! Gazember! Miféle szörnyeteg képes ilyet elkövetni? Válaszoljon, senor!";
			link.l1 = "Nyugodjon meg, senor! Elôször mutatkozzon be! Igen, szörnyû mészárlás történt itt, de akik elkövették, már halottak. Én személyesen 'dekoráltam' a maradványaikkal a bányákat...";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "A " + GetFullName(npchar) + "vagyok, a királyi Los Teques bánya fômérnöke. Éppen most tértem vissza egy több hónapos kiküldetésbôl, és... mit látok! Ami itt történt, az Isten és az emberiség elleni bûntett, ezért arra kérem önöket, hogy azonnal adják le a fegyvereiket. A caracasi hatóságok kivizsgálják ezt a gazemberséget!";
			link.l1 = " Nem tudok engedelmeskedni, senor, és esküszöm, semmi közöm ehhez a mészárláshoz! De ha nem hagyja abba, a saját teste is a halomra kerül.";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "Nem félek a haláltól, de mindig tudom, mikor kell visszavonulni. Menjen, de ne feledje, jelenteni fogom, mi történt itt, és nem hagyok ki egyetlen részletet sem!";
			link.l1 = "Ebbe nem tudok belemenni, senor. Sajnálom, hogy idáig fajult a dolog. A csatára!";
			link.l1.go = "mine_head_fight";
			link.l2 = "Úgy tûnik, a halált keresi, senor. De ma senki más nem fog meghalni. Elmegyünk, és remélem, ez a részlet is bekerül a jelentésébe!";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "Mit tegyünk a fogollyal, kapitány?";
			link.l1 = "Semmi különöset, csak ne hagyják meghalni vagy megszökni.";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "Igenis! Gondolom, nem kell részt vennem a mai kihallgatáson, kapitány?";
			link.l1 = "Miért ne? Miért ne? Úgy döntött, hogy szakmát vált, Alonso?";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "Ha-ha, nem, kapitány. Imádom ezt a munkát, de úgy tûnik, új mestere van a fedélzeten!";
			link.l1 = "Hercule? Honnan jött ez az ötlet?";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "Nos, kapitány úr, az öreg csak erre az alkalomra hozta a szerszámkészletét, és használatba vette. Nekem még az enyémet sem kell elôvennem. Ha!";
			link.l1 = "Értem... Ahogy mondtad!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "Ah... Charles de Maure. Engedje meg, hogy bocsánatot kérjek az egész Liga nevében. Túl késôn kaptuk meg a parancsot, hogy hagyjuk békén. A szervezetünknek nincs követelése önnel szemben, kapitány. Ami ezt a kopasz állatot illeti... Ugh! Amíg a pórázon van, biztonságban van, de azt tanácsolom, hogy ne tartsa meg, és hagyja a csatornában rohadni, ahová való!";
			link.l1 = "Köszönöm az ajánlást, de engem jobban érdekel, hogy miért véd meg valaki a zsoldosaitól.";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "Nem tudhatom, kapitány. Gondolom, az utasítás az új patrónusunktól jött. Hallottál már róla, áruló? A Liga újra a csúcson van!";
			link.l1 = "És ki ô?";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "Nem tudhatom, kapitány, és még ha tudnám is, ilyen dolgokat nem árulunk el.";
			link.l1 = "Ebben az esetben mondj valami mást, és mehetsz, ahová akarsz. A szavamat adom.";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "Csak így? Rendben, kapitány, tegye fel a kérdéseit, és engedjen el. Ígérem, hogy nem térek vissza a Ligához, még ha meg is tehetem.";
			link.l1 = "Miért van ennyire rátapadva Hercule-ra? Túl sok a baj egy dezertôrért.";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "Mit mondtál neki, te kutya? Nem minden az, aminek látszik, kapitány! A Liga állandóan mozgásban van, a kódok változnak, a munkaadók változnak. El akarsz menni? Persze! A kijárat csak a fôtisztek elôtt van lezárva, és ez a söpredék sosem volt az. A felesége, persze, de túlságosan tiszteltük Madame Tonzagot ahhoz, hogy ne tegyünk kivételt vele.";
			link.l1 = "Akkor miért?";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "Volt egy dolog, Porto Bello... Nagy volt. Tudja, a barátja nem csak úgy elment, nem csak úgy megszegte a szerzôdést, nem csak úgy megölte a csoportot, amelyik azért jött, hogy befejezze a munkáját. Valóságos mészárlást okozott az utcákon, jelentôsen megnehezítve a kapcsolatunkat a kasztíliaiakkal. Egy ritka kalózrajtaütés is akkora rémületet kelt, mint amit a jó katolikusok azon a napon átéltek. A pokolba is, talán még le is nyûgözött volna, ha valaki más csinálja.";
			link.l1 = "Egy újabb mészárlás? Milyen érdekes. Folytassa.";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "A Társaság akkori igazgatóhelyettese, Rodenburg közbelépett. Valahogy sikerült elhallgatnia az egész ügyet, de csak azután, hogy sok legjobb emberünket elvesztettük a spanyol büntetôakciók miatt. Egy kis idô elteltével azonban ismét üzletet kötöttünk velük... Áh! De mi semmit sem felejtettünk el, és amint alkalom adódott rá, megpróbáltunk bosszút állni. Az egésznek a felbujtóját, Tonzagot meg kellett ölni.";
			link.l1 = "Ez nem sikerült. Mi van a bányával?";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "Kénytelenek voltunk megtenni. Megszabadulni attól a söpredéktôl túl sokba került; aranyra volt szükségünk. Mindez miatta... De a merényletkísérlet kudarcot vallott, és visszatértem Los Tequesbe, hogy rendet tegyek egy kicsit... Hogy találtad ki, hol keressük?";
			link.l1 = "Nem számít. Találkoznom kell a vezetôddel. Személyesen akarom rendezni a félreértést, mivel a titokzatos pártfogótok garanciái bármelyik pillanatban lejárhatnak.";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "Biztos vagyok benne, hogy már várják önt Caracasban, kapitány. Látja, semmit sem titkolok maga elôl.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "Arno parancsnok meghalt, most Austin a fônök.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "Minden kérdésére válaszoltam, kapitány. Tartsa meg a szavát.";
			link.l1 = "Elengedem magát. Szálljon le a hajómról, és imádkozzon, hogy ne várjon rám csapda Caracasban.";
			link.l1.go = "captive_spare";
			link.l2 = "Köszönöm az érdekes beszélgetést. Az, hogy Hercule-t mészárlással vádolja, azok után, amit a bányában láttam, egy kicsit sok volt. Menjen a pokolba, ahová tartozik.";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "Uraim, meghívom önöket egy találkozóra. A templomban várják önöket, így a biztonság garantált.";
			link.l1 = "Ez gyors volt...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "Charles de Maure. Hercule. Nem fogsz innen élve távozni.";
			link.l1 = "Mindig szépen kezdôdik egy beszélgetés. Tényleg szükséged van erre az egészre?";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "Magával, kapitány, a dolgok nem egészen egyszerûek. Tudja, az új patrónusunk ragaszkodott hozzá, hogy hagyják magát békén... és feldughatja a kéréseit a seggébe! Nagyon utálom a fajtádat! Vitorlázol a szép, fehér vitorláid alatt, azt hiszed, hogy a jég nem olvad el a szádban. De amikor a pengém lopása belétek hatol, mind sikoltoztok, mint a lányok. Ezt imádni kell, Charles, hadd mondjam el neked! Rég nem csináltam már ilyet... és most itt vagy elôttem, szépfiú.";
			link.l1 = "Beteg vagy, haver.";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "Nem, nem engedhetlek el. A barátoddal viszont még sokkal egyszerûbb a helyzet - a fiaimnak nincs szükségük rá, de még mindig van néhány régi, mérhetô ligás pallosa, akik nincsenek egészen meggyôzôdve módszereim hatékonyságáról... Túlságosan is tisztán dolgozott, a tiszta dublónokért, a tiszta Társaságtól. De én tudom, mi az, ami megváltoztatja a véleményüket - egy merész bûnös fejét tálcán, ha-ha!";
			link.l1 = "Rossz helyszínt választottál erre, te bolond. Tényleg egy templomban akarsz csatát kezdeni?";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "Persze, miért ne? Rosszul érzed magad a nép miatt? Lehet, hogy nem lesz olyan jövedelmezô, mint Los Tequesben, de attól még jól fogjuk érezni magunkat. Lefestjük Isten házának falait, ah-ha! Kapitány, maga gondoskodik a festékrôl.";
			link.l1 = "Értem. Irigykedsz ránk, ugye, te ôrült patkány? Irigyled a szabadságunkat? Hogy a lányok örülnek, ha látnak minket, és hogy a zsebünkben csörögnek az érmék? Nézz magadra: hol ástak ki titeket a patrónusok, te disznó? Ki engedett be a templomba?";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "Egyél mocskot, te kis szarházi!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
} 
