// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz...",
                          "További kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Monsieur, munkát keresek. Van valami munkája?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "Már teljesítettem a megbízását. A hosszúhajót a rummal a Le Francois öbölbe szállítottuk és átadtuk az embereinek.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "Ki szeretném bérelni az egyik szobáját két-három napra. Van egy sebesült emberem a fedélzeten. Pihenésre és gyógyulásra van szüksége.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Mondja csak. A barátom, akinek szobát béreltem, elment már? Megígérte, hogy vár rám, de a szoba üres.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Megyek, rendezek egy partit az embereimnek. Gondolom, már tudsz róla.";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Mindent elhoztam, ami az ünnepséghez szükséges.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "Egy feladat? Hm... Úgy nézel ki, mint akinek van esze, fiú. Talán van valamim a számodra\nEz a munka könnyûnek hangzik, de felelôsségteljes és okos munkát igényel. Nem bízhatom ezekre az idiótákra az üzletet, biztos, hogy tönkreteszik...";
			link.l1 = "Figyelj, megmondanád, hogy mi a fenét akarsz rám bízni? Esküszöm, nem hagyom cserben, vagy legalábbis megteszek minden tôlem telhetôt.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Az öreg Thomas belefáradt a sörre várakozásba.";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "A deszkák és az oakum reggelre itt lesznek.";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Ne várd meg a déli szelet.";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "Az öböl készen áll a partraszállásra";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "A tevék északra mennek.";
				break;
			}
			dialog.text = "Jól van. Szükségem van valakire, aki több láda finom jamaicai rumot szállít a kocsmámba. A helyzet a következô: az importvámok csökkentik az árrésemet, és a legjobb vendégeim szomjasak, ezért okosan kell cselekednünk, hogy elkerüljük a vámosokat. A lugger 'Ghost' ma este érkezik meg Martinique partjaihoz\nA Lamanten-öböltôl nem messze horgonyt vetnek. Meg kell találnod ezt a hajót, és fel kell szállnod a fedélzetére. Adok neked egy hosszú csónakot és öt matrózt, ôk követni fogják a parancsaidat\nAmint a fedélzetre értél, egy férfi fog közeledni hozzád. Egy jelszót kell neki mondanod: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nA válasz a következô lesz 'Miért nem iszol egy rumot, tengerész?'. Csak egy próbálkozásod lesz, úgyhogy írd le, és ne hibázz, különben az üzletnek annyi. Ezért nem bízhatom azokra az agyatlan idiótákra, akik veled hajóznak majd. Ismételd meg a jelszót.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Remek. Ismételd el magadban még néhányszor, vagy ami még jobb, írd le valahova. Miután megemlítetted a jelszót a lugger kapitányának, a rumos üvegekkel teli ládákat felpakolják a hosszúhajóra, amivel aztán el kell hajóznod a Le Francois nevû kalóztelepülés öbléhez - ott fogadnak majd téged.\nEz az egész feladat. A Le Francois öbölbôl gyalogosan juthatsz el Saint Pierre-be - a hosszúhajó az öbölben marad. Ötezer nyolcezret fizetek, ha ez megvan.";
			link.l1 = "A csempészet izgalmasan és jövedelmezôen hangzik. Megteszem, amit mondott. Hol van a hosszú csónak?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "Tehát azt javaslod, hogy kezdjek el csempészni? Hm... Tudja, nem kockáztathatom a nevemet. Bocsásson meg, úgy teszünk, mintha nem hallottam volna semmit.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Ahogy óhajtja, monsieur. Nincs más munkám.";
			link.l1 = "Értem. Akkor minden jót, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "A hosszúhajó este hétkor a mólónál lesz. A hosszúhajó legénysége képzett, így gyorsan elérheti a luggert. Az egész feladat nem tart tovább négy óránál - biztos vagyok benne, hogy este tizenegyre visszaér Saint Pierre-be. Fogd ezt a távcsövet, ez egy szemét, de jobb, mint a semmi. A Lamanten Beach a sziget északi részén található, ezért a kikötôt elhagyva tartsátok az irányt észak felé. Sok szerencsét!";
			link.l1 = "Rendben, értem. Hamarosan találkozunk, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("Kaptál egy távcsövet");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("Kaptál egy térképet Martinique-ról");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Nyisd meg a leltáradat (F1) és vedd fel a távcsövet.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Csodálatos! Tudom, hogy számíthatok rád. Nehéz volt?";
			link.l1 = "Nos, ez attól függ, hogy hogyan definiálod a nehézséget...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Nos, itt a jutalmad: ötezer pezó. A távcsövet megtarthatod. És még egy kis ajándék, kérem, vigye ezt a három üveg rumot. Miután megkóstolta, meg fogja érteni, miért van rá akkora kereslet.";
			link.l1 = "Köszönöm! Jó volt önnel dolgozni! Viszlát késôbb!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "Semmi gond, van egy szobám. 50 pezóért a tiéd három napra.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Tessék, tessék.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Elmegyek a pénzért a pénztároshoz, és visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Nem mondanám, hogy egyedül állt fel és hagyta el a szobát, monsieur. Tegnap járt erre néhány ember. Az egyikük egy félszemû, magas, vaskos férfi volt - a kinézete alapján nyilvánvalóan bandita, és egy lisztes férfi is, aki úgy nézett ki, mint egy kasztíliai. Én csak meglepôdtem, de az a lisztes úgy nézett rám... mint egy tetûre a verés elôtt. És akkor kérdeztek a barátodról... és én elmondtam nekik. Mi mást tehettem volna?";
			link.l1 = "Tudom, " + npchar.name + ", nem vagy hôs, ez igaz. Mit láttál még? Hová mentek?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Ez minden... várj, ne! Várj, a félszemû mondott valamit egy szekérrôl. Gondolom, fogtak egy szekeret, és átvonszolták a barátodat a sziget másik oldalára. Ez minden, monsieur, esküszöm... Hívnám az ôrséget, de az a selyemfiú azt mondta, hogy van egy gyönyörû feleségem, mielôtt elment volna... Látja? Ha rájönnek, hogy mindezt elmondtam neked, akkor...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Ne félj, a golyókon kívül semmit sem fognak hallani tôlem. Nagyon sokat segítettél nekem, köszönöm. Tessék, itt van 1000 pezó jutalomként.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "Nem sok, de azért köszönöm. Legközelebb hívd az ôrséget, és ne légy ilyen nyápic.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Köszönöm, uram. Szavamat adom, hogy a barátja már majdnem felépült. Legalábbis egyedül sétált. És az az egy ember, az a csendes holland, abban a pillanatban jött be kintrôl, látta azt a nagy rendetlenséget, és visszaugrott kifelé, csak úgy eltûnt utána.";
			link.l1 = "Azt mondanám, hogy már el is indult az elsô hajóval, amivel el tudott menni. Köszönöm az információt, ideje mennem.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Nem minden ember lehet hôs a kardját kitárt karddal, kapitány.";
			link.l1 = "Nos... ez az ember döntése.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Igen, a segéded beugrott, de mondtam neki, és megismétlem neked is - szoktam hozzá a részeg matrózok tömegéhez, de én hogy mennek a partik. Ami megmarad, az úgy fog kinézni, mint Antwerpen, miután a spanyol terciosok megjöttek. Örülnék, ha a falak még állnának. Szóval, ha a tömegeket akarod feldúlni, akkor szükségem lesz egy vissza nem térítendô elôlegre azon felül, amit már elhoztál. Úgymond a következmények esetére.";
			link.l1 = "Te ravasz róka! Én magam is évek óta iszom a tengeri kutyákkal, jártam már különbözô... vendéglátóhelyeken, és tudom, hogy a hozott pénzért az alapoktól kezdve újjáépíthetnénk a kocsmádat! Kihasználva a lehetôséget, mi? Rendben, esküvôm van, és nincs kedvem ilyen apróságokkal bajlódni - mennyit kérsz?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Még nyolcezer darab elég lesz, és ne aggódj - mindent a lehetô legjobban fogok csinálni. A fiaid sokáig emlékezni fognak erre a bulira, ne feledd a szavamat!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Tényleg meg kell próbálnod - ez egy különleges alkalom, érted. És igen, az ünnepség után ne gyere hozzám panasszal, még akkor se, ha leég a kocsmád.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "Már most úgy tûnik, mintha egy királyi esküvôt szerveznék! Várj, hamarosan visszajövök.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "A fiaid sokáig emlékezni fognak erre a mulatságra, ne feledd a szavamat!";
			link.l1 = "Tényleg meg kell próbálnod - ez egy különleges alkalom, érted. Ne gyere sírva hozzám, ha a fiaim véletlenül felgyújtják a kocsmádat.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
