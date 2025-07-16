// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, co do diabła!";
				link.l1 = "Steven,   było nakładanie się. Nie mogłem ani przyjść, ani poinformować cię o mojej nieobecności...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Miło cię widzieć, kumplu! Jak mogę ci pomóc?";
				link.l1 = "Również cieszę się, że cię widzę. Chciałem ci podziękować za doskonale przeprowadzone przedstawienie!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Miło cię widzieć, kumplu! Jak mogę ci pomóc?";
				link.l1 = "Mam dla ciebie propozycję. Piracką, wiesz!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "To nasz klient! Robota skończona, twój baron siedzi w dobrze strzeżonym lochu. Może chcesz rzucić okiem, he-he?!";
				link.l1 = "Na to będę miał mnóstwo czasu, ha-ha. Czy dobrze go traktują?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Cieszę się, że cię widzę, kumplu! Jak mogę ci pomóc?";
				link.l1 = "Przyszedłem znów, aby prosić o twoją pomoc.";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Miło cię widzieć, przyjacielu! Jak mogę ci pomóc?";
				link.l1 = "Steven, mam coś dla ciebie.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Cieszę się, że cię widzę, kumplu! Jak mogę ci pomóc?";
				link.l1 = "Steven, muszę cię o coś zapytać. Może ci się to nie spodobać, ale potrzebuję twojej pomocy.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ha, oto jesteś, "+pchar.name+"Spodziewałem się twojego przybycia. Leśny Diabeł opowiedział mi o twoich kłopotach z Tortugą...";
				link.l1 = "Powiedział mi również, że już znalazłeś rozwiązanie. Czy to prawda?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "Jak nam idzie, "+pchar.name+"?";
				link.l1 = "Tajemnice wszędzie... Potrzebuję twojej rady, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "Tak, chcę ci coś pokazać... Chciałbyś pójść ze mną na molo?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ach, mój przyjacielu "+GetFullName(pchar)+" ! Wejdź, dobrze cię widzieć! Dlaczego przyszedłeś?";
				link.l1 = "Cześć, Steven! No cóż, dotrzymałem słowa i się pojawiłem. Czy twój statek jest gotowy?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "Więc co tam z twoim interesem? Nie porzuciłeś jeszcze tego przedsięwzięcia związanego ze 'Złotą Flotą'?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ach, mój przyjacielu "+GetFullName(pchar)+" ! Wejdź, miło cię widzieć! Dlaczego przybyłeś?";
			link.l1 = "Tak, odwiedziłem Isla Tesoro w interesach i postanowiłem wpaść na chwilę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha! Zgaduję, że jesteś naszym nocnym gościem? Zostałem poinformowany o tym wypadku zbyt późno. Sprawdziłem twoje rzeczy i znalazłem list od Leśnego Diabła. Cholera, prawie pachniał dżunglami Main\nTwoje imię to "+GetFullName(pchar)+"? Nie bądź zaskoczony, wyczytałem to z listu. Nazywam się Steven Dodson. Albo po prostu Rekin. Rekin. Myślę, że już o mnie słyszałeś. Obecnie zajmuję stanowisko admirała w tym mieście lub na tej wyspie, jakkolwiek\nPrzepraszam za działania moich ludzi zeszłej nocy. To było moje polecenie, aby schwytać każdego, kto wkradnie się do ładowni. Zbyt wielu złodziei wśród Narwali i Rivados\nChad pozwolił ci odejść, jak mniemam? Dziwne. Dopiero co miałem wysłać mu rozkaz, by cię uwolnił. Gdzie jest twój statek? Mam nadzieję, że wszystko z nią w porządku?";
			link.l1 = "Chad? O ile rozumiem, twój bosman nigdy nie pozwoliłby mi opuścić więzienia żywym. Zrobiłem to sam i uwolniłem też jednego czarnego gościa z tych... Rivados.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Opowiadasz mi ciekawe rzeczy, kolego. A jak udało ci się wydostać z 'Tartaru'? Wygląda na to, że będę miał miłą pogawędkę z Chadem i jego strażnikami...";
			link.l1 = "Nie będziesz z nimi rozmawiać. Obawiam się, że nigdy więcej się nie odezwą. Chad zagroził, że zamknie mnie w klatce na zawsze. Oskarżył mnie o bycie z Rivados i zażądał, żebym udowodnił, że jest inaczej, zabijając czarnego czarownika Chimiseta...";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Co do diabła?! Co za głupia samowola! Potrzebujemy Chimiseta żywego, a Chad doskonale o tym wiedział! I dlaczego założyłby, że jesteś z Rivados, skoro wszyscy oni są czarni? Co on kombinuje, niech go diabli wezmą?";
			link.l1 = "On knuje coś, co z pewnością ci się nie spodoba, Steven. Chad dał mi maczetę i wysłał mnie na dół, aby zabić Chimiseta. Ale stary Czarny powiedział mi coś ważnego i zdałem sobie sprawę, że jeśli zabiję Chimiseta, to ja będę następny...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Zamiast zabić starca, otworzyłem skrzynię z amunicją i walczyłem z Chadem i jego kumplami. Widzisz teraz, dlaczego nie możesz już z nimi rozmawiać? Wszyscy nie żyją.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Cholera! Wieści stają się coraz bardziej przerażające! I co ja mam z tym całym bałaganem zrobić?";
			link.l1 = "Słuchaj mnie, Steve. Chimiset powiedział mi, że Chad miał umowę z jakimiś Narwalami - to drugi klan, o ile rozumiem. Chad planował cię zabić i zająć twoje miejsce. Narwale pragną zobaczyć cię martwego, ponieważ są pewni, że zabiłeś ich przywódcę Allena... czy Alana, nie pamiętam.";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Bzdury! Nie zabiłem Alana! Ktoś inny to zrobił, może nawet Narwale. Myślę, że to ich obecny przywódca - Donald Greenspen - zabił Alana!";
			link.l1 = "Nie. Chad go zamordował. Chimiset był świadkiem zbrodni - dlatego chcieli go również zabić. Chad z jakiegoś powodu nie chciał tego zrobić sam - wygląda na to, że bał się jakiejś klątwy. Dlatego chciał, żebym ja wykonał robotę.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "Nie mogę w to uwierzyć... Chad zabił Alana? Ale dlaczego?";
			link.l1 = "Aby obciążyć cię winą i zrobić z ciebie wroga Narwali. Przypuszczam, że to on rozsiewał plotki, bo dlaczego Narwale obwiniliby tylko ciebie? Steven, planują cię zabić. A za to obwiniony zostałby klan Rivadów - choć nie wiem, jak zamierzają to zrobić. Chimiset mi o tym powiedział.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "Oprócz tego znalazłem ten list w skrzyni Chada. Przeczytaj go. Wygląda na solidny dowód, choć jest pośredni.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(czytanie)... heh! Nie dziwi mnie zdrada Chada. Sku...syn zawsze pragnął władzy na tej wyspie. Ale Narwale! Żeby naprawdę uwierzyć, że to ja zabiłem Alana! To będzie ich kosztować podwójnie za zapasy\nI tak planowałem uwolnić Chimiset, najwyższy czas się z nimi pogodzić. Zaskoczyłeś mnie, kumplu, szczerze mówiąc...";
			link.l1 = "Rozumiem, Steven. Też mi się to nie podoba, wplątałem się w jakiś polityczny bałagan odkąd dotarłem na Wyspę. Przybyłem tu tylko po to, by znaleźć ciebie i Nathaniela Hawka...";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Co? Hawk? Czyż nie jest na Jamajce? On jest baronem Maroon Town, dlaczego miałby być tutaj?";
			link.l1 = "Nie. Teraz dowodzi tam Jackman. Udało mi się dowiedzieć, że Hawk dotarł tam w ten sam sposób co ja - przez portal Kukulkana.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "Co to za bzdury? Jaki portal? I nadal nie odpowiedziałeś - gdzie jest twój statek?";
			link.l1 = "Nie ma statku. Rozumiem, Steve, że trudno w to uwierzyć, ale naprawdę dotarłem tu przez indyjski idol z Głównego... nie patrz na mnie tak - nie jestem szalony! Sam nie rozumiem, jak to możliwe, ale tak jest!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "";
			link.l1 = "Szaman w wiosce Miskito widział, jak Nathaniel Hawk, uciekając przed pościgiem, pobiegł do indiańskiego idola, znanego jako posąg Kukulkana, i nagle zniknął. Ten szaman powiedział mi, że sam był na tej Wyspie i że dostał się tam w ten sam sposób, przez posąg...";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "";
			link.l1 = "Szukam Nathana, dlatego musiałem iść jego śladami. Przyszedłem do posągu o północy, tak jak szaman mi powiedział. Nie uwierzysz, ale szczyt kamiennego posągu był tej nocy złoty, a nad nim świeciło tajemnicze światło!";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "";
			link.l1 = "Jak tylko dotknąłem posągu, wokół idola uformował się krąg światła, ogień buchnął, a potem zostałem wciągnięty do posągu. Zostałem wyrzucony tutaj, w ładowni twojego statku, na dole, blisko dziobu, przy wyrwie...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "";
			link.l1 = "Ledwo to przeżyłem, dzięki szamanowi, który dał mi specjalny eliksir. Na końcu zaatakował mnie jakiś potwór - olbrzymi krab. Mam nadzieję, że teraz mi ufasz?";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "Masz na myśli tę część o krabie? W to ci wierzę. Jest tu mnóstwo tych potworów wokół wyspy. Przyciągamy je zdechłą rybą, więc często pilnują naszego tylnego wejścia. Przerażają złodziei na śmierć. A to, co powiedziałeś o idolu - jeszcze nie zwariowałem\nAle też nie odrzucę twojej opowieści, miejscowi plotkują o takich rzeczach od kilkudziesięciu lat, a ja sam widziałem dziwne rzeczy dawno temu na statkach Rivados... nieważne.";
			link.l1 = "Przysięgam, że to wszystko prawda.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Dobrze. Niech tak będzie. Powiedz mi, dlaczego szukałeś mnie i Nathana? Według listu Jana, chciałeś, żebym został przywódcą Bractwa Wybrzeża?";
			link.l1 = "Dokładnie. Wiele się zmieniło po twoim i zniknięciu Hawka. Jackman próbuje odgrywać centralną rolę wśród piratów. Planuje zostać ich przywódcą, i uda mu się to, jeśli Jan i ja go nie powstrzymamy.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman jest gotów na poważną i krwawą grę. Jestem pewien, że to on zorganizował zasadzkę i polowanie na Nathaniela. Myślę także, że to on zabił Blaze'a. Uczynienie cię przywódcą Bractwa Wybrzeża to jedyny sposób, by go powstrzymać.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Patrz, byłbym rad, ale najpierw musimy opuścić tę wyspę. Mam jej już dość. Tym bardziej, że mogę tu zostawić Dextera, poradzi sobie z interesami pod moją nieobecność. Nie zamierzałem tu zostać tak długo, ale mój statek został spalony w walce z klanami\nNie zamierzam podróżować przez te portale, nawet nie próbuj mnie przekonywać, potrzebuję statku.";
			link.l1 = "Nie będę... Steven, szaman Miskito powiedział mi, że tutaj, na Wyspie, znajduje się statua Kukulkana. Wygląda jak zwykły kamienny idol. Wiesz, gdzie mogę ją znaleźć?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Nie znam. Nigdy nie widziałem takich posągów. Zapytaj kogoś innego.";
			link.l1 = "Widzisz, jeśli znajdę tę statuę, będę mógł opuścić tę wyspę bez statku. Podróż już mnie nie przeraża. A potem wrócę tutaj w normalny sposób i zabiorę cię stąd.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "Rozumiem, ale nie mogę Ci pomóc. Co więcej, ta sprawa z zamachem jest dość niepokojąca. Chad nie żyje, ale wątpię, że Narwale porzucą swój plan. Nie chcę żyć z myślą, że codziennie mogę dostać kulkę w plecy. Skoro potrzebujesz mnie żywego i już jesteś wplątany w ten bałagan, proponuję Ci zbadanie tej konspiracji\nJesteś nowicjuszem, to atut. Znajdź wspólników Chada i przyprowadź ich do mnie albo zabij na miejscu, nie obchodzi mnie to. Porozmawiaj z Chimisetem, stary czarny wie więcej, niż nam powiedział\nUważaj na Narwali, nie przekraczaj ich granic, chyba że masz hasło. Zmieniają hasła co tydzień.\nGdy zagrożenie zostanie wyeliminowane, zapewnię Ci kurs i wszystkie potrzebne informacje\nIdź i znajdź tych, którzy są odpowiedzialni. Przywróć porządek. Upewnię się, że po Tobie wyczyszczą więzienie. I potrzebujemy nowego strażnika. A ja potrzebuję trochę rumu, nie czuję się dobrze.";
			link.l1 = "Dobrze, Steven. Zróbmy to...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			pchar.rvd_friend = true; // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Just imagine: someone has killed the admiral's jailer, Chad Kapper. Impossible! No doubt, that was the Rivados wizard's job...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead. There was no official statement; his body was never found, either. Perhaps, the admiral had simply given him a secret mission?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I don't see our jailer Chad Kapper. Some people say that he was killed and some disagree. Anyway, no one has seen him dead.", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the admiral has doubled provision prices for Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Cóż, co masz, "+pchar.name+" ? Jakieś wieści o Narwalach?";
			link.l1 = "Tak. Ucieszy cię, Steve, że spisek został ujawniony, a spiskowcy nie żyją. Mam wszystkie dowody.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "Tak pomyślałem, gdy usłyszałem strzelaninę... Opowiedz mi więcej, słucham.";
			else dialog.text = "Czyżby? Bardzo się cieszę to słyszeć! Opowiadaj dalej, słucham cię.";
			link.l1 = "To wszystko zostało zaplanowane przez twojego bosmana, Chada Kappera. Zabił Alana Milrowa w więzieniu 'Tartarus', a potem rozprzestrzeniał plotki o twoim udziale. Myślę, że Narwale były naprawdę wściekłe, a to był ciężki cios dla dziewczyny Alana, Czerwonej Mary...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary była chętna do zemsty, a Chad Kapper wykorzystał to dla własnych celów. Opracowali sprytny plan zamachu na twoje życie. Wszyscy tutaj wiedzą o twoim zwyczaju spacerowania po rufie 'San Augustine' każdego wieczoru.";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Ha! Zastanowię się nad moimi nawykami... Kontynuuj.";
			link.l1 = "Potrzebowali muszkietu dalekiego zasięgu i dużej dokładności, aby zrealizować swój plan, więc Adolf Barbier im go dostarczył. Jednak jego sztucer został zastawiony u Giuseppe Fazio, więc Mary i Chad dali mu wystarczająco pieniędzy, by go wykupić. Adolf wydostał go z lombardu...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "Wynajęli Cyklopa Marcella, byłego królewskiego łowczego, by cię zabił. Miał otrzymać karabin i cię zastrzelić. Potem Mary miałaby go zabić i użyć jego ciała oraz karabinu jako dowodu, że to Rivados są odpowiedzialni za atak. Cyklop Marcello jest mulatem, wiesz...";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "Taki sprytny drań!";
			link.l1 = "Po tym Narwale i piraci zaatakowaliby Rivados i zniszczyliby ich. Chad zostałby admirałem, a Mary jego kochanką. Może jednak poderżnąłby jej gardło, ponieważ wiedziała za dużo. Całkiem prawdopodobne...";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "Ale cóż, to już koniec. Adolf nie był zbyt rozmowny i musiałem go zabić prosto w jego kajucie. Musiałem też poradzić sobie z Mary i Cyklopem, którzy przyszli odebrać stutzen od Adolfa. Od razu zorientowali się, kim jestem, i natychmiast mnie zaatakowali.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "Więc leżą wewnątrz 'Santa Florentina', prawda?";
			link.l1 = "Tak. Wszystkich trzech.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "To dobrze, że żadne świadki nie były zamieszane w ten bałagan. Zajmę się ciałami. Dobrze się spisałeś, "+pchar.name+"Gdybyś był w mojej załodze, na pewno uczyniłbym cię moim pierwszym oficerem.";
			link.l1 = "Dzięki za tak szybki odzew! I wreszcie, spójrz na te listy. Wziąłem je z ciał Cyklopa i biednej Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our squabbler and madcap Red Mary has disappeared. I won't be surprised if she is dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. Have you heard about it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she is still inside her cabin but I don't believe it. It's been too long since there last was light in it.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she had tough character, but everybody loved her. Who could have done such a terrible thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Tak czy inaczej, to już koniec. Adolf nie był wystarczająco rozmowny, musiałem go zabić prosto w jego kajucie. Musiałem także poradzić sobie z Mary i Cyklopem, którzy przyszli, by odebrać stutzen od Adolfa. Natychmiast zorientowali się, kim jestem, i od razu mnie zaatakowali.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Za szkoda, że rozpocząłeś bójkę na 'Ewie'. Teraz Narwale wiedzą, że to ty jesteś odpowiedzialny za zabicie ich ludzi, takie działania nie poprawią twojej reputacji. To samo można powiedzieć o mojej. Nie odwiedzaj ich, dopóki nie rozwiążesz tego konfliktu\nOgólnie rzecz biorąc, dobrze się spisałeś, "+pchar.name+" ! Gdybyś był w mojej załodze, na pewno uczyniłbym cię moim pierwszym oficerem.";
			link.l1 = "Dzięki za tak szybką odpowiedź! A teraz spójrz na te listy. Zabrałem je z ciał Cyklopa i biednej Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you have performed here! Narwhals won't forget about it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits... But the girl, why have you killed the girl? Poor Mary...", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = " Biedna Mary? Żal ci tej dziwki?";
			link.l1 = "Naprawdę jestem. Widzisz, Chad ją oszukał i wykorzystał. Nie mogła oprzeć się swoim uczuciom i naturalnej porywczości... i to ją zgubiło.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Cóż, idź zobaczyć się z bratem Julianem i zapal świecę... Sam tego jednak nie zrobię. Dobrze, porzućmy ten temat. Jestem ci wdzięczny, "+pchar.name+", za twoją pomoc. Możesz teraz liczyć na moje wsparcie. Chcę ci zapłacić za twoją doskonałą pracę. Oto pięćset dublonów.";
			link.l1 = "Miło, dzięki!";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say that the admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "Czego chcesz? Nie pamiętam cię...";
			link.l1 = "Oczywiście, że nie - nigdy wcześniej się nie spotkaliśmy, a ja przybyłem tu całkiem niedawno. Witaj, Steven. Co za rzadka fortuna! W końcu cię znalazłem, szukałem cię, choć nie spodziewałem się znaleźć cię tutaj!";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "„Czekaj, przyjacielu, uspokój się. Szukasz mnie? Nie podoba mi się to. Dlaczego do diabła mnie szukałeś?”";
			link.l1 = "Rozumiem. Spróbujmy więc jeszcze raz. Proszę, weź list. Napisał go Jan Svenson specjalnie dla ciebie. Myślę, że wszystkie twoje podejrzenia znikną po jego przeczytaniu.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(czytając)... Hm. To wiele wyjaśnia. A ja myślałem, że dasz mi czarną plamę za śmierć Blaze'a. Wiesz, ostatnio było wielu, którzy chcieli to zrobić. Zostawiłeś swój statek na zewnętrznym pierścieniu? I skąd wiedziałeś, że tu jestem?";
			link.l1 = "Nie zrobiłem tego. To był szczęśliwy traf. A co do Blaze'a... Jan i ja uważamy, że nie ponosisz odpowiedzialności za jego śmierć.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "A masz rację. Nie jestem. Ktoś próbuje mnie wrobić, to prawda. Ale to nie ja go zabiłem.";
			link.l1 = "To dobrze. Interesujące, przybyłem tu, by znaleźć Nathaniela Hawka, ale zamiast tego znalazłem ciebie, ha-ha!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "Rozumiem, ale nie mogę ci pomóc. Musisz o tym porozmawiać ze staruszkami tej Wyspy. Porozmawiaj z czarodziejem Rivados, Chimisetem. Stary czarny człowiek wie znacznie więcej, niż mówi.";
			link.l1 = "I gdzie mogę znaleźć tego czarodzieja?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "W moim więzieniu, na 'Tartarusie'. I tak zamierzałem go uwolnić, czas poprawić nasze stosunki z Rivados. Tak! Idź do więzienia, powiedz Chad'owi Kapper'owi, on jest strażnikiem, że rozkazałem uwolnić Chimiset\nPowiedz czarnemu człowiekowi, dlaczego cię wysłałem, powiedz mu, że uwolnię go, jeśli będzie wystarczająco rozmowny. Jestem pewny, że to sprawi, że zacznie mówić.";
			link.l1 = "Hm... Jestem tu nowicjuszem. Gdzie jest więzienie?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Zachowaj to na uwadze. Opuść moją rezydencję, przejdź przez most, skręć w lewo, przejdź przez fregatę Carolina do galeonu Gloria, a dotrzesz do Esmeraldy. Poszukaj znaku sklepu i wejdź przez drzwi pod nim. Przejdź przez drzwi w dziobowej części statku, a dotrzesz do Tartaru\nUważaj na Esmeraldzie, to własność klanu Narwali, mimo to, inni mogą ją odwiedzać. Nie wchodź w konflikty z ich wojownikami i unikaj kłopotów.";
			link.l1 = "Kim są ci Rivados i Narwale?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "Klany żyją tu od bardzo dawna. Reprezentują potomków pierwszych osadników. Narwale to głównie Anglicy, Holendrzy i Francuzi, Rivados to wszyscy Murzyni. Każdy klan ma przywódcę, mają kilka statków i nie wpuszczają innych na swoje terytorium\nMusisz znać hasła, aby ich odwiedzić. Zmieniają hasła co tydzień.";
			link.l1 = "Dobrze. Zajmę się tym. Czy pozwolą mi wejść do więzienia?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "Oni to zrobią. Oto klucz, aby Chad wiedział, że ja cię tam wysłałem. Weź to.";
			link.l1 = "Dobrze. Porozmawiam z tym... Chimisetem, a potem wrócę z wynikami.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "Więc, byłeś na 'Tartarze'?";
			link.l1 = "Tak. Przekazałem twoje rozkazy Chad'owi i rozmawiałem z czarnoskórym.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Czy czarodziej powiedział ci coś interesującego?";
			link.l1 = "O tak. Powiedział mi, gdzie znaleźć idol teleportacyjny Kukulkana. Był na statku 'San Geronimo', który zatonął na mieliźnie w pobliżu terytorium Narwali.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha, świetnie! Więc twój 'portal' jest teraz na dnie? Cóż, przyjacielu, obawiam się, że utknąłeś na tej wyspie. Dołącz więc do mnie i moich ludzi...";
			link.l1 = " Znajdę sposób, by dostać się do idola. Znajdę drogę. Teraz. Chimiset powiedział mi, że nie powinieneś ufać Kapperowi, ponieważ widział na własne oczy, jak Chad zabił jakiegoś Alana Milrowa, przywódcę Narwali.";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "Co?! Chad zabił Alana? Ten czarodziej jest szalony! To po prostu nie może być prawda!";
			link.l1 = "Wiesz, Steve, Chimiset jest naprawdę przerażony. Nie sądzę, że kłamał.";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Cholera, to naprawdę złe wieści! Zabójstwo Alana już i tak zrujnowało moją reputację wśród Narwali - niektórzy z nich uznali, że to ja jestem za to odpowiedzialny, a teraz okazuje się, że jeden z moich oficerów mógł to zrobić!";
			link.l1 = "Wydaje się, że ludzie lubią obarczać cię winą za grzechy, które nie są twoje...";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Tak, to niepokojące...";
			link.l1 = "A teraz, najprzyjemniejsza wiadomość dla ciebie - starzec powiedział mi, że podsłuchał kilka rozmów i dowiedział się, że niektórzy z twoich ludzi planowali cię zabić. Powie ci więcej dopiero po tym, jak go uwolnisz, i to na osobności.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Wspaniale! I wszystko to przez ciebie! Bez urazy, tylko żartuję. Kręci mi się w głowie: Chad zabił Alana, moi ludzie planują zamach na moje życie... Czy stary czarny człowiek powiedział ci jakieś szczegóły?";
			link.l1 = "Nie. Z tego co zrozumiałem, zbytnio obawia się Chada.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Dobrze. Powiem Rivados, że chcę spotkać się z Chimisetem. Zobaczymy, co mi powie. A co do próby... dobrze, będę ostrożny. Więc, co teraz zamierzasz zrobić, "+pchar.name+"?";
			link.l1 = "Nic szczególnego na razie. Pochodzę po Wyspie i poznam miejscowych - może wpadnę na pomysł, jak się stąd wydostać. Najpierw muszę znaleźć Natana Hawka, to dla niego tu jestem.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Rozumiem. Nie zapomnij odwiedzić mnie, kiedy znajdziesz sposób, by opuścić tę wyspę - dam ci wskazówki żeglugowe, bez nich nie będziesz mógł tu wrócić. Powiem ci także o kilku ważnych szczegółach.";
			link.l1 = "Dobrze. Na pewno cię odwiedzę, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = "To dobrze, że przyszedłeś, "+pchar.name+" . Czekałem na ciebie. Złe wieści. Chimiset nie żyje, Chad Kapper zniknął bez śladu.";
			link.l1 = "Cholera... Jestem pewien, że Chad zabił Chimiseta! Stary czarny człowiek nie bez powodu był tak przestraszony.";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Nie mam co do tego wątpliwości. Cholera, sytuacja pogarsza się z każdą godziną. Prawie udało mi się nawiązać solidne i uczciwe kontakty z Czarnym Eddiem, a teraz to. Cóż, możemy zapomnieć o przyjaźni z Rivadosem\nWiedzą, że rozmawiałeś z Chimisetem przed jego śmiercią i uważają cię za jednego z moich ludzi, więc unikaj kontaktu z nimi.";
			link.l1 = "Tak, co za szkoda...";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "Prosiłem cię, abyś przyszedł nie tylko po to, by przekazać wieści. Otrzymałem list od naszego mediatora i dyplomaty, Giuseppe Fazio, zaprasza mnie do odwiedzenia jego kabiny w Karolinie o północy. Wspomina również, że muszę przyjść sam, ponieważ stawką jest moje życie i nikomu nie można ufać\nTo ma sens, Chimiset ostrzegł nas o zdrajcy blisko mnie. Jednak to pachnie zbyt podejrzanie... sam, o północy... Zwykle sam gruby człowiek przychodzi do mnie. W każdym razie, zamierzam poprosić cię o pomoc\nTechnicznie rzecz biorąc, nie jesteś jednym z moich ludzi i jesteś tu nowy. Jan scharakteryzował cię jako zaradnego i odważnego człowieka z dobrymi umiejętnościami w szermierce. Chcę, abyś eskortował mnie na spotkanie o północy...";
			link.l1 = "Nie musisz mnie pytać, Steven. Wchodzę w to. Też mi się nie podoba to zaproszenie - pachnie pułapką.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Być może się mylę i nie ma żadnej pułapki, ale lepiej być gotowym. Cieszę się, że się zgodziłeś. Przyjdź na pokład 'San Augustine' o północy, a pójdziemy zobaczyć Fazio, jego stara łajba nie jest daleko stąd.";
			link.l1 = "Umowa stoi. Będę na pokładzie 'San Augustine' o północy, dobrze uzbrojony.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Miło cię widzieć, "+pchar.name+"Nie traćmy czasu i zobaczmy, co ten grubas Fazio ma do powiedzenia. Podążaj za mną!";
			link.l1 = "Chodźmy, Steve. Trzymaj broń gotową...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "A gdzie ten cholerny grubas? Gdzie się podział? Jesteśmy jego gośćmi, a on nas nie wita. Widzisz go, "+pchar.name+"? Może powinniśmy sprawdzić jego skrzynie, może tam się ukrywa...";
			link.l1 = "Nie zdoła otworzyć żadnej skrzyni na świecie, tak czy inaczej. Cisza! Steven! Na zewnątrz coś słychać...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "Cholera! Masz rację. Wygląda na to, że mamy kłopoty."+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "caroline_4";
		break;
		
		case "caroline_4":
			DialogExit();
			LAi_SetPlayerType(pchar);
			// запускаем Мэри, Чада и нарвалов - будет лютое рубилово
			sld = characterFromId("Capper");
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
			sld = characterFromId("Mary");
			sld.greeting = "mary_4";
			int iScl = MOD_SKILL_ENEMY_RATE*10 + 2*sti(pchar.rank);
			LAi_SetHP(sld, 250+iScl, 250+iScl); // усилим
			sld.dialog.currentnode = "caroline";
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "caroline_5":
			dialog.text = "Argh! Zrobiliśmy to... Szczerze mówiąc, myślałem, że na pewno jesteśmy martwi.";
			link.l1 = "Byłem w tarapatach gorszych niż te. Ale przyznaję, te sukinsyny były twarde. Chimiset miał rację, ostrzegając nas - Chad to zdrajca. Kim była dziewczyna, która nimi dowodziła?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Jej imię to Mary Casper, znana również jako Czerwona Mary, była dziewczyna nieżyjącego Alana Milrowa. Rozumiem, dlaczego Chad tu przybył, chciał zdobyć moje stanowisko, ale co ona tutaj robiła?";
			link.l1 = "To jasne. Powiedziałeś, że była jego kochanką, jej zamiary są oczywiste - zemsta. Biedna dziewczyna nie wiedziała, że walczy po tej samej stronie z mordercą swojego chłopaka.";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Ma to sens. Cóż, teraz zapłacą za wszystko! Przestanę im sprzedawać zapasy i prowiant - niech zginą z głodu. Moi ludzie wytrzymają każde oblężenie, a jeśli Narwale spróbują szturmować San Augustine, zastrzelimy ich jak psy\nBędą żałować, że wystąpili przeciwko mnie w tak nikczemny sposób. Przybiję tłuste dupsko Fazio do ściany za moim krzesłem!";
			link.l1 = "Poczekaj, Steve.  Wydaje się, że to nie jest takie jasne. Daj mi jeden dzień, a spróbuję zbadać ten bałagan. Jestem pewien, że Chad jest jedynym odpowiedzialnym. Zabił Milrowa, rozpuścił plotkę, że to ty, wykorzystał dziewczynę Alana...";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "Dobrze. Zbadaj sprawę. Być może jeszcze nie odkryliśmy wszystkich spiskowców. A ja pójdę i napiję się rumu. I, "+pchar.name+"Jestem ci dłużny. Możesz na mnie liczyć we wszystkim. Dostałbyś stanowisko bosmana, gdybyś był w mojej załodze.";
			link.l1 = "Dzięki za tak szybką odpowiedź! I tak będziemy współpracować, gdy zostaniesz przywódcą Bractwa Wybrzeża. Idź i odpocznij, a ja sprawdzę tę kajutę, może znajdę coś użytecznego.";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Dobrze. Wyślę tu moich ludzi, by posprzątali przed porankiem - nie chcemy straszyć ludzi martwymi ciałami. Cóż, kraby będą miały dziś w nocy wyśmienity posiłek! Do zobaczenia!";
			link.l1 = "Do zobaczenia...";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Cóż, "+pchar.name+"Rozumiem, że Twoje śledztwo przyniosło owoce?";
			link.l1 = "Można tak powiedzieć. Narwale nie są zaangażowane w zamach na twoje życie. Z wyjątkiem Mary i tych ludzi, którzy spotkali nas na 'Carolinie'. Myślę, że to ona podżegała ich do ataku na nas. Fazio został zmuszony, by wysłać ci zaproszenie. Znalazłem list w jego kabinie, który wiele wyjaśnia. Przeczytaj go.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "„(czytając)... Hm. To wygląda jak robota Fazia. Cóż, co mógł zrobić przeciwko Chad... ratował swoją tłustą skórę. Wygląda na to, że to wszystko przez mojego bosmana...”";
			link.l1 = "Widzisz to teraz na własne oczy. Motywy są jasne, i wiemy, dlaczego Chad zabił Chimiseta i Alana. Kapper chciał zostać admirałem wyspy. Odwiedziłem szefa Narwali - Donalda Greenspana. Przysiągł, że ani on, ani żaden z jego ludzi nie spiskowali przeciwko tobie.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Czy mu ufasz?";
			link.l1 = "Tak, zrobię to. Donald oczyści twoje imię z zarzutów o śmierć Alana. Jest gotów odwiedzić cię osobiście i przynieść oficjalne przeprosiny. Pamiętasz, że ciebie też niesłusznie oskarżono?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = " Dobrze, ogłoszenie wojny byłoby przesadą. Nie jesteśmy w sytuacji, by rozpoczynać rozlew krwi. Poza tym, wygląda na to, że tylko kilku łajdaków za to odpowiada, a nie cały klan\nMówisz, że Donald jest gotów przeprosić? Dobrze, wykorzystajmy to, by nawiązać pozytywne relacje z Narwalami, Rivados i tak są dla nas straceni.";
			link.l1 = "To dobry punkt, Steven. Teraz jest na to idealny czas.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Dobrze. Powiedz Donaldowi, że jestem gotów go zobaczyć i zawrzeć pokój.";
			link.l1 = "Jestem w drodze.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Czekaj, "+pchar.name+"Spisałeś się dobrze i chcę ci zapłacić szlachetną monetą. Oto, weź te pięćset dublonów.";
			link.l1 = "Dziękuję!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "W moim więzieniu 'Tartarus'. Możesz tam pójść i go zobaczyć. Dam ci klucz, a Chad Kapper nie będzie ci przeszkadzał...";
			link.l1 = "„Poczekaj, Steven. Myślę, że nie powinienem jeszcze iść do Chada Kappera...”";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "A czemużby nie? Co, nie lubisz go?";
			link.l1 = "Właściwie to ciebie nie lubi. Mam dla ciebie złe wieści. Chad Kapper planuje zamach na twoje życie.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Co?! Wytłumacz się. Kto to powiedział?";
			link.l1 = "Pozwól, że opowiem ci całą historię. To będzie lepsze.";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "No, powiedz mi zatem...";
			link.l1 = "Po tym, jak znalazłem się w zatopionej ładowni, wydostałem się przez dziurę i przepłynąłem wśród wraków statków, aby znaleźć bezpieczne miejsce. W końcu wspiąłem się na stary flet i dostałem się do środka statku. Tam była walka między jakąś dziewczyną w czerwonej kurtce a dwoma dużymi facetami...";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Heh, wygląda na to, że Czerwona Mary w końcu kogoś wkurzyła.";
			link.l1 = "Pomogłem jej i skończyliśmy z tymi draniami. Potem mieliśmy ciekawą rozmowę... Powiedz mi, Steve, kim są ci Narwale i Rivados, używała tych słów tak często, że byłem zbyt nieśmiały, by zapytać ją, co one właściwie znaczą.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Grupy miejscowych mieszkańców, którzy żyją tutaj od dawna. Są potomkami pierwszych osadników Wyspy Sprawiedliwości. Narwale to głównie Anglicy, Holendrzy i Francuzi, Rivados to wszyscy czarnoskórzy. Te klany mają swoich własnych przywódców, swoje własne statki i nie wpuszczają innych na swoje terytoria. Musisz znać ich hasła, jeśli chcesz odwiedzić statki klanów. Zmieniają je co tydzień.";
			link.l1 = "Teraz rozumiem. Rozumiem, że Mary jest z Narwalami?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Tak, ta ekspresywna dziewczyna jest z ich klanu. Więc co ci powiedziała?";
			link.l1 = "Chad Kapper zabił Alana Milrowa, jej kochanka, którego schwytałeś. Potem rozprzestrzenił plotki o twoim udziale w tym. Chad oszukał Mary i próbował wykorzystać jej pragnienie zemsty.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Do diabła! Zabił Alana? Ale dlaczego? By zrzucić na mnie winę?";
			link.l1 = "Aby uczynić Narwale wrogimi wobec ciebie i zdobyć ich zaufanie. Ostatecznym celem Kappera jest wyeliminowanie cię i zajęcie twojej pozycji. Mary odmówiła udziału w jego planie i zostania jego kochanką - dlatego rozkazał Narwalom ją zabić.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Czy ona ci to powiedziała?";
			link.l1 = "Tak. I nie wyglądało na to, że kłamała. Poza tym, dała mi list od Chada Kappera. Już go przeczytałem, więc ty też powinieneś to zrobić.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Chm. Tak, to są pisma Chada. Doskonale znam jego chłopskie pismo (czyta) Argh! Niewiarygodne! Drań! Zdrajca! No cóż, powieszę go na jego własnych wnętrznościach! Layton! Zbierz pięciu ludzi! Z drugiej strony, Layton, czekaj, odwołane!\nZrobimy to sprytnie. Planowałem polepszyć nasze stosunki z Rivados, to jest szansa. Ich czarownik Chimiset jest trzymany w Tartarusie. Więzienie. Pozwolimy Rivados uwolnić swojego człowieka samodzielnie, a przy okazji zabiją zdrajcę.\nLayton! Idź do Tartarus i zabierz wszystkich naszych strażników z jej górnego pokładu!"+pchar.name+", ty również weźmiesz w tym udział, a ja zamierzam powierzyć ci bardzo ważną rolę. Znajdź przywódcę Rivados, Czarnego Eddiego, i negocjuj z nim...";
			link.l1 = "Ja? Hm. Ale nie znam tu nikogo!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "So you will get to know some people soon - actually you will get to know the very first man of the entire Rivados clan. You are the most suitable candidate to perform the diplomatic part of my plan. My pirates won't be able to come through Rivados territories easily; also I don't have men with decent oratory skills.";
			link.l1 = "No dobrze. Zajmę się tym. Co mam zrobić?";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Weź ten klucz. Otwiera każde drzwi na 'Tartarusie'. Weź też te pięćdziesiąt dublonów. Najpierw powinieneś udać się do 'Carolina', kupić hasło, aby uzyskać dostęp do terytorium Rivados. Porozmawiaj z Fazio, jest naszym mediatorem, hasło będzie kosztować cię pięćdziesiąt dublonów. Następnie powinieneś udać się do 'Protektor'\nTo rezydencja Czarnego Eddiego. Powiedz mu, że Chad Kapper jest po stronie Narwali, przestał wykonywać moje rozkazy i zamierza zamordować Chimiseta. Daj mu klucz, powiedz, żeby zebrał odpowiednią liczbę swoich wojowników i zaatakował 'Tartarus'\nUpieczemy dwie pieczenie na jednym ogniu: Rivados uznają nas za swoich sojuszników, a Kapper zginie z rąk Czarnych. Nie mogę powiedzieć, że mu zazdroszczę. Zrozumiałeś?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "Rozumiem - ale gdzie znaleźć 'Protektora' i 'Karolinę'?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Słuchaj, Steve, powiedz mi, kim są ci Rivados i Narwale. Ciągle o nich mówisz, ale nadal nie mam pojęcia, kim oni są.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "Narwale i Rivados to lokalne klany. Klany żyją tu od bardzo dawna. Reprezentują potomków pierwszych osadników. Narwale to głównie Anglicy, Holendrzy i Francuzi, Rivados to wszyscy Murzyni. Każdy klan ma lidera, posiadają kilka statków i nie wpuszczają innych na swoje terytorium\nMusisz znać hasła, aby ich odwiedzić. Zmieniają hasła co tydzień.";
			link.l1 = "Teraz rozumiem. Powiedz mi - gdzie znaleźć 'Protektora' i 'Karolinę'?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Łatwizna. Opuść moją rezydencję, przejdź przez most i skręć w lewo. To będzie Carolina. Znalezienie Protektora jest nieco trudniejsze: po przejściu przez most, skręć w prawo i idź do Santa Florentina po deskach\nZnajdź tam żołnierzy Rivados. Zapytają o hasło. Powiedz je głośno i wyraźnie. Następnie wejdź do Fury i wejdź do Protektora przez rufę.";
			link.l1 = "No cóż, teraz rozumiem. Myślę, że nie będę za nimi tęsknił.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Bardzo dobrze, zatem. Do dzieła, przyjacielu!";
			link.l1 = "Do zobaczenia!";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Jeszcze tu jesteś? Idź teraz do Rivados!";
			link.l1 = "Jestem w drodze!";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Heh, wygląda na to, że Czerwona Mary w końcu kogoś wkurzyła.";
			link.l1 = "Tak. Wkurzyła Chada Kappera. Dołączyłem do walki, ale niestety, nie udało mi się uratować dziewczyny, jeden z napastników przeciął ją szablą.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Przykro mi z jej powodu, oczywiście, ale to bez wątpienia była jej wina. Mary zawsze szukała kłopotów. A co z Chadem Kapperem? To mój bosman, w rzeczy samej.";
			link.l1 = "Twój bosman? He-he... Tutaj, przeczytaj ten list. Znalazłem go przy ciele dziewczyny. Zobaczysz teraz, kto zlecił jej zabójstwo i dlaczego. Kapper planuje zamach na twoje życie.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Gdzie się podziewałeś tak długo? Powiedziano mi, że Rivados uwolnili swojego czarodzieja...";
			link.l1 = "Byłem przetrzymywany jako zakładnik na 'Protektorze', aby zapewnić im bezpieczeństwo przed zasadzką. Uwolnili Chimiset, tak, ale Chad zdołał uciec.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Cholera! Mówią, żeby nigdy nie robić interesów z czarnymi... Nie potrafili nawet wykonać tak prostego zadania! Pieprzyć tych Rivados!";
			link.l1 = "Chad ukrył się wśród Narwali...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Z pewnością, że tak! Nie jest głupcem i zdał sobie sprawę, że Rivados nie mogliby dostać się do Tartarus bez mojej pomocy. Teraz będzie się ukrywał i atakował z cieni. Layton! Umocnij posterunki! Miej oczy otwarte przez cały czas! Zapłacę fortunę temu, kto poradzi sobie z Kapperem!";
			link.l1 = "Dobrze, Steven. Muszę to przemyśleć. Może uda mi się wytropić Chada. Do zobaczenia.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "Co się stało, "+pchar.name+" ? Wyglądasz, jakby gonił cię sam Lucyfer.";
			link.l1 = "Przywieźli ci beczkę whisky?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Jaka beczka?";
			link.l1 = "CZY PRZYNIEŚLI CI BECZKĘ WHISKEY?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Czemu tak krzyczysz, kumplu? Nie, nie zrobili tego. O co chodzi?";
			link.l1 = "Dzięki Bogu, że przybyłem na czas... Chad Kapper kupił beczkę Bushmills od Axela Yosta...";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills? To mój ulubiony! Nie piłem tego od wieków!";
			link.l1 = "Tak-tak. I Kapper też to wie. Poprosił również swojego kumpla, Marcello Cyklopa, aby kupił trochę arszeniku od Sancho Carpentero. Widzisz, dlaczego?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Czy myślisz, że on zamierza mnie otruć?";
			link.l1 = "Bez wątpienia! Dlatego tak się spieszyłem. Jeśli przyniosą ci beczkę whisky - nie pij jej. Jest zatruta.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Heh, dzięki za ostrzeżenie! Będę ostrożny. Czekaj, dokąd teraz idziesz?";
			link.l1 = "Muszę znaleźć Kappera i Cyklopa. Mam pomysł, gdzie ich szukać. Do zobaczenia!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha! Cieszę się, że cię widzę, kumplu! Wygląda na to, że jestem ci winien życie.";
			link.l1 = "Czy przynieśli whisky?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "Maję! Bushmills, tak jak mówiłeś. Nasz drogi Fazio był tak uprzejmy... Aresztowałem go, by przeprowadzić śledztwo...";
			link.l1 = "Czy się przyznał?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Tak. Mówi, że Kapper zmusił go do tego. Był przerażony i... przyniósł mi beczkę jako prezent od Narwali.";
			link.l1 = "Kapper nie żyje. Zlikwidowałem go i jego przyjaciół Narwali. Teraz został tylko jeden drań - Cyklop Marcello... Jestem pewien, że ta tłusta świnia wie, gdzie się znajduje. Pozwól mi go trochę nacisnąć!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Pewnie. Tylko postaraj się go nie zabić, nasz biedny Fazio jest w dość kiepskim stanie zdrowia.";
			link.l1 = "Będę delikatny... bardzo delikatny, do diabła!";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", przyjacielu, coś jest bardzo nie tak ze mną..";
			link.l1 = "Steven! Czy ty wypiłeś whisky? Cholera, naprawdę ją wypiłeś?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Tak... To najlepsza irlandzka whiskey... Giuseppe Fazio przyniósł mi ją dzisiaj. Powiedział, że to prezent od przywódcy Narwali... znak pokoju... och, to boli... Wygląda na to, że to mój koniec.";
			link.l1 = "Do diabła! Whiskey było zatrute arsenem! Chad Kapper i Marcello Cyklop to zrobili!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Argh... bosman w końcu mnie dorwał... cholera!";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "Nie umrzesz! Słyszysz mnie? Nie umrzesz! Szybko, weź tę flaszkę. To najpotężniejszy eliksir leczniczy na świecie, leczy wszystko. Wypij to... teraz!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Stevena!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", naprawdę pomogło. Nadal czuję się trochę chory, ale ból prawie zniknął...";
			link.l1 = "Ten eliksir neutralizuje nawet najbardziej śmiercionośne trucizny. Wypij to wszystko! Tak...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "Cud... Teraz jest mi dobrze. Dzięki, przyjacielu, nigdy tego nie zapomnę...";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "Lepiej teraz odpocznij. Wyglądasz jak trup. Ten sukinsyn Kapper nie będzie już w stanie nam grozić - załatwiłem go, a także kilku Narwali. Został tylko Marcello Cyklop. Powiedziałeś, że Fazio przyniósł ci whisky, prawda?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "Lepiej teraz odpocznij. Wyglądasz jak martwy człowiek. Powiedziałeś, że Fazio przyniósł ci whisky, prawda?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Tak. Naprawdę powinienem był zwrócić uwagę na jego bladą twarz i drżące ręce...";
			link.l1 = "Wydaje się, że został do tego zmuszony. Dobrze, odwiedzę tę tłustą świnię i zdobędę od niego informacje. Jestem pewien, że wie, czego potrzebuję. Zdrowiej!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Tak. Naprawdę musiałem zwrócić uwagę na jego bladą twarz i drżące ręce...";
			link.l1 = "Wydaje się, że został do tego zmuszony. Dobrze, w końcu dorwę tę tłustą świnię, ale teraz muszę zająć się Kapperem i Cyklopem. Wiem, gdzie się ukrywają. Zdrowiej!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Co powiesz, "+pchar.name+"? Już wiem, że rozprawiłeś się z Kapperem na 'Evie'. I nawet tam nie posprzątałeś, ha-ha! Szczerze mówiąc, jestem pełen podziwu! Zabić Chada i jego ludzi, to coś! Tak, Jan miał rację, chwaląc cię.";
			link.l1 = "Nie tylko rozprawiłem się z Kapperem, ale także zapobiegłem zamachowi na twoje życie. Miałeś zostać otruty, Steven, ale powstrzymałem tych drani przed tym.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Aby mnie otruć? Ale jak?";
			link.l1 = "Chad kupił beczkę irlandzkiej whiskey Bushmills od Axela...";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills? To mój ulubiony! Nie piłem go od wieków!";
			link.l1 = "Tak-tak. I Kapper o tym wie. Poprosił też swojego kumpla, Marcello Cyklopa, by kupił trochę arszeniku od Sancho Carpentero. Potem on i jego kumple zabrali Fazia i zeszli do ładowni 'Evy'. Zamierzał zatruć whiskey i zmusić Fazia, aby przyniósł ci je jako prezent od Narwali.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Ha! Oczywiście, wypiłbym kufel whiskey natychmiast...";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad na to liczył. Ale zawiódł - nawet nie zdążył wsypać do niego arszeniku. Tak, a ja wziąłem beczkę ze sobą. Możesz ją mieć w prezencie.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad na to liczył. Ale mu się nie udało - nawet nie miał czasu wrzucić do niego arszeniku.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Pokaż mi... "+pchar.name+", to prawdziwy Bushmills! Najlepsza irlandzka whiskey! Argh, marzyłem o tym przez lata! Ty, ty... Cholera! Wyeliminowałeś Chada i znalazłeś tak wspaniałą whiskey!\nDam ci jeden z moich najlepszych talizmanów. To jest Młot Thora, jest niezniszczalny. Twój artylerzysta go pokocha!";
			link.l1 = "Dzięki! Ja też się bardzo cieszę.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "Nie mogę się doczekać, aż wypiję pintę tego wspaniałego whiskey... "+pchar.name+" ,   zrobimy   dziś   wieczorem   przyjęcie!   A   ty   przyjdź   do   mnie   jutro.   W   międzyczasie   pomyślę   o   twoich   słowach   i   działaniach   Chada...";
			link.l1 = "Dobrze, Steven, nie będę ci przeszkadzać w... relaksowaniu się, ha-ha!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "Powiedziałeś mi coś bardzo ważnego. Zastanowię się nad twoimi słowami i działaniami Chada... a potem cię zawołam.";
			link.l1 = "Dobrze, Steven. Będę czekał!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, oto jesteś, "+pchar.name+"  Teraz wszyscy są tutaj i możemy zacząć. Wezwałem was i Laytona, aby omówić sytuację i zdecydować, co zrobić z Narwalami.";
			link.l1 = "Co masz na myśli - co zrobić z Narwalami?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "Chad zorganizował zamach na moje życie, mając bezpośrednie wsparcie Narwali. Rozpoznaję to jako otwarty akt agresji. Biorąc pod uwagę fakt, że mamy krótkoterminowy sojusz z Rivados, oferuję następujące\nTworzymy sojusz z Rivados, przygotowujemy operację i raz na zawsze likwidujemy klan Narwali. Mam dość ich bandyckiego nastawienia. Ty, "+pchar.name+", będziesz musiał znów zagrać rolę dyplomaty\nPorozmawiaj z Czarnym Eddiem i Chimisetem, przekonaj ich, by dołączyli do nas w walce przeciwko naszemu wspólnemu wrogowi. Myślę, że cię wysłuchają, uważają cię za swojego sojusznika\nDexter opracuje plan ataku, zna wszystkie szczegóły geograficzne Wyspy. Layton, czy masz już jakieś przemyślenia?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "Mądry pomysł. Zmuszeni do wycofania się na San Gabriel, Narwale być może nie ustąpią naszym wojskom zbyt szybko - ale umrą prędko bez dostaw zaopatrzenia albo będą zmuszeni do desperackiego ataku. Co ty na to, "+pchar.name+"?";
			link.l1 = "Co mam powiedzieć... Powiem, że wypowiedzenie wojny Narwalom to politycznie błędny krok.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "  A mówisz to po tym, jak zabiłeś wszystkich ludzi Chada? Nie zapominaj, że wszyscy oni byli Narwalami!";
			link.l1 = "Nie wszyscy z nich. Jeden z pierwszych tych łotrów, Marcello Cyklop, nie był Narwalem. W rzeczywistości był lojalny Rivados i być może planował do nich dołączyć. W końcu jest mulatem. Myślę, że Narwale nie odpowiadają za próbę zamachu na twoje życie - tylko kilku łotrów, którzy zostali zwerbowani przez Kappera.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "A co sugerujesz? Zignorować to wszystko?";
			link.l1 = "Sugeruję, abyś pozostawił mnie w mojej roli dyplomaty - ale tym razem będę negocjował z przywódcą Narwali, Donaldem. Poza tym, pozwól, że przedstawię ci mój punkt widzenia na temat możliwego wyniku ataku na Narwali.";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "Kontynuuj.";
			link.l1 = "Tak jak widzę, pokój na Wyspie jest możliwy tylko dzięki rywalizacji między dwoma klanami, które są niemal równe w swoich siłach. Twoi wojownicy są trzecią siłą i mogą pomóc któremukolwiek z nich osiągnąć zwycięstwo. Ale zarówno Rivados, jak i Narwale są silni i zwycięstwo będzie kosztować zwycięzcę zbyt wiele w każdym przypadku.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "Cena za zniszczenie Narwali będzie wiele żyć twoich ludzi i ludzi Rivados. Poza tym, Layton powiedział, że oblężenie San Gabriel potrwa długo, a także możemy się zmierzyć z możliwą agresją ze strony Rivados, jeśli stracimy zbyt wielu ludzi...";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = " ";
			link.l1 = "Nie zapominaj, że oba klany pragną dominować na Wyspie i niedawno byli twoimi wrogami. Więc, moim zdaniem, rzeź byłaby prawdziwą plagą dla zwykłych mieszkańców.";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "Hm. Twoje słowa brzmią mądrze, ale jeszcze mnie nie przekonałeś.";
			link.l1 = "Muszę również jakoś opuścić Wyspę, więc muszę dotrzeć do posągu Kukulkana na dnie morza. Rivados nie są w stanie mi pomóc - może Narwale? Walka z nimi też mi nie pomoże.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "Ha! And I guess that there is one more reason why you don't want to make Narwhals our enemies. That red-haired girl of Ceres Smithy, right, friend? Am I right? Don't worry about her, "+pchar.name+", since you care about her this much - we will take her in the safe place before fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" Ale zgadzam się, jeśli jesteś tak zdeterminowany. Idź i zobacz Donalda Greenspana, głowę Narwali. Jego rezydencja znajduje się na tyłach Esmeraldy. Zobaczymy, co nam powie ten łajdak.";
			link.l1 = "Dobrze. Wyruszam w drogę.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Idź do Donalda, kumplu, i spraw, by lizał ci buty, ha-ha! Będę na ciebie czekał.";
			link.l1 = "Jestem w drodze.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "Więc co, rozmawiałeś z Donaldem? Widzę, że tak...";
			link.l1 = "Tak. Nie nakazał swoim ludziom cię skrzywdzić. Wszyscy Narwale, którzy uczestniczyli w próbie, zostali zwerbowani przez Chada Kappera. Jest bardzo zmartwiony i zapewnia nas, że Narwale nie mają złych zamiarów wobec ciebie. Jest gotów osobiście przeprosić cię za tę próbę zamachu na twoje życie i za podejrzenia o zabójstwo Alana.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Czy jest gotów przyjść tutaj i powiedzieć to wszystko?";
			link.l1 = "Przysiągł na Biblię.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, być może, to wystarczy. Wygląda na to, że jedynym draniem do obwinienia jest mój były bosman.";
			link.l1 = "Jestem tego całkowicie pewien, Steven. Nie potrzebujemy tej wojny. Nikt jej nie potrzebuje.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "Dobrze! Umowa stoi. Jestem gotów przyjąć Donalda z jego przeprosinami, ale niech się pospieszy. Idź i mu to powiedz.";
			link.l1 = "Natychmiast, Steven.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Take your Mary there and live your lives together, there is plenty of free space.";
			else sTemp = "";
			dialog.text = "Czekaj! "+pchar.name+", bardzo się cieszę, że zjawiłeś się tutaj, na Wyspie. Jan ma o tobie bardzo wysokie zdanie, ale przewyższyłeś wszelkie oczekiwania. Gdybyś był w mojej załodze... w zasadzie, oferuję ci pozycję Kappera, podczas gdy tu jesteś. Będziesz dowodzić moim garnizonem na 'Tartarze'. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "Nie, Steven, dzięki wielkie, ale nie zamierzam tu zostawać na długo. Znajdź kogoś innego do tego. A co do Mary - radzimy sobie dobrze na 'Kowadle Ceresa'.";
			else link.l1 = "Nie, Steven, dzięki wielkie, ale nie zamierzam tu zostać na długo. Znajdź kogoś innego do tego.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Cokolwiek, przyjacielu. Niech tak będzie. Proszę, przyjmij ode mnie ten prezent. Myślę, że te pięćset dublonów będzie dla ciebie użyteczne.";
			link.l1 = "Dzięki!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Porozmawiajmy o naszych interesach... Weź te wskazówki nawigacyjne. Użyj ich, aby wrócić tutaj na statku i w jednym kawałku\nBez nich albo nie uda ci się znaleźć drogi tutaj z powodu raf i burz wokół Wyspy, więc twój statek prawdopodobnie dołączy tutaj do swoich sióstr. Pamiętaj, że musisz użyć stosunkowo małego statku, aby przejść przez rafy. Lugier, szkuner, brygantyna, bryg... Czwarta klasa, nie większa\nTwoim celem jest opuścić to miejsce z tymi wskazówkami nawigacyjnymi w kieszeni, a potem wrócić po mnie na statku. Gdy wrócę, dołączę do ciebie i Svensona w twojej grze. Nie mam pojęcia, jak możesz opuścić wyspę. Tylko ty możesz sobie pomóc w tej sprawie, a może ten twój Kukulcan...";
			link.l1 = "Zabawne, ale faktycznie liczę na jego pomoc. Dzięki za instrukcje żeglarskie, Steven. Jeszcze znajdę drogę z tej wyspy.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Życzę ci więc powodzenia. Pospiesz się, jeśli możesz, moje magazyny szybko się opróżniają, a wkrótce nie będzie żadnych zapasów. Wiesz, do czego są zdolni głodni i uzbrojeni ludzie, prawda?";
			link.l1 = "Tak, muszę już iść. Do zobaczenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Czy znalazłeś drogę wyjścia z wyspy, "+pchar.name+"?";
			link.l1 = "Jeszcze nie, Steven. Nadal nad tym pracuję.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Cóż, co masz, "+pchar.name+"Masz jakieś ciekawe wieści?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, chciałbym prosić cię o zwrot moich skonfiskowanych rzeczy.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, opowiedz mi więcej o tej wyspie.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Jesteś pewien, że Hawk nie jest na wyspie? Przeszedł przez portal, więc musi tu być.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Czy znasz człowieka o przezwisku Biały Chłopiec?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "Jakie terytoria tutaj należą do Narwali i Rivados?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "Jak mogę poznać hasła, aby dostać się na pokład statków klanowych?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Słuchaj, czy jest jakaś mapa Wyspy?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "Masz tak interesujący pałasz. Nigdy wcześniej czegoś takiego nie widziałem...";
				link.l8.go = "blade";
			}
			link.l9 = "Jeszcze nie mam pytań. Ale wkrótce mogę mieć...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ach, tak, oczywiście! Całkowicie o tym zapomniałem... Twoje rzeczy są na górze w skrzyni. Możesz je zabrać. Layton cię nie powstrzyma.";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "Ta wyspa musi być bardzo stara. Widziałem stare karawelki na zewnętrznym pierścieniu, mają ponad sto lat. Jej istnienie jest możliwe dzięki dużym płytkim wodom i silnemu prądowi, który przynosi tutaj kadłuby statków. Ludzie żyją tu od dawna. Są tacy, którzy urodzili się tutaj i nigdy nie opuścili.\nKlanów utworzono zaraz po tym, jak wyprawa de Betancourta znalazła się tutaj. A tak przy okazji, San Augustine i Tartarus były częścią tej wyprawy. Tartarus miał w swoich ładowniach wielu czarnych niewolników. Założyli klan Rivados na cześć Pedro Rivadosa, ich przywódcy. Rozpoczął powstanie i próbował przejąć Tartarus, ale nie udało się. Mężczyzna został skazany na powolną śmierć.\nNiewolnicy zdobyli tu wolność i natychmiast sprzeciwili się reszcie mieszkańców. Ich żądanie dominacji i afrykańskie tradycje sprawiły, że większość chrześcijan zjednoczyła się, tworząc klan Narwali.\nKlan Narwali miał w swoich szeregach wielu najemników, żołnierzy, oficerów i poszukiwaczy przygód, gromadzili zapasy i budowali małą, profesjonalną armię gotową do walki z Rivados z przewagą liczebną. Od tego czasu Narwale stały się bardzo selektywne w przyjmowaniu nowych rekrutów, a Rivados ograniczyli swoje ambicje. Możesz teraz zobaczyć rezultaty.";
			link.l1 = "Czy były jakieś powiązania między Wyspą a światem zewnętrznym?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "Nie było żadnych połączeń przez ostatnie dziesięć lat. Miejscowi handlowali kiedyś z Kubą, wymieniając złoto i cenne towary na żywność. Ale już tego nie robią.";
			link.l1 = "Hm.  Więc wydaje się, że Svenson i Czarny Pastor obaj mieli rację... A dlaczego ludzie nie opuścili Wyspy, gdy jeszcze mieli taką okazję?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Niektórzy to zrobili, ale większość zdecydowała się zostać. Wielu znalazło tu dom, wielu innych tu się urodziło. Nie chcą wracać. To miejsce wydaje się dla nich znacznie lepsze... Niektórzy boją się podróżować przez strefę burz na starych łajbach. Co do Rivados - nie mają wyboru i muszą tu zostać.";
			link.l1 = " I dlaczego tu przybyłeś? Porzuciłeś swój doskonały fregat, wybierając zamiast tego bryg...";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "Obwiniono mnie o morderstwo Blaze'a Sharpa. Nie mam pojęcia dlaczego. Oczywiście ktoś gra nieczysto. Liczba moich wrogów zaczęła gwałtownie rosnąć, więc musiałem opuścić Isla Tesoro i przeczekać na Wyspie Sprawiedliwości. Wiedziałem o tym miejscu od dawna. Zostawiłem mój fregat, bo była za duża, by ominąć lokalne rafy.\nZaatakowali mnie Narwale i Riwados, jak tylko tutaj dotarłem. Nie docenili mojego przybycia. Podpłynęli do mojego statku nocą na szalupach i podpalili ją. Rozgromiliśmy ich łajby naszymi armatami i muszkietami. Ale ogień zrobił swoje - mój bryg spłonął.\nWściekliśmy się jak diabli, najechaliśmy Wyspę, szturmowaliśmy San Augustine i pokazaliśmy im, jak walczą korsarze. Nie mogli znieść naszego nacisku i wkrótce pokazali swoje plecy jak tchórze. Zdobyliśmy San Augustine, okazało się, że ci idioci używali go jako magazynu zaopatrzenia. Teraz muszą kupować ode mnie po cenie, którą ustalę.\nPojmaliśmy także lokalnych przywódców: głowę Narwali, Alana Milrowa i duchowego przywódcę Riwados, Chimiseta. Layton spędził kilka następnych dni, aby zbadać teren, a my zaatakowaliśmy Tartarus - słaby punkt w ich obronie.\nTeraz mamy dwa z tych statków i klany muszą przyzwyczaić się do naszej obecności. Obecnie mamy tu coś na kształt pokoju. Jeśli chodzi o innych mieszkańców, zdają się lubić pomysł trzeciej siły.";
			link.l1 = "Teraz rozumiem. Dzięki za opowieść!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "Nie mogę powiedzieć na pewno, ale nie widziałem go tutaj. Ani na ulicach, ani w tawernie, ani na statkach klanowych. Jesteś pierwszym, kto mi powiedział, że Hawk powinien być gdzieś w pobliżu. Ale jak już mówiłem - wątpię w to.";
			link.l1 = "Widzę...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "Białas? Hm... Nie, wcześniej o nim nie słyszałem. Ale to nie znaczy, że go tu nie ma. Nie muszę znać całej miejscowej hołoty, zgadzasz się?";
			link.l1 = "Ja wiem. Dobrze, zapytam kogoś innego.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "Wyspa jest podzielona pomiędzy Narwale, Rivados i moich ludzi. Jest także strefa neutralna. Kontroluję San Augustin i Tartarus\nRivados mają Protektor, który jest ich rezydencją, Fury - koszary, Velasco - magazyn. Obcym zakazuje się wstępu, musisz podać specjalne hasło, aby się tam dostać\nNarwale mają wiele statków w swoim posiadaniu. Esmeralda jest rezydencją ich przywódcy i sklepem. Tak zwane 'Centrum naukowe San Gabriel' i platforma Feniks. Ostatnie, ale nie mniej ważne, Ceres Smithy - ich warsztat. Każdy statek oprócz Esmeraldy jest strefą zastrzeżoną, musisz podać hasło, zanim cię wpuszczą\nReszta statków jest uznawana za neutralną, miejscowi mieszkańcy żyją w ich wnętrzach. Tawerna Sancho znajduje się na karaweli Fleron, a brat Julian jest głową lokalnego kościoła na galeonie Gloria.";
			link.l1 = "Dzięki za informacje!";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "Właściwie to dają je osobom, które ich same interesują. Niestety, nie jesteś jedną z nich. Ale to nie jest problem. Idź na stary fregat o nazwie Carolinea. Tam mieszka gruby, przebiegły pies Giuseppe Fazio. Jest tu pewnego rodzaju dyplomatą. Nie wiem, co robił, zanim tu trafił, ale człowiek ma talent.\nRobi interesy z każdym. Klany używają go jako mediatora. Chciwy. Gotów zjeść samego siebie za jednego dubloona, ale nigdy tego nie okazuje. Zapytaj go o aktualne hasło, choć to będzie cię kosztować.";
			link.l1 = "Dzięki! Zapamiętam to.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter ma jeden. On jest moim drugim w dowodzeniu. Sporządził szczegółową mapę zaraz po naszym przybyciu. Idź na górę i porozmawiaj z nim, jeśli jej potrzebujesz.";
			link.l1 = "Zrozumiałem. Dzięki!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha! Zacna szabla. Unikalne ostrze jakiegoś rodzaju... Trofeum od Alana Milrowa, przywódcy klanu Narwali. Tak je nazwałem. Jurgen, rusznikarz Narwali, wykonał je z niezwykłego metalu, który znaleźli na dnie morza\nNie rdzewieje, nigdy się nie tępi i tnie wszystko i wszystkich naraz. Jestem bardzo zadowolony z tej broni i nie zamierzam jej zostawiać.";
			link.l1 = "Jestem ciekaw, czy Jurgen potrafi zrobić jeszcze jeden taki kordelas? Za dobre pieniądze, oczywiście...";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Cóż, na pewno może zrobić kolejny. Ale nie zrobi tego. Jurgen to Narwal, jest lojalny swojemu klanowi i nigdy nie zrobi niczego dla obcych. Poza tym, będziesz potrzebować bardzo specjalnego żelaza, by wykonać drugi miecz. To żelazo można znaleźć tylko na dnie - a jak ktokolwiek miałby się tam dostać? Więc zapomnij o tym.";
			link.l1 = "Rozumiem. Szkoda.";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Ha, widziałem twoje żagle na horyzoncie, "+pchar.name+" Cieszę się, że cię widzę, przyjacielu! Jak minęła podróż?";
			link.l1 = "Było w porządku.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Dobrze. Cóż, jestem gotowy wsiąść na twój statek i popłynąć do Jana Svensona. Layton zostanie tutaj jako admirał, już zajął miejsce, ha-ha! Wygląda na to, że nie zamierza opuszczać Wyspy, podoba mu się to miejsce.";
			link.l1 = "Powiedziałeś kiedyś, że radzi sobie naprawdę dobrze.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Tak, z pewnością jest. Cóż, jestem gotów. Ruszamy?";
			link.l1 = "Wsiadaj na mój statek, Steven. Odpłyniemy, jak tylko skończę tutaj swoje sprawy.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Umowa stoi! Eh, zbyt długo nie czułem pokładu porządnego statku pod stopami!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Tu jesteśmy, przyjacielu. Cóż, pójdę zobaczyć się ze Svensonem. Ty też powinieneś go odwiedzić i omówić nasze przyszłe plany. Ha-ha! Czekają nas gorące dni, co?";
			link.l1 = "Bez wątpienia. Do zobaczenia, Steven!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Oczywiście, zrobię, co będę mógł! Mów dalej.";
			link.l1 = "Steve, spójrz... Ząb rekina. Nie mów mi, że jest ci nieznany!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Jesteś bystry! Tak, to mój ząb. Cóż, to ząb rekina, którego zabiłem, by zaimponować jednej piękności. Od tamtej pory nazywają mnie Rekinem. Tylko nieliczni potrafili to zrobić pod wodą przy pomocy zwykłej szabli, ale byłem młody i głupi, a Beatrice Sharp była najpiękniejszą dziewczyną na Karaibach... Jak go zdobyłeś?";
			link.l1 = "Były kat z St. John's dał mi to. Człowiek został nim zarżnięty. Nazywał się... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Tak, zrobiłem to. Przeciąłem mu gardło tym zębem. Byłem przerażony śmiercią Beatrice i uwierzyłem, że Leadbeater jest jedynym odpowiedzialnym, który pozostał przy życiu. Przeczytałem papiery, które znalazłem później przy nim. Cóż, miał pełne prawo do zemsty\nSiostra Blaze'a była po prostu w złym miejscu i w złym czasie. Mask nie jest winny jej śmierci, nie chciał tego, tylko Rzeźnik był jego celem. Żałuję, że go zabiłem. Prawda jest taka, że to suka Jessica wszystko ustawiła.";
			link.l1 = "Czy uratowałeś te dokumenty?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Po co miałbym? Oczywiście, że nie. Nie potrzebowałem ich. Ale mogę ci powiedzieć, dlaczego Mask ścigał Rzeźnika, jeśli masz czas.";
			link.l1 = "Posiadam. Wiedz, że to nie jest zwykła ciekawość, naprawdę jestem zainteresowany. Jestem nawet gotów spisać twoją historię.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Wiem, nigdy nie marnujesz czasu. Posłuchaj więc. Joshua Leadbeater był zwykłym kapitanem brytyjskiej marynarki i dowodził fregatą 'Neptune', która później stała się legendą...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... Jednakże Leadbeater przeżył i został uratowany przez przepływający statek. Jego rany oszpeciły mu twarz i od tamtej pory nosił maskę. Odnalezienie i ukaranie winowajcy wszystkich jego nieszczęść stało się sensem jego życia.";
			link.l1 = "Widzę... Mam to zapisane. Myślę, że powinienem to przeczytać, żeby zobaczyć, co zdobyłem. To bardzo smutna historia. Widziałeś tę Jessicę?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Tak! Towarzyszyła Rzeźnikowi we wszystkich jego podróżach, dopóki nie porzucił jej dla Beatrice. Jess nie mogła mu tego wybaczyć. Nazywali ją talizmanem Rzeźnika, bo zawsze miał szczęście, gdy ona była z nim\nWierz lub nie, ale gdy tylko pozbył się jej na Barbadosie, jego interesy zaczęły się psuć, łupy były marne, a 'Neptune' stał się częstym gościem w stoczni na Isla Tesoro. Choć można to wyjaśnić faktem, że Rzeźnik spędzał większość czasu z Beatrice w kabinie, a nie na pokładzie\nBeatrice nie była jak Jessica, nie była uzależniona od przygód i wojny, choć Nicolas nauczył ją szermierki i żeglarstwa. Tak, lubiła morską romantykę, ale brakowało jej twardości charakteru. 'Neptune' Rzeźnika nie był dla niej odpowiednim miejscem. W końcu, zabiła ją.";
			link.l1 = "A co z Jessicą?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Ona była kimś wyjątkowym. Każdy marynarz na 'Neptunie' słuchał jej rozkazów i nie tylko dlatego, że była dziewczyną kapitana. Jess opanowała sztukę fechtunku i nawigacji, wysiłki Rzeźnika nie poszły na marne. Była twarda i lekkomyślna, a także obdarzona urodą.\nWielu mężczyzn pragnęło z nią się przespać, ale ona chciała tylko Rzeźnika. Przeszkadzanie jej było naprawdę ryzykowne - wielu dosłownie przetestowało to na własnych plecach, a dla najbardziej upartych jej lekcje fechtunku okazały się ostatnimi w ich życiu.\nJess posiadała bardzo wyjątkowy miecz, jedyny w swoim rodzaju na Karaibach, nie mam pojęcia, skąd go miała. Miecz o płomienistej klindze. Nikt nie może go chwycić, a nawet najmniejszy dotyk pozostawia straszliwą ranę.\nJess była poszukiwaczką przygód nie z urodzenia, ale z powołania. Tak przy okazji, jeśli chcesz dowiedzieć się o niej więcej, możesz porozmawiać ze znajomym. On może opowiedzieć ci o niej znacznie więcej niż ja.";
			link.l1 = "Naprawdę? I kim jest ten człowiek?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Diabeł Lasu nigdy by się do tego nie przyznał, ale miał plany wobec Jessiki. To był czas, kiedy już przejął Zachodnią Główną i jego sława była czymś, czego można było zazdrościć, więc tygrysica była tak dobra jak on\nPo tym, jak Rzeźnik pozbył się Jess, Jan zaczął podejrzanie często odwiedzać Barbados, co wstrząsnęło angielskim garnizonem. Jak wiadomo, Jessica była córką plantatora z Bridgetown\nW końcu jego plany były dobrze znane w prywatnych kręgach, a jednak nikt nie odważył się wyrazić swojej opinii na ten temat, Jan może teraz siedzieć na tyłku w Blueweld, ale w tamtych czasach każde niewłaściwe słowo pod jego adresem mogło skończyć się źle\nW końcu nic im z tego nie wyszło. Jess nie mogła żyć z tym, jak traktował ją Rzeźnik i zemściła się rok później z pomocą Maski. Ta zemsta skończyła się tragicznie dla wszystkich: dla Rzeźnika, dla Beatrice, dla Maski i dla niej samej. Wszyscy zginęli.";
			link.l1 = "Nie wszyscy. Rzeźnik wciąż żyje.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Co? Czy się przesłyszałem? On żyje?!";
			link.l1 = "Tak. Kapitan Butcher nie został stracony. Cóż, powinien był, ale przeżył dzięki Jacobowi Jackmanowi i Henry'emu Wisielcowi, którzy zastraszyli kata. Egzekucja była fałszywa. Mam dowody.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Niemożliwe! A gdzie on teraz jest?";
			link.l1 = "Jest znany jako Lawrence Beltrope i mieszka w Port Royal. Jednak wciąż jest niebezpieczny. Jackman, który sprawił tyle problemów Bractwu Wybrzeża, działał pod jego rozkazami.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Do diabła! Kwatermistrz odnalazł swojego kapitana po tak długim czasie! Beltrope, mówisz... czekaj! Teraz rozumiem, dlaczego w papierach Blaze'a był dziwny zapis z przesłuchania... Wygląda na to, że Blaze również dowiedział się o Rzeźniku-Beltrope...";
			link.l1 = "O czym ty mówisz?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Po objęciu tej rezydencji, przeszukałem papiery starego Blaze'a. Znalazłem protokół przesłuchania pewnego Samuela Brooksa. Było tam wiele o przygodach Thomasa Beltrope'a i że jest znany jako pirat oraz bliski przyjaciel Nicolasa Sharpa. Wygląda na to, że był ojcem Rzeźnika.";
			link.l1 = "Interesujące. Wygląda na to, że dzieci Sharpa i Beltrope'a kontynuują pracę swoich rodziców...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Wydaje się, że tak... Ale powiedz mi, przyjacielu, dlaczego tak interesują cię czyny zmarłych? Co cię to obchodzi?";
			link.l1 = "Potrzebuję dokumentów, które potwierdzą, że Helen McArthur jest córką Beatrice Sharp i że ma wszelkie prawa do tego nazwiska. Nie obchodzi mnie, że jest również Beltrope.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Nie ma żadnej wzmianki o Helen McArthur ani w dokumentach Leadbeatera, ani w archiwach Blaze'a. To dziwne, że Beatrice nie powiedziała Blaze'owi o narodzinach jego siostrzenicy. To do niej niepodobne.";
			link.l1 = "Słuchaj, może jest coś jeszcze w papierach Sharpa? Potrzebuję każdego szczegółu!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, zgaduję. Według notatek Blaze'a, próbował znaleźć wyspę, na której zginęła jego siostra. Są tu dokumenty dotyczące ekspedycji karnej Leadbeatera. Nic ciekawego, poza kilkoma liczbami szerokości geograficznej\nTa równoleżnik przecina Morze Karaibskie w jego północnej części. Ale nie ma żadnego śladu długości geograficznej. Oczywiście, poszukiwania Blaze'a zakończyły się niepowodzeniem, nie możesz sobie nawet wyobrazić, ile małych wysp jest na tej szerokości geograficznej.";
			link.l1 = "A co to jest?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Zobaczmy... tutaj: szerokość 21 stopni 32' Północ. Nie wiem, jak to może ci pomóc.";
			link.l1 = "Tak będzie. Dobrze, Steven, bardzo dziękuję za twoją szczerą opowieść. Do zobaczenia!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Można tak powiedzieć. A teraz, o Tortudze\nWyspę nazwano tak, ponieważ wygląda prawie jak żółw. Levasseur przez dwanaście lat wzmacniał pancerz tego żółwia - fort La Roche. Atak frontalny to samobójstwo, ciężkie działa fortu nie zostawią żadnej szansy. Więc gotowanie zupy z tego piękna nie będzie łatwe. Hiszpanie próbowali przez bardzo długi czas i nigdy im się nie udało.";
			link.l1 = "To dlatego poszedłem do Svensona. Więc jaki jest twój plan? Dalej, Steven!";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Moi ludzie wykonali niezłą robotę na Tortudze przez ostatnie kilka tygodni, i zdobyli mnóstwo interesujących informacji. Mam więc dla ciebie dobre wieści, kumplu! Wygląda na to, że nie musisz się mierzyć z działami La Roche, ponieważ nie tylko my mamy dość Levasseura. Wśród jego przyjaciół są tacy, którzy również chcą jego śmierci.";
			link.l1 = "Kontynuuj...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Wiemy, że Levasseur ma słabość do młodych kolonialnych dziewcząt. Znikają, gdy skończy się nimi bawić. Główny dostawca niewolników na Tortudze nazywa się Robert Marten z galeonu Voltigeur\nJego wspólnik, siostrzeniec Levasseura, Henri Thibaut wybiera najładniejsze białe dziewczęta prosto w porcie dla swojego patrona. Niedawno Marten dostał w swoje ręce bardzo piękną dziewczynę z angielskiego brygu. Nazywa się Molly Jones. Dostarczył ją nie Levasseur, lecz swojemu siostrzeńcowi, w nocy do jakiejś tajnej groty na Tortudze\nZałodze powiedziano, że dziewczyna zmarła na zawał serca, a jej 'ciało' zostało wyrzucone za burtę. Wygląda na to, że nasi kumple postanowili zachować sobie tę piękność. Jeśli Levasseur dowie się o Molly, ci dwaj będą mieli kłopoty.";
			link.l1 = "A jak możemy zaufać tym informacjom? Oczywiste jest, że obaj rozumieją, iż igrają z ogniem...";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "Prawda. Ale każdy łańcuch ma słaby punkt. I znalazłem taki dla ciebie. Trzy dni temu były marynarz 'Voltigeur' imieniem Fernand Lucas wypił za dużo i opowiedział wiele ciekawych rzeczy w tawernie w Basse-Terre\nOkazało się, że Molly Jones poprosiła go, by poprosił jej brata w St John's o pomoc. Ale Lucas nigdy nie dotarł do celu, uciekł od swojego kapitana i siedzi na tyłku w Gwadelupie, topiąc swoją tchórzliwość w rumie\nAntigua nie jest bezpiecznym miejscem dla francuskich piratów. Pamiętaj o tym! Pułkownik Fox jest gotów powiesić ich na każdej palmie wyspy po tym, jak jego żona zginęła z ręki francuskiego korsarza. A jego straszliwi marines zrobią wszystko, co im każe ich dowódca.";
			link.l1 = "Jeszcze nie rozumiem, jak to jest związane z naszym interesem... Porozmawiajmy o naszych ludziach, Martenie i Thibaucie. Jaki jest sens takiego ryzyka? Czy urok tej kobiety był tak silny, czy ci handlarze niewolników okazali łaskę?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Znam tego łajdaka Martena bardzo dobrze. Jeśli podejmuje ryzyko, to znaczy, że w grę wchodzi albo złoto, albo strach o własną skórę. Nie wiem, co nasz więzień ma z tym wspólnego\nMoże Robert spodziewa się dostać za nią ogromny okup, co jest mało prawdopodobne, dziewczyna wyglądała jak służąca. A może... Ha! Zastanawiam się, kto mógłby bardziej przerażać Martena niż Levasseur!";
			link.l1 = "A dlaczego sądzisz, że panna Jones wciąż jest ukrywana przed gubernatorem? Może dostali od niej to, czego chcieli, i przekazali ją Levasseur? Tak, masz coś konkretnego do powiedzenia o tym Thibaut?";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Nie wiem wiele o tym człowieku. Wiem tylko, że wuj ufa temu szczeniakowi na tyle, by uczynić go swoim dziedzicem. Nadal ma dziewczynę, inaczej po co by im były te wszystkie intrygi?\nNie wiadomo, gdzie przetrzymują dziewczynę i dlaczego Thibaut pozwala Martenowi przejąć dowództwo. Jest tu jakaś tajemnica, która może pomóc nam wygrać tę rozgrywkę bez szturmu na Tortugę. Jesteś Francuzem, więc myślę, że wolałbyś w ten sposób\nAle musisz się pospieszyć, pijackie gadki Lucasa mogą zostać usłyszane przez agentów Martena i Levasseura, możesz sobie wyobrazić konsekwencje!";
			link.l1 = "Rozumiem. Czyli Thibaut jest spadkobiercą Levasseura? I ukrywa niewolnicę przed swoim wujem? Cholera, wygląda na to, że młodzieniec pragnie śmierci wuja jak najszybciej!";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Prawda. Według słów Lucasa, ta Molly to rzadki okaz piękna, nasz dzielny Thibaut może się w niej zakochać. Wiesz, co ludzie potrafią zrobić w imię miłości. Idź do Basse-Terre\nZnajdź tego pijackiego idiotę i zmusz go do mówienia. Dodatkowo, powinieneś również dowiedzieć się czegokolwiek o Molly i jej bracie. Może najpierw chcesz odwiedzić Antiguę, Molly wysłała tam Lucasa w jakimś celu. Ale jaki to cel?";
			link.l1 = "Rozumiem. Nie traćmy czasu. Dziękuję, Steven.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Idź dalej!";
			link.l1 = "Znalazłem brata Molly w St. John's. To ordynans Foxa. Ale jest coś dziwnego. Jego siostra Molly to znana brzydka wiedźma, mniej więcej tak wysoka jak ty. Jest pokojówką córki Foxa, Catherine, i była z nią w Anglii do niedawna...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "Jeśli chodzi o Katarzynę, to rzeczywiście jest znana ze swojej urody i miała zamiar odwiedzić ojca w dniu jego urodzin, ale była spóźniona z powodu opóźnienia eskadry w Londynie...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "Jej ojciec, który ciężko przeżył śmierć żony z powodu ataku francuskiego korsarza, surowo zabronił jej opuszczać Anglię na samotnym statku. Więc Molly Jones nie może być więźniem Thibauta. Kim więc ona jest?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Do diabła, jeśli wiem. Może to jakaś inna Molly Jones, a nie ta, o którą pytałeś. Chociaż... za dużo zbiegów okoliczności. Nie wierzę, że to wszystko jest tylko przypadek! Mam jakieś niejasne podejrzenia, ale... wiele dziwnych rzeczy może się zdarzyć!";
			link.l1 = "Co masz na myśli? Powiedz mi!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "A co jeśli córka nie posłuchała rozkazów ojca i wypłynęła bez eskorty? W zeszłym miesiącu było dość burzliwie, Albatros mógł zostać uszkodzony i stać się łatwym łupem dla Martena. Podejrzewam, że Katarzyna nie podała swojego prawdziwego imienia, powinieneś zrozumieć dlaczego, i jest przetrzymywana na Tortudze pod imieniem Molly. \nWiesz, co ją czeka, jeśli jej prawdziwe imię zostanie ujawnione. Zaczyna to mieć sens!";
			link.l1 = "Cholera! Nigdy bym o tym nie pomyślał! Molly... Catherine... Ale to wszystko się zgadza!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "To właśnie mam na myśli, kumplu. Nie jestem pewien, czy mamy rację, ale...";
			link.l1 = "Ale to zmienia wszystko! Może powinniśmy poprosić Anglików o wsparcie? Niech bagnety marines torują nam drogę!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Spokojnie, "+pchar.name+"! Potrzebujemy bardziej solidnych dowodów. Nie możemy być pewni. Prawdziwa Katarzyna może być w Londynie, czekając na wypłynięcie eskadry. Brytyjczycy mają swoje własne problemy, nie zaryzykują ataku na La Roche. Ale jeśli nasze podejrzenia są prawdziwe i pułkownik Fox dowie się, co stało się z jego córką...\n Ustawi blokadę wokół wyspy i będzie czekał na przybycie eskadry. Potem zaatakuje miasto. Morskie lisy to przerażająca siła w walce wręcz. Jestem pewien, że wzniesie angielską flagę nad ruinami Tortugi w ciągu trzech dni. Czy naprawdę tego chcesz?";
			link.l1 = "Nie, to nie jest nasz sposób. Teraz widzę, o jakim okupie mówi Marten.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "Musimy działać ostrożnie. Nawet nie jesteśmy pewni, czy Marten zdaje sobie sprawę z prawdziwej tożsamości Molly. Szantażowanie pułkownika Foxa byłoby samobójczym pomysłem. Zwłaszcza gdy eskadra Cromwella wkrótce przybędzie\nJeśli Catherine umrze, my również stracimy. Nasze Bractwo nie jest zainteresowane, aby bardziej rozzłościć pułkownika Foxa niż zwykle. Ten człowiek może sprawić wiele kłopotów. Jeśli Catherine ma w końcu umrzeć, musimy upewnić się, że nie umrze z naszych rąk i dopiero po odegraniu swojej roli w naszej grze\nAle byłoby o wiele lepiej oddać biedną dziewczynę jej ojcu. Jej wybawca zostanie nagrodzony. Jeśli nie na tym świecie, to na innym.";
			link.l1 = "Na Boga... Steven, jesteś geniuszem! Natychmiast udaję się na Tortugę! Dowiem się, kim jest ta Molly Jones! Jestem przeklęcie pewien, że to Catie Fox!";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Być może... Nie trać czasu, "+pchar.name+"  A jeśli miałem rację - upewnij się, że pozostanie przy życiu.";
			link.l1 = "Zrobię, co w mojej mocy. Do zobaczenia!";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho! Wypluj to, przyjacielu! Rozwiążemy każdy problem, na pewno, do diabła!";
			link.l1 = "Przejdę od razu do rzeczy. Czy znasz Miguela Dichoso?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Znam go. Ten hiszpański don sprzedał mi świetny statek - fregatę. Eh, co to był za okręt, wyobraź sobie...";
			link.l1 = "Niech zgadnę, unikalny kadłub, maksymalna prędkość szesnaście węzłów? 'Santa Quiteria'?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Masz rację co do jej kadłuba i prędkości, ale nazwa była inna - 'San Martin'. Zapłaciłem mu ogromną ilość złota, to było wszystko, co miałem. Wszystkie moje oszczędności trafiły prosto do kieszeni tego łotra.";
			link.l1 = "Czy jesteś pewien, że jej imię było San Martin, a nie Santa Quiteria? A kiedy go kupiłeś? I dlaczego nazywasz go łotrem?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Tak wiele pytań! Odpowiem na nie wszystkie w kolejności: jestem pewien, że to był San Martin. Osobiście pomogłem robotnikom Alexusa pozbyć się deski z tym papistowskim imieniem z rufy. Nazwałem ją 'Fortuna' - znacznie bardziej odpowiednie imię dla takiej księżniczki\nKupiłem ją niedługo przed tym, jak Blaze Sharp został zamordowany zimą 1654 roku. Dlaczego nazwałem Miguela w ten sposób? Bo ten skurwysyn zdołał ukraść statek z hiszpańskiej bazy wojskowej w Providence. Zorganizowaliśmy dla nich niezłe widowisko, tuż przed fortem San Juan. Poświęciłem dwie pół-martwe szalupy, aby uczynić bój bardziej wiarygodnym. Spaliliśmy i zatopiliśmy statki, symulując bitwę z fregatą. Gdy zapadła ciemność - poprowadziliśmy San Martin na Wyspę Skarbów... Ja zdobyłem statek, a Dichoso pieniądze. Powiedział swoim przełożonym, że fregata została zatopiona w bitwie z piratami, co potwierdził komendant San Juan.";
			link.l1 = "Więc tak właśnie hiszpańscy donowie napełniają swe kieszenie! Co za łotr! Powiedz mi, czy to naprawdę wydarzyło się zimą 1654 roku? Może na wiosnę? A czy fregata została uszkodzona przez burze?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "W zimie... Do diabła, nie jestem całkowicie pewien - może to było na wiosnę. Naprawdę nie pamiętam. Fregata nie była uszkodzona, była całkiem nowa. Wyglądała na nowo zbudowaną. Kiedy o niej myślę, chce mi się płakać z irytacji...";
			link.l1 = "Dlaczego? Tak, a gdzie teraz twój piękny fregat?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Bo ona odeszła ode mnie. Wrobili mnie, umieścili mój talizman na zwłokach Blaze'a i rozgłosili, że to ja byłem mordercą. Potem usłyszałem, że Marcus Tyrex - nasz strażnik kodeksu - zamierza naznaczyć mnie czarną plamą. Więc postanowiłem uciec z tego bałaganu na jakiś czas na Wyspę Sprawiedliwości, gdzie mnie znalazłeś\nNie mogłem tam dotrzeć na fregacie, więc zastawiłem ją Czarnemu Pastorowi w zamian za brygantynę wypełnioną zapasami, nie miałem dużo pieniędzy po mojej umowie z tym przebiegłym Dichoso. Miałem nadzieję sprzedać zapasy i wrócić na Isla Tesoro za miesiąc lub dwa... Cóż, resztę znasz.";
			link.l1 = "I Czarny Pastor nie czekał na ciebie, więc ją sprzedał";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Dokładnie. Została kupiona przez jednego Anglika, a mówiąc dokładniej, przez jednego Szkota, Williama Patersona. Mógłbym spróbować odzyskać dziewczynę, pewnie, ale ten górale to poważny ptak, kapitan Królewskiej Marynarki, dobry przyjaciel pułkownika Foxa. Poza tym, robił interesy z Jackmanem tak samo jak ty ze Svensonem\nSzkot ma eskadrę... do diabła, nie zobaczę już mojego statku.";
			link.l1 = "Rozumiem. Nie wiesz, gdzie jest teraz ten Dichoso?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Nie mam pojęcia. Nigdy go nie widziałem, odkąd kupiłem moje Szczęście.";
			link.l1 = "„A dlaczego Miguel nie zaproponował kupna komuś innemu? A co z Tyrexem, Barbazonem, Sharpem? Albo Patersonem?”";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Nie mam pojęcia. Patersona wtedy tutaj nie było, o ile pamiętam. Zachariasz, Jacques i Marcus nigdy by się nie zgodzili, a ja... Naprawdę lubiłem tę fregatę!";
			link.l1 = "Rozumiem, że... Nic nie rozumiem. Wszędzie zagadki...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Znowu grzebiesz w przeszłości? Jaką wyspę chcesz tym razem zdobyć? Ha-ha-ha!";
			link.l1 = "Jest jedna wyspa... Choć jeszcze nie mogę znaleźć drogi do niej. Dobrze, Steven, dziękuję za informację! Żegnaj!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Powodzenia, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "I jak zawsze, cieszę się, że mogę ci pomóc. Czego chcesz tym razem, "+pchar.name+"?";
			link.l1 = "Znów chodzi o twojego starego przyjaciela Miguela Dichoso. Wiem, że znowu widziano go na Wyspie Skarbów. Czy możesz mi pomóc go znaleźć?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ho, przyjacielu, nie wiedziałem tego, w rzeczy samej. Nie widziałem go tutaj. Nie widziałem go od czasu, gdy kupiłem od niego 'Fortunę'. A po co ci ten hiszpański don?";
			link.l1 = "Potrzebuję go. Miguel zna drogę do starego indiańskiego miasta. Naprawdę nie mogę się doczekać, aby tam dotrzeć.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Jak zawsze, mój przyjacielu, wplączesz się w kłopoty. Niestety, nie mogę ci pomóc. Radzę przejść się po osadzie i popytać ludzi, może ktoś go widział. Jest tutaj znaną osobą, wiesz.";
			link.l1 = "Hej, Steven, czy możesz przynajmniej powiedzieć mi, jak on wygląda?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Cóż, ma dwadzieścia pięć - dwadzieścia osiem lat, jest mniej więcej tak wysoki jak ty, ma ciemne oczy, bez peruki. Na prawym policzku ma bliznę po szabli.";
			link.l1 = "Hm. Wiesz, jest tu wielu ludzi, którzy pasowaliby do tego opisu.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Nie ma o nim innych wyjątkowych szczegółów. Jest pewny siebie, bezczelny i bardzo niebezpieczny. Krążyły o nim plotki...";
			link.l1 = "Rozumiem. Dobrze, popytam o niego. Powodzenia, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Trafiłeś we właściwe miejsce! Wyrzuć to z siebie!";
			link.l1 = "Jest taki facet, który nie boi się piratów. Nie traktuje ich poważnie. Trzeba go nauczyć szacunku. Pamiętaj, nie zabijaj go.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! Toż to stary Charles! Założyłbym się, że znów wpakowałeś się w jakieś kłopoty! Przejdźmy do szczegółów, kto tym razem jest celem i czego go nauczymy?";
			link.l1 = "Gość z Europy, inspektor francuskiego Ministerstwa Finansów - baron Noel Forget. Chce założyć tutaj Francuską Kompanię Handlową, ale ja i mój bliski przyjaciel sprzeciwiamy się temu. Próbowaliśmy przekonać barona, że handel tutaj byłby bardzo ryzykowny z powodu Holendrów, Anglików i zwłaszcza piratów po pokonaniu Levasseura, ale nie posłuchał. Musimy wzbudzić w nim strach, aby poczuł to na własnej skórze.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Tak-tak... Prawdziwy baron!.. Czy zaatakujemy jego statek?";
			link.l1 = "Plan jest taki: jego statek wkrótce wypłynie do Capsterville z Port-au-Prince. Musisz przechwycić Barona po jego wypłynięciu i wziąć go jako zakładnika. Byłoby lepiej, gdybyś nie zatopił statku i unikał zabijania załogi. Francuzi w końcu są naszymi przyjaciółmi. Czy dasz radę to zrobić?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "„Cóż, niczego nie mogę obiecać. Ale spróbuję. Jaki to statek?”";
			link.l1 = "Brygantyna zwana 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Bryg nie dorówna mojej fregacie. Łatwo sobie z nimi poradzimy. Jeśli się poddadzą, pozwolę wszystkim żyć.";
			link.l1 = "Znakomicie. Napędź strachu i zaproponuj im poddanie się. Następnie wyślij Barona do zainfekowanego szczurami ładowni. Spróbuj znaleźć najbrudniejsze miejsce, jakie możesz, ale nie trzymaj go tam dłużej niż dzień, bo inaczej może się rozchorować i umrzeć. Potem ulokuj go w kajucie, udaj się na Wyspę Tesoro i zamknij w jakimś ustronnym miejscu. Przyodziej niektórych swoich ludzi w stroje pojmanych francuskich kupców i każ im działać jak oni. Przez trzy dni z rzędu powinni opowiadać mu o tym, jak bezlitośni piraci ich ścigają, rabują, żądają okupu, torturują... ze wszystkimi wymaganymi szczegółami.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! To musi być najzabawniejsza robota, jakiej się podjąłem od bardzo długiego czasu! No cóż, znajdę takich aktorów, kumplu. Nie miej wątpliwości, po ich opowieściach twój baron narobi w spodnie! Pokażą mu blizny od szabel i rozgrzanych wyciorów... ";
			link.l1 = "Załatwione. Potem zmusisz go, by napisał list do Poincy, prosząc o okup. Trzydzieści pięćset tysięcy za taką szychę to nie tak dużo.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Dobrze. Co zrobimy dalej?";
			link.l1 = "A potem przyprowadzisz Barona na Turków. Tam weźmiesz okup, a mnie oddasz Barona. A dodatkowo powinieneś wspomnieć, że wszyscy Francuzi odpowiedzą za Tortugę i Levasseura.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Toż to niezły numer! Osobiście, cóż, wiesz, co zrobiliśmy z Levasseurem, a teraz... ha-ha-ha!.. Dobrze, kumplu. Zrobimy to! Mówisz, że statek wkrótce przypłynie?";
			link.l1 = "Wkrótce. Musimy być czujni.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Nie martw się, nie zawiodę cię. Osobiście się tym zajmę. Gdy usłyszysz plotkę, że ten baron został pojmany, przyjdź do mnie.";
			link.l1 = "Dobrze. Dziękuję ci, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Oczywiście, kumplu. Jak się umawialiśmy. Straszliwe opowieści o złych piratach, mordujących niewinnych francuskich kupców, dźwięki bicza, jęki i krzyki. Kocioł z węglem i przypalone kajdany. Tak jak powinno być.";
			link.l1 = "No cóż! Spokojnie, potrzebuję go żywego.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Nie martw się, on przeżyje. Napisał ten list drżącą ręką. Oto on.";
			link.l1 = "Co tam jest napisane? Czy błaga Poincy'ego, by go stąd wydostał?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Dokładnie, kumplu! On błaga!";
			link.l1 = "Wyrzuć ten list, a jeszcze lepiej – spal go. Spotkamy się na Turkach za tydzień. Musi wyglądać, jakbyśmy potrzebowali czasu na zebranie okupu.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Zrozumiano. Za tydzień, Północna zatoka. Nie zapomnij wziąć pieniędzy: to musi wyglądać pięknie. Potem przyjdź do mnie, załatwimy to.";
			link.l1 = "Oczywiście, założę się, że nawet jeżowiec by to zrozumiał. Do zobaczenia później! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hej, żabożercze! Stój!";
			link.l1 = "Nie ruszam się.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Oto twój baron. Trochę zużyty, ale w jednym kawałku. To on?";
			link.l1 = "Tak.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Doskonale. Teraz oddaj pieniądze, albo z nim koniec! I nie próbuj nas oszukać, mamy cię na muszce!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Oto.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Cholera! Zapomniałem tego na statku...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Jesteś sprytnym dzieciakiem, francuziku. Weź swą świętość. I powiedz Poincy, że powinien przygotować pieniądze: wszyscy francuscy dranie będą musieli zapłacić za to, co zrobiliście Levasseurowi i Tortudze. A wasi kupcy zapłacą nam swoimi towarami i statkami. Ha-ha-ha! Nie zapomnij przyprowadzić nam jeszcze kilku baronów do archipelagu, przynoszą nam dużo zysków! Ha-ha-ha!";
			link.l1 = "Proszę iść do mojej łodzi, baronie.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "I nawet nie myśl o pościgu za nami, kapitanie. Wiesz, kim jestem. Mam więcej jeńców żabojadów, a jeśli nie wrócę na czas, wszyscy zostaną zabici przez moich ludzi. Zrozumiano?";
			link.l1 = "Nadejdzie czas, a rozprawimy się z wami, przeklęci bluźniercy!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Żartujesz sobie ze mnie?";
			link.l1 = "Chwileczkę, przyniosę to...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Steven, co zrobił twój tępak!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, co robiłeś? Gdzie są pieniądze? Nie powiedziałem moim chłopakom, że to nie było prawdziwe... i więc ten idiota uznał, że chciałeś ich oszukać...";
			link.l1 = "Co za szkoda! Baron nie żyje... Co teraz zrobi Poincy?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "No cóż, kumplu, to twoja wina, mam nadzieję, że to rozumiesz. Być może, to będzie dla ciebie lepiej.";
			link.l1 = "Co za idiota ze mnie! Wszystko schrzaniłem. Dobrze, pójdę do Poincy... Wybacz mi, że byłem głupcem, Stevenie, do zobaczenia.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Musisz odpocząć, tracisz swój talent. Przyjdź do mnie kiedyś, załatwię ci trochę rumu i piękne dziewczęta.";
			link.l1 = "Dziękuję, odwiedzę cię, kiedy będę mógł.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Proszę bardzo, kumplu. To była najlepsza zabawa, jaką miałem w tym roku! Śmialiśmy się tak bardzo, ja i moi chłopcy!.. Więc chciałbym ci za to podziękować. Oto twoje pieniądze.";
			link.l1 = "Powinieneś zostawić sobie część.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Zapomnij o tym. Zrobiłem to dla dobra naszej przyjaźni. Braterstwo Wybrzeża jest ci winne znacznie więcej, a jednak nie poprosiłeś o ani jednego dubloona.";
			link.l1 = "Mimo to, weź przynajmniej pięćdziesiąt tysięcy za usługi i rekompensatę. Dziękuję, Steven! Cieszę się, że kiedyś spotkałem cię na tej dziwnej Wyspie Sprawiedliwości.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "I ja również. Charles, odwiedź mnie, kiedy tylko będziesz miał chwilę!";
			link.l1 = "Z przyjemnością!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Spóźniłeś się o tydzień! Nie powiedziałem moim chłopakom, że to nie było prawdziwe... ! Odmówili dłużej czekać i postanowili zakończyć żywot twojego barona!";
			link.l1 = "Co za idiota ze mnie! Wszystko popsułem! Co powiem Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Cóż, przyjacielu, to twoja wina, mam nadzieję, że to rozumiesz. Być może to wyjdzie ci na dobre.";
			link.l1 = "Dobrze, pójdę do Poincy... Wybacz mi, że byłem głupcem, Stevenie, do zobaczenia..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "Musisz odpocząć, tracisz swój kunszt. Przyjdź do mnie kiedyś, załatwię ci trochę rumu i piękne panny";
			link.l1 = "Dziękuję, odwiedzę cię, gdy tylko będę mógł.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "Interesujące, zaintrygowany. Cóż, chodźmy na spacer.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Niech mnie kule biją! Nie wierzę własnym oczom! Czy to naprawdę ona? Powiedz mi, czy to ona? Czy to 'Fortuna'?!";
			link.l1 = "Tak, mój przyjacielu, twoje oczy cię nie zwodzą. To ona. Tęskniłeś za nią?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ha ha ha, nie mogę w to uwierzyć! Tysiące diabłów! Ale skąd to wziąłeś?";
			link.l1 = "Od pewnego Szkota o imieniu William Paterson. Tak, tak, od tego, który kupił go od Czarnego Pastora.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Niech mnie kule biją... I co, sprzedał ci „Fortunę”? Taki piękny statek? Po tym, jak go kupiłeś?";
			link.l1 = "Hehe, cóż, prawie. Ujmijmy to tak: nie dogadaliśmy się za dobrze, więc wziąłem statek jako rekompensatę za koszty, które poniosłem w wyniku naszego konfliktu. I tak nie potrzebuje statku.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "Zaskakujesz mnie jeszcze bardziej... On jest kapitanem wojskowym w służbie Anglii. Jego eskadra kolonii może rabować w razie potrzeby. Nawet ja nie ryzykowałem połamać sobie na nim zębów. A jak to sprawdziłeś? Udało ci się oderwać 'Fortunę' od eskadry?";
			link.l1 = "Nie, eskadra zatonęła. Właściwie, to nie było łatwe. Bitwa była poważna, ale miała miejsce daleko od zamieszkałych miejsc, a tylko moi marynarze i oficerowie byli wśród świadków. Ogólnie rzecz biorąc, nie boję się prześladowań ze strony brytyjskich władz. William Paterson po prostu zniknął podczas jakiejś zwyczajnej przygody...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Och... Już dawno straciłem nadzieję na ponowne zobaczenie mojej jaskółki. No cóż, mam nadzieję, że ten statek będzie ci wiernie służył. Naprawdę cieszę się dla ciebie, przyjacielu!";
			link.l1 = "Co? Nie potrzebujesz go? Chciałem zwrócić go prawowitemu właścicielowi...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ha-ha-ha, mój przyjacielu, zatrzymaj 'Fortunę' dla siebie. Po pierwsze, jesteś jej prawowitym właścicielem. Uczciwie zdobyłeś ją w walce. Nie jest dobrze porzucać statek po tym. A po drugie, mam już nowy okręt. Oczywiście, kiedy kupiłem 'Fortunę', nie myślałem, że kiedykolwiek zamienię ją na coś innego. Ale skoro już nie spodziewałem się jej zobaczyć ponownie, zamówiłem nową fregatę u Alexusa. I wiesz co... Jest cholernie dobry. Słyszałem, i w tym przypadku nie obyło się bez twojego udziału, ha ha!";
			}
			else
			{
				dialog.text = "Ha-ha-ha, mój przyjacielu, zatrzymaj 'Fortunę' dla siebie. Po pierwsze, jesteś jej prawowitym właścicielem. Uczciwie zdobyłeś ją w bitwie. Nie jest dobrze porzucać statek po tym. A po drugie, nowy statek już jest dla mnie budowany. Oczywiście, kiedy kupiłem 'Fortunę', nie myślałem, że kiedykolwiek zamienię ją na coś innego. Ale, skoro już nie spodziewałem się jej ponownie zobaczyć, zamówiłem nową fregatę u Alexusa. I nie mogę się doczekać, kiedy będę mógł postawić stopę na jej pokładzie.";
			}
			link.l1 = "Cóż, nie mam innego wyboru, jak tylko zatrzymać ten piękny statek dla siebie, Steven!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Dokładnie. Jedyne, o co cię proszę, to dbaj o 'Fortunę'. Wierz mi, takiego statku nigdzie indziej nie znajdziesz. Jest wyjątkowy. I kocham go jako wspomnienie. I byłbym szczęśliwy wiedząc, że mój przyjaciel jest właścicielem tego statku, a nie jakiś łotr.";
			link.l1 = " Dobrze, Steven. Obiecuję, że będę chronił 'Fortunę'.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Tak, i jeszcze jedno...";
			link.l1 = "Słucham.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Skoro masz teraz 'Fortunę', chcę zaproponować ci pewien interes.";
			link.l1 = "Słucham cię BARDZO uważnie.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "Jak już mówiłem, Alexus obecnie buduje dla mnie nową fregatę. Oczywiście, raczej nie przewyższy ona 'Fortuny' prędkością, ale też nie ustąpi za bardzo. A do jednego celu potrzebuję pary potężnych, ale szybkich statków. Może poradziłbym sobie sam, ale dwa są o wiele lepsze.";
				link.l1 = "Świetnie. A jaki to interes?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "Jak już mówiłem, Alexus niedawno zbudował dla mnie nową fregatę. Oczywiście, nie dorówna ona 'Fortunie' pod względem szybkości, ale nie ustąpi jej zbytnio. A właśnie do jednej rzeczy potrzebuję pary potężnych, ale szybkich statków. Mogę spróbować sam, ale dwa są o wiele lepsze.";
				link.l1 = "Świetnie. A jaki to interes?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "Za wcześnie, by o tym mówić, ponieważ jeszcze nie wiem, kiedy mój nowy statek opuści stocznie. Alexus zdaje się mieć pewne trudności z pozyskiwaniem materiałów. A tak przy okazji, jeśli masz możliwość, mógłbyś mu pomóc. Jestem pewien, że zapłaci przyzwoicie: dałem mu bardzo poważną zaliczkę. Po znalezieniu wszystkich materiałów, myślę, że za miesiąc mój statek będzie gotowy. Wtedy na ciebie czekam. Ale koniecznie przyjdź na 'Fortunę' i wyposaż ją zawczasu, wtedy będzie mało czasu! Tak, i upewnij się, że Hiszpanie nie chcą zobaczyć twojej głowy na srebrnym półmisku. Opowiem ci wszystkie szczegóły później.";
			link.l1 = "Cóż, zapytam naszego szkutnika, jakiej pomocy może potrzebować. A wtedy wrócimy do naszej rozmowy miesiąc po tym, jak pomogę Alexusowi, kiedy znów będziesz żeglował.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "Za wcześnie, by o tym mówić, bo mój statek nawet jeszcze nie opuścił stoczni. Muszę go jeszcze wyposażyć. Więc czekam na ciebie najwcześniej za miesiąc. Ale koniecznie przyjdź na 'Fortunę' i wyposaź go wcześniej, wtedy czasu będzie niewiele! Tak, i upewnij się, że Hiszpanie nie chcą zobaczyć twojej głowy na srebrnej tacy. Wszystkie szczegóły opowiem ci później.";
			link.l1 = "Dobrze, wtedy wrócimy do naszej rozmowy później, gdy znów będziesz pod żaglami.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Cóż, dobrze. Teraz idę do rezydencji, jeśli nie masz nic przeciwko. Sprawy, jak to mówią, nie czekają.";
			link.l1 = "Do zobaczenia wkrótce, Rekinie! Nie żegnam się.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Moja jest gotowa, a co z twoją? Powiedziałem ci, żebyś przyszedł na 'Fortune'. Nie wiem, gdzie ją zostawiłeś, ale to zbyt ryzykowne, by wyruszać na taką grę na jakimkolwiek innym statku. Więc czekam na ciebie na statku, na którym się umówiliśmy. I nie przesadź.";
				link.l1 = "Cholera, zupełnie zapomniałem, łajdaku! Czekaj: wrócę na właściwy statek.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, mówiłem ci, żebyś przyszedł bez eskadry. W sprawie, którą chcę z tobą załatwić, dodatkowe statki są zdecydowanie zbędne. Przesuń swoją flotyllę gdzieś indziej i wróć.";
				link.l1 = "Tak, zupełnie zapomniałem. Poczekaj: wrócę wkrótce bez eskadry.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ah, tam jesteś, przyjacielu! W końcu! A już zaczynałem się martwić. Mój statek jest prawie gotowy. Teraz wysłałem go do Tirax: musi go wyposażyć w trzydziestodwucalibrowe działa, które zdobył z ciężkiego galeonu w zeszłym miesiącu. Już przepłynąłem nim do Turków i z powrotem i muszę powiedzieć, że Alexus wykonał świetną robotę. A propos, nie wybrałem jeszcze odpowiedniej nazwy dla niego, chociaż mam kilka opcji. Czy możesz mi pomóc wybrać?";
			link.l1 = "Oczywiście, że pomogę! Jak nazwiesz statek, tak popłynie, prawda? Jakie masz opcje?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Jak dotąd zdecydowałem się na trzy opcje.";
			link.l1 = "... ";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Pierwsza opcja to 'Widmo'. Fregata jest szybka i potężna, a z taką nazwą wszyscy sknery od Hawany po Cumanę będą drżeć na samo jej wspomnienie!";
			link.l1 = "Tak, i musisz jeszcze pojawiać się i znikać we mgle, żeby marynarze na pewno zaczęli się żegnać, ha ha! Dobra nazwa, podoba mi się.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Też mi się podoba. Drugą opcją jest 'Rekin'. I co? Czemu nie miałbym nadać mojemu statkowi własnego przezwiska? Bądźmy imiennikami, ha!";
			link.l1 = "Na 'Rekinie' jest Rekin... Ironia. Ale wszyscy będą wiedzieć, do kogo należy ten statek.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Ja tutaj mam podobnie. A trzecią opcją jest 'Furia'. Żeby wszyscy bali się nawet zbliżyć do mojego statku, ha ha ha!";
			link.l1 = "Bo możesz natknąć się na grad kul z boku? I co, nieźle.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Dokładnie! Ale teraz nie mogę zdecydować się między tymi trzema imionami. No dalej, pomóż. Jak sobie życzysz.";
			link.l1 = "Proponuję nazwać go 'Upiór'. Wtedy wszyscy kupcy wyrzucą białą flagę, gdy tylko zobaczą cię na horyzoncie!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "Lubię nazwę 'Rekin'. Wszyscy powinni wiedzieć, że ten statek to nie jakiś nowicjusz, ale sam przywódca Bractwa Wybrzeża!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "Myślę, że 'Flurry' to dobra nazwa. Każdy wojownik, kaper czy kupiec powinien wiedzieć, co się stanie, jeśli zdecyduje się walczyć z tym statkiem.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "Zobaczysz - nawet wojsko zacznie robić to samo, ha! Zatem postanowione. Trzymaj kufel, przyjacielu. Wypijmy za mój nowy statek. Za 'Widmo!'";
			link.l1 = "Za 'Fantoma!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "I niech pomyślą trzy razy, zanim wejdą mi w drogę! Zatem, postanowione. Trzymaj kufel, przyjacielu. Wypijmy za mój nowy statek. Za 'Rekina'!";
			link.l1 = "Za 'Rekina'!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "I jeśli on nadal zdecyduje, taka zawierucha go pokryje, że tropikalne burze wydadzą się lekkim wietrzykiem! Więc, postanowione. Trzymaj kufel, przyjacielu. Wypijmy za mój nowy statek. Za 'Zawierucha!'";
			link.l1 = "Na 'Huragan!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "I niech ten statek służy wiernie i nie zna goryczy porażki! No, teraz do rzeczy.";
			link.l1 = "Słucham cię uważnie.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Powiedz mi, Charles, czy wiesz, czym jest 'Złota Flota'?";
			link.l1 = "Kha-kha! .. Już się zakrztusiłem rumem. Steven, nie mów mi, że wyruszasz na dwa fregaty, by obrabować najlepiej uzbrojony konwój na Karaibach.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "„Cóż, nie, oczywiście, że nie jestem samobójcą. Na pewno nie obrabujemy całego konwoju. Ale tutaj możemy coś stamtąd uszczknąć.”";
			link.l1 = "Steven, wybacz, oczywiście, ale nie jestem na to gotowy. Tak, Hiszpanie spalą nas żywcem, jeśli wpakujemy się w ich flotę! Idźcie beze mnie.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "Dobrze, gdzie my tylko nie zniknęliśmy... Jestem gotów do udziału!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Argh! To szkoda. Jestem zbyt ryzykowny bez ciebie. W porządku, teraz nie będę cię namawiał, ale przemyśl to, dobrze? Jeśli kiedykolwiek się na to zdecydujesz, proszę, daj mi znać.";
			link.l1 = "Jeśli tak, to pewnie. Przepraszam, Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Takie przedsięwzięcia nie poddają się! No i co z tobą? Może zmieniłeś zdanie?";
			link.l1 = "Nie, przyjacielu, przykro mi, ale nadal odmawiam.";
			link.l1.go = "exit";
			link.l2 = "Dobrze, gdzie myśmy się nie zniknęli ... Jestem gotów uczestniczyć!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Może jesteś gotowy, ale twoja łajba nie jest. Mówiłem ci, żebyś przybył na 'Fortunie'. Nie wiem, gdzie ją zostawiłeś, ale to zbyt ryzykowne, aby podejmować takie ryzyko na jakimkolwiek innym statku. Czekam więc na ciebie na statku, na którym się umówiliśmy. I nie przesadzaj z napięciem.";
				link.l1 = "Cholera, zupełnie zapomniałem, niezdaro! Poczekaj: wrócę na właściwy statek.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Ale nie: nie jesteś gotowy, Charles. Mówiłem ci, żebyś przyszedł bez eskadry. W przypadku, który chcę z tobą omówić, dodatkowe statki są zdecydowanie niepotrzebne. Przemieść swoją flotę gdzieś i wróć.";
				link.l1 = "Tak, całkowicie zapomniałem. Poczekaj: wkrótce wrócę bez eskadry.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Tysiąc diabłów, to właśnie chciałem usłyszeć! Proponuję więc, żebyśmy razem urwali kawałek z konwoju. Mnóstwo łupów...";
			link.l1 = "Porwać, masz na myśli? Bez zostania złapanym przez strażnicze statki?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Dokładnie. Słuchaj, jak zapewne wiesz, 'Złota Flota' zbiera się w Porto Bello, a stamtąd płynie do Hawany. Po Hawanie nie ma już sensu go przechwytywać: płynie przez Atlantyk do Hiszpanii z taką eskortą, że tylko kompletny dureń wsadziłby mu głowę. Podczas przejścia z Porto Bello do Hawany sytuacja nie jest wiele lepsza. Oczywiście, możesz spróbować, ale do tego trzeba zebrać eskadrę zdolną rozbijać fortece jak orzechy. Natomiast w Porto Bello statki schodzą się z całego Maine i tam już nie są szczególnie chronione.";
			link.l1 = "Tylko teraz czas przejścia i nazwy takich statków są ściśle tajne. Nie będziemy kręcić się gdzieś koło Porto Bello przez pół roku i przechwytywać wszystkich hiszpańskich statków zmierzających do portu.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Oczywiście, że nie. Na przykład, z Kartageny statki płyną same, i, jak słusznie zauważyłeś, tylko Bóg wie, jakie to statki i kiedy wypłyną. Ale z Caracas, obok którego znajduje się hiszpańska kopalnia, a które jest dość daleko od Porto Bello, statki nie są całkiem samotne.";
			link.l1 = "Jak to jest, że nie jest zupełnie samotny?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "Udało mi się dowiedzieć, że statek załadowany towarami opuszcza Caracas sam lub z małą eskortą, ale gdzieś na długości geograficznej Zatoki Maracaibo spotykają go hiszpańskie okręty wojenne, aby zapewnić mu dalsze bezpieczeństwo. Jak myślisz, skąd wiedzą, kiedy i kogo mają tam spotkać?";
			link.l1 = "Musieli coś im powiedzieć...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "Racja. Zanim główny statek odpłynie, okręt kurierski wyrusza z Caracas do Porto Bello, zgłaszając miejsce i datę spotkania, a także nazwę hiszpańskiego statku. Następnie wraca i przewozi potwierdzenie, że statek zostanie przyjęty we właściwym czasie i miejscu. Dopiero wtedy, nasz cel z tobą wyrusza z Caracas.";
			link.l1 = " Ale jeśli przechwycimy kuriera, to statek w Caracas nie otrzyma potwierdzenia i nie opuści portu. Masz jakieś pomysły na ten temat? Poza tym, jak zamierzamy złapać samego kuriera? Nie wiemy też, kiedy on wyjedzie. ";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "I tutaj pojawia się mały haczyk. Hiszpanie, oczywiście, używają kurierów lugrowych do tych celów, ale to ryzykowne: zbyt duże jest ryzyko, że zostaną przechwyceni przez pierwszego napotkanego pirata. Więc można długo czekać na wysłanie statku. Dlatego, jeśli jest taka możliwość, przekazują instrukcje wraz z dobrymi, potężnymi, ale szybkimi statkami - kupcami, na przykład, lub korsarzami, które idą właściwą trasą. \nJak zamknięta poczta. Co więcej, jest to znacznie tańsze niż wysyłanie osobnego statku kuriera, nawet lugra. A chciwi hiszpańscy urzędnicy lubią oszczędzać pieniądze, jednocześnie wkładając coś do swojej kieszeni, hehe.";
			link.l1 = "Chyba rozumiem! Czy muszę zostać takim kupcem?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Dokładnie! I mieliśmy szczęście: udało mi się dowiedzieć z wiarygodnego źródła, że w Caracas teraz szukają takiego kuriera, by wysłać go z listem w ciągu najbliższych trzech tygodni. A ty masz akurat potężny i szybki statek, i do tego zbudowany przez Hiszpanów! Zdobądź licencję GVIK, dla większej wiarygodności - od razu na sześć miesięcy, kup wystarczająco dużo towarów w Caracas do opłacalnej odsprzedaży w Porto Bello, a potem idź do lokalnego szefa urzędu portowego i zapytaj, czy trzeba coś zabrać po drodze. \nJeśli Urząd Portowy zapyta, przedstaw się jako Hiszpan. I tak - nawet nie myśl o ciągnięciu za sobą eskadry. Nie ma potrzeby przyciągać zbyt dużej uwagi, bo inaczej całe przedsięwzięcie może zostać zniweczone.";
			link.l1 = "I z dokumentów, które mi przekażą, dowiem się o dacie i miejscu spotkania statku z konwojem?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "Nie tak prosto. Mówię ci: dokumenty są zapieczętowane. I nie możesz ich sam otworzyć. Otworzą je w urzędzie portowym Porto Bello, a potem napiszą odpowiedź i, jeśli będziesz tak uprzejmy, żeby powiedzieć, że wracasz do Caracas, poproszą cię, żebyś go tam zabrał. Odpowiedź, oczywiście, również będzie zapieczętowana.";
			link.l1 = "I jak mogę się dowiedzieć o miejscu i dacie spotkania?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "Musisz być sprytny i jakoś to podpatrzeć... Na przykład w momencie, gdy dokumenty są otwierane w Porto Bello i piszą odpowiedź. Albo po prostu je ukraść, gdy dadzą ci potwierdzenie, które trzeba będzie zabrać do Caracas. Ale to nie jest dobre rozwiązanie: po tym wszystkim może się nie udać.";
			link.l1 = "Oczywiście, że to trudne... Ale myślę, że dam sobie radę.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "Ja z kolei odbiorę mój statek od Marcusa i będę czekał na ciebie na kotwicy u przylądka Santa Maria na Curacao. Gdy skończysz, po prostu rusz do mnie. Przechwycimy statek na wskazanych współrzędnych, a potem natychmiast się stąd wynosimy. Teraz rozumiesz, dlaczego statki muszą być potężne, ale szybkie? Wcale nie chcę walczyć z hiszpańską eskadrą wojenną. Będziesz musiał się od nich oddalić.";
			link.l1 = "Rozumiem. Cóż, w takim razie ruszam dalej. Spotkajmy się na Przylądku Santa Maria!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "Zgadza się, spotkamy się tam. No cóż, powodzenia, przyjacielu! Mam nadzieję, że nasz interes się uda.";
			link.l1 = "Też mam taką nadzieję. W każdym razie, odchodzę.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Cholera, Charles! Myślałem, że cię już nigdy nie zobaczę! Gdzieś ty się podziewał? Czekałem na ciebie w wyznaczonym miejscu, ale nigdy nie przyszedłeś. I nie było od ciebie żadnych wieści.";
			link.l1 = "Przykro mi, Steven. Nie udało mi się wykonać zadania.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Eh, przegapili taką rybę... Dobrze, nie martw się. Może następnym razem się uda.";
			link.l1 = "Mam nadzieję.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", co do licha? Mówiłem ci, żebyś był bez eskadry! Zrozum: nie potrzebujemy żadnego balastu, w przeciwnym razie cała operacja może się nie udać! Nie wiem, co cię opętało, ale to tak nie zadziała. Pilnie wyślij swój karawan gdzieś i wróć na jednym statku. Czekam na ciebie tutaj.";
				link.l1 = "Tak, właśnie pomyślałem, że to bardziej prawdopodobne... Dobrze, rozumiem cię. Poczekaj tutaj: zaraz wracam!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", co do diabła? Mówiłem ci, żebyś był na 'Fortunie'! Zrozum: potrzebujemy dwóch szybkich i potężnych statków, inaczej cała operacja może się nie udać! Nie wiem, co cię napadło, ale tak to nie zadziała. Natychmiast zmień swój koryto na 'Fortunę' i wracaj. Czekam tu na ciebie.";
				link.l1 = "Tak, właśnie pomyślałem, że ten statek jest lepszy... Dobrze, rozumiem cię. Poczekaj tutaj: zaraz wracam!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "A oto jesteś, mój przyjacielu! No, jak ci się podoba mój przystojniak?";
			link.l1 = "Piękna fregata, Steven! Nie odmówiłbym takiej...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "Nie, teraz masz 'Fortunę', haha! No, opowiedz mi, jak poszło.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Wszystko poszło bezbłędnie: udało mi się podszyć pod uczciwego i niezawodnego kupca. Zabrałem dokumenty do Porto Bello, gdzie udało mi się odwrócić uwagę miejscowego szefa urzędu portowego na pięć minut i przepisać dla siebie datę i współrzędne spotkania statków z ładunkiem i eskadry wojskowej.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "Były pewne drobne komplikacje. List został wysłany do Porto Bello przez kuriera. Przechwyciłem go, dostarczyłem do adresata i nawet otrzymałem odpowiedź, ale szef władzy portowej odgadł, że nie byłem osobą, która miała przynieść dokumenty. Musiałem stamtąd wyrwać się z walką. Jednak dowiedziałem się daty i współrzędnych spotkania statku z ładunkiem i eskadrą wojskową, i dostarczyłem odpowiedź do Caracas, więc produkcja czeka na nas!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Chwila. Czy powiedziałeś 'statki'?";
			link.l1 = "Tak, Rekinie! Będzie ich dwóch!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ha-ha-ha, tak, zgarnijmy całą pulę! Cóż, moja bestia jest gotowa przejść przez chrzest bojowy. Ale jeszcze nie brała udziału w bitwach, więc poprowadźmy bitwę. A na razie dołączę do twojej eskadry.";
			link.l1 = "Czy mam dowodzić samym Stevenem Dodsonem, głową Braci Wybrzeża? W interesach!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Cóż, nie bądź zbyt arogancki: to tylko dlatego, że po raz pierwszy będę walczył na moim statku. I zadbaj o dostępność wolnych oficerów dla statków-pryzów. Bo ich ładownie będą pełne, a żaden z mojej załogi nie będzie w stanie samodzielnie zarządzać statkiem... Dobrze, dość drapania języka. Łup czeka na nas!";
			link.l1 = "Dokładnie! Idę na mój statek.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Tak, odziedziczyłeś... Wtedy musimy przygotować się na to, że eskadra dotrze tam przed ustaloną datą, i będziemy musieli walczyć ze wszystkimi naraz.";
			link.l1 = "Dlaczego tak mówisz?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "  A ty burzy mózgi. W Porto Bello wiedzą, że statek z ładunkiem na pewno opuści Caracas, ponieważ tam dostarczyłeś list zwrotny. Ale skoro się zdradziłeś, zrobią wszystko, aby uniemożliwić nam przechwycenie tego statku. Myślę, że eskadra przybędzie tam wcześniej. Tak bym zrobił. Więc przygotujmy się na ciężką walkę. Spóźnione wycofanie się.";
			link.l1 = "Nie martw się. Ty i ja to dwa wilki morskie, nie przez to przechodziliśmy!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "Twoja prawda. Cóż, mój bestia jest gotowa przejść przez chrzest ognia. Ale jeszcze nie brał udziału w bitwach, więc poprowadź bitwę ty. Tymczasem dołączę do twojej eskadry.";
			link.l1 = "To ja mam rozkazywać samemu Stephenowi Dodsonowi, przywódcy Braci Wybrzeża? Do pracy!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "Nie ma czasu na pogawędki, "+pchar.name+"  Ruszajmy po łup!";
			link.l1 = "I oby los nam sprzyjał!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Tysiąc diabłów! Świetna robota, Charles! Łup okazał się znacznie bogatszy, niż się początkowo spodziewałem! Myślę, że cała ta wyprawa była zdecydowanie tego warta.";
				link.l1 = "Całkowicie się z tobą zgadzam, Steven! Dziś jest zdecydowanie nasz dzień!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "Dobra robota, przyjacielu. Chociaż musimy przyznać, że straciliśmy dużo zdobyczy.";
					link.l1 = "Zgadzam się, Steven, moglibyśmy zrobić lepiej. Ale to, co mamy, też jest dobre!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "Cholera! To był taki dobry pomysł... A w rezultacie, wydatki z tej kampanii są większe niż zyski. Charles, właściwie to dałem ci dowództwo, a ty zdołałeś wszystko stracić!";
					link.l1 = "Nie mów nic... Sam jestem cholernie wściekły. Ileż to zdobyczy wymknęło się z rąk!..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Cóż, obaj wykonaliśmy dobrą robotę. Ja wymyśliłem plan i zdobyłem informacje o kurierze, a ty znakomicie wprowadziłeś ten plan w życie. I obaj walczyliśmy na równych warunkach o naszą zdobycz. Dlatego proponuję podzielić ją zgodnie z prawami Braci Wybrzeża: po równo!";
			link.l1 = "Zrobimy to!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Cóż, teraz wyruszam na Isla Tesoro. Muszę naprawić statek i odpowiednio uczcić pierwszą udaną podróż na moim nowym statku. Powodzenia, przyjacielu! Zawsze miło cię widzieć w mojej rezydencji!";
			link.l1 = "Cieszę się, że nasz interes okazał się tak dochodowy. Na pewno kiedyś cię odwiedzę. Powodzenia!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "W porządku, zatrzymaj to wszystko dla siebie. Jeśli w ogóle coś zostało. Nie obchodzą mnie te małe sprawy. W końcu to ja cię w to wszystko wciągnąłem.";
			link.l1 = "Tak, moja wina też... Przepraszam, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Nie przepraszaj, wciąż jestem ci winien życie, i nie zapomnę tego. A teraz ruszam na Wyspę Skarbu. Musimy naprawić statek i go umyć... Chociaż, co tam do mycia... Powodzenia, kamracie! Zawsze cieszę się, gdy cię widzę w mojej rezydencji!";
			link.l1 = "Dobrze, wszystko się może zdarzyć, porażki się zdarzają. Najważniejsze, że żyjemy. Na pewno kiedyś cię odwiedzę, przyjacielu! Powodzenia!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
