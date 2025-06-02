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
				dialog.text = "Czego chcesz, chłopcze? Porozmawiaj z Rekinem, on tu rządzi.";
				link.l1 = "Czy mogę przynajmniej się przywitać, czy to wbrew zasadom?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Rekin powiedział mi, że masz mapę Wyspy. Czy sprzedajesz ją?";
					link.l2.go = "map";
				}
				dialog.text = "A-ach, "+GetFullName(pchar)+"! Masz do mnie interes, czy po prostu chcesz znów pogadać? Jeśli tak, to następnym razem przynieś butelkę rumu, ha-ha!";
				link.l1 = "Nie, nie mam dla ciebie żadnych szczególnych zleceń. Przyniosę rum następnym razem, tylko dla ciebie.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha! Jesteś żartownisiem, prawda, chłopcze? Dobrze... Nazywam się Layton Dexter, jestem zastępcą Rekina, a obecnie jego zastępcą w tym przeklętym Mieście Porzuconych Okrętów. W międzyczasie sprzedaję zapasy i próbuję wyciągnąć pieniądze od tego leniucha Fazio.";
			link.l1 = "I moje imię to "+GetFullName(pchar)+" Miło cię poznać!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Przypuszczam, że już słyszałeś, że Steven nie żyje. To sprawka Narwali.";
			link.l1 = "Masz rację, wiem o tym... Więc co, teraz jesteś admirałem?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Dokładnie. Chad przeszedł do Narwali, Steven nie żyje, a więc - ja, będąc drugim w dowództwie, naturalnie, jestem teraz admirałem. Sprzeciwy?";
			link.l1 = "Nie. Bez sprzeciwu.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Dobrze. Posłuchajmy twoich pytań.";
			link.l1 = "Czy zamierzasz zemścić się na Narwalach za śmierć Stevena?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "„Czy mam zamiar wypowiedzieć im wojnę? Nie. Są lepsze sposoby, żeby ich ukarać. Najpierw potroję cenę, jaką płacą za zaopatrzenie\nJeśli zaatakują 'San Augustine', damy im popalić. Potem zamierzam negocjować z Rivados. Oczywiście, nie można ufać tym brudnym czarnuchom i mają do nas urazę za śmierć ich czarownika, ale każdy problem można załagodzić rumem i jedzeniem.”";
			link.l1 = "Widzę. Dobrze, Layton, muszę iść...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Czekaj. Steven powiedział mi, że próbujesz opuścić Miasto Porzuconych Statków w jakiś sposób i wrócić tutaj na statku?";
			link.l1 = "To jest plan.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Weź te wskazówki żeglarskie. Dzięki nim możesz wrócić tutaj drogą morską w jednym kawałku. Znaczy to: nie rozbijesz się na rafach, prąd cię nie porwie, a twoja łajba nie roztrzaska się o inne wraki na zewnętrznym pierścieniu\nBez nich albo nie znajdziesz przejścia, albo twój statek dołączy do swoich sióstr tutaj. Pamiętaj, że musisz używać małej jednostki z płytkim zanurzeniem, aby przejść przez mielizny. Lugger, szkuner, brygantyna, bryg... nic większego niż czwarta klasa. Zrozumiano?";
			link.l1 = "Tak, robię. Dzięki! To jest dokładnie to, czego potrzebuję.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Nie zapomnij zaopatrzyć ładowni w prowiant. Sprzedam ci je po dobrej cenie. Nie pokazuj tego dokumentu nikomu, nasza baza musi pozostać w tajemnicy. Daję ci ten dokument tylko dlatego, że sam Steven miał ci go dać, a ty jesteś przyjacielem Jana Svensona.";
			link.l1 = "Nie martw się o to. Jeszcze raz dziękuję i do zobaczenia!";
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
			dialog.text = "Czy masz jakieś postępy w ucieczce z Miasta Porzuconych Statków, "+pchar.name+"?";
			link.l1 = "Jeszcze żadnych postępów, Layton. Pracuję nad tym.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "Oto jesteś, "+pchar.name+" Mam z tobą kilka spraw do omówienia.";
			link.l1 = "Z tego, co zrozumiałem, objąłeś stanowisko Stevena po jego śmierci. Czy jesteś teraz admirałem?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Dokładnie. Będąc drugim w dowodzeniu, jestem teraz admirałem. Sprzeciwy?";
			link.l1 = "Bez sprzeciwów. Masz pełne prawo zachować tę pozycję.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Cieszę się, że się rozumiemy. Daj mi znać, jeśli czegoś potrzebujesz.";
			link.l1 = "Czy zamierzasz zemścić się na Narwalach za śmierć Stevena?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "Chcesz powiedzieć, że wypowiem im wojnę? Nie. Są lepsze sposoby, by ich ukarać. Potroję cenę, którą płacą za zaopatrzenie.\nJeśli zaatakują 'San Augustine', damy im popalić. Poza tym, mamy teraz dobre relacje z Rivados, więc Narwale nie zaryzykują głupiego działania.";
			link.l1 = "Rozumiem. Czy chcesz mi powiedzieć coś jeszcze? Czy mogę już iść?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Wiem. Widzę tylko jeden sposób, abyśmy mogli dostać się do Narwali. Nie jest doskonały, ale nie widzę alternatywy. Zaatakujemy ich z dwóch kierunków. Grupa śmiałych opryszków na łodziach abordażowych zaatakuje 'Ceres Smithy', podczas gdy druga grupa wraz z Rivados szturmuje 'Esmeraldę'. To albo ich całkowicie wyeliminuje, albo zmusi do ucieczki na 'San Gabriel'. Drugi scenariusz jest najbardziej prawdopodobny, San Gabriel to silnie umocniona pozycja, a oblężenie jej zajmie dużo czasu. Ale w każdym razie, wygramy.";
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
			dialog.text = " Czekamy na wyniki twojej rozmowy z Donaldem Greenspenem. To bardzo ważna sprawa, więc nie trać czasu.";
			link.l1 = "Już idę!";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Tak, mam mapę. Chciałbyś ją kupić? Zapraszam, jeśli chcesz. Będzie Twoja za jedyne dwieście dublonów.";
			link.l1 = "A co powiesz na pesos?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "Nie. Chcę złota. Żadne targowanie się nie wchodzi w grę.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Dobrze. Weź swoje złoto, zgadzam się.";
				link.l1.go = "map_2";
			}
			link.l2 = "Nie mam tyle złota. Może później...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveItems(pchar, "gold_dublon", 200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Ładna transakcja, chłopcze! Weź swoją mapę. Jest warta swojej ceny - pełzałem po Mieście przez cały tydzień, aby ją narysować, więc właściwie sprzedałem ci ją dość tanio.";
			link.l1 = "Tanie?! Pewnie. No cóż, dziękuję mimo wszystko.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Stój tam, kamracie! Tak, Rekin miał rację, ten facet oszalał. Tylu ludzi zginęło przez niego... Zwiążcie go chłopcy i wrzućcie do ładowni!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steven uczynił mnie admirałem Miasta zamiast siebie - rozumiem, że ty i on wracacie razem na Karaiby. Ja zostanę tutaj i będę kontynuować interesy, ja i Steven niechętnie stracilibyśmy tak wspaniałą bazę. I chcę ci powiedzieć, że zawsze będziesz tu mile widzianym gościem.";
			link.l1 = "Dzięki, Layton. Myślę, że będę często wracał na twoją Wyspę.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "Ach, mój stary przyjacielu "+GetFullName(pchar)+"! Udało ci się odnaleźć Miasto Opuszczonych Statków, korzystając z żeglarskich wskazówek Stevena, prawda? Bardzo, bardzo się cieszę, że cię widzę. Jesteś tu zawsze mile widzianym gościem.";
			link.l1 = "Dzięki, Layton. Myślę, że będę często wracał do twego Miasta.";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Bardzo dobrze. Czy masz jakiekolwiek jedzenie na sprzedaż? Jestem gotów kupić je od ciebie za podwójną zwykłą cenę.";
			if (iTrade > 0)
			{
				link.l1 = "Tak, mogę sprzedać ci trochę zapasów.";
				link.l1.go = "trade";
			}
			link.l2 = "Niestety, nie mam teraz nic do sprzedania.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Szkoda. Nie zapomnij przynieść tego następnym razem - dobrze zapłacę.";
			link.l1 = "Dobrze. Postaram się o tym nie zapomnieć...";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "Ile?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "Do diabła, jesteś kompletnie pijany, kumplu! Jestem pod wrażeniem! Idź się przespać, pohandlujemy później.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "Nie ruszę nawet tyłka z krzesła za taką marną sumę. Przynieś mi więcej!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "I jak zamierzasz żeglować bez żadnych zapasów na swoim statku, kumplu? Chcesz, żeby twoi chłopcy przymierali głodem? Zatrzymaj przynajmniej "+FindRussianQtyString(GetCrewQuantity(pchar))+" dla siebie.";
				link.l1 = "Hm, masz rację.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Łał, kolego, to dla nas za dużo! Nie zdążymy tego zjeść, zanim się zepsuje. Na razie nie mogę wziąć więcej niż "+iTemp+".";
			 link.l1 = "Cokolwiek powiesz.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+" ? W porządku. Zapłacę ci "+FindRussianMoneyString(iMoney)+". Umowa?";
			link.l1 = "Jasne! Miło robić z tobą interesy!";
			link.l1.go = "trade_2";
			link.l2 = "Hm. Nie, zmieniłem zdanie.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Umowa stoi. Zapłacę ci "+FindRussianMoneyString(iMoney)+" za towary. Czy to wystarczy?";
			link.l1 = "Oczywiście! Miłego handlu!";
			link.l1.go = "trade_4";
			link.l2 = "Hm. Nie, zmieniłem zdanie.";
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
				dialog.text = "Cholera jasna! Mój magazyn jest pełny! Nie będę musiał kupować zapasów przez następne pół roku.";
				link.l1 = "Dobrze. W takim razie przywiozę następną partię zaopatrzenia za sześć miesięcy.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Świetnie! Przynieś mi więcej następnym razem.";
				link.l1 = "Pewnie!";
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
				dialog.text = "Świetnie! Mój magazyn jest teraz pełny. Nie będę musiał kupować prowiantu przez kolejne pół roku.";
				link.l1 = "Dobrze. W takim razie przyniosę ci następną partię zapasów za sześć miesięcy.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Świetnie! Przynieś mi więcej następnym razem.";
				link.l1 = "Jasne!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ach, "+GetFullName(pchar)+" ! Cieszę się, że cię widzę! Czego chcesz?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Chcesz kupić ode mnie jakieś zapasy?";
				link.l1.go = "trade";
			}
			link.l2 = "To nic, po prostu chciałem wiedzieć, jak sobie radzisz.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
