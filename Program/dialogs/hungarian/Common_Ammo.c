// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Figyelj, fontos dolgom van veled. Remélem, tudna segíteni.","Kapitány, érdekelhetem egy igen jövedelmezô ajánlattal?"), RandPhraseSimple("Úgy gondolom, hogy egy fontos ügyben tudna segíteni nekünk.","Kapitány, van egy kényes ajánlatom az Ön számára, amely mindkettônk számára igen jövedelmezô lehet."));					
				link.l1 = "Nos, mondja el a véleményét, és meglátjuk...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("Én vagyok az erôd parancsnoka. Mire van itt szüksége?", "Mire van szüksége? Miért jöttél ide?");
			link.l1 = "Ó, semmi, csak körülnézek a városban és a környéken. Csak egy szerencsés véletlen folytán kerültem ide.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Üdvözlöm az erôdben, kapitány. Szüksége van valamire?";
				link.l1 = "Nem, semmi, csak véletlenül ugrottam be.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Üdvözlöm, admirális-helyettes! Van valami parancsa?";
				link.l1 = "Nem, tiszt úr, nincs parancs. Csak az erôdöt jöttem megnézni.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Fôkormányzó úr, kegyelmes uram! Teljes a rend az erôdben. Lesz valami parancs?";
				link.l1 = "Örülök, hogy jól van, tiszt úr. Nincs parancs, csak beugrottam megnézni az erôdöt.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "Van egy érdekes információm az ön számára, biztos úr. Az egyik katonája, "+pchar.questTemp.Wine.SName+" megkért, hogy az én közvetítésemmel vásároljon bort a városban. Figyelembe véve a parancsát...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Üdvözlöm, tiszt úr. A Basse-Terre kolóniáról jövök, egy Gerard LeCroix nevû férfi parancsára. A rakományomban puskapor és bombák vannak az ön számára...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "Aggódónak tûnik, tiszt úr. Miben segíthetek?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "Készen állok jelenteni, hogy az egész rakomány puskaport leszállították. A hajóm készen áll a kirakodásra.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "Vissza akarom utasítani a lôporüzletünket. Ez túlságosan zavaró.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Látod, az erôd ágyúi eléggé elhasználódtak. A kincstár pénzt utalt ki a cseréjükre, de egyszerûen fogalmam sincs, hol vehetnék újakat: egyszerûen nem találok a kolóniánkon a szükséges mennyiségben. Úgy gondoltam tehát, hogy az önök által megszállt hajókról származó ágyúk igen hasznosak lehetnek számunkra itt.","Ki kell cserélnem az erôd ágyútöltényeit. A pénzt már kiutaltuk, de tudod... Egyszerûen lehetetlen megvenni a szükséges mennyiséget a mi kolóniánkon.","Az elhasználódott erôd ágyúinak pótlásával bíztak meg, de úgy tûnik, sehol sem találok eleget.");
			Link.l1 = "Hmm... Tudna egy kicsit részletesebben beszélni? Kaliber, mennyiség, ár?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "Szükségem van "+ pchar.questTemp.PrisonGun.Text +", pontosan " + sti(pchar.questTemp.PrisonGun.Qty) + "  egységnyi mennyiségre. Aranydublonokban fizetek, "+ sti(pchar.questTemp.PrisonGun.Price) +" darabonként. Ez összesen " + FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum)) + " lesz. Mit fogsz mondani? Ja, és még valami - a teljes tételt átveszem, de legkorábban egy hónap múlva - a pénz még nem érkezett meg.";
			Link.l1 = RandPhraseSimple("Nem, biztos úr, az ajánlata egyáltalán nem érdekelt... Sajnálom.","Csábító, de azt hiszem, kiszállok. Engedje meg, hogy az érvelésemet megtartjam magamnak.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Nos, ez az ajánlat kétségtelenül érdekes. Tekintsük üzletnek.","Azt hiszem, elfogadom. Nem olyan nehéz és egyértelmûen jövedelmezô.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "Milyen kár, kapitány, számítottam magára. És... Remélem, hogy ez a beszélgetés az erôdön belül marad?";
			Link.l1 = "Erre nem kell emlékeztetnie. Üdvözlettel.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Nos, akkor megegyeztünk! Nem korlátozlak bizonyos feltételekhez, de kérlek, próbáld meg nem elhúzni fél évnél tovább. És remélem, megérti, hogy ez szigorúan bizalmas?";
			Link.l1 = "Természetesen. Viszlát, parancsnok.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Mondtam, hogy egy hónapnál hamarabb ne jöjjön!";
				Link.l1 = "A francba! Annyira elfoglalt voltam"+ GetSexPhrase("","") +", hogy elvesztettem a"+ GetSexPhrase("","") +" idôérzékemet ... Bocsánat, majd késôbb jövök, ahogy megbeszéltük.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... Tudod, több mint fél év telt el azóta a nap óta, hogy megkötöttük az 'üzletünket'. Már megvettem az ágyúkat. Komolyan azt hitted, hogy örökké várni fogok rád?";
				Link.l1 = "A francba! És most mit csináljak velük?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Igen, készen állsz segíteni nekem?";
				if (amount < 0)
				{
					Link.l1 = "Nem, még folyamatban van. Csak meg akartam gyôzôdni róla, hogy az egyezségünk még mindig áll.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Én vagyok. Az egész tétel a raktárban van - "+ sTemp +" egység, ahogyan azt megbeszéltük.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "Nem látom a hajóját a kikötôben. Azt javaslod, hogy az ágyúkat a dzsungelen keresztül vonszoljuk? Siess a kikötônkbe és gyere vissza.";
				link.l1 = "A hajóm a sziget másik oldalán van. Elviszem a kikötôbe.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("Tudod, ez nagyon kínos, de fel kell mondanom a megállapodásunkat. Most volt egy pénzügyi ellenôrzésünk, és tudod, milyen lelkiismeretesek az ilyen dolgokban. Nem tehetek semmit. Sajnálom.","Kapitány, tudja... Hát, ágyúkat küldtek nekünk a metropoliszból, és persze kénytelen voltam kivásárolni ôket. Meglehetôsen magas áron, de... Nagyon sajnálom, hogy cserben hagytam... Én sem érzem jól magam emiatt.");
				Link.l1 = "A francba! És most mit csináljak velük?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Kiváló. Küldök egy osztagot a helyôrségbôl, hogy kirakodják ôket.","Excellent. A katonáim segítenek majd kipakolni az ágyúkat.");
				Link.l1 = "Elôkészítette a fizetséget?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "Nem tudom. Eladjuk ôket a hajógyárban, felszerelünk egy kereskedelmi hajót, elsüllyesztjük ôket... Tényleg fogalmam sincs. És kérlek, ne szólj senkinek errôl az üzletrôl.";
			Link.l1 = "Ó, te mondod! Csak nincsenek szavaim!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "Fogalmam sincs. Ez a te problémád. Adja el, dobja ki, süllyessze el - engem nem érdekel.";
			Link.l1 = "Ó, ez csak idôpocsékolás volt...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Hát persze. Itt van az aranyad - ahogy akarod.";
			Link.l1 = "Köszönöm! Öröm volt önnel üzletelni!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("Megkaptad "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "Az érzés kölcsönös. Nagyon segítôkész voltál. És könyörgöm, tartsa az üzletet ebben a szobában.";
			Link.l1 = "Persze, persze. Minden jót kívánok.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "Micsoda?! Szigorúan megtiltottam az ivást az erôd területén! Nos, ezért meg kell fizetnie. Levonok 1000 pezót a fizetésébôl, és átadom neked, mint jutalmat az éberségedért. Ez a fickó pedig három napig fogdában fog ülni.";
			link.l1 = "Köszönöm, " + GetAddress_FormToNPC(NPChar) + ". Az ilyen jogsértések megállítása közös kötelességünk.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hmm. De ez a tétel nincs tele! Hogy történhetett ez?";
					link.l1 = "A francba! Kérem, bocsásson meg, az én hibám. Azonnal megveszem a hiányzó mennyiséget, és átadom a teljes tételt, ahogy megbeszéltük.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Szóval maga a futárunk? Igen, persze. Rendezzük el a dolgokat a rakománnyal, és utána kapja meg a további utasításokat.";
					link.l1 = "Rendben.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "Nem látom a hajóját a kikötôben. Azt javasolja, hogy a dzsungelen keresztül vonszoljuk a rakományt? Siessenek a kikötônkbe és jöjjenek vissza.";
				link.l1 = "A hajóm a sziget másik oldalán van. Elviszem a kikötôbe.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "Rendben, bombák és puskapor, 2500 egységenként... Jó. A katonák kirakodják a rakományt, az embereid pihenhetnek. Itt a fizetség a szállítmányért - ötezer pezó.";
			link.l1 = "Köszönöm! Mi legyen a következô lépés? Monsieur LeCroix azt mondta...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Igen, igen, most megkapja az utasításokat. Készen áll a figyelemfelhívásra?";
			link.l1 = "Persze, biztos úr.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Tehát, a mi katonai hajónk 'háborús' a spanyol kolónia Porto Bello közelében cirkál, a spanyol fôsziget déli részén. Ez a hajó Florian Shoke parancsnoksága alatt áll, aki egy spanyol nehézgálya rajtaütésére készül, amely két hét múlva indul Porto Bellóból.\nA probléma az, hogy fregattunk ágyúi öntési hibában szenvednek, és tizenöt ágyút kell kicserélnünk, hogy megmentsük a küldetést, különben a gálya túlerôben 'Warlike' mind ágyúkban, mind emberekben. \nA csere nélkül Florian Shoke kénytelen lesz eredménytelenül elhajózni. Egy ilyen eseménysorozat rendkívül nem kívánatos. Az ön feladata a küldetés megmentése tizenöt ágyú tizennégy napon belüli leszállításával.";
			link.l1 = "Szóval fel kell vennem tizenöt ágyút a fedélzetre, Portobello felé kell mennem, megkeresni a fregatt 'Militant' és átadni az ágyúkat Florian Shoke kapitánynak?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Pontosan. Pontosan így van. Készen állsz a küldetésre?";
			link.l1 = "És mi lesz a fizetséggel?";
			link.l1.go = "trial_5";
			link.l2 = "Sajnálom, tiszt úr, de nem akarok belekeveredni. Kérem, bocsásson meg.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "Ön a saját jogán, de számítottam a beleegyezésére. Most pedig keresnem kell egy másik futárt, bár már nincs sok idôm hátra... Nos, nem tartom fel tovább, kapitány úr.";
			link.l1 = "Üdvözlettel.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "Ne aggódjon emiatt. Florian Shoke kétszáz aranydublont fog fizetni neked a hajó kincstárából. Emellett biztos vagyok benne, hogy a saját céljaira akarja felhasználni önt és a hajóját - természetesen az ön beleegyezésével.";
			link.l1 = "Rendben, benne vagyok ebben a küldetésben! Hol vannak az ágyúk?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Parancsot adok a katonáknak, hogy azonnal rakodjanak fel a hajódra. Induljon, amint tud, monsieur! Sok szerencsét!";
			link.l1 = "Köszönöm. A szerencse biztosan nem fog ártani, és a hátszél sem...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Felfedezô mód: az idôzítô ki van kapcsolva.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, talán. Nos, a jó hírneve miatt megkockáztatom, hogy megbízom magában. Más esetben nem is beszélnék veled errôl. A helyzet az, hogy elég nagy tétel különleges rakományra van szükségünk, így nagy teherhajóra és kockázatvállalási hajlandóságra lesz szükséged. Emellett meg kell adnod a szavadat, hogy senkinek nem szólok róla.\nHa kínosnak találod, akkor most azonnal mondd el. Azt hiszem, hogy a lényegre tértem...";
				link.l1 = "Érdekesen hangzik. Benne vagyok, ha a fizetés rendben van, bár fogalmam sincs, hogy milyen szállítmányról beszélsz. A szavamat adom.";
				link.l1.go = "zpq_prs2";
				link.l2 = "Azt hiszem, nemet mondanék... ha a szavamat adnám, akkor munkát kellene végeznem, ami eléggé zavarónak tûnik. Ezt nem fogom megtenni.";
				link.l2.go = "zpq_fld";
				Notification_Reputation(true, 71, "low");
			}
			else
			{
				dialog.text = "Az ön hírneve elfogadhatatlan számomra. Kérem, hagyja el a szobát. Képesek vagyunk egyedül is megoldani a problémáinkat.";
				link.l1 = "Mindegy, akkor oldja meg ôket...";
				link.l1.go = "exit";
				Notification_Reputation(false, 71, "low");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Nos, legalább ôszintén visszautasítottad... Nem tartalak tovább itt.";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "Hm, igazából ezt nem vártam tôled. Meg kell kérnem, hogy távozzon... És ne feledje az ígéretét, hogy nem árul el semmilyen információt.";
			link.l1 = "Sajnálom...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Nagyszerû. Nagyszerû. A probléma az, hogy a legutóbbi vihar megrongálta a lôpor készletünket az erôd arzenáljában. Remélem, nem kell elmagyaráznom, hogy kényes bajban vagyunk. Hosszú ostrom esetén az erôd nem lesz képes semmire. Nem fogunk sokáig kitartani.";
			link.l1 = "Most már értem. Milyen rakományra van szükséged - és mekkora mennyiségre?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "Szükségünk van 15 000 puskaporos hordóra. 100 000 pezó-t fizetek... Meg kell értenie, hogy ez egy nagyon jó ár. A jelenlegi helyzetünk arra kényszerít, hogy ilyen költségekkel menjek, bár nehéz volt meggyôzni a kormányzó pénztárosát... A viharszezon nem engedi, hogy a saját ellátóvezetékeinket használjuk, és nem akarjuk, hogy mindenki tudjon errôl a bajról...";
			link.l1 = "Értem... az ár tényleg szép. Említette a kockázatokat...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "Úgy értettem, hogy egy ekkora mennyiségû puskapor nagyon veszélyes lehet a szállítás során. Láttam néhány robbanást a saját szememmel, néha egyetlen szikra is elég lehet. De ha szembenézel a viharral... Az egész konvoj általában távolságot tart a potenciális branderektôl. Ha felrobban, akkor mindenkinek annyi!";
			link.l1 = "Értem... De én mindig tartom a szavam, úgy gondolom, hogy ez megtörtént.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Nos, senor... Olyan szörnyû dolgokat mondott nekem, hogy elvesztettem minden kedvemet ahhoz a munkához.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Jó, nagyon örülök, hogy megegyeztünk. Fizetni fogok, amint elhozza nekem a rakományt.\nEgy hét múlva lesz pénzem, nem hamarabb, úgyhogy ne siessenek, de arra kérem, hogy ne késlekedjenek túl sokat.";
			link.l1 = "Megértem, senor. Rajta vagyok.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "Végre! Azt hittem, hogy már elfelejtette a megállapodásunkat. Azonnal utasítom a katonáimat, hogy kezdjék meg a hajója kirakodását. A puskaporral való munka nagyon kényes dolog, ha-ha!";
			link.l1 = "Nagyszerû, senor, de emlékeztetnem kell a fizetségre.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Igen, persze. 50 000 pezót fog kapni, ahogy megbeszéltük.";
			link.l1 = "Most biztos csak viccel velem, senor?! 100 000 pezóban állapodtunk meg!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Megbízható", "Trustworthy");
				link.l2 = "(megbízható) Kezdem azt hinni, hogy meg fogsz csalni, ezért nem megyek el innen a 125 000 pesóm nélkül!";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "Hm... látom, hogy a körülmények megváltoztak. Nos, jobb, ha fogom a pénzt és elmegyek...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 35)
			{
				Notification_Skill(true, 36, SKILL_LEADERSHIP);
				dialog.text = "Ah, igen... Pontosan! 100 000 pezó. Elfelejtettem, bocsásson meg. Az én koromat kell hibáztatni, a szklerózis miatt, tudja... Persze, itt vannak az érméi. Öröm volt önnel üzletelni, kapitány. Most sajnálom, de rengeteg munkám van...";
				link.l1 = "Önnek is, senor. Viszlát.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				Notification_Skill(false, 36, SKILL_LEADERSHIP);
				dialog.text = "Micsoda?! Fogd a pénzed és tûnj el, vagy megrohadsz ebben a kazamatában!";
				link.l1 = "Maga egy hazug, senor! Azt tanácsolom, hogy adjon nekem rendesen pénzt, különben elviszem a rakományt!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Bocsásson meg... Rendben, elfogadom az összeget, amit felajánl, és végeztünk.";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Micsoda gorombaság! Nem vagyok elmebeteg, és pontosan emlékszem, hogy 100 000 pezót ajánlottam fel.\n A fenébe! Nem játszom a játékodat!";
				link.l1 = "Nyugodjon meg. Gondolj a kész puskaporral teli branderre az erôd elôtt. Ha csak egy szót is szólok, az erôd rommá válik.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "Hm-hm... erôs érv. 125 000 pezó, azt mondja? Tessék, vegye el, és most bocsásson meg, de dolgom van...";
			link.l1 = "Viszlát, senor. Viszlát.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "Micsoda?! Katonatiszt vagyok! Azt hiszed, hogy megijeszthetsz, kölyök?! Ôrök, vigyétek "+ GetSexPhrase("ôt","ôt") +"!";
				link.l1 = "Sok szerencsét a próbálkozáshoz, patkányok...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "Pompás! Jól döntöttél. Fogjátok az érméket és viszlát. Örömömre szolgált!";
			link.l1 = "Ég veled...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Te szemétláda! Ôrök, vigyétek "+ GetSexPhrase("ôt","ôt") +"!";
			link.l1 = "Argh! Úgy tûnik, hogy el kell vennem a pénzemet a lélegzetvisszafojtott testedtôl...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Wow!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 kaliberû ágyú";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 kaliberû ágyúk";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 kaliberû ágyú";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "teljes couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 kaliberû ágyúk";
		break; 
	}
}
