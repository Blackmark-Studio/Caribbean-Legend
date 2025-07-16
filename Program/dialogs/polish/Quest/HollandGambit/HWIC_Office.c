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
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Nie.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Wróg jest tutaj! Do broni!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Ty tam, stój! Twoja twarz jest znajoma...oczywiście! Jesteś poszukiwany za swe zbrodnie! Chłopcy, schwytajcie go!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Witamy w Holenderskiej Kompanii Zachodnioindyjskiej. Mów prędko, czas to pieniądz.";
				link.l1 = "Jestem tu w sprawach handlowych. Licencje, przyrządy nawigacyjne i tak dalej...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Chcę zaoferować swoje usługi Kompanii. W zamian za złoto, oczywiście. Czy zatrudniacie?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Witamy w Holenderskiej Kompanii Zachodnioindyjskiej. Mów szybko, czas to pieniądz.";
				link.l1 = "Przykro mi, wydaje się, że się pomyliłem. Odchodzę.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Jestem tu w sprawach handlowych. Licencje, przyrządy nawigacyjne i tak dalej...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Mów szybko, czas to pieniądz.";
			link.l1 = "Jestem tu w sprawach handlowych. Licencje, instrumenty nawigacyjne i tak dalej...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Chcę zaoferować swoje usługi Kompanii. W zamian za złoto oczywiście. Czy zatrudniacie?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Wtedy idź na górę do biura pana Rodenburga.";
			link.l1 = "Dzięki, jestem w drodze.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "Kompanija obecnie nie zatrudnia.";
			link.l1 = "To szkoda. Przepraszam, że przeszkadzam.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Porozmawiaj z Mynheerem Gerritzem. Jego stół jest po lewej stronie, gdy wchodzisz. Prowadzi interesy z kapitanami na kontrakcie.";
			link.l1 = "Dziękuję, oficerze...";
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
				dialog.text = "Alarm! Wróg jest tutaj! Do broni!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! Myślę, że wiem, kim jesteś... Ależ oczywiście! Jesteś poszukiwany za swoje zbrodnie! Chłopcy, bierzcie go!";
				link.l1 = "Do diabła!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Porozmawiaj z naszymi oficerami lub z Mynheerem Gerritzem. Nie mam ci nic do powiedzenia. Jestem na służbie.";
			link.l1 = "Twoja dyscyplina jest godna podziwu.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Wróg jest tutaj! Żołnierze!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Porozmawiaj z Mynheerem Gerritzem.";
			link.l1 = "Dobrze, zrozumiałem.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Wróg jest tutaj! Żołnierze, chwyćcie go!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. Myślę, że coś jest z tobą nie tak... Ale oczywiście! Jesteś poszukiwany za liczne zbrodnie przeciwko Holandii! Żołnierze, zabierzcie go!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Czego chcesz, panie?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "Chcę kupić licencję handlową Holenderskiej Kompanii Zachodnioindyjskiej.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "Słyszałem, że można tu kupić przyrządy nawigacyjne i inne przydatne przedmioty. Czy to prawda?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "Co dziś sprzedajesz?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "Posiadam interesujący dokument dla ciebie, mynheer. Spójrz na pierwsze kilka linijek. Dotyczy on przetrwania Republiki i zysków Kompanii. Są tam również współrzędne pewnego spotkania. Sprzedam ci je, jeśli jesteś zainteresowany. Oczywiście za hojną cenę.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Kapitan o imieniu Reginald Jackson musi dla was pracować. Pływa na szebeku o nazwie 'Harpyja'. Czy mógłbyś mi powiedzieć, jak mogę go znaleźć? Mam do niego ważną sprawę.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Muszę pilnie zobaczyć się z Mynheer Rodenburgiem. To sprawa najwyższej wagi. Gdzie on jest?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Nie, to nic.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Cóż, jesteś wolny, by to kupić. Ale muszę cię ostrzec, że Kompania ceni sobie reputację ścisłej neutralności, dlatego zabronione jest atakowanie jakichkolwiek statków handlowych dowolnego narodu, gdy posiadasz tę licencję\nJeśli dowiemy się, że taki czyn został popełniony - unieważnimy twoją licencję. Dodatkowo, jeśli z jakiegokolwiek powodu popadniesz w konflikt z Holendrami lub Kompanią, twoja licencja również zostanie unieważniona. Czy wszystko jasne?";
				link.l1 = "Jasne jak słońce. Zapamiętam to.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Zapraszamy do zakupu licencji. Więc, na ile dni?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "Licencja zapewnia swobodny przejazd do każdego portu dowolnego narodu, pokazuje twoje pokojowe zamiary i tłumaczy twój cel - handel. Ale nie pomoże ci, jeśli masz jakiekolwiek problemy z prawem. W takim przypadku po prostu ci ją odbiorą. Pamiętaj, \nNie zapomnij podnieść przyjaznej flagi, zanim wpłyniesz do jakiegokolwiek portu. Patrole i kanonierzy fortec wolą najpierw strzelać, a potem pytać\nMinimalny okres obowiązywania licencji to dwadzieścia dni, a maksymalny okres to sześć miesięcy lub 180 dni\nTak, prawie zapomniałem... Zgodnie z naszymi szacownymi tradycjami, wszystkie transakcje związane z licencjami są opłacane w dublonach. Teraz porozmawiajmy o warunkach. Jak długo chcesz, aby licencja trwała?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Przykro mi, ale muszę jeszcze trochę o tym pomyśleć. Do zobaczenia później.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Mynheer, proszę, mów wyraźnie. Nie dosłyszałem cię dobrze. Więc na jak długo?";
				link.l1 = "Niech pomyślę...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "Minimalny termin licencji to dwadzieścia dni. Więc? Dwadzieścia dni lub dłużej?";
				link.l1 = "Pozwól, że pomyślę...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "Maksymalny okres ważności licencji to pół roku. Sto osiemdziesiąt dni lub mniej?";
				link.l1 = "Niech pomyślę...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "Dla "+FindRussianDaysString(sti(fQty))+"? Bardzo dobrze. To będzie cię kosztować "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+" Czy te warunki są do przyjęcia?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Tak, jestem.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Niestety, nie mam teraz przy sobie tyle pieniędzy. Wrócę po licencję później.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Przykro mi, ale muszę jeszcze o tym pomyśleć. Zobaczymy się później.";	
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
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Chwileczkę... Pozwól, że tu postawię znak i pieczęć... zapieczętowane i gotowe. Weź swój dokument.";
			link.l1 = "Dzięki! Żegnaj, mynheer.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "Rzeczywiście, mamy je. Można tu kupić narzędzia nawigacyjne, takie jak kompasy, astrolabia, chronometry i klepsydry. Ale nie zawsze mamy pełny zapas gotowy do sprzedaży, chyba że klepsydry. Nasi kontrahenci i kapitanowie bardzo szybko wykupują pozostałe narzędzia. Więc jeśli nie znalazłeś tego, czego potrzebujesz - odwiedź nas ponownie za tydzień, gdy uzupełnimy zapasy.\nSprzedajemy także mapy i lunety. Chcesz zobaczyć, co mamy?";
			link.l1 = "Tak, proszę.";
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
			dialog.text = "Hm, pokaż mi...(czytanie) No, no... Apetyt Cromwella rośnie. Cholera! Czy te purytańskie psy nie przelały wystarczająco krwi na swojej wyspie, że muszą teraz przynosić swoje plugastwo tutaj!? Skąd masz tę depeszę?";
			link.l1 = "Zabrałem to angielskiemu kurierowi. Czy chciałbyś to kupić?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Tak. Peter Stuyvesant będzie naprawdę zadowolony, gdy to przeczyta, jestem pewien. I podejmie skuteczne kroki, by to powstrzymać... Mogę zapłacić złotymi dublonami lub wystawić ci licencję na pół roku. Co wolisz?";
			link.l1 = " Wybieram złoto.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Chcę licencję.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Bardzo dobrze. Oto twoje siedemset doblonów. Piękna nagroda za dobrze wykonaną usługę.";
			link.l1 = "Oto twoja depesza.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Dobrze. Oto twoja licencja na pół roku.";
			link.l1 = "Dzięki! A oto twoja depesza.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Dziękuję. To dobrze, że okazałeś swoją świadomość i lojalność wobec Republiki. Opowiem Matthiasowi Beckowi i Peterowi Stuyvesantowi o twoim dobrym uczynku.";
			link.l1 = "Dobrze wiedzieć. Żegnaj!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Obawiam się, że już wyruszył do Starego Świata z rodziną Schneurów. Wierzę, że wspomniał ci o tym.";
			link.l1 = "Zgadza się, zrobił to. Ale miałem nadzieję, że mógł się opóźnić z powodu jakichś ostatnich spraw na Archipelagu. Powiedz mi, Gerritz, czy ktoś w Kompanii utrzymuje kontakt z Mynheerem Rodenburgiem? Może za pośrednictwem statków kurierskich?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Wcale nie - zanim wyjechał, poprosił nas, byśmy mu nie przeszkadzali - powiedział, że zaczyna nowe, lepsze życie.";
			link.l1 = "Miejmy nadzieję, że nasze życie też się poprawi. Żegnaj.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Pozwól mi sprawdzić dzienniki manifestów... Ikema, Immerzeel, Jacobs... Jackson, znalazłem go. Hmm, Kapitan Reginald Jackson obecnie prowadzi regularne operacje wysyłkowe między Port Royal a Philipsburgiem. Szukaj go na tej trasie. Teraz kapitanie, muszę cię ostrzec zawczasu - jeśli planujesz jakieś psoty, lepiej tego nie rób, ponieważ ten Kapitan Jackson jest pod naszą ochroną. Czy rozumiemy się, panie?";
			link.l1 = "Po prostu mam z nim interesy. Zwykły handel. Nie zamierzam go w żaden sposób skrzywdzić.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Doskonale. Kapitein Jackson zazwyczaj nie zatrzymuje się na długo w Port Royal ani w Philipsburgu. W końcu czas to pieniądz. Po rozładunku i ponownym załadunku jego statku zwykle natychmiast wyrusza w morze. Lepiej spotkasz go na szlakach morskich.";
			link.l1 = "Dziękuję!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
				{
					dialog.text = "Aha, Kapitanie "+GetFullName(pchar)+"! Dobrze, że tu przybyłeś. Mam dla ciebie propozycję biznesową.";
					link.l1 = "Interesujące! Słucham cię, mynheer.";
					link.l1.go = "silk_info";
					break;
				}
			}
			dialog.text = "Dzień dobry, Kapitein "+GetFullName(pchar)+"! Jak mogę służyć?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "O tym jedwabiu z okrętu...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Dzień dobry. Nie, niczego nie potrzebuję, po prostu chciałem się przywitać.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Niedawno nawiązałem kontakty handlowe z kupcem z Lyonu w sprawie dostaw jedwabiu na Karaiby. Wiesz o tym? Najlepsze żagle na świecie są wykonane z tego jedwabiu, więc musisz być zainteresowany.";
			link.l1 = "Niech mnie piorun trzaśnie, to muzyka dla moich uszu. Jakie są twoje warunki?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Małe, ale regularne dostawy. Mogę zachować dla ciebie trzydzieści beli co dwa tygodnie. Koszt jednej beli to dwadzieścia dubloonów. Zróbmy tak: będę trzymał dla ciebie trzydzieści beli każdego pierwszego i piętnastego dnia miesiąca. Jeśli wtedy po nie nie przyjdziesz, sprzedam je innemu klientowi.";
			link.l1 = "Więc bez zobowiązań?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Dokładnie, kapitanie. Kup jedwab, jeśli chcesz. Płacisz za całą partię - sześćset dublonów. Mam nadzieję, że będziesz stałym klientem.";
			link.l1 = "Dzięki za twoją propozycję, mynheer. Umowa stoi.";
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
				dialog.text = "Oczywiście, kapitanie. Twoje jedwabie czekają na ciebie. Czy jesteś gotów za nie zapłacić?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Oczywiście! Proszę, weź 2550 doblonów.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Do diabła, zapomniałem pieniędzy na moim statku. Przyniosę je za chwilę!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Oczywiście, kapitanie. Twoje jedwabie czekają na ciebie. Czy jesteś gotów za nie zapłacić?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Oczywiście! Proszę, weź sześćset doblonów.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Do diabła, zapomniałem pieniędzy na moim statku. Przyniosę je za chwilę!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", "+GetSexPhrase("chciałbym","chciałabym")+" omówić możliwość zwiększenia dostaw jedwabiu.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = ""+GetSexPhrase("Przyniosłem","Przyniosłam")+" pańskie dublony, Mijnheer "+npchar.name+". Proszę przyjąć.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Przyjemność robić z tobą interesy, kapitanie. Twoje jedwabie zostaną dostarczone na twój statek za pomocą łodzi.";
			link.l1 = "Dzięki!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "Mam nadzieję, że zobaczymy się wkrótce. Wróć ponownie.";
			link.l1 = "Jasne. Do zobaczenia!";
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
				dialog.text = "Doceniam pańskie podejście do biznesu i jestem gotów rozważyć pańską prośbę. Być może moglibyśmy zwiększyć wolumen, powiedzmy, pięciokrotnie. Jednak organizacja takich dostaw będzie wymagać znacznych zasobów. Będziemy musieli rozszerzyć powierzchnię magazynową, wzmocnić ochronę i zapewnić niezawodne trasy dostaw. Ponieważ przynosi to korzyści również panu, proponuję, abyśmy podzielili między sobą te wydatki.";
				link.l1 = "To wszystko brzmi rozsądnie. Jaką kwotę uważa pan za niezbędną do pokrycia tych wydatków?";
				link.l1.go = "UpgradeSilk_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Rozumiem pańskie zainteresowanie zwiększeniem dostaw, jednak na tym etapie trudno mi zgodzić się na takie zmiany. Nie wątpię w pańskie dążenie do rozwoju, ale tego rodzaju transakcja wymaga znacznie większego doświadczenia w sprawach handlowych i pewności własnych działań. Sugeruję, aby poszerzył pan swoją wiedzę w sztuce negocjacji, a następnie wrócił do mnie z bardziej konkretną propozycją. Kiedy będzie pan gotowy, z przyjemnością wzmocnię naszą współpracę.";
				link.l1 = "Hmm... Dobrze. Wrócę do tej rozmowy później.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Biorąc pod uwagę wszystkie niuanse, pański udział w kosztach wyniesie trzy tysiące złotych dublonów. Te środki pozwolą nam bez zwłoki zorganizować niezbędne działania.";
			link.l1 = "Mijnheer "+npchar.name+", trzy tysiące dublonów? Czy to żart? "+GetSexPhrase("Przyszedłem","Przyszłam")+" do pana z uczciwą propozycją, a pan chce, żebym "+GetSexPhrase("zapłacił","zapłaciła")+" tak bajońską sumę za organizację dostaw?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Proszę mnie dobrze zrozumieć. Nie próbuję pana oszukać. Te pieniądze to kwota, która pozwoli nam zapewnić należyty porządek w organizacji dostaw. Chodzi nie tylko o rozbudowę magazynów i ochronę, ale także o zagwarantowanie dostawy towaru bez opóźnień i strat, mimo całej nieprzewidywalności tej sprawy. To standardowe koszty dla takich wolumenów. Ostatecznie pańskie inwestycje się opłacą, a pan otrzyma towar w należytym stanie i na czas.";
			link.l1 = "Pańskie wyjaśnienia nieco mnie uspokajają, mijnheer. Ale jednak ta kwota pozostaje zbyt wysoka. Jestem "+GetSexPhrase("gotowy","gotowa")+" zgodzić się na pańskie warunki, jeśli obniży pan cenę do co najmniej dwóch i pół tysiąca dublonów. Jestem "+GetSexPhrase("pewien","pewna")+", że to wystarczy do zorganizowania dostaw i przestrzegania wszystkich środków bezpieczeństwa.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Rozumiem, kwota jest duża, ale jak już mówiłem, jest niezbędna do właściwego wykonania pracy. Nie mogę jej obniżyć, ponieważ zagroziłoby to wszystkim naszym wysiłkom. Jednak, aby nie czuł się pan"+GetSexPhrase("oszukany","oszukana")+", jestem gotów zaoferować panu piętnastoprocentową zniżkę na wszystkie przyszłe dostawy. To, mam nadzieję, pozwoli panu zrekompensować wydatki.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, piętnastoprocentowa zniżka to oczywiście krok naprzód. Dobrze. Jestem "+GetSexPhrase("gotowy","gotowa")+" przyjąć pańską ofertę, choć cena wydaje mi się wyjątkowo wysoka. Mam nadzieję, że nasza współpraca spełni moje oczekiwania. Oto pańskie pieniądze.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", pańska oferta nie pozostawia mi wyboru. Niech będzie trzy tysiące dublonów, choć to niemała suma. Jednak teraz nie mogę zapłacić wszystkiego od razu. Wrócę, jak tylko zdobędę pieniądze.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Zniżka piętnaście procent? Mijnheer "+npchar.name+", to nie to, czego "+GetSexPhrase("oczekiwałem","oczekiwałam")+". Ta suma to nie tylko koszty, to jawny i bezwstydny rabunek! Ale nie zamierzam zrywać z panem stosunków handlowych. Wrócimy do poprzednich warunków - 30 rolek jedwabiu po 20 dublonów za każdą.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Cieszę się, że się pan zgodził, "+pchar.name+". Teraz co do szczegółów: 150 rolek jedwabiu po 17 dublonów za każdą. Łącznie - 2550 dublonów za całą partię. Towar będzie można odebrać jak zwykle - 1. i 15. dnia każdego miesiąca. Myślę, że ta transakcja przyniesie dobry zysk obu stronom.";
			link.l1 = "Отлично! Вот это - уже неплохой размах. Всего доброго, минхер. Скоро увидимся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "To tylko podejście biznesowe, a nie rabunek, jak mogło się panu wydawać. Ale jak pan sobie życzy. Proszę przychodzić jak zwykle, 1. i 15. dnia, po partię jedwabiu, będę rad nowej transakcji.";
			link.l1 = "Z pewnością, mijnheer. Wszystkiego dobrego.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Cieszę się, że podjął pan właściwą decyzję. Jak tylko przyniesie pan pieniądze, omówimy wszystkie szczegóły transakcji i przystąpimy do jej realizacji.";
			link.l1 = "Do widzenia, Mijnheer "+npchar.name+". Do zobaczenia, gdy tylko zbiorę potrzebną kwotę.";
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
