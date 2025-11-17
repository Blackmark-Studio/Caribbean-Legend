// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Widoczny błąd. Powiedz o tym deweloperom.";
			link.l1 = "O tak, zrobię to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Och, "+GetFullName(pchar)+"! Wyglądasz inaczej, mój przyjacielu, i jesteś naprawde skuteczny! Zaczynają o tobie mówić, wiesz? Szybko się uczysz, monsieur, jestem z ciebie naprawdę dumny. Życzę ci więcej fortun i szczęścia w przyszłości! To przyjemność spotkać cię ponownie!";
				link.l1 = "Monsieur Gregoire Valinnie, cóż za spotkanie! Jestem Ci wiele winien za moje skromne osiągnięcia. Miło Cię również widzieć! Powodzenia!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "O, "+GetFullName(pchar)+"! Wyglądasz inaczej, mój przyjacielu, i odnosisz sukcesy! Zaczynają o tobie mówić, wiesz? Szybko się uczysz, monsieur, muszę przyznać, że jestem z ciebie dumny.";
				link.l1 = "Monsieur Gregoire Valinnie, cóż za spotkanie! Jestem ci wiele winien za moje skromne osiągnięcia. Miło cię poznać! Pozwól zgadnąć, masz dla mnie propozycję biznesową?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Aye! Tak jest. Będę zwięzły, czas to pieniądz. Otóż, holenderska eskadra koronna płynąca z Brazylii do Kurakao z ładunkiem towarów o strategicznej wartości została zaatakowana przez Anglików pomiędzy Trynidadem a kontynentem. Jedna fluita Kompanii zdołała uciec i zacumować na wybrzeżu Boca de la Serpienta. Uratowali część ładunku, ale nie na długo - zostali zaatakowani przez miejscowe plemię Indian.\nZ moich informacji wynika, że wybili wszystkich Holendrów na tym wybrzeżu i zabrali ładunek do swojej wioski. Indianie również przejęli holenderską broń palną, ale ponieśli ciężkie straty. To nasza szansa! Brytyjczycy i Holendrzy nadal walczą w tym regionie i są zbyt zajęci, by martwić się o zaginioną fluite. Na razie... Masz statek i załogę. Możemy tam popłynąć, wysiąść i dobić Indian. Ładunek jest niezwykle cenny i jest go tam mnóstwo.\nWysłałem już małą ekspedycję na zwiady - to wszystko, na co było mnie stać, pamiętasz problemy finansowe? Mam zaufanego kupca, możesz liczyć na mój miecz i moich najemników. Podział pięćdziesiąt na pięćdziesiąt, mamy tydzień, aby się tam dostać. Więc, mój przyjacielu, wchodzisz w to?";
			link.l1 = "Przebacz mi, monsieur, ale odmówię. Właśnie wróciłem z ciężkiej podróży, nie mamy wystarczająco czasu na naprawy i rekrutację. Nawet w tym zapomnianym przez Boga miejscu człowiek nie może mieć wszystkiego.";
			link.l1.go = "greguar_exit";
			link.l2 = "Brzmi to jak niebezpieczny interes z zapachem godziwego zysku i przygód. Oczywiście, że wchodzę! Nie marnujmy czasu!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Szkoda. Decyzja należy do ciebie. Szczęśliwej drogi, monsieur, i tak tam się udam. Człowiek musi spróbować, co?";
			link.l1 = "Pomóż Bóg, monsieur Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Właściwy wybór, mój przyjacielu! Przyda ci się dodatkowa kasa, prawda? Jak tam twój brat, tak przy okazji?";
			link.l1 = "Zawsze przyda się dodatkowa kasa. Michel? Mój brat jest w dobrym zdrowiu i się nudzi. Czasem mu zazdroszczę... Czas wypłynąć!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "Łatwizna! To byli nowicjusze, którzy przeżyli potyczkę z Holendrami. Powinniśmy udać się głębiej w głąb lądu, moja ekspedycja musi tam być!";
			link.l1 = "Wydawało się to zbyt proste... ale za wcześnie na świętowanie, panie Valinnie. Spójrz tam...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "Cholera te czerwone skóry! Prawie nas mieli! Teraz jestem pewien, że w wiosce zostały tylko kobiety i dzieci. Ruszać się!";
			link.l1 = "Nie jestem aż tak pewny. Wspomniałeś o muszkietach, a ich nie widziałem... Ach, nieważne. Ruszajmy!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "To znaczy? Holendrzy i my musieliśmy ich wszystkich zabić!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Uciekać? Oszalałeś? Jesteśmy prawie na miejscu! Boisz się bandy wymalowanych dzikusów?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "Najpodlejsze z podłych rzeczy, kapitanie. Wracam do Europy. Jestem zawiedziony! Tobą, tymi tchórzami i tym cholernym regionem!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Fuh! Zrobiliśmy to!";
			link.l1 = "Ale za jaką cenę! Spójrz! Prawie wszyscy z naszej drużyny są martwi. Powinniśmy się wycofać, Gregoire, nie mamy żadnej gwarancji, że czekają na nas kolejni wojownicy. Poza tym, po prostu brak nam ludzi, by unieść łup.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Do diabła! To smutne, ale masz rację, "+pchar.name+": nawet jeśli dzikusy są martwe, nie zdołamy zabrać ładunku, zanim Holendrzy lub Anglicy tu wylądują. Musimy odpłynąć teraz! Do diabła z tym przeklętym wybrzeżem!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Fuh! Udało się! Dobra robota, "+pchar.name+". Teraz ruszajmy do legowiska dzikusów po naszą nagrodę! Nic nas teraz nie powstrzyma!";
			link.l1 = "Powinniśmy się pośpieszyć, póki Brytyjczycy i Holendrzy są jeszcze zajęci sobą nawzajem. Ruszajmy!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "Dobrze się spisaliśmy, "+pchar.name+". Teraz musimy tylko sprzedać ładunek bez wzbudzania podejrzeń. Mam solidnego kupca, będzie na nas czekał w zatoce Lamentin o północy. Nie zabieraj żadnych oficerów i unikaj tego miejsca przed spotkaniem, klient jest bardzo nerwowym jegomościem.";
			link.l1 = "Biznes to biznes. Ładunek musi zostać sprzedany i to bezpiecznie, inaczej mój dług wobec de Poincy jeszcze bardziej wzrośnie. Dobrze, będę tam o północy.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "Zrobione. Ładunek jest rozładowany, klient jest tutaj. Porozmawiajmy.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Niespodzianka, łotry!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Ach, Johnny, co za facet! Świetnie! Masz coś do powiedzenia, "+pchar.name+"?";
			link.l1 = "Nie. Właściwie, tak! Co do cholery?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Nie drażnij trupa, monseniurze. Gdzie są twoje maniery?.. Pieniądze są tutaj, a ładunkiem zajmuję się ja i moi przyjaciele. Nie wysłałem ich na wybrzeże, to byłoby marnotrawstwo. Zwłaszcza wysyłanie tam Johnny'ego. Widzisz tego czerwonoskórego z kolubryną w rękach? Wiesz, Johnny nigdy naprawdę nie lubił swojego własnego plemienia.";
			link.l1 = "Rozumiem... Co teraz? Też chcesz mnie zabić?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Cóż, powinienem. Ale jestem sentymentalny. Odejdź i weź czwartą część gotówki. Ładunek i reszta pieniędzy zostaną tutaj ze mną. Nie próbuj udawać bohatera, to nie są dżungle kontynentu. Nie masz szans.";
			link.l1 = "A gdzie twoja szlachetność i maniery, Gregoire? Nie spodziewałem się tego po tobie. Odchodzę, ale tego nie zapomnę.";
			link.l1.go = "greguar_23";
			link.l2 = "Nie gram bohatera, nigdy tego nie robiłem. Po prostu was wszystkich zabiję! Najpierw te damy, potem małpę z granatnikiem, a potem ciebie!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "Na tej plaży nie ma ani szlachty, ani łotrów, monseniurze. Jest tylko pięciu ludzi, wielkie działo i ofiara. To dzieje się tutaj cały czas, ale dokonałeś jedynego słusznego wyboru. Dobra robota. Czy wiesz, że zamiast ciebie mogło tutaj stać dwóch innych, dokładnie w tym miejscu, w tej chwili? Są prawie tacy sami jak ty. Ale ty jesteś tutaj, a ich nie ma, i myślę, że z tego powodu zginą.";
			link.l1 = "Nie nadążam...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Pewnego dnia to zrozumiesz. Oni nie otrzymali swojej ostatniej lekcji. Ty ją otrzymałeś. Nie ma za co. Żegnaj, monsieur. Witaj na Karaibach!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... Nie jesteś najbystrzejszym uczniem, jakiego miałem. Dobrze... co kto lubi!";
			link.l1 = "Pożałujesz tego noża w moje plecy!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Doskonale wyczucie czasu! Ledwo uciekliśmy przed hordą Karaibów, zmierzali w twoim kierunku i, patrząc na ciebie, już ich spotkałeś. Ich wioska jest w pobliżu, ale nasze kłopoty dopiero się zaczynają.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! Też tu jesteś! I czemu mnie to nie dziwi? Idealne wyczucie czasu, przyjacielu. Ledwo uciekliśmy przed hordą Karibów, zmierzali w twoim kierunku i, jak widzę, już ich spotkałeś.";
			link.l1 = "Prosper! A ja jestem zaskoczony! Znowu robisz dziury w Indianach? Mam nadzieję, że z Seliną wszystko w porządku?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "Głupotą było z mojej strony dołączać do tej ekspedycji, zastanawiam się, czy moja córka jeszcze mnie kiedyś zobaczy. Selina? Cóż, siedzi w domu i marzy o tobie! Młodzież z Martyniki straciła już wszelką nadzieję... Wiesz, nie żałuję już zakupu tego muszkietu. Solidna broń palna. Niezawodna. To również dodatkowy powód, by wziąć udział w kolejnej samobójczej wyprawie, choć teraz jest ona trochę mniej samobójcza, odkąd się pojawiłeś. Ich wioska jest niedaleko, ale nasze problemy dopiero się zaczną.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Nie wszyscy. Nasz zwiadowca został postrzelony, ale udało mu się dotrzeć do ich kryjówki. Sam wódz przychodzi tutaj ze swoimi strażnikami. I mają holenderskie muszkiety. Mają przewagę liczebną i są wściekli jak diabli. Wódz jest najlepszym wojownikiem ich plemienia, jego ludzie to diabły wcielone. Musimy szybko podjąć decyzję, tu i teraz. Albo stawimy im czoła, albo uciekniemy. Szczerze mówiąc, wolę to drugie...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Nie widziałeś ich, dobry człowiecze! Te 'dzikusy' mają muszkiety i są zaskakująco dobrzy w ich używaniu. Ktoś ich nauczył, co do tego nie ma wątpliwości! Więc nie nazywaj mnie więcej tchórzem!";
			link.l1 = "Uspokójmy się i zdecydujmy, co robić. Jest jeszcze czas.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Słucham, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "Stawimy im czoła, chłopcy! Za tym wzgórzem są towary i pieniądze! Jesteśmy tu dla nich i nigdzie się nie ruszamy. Żadna banda czerwonoskórych, nawet z muszkietami, nas nie powstrzyma! Zakopmy skurczybyków i dokończmy robotę! Mamy wystarczająco ludzi, jest szansa ich zaskoczyć. Czterech ludzi przywita ich ogniem z flanek, a reszta zajmie tu pozycje. Zmniejszmy ich liczebność i dobijmy ich!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "Damy im walkę, chłopcy! Za tym wzgórzem są towary i pieniądze! Jesteśmy tu po nie i nie zamierzamy odchodzić. Żadna zgraja czerwonoskórych, nawet z muszkietami, nie zatrzyma nas! Zakopmy skurczybyków i skończmy robotę!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Szanse są przeciwko nam na każdy możliwy sposób. Nie zapomnij o Holendrach tuż za nami.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "Żyjemy i jesteśmy w domu! Przysięgam, mam dość przygód... na kilka następnych miesięcy, ha-ha! Powinienem iść do mojej córki, proszę odwiedź nas, "+pchar.name+". I proszę, bądź ostrożny.";
			link.l1 = "Nie obiecuję niczego, Prosper. Pomyślności!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Ostrzegałem cię, kapitanie, żebyś był ostrożny! Miałem podejrzenia co do tego drania.";
			link.l1 = "Prosper?! Dziękuję! Ale jak się o tym dowiedziałeś?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = " Szkoda, że zginął. Przynajmniej do końca próbował być ci wierny... ";
			dialog.text = "Johnny zrobił się zbyt gadatliwy. To ten czerwonoskóry facet, który leży teraz na piasku. Przyszedł do burdelu i próbował poderwać dziewczynę. Odmówili mu obsługi, Johnny wpadł w furię, zaczął krzyczeć, że wkrótce się wzbogaci, kiedy on i jego kumple zabiją jakiegoś kapitana w dżungli. Wiedziałem, co się święci i pobiegłem do twojego oficera, który zdążył sobie wyrobić złą sławe na mieście."+sTemp+"Jestem ci wiele winien, "+pchar.name+", więc nie musisz mi zbyt mocno dziękować.";
			link.l1 = "I tak, bardzo Ci dziękuję, Prosper! Było tu ciężko... za ciężko. Chcesz dołączyć do mojej załogi? Potrzebuję oficera takiego jak Ty. Trudno znaleźć lojalnych ludzi w dzisiejszych czasach, zwłaszcza strzelców wyborowych.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "Nie, mój przyjacielu. Mam zobowiązania wobec mojej córki. Kazała mi przysiąc, że porzucę moje przygody. To była moja ostatnia. Cholera, co za szkoda, ale kocham moją córkę bardziej niż cokolwiek na świecie. Żegnaj, "+pchar.name+". I... Selina mówi o tobie cały czas. Może kiedyś mógłbyś nas odwiedzić?";
			link.l1 = "Kto wie, może tak zrobię... Żegnaj, Prosper! Życzę twojej córce, by znalazła dobrego męża... (do siebie) Lekcja odrobiona, monsieur Gregoire, lekcja odrobiona... co kto lubi, jak powiedział... Zapamiętam to.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Kim, do cholery, jesteś?";
			link.l1 = "Mamy towar. Zainteresowany?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Bardzo zainteresowany. Zwłaszcza mój klient. Jaki jest łup?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" twardego drewna, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" sztuk jedwabiu,   "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" liny i "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" z żywicy.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Bardzo dobrze. 2200 pesos za każdą sztukę twardego drewna, 900 pesos za żywicę, 1600 pesos za jedwab okrętowy i 1000 pesos za liny. Co my tu mamy... No proszę."+iTotalTemp+" peso. Zgoda?";
			link.l1 = "Umowa stoi!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Wspaniale! Przynieś więcej. Holendrzy nigdy nie przestają być hojni dla czerwonoskórych... A kim są ci goście? Co do licha?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Kurwa mać... a ten wieczór wydawał się być taki przyjemny...";
			link.l1 = "Claude?! Co do cholery!?? Jak mnie znalazłeś?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Przepraszam, kapitanie. Musiałem wychylić kubek lub dwa po tej aferze z Indianami. Była tam dziewczyna, wynająłem pokój za sto pesos i ona... ona...";
			link.l1 = "Co? Okradła cię?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "Gorzej! Zakochała się! Do diabła, powinienem był dać dyla i jak najszybciej stamtąd uciec! Byłem już gotów nawet wyskoczyć przez okno, gdyby nie to, że wtedy pojawił się twój przyjaciel. Zaczął na mnie wrzeszczeć o jakimś łajdaku, twoim byłym towarzyszu, który chce cię oszukać i zabić.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Dobra robota, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... tak mi przykro. Zajmę się twoją córką. Lekcja odrobiona, monsieur Gregoire... Co tam wtedy powiedziałeś? Co kto lubi? Powinienem to zapamiętać.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Możemy stąd iść, kapitanie?";
			link.l1 = "Tak. Dzięki za twoją pomoc. Trzymaj się z dala od kielicha, a my ocalimy cię od tej piękności. Chodźmy.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
