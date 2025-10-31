void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "Üdvözlöm szerény hajlékomban! Christian vagyok. Christian Deluce, szolgálatára. Mi szél hozta a küszöbömre?";
			link.l1 = "A név a kapitány "+GetFullName(pchar)+". Jelentôs mennyiségû szeszes italt szeretnék beszerezni. Bízom benne, hogy érthetô a jelentésem?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "Micsoda? Micsoda? Ki terjesztene ilyen hazugságokat? Ez egy súlyos félreértés, biztosíthatom önöket! Én nem kereskedem semmiféle szeszes itallal!";
			link.l1 = "Nocsak, nocsak... Úgy tûnik, megtaláltam azt, akit keresek.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "Ó, egek, nem-nem-nem! Micsoda vádaskodások! Szellemekkel kereskedik? Én? Én... Én csak, ööö, vagyis... Rendben, bizonyos italok birtokában vagyok, de mind teljesen törvényes! Én csak frissítôket szerzek magánszemélyeknek, ah... ünnepségekre és szerény társadalmi összejövetelekre!";
			link.l1 = "Miért ilyen reszketeg, jóember? Nem börtönôrként, hanem jótevôként jöttem. Az ön vagyona emelkedhet, és az én erszényem néhány dublonnal gyarapodhat az alku során.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Én? Ideges? Nevetséges! Mi okom van az idegességre? Makulátlan ember vagyok - a lakásom a kormányzó rezidenciájának árnyékában áll! Semmilyen törvényt nem szegek meg, becsületemre mondom!";
			link.l1 = "Szóval nem foglalkozik szeszkereskedelemmel? Valóban szörnyû szégyen. A jelentôs haszon lehetôségével érkeztem. Olyan dublonokat, amilyeneket egy szerény titkos kereskedô aligha tudna elképzelni. De mivel maga nem az én emberem, nem zavarom tovább, és megyek tovább. Hacsak...?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "Á... várjon egy pillanatot... "+GetAddress_Form(NPChar)+"... bocsásson meg, az eszem szétszóródik, mint a sirályok a viharban, egészen elfelejtettem az ön elôkelô nevét.";
			link.l1 = "Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", az igazat megvallva, én... vagyis... talán tudom, hogy hol van az ön által keresett személy. Továbbíthatnám ennek a személynek... az ön nagylelkû ajánlatát.";
			link.l1 = "Továbbítani? Biztosan viccel. Tényleg azt hiszi, hogy ilyen kényes ügyek felesleges kezekbe kerülhetnek?";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "Igazat beszél. De... az ég segítsen meg... a kocka el van vetve... igen, valóban én vagyok az embere.";
			link.l1 = "Most már értjük egymást, Christian. A kocsmának súlyos szeszhiánnyal kell szembenéznie, és úgy vélem, mindketten jól járunk ezzel a helyzettel.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Kapitány, jól ismerem a fogadós gondjait. A népek már az ajtóm elôtt járnak, és félelemmel tölt el, hogy folytassam szerény kereskedésemet - túl sok szem figyel mostanában. Azt reméltem, hogy talán ön... nos, egy olyan ember, mint ön, talán...";
			link.l1 = "Miért nem keresed meg te magad a fogadós urat az áruddal?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "Ô... inkább egy leprást ölelgetne, minthogy velem üzleteljen. Az a nagyképû bolond csak lenézi a magamfajta szerény kereskedôket.";
			link.l1 = "Valóban, a hírneve megelôzi ôt. Lehet, hogy egyenesen megveti a kínálatodat. De rajtam keresztül bemutatva - az egészen más kérdés.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "Felajánlod magadat közvetítônek? Ezt a megállapodást nagyon is elfogadhatónak találom... Nemrég szereztünk be egy figyelemre méltó méretû szállítmányt - ilyen mennyiséget még sosem sikerült! A pincéim legalább egy fél évre elegendôek lennének. De a Mindenható Isten kegyelmébôl, csak hajszál híján úsztuk meg a lebukást\nMég mindig nem értem, hogyan csúsztunk át a kormányzó hálóján. A sorsot kétszer ilyen módon megkísérteni nem lenne más, mint önpusztítás.";
			link.l1 = "Akkor talán 'tt az ideje, hogy kilépj a fényre. Nem teljesen, de eléggé ahhoz, hogy kevesebb veszéllyel járjon.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "L-lépni a fénybe? De... ahhoz hatalmas barátok kellenek! És jelentôs pénzre! És mi célból? Te, egy tengeri kapitány, akinek saját hajója van, bizonyára nem akarsz végleg lehorgonyozni, és egyszerû kocsmárosnak állni?";
			link.l1 = "Ami a kapcsolatokat illeti, az én hatóköröm oda terjed, ahová a tiéd nem. Ami a pénzügyeket illeti... a befektetés szerénynek fog bizonyulni. És az utolsó aggodalmadra - ne félj. Ezekben az ügyekben az én ügynökömként fogsz tevékenykedni. Én leszek a pajzsod, te pedig az állandó forrásom. Megállapodásunk tartós és kölcsönösen jövedelmezô lesz. Ön megbízható vásárlót szerez, én pedig megbízható árut. Mit szólna egy ilyen vállalkozáshoz?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "Biztos voltam benne, hogy ez valami bonyolult csapda. De az igazság az, hogy az ajánlata... nagyon csábítóan hangzik. Stabilitás, megbízhatóság... Soha nem gondoltam volna, hogy ilyen szerencse rám mosolyog. "+GetSexPhrase("Monsieur","Mademoiselle")+", teljes szívembôl egyetértek! Milyen mennyiséget kíván vásárolni?";
			link.l1 = "Elôször is alapozzuk meg a kereskedelmét, aztán megbeszéljük a részleteket. Mennyi rum és bor van jelenleg a raktárában?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "Ebben a pillanatban? Ah... Talán meg kellene néznünk a pincémet, ahol pontos elszámolást adhatnék a készleteimrôl.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Lássuk csak... Milyen kincsek rejlenek odalent? Ah igen\nA jelenlegi készletem pontosan száz üveg finom rumból és száz üveg kiváló borból áll.";
			link.l1 = "Mondhatom, ez egy tisztességes kezdet. Ha már rendeztük a behozatali nehézségeit, tudna ilyen szállítmányokat minden hónapban biztosítani?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "Természetesen, kapitány úr! Nem, háromszor, nem, nem... négyszer ekkora mennyiséget is el tudnék látni! Nem lesznek késedelmei - mindig bôséges tartalékot tartok fenn, biztosítva, hogy minden szerencsétlenséget gyorsan leküzdhessünk anélkül, hogy az önök ellátását befolyásolná.";
			link.l1 = "Nevezze meg az árat ezért a szállítmányért.";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "A tisztességes fizetségnek a következôt tartanám: tíz dublont tíz üveg borért és három dublont tíz üveg rumért. Összesen százharminc dublont a teljes rakományért.";
			link.l1 = "Rendben. Tárgyalni fogok a kocsmárossal, és azonnal visszatérek.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Kapitány, mi újság? Hogy ment a beszélgetés a fogadósokkal?";
			link.l1 = "Még nem beszéltem vele. Az lesz a következô állomásom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "Hogy ment, kapitány? Sikerült megegyeznie a fogadósával?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Csodálatosan sikerült, Christian. Megveszi ezt és minden további szállítmányt kétszáznegyven dublonnáért. Az elsô szállítmányért kifizetem neked a kért százharmincat, a többit pedig megtartom jutalomként. A jövôbeni nyereség azonban teljes egészében a tiéd lesz.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "Jól csináltam, Christian. Kétszáz dublonnáért megveszi ezt és a következô szállítmányokat. Az elsôért kifizetem neked a kért százharmincat, a különbözetet pedig megtartom méltányos jutalomként. A jövôbeni nyereség csak a tiéd.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "Ez megdöbbentô hír, kapitány! Álmodni sem mertem volna ilyen üzletrôl - köszönöm! De... talán túl gyorsan cselekedett? A kormányzó... Én... vagyis...";
			link.l1 = "A kormányzó tisztában van vele. Mostantól kezdve havonta száz dublont fogsz fizetni, és megfelelô kereskedelmi jelentéseket fogsz benyújtani.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "Hihetetlen! Hogy sikerült, kapitány? A kormányzó egy szigorú ember, és a feketekereskedôk ádáz ellensége...";
			link.l1 = "Ez az, Christian - ô a tiltott kereskedelem ellen van, nem a tisztességes üzletelés ellen. Meghallgatott, és világos feltételeket szabott a szigeten folyó szeszkereskedelemre. Mostantól az én nevem alatt fog mûködni. Bármilyen vétségért én is ugyanúgy viselem a terhet, mint te. Szóval ne hagyj cserben, különben még a túlvilágon is levadászlak.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "Esküszöm, kapitány, ezt nem fogja megbánni!";
			link.l1 = "Most a fogadósnál kell elintéznünk a dolgokat, és utána rendezzük a megállapodásunk részleteit.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Természetesen, kapitány. Készen állsz arra, hogy most azonnal átvedd a szállítmányt? Ez százharminc dublont jelent.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Igen, itt vannak a dublonok.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Jelenleg nem rendelkezem a szükséges pénzzel. Maradjon itt - visszatérek a fizetséggel.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "Kapitány! Visszatért az áruért? Az ár továbbra is százharminc dublon.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Valóban így van! Itt a fizetség.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Sajnálatos módon, még mindig nincs meg a pénz. Késôbb újra hívni fogom.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "Nagyon hálás vagyok! Fogja ôket! Száz üveg bor és száz üveg rum, ahogy ígértem.";
			link.l1 = "A legénységem gondoskodik a rakományról. Addig is, beszélnem kell a fogadós úrral.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! Olyan gyorsan visszatértél! Mondd, kedvezôen alakult a megállapodásunk?";
			link.l1 = "Minden a legcsodálatosabban alakult, Christian. A kocsmáros havonta kétszer azonos szállítmányt kér. Folyamatosan szállítsd a szeszes italokat a létesítményébe, és hamarosan búcsút mondhatsz a hiány fogalmának.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "Kapitány... te... 'tis mintha maga a Gondviselés vezette volna a küszöbömhöz! Valóságos csoda bontakozott ki elôttem - alig merem elhinni a szerencsémet! Milyen tettemmel érdemeltem ki ezt a jóindulatot? Szavakkal nem tudom kifejezni hálámat!";
			link.l1 = "Én azonban felvilágosíthatlak, Christian. Minden hónapban a legfinomabb árucikkeid egy kiválasztott részét kizárólag az én megvásárlásomra tartogatod, és nem kínálod más vevônek. Az általad meghatározott árakon fogom megvásárolni - tíz dublont minden tíz üveg borért és három dublont minden tíz üveg rumért.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "Nagy örömömre szolgálna, "+pchar.name+", hogy árut különíthetek el az Ön kizárólagos beszerzésére! Becsületemre legyen mondva, soha nem fog hiányt szenvedni tôlem! Milyen mennyiségre van szüksége? Ötven üveggel? Talán száz? Mondjon bármilyen összeget, amennyit csak akar!";
			link.l1 = "Az ilyen mennyiségek meghaladják a jelenlegi igényeimet. Húsz üveg mindegyikbôl tökéletesen elegendô. Ha az igényeim növekednének - azonnal értesíteni fogom.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "Természetesen, természetesen! Akkor megegyeztünk - húsz üveg bor és húsz üveg rum huszonhat dublonért. Minden hónap tizenötödik napján az áru várja, hogy átvegye. Szívesen látom nagyrabecsült jelenlétedet, amikor csak meglátogatsz, még ha csak udvariaskodni is akarsz velem!";
			link.l1 = "Pompás! Még egy utolsó dologra kell felhívni a figyelmet, Christian. A hírnevemet a becsületességedre tettem fel. Ne hagyj cserben, nehogy rájöjj a következményekre.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "Én... mit javasol, kapitány... biztosan ön... nem-nem, soha nem fogok csalódást okozni! Mindent kifogástalanul fogok csinálni, a lelkemre esküszöm!";
			link.l1 = "Aztán amíg az útjaink még egyszer keresztezik egymást!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "Te kotnyeles "+GetSexPhrase("kurva","kurva")+"! Soha nem tanították meg neked, hogy ha beleavatkozol a nem a saját ügyeidbe, az csak szerencsétlenséget hoz?";
			link.l1 = "’Te voltál az, aki kéretlenül rátelepedett a hajómra, és most azzal mersz vádolni, hogy beavatkozom? Teljesen eluralkodott rajtad az ôrület?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "Dörgés robbantsa az elôárbocomat! Szóval te, "+GetSexPhrase("nyomorult kölyök","hitvány kurva")+", fogalmad sincs arról, hogy milyen ügyekbe keveredtél? Azt képzelted, hogy a kocsma készletei csak úgy véletlenül eltûntek?";
			link.l1 = "Te vállalod a felelôsséget azért, hogy a szeszfôzde hamuvá vált?";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "Ha-ha, végre az igazság áthatol a vastag koponyádon, a lánglövés hasítsa át a belemet! ’Tényleg az én mûvem volt! Az a szállító túl mélyre süllyesztette a gyökereit a kereskedelemben. De amint látod, én mindig legyôzöm a riválisaimat. És te is osztozni fogsz a sorsukban, a grapeshot szalagokra tépheti a vitorláimat!";
			link.l1 = "Nagyon mulatságos. Nos, akkor derítsük ki, mennyire vagy képes, Neptunusz vadállatai lakmározzanak a tetemeden! Ha-ha!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "Üdvözlet, "+pchar.name+"! Milyen kedvezô szelek vittek a küszöbömig?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Jó napot, Christian. Elôkészítetted az árumat?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Jó napot, Christian. Csak azt akartam, hogy az ügyeid kedvezôen alakuljanak. Most már nem zavarlak tovább.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Természetesen, kapitány! A legcsekélyebb bizonytalanság is felmerülhet a szorgalmamat illetôen?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Egy pillanatig sem, Christian. A fizetséged, ahogy megbeszéltük. Most már elviszem a pezsgômet.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "A legkevésbé sem. Sajnos, az erszényem jelenleg kényelmetlenül könnyûnek tûnik. Visszatérek, ha jobban fel vagyok szerelve.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Természetesen, kapitány! A legcsekélyebb bizonytalanság is felmerülhet a szorgalmamat illetôen?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Egy pillanatig sem, Christian. Itt vannak a dublonjaid, ahogy megbeszéltük. Most már birtokba veszem a szellememet.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "A legkevésbé sem. Sajnos, jelenleg megfelelô fizetség nélkül vagyok. Visszatérek, ha az erszényem megfelelôen megtömve lesz.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, szeretném növelni az állandó rendelésemet. Havonta száz üveg rummal és borral, hogy pontos legyek.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, szeretném átgondolni a megállapodásunk kiterjesztését.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Nagyszerû. Mint mindig, a friss készlet várja, hogy tizenötödikén örömmel fogadjon. Alig várom a következô látogatását.";
			link.l1 = "Számíthatsz a visszatérésemre. Amíg az útjaink újra keresztezik egymást.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "Kapitány, bár egy ilyen bôvítés nagyon örvendetes lenne az üzlet számára, 'tis not without considerable expenses! A nagyobb mennyiség további munkásokat igényel, megnövelt raktárakat, tágasabb hajók bérlését... Megfelelô beruházás nélkül nem tudnám biztosítani az ilyen jelentôs megrendelések idôben történô kiszállítását.";
			link.l1 = "És mekkora összeget igényelnek ezek a megállapodások? Milyen beruházás garantálná a kibôvített vállalkozás zökkenômentes mûködését?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Ötvenezer peso elég lenne. Minden további költséget a saját kasszámból állok.";
			link.l1 = "Ötvenezer? Istenemre esküszöm... ez nem csekély összeg. Tényleg nem tudna ennél szerényebb finanszírozással is boldogulni?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "Mélységesen sajnálom, kapitány, de ragaszkodom hozzá, hogy ez az összeg a minimum. Ha spórolunk, a vállalkozásunk... mondjuk úgy, katasztrofálisan letérhet a helyes útról. Egy ilyen szerencsétlenség nem szolgálná sem az ön, sem az én érdekeimet, megkockáztatom.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Itt van a teljes összeg. Gondoskodj róla, hogy méltónak bizonyulj a bizalomra, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Ha jobban belegondolok, Christian, ez a bôvítés talán kissé korai lenne. Térjünk vissza az ügyre, ha a körülmények kedvezôbbnek bizonyulnak.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "Ahogy óhajtja, kapitány. Ha esetleg megváltoznának a megfontolásai, továbbra is állok rendelkezésére.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "Kapitány, nagyszerû hírek! Elhoztad az ötvenezer ezüstöt, hogy azonnal indulhassunk?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Itt van a teljes összeg. Gondoskodj róla, hogy méltónak bizonyulj a bizalomra, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Jelenleg a pénztáramból hiányzik a szükséges pénz. Visszatérek, ha a pénzügyeim lehetôvé teszik ezt a befektetést.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Becsületemre legyen mondva, "+pchar.name+", soha nem fogod megbánni ezt a döntést! Késedelem nélkül megkezdem az elôkészületeket. A következô gyûjtéstôl kezdve száz palackot kaphat a legfinomabb rumból és ugyanannyi kiváló bort, mindezt százharminc dublonnáért egy teljes szállítmányért.";
			link.l1 = "Nagyon kielégítô. De ne feledje, hogy mindenben a legnagyobb diszkréciót kell tanúsítania. A viselkedésed közvetlenül visszahat a helyzetemre ezeken a vizeken.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}