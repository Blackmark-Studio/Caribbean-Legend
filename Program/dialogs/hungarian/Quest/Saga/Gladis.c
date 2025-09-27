// Глэдис МакАртур - приемная мать Элен
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
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ah, kapitány! Tudja, mindent elmondtam Helennek. El sem tudja képzelni, mekkora teher esett le a fejemrôl!";
				link.l1 = "Mindent jól csinált, Miss McArthur. A lánynak tudnia kell az igazat. És én miatta vagyok itt.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Üdvözlet, "+pchar.name+"! Örülök, hogy látlak! Kérsz egy kis rumot?";
				link.l1 = "Köszönöm, Miss McArthur, de most túl elfoglalt vagyok.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "Mit akar, uram?";
			link.l1 = "Maga Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Igen, én vagyok. Nem emlékszem magára, fiatalember. Elmagyarázná, hogy mit akar tôlem?";
			link.l1 = "Érdekel a lánya eltûnésének története, Miss McArthur. Mibôl gondolta, hogy eltûnt? Úgy hallottam, hogy Helennek nagyon ügyes csapata volt...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ah, teljesen biztos vagyok benne! Nézze, a néhai férjem halálának évfordulója öt nappal ezelôtt volt. Helen szerette az apját, és soha nem hagyta volna ki ezt a dátumot. Csak néhány napra ment el, hogy átvegyen egy rakomány vörös fát a barátságos miskitóktól.\nAz indiánok tisztelik és féltik a mi védnökünket, Jan Svensont, soha nem bántanák. Svenson úr már beszélt velük. A fát még aznap megrakodták. Helent azóta sem látta senki.";
			link.l1 = "Talán a kalózok támadták meg?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Ostobaság! Biztosan tudjátok már, hogy Svenson úr az öt kalózbáró egyike és a Parti Testvérek Tanácsának tagja. Az ô engedélye nélkül egyetlen kalóz sem vadászhat itt. Bár lehet, hogy egy újonc...";
			link.l1 = "És mi a helyzet a spanyolokkal? Lehet, hogy egy spanyol ôrjárattal került szembe?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Nem értek a politikához, de azt mondják, hogy a helyi arany- és ezüstbányák teljesen elpusztultak, nem sok kincs maradt, amiért nemes hidalgók életét kockáztatnák. Szóval ôk ritka vendégek itt. Ráadásul az indiánok ellenségesen viszonyulnak hozzájuk.\nEgy véletlen találkozás egy spanyol ôrjárattal nem végzôdhetett rosszul Helen számára, az ô szemszögükbôl nézve semmi törvénytelent nem tett. 'Rainbow' holland zászló alatt hajózott, és Helen minden papírja rendben volt, beleértve a kereskedelmi engedélyt is.";
			link.l1 = "Történt valami különleges a legutóbbi útja elôtt? Esetleg valami furcsa esemény, amirôl lemaradt?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Á, ne! Hála Istennek, mi itt békésen élünk. Néhány hete azonban Helen kapott egy levelet egy másik kéretlen hódolótól, aki randevúért könyörgött. Helen csinos lány, de nem gazdag.\nSzóval rengeteg hódolója van, bár egyik sem tetszik neki, és nem akar férjhez menni. Sok embert átvert már így is. Olyan könnyelmû, mint amilyen az anyja volt!";
			link.l1 = "Maga nem úgy néz ki, mint az a fajta nô, Miss McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "Mi az? - Nem... Á, mindegy, megszakad a szívem. Mit is mondtam? Á, igen, a levél. Egyébként azt a levelet Jimmy Higgins írta. Ô Jackman egyik embere, és Maroon Townban él. Gyakran meglátogatja a városunkat. Jackman is kalózbáró, de Svenson úr nem kedveli ôt, nem tudom miért.";
			link.l1 = "És Helen?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Ó, ô hangosan nevetett. Egy nappal korábban kapott egy leánykérést egy angol korvett kapitányától, és még ôt is visszautasította. És most ez a közönséges csónakos egy kalóz öreg teknôjébôl... Szó sem lehet róla, Sean McArthur lánya impozánsabb férjet követel!";
			link.l1 = "És hogy hívták azt az angol kapitányt?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Ó, honnan is tudhatnám? Az igazi úriemberek ritka vendégek itt. Sajnálom, nem akartalak megbántani. Kérdezze meg Higgins-t. Biztos emlékszik a nevére. Jimmy megpróbált párbajozni a kapitánnyal Helenért. A cimborái alig tudták megakadályozni ebben. De mindketten elhagyták Blueweldet néhány nappal Helen elhajózása elôtt.";
			link.l1 = "Nos, köszönöm a történetet. Megpróbálom megtalálni a szerelmedet. Ha megtudok valamit, elmondom önnek vagy Svenson úrnak. Remélem, hogy élve és épségben találom meg a lányát.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Meg fogja keresni? Isten legyen veled, vezessen és erôsítse meg a kezed! Imádkozni fogok önökért! Mondja meg a nevét, becsületes ember?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". Remélem, hamarosan jó hírekkel térek vissza, Miss McArthur. Viszontlátásra!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Van valami új információja szegény lányomról, "+pchar.name+"?";
			link.l1 = "Sajnálom, Miss McArthur, hogy eddig semmi újat nem tudok mondani, de ne essen kétségbe. Folytatom a keresést. A rossz hírek hiánya önmagában jó hír is.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Elkésett, kapitány. Szegény lányom holttestét Antigua partjainál találták meg. Uram, hogy még meg is kínozták a halála elôtt! Nem sikerült megóvnom az én gyönyörû lányomat...";
			link.l1 = "Sajnálom. Nem tehettem semmit...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ah, fiatalember, kérem, hagyjon békén a bánatommal...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Nem is tudom, hogyan köszönjem meg, kapitány úr, hogy megmentette a lányomat. Mindent elmondott nekem, és csodálom a bátorságát és a becsületét. Tessék, fogd ezeket az arany dublónokat. Nem sok, de ôszintén ajánlom fel. És eszedbe se jusson visszautasítani!";
			link.l1 = "Rendben, Gladys, nem fogom. De a lányát nem érmékért mentettem meg, és remélem, ezt tudja.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Tartsa meg ezt a pénzt magának, Gladys. Neked nagyobb szükséged van rá, mint nekem.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Örülök, hogy valahogy meghálálhattam a megtisztelô tettét. Az otthonom ajtajai mindig nyitva állnak elôtted. Helen és én bármikor szívesen látjuk.";
			link.l1 = "Köszönöm, Miss McArthur. Meglátogatom önt és Helent, ha lesz rá alkalom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ah, kérem... Csak meg akartam hálálni a megtisztelô tettét. Tudja, hogy az otthonom ajtaja mindig nyitva áll ön elôtt. Helen és én bármikor szívesen látjuk.";
			link.l1 = "Köszönöm, Miss McArthur. Meglátogatom önt és Helent, ha lesz rá alkalom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Kapitány, mindig szívesen látjuk az otthonunkban! Helen miatt jött? Attól tartok, bezárkózott a szobájába - biztos kimerült az elmúlt napokban. Ne aggódjon, néha megesik vele.";
				link.l1 = "Tényleg? Igen. Biztos, hogy jól van?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ah, Monsieur de Maure! Mindig örülök, ha a lányom megmentôjét a házamban látom. Szeretné látni Helent? Fent van a szobájában. A 'Rainbow' és a csodálatos megmentése után kerüli a kimozdulást. Ez az elsô alkalom, hogy ilyen zavart állapotban látom...";
			link.l1 = "Köszönöm, Miss McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ah, Monsieur de Maure! Mindig örülök, ha a lányom megmentôjét a házamban látom. Szeretné látni Helent?";
			link.l1 = "Nem. Csak néhány kérdést szeretnék feltenni, és nagyon bízom az ôszinteségében. Helen biztonsága függ ettôl. Ismerôs önnek ez a gyûrû?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Te jó ég! Ez... az apja gyûrûje!";
			link.l1 = "Mr. McArthuré?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "Nem. Helen a mostohalányunk, de ô ezt nem tudja, a szülei meghaltak, ezért úgy döntöttem, hogy magamhoz veszem, mint gyermekemet. Sean örökbe fogadta, de még ô sem tudta, hogy nem az én lányom.";
			link.l1 = "Akkor kik az igazi szülei?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "Tudom, hogy az apja egy kalóz volt, akit úgy hívtak 'Hentes' a fregatton 'Neptun'. Csak kétszer láttam. Az anyja pedig egy gyönyörû fiatal nô volt, vörös hajjal, férfiruhában. Nagyjából ennyit tudok róla elmondani, kivéve, hogy rossz anya volt.\nEgy ilyen gyereket soha nem bíznék idegenekre. Mindketten tragikusan haltak meg. A beígért futár pedig húsz évvel késôbb jelentkezett, és kiderült, hogy te vagy az. Mészáros küldött téged? Életben van?";
			link.l1 = "Nyugodjon meg, Miss Gladys! Semmi okunk sincs arra gyanakodni, hogy Mészáros feltámadt, bár maga a második, akinek ez az ötlete támadt. Nemrég találkoztam egy férfival, akinek meg kellett volna mutatnia ezt a gyûrût...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "";
			link.l1 = "Egy egyszerû incidens miatt nem tudta ezt idôben megtenni, és egész életében szenvedett, mert megszegte a kapitánya utolsó parancsát. Nemrég meghalt, és... nos, elég a szomorú hírekbôl. Mondja, Gladys, Helen édesanyja nem hagyott valamilyen jelképet gyermeke emlékére? Talán valami apróságot?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Egy régi térkép egy furcsa darabját hagyta rám. Viccelôdött, hogy ez volt az öröksége. Mire lehet jó az a darab papír? Azt hiszem, ez csak egy rossz vicc volt. Túlságosan izgatott volt, és egy kicsit elment az esze. De megôriztem ezt 'ajándék'.\nKi tudja... Ha akarod, odaadom neked, ha megígéred, hogy egyszer elmeséled az egész történetet.";
			link.l1 = "Természetesen, Miss McArthur. Egy ideig magammal viszem ezt az apróságot. Beszélnem kell Mr. Svensonnal.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Megint segített nekünk, Monsieur de Maure! És fogalmam sincs, hogyan köszönjem meg. Legalább a férjem pisztolyát vegye el. Mindig büszke volt rá, és azt mondta, hogy nagyon ritka. Már régóta itt hever. Hadd szolgáljon téged! Vedd el, vedd el!";
			link.l1 = "Köszönöm, Gladys. Ez a pisztoly tényleg kiváló. Köszönöm és viszlát.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Ez a pisztoly szolgáljon Helent. Van elég fegyverem.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "De miért utasítod vissza az ajándékaimat? Felbosszantasz...";
			link.l1 = "Azt hiszem, most már képes leszek boldoggá tenni téged. Visszaadom az aranyat, amit a futárnak kellett volna átadnia neked, hogy méltó módon megôrizze Mészáros kapitány lányát. Persze, ezek a dublonok nem fogják meghálálni minden szeretetedet és hûségedet, de mindenképpen téged illetnek. Azt tehetsz velük, amit csak akarsz.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ah, kapitány! Nem tudom, mit mondjak... El sem tudtam képzelni, hogy ilyen... tiszteletreméltó emberek egyáltalán léteznek! Menj a lányomhoz és mondd el neki a jó hírt!";
			link.l1 = "Már úton vagyok, Miss McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Ez most komoly? Hogy érti ezt?";
			link.l1 = "Svenson úr kérésének megfelelôen Helent a hajómon fogom alkalmazni tisztként. Nagy veszélyben van. Helennek szilárd védelemre lesz szüksége, amíg Jan és én ezt az ügyet intézzük. Remélem, hogy képes leszek biztosítani ezt a védelmet.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ah, ez nagyon jó! Magamtól nem merném ezt kérni. Ez lesz a legjobb védelem a lányom számára. Helen nagyon fog örülni, hogy újra hajózhat!";
			link.l1 = "Köszönöm a bókját, Miss McArthur. És most meg kell látogatnom a mostohalányát.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "Ó, Istenem! Az én kislányom!";
			link.l1 = "Gladys, nem tudod, hogy kopogni kell?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Ó, bocsássanak meg, fiatalok! Elmegyek! Helen, ne feledd, mit mondtam neked!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "Azt hiszem, ezúttal csak túlhajszolta magát. Mindent elmondott nekem, kapitány! Köszönöm, hogy tegnap segítettél neki új hajót választani!";
			link.l1 = "Helen, emlékezz arra, amit mondtam! Hm, szívesen. Viszlát, Mrs. MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
