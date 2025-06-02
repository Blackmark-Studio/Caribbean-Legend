// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ach, Charles. Dzięki, że wpadłeś. Chciałem ci tylko podziękować za spędzenie czasu z Helen. Dziewczyna musiała wyleczyć swoje rany, a słyszałem, że ty też się dobrze bawiłeś, ha-ha! Cholera, nawet ci zazdroszczę!";
					link.l1 = "Nie jesteś zły? Za beczkę i... wszystko inne?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ah, Charles. Dzięki, że wpadłeś. Chciałem ci podziękować za spędzenie czasu z Helen. Dziewczyna potrzebowała zaleczyć swoje rany, a słyszałem, że ty też dobrze się bawiłeś, ha-ha! Powodzenia w Cartagenie!";
					link.l1 = "Tak, również cieszę się, że wszystko poszło dobrze wczoraj. Do zobaczenia, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "O, mój przyjacielu "+pchar.name+"Miło cię widzieć! Co mogę dla ciebie zrobić?";
					link.l1 = "Zatrzymałem się tylko, aby zobaczyć, jak się miewasz.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, chciałbym kupić żelazne drewno.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "Jak mogę pomóc, panie?";
					link.l1 = "Chciałbym prosić o twoją pomoc, Diable Lasu.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Aha, mój przyjacielu "+pchar.name+"! Jaka nowina?";
					link.l1 = "Udało mi się dowiedzieć wielu ciekawych rzeczy od Kata.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Więc, "+pchar.name+", czy rozmawiałeś z Gladys?";
					link.l1 = "Tak, zrobiłem. Jan, spójrz tutaj... Czy możesz mi coś powiedzieć o tym kawałku pergaminu?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Nie mam jeszcze nic nowego do powiedzenia, "+pchar.name+". Ale pracuję nad rozwiązaniem naszej sprawy. Wróć później.";
					link.l1 = "Dobrze, Jan. Zobaczę się z tobą później.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", całkowicie mnie zawiodłeś. Spodziewałem się, że będziesz poważnym człowiekiem, a okazuje się, że jesteś tylko głupim chłopcem. Gdzie byłeś przez cały ten czas, co? Anglicy zajęli Isla Tesoro, podczas gdy ty robiłeś Bóg wie co!\nWszystkie moje plany są zrujnowane! Szczerze mówiąc, prawie zapomniałem o twoim istnieniu i nie chcę, by mi o tym przypominano. Znikaj!";
						link.l1 = "Nie mogę w to uwierzyć!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "O, jesteś, "+pchar.name+"Rozważyłem naszą niedolę nieco. Nie nazwałbym tego planem, ale...";
						link.l1 = "Zamieniam się w słuch, Janie.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "Jak się sprawy mają? Czy jest coś, w czym mogę ci pomóc?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "Rozmawiałem z Czarnym Pastorem. Niestety, wynik naszej rozmowy sprawił, że wróciłem do ciebie po radę, jestem skołowany.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "Znalazłem Diosa i odbyliśmy miłą pogawędkę. Powiedział mi wiele interesujących rzeczy, ale niestety nie doszliśmy do sedna sprawy.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "O, Janie. Mam ci tyle do powiedzenia, że zajęłoby mi to całą noc, więc będę zwięzły.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "Zabrałem Nathaniela Hawka z Wyspy Sprawiedliwości. Jest teraz na moim statku.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "Zostawiłem Nathaniela Hawka w wiosce Miskito na leczenie przez szamana o imieniu Wężowe Oko. Obiecał mi przywrócić zdrowie Nathanowi.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Nie ma wiele do powiedzenia w tej chwili. Po prostu wpadłem, żeby zobaczyć, jak się masz.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "Jakie wieści, "+pchar.name+"? Jak tam sprawy?";
					link.l1 = "O, nie mogło być gorzej. Zrobiłem tyle pracy... Wytropiłem Jackmana, wyrzuciliśmy pochwy, a ja utopiłem go jak największego imbecyla razem z wszystkim, co mogło być w jego kabinie. Teraz nie mam nic, co mogłoby pomóc mi zdjąć smród z imienia Rekina i przenieść winę na Barbazona. Obawiam się, że to sprawa stracona, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "Słyszałem o twoich bohaterskich czynach! Dannie opowiedział mi o nich pokrótce. A przy okazji, teraz jesteśmy przyjaciółmi. I Nathan zupełnie się zmienił! Cała jego depresja zniknęła, gdy ujrzał swojego 'Centuriona'.\nAle mam dla ciebie złe wieści, "+pchar.name+"Zmarnowaliśmy tyle czasu, że prawa dziedziczenia testamentu Sharpa dawno przepadły, a Isla Tesoro stała się angielską bazą wojskową. Nie mogę już nic zrobić, aby pomóc ci z Levasseurem."link.l1 ="Jestem absolutnie oniemiały... Przeszliśmy przez tyle kłopotów na nic. Czy naprawdę nie ma nic, co możemy zrobić?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "Słyszałam o twoich bohaterskich czynach! Dannie mnie wprowadziła. A tak przy okazji, pogodziliśmy się. Nie poznasz Nathana. Jak tylko zobaczył swojego 'Centuriona', jego marudzenie zniknęło jak zły sen...";
						link.l1 = "Nathan znowu ma się dobrze? Cieszę się, że to słyszę!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Oto jesteś, "+pchar.name+"  Teraz mam coś, co muszę ci powiedzieć.";
					link.l1 = "Witaj, Janie. Jestem przepełniony radością! Co słychać? Mam nadzieję, że coś pozytywnego?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "O, jesteś, "+pchar.name+" ! Wypocząłeś?   I czy mogę stwierdzić,  że jesteś ponownie gotowy na wielkie przygody?";
					link.l1 = "Cześć, Jan. Tak, jestem gotów.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "Jakie wieści, "+pchar.name+"? Jak się mają sprawy?";
					link.l1 = "Och.  Wszystko jest absolutnie okropne. Walczyłem jak lew, ale wciąż przegrałem. Jak pamiętasz, testament Sharpa miał ograniczenie czasowe. Cóż, ten czas minął i Isla Tesoro jest teraz angielską bazą wojskową. To przegrana sprawa, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Witaj, "+pchar.name+" ! Dobre wieści: odbyło się zebranie Rady i Bractwo Wybrzeża znalazło nowego przywódcę.";
					link.l1 = "Dzień dobry, Janie. Cieszę się z tobą.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Cóż, "+pchar.name+"? Dogoniłeś Molligana?";
					link.l1 = "Zrobiłem to. To on ukradł twoje żelazne drewno.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "Na czas jak zawsze, "+pchar.name+"Sprzedałem żelazne drewno, które mi przyniosłeś.";
					link.l1 = "Doskonale. Ile pieniędzy zarobiłeś?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Cóż, "+pchar.name+"Czy dogoniłeś Molligana?";
					link.l1 = "Zrobiłem to. To on ukradł twoje żelazne drewno. Przy okazji natknąłem się na jego kupca. Był nim jakiś holenderski dowódca wojskowy. Sprzedałem mu towar.";
					link.l1.go = "saga_59";
					link.l2 = "Zrobiłem to. Próbowałem zmusić go, by pokazał mi swój ładownię... wdaliśmy się w potyczkę i... teraz nie ma już Molligana. Ale nic nie można zobaczyć w ładowni poza hebanem i mahoniem.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Co nowego?";
					link.l1 = "Jan, chciałbym z tobą porozmawiać na pewien temat. Zgłębiając przeszłość matki Helen, Beatrycze, natknąłem się na kogoś, kogo dobrze znasz. Jak mi powiedziano...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+" . Jak idą sprawy? Sądząc po twojej twarzy, mogę ci pogratulować? ";
					link.l1 = "Tak. W końcu udało mi się rozwiązać ten bałagan. Helen otrzymała wszystkie prawa do Isla Tesoro. Nigdy więcej nikt nie odważy się naruszyć schronienia Braci Wybrzeża!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "Nie, Jan. Na razie nic.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, chciałbym kupić trochę twojego żelaznego drewna.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Helen, witaj, moja droga. Jakie masz wieści? Chciałaś czegoś?";
					link.l1 = " Witaj, Janie!  Wszystko po staremu, wpadłem tylko, by cię zobaczyć.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Czy mogę ci w czymś pomóc?";
				link.l1 = "Nie, jestem w porządku.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "Znam cię, do diabła! Jesteś tym dzielnym kapitanem, który uratował Rumbę i stawił czoła działom angielskiej korwety! Co za radość cię widzieć! Helen jest dla mnie jak córka. Od dziś jestem ci wiecznie dłużny. Możesz mnie po prostu nazywać Janem lub Svensonem, jeśli chcesz. Co mogę dla ciebie zrobić?";
			link.l1 = "Muszę zlikwidować Levasseura, gubernatora Tortugi. Wiem, że dotarcie do niego na jego wyspie nie będzie łatwym zadaniem, dlatego przyszedłem do ciebie po poradę.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Na Boga, gdzie byłeś kilka lat temu! Sam planowałem przeprowadzić tę samą eskapadę. On zrujnował całą grę dla nas z Francuzami. Ale wtedy wszystko było inne. Blaze żył, Shark miał pewne znaczenie, a Nathan rządził w Maroon Town... Teraz wszystko się zmieniło i, Bóg wie, nie na lepsze. Czy wiesz cokolwiek o nas, o Braciach?";
			link.l1 = "Niedawno tu przybyłem, więc właściwie nic nie wiem. Poza tym, że ty i Jackman jesteście częścią Rady.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Och, nie mogę znieść tego Jackmana! Kiedy się tu pojawił, zaczęły się wszystkie nasze kłopoty. Zastanowię się nad twoją prośbą. Na pierwszy rzut oka nic nie przychodzi mi do głowy.";
			link.l1 = "Mam coś interesującego dotyczącego Jackmana.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Hm. Co to takiego?";
			link.l1 = "Jackman szuka Gladys Chandler i jej córki. Po rozmowie z Higginsem zacząłem myśleć, że szuka Rumba. Wydaje się, że Gladys nie jest biologiczną matką Helen i nazywała się Chandler zanim poślubiła Seana McArthura.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "Do diabła! To złe wieści. Jackman jest teraz silniejszy niż kiedykolwiek. Na dodatek mam złe przeczucie, że nie działa sam. Za jego plecami kryje się złowieszczy cień. Jeśli naprawdę potrzebuje Helen, to dziewczyna pilnie potrzebuje ochrony. Obawiam się, że jestem trochę za stary, by zrobić to osobiście...";
			link.l1 = "To nie wszystko. Jackman szuka również kogoś o imieniu Henry Kat, dawnego bosmana z 'Neptuna', z załogi kapitana Rzeźnika.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Caramba! Moje najgorsze podejrzenia się potwierdziły! Ten Rzeźnik i jego 'Neptune' trzymali cały archipelag w strachu. Wtedy nie było żadnych Braci, każdy był zdany na siebie. Ten człowiek zrobił wiele złych rzeczy, osoba droga mi zginęła z jego powodu.\nNigdy nie miałem okazji go spotkać. 'Neptune' został zatopiony przez angielski fregat, a Rzeźnik został stracony w St. John's. Dobrej podróży! Chociaż było wielu ludzi, którzy podziwiali jego szczęście i bezmyślną odwagę.\nSam Jackman był jego prawą ręką i pierwszym oficerem na 'Neptunie'. Zaskoczony? Byli przestępcy stali się bohaterami Narodu, wszystko dzięki Cromwellowi! Gdzie podziała się dobra stara Anglia?\nMusimy znaleźć Henryka Wisielca, zanim zrobią to ludzie Jackmana. Może on trzyma klucz do tej zagadki, jeśli jeszcze żyje.";
			link.l1 = "Założę się, że łatwiej byłoby znaleźć igłę w stogu siana. Masz chociaż jakieś tropy?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Znałem Henryka, gdy był jeszcze dzieciakiem. Syn dziwki z Kartageny, pół Hiszpan, choć zawsze trzymał to w tajemnicy. Jego matka była gorąca! Nie mogę powiedzieć, że była piękna, ale bardzo mało flamenco tańczyło tak jak ona. Cały burdel oglądał pokazy nagiej Chici Gonzales i jej kastaniety.\nBiedna dziewczyna. Złapała paskudną chorobę i zmarła jak świeca. To wtedy namówiłem Henryka, by pojechał na Providencję, gdzie szybko sobie wyrobił imię i dołączył do załogi Thomasa Beltrope'a, bliskiego przyjaciela Nicolasa Sharpa. Ci dwaj byli ostatnimi psami królowej Elżbiety i zawsze pracowali razem. Dobre czasy!\nThomas odpłynął z powrotem do Anglii, gdy jego partner umarł. Zabrał swoją załogę ze sobą, ale Henryk został na Karaibach. Pływał pod różnymi kapitanami, aż pojawił się Rzeźnik. A propos, zyskał swój przydomek dzięki kordelasowi, który zawsze miał pod ręką.";
			link.l1 = "A co nam mówi ta informacja?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Jeśli Kaci ucieka przed piratami, najlepszym miejscem dla niego byłoby jakieś hiszpańskie miasto. Zwłaszcza jego dom w Kartagenie, gdzie ma przyjaciół i krewnych. Henry był dość religijny. Więc mało prawdopodobne, że chodziłby do kościoła pod innym wezwaniem. Prawdopodobnie nadal nosi to samo imię, które miał jako dziecko, Enrique.";
			link.l1 = "Tak... Wybór jest marny, ale przynajmniej lepszy niż nic.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Spróbuj go znaleźć, Charles! Niewielu wie o hiszpańskich korzeniach Henry'ego, więc mamy tu małą przewagę. Pomyślę, jak przekonać Rumbę, by dołączyła do twojej załogi. Dziewczyna ma jaja, nigdy nie służyła pod czyimś dowództwem oprócz ojca. \nAle nie ma ani statku, ani załogi, a musi jakoś zarabiać na życie. Oczywiście, będę dalej pomagać Gladys, jak zawsze, ale nie będę w stanie zatrzymać Helen w Blueweld na długo. A taki oficer będzie dla ciebie bardzo przydatny. Sean nauczył ją wszystkiego, co wiedział, i wychował jak chłopca. \nCzułbym się lepiej, gdyby była pod dowództwem takiego kapitana jak ty.";
			link.l1 = "Rumba okazała się dość wartościowa. Potrzebuję więcej takich ludzi jak ona w mojej załodze. Więc, jeśli uda ci się ją przekonać, zrobię ją oficerem. Ale najpierw chcę zrozumieć, kim ona naprawdę jest i dlaczego Jackman jej potrzebuje. Obawiam się, że w przeciwieństwie do Donovana, nie interesują go jej wdzięki. Więc spróbuję znaleźć Wisielca, choć niczego nie mogę obiecać.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Cóż, wspaniale. Weź tę licencję Holenderskiej Kompanii Zachodnioindyjskiej na trzy miesiące. Napisz tam swoje imię, może się okazać przydatna w twoich poszukiwaniach. W międzyczasie, pomyślę o tym, co powiedziałeś na temat Levasseura i Tortugi.";
			link.l1 = "Dzięki wielkie! Ten papier mi się przyda. W takim razie ruszam do Kartageny.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "Henry nie żyje?  Czekaj, czy to ty go zabiłeś?";
			link.l1 = "Nie patrz na mnie tymi szerokimi oczami! Nie miałem z tym nic wspólnego. Zmarł przez własne sumienie, które go zepsuło, i strach przed Jackmanem. Stary pirat miał problemy z sercem i nie miał zbyt wiele czasu do życia. Oto, co udało mi się dowiedzieć...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Proszę, powiedz!";
			link.l1 = "Dwadzieścia lat temu Henry miał przekazać skrzynię złota w imieniu Kapitana Rzeźnika przybranej matce swojej biologicznej córki. Nie ma absolutnie żadnych wątpliwości, że tą przybraną matką była pani McArthur. W tamtym czasie nosiła nazwisko Chandler i mieszkała w Belize. Ale okoliczności zatrzymały Kaciego w St. John's na cały dodatkowy miesiąc, a kiedy w końcu dotarł do Belize, było ono w ruinach po napaści Hiszpanów, a ciotka Gladys i Sean już ruszyli w drogę pod twoim skrzydłem.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = " ";
			link.l1 = "Oni podawali Helen za swoją biologiczną córkę i wychowywali ją jak własną. Henry stracił z nimi kontakt i ukrywał się, świadom zemsty Jackmana i żyjąc przez te całe dwadzieścia lat w strachu. Okazuje się, że Jackman szuka córki swojego kapitana. Ale dlaczego, nie wiem.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Może wykonuje czyjeś rozkazy...";
			link.l1 = "Wątpię. Kto mógłby mu rozkazywać? Rzeźnik nie żyje. Jego śmierć jest potwierdzona oficjalnymi dokumentami. Dziesiątki, jeśli nie setki ludzi, byli świadkami jego śmierci.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Może nie chodzi o to, kim jest ojciec Helen. Może wszystko sprowadza się do jej biologicznej matki. Już domyślam się, kim była, ale boję się to przyznać. Ale Gladys! Jak mogła utrzymać to w tajemnicy przez tyle lat, nie ujawniając tego nawet swojemu mężowi! Sean McArthur z pewnością by mi o tym powiedział. Nigdy nie mieliśmy przed sobą tajemnic.";
			link.l1 = "Zamierzam odbyć szczerą rozmowę z Gladys. Myślę, że mam sposoby, aby ją zmusić do mówienia. Do następnego razu, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "Skąd to wziąłeś!?";
			link.l1 = "Gladys dała mi to. Powiedziała, że to 'spadek po matce Helen'. Nie zna jej imienia. Coś mi mówi, że to nie jest byle jaki skrawek papieru.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Pamiętasz, kiedy mówiłem ci, że mam przeczucie, kim była prawdziwa matka Helen? Teraz jestem tego pewny. Miała na imię Beatrice Sharp. Była biologiczną córką mojego nauczyciela i przyjaciela Nicholasa Sharpa, uznaną siostrą założyciela naszego Bractwa, Blaze'a Sharpa, i współwłaścicielką Isla Tesoro. To ten kawałek mapy, na który poluje Jackman.";
			link.l1 = "No proszę! Ale po co mu połowa mapy wyspy?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Wyspę odkrył Nicolas Sharp. Nazwał ją Isla Tesoro, sporządził jej mapę i objął w posiadanie poprzez Providence Island Company, gdzie miał dobre kontakty.\nNicolas napisał w swoim świadectwie, że wyspa może być dziedziczona tylko przez tych, którzy przedstawią dwie części mapy. Zrobił to, aby uniknąć jakichkolwiek niesnasek. Przekazał części Beatrice i swojemu pasierbowi Blaze'owi, zanim tragicznie zginął z rąk Hiszpanów.";
			link.l1 = "No, przeklęty ja! Jakie to dziwne.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Masz rację. To nie był najlepszy pomysł. A przebiegły notariusz dodał, że wyspa będzie należeć do korony angielskiej, jeśli nikt nie przedstawi obu części mapy w ciągu roku po śmierci spadkobierców.\nNikt się tego wtedy nie spodziewał. A teraz płacimy cenę za naszą głupotę. Beatrice zmarła dwadzieścia lat temu. Wszystkie te lata minęły, a my wciąż nie mamy pojęcia, gdzie jest jej grób wraz z jej częścią mapy. Blaze Sharp został zamordowany niedawno. Jego część również zniknęła.\nJeśli nikt nie przedstawi całej mapy Isla Tesoro władzom w ciągu roku, to Sharptown zostanie przejęte przez Anglię. Wyślą tam gubernatora z garnizonem i Bractwo zostanie zniszczone.";
			link.l1 = "Co sugerujesz, abyśmy zrobili?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Nie możemy do tego dopuścić. Potrzebuję cię, Charles, potrzebuję, byś zapobiegł takiemu rozwojowi wypadków. I będę w stanie pomóc ci w eliminacji Levasseura dopiero po tym, jak przejmiemy kontrolę nad Isla Tesoro i wybierzemy Sharka Dodsona jako nowego przywódcę Braci. On jest najgodniejszy z nas. Oferuję ci sojusz.\nA tak przy okazji, rozmawiałem z Helen. Zgodziła się dołączyć do twojej załogi.";
			link.l1 = "Nie zostawiasz mi wyboru, Janie. Nie mogę wrócić do Francji, nie przywróciwszy honoru mojej rodzinie. A żeby to zrobić, muszę zlikwidować Levasseura z twoją pomocą lub bez niej. Niepotrzebne ofiary nie są tym, czego pragnę, i mam nadzieję, że potrafisz wymyślić, jak zdobyć Tortugę, nie rozlewając zbyt dużo krwi. Muszę jednak przyznać, że chciałbym samemu zrozumieć zamgloną przeszłość dotyczącą dziedzictwa Sharpsa.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "Miło słyszeć rozsądne myśli! Znajdziemy właściwy sposób, by zdobyć Tortugę. To ci obiecuję. Więc, ruszajmy?";
			link.l1 = "Chodźmy! Wpadnę później jeszcze raz. Na razie pomyśl, od czego zacząć rozwiązywanie tego problemu.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Zajrzyj ponownie za dwa lub trzy dni. Myślę, że do tego czasu mój plan dojdzie do kulminacji. I nie zapomnij zabrać ze sobą Helen na swój statek. Biedna dziewczyna tęskni za morzem. Będzie lojalną asystentką i nie będziesz musiał się dwa razy zastanawiać, by na niej polegać.";
			link.l1 = "Dobrze, Jan. Idę po nią od razu.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "Najpierw musisz znaleźć Rekina. Chciał sam pozbyć się Levasseura i zapewniam cię, że ma kilka błyskotliwych pomysłów. Oczywiście, moglibyśmy również przekonać Marcusa, by przyjął przywództwo. W końcu jest strażnikiem Kodeksu. Ale wątpię, by był w stanie nam pomóc, celowo ograniczył wszelki kontakt z Levasseurem i Tortugą. Człowiek zasad.\nNie mam pojęcia, gdzie ukrywa się Steven i jego ludzie, ale jego fregata 'Fortuna' była widziana w Puerto Principe. Może Zachary Marlow, znany również jako Czarny Pastor, wskaże nam, gdzie szukać Rekina. Po drugie, musimy zdobyć poparcie innych baronów, aby wybrać Dodsona. A żeby to zrobić, musimy zebrać ich indiańskie odłamki - głosy. Nowy przywódca musi mieć wszystkie pięć. Tak mówi nam Kodeks, gdy poprzedni przywódca umarł.\nAbsurd! Czas zmienić prawa, ale tylko nowy przywódca może to zrobić. Już mamy mój głos. Wierzę, że Czarny Pastor ma gdzieś, czyj zadek siedzi w Sharptown. Mam nadzieję, że Jackman nie rozmawiał z nim pierwszy. Musimy również przekonać zarówno Tyrexa, jak i Jacquesa Barbazona, którzy się nienawidzą. Ale to wszystko nie ma znaczenia, dopóki nie dowiemy się, co stało się z Rekinem. Po trzecie, pewnego dnia będziemy musieli zabić Jackmana i zastąpić go kimś innym. Nie będzie z nami negocjować.\nSzkoda, że Hawk nie żyje! Ludzie mu ufali i moglibyśmy skorzystać z jego słowa. Nie znajdziemy lepszego barona dla Maroon Town. Możliwe, że Jackman ma coś wspólnego z morderstwem Blaze'a, więc jest on również kluczem do znalezienia drugiej części mapy. Jacob nikomu nie ufa i najprawdopodobniej trzyma część mapy w swojej kajucie na 'Centurionie'.\nRodzina Hawka była właścicielem fregaty, ale Jackman ją przejął, podobnie jak baronię Hawka. Jeśli znajdziemy drugą część mapy u Jackmana, będzie to wielki argument dla wyboru Stevena. Szczególnie dla Marcusa Tyrexa, strażnika Kodeksu, i jego nadmiernej skrupulatności w kwestii honoru. Zwrócimy Helen jej prawa do Isla Tesoro, gdy tylko zdobędziemy obie części mapy.\nMusimy jednak być ostrożni, Jackman nie będzie bezczynnie siedział i patrzył, jak szukasz.";
			link.l1 = "Cóż... Zamierzam odwiedzić Czarnego Pastora. Opowiedz mi o nim.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "Do diabła, jeśli wiem, co on ma na myśli. Czasami wygląda jak kompletny dziwak, ale mimo to wierzę, że to tylko sprytna gra. Poza tym jego ludzie są gotowi walczyć z samym diabłem na cześć ich ukochanego Pastora.\nZałożyli coś w rodzaju protestanckiej sekty blisko hiszpańskiej inkwizycji na Kubie. Więc nawet nie zaczynaj mówić o kwestiach teologicznych tam, nie zaakceptują ich.";
			link.l1 = "Zważę na to...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "I, "+pchar.name+": nie trać ani minuty swojego czasu. Mówię poważnie. Pamiętasz zapis w testamencie, który mówi, że jeśli spadkobiercy nie zgłoszą się po wyspę w ciągu roku, to Isla Tesoro przejdzie na koronę angielską, prawda? Cóż, czas nie jest teraz po naszej stronie. Kiedy ostatnim razem się widzieliśmy, zostało tylko około jedenaście miesięcy do upływu terminu.";
			link.l1 = "Pamiętam, Jan. Masz rację, czas to pieniądz. Już nad tym pracuję!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Hm... Co ci powiedział Zachary?";
			link.l1 = "Przed swoim zniknięciem Rekin przyszedł go odwiedzić i zostawił u Zacharego swój fregat jako zastaw za bryg z jedzeniem, a potem odpłynął gdzieś na północny zachód do Kuby.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "To naprawdę podejrzane. Kontynuuj.";
			link.l1 = "Jeden miesiąc później Dodson nie wrócił, a Pastor, zgodnie z warunkami umowy, wziął fregatę dla siebie i sprzedał ją za dobrą cenę jakiemuś gościowi o nazwisku Paterson. Jeśli chodzi o nasze sprawy, Zachary wspomniał, że Rekin mógł odpłynąć na jakiś legendarny Wyspę Sprawiedliwości, rzekomo znajdującą się gdzieś niedaleko na północny zachód od Kuby.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "Słyszałem o Wyspie Sprawiedliwości. Mówią, że jest wyspa, gdzie biali i czarni żyją w pokoju, razem jako równi sobie. Bzdury rozpowiadane przez wszelkiej maści marzycieli. Ale istnieje możliwość, że na północnym zachodzie znajduje się jakaś baza przemytników. Ich barki były regularnie widywane na otwartym morzu dziesięć lat temu. Przywozili różne towary na Kubę w zamian za jedzenie.";
			link.l1 = "Skarby za jedzenie? Pastor również wspominał mi o korsarzach przewożących wołowinę. To prawdziwa chodząca sprzeczność.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "Te plotki muszą mieć jakieś źródło, te barki przemytników lub bukanierskie żaglowce płynęły do tego regionu z jakiegoś powodu. Pamiętam, że Rekin opowiadał mi historie o swojej młodości, był jakimś niewolnikiem w dziwnej formacji zrobionej z wraków statków na środku morza.\nMoże to jest nasze miejsce? Nie mam pojęcia. W każdym razie, Pastor ma rację, coś tam jest, albo tajna baza, albo wyspa, do której Rekin mógł się udać. Posłuchaj, popłyń do Santo Domingo i znajdź naukowca o imieniu Jose Dios.\nJest hiszpańskim kartografem. Kiedyś uratowałem go przed brudnymi łajdakami, szanuję wykształconych ludzi. On ci pomoże, po prostu powiedz mu moje imię. Udaj się na Hispaniolę, znajdź Dosa i porozmawiaj z nim.\nZna geografię naszego regionu doskonale i jeśli on ci nie pomoże - nikt nie pomoże.";
			link.l1 = "Dobrze, Janie. Brzmi jak plan. Wyruszam!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "To szkoda. Miałem nadzieję, że Jose nam pomoże.";
			link.l1 = "Też na to liczyłem, ale niestety. Cóż, nie pogrążajmy się w smutku. Poświęcę jeszcze trochę czasu na rozważenie tej sprawy. Tak, Janie, powiedz mi, jak zginął Hawk?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Nikt nie był świadkiem jego śmierci, tak samo jak nikt nie widział jego ciała. Po prostu zniknął kilka miesięcy temu. Od tego czasu jest tak samo jak z Shark, ani śladu. Ale w przeciwieństwie do Stevena, Nathan nie miał powodu, by się ukrywać. Z tego powodu wszyscy uznali, że zginął w selwie. Gdyby nie to, nie zgodziliby się wybrać Jackmana na jego miejsce.";
			link.l1 = "Co do diabła robił Hawk w selwie?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "To moja wina, jestem starym głupcem! Namówiłem go, by zajął się nowo przybyłymi bandytami. Nie mam pojęcia, kim są i kto jest ich szefem. Normalnie bym się nie przejmował, ale zaczęli porywać przyjaznych Miskitów. Ich wódz wojenny Kumvana zagroził wypowiedzeniem Wojennej Ścieżki i poprosił mnie o pomoc. Nie miałem wyboru, musiałem interweniować.\nHawk wylądował z małym oddziałem na Wybrzeżu Moskitów, wpadł w doskonale zorganizowaną zasadzkę i został pokonany. Wyglądało na to, że jego i jego ludzi oczekiwano na lądzie. Ciała Hawka nie znaleziono wśród innych w dżungli.";
			link.l1 = "Masz wszelkiego rodzaju wybryki dziejące się tuż pod nosem! Żaden z ludzi Hawka nie próbował poradzić sobie z bandytami?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman wszystkich ubiegł. Sam zgłosił się, by rozwiązać problem na radzie Bractwa i podjął decyzję. Miskitos przestali znikać, ale bandyci tam zostali, trzymając się względnie z dala.\nJackman powiedział, że nie trzymają w niewoli nikogo z tych, którzy próbowali ich zaatakować, i nie ma powodu, by Bractwo wypowiadało im wojnę. Hawk zaatakował ich pierwszy, więc zgodnie z naszymi prawami, bandyci mieli prawo do obrony. Wszyscy się zgodzili. Wszyscy oprócz...";
			link.l1 = "Wszyscy, ale kto?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan miał żonę. Nazywa się Danielle Hawk i to twarda suka! Wątpię, by kiedykolwiek pogodziła się ze stratą swojego kapitana, nie mówiąc już o tym, że podejrzewała coś od samego początku i próbowała zniechęcić Hawka. Pamiętam, że mieli o to ogromną kłótnię, ale to nie było nic nadzwyczajnego dla nich.";
			link.l1 = "A gdzie jest teraz Danielle?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Kto wie! Jackman upewnił się, że opuściła Maroon Town. Nie odwiedza mnie. Nigdy się nie lubiłyśmy, a ona stała się jeszcze bardziej jędzowata przez te lata, i teraz pewnie naprawdę mnie nienawidzi, bo prawdopodobnie wierzy, że to ja jestem przyczyną jej nieszczęść.\nByć może szuka Hawka na własną rękę, ale co może zrobić jedna kobieta, nawet jeśli nosi spodnie i szablę! Tak przy okazji, opanowała sztukę posługiwania się szablą. Nie polecam jej sprawdzać, jeśli ją spotkasz. Tak, i nie ma sensu rozmawiać z bandytami. Założyli tam bardzo imponujący obóz i są uzbrojeni po zęby.\nWygląda na to, że to byli wojskowi i dobrze znają swój fach. Nie wpuszczają nikogo na swoje terytorium. Mówią, że Hiszpanie kiedyś wydobywali tam złoto. Ale złoto się wyczerpało i porzucili kopalnię. Nie mam pojęcia, co te dranie tam robią.";
			link.l1 = "Cóż, skoro nikt nie widział ciała Jastrzębia, nadzieja na odnalezienie go żywym wciąż się tli. Bóg jeden wie, może nawet przywrócimy go do baronatu.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Tak, co o tym sądzisz. Weź ten list. Kiedy spotkasz Steve'a Dodsona, przekaż mu go od razu. Zawartość tego listu zagwarantuje twoje bezpieczeństwo. Cóż, na wszelki wypadek.";
			link.l1 = "Dzięki, Janie. Z pewnością to zrobię!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "No cóż, dlaczego taka smutna mina. Zmęczony? Może kieliszek rumu dla ciebie?";
			link.l1 = "Nie miałbym nic przeciwko...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Proszę, weź kielich. Teraz mów.";
			link.l1 = "(pijąc) Ach, to znacznie lepsze... No cóż, Janie, ty i Czarny Pastor mieliście rację. Wyspa Sprawiedliwości istnieje. Byłem tam.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "Mówiłem ci, że tam miała być baza przemytników!";
			link.l1 = "Tak naprawdę nie ma żadnej bazy. Plotki po Karaibach nie kłamały. Czarni i biali rzeczywiście tam żyją razem, z pewnością niekoniecznie w pokoju, ale bardziej jak koty i psy. A sama wyspa składa się z niezliczonej ilości wraków statków.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "Nie mogę w to uwierzyć! Jose Dios na pewno będzie bardzo zainteresowany usłyszeniem twojej opowieści, jestem tego pewien. Odwiedź go któregoś dnia, tak przy okazji.";
			link.l1 = "Odwiedzę go później. To nie jest najlepszy czas na to teraz. Mam teraz ważniejsze sprawy do załatwienia. Znalazłem Nathaniela Hawka na Wyspie.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "Znalazłeś Nathana? To niezwykłe! Jak się ma?";
			link.l1 = "No cóż... Jest chory, ciągle pijany i głęboko przygnębiony.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "Do diabła, to zniechęcające. Gdzie on jest? Na twoim statku?";
			link.l1 = "Nie, jest na swoim statku. Na wyspie.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "Cóż, nie przyprowadziłeś go tutaj? Dlaczego?";
			link.l1 = "Ponieważ nie było nic, co mogłoby go powstrzymać. Dostałem się na wyspę bez statku.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "Do diabła, "+pchar.name+", ledwie wypiłeś szklankę rumu, a gadasz brednie, jakbyś się upił do nieprzytomności. Co, przepłynąłeś cały Karaib? Albo przytwierdziłeś sobie żółwie do stóp?";
			link.l1 = "Nie, nie płynąłem. Janie, dostałem się na wyspę prosto z dżungli Głównego, tak jak Nathan, przez magiczny indiański idol. Opowiadałem już tę historię tylu ludziom i mam dość udowadniania, że nie zwariowałem, więc wszystko, co mam do powiedzenia, to: po prostu mi uwierz, dobrze!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Indyjski idol?";
			link.l1 = "Na Karaibach znajdują się co najmniej trzy posągi znane jako statuy Kukulkana: jeden w pobliżu wioski Miskito na West Main, drugi na dnie płytkich wód wyspy Justice, a trzeci w wiosce Karibów na Dominice. Te idole, dzięki pomocy indiańskiej magii, są zdolne do natychmiastowego przenoszenia ludzi w czasie i przestrzeni.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "Przeszedłem przez wszystkie trzy posągi w okręgu i wyszedłem dokładnie tam, gdzie zacząłem swoją podróż w wiosce Miskito. Jeśli mi nie wierzysz, mogę zawołać Danielle. Ona widziała wszystko na własne oczy!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle? Żona Hawka? Była z tobą?";
			link.l1 = "Po części tak. Znalazła mnie sama w Błękitnym Porcie i przyprowadziła do wioski Miskito, do szamana, który wysłał mnie do magicznego posągu. Teraz służy jako jeden z moich oficerów, tymczasowo oczywiście.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Jestem absolutnie zdumiony, "+pchar.name+"! To dokładnie tak, jak mówią Anglicy. Urodziłeś się w czepku, szczęściarzu! Dobra, uwierzę ci, chociaż trudno w to uwierzyć. Ale sprawa z Nathanem pozostaje bez zmian, trzeba mu pomóc.";
			link.l1 = "Tak właśnie zamierzam uczynić. Przygotowuję wyprawę na Wyspę Sprawiedliwości. Teraz mam wszystko, czego potrzebuję: współrzędne wyspy i kierunki żeglugi.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fantastycznie.  Czy mogę jakoś ci pomóc?";
			link.l1 = "Nie, dzięki. Ale pominąłem jeden drobny szczegół. Oprócz Nathana, znalazłem na wyspie także Rekina Dodsona.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "Więc naprawdę tam poszedł! No cóż, "+pchar.name+", wykonałeś świetną robotę. Jak tam Dodson sobie radzi? Rozmawiałeś z nim oczywiście, prawda?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "Nie tylko z nim rozmawiałem. Staliśmy się również przyjaciółmi. To on dał mi wskazówki żeglarskie, których będę potrzebował, by wrócić na wyspę. Steven zgodził się zamienić kabinę swojego okrętu wojennego na rezydencję w Sharptown.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Rozmawialiśmy, tak, ale ostatecznie okazało się to bezużyteczne. Steven został zabity, gdy przebywałem na Wyspie, kiedy w życie weszła zmowa zorganizowana przez jego bosmana, Chada Kappera.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Hah! A jak to się stało, że Rekin został kapitanem okrętu wojennego?";
			link.l1 = "Statek od ponad pół wieku tkwi w niekończącej się 'ciszy'. Jest uwięziony ze swoimi ludźmi na Wyspie. Dlatego nie pokazywał się na Karaibach przez tak długi czas. W każdym razie, wkrótce go tu przyprowadzę, a on sam opowie ci o swoich przygodach.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "Nie mogę się tego doczekać! Teraz sprawy zaczynają się poprawiać. Właśnie staliśmy się potężniejsi, "+pchar.name+"Kiedy zamierzasz wrócić na Wyspę?";
			link.l1 = "Teraz. Właśnie wszedłem tu na chwilę, żeby opowiedzieć ci o nowinach, podczas gdy Danielle przygotowuje się do wyprawy. Umiera z tęsknoty za swoim Nathanem. I wiesz co, Jan, nie jest aż taką suką.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "Tak?  Cóż, może nie miałem do końca racji co do niej. Dobrze, "+pchar.name+", nie będę cię dłużej zatrzymywać. Idź i niechaj szczęście ci sprzyja! Będę wyczekiwał twojego powrotu.";
			link.l1 = "Do zobaczenia, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper? Cholera, znałem tego gościa. Zabił Stevena? Ten drań...";
			link.l1 = "Kapper nie żyje. Ale nie możemy przywrócić Stevena, więc musimy pomyśleć o sposobie kontynuacji organizacji naszej polityki.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Hah! To szkoda... Cóż tu do rozmyślania? Musimy po prostu przekonać Tyrexa, aby stanął na czele Bractwa. Poza tym, po Blaze'u, Tyrex jako strażnik Kodeksu, jest naszą najbardziej szanowaną postacią. Ale najpierw musimy sprowadzić Hawka, aby przynajmniej mieć jednego asa w rękawie. Kiedy wyruszasz na Wyspę?";
			link.l1 = "Teraz. Właśnie wpadłem tutaj na chwilę, by opowiedzieć ci o nowinach, podczas gdy Danielle przygotowuje się do wyprawy. Umiera z chęci, by zobaczyć się z Nathanem. I wiesz co, Jan, ona wcale nie jest taką suką.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "Jak się on miewa? Mówiłeś, że nie czuł się dobrze.";
			link.l1 = "Tak, dokładnie tak. Wezmę go ze sobą, by otrzymał leczenie w wiosce Miskito u Wężowego Oka, szamana.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Zatem nie ma czasu do stracenia! Pospiesz się, "+pchar.name+"Jak tylko dostarczysz Nathana do swojego szamana, wracaj natychmiast do mnie.";
			link.l1 = "Dobrze, Jan. Brzmi jak plan.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Bardzo dobrze. Steven już mnie odwiedził. Teraz możemy wreszcie kontynuować omawianie naszych planów.";
					link.l1 = "Zamieniam się w słuch, Janie.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "Oczywiście to miłe, ale dlaczego Dodson jeszcze do mnie nie przyszedł? Co, zostawiłeś go na wyspie?";
					link.l1 = "Hm... Śpieszyłem się, by przyprowadzić Nathana do Wężowego Oka...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Bardzo dobrze. Moje serce płacze za Rekinem. Ale takie jest życie, więc Tyrex zajmie jego miejsce. No dobrze, teraz możemy w końcu kontynuować omawianie naszych planów.";
				link.l1 = "Słucham cię uważnie, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... i zapomniałeś zabrać Rekina? Nie mogę w to uwierzyć, "+pchar.name+"Zabierz Stevena do Blueweld teraz! Słyszysz mnie? Ruszaj!";
			link.l1 = "Spokojnie, Jan. Zajmę się wszystkim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven przyszedł mnie odwiedzić. Teraz wreszcie możemy kontynuować dyskusję o naszych planach.";
				link.l1 = "Zamieniam się w słuch, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Och, "+pchar.name+"... Wygląda na to, że ostatnio za dużo rumu pijesz. Widzisz, to nigdy się dobrze nie kończy. Najpierw ręce zaczynają ci się trząść, potem tracisz pamięć, a potem dostajesz czarną plamkę...";
				link.l1 = "Zrozumiałem, Janie. Od razu ruszam po Stevena!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "Czarny Pastor wyraził się bardzo jasno, interesuje go tylko ta teologiczna książka. Wysłałem moich ludzi, aby jej poszukali, być może ktoś ją znajdzie. Marcus Tyrex nie stanowi problemu, nie będziemy mieli trudności z przekonaniem go. Jackman opuścił Maroon Town wkrótce po twojej wizycie. Odpłynął gdzieś na 'Centurionie', fregacie Jastrzębi.\nPozostał tylko Barbazon - znany także jako Jacques Dobroduszny. Musimy znaleźć sposób, by skłonić go do współpracy z nami. Nie jestem jeszcze pewien, jak to zrobić. Ale jedno jest oczywiste - powinieneś go odwiedzić.";
			link.l1 = "Opowiedz mi o Barbazonie."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Tajemniczy typ. Udaje biednego, a jednak może być najbogatszym człowiekiem na Karaibach. Kontroluje wszystkie operacje przemytnicze Wschodu. Gdyby nie Marcus stawiający mu opór, rządziłby całym przemytem na Wyspach Nawietrznych. Tyrex to jak kość w jego gardle.\nZawsze kłócą się na radzie, ale Barbazon nie ma jaj, by ogłosić otwartą wojnę. Może naprawdę kiedyś był piratem z Dunkierki, jak twierdzi, ale teraz bardziej przypomina mi lichwiarza.";
			link.l1 = "Jak do cholery został wybrany na barona?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Złoto, mój przyjacielu, rządzi wszystkim i wszędzie, kto ma złoto, ten tworzy zasady. Poza tym, Barbazon jest naprawdę dobry w wymyślaniu wszelkiego rodzaju dochodowych i nielegalnych operacji. Sam w nich nie uczestniczy, ale zawsze bierze udział w zyskach. Dlatego ma wokół siebie stale wielu odważnych zbirów, którzy są głównie słabi na umyśle. Bez niego wszyscy oni po prostu umarliby z głodu albo skończyli na szafocie.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Przypomina mi Marcusa... Jan, sprawa jest taka... Nie mam pojęcia, jak podejść do Barbazona. Jest problem, o którym nie wiesz.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "Jak dostanę się do Barbazon?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Po prostu udawaj jednego z tych głupców, którzy potrzebują cynku na tłustą robotę. Nawet nie próbuj go oszukać co do jego udziału. Dobrotliwy Barbazon nie wybacza.";
			link.l1 = "To się rozumie samo przez się. Nie angażuję się z nim dla własnej korzyści. W każdym razie, czas go odwiedzić.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Doprawdy? Mów.";
			link.l1 = "Słyszałeś kiedyś o Charlie Prince?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Tak, słyszałem plotki. Ten facet pracował dla Marcusa Tyrexa niezbyt dawno temu. Zrobił całkiem sporo w bardzo krótkim czasie, zasłynął plądrując Kartagenę. I co z tego?";
			link.l1 = "„Ten facet to ja. Jestem Charlie Prince. Byłem. Widzisz teraz?”"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Cholera jasna! Jesteś Charlie Prince? Co za zwrot akcji!"+pchar.name+", jestem pod wrażeniem! Teraz widzę, skąd pochodzi Twój uścisk... Ale co z tym ma wspólnego Barbazon?";
			link.l1 = "Jak by to było, gdyby Książę złożył wizytę Barbazonowi, Jan?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... Rozumiem. Miałeś z nim wcześniej do czynienia?";
			link.l1 = "Nie do końca. Jeden z jego pachołków o imieniu Ignacio Marco próbował mnie załatwić na bezpośredni rozkaz Barbazona. To była część ich małej wojny."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "Widział twoją twarz? Przedstawiłeś mu się?";
			link.l1 = "Nie."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Nie widzę tu problemu. Słyszałem też o korsarzu Charliem Prince, ale nie wiedziałem, że to ty, dopóki mi nie powiedziałeś.";
			link.l1 = "Ty myślisz, że Barbazon mnie nie przejrzy?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "Jakże mógł, skoro nigdy nie widział twojej twarzy? Wszystko, co zrobił, to wydanie rozkazu pozbycia się jednego z pracowników Marcusa.";
			link.l1 = "Hm... Możesz mieć rację w tej kwestii."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "Nie ma mowy, żebyśmy z tego wybrnęli bez Barbazona. Idź do niego, ale bądź ostrożny. Uciekaj, jeśli cię rozpozna, w takim przypadku wymyślimy inny sposób, żeby się do niego zbliżyć.";
			link.l1 = "Dobrze. Powinienem już iść. Nie mogę się doczekać, aż spotkam tego drania."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Nie udawaj głupka i nie próbuj oszukać Jacques'a. On nigdy nie wybacza. Zachowuj się jak idiota, który pragnie łatwego zarobku.";
			link.l1 = "Moja ulubiona rola, jak się zdaje... Żegnaj, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Tak. Szaman indiański dał z siebie wszystko, Hawk jest jak nowy. Powinien już być w Maroon Town z Dannie, więc jeśli chcesz, idź i przywitaj się. Byłoby im bardzo miło cię zobaczyć.";
			link.l1 = "Na pewno wpadnę, żeby zobaczyć, jak sobie radzą... Janie, udało mi się znaleźć drugą część mapy Sharpa! Była w kajucie Jackmana. Teraz nie będziemy mieć problemu z udowodnieniem praw Helen do Isla Tesoro.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Świetnie, pokaż mi to.\nMieliśmy rację, to Jacob zabił Blaze'a. Teraz plama na imieniu Shark ma być na dobre usunięta. Jeśli chodzi o dowody, to bardziej delikatna sprawa. I należy się do niej zabrać dopiero po bardzo dokładnym rozważeniu.";
			link.l1 = "Inna sprawa, Janie. Spójrz na tę notatkę. To również było wśród rzeczy Jackmana.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Cóż, spójrzmy... Ha, więc dlatego bandyci słuchali Jackmana i przestali porywać Miskitosów! Nie mogło być inaczej! Ten drań wszystko zaplanował i był o kilka kroków do przodu.";
			link.l1 = "Tak, i widzę, dlaczego ludzie Hawka zostali wyrżnięci. Ale są dwie rzeczy, których nie rozumiem: po pierwsze, co robią wspólnicy Jackmana w kopalni, a po drugie, dlaczego reagujesz tak spokojnie na fakt, że cały ten bałagan dzieje się na twoim terenie?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Wstyd mi... Masz rację. Jackman naprawdę wymknął się spod kontroli. A jego pachołki nie mają czego szukać na moim terenie. Wygląda na to, że nadszedł czas, by przypomnieć Karaibom, z kim mają do czynienia.";
			link.l1 = "Co masz na myśli, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Ożywiając przeszłość... Zamierzam zorganizować ekspedycję karną i wyeliminować każdego bandytę w kopalniach. Teraz mamy dowody, że to ludzie Jackmana i jestem zobowiązany oczyścić moje terytoria z tego ścierwa.\n"+pchar.name+", wykonałeś doskonałą robotę. Czas, żebym wziął się do roboty. Ty teraz odpocznij. Odwiedź Jastrzębi. Wróć za dziesięć dni!";
			link.l1 = "W porządku, Jan. Zrobię to. Wrócę dokładnie w czasie, który powiedziałeś!";
			link.l1.go = "saga_31";
			link.l2 = "Ha! I ja chcę wziąć udział w tej krucjacie. Dlaczego postanowiłeś wysłać mnie na czas rekreacji?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Przebacz mi, stary druhu. Pomyślałem tylko, że może w końcu nadszedł czas, bym wziął się do roboty, a ty żebyś odpoczął. Ale jeśli taka jest twoja wola, będę więcej niż szczęśliwy! Stawmy czoło burzy razem! A wszystko, co znajdziemy w kopalni, podzielimy równo między nasze załogi, jak zapisano w prawach Bractwa.";
			link.l1 = "Umowa stoi, Jan! Kiedy wyruszamy?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Przybądź ze swoimi ludźmi na Wybrzeże Moskitów za trzy dni. Do tego czasu zbiorę swoją ekipę i będę już czekać na ciebie. Nie spóźnij się!";
			link.l1 = "W porządku, Diable Leśny. Już palę się do walki z tobą ramię w ramię! Do zobaczenia wkrótce!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Doskonale. Wywęszyłem coś o tajemniczym właścicielu kopalni, Lawrence Beltrope.";
			link.l1 = "Więc, kim jest ten ptaszek?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Wyciągnąłem to z popleczników Jackmana w kopalni. Okazali się twardymi orzechami do zgryzienia, ale moi ludzie też nie urodzili się wczoraj. Na dodatek, udało nam się uśpić ich czujność po podaniu hasła z notatki, którą znalazłeś. Przeniknęliśmy do kopalni i zgotowaliśmy im efektowne pożegnanie.";
			link.l1 = "Przejąłeś kopalnię? Znakomicie!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Niech to będzie lekcja dla każdego, kto myśli, że Diabeł z Lasu zardzewiał. Naprawdę zbyt dużo się obijałem w ostatnich latach i co się stało? Jackman rozwijał swój nikczemny plan tuż pod moim nosem!";
			link.l1 = "Co widziałeś w tej kopalni? Opowiedz mi o tym!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "Kopalnia została rzeczywiście opuszczona przez Hiszpanów, jednak Lawrence Beltrope z Port Royal kupił ją za grosze i potajemnie kontynuował eksploatację. Najwyraźniej Hiszpanie porzucili szyb zbyt wcześnie, ponieważ chociaż sami nie znaleźliśmy tam złota, znaleźliśmy kilku niewolników, którzy twierdzili, że jeszcze do niedawna można było tam znaleźć złoto.";
			link.l1 = "Lawrence Beltrope? Nigdy o nim nie słyszałem. Kim on jest?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "On jest miejscowym tubylcem, synem Thomasa Beltrope'a, dawno temu przysięgłego brata Nicholasa Sharpa i korsarza Providence Island Company. Sam bardzo dobrze znałem Thomasa. Rok temu, Lawrence ponownie przybył na Karaiby. Okazuje się, że Jackman dla niego pracował. Miej to na uwadze i miej oczy szeroko otwarte!";
			link.l1 = "Więc tajemniczym 'szefem' Jackmana, wspomnianym w tym liście, jest Lawrence Beltrope... Dobrze, zapamiętam to imię.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Jeszcze jedna rzecz. Przypominam sobie coś dziwnego. Blaze kiedyś wspomniał o opuszczonej hiszpańskiej kopalni złota i że zamierzał zainwestować jej złoto w Sharptown. Ale mapa kopalni zniknęła po tym, jak jego siostra uciekła z kapitanem Rzeźnikiem. Może mówił o naszej kopalni?\nNieważne, to było tak dawno temu i niewiele to zmienia... Ty i ja powinniśmy zająć się Radą. Masz wszystkie pięć odłamków?";
			link.l1 = "Tak. Ci czterej: Nathaniel, Tyrex, Marlow i Barbazon. Wszyscy oni wyrazili zgodę.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Wspaniale. Jestem pewien, że nie będzie żadnych problemów z wyborem "+sTemp+" jako głowa Bractwa Wybrzeża. Natychmiast zacznę pracować nad zwołaniem spotkania Rady.";
			link.l1 = "Więc Janie, możemy uznać, że na razie wszystkie problemy mamy pod kontrolą? Nathaniel jest w Maroon Town, Jackman nie żyje, a Bractwo ma nowego przywódcę... Może nadszedł czas, aby wrócić do punktu wyjścia, czyli przejąć Tortugę?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Pamiętam, "+pchar.name+", ale musimy trochę poczekać. Na dodatek, czas na uporządkowanie dziedzictwa Sharpa się kończy, a ta kwestia, jak wiesz, musi być poważnie załatwiona.";
			link.l1 = "Co jest nie tak ze spadkiem? Mam obie części mapy. Wystarczy je przedstawić i to wszystko...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Rozumiem, proszę podać tekst, który należy przetłumaczyć."+pchar.name+", zapewniam cię, że w dzisiejszych czasach nie rozdają wysp tak po prostu. Nawet prawowitym spadkobiercom z każdym paragrafem testamentu spełnionym. Angielskie władze pragną tej wyspy bardzo, jestem tego świadomy.\nNie sądzę, żeby pułkownik Doyle bezczynnie patrzył, jak odbieramy mu wyspę, którą już uważa za angielską własność. Również ty i ja powinniśmy pozostać w cieniu.";
			link.l1 = "A co sugerujesz?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Udaj się do Port Royal i znajdź tam człowieka imieniem Albert Loxley. To najlepszy prawnik w całych Karaibach. Stał się niezwykle biegły w podejrzanych sprawach wszelkiego rodzaju, więc podejmie się każdej pracy, jeśli zaoferujesz mu za nią wygórowaną opłatę. Ma królewskie apetyty, ale jest tego wart.";
			link.l1 = "Czy myślisz, że testament Sharpa może zawierać jakieś pułapki?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "Nie tylko tak myślę, jestem tego pewien. Czy kiedykolwiek musiałeś prowadzić interesy z urzędnikami? Wiedz, że jeśli czegoś od ciebie chcą, wyciągną twoją duszę, wskażą ci nos na źle postawiony przecinek, zinterpretują wszystko tak, jak im to pasuje, i zostawią cię nagiego jak ślepego kociaka.\nDlatego powstały prawnicy. Walczą z urzędnikami ich własną bronią - gadulstwem, rozlewaniem atramentu i krętactwem. Dlatego powinieneś odwiedzić Loxleya i zatrudnić go, aby chronił nasze interesy, podczas gdy ja zajmę się wyborami.";
			link.l1 = "Dobrze. Wyruszam do Port Royal. Ile czasu zajmie, zanim Rada się zbierze i przeprowadzi wybory?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = " Dziesięć dni. Więc nie fatyguj się szukaniem mnie w Blueweld wcześniej.";
			link.l1 = "Zrozumiano. Cóż, Janie. W takim razie, do zobaczenia za chwilę!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = " "+sTemp+" przesyła najcieplejsze pozdrowienia. Zawsze będzie się cieszył z twojej wizyty w jego rezydencji na Isla Tesoro. Odwiedź go, jeśli nadarzy się okazja.";
			link.l1 = "By upewnić się "+sTemp+" nie opuści swojej nowej rezydencji, ty i ja, Janie, mamy przed sobą trochę roboty.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Rozumiem, że już odwiedziłeś Loxleya...";
			link.l1 = "Tak, mam. Zajął się naszą sprawą, ale zażądał sterty złota za swoje usługi."+sTemp+"  dublony z góry. Z góry! A będziemy musieli zapłacić mu jeszcze więcej, w zależności od tego, jak dobrze pójdzie dowód praw Helen. Kwota się podwoi lub potroi, jak powiedział.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ha! Cóż, nie spodziewałem się niczego innego po starym szulerze jak on. Wywęszy ofiarę z daleka, niczym hiena. Oczywiście, mówimy tu o całej wyspie. Śmieszne byłoby myśleć, że Albert nie poprosi o kilkaset. Tak więc, całkowita suma może wynosić około tysiąca pięciuset złotych...";
			link.l1 = "Jan, to kupa pieniędzy!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "Wiem, do czego zmierzasz. Zgadzam się, że nie jesteś jakimś głupim gorylem, który płaci to wszystko z własnej kieszeni. Ale niestety, w tej chwili nie mam tyle złota ukrytego. Planowałem na takie wydatki, jednak interwencja jednego łotra zrujnowała wszystko.";
			link.l1 = "O czym ty mówisz?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Słuchaj. Być może już wiesz, że nasza osada jest tylko w połowie legalna. Anglicy trzymają tu garnizon, a my dostarczamy im mahoniu za dobrą cenę. Ale jest jeszcze jeden bardzo ciężki i trwały rodzaj drewna - Lignum Vitae, które powinieneś znać jako żelazne drzewo.\nJest rzadkie i trudne do obróbki nawet przy użyciu hartowanej stali. Mówią, że dawno temu Majowie-Itza używali go do produkcji swoich strasznych maczug. Nie można kupić żelaznego drewna na otwartym rynku, a przemycane kosztuje tyle, co waży w srebrze.\nLudzie Doyle'a czasami przychodzą i kupują całą ilość, którą przetworzyliśmy, za taniochę. Ale zawsze udaje mi się zaoszczędzić trochę na własne potrzeby.";
			link.l1 = "Słyszałem o tym drzewie. Mówią, że kule muszkietowe wnikają w jego oleiste drewno niczym smoła! Jego solidność jest wystarczająca, by tworzyć z niego tryby do stalowych mechanizmów.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "Kłamią trochę o sprzęcie, ale reszta się zgadza. Przewidując wydatki, przygotowałem dużą partię żelaznego drewna, ale jakiś drań opróżnił mój magazyn kilka dni temu. To ktoś z nas, wiem to. Mam podejrzenia, ale nie mogę powiedzieć na pewno.";
			link.l1 = "Szczury trzeba rozdeptać! Kogo podejrzewasz?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. Jego wschodnioindyjski 'Oyster' wypłynął wczoraj na Barbados. Nie miałem okazji sprawdzić jej ładowni. Ale i tak nie przyniósłby żelaznego drewna do Bridgetown, lord Willoughby ma tam poważnych celników, a żelazne drewno to surowiec o strategicznym znaczeniu dla angielskiej marynarki.\nJeśli naprawdę ma moje żelazne drewno, to sprzeda je przed dotarciem do Bridgetown. Gdybyś tylko mógł przechwycić Molligana i sprawdzić jego ładownie!..";
			link.l1 = "Mówisz, że wczoraj odpłynął do Bridgetown? Jeszcze nie wszystko stracone. Spróbuję go dogonić.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "Wiesz, co robić, jeśli Molligan to szczur. Ale spróbuj najpierw poznać imię jego klienta. Potem możesz albo dostarczyć ładunek klientowi osobiście, albo zwrócić go mnie.\nPrzyprowadź też 'Oyster' do Blueweld, to dobry statek, chciałbym go wziąć dla siebie i przystosować do własnych potrzeb. Wolno ci wziąć, co tylko zechcesz jako łup... A jeśli Molligan nie jest winny... nie, jestem pewien, że to on jest szczurem, który ukradł moje żelazne drewno.";
			link.l1 = "Zrobię dobry użytek z mego czasu!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Jeśli sam sprzedasz żelazo drzewne, odłóż tysiąc pięćset złotych dublonów dla Loxleya, a resztę podzielimy na pół. Mogę na tobie polegać, prawda?";
			link.l1 = "Oczywiście. Nie jestem szczurem.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "Nie mam wątpliwości. Powodzenia, "+pchar.name+" ! Mam nadzieję, że tym razem los się do ciebie uśmiechnie.";
			link.l1 = "Dziękuję. Do zobaczenia później!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Wiedziałem. Ile miał w ładowniach?";
			link.l1 = "Znalazłem "+FindRussianQtyString(sti(npchar.quest.bakaut))+" na 'Ostrydze'.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Łał! Nigdy nie miałem tyle w moim magazynie. Spójrz, kto tu dorwał się do fortuny. Dziękuję, "+pchar.name+", nigdy mnie nie zawiodłeś. Natychmiast sprzedam towar, już mamy kupca. Będę miał dla ciebie pieniądze jutro.";
				link.l1 = "Dobrze. Nie będę cię dłużej rozpraszał. Do zobaczenia jutro.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Tak, miałem już tego dość. Mały szczur! Dziękuję, "+pchar.name+", nigdy mnie nie zawiodłeś. Sprzedam towar od razu, już mamy kupca. Będę miał dla ciebie pieniądze jutro.";
				link.l1 = "W porządku. Nie będę cię dłużej rozpraszać. Do zobaczenia jutro.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Najpewniej już zdążył sprzedać część ładunku komuś, bo powinno być tego więcej. Ale to nic wielkiego, odzyskaliśmy większość. Dzięki, "+pchar.name+", Sprzedam towar od razu, już mamy kupca. Będę miał dla ciebie pieniądze jutro.";
				link.l1 = "Dobrze. Nie będę cię dłużej rozpraszał. Do zobaczenia jutro.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Do diabła, ten drań zdążył już sprzedać sporą część ładunku... Ach, szkoda. No cóż. Sprzedam to, co mam, już mam kupca. Jutro będę miał pieniądze.";
				link.l1 = "W porządku. Nie będę cię więcej rozpraszać. Do zobaczenia jutro.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "Do diabła, to godne pożałowania! Ten drań zdołał sprzedać już ponad połowę ładunku... Ach, to niedobrze. No cóż. Sprzedam to, co mam, już znalazłem kupca. Będę miał pieniądze jutro.";
				link.l1 = "W porządku. Nie będę cię już dłużej rozpraszał. Do zobaczenia jutro.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Człowieku, po prostu mam pieprzonego pecha. On sprzedał prawie wszystko... Trzymaj dla siebie to żelazne drewno, "+pchar.name+", rób z tym, co chcesz. Jesteś teraz moją jedyną nadzieją na zarobienie pieniędzy.";
			link.l1 = "Zrozumiałem. Dobrze, poszukam sam. To nie pierwszy raz, kiedy to robię... Żegnaj, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Zaczekaj! Czy przechwyciłeś 'Ostrygę'?";
			if (iUst == 1)
			{
				link.l1 = "Tak. Ona jest teraz w porcie. Zacumowałem ją dla ciebie, tak jak prosiłeś.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "Nie. Statek był tak poważnie uszkodzony podczas bitwy, że musiałem go zatopić.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Jaka szkoda. Ale co zrobisz, tak to już jest. Do zobaczenia później, "+pchar.name+"!";
			link.l1 = "Żegnaj, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Znakomicie! Wyposażę tę piękność tak, jak na to zasługuje. A później zawsze możesz pożyczyć ją na jakiś czas, tak jak się umówiliśmy. Myślę, że za około dwa miesiące będzie gotowa.";
			link.l1 = "Dobrze. Statek taki jak ten mógłby czasem naprawdę się przydać... Do zobaczenia później, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "Otrzymałem "+iTemp+" monet za to. Tysiąc pięćset to dla prawnika, plus twój udział w dublonach - "+idlt+"Oto masz.";
				link.l1 = "Chwalebne! Teraz mogę bez trudu wyruszyć do Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "Otrzymałem za to tysiąc pięćset doblonów. To akurat wystarczy dla prawnika. Proszę, oto one.";
				link.l1 = "Fantastycznie. Teraz mogę ruszyć do Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "Otrzymałem "+iTemp+"  дублонów za to. Proszę bardzo. Resztę będziesz musiał wykopać sam.";
			link.l1 = "Cóż, jeśli sam, to sam. Dobrze, wyruszam spotkać się z Loxleyem.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "A co powiesz na to? To interesujące. A ile Holender jest skłonny za to zapłacić?";
			link.l1 = "Czterdzieści doublonów za sztukę.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Ho! Moi kupcy płacą mniej...";
			link.l1 = "Ostatecznie, mam dwa tysiące złota dla Loxley'a i "+sti(npchar.quest.bakaut_sum)*2+"   doublony na dodatek.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Dobrze więc. Podzielimy to na pół.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Oto i masz. Mam "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Zostawiłem doblony na statku. Szybko tam skoczę i zaraz wracam.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Wesoło, dobrze. Ile przyniosłeś?";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Proszę bardzo. Mam "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Co się dzieje z moją pamięcią! Czas przestać zabawiać się tym rumem. Znowu zostawiłem   дублоны w mojej skrzyni. Szybko tam pobiegnę i je przyniosę.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Dobra robota, "+pchar.name+" ! Po raz kolejny przypomina mi się, że jesteś dobrą osobą do współpracy.";
				link.l1 = "Próbuję, Janie...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Świetnie. Czy przyniesiesz pozostałe "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+"  dublonów później?";
				link.l1 = "Tak. Po prostu nie mogłem przewieźć takiej ogromnej sterty złota za jednym razem.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Więc, "+pchar.name+", jak tam moje doubloony?";
			link.l1 = "Jestem gotów dać ci trochę więcej złota.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "Mam dla ciebie propozycję. Skoro udało ci się znaleźć dochodowego kupca, to mógłbym sprzedać ci trochę żelaznego drewna. Kiedyś dostawałem trzydzieści dublonów za sztukę. Jeśli chcesz, możesz je ode mnie kupić za tę cenę. Wolę sprzedać tobie niż komuś innemu.";
			link.l1 = "Ile żelaznego drewna jesteś w stanie sprzedać?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "Unikam zbierania dużych partii. Molligan's był wyjątkiem. Władze nie będą zadowolone z wieści o lokalnym czarnym rynku. Więc oto umowa: Będę odkładał 25 sztuk żelaznego drewna dla ciebie każdego 14-go i 24-go dnia miesiąca.\nJeśli chcesz je kupić, przynieś siedemset pięćdziesiąt dublonów i zabierz całą partię. Jeśli nie pojawisz się tego dnia, sprzedam to innemu klientowi. W ten sposób będziesz mógł mieć 50 sztuk miesięcznie. Umowa?";
			link.l1 = "Umowa stoi, Janie! Zróbmy to. Teraz czas, żebym ruszał...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ach, więc albo to nie był on, albo już wcześniej sprzedał żelazne drewno... Co za szkoda. No cóż, jesteś teraz moją jedyną nadzieją na zdobycie pieniędzy dla prawnika.";
			link.l1 = "Będę gotów przyjąć tę odpowiedzialność. To nie moje pierwsze rodeo.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "Czyżby tak? To ciekawe. Śmiało, pytaj. O kim chcesz porozmawiać?";
			link.l1 = "O dziewczynie. Miała na imię... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Hm. Czy nowa przywódczyni naszych Braci mówiła ci o niej?";
			link.l1 = "On też tak zrobił. Ale dowiedziałem się o niej od Bakera, starego kata z St. John's. Tego samego człowieka, który wykonał egzekucję kapitana Butchera.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Zgoda. Hm. Cóż, minęło ponad dwadzieścia lat odkąd ostatni raz widziałem Jessicę. Co o niej wiesz?";
			link.l1 = "Cóż, wiem, jak skończyła z kapitanem Rzeźnikiem i jak razem piratowali. Wiem, że zostawił ją dla Beatrice. Później ona zemściła się na nim za to z pomocą jakiegoś Joshua Leadbeatera, znanego również jako Maska...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "Również wiem, że ty, Janie, wybacz moją szczerość, interesowałeś się Jessicą. To jest powód, dla którego przyszedłem do ciebie. Jessica jest ważną postacią w moich poszukiwaniach. To ona zamordowała Beatrice Sharp, z zazdrości, o ile rozumiem.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "„Cóż, wiesz wiele. Tak, rzeczywiście zalecałem się do Jess, ale to nie było zaskoczenie, wszyscy piraci z Isla Tesoro byli wtedy podzieleni na dwie grupy: tych, którzy chcieli przelecieć Beatrice i tych, którzy chcieli Jessicę.\nDobrze ją pamiętam... Była piękna, bardzo piękna!..”";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "Była wyjątkowa... Jest również całkiem prawdopodobne, że Jess zabiła Beatrice. Po tym jak Rzeźnik wyrzucił ją z 'Neptuna', prawdopodobnie nie myślała o niczym innym, jak tylko o zemście na nim i Beatrice. A tak przy okazji, wiesz jak Rzeźnik pozbył się Jessiki?";
			link.l1 = "Nie. Albo po prostu zostawił ją na Barbadosie, albo wziął za nią okup.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "Drugi. Poniżył ją niewyobrażalnie. Po prostu zamknął ją w kajucie, przywiózł na Barbados, zaczął negocjować z jej ojcem Oliverem Rose'em i faktycznie sprzedał ją za stertę dublonów... po wszystkim, co dla niego zrobiła.";
			link.l1 = "Hm. Myślałem, że Rzeźnik chronił jej honor, gdy piraci zajęli 'Neptuna' od Joshuy Leadbeatera...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "To również prawda. Ale ona zapłaciła mu sowicie jako nagrodę. Jessica kilka razy uratowała temu łajdakowi marny żywot, wyciągając go z tarapatów, które sam sobie regularnie sprowadzał przez swoje hulaszcze życie i gwałtowny temperament. W rzeczywistości to tylko dzięki niej osiągnął chwałę jako prosperujący pirat.";
			link.l1 = "Tak, tak, jego 'czerwony talizman'. Słyszałem o tym. Mówią, że jak tylko Rzeźnik wyrzucił Jessa, jego szczęście zrobiło to samo z nim...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "Ale oczywiście. Bez Jessiki stał się tylko kolejnym zwykłym rozbójnikiem morskim, choć niesamowicie odważnym. Jednak Jessiki przy nim nie było, to ona pomagała mu planować wszystkie ryzykowne operacje i zawsze mógł liczyć na jej ostrze.\nJasne, Beatrice też nie była dobrą dziewczyną, ale nie dorównywała Jess, urok Beatrice był zupełnie inny... Popełniła błąd, zadzierając z Rzeźnikiem.";
			link.l1 = "Słyszałem to już gdzieś...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "Wszyscy piraci tak myśleli, w tym Blaze Sharp, jej brat. Nie mógł znieść Rzeźnika... Ale wróćmy do Jessiki. Nawet nie śmiałem o niej myśleć, gdy była na 'Neptunie', nigdy nie opuściłaby swojego ukochanego kapitana. Ale kiedy Rzeźnik pozbył się jej w tak podły sposób...\nPrzybyłem na Barbados i zaprzyjaźniłem się z nią. Nie było jej łatwo, kochała morze i niebezpieczne przygody. To nudne kolonialne życie ją zabijało. Poza tym, stała się bardzo niesławną osobą na Karaibach, służąc na 'Neptunie', a ludzie z Bridgetown mieli powody, by uważać ją za wspólniczkę Rzeźnika...";
			link.l1 = "Ale nie mogli niczego udowodnić...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "Nie. Ale nikt też nie chciał mieć z nią do czynienia. Uważano ją za przeklętą, mimo jej statusu w Bridgetown. Myślę, że byłem jedynym człowiekiem, który spędził tam z Jessicą więcej niż pół godziny.\nZaproponowałem jej, żeby pojechała ze mną na Zachodnią Główną i tam zaczęła nowe życie. Życie, o którym zawsze marzyła - morze, statki, podróże, przygody. Wtedy już zorganizowałem dużą operację w Blueweld i mogłem zaoferować jej sto razy więcej niż ten gnój Rzeźnik. Ale Jess była bardzo zraniona. Nie wybaczyła Rzeźnikowi jego zdrady i tego, jak ją traktował później. I wierzę, że nadal miała do niego uczucia nawet wtedy... Pomimo wszystkich moich wysiłków, nie mogłem sprawić, by zapomniała o przeszłości, była opętana myślami o zemście.";
			link.l1 = "Tak, nie zazdroszczę jej. Biedna dziewczyna...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Czułem się podobnie do niej. A później zaczęła się interesować starożytnymi kultami i rytuałami Indian. Stało się to po tym, jak złapano jakiegoś indyjskiego maga i sprowadzono z głębi dżungli Jukatanu na miejscową plantację. Jessica go kupiła i dała mu dom na swojej plantacji.\nSpędzała z magiem mnóstwo czasu. Mówiła, że wszystko to z powodu jej historycznego zainteresowania magicznymi rytuałami Indian. Ludzie z Bridgetown zaczęli się niepokoić, zwłaszcza miejscowy pastor. Właściwie to był jednym z nielicznych, którzy byli dobrzy dla Jessiki.\nKsiądz często z nią rozmawiał, przekonując ją, by pozbyła się maga, grożąc niebezpieczeństwami i inkwizycją, ale próby przestraszenia Jessiki były daremne. Pewnej nocy jacyś nieznajomi włamali się do domu maga i zamordowali go.\nTej samej nocy dwóch mężczyzn zaatakowało Jessikę w jej własnej sypialni, ale nie skończyło się to dla nich dobrze - nikt w Bridgetown nie wiedział, jak dobrze Jess włada swoim mieczem z płonącym ostrzem. Dosłownie pocięła ich na kawałki.";
			link.l1 = "Tak, oczywiście... ta lekkomyślna jędza!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Potem całe miasto zaczęło się jej obawiać. A potem pojawiła się Maska. Znaleźli się wzajemnie dość szybko.";
			link.l1 = "Według zapisków, Maską jest Joshua Leadbeater, były kapitan 'Neptuna'...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "Dowiedziałem się o tym dużo później. Tydzień po przybyciu Maski, Jess zabrała swoje rzeczy, pożegnała się ze mną i odpłynęła na wojennym fregacie w nieznane kierunki. Nigdy nie wróciła... tak samo jak Beatrice nigdy nie wróciła na Isla Tesoro.\nWkrótce potem powiesili Rzeźnika w St. John's, został tam dostarczony przez samą Maskę. Ale przeżył Rzeźnika tylko o jeden dzień.";
			link.l1 = "Tak... Nasz Steven Dodson pokazał klasę...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Tak, tak mi powiedziano. Pomścił Beatrycze... I tak kończy się historia Jessiki, zmarła gdzieś na bezludnej wyspie w starciu z piratami Rzeźnika. Nikt nie wie, gdzie jest to miejsce. Rzeźnik nie żyje, a także Jackman i Kat.";
			link.l1 = "Tu się mylisz, Janie. Rzeźnik żyje.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " Co!? To niemożliwe! Został powieszony!";
			link.l1 = "Przeczytaj zeznania Raymonda Bakera. To lepsze niż jakakolwiek opowieść.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Pokaż mi to... (czyta) Hm. Niesamowite! Okazuje się, że jego egzekucja była sfingowana!";
			link.l1 = "Sprytnie, co? Ale to nie wszystko. Znasz Rzeźnika. Po prostu nie wiesz, kim jest teraz.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "Tak? I kimże jest?";
			link.l1 = "Lawrence Beltrope z Port Royal. Właściciel kopalni, ta bardzo tajemnicza postać stojąca za Jackmanem. Odkryłem to przez Bakera, a Baker dowiedział się od Maski.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Święty kurwa! A więc to on stoi za wszystkim? Cóż, dobrze... Udajemy się także do Rzeźnika. Zastanowię się, jak pozbyć się tego złego grosza. Choć to nie będzie łatwe, jest pod trwałą ochroną angielskich władz.";
			link.l1 = "Jego czas nadejdzie, Janie. Wkrótce spotka się ze swoim bosmanem i kwatermistrzem. Dobra, dzięki za opowieść. Czas mi ruszać.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Dokąd się teraz wybierasz?";
			link.l1 = "Na jakąś wyspę. Wierzę, że to to samo miejsce, gdzie zginęli Jess i Beatrice, a Mask rzucił się na Butchera-Beltrope. Potrzebuję dowodu, że Helen należy do rodziny Sharp i mam nadzieję odkopać go tam.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "Dobrze. Więc, "+pchar.name+"    Powodzenia ci życzę. Opowiedz mi szczegóły, gdy wrócisz.";
			link.l1 = "Oczywiście. Do zobaczenia później, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Świetna robota, "+pchar.name+"Dokonałeś niemożliwego. Wszyscy my, baronowie Bractwa Wybrzeża, jesteśmy ci wdzięczni.";
			link.l1 = "Tak, droga do zwycięstwa była wąska. Gdybym tylko wiedział wcześniej, że będę musiał wytrzymać tak wiele...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "Jak się ma Helen? Co planuje zrobić?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Zostaje na moim statku ze mną. Nie jest już zwykłym oficerem. Kontrola nad wyspą zostanie przekazana przywódcy Bractwa, a wszystko, co otrzyma, to czynsz. Helen sama tak zdecydowała.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "Wyruszyła na Isla Tesoro, by przejąć baronię w swoje ręce.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Cóż, "+pchar.name+"... Gratulacje! Wielu mężczyzn marzyło, by być na twoim miejscu. Cieszę się, że Elen wybrała mężczyznę, który na nią zasługuje. Nie mogło być lepszego kandydata niż ty, by być jej towarzyszem życia.";
			link.l1 = "Dziękuję, Janie! Teraz chciałbym wrócić do naszej rozmowy o Tortudze i Levasseurze.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Dziękuję, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Wspaniale. Ona na to zasługuje. Myślę, że nowy przywódca Bractwa pomoże jej w jej sprawach. Jest utalentowaną i bystrą młodą dziewczyną, która szybko się uczy i potrafi przyswoić wszystko. Dziękuję, "+pchar.name+" ! Helen jest dla mnie jak córka i jestem zachwycony, że taki wspaniały przyszłość właśnie się przed nią otworzyła.";
			link.l1 = "Nie ma za co, Janie... Tak czy inaczej, chciałbym wrócić do naszej rozmowy o Tortudze i Levasseurze.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Nie ma za co, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Podczas twojej nieobecności, "+sTemp+" i już to omówiliśmy i doszliśmy do wspólnej opinii w sprawie usunięcia Levasseura. Wypłyń na Isla Tesoro i porozmawiaj z naszym nowym przywódcą, poda ci szczegóły naszego planu i udzieli wszelkiej pomocy, jaką może ci zapewnić.";
			link.l1 = "Wreszcie czuję zapach prochu! Nie ma czasu do stracenia, ruszam na Isla Tesoro!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", zaczekaj chwilę. Mam dla ciebie kilka prezentów za twoją pomoc w sprawie Helen i Braci. Pierwszy to zaczarowany amulet Saracena z dalekiego Wschodu. Jego uroki wzmacniają dyscyplinę na statku, co osobiście sprawdziłem. Proszę, oto on.";
			link.l1 = "Dziękuję!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Drugi to tylko pamiątka z przeszłych przygód. Przekonałem Radę, by wyrzuciła ten absurdalny relikt używania fragmentów kamienia na wiatry. Nie są już potrzebne. Oddam je tobie. Może znajdziesz dla nich jakieś zastosowanie.";
			link.l1 = "Zastosowanie dla fragmentów? Hm. Nie wiem... ale jako pamiątka, jestem bardzo zobowiązany!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "Cóż, nie zapomnij o swoim przyjacielu, "+pchar.name+". Wpadnij do mnie, gdy zakotwiczysz w Blueweld. Usiądziemy i wypijemy trochę rumu. Zawsze się cieszę, gdy cię widzę.";
			link.l1 = "Z pewnością, Janie. Mamy teraz coś do zapamiętania, prawda? Ha-ha! W każdym razie, powinienem już iść.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Powodzenia, "+pchar.name+"!";
			link.l1 = "Do zobaczenia...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Tak... Wygląda na to, że nasz plan legł w gruzach. Teraz nie będziemy mogli obsadzić na czele Bractwa tego, kogo chcieliśmy. Jackman nie żyje, i to dobrze. Ale niestety mój plan teraz się nie uda. Będziemy musieli wybrać głowę Bractwa w zwykły sposób, a Bóg jeden wie, jaki to zwrot przybierze...";
			link.l1 = "To niefortunne. Bardzo niefortunne. I wygląda na to, że Helen zostanie bez swojego dziedzictwa.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Tak, "+pchar.name+" I chciałbym ci pomóc zdobyć Tortugę, naprawdę chciałbym, ale teraz nawet nie wiem jak. Prawdopodobnie nic nie mogę zrobić, aby pomóc. Wygląda na to, że będziesz musiał polegać tylko na własnych siłach i zdolności do walki.";
			link.l1 = "Wydaje się, że nie ma innej opcji... Dobrze, Janie, pójdę pomyśleć, co robić dalej. Do zobaczenia później...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Zatrzymaj się, "+pchar.name+"Zawsze cieszę się na twój widok.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "Lecz niestety, teraz jest za późno, by cokolwiek zrobić. Isla Tesoro jest oficjalnie przekazane pod władzę angielskiej korony. Teraz stacjonuje tam garnizon. To ciężki cios dla Braci, z którego, obawiam się, nie będziemy w stanie się podnieść.";
			link.l1 = "Jak straszne... Ach, powinienem był działać szybciej. Wtedy, widzisz, wszystko by się dobrze skończyło. Dobrze, Jan, pójdę pomyśleć, co robić dalej. Do zobaczenia później...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Zatrzymaj się, "+pchar.name+". Zawsze się cieszę, gdy cię widzę.";
			link.l1 = "Hello, I am Charles de Mor.";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Tak... Naprawdę ponieśliśmy dotkliwą klęskę. A najgorsze jest to, że byliśmy dosłownie o krok od zwycięstwa. Caramba! Jak to się mogło stać, co, "+pchar.name+" ? Tak się starałeś, zrobiłeś tak wiele i... taki pech!";
			link.l1 = "Jestem tym imbecylem, który za to odpowiada. Powinienem był być szybszy. A dzięki mnie, Helen straci swoje dziedzictwo. A plan Turtugi nigdy nie dojdzie do skutku.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "Dobrze, nie mam nic przeciwko. Mam dwadzieścia pięć jednostek w moim magazynie. Cena, jak pamiętasz, to 3150 dubloonów.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "Dobrze, umowa stoi. Proszę bardzo. Oto 3150 doubloonów.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "A to pech. Zapomniałem pieniędzy na moim statku. Zaraz wrócę z nimi";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Dobrze, nie mam nic przeciwko. Mam dwadzieścia pięć jednostek w moim magazynie. Cena, jak pamiętasz, to trzydzieści dubloonów za sztukę.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "Dobrze, umowa stoi. Proszę bardzo. Oto siedemset pięćdziesiąt doubloonów.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "A to pech. Zapomniałem pieniędzy na moim statku. Zaraz wrócę z nimi.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, czy można by zwiększyć rozmiary partii gwajakowca?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, "+GetSexPhrase("zebrałem","zebrałam")+" trzy tysiące złotych. Masz, możesz wręczyć ten prezent naszym darmozjadom. Przypuszczam, że będą mieli dzisiaj szczęśliwy dzień.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Chwalebnie. Rozkażę moim ludziom przenieść żelazne drewno na twój statek.";
			link.l1 = "Dziękuję!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Jeśli chcesz kupić więcej, wróć za dwa tygodnie. Do tego czasu przygotuję nową partię.";
			link.l1 = "Dobrze, Janie. Do zobaczenia następnym razem!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "przyjacielu";
			if (startHeroType == 2) sStr = "przyjacielu";
			if (startHeroType == 3) sStr = "przyjacielu";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Cieszę się, że gwajakowiec przypadł ci do gustu, " + sStr + ". Zwiększenie partii to nie problem, ale jest tu pewne 'ale', sam"+GetSexPhrase("","a")+" rozumiesz. Ze zwiększeniem objętości pojawia się też ślad, który może przyciągnąć niepotrzebną uwagę, szczególnie ze strony władz angielskich. Ale jeśli dodamy do interesu pewne ręce, wierne uszy i ludzi w rezydencji, którzy pomogą pozostać w cieniu, wszystko można zorganizować. Prawda, że to nie będzie tanie - trzy tysiące dublonów za ominięcie skarbca miasta i potrzeb Anglii. Wtedy będę mógł dostarczyć ci pięć razy więcej. Co ty na to?";
				link.l1 = "Trzy tysiące dublonów? Jan, to przecież rabunek w biały dzień! Czy nie można jakoś poradzić sobie mniejszym kosztem? Może jest sposób załatwić sprawę bez takich bajońskich sum?";
				link.l1.go = "UpgradeBakaut_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Dobry pomysł, ale muszę powiedzieć, że do takich wolumenów w sprawach handlowych potrzeba nieco więcej doświadczenia i umiejętności. Pośpieszysz się - więcej ryzyka niż pożytku. Zróbmy tak: zdobądź jeszcze trochę doświadczenia, a kiedy będziesz "+GetSexPhrase("gotowy","gotowa")+" na większe partie, wpadnij. Wtedy omówimy wszystko jak należy.";
				link.l1 = "Hmm... Dobrze. Wrócimy do tej rozmowy później.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Niestety, "+pchar.name+", taka jest teraz cena spokoju - apetyty tych panów w perukach i mundurach rosną z każdym dniem. Nic ich bardziej nie nęci niż dublony brzęczące w ich skrzyniach. Gwarantuję ci zniżkę w wysokości piętnastu procent na wszystkie kolejne partie, jeśli cię to pocieszy.";
			link.l1 = "A niech ich! Żądać takich sum! Z taką chciwością powinni skupować skarby królów, a nie targować się o milczenie! Jan, a może tego... pokażemy im, kto jest prawdziwą siłą na archipelagu, co?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "przyjacielu";
			if (startHeroType == 2) sStr = "przyjacielu";
			if (startHeroType == 3) sStr = "przyjacielu";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ha! Co za zapał u ciebie, " + sStr + "! Ale iść przeciwko całej Anglii nie jest mi teraz na rękę, a i lata już nie te. Zapłaćmy po prostu tym krwiopijcom, i niech sobie siedzą cicho - my mamy swoje sprawy do zrobienia. Zbierz potrzebną sumę, a nasza droga będzie wolna, bez zbędnych pytań!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "No dobrze, Jan, przekonałeś mnie. Niech tak będzie, skoro inaczej się nie da. Masz swoje trzy tysiące dublonów. Tylko pamiętaj: nie zamierzam wiecznie dokarmiać tych skąpców.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Diabli ich wezmą, Jan! Naprawdę uważasz, że nie ma innego wyjścia? Dobrze. Znajdę te dublony. Ale w tej chwili nie mam takich pieniędzy.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Do diabła, Jan, czy naprawdę chcesz, żebym karmił tych urzędników z ich wygładzonymi damami? Oni siedzą na swoich fotelach, nic nie robią, a tylko żądają pieniędzy! Nie, to nie jest w moim guście! Nie zamierzam napełniać ich kieszeni swoim potem i krwią! Wróćmy do poprzednich warunków. Wystarczy mi i tego.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "To zupełnie inna rozmowa! Z twoim wkładem nasze sprawy pójdą jak po maśle, a ci skąpcy dostaną swoje - i przestaną nawet patrzeć w stronę gwajakowca. Zapewniam cię, wkrótce odzyskamy wszystkie inwestycje stokrotnie.";
			link.l1 = "Mam nadzieję, Jan, mam nadzieję.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Interesy pójdą jak należy, możesz być spokojny. A teraz, co do naszych przyszłych transakcji: będę trzymał dla ciebie w gotowości 125 pni gwajakowca, jak poprzednio, na 14-ty i 28-my dzień każdego miesiąca. Całą partię będziesz mógł odebrać za 3150 dublonów.";
			link.l1 = "Takie rozmowy są mi o wiele bardziej po myśli! Sto dwadzieścia pięć pni, tak? Wspaniale, Jan. Cóż, do rychłego zobaczenia, będę czekać na dostawę!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "przyjacielu";
			if (startHeroType == 2) sStr = "przyjacielu";
			if (startHeroType == 3) sStr = "przyjacielu";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Jak sobie życzysz, " + sStr + ". I nie denerwuj się tak. Tak już jest urządzony ten świat.";
			link.l1 = "Tak, Jan, wiem jak urządzony jest ten świat. Ale to nie znaczy, że muszę to tolerować. Dobrze, muszę już iść.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "Poczekam, aż zbierzesz pieniądze. Wiem, że znajdziesz sposób. Jak tylko będziesz "+GetSexPhrase("gotowy","gotowa")+" - czekam na ciebie z pieniędzmi, i będziemy kontynuować.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Cieszę się, że cię widzę, "+pchar.name+"Moi ludzie są gotowi. W drogę do selwy?";
			link.l1 = "Tak, Janie. Moja drużyna jest gotowa do bitwy.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Ruszajmy zatem. Kopalnia znajduje się w głębi dżungli, tuż przy tej ścieżce. Trzymaj się prawej strony na rozwidleniu. Naprzód!";
			link.l1 = "Naprzód!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Więc, "+pchar.name+", czas omówić, jak przeprowadzimy tę operację. Wysłałem już wcześniej kilku Indian Miskito, aby zbadali teren i opracowałem plan działania na podstawie ich obserwacji.";
			link.l1 = "Opowiedz mi wszystko!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Dół przedstawia kopalnię pod górami w dżungli. Jest tam obóz blisko wejścia do kopalni. Kilka domów i palisada. Jest ścieżka prowadząca do palisady. Spójrz, prowadzi do małej, oczyszczonej przestrzeni w dżungli niedaleko stąd. Tam znajduje się główne wejście do dołu.\nPrzedstawia wysoką kamienną ścianę pomiędzy dwoma stromymi wzgórzami, zapobiegającą przed zakradnięciem się do środka. Bramy są chronione przez straż sześciu ludzi. Nie jest to wielka sprawa, ale mają tam także ustawione dwie armaty. To największy problem.\nDwie salwy kartaczami mogą zniszczyć połowę naszego oddziału, co byłoby katastrofą, więc frontalny atak nie wchodzi w rachubę...";
			link.l1 = "Ha! Ale mamy asa w rękawie, znamy hasło, które pozwoli nam wejść do środka...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "To prawda. Wykorzystamy to na swoją korzyść, ale najpierw pozwól mi przedstawić ci cały mój plan aż do końca.";
			link.l1 = "Jasne, Jan. Zamieniam się w słuch.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "Jest jeszcze jedno wejście do jamy - przez tę ścieżkę w dżungli. Obchodzi ono wzgórza chroniące kopalnię i prowadzi do małego i wąskiego zagłębienia, które można wykorzystać do wejścia. Ale bandyci postawili tam wysoki płot i umieścili strażników. Płot ma małe bramki, ale są one zablokowane od drugiej strony.\nTeraz posłuchaj, co zamierzamy zrobić. Pozbędziemy się tych, którzy pilnują drugiego wejścia do kopalni. Część naszego oddziału zostanie tam i znajdzie jakiś kloc do użycia jako taran.\nWrócimy do głównego wejścia i zabijemy załogi dział. Hasło, które mamy, pomoże nam dwa razy. Następnie zaatakujemy kopalnię z dwóch stron. Ja poprowadzę pierwszą jednostkę szturmową, a ty poprowadzisz drugą.";
			link.l1 = "Cóż, to logiczne. Zmusimy ich do walki na dwa fronty. Naprzód!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Prawda, oto jesteśmy... To jest ścieżka do płotu bandytów. Teraz musimy zdecydować, jak się z nimi rozprawić. Jeśli wyślemy tam cały oddział, będzie to zbyt podejrzane i podniosą alarm.\nPowinniśmy wysłać małą grupę trzech osób, nie więcej, ta grupa będzie mogła podejść wystarczająco blisko, nie wzbudzając podejrzeń, i zaatakować z zaskoczenia. Nie mogę prowadzić grupy, moja twarz jest tu zbyt dobrze znana.\nWięc to zależy od ciebie, "+pchar.name+", ponieważ jesteś jedynym, któremu mogę zaufać, że poprowadzi bez ryzyka dla całej operacji. Dam ci Gregory'ego i muszkietera do pomocy...";
			link.l1 = "Ilu strażników jest przy płocie?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Czterech. Dwóch muszkieterów i dwóch żołnierzy.";
			link.l1 = "Weźmiemy ich...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Znając ciebie, nawet przez chwilę w to nie wątpię. Podejdź do nich i powiedz, że przysłał cię Jackman. Powiedz im hasło. A potem, gdy się rozluźnią... działaj zgodnie z okolicznościami.";
			link.l1 = "Dobrze. Będziemy trzymać ich w napięciu.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Powodzenia, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Świetna robota, "+pchar.name+" ! Wyszedłeś na swoje, jak zawsze. Teraz moi chłopcy przygotują się do rozpoczęcia szturmu z tej strony kopalni, a my oczyścimy główne wejście.";
			link.l1 = "Rozumiem, że znowu będę musiał podejść do strażników?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Tak, "+pchar.name+", po raz kolejny. Sam bym się tam udał, ale na pewno by mnie rozpoznali i cała operacja poszłaby na marne. Będzie to bardziej niebezpieczne, bo jest więcej wrogów, i nie zapomnij o broni.";
			link.l1 = "Wezmę ze sobą moich oficerów.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Tak, "+pchar.name+", jeszcze raz. Sam chciałbym się tam udać, ale z pewnością by mnie rozpoznali i cała operacja poszłaby w diabły. Będzie bardziej niebezpiecznie, bo jest więcej wrogów, i nie zapominaj o broni. Kogo zabierzesz ze sobą, by cię wspomóc? Swoich oficerów czy Gregory'ego i muszkietera jak ostatnim razem?";
			link.l1 = "Wezmę moich oficerów.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Wezmę Grzegorza i muszkietera.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "W porządku. Własna załoga to najlepsze wsparcie. Teraz wrócimy do głównego wejścia. Pamiętasz drogę?";
			link.l1 = "Oczywiście. Wracaj tą samą drogą, którą przyszliśmy, potem trzymaj się lewej strony, a następnie idź ścieżką wokół wzgórza.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "Dobrze. Udało ci się to raz, więc drugi raz powinien być bułką z masłem. Teraz wracamy do głównego wejścia. Pamiętasz drogę?";
			link.l1 = "Oczywiście. Wróćmy tą samą drogą, następnie trzymaj się lewej strony i idź ścieżką wokół wzgórza.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Nie ma czasu do stracenia. Naprzód!";
			link.l1 = "Naprzód!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Zgadza się, "+pchar.name+", posłuchaj tych ostatnich instrukcji. Te diabły strzegące bram są twarde, więc nie będzie ci łatwo. Twoim głównym celem jest zabicie kanonierów stojących przy bramach, bo nie będziemy mogli przyjść ci z pomocą, jeśli będą jeszcze oddychać.\nGdy obaj będą martwi i nie będzie szansy na salwę, wszyscy przyjdziemy i zgładzimy ich w kilka sekund. Czy zrozumiałeś, "+pchar.name+"? Nie baw się w bohatera, zabij kanonierów, a resztę zostaw nam.";
			link.l1 = "Dobrze, Janie. Spróbuję zrobić wszystko tak, jak zaplanowaliśmy. A jeśli coś pójdzie nie tak, będę improwizować.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Brzmi dobrze. Niech Bóg będzie z Tobą!";
			link.l1 = "Dzięki...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Phew! Pokonaliśmy tych sukinsynów... Byli to zapalczywi małolaci. Mogę powiedzieć, że ci najemnicy służyli wcześniej w regularnych oddziałach. Narobiliśmy tu hałasu, obawiam się, że mogli nas usłyszeć. Nie ma czasu do stracenia!"+pchar.name+", czas, abyśmy zaatakowali kopalnię.\nWrócę do mojej grupy przy drugim wejściu - musieli już znaleźć i przygotować kłodę, by rozwalić ogrodzenie. Ty i twoi ludzie pójdziecie przez główne bramy. Poczekajcie na nas pół godziny, nie atakujcie od razu...";
			link.l1 = "Jan, jeśli usłyszeli strzały w kopalni, nie mamy tej pół godziny. Ci bandyci mogą ustawić linię obrony lub prawdopodobnie przyjść prosto do głównych bram i zaatakować moją grupę wszystkim, co mają...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Cholera! To całkiem możliwe. Co sugerujesz, żebyśmy zrobili?";
			link.l1 = "Hm... Ha! Mam pomysł! Działa! Rozejrzyj się. Znajdziemy tu nie tylko śrut, ale i bomby! Teraz te bandziory są skończone! Czemu wcześniej na to nie wpadłem?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "Co myślisz, że powinniśmy zrobić?";
			link.l1 = "Weźmiemy jedną armatę. Z jedną będziemy mogli poruszać się znacznie szybciej i sprawniej. Przetoczymy ją do środka, za bramy, do kopalni i ustawimy na pozycji. Jeśli sami zaatakują, dostaną wielki wybuch, a jeśli będą się cofać, po prostu zbombardujemy ich obóz. Możesz mi powiedzieć, gdzie dokładnie znajduje się obóz za bramami?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "Obóz znajduje się na nizinie u podnóża góry. Tuż za bramami znajduje się ścieżka prowadząca w dół, wijąca się wokół wzgórza. Obozowisko usytuowane jest tuż za tym wzgórzem.";
			link.l1 = "Znakomicie! Ustawimy się na szczycie ścieżki i rzucimy parę bomb przez wzgórze prosto do ich gniazda! Ach, będą tańcować na wszystkie strony!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Do diabła, "+pchar.name+" , dobra robota! Wszystkie żagle na wiatr! Zostawiam Randolfa pod twoim dowództwem, to mój najlepszy artylerzysta. Uczyń go swoim kanonierem, a nie zawiedzie cię. Wyruszam teraz do mojego oddziału.";
			link.l1 = "Dobrze. Będę bombardował ich pozycje do diabła przez pół godziny, aż złamiesz bramy.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Spróbuję zdążyć na czas. Spotkamy się w obozie!";
			link.l1 = "Umowa... Drużyno! Słuchajcie mojego rozkazu! Przygotować się do przeniesienia działa na nowe stanowisko! Zabierzcie proch, bomby i kartacze ze sobą! Do kopalni przez bramy. Naprzód marsz!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Uff, czyżbyśmy się spóźnili, "+pchar.name+"?";
			link.l1 = "Jan, święte nieba! Co cię tak długo zajęło? Moja drużyna właśnie otrzymała potężny cios!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "Ten cholerny drewniany płot okazał się naprawdę solidny. Przebiliśmy się siłą... Słyszeliśmy twoje hałasy. Wygląda na to, że dobrze oczyściłeś to miejsce! Płonie do ziemi!";
			link.l1 = "Wyczyny Randolfa... Żałuję, że nie mogłeś zobaczyć, ilu drani pochowaliśmy, zanim w końcu doszło do walki wręcz!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! Chylę przed tobą kapelusz, "+pchar.name+" . Dobra robota! No cóż, jeśli chodzi o straty... zawsze masz je, gdy jesteś na wojnie.";
			link.l1 = "Teraz musimy oczyścić samą kopalnię. Możliwe, że niektórzy ocalałcy się tam ukrywają.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Chodźmy tylko we dwoje. Zbadajmy tam sytuację.";
			link.l1 = "Brzmi jak plan!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "Nie przeszukaliśmy jeszcze całej kopalni! Gwarantuję ci, że jeszcze kilku z tych szubrawców się tu ukrywa!";
			link.l1 = "...na miłość boską! Niechże ktoś zatrzyma tego przeklętego szaleńca!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "Nie sądzę, żeby został jeszcze jakiś łajdak...";
			link.l1 = "Jan, myślałem, że przybywamy tu tylko, aby zbadać sytuację...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ha-ha, cóż, nie mówiłem ci, że to będzie specjalna wyprawa, krwawa wyprawa... Dawno nie miałem takiej rozgrzewki! Teraz każdy może być pewien, że nie ma ani jednego łajdaka, który uciekł z tej kopalni!";
			link.l1 = "Co zrobimy dalej, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "Co masz na myśli, co zrobimy dalej? Będziemy szukać złota i srebra. Nie sądzę, że Jackman trzymał tu taki bastion z nudów. Umieścił tu cały garnizon. Widziałeś niewolników w kopalni? Powinieneś zapytać, gdzie przechowują wydobyty surowiec.";
			link.l1 = "W porządku. Ty przesłuchaj niewolników, a ja się wspinam i przeszukam wszystkie domy w obozie, może coś znajdę.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Złapany! Czas się ruszać!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Idź, kamracie. I przewróć te żałosne chaty do góry nogami!";
			link.l1 = "Jestem w drodze!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ha-ha! "+pchar.name+", to wspaniale, że zgłosiłeś się, aby wyruszyć ze mną i rozbić tę kopalnię! To kolejny wyraźny znak, że urodziłeś się pod szczęśliwą gwiazdą.";
			link.l1 = "Czy znalazłeś złoto?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Tak, do diabła! Nie złoto, ale srebro, dobra kupa tego. Dzień później i wywieźliby to z obozu. Dlatego było tu tylu zbirów - to była grupa eskortowa.\nDzięki tobie zdążyliśmy na czas, bez ciebie wciąż zbierałbym ludzi. Gratulacje, partnerze!";
			link.l1 = "Ha! Rozumiem... Ile mamy srebra?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Mamy około cztery tysiące jednostek. Podzielimy to na dwie części - połowa dla mnie, połowa dla ciebie, tak jak się umówiliśmy.";
			link.l1 = "Znakomicie! Możemy zgarnąć kupę kasy za te rzeczy!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "To na pewno... Znalazłeś coś cennego?";
			link.l1 = "Nie, nie ma ani jednego дублона w tych chałupach. Chociaż znalazłem jakieś papiery. Przeczytałem je i dowiedziałem się, że właścicielem tej kopalni jest jakiś Lawrence Beltrope z Port Royal.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "O, naprawdę? Pozwól, że zobaczę te dokumenty...";
			link.l1 = "Oto proszę.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(czytając)... Dobrze... Beltrope? Znam to nazwisko skądś. Och, tak! Thomas Beltrope! To interesujące... Dobrze, sprawdzę to, gdy wrócę do Blueweld. Zatrzymam te dokumenty przy sobie, jeśli nie masz nic przeciwko?";
			link.l1 = "Zupełnie nie. Nie są mi do niczego potrzebni.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Dobrze. Teraz pozostała najlepsza część, zamierzam przetransportować srebro na statki. Miskitos nam w tym pomogą. Złożymy razem wóz... Tymczasem ty po prostu odpocznij, "+pchar.name+"Zasłużyłeś na to bardziej niż ktokolwiek inny!";
			link.l1 = "Dzięki, Jan.  Rozbijemy obóz na tamtym wzgórzu, ten zapach popiołu jest nie do zniesienia.  Tak, i musimy zgasić ogniska w tych chałupach, kto wie, może kiedyś się nam przydadzą...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "Zastanawiasz się nad przejęciem kopalni? Ha-ha! Już rozważałem ten pomysł, ale rabowanie to jedno, a przejęcie jako własność to co innego. Przyjacielu, już ma właściciela. Możemy mieć kłopoty z angielskimi władzami.\nPoza tym, niewolnicy, z którymi rozmawiałem, powiedzieli mi, że wszystkie żyły tutaj zostały praktycznie wyczerpane - duże partie srebra były stąd wywożone już kilka razy wcześniej. Obawiam się, że ta kopalnia jest skończona.";
			link.l1 = "Hm... Zobaczymy. Może nie wszystko jest wyczerpane. Dobrze, naprawdę powinienem trochę odpocząć. Do zobaczenia później, Jan";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Idź do przodu. I nie martw się o nic. O resztę zadbamy sami.";
			link.l1 = "Hello, Charles!";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Odpocząłeś dobrze, "+pchar.name+"?";
			link.l1 = "Nie było źle... Choć, szczerze mówiąc, dałbym wszystko, by znaleźć się w tawernie, napić się i przespać w czystym łóżku.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Indianie dostarczyli srebro na brzeg i ładują je na twój statek pod nadzorem moich oficerów. Możesz już wracać. Twoje pragnienie rumu, tawerny i łóżka wkrótce się spełni. A ja chciałbym, żebyś wpadł do mnie za pięć dni, mamy jeszcze wiele spraw do załatwienia.";
			link.l1 = "Dobrze, Jan. Do zobaczenia w Błękitnym Porcie za pięć dni! Powodzenia!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, nie krzycz na mnie. Rozwiążmy to jak rozsądni ludzie - pamiętaj, mamy interesy do załatwienia!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "Zaraz nasyłam na ciebie moje psy, ropucho! Zapomnij o Levasseurze i zmykaj!";
			link.l1 = "Jan! Słuchaj mnie...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "Jaki beczkę? Jeśli chodzi o Helen, to na pewno jej porządnie dokopię... Żartuję, Charles, żartuję! Wiem, jak to jest, a co do Joanny - ta historia, miejmy nadzieję, sprawi, że trochę pomyśli - ostatnio jest wyjątkowo zrzędliwa, wiesz... No cóż, takie jest życie. W każdym razie, powodzenia w Kartagenie!";
			link.l1 = "Do zobaczenia, Janie.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
