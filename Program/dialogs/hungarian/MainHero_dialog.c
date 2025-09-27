void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Ha ezt a sort olvasod, ez egy hiba a kódban.";
			Link.l1 = "Kilépés";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
			{
				dialog.text = "Izgalmas, a fenébe is! Egy igazi tengeri csata!\nKár, hogy innen nem fogom látni a harcot... Nem baj. Azt hiszem, eleget tanultam a tengerészetrôl ahhoz, hogy elképzelhessem, hogyan megy ez\nVélhetôen öt kalóz... Egy nagy hajó, néhány közepes, és néhány kis kalóz. Épp megfelelô a mi cirkálónknak. Remek mese lesz belôle - Lulu imádni fogja!";
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
				pchar.wind.speed = 18.0;
				fWeatherSpeed = stf(18.0);
				//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
				AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
			}
			//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "Szóval, megtaláltuk ezt a helyet a térképen. Meg kell jelölnöm, és már mehetünk is keresgélni.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "Rendben, itt vagyunk. El kéne rejtenem a hajómat a déli öbölben, aztán gyalog visszajönni a dzsungelen keresztül, és kellemetlen meglepetést szervezni Fleetwoodnak.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "Hm... Bízni ebben a gazemberben veszélyes, bár a története hitelesnek tûnik. Talán ezúttal nem hazudik. De mindenesetre, beszélnem kell a feleségével... Bosun! Hozd ide azt a fogoly nôt!";
    			link.l1 = "Igenis, kapitány!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "Úgy tûnik, ez a megfelelô hely. Ez az egyetlen fa a környéken, ami nem termô. Itt kellene ásnom.";
    			link.l1 = "(ássuk ki a kincset)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "Mi folyik itt? Hol vagyok?! Miféle hely ez?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "Ez az ajtó a hajó belsô helyiségeibe vezet. Zárva van... Sólyomnak itt kell lennie. Mit is említett Ole? Titkos kopogást kellene használnom.";
    			link.l1 = "Kopogj kétszer.";
    			link.l1.go = "knock_2";
				link.l2 = "Kopogj háromszor.";
    			link.l2.go = "knock_3";
				link.l3 = "Kopogás egyszer, szünet, kopogás háromszor.";
    			link.l3.go = "knock_1_3";
				link.l4 = "Kopogj kétszer, szünet, kopogj kétszer.";
    			link.l4.go = "knock_2_2";
				link.l5 = "Kopogás háromszor, szünet, kopogás egyszer.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "Hûha! Ez az izé tényleg nehéz!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "Ne-ne-ne-ne! Nem lehet! Háromszor több mint elég volt!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "Megtörtént. Levasseur halott. Sokkal könnyebbnek bizonyult, mint vártam... De valami nincs rendben. Thibaut nem is beszélt Martene-vel! Ez azt jelenti, hogy vagy Robert elárult engem, vagy baleset történt\nDe hová menekülhetett az a rohadék Thibaut? Biztos Catherine-re vadászik. Gyorsan kell cselekednem, ha élve akarom elvinni a lányt az orra elôl...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "Kincsek, kincsek... egy indiai város... Nem hiszek az ilyen véletlenekben... Fogadok, hogy a bátyámnak köze van Dichoso fregattjának eltûnéséhez. Valószínûleg gondoskodott róla, hogy Dichoso soha többé ne nyissa ki a száját\nVagy talán együtt dolgozott vele, a spanyoloknak biztos volt oka azt hinni, hogy Dichoso valahol itt van a környéken. Ennek semmi értelme. De abban biztos vagyok, hogy az indiai arany, amit Michel de Poincy-nak szállított, valamint Miguel Dichoso aranya ugyanaz az arany. A fogoly története egyezik azzal, amit a tiszt mesélt nekem a bátyám kalandjairól\nVicces, Michel nem szállította le az aranyat, és Miguel is! És akkor most hol vannak a kincsek? Talán ôk voltak az oka annak, hogy a bátyám ennyire sietett\nErgo, az arany megtalálása két legyet ütne egy csapásra: Újra a bátyám szemtelen szemébe nézhetek, és... igen, az arany mindig jó. De hogy a fenébe találom meg? Úgy tûnik, itt az ideje, hogy igazán közel kerüljek a spanyolhoz\nDon Ramona Mendoza lekerült az asztalról, kétlem, hogy képes leszek vele elbánni, de szent Vincento atya, egy báró legnagyobb ellensége... ô megteszi. Az ô fajtája nem lelkiismeretes, de szereti a pénzt és a piszkos eszközöket\nDichoso, Dichoso... Hallottam már ezt a vezetéknevet... vagy mégsem? Mindegy, a pokolba vele. El kellene mennem a tiszthez, és követelni a spanyol foglyot. Aztán bármikor elindulhatok Santiagóba.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "A Vaníliát felpakolták a karakkra, és a vitorlái már rég eltûntek a horizonton túl - és ez az átkozott gálya visszatért a kikötôbe, ahelyett, hogy a nyílt tengerre indult volna. Nem szabad a hajómmal a kikötôben megjelennem - jobb, ha azt hiszik, hogy elhagytam Guadeloupe-t... Azt hiszem, gyalog megyek a városba a dzsungelen keresztül, és megtudom, mi van az én drága Marchais-ommal...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "A felsô fedélzeten csak néhány ôr van, mindegyikük meglehetôsen álmos. Gondolom, egyenként kiiktathatom ôket, ha csendben hátulról jövök, és egy bokornyakkendôvel tarkón vágom ôket... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "Egy lezáratlan, üres ház, a második emeleten egy hangulatos szobával, és Calhoun lakásának közelében... Ez csak egy leány imájára adott válasz... Ha kiszállok az ablakon, és a tetô abat-jourján sétálok, könnyedén besurranok Archie szobájába. De ezt éjszaka kell megtennem, nehogy lebukjak...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "Végre! Megtaláltam a helyet, amelyet a 'megnyilvánulás jelez: ez egy indiai bálvány. Amikor a közelben van, az 'Út' nyila abbahagyja a lengést, és egy irányba mutat. Nos, ez logikusnak tûnik - indiai mágia és egy indiai bálvány. Most meg kell jelölnöm a térképen az 'Az Út Nyila' által jelzett helyet, aztán elmegyek Dominikára.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "Végre! Megtaláltam a helyet, amelyet a 'megnyilvánulás jelez: ez egy indiai bálvány. Amikor a közelébe ér, az 'Az Út' nyila abbahagyja a lengést, és egy irányba mutat. Nos, ez logikusnak tûnik - indiai mágia és egy indiai bálvány. Most meg kell jelölnöm a térképen az 'Az Út Nyila' által jelzett helyet, és aztán elmegyek a Mainba.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "Mindkét megnyilvánulást megtaláltam! Most a második irányt kell bejelölnöm a térképen. A két irány metszéspontja megmutatja nekem a Ksocheatem szigetének helyét.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "Alonso de Maldonado azt mondta, hogy van egy út Tayasalba, amely Yucatántól északra indul. Ez azt jelenti, hogy mélyen be kell mennem a terület selvájába. De Gino azt mondta, hogy a teleport-szobrok eredetileg arra voltak hivatottak, hogy az embereket Tayasalba\nés a miskitók sámánja, Kígyószem azt mondta nekem, hogy a bálványok arra lettek tervezve, hogy a 'eaten' a helyre küldjék. De akkor miért törtek el azok a portálok? Hm. Emellett a Két Megnyilvánulás térképén egy furcsa kör látható a Miskito szobor közelében\nMi a fenét jelenthet ez? Egy másik mágikus hely? Vagy azt mutatja, hogy az ottani szobornak van valami plusz funkciója? Gondolom, meg kellene látogatnom a sámánt. Vagy elmehetek a Main északnyugati részére, és megkereshetem az ösvényt ott, az egyik helyi öbölben.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alonso de Maldonado azt mondta, hogy a Yucatan-félsziget északi részébôl egy másik út is vezet Tayasalba. Ez azt jelenti, hogy a selva mélyén kell keresnem egy ösvényt. Valószínû, hogy az út, amelyre szükségem van, az északnyugati fôfolyó egyik öblénél kezdôdik.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "Megtörtént. Hosszú utam vége. El sem tudtam volna képzelni, hogy a bátyám megmentése a börtöntôl azt jelenti, hogy felkészülök az ellene vívott végsô harcra! Hogy majdnem elpusztítottam a világunkat. Hála Istennek, vége\nNem tart többé semmi a Karib-tengerben. Ideje hazatérni, Franciaországba. De... Tényleg ezt akarom?";
				link.l1 = "Igen, visszatérek Európába.";
				link.l1.go = "final_1";
				link.l2 = "Nem, itt maradok a Karib-tengeren.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "Hallottad az ezredest? A lázadók ott bujkálnak! Kutassanak át mindent, fordítsák fel a házat, és fogjanak el mindenkit, akit ott találnak! Menjetek oda!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "Ez a legjobb hely a rajtaütéshez. Itt kell megvárnom Pinette érkezését.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "Hm. Ez a történet nem tûnik helyesnek. Azt hiszem, hogy a St. Jones-i luggernek sosem kellett volna léteznie. A hadnagy belerángat a hadmûveletébe. Miért lenne erre szükségem? Nem állok háborúban a hollandokkal... Elmenjek innen messzire, küldjem mindet pokolra — vagy maradjak?";
				link.l1 = "Menj el.";
				link.l1.go = "FMQN_1";
				link.l2 = "Maradj.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "Szóval, a láda készen áll. Megpróbálhatnám magam is megtalálni a szükséges anyagot, de inkább elmegyek Fadeyhez. Olyan embernek tûnik, aki bármit meg tud szerezni.";
    			link.l1 = "*HASZNÁLJA A HANGOSAN GONDOLKODÓ OPCIÓT, HOGY BEFEJEZZE A LÔSZEREK ÖSSZEGYÛJTÉSÉT*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "Szóval, hat hosszúhajót kell építenünk. Ehhez szükségem van egy ácsra, 20 deszkára és 10 bôrkötegre.";
    			link.l1 = "*HASZNÁLJA A HANGOS GONDOLKODÁS LEHETÔSÉGÉT, HOGY ELKEZDJE A HOSSZÚHAJÓK ÉPÍTÉSÉT*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "Szóval, egyszerûen fel akarom robbantani ezt a halom öreg fát az égbe. Ehhez csak 300 egység puskaporra van szükségem, csak a biztonság kedvéért.";
    			link.l1 = "*használj egy hangosan gondolkodó opciót, hogy rendelj egy lôpor elhelyezést*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" A kijárat le van zárva! Úgy tûnik, valami nehéz dologgal eltorlaszolták az ajtót! "+RandSwear()+"\nHush... Mi a fene?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "Ez az... Vége a sornak\n Úgy tûnik, don Enrico komolyan gondolta: nincs kiút ezekbôl a börtönökbôl. Volt egy pillanatnyi reményem, amikor találtam egy második ajtót a víz szintjén, de most... Elvesztettem az idôérzékem - mióta is lôdörgök ezekben a sötét alagutakban? Fél nap, egész nap? Ez a hely olyan csendes és ijesztô, mint egy koporsó\nEgyszer volt itt egy templom, pont itt. Tökéletes hely, hogy elmondjam az imáimat. Sokat vétkeztem, túl sokat... Itt fogok imádkozni és aludni, a sebeim és a kimerültségem megölnek. Ha szerencsém van, soha nem kelek fel...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "Én, Charles de Maure, francia kapitány és nemes, esküszöm magamnak és a lelkiismeretemnek, hogy végleg leszámoltam kalózmúltammal!";
    			link.l1.go = "Good_Choice";
				link.l2 = "Ez az! Ez az! Ah ha ha ha!!! Megcsináltam, túléltem! Egyél, Zorro! Menj a pokolba, Marcus! Most már egyedül vagyok! Charlie Prince talán meghalt, de Charles de Maure-t senki sem ölheti meg!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "Mit tegyünk?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "...természetesen Levasseur nem bolond. Különben miért kellett volna éppen most letartóztatniuk minket?\nÉs egy szót sem szóltak!\n" + dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "Helen, miért vagy ilyen csendes?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "Mary, miért vagy ilyen boldog?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "Tichingitu? Mondj valami a helyzetnek megfelelôt.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "Hercule, hallasz engem? Mit fogunk csinálni?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "Semmit sem tehetünk. Azt hiszem, egy ideig Michel cipôjét fogom viselni.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "Istenem, megölték Hercule-t!";
				link.l1.go = "exit";
				link.l2 = "Rohadékok!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "Micsoda este! Miért hallgattam rá? A bátyámnak igaza volt - az itteni lányok teljesen mások. Talán ôk adnak valamit a rumhoz?";
				link.l1 = "Ideje aludni, és aztán - Cartagenába!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "Egyetlen dolgot sem loptak el, bár minden szétszóródott. Még az értéktárgyak is érintetlenek. ";
				link.l1 = "Nem ki akartak rabolni - valami konkrét dolgot kerestek. De mit is? És ami még fontosabb, hogy ki...?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_4");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "Várjunk sötétedésig, és támadjunk!";
				link.l1 = "Addig is elkezdjük elôkészíteni a hosszúhajókat.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "Ó, Istenem... Nem, nem, nem, nem... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "Ó, Istenem, ó, Istenem, ó, Istenem... Miért? Miért? Istenem, miért... de megtettem mindent, amit tudtam...";
				link.l1 = "Az egész az én hibám, egyedül az enyém. Nem értem ide idôben. Annyira sajnálom... Kérem, kérem, bocsásson meg nekem.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("Ez aztán a pokoli küzdelem volt... Most már hívhatjuk azokat a gyávákat, akik elfutottak...", "Ha! Ez könnyû volt. És azok a szárazföldi barmok csak úgy szétszéledtek!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Hmm... Akkor most mit tegyek?", "Mit tegyek most?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Hívj egy társat.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Pihenj reggelig.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Pihenj éjszakáig.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Pihenj másnap reggelig.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Vedd be a rabszolgákat a legénységbe.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "Kezdjétek el elfoglalni a legközelebbi várost.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "Pihennem kéne...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "Ki akarom cserélni a lôszert a lôfegyverekhez.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "Ki akarom cserélni a lôszert a muskétához.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "Ki akarok választani egy elsôbbségi fegyvert a harchoz.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "Ki akarok választani egy állandó használatra szánt varázsitalt.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "Próbáld meg megtalálni a szigetet a térképen lévô koordináták alapján.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Hívd ide Adam Raynert.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Tartóztasd le Adam Raynert.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "Számold össze a láda tartalmát, és döntsd el, hogy befejezed a lôszergyûjtést Picard számára.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "Adj parancsot a Maracaibo ültetvény megtámadására.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "Adj parancsot hosszúhajók építésére.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "Adj parancsot a lôpor leszállítására a halott abatishoz.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "Gondolkodjon egy esküvôn.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "Tegyen házassági ajánlatot.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "Készítse elô az ünnepséget.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "Fejezd be az üzletet a Karib-tengeren, és hajózz Európába.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("Most nem. Nincs rá idô.", "Erre nincs idô, túl sok a tennivaló.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		

		
		case "SetGunBullets":
			Dialog.Text = "Válaszd kia lôszertípust:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
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
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Válaszd kia lôszertípust:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "A harc elején fogom használni:";
			Link.l1 = "Penge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskéta";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "Válaszd kia bájitalt:";
	    	Link.l1 = "Gyógyító ital.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "Elixír.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "Keverék.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "Gyömbérgyökér.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "Rum.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "Bor.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "Automatikusan akarom kiválasztani a bájitalokat.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "Várj, meggondoltam magam...";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("Alapértelmezés szerint egy gyógyító esszenciát fogsz használni.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("Alapértelmezés szerint egy elixírt fogsz használni.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("Alapértelmezés szerint egy keveréket fogsz használni.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("Alapértelmezés szerint gyömbérgyökeret használnak.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Alapértelmezés szerint rumot használnak.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Alapértelmezés szerint bort használnak.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("A bájitalok automatikusan kiválasztásra kerülnek.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Megkezdhetnénk a város elfoglalását, de a hajó nem sokáig bírná az erôd ágyúinak szalvóit, és nem tudnánk partraszálló csapatot küldeni.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "Nem, még nem vagyok annyira ôrült...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "Nincs értelme megtámadni ezt a bányát anélkül, hogy elôbb ne gyûjtenénk információkat az ott bányászott aranyról és ezüstrôl. Különben hiába küldöm az embereimet meghalni.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Támadás " + GetCityName(chr.City) + ".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "Ne szórakozzatok! Állj!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "Ne szórakozzatok! Állj!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "Fegyverbe!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Állj!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Heh! Nincs elég ember a legénységben; legalább "+needCrew+" emberre van szükségünk.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Ne oszoljatok szét! Folytassátok a támadást!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Egyik rabszolga sem hajlandó csatlakozni a legénységhez.";
	            Link.l1 = "A pokolba velük!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "Nincs szabad hely a hajón az új matrózoknak.";
	                Link.l1 = "Heh! A legénység egy részét át kell helyeznem egy másik hajóra.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "A legénységed feltölthetô " + pchar.GenQuest.SlavesToCrew+ " rabszolgákkal, akik alattad akarnak szolgálni. Szeretné elfogadni?";
	                Link.l1 = "Igen";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Nem";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
			if(!bOk)
			{
				// belamour legendary edition перк получил время работы, старый метод не подходит
				if (GetOfficersPerkUsing(pchar, "IronWill"))
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
				}
				else
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
				}
			}
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Ez az édes hajó most már az enyém, és én vagyok itt a kapitány! Kár, hogy meg kellett ölnöm az egész legénységet.";
			Link.l1 = "Itt az ideje, hogy partra szálljunk...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Melyik társat idézzem meg?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Majd máskor.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "Kár, hogy nincsenek nálam a szélességi és hosszúsági fok meghatározásához szükséges navigációs mûszerek. Majd máskor kell megkeresnem a szigetet. ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "Bosun! Azonnal hozza ide Adam Raynert!";
			link.l1 = "Igenis, kapitány!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "Tehát, kopogtam, most várjuk a választ...";
			link.l1 = "(várjon)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "Tehát, kopogtam, most várjuk a választ...";
			link.l1 = "(várjon)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "Tehát, kopogtam, most várjuk a választ...";
			link.l1 = "(várjon)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "Tehát, kopogtam, most várjuk a választ...";
			link.l1 = "(várjon)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "Tehát, kopogtam, most várjuk a választ...";
			link.l1 = "(várjon)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "Nem nyitja ki az ajtót... Azt hiszem, rosszul kopogtam. Rendben, holnap jövök és megpróbálom újra. Ma biztosan nem nyitja ki az ajtót.";
			link.l1 = "(hagyja)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "Hûha! Válaszolt és kinyitotta az ajtót! Most már bemehetek...";
			link.l1 = "(írja be.)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "Caramba! Szóval ez Levasseur késleltetett helyettesítése... Kizárt, hogy az ajtón keresztül távozzak... Rendben, követem Thibaut-t - az ablakon keresztül! Végül is, ennek a gazembernek sikerült valahogy elszöknie!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "A mi feladatunk tehát az, hogy visszaverjük az átkozott spanyolok támadását, és megmentsük Saint Pierre-t. Az erôdöt elfoglalják, és az utcákon harc folyik. Saint Pierre öblében egy hatalmas hajóraj van, és egy csatahajót kaptak zászlóshajónak. Most megtámadni értelmetlen, az erôd és a város ellenséges ellenôrzés alatt áll, így nem engedik, hogy kikötôbe szálljunk\nEzért úgy döntöttem, hogy a dzsungeleken keresztül haladok, és hátulról csapok le rájuk a városkapukon keresztül. Amint az erôdöt és a várost megtisztítottuk a spanyoloktól, foglalkozunk a századdal. Az erôd tûztámogatása nélkül sokkal sebezhetôbb lesz\nEz nem lesz könnyû, ezért parancsot adtam, hogy a szokásos fizetésen felül további százezer pezót fizessünk a legénységnek. Induljunk!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "Várjatok, hová megyek? Nem hagyhatom el a fôkormányzói pozíciót Párizs engedélye nélkül! Különben egészen biztosan letartóztatnak a rábízott gyarmatok jogosulatlan elhagyása miatt, amikor visszatérek Franciaországba. Párizs, hiányozni fogsz ...";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "Akkor ne vesztegessük tovább az idôt! Annyira hiányoznak az én drága Gascogne-mezôi! Vitorlát bontani!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "Hiszem, hogy ez a helyes döntés! Mi vár még rám a jó öreg Európában, ha már itt találtam magam? Különben is, Franciaországba úgyis bármikor visszamehetek, amikor csak akarok!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "Ez a legjobb megoldás. Fel kell szállnom a fedélzetre, és elhajózni innen.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "Nem, kizárt, maradok. De a pokolba is, nem fogok itt maradni és várni Isten tudja mire. El kellene hajóznom Philipsburg kikötôjébe, hogy kivizsgáljam a helyzetet. Nem áll szándékomban vak eszközzé válni a kezükben.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "Harminc darab hideg acél van a ládában! Megálljak most, vagy gyûjtsek még több lôfegyvert, töltetet és bájitalt?";
				link.l1 = "Ennyi elég lesz!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "Nem, tovább kell töltenem ezt a ládát.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "Töltsd meg Fadey ládájának tartalmával, és vidd el a felesleget."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "Harminc darab hideg acél még nem gyûlt össze! Többet kellene hoznom.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Lezárom a ládát, és tervet készítek, hogy becsempészem az ültetvényre.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "Menj, chaaarge! Huurah!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "Minden szükséges anyag elkészült, azonnal el kell kezdenünk a hosszú csónakok építését.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "Nincs olyan tapasztalt ácsom, aki képes lenne elvégezni a munkát. Egy tisztet kellene kijelölnöm erre a feladatra.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Nincs elég anyag, legalább 20 csomag deszkára és 10 bála bôrre van szükségünk.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "Minden készen áll a robbanásra!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "Legalább 20 emberre van szükségem a puskapor szállításához.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Nincs elég puskapor, legalább 300-ra van szükség.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "Ez egy ajtó volt?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "Igen, az! Látogatóink vannak... Jan?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "Én és "+sTemp+" már régóta együtt vagyunk, és a kötelékeink erôsebbek, mint bármilyen templomi fogadalom, de szeretném, ha mindketten emlékeznénk erre a pillanatra. Ezért el kell döntenem, hogy hol kérjem meg a kezét:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Isla Tessoro - ez a sziget sokat jelent a történetünkben. Azt hiszem, nincs is jobb hely - a Sabu Matila-öböl elbûvölô naplementében!";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "Tortuga - korunk szabadságának szimbóluma, és a kilátás a világítótoronyból a Tortu-szorosra méltó bármelyik festô ecsetjéhez!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "Jamaika - annyi minden van benne! És a hajnalban gyönyörködni a Portland Cove-ban - így képzelem el a földi Paradicsomot.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "De ezt nem tehetjük meg az egyházi ünnepélyesség nélkül - mindennek minden kánon szerint kell történnie, hogy apám kénytelen legyen elfogadni a választásomat. Szükségem lesz tehát egy papra, és Benoit apáton kívül nem látok senkit, aki méltó lenne erre a posztra. Ô apám régi barátja, és tôle kezdôdtek kalandjaim az Újvilágban. Azt hiszem, beleegyezik, hogy megtiszteljen engem ezzel a feladattal.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "De ezt nem tehetjük meg az egyházi ünnepélyesség nélkül - mindennek minden kánon szerint kell történnie, hogy apám kénytelen legyen elfogadni a választásomat. Szükségem lesz tehát egy papra, és Benoit apáton kívül nem látok senkit, aki méltó lenne erre a posztra. Ô apám régi barátja, és tôle kezdôdtek kalandjaim az Újvilágban. Azt hiszem, beleegyezik, hogy megtiszteljen engem ezzel a feladattal.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "De ezt nem tehetjük meg az egyházi ünnepélyesség nélkül - mindennek minden kánon szerint kell történnie, hogy apám kénytelen legyen elfogadni a választásomat. Szükségem lesz tehát egy papra, és Benoit apáton kívül nem látok senkit, aki méltó lenne erre a posztra. Ô apám régi barátja, és tôle kezdôdtek kalandjaim az Újvilágban. Azt hiszem, beleegyezik, hogy megtiszteljen engem ezzel a feladattal.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Nos, ez megtörténhet az emberiség ünnepélyessége nélkül is. Bár ezt inkább a "+sTemp+" egy kicsit késôbb beszélném meg.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "Nos, én készen állok!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "Minden készen áll!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "A szükséges árut és érmét még nem gyûjtöttük össze!";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    DialogExit();
	locCameraSleep(false); //boal
}
