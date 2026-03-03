void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		case "startoff":
			dialog.text = "Kapitanie de Maure! Witaj na Tortudze!";
			link.l1 = "Dzień dobry, poruczniku. Cieszysz się widokiem morza ze swoimi przyjaciółmi?";
			link.l1.go = "startoff_joke";
			link.l2 = "Odpuść, poruczniku.";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "Kapitanie, twoja reputacja cię wyprzedza, a wyżsi rangą postanowili zorganizować dla ciebie małą wycieczkę po urokach naszej pięknej wyspy. Zaczynamy od razu - od więziennych cel miasta. Twoi oficerowie są również zaproszeni.";
			link.l1 = "Poruczniku, nie jestem jakimś parszywym przemytnikiem, którego złapałeś na plaży. Żadnych żartów, proszę. Wyjaśnij sprawy porządnie.";
			link.l1.go = "startoff_joke_1";
			link.l2 = "W takim razie nie traćmy czasu! Prowadź, poruczniku!";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "Widzę, że w kontaktach z wami, żeglarze, potrzeba innego podejścia. Żołnierze, szykujcie się do walki! Kapitanie de Maure, ty i twoi oficerowie jesteście aresztowani. Oddajcie broń!";
			link.l1 = "Mogę dać ci kulę - gdzie sobie życzysz, poruczniku? Z wami, lądowe szczury, nie ma innej drogi.";
			link.l1.go = "startoff_silence_1";
			link.l2 = "Na mocy jakiego prawa? Jeśli chcesz aresztować uzbrojoną grupę bez rozlewu krwi, poruczniku, musisz się bardziej postarać.";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = " Dla mnie wszyscy jesteście tacy sami... Przykro mi, ale nie będzie żadnych wyjaśnień, kapitanie. Rozkazy z góry. Oddajcie broń, jeśli bylibyście tak uprzejmi.";
			link.l1 = "Nie potrzebuję teraz żadnych kłopotów... nie teraz. Zrób, co mówią.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "Uh... Myślę, że nie do końca mnie zrozumiałeś. Kapitanie, ty i twoi oficerowie jesteście aresztowani! Złóżcie broń i chodźcie z nami!";
			link.l1 = "Nie potrzebuję kłopotów... nie teraz. Rób, co mówią.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "Jeszcze jedno słowo, kapitanie, a zakopiemy cię tutaj. Broń na ziemię, natychmiast!";
			link.l1 = "Nie potrzebuję teraz kłopotów... nie teraz. Rób, co mówią.";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "Nie boję się krwi, Kapitanie. Nawet jeśli cudem przeżyjesz, nigdy więcej nie postawisz stopy na Tortudze. A nasze służby wywiadowcze wierzą, że bardzo cenisz sobie dostęp do tej wyspy.";
			link.l1 = "Nie potrzebuję żadnych kłopotów... nie teraz. Rób, co mówią.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Kapitanie, sprawy mają się parszywie! Wróg trzyma nas w żelaznym uścisku, obawiam się, że nie odpuszczą, dopóki nie będziemy martwi! Nasi ludzie są teraz w prawdziwych tarapatach, a większość załóg dział została wyeliminowana!";
			link.l1 = "Pomogę im. Przejmij dowodzenie i wyprowadź nas stąd!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Tak, panie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Zwycięstwo, Kapitanie! Grupa desantowa została zniszczona, wróg postanowił się wycofać i skierował się na południe. Stan statku jest zadowalający. Żywa załoga: "+GetCrewQuantity(pchar)+" ludzi. Koniec raportu!";
			link.l1 = "Dziękuję! Rum dla wszystkich i wzmocnijcie straż, dopóki nie dotrzemy do portu!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Hura! Aye aye!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "A oto i sam człowiek! Czy widziałeś tę krwawą masakrę na zewnątrz? To wszystko twoja robota, zdrajco! Ale odpowiesz za wszystko: za Portobelo, za Gruoh i za tę kopalnię!";
			link.l1 = "Zaczekaj, co to ma niby...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "Agh! To nie wróży dobrze...";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "San Santiago, miej mnie w opiece! Łotrostwo! Jakaż bestia mogła popełnić taki czyn? Odpowiedz, señor!";
			link.l1 = "Spokojnie, señor! Najpierw się przedstaw! Tak, miała tu miejsce potworna rzeź, ale ludzie, którzy jej dokonali, już nie żyją. Osobiście 'ozdobiłem' kopalnie ich szczątkami...";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "Jestem "+GetFullName(npchar)+", główny inżynier królewskiej kopalni Los Teques. Właśnie wróciłem z wielomiesięcznego zadania i...co widzę! To, co się tutaj wydarzyło, jest zbrodnią przeciwko Bogu i ludzkości, więc proszę was o natychmiastowe złożenie broni. Władze Caracas zbadają to łotrostwo!";
			link.l1 = "Nie mogę się zgodzić, señor, i przysięgam, że nie miałem nic wspólnego z tą masakrą! Ale jeśli będziesz nalegał, twoje własne ciało zostanie dodane do stosu.";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "Nie boję się śmierci, ale zawsze wiem, kiedy się wycofać. Idź, ale pamiętaj, że zgłoszę, co się tu wydarzyło, i nie pominę żadnego szczegółu!";
			link.l1 = "Nie mogę się na to zgodzić, señor. Przykro mi, że do tego doszło. Do boju!";
			link.l1.go = "mine_head_fight";
			link.l2 = "Wygląda na to, że szukasz śmierci, señor. Ale dziś nikt więcej nie zginie. Odchodzimy, i mam nadzieję, że ten szczegół również znajdzie się w twoim raporcie!";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "Co powinniśmy zrobić z więźniem, Kapitanie?";
			link.l1 = "Nic specjalnego, po prostu nie pozwól mu umrzeć ani uciec.";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "Tak jest! Rozumiem, że nie będę musiał uczestniczyć w dzisiejszym przesłuchaniu, Kapitanie?";
			link.l1 = "Czemu nie? Zdecydowałeś się zmienić zawód, Alonso?";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "Ha-ha, nie, Kapitanie. Uwielbiam tę robotę, ale wygląda na to, że masz nowego mistrza rzemiosła na pokładzie!";
			link.l1 = "Hercule? Skąd wziąłeś ten pomysł?";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "Cóż, kapitanie, starzec przyniósł swoje narzędzia właśnie na tę okazję i już je wykorzystał. Nawet nie będę musiał wyciągać swoich. Ha!";
			link.l1 = "Rozumiem...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "Ach... Charles de Maure. Pozwól, że złożę moje przeprosiny w imieniu całej Ligi. Rozkaz, by cię zostawić, dotarł do nas zbyt późno. Nasza organizacja nie ma wobec ciebie żadnych roszczeń, Kapitanie. Jeśli chodzi o to łyse zwierzę... Uch! Dopóki jest na twojej smyczy, jest bezpieczny, ale moja rada dla ciebie to nie zatrzymuj go i pozwól mu zgnić w rynsztoku, gdzie jego miejsce!";
			link.l1 = "Dzięki za rekomendację, ale bardziej interesuje mnie, dlaczego ktoś mnie chroni przed twoimi najemnikami.";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "Nie wiem, Kapitanie. Przypuszczam, że instrukcje przyszły od naszego nowego mecenasa. Słyszałeś o nim, zdrajco? Liga znowu jest na szczycie!";
			link.l1 = "A kto to jest?";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "Nie wiem, Kapitanie, a nawet gdybym wiedział, takich rzeczy się nie ujawnia.";
			link.l1 = "W takim razie powiedz mi coś jeszcze, a potem możesz iść, gdzie tylko chcesz. Masz moje słowo.";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "Tak po prostu? Dobrze, kapitanie, zadawaj swoje pytania i pozwól mi odejść. Obiecuję, że nie wrócę do Ligi, nawet gdybym mógł.";
			link.l1 = "Dlaczego tak się uwziąłeś na Hercule'a? Zbyt wiele kłopotów jak na jednego dezertera.";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "Co mu powiedziałeś, psie? Wszystko nie jest takie, jak się wydaje, Kapitanie! Liga jest w ciągłym ruchu, zasady się zmieniają, pracodawcy się różnią. Chcesz odejść? Jasna sprawa! Wyjście jest zamknięte tylko dla najwyższych oficerów, a ten łotr nigdy nim nie był. Jego żona, owszem, ale szanowaliśmy Madame Tonzag zbyt mocno, by nie zrobić dla niej wyjątku.";
			link.l1 = "W takim razie dlaczego?";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "Była sprawa w Portobelo... To było coś dużego. Widzisz, twój przyjaciel nie tylko odszedł, nie tylko zerwał kontrakt, nie tylko zabił grupę, która przyszła dokończyć jego robotę. On wywołał prawdziwą masakrę na ulicach, znacznie komplikując nasze relacje z Kastylijczykami. Rzadki piracki rajd sieje tyle terroru, co ten, którego doświadczyli dobrzy katolicy tamtego dnia. Do diabła, może nawet byłbym pod wrażeniem, gdyby ktoś inny to zrobił.";
			link.l1 = "Kolejna masakra? Jakże interesujące. Kontynuuj.";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "Wówczas wice-dyrektor Kompanii, Rodenburg, interweniował. W jakiś sposób udało mu się stłumić całą sprawę, ale nie zanim straciliśmy wielu z naszych najlepszych ludzi w hiszpańskich operacjach karnych. Po pewnym czasie jednak, ponownie prowadziliśmy z nimi interesy... Ach! Ale niczego nie zapomnieliśmy i gdy tylko nadarzyła się okazja, próbowaliśmy się wyrównać. Inicjator wszystkiego, Tonzag, musiał zostać zgładzony.";
			link.l1 = "Nie udało ci się to. A co z kopalnią?";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "Byliśmy zmuszeni to zrobić. Pozbycie się tej szumowiny wymagało zbyt dużych wydatków; potrzebowaliśmy złota. Wszystko przez niego... Ale próba zamachu się nie powiodła i wróciłem do Los Teques, żeby trochę posprzątać... Jak zorientowałeś się, gdzie szukać?";
			link.l1 = "To nie ma znaczenia. Muszę spotkać się z waszym przywódcą. Chcę osobiście wyjaśnić to nieporozumienie, ponieważ gwarancje od waszego tajemniczego protektora mogą wygasnąć w każdej chwili.";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "Jestem pewien, że już czekają na ciebie w Caracas, Kapitanie. Widzisz, nic przed tobą nie ukrywam.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "Dowódca Arno zginął, teraz dowodzi Austin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "Odpowiedziałem na wszystkie twoje pytania, kapitanie. Dotrzymaj słowa.";
			link.l1 = "Pozwalam ci odejść. Zejdź z mojego statku i módl się, żeby nie czekała na mnie zasadzka w Caracas.";
			link.l1.go = "captive_spare";
			link.l2 = "Dzięki za interesującą rozmowę. Oskarżanie Hercule'a o spowodowanie masakry po tym, co widziałem w kopalni, to jednak przesada. Marsz do piekła, gdzie twoje miejsce.";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "Panowie, jesteście zaproszeni na spotkanie. Czekają na was w kościele, więc bezpieczeństwo jest gwarantowane.";
			link.l1 = "To było szybkie...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "Charles de Maure. Hercule. Nie wyjdziecie stąd żywi.";
			link.l1 = "Bardzo miły sposób na rozpoczęcie rozmowy. Naprawdę potrzebujesz tego wszystkiego?";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "Z tobą, Kapitanie, sprawy nie są tak proste. Widzisz, nasz nowy patron nalegał, aby cię zostawić w spokoju... i niech sobie te prośby wsadzi tam, gdzie słońce nie dochodzi! Nienawidzę takich jak ty! Żeglujecie pod swoimi pięknymi, białymi żaglami, myśląc, że lód nie stopi się wam w ustach. Ale kiedy stal mojej klingi wchodzi w was, wszyscy wrzeszczycie jak dziewczynki. Uwielbiam to, Charles, powiem ci! Dawno tego nie robiłem... a teraz mam cię tuż przed sobą, przystojniaku.";
			link.l1 = "Jesteś chory, kamracie. Ciebie to nawet szkoda przeszywać ostrzem... Powiem więc krótko: Ja i Hercule wychodzimy stąd w tej chwili, a ty i twoi przełożeni zapominacie o całej sprawie. Wyślesz choćby jednego zabójce na mnie, bądź Hercule'a, a będe wiedzieć gdzie cię szukać.";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "Nie, nie mogę cię puścić. Z twoim przyjacielem, z drugiej strony, to jest o wiele prostsze - moi chłopcy nie potrzebują go, ale wciąż są niektórzy z jego starych mierzalnych kolegów z Ligi, którzy nie są do końca przekonani o skuteczności moich metod... Zbyt przyzwyczajeni do pracy czysto, za czyste dublony, od czystej Kompanii. Ale znam właśnie coś, co zmieni ich zdanie - głowa jednego śmiałego grzesznika na tacy, ha-ha!";
			link.l1 = "Nie wybrałeś odpowiedniego miejsca, ty wariacie. Naprawdę zamierzasz rozpocząć bitwę w kościele?";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "Pewnie, czemu nie? Żal ci tych ludzi? Może nie będzie to tak dochodowe jak w Los Teques, ale i tak będziemy się dobrze bawić. Pomalujemy ściany domu Bożego, ah-ha! Kapitanie, dostarczysz dużo farby.";
			link.l1 = "Rozumiem. Zazdrościsz nam, prawda, ty szalony szczurze? Zazdrościsz naszej wolności? Tego, że dziewczęta cieszą się na nasz widok i że monety dźwięczą w naszych kieszeniach? Spójrz na siebie: gdzie cię twoi protektorzy wykopali, świnio? Kto cię wpuścił do kościoła?";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "Żryj ziemię, ty mały gnojku!";
			link.l1 = "Wzajemnie!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
} 
