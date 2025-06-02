// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Kapitanie! Wypłynąłeś na morze, jak słyszałam! Co się stało? Dowiedziałeś się czegoś? Proszę, powiedz mi, wykrztuś to z siebie!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "Nie, moja piękności, ten najazd został przeprowadzony na prośbę Jego Ekscelencji gubernatora. Bardzo mi przykro, ale Angelo zginął w kazamatach fortu - teraz nie ma co do tego wątpliwości. Trzymaj się mocno!";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Miałaś rację. Twój brat został porwany. Komendant sprzedawał więźniów jak bydło handlarzowi niewolników o przydomku 'Gruźlica'.  Lecz dogoniłem jego statek, a teraz leży na dnie, twój brat Angelo wkrótce dotrze na brzeg. Niestety,  nie miałem tylu szalup, ile potrzeba, by dostarczyć wszystkich pasażerów na brzeg jednocześnie. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "Miałaś rację. Twój brat został porwany. Komendant sprzedawał więźniów jak bydło handlarzowi niewolników o przezwisku 'Gruźlica'. Ale dogoniłem jego statek, choć nie udało mi się zabić tego drania, twój brat Angelo wkrótce zejdzie na ląd. Niestety, nie miałem tylu szalup, ile potrzeba, aby wszyscy pasażerowie mogli zostać dostarczeni na brzeg naraz.";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Czy udało ci się dowiedzieć czegoś o losie Angelo, kapitanie?";
				link.l1 = "Jeszcze nie. Ale myślę, że wkrótce będę miał wieści. Musisz tylko poczekać. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Señor, obiecałeś znaleźć mojego brata... Dlaczego tracisz czas na picie tutaj?";
			link.l1 = "Ohh...Tak, racja...hik... Spokojnie, dziewczyno... Jezus ma nad tym kontrolę...'siorb'... Jezus ma nad tym kontrolę. Już mnie nie ma...hik...";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Dzień dobry, seniorze. Jaki masz tu interes?";
			link.l1 = "Przyniosłem depeszę dla seniora komendanta, ale powinienem przekazać ją osobiście.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "W takim razie idź go szukać w fortecy.";
			link.l1 = "Ten rozkaz jest zbyt ważny i nie jest przeznaczony dla oczu i uszu żołnierzy. Może przyszedłem za wcześnie, ale mogę tu na niego poczekać. Uwierz mi, to bardzo ważne!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "Senor komendant zazwyczaj ostrzega mnie o wszystkich ważnych sprawach, które wymagają zmiany rutyny... Wiesz, właściwie to ostrzegł mnie o tym konkretnym przypadku.";
				link.l1 = "A co on powiedział?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "Dobrze, wierzę ci. I uwierzę ci jeszcze bardziej, gdy nadejdzie señor komendant, aby potwierdzić twoje słowa. Ale do tego czasu będę cię nieustannie obserwować.";
				link.l1 = "Możesz mnie obserwować, ile tylko chcesz...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Powiedział mi, żebym w takich przypadkach wezwał straż garnizonową. Ale pewnie poradzimy sobie sami. Chłopcy! Wypatroszymy go!";
			link.l1 = "Po moim trupie! To wy zginiecie!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "Czego jeszcze chcesz? Zdecydowałeś się przekazać mi wiadomość?";
			link.l1 = "Nie, poczekam na komendanta...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Jesteś złodziejem! A może i szpiegiem? Chłopaki, na dół szybko!";
			link.l1 = "Argh, do diabła z tym! Chodź tu!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Przepraszam, czy mogę z tobą porozmawiać?";
			link.l1 = "By być szczerym, śpieszę się. Czego chcesz?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "Słyszałem, że wypytujesz o człowieka imieniem Juan i chorobę w naszym więzieniu...";
			link.l1 = "Rzeczywiście, wypytywałem... czy mógłbyś się wytłumaczyć.";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Spokojnie, spokojnie! Uspokój się i nie dotykaj swego miecza! Jesteśmy po tej samej stronie! Nie wiem, dlaczego miałbyś się przejmować naszymi problemami, ale to musi się skończyć! Nie mogę dłużej milczeć!";
			link.l1 = "Milczeć? O czym? Co ty wiesz o gruźlicy?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "Znam wiele, jeśli nie wszystko, i wytłumacze się - ale nie tutaj. Spotkajmy się wieczorem, gdy zgasną światła, jestem asystentem medycznym, więc mogę opuścić fort. Spotkamy się za bramami miasta, i powiem ci wszystko. Błagam cię - przestań zadawać pytania, zanim zwrócisz ich uwagę, jeśli już tego nie zrobiłeś... Muszę teraz iść. Pamiętaj, w nocy za bramami miasta.";
			link.l1 = "Dobrze, będę tam. Hej! Czekaj...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Dzięki Bogu, że jesteś... Mam nadzieję, że nikt cię nie śledził?";
			link.l1 = " Dlaczego? Jesteś zbyt podejrzliwy, być może nawet bardziej niż senor komendant, więc lepiej przejdź do rzeczy... Co wiesz o Juanie?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "Nazywam się Sergio Saldo. Służę jako asystent medyczny w naszym forcie i...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Czekaj! Słyszałeś to?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "Co?! Gdzie?";
			link.l1 = "Cholera, nie jesteśmy tu sami... Kogo ze sobą przyprowadziłeś, łajdaku?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Zauważyli nas! Ty bierz doktora, a ja wezmę tego drugiego!";
			link.l1 = "Do broni!!";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Schowaj swój miecz, to koniec! Widziałeś sam, że oni próbowali też i mnie zabić!";
			link.l1 = "Cóż, to wydaje się zbyt wyrafinowane na nieczystą grę - więc nie jesteś z nimi. Gdzie skończyliśmy? Jesteś więziennym lekarzem, prawda?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Tak. Służę jako lekarz więzienny. Studiowałem medycynę, gdy byłem młody, a tutaj nie ma wielu wykształconych ludzi. Dlatego wiem lepiej niż ktokolwiek, co się dzieje w więzieniu!";
			link.l1 = "Co się dzieje? Co z więźniami? Wiesz coś o ich nagłym zniknięciu?";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Nasz komendant sprzedaje ich... sprzedaje jak bydło jednemu handlarzowi niewolników o imieniu Juan. Wybiera tych, których nikt nie będzie szukał - biedaków, marynarzy z przypadkowych statków. A potem nagle 'umierają na suchoty' - resztę możesz sobie dopowiedzieć...";
			link.l1 = "Ten Juan to jednak człowiek! Co o nim wiesz?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Trochę. Zwykł załatwiać swoje brudne interesy w Maroku razem z berberyjskimi piratami, lubi opowiadać historie o tamtych czasach, gdy nas odwiedza. To było miejsce, gdzie dostał swoje przezwisko - 'Gruźlica'. Nie chcę myśleć o jego pochodzeniu\nPrzyjeżdża tu co miesiąc i zabiera wszystkich więźniów na pokład.";
			link.l1 = "'Gruźlica!' A oni oskarżyli mnie o cynizm! Więc to dlatego... Ten wasz señor komendant to prawdziwy dupek!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Jak rozumiem, potrzebujesz kogoś spośród zaginionych więźniów, inaczej skąd wiedziałbyś o tej historii, prawda? Jeśli tak, powinieneś się pospieszyć: tej nocy jest ostatnia w tym miesiącu. Już podpisałem dokumenty stwierdzające śmierć trzech kolejnych osób, a Juan podniesie kotwicę jutro przed południem, gdy je otrzyma!";
			link.l1 = "Coś ty podpisał? Nie bardzo cię rozumiem...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Musiałem to zrobić - tak jak robiłem to już od kilku miesięcy! Dlatego właśnie przyszedłem tu, aby to zakończyć. Wiesz, jak umarł doktor Pinero? Ten, który leczył więźniów przede mną?";
			link.l1 = "Zdaje mi się, że mówiono mi, iż zmarł na suchoty, czyż nie? Więc zostałeś do tego zmuszony. To logiczne - ale dlaczego nikt nie skontaktował się z władzami w tej sprawie?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "A kto w to uwierzy? Nie mam żadnych dowodów, a żołnierze, którzy powinni pilnować więźniów, są sowicie opłacani, więc nie obchodzi ich to, nawet jeśli sprzedawaliby ludzi Karibom na posiłek\nNikt nie przejmuje się więźniami, a to jest atut w ręku komendanta. Ale możesz to zatrzymać, przynajmniej na jakiś czas, eliminując Juana!";
			link.l1 = "Z tego co rozumiem, ci ludzie na lądzie byli jego ludźmi, prawda? Jak mogę go znaleźć?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Zapewne zwróciłeś czyjąś uwagę swoimi pytaniami... Mówiłem, żebyś był bardziej ostrożny! Ale to teraz nieważne. Nic nie wiem o statku Juana, ale więźniów zawsze wysyłają na Galera Point, co znajduje się na północnej części wyspy. Przypuszczam, że statek handlarza niewolnikami powinien być w pobliżu i możesz go dogonić. Jego posłańcy wspomnieli dzisiaj, że zamierza odpłynąć jutro w południe.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Dziękuję, Sergio, jesteś prawdziwym oficerem i człowiekiem honoru. Podniosę kotwicę od razu i znajdę ten plugawy statek. Musisz wrócić do fortu, zanim zaczną cię szukać.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Cóż, to wszystko, co muszę wiedzieć. Muszę teraz podnieść kotwicę, jeśli nie chcę szukać 'Gruźlicy' po całym Nowym Świecie. W międzyczasie możesz się temu przyjrzeć.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Powodzenia, kapitanie! Nie martw się o mnie - najważniejsze to zatrzymać to chociaż na chwilę. Życzę ci szczęścia!";
			link.l1 = "Moje działa są najlepszym lekarstwem na chorobę i podłość. Przysięgam, że wszyscy więźniowie będą na brzegu przed świtem - a statek Juana spocznie na dnie morskim!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Co to jest? To nazwisko pułkownika i monogram 'J'? Niesamowite! Skąd to masz?";
			link.l1 = "Lepiej, żebyś tego nie wiedział, ale myślę, że wykorzystasz to w najlepszy możliwy sposób.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Przysięgam na wszystko, co święte! Pułkownik trafi na szubienicę przed końcem miesiąca! Osobiście się tym zajmę!";
			link.l1 = "Obawiam się, że skończy się to na karze dyscyplinarnej, która, jak sądzę, nie będzie pierwszą w jego życiu. Może lepiej zastrzelić tego huncwota? To bardzo skuteczny środek... Muszę już iść - nie chcę, by 'Gruźlica' czekał.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "O, cóż za szczęśliwe spotkanie! Senor "+GetFullName(pchar)+"! Tak się cieszę, że cię widzę!";
			link.l1 = "Senor Sergio! Nie spodziewałem się ciebie spotkać! Jak się masz? Jak się miewa stary dobry komendant?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "U mnie w porządku, a senor komendant pojechał do kopalń w Los-Teques - jego plugawą machinację z Juanem Konsumpcją ujawniono.";
			link.l1 = "Kopalnie?! Na moją duszę! Nigdy bym nie pomyślał, że w jego przypadku sprawiedliwość zostanie wymierzona...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ach, gdyby tylko tak było, kapitanie... Został tylko przeniesiony i zdegradowany. Służy teraz w garnizonie, a nawet nie został pozbawiony rangi oficerskiej. Cóż, przynajmniej San Jose pozbyło się tego łajdaka.";
			link.l1 = "No cóż, jak dotąd dobrze. Choć spodziewałem się więcej.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Ja również... Ale zapomnijmy o tym łajdaku - nie zasługuje, by o nim mówić. Señor, gdy tylko usłyszałem, że twój statek ma wpłynąć do portu, pospieszyłem na molo z całą szybkością. Mam dla ciebie propozycję.";
			link.l1 = "Naprawdę? Słucham.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			if (startHeroType == 1) sStr = "francuzem, co osobiście nie sprawia mi problemu";
			if (startHeroType == 2) sStr = "rodowitym hiszpanem, a rodacy muszą sobie pomagać,";
			if (startHeroType == 3) sStr = "anglikiem";
			if (startHeroType == 4) sStr = "angielką";
			dialog.text = "Kapitanie, zdajesz się być człowiekiem, któremu można zaufać. Kolejną bardzo istotną rzeczą jest to, że jesteś "+sStr+" i masz własny statek. Proponuję zawrzeć umowę handlową.";
			link.l1 = "Brzmi obiecująco! Jaki to rodzaj umowy?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "Lepiej omówmy to w innym miejscu - w latarni morskiej, w chatce latarnika. To mój stary przyjaciel i mu ufam. Przyjdź dziś lub jutro do latarni morskiej San Jose. Będę tam na ciebie czekał. Jestem pewien, że moja propozycja wyda ci się bardzo interesująca!";
			link.l1 = "Dobrze, señor Sergio. Do zobaczenia tam!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Witaj ponownie, señor. Pozwól, że wyjaśnię ci tę sprawę. ";
			link.l1 = "Zamieniam się w słuch. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "Jak zapewne już wiesz, nie jestem tylko żołnierzem, ale także lekarzem. Dlaczego? Ponieważ jestem dobrze wykształconym człowiekiem. Moje wykształcenie powstrzymało mnie od marnowania czasu tutaj na kobiety i trunki. Zamiast tego zorganizowałem kilka wypraw i udało mi się znaleźć złoże żywicy niedaleko stąd\nTo zasób o strategicznym znaczeniu, ta wyspa jest jedynym miejscem, gdzie można znaleźć specjalną żywicę, która jest używana do budowy solidnych i trwałych statków\nGubernator i komendant kazali mi sprzedać całą żywicę hiszpańskiej marynarce\nProblem w tym, że płacą mi połowę jej ceny rynkowej i nie mogę jej sprzedać gdzie indziej. Dlatego oferuję ci jej zakup ode mnie. To bardzo ważny towar i bardzo trudno go zdobyć.";
			link.l1 = "Jakie są warunki naszej umowy? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "Według moich obliczeń, będę w stanie zbierać 60 beczek miesięcznie, nie wzbudzając podejrzeń. Zawrzyjmy umowę - każdego piątego dnia miesiąca odwiedzę tę latarnię morską, by napić się z moim przyjacielem. Dołącz do nas, jeśli chcesz kupić żywicę. Dziesięć złotych dublonów za beczkę\nPłacisz za całą partię i zabierasz ją za jednym razem. Bez presji, decyzja należy do ciebie. Więc, zgoda?";
			link.l1 = "Brzmi jak cholernie dobra umowa dla mnie! Oczywiście, że zgoda!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Cudownie. Więc piątego każdego miesiąca wypiję butelkę kanaryjskiego wina z moim starym przyjacielem, stróżem, i będziemy na ciebie czekać.";
			link.l1 = "Dobrze. Zróbmy to w ten sposób.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Cieszę się, że doszliśmy do porozumienia. Do zobaczenia, kapitanie!";
			link.l1 = "Powodzenia w twoim biznesie żywicznym, señor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Witaj, señor kapitanie! Przyszedłeś po partię żywicy, jak sądzę.";
			link.l1 = "Zgadza się, senor Sergio. Czy wszystko gotowe?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Senor Sergio, nie jestem w nastroju do handlu. Może później.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Tak. Masz przy sobie 2550 doblonów?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Jasne. Proszę bardzo.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Zły los! Zapomniałem pieniędzy na moim statku. Zaraz je tu przyniosę!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Tak. Masz przy sobie sześćset dublonów?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Jasne. Proszę bardzo.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Co za pech! Zapomniałem pieniędzy na moim statku. Zaraz je tu przyniosę!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Señor Sergio, chcę kupować więcej żywicy. Czy mógłby pan dostarczać partie, powiedzmy, pięć razy większe?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "Oto, jak "+GetSexPhrase("obiecałem","obiecałam")+", Señor Sergio, trzy tysiące dublonów, jak pan prosił. Jestem "+GetSexPhrase("pewien","pewna")+", że z pańską przezornością i moją inwestycją to przedsięwzięcie przyniesie nam obu niemały zysk.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "Z przyjemnością z tobą współpracuję, kapitanie. Moi ludzie pomogą ci załadować beczki na twój statek.";
			link.l1 = "Dziękuję!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "Umowa nadal obowiązuje. Jeśli będziesz potrzebował kolejnej partii, wróć za miesiąc.";
			link.l1 = "Dobrze, Sergio. Do zobaczenia.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+" "+GetSexPhrase("pańskie","pani")+" pragnienie zakupu większej ilości żywicy niewątpliwie świadczy o zaufaniu do naszego interesu. Jednak pojawia się pewna trudność: wraz ze zwiększeniem wydobycia rośnie ryzyko zwrócenia uwagi władz wyspy, a kontrola nad takimi partiami wymaga ludzi i środków bezpieczeństwa, co, przyznaję, nie jest tanie. Jeśli jest "+GetSexPhrase("pan","pani")+" "+GetSexPhrase("gotowy","gotowa")+" dodać do ceny trzy tysiące dublonów jako jednorazową opłatę, zatrudnię godnych zaufania ludzi, którzy będą w stanie chronić ładunki i zapobiec wyciekom informacji. Wtedy nasza trasa stanie się bezpieczniejsza, a ja będę mógł dostarczać "+GetSexPhrase("panu","pani")+" trzysta beczek żywicy miesięcznie. Jako rekompensatę za "+GetSexPhrase("pańską","pani")+" inwestycję, zaproponuję "+GetSexPhrase("panu","pani")+" jako klientowi hurtowemu piętnastoprocentową zniżkę na wszystkie przyszłe partie.";
				link.l1 = "Trzy tysiące dublonów za bezpieczeństwo dostaw? Señor Sergio, nie ukrywam, ta cena wydaje mi się niewiarygodna - jakby proponował mi pan spisek w Eskorialu, a nie tylko zapewnienie ochrony ładunków żywicy!";
				link.l1.go = "UpgradeOil_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", cenię "+GetSexPhrase("pańskie","pani")+" zainteresowanie, ale tak duże transakcje wymagają doświadczenia i ostrożności. Przyznam, że "+GetSexPhrase("pański","pani")+" poziom w sprawach handlowych nie jest jeszcze wystarczająco wysoki, aby poradzić sobie z taką ilością. Radzę nabrać jeszcze trochę doświadczenia i wrócić do mnie, gdy będzie "+GetSexPhrase("pan gotowy","pani gotowa")+" na większe partie. Wtedy, być może, omówimy sprawę dogłębnie.";
				link.l1 = "Dobrze. Wrócimy do tej kwestii później.";
				link.l1.go = "oil_trade_exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Señor"+GetSexPhrase("","ita")+", rozumiem "+GetSexPhrase("pańskie","pani")+" obawy. Ale wie "+GetSexPhrase("pan","pani")+", bezpieczeństwo nigdy nie jest tanie, zwłaszcza gdy mowa o tak rzadkim towarze. Ponadto, nie tylko gwarantuję brak wycieków, ale jestem również gotów zaoferować zniżkę, która z czasem zrekompensuje "+GetSexPhrase("pańską","pani")+" inwestycję. Czy to nie jest rozsądny kompromis?";
			link.l1 = "Przyznaję: w naszym interesie niezawodność i tajemnica kosztują drogo, a zniżka czyni naszą potencjalną transakcję nieco przyjemniejszą. Ale mimo wszystko, trzy tysiące dublonów to nadmiernie duża suma. Może mógłby pan nieco zmniejszyć jej wysokość?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "Ubolewam, ale w takich sprawach półśrodki są niedopuszczalne. Albo zapewniamy pełną ochronę, albo ryzykujemy wszystkim. Suma pozostaje bez zmian i tylko w ten sposób mogę zagwarantować niezawodność i poufność. Chyba nie chce "+GetSexPhrase("pan","pani")+", żeby najpierw za mną, a potem za panem/panią ścigała się cała królewska flota?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Dobrze, Señor Saldo, przekonał mnie pan. Bezpieczeństwo i niezawodność są warte swojej ceny. Trzy tysiące dublonów. Proszę.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Señor Saldo, przekonał mnie pan o konieczności tych środków. Jednak trzy tysiące dublonów to poważna suma, a w tej chwili jej nie mam. Będę "+GetSexPhrase("musiał","musiała")+" poczekać, aż zbiorę wymaganą ilość.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "Za takie pieniądze można przekupić całą flotę i wszystkich żołnierzy na kontynencie, nie mówiąc już o wynajęciu strażników dla skromnego ładunku żywicy! Przepraszam, ale nie mogę zgodzić się na taką propozycję. Zostawmy wszystko tak, jak jest, bez zbędnych dodatków i dodatkowych kosztów.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "No cóż, Señor"+GetSexPhrase("","ita")+", widzę, że nasze zaufanie jest wzajemne. Proszę być "+GetSexPhrase("pewnym","pewną")+": sprawa zostanie zorganizowana jak należy. Teraz do szczegółów: 300 beczek żywicy, jak zwykle, 5-go dnia każdego miesiąca będzie na "+GetSexPhrase("pana","panią")+" czekać tutaj, na latarni morskiej Trinidadu. Wykupić całą partię będzie "+GetSexPhrase("pan mógł","pani mogła")+" za 2550 dublonów.";
			link.l1 = "Wspaniale, Señor Sergio. Proszę mnie nie zawieść.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "Proszę nie wątpić, Señor"+GetSexPhrase("","ita")+". Wszystko zostanie zorganizowane na najwyższym poziomie, a nasza wspólna praca przyniesie owoce.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Proszę przyjść, gdy będzie "+GetSexPhrase("pan miał","pani miała")+" całą sumę. Z przyjemnością zawrę z "+GetSexPhrase("panem","panią")+" nową transakcję.";
			link.l1 = "Dobrze.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Kim, do diabła, jesteś!?";
			link.l1 = "Me imię to "+GetFullName(pchar)+", co do ciebie, Konsumpcjo, diabeł już na ciebie czeka - i wkrótce pochwyci twoją duszę!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Ten statek wyleci w powietrze - lont już się pali w prochowni - dlaczego obaj mamy zginąć? Odłóżmy szable. Będziesz miał dość czasu, by się wydostać, a ja skoczę ze statku, Galera Point jest stąd niemal na wyciągnięcie ręki. Jeśli potrzebujesz złota, weź je! Pięćset dublonów, gotówka na miejscu - i zapominasz o mnie, a ja o tobie! Zgoda?";
				link.l1 = "Złoto? Zacząłem to wszystko nie dla pieniędzy, Juan, ale by zabijać szumowiny, a ty sam jesteś największą nagrodą.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Pięćset doublonów? Żartujesz sobie ze mnie, Konsumpcjo. Myślę, że masz tutaj przynajmniej dwa razy tyle... Daj mi tysiąc teraz i możesz iść do diabła, w przeciwnym razie...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "Statek zaraz wybuchnie, więc będę miał dobre towarzystwo, co myślisz?";
				link.l1 = "Za dużo gadasz, Konsumpcja, zabieraj się do roboty!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "Mogliśmy się dogadać... Eh, nieważne!";
			link.l1 = "Zabrałeś tych biedaków z ich cel, a oni nie mogli się ani opierać, ani uciec. Jesteś tchórzem, Consumption, i teraz zginiesz jako tchórz.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "Masz łeb do interesów, przyjacielu... Proszę - to wszystko, co mam. Niewiele za życie, prawda?";
			link.l1 = "Twoje życie nie jest warte kuli, więc wygląda na to, że to najbardziej opłacalny interes w moim życiu. A teraz zjeżdżaj.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "Szkoda, że nie będziesz miał czasu, by wszystkich ocalić i mnie zabić, prawda? Knot się pali, a czas mija...";
			link.l1 = "Do diabła! Muszę stąd wyciągnąć ludzi... Zjeżdżaj, łajzo - prędzej czy później dostaniesz, na co zasłużyłeś!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "Spróbuję mimo wszystko...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ach... Brak mi słów... Co za koszmar!";
			link.l1 = "Ach, nie mogłem nic zrobić. Przykro mi, dziewczyno. Żegnaj.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Niewiarygodne! Ty... naprawdę go uratowałeś? Nie mam pojęcia, jak ci dziękować.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "Potrafię to sobie wyobrazić, piękna. Ale moja część umowy jest już zakończona - pozostaje tylko jedna mała rzecz.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "Obowiązek wzywał - i działałem. To wszystko.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Ja... o Boże! Masz rację. Dla niego, jak obiecałem... Idź na górę do pokoju - nie mamy dużo czasu.";
			link.l1 = "Pospieszmy się, zatem!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "Oto jestem, mój dzielny caballero! I spójrz, co ze sobą przyniosłem.";
			link.l1 = "Ho ho, jestem pod wrażeniem, otwórzmy to wiśniowe wino! Potem otworzymy coś jeszcze... To twój szczęśliwy dzień w końcu... Ha-ha!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Jesteś prawdziwym rycerzem! Caballero! Proszę - nie traktuj tego jako zniewagi, ale chcę, żebyś to wziął. Zbierałem te pieniądze, aby wykupić Angelo, ale teraz to nie jest ważne! Proszę, nie odmawiaj - weź to!";
				link.l1 = "Cóż, zapamiętam twoje oczy, señorita - są o wiele piękniejsze, gdy błyszczą łzami szczęścia, a nie bólu. Przyjmuję twój dar. Żegnaj, i powodzenia tobie i Angelo.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Jesteś prawdziwym rycerzem! Caballero! Powiem wszystkim! Zawsze będę Cię pamiętać!";
				link.l1 = "Cóż, a ja zapamiętam twe oczy, señorita - są o wiele piękniejsze, gdy lśnią łzami szczęścia, a nie bólu. Niechaj zawsze będziesz szczęśliwa. Żegnaj!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
