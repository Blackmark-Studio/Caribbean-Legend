void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ez egy bogár. Szólj a fejlesztôknek.";
			link.l1 = "Úgy lesz!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Hogyan, sápadtarcú. Látom, hogy te vagy a nagy kenu kapitánya. Én Kanauri. Én vagyok a Kajmánok fônöke - a hatalmas Arawak törzs. Beszélni akarok veled.";
			link.l1 = "Hallgatlak, fônök. Milyen gondok hoztak hozzám?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "Mit akarsz tôlem, te büdös, vörös bôrû majom? Menj vissza a dzsungeledbe, és ne zaklass engem a kéréseiddel.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! A fehér kapitányt nem nevelték udvariasságra? Ajánlatot tettem. Egy rakás wampumot kerestél, de most elmegyek. Viszlát, sápadtarcú.";
			link.l1 = "Menj, tûnj el...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "Fehér testvér, éleslátó, mint a bagoly, ravasz, mint a kígyó. Baj van az indiánokkal. Nagy-nagy kenu fehér emberekkel jön a falumba. Sok Kajmánt, az én népemet, felrakják a kenujukba, és elviszik ôket a Minden Vizek Anyjához...";
			link.l1 = "Várj... azt mondod, hogy a népedet fehér emberek rabszolgasorba taszították egy hajóról?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "Igazat beszélsz, fehér testvér. Tudom, hogy azok a sápadtarcúak nem a barátaid. Ezek a kegyetlen fehér emberek a spanyol törzsbôl. Elvették a népemet. De én megtalálom ôket. A spanyolok hajnaltól estig dolgoztatják az indiánokat, mélyen merülnek a vizek anyjába, kagylókat találnak, tele istenek könnyeivel.";
			link.l1 = "Gyöngybúvárkodás... Ez egy brutális munka.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "Igazat beszélsz, fehér testvér. Tudom, hogy azok az emberek nem a barátaid. Ôk az angol törzs tagjai. Elvették a népemet. De én megtalálom ôket. Az angolok hajnaltól estig dolgoztatják az indiánokat, mélyen a vizek anyjában merülnek, istenek könnyeivel teli kagylókat találnak.";
			link.l1 = "Gyöngybúvárkodás... Ez kemény munka.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Az indiánok megbetegednek és meghalnak a rabszolgaságban. A fehérek nem sajnálják az indiánokat. A fehérek törvénye az indiánok számára a korbács és a pisztoly. Én öreg vagyok. Nincs emberem a harchoz. Kajmán Arawak békés nép, mi találtuk ki a békepipát. Kérlek téged, fehér testvér, hogy vedd le a pálcát és a pisztolyt a gonosz fehérek ellen, és mentsd meg az indián arawakokat.";
			link.l1 = "Arra kérsz, hogy hadat üzenjek? Meg kell értened, fônök, az erôforrásaim korlátozottak.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "Ne menj a hadiösvényre. Szabad indián. Az én népem. Neked adjuk az istenek minden könnyét, ami a kenuinkon van. Öld meg a gonosz fehéret, segíts az indiánoknak, szerezd meg az istenek könnyeit, add el ôket sok-sok wampumért. Halom wampum";
			link.l1 = "Ah, most már értem. Nem, Canauri, nem tudok segíteni neked. Most nem tehetem - a hajóm javításra szorul, nincs több készletem...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "Ebben az esetben, örömmel teszem. Beszéljük meg a részleteket. Hol vannak az emberei? Azt mondta, hogy már megtalálta ôket...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! Tudok várni, fehér testvér... Még egy holdat maradok ebben a kikötôben, hogy megkeressem népem védelmezôjét. Itt megtalálsz, ha készen állsz.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "Visszajöttél, fehér testvér? Segítesz nekem megbüntetni a gonosz embereket és megmenteni az indiánokat?";
			link.l1 = "Készen állok, amennyire csak lehet.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "Még fel kell készülnöm.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "Itt leszek, fehér testvér.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "Nagyon örülök, hogy beleegyeztél, fehér testvér!";
			link.l1 = "Beszéljünk a részletekrôl, Canauri. Hol van a néped? Azt mondtad, hogy már megtaláltad ôket...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "A Carupano öbölben táboroznak, a Cumana nevû spanyol tábor közelében. Minden nap csónakkal hajóznak a tengeren, búvárkodnak, mélyen a vízben...";
				link.l1 = "Értem. És a spanyolok vigyáznak rájuk, amíg merülnek?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "A Perlas-foknál táboroznak, a Blueweld nevû angol tábor közelében. Minden nap csónakokon hajóznak a tengeren, merülnek a vízbe, mélyen a mélyben...";
				link.l1 = "Értem. És persze az angolok vigyáznak rájuk?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Igen, két nagy kenu sápadtarcú, tûzpálcákkal és nagy késekkel. Tábor a parton is ôrzik - indián nem tud megszökni.";
			link.l1 = "Miféle hajók? Le tudod írni ôket? Milyen nagyok? Milyen vitorlájuk van?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Ez a kenu nagy, de Canauri látott már nagyobbat is. Az elsô vitorla nagyon-nagyon ferde, három oldala ilyen. (Három lateen vitorlát és egy trapézvitorlát húz a koszba) Fölül keskeny, alul széles.";
			link.l1 = "Úgy hangzik és úgy néz ki, mint egy szkúner...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri nem ismeri ezt a szót. A sápadtarcúak nagyon óvatosak, ha meglátnak egy másik kenut - indiánok szállnak le, és megvárják, amíg a másik kenu elvitorlázik.";
			link.l1 = "Óvatos kurafiak... hogyan tudnék közel kerülni hozzájuk?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "Ha a sápadtarcú testvér kis kenuval megy, akkor a part közelébe tud lopakodni. Megmutatom az utat. De csak egy kis kenut vigyetek, különben a sápadtarcú kutya meglátja és a dzsungelbe kergeti az indiánokat a hajóról...";
			link.l1 = "Megvan. Szükségem lesz egy luggerre vagy egy sloopra ehhez a mûvelethez. Nagyszerû. Egy sloop két schooner ellen... Istenem... és én még azt hittem, hogy ez könnyû lesz!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Mehetünk, fehér testvér? Kevesebb, mint egy holdunk van.";
			link.l1 = "Igen, uram. Szállj fel a hajómra, fônök. Ne vesztegessük az idôt!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Köszönöm, fehér testvér! Megmentetted a Kajmán Arawak törzset! Nagy adóssággal tartozunk neked. Az út megszabadult a sápadtarcú kutyáktól, és az indiánok szabadon szaladgálhatnak a dzsungelben. Neked adjuk a hajókon maradt istenek könnyeit.";
			link.l1 = "Lássuk, mit tudsz...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("Örülök, hogy az istenek könnyei a tiéd, Arawak testvére!","Indián köszönöm, bátor sápadtarcú!","Fogd a fogásunkat, fehér testvér!");
			link.l1 = LinkRandPhrase("Örülök, hogy segíthetek!","Köszi, vörösbôrû testvér!","Nagyszerû!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Canauri köszönöm még egyszer, sápadtarcú testvér! Megmentetted az összes indián kenut! Canauri számára nagyon fontos az összes kenu megmentése, mert megmented Canauri unokáját is, akit a gonosz sápadtarcúak rabszolgasorba visznek. Gyermekként az unokám nagyon szeretett úszni, és Kanauri adta neki ezt a bûvös amulettet, hogy az unokám ne fulladjon meg. Most az unoka már nem akar úszni, és nekem adja az amulettet, hogy neked adhassam, sápadtarcú testvér. Remélem, hogy az istenek könnyei és ez az ajándék elegendô jutalom lesz Arawak életéért. És most elbúcsúzunk - itt az ideje, hogy visszatérjünk a szülôfalunkba.";
				link.l1 = "Sok szerencsét, Cunauri! Örülök, hogy az unokád túlélte! Imádkozom, hogy ez a gonoszság soha többé ne érjen titeket!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri még egyszer köszöni neked, sápadtarcú testvér! Remélem, hogy az istenek könnyei elég jutalom lesznek az indiánok életéért. Most pedig viszlát, megyünk az ôslakosok falujába.";
				link.l1 = "Sok szerencsét, Cunauri! Soha többé ne ess rabszolgasorba!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("Megkaptad a Keresô felsôbbségét.");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
