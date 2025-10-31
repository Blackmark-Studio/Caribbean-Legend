void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Jó napot! Ön a kapitány " + GetFullName(pchar) + "?";
			link.l1 = "Igen, én vagyok. És mi a helyzet?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "Levelet hoztam önnek Jamaica kormányzójától, Sir Edward Doily-tól.";
			link.l1 = "Hûha! Erre nem számítottam... És mit akar tôlem a kormányzó?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Olvassa el a levelet, uram. Röviden: felajánlják önnek, hogy részt vehet a regattán, egy versenyen, amely az egész szigetvilágot átszeli. Nem maradtak észrevétlenek a pletykák a tengerészeti képességeidrôl, és a figyelemre méltó gyorsaságodról a vitorlázásban.";
			link.l1 = "Hihetetlen! Nos, én... Megfontolom.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Továbbá szabad bejárást biztosítok neked Port Royal kikötôjébe. Itt van egy 30 napra szóló engedély. A küldetésem teljesítve. Viszlát, kapitány.";
				link.l1 = "Köszönöm, kapitány. Az engedélyt szívesen fogadom. Viszontlátásra!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Jól van. Most már teljes a küldetésem. Viszlát, kapitány.";
				link.l1 = "Ég veled!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Viszlát, kapitány. Gondolom, részt vesz a regattán?";
				link.l1 = "Pontosan, uram. A nevem " + GetFullName(pchar) + ". Megkaptam a meghívót.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Kér valamit, uram?";
				link.l1 = "Nem, semmit. Már megyek is.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Örülök, hogy megismerhetem, kapitány " + GetFullName(pchar) + ". Akkor kezdjük. Az alapokkal már tisztában van a levélbôl, ugye? Kizárólag Luggerek, és a regattán való részvételhez a századod egyetlen hajójának kell lennie. Teljesítettétek ezeket a követelményeket?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Még nem. Most megteszem, és hamarosan visszajövök.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Igen, hoztam.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Azért jött, hogy részt vegyen a regattán, de hol van a hajója, kapitány?";
				link.l1 = "Elnézést, uram. Azonnal a kikötôbe viszem a hajómat.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Á, már megint te vagy az. Mindent megtettél, hogy teljesítsd a regatta követelményeit?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Még nem. Most megteszem, és hamarosan visszajövök.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Igen, hoztam.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Kapitány, nincs mit megbeszélnünk, amíg nem látom a hajóját a kikötôben. Megértette, vagy ismételjem meg magam?";
					link.l1 = "Elnézést, uram. Azonnal a kikötôbe viszem a hajómat.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Kér valamit, uram?";
				link.l1 = "Nem... ez semmiség. Már indulok is.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Jól van, rendben. Most a következô pont. Mi a neve a hajójának?";
			link.l1 = "'"+pchar.Ship.Name+"'.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Mivel a regattát az angol hatóságok rendezik, és a rögzített szabályok miatt a hajód nevét a verseny idejére meg kell változtatni. Ne aggódj, ez minden résztvevôt érint.";
			link.l1 = "Azt mondják, hogy balszerencsét hoz, ha megváltoztatod a hajód nevét.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "A nevet a regatta után vissza lehet változtatni. Tehát a luggered a 'Saint Catherine'.nevet viseli majd.";
			link.l1 = "Értem uram, meg fogom változtatni a nevet.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Most pedig beszéljünk magáról a regattáról. Hallgassanak ide figyelmesen. Egy szabálypapírt is adok nektek.\nA regatta Port Royalban kezdôdik és ott is ér véget. Öt pont van, amit el kell érnetek\nAz elsô Port Royalból Belize-be, West Mainba\nA második Belize-bôl Kikötô-au-Prince-be, Hispaniola\A harmadik Kikötô-au-Prince-bôl St.John's, Antigua\nNegyedik St.John's és Bridgetown, Barbados\nAz utolsó pedig Bridgetown és Port Royal\nAm érthetô?";
			link.l1 = "Teljesen világos, uram.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Pompás. A következô városok kikötôi irodáiban kell bejelentkeznie: Belize, Kikötô-au-Prince, St.John's, Bridgetown. Kizárják, ha bármelyik várost kihagyja, vagy megszegi a helyes sorrendet\nAz irodák a regatta ideje alatt huszonnégy órán át nyitva tartanak. Kopogjatok be az ajtón, és beengednek benneteket.";
			link.l1 = "Megértettem.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "Tilos hajót cserélni és további hajókat felvenni a századodba. Ezt minden városban ellenôrizni fogják, ezt vegyétek figyelembe.";
			link.l1 = "Megfontolom. Ki számít általában gyôztesnek, és beszélhetünk a díjakról?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "A regattának csak egy gyôztese van - az a kapitány, akinek a hajója elsôként éri el Kikötô-Royalt. A díj nagyon értékes. A gyôztes nagy összeget kap - 250 000 pesót. Emellett egy sor értékes ajándékot is kap.";
			link.l1 = "A vesztesek nem kapnak semmit?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Pontosan. Ráadásul az angol gyarmatok sok gazdag és szegény polgára fogadásokat köt a regatta gyôztesére. Fogadhatsz... magadra is. Általában minden kapitány ezt teszi. Ha nyersz, még többet keresel, és ne feledkezz meg a motivációról sem. Általában elfogadom a fogadásokat\nA gyôzelmedre fogadsz?";
			link.l1 = "Ha! Persze, hogy az vagyok. Mennyit fogadhatok?";
			link.l1.go = "Regata_rate";
			link.l2 = "Majd meggondolom. Talán fogadni fogok.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Gondolkodj, ha akarsz. Van még egy kis idôd a regatta kezdete elôtt.";
				link.l1 = "Rendben. Mikor kezdôdik?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Gondolkodj, ha akarsz. Van még egy kis idôd a regatta kezdete elôtt.";
				link.l1 = "Rendben.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "Három nap múlva, tizenkét órakor, délben. Gyere a mólóra, és ne késs el. Öt versenyzôd lesz.\n"+pchar.questTemp.Regata.AdversaryName.a+", a "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", a "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", a "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", a "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", a "+pchar.questTemp.Regata.AdversaryShipName.e+"\nMindannyian tapasztalt kapitányok. Nos, úgy tûnik, ennyi. A biztonság kedvéért vigyétek a szabálypapírt. Találkozunk a rajtnál!";
			link.l1 = "Viszontlátásra, uram.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "Várj! Megkapod a 30 napos engedélyt az angol és francia kikötôk meglátogatására. A regatta nem tart tovább egy hónapnál. Kérem, vegye el.";
			link.l1 = "Köszönjük!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "Mennyi a tét?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Azt hiszem, még gondolkodnom kell egy kicsit.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Uram, ez nem vicces, és nem is vicces. Ilyen kis összeggel nem fogok dolgozni.";
				link.l1 = "Elnézést... Gondoljuk át a tétet.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Uram, a regatta szabályai miatt nem fogadhatok el ilyen tétet. Csökkentse az ésszerû értékre.";
				link.l1 = "Kár érte. Gondoljuk át az összeget.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? Ez egy szép tét. Kész vagyok elfogadni. A pénze, uram?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Kérem, vegye el.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "Most nincs elég érmém. Késôbb eljövök hozzád, és meg fogjuk kötni a tétet. És még gondolkodom rajta, talán átgondolom az összeget.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Pompás! Most már csak annyit kell tennie, hogy elsô lesz, és a nyeremény az öné lesz. A végsô értéke változhat, minden attól függ, hogy végül hányan tesznek rád.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Értem. Mikor kezdôdik a regatta?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Értem, értem. Várom a rajtot. Viszlát!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Á, megint itt vagy, kapitány " + GetFullName(pchar) + "? Mit akarsz?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Fogadni akarok a gyôzelmemre.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "Nem, semmiség. Csak üdvözölni akartalak.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitány, maga az elsô alkalom? Hadd mondjam el, hogy óvatosnak kell lennie. A versenytársai kellemetlen meglepetéseket okozhatnak önnek...","Kapitány úr, tétet tettem önre. Ne okozzon csalódást!","Kapitány, a regatta kikötôiben a helyiek talán felajánlanak neked valamit. Ez gyakran nagyon hasznos lehet. Gondolj erre!"), LinkRandPhrase("Jó utat, kapitány!","Kapitány, kérem, legyen óvatos, a kasztíliaiak gyakran vadásznak a résztvevôk luggereire a spanyol vizeken.","Hallottam, hogy néhány gyanús alak gyakran felajánlja 'szolgálatait' a regattakapitányoknak. Az önök döntése, hogy elfogadják-e az ajánlatukat vagy sem."));
			link.l1 = "Igen, igen, persze... köszönöm, azt hiszem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Kapitány, én és a férjem tízezret tettünk a gyôzelmére. Ne hagyjon cserben minket! Imádkozni fogok önért!","Kapitány! Sok szerencsét kívánok!","Uhm... te egy olyan bátor és bátor kapitány vagy...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Hé, tengerész! Integess a szépségnek! Várni fogom a visszatérésedet!","Hé, sós tengerész! A hölgy azt mondta, hogy engem ingyen ad a regatta gyôztesének jutalmul... Próbáld meg megnyerni, olyan jóképû vagy!","Ne felejts el meglátogatni minket, ha visszajössz, szépfiú, a legmagasabb színvonalúak szerint fogunk kedveskedni neked!");
			link.l1 = "Nos, hah... Megfontolom, köszönöm!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Kapitány, a regatta 12 órakor kezdôdik. Most már pihenhet, készülünk az ünnepségre. Jöjjön vissza délben, a versenytársai is ezt fogják tenni.";
				link.l1 = "Rendben, uram! Várom a rajtot...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Tessék, kapitány.";
				link.l1 = "Én és a legénységem készen állunk, uram! Várom a rajtot...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "Tehát, uraim, itt vagyunk. Bejelentem a regatta kezdetét. Ismerik a szabályokat. Aki elôször tér vissza ide, azt gyôztesként fogjuk dicsérni. Hölgyeim és uraim, kívánjunk szerencsét bátor kapitányainknak!\nUrak! Készen álltok? Készen állunk! Készüljetek! Gyerünk!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("A regatta elkezdôdött! Szálljatok be a fedélzetre! Irány Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Üdvözlet, kapitány! Úgy értesültem, hogy részt vesz a karibi regattán.";
			link.l1 = "Ez igaz. A hír valóban gyorsabban terjed a szigetvilágban, mint a szél.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Így van, kapitány. Van egy ajánlatom a számodra. A hajójára és a regattára vonatkozik.";
			link.l1 = "Heh! Érdekes. Hallgatlak, uram.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Van egy garnitúra tökéletes vitorla egy luggerhez, a legjobb pamutból készültek. Ezek a vitorlák megnövelik a hajód gyorsulását, és idôelônyt adnak neked az ellenfeleiddel szemben\nKész vagyok eladni ôket neked, vagyis ha meg akarod venni.";
			link.l1 = "Mennyit kérsz ezekért a vitorlákért?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Csak 15 000 pezó. El kell ismernie, hogy ez egy nagyon szerény ár egy ilyen... helyzetért.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Egyetértek. Megveszem ezeket az új vitorlákat a luggeremre. Tessék, vegye el a pénzét, uram. Lenne olyan kedves, és elszállítaná a hajómra, amíg én bejelentkezem.";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "Nincs ennyi pénzem. Így nem tudom megvenni a vitorláit.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Meglesz, uram. Az embereim csak a parancsra várnak, és ígérem, nem fogja megbánni. Különben is, ezek a vitorlák szép kék színûek. Az ön szépsége értékelni fogja.";
			link.l1 = "Rendben van! Nos, nekem most mennem kell, te meg csináld meg a vitorlákat.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Milyen kár. Nos, a te döntésed. Viszlát, kapitány.";
			link.l1 = "Viszontlátásra!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Hello, kapitány " + GetFullName(pchar) + ". Beszélnünk kell önnel... valójában csak egy... üzleti ajánlatról van szó.";
			link.l1 = "Hm. Érdekes, és honnan tudja, hogy ki vagyok?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "Mit mondhatnék, mindig azt mondták, hogy tehetséges vagyok... Ha-ha, hát a Regatta teljes lendülettel zajlik, és te részt veszel benne, te vagy a híres kapitány!";
			link.l1 = "Értem, értem. Nos, mondd el, amit gondolsz.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Tudjuk, hogy még egy résztvevô van elôttetek - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" a "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". Nemrég hagyta el a kikötôt, és hamarosan elhajózik a Gonaives-fok mellett.";
			}
			else
			{
				dialog.text = "Tudjuk, hogy van még egy résztvevô közvetlenül mögötted - "+pchar.questTemp.Regata.AdversaryName.b+" a "+pchar.questTemp.Regata.AdversaryShipName.b+". Ô néhány órán belül itt lesz.";
			}
			link.l1 = "Hmm... nagyon jól informált vagy.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "Hadd menjetek el elôtte, és foglaljátok el a helyét!";
			else sTemp = "ezért sokáig vezetni fogsz.";
			dialog.text = "Abszolút. Most pedig térjünk a lényegre. Felajánljuk a segítségünket a pénzéért. Négy ágyút helyeztünk el a hajónkról a Gonaives-i öböl mögötti fokon. Bármelyik regattahajónak meg kell dupláznia\nAz ágyúk láncos lövedékekkel vannak töltve. Ha megegyezünk, megmondom az ágyús barátainknak, hogy tegyék tönkre a versenytársad vitorláit, így kénytelen lesz idôt veszíteni a javításukra, "+sTemp+".";
			link.l1 = "Mennyit kérsz ezért a szolgáltatásért?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "Nem. Nem fogok ilyen módszereket használni a gyôzelem érdekében. Tévedtél velem kapcsolatban. Viszlát, uraim.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Nos, kapitány, a te döntésed. Viszontlátásra.";
			link.l1 = "Köszönöm az információt a köpenyrôl. Távol fogok maradni tôle.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Nem sokat. Csak "+iTemp+" pezó. És az egyik versenytársad majdnem két napot veszít egy... baleset miatt, ha-ha!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Heh! Te beszélsz értelmesen, barátom! Fizetek. De milyen garanciát kapok arra, hogy elvégzi a munkáját? És hogy nem lövöd le a hajómat, amikor a köpeny mellett haladok el?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "Nincs ennyi pénzem. Szóval nem tudom igénybe venni a szolgáltatásait.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Kapitány kérem, mi csempészek vagyunk, nem kalózok. Mindannyian becsületes emberek vagyunk... a magunk módján. Biztosan igénybe vette már a szolgáltatásainkat, igaz? A szavamat adom. Bízhat benne.";
			link.l1 = "Rendben, fogadja el a pénzét.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Örülni fog ennek az üzletnek, kapitány. Azonnal értesítem a fegyvereseimet. Sok szerencsét!";
			link.l1 = "Neked is...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Szép napot, fiam. Szeretnélek köszönteni, és alázatosan megkérdezni: akarsz-e hozzájárulni a plébánia kincstárához, mint Anglia és nagy Urunk hûséges szolgája?";
			link.l1 = "Padre, az emberek a lelkük' hívásuk miatt jótékonykodnak, nem pedig kényszerbôl. Kezdem azt hinni, hogy a szigetországban mindenki elhatározta, hogy kirabolja a regatta kapitányait...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Persze, szent atyám. Mennyi lenne elég?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Csak annyi, amennyit a kívánságod és a lehetôségeid megengednek, fiam. Egyházközségünk a legkisebb összegnek is örülni fog.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Ez rossz hozzáállás, fiam. Mindannyiunknak vannak bûneink, ne feledkezz meg a lelkedrôl. Meg kell majd jelenned a Teremtônk elôtt... és talán hamarosan.";
				link.l1 = "Nincs szükségem a prédikációidra, szent atyám. Búcsúzz el.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "Egyházközségünk és én köszönjük ezt a szerény ajándékot.";
				link.l1 = "Szívesen látjuk, szentatya.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "Az egyházközségünk és én köszönjük ezt az ajándékot. És figyelmeztetni akarlak, fiam, hogy néhány bûnös ember ártani akar neked. Légy óvatos a tengeren!";
				link.l1 = "Atyám, az emberek minden nap terveznek valamit ellenem... De köszönöm, hogy aggódsz a sorsomért.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "Egyházközségünk nevében köszönöm ezt az értékes ajándékot. Viszonzásul szeretném figyelmeztetni Önöket, hogy néhány nagyon rossz ember összeesküvést szô ellenük. Úgy hallottam, hogy ezek az aljas hitehagyottak éppen ebben a kikötôben akarják elsüllyeszteni a hajótokat\nEgy puskaporral teli hajót már elôkészítettek erre a gonosz tettre. Légy óvatos, fiam, ezek az elveszett lelkek komolyan gondolják aljas szándékaikat... Áldjon meg az ég!";
				link.l1 = "Köszönöm, szent atyám. Figyelmes leszek.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Nagyon nagylelkû vagy, fiam. Isten alázatos szolgájának szerénysége nem engedi meg, hogy elfogadjam az egész összeget, amit hajlandó vagy odaadni az egyházunk javára. Csak 10 000 pezót fogadok el\nViszonzásul figyelmeztetni akarlak, hogy rossz emberek szövetkeznek ellened. Úgy hallottam, hogy ezek az aljas hitehagyottak éppen ebben a kikötôben akarják elsüllyeszteni a hajóját\nElôkészítettek egy puskaporral teli luggert, melynek neve '"+pchar.questTemp.Regata.BranderName+"', angol zászló alatt hajózik, hogy gyanú nélkül közeledhessen önhöz. Légy óvatos, fiam, ezek az elveszett lelkek komolyan gondolják aljas szándékaikat.\nElpusztítsd ôket, feloldozást adok e bûn alól. Áldásom rád! Imádkozni fogok érted, fiam.";
				link.l1 = "Köszönöm, szent atyám. Ha ezek a szemetek valami rosszat mernek tenni, egyenesen a pokolba küldöm ôket!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "Ne légy mérges, fiam. A harag bûn. Jogod van nem jótékonykodni. Békében járj, fiam.";
			link.l1 = "Isten veled, szent atyám.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "Jó napot, kapitány! A nevem " + npchar.name + " és szeretnék...";
			link.l1 = "...felajánlani nekem valamit... Igazam van, ifjú hölgy?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Természetesen, kapitány! És miért lepôdik meg ennyire? Ön egy jóképû tengerész, és részt vesz a regattán, biztos, hogy mindenki hajlandó eladni önnek valami hasznos tengeri holmit.";
			link.l1 = "Rendben, szépségem, igazad van. Mit hoztál nekem?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "Egy kiváló távcsô.";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "egy közönséges távcsô.";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "egy jó távcsô";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Tessék, nézze meg. Apámtól örököltem. Ô is tengerész volt, akárcsak te, és sok navigációs kütyüje volt. Nekem nincs rá szükségem, de neked biztosan hasznos lesz. Csak "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" kérek érte.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Nocsak, nocsak..."+sTemp+"! Érdekes! Azt mondom, megveszem tôled. A szép szemedért. Szóval "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" akarsz érte? Kérem, vegye el a pénzét.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"? Nem, kislány, sajnálom, de nincs rá szükségem. Nekem már van egy nagyon szép saját távcsövem. Szóval... sajnos!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Köszönöm, kapitány. Remélem, hogy jó szolgálatot tesz majd. Örülök, hogy hasznosnak találta. Sok szerencsét a regattán!";
			link.l1 = "Köszönöm, " + npchar.name + "! Búcsúzás.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "Milyen kár, kapitány. Reméltem, hogy hasznos lesz önnek. Nos, megpróbálom eladni valaki másnak. Viszontlátásra!";
			link.l1 = "Viszlát, " + npchar.name + ".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Üdvözlöm, kapitány. Ön nem a regatta résztvevôje? Igazam van?";
			link.l1 = "Igen. És mi a helyzet, tiszt úr?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Bizonyára már értesült róla, hogy a kolóniánkat spanyol ostrom alatt tartják. Ezért akar beszélni önnel a kormányzó. Lenne olyan kedves meglátogatni ôt? Most nagyon sürgôs az ügy.";
			link.l1 = "Hm... Rendben, azonnal megyek és meglátogatom Ôexcellenciáját, bár nem igazán értem, hogyan lehetek én is részese a katonai mûveleteknek.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Ön is benne van, kapitány. Ne vesztegessük az idôt, és menjünk a rezidenciára. Kövessenek.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Uram! Készen állok, hogy civileket küldjek a hajójára. Most már mehetünk?";
			link.l1 = "Igen, persze. Azonnal indulunk. Mondja meg az embereknek, hogy szálljanak fel a hosszúhajókra.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Megcsináltuk... Úgy néz ki, hogy ez a sloop az osztag felderítôje volt, és ezek a kasztíliai gazemberek felderítették a környéket. Kapitány, kérem, segítsen nekem, hogy a nôket a barlangokba juttassam, lehetséges, hogy több spanyol különítmény van.";
			link.l1 = "Jól van. Induljunk!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Köszönöm a segítségét, kapitány! Ha te és a bátorságod nem lett volna... Igazi hôs vagy, minden veszély és a saját érdeked ellenére befejezted ezt a mûveletet. Gondolkodtam azon, hogyan jutalmazhatnám meg... és van egy módja, hogy javítsuk az esélyeiteket a regattán.";
			link.l1 = "Érdekes. Mi ez a mód?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Üdvözlet, kapitány " + GetFullName(pchar) + ". Örülök, hogy eljött. A városunknak szüksége van a segítségedre.";
			link.l1 = "Uram, ha a spanyol századról beszél, amelyik épp most ostromolja a kolóniájukat, akkor fogalmam sincs, hogyan segíthetnék. Én egy luggernek parancsolok, nem egy csatahajónak...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Figyeljen rám, kapitány, és meg fogja érteni. Komoly bajban vagyunk. A város spanyol ostrom alatt áll. Hamarosan döntô ütközet kezdôdik az erôddel. Ráadásul néhány száz spanyol már partra szállt, és elzártak minden kijáratot a városból, most már a tengerrôl és a szárazföldrôl is támadhatnak minket\nAz erôd helyôrsége arra készül, hogy megvédje a várost a századdal szemben, és magában a településen sincs elég katona. Minden fegyverrel bánni képes férfit mozgósítanak, de mi lesz a többiekkel?\nSzáz lelket számláló nô van Bridgetownban. El tudják képzelni, mi történik velük, ha nem sikerül megvédeni a kolóniánkat? Azt hiszem, hogy önök megértik.";
			link.l1 = "Uram, én megértem önt, de ismétlem, hogyan segíthetnék? Mit akar tôlem? Hogy harcoljak a hadihajók ellen, vagy hogy a legénységemmel együtt jelentkezzek a városi milíciába?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "Ön angol, segítsen nekünk megmenteni az angol polgárokat és ami fontos - a nôket!" break;
				case FRANCE: sTemp = "Ön francia, tehát alapvetôen a szövetségesünk, segítsen megmenteni az angol polgárokat és ami még fontosabb - a nôket!" break;
				case SPAIN: sTemp = "Tudom, hogy spanyolok vagytok, és ezek a ti népetek a tengeren, így tudom, hogy már így is sokat kérek, de ezek a nôk ártatlanok, és semmi közük ehhez a csatához. Szóval kérem, könyörgöm, segítsenek nekik!" break;
				case HOLLAND: sTemp = "Tudom, hogy önök hollandok, és a mi nemzeteink háborúban állnak, de önök angol zászló alatt vesznek részt az angol regattán. Nem gondoljátok, hogy helyes az ártatlan és békés emberekért, a nôkért harcolni? Kérem kapitány, segítsen nekik!" break;
			}
			dialog.text = "Egyik sem. Csak egy dolgot kérek tôled. Vigye el innen a nôket és a gyerekeket a hajóján. Nem sokan vannak, körülbelül százan. Vigyétek ôket a Harrison-fokhoz Mahony hadnaggyal együtt, ô majd gondoskodik róla, hogy biztonságban legyenek a barlangban\nbiztos vagyok benne, hogy a spanyolok nem fogják keresni ôket. Nincs tartalék hajóm, minden hajónkat elsüllyesztette a spanyol hajóraj. Te vagy az utolsó reményem. Egy út alatt el tudod vinni ôket a fokhoz, még akkor is, ha a hajód túlterhelt lesz. A sorhajók nem fognak követni téged.\nNem kérhetek mást, hogy megtegye. "+sTemp+"";
			link.l1 = "Uram, sajnálom, de a hajóm már így is túlterhelt, és még két útra sem fog tudni ennyi embert befogadni. Bármilyen véletlen ágyúgolyó, még ha a közelébe is csapódik, a hajómat és a nôit a tenger fenekére küldi. Bocsáss meg, de nem tudok segíteni neked.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Rendben van, uram. Segíteni fogok. A tengerész becsület kötelez erre.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Örülök, hogy beleegyezett. Igazi katona vagy. Mahony hadnagy elviszi a nôket és a gyerekeket a hajójára. Isten éltessen, kapitány!";
			link.l1 = "Köszönöm, uram. Ne vesztegessük az idôt!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Siessen, kapitány. Az idô rohan.";
			link.l1 = "Már indulok is!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "Ez hihetetlen. Meg sem próbálod? Nos, igazad van. Nem követelhetek tôled semmit. Ha csak egy közönséges kapitány lennél, száz nô miatt elkoboznám a hajódat, de te regattán veszel részt, és ezért az angol gyarmatok fôkormányzójának védelme alatt állsz\nAzt reméltem, hogy a lelkiismereted majd jobb belátásra bír, mégis tévedtem. Menj, és Isten legyen irgalmas a lelkedhez!";
			link.l1 = "Viszontlátásra, uram.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "A spanyolok a nyomunkban vannak! Istenem, segíts rajtunk!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "Mahony hadnagy meghalt... ez egy rémálom lehet. Bátor tiszt volt. Kapitány, elvinne minket egy barlangba? Csak vigyen oda minket, és majd mi gondoskodunk magunkról.";
			link.l1 = "Persze. Kövessenek!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Itt vagyunk... köszönöm, kapitány! Most mentett meg mindannyiunkat! Gondolkodtam, hogyan jutalmazhatnám meg önöket... van egy mód, hogy javítsuk az esélyeiket a regattán.";
			link.l1 = "Folytasd.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Port Royalba tart? A legrövidebb útvonal Curacaón keresztül vezet. Vissza Bridgetownba. Keress meg egy Woodrow Dougherty nevû férfit, aki egy öreg tengerész és tapasztalt navigátor. Tökéletesen ismeri a Barbados és Jamaica közötti területet, nagy segítségedre lenne\nEzzel rengeteg kritikus idôt spórolhatsz meg, amire oly nagy szükséged van a gyôzelemhez. Keressétek meg az embert a helyi templomban, és mondjátok meg neki, hogy " + GetFullName(npchar) + " - küldött titeket, nem fog visszautasítani. Vidd el Port Royalba, úgyis oda akart hajózni.";
			link.l1 = "Nagyon jó! Egy jó navigátor hasznos lesz számomra. Viszlát.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Viszlát, kapitány! Sok szerencsét!";
			link.l1 = "Talán még találkozunk...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Szép napot. Kérsz valamit?";
			link.l1 = "A neved Woodrow Dougherty, igazam van?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Igen, igaza van. Miben lehetek a szolgálatára?";
			link.l1 = "Tudom, hogy ön tapasztalt navigátor, és jól ismeri a Barbados és Curacao közötti vizeket. Azt is tudom, hogy Port Royalba akar eljutni. Én is részt veszek a regattán, és van egy utolsó állomás - Port Royal. Szeretnélek megkérni, hogy csatlakozz a legénységemhez, mint navigátor erre az utolsó útra.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Érdekes... És miért gondolod, hogy csatlakozom a legénységedhez?";
			link.l1 = "Nos, mert hallottam rólad a "+pchar.questTemp.Regata.Name+" minden garanciával, hogy nem fogsz nemet mondani. És mert segítettem Bridgetownnak ebben a kritikus pillanatban...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "A "+pchar.questTemp.Regata.Name+"? Most már értem, persze. Rendben, kapitány, segítek a legrövidebb úton elhajózni Port Royalba. Most már el fogsz indulni?";
				link.l1 = "Igen.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? Értem. De kapitány, nem hagyhatom el a városomat ilyen veszélyes idôben. Meg kell értenie engem, mint katonát, aki önzetlen segítséget nyújtott nekünk\nNem akarom, hogy a hátam mögött azt suttogják, hogy az öreg Woodrow elmenekült a spanyolok elleni végsô csata fényében. Én maradok. Ne nehezteljen, kapitány.";
				link.l1 = "És ez az utolsó szava? De én segítettem a kolóniádnak...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "Akkor ne vesztegessük az idôt. Csak hadd pakoljam össze a holmimat, és máris a rendelkezésére állok.";
			link.l1 = "A matrózaim várnak rád a mólón, és elvisznek a 'Saint Catherine'. Köszönöm, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Kapitány, a regatta egy sport, az otthonom spanyol ostroma pedig egy élet. Én nem megyek veled sehová. És megismétlem magam, meg kell értenie engem - a becsület és a kötelesség még mindig jelent valamit ebben a világban. Ez az utolsó szavam, és nem fogok változtatni rajta\nMégis adhatok egy tanácsot, hogyan juthatsz oda pillanatok alatt a legbiztonságosabb útvonalon, vitorlázz északnyugatra Dominika felé, és onnan utat törj Martinque vagy Guadeloupe felé, rajtad és a szeleken múlik. Aztán hajózz egyenesen Kikötô-Royal felé, vagy hajózhatsz Curacao mellett, amit nem javasolnék, de ha jóban vagy a hollandokkal, akkor mindenképpen.";
			link.l1 = "Nos, köszönöm... de csalódott vagyok. Viszlát, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Az utolsó szakaszon megszegted a regatta szabályait. Az eredményedet kizártuk. Nincs több mondanivalóm, kapitány.";
				link.l1 = "Eh... mi a fene! Nos, akkor nincs mit tenni, túl figyelmes voltál. Viszontlátásra!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Kapitány "+GetFullName(pchar)+", gratulálok! "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" órákba telt, amíg befejeztétek a regattát, és messze magatok mögött hagytátok az összes ellenfeleteket. Ez egy figyelemre méltó eredmény!";
					link.l1 = "Köszönöm a kedves szavakat, uram!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Kapitány, sajnos, de az Ön eredménye a legrosszabb, a "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" órákat töltötte. Ne szomorkodj, nagyon kemény ellenfeleid voltak.";
						link.l1 = "Nem vagyok szomorú, uram. Örülök, hogy részt vehettem a regattán és kipróbálhattam magam.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Kapitány, a "+n+"helyen van. Gratulálok a sikeres eredményhez, méltó idôt mutattál - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" órát. Gratulálok a vereség ellenére is!";
						link.l1 = "Minden rendben, uram. Örülök, hogy szép eredményt értem el ezen a kemény versenyen.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty leszállt");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Uram, hadd kérdezzek valamit - hol van a hajója? Nem látom...";
			link.l1 = "Sajnálom, uram. Azonnal a kikötôbe viszem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Gyere el hozzám az irodámba. Átadom neked a jutalmadat a tétedért.";
			else sTemp = "És ha tétet tettél volna a gyôzelmedre, ahogyan azt felajánlottam, akkor még egy extra díjat is kaptál volna.";
			dialog.text = "Holnap látogasson el a fôkormányzóhoz, aki 250 000 pesót és értékes ajándékokat fog adni. "+sTemp+" Ne hagyd el a várost, a hagyományok szerint a nyereményt a város kincstárába adják, ha a nyertes egy hét múlva nem veszi át.";
			link.l1 = "Értettem, uram. Holnap meglátogatom ôt!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "Jó hallani a megtisztelô választ. Sok szerencsét, kapitány úr!";
			link.l1 = "Viszontlátásra, uram.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Kér még valamit, kapitány úr?";
			link.l1 = "Nem... semmit.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Á, hát itt vagy, mister "+GetFullName(pchar)+". Örülök, hogy látlak. A díjáért jött? Készen áll.";
			link.l1 = "Ezt jó hallani! Mekkora a további nyereményem?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Az összes tétet figyelembe véve a végsô nyereménye "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". Kérem, vegye el. Gratulálok!";
			link.l1 = "Köszönjük!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Persze, a népszerûsége Port Royal polgárai körében nôtt. Azt hiszem, ezt ön is látja... de sajnos az emberek memóriája rövid. Úgyhogy fürödjetek a dicsôségben, amíg még ilyen fényes!";
			link.l1 = "Ön a legszebb dolgokról beszél, uram... Nos, lássuk csak, milyen a dicsôségben fürdeni. Viszontlátásra! Öröm volt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Gratulálok a gyôzelméhez, kapitány! Kiváló eredmény!";
						link.l1 = "Köszönjük!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Ne legyen szomorú, kapitány. Nem könnyû megnyerni a regattát, még a részvétel is kiváltság!";
						link.l1 = "Ne aggódjon miattam. Elégedett vagyok az eredményemmel.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Örülök, hogy látom, kapitány! Regisztrálnia kellene magát, hogy beszéljen Stevenson úrral.";
					link.l1 = "Értem, értem. Már úton vagyok hozzá!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, kapitány, miért buktál el így, és pont az utolsó szakaszon!";
				link.l1 = "Igen, milyen ostoba voltam...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Gratulálok a gyôzelméhez, kapitány! Kiváló eredmény!";
						link.l1 = "Köszönöm!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Ne legyen szomorú, kapitány. Nem könnyû megnyerni a regattát, még a részvétel is kiváltság!";
						link.l1 = "Ne aggódjon miattam. Elégedett vagyok az eredményemmel.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Örülök, hogy látom, kapitány! Regisztrálnia kellene magát, hogy beszéljen Stevenson úrral.";
					link.l1 = "Értem, értem. Már úton vagyok!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, kapitány, miért buktál el így, és pont az utolsó szakaszon!";
				link.l1 = "Igen, milyen ostoba voltam...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Gratulálok a gyôzelméhez, kapitány! Kiváló eredmény!";
						link.l1 = "Köszönöm!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Ne legyen szomorú, kapitány. Nem könnyû nyerni a regattán, még a részvétel is kiváltság!";
						link.l1 = "Ne aggódjon miattam. Elégedett vagyok az eredményemmel.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Örülök, hogy látom, kapitány! Regisztrálnia kellene magát, hogy beszéljen Stevenson úrral.";
					link.l1 = "Értem, értem. Már úton vagyok!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, kapitány, miért buktál el így, és pont az utolsó szakaszon!";
				link.l1 = "Igen, milyen ostoba voltam...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
