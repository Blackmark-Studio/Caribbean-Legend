// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Nazywam się Albert Loxley i jestem prawnikiem. Reprezentuję interesy mojego klienta w procesach. Moje usługi są kosztowne, ale warte swojej ceny, mogę cię zapewnić.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "Jestem w tarapatach z angielskimi władzami.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "Mam kłopoty z francuskimi władzami.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "Mam kłopoty z hiszpańskimi władzami.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "Jestem w tarapatach z holenderskimi władzami.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Pokłóciłem się z przemytnikami.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Dzięki, ale na szczęście, jak dotąd nie potrzebuję usług adwokata.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
				}
				link.l1 = "Dzięki, ale na szczęście nie potrzebuję jeszcze usług prawnika.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "Potrzebuję twoich usług. Jestem upoważnionym delegatem pewnej młodej damy o imieniu Helen McArthur, jest wnuczką słynnego Nicolasa Sharpa. Ona jest jedyną spadkobierczynią po śmierci swojej matki i wuja. Ma pełne prawa do Isla Tesoro zgodnie z testamentem jej wuja. Ile byś zażądał za pomoc Helen w zostaniu prawowitą panią wyspy?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Czy potrzebujesz moich usług, panie? Będziesz zadowolony, mogę cię zapewnić.";
						link.l1 = "Tak, potrzebuję ich. Jestem upoważnionym delegatem pewnej młodej damy imieniem Helen McArthur, jest wnuczką słynnego Nicolasa Sharpa. Jest jedyną prawną spadkobierczynią po śmierci matki i wuja. Ma wszelkie prawa do Isla Tesoro zgodnie z testamentem jej wuja. Ile byś zażądał za pomoc Helen w zostaniu prawowitą panią wyspy?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Panie, nie jestem jeszcze zaznajomiony z materiałami twojego interesu. Proszę, przyjdź później, jak już ci mówiłem.";
						link.l1 = "Dobrze.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Panie, niestety potrzebuję więcej czasu, aby zebrać wszystkie dokumenty potrzebne w archiwach. Nie jestem jeszcze gotowy. Proszę, przyjdź później.";
						link.l1 = "Dobrze.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Panie, dlaczego pracowałeś tak wolno?! Dla twego mocodawcy wszystko przepadło. Okres ważności testamentu minął i Isla Tesoro teraz należy do Anglii. Wkrótce stanie się bazą wojskową."link.l1 ="O rany! Wygląda na to, że wszystkie moje wysiłki poszły na marne...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Ach, oto jesteś, Panie. Zaznajomiłem się z materiałami, więc czas na zaliczkę. Czy przyniosłeś ze sobą dublony?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Tak, mam. Oto twoje doubloony.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Przepraszam za moją słabą pamięć, zostawiłem je w skrzyni na moim statku. Przyniosę je natychmiast.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Panie, dlaczego pracowałeś tak wolno?! Wszystko skończone dla twego zleceniodawcy. Okres ważności testamentu wygasł i Isla Tesoro teraz należy do Anglii. Wkrótce stanie się bazą wojskową."link.l1 ="Wow!  Wydaje się, że wszystkie moje wysiłki poszły na marne...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Sir, czy udało się panu znaleźć coś, co mogłoby udowodnić pochodzenie pańskiego pryncypała?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Jeszcze nie. Ale pracuję nad tym.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Tak. Naprawdę mam wyczerpujące dowody.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "A-ah, oto jesteś, panie. Cieszę się, że cię widzę. Muszę przyznać, że czekałem na ciebie od dłuższego czasu. Czy to twój zwierzchnik?";
						link.l1 = "Tak. Pozwól, że przedstawię ci Helen McArthur.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Czy potrzebujesz moich usług, Panie? Będziesz zadowolony, mogę Cię zapewnić.";
					link.l1 = "Dziękuję, ale na razie ich nie potrzebuję.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Dzień dobry, panie. Zakładam, że przyniósł pan moją opłatę?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Tak, mam. Oto twoje doubloony.";
						link.l1.go = "saga_36";
					}
					link.l2 = "Wiesz, panie Loxley, myślałem... Chodzi mi o to, że 900 dublonów to więcej niż wystarczająco za twoją pracę.";
					link.l2.go = "saga_38";
					link.l3 = "Pamiętam, Panie Loxley. Przyniosę to nieco później...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Czy potrzebujesz moich usług, panie? Będziesz zadowolony, zapewniam cię.";
				link.l1 = "Dziękuję, ale na razie ich nie potrzebuję.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Sir, musiałeś za długo być na morzu. Isla Tesoro to teraz baza wojskowa angielskiej floty! Tak, testament Sharpa istnieje, ale wygasł i Isla Tesoro stało się własnością angielskiej korony. Niestety!"link.l1 ="Wow!  Wydaje się, że wszystkie moje wysiłki poszły na marne...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Pani twierdzi, że jest właścicielką całej wyspy? Hm... Wygląda na to, że to nie będzie łatwa sprawa. Isla Tesoro to już prawie angielska kolonia...";
				link.l1 = "Jeszcze nie. Zgodnie z testamentem, osoba, która pokaże obie części mapy, stanie się właścicielem Isla Tesoro. Mamy obie części mapy Sharpa, co jest głównym dowodem dziedzictwa.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... No, no. Muszę odwiedzić archiwum i zapoznać się z materiałami dotyczącymi Isla Tesoro. Czy masz przy sobie mapę?";
			link.l1 = "Mam, ale dam ci to dopiero po podpisaniu umowy. Więc, co z ceną za twoje usługi?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "Jak już mówiłem - to nie będzie łatwe. Musisz udowodnić prawo własności do całej wyspy, a nie do jakiejś starej łajby czy chatki. Poza tym, Nicolas Sharp był piratem, a pomaganie piratom lub ich krewnym jest kosztowne."+sTemp;
			link.l1 = "Czy zamierzasz powiedzieć mi rzeczywistą sumę?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Panie, ostateczna suma zostanie ustalona podczas procesu. Jeszcze nie wiem, jak problematyczne to będzie. Ale jestem gotów oszacować zaliczkę - "+sTemp+"  дублонów. Tę sumę złota trzeba będzie zapłacić ponownie raz lub dwa, w zależności od tego, jak dobrze pójdzie nasz interes.\nPrzynieś mi pieniądze za tydzień, potrzebuję czasu, aby sprawdzić archiwa i przygotować się. Potem dokonamy ustaleń. Zgoda?";
			link.l1 = "Polecili Cię jako najlepszego prawnika w archipelagu, więc mamy umowę. Do zobaczenia za tydzień!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Bardzo dobrze. Jestem gotów zająć się twoją sprawą i reprezentować twoje interesy w sądzie. Teraz przejdźmy do sedna. Zrobiłem dobrą robotę w archiwach i rozmawiałem z ważnymi ludźmi. Sprawa spadku Sharpa nie będzie łatwa. Dobrze, że zdobyłeś oba kawałki mapy. Ale to może nie wystarczyć.\nPułkownik Doyle ma wielkie plany dla Isla Tesoro, ponieważ nie udało mu się przejąć kontroli nad Tortugą. Ma naturalne obrony i może służyć jako przyszła baza wojskowa w tym regionie.";
			link.l1 = "Ale Helen ma wszelkie prawa do wyspy zgodnie z prawem Anglii!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Nie wiesz, być może, że nieboszczyk Sharp dodał coś do swojego testamentu. Spadkobierca lub spadkobiercy muszą nosić jego nazwisko. A z tego co pamiętam, twoja dziewczyna nosi inne nazwisko. Powiedziałeś, że to było McArthur, prawda?";
			link.l1 = "To nazwisko jej ojczyma, ale Helen ma pełne prawo nosić nazwisko Sharp, ponieważ jest córką zmarłej Beatrice Sharp, córki Nicolasa.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Znakomicie! Ale kto może to potwierdzić pod przysięgą? Czy przybrani rodzice Helen znali Beatrice Sharp?";
			link.l1 = "Z tego, co rozumiem, to nie byli. Pan McArthur uważał ją za córkę Gladys, a Gladys była tylko zaznajomiona z ojcem dziewczyny.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "To szkoda. Widzisz, nie znalazłem żadnej wzmianki w archiwach, że Beatrice Sharp kiedykolwiek miała jakieś potomstwo. Istnieje możliwość, że nie ma żadnej oficjalnej notatki o narodzinach dziecka. Każdy może nazwać się wnukiem Sharpa i rościć prawo do noszenia jego nazwiska.";
			link.l1 = "Ale tylko Helen ma kompletną mapę!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "To jej atut i być może wystarczyłby, gdyby miejscowe władze nie miały własnych planów dotyczących Isla Tesoro. Dokument z pismem Beatrice i jej podpisem znajduje się w archiwach. Musimy znaleźć jakiś dokument napisany przez nią, który udowodni fakt narodzin jej córki, córki, która została oddana tej Gladys... eh, jak brzmiało jej nazwisko?";
			link.l1 = "Chandler. Gladys Chandler z Belize.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Dokładnie. Czy masz okazję znaleźć coś takiego?";
			link.l1 = "Wątpię w to. Zbyt wiele lat minęło. Według legendy, kapitan Rzeźnik sam może być ojcem Helen. Może były kat z St. John's może nam coś o tym powiedzieć. Był ostatnim, który widział jej ojca żywego.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Hm. Naprawdę był zabawnym człowiekiem. O ile pamiętam, nazywał się Raymond Baker. Miałem szczęście raz z nim porozmawiać. Jest inteligentnym i dobrze wykształconym człowiekiem. Cóż, spróbuj znaleźć coś na Antigui, a ja będę kontynuować poszukiwania w archiwach, może znajdę coś przydatnego.";
			link.l1 = "Dobrze. Pasuje mi.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Daj mi mapę Sharpa i pośpiesz się, porozmawiaj z Bakerem, być może z jego pomocą uda ci się znaleźć jakieś dokumenty. Może nawet znajdziesz dowód na jej narodziny.";
			link.l1 = "Eh, chciałbym móc. Dobrze, do zobaczenia, panie Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Czyżby tak? Przyjrzyjmy się tym dowodom.";
			link.l1 = "To prywatny list napisany przez Beatrice Sharp do jej brata. Napisano tutaj, że urodziła córkę i że jej ojcem był w rzeczywistości Lawrence Beltrope. Dziewczynka została wysłana do młodej wdowy imieniem Gladys Chandler. Lawrence Beltrope jest również znany jako kapitan Rzeźnik. Proszę, weź list...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "I'm sorry, I don't have any text to translate. Could you provide the text you need translated?";
			link.l1 = "Gladys jest gotowa potwierdzić to pod przysięgą. Jest również gotowa potwierdzić, że ojciec przedstawił się jako kapitan Butcher.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Chwileczkę! Kapitan Rzeźnik, zły pirat i zabójca angielskich poddanych, został powieszony w fortecy St. John's dwadzieścia lat temu. A Lawrence Beltrope, bliski przyjaciel Richarda Doyle'a, zmarł tragicznie niedawno. A co najważniejsze, Doyle chciał uczynić go nowym gubernatorem Sharptown!";
				link.l1 = "Ha! Pewnie, nikt o tym nie wie... Mam pisemne zeznanie Raymonda Bakera, byłego kata z St. John's, że został zmuszony pod groźbą pewnej śmierci do sfingowania egzekucji Butchera! Proszę, spójrz...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Chwileczkę! Kapitan Butcher, zły pirat i zabójca angielskich poddanych, został powieszony w forcie St. John's dwadzieścia lat temu. A Lawrence Beltrope żyje i mieszka w jednej z najlepszych rezydencji Port Royal. I co najważniejsze, Doyle chce go uczynić nowym gubernatorem Sharptown!";
				link.l1 = "Ha! Pewnie, nikt o tym nie wie... Mam pisemne zeznanie Raymonda Bakera, byłego kata z St. John's, że został zmuszony pod groźbą pewnej śmierci, by sfingować egzekucję Butchera! Proszę, spójrz...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Hm. No, no...";
			link.l1 = "Czyż to nie jest bardzo zręczne? Kapitan Rzeźnik zdołał przeżyć i wrócił do Anglii. Zmienił swoje nazwisko z powrotem na Lawrence Beltrope i powrócił tutaj niezauważony.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "Lecz to... To zmienia wszystko! Opublikowanie listu Beatrice pokaże, że przez cały ten czas wojskowy gubernator ukrywał zbiegłego pirata Rzeźnika, którego należało aresztować na miejscu i który powinien był stanąć przed sądem za swoje przeszłe zbrodnie!\nA zeznania Bakera całkowicie zniszczą wszelkie argumenty przeciwko temu! To wspaniałe! Z takim asem w ręku pokonamy Doyle'a uczciwie i bez wątpliwości!";
			link.l1 = "Cieszę się. Polegam na tobie w tym wyzwaniu. Powiedz mi też, jak zginął Lawrence Beltrope?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "To przerażająca historia, panie. Znaleziono go w jego własnej sypialni z wykrzywioną twarzą. Trudno sobie wyobrazić, co mogło tak przestraszyć tego nieustraszonego człowieka. Mówią, że był pokryty szronem. Jego ciało było pełne przerażających, poszarpanych ran, ale na podłodze ani kropli krwi! Wyobraź sobie! Ani kropli!";
			link.l1 = "Tak, to wygląda jak z najgorszego koszmaru. Wygląda na to, że został zamordowany... Ale kto mógł to zrobić?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Nie wiadomo. To jest zbyt zagmatwane... Lekarz garnizonowy powiedział, że jego rany nie były śmiertelne. Beltrope zmarł ze strachu, bólu lub czegoś innego. Tak czy inaczej, to jest mistyczna śmierć.";
			link.l1 = "Rozumiem... A kiedy rozpocznie się proces?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Wszystko zależy od ciebie, panie. Przedstawię wszystkie dokumenty w sądzie, jak tylko zapłacisz mi drugą część mojej opłaty - 450 dublonów. Helen zyska swoje prawa tydzień później.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Bardzo dobrze. Oto twoje doubloony.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Tak, oczywiście. Przyniosę ci potrzebną sumę.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Panie, zachwiałeś mną! Zrobiłeś tak wiele, wyspa była prawie w naszych rękach, ale teraz wszystko przepadło przez twoje opóźnienie z moją opłatą! Testament wygasł i Isla Tesoro należy teraz do angielskiej korony. To będzie baza wojskowa."link.l1 ="O rany! Wygląda na to, że wszystkie moje wysiłki poszły na marne...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Czy przyniosłeś drugą część mojej opłaty, panie?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Tak, oczywiście. Oto twoje dublony.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Proszę wybaczyć moją złą pamięć, zostawiłem je w skrzyni na moim statku. Przyniosę je natychmiast.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "Ale to... to zmienia wszystko! Opublikowanie listu Beatrice oznacza, że Lawrence Beltrope musi zostać natychmiast aresztowany i stanąć przed sądem za swoje przeszłe zbrodnie!\nA zeznania Bakera całkowicie zniszczą wszelkie argumenty przeciwko temu! To wspaniałe! Z takim asem w rękawie pokonamy Doyla uczciwie i sprawiedliwie!";
			link.l1 = "Jestem bardzo zadowolony. Kiedy rozpocznie się proces?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Doskonałe, Sir. Przyjemność robić interesy z tobą. Teraz, oto umowa. Wróć tu jutro. Tak-tak, dobrze słyszałeś - jutro! W końcu jestem najlepszym prawnikiem archipelagu i mam kontakty.\nPrzyprowadź swoją główną, proces nie odbędzie się bez niej. Nie spóźnij się i nie opuszczaj miasta. I weź ze sobą ostatnią część płatności, jeśli możesz, jestem całkowicie pewien naszego zwycięstwa.";
			link.l1 = "Dobrze. Będziemy w twoim biurze jutro, panie Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur? Nie, to Sharp! Cóż, teraz za mną!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Pozwól mi pogratulować ci, Panie, i twej przełożonej. Ona jest teraz prawowitą władczynią Ilsa Tesoro. Warto wypić za to trochę szampana!";
			link.l1 = "Absolutnie, panie Loxley. Twoja mowa była naprawdę znakomita. Myślałem, że pułkownik Doyle dostanie zawału serca, kiedy powiedziałeś sądowi, że Lawrence Beltrop jest kapitanem Rzeźnikiem.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Tak, pan Doyle będzie musiał pożegnać się ze swoim marzeniem o bazie wojskowej na Isla Tesoro. A cóż może zrobić? Prawo to prawo i jest napisane dla wszystkich, nawet dla szanownego pułkownika.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Czy wszystkie dokumenty są w porządku i potwierdzają prawo Helen do wyspy?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "Słyszałem, że sędzia wydał nakaz aresztowania Lawrence'a Beltropa. Czy to oznacza, że zostanie powieszony?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Oczywiście, Panie. Sprawdziłem każdy przecinek w nich. Możesz być pewien, że są w porządku.";
			link.l1 = "Bardzo dobrze...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Cóż, moja robota jest skończona. Sprawa była skomplikowana, ale wygraliśmy ją razem. Teraz, Sir, pozostaje tylko zapłacić mi ostatnią część mojej opłaty. Bez presji, zdaję sobie sprawę, że musisz być zajęty. Ale wierzę, że znajdziesz czas, aby dostarczyć mi ostatnie 450 doublonów w ciągu tygodnia.\nPoza tym, klient taki jak Ty zawsze może liczyć na znaczne zniżki. Mogę Ci bardzo pomóc, mam znajomości we wszystkich stolicach archipelagu, nawet w tych wrogich, więc każdy problem prawny, z jakim się zetkniesz, może być rozwiązany.";
			link.l1 = "Doskonałe. Teraz wiem, kogo zapytać.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = " Gwarantuję ci pozytywne rozstrzygnięcie nawet w najtrudniejszych sytuacjach.";
			link.l1 = "Miło. Muszę teraz iść, ja i Helen mamy dużo do zrobienia.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Żegnaj, sir.";
			link.l1 = "Żegnaj, Panie Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Przypuszczam, że tak, jest on kapitanem Rzeźnikiem, piratem i bandytą. Choć teraz nie ma go w Port Royal. Miał tyle szczęścia, że opuścił miasto, udając się w głąb wyspy. Ale polowanie się zaczęło i na pewno zostanie schwytany.";
			link.l1 = "Widzę... Czy dokumenty są w porządku?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Znakomicie! Z przyjemnością robiłem z tobą interesy, Sir! Teraz możesz prosić mnie o pomoc w każdej sprawie i otrzymać zniżkę. Kłopoty z prawem, nagroda za twoją głowę... Zapraszam. Zawsze będę się cieszył, widząc cię.";
			link.l1 = "Byłoby lepiej, gdybym trzymał się z dala od kłopotów, ale... rzeczy się zdarzają. Dziękuję i żegnaj, panie Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "Co masz na myśli, panie? Zamierzasz naruszyć warunki naszej umowy?";
			link.l1 = "Dokładnie. Zrobiłem większość pracy. Nie możesz nawet sobie wyobrazić, co musiałem zrobić, żeby zdobyć te dowody. A ty tylko wziąłeś te papiery i poszedłeś do sądu. Dziewięćset dublonów to więcej niż wystarczająco, jestem tego pewien.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Mówisz jak pirat, panie! Cóż, nie zbiednieję tracąc czterysta pięćdziesiąt doublonów, ale ty też się nie wzbogacisz. W rzeczywistości straciłeś znacznie więcej! I być może stracisz coś w przyszłości... Natychmiast opuść mój dom i nigdy więcej się tutaj nie pokazuj!";
			link.l1 = "I ja zamierzam to zrobić. Żegnaj, panie Loxley.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Nie chcę z tobą rozmawiać. Zjeżdżaj, bo zawołam straże!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Panie, wygralibyśmy twoją sprawę, gdybyś przyszedł do mnie wcześniej. Testament stracił ważność. Przykro mi.";
			link.l1 = "Eh, jestem jeszcze bardziej przykro! No cóż, żegnaj, panie Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+" , Sir. Cieszę się, że Cię widzę. Potrzebujesz moich usług?";
			link.l1 = "Tak. Dlatego tu jestem.";
			link.l1.go = "loxly_1";
			link.l2 = "Nie, na szczęście nie potrzebuję ich w tej chwili. Chciałem tylko cię przywitać.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Jestem gotów cię wysłuchać. Jakiej pomocy potrzebujesz.";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "Jestem w tarapatach z angielskimi władzami.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "Mam kłopoty z francuskimi władzami.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "Mam kłopoty z hiszpańskimi władzami.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Jestem w tarapatach z holenderskimi władzami.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Pokłóciłem się z przemytnikami.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Przykro mi, zmieniłem zdanie...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Już pracuję nad twoją sprawą. Wszystko będzie dobrze, mogę Cię zapewnić.";
			Link.l1 = "Dziękuję. Będę czekał.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = " "+sTemp+" z "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+"To będzie cię kosztować "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Zgoda, panie Loxley, zgadzam się. Oto twoje pieniądze i postaraj się załatwić sprawy jak najszybciej.";
				link.l1.go = "relation";
			}
			link.l2 = "Nie mam teraz sumy, o którą prosisz. Wrócę później!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "Przyjemność robić interesy z tobą, sir. Możesz znów swobodnie oddychać, twój problem zniknie w ciągu najbliższych dwóch tygodni. Proszę unikać jakichkolwiek konfrontacji z "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+", podczas gdy jestem w trakcie negocjacji.";
			link.l1 = "Dobrze, rozważę twoje ostrzeżenie. Dziękuję i żegnaj!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = " I dlaczego to zrobiłeś? Przemytnicy to dobrzy chłopcy, są uczciwi na swój sposób. Wszyscy musimy żyć i jeść... Dobrze, to nie jest wielka sprawa i będzie kosztować cię tylko "+FindRussianMoneyString(sti(npchar.quest.contrasum))+".";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "Zgoda, panie Loxley, zgadzam się. Oto twoje pieniądze i postaraj się załatwić sprawy jak najszybciej.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Nie mam teraz sumy, której żądasz. Wrócę później!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Doskonale, rozwiążę twój problem. Wkrótce znów będą chcieli z tobą robić interesy.";
			Link.l1 = "Dzięki!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
