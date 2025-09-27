// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

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
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Mit akarsz, sápadtarcú? Tichingitu nem tud neked semmit mondani.";
			link.l1 = "Tichingitu a neved? Hm. Figyelj, harcos, nem azért jöttem ide, hogy téged bámuljalak. Azért jöttem, hogy feltegyek neked egy kérdést: Miért törtél be annak a kövér embernek a házába?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Nem mondtál semmit? Nem okos. Fel fognak akasztani lopásért és minden másért, amit tettél. Mondd el, miért követtél el ilyen tettet, és talán tudok segíteni neked.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu sok-sok úton, nagy vízen, nagy erdôkbôl és mocsarakból érkezik a sápadt arcú városba. Tichingitu elfáradt és enni akart. Tichingitu meghalt az éhségtôl. Senki sem akart segíteni Tichingitunak. Kiabálnak, 'menj el, vörösbôrû kutya'. kocsmáros kirúgta az indiánt, mint egy rühes kutyát. Tichingitu enni akar.";
			link.l1 = "Az istenit, de miért jöttél erre a településre az erdôbôl?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu kirúgták a bennszülött törzsbôl. Tichingitu összeveszik a törzs sámánjával, a sámán szól a fônöknek, a sámán megátkozza Tichingitut, Tichingitu elhagyja a törzset, messzire, messzire a szülôföldrôl. Tichingitu nincs otthona, nincs fegyvere, nincs semmije.";
			link.l1 = "Ezt nevezem én szerencsétlenségnek. Miért harcoltál a saját népeddel?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "A törzs sámánja gonosz ember. Azt mondja, gonosz szellem telepedett a feleség testébe. A feleségnek meg kell halnia. A feleségem csak beteg, nincs benne szellem. Tichingitu kezeli a feleségét, a sámán megöli a feleségét. Tichingitu kiállt a sámán ellen, mindenki kiállt Tichingitu ellen, Tichingitu elment.";
			link.l1 = "Megpróbálta megmenteni a feleségét? Ezért rúgtak ki a faluból?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Igen, sápadt arc. Tichingitu nincs más választás. Vagy lop, vagy éhen hal...";
			link.l1 = "Nos, én azt mondom... Hurok egy éhezô ember által ellopott néhány vacak érméért... Tichingitu, megpróbálok segíteni neked. Ismerem Fadey-t, azt a husky embert, akinek a házába belopóztál. Talán tudok tenni valamit... Beszélek a parancsnokkal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu várj. Indián nem fél a haláltól. Sámán átok Tichingitu, Tichingitu meg kell halnia.";
			link.l1 = "Még nincs minden veszve. Megpróbálok segíteni...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu várj. Indián nem fél a haláltól. Sámán átok Tichingitu, Tichingitu meg kell halnia.";
			link.l1 = "Nem kell pesszimistának lenni. A fogságod véget ért. Segítettem kiszabadítani téged.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Sápadtarcú vicc? Tichingitu szabad?";
			link.l1 = "Nem, nem viccelek. Mindjárt kinyitják a celládat, és kiengednek. Kövess, kivezetlek a börtönbôl.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			if (GetHour() > 17.0)
			{
				WaitDate("", 0, 0, 0, 13, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			if (GetHour() < 8.0)
			{
				WaitDate("", 0, 0, 0, 7, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "Tessék, újra szabad vagy. Menj csak, Tichingitu, vigyázz, hogy ne lopj többet, és ne keveredj több bajba! Inkább keress egy indián falut, és élj a saját fajtáddal, nem hiszem, hogy elleneznék, hogy befogadjanak.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu nem megy. Mester, mentsd meg Tichingitu életét. Tichingitu marad. Tichingitu élete a mesteré.";
			link.l1 = "Tichichituichi élete az övé. Mirôl beszélsz? Milyen mesterrôl, milyen életrôl? Nem érted, mit mondok? Szabad vagy! Menjetek!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Az indiánoknak adóssága van, fehér mester. Tichingitu szolgálja a hitet és az igazságot. Tichingitu tudja, hogyan kell harcolni. Tichingitu meghal a csatában a mesterért. Ô marad.";
			link.l1 = "Ó, Uram! A fenébe... Miféle mester vagyok én neked, Tichingitu? Segítettem neked, hogy ne válj rabszolgává.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu nem rabszolga. Tichingitu szabad indián. Tichingitu szolgálni akar téged. Tichingitu tudja, hogyan kell harcolni, minden kutya meghal, mielôtt a gazdája közelébe kerülne. Tichingitu tudja, hogyan kell tisztítani és tölteni a muskétát. Tichingitu tud lôni muskétával.";
			link.l1 = "Bár... Tudod, Tichingitu, ez nem is rossz ötlet. Szükségem van hûséges emberekre, és te nem tûnsz rossz embernek. És azt is tudod, hogyan kell muskétával lôni. És egyébként is, mit fogsz csinálni egyedül? A végén még ellopsz valamit, és legközelebb biztosan felakasztanak... Rendben, maradhatsz. De ne feledd: velem nem lesz nyugodt az élet.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "Rendben, elég. Menj békével, vörösbôrû testvér. Vigyázzanak rád az isteneid!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Tichingitu", "5");
			CloseQuestHeader("Tichingitu");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.systeminfo.tutorial.Fighter = true;
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu nem fél semmitôl, fehér mester. Tichingitu örömmel szolgál téged. Tichingitu hûséges az utolsó leheletéig.";
			link.l1 = "Tichichichitich... Üdvözöllek a legénységben, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.OfficerAttRange = 35.0;
			
			AddQuestRecord("Tichingitu", "4");
			CloseQuestHeader("Tichingitu");
			// Sinistra - Начало квеста "Знакомство с индейцами"
			string sModel = "Miskito_"+(rand(5)+1);
			sld = GetCharacter(NPC_GenerateCharacter("ListKakao", sModel, "man", "man", 1, PIRATE, -1, false, "quest"));
			sld.name = "Cocoa";
			sld.lastname = "Leaf";
			GiveItem2Character(sld, "blade_01");
			EquipCharacterByItem(sld, "blade_01");
			AddItems(sld, "jewelry53", rand(20)+180);
			AddItems(sld, "cannabis1", 3);
			GiveItem2Character(sld, "indian_10");
			GiveItem2Character(sld, "talisman11");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_ListKakao";
			ChangeCharacterAddressGroup(sld, "BasTer_ExitTown", "item", "item3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//LaunchTutorial("Fighter", 1);
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu hallgasson rád, kapitány "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, most indulok egy régi indián faluba, Tayasalba. Nem fogok hazudni neked, ez egy rendkívül veszélyes utazás és nagyon szokatlan: egy teleportációs bálványon keresztül. Te... Csatlakozol hozzám?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, adj egy teljes jelentést a hajóról.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Azt akarom, hogy minden alkalommal, amikor kikötünk, vásároljon bizonyos árukat.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Hallgassa meg a parancsomat!";
            Link.l1.go = "stay_follow";
			link.l2 = "Egyelôre semmi. Pihenj!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Hajójelentés? Tichingitunak nincs jelentése, mester. Csak a fegyverekrôl és a ruhákról. Tichingitu nem kapott jelentést a semmibôl.";
			Link.l1 = "Rendben, mindegy.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Mester, Tichingitu soha nem tette be a lábát egy kolóniára sem nélküled. Amikor Tichingitu belép egy boltba - mindenki azt hiszi, hogy Tichingitu megint tolvaj. Aztán börtön.";
			link.l1 = "Igen, valószínûleg igazad van. Már megint ez a börtön dolog. Ráadásul senki sem fogja elhinni, hogy pénztáros vagy.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Milyen parancsokat kaptál?";
            Link.l1 = "Várjatok meg itt!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek, és ne maradjatok le!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Meg kell változtatnod a lôszer típusát a lôfegyveredhez.";
					Link.l3.go = "SetGunBullets";
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
					Link.l6 = "Azt akarom, hogy tartsd a távolságot a célponttól.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Válaszd kia lôszertípust:";
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
            dialog.Text = "Tervváltoztatás!";
            Link.l1 = "Pihenj.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Tervváltoztatás!";
            Link.l1 = "Pihenj.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Milyen messze, kapitány? Mondja meg Tichingitu-nak, hány méter, de ne több mint húsz.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kapitány, bocsásson meg Tichingitu-nak, de nem értem magát.";
				link.l1 = "Bocsánat, az én hibám...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu tétlenül áll, nem mozdul. Ezt akarod, kapitány?";
				link.l1 = "Igen, pontosan ezt.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu nem maradhat húsz méternél messzebb a célponttól. Aztán elhibázza.";
				link.l1 = "Rendben, tartsa a távolságot húsz méteren.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu mindent megértett. Tichingitu elfoglalja a helyét, ahogy mondod.";
			link.l1 = "Jó.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tichingitu élete hosszú idôre a kapitányom életévé válik. Indián, ne felejtsd el, mit tett a kapitány Tichingituért. Tichingitu követi ôt oda, ahová a kapitány mondja, nem kérdez, nem habozik.";
			link.l1 = "Köszönöm, barátom!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Mikor indulunk?";
			link.l1 = "Kicsit késôbb. Most még fel kell készülnünk az útra.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Száz dublont fizetünk a fehér embernek, elmegyünk, és szabadon elvégezzük a dolgunkat.";
			link.l1 = "És mi van, ha megint elkapnak minket?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Akkor is fizetünk ezer dublont.";
			link.l1 = "Cinikus, de nagyon éleselméjû.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadeloupe rosszabb lesz.";
			link.l1 = "Hogyhogy?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Ott egyedül Tichingitu-t akarják felakasztani. Itt többeket akarnak felakasztani. Nem is olyan rossz.";
			link.l1 = "Ez aztán a cinizmus!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Közvetlen közelrôl lôttek. Kapitány, az öregember erôs, megmenthetjük, ha gyorsan cselekszünk.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "A fehér ember nem ismer kegyelmet. Az enyémek közül sokan, kapitány. Nagyon sok. De a magáé még több.";
			link.l1 = "Ôk a te törzsed?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Néhányan... néhányan az enyémek közül.";
			link.l1 = "Tartson ki, barátom.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Több száz dublont?";
			link.l1 = "Huh? Azt kérdezed, hogy megint én fizetem-e Deluc szabadulását a börtönbôl?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Igen.";
			link.l1 = "Én magam sem vagyok benne biztos... Te mit gondolsz?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Ki kéne fizetnünk az óvadékot.";
			link.l1 = "Ez becsületes. Soha ne hagyd hátra a sajátjaidat, mi?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Vagy ôt. Hagyd a gyengét egy jaguárnak a dzsungelben.";
			link.l1 = "Ki?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "A nagymacskának.";
			link.l1 = "Tichingitu, nehezen értelek meg. Csak azt mondd meg: mit kellene tennem ebben a helyzetben?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Használd a saját fejed.";
			link.l1 = "Nagyon segítôkész!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			ReturnOfficer_Tichingitu();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
