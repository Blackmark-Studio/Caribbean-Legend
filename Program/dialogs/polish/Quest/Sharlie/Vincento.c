// отец Винсенто
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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "W końcu widzę słynnego francuskiego kapitana "+GetFullName(pchar)+" we własnej osobie. Słyszałem wiele o twoich wyczynach. Jesteś dzielnym żołnierzem i, mam nadzieję, lojalnym i wiernym synem naszej Matki, Świętego Kościoła Rzymskokatolickiego. Usiądź, mój synu. Nie trzeba stać z mojego powodu. Dominus vobiscum! ";
				link.l1 = "I z duchem twoim, Wasza Ekscelencjo. Moja droga tutaj była długa i trudna... Przez ciernie do gwiazd i wszystko...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Tak, widzę w twych oczach, że masz dla mnie wieści. Całkowicie cię słucham.";
				link.l1 = "Wasza Ekscelencjo, znalazłem waszego zaginionego sekretarza...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Czy przyniosłeś mi wieści z San Jose, mój synu?";
				link.l1 = "Tak, Wasza Ekscelencjo. Ustaliłem, co się stało z naszym wspólnym znajomym Miguelem Dichoso i jego zaginioną fregatą. Gdy tylko jego statek wpłynął na Atlantyk w drodze do Hiszpanii, natychmiast został wciągnięty w przeciwny sztorm i z powrotem porwany na Karaiby.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Pokój z tobą, synu mój... Co mogę dla ciebie uczynić?";
				link.l1 = TimeGreeting()+" , Wasza Ekscelencjo. Czy macie jakieś wieści dotyczące naszej umowy?"link.l1.go ="strażnikprawdy_17";
				break;
			}
			dialog.text = "Czy coś chciałeś, mój synu?";
			link.l1 = "Nie, nic, Ojcze.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Wchodźcie przez ciasną bramę; bo szeroka jest brama i przestronna droga, która prowadzi do zagłady, a wielu jest takich, którzy przez nią wchodzą. Bo ciasna jest brama i wąska droga, która prowadzi do życia, a mało jest takich, którzy ją znajdują. Droga sprawiedliwości jest zawsze trudna, mój synu. Ale cel, który jest osiągnięty, w pełni wynagradza sprawiedliwego człowieka za jego uczynki.";
			link.l1 = "Zgadzam się, Wasza Ekscelencjo. Wykonałem zadania, które mi powierzyłeś. Już masz tchórzliwego pirata, który ukradł cenne naczynia z Kościoła. Teraz zwracam wszystkie zabrane rzeczy: monstrancję, krzyż i kadzielnicę. Weź je dla parafii w Santiago.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite! Dziękuję ci z głębi serca za twoją wierną służbę Świętej Matce Kościołowi i parafii Santiago, mój synu. Twoje dzieła nie pozostaną bez nagrody. Parafianie zebrali ofiarę dla odważnego wojownika, który zwrócił ich skradzione przedmioty, i z przyjemnością przekazuję ją tobie w ich imieniu. 'Robotnik jest godzien swojej zapłaty.' ";
			link.l1 = "Dziękuję, Wasza Ekscelencjo. Co za miła niespodzianka!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("Otrzymałeś skrzynię dublonów");
			PlaySound("interface\important_item.wav");
			dialog.text = "Wierna służba Matce Kościołowi zawsze jest wiernie wynagrodzona, "+pchar.name+"Ze swej strony mam nadzieję, że pozostaniesz oddanym wojownikiem w obronie i ochronie chrześcijaństwa, gdyż grozi nam śmiertelne niebezpieczeństwo, wiszące nad nami niczym mityczny Miecz Damoklesa.";
			link.l1 = "Co to może być, Wasza Ekscelencjo?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Być może jesteś przeznaczony, by stać się naszym czempionem w nadchodzącej bitwie przeciwko ciemnym mocom i władcom tego świata, mój synu, albowiem wiele jest znaków i omenów, że coś złowrogiego nadchodzi.";
			link.l1 = "Omeny i przepowiednie?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Wiele, mój synu... Jedno z nich to twoje pragnienie poszukiwania zagubionego indiańskiego złota z pogańskiego Tayasal, ponieważ to, co zachowane jest w ich skarbcach, jest dokładnie tym, co stanowi zagrożenie dla całego chrześcijańskiego świata.";
			link.l1 = "Czy mógłbyś mnie nieco oświecić w kwestii tego złota, czcigodny ojcze? O jego zniknięciu już słyszałem, ale o jakim zagrożeniu mówisz?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Słuchaj uważnie, mój synu, i wiedz, że wszystko, co zaraz usłyszysz, jest tylko dla twoich uszu. Na długo przed tym, jak Miguel Dichoso wywiózł to pogańskie skarby ze starożytnego indiańskiego miasta, kazałem przesłuchać pojmanego człowieka z plemienia Itza w sprawie naszej misji na Karaibach. Lud Itza to potomkowie Majów, potężnego imperium, które zaginęło wieki przed tym, jak nawet Cristobal Colon i jego ludzie po raz pierwszy postawili stopę w Nowym Świecie. Imperium Majów rządziło otaczającymi plemionami żelazną ręką, z niewypowiedzianą mocą przyznaną im poprzez piekielne układy z demonami. Czarne magije kupione krwią pokoleń ludzkich ofiar. \nTen człowiek z Itza wiedział o Tayasal, zaginionym mieście Majów i niewiarygodnym złu, które wciąż jest w nim zapieczętowane. Powiedział nam wszystko, co wiedział. Jeśli te pieczęcie zostaną otwarte, konsekwencje będą apokaliptyczne. Od tego momentu zrobiłem wszystko, co mogłem, aby powstrzymać to straszliwe zło przed przebudzeniem. Pisałem do Eskorialu i Rzymu z desperacką prośbą o pomoc.\nOni posłuchali i wysłali Don Ramona de Mendoza y Riba, który założył swoją bazę na Providence i rozpoczął poszukiwania Tayasal. Wtedy odkryłem, że dobry Don Mendosa miał... inne motywacje do odnalezienia zaginionego miasta. Zamiast zapobiegać końcowi świata, pragnął służyć Mamonowi, a nie Chrystusowi.\nTo dlatego Bóg go opuścił i zesłał anioła śmierci do jego obozu. Wszystkie jego działania były daremne i prowadziły tylko do bezsensownej śmierci hiszpańskich żołnierzy i wiernych indiańskich konwertytów. Pisałem do Eskorialu z prośbą o zwolnienie Ramona de Mendoza z powodu rażącej niekompetencji i zgodzili się go z tej funkcji zwolnić, ale...";
			link.l1 = "Miguel Dichoso przybył.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, ten stary wąż...";
			else sTemp = "Hm...";
			dialog.text = "Dokładnie. Ten przysłany przez diabła awanturnik odnalazł Tayasal wraz ze skarbami starożytnych Majów. Jednak radość Don Mendosy była krótkotrwała. Wszystkie te skarby zniknęły wraz z Dichoso w drodze powrotnej do Hiszpanii. Prawdopodobnie wraz ze wszystkimi sztabkami złota i ozdobami Miguel zabrał ze sobą starożytne źródło diabelstwa, przerażającą maskę starożytnego boga demona Majów o imieniu Kukulkan.";
			link.l1 = sTemp+"Ale o jakim złu mówisz, Wasza Ekscelencjo? Skąd o tym wiesz?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "To zło, które niesie śmierć wszystkim ochrzczonym chrześcijanom Karaibów, Nowego Świata, a być może także Starego Świata. Koniec nadejdzie jak złodziej w nocy, i nikt nawet nie zda sobie sprawy, co się stało. A znaki tego są już wszędzie!";
			link.l1 = "Jakie znaki? Nie rozumiem...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Synu, czyżbyś był tak ślepy, że nawet ich nie zauważasz? Dzieją się już od dwudziestu pięciu lat, niemal bez przerwy!";
			link.l1 = "Pragnąłbym skromnie wspomnieć, Wasza Ekscelencjo, że bieg mojego życia trwa dokładnie tyle czasu, nie wspominając już o tym, że większość życia spędziłem w Europie. Moja ignorancja powinna być nieco usprawiedliwiona.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Rozumiem, "+pchar.name+"Teraz, czy nie zauważyłeś dziwnych rzeczy dziejących się po całych Karaibach od chwili, gdy przybyłeś tu z Europy? Czy nie wydaje ci się dziwne, że czary, czarna magia i inne rytuały mają tu znacznie większą moc niż w ojczyźnie? Pogańskie amulety zaczarowane przez indiańskich szamanów posiadają prawdziwą moc, którą każdy człowiek może odczuć, trzymając je w dłoni.\nNawet nasi chrześcijańscy alchemicy - niech Bóg sprawi, by dostrzegli błąd swoich dróg! - opanowali sztukę tworzenia zaczarowanych przedmiotów. Nie zdają sobie sprawy, że służą samemu Diabłu, robiąc to. Czy nie czujesz nienaturalnej obecności czegoś piekielnego, czającego się tuż poza twoim polem widzenia?";
			link.l1 = "Masz rację, ojcze. Na początku mnie to zaskoczyło, ale teraz chyba już się do tego przyzwyczaiłem... W końcu to Nowy Świat!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "Ale nie zawsze tak było. Ciemność, o której mówię, pojawiła się tutaj jakieś dwadzieścia pięć lat temu i z każdym dniem zyskuje coraz większą moc. To oznacza tylko jedno: 'to' już przyszło, 'to' jest wśród nas i 'to' działa...";
			link.l1 = "O kim mówisz? Kim jest to tajemnicze 'ono'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "Zaprzysiężony wróg chrześcijan, pragnący zniszczenia Kościoła i całego chrześcijaństwa.";
			link.l1 = "...Czy mówisz o Antychryście?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Czy to jest 'Antychryst', czy tylko 'antychryst', nie ośmielę się powiedzieć. Nie ma znaczenia, jakie imię nosi ta bestia, gdy przybiera śmiertelne ciało w groteskowej parodii Wcielenia Naszego Zbawiciela. Ważne jest to, co zamierza zrobić. Jestem tu, aby to powstrzymać, a ty mi w tym pomożesz. Ale nieco się zapędziliśmy. Jesteś człowiekiem czynu. Prawdopodobnie wolałbyś przejść do sedna i pominąć teologię, prawda?";
			link.l1 = "Przeciwnie, dowiedziałem się od Was, Wasza Ekscelencjo, wielu nowych i ważnych rzeczy. Jestem gotów słuchać dalej.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Jesteś uprzejmy i dobrze wychowany, mój synu. To dobrze. Teraz wracajmy do powodu, dla którego się ze mną skontaktowałeś. Naszym wspólnym celem jest odnalezienie skarbów Tayasal zabranych przez Dichoso. Prawdopodobnie znajdziemy wśród tych skarbów broń, której możemy użyć w nadchodzącej walce z Diabłem.";
			link.l1 = "Ale czyżby Dichoso już opuścił Karaiby i siedział na stosie złota w Hiszpanii?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "Nie. Mam dowód, że te skarby wciąż są tutaj na Karaibach. Nie musisz jeszcze znać moich źródeł, musisz mi zaufać. Poza tym, myślę, że Dichoso kłamał baronowi.\nJego opowieść o ruinach Tayasal nie zgadza się z tym, co mój Indianin Itza powiedział mi podczas przesłuchania. Nie wspominając o tym, że Dichoso był jedynym ocalałym z zasadzki komarów, co było po prostu trochę zbyt wygodne.";
			link.l1 = "Rozumiem, że Don Mendosa również w to wierzy, skoro zaatakował Saint-Pierre, próbując odnaleźć Dichoso?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "Działania barona nie powinny cię martwić, synu. Kieruje się jedynie żądzą złota i osobistym zyskiem. Jego chciwość będzie kamieniem młyńskim u jego szyi, podczas gdy wokół niego dobrzy chrześcijanie walczą z siłami piekielnymi.";
			link.l1 = "Czy masz jakieś wskazówki, gdzie powinniśmy szukać Dichoso i skarbu?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "Rozmyślam o tym każdą chwilę, mój synu, ale nie mam nic konkretnego do powiedzenia. Jest tu jednak człowiek, który nam pomoże, naturalny filozof z Genui. Przywiozłem go tutaj ze mną, aby pomógł kategoryzować rzeczy Nowego Świata, które mogłyby być przydatne dla misji Kościoła. Był świadkiem przesłuchania Indianina Itza i, według mojej najlepszej oceny, rzeczy, które usłyszał, zaszokowały go i przewrotnie przyciągnęły. \nDiabeł użył jego ciekawości jak przynęty na wilczy hak i opętał go, ciało i duszę. Pan dał mu wielką zdolność do medycyny i alchemii, ale nasz Genueńczyk wpadł w pokusę czarnej magii i czarodziejstwa. Kilkakrotnie rozmawiał z moim jeńcem Itza bez mojej zgody, a potem zniknął. Musimy go odnaleźć i ocalić jego duszę.";
			link.l1 = "Rozumiem, że mam go znaleźć?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Tak, mój synu. On jest pierwszym krokiem do odnalezienia skarbu i broni, którą możemy użyć przeciwko złym siłom, które nam zagrażają.";
			link.l1 = "Kim jest ten Genueńczyk?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "Jego imię to Gino Gvineili. Ma około trzydziestu lat, plus minus kilka. Utalentowany lekarz i alchemik. Jak już powiedziałem, teraz studiuje czarną magię. Według moich najlepszych informacji ukrywa się gdzieś w angielskich koloniach na Karaibach.\nZnajdź Gino Gvineili, mój synu. Jeśli udało ci się znaleźć tego pirata, który ukradł nasze kościelne naczynia, to również uda ci się znaleźć mojego zbiegłego sekretarza i przyprowadzić go tutaj. Będę się modlił o wstawiennictwo św. Antoniego w twojej sprawie.";
			link.l1 = "Rozumiem, Wasza Ekscelencjo. Nie zmarnuję ani chwili. Do zobaczenia później!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "Prawie zdradziłem się krzykiem zaskoczenia. Ojciec Vincento rozkazał mi znaleźć i przyprowadzić jego zbiegłego sekretarza, lekarza alchemika o imieniu Gino Gvineili. Tego samego Gino, który zajmuje pokój gościnny na drugim piętrze mojego domu w St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "Muszę znaleźć mężczyznę o imieniu Gino Gvineili, ukrywającego się gdzieś w angielskich koloniach karaibskich. Jest lekarzem i alchemikiem. Gdzie może się ukryć taki człowiek?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Miałem pełną wiarę, że to powiesz, "+pchar.name+". Teraz moja wiara jest jeszcze bardziej wzmocniona przez pewność, że zostałeś mi zesłany ręką samej Opatrzności Bożej. Gdzie jest mój nieszczęsny, marnotrawny syn?";
			link.l1 = "Obawiam się, że to, co usłyszysz, nie przypadnie ci do gustu, ale nie mam wyboru. Twój sekretarz nie żyje.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Niech Bóg ocali jego duszę i wybaczy mu grzechy... Jak to się stało, synu mój?";
			link.l1 = "Znalazłem Gino na Antigui. Ukrywał się tam w jednym ze starych budynków, które wzniesiono pod laboratorium. Nie zgodził się pójść ze mną dobrowolnie. Po usłyszeniu twego imienia i widząc, że byłem gotów użyć siły, wyjął fiolkę z przejrzystym płynem z fałd swojego długiego odzienia i wypił ją w okamgnieniu...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = " ";
			link.l1 = "A potem stało się coś strasznego: zrobił się czerwony, potem ciemnoniebieski. Upadł na podłogę, drgając w spazmach i w ciągu minuty umarł w straszliwych bólach. Silny zapach migdałów wypełnił pokój.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Ty biedny głupcze... Nawet ostatnią chwilę swojego życia spędził w grzechu, popełniając samobójstwo. Jaka tragiczna strata. Będę się modlił za jego duszę...";
			link.l1 = "Po jego śmierci przeszukałem jego mieszkanie i znalazłem tam ten foliał. Czy może cię to zainteresować lub może pomóc nam w naszych poszukiwaniach? Są tu jakieś dziwne i ezoteryczne notatki...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("Dałeś almanach");
			PlaySound("interface\important_item.wav");
			dialog.text = "To almanach biednego Gino. Pisał tam notatki o wszystkich swoich eksploracjach. Daj mi go, synu, przestudiuję, co w nim zapisano. Może znajdziemy jakąś wskazówkę.\nChociaż nie przyprowadziłeś mi z powrotem Gino Gvineili, jestem zadowolony z twoich starań, synu. Teraz mam dla ciebie jakieś wieści.";
			link.l1 = "Masz moją uwagę, Ojcze.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Zdobyłem informację, że wyspa Trynidad była ostatnim miejscem, gdzie widziano fregatę Dichoso. Znam również przybliżony czas - początek kwietnia 1654 roku.\nUdaj się na Trynidad i spróbuj dowiedzieć się czegokolwiek o losach fregaty: dokąd zmierzała, jakie plany miał kapitan, cokolwiek uda ci się znaleźć. Rozumiem, że minęło dużo czasu i ludzka pamięć ma swoje granice, ale tonący brzytwy się chwyta.";
			link.l1 = "Zrobię wszystko, co w mojej mocy.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Pozwól mi zobaczyć twój list przepustowy. Dodam zezwolenie na odwiedzenie kolonii San Jose.";
			link.l1 = "Prosze.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "Prosze... to będzie wszystko. Nie zapomnij podnieść hiszpańskiej flagi na swoim statku. Podejdź i przyjmij błogosławieństwo Boże, mój synu!";
			link.l1 = "Chwila, Wasza Wysokość. Czy mógłbym zadać pytanie?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Tak, oczywiście. Co chciałbyś wiedzieć?";
			link.l1 = "Podczas naszego ostatniego spotkania wspominałeś o Indianinie Itza, który poinformował cię o Tayasalu. Myślałem o tym dużo... Powiedz mi, czy ten człowiek miał przy sobie coś? Jakieś przedmioty, pisma, czy coś w tym rodzaju? To może okazać się przydatne.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Żadnych specjalnych przedmiotów, mój synu. Przepaska biodrowa, prymitywna biżuteria, bambusowa fajka z jakimiś ziołami i kawałek surowej skóry używanej jako knebel.\nWszystko to zostało wysłane do Don Ramona de Mendoza y Riba. Ale zapewniam cię, nie było tam nic wartego uwagi.";
			link.l1 = "Rozumiem. Dziękuję, Ojcze. Do następnego razu!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Niech Wszechmogący cię błogosławi i strzeże... Co się stało z Miguelem Dichoso? Dowiedziałeś się?";
			link.l1 = "Niestety, nie. Ostatnia rzecz, którą mogli mi powiedzieć świadkowie, to że Santa Quiteria została porwana przez gwałtowne wiatry w kierunku Martyniki. Nie wiadomo na pewno, czy statek został uratowany, czy zatonął. Ale mam podejrzenia, że Miguel Dichoso wyszedł z tego cało.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Co sprawiło, że tak postanowiłeś, mój synu?";
			link.l1 = "Klucz tkwi w tym, że fregata ukrywała się gdzieś w kierunku Martyniki. I całkiem niedawno dzielny caballero o imieniu Diego de Montoya, jeden z ludzi Don Ramona de Mendosa, zaatakował Saint-Pierre z zamiarem znalezienia Miguela Dichoso, który rzekomo się tam ukrywał.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Więc baron uważa, że Dichoso ukrył się z Francuzami...";
			link.l1 = "Znam dobrze Saint-Pierre i gubernatora Jacquesa Dyel du Parquet, Wasza Ekscelencjo. Nikt tam nie znał Hiszpana o imieniu Miguel Dichoso. Czy możesz mi powiedzieć, jak znaleźć Diego de Montoya? Chciałbym z nim porozmawiać o Dichoso.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Jesteś pewien, że będzie chciał z tobą rozmawiać, mój synu? Nie sądzę, chyba że użyjesz szpady i pistoletu.";
			link.l1 = "Czyżby Twoje nazwisko mogło go uczynić bardziej uległym?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Och, "+pchar.name+". Wątpię, by człowiek przysięgły Don Mendozy zechciał dojść do porozumienia z tobą. Wydanie mu rozkazu przybycia do San Diego na przesłuchanie ze mną może być opcją, ale nie jestem pewien, czy Diego byłby wobec mnie całkowicie szczery.";
			link.l1 = "Jakie kroki powinniśmy teraz podjąć, Ojcze?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Zostaw mnie na chwilę, synu. Muszę przetrawić to, co mi powiedziałeś i zebrać wszystkie fakty, które już znam z różnych źródeł. Potem powiem ci, jaki będzie nasz następny krok. Wpadnij później.";
			link.l1 = "Tak, Wasza Łaskawość. Zrobię to. Będę sprawdzał okresowo...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Niech cię Bóg błogosławi, mój synu... Co mogę dla ciebie zrobić?";
			link.l1 = "Czy masz jakieś wieści, Wasza Ekscelencjo?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Nie w tej chwili, mój synu. Nie trać jednak nadziei. Moi ludzie i ja nad tym pracujemy. Wpadnij później.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Tak, mój synu. Mam pewne informacje o Miguelu Dichoso. Nie na darmo wierzyłem, że Dichoso wciąż żyje i jest na Karaibach. Wygląda na to, że Don Diego de Montoya miał rację. Otrzymaliśmy dowód od człowieka, który znał Miguela Dichoso z twarzy, że zaginiony dżentelmen był widziany w osadzie pirackiej Le Francois na Martynice w kwietniu 1654 roku po zniknięciu Santa Quiteria...";
			link.l1 = "Więc fregata rozbiła się na brzegach Martyniki?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Zwolnij, mój synu. Nie mamy teraz żadnych informacji o jakimkolwiek wraku statku na Martynice w tamtym czasie. A fregata to nie lugger. Jej zniszczenie z pewnością przyciągnęłoby uwagę i stworzyło ogromną okazję do ratowania dla miejscowych padlinożerców.";
			link.l1 = "Czy warto przeszukać wybrzeże i plaże, aby znaleźć to, co pozostało z okrętu?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Mój syn, Don Diego de Montoya, już to wszystko zrobił bez rezultatu. Słuchaj dalej. Moje źródła w Providence donoszą, że baron jest pewien, iż Santa Quiteria wciąż pływa po Karaibach, choć pod inną nazwą.\nDlatego tak desperacko poluje na Miguela Dichoso. Według jego słów, Santa Quiteria była widziana niedaleko Isla Tesoro i ostatnio była widziana pod angielską banderą w towarzystwie eskadry wojskowej.";
			link.l1 = "Co? To niewiarygodne. Mówili, że przetrwać burzę takiego kalibru byłoby niemożliwe... A teraz Santa Quiteria nie tylko przetrwała, ale pływa pod angielską banderą? Te dwa fakty się nie zgadzają. Co skłoniło barona do uznania, że to była Santa Quiteria? Czy naprawdę jest takim wyjątkowym statkiem?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "O tak. Ta fregata została zbudowana przy użyciu najnowszych technik w Europie. Jest bardzo dobrze uzbrojona jak na swoją klasę, a jej szybkość pozwala jej wyprzedzić wszystko, co mogłoby ją przebić w uzbrojeniu. Tak powiedziało mi moje źródło.";
			link.l1 = "A teraz nazywa się, jeśli nie Santa Quiteria?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Niestety, tego nie wiem... Idź na Isla Tesoro, "+pchar.name+", i spróbuj dowiedzieć się czegoś o fregacie Dichoso. Może uda nam się w ten sposób znaleźć jej byłego kapitana, dwa ptaki jednym kamieniem. Albo dwie szczury jedną pułapką.";
			link.l1 = "Uważaj to za załatwione, Wasza Ekscelencjo!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Cieszę się, że zdecydowałeś się mnie odwiedzić, synu.";
			link.l1 = "Witaj, Wasza Ekscelencjo. Po spotkaniu z Donem Alonsem de Maldonado nawet nie pomyślałem, że jeszcze kiedyś Cię zobaczę.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado złamał moje bezpośrednie rozkazy. Surowo zabroniłem mu konfrontacji z tobą, mój synu, wiedziałem, jak to się dla niego skończy. I to, co przewidziałem, stało się prawdą. Jego misją było eskortowanie cię do Tayasal, ponieważ był tam wcześniej. Na dodatek, jego eskadra i kompania hiszpańskich żołnierzy miały cię bronić przed atakami Itza lub Mosquito. Alonso działał niegodnie, kierowany samolubną chęcią zemsty. Nie tylko zawiódł ekspedycję do Tayasal i skazał powierzonych mu żołnierzy i statki, ale również zasiał nasiona nieufności i urazy wobec mnie w twoim sercu. Zapewniam cię, mój synu, jestem całkowicie po twojej stronie. Musimy razem stawić czoła tej obecnej ciemności.";
			link.l1 = "Chciałbym w to uwierzyć.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Spokojnie, "+pchar.name+". Ja, lojalny i oddany sługa naszego Pana i Zbawiciela Jezusa Chrystusa oraz przedstawiciel Jego Kościoła, kieruję się jednym celem: powstrzymać koniec świata, aby wszystkie dusze miały szansę usłyszeć słowo Naszego Błogosławionego Pana. A to oznacza powstrzymanie diabelskiego agenta, który obecnie znajduje się w rękach opętanego przez demona Indianina. Podejrzewałem to od razu i dopiero teraz jestem całkowicie pewien. Zostałeś wybrany przez Pana jako Jego mistrz w walce przeciwko Szatanowi.";
			link.l1 = "Ale co sprawia, że tak mówisz, Ojcze?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Udało ci się dokonać czegoś, czego ani ja z pomocą wszystkich moich agentów, ani baron Mendosa i Don Diego, ani nikt inny nie był w stanie dokonać. Udało ci się znaleźć przeklętą wyspę i odnaleźć na niej artefakt K'uk'ulkan'a. Czyż nie?";
			link.l1 = "Tak, mam maskę K'uk'ulkan.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "I czy twierdzisz, że to wszystko wydarzyło się przypadkowo? Przez zbieg okoliczności? 'Serce człowieka planuje jego drogę, lecz Pan kieruje jego krokami.' Mój synu, Wszechmogący poprowadził cię tą ścieżką! Wzmocnił twoją rękę w bitwie, skierował twoje stopy na właściwą drogę i chronił cię w czasach niebezpieczeństwa! 'Oto miecz Pana zstępuje na sąd nad Edomem, nad ludem, który przeznaczyłem do zniszczenia!'";
			link.l1 = "Ykhm... Ojcze, ale misja została już praktycznie wykonana. Mam maskę. Czyż to nie znaczy, że opętana powłoka Kukulkana nie może wejść do naszej historii i jej zmienić...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Jesteś w błędzie, mój synu. Demon może przejść przez tę bramę, niezależnie od tego, czy ma tę maskę, czy nie. Maska jedynie ułatwia mu wykonywanie jego mrocznych czynów. Jedyną rzeczą, która może go powstrzymać, jest całkowite zniszczenie piekielnych bram.";
			link.l1 = "Don Alonso powiedział mi to samo...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "I miał rację! W imię naszego Pana Jezusa Chrystusa i Jego Błogosławionej Matki, wzywam cię, byś podjął Krzyż przeciwko temu złu, mój synu! Nie możesz odmówić wielkiego zadania, które zostało ci powierzone. Ja i całe chrześcijaństwo polegają na tobie, mój synu.";
			link.l1 = "Wasza Ekscelencjo, to zbyt wiele. Naprawdę czuję się... dość niezręcznie...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Twoja skromność jest urocza, mój synu, ale to nie czas na udawanie zawstydzonej dziewicy. Nie bądź tchórzem ani nie lękaj się, bo Pan, twój Bóg, idzie przed tobą, by dać ci zwycięstwo! Wejdź do tej bitwy dla swoich bliskich, dla wszystkich chrześcijan... a jeśli nie dla nich, to dla siebie samego, bo jeśli ten demon zwycięży, zginiesz wraz z innymi.";
			link.l1 = "Przypuszczam, że mnie przekonałeś, Ojcze. Waham się co do mojej sytuacji, by wyruszyć na wyprawę do Tayasal, ale teraz nie mam już żadnych wątpliwości. W czym możesz mi pomóc?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Tylko dwóch ludzi wiedziało, jak dotrzeć do Tayasal: Alonso de Maldonado i Miguel Dichoso. Don Alonso już nie żyje. A Dichoso... Powiedziano mi, że niedawno widziano go w Sharptown na Isla Tesoro. Być może wciąż tam jest. Musisz odnaleźć Dichoso i przekonać go, by został twoim przewodnikiem.\nPrzez złoto lub siłę, musisz sprawić, by ten człowiek zaprowadził cię do Tayasal. Tam znajdziesz bramy piekła i tam je zapieczętujesz.";
			link.l1 = "A co z mężczyznami?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Ostatnia kompania żołnierzy, którą miałem, była pod dowództwem Alonso de Maldonado. Niestety, nie mam już szansy zebrać kolejnego oddziału hiszpańskich żołnierzy. Wyczerpałem cały mój autorytet w lokalnym garnizonie. Będziesz musiał to zrobić z pomocą swoich własnych ludzi, mój synu. Ale dam ci tyle pomocy, ile mogę w każdej innej sprawie.";
			link.l1 = "Jakiego rodzaju pomoc?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Musimy wykorzystać każdą przewagę, jaką mamy w tej walce, zarówno materialną, jak i duchową. Poprosiłem ojca Adriana, aby dołączył do mnie tutaj w tej kaplicy za pięć dni. Przywiezie ze sobą święte amulety dla ciebie. Amulety, które mogą wspomóc wojowników Chrystusa w bitwie. Dostarczy ci także wszelkiego rodzaju mikstury. Co do mnie, przyjmij ten miecz, mój synu.\nTo jest starożytny miecz Templariuszy, potężna broń naszych przodków. Wciąż ostry, lśniący błogosławieństwem Kościoła. Tylko najwięksi rycerze mieli zaszczyt nim władać. Weź go, posiądź z dumą i miażdż wrogów naszej Wiary z imieniem Jezusa Chrystusa na ustach!";
			link.l1 = "Dziękuję! Ten miecz jest absolutnie niesamowity. Brak mi słów...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("Otrzymałeś Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "Niech cię Bóg błogosławi, "+GetFullName(pchar)+", w tej nadchodzącej bitwie. Przyozdabiam Cię Świętym Krzyżem. Wszechmogący Boże, w którego ręku spoczywa zwycięstwo i który dałeś Dawidowi cudowną siłę, by zmiażdżyć Goliata: pokornie prosimy Cię o Twoje miłosierdzie, abyś pobłogosławił tę broń swoim życiodajnym miłosierdziem; i udzielił Twojemu słudze "+GetFullName(pchar)+" kto chce je znieść, aby mógł ich swobodnie i zwycięsko użyć do obrony Świętej Matki Kościoła przed atakami wszystkich wrogów widzialnych i niewidzialnych. Przez Chrystusa, Pana naszego. Amen.";
			link.l1 = "Amen!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "I teraz idź, mój synu. Niech Bóg nad tobą czuwa, niech cię nigdy nie opuszcza, ani w poszukiwaniach, ani na twej drodze, ani w bitwie. Znajdź Miguela Dichoso i udaj się do Tayasal z jego pomocą. Nie zapomnij o ojcu Adrianie, wyposaży cię w amulety i lekarstwa, które mogą ci się przydać. A teraz czas, abym wrócił do Santiago. Żegnaj, mój synu. Vaya con Dios.";
			link.l1 = "Żegnaj, ojcze Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
