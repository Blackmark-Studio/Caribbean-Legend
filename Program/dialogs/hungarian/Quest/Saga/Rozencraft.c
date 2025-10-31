// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
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
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... És hol van Molligan? Nem ô maga akart látni engem?";
				link.l1 = "Szegény Paul lázas. Nincs kedve kereskedni. Én vagyok itt helyette.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "Mit akar, Mister?";
				link.l1 = "Gondolom, vasfát akar venni.";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Ki mondta ezt a baromságot, uram? Nem várok senkire vagy semmire. A hajóm a willemstadi kormányzó parancsára járôrözik a környéken. Szóval, lenne olyan kedves elhagyni a hajómat, biztos téved.";
			link.l1 = "Hm... Értem. Elnézést a zavarásért.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Nem beszéltünk már errôl, uram?";
			link.l1 = "De, de. Elmegyek, és már a hajómra szállok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "És maga kicsoda?";
			link.l1 = "Nem érdekli, hogy kivel kereskedik? Vasfát hoztam eladni. Mennyit?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "A megállapodás szerint - negyven dublont darabonként.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Pajtás, megegyeztünk Molligan-nal. Ez egy jó ár, ennél jobbat nem fogsz találni. Szóval ne viselkedj úgy, mint egy paraszt a boltban. Mennyi vasfád van?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Nagyszerû. Ez több, mint amire számítottam. Tessék, fogd az aranyat. Ha lesz még vasfa, menj el a Saint Martin-i kocsmába és beszélj... tudod kivel. Ô majd összehoz nekünk egy találkozót. Látom, hogy sokkal jobb partner vagy, mint az az idióta Molligan.";
				link.l1 = "Jól van. Megegyeztünk.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Rendben. Tessék, fogd az aranyat. Ha még több vasfát szerzel, menj el a Philipsburgi kocsmába és beszélj... tudod kivel. Ô majd kapcsolatba lép velem. Úgy látom, hogy veled nem tudunk rosszabb üzletet kötni, mint azzal az idióta Molligannel.";
				link.l1 = "Jól van. Megegyeztünk.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... többre számítottam. Rendben. Tessék, fogd az aranyat. És mondd meg Molligan-nak, hogy legközelebb száz darabnál nem lehet kevesebbet hozni.";
				link.l1 = "Rendben. Megmondom neki.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Most viccelsz velem? Megegyeztünk Molligan-nal, hogy a tétel nem lehet ötven darabnál kisebb! Tûnj el, és ne térj vissza, amíg nem lesz elég.";
			link.l1 = "Jól van, jól van, nyugodj meg.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "Ráadásul, ha vasfát szerzek, eladhatom Michael Rosencraftnak, ha megbeszélek egy találkozót az emberével a Philipsburgi kocsmában.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "Ó, öreg barátom! Van egy kis vasfád, amit eladnál?";
			link.l1 = "Pontosan, Michael. Cseréljünk.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Mennyi van nálad? Nem kisebb tételre van szükségem, mint "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Tudom. Van "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SANDAL))+"  vasfám, amit annyira szeretnél megszerezni.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Sajnos nincs ennyi pénzem.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "A fenébe is, nem figyelmeztettek? Vagy a patkányok megették a fát? Nekem a "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" kell, és nem egy darabbal kevesebb. Legközelebb annyi fát hozzon, amennyit az ügynököm mond. Remélem, hogy nem fog még egyszer csalódást okozni, különben kénytelen leszek visszautasítani a szolgáltatásait.";
				link.l1 = "Rendben, Mynheer, a jövôben figyelmesebb leszek.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Másodszorra is átver engem. Nem tetszik ez nekem. Tudd, hogy ez az utolsó figyelmeztetés, legközelebb visszautasítom a szolgáltatásaidat.";
					link.l1 = "Átkozott patkányok megrongálták az árumat! Megígérem, Michael, hogy ez volt az utolsó alkalom.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "És most elfogyott a türelmem! Nem akarok többé üzletet kötni veled. Tûnj el, és felejts el engem!";
					link.l1 = "De Mynheer...";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Hûha! Sajnálom, barátom, de csak "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+"tudok vásárolni, nincs pénzem az összes rakományodra. Egy tétel "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" darabot vártam, darabonként negyven dublonnal...";
				link.l1 = "Jól van. Vegye el a "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" most, a többit pedig legközelebb eladom.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Rendben. Az ár a szokásos, negyven dublon darabonként.";
				link.l1 = "Nekem megfelel. Vigyétek a szállítmányt.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Öröm veled üzletelni. Jöjjön el hozzám újra, ha több vasfát akar eladni.";
			link.l1 = "Viszlát, uram. Az együttmûködésünk nagyon jövedelmezô számomra. Viszontlátásra!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
