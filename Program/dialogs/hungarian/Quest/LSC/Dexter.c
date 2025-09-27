// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mit akarsz, fiú? Beszélj a Cápával, ô itt a fônök.";
				link.l1 = "Legalább köszönhetek neked, vagy az szabályellenes?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Shark mondta, hogy van egy térképed a szigetrôl. Eladod?";
					link.l2.go = "map";
				}
				dialog.text = "A-ah, "+GetFullName(pchar)+"! Van valami dolgod velem, vagy csak megint beszélgetni akarsz? Ha igen, legközelebb hozz egy üveg rumot, ha-ha!";
				link.l1 = "Nem, nincs különösebb dolgom magával. Legközelebb hozok rumot, csak neked.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha! Te egy mókamester vagy, ugye fiú? Jól van... A nevem Layton Dexter, én vagyok Shark második embere, és mostanában én vagyok a helyettese ebben az átkozott Elhagyott Hajók Városában. Közben ellátmányt árulok, és megpróbálok pénzt kicsikarni abból a semmirekellô Fazióból.";
			link.l1 = "A nevem pedig "+GetFullName(pchar)+". Örülök, hogy megismerhetlek!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Gondolom, már hallottad, hogy Steven meghalt. A narválok tették.";
			link.l1 = "Igazad van, tudom, hogy... És most mi van, te vagy az admirális?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Pontosan. Chad átállt a Narwhalshoz, Steven meghalt, és így - mivel én vagyok a második számú parancsnok, természetesen én vagyok most az admirális. Ellenvetés?";
			link.l1 = "Nem. Nincs ellenvetés.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Nem, nincs ellenvetés. Halljuk a kérdéseiteket.";
			link.l1 = "Bosszút akar állni a Narwhalokon Steven haláláért?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "Úgy érted, hogy akkor hadat üzenek? Nem. Vannak jobb módszerek is, hogy megfizettessük velük. Elôször is megháromszorozom az árat, amit az ellátásért fizetnek\nHa megtámadják a 'San Augustinust' , pokollá tesszük ôket. Aztán tárgyalni fogok a rivadókkal. Persze, nem bízhatunk azokban a mocskos niggerekben, és haragszanak ránk a varázslójuk halála miatt, de minden problémát el lehet simítani rummal és kajával.";
			link.l1 = "Értem. Rendben, Layton, mennem kell...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Várj. Steven azt mondta, hogy valahogy el akarod hagyni az Elhagyott Hajók Városát, és egy hajón akarsz visszajönni ide?";
			link.l1 = "Ez a terv.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Vegyük ezeket a vitorlázási irányokat. Ezek segítségével egy darabban vissza tudsz jutni ide a tengeren. Azaz: nem fogsz zátonyra futni, nem sodor el a sodrás, és a hajód nem fog a külsô peremen lévô többi roncsra zuhanni\nHa nem használod ôket, vagy nem találsz átjárót, vagy a hajód itt csatlakozik a testvérekhez. Ne feledd, hogy a zátonyokon való áthaladáshoz kis merülésû, sekély merülésû hajót kell használnod. Lugger, schooner, brigantine, brigg... semmi, ami nagyobb egy negyedosztályúnál. Megértettétek?";
			link.l1 = "Igen, értem. Köszönöm! Pontosan erre van szükségem.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Ne felejtsétek el megtölteni a rakteret élelemmel. Jó áron eladom neked. Ne mutasd meg ezt a dokumentumot senkinek, a bázisunknak titokban kell maradnia. Csak azért adom át neked ezt a dokumentumot, mert maga Steven akarta átadni neked, és te Jan Svenson barátja vagy.";
			link.l1 = "Emiatt ne aggódjon. Még egyszer köszönöm, és még találkozunk!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "Van valami elôrelépés az elhagyott hajók városából való menekülésben, "+pchar.name+"?";
			link.l1 = "Még nincs elôrelépés, Layton. Dolgozom rajta.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "Tessék, "+pchar.name+". Néhány dolgot szeretnék megbeszélni veled.";
			link.l1 = "Ha jól értettem, te vetted át Steven helyét a halála után. Szóval most már te vagy az admirális?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Pontosan. Mivel én vagyok a második számú parancsnok, most én vagyok az admirális. Ellenvetés?";
			link.l1 = "Nincs ellenvetés. Minden joga megvan, hogy megtartsa ezt a pozíciót.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Örülök, hogy megértjük egymást. Szóljon, ha bármire szüksége van.";
			link.l1 = "Bosszút akar állni a Narwhalokon Steven haláláért?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "Úgy érted, hogy akkor hadat üzenek? Nem. Vannak jobb módszerek is, hogy megfizettessük velük. Megháromszorozom az árat, amit az ellátásért fizetnek\nHa megtámadják 'San Augustine', , pokollá tesszük ôket. Emellett most már jó kapcsolataink vannak a Rivadókkal, úgyhogy a Narwhals nem fog kockáztatni semmit, hogy ostobán viselkedjen.";
			link.l1 = "Értem. Akarsz még valamit mondani? Vagy már mehetek is?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Én igen. Csak egy módot látok arra, hogy megszerezzük a narválokat. Nem tökéletes, de nem látok más alternatívát. Két irányból fogjuk megtámadni ôket. Egy csapat merész vágtázó hosszúhajón a 'Ceres Smithy', fedélzetére száll, míg egy második csoport a Rivadókkal együtt megrohamozza a 'Esmeralda'. Ez vagy teljesen kiiktatja ôket, vagy arra készteti ôket, hogy a 'San Gabriel felé meneküljenek. A második forgatókönyv a legvalószínûbb, San Gabriel egy erôsen megerôsített állás, és ostromlása sokáig tart. De akárhogy is, mi fogunk gyôzni.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "Várjuk a Donald Greenspennel folytatott beszélgetésed eredményét. Ez egy nagyon fontos ügy, úgyhogy ne vesztegessük az idôt.";
			link.l1 = "Már úton vagyok!";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Igen, megvan a térkép. Szeretné megvenni? Szívesen, ha szeretné. Kétszáz dublonnáért a tiéd lehet.";
			link.l1 = "Mit szólna egy pezóhoz?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "Nem. Aranyat akarok. Nem alkudozom.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Rendben. Vigye az aranyat, beleegyezem.";
				link.l1.go = "map_2";
			}
			link.l2 = "Nincs annyi aranyam. Talán késôbb...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveDublonsFromPCharTotal(200);
			PlaySound("interface\important_item.wav");
			Log_Info("Kaptál egy térképet az elhagyott hajók városáról.");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Szép üzlet, fiú! Vidd a térképedet. Megéri az árát - egy egész héten át másztam a városban, hogy lerajzoljam, így tulajdonképpen elég olcsón adtam el neked.";
			link.l1 = "Olcsón?! Persze. Azért köszönöm.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Állj meg, haver! Igen, Sharknak igaza volt, ez a fickó megôrült. Annyi ember halt meg miatta... Láncoljátok meg, fiúk, és dobjátok a raktárba!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steven engem tett meg helyette a város admirálisává - úgy veszem, hogy együtt mennek vissza a Karib-tengerre. Én itt maradok és folytatom az üzletet, én és Steven nem szívesen veszítünk el egy ilyen nagyszerû bázist. És szeretném elmondani, hogy mindig szívesen látott vendég leszel itt.";
			link.l1 = "Köszönöm, Layton. Azt hiszem, gyakran fogok visszatérni a szigetedre.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "Á, régi barátom "+GetFullName(pchar)+"! Sikerült megtalálnod az Elhagyott hajók városát Steven vitorlás útbaigazítása alapján, ugye? Nagyon, nagyon örülök, hogy látlak. Mindig szívesen látott vendég vagy itt.";
			link.l1 = "Köszönöm, Layton. Azt hiszem, gyakran fogok visszatérni a városodba.";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Rendben. Van eladó ételük? Kész vagyok megvenni tôled a szokásos ár duplájáért.";
			if (iTrade > 0)
			{
				link.l1 = "Igen, eladhatok némi élelmiszert.";
				link.l1.go = "trade";
			}
			link.l2 = "Sajnos, most nincs mit eladnom neked.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Kár. Ne felejtsen el legközelebb is hozni - jól megfizetem.";
			link.l1 = "Rendben. Megpróbálom nem elfelejteni...";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "Mennyibe kerül?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "A francba, te aztán részeg vagy, haver! Le vagyok nyûgözve! Menj és aludj egy kicsit, majd késôbb cserélünk.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "Még a seggemet sem emelem fel a székrôl egy ilyen pitiáner összegért. Hozz még!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "És hogyan fogsz hajózni a hajódon mindenféle ellátmány nélkül, pajtás? Azt akarod, hogy a fiaid éhezzenek? Tartsd meg legalább a "+FindRussianQtyString(GetCrewQuantity(pchar))+" magadnak.";
				link.l1 = "Hm, igazad van.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Hû, haver, ez már túl sok nekünk! Nem fogjuk tudni megenni, mielôtt megrohad. Most nem bírok többet, mint "+iTemp+".";
			 link.l1 = "Ahogy akarod.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? Rendben. Fizetek neked "+FindRussianMoneyString(iMoney)+". Megegyeztünk?";
			link.l1 = "Persze! Jó volt veled üzletelni!";
			link.l1.go = "trade_2";
			link.l2 = "Hm. Nem, meggondoltam magam.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Megegyeztünk. Fizetek neked "+FindRussianMoneyString(iMoney)+" az áruért. Elég lesz?";
			link.l1 = "Persze! Szép üzlet!";
			link.l1.go = "trade_4";
			link.l2 = "Hm. Nem, meggondoltam magam.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "A fenébe a szememmel! Tele van a raktáram! A következô fél évben nem kell ellátmányt vásárolnom.";
				link.l1 = "Jól van. Akkor hat hónap múlva hozom neked a következô adag élelmiszert.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Nagyszerû! Legközelebb többet hozz nekem.";
				link.l1 = "Persze!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Szép volt! A raktáram megtelt. A következô fél évben nem kell élelmiszert vásárolnom.";
				link.l1 = "Jól van. Akkor hat hónap múlva hozom neked a következô adag élelmiszert.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Nagyszerû! Legközelebb többet hozz nekem.";
				link.l1 = "Persze!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ah, "+GetFullName(pchar)+"! Örülök, hogy látlak! Mit szeretnél?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Akarsz venni tôlem némi élelmiszert?";
				link.l1.go = "trade";
			}
			link.l2 = "Semmiség, csak tudni akartam, hogy vagy.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
