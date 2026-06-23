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
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Nie, to nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... A gdzie jest Molligan? Czyżby nie chciał zobaczyć się ze mną osobiście?";
				link.l1 = "Nasz biedny Paul ma gorączkę. Nie jest w nastroju do handlu. Jestem tutaj zamiast niego.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "Czego chcesz, panie?";
				link.l1 = "Jak mniemam, czekasz, aby kupić trochę żelazodrzewa?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Kto ci nagadał te bzdury, panie? Nie czekam ani na nikogo, ani na nic. Mój statek patroluje okoliczny teren na rozkaz gubernatora Willemstad. Więc, byłbyś tak uprzejmy opuścić mój statek, musisz się mylić.";
			link.l1 = "Hm... Rozumiem. Przepraszam za kłopot.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Czyż nie rozmawialiśmy już o tym, panie?";
			link.l1 = "Tak, tak. Już odchodzę i wsiadam na mój statek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "A kimżeś ty?";
			link.l1 = "Czy nie obchodzi cię, z kim handlujesz? Przywiozłem żelazne drewno na sprzedaż. Ile?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "Zgodnie z umową - czterdzieści dublonów za sztukę.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Przyjacielu, mieliśmy umowę z Molliganem. To jest dobra cena, lepszej nie znajdziesz. Więc nie zachowuj się jak chłop w sklepie. Ile masz żelaznego drewna?";
			link.l1 = ""+FindRussianQtyString(int(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = int(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Wspaniale. To więcej, niż się spodziewałem. Oto złoto. Jeśli zdobędziesz więcej żelaznego drewna, idź do tawerny w Saint Martin i porozmawiaj z... wiesz kim. On umówi nas na spotkanie. Widzę, że jesteś dużo lepszym partnerem niż ten idiota Molligan.";
				link.l1 = "Dobrze. Umowa stoi.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Dobrze. Oto złoto. Jeśli zdobędziesz więcej żelaznego drewna, idź do tawerny w Philipsburgu i porozmawiaj z... wiesz kim. On skontaktuje się ze mną. Widzę, że możemy robić z tobą interesy nie gorzej niż z tym idiotą Molliganem.";
				link.l1 = "Dobrze. Umowa stoi.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... Spodziewałem się czegoś więcej. Dobrze. Oto złoto. I powiedz Molliganowi, że następnym razem musi przynieść partię nie mniejszą niż sto sztuk.";
				link.l1 = "Dobrze. Powiem mu.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Żartujesz sobie ze mnie? Mieliśmy umowę z Molliganem, partia nie może być mniejsza niż pięćdziesiąt sztuk! Zjeżdżaj i nie wracaj, dopóki nie będziesz miał wystarczająco.";
			link.l1 = "Dobrze, dobrze, uspokój się.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = int(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = int((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "In addition, if I get ironwood, I will be able to sell it to Michael Rosencraft by having a meeting arranged with his man at the tavern in Philipsburg.");
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
			dialog.text = "O, mój stary przyjacielu! Masz do sprzedania trochę żelaznego drewna?";
			link.l1 = "Dokładnie, Michael. Handlujmy.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Ile masz? Potrzebuję partii nie mniejszej niż "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= int(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Wiem o tym. Mam "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  z żelaznego drzewa, które tak chętnie pragniesz zdobyć.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Niestety, nie mam aż tyle.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Cholera jasna, nie ostrzegli cię? A może szczury zjadły drewno? Potrzebuję "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value))+" i ani jednej sztuki mniej. Następnym razem przynieś mi tyle drewna, ile powie ci mój agent. Mam nadzieję, że mnie znów nie zawiedziesz, bo inaczej będę musiał odmówić twoich usług.";
				link.l1 = "Dobrze, Mynheer, będę bardziej uważny w przyszłości.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (int(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Robisz mnie w konia po raz drugi. Nie podoba mi się to. Wiedz, że to jest ostatnie ostrzeżenie, następnym razem odmówię twoich usług.";
					link.l1 = "Przeklęte szczury uszkodziły moje towary! Obiecuję ci, Michale, że to był ostatni raz.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "A teraz moja cierpliwość się wyczerpała! Nie chcę już robić z tobą interesów. Zjeżdżaj i zapomnij o mnie.";
					link.l1 = "Ale Mynheer...";
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
			else npchar.quest.bakaut_angry = int(npchar.quest.bakaut_angry)+1;
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
			if (iTemp > int(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "O rany! Przykro mi, przyjacielu, ale mogę kupić tylko "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value)+20)+", nie mam pieniędzy na cały twój ładunek. Spodziewałem się partii "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value))+" sztuk za czterdzieści dublonów każda...";
				link.l1 = "Dobrze. Weź "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value)+20)+" teraz, a resztę sprzedam ci następnym razem.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = int(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Bardzo dobrze. Cena jest zwyczajowa, czterdzieści dublonów za każdy kawałek.";
				link.l1 = "Działa dla mnie. Weź swoją partię.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Przyjemność robić z Tobą interesy. Przyjdź do mnie ponownie, jeśli chcesz sprzedać więcej żelaznego drewna.";
			link.l1 = "Do zobaczenia, panie. Nasza współpraca jest dla mnie bardzo opłacalna. Żegnaj!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = int(npchar.quest.bakaut);
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
