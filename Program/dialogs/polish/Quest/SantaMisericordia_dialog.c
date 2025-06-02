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
			dialog.text = "Czego ci potrzeba?";
			link.l1 = "Mi? Niczego.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...i Ducha Świętego. Amen.";
			link.l1 = "Czy ja dobrze widzę? Wojskowy w kościele? Myślałem, że wojsko ma kapelanów, którzy zapewniają żołnierzom dostęp do wiary.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Czy to kapelan, czy to kościół - żadna w tym różnica. Co do mojej profesji... Wiele osób uważa, że wiara i miecz są niezgodne. Ale czyż chirurg nie tnie, aby leczyć? Czyż ojciec nie karze, aby chronić?";
			link.l1 = "Brzmi jak usprawiedliwienie.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "Jest w tym coś mądrego. Okrucieństwo jest czasem konieczne.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Jesteś w błędzie. To nie jest usprawiedliwienie - to zrozumienie. Kiedy po raz pierwszy rozpocząłem służbę, każda śmierć była... trudna. Ale potem... moje oczy się otworzyły. 'Okrucieństwo jest manifestacją najwyższej miłości.'";
			link.l1 = "Zostawię cię z twoimi modlitwami.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Tak... tak! Dokładnie tak powiedział ten, który prowadził mnie tą ścieżką. 'Miłosierdzie bez siły jest bezużyteczne, jak miecz bez ręki.'";
			link.l1 = "Zostawię cię z twoimi modlitwami.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Módl się za nas wszystkich. Za to, co robimy... i za to, co jeszcze musimy zrobić.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Siedem procent niedoboru. Ostatnim razem było pięć. Rosną jak chwasty w opuszczonym ogrodzie...";
			link.l1 = "Przepraszam, w mieście jest nowy gubernator?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "Co? Ach, nie. Jego Ekscelencja jest tam, w rogu. Jestem don Fernando de Alamida, królewski inspektor.";
			link.l1 = "To musi być ciężka praca.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Wiesz, co jest najtrudniejsze w walce z korupcją? Winni niekoniecznie są złymi ludźmi. Mają dzieci, rodziny. I za każdym razem musisz sobie przypominać: trucizna pozostaje trucizną, nawet podana w złotym kielichu.";
			link.l1 = "Ale czy można sądzić tak surowo? Wszyscy jesteśmy ludźmi...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Jesteś zbyt miękki. Tylko więzienie ich zreformuje.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "Miłosierdzie dla wilka jest okrucieństwem wobec owiec. Tak powiedział... mędrzec. I z każdym mijającym dniem, coraz bardziej rozumiem jego mądrość.";
			link.l1 = "Nie będę cię dłużej odciągał od pracy.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hm. Wiesz, kiedyś myślałem tak samo. Ale więzienie jest zbyt proste. Potrzeba czegoś więcej... Oczyszczenia.";
			link.l1 = "Nie będę cię dłużej odciągać od pracy.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Tak. Dokumenty nie będą czekać. Chociaż czasami wydaje mi się, że za każdą liczbą tutaj kryje się czyjś los.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Słucham uważnie, "+GetAddress_Form(NPChar)+"? Co sprawiło, że podszedłeś do mnie tak po prostu, na ulicy?";
			link.l1 = "Wyróżniasz się spośród reszty.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, królewski inspektor. Jesteś dziś pierwszym takim ciekawskim. Wszyscy się ukrywają, wszyscy się mnie boją. A jednak uczciwy człowiek nie ma się czego obawiać. Co nam to mówi?";
			link.l1 = "Że twoja reputacja ich przeraża?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Że uczciwych ludzi jest niewielu?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Zabawne. Też tak myślałem. Dopóki nie zrozumiałem - strach oczyszcza. Kiedy człowiek się boi, staje się bardziej szczery. Bliżej swojej prawdziwej natury. Do Boga.";
			link.l1 = "Interesująca myśl. Muszę iść. Dobrego dnia, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Interesujące... Rozumujesz dokładnie jak ktoś, kogo znałem. Szkoda, że nie każdy potrafi zaakceptować tę prawdę.";
			link.l1 = "Interesująca myśl. Muszę iść. Dobrego dnia, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Dobrego? Być może.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "Coś jeszcze, Kapitanie?";
			link.l1 = "Nie nie, don Fernando, chciałem się tylko przywitać, nic więcej.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Panienka z mieczem? Cóż, nigdy bym nie pomyślał, że przyjdzie mi dożyć takiego widoku. A kimże ty jesteś, señorita, by ośmielić się atakować 'Święte Miłosierdzie'?";
				link.l1 = "Kapitan Hellen McArthur. A to zaskoczenie na twej twarzy jest mi dobrze znane.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Ahh! Ty diable! Jak śmiesz?! Atakować 'Święte Miłosierdzie'?! Statek, który wypełnia wolę króla i... Cóż. Skoro już tu jesteś, powiedz mi - dlaczego? Dlaczego zdecydowałeś się na to szaleństwo?";
				link.l1 = "Jestem piratem. A twój galeon z pewnością pełen jest skarbów.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Jaki piękny statek... Muszę go zdobyć.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Jestem wrogiem twojego kraju, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Tak po prostu. Czemu nie?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Jakże mi przypominasz Dziewicę Maryję, opiekunkę naszego statku... Tak samo piękna. Ale Ona chroni sprawiedliwych, podczas gdy ty...";
			link.l1 = "Przyszłam po twój statek. A komplementy tu nie pomogą, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Jakie to smutne. Będę musiał nauczyć cię pokory. Siłą, skoro nie ma innego sposobu.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ach tak. Oczywiście. Złoto. Zawsze złoto. Trucizna, która koroduje dusze. Za nie zginiesz.";
			link.l1 = "Nie bądź taki dramatyczny. To tylko interesy.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Każda moneta w ładowni to zapłata grzeszników za oczyszczenie. Chcesz je? To podziel ich los.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Wielu już pragnęło 'Świętego Miłosierdzia'. Jej piękno było zgubą niejednego kapitana.";
			link.l1 = "W takim razie będę pierwszym, który ją zdobędzie.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "Miłosierdzie bez siły jest bezużyteczne, jak miecz bez ręki. Tę lekcję poznasz dzisiaj.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "A więc to tak... Kolejny zazdrośnik o wielkość Imperium.";
			link.l1 = "Jakie wielkości? Twoje sztywne sposoby powstrzymują ten świat.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Nie okłamuj się. Strach przed Hiszpanią czyni cię bardziej szczerym. Bliższym twej prawdziwej naturze. Sam zobaczysz.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Wariat. Prawdziwy wariat. A może zostałeś tu przysłany na próbe?";
			link.l1 = "Nie zawsze potrzebny jest powód do podjęcia decyzji, señor. Nigdy nie słyszałeś o czymś takim jak spontaniczność?";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Spontaniczność? A więc jesteś jednym z nich... On powiedział, że ludzie tacy jak ty są najbardziej niebezpieczni. Ale to tylko wzmocni moją rękę w bitwie.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_TrirdRound");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Cóż za siła ducha... Ta niezachwiana wola...";
				link.l1 = "Zaskoczony?";
			}
			else
			{
				dialog.text = "Nieźle. Minęło trochę czasu, odkąd spotkałem godnego przeciwnika.";
				link.l1 = "Nie dam ci czasu na odpoczynek.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Ostrzegano mnie... przed takim wyzwaniem. O pięknie, które mogłoby zachwiać wiarą wojownika.";
				link.l1 = "Czy zawsze tak bardzo komplikujesz proste rzeczy, don Fernando?";
			}
			else
			{
				dialog.text = "Pan daje siłę tym, którzy służą słusznej sprawie. Choć... czasami nie mam już pewności, komu służę.";
				link.l1 = "Zaczynasz wątpić w słuszność swej sprawy?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Wątpić? Nie... Słuszność?... To musi mieć głębsze znaczenie. To jest próba. Nie mogę się mylić.";
			}
			else
			{
				dialog.text = "Nie. Nigdy! To On mnie Nauczył, żeby nie zwątpić nawet na chwile! Nigdy nie zwątpie!";
			}
			link.l1 = "Widze, że twa szlachetność już dawno zaślepiła twoje racjonalne myślenie. Z moją pomocą otworzysz swe oczy, zobaczysz!";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			npchar.MultiFighter = 2.5;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_Molitva");
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "AHH!! Czekaj... Czekaj! Wygrałeś! Ał!... Jestem ranny, wykrwawiam się... Pozwól mi się pomodlić przed śmiercią, prosze...";
			link.l1 = "Niech będzie.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Panie... wybacz mi moje grzechy i daj mi siłę w tej godzinie próby. Pobłogosław dusze moich poległych towarzyszy. Wierni żeglarze, zginęli wierząc, że nieśli sprawiedliwość\nOjcze, starałem się żyć według Twoich nauk, walczyć z niesprawiedliwością. Lecz Twój własny syn splamił honor rodziny de Alamida. Wybacz mi\nOjczyzno... przysięgałem Ci służyć wiernie i prawdziwie. Ale mój zapał, mój gniew... stałem się tym, z czym chciałem walczyć\nDiego... Może kłamał? Przez cały ten czas... Biada mi, jeśli tak było\nI pobłogosław tę kobietę, Panie. Może w Twej ostatecznej łasce posłałeś mi ją... abym mógł zobaczyć, jak daleko zbłądziłem. Amen.";
			}
			else
			{
				dialog.text = "Panie... wybacz mi moje grzechy i daj mi siłę w tej godzinie próby. Pobłogosław dusze moich poległych towarzyszy. Wierni żeglarze, zginęli wierząc, że nieśli sprawiedliwość\nOjcze, starałem się żyć według Twoich nauk, walczyć z niesprawiedliwością. Lecz Twój własny syn splamił honor rodziny de Alamida. Wybacz mi\nOjczyzno... przysięgałem Ci służyć wiernie i prawdziwie. Ale mój zapał, mój gniew... stałem się tym, z czym chciałem walczyć\nDiego... Może kłamał? Przez cały ten czas... Biada mi, jeśli tak było\nŚwięta Maryjo Dziewico, módl się za nami grzesznymi i udziel nam swego miłosierdzia. Amen.";
			}
			link.l1 = "Nie rozpoznaję cię, don Fernando. Wydajesz się teraz inną osobą. A o kim ty wogóle mówiłeś? H-Hej! Nie odpływaj!!";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			
			DoQuestFunctionDelay("Alamida_abordage_OfficerPodhodit", 2.0);
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Mój kapitanie, gratulacje! Co za zażarta bitwa. Ten kapitan był zdolny, wręcz niezwykle zdolny. Ale ty... ty okazałeś się jeszcze lepszy. Jakże jestem z ciebie dumna...";
			link.l1 = "Dziękuję, kochanie. Jesteś ranna?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "Nie, nie. Chociaż myślałam, że byliśmy na krawędzi z kilka razy - zarówno przed abordażem, jak i w trakcie. A ty, wszystko z tobą w porządku?";
			link.l1 = "U mnie dobrze, jeszcze raz dziękuję. Idź odpocznij w kajucie, wkrótce do ciebie dołączę.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, wszystko w porządku? Przyszłam, jak tylko mogłam...";
			link.l1 = "U mnie wszystko w porządku, dziękuję, kochana. Choć nie ukrywam, że to była niezła przeprawa.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Cieszę się! Ale... Słuchaj, Charles? Dlaczego zaatakowaliśmy tych ludzi? Pan nam tego nie wybaczy, oj nie. Ten statek... jest jak wielka świątynia. Kiedy go zobaczyłam, moje serce zadrżało, tak samo jak wtedy, gdy po raz pierwszy zobaczyłam prawdziwy kościół, nie tylko w książkach. A teraz ta świątynia krwawi!";
			link.l1 = "Mary... Wiesz, pozory mogą mylić. A za tą maską pobożności kryli się ci, którzy brali pieniądze od prostych wiernych - takich jak ty. Rozumiesz?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Ja... wierzę ci, Charles. Dobrze. Tylko... przekażmy przynajmniej część złota, które tu znaleźliśmy, tym, którzy naprawdę go potrzebują? Uspokoiłoby to moje serce.";
			link.l1 = "Zrobimy to, Mary. Obiecuję. Teraz zbierz myśli i spróbuj się uspokoić. To już koniec.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Ha! Gratulacje z okazji zwycięstwa, Kapitanie! Ha! Takie interesy to ja rozumiem! Jakie oni mieli łupy na tym galeonie!..";
			link.l1 = "Twój uśmiech jest dziś jeszcze szerszy niż zwykle, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "A żebyś wiedział! Takie łupy. I co za walka. Aż mi się czasy Rewolucji przypomniały. A także... heh.";
			link.l1 = "Co się stało, Tommy? No dalej, mów głośniej.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "To, jak udekorowali cały ten statek... Przypomina on bardziej pływającą katedrę. I zebrali tyle złota zewsząd. Prawdziwi papiescy świętoszkowie! Hańba i śmiech na sali heheh...";
			link.l1 = "To jest statek skarbowy, Tommy. Nie statek kościelny.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Niewielka różnica w naszym przypadku. Tak czy inaczej, ciesze się, że mogłem dać tym donom i papistom porządną nauczkę! Nie znoszę żadnego z nich. Naprawdę cieszyłem się z tego dnia, ha-ha-ha!";
			link.l1 = "Ty się nigdy nie zmienisz! Dobrze, spocznij Irons. Wszystko tutaj jest pod kontrolą.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Kapitan Charles, my wygraliśmy. To była trudna walka. Nawet Tichingitu miał ciężko, a ja jeden z najlepszych wojowników w wiosce.";
				link.l1 = "Racja, przyjacielu. To byli godni przeciwnicy, bez wątpienia.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Señor de Montoya, statek jest nasz.";
				link.l1 = "Bardzo dobrze, Tichingitu. Ja też tu właśnie skończyłem.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Kapitan Paterson, ostatni opór na statku zdławiony.";
				link.l1 = "Spóźniłeś się, Tich! Następnym razem lepiej trzymaj się blisko mnie. Nie żebym nie mógł sobie bez ciebie poradzić, wiesz...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Pani Kapitan McArthur, wszystko w porządku?";
				link.l1 = "Tak, Tichingitu, mam się dobrze, dziękuję za troskę. I przestań wątpić w swojego kapitana - poradziłam sobie doskonale sama.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Duchy mówią mi to podczas walki. I pytają, czemu ich zabiłem. Teraz ja pytam ciebie. Tichingitu widzi w ich oczach, że oni nie złoczyńcy. Jeszcze nie.";
				link.l1 = "Ach, cóż mogę ci powiedzieć? Tak to już bywa w naszym 'zawodzie', Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Chcę zadać pytanie, kapitanie de Montoya.";
				link.l1 = "Słucham.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu chce zadać pytanie, Kapitan William, jeśli pozwolisz.";
				link.l1 = "Przyznano.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Nie wątpię, Tichingitu martwi się o ciebie, Pani Kapitan.";
				link.l1 = "Dobrze, dobrze. Widzę w twoich oczach, że chcesz mnie o coś jeszcze zapytać.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hmm, rozumiem, kapitan. Kończymy tutaj?";
				link.l1 = "Tak. Rozejrzę się jeszcze trochę, a potem dołączę do pozostałych.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Ci ludzie nie z tego samego plemienia co ty? Oni nie byli Hiszpanami? Dlaczego zdecydowałeś się zaatakować własne plemie?";
				link.l1 = "Byli Hiszpanami, i co z tego? Myślałeś, że zamierzam z nimi po prostu pogadać? Ale czy plemiona indiańskie nie walczą ze sobą nawzajem? Albo czy nie ma kłótni i waśni w obrębie jednego plemienia?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Statek wygląda jak kościół. Nienawidzisz kościoła i białego Boga?";
				link.l1 = "Skądże znowu. To tylko dekoracja, rozumiesz? To jest statek skarbowy. Choć i tak byś nie zrozumiał - słyszałem, że twoi ludzie nawet nie wiedzą, co to są podatki. Pfft. Szczęściarze.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tak. Tylko szczerze. Pani Kapitan MacArthur, dlaczego atakujemy ten pływający kościół?";
				link.l1 = "Pływający kościół, ha-ha-ha! Nie, nie. To jest statek skarbniczy. Hmm, widzę, że nie do końca rozumiesz. Cóż, przewozili złoto. Mogę sobie wyobrazić, jak dumny będzie Jan, kiedy powiem mu, że pokonałam Fernando de Alamide!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Hmm, masz rację, Kapitan. Ale z Indianami zdarza się rzadziej niż z białym człowiekiem.";
				link.l1 = "Być może. Cóż, ten człowiek mi... przeszkadzał.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Być może, Maskogi nie mają zamków ani podatków.";
				link.l1 = "Dokładnie. Możesz iść, i tak jesteś spóźniony. Później zdecydujemy, co zrobić z tym pięknym galeonem. Nie lubię tych balii, ale do diabła, jest piękna.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu również jest dumny, Pani Kapitan. I gratuluje zwycięstwa w tej ciężkiej walce.";
				link.l1 = "Dziękuję. Teraz podzielmy łupy.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Zwalczasz swoich, Señor de Montoya?";
			link.l1 = "Dokładnie. Ten Archipelag jest zbyt mały dla nas obu. A ja jestem tu znacznie bardziej przydatny naszemu państwu. Pamiętaj o Liściu Kakaowca - wyrządził swoim braciom więcej szkód niż pożytku. Tutaj jest tak samo.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Teraz rozumiem. Tichingitu może iść, Kapitan?";
			link.l1 = "Tak, idź. Wkrótce do was dołączę.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		case "Alamida_monah":
			dialog.text = "Ciekawe... Co sprowadza dziecko Boże do miejsca... wiecznego odpoczynku?";
			link.l1 = "Ja...";
			link.l1.go = "Alamida_monah_2";
		break;
		
		case "Alamida_monah_2":
			dialog.text = "Czy wiesz, co jest szczególnego w tym grobowcu? Spoczywają tu dwie dusze, związane... więzami krwi. Ojciec i syn de Alamida. Jeden padł z rąk grzeszników, drugi... Hmm, znalazł swoją drogę do Pana.";
			link.l1 = "Dziennik don Fernanda doprowadził mnie tutaj.";
			link.l1.go = "Alamida_monah_3";
			link.l2 = "Po prostu szukam czegoś cennego w tej krypcie.";
			link.l2.go = "Alamida_monah_6";
		break;
		
		case "Alamida_monah_3":
			dialog.text = "Ah... Dziennik. Niezwykła rzecz - słowo pisane. To jak... ścieżka w ciemności. Prowadzi tam, gdzie... czeka objawienie. Naszą parafię często odwiedzał don Fernando. Zwłaszcza w ostatnim roku.";
			link.l1 = "Służysz w lokalnej parafii? Znałeś don Fernanda, ojcze?";
			link.l1.go = "Alamida_monah_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Alamida_monah_4":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_5";
		break;
		
		case "Alamida_monah_5":
			dialog.text = "Ja... obserwowałem jego ścieżkę. A tę książkę, którą zabrałeś. Wiesz, co czyni ją wyjątkową?";
			link.l1 = "Wygląda na starą.";
			link.l1.go = "Alamida_monah_5_1";
		break;
		
		case "Alamida_monah_5_1":
			dialog.text = "Starą? Ja bym określił tą księge jako... oświeconą. Biblia don de Alamida Seniora. Każde słowo w niej zapisane, jest niczym latarnia w ciemności. Weź ją. Pomóż swym braciom w Chrystusie, a wtedy, być może... poprowadzi cię do czegoś... większego.";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_9";
		break;
		
		case "Alamida_monah_6":
			dialog.text = "Jakże... przyziemne. A jednak... Czyż to nie jest niezwykłe? Spośród wszystkich krypt, przyszedłeś do tej. Przypadek?";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_7";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Alamida_monah_7":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_8";
		break;
		
		case "Alamida_monah_8":
			dialog.text = "O nie. Pan zawsze znajduje sposób, nawet dla tych, którzy błądzą w ciemności.";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_9";
		break;
		
		case "Alamida_monah_9":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload2", "", -1);
			DoQuestFunctionDelay("SantaMisericordia_HavanaCrypt_9", 2.4);
		break;
		
		case "Alamida_monah_10":
			dialog.text = "Czy wiesz, co jest najbardziej niezwykłego w losie don Fernanda?";
			link.l1 = "Co niby?";
			link.l1.go = "Alamida_monah_11";
		break;
		
		case "Alamida_monah_11":
			dialog.text = "Że był zaledwie... pierwszym.";
			link.l1 = "...";
			link.l1.go = "Alamida_monah_12";
		break;
		
		case "Alamida_monah_12":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_priest");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "SantaMisericordia_Final", 3);
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Hej, co to za machanie bronią?! Schowaj to natychmiast!","Rozkazuję ci natychmiast schować broń!","Hej, "+GetAddress_Form(NPChar)+", przestań straszyć ludzi! Schowaj swoją broń.");
			link.l1 = LinkRandPhrase("Dobrze, schowam to...","Już zrobione.","Jak powiadasz...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Cholera jasna!","Chyba go użyję!","Odłożę to, gdy przyjdzie odpowiedni czas.");
			link.l2.go = "fight";
		break;
		
	}
} 