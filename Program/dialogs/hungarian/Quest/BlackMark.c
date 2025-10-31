void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

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
		
		case "BM_Contra_1":
			dialog.text = "Ki vagy te, és mi a fenét csinálsz itt?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Nyugi, haver. Csak erre járok. Nem fogok beleszólni a... akármi is ez.";
			}
			else
			{
				link.l1 = "Mi? Ez a világítótorony a tiéd? Legközelebb tegyen egy táblát a nevével az egyik pálmafára, vagy építsen egy rohadt kerítést.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Takarodjon innen! Ha elrontja az üzletet azzal, hogy elijeszti az ügyfelet, én...";
			}
			else
			{
				dialog.text = "Figyelj, kölyök, ne akard, hogy én és az embereim elhívjunk, hogy lássuk, olyan éles-e a pengéd, mint a nyelved. Csak tûnj el és...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "Nos, Frankie, melyik az?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "Nem... átkozott legyek, de nem ismerem fel egyik bögrét sem.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "Nem ismerek semmilyen bögrét. Biztos vagy benne?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Azt hiszed, vak vagyok?! Én mondom neked, mi...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Mi a fene?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Ki rúgott ki?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Hülyének nézel minket, te szemétláda? Tegyétek le a fegyvert a földre, mindannyian! És te is!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Csak nyugodjon meg, biztos úr. Nem mi vagyunk azok, nem látja? A fegyvereink ott vannak, ahol voltak. És maga ne nyúljon a sajátjához!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Te parancsolsz nekem, te szemétláda?! Tartóztassa le mindet, most!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Cseszd meg! Ez nem fog megtörténni. Fiúk, fegyverbe!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Hé, hé, vigyázz! Valaki megölhet valakit, ha továbbra is ilyen vadul hadonászik azzal a vasalóval.";
			link.l1 = "Ha, ki?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Engem, természetesen.";
			link.l1 = "Mi a...? Ki a fene vagy te?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "Pontosan ezt próbálom tenni. Megcsináljuk?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_DlgExit_1");
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Tommy vagyok! Tommy Irons. Gondolom. És te ki vagy? Bátor nô vagy, én mondom neked, hogy így járkálsz, hehehe.";
				link.l1 = "Bátor, valóban. És nem félek befogni a szádat, ha kell. Ez egy forró hely, ezért könnyedén öltözködöm - nem azért, hogy neked vagy a fajtádnak örömet okozzak. A nevem Helen MacArthur. A barátaim talán Rumbának hívnak, de maga biztosan nem tartozik közéjük. És hogy mi volt az a 'gondolom' ?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Tommy vagyok! Tommy Irons. Gondolom. És maga?";
				link.l1 = ""+GetFullName(pchar)+". És mit jelent ez 'Gondolom' pontosan?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Ez pontosan azt jelenti, amit jelent. Elvesztettem az emlékezetemet - elég csúnyán összevertek a csatában. Tudod, néha az ember mindent elveszít. De szerencsés vagyok. Csak a nevemet felejtettem el. Szerencsémre van egy medál a nyakamban, amire az van írva, hogy 'Thomas'. De én inkább Tommy. És Irons. Cromwell oldalán harcoltam az Ironsidesben, emlékezzenek rá. De az ‘Ironsides' túl vaskos. Az Irons sokkal jobb.";
			link.l1 = "Már értem, mi a bajod, Tommy. Szóval, mondd csak - mi volt az? Valakit konkrétan megcéloztál? Eltaláltad a célpontot? Vagy csak szórakozásból lôttél? Nem lennék meglepve.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "Eltaláltam, méghozzá keményen! Minden szempontból. Emlékszel azokra a puccos nadrágokra? Követte a nyomomat, és katonákat hozott magával. Egy egész osztagot, csak mert lefeküdtem a feleségével.";
			link.l1 = "Valóban eltaláltad, heh. Gondolom, rajtakapta magukat tetten?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ha! Nem fogod elhinni - nem. A szajha késôbb bevallotta. Bûnös lelkiismeret, vagy talán nem élvezte annyira, mint én, hehe. Ki tudja, mi jár a nôk fejében? Engem nem igazán érdekel, ha-ha-ha-ha!";
			link.l1 = ""+GetSexPhrase("Hmm, ô egy furcsa nô.","Férfiak... Az egyik percben még azt próbáljátok kitalálni, hogy mi van a fejünkben, a másikban meg azt mondjátok, hogy nem érdekel titeket. De egy dologban igazad van - amit tett, az furcsa volt. Csak el kellett volna mennie, és elfelejteni, mint egy rossz álmot. Én is pontosan ezt tenném, ha erre kerülne a sor.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Pontosan! Az emberek azt mondják, hogy valami baj van velem. Sajnálom a katonákat, akik meghaltak. Tudom, hogy így van, én is csak katona voltam egyszer. Nem mondtam neked?";
			link.l1 = "Igen, így volt. A Vaskalaposoktól. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Tényleg? Nem emlékszem, hogy mondtam-e vagy sem. Tudja, hogy kerültem az Újvilágba? Elmondjam?";
			link.l1 = "Nem, és nem is érdekelne, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "De igen, érdekelne. Elmondom.";
			link.l1 = "Rendben, a pokolba vele, csak lôjjön. Úgy értem, rajta.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Akkor ne szakíts félbe! Hol is tartottam? Rendben, szóval megsebesültem, látod? Megkaptam a hivatalos lemondásomat, mert a gyôztes oldalon álltam. De látnod kellett volna a tekinteteket azokon az íróasztal-patkányok' arcán! Azt hitték, hogy csak színleltem, és úgy tettem, mintha elvesztettem volna az emlékezetem. Folyton a családomról kérdezôsködtek.";
			link.l1 = "És mit mondtál nekik?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "Mit mondtam nekik? Azt, hogy nem emlékszem. És nem hazudtam - sosem ismertem a szüleimet. Az utcán nôttem fel, munkások és szolgák a nyomornegyedben. Az ô kedvükért csatlakoztam a forradalomhoz. Bár az emberek hálátlansága megdöbbentô - ha elvesztettem volna a karomat vagy a lábamat, kénytelenek lettek volna egy ilyen hôst, mint én, azonnal nyugdíjazni. És mellesleg majdnem elvesztettem a fejem, szó szerint!";
			link.l1 = "Nos, hogy jutottál el az Újvilágba, háborús hôs?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "Kételkedik benne? A köznépért harcolni - mi ebben nem hôsies? Remélem, egy nap a magadfajta puhányok is megtudják, mi az igazi szabadság!";
			link.l1 = "Bár a szabadság jó dolog, valahogy úgy hangzott, mintha fenyegetés lenne. Rendben, Tommy, folytasd.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Igenis, Tommy, folytasd. A forradalom megnyerése után kaptam meg a lemondásomat, aztán rájöttem, hogy nem tudok mást csinálni, csak lövöldözni és pofonverni az embereket. És nem léphetsz vissza a hadseregbe - kinevetnének, fôleg azok után, hogy olyan keményen küzdöttem a lemondásomért. Heh, nekem úgy tûnik, hogy még ha tényleg el is veszítettem volna egy karomat vagy lábamat, az íróasztali patkányok akkor is azt hitték volna, hogy elrejtem ôket valahol, hogy késôbb visszavarrjam ôket, amint megkapom a kilépési papírjaimat, ha-ha-ha!";
			link.l1 = "Ez vicces. De még mindig nem mondtad el, hogy kerültél ide.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Ó, te olyan unalmas vagy. Nem tanítottak neked türelmet, " + GetSexPhrase("fiatalember","lányom") + "? Otthon nem volt más dolgom, mint kacsákat és szarvasokat lôni, ezért elmentem az Újvilágba. Egy ideig kalózokkal hajózgattam szórakozásból, majd amikor meguntam a törvénytelenséget, zsoldos lettem.";
			link.l1 = "Nem túl eredeti történet.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Talán neked van jobb ötleted? Nincs szükséged testôrre, véletlenül? Mert maga... gyengének tûnik. Aggódom, hogy nem jutsz messzire, hehe. Ne feledd, a kíséret teszi a királyokat. És egy rossz kíséret megbuktathatja ôket.";
			link.l1 = "És miféle " + GetSexPhrase("király","királynô") + " lennék egy ilyen kísérettel, mint te? " + GetSexPhrase("király","királynô") + " a trágyadombon?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "Nem, nem, nem! Én egy ôszinte ajánlatot teszek neked, és te...";
			link.l1 = "Még nem kaptam semmilyen ajánlatot. Mennyit kérsz a szolgálataidért, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "150 dublont elôre! Hogy biztos legyek benne, hogy komolyan gondolja, és nem csak egy bukta. És utána havi díjat. Azt hiszem, megegyezhetünk.";
			link.l1 = "És te nem...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "...gondolod, hogy van hozzá merszed? Heh, nem is vitatkozom veled - láttad, hogy lôttem le azt a felszarvazottat a világítótoronyból? Elsô lövés! Nem alkudtam, ha erre gondolsz. Meg kell mutatnod, hogy megengedhetsz magadnak egy olyan profit, mint én.";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Igen, meg tudok! 150 arany. Tessék.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "Szerencséd volt ezzel a lövéssel. És most megpróbálod feldobni az értékedet a hencegéssel. Egy ilyen profi nélkül is elboldogulok. Túl sok a becsület és túl sok a pénz.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Most nem engedhetem meg magamnak, mert nem hordok annyit a zsebemben. Maradj itt, és ne menj sehova - elhozom az aranyat a hajóról, és visszatérek.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(150);
			
			dialog.text = "Nem is vagy olyan rossz, mint gondoltam! De jobb, ha vigyázol, hogy ne unatkozzak. Nem lenne kár a tehetségemért, ugye? Tommy és " + pchar.name + "! Rázzuk fel a Karib-térséget!";
			link.l1 = "Tanuld meg tisztelni a parancsnoki láncot, Tommy. És másodszor, én vagyok a kapitányod. Megértetted?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Heh, én igen, Unalmas kapitány, " + GetSexPhrase("uram","miss") + ".";
			link.l1 = "Ó, már kezdem megbánni ezt...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_Hire");
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Nos, te egy idióta vagy, fiatal " + GetSexPhrase("férfi","nô") + "! És teljesen hiányzik az ítélôképességed. Javaslom, hogy ezt javítsd ki, különben nem sokáig maradsz életben. Különösen a szigetvilágban.";
			link.l1 = "Megoldom nélküled is, Tommy. Viszontlátásra.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Ez most komoly? Egy csomó katona halt meg itt, zsenikém! Valószínûleg hamarosan küldenek egy másik osztagot. Nem, bezárhatnám a világítótorony ajtaját és megszervezhetném a védelmet, de akarom-e? Nem, nem akarom.";
			link.l1 = "Akkor mit javasolsz?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Találkozzunk egy barlangnál a dzsungelben. Adok neked pár napot, hogy megkeress annyit, amivel kifizetheted a szolgálataimat - tudod, hogyan kell tartani a pengét, talán sikerülni fog.";
			link.l1 = "Komolyan mondod? Olyan leszel ott, mint egy sarokba szorított patkány.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Csak akkor, ha külön keresnek engem, egy nagy osztaggal. Szóval szerintem nem lesz semmi bajom. És most mennem kell - hamarosan itt lesznek. Viszlát késôbb.";
			link.l1 = "Igen, nekem is mennem kell, a biztonság kedvéért.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Igen, hát itt vagy! Már kezdtem azt hinni, hogy nem vagy képes pénzt keresni. Néha azt hiszem, hogy az olyanok, mint te, ezzel születnek. És ha nem, akkor szegénységben halnak meg, anélkül, hogy egy napot is dolgoznának, mint a becsületes emberek.";
			link.l1 = "Nocsak, nocsak, Tommy. Ha nem akarsz csatlakozni a legénységemhez, akkor ne tedd. Látom, szeretsz ebben a lyukban fészkelni.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Nyilván nem bújtál gödrökbe az esôs évszakban Írországban, " + GetSexPhrase("fiatalember","kislányom") + "! De veled menni jobb, mint itt bujkálni. Most pedig, ami az aranyat illeti...";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Itt az aranyad.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Még nem kaptam meg. Gondoltam, megnézem, nem szöktél-e el valahova máshova.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(150);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Most már beszélgetünk! Mi lesz a következô lépés... Kapitány?";
			link.l1 = "Elôször is, tûnjünk el errôl a nyirkos helyrôl, különben elkezdek tüsszögni.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Ó, megpróbálhatnád a háborút. Szinte otthon érzem magam az ilyen helyeken.";
			link.l1 = "Értem, szóval megkaptad a felmondásodat, és elfelejtetted a tiszteletet és az alárendeltséget, mi, Tommy? Ne aggódj, nem fogok habozni, hogy újra megtanítsalak, ha kell. Most pedig menjünk.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Heh, Tommy Irons sosem fut el! Tartja a szavát. Te is megtartod a tiédet?";
			link.l1 = "Dolgozom rajta.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Elhoztad az aranyat?";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "Itt az aranyad.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Még nem kaptam meg. Gondoltam, megnézem, nem szöktél-e el valahova máshova.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsJungleUhodit");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Figyeljen, kapitány...";
			link.l1 = "Mi az, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "Nincs nálad egy extra lôszer? Nem csak egy golyó, hanem egy teljes értékû, papírba csomagolt töltény.";
			link.l1 = "Ez is egy újabb vicc? Én rendszeresen adok neked töltényeket és patronokat, amire csak szükséged van. És miért pont egy töltényt, nem egy maréknyit?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Miért veszed ilyen rossz néven a kérésemet? Nem véres gyöngyöket kérek, csak egy patront. Még a megfelelô pillanatot is kivártam, hogy ne vonjam el a figyelmedet az üzletrôl, és ne álljak az utadba, mint valami ôrült, hehe. Szóval... van egy töltényed?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Igen, van egy töltényem. Tessék, tessék. Csak ne szórakozz velem a golyóval. Megértetted, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Jelenleg nem, nem értem. Nem mintha egyetlen töltényt hordanék a zsebemben, és azon gondolkoznék, hogy mi van, ha Tommy kéri...?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Nos, ez egy jó érv, és te gyorsan felfogtad, hehe. De attól tartok, itt elválnak útjaink.";
			link.l1 = "Komolyan mondod? Megsértôdött egy golyó miatt? Gyerünk, menjünk a hajóra és szerezzünk egyet. Ha olyan sürgôsen kell, hozok egyet, tízet, amennyit csak akarsz.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "Nem. Végül is semmi különös nincs benned. Egy jó kapitány mindig el tudja látni a legénységét mindennel, amire szükségük van. Akkor én megyek.";
			link.l1 = "És ha a tengeren lennénk, elfogyna a rum, és te többet akarnál? Eloldoznád a csónakot és elhajóznál? Vagy beugranál a vízbe?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ha-ha-ha-ha! Nevettem, de ebben a szomorú pillanatban még egy jó vicc sem segít. Viszlát, Unalmas kapitány.";
			link.l1 = "Nos, a pokolba veled, Tommy. Viszlát.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Nem ígérhetek semmit, he-heh-heh. Egy jó vicc könnyedén tartja a dolgokat. De természetesen köszönöm.";
			link.l1 = "Rendben, menjünk, te viccelôdô.";
			link.l1.go = "BM_IronsFirstJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
				TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsFirstJungle");
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Hé, kapitány!";
			link.l1 = "Igen, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Van még egy papírpatrontok?";
			link.l1 = "Mi történt az elôzôvel? És mi volt az a vicc a patronról? Két hete várok valami hülye viccre tôled, de semmi.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Ó, ez egy gyilkos vicc lesz, hidd el. Imádni fogod, hehe. Csak még nem állt össze minden. És mi van a patronnal?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Tessék. Remélem, nagyon élvezem a következô csínyedet. És hova tetted az utolsó kört? Adok belôle bôven. Vagy a harcra való lôszert az egyik helyen tartod, a vicceket pedig a másik helyen?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Nincs nálam lôszer a hülye vicceidhez, Tommy! Két hete egy egész adagot is kérhettél volna, nem csak egy töltényt!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "Megkértem! Azt hittem, hogy aki a kapitányomnak mondja magát, az mindig azt tartja meg, amire a legénységének szüksége van.";
			link.l1 = "Én nem játszom meg magam, Tommy. Már régen úgy döntöttem, hogy önmagam leszek. Akinek megfelel, annak jó. Ha nem, az is rendben van.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Heh, ebben hasonlítunk egymásra. De vannak bizonyos elvárásaim a kapitányommal szemben. És te már nem felelsz meg nekik, fiatalember. És itt elválnak útjaink.";
			link.l1 = "Ez most komoly? Mert nem volt nálam egy átkozott papírpatron?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "Ez szóba sem jöhet. Általában azt tanácsolom az embereknek, hogy azt tegyék, amit szeretnek, és azt vegyék el az élettôl, amit akarnak. Én azt tanácsolnám, hogy a jövôben jobban gondoljon az emberekre. Viszontlátásra.";
			link.l1 = "És azt tanácsolom, hogy vigyázzon a fejére - több kárt tettek benne, mint gondolná. Viszlát, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Majd meglátod. Mindent a maga idejében, hehe.";
			link.l1 = "Ó, rossz érzésem van ezzel kapcsolatban, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
				TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsSecondJungle");
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "Lenne egy kérdésem, kapitány.";
			link.l1 = "Igen, Tommy, mi az?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "Nem találta ki? A találgatás hasznos képesség, hehe. Te, én, a dzsungel... Úgy két hete volt ez a beszélgetésünk. Szükségem van egy másik papírkazettára.";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "Ez kezd vicces hagyomány lenni, nem igaz? Két hét telt el - Tommy kér egy patront. Tessék, tessék. Hány kell még a viccedhez?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Meddig tart még, Tommy?! Meddig fog ez így menni? Ti vaskalaposok csak egy patront kaptok minden csata elôtt?! Nem kell mindig magamnál tartanom egy töltényt a te furcsaságaid miatt, ezt te is tudod!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "Valójában, mint a kapitányom, a te kötelességed, hogy elláss engem mindennel, amire szükségem van a csatákhoz, és még annál is többel.";
			link.l1 = "Össze vagy zavarodva, Tommy. Kötelességed, hogy engedelmeskedj a kapitányod parancsának. Mindig ellátlak titeket mindennel - gyógyszerrel, lôszerrel, rummal. Az, hogy nem veszitek el idôben, amire szükségetek van, és aztán koldusként viselkedtek, csakis a ti hibátok!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Olyan okos vagy - miért nem értél el itt eddig semmi érdemlegeset? Megmondom, miért. Mert nem gondolkodsz elôre, és soha semmire nem vagy felkészülve. Nem tudod, mit csinálsz, te unalmas. Egy ilyen embert nem ismerek el parancsnokomnak, úgyhogy viszlát.";
			link.l1 = "És egyáltalán nem használod a fejed! Jó, hogy megszabadultál tôle, te átkozott bohóc!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Ez is megteszi, hehe.";
			link.l1 = "Végre összeszedted magad? De miért?";
			link.l1.go = "BM_IronsThirdJungle_6";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
				TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Csak meg akartalak tréfálni, hátha visszaváltozol a mogorva önmagaddá. Hehe. De köszi a patront.";
			link.l1 = "Furcsa vicceid vannak, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "Ez is egy vicc volt. Nem gyûjtöttem ôket, hanem válogattam. Szükségem volt egy patronra, ami közel tökéletes. Ez megteszi. Igen, ezzel a lövedékkel a golyó messzire megy. Mint amikor szétlôttem az öreg Reasley fejét, ha-ha-ha-ha!";
			link.l1 = "Az öreg Reasley, azt mondtad... Frankie a felszarvazott, ugye? Akit a világítótoronynál lôttél le? Akkor már régóta ismerik egymást?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "Micsoda? - Nem, nem, nem. Ó, a fenébe is, ez kicsúszott a számon. De nem érdekel - sosem voltam jó a hazudozásban vagy a titoktartásban.";
			link.l1 = "Gondolom, a második golyót valaki másnak szántad, ugye, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Igen, zsenikém. Nos, ismerem magam és a céljaimat, és nem szégyellem. Ezért nem érdekel, mit gondolsz - elmondom az egész történetet, miért ne mondanám el.";
			link.l1 = "Nos, akkor mondd el. Nem árt, ha tudom, mire készülsz.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Nos, ne szakíts félbe, ahogy általában szoktál. Két szemétláda volt velem a társaságban - Francis Reasley és Gabriel Callow. Igazi patkányok! Még rosszabbak, mint azok az irodai patkányok, akik nem adták oda a felmondásomat, amit, tudod, nem volt könnyû megszerezni.";
			link.l1 = "És mit csináltak? Különösen a második, Callow. A feleségével is lefeküdtél? És katonákat is küldött utánad?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Fogd be a szád, jó? Bár... Nem bánnám, hehe. De nem. A királypártiak megtámadtak minket aznap. A lovasság is. Sokkal többen voltak. Gabe és Frankie úgy futott, mint a rémült nyulak. De én a fiúkkal maradtam. Én voltam az egyetlen, aki túlélte. Sok mindent elfelejtettem a gyerekkoromból és a fiatalságomból, de ezt nem.";
			link.l1 = "És bosszút akarsz állni, mert elmenekültek? Nem mindenki harcol egy eszméért. Mindenki a túlélést akarja. Vagy majdnem mindenki. Még ha valaki a forradalomért harcol is, lehet, hogy véletlenül csatlakozott, és megbánta.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ha minden gyávára vadászni akarnék, az egész világot le kellene lônöm. Gyávák, a pokolba velük. De ôk elárultak engem. Mindenkinek azt mondták, hogy elárultam a forradalmat, és a király támogatóinak parancsára lemészároltam az egész századunkat. Hazudtam magának valamirôl, kapitány.";
			link.l1 = "Mi az? Azon kívül, hogy hazudtál arról, hogy Frankie csak azért vadászik rád, mert a feleségével tetted?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "Nem, nem, nem! Nem hazudtam neked, csak nem mondtam el mindent. Ez a különbség. Amirôl hazudtam, az a lemondás volt. Nem volt lemondás. Volt egy bírósági tárgyalás. És a szerencsés öreg Tommy - úgy döntöttek, hogy nem akasztják fel, hanem a déli gyarmatokon lévô kôbányákba küldik. Barbadosra, hogy pontos legyek.";
			link.l1 = "Igen, ez szerencsés volt. Hány évig dolgozott ott?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Egyetlen évet sem. Mivel a földi bíróság elítélt azok miatt a patkányok miatt, a mennyei odafent úgy döntött, hogy megment engem. Amint átkeltünk a szigetvilágba, megéreztük a hangulatát - a hajónkra kalózok szálltak fel.";
			link.l1 = "Tehát a barbadosi kôbányák és ültetvények helyett kalózok adták el rabszolgának? De azt mondta, hogy soha nem dolgozott a kôbányákban.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "Ezt mondtam - valaki odafent úgy döntött, hogy megment engem. Micsoda megmentés volt, hehe! Igazad van - a kalózok gyôztek azok felett, akik szeretik a megkötözött és leláncolt embereket bántalmazni. De még így is forró küzdelem volt, olyan forró, mint itt a nap. És a megmentôink szenvedtek némi veszteséget. Ezért felajánlották mindenkinek, aki csatlakozni akart hozzájuk.";
			link.l1 = "És te csatlakoztál hozzájuk? Azt mondtad, kalózokkal hajózol.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "A pokolba is, igen! Életem legjobb évei. Jack Mills nagybetûs kapitány volt - remélem, egy nap te is olyan leszel, mint ô. Az ô 'Crane' hajóján hajózgattam körülbelül két évig, amíg...";
			link.l1 = "...amíg bele nem fáradt a törvénytelenségbe, ahogy mondta? Miért mondja, hogy azok voltak élete legszebb évei?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... amíg meg nem hallottam, hogy az a két áruló is a szigetvilágban kötött ki. Igen, tudom, mondtam, hogy elegem van a nyílt tengeri kalózkodásból, meg minden. És már mondtam, hogy nem érdekel, mit gondolsz. Ez még mindig igaz, de nem ismertelek jól, amikor elôször találkoztunk. Nem tudtam, hogyan fogsz reagálni. Ezért mondtam különbözô dolgokat.";
			link.l1 = "Hazug vagy, Tommy! De rendben, miért hagytad el a 'Crane'?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Mert Jack igazi vezetô volt, ezért mondta, hogy nem tesz kerülôt egy ember miatt, nem vár rá, nem játszik bosszút, és nem szórakozik a brit haditengerészet prominens tisztjeivel, ahelyett, hogy kövér kereskedelmi hajókat támadna meg.";
			link.l1 = "Prominens tisztekkel? Frank civil volt, azt hiszem.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, nem volt mindig az. Mindig is olyan... tudod, homályos volt. És amikor megpróbált felültetni valakit, szégyenszemre kirúgták. Megpróbált egy kereskedôhajón hajózni, de a becsületes munka nem volt az ô mûfaja. Végül itt telepedett le.";
			link.l1 = "Még mindig nem nevezném kiemelkedô tisztnek.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Ne feledkezz meg Gabe-rôl. Otthon hadnagy lett. És itt Port Royalban kapta meg a kinevezését a hajó, a 'Principio'.kapitányaként.";
			link.l1 = "Nem hangzik túl angolosan.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Jó meglátás! A hajó úgy cserélt gazdát, mint egy kikötôi szûz, így sok mindent látott. De még mindig hajózható. És Gabe egy képzett kapitány, a fenébe is.";
			link.l1 = "És Jack félt vele foglalkozni? Olyan jó, mint amilyennek mondod?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Jól van, jól van! Inkább nem akart idôt pazarolni rám. Ha már Jacknél tartunk, tetszett néhány hagyomány, amit elôször láttam tôle - a deszkázás és a fekete jelek kiosztása. Ez akkoriban egy vicces ötletet adott nekem.";
			link.l1 = "Fekete... jelek? Úgy érti, fekete foltok, ugye? És mi volt az, Tommy? Nem hiszem, hogy tudná, mit tegyen, ha egy fekete foltot adnál neki. Ez történt? Át akartad adni, ô pedig megtámadott, amint meglátott, ezért a világítótoronyhoz rohantál, ô pedig egy csapat katonát vitt magával, és azt mondta nekik, hogy kalóz vagy?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Én inkább fekete foltnak nevezném. Az jobban hangzik. Egy egyszerû fekete jel semmit sem tudatosult volna benne. De egy fekete jel, amit a selyemzsebkendônkbôl készítettünk, ami a társaságunk megkülönböztetô jegye volt - azt megértette volna. Diszkréten a zsebébe csúsztattam. Aztán megbizonyosodtam róla, hogy látja, amint a világítótorony felé tartok. A többit már tudod.";
			link.l1 = "És a csempészek?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Rossz helyen, rossz idôben. Még egy kicsit meg is sajnáltam ôket. De csak egy kicsit, hehe.";
			link.l1 = "És Frankie-t?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Most kit érdekel? Nagyobb dolgunk is van. Marad Gabe. Az trükkös lesz. Meg kell...";
			link.l1 = "Mi?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Nos, egy dolog egy érdekes történetet megtanulni, és egy másik dolog, ha te magad találsz ki egyet! Szóval a terv a következô. Hagynunk kell Gabe-nek egy másik különleges fekete jelet - én már csináltam egyet. Aztán követjük a nyomát Portland Cove-ba, ahol nyom nélkül elintézzük.";
			link.l1 = "És hova fogjuk elhelyezni?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ha ha ha ha, erre gondoltam, amikor azt mondtam, hogy bárcsak jobban hasonlítana Jackre, kapitány. Gyerünk, ne unatkozz, látom, hogy ég a szemed!";
			link.l1 = "Inkább csak érdekel a története.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "A házában, természetesen! Miféle kérdés ez? Port Royalban telepedett le. Szóval mi ketten az öbölben fogunk kikötni, így el tudjuk hagyni a szigetet, ha bármi baj történne.";
			link.l1 = "Tudja, hol van a háza?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Nem, nem tudom. De nem nehéz kideríteni. Megkérdezzük a részegeseket - az anyjukat is eladnák, ha meghívnád ôket egy-két italra. Nos, mit gondolsz a tervemrôl?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Ha ô egy Jamaicába tartó hajó kapitánya, akkor állandóan a sziget vizein járôrözik. A hamis zászló alatt történô támadás jobb, mintha a városban próbálkoznánk.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Képességellenôrzés megfelelt", SKILL_SAILING);
				notification("Képességellenôrzés megfelelt", SKILL_ACCURACY);
				notification("Képességellenôrzés megfelelt", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Képességpróba Sikertelen (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Képességpróba Sikertelen (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Képességpróba Sikertelen (25)", SKILL_GRAPPLING);
			}
			link.l2 = "Nem hibátlan, és sok mindent a szerencsére bízol. De összességében megoldható. Veled vagyok, Tommy. Az egyiktôl megszabadultál, a másikat nem hagyhatod elmenni, ugye?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "Nem fogok belekeveredni a bosszúdba, és nem kockáztatom az Angliával való kapcsolatomat ezért a kalandért, ahol annyi minden múlik a véletlenen, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Kockázatos vagy, kapitány! Kezdem megkedvelni magát. De Gabe az öreg 'Principio' nem könnyû préda - ô sokkal veszélyesebb, mint más kapitányok egy ilyen hajón.";
			link.l1 = "Mit gondolsz, mi vagyok én, egy gyáva, Tommy? Mi magunk megyünk a fedélzetre, és te majd elbeszélgetsz vele. Adj neki egy fekete pontot, mielôtt leváltják.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Lehet, hogy te nem vagy gyáva, de ô az, bár nagyon okos. Nem fog megtámadni egy katonát, de még egy kalózt sem, aki nagyobb, mint a hajója. Ha ilyesmit lát a láthatáron, akkor az erôd szárnya alá bújik.";
			link.l1 = "Hmm, mi van a kereskedelmi hajókkal?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Igen, ez mûködhet! De ismétlem, semmi nagyobb, mint egy bárka vagy barquentine! Gabe nem csak gyáva - sosem volt eléggé kapzsi ahhoz, hogy ez felülírja az óvatosságát.";
			link.l1 = "Reméljük, hogy mûködik, Tommy. Szóval, egy ötödosztályú bárka vagy barquentine spanyol vagy holland színekben. Készülj fel a régi harcostársaddal való találkozásra!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Tudtam, hogy számíthatok rád! Talán még Jacknél is jobb kapitány leszel egy nap. És ami a szerencsémet illeti... Be is az segített, úgyhogy most is számítok rá. Akkor mehetünk?";
			link.l1 = "Igen, ne húzzuk ezt túl sokáig. Minél hamarabb vége, annál jobb.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Heh, én másban reménykedtem, de erre számítottam - neked nincs merszed az ilyesmihez, " + GetSexPhrase("fiatalember","lányom") + ". Minden igazi kapitánynak volt már legalább néhány ilyen esete, amikor diszkréten elintézte a patkányokat. Néha még a saját patkányaikkal is.";
			link.l1 = "Gondolom, be kéne dôlnöm a provokációnak, és azt mondani, hogy meggondoltam magam, és bebizonyítom, hogy igazi kapitány vagyok, mi, Tommy? De megértem a bosszúvágyát. Nem foglak arra kényszeríteni, hogy elhagyd a legénységet, mint Jack tette. Mennyi idôre van szükséged ehhez? Addigra Jamaikára érek.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ha ha ha ha, felnôttél. Majdnem tisztellek, hogy nem dôlsz be neki. De nem kell megvárnod, hogy utána értem jöjj - ezt magam is befejezem. Végül is mindig is csak azt akartam, hogy valaki hajlandó legyen tenni értem valamit, mint a kapitányom. Szóval viszlát. Vigyázz Angliára, ha-ha.";
			link.l1 = "Te tényleg furcsa vagy. De ahogy kívánod. Viszontlátásra! És sok szerencsét a bosszúdhoz, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsThirdJungle_Otkaz");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Nagyszerû, gyorsan visszavonulhatunk innen, ha szükség lesz rá. Fogd ezt - adja át Gabe-nek a cetlit és a fekete jelet, amint megtudja, hol lakik és mikor van otthon.";
			link.l1 = "Ó, szóval most már te vagy a fônök, Tommy. De ne feledd, még mindig én vagyok a kapitányod. Mit tervezel csinálni, amíg a városban vagyok?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, hogy is felejthettem volna el, Unalmas kapitány? Ha Gabe meglát az utcán, vagy riadót fúj, vagy lelép a szigetrôl, az a rohadt gyáva. Ne aggódj, itt fogok csapdát állítani, hehehe.";
			link.l1 = "Csapdát, azt mondod. Rendben, Tommy. Adjunk a régi háborús bajtársadnak egy rendes találkozót, ha ha ha ha ha ha!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hic! Ez remek rum! Hic... Egészségünkre!";
				link.l1 = "Figyelj, pajtás, mi a hír a városban Gabriel Callow kapitányról?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Az öreg Gabe-rôl?! Csak jókat! Miért, hic, mi az?";
			link.l1 = "Ó, tényleg? Örömmel hallom. Hát, egy kalózzal baj van. A parancsnok többnyire szárazföldi ügyekkel foglalkozik, és én nem akarom zavarni Ôlordságát.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Akkor menj egyenesen Gabe-hez, én mondom neked! Nincs becsületesebb és bátrabb kapitány a városban, mint Gabe. Még Doyley ezredes is nagyra tartja. Egy olyan hajót vezet, ami egykor Nicolas Sharpé volt, el tudod ezt hinni?";
			link.l1 = " Még nem vagyok elég részeg ahhoz, hogy ezt elhiggyem, pajtás.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "Igen, de te igen! Ez a Principio! Ismerôsen cseng, mi?";
			link.l1 = "Egy spanyol trófeahajó, ugye? Egy spanyol hajó, mi?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "Mikor láttál utoljára rózsaszínt a saját szemeddel, mi? Tudom, mit mondok, fúj!";
			link.l1 = "Nos, nem tudom, hogy a hajó kialakítása annyira szokatlan-e.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "De az! Senki sem parancsolna ilyen ócskaságot, most, hogy ennyi új tervezésû hajó van körülöttünk! Már majdnem harminc éve nem gyártanak ilyeneket a hajógyárakban! Nic maga vitorlázott vele, én mondom.";
			link.l1 = "Rendben, megveszem. Szóval, ez az a hajó. Hogyhogy még nem esett szét ez a roncs?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "mi";
			else sStr = "az";
			dialog.text = "Nos, már nem olyan gyors, mint a legjobb éveiben volt - mint én egy újabb ital után, ha-ha-ha-ha! De egy jó kapitány még mindig ki tud hozni valamit ebbôl az öreg hölgybôl. Gabe igyekszik ôt sem a tûzvonalba állítani.";
			link.l1 = "Akkor miért nem nevezték át a hajót? Talán Ôfelsége Hajótörô, a " + sStr + " régi rendszer alatt?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Hagyományos... Trad-trad-tradíció, fúj! Nic maga sem nevezte át, miután elmenekült egy kubai spanyol ültetvényrôl. Soha nem akarta elfelejteni az élményt - és a spanyolok sem! Hadd mondjam el, az a csata Tendales partjainál...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, igaz? Utoljára gyerekkoromban hallottam ezt a nevet. Nem gondoltam volna, hogy még mindig tud és emlékszik valaki ezekre a most már elhagyatott sziklákra.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Tendales? Hol van ez?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Vagy az volt a Highrock? N-nem, biztosan nem ott... Mindegy, nem számít! Nic harcolt és gyôzött abban a rózsaszínben, hihetetlen gyôzelmet aratott a Cuttlefish nevû brigg ellen, amelyet Desmond Ray Beltrop kalózbáró küldött utána. Sokáig rontották egymás vérét, mígnem Nic maga vágta le Desmondot.";
			if (startHeroType == 4)
			{
				link.l1 = "Hû, ez lenyûgözô! Bár Nicholastól nem is várna mást az ember. Eh, a Sharps és a Beltropok mindig együtt vannak, aztán külön - úgy látszik, a történelem tényleg megismétli önmagát idôrôl idôre.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Lenyûgözô. Szóval, hogyan vált meg Sharp a hajótól? Eladta a hajógyárban?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Nem. A beszállás után elkezdett szivárogni, így Nic elhagyta. Aztán a nagy dagállyal a rózsaszínt partra vitték, pont a város közelében.";
			link.l1 = "Mintha bárkit is érdekelt volna az a roncs.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Ó, de a haditengerészet érdeklôdött! Gyakorlatias fickók. Megláttak egy angol zászló alatt közlekedô, de spanyol nevû hajót, és érdeklôdni kezdtek. Nic néhány évvel késôbb meghalt, de a hajója tovább ment, gazdát cserélt, mindig véres módon.";
			link.l1 = "Ez is csak egy újabb kísértethajó-történet, míg Gabe kapitánysága nagyon is valóságos. Szóval, azt hiszem, meglátogatom. Tudod, hogy hol lakik?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ha-ha! Persze, hic, tudom! Mindenki tudja! Az öreg Gabe az öreg szélmalom mellett lakik. Csak menjetek körbe a kocsma körül, és nézzetek fel... hic!";
			link.l1 = "Mikor van otthon? Úgy tûnik, elfoglalt ember.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "Így van, haver! Sok dolga van. Csak esténként van otthon, tíz órától. És minden nap pontban hatkor kel, egyedül. Vasfegyelem!";
			link.l1 = "Köszönöm szépen! Egyelôre elég volt ezekbôl a kalózmesékbôl.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Te tényleg... Rumba? Hallottam már rólad... de még sosem fordultál a sajátjaid ellen!";
				link.l1 = "Én sem. Nem a hazámmal van bajom. Hanem veled, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Te nem vagy kereskedô...";
				link.l1 = "Meglepetés, Gabe! Azt mondták, hogy óvatos vagy, sôt gyáva. A kapzsiság elhomályosította az ítélôképességedet, nem igaz? Egyetlen kereskedô sem keresné a beszállást úgy, ahogy én tettem.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "Velem? Mi a probléma? Megbeszélhetnénk ezt nálam, vagy akár nálad is. Mint a kapitányok, és... Mit keresel te itt?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "Hát persze. Szóval, ki vagy te? Nem, a pokolba veled. Ki az a...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Thomas, te vagy az?";
			link.l1 = "Ó, igen, Gabe. És azért jöttem, hogy megbüntesselek azért, amit aznap tettél velem.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Megbüntetni?! Vigyázz a szádra, Thomas! Ha valaki közülünk büntetést érdemel, az te vagy! Azt mondtad, hozol erôsítést! És mi vártunk, haldokolva a király lovasságának golyói és kardjai alatt!";
			link.l1 = "Átkozottul keményen futottam, hogy segélyt hozzak! De megelôzött egy másik kibaszott erô! Charles' véres támogatói voltak mindenütt! Leszorítottak, majdnem meghaltam! Még jó, hogy azt hitték, hogy meghaltam. De tudod mit láttam, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "Mi az, Tom? Hajlandó vagy bármilyen történetet kitalálni, hogy ez az ember higgyen neked?!";
			link.l1 = "Heh, ez az ember úgysem fog elárulni engem. Ô nem egy patkány, mint egyesek.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Nincs más választása! Megtámadni az angol haditengerészet egyik hajóját!";
			link.l1 = "Ó, már az elejétôl fogva volt választása. És úgy döntött, hogy segít nekem. Neked és Frankie-nek is volt választása. Úgy döntöttetek, hogy elmenekültök, hogy ne haljatok meg. Aztán visszajöttetek, és félholtan találtatok rám. És elmondtad az aljas hazugságaidat a bíróságon. Tudtad, hogy senki sem hallgatna rám, mert fejbe vertek és elvesztettem az emlékezetem!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Úgysem hallgatott volna rád senki. Te mindig is... egy kicsit... összecsapott voltál, Thomas.";
			link.l1 = "Ó, szóval nem titkolod, hogy mit tettél aznap. Van valamim a számodra, Gabe. Egy fekete folt. De mi értelme lenne odaadni neked, most, hogy a hajót elfoglalták, és ki fogjuk önteni a beledet, hej, hej, hej, hej, hej, hej, hej...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("BM_IronsClone5_function"); // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Nos, Gabe-et leváltották, hehehe. Ezt már régóta el akartam mondani. Kár, hogy már nem hallhatod, haver. Ó, várj csak! Talán mégis - a pokolból.";
			link.l1 = "Gyerünk, Tommy. Még ha nem is hallotta, látta és tudta, hogy ez pontosan a te terved és bosszúd. És nem tehetett ellene semmit.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, igazad van! Átkozottul igazad van! Köszönöm, hogy segítettél nekem ebben. Tudod, azt hittem, hogy te csak egy elkényeztetett lány vagy egy feltûnô ruhában, aki kapott egy hajót egy kis kirándulásra. De te egy átkozottul jó kapitány vagy! Lefogadom, hogy Jacket is leköröznéd.";
			}
			else
			{
				dialog.text = "Heh, igazad van! Átkozottul igazad van! Kösz, hogy segítettél nekem ebben. Tudod, szerintem te is olyan jó kapitány vagy, mint Jack. Vagy még jobb is!";
			}
			link.l1 = "Ó, most hízelegsz nekem. Köszönöm. Köszönöm. Azt hiszem.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Egyáltalán nem. Semmi hízelgés. Ahogy talán észrevetted, ritkán dicsérek meg bárkit is így. Szóval fogd be a pofád és örülj, hogy ilyen jó véleménnyel vagyok rólad!";
			link.l1 = "Nem mondanám, hogy tetszik, ahogyan ezt elôadod, bár örülök, hogy általában jó kapitánynak tartasz. De... a parancsnoki lánc, Tommy, a parancsnoki lánc.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Ó, ugyan már! Úgy érzem, hogy mindaz, amin keresztülmentünk, közelebb hozott minket egymáshoz, Ellie. Többek lehetnénk, mint kapitány és tiszt. Ismerd be - még ha csak magadnak is, te is érzed.";
				link.l1 = "Csak a legvadabb álmaidban, Tommy. És ez Helen, nem Ellie. De azt hiszem, most már hívhatsz Rumbának.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Ó, ugyan már, te unalmas! Nekem úgy tûnik, hogy mi már nem csak egy kapitány és a tisztje vagyunk, hanem a legigazibb barátok. Nem gondolod?!";
				link.l1 = "Heh. Talán. Jobb a barátodnak lenni, mint az ellenségednek. És mivel az etikett nyilvánvalóan nem a te mûfajod, azt hiszem, hozzá kell szoknom.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Van egy... ajándékom az ön számára, kapitány.";
			link.l1 = "Hûha, nézzenek oda! Egy fekete folt? Azt akarod, hogy engem is leváltsanak, mi, Tommy? Te is kapitány akarsz lenni? Ha-ha-ha-ha-ha-ha! Azt hittem, azt mondtad, hogy haverok vagyunk.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "Ez egy fekete pont, te faszfej. Tudod, kezdem azt hinni, hogy amint a koponyát és a csontokat hímeztem erre a sálra, szerencsét hozott nekem. Nem tudom megmagyarázni. Vedd el. És... ha akarod, bármikor kölcsönkérheted a megbízható kardomat és páncélomat... ami megmaradt belôle, ha-ha! Jól fog jönni! Messzire fogsz jutni. És tanúja akarok lenni. Nem akarom, hogy megöljön egy eltévedt golyó.";
			link.l1 = "Kösz, haver! Megteszek minden tôlem telhetôt. És te - nézd és csodáld, ha-ha-ha-ha!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Csodálom, persze, ha-ha-ha-ha. Igen, persze. Szóval, mihez kezdesz ezzel a hajóval? Egyrészt, már nem sok hasznát veszem. Másrészt, nincs több ilyen. Nem hiszem, hogy valaha is lesz még ilyen.";
			if (startHeroType == 4) 
			{
				link.l1 = "Még nem döntöttem el... Tudod, Tommy, úgy érzem, hogy valamiféle kapcsolatom van ezzel a hajóval. Nem tudom megmagyarázni. Szóval, elôbb vigyük ki innen ezt a büdös hullát. Ha nincs szivárgás a raktérben, akkor valószínûleg magamhoz veszem ezt a lányt.";
			}
			else
			{
				link.l1 = "Nem tudom, Tommy. Még nem döntöttem. Addig is, szabaduljunk meg Gabe testétôl. Arra az esetre, ha mégis megtartanánk a hajót.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Nos, elég jó munkát végzett azon az ôsi hajón, kapitány! És bár a saját kezemmel akartam végezni Gabe-bel, nem fogom feldühíteni a Teremtôt azzal, hogy lekicsinylem ezt a gyôzelmet.";
			link.l1 = "Az felesleges lenne, Tommy. Remélem, a lelked már megnyugodott.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Úgy érzem, hogy mindaz, amin keresztülmentünk, közelebb hozott minket egymáshoz, Ellie. Többek lehetünk, mint kapitány és tiszt. Ismerd be - még ha csak magadnak is, te is érzed.";
				link.l1 = "Csak a legvadabb álmaidban, Tommy. És ez Helen, nem Ellie. De azt hiszem, most már hívhatsz Rumbának, ha abbahagyod ezt a hízelgést.";
			}
			else
			{
				dialog.text = "Soha életemben nem voltam még ilyen boldog! Köszönöm, hogy átsegítettél ezen. Tudod, szerintem ugyanolyan jó vagy, mint Jack, mint kapitány. Vagy még jobb is!";
				link.l1 = "Ó, te hízelegsz nekem. Köszönöm az összehasonlítást is, azt hiszem.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Egyáltalán nem. Semmi hízelgés. Ahogy már talán észrevetted, én ritkán dicsérek meg bárkit is így. Úgyhogy fogd be és örülj, hogy ilyen jó véleménnyel vagyok rólad.";
				link.l1 = "Nem mondanám, hogy tetszik, ahogyan fogalmazol, de örülök, hogy általában jó kapitánynak tartasz. De... a parancsnoki láncolat, Tommy, a parancsnoki láncolat.";
			}
			else
			{
				dialog.text = "Egyáltalán nem. Semmi hízelgés. Ahogy már talán észrevetted, én ritkán dicsérek meg bárkit is így. Úgyhogy fogd be és örülj, hogy ilyen jó véleménnyel vagyok rólad.";
				link.l1 = "Nem mondanám, hogy tetszik, ahogyan fogalmazol, de örülök, hogy általában jó kapitánynak tartasz. De... a parancsnoki láncolat, Tommy, a parancsnoki láncolat.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Ó, ugyan már, te unalmas! Nekem úgy tûnik, hogy te és én már nem csak egy kapitány és a tisztje vagyunk, hanem a legigazibb barátok. Nem gondolod?!";
				link.l1 = "Heh. Talán. Jobb a barátodnak lenni, mint az ellenségednek. És mivel az etikett nyilvánvalóan nem a te mûfajod, azt hiszem, hozzá kell szoknom.";
			}
			else
			{
				dialog.text = "Ó, ugyan már, te unalmas! Nekem úgy tûnik, hogy te és én már nem csak egy kapitány és a tisztje vagyunk, hanem a legigazibb barátok. Nem gondolod?!";
				link.l1 = "Heh. Talán. Jobb a barátodnak lenni, mint az ellenségednek. És mivel az etikett nyilvánvalóan nem a te mûfajod, azt hiszem, hozzá kell szoknom.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Van egy... ajándékom az ön számára, kapitány.";
			}
			else
			{
				dialog.text = "Van egy... ajándékom az ön számára, kapitány.";
			}
			link.l1 = "Hûha, nézzenek oda! Egy fekete folt? Azt akarod, hogy engem is leváltsanak, mi, Tommy? Te is kapitány akarsz lenni? Ha-ha-ha-ha-ha-ha! Azt hittem, azt mondtad, hogy haverok vagyunk.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "Ez egy fekete pont, te faszfej. Tudod, kezdem azt hinni, hogy amint a koponyát és a csontokat hímeztem erre a sálra, szerencsét hozott nekem. Nem tudom megmagyarázni. Vedd el. És... ha akarod, bármikor kölcsönkérheted a megbízható kardomat és páncélomat... ami megmaradt belôle, ha-ha! Jól fog jönni! Messzire fogsz jutni. És tanúja akarok lenni. Nem akarom, hogy megöljön egy eltévedt golyó.";
			link.l1 = "Kösz, haver! Megteszek minden tôlem telhetôt. És te - nézd és csodáld, ha-ha-ha-ha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			Notification_Reputation(true, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "Kinek kell hinnie ilyesmiben... Sajnálom, kisasszony. " + TimeGreeting() + ". Miben segíthetek? Nagyon aggódónak tûnik.";
			}
			else
			{
				dialog.text = "Micsoda? - Nem tudom. Ki jön erre ilyen késôn? Eléggé aggódónak tûnik, uram. Mit tehetek önért?";
			}
			link.l1 = "Elnézést kérek, hogy megzavartam a pihenését, Callow kapitány. A nevem " + GetFullName(pchar) + ", és az egyik régi harcostársa nevében jöttem.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Melyik bajtársam? Sokan voltak, mind a régi, mind az új világban.";
			link.l1 = "Elôször csak az volt a szándékom, hogy hagyjak valamit az egyik ládájában. Vagy talán az asztalon, hogy hamarabb észrevegye. Egy emberrôl van szó a múltjából. Tessék, nézze meg és olvassa el maga.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "Egy fekete folt? Nem emlékszem, hogy kalózok lettek volna a bajtársaim között. Vagy a fiúk közül néhányan beleestek ebbe az életbe? Fekete selyem? Tényleg... Ó, Thomas. Meglep, hogy egy olyan ember, mint te, ilyen gazemberrel üzletel.";
			link.l1 = "Elnézést kérek, de nem a te dolgod, hogy gazembernek nevezd. Elmenekültél a csatatérrôl, és rágalmaztad Tomot. Talán késôbb megbántad, és példás tiszt lettél itt a szigetvilágban, de ez nem változtat a múlton.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Ezt ô mondta neked? Nem meglepô - mindig is tudta, hogyan találja meg a megfelelô embert, hogy meséljen. Thomasnak ezüst nyelve volt. Nem ismeri ôt, nem ismeri a valódi történetet, nem tudja, mibe keveredik. Elmondhatom - mivel most úgysem fogok aludni.";
			link.l1 = "Sosem árt hallgatni. Folytassa, Callow kapitány.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Szóval, Thomas azt állítja, hogy elmenekültem, majd rágalmaztam ôt? Nos, tudnod kell, hogy az ellenkezôje történt! Amikor a király lovassága közeledett, Tom azt mondta, hogy erôsítésért megy. Így hát nem hátráltunk meg - vártunk. Az egész századunkat megölték! Ha nem vártuk volna meg az erôsítést, amit ígért, visszavonulhattunk volna és túlélhettük volna! Végül csak én, Frankie és az átkozott Thomas maradtunk életben.";
			link.l1 = "Szóval azt akarod mondani...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "Én azt mondom, hogy a mi fiaink vére ugyanúgy Tom kezén szárad, mint a királypártiakén'. Szerencséje, hogy büntetômunkára ítélték és nem akasztásra! És most van képe haragudni és párbajra hívni engem! Nem méltó rá!";
			link.l1 = "Szóval nem mész? Tisztában vagy vele, hogy ez mit jelent. A becsület törvényei mindenki számára meg vannak írva.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Természetesen én. És ezért megyek én is. Be kell fejeznünk azt, amit a republikánus udvarunk nem tudott befejezni Tom múltbeli katonai kitüntetései miatt. És maga... maga rendes embernek tûnik. Azt tanácsolnám, hogy bölcsebben válassza meg az ismerôseit. Ne keveredjen össze Tommal és a fajtájával.";
			link.l1 = "De Thomas most már a beosztottam, tiszt a hajómon. "+GetSexPhrase("Rajta tartom a szemem, és nem hagyom, hogy még jobban megszégyenítse magát, ha túléli a veled való találkozást.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "És mit tenne a helyemben, Callow kapitány?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, ha Tom meg tudott gyôzni téged a meséjérôl, akkor nem lesz gondja, hogy újra megtegye.";
			link.l1 = ""+GetSexPhrase("De a becsület törvényei szerint nem árulhatom el ôt. Én","vagyok")+" felelôs vagyok az embereimért... Nem leszek olyan, mint ô. És mostantól óvatosabb és kritikusabb leszek vele szemben, ha túléli.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "Nehéz döntés. De nem fogom megpróbálni, hogy megváltoztassam a véleményét. Nos, viszlát, "+GetSexPhrase("uram","miss")+" - Még fel kell készülnöm a találkozóra Tommal.";
			link.l1 = "Viszlát, Callow kapitány.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Legyen igazság! Segítsetek elpusztítani Thomast, "+pchar.lastname+". Ritka gazember és gyáva, de remek céllövô - nem lesz könnyû. De együtt...";
			link.l1 = "Hmm, segíteni legyôzni Thomast? Sok becsület van egy ilyen párbajban? Elintézhetitek magatok, én pedig távol maradok az útból.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Ismerve ôt, kétlem, hogy tisztességes párbajt kapnék. Azzal, hogy semleges maradsz, csak elnézed az igazságtalanságot. Igazam van?";
			link.l1 = "Úgy tûnik, jobban ismered Tomot, mint én, és hogy milyen is ô valójában. Igazad van - már csapdát állít a Portland-öbölben, és számít a segítségemre - ahogy most te is.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Akkor ez nem párbaj, hanem verekedés. De nem javaslom, hogy mi magunk öljük meg Thomast. Letartóztatjuk! Hozok katonákat, és befejezzük azt, amit az Óvilágban nem tudtunk. Ha megint megpróbálják felmenteni, írok az ezredesnek, vagy akár ide is hozom a tárgyalásra. Ha Thomas nem teszi le a fegyvert, az az ô hibája.";
			link.l1 = "Ez sokkal jobban hangzik.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Örömmel hallom, "+pchar.lastname+"! Tisztában vagyok vele, hogy nem biztos, hogy könnyû neked ilyen döntést hozni, de biztosíthatlak, hogy jól döntöttél. És hogy ezt biztosítsam, segítek neked még valamiben.";
			link.l1 = "Mi az, Callow kapitány?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Tessék, fogd ezt. Nem ajándék, hanem kölcsön - Thomas, mint mondtam, nagyon jó harcos, és jobb, ha rendes fegyverrel szállunk szembe vele, nem pedig egy rozsdás vasdarabbal. Maga Doyley ezredes adta nekem ezt a szépséget, de egy igazi harchoz mindig egy széles kardot választanék.";
			link.l1 = "Valóban, ez egy pompás penge. Köszönöm, uram.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Ne köszönd meg nekem - kölcsönadom neked, nem ajándékozom, emlékszel? Most menj az öbölbe, és játssz a mi drága Tomunkkal, amíg én erôsítést gyûjtök. Ott találkozunk.";
			link.l1 = "Ott találkozunk, Callow kapitány.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			Notification_Reputation(false, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "Ki maga, kisasszony? Biztos rossz címre jött. Nem rendeltem éjszakai szolgáltatást.";
				link.l1 = "Helen MacArthur. És tartsa kordában a vágyait, Mr. Callow. Tisztességes lány vagyok. A mi éghajlatunk miatt még éjszaka is forrónak érzem magam. Nem szégyellte ezt mondani egy idegen lánynak? Azt mondták, hogy ön példamutató tiszt.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Ki maga, és mit akar? Nem tetszik a vigyora, uram.";
				link.l1 = "" + GetFullName(pchar) + ". És ön nem túl vendégszeretô, Mr. Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Ön ilyenkor másképp köszönti az idegeneket?";
			link.l1 = "Azt mondták, hogy máskor nincs itthon.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Persze, hogy nem vagyok - szolgálatot teljesítek, kötelességtudó vagyok, és becsületes munkát végzek, olyan szavakat, amelyek a megjelenésébôl ítélve ismeretlennek tûnnek az ön számára.";
			link.l1 = "Micsoda önbizalom! De hát másképp nem gyôzte volna meg Doyley ezredest és a többieket az ôszinteségérôl. Nekem nincs szükségem magára, Gabe, de egy régi ismerôsének igen. Tessék, tessék.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Meggyôzték? Gabe? Azt mondom! Egy fekete folt? Szóval kalóz vagy? Várj egy percet... fekete selyem... lehet, hogy ez... Ó, értem. Thomas, te rohadt szemétláda, még mindig haragszol rám és Frankre, amiért feljelentettünk, ha ha ha ha ha!";
			link.l1 = "Én mondom! Tom tiszt a hajómon, és tiszteletet érdemel. Ô a szigetvilág egyik legjobb mesterlövésze.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Nem mondtam, hogy rossz lövész. De úgy látom, nem ismeri túl jól Thomast. Ô az, aki elárult minket. De úgy látom, nincs értelme vitatkozni veled - nyilvánvalóan tökéletesen illenek egymáshoz.";
			link.l1 = "Nem érdekel. Tartsd meg a meséidet Doyley-nak és a többi naiv együgyûnek. Ha olyan bátor és becsületes vagy, mint mondják, akkor elfogadod a kihívást, és most jössz. Szóval, elfogadod?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Igen, igen. Most pedig kifelé a házamból, mielôtt hívom az ôrséget.";
			link.l1 = "Örömömre szolgál, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Miért vagy ilyen ideges? Megijedtél, vagy mi?";
				link.l1 = "Bárki ideges lenne, ha látna egy muskétás embert rohanni feléje - nem ismertem fel elôször. Mit keresel itt, Tommy?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Hogy ment? Hé, hé, miért nézel így rám? Megijesztettél, hehehe.";
				link.l1 = "Ki ijesztget kit! Ki szalad ki így?! Megbeszéltük, hogy a vendégekkel az öbölben találkozunk!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, nos, talán. Belefáradtam a várakozásba - a kedves vendégeinkre és rád. És úgy döntöttem, hogy ez a hely alkalmasabb egy jó kis rajtaütésre. Elvégre vadász vagyok, nem párbajozó.";
			link.l1 = "Értem, értem.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Nem párbajozó, nem párbajozó. Szóval, Gabe házában hagytad az ajándékomat? Elég sokáig tartott. Sokkal gyorsabb lennék, ha be tudnék jutni a városba. Mitôl szalad a szeme, kapitány? Mi a baj?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Megbízható) Ideges vagyok. Gabe gyáva, de nem hülye. Mi van, ha egy egész szakasznyi katona jön ide helyette? Vagy megközelítik az öblöt, és elsüllyesztik a hajónkat?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Megbízható", "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe látott engem. Futnom kellett.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("A képességek ellenôrzése sikertelen.", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, értem én - én sem vagyok benne teljesen biztos, hogy mûködni fog. Ez az elsô alkalom, hogy ilyen nagy dolog történik veled, mi? Semmi baj, megesik az ilyesmi. Már mindent kidolgoztam. Ha a katonák Gabe nélkül jönnek, mi csak elmegyünk. Ha Gabe-bel jönnek, golyót eresztek a szeme közé, és megint csak elmegyünk. Ha pedig egy hajó érkezik az öbölbe, elszaladunk Maroon Townba - oda nem merészkednek, és aztán eldöntjük, mi legyen a következô lépés.";
			link.l1 = "Látom, tényleg mindenre gondoltál, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Persze, hogy gondoltam. Most pedig várjuk meg a vendégünket...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ha ha, te olyan jó tolvaj vagy, mint én királypárti. De miért nem nézel a szemembe... Kapitány? Gabe-bel beszéltél, ugye?";
			link.l1 = "Nem, mirôl beszélsz? Miért beszélnék vele egyáltalán?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Mert ti mind nagydumások vagytok. Mindig csak beszéltek. Szóval, mit mondott neked a mi drága Gabe-ünk?";
			link.l1 = "Számít ez, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Ôszintén szólva, nem. De igen, ha nem szúrsz hátba. De úgy tûnik, már megtetted. Rábeszélt, hogy állj az ô oldalára, ugye?";
			link.l1 = "Nem. Nem igazán. Tedd le a fegyvert, Tommy. Ígérem, hogy semmi helyrehozhatatlan nem fog történni. Talán dolgozhatnál a kôbányában. Megkérem Gabe-et, hogy legyen kegyes. Még Doyley ezredest is megkérem, ha kell.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Micsoda jó szamaritánus vagy. Kegyelmet mutatsz, hogy felköhöghessem a tüdômet a kôbányában töltött évek után? Nem megyek vissza a börtönhajókra. Soha többé. És maga... Tudhattam volna, hogy csak egy újabb patkány vagy. Van valami abban, ahogy kinézel. Elôször veled foglalkozom, így Gabe-nek késôbb könnyebb lesz.";
			link.l1 = "Nem hagysz nekünk más választást!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Nos, látom, már megtette, "+GetSexPhrase("uram","miss")+". Én pedig éppen egy osztagot gyûjtöttem össze, azt gondoltam, hogy a számbeli fölény miatt Tom kétszer is meggondolja magát, és leteszi a fegyvert.";
			link.l1 = "És maga nem sietett, Callow kapitány.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Mondtam, hogy embereket gyûjtöttem. A helyôrségünk legjobbjait. Tom végül is veterán katona. De kinek mondom ezt el? Szép munka, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". "+GetSexPhrase("Büszke vagyok rád, fiatalember","El kell ismernem, hogy egyformán rendelkezel szépséggel, intelligenciával és ügyességgel, ifjú hölgy")+". Ahogy már az elsô találkozásunkkor is mondtam, jól döntöttél. Most igazságot szolgáltattál.";
			link.l1 = "Ez nagyon jól sikerült neked. Büszke vagy?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Nos, én nem vagyok veterán katona, de tudok harcolni, ahogy talán most észrevetted. De köszönöm, uram. Az igazság nem üres szó számomra.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "És ez dicséretes, "+GetSexPhrase("fiatalember","fiatal kisasszony")+". Azonban még egy dolog van hátra, hogy befejezzük ezt a szép napot.";
			link.l1 = "Hmm, és mi az? Tom már legyôzték, végül is.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Van nálad valami, ami az enyém. Add vissza a gyönyörû olasz pengémet, kérlek. Végül is ez nem csak egy fogpiszkáló, hanem egy emléktárgy - egy ajándék magától Doyley ezredestôl.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "A helyzet a következô, Callow kapitány... a pengéje eltûnt. Elvesztettem. Sajnálom.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Á, hát persze. Kérem, kérem, kérem. Nem állt szándékomban ellopni. Bár nem hazudok - szeretném megtartani. De hát itt van, Callow kapitány.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "Jobb ajánlatom van önnek, kapitány.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "De maga csak fogpiszkálónak nevezte. Különben is, azt mondta, hogy nem is szereti a pengéket. Én viszont megérdemlem a jutalmat.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Bárki meg akarta volna tartani ezt a szépséget! Köszönöm, hogy visszaadta nekem. Sokan makacskodtak volna a helyedben.";
			link.l1 = "Ez a tiéd. Gondolom, itt végeztünk?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "Nem érdekel. Csak adja vissza a rapírját, és akkor jóban leszünk, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+".";
			link.l1 = "Gondolom azért kedveli ezt a pengét, mert szereti a történelmi fegyvereket, igazam van? Nekem is van egy ugyanilyenem, és ez az, amit a fiókban tartás helyett szívesen hordana magánál.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Tényleg így van? Nos, nem ígérhetem, hogy megegyezünk, de hallgatlak. Engem valóban érdekelnek a történelmi fegyverek. De ezt a pengét az ezredestôl kaptam ajándékba. Ezért olyan értékes számomra.";
			link.l1 = "Említette, hogy szereti a kardokat. Tessék. A mi drága Tommy-nké volt. Képzelje el, min ment keresztül ez a fegyver az évek során. És hogy min megy keresztül veled együtt.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Nagyon meggyôzô vagy, fiatalember! Thomas kardját forgatni... milyen ironikus. Á, nos, fogd a pengét. Nem könnyelmûen válok meg tôle, ne feledd.";
			link.l1 = "Örülök, hogy meg tudtunk egyezni. Azt hiszem, ez egy búcsú, Callow kapitány?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "MICSODA?! Hogy tehetted... Hogy veszíthettél el egy egész kibaszott pengét?! Maga egy idióta!";
			link.l1 = "Nyugodjon meg! Ez csak egy pengéje. Úgysem használnád. Tom halott - nem ez az egyetlen dolog, ami most számít?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Csak egy pengéje?! Az az én kincsem volt! Egy ajándék magától Doyley ezredestôl! Nem érdekel, ha nem használom!";
			link.l1 = "Akkor nem kellett volna nekem adnod, nem igaz?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "Most már jobb lenne, ha befogná a száját, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". Békésen elválhattak volna útjaink. De most... most szeretném megleckéztetni, "+GetSexPhrase("fiatalember","fiatal kisasszony")+".";
			link.l1 = "A temetôk tele vannak ilyen tanárokkal, mint te.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Persze, hogy van. De nem veheted el egy tiszt személyes fegyverét, csak mert kölcsönadtad neki a kezed, ugye?";
			link.l1 = "Egyetértek, de úgysem használod. Csak egy szögön fog lógni a szobádban. Míg nálam méltó használatra talál. Doyley ezredes nem fogja megnézni, hogy elvesztette-e, ugye?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Ez nem vita tárgya, fiatalember. Már az elején megmondtam, hogy ez nem ajándék. Add ide a pengét. Add ide a pengét!";
			link.l1 = ""+GetSexPhrase("Nem vagyok egy a játékkatonáid közül","Nem vagyok egy a kikötôi kurváid közül")+", hogy parancsokat fogadjak el tôled. Én is hajóskapitány vagyok, akárcsak te. A pengém velem marad, akár tetszik, akár nem.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Úgy tûnik, Thomas elég nagy hatással volt rád. Akkor halj meg érte, ha annyira akarod.";
			link.l1 = "Pontosan ezt gondoltam!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Tessék, fogd ezt. Egyáltalán nincs rá szükségem. Ez lesz az emléked a mai napról. Mostantól próbálj meg egy kicsit kevésbé hiszékeny lenni. És ne hagyja, hogy az olyan gazemberek, mint Thomas, belekeverjék a piszkos ügyeikbe.";
			link.l1 = "Heh, maga most fekete foltot vet rám, Callow kapitány?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Nos, egyikünk sem kalóz, ugye, "+pchar.name+"? Legyen ez egy emlékeztetô. Vigyázz magadra, a szigetvilágnak szüksége van az olyan emberekre, mint te. "+GetSexPhrase("Talán javasolnám, hogy csatlakozzon a haditengerészethez, és írjon ajánlást Doyley ezredesnek...","")+"";
			link.l1 = "Sajnálom, hogy nem fogadhatom el az ajánlatát, kapitány.";
			if (startHeroType == 3)
			{
				link.l1 = "Hm. Gondolkodom rajta. Egy igazán jót.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Viszontlátásra, uram.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Ahogy akarod. Nos, viszlát, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". Megérdemled, hogy vigyed, ami a Vaskalaposokból megmaradt. Viszontlátásra.";
			link.l1 = "Viszontlátásra, uram.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Nem tetszik a hangnemed, "+GetSexPhrase("mister","miss")+". Mire akarsz kilyukadni?";
			link.l1 = "Szándékosan húztad az idôt, összegyûjtötted a 'legjobb embereidet'. Minek? Hogy elfogjanak egy embert? El kellett volna fognod néhány, a városban járôrözô katonát, és azonnal a segítségemre sietned!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Hogy ágyútölteléket hozol?! Tom nem csak egy városi ôr volt, mint ôk. Teljesen más kiképzést és tapasztalatot kapott - ô egy rohadt vasgyalogos, akárcsak én! Hogyhogy nem veszed ezt észre?";
			link.l1 = "Ó, épp ellenkezôleg, tisztában vagyok vele. Ezért voltunk itt te és én - hogy keresztezzük a pengéket Tommal, és lehetôvé tegyük a fiúknak, hogy élve elfogják. Mellesleg, te is Vasbôrû vagy. Ugyanaz a társaság. Annyira féltél személyesen megküzdeni vele?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Hogy merészelsz gyávasággal vádolni, fiatal "+GetSexPhrase("ember","kisasszony")+"! Kérdezzen meg bárkit, és részletesen el fogja mondani, milyen hôstetteket vittem véghez a városért.";
			link.l1 = "Még nem végeztem. Kezdek azon tûnôdni, hogy ezeket ‘feats' a saját kezûleg csináltad-e. Azt akartad, hogy Tom és én megöljük egymást, hogy te arathasd le a dicsôséget. Már csináltál ilyet korábban is, nem igaz?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "Elegem van a vádaskodásaiból, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+". Konfliktust akar? Megkapja. Most rögtön.";
			link.l1 = "Az igazság fáj, nem igaz, Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe! Olyan rég volt már, olyan sok sivár tél közepén! És nézz magadra - még mindig ugyanolyan önelégült vagy, a fenébe is!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomas! Örülnöm kellene, mert ma végre a saját kezemmel fogom befejezni azt, amit az igazságszolgáltatási rendszerünk évekig nem tudott megtenni. És mivel jó hangulatban vagyok, megengedem, hogy letegye a fegyvert és kövessen minket. Még az is lehet, hogy visszaküldünk büntetômunkára. Ebben az esetben személyesen viszlek oda.";
			link.l1 = "Heh, kényszeríts! Azt hiszed, hogy egy pár fickó melletted majd megállít engem!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Ki mondta, hogy csak ôk vannak velem? Arról a személyrôl beszélek, aki most is melletted áll.";
			link.l1 = "Micsoda?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas, Thomas... mint mindig, most is egyedül vagy ezen a világon. Majdnem sajnállak!";
			link.l1 = "Rohadt patkányok! Rohadékok!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "Ez meg mit jelentsen?! Hogy értette ezt?!";
			link.l1 = "Tommy, figyelj...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "Pontosan ezt csinálom! Mondd, hogy hazudik!";
			link.l1 = "Sajnos, igaza van. Tegyétek le a fegyvert. És senkinek sem kell ma meghalnia. Majd én magam szólok egy jó szót az érdekedben, hogy ne akasszanak fel. Egyszer még a becsületes életbe is visszatérhetsz.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "Ezt nem neked kell eldöntened! És fôleg nem neked! Kinek kellenek ellenségek egy ilyen parancsnokkal! Még egy kibaszott patkány.";
			link.l1 = "Gyerünk, Tommy. Az olyanoknak, mint te, nincs tiszta menekülés.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " Egy hely a legénységedben, a hajódon már kezdetnek jó lenne, ha hajlandó lennél kiállni az embereidért! De ez már nem számít. Átkozottak vagytok, mindannyian! Kibelezem a gyáva beleidet, te kis patkány. És téged, Gabe, megpróbállak magammal vinni...";
			link.l1 = "Várj, Tommy, ne!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Gratulálok, "+GetSexPhrase("fiatalember","fiatal kisasszony")+"! Le vagyok nyûgözve, hogy sikerült elérned, hogy Tamás úgy érezze, minden a terve szerint halad - volt érzéke az áruláshoz.";
			link.l1 = "Köszönöm, természetesen, Callow kapitány.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Valami zavarja önt, "+GetSexPhrase("Mr.","miss")+" "+pchar.lastname+"?";
			link.l1 = "Tom... nem csak azért volt dühös, mert a te oldaladon álltam. Valódi kétségbeesés és értetlenség volt a hangjában, mintha...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...mintha ô lenne a sértett fél. Ez várható volt. Ne feledje, Charles, egy szörnyeteg is érez fájdalmat. De ettôl még szörnyeteg marad. Sok bûnözô gyakran ôszintén meg van gyôzôdve az igazáról és az ártatlanságáról.";
			link.l1 = "Megpróbálom ezt észben tartani. Azt hiszem, itt végeztünk, nem gondolja, kapitány?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "Általában igen, de még egy dolog hátravan, hogy befejezzük ezt a szép napot.";
			link.l1 = "Ó? Mi az?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Elég sokáig tartott. Úgyhogy gondoltam, felderítek egy kicsit. Különben is, szerintem jobb lenne itt rajtaütni rajtuk, mint a parton párbajozni. Remélem, sikerült megtalálnod Gabe házát, és mindent szem elôtt hagyni?";
			link.l1 = "Hát persze, minek nézel te engem, egy idiótának? Valójában a kapitányod vagyok, Tommy. Mit jelentene az, ha egy idiótát szolgálna?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ha-ha-ha-ha-ha, el sem hinnéd, milyen gyakran kellett ilyen szarságokkal foglalkoznom a szolgálatban! De a mi esetünkben szerencsére nem ez a helyzet. Rendben, akkor. Társaságot várunk. Készen álltok?";
			link.l1 = "Nos, hacsak nem bukkan fel itt az egész flotta vagy Port Royal helyôrsége, én készen állok.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas? Mégiscsak te vagy az...";
			link.l1 = "Persze, hogy tényleg én vagyok, vagy valaki másra számítottál, Gabe? Sápadtnak tûnsz, mintha szellemet láttál volna. És kövérebb is vagy, mint a régi Angliában voltál.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Most már végre meggyôzôdésem, hogy tényleg te vagy az. Durva, mint mindig. De semmi baj, hamarosan végleg befogom a mocskos szádat, te szemétláda.";
			link.l1 = "Ha-ha-ha-ha, most már beszélgetünk! Tudod, valójában csalódtam benned, Gabe. Megint! Nyilvánvalóan több embert kellett volna hoznod magaddal, még ahhoz is, hogy egyedül elbánj velem. És itt vagyunk mi ketten! Vagy csak ennyit tudtak megspórolni neked, te gyáva?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Elég volt! Nem látom értelmét, hogy tovább beszélgessünk.";
			link.l1 = "Ebben egyetértek veled! " + pchar.name + "! A csatára, kapitány!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Heh, tessék! Nyugodj békében, te szemétláda!";
			link.l1 = "Nos, elégedett vagy, Tommy? Tudod, sok ember csak rosszabb lesz, miután bosszút állt.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ha, ezt olvastad valahol? Soha nem értettem az ilyen puhányokat. Bah! Elégedett vagyok? Annyira boldog vagyok, hogy mindjárt bepisilek! Azok a szemetek voltak a legnagyobb szerencsétlenségem gyökerei!";
			link.l1 = "Örülök neked. Nincs senki más, akin bosszút állhatnál? Még több papírpatronos viccet várhatok tôled?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Nyugodj meg, Gabe volt az utolsó. És ami a vicceket illeti - ne aggódj, nem lesz több, legalábbis ami téged illet.";
			link.l1 = "Akkor menjünk vissza a hajóra?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Úgyis visszamennénk rá, akár van még valaki, akin bosszút állhatok, akár nincs. Várj egy percet...";
			link.l1 = "Ó, szóval még nincs vége...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "De igen, de igen. Van valami, amit el akarok mondani neked. Valamit, amit nagyon kevés embernek mondok. És nem fogom még egyszer elmondani. Ha kinevetsz, nagyon mérges leszek rád.";
			link.l1 = "Megígérem, hogy nem nevetek. Egyébként is, a vicceidet inkább feszültnek, mint viccesnek találom.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Jól van. Szóval... Nagyon hálás vagyok, hogy úgy döntöttél, segítesz nekem, ahelyett, hogy azt tetted volna, amit Jack. Igazi barát vagy, kapitány. Köszönöm, kapitány. És... ha akarod, kölcsönkérheted a megbízható kardomat és a páncélomat... Ami megmaradt belôle, ha-ha!";
			link.l1 = "Nos, köszönöm, hogy ezt mondtad. Nem minden nap hall az ember ilyesmit a tisztjeitôl. Gyerünk, pajtás.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Aaaaye-aye, kapitány?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Szóval, Rumba, kinek a csontjain táncoljunk ma este?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Igen, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Csupa fül vagyok, kapitány.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, szeretnék kérdezni tôled valami nagyon komolyat. Van egy... a Vörösbôrûek kôbálványa. És segítségre lesz szükségem. Csak a legközelebbi barátaimtól kérhetem, mint például tôled. Újoncok vagy olyanok, akikben még nem bízom túlságosan, nem fognak.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, ne számold a sirályokat. Összeszámoltad az összes rakományt? Adj egy teljes jelentést az elôrejelzéssel együtt.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, a mai naptól kezdve bizonyos árukat kell vásárolnod a kikötôkben.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, tudnál jelenteni mindent a hajón?";
					Link.l12 = "Tommy, kezdek nagyon fáradt lenni. Fel tudnál tölteni bizonyos árukat az egyes kikötôkben?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Készíts nekem egy jelentést a hajó állapotáról és mindenrôl, ami rajta van, Tommy.";
					Link.l12 = "Fel tudnál tölteni bizonyos árucikkeket a kikötôinkben?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Számolj össze mindent, ami a hajón van, és készíts jelentést a hajó általános állapotáról.";
					Link.l12 = "Szeretném, ha ezeket az árukat megvennéd a kikötések alkalmával.";
				}
			}
			//////
			Link.l1 = "Hallgass figyelmesen a parancsomra!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Valaki biztosan van. De egyelôre hallgassatok a parancsomra.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Hallgassa meg a parancsomat... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Ez jó, mert van egy új parancsom számodra, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Figyelj a parancsomra, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Semmi, Tommy. Pihenj.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Meglátjuk, hogy megy, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Nem, Tom, semmi.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Nem, semmit.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Semmi, minden rendben.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Még el sem kezdtem a leltárt. Hálás lehetsz, hogy egyáltalán számolom a nyereséget és a veszteséget, nemhogy alkudozom ezekkel a kapzsi kereskedôkkel. A leltározás nem az én dolgom, a seregben sosem kellett, és most sem fogok belekezdeni.";
			Link.l1 = "Ez nem a hadsereg, Tommy. De rendben, értem, nem kényszerítelek.";
			if (startHeroType == 4)
			{
				dialog.Text = "Nem vagyok írnok, Ellie. Ismertem egyszer egy fickót, Daniel Crimson-t, aki mindig azt állította, hogy írnok, de alig látta a csatamezôt. Mégis, az az ember egy vadállat volt a harcban. De ez nem én vagyok, és nem fogok hazudni. A leltározás egyszerûen nem az én világom. Már a te kedvedért is megcsinálom a számláinkat. Ne erôltesd.";
				Link.l1 = "Rendben, Tommy, nem fogom.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Nézd, én nem vagyok írnok. Soha senki nem követelte ezt meg a magamfajta egyszerû katonáktól, még a hadseregben sem. Ne változtassuk meg ezt a szabályt.";
				Link.l1 = "Oké, ne változtassuk meg.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Az egyetlen dolog, amit meg tudok számolni, az az, hogy hány ellenségünket lôttem le, ha-ha-ha-ha. És még akkor is el fogom veszíteni a számolást. Egyszerû katona vagyok, tudod. Ki a fene tud a hajóról - életem nagy részében szárazföldi voltam.";
				Link.l1 = "Úgy tûnik, nekem kell megcsinálnom.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Minek nézel te engem, valami háztáji szállásmesternek? Mi csak megvetettük azokat a puhány gyávákat odahaza. Lehet, hogy nem vagyok nemes, de a büszkeségem megmaradt.";
			link.l1 = "Rendben, rendben, ha nem akarod, akkor nem fogod.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Figyelj, én egy egyszerû, becsületes katona voltam, nem ellátó tiszt, kislányom. Nem sokat tudok róla, és nem is akarok elkezdeni tanulni. Ez olyan, mintha azt kérném, hogy rakj össze és szedj szét idôben egy muskétát.";
				Link.l1 = "Nos, a hajó összes álló- és futókötélzetét kívülrôl tudnám megnevezni. De ahogy akarod, Tom. Az ügy lezárva.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Nem, nem tudnám. Talán elfelejtette, vagy egyáltalán nem tudja, úgyhogy elmagyarázom. Számodra ez rutinfeladat lenne, de a mi hadseregünkben nem bánunk túl jól az utánpótlással és a hátvédekkel. Kérem, engem ne számítson közéjük.";
				Link.l1 = "Ha-ha, jó, jó.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Nézze, természetesen tisztelem magát, de nem fogok átlépni magamon és olyasmit tenni, amit nem tudok és nem bírok elviselni. Alig tanultam meg számolni akkoriban, és te azt akarod, hogy igazi szállító legyek. Egyébként nem szerettük ôket - spóroltak a lôszerrel, a vízzel, az élelemmel és annak frissességével.";
				Link.l1 = "Hm, oké, felejtsük el.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Ó, egy rendelés, mi? Szereted a kiképzést, meg a többi katonai dolgot, ugye? Inkább csak mondd meg, mit kell tennem.","Olyan vagy, mint egy ôrmester vagy ilyesmi. Nem illik hozzád - túl szép vagy ahhoz. Egy napot sem élnél túl a seregben. De hallgatlak.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Úgy tûnik, te tényleg nagy rajongója vagy az egyenruháknak, a gyakorlatoknak, meg minden ilyesminek. De oké, folytasd.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Melyik?";
			}
			
            Link.l1 = ""+GetSexPhrase("Ne menjetek sehova, és ne csináljatok semmit - csak figyeljetek, értitek? Ismerlek.","Maradj ott, ahol vagy, érted?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Csak állj itt, ne menj sehova, és ne nyúlj semmihez.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Maradj itt, és ne engedj el senkit.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Kövessetek engem, és semmi se vonja el a figyelmeteket - beleértve a kóbor feleségeket vagy a hirtelen felbukkanó régi háborús bajtársakat is.","Maradjatok közel, rendben? Szeretném, ha fedeznének.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Kövessetek. Látom, hogy elmerültél a gondolataidban.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Kövess, különben valamiért megálltál.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ezúttal valami másra kell lônöd.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Azt akarom, hogy más lôszert használj a következô harcban.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "A következô csatában más lôszert fogsz használni.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Változtasd meg a muskétád lôszertípusát.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Változtasd meg a harcban használt elsôdleges fegyveredet.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Szeretném, ha bizonyos távolságot tartanál magad és az ellenségeid között.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Szeretném, ha bizonyos távolságot tartanál az ellenségtôl.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Tarts bizonyos távolságot magad és az ellenség között, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Milyen lövedékek? Remélem, gondosan megmunkáltad mindegyiket, mert ki tudja, hol fognak landolni, hehe.","Bármit lövök neked. Bármit, de vaktöltényt soha, hehe. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Érzem, hogy valami érdekes készülôdik! Oké, milyen fajta?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Megint beugrottam... Oké, milyen fajta?";
			}
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

		case "SetMusketBullets":
			Dialog.Text = "Válaszd kia lôszertípust:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "A harc elején használni fogod:";
			Link.l1 = "Penge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskéta";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Még akkor is, ha ott megverik, hehe? Értem, majd csak nézem.","Próbálsz ôrré változtatni? Mi van, ha megverik vagy ilyesmi?")+"";
            Link.l1 = ""+GetSexPhrase("Hé, vigyázz! Majd kitalálunk valamit, ha arra kerül a sor.","Hát, ugye nem csak nézni fogod? Ha úgy gondolod, hogy a kapitányod olyan csodálatos, ahogy mondod, akkor teszel is érte valamit.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Még a fejét is megütöd? Oké, oké, ne nézz így rám, értem én.";
				Link.l1 = "Remélem is.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Ne félj, senki nem fog átmenni.";
				Link.l1 = "Persze csak ha nem hibázol el senkit. De jó.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Nagyon vicces. De értem, mire gondolsz.","Ó, ne aggódj, a hátad mindig az én figyelô szemem alatt van, hehe.")+"";
            Link.l1 = ""+GetSexPhrase("Jól van.","Istenem, de kibírhatatlan vagy, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Nos, próbálok emlékezni valami nagyon fontosra. Aztán rájövök, hogy nem is tudom, mi az, hiszen akkoriban elvesztettem az emlékezetemet, így nem lesz belôle semmi. Oké, menjünk.";
				Link.l1 = "Szellemes, azt kell mondjam.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Nos, azért állok itt, mert maga utasított rá korábban. Jövök, jövök.";
				Link.l1 = "Hm-m, oké, oké.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Milyen távolságra? Ne feledje, hogy húsz méteren túl nem fogok tudni pontosan célozni. Kivéve persze, ha nincs szükséged arra, hogy eltaláljak valamit, hehe.","Mintha büdös férfiak közelébe akarnék menni, miután körülötted voltam. Szóval, mekkora a távolság? De ne feledd, nem igazán tudok célozni, húsz méteren túl senki sem tud.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Oké, milyen távolságról? De hadd emlékeztesselek, hogy a csata hevében nem fogok tudni húsz méternél pontosabban és lassabban lôni.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Nem, nem, nem, nem, nem, nem. Mi az? Mi az? Ne feledd, hogy... nos, már nem vagyunk kicsik, ezt mindketten tudjuk.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Nem kellene humorral próbálkoznod.","Még sokat kell tanulnod tôlem a humorról, kislányom. De haladsz elôre!")+"";
				link.l1 = ""+GetSexPhrase("Ez furcsa; nekem mindig az ellenkezôjét mondták.","Nagyon vicces, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Nem a legrosszabb vicced. Talán egy nap abbahagyod a savanyúságot, heh-heh.";
					Link.l1 = "Hát jó.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ha-ha-ha, jó vicc.";
					Link.l1 = "Igazából, én csak... oké.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Nos, akkor én csak állok és tartom a pozíciómat. Ha túl messzirôl harcolsz ellenük, akkor a te seggedet kockáztatod, hehe.";
				link.l1 = "Ne gúnyolódj, mostantól pontosan azt akarom, hogy tartsd a helyed.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, mondhattad volna, hogy maradjak a vonalban, és ne beszéljünk távolságokról és számokról.";
					Link.l1 = "Nos, a lényeg, hogy megértettél.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Értettem, itt tartom a frontot. Akkor hozd ôket közelebb hozzám, hogy lôhessek.";
					Link.l1 = "Természetesen.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Nézd, tudom, hogy azt szeretnéd, ha minden lövésem olyan lenne, mint a világítótoronynál, de ez nem fog megtörténni. Jó pozíció volt. Nyugodt és stabil. Ezt nem tudod megismételni a csata hevében.";
				link.l1 = "Hmm. Akkor maradj húsz méter távolságban.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Tudom, hogy ezt szeretnéd, minden srác ezt szeretné, de mint akkor, a világítótoronynál, ez már nem fog mûködni. Kell egy jó pont, és hogy senki se jusson el hozzám, különben az idegeim felmondják a szolgálatot.";
					Link.l1 = "Hm-m, oké.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Azóta bizonyára csiszoltam a képességeimen, de a lehetetlen lehetetlen marad - a csata hevében soha nem tudnám megismételni azt a lövést a világítótoronyból. Még egy kerékzáras puskával sem.";
					Link.l1 = "És a lehetetlen is lehetséges, Tommy. De oké, a nem azt jelenti, hogy nem.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Nagyon jó. Pontosan tartom ezt a távolságot, de ha egy kocsmában vagy barlangban harcolunk, akkor kimegyek, hogy megtartsam, hehe.", "Megpróbálom. De a fedélzetek és a zárt terek diktálhatják a saját feltételeiket.");
			link.l1 = ""+GetSexPhrase("Nem vicces, Tommy. Viselkedj a helyzetnek megfelelôen, de ne viccelôdj, vagy csinálj hülye csínyeket.","Tudom, Thomas, nem vagyok hülye.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Megpróbálok emlékezni.";
				Link.l1 = "Oké, számítok rád.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Igen, kapitány.";
				Link.l1 = "Pihenj, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Miben segítesz, ellopni? De miért? Természetesen hízelgô, de már régen elmondhattál volna mindent. Gyerünk, köpd ki.";
			link.l1 = "Vigyázz a szádra, jó? Hát, a fenébe is - nem igazán érdekel, hogyan fejezed ki magad, amíg az én oldalamon állsz. Szóval, az a bálvány. Rajta keresztül... varázslatos módon eljuthatsz egy másik helyre. Ne nézz így rám - tudom, hogy hangzik. De én már átéltem ezt az egészet, és a saját szememmel láttam. Ez... biztonságos, ha megiszol egy elixírt.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Látom, már megittál néhányat. Bár nem, józannak tûnsz. És azt mondják rólam, hogy mindig hülyeségeket beszélek...";
			link.l1 = "Velem jössz vagy sem? A bálvány állítólag egy ôsi maja városba visz minket, és ki tudja, mi vár ott ránk? Te vagy az egyik, akire a nehéz pillanatokban számíthatok. És most épp egy ilyen pillanat jött el.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Rossz érzésem van ezzel kapcsolatban. Ha nem a kapitányom lenne, azt mondanám, hogy egy elmegyógyintézetben lenne a helye. Legközelebb azt fogja mondani, hogy Isten létezik.";
			link.l1 = "Tudja, Tommy. És, ahogy meglepetésemre felfedeztem ezen a szigetvilágon, nem csak a miénkben. Te magad is láthattad, hogy milyen ördögi dolgok történnek itt. És bizonyára észrevetted az áldott vagy átkozott csecsebecsék hatását.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Az ördögi praktikák itthon is léteznek. És mindig is volt rá normális magyarázat. Sajnálom, kapitány, de nem fogok veled kôbálványok körül táncolni. Lövöldözô ellenségek - szívesen. Lehet, hogy elvesztettem az emlékezetemet, de az eszemet nem vesztettem el. Legalábbis azt hiszem.";
			link.l1 = "Hát, én nem kényszeríthetlek. Szóval... ahogy kívánod, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Kétlem, hogy lesz merszed lelôni ôket, te merész, ha félsz a bálvány közelébe menni.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ó, nos, ne duzzogj. Oké, ha visszajössz, miután körbetáncoltad azt a bálványt, akkor legközelebb meggondolom.";
			link.l1 = "Lehet, hogy nem lesz következô alkalom. Menj vissza a hajóra, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Nem félek, ne érts félre. De megszoktam, hogy a megérzéseimre hallgatok, az évek során sosem hagytak cserben. És most azt súgja, hogy ebbôl semmi jó nem sül ki. És különben is... Hát, majd megsértôdsz.";
			link.l1 = "Gyerünk, mondd csak.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Hát, ha ez a helyzet! Beleegyeztem, hogy melletted harcolok. De mi van, ha, képzeljük el, ez a dolog tényleg mûködik? Mi van, ha el van átkozva? Nem fogok meghalni senkiért, sajnálom.";
			link.l1 = "Most már bizonyítottál, Tommy. Most a leghûségesebb emberekre volt szükségem. És most látom, hogy te nem tartozol közéjük. Odamegyek. Te pedig... csinálj, amit akarsz.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Nézz rá. Mégiscsak megsértôdött.";
			link.l1 = "Fogd be a szád. Ha ennyire undorítónak találsz minket, nem kell visszajönnöd a hajóra.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Hûha! Ez most komoly? Hát, talán így a legjobb. Nem akarok olyanokkal lenni, akik még a vicceket sem értik. Ebben az esetben... viszlát, excellenciás uram.";
			link.l1 = "Viszlát, Tommy. És menj a pokolba.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_tieyasal_otkaz");
		break;
	}
} 