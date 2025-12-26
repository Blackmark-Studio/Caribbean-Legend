void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Czegoś pan chciał?";
			link.l1 = "Nie, nic takiego.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Kogo my tu mamy! Sam "+GetTitle(NPChar,true)+" "+pchar.lastname+" we własnej osobie!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Ciebie to się tu nie spodziewałem... Ba, nawet nie sądziłem, że jeszcze żyjesz!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "Nie wierzę własnym oczom... Przystojniak? Ale... jak?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ha-ha! No toś się pomylił. Jak widzisz – żyję i mam się dobrze. Właśnie postanowiłem sprawić sobie 'czyściutki' stateczek. A ty... opowiadaj: jak to się stało, że tak skończyłeś, co, przyjacielu?";
			  }
			  else 
			  {
				dialog.text = "Ha-ha! No to się pomyliłeś. Jak widzisz – żyję i mam się świetnie. Właśnie postanowiłem sprawić sobie 'czyściutki' stateczek. A ty... opowiadaj: co cię tu sprowadza, przyjacielu?";
			  }
			link.l1 = "Nie tutaj. Chodźmy do tawerny – sprawy mogą poczekać.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Ciii... Nie krzycz tak. Przystojniak to już przeszłość, podobnie jak, jak sądzę, Książę. Prawda?";
			link.l1 = "Ale przecież widziałem to na własne oczy...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "Jak mnie wykończyli? Lepiej by było, gdyby tak się stało, przyjacielu. Uwierz mi.";
			link.l1 = "Chodźmy do tawerny. Opowiesz mi wszystko.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Więc to pan jest nowym właścicielem pinasy '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Ja. "+GetFullName(npchar)+", skoro już tak bardzo chcecie wiedzieć. A wy kim jesteście?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", i chciałbym odkupić od was ten statek.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Oczywiście, oczywiście, słyszałem już o tym. Myślałem, że już dawno pozbyłem się wszystkich chętnych na ten statek. Niestety muszę cię rozczarować, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"' teraz mój, i już niedługo wypływam nim do Bordeaux. Nie po to zająłem się handlem, żeby od razu zrywać pierwszą transakcję. To zły znak, wie pan.";
			link.l1 = "Bordeaux, powiadacie? Ciekawe... Może będę miała dla was korzystną propozycję. Może omówimy to przy kuflu rumu?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "Nie mam w zwyczaju odmawiać ani rumu, ani korzystnych propozycji. Chodźmy.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "No to, za ciebie, "+GetTitle(npchar,false)+" "+pchar.lastname+". Wiedziałem, że taki facet jak ty nie będzie długo biegał na posyłki u Tiraxa. Ale że zostaniesz taką ważną osobistością... potrafisz zaskoczyć, do diabła.";
				link.l1 = "Ha-ha. Kto by to mówił. Więc postanowiłeś zostać kupcem?";
			  }
			  else 
			  {
				dialog.text = "Za spotkanie! Czułem w kościach, że jeszcze się zobaczymy.";
				link.l1 = "Ha-ha. Za nią! Czyli postanowiłeś zostać kupcem?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "No przecież nie będę całe życie ryzykował gardła za parę dubloonów. Posmarowałem komu trzeba, zamknąłem usta komu nie trzeba – i proszę: nie jestem już złodziejem ani piratem, tylko szanowanym kupcem.";
			link.l1 = "No proszę, niezły zwrot akcji. Teraz nawet nie wiem, jak zaproponować ci to, co zamierzałem zaproponować świeżo upieczonemu kapitanowi pinasy '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Daj spokój, mów jak jest. Znamy się przecież od wieków.";
			link.l1 = "Widzisz... przybyłem tu, na Karaiby, na pinasie, który to ty wykupiłeś. Kiedy dowiedziałem się, że wystawiono go na aukcję, chciałem go odkupić – i wrócić na nim do domu, do Francji.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ha-ha-ha-ha! Poczekaj... ach-ha-ha-ha-ha-ha!..";
			link.l1 = "No i co w tym śmiesznego?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "A ledwie wygrałem licytację, podszedł do mnie elegant – młody, zadbany: mówi, zabierz mnie, uprzejmy panie, razem z moimi rzeczami do Bordeaux, za dobrą monetę. A co tam monetę – cały cholerny worek monet.";
			link.l1 = "Tak? Ha, ha. Naprawdę zabawne. I co zrobiłeś? Zgodziłeś się?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", no przecież nie jestem głupcem, żeby odmawiać góry złota za zwykłą przeprawę przez Atlantyk. Tak, będę musiał przez parę miesięcy chrupać suchary i żuć solone mięso. Ale wiesz, zdarzało mi się ryzykować własną skórą za dużo mniejsze pieniądze. Więc oczywiście, wchodzę w to.";
			link.l1 = "W takim razie mogę ci zaproponować to samo. Odwieź mnie do Bordeaux – a dostaniesz taką samą górę monet.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Jesteś gotów zostać pasażerem? Przecież znasz nasze zasady – na statku jest tylko jeden kapitan. A na moim statku – to ja.";
			link.l1 = "Dlaczego nie? Odetchnę, zastanowię się nad życiem. Może rzeczywiście powinienem się ustatkować, osiąść gdzieś na stałe. Teraz trudno mi to sobie wyobrazić, ale może to ma sens. Nawet ty postanowiłeś trzymać się z dala od walk.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ach, gdybym miał taką piękną żonę jak ty, może sam rzuciłbym morze, osiadł gdzieś na uboczu: dom bym postawił, winem pohandlował. Na życie nie narzekam – odkąd wyciągnąłeś mnie z łap Hiszpanów, nie traciłem czasu.";
			}
			else
			{
				dialog.text = "Eh, gdybym miał taką piękną żonę jak ty, może i sam rzuciłbym morze, osiadł gdzieś na uboczu: dom bym postawił, winem pohandlował. A i żyć byłoby za co – wdówka po plantatorze miała niezły spadek.";
			}
			link.l1 = "Żona! Do diabła, "+npchar.name+", przecież jeszcze z nią o tym nie rozmawiałem.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "Na to masz jeszcze mnóstwo czasu. Muszę porządnie wyposażyć swoją łajbę. Jak już uporasz się ze wszystkimi sprawami – ruszaj tu ze swoim tyłkiem. Urządzimy ucztę przed wypłynięciem.";
			link.l1 = "To mi się podoba! Nie martw się, długo czekać nie będziesz.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ach, gdybym miał żonę, może sam rzuciłbym morze, osiadł gdzieś na uboczu: postawiłbym dom i handlował winem. Ale póki co... morze to mój dom.";
			link.l1 = "Winem z moich plantacji, ha-ha! W Bordeaux, "+npchar.name+", takie dziewczyny to prawdziwy skarb! Może i sobie tam kogoś wypatrzysz – w miłosnych sprawach są naprawdę niezłe. Wiesz co sobie pomyślałem? Przez najbliższe miesiące jedyne, co będziemy oglądać, to gęby twoich marynarzy. Przydałoby się przed wypłynięciem urządzić porządną zabawę w miejscowym burdelu.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "A wy, monsieur, dobrze wiecie, co zaproponować. Jak już uporasz się ze wszystkimi sprawami – rusz tu swój tyłek. A potem możemy zahaczyć o burdel, możesz być pewien.";
			link.l1 = "No dobrze, nie będę więc tracić czasu. Do dzieła!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "Za wolność!";
			link.l1 = "I za ciebie, Jean! Za twoje zmartwychwstanie! Wciąż nie mogę w to uwierzyć. Jak?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "Wywlekli mnie z pola bitwy – ledwo żywego, całego we krwi od stóp do głów. Wrzucili do baraku i zostawili tam na pewną śmierć, jak padlinę. Wśród niewolników był całkiem sprytny chłopak – Moko. To on uratował mi skórę: zacisnął ranę kawałkiem mojej koszuli, dał mi się napić.";
			link.l1 = "Chcesz powiedzieć, że Hiszpanie zostawili cię przy życiu po tym wszystkim?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Jak widzisz. Ale nie z dobroci serca. Chcieli zemsty – przesłuchań, tortur. Palili, bili, cięli. Grozili, że wypalą mi oczy – wyłącznie z wielkiej miłości do mnie. Ale wtedy ktoś rozpuścił plotkę, że piraci szykują się mnie pomścić i już ostrzą noże. Właściciel plantacji aż dostał tiki w oku. Nie czekał na wizytę naszych braci i czym prędzej uciekł do swoich posiadłości w Campeche. Nas z Moko i resztą zabrał ze sobą, żeby nie zostało świadków. Pozostałym ogłosili, że zszedłem – i na tym postawili krzyż.";
			link.l1 = "I co dalej? Jak udało ci się odzyskać wolność? I jak, do diabła, znalazłeś się tutaj?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "Szczęście, przyjacielu. Ślepe, brudne szczęście. Trafiłem na plantację – i tortury trwały dalej. Ten drań postanowił rozkoszować się każdą sekundą moich cierpień, ale z każdym dniem coraz bardziej słabł... aż w końcu zdechł na gorączkę. Potem już nikogo nie obchodziłem. Wyrzucili mnie na pole jak bydło, nie szczędząc razów batem.";
			link.l1 = "Wciąż nie rozumiem, jak udało ci się stamtąd wydostać?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Słyszałeś o Christopherze Myngsie?";
			link.l1 = "Alonso coś wspominał... Najazd na Campeche! Nieźle wtedy urządzili tych Hiszpanów. To oni cię wtedy uwolnili?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Nie do końca. Sami się uwolniliśmy. Gdy straż walczyła z oddziałem angielsko-bukanierów, razem z Moko znaleźliśmy dziurę w dachu baraku i wznieciliśmy bunt. Przejęliśmy arsenał i skarbiec żony świętej pamięci drania-plantatora.";
			link.l1 = "Skarbiec?! Tego się nie spodziewałem.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "Nie zastanawialiśmy się długo – z bronią i zapasami ruszyliśmy w dżunglę. Dwa dni przedzieraliśmy się przez gęstwinę, aż trafiliśmy do wioski Indian Can Pech. Ich szaman dla pozoru słuchał Hiszpanów, ale nie pałał do nich sympatią. Moko szybko się z nim dogadał – przyjęli nas w zamian za połowę naszego arsenału i pomoc w wojnie z kimkolwiek. Tak właśnie spędziłem tam półtora roku.";
			link.l1 = "Ty, Jean, nie jesteś już tym, kim byłeś kiedyś. Od teraz jesteś Szczęściarzem.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ha-ha. Nie mam nic przeciwko. No a potem do naszego Batabille’a zawitał francuski kaznodzieja. Od razu zrozumieliśmy: to szansa, żeby wydostać się stamtąd nie w kajdanach. Przekupiliśmy jego eskortę – i wkrótce już płynęliśmy na Tortugę.\nA dalej, jak się pewnie domyślasz, postanowiłem już więcej nie igrać ze śmiercią. Zerwałem ze starym fachem... i przy okazji kupiłem "+GetShipName("Ulysse")+".\n"+"A ty? Jak to się stało, że tak skończyłeś? Wiedziałem, że taki zawadiaka jak ty nie wytrzyma długo na posyłkach u Tiraxa. Ale żebyś został taką szychą... potrafisz zaskoczyć, do diabła.";
			link.l1 = "Ha-ha. Kto by mówił. Więc postanowiłeś zostać kupcem?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "Za tych, którzy są na morzu!";
			link.l1 = "I za panią Fortunę!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "No dobrze, do rzeczy. Co chcieliście mi zaproponować?";
			link.l1 = "Wyruszacie do Bordeaux... Wiecie, ja również tam się udaję.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Chcecie, żebym zabrała was na pokład? Z tego co wiem, powinniście mieć własny statek. A może nawet całą flotyllę. A jednak postanowiliście popłynąć cudzym okrętem. Dobrze rozumiem?";
			link.l1 = "Dokładnie tak. Ostatnie wydarzenia sprawiły, że zacząłem się zastanawiać: może nadszedł czas, by rzucić kotwicę, ustatkować się... Myślę, że rola zwykłego pasażera na twoim statku pozwoli mi zrozumieć, czy potrafię przyjąć nowy rytm życia.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hmm... Czyli zmęczyło cię już ryzykowanie karkiem bez sensu? Znam to uczucie. Sam też... Zresztą, nieważne. Miejsce na statku się dla ciebie znajdzie, nawet dla całej twojej świty. Rejs już opłacił pewien młody fircyk – i to on płaci za pośpiech, więc nie będę ładował ładowni. Co do zapłaty...";
			link.l1 = "Nie martw się, kapitanie. Nie ustępuję hojnością twojemu pracodawcy i jestem gotów zapłacić tę samą sumę.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Wyśmienicie! W takim razie przybijamy targ?";
			link.l1 = "Przybito! Za to trzeba się napić!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Tak, rum pierwsza klasa... Potrzebuję dwóch tygodni – żeby doprowadzić statek do porządku i zaopatrzyć się we wszystko, co trzeba. Potem możemy ruszać.";
			link.l1 = "W takim razie spotkajmy się tutaj za dwa tygodnie. No, do zobaczenia, kapitanie.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "No i co, przyjacielu, załatwiłeś już swoje sprawy? Pokażemy tej zbieraninie, jak się naprawdę bawi?";
				link.l1 = "Jeszcze nie czas, "+npchar.name+", mam jeszcze parę spraw do załatwienia.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Kapitánie, jesteś już gotowy, by wejść na pokład?";
				link.l1 = "Niestety, kolego, mam jeszcze trochę spraw do załatwienia.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "Hej, karczmarzu! Wszystkim postaw kolejkę na mój koszt! I nie byle co, tylko to, co masz najlepszego!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "Za nas, przyjacielu. Za słony wiatr, za bezkresne morze i za horyzont – wiecznie kuszący, wiecznie nieosiągalny...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", kochanie, chcę z tobą porozmawiać o moim ojcu.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "Co się stało, kochanie? Mam nadzieję, że wszystko z nim w porządku, tak?";
			link.l1 = "No, nie tak dobrze, jak by się chciało. Są powody sądzić, że nie pożyje już długo, i bardzo go niepokoi myśl, że może mnie nie zobaczyć, zanim odejdzie w ostatnią drogę.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Wiem, moja droga, wiem... Ale takie jest życie. Chciałbym, żebyście się poznali. Niech zobaczy, jaką mam niezwykłą żonę, i da nam swoje błogosławieństwo.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "A co, jeśli mu się nie spodobam, tak, co nie? Przecież nie jestem z arystokratycznej rodziny...";
			link.l1 = "Głupoty, "+npchar.name+", no jak możesz mu się nie spodobać? Jesteś przecież cudem! Skoro zdobyłaś moje serce – zdobędziesz i jego.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Naprawdę tak myślisz, kochanie? W takim razie musimy jak najszybciej do niego ruszyć.";
			link.l1 = "Właśnie to zamierzam zrobić. Nawet znalazłem nam statek. Wypływamy za dwa tygodnie.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "Statek? Popłyniemy nie naszym okrętem?";
			link.l1 = "Nie, kochanie. Popłyniemy pinasą '"+GetShipName("Ulysse")+"'. To na nim przybyłem na Karaiby – i na nim je opuszczę.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "A ty nie będziesz kapitanem?";
			link.l1 = "Prędzej czy później i tak musiałabym zrezygnować z tej roli. Mam nadzieję, że to tylko na chwilę. Ale w każdym razie nie zaszkodzi mi poczuć, co czeka mnie w przyszłości.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "A co z naszymi oficerami? Przecież nie zabierzemy ich wszystkich ze sobą. I raczej nie będą tu na ciebie czekać.";
			link.l1 = "Ekhm... Tak, masz rację. Będę musiał porozmawiać z każdym z nich i pewnie pożegnać się na zawsze. Choć to nie będzie łatwe – biorąc pod uwagę, przez co razem przeszliśmy.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Może warto zorganizować na pożegnanie małą ucztę w tawernie?";
			link.l1 = "Też o tym myślałem, kochanie. Wiesz... chyba masz rację. To naprawdę dobry pomysł.";
			link.l1.go = "exit";
			link.l2 = "Nie sądzę, żeby to był dobry pomysł. Obejdziemy się bez hucznych pożegnań... Tak chyba będzie lepiej dla wszystkich. Chyba że zaprosimy tylko najwierniejszych przyjaciół...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Kochana, chciałbym porozmawiać z tobą o moim ojcu.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Oczywiście, "+pchar.name+". Mam nadzieję, że wszystko z nim w porządku?";
			link.l1 = "Nie do końca. Od dawna choruje i, obawiam się, wkrótce choroba weźmie górę... Ojciec znosi to wszystko z wielką odwagą. Jedyna rzecz, która naprawdę go niepokoi – że może już mnie nie zobaczyć. Chcę go odwiedzić... i przedstawić cię jemu. Uzyskać jego błogosławieństwo na nasze małżeństwo.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Będę szczęśliwa, mogąc go poznać, kochanie. Kiedy wypływamy?";
			link.l1 = "Za dwa tygodnie. Ale to jeszcze nie wszystko. Nie popłyniemy naszym statkiem. Do Starego Świata zabierze nas pinas '"+GetShipName("Ulysse")+"' - ten sam, który kiedyś mnie tu przywiózł.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", ale przecież zmieniać statek tuż przed długim rejsem to zły omen.";
			link.l1 = "Nie będziemy zmieniać statku, kochanie. Będziemy pasażerami.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Ale... kochanie, nie rozumiem...";
			link.l1 = "Tak trzeba, "+npchar.name+". Prędzej czy później będę musiała zrezygnować ze stanowiska kapitana. I chcę z góry wiedzieć, z jakimi uczuciami będę musiała się zmierzyć.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Skoro tak postanowiłeś... Ale co z naszymi oficerami? Przecież nie zabierzemy ich wszystkich ze sobą. A i czekać tutaj na ciebie raczej nie będą.";
			link.l1 = "Ekhm... Tak, masz rację. Będę musiał porozmawiać z każdym z nich i pewnie pożegnać się na zawsze. Choć to nie będzie łatwe – biorąc pod uwagę wszystko, przez co razem przeszliśmy.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Może warto zorganizować na pożegnanie małą ucztę w tawernie?";
			link.l1 = "Też o tym myślałem, kochanie. Wiesz... chyba tak zrobimy. To naprawdę dobry pomysł.";
			link.l1.go = "exit";
			link.l2 = "Nie sądzę, żeby to był dobry pomysł. Obejdziemy się bez hucznych pożegnań... Tak chyba będzie lepiej dla wszystkich. Chyba że zaprosimy tylko najwierniejszych przyjaciół...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Kapitanie... Już rozmawiałem z karczmarzem – przygotował najlepszy trunek, jaki ma. Kiedy zaczynamy?";
				link.l1 = "Już teraz! Hej, karczmarzu! Dla wszystkich napitki na mój koszt!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Kapitánie, obiecałeś mi opowiedzieć, jak dowiedziałeś się o 'Ulissesie'.";
				link.l1 = "Pamiętam, pamiętam. Hej, karczmarzu! Najlepszy rum na ten stół.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Za wcześnie, "+npchar.name+". Mam jeszcze pilne sprawy.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "No to co, przyjacielu, wołaj resztę – pokażemy Saint-Pierre, jak bawią się prawdziwi wilki morskie!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ha-ha! Kapitanie, nie uwierzycie – już ich zawołałem!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "Za nas, "+npchar.name+"Za panią Fortunę i za wiatr, który napełnia nasze żagle!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "No i niezłą rozróbę tu zrobiliśmy, kapitanie. Ha-ha. Wygląda na to, że przed całkowitą ruiną tawernę uratowały tylko skromne zapasy rumu u karczmarza.";
			link.l1 = "Nie przypominaj, "+npchar.name+", dopiero teraz trochę mi ulżyło.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Jak pan każe, panie "+pchar.lastname+". Ha-ha. Za to pożegnaliśmy się z Martyniką po królewsku. Tam jeszcze długo będą wspominać wasz wyjazd.";
			link.l1 = "Wydaje mi się, że trochę przesadziliśmy, kiedy wsadziliśmy karczmarza do łodzi i wysłaliśmy go po trunki do Le François.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ha, ha, ha. Nie martwcie się o niego. Przez te dni zdobył tyle złota, że mógłby kupić plantację, a do tego jeszcze tytuł szlachecki.";
				}
			else
				{
					dialog.text = "Ha, ha, ha. O niego się nie martwcie. W ostatnich dniach zdobył tyle złota, że mógłby kupić plantację, a nawet tytuł szlachecki w dodatku. Szkoda tylko, że nie porozmawialiście z żadnym z oficerów. Będzie nam ich brakować.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Chyba, "+sld.name+" wciąż jest na ciebie zła za to, że zniknąłeś na pół nocy.";
			}
			else
			{
				dialog.text = "Ale z tym kupcem… tam to już, kapitanie, naprawdę przesadziliście.";
			}
			link.l1 = "Cholera, i po co nam było z Jeanem pchać się do tego miejscowego sklepu…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "I jak was w ogóle nie złapali? Ale by było śmiechu - "+GetTitle(PChar,true)+" złapany na próbie kradzieży kilku butelek wina.";
			link.l1 = "Śmieszy cię to, "+npchar.name+", a ja nawet połowy tego nie pamiętam. Ostatni raz tak się upiłem... właściwie... właściwie nigdy.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "No to zaczynamy, kapitanie. Ha, ha. Podobało mi się. Chętnie bym to powtórzył. Kiedy, mówisz, wracamy?";
			link.l1 = "Lepiej idź sprawdź, co z naszymi rzeczami. Na pewno wszystko zabraliśmy? Zejdę później – powietrze w ładowni na pewno mi teraz nie posłuży.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Spójrz tylko na to... nieźle zatrzęsło tym statkiem.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "Tu przecież jest cała cholerna góra złota, kapitanie!";
			link.l1 = "Widzę, "+npchar.name+". Trzeba to wszystko szybko schować do skrzyń, zanim załoga zobaczy. Takie pokusy są im niepotrzebne.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "Nie, nie powstrzymam się...";
			link.l1 = "Co?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "Hej, co ty robisz?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "No to wstawaj. Znalazłeś sobie czas...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Dołącz do nas, kapitanie.";
			link.l1 = "Wstawaj, przestań się wygłupiać.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = " No rozluźnij się. Musisz to poczuć. ";
			link.l1 = "Dobra, niech ci będzie. No, przesuń się.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "Zawsze o tym marzyłem...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Wspaniałe uczucie, prawda, kapitanie?";
			link.l1 = "Ha, ha, ha. Tak to odwiedziłem Karaiby – tylko żeby dowiedzieć się, co u braciszka. Ojciec na pewno nie spodziewał się takiego obrotu spraw. Ha, ha!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Panie "+GetTitle(NPChar,false)+" "+pchar.lastname+"... Ha-ha!  Pamiętasz, jaki byłeś, kiedy przybyłeś na archipelag?";
			link.l1 = "Jakżebym nie pamiętał. Ha, ha. Aż trudno uwierzyć, że kiedyś byłem takim samym fircykiem, jak ten, który teraz przechadza się po pokładzie. Tyle się tu przeżyło, na tych przeklętych Karaibach… Intrygi, nieumarli, braciszek Kukulkan…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Ma pan piekielne szczęście, kapitanie. Dorobić się takiego majątku i jeszcze wyjść z tego cało… nie każdemu się to udaje.";
			link.l1 = "No dobra. Wystarczy już się obijać. Jeszcze chwila i ktoś naprawdę nas zauważy.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Słuchaj, przyjacielu, nie podoba mi się zabezpieczenie kabestanu na tym statku. Jest stanowczo za mało pewne. Jeszcze ktoś przypadkiem je zerwie.";
			}
			else
			{
				link.l1 = "Posłuchaj, kapitanie, nie podoba mi się zabezpieczenie kabestanu na tym statku. Zbyt jest ono zawodne. Jeszcze ktoś przypadkiem je zerwie.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Daj spokój, "+pchar.name+", na statku każdy wie, że…";
			}
			else
			{
				dialog.text = "Daj spokój, kapitanie. Komu by to przyszło do głowy...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Hej, ty, gamoniu... Co ty, do diabła, wyprawiasz? Nie nauczyli cię, żeby nie wtykać swoich krzywych gir tam, gdzie nie trzeba?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Spokojnie, nie zapominaj się! Jestem szlachcicem i nie pozwolę sobie na takie traktowanie…";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "Na moim statku jesteś nikim. Moi marynarze mają tu więcej praw niż ty. Więc albo siedzisz cicho i nikomu nie przeszkadzasz, albo sam cię wyrzucę za burtę.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ha, ha, ha. Jakbym spojrzał na siebie z boku.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "O czym mówisz?";
				link.l1 = "Tak, nieważne, "+npchar.name+". Nie bądź taki surowy dla naszego pasażera. To dla niego wszystko jeszcze nowe. W końcu my też nie od razu staliśmy się wilkami morskimi.";
			}
			else
			{
				dialog.text = "O czym mówicie?";
				link.l1 = "Nie przywiązujcie do tego wagi, "+npchar.name+". I nie oceniajcie zbyt surowo waszego pasażera. To dla niego wszystko nowe. W końcu my też nie od razu staliśmy się wilkami morskimi.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "Z takim talentem prędzej się o kabestan powiesi, niż zostanie marynarzem. Trzeba mieć wyobraźnię...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Kto wie, kto wie. Przybyłem na archipelag równie beztroski, ciekawski i zarozumiały jak wtedy, gdy byłem młodym chłopakiem.";
			}
			else
			{
				link.l1 = "Kto wie. Kiedy przybyłem na archipelag, byłem takim samym beztroskim, ciekawskim i zarozumiałym młokosem.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Też mi porównanie.\n"+"Poczekaj\n"+"Widzisz w nim siebie? Ha-ha-ha. To bierz go pod swoje skrzydła. Ja niańczyć się z nim nie zamierzam.";
				link.l1 = "Popilnuję go. Zanim zdążysz obedrzeć go ze skóry. Ale za kotwicę niech zapłaci co do grosza.";
			}
			else
			{
				dialog.text = "Więc zobaczyłeś w nim siebie? Ha-ha. No cóż, kapitanie, w takim razie bierz go pod swoją opiekę. Ja niańczyć się z nim nie zamierzam.";
				link.l1 = "Popilnuję go. Dopóki nie obedrzecie go ze skóry. Ale za kotwicę – niech zapłaci jak należy.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Rzucić kotwicę. Czekamy na wiatr. Trzymać dotychczasowy kurs.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Podnieść kotwicę. Łapiemy wiatr. Kurs – na północny wschód.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Podnieść kotwicę! Opuścić fok – złapiemy wiatr. Do roboty...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "Co robisz?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "Co robisz?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "Nie, co ty robisz?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh... Co ty robisz? Starszy marynarz powtarza rozkazy kapitana.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "No to starszy marynarz ich powtarza.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Odpuść sobie, Alonso. Jesteśmy tu tylko pasażerami. Zapomniałeś?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Ekhm... Przepraszam, kapitanie.   Nie mogłem się powstrzymać\nAle było warto.   Jakbym cofnął się w przeszłość.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Czego sobie życzycie?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "No i jak się czujesz, przyjacielu?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Przyznaj się, "+npchar.name+", przecież już wtedy, gdy postanowiłeś odłączyć się od Tyraksa, miałeś zamiar zostać kupcem?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Przyznaj się, "+npchar.name+", przecież już wtedy na plantacji planowałeś zostać kupcem?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Doskonale pamiętam, że próbował ze mną rozmawiać jakiś posłaniec. Ale za nic w świecie nie mogę sobie przypomnieć, w jakiej sprawie. Czy ty coś o tym wiesz?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Był już pan kiedyś w Bordeaux, kapitanie?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Kapitánie, szczerze mówiąc, nie bardzo pamiętam, jak opuściliśmy Martynikę. Miałem dostać ważną pocztę od pewnej osoby, ale wygląda na to, że jej nie otrzymałem. Czy ktoś zwracał się do was w tej sprawie?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Chyba pojawił się lekki wiaterek. Czas stawiać żagle. (Wypłynąć w morze)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Na razie nic. Pójdę.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ha-ha... Jak nigdy dotąd! Pełen sił i zdrowia.";
			link.l1 = "Naprawdę? A wyglądasz, jakby cię rekin przeżuł.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Kto by mówił. Sam wyglądasz jak zbity pies.";
			link.l1 = "I ja czuję się tak samo. Ha, ha. Do diabła, nawet nie pamiętam, kiedy i jak odbiliśmy od brzegu.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Eh, to była niezła biesiada. Tylko diabelnie droga. Moi głupcy prawie spalili burdel – musiałem wysupłać worek monet, żeby uciszyć skandal. Teraz te gamonie będą mi winni do końca życia\nNo i jak ci się podoba rola pasażera? Jeszcze nie zacząłeś wyć z tęsknoty?";
			link.l1 = "Mam wrażenie, jakbym już nie trzymał własnego losu w swoich rękach. A jednocześnie czuję dziwną ulgę. Jakbym zrzucił z ramion skrzynię z kulami armatnimi.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ha-ha. No dobrze, jeśli dopadnie cię tęsknota – zawsze możesz zostać moim oficerem.";
			link.l1 = "To bardzo wielkoduszne z twojej strony, ale muszę odmówić. Na całych Karaibach nie znajdzie się tyle rumu, żeby wystarczyło na nasze hulanki.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Nie do końca, przyjacielu. Taka myśl czasem mnie nachodziła, ale nie przywiązywałem do niej większej wagi. Wróciła do mnie po raz drugi, kiedy doszły mnie słuchy, że cała banda wiernych psów Tyraksa przepadła bez śladu. Wszyscy co do jednego – Tasak, Łysy, a nawet ten stary śmierdzący szmaciarz Leprechaun.\nNo a kiedy usłyszałem, jakie sukcesy odnosisz ty – postanowiłem w końcu, że mam już dość. Wiecznie ryzykować głową dla kilku monet – tak się nie da.\nZłota mam dość, żeby nigdy nie musieć płaszczyć się przed żadnym draniem w peruce. Ale rozstać się z morzem... na to nie byłem gotów. Więc postanowiłem zmienić fach.";
			} 
			else 
			{
				dialog.text = "Nie do końca, przyjacielu. Czasem nachodziła mnie taka myśl, ale nie przywiązywałem do niej większej wagi. Wróciła do mnie ponownie, kiedy doszły mnie słuchy, że cała banda wiernych psów Tyraksa zniknęła bez śladu. Wszyscy co do jednego – Tasak, Łysy, a nawet ten stary śmierdzący szmaciarz Leprechaun.\nNo a kiedy wrogie kule dwa razy w jednej bitwie prawie wybiły mi mózg z głowy – wtedy już postanowiłem, że mam dość. Wiecznie ryzykować głową za monety nie da się.\nZłota mam tyle, że nigdy nie będę musiał płaszczyć się przed żadnym draniem w peruce. Ale rozstać się z morzem... na to nie byłem gotów. Więc postanowiłem zmienić fach.";
			}
			link.l1 = "Maczeta, Łysy, Leprechaun... Wiesz, co się z nimi stało?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "Nie, nie wiem. I szczerze mówiąc – mam gdzieś, gdzie te łajzy się podziały. Choćby i do diabła.";
			link.l1 = "Mniej więcej tam właśnie ich wysłałem.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "To ty wykończyłeś całą ich kompanię? Nieźle! I Markus ci to wybaczył?";
			link.l1 = "On o tym nie wie. I najprawdopodobniej nigdy się nie dowie.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Więc, do diabła, dobrze zrobiłem, że ich wtedy zostawiłem, ha-ha. Ty, kto wie, może i mojej głowy byś nie oszczędził\nTylko jednego pojąć nie mogę – po co ci to wszystko było do cholery?";
			link.l1 = "Miałeś rację – za marne złoto te łotry gotowe są się udusić, zdradzić, zabić kogokolwiek. Zwabili nas do jednej z podziemi na Południowym Mainie, wciskając bajkę o niewyobrażalnych skarbach. To była starannie przygotowana pułapka, a te przeklęte tępe łby połknęły przynętę bez wahania. Zamiast podzielić łup po równo – uznali, że nie warto się dzielić, łatwiej będzie mnie zabić i zgarnąć wszystko dla siebie.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "I gówno im z tego wyszło, ha-ha! Poczekaj, a kto w ogóle zastawił tę pułapkę?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Pewien Zorro, hiszpański ludowy mściciel – zemsta za Kartagenę. Ten, kto przeżyłby tamtą rzeź, musiałby zostać w lochu na zawsze – wszystkie wyjścia były zamknięte. Ale temu draniowi się nie poszczęściło – mój oficer go przechytrzył.";
			}
			else
			{
				link.l1 = "Jakiś Zorro, hiszpański ludowy mściciel – zemsta za Kartagenę. Ten, kto przeżyłby tę piekielną rzeź, musiałby już na zawsze zostać w lochach – wszystkie wyjścia były szczelnie zamknięte. Udało mi się stamtąd wydostać. Ale zapłaciłem za to bardzo wysoką cenę.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "Przynajmniej przeżyłeś. I, jak sądzę, zgarnąłeś całe złoto, za które o mało nie przypłaciłeś własną skórą?";
			link.l1 = "Nie było tam żadnego złota. To był pozłacany ołów...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "Po tym wszystkim postanowiłem odejść od Tiraxa. Jesteś pierwszą osobą, której o tym mówię. No, nie licząc moich oficerów.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "Nie lubię mówić 'a nie mówiłem', ale... przecież ostrzegałem.";
			link.l1 = "Zatrzymywanie się w odpowiednim momencie to nie jest moja mocna strona. Więc będziesz musiał dać mi kilka lekcji.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Przecież mnie znasz – za parę kufli dobrego rumu opowiem ci nawet o swojej kryjówce ze złotem, he-he.";
			link.l1 = "A ode mnie takiej hojności się nie spodziewaj, ha-ha-ha. Wystarczy ci twoich własnych zapasów.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Wiadomo. Próbował ci wcisnąć jakieś listy – czy to od jakiegoś Bena, czy od Benedykta. Ale ty warknąłeś, że żadnego Bena nie znasz i zagroziłeś, że wyrzucisz go z tawerny, jeśli dalej będzie nam psuł zabawę.";
			link.l1 = "Diabli... Wygląda na to, że to były listy od opata Benoît. Ważne listy.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "No to dobrze, że je zabrałem. He-he.  Czułem w kościach, że ten szczeniak nie pomylił adresata. Trzymaj.";
			link.l1 = "Naprawdę mi pomogłeś, "+npchar.name+", dziękuję.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Jedno 'dziękuję' to za mało, przyjacielu. Stawiasz drinka – i to nie byle jakiego, tylko najlepszego, jaki można znaleźć w Bordeaux.";
			link.l1 = "Dostaniesz swoje, żebraku. Rum u nas, rzecz jasna, nie dorównuje temu z Karaibów, ale wino... Takiego to na pewno jeszcze nie piłeś.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Nie zdarzyło się...";
			link.l1 = "Zazdroszczę wam. Chciałbym jeszcze raz zobaczyć Bordeaux, tak jak za pierwszym razem. Pewnie wolicie rum, ale mimo wszystko polecam zajrzeć na targ winny przy ratuszu. Za nasz klaret znawcy na Karaibach są gotowi zapłacić fortunę.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Dziękuję za radę. Czy mogę zadać pytanie?";
			link.l1 = "Oczywiście.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "Jak to jest być pasażerem po tylu latach za sterem? Już się Pani przyzwyczaiła do nowej roli?";
			link.l1 = "Hmm... Nie opuszcza mnie wrażenie, że już nie trzymam własnego losu w swoich rękach. A jednocześnie czuję dziwną ulgę. Jakbym zrzucił z ramion skrzynię z kulami armatnimi. Myślę, że jeszcze za wcześnie na wnioski.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Biorąc pod uwagę to cholerne bezwietrze, w które tak szczęśliwie wpadliśmy, będziecie mieli czasu po uszy.";
			link.l1 = "W dobrym towarzystwie nawet cisza morska nie doskwiera. A do tego, kapitanie, muszę przyznać, że z towarzystwem naprawdę mi się poszczęściło.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Był. Posłaniec od jakiegoś opata. Ciągle zapominam oddać wam te listy. Proszę, oto one.";
			link.l1 = "Wyśmienicie. Bardzo mi pan pomógł, kapitanie. Dziękuję panu.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Masz rację.";}
			else {dialog.text = "Ma pan rację.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Wiatr z prawej burty! Postaw wszystko, od fokmasztu po bezan! Cała naprzód!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Znakomity klinga, "+GetTitle(NPChar,true)+". Pozwolicie zobaczyć?";
			link.l1 = "Może innym razem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "Kiedy wreszcie te klepsydry? Zaraz połknę własny język.";
			link.l1 = "Cierpliwości, marynarzu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Widzieliście, jaki szczur przebiegł? Przysięgam, w życiu nie widziałem tak wielkiego!";
			link.l1 = "No cóż...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "Co ja teraz pocznę, monsieur? Tak się upiłem, że nawet nie pamiętam, jak znalazłem się na tym statku. Przecież nie jestem żadnym marynarzem... A w domu czeka żona i dwójka dzieci.";
			link.l1 = "Trzeba było mniej pić. A teraz już za późno – zostaje ci zostać marynarzem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+".   To dla nas zaszczyt gościć was na pokładzie naszego statku.";
			link.l1 = "Jest pan bardzo uprzejmy, monsieur starszy marynarzu. Uprzejmość nie jest zbyt powszechną cechą wśród doświadczonych wilków morskich. Ale nie wprawiajmy załogi w zakłopotanie – nie jesteśmy przecież na dworze Jego Wysokości. Zwracaj się do mnie po prostu: kapitan.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "No, marynarzem zostałem całkiem niedawno. Wcześniej byłem pisarzem u pana Levassera. A kiedy jego… ekhm… usunęli, przyszedł nowy gubernator. W wąskich kręgach szybko rozeszła się wieść, jakim łajdakiem okazał się pan de René de Boisdufle de Lestre. Wtedy zrozumiałem: normalnej pracy już nie znajdę. Ludzie będą myśleć, że wszystko wiedziałem – i milczałem.";
			link.l1 = "A czy tak nie było?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Oczywiście, że nie. Nigdy nie miałem zwyczaju wtykać nosa w nie swoje sprawy. Poza tym, Levasseur surowo karał za ciekawość.";
			link.l1 = "W to chętnie uwierzę.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "Widzisz, kiedy się go pozbyłeś, zaciągnąłem się jako marynarz na pierwszy lepszy piracki statek. I, co dziwne, dość szybko się odnalazłem i zmieniłem. Nawet udało mi się zdobyć szacunek wśród największych zabijaków. Ale to, czym się zajmowali... Nie leżało mi to. Tak właśnie trafiłem tutaj.";
			link.l1 = "A więc wiedziałeś o moim udziale w losie Levassera?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Oczywiście, kapitanie. I cieszę się, że uwolniliście świat od tego potwora. Przy okazji wyciągnęliście mnie z mojej zatęchłej klitki. Sprawiliście, że spojrzałem na swoje życie inaczej.";
			link.l1 = "Niesamowite, jaki ten świat jest mały...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "Choć to brzmi sprzecznie, świat jest równie mały, co ogromny.";
			link.l1 = "Zabawne. Nigdy się nad tym nie zastanawiałem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Kapitan "+pchar.lastname+"... Cudowny dziś wieczór, prawda?";
			link.l1 = "Chyba tak. Jeszcze lepszy byłby tylko łagodny wiatr z północnego zachodu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Kapitan "+pchar.lastname+"...";
				link.l1 = "Właściwie… A zresztą, nieważne. Pamiętam cię! Ty masz na imię Moko. To przecież ty opróżniłeś cały beczułek rumu za jednym razem?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "Czego pan… monsieur?";
				link.l1 = "Nie codziennie spotyka się takiego olbrzyma. Jak masz na imię?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Ja... I ocknąłem się dopiero po dwóch dniach.";
			link.l1 = "Na twoim miejscu ktoś inny nie przetrwałby nawet kilku godzin. Jeśli walczysz tak dobrze, jak pijesz – Jean miał niesamowite szczęście z takim bosmanem.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Tak samo jak mi się poszczęściło z kapitanem. Dzięki niemu odzyskałem wolność. I dzięki wam. Gniłbym na plantacjach, gdybyście nie uratowali Jeana.";
			link.l1 = "To była ciekawa przygoda. I cieszę się, że skończyła się lepiej, niż mogłaby.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Jestem bosmanem na tym statku.";
			link.l1 = "Ha-ha, chciałbym zobaczyć tego, kto odważy się ci się sprzeciwić. Długo już służysz u kapitana?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Kilka lat. Wiele mu zawdzięczam. Gdyby nie on, dawno bym zgnił w...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "Chciałeś powiedzieć – na plantacji?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Daj spokój, "+npchar.name+", oczywiście, nie musisz mi nic mówić, ale jeśli jeszcze nie zauważyłeś, nie jestem jedną z tych czyścioszków w perukach. Kapitan cię wykupił?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Uciekliśmy razem. Z plantacji w Maracaibo. Bez Jeana nic by nam się nie udało. Od tamtej pory jestem w jego załodze. Najpierw jako marynarz, a teraz – jestem bosmanem.";
			link.l1 = "Kapitan był niewolnikiem? Nigdy bym nie pomyślał. Zresztą, w mojej szafie też znajdzie się kilka trupów. Cieszę się, że udało ci się wyrwać spod hiszpańskiego buta, "+npchar.name+". No i jak ci się podoba być marynarzem?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Jakbym wcześniej w ogóle nie żył. Morze to teraz mój dom.";
			link.l1 = "Tu cię rozumiem, mój przyjacielu. Jak nikt inny.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Kapitan "+pchar.lastname+"... W czym mogę pomóc?";
			link.l1 = "Dziękuję, "+npchar.name+", na razie niczego nie potrzebuję.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Jakże się cieszę, że widzę na tym statku choć jedną rozsądną twarz. Ci... marynarze... to barbarzyńcy.";
			link.l1 = "Na waszym miejscu nie odzywałbym się tak na cudzym statku. Nie wiem, jak trafiliście na Karaiby, ale tutaj, wiecie, panują inne zasady. Lepiej okażcie szacunek załodze.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Szacunek? Dla nich? Przecież to dzikusy! Jestem szlachcicem, "+GetTitle(NPChar,true)+", jestem przyzwyczajony do porządku, do obsługi, do... cywilizacji! Niech tylko spróbują mi się sprzeciwić – mój ojciec ich...";
			link.l1 = "Twój ojciec dowie się, że zmarłeś na gorączkę w drodze. I raczej nie będzie w stanie udowodnić, że było inaczej.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Niech diabli wezmą tego pułkownika Foxa! To wszystko przez niego! Dla jego córki przepłynąłem ocean, poświęciłem wygody, znosiłem te krzywe spojrzenia, to okropne jedzenie, to... bujanie! A teraz jeszcze płynę na jakimś cudzym statku!";
			link.l1 = "Pułkownik Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Znasz go, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Ekhm... Słyszałem o nim.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "No cóż, wiele nie straciliście. Ten człowiek to uosobienie ślepego żołnierskiego uporu i przesądów.";
			link.l1 = "On jest wojskowym...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Dokładnie! I to wszystko wyjaśnia. Kiedy przyszedłem poprosić o spotkanie z jego córką, wiecie co zrobił? Wiecie? Wyrzucił mnie za drzwi! Bez słowa!";
			link.l1 = "Ale chyba się pan nie poddał?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Oczywiście! Starałem się o audiencję przez cały tydzień! Upokarzałem się! Nawet... próbowałem przekupić straż! W końcu udało mi się do niego przemknąć, bez zaproszenia. Po prostu chciałem porozmawiać!";
			link.l1 = "Nie sądzę, żeby go to ucieszyło.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Ucieszył się? O, dostał prawdziwej histerii! Wyrzucili mnie, zakazali zbliżać się do rezydencji, skonfiskowali ojcowski statek, a potem w ogóle zabronili wszystkim angielskim kapitanom brać mnie na pokład! Musiałam szukać francuskiego statku na Martynice... To był koszmar.";
			link.l1 = "Wygląda na to, że naprawdę go rozzłościłeś.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "On zawsze był przeciwko mnie. Jego ulubione powiedzenie: 'Córka oficera – żona oficera'. Was, "+GetTitle(NPChar,true)+", uznał ją za znacznie bardziej odpowiednią partię.";
			link.l1 = "Możliwe, że tym razem miał też inne powody...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Więc przybyłeś tutaj, żeby spotkać się ze swoją ukochaną.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Tak. Nie dostałem od niej ani słowa, odkąd opuściła Europę. Jestem pewien, że jej ojciec po prostu przechwytuje listy. Ona nie mogła o mnie zapomnieć! Oczywiście, była wobec mnie powściągliwa... nawet chłodna... Ale nie wierzę, że wykreśliła mnie ze swojego życia.";
			link.l1 = "Współczuję panu, monsieur. Rany duszy goją się znacznie trudniej niż te cielesne. Proszę chwilę... Dlaczego pan, Anglik, wybiera się do Bordeaux?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "Nie zamierzam wracać do domu z hańbą. Będę musiał zatrzymać się u wuja w Bordeaux, dopóki wszystko się nie uspokoi. Zresztą, jego posiadłość jest znacznie przestronniejsza i bardziej elegancka od naszej. No i służba lepiej wyszkolona.";
			link.l1 = "Cóż, chyba to nie najgorsze rozwiązanie. Może nawet znajdziesz sobie inną wybrankę. Bordeaux jest pełne młodych piękności, uwierz mi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "Kiedy w końcu dotrzemy, "+GetTitle(NPChar,true)+"? Nie do zniesienia cierpię wśród tych wszystkich... dżentelmenów. Muszę natychmiast wziąć kąpiel.";
			link.l1 = "Obawiam się, że przez najbliższe dwa miesiące pozostaje ci tylko o niej marzyć.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Cholerna cisza morska, niechby ją szlag trafił.";
			link.l1 = "Nie marudź, "+npchar.name+", prędzej czy później wiatr się zerwie.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "A co mam robić do tego czasu, sir? Nawet nie mogę sprawdzić dział... Przecież jesteśmy na cudzym statku.";
			link.l1 = "Spróbuj po prostu odpocząć. Nie samą pracą człowiek żyje.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Przeklęta cisza morska...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Całkiem niezły statek, panie kapitanie. Też tak pan uważa?";
			link.l1 = "Nawet lepiej niż Meifeng?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "Dla "+npchar.name+" nie ma lepszego statku niż Meifeng. Ten statek nigdy nie pójdzie tak ostro pod wiatr, jak on.";
			link.l1 = "Spokojnie, "+npchar.name+", przecież żartowałem. Oczywiście, Meifeng nie ma sobie równych. Ale i Ulysses to porządny statek. Solidny.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" chcieć stanąć za sterem. Poczuć, jak statek słucha ręki...";
			link.l1 = "Niestety, mój przyjacielu, to nie jest nasz statek. Lepiej zaproponuj tamtemu olbrzymowi wspólny trening szermierki. Wam obu to dobrze zrobi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "Z jaką prędkością możemy płynąć, jeśli wiatr będzie sprzyjający?";
			link.l1 = "Tego ci na pewno nie powiem, "+npchar.name+". Lepiej zapytaj ich nawigatora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Widziałeś, jaki olbrzym tu jest bosmanem? Mówią, że jedną ręką potrafi rozgnieść kokos.";
			link.l1 = "Ha-ha. Widzę, że trochę się go boisz?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Niby dlaczego? Rozmiar nie ma znaczenia. Radziłem sobie i z większymi.";
			link.l1 = "Może więc zaproponujesz mu pojedynek na pięści? Jeden na jednego – uczciwie.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Argh...";
			link.l1 = "Zbladłeś jakoś. Ha, ha. No trudno – jak nie, to nie. Oszczędzimy twoje niezbyt już młode kości.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "W tych wodach ryb jest tyle, że można by je czerpać łodzią, a ci lenie nawet sieci nie raczyli zarzucić.";
			link.l1 = "Porozmawiaj z ich bosmanem. Myślę, że doceni twoją uwagę, he-he.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "Złoto jest bezpieczne, kapitanie "+pchar.name+". Kazałem Tichingitowi pilnować go jak oka w głowie.";
			link.l1 = "Dzięki, przyjacielu. Alonso wkrótce cię zastąpi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Knippel mi w grot, sir, na tym gruchocie jest więcej szczurów, niż widziałem przez całe swoje życie.";
			link.l1 = "Okręt długo stał w porcie, bez należytej opieki. Nowa załoga wkrótce się ich pozbędzie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway słyszeć hałas łańcucha. Kapitan rzucić kotwicę?";
			link.l1 = "To nasz pasażer zerwał bezpiecznik. Wiatr na razie jest bardzo słaby, ale mam nadzieję, że to nie potrwa długo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Tak, do diabła... Nie odmówiłbym teraz kufla porządnego rumu.";
			link.l1 = "Zaraz będzie kolacja, wytrzymaj jeszcze trochę. Alonso cię zmieni.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", kochanie, jak się czujesz?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Daj spokój, kochanie, naprawdę się na mnie obraziłaś tylko dlatego, że poszedłem do sklepu po wino?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "Do sklepu po wino? Mogłeś chociaż uprzedzić! Skąd mam wiedzieć, że nie byłeś w burdelu – z jakąś… albo ze wszystkimi naraz?!";
			link.l1 = "Kochanie, czy naprawdę sądzisz, że bym tak ryzykował? Mam najpiękniejszą, najmądrzejszą i szalenie zazdrosną żonę na całym archipelagu. Naprawdę miałbym się zadawać z jakimiś tanimi portowymi dziewczynami?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "Mógłbyś chociaż słowo do mnie powiedzieć, tak, co nie? Siedziałam tam i…";
			link.l1 = "Obiecuję, następnym razem nie tylko ci powiem – zabiorę cię ze sobą. A teraz… nagle zaczęłam się zastanawiać, czy z meblami w kajucie kapitana wszystko w porządku. Zwłaszcza z łóżkiem. Sprawdzimy?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... A jeśli ktoś wejdzie?\nHm… teraz mam na to jeszcze większą ochotę.";
			link.l1 = "W takim razie nie traćmy ani sekundy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", kochanie, jak się czujesz?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Daj spokój, kochanie, naprawdę się na mnie obraziłaś tylko dlatego, że poszedłem do sklepu po wino?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Mógłbyś mnie też zabrać ze sobą. Albo myślisz, że poradziłabym sobie gorzej niż twoi wspólnicy?";
			link.l1 = "Myślę, że bez trudu przyćmiłabyś je. Ale wtedy wino nie byłoby już w moich myślach.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "A o czym?";
			link.l1 = "O tym, żeby się z tobą tam od razu zaszyć... I ta myśl nie daje mi teraz spokoju.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "Tak?   I gdzie zamierzasz się ukryć przed ciekawskimi spojrzeniami?";
			link.l1 = "W kajucie kapitana. Myślę, że powinniśmy sprawdzić, jak wytrzymałe jest jego łóżko.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ha-ha. A co, jeśli kapitan nas przyłapie?\nChociaż… sama ta myśl sprawia, że moje serce bije szybciej.";
			link.l1 = "W takim razie nie traćmy czasu!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "To było cudowne, mój kapitanie...\nMam dla ciebie wiadomość.";
			link.l1 = "Nowina? Słucham uważnie.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... Będziemy mieli dziecko. Jestem w ciąży, tak, co nie.";
			link.l1 = "Kochana...   To prawda?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Zostaniesz ojcem, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... To niesamowite!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Czy jesteś szczęśliwy, kochanie?";
			link.l1 = "Cieszę się? Żartujesz? Do diabła, jestem najszczęśliwszym człowiekiem na świecie! Ale... dlaczego nie powiedziałaś mi wcześniej?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "Żeby opóźnić wypłynięcie? Bardzo chcę poznać twojego ojca, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... Kocham cię!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Byłeś jak zwykle wspaniały, kochanie. Mam dla ciebie wiadomość.";
			link.l1 = "Nowina? Słucham uważnie.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", chevalier de Monpe - zostaniesz ojcem.";
			link.l1 = "To... to prawda?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "To taka sama prawda, jak to, że nazywam się "+npchar.name+". Najpóźniej za pół roku urodzi nam się dziecko – mały monsieur de Mor... albo może mademoiselle.";
			link.l1 = "Helen... To niesamowite!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "To dlatego nie piłaś z nami za wypłynięcie! Ale… dlaczego nie powiedziałaś mi wcześniej?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "Bałam się, że zdecydujesz się nie ryzykować i zostaniesz na archipelagu. Chciałam, żebyś spełnił prośbę ojca. No i... bardzo chciałabym sama go poznać.";
			link.l1 = ""+npchar.name+"… Kocham cię!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "No, no… I co my tu robimy? Małych Gaskończyków?";
				link.l1 = "Ha-ha-ha! Będę miał syna, "+npchar.name+"! Zostanę ojcem!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+".   Nie uważa pan, że korzystanie z kajuty kapitana bez jego wiedzy to już przesada, nawet jak na osobę pańskiego stanowiska?";
				link.l1 = "Przepraszam, kapitanie. Ale mam ku temu ważny powód! Zostanę ojcem!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "Albo córka!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "I ty to przede mną ukrywałeś, łajdaku? A przecież uważałem cię za przyjaciela!";
			link.l1 = "Sam się właśnie dowiedziałem! Wyobrażasz sobie? Ja! Zostanę! Ojcem!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ha, ha, ha! Naprawdę jesteś szczęśliwy, przyjacielu! Pierwszy raz widzę cię takim\nNo, wy sobie tu jeszcze pogadajcie, a ja przygotuję działa do salwy na cześć święta. Daj mi znać, kiedy będziesz gotów wydać rozkaz.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ha... Uwierzcie, domyślałem się, po co tu zajrzeliście.";
			link.l1 = "Ależ nie! "+sld.name+" jestem w ciąży! Będę miała syna!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "Albo córka!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Ekhm... Z całego serca gratuluję!\nZarządzę, by oddano salwę honorową ze wszystkich dział. Dajcie znać, kiedy będziecie gotowi wydać rozkaz.\nA póki co... kajuta jest do waszej dyspozycji.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ekhm, ekhm... No cóż, tato... widzę, że od razu zapragnąłeś kolejnego dziedzica, co?";
				link.l1 = "Ha-ha! Gdyby to zależało ode mnie – zrobiłbym od razu całą tuzinę! No co, przyjacielu, oddamy salwę ze wszystkich dział?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "Obawiam się, przyjacielu, to tak nie działa. Ale staraliśmy się.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "No to co, kapitanie, oddamy salwę ze wszystkich dział?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Nie teraz.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "Załoga tylko na to czeka! Wydawaj rozkazy, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "Załoga gotowa. Wydawaj rozkazy.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Kanoniery! Ze wszystkich dział! Ognia!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Jakże się cieszę, że cię widzę, synu!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Ojciec... Nie wierzę, że znów jestem w domu... Już zapomniałem, jak wygląda śnieg. Wydaje się, że tutaj nic się nie zmieniło...";
			}
			else
			{
				link.l1 = "Ojciec... Nie wierzę, że znowu jestem w domu... Wygląda na to, że nawet śnieg postanowił uczcić ten powrót. W "+month+". Tutaj zupełnie nic się nie zmieniło...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "A o tobie nie można powiedzieć tego samego! Twój sposób bycia, chód, blizny\n"+"Nie, przede mną już nie stoi ten rozpuszczony chłopiec, którego żegnałem, когда wyruszał w dalekie strony.";
			link.l1 = "Na Karaibach szybko się dorasta, ojcze. Ale o tym jeszcze zdążymy porozmawiać. Lepiej opowiedz, jak się czujesz? Mam nadzieję, że choroba ustąpiła, skoro stoisz przede mną w pełnym rynsztunku?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Niestety, "+pchar.name+", tylko mocniej zacisnęła dłonie na moim gardle. Ale czy mógłbym spotkać mojego ukochanego syna w zwyczajnym stroju? To dla mnie wielki dzień, "+pchar.name+"\n"+"Chyba powinieneś mnie z kimś zapoznać.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Niestety, "+pchar.name+", jej uścisk z biegiem lat staje się tylko silniejszy. Ale czy mógłbym spotkać mojego ukochanego syna w zwyczajnym stroju? To dla mnie wielki dzień, "+pchar.name+"\n"+"Widzę, że nie przybyłeś sam\n"+"Na pewno zgłodniałeś po podróży? Suzanne przygotowała wątróbkę z gęsi według twojego ulubionego przepisu!\n"+"Zapraszam do stołu – po drodze nas sobie przedstawisz!";
				link.l1 = "Przyznam, ten zapach poczułem już zbliżając się do posiadłości!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Ojcze, pozwól, że przedstawię ci moją żonę - "+sld.name+" "+pchar.lastname+". "+sld.name+", to mój ojciec – kawaler "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", jestem oczarowany! Twoja wybranka wcale nie przypomina rozpieszczonej damy z towarzystwa, do których tu przywykliśmy. Śmiem przypuszczać, że równie pewnie radzi sobie ze statkiem, jak i z sercem mojego syna.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "Dla mnie to wielka przyjemność poznać panią, madame. Zapewniam, mój syn ma doskonały gust!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "Jestem zaszczycona, chevalier! Ma pan rację, naprawdę potrafię utrzymać ster nawet podczas najsroższej burzy. Jednak jeśli chodzi o serce pańskiego syna – nie trzeba nim kierować. Jesteśmy jednością w naszych celach i dążeniach.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "Opat Benoît opisał cię jako dziewczynę mądrą i odważną – i wygląda na to, że wcale nie przesadził. Cieszę się, że "+pchar.name+" odnalazłem w tobie nie tylko żonę, ale i bratnią duszę, towarzyszkę\n"+"Na pewno zgłodniałeś po podróży? Suzanne przygotowała wątróbkę z gęsi według twojego ulubionego przepisu!\n"+"No dobrze, zapraszam wszystkich do stołu! Po drodze mam nadzieję, że lepiej się poznamy.";
			link.l1 = "Przyznam, ten zapach poczułem już, kiedy tylko zbliżałem się do posiadłości!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "Miło mi pana poznać, kawalerze! "+pchar.name+" dużo o was opowiadał, i wyobrażałam sobie was właśnie takiego, tak, co nie!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", jestem oczarowany! Twoja wybranka wcale nie przypomina napudrowanych dam z salonów – i w tym tkwi jej prawdziwa wartość\n"+"Wydaje mi się, że wybrałeś piękną różę zamiast rozkapryszonych, delikatnych lilii.";
			link.l1 = "Dziką różę, ojcze… "+sld.name+"  - prawdziwy skarb. Jestem pewien, że się ze mną zgodzisz, gdy poznasz ją bliżej.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "W takim razie nie będziemy zwlekać z tym momentem! Na pewno zgłodniałeś po podróży? Suzanne przygotowała wątróbkę z gęsi według twojego ulubionego przepisu!\n"+"Zapraszam wszystkich do stołu! A po drodze, mam nadzieję, że "+sStr+"";
			link.l1 = "Przyznam, ten zapach poczułem już zbliżając się do posiadłości!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Kochana, musisz tego koniecznie spróbować – nic nie może się równać z foie gras przyrządzonym według naszego rodzinnego przepisu! Przepis ten odziedziczyliśmy po dziadku – a jemu przywieziono go w prezencie z pewnego śródziemnomorskiego kraju.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "Nie chciałbym zaczynać uczty od smutku, ale jako rodzina musimy pamiętać o tych, którzy odeszli przed nami. Proszę was, wznieśmy toast za Michela. Niech Pan obdarzy jego duszę spokojem.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "Muszę cię o tyle rzeczy zapytać, "+pchar.name+"... Ale najpierw pozwól wysłuchać twojej żony i "+sStr+". Proszę, opowiedzcie, jak poznaliście się z Charles’em.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "Muszę cię o tyle rzeczy zapytać, "+pchar.name+"... Ale najpierw pozwól mi wysłuchać "+sStr+". Proszę, opowiedzcie, jak poznaliście się z Charles’em.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "Tak samo jak wam, nie mogę się doczekać, żeby tego posłuchać!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Groziło mi śmiertelne niebezpieczeństwo... "+pchar.name+", jak prawdziwy dżentelmen, nie pozwolił, by stało mi się coś złego! Wstawił się za mną i rozprawił się z łajdakami, tak, co nie?";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" wyrwał mnie z rąk pewnego angielskiego łajdaka, który ośmielił się... porwać mnie. Gdyby przybył choćby godzinę później – nigdy byśmy się nie poznali.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "Nie wątpiłem, że postąpisz jak prawdziwy szlachcic. Honor to dla naszego rodu coś więcej niż tylko słowo. Jestem z ciebie dumny, synu.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" włamać się do domu bladoskórego, żeby znaleźć jedzenie. Bladoskóry zastał "+sld.name+" - i wsadzić do więzienia. Kapitan "+pchar.name+" przyjść, uwolnić "+sld.name+" z więzienia. Od tamtej pory "+sld.name+" służyć kapitanowi "+pchar.name+" i być wierny aż do ostatniego tchu.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "Miło wiedzieć, że mój syn jest nie tylko szlachetnym arystokratą, ale też człowiekiem o dobrym sercu. Cieszę się, że ma przy sobie tak wiernych przyjaciół jak wy, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Pewnego razu kapitan przyszedł do mnie do domu – szukał pracy. Dałem mu zadanie i poradził sobie jak należy. Szefowi się spodobał, więc coraz bardziej wciągał kapitana w swoje sprawy, a mnie wysłał na jego statek – żebym miał na niego oko... A potem ten... pan po cichu podniósł kotwicę, niech mnie kule biją, i opuścił archipelag, nie mówiąc kapitanowi ani słowa. Zostawił go samego w tym bałaganie, który sam narobił. Zaproponowałem kapitanowi swoją pomoc i choć Ryszard postąpił wobec niego podle, niech mu kule w rufę, kapitan mnie nie wygonił.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longwei i pan kapitan pracowali dla tego samego człowieka. Ale ten człowiek zdradził Longweia. Wtedy Longwei postanowił: już więcej nie będzie mu służył. Pan kapitan zabrał mnie na swój statek jako oficera i zrobił dla Longweia naprawdę wiele.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Po raz pierwszy spotkaliśmy się w tawernie w Bridgetown: "+pchar.name+" szukał sprawy, a ja - zaufanego wykonawcy. To spotkanie było tylko początkiem – potem nastąpiły wydarzenia, które splotły nasze losy. Zostałem jego oficerem i teraz bez wahania mogę nazwać go swoim przyjacielem – człowiekiem, dla którego gotów jestem zaryzykować życie.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Dostrzec człowieka mimo okoliczności to rzadka umiejętność. To chyba dowodzi, że mój syn nie jest pozbawiony rozsądku.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Cieszę się, że mój syn nie jest bezdusznym żołnierzem, lecz prawdziwym dowódcą, który potrafi zadbać o swoich towarzyszy.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Nie codziennie słyszy się takie słowa. Chyba to najlepszy dowód na to, że mój syn jest nie tylko zdolnym marynarzem, ale i dobrym przyjacielem.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Poznaliśmy się w Bordeaux. Kapitan wsiadł na nasz statek jako pasażer i zawieźliśmy go na Martynikę. Od tamtej pory – aż do samego wyjazdu tutaj – byłem głosem jego załogi i obserwowałem, jak "+GetFullName(pchar)+" krok po kroku stawał się tym, kim jest teraz.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "Więc zna pan Charles’a jeszcze jako tego nieznośnego młokosa, który opuścił dom rodzinny na moje naleganie? Sądzę, monsieur, że będziemy mieli o czym porozmawiać.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Mój drogi "+pchar.name+", przeszedłeś długą i chwalebną drogę... Wyruszyłeś na dziką sawannę tylko po króliczą skórkę, ale zmierzyłeś się z lwem i wróciłeś w triumfie, niosąc jego skórę na ramionach. Teraz jestem spokojny o los naszego majątku i wszystkich naszych ziem jak nigdy dotąd.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "Nie mogę się doczekać, kiedy będę mógł przekazać ci stery nad wszystkimi sprawami naszej rodziny. Pracy przed tobą niemało, ale wierzę, że sam Pan patrzy na ciebie z błogosławieństwem i że zdołasz nie tylko zachować powierzone ci dziedzictwo, ale i pomnożyć honor oraz dostatek rodu de Monpe.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "Dla mnie to wielki zaszczyt – być waszym synem i dziedzicem. Z radością wezmę na siebie wszystkie troski naszej rodziny. Jestem pewien, że moja żona będzie mi w tym wiernym wsparciem. Obiecuję zrobić wszystko, by jeszcze bardziej rozsławić nasz ród... A pierwszym krokiem ku jego pomyślności będzie narodziny dziecka!";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "To dla mnie wielki zaszczyt być waszym synem i spadkobiercą. Z radością przejmę wszystkie obowiązki wobec naszej rodziny i obiecuję zrobić wszystko, by jeszcze bardziej rozsławić nasze nazwisko.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Ojcze, lata w Nowym Świecie mnie zmieniły. Obawiam się, że już nie potrafię pogodzić się ze spokojnym rytmem życia tutaj, w Europie.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", naprawdę...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Tak, ojcze. "+sld.name+" jestem w ciąży.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "To naprawdę wspaniała nowina, mój drogi synu! Pan wysłuchał moich modlitw! Niech wszyscy tu obecni będą świadkami: na cześć nowo narodzonego urządzę najbardziej wystawny bal, jaki widziała nasza posiadłość! Wznieśmy więc kielichy – za dziedzica!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "Albo dziedziczkę!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "Za nowy rozdział w historii naszej rodziny!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "Za przyszłego wojownika lub dobrą córkę!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Za zdrowie maleństwa!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Za przypadek, który was połączył!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Za świetlaną przyszłość waszej rodziny!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "Za przyszłego Alonso de Mora albo Alonsitę de Mor!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ha-ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ha, ha, ha!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "To dla mnie wielki zaszczyt być waszym synem i spadkobiercą. Z radością przejmę wszystkie obowiązki wobec naszej rodziny i obiecuję zrobić wszystko, by jeszcze bardziej rozsławić nasze nazwisko.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Powiedz, "+pchar.name+", zastanawiałeś się nad moją propozycją, by połączyć się węzłem małżeńskim z Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "Przyznam się, ojcze… Yvonne nigdy nie była mi bliska. Ale w Nowym Świecie nie brakuje pięknych dziewcząt. Obiecuję wam – gdy spotkam godną, nie będę zwlekał.";
			}
			else
			{
				link.l1 = "Przyznam się, ojcze… Yvonne nigdy nie była mi bliska. Ale we Francji nie brakuje pięknych dziewcząt. Obiecuję – gdy spotkam tę właściwą, nie będę zwlekał.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "Podoba mi się twoje nastawienie, mój drogi synu. Wznieśmy kielichy – za ciebie, za twoje osiągnięcia i za godny powrót do domu!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "Za wiernych przyjaciół, bez których nie da się przetrwać w Nowym Świecie!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "Za wielkie serce kapitana Charles'a!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Za żelazną wolę kapitana!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Za mądrość pana kapitana!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Za oddanie sprawie!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "Za umiejętność wychodzenia z opresji bez szwanku!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "Słyszałem, że bardzo uparcie domagał się pan audiencji. Więc, czego pan potrzebuje od gubernatora Martyniki?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Chcę porozmawiać o pracy na rzecz korony Francji.";
			link.l1 = "Tak, mam dla ciebie zadanie, do którego potrzebna będzie ci maksymalna zaradność i umiejętność prowadzenia morskiej walki. Jesteś gotów się wykazać?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Wasza Wysokość, czy mógłby Pan dokładniej wyjaśnić, na czym będzie polegało to zadanie?";
			link.l1 = "Oczywiście. Musicie odnaleźć hiszpański statek kurierski o nazwie 'Santa Esperanza', przejąć go abordażem i przywieźć mi dokumenty, które znajdziecie w kajucie kapitana. Wskazany przeze mnie okręt będzie przepływał w pobliżu Trynidadu za mniej więcej dwanaście dni.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "Dobrze, podejmuję się tego zadania. Jakich dokumentów mam szukać?";
			link.l1 = "Korespondencję pocztową. Tam, między innymi, znajdą się dla mnie bardzo ważne dokumenty. Ale nie musicie grzebać w papierach, po prostu dostarczcie mi cały pakiet w całości. Za tę przysługę zapłacę wam piętnaście tysięcy peso... A więc, czekam na was w swojej rezydencji z efektami waszej pracy.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Przypuszczam, że nie każę Waszej Wysokości długo czekać.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Wasza Wysokość... Czy mogę złożyć raport?";
			link.l1 = "Zdajcie raport, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Ekhm-ekhm...";
			link.l1 = "Mówcie swobodnie. Nie mam przed żoną żadnych tajemnic.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "Wywiad donosi: z Willemstadu wypłynęła eskadra. Na czele – okręt liniowy drugiej rangi ‘Gouden Leeuw’, prawdziwy morski potwór. Łączna siła eskadry to ponad dwieście pięćdziesiąt dział i ponad półtora tysiąca żołnierzy. Ich celem jest Saint-Pierre.";
			link.l1 = "Hmm... Czyli praktycznie nie mamy czasu na przygotowania.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "Jak postąpimy, panie gubernatorze?";
			link.l1 = "Na naszej redzie stoi kilka okrętów, które mogą uderzyć przeciwnika od tyłu...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Zamierzasz uderzyć na nich z dwóch stron?";
			link.l1 = "Dokładnie tak. Fort przyjmie na siebie pierwszy ogień. A gdy zapadnie noc, eskadra pod moim dowództwem uderzy od strony morza. Rozproszymy ich uwagę, a wtedy z portu ruszą brandery, wypełnione smołą i deskami. Po ich flocie nie zostanie nawet drzazga.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "Wyśmienity plan, Wasza Wysokość! Czy pozwolicie wydać rozkaz rozpoczęcia przygotowań?";
			link.l1 = "Zaczynajcie. I niech Pan będzie z nami.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Straż, zawołajcie Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Panie gubernatorze...";
				link.l1 = ""+npchar.name+", holenderska eskadra lada dzień tu przybędzie i zacznie oblężenie. Słuchaj rozkazu: zabierz Filipa i "+sld.name+", i natychmiast zaprowadź ich do opata. Niech zbierze wszystkie kobiety, dzieci i starców i zadba o ich bezpieczeństwo.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Panie gubernatorze...";
			link.l1 = ""+npchar.name+", holenderska eskadra może w każdej chwili przypłynąć tutaj i oblec miasto. Przekaż opatowi, żeby zebrał wszystkie kobiety, dzieci i starców i zadbał o ich bezpieczeństwo. Co do ciebie, planuję powierzyć ci dowodzenie branderem. Szczegóły później. Najważniejsze to ochronić cywilów.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "Nie sądzę, że "+sld.name+" zgodzi się dołączyć do pozostałych kobiet. Umiera z nudów.";
			link.l1 = "Hmm... W takim razie przekaż jej, żeby szykowała się do walki. Ty też nie będziesz się nudził – poprowadzisz brander. Szczegóły później. Teraz — zaopiekuj się moim synem.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "To dla mnie zaszczyt! Pozwolisz mi wykonać?";
			link.l1 = "Pozwalam. Działaj. Każda sekunda się liczy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Cóż... Przyznam, spodziewałem się, że tak powiesz – a jednak miałem nadzieję na inną odpowiedź. Ale szanuję twój wybór i nie będę cię już namawiać.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Rozumiem, że was zawiodłem. Ale mam dla was wiadomość, która, mam nadzieję, przyćmi wszystko, co zostało wcześniej powiedziane.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Jestem cały w słuchu.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Zamierzam zostać tutaj co najmniej rok. "+sld.name+" w jej stanie kołysanie jest niewskazane.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", naprawdę...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Cóż... Przyznam, spodziewałem się, że tak powiesz – a jednak miałem nadzieję na inną odpowiedź. Ale szanuję twój wybór i nie będę cię już namawiał. Powiedz mi jednak, "+pchar.name+", zastanawiałeś się nad moją propozycją, by połączyć się węzłem małżeńskim z Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Nie mogłeś się powstrzymać, co?";
			link.l1 = "Ty?!   To sen?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "Pragnienie łatwego zysku, władza, złudzenie nieśmiertelności… Co z tego cię zgubiło, bracie? Co przesłoniło twój rozum, tak jak zaćmiewa umysły wszystkich bladych twarzy?";
			link.l1 = " Wynoś się! Jesteś tylko duchem! Ciebie tu nie ma! ";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "Więc jeszcze nie zrozumiałeś? Spectra sunt memoria peccatorum. To ty jesteś duchem... Karaibska legenda o człowieku, którego pożarły chciwość i ślepa pycha. Ilu zabiłeś dla złota, "+pchar.name+"?";
			link.l1 = "Cóż, drogi bracie, nie mam nic przeciwko, żeby zabić cię po raz drugi! Sam się o to prosiłeś!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}