// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Várj, szépfiú! Azt hiszem, beszélnünk kellene.";
			link.l1 = "Ismerem magát? Egyébként is, mindig van pár extra órám egy hölgynek.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Még ne tervezzen semmit, kapitány. Keressen magának egy fiatalabb, bolondos kinézetû lányt néhány extra órára. Nekem dolgom van magával. Valójában házas vagyok. A férjem neve Nathaniel Hawk.";
			link.l1 = "Ez nem semmi! Szóval maga biztos az a... Dannie Hawk, akit Svenson úr említett.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Hús-vér testben. Igen, tisztában vagyok vele, hogy az Erdei Ördög nem tart sokra, az érzés kölcsönös, de figyelmeztetnie kellett, hogy nem csak azért hordom a szablyámat, mert szép. Szóval, térj a lényegre, fiam!\nEgy ideje már követem Svensont és a látogatóit, mert ô volt az, aki a férjemet a dzsungelbe küldte meghalni. Azt hittem, hogy Jackmannel dolgozik, de most már látom, hogy nem. A beszélgetésük alatt az ablak alatt bújtam el. Nem tudtam mindent kihallgatni, de sok hasznos információt megtudtam.\nTényleg hajlandó vagy megtalálni a férjemet, és szétrúgni Jackman seggét? Vagy csak ócska dumát mondtál?";
			link.l1 = "A hallgatózás rossz dolog, Madame Hawk. De megbocsátok, ha tisztelettudóbban beszél velem. Sólyom keresése vagy sem, ez csak az én gondom. Beszéljen, ha van valami hasznos mondanivalója, vagy hagyjon békén, ha nincs. Nem kérem kétszer.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A-ha, micsoda forrófejû! Ugyan már, kapitány... A temperamentumom nem igazán teszi kényelmessé, az biztos. Látom, hogy nem vagy gyáva, és tudod, mit érsz. Szóval... ismerkedjünk meg egymással. Ígérem, hogy óvatosan fogok bánni azzal, amit mondok neked. Szükségem van rád és neked is szükséged van rám. Közösek a céljaink. Vegyél be a csapatodba és nem fogod megbánni. Jóhiszemûen és hûségesen szolgállak, amíg meg nem találjuk Nathant, a szavamat adom.";
			link.l1 = "Tekintsd magad elfogadottnak... Dannie. Svenson mondta, hogy már keresi a férjét. Találtál már valami érdekeset?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Nem sokat, de eleget ahhoz, hogy Jackmant hazugsággal vádoljuk. A szemétláda azt mondta, hogy a bánya ôrei, azok, akikkel Nathanem szembenézett, nem ejtenek foglyokat. És bár igaz, hogy senki sem látta a férjem holttestét az öbölben, hogyan is láthatták volna, hiszen ôt valóban fogolyként vitték a bányába. Kígyószem, a miskitók sámánja talált rá ott.\nÔ szervezte meg a szökését is. De hogy hol van most a férjem, az ismeretlen marad. A sámán motyogott valamit valami Kukulcanról, aki megette ôt, de én nem értettem semmit. Különben is, a rézbôrû elég világossá tette, hogy a fehér nôk számára csak viccnek számítanak. Beszélned kellene vele, talán beszélgetni fog vele.";
			link.l1 = "Ez legalább valami! Az ilyen hírek boldogabbá tesznek. Hol találom ezt az indiánt?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Van egy falu a dzsungel mélyén. Az Amatique-öbölben kell partra szállnunk, és nyugatra kell mennünk a dzsungelben. Megmutatom az utat, ha nem találod meg magad. A falutól nem messze található egy kôbálvány, amit a vademberek istenként tisztelnek. Már többször jártam ott. Igazából semmi különös. Csak egy egyszerû, mohával borított kô.";
			link.l1 = "Érdekes. Rendben, menjünk. Beszélünk a sámánnal, és meglátjuk, mi lesz a következô lépés. Készen állsz?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Persze! Természetesen, készen állok. Amióta elhagytam Maroon Townt, állandóan utazom. Emellett nem akarok csak egy újabb utasod lenni.";
			link.l1 = "Nem akarok csak egy egyszerû utas lenni. Menjünk a hajómra.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"! Gyerünk, gyerünk! Megmutatom a kôbálványt, amirôl az indián sámán beszélt. Csak egy szokásos kôoszlop. Gyerünk, menjünk!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Hé! Nézd meg, ez csak egy kôszobor. Semmi különös...";
			link.l1 = "Értem... Bár a tetején lévô alak egy kicsit baljós, nem gondolod? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "Minden indiai szobor ijesztô és gonosz kinézetû. Láttam már hasonlót korábban. Mind egyforma. Mindegy, menjünk, a falu a közelben van!";
			link.l1 = "Gyerünk!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "Szóval, mit mondasz, "+pchar.name+"? Mit mondott neked az a rézbôrû hasbeszélô? Értettél valamit a filozofikus szavaiból?";
			link.l1 = "Megint hallgatóztál, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Hát... egy kicsit. Tudod, mi nôk már csak ilyenek vagyunk. De meg kell értened - én csak a férjem miatt aggódom. Igazából szeretem ôt. Szóval mi van, ha hallgatózom? Egyébként, találtál valami hasznosat?";
			link.l1 = "Próbálok gondolkodni... nem volt könnyû megérteni Kígyószemet. Úgy tûnik azonban, hogy a bálvány, amit a faluba vezetô úton láttunk, valamiféle mágikus portál, ami képes teleportálni az embereket.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Ne nézz így rám. Nem az én ötletem, és eddig nem is volt gond a fejemmel. Azt kérdezted, hogy mit mondott a sámán, úgyhogy elmondom neked.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Kérem, bocsásson meg. Nem fogok többé így nézni rád. Menj csak.";
			link.l1 = "Azt mondta, hogy amikor Nathant majdnem elkapták az üldözôi, az indián megmutatta neki a szobrot, hogy megmentse, Kukulkánnak nevezte, és azt mondta, hogy az élve megette Nathant, és kiköpte valahol. Leegyszerûsítve úgy tûnik, hogy Nathant a szobor teleportálta.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Istenem, mi a... Én és Nathan már voltunk hasonló zûrzavarban korábban, és most megint ez történik. Volt elég kalandunk azzal a maja mágiával teli indiai templommal...";
			link.l1 = "Mit mondtál?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Á, semmiség, "+pchar.name+", nem számít. Csak emlékek a felhevült fiatalságomból. De hogy volt képes Nathan erre? Mármint teleportálni? Az elôbb voltunk a bálvány közelében, körbejártam, megérintettem... ez csak egy kô!";
			link.l1 = "Kígyószem azt mondta, hogy a bálvány éjfélkor kel életre. Csak akkor kezd arany színben ragyogni, amikor Kukulcan szelleme belekerül. Ez az az idô, amikor nem szabad megérinteni. Vagy éppen ellenkezôleg...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Hátborzongató... Most mi lesz? Várjunk éjfélig, és akkor menjünk a dzsungelbe?";
			link.l1 = "Nem. A sámán azt mondta, hogy a bálvány nem csak teleportálja az embereket, hanem meg is eszi az életüket. Ha jól értettem, úgy értettem, hogy elszívja az életerejüket. Kígyószem már háromszor ment át ezeken a szobrokon, és minden teleportálás után valami egyedi bájitallal gyógyította magát.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Kérte tôle ezt a bájitalt?";
			link.l1 = "Persze. De egyrészt már csak három flaska maradt, másrészt három amulettet kért cserébe.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Mi lenne, ha ezt a bájital nélkül csinálnád? Menjünk a szoborhoz éjszaka, és érintsük meg...";
			link.l1 = "Túl kockázatos. Elismerem, hogy az indiánnak kicsit elment az esze, és átver minket, de nem tûnik pszichopatának, úgyhogy elhiszem, hogy igazat mond. Emlékszem, hogy mesélt nekem valamit az indián mágiáról... Kételkedik a létezésében?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Igen, kételkedtem. Nem kételkedem benne, mert a saját szememmel láttam. Szóval, azt hiszem, igazad van, nincs értelme kockáztatni.";
			link.l1 = "Pontosan. Ezért elôbb megkeressük az amuletteket, aztán megszerezzük azt a csodálatos bájitalt a sámántól, és elmegyünk a szoborhoz. Én megyek. Egyedül.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Miért is? És mi lesz velem?";
			link.l1 = "A hajómon maradsz, és te leszel a fônök, amíg én távol vagyok. Meg se próbálj vitatkozni, Dannie. Csak három lombik van a bájitalból. Nem tudni, hová vezet a kapu, ha esetleg a sámánnak igaza van, és ez a dolog tényleg mûködik. Talán még Nathant sem fogom ott megtalálni.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Pont olyan vagy, mint Nathan. Minden ember egyforma... Rendben, egyetértek.";
			link.l1 = "Jó, hogy megértjük egymást. Menjünk, meg kell találnunk az amuletteket.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "És akkor mi van? Megszerezted a bájitalokat?";
			link.l1 = "Igen. Megkaptam a bájitalokat és néhány utasítást. Már csak egy dolgunk van, hogy éjfélkor odamegyünk a bálványhoz és megérintjük.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Félsz?";
			link.l1 = "Igen. Attól félek, hogy a sámánról kiderülhet, hogy csak egy ôrült, és nem fog megtörténni a teleportálás.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Nos, nos, nos... Nem félsz igazán? Egy kicsit sem?";
			link.l1 = "Dannie, ne erôltesd... Ha tényleg tudni akarod, akkor persze, nem vagyok túl magabiztos, be kell vallanom.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Veled megyek.";
			link.l1 = "Megint vitatkozni fogsz? Azt hittem, megegyeztünk...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Félreértettél. Csak a közeledben maradok. Nekem kell gondoskodnom arról, hogy a szobor mûködjön... vagy ne mûködjön.";
			link.l1 = "Nincs ellenvetésem. De eszedbe se jusson követni engem, hátha a szobor 'megeszi' amat. Hallasz engem?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Igen, hallom. Megígérem, hogy nem követlek... Kapitány.";
			link.l1 = "Jó. Jó. És Dannie, úgy tûnik, hogy nem vagy olyan nagy ribanc, mint ahogy mondják.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Nem ismersz túl jól, "+pchar.name+". De errôl most ne beszéljünk.";
			link.l1 = "Ne beszéljünk... Nos, készüljünk fel az éjszakai kirándulásra!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Nézd, "+pchar.name+"! Esküszöm mindenre, ami szent, a szobor felett egy furcsa fény van!";
			link.l1 = "Úgy tûnik, hogy a sámán nem hazudott. És, ha a sötétség nem csal meg, a szobor teteje már nem is tûnik olyan kövesnek.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Pontosan... Úgy néz ki, mintha tiszta aranyból lenne! Hihetetlen!";
			link.l1 = "Eljött az idô, Dannie. Kívánj szerencsét, és szoríts nekem. Ne menj közel a bálványhoz! Maradj itt.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Sok szerencsét, "+pchar.name+". Reméljük, hogy ez mûködni fog... Elkészítetted már a sámánfôzetet?";
			link.l1 = "Igen, itt van nálam. Minden rendben lesz, Dannie. Nos, itt vagyok! (Nyomd meg a T-t a bálvány aktiválásához)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Bassza meg! Miféle szörnyeteg vagy te, az isten verje meg?! Baszd meg! Láttam már rosszabb teremtményeket is életemben, beleértve magát Van der Decken-t is! Most megkapod, amit kértél!";
			link.l1 = "(halványan)Dannie, várj! Hagyd abba! Azonnal!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(halványan) Van der Decken? Uh-ha-ha-ha-ha! Ez a féreg már kiszolgál engem! Most te jössz! Hajolj meg elôttem, hûséges szolgám! Te fogod vezetni a holtak seregét!";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A komancsok bájitalt használnak", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("Úgy érzed, hogy az egészséged helyreállt!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Menjetek el! Ez nem történhet meg most!";
			link.l1 = "(halványan)Dannie, várj! Hagyd abba! Azonnal!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Ah?! Mit mondtál?! Dannie?";
			link.l1 = "(halkan) Hagyd abba azonnal! Tartsd a szablyád! Hadd vegyem le ezt az izét!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "A francba, te szörnyeteg úgy beszélsz, mint... "+pchar.name+"?!";
			link.l1 = "(Halványan) Ó-ó... Ne is mondd!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "A francba, majdnem halálra ijesztettél! Olyan közel voltam hozzá, hogy levágjalak a szablyámmal!";
			link.l1 = "Láttam... és miért vagy ilyen tüzes, mi?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "Ez vagyok én... Ó, a szívem még mindig a mellkasomból dobog...";
			link.l1 = "Dannie, hol vagyunk most? Nem messze a miskitó falutól, igaz?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Hol máshol lehetnénk! Ez az a szobor, ami miatt eltûntél. Látványos volt! Erre egész életemben emlékezni fogok.";
			link.l1 = "Értem, azóta is itt vársz rám?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Mondd csak, mi mást kellett volna tennem? Miután a szobor megevett téged, csak remélni tudtam, hogy egy nap majd visszaköp téged. Különben is, Kígyószem azt mondta, hogy valószínûleg ez fog történni.\nA miskitókkal éltem, és minden nap figyeltem a bálványt. Miért beszélünk egyáltalán ilyen marhaságokról? Mondd meg nekem! Mi történt odakint? Hol voltál?";
			link.l1 = "Dannie, ez a történet túl hosszú, annyi mindent láttam... De hogy lekerüljön a lelkedrôl, elmondom, hogy megtaláltam Nátánielt!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Megtaláltad Nathaniel-t? Hol van? És hogy van?";
			link.l1 = "Nem fogok hazudni - életben van, de nagyon rosszul érzi magát. Nem volt nála a komancs bájital, és a bálvány minden egészségét elszívta. Valami öreg és törött hajó kabinjában fekszik az Elhagyott hajók különös szigetén. Engem is oda teleportáltak, tehát Kígyószemnek igaza volt!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Szegény Nathan... Hol van az az átkozott sziget? Hogy jutunk oda?! Csak a bálványon keresztül? Megpróbálok minden egyes gyógyitalt megvenni a Miskitótól, és még ma este odamegyek! Valahogy sikerülni fog...";
			link.l1 = "Hagyd abba! Várj! Nathan beteg, de nincs életveszélyben. Egy fiú vigyáz rá és eteti. Ha átmész a bálványon, tönkreteszed az egészségedet, és a Sziget nagyon veszélyes. Túl kockázatos!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "Akkor mit javasolsz? Hogy ne tegyünk semmit, amíg Nathan szenved vagy haldoklik?";
			link.l1 = "Ne hisztériázz! Elôször is, azt mondtam, hogy Nathan beteg, de nem haldoklik. Beszéltem vele. Másodszor, elhajózom a szigetre, és te velem jössz.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Tudod, hol van az a sziget?";
			link.l1 = "Persze, hogy megyek! Nemcsak Nathan-t találtam ott, hanem Shark Dodson-t is. Megkaptam a sziget hozzávetôleges koordinátáit és a vitorlázási irányt, hogy megkerüljem a szigetet körülvevô zátonyokat. És most visszamegyünk a hajómra, és elhajózunk Blueweld felé...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "Milyen célból? Miért nem hajózhatunk most egyenesen a szigetre?";
			link.l1 = "Dannie, meg kell szerveznem egy expedíciót. A Szigeten óriási az élelmiszerhiány, ezért annyi élelmiszert fogok vásárolni, amennyit csak tudok. Aztán ki kell választanom egy hajót, amivel odahajózhatok, nem minden hajó képes megkerülni a sziget zátonyait. És elôbb Svensonnal is szeretnék beszélni...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Nem fog sokáig tartani a felkészülés. A sziget nincs messze innen, Havannától északnyugatra van, keletre a Mexikói-öböltôl.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Rendben... akkor csináljuk. Megtaláltad Nathant, és ez a legfontosabb. Köszönöm! Rosszul érzi magát ott?";
			link.l1 = "Nos... beteg. Ráadásul depressziós és kétségbeesett. Hiányzol neki. És igen, Nathan megkért, hogy mondjam el, hogy nagyon szeret téged.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(törölget egy könnycseppet) Vén bolond! Soha nem hallgatott rám... "+pchar.name+", irány a hajód! A lehetô leggyorsabban oda akarok hajózni!";
			link.l1 = "Persze, Dannie. És mesélek neked a kalandjaimról. Gyerünk, menjünk!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Még sosem láttam ilyen helyet, mint ez. Az egész sziget hajókból áll!";
			link.l1 = "Már meséltem róla, Dannie...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "De most már a saját szememmel is láthatom. Egyébként mondd meg, hol találom Nathanielt?";
			link.l1 = "Az egyik hajóban van. De oda kell úsznod.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Nem érdekel. Mondd meg, hogyan jutok el a hajóhoz.";
			link.l1 = "Dannie, nyugodj meg. Te és Nathan már régóta vártok, szóval csak egy kicsit több türelemmel! Én majd elvezetlek hozzá, te magad sosem találod meg. Nem akarom, hogy összefussatok a Narwhalokkal vagy a Rivadókkal, mert akkor elkezdesz velük vitatkozni, és annak nem lesz jó vége.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Rendben, akkor menjünk. Majd én követlek.";
			link.l1 = "Ne felejtsd el, hogy sokat kell majd úsznunk.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "Semmi gond, meg tudom oldani.";
			link.l1 = "Örülök, hogy ezt hallom... Hamarosan találkozol a férjeddel!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! A francba! Szerelmem...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Jézusom, csak nézz magadra... Miért tetted ezt magaddal?!...(sírás) Soha nem hallgatsz rám, soha! Mondtam, hogy ne menj be abba a szelvába! De te mégis odamentél! Miért Nathan?!";
			link.l1 = "Dannie... Sajnálom. Nem volt más választásom, tudod jól...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Tudom! Ó, Istenem, drágám... mi történt veled! (könnyek között) Minden rendben van, drágám, minden rendben lesz... Én itt vagyok. Elviszünk a Miskitóhoz, a Kígyószemhez. "+sld.name+"  azt mondta, hogy a sámán meg tud majd gyógyítani. Van egy hajónk... Minden rendben lesz!";
			link.l1 = "Dannie, drágám... szerelmem! A jelenléted csak félig gyógyított meg. Oda megyünk, ahová mondod. Ha Kígyószemhez, akkor hozzá.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Pakold össze a holmidat. Ó, olyan hülye vagyok... Nincs mit összepakolni, csak üres üvegeket. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ...bocsáss meg nekem és Nathan-nek a jelenetért.";
			link.l1 = "Dannie! Mit bocsássak meg neked? Meggyulladt. Szégyelled az érzéseidet?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "Nem, nem szégyellem... Csak...";
			link.l1 = "Senki sem fog tudni errôl a jelenetrôl. Megígérem. És senki sem fogja megtudni, mi történt Nathannel. Maroon Town kalózai egy erôs és félelmetes Nathaniel Hawkot fognak látni!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Köszönöm, "+pchar.name+"! Tartozom neked... Elviszem a férjemet a hajóra. Ne aggódj, sikerül oda vinnem, emlékeztem az útra. Beteszem egy ágyba, és vele maradok. Elhajózunk a Kígyószemhez, miután végeztél mindazzal, amit itt kell tenned. Hiszek abban, hogy képes meggyógyítani Nathant.";
			link.l1 = "Rendben, Dannie. Úgysem maradunk itt sokáig. Biztos, hogy nincs szükséged segítségre?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Biztos vagyok benne. El fogjuk érni a hajót. Ne aggódj, nem hagyom, hogy a férjem meghaljon!";
			link.l1 = "Dannie, te... csodálatos vagy!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(könnyet ecsetelve) Menj... csak menj, "+pchar.name+"... és kérlek, ne vesztegesd itt az idôt!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "És akkor mi van? Meg fogja gyógyítani a férjemet? Mondd, hogy meg fogja gyógyítani!";
			link.l1 = "Dannie, Nathannek itt kell maradnia. Egyedül. A sámán megkérte, hogy ne zavarja a szertartását. Ez téged is érint. Megígérte, hogy egy hónapon belül meggyógyítja Nathanielt.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Tudod, "+pchar.name+", most végre újra szabadon lélegezhetek. Erôsen hiszek abban, hogy a sámán visszahozza a férjemet a normális állapotába. Nathant habozás nélkül itt hagyom, mert ha Kígyószem nem lesz képes meggyógyítani - senki sem fogja.";
			link.l1 = "Minden rendben lesz, Dannie. Kígyószem soha nem hazudott nekem. Bízom benne.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Én is. Egy darabig veled maradok, "+pchar.name+", nem bánod? Még mindig meg kell találnunk azt a szemét Jackmant, elvégre ô a felelôs minden bajunkért. Ô szervezte a rajtaütést! Ô vette át Nathan helyét Maroon Townban! Ellopta a fregattunkat 'Centurion'!";
			link.l1 = "Egyetértek. El kell intéznünk Jackmant. Egyikünk sincs biztonságban, amíg Jackman nem halott. De nem lesz könnyû megölni.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Van valami terved, "+pchar.name+"?";
			link.l1 = "Még nem. El kell mennem Jan Svensonhoz, és tanácsot kell kérnem tôle. Tegyük egyiket a másik után, elôbb el kell léptetnünk "+sTemp+" a Partiumi Testvérek vezetôjévé. Ehhez minden kalózbáró szavazatára szükségünk van.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Rendben, menjünk Svensonhoz. Hallgassuk meg, mit mond az a vén szivar...";
			link.l1 = "Tudod, nem kéne ennyire negatívnak lenned Jannal szemben. Igazából sokkal jobb lenne, ha megbékélnél vele... elvégre mindannyiunknak közös a célunk!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "De csak azért, mert tisztellek téged... Rendben, "+pchar.name+", sajnálom. Nem akartam megsérteni Svensont, csak ideges vagyok. Nem fog még egyszer elôfordulni.";
			link.l1 = "Jó. Dannie, minden rendben lesz. Ezt megígérhetem neked!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Teljesen megbízom benned, "+pchar.name+". Menjünk Svensonhoz?";
			link.l1 = "Gyerünk, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Menjünk, Dannie! Hallgatlak. Miben segíthetek?";
			link.l1 = "Van valami ötleted, hogy Jackman hol rejtôzhet el? Te jobban ismered ezt a szemetet, mint én. Talán van egy bázisa...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "A fenébe is, ha tudom! Jacob mindig is nagyon titokzatos volt. Soha nem hallottam még a búvóhelyérôl. Talán jobb, ha megpróbálsz logikusan gondolkodni... Olvassuk el újra a levelet, amit Knive-tól kaptál. Talán találunk benne valami nyomot.";
			link.l1 = "Próbáljuk meg...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Nos... említi Isla Tesoro-t és valami végrendeletet... Ismerôsen hangzik?";
			link.l1 = "Én és Jan úgy gondoljuk, hogy Blaze Sharp-ot Jackman ölte meg Isla Tesoro-n, és Shark-ot hibáztatták érte. És egy végrendelet... egy ribanc... biztos Helenrôl van szó... A francba, hogyhogy nem értettem eddig! Ez a szemétláda biztos Isla Tesoro közelében hajózik!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Akkor ne vesztegessük az idônket, "+pchar.name+"?";
			link.l1 = "Igen. Menjünk az Isla Tesoróra. Az öreg 'Marlin' segíteni fog nekünk ebben a rajtaütésben.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "Az a szemétláda végre meghalt... Nem hiszem el - újra a 'Centurion' fedélzetén állok! Ismerek itt minden szöget, és úgy tûnik, a hajó is felismert engem.";
			link.l1 = "Újra a tiéd, Dannie. A tiéd és Nathanielé.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "El sem tudod képzelni, mennyire örülök. Nathaniel gyakran beszélt a hajónkról, örülni fog, ha megtudja, hogy újra a miénk.";
			link.l1 = "Mit fogsz most tenni, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Én? Elviszem a hajót Sharp városába, felveszem legalább a minimális legénységet, és elhajózom Blueweldbe. Megkérem Jan Svensont, hogy vigyázzon a 'Centurion', menjen a miskitókhoz, és ott várjam meg, amíg Kígyószem meggyógyítja a férjemet.";
			link.l1 = "Tényleg meglátogatja Jan Svensont? Meg vagyok lepve...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", ez mind a te érdemed. Elgondolkodtam a szavaidon: 'mindannyiunknak ugyanaz a célja'. Emlékszel? Békét akarok kötni Svensonnal, végül is ô segített visszaadni nekem Nathant. Itt az ideje, hogy abbahagyjuk a vitát.";
			link.l1 = "Bölcs szavak, Dannie! Nathaniel újra elfoglalhatja a helyét Maroon Townban, amint jobban érzi magát.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Talán... az a helyzet, hogy a kalózbáró egy választott tisztség. Mi van, ha a többiek ellene döntenek?";
			link.l1 = "Hagyja, hogy Svenson foglalkozzon vele. Ô bárkit meg tud gyôzni. Jackman kiesése is szerepet fog játszani.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Jól van. Úgyis meg kell barátkoznom Svensonnal... "+pchar.name+"! Szeretném megköszönni mindazt, amit értem és Nathanért tettél. Megmentetted a férjemet és visszaadtál mindent, amit elvesztettünk. Tartozom neked.";
			link.l1 = "Gyerünk, Dannie. Barátok vagyunk.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Szeretném, ha tudnád, hogy mindig örömmel látunk majd Maroon Townban. Keress meg minket ott, ha lesz egy kis idôd. Nathaniel és én megtaláljuk a módját, hogy megjutalmazzunk.";
			link.l1 = "Te jó ég, Dannie! Örömmel elfogadom a meghívásodat. Leülünk, iszogatunk és beszélgetünk arról, hogy te és Nathan hogyan süllyesztettétek el Van der Decken-t...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Elmondta? Ó, ne is emlékeztessen rá...";
			link.l1 = "Rendben, Dannie. Sok munka vár rád, nekem pedig meg kell látogatnom esküdt barátainkat - Marcust és Barbazont. Remélem, megengeded, hogy felforgassam ezt a kabinot, biztos vagyok benne, hogy sok érdekes dolog van Jackman ládáiban.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Persze, tényleg azt hiszed, hogy ellenkeznék?";
			link.l1 = "Szép. Igazából kár, hogy elválunk tôled, Dannie... Viszlát Maroon Townban!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", nagyon örülök, hogy látlak! Visszatértünk Maroon Townba, és Nathan ismét a neki járó helyen van. Igazából a faluban mindenki örül neki. Most már minden ugyanolyan jól fog menni, mint régen! Nagyon hálás vagyok az önzetlen segítségedért!\nAzért szeretnék neked ajándékot adni. Tessék, vedd el. Ez a talizmán sokkal könnyebbé teheti számodra a harcot. Ez a formula pedig lehetôvé teszi, hogy még többet csinálj magadnak.";
			link.l1 = "Köszönöm, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("Kaptál egy talizmánt");
			Log_Info("Megkaptad a talizmán receptjét.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ez még nem minden. Találtam itt két ládát is, tele arannyal. Kétségtelenül Jackman tulajdona voltak. Fogadd el ôket hálám jeléül. És ne merészeld visszautasítani! Tudom, mennyi pénzt pazaroltál el, hogy segíts nekem és Nathan-nak.";
			link.l1 = "Rendben, rendben, Dannie, elfogadom!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("Kaptál két ládát dublonnal.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Kiváló! "+pchar.name+", szeretném, ha tudnád, hogy mostantól te vagy a legjobb barátunk. Nathan és én mindig örömmel látunk majd Maroon Townban! Látogass meg minket gyakrabban!";
			link.l1 = "Köszi, hogy eljöttél! Örülni fogok, ha újra látlak, úgyhogy számíts rám!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "Mit tehetünk önért, "+pchar.name+"?";
				link.l1 = "Sajnos, én most elmegyek... Viszlát, Danny.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "És itt van "+GetFullName(pchar)+". Látszik az arcán, hogy nem vesztegette az idejét!";
					link.l1 = "El kell ismernem, tudod, hogy kell szórakozni! Köszönöm, nagyon jól éreztem magam.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "Örülök, hogy látlak, "+pchar.name+"! Rum, bor? Vagy egy lányt?";
			link.l1 = "Köszönöm, Dannie! Csak látni akartalak...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "A lányt? Csendet, Danny! Ugye nem akarsz darabokra vágva és szépen összehajtogatva találni a küszöbödön? Ha-ha. Az én hûséges hölgyem, aki ott áll az ajtó elôtt, nem fogja megbocsátani nekem az ilyen kántálást.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "Egy lány? Érdekesen hangzik, Danny. Már régóta vágyom... a nôi szívverésre... Azt hiszem, meg kellene néznem - ugye nem javasolsz akárkit?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Tényleg? Igen. Miért vagy ilyen sápadt? Ha-ha, csak vicceltem. Vigyázz rá, hallod?";
			link.l1 = "Persze, hogy vigyázz rá, oké? Drágább nekem, mint az összes kincs ezen a környéken!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "Így már jobb, ha-ha. Gyerünk, menj már, a kedvesed biztos ideges lesz.";
			link.l1 = "Viszlát, Danny. És köszönöm, hogy aggódsz értem, ha-ha.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "Biztosíthatlak, ez a fiatal szépség biztosan tudja, hogyan kell felejthetetlen idôt szerezni, "+pchar.name+". Jó szórakozást! Várni fog rád a kocsmai szobában.";
			link.l1 = "Köszönöm, Danny. Már megyek is. Nem akarok egy percet sem vesztegetni!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", mindig szívesen látunk Maroon Townban. A legjobb lányok a tiéd!";
			link.l1 = "Ó, Danny. Esküszöm, ez a második otthonom.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "És itt van a kapitányom. Ma csak az enyém vagy! Gyere hozzám, már olyan régóta várok rád...";
			link.l1 = "Ó, tényleg? Nem tudsz tovább várni? Nos, akkor ne vesztegessük az idôt!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("Kapitányom... te tényleg tudod, hogyan kell meghódítani a hölgyeket! Ilyet még sosem tapasztaltam! Talán maradsz még pár órát?", "Máris indulsz, kedvesem?");
			link.l1 = RandPhraseSimple("Tudtam, hogy nem akarsz majd ilyen könnyen elengedni. Viszlát, kicsim. Nagy dolgok várnak rám...", "Sajnos, a munka útban van. De talán még találkozunk...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Végre én és Nathan újra szabadon lélegezhetünk! Ez a rohadt szemét Jackman halott! Sajnálom a 'Centurion' , de már elfogadtam a veszteségét, amikor az a szemétláda ellopta tôlem. Úgyhogy nem aggódom túlságosan.";
			link.l1 = "De én igen. Én egy idióta vagyok! Minden bizonyíték a hajóval együtt a tenger fenekére süllyedt. Segíthetett volna nekünk a Parti Testvérek új vezetôjének szavazásán. Most... minden eltûnt.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Ne izgulj túlságosan! Elôfordul. Legközelebb szerencsésebb leszel... Mindegy. Szeretném megköszönni, amit értem és Nathanért tettél. Megmentette a férjem életét. Sokkal tartozom neked.\nSzeretném, ha tudnád, hogy Maroon Town mindig örülni fog neked. Nézz be hozzám és Nate-hez, amikor csak idôd engedi. Megtaláljuk a módját, hogy megháláljuk.";
			link.l1 = "Rendben, Dannie. Biztosan meglátogatlak. Máris indulsz?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Igen, elmegyek a Miskitóba, remélem, hogy Kígyószem már meggyógyította Nathant. Aztán visszatérünk Maroon Townba.";
			link.l1 = "Heh, már annyira megszoktam téged, kár, hogy el kell válnom tôled... Sok szerencsét, Dannie!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Ó, ne játszd a hülyét, édesem. Charles, ez a szerelmes bogár éjjel-nappal körbejárta azt a bálványt, és folyton kérdésekkel zaklatta szegény Kígyószemet. Aztán hazaszaladt és hozott neki valamit, nem igaz?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "Ó, köszönöm a mûsort, Charles. Az egész Maroon Town errôl fog pletykálni, ha-ha!";
			link.l1 = "Nincs kétségem afelôl, hogy ez lesz az új prioritásod - hogy ez megtörténjen.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "Az én listám legvégén van, ami azt illeti. Ne haragudj a lányra - ez az elsô alkalom. Amikor Nathan és én kalandoztunk, az egész szigetvilág is rajtunk röhögött.";
			link.l1 = "Váltsunk témát és hangulatot. Elegem van ebbôl a bálványból, menjünk.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "Egyetértek, menjünk, hôs.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "Mit akarsz, kapitány?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, szeretnék tanácsot kérni tôled!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Hallgassa meg a parancsomat!";
            Link.l1.go = "stay_follow";
			link.l2 = "Semmiség. Lelépni!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Rendelések?";
            Link.l1 = "Álljatok ide!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és tartsátok a lépést!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Változtassátok meg a lôszer típusát a lôfegyvereitekhez.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "A lôszer típusának kiválasztása:";
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Változott a helyzet!";
            Link.l1 = "Elmehetnek.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Változott a helyzet!";
            Link.l1 = "Elmehetnek.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
