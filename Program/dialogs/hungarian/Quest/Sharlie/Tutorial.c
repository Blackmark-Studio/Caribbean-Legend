void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{	case "First time":
			dialog.text = "Akarsz valamit?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "Szép látvány, mi?";
			link.l1 = "Ez az átkozott tenger már két hónapja próbál megölni. De még nem sikerült.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Így van. Néha az óceán emlékeztet arra, hogy milyen kicsik is vagyunk valójában.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "Megtanultam, hogy a tengeren csak két állapot létezik: unalom vagy rettegés. Ez... más.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "Ez más. Elôször van a tengeren, monsieur? Amikor ilyen nyugalom van, bárki játszhatja a kapitányt. Jobb, ha élvezzük, amíg tart.";
			link.l1 = ""+GetFullName(pchar)+". Egy nemesember, hogy tudd. Ne, uram, ne engem!";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "Ez más. Elôször van a tengeren, monsieur? Amikor ilyen nyugalom van, bárki játszhatja a kapitányt. Jobb, ha élvezzük, amíg tart.";
			link.l1 = ""+GetFullName(pchar)+". Egy nemesember, hogy tudd. Ne, uram, ne engem!";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "Ez más. Elôször van a tengeren, monsieur? Amikor ilyen nyugalom van, bárki játszhatja a kapitányt. Jobb, ha élvezzük, amíg tart.";
			link.l1 = ""+GetFullName(pchar)+". Egy nemesember, hogy tudd. Ne, uram, ne engem!";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "Ahogy óhajtja, uram. Akkor hát, elsô útja, uram "+pchar.lastname+"?";
			link.l1 = "Ennyire nyilvánvaló? Igen, az elsô. És én nem a szûkös kabinokra és a rothadó hajós ételekre születtem.";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "Egyértelmû, hogy szárazföldi lúzer vagy, uram.";
			link.l1 = "Vigyázz a nyelvedre! Egy becsületes embernek eldobnám a kesztyûmet, és elégtételt követelnék. De egy olyan parasztnak, mint te - egyszerûen levágom a füled.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "Talán Párizsban. De itt kint, az ilyen szavakkal a halakkal etethetik meg az embert. Én nem hadonásznék azzal a pengével, uram - és ne hagyja, hogy a kapitány megbánja, hogy felfegyverkezve sétálhat a fedélzetén. A legutóbbi bajkeverôt a raktérbe küldték, penészes kenyérrel és fenékvízzel, amihez még a patkányok sem nyúlnak. És tudod mit? A szerencsétlen fattyúnak még mindig fizetnie kellett, amikor kikötöttünk.";
			link.l1 = "Mit várhatsz... Rendben, felejtsük el ezt a félreértést. Folyton emlékeztetnem kell magam, hogy ez a kád a Louvre közelében sincs.";
			link.l1.go = "StartSailor_5";
		break;
		
				case "StartSailor_5":
			dialog.text = "Mi? A Louvre-hoz? Az meg micsoda?";
			link.l1 = "Ha! A Louvre a kiválasztott kevesek palotája. Bálok, fogadások, intrikák...";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "Ah... akkor egy bordélyház. Van belôlük bôven. Nem mondhatnám, hogy a kiválasztottaknak vannak - fizesse ki a pénzét, és minden a magáé.";
			link.l1 = "Ha! Nem jár messze a céltól, matróz.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "A nevem egyébként Alonso. És mi szél hozott a világ végére, uram? Kétlem, hogy azért kelt át az Atlanti-óceánon, hogy egy tengerésszel vitatkozzon.";
			link.l1 = "Az apám beteg, és nem tudja elhagyni a gázkonyi birtokunkat. Azzal bíztak meg, hogy keressem meg... idôsebb bátyámat. Üzleti ügyben jött ide, és azóta semmit sem hallottunk felôle.";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "Miért nem küldesz egy megbízható embert, ahelyett, hogy te magad viselnéd el a tenger viszontagságait?";
			link.l1 = "A család az elsô. Nem bízhatom a sorsát az elsô emberre, akivel találkozom.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "Szerettem volna - de apám ragaszkodik hozzá, hogy én legyek az. Fogalmam sincs, miért.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "És hogy hívják a bátyádat?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "És hogy hívják a bátyádat?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "De Monper? És te "+pchar.lastname+"? Hogyhogy?";
			link.l1 = "Ne nézz így rám. Én vagyok a törvényes fiú. Csak felvettem anyám nevét.";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "Nincs miért szégyenkezned. Jól be fogsz illeszkedni - az Újvilágban mindenkinek van valami története. Nekem például...";
			link.l1 = "Én nem szégyenkezem semmi miatt! Csak meséljen nekem Martinique-ról. Nagy város? Mint Toulouse?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "Egy város? Ha! Martinique egy sziget. Az egyik legnagyobb Franciaország karibi birtokában. Tüzes kávét termesztenek, pokoli ként bányásznak, és a világ legszebb nôit szülik. Remek keverék, ha engem kérdezel.";
			link.l1 = "Engem nem érdekel a kávé vagy a kén. De várjunk csak... egy sziget? Hogy találjam meg a bátyámat egy egész szigeten?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "Ne aggódj. Saint-Pierre egy kisváros - nem a Louvre, persze, de nem is a dzsungel. Le François, Isten ments - egy tisztességes embernek semmi keresnivalója ott.";
			link.l1 = "Ha kell, akkor a banditákhoz megyek. Michel mindig kihúzott a bajból. Most én jövök.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "Nem is rossz... egy szárazföldi csavargótól.";
			link.l1 = "Már megint itt vagy. Mikor érjük el ezt az átkozott Martinique-ot?";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "Öt nap múlva.";
			link.l1 = "Öt?!";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "Legalább. És ha kalózok bukkannak fel - lehet, hogy egyáltalán nem érünk oda. A Kis-Antillák veszélyes vizek, még értékes rakomány nélkül is.";
			link.l1 = "Az utasoktól eltekintve!";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "Ha-ha! Ne aggódjatok. Legrosszabb esetben én magam rejtegetlek a raktérben - egy kalóznak sem jutna eszébe, hogy egy gázkói nemest keressen a rumos hordók között! Végül is nem vagyunk idióták - egy élô gázkónt rummal keverni. Az még a puskapornál is jobban felrobban, ha-ha!";
			link.l1 = "Ha! Még jó, hogy a rum már egy hónapja elfogyott!";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "Ööö... jobb, ha nem mondunk ilyesmit hangosan. Az emberek még azt hinnék, hogy miattad fogyott el a rum.";
			link.l1 = "Rendben, Alonso, nem fogom. Amúgy sem innám meg azt a szeszt. Ami a briliáns tervedet illeti, hogy a csata elôtt a raktérben rejtegetsz - nem fog megtörténni.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "Miért ne?";
			link.l1 = "Nemes vagyok, jól bánok a karddal, és nem bújkálok a raktérben.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Ha arra kerül a sor - megvédem a hajót és a többiekkel együtt harcolok. Mi mással?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Magam döntöm el, mikor harcolok, és mikor menekülök. Majd meglátjuk, hogy mi lesz.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ha. Talán mégis van benned valami. De vigyázz - a Karib-tenger szereti megnyúzni azokat, akik felemelt orral sétálnak be. Nem fogod túlélni az elsô összecsapást a kalózok elôôrsével. A pokolba is, egy rongyos gengszter Saint-Pierre elôtt kibelez, mielôtt észrevennéd.";
			link.l1 = "Egyáltalán nem ismersz engem.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "Ha. Talán mégis van benned valami. De vigyázz - a Karib-tenger szereti megnyúzni azokat, akik felemelt orral sétálnak be. Nem fogod túlélni az elsô összecsapást a kalózok elôôrsével. A pokolba is, egy rongyos gengszter Saint-Pierre elôtt kibelez, mielôtt észrevennéd.";
			link.l1 = "Egyáltalán nem ismersz engem.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "Ha. Talán mégis van benned valami. De vigyázz - a Karib-tenger szereti megnyúzni azokat, akik felemelt orral sétálnak be. Nem fogod túlélni az elsô összecsapást a kalózok elôôrsével. A pokolba is, egy rongyos gengszter Saint-Pierre elôtt kibelez, mielôtt észrevennéd.";
			link.l1 = "Egyáltalán nem ismersz engem.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "De ismerem az Újvilágot és a népét. Ha nem tervezed, hogy a számlakönyvek mögött sorvadsz el, vagy a kormányzó házában szolgálsz - mindent a semmibôl kell megtanulnod.";
			link.l1 = "Még jó, hogy nem tervezem, hogy itt maradok.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "Ezt gondolod te is. Nem sûrûn viszünk utasokat Európába. Néhányan meghalnak - láztól, kötéltôl vagy golyótól. Mások maradnak - örökre. Láttam, hogy gyenge arisztokratákból kapitányok lettek, kegyetlen banditákból elismert ültetvényesek. És briliáns tisztekbôl - nincstelen csavargók lettek.";
			link.l1 = "Pokolian csábító, de én visszamegyek Franciaországba. Várnak rám az emberek.";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "Ó, igen, így van. Egy beteg apa?";
			link.l1 = "Mondjuk úgy... van egy bizonyos hölgy, akinek a férje nagyon nem akarja, hogy Párizsban legyek. De néhány hónap - és a szenvedélyek lehûlnek.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "Ha-ha-ha-ha! Akkor biztosan jó helyen jársz. A Karib-tenger a féltékeny férjek elôl menekülôk paradicsoma. És itt repül az idô. Adj neki egy kis idôt - lehet, hogy a végén még tengerész leszel!";
			link.l1 = "Sokkal valószínûbb, hogy kapitány leszel. Attól tartok, nem vagyok jó egyszerû tengerész. A kétkezi munka nem az én világom.";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "Franciaországban az emberek születési jogon uralkodnak. De a hajó fedélzetén a kapitány király, bíró és Isten. Senki sem tudja, milyen megpróbáltatásokkal kellett szembenéznie, hogy kiérdemelje ezt a kalapot. Itt mindenki azt kapja, amit megérdemel. Ahogy a fedélzeten mondjuk - mindenkinek a sajátja.";
			link.l1 = "Ostobaság. Ha már a kapitányoknál tartunk - beszélnem kell a tiéddel, különösen, hogy keresett engem. Viszlát, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Akart kérdezni valamit?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Monsieur Pinchontól jöttem.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Semmi.";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "Há! Az a négyszemû téged is beavatott ebbe?";
			link.l1 = "Négyszemû?";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "Látta a szemüvegét? Pontosan! De ne értsen félre - a legénység tiszteli Monsieur Pinchon-t. A jó orvosokat mindig megbecsülik egy hajón. És ô egy rendes pénztáros is.";
			link.l1 = "Mi dolga van vele?";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "Uhh... Sajnálom, de ez a mi dolgunk. De ne aggódjon - nem szegünk meg semmilyen hajótörvényt.";
			link.l1 = "Mi a helyzet a rendes törvényekkel?";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "A rendes törvények nem tartoznak ránk. Szóval, mennyit számoltak össze nekem?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 dublont.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 dublont.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 dublont.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "I need to double-check everything. I'll come back later.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "Itt az arany. Saint-Pierre, jövök! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "Itt az arany. Saint-Pierre, jövök! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "Itt az arany. Saint-Pierre, jövök! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Á, Charles. Nem igazán sietett, ugye? Ha a hajó kapitánya beszélni akar veled, azonnal jelentkezz. Nehezen követi a parancsokat?";
			link.l1 = "Nem szoktam parancsokat fogadni, kapitány.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Elnézést, kapitány, késésben voltam.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Világosan megmondtam, hogy a hajója - a maga szabályai.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (skip tutorial és indítsa el a játékot Martinique-on)";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "Nem hagyom, hogy megkérdôjelezzék a tekintélyemet. Fogalmad sincs, milyen gyakran éri szerencsétlenség az utasokat a tengeren. Nagyon szerencsés vagy, hogy érdekel, hogy épségben eljuss Saint-Pierre-be.";
			link.l1 = "Mirôl beszélsz?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "Bocsánatkérés elfogadva. Élvezze a pillanatot. Ilyen naplemente nem gyakran lesz.";
			link.l1 = "Mirôl beszélsz?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "Jó látni, hogy tanult valamit ezen az úton. A kapitány szava törvény - és néha még a parton is érvényes, távol a hajótól.";
			link.l1 = "Mirôl beszélsz?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Kapitány. Kérem, szólítson meg a tengeri protokoll szerint.";
			link.l1 = "Mirôl beszél, kapitány?";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "Tájékoztatni akartam, hogy a vitorlákat leengedtük, és sodródunk. Sajnos az önök megérkezése Martinique-ra néhány napot késni fog.";
			link.l1 = "De miért, kapitány?";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "Mert én így döntöttem.";
			link.l1 = "Ez valahogy összefügg a tegnapi találkozással a kereskedelmi konvojjal, amelyik arra a... hogy is hívják...";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Capsterville. Figyelj, "+pchar.name+": komolyan el kell beszélgetnünk. Meghívlak vacsorázni a kabinomba. Hamarosan megszólal a harang - akkor lesz idônk civilizált emberek módjára beszélgetni, miközben befejezzük a hajó utolsó üveg borát.";
			link.l1 = "Köszönöm a meghívást. Megtisztel, kapitány.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Szóljon, ha készen áll. Még van egy kis idônk, úgyhogy nyugodtan sétálgathat a hajón - csak ne zavarja a legénységemet a munkában.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "Egyéb kérdés?";
			link.l1 = "(Készen állok), kapitány. Veled - még burgundit is iszom!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Mit figyelsz olyan feszülten azon a távcsövön keresztül... Kapitány?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Kapitány, volt szerencsém beszélni egy bizonyos Alonsóval. Mi a pozíciója a fedélzeten?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Kapitány, meséljen a hajójáról. Egy pinace, ugye?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "A következô alkalomig, kapitány.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Semmi különös, csak a horizontot pásztázom. Egy sodródó hajó könnyû préda.";
			link.l1 = "Kalózokat keres?";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "Vagy spanyolokat. Francia zászló alatt hajózunk, kíséret nélkül, és a Kis-Antillák igazi keresztút - és Jacques Barbazon birodalma.";
			link.l1 = "Az meg ki? Egy kormányzó?";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "Rosszabb esetben az egyik kalózbáró. Ezek az akasztófamadarak valami szervezetszerûséget alakítottak, és a Parti Testvériségnek nevezik magukat. Hat részre osztották a Karib-térséget, és mindegyikbe egy-egy bárót helyeztek, hogy ne tépjék szét egymást.";
			link.l1 = "Miért nem tesznek ellene valamit a hatóságok?";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "Naiv vagy, "+pchar.name+". A kalózkodás csak azért létezik, mert a helyi hatóságok hagyják, hogy a zsákmányból való részesedésért cserébe javítsanak és feltöltôdjenek a kiválasztott kikötôkben. Nem szívesen ismerem be, de az egyetlenek, akik tényleg tesznek valamit ez ellen a fekete pestis ellen, a spanyolok. Ha ôk nem lennének, a hajónkat drága ágyúkkal kellene felszerelnünk - és kíséretet is felbérelnünk.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "A rangidôs matróz. Nem sokat tudok róla, de annyit mondhatok: ha minden embernek van egy csontváza a szekrényében, Alonsónak egy egész temetôje van.";
			link.l1 = "Úgy hangzik, mintha nem bíznál benne.";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
				case "Captain_7_question_2_2":
			dialog.text = "Egyáltalán nem. Gondolja, hogy könnyû ilyen tapasztalt embereket találni a legénységbe? Legalább egy év és egy kiváló hajóskapitány kell ahhoz, hogy egy kocsmai részegekbôl álló csapat akár csak távolról is legénységnek tûnjön. Emellett Alonso a legénység hangja is. Egy kapitány nem foglalkozik azzal, hogy az alsóbb rangúakkal beszélgessen, de ostobaság - és halálos - elfelejteni, hogy a közönséges matrózoknak is vannak érdekeik. Alonso képviseli ôket, ha kell.";
			link.l1 = "És mi történik, ha a legénység elégedetlen?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "Felakasztanak, téged meg csak leszúrnak. Ne nézz olyan sápadtan. Amíg a legénység megkapja a fizetést, az élelmet, az italt és a foltozást - addig a kapitány és a legénység közötti szerzôdés teljesül. Nem játszom az életükkel, nem büntetek szeszélybôl, megosztom a zsákmányt, és néha elkényeztetem ôket ingyen itallal és partra szállással. Így tartjuk fenn a törékeny egyensúlyt - és ezért jut el a hajó mindig oda, ahová tart.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "Megérintettél egy ideget, "+pchar.name+"! Örökké tudnék beszélni a szépségemrôl. Harmadosztályú, húsz ágyú, nagy sebesség -  ne tévesszen meg a ‘kereskedô’ rész!!";
			link.l1 = "Értettem a fegyverekrôl és a sebességrôl szóló részt. De a ‘díjszabás’? A‘kereskedô’?";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "Az árfolyam egy laza osztályozás az ágyúk száma szerint. A hetedik osztály alig egy hajó, míg az elsô osztály majdnem egy erôd. De ezt ne ismételje Európában - különösen ne a tengerésztisztek körében.";
			link.l1 = "Miért ne? Ez valami matrózos vicc?";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "Teljesen hülyének néznének és kigúnyolnának. Az igazság az, hogy bármelyik komoly haditengerészetnél más a rangsorolási rendszer, és csak a hadihajókra vonatkozik. De itt a Karib-tengeren a dolgokat a magunk módján intézzük, ahogy szoktuk.";
			link.l1 = "És mit értettél az alatt, hogy a hajódat ‘kereskedônek nevezted?’?";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "Egy másik laza kifejezés. Hadihajók - keményebbek és jobban lônek. Fosztogatók - rabolnak és menekülnek. Kereskedôk - sok rakományt, legénységet vagy fegyvert szállíthatnak, de kompromisszumot kell kötniük, különben a sebességük nevetségessé válik. Vannak többcélú hajók is, de ezekrôl nem sok mindent lehet mondani azon kívül, hogy alkalmazkodnak a tulajdonosuk igényeihez.";
			link.l1 = "Kezd izgatott lenni, kapitány.";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "Szeretem a hajómat, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Nos, szerencsés vagy - nekem csak burgundi maradt... Várjon, "+pchar.name+". Honnan szerezted a régi kalapomat?!\nVárj. Hé, a tetején! Mi folyik ott fent?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Hát, szerencséd van - nekem csak burgundi maradt\nVárj. Hé, a tetején! Mi folyik ott fent?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Bocsásson meg, monsieur de More, de ön nem mehet be oda.";
			link.l1 = "Voltam már a kapitány kabinjában. Erre már emlékeznie kellene.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Sajnos, a ravasz tervem kudarcot vallott. Viszlát, matróz.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "Bocsásson meg, monsieur, de a körülmények megváltoztak.";
			link.l1 = "És pontosan mi történt?";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "Alig van hátra az út, és a kapitány nem szeretné, ha bárki is kitakarítaná az értékeit, és eltûnne a Le Francois-i rablóparadicsomba.";
			link.l1 = "Kétlem, hogy a kapitány rám gondolt volna, amikor ilyen parancsot adott.";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Nos... igaza van. És már nem egyszer vacsorázott a kapitány kabinjában. Folytassa, Monsieur de More.";
					link.l1 = "Ez már jobban tetszik!";
					link.l1.go = "OhrannikCabin_4";
					notification("A csekk átadva", SKILL_Leadership);
				}
				else
				{
					dialog.text = "Insi... insi... insi... mi? Nem úgy értettem, monsieur de More!";
					link.l1 = "Akkor engedjen át.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Monsieur, bizonyára megérti, hogy a kapitány kabinja nem nyilvános utca. A parancs az parancs.";
					link.l1 = "A fenébe is, alig várom, hogy újra a szárazföldön legyek. Ez megalázó!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Monsieur, ezt már megbeszéltük. Nem engedhetem át.";
					link.l1 = "Makacs, mint mindig, tengerész. Viszontlátásra.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Elégtelen készség (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Eh... rendben. Gondolom, nem lesz belôle nagy baj.";
			link.l1 = "Ez már jobban tetszik!";
			link.l1.go = "OhrannikCabin_4";
			notification("A csekk átadva", SKILL_Leadership);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "Még valamit, uram? Nem engedhetem be - a kapitány aggódik az értékei miatt.";
			link.l1 = "Lopásra céloz, matróz? Óvatosan a szavakkal. Ez tiszta célzás!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Semmi, matróz.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Hé, te nemes fajankó! Mit csinálsz, megpróbálod az ördögöt a csörlôbe tömni?!\nA királyi lábaddal belerúgtál a dugóba! Azt tervezed, hogy mindannyiunkat a fenékre küldesz, mi?!\nTegyél meg nekünk egy szívességet - ne nyúlj semmihez, hacsak nem egy francia orrfolyásról van szó!";
			link.l1 = "Ez meg mi is pontosan?";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "Ez a csörlô, te tökfej. Az emeli a horgonyt. És ha nincs rögzítve - darabokra szaggatja a hajót, vagy valakit felcsavaroz, mint egy heringet a hordóba!";
			link.l1 = "Ha... És ha a másik irányba fordítod - leengedi a horgonyt, igaz?";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "Nem, zsenikém, visszafordítja az idôt. Kár neked - te már megszülettél!";
			link.l1 = "Nos, senkinek sem esett baja, igaz? A hajók tényleg bonyolult gépek. Óvatosabb leszek.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Ugyanolyan áhítattal bámulod az ágyú hosszú csövét, mint korábban a naplementét.";
			link.l1 = "Látom, élvezed, hogy figyelsz engem, Alonso. Jobb, ha mesél nekem a haditechnika eme csodájáról.";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "Ez egy tizenhatfontos. Nem minden hadihajónak van ilyenje.";
			link.l1 = "Könnyû eltalálni vele valamit?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "Közvetlen közelrôl - bármit szétrobbantunk. Száz méterrôl már benne vagyunk a játékban. Azon túl csak zaj és lángok, de jobb, mint a semmi.";
			link.l1 = "Száz méter - és az ellenség ugyanezt tudja.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "Ez igaz. De minden a legénység csapatmunkáján és a sannoneer ügyességén múlik. Kár, hogy a miénk alszik - egy egész leckét adna neked, aztán maga töltene be az ágyúba, ha!";
			link.l1 = "Az ágyúkezelô egy tiszt, ugye?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "Általában. Legalább egy félig-meddig hozzáértô kanonok nélkül jobb elkerülni a harcokat - akár ki is dobhatod az ágyúkat a fedélzetre és elmenekülhetsz.\nA kereskedô kapitányok ritkán visznek magukkal hatfontosnál nagyobbat - kíséretre vagy szerencsére számítanak.\nEz így van rendjén: nehéz ágyúk és lôszerek nélkül a hajó jobban vitorlázik, és több hely marad az eladható rakománynak.\nHa a kapitányunk nem pazarolt volna ezekre a szépségekre, talán még mindig maradna egy kis rumunk. Sóhaj.";
			link.l1 = "Nem a kapitány személyesen irányítja a tüzet?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "Egy jó sannoneerrel és legénységgel erre nincs is szüksége. De hadd mondjam el: amikor egy kapitány maga céloz az ágyúkkal, ahelyett, hogy a hátsó fedélzetrôl ugatna 'Fire!' - az ellenséges hajókon több lyuk keletkezik.";
			link.l1 = "Tüzelhetek egyet?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Köszönöm a lenyûgözô elôadást, Alonso. Maga a tengerészeti bölcsesség igazi kincsesbányája.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Persze! De azért ne szórakozz az ágyúval, és ne idegesítsd a legénységet.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "Tüzelni? Nem valószínû. A lövéshez a kapitány engedélye kell. Majd most megkérdezem tôle!";
			link.l1 = "Nem kell!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "Caa-ap'n!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "Mi van itt, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "Mister Charles azt javasolja, hogy lôjünk az ágyúval - szigorúan kiképzési céllal.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "Azt hittem, hogy a legénység érdekeit nézi, Alonso. Mégis itt van, és azt javasolja, hogy ébresszük fel a következô ôrséget, és ébresszünk fel mindenkit a lehetô legbarbárabb módon?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "Nekem úgy tûnik, bölcsebb lenne felkelteni a vérüket és felkészíteni ôket. Nem tetszik, hogy a szemünk láttára sodródunk. Valami történhet.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "Ne vészmadárkodj!... Jól van, rendben. Egy lövés. Üres.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "Jó szórakozást, "+pchar.name+". Majd mi felébresztjük a csapatot... a te költségeden, ha-ha!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Van egy perce, uram?";
			link.l1 = "Beszéljen, matróz.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "Örülök, hogy megismerhetem, monsieur. A nevem Henry. Szeretne egy kis pénzt keresni?";
			link.l1 = "Mennyibe kerül 'a kevés'?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Ötszáz peso.";
			link.l1 = "Mennyi?! Mit akarsz, mit csináljak ennyi pénzért? Lázadást szervezzek?";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "Te jó ég, uram! Nem kell kiabálni!";
			link.l1 = "Ez rengeteg pénz, tengerész. Párizsban is jól megélhetne belôle.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Nem fogom kihasználni a tudatlanságát. Itt a Karib-tengeren 500 peso semmi. A kapitányok és a kereskedôk annyi árut hoznak, hogy minden használható dolog ára az egekbe szökik. Néha egy ritka penge annyiba kerül, mint egy kis hajó.";
			link.l1 = "Ez ôrültség.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "Mit is mondhatnék? Mindannyian arra várunk, hogy a dolgok stabilizálódjanak és az árak normalizálódjanak. Szóval, szeretnél 500 pezót keresni?";
			link.l1 = "Elôször is, tudni akarom, mi a munka.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "Bizonyára tisztában van a szerencsétlen rumhelyzettel a hajón. De meggyôzôdésem, hogy valahol még mindig maradt néhány üveg. A palackozott rum nem ugyanaz, mint a hordóba töltött. Remek ízû, megelôzi a mérgezést, erôsíti a kart és az egészséget - igazi kincs. Különösen az utazás végén, amikor a horizont kezd megôrjíteni.";
			link.l1 = "És mit csinálnál vele? Miért ne keresnéd meg magad?";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "Mikor lenne rá idôm? Kevesen vagyunk, ezért három emberért dolgozom. Ami a rumot illeti, majd eladom - találok rá vevôt.";
			link.l1 = "Nos, én tisztelem az ôszinteséget egy férfiban.";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "Szóval, elvállalja a munkát? Három üvegre van szükségem.";
			link.l1 = "Megpróbálom, de nem ígérek semmit.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Inkább visszautasítom. Ez a fajta munka nem méltó hozzám.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "Kár, de nem fogok haragudni. Jó estét, uram.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Igen, uram. "+pchar.lastname+"";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Itt van a három üveg rum.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, hoztam neked valamit Monsieur Pinchontól.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Semmi.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "Mindig örülök, ha a szolgálatára lehetek! Mennyivel tartozom ezúttal?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 dublonnal.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 dublont.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 dublont.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "I need to double-check everything. I’ll be back.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "Köszönöm, monsieur "+pchar.lastname+". Adja át üdvözletemet a pénztárosnak.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "Köszönöm, monsieur "+pchar.lastname+". Adja át üdvözletemet a pénztárosnak.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "Köszönöm, monsieur "+pchar.lastname+". Adja át üdvözletemet a pénztárosnak.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold42":
			dialog.text = "Köszönöm, monsieur "+pchar.lastname+". Adja át üdvözletemet a pénztárosnak.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Köszönöm, monsieur "+pchar.lastname+". Ügyes munka volt!";
			link.l1 = "Remélem, én is ilyen ügyesen kapom meg a fizetésemet.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "Megfontolná a nem pénzbeli fizetést?";
			link.l1 = "Úgy tûnik, nem vagy olyan becsületes, mint amilyennek állítod.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Nem, nem, nem! Ha pénzt akar, pénzt fog kapni! De én is meg tudok osztani némi tudást.";
			link.l1 = "Miféle tudást?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Sok mindent el tudok mondani a tengerészetrôl, amit nem talál a tudományos könyveiben.";
			link.l1 = "Rendben, akkor adja meg nekem életem legdrágább leckéjét.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Ötszáz borravaló nem váltja ki az ötszáz érmét. Elfogadom a pénzt.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Tessék, monsieur "+pchar.lastname+". És még egyszer köszönöm!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
			AddMoneyToCharacter(pchar, 500);
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "Ôszintén remélem, monsieur "+pchar.name+", hogy a leckém hasznosnak bizonyul. Tudja, mi az a navigáció?";
			link.l1 = "Meglepôdne, de tudom. Még olvasni is tudok. A navigáció a térbeli helyzet meghatározása és az útvonal kijelölése, például egy hajó számára.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Aha. Úgy érti, csillagok és térképek. Nem, én nem ismerem ezeket a dolgokat. Az a navigátornak vagy a kapitánynak való. Errefelé a navigáció a hajó irányításának és vezetésének képességét jelenti.";
			link.l1 = "Ki van 'errefelé'?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "A Karib-tengeren. Ez így van, ne kérdezd, miért. Tehát, minél jobb a navigáció, annál nagyobb sebességet és manôverezôképességet tudsz kicsikarni a hajóból. A legénységed is gyorsabban kezeli a vitorlákat. De nem ez a legfontosabb.";
			link.l1 = "Te aztán tudod, hogyan kell feszültséget teremteni.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Minél jobb a navigációd, annál nagyobb hajót tudsz irányítani! Ha túl fejlett hajót veszel, elveszíted a koncentrációdat, az energiádat, sôt, még az egészségedet is!";
			link.l1 = "Veszélyesen hangzik. Furcsa, hogy ilyen sokáig életben maradtam anélkül, hogy tudtam volna róla.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Szerencsére nem kell mindenben szakértônek lenned. Bármikor felbérelhetsz egy jó navigátort, hogy fedezze a hiányosságaidat. Csak gyôzôdj meg róla, hogy fizetett és lojális. Elveszíteni egy navigátort egy olyan hajón, ami meghaladja a képességeidet - nem jó móka.";
			link.l1 = "Köszönöm az elôadást, Henry. Nem biztos, hogy szükségem lesz rá, de azt hiszem, sosem lehet elég tudásod.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "Szívesen, monsieur "+pchar.lastname+". És még egyszer köszönöm!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(énekel) Michel anya az, aki elvesztette a macskáját... Aki kiabál az ablakon keresztül, hogy ki adja vissza neki...";
			link.l1 = "Mit keresel itt, tengerész?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "Szóval most olyan vagyok, mint madame Michel - keresem a macskát. Csak én nem kiabálok - ô nem szereti a kiabálást.";
			link.l1 = "Ma reggel láttam ôt - megint a csizmámat karmolta.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "Ez semmiség. A kapitány csizmája rosszabbul járt. Szereti a macskákat?";
			link.l1 = "Persze, hogy szeretem.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Nem igazán.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Érthetô. Különben hogy bánnánk el azokkal az átkozott patkányokkal?";
			link.l1 = "De nem lehet örökké a macskákra hagyatkozni, ugye? Elég akaratos teremtmények.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Kár. A macskákat szeretik és megbecsülik a fedélzeten. Máskülönben hogyan bánnánk el azokkal az átkozott patkányokkal?";
			link.l1 = "De nem lehet örökké a macskákra hagyatkozni, ugye? Elég akaratos teremtmények.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "Ez igaz. Tehát az arzénre támaszkodunk. Csak sok szerencsét a Karib-térségben. Így elveszítjük a rakományt - a patkányok beszennyezik a rumot, tönkreteszik a hardtackot, és minden mást megrágcsálnak\nÉs a pénztárosunk azt mondja: 'Relax, ez olyan, mint egy kereskedelmi adó'\nDe mi tudjuk az igazságot: ô csak lusta. Ha nem lenne a mi drága Chantalunk, a kapitány már régen a raktérben lakna, és maga fogna patkányokat, ha-ha!";
			link.l1 = "Sok szerencsét a macskával. Mennem kell.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "Várjon, uram. Egy közönséges matróz általában csak a nemes utasokat látja a fedélzeten, de ön itt van - egészen lent a raktérben!";
			link.l1 = "A kíváncsiság megölte a macskát, ha-ha!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "Érdekli a tengerészet, ugye?";
			link.l1 = "Úgy tûnik, a legénység minden tagja elhatározta, hogy igazi tengerészt farag belôlem, mielôtt partot érnék.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "Nem meglepô. Bár a tenger sokunknak csak bánatot hozott, szeretjük a munkánkat. És egy tengerész mindig örül, ha egy új ember ôszinte érdeklôdést mutat.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "Most mondja meg nekem: mi a legfontosabb készség egy kapitány számára?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "A navigáció. Ez határozza meg a hajó méretét, amit irányítani tud.";
				link.l1.go = "OldSailor_10";
				notification("A csekk átadva", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Nem fogok hazudni - nem tudom.";
				link.l1.go = "OldSailor_9_1";
				notification("Elégtelen készségszint (6)", SKILL_Sailing);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "Ne bosszankodjon, monsieur. Beszéljen a legénységgel, fedezze fel a hajót. Ha megtalálja a választ - valami igazán lenyûgözôt fogok megosztani önnel. Mintha közülünk való lenne.";
			link.l1 = "Ezt észben fogom tartani. Viszontlátásra!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "Helyes! Most jön egy trükkösebb kérdés: szögletes vitorla vagy orrvitorla - melyik a jobb?";
			link.l1 = "Nehéz megmondani, de érzem a trükköt. Szerintem mindkettônek megvan a maga elônye.";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "Megint igazam van! A négyszögletes vitorlák nagyszerûek, ha a szél a hátad mögött van. De egy orrvitorla képes fordítani és elkapni még az oldalszelet is. Jó látni, hogy nem vesztegeti az idejét, monsieur.";
			link.l1 = "Nem biztos, hogy ez a tudás valaha is hasznos lesz... Hacsak nem akarok lenyûgözni egy elôkelô hölgyet azzal, hogy igazi tengerésznek adom ki magam, ha-ha!";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "Ó, nem is tudom, monsieur "+pchar.name+". Lehet, hogy ön nemes - de tisztességesen bánik velünk. Ezt értékeljük. A kapitány készül valamire. Egy fekete macska keresztezte az útját.";
			link.l1 = "Ostobaság. Mirôl beszélsz, tengerész?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Az a hír járja, hogy néhány nappal ezelôtt levelet küldött Capsterville-be egy átutazó hajóval\nés elsodródott - pont az út végén, amikor mindenki a partraszállásért üvölt.";
			link.l1 = "Nem érdekelnek a pletykák. Miért is érdekelne? Csak megkérdezhetem tôle. Egy nemesembertôl nem tagadná meg az egyenes választ.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "Nem ismeri ôt, monsieur "+pchar.name+". Ô igen - és hogyan. És most dühös - elvesztette a kulcsát.";
			link.l1 = "Kulcs?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "A ládájához, a kabinban. Gondolom, valahol itt hever valahol.";
			link.l1 = "Megtalálta a kulcsot? Én?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "Ez csak rajtad múlik\nApropó, monsieur "+pchar.name+", maradt még rum? Biztos nem adtad az egészet Henrynek, ha-ha!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "De igen. Tessék, tessék.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Attól tartok, nem. Csoda, hogy egyáltalán megtaláltam azt a három üveggel.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "Ez igaz. Sok szerencsét, monsieur "+pchar.name+". Tovább keresem azt a csíkos gazembert.";
			link.l1 = "Magának is sok szerencsét, tengerész.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "Jó szolgálatot tett a legénységnek, monsieur "+pchar.name+". Itt egy kis szerencsét hozó bûbáj!";
			link.l1 = "Egy lyukas kô? Milyen kedves.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Nevess csak, ha akarsz. A tengeren a talizmánok nem ártanak.";
			link.l1 = "Ti tengerészek babonásak vagytok. Sok szerencsét nektek.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "Máris megtaláltad a választ? Mi a legfontosabb képesség egy kapitány számára?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "A navigáció. Ez határozza meg a hajó méretét, amit irányítani tud.";
				link.l1.go = "OldSailor_10";
				notification("A csekk átadva", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Még nem.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Elégtelen készségszint (6)", SKILL_Sailing);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Hé, fiacskám!";
			link.l1 = "Nem úgy nézel ki, mint az apám. Hála Istennek.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Hah! Büszke lennék egy ilyen magas, nemes fiúra. De én csak a föld sója lehetek, mint én magam.";
			link.l1 = "Rendben, elfogadom a bókot. Mi a baj?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Segítô kézre van szükséged, fiam. Parancsot kaptam, hogy az ágyúknál lôjek, ha bajba kerülnénk ezeken a veszélyes vizeken. A fél ôrséget azzal töltöttem, hogy ezeket a vasfattyúkat felhúztam a raktérbôl, és az utolsó ládánál már nem bírom a hátam.";
			link.l1 = "Miért nem kérdezi meg a haverjait? Azt hittem, ti tengerészek segítetek egymásnak.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Egy dolog, amit a testvériségünk határozottan utál, az a nehéz terhek ok nélküli cipelése. Ma én húztam a rövidebbet - lôszeres ládákat cipeltem a raktérbôl. Pocsék munka, egy ilyen kaliberû matrózhoz képest. De mit lehet tenni?";
			link.l1 = "Hagyd abba a nyafogást. Majd én segítek. Legalább megnézhetem azt a raktérséget, amivel mindenki fenyeget engem.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Athlete) Látod ezt a kardot az övemen? Többet nyom, mint te. Hozom az injekciót - nem okoz gondot.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Én nem végzek fizikai munkát, matróz. Hozd a saját ládáidat.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Köszönöm, fiam. Csak a hátadat ne dobd ki!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ожидание выстрела
			dialog.text = "Hogy vagy, fiú?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Itt van a képed. Azt hittem, nagyobbak lesznek.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Paulnak hívnak, ugye?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Ég veled!";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Ööö... igen.";
			link.l1 = "A neve rajta van a listán, amit Pinchon úr adott nekem.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Hú, egy pillanatra elgondolkodtam... Igen, Paul - én vagyok az. Mennyi van a számomra?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 dublont.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 dublont.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 dublont.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "I need to double-check everything. I'll be back later.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Köszönöm, fiam.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Köszönöm, fiam.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Köszönöm, fiam.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Ha nagyobbat adnék, az ellenségnek ajándékoznám! Ha eltalálja a hajótestet - nos, talán csak szilánkokra törik valaki. De ha a tatba csapódik, az egész fedélzeten pattogni fog, mint egy labda!";
			link.l1 = "Láttál már ilyet?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Magam is láttam, fiam. Az ember igazán jó a gyilkológépek feltalálásában. Vegyük a grapeshotot - kis hatótávolságú, nem törik át a hajótestet, de egy tucat embert egyenesen a másvilágra küldhet. Vagy a lánclövés - eltalálja a vitorlákat és szalagokká változtatja ôket! Ami a bombákat illeti - nem mondok semmit, soha nem láttam egyet sem, és hála Istennek! Az ördög eszközei, ráadásul drágák.";
			link.l1 = "Már láttam, milyen halálosak az ágyúgolyók - kérdezd csak meg szegény hátadat.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Nos, ezzel nagy szívességet tettél nekem. És én viszonzom. Tessék - egy majdnem teli üveg kiváló rum, ha-ha!";
			link.l1 = "Honnan szerezted? Azt hallottam, hogy a rum már régen elfogyott. Ennyi áruval bárkit rávehettél volna, hogy ne csak egyet, hanem az összes ládát elhozza a raktérbôl.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "Így történt, fiam. Köszönöm és viszlát.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, monsieur "+pchar.lastname+". Ha azt tervezi, hogy alszik - nincs szerencséje. Az ágyúsunk lefoglalta az ágyát. Mint tudja, felébreszteni ôt elég trükkös.";
			link.l1 = "Meg kell mondanom, amikor kell - mindent tökéletesen hall!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "Нет.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "Ez semmiség. Hallottam, hogy Sharp legénységének volt egyszer egy vak ágyús. Azt mondták, az ágyúk hangja alapján célzott.";
			link.l1 = "Maga ma feltûnôen beszédes, monsieur boatswain.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "Ennek oka van! Hamarosan partra szállunk - itt az ideje, hogy a megmaradt árut csilingelô pesókra váltsuk. A Saint-Pierre-i bordélyházak mindig örömmel fogadják azokat, ha-ha!";
			link.l1 = "Furcsa, hogy maga, és nem a pénztáros intézi a pitiáner kereskedelmet a fedélzeten.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "A pénztáros nem tud beszélni az emberekkel! Erre való a hajóskapitány - jól bánik a szavakkal és a munkával, ha-ha! A pénztárosnak persze megvan a saját terve, de én nem fogok belemerülni azokba a zavaros vizekbe.";
			link.l1 = "És mi a mai ajánlat?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Az utolsó üveg rum a hajón, néhány szerencsehozó... és voilá! Egy teljes kincses térkép.";
				link.l1 = "Kereskedônek kéne lenned, nem hajóskapitánynak! Lássuk, mit találtál.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Még valami?";
				link.l1 = "Lássuk, mit tudsz.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Bûbájok? Mint az, ami a mellkasodon lóg?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Bocsánat... kincses térképet mondtál?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Talán majd máskor.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;

		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Á, éles szemek, monsieur. Igen, a 'Coral Head' - egy szép dolog. Különösen nekem. Ha nekem kell vezetnem egy hajóhadat - segít összeszedni az embereket.";
			link.l1 = "Tényleg elhiszi ezt?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "Nem kell elhinnem. Így mûködik a Karib-tenger és a tengerészek sorsa. A bûbájok hasznos dolgok. Szóval ha velünk maradsz, javaslom, hogy legyen nálad néhány - különbözô alkalmakra.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Ó, igen. Ez nem szokatlan a Karib-tengeren. Van, akinek szerencséje van - nagyot üt. Aztán vagy adót fizetnek, nyugodtan és sokáig élnek... vagy elrejtik az aranyat egy barlangban. És ami marad, az egy sír, egy kincs... és egy darabka papír.";
			link.l1 = "Csak így?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Nem egészen. A térképek drágák, és vonzzák a hozzád hasonló vadászokat. És néha a zsákmány alig fedezi a fáradságot. Eleinte még a nagy Albert Blackwoodnak is nehéz dolga volt. Legyen a kincsvadászat a szakmád - minél többet találsz, annál nagyobb a jutalom. És ha van egy szerencsehozó kabalád - annál jobb!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! Egy pillanat.";
			link.l1 = "Már megint a kioktatás, monsieur Pinchon? Nem nyúltam a drága tintájához!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "Akkor mivel firkál a kis könyvébe? Szentelt vízzel? Nem volt tinta az utasok leltárában. Különben is, most nagyobb gondjai is vannak.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "És még kétszáz - az elromlott csörlôért. A horgonykötél elszakadt.";
			dialog.text = "Tartozol még harminc pezóval a hajó kincstárának - az esôhordóért, amit tönkretettél. A fergeteges próbálkozásod, hogy kimosd az inged, még többe került volna, ha nem esik megint az esô az imént. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Pont erre volt szükségem - adósságok a hajóról. Tessék, tessék.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Pont erre volt szükségem - adósságok a hajóról. Tessék, tessék.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "Ennyi? Ez nem szerencsejáték adósság. Kicsit elfoglalt vagyok - várnia kell, amíg kikötünk.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Kár. Rendben - az üzlethez. Van egy feladatom a számodra.";
			link.l1 = "Maga nem éppen egy emberbarát, ugye?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "Egy pillanat, hadd számoljam meg.";
			link.l1 = "Ne felejtsd el megszámolni a kenyérmorzsákat, amiket vacsora után az asztalon hagytam.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "Gratulálok. A hajó kincstárának nincs több kérdése hozzád. Egyelôre.\nRögtön a lényegre térek - van egy feladatom számodra.";
			link.l1 = "Maga nem éppen egy emberbarát, ugye?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "Emberek? Nem igazán. De jól bánok a számokkal.\nMaga, monsieur "+pchar.lastname+" - tud számolni?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Könyvelés) Nem idegenek számomra a fôkönyvek és a váltók. Még azt is tudom, mit jelent a nulla.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Eleget ahhoz, hogy apám szûkös zsebpénzét a szezonra kihúzzam.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "Ooooh! Kár, hogy nem szóltál hamarabb - ez az utazás sokkal érdekesebb lehetett volna.";
			link.l1 = "Említettél egy feladatot?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "A saját érdekedben remélem, hogy soha nem leszel hajótulajdonos. Csôdbe juttatnád magad - és mindenki mást is a fedélzeten.";
			link.l1 = "Említettél egy feladatot?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Igen. Nem biztos, hogy tisztában van vele, de a pénztáros és az orvos - a kapitány után a második helyen áll.\n" +
			"Ha bármelyikük nélkül vitorlát bontasz, az a pénzedre is kockázatot jelent. Pénz nélkül pedig egy hajó csak egy nagyon drága fadarab.\n" +
			"Még egy kis sloop is csôdbe viheti a kapitányát pénztáros nélkül. És az elsô csata orvos nélkül akár az egész legénységet is kiirthatja - kiváltva az utánpótlás felvételének és kiképzésének hosszú és költséges folyamatát.\n" +
			"Szerencsénkre mindkettônknek mindkettô szolgálok. Ez lehetôvé teszi számomra, hogy személyes kereskedelmet folytassak, és kisebb szolgáltatásokat kérjek a legénységtôl.\n" +
			"Természetesen bôkezûen fizetek - és most itt az alkalom erre.\n" +
			"Azt akarom, hogy fogd ezt a listát, ezt a láda dublont - és fizess a legénységnek.\n" +
			"Pontosan a lista szerint! Ezért kérdeztem, hogy tudsz-e számolni.";
			link.l1 = "Miért nem csinálod te magad? Ha fizetést várnak - hadd jöjjenek hozzád.";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "Túl sok a dolgom most. Már csak napok vannak hátra az útból - és hamarosan száz matróz áll majd sorba a fizetését követelve.";
			link.l1 = "Említetted a dublonokat...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "Spanyol aranyérme. Kemény valuta. A gazdagság igazi mércéje. Csak a legritkább, legértékesebb szolgáltatások mennek ezekért.\nAz ilyen ládákban tárolják a kényelem érdekében.";
			link.l1 = "És mit kapok érte?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(könyvelô) 150 pezót, és 5 dublont pluszban - gyakorlatilag azért, mert a kollégám. És tisztességes árfolyamot kapsz a peso és a dublonok között.";
			}
			else
			{
				dialog.text = "150 peso, és a lehetôség, hogy pesót dublonnára váltsunk. Nem sok, de a munka egyszerû.";
			}
			link.l1 = "Rendben. Add át a listát és a ládát.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Attól tartok, ez a fajta munka nem nekem való. Viszlát, Monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Ön választ. Csak ne álljon az utamba, uram. "+pchar.lastname+"";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Tessék. Az isten szerelmére - ne felejtsd el kivenni a ládából a dublont, pontosan kövesd a listát, és ne tegyél zsebre semmi feleslegeset. Az üres ládát is visszavárom.\nNe erôltesse meg magát, monsieur. Miért cipel ennyi kacatot? Javaslom, hogy néhány dolgot rejtsen el a ládában.";
			}
			else
			{
				dialog.text = "Tessék, tessék. Az isten szerelmére - ne felejtsd el kivenni a ládából a dublonokat, pontosan kövesd a listát, és ne tegyél zsebre semmi felesleget. Az üres ládát is visszavárom.";
			}
			link.l1 = "Ahogy kívánod. Hamarosan találkozunk, monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
				
		case "OfficerKaznachey_12_Wait":
			dialog.text = "Hogy ment? Mindet kifizette? Megkaptad a maradék dublont és az üres ládát?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && PCharDublonsTotal() >= 18)
			{
				link.l1 = "Mindent elintéztem.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Még nem, monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Lássuk csak...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = PCharDublonsTotal();
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "És még azt állítottad, hogy tudsz számolni. Kevesebb dublont adtál vissza, mint vártad. Ez több munkát jelent nekem, nem kevesebbet - és ez azt jelenti, hogy nem kapsz fizetést.";
				link.l1 = "De akkor is cserélsz dublont?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "És azt állítottad, hogy tudsz számolni. Többet hoztál vissza, mint kellett volna. Ez több munkát jelent nekem, nem kevesebbet - és ez azt jelenti, hogy nem kapsz fizetést.";
				link.l1 = "Mi a helyzet a cserével?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Minden rendben. Jó látni, hogy a fiatalabb generáció még tud számolni. Köszönöm, monsieur "+pchar.lastname+". Itt a fizetése - és egy kis bónusz, egyik szakembertôl a másiknak.";
					link.l1 = "És a csere?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Minden rendben. Örülök, hogy a fiatalok felelôsségteljesen bánnak a pénzzel. Köszönöm, monsieur "+pchar.lastname+". Itt a fizetséged.";
					link.l1 = "Még mindig cserél?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Miért ne. 115 pezó dublónánként. Jöjjön el hozzám, ha érdekli.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Természetesen. 105 peso egy dublóna. Jöjjön el hozzám, ha érdekli.\nHadd adjak egy tanácsot: ha a sors valaha is egy hajó élére állítja, elsô dolga legyen, hogy felvegyen egy kincstárnokot. Még egy szegény is megspórol egy vagyont.";
			link.l1 = "Köszönöm, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Hát persze! 100 peso egy dublóna - ez egy tisztességes ár. A karibi bankok ennél többet kérnének.\nHadd adjak egy tanácsot: ha a sors valaha is egy hajó élére állít, elsô dolgod legyen, hogy felveszel egy pénztárost. Még egy szegény is egy vagyont spórol meg neked.";
			link.l1 = "Köszönöm, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Lófrál, monsieur "+pchar.lastname+"?";
			link.l1 = "Magát is a raktérbe osztották be?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Én vagyok a hajóorvos, "+pchar.lastname+"! Hamarosan tele lesz a kórterem sebesültekkel, és több vért fogok látni, mint bármelyik harcos. És még ha csak a pénztáros lennék is, akkor is a tûzvonalban foglalnám el a helyem. Nem, csak téged küldtek pihenni a kényelmes raktérbe.";
			link.l1 = "Akkor mit keresel idelent?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "A csata csak néhány óra múlva kezdôdik, úgyhogy itt az ideje, hogy lezárjuk a napi számlákat. Nálad van a ládám a dublonokkal, de Maure. Légy szíves add vissza.";
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Tessék. És ne mutatkozz még egyszer itt lent.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "Máshol hagytam a cuccodat.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = PCharDublonsTotal();
			dialog.text = "Nem állt szándékomban. Nem vagyok szárazföldi, nem a raktérben van a helyem. Viszontlátásra.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "Valahol máshol... Ezt majd a csata után megbeszéljük - a kapitány jelenlétében. De addig is...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "Érdekli a dublon, monsieur "+pchar.lastname+"?";
			link.l1 = "Kössünk üzletet.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Most nem.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Kapitány, riadó! Kalózok a láthatáron!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, kérem, kísérje Monsieur "+pchar.lastname+" a raktérbe. És gyôzôdjön meg róla, hogy Monsieur Drussac felébredt és a tüzérek készen állnak.";
			link.l1 = "Kapitány, készen állok a harcra! Egy nemesember nem...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Ha bármiben segíthetek...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Várjon, ez azt jelenti, hogy nincs bordó?...";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, vidd ki innen! Mozgás, ti lógósok! Húzzátok fel a vitorlákat!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, vidd ki innen! Mozgás, ti lógósok! Húzzátok fel a vitorlákat!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, vidd ki innen! Mozgás, ti lógósok! Húzzátok fel a vitorlákat!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
				// <-- Матрос сообщает о приближающихся кораблях
				
				// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Az ördög vigye el! Makacs ördögök!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "Mit keresel itt?! Elhagytad a legénységet és elbújtál a harc elôl, te szemétláda?! Most rögtön kibelezlek!";
			link.l1 = "Rossz húzás volt bemászni a raktérbe. Magam foglak kibelezni.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Alig állsz, és a rajtad lévô vér nagy része nem is a tiéd.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Párbajozó) Hogy én errôl lemaradtam.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "Heh-heh. Akkor rajta, piperkôc.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "Heh-heh. Akkor nincs vesztenivalóm.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "Mirôl fecsegsz?!";
			link.l1 = "Két hónap. Két hónapig kellett a kardomat hüvelyben tartanom. Táncoljunk!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Legalább életben vagy... Nekem végem. Keményen megütöttem a kormányrudat...";
			link.l1 = "Mi történt?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "Felszálltak ránk. Ar-r-gh! Makacs ördögök!\nHallgassatok figyelmesen: az ágyúfedélzetet megtartottuk, de a móka csak most kezdôdik odafent. Esküszöm, bármelyik percben itt lehetnek lent. Fogd a szórópuskát! Ördög, óvatosan! Meg van töltve!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Mesterlövész) Ne aggódj miattam. Bárkit kilyukasztok, aki megpróbálja.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "Szôlôgolyó van benne. Ha jól csinálod, egyszerre kettôt vagy hármat is elintézhetsz.\nHiszek benned, "+pchar.name+". Ha legyôzted ôket, nézd meg a holttesteket. Talán találsz nekem egy italt, különben nem vagyok segítségedre.";
			link.l1 = "Tarts ki, Alonso. Itt jönnek a vendégek!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Rendben... Szép munka, "+pchar.name+". Találtál nekem valamit?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Azt hiszem, ez az. Bár egy kicsit gyanúsnak tûnik.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Még keresem!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "Egyáltalán nem rossz, ha-ha! Köszönöm, "+pchar.name+". És azt a hármat - szépen kivetted ôket. Mivel te tényleg nemes vagy, vedd át a parancsnokságot. Együtt meg tudjuk tartani ezt a paklit. És ha a fiúknak odafent is sikerül - a nap a miénk!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Sokkal jobb. Megtöltötted a szórópuskát?";
				link.l1 = "Csak azt csinálom... Miért lett hirtelen ilyen csend?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Mivel te tényleg nemes vagy, vedd át a parancsnokságot.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Sokkal jobb. Megtöltötted a szórópuskát?";
			link.l1 = "Csak azt csinálom... Miért lett hirtelen ilyen csend?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "Csak a drámaiság kedvéért. Mindjárt kezdôdik.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "Itt fejezzük be, ahol elkezdtük. Köszönöm, hogy megmentetted a bôrömet, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Azt hiszem, kvittek vagyunk. Már nem is emlékszem, hogyan rángattál ki onnan.";
			}
			else
			{
				link.l1 = "Azt hiszem, kvittek vagyunk. Ha te és a fiúk nem lennétek, még mindig ott lennék.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Maradhattál volna a raktérben, ahogy mondták. Kár, hogy a kapitány nem maradt életben, hogy rendesen megdorgáljon.";
			link.l1 = "Egy halom hulla alól kellett kiásnunk. Hány gazembert végzett vele?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Néhányan látták, hogy hármat is elejtett. Mások szerint egy tucatot. Szerintem csak az ördög számolta.";
			link.l1 = "Még mindig nem mondtad el, hogyan alakult így az egész.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "Mit lehet elmondani? A tizenhatfontosaink egyetlen kalózbriggtôl sem mentettek meg minket.\n" +
			"Egy szempillantás alatt rajtunk volt, grapeshot-tal eltalált minket, miközben fordultunk, és rögtön a fedélzetre szállt. Látnod kellett volna a fedélzetet - a sebésznek nem maradt semmi dolga.\n" +
			"A kalózok elleni harc legrosszabb része - nincs nyereség. Csak koldusok. Még a briggjüket sem tudtuk elfoglalni.";
			link.l1 = "És mi lesz a következô lépés?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "A hajó úszik, és maradt annyi legénységünk, hogy menetrend szerint eljussatok Saint-Pierre-be, ahol új kapitányt keresek, te pedig megkeresed a bátyádat, és elmeséled neki a kalandjaidat. Hogy mi következik ezután - csak Isten tudja.\n" +
			"De egy dolog biztos - jól be fogsz illeszkedni hozzánk. Nem rossz egy szárazföldi patkánytól, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "Ha! Mindjárt kezdesz kifordulni. Ne légy szégyenlôs. Ez csak a félelem, ami elhagyja a tested. Üdvözöllek a Karib-tengeren!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}