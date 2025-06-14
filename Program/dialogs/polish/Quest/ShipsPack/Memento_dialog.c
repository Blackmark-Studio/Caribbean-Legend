void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Czego pan chce?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;

		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Kapitanie, dzień należy do nas. Awangarda kończy czyszczenie dolnego pokładu. Nie ma jeńców... Ba! Widzę, że pan też się nie cackał.";
			link.l1 = "Jakoś oczekiwałem"+GetSexPhrase("","a")+" od niego pompatycznej przemowy. A on od razu rzucił się do walki.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Czy mogę się wypowiedzieć?";
			link.l1 = "Zezwalam.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "Nie, tutaj skończyliśmy.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Po co ich zaatakowaliśmy? Ten bryg nie stanowił dla nas żadnego zagrożenia, nie przewoził towarów. O Grimie krążyły różne plotki, ale bali się go tylko handlarze żywym towarem. Dziś zginęło mnóstwo ludzi - i nie wiadomo po co.";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Mówisz teraz w imieniu załogi?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;
		
		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "I to już nie pierwszy raz...";
			link.l1 = "Mówisz teraz w imieniu załogi?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;

		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Nie. Proszę mi wierzyć, gdyby załoga miała tego rodzaju pytania, to znaczyłoby, że źle wykonuję swoją pracę, a pan byłby już martwy, kapitanie\n"+
			"Na szczęście dla pana, ludzie dobrze zarobili na tej krwawej awanturze. Kieszenie każdego marynarza na tym statku są wypchane dublonami po brzegi!\n"+
			"Nie było żadnego cennego ładunku – tylko tubylcze świecidełka i upiorne amulety. Ale i tak ludzie się obłowili. Grim musiał dobrze im płacić\n"+
			"Mam nadzieję, że nie zamierza pan rościć sobie prawa do części tego złota, kapitanie?";
			link.l1 = "Nie zamierzam, Alonso. Dzięki, że mnie informujesz.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Oczywiście, że zamierzam. Dopilnuj, by moja część trafiła do kajuty.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Zawsze jestem po pańskiej stronie, kapitanie. A tak przy okazji – co zamierza pan zrobić z 'Memento'?";
			link.l1 = "Wezmę jako zdobycz – a jakże?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Jeszcze nie zdecydował"+GetSexPhrase("em","am")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Zawsze jestem po pańskiej stronie, kapitanie. A tak przy okazji – co zamierza pan zrobić z 'Memento'?";
			link.l1 = "Wezmę jako zdobycz – a jakże?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Jeszcze nie zdecydował"+GetSexPhrase("em","am")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;
		
		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Lepiej nie warto. Jest cały obwieszony jakimiś tubylczymi symbolami. I krążą o nim złe plotki – mówią, że przetrwał kiedyś potworną epidemię i że na pokładach to prawie umarli tańczyli\n"+
			"O szkielecie na rufie nawet nie wspomnę: dopóki jakiś idiota nie odważy się buchnąć czaszki dla zabawy – nikt oprócz mnie długo nie odważy się trzymać wachty na rufie.";
			link.l1 = "Przyjąłem do wiadomości, Alonso. Wracaj do pracy.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;

		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Tak jest, kapitanie.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;

		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Kapitanie, przepraszam, że przeszkadzam o takiej porze.";
			link.l1 = "Zgłaszaj, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Kapitanie? Co pan tutaj robi? Spał pan tutaj?";
				link.l1 = "Nieważne.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "W mojej kajucie jakoś... nieswojo.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Nasze sprawy mają się kiepsko. Nastroje załogi – fatalne! Ludzie już otwarcie mówią, że statek jest przeklęty. Skarżą się, że coś im się roi po nocach.";
			link.l1 = "Co dokładnie im się roi?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Jakieś koszmary. Ale najgorsze jest to, że jeden z naszych ludzi zmarł na febrę. Młody chłopak, okaz zdrowia – a spłonął w kilka godzin.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "To już decyzja lekarza. "+sld.name+" zna się na swoim fachu.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "To niemożliwe. Trzymaj załogę w ryzach, Alonso. To twoja robota.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Tak jest!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Rozumiem. Wielu z załogi śpi teraz razem – boją się zostać sami. Można pomyśleć, że na tym statku w ogóle można być samemu…";
			link.l1 = "Jak widzisz, mnie się nie udało. Co się stało?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Bójka – José zasztyletował Marcela. Krzyczał, że tamten 'niesie zarazę'.";
			link.l1 = "Sytuacja się pogorszyła?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = "Przecież "+sld.name+" już rano o tym meldował. Straciliśmy jedenaście dusz. Co robimy?";
			}
			else
			{
				dialog.text = "Straciliśmy kolejne jedenaście dusz. Co robimy?";
			}
			link.l1 = "Podejmę decyzję.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Mam taką nadzieję, kapitanie. Co zrobimy z José? Zabójstwo to nie przelewki.";
			link.l1 = "Powiesić po szkłach. Pokażemy, że sytuacja jest pod kontrolą.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Trzydzieści batów. Przeżyje – znaczy Bóg tak chciał.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Tak jest!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Tak jest!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Kapitanie! Alarm!! Natychmiast proszę zejść na dolny pokład!";
			link.l1 = "Co się stało?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "Lepiej, żeby pan to sam zobaczył. Chodźmy, szybko!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;

		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Dzień dobry, kapitanie!";
			link.l1 = "A?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Eee, nie wygląda pan najlepiej. Zła noc? Nic nie szkodzi, zaraz się pan ucieszy. Epidemia ustała. A właściwie – jej w ogóle nie było.";
			link.l1 = "Jak to?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "Ludzie się nakręcili, nasłuchali się bzdur o przeklętym statku. Siła autosugestii to straszna rzecz, proszę mi wierzyć. Niejedną jednostkę już zatopiła.";
			link.l1 = "Ale przecież ludzie ginęli!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Walka, brudne rany, zepsuta solona wołowina — zwykła morska arytmetyka. Gdybyśmy się tak nie nakręcali opowieściami o przeklętych statkach, może byśmy stracili o dwóch ludzi mniej\n"+
			"Szkielet na rufie też nie pomagał. Dobrze, że jakiś… dowcipniś ukradł mu w nocy kapelusz\n"+
			"Ponieważ po takim bluźnierstwie statek nie został trafiony piorunem, załoga trochę się ożywiła i zaczęła knuć, jakby tu jeszcze bardziej drażnić szkielet. Na przykład...";
			link.l1 = "Nie ruszać szkieletu!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Eee... No, jeśli żywi pan do niego ciepłe uczucia, to oczywiście nie ruszymy. Miłego dnia, kapitanie\n"+
			"Przy okazji – świetny kapelusz! Bardzo panu pasuje. Poprzedni właściciel miał wyraźnie za małą głowę.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Witam, kapitanie. Powinien pan porozmawiać z kapitanem Grimem.";
				link.l1 = "Wybacz, marynarzu, ale tu się wyróżniasz.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Coś jeszcze, kapitanie?";
				link.l1 = "Nic.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "Rozumiem, kapitanie. Służyłem u wolnego kapitana — takiego jak pan. Szukał skarbów, handlował, brał frachty. Potem postanowił obrabować kupców — nie wyszło. Ocalałych skazano na szubienicę za piractwo.";
			link.l1 = "I kapitan Grim was wykupił?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "Kupił nas wszystkich naraz, jak towar. Każdy potrzebuje doświadczonych marynarzy, a kapitan Grim nie werbuje po tawernach... Ale karmi nas i dobrze płaci. A my służymy — i losujemy.";
			link.l1 = "Losujecie?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "Przepraszam, nie powinniśmy o tym rozmawiać.";
			link.l1 = "Dlaczego więc nie odejdziecie?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "Dokąd? Tu przynajmniej jest jakaś szansa. Może się poszczęści. Na każdym statku jest jakiś los. Grim ma swój, pan ma swój. Nie jesteśmy ludźmi, tylko numerami w dzienniku okrętowym.";
			link.l1 = "U mnie na statku obowiązują inne zasady.";
			link.l1.go = "Memento_Sailor_1_5";
		break;

		case "Memento_Sailor_1_5":
			dialog.text = "Jak pan sobie życzy, kapitanie. Miłego dnia.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Dawno nie było gości na naszym wspaniałym okręcie!";
				link.l1 = "Jesteś marynarzem? Nie wyglądasz.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Coś jeszcze, kapitanie?";
				link.l1 = "Nic.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;
		
		case "Memento_Sailor_2_1":
			dialog.text = "Ha! Kapitan wykupił mnie prosto z celi. Mieli mnie powiesić w Port Royal – zadźgałem jakiegoś młokosa, co tylko wiersze recytował. Zasłużył sobie, drań.";
			link.l1 = "Czyli miałeś szczęście?";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "Pewnie! Kapitan nie żałuje grosza, ale czasem trzeba brać udział w jego ... grach.";
			link.l1 = "Jakich grach?";
			link.l1.go = "Memento_Sailor_2_3";
		break;

		case "Memento_Sailor_2_3":
			dialog.text = "Co tydzień losujemy patyczki: krótki oznacza niebezpieczną robotę albo skok za burtę. Wesoło, no... Nie dla wszystkich, ale kapitan mówi, że tak odsiewa niegodnych.";
			link.l1 = "Niegodnych czego?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "Skąd mam wiedzieć? Kapitan to gaduła, gada jak ksiądz: 'Tylko poznawszy śmierć, można naprawdę żyć!'\n"+
			"(pluje)";
			link.l1 = "Za plucie na pokładzie jest bicz. Zachowujesz się jak bandyta, nie marynarz. Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Dzień dobry, kapitanie.";
				link.l1 = "Jak się tu znalazłeś?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Coś jeszcze, kapitanie?";
				link.l1 = "Nic.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "Kapitan Grim przejął statek niewolniczy, na którym byłem. Byłem wtedy chory, umierałem w ładowni ... niewiele pamiętam. Ocknąłem się już tutaj, na 'Memento'.";
			link.l1 = "A co stało się z innymi niewolnikami?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "Nie wiem. Kapitan mówi, że wszystkich uwolnił, ale tylko mnie zabrano na statek. Reszta pewnie rozbiegła się po wyspach albo zmarła z ran. Słabo pamiętam ten dzień.";
			link.l1 = "Za to jesteś wolny.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "Wolny? Tutaj nikt nie jest wolny. Kapitan daje złoto, jedzenie, ubrania, ale w zamian żąda pełnej lojalności — i organizuje ten straszny los.";
			link.l1 = "Los?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Co tydzień ktoś losuje krótki patyczek i dostaje niebezpieczne zadanie, z którego nie wszyscy wracają. Kapitan mówi: tak oddziela się żywych od martwych.";
			link.l1 = "I wy to znosicie?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "Każdy liczy na to, że mu się poszczęści. Kapitan potrafi znaleźć klucz do każdego: strach przed stryczkiem, chciwość, chęć spłaty długu za ocalenie. Mnie to nie interesuje. Pieniądze są mi zbędne, a dług... jaki może być dług za coś, czego się nie pamięta?";
			link.l1 = "Nie boisz się mówić o tym otwarcie?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "A co mi zrobią? To statek umarłych, kapitanie, i tu jest moje miejsce. A pan — nie.";
			link.l1 = "Jak uważasz. Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Witamy na pokładzie 'Memento', kapitanie.";
				link.l1 = "Hiszpański żołnierz na pirackim statku? To nietypowe.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Coś jeszcze, kapitanie?";
				link.l1 = "Nic.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		case "Memento_Sailor_4_1":
			dialog.text = "Jestem dezerterem. Kapitan Grim wykupił mnie prosto spod szubienicy na placu w San José. Zapłacił dużo – cały worek dublońców za moją zakurzoną skórę.";
			link.l1 = "Za co was skazano?";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "Oficer Saldo wysłał nas do pilnowania robotników w selwie, gdzie połowa umiera z gorączki w tydzień. Uznałem, że moje życie jest więcej warte. Teraz... służę temu, kto je wycenił na twardą monetę.";
			link.l1 = "Nie żałujecie?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "Szubienica i tak czeka... Kapitan jest hojny wobec wiernych. Choć czasem organizuje dziwne próby – losowanie. Nie każdemu się poszczęści.";
			link.l1 = "Losowanie?";
			link.l1.go = "Memento_Sailor_4_4";
		break;

		case "Memento_Sailor_4_4":
			dialog.text = "No wie pan. Jednemu przypadnie praca na masztach w czasie sztormu, innemu miejsce w awangardzie. Kapitan mówi, że tak się sprawdza gotowość. Nie wiem do czego, ale mam nadzieję, że mi się poszczęści.";
			link.l1 = "Powodzenia... chyba.";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "Dziękuję, kapitanie. Śmierć i tak każdego dopadnie.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Witamy na pokładzie 'Memento', kolego. Nazywam się Mortimer Grim.";
				link.l1 = "Kapitan "+GetFullName(pchar)+". Dziękuję za przyjęcie...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "O czym jeszcze porozmawiamy?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Ma pan wspaniały miecz, kapitanie.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Pańska luneta doskonale komponuje się ze szkieletem.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Muszę przyznać, że ma pan bardzo różnorodną załogę.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Nic... kolego. Pomyślnych wiatrów.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "Karaiby są hojne dla tych, którzy śpieszą na szafot — wiem coś o tym.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;

		case "Memento_MortimerGrim_3":
			dialog.text = "Tak? Chciał pan o coś zapytać?";
			link.l1 = "Za panem wisi szkielet.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Dziś piękny wiatr, prawda? I pogoda świetna.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "Jaki szkielet? Za mną jest tylko błękitne Morze Karaibskie.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "Zgadzam się, kolego. Oby każdy dzień był taki!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "Ha ha ha! Ten żart nigdy się nie starzeje! Proszę się nie bać: stary Yorick, tak jak ten statek, to pamiątka z mojego poprzedniego życia. Dosłownie, oczywiście.";
			link.l1 = "«Oczywiście»?";
			link.l1.go = "Memento_MortimerGrim_7";
		break;
		
		case "Memento_MortimerGrim_7":
			dialog.text = "Kolego, czy boisz się śmierci? To nie groźba, naprawdę jestem ciekaw.";
			link.l1 = "Oczywiście. Kto twierdzi inaczej, ten kłamie.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "Nie. Wszyscy tam trafimy.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "A pan?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;

		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "O! Śmierć to matka wszelkich lęków. Samotności, ciemności czy kary — to tylko jej maski.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "O! Śmierć to matka wszelkich lęków. Samotności, ciemności czy kary — to tylko jej maski.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "O! Śmierć to matka wszelkich lęków. Samotności, ciemności czy kary — to tylko jej maski.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "Po co szukać daleko? Weźmy starego Yoricka: kupa kości z latarnią w żebrach — a nawet tak groźnego kapitana jak ty potrafił wystraszyć!";
			if (startHeroType == 4)
			{
				dialog.text = "Po co szukać daleko? Weźmy starego Yoricka: kupa kości z latarnią w żebrach — a nawet nieustraszoną Elen, córkę wielkiego Shawna MacArthura, potrafił wystraszyć!";
			}
			link.l1 = "Ładnie pan mówi, ale nie powiedział, co z tym wszystkim zrobić.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "Ja znam odpowiedź, ale moje lekarstwo nie każdemu pasuje. Można spróbować w każdej chwili, ale najpierw powiedz, co sam o tym myślisz.";
			link.l1 = "Biblia mówi, że śmierci nie ma.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Jeśli zacznę się bać — statek zginie.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "Odpowiedź utonęła na dnie butelki rumu.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;

		case "Memento_MortimerGrim_11_1":
			dialog.text = "To prawda. Jedyna rzecz, z którą zgadzam się w tej księdze.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_11_2":
			dialog.text = "Godne pochwały. Ale niepotrzebnie się niepokoisz: śmierci nie ma.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "Jo-ho-ho! Cynik. Ale i bez rumu powiem: śmierci nie ma.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "To proste: prawdziwe życie zaczyna się dopiero wtedy, gdy pokonasz śmierć. Byłem tam, za zasłoną, i wierz mi — naprawdę zacząłem żyć dopiero teraz.";
			link.l1 = "Słucham?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "Nieważne, kolego.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Miło, że pan zauważył, kolego! Nie jestem pozerski, ale jaki ze mnie pirat bez budzącego grozę kordelasa?";
			link.l1 = "Czy to naprawdę ważne?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;

		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "A jakże! Jedyny raz, kiedy mocno naruszyłem okrętowy budżet dla osobistych celów, to właśnie ten miecz. Dwa tysiące złotych dublońców, kolego! Diabli, gdybym mógł powstać z grobu drugi raz, to ożyłbym samą jego ceną!\n"+
		"Broń, nawiasem mówiąc, doskonała. Ale jakby czegoś jej brakowało...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Prezent od pewnej osoby. Wspaniały rozmówca, rozumiejący śmierć jak nikt inny — i z doskonałą wyobraźnią, co sam pan widzi.";
			link.l1 = "Wygląda upiornie.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, kolego.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Moja załoga ma ze sobą znacznie więcej wspólnego niż, powiedzmy, twoja... Wszyscy zostali przeze mnie wybawieni ze stryczka i kajdan, każdy z nich poczuł tchnienie śmierci. To doświadczenie łączy ludzi bardziej niż krew czy flaga.";
			link.l1 = "Więc nie rekrutujesz w tawernach, co?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;
		
		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Zdziwisz się, jak chętnie byli niewolnicy i skazańcy dołączają do załogi: zamienić ładownię handlarza ludźmi albo szafot na pokład 'Memento'? Na moim statku jest teraz 178 ludzi — i każdy z nich coś mi zawdzięcza.";
			link.l1 = "Ale przecież musisz jakoś płacić załodze i utrzymywać statek. Sama wdzięczność nie wystarczy.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Jestem skutecznym piratem, kolego. Prawdziwy 'hostis humanitatis'. Tak nazwaliby mnie prawdziwi wrogowie ludzkości — handlarze ludźmi i koronowane głowy. Różni ich tylko nazwa\n"+
		"Na szczęście mają mnóstwo złota. Monety z kufrów handlarzy ludźmi wydaję na ratowanie tych, których korona skazała na śmierć. Resztę oddaję załodze — a sam niczego nie potrzebuję. Po co umarłym złoto? Wkrótce to zrozumieją...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;

		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "Takie to u nas gówniane sprawy, kapitanie.";
			link.l1 = "Co to ma być?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "Zostałeś sam. Choroba wszystkich wykończyła. Zawiodłeś nas.";
			link.l1 = "To niemożliwe!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "Sprowadziłeś nas na przeklęty statek.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "Sprowadziłeś na wszystkich śmierć!";
			link.l1 = "Alonso, co z tobą?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Czemu stanąłeś, kolego? Zmieniłeś zdanie? To po co był ten atak?";
			link.l1 = "Grim? Przecież ty nie żyjesz!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ha! Co martwe, umrzeć nie może. Poza tym wyprzedzasz fakty: może i wygrałeś abordaż, ale czy przeżyjesz... zaraz się przekonamy!";
			link.l1 = "Ta walka skończyła się tygodnie temu! Ty nie żyjesz!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Teraz to już wszystko. Gratuluję zwycięstwa.";
			link.l1 = "Grim?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Wiesz, cieszę się. Naprawdę się cieszę, że mnie zabiłeś. Tak naprawdę.";
			link.l1 = "O czym ty mówisz?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Jestem tchórzem, kolego. Zwykłym, żałosnym tchórzem, który przestraszył się śmierci – jak tysiące innych ludzi przede mną. Gdy załoga zmarła na dżumę... i to z mojej winy, oszalałem ze strachu. Miesiąc dryfowałem sam na statku umarłych.";
			link.l1 = "Co tak naprawdę się wydarzyło?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Nie przeszedłem próby śmierci. Zamiast ją zaakceptować, przeżyć i wyciągnąć wnioski, zacząłem się jej jeszcze bardziej bać. I żeby zagłuszyć ten strach... zmuszałem innych, by przechodzili przez to samo, co ja.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;

		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Dziękuję ci, kolego. Za to, że uwolniłeś mnie od tego... istnienia. Teraz wiem na pewno, że śmierci nie ma. I już się nie boję. Nie ma kogo obwiniać ani zniewalać.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Nie rozdzielaj 'Memento' i jego kapitana. Mortimer… Kapitan Mortimer był dobrym człowiekiem. Znajdź go na Dominice. A statek… statek cię przyjmie.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, kolego. Umarli uczą żywych. Żegnaj.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 