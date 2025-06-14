// диалоги НПС по квесту 'В поисках Стража Истины'
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Jak mogę ci pomóc?";
			link.l1 = "Przepraszam, to nic takiego.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "Czego chcesz? Kolejne przesłuchanie? Idź do diabła!";
			link.l1 = "Panie, jak się nazywasz?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Cóż cię obchodzi imię człowieka, którego masz powiesić lub zastrzelić? Bastardo! Byłem na tyle nieostrożny, że wpadłem w twoje ręce...";
			link.l1 = "Señor, przedstaw się. Nie mogę rozmawiać z człowiekiem, nie znając jego imienia.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+" No i co, zadowolony jesteś? A teraz, z kim mam przyjemność rozmawiać?";
			link.l1 = " Nazywam się "+GetFullName(pchar)+" Czy kiedykolwiek wcześniej o mnie słyszałeś?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "Nie, do diabła! Czy wyglądam na kogoś, kto zna każdego wędrownego włóczęgę na Zachodnich Indiach, który...";
			link.l1 = "Dość. Zróbmy to bez obelg i zachowajmy się jak dżentelmeni. Twój los będzie zależał od tego, co możesz mi powiedzieć. Jeśli powiesz mi coś interesującego, złożę petycję o twoje zwolnienie pod moją opiekę. To pozwoli ci uniknąć kuli muszkietowej lub pętli, która teraz na ciebie czeka.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Dios mio, to oferta, której nie mogę odrzucić. Co chciałbyś wiedzieć, señor?";
			link.l1 = "Kto zorganizował tak wielki atak na St. Pierre i dlaczego?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Baron Ramon de Mendosa y Riba, dowódca garnizonu na wyspie Providence. Wysłał eskadrę, by najechać i złupić miasto, przejmując wszelkie wartościowe rzeczy, które możemy znaleźć.";
			link.l1 = "Jakie było twoje bezpośrednie zadanie podczas ataku? Konkretnie, jakie były twoje rozkazy?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Jestem dowódcą batalionu morskiego. Nasze rozkazy dotyczyły zdobycia fortu i zabezpieczenia jego baterii przed ostrzałem naszych łodzi desantowych, gdy zbliżały się do miasta. Po tym moi ludzie wzięli udział w ataku na samo St. Pierre.";
			link.l1 = "Czy został pan poinformowany o kosztownościach znajdujących się w mieście? O ich ilości i jakości?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Nie mieliśmy dokładnych informacji co do ilości, ale Baron de Mendosa y Riba powiedział nam, że pod fortem przechowywane jest srebro, a magazyny portowe mają strategiczne surowce niezbędne do wysiłku wojennego: drewno twarde i jedwab okrętowy.";
			link.l1 = "Czy znalazłeś te cenne rzeczy?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "Nie. Nie znaleźliśmy ani jednego. Magazyny były wypełnione typowymi kolonialnymi towarami, a pod fortem znajdował się proch strzelniczy, broń i ołów. Ale nie mieliśmy wystarczająco dużo czasu, aby przeprowadzić dokładniejsze poszukiwania... francuskie posiłki wpadły z hukiem i byliśmy zmuszeni podjąć bitwę.";
			link.l1 = "Czy nie wydało ci się dziwne, że nie znalazłeś kosztowności?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Oczywiście, że tak, ale zazwyczaj nie kwestionuję rozkazów.";
			link.l1 = "Słuchaj uważnie, co mam ci powiedzieć. Fort St. Pierre nigdy nie skrywał srebra, a te magazyny nigdy nie przechowywały drewna twardego i jedwabiu. Pomyśl dobrze, señor, zanim odpowiesz, bo jeśli twoja odpowiedź mnie nie zadowoli, odwrócę się i wyjdę stąd, zostawiając cię na łaskę losu... smutnego losu.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Słucham.";
			link.l1 = "Nie wierzę, że jedynym celem waszego najazdu było zwykłe rabowanie. St.Pierre to niepozorna i stosunkowo biedna kolonia, by wysyłać tu całą eskadrę dowodzoną przez okręt liniowy pierwszej klasy. Z pewnością ty, twój dowódca lub ktoś inny mieli dodatkowe rozkazy lub polecenia. Co ci powiedzieli? Dobrze się zastanów, zanim odpowiesz...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Zamierzasz milczeć? Dobrze. Zastanów się nad tym chwilę, poczekam.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Señor, moje życie będzie zależało od mojej odpowiedzi?";
			link.l1 = "Poprawnie.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "Mam coś... Ale musisz mi przysiąc, że wyciągniesz mnie stąd i wykupisz mnie do Hiszpanii.";
			link.l1 = "Jeśli powiesz mi coś godnego mej uwagi, przysięgam na Święty Krzyż, że zostaniesz przetransportowany na mój statek dla okupu i unikniesz egzekucji.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "Dobrze. Don Diego de Montoya polecił naszemu batalionowi marines, że musimy w pełnej tajemnicy i z najwyższą wagą znaleźć i pojmać człowieka o imieniu Miguel Dichoso, który znajduje się gdzieś w St. Pierre pod ochroną władz.";
			link.l1 = "Nie przestawaj. Kim jest Diego de Montoya?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "Oficer dowodzący eskadrą. Uciekł wkrótce po twoim... dramatycznym przybyciu.";
			link.l1 = "Kim on jest, ten Don Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "Jedyne, co wiem, to że jest upoważnionym przedstawicielem Barona de Mendosa y Riba, jego prawą ręką i agentem do zadań specjalnych.";
			link.l1 = "Interesujące... A kim jest Miguel Dichoso, człowiek, na którego najwyraźniej zaaranżowano całą tę katastrofę? Musi być złym człowiekiem, co?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Czy pamiętasz swoją przysięgę, señor?";
			link.l1 = "Tak. I zapewniam, że jeśli będziesz kontynuować swoją opowieść, zostaniesz przekazany jako kluczowy świadek na mój statek, a później... cóż, znajdę sposób, by dostarczyć cię do hiszpańskiej osady. Ale nie zanim powiesz mi wszystko, co wiesz.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso jest byłym towarzyszem broni barona, jednak niektórzy mówią, że Miguel go zdradził. Señor de Mendosa y Riba chce go żywego, więc otrzymaliśmy rozkaz, by nie zabijać Dichoso pod żadnym pozorem.";
			link.l1 = "Czy Dichoso też jest Hiszpanem?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Si. Don Diego de Montoya dał nam przybliżony opis i rozkazał, by każdy człowiek wyglądający jak Dichoso został dostarczony bezpośrednio do niego. Ale z uwagi na krótki czas, jaki mieliśmy przed waszym kontratakiem, nigdy nie mieliśmy czasu na poszukiwania.";
			link.l1 = "Czy znałeś Dichoso osobiście?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "Nie, tylko z reputacji. Nigdy wcześniej nie widziałem tego człowieka. Niektórzy z moich kolegów oficerów znali go osobiście. Wszyscy są martwi.";
			link.l1 = "Jak bardzo Dichoso zdradził waszego Don Mendozę, że ten postanowił wysłać za nim całą eskadrę?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "Opowiem ci. Baron dopiero niedawno przybył na Karaiby z Hiszpanii. Jego rozkazy były takie, aby zapewnić bezpieczeństwo konwojom Hiszpańskiej Floty Skarbowej, ale zamiast tego szukał na lądzie... poszukując indiańskiego złota. Jego głowę zawróciły plotki o ukrytych skarbach. Zdecydował, że starożytne miasto Majów istnieje gdzieś głęboko w dżunglach Jukatanu - Tayasal, legendarne miasto złota\nBaron wysłał kilka ekspedycji, aby znaleźć to miasto, ale wszystkie zostały całkowicie zniszczone w dzikiej dżungli. Bez wątpienia każda z nich została zmasakrowana przez wojowniczych ludzi Itza, którzy tam mieszkają\nOstatecznie inkwizytor Vincento miał dość fantazji Don Mendosy i bezsensownej śmierci dobrych żołnierzy. Inkwizytor poinformował Madryt o sytuacji. Wicekról zabronił Don Mendozie poszukiwania mitycznego miasta i nakazał mu skupić się na swoich obowiązkach. Wtedy pojawił się Miguel Dichoso\nPrzekonał barona do zorganizowania kolejnej ekspedycji, która zaskakująco zakończyła się sukcesem. Znaleźli ruiny starożytnego miasta i stos złota inkrustowanego klejnotami. Ale w drodze powrotnej zostali zaatakowani przez plemię Mosquito\nWszyscy poza Miguelem zginęli, indiańskie strzały są nasączone miejscową trucizną, nawet małe zadrapanie prowadzi do pewnej, agonizującej śmierci w ciągu kilku dni. Dichoso powrócił do Providence z takim skarbem, jaki mógł unieść\nCarajo! Baron był niewymownie szczęśliwy, wysłał pilne listy do Madrytu i do ojca Vincento w Santiago, bez wątpienia chciał wytknąć swoje sukcesy ojcu zakonu. Następnie przygotowano fregatę, aby dostarczyć skarb z powrotem do Hiszpanii. Dichoso zgłosił się na ochotnika, aby ją eskortować.";
			link.l1 = "Niech zgadnę. Nie dostarczył złota?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Zgadza się, señor! Fregata zniknęła bez śladu wraz z całym ładunkiem i załogą, w tym Dichoso. Baron był wściekły. Ponownie został upokorzony przed Eskurialem, ku wielkiej satysfakcji ojca Vincento. Teraz Don Mendosa jest człowiekiem opętanym odzyskaniem swojej zranionej dumy, utraconego skarbu i Miguela Dichoso.";
			link.l1 = "Nie jest możliwe, że fregata mogła po prostu wpaść w burzę i zatonąć? Albo została schwytana przez piratów?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "Baron przysiągł w uniesieniu, że był pewien, iż Dichoso go zdradził. Nie znam szczegółów. Po kilku tygodniach przybył Don Diego de Montoya z nowymi informacjami, że Miguel Dichoso może być w St. Pierre.";
			link.l1 = "Hm.  Interesujące. Znowu te indiańskie skarby. Wszystko wydaje się podejrzanie związane z nimi...  Więc, nie znalazłeś Dichoso?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "Nie. I szczerze mówiąc, byłbym zaskoczony, gdyby kiedykolwiek tu był. Baron jest tak zaślepiony myślą o schwytaniu Dichoso, że uwierzyłby nawet w najbardziej nieprawdopodobne fantazje.";
			link.l1 = "Powiedz mi, "+npchar.name+",  jak Don Mendosa dowiedział się o tym... uh... mieście Tayasal? Nie wyśnił tego, prawda? Były jakieś fakty czy coś innego?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "To ojciec Vincento jako pierwszy usłyszał o rzekomym istnieniu Tayasal i mieście złota. Gdzie się o tym dowiedział, nie mam pojęcia...";
			link.l1 = "To ciekawy rozwój wydarzeń. Ojciec Vincento sam wymyślił teorię istnienia Tayasal, sam poinformował Hiszpanię i zaczął wrzucać muchy do maści barona...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "Jako współwyznawca katolicyzmu powinieneś wiedzieć, jak ci czcigodni ojcowie z Świętego Trybunału działają... Nie poinformował Madrytu bez powodu. Ma jakiś plan, ale przybycie barona najwyraźniej nie było jego częścią. W każdym razie, nie wiem nic więcej na ten temat. Nigdy nie miałem ochoty zajmować się Inkwizycją.";
			link.l1 = "Dobrze. Przekazałeś mi wiele interesujących informacji, "+npchar.name+", i zgodnie z moją przysięgą wyprowadzam cię stąd. Wrócę po ciebie później, ale na razie... pozwól mi chwilę pomyśleć o tym, co mi powiedziałeś...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Señor? Czy dotrzymasz swojej obietnicy?";
			link.l1 = "Zawsze dotrzymuję obietnic. Dziś jest twój szczęśliwy dzień, "+npchar.name+". Pojedziesz ze mną do Santiago na Kubie. Opowiem ci więcej o moim planie, gdy dotrzemy na miejsce. Ale na razie, witaj na pokładzie. Będziesz odprowadzony do portu i dostarczony na mój statek.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "Moja wdzięczność, kapitanie. Cieszę się, że jesteś dżentelmenem słowa.";
			link.l1 = "Możesz wyrazić swoją wdzięczność później. Będziesz moim gościem, ale pod strażą. Nie zrozum mnie źle, wciąż cię potrzebuję.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Rozumiem, señor. Daję ci moje słowo jako hiszpański oficer, że nie podejmę żadnych prób ucieczki.";
			link.l1 = "Bóg oszczędza ostrożnych. Do zobaczenia na pokładzie.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Kapitanie, jakie są twoje zamiary tutaj na Kubie? Przybyłeś, by mnie tu zostawić? Nawet nie śmiem na to liczyć...";
			link.l1 = "Dokładnie tak, jestem tutaj, aby oddać cię twoim rodakom. Jednak powód mojego przybycia tutaj jest nieco bardziej skomplikowany niż tylko to. Ale to już cię nie dotyczy. Pozwolę ci odejść teraz bez okupu, ale pod warunkiem, że przysięgniesz mi dwie rzeczy.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "Czym one są?";
			link.l1 = "Po pierwsze dam ci zapieczętowany list. Osobiście dostarczysz ten list inkwizytorowi Santiago, Ojcu Vincento. Jeśli zapyta, od kogo jest list i jak go dostałeś, powiedz mu prawdę...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "Drugim jest to, że nie będziesz wspierał ani pomagał w żadnych próbach odnalezienia mnie i zaatakowania mojego statku przynajmniej przez tydzień. Zgoda?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "Czy to wszystko?";
			link.l1 = "Tak, to wszystko. Spełnij moje warunki i możesz odejść wolno.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Przysięgam ci, señor, że osobiście dostarczę list Ojcu Vincento i nie podejmę żadnych działań, które mogłyby sprowokować agresję garnizonu Santiago przeciwko tobie lub twojemu statkowi. Bądź pewny, dotrzymam słowa. Jestem Hiszpanem i szanuję silnych i szlachetnych przeciwników.";
			link.l1 = "Dobrze, Don "+GetFullName(npchar)+"Przyjmuję twoją przysięgę i pozwalam ci odejść już teraz. Oto, weź ten list dla Inkwizytora. Jesteś teraz wolny.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Żegnaj, señor. Mam nadzieję, że nigdy więcej nie spotkamy się na polu bitwy. To by mnie strasznie zasmuciło.";
			link.l1 = "Żegnaj...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dios mio, cóż za szczęśliwe spotkanie! Witaj, monsieur "+GetFullName(pchar)+"! Widzę, że stałeś się mile widzianym gościem w Santiago. Czy pracujesz dla Świętej Inkwizycji?";
			link.l1 = "Witaj, señor "+npchar.name+" Myślałem, że już nigdy się nie zobaczymy, przynajmniej nie w przyjaznych okolicznościach! Nie, właśnie wpadłem odwiedzić ojca Vincento. A co z tobą? Teraz służysz w Santiago?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "Po tym jak mnie uwolniłeś z aresztu, byłem zmuszony zostać w Santiago, nie jest bezpiecznie wracać mi do Providence... ale jak widzisz, dotrzymałem słowa. Żadne hiszpańskie statki nie ścigają cię...";
			link.l1 = "Cieszę się, że obaj jesteśmy ludźmi honoru.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Słuchaj, kapitanie, czy nie miałbyś nic przeciwko wzniesieniu kielicha rumu, na nasze ponowne spotkanie, że tak powiem? Nigdy bym nie pomyślał, że zaproponuję to Francuzowi, ale ty, señor, jesteś wyjątkiem.";
			link.l1 = "Oczywiście! Nie miałbym nic przeciwko przepłukaniu ust rumem. Chodźmy do tawerny.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ach, zdrowie!";
			link.l1 = "Za co pijemy, señor oficerze?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Napijmy się za coś neutralnego, co jednak dotyczy nas obu. Na przykład, za dzielną i udaną służbę dla ojczyzny! Każdy ma swoją!";
			link.l1 = "I wypijmy także za to, by nasi monarchowie doszli do porozumienia między sobą, a Francuzi i Hiszpanie przestali walczyć zarówno w ojczyźnie, jak i na Karaibach.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Dobrze powiedziane, kapitanie! Za pokój! Pokażę ci, jak pić po hiszpańsku! Arriba, abajo, al centro y pa' dentro!";
			link.l1 = "Za pokój... (pije)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha! Kubański rum jest naprawdę najlepszy na Karaibach...";
			link.l1 = "Zgadzam się. Powiedz mi, czy próbowali cię ukarać za to, że zostałeś schwytany w St. Pierre?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Na szczęście dostałem tylko po łapach. Tamta katastrofa to już przeszłość. W końcu tutaj, w koloniach, potrzebują oficerów.";
			link.l1 = "A twój dowódca... jak on się nazywał... Diego, prawda? Jak się dla niego zakończył ten jałowy najazd? Został zdegradowany?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "O, nie! Nasz drogi Diego de Montoya jest nietykalny, dopóki stoi za nim Don Ramon de Mendosa y Riba. Przy okazji, Don Diego był wczoraj w Santiago. Przybył z San Jose.";
			link.l1 = "Nie mów? Intrygujące! Dobrze, że nie spotkaliśmy się na ulicy. Obawiam się, że ta sprawa mogłaby się skończyć pojedynkiem, haha!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diego nie ma teraz dla ciebie czasu, kapitanie. Stawka jest dla niego zbyt wysoka, by ryzykować życie w pojedynku. Opracował jakiś plan razem z Baronem Mendosą na Zachodnim Wybrzeżu. Zebrał eskadrę w Hawanie i w każdej chwili może wyruszyć z powrotem do Hiszpanii.";
			link.l1 = "Jesteś też w jego załodze?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "Nie. Jutro wyjeżdżam do garnizonu w San Juan, który znajduje się w Puerto Rico. Na Providence nie jestem już mile widziany z Donem Mendosą.";
			link.l1 = "No cóż, wznieśmy toast za twój nowy przydział i oby czekały na ciebie tam tylko szczęśliwe chwile i piękne dziewczęta.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Wielkie dzięki, monsieur. Wszystkiego dobrego również dla ciebie. Ach, myślę, że czas na mnie. Skończę tego drinka i potem się z tobą pożegnam.";
			link.l1 = "Vaya con Dios, señor "+npchar.name+". Może spotkamy się ponownie w pokoju.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Tak jak ci powiedziałem, Don Diego: ryba wzięła przynętę; haczyk, żyłka i ciężarek... Och, wygląda na to, że znów się spotykamy, monsieur. Niestety, nie pod pokojowymi auspicjami, jakich chcieliśmy.";
			link.l1 = ""+npchar.name+"? Cóż! Nie spodziewałem się tego. Z jakiegoś powodu sądziłem, że jesteś uczciwym, szlachetnym oficerem. Okazuje się, że się myliłem.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "Co sprawia, że się mylisz? Dotrzymałem słowa, nie przysięgałem ci wiecznej przyjaźni. Nic się nie zmieniło, monsieur. Nadal jesteś wrogiem Hiszpanii i moim osobistym wrogiem. To nie jest Santiago, tutaj nie ma Ojca Vincento, a jego mały glejt bezpieczeństwa nie pomoże ci...";
			link.l1 = "O, tak to jest? Wydaje mi się, że prowadzenie przyjacielskiej rozmowy przy rumie, jednocześnie próbując wciągnąć mnie w pułapkę, jest dość zdradzieckie, nie sądzisz, señor "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Śmiesz nazywać mnie zdrajcą, ty maricon?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "Hej, ty! Tak, tak, ty! "+GetFullName(pchar)+"?";
			link.l1 = "Tak, kumplu. To ja.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "Mam list od ważnej osoby. Już wiesz, kto to jest.";
			link.l1 = "Wiem, daj to tutaj.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Oto i jest. Co powiesz na kilka monet za mój trud?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Weź trochę srebra. Uczciwie na nie zasłużyłeś.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Próbujesz mnie oszukać, kumplu? Już otrzymałeś zapłatę za dostawę.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Dzięki, chłopcze. Przyjemnie mieć do czynienia z hojnym dżentelmenem.";
			link.l1 = "Dobrze, zmykaj i ani słowa o tym, co się tu wydarzyło.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "Wilk z Hawany jest twoim przyjacielem...";
			link.l1 = "Co? Nadal tu jesteś...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Witaj na pokładzie 'Admirable', kapitanie "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! Zaskakujące. Czy mnie znasz?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Kto w koloniach francuskich nie słyszał o wielkim kapitanie imieniem "+GetFullName(pchar)+", ten, który wybił zęby hiszpańskiej eskadrze prowadzonej przez pancernik atakujący St. Pierre i zabił całą wrogą grupę napadu! Jesteś narodowym bohaterem!";
			link.l1 = "Och, daj spokój. 'Bohater'... Jestem tylko żołnierzem wypełniającym swój obowiązek wobec Francji.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Nie sądzę, by wielu żołnierzy zdołało zrobić to, co ty zrobiłeś, kapitanie... Eh, chciałbym cię poczęstować rumem w karczmie, ale niestety: kapitan zabronił ludziom pić choćby kroplę rumu i nie chcę dawać złego przykładu...";
			link.l1 = "Hm... Więc nie jesteś kapitanem samym w sobie?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "„Czy wyglądam na kapitana? Hoho! Nie, jestem tylko bosmanem. Nazywam się Serge Degas. Nasz kapitan, Gaius Marchais, spędza cały dzień w karczmie, podczas gdy my leżymy tu w oczekiwaniu na jakąś karawanę 'kupców'. Kapitan jest winien żołd marynarzom, i nam też, cała załoga jest kompletnie spłukana...”";
			link.l1 = "Co się stało? Hiszpańska karawana waniliowa nie pojawiła się, by oskubać jej pióra?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "Nie ma mowy! Nasz kapitan skończył z piractwem, gdy zdobył ten galeon. Widzisz, usłyszał, że karawana handlowa płynąca do Europy zatrzyma się wkrótce na Gwadelupie i będą kupować wanilię. Więc załadował nasze ładownie wanilią po brzegi w Bridgetown! Myślał, że będzie mógł sprzedać ją za trzysta peso za skrzynkę, tak, akurat!\nOczywiście, kiedy przybywamy, nie ma żadnej karawany waniliowej, a sprzedawanie wanilii tubylcom byłoby stratą. Więc oto jesteśmy, czekając na 'kupców', jestem pewien, że pojawią się tutaj za dzień lub trzy lata... Kapitan siedzi cały dzień w tawernie, będąc królewskim utrapieniem i dokuczając wszystkim. Wraca na statek tylko po to, by zemdleć. Teraz, wreszcie, jest gotów sprzedać za dwieście peso, tylko żeby wyjść na zero.\nWszystkie nasze pieniądze poszły na ten ładunek. Pewnego dnia załoga go zwiąże i sprzeda wanilię za grosze, tylko żeby pokryć nasze długi... Przysięgam, widzę, że to się stanie każdego dnia.";
			link.l1 = "Aj... co gryzie twojego kapitana?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Cóż, jeśli warto coś robić, to warto robić to dobrze. On nie robi ani jednego, ani drugiego. Jest okropnym negocjatorem. Byłoby inaczej, gdyby zajmował się również przewozem towarów, ale chciał poczuć się jak prawdziwy kupiec. Mam nadzieję, że pewnej nocy wypadnie za burtę...";
			link.l1 = "Zrozumiałem cię, Sergo. Nie martw się, jestem pewien, że pewnego dnia twoja... karawana się pojawi.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Och, nie wierzę w cuda, kapitanie. Może kiedyś znów się spotkamy i łyknie się rumu... co bym dał za trochę rumu teraz...";
			link.l1 = "Powodzenia, kamracie.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Eh, kapitanie, chętnie bym się napił rumu!";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho! Czyżbyś nie był z kupieckiego statku? Nie? Och, moje przeprosiny. Oczywiście, że nie... Mój błąd.","Nie jestem w nastroju, monsieur, więc znajdź sobie kogoś innego do rozmowy.","Ach, znowu ty?!","Ekhm...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nie martw się tym, kumplu. To się zdarza.","Napij się rumu, kapitanie. To trochę złagodzi twoje kłopoty...","Nie denerwuj się, kumplu. To niezdrowe.","Dobrze, dobrze. Już wychodzę.",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "A argh... Mm... Co do diabła, co to jest?..";
			link.l1 = "Cicho, kumplu... Nie rób hałasu...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Cóż? Co? Cholera!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah! Kimże jesteś? Czego chcesz ode mnie?";
			link.l1 = "Jeśli się nie zamkniesz, wybije ci zęby, kumasz? Gdzie są święte naczynia, które zabrałeś, gdy przejąłeś ten statek?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Jakie statki? Nie wiem, o czym mówisz! To jest mój statek!";
			link.l1 = "Twój statek? Jeszcze całkiem niedawno nazywał się 'Santa Margarita' i pływał pod hiszpańską banderą... Pytam cię, gdzie są te święte naczynia? Złoty monstrancja, krzyż inkrustowany lazurytem i złoty kadzielnica? Co z nimi zrobiłeś? Nie sprzedałeś ich, prawda?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "O Boże, nie wierzę własnym uszom... jesteś Hiszpanem? O, nie... nie jesteś Hiszpanem! Jesteś Francuzem! To jeszcze gorzej! Sprzedałeś się tym nikczemnym Kastylijczykom! Ile teraz płacą za dusze Francuzów? Nic ci nie powiem, zdrajco! Nie dostaniesz w swoje ręce tych błyskotek!";
			link.l1 = "Nie mówisz, co? Dla mnie to nie problem. To i tak nie najlepsze miejsce na przesłuchanie... Zatkamy ci usta, żebyś nie piszczał, a potem wsiądziemy do mojej szalupy... w końcu się rozgadasz, kamracie. Nie mam co do tego wątpliwości.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Ty hiszpański zdrajco! Lepiej...";
			link.l1 = "Milcz, łajdaku... Idź zaraz za mną, albo cię powalę i przeciągnę przez pokład za nogi.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "Jak mogę pomóc, panie?";
			link.l1 = "Jak się sprawy mają, kapitanie? Co cię sprowadza do Basse-Terre? O ile rozumiem, jesteś Hiszpanem pływającym pod holenderską banderą?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "Jaki problem, sir? Tak, jestem Hiszpanem. To łatwo wywnioskować po imieniu i rodzaju mojego statku, ale jestem tu dość legalnie. Mam licencję od Holenderskiej Kompanii Zachodnioindyjskiej, więc...";
			link.l1 = "Nie denerwuj się, señor! Jesteśmy naprawdę bardzo zadowoleni, że jesteś Hiszpanem... Powiedz mi, jesteś tu na import czy eksport?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "Przywiozłem towar z Hawany i sprzedałem go na lokalnym rynku. Teraz czekam na jakiś zyskowny fracht, aby nie wracać do domu z pustym ładownią.";
			link.l1 = "Panie, mam dla ciebie propozycję biznesową! Możesz zarobić dobre pieniądze, jeśli mi pomożesz. Czy możemy to omówić? Jak się nazywasz, przy okazji?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Kapitan Carlos Guevara. Jaka jest twoja oferta?";
			link.l1 = "Muszę zakupić partię wanilii i wysłać ją na Kubę, do człowieka o imieniu "+pchar.questTemp.Guardoftruth.LMname+", latarnik latarni morskiej w Santiago. Jednak mam poważny problem. Przede wszystkim, żaden sklep nie ma ilości wanilii, której potrzebuję...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "Po drugie, muszę natychmiast wyruszyć na St. Christopher i nie wiem, jak długo mnie nie będzie. Tracę pieniądze każdego dnia, rozumiesz? To przeklęty wstyd!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Rozumiem. Que lastima, senor. Nie można przecież zarobić wszystkich pieniędzy na świecie. Czego więc ode mnie chcesz?";
			link.l1 = "Spójrz tam. Widzisz ten galeon? Jest napakowany wanilią, której bardzo potrzebuję. Problem w tym, że kapitan galeonu wbił sobie do głowy jakieś bzdury o karawanie przypraw, która wkrótce tu przybędzie i kupi jego ładunek z zyskiem, prawie trzysta pesos za skrzynię!";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Tak, w dzisiejszych czasach jest wielu naiwnych ludzi, głupiec i jego pieniądze szybko się rozstają...";
			link.l1 = " Naiwny to jedno, ale on jest po prostu kompletnie głupi! Zaproponowałem kupno jego wanilii za dwieście dziesięć pesos, tutaj nie dostanie za nią nawet dwustu w sklepie. I czy możesz w to uwierzyć, powiedział mi, żebym się odczepił! Powiedział, że sprzeda tylko za dwieście pięćdziesiąt!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Haha! Co za idiota!";
			link.l1 = "Tak! To w zasadzie to, co mu powiedziałem. Oczywiście, że się na mnie wkurzył... ale naprawdę potrzebuję tej wanilii! Oto moja propozycja, seniorze. Nie jestem kupcem, ale myślę, że jesteś prawdziwym mistrzem sztuki handlu. I masz pojemny ładownię...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Namów tego przeklętego głupca, by sprzedał ci ładunek. Mnie już go nie sprzeda, po tym jak go obraziłem w twarz. Jestem gotów zapłacić dwieście dziesięć pesos za skrzynię. Jeśli zbijeżesz cenę, różnicę zatrzymaj dla siebie. A za to wynajmę twój statek, by dostarczył wanilię do Santiago.";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Ile jesteś gotów mi zapłacić za ten ładunek?";
			link.l1 = "Ile chcesz?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago jest całkiem daleko...trzydzieści tysięcy pesos.";
			link.l1 = "To za dużo, amigo. Spotkajmy się w połowie drogi.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "Dobrze, i tak jest to po drodze...Dwadzieścia pięć tysięcy i ani peso mniej.";
			link.l1 = "To dobrze. Kapitan galeonu nazywa się Gaius Marchais. Cały dzień spędza, dąsając się w tawernie. Mam nadzieję, że uda ci się go przekonać, by rozstał się ze swoimi przyprawami.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "Robiłem interesy z większymi imbecylami wcześniej. Opowiem mu wszystkie szczegóły o tym, kto rozpuszcza plotki o karawanie, która rzekomo miała kupić towar po niebotycznych cenach. Gdy już go przekonam, że to wszystko wymysł jego wyobraźni, sprzeda, jestem tego pewien.";
			link.l1 = "Więc mamy umowę?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Mamy umowę, jeśli masz gotówkę na zapłatę za wanilię i transport. Jak mówi urocze irlandzkie powiedzenie: 'Pokaż mi pieniądze.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Proszę, spójrz. Wszystko jest tutaj.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Mam srebro na moim statku. Pójdę je zabrać i zaraz wracam!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Czy przyniosłeś pieniądze?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Proszę bardzo, spójrz. Wszystko jest tutaj.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Już to załatwiam!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Świetnie! Lubię robić interesy z rozsądnymi partnerami. Wróć "+sTemp+" do dziesiątej rano. Myślę, że do tego czasu nasz wspólny przyjaciel Gaius oprzytomnieje.";
				link.l1 = "Świetnie! Do zobaczenia później!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Estupendo! Cieszę się, że mogę robić interesy z rozsądnymi partnerami. Wyruszam na brzeg. Wróć za trzy godziny. Myślę, że do tego czasu nasz wspólny przyjaciel Gajusz odzyska rozum...";
				link.l1 = "Świetnie! Do zobaczenia później!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Panie, dobrze pamiętam moją rolę. Nie martw się, może być twardym orzechem do zgryzienia, ale ja go rozłupię.";
			link.l1 = "Dziękuję.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "To zrobione, señor. Biedak był zachwycony, że chciałem kupić jego wanilię. Ręce trzęsły się mu ze szczęścia, gdy liczyłem zaliczkę - a może to po prostu przez rum. Załadujemy towar na plaży Capster jutro w południe, aby uniknąć niechcianej uwagi celników w porcie\nWypłynę natychmiast do Santiago, jak tylko towar będzie na pokładzie. Skontaktuję się z Twoim partnerem przy latarni morskiej i po dostarczeniu przekażę mu wanilię. Czy chcesz, abym przekazał mu jakąś wiadomość?";
			link.l1 = "Tak. Oto list. Mówisz, że transakcja odbędzie się na plaży Capster jutro w południe? Dobrze, więc zacumuję tuż przy cyplu, niedostępny dla wyspy na wypadek, gdyby coś się wydarzyło.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "Możesz mi zaufać, señor. Jestem uczciwym człowiekiem. Poza tym, nie mam ochoty się z tobą kłócić, a kupiec jest niczym bez swojej reputacji. Ale jeśli chcesz zobaczyć i zweryfikować, to dla mnie żaden trud.";
			link.l1 = "Jestem wdzięczny, señor. Jutro będę miał oko na tę umowę, a jak tylko odpłyniesz, zajmę się swoimi sprawami na St. Christopher.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Kapitanie, zapewniam cię: nie zawiodę cię i spełnię warunki naszej umowy w pełni.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hiic! H-hura! Stary dobry kapitan w końcu wypłacił nam naszą zapłatę! Trzy razy hurra dla kapitana! Hic!","To w pintach?! Biorę jedną!","Niech nasze sakiewki będą tłuste, a nasze dziewki jeszcze tłustsze! Hurra!","I tam leżeli, wszyscy dobrzy martwi ludzie, hic! Jak o świcie w knajpie pijackiej. Jo ho ho i butelka rumu!","Yo ho ho i butelka rumu!");
			link.l1 = LinkRandPhrase("Tak, kumplu.","Czy nie sądzisz, że już wystarczy ci rumu?","Pij i diabeł załatwił resztę...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Stój! Kto tam idzie? Alarm! Odeprzeć abordaż!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Har har! Też przyszedłeś po skarb Rollie'ego Kapitana, co? Szukaliśmy i szukaliśmy, i szukaliśmy, ale nie mogliśmy go znaleźć. Mam nadzieję, że przynajmniej jeden z tych imbecyli wpadnie na pomysł, żeby przepłynąć za wodospad na półkę!";
			link.l1 = "Jesteś jednym z ludzi pułkownika Foxa, prawda?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Mogę mieć powiązania z Morskimi Lisami. Nie musisz wiedzieć, nie ma sensu. Nie musisz teraz nic wiedzieć. Znalazłeś mój skarb, za co teraz jesteśmy ci ogromnie wdzięczni...";
			link.l1 = "Widzę. Nie jesteś Morskim Lisem, bardziej morskim psem... albo szakalem. Co ci bardziej pasuje?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Wygląda na to, że mamy do czynienia z prawdziwym filozofem przyrody, chłopcy. Prawdziwy ekspert w królestwie zwierząt!";
			link.l1 = "Czy chcesz sprawdzić ostrość mojej szabli, szakalu?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", señor. Jak mogę ci pomóc?";
			link.l1 = "Czy jest Pani Donna Belinda de Ribero?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Tak, to ja. Z kim mam zaszczyt rozmawiać?";
			link.l1 = "Kapitanie "+GetFullName(pchar)+", madame. Proszę się nie zrażać moim francuskim nazwiskiem, w tej chwili wykonuję zadanie od Jego Czcigodności Inkwizytora z Santiago, Ojca Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Que interesante! Słyszałem, że Święte Oficjum i Towarzystwo Jezusowe są pełne wielkiej rzeszy ludzi, z różnych klas i narodowości, ale nigdy wcześniej nie spotkałem osobiście cudzoziemca pracującego dla nich. Co mogę dla ciebie zrobić, señor?";
			link.l1 = "Posiadasz przedmiot, którym bardzo interesuje się Ojciec Rewident. Złotą monstrancję, którą niedawno nabyłeś od bankiera w Willemstad.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Jesteś dobrze poinformowany, señor. Cóż, wiedząc dla kogo pracujesz, nie powinienem się dziwić. Tak, kupiłem monstrancję, z pewnością nie powinna była leżeć w sklepie kupca obok skradzionych błyskotek i zastawionych towarów jak jakaś drobnostka.";
			link.l1 = "Czy masz monstrancję, pani?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Tak. Zamierzałem podarować go naszemu kościołowi parafialnemu, ale tyle mnie tu spotkało... Nie mogłem... ach, przepraszam...";
			link.l1 = "Czy płaczesz, pani? Czy moje słowa przyniosły ci smutek? Jeśli tak, proszę wybacz mi.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Och, proszę senor... Wróćmy do naszej rozmowy. Jak rozumiem, ojciec Vincento potrzebuje tej monstrancji? Chciałbyś, abym ci ją dał?";
			link.l1 = "Ten cenny naczynie było przeznaczone dla katedry w Santiago, ale zostało zagarnięte przez pospolitego pirata i sprzedane lichwiarzowi wraz z kilkoma innymi świętymi przedmiotami. Moim zadaniem jest zwrócenie tego, co zostało skradzione, tam gdzie należy. Oczywiście, w pełni zrekompensuję twoje wydatki.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Och, nie wolno ci! Czy naprawdę myślisz, że te pieniądze tak wiele dla mnie znaczą? Kupiłem tę monstrancję dla Świętej Matki Kościoła i nie zawaham się przekazać jej prawdziwemu właścicielowi, nie wspominając już o członku Towarzystwa Jezusowego służącym Ojcu Vincento. Ale, inna rzecz głęboko mnie niepokoi. Czy mógłbyś pomóc wiernej córce Kościoła w jej potrzebie?";
			link.l1 = "Jesteś szlachetną damą, madame. Jakie troski cię dręczą? Jak mogę pomóc?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Och, ale señor... Nie śmiałbym prosić samego brata jezuitę o pomoc. Zawsze jesteście tacy zajęci...";
			link.l1 = "Już to zrobiłeś. O co chodzi?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Czy możesz mi obiecać, jako przedstawiciel Świętego Kościoła, że nikt nigdy nie dowie się, o co cię proszę?";
			link.l1 = "Przysięgam ci na mój honor, senoro. Nie jest to pieczęć spowiedzi, ale nie pisnę o tym słówka żadnej duszy.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Bardzo dobrze. Ufam ci. Mój bardzo drogi przyjaciel Esteban Sosa wpadł w kłopoty. Został schwytany przez bandytów podczas podróży i żądają okupu w wysokości stu tysięcy peso. Nie posiadam takiej sumy pieniędzy i udało mi się zebrać tylko około połowy kwoty z mojego zasiłku. Nie mogę prosić nikogo o pomoc w tej sprawie, ponieważ przysięgli, że go zabiją, jeśli to zrobię\nPoza tym martwię się o mojego drogiego... przyjaciela i boję się najgorszego. Mogą go zabić, gdy tylko otrzymają pieniądze, aby upewnić się, że nie powie strażom o nich. Być może ty, odważny kapitanie, chrześcijaninie i bracie Towarzystwa, mógłbyś przekonać bandytów, aby przyjęli pieniądze, które mam, i nie skrzywdzili go...";
			link.l1 = "Kiedy i gdzie odbędzie się wymiana?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Ich herszt to jakiś człowiek o imieniu Bartie Rzeźnik. Powiedział, że będzie czekał na okup za Estebana każdej nocy od jedenastej wieczorem do północy przy wejściu do jaskini w dżungli...";
			link.l1 = "To są niezwykle specyficzne warunki...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Widocznie chcieli, żebym szybko zebrał cały okup i nie chciał, żebym kogokolwiek prosił o pomoc... ale ja nie znajdę takich pieniędzy, nigdy nie dam rady!";
			link.l1 = "Nie płacz, pani. Postaram się pomóc. Brat Towarzystwa Jezusowego nigdy nie zostawiłby prawej chrześcijańskiej kobiety w niebezpieczeństwie.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Muszę pokładać wiarę w tobie... Ale kapitanie, Bartie Rozpruwacz również powiedział, że jeśli nosiciel okupu nie przyjdzie sam lub jeśli pójdę do straży, natychmiast zabije biednego Estabana!";
			link.l1 = "Będę mieć to na uwadze.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Proszę, weź to. To pięćdziesiąt tysięcy pesos, które udało mi się zebrać. Przekonaj tych brigandos, by przynajmniej to przyjęli. Powiedz im, że nie mam ani jednego peso więcej! Sprowadź Estebana z powrotem! Gdy to zrobisz, z radością dam ci monstrancję dla Ojca Vincento.";
			link.l1 = "Zrobię wszystko, co w mojej mocy, pani. Miejmy nadzieję na najlepsze.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Niech Bóg cię wspiera, odważny kapitanie! Będę się za ciebie modlić!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Masz jakieś wieści, kapitanie?";
			link.l1 = "Jeszcze nie. Poczekaj, señora. Nie zawiodę cię.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Masz jakieś nowiny, kapitanie?";
			link.l1 = "Tak, señora. Obawiam się, że to nie są dobre wieści.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Powiedz mi, nie każ mi czekać! Czy spotkałeś się z bandytami?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Proszę, weź swoje pięćdziesiąt tysięcy z powrotem. Nie były mi potrzebne. Weź także ten pierścień. Wierzę, że znajdziesz go znajomym.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Masz, weź ten pierścień. Myślę, że wyda ci się znajomy.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "To... tak, jest znajome. Co się stało z Estebanem?";
			link.l1 = "Znalazłem zbójców w jaskini, tak jak mi kazałeś. 'Bartie Rozpruwacz' i Esteban Sosa to ta sama osoba. Zainscenował porwanie, by cię szantażować. Opowiedział mi o waszym... związku. Powiedział też, że nie chce cię więcej widzieć. Wziąłem pierścień, który mu dałeś jako dowód.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "To... tak, tak, wiem to. Co się stało z Estebanem?";
			link.l1 = "Znalazłem zbójów przy jaskini, tak jak mi powiedziałeś. Napadli mnie, związali i zabrali twoje pieniądze. 'Bartie Rzeźnik' i Esteban Sosa to ta sama osoba. Zaaranżował porwanie, by cię szantażować. Powiedział mi o waszym... związku. Esteban mnie puścił i dał mi ten pierścień jako dowód. Powiedział, że nigdy więcej go nie zobaczysz.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "Dios mio! Nie wierzę własnym uszom! Dlaczego to wszystko dzieje się ze mną, dlaczego?! Co ja zrobiłem, żeby on...";
			link.l1 = "Senora, błagam cię, nie zadręczaj się tym. Ten łajdak nie jest wart ani jednej twojej łzy. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "Och... Spróbuję się uspokoić. Señor, muszę ci podziękować za pomoc. Oto, weź swoje monstrancjum. "+sTemp+"Idź z Bogiem.";
			link.l1 = "Gracias, senora. Nie martw się, nikt się nie dowie o tym, co się stało w jaskini. My, jezuici, zawsze dotrzymujemy słowa. A teraz, jeśli pozwolisz, muszę iść.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Stójże tam, kamracie!";
			link.l1 = "Stoję właśnie tutaj.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Czy przyniosłeś pieniądze?";
			link.l1 = "Co za głupie pytanie. Nie, przyszedłem tutaj, żeby zbierać Manga Rosas... Dlaczego myślisz, że w ogóle bym tu przyszedł?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "O ho ho! Komik! Do jaskini z tobą, Bartie już na ciebie czeka.";
			link.l1 = "Widać, żeś doświadczonym strażnikiem... z taką postawą mógłbyś strzec samego króla Filipa. Sam się wprowadzę.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "Trzymałeś mnie w oczekiwaniu... Masz pieniądze ze sobą?";
			link.l1 = "Czyżbyś był Bartie Rozpruwaczem? Nie wyglądasz mi na pospolitego bandytę.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Dlaczego cię obchodzi, jak wyglądam? Masz te cholernie pieniądze, czy nie?";
			link.l1 = "Gdzie jest zakładnik?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Dostaniesz swojego zakładnika. No dalej, dawaj mi monety. Nie denerwuj mnie, chłopcze.";
			link.l1 = "Bartie, czy wyglądam na głupca? Dopóki nie zobaczę Estebana Sosy żywego i kopiącego, nie zobaczysz ani jednego peso. Gdzie on jest?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "O, stawiasz opór, co? Dobrze, nauczymy cię porządnej lekcji... Chłopcy, rozerwijmy temu gnojkowi nową dziurę!";
			link.l1 = "Drań!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Czy wystarczy ci już tańców? Gdzie jest Esteban Sosa? No dalej, mów, albo przytrzymam twoją głowę pod wodą, aż przestaną lecieć bąbelki!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "Nie... Nie krzywdź mnie, proszę! Jestem Esteban Sosa.";
			link.l1 = "Co?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Tak, tak. Nie jestem Bartie Knacker. Jestem tylko...";
			link.l1 = "Ty łajdaku! Więc postanowiłeś wyciągnąć sto tysięcy pesos od Senory de Ribero, 'porywając' samego siebie?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Musisz mnie zrozumieć, mężczyzna do mężczyzny. Belinda... Naprawdę mnie odpycha swoim obsesyjnym uczuciem. Jest przy mnie cały czas, dzień i noc, człowieku! Nawet jej mąż zaczął podejrzewać coś między nami, a jest na wpół ślepy!";
			link.l1 = "Cóż, co powiesz na to! Więc jesteście kochankami?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Już nie. Właśnie od niej uciekłem.";
			link.l1 = "A ty postanowiłeś zabrać parę monet na drogę, co? No cóż, co ja mam teraz z tobą zrobić? Ukryć twoje ciało w dżungli, tak jak ty próbowałeś ze mną?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "Nie! Nie chciałem żadnej krwi, przysięgam!";
			link.l1 = "To dlatego poszczułeś na mnie swoje psy?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Mieliśmy tylko zamiar przeszukać twoje kieszenie, i tyle!";
			link.l1 = "A zostawić mnie nagiego w dżungli? Powinienem cię powiesić na najwyższym gaflu mojego statku, łotrze! Ale tego nie zrobię, wyłącznie z szacunku do dobrej kobiety, która miała nieszczęście z tobą się związać. Wiesz co? Powinienem cię do niej zaprowadzić i pozwolić jej zdecydować, co z tobą zrobić.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "Nie, tylko nie to! Nie wracam do Cumany!";
			link.l1 = "Chciałbyś raczej zostać w tej jaskini na zawsze?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Daruj mi, señor! Pozwól mi odejść, a odpłynę stąd i nigdy więcej nie wrócę do Cumany! Nie zamierzam czekać, aż mąż Belindy rozszarpie mnie na kawałki w pojedynku lub nasła na mnie zabójcę!";
			link.l1 = "Dobrze. Ze względu na Senorę de Ribero, nie zamierzam cię do niej przyprowadzać. Ale nie myśl przez chwilę, że to wszystko zostanie zamiecione pod dywan. Dowie się o tym żałosnym kawałku gówna, z którym postanowiła flirtować. Jakie masz znaki rozpoznawcze, które mogłaby zidentyfikować?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Tu. Ten turkusowy pierścień tutaj. Sama mi go dała.";
			link.l1 = "Doskonale. Daj to tutaj i znikaj z mojego pola widzenia!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Idealnie. I wiesz, Sosa, zmieniłem zdanie - teraz służę Towarzystwu Jezusowemu. Jak mówi Pismo, 'Musisz usunąć złego człowieka spośród siebie.' A ty jesteś nikczemnym narcyzem, przestępcą i bezużytecznym kawałkiem gówna. Myślę, że utopię cię w tej jaskini. Requiesce in pace.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "Masz to, czego potrzebujemy, kamracie...";
			link.l1 = "Naprawdę? A co by to miało być?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Nie pytałem, bogaczu. Otrzymałem rozkaz zabrać twoje rzeczy, absolutnie wszystko, co masz przy sobie. Zrobimy to po dobroci czy po złości? Wybór należy do ciebie.";
			link.l1 = "Myślisz, żeś wojownik, co? Nie masz pojęcia, z kim masz do czynienia. Takie łajzy jak ty zjadam na śniadanie.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Jesteś prawdziwym błaznem, prawda, żabko? No to zobaczmy, jak twoja krew wygląda na ziemi!";
			link.l1 = "Będzie wyglądać tak samo jak twój, idioto. Pozwól, że zafunduję ci lekcję anatomii!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, dobrze kumplu... Wywracaj kieszenie na drugą stronę i to szybko! Jak będziesz grzeczny i posłuszny, to zostaniesz w jednym kawałku, rozumiesz?";
			link.l1 = "Cholera, znowu wy? Też przybyliście aż tutaj? Kto do diabła was zatrudnił?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "To nie twoja sprawa. Poddaj się teraz i żyj, albo staw czoła walce, a my po prostu zabierzemy twoje łupy z twojego martwego ciała. Jak ci się podoba taka umowa?";
			link.l1 = "Mam kontrpropozycję. Co powiesz na to, że zabiorę twój łup z twojego martwego ciała?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Oczekuję rozkazów, kapitanie!";
			link.l1 = "Przemierzajcie dżunglę w kierunku Przylądka San Antonio. Weźcie ścieżkę w lewo i idźcie prosto. Trzymajcie głowy nisko i przygotujcie się na zasadzkę na brzegu. Bądźcie gotowi. Ja popłynę tam drogą morską i spotkam się z wami. Jak długo wam to zajmie?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Będziemy tam za sześć godzin, kapitanie!";
			link.l1 = "Dobrze. Ruszaj się!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "Uparty drań! Wciąż żyje... Wiedziałem, że powinniśmy użyć więcej prochu! Dobra, skończę z tobą, ty sukinsynu...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
