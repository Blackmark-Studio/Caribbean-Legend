// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Dzień dobry, mynheer. Co cię sprowadza do naszego domu?";
					link.l1 = "Dzień dobry, Abigail. Nazywam się "+GetFullName(pchar)+". Służę Republice Holenderskiej Kompanii Zachodnioindyjskiej jako kapitan.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Boże wielki...! Znalazłeś pieniądze mojego ojca? Naprawdę?! Rany, nie potrafię nawet wyrazić, jak bardzo się cieszę! Proszę, idź natychmiast do ojca - chce z tobą jak najszybciej porozmawiać!";
					link.l1 = "Już idę, madame.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "Kapitanie, uratowałeś nas przed całkowitą rozpaczą! Nigdy ci tego nie zapomnę! Dobre imię rodu Shneur zostało uratowane!";
					link.l1 = "Madame, ja tylko spełniam swój obowiązek jako dżentelmen. Mam nadzieję, że nic już nie stoi na drodze do twego szczęścia.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Potrzebujesz czegoś, kapitanie?";
				link.l1 = "Nie, nie teraz, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Najświętsza Panno, Królowo Miłosierdzia! Jedyna nadziejo nasza. Do Ciebie wzdychamy, biedni grzesznicy... Proszę, przybądź nam z pomocą! Błagamy Cię, o Pani. Dojrzyj nasz płacz, naszą udrękę... spraw, aby Twój Przenajświętszy Syn zlitował się nad nami... Oh, mynheer! Przestraszyłeś mnie! Co Cię tu sprowadza?";
					link.l1 = "Wybacz mi, nie chciałem cię wystraszyć. Madame Abigail, jak mniemam? Przysłał mnie Richard Fleetwood...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Czy mogę doś dla ciebie zrobić, kapitanie?";
				link.l1 = "Nie, madame. Tylko się upewniam, że wszystko w porządku.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Hej, co tu się dzieje?! Tato, kim jest ten dziwaczny jegomość?";
					link.l1 = "Spokojnie madame. Abigail Schneur, jak zakładam? Proszę, wybacz to najście, ale mam dla ciebie bardzo ważny list od... Cóż, chciałem ci to wyznać, ale twój drogi ojciec nie pozwolił mi nawet wejść do środka...";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ach, oto jesteś, Charles. Jestem gotowa, by podążyć za tobą wszędzie!";
					link.l1 = "Chodźmy więc!";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Czy to już St. John? Kiedy wreszcie spotkam się z Richardem?";
					link.l1 = "Dokładnie tak, madame. Niestety, Richarda aktualnie tu nie ma - wysłano go na patrol w kierunku Barbaros. Wróci za kilka dni, więc nie musisz się martwić. Wszystko będzie dobrze.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles! Tak się cieszę, że jesteś! Czy masz jakieś wieści od Richarda?";
					link.l1 = "Niestety, madame, ale Richard nadal przebywa w Bridgetown. To tajna i bardzo ważna misja, coś związanego z Holendrami. Zakładam, że Richard powiedział ci, czym się zajmuje, tak?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "CCharles! Nareszcie! Myślałam, że już nigdy cię nie zobaczę!";
					link.l1 = "Witam, madame. Miło znów cię widzieć.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ach, wreszcie jestem w domu! Nawet nie wiesz jak tęskniłam za tym miejscem... i za tatą. Charles, nigdy nie zapomnę, co dla mnie zrobiłeś. Jesteś prawdziwym bohaterem.";
					link.l1 = "Ależ madame, to nic takiego. Zrobiłem jedynie to, co zrobiłby każdy dżentelmen, widząc damę w potrzebie. To mój obowiązek";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Tato, proszę... jeśli cokolwiek pamiętasz, powiedz to! Charles, on jest... można mu zaufać. Jest jedynym człowiekiem, który może nam pomóc!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "Rany, będę się za ciebie modlić dniami i nocami! Przysięgam! Tylko proszę... obiecaj mi, że to zrobisz! Że znajdziesz tę wyspę!";
					link.l1 = "Możesz być o to spokojna, madame. Masz moje słowo. Zrobię co tylko w mojej mocy.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles! Jak dobrze, że wróciłeś! Czy udało ci się znaleźć tę wyspę? Uwierz mi, ja już nie potrafię dłużej czekać!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "W takim razie mam dla ciebie dobre wieści! Tak, znalazłem wyspę, a na niej pieniądze twojego ojca. Przybyłem, by oddać je w twoje ręce.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Niestety, madame. Ja po prostu... cóż, zawiodłem. Nie zdołałem odnaleźć ani wyspy, ani kapitana Kellera. Zrobiłem, co mogłem, ale...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
                dialog.text = "Ach, Charles! To naprawdę ty! Czy czegoś ci potrzeba? Może filiżankę kawy?";
                link.l1 = "Nie trzeba, ale dziękuję. Nie kłopocz się.";
                link.l1.go = "exit";
                break;
			}
			dialog.text = "Dzień dobry, mynheer. Czego sobie życzysz?";
			link.l1 = "Nic, madame, wybacz to najście.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "Jestem zaszczycona tym spotkaniem, Kapitanie "+GetFullName(pchar)+". Uwierz mi, w mieście słyszałam niejedną historię o twoich przygodach. Jesteś człowiekiem, który przechwycił ten piracki statek widmo, a potem przywiózł do Willemstad jako łup! To naprawdę fascynujące! Tylko powiedz mi, proszę... czy to prawda, że dowodził nim sam... Richarda Fleetwood?";
			link.l1 = "Wszystko, co pani słyszała, to prawda, madame. I przyznam, byłem równie zaskoczony jak wszyscy, gdy poznałem prawdę. To... to czysty skandal! Oficer Królewskiej Marynarki grabiący własnych rodaków jak zwykły pirat! Heh, że też ten drań wpadł na pomysł, by ukrywać swoje występki, podszywając się pod statek-widmo, rzekomo działający dla Holenderskiej Kompanii. Używał tej fikcji, by zrzucać winę na Kompanię i potem atakować też nasze statki.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "Rany, aż mi słabo, jak o tym słucham... To straszne łajdactwo, Kapitanie. Znałam osobiście Richarda Fleetwooda i nigdy bym nie pomyślała, że on...";
			link.l1 = "Madame, Lucas Rodenburg poinformował mnie o waszej podróży z Recife do Curacao. Teraz wszystko się układa. Fleetwood zatopił wasz statek, a potem wrócił, by 'uratować' was z tej przeklętej wyspy. Nawet czytałem dziennik pokładowy tego łajdaka - opisał tam wszystko ze szczegółami.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Co za koszmar... Czyli mój papa miał rację. Od początku powtarzał, że to Richard był źródłem całego naszego nieszczęścia. Powinnam się cieszyć, że prawda wyszła na jaw, ale... Eh, wybacz mi, kapitanie. To po prostu mnie przerasta. Czego taki człowiek jak ty mógłby chcieć od zwykłej dziewczyny?";
			link.l1 = "Abigail, jestem tu z powodu bardzo skomplikowanej i delikatnej sprawy. Czy zechcesz mnie wysłuchać?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Oczywiście, mynheer. Zamieniam się w słuch.";
			link.l1 = "Jak już mówiłem, służę Kompanii. Lucas Rodenburg jest nie tylko moim przełożonym, ale i bliskim przyjacielem. Wysłał mnie tu z wiadomością - a raczej prośbą. Wiesz, on... chciałby cię poślubić. Jest gotów uczynić wszystko, byle tylko dać ci szczęście.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "O, kapitanie! Teraz rozumiem, dlaczego Mynheer Rodenburg nie zdobył się na to sam... Mój biedny papa byłby wniebowzięty, ale ja...";
			link.l1 = "Widzę, że coś cię dręczy, madame. Czy wątpisz w jego szczerość? Może mogę jakoś pomóc rozwiać twoje obawy?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "O nie, kapitanie, nie wątpię w jego intencje. Lucas zrobił dla mnie i mego ojca więcej, niż ktokolwiek inny. Nie wiem, co by się z nami stało, gdyby nie jego opieka. Ale musisz też zrozumieć moją sytuację! \nCo prawda nie jesteśmy jak Rothschildowie, ale też biedni nie jesteśmy. Shneurowie byli dobrze znani wśród europejskich bankierów z powodu naszego majątku... Ale teraz... ten okropny pirat nas zrujnował! Miasto wręcz huczy od plotek na ten temat. Służące, przekupki, damy - wszyscy gadają, że zależy mi tylko na majątku Rodenburga. 'Jak przystało na Żydówkę', mówią... bezwstydne języki! Mój biedny ojciec ukrył resztki naszego majątku na tamtej wyspie, próbując ocalić to, co zostało po śmierci moich braci i sióstr... \nAle on nie jest żeglarzem. Nie pamięta drogi. I nie wie, gdzie jest ta wyspa! Proszę cię, porozmawiaj z nim. Może zdołasz z niego coś wydobyć. I naprawdę - jeśli odnajdziesz tę cholerną wyspę i to, co zostało - uratujesz mnie przed hańbą i ocalisz imię mojej rodziny. Proszę cię, kapitanie...!";
			link.l1 = "Dobrze, Abigail. Zajmę się tym i porozmawiam z nim. Nie martw się, dziewczyno, zrobię wszystko, co w mojej mocy.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Dziękuję, mynheer! Naprawdę! Będę się modlić dniami i ojcami o ciebie i twój sukces. I niech Bóg naszych ojców będzie z tobą!";
			link.l1 = "Żegnaj, Abigail. Wrócę z dobrymi wieściami, przysięgam.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "O, tak! Mynheer Rodenburg to prawdziwie honorowy i życzliwy człowiek. Bez wahania oddam mu swoje serce i z dumą nazwę swoim mężem.";
			link.l1 = "Świetnie! W takim razie uważam swoją misję za zakończoną. No cóż, czas teraz wracać do Rodenburga i przekazać mu tę dobrą nowinę. Ale się ucieszy...! Żegnaj madame. Życzę wam szczęścia na nowej drodze i błogosławieństwa Bożego!";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard cię przysłał?! Błogosławiona Maryjo, dziękuję! Ach, panie! Słyszałem, że biedny Richard został ranny i jest bliski śmierci. Czy to prawda? Powiedz mi, czy on żyje?! Czy jest zdrowy?!";
			link.l1 = "Richard żyje i... w większości zdrowy. Oto najpierw złe wieści: jest trochę bardziej zużyty i tymczasowo oślepiony, ale wraca do zdrowia. A teraz dobre wieści: Richard chce, żebyś odpłynęła z nim do Anglii, gdzie się pobierzecie. Jego czas na Karaibach dobiegł końca i czeka na twoją odpowiedź.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ach, jak piękne są stopy tego, który zwiastuje dobrą nowinę! Mój drogi posłańcu, powiedz Richardowi, że dla wspólnego szczęścia pójdę za nim, dokądkolwiek zechce. Ale... Jest pewien problem. Boję się, że nasza ucieczka złamałaby serce mojego biednego ojca. Rany, jestem rozdarta i kompletnie nie wiem, co robić...! Chciałabym, aby Richard znalazł tę przeklętą wyspę i tą skrzynię z rodzinnym złotem... Może chociaż to w jakiś sposób by go wtedy pocieszyło? O Boże, zmiłuj się nade mną!";
			link.l1 = "Rozumiem... Moja misja polegała tylko na dostarczeniu cię na Antiguę, ale to nieco komplikuje sytuacje. Jeśli znajdę wyspę i skrzynię, i przyniosę ją tobie, czy wtedy pojedziesz ze mną do St. John's i Richarda?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "O tak, mynheer, będziemy się za ciebie modlić, daję słowo! Jeśli dane nam będzie mieć syna, nazwiemy go twoim imieniem. Dziękuję ci, kapitanie! Niech pan nasz Jezus Chrystus i Najświętsza Maryja Panna nad tobą czuwają!";
			link.l1 = "Nie każę ci długo na siebie czekać, madame. Wrócę wkrótce.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Och... Masz od niego list? Ależ, ojcze, nie bądź taki surowy dla naszego gościa! Przysparzasz mi wstydu tą swoją dziwną podejrzliwością! Mynheer, chodź ze mną, proszę. Chciałabym porozmawiać z tobą w cztery oczy.";
			link.l1 = "Dziękuję, madame Abigail. Miło wreszcie spotkać pod tym dachem kogoś rozsądnego.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Wybacz mojemu ojcu, mynheer. Jest naprawdę dobrym i życzliwym człowiekiem, ale to, co nas spotkało... po prostu nas zniszczyło.";
			link.l1 = "  W porządku, madame, to zrozumiałe. Pozwól, że się przedstawię, jestem Charlie... Knippel. Jestem tu z rozkazu Richarda Fleetwooda. On chce, żebym cię do niego przyprowadził. Proszę, oto list.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "O, Richard... (czyta). O, Boże! On postanowił... zwrócić ojcu wszystkie stracone pieniądze! Rany, to takie szlachetne... Aż się wzruszyłam (ociera łzę). Mój drogi, słodki Richard! Mynheer, przynosisz dobre wieści niczym sam Archanioł Gabriel! Gdzie on teraz jest? Na Curacao?";
			link.l1 = "Nie, madame. Próbowano go zamordować - został ciężko ranny. Leży teraz na Antigui... ale nie skończyłaś jeszcze listu. Czytaj dalej.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "O Najświętsza Maryjo, niepokalanie poczęta, módl się za nami, którzy się do Ciebie uciekamy! Słodki Jezu...! Błagam, powiedz mi, czy on jest bezpieczny?! Czy to coś poważnego?";
			link.l1 = "Nie martw się, madame! Richard to nie człowiek, którego można łatwo zabić. Odpoczywa teraz i wraca do sił. I co najważniejsze - pragnie, abym cię do niego zabrał. A potem...  odpłyniecie razem do Londynu. Ale proszę, skończ najpierw czytać list!";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ach, tak... Wybacz mi (czytanie). Mynheer Knippel, jestem gotowa popłynąć z tobą. Potrzebuję przynajmniej jednego dnia, aby spakować rzeczy, ogarnąć wszystko, no i też porozmawiać z ojcem. Wróć jutro - będę gotowa.";
			link.l1 = "Dobrze, madame. Przyjdę tu jutro. I proszę, nie martw się, ja i moja załoga ochronimy cię przed wszelkimi niebezpieczeństwami podczas naszej podróży.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Eh, szkoda. Cóz mogę powiedzieć... myślę, że zdołam poczekać jeszcze tydzień, skoro i tak już tyle czekałam.";
			link.l1 = "Dokładnie tak, madame. A żeby umilić ten czas, proponuję zmienić tę surową kajutę na dom mojego przyjaciela. Tam czeka na panią mięciutkie łóżko i wyśmienite jedzenie!";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Och, jesteś dla mnie taki dobry, Charlie. Dziękuję. Dobrze będzie znów stanąc na stałym lądzie... Mam już dosyć tego kołysania!";
			link.l1 = "Proszę za mną, panienko.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "Miło mi cię poznać, John. Dziękuję wam za tak uprzejmą gościnę!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "O, Charlie, musisz wiedzieć, że spotkałam się z Richardem tylko kilka razy i nie zdradził mi zbyt wiele o tym, co robi.";
			link.l1 = "To i tak zaskakujące, że ukrywał przed swoją miłością tak wielką tajemnicę. Otóz Richard wcale nie jest zwykłym kapitanem. To agent Tajnej Rady Jego Królewskiej Mości. To cholernie ważny człowiek, który zajmuje się delikatnymi zadaniami zleconymi bezpośrednio przez samego Lorda Protektora. Obecnie jego obowiązkiem jest rozbicie wpływów Holenderskiej Kompanii Zachodnioindyjskiej tutaj, na Karaibach.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Co...? Mynheer, o czym pan mówi?";
			link.l1 = "Tak, madame. Twój ukochany Richard - mój przyjaciel - jest człowiek wielkiej wagi. Zawsze cieszyła mnie jego przyjaźń, ale ostatnio stał się aż nazbyt tajemniczy także wobec mnie. Wszystko wskazuje na to, że prowadzi jakąś tajną operację. Przykro mi, że przez to nie może się z tobą spotkać.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, przerażasz mnie. Czy jesteś pewien, że nic mu nie grozi? Boję się, nawet nie wiesz jak bardzo.";
			link.l1 = "Wszystko jest w porządku. Tylko... nie spodobało mi się, że tak cię potraktował. Ale rozumiem - obowiązku ponad uczucia. Nawet wobec kogoś takiego jak ty.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "O mój drogi Charlie... Ale wiedz, że będę czekać na Richarda, choćby do końca świata. Może mogłabym wynając pokój w atawernie... Nie chcę wiecznie nadużywać gościnności Johna.";
			link.l1 = "Nie opowiadaj bzdur, madame! Twoja obecność to dla nas zaszczyt, a nie ciężar! Jak mógłbym pozowlić, by narzeczona mojego najdroższczego przyjaciela spała w tawernie?! Mój honor na to nie pozwoli!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Teraz naprawdę mnie wzruszyłeś. Jesteś dla mnie taki dobry... A przecież jestem tylko zwykłą dziewczyną, i do tego Żydówką...";
			link.l1 = "Madame! Ależ proszę tak nie mówić. Dla mnie jesteś prawdziwą damą i chrześcijanką z sercem ze złota. I ani mi się waż myśleć o tawernach! Nigdy sobie nie wybaczę, jeśli zawiodę cię w służbie Richardowi.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Dziękuję, Charlie. Cieszę się, że jesteś... taki szlachetny.";
			link.l1 = "To mój obowiązek, madame. Ale teraz muszę już iść. Jeśli chcesz, możesz swobodnie spacerować po mieście. W końcu siedzenie bez końca w czterech ścianach mogłoby przyprawić cię o ból głowy. Tylko uważaj na siebie, dobrze?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Cóż... Powiem ci, że John to intrygujący człowiek. Potrafi godzinami mówić o swoich proszkach, mieszankach i różnych... chorobach. Ale jest też uprzejmym i łaskawym człowiekiem. Zaczęłam chodzić też do lokalnego kościoła, tutejszy ksiądz jest taki miły i troskliwy... Jest dobrze, ale moje serce dalej tęskni za Richardem.";
			link.l1 = " Myślę, że wkrótce wróci. A jeśli czegoś potrzebujesz - Charlie Knippel jest do twojej dyspozycji.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "Słyszałem jakieś dziwne plotki o Richardzie... że podobno zniknął. Wiesz coś o tym, Charlie? Błagam, powiedz!";
			link.l1 = "Tak, Abigail. Przykro mi... Richard Fleetwood wyjechał do Anglii i już tu nie wróci. Podobno dostał awans, przeniesienie, albo coś w tym rodzaju. Ale tak szczerze, to po tym, co ci zrobił... nawet nie chcę więcej słyszeć jego imienia.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "O rany. Wiedziałam, że to się tak skończy... (szlocha). Jezu, dlaczego nie posłuchałam ojca?! Przynajmniej by się ucieszył, gdybym wyszła za Lucasa Rodenburga. O Boże...!";
			link.l1 = "Przebacz mi, madame...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "Ależ za co, Charlie? Przecież to nie twoja wina. Byłeś dla mnie taki dobry i wspierający przez ten cały czas!";
			link.l1 = "Niestety, to nie koniec złych wieści. Właśnie wróciłem z Curacao. Musisz wiedzieć, że Lucas Rodenburg został aresztowany za bunt i zdradę przeciwko Republice. Będą go wysyłać w kajdanach do Amsterdamu, by stanął przed sądem. Okazało się, że próbował zamordować Petera Stuyvesanta, dyrektora Kompanii. Usiłował też obalić gubernatora Willemstad i jest podejrzewany o morderstwo co najmniej jednej osoby. Wątpię więc, by Stadtholder go oszczędził.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Boże, Co za koszmar?! (łapie się za głowę). Chyba zaraz zemdleję! Słabo mi. Charles, czy to prawda...? Błagam, nie... powiedz mi, że to nieprawda! (szlocha)";
			link.l1 = "Przykro mi, madame. Naprawdę. Ale sytuacja jeszcze się pogarsza. Śledztwo w sprawiwe Rodenburga wykazało, że ten przeklęty pirat, który zatopił twóją fluitę, działał na rozkaz Lucasa Rodenburga. Prowadził on swoją własną, prywatną wojenkę przeciwko angielskiej flocie. Tak bardzo ci współczuję, Abigail... Wszyscy mężczyźni, z którymi miałaś do czynienia po tej stronie świata, to kłamcy, złodzieje i mordercy. Zasłużyłaś na kogoś lepszego";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Ja... jestem zgubiona. Nie wiem. Charles... proszę... zabierz mnie do Willemstad. Potrzebuję mojego taty...";
			link.l1 = "Oczywiście, moja droga. Z St. John's już cię nic nie łączy. Spakuj swoje rzeczy i pożegnaj się z Johnem. A potem natymiast wyruszymy w morze.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "Nie, Charlie, to ja ci dziękuję. Gdyby nie ty i John, nawet nie wiem, co by się ze mną stało. Jesteście jedynymi uczciwymi ludźmi, których spotkałem po tej stronie świata.";
			link.l1 = "Ojej... aż się zarumieniłem. To miłe, Abigail, dzięki. Cieszę się, że mogłem ci jakoś pomóc. I naprawdę przykro mi z powodu całego tego zamieszania.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Wiesz, Charlie, dużo myślałem podczas naszej podróży na Curacao. Teraz już wszystko jest dla mnie jasne - Richard Fleetwood, Lucas Rodenburg... to wszystko jest jak jakiś koszmar, który właśnie dobiegł końca. Jestem znowu z ojcem i możemy wrócić do normalności. \nNie będzie to łatwe - nie mamy żadnych pieniędzy. Ale jakoś sobie poradzimy. Musimy. Błogosławiona Maryja cały czas czuwa nad nami i wierzę, że się nami zajmie; ona nigdy nie zapomina o swoich dzieciach, nawet o moim upartym starym ojcu, który nie wierzy w Jej Syna.";
			link.l1 = "Abigail, proszę, pozwól mi wam pomóc!";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Pomóc? Ale jak, Charlie?";
			link.l1 = "Richard opowiedział mi historię o twoim rozbiciu i ocaleniu. Wiem też, że twój ojciec ukrył swoje rzeczy na pewnej nieznanej wyspie. Zamierzam ją znaleźć i przywieźć z powrotem twoje pieniądze.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "O, Charlie... To takie kochane z twojej strony. Ale nni ja, ani mój ojciec nie jesteśmy w stanie powiedzieć ci, gdzie konkretnie leży ta nieszczęsna wyspa... Nie jesteśmy żeglarzami. Poza tym podczas ataku byłam śmiertelnie przerażona - nie pamiętam nic oprócz krwi i przemocy.";
			link.l1 = "Proszę, spróbuj sobie przypomnieć - cokolwiek! Każdy drobiazg może mi pomóc, nawet ten najmniejszy. Może coś się wydarzyło tuż przed atakiem? Jak wygląda ta wyspa? Hm?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Wyspa... Jak wygląda? Po prostu jak wyspa. Zatoka, dżungla... Przepraszam, ale nie wiem, co mogę ci powiedzieć (kręci głową). Albo... chwila! Coś pamiętam! Nie wiem czy to ci cokolwiek da, ale kojarzę, że tuż przed atakiem piratów napotkaliśmy na obcą fluitę. Zaprosiliśmy tamtego kapitana na nasz statek, aby zjadł z nami kolacje. Pamiętam to, byłam tam. Może on wie coś o tej wyspie?";
			link.l1 = "Wow, Abigail! To już bardzo dużo mi daje! A jak miał na imię ten kapitan? A może kojarzysz nazwę tej fluity?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "Oj nie, nie pamiętam, Charlie. Naprawdę nie...";
			link.l1 = "Błagam, spróbuj sobie przypomnieć, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Będziemy na ciebie czekać. Uwierz mi, że jesteś naszą jedyną nadzieją... Będę się za ciebie modlić! Niech Bóg cię prowadzi!";
			link.l1 = "Wrócę najszybciej jak to tylko możliwe. Tymczasem żegnaj, Abi. Żegnaj, Salomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Och, drogi... jaka szkoda. Mieliśmy nadzieję, ale... dziękujemy mimo wszystko, Charlie, że chociaż spróbowałeś nam pomóc, gdy nikt inny nie chciał. Wygląda na to, że to jest los, który Bóg w swojej niepojętej mądrości mi wyznaczył. Pozostaje mi z ufnością podporządkować się Jego woli.";
			link.l1 = "Żegnaj, Abigail. Mam nadzieję, że wszystko się ułoży.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "Czy to... czy to prawda? Czy ty naprawdę przywiozłeś nam z powrotem ten zaginiony skarb? Och, Charlie!";
			link.l1 = "Tak, Abi, to prawda. Mam go przy sobie. Proszę, oto on. Należy do ciebie.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "Jezu! Aż nie mogę w to uwierzyć...! Charlie, jak mogę ci podziękować?! Jak?!";
			link.l1 = "Nie potrzebuję żadnych podziękowań, Abi. Tylko tyle mogłem dla ciebie zrobić. Najważniejsze, że teraz masz szansę zacząć wszystko od nowa - bez Rodenburgów, Fleetwoodów i innych podejrzanych indywiduuów, którzy będą chcieli cię wykorzystać. Zresztą jestem przekonany, że twój ojciec znajdzie sposób, aby te pieniądze poszły w ruch. Coś mi mówi, że u was to rodzinne.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Ależ Charlie, błagam, nie bądź taki bezczelny! Zrobiłeś tak wiele dla mnie...  i mojego biednego ojca. No cóż, przyznam, że bardzo przyzwyczaiłam się do twojej obecności w moim życiu. Bez przerwy, każdego dnia modliłam się za ciebie i obiecuję, że nadal będę to robić. Jesteś naszym aniołem stróżem. Sam Pan cię do nas zesłał, wierz lub nie. \nZanim jednak odejdziesz, chcę, żebyś wiedział, że drzwi naszego domu zawsze będą dla ciebie otwarte o każdej porze. I... proszę, pozwól mi cię pocałować, mój drogi Charlie...";
			link.l1 = "Cóż... tak, oczywiście Abi... jeśli nalegasz.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Niech ci Bóg błogosławi, Charles. U nas niestety wszystko po staremu... Jestem zmuszona żebrać o resztki przed kościołem.";
			link.l1 = "Trzymaj się mocno, madame. Niech Bóg będzie z tobą.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, to ty! Tak się cieszę, że cię widzę! Proszę, usiądź! Zaparzę kawę!";
			link.l1 = "Też się cieszę, że cię widzę, Abi. I dobrze wiedzieć, że u ciebie wszystko w porządku.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Ach, więc to tak?! Przyjąłem cię jako mego gościa, a ty postanowiłeś mnie okraść?! Straże!!!";
			link.l1 = "Stul pysk, głupia dziwko!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
