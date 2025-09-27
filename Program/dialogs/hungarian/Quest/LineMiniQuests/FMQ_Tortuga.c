// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
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
			dialog.text = "Egy nyilvánvaló bogár. Szólj róla a fejlesztôknek.";
			link.l1 = "Ó, meg fogom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Ó, hello monsieur! Üdvözöljük a Tortugán! Az ilyen nemes kapitányok, mint ön, ritka vendégek itt...";
			link.l1 = "Üdvözlöm, mademoiselle. Köszönöm a szívélyes fogadtatást. De hogyan? Azt hittem, hogy egy ilyen fontos kikötô mindig is a nálam sokkal nemesebb vagyonos urak érdeklôdési körébe tartozik.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ah, monsieur... Ön nyilvánvalóan újonnan érkezett, igazam van? Majd meglátja. Fogalma sincs, milyen nehéz méltó férfiakat találni a kormányzó palotájának táncmulatságára. Talán elkísérhetne engem...?";
			link.l1 = "Hogyan lehetnék szolgálatára egy ilyen gyönyörû nônek?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Jaj, jaj, micsoda gáláns viselkedés! (kuncogás) Talán ma este hatkor meglátogathatna minket? Kormányzónk felesége rendszeresen rendez informális partikat a palota szolgáinak' szállásán. Ritka lehetôség számunkra, hogy ilyen eseményekre érdekes társaságot kapjunk. Meglátogatna minket? Kérem, jöjjön el, nagyon örülnénk neki.";
			link.l1 = "Megtiszteltetés lenne, mademoiselle. Ma este meglátogatom önöket.";
			link.l1.go = "girl_3";
			link.l2 = "Bocsásson meg, kisasszony, de sürgôs dolgom van. Talán majd máskor?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Kár. Találnom kell valaki mást, aki elszórakoztat engem és a barátnôimet... a társaságomban. Viszontlátásra.";
			link.l1 = "Ég veled!";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Köszönöm! Ígérem, ezt az éjszakát sosem fogja elfelejteni, monseiur! Au revoir!";
			link.l1 = "Viszlát...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Hé, tengerész! Melyik szerencsés szél fújt ma ide? Ritkán látunk ilyen jó embereket Tortugán.";
			link.l1 = "Üdvözlöm önt is, mademoiselle, ön mindig elpirít a bókjaival. A saját hajóm kapitánya vagyok, és elfoglalt ember, de biztos vagyok benne, hogy ez a sziget eleget tud nyújtani egy magamfajta vad csavargónak ahhoz, hogy jól szórakozzon.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(kuncogás) Ó, igen uram, ebben biztosan tudunk segíteni! Tortuga mindig tud valamit ajánlani. Ahogy én is... Miért, én szinte *mindent* hajlandó vagyok megtenni, miután hallottam egy jó tengeri történetet. Annyira szeretem ôket! Egy kapitány egyszer mesélt nekem egy nagy mesét arról, hogyan sikerült megmenekülnie egy lakatlan szigeten való kikötés elôl úgy, hogy tengeri teknôsökbôl készített tutajt. Micsoda gavallér! Megtennéd?";
			link.l1 = "Mit tudnék?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(kuncogás) Tudnál tutajt készíteni tengeri teknôsökbôl?";
			link.l1 = "Én még jobbat fogok csinálni. Egyszer egy szökött tanonccal elfoglaltuk az angol haditengerészet leggyorsabb hajóját, és csak egy fejszét használtunk. És tíz percig vissza tudom tartani a lélegzetemet. Akarod látni?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Talán késôbb. Szolgaként dolgozom a kormányzó palotájában. Gyere oda ma este hat órára, és találj meg engem és a barátomat a páholyban. Akkor majd mesélhetsz nekünk a kalandjaidról...";
			link.l1 = "Úgy hangzik, mint egy olyan meghívás, amit nem utasíthatok vissza. Este hatkor találkozunk.";
			link.l1.go = "girl_9";
			link.l2 = "Beosonni a kormányzó palotájába? Kicsit gazdagnak hangzik az én véremhez képest. Kihagyom, kedvesem. Keress meg a kocsmában, ha igazi férfitársaságra vágysz. Yo ho ho ho!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Ph-f. Mindegy, akkor majd találok egy jobb és nagyobb férfit, mint te. Végül is túl kicsinek tûnik a tôkesúlyod. Jó, hogy megszabadultál tôle.";
			link.l1 = "Még egy csatahajó is kicsinek tûnne, amikor áthajózik a te Széljárásodon.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Már alig várom!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Á, hát itt vagy! Kapitány "+GetFullName(pchar)+"! Nagyon örülök, hogy megismerhetem, régen volt már, hogy ilyen nemes és rangos hívó megtisztelt!";
			link.l1 = "Nagy megtiszteltetés és öröm számomra, hogy itt lehetek a társaságában, asszonyom. De mi a helyzet a többi vendéggel? Túl korán jöttem?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Ó, gyengélkednek és nem tudnak jönni. De ne is gondolj rájuk, igyunk bort és beszélgessünk... Ó, ha tudnád, milyen unalmasnak és magányosnak érzem magam itt! Tortuga egy mocskos barlang, tele söpredékkel, gazemberekkel és kalózokkal! Kalózokkal! És végre egy méltó úriember a házamban! Bárcsak a férjem több üzletet kötne a maga osztályához és tehetségéhez hasonló emberekkel! De nem, csak kalózok, kalózok mindenütt! Hallottál már arról az új divatról, ami egyre népszerûbb Párizsban, Ôfelsége királyi udvarában? Mi a véleménye róla?";
			link.l1 = "Bocsánat, mi a véleményem pontosan mirôl? Kalózokról? Vagy a divatról?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Ó, uram, ön olyan jól megért engem! Ezt nem is tudom elhinni. A férjem filléreket ad nekem, miközben ô MILLIÓKAT keres a kalózain, képzelje csak el! Kalózok! Ruhákat kell rendelnem ide, ebbe a koszos lyukba, de mire ideérnek, már hat hónapja lejártak! Hogy viselhet egy nô az én státuszomban ilyen rongyokat? Ó, annyira szeretném látni és viselni ezeket a párizsi divatokat! Gondolja, hogy jól néznék ki benne?";
			link.l1 = "Madame, ön nagyon csinos. Nem kell ehhez párizsi divat, ez már minden férfi számára nyilvánvaló ezen a gyönyörû szigeten.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Ön túl kedves hozzám... Kapitány, be kell vallanom, nagy bajban vagyok. De ugye segíteni fog egy szegény nônek?";
			link.l1 = "Persze, asszonyom. Bármit, amit csak kíván.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Vigyázzon, kapitány úr, vagy elveszítem a fejem! (kacér kuncogás) A férjem mostanában egy fillért sem ad nekem. Az a barom közönséges szajhákat hoz haza hozzánk, és egyáltalán nem törôdik velem!\nTudom, hol tartja a rosszul szerzett kincseinek egy részét, az irodájában van egy ládában. Ez az én pénzem, feleség és asszonyi jogon. Segíts nekem megszerezni, amivel tartozik nekem, és megjutalmazlak... Arannyal és... más kellemes dolgokkal.";
			link.l1 = "Ez egy érdekes ajánlat. Rendben, asszonyom, segítek önnek. Hol van ez a láda és hogyan nyissam ki?";
			link.l1.go = "wife_5";
			link.l2 = "Rendben van, madame, elhozom a láda tartalmát. Megkapjuk a pénzt, és utána nagyon kellemes 'beszélgetést' zunk együtt. Melyik ember utasíthat vissza egy ilyen ajánlatot? Hol van ez a láda és hogyan lehet kinyitni?";
			link.l2.go = "wife_6";
			link.l3 = "Asszonyom, ön megpróbál elcsábítani engem. Sajnálom, de a becsületem megköveteli, hogy visszautasítsam az ajánlatát. Együttérzek önnel, jobbat érdemel, de keresnie kell magának egy másik színészt a darabjához.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Kár. Akkor nincs mirôl beszélnünk, monsieur. Távozzon, és ne feledje: ha errôl egy szót is szól a férjemnek, meg fogja bánni!";
			link.l1 = "Ég veled!";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Ezt nem vártam tôled... A láda... Hagyjuk késôbbre, elôbb meg kell találnunk a másodkulcsot, amit egy mocskos kalóz lopott el. Éppen egy helyi barlangban mulatozik, és iszik, mint egy disznó. Siessetek, és hozzátok vissza a másodkulcsot. Várni fogok rád.";
			link.l1 = "Akkor ne vesztegesd az idôt!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Nem fogja megbánni, kapitány. Elôször is meg kell találnunk a másodkulcsot, amit egy mocskos kalóz lopott el. Éppen egy helyi barlangban mulatozik, és iszik, mint egy disznó. Siessetek, és hozzátok vissza a másodkulcsot. Várni fogok rád.";
			link.l1 = "Akkor ne vesztegesd az idôt!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Kapitány "+GetFullName(pchar)+"! Jajj, jajj! Micsoda ember a magánszobámban! Meglepôdtél? Ön az egyetlen vendég itt ma este. (kuncogás)";
			link.l1 = "Meg vagyok lepve, madame. De egyáltalán nem bánom. Üzleti vagy szórakozásról van szó?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Micsoda közvetlen megközelítés! Szeretem az olyan férfiakat, mint maga. Van egy üzleti ajánlatom az ön számára, kapitány. Megtalálom a módját, hogy kompenzáljam az erôfeszítéseit, ha sikerrel jár.";
			link.l1 = "Folytasd.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "A férjemnek van egy láda tele pénzzel és ékszerekkel. Gyûlölöm ôt, és nagyobb járandóságot akarok a fájdalmaimért.";
			link.l1 = "Asszonyom, nagyon szépen néz ki. Ehhez nincs szüksége több ékszerre vagy párizsi divatra, ez már minden férfi számára nyilvánvaló Hispaniolán.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Ön túl kedves hozzám... Kapitány, be kell vallanom, nagy bajban vagyok. Segítene egy bajba jutott nônek?";
			link.l1 = "Természetesen, asszonyom. A becsület ezt követeli. Bármit, amit csak kíván.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Vigyázzon, kapitány úr, vagy elveszítem a fejem! (kacér kuncogás) A férjem mostanában egy fillért sem ad nekem. Az a barom közönséges szajhákat hoz haza hozzánk, és egyáltalán nem törôdik velem!\nTudom, hol tartja a rosszul szerzett kincseinek egy részét, az irodájában van egy ládában. Ez az én pénzem, feleség és asszonyi jogon. Segíts nekem megszerezni, amivel tartozik nekem, és megjutalmazlak... Arannyal és... más kellemes dolgokkal.";
			link.l1 = "Ahogy óhajtja. Megteszem. Hol van ez a láda, és hogyan nyissam ki?";
			link.l1.go = "wife_13";
			link.l2 = "Ha! Nincs kérdés, egy ilyen nônek, mint ön, meg tudom tenni. Nem fogja megbánni, kedvesem. Megkapjuk a pénzt, és nagyon kellemesen fogjuk együtt tölteni az idôt. Hol van ez a láda és hogyan nyissam ki?";
			link.l2.go = "wife_14";
			link.l3 = "Nem én, asszonyom. Nem vagyok én olyan úriember, hogy egy éjszaka alatt felszarvazzak és kiraboljak egy férfit. Legalábbis nem ilyen módon. Keressen magának egy másik színészt ehhez a darabhoz.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Ó... egyre jobban tetszik nekem... Elôször is, vissza kell adnunk egy kulcsmásolatot, amit egy mocskos kalóz lopott el. Egy helyi barlangban mulatozik, és iszik, mint egy disznó. Siess, és hozd el nekem a másodpéldányt. Várni fogom.";
			link.l1 = "Akkor ne vesztegesd az idôt!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Maradjon nyugodt, uram, erre késôbb is lesz idô. (kuncogás) Elôször is vissza kell adnunk egy kulcsmásolatot, amit egy mocskos kalóz lopott el. Ô épp egy helyi barlangban mulatozik, és iszik, mint a disznó. Siessetek, és hozzátok el nekem a másodpéldányt. Várni fogok rád. Biztos vagy benne, hogy meg tudod csinálni?";
			link.l1 = "Ne kételkedj bennem, már úton vagyok.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Prûd szemérem! Tûnj a szemem elôl! És eszedbe se jusson elmondani ezt a férjemnek, mert még megbánod!";
			link.l1 = "Viszlát, édesem.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Kapitány úr! Megszerezte a kulcsot?";
			link.l1 = "Igen, megvan. Hol van a láda?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Ó! Az én hitvány férjem tényleg azt kapja, amit megérdemel? Maga egy hihetetlen ember, kapitány! Nagy jövô áll elôtted, tudod? Felejtse el a ládát. Majd én megcsinálom. Jöjjön el hozzám holnap, hogy megkapja a jutalmát. Nem fogja megbánni, kapitány...";
			link.l1 = "Rendben. Ahogy akarod. Alig várom, hogy holnap találkozzunk.";
			link.l1.go = "wife_17";
			link.l2 = "Nem, elfoglalt ember vagyok, és nem akarom az idôt vesztegetni a várakozással. Miért várna? Mondja meg, mit kell tennem, és én megteszem. Nem hagyhatom, hogy egy ilyen gyönyörû nô elrontja a szép kis kezét, ha egy zárral és kulccsal babrál.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Jöjjön el hozzám hat órára, bátor lovagom...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Biztos vagy benne? Lehet, hogy veszélyes lehet önre nézve. Miért akarja kockáztatni az életét, kapitány úr?";
			link.l1 = "Rendben. Ahogy akarod. Alig várom, hogy holnap találkozzunk.";
			link.l1.go = "wife_17";
			link.l2 = "Már döntöttem. Mit kellene tennem pontosan?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Egy oroszlánszív! Menjen a férjem irodájába, ott megtalálja a ládát. Használja a másodkulcsot. Senki sincs fent ilyenkor éjszaka, úgyhogy ne siess. Gyémántok vannak a ládában. Rengeteg van belôlük. Vedd el mindet és térj vissza hozzám. Várni fogok rád. Ne árulja el a bizalmamat... kérem.";
			link.l1 = "Hamarosan visszajövök.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Ó, kapitány! Én... maga... Kész van? Ó, és ki ez?! A-ah!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Ó, te jó ég! Kapitány, megmentettél! Te... te vagy a hôsöm! A férjem gengsztere volt, meg akarta önt ölni! Könyörögtem neki, hogy ne tegye! Megsérült? Elhoztad a gyémántokat?";
			link.l1 = "Ha. Tényleg? A férjed egy féltékeny ember... Mindegy. A pokolba vele, nálam vannak a kövek.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Ó, kapitány! I... Maga... Végeztél?";
			link.l1 = "Volt egy kis bonyodalom, de már el van intézve. Miért sápadt, asszonyom? Jól van? Nálam vannak az ékszerek, ez majd felvidítja, igazam van?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Hála Istennek! Megbosszultam magam! Lovagom! Hány gyémánt volt ott?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "A lovagod egy zsáknyi zsákmánnyal tért vissza a kalandból. A felét a hölgyére hagyja, hogy megvehesse a legjobb párizsi divatot. Megtartottam az ígéretemet.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Ó, rengeteg gyémánt volt, de nem fogsz kapni semmit. Felbéreltél egy bérgyilkost, hogy megöljön engem, te putain! Tényleg azt hiszed, hogy mindezek után osztoznék veled? Ha kinyitod a szádat, a férjed megtudja, hogy ki akarod rabolni és felszarvazni. Úgyhogy tartsd a szád!";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Gazember! Szemétláda! Ezt nem úszod meg!";
			link.l1 = "Igen, ezt már hallottam korábban.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("Gyémántokat kaptál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Te nem olyan vagy, mint... a többiek. Megkapod, amit akarsz. Fényes jövô áll elôtted. Tudom, hogy elfoglalt ember vagy, de... Maradnál velem egy kicsit? Senki sem fog zavarni minket, ígérem.";
			link.l1 = "Mindig van idôm egy olyan gyönyörû nôre, mint te. Kinyissak egy üveggel a férje borából?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("Gyémántokat kaptál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Azt hiszem, tudok nélkülük élni. Rengeteg lehetôség van itt a pénzköltésre. Annyi jóképû és méltó férfi van Tortugán... Köszönök mindent, kapitány. Csak hogy tudja, kérem, hallgasson errôl a viszonyról, különben a férjem felakasztatja magát egy bitófára. Ô nem egy jó ember. Viszontlátásra.";
			link.l1 = "Csak így? Tanulságos tapasztalat volt. Viszlát, asszonyom, javaslom, hogy errôl is hallgasson, én sem vagyok jó ember. De ezt már tudja, ugye?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Ki maga és mit keres itt?";
			link.l1 = "Mit játszadozik? Megállapodtunk...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Milyen üzlet, monsieur? Én férjes asszony vagyok, nem üzletelek más férfiakkal! Hagyja el a szobámat, vagy hívom a férjemet és az ôrségét!";
			link.l1 = "Csak így, mi? Rendben, azt hiszem, ebben az esetben felvilágosítom a jó férjét!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Távozz most, te szemtelen fickó, vagy az embereim a La Roche erôd oubliette-jébe vetnek! Nem érdekelnek a fenyegetéseid! Kifelé!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Ki vagy te? Á, mindegy. Ne bízz a nôkben, haver. Ahogy a Biblia mondja... még a leghülyébb kurvák is a pokol fenekére rángathatnak a férfi-emberi manipulációikkal. Foglalj helyet, haver, igyál egy italt!";
			link.l1 = "Örömmel!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "Mit bámulsz? Töltsd ki!";
			link.l1 = "Igyunk rád!... Hé barátom, nem fogom itt vesztegetni az idôt. Szükségem van arra a másodkulcsra, ami nálad van, tudod, mirôl beszélek. Add ide, és elválnak útjaink: te tovább iszol, én pedig segítek a bajba jutott lányoknak.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Hé haver! Nem figyeltél arra, amit az elôbb mondtam! Biztos okosabbnak tûnsz, mint amilyen valójában vagy... annak a kurvának dolgozol. Tudod, ki a férje? Nemrég Levasseur kormányzó elküldte hûséges négerét, Kampachót, hogy menjen 'beszélgetni' egy helyi és nagy tekintélyû kereskedôvel. A fekete agyonverte a szerencsétlent a saját boltjában! Ez a kereskedô valami kisebb tiszteletlenséget tanúsított a kormányzó feleségével szemben egy bálon vagy ilyesmi alatt. És ugyanez a ribanc elcsábított a külsejével és a dublonjaival\nA másodkulcs létezik. Régebben, Franciaországban rendes széftörô voltam, úgyhogy gyerekjáték volt. Ha nem lett volna Lyons parancsnokának lánya... sosem lettem volna kalóz. Bah! Bassza meg!";
			link.l1 = "Ez mind nagyon szomorú, de beszéljünk az üzletrôl. Hol van a kulcs?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Figyelsz rám? Kiszálltam a játékból, haver! Elég okos voltam, hogy lássam, mi jön! Örökre elhagyom ezt a helyet, amint a hajóm készen áll a kihajózásra. Ha kell a kulcs, fizess érte! Ne légy itt kapzsi, szerintem hamarosan nem lesz szükséged pénzre.";
			link.l1 = "Tudod, igazad van. Nem akarok egy nô játékszere lenni. Köszönöm a tanácsot és vigyázz magadra a tengeren!";
			link.l1.go = "pirate_4";
			link.l2 = "Fizetsz érte? Neked? Szánalmas tolvaj és gyáva vagy. Ott kellett volna maradnod abban a szaros Lyonsban. Ki tudja, talán a helyi parancsnok megsajnált volna, és egy degenerált tolvaj lett volna a veje. Én nem fogom megsajnálni magát, az biztos. Átadhatod a kulcsot a könnyebb vagy a nehezebb úton, a választás a tiéd.";
			link.l2.go = "pirate_5";
			link.l3 = "(sóhaj) Mennyi?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Okos fiú, ez a helyes döntés, pajtás. Sok szerencsét! Remélem, egy nap találsz egy igaz és szeretô nôt. Lehetôleg egy vöröset vagy szôkét, igazam van?";
			link.l1 = "Viszlát, haver...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Megsértettél! Húzz acélból, te szemétláda!";
			link.l1 = "Lássuk, milyen jól tudod feltörni a széfeket kar nélkül!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Te egy üzletember vagy, ezt meg kell hagyni. Lehet, hogy tényleg sikerülni fog. Ötven dublont. Az asztalra.";
			link.l1 = "Ötven aranyat? Egy darab ónért? Húzzon el! Tedd a kulcsot az asztalra. Tegye le a kulcsot az asztalra.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Micsoda ár... Rendben. Fogd ôket.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Elég nagy ár... Rendben. Hamarosan hozom ôket. Maradj itt.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Hoztál ötven dublont?";
			link.l1 = "Tudod, szerintem tudsz nélkülük is élni. A kulcs. Az asztalon.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "A kulcs az asztalon van. Vedd el ôket.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Még mindig veszem ôket.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Táncoljunk?";
			link.l1 = "Én vezetek.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("Adtál 50 dublont");
			PlaySound("interface\important_item.wav");
			dialog.text = "Jól van. Használd az eszed, és talán megúszod ezt néhány darab nyolccal és a fejeddel. Fogd a kulcsot és hallgass a tanácsomra. Ingyenesen. Levasseur asszonya buta, mint a hal, mégis ravasznak hiszi magát. Ne bízzon benne. Tartsd a farkad a nadrágodban és vigyázz a zsebeidre. Nem nagy ellenfél, csak légy óvatos, és kerüld el, hogy a férjét is belekeverd ebbe\nEgy utolsó dolog - van egy láda a lugasában, ahol a csecsebecséit tartja, könnyen fel lehet zárni. Oda fogja tenni a vágását. Hallottad, amit mondtam. Vigyázz magadra a tengeren, testvér. Ne feledd, hogy elôbb a testvérek, mint a lányok.";
			link.l1 = "Isten éltessen, haver...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "A francba! Nem számítottam rá... a pokolba a nôkkel! A mesterem azt mondta, hogy kerüljem a fajtáját. De a munka az munka. Végül is elkaplak.";
			link.l1 = "Nocsak, nocsak, haver... Úgy tûnik, mindkettônket át akart verni, nem mondhatnám, hogy meglepôdtem. Miért kellene tovább harcolnunk? Akarsz munkát? Nekem van. Te ügyes vagy, szükségem van az ilyen emberekre a legénységemben. Étkezés, priccs, rendes fizetés, rum, és tisztességes részesedés a zsákmányból. Megkapod a pénzemet. Mit mondasz?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Képességellenôrzés megfelelt", SKILL_FORTUNE);
			dialog.text = "Ezüst nyelved van, és a hírneved megelôz, kapitány, ezt meg kell hagyni. Igen, benne vagyok. Mi a hajó neve?";
			link.l1 = "'"+pchar.ship.name+"'. Beszélj a bosunnal, ô majd talál neked egy priccset.Üdvözöllek a fedélzeten!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ha! Feljebb lépek a világban. Rúgd meg azt a ribancot a nevemben.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Képességpróba Sikertelen (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Képességpróba Sikertelen (21)", SKILL_FORTUNE);
			dialog.text = "Szépen beszélsz. De nem elég édes, ha azt akarod, hogy igazi profik csatlakozzanak hozzád. Ezt tartsd észben a jövôben. Ha lesz.";
			link.l1 = "Próbáld ki. Légy gyors, eljegyeztem egy hölgyet.";
			link.l1.go = "mercen_5";
			link.l2 = "Ma nincs második esély. Elfoglalt ember vagyok, úgyhogy ne rontsuk el a szônyeget. Nem kapsz elég pénzt, hogy meghalj egy kis pitiánerért. Ha egyáltalán fizetnek neked.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Igazad van. Senki sem fizetett nekem... még. Ezt most rögtön elintézem. Csinálj, amit akarsz...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
