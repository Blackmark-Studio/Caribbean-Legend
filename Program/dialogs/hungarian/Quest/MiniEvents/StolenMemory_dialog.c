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

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, azt mondják, Port-au-Prince elveszti a varázsát, ha nem mosolyog. A mai nap, úgy tûnik, egy ilyen nap. Bocsássa meg az ôszinteségemet, de valami bántja önt?";
			}
			else
			{
				link.l1 = "Mademoiselle, a szépségérôl és kecsességérôl szóló mesék eljutottak a fülemhez, és meg kell mondanom, hogy a pletykák nem igazságosak önnel kapcsolatban. Azt is mondják, hogy Port-au-Prince elveszti a varázsát, ha nem mosolyog. A mai nap sajnos ilyen napnak tûnik. Nevezze meg a gazembert, aki el merte keseríteni a hangulatát, és esküszöm, párbajra hívom, hogy visszahozzam a mosolyt a kedves arcára.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ah, mademoiselle, az ön figyelme nagyon megható... Be kell vallanom, az aggodalma meghatott. De sajnos, bánatom oka nem olyan, amit puszta beszélgetéssel el lehet oszlatni. Nem egy személy hibája, hanem olyan körülmények, amelyeken, attól tartok, még a legelszántabbak sem tudnak úrrá lenni.";
				link.l1 = "A körülmények? Biztosíthatom, mademoiselle, a "+GetFullName(pchar)+" számára egyetlen akadály sem leküzdhetetlen. Mondja el, mi történt - talán tudok segíteni.";
			}
			else
			{
				dialog.text = "Ó, monsieur, ön valóban a kedves szavak mestere. Bevallom, majdnem sikerült mosolyt csalnia az arcomra. De sajnos, a párbaj nem oldja meg a problémámat. Aki elsötétítette a napomat, az nem egy gazember, hanem olyan körülmények, amelyeket még egy ilyen gáláns úriember, mint ön, sem tud leküzdeni.";
				link.l1 = "A körülmények? Kedves kisasszonyom, a kapitány "+GetFullName(pchar)+" minden vihart átvészel! És ha nem sikerülne, esküszöm, megeszem az elsô járókelô kalapját, akit meglátok!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ha tényleg ragaszkodik hozzá, elmondom, mi történt. De elôbb a szavára van szükségem, hogy ez a beszélgetés kettônk között marad.";
				link.l1 = "A szavamat adom, mademoiselle. Bármit is mond, köztünk marad, még akkor is, ha az óceán mélyére kell vinnem.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", önnek bizonyára megvan az az adottsága, hogy még a legproblémásabb hölgyet is felvidítsa. De kérem, kegyelmezzen az ártatlan járókelôk kalapjainak. Ha tényleg ragaszkodik hozzá, megosztom önnel, mi történt. Csak ígérje meg, hogy a szavaim titok maradnak, amit csak mi ismerünk.";
				link.l1 = "Szavamat adom, kisasszony, hogy mindent, amit nekem mond, teljes titokban tartok, még halálos fenyegetés esetén is.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Nagyon jó. Egy nyaklánc tûnt el a szobámból... de értsd meg, ez sokkal több, mint egy egyszerû csecsebecse. Valaki adományozta nekem, aki fontos helyet foglal el a szívemben. Hiánya sokkal mélyebb sebnek tûnik, mint egy tárgy puszta elvesztése\nHosszasan töprengtem, ki lehet a felelôs, és csak egy következtetésre jutottam. Attól tartok, hogy az egyik saját szolgám lehetett. Egyedül nekik van hozzáférésük a magánlakosztályomhoz, és csak ôk áhítozhatnak egy ilyen értékes darabra. Mégsem merem ezt a vádat nyilvánosan felhozni...";
			link.l1 = "Valóban nagyon kényes ügy, különösen, ha a diszkréció a kívánsága. De ha felajánlom a segítségemet, meg kell értenem, mi kényszeríti önt arra, hogy ilyen gondosan ôrizze ezt a titkot. Ha nem tudnám, milyen veszélyekkel kell szembenéznünk, akaratlanul is veszélybe sodorhatnám mindkettônket. Mondd el, kit kell elkerülnünk, és milyen veszélyek leselkednek az árnyékban.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "Nem beszélhetsz szabadon? Akkor attól tartok, mademoiselle, hogy nem tudok mást ajánlani, mint jókívánságaimat. Sem ízlésem, sem tehetségem nincs az intrikákhoz és a titkolózáshoz. Szerintem az ön nehézsége gyorsan megoldható lenne a városôrség segítségével. Úgy tûnik azonban, hogy ön egy sokkal árulkodóbb utat választott ezeken a zavaros vizeken.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "Nem tudsz nyíltan beszélni? Akkor bocsánatát kell kérnem, kisasszony, mert teljesen tehetetlen vagyok a titoktartás ködében. Nem igazán kedvelem a titkos ügyeket és az árnyékos ügyleteket. Az ön dilemmája meglepôen egyszerûnek tûnik: a városôrségnek egyszerû dolga lesz megoldani. Mégis úgy tûnik, ön elhatározta, hogy olyan intrikát szô belôle, amely méltó Európa királyi udvaraihoz.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "Így néz szembe a híres kapitány "+GetFullName(pchar)+" a megpróbáltatásokkal? Úgy, hogy a bonyolultság elsô jelére visszavonul? Talán a tehetségét jobban hasznosíthatná a rumoshordók számolásában vagy a kikötôi kereskedôkkel való csevegésben. Csak annyit kérek: ha van benned egy cseppnyi becsület, tartsd szigorúan titokban, amit megosztottam veled. Szép napot, kapitány.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "Bölcsen beszélsz, "+GetAddress_Form(NPChar)+". Az igazság tehát: ez a nyaklánc egy olyan embertôl származik, akinek puszta létezése is a nagybátyám haragját vonja maga után - a francia területek kormányzójától ezen a szigeten. Megtiltott minden kapcsolatot, még a nevének puszta említését is. Ha a nagybátyám rájönne az ajándék eredetére, annak katasztrofális következményei lennének, nemcsak rám nézve, hanem...";
			link.l1 = "Ne mondjon többet, kisasszony. Tökéletesen értem. Biztos lehet benne, hogy a legnagyobb diszkrécióval fogom visszaszerezni a nyakláncát, és olyan féltékenyen ôrzöm a titkát, mint egy sárkány a kincsét.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "Mélységes hálámat fejezem ki, "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+". Az Ön gáláns és megértô viselkedése felmelegíti a szívemet ezekben a nehéz idôkben. Feltétlenül bízom abban, hogy titkom biztonságban van az Ön kezében. A szerencse szele töltse meg vitorláit ebben a kényes vállalkozásban.";
			if (pchar.sex == "woman")
			{
				link.l1 = "A szerencse átöleli azokat, akik mernek cselekedni, mademoiselle. Nyugodjon meg - visszaszerzem a nyakláncát, olyan biztosan, mint ahogy a dagály visszatér a partra.";
			}
			else
			{
				link.l1 = "A szerencse mosolyog a bátrakra, kisasszony. Amint visszaszerzem a drága nyakláncát, visszakerül a kecses kezekbe, ahová jogosan tartozik.";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Kapitány, visszatért! Hírei vannak számomra? Imádkozom, hogy visszaszerezte a nyakláncomat. Kérem, mondja, hogy így van.";
				link.l1 = "A gondjaidnak vége, Julie. A nyaklánc megvan, és a legnagyobb megelégedéssel tölt el, hogy visszakerülhet a jogos helyére - az ön finom kezébe.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Kapitány, visszatért! Hírei vannak számomra? Imádkozom, hogy visszaszerezte a nyakláncomat. Kérem, mondja, hogy így van.";
				link.l1 = "Sajnálom, hogy csalódást kell okoznom, Julie. A keresés folytatódik. De légy szíves, nem hagyok semmit sem hátra, amíg a drága nyakláncodat vissza nem kapod.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "Üdvözlöm, uram. Mi szél hozta a hajónkra?";
			link.l1 = "Tristan Renier kapitányt keresem; egy olyan ajánlatot hoztam, ami jól megtömné a zsebét.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "Beszélnem kell Tristan Renier kapitánnyal egy kényes ügyben - személyes ügy, ha jól érti.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "A kapitány sajnos partra szállt. Talán valahol a városban találja meg, ha sürgôs az ügye.";
			link.l1 = "Tudja, hová megy? Van valami különleges hely, amit szívesen látogat a kikötôben?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "A kapitány sajnos partra szállt. Talán valahol a városban találja meg, ha sürgôs az ügye.";
			link.l1 = "Tudja, hová megy? Van valami különleges hely, amit szívesen látogat a kikötôben?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Elnézést kérek, "+GetAddress_Form(NPChar)+", de a kapitány megtartja a saját tanácsát a jövés-menéseit illetôen. Csak annyit tudok, hogy néhány órája szállt le a hajóról.";
			link.l1 = "Még ez is sokat segít. Köszönöm a segítségét.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Ki a fene maga? Milyen jogon merészel hívatlanul behatolni a magánlakosztályomba?";
				link.l1 = "Kapitány vagyok "+GetFullName(pchar)+". És egy fontos ügyben jöttem.";
			}
			else
			{
				dialog.text = "És ön ki lehet, hölgyem? Nem emlékszem, hogy meghívást kaptam volna ma este. Bár be kell vallanom, néhány váratlan látogató sokkal... érdekesebbnek bizonyul, mint mások. Mi hozta ezt a látomást szerény szállásomra?";
				link.l1 = "Kapitány vagyok "+GetFullName(pchar)+". És látogatásom üzleti ügyben történik, nem szórakozásból.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Üzleti ügy, ugye? Miféle ügy indokolja ezt az udvariatlan megzavarást?";
				link.l1 = "Ez elég egyszerû. Önnél van egy nyaklánc, amiért jöttem, hogy visszaszerezzem.";
			}
			else
			{
				dialog.text = "Üzleti ügy, azt mondja? Lenyûgözô... Milyen sürgetô üzleti ügy késztet egy ilyen elbûvölô hölgyet arra, hogy felkeressen a magánszobámban?";
				link.l1 = "Kíméljen meg a mézes-mázos szavaitól, monsieur. Az ön birtokában lévô nyakláncért jöttem. És igen, pontosan tudom, hogy önnél van.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ha! Egy nyaklánc, azt mondja? Valóban szereztem egy ilyen darabot nemrég, de mi köze van hozzá? Bizonyára nem várja el, hogy átadjam a tulajdonomat az elsô idegennek, aki követeli?";
			}
			else
			{
				dialog.text = "Egy nyaklánc? Valóban... Nemrég szereztem egy ilyen csecsebecsét. És mondja, kapitány, milyen módon akar megszabadítani ettôl az ékszertôl, ami jogosan az enyém?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Kész vagyok ötezer pesót ajánlani érte. Egy szép összeget, ami lehetôvé tenné, hogy egy hasonlóan szép dísztárgyat vásároljon, talán még nagyobbat is. Addig is, ez a bizonyos nyaklánc visszakerülne ahhoz, aki mérhetetlenül nagyra értékeli - sokkal többre, mint bármilyen pénzbeli érték.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Hadd beszéljek nyíltan, uram. A választási lehetôségei jelentôsen beszûkültek: önként adja át a nyakláncot, és élhet még egy napot, vagy ellenáll, és megkéri, hogy szerezzem vissza az élettelen testébôl. A döntés az ön kezében van, de azt javaslom, siessen a döntéssel.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "Ötezer, azt mondod? Nos akkor, kapitány, meggyôzô alkut köt. Tessék, vegye el a csecsebecsét, ha ennyit jelent.";
				link.l1 = "A bölcsessége megegyezik a nagylelkûségével, uram. Ezt a döntést nem fogjuk megbánni.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("A csekk átadva", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Nem azért szereztem ezt a nyakláncot, hogy elcseréljem az elsô csavargóra, aki érmét villant! A feleségemnek szánom ajándékba, és többet nem hallok errôl az ügyrôl. Távozz a jelenlétembôl, mielôtt embereket hívok, hogy kikísérjenek!";
				link.l1 = "Ha megtagadod az úriemberi megállapodást, akkor kevésbé civilizált eszközökkel fogom követelni, amit keresek.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Elégtelen készségszint (25)", SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Argh... Te szemtelen kölyök... Azt hiszed, hogy a gyerekes fenyegetéseiddel megijesztesz engem? Ha! Fogalmad sincs, kivel van dolgod!";
				link.l1 = "Nem érdekel, hogy ki vagy. Csak add át a nyakláncot és elmegyek. Vagy tényleg hajlandó vagy meghalni egy csecsebecséért, ami semmit sem jelent neked?";
				link.l1.go = "Captain_4_leadership_2";
				notification("A csekk átadva", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Nem azért vettem ezt a nyakláncot, hogy a magadfajtákkal alkudozzak! Ajándékba kaptam a feleségemnek, és magának semmi keresnivalója itt. Takarodj, mielôtt kidobunk!";
				link.l1 = "Ha nem válik meg tôle békésen, akkor erôszakkal veszem el.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("A képesség nem elég magas (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Átkozott legyél te és az az átkozott nyaklánc! Vedd el! Vedd el és tûnj el, mielôtt meggondolom magam.";
			link.l1 = "Bölcs döntés! Búcsúzz el!";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", visszahoztad az örömöt a szívembe! Nem csak a nyakláncot adtad vissza, hanem a lelkem egy darabját is. Nemeslelkûséged csodálatra méltó, és ígérem, hogy mindenkinek, akinek csak tudom, elmesélem bátorságodat!";
			link.l1 = "Kérem, kisasszony, nem a hírnévért adtam vissza. Az ön mosolya az egyetlen jutalom, amit igazán értékelek.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Olyan szerény vagy, "+pchar.name+". De kérlek, fogadd el ezt a láda dublont. Csak a tudat, hogy elfogadtad az ajándékomat, ad nekem egy olyan érzést, hogy úgy köszöntem meg neked, ahogy igazán megérdemled.";
			link.l1 = "Kérem, kisasszony, ne ragaszkodjon hozzá. Kedves szavai többet jelentenek nekem, mint bármilyen láda dublón.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Ha ez megnyugvást hoz önnek, kisasszony, elfogadom az ajándékát. De tudja, hogy ezt nem jutalomért tettem. "+GetSexPhrase("elismerése","hálája")+" sokkal többet jelent nekem, mint ezek a dublónok.";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "Teljesen elfelejtettem megkérdezni - tudja, ki lopta el a nyakláncot?";
			link.l1 = "Csak annyit tudok, mademoiselle, hogy egy kereskedô kapta egy Giselle nevû személytôl. És a körülményekbôl ítélve, lehet, hogy nem ez az utolsó ékszer, amit el akar adni.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "Teljesen elfelejtettem megkérdezni - tudja, ki lopta el a nyakláncot?";
			link.l1 = "Csak annyit tudok, mademoiselle, hogy egy kereskedô kapta egy Giselle nevû személytôl. És a körülményekbôl ítélve, lehet, hogy nem ez az utolsó ékszer, amit el akar adni.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "Giselle? De ô a szobalányom! Volt egy gyanúm... de nem akartam elhinni. A legrosszabb az, hogy még csak meg sem tudom büntetni rendesen. Felfedhetné a titkomat - és ezt nem engedhetem meg.";
			link.l1 = "Szóval mit fogsz tenni? Hagyod, hogy megússza, és továbbra is lopni fog tôled?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Ó, nem, persze, hogy nem. Elôször is, gondoskodom róla, hogy többé ne legyen a közelemben. Aztán kitalálom, hogyan büntessem meg, hogy úgy tûnjön, a büntetés máshonnan jött.";
			link.l1 = "Egy nô ravaszsága veszélyes fegyver, különösen egy olyan kifinomult és éleslátó ember kezében, mint te. Biztos vagyok benne, hogy a szobalányod nem is veszi észre, hogy a játszma már elveszett - és nem az ô javára.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ah, kapitány... Nem szeretnék trükkökhöz folyamodni, de... néha a ravaszság az egyetlen út elôre.";
			link.l1 = "Valóban, Julie. Nem szívesen hagylak itt, de hív a kötelesség. Ki más vigyázna a legénységemre, ha nem én?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "A viszontlátásig, "+pchar.name+". Kérjük, látogasson el gyakrabban a kikötônkbe. Városunknak nagyon hiányzik "+GetSexPhrase("az olyan nemes és bátor emberek, mint te.","hölgyek, akiknek olyan nemes szívük és olyan bátor lelkük van, mint az önöké.")+"";
			link.l1 = "Hízeleg nekem, kisasszony. Ígérem, nem hagyok ki egyetlen alkalmat sem, hogy visszatérjek az ön gyönyörû városába. A következô alkalomig.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! Micsoda meglepetés! Még mindig a tengereket hódítja?";
						link.l1 = "Örülök, hogy látom, kisasszony. Hódítok, amennyire csak tudok, bár a tenger továbbra is engesztelhetetlenül szeszélyes. És ön... élvezi a nyugalmat és a csendet?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ah, Kapitány "+pchar.lastname+", milyen jó újra látni téged! Remélem, minden rendben megy neked?";
						link.l1 = "Én is örülök, hogy látom, mademoiselle. Az üzlet, mint mindig, idôt és erôfeszítést igényel, de az ilyen találkozók minden napot feldobnak. És hogy teltek a napjai?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitány "+pchar.lastname+", már megint itt vagy? Tényleg vannak még emberek szerény városunkban, akiket nem árultál el egy maréknyi aranyérméért?";
						link.l1 = "Mademoiselle, megértem az érzéseit, de úgy cselekedtem, ahogy helyesnek tartottam. Néha a helyes döntés fájdalommal jár, és sajnálom, hogy megbántottalak.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Kapitány "+pchar.lastname+", már megint? A kapzsiságod annyira határtalan, hogy nem tudod békén hagyni a városunkat és vadászol a következô áldozatodra?";
						link.l1 = "Kisasszony, sajnálom, hogy a tetteim fájdalmat okoztak önnek, de a lelkiismeretem szerint cselekedtem.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Az utóbbi idôben a dolgok nyugodtak és csendesek voltak - semmi sem zavarja a békét. Kérem, látogasson el gyakrabban a kikötônkbe, kapitány. Biztos vagyok benne, hogy itt mindent megtalál, amire vágyik, mind a boltunkban, mind azon kívül.";
			link.l1 = "Köszönöm, mademoiselle. Igyekszem majd gyakrabban meglátogatni. Biztos vagyok benne, hogy az önök városa még sok kellemes meglepetést tartogat.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "Hála önnek, kapitány, a napjaim most sokkal nyugodtabbak. Remélem, még meglátogat minket.";
			link.l1 = "Természetesen, mademoiselle. Az önök városa mindig a legkellemesebb benyomást kelti. A következô alkalomig.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Kapitány "+pchar.lastname+", újra találkozunk. Figyelemre méltó, nem igaz?";
					link.l1 = "Úgy tûnik, a sors mosolyog a mai találkozásunkra, mademoiselle.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Kapitány "+pchar.lastname+", úgy tûnik, az útjaink ismét keresztezték egymást.";
					link.l1 = "Valóban, kisasszony. Örülök, hogy újra látom.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Úgy tûnik, túl gyakran találkozunk, kapitány. Vagy csak nem tudsz távol maradni azoktól, akiket már elárultál?";
					link.l1 = "Mademoiselle, a találkozásaink pusztán véletlenek, de megértem a keserûségét. Csak remélem, hogy egy nap majd megérti az okaimat.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "Most mit akar? Biztos nem olyan rossz a szerencséje, hogy ez véletlen legyen. Vagy csak azért jöttél, hogy emlékeztess a szégyenedre?";
					link.l1 = "Mademoiselle, nem állt szándékomban tolakodni, vagy régi sebeket feltépni. Ez a találkozás valóban véletlen.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}