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
				dialog.text = "Alarm! Mamy tu wroga! Do broni!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Ty tam, stój! Twoja twarz jest znajoma... oczywiście! Jesteś poszukiwany za swe zbrodnie! Chłopcy, brać go!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Witamy w Holenderskiej Kompanii Zachodnioindyjskiej. Mów szybko - w końcu czas to pieniądz.";
				link.l1 = "Jestem tu w sprawach handlowych. Licencje, przyrządy nawigacyjne i tak dalej...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Chcę zaoferować swoje usługi Kompanii. W zamian za złoto, oczywiście. Czy są jakieś wolne kontrakty?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Witamy w Holenderskiej Kompanii Zachodnioindyjskiej. Mów szybko - w końcu czas to pieniądz.";
				link.l1 = "Przykro mi, wydaje się, że się pomyliłem. Odchodzę.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Jestem tu w sprawach handlowych. Licencje, przyrządy nawigacyjne i tak dalej...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Mów szybko. Czas to pieniądz.";
			link.l1 = "Jestem tu w sprawach handlowych. Licencje, instrumenty nawigacyjne i tak dalej...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Chcę zaoferować swoje usługi Kompanii. Czy załapię się na jakieś wolne etaty?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Wtedy idź na górę do biura pana Rodenburga.";
			link.l1 = "Dzięki, już idę.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "W tej chwili nie prowadzimy naboru.";
			link.l1 = "Szkoda. Przepraszam za kłopot.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Zgłoś się do mynheera Gerritza. Jego biurko znajdziesz po lewej stronie przy wejściu. On zajmuje się kontraktami z kapitanami.";
			link.l1 = "Dziękuję, oficerze.";
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
				dialog.text = "Alarm! Mamy tu wroga! Do broni!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "A więc to ty! Jesteś poszukiwany za swoje zbrodnie! Chłopcy, łapać go!";
				link.l1 = "Do diabła!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Nie mam ci nic do powiedzenia. Porozmawiaj z oficerem lub mynheerem Gerritzem. Jestem na służbie.";
			link.l1 = "Twoja dyscyplina jest godna podziwu.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Mamy tu wroga! Żołnierze!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Porozmawiaj z Mynheerem Gerritzem.";
			link.l1 = "Zrozumiałem.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Mamy tu wroga! Żołnierze, łapać go!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = " Hm... coś mi w tobie nie pasuje… Oczywiście! Jesteś poszukiwany za zbrodnie przeciwko Holandii! Żołnierze, brać go!";
				link.l1 = "Cholera!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Czego chcesz, kapitanie?";
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
				link.l3 = "Mam dla ciebie pewien interesujący dokument, mynheer. Rzuć okiem na pierwsze linijki - chodzi o przyszłość Republiki i zyski dla Kompanii. Zawiera też współrzędne pewnego spotkania... Mogę ci to sprzedać. Za odpowiednią, hojną cenę..";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Szukam kapitana imieniem Reginald Jackson. Pływa na szebeku o nazwie 'Harpy'. Słyszałem, że działa na wasze zlecenie. To ważna sprawa - wiesz, gdzie mogę go znaleźć?";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Muszę pilnie zobaczyć się z mynheer Rodenburgiem. To sprawa najwyższej wagi. Gdzie mogę go znaleźć?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Nie, to nic ważnego.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Cóż, możesz ją kupić. Ale ostrzegam - Kompania słynie z bezwzględnej neutralności. Dlatego surowo zabrania się atakowania jakichkolwiek statków handlowych, bez względu na banderę, jeśli tylko posiadasz tę licencję... \nJeśli dowiemy się, że taki czyn został popełniony - unieważnimy twoją licencję. Co więcej, jeśli z jakiegokolwiek powodu popadniesz w konflikt z Holendrami lub Kompanią, twoja licencja również zostanie unieważniona. Czy to jasne?";
				link.l1 = "Jasne jak słońce. Będę o tym pamiętać, mynheer.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Zapraszam. Na ile dni chcesz wykupić licencję?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "Licencja daje ci wolny wstęp do portów wszystkich nacji, potwierdza twoje pokojowe zamiary i handlowy charakter podróży. Ale pamiętaj - nie chroni cię przed odpowiedzialnością za złamanie prawa. W takim wypadku po prostu ci ją odbiorą. \nZawsze podnoś przyjazną banderę, zanim wpłyniesz do cudzego portu - patrole i działa fortecy wolą strzelać, niż zadawać pytania. \nMinimalny czas trwania licencji to 20 dni, maksymalny - 6 miesięcy, czyli 180 dni.\nI jeszcze jedno - zgodnie z naszą szanowną tradycją, wszystkie opłaty za licencje pobieramy wyłącznie w dublonach. Teraz skupmy się na szczegółach umowy. Na ile dni chcesz wystawić licencję?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = " Właściwie... muszę się jeszcze nad tym zastanowić. Wrócę później.";	
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
				dialog.text = "Minimalny termin licencji to 20 dni. Więc...?";
				link.l1 = "Pozwól, że pomyślę...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "Maksymalny okres ważności licencji to pół roku. 180 lub mniej?";
				link.l1 = "Niech pomyślę...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "Dla "+FindRussianDaysString(sti(fQty))+"? Bardzo dobrze. To będzie cię kosztować "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Czy te warunki są dla ciebie do przyjęcia?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Tak, to brzmi dobrze.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Niestety, nie mam przy sobie wymaganej kwoty. Wrócę po licencję później.";
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
					Log_info("Quest: 'Together with the Shark' - Twoja licencja jest krótsza niż 180 dni");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Chwileczkę... Pozwól, że tylko postawię znak i pieczęć... Zapieczętowane i gotowe. Proszę - oto twój dokument.";
			link.l1 = "Dzięki! Żegnaj, mynheer.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "W istocie, mamy je. Można tu kupić przyrządy nawigacyjne, takie jak kompasy, astrolabia, chronometry i klepsydry. Ale nie zawsze mamy pełny zapas gotowy do sprzedaży... no chyba że chodzi o klepsydry. Wiesz, nasi kontrahenci i kapitanowie bardzo szybko wykupują pozostałe narzędzia. Więc jeśli nie znalazłeś tego, czego potrzebujesz - odwiedź nas ponownie za tydzień, gdy uzupełnimy zapasy. \nSprzedajemy także mapy i lunety. Chcesz zobaczyć, co mamy?";
			link.l1 = "Tak, poproszę.";
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
			dialog.text = "Hm, pokaż mi... (czytanie) No, no... Apetyt Cromwella rośnie. Cholera! Czy te purytańskie psy nie przelały już wystarczająco krwi na tej swojej wyspie, że teraz muszą przynosić swoje plugastwo tutaj?! Skąd masz tę depeszę?";
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
			Log_Info("Otrzymałeś 700 dublonów");
			dialog.text = "Bardzo dobrze. Oto twoje 700 doblonów. Piękna nagroda za solidnie wykonaną prace.";
			link.l1 = "Oto twoja depesza.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Dobrze. Oto twoja licencja na pół roku.";
			link.l1 = "Dzięki! W takim razie weź depesze.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Dziękuję. Dobrze, że okazałeś lojalność wobec Republiki... i rozsądek. Opowiem Matthiasowi Beckowi i Peterowi Stuyvesantowi o twoim dobrym uczynku.";
			link.l1 = "Dobrze wiedzieć. Żegnaj!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Obawiam się, że już wyruszył do Starego Świata wraz z rodziną Schneurów. Z tego, co wiem, wspominał ci o tym...";
			link.l1 = "Tak, zgadza się. Ale liczyłem, że jego wyprawa trochę się opóźni... może przez jakieś sprawy na archipelagu. Powiedz mi, Gerritz - czy ktoś z Kompanii utrzymuje z nim kontakt? Chociażby przez statki kurierskie?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Wcale nie - zanim wyjechał, poprosił nas, byśmy mu nie przeszkadzali. Powiedział, że zaczyna nowe, lepsze życie.";
			link.l1 = "Oby i nasze życie zmierzało ku lepszemu... Żegnaj.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Pozwól, że zerknę do manifestów...  Ikema, Immerzeel, Jacobs... Jackson - mam go. Kapitan Reginald Jackson prowadzi regularne rejsy między Port Royal a Philipsburgiem. Szukaj go na tej trasie. Ale ostrzegam cię, kapitanie - jeśli masz wobec niego jakieś złe zamiary, lepiej zrezygnuj... Jackson jest pod naszą ochroną. Czy wyraziłem się jasno?";
			link.l1 = "Chodzi tylko o interesy. Zwykły handel... Nie mam zamiaru robić mu krzywdy.";
			link.l1.go = "caleuche_1";
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
		break;
		
		case "caleuche_1":
			dialog.text = "Doskonale. Kapitein Jackson zwykle nie zatrzymuje się zbyt długo ani w Port Royal, ani w Philipsburgu - w końcu czas to pieniądz. Zwykle zaraz po rozładunku i załadunku wypływa z powrotem. Najlepiej będzie, jeśli spróbujesz go złapać na morzu.";
			link.l1 = "Dziękuję!";
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
				if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
				{
					dialog.text = "Aha... Kapitanie "+GetFullName(pchar)+"! Dobrze, że się zjawiłeś. Mam dla ciebie pewną propozycję... czysto biznesową.";
					link.l1 = "Brzmi interesująco. Słucham cię, mynheer.";
					link.l1.go = "silk_info";
					break;
				}
			}
			dialog.text = "Dzień dobry, kapitanie "+GetFullName(pchar)+"! Jak mogę służyć?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "Co do tego jedwabiu z okrętu...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Dzień dobry. Nie, niczego nie potrzebuję, po prostu chciałem się przywitać.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Niedawno nawiązałem właśnie kontakt z kupcem z Lyonu w sprawie dostaw jedwabiu na Karaiby. Wiesz, najlepsze żagle świata robi się właśnie z tego materiału... Więc pewnie jesteś zainteresowany.";
			link.l1 = "Niech mnie piorun trzaśnie! To przecież muzyka dla moich uszu! Jakie masz warunki?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Chodzi o małe, ale regularne dostawy. Co dwa tygodnie mogę odkładać dla ciebie trzydzieści beli. Cena jednej to dwadzieścia dublonów. Trzymam je zawsze pierwszego i piętnastego dnia miesiąca. Ale jeśli nie przyjdziesz... wtedy sprzedam je komuś innemu.";
			link.l1 = "Czyli żadnych zobowiązań?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Dokładnie, kapitanie. Kupuj jedwab, jeśli chcesz. Płać za całą partię - 600 dublonów. Mam nadzieję, że będziesz stałym klientem.";
			link.l1 = "Dzięki za ofertę, mynheer. Umowa stoi.";
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
				dialog.text = "Oczywiście, kapitanie. Twoje jedwabie już na ciebie czekają. Czy jesteś gotów zapłacić?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Oczywiście! Proszę, weź 2550 doblonów.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Do diabła, zostawiłem pieniędze na statku. Poczekaj, zaraz wrócę!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Oczywiście, kapitanie. Twoje jedwabie już na ciebie czekają. Czy jesteś gotów zapłacić?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Oczywiście! Proszę, weź 600 doblonów.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Do diabła, zostawiłem pieniędze na statku. Poczekaj, zaraz wrócę!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mynheer "+npchar.name+", "+GetSexPhrase("chciałbym","chciałabym")+" omówić możliwość zwiększenia dostaw jedwabiu.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = ""+GetSexPhrase("Przyniosłem","Przyniosłam")+" pańskie dublony, mynheer "+npchar.name+". Proszę je przyjąć.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Interesy z panem to czysta przyjemność, kapitanie. Jedwabie zostaną dostarczone na twój statek łodzią.";
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
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Rozumiem pańskie zainteresowanie zwiększeniem dostaw, jednak na tym etapie nie jest to możliwe. Nie wątpię w pańskie szczere intencje handlowe, ale tego rodzaju transakcja wymaga znacznie większego doświadczenia w sprawach handlowych i pewności własnych działań. Sugeruję, aby poszerzył pan swoją wiedzę w sztuce negocjacji, a następnie wrócił do mnie z bardziej konkretną propozycją. Gdy już będzie pan gotowy, z przyjemnością wzmocnię naszą współpracę.";
				link.l1 = "Hmm... Dobrze. Wrócimy do tej rozmowy później.";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Biorąc pod uwagę wszystkie niuanse, pański udział w kosztach wyniesie trzy tysiące złotych dublonów. Te środki pozwolą nam bez zwłoki zorganizować niezbędne działania.";
			link.l1 = "Mynheer "+npchar.name+", trzy tysiące dublonów...? Czy to jakiś żart?! "+GetSexPhrase("Przyszedłem","Przyszłam")+" do pana z uczciwą propozycją, a pan chce, żebym "+GetSexPhrase("zapłacił","zapłaciła")+" tak bajońską sumę za organizację dostaw?!";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Proszę mnie dobrze zrozumieć. Nie próbuję pana oszukać. Te pieniądze to kwota, która pozwoli nam zapewnić należyty porządek w organizacji dostaw. Chodzi nie tylko o rozbudowę magazynów i ochronę, ale także o zagwarantowanie dostawy towaru bez opóźnień i strat, mimo całej nieprzewidywalności tej sprawy. To standardowe koszty dla takich wolumenów. Ostatecznie pańskie inwestycje się opłacą, a pan otrzyma towar w należytym stanie i na czas.";
			link.l1 = "W porządku, pańskie wyjaśnienia nieco mnie uspokoiły. Ale jednak ta kwota pozostaje zbyt wysoka. Jestem "+GetSexPhrase("gotowy","gotowa")+" zgodzić się na pańskie warunki, jeśli obniży pan cenę do co najmniej dwóch i pół tysiąca dublonów. Jestem "+GetSexPhrase("pewien","pewna")+", że to wystarczy do zorganizowania dostaw i przestrzegania wszystkich środków bezpieczeństwa.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Rozumiem, kwota jest duża, ale jak już mówiłem, jest niezbędna do właściwego wykonania pracy. Nie mogę jej obniżyć, ponieważ zagroziłoby to wszystkim naszym wysiłkom. Jednak, aby nie czuł się pan"+GetSexPhrase("oszukany","oszukana")+", jestem gotów zaoferować panu piętnastoprocentową zniżkę na wszystkie przyszłe dostawy. To, mam nadzieję, pozwoli panu zrekompensować wydatki.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, piętnastoprocentowa zniżka to oczywiście krok naprzód. Dobrze. Jestem "+GetSexPhrase("gotowy","gotowa")+" przyjąć pańską ofertę, choć cena wydaje mi się wyjątkowo wysoka. Mam nadzieję, że nasza współpraca spełni moje oczekiwania. Oto pańskie pieniądze.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mynheer "+npchar.name+", pańska oferta nie pozostawia mi wyboru. Niech już będą te trzy tysiące dublonów, choć to niemała suma. Jednak teraz nie mogę zapłacić wszystkiego od razu. Wrócę, jak tylko zdobędę pieniądze.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Zniżka piętnaście procent? Mynheer "+npchar.name+", to nie to, czego "+GetSexPhrase("oczekiwałem","oczekiwałam")+". Ta suma to nie tylko koszty, ale wręcz jawny i bezwstydny rabunek! Ale nie zamierzam zrywać z panem stosunków handlowych. Wrócimy do poprzednich warunków - 30 rolek jedwabiu po 20 dublonów za każdą.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Cieszę się, że się pan zgodził, "+pchar.name+". Teraz co do szczegółów: 150 rolek jedwabiu po 17 dublonów za każdą. Łącznie - 2550 dublonów za całą partię. Towar będzie można odebrać jak zwykle - 1. i 15. dnia każdego miesiąca. Myślę, że ta transakcja przyniesie dobry zysk obu stronom.";
			link.l1 = "Wyśmienicie. To całkiem niezły interes. W takim razie miłego dnia, mynheer. Do zobaczenia wkrótce.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "To tylko podejście biznesowe, a nie rabunek, jak mogło się panu wydawać. Ale jak pan sobie życzy. Proszę przychodzić jak zwykle, 1. i 15. dnia, po partię jedwabiu. Będę się cieszył z każdej transakcji.";
			link.l1 = "Z pewnością, mynheer. Wszystkiego dobrego.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Cieszę się, że podjął pan właściwą decyzję. Jak tylko przyniesie pan pieniądze, omówimy wszystkie szczegóły transakcji i przystąpimy do jej realizacji.";
			link.l1 = "Do widzenia, mynheer "+npchar.name+". Zobaczymy się, gdy tylko zbiorę potrzebną kwotę.";
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
