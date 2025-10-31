// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Riasztás! Itt az ellenség! Fegyverbe!";
				link.l1 = "A fenébe!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Te ott, állj! Ismerôs az arcod... persze! Köröznek a bûneidért! Fiúk, fogjátok el!";
				link.l1 = "A fenébe!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Üdvözöljük a Holland Nyugat-indiai Társaságnál. Beszéljetek gyorsan, az idô pénz.";
				link.l1 = "Kereskedelmi ügyek miatt vagyok itt. Engedélyek, navigációs eszközök és így tovább...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Szeretném felajánlani a szolgálataimat a Társaságnak. Természetesen aranyért cserébe. Felvesznek valakit?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Üdvözöljük a Holland Nyugat-indiai Társaságnál. Beszéljetek gyorsan, az idô pénz.";
				link.l1 = "Sajnálom, úgy tûnik, hogy tévedtem. Elmegyek.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Kereskedelmi ügyek miatt vagyok itt. Engedélyek, navigációs eszközök és így tovább...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Beszéljen gyorsan, az idô pénz.";
			link.l1 = "Kereskedelmi ügyek miatt vagyok itt. Engedélyek, navigációs eszközök és így tovább...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Szeretném felajánlani a szolgálataimat a Társaságnak. Természetesen aranyért cserébe. Felvesznek valakit?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Akkor menj fel Mynheer Rodenburg irodájába.";
			link.l1 = "Köszönöm, máris indulok.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "A cég jelenleg nem vesz fel senkit.";
			link.l1 = "Az nagyon rossz. Elnézést a zavarásért.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Beszélj Mynheer Gerritz-szel. Az asztala balra van, ahogy belépsz. Ô üzletel a szerzôdéses kapitányokkal.";
			link.l1 = "Köszönöm, tiszt úr...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Riasztás! Itt az ellenség! Fegyverbe!";
				link.l1 = "A fenébe!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! Azt hiszem, tudom, ki vagy... De hát persze! Köröznek a bûneid miatt! Fiúk, kapjátok el!";
				link.l1 = "A fenébe!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Beszéljetek a tisztjeinkkel vagy Mynheer Gerritz-szel. Nincs mit mondanom nektek. Szolgálatban vagyok.";
			link.l1 = "A fegyelmetek csodálatra méltó.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Riadó! Az ellenség itt van! Katonák!";
				link.l1 = "A fenébe!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Beszéljetek Mynheer Gerritz-szel.";
			link.l1 = "Rendben, értem.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Riadó! Itt az ellenség! Katonák, kapjátok el!";
				link.l1 = "A fenébe!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. Azt hiszem, valami nem stimmel veled... De hát persze! Körözik a Hollandia ellen elkövetett számos bûntette miatt! Katonák, fogjátok el!";
				link.l1 = "A fenébe!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Kérsz valamit, mynheer?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "A Holland Nyugat-Indiai Társaság kereskedelmi engedélyét szeretném megvenni.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "Úgy hallottam, hogy itt navigációs eszközöket és más hasznos dolgokat lehet vásárolni. Valóban?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "Mit árulsz ma?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "Van egy érdekes dokumentumom a számodra, mynheer. Nézze meg az elsô néhány sort. A Köztársaság túlélésérôl és a Társaság hasznáról szól. Egy bizonyos találkozó koordinátái is benne vannak. Eladom neked, ha érdekel. Természetesen bôkezû áron.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Egy Reginald Jackson nevû kapitány biztosan önnek dolgozik. Egy Xebec nevû hajón hajózik 'Harpy'. Meg tudná mondani, hogyan találhatom meg? Fontos dolgom van vele.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Sürgôsen beszélnem kell Mynheer Rodenburggal. Rendkívül fontos. Hol van?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Nem, semmi.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Nos, szabadon megveheti. De figyelmeztetnem kell, hogy a Társaság nagyra értékeli a szigorú semlegesség hírnevét, ezért tilos bármely nemzet kereskedelmi hajóit megtámadni, amíg ön birtokolja ezt az engedélyt\nHa megtudjuk, hogy ilyen cselekményt követtek el - érvénytelenítjük az engedélyét. Továbbá, ha bármilyen okból konfliktusba kerülsz a hollandokkal vagy a Társasággal, az engedélyedet szintén érvénytelenítjük. Világos?";
				link.l1 = "Kristálytisztán. Ezt nem felejtem el.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Szívesen látjuk, ha licencet vásárol. Szóval, hány nap?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "Az engedély szabad áthaladást biztosít bármely nemzet bármelyik kikötôjébe, megmutatja békés szándékait, és megmagyarázza célját - a kereskedelmet. De nem segít, ha problémáid vannak a törvénnyel. Ebben az esetben egyszerûen elveszik tôled. Ne feledd, \nNe felejtsd el kitûzni a barátságos zászlót, mielôtt behajózol bármelyik kikötôbe. Az ôrjáratok és erôdök' cannoneerek inkább elôbb lônek, és csak utána kérdeznek\nAz engedély minimális hossza húsz nap, a maximális hossza pedig hat hónap vagy 180 nap\nRendben, majdnem elfelejtettem... Nagyra becsült hagyományaink szerint minden engedélyekkel kapcsolatos üzletet dublonnal fizetünk.  Most pedig beszéljünk a feltételekrôl. Mennyi idôre szeretné, hogy a licenc érvényben maradjon?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Sajnálom, de még egy kicsit gondolkodnom kell rajta. Késôbb találkozunk.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Mynheer, kérlek, beszélj hangosan. Nem hallottam jól. Szóval meddig?";
				link.l1 = "Hadd gondolkozzam...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "Az engedély minimális idôtartama húsz nap. És akkor? Húsz nap vagy több?";
				link.l1 = "Hadd gondolkozzam...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "Az engedély maximális idôtartama fél év. Száznyolcvan nap vagy kevesebb?";
				link.l1 = "Hadd gondolkozzam...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "A "+FindRussianDaysString(sti(fQty))+"? Nagyon jó. Ez a "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Elfogadhatóak ezek a feltételek?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Igen, elfogadhatóak.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Sajnos, most nincs nálam ennyi pénz. Késôbb visszajövök az engedélyért.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Sajnálom, de még gondolkodnom kell rajta. Késôbb találkozunk.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'A Sharkkal együtt' - az engedélye kevesebb, mint 180 nap.");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Várjon egy percet... Hadd tegyek ide egy aláírást és egy bélyegzôt... lepecsételve és kész. Fogja a dokumentumot.";
			link.l1 = "Köszönöm! Viszlát, mynheer.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "Valóban így van. Itt vásárolhat navigációs eszközöket, például iránytût, asztrolábiumot, kronométert és homokórát. De nem mindig van teljes készletünk, kivéve talán a homokszemüveget. A vállalkozóink és kapitányaink nagyon gyorsan felvásárolják a többi eszközt. Tehát ha nem találta meg, amire szüksége van - nézzen be hozzánk egy hét múlva, amikor újra feltöltjük a készleteket\nTérképeket és távcsöveket is árulunk. Szeretné látni, hogy mi van nálunk?";
			link.l1 = "Igen, kérem.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, mutasd meg...(olvasás) Nos, nos... Cromwell étvágya egyre nô. Kanker! Azok a puritán kutyák nem ontottak elég vért a saját szigetükön, anélkül, hogy ide hoznák a mocskukat!? Honnan szerezted ezt a küldeményt?";
			link.l1 = "Egy angol futártól kaptam. Szóval, szeretnéd megvenni?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Igen, uram. Peter Stuyvesant biztosan örülni fog, ha elolvassa. És hatékony intézkedéseket fog tenni, hogy megállítsa... Fizethetek aranydublonnal, vagy kiállíthatok egy féléves engedélyt. Melyiket szeretnéd inkább?";
			link.l1 = "Én az aranyat választom.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Az engedélyt akarom.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("700 dublont kapott.");
			dialog.text = "Nagyon jó. Itt van a hétszáz dublona. Szép jutalom a teljesített szolgálatért.";
			link.l1 = "Itt van a küldeménye.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Itt van a küldeménye. Itt van az engedélyed fél évre.";
			link.l1 = "Köszönöm! És itt a küldeménye.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Köszönet. Jó, hogy megmutattad öntudatodat és hûségedet a Köztársaság iránt. Elmondom Matthias Becknek és Peter Stuyvesantnak a jótéteményedet.";
			link.l1 = "Jó tudni. Viszontlátásra!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Attól tartok, ô már elment az Óvilágba a Schneur családdal. Azt hiszem, említette neked.";
			link.l1 = "Így van, említette. De azt reméltem, hogy a szigetvilágban történt legutóbbi ügyei miatt késik. Mondja, Gerritz, van valaki a Társaságban, aki kapcsolatban áll Mynheer Rodenburggal? Talán futárhajókon keresztül?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Egyáltalán nem - mielôtt elment, megkért minket, hogy ne zavarjuk - azt mondta, hogy új, jobb életet kezd.";
			link.l1 = "Reméljük, hogy a mi életünk is jobb lesz. Viszontlátásra.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Hadd nézzem meg a hajónaplókat....Ikema, Immerzeel, Jacobs... Jackson, megtaláltam. Hmm, Reginald Jackson kapitány jelenleg rendszeres hajójáratokat üzemeltet Port Royal és Philipsburg között. Keresse ôt ezen az útvonalon. Nos kapitány, elôre figyelmeztetlek - ha valami csínytevést tervezel, jobb, ha nem teszed, mert ez a kapitány Jackson a mi védelmünk alatt áll. Értjük egymást, mynheer?";
			link.l1 = "Nekem csak dolgom van vele. Egy közös üzlet. Nem akarom megbántani ôt.";
			link.l1.go = "caleuche_1";
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
		break;
		
		case "caleuche_1":
			dialog.text = "Kitûnô. Jackson kapitány általában nem marad sokáig Port Royalban vagy Philipsburgban. Az idô végül is pénz. Miután a hajóját kirakodták és újra megrakodták, általában azonnal útnak indul. Nagyobb szerencséd lesz, ha a tengeri útvonalak mentén találkozol vele.";
			link.l1 = "Köszönöm!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_PrepareCreateGarpiya");
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "Aha, Kapitein " + GetFullName(pchar) + "! Jó, hogy idejöttél. Van egy üzleti ajánlatom számodra.";
						link.l1 = "Érdekes! Hallgatlak, mynheer.";
						link.l1.go = "silk_info";
						break;
					}
					else notification("Túl alacsony a hírneve! ("+XI_ConvertString(GetReputationName(61))+")", "None");
				}
			}
			dialog.text = "Jó napot, Kapitein " + GetFullName(pchar) + "! Miben lehetek a szolgálatára?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "Ami a hajóselymet illeti...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Jó napot! Nem, nincs szükségem semmire, csak üdvözölni akartam.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Nemrégiben kereskedelmi kapcsolatot létesítettem egy lyoni kereskedôvel a Karib-tengeri selyemmel való ellátásáról. Tud róla? A világ legjobb vitorlái készülnek ebbôl a selyembôl, úgyhogy biztosan érdekli.";
			link.l1 = "Ez zene a fülemnek. Mik a feltételei?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Kisebb, de rendszeres szállítmányok. Kéthetente harminc tekercset tudok félretenni önnek. Egy tekercs ára húsz dublon. Legyen így: Minden hónap elsô és tizenötödik napján harminc tekercset tartogatok neked. Ha akkor nem jössz értük, eladom a tekercseket egy másik vásárlónak.";
			link.l1 = "Akkor nincs kötelezettség?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Pontosan, kapitein. Vedd meg a selymet, ha akarod. Az egész tételért hatszáz dublont fizetsz. Remélem, hogy rendszeres vásárló leszel.";
			link.l1 = "Köszönöm az ajánlatodat, mynheer. Megegyeztünk.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Persze, kapitein. A selyem már vár rád. Készen állsz fizetni érte?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Persze! Tessék, itt van 2550 dublon.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "A fenébe is, a hajón felejtettem a pénzt. Mindjárt hozom!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Persze, kapitein. A selyem már vár rád. Készen állsz fizetni érte?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Persze! Tessék, itt van hatszáz dublon.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "A fenébe is, a hajón felejtettem a pénzt. Mindjárt hozom!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", Szeretném megvitatni a selyemkészletek növelésének lehetôségét.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "Elhoztam a dublonjaidat, Mijnheer "+npchar.name+". Kérlek, fogadd el ôket.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("600 dublont adtál.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Öröm veled üzletelni, kapitány. A selymet a hajójára szállítjuk a hosszúhajón keresztül.";
			link.l1 = "Köszönjük!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "Remélem, hamarosan találkozunk. Gyere vissza máskor is.";
			link.l1 = "Persze. Viszlát!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Nagyra értékelem az üzleti hozzáállásodat és hajlandó vagyok megfontolni a kérésedet. Talán növelhetnénk a mennyiséget, mondjuk, ötszörösére. Azonban az ilyen ellátmányok megszervezése jelentôs erôforrásokat igényel. Bôvítenünk kell a raktárhelyiséget, megerôsíteni a biztonságot, és biztosítani a megbízható szállítási útvonalakat. Mivel ez önöknek is elônyös, javaslom, hogy osszuk meg ezeket a kiadásokat egymás között.";
				link.l1 = "Ez mind ésszerûnek hangzik. Mekkora összeget tart szükségesnek ezeknek a kiadásoknak a fedezéséhez?";
				link.l1.go = "UpgradeSilk_1";
				Notification_Skill(true, 60, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Megértem, hogy érdekel a készletek növelése, azonban ebben a szakaszban nehezen tudok belemenni ilyen változtatásokba. Nem vonom kétségbe a fejlôdésre való törekvését, de egy ilyen ügylethez sokkal több tapasztalatra van szükség a kereskedelmi ügyekben és a saját tetteiben való bizalomra. Javaslom, hogy gyarapítsa tudását a tárgyalás mûvészetében, majd térjen vissza hozzám egy konkrétabb javaslattal. Ha készen áll, örömmel megerôsítem együttmûködésünket.";
				link.l1 = "Hmm... Rendben. Késôbb visszatérek erre a beszélgetésre.";
				link.l1.go = "exit";
				notification("Képességpróba Sikertelen (80)", SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Figyelembe véve az összes árnyalatot, a te részed a költségekbôl háromezer arany dublont fog kitenni. Ez a pénz lehetôvé teszi számunkra, hogy késedelem nélkül megszervezzük a szükséges intézkedéseket.";
			link.l1 = "Mijnheer "+npchar.name+", háromezer dublont? Ez valami vicc? Én egy becsületes ajánlattal jöttem hozzád, és azt akarod, hogy ilyen túlzó összeget fizessek a kellékek szervezéséért?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Kérem, hogy értsen meg engem helyesen. Nem próbálom becsapni önt. Ez a pénz az az összeg, amely lehetôvé teszi számunkra, hogy megfelelô rendet biztosítsunk az ellátmányok megszervezésében. Nemcsak a raktárak bôvítésérôl és a biztonságról van szó, hanem arról is, hogy garantáljuk az áruk késedelem és veszteségek nélküli szállítását, az üzlet minden kiszámíthatatlansága ellenére. Ezek az ilyen volumeneknél szokásos kiadások. A végén a befektetései igazolni fogják magukat, és Ön megfelelô állapotban és idôben megkapja az árut.";
			link.l1 = "A magyarázataid némileg megnyugtatóak, mijnheer. De ez az összeg még mindig túl magas. Kész vagyok beleegyezni a feltételeibe, ha legalább két és fél ezer dublonnára csökkenti az árat. Biztos vagyok benne, hogy ez elegendô lesz az ellátmány megszervezésére és az összes biztonsági intézkedés betartására.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Megértem, hogy az összeg nagy, de mint már mondtam, szükséges a munka megfelelô elvégzéséhez. Nem tudom csökkenteni, mert ez veszélyeztetné minden erôfeszítésünket. Azonban, hogy ne érezzék magukat becsapva, kész vagyok tizenöt százalékos kedvezményt adni minden jövôbeli ellátmányra. Ez, remélem, lehetôvé teszi önöknek, hogy kompenzálják a kiadásokat.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, a tizenöt százalékos kedvezmény természetesen elôrelépés. Rendben. Kész vagyok elfogadni az ajánlatát, még ha az ár rendkívül magasnak is tûnik számomra. Remélem, hogy az együttmûködésünk megfelel majd az elvárásaimnak. Itt a pénze.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", az ajánlata nem hagy más választást. Legyen háromezer dublon, bár ez jelentôs összeg. Azonban most nem tudok mindent egyszerre kifizetni. Visszatérek, amint megkapom a pénzt.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Tizenöt százalék kedvezmény? Mijnheer "+npchar.name+", nem erre számítottam. Ez az összeg nem csak költség, hanem egyenesen és szemenszedett rablás! De nem áll szándékomban megszakítani az üzleti kapcsolatokat önnel. Visszatérünk a korábbi feltételekhez - 30 tekercs selyem, darabonként 20 dublonnal.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Örülök, hogy egyetértettél, "+pchar.name+". Most a részleteket illetôen: 150 tekercs selyem 17 dublonnáért darabonként. Összesen - 2550 dublon az egész tételre. Az árut a szokásos módon veheted át - minden hónap 1-jén és 15-én. Úgy gondolom, hogy ez az üzlet mindkét félnek jó hasznot fog hozni.";
			link.l1 = "Nagyszerû! Ez egy már jó teríték. Szép napot, minhér. Viszlát hamarosan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "Ez csak egy üzleti megközelítés, nem rablás, ahogyan az önök számára tûnhetett. De, ahogy kívánod. Jöjjön el, mint mindig, 1. és 15-én, egy adag selyemért, szívesen kötök új üzletet.";
			link.l1 = "Természetesen, mijnheer. Viszlát.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Örülök, hogy jól döntött. Amint elhozod a pénzt, megbeszéljük az üzlet minden részletét, és folytatjuk a megvalósítást.";
			link.l1 = "Viszlát, Mijnheer "+npchar.name+". Találkozunk, amint összegyûjtöttem a szükséges összeget.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
