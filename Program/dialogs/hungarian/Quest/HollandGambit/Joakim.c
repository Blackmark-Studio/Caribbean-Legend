// Жоаким Мерриман - португальский сумрачный гений
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Jó napot, uram! Joachim Merriman doktor vagyok. Van szerencsém megszólítani a " + GetFullName(pchar) + "kapitányt?";
					link.l1 = "Igen, én vagyok. Honnan az ördögbôl tudja a nevem? Nem emlékszem, hogy már találkoztunk volna.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Örülök, hogy látom, kapitány. Látszik a ruganyos lépésén, hogy nagyon boldoggá fog tenni. Nálad van Yum Cimil koponyája?";
					link.l1 = "Nálam van a koponya, amirôl beszélt. Úgy pattog az energiától, mint egy dübörgô kemence.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Van még valami mondanivalója, kapitány?";
				link.l1 = "Nem, Senor Merriman. Elmegyek...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Jó napot, uram! Joachim Merriman doktor vagyok. Van szerencsém megszólítani a " + GetFullName(pchar) + "kapitányt?";
					link.l1 = "Igen, én vagyok. Honnan az ördögbôl tudja a nevem? Nem emlékszem, hogy már találkoztunk volna.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "Örülök, hogy látom, kapitány. Látszik a ruganyos lépésén, hogy nagyon boldoggá fog tenni. Nálad van Yum Cimil koponyája?";
					link.l1 = "Nálam van a koponya, amirôl beszélt. Úgy pattog az energiától, mint egy dübörgô kemence.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Van még valami hozzáfûznivalója, kapitány?";
				link.l1 = "Nem, doktor Merriman. Elmegyek.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Szép napot. Akar tôlem valamit?";
			link.l1 = "Nem, sajnálom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "Ha Dr. Merrimanhoz jött, ô nincs itt. Már nem lakik itt.";
			link.l1 = "Értem, értem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "Ha Dr. Merrimanhoz jött, akkor azt kell mondanom, hogy nincs itthon. Jelenleg úton van, és nem tudom, mikor tér vissza.";
			link.l1 = "Értem, értem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "Ha Dr. Merrimanhoz jött, ô nincs itt. Már nem lakik itt.";
			link.l1 = "Értem, értem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Az ön ügyei nem olyan magánügyek, mint ahogyan azt ön gondolja, kapitány! De ne ijedjen meg, van egy ajánlatom az ön számára! Én a tudomány embere vagyok, afféle természetfilozófus, aki a Spanyol-fôsziget és a Nyugat-Indiai-szigetek indiai pogányainak lenyûgözô kultúráját tanulmányozza. Lenne olyan kedves elkísérni a házamhoz, és a nappalimban megbeszélni a potenciálisan igen jövedelmezô részleteket?";
			link.l1 = "Kíváncsiságom és figyelmem az öné. Mutassa az utat.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "Ezt nem fogja visszautasítani, uram! A házam nincs messze innen. Kövessenek!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Itt beszélgethetünk a kíváncsiskodó fülek félelme nélkül. Ön nemrégiben meglátogatta a szomszédomat, Solomon Shneurt. Épp arra jártam, és - bocsásson meg, kapitány - véletlenül elkaptam néhány részletet a Solomonnal folytatott beszélgetésébôl. Annyira lenyûgözô volt, hogy végig kellett hallgatnom az egészet!";
			link.l1 = "Egy hallgatózó, aki fél a többi hallgatótól, mi?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Na, na, kapitány! Ez egyáltalán nem így van! Solomon a szomszédom, és gyakran meglátogat. Jó barátok vagyunk a vallási különbözôségeink ellenére! Tudok a kalandjairól... mint mindenki más Willemstadban! Solomon reggel, délben és este mindenkinek, aki meghallgatja, hirdeti a gondjait. De elég ebbôl. Az öreg zsidó bizonyára mesélt már neked egy régi jáde koponyáról, amelyet az aranyával együtt egy ismeretlen szigeten rejteget. Mesélt neked róla?";
			link.l1 = "Egy koponyáról beszélt, de azt nem említette, hogy jáde lenne belôle. Azt is mondta, hogy a nagyapja koponyája, az igazat megvallva azt hittem, hogy vagy valami kabbalisztikus rémség, vagy az öreg koboldnak van néhány denevér a harangtoronyban.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "Nem, kapitány, Solomon teljesen épelméjû, csak különc. A koponya létezik. Ez egy ôsi indiai kincs, Yum Cimil jáde koponyája! Fogalmam sincs, hogy a vén zsidó hogyan kaparintotta meg a karmaival. Már fél életemben kerestem\nKeresem azt a szigetet, ahol Salamon elrejtette a családja pénzét. A koponya biztosan ott van a ládájában. Ha átadja nekem azt a jáde koponyát, fizetek magának félmillió pezót.";
			link.l1 = "Fél ezer? Az aligha éri meg az idômet... várj egy percet... azt mondtad, hogy Félmillió nyolcrészes ezüst?! Most viccelsz velem? Életemben nem láttam még ennyi pénzt egy helyen!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "Maga még mindig fiatalember, kapitány... Szóval, benne vagy? Add ide a jáde koponyát, és én adok neked ötszázezer nyolcezret cserébe. Megegyeztünk?";
			link.l1 = "Ha, egy vagyont egy öreg koponyáért? Persze, hogy benne vagyok.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Pompás. Mindig öröm olyan emberrel dolgozni, aki ért a profithoz. Itt találnak a házamban, ha szükségük van rám. Sok szerencsét!";
			link.l1 = "Köszönöm, Dr. Merriman. Nem akarom sokáig váratni.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "Ó, igen! Határozottan igaza van az erejét illetôen... De elég a szavakból, hadd lássam, remegek a türelmetlenségtôl.";
			link.l1 = "Tessék, kérem, vegye el. Remélem, nem tévedtem?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ah, hihetetlen! Igen, ez az. Kitûnô, kapitány, nagyon kitûnô! Végre! Végre nálam van! Annyi éven át vártam erre a pillanatra!";
			link.l1 = "Mi van a pénzzel, amit ígért, Dr. Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "Ó, igen, persze! Félmillió nyolcrészes ezüst. Vegye el, megdolgozott érte.";
			link.l1 = "Öröm volt önnel üzletelni. Nehéz elhinni, hogy egy ilyen kis dolog ennyit érhet...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Apróság? Nem tudod, mirôl beszélsz. Ez... bah, a te filiszteus elméd aligha tudja felfogni a hihetetlen erô nagyságát, ami e drága koponya mögött rejlik. Az igazat megvallva, amúgy sincs idôm rá\nKöszönöm, kapitány, amit tett. Most itt az ideje, hogy búcsút vegyünk. Mennem kell.";
			link.l1 = "Viszlát, Dr. Merriman. Talán még találkozunk.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Itt beszélgethetünk, kapitány. Tudom, hogy ön Abigail Shneur, a szomszédom, Solomon lányának bizalmas munkatársa. Az ön hajóján elhajózott a szeretôjéhez... de ez igazából nem számít.";
			link.l1 = "Mire akar kilyukadni, doktor úr?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "Ha ismeri Salomont, akkor bizonyára ismeri a történetét a hajótörésrôl és az elveszett kincseirôl, amelyeket egy ismeretlen szigeten rejtegetett. Ezt a történetet már mindenkinek elmondta Willemstadban.";
			link.l1 = "Miért feltételezi, hogy én hallottam errôl valamit, és miért érdekel az öreg zsidó szerencsétlensége?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Nem kedveled Salamont? Biztosíthatom, hogy ô csak egy ártalmatlan öreg különc. Felejtsd el ôt. Beszéljünk inkább az üzletrôl\nMég több hosszú beszélgetést folytattam Salomonnal. El sem tudod képzelni, mit éreztem, amikor megtudtam, hogy ez az öreg zsidó a tulajdonosa egy ôsi, felbecsülhetetlen értékû mûkincsnek, amit évek óta keresek! Az ôrült vénember a szánalmas pénzével együtt elrejtette valami szigeten, és még a helyére sem emlékszik\nSzükségem van erre a leletre. Hozd el nekem, és fizetek neked Félmillió nyolcrészes ezüstt.";
			link.l1 = "Félmillió nyolcrészes ezüstt? Biztos csak viccel, doktor úr. Soha életemben nem láttam ennyi pénzt egy helyen!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "Maga még mindig fiatalember. Szóval, benne van? Adja ide a koponyát, én pedig ötszázezer nyolcezrest adok cserébe. Ráadásul elviheted Salamon pénzét is. Az öregember szavai szerint körülbelül kétszázezer pezó lehet... Tehát összesen hétszázezer nyolcezret kapsz. Megegyeztünk, kapitány?";
			link.l1 = "Üssön meg! Persze, hogy megegyeztünk! De hogyan találjam meg ezt a szigetet?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Beszélj Abigail-lel. Talán emlékszik valamire. Kérdezd meg Salomont. Látod, ha tudtam volna, hol találom a szigetet, nem kértem volna a segítségedet.";
			link.l1 = "Értem. Elnézést a hülye kérdésemért. Most pedig meg kell találnunk ezt a szigetet. Csak gyôzôdj meg róla, hogy a fizetségemmel várlak.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Pontosan. Örülök, hogy megértjük egymást, kapitány. Sok szerencsét a kereséshez. Engem mindig megtalál itt a házamban.";
			link.l1 = "Nem akarom sokáig váratni, Dr. Merriman. Viszontlátásra!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "Yesssssss. Az áldozati kövek vörösek ellenségeim vérétôl! Yum Cimil megadta nekem a hatalmát, hogy parancsoljak a holtaknak! Ezzel a hatalommal hamarosan uralkodni fogok az élôk felett!";
			link.l1 = "Nagyon melodramatikus, Merriman. Mit tervezel a két lábon járó hullákból álló seregeddel? Cézárt játszol, és megpróbálod meghódítani a világot?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Hallgass, te bolond! Azt várod, hogy egy monológban fedjem fel a titkos tervemet?! Nos, nem látom okát, hogy ne tegyem, nem fogod túlélni ezt a találkozást! Az élôhalott légióim elôbb elfoglalják a Karib-tenger összes sötét barlangját és tömlöcét. Az elôôrseim minden faluban ott lesznek, és a jelemre várnak. És amikor eljön az idô, két lábon járó hulláim kivonulnak, és beborítják az élôk földjét!\nKár, hogy ezt nem éred meg, te szánalmas kis jóságos, te leendô fôhôs! Beléptél a szentélyembe - és nem fogsz onnan élve kijutni! Én vezetem a sötétség seregét!";
			link.l1 = "Figyelj haver, te nem vezetsz semmit, csak Jacket és a szart, és Jack épp most hagyta el a várost.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "Oh ho ho! Ki merészelsz hívni engem és a csontváz szolgáimat?! Akkor nézzétek meg, ki vagyok valójában, és reszkessetek a félelemtôl!";
			link.l1 = "Gyertek, kapjatok el.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "Ahhh! Édes Jézusom!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "Most már érted, ki áll elôtted, te nyávogó féreg?! Van egy csontom, amit ki kell piszkálnom veled! Maga Yum Cimil kedvez nekem! Elnyelem a lelkedet!";
			link.l1 = "Jól van, csontfejû. Táncoljunk.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Maga egy "+ GetSexPhrase("tolvaj, uram! Ôrök, vigyétek","tolvaj, lány! Ôrök, vigyétek") +"!!!", "Csak nézd meg ezt! Amint hátat fordítottam, úgy döntöttél, hogy megnézed a mellkasomat! Vigyétek a tolvajt!!!", "Ôrség! Rablás! Elkapni a tolvajt!!!");
			link.l1 = "A francba!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
