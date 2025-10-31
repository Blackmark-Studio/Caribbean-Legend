// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
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
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Üdvözletem, kapitány! Van egy üzleti ajánlatom, amit nagyon érdekesnek fog találni.";
			link.l1 = "Menjen, uram.";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "Szeretném felbérelni a hajóját egy szállításra Guadeloupe-ból a spanyol fôszigetre.";
			link.l1 = "Utasként akar oda hajózni?";
			link.l1.go = "citizen_2";
			link.l2 = "A spanyol main? Kihagyom. Nem igazán vagyunk barátok a spanyolokkal. Azt javaslom, keressen egy másik bolondot.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Ahogy mondja, kapitány, bár ez nem egy nagy kockázatú út. Viszontlátásra.";
			link.l1 = "Ég veled!";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Ahogy óhajtja, kapitány. Viszontlátásra!";
			link.l1 = "Ég veled!";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Nem egészen, uram. Az utas a kapitány akaratától függô ember. Azért akarom felbérelni önt, a legénységét és a hajóját, hogy két barátommal együtt Panamába jussak.";
			link.l1 = "Panamába? Hogyan? Körbe akarja hajózni az egész kontinenst?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Ha-ha-ha-ha! Jó vicc, kapitány. Persze, hogy nem. Csak annyit kell tennie, hogy elvisz minket a Mosquitoes Bay-be, ami nincs messze Portobellótól. Panamába magunktól is eljutunk, nem ez lesz az elsô túránk a dzsungelben.";
			link.l1 = "Mi a helyzet a fizetséggel?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Két láda dublon. Háromszáz darab. Az egyiket elôre megkapod, amint a fedélzeten leszünk. A második láda a tiéd lesz, amint elérjük a célállomásunkat.";
			link.l1 = "Komoly jutalom egy ilyen könnyû munkáért. Mi a csapda, jóember?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Kapitány, az idô pénz, a barátaimnak és nekem nincs. Ma este el kell indulnunk innen, és tíz napon belül ott kell lennünk. Ez lesz a második félévünk. Szóval, benne vagy?";
			link.l1 = "Áll az alku!";
			link.l1.go = "citizen_6";
			link.l2 = "Sajnálom, uram, de az ajánlata túl gyanúsan hangzik nekem. Keressen magának egy másik bolondot.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Pompás. A barátaim jelenleg a dzsungelben vannak, majd értesítem ôket a megállapodásunkról. Ma este tízkor a Capster Beach-en találnak minket. Ne késsen, kapitány!";
			link.l1 = "Rendben. Capster Beach, ma este tízkor.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Egy pillanat, kapitány, még be sem mutatkoztunk egymásnak. A nevem Bertrand Pinette. Ön pedig...";
			link.l1 = ""+GetFullName(pchar)+". Kapitány "+GetFullName(pchar)+". Viszlát, monsieur Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Kapitány "+GetFullName(pchar)+", tessék. Mehetünk?";
			link.l1 = "Igen. Üdvözöljük a fedélzeten.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Rendben. Elfogadom az elôleget - egy láda tele dublonnal. És ne feledjétek - csak tíz napotok van, hogy eljuttassatok minket a célunkhoz. Egy nappal sem tovább!";
			link.l1 = "Emlékszem a feltételekre. Ne aggódj, idôben odaérünk. Foglaljatok helyet.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("Kaptál egy ládát tele dublonnal.");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Szóval, kapitány, teljes mértékben teljesítette az alku részét. Most én jövök. Fogadja el ezt a ládát a legmélyebb hálánkkal együtt.";
			link.l1 = "Öröm önnel üzletelni, monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("Kaptál egy ládát tele dublonnal.");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Hasonlóképpen. Viszlát, kapitány "+GetFullName(pchar)+".";
			link.l1 = "Ég veled!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "Szóval, kapitány, itt vagyunk. Ön csak az alku felét teljesítette, így én is ezt fogom tenni. Tartsa meg az elôlegét teljes fizetségként. Remélem, nem fog ellenkezni, végül is a maga hibája volt.";
			link.l1 = "Nem mondhatom, hogy ez tetszik, de elismerem, hogy igaza van. Most már elválnak útjaink.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "Mindenesetre köszönöm a szolgálatot, kapitány "+GetFullName(pchar)+". Viszontlátásra!";
			link.l1 = "Ég veled!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Ó, micsoda találkozó! "+TimeGreeting()+", "+GetFullName(pchar)+"! De hogyan?";
			link.l1 = TimeGreeting()+", Pinette úr. Nem volt könnyû megtalálni önt.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "És mi az oka, kapitány úr?";
			link.l1 = "Jó uram, van itt egy ember, akit "+GetFullName(sld)+" hívnak, és nagyon szeretné látni önt. Gondolom, tudja, miért.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Természetesen igen, de önnek, kedves kapitányom, azt is tudnia kell, hogy egyáltalán nem kíváncsi vagyok monsieur "+GetFullName(sld)+" . Maga a fejvadásza? Egyszerûen nem értem.";
			link.l1 = "Sajnos, de jelenleg ilyen vagyok, és nem örülök neki. Hibát követtem el, és most monsieur "+GetFullName(sld)+", a fenébe is, választás elé állított. Vagy a dicsôséges visszatérésed Guadeloupe-ra, vagy az én seggem, mint cinkos a kis vállalkozásodban, don Carlos de Milyar kiszabadításában. Ez fájni fog nekem, ezt te is tudod.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Á, az a szemétláda! Ez egy nagyon bûnös módja az emberek zsarolásának!... Szóval, kapitány úr, mi lesz, döntést hoz, vagy hagyja, hogy egy ilyen ember zsarolja magát?";
			link.l1 = "És mit gondolsz? Azt hiszem, velem jön Basse-Terre-be.";
			link.l1.go = "citizen_19";
			link.l2 = "Van választásom?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Ó, csalódást kell okoznom, kapitány. Nem kívánok felszállni a gyönyörû hajójára. Erôszakkal itt semmit sem fog elérni, a helyet ôrök veszik körül, és segítségért kiáltok, ha erôszakos szándékot mutatna. Persze, megpróbálhatsz leszúrni, de jó barátunk nem fog érméket kapni egy kihûlt hullától. Szóval, a legokosabb megoldás számodra ebben a pillanatban - az, ha békén hagysz. Megengedem, hogy sértetlenül távozhass.";
			link.l1 = "Tényleg azt hiszed, hogy a történtek után csak úgy elsétálok? Te rángattál bele ebbe a mocsokba, te szemétláda, ideje fizetni!";
			link.l1.go = "citizen_20";
			link.l2 = "Azt hiszem, igazad van. Tetszik az ötlet, hogy leszúrjalak, de értelmetlen. Meg se próbálj reménykedni, hogy ez lesz a vége. Most indulok Basse-Terre-be, ahol tájékoztatom jó barátunkat a hollétedrôl. Aztán álarcos embereket fog utánad küldeni.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ah! Katonák! Segítség!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "De persze. Mondd meg a fônöködnek, hogy tartsa kordában az álarcos embereit - kezdek nagyon népszerû lenni mostanában. Viszlát, kapitány.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "Várj! Megadom magam! Megadom magam!";
			link.l1 = "Megadom magam! Most pedig dobja el a fegyvert és menjen a hajóhoz!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "Mindig van választás, kapitány. Ha jól értem, nem vadásznál rám, ha nem fenyegetne az a bankár?";
			link.l1 = "Pontosan.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Jól van. Akkor szervezek neked egy szilárd módszert, hogy befogd a száját. Írjunk egy levelet, amit elviszel a munkaadódnak. Mondd meg neki, hogy ha valaha is beszélni kezd, Guadeloupe kormányzója megtudja, ki tervezte meg és fektetett be a Courage eltûnésébe - egy futárszállító hajó, amelynek feladata egy nagy tétel gyémánt szállítása volt.";
			link.l1 = "Hm. Azt hiszem, kezdem érteni, monsieur Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Örülök, hogy ilyen okos, kapitány. De Lion személyesen fogja a város kapujához szögezni a sunyi csirkefogó fejét, ha megtudja az igazságot a Courage eltûnése mögött. Ebben a levélben, amelyet most írok, olyan bizonyítékokat fog találni, amelyek megnyugtatják a zsarolót. Adjatok egy percet, hogy elôvegyem a tollamat.";
			link.l1 = "Rendben...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(írás) Tessék, vedd el. Két hasonló levél van ebben a csomagban. Az egyiket add oda a bankárnak, hadd élvezze. A másikat tartsd meg magadnak, és rejtsd el.";
			link.l1 = " Megbízható az információ?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "Esküszöm, hogy ön segített nekem, és most én is segíteni fogok önnek. Biztos lehet benne, hogy a zsaroló békén hagyja önt, amint elolvassa ezt a végrendeletet. Ah, igen... Még egy dolog, kapitány. Mivel ezt békésen rendeztük... Van egy rejtekhelyem, és elmondom, hol találja, ha megígéri, hogy a jövôben távol tartja magát a mûveleteimtôl. Úgysem engedik, hogy valaha is Guadeloupe-ra tegyem a lábam.";
			link.l1 = "Ha a levél a szándékom szerint fog mûködni, akkor ezt mindenképpen megígérhetem.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "Akkor megegyeztünk. Keressétek meg a sziklák között a Guadeloupe-i barlangban. Hadd szolgáljon ez szerény kárpótlásul a fáradozásaiért. Sok szerencsét, kapitány.";
			link.l1 = "Magának is, monsieur Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "Üdvözlöm, monsieur! Ön a kapitány "+GetFullName(pchar)+", igaz?";
			link.l1 = "Igen, uram. Mit tehetek önért?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", a Basse-Terre bank tulajdonosa arra kéri, hogy minél hamarabb látogassa meg. Megparancsolta, hogy minden nap ellenôrizzem a kikötôi irodánkat, hogy az Ön érkezése ne maradjon el.";
			link.l1 = "Érdekes, és miért akar ennyire látni engem?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+" személyesen fogja elmondani, hogy miért. Remélem, hogy nem utasítja vissza a meghívását.";
			link.l1 = "Hm... Rendben. Ezek a bankárok hatalmas emberek, és sosem vesztegetik az idejüket kis halakra. Megyek és meglátogatom az urat, amilyen hamar csak lehet.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Köszönöm, kapitány. Viszontlátásra!";
			link.l1 = "Ég veled!";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh! Te szemétláda! Kizárt, hogy ez egy véletlen találkozó...";
			link.l1 = "Igaz, Jean... bocsánat, Juanra gondoltam. Lenyomoztalak. Most pedig megtennéd, hogy bemész a raktérbe? Fújd ki a gôzt, és beszélgetünk.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "Az alku rám esô részét teljesítettem. Most maga jön. Lôdd le, és tartsd észben a hazugság következményeit.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Bertrand Pinette-et Barbadoson találja, pontosabban a fô ültetvényen. Ott akarta folytatni a tevékenységét. Az ültetvény felügyelôje a barátja.";
			link.l1 = "Miféle mûveletekkel?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "Ugyanazokat, amiket Guadeloupe-on folytatott. Félig legális kereskedelem, csempészet, rabszolgák. Szerintem a rabszolga- és cukorkereskedelem a célja, miért költözött volna másképp egy ültetvényre?";
			link.l1 = "Értem. Vannak pártfogói az angol hatóságok között?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Gondolom. Furcsa egy alak. Mindig és mindenhol vannak barátai.";
			link.l1 = "Még valami?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Mint például? Ravasz és okos, mindig tud valamit, mindig van egy ász a kezében. Nem volt sok idôm többet megtudni róla.";
			link.l1 = "Megvan. Rendben, el kell hajózni Bridgetownba. Szabadon távozhat, don Juan. Eszébe se jusson figyelmeztetni Pinette-et. Ha nem találom ott, akkor megint a maga segge a tét.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "Sajnálom, haver. Semmi személyes. Túl sokat tudsz, ez a te bajod.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
