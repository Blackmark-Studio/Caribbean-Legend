void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Mit akarsz?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Elnézést kérek, hogy betolakodom a szállására, Kapitány Úr, de ez nagyon fontos.";
			link.l1 = "Remélem, Alonso. Ha mindenki úgy ront ide, mintha ez a saját területe lenne, akkor gondban leszünk. Szóval, mi folyik itt?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Úgy találtuk, hogy a szekrényét átkutatták.";
			link.l1 = "Micsoda?! Várjatok csak... Hogy jöttek rá? És mit kerestek a kabinomban?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "Idônként kitakarítjuk a kabinodat, amikor nem vagy a városban, vagy a priccseken pihensz. Nem vették észre? Vagy csak elfelejtetted?";
			link.l1 = "Ó, hát persze. Nos, most már elmehettek.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Charles kapitány, nézze! Valaki kotorászott a nagy fiókjában.";
			link.l1 = "Micsoda? - Nem, nem, nem, nem. Mikor vette ezt észre? Tudja, hogy ki volt az?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Nemrég, amikor meglátogattam önt. A szellemek hallgatnak arról, hogy ki lehetett.";
			link.l1 = "Ez szép húzás, Tichingitu. Most ha megbocsátasz, meg kell néznem, hogy hiányzik-e valami.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Hé, kapitány, mit nézel? Valaki átkutatta a cuccait. Még én is észrevettem.";
			link.l1 = "Nem te voltál az? Végül is, nem fizetlek olyan bôkezûen, mint Francois.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Ha én lennék a tolvaj, nem mondanám el, ugye? Elvinném az értékeket, és feltakarítanék magam után. Ez a rendetlenség nem az én stílusom.";
			link.l1 = "Utálom beismerni, de igazad van. Nos, Claude, tartogasd késôbbre a szurkálódást. Meg kell néznem, mit vitt el a tolvaj.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Kapitány, ma vettem észre, hogy valaki átkutatta a szekrényét. Nem vette észre?";
			link.l1 = "Micsoda? Nem ellenôrzöm állandóan a szekrényt, Folke, és nem is vagyok mindig a kabinban. Mondd meg ôszintén - te voltál az? Megint elszúrtad, és több banki kölcsönt vettél fel, amikor legutóbb a szárazföldön voltunk?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Egyáltalán nem, kapitány. Semmi sincs a zsebemben vagy a szekrényemben. És soha nem is lesz.";
			link.l1 = "Nagyon remélem, hogy nincs. Elmehet - én megnézem, mi hiányzik.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_0");
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, igaz?";
			link.l1 = "Az arckifejezésébôl ítélve, azt mondanám, hogy már tudja a választ. Szóval, mit akar?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "A fejét.";
			link.l1 = "Lenyûgözô! Azt kell mondjam, tetszik, ahogy ez a beszélgetés elkezdôdött. De mielôtt továbbmennénk, legalább azt megmondanád, hogy kit bántottam meg? Talán tudnánk tárgyalni.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Nem vagyunk amatôrök, Monsieur de Maure. Még ha el is mondanánk, az sem segítene önnek - a munkaadónk már elhagyta a szigetvilágot. Nem árthat nekik, és nem kérhet bocsánatot. Fizetést kaptunk, és most itt az ideje, hogy teljesítsük az alku ránk esô részét.";
			link.l1 = "Ha már kifizették magukat, minek ontani még több vért?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Nem vagyunk amatôrök. Nekünk fontos a hírnevünk.";
			link.l1 = "Attól tartok, ezúttal nem tudnak majd megfelelni neki.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Majd meglátjuk. Kutassátok át a holttestét, ha végeztünk! Égessetek el mindent, amit találtok!";
			link.l1 = "Mit égessek el?";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Amit az álarcos férfi mondott... Lehet, hogy...?";
			link.l1 = "Mi az, Longway? Nem ez az elsô alkalom, hogy fejvadászok jönnek utánam, de szokatlanul aggódónak tûnsz.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway azt hiszi, tudja, ki küldte ezeket az embereket ön után, kapitány úr.";
			link.l1 = "Van valami, amirôl tudnom kellene?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "Ez Lord Rodenburg módszere - kiiktatja azokat, akik segítettek neki, de túl sokat tudnak.";
			link.l1 = "Tényleg... Az a maszkos férfi azt mondta, hogy a megbízója nemrég hagyta el a szigetvilágot. Pontosan ezt tervezte Lucas is! Gondolod, hogy további támadásokra kell számítanunk?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "Bölcs dolog mindenre felkészülni, kapitány úr.";
			link.l1 = "Bölcs szavak. Úgy lesz. De mit akart Lucas? Mit gondolt, mi van nálam? Van valami ötleted, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, nem, Longway-nek fogalma sincs, mi lehet az.";
			link.l1 = "Kár érte. De rendben, menjünk innen.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			ReturnOfficer_Longway();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Kapitány úr, Longway beszélni szeretne önnel. Nagyon fontos.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "Mi az, Longway? Aggódsz Lucas búcsúja miatt, vagy felfedeztél valami újat?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Persze, hogy nem. Mi jár a fejében?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Sajnos nem.";
			link.l1 = "Akkor mi az, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway nem tudja megmondani. De... engedélyt szeretne kérni a távozásra.";
			link.l1 = "Elmenni? Örökre? Miért, Longway? Mint a kapitánya, jogom van tudni az okát.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "Ez igaz, kapitány úr. De Longway nem munkás és nem is szolga. Szabad akaratából jött segíteni, és ugyanúgy távozhat is. Nem örökre - van egy fontos ügy, amit el kell intézni. Longway reméli, hogy visszatérhet, amint ez megtörtént.";
			link.l1 = "Mi ez a dolog? Mondd el - ha nem is mint a kapitányod, de mint valaki, aki sok mindenen ment keresztül veled.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Longway csak annyit mondhat, hogy fogadalmat tett - régen. Eljött az idô, hogy teljesítse. Máskülönben... nincs értelme Longway életének.";
			link.l1 = "Igazad van, Longway - te nem vagy rab, és én nem vagyok börtönôr. Szabadon elmehetsz. Isten éltessen.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Elmehetsz, de legalább azt mondd meg, hová mész. Segíthetek anélkül, hogy túl sok kérdést tennék fel.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "Nekem is van egy fontos feladatom - megmenteni a testvéremet. Ehhez minden emberre szükségem van, beleértve téged is, Longway. Nélküled nem tudjuk megcsinálni.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Ne próbálj a szánalmammal vagy a kötelességtudatommal játszani. Tökéletesen megértem. Tett valaha fogadalmat, kapitány úr?";
			link.l1 = "Persze, hogy tettem. Szóval mondjon el mindent úgy, ahogy van, és az embereim és én biztosan segítünk önnek.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway nem tud. Egyszerûen... nem tud. Ez egy nagy rejtély, és még csak nem is az enyém, hogy megosszam.";
			link.l1 = "Az nagy kár. Azt hittem, hogy van köztünk bizalom. Nem hagyja el a hajót - most már minden tiszt az én oldalamon áll.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Igazad van, Longway - te nem vagy rab, és én nem vagyok börtönôr. Szabadon elmehetsz. Isten éltessen.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Ezt nem teheti!";
			link.l1 = "Sajnos, én igen, Longway. Most menj vissza a kötelességeidhez.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Nem gondoltam, hogy ilyen könnyen elengedsz. Köszönöm, kapitány úr.";
			link.l1 = "Á, semmiség. De mondja csak - hol találom meg, ha végeztél a dolgoddal?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway tényleg nem tudja megmondani, bármennyire is szeretné, ha tudná. De nagyra értékeli a kapitány úr segítôkészségét.";
			link.l1 = "Hát legyen. Hol keresselek, ha teljesítetted a fogadalmadat?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Arra számítok, hogy egy hónapon belül befejezem a dolgomat. Utána Longway még egy hétig várni fog a basse-terre-i kocsmában.";
			link.l1 = "Nos, ahogy gondolja, barátom. Ez nem búcsú. Viszlát Basse-Terre-ben.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Nos, helló, kapitány.";
			link.l1 = "Nem tetszik a vigyora, uram.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Meg vagyok döbbenve. Azért jöttem, hogy elmondjam, végre szabad vagy. De ha tovább akar maradni ebben a luxuskabinban, nyugodtan megteheti.";
			link.l1 = "Egyáltalán nem. Szóval, Longwayt megtalálták? Hol van most? Az egyik cellában?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "Inkább egy másik világban - nem akart beszélni egyikünkkel sem, és egyenesen a csatába ment.";
			link.l1 = "A francba! Egyszerûen elfoghattátok volna.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Néhány embert sokkal könnyebb megölni, mint elfogni, nem tudod? Örülhetsz, hogy nem tartunk számon semmit - a kínaiad újabb mészárlást okozott, és több mesterlövész egységre volt szükségünk, hogy elbánjunk vele.";
			link.l1 = "Igen, valóban. Köszönöm.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Ha már itt tartunk, mivel a barátja volt, találtunk róla néhány papírt. Nem értettük, hogy mik ezek - ön valószínûleg jobban tudná. Valami zagyvaságot írtak a vérrel nem borított részekre.";
			link.l1 = "Ez... A francba. Köszönjük, hogy visszahozták ôket. Viszlát, biztos úr.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Jöjjön velünk, a parancsnok úr szeretne beszélni önnel.";
			link.l1 = "Gondolom, ez a kínai keresésével kapcsolatos?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Majd meglátja, uram.";
			link.l1 = "Vádolnak valamivel?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "Egyáltalán nem. Senki sem akarja letartóztatni vagy ôrizetbe venni. Egyelôre. Amikor azt mondtam, hogy a parancsnok beszélni akar önnel, pontosan erre gondoltam.";
			link.l1 = "Ó, nos...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "Van valami ötlete? Ez a sárga bôrû ember halálosan veszélyes. Nem mi vagyunk az elsô osztag, amit ide küldtek. A parancs az parancs, de nem akarok hülyén meghalni, ha szilárd terv nélkül megyek be.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "Teljesen egyedül van odabent, és én veled vagyok. Majd én elintézem ôt, ti pedig koncentráljatok rám. Megoldjuk.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Nekem van egy. Mindannyian meg fogtok halni, pont itt.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Ne aggódj, csak beszélni fogunk vele.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Sajnálom, de ma mindannyian meg fogtok halni. És nem egy kínai ember keze által.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Szóval maga nem fejvadász... De még ha az is vagy, annak az átkozott kínai embernek a barátja vagy!";
				link.l1 = "Igen, így van. Úgyis meg kell szabadulnom tôled - nincs értelme halogatni az elkerülhetetlent.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Hogy érted ezt?! Megígérted, hogy segítesz!";
				link.l1 = "Szerintem amúgy sem adtál volna békés kiutat. Ez nem személyes ügy.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Szeretném ezt hinni.";
				link.l1 = "Szembe kellett néznem rosszabbal is. Egy kínai ember nem lesz a végünk. Gyerünk, fiúk!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Mi van, ha a beszélgetés nem úgy megy, ahogy terveztük?";
				link.l1 = "Azt utálnám, de akkor meg kell védenem magam. Gyerünk, menjünk.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Kapitány úr?! Longway nem tudja elhinni, hogy velük vagy!";
			link.l1 = "Nem, Longway, csak beszélgetni jöttem! Ez nem az, amire gondolsz!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Akkor egyedül jöttél volna. Azért próbálod csökkenteni az ôrségemet, hogy megtámadhass ezeknek a katonáknak a segítségével!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Ha tehetném, megtenném. Én vagyok az egyetlen oka, hogy még nem támadtak meg téged. Nyugodj meg, és beszéljünk, rendben?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Hagyd abba a hülyeséget! Ha akarnám, már rég megöltelek volna. Tegye le a fegyvert, és beszéljünk. Ez parancs a kapitányodtól.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Igenis, uram. Longway bízik önben, kapitány úr.";
			link.l1 = "Tessék, így már jobb. Most pedig mondd meg...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, mi folyik itt? Mi ez a... megható találkozás? Úgy volt, hogy segít nekünk likvidálni azt a kínai vadembert, nem igaz?";
				link.l1 = "Igen, én. Magammal viszem ôt, és ez az egész gyilkolás véget ér. Majd elmondod a parancsnoknak, hogy együtt öltük meg. Megegyeztünk?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Szép munka, kapitány! Letette a fegyvereit. Jó, hogy velünk vagy. Most pedig vigyük a parancsnokhoz.";
				link.l1 = "Miért tennék ilyet? Aranybüntetést fizettem Longway tetteiért - egy nagylelkû büntetést. A tiszttársaid szemtanúk voltak - ôk is megerôsítik majd. A parancsnok felhatalmazott, hogy az emberemet magammal vigyem a hajóra.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "A parancsnoknak talán elég lesz ebbôl a véraranyból, de nekem nem. Néhányan azok közül, akiket megölt abban a véres barlangban, a barátaim voltak. Különben is kétlem, hogy érdekelné, ha úgyis megöljük a kínait.";
			link.l1 = "Biztos, hogy ki akarod deríteni? És a barátaidról, akiket megöltek... hallottál már arról a szemtelen rablóbandáról? Biztos ôk voltak.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, nem ölt meg annyi katonát, mint amennyit állítanak, ugye?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "Így van, kapitány úr. Longway látta azt a bandát. Mélyebbre bújtak a barlangban, hogy ne vegyék észre. És Longway hallotta a banditák és a katonák közötti beszélgetés, káromkodás és harc hangjait.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Látod? Minden stimmel. Longway talán indulatos, de becsületes ember. Elmegyünk. Ha hozzánk érsz, megszégyeníted az egyenruhádat. Viszlát, uraim.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "Szó sem lehet róla, monsieur! Megölt egy csomó emberünket, és most azt mondja, hogy megússza?! Vagy segít megölni a rohadékot, vagy legalább ne álljon az utunkba!";
			link.l1 = "Attól tartok, közbe kell avatkoznom. Sajnálom, tényleg.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Ha csak beszélgetni akartál volna, nem kértél volna meg, hogy fegyverezzem le. De a tigris akkor is tigris marad, ha behúzott karma van. Már régen el kellett döntened, hogy elárulod Longwayt - nem kell hazudnod. Védd magad, kapitány!";
			link.l1 = "Bassza meg!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Nem hiszem el, hogy végeztünk vele! De mondd csak, miért hívott kapitánynak?";
				link.l1 = "Ez bonyolultabb, mint amilyennek látszik, haver. Meg kellett nyugtatnom a parancsnokotokat. A lényeg az eredmény, igaz? És az eredmény az, hogy Longway halott, és én segítettem neked ebben.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Még a maga jelenléte sem segített - még mindig ránk támadt. Átkozott vadember...";
				link.l1 = "Nem kellene így beszélnie róla. Azért támadott ránk, mert feldúlt volt, és azt hitte, hogy veled vagyok.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Talán... Ebben az esetben, viszlát, uram. Majd mi magunk mondjuk meg a parancsnoknak, hogy a kínai végre meghalt.";
				link.l1 = "Rendben, köszönöm. Viszlát, fiúk.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Nos, feldúlt vagy sem, vad vagy sem, ez nem változtat semmin - sokunkat megölt már korábban, elôbb ontotta a vért.";
				link.l1 = "Valami biztos ebbe az állapotba kergette. De ne rágódjunk ezen. Én megyek, te pedig visszatérhetsz a parancsnokságra, amikor jónak látod. Viszontlátásra.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Kapitány úr?";
			link.l1 = "Igenis! Mindenhol kerestelek, Longway. Elég nagy feltûnést keltettél a városban. Sok megbeszélnivalónk van, úgyhogy azonnal menjünk vissza a hajóra.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Arra!";
			link.l1 = "Látom, társaságot kaptunk. Úgy tûnik, egy kicsit késni fogunk.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Jönnek még!";
			link.l1 = "Makacs fattyúk - ezt meg kell hagyni nekik. Túlságosan védtelenek vagyunk itt kint. Menjünk a barlangba - ott könnyebb lesz megvédeni magunkat.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Nem maradhatunk itt örökké.";
			link.l1 = "És ez az elsô dolog, amit mondani akarsz mindazok után, ami történt, Longway? Nem gondolja, hogy itt az ideje, hogy elmagyarázza, mi folyik itt?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Kapitány úr, Longway...";
			link.l1 = "De igazad van - nem maradhatunk. Induljunk, mielôtt egy másik osztag is felbukkan. Majd a hajón beszélünk, ha kihajóztunk.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "A fehér ember ármánya és gonoszsága nem ismer határokat.";
			link.l1 = "Hé, én is fehér ember vagyok! Különben is, megölted a barátaikat és a katonatársaikat - joguk van dühösnek lenni.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Felmenti ôket, kapitány úr?";
			link.l1 = "Feloldozlak, Longway. És arra kérem, hogy ne ítélkezzen az emberek felett a bôrük színe alapján. Ezt neked kellene a legjobban megértened. Megzavartak minket - hol is tartottunk...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Kapitány! Mögötted!";
			link.l1 = "Ó, ma nem hagynak minket rendesen beszélgetni...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Tiszta, kapitány úr.";
			link.l1 = "Ez jó, de ne idôzzünk itt. Nekünk sok megbeszélnivalónk van. Kövessenek - visszamegyünk a hajóra.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
		
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Kapitány úr, tényleg maga az?";
			link.l1 = "Igenis, Longway. Jól vagy?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway jól van. Köszönöm. Köszönöm. De, kapitány! Nézze!";
			link.l1 = "Futás a barlangba, gyorsan! Ez egy jó védelmi pozíció!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway megnézi, hogy jönnek-e még a katonák.";
			link.l1 = "Együtt megyünk - az egész helyôrséggel szemben nem tudjuk tartani a védelmünket.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Igen, kapitány úr?";
			link.l1 = "Sok megbeszélnivalónk van. Most pedig kövessetek - azonnal fel kell emelnünk a horgonyt.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Még egyszer köszönöm, hogy segítettél, kapitány úr. Biztos vagyok benne, hogy sok kérdése van.";
			link.l1 = "Ez még enyhén szólva is. Miért ölte meg azokat a katonákat? Ön nem gyilkol kedvtelésbôl. Tudom.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "Nem, Longway nem. A katonák megpróbálták megállítani Longwayt, és a börtön nem jöhetett szóba. Nem hallgattak volna egy kínaira - csak egy fehér embernek jár ez az udvariasság.";
			link.l1 = "Más fehér emberekre sem mindig hallgatnak, de értem, mire gondol. Mégis, levágni ôket, mint a marhákat a városban? Mit csináltál Basse-Terre-ben?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "A fehérek nemcsak hogy gyakran nem hallgatnak meg; néha még beszélni sem hajlandók. És ha mégis, akkor csak azért, hogy szóljanak az ôröknek. Longway nem a bôrét vagy a szemét választotta, de büszke arra, aki. Amikor a katonák gúnyolódnak és fenyegetôznek, Longway belefárad... és dühös lesz.";
			link.l1 = "Mostantól kezdve dolgozzunk együtt. Az emberek velem beszélnek, ahelyett, hogy az ôröket hívnák... általában. De most komolyan, mesélj nekem a küldetésedrôl. Hadd segítsek.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Kérem, kapitány úr, értse meg Longwayt. Megesküdött, hogy ezt egyedül csinálja. Ne erôltesse. Ennyivel tartozik Longway-nek.";
			link.l1 = "Igazán hálás vagyok, de akkoriban magam is elbántam volna van Merdennel. Azonban már a kezdetektôl fogva kvittek voltunk - azt mondtad, hogy megmentettem az arcodat, te pedig az életemet. Most megint én mentettelek meg.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... igaza van, kapitány úr. Longway azt hiszi, hogy maga az igazi barátja a fehér emberek között. Egyszer már gondolta ezt, de keservesen tévedett. Emlékszik John Murdockra? Johan van Merdenre?";
			link.l1 = "Milyen különös, hogy van Merdenrôl beszél. Nemrég valaki az orrom elôtt tépett ki néhány oldalt az archívumából. Volt valami köze az ügyéhez? Megtalálta a tolvajt?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Megtaláltam. A tolvaj... Longway. Nagyon sajnálja, kapitány úr. Akkoriban nem tudta, hogy teljesen megbízhat-e önben.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Barátságról beszélsz, de lopsz tôlem a hátam mögött? Ez az elsô és utolsó alkalom, Longway. Megértetted?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Túl alacsony a hírneve! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "És hogyan sikerült ezt véghezvinned, Longway?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				Notification_Reputation(true, 71, "low");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway megérti. Komolyan gondolja.";
			link.l1 = "Remélem is. Most pedig mondd el, hogyan kerültél ebbe az életbe - milyen ígéretet tettél, mikor és kinek.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Igen, Lord Captain\nLongway felkeresi a számára legfontosabb élô személyt, Csang Hszinget.";
			link.l1 = "Chang Xing a legjobb barátod?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "A kedvességednek köszönhetôen a legénység többi tagja hamar hozzám szokott, és elkezdett bízni bennem.";
			link.l1 = "Nos, értem. Nem a dicséret híve, de jó munkát végeztél, Longway... ha feltakarítottad a rendetlenséget, amit a behatolásod hagyott maga után.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Rendben. De erre most nincs idô.";
			link.l1 = "Azt hiszem, nincs. De próbáld meg nem megismételni, rendben? Ha bármire szükséged van, csak szólj. Bízhatsz bennem. Most pedig mesélj az esküdrôl.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Természetesen Longway örömmel osztja meg veled a terheit, kapitány úr.\nLongway felkeresi a számára legfontosabb élô személyt, Csang Hszinget.";
			link.l1 = "Chang Xing a legjobb barátod?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing a családom, a nôvérem. Évekkel ezelôtt eltûnt. Hogy megtalálja ôt, Longway azokat keresi, akik talán tudják, hol van.";
			link.l1 = "Mi köze van ennek van Merden archívumához? Van köze a húga eltûnéséhez?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Igen, így van. Minden összefügg. Longway és Johan sok évvel ezelôtt találkoztak azon a földön, amit ti Formosának hívtok, jóval azelôtt, hogy én a szigetvilágba jöttem volna.";
			link.l1 = "Ennyi éve ismerik egymást? És van Merden is benne volt? Micsoda történet! Mi köze volt a húga eltûnéséhez?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Segített nekem a keresésben, nagyon rossz emberek után kutatva - még a fehérek mércéjével mérve is. Oliveiro Fermentelos, Antoon van Diemen és Joep van der Vink.";
			link.l1 = "A nevükbôl ítélve az egyik portugál, a másik kettô pedig holland.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Igen, így van. De a keresés nem járt sikerrel. Longway türelmesen várta az égiek útmutatását. Így amikor megszerezte van Merden archívumát, úgy döntöttem, hogy tanulmányozom. Amikor megtaláltam az elsô oldalakat, amelyeken Oliveiro szerepel, kitéptem ôket, és elmenekültem a kabinból.";
			link.l1 = "Végre minden beleillett a történetbe.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "De maga a történet még csak most kezdôdik. Kapitány úr, szeretné megismerni Longway kutatását a kezdetektôl fogva? Készen áll arra, hogy leüljön és meghallgassa?";
			link.l1 = "Pontosan ezért hívtam önt a kunyhóba. Csak rajta.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Kínaiak nem jöhetnek be ide. Ez egy tiszteletreméltó létesítmény, tiszteletreméltó embereknek - nem a magafajtáknak.";
			link.l1 = "Csak egy kérdésem lenne. Hadd tegyem fel, aztán elmegyek.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Elôbb tanuljon meg rendesen beszélni! Mondtam már - a magafajtát nem látjuk itt szívesen.";
			link.l1 = "Hol találom Oliveiro Fermentelost? Mondja meg, és máris indulok.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Te is süket vagy? Ne tegye próbára a türelmemet, különben az egész szoba bûzleni fog a sárga belsôségektôl.";
			link.l1 = "A népem már évezredek óta itt él. Ez a mi szigetünk, és még egy egyszerû kocsmába sem mehetünk be?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Ó, nagyot beszélsz, mi? Ezért akár fel is akaszthatják. Kifelé!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "Hallottam a nagy problémádról, kis barátom. Nem kellett volna ilyen hangosnak lenned - rossz név, rossz hely.";
			link.l1 = "Tudsz valamit errôl az emberrôl?! Mondd el!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Nyugodj meg, haver.";
			link.l1 = "Elnézést kérek.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "Nem akarom a bocsánatkérését, de a pénzét igen. Talán akkor segítek neked. Marcelo Schulte vagyok. És maga? Van pénzed, ugye?";
			link.l1 = "A nevem Chang Tu. Van pénzem. Ez elég?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(fütyül)Escudók, pesók, guldenek, dubloonok... és még azok a furcsa érmék is, amik nálatok vannak. Ez is megteszi. Rendben, Chung Chung, megnézem, mit tudok kideríteni az emberrôl. Ne aggódj, majdnem minden nap itt vagyok, szóval a pénzed biztonságban van. Nézz vissza naponta, és biztosan találkozunk még.";
			link.l1 = "Remélem. Nem maradt több pénzem...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Eltelt néhány nap,"+ NewStr() +"1645. április 4.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ah, Chang-Chang! Már itt is vagy.";
			link.l1 = "Chang Tu vagyok.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Nem számít, haver.";
			link.l1 = "Megtudtad, hol van Oliveiro?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Nem, fogalmam sincs.";
			link.l1 = "A pénzem!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Ne légy ilyen ideges! Ha nem tudtam volna meg semmit, mertem volna újra közeledni hozzád? Bemutatlak valakinek, aki tudja. És szerencséd van, ô szereti az ázsiaiakat. Még szolgái is vannak, hogy passzoljanak hozzá - sôt, még szolgálólányai is. Megtanulják a mocskos nyelveteket is. A neve Johan van Merden. Egy kétemeletes házban fog várni rád a rezidencia közelében.";
			link.l1 = "Köszönöm.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Te vagy Chang Chang Chang, úgy tûnik? Jöjjön be, ne szégyenlôsködjön.";
			link.l1 = "Chang Tu vagyok.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "Tényleg? Elnézést kérek. Az a Marcelo és a viccparádéja... Szégyen, hogy ilyen kevesen érdeklôdnek a kultúrája iránt. És mindez csak egy másik nyelv és a szemed vágása miatt. De maga intelligens. Nem úgy, mint a feketék, hehehe.";
			link.l1 = "(mandarinul) Tehát a csempész nem hazudott - ön valóban a kultúra embere. És tényleg beszéled a nyelvünket?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Köszönöm a meleg szavakat a kultúrámról. Ön bizonyára Johan van Merden?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Ó... csak néhány szót értettem. Még mindig tanulok, tudja. Folytatná hollandul?";
			link.l1 = "Ahogy óhajtja. Ön Johan van Merden?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Igen, Chung Tu, én vagyok. Hallom, Oliveiro Fermentelost keresi. Tudom, hol találom, de elôször is mondja meg, miért keresi ôt? A válaszod fogja meghatározni az enyémet.";
			link.l1 = "Ô... elrabolta az utolsó és legkedvesebb családtagomat, a húgomat, Chang Xing-et.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Akkor csalódást kell okoznom neked, Chang Tu. Valószínûleg már nincs remény a számára. Valószínûleg eladták rabszolgának egy gazdag ültetvényesnek vagy egy bordélyházba. Akárhogy is, nem fogod tudni megmenteni.";
			link.l1 = "Azt hiszem, Chang Xing még életben van. Oliveiro szemet vetett rá. A lány büszkén visszautasította. Ellopta ôt, amikor nem voltam otthon. És... megölte a szüleinket.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Én... nagyon sajnálom. Ha ez a helyzet, Chang Xing - igaz? - talán még mindig életben van. A következôt fogjuk tenni: adj egy kis idôt, hogy kiderítsem, hol van most Oliveiro. Mondjuk egy hét. Akkor találkozunk újra. Találkozzunk a városkapuk elôtt - ki tudja, milyen szemek követnek ide. Nem akarok jobban belekeveredni, mint amennyire szoktam, remélem, megérted.";
			link.l1 = "Én... Nagyon hálás vagyok neked, Mynheer van Merden. Alig várom a következô találkozásunkat.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Eltelt egy hét,"+ NewStr() +"1645. április 11.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Helló, Chung Tu. Látom a tüzet a szemedben. Híreim vannak, de nem jók.";
			link.l1 = "Minden hír rendkívül fontos számomra. Kérlek, mondd el, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Igenis... Fermentelos körülbelül egy hónapja indult el Bataviába. Ez az egyetlen nyomom róla. A jó hír az, hogy egy ideig ott akar maradni, szóval ha most mész, még elkaphatod. A rossz hír? Anthony van Diemen fôkormányzó közeli barátja. Nem fogsz a közelébe férkôzni.";
			link.l1 = "Ez a hír elég. Alázatos köszönetem neked, Mynheer van Merden. Azonnal indulok.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Valami azt súgta, hogy ezt fogod mondani, ezért úgy döntöttem, hogy segítek kiegyenlíteni az esélyeket neked és Chang Xing-nek. Írtam egy levelet egy régi barátomnak, Oliver Trustnak. Van egy boltja Bataviában. Tartozik nekem egy szívességgel, ezért segít neked.";
			link.l1 = "Én... nem tudom, mit mondjak...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Egy egyszerû “köszönöm” is megteszi. Ha nem találja Oliveirót a városban, keresse a Morning Star-t. A hajóján keresztül mindig megtalálhatod ôt. Sok szerencsét, barátom - neked és a húgodnak szüksége lesz rá.";
			link.l1 = "Szívbôl köszönöm, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"1645. május 29.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Ki vagy te, és mit keresel itt? Nem üzletelek a fajtáddal.";
			link.l1 = "Levelet hoztam neked.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Á, a hírnök! Bár ma nem vártam levelet. Maradj itt! Megnézem.";
			link.l1 = "Te vagy Oliver Trust? Van Merden küldött hozzád.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "Tudok olvasni, tudja. Normális esetben elküldenélek, de az olyan emberek, mint van Merden, nem fogadnak el nemleges választ. Végre itt az ideje, hogy leszámoljunk van Diemennel.";
			link.l1 = "A célpontom Fermentelos. Mi van van Diemennel?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Az nem tartozik rád. Hálásnak kellene lenned, hogy egyáltalán segítek neked. Most jól figyelj, mielôtt úgy döntök, hogy ez egy rossz ötlet. Ismerem Fermentelost. Itt volt egy ideig, de már nincs itt. A Hajnalcsillag néhány hete távozott. Isten tudja, mikor jön vissza. Tehát a célpontod megváltozott, és Fermentelos egyik barátja...";
			link.l1 = "...van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Igenis, uram. Arról is tudsz? Gondolom Johan elmondta neked? Ó, van Merden... te egy merész fattyú vagy. De ha már tudsz van Diemenrôl, akkor tudsz a magas pozíciójáról is, ugye? Mi a fô terved, hogy eljuss a fôkormányzóhoz? Biztos vagyok benne, hogy nem a rezidenciája megrohamozásával!";
			link.l1 = "Chang Tu egy képzett harcos.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "Egy képzett harcos, mi? Felfogtad, hogy most már mindannyian össze vagyunk zavarodva? És mi lesz velem, ha elfognak? Segítenem kell neked a saját és az én biztonságom érdekében. Amellett, hogy Van Diemen a rezidenciáján lakik, rendszeresen meglátogatja a városon kívüli ültetvényt és a szeretôjét, Vette-et.";
			link.l1 = "Említette, hogy segít nekem.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Úgy vélem, mindenkinek kell, hogy legyen egy szenvedélye, egy hobbija. Ami engem illet, ritka és drága fegyvereket gyûjtök. Néha van történelmük, néha nincs, de mindig halálosak. A gyûjteményem hasznos lehet a keresztes hadjáratodban. Szóval, mondja, hol tervezi a rajtaütést van Diemenen-en?";
			link.l1 = "(Residencia) Mivel ennyi jó fegyvered van, én a legjobb pengét választom. Ezzel Chang Tu páratlan lesz a fehér emberek között.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Plantáció) Az ültetvényen fogok lesbôl támadni rájuk - nem lesz hova menekülniük.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Kisasszony) A kisasszony - nem sokan lesznek ott, így az ôrök nem fognak idôben reagálni.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Jó választás! Le vagyok nyûgözve. Ahhoz, hogy a legtöbbet hozd ki belôle, szükséged lesz egy jó lôfegyverre. Mondd csak, milyen messzire tudsz célozni, Chang Tu?";
			link.l1 = "Hogy ôszinte legyek... nem túl messzire, biztosra kell mennem, hogy nem hibázom el."
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "Távolról fogok támadni - az ellenségem észre sem fogja venni, hogy honnan találtam el.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification(GetConvertStr("Sniper", "AbilityDescribe.txt")+" feloldva", "Longway");
			SetCharacterPerk(pchar, "Sniper");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Értem. Ebben az esetben, fogd ezt! Egy antik portugál toronypuskát, amely nagy kaliberû töltényt lô ki. Már nem gyártanak ilyet, még az Óvilágban sem.";
			link.l1 = "Gyerekkoromban láttam egyet...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Szóval, tudod, hogy kell használni?";
			link.l1 = "Nem...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Ne feledje, hogy a cserélhetô mechanizmus idôvel berozsdásodott. Semmi olaj nem fogja megjavítani - végleg elromlott. A feltöltés nehéz, úgyhogy csináljuk most. Vigyázzunk óvatosan - használjunk egy kis erôt, így. De ne túl erôsen, különben eltörik.";
			link.l1 = "Így?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Pontosan.";
			link.l1 = "Megértetted? Köszönöm szépen!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "bullet", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
			
			dialog.text = "Egy igazi jaeger! Légy óvatos, ez egy ajándék volt. Ez azon ritka esetek egyike, amikor egy fegyver egyszerre díszes és halálos. Egy duplacsövû vadászpuska! Nehéz kézben tartani, könnyû használni. Rájöttél már, hogyan kell vele lôni?";
			link.l1 = "Megértetted? Köszönöm szépen!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Igazad van az ôrökkel kapcsolatban, de ne becsüld alá a veszélyt. Van Diemen soha nem megy sehova a városban a jobbkeze, Joep van der Vink nélkül.";
			link.l1 = "Tehát együtt vannak Vette-tel...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Tengerészeti képességek +", "Longway");
			notification("Patkány Farkas feloldva", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "Mi? Ha! Elég nagy képzelôerôd van, kínai! Antoon gyáva, és van der Vink azért van ott, hogy megvédje ôt, ha valaki megzavarja a 'privát idejüket'\nJoep mindig nehéz árokpáncélt visel - áthatolhatatlan a legtöbb hideg fegyver számára. Ezért is kell valami különleges. Vedd ezt a pengét. Hosszú, erôsebb, mint a legtöbb más kard, és a súlya is olyan, mint egy jó pengéé.";
			link.l1 = "Egy páncélos ellenfelek elleni harcra való rapír?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "Ne célozz magára a páncélra - ez nem egy estoc. Csapj a réseken és a sebezhetô helyeken, például az ágyékon, a hónaljban és a torokban. Fáraszd le, diktáld a feltételeket. Joep egy nehéz fejszével is hadonászik, ezért ne próbáld hárítani a csapásait - inkább térj ki\nHa esetleg nem találnál nyitást, vedd magadhoz ezt a bunkósbotot. Általában sörétes tölténnyel van megtöltve, de készítettem neked egy készlet acélnyilat.";
			link.l1 = "Nyilak egy muskétához...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Szokatlan, igaz? A régi és az új keveréke. Úgy tervezték, hogy egy kézzel lehessen lôni vele, de ha túl nehéz, használd mindkét kezed. Sokan megteszik\nés itt, próbálja ki ezt a fonott páncélt. Könnyebb, mint Joep cuirassja, de még így is megfelelô védelmet nyújt. Ne hagyd, hogy a fejszéje közvetlen találatot mérjen rá - egy ilyen fegyverrel szemben még a milánói páncél sem bírná ki. Megértetted?";
			link.l1 = "Igen, értem. Köszönöm, Mr. Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Túlságosan magabiztos vagy, ugye? Talán túl korán beszéltem neked a gyûjteményemrôl. De... maga már elkötelezte magát. Fényes nappal megtámadni egy rezidenciát merész lépés, nem várható el. Ez a penge megfelel az igényeinek. Nem a legjobb a világon, de szúrásra, vágásra és aprításra tökéletes.";
			link.l1 = "Clewang! Felismerem ezt a pengét. A szomszédos szigetekrôl származó emberek gyakran használnak ilyet.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification(GetConvertStr("TannedLeather", "AbilityDescribe.txt")+" feloldva", "Longway");
			SetCharacterPerk(pchar, "TannedLeather");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Használtál már ilyet korábban? Igen. Kevés idôd lesz, és sok ellenséggel kell szembenézned. Tessék, fogd ezt is - egy háromcsövû, gyönyörûen berakott kézifegyver. Most töltsd meg elôttem; késôbb nem lesz rá idôd. És vedd fel ezt a párbajmellényt. Könnyû, megadja a szükséges sebességet, és némi védelmet.";
			link.l1 = "Köszönöm, Mynheer Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Várj, még nem végeztünk. Közös érdekünk, hogy túléld. Vedd be ezt a gyógyszert, hogy begyógyuljanak a sebeid a csata után. \nés ezt az elixírt is. Az íze és a szaga szörnyû, de elpusztítja a szervezetedben lévô mérget. Joep van der Vink, Van Diemen testôre ezzel a szarral keni be a fegyvereit. Pimasz szemétláda, így elônyben leszel.";
			link.l1 = "Nem tudom, hogy valaha is eléggé meg tudom-e köszönni, Mynheer Trust...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "A legjobb hála az lenne, ha nem adnál fel, ha elkapnának. Habár, a legvalószínûbb, hogy ott helyben megölnének. De ha ezt túléled, mondd meg Van Diemennek, hogy nekem köszönheti a halálát. Meg tudod ezt tenni?";
			link.l1 = "Nem probléma. Még egyszer köszönöm, Mynheer Trust. Viszontlátásra!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Állj! Hová mész, kínai?";
			link.l1 = "A rezidenciára.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Ez költôi kérdés volt, zsenikém. Mibôl gondolod, hogy bárki is beengedne oda egy olyan embert, mint te?";
			link.l1 = "Mynheer Van Diemennel van dolgom. Engedjen át, kérem.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Tudja a fôkormányzó nevét? Nos... mondja el, mi a dolga. Továbbítom, és válaszolok.";
			link.l1 = "Csak Mynheer Van Diemennel beszélgetek. Már vár rám. Menjen arrébb, vagy megbánja.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Nocsak, nocsak, ne krákogj, szûkszemû. Vagy így csinálom, vagy nem.";
			link.l1 = "Akkor az én utam.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Átkozott paraszt! Ki bérelt fel téged? Ennél többet fizetek neked!";
			link.l1 = "Ti fehérek csak az arannyal törôdtök. A sárkányok átkozzák meg a fajtádat. Információért jöttem, de az embereid nem engednek be.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "Mit akarsz?!";
			link.l1 = "Fermentelos. Hol van most?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro? De mi a fenének akarod ôt? Nem mondok neked semmit!";
			link.l1 = "Megölte a családomat és elrabolta a húgomat. Azt tanácsolom neked, hogy kezdj el beszélni. A saját érdekében.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "Mit fogsz tenni velem? Az egész helyôrség hamarosan itt lesz.";
			link.l1 = "Hallottál már Lynchy-rôl? Ez egy büntetés az én kultúrámban. Azt jelenti: 'Halál ezer vágással'.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Nem lesz idôd annyi vágást ejteni rajtam, te idióta!";
			link.l1 = "Ez egy szófordulat. A hóhér egyenként ejti a vágásokat. Vagy levágja a test darabjait. Annyit csinálunk, amennyire van idônk - hacsak nem kezdesz el beszélni.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A-A!!! Állj! Állj meg, te mocskos állat! Elmondom, elmondok mindent. Csak hagyd abba. Joep! Végre! Hol a faszban voltál egész idô alatt?!";
			link.l1 = "Milyen rossz idôzítés...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? Azonnal orvoshoz kell menned. Segítek neked eljutni oda, amint itt végeztem. Te! Mi a fenét csinálsz, te sárga mészáros?!";
			link.l1 = "Sárga hentes? Ez tetszik nekem. Csak egy kérdésre szeretnék választ kapni, de úgy tûnik, senki sem hajlandó megtenni...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Milyen kérdés?!";
			link.l1 = "Hol van Oliveiro Fermentelos? Nem tudod megmondani, hogy hol van?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Leszarom Fermentelos-t! Ki adta neked a pénzt és az információt?!";
			link.l1 = "Oliver Trust. Egyébként azt akarta, hogy megmondjam neked, hogy a haláloddal tartozol neki.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "Bizalom?! Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha! Az a fösvény, azt hiszi, bosszút állhat, csak mert elvettük az ültetvényét? Hamarosan elveszítjük a boltját és az életét, amint végeztem veled.";
			link.l1 = "Csak az idômet vesztegeted.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(mandarinul) Szóval keressünk egy jó leshelyet.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(mandarinul) Ezzel a rozsdás izével közel kell mennem. Gyors röppentyû - éles és könyörtelen. A félelem és a pánik elvégzi a többit.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(mandarinul) Pontosan itt. Elôször meg sem fognak látni. A legjobb csaták azok, amelyek el sem kezdôdnek... vagy gyorsan, kevés vérontással végzôdnek.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Csúnya állat... Szökött rabszolga vagy, ugye? Honnan van ilyen fegyvered? Valaki felbérelt téged...?";
				link.l1 = "Nincs idô! Mondd meg, hol van Oliveiro Fermentelos - most!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, vicces... Nincs idô - a vér már folyik a hasamból. Égj a pokolban, pogány...";
			link.l1 = "(Mandarinul) Nem!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(mandarinul) Miért, miért, miért?! Hogy találjam meg most Fermentelót?!";
			link.l1 = "De elôbb el kell rejtôznöm - valaki már biztosan jelentette ezt a vérfürdôt...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hic! Egy kínai! Nem gondoltam volna, hogy egy ilyen embert, mint te, meghívnak ide. Szeret nézni, mi? Hehe.";
			link.l1 = "Miért van itt ennyi ember...? És te ki vagy?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "Nem ismersz fel a ruhámról? És vigyázz a hangodra, amikor a fôkormányzóval beszélsz! Hic!";
			link.l1 = "Szóval, maga biztosan Mynheer Van Diemen. Elnézést kérek a tudatlanságomért. Ez itt valami karnevál?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "Így van, jóember, és nem is lehet másképp! Egy transzvesztita karnevál! Ha-ha-ha-ha! Nem is olyan rossz, paraszt! Biztos vagyok benne, hogy Luthers szívesen felvenné Vette ruháját, ha-ha-ha-ha!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "Az a szánalmas férj, aki szeret a szekrénybôl leselkedni, miközben a kedves feleségét ágyba dugják. Ôt nem zavarja!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "Igaz, Vette, kedvesem? Heh-heh.";
			link.l1 = "(Mandarinul) Mi a fene folyik itt...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hic! Nem tudom, mit mondtál, de a szemedbôl és a hangodból ítélve egyetértesz velem! Van Haan egy istenverte perverz. Szóval, mi vagy te egyébként? Munkás? Vette hívott meg?";
			link.l1 = "Én...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Egy munkást meghívni ide túlzás, még Vette-nek is. Nyilvánvalóan eltévedt és rossz helyen van. Hé, te! Tûnj el innen, és felejts el mindent, amit láttál. Ki a gazdád? Kapcsolatba lépünk vele, és mindketten megkapjátok a pénzt a hallgatásotokért. Talán még a családodhoz is visszatérhetsz a kontinensre. Válaszoljon és távozzon.";
			link.l1 = "Valójában üzleti ügyben vagyok itt.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, üzlet. Itt csak Mynheer van Diemen “Biznisz” csinál. Az én feladatom, hogy megvédjem ôt a magadfajtáktól. És Luthers... az Luthers. Vagy... Vette tényleg meghívott ide?";
			link.l1 = " Nem, azért vagyok itt, hogy...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Az én drága Vette-em tényleg meghívott ide egy sárga seggût?! Takarodj innen!!!";
			link.l1 = "A nyomorult felszarvazott...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Senki sem beszél hozzád. Fogd be a szád. Ne tegyél úgy, mintha lenne farkad vagy méltóságod.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Cu-cu-cuckold?! Nem, jobban szeretem ôt, mint magamat. Ha, egy ilyen hülye kínai, mint te, ezt nem értheti meg!";
			link.l1 = "(mandarinul) Beteg állat.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Co-co-kakas?! Semmi gond! Ez az! Csak azt tudom, hogy más férfiak több örömet okoznak az én drága Vette-emnek, ennyi az egész!";
			link.l1 = "Ahogy az én hazámban mondják, a férfi addig férfi, amíg csak egy ujja marad. Ha férfi lennél, megértenéd ezt.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Persze nem én hívtam meg, de tudod, ô nagyon kedves. Talán itt marad, miután mindannyian elmentek. A kutyánkkal már próbáltam, de még sosem csináltam...";
			link.l1 = "Fogd be, amikor a férfiak beszélnek, te kurva! Te vagy itt az egyetlen állat. Üzleti ügyben vagyok itt. Oliveiro Fermentelost keresem. Ti biztos a barátai vagytok. Meg tudná mondani, hol lehet, Mynheer Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, megsértett engem! Megsértett! Nem hagyod annyiban, ugye?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, bocs, haver, de a hölgy ki van akadva. Meg kell adnom neked egy kis illemleckét. Elsô lecke.";
			link.l1 = "De tudnál segíteni Oliveiro keresésében?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "Egy halott munkáson nem segít.";
			link.l1 = "(Mandarinul) A francba veletek...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(Mandarinul) A fenébe! Nem tanultam semmit!";
			link.l1 = "(mandarinul) Soha nem fogom elfelejteni ezt a napot... El kell tûnnöm innen, mielôtt az ôrök megérkeznek. Nem mintha érdekelné ôket a zaj, ami ebbôl az ôrültekházából jön...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(mandarinul) Az istenek elátkozták ezt a napot! Van Diemen elvérzett, miközben a lakájával foglalkoztam...!";
			link.l1 = "(mandarinul) Az ôrök jönnek. Ki kell verekednem magam innen.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"1645. július 26.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Ó, ez Chang Chang! Ezúttal miben van szükséged segítségre, kis barátom?";
			link.l1 = "Chang Tu az... hogy érted?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Csöpög belôled a megvetés irántam, ugye? Nem jönnél ide, ha nem lenne szükséged valamire.";
			link.l1 = "Tudod, hol van van Merden? A városban van? Nincs otthon. Beszélnem kell vele.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Nem lehet elvárni egy férfitól, hogy egész nap otthon maradjon, és várja, hogy egy sárga bôrû férfi felbukkanjon. Dolga van a szigeten. Ma este visszaér a városba, úgyhogy ne aggódj, Chang Chang!";
			link.l1 = "Köszönöm. Köszönöm. Viszontlátásra.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Hé, szûkszemû! Mi ez a nagy sietség ilyenkor? Már minden rendes ember alszik.";
			link.l1 = "Akkor mi van veled?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Jól mondod! Járôrözünk! Az a hír járja, hogy egy kis sárga fickó szaglászik a városban, és zaklatja az istenfélô embereket.";
			link.l1 = "Ki lehet az, mondd csak, ki lehet az?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Elég a beszédbôl - késôre jár, és kezdek elálmosodni.";
			link.l1 = "Hamarosan örökké fogsz aludni.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, jól vagy?";
			link.l1 = "Mynheer van Merden! Igen, hála a közbelépésednek. Jól vagy? Ez a legfontosabb kérdés.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Mindig másokra gondolsz, ugye? Ez a tulajdonságunk közös. Nem nézhettem tétlenül, amikor láttam, hogy megtámadnak téged, még ha tudtam is, hogy elintézed ôket. Hogy válaszoljak a kérdésedre, jól vagyok, csak egy kicsit fáradt. Kicsit remegnek a lábaim. Menjünk be, ha nem bánod. Ott beszélhetünk.";
			link.l1 = "Természetesen, Mynheer van Merden, ez mégiscsak a te házad.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Most már nyugodtan beszélgethetünk, nyugodtan és békében. Mondd, mi szél hozott hozzám, Chang Tu?";
			link.l1 = "Igazad van, Mynheer van Merden. Most tértem vissza Bataviából, és...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Várj. Szegény Chang Xing...?";
			link.l1 = "Nem, dehogyis! Remélem, nem. Az Ég még mindig titokban tartja a sorsát elôttem. És ami Fermentelost illeti... ô nincs Bataviában. Van Diemen nem segített.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Nem is segíthetett, mert ô és Oliveiro régi barátok. Ahogy az angolok mondják, barátok és bûntársak. Meglepôdnék, ha bármi hasznosat mondana.";
			link.l1 = "Igen, hála neked és a Trösztnek, hatalmas fegyverekre tettem szert. Megtámadtam Van Diement, hogy kihallgassam, és megtudjam, hol van Fermentelos. De meghalt, mielôtt bármit is megtudhattam volna...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Lenyûgözô. Rájöttél, hogy az emberek nem mindig akarják megosztani, amit tudnak. Szóval vannak más... meggyôzési módszerek is, mondjuk úgy. Azt hittem, hogy talán megtudtad a húgod halálát, és ezért kezdtél el tombolni. De most mi szél hozott ide? Mondtam, hogy nem tudom, hová jár Fermentelos, eltekintve az alkalmi látogatásaitól Bataviában. Van Diemen eltûnésével ez az utolsó nyom is elveszett.";
			link.l1 = "De te sok mindent és sok embert ismersz. Arra gondoltam, talán megint segíthetnél, talán kérdezôsködhetnél Fermentelosról, mint korábban. Maga volt az elsô fehér ember, aki jól bánt velem. Az elsô... fehér barát.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "Ez... megható.";
			link.l1 = "Mynheer van Merden, miért mosolyogsz...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Huh? Ó, sajnálom, Chang Tu. Öregszem, érzelgôs és melankolikus leszek a korral. Ez egy ôszinte mosoly - nem tudtam elrejteni. Örülök, hogy barátodnak tekintesz. Mivel barátok vagyunk, azt is elvárom, hogy idôrôl idôre segíts nekem. Cserébe én biztosan segítek neked Fermentelosban. Ne aggódj - nem sétálsz bele egy csapdába.";
			link.l1 = "Hmm, segíteni hogyan?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Mióta utoljára találkoztunk, elmélyültem a nyelved és a kultúrád tanulmányozásában, különösen az orvostudományban. Szeretném, ha idôrôl idôre megtalálnál nekem bizonyos ereklyetáblákat. Nagylelkûen megfizetem majd érte, mint bármely más munkáért. És remélem, hogy idônként gyakorolhatjuk a kínai nyelvû beszélgetéseket. Szégyellem, hogy a szolgáimat kérem, de egy barátom...";
			link.l1 = "Chang Tu mindent meg fog tenni, Lord van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Jól van. Hosszú út áll elôttünk, barátom. Hosszú út. Ha! Szerintem ez egy jó fedôneved lenne. A szakmám hasznos gyakorlása. Hollandul “Lange Afstand.” Az angoloknál “Long Way.” Melyik tetszik jobban?";
			link.l1 = "Nekem az angol változat jobban tetszik. Hosszú. Way. Longway. Az én nyelvemen elég jól hangzik. Köszönöm, hogy meghallgatott, Lord van Merden. Longway várni fogja szavát, és készen áll, hogy segítsen Önnek és teljesítse kéréseit.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Ha már az archívumról beszélünk, kapitány úr, nálad van? Csak ez kell nekem - kívülrôl tudom a rejtjelezést.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("Minden képesség +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Igen, megtartottam, mert gondoltam, hogy egy nap még hasznos lehet.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Sajnos, nem. Ez volt az utolsó reménye, hogy megtalálja a húgát?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway nagyon örül, hogy a kapitány úr aggódik. Egyelôre még van remény. Találtam egy új nyomot Guadeloupe-on.";
			link.l1 = "Rendben, akkor... Mondja el, mi történt ott magával.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "Ez bölcs döntés volt. Talán találunk ott valamit, ami segíthet nekünk Chang Xing keresésében.";
			link.l1 = "Az ideális lenne. Tanulmányozzuk most rögtön.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Igen, tanulmányozzuk együtt. Az évszám... 1637. Antoon van Diemen eladta... eladta...";
			link.l1 = "Rabszolgákat, igaz?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Nôket a népembôl, akiket gazdag fehér embereknek adtak el.";
			link.l1 = "Ez szörnyû.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Kapitány úr, nem tûnik meglepettnek. Egyáltalán nem aggasztja önt azoknak a nôknek a sorsa?";
			link.l1 = "Longway, persze, hogy ôszintén aggaszt. Láttam ezt a mocskot belülrôl. De én mindig is a nôk szószólója voltam... és egy kicsit nôi' man, hogy ôszinte legyek. Jó, hogy megölte van Diemen-t, megérdemelte. Van még valami más is?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen csak azokkal dolgozott együtt, akikben teljesen megbízott - Joep van der Vinkkel, a jobbkezével, és azzal az átkozott Oliveiro Fermentelosszal. És... és...";
			link.l1 = "Mi az? Elsápadtál, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Nagyon sajnálom. Ez szörnyû, de miért vagy ilyen sokkolt? Korábban azt mondta, hogy kitépte az összes Fermentelosról szóló oldalt. Akkor nem találtál említést van Merdenrôl?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway sietett, és biztos kihagyta ezt a fontos darabot.";
			link.l1 = "Értem. Ha készen állsz, keressünk tovább, és találjunk bármit, amit most azonnal felhasználhatunk.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Azt írja, hogy Fermentelos az embereit nôk elfogására küldte, kicserélte ôket és megsemmisítette a feljegyzéseket. Merden aztán elküldte ôket Bataviába, ahol van der Vink és van Diemen eladta a nôinket fehér embereknek. Bárcsak hamarabb megtudtam volna ezt...";
			link.l1 = "Szóval, végül mindannyian együtt dolgoztak. Ne hibáztasd magad, Longway. Nem tudhattad. Az archívum csak nemrég került a kezedbe. Van még valami más is?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Igen. Már majdnem tíz éve dolgoznak rajta. Annyi nô vesztette el a családját, a becsületét, a reményét... De aztán Fermentelos abbahagyta a munkát van Merdennel. Ez volt az egyetlen ok, amiért segített nekem - mindig is csak meg akart szabadulni a korábbi társától.";
			link.l1 = "Milyen egyéb részleteket jegyeztek fel itt a piszkos tetteikrôl?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Még több van Merden sötét gondolata. Rájött, hogy van Diemen pénzt csalt ki tôle. Ezért elküldött engem Bataviába, remélve, hogy ott halok meg, de abban is reménykedett, hogy magammal viszem van Diement.";
			link.l1 = "Hideg. De hihetetlenül okos is.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Lehetett volna még rosszabb is. Van Merden küldte azokat a verôembereket a házához, hogy megöljenek. Csak akkor lépett közbe, amikor rájött, hogy egyedül is legyôzhetem ôket.";
			link.l1 = "Kétségtelenül átgondolta az egészet.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Miután élve visszatértem, biztos azt hitte, hogy rájöttem a valódi tervére, és bosszút akar állni. Amikor beszéltünk, a fegyverét az asztal alá tartotta. De amikor az elsô fehér barátomnak neveztem... majdnem szétrobbant a nevetéstôl...";
			link.l1 = "Ez szörnyû, Longway. Keserû dolog rájönni, hogy azok, akiket barátoknak tartottunk, a hátunk mögött végig rajtunk nevettek.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway már régen megtanult valamit, nem sokkal azelôtt, hogy megérkezett erre a szigetcsoportra. Elfogtak a portugálok, és fel akartak akasztani. Lord Rodenburg mentette meg az életemet.";
			link.l1 = "Így kerültél a szolgálatába? Lucas is Formózában volt?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Igen, így van. És nem csak ô, hanem Van Berg is. Van Merden mondta, hogy ô volt az, aki azt tanácsolta Rodenburgnak, hogy kíméljen meg. De valamivel késôbb Longway egy kétes forrásból megtudta, hogy valójában Johan volt az, aki a portugálokat utánam küldte. Akkor még nem hittem el... de most már tudom, hogy talán igaz...";
			link.l1 = "Undorító.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Mégis, kétségek telepedtek a szívembe aznap. Így amikor megtudtam, hogy Lord Kapitány és van Merden szembekerültek egymással, Longwaynek eszébe jutott a kedvességed, és a te oldaladra állt.";
			link.l1 = "Ez volt a helyes döntés, Longway. Heh, kiderült, hogy mindvégig én voltam az elsô igazi fehér barátod.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Kiderült, kapitány úr. Most már értem. Van Merden azt mondta, hogy a barátja vagyok. De a valóságban Longway nem volt több számára, mint egy másik munkás - csak hasznosabb, mint a legtöbb\nEz minden. A többi oldal a könyveléssel, valamint Van Berg és Rodenburg közötti üzleti részletekkel foglalkozik.";
			link.l1 = "Értem. És most itt az ideje, hogy elmesélje, mit csinált Guadeloupe-on.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "A Reggeli Csillagot kerestem. Az egyik kitépett levéltári oldal szerint utoljára a Szent Kristóf közelében látták.";
			link.l1 = "Miért ott? Megegyeztünk, hogy Guadeloupe-on találkozunk, és ott találtam rád.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Mert St. Christopher's Georges Gravel, van Merden egyik informátora lakik. Georges azt hiszi, hogy még mindig Johannak dolgozom. Ráadásul Gravel egyszer súlyos bûncselekményt követett el van Merden ellen. És Longway segített eltussolni.";
			link.l1 = "És milyen bûncselekmény volt az?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Ez nem fontos. Ami fontos, az az, hogy Georges tartozott Longwaynek. Ezért elmentem a templomba, ahol Gravel segédpapként dolgozik. Készen áll a kapitány úr, hogy tovább hallgasson? Kicsit zavartnak tûnik.";
			link.l1 = "Bocsánat, elkalandoztam. Igen, persze, csak rajta, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"Szent Kristóf-sziget.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Jó, még nem késtél el. Nem szeretnék a szükségesnél tovább itt maradni, tudja! Ezúttal mire van szüksége, Longway?";
			link.l1 = "Változtass a hangodon, Kavics. A szervezetnek szüksége van a szolgálataira.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Be kell vallanom, régóta nem hallottam felôlük. Elfelejtettek engem?";
			link.l1 = "Emlékeztethetem ôket. Talán azzal, hogy elmondod Lord van Merdennek, amit tettél.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "Jól van, jól van, nem kell ilyen dühösnek lenni! Mit tehetek érted?";
			link.l1 = "Információra van szükségem a Hajnalcsillagról. Bármit, amit csak találsz. Minél többet, annál jobb.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Persze, de idôbe telik! Két nap! Legalább két nap.";
			link.l1 = "Miért tart ennyi ideig?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Normális esetben az áldozati ládából kell pénz, hogy az informátoraim nyelvét meglazítsam. De nemrég kiraboltak minket! Az atya persze újból meghirdeti az adománypénz gyûjtését, de még meg kell javítanunk a tetônket - beázik! Sok adományra lesz szükség, hogy megjavítsuk.";
			link.l1 = "Két nap. Nem maradhatok itt örökké. Nincs annyi idôm. Longway nem a türelmérôl híres. Lord van Merden még kevésbé. Vagy emlékeztesselek erre, Kavics?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Nem irányíthatom azt, ami a hatókörömön kívül van! Megteszem, amit tudok. Bár sokkal gyorsabban rájönnék, ha megtalálnád azokat a rablókat, és visszahoznád az adományainkat!";
			link.l1 = "Majd meggondolom. Kezdj el keresni. Két nap. Nem több. Találkozzunk ugyanabban az idôben és ugyanott.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Egy nappal késôbb..."+ NewStr() +"A templomrablók nyomában.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Nézzenek oda! Egy szûkszemû ember a mi szigetünkön! Menekülsz a gazdáid elôl, mi? Ki elôl bujkálsz, ha megkérdezhetem?";
			link.l1 = "Szabad ember vagyok.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ha! Hát persze. De erôsnek és okosnak tûnsz, még ha a szemed kicsit ferde is. Akarsz csatlakozni a bandánkhoz? Nem hiszem, hogy lenne hova menned.";
			link.l1 = "Longway úgy gondolja, hogy jobban érdekel a kirablása, mint a beszervezése.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, tartsd magad szerencsésnek. Nemrég kiraboltunk egy templomot a városban, el tudod ezt hinni? Egy templomot? Elhiszed ezt? Mert tolvajoktól lopni nem is lopás.";
			link.l1 = "Nem terveztem, hogy levadászlak, de örülök, hogy megtaláltalak.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Vadászni ránk? Á, szóval zsoldos vagy, nem valami szökött munkás. Akkor rossz nektek.";
			link.l1 = "Pontosan.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Baszd meg... Miért nem öltél meg azonnal? Mit akarsz tôlem? Börtönbe akarsz hurcolni?";
				link.l1 = "Nem érdekel. Csak mondd el, hova rejtetted az aranyat.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Heh... Te sárga bôrû fattyú...";
			link.l1 = "Longway türelme fogytán van. Majd én kiderítem. A kérdés csak az, hogy meddig fogsz szenvedni.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Rendben, rendben... Egy barlangban van. Minden ott van. A pénz a tiéd. Csak... csak ne ölj meg, rendben?";
			link.l1 = "Nem mondtam, hogy nem lesz szenvedés...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(Mandarin nyelven) Itt vannak a banditák' hideout.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(mandarinul) Ez nagyon sok!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(Mandarinul) Lépéseket hallok...";
			link.l1 = "(Mandarinul) Van itt még valaki...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "Mi a fenét keresünk itt? Nincs itt senki - megbizonyosodtunk róla, hogy az összes rabló eltûnt.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "Ez a lényeg, idióta! Vissza fognak jönni, és mi majd melegen fogadjuk ôket.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Körülnézek, hátha senki sem bújkál. Úgyis unatkozom...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(mandarinul) Soldiers! Milyen szerencsétlen... Most mit kellene tennem?";
			link.l1 = "(mandarinul) Nekem nagyobb szükségem van erre a pénzre, mint a fehér katonáknak! Nem megyek el nélküle!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Á, Longway úr, visszatért!";
			link.l1 = "Hát persze. Voltak kétségei? Találtál valamit a Hajnalcsillagról, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Igen, uram. Egy nehéz gálya, egy spanyol kapitány vezeti, legalábbis azt mondják...";
			link.l1 = "Ô portugál. Ti fehérek még egymást sem tudjátok megkülönböztetni.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Ó, igen, persze. Az én hibám. Mindenesetre rájöttem, hogy erôsen átalakította a gályát, hogy megpróbálja kereskedelmi hajónak kiadni, kis kaliberû ágyúkkal és kisebb legénységgel. De a raktérteret kibôvítette, csordultig megtöltötte - olyan nehéz, hogy alig tud vitorlázni.";
			link.l1 = "Ezért úgy döntött, új életet kezd. Jól van. Hol találom meg?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "Az már bonyolultabb. Folyamatosan mozog a mi gyarmataink és az angolok között, de csak a Windward-szigetek között. Azonban megtudtam, hogy jelenleg Basse-Terre felé tart egy nagy rakomány borral.";
			link.l1 = "Ki kell találnom, hogyan juthatnék oda gyorsan.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "Ez az ön gondja, monsieur Longway. Nekem is van elég gondom... például megjavítani azt az átkozott tetôt.";
			link.l1 = "Ha már a gondoknál tartunk, megtaláltam azokat a templomrablókat. Itt van az adománya. Javítsa meg a tetôt - nem tesz jót az istenének, ha nincs tetô.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Nagyon köszönöm, monsieur Longway! Soha nem gondoltam volna, hogy maga lesz az, aki ezt megteszi.";
			link.l1 = "Én sem gondoltam. De valamit kezdenem kellett azzal a két nappal.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Szóval, el kell jutnia Guadeloupe-ra? Találok egy hajót, ami arrafelé tart. Várja, hogy hamarosan halljon felôlem!";
			link.l1 = "Ez nagy segítség lenne. Köszönöm, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Másnap reggel..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Ön biztosan Georges ismerôse? Megkért, hogy adjam át ezt önnek.";
			link.l1 = "Egy cetlit? Hálámat fejezem ki. Honnan tudta, hogy nekem jött?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Ez most komoly?";
			link.l1 = "Ó, persze.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(olvassa a levelet) Monsieur Longway, a ‘Provence' pinnace holnap reggel indul Basse-Terre-be. A kapitányt, Mathieu Terugny-t a kocsmában találják. Adja át üdvözletemet van Merden úrnak. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Itt nem szolgálunk fel italokat a fajtádnak. És hacsak nem akarok bolhákról szóló panaszokat hallani, nem adok ki szobát sem.";
			link.l1 = "Nincs szükségem se italra, se szobára. És... Longwayben nincsenek bolhák.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Honnan a fenébôl kéne tudnom? Rendben, köpd ki. Mit akarsz? Akkor kifelé.";
			link.l1 = "Igenis, uram. Mathieu Terugny kapitányt keresem. Nem találom. Tudja, hol van?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Éppen a hajóját készíti elô a helyi boltban. Ez sokkal fontosabb, mint egy magafajta kínaival csevegni, de maga ezt nyilvánvalóan nem érti.";
			link.l1 = "Valójában, én régen... Nem érdekes. Most nem fontos.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "Mit akarsz, kínai? Nem látod, hogy elfoglalt vagyok? El kell készítenem a hajómat.";
			link.l1 = "Mathieu Terugny kapitány?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Nos, ez már nem vicces. Honnan tudja valaki, mint maga, hogy ki vagyok? Valaki küldte magát?";
			link.l1 = "Nem kell aggódnia. Hallottam, hogy Basse-Terre-be hajózik. Elvinnél engem is utasként? Fizetek.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Ez egyre jobb lesz. St. Pierre-be tartok, nem Basse-Terre-be, de ez csak egy kis kitérô. Az jó, mert így nem kell tovább a hajón tartanom a szükségesnél. Ötezer pezó. Három óra múlva indulunk. Fizessen a mólónál. Még ha kereskedô is vagyok, nincs alku. Megértette?";
			link.l1 = "Igen. Köszönöm. Találkozunk a mólónál, Terugny kapitány.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Mégiscsak eljöttél, cinkes. Azt hittem, nem fogsz eljönni - a te fajtádnak senki sem ad önként valódi pénzt.";
			link.l1 = "Ötezer pezó, ahogy kérted. Készen állsz a kihajózásra?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "Nem, nem, nem! Nekem kellene ezt kérdeznem. De úgy veszem, hogy készen állsz. Gyerünk, gyerünk. Te fogsz evezni a csónakkal. És ne számítson rendes kabinra! Te vagy az egyetlen oka, hogy megtesszük ezt a kitérôt.";
			link.l1 = "Nincs szükségem kényelemre. Csak vigyél oda.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...így Longway nem tudta kitalálni, hogy pontosan merre tart a Hajnalcsillag.";
			link.l1 = "Igen, már értem, hogy kerültél ebbe a zûrzavarba.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "Láttam egy brigget Guadeloupe vizein. Talán a Banten volt az. Megpróbálom kideríteni. Nos, most már elmehetsz, Longway. Hozd el nekem a " + sStr + ".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Kapitányom, minden rendben? Jöttem, amint Longway mondta, hogy szüksége van rám.";
				link.l1 = "Csak próbálom összerakni a dolgokat. Emlékszik annak a briggnek a nevére, amit a szigetnél láttunk?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "Látni akartál?";
				link.l1 = "Igen, uram. Emlékszik a hajóra, amit nemrég láttunk? Tudja meg a helyét és a nevét.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Emlékszem, de mi ez a hirtelen érdeklôdés egy brigg iránt? Ennek kiderítése eltarthat egy darabig.";
			link.l1 = "Helen, csak csináld, kérlek. És igen, tudom, hogy eltarthat egy darabig. Várni fogok.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "Nem, nem ellenôriztem. Nem, nem néztem meg. Mert fontos?";
			link.l1 = "Mm-hmm. Tudsz még többet megtudni? Tudnom kell, hol horgonyoznak most, ha még nem hagyták el Guadeloupe vizeit.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Mindenképpen. Csak figyelmeztetem, hogy eltarthat egy darabig. Viszek egy csónakot és pár embert, hogy segítsenek, rendben, Charles?";
			link.l1 = "Természetesen, Helen, köszönöm. Várni fogok.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Kapitány Úr, hívott?";
			link.l1 = "Igen, Alonso. Elhaladtunk egy brigg mellett a sziget elôtti vizeken, amikor visszamentünk Longway-hez. Nem tudta véletlenül a nevét?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "Nem, az a feladatom, hogy szemmel tartsam az újoncokat, és részt vegyek a fedélzeti elôôrsben. Különben is, nincs távcsövem, és nem voltunk olyan közel.";
			link.l1 = "Ez igaz. De ettôl függetlenül ki kell derítenem. Végezzék el.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Igenis, kapitány. Azt hiszem, fél nap alatt meg tudom csinálni.";
			link.l1 = "Siessenek. Várni fogok.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Öt órával késôbb...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Mindent megtanultam. Minden rendben volt, amíg távol voltam, kapitányom?";
				link.l1 = "Igen, jól vagyok, köszönöm, Helen. Mondja csak.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Hú, visszatértem. Megtaláltam a fogdát.";
				link.l1 = "Isten hozta újra itthon. Hol van és mi a neve?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "A Banten. Ez a név jelent magának valamit, ugye? Most a világítótoronynál van, és a legénységébôl néhányan partra szálltak. Megtámadjuk azt a hajót?";
			link.l1 = "Nem, ki kell derítenünk, hogy pontosan kik mentek partra. A szárazföldön megyünk a világítótoronyhoz. Tekintve, hogy már így is késésben vagyunk, itt az ideje, hogy elhagyjuk a kikötôt. Valami távoli helyen kellene lehorgonyoznunk. A Capster Beach jó lenne. Siessünk, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Nos, a brigg neve Banten, és a világítótoronynál horgonyoz. A legénység egy része ott kötött ki. Mit fogsz csinálni?";
			link.l1 = "Ahhoz, hogy ezt megtudjuk, észrevétlenül kell eljutnunk a világítótoronyhoz, és ezt csak gyalog tehetjük meg. A hajónknak biztonságos helyen kell lehorgonyoznia. Mit szólnátok a Capster Beachhez?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Jó ötlet. Charles, akarod, hogy veled menjek a világítótoronyhoz?";
			link.l1 = "Gondolkodom rajta, amíg a hajót mozgatjuk - így is elég fáradtak vagytok.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Visszajöttem, amint végeztem, Kapitány Úr.";
			link.l1 = "Nagyon jó. Jelentést, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "A brigg még mindig a szigeten van, pontosabban a világítótoronynál. A neve a tatján Banten. A legénységük egy része partra szállt.";
			link.l1 = "Szép munka, Alonso. Készítsd fel a legénységet a horgony felhúzására azonnal.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Készüljenek fel a partraszállásra is?";
			link.l1 = "Még nem. Ha a kapitányuk a világítótorony felé tart, talán a városban rejtôzik el, ha a tengeren támadunk. Elmegyünk a Capster Beachre, hogy biztosítsuk a hajónkat, aztán gyalogosan közelítjük meg a világítótornyot.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Kapitány úr, nézze! Valaki van a világítótoronyban.";
			link.l1 = "Jó, idôben érkeztünk! Siessünk és kapjuk el ôket. Alonsónak ma sok munkája lesz.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "De mi van, ha közben meghalnak?";
			link.l1 = "Mit javasolsz?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "Lopakodjunk be csendben, és hallgassuk meg elôször a beszélgetésüket.";
			link.l1 = "Kétlem, hogy ezt megtehetjük anélkül, hogy az ablakon keresztül észrevennének minket. De próbáljuk meg.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "HiddenImmortality");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Gondolj arra, amit mondtam. Gondolkodjatok erôsen. A pénz nem kérdés - persze bizonyos határokon belül. De még ez a határ is aranyhegynek fog tûnni számodra - a kínainak meg kell halnia! Már küldtem utána embereket, de hiába. Ezúttal azonban, ha összefognak az embereiddel...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Nézd, figyelnek minket! Ô az! Ô és az átkozott kapitánya!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "A fenébe veled, mocskos ázsiai... Annyi mindent kellett elviselnem miattad. És most, mindezért, meg fogok halni...";
				link.l1 = "Elvisszük az orvosunkhoz, parancsnok úr. Csak mondja meg, kivel beszélt - ez nagyon fontos.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "A neve... Joep van der Vink, ô... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Meghalt... Nos, legalább a nevét tudjuk. Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Ez egyáltalán nem lehet...";
			link.l1 = "Kicsit sápadtnak tûnsz, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway egészen biztos volt benne, hogy ô ölte meg van der Vinket tíz évvel ezelôtt\nElmenekülnek! A hajójuk gyors!";
			link.l1 = "Igen, egy csodálatos brigg... a mi szerencsétlenségünkre. Még ha idôben oda is érünk a hajónkhoz, mire felhúzzuk a vitorlákat és elkapjuk a szelet, már nem lesznek ott.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Ez lehet a vég...";
			link.l1 = "Nem, Longway. Figyeljen rám. Ha a szigetvilágban akarnak maradni, elôbb-utóbb biztosan összefutunk velük - kicsi a világ, és a Karib-tenger különösen kicsi. Amint újra a nyomukra bukkanunk, mindent eldobok, és utánuk megyek. Ezt megígérem. Hallottad, amit mondtam?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Igen, kapitány úr. Köszönöm, kapitány.";
			link.l1 = "Fel a fejjel, Longway. Vissza kell sietnünk a hajóra - a parancsnok halála hamarosan nagy hír lesz.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			ReturnOfficer_Longway();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Uram! Egy pillanat! Ön kapitány?";
			link.l1 = "Talán. Hogy találta ki? És mit akar?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Hát, errefelé csak hegyek és sûrû dzsungel van - nincs út a városba. Mégis itt vagy. Nem csak városnézésre jöttél, igaz?";
			link.l1 = "Jó megfigyelés. De még mindig nem mondtad el, hogy mit akarsz.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Á, igen! Kapitány, a hajónk szikláknak ütközött ebben az öbölben. Mi vagyunk az egyetlenek, akik túléltük...";
			link.l1 = "Sajnálom, uram. Azt akarja, hogy elvigyem valahova, ugye?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Igen... Nem lesz semmi baj, esküszöm. Csak tegyen ki minket Belize-ben, és onnan majd megoldjuk.";
			link.l1 = "Nincs messze, ugye? Ebben az esetben, üdvözlöm önöket a fedélzeten.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Sajnálom, de én a másik irányba megyek.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Köszönöm, kapitány! Ki tudja, mennyi ideig ragadtunk volna itt ön nélkül.";
			link.l1 = "Hát persze. Ne vesztegessük az idôt!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "De Belize olyan közel van! Nem tarthat sokáig, ugye?";
			link.l1 = "Sietek. Nem engedhetek meg magamnak semmilyen kerülôt.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Még egy rövidet sem? Csak Belize-be? Kérem, kapitány, ne hagyjon itt minket!";
			link.l1 = "Rendben, remélem, nem fogom megbánni. Mindenki a fedélzetre!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "C'est la vie. Kellemes napot, barátaim.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Még egyszer köszönöm, kapitány! Mi csak egyszerû matrózok vagyunk, szóval nem sokat tudunk ajánlani.";
			link.l1 = "Nos, legalább nem kellett túl messzire mennünk.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Emeljük poharunkat az egészségére, és gyertyát gyújtunk önért a templomban.";
			link.l1 = "Ez jobb, mint a semmi. Egészségetekre, fiúk!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Hallottátok? Végre elkapták! Végre biztonságban vannak a vizeink!";
			link.l1 = "Ez... jó hír? De kit fogtak el?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, maga a Szélzsák!";
			link.l1 = "Nem ismerem - mit csinált?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Nem tudod?! Nos, maga nyilvánvalóan nem angol, ezt látom. Ô egy kalóz, aki évek óta fosztogat minket és a spanyolokat a hajóján, a Sirályon.";
			link.l1 = "Kifosztja az angolokat és a spanyolokat? Ez szokatlan.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "Valóban. A parti ôrség soha nem tudta elkapni, de végül többet harapott, mint amennyit meg tudott rágni - elvesztette valami furcsa kereskedôhajó, ha elhiszed ezt.";
			link.l1 = "Ez mulatságos. Mi volt olyan furcsa a kereskedôhajóban?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Hát, ez csak egy hatalmas, ügyetlen gálya volt, kíséret nélkül! De hála ôrült kapitányának, Lutter ma énekli el az utolsó dalát - hamarosan felakasztják. El kellene jönnöd megnézni!";
			link.l1 = "Lehet, de egyelôre más dolgom van.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Kapitány úr!";
			link.l1 = "Egy spanyol kereskedô legyôzi a vakmerô kalózt... Ugye te is arra gondolsz, amire Longway gondol?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "A Hajnalcsillag...";
			link.l1 = "Valószínûleg - az egész szigetvilágban nincs még egy hozzá hasonló kereskedelmi kapitány.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Azonnal meg kell találnunk ôt!";
			link.l1 = "Meg kell találnunk! De nem látok egyetlen nehéz gályát sem a kikötôben. Próbáljunk meg beszélni a Szélzsákkal, mielôtt felakasztják. Lássuk, hogy kiérdemelte-e ezt a becenevet.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			ReturnOfficer_Longway();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Életben van még? Beszélhetünk vele?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "Mi az? - Nem tudom. Ó, igen. Életben van - a kivégzés még nem történt meg. Beszélhetnek vele - beszédesebb, mint valaha. De mostanában csak hülyeségeket beszél, leginkább magában. A szélzsák megôrült... Alig várom, hogy felakasszuk, mielôtt mindannyian megôrülünk a végtelen fecsegésétôl.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Köszönöm.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			ReturnOfficer_Longway();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "Ellopta a kincsemet!";
			link.l1 = "Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "A kincsemet most már hozzá kötöttem, tudod, hozzá! Nem tehetünk semmit! Mit akarsz?! El akarsz venni tôlünk még valamit? Semmi sem maradt! Meg fog halni! Vagy még rosszabb!";
			link.l1 = "Ki fog meghalni? Milyen kincs? Mindegy, a te hibád - te támadtad meg azt a gályát, nem pedig fordítva.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "Nem! Épp fordítva volt! Átkozott hidalgo! Ô az oka, hogy ebben a szarban vagyunk! Egyenesen felénk jött és tüzet nyitott ránk! Aztán elvette tôlünk!";
			link.l1 = "Tényleg? Ez nem meglepô. Mit tud még róla mondani? És... mit vett be?Ki az a 'nô'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "Ah-ah-ah!!! A-A-A-A-A!!!";
			link.l1 = "Látom, csak az idômet vesztegetem...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Kapitány, az engedélyével... Lutter! Kifelé! Vége a sornak, haver.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Kapitány, többet kell megtudnunk Sottáról és Lutterrôl. Kérdezôsködjünk.";
			link.l1 = "Jó ötlet, Longway. Úgysem tudtunk meg sokat az ordibáló embertôl.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "De jobb, ha Sottával kezdjük.";
			link.l1 = "Igen, ôt keressük. Gyerünk, menjünk.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Nem tudnak semmit!";
			link.l1 = "Nyilvánvalóan. De van elég, hogy elkezdjünk magunkban gondolkodni. Abból, amit hallottam, Sotta valószínûleg megpróbálja majd eladni azokat a stratégiai árukat, amikkel megjutalmazták, méghozzá hamarosan.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Pontosan!";
			link.l1 = "Útközben Port Royalban vagy Capsterville-ben kellene elfognunk. A kérdés csak az, hogy merre tart, és hol kellene megtámadnunk. Vagy talán a nyílt tengeren fogjuk elkapni.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "Nem! Longway úgy értette... Fermentelos egy tapasztalt kapitány. A nyílt tengeren való harc akárhogy is alakulhat. Nagyobb esélyünk lenne, ha a kikötôben csapnánk le rá.";
			link.l1 = "Igazad van, azt hiszem. Nem számít, mi történt valójában Matt és közte, Sotta veszélyes, és nem szabad alábecsülni.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Mi sem várhatunk!";
			link.l1 = "Ismét igazad van, Longway. Szóval azonnal húzzuk fel a horgonyt, aztán megtervezzük a következô lépésünket.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Kapitány úr, a Hajnalcsillag a kikötôben van!";
			link.l1 = "Igen, már észrevettem.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "Mi a terved?";
			link.l1 = "Még nem döntöttem. Öngyilkosság lenne az erôd ágyúi alatt partra szállni. És még ha el is foglaljuk a nehéz gályájukat, nem menekülhetünk el rajta. Van valami ötleted, Longway?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Igen, van. Horgonyt vethetnénk egy biztonságos öbölnél, és az éjszaka leple alatt csónakkal közelíthetnénk meg a gályát.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "Mi a helyzet a Félhold-öbölrel, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Szerintem a Portland-öböl jó lenne - elég közel és viszonylag biztonságos. Mit gondol?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Jó választás.";
			link.l1 = "Nagyszerû, ez meg van oldva. Kihagytunk valamit?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "Nem hiszem, kapitány úr. Csak jól fel kell készülnünk.";
			link.l1 = "Természetesen.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Ki a fasz vagy te, mi folyik itt? Mr. Holmes!";
			link.l1 = "Mister Holmes már nem dolgozik itt. És minden ajtót jól lezártunk. Szóval, egy darabig nem fognak minket zavarni, Mynheer Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "Micsoda? - Nem, nem, nem. Fermentelos? A nevem Edgardo Sotta!";
			link.l1 = "Uh-huh, ezt már hallottam korábban. Tudjuk, hogy nem ez az igazi neve, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos halott!";
			link.l1 = "Ha jobban belegondolok, túl fiatalnak tûnik. Nyilvánvalóan nem lehetett a Hajnalcsillag kapitánya tíz évvel ezelôtt. Szóval, mi történt Oliveiróval?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Megszabadultunk tôle. Ô is csak egy újabb probléma volt, amit el kellett takarítanunk - akárcsak az, aki melletted áll.";
			link.l1 = "Nos, mivel maga nem Fermentelos, talán még mindig tud válaszolni a kérdéseinkre. Keresünk valakit, akit elvett a barátomtól.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Nem fogok semmit sem mondani! Ezt soha nem fogja megbocsátani nekem.";
			link.l1 = "Most inkább azon aggódjon, hogy mi megbocsátunk-e magának...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Végre meghalt...";
			link.l1 = "Igen, így van. És ki maga, asszonyom? Akarata ellenére tartotta fogva? Együttérzek önnel; szörnyû megpróbáltatásokon kellett keresztülmennie...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Annabel Lutter vagyok. És hála Istennek, nem kellett sokat elviselnem, de értékelem az aggodalmát, uram...?";
			link.l1 = "Charles de Maure kapitány. Lutter, azt mondja...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Biztos hallott már Mattrôl. Szegény bolond... Én voltam a... hitvese.";
			link.l1 = "Ôszinte részvétem, Mrs. Lutter. Ön most már özvegy. Mi volt a leánykori neve, ha nem titok?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Nem volt. Nézzen meg közelebbrôl. Szegény anyám sötét bôrû rabszolgalány volt a kalózoknál. Senki sem tudja, hogy ki volt az apám, ezért nem fáradoztak azzal, hogy rendes nevet adjanak nekem.";
			link.l1 = "Akkor miért nem nyúlt hozzád senki? Ne érts félre - örülök, hogy nem történt meg. De mégis, ez... szokatlan.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "Igazad van. De nevezzük a dolgokat a rendes nevükön. Nem vagyok elkényeztetett nemesasszony, egy rabszolga lánya vagyok. Nem fogok elájulni egy nehéz beszélgetéstôl.";
			link.l1 = "Én sem vagyok a kényeztetés híve. De folytassa, kérem. Miért nem nyúlt a legénység a rabszolgalány lányához? Nem ismeri az apját, és úgy tûnt, nem is érdekli.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Gondolom, nem. Mivel tudsz Mattrôl, tudod, hogy egy ideig Levasseurnek dolgozott?";
			link.l1 = "Igen, hallottam róla, amikor a Hajnalcsillagot kerestem. De mi köze van ennek ehhez? Mondjon el mindent, kérem.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Még mindig nem érti, ugye? Úgy tûnik, nem hallott Levasseur... preferenciáiról?";
			link.l1 = "Nem hallottam, de mi köze van ennek ahhoz, hogy...?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Ó, azt hiszem, mindent el kell mondanom. Üljön le, ha túl befolyásolható, uram. A helyzet az, hogy sok nôvel lefekszik, és...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "A felesége nem messze van tôle, és szinte bárkivel lefekszik.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Ó, ne...";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Nos, tudja, mit mondanak... ahogy a férj, úgy a feleség. De nem, biztos vagyok benne, hogy ennél sokkal tovább ment.";
			link.l1 = "És milyen messzire?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "A szarkazmusa nem helyénvaló, uram. Fogalma sincs, mirôl beszélünk.";
			link.l1 = "Jól van, jól van, sajnálom. Folytassa, kérem.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "Ez nem csak a házastárs megcsalása. Nôket vesz el akaratuk ellenére. És ez nem csak egyszeri visszaélés. Elrabolja a lányokat, és az egyik borospincéjében tartja ôket.";
			link.l1 = "Szóval rendszeresen szerez rabszolgalányokat? És maga állítólag az egyikük volt?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Ez utóbbiban igazad van. De sajnos az elsôben nem. Neki nincs szüksége rabszolgákra. Levasseur ôrült - a maga módján, nem úgy, mint az én Mattem. Francois teljesen birtokolni akar egy nôt, testestül-lelkestül. És persze nem a szerelemrôl volt szó. Szabad nôkre volt szüksége, hogy megtörje az akaratukat. Élvezte nézni, ahogyan idôvel változik a külsejük, a viselkedésük, a beszédmódjuk...";
			link.l1 = "Undorító...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Máris rosszul érzi magát egy kicsit. Most képzelje el, milyen lehetett azoknak a nôknek. Hallottam minderrôl, és nem csak Mattetôl. Levasseur-nek egyszer volt egy portugál nemesasszonya...";
			link.l1 = "Elfordította a tekintetét, és hallgatott. Mondj el mindent. Mindenfélét láttam az Óvilágban és a szigetvilágban töltött idôm alatt is. Most már semmi sem lep meg.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Elég, nem akarom tudni, mi történt vele. Remélem, azok a nôk nem szenvedtek túl sokáig a kezei között.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "De ilyesmirôl még nem hallott. És remélem, soha nem is látja. A nôt még mindig büszkén és töretlenül hozták hozzá, annak ellenére, hogy - ahogy Matt elmondta - Levasseur emberei megerôszakolták egészen Tortugáig, miután elfoglalták a férje Campeche melletti ültetvényét - a férfi vérzésbe halt bele, miután azok a szörnyetegek mindkét térdébe lôttek...";
			link.l1 = "Egy erôs nô... De azt mondta, hogy Levasseur általában nem nyúlt azokhoz a nôkhöz, akiket magának akart.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Akiket kifejezetten kért, azokat békén hagyta. De Senora Leontina egy ajándék volt. Váratlan és kellemes mindannyiuk számára. Így hát kényeztették magukat...";
			link.l1 = "Értem...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Azt hiszem... Matt Francois' egyik kedvencévé vált. Meghívták Levasseur egyik titkos estélyére... A lakoma alatt az egyik kalóz panaszkodott, hogy nincs elég nô. Levasseur nevetett, majd...";
			link.l1 = "És aztán? Mi történt?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...aztán elôvették a nôt. Pórázon! Megverték, megvakarták a hátát, bekötötték a szemét és betömték a száját. Amikor levették a szájkosarat, csak annyit mondott...";
			link.l1 = "Valami szörnyûséget, gondolom. Megátkozta a férfit minden erejével?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Bárcsak... Dona Leontina csak suttogott, 'Mit kíván az uram?'";
			link.l1 = "Azt hiszem, rosszul leszek. Matt elmondta, mi történt vele utána?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Meggyilkolták, természetesen. De nem Levasseur keze által. Úgy dobta ki, mint egy kóbor kutyát. Az egyik kapitánya lôtte le. Mielôtt meghalt, csak egy szót mondott...";
			link.l1 = "Egy átkot? Egy imát?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "Nem. 'Köszönöm...'";
			link.l1 = "Hálásnak lenni a halálért ilyen kínok után... Amit el kellett viselnie... és a hozzá hasonlóknak abban a szörnyeteg barlangjában...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur különösen megvetette a rabszolgákat és a sötét bôrû nôket - azt mondta, nincs bennük semmi törni való. Nem sokáig bírták nála, ahogy az indiánok sem - kivéve néhány különösen makacs példányt. De a vadság és a lázadás sem volt megoldás - megölte azokat, akik túl hamar próbáltak a kedvében járni, és azokat is, akik túl sokáig dacosak maradtak.";
			link.l1 = "Ez borzalmas... Mondd csak, Levasseurnek voltak valaha ázsiai nôk?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "Legalábbis én nem hallottam róla. Ami engem illet... Már mondtam, hogy nem szerette a sötét bôrû nôket. Ezért amikor Matt Francoisnak dolgozott, nyíltan sétált velem Tortuga utcáin. Egyszer még a rezidenciára is elvitt.";
			link.l1 = "De Levasseur amúgy is a rabszolgája akart lenni...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Pontosan... Nem tudom, miért kedvelt engem annyira... Amikor Matt rájött, elmenekült a szigetrôl, amint megtudta. Soha nem tért vissza Tortugára. Lehet, hogy egy kicsit ôrült volt, de szeretett engem. A kincsének nevezett...";
			link.l1 = "Szóval erre gondolt, amikor azt mondta, hogy Sotta elvette tôle a kincsét!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Heh, tényleg ezt mondta? Ó, Matt... De úgy tûnik, sosem akartunk együtt megöregedni. Ha Levasseur szemet vetett egy nôre, bármit megtett, hogy megszerezze, nem számított a háttere vagy az ára. Sotta az egyik kapitánya volt, és azt tette, amit mondtak neki.";
			link.l1 = "Értem. És most mit szándékozik tenni, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Elfutni. Valahová, ahol Levasseur emberei nem érnek el. Megváltoztatom a nevem. Álcázom magam...";
			link.l1 = "Remélem, sikerrel jársz. Minden jót kívánok, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Pénzre lesz szükséged, hogy megszervezd az átutazást. Fogd ezt. Itt van tízezer pezó.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Többre lesz szükséged, mint egy kis pénz. Nem mindenki hajlandó segíteni egy sötét bôrû lánynak, még egy félvérnek sem. Tessék, fogj száz dublont - keress egy hajót és bújj el.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "Te is! Viszlát, kapitány.";
			link.l1 = "Viszontlátásra.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "I... Nem tudom, mit mondjak. Matt-en kívül senki sem volt még ilyen kedves velem.";
			link.l1 = "Talán ez egy jel. Hogy mégiscsak boldogan fogsz megöregedni valahol. Viszlát.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Igazad van. Köszönöm szépen ezt. Életem végéig imádkozni fogok érted.";
			link.l1 = "Köszönöm, hogy eljöttél. Goodspeed.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Az az ember... Nem, ô már nem férfi. Ô egy szörnyeteg. Egy szörnyeteg. Így kínozni a nôket...";
			link.l1 = "Tudom, mire gondolsz, Longway. De hallottad - soha nem volt még sárga bôrû nôje.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "De ismerte az egész csoportot! Van der Vink, Fermentelos, Sotta... Csak a naplójában olvastunk róla. Mi van, ha az a bizonyos 'she' a... ô?";
			link.l1 = "Ki tudja... Egy nô, aki bosszút akar állni Fermenteloson - könnyû megérteni, miért gondolja ezt. De lehetett volna bármelyik nô, akinek az életét Oliveiro tönkretette. Nem kell, hogy a húgod legyen. Még csak nem is kell, hogy sárga bôrû nô legyen.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Ön... nem hajlandó megpróbálni, kapitány úr? Az utolsó pillanatban...?";
			link.l1 = "Nem, Longway. De hogy képzeled? Nem valószínû, hogy Levasseur válaszolna a kérdéseinkre. És Tortuga körül szaglászni túl veszélyes.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "Akkor mit javasolsz?";
			link.l1 = "Várjon. Tudjuk, hogy Levasseur nem szereti az olyan nôket, mint a húgod. Szóval egyelôre takarékoskodhatunk az erôforrásainkkal. Türelem és erô. Francois kemény dió, nem utolsósorban a 'turtle.' miatt, de Svenson segítségével a mi feltételeink szerint beszélhetünk vele. Megígértem, hogy segítek megtalálni a húgodat, és szándékomban áll betartani. Hiszel nekem, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Hmm... Igenis, kapitány úr. De Longwaynek van még egy kérése önhöz.";
			link.l1 = "Mi lenne az? Ugye nem tervezed, hogy megint egyedül mész el? Legutóbb nem végzôdött túl jól.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "Egyáltalán nem, kapitány úr. Most már tudom, hogy sajnos egy magamfajta ember nem tehet semmit egyedül egy olyan világban, amit fehér emberek irányítanak. Longway arra kéri, hogy dokkoljon Capsterville-ben, és adjon át egy üzenetet Georges Gravelnek, amelyben arra kéri, hogy amíg ön készülôdik, tudjon meg bármit.";
			link.l1 = "Értelmes ötlet, Longway. Meg fogjuk tenni.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Kapitány úr, van valami, amit Longwaynek meg kell kérdeznie...";
			link.l1 = "Elfelejtette megírni a levelet? Beszélhetsz Gravel-lel.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "Nem, a levél készen van. De Longway úgy gondolta, jobb, ha nem bolyong egyedül a városban. Kapitány úr... átadná a levelet Georges-nak a nevemben? Kérem...";
			link.l1 = "Úgy nézek ki, mint egy futár? Vagy ön itt a kapitány?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Kapitány úr...";
			link.l1 = "Ha ha ha ha, csak vicceltem, Longway! Emlékeztessen, hol találom ezt a Kavicsot?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "A templomban dolgozik.";
			link.l1 = "Rendben, majd én elintézem.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, kedves Charles, valami baj van? Aggódónak és... fáradtnak tûnsz, rendben.";
			link.l1 = "Ó, nem, nem, nem, Mary, jól vagyok. Ez csak... ez a Tortuga küldetésem. Úgy tûnik, zsákutcába jutottam... megint. És az a Sharp akarata határozottan megvisel, az isten szerelmére' sake. De mindegy.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "De mindegy. Milyen küldetés? És mi köze van ennek Sharphoz? Nem értek semmit!";
			link.l1 = "Túl sok a kérdés, Mary. Ez nem a megfelelô hely az ilyen beszélgetésekre. Beszéljük meg a kocsmai szobában? Pont ahogy szereted, ne lássanak és ne gondoljanak rá. Elmondom, mit csináltam az elmúlt évben.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "Jól van, rendben! De vigyázz: ha valamit rejtegetsz...";
			link.l1 = "Egyáltalán nem! Menjünk, úgyis van idônk...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Milyen furcsa, nem igaz, Charles? Állítólag az enyém ez a sziget, de egyáltalán nem érzem úgy, hogy az enyém lenne.";
			link.l1 = "Gondolod?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Ó, az a vigyorod... Tudod, hogy kell bánni egy lánnyal. De mi a baj veled? Teljesen rossz az arcod!";
			link.l1 = "Miért? Miért? Ez a szokásos arcom, nagyon jóképû is.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, hallom a hangodon, hogy mostanában nem vagy valami jól.";
			link.l1 = "Sok dolgom van, fôleg Longway miatt. Egyszerûen kimerült vagyok. De túl késô feladni, fôleg, hogy ígéretet tettem neki és apámnak.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Nem értem... Mi köze van ehhez Longway-nek? És milyen ígéreteket tettél?";
			link.l1 = "Ha már beszélgetni akarunk, tegyük meg a kocsmában, béreljünk ki egy szobát. Távol a többi embertôl.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "Rendben, menjünk. Úgysincs más dolgunk, legalább egy kis idôt együtt tölthetünk.";
			link.l1 = "Menj elôre, drágám!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Nézd, milyen édesen alszanak egymás karjaiban! Csodálatos!";
				link.l1 = "Féltékeny?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kelj fel és ragyogj! Hogy aludtatok, szerelmespár?";
				link.l1 = "Jól, köszönöm a kérdést. És ti hogy aludtatok, fiúk?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ez egy buta kérdés, nem gondoljátok?";
				link.l1 = "Így van. És hülyeség volt a részedrôl. Akarod tudni, miért?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Azt mondják, éles a nyelved, Charles de Maure.";
				link.l1 = "És nem csak az én nyelvem. Akarja megtudni? De mondd csak, miért nem támadtál, amíg aludtunk?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "És miért is?";
				link.l1 = "Nem kellene reggel feldühítened Máriát. Hamarosan megtudod, miért.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Egyszerû! Sötét van, tudod, így nem tudtuk volna megmondani, melyikôtök a lány.";
				link.l1 = "Szemétláda.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Veled ellentétben én nem félek a nôktôl. Ha már itt tartunk - fiúk, vigyétek el épségben, vagy a hugenotta nôkké változtat minket!";
				link.l1 = "Hu... ki?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Legalább úgy nézek ki, mint egy férfi. Fiúk, vigyétek a szôkét élve - a hugenotta vár rá.";
				link.l1 = "Hu... ki?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ki volt az, Charles? Ki a fene az a hugenotta? Tényleg...?";
				link.l1 = "Csak egy van, Mary. És jobb, ha...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... mi volt ez? Egy hugenotta? Ez az a férfi, akire gondolok?";
				link.l1 = "Attól tartok, igen, Helen. Meg kell...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Hallod ezt? Valaki jön, rendben. Valószínûleg a halottak barátai.";
				link.l1 = "Akkor majd meglátjuk, hogy csatlakoznak hozzájuk. Készüljetek...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Hallod ezt? Lépéseket.";
				link.l1 = "Valóban hallom. Álljatok mögém.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Kapitány úr, hölgyem " + sStr + ".";
			link.l1 = "Longway?! Azt hiszed, csak úgy besétálhatsz a szobánkba? Mi lenne, ha...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Hm, elnézését kérem, kapitány úr. Azt hittem, hogy bezárta volna az ajtót, ha így elfoglalt. De Longway nyitva találta.";
			link.l1 = "Törött, nem nyitva. De mondd csak, barátom, miért vagy ilyen átkozottul nyugodt? Holttestek vannak a földön, fegyverünk van, és maga...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Nos, én már hozzászoktam.";
			link.l1 = "És ezzel nem tudsz vitatkozni, ugye? De tényleg, nem hallottad a harc hangjait idefelé jövet? Nem láttad, hogy ezek a fickók besétáltak a kocsmába és felmentek a lépcsôn, pont elôtted? ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "Nem, kapitány úr. Nem láttam idegeneket a folyosón, amikor feljöttem ide.";
			link.l1 = "Ez nevetséges egybeesés. Szóval mit akar, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Sürgôsen szükségem van egy hajóra és legénységre, kapitány úr.";
			link.l1 = "Mit akarsz, Longway? Mit akarsz, Longway? Végre Chang Xing nyomára bukkantál? Ebben az esetben, menjünk érte most azonnal, együtt.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Chang Xinget sajnos nem. Hanem... Joep van der Vink. Georges Gravel küldött egy üzenetet, és én akkor kaptam meg, amikor a faluban sétálgattam, amíg te... a hölgy mellett pihentél.";
			link.l1 = "Igen, nagyon jól pihentem, azt mondhatom. De miért kellene most elválnunk, Longway? Átkozottul hosszú listánk van fontos feladatokról, amiket el kell végeznünk, és veszélyes embereket kell megölnünk.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink nem olyan veszélyes, mint Levasseur. Különben is, egyszer már legyôztem ôt. És újra le fogom gyôzni. Ezúttal, hogy biztos legyek benne, hogy végleg meghalt. Nem akarom, hogy mindannyian értékes idôt pazaroljunk rá. El kellene menned Tortugára, és megkérdezni a fontos embereket, hogy mire van szükségünk. Én magam fogom elfogni van der Vinket. Kapitány úr, erre nem érdemes az idejét vesztegetni, pedig én is voltam egyszer kapitány. Majd én elintézem.";
			link.l1 = "Hmm, igazad van, Longway. A Van der Vink talán nem olyan veszélyes, de a 'Banten' az egyik leggyorsabb hajó a szigetvilágban. Nem minden hajó képes elkapni ôt. És mi a helyzet a legénységgel? Hogyan akarsz ilyen gyorsan és egyedül embereket gyûjteni?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Ismerem a megfelelô helyet, és a Compnay is ott áll. Vagy legalábbis úgy teszek, mintha tudnék, ahogy Georges-szal tettem. A Társaság... Mynheer Rodenburg igénybe vette a szolgáltatásaikat, amikor sürgôsen szüksége volt harcos emberekre, profi legénységre, akik nem kérdezôsködnek.";
			link.l1 = "Egy bérelt hajó legénysége, akkor... Van értelme, hogy létezik ilyesmi. És mennyibe fog kerülni?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Két és fél ezer. Azonnal és azonnal.";
			link.l1 = "Ennyi? Ennél több kell ahhoz, hogy egy kocsmából egy teljes létszámú, rendes matrózokat vegyenek fel, különösen egy nagy hajóra. Úgy tûnik, Rodenburg és ügynökei különleges helyeken különleges árakat szabnak.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Én dubloonokra gondoltam, kapitány úr.";
			link.l1 = "MICSODA?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Jól hallotta, kapitány úr. Ez fontos. Nem kérnék ekkora összeget egy apróságért.";
			link.l1 = "Igen, hallottam, de még mindig nem tudom elhinni. Valóban különleges árak. Elfogadnak pezót?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Igen... a fehérektôl. Longway-nek lehet, hogy gondot okozna, de... Azt hiszem, meg tudom ôket gyôzni, ha elég erôsen kérem. Mindig van rá mód.";
			link.l1 = "Hát, ez már valami. És ez csak a legénységnek szól... És még egy hajóra is el kell jutnod. Valószínûleg szintén valami 'különleges helyen'? Félek megkérdezni, hogy mennyibe fog ez nekünk kerülni...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Nem egészen, kapitány úr. A legénység saját hajóval érkezik.";
			link.l1 = "De?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "A 'Meifeng'. döntô tényezôvé válhat - a szigetvilágban nincs nála gyorsabb hajó. És ô... az enyém volt, tehát ismerem. Kölcsönadná nekem, kapitány úr?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Tessék. Két és fél ezer dublont. Ha elhozza nekem van der Vink fejét egy arany tálcán, ha ha ha ha ha ha!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Nincs nálam ennyi dublon, Longway. És kétlem, hogy ennyi lenne a hajón - egy halom aranyról beszélsz. De pezó, persze. Háromszázezer pont annyi, amennyire szükséged van.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Tudod mit, Longway... Tényleg azt akarod, hogy egy ostromflotta felfegyverzésére elegendô pénzt fizessek, csak azért, hogy te egy közönséges gengszter ellen harcolhass?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Ó... Longway szívbôl köszöni, kapitány úr! De akkor is, mi van a 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Mi van vele? Barátom, beverted a fejed idefelé jövet? Most is a flottánkban van!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Ezen még gondolkodnom kell, Longway.  Mennyi idônk van, hogy elkapjuk van der Vinket?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Kapitány úr, egy kis hibát követett el. Kétszázötvenezer pezó lenne.";
			link.l1 = "Én nem; ez Charles de Maure különleges árfolyama, ha a barátainak segítségre van szükségük, ha-ha. Adok neked plusz pénzt, hogy mindenre legyen elég.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Köszönöm szépen, Uram. Kapitány... De mi van a 'Meifenggel?'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Mi van vele? Barátom, beverted a fejed idefelé jövet? Most is a flottánkban van!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Ezen még gondolkodnom kell, Longway.  Mennyi idônk van, hogy elkapjuk van der Vinket?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Nincs más lehetôség, kapitány úr, kérem, nyugodjon meg...";
			link.l1 = "Ó, még nem kezdtem el. A következô a helyzet. Ötvenezer pezó. Ez éppen elég arra, hogy vegyünk egy brigget a hajógyárból, felkészítsük a csatára, és még legénységet is felvegyünk.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "De, kapitány úr. Talán elég lesz egy fehér kapitánynak is! Nem mindenki fog beleegyezni, hogy Longway-jel üzleteljen. Keményen alkudozni fognak, mielôtt bármit is eladnának nekem!";
			link.l1 = "Szóval, legyetek meggyôzôek! Ön elég ügyes az alkudozásban, a kezdeti... ajánlatából ítélve. Még mindig itt van? Fogja ezt a pénzt és menjen, ha már ennyire sürgôs, ahogy mondja!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Igenis, kapitány úr...";
			link.l1 = "És ne nézzen így rám. Késôbb találkozunk Tortugán. Sok szerencsét!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Nem, kapitány úr. Persze, emlékszem. Longway csak azt kérdezte, hogy készen áll-e megosztani velem.";
			link.l1 = "Igen, kész vagyok. Elvégre van der Vink ugyanúgy benne van a húgod szerencsétlenségében, mint a többi ember a listánkon. Szóval nagyon fontos, hogy elkapjuk. Átadom neked a Meifeng parancsnokságát.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Nem tudom elhinni... Köszönöm, kapitány úr!";
			link.l1 = "Á, semmiség. Valaha a te hajód volt, erre mindig emlékezni fogok. Nos, menj csak. Öld meg a rohadékot. Elmegyek Tortugára.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			Notification_Approve(true, "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "Az idô sürget, kapitány úr. Nem szabad elvesztegetnünk - Chang Xingnek szüksége lehet a segítségünkre...";
			link.l1 = "Tudom, Longway. Mégis, pontosan mennyi idônk van, hogy elkapjuk van der Vinket?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Néhány hónap - körülbelül ennyi ideig járja a szokásos útvonalat, mielôtt eltûnik egy idôre. Ez az ô szokása, ahogy Gravel is tájékoztatott a levelében.";
			link.l1 = "Rendben. Akkor menjünk a hajóhoz...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Attól tartok, az elôkészületeket azonnal meg kell kezdenem, kapitány úr. Hogy rögtön indulhassunk, amikor a Meifenget megkapom. Elôzetesen tárgyalnom kell az emberekkel. ";
			link.l1 = "Szóval hol találkozunk?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Itt. De találkozhatunk a hajógyárban is, ha ez önnek megfelel.";
				link.l1 = "És miért én vagyok az egyetlen, aki nem tudta, hogy itt egy teljes legénységnyi harcoló embert fel lehet bérelni a megfelelô árért?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Ezeknek a zsoldosoknak korábban Isla Tesorón volt a helyük, de kénytelenek voltak ide költözni.";
				link.l1 = "Már értem, miért. Szóval hol keresselek meg La Vegában?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Mert nagyon kevesen tudnak róla. És még kevesebben engedhetik meg maguknak. Mynheer Rodenburg sokáig az egyetlen ügyfelük volt.";
			link.l1 = "Értem. Rendben, Longway. Ott találkozunk.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "A kocsmában, kapitány úr. Hol máshol lennék?";
			link.l1 = "Igen, így van. Akkor késôbb találkozunk, Longway! Vigyázz magadra.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Kapitány úr, tájékoztatom, hogy a legénység készen áll. Még egy utolsó dologgal kell foglalkoznunk. What about the 'Meifeng'?";
			link.l1 = "Eddig nem igazán választottam hozzád méltó hajót, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "Háborús szkúner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'" + sStr + "' a tiéd.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "Mi van a 'Meifeng'? Gondoltad, hogy hagytam ôt veszni?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "Van egy... különleges hajóm a számodra, Longway. Egy gyorsat. És még a Meifengnél is halálosabb. Ez egy harci gálya, a 'Flying Heart'..";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Szereted a xebeceket, Longway. És a polákok? Különösen ezt, a, 'Torero'. Persze nem regattákra épült, de elég erôs.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Be kell vallanom, nem gondoltam, hogy egyszer méltó felhasználása lesz ennek. Mit gondolsz errôl a gályáról? A hatalmas 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "Ez nem a 'Meifeng', kapitány úr! Mi történt a Meifenggel?";
			link.l1 = "Hosszú út! " + sStr + " veszélyben van! És a húgod is! És te még morcos vagy, hogy nincs ilyen hajód?! Bárki boldog lenne egy ilyen hajóval! Vedd a parancsnokságod alá, és mutasd meg van der Vinknek, mire vagy képes.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Rendben... Remélem, az Ég szerencsét küld nekem. Ahogy én is remélem ugyanezt neked a Tortugán. Viszlát, kapitány úr.";
			link.l1 = "Biztos vagyok benne. Viszlát, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Nem, kapitány úr. Persze, emlékszem. Longway csak azt kérdezte, hogy készen áll-e megosztani velem.";
			link.l1 = "Én vagyok. Végül is van der Vink ugyanúgy benne van a húgod szerencsétlenségében, mint a listánkon szereplô többi ember. Szóval nagyon fontos, hogy elkapjuk. Átadom önnek a 'Meifeng'.parancsnokságát.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "Nem tudom elhinni... Köszönöm, kapitány úr!";
			link.l1 = "Á, semmiség. Valaha a te hajód volt, erre mindig emlékezni fogok. Nos, menj csak. Öld meg a rohadékot. Elmegyek Tortugára.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "I... Én nem parancsolhatom ezt, kapitány úr. Longway még mindig törôdik az életével, a lelkével és a józan eszével.";
			link.l1 = "Ha ha ha ha, Longway! Ugyan már, nem tudtam, hogy ennyire babonás vagy. De mindegy is, az átok feloldódott, úgyhogy nincs mitôl félned.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "De vajon van der Vink tudja ezt? Úgy fog futni, mint egy rémült nyúl, amint meglátja azt a hajót.";
			link.l1 = "Ebben igazad van. Rendben, találunk valami mást.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "Én magam még sosem vitorláztam polakreppel, amikor kapitány voltam. Érdekes, de most a sebesség a legfontosabb, nem a teljesítmény.";
			link.l1 = "Ez igaz, de végül is ez egy polkorrektség. Lehet, hogy nem olyan gyors, mint a 'Banten', , de olyan szögekbôl is elkaphatja a szelet, amilyenekbôl ôk nem. Sôt, jobban, mint ahogy a 'Meifeng' maga valaha is tudta. Szóval használd ezt ki.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Still... the 'Meifeng' was better... Kár, hogy hagyta elpazarolni, kapitány úr. Sok szerencsét a Tortugán.";
			link.l1 = "Neked is, Longway. Köszönöm. Köszönöm.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "Hogy ez lehet a legszokatlanabb gálya a szigetvilágban, kapitány úr. Tudok vele bánni, de lassabb, mint a 'Banten'...";
			link.l1 = "Nos, nem Joep-pel versenyezel egy regattán, ugye?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Ahogy akarod. But the 'Meifeng' was better... Kár, hogy hagyta elpazarolni, kapitány úr. Sok szerencsét a Tortugán.";
			link.l1 = "Neked is, Longway. Köszönöm. Köszönöm.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Értékelem az aggodalmát, kapitány úr, de kérem, siessen - nincs sok idônk.";
			link.l1 = "Tudom, tudom. Tudom. De ugye nem akarja, hogy a vadludakat üldözzük? Rendben, keresek egy megfelelô hajót.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Már majdnem ott vagyunk, Charles. Eldöntötted már, hol kezded? Talán van értelme, hogy megkérdezzük az embereket az utcán...";
			link.l1 = "Talán igen. De nem nekünk - nekem. A fedélzeten maradsz, Helen.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, persze, engem még mindig nyugtalanítanak azok a gazemberek, és amit mondtak, és van értelme, hogy a legénység védelme alatt maradjak... De attól, hogy egyedül mész a fenevad barlangjába, nem érzem magam nagyobb biztonságban.";
			link.l1 = "Megértem. De ha a dolgok rosszra fordulnak, sokkal könnyebb egyedül menekülni, tudva, hogy biztonságban vagy. Ez parancs, Helen. Várj meg itt, és próbálj meg nem aggódni.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Itt van Tortuga, Charles, rendben. Alig várom, hogy bekopogjak néhány ajtón, és megkérdezzem, mit akart tôlem az a kövér szamár...";
			link.l1 = "Pontosan ezért maradsz a fedélzeten, kedvesem.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "Ez nem lehet igaz! Azt hiszed, hogy hagylak egyedül partra szállni?";
			link.l1 = "Azt hiszem, ha Levasseur úgy dönt, hogy befejezi azt, amit a zsoldosai nem tudtak, akkor nem lesz esélyünk visszavágni. Nem akarom feleslegesen provokálni, fôleg, hogy a célpontom nem ô, hanem Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Szóval most már be vagyok zárva, rendben?";
			link.l1 = " Nem parancsolom, hanem kérem, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "Mi van, ha valami történik veled annak a szaros szigetnek valamelyik sikátorában?";
			link.l1 = "Akkor megígérem, hogy nem játszom a hôst. És a tudat, hogy biztonságban vagy, segít gyorsabban futni. Szóval várj meg a hajón, és az Isten szerelmére, ne menj a partra, bármi is történik.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Ki vagy te? Kétlem, hogy csak azért sétáltál át a parton, hogy beszélgessünk.";
			link.l1 = "Így van, Mary. Charles de Maure. Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "A Charles de Maure? A francba, csak ne keverjen bele semmi gyanúsba. Igen, én vagyok az. Szóval, mit akarsz?";
			link.l1 = "Azt mondták, hogy Joep van der Vink barátja vagy, és...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Ki mondta ezt neked? Kiöntöm a belüket. Hát, ismerjük egymást, ennyi az egész. Nem akarok semmi bajt, mert keresztbe tett neked.";
			link.l1 = "Heh, gyorsan lemondasz a barátaidról...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Ne gondolj ilyet. Nem félek tôled. De minek bajlódni, vagy akár csak csinálni? Nem ismerem Joepet olyan közelrôl, mint ahogyan azt mondták. Ôt keresed?";
			link.l1 = "Igen, olyasmi. Tudom, hogy már elhagyta Tortugát, de nem ártana többet megtudni róla - hol járt, kivel beszélt. Tud segíteni?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "Neked úgysem segítene, szóval... miért ne? Egy bordélyházban volt. A bordélyházban. Szerintem megengedheted magadnak, ezért mesélek neked róla.";
			link.l1 = "Egy új bordélyház? Egy már nem elég neked?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Hát, nem új, de nem sokan tudnak róla. És csak kevesen engedhetik meg maguknak. Azt hiszem, eljött a te idôd. De figyelmeztetlek - csak dublonokat fogadnak el. Ha ezüstöt csúsztatsz, kapsz egy rúgást a seggedbe.";
			link.l1 = "Én is gondoltam. És mit is mondtál, hol van ez a bordélyház?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "Ismered azt az épületet az oszlopokkal? Az az. És micsoda háziasszonyuk van! Sárga bôrû, olyan jóképû! Huh, látom, máris csorog a nyálad, mi?";
			link.l1 = "Heh-heh, olyasmi. Köszönöm, Rober. Ma nem volt semmi baj - nagy segítségemre voltál.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "Végre visszatértél, Charles! Nem találtam helyet magamnak, rendben!";
			link.l1 = "Nem maradok sokáig, Mary. Van egy kis elintéznivalóm... Nem akarlak bizonytalanságban tartani - ez Longway ügye. Meg kell látogatnom egy helyi bordélyházat.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Tudtam, hogy nem kellett volna hagynom, hogy egyedül menj a partra. Vagy elfelejtetted feltenni a kalapodat, és a fejed felforrósodott... Vagy megütötted, rendben!";
			link.l1 = "Mary, figyelj rám. Lehetséges, hogy ennek a létesítménynek a tulajdonosa Longway húga. Hogy biztosra menjek, meg kell látogatnom ôt, de csak ennyit teszek. Ezt nem tehetem meg anélkül, hogy bemennék. De nem akarom, hogy olyasmit gondoljon, amit nem kellene.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Biztos, hogy nem hazudik nekem, Charles?";
			link.l1 = "Mary, nézd meg a dolgot így... Hallottál már olyanról, hogy egy férfi figyelmezteti a szerelmét...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Hagyd abba, Charles, nem is akarok erre gondolni. Hiszek és bízom benned. És remélem, hogy nem maradsz ott tovább, mint ameddig muszáj.";
			link.l1 = "Egy perccel sem tovább, drágám, ígérem. Be és ki, majd meglátod.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles! Még gyorsabban visszajöttél, mint vártam. De mi történt? Nem nézel ki jól... Megtudtál valamit Joep van der Vinkrôl?";
			link.l1 = "Még nem. Megtudtam néhány dolgot, de ha tovább akarok menni... El kell mennem egy... bordélyházba. Persze nem azért, amire gondolsz.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Egy bordélyház? Nem tudtam, hogy ezek a helyek a nyilvánvaló dolgokon kívül mást is kínálnak.";
			link.l1 = "Beszélnem kell a tulajdonossal, ennyi az egész. És ez nem akármilyen bordélyház. A pletykák szerint ez egy nagyon drága intézmény, csak a felsôbb körök tagjainak...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Nos, akkor ez pont neked való, drágám. Ó, csak viccelek. De azért nem vagyok elragadtatva, hogy oda mész. De...";
			link.l1 = "Ígérem, hogy szigorúan Longway ügyében megyek. Könnyen lehet, hogy a hely tulajdonosa a húga. Nem maradok ott sokáig.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Ahogy óhajtod. Nem vagy köteles tájékoztatni engem az ilyen dolgokról. Soha nem ígértem meg, hogy nem fekszem le mással. És mégsem teszem. Mert ez olyasmi, amit természetesnek veszek.";
			link.l1 = "Más körülmények között magammal vittelek volna, de...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "Kösz, de nem, köszönöm. Charles, ne aggódj. Nem vagyok egy hülye féltékeny lány. Nos, talán féltékeny, de nem hülye. És én hiszek neked. Hülye én!";
			link.l1 = "Köszönöm, Helen. Mindjárt jövök.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "Ó, egy új arc a létesítményünkben? Üdvözlöm, monsieur. Étel, érlelt bor, forró fürdô - mindez várja Önt, ha megengedheti magának, hogy valamelyikünkkel töltse az idejét.";
			link.l1 = "Köszönöm a fogadtatást, mademoiselle. De nem ezért vagyok itt. Keresek valakit...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "Csak a szívvel lehet helyesen látni; ami lényeges, az a szem számára láthatatlan.";
			link.l1 = "Gyönyörû. Még sosem hallottam ezeket a sorokat.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Mi itt tanult emberek vagyunk, nem csak babák. A háziasszony szerint ez lényeges a mi intézményünkben.";
			link.l1 = "A háziasszony! Ôt keresem. Úgy hallottam, hogy sárga bôrû. Mondja, igaz ez? Egyébként mi a neve?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "Ez igaz. De jobb üzleti érzékkel rendelkezik, mint sok fehér nô. A neve Belle Etoile. De elég a beszédbôl.";
			link.l1 = "Elég a beszédbôl, azt mondod? A beszéd miatt vagyok itt. Felteszek még néhány kérdést, aztán elmegyek.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "És mi haszna van ebbôl az intézménynek? Itt nem a testekért fizetnek, hanem az idôért. Beszélni akar? Szívesen. De a pénzt elôre. És a szobában suttogunk, távol a kíváncsi fülek elôl. Nem érdekel, mit csinálunk ott - nem érdekel, ha gyertyát gyújtunk és imádkozunk. Egy ügyfél egyszer megkért, hogy segítsek neki verset írni. Egy másik, hogy beszéljen a gondjairól, jó barátjának nevezett. Egy harmadik pedig - csak gyertyát gyújtani, hogy aztán...";
			link.l1 = "Hát, nem akarom tudni - hallottam már valami kellemetlen dolgot mostanában. Mennyivel tartozom neked?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Kétszázötven dublonnal. Nincs alku. Ha rájövünk, hogy egy nincstelen pózerrel állunk szemben, akkor sajnálat nélkül kidobjuk. Ha pedig gazdag, de kapzsi, akkor emeljük az árat - úgyis fizetni fog.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Tessék, kétszázötven arany.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Hûha, ez a hely drágább, mint az a bordélyház Jamaikában. Visszajöhetek késôbb, miután megkaptam az aranyat?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Jól van. Hol kezdjük? Vacsora, gyertyákkal vagy anélkül, fürdô, beszélgetés?";
			link.l1 = "Nincs sok idôm, úgyhogy térjünk rá a kérdéseimre. Vezessetek.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Persze, hogy vezethet. A türelem a kurtizánok egyik erénye. Egy koldust kidobni egy dolog. Egy magafajta gazdag úriembert hagyni, hogy elmenjen a pénzéért, vagy akár kölcsönkérje, egészen más.";
			link.l1 = "A kurtizánok erényei... Ironikus. Mindjárt jövök.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Isten hozta, uram! Szóval, ki maga? Egy gazdag úriember vagy egy pózer?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Természetesen, én egy gazdag úriember vagyok, mademoiselle. Itt van az aranya - mind a kétszázötven dublon. Nem kell megszámolni.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Még mindig kevés vagyok, csak türelemmel.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "Mi itt nem számolunk. Hmm, néhány érme elhajlottnak és töröttnek tûnik - az úrnônek ez nem fog tetszeni, de legalább mind valódi arany.";
			link.l1 = "Micsoda... kecses személyiség.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "Így van. Etoile úrnô tud lágy és gondoskodó lenni, tud szigorú lenni, és tud kegyetlen is lenni. Ezért nem számítunk egyébként. Az úrnônek nem mindig fizetnek azonnal, de mindig megkapja, ami jár neki. Ha nem aranyban, akkor vérben. Minden toleráns háznak szüksége van védelmezôkre és pártfogókra. És a miénk megfelel az intézmény státuszának.";
			link.l1 = "Én fizettem, úgyhogy mutasd az utat.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Szóval, milyen kérdései vannak, monsieur? Megpróbálom kielégíteni a... kíváncsiságát.";
			link.l1 = "Tudja, mi érdekel engem, mademoiselle - az ön úrnôje, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "Mit mondhatok róla? Még számunkra is rejtélyes. Bár törôdik a jólétünkkel, egészségünkkel és biztonságunkkal, nem barátkozik és nem kerül közel egyikünkhöz sem.";
			link.l1 = "Talán nem szereti a hosszú beszélgetéseket. Mondja, beszél akcentussal?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "Nem, mibôl gondolja ezt? Csak mert sárga bôrû? Tiszta franciául beszél, és több más nyelven is. És bármilyen témáról képes egy órás beszélgetést folytatni a vendégekkel és a potenciális érdeklôdôkkel.";
			link.l1 = "Nem mondhatod. Érdekes... Most itt van? Ha igen, akkor bemegyek hozzá, és nem vesztegetem tovább az igazán... drága idejét, hogy visszatérhessen a munkájához.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "Nincs sok minden, ahová vissza lehetne térni - bár háziasszonyunk' célja, hogy ez a hely legyen a legjobb a szigetvilágban. Egy elit hely, ahová egyetlen kereskedô, nemes vagy csak mûvelt ember sem szégyellne eljönni - mert mi sokkal többet nyújtunk, mint a testünk.";
			link.l1 = "De nem túl sikeres ebben, nem igaz?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Hogy is mondjam... Ô mindannyiunkat nem csak árucikknek tekint, mint az egyszerûbb intézményekben, hanem projektnek. Drága ruhák, gyógyszerek, oktatás - mindannyiunkba befektet. És ha egy nagyvárosban lennénk az Óvilágban, sikerrel járna! De itt... Még egy tehetséges kereskedô sem keres semmit, ha az áru olyan drága, hogy szinte senki sem tudja megvenni. Még ha csökkentjük is az árakat, akkor is arra vagyunk ítélve, hogy egy nap csôdbe megyünk.";
			link.l1 = "Sajnálattal hallom ezt. Szóval, hol van most a szeretôd?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Eddig jól élünk itt, azt mondhatom. Azért, hogy megdolgozzunk érte, és megfeleljünk az elvárásainak... Ami az úrnôt illeti, Espanolába ment, hogy megvitassa annak lehetôségét, hogy mindannyian Kikötô-au-Prince-be költözzünk - elvégre ott több kereskedelmi útvonal fut össze, és a kereskedelmünk nem fog ott tétlenül állni és szinte állandó veszteségeket szenvedni. ";
			link.l1 = "Valóban? Levasseur nem fektetett be ebbe a helybe, hogy biztosítsa a stabilitását?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Nem túl sokat. Eljött hozzánk, és azt mondta, hogy csak akkor fektet be nagy összegeket, ha idôrôl idôre elmegyünk hozzá. De a hölgy élesen visszautasította. Olyannyira, hogy a kegyelmes úr egy pillanatra meglepôdött. Soha nem láttam még így sem ôt, sem ôt.";
			link.l1 = "Heh-heh, nézzenek oda. Úgy tûnik, tudja... Bátor, nagyon bátor tôle.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Mit tud? Viszont, ha már ilyen jól elbeszélgetünk, elmondok még valamit, de ez egy nagy titok, úgyhogy ne beszélj róla senkinek!";
			link.l1 = "Ó, nem, kisasszony. Biztosíthatom, hogy nem akarom semmiképpen bántani a hölgyet. Kérem, folytassa.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Nem is tudom, hogy árthatnál-e neki, mert Belle Etoile minden nap gyakorolja a vívást, és nincs méltó ellenfele az egész városban. Kikötô-au-Prince mellett magát Marcus Tyrexet is fel akarja ajánlani befektetésre! Vagy inkább, hogy kölcsönt vegyen fel tôle. El tudod képzelni?";
			link.l1 = "Igen, és úgy érzem, hogy ma nagyon kemény beszélgetésem lesz egy másik nôvel, aki rendszeresen gyakorolja a vívást... Nos, köszönöm, hogy megosztotta velem, kisasszony. További szép napot és nagylelkû ügyfeleket.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Köszönöm! De hová sietsz? Teljes egészében kifizette, és még nem is beszéltünk olyan régóta. Különben is, van önben valami kifinomult, monsieur. Valami sokkal több, mint azok a ritka gazdag emberek, akik eljönnek hozzánk. Élvezzük egymás társaságát igazán?";
			link.l1 = "Tudja... mi a fene? Miért tettetem és hazudok magamnak, mintha nem akarnám ezt? Nagyon ritka az esély egy olyan nôvel, mint te.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Ó, sajnálom, hogy nemet kell mondanom, kisasszony. Csak beszélgetni jöttem ide. Különben is... Valaki vár rám.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Mintha ez valaha is megállított volna bárkit is. Ebben az esetben tiszteletet érdemel, monsieur. Nagyon örülök az ön 'someone'.";
			link.l1 = "Még egyszer köszönöm, mademoiselle. Viszontlátásra.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Köszönöm. Köszönöm. Mit szólna egy közös forró fürdôhöz, kezdésnek?";
			link.l1 = "Mindkét kezemmel támogatom.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "Varázslatos élmény volt, monsieur. Nem gondoltam volna, hogy egy férfi így meg tud lepni. Maga tudja, hogyan szerezzen örömet egy nônek...";
			link.l1 = "Az a nôtôl függ.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Megbánta?";
			link.l1 = "Most még egyáltalán nem. Viszlát, kisasszony.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Vigyázz hova mész, pózer!";
			link.l1 = "Vigyázz a szádra!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Én figyeltem, hova megyek, amíg te varjakat számoltál.";
			link.l1 = "Megkerülhetted volna, ha figyelsz, nem igaz?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Miért kellett volna megkerülnöm téged?!";
			link.l1 = "Javaslom, hogy a városon kívül derítsük ki, ki mivel tartozik és kinek.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, nem. Nem tudtam, hogy ôlordsága ennyire undorodik egy egyszerû férfi akaratlan érintésétôl.";
			link.l1 = "Mondja még egyszer?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Hmm, bocsánat. Nem állt szándékomban lökdösni téged.";
			link.l1 = "Így már jobb.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Ha fél órát késtél volna, Charles, az ágyúgolyóinkkal darabokra zúznám ezt a mocskos barlangot, rendben! Megtalálta, amit keresett? Ô az, Longway húga? Láttad ôt?";
			link.l1 = "Shh, Mary, ne beszélj így. Nem, nem találkoztam Chang Xinggel...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "Akkor mi a fene tartott ilyen sokáig?! Mit csináltál ott?";
			link.l1 = "Nincs miért aggódnod. Amint megtudtam mindent, amit tudtam, elmentem onnan, ahogy megígértem neked.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Csak köpd ki, rendben!";
			link.l1 = "A tulaj jelenleg nincs a Tortugán. Itt alacsony a kereslet a szolgáltatásai iránt, mivel jól képzett, drága ruhás hölgyeket alkalmaz, és csak aranyat fogadnak el fizetségként...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Te is fizettél nekik?!";
			link.l1 = "Máskülönben nem is álltak volna szóba velem. Ilyen hozzáállással nem csoda, hogy nem sok ügyfelük van. A madame úgy döntött, hogy Kikötô-au-Prince-be költözteti a kereskedését, remélve, hogy gazdagabb ügyfélkört vonz majd. De nyilvánvalóan pénzszûkében van, mivel úgy döntött, hogy kölcsönért fordul Marcus Tyrexhez...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "Vajon ismeri ôt?";
			link.l1 = "Majd kiderül, ha La Vegába érünk. És ha sietünk, és nem vesztegetjük az idôt felesleges fecsegéssel, elkapjuk ezt az ázsiai nôt, bárki is legyen az.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "Felesleges volt elmenni abba a bordélyházba, Charles. Biztos vagyok benne, hogy mindezt a kocsmában vagy az utcán is kideríthettük volna, ha eléggé igyekszünk, rendben.";
			link.l1 = "Legközelebb magammal viszlek, hogy ne tömd tele a szép piros fejedet hülyeségekkel, jó? Most pedig térjünk a tárgyra.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "Ó, látom, egy kicsit elkéstem, rendben! Várj csak, te gazember...";
			link.l1 = "Mary, mi a fenét keresel itt?! Mondtam, hogy maradj a hajón!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Hogy ne akadályozzalak meg abban, hogy kurvákkal szórakozz?! Eszedbe se jusson tagadni, Charles! A legénység látott téged, rendben? Hogy tehetted?!";
			link.l1 = "Én is ezt gondoltam. Gondolom, magammal kellett volna vinnem ôket, hogy lássák, mit csinálok - vagy inkább nem csinálok -, és ne csináljak belôle nagy ügyet...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "Hazugsággal vádolod a fiainkat? Azok után, amit te magad tettél, te vadállat?";
			link.l1 = "Én csak páratlan ostobasággal vádolom ôket. Anélkül, hogy megértenéd a helyzetet, te...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, nem hiszem, hogy neked és a kurváidnak tetszett volna, ahogy én megértettem a helyzetet, ha idôben odaértem volna abba a lyukba. De szerencséd van - egyedül eveztem ezt a kibaszott hajót...";
			link.l1 = "Azt mondják, a kemény fizikai munka kitisztítja a fejedet a felesleges gondolatoktól. De neked még mindig rengeteg van belôlük, úgyhogy te is visszavánszorogsz.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Nem mozdulok, rendben!";
			link.l1 = "Mary, nem fogom ezt a beszélgetést itt Levasseur emberei elôtt folytatni. Nyugodjon meg, nézzen körül, és döntsön. Ez nem a megfelelô hely és idô.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "A pokolba veled. Még mindig a kabinban vannak a dolgaim... De ne higgye, hogy megint az evezôket fogom kezelni, rendben! Biztos maradt még benned valami a nemesemberbôl!";
			link.l1 = "Én egy gazember és egy vadállat vagyok, emlékszel? Majd a hajón bebizonyítom, de elôbb oda kell érnem. Szóval hiábavalóak a könyörgéseid.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Az egész legénység rajtad röhög!";
			link.l1 = "Nos, talán rajtad is. Rég nem láttak már ilyen látványosságot. Most, hogy kicsit lehûltek az indulataid, hadd mondjam el, mi történt.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, mostanra már mindent hallottam. Csak egy kérdésem van: nem voltam elég jó neked? Valami hiányzik belôlem?";
			link.l1 = "Udvariatlanság, de egy kérdéssel válaszolok: adtam én valaha is jó okot arra, hogy ne bízzon bennem? Huh? Nem emlékszem ilyesmire. Szóval vegyen egy nagy levegôt, és hallgasson meg. Nem sokat tudtam meg Joep van der Vinkrôl, csak annyit, hogy járt egy bordélyházban. Nem abban, amelyik a 'Singing Crow', mellett van, hanem egy másikban a móló közelében. Én nem tudtam róla korábban... ellentétben, úgy tûnik, a tengerészeinkkel, akik felvilágosítottak. Bár nekik nem lett volna szabad odamenniük...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Miféle bordélyház az, ahová nem engedik be a tengerészeket?";
			link.l1 = "Egy bordélyház, ahol selyembe öltözött hölgyeket alkalmaznak, akiknek nem csak levegô van a fejükben. És a szolgáltatásaikért kizárólag aranydublonokban fizetnek. Nem akárki szeszélye, hanem titokzatos úrnôjük, Belle Etoile parancsa.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Titokzatos, igen.";
			link.l1 = "Nem csak errôl van szó. Ô ázsiai.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Ázsiai? A Tortuga bordélyház asszonya?";
			link.l1 = "Lehet, hogy Chang Xing az. Ezért mentem oda - a saját szememmel akartam látni ôt. Ez minden.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "Milyen a nô?";
			link.l1 = "Fogalmam sincs. Nem volt ott, így egy másik... sztárral kellett beszélgetnem.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "Ô is ázsiai volt, ugye?";
			link.l1 = "Nem, ô fehér volt. Elmondta, hogy Belle Etoile-nak mostanában nem megy valami jól, ezért úgy döntött, hogy Kikötô-au-Prince-be költözik. Érthetô, mert ott gazdagabbak az emberek. A madamnak bizonyára pénzszûkében van, mivel kölcsönre van szüksége, hogy Espanolában kereskedést nyisson, amit Tyrex-tôl szándékozik felvenni. Tehát ha sietünk La Vegába, még azelôtt elfoghatjuk, hogy Marcus találkozna vele.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "Leszarom ôt, Marcust vagy bárki mást, rendben. Charles, csak egy dolgot árulj el - voltál valamelyik lánnyal a bordélyházában?";
			link.l1 = "Erre nincs szükségem, Mary. Itt vagy nekem te, a legjobb lány a világon. Nem értem, miért nem veszed ezt észre.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "Igazából, nagyon könnyû rájönni az igazságra, rendben, hee hee. Ha még nem voltál senkivel, akkor most tele lehetsz energiával. Ezt fogjuk most ellenôrizni, rendben!";
			link.l1 = "Mary, kérlek...";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Kiváló egészség", "Medic");
					dialog.text = "(Kiváló egészség) Ugh... Úgy tûnik, hogy nem hazudtál, Charles, rendben...";
					link.l1 = "Nincs szükségem arra, hogy becsapjalak, kedvesem...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("A képességek ellenôrzése sikertelen.", "Medic");
					dialog.text = "Charles, te... komolyan mondod?! Mi volt ez?";
					link.l1 = "Ó, ez a hôség nem tesz jót nekem. Ahem.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Úgy tûnik, nem hazudtál, Charles, rendben...";
				link.l1 = "Nincs szükségem arra, hogy becsapjalak, kedvesem...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "De azt a csónakázást sokáig nem fogom elfelejteni!";
			link.l1 = "Ha!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "Még sosem panaszkodtál rá, ugye?";
			link.l1 = "Próbáld meg te is körbefutni az átkozott szigetet...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "És a bordélyházak, rendben! Tényleg...";
			link.l1 = "Mary, sajnálom.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "Mary, sajnálom. Szóval te...";
			link.l1 = "Ezt nem sajnálom. A francba. Úgy értem, nem voltam senkivel, csak veled, mondtam neked. Én csak... nem tudtam megnyugodni, ennyi az egész. Nehéz ezt megtenni, tudod, amikor La Roche ágyúi bámulnak rád.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "Ez egy remek kifogás, Charles. Rendben, elhiszem. Ezúttal... De tudd, hogy még mindig haragszom rád, rendben!";
			link.l1 = "Ki fogom érdemelni a megbocsátásodat, ígérem.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Nos, szerelmes fiú, mondd el, mit találtál. Megérte kockáztatni a kegyeimet?";
			link.l1 = "Tényleg nem tudom eldönteni, hogy viccelsz vagy komolyan beszélsz. Megérte - még akkor is, ha nem láttam a saját szememmel a hostess-t. Ázsiai, és a neve Belle Etoile - egy csodálatos sztár. Persze nem az igazi neve...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "És ezért el kellett menned egy bordélyházba? Ezt nem tudtad kideríteni a fogadóban?";
			link.l1 = "Nem igazán beszélnek errôl a helyrôl a városban. Miért nem beszélnek errôl a városban? Ez egy jó kérdés. Kérdezd meg Belle Etoile-t személyesen - ô is elment Espanolába.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "Tortuga nem volt elég neki?";
			link.l1 = "A kereskedelem, úgy tûnik, nem megy jól itt. Nem közönséges kikötôi lányokat alkalmaz, hanem gazdagon öltözött, mûvelt hölgyeket.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "És miért tennének ilyet?";
			link.l1 = "Ez egy másik jó kérdés. Mindenesetre a mi kismadarunk úgy döntött, hogy Kikötô-au-Prince-be, de Mussac hûbérbirtokára repül. De a kölcsönt ehhez a vállalkozáshoz nem mástól, mint Tyrex-tôl kellett volna megszerezni.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Szeretném, ha ennek a történetnek hamarosan vége lenne. Ne vesztegessük az idôt, és vegyük az irányt La Vega felé.";
			link.l1 = "Ezt fogjuk tenni.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Bátor ember vagy, Charles, azt meg kell hagyni. Ilyen könnyedén felbukkansz, ilyen egyenes arccal, mintha mi sem történt volna.";
			link.l1 = "Gondolom, az egyik legénységi tag elkotyogta? Természetesen mindenféle összefüggés nélkül. Mert igazából semmi sem történt, legalábbis nem az, amire maga gondol.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Örülök, hogy nem tagadta le, Charles.";
			link.l1 = "Mindent el akartam mondani neked, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Ne tedd, Charles. A részletek nem nagyon érdekelnek. De az okok igen. Mondd, van valami baj velem?";
			link.l1 = "Kezdjük az okokkal. Megtudtam, hogy két bordélyház van Tortugán. Az egyik jól ismert. A másik - az emberek tudnak róla, de kevesen akarnak beszélni róla. Egy ázsiai nô tulajdonában van...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Ezt csak úgy kitalálod?";
			link.l1 = "Mi a fenéért tennék ilyet, Helen?! Ha nem hiszel nekem, majd a helyszínen megerôsítik!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Elôször is, azt mondtad, hogy ne menjek ki a partra, szóval kizárt, hogy odajussak. Másodszor, mit gondolsz, ki a fenének nézel te engem?! Nem megyek egy ilyen hely közelébe! Harmadszor... csak menj tovább.";
			link.l1 = "Jó. Úgy döntöttem, hogy odamegyek, hogy a saját szememmel lássam Madame Étoile-t. Ez volt az egyetlen szándékom, a fenébe is!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Gondolom. Találkozott vele?";
			link.l1 = "Nem. Elment Espanolába. Itt nem mennek jól a dolgai, ezért úgy döntött, hogy Kikötô-au-Prince-ben próbál szerencsét. Ott a selyembe öltözött, mûvelt hölgyek, akik az üzletében dolgoznak, több hasznot hozhatnak neki, mint Tortugán...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Felöltözve és mûveltek? Hûha, mit hozhat az élet. De úgy kell szeretni ôket, ahogy vannak.";
			link.l1 = "Helen, hagyd abba! Nem tettem semmit, amivel kiérdemeltem volna a bizalmatlanságodat.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Ez igaz. Ha megpróbáltál volna becsapni, nem lennél ilyen nyugodt. De figyelmeztetned kellett volna a terveidrôl, Charles.";
			link.l1 = "Igazad van, drágám. De úgy döntöttem, hogy idôt spórolok. Az én hibám.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "Jól van, rendben. Most mi lesz, tervezzük az utat Kikötô-au-Prince felé?";
			link.l1 = "La Vega. Ne lepôdj meg, Helen. Madame Belle Etoile nincs jól. Kölcsönre volt szüksége, hogy Kikötô-au-Prince-be költöztesse a kereskedelmét, ezért úgy döntött, hogy kölcsönkér Marcustól. Ha sietünk, még odaérhetünk. Szóval ne vesztegessük az idôt.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ_1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ_1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Mary();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Helena();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Nem hiszem el, hogy egy ilyen pöcs, mint te és a csôcseléked legyôzött minket!";
			link.l1 = "Te...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Ó, felismersz engem?";
			link.l1 = "Találkoztunk már?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "Mi van?! Te most szórakozol velem, baszd meg?!";
			link.l1 = "Nem emlékszem minden civilizálatlan söpredékre, akivel találkoztam. Jobb lenne, ha elmondanád, ki küldött, hogy megölj minket. Vagy talán csak meg akartak szabadulni tôled?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Nem mondok semmit egy olyan embernek, mint te. Olyan rohadtul nagyra tartod magad! Lássuk, hogy ezt vissza tudod-e támasztani a mi kis pihenônk után.";
			link.l1 = "Kár érte. Undorító vagy, de akár egy másik szigeten is kitehettelek volna. Most már csak annyit tehetek, hogy elküldelek a túloldalra.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Hívott, kapitány?";
			link.l1 = "Igen, pajtás. Jelentse a károkat.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Heves vihar van. A hajó nyikorog és recseg, erôsen imbolyog.";
			link.l1 = "Igen, észrevettem. Tichingitu, barátom. Én és a " + sStr + " partra szállunk. Te maradsz a fônök. Azonnal kezdjétek el a javításokat - amíg a vihar elül, nincs értelme a kikötôbe menni. Különben sem leszünk itt sokáig.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Majd én mindent rendbe hozok.";
			link.l1 = "Remek, köszönöm. Akkor minden gond nélkül indulunk a városba.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Monsieur le Capitaine? Megtiszteltetés. De ilyenkor általában Alonsót hívja. Minden rendben van, ha megkérdezhetem?";
			link.l1 = "Igen, minden rendben. De a mi Alonsónk inkább a rombolásról szól, nem a javításról. A szó minden értelmében. Mennyire rossz a hajó?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso azt mondaná, hogy pocsékul, még ha nem is megyünk lefelé. Említette a javításokat - elkezdjük ôket?";
			link.l1 = "Igen, tegye meg, amit tud. De ne tervezz teljes körû, hosszú távú munkát - hamarosan felhúzzuk a horgonyt, miután befejeztem az üzleti ügyeimet a városban. Én és a " + sStr + " nem leszünk ott, úgyhogy ha bármi történne, minden döntést te hozol meg. Mindenben hallgassatok Alonsóra.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Ahogy parancsolja, Monsieur le Capitaine.";
			link.l1 = "Pihenj.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Üdvözlöm, uram! Üdvözöljük Kikötô-au-Prince-ben.";
			link.l1 = "Jó napot, uram. Ki maga, és minek köszönhetem ezt a fogadtatást? Nem mondanám, hogy hosszú beszélgetéshez lenne kedvem ebben az esôben és vihar után.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Ó, nem fogom sokáig rabolni az idejét, Monsieur de Maure.";
			link.l1 = "Ismerem magát?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Ó, nem, de az egész szigetvilág tudja, ki maga. Ah, hol vannak a jó modorom! Henri Thibaut, szolgálatára. Ôlordsága, Monsieur de Mussac küldötte vagyok. Amint meglátta a hajóját, megparancsolta, hogy a lehetô legmelegebben üdvözöljem, monsieur.";
			link.l1 = "Nos, ez sok mindent megmagyaráz. Örülök, hogy megismerhetem, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "Az öröm kölcsönös, Monsieur de Maure! Kérem, kövessenek. Nem helyes, hogy egy ilyen magas rangú férfi és gyönyörû kísérôje ebben a bûzös kocsmában van bezárva. Ôlordsága kijelölt önnek egy házat a városban, és megbízott, hogy mindenben segítsem önt. Kérem, ne felejtse el, hogy utána átadja jókívánságait Poincy ôexcellenciájának.";
			link.l1 = "Valójában a megbízásom diszkrét. Tudja, Monsieur Thibaut, azt hiszem...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Ritkán kérek öntôl bármit is, nemhogy félbeszakítanám, de nem élhetnénk az ajánlatukkal? Elegem van abból, hogy elázom az esôben. Hányingerem van és szédülök is.";
			link.l1 = "Biztos, hogy az esô miatt van?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Harapj a nyelvedre, Charles! Különben is, pihenni akarok. Egy nagy ágyon és hullámok nélkül.";
			link.l1 = "Jól van, rendben. Megszárítjuk magunkat, tartunk egy kis szünetet, aztán folytatjuk a munkát.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Tarthatunk egy kis szünetet ebben a házban? Nem érzem jól magam, és... fáradt is vagyok, Charles. Jól van, rendben.";
			link.l1 = "Mary, kedvesem, megértem, de talán el kéne mennünk a kocsmába. Ennek az egésznek rossz szaga van, nem igaz?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "Mi történhet velem? Ez nem is Tortuga.";
			link.l1 = "Ez az, ami megrémít.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "Ez még nem is Tortuga. Ha valami, akkor felállítok egy védelmet a szobában - pont úgy, mint... akkoriban, rendben. Mindenkinél jobban ismersz engem, Charles, szóval tudod, hogy meg tudom oldani.";
			link.l1 = "Rendben, rendben. Remélhetôleg ez nem olyan lesz, mint akkor.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Tudtam, hogy meggondolja magát, monsieur! Ami az aggodalmait illeti, tökéletesen megértem. De tudja, Poincy ôexcellenciája és a kormányzó régi barátok, és ezért Ön szívesen látott vendég a városunkban, Monsieur de Maure!";
			link.l1 = "Ó, nos... Nos, akkor vigyen minket a házba.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Természetesen, monsieur! Kövessen, kérem.";
			link.l1 = "Köszönöm.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Monsieur, a kormányzó várja önt. Arra kérte, hogy menjen hozzá, amint tud - négyszemközt szeretne önnel beszélni.";
			link.l1 = "Tudja már ezt?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Természetesen, tudja! Ezért várja önt. Hagyja kedvesét édesen aludni, amíg ön elmegy Monsieur de Mussac-hoz. Valami vihar nem fogja megállítani a híres Charles de Maure-t, ugye? De Ôlordsága, mint tudja, nem sok ideje van két találkozó között...";
			link.l1 = "Nos, ez igaz, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Megmutatjuk az utat, kapitány.";
			link.l1 = "Ó, szóval még egy tiszteletbeli kísérôm is van... Nos, akkor mutassa az utat.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Kapitány úr!";
			link.l1 = "Hosszú út! A hajóhoz! A hajóhoz! Most!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "De én láttam Chang Xinget!";
			link.l1 = "Micsoda?! Hol? Mikor? A hajódon van?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Nem! Itt a városban, Longway messzirôl látta ôt. Nincs ideje utolérni - egy gályára szállt fel, amelyik épp most szállt hajóra!";
			link.l1 = "Majd utolérjük a gályát! De mondd csak - láttad valahol a " + sStr + " ?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "Nem! Történt valami?";
			link.l1 = "Igen, valami történt! Veszélyben van! Nem látta Levasseur unokaöccsét? A neve Henri Thibaut! Csúnya, sovány, hosszú hajú fiatalember, vicces bajusszal!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(mandarinul) Nem kell a vicces bajuszokról beszélni, kapitány... (tört francia nyelven) Láttam ôt! Ô és a zsoldosok is ugyanarra a gályára szálltak.";
			link.l1 = "Azonnal vegyük üldözôbe ôket!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "A hajója nagyon elhasználódott, kapitány úr!";
			link.l1 = "Nem érdekel! " + sStr + "'az élete forog kockán!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Az én... 'A te Meifenged' átvisz minket!";
				link.l1 = "Ó, hát persze! Gyorsan!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Ne dobj minket egy öngyilkos támadásba. Használd a hajót, amit korábban adtál nekem!";
				link.l1 = "Jó ötlet, Longway! Gyerünk, siessünk!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			AddDialogExitQuestFunction("PZ_Longway_78");
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Te megint... Tudtam, hogy vissza kellett volna utasítanom, és hagynom kellett volna, hogy valaki más vigye el a lányodat.";
			link.l1 = "Hol van?! Mondd meg! Nem... Fogd be a szád. Csak a raktérben fogsz beszélni, bilincsben! Hallasz engem?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "A pengéje. Ha most azonnal nem kezdesz el énekelni, darabokra váglak vele.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Te... elment az istenverte eszed!...";
			link.l1 = "Most meglátod a kellemetlen oldalamat...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ennyi?";
			link.l1 = "Újra megkérdezem! Hol van a " + sStr + "?! Hol van a kínai nô?! Hol van Henri Thibaut?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(vért köpköd) Úgy ütsz, mint egy lány.";
			link.l1 = "Te ribanc! Minden szót kiverek belôled!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Szánalmas. Bár... kimondom. Miért ne, ha ha. Mindannyian a másik hajón vannak, éppen úton Tortuga felé. Elkéstél.";
			link.l1 = "Ha csak egy hajszál is leesik a fejérôl...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "És ez kinek a hibája?! Te ölted meg Edgardo Sottát! Levasseur életében elôször akart megízlelni egy lányt, és nem kapta meg rögtön! Elôször fordult elô, hogy a legénységünk nem teljesítette a közvetlen parancsát! Ez az ember olyan ijesztô tud lenni, mint az ördög...";
			link.l1 = "Akkor ijesztôbb leszek, mint maga az ördög, és egy kis személyes pokolra juttatlak, ha nem mondod el, amit tudni akarok, hallod?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Leszarom a bánatodat - a te ôrült szemeidbôl ítélve úgyis halott ember vagyok. De azért elismerem, de Maure.";
			link.l1 = "Mi a fenérôl beszélsz?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur kedveli a szôkéket. De én mindig is jobban szerettem a vöröseket, akárcsak te, hehehe... Micsoda csípôs egy van neked!";
			link.l1 = "Igazad van, nem fogod túlélni a napot...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Nem érdekel, hogy mit akarsz. De hadd mondjam el, mit akar Levasseur - csinos szôke lányokat, ha ha ha ha ha ha ha ha ha ha ha ha ha! Elôször is, a lányt...";
			link.l1 = "A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Nyikorgás és egy fegyvertelen ember megverése - szánalmas. Ez minden, amit tehetsz. Vesztettél, de Maure! Akarod tudni, mikor vesztettél igazán, te szánalmas kretén?";
			link.l1 = "Világosíts fel. De ha nem vagyok lenyûgözve, akkor elveszíted az ujjadat. Vagy egy fület. Vagy a rohadt fogaidat a büdös szádból. Vagy talán valami mást. A választás a tiéd...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Heh-heh, van valamim, ami neked nincs. Azt hiszi, Levasseur nem tudta, hogy az a vén róka, Poincy mit tervez ellene? Francois mindent tud, mindent! Még a testvériség bárói sem merik kihívni ôt. És te, okostojás, te megtetted. De...";
			link.l1 = "De mi?! Ne merészeld ezt elhúzni!!! Kezdj el beszélni, vagy elkezdem egyenként eltörni az ujjaidat!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ha-ha, bátor de Maure kapitány! De rendben van. Én, Henri és a sárga bôrû nô úgy döntöttünk, hogy a legjobb, ha itt pusztítunk el téged. És Tyrexre fogjuk, hogy a testvériség vén bolondjai újabb háborút kezdjenek egymás között! Vagy talán de Mussacra - ô már megint oda dugja az orrát, ahová nem tartozik... Tudod, mindenki kinevetett, amiért egy gályát vitorláztam, de az könnyedén átvészelte a vihart, nem úgy, mint a te szarod.";
			link.l1 = "Elég legyen! Hol tartja Levasseur az áldozatait?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Szóval tudsz a titkos helyérôl, a börtönrôl? Ó igen, ô az igazi börtönmester, ha-ha-ha-ha! De tényleg ki tudod hívni ôt? Kétlem. Le akarod gyôzni a szörnyeteget? Akkor legyél te magad a szörnyeteg. Lássuk, hogy meg tudsz-e törni engem, ahogy Francois megtöri azokat a lányokat. Ahogy hamarosan a tiédet is meg fogja törni...";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Mondtam, hogy ne fáradj, a fenébe is!...";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Engedje meg, kapitány úr.";
			link.l1 = "Longway? Mit engedsz meg?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "A fehér férfiak kínozzák a testet. Az én népem tudja, hogy elôször a nyomorult lelket kell gyötörni, hogy egy kis állandó fájdalommal az ôrületbe kergessék. Nem lehet csak úgy elvenni és kínozni elôkészítés nélkül. Mindig különleges megközelítésre van szükség. Itt szükség van... Lynchy.";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Igen, kapitány úr. Ezer vágás általi halál.";
			link.l1 = "Megôrültél?! Betörted a fejed? Milyen halálról fecsegsz?! Elôbb szóra kell bírnom!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway tudja, kapitány úr. Tudja, mit kell tennie. Ez a fattyú mindent el fog mondani nekem. Adj idôt...";
			link.l1 = "Idôt? Idôt?! Rendben... Csináld. Csak kérlek, könyörgöm, szedj ki belôle mindent, mindent!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_LongwayKazn_3_1", -1);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Ölj meg, csak ölj meg, kérlek... Mit akarsz még tôlem?!";
			link.l1 = "Semmi mást. Fogd be a szád és halj meg.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Tiszta lövés, kapitány úr. Mondtam, hogy mûködni fog.";
			link.l1 = "Igen, igen, igen. Szép munka. Akkor irány a börtön. Vitorlákat fel! Irány Tortuga. És Isten óvja ezt az átkozott várost, ha egy hajszál is leesik " + sStr + " fejérôl...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			AddQuestRecord("PZ", "39");
			pchar.questTemp.PZ_FlagMartinInfo = true;
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mio... Még sosem láttam vagy hallottam önt... így, senor kapitány.";
			link.l1 = "A tiéd, Alonso! Gyerünk, mutasd meg, mit tesz a Szent Inkvizíció a hugenottákkal és a csatlósaikkal... És én megnézem... Aztán azt csinálsz vele, amit akarsz.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Igenis, kapitány úr...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "Nem tart sokáig, Kapitány Úr...";
			link.l1 = "Csinálja, az ég szerelmére!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Kelj fel, te szarházi. Azt mondtam, kelj fel!";
			link.l1 = "Meghalt? Meghalt?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Úgy tûnik, kapitány...";
			link.l1 = "Mi a fenét csináltál?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Ki gondolta volna, hogy ez a fajankó ilyen gyengének bizonyul! A bugyiját is összepiszkította, a mocskos szemétláda! A fenébe is, a tûz nem volt szükségszerû...";
			link.l1 = "Maga... Hát, dobja a hajóra a halakhoz. Irány Tortuga. Ha kell, tégláról téglára szedem szét - elôször La Roche, aztán... Aztán Isten segítsen, ha nem találom meg élve...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			AddQuestRecord("PZ", "38");
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_Norman1":
			dialog.text = "Végre. Ez a trón most már az enyém. Erre a sziklára fogok építeni...";
			link.l1 = "Mi a fasz... Komolyan?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Cápa";
			
			dialog.text = "...a templomomat. Mostantól én vagyok Róma pápája. Ne esküdözz az Isten házában!";
			link.l1 = "És én még azt hittem... Nos, Ôszentsége, lenne szíves megmondani híveinek, hogy hol van most a "+ sTemp +" ?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "Szent küldetésre ment. Egy új keresztes hadjáratra, ha úgy tetszik. El fogja venni a pénzt a gonoszoktól és elviszi nekem.";
			link.l1 = "Hozzád, persze. Említette, hogy mikor jön vissza?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Egy hónap múlva. Talán egy kicsit késôbb. Várom a visszatérését, a nyáj többi tagjával együtt.";
			link.l1 = "Szóval tényleg a tengeren van. Jobb lesz, ha elmegyek, mielôtt elkapom, bármi is van nálad.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Megtisztítom ôket a szent lángokban...";
			link.l1 = "A fejedre ráférne egy kis tisztítás...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcusszal";
					else sTemp = "Steve-vel";
					
					dialog.text = "Charles! Mit tehetek érted?";
					link.l1 = "Helló, Helen! Beszélni szeretnék a "+ sTemp +". Fent van? Vagy a kocsmában van?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles! És... Ah, micsoda kellemes meglepetés. Mit tehetek értetek?";
					link.l1 = "Helló, Helen. Hol van a "+ sTemp +"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Cápa";
				
				dialog.text = TimeGreeting() + ", Charles. Mi szél hozott ide?";
				link.l1 = TimeGreeting() + ", Helen. Keresem a "+ sTemp +". Tudja, hogy hol van?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Kint van, de attól tartok, hogy hosszú idôre elment - a tengerre, hogy pontos legyek.";
			link.l1 = "A fenébe. Történt valami? Mondta, hogy mikor jön vissza?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Nem mondta, de semmi komoly - szokás szerint jó nyomon jár. Általában egy, legfeljebb két hónap múlva tér vissza. Tudom, hogy van ez, néha nekem is hiányzik a hajó fedélzete...";
			link.l1 = "A tengerre bármikor kimehetsz. Jó lenne egyszer együtt csinálni - te a 'Rainbow', én a...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Az jó lenne. De a... barátnôd nem biztos, hogy örülne neki. És én nem akarok a harmadik kerék lenni.";
			link.l1 = "Bocsánat, Helen, nem akartalak megbántani. Köszönöm a beszélgetést. Késôbb találkozunk.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, hát visszajöttél. Segíthetek még valamiben?";
			link.l1 = "Nem, köszönöm, Helen. Csak ellenôrizni akartam, hogy a "+ sTemp +" felkerült-e.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "Meglepôdnék, ha engem keresnél. Ami a "+ sTemp +"illeti, ô a tengeren van.";
			link.l1 = "Ó, tényleg? Mondta, hogy mikor jön vissza?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Úgy tûnik, belefáradt ennek a pöcegödörnek a vezetésébe, és emlékeztetnie kell magát, hogy még mindig egy hajó kapitánya. Nem elôször. Általában egy hónap, talán másfél hónap múlva tér vissza.";
			link.l1 = "A fenébe, szóval a bárók nem mindig ülnek ilyen nyugodtan? Köszönöm, Helen. Viszontlátásra.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+ sTemp +"'még mindig nem jött vissza, Charles";
			link.l1 = "Értem, csak ellenôrzöm.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "Szabad ember, ugye? Akkor megy a tengerre, amikor csak akar.";
			link.l1 = "Persze, hogy mehet. Szóval, hol van?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "A Cápa";
			
			dialog.text = "De Károly, ha nincs a szigeten, akkor a spanyolok kifosztására ment. És most, ha megbocsátasz, sok dolgom van. Idônként nézz be - általában a "+ sTemp +" körülbelül egy hónap múlva tér vissza, néha kicsit késôbb.";
			link.l1 = "Jól van, Helen, köszönöm. Elfoglaltak leszünk.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Most nincs hozzá kedvem. Talán majd máskor visszajössz, Charles?";
			link.l1 = "Persze, Helen. Elnézést a zavarásért. Vigyázz magadra.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "A helyünkön vagyunk, kapitány úr. Emlékszik az útra?";
				link.l1 = "Persze, Longway. Reméljük, hogy nem veszítjük el abban az átkozott börtönben...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "A helyünkön vagyunk, kapitány úr. Van terved?";
				link.l1 = "Még dolgozom rajta... Miért, van valami elképzelése?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Nos, azt hiszem, ha Chang Xingbe sietünk...";
			link.l1 = "Longway... Megértem, hogy mennyire szeretnéd látni a húgodat, de " + sStr + " most életveszélyben van, és ez nem csak szófordulat! Meg kell értened, hogy a megmentése az elsô számú prioritás!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Kapitány úr, kétlem, hogy igazán megérti, min mentem keresztül az elmúlt tíz évben. Hogy min megyek most keresztül.";
			link.l1 = "Tudja, bizonyos értelemben igen. A bátyámat börtönben tartják fogva. És bár még nem bántották, bármelyik pillanatban azt tehetnek vele, amit csak akarnak.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "De hova mennél, ha csak a hölgy " + sStr + " lenne az, akit meg kellene menteni?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Van egy hely... egy személy... De ne fáradj ezzel, Longway - ezt nekem kell megoldanom.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "Igazság szerint azt sem tudom, hová menjek. Ha óvatlanul szaglászom mindenhol, feltûnést keltek, és akkor " + sStr + " végleg vége. Szóval... egyszerûen nem tudom.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "Mi az? Miért? Miért?";
			link.l1 = "Nem fognak csak úgy beengedni oda - ez a felsô tízezer, a fenébe is! Szóval, egyedül megyek. Addig is menj a húgodhoz. Amint tudok, csatlakozom hozzád. Sok szerencsét, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Igenis! Köszönöm, kapitány úr. És sok szerencsét neked is!";
			link.l1 = "Ó, köszönöm - ma nagy szükségem van rá. Mindannyiunknak.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Kapitány úr...";
			link.l1 = "Ne is törôdj vele. Menjünk a húgodhoz, Longway. Ha most szétválunk - halottak vagyunk. Siessünk a húgodhoz, és derítsük ki, hol van Levasseur búvóhelye. Aztán újra együtt megyünk - most minden segítségre szükségem van. Remélem, nem késtünk el.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Nem fogunk elkésni, kapitány úr. Ne késlekedjünk tovább, és ne vesztegessük az idôt vitatkozással. Menjünk Chang Xingbe!";
			link.l1 = "Igazad van, siessünk.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Hova a fenébe mész? Tudod egyáltalán, hová vezet az az ajtó?";
			link.l1 = "Tökéletesen tudom. Üzleti ügyben megyek oda, nem csak kíváncsiságból vagy lopni.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Milyen ügyben? Madame Levasseur jelenleg nem elérhetô. Különben is, ô egy férjes asszony - nem helyes, hogy az emberek a háza körül lógnak.";
			link.l1 = "Nôs, rendben. De idônként fogadásokat tart, nem? Beleértve a privát fogadásokat is. Ez egy ilyen alkalom. Vár engem, és sietek.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Figyelmeztetett volna, ha ez lenne a helyzet.";
			link.l1 = "Én egy különleges vendég vagyok - az a fajta, akinek nincs szüksége bejelentésre.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Igen, az a fajta vendég, aki miatt Ôlordsága megparancsolja, hogy lôjenek le. Vagy maga az úrnô nyúz meg.";
			link.l1 = "Voltam már Madame Marceline vendége. Biztosíthatom, hogy utána semmi sem fog történni magával, katona.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "De persze vakon maradni és mindenkit beengedni - ez a városôrség dolga.";
			link.l1 = "Erre nincs idôm, te makacs öszvér...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Te...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Ó, igen, asszonyom. A lovagod örül, hogy újra találkozunk. Látom, meglepôdtél, hogy látsz engem. Ez a találkozás öröme... nem kölcsönös?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "De igen, így van. Tisztában vagyok vele, hogy talán nem én vagyok a legjóképûbb vagy legméltóbb férfi ezen a szigeten, ahogy azt a legutóbbi találkozásunkkor említetted, de legalább tudod, hogy becsületes ember vagyok. Hallgasson meg, hölgyem - nem fogom sokáig rabolni a... drága idejét.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Az Isten szerelmére, hagyja abba ezt a sikoltozást, asszonyom. Nem azért vagyok itt, hogy bosszút álljak rajtad, amiért becsaptad a lovagodat, és elszöktél a sárkány kincsével. És biztosíthatlak, ha meg akarnálak ölni, egyszerûen lelônélek, és menekülnék az életemért. Végül is ez itt Tortuga! De azt hiszem, már tudod, hogy ez méltóságomon aluli lenne.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Jaj, ne! Csak azt hittem, hogy... Nos, nem számít! Látod, gonosz nyelvek mocskos pletykákat terjesztenek rólam - egy szegény asszonyról, aki, még ha akarná sem tudna ártani senkinek, sem megvédeni magát az ellenséggel szemben. Különben is, olyan régen volt már... Azt hittem, rossz szándékkal jöttél hozzám, és nem jó szándékkal. Örülök, hogy tévedtem. Nehéz úgy élni, hogy rosszindulatúak vesznek körül.";
			link.l1 = "Hogy is tehettem volna? Még ha hallanék is ilyesmit, egy szót sem hinnék el belôle. De igazad van - nem azért jöttem ide, hogy téged lássalak. Bár örülök, hogy eljöttem. Tudom, hogy ez szokatlanul hangzik, de... ezúttal a lovagjának szüksége van a segítségére, asszonyom.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "És sokkal érzékenyebb vagy, mint gondoltam. De azért ön sem hibátlan, Monsieur de Maure - azt vártam, hogy ön sokkal... kifinomultabb lesz. Valójában... vagy mindig is ilyen voltál, vagy a szigetvilág már megrontott téged. Újra meg kellene tanulnia, hogyan kell beszélni egy hölggyel. De igazad van - te egy becsületes ember vagy, bár... egyszerû.";
			link.l1 = "Te pedig egy büszke és bosszúálló nô vagy. A szemeid, a szavaid és a tetteid elárulják ezt. Szóval, ha valaki megért engem, az te vagy. Ahogy én is megértettelek téged. Szóval ne rágódjunk tovább a múlton. Tud segíteni, asszonyom?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Ó... elismerem, hogy akkoriban nem voltam kedves hozzád. De csak azért, mert nem voltam teljesen biztos benned, semmi több! Elvette volna tôlem az összes gyémántot? Vagy odavitted volna a férjemet, mondván, hogy a szolgáinktól tudtad meg, hogy loptam tôle, és tagadod a részed ebben? Hiszen mindenki az ô kegyeit keresi, nem pedig egy olyan szegény asszonyét, mint én... Most már tudom, hogy tévedtem veled kapcsolatban. Kérem, fogadja el bocsánatkérésemet... lovagom.";
			link.l1 = "Most már nem tudom, hogy ôszinte-e vagy sem. De ez nem számít. Szükségem van a segítségére, Madame Marceline. Élet-halál kérdése. Kérem, ne utasítsa vissza.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "A segítségem...? Biztosan nem én vagyok az utolsó nô a városban, de a befolyásom nem olyan nagy, mint ahogy önök gondolják. Én egy királynô vagyok, aki uralkodik, nem uralkodik. De hallgatni fogok rád. Mit tehet az én szerény személyem értetek?";
			link.l1 = "Tudom, hogy ez kellemetlen téma önnek, de a férjét keresem, asszonyom, mégpedig minél elôbb. A helyzet az...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "Ez egy vicc? Jelenleg nincs a rezidencián? Akkor üzleti úton van. Nem tudok segíteni, Monsieur de Maure.";
			link.l1 = "Elfordította a szemét. Tudja... Én is tudom. Csak oda kell érnem. Kérem, ne tegyen úgy, mintha most hallana elôször a tömlöcrôl - túl okos ahhoz, hogy ne tudná.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Ó, úgy érzem, ez a beszélgetés újabb ôsz hajszálakkal gyarapítja a fejemet. Mintha nem lenne már így is elég elsô ráncom. Mi a fenét mûvelsz velünk, Francois...";
			link.l1 = "Egy ôsz hajszál csak növeli a nemességét, és nem veszi el a szépségét. De egy jó, ártatlan lány a férjed kezébe került. És most azt kockáztatja, hogy elveszíti a szépségét, az egészségét, sôt az életét is!...! Tudod, mi történik azokkal, akik ott csapdába esnek. Kérem, asszonyom. Marceline... Segítsen a lovagjának.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Már nem az én lovagom, igaz? Ugyan már, nem vagyok hülye. De... Segítek neked, de Maure. Végül is, ez nem mehet így örökké. És egy nap nyilvánosságra került volna. Nekem most az a fontos, hogy idôben és a megfelelô módon kijussak. És... Nem ítélhetlek örök szenvedésre, amit az okoz, amit az én ‘férjem' fog tenni a... ismerôsöddel.";
			link.l1 = "Lehet, hogy már nem leszek a lovagja, asszonyom. De ön sem volt a hölgyem a kezdetektôl fogva. Azonban életem végéig hálás leszek neked. Szóval, hol van ez a hely?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Nos, szavadon foglak, Charles. A városi börtönben. Az egyik zsákutcában van egy nagy hordó, mellette pedig egy folyosó kezdôdik, amely ennek az ördögnek a búvóhelyére vezet. Nem néztem bele. Csak egyszer követtem ôt, nagyon régen. És megijedtem, amikor meghallottam azoknak a szerencsétlen teremtményeknek az embertelen sikolyait.";
			link.l1 = "Sok életet mentett meg ma, asszonyom. Nem csak az én kedvesemet, hanem mindazokat, akik a jövôben a férje kezére kerülhettek volna. Köszönöm.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ah, hagyjon engem ezekkel az üres szavakkal, monsieur. Nagyon sokat kért tôlem. És nagy kockázatot vállaltam. Próbáld meg most, lovagom, sikerre vinni az új küldetésedet a sárkányok barlangjába!";
			link.l1 = "Megteszek minden tôlem telhetôt. Viszlát, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Szóval, ön egy bandita, monsieur...? Mi nem veszünk fel ilyen új lányokat; mindannyian önként jöttünk ide. Meg kell kérnem magát és a... bûntársát, hogy távozzanak. Én pedig gondoskodom róla, hogy ez a lány megkapja a kezelését - különben feljelentem a hatóságoknál!";
				link.l1 = "Nem vagyunk banditák. De ez a lány bármelyikükkel felveszi a versenyt. Nem a látszat kedvéért hordja a pengét. Csak megsebesült. Ez az ember a barátom, és az úrnôd bátyja is. Hadd nézzük meg.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Örülök, hogy újra látom, uram! De tudod, hogy nem fogadunk itt alacsonyrendû vendégeket. Még akkor sem, ha kezeskednek értük és fizetnek értük. Különösen a sárga bôrû munkásokat vagy néger rabszolgákat. Attól tartok, a barátjának távoznia kell.";
				link.l1 = "Ne mondd ezt az úrnôd elôtt. Ô is sárga bôrû. És ez nem egy munkás, hanem a testvére. Ugye nem avatkozna bele egy családi összejövetelbe?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Óráról órára rosszabb lesz. Elôször az ôrült sárga munkás, most meg te. Nem, uram, mi nem fizetünk a lányokért, akiket erôszakkal hoznak hozzánk; mindannyian saját akaratukból vannak itt.";
				link.l1 = "Megmentettem ezt a lányt, és soha nem fog olyan helyen dolgozni, ami alatta van. Munkás, azt mondja?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Ó, monsieur, milyen rossz idôzítés! Ma már nem fogadunk több vendéget - a saját szemével láthatja, mi történt itt.";
				link.l1 = "Ezért vagyok itt. Egy sárga bôrû ember szervezte ezt az egészet, ugye?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Igen, uram, egy munkás! Alig értettük, amit mondott! Ez a rongybaba berontott, és a hölgyet követelte. Biztosított minket, hogy ô a testvére. Hívtunk embereket, de...";
			link.l1 = "Ez nem jelentett akadályt neki. Mi történt akkor?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Mint kiderült, nem hazudott. A hölgy kijött hozzánk, és felismerte ôt. Sôt, még most is beszélgetnek a luxuslakásában.";
			link.l1 = "Bár ki tudja, mi jár a fejében. Bemegyünk oda - mentjük meg a nôt, ha kell. Ne csináljatok felhajtást - azzal tönkretennétek a hely hírnevét.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Így van, uram. Azt mondta, hogy ô a hölgy testvére.";
			link.l1 = "És maga nem engedte be...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Persze, hogy nem! A hölgy kitûnôen öltözött, és akcentus nélkül beszél, nem úgy, mint az a munkás. Megpróbáltuk elkergetni, és ô leütötte az összes ôrt, el tudja képzelni?!";
			link.l1 = "Könnyen el tudom képzelni. És hol van most?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Ô és a hölgy még mindig beszélgetnek valamirôl, de nem értjük, mirôl - valószínûleg a saját nyelvükön.";
			link.l1 = "Odamegyek hozzájuk. Talán a hölgynek segítségre van szüksége. Ne hívja az ôrséget - ha ez nyilvánosságra kerül, soha többé senki nem fog az ajtajához jönni.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Egy testvér? Az úrnô méltóságteljes, ami több, mint amit errôl a ‘testvérérôl' elmondhatok. Nincs szükség arra, hogy szórakozzanak vele, vagy megpróbálják átverni ezzel a munkással. Vigyék el.";
			link.l1 = "Mondtam, hogy már régen elvesztették egymást. Ô csak kevésbé szerencsés. Majd mi magunk fizetünk a létesítménynek az idônkért. Azonnal riassza az úrnôt.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "Nem kell ôt riasztani veled. És nem tetszik a kitartásod. Fiúk! Dobjátok ki azt a munkást! És a félrevezetett gazdáját is!";
			link.l1 = "A fenébe! Mennyi arrogancia egy kurtizánhoz képest!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "Ez nem lehet igaz! Hogy az úrnôd egyedül maradjon ezzel a furcsa társasággal? Csak ha egyedül megy oda, uram. És a... barátai odakint várnak majd - van itt egy rendes vendéglô.";
			link.l1 = "Miért aggódsz miatta? Mindenki tudja, hogy ô Tortuga egyik legjobb kardforgatója. És a barátaim tisztességesebbek, mint a legtöbb ember ebben a városban.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Fiúk! Van itt egy sebesült bandita és egy mocskos munkás! Akarnak valamit az úrnônktôl! Intézzétek el ôket!";
			link.l1 = "Micsoda elkötelezettség, a fenébe is...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Gondolom, ön Charles de Maure? És ez... És ez...";
				link.l1 = "És ön bizonyára Belle Etoile. Vagy inkább Chang Xing? És igen, ô a bátyja. Már több mint egy évtizede keresi magát. Sok-sok kérdésünk van hozzád. És nincs sok idônk.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "Te jó ég, túlélted. Elég jó védôje van, még ha egy kicsit késett is. Jobb, mint az, aki nyilvánvalóan engem tart a védelmezôjének, és most itt áll melletted. Az ég kegyes hozzád, drága lányom.";
				link.l1 = "Látom, hogy te is tudod. Ez még jobb - nem kell magyarázkodni. De mondd csak, min mosolyogsz, Csang Hszing? Élvezed nézni, ahogy más lányok szenvednek, ugye? Elvégre te adod el ôket.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, igaz? Hallottam, hogy látni akartál. Szóval, mi bántja magát? Nem tetszett a kiszolgálás nálunk, amikor legutóbb itt járt?";
				link.l1 = "Most jövök egy másik létesítményébôl, Chang Xing. "+ sStr +", a szeretôm meghalt. És tudom, hogy maga is szerepet játszott benne.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... Régen hallottam ezt a nevet. Nagyon régen. Fehér emberek... mindig sietnek. Mit szólnál egy nyugodt családi összejövetelhez? Nem érdekel. Már évekkel ezelôtt felhagytam azzal, hogy másokra hagyatkozom. Miért nem mondasz semmit, testvérem? Nem örülsz, hogy láthatod a saját húgodat? Végül is olyan könyörtelenül kerestél engem.";
			link.l1 = "Más sürgôs és fontosabb dolgunk van, amivel foglalkoznunk kell. Beszélj a húgoddal, Longway. De ne feledd, hová kell még mennünk. Sietnünk kell. És nekem is vannak kérdéseim hozzá.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(mandarinul) Hosszú út, mi? Hát, a neveden kívül nem sokat változtál... Chang Tu.";
			link.l1 = "(mandarinul) De sokat változtál, húgom. Mi történt? A tekinteted régen olyan meleg volt, mint a déli nap. Most hideg, és csak megvetést fejez ki. És a hangod? Régen szerettelek megnevettetni, és hallgatni az ezüstcsengettyûket... Most hidegebb, mint egy Goango télen. És te az ô ruháikat viseled. És te magad adod el a nôket, pedig egyszer Fermentelos elrabolt téged.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Azért jöttél ide, hogy kioktass engem, pedig egykor Rodenburgnak, a szigetvilág egyik legnagyobb gazemberének dolgoztál? Azt hiszed, nem tudtam rólad? Mindig is tudtam. Nem a te dolgod megítélni, hogy mivé váltam és miért, félrevezetett bátyám.";
			link.l1 = "Hadd derítsem ki, Xing! És mondd meg nekem. Ha tudtad, hogy a szigetvilágban vagyok, miért nem akartál találkozni velem ennyi év után? Egész életemet a keresésednek szenteltem...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Mert sem te, sem az Ég nem védett meg a legszörnyûbb sorstól. Aztán rájöttem, hogy ezen a világon senkinek sincs szüksége senki másra. Csak magunkra számíthatunk. Nos, elmondom, ha tudni akarod. De az ô nyelvén fogok beszélni. Biztos vagyok benne, hogy ô is szívesen hallaná. Ugye értesz franciául, Tu?";
			link.l1 = "(tört francia nyelven): Igen, beszélem ezt a nyelvet.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ha ha ha ha, ó, Istenem! Szörnyû az akcentusod. De nem a te hibád - a francia kiejtés és írás valóban nehéz.";
			link.l1 = "Most már másképp nevetsz, húgom...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			ReturnOfficer_Longway();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Kedves bátyám tudni akarja, mi történt velem az évek során. Azt hiszem, jó lenne, ha te is meghallgatnád - ahogy mondtad, vannak kérdéseid. Úgyhogy ne aggódj - mindent elmesélek neked franciául.";
			link.l1 = "Csak a lényeget mondd el - amikor Longway elmesélte nekem az élettörténetét, jó néhány óráig tartott. És én most sietek.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Legyen türelmes. Több mint egy évig tartottam magamban az egészet. És ha félbeszakít, nem fogok válaszolni a kérdéseire.";
			link.l1 = "Rendben... Akkor folytassa.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Hol van a jó modorod, Charles de Maure? Azt mondták nekem, hogy ön egy kiváló modorú férfi, és egy mintaszerû nôi' ember. Csak pletykák, de a valóságban... egy bukás? Én is így gondoltam. És tévedsz - minden férfit és nôt egyformán utálok. Igazából nem bízom senkiben, nem csodálkozom, nem várok semmit. Szívesen szétzúznám a heréidet, ha a kezem közé kerülnél. De az igazi nevemet hallani ennyi év után egy kicsit... felüdítô volt.";
			link.l1 = "Én egy nôi' férfi vagyok a hölgyek számára, nem a hozzád hasonló boszorkányok számára. És különben is, mit vártál, tekintve, hogy részt veszel annak a személynek a kínzásában, aki a legjobban érdekel? Alig tudom visszafogni magam, hogy ne tegyek veled is valamit. Nem utolsósorban az ô kedvéért. Longway a barátom. Te pedig a családja vagy. Már több mint egy évtizede keresi magát. És megérdemli, hogy beszéljen veled.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Milyen szentimentális. És milyen szomorú, hogy nem érdekel. De most már nem úszod meg ilyen könnyen, igaz, Tu? Azért nem, mert egyszer megöltelek, és mindannyian elkéstetek. De tudva... Azt hiszem, megérdemled, hogy tudd. Ismertél engem, amikor még nem voltam ilyen, testvér.";
			link.l1 = "Nem számít, mi történt veled... mindig volt választásod, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Még fiatal vagy, és nem tudod, hogy mûködik a világ, Charles de Maure. Csak egy igazi választás van az életben: élni vagy meghalni. Azt hiszem, jó lenne, ha te is mindent tudnál. Ezért elmondom a történetemet franciául. Te beszélsz, ugye, Tu?";
			link.l1 = "Akcentussal. De nagyon jól érti. Kezdheted.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "És hol voltál egész idô alatt? Espanola csak egy-két napra van innen. Az ô halála is a te hibád. És a te hibád is. Több mint egy évtizedet késtél. A megmentôink, a védelmezôink. Minél hamarabb megtanulja egy nô megvédeni magát, annál jobb. Van, aki idôben megtanulja, van, aki nem. És valakinek nincs elég esze, hogy eljusson hozzá.";
			link.l1 = "Vigyázz minden következô szavadra. Még mindig nem téptelek darabokra, csak a barátom, a bátyád miatt. Fogalmad sincs, hogy ô min ment keresztül érted.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Erôsen kétlem, hogy bármi olyasmin ment volna keresztül, mint amin én.";
			link.l1 = "Szóval mondd el nekünk.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Nos, mit mondhatnék, fiatal, ostoba és naiv voltam akkoriban. És intoleráns. Tu már mesélt neked arról, hogyan rabolt el Oliverio Fermentelos, miután megölte a szüleimet és engem?";
			link.l1 = "Igen, így van.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Udvarolt nekem, és bevallotta az érzéseit, de én visszautasítottam. És ekkor lemészárolta a családunkat és elrabolt engem. És aztán...";
			link.l1 = "Kitalálom.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Bárcsak tudnád. Aztán újra bevallotta nekem az érzéseit, forrón és sírva, mondván, hogy ez az egyetlen módja, mert a családom soha nem engedne el vele.";
			link.l1 = "Ôrület...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, egy szó, ami az egész életemet leírja azóta. Újra visszautasítottam ôt. És ez így ment egy darabig. De nyilván nem tarthatott örökké, mert teljesen ki voltam szolgáltatva neki.";
			link.l1 = "Szóval megtörtént?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Hát persze. Erôszakkal, durván és könyörtelenül elvett. Nem mintha ez valaha is zavarta volna az erôszaktevôket, de nem ô vallotta meg nekem korábban könnyes szemmel a nagy szerelmét? Pfft! A szerelem nyilvánvalóan elmúlt. És mindez minden nap folytatódott, mintha csak rutin lenne. Eleinte kiabáltam és ellenálltam, de aztán abbahagytam - amúgy is, mi értelme volt...?";
			link.l1 = "De Fermentelos megkapta, amit megérdemelt, és te itt kötöttél ki. Hogy történt ez?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Nos, elég hamar elege lett belôlem. Vicces, nem igaz? Megölte az én és Tu szüleimet, ellopott, rendszeresen meggyalázott, hogy aztán a végén eldobjon. Eljött erre a szigetvilágra, és eladott Levasseurnek rabszolgának.";
			link.l1 = "Nem kívánnám ezt az ellenségemnek. És hogy élted túl? És egyáltalán, hogy szabad lettél? Ahogy hallottam, Levasseur sosem engedett ki nôket a rejtekhelyérôl. Mindig megszabadult tôlük.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "Most már ez a helyzet. Levasseur akkoriban más volt. Nem, ô mindig is állat volt. De eleinte idônként elrabolt helyi fiatal telepesnôket, megerôszakolta ôket a pincéjében, és szinte azonnal megszabadult tôlük, hogy ne kelljen fizetnie a hallgatásukért. Csak ritkán tartotta ôket néhány napnál tovább azokban az években. Velem viszont kezdettôl fogva más volt a helyzet.";
			link.l1 = "Mert rabszolga voltál, igaz?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Pontosan. Levasseur legfôbb vágya nem csak a testi gyönyör volt. És még csak nem is az áldozatai feletti hatalom pillanatnyi érzése - elvégre az egész sziget fölött az övé. De...";
			link.l1 = "...az élvezet, hogy láthassa, ahogy megtörik - az akaratuk, a kinézetük, a hangjuk, a viselkedésük.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Igen. Látom, megcsinálta a házi feladatát, kapitány. De ebben a tekintetben nem voltam szórakoztató számára - Fermentelos már összetörve hozott. Levasseur pedig nem tartott szépnek - nem szereti az ázsiai nôket. Tudja, ez valamiért nagyon meghatott - rájöttem, hogy vonzó vagyok, de nem tart igazán szépnek. És nem hiszem el, amikor ezt mondják nekem. Még most is, amikor tornázom, selymet viselek, és finom parfümmel fújom magam. Nem mintha szükségem lenne a kínzóm jóváhagyására, de...";
			link.l1 = "Nos, akkor megismétlem a kérdésemet - hogyan élted túl? Amint megun egy nôt, megszabadul tôle. Veled, ahogy mondod, kezdettôl fogva unatkozott.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Gondolom, az a tény, hogy kezdettôl fogva untattam ôt, hatott. És az a tény, hogy rabszolga voltam - nem mehettem sehova, és nem mondhattam semmit. A rabszolgalányokkal évezredek óta így bánnak. Elkezdett azon gondolkodni, hogyan lehetne a velem töltött idôt ‘szórakoztató' számára.";
			link.l1 = "Azt hiszem, így született meg a függôsége, a jelenlegi formájában.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Pontosan. Eleinte verés, köpködés és egyéb megaláztatások voltak. És gúnyolódás - mind a külsôm, mind a származásom, a vérem miatt. Aztán jöttek az elsô kínzások - kések, fogók, serpenyô... Ezért hordok ilyen zárt ruhákat - az egész testem sebhelyes, megégett és megcsonkított. És ezért nem tervezem, hogy soha többé nem vetkôzöm le férfi elôtt. Soha többé. Aztán végre rájöttem, amire már akkor rá kellett volna jönnöm, amikor Fermentelos elrabolt.";
			link.l1 = "Mi volt ez?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Hogy nem lehetek többé egy tehetetlen bábu. Épp ellenkezôleg, nekem kell irányítanom az életemet. Nálam az volt a helyzet, hogy egy nô csak úgy tudja valamilyen módon megváltoztatni az életét, ha irányítja a körülötte lévô férfiakat.";
			link.l1 = "Nem mondanám, hogy Levasseurt lehet irányítani.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "És nem is tévedne. De óvatosan befolyásolni lehet ôt. Levasseur egyformán utálja mind a teljes engedelmességet kezdettôl fogva, mind az érvelést vagy a könyörgést. Ahogy a hízelgést is - látszólag rájött, hogy milyen disznó is ô valójában. Erre rögtön rájöttem, eléggé gyötrelmes áron. De amikor a kínzások és erôszak újabb estéje után mindennel megelégedett, már lehetett vele finoman beszélni. Lehet, hogy nem vagyok nemesi származású, de nem vagyok híján az intelligenciának.";
			link.l1 = "És mirôl beszélgettetek?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Felkeltettem az érdeklôdését. Ötleteket javasoltam a kínzásra, tanácsot adtam, hogy milyen kínzóeszközöket nem érdemes használni, és melyikkel érdemes kezdeni. Elôször persze mindezt rajtam próbálta ki. De aztán... elkezdett tisztelni engem, a maga csavaros módján. Mi játszódik le a fejében? Próbáltam kideríteni, hogy hogyan lett ilyen, de megint félholtra vert. Aztán behívott egy személyi orvost.";
			link.l1 = "Ez még furcsább és undorítóbb, mint amit eddig hallottam róla.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Már nem követelte, hogy adjam oda magam neki. Tanítványnak nevezett engem. De mindig azt mondta, hogy mint az ô projektje, teljes csalódás voltam. Gondolom azért, hogy a sarkamban tartson. Ezért kezdett el vívást és nyelveket tanítani nekem. Bár a pincében tartott, az összes drága ruhát én kaptam, nem a felesége.";
			link.l1 = "Valóban egy projekt. Egyértelmû párhuzamot láthatsz azzal, ahogyan te vezeted a helyet.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Erre nem is gondoltam, hmmm. És nem tetszik a párhuzamod, mert én nem kínzom a nôi alkalmazottaimat. És nem hagyom, hogy az ügyfeleim megtegyék. Még akkor sem, ha utálom azokat a ribancokat és irigylem a szépségüket. És semmi közös nincs bennem azzal a disznóval, ezt ne feledd.";
			link.l1 = "Szóval, hogy szerezted ezt a bordélyházat?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "Levasseur-tôl, természetesen. Egy ideig nála tartott. Idôrôl idôre még tanácsot is kért, hogyan törjem meg ezt vagy azt a lányt. Elvégre különleges voltam a számára, még ha ezt soha nem is vallotta volna be. Én voltam az elsô. Én láttam mindent.";
			link.l1 = "Ki is tanult kitôl?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Én nem vagyok ilyen! Teljes lelkemmel gyûlölök mindenkit, akinek mindent tálcán adtak a kezébe! Ez nem igazságos! Ez a bordélyház az én ötletem volt! A munkásaim kereskedôk, hivatalnokok és nemesek lányai, akik néha összejöttek Levasseurrel. Én kértem, hogy adja ôket nekem. A kínzás és a megaláztatás egy titkos pincében egy dolog. De egy kurtizán nyilvános tevékenysége a hozzájuk hasonlók számára egészen más!";
			link.l1 = "Nem mondanám, hogy a nôi munkásai ennyire megalázottnak, nyomorultnak és megtörtnek tûnnek.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Mert ôk tudják, hogy mit tesz velük Levasseur vagy akár én, ha csak egy hangot is adnak ki. De részben persze igazad van. A bor, az ételek, a selymek, a mindennapos kínzások hiánya - sokan közülük kezdtek megmentôként tekinteni rám. Átkozott bolondok! Csak néhányan nem örülnek, hogy itt vannak. Némelyiket nehéz szívvel adta el. Ô pedig kuncogott, mondván, hogy bármelyiküket bármikor visszaadhatom neki, cserébe azért, hogy megoldom a helyem pénzproblémáit. De én mindig nemet mondtam. Így legalább visszahoznák az aranyat, ahelyett, hogy a pincében pusztulnának el a semmiért. Túl könnyû kiút lenne számukra.";
			link.l1 = "Milyen kár, hogy nem mindenki érezte magát megalázva, a Szent Inkvizíciónál is rosszabb klastromot aranykalitkává változtatva, mint amilyen a bordélyházad...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Elítélsz engem? Nemcsak túlélni akartam, hanem sikeres kereskedelmet építeni. Bár tudtán kívül, Levasseur hálás volt nekem. Bár már nem voltam rabszolga, mégsem tudott elengedni. Még mindig kénytelen voltam neki dolgozni és segíteni a csatlósainak. Különösen a vézna unokaöccsének, aki minden alkalommal, amikor meglátott, csorgatta a nyálát utánam. De nem mert megtámadni, vagy csúnyán beszélni velem. Undorító. Tudod, még ha csalódásnak is nevezett, hasznosabb voltam, mint Thibaut és Martene együttvéve. Elég gyakran elkísértem ôket a parancsára, ahogy akkor Kikötô-au-Prince-ben is tettem.";
			link.l1 = "Ez sok mindent megmagyaráz...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "Igen, így van. Hallgassa meg. Nem kínoztam meg a szeretôjét. Mint ahogy egyetlen lányt sem kínoztam ezekkel a kezekkel, még ha néha tanácsokat is adtam Levasseurnek. De ha már itt tartunk...";
			link.l1 = "Micsoda?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Mint azt ön is tudhatja, Levasseur néha követelte, hogy hozzak neki egy bizonyos lányt, akit Tortugában pillantott meg, majd elhagyta a szigetet. Vagy valaki meglepi ôt, és elhoz neki egy idegent, hogy elnyerje a kegyeit, ahogy velem is történt. A kedvesed elrablása az én ötletem volt.";
			link.l1 = "Mit mondtál az elôbb...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Elôször azon gondolkodtunk, hogy elkapjuk azt a szôkét, aki régen olyan közel állt hozzád. De mivel most már érinthetetlen, és mivel már ígértünk neki egy lányt, neked, vöröske, kellett megtenned.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Hallottam pletykákat a gyönyörû társadról, aki sosem hagy el téged. Tekintve, hogy Levausser imádja a szôkéket, nem volt nagy gondom, hogy eladjam neki ezt az ötletet.";
			dialog.text = "Sottának, a korcsának kellett volna elhoznia neki a mulattot, Lutter feleségét. De te megölted Sottát, így - nincs mulatt a nagy embernek. Levasseur dühös volt. Mindenki kiakadt - Thibaut, Martene, még én is. Nem is tudom, ki dühített fel jobban: ô, mert megint megvert, vagy te, aki ezt okozta... "+ sStr +"";
			link.l1 = "Szóval nem is miatta... Te tetted ezt.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Nem is remélem, hogy megbocsátasz, sôt, nincs is rá szükségem. Ha vért akarsz, vért fogsz kapni. És nagyon meg fogod bánni. De én nem fogom megtagadni a megértést. Hosszú tíz év óta elôször tudnám használni. Mindig csak annyit tettem, hogy mindent megtettem, hogy egy nap kijussak Tortugáról. Van kérdésed hozzám, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "De ön is részt vett az emberrablásban. És tudja, hol tartja Levasseur az áldozatait. Mondja el, hol van. És ha nem történt meg a legrosszabb - jól meggondolom, hogy ne álljak bosszút magán.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Nos, végre összeállt a kép...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "Tudom, mert ott voltam. És ha az a benyomásod, hogy kölcsönösen és egészségtelenül kötôdöm hozzá - akkor nagyot tévedsz. Örülnék, ha valaki nyársra húzná azt a disznót.";
			link.l1 = "Nincs idôm, Chang Xing. Hol van?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Ismered a helyi börtönt a város utcái alatt? Oda fogsz menni. Az egyik zsákutcában van egy nagy boroshordó, mellette pedig egy titkos átjáró kezdôdik a kéjszobájába, ahogy ô néha nevezi.";
			link.l1 = "Nos, végre összeállt a kép...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Jó neked. Most pedig kifelé. Bármennyire is szerettem volna ennyi év után beszélni, a felismerés, hogy ismeri az összes titkomat, tudja, mit tettek velem - undorító. A látványodtól most már csak dühös leszek. Ó, és Tu velem marad.";
				link.l1 = "Miért van ez?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Talán mert én vagyok a családja? És mert látom, milyen veled - egy levert, szerencsétlen motyogó, akinek még arra sem volt ideje, hogy teljesen megtanulja a nyelvet és elkezdjen rendesen beszélni. Mégis azt mondta nekem, hogy ti ketten barátok vagytok. Világos, hogy milyen hatással voltál rá. Legalább férfit faragok belôle.";
			link.l1 = "És te tényleg elégedett vagy magaddal? Mit fogsz csinálni belôle? Egy kegyetlen, keserû teremtéssé, aki életekkel kereskedik?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Kapitány úr, kérem, hagyja abba. Arra kérlek, hogy hagyd békén a húgomat. És... Én vele maradok.";
				link.l1 = "Te... mi? Hosszú út... de miért? Nem látod, hogy mivé vált?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Te más vagy? Megváltoztál az idô múlásával. Rosszabbra. Eleinte udvarias és megértô voltál. De aztán durva lettél, még durvább, mint Rodenburg. És amikor szükségem volt egy jó hajóra, hogy elkapjam Van der Vinket, te egy szemetet adtál nekem!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Egyszer elindultam a tengerre, és annyi évet töltöttem azzal, hogy megtaláljam és megmentsem a húgomat. És most itt van és biztonságban. A küldetésem teljesítve. És... A nevem Chang Tu. Longway a név, amit az áruló Van Merden adott nekem, ha esetleg elfelejtetted volna. De Chang Tu szabad ember. Chang Tu hosszú útja végre véget ért.";
			link.l1 = "Szolgát csinál belôled, mint egykor Rodenburgból. Nyomást fog gyakorolni rád, mert családtag vagy. És te ilyen könnyen annak az oldalára állsz, aki nekem és a " + sStr + " annyi fájdalmat okozott?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Most te vagy az, aki Chang Tu-t nyomasztja. Kérlek, engedj el. Nagyon fáradt vagyok. Maga jó ember, kapitány - ezt az ég is tanúsíthatja. De maga nem tartozik a családomhoz. Ô az. Ha nem maradok, akkor hiábavaló volt ez a sok év. Most én leszek az ô vezércsillaga, és újra fellobbantom a kialudt tüzet - meleg és vigasztaló, nem éget el mindent, amihez hozzáér.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hmm, igazad van. Lehet, hogy most túl keményen nyomulok. Nos, én mindig is tiszteltelek téged. Kívánom, hogy legyen régóta várt családi találkozásod a húgoddal. De figyelmeztetlek, nem fogsz békét találni vele.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Most nem hagyhatsz itt! Még mindig meg kell mentenem " + sStr + " Levasseurtól! Azt akarod, hogy egyedül menjek oda? Segíts nekem, Longway. És akkor elengedlek. Megígérem neked.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Meg tudom oldani. Nem kell többé aggódnod miattam. Köszönöm. Köszönöm.";
				link.l1 = "Úgy tûnik, a húgod dühös, hogy úgy döntöttünk, békésen elválunk.";
			}
			else
			{
				dialog.text = "Ki fogod találni, kapitány úr. Maga a legintelligensebb ember, akit valaha láttam. Könnyedén elbánsz azzal a féreggel, aki csak a nôk kínzásához szokott. Csak kérlek, ne kényszeríts. A nôvéremnek annyi mindenrôl kell beszélnie velem! És... a nevem Chang Tu.";
				link.l1 = "Felfogtad, hogy azzal, hogy most elhagysz, elárulsz engem?! Különösen azzal, hogy vele maradsz - a nôvel, aki ezt az egészet elkezdte!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Ne féljen, kapitány. Bár tiszteletlenül beszél rólam, én vagyok az idôsebb testvére és az utolsó férfi rokona. Elmehetsz. Nem hagyom, hogy megöljön. Viszlát.";
				link.l1 = "Viszontlátásra... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "Elmondtam mindent, amit mondani akartam. Viszlát, kapitány. És sok szerencsét. Chang Tu mindig szabad ember marad. Ezt ne felejtsd el.";
				link.l1 = "És ezt kapom, miután mindent feladtam, és segítettem neked a keresésben?! Azok után, amit most tesznek a " + sStr + " ?! Te egy áruló vagy, Chang Tu. És úgy is fogtok meghalni, mindketten, ti kibaszott kígyók!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "A nevem Chang Tu. Longway halott. Te ölted meg. Nem vagy többé a kapitányom. És most meg fogsz halni. A családom végre békére lel, és a csillagunk fényesen ragyog majd az éjszakai égbolton.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Megbízható) (Vezetô) Hosszú út... Chang Tu. Állj! Tudom, hogy nem én voltam a tökéletes kapitány számodra. De tényleg ennyire meg akarsz ölni ezért? Azok után, amin keresztülmentünk? Elôször Rodenburg, most pedig a húgod keresése.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Megbízható", "Trustworthy");
				notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, én vagyok a kapitányod. Nem a családod és nem a bébiszittered. Parancsokat adok, és nem azon gondolkodom, hogy véletlenül megsértettelek-e. Úgy követelsz, mintha régi házastársak lennénk, az Isten szerelmére...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Megbízható")) Notification_Perk(false, "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Képességpróba Sikertelen (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Igen, uram. Most már látom. Te is ugyanolyan rohadt szemétláda vagy, aki csak magával törôdik... Hosszú út. Akárcsak a húgod. A családom túl fogja élni a napot. A tiéd nem. Menj a pokolba!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Ha választani kell közted és a családom között - én a családot választom, még ha nehéz is a választás.";
			link.l1 = "Egy család, amelyik a kisujját sem mozdította, amíg te kerested ôt ennyi éven át? Ó, de aztán egyszer csak eljött a megfelelô idô! Ami engem illet, én mindent feladtam, hogy segítsek neked. Te, aki itt állsz, ennek az eredménye vagy. A pokolba is, én jobban a családod vagyok, mint ô, barátom!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Igazad van. Mint mindig, most is igazad van. Megbocsátasz nekem, kapitány úr?";
			link.l1 = "Nincs mit megbocsátani! Egy dologban igazad van - nem voltam mindig az a kapitány, akit megérdemeltél. Azt hiszem, ettôl most már kvittek vagyunk. Egyébként, hogy szeretnéd, hogy mostantól hogyan szólítsalak? Longway? Vagy Chang Tu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Legyen Hosszúút. Már megszoktam, hogy így szólítasz.";
			link.l1 = "Akkor felejtsünk el minden nézeteltérést, és üdvözöljük újra a fedélzeten, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Tu! Mit beszélsz?! Miért álltál meg?! Öljétek meg! Mindig csak egy munkás leszel neki! A családod én vagyok, és csak én!";
			link.l1 = "Nagyon dühös, ugye, Longway? Te már nem vagy a családja, Xing. Ennek akkor lett vége, amikor megtudtad, hogy Longway megérkezett a szigetvilágba, és úgy döntöttél, hogy nem veszel róla tudomást. Elmegyünk.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Azt hiszem, sosem volt igazi esélyem arra, hogy gyökerestül kiûzzem belôle a rabszolga mentalitást. Nem tudom megmenteni. Akkor én magam öllek meg mindkettôtöket.";
			link.l1 = "Te vagy itt az egyetlen, akit nem lehet megmenteni. Tudod, túl megértô és megbocsátó voltam veled szemben. De ez még jobb. Azt hiszem, még Longway is rájött, milyen kígyó vagy. Nem fog túlságosan gyászolni téged.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "A viccek most már nem helyénvalóak! A félelmedet és a kudarcodat rejtegeted mögéjük! Ami csak még jobban meggyôzött. Védd magad, de Maure! Mert Chang Tu nem szándékozik megkímélni téged.";
			link.l1 = "Sajnálom, hogy így végzôdött. De ha így akarod, hát legyen. Ebben az esetben, tôlem sem fogsz kegyelmet kapni.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, figyelj...";
				link.l1 = "Helen?";
			}
			else
			{
				dialog.text = "Charles, Longway, állj...";
				link.l1 = "Helen, jobb, ha most mögém állsz. Nagyobb biztonságban érezném magam, ha így tennél, ha esetleg megtámadnának minket.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Olyan fáradt vagyok, alig bírok állni. Csak ki akarok jutni innen. Nem fogjuk visszarángatni Longwayt a hajóra, ha nem akar jönni, ugye? Én leszek a navigátora és az elsô tisztje, kapitányom. Remélhetôleg a legmegbízhatóbb és legkedvesebb embere is. Egyébként is, igaza van - mi nem vagyunk a családja. Ô az, jóban-rosszban.";
				link.l1 = "De mi van vele? Ô az oka annak, hogy megkínozták, az egész az ô ötlete volt. És ô az, aki elrabolt téged.";
			}
			else
			{
				dialog.text = "De ôk nem fogják, igaz? Csak menjünk el, ennyi az egész. Ha ezt gondolja rólunk mindazok után, amit érte tettünk, akkor nincs értelme megpróbálni megváltoztatni a véleményét. A tettek hangosabban beszélnek, mint a szavak. Ha a nôvérével akar maradni, hagyjuk.";
				link.l1 = "Helen, annyi mindent elszenvedtél miatta...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Hagyd békén azt a démont a démonaival. Hamarosan felemésztik a lelkét. A miénk pedig megérdemli a pihenést. Gyerünk, menjünk.";
				link.l1 = "Igen. Azt hiszem, így van. Menjünk innen, angyalom. És te - Longway, vagy Chang Tu - viszlát.";
			}
			else
			{
				dialog.text = "De én nem haltam meg. És a legrosszabb nem történt meg. Itt vagyok, veled, és csak ez számít. És Levasseur halott. Nélküle a lány egy senki. Az üzlete veszteséges, és hamarosan tönkremegy. És ôk is vele együtt mennek a süllyesztôbe. Menjünk, kapitányom. Itt már nincs mit tennünk.";
				link.l1 = "Nem fogok vitatkozni, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Hová megy?";
			link.l1 = "Mi az, meglepôdtél, hogy nem akarjuk kiönteni a te és a nôvéred belét, Longway? Ez a különbség köztünk. És még mindig azt hiszed, hogy én vagyok a rosszfiú... De rendben, nézd. Ha meg akarsz ölni, akkor Helent is meg kell ölnöd. Megsebesült, megsérült. Tényleg ezt akarja tenni?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Mm-hmm.";
			link.l1 = "Látom a kétséget a szemedben, még akkor is, ha rengeteg haragot táplálsz ellenem. De vegyünk példát Helentôl, rendben? Senki sem kedvesebb és megbocsátóbb nála a csapatunkban. Elmegyünk. És ha maradt benned egy kis jóság vagy értelem, nem fogsz az utunkba állni.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Legyetek olyanok. Bocsánatot kérek. De maga már nem a kapitányom.";
			link.l1 = "Majd valahogy túljutok rajta. A legjobbakat kívánom neked és a nôvérednek, annak ellenére, amit tett. Viszlát, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Gyerünk, Charles, itt az ideje, hogy eltiporjuk ezt a lázadást.";
			link.l1 = "Isten tudja, hogy nem akartam ezt tenni... és még mindig nem akarom.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "Nem igaz?! Charles, figyelj rám. Olyan sokat tettél érte, és mit kaptál cserébe? Árulást és csúnya szavakat, rendben! Tényleg hagyod ezt annyiban?";
			link.l1 = "Nem akarom Longway vérét ontani. Nem felejtettem el, hogy valaha barátok voltunk.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Cseszd meg az ilyen barátokat - rosszabbak, mint az ellenségek, rendben?! Charles, nézz rám. Nézd meg, mi történt velem - a húga miatt, aki kigúnyolt, sértegetett és megalázott engem az úton erre az átkozott szigetre!";
			link.l1 = "Mary, megértem - most nagyon, nagyon dühös vagy...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "Ó, nem, Charles, nem csak dühös vagyok, nem... Dühös vagyok! És nem csak azért, amit az a nyomorult kis szemétláda mondott neked! Nézz rám újra, Charles - és képzeld el, hány lány fog még ezen keresztülmenni, ha nem vetünk véget ennek. Itt és most.";
			link.l1 = "Senki mást nem fognak bántani. Levasseur halott.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, te tényleg hallgattad azt az eretnekséget, amit a nô szajkózott? Ô ugyanolyan felelôs azért, ami a pincében történt, mint az a büdös disznó. Most nézd meg Longwayt - vagy bármi is legyen a neve most. Nézd meg, milyen gyorsan sikerült a maga oldalára állítania, rendben! Ki tudja, milyen beteges ötleteket ültet még annak az árulónak a fejébe? Gondolod, hogy annak a démonnônek sok gondot fog okozni, hogy Levasseur útjára terelje? Ne gondolj arra, hogy most mi ô, Charles. Gondolj arra, milyen szörnyeteggé válhat egy év múlva... vagy akár egy hónap múlva. Tudod, hogy igazam van, ugye?";
			link.l1 = "Bármennyire is utálom beismerni, nincs semmi, amivel ellentmondhatnék neked, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ha-ha-ha-ha! Lenyûgözô, micsoda elôadás. Régóta nem nevettem ilyen szívbôl jövôn. És van bátorsága, azt meg kell hagyni.";
			link.l1 = "Fogd be a szád, te ribanc.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "Ez mulatságos, nem igaz, de Maure? Szívesen megnézném, ahogy Tu magam is elintézi magát. És itt az asszonyod épp olyan vérszomjas, mint én. Nagyon jó. Nem fogok tétlenül állni - Levasseurrel és Tortuga néhány legjobb kutyájával edzettem. Lássuk, kinek a duója kerül ki gyôztesen.";
			link.l1 = "Nem volt túl jó tanárod. És felbosszantottad Mary-t. Végeztél. Ha nem lennék itt, akkor sem lenne esélyed ellene.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Igen, uram. Végre. Beszélhet Longway újra a húgommal, kapitány úr? Nem sokáig.";
			link.l1 = "Nemsokára. Csak gyorsan - nincs sok idônk.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway, siessünk.";
			link.l1 = "Jó.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "És mit akartál mondani nekem, testvérem?";
			link.l1 = "Ez a Longway nagyon csalódott benned, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(mandarinul) Miért nem beszélsz a mi nyelvünkön, ha már megint beszélgetni akartál, Tu? Zavarban vagy miatta? A helyedben én inkább az akcentusod miatt szégyellném magam.";
			link.l1 = "Nem. Longwaynek nincsenek titkai a kapitány úr elôtt. Többé már nincsenek.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(in French) Elôször Rodenburg, most de Maure. Mindig kell egy ‘monsieur.' Több mint egy tucat év alatt semmit sem ért el itt. Még a nyelvüket sem tudod megtanulni. Pedig sokkal egyszerûbbek, mint a mieink! Ha valaki csalódást okoz, az te vagy.";
			link.l1 = "De én nem kereskedem nôkkel. Nem veszek részt az elrablásukban és kínzásukban.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Ez most komoly? Felsoroljam, mit tettél Rodenburgért? Amit én csináltam, ahhoz képest gyerekjáték lenne.";
			link.l1 = "Volt egy célom - megtalálni téged. De te még csak látni sem akartál. És amikor megtaláltalak, egy szörnyeteget találtam, nem pedig a meleg vezércsillagot, ami egykor az utamat szegélyezte.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Egy szörnyeteg? Nos, talán igazad van. Már nem vagyok az a vidám lány, akit ismertél. Ha ilyen maradtam volna, az élet megrágott volna és kiköpött volna. Meg kellett növesztenem a saját fogaimat. A csillagom már rég kialudt. De még mindig a húgod vagyok, Tu.";
			link.l1 = "Nem. Már nem vagy a húgom.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Ilyen könnyen lemondasz rólam ennyi év után? Heh... És ki tudja, talán még mindig ugyanaz lennék, ha aznap idôben hazaértél volna, hogy megöld Fermentelost?";
			link.l1 = "Igazad van. Részben az én hibám is. Az én felelôsségem. És véget vetek neki. Megszabadítalak a szenvedésedtôl. Véget vetek ennek a nyomorult létnek.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Tényleg meg akarod ölni a saját húgodat, Chung Tu? Nem mintha sikerülne, de tény, hogy...";
			link.l1 = "Már nem vagy a húgom. Xing tíz évvel ezelôtt meghalt. És ma van az a nap, amikor Chung Tu végre meghal. Mostantól kezdve és mindörökké, a nevem... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Elôször is, megmentjük Chang Xing-et.";
			link.l1 = "Micsoda?! Úgy tûnik, nem érted, barátom. A húgod nincs közvetlen veszélyben, de a " + sStr + " igen. És kell-e emlékeztetnem, hogy Chang Xing ugyanúgy hibás ezért, mint Martene és Thibaut?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ez nem igaz! Ô...";
			link.l1 = "Van valami ötleted, hogy Levasseur mit csinálhat a " + sStr + " , amíg mi itt vitatkozunk?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "De csak Chang Xing maradt nekem, kapitány... A családja még mindig sértetlen...";
			link.l1 = + sStr + " Lehet, hogy nem a feleségem, de olyan kedves nekem, mint a saját családom.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing az utolsó vezércsillagom, kapitány. Mellesleg, tartozol nekem, amiért kiszedtem Robert Martenbôl a vallomást.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "A húgod után megyünk, ígérem. De Levasseur nem nyúlt hozzá egész idô alatt. " + sStr + " sokkal nagyobb veszélyben van, mint Chang Xing. Ha segítesz megmenteni ôt, akkor jövök neked egy nagy szívességgel.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(megbízható) (vezetés) A húgod után megyünk, ígérem. De Levasseur nem nyúlt hozzá egész idô alatt. " + sStr + " sokkal nagyobb veszélyben van, mint Chang Xing. Ha segítesz megmenteni ôt, akkor jövök neked egy nagy szívességgel.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Megbízható", "Trustworthy");
						notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Hallgassanak meg! A húgod biztonságban van. De " + sStr + " most egy perverz kezében van, aki most is kínozhatja ôt - vagy még rosszabb! Gondolod, hogy Levasseur megengedné a húgodnak, hogy egy ilyen elôkelô létesítmény tulajdonosa legyen, ha úgy bánna vele, mint a többi szegény lánnyal a börtönében?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Megbízható")) Notification_Perk(false, "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Képességpróba Sikertelen (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Nem fogom az idôt értelmetlen vitákra pazarolni. Mindannyiunknak megvannak a saját prioritásai. Váljunk szét újra. Az én Istenem segítsen engem, a tiéd pedig téged.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Igazad van. Tartozom neked eggyel. Rendben, ahogy akarod. Különben is, nélküled nem tudnék megbirkózni Levasseurrel és az embereivel. De ha valami történik a " + sStr + " , amíg a húgoddal foglalkozunk...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Köszönöm a megértését, kapitány úr. Sok szerencsét!";
			link.l1 = "És neked, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Az üres fenyegetések üres fenyegetések, kapitány úr. Sietnünk kell, hogy mindenre idôben odaérjünk.";
			link.l1 = "Remélem, az Istened meghallgatja. Gyerünk, indulás!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "'ezt tisztelettel elnézem, kapitány úr. Csak most az egyszer. Legközelebb megütlek. Most a húgom után megyek, a beleegyezéseddel vagy anélkül.";
			link.l1 = "Nem fogok több idôt vesztegetni arra, hogy vitatkozzak veled, Longway. Végül is mindannyiunknak van valami, ami mindennél drágább nekünk.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Mm-hmm, rendben, kapitány úr. De akkor sietnünk kell.";
			link.l1 = "Igen, uram. Köszönöm, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Nocsak, nocsak, ki a fene van itt nekünk... Baszd meg! Charles de Maure és a ferdeszemû korcs.";
				link.l1 = "Itt csak egy korcs van. Ha látni akarod, nézz a tükörbe, te hugenotta fattyú. Vagy csak nézd meg az unokaöcsédet. Bár ô inkább egy rühes patkányra hasonlít.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Mondtam, hogy ne zavarj! Á, Charles de Maure, hehehe. Micsoda kitartó kis nyavalyás.";
				link.l1 = "Ilyen vagyok én is. Most pedig fogd be a pofád és...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Nem a saját hajódon vagy, kölyök! Csak egy ember van ezen a szigeten, és az én vagyok!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Hogy merészeled, te szemétláda!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Nyugodj meg, unokaöcsém! Monsieur de Maure mindjárt leckét kap jó modorból.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Engedélyeztem, hogy visítozz?!";
			}
			else
			{
				dialog.text = "Hová tûnt az a sok tûz, mi, szépségem? Azt hiszem, értem...";
			}
			link.l1 = "Hagyd békén, te szemétláda!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... Kiabálhatsz és sértegethetsz, amennyit csak akarsz, de látom, hogy reszketsz, mint falevél a szélben. Látom a félelmet a szemében. Ez közös benned és Henriben. Ne vedd sértésnek, unokaöcsém.";
			link.l1 = "Igazad van, ez a félelem. De nem tôled, te szemétláda.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Persze, persze. Mindent hallottam már - hogy senkitôl sem félsz, de Maure. Ô mondta ezt nekem. 'O-oh, Charles el fog jönni, Charles meg fog menteni... Charles így, Charles úgy...' Hát, Charles itt van. Charles az elsô sorban ül. Henri, helyezze kényelembe a vendégünket.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Erre nincs szükség, bácsikám. Attól tartok, ezúttal egy kicsit túl messzire mentél...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Bácsikám, szükségem van a segítségedre...";
				}
				else
				{
					dialog.text = "Végezzek vele, bácsikám, vagy hagyjam, hogy elôbb nézze?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Nem én voltam, hanem Fehér Lovag úr volt az, aki túl sokáig tartott, hogy megmentsen. Úgy tûnik, vége a mûsornak, ha-ha-ha-ha-ha-ha!";
				link.l1 = "Istenem, ne...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Gondoltam. Hogy sikerült ilyen idôs koráig élnie? Egyébként ugyanezt kérdezem tôled is, de Maure.";
					link.l1 = "Fogalmad sincs, mennyi kérdésem van hozzád, hentes!";
				}
				else
				{
					dialog.text = "Bárcsak lenne közönség a mi kis elôadásunkban... De nem hiszem, hogy Makacs úr megadja nekünk ezt az örömöt.";
					link.l1 = "Az egyetlen öröm, amit bárki is kap, az én vagyok - azzal, hogy kibelezlek, hentes!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Gyerünk, menjetek és szedjétek fel! Ha-ha-ha-ha!";
			link.l1 = "Kibaszott állatok, még megbánjátok, hogy megszülettetek!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Mészáros? Én inkább mûvésznek, festônek tartom magam - legalább megpróbálná mûvészetnek tekinteni... Observe.\nDo you like my work? Valóban az egyik mestermûvem. Hogy teljesen ôszinte legyek, jobban szeretem a szôkéket, de ô... Végül is megbocsátottam neki ezt a csúnya hajszínt. Nem csak a hajáról volt szó - a lány olyan, mint a tûz! Majdnem megégettem magam. Harcolt, harapott, vicsorgott, mint egy vadállat! Egy vörös bôrû vademberre emlékeztetett, akivel nagyon jól szórakoztam, még ha nem is sokáig...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mészáros? Én inkább mûvésznek, festônek tartom magam - legalább megpróbálná mûvészetnek tekinteni... Observe.\nNézze, még nem végeztem vele - még mindig sok üres hely van ezen a vásznon. Nem csak gyönyörû, de kemény, mint a kô, és hideg, mint a jég. Még egy kicsit meg is kellett izzadnom, hogy rávegyem, hogy sikítson. A végsôkig kitartott, csak azért, hogy ne adjam meg nekem azt az örömöt, hogy halljam a szép hangját.";
			}
			link.l1 = "Engedd el most, te degenerált.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Mit gondolsz, hová mész? Ez a húsdarab most már az én tulajdonom. Mint ahogy minden körülötte - ez a város, ez az erôd... Én vagyok Tortuga. És te meg Poincy, az a büdös vén pulyka, ezen soha nem változtathatsz.";
			link.l1 = "Levasseur, te...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "Signor de René de Buaduflé de Lettre vagyok.";
			link.l1 = "Nem érdekel. Húzd ki a kardod, és mutasd meg, mit érsz a harcban - egy férfival, nem egy védtelen lánnyal.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "És micsoda férfi vagy! De igazad van, én is belefáradtam ebbe a sok fecsegésbe. Vissza akarok térni... a hölgyemhez. De felteszek még egy utolsó kérdést. Hogy került ide? Ki árulta el ennek a helynek a helyét? Csak egy maroknyi ember tud róla.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "A közös barátjuk, Martene, úgy énekelt, mint egy fülemüle. Valójában inkább úgy visított, mint egy disznó a vágóhídon...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Talán jobb, ha titokban tartom ön elôtt. Attól tartok, hogy ez sérti az ön egóját, Signor de René... valamit.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Az egyik áldozata, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Hazudik, maga gazember! Senki sem hagyhatja el ezeket a falakat!";
			link.l1 = "Használja az emlékezetét, gyerünk. Volt egy. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "Az kizárt. Nem ô az. Néhány ötletemet az a kis ördög szülte. Oh-oh, sokat tanítottuk egymást, hehe. Úgy döntött, hogy a végén megtisztítja a lelkiismeretét? Kétlem. Végül is, már régen kivertem belôle mindent!";
			link.l1 = "Most én foglak szárazra marni téged. Egyszerre csak egy cseppet.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "És még te nevezel engem hentesnek, te nyomorult képmutató! Heh-heh... De amíg ô a pokolban ég, addig nincs mitôl tartanom.";
			link.l1 = "Ott vár rád. És a te gazember unokaöcséd is. Ne okozzunk neki csalódást.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "Mi lenne, ha még egy kicsit jobban bántanám ezt a játékot? Vágjuk fel a hasát vagy a torkát, és nézzük, ahogy elvérzik, miközben megpróbálsz lejutni hozzá...";
			link.l1 = "Bármit is mondasz, Levasseur, bármit is mondasz... A felesége üdvözletét küldi. És ezzel együtt egy búcsúmeghajlás.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "MICSODA?! Kha-kha... Kibaszott Marceline... Te nyomorult kurva, kurva, kurva, kurva, kurva!";
			link.l1 = "Ez a nô az. Méltóak vagytok egymáshoz. Bár ô egy kicsit jobb, ha egyenes a feje. Legalábbis elsô ránézésre.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "A csirkefejét felrakom egy tüskére. De elôtte... ó-ó, sok-sok dolog fog történni azzal a ribanccal..... Még az új játékszeremet is hagyom egy kicsit pihenni. Várj! Van egy jobb ötletem. Kölcsönadom Henri-nek. Egy idôre, persze.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Tényleg? - Igen. Köszönöm, bácsikám!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Elôbb megérdemled - segíts nekem ebben, jó?";
			link.l1 = "Mindjárt elveszti a fejét.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Kapitány úr... Longway részvétét fejezi ki. Mindent megtettünk, amit tudtunk.";
			link.l1 = "Nem mindent, de közel sem eleget.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway meg fogja találni Chang Xinget. Velem tartasz?";
			link.l1 = "Igen, veled megyek, Longway. De ne feledd - a húgodnak is nagyon aktív szerepe volt ebben a véres látványosságban. Nagyon keményen kell majd dolgoznia, hogy meggyôzzön, hogy kíméljem meg. És te nem fogsz neki segíteni. Most pedig gyerünk, itt az ideje, hogy véget vessünk ennek.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			ReturnOfficer_Longway();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, tudtam, hogy így lesz! Tudtam, hogy eljössz! Mindig is tudtad, nem igaz?";
					link.l1 = "Nem akarom negyedszer is próbára tenni, Mary... Azok a gazemberek, ôk...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ó, kapitányom, nem is tudja, milyen jókor jött. Azok... azok a szörnyetegek...";
					link.l1 = "Most már vége, Helen. Minden rendben, mindennek vége. Istenem, mit tettek veled...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, itt vagy! Tudtam, tudtam, tudtam, rendben!";
					link.l1 = "Teljes gôzzel repültem, az életemért futottam, Mary. Te... ôk...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "A kapitányom... Itt vagy... Már majdnem elvesztettem a reményt...";
					link.l1 = "Olyan gyorsan jöttem, ahogy csak tudtam, Helen. Sajnálom, hogy ilyen sokáig tartott.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nem, Charles, nem. Megpróbálták, de én küzdöttem ellenük, ahogy csak tudtam. Ezért vertek meg olyan csúnyán... Kérlek, Charles, menjünk innen... rendben?";
					link.l1 = "Azonnal, kedvesem. Még egy utolsó dolog van hátra.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Nem ôk tették, Charles! Nem ôk tették. A többi begyógyul. Kérlek, vigyél el innen.";
					link.l1 = "Természetesen, kedvesem. Már csak egy dolog van hátra.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Ne, Charles, ne. Megpróbálták, de te még épp idôben ideértél. Mint akkoriban. Hányszor is volt ez?";
					link.l1 = "Nem számoltam, Mary. És soha nem is fogom.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ideértél... épp idôben. A legrosszabb nem történt meg. Most pedig, kérlek, menjünk innen. Bárhová.";
					link.l1 = "Állj talpra, Helen. Menj fel az emeletre. Elôbb ezzel a rohadékkal kell foglalkoznom.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "És nem hagyom abba a számolást. Most pedig hagyjuk el ezt a helyet, kérlek.";
			link.l1 = "Természetesen, kedvesem. Nincs itt semmi keresnivalónk. Kivéve egy dolgot.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Na és, kha-kha, nincs hozzá merszed, takonypóc? Kérd meg a sárga seggû vaddisznódat, hogy segítsen neked...  Vagy csináld meg te magad, és akkor lesz okod elmondani Poincy-nak, hogy milyen bátor vagy.";
				link.l1 = "Inkább elmondanám mindenkinek, hogy milyen gyáva szar alak vagy.";
			}
			else
			{
				dialog.text = "Mi az, tényleg végig akarod nézni, ahogy elvérzek? Élvezed, mi? Majd elmondod a nôdnek, hogy milyen hôs vagy. Látod azt a csontvázat a falon? Santiago bankár felesége... Az ô férje is hôsnek hitte magát, de kiderült, hogy csak egy jó sikoltozó - amikor megpörgettem a keréken...";
				link.l1 = "A tetemedet is guríthatnám rajta, te szemétláda, de attól tartok, nem bírná el a segged súlyát.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Gyáva? Ó, kha-kha, ugyan már...";
				link.l1 = "A kegyetlenség nem a gyávaság ellentéte. De az olyanok, mint te, nem tudják a különbséget.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "Ez nagyon okos. Jegyezd meg a szavaimat, de Maure: úgy fogsz meghalni, mint az a nagyfônök, a saját sikolyaidtól rekedten, és süketülve a...";
				link.l1 = "Égj a pokolban, söpredék!";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Igen, nem vagyok egy nagy filozófus, ezt elismerem. Látja azt a csontvázat a falon, de Maure? Ez minden, ami Santiago bankár feleségébôl megmaradt. Ô is szeretett nagyot mondani, de ez abbamaradt, amikor elkezdtem a testét a kerékre tekerni. Csak a sikoltozás maradt, amitôl majdnem megsüketültem...";
			link.l1 = "Essünk túl rajta.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Várjon egy percet, kapitány úr... Ne siessen ennyire.";
			link.l1 = "Mi a baj, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ne öld meg. Túl egyszerû. Rosszabbat érdemel.";
			link.l1 = "Mérges vagy a húgod miatt, barátom. Én pedig dühös vagyok amiatt, amit a " + sStr + "... és amit vele tehetett volna. De én nem vagyok olyan állat, mint ô. Megégethetném a parazsat a parázzsal, eltörhetném a csontjait a kerékkel... Megbilincselhetném, és hagynám, hogy belehaljon a vérveszteségbe. De nem kockáztathatom, hogy az egyik csatlósa megmentse. Nem vállalhatom ezt a kockázatot.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Várj, kapitány úr. Nem így értettem. Poincy-ról beszélek.";
			link.l1 = "Mi van vele?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Gondolj arra, hogyan jutalmazna meg, ha élve hoznád el neki ezt az állatot. Dublonnal halmozna el. És az a söpredék inkább itt halna meg, minthogy egy capsterville-i börtönben rohadjon meg.";
			link.l1 = "Lehet, hogy igazad van, Longway. De nem tudom, mi történt pontosan ez a szemétláda és a lovag között. Higgye el, én jobban ismerem ezt a tömeget, mint maga. Ha minden a pénzrôl szól, ahogy mondják, akkor ôk ketten alkut köthetnek. Poincy elengedhetné, és egy másik ilyen szoba felbukkanhatna egy másik szigeten vagy az Óvilág valamelyik városában.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Nem rossz ötlet, Longway. Bár kétlem, hogy a Chevalier ilyen nagylelkû lenne... Ez nem igazán a természete. De nekem amúgy sem a pénzrôl van szó. Húzzátok fel! És kötözzétek be a sebeit, hogy ne haljon meg idô elôtt.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "De elôbb érted megyek. És a társadért. Nem nyúlok hozzád, szûklátókörû ember - nem éred meg az idômet.";
			link.l1 = "Látod, Longway? Ennek az egésznek véget kell vetni. Itt és most.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Várjon egy percet, kapitány, várjon egy percet, kha-kha.";
			link.l1 = "Mi az, Monsieur ex-kormányzó?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "A kulcsom valahol ebben a szobában van. Egy ládát nyit az irodámban. Kétszázezer ezüst van benne és egy finom penge. Ha ez nem lenne elég, a feleségem hálószobájában, a fiókos szekrényben van egy gyûjtemény drága drágakövekbôl.";
			link.l1 = "Hmm, és mit akar cserébe?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Egy golyót. Végezz velem. Itt és most.";
			link.l1 = "Mi van a Chevalier de Poincyval? Úgy hallottam, régi barátok vagytok... Nem akarja látni ôt?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "A pokolba Poincy-val! Szóval, egyetértesz vagy sem?";
			link.l1 = "Nem igazán, Monsieur de... Nem akarom felsorolni a teljes nevét.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Ez nem elég önnek? Rendben, van még más is...";
			link.l1 = "Az áldozatai sikolyaitól megsüketülhetett, Levasseur. Mondtam, hogy nem a pénzrôl van szó. Okkal fél Poincy-tól, Ed? Nem is akarom tudni, mit fog tenni magával. De ha ez egy kis megtorlásként szolgál a... mûvészetéért, hát legyen.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Szóval ez vagy te valójában, kha-kha... Nem jobb nálam.";
			link.l1 = "Elég volt. Longway - állítsd fel!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) ReturnOfficer_Longway();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "A hajónk... Soha nem gondoltam volna, hogy ennyire örülni fogok neki... rendben. Végre vége ennek a rémálomnak.";
				}
				else
				{
					dialog.text = "Végre vége. Most hova, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Nem tudom elhinni, hogy vége van... Most mit tegyünk, kapitányom?";
				}
				else
				{
					dialog.text = "Nos, ez az, kapitányom. Most mit tegyünk?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Sajnos, még nincs vége. Chang Xing... Ez a történet csak akkor ér véget igazán, ha megkapom tôle a válaszokat.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Irány Capsterville. Itt az ideje, hogy Monsieur Levasseur a történelem részévé váljon.";
				}
				else
				{
					link.l1 = "A Chevalier küldetése teljesítve. Jelentenem kell neki. Néhány részletet azonban kihagyok belôle. Csak remélem, hogy megtartja a szavát, és Michel kiszabadul...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Én is, rendben. Szóval veled megyek. És meg se próbálj vitatkozni velem, Charles.";
				link.l1 = "Mary, kedvesem, pihenned kell. Ilyen közel vagy az ájuláshoz...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Veled megyek.";
				link.l1 = "Helen, majdnem meghaltál annak az ördögnek a keze által. Alig tudsz megállni a lábadon...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Szükségem van rád, Charles. És neked is szükséged van rám. És ha valaki ma este el fog ájulni, az Chang Xing. A bordélyháza padlóján, egy golyóval a szemei között!";
				link.l1 = "Igen, Levasseur nem verte ki belôled a harci szellemet. Visszaküldenélek a hajóra, de tudom, hogy úgyis követnél...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "De a pengét még mindig tudom tartani. Charles, ott kell lennem. Meg kell értenem, mi késztette erre. Érted, miért olyan fontos ez nekem?";
				link.l1 = "Megértem, hogy pihenésre és gyógyulásra van szükséged. Méghozzá hosszú idôre.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Túl jól ismersz engem, Charles, rendben. Szóval hagyjuk a fecsegést és fejezzük be ezt.";
				link.l1 = "Ahogy akarod. De maradj éber. Senki sem tudja, milyen meglepetések várnak ránk odakint.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ez várhat. Értem jöttél, és most én is veled megyek. Akár akarod, akár nem.";
				link.l1 = "Látom, hogy még mindig megvan a bátorságod, Helen. Jó. Jó. Maradj mögöttem, és az Isten szerelmére, légy óvatos.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "A hajónk... Nem hiszem el, hogy újra a fedélzetre kell szállnom...";
					link.l1 = "Vár rád, Mary. Egy kiadós vacsora és egy puha ágy...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Nem hittem, hogy a saját lábamon eljutok a hajóig.";
					link.l1 = "Te vagy a legkitartóbb ember, akit valaha ismertem, Helen. Most pedig befelé, aztán irány az ágy...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "A hajónk... Nem hiszem el, hogy újra a fedélzetre kell szállnom...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Nem hittem, hogy a saját lábamon eljutok a hajóig.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Irány Capsterville. Itt az ideje, hogy Monsieur Levasseur a történelem részévé váljon.";
				}
				else
				{
					link.l1 = "A Chevalier küldetése teljesítve. Jelentenem kell neki. Néhány részletet azonban kihagyok belôle. Csak remélem, hogy megtartja a szavát, és Michel kiszabadul...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "És te, Charles... Miért nézel így? Már megint készülsz valamire, ugye?";
				link.l1 = "Chang Xing. Nekem is el kell jutnom hozzá.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "És te? Hová mész?";
				link.l1 = "Chang Xinghez. Ô az utolsó fejezet ebben a rémálomban.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Akkor én is veled megyek! Tartozik nekem egy csomó mindennel, rendben?!";
				link.l1 = "Mary, drágám, alig értél a hajóra. És most még egy pengét sem tudsz tartani. Megfizet azért, amit veled tett, Istenre esküszöm. De sokkal jobban érzem magam, ha a hajón maradsz, mert biztonságban vagy.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kapitányom, annyira szeretnék veled menni... Kérem, legyen óvatos. Ki tudja, mire képes még? Ô tartott le, amíg az a kölyök Thibaut...";
				link.l1 = "A legrosszabbnak vége, Helen. Hamarosan vége lesz, ígérem.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Nos, legalább Longway fedezni fog téged a távollétemben. De ha bármi történik veled, ôt és Chang Xinget én magam teszem a földbe!";
					link.l1 = "Minden rendben lesz. Most menj és pihenj. Visszajövök, mielôtt észrevennéd.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Hová tûnt Longway, Charles?";
					link.l1 = "Nélkülem ment Chang Xing után. Nem tudtam megállítani, de mit tehettem volna?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Nos, legalább Longway veled jön. Legalább ez megnyugtat.";
					link.l1 = "Látod? Nem kell aggódnod. Nem maradok sokáig.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Hol van Longway? Most vettem észre, hogy nincs itt.";
					link.l1 = "Elment a nôvéréhez nélkülem. Nem hibáztatom érte. Túl régóta várt erre a pillanatra.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, rossz érzésem van ezzel kapcsolatban...";
				link.l1 = "Tudom, tudom. Ez a rémálom már túl régóta tart, és közel a vége. A legrosszabbnak vége.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ki tudja, mi jár a fejében, Charles? Tartsd nyitva a szemed, rendben?";
				link.l1 = "Tartsd nyitva a szemed, oké? Hamarosan visszajövök, Helen."
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Ígérd meg, hogy mindenre készen állsz.";
			link.l1 = "Visszajövök, és vissza is fogok. Hamarosan visszajövök, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Régóta segítettem, kapitány. Most már a maga szavát kell megtartania.";
			link.l1 = "Mindent hallottál, Longway. Menjünk a húgodhoz.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Kapitány úr, Longwaynek van egy utolsó kérése: hagyja, hogy Chang Xing megmagyarázza magát. Hallgassa meg, mielôtt döntést hoz.";
			link.l1 = "Ami a " + sStr + " történt, az az ô hibája. De elôbb adok neki egy esélyt, hogy megmagyarázza.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway bízik a szavadban, az ítélôképességedben és a kedvességedben.";
			link.l1 = "Haver, ebben a véres zûrzavarban nincs helye az észnek vagy a kedvességnek. És itt az ideje, hogy véget vessünk neki.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mária";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Kapitány úr...";
				link.l1 = + sStr + " meghalt.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Kapitány, hölgyem " + sStr + ", örülök, hogy látom. Ez itt... Chang Xing.";
					link.l1 = "Kitaláltam, Longway. Álljatok hátrébb. Rengeteg idôd volt beszélni a húgoddal. Most felelnie kell a " + sStr + " , amiért segített Levasseur kegyenceinek elrabolni ôt.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Eljöttél... Hol van a hölgy " + sStr + "? Ô...?";
					link.l1 = "Nem, Longway. Hála Istennek, nem. Elvittem a hajóra. Különben most nem beszélgetnénk. Azonban ez még mindig nem lesz könnyû vagy kellemes.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing és én részvétünket fejezzük ki...";
			link.l1 = "Részvétem Chang Xing?! Te is részvétet nyilváníthatnál Levasseur nevében, Longway! Nagyon jól tudod, hogy részt vett a " + sStr + " elrablásában a többi kegyencével együtt! És most már nincs többé...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Megértem, hogy mit érez most, kapitány úr.";
			link.l1 = "Ó, tényleg?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Elvesztettem a szüleimet, mint emlékszel. Ha emlékszel. Különben is, nem Chang Xing volt az, aki megkínozta és megölte " + sStr + ". Megértem a fájdalmadat, a dühödet. De a nôvérem bûntudatát nem kell annyira figyelembe venned, mint a tiédet. Kérem, hallgasson meg.";
			link.l1 = "Emlékszem. Meghallgatom a történeted. De gyorsan! És tudd, hogy nem hagyhatok ilyesmit büntetlenül!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Akkor jobb, ha mindent újra elmondok, Monsieur de Maure. A mi Tu-nk olyan rosszul beszél franciául, hogy majdnem megtámadta.";
			link.l1 = "Be kellett volna fognia a száját. Nem akartam megtámadni Longwayt, de maga... Maga a felelôs a haláláért.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Vitatkoznék ezzel, de rájöttem, hogy inkább nem. Tu úgy beszélt rólad, mint egy tisztelettudó és megértô emberrôl. De ez tényleg így van? Van értelme egyáltalán elkezdenem beszélgetni? Vagy már döntöttél?";
			link.l1 = "Maga tudja, hogyan kell valakinek a fejébe hatolni, kisasszony. Most már tényleg nem érdemes vitatkozni. De ha meg akarja próbálni magát igazolni... Nos, csak rajta. Longway kedvéért, meghallgatlak.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ô mindent meg tud magyarázni, kapitány úr... Nem az, amire gondol... Nem igazán...";
			link.l1 = "Akkor magyarázza meg. De ne nekem. " + sStr + ". Nézz a szemébe. Nézd meg a zúzódásait és a sebeit. És mondd meg neki, hogy nem így történt.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Elnézést kérek Xing nevében, kapitány...";
			link.l1 = "A vigyorgó arcából ítélve, hiába teszed. Nem érdemli meg a bocsánatkérésedet.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Túl keményen bánik vele, Monsieur de Maure. Bár valószínûleg megszokta, hogy így bánik vele - mint egy tipikus sárga bôrû munkással.";
			link.l1 = "Megpróbálja ellenem fordítani Longwayt? Nem fog sikerülni. Mindig tisztelettel bántam vele, és ezt ô is tudja. Csak ez számít. Tudom, hogy most már csak a játszadozás maradt neked.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mit akarsz tenni? Elvenni szegény Tu-t a családjától? Amikor tíz év után végre újra rájuk talált?";
			link.l1 = "Nem mindig a vér teszi a családot. De mit javasolsz, mit tegyünk? Hagyjuk büntetlenül, amit a " + sStr + " tettél? És hogy Longway idônként meglátogasson egy olyan nôt, aki gondolkodás nélkül más lányokkal kereskedik?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Nos, elôször is, figyelj. Vele ellentétben én tökéletesen el tudom mondani franciául, amit az elôbb mondtam neki. Az én történetemet. Egyenesen a szemébe nézek, vagy akár az övébe. És mindezt anélkül az akcentus nélkül, amit már valószínûleg halálra unsz. Végül is, mit veszíthetünk?";
			link.l1 = "Megszoktam Longway akcentusát; ez része annak, aki számomra ô. Meghallgatlak, de csak a barátom kedvéért. Folytassa.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Miért ne, kapitány úr...?";
			link.l1 = "Tényleg meg kell kérdeznie? Részt vett a " + sStr + "elrablásában, nem igaz?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Én... ôszintén elnézést kérek. Az én hibám is, hogy nem tudtam megmenteni a húgomat tíz évvel ezelôtt, hogy megóvjam ettôl az egésztôl.";
			link.l1 = "Nem kellene bocsánatot kérned azokért, akiknek a legcsekélyebb lelkiismeret-furdalásuk sincs, Longway. Végeztél itt? Most rajtam a sor, hogy beszéljek vele.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Kapitány úr, várjon! Chang Xing nem olyan, mint Levasseur. Nem teljesen. Mesélni fog nekem az életérôl az elmúlt tíz évben. Hadd meséljek én is.";
			link.l1 = "Rendben, Longway. Hallgatom. Sok múlik azon, hogy mit mondasz el nekem.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Ha te mondod el, mindannyiunknak megfájdul a feje. Engedd meg, Tu. Charles de Maure, gondolom?";
			link.l1 = "Igen, uram. És te vagy Belle Etoile, más néven Chang Xing. Te is részt vettél a szerelmem elrablásában, Thibaut-val és Martene-vel együtt. És mosolyogsz, amikor megemlítem. Boldog emlékek?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "Hülyeség lenne tagadni. De mi van most? Meg akarsz kínozni a bátyám elôtt? Vagy megkéred, hogy segítsen neked megkínozni engem? Vagy egyszerûen csak megölsz? Tényleg ezt tennéd vele?";
			link.l1 = "Mint mondtam, mindannak ellenére, amit most szeretnék tenni, még mindig beszélek veled. Ne erôltesd. Mondd el, mit mondtál neki korábban. És aztán meglátjuk, hogy mi lesz ebbôl.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Még mindig nem tudom elhinni, hogy Chang Xingbôl ilyen lett... ez.";
				link.l1 = "Az emberek változnak, Longway. Bárki megtört lehet, vagy a kedvesség és a hit utolsó cseppjeit is ki lehet marni belôle.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway még mindig nem tudja elhinni, hogy a húgomból ez lett... ez... Miért... miért? Bárcsak otthon lettem volna aznap...";
				link.l1 = "Ne ostorozd magad a mi lett volna, ha miatt. Különben is, nem ültél tétlenül azokban az években - olyan átkozottul keményen próbáltad helyrehozni a dolgokat.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh... Azt hiszem, ez már csak így van, kapitány úr.";
			link.l1 = "Menjünk innen. Még mindig fel kell takarítanunk a mocskot, amit hátrahagyott, és meg kell mentenünk a " + sStr + " , amilyen hamar csak lehet.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Igen, uram. Sietnünk kell - már így is túl sokat késett miattam.";
			link.l1 = "Nem a te hibád, Longway. Siessünk!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Rendben. Köszönöm a támogatását, kapitány úr.";
			link.l1 = "Szóra sem érdemes. Amúgy sem érdemelte meg az odaadásodat - nem ô volt az, aki megkeresett téged, még akkor sem, ha megtehette volna. A csillagod már rég kialudt, és ô már régen nem a családod. Most már mi vagyunk a családod, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Aye... Így van. És én túl vak voltam, hogy ezt észrevegyem.";
			link.l1 = "Jobb késôn, mint soha. Most menjünk haza - a hajónk vár ránk.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "Rendben. Fogalmad sincs, mennyire akartam ezt.";
			link.l1 = "Azt hiszem, most már látom. Hogy érzed magad, Mary? Azért akartam elkerülni a vérontást, mert nem voltam biztos benne, hogy olyan szilárdan tudod-e tartani a pengédet, mint mindig - az egyikük fölénybe kerülhetett volna, amíg én a másikkal vagyok elfoglalva.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Alábecsülsz engem. Különben is, a harag pokolian jó gyógyszer. Nem volt kétségem afelôl, hogy a megmentésemre sietsz - ahogy mindig is szoktál, rendben. Tudod, Charles... Még ha a Vörös Talizmánodnak is hívsz, mi van, ha te is az enyém vagy? Valami csodálatos mindig történik, amikor együtt vagyunk.";
			link.l1 = "Én vagyok a te talizmánod? Miért, tetszik az ötlet.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "Tessék, máris mosolyogsz! Most pedig tûnjünk el errôl az undorító helyrôl - siessünk, hipp-hopp, rendben.";
			link.l1 = "Eh-heh, ez a zûrzavar nagyon megütött. Bárcsak másképp végzôdhetett volna.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "Én nem. Nem lehetett megmenteni ôt, Charles. És magával rántotta Longwayt is. Meghozta a döntését, és nem hagyott nekünk más választást. Gondolj azokra az emberekre, akiknek ma segítettünk.";
			link.l1 = "Még egyszer mondom, nincs semmi, amivel ellentmondhatnék neked, Mary. És ezúttal nem is akarok. Gyere, Vörös Talizmánom...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "Mi történt ott, uram? Káromkodást és kiabálást hallottunk. De nem mertünk segítséget hívni, amíg nem volt vége.";
				link.l1 = "És jogosan. A háziasszonya halott. Szabadon távozhatnak. Én a helyetekben összeszedném a létesítmény kincstárát, felosztanám, és elmenekülnék a szigetrôl, amilyen gyorsan csak lehet. Tudom, hogy maguk becsületes hölgyek, nem egyszerû prostituáltak, így lesz jövôjük ezen a nyomorult helyen túl is.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Ó, maga az, uram. Tudja, mikor jön le a háziasszony?";
				link.l1 = "Nemsokára. És az ön helyében én inkább elállnék az ajtótól. És soha ne beszéljen vele errôl az estérôl - nem fog semmit sem megosztani, és a kíváncsi macskák egyszeriben elveszítik az életüket. Úgy tûnik, a madamod nem szereti, ha bárki is belepiszkál a titkaiba.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Megölted ôt?!";
			link.l1 = "Megöltem. És ha idôzöl, vagy megpróbálod rám hívni az ôröket, az lenne a legnagyobb hibád. Ô sosem volt a védôszentetek - akármennyi selymet és oktatást is adott nektek, itt voltatok bebörtönözve, arra kényszerítve, hogy bármelyik csôcseléknek, akire ô mutatott, odaadjátok magatokat. Sok szerencsét kívánok nektek, hogy kijussatok innen. Viszlát, hölgyeim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Tényleg jól van? Bemehetünk? Hívnunk kell az ôröket?";
			link.l1 = "Soha nem lesz jól. Megpróbálhatjátok megkérdezni tôle... saját felelôsségre. Még mindig a bátyjával beszélget. És nem hiszem, hogy örülnének, ha megzavarnánk ôket.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Értem... Nos, látogasson meg minket valamikor újra, uram.";
			link.l1 = "Soha többé. Viszlát, hölgyeim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Állj! Etoile kisasszony lakásából kiabálást és verekedést jelentettek. Az ôr szerint önnek köze van hozzá. Adják le a fegyvereiket és kövessenek minket, uram.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "Igaz, de nem mi kezdtük a veszekedést, hanem mi fejeztük be. A felbérelt gengszterek fellázadtak a késedelmes fizetés miatt, és megtámadták Madame Etoile-t, hogy kirabolják. Bízik a zsoldosokban, mi? Megnyertük a napot, de sajnos ô nem élte túl.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "Ma elvesztettem életem szerelmét, úgyhogy engedjen át, biztos úr.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Ugye tudja, hogy nem hihetünk magának? Le kell tartóztatnunk. És tanúkra lesz szükségük a nôi alkalmazottak közül. Lássuk, mit mondanak.";
			link.l1 = "A szerettem súlyosan megsérült. Én is hullafáradt vagyok. Nem tudna minket elengedni, kérem?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Megpróbáljuk ezt minél hamarabb megoldani. Most pedig kövessenek minket.";
			link.l1 = "Menjetek a pokolba...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Részvétem, uram. És én még nem vagyok tiszt, de... mindegy, mindegy. Velünk jönne, és elmondaná, mi történt ott?";
			link.l1 = "Megmondom én neked. A bordélyház veszteséges volt, és nem maradt pénz az ôrzô zsoldosok fizetésére. Úgy döntöttek, hogy elviszik, ami megmaradt, pont akkor, amikor én is ott voltam. Madame Etoile-lal harcoltunk ellenük, de ô belehalt a sebeibe. Most pedig hadd menjek el végre.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Szeretnék, de rengeteg papírmunkát kell kitöltenem. És ki kell kérdeznem az ott dolgozó hölgyeket. Attól tartok, legalább egy napig a városban kell maradnia, még akkor is, ha igazat mond, monsieur.";
			link.l1 = "Menjetek a pokolba...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway-nek van valamije az ön számára, kapitány úr.";
			link.l1 = "Milyen gyönyörû és szeszélyes. Még sosem láttam ehhez foghatót. Mi ez?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "Ez az én hazám kapitányának amulettje. És mivel Longway már nem kapitány, neked adom.";
			link.l1 = "Köszönöm, Longway. Van der Vink halálával bosszút állt mindenkin, akin csak akart. Örülök, hogy így alakult.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Bárcsak meg tudnám gyôzni Xinget, hogy újra jó ember legyen...";
			link.l1 = "Senkire sem akarna többé hallgatni, még a bátyjára sem. Megtettél minden tôled telhetôt. Mindannyian megtettük.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Igen... Nagyon köszönöm, kapitány úr. Hosszú út vezetett a szabadsághoz, és ahhoz, hogy újra legyen otthona és barátai.";
			link.l1 = "Szívesen, barátom. Most pedig, miért nem jössz velem meglátogatni a bátyámat? Ó, micsoda irónia!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			ReturnOfficer_Longway();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Megint itt vagyunk, François. Látom, az élet megviselte magát, hehe.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, te mohó szemétláda... Majdnem megfulladtál az aranytól, amivel tele van a pénztárcád, és még mindig nem tudsz betelni?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Megosztom veled, François. Elég lesz, hidd el.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "Hogy... hogy érted ezt?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Fôkormányzó úr, maga most...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, barátom, elvégezted a munkádat, és remekül csináltad! Ami ezzel az emberrel történni fog, az nem tartozik rád... Azonban hasznos lesz, ha tudod, kapitány, arra az esetre, ha a te okos fejednek egyszer csak hülye ötletei támadnának. Egy rossz emésztési zavar vár közös barátunkra, hogy úgy mondjam. Az arany nem tesz jót a gyomornak, úgy hallottam... Remélem, nem kell tovább magyarázkodnom.";
			link.l1 = "Nem, fôkormányzó úr.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "Monsieur François-val ellentétben, neked nagy jövô áll elôtted, Charles. Fiúk, vigyétek azt a disznót a börtönbe!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "El a kezekkel, ti picsák! Elégedett vagy, de Maure?! Baszd meg! Mindketten a pokolban fogtok égni, egy serpenyôben velem!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Nos, uram. Megvizsgáltam Miss " + sStr + "...";
			link.l1 = "Mennyire rossz a helyzet, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Nincs miért aggódnia, kapitány. Mary persze súlyosan megsérült, de összességében minden rendben lesz. Néhány napig ágyban kell maradnia, és két hét múlva újra bevethetô lesz.";
					link.l1 = "Értem. Köszönöm, Raymond. Leléphet.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary-t eléggé megverték, kapitány. Zúzódások, vágások... és persze a sokk, bár igyekszik nem mutatni.";
					link.l1 = "Kemény arcot vág, mint mindig. De azt hiszem, rájött, hogy most már jobb, ha ágynyugalomban van. De meddig?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Még egy hivatásos katona is nehezen élné túl azt, amin ô keresztülment, kapitány. Rándulások, húzódások, zúzódások - szerencsénk van, hogy azok a szemetek nem törték el a csontjait. Az inai azonban megsérültek, így legalább egy hónapig nem fog tudni pengét forgatni.";
					link.l1 = "A pokolba a pengével. Mikor fog tudni lábra állni?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Ne aggódjon, kapitány. Hellen megsérült, de nem súlyosan. Egyelôre ágyban kell maradnia, de szerintem néhány héten belül teljesen felépül.";
					link.l1 = "Értem. Köszönöm, Raymond. Leléphet.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Eléggé megverték, kapitány. És a fizikai sérülések csak egy része a diagnózisnak... Az, hogy azon a szörnyû helyen volt, az Arbutuson átélt rémálmára emlékeztette.";
					link.l1 = "Persze... a fenébe is! Mikor fog újra talpra állni?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen borotvaélen járt, kapitány. Meglep, hogy túlélte mindazok után, amin keresztülment. Belsô sérülése vagy törése nincs, de rengeteg rándulás és húzódás igen.";
					link.l1 = "Szegénykém. Mennyi ideig tart a felépülése?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Legalább egy hétig, uram. Ha követi a javaslataimat, egy hónap múlva újra harcképes lesz.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Két hét múlva, uram. Utána rövid sétákat engedélyezek neki a fedélzeten. A teljes felépülés legalább két hónapot vesz igénybe.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Legalább egy hétig ne zavarja, ezt megmondom, uram. A teljes felépülés körülbelül egy hónapig tart.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Két hétig ágyban kell maradnia, utána már sétálhat a fedélzeten. De legalább két hónapig ne számítson arra, hogy újra akcióban láthatja.";
				}
			}
			link.l1 = "Értem. Köszönöm, Raymond. Leléphet.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Nehezebb, mint gondoltam volna, hogy ilyen hosszú fekvés után magamra álljak, rendben!";
				link.l1 = "Talán nem kéne ilyen hirtelen abbahagynod az ágynyugalmat, drágám.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ó, a fejem...";
				link.l1 = "Helen! Nem keltél fel egy kicsit korán? Alig tudsz állni!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Inkább felgyújtom ezt az átkozott ágyat, minthogy még egyszer lefeküdjek bele - legalábbis addig, amíg nem sétáltam az orrtól a tatig és vissza!";
				link.l1 = "Ez egy szép, kényelmes ágy. És nem is rossz hajó. Úgyhogy nem fogom megállítani. De ott leszek, hogy biztos legyek benne, hogy nem csinálsz semmi ostobaságot.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Jól vagyok, kapitány, bár nem teljesen. Még nem állok készen arra, hogy pengét lendítsek, de teljes lelkemmel gyûlölöm ezt az ágyat.";
				link.l1 = "Nos, egy rövid séta a fedélzeten valószínûleg nem fog ártani. De eszébe se jusson a kábelek közelébe menni!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, nem gondolod, hogy elfelejtettél engem? Emlékeztess, mikor feküdtünk utoljára együtt, rendben!";
				link.l1 = "Mielôtt... Ne beszéljünk errôl, rendben, Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kapitányom, már nem érdeklem magát, mint nô?";
				link.l1 = "Ez váratlanul ért, Helen. Általában én szoktam ezt felhozni, de nem voltam biztos benne, hogy készen állsz...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Akkor legalább beszélj rólam, rendben. Vagy kellemetlenné váltam számodra, miután az a két szemétláda megvert?";
				link.l1 = "Ez a leghülyébb dolog, amit valaha hallottam. Csak nem akartalak zavarni, amíg nem állsz készen. És ha már így alakult...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Semmi baj, Charles, tényleg. Csak próbálok nem gondolni rá. És különben is, megmentettél a legrosszabbtól. Szóval hagyjuk abba a beszélgetést, és csak... beszélgessünk.";
				link.l1 = "Ez egy átkozottul jó ötlet, Helen.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, én nem akarom, hanem követelem, rendben!";
				link.l1 = "Nem merném visszautasítani...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, beszélnünk kell, rendben.";
				link.l1 = "Valami baj van, Mary? Eléggé nyugtalannak tûnsz, és ez általában nem jelent jót.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kapitányom, valamit el kell mondanom.";
				link.l1 = "Valóban, Helen? Hallgatlak.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ez az! Hát nem jó, hogy készen állok visszatérni a tiszti kötelességeimhez?";
				link.l1 = "Szóval ez az. Nos, ha elég erôsnek érzi magát, az nem csak jó, hanem csodálatos.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Elegem van abból, hogy a legénység úgy bámul rám, mint valami gyenge öregasszonyra. Vissza akarok menni a kormányhoz és kinyújtóztatni a karjaimat azzal, hogy gyakorolok a pengével...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Ha úgy érzed, hogy van kedved hozzá, nem fogok ellenkezni, kedvesem. Hozom a felszerelésed. És örömmel engedem, hogy átvegye a kormányt. De légy óvatos a harcban, rendben?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Hiányoztál a hídon, Helen. Ami a pengét illeti, azt hiszem, itt az ideje, hogy visszakapd.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Természetesen, kapitányom, ahogy akarja.";
			link.l1 = "Jó.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Csodálatos, rendben! Alig várom, hogy gyakorolhassak a pengével...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Örömmel hallom, Mary. De még ne ugorj bele a dolgok sûrûjébe... De kinek mondjam el?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Gondolom, örülni fogsz, hogy a pálcád újra a hüvelyében van...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "I... Nem tudom, mit mondjak, Charles. Csak most jöttem rá, milyen sokat jelent nekem ez a kard...";
				link.l1 = "Ezt már régóta tudom, ezért is várt rád épségben és sértetlenül.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Adta a Lángoló kardot", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Az én narválom, rendben!!! Charles, megmentetted! Nem csak boldog vagyok, hanem izgatott! Köszönöm, köszönöm! Annyira féltem, hogy Martin hajóján maradt...";
				link.l1 = "Ez a penge a te kezedbe való, Vörös Talizmánom. Bízom benne, hogy nem veszíted el újra... Nos, nem állok a találkozásotok útjába, ha-ha!";
				notification("Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Köszönöm, Charles. Tudod, valószínûleg ezért szeretlek téged...";
				link.l1 = "Azért, mert visszahozod az elveszett dolgokat? Ha ha ha ha ha ha...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Te nevetsz, de én komolyan beszélek.";
			link.l1 = "Tudom, Helen. Én is szeretlek, bár még mindig nem tudom, miért.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Talán azért, mert még nem használtam rajtad ezt a bicskát.";
			link.l1 = "Megkímélem magam ettôl, ha a hajók felé veszem az irányt. Ott megvárlak, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 