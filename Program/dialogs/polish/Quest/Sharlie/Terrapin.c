// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czego potrzebujesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "Pana pułkownika obecnie nie ma, jest na manewrach wojskowych. Czego od niego chcesz, kapitanie?";
				link.l1 = "Tym razem, Ben, to ciebie potrzebuję. Mam złe wieści o twojej siostrze Molly. Ta piękna dziewczyna najwyraźniej wpadła w tarapaty. Została schwytana przez piratów z Tortugi. Potrzebuje pomocy i prosiła, aby cię ostrzec. Człowiek, który podjął się przekazania wiadomości, został zabity, ale przed śmiercią udało mu się opowiedzieć mi o twojej siostrze.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "Jeśli idziesz do pułkownika Foxa, to odwróć się o 360 stopni i odejdź. Nie przyjmuje gości.";
				link.l1 = "Bardzo dobrze zatem.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Pułkownika nie ma tutaj. Przyjdź później.";
				link.l1 = "Dobrze...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ha! Jesteś pierwszym człowiekiem, który nazwał moją siostrę 'piękną'. Bóg dał jej ciało grenadiera i róg Jerycha zamiast głosu. Nasza Molly potrafi o siebie zadbać\nAle kreatywność naszego Pana nie zakończyła się na wszystkim poniżej jej brody. Nie, nie, najlepszą rzeczą, którą zrobił, było umieszczenie włochatej, pokrytej ospą twarzy naszego zmarłego ojca powyżej jej piersi. I muszę powiedzieć, panie, twarz mojego starego sprawiała, że konie mdlały.";
			link.l1 = "Widzę, że nie jesteś szczególnie zmartwiony...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "A dlaczego miałaby pojawić się na Tortudze? Molly jest służącą Catherine Fox, córki naszego dzielnego pułkownika. Catherine przybywała z Europy, aby odwiedzić ojca w jego urodziny. Ale eskadra, z którą płynął jej statek, została opóźniona\nJeśli chcesz zobaczyć prawdziwą Molly Jones i jej panią, która nawiasem mówiąc jest bardzo piękna, przyjdź tu za miesiąc. Ani dnia wcześniej.";
			link.l1 = "Okazuje się, że twoja siostra Molly Jones służyła pani Fox i w chwili obecnej przebywa po drugiej stronie Atlantyku?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Dokładnie tak! Ostatni kurier poinformował nas, że eskadra marynarki wysłana przez samego Lorda Protektora Cromwella miała opuścić Londyn zaledwie miesiąc temu. Bryg 'Albatros' z Catherine na pokładzie miał im towarzyszyć. Dowiemy się, czy tak jest naprawdę, z następnego listu na statku pocztowym. Chociaż statki jeszcze nie przybyły, a pułkownik surowo zabronił 'Albatrosowi' pływać samodzielnie.\nCzy wiesz, że jego ukochana żona zginęła podczas ataku francuskich korsarzy? To nie było łatwe dla pułkownika i wciąż boi się niebezpieczeństw na pełnym morzu... Więc nie mogę ci pomóc z Molly Jones, kapitanie! Jest wiele kolonialnych dziewcząt o imieniu Molly! Poza tym, posiadanie nazwiska Jones w Wielkiej Brytanii jest tak dobre, jak nie mieć nazwiska wcale!\nKażdy wilk morski na Antigui zna mnie i mojego dowódcę. Nie dziwi mnie, że jakaś biedna dziewczyna, która wpadła w kłopoty, chce mojej pomocy. Chciałbym, ale nie mam pieniędzy na okup. Pułkownik jest mi winien trzy miesiące wypłaty, moja pensja wraz z pensjami wszystkich innych przybywa z 'Albatrosem'.";
			link.l1 = "Najwyraźniej się pomyliłem. Ale i tak dziękuję za wyjaśnienie.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Wcale nie, kapitanie.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "Czego chcesz?! Nie chcę rozmawiać.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "Mam dla ciebie pewne zadanie, kapitanie. Widzę, że nie jesteś w radosnym nastroju i może moja propozycja cię nieco rozweseli.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Ucisz się, napij się rumu. Mój błąd, kumplu. Przepraszam.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "Brzmi to całkiem kusząco! A twoja twarz wygląda jakbym ją już gdzieś widział... Tylko nie mogę sobie przypomnieć, gdzie cię widziałem. Powiedz mi!";
			link.l1 = "Jestem świadomy twoich interesów z Thibautem... Spokojnie, kumplu! Nie musisz się mnie obawiać. Mam dla ciebie propozycję.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Do diabła! Jebać tego pijanego wieprza!... Nie udało mi się...";
			link.l1 = "Masz rację. Twój marynarz miał niewyparzoną gębę, ale jego plotki nie dotarły nigdzie dalej niż do mnie. I te plotki nie pójdą dalej, skoro to ty się tym zająłeś, prawda?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Karamba! Teraz cię rozpoznaję! To ty zrobiłeś bigos z pułkownika Doileya i przejąłeś całą jego wyspę! Byłeś zamieszany w jakieś wielkie interesy z Holenderską Kompanią Zachodnioindyjską, ocierasz się o barona z Zachodnich Indii.... Twoje imię to... "+GetFullName(pchar)+", prawda?";
			link.l1 = "Posiadasz dość dokładne informacje. Tak, to ja. Ale czy mógłbyś się na chwilę uspokoić, Robercie?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh!  No jakże mam się uspokoić, gdy jeden z najsłynniejszych wilków morskich archipelagu zainteresował się mną, i nie tylko to, dowiedział się też o moich interesach! Co mnie, do cholery, podkusiło, by zaatakować tę brygantynę! Czego ode mnie chcesz?";
			link.l1 = "Zamknij gębę i posłuchaj mnie. Wygląda na to, że obaj chcemy głowy Levasseura na talerzu. Ten napuszony chełpliwiec urósł zbyt wysoko i rozzłościł poważnych ludzi. Zamierzam zmienić równowagę sił na wyspie i umieścić de Poincy'ego na jego miejscu, ale nie chcę rozlewać nadmiaru krwi moich rodaków, zwłaszcza z powodu jakiegoś brudnego złodzieja. Możesz mi pomóc. A ja mogę pomóc tobie i Thibautowi zachować wasze przywileje.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Poczekaj, poczekaj! Nie mogę uwierzyć własnym uszom! Fortuna dziś mi sprzyja. Masz rację, dzielimy te same cele. Z tobą może być to znacznie ciekawsze... Thibaut to dobry szermierz, ale nie ma jaj, żeby poderżnąć gardło swojemu wujowi... Ale sprytny rekin jak ty mógłby to zrobić. Twoja sława jest dobrze znana\nNie potrzebuję twoich gwarancji, ale pomogę ci w zamian za dziewczynę. Potrzebuję jej jako zakładnika, dopóki nie skończę swoich interesów na Karaibach. Wkrótce angielskie fregaty zaczną mnie ścigać. Co mnie, do diabła, podkusiło, żeby zaatakować ten bryg! Wyglądał na tak łatwą zdobycz oddzieloną od eskadry...";
			link.l1 = "Co było w niej takiego wyjątkowego? Dziewczyna, którą ukrywałeś przed Levasseurem?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Tak. Musisz przekonać Thibauta, by rozstał się z dziewczyną. Poprosiłem go, by się nią zajął, dopóki nie dowiem się, kim jest ten diabeł, ale ta 'Panna Jones', czy jak jej tam, całkowicie zawróciła mu w głowie, a teraz Henry nawet ją przede mną ukrywa! Sprowadź mi tę czarującą syrenę, a zorganizuję dla ciebie spotkanie z Levasseur'em poza miastem. W tym momencie będziesz miał okazję go zasadzić. Będę czekał na Plaży Rybim Oku.";
			link.l1 = "Umowa stoi. Teraz powiedz mi, jak złapać Thibauta.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "Ludzie w karczmie mogą pokazać ci drogę do jego domu. Henri jest całkiem wyjątkowy. Zagroź mu ujawnieniem i zmusić, by przyprowadził dziewczynę do mnie. Tego samego dnia dam znać Levasseurowi, że jego siostrzeniec ukrywa rzadką piękność w miejskim lochu\nMój kurier znajdzie cię w karczmie. Po tym, jak nie uda mu się znaleźć Henriego, gubernator uda się do lochu z małym oddziałem, a ty będziesz miał okazję z nim porozmawiać.";
			link.l1 = "Gdzie mam dostarczyć dziewczynę?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Powiedz mu, żeby sam ją dostarczył na plażę. Powiem mu przy okazji parę słów...";
			link.l1 = "Dobrze. Umowa stoi. Do zobaczenia na Tortudze!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "Jeśli wszystko pójdzie zgodnie z planem, nigdy więcej się nie spotkamy. Przynajmniej mam taką nadzieję. Żegnaj!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Argh! Nie spodziewałem się tego... Przyszedłeś po moją duszę, prawda, kamracie? Wszystko zrobiłem zgodnie z umową! Co do diabła?!";
			link.l1 = "Masz na sobie wyrok, Robercie. Wyrok został mi powierzony do wykonania. Więc wypełniam swoje zadanie.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "Ty demonie! To niemożliwe! Nie mógł wszystkiego odkryć tak szybko! I jak w ogóle to odkrył?!";
			link.l1 = "Masz na myśli Fox'a? Nie. On mnie nie przysłał. Pułkownik nadal nawet nie wie, że jego córkę już uśmierciłeś. To twój stary kumpel Henry Thibaut chce cię martwego. On mnie wynajął.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Ten przeklęty katamit! Powinienem był nakarmić nim kraby, gdy był na 'Voltigeur'... Ile ci ten drań obiecał?";
			link.l1 = "Nie codziennie człowiek dowiaduje się, jaka jest cena za jego głowę, prawda Robert? Thibaut wycenił cię na ćwierć miliona, ale przekonałem go, że jesteś wart więcej. Jesteś wart trzysta tysięcy srebrnych peso, mój przyjacielu. Nie cieszysz się?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Poczekaj chwilę... Zróbmy interes! Zapłacę ci więcej!";
			link.l1 = "Jakimi pieniędzmi, Robercie? Jestem absolutnie pewny, że kłamiesz. Nie masz tyle pieniędzy, ile obiecał mi Henry. A to i tak nie jest najważniejsze. Gdyby nie jeden fakt, odrzuciłbym jego propozycję, żeby cię ścigać i zakończyć twoje brudne interesy z Thibautem.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "Co to za fakt?";
			link.l1 = "Zabiłeś Catherine Fox. Wina tej biednej dziewczyny polegała tylko na tym, że była córką pułkownika Foxa. Nienawidzę pogardliwych tchórzy jak ty, którzy skazują na śmierć bezbronne kobiety! Nie będę z tobą robił żadnych interesów. Nawet o tym nie pomyślę. Nie trać czasu.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Cholera! Co jeszcze mogłem zrobić?! Nie mogłem pozwolić jej żyć i ukrywać w nieskończoność na łodzi! A kim ty jesteś... ty łobuzie, ty draniu, ty zabójco, by mnie pouczać o moralności! Spójrz na siebie! Na swoje 'metody'! Nie jesteś lepszy ode mnie!";
			link.l1 = "Dosyć. Martene, dobywaj ostrza! Czas to zakończyć.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Zobaczymy się w piekle!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Co robisz w moim domu, monsieur?";
			link.l1 = TimeGreeting()+", monsieur Thibaut. Jestem tutaj w imieniu człowieka, którego znasz, kapitana Roberta Martene'a.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hm. I? Co z tego?";
			link.l1 = "Kapitan Martene prosi o zaszczyt twojego towarzystwa właśnie teraz na Plaży Rybiego Oka. Ale nie w pojedynkę. Chciałby również zobaczyć Molly Jones w twoim towarzystwie. Rozumiesz, co mam na myśli?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Ach, panie, nie znam. Nigdy nie słyszałem o żadnej Molly Jones, a Robert nigdy nie miał potrzeby wysyłać do mnie... pełnomocnika, którego nigdy wcześniej nie widziałem. Dla twojej informacji, monsieur, jestem drugim człowiekiem na tej wyspie po moim wuju gubernatorze, więc...";
			link.l1 = "Życie to nieprzewidywalna bestia, Henryku... Teraz jesteś drugim człowiekiem na wyspie, a za parę godzin możesz być w kajdanach w kazamatach... Wszystko za życie kogoś, kto nie dałby ci ani jednego peso. Nie posłuchałeś rozkazu wuja, prawda, monsieur Thibaut? Co jest dla ciebie ważniejsze: rozpustna dziewczyna czy twoje życie?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Dlaczego ty... Kłamiesz! Pleciesz bzdury!";
			link.l1 = "Ty, jak każdy inny, musisz wiedzieć, jak ognisty potrafi być temperament twego wuja. Levasseur odkryje, że ukrywasz dziewczynę, zanim słońce zajdzie. Nie pytaj mnie, skąd Robert się o tym dowiedział, po prostu posłuchaj moich słów: jest przerażony na śmierć i gotowy natychmiast podnieść kotwicę. Nie odważył się nawet wejść do miasta i zapłacił mi pokaźną sumę, by przekazać ci tę wiadomość.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Cholera... To niemożliwe!";
			link.l1 = "To zależy od ciebie, panie. Martene nie będzie czekał na ciebie dłużej niż dwie godziny. Ceni swoją własną głowę na karku. Tylko jako znak przyjaźni wciąż kręci się w pobliżu brzegu Tortugi, zamiast ukrywać się gdzieś z Holendrami.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Karamba! Jak mój wujek mógł się o tym dowiedzieć?";
			link.l1 = "Języki, Henry. Gadające języki. Nawet ja wiem, że ty i Robert złapaliście piękność, która zeszła z angielskiej brygantyny przejętej przez twego kumpla. Ukryliście ją przed Levasseurem... tsk tsk. Naprawdę wątpisz, że jestem jedynym, kto wie o tej historii?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Wygląda na to, że mówisz prawdę, sir. Powiedz Martene...";
			link.l1 = "Nie sądzę, że rozumiesz, Henry. Martene nie będzie na ciebie czekać. Twoją jedyną nadzieją jest wyciągnąć stąd tę dziewczynę, powód, dla którego zarówno ty, jak i Robert macie pętle na szyjach. Biegnij tam, gdzie ją ukrywasz, weź ją za jej śliczne małe rączki i przyprowadź ją do Voltigeura. Znajdź ją szybko i przyprowadź jeszcze szybciej. Twój wujek ode mnie o tym nie usłyszy.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "Dobrze. Zrobimy to zatem. Dzięki za twe dobrodziejstwo, panie!";
			link.l1 = "Nie ma potrzeby dziękować mi, monsieur. Moja praca jest opłacana... Chcę tylko, żebyś wyszedł z zupy, zanim się ugotujesz.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Co tu robisz, panie? Nie zapraszałem cię tutaj.";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Przybyłem od człowieka, którego znasz. Nazywa się kapitan Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. I? Co z tego?";
			link.l1 = "Kapitan Martene prosi o zaszczyt twego towarzystwa teraz na Plaży Rybiego Oka. Ale nie samemu. Doceniłby również widok Molly Jones w twym towarzystwie. Rozumiesz, co mam na myśli?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Niestety, panie, nie mam.";
			link.l1 = "Tak właśnie się spodziewałem, że powiesz. Oczywiście wątpię, byś wcześniej poznał córkę pułkownika Foxa, znasz pułkownika Foxa oczywiście, dowódcę słynnych Morskich Lisów... postrachu wrogów Anglii na Karaibach? Ty i Robert narobiliście takiego zamieszania, że to cud, że jeszcze was nie użądliły! Dziewczyna Molly Jones, którą pojmałeś z angielskiego brygu i ukrywałeś przed Levasseurem, jest córką pułkownika Foxa, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "C-c-co?";
			link.l1 = "Zbladłeś całkiem, panie. Teraz słuchaj mnie uważnie, Henry, i miej na baczności: ty i twój kumpel Robert tkwicie po uszy w gównie. Każdego dnia eskadra morska Cromwella może dotrzeć na Karaiby. Będą na was polować. Sama ich flagowa jednostka jest w stanie w ciągu kilku godzin zamienić twoją osławioną La Roche i załogę w drzazgi i siekaninę. Co myślisz? Czy atak na ten angielski bryg i niewola córki Foxa były tego warte?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "Lecz to nie wszystko. Twoje machinacje stały się znane nie tylko mnie. Twój drogi wujek gubernator dowie się, że łamiesz jego surowe rozkazy i ukryłeś przed nim dziewczynę, którą stary lubieżnik z pewnością chciałby wziąć dla siebie. Jak myślisz, Henry? Co twój wujek zrobi z tobą? Musisz wiedzieć jak nikt inny, jak ognisty jest jego temperament...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "Wszystko kłamstwa!";
			link.l1 = "Czyżby? Mój drogi Henry, możesz zapytać swojego przyjaciela Martene'a. To on mnie wysłał. Levasseur dowie się, że ukrywasz dziewczynę, zanim słońce zajdzie. Nie pytaj mnie, jak Robert się o tym dowiedział, po prostu posłuchaj moich słów: jest przerażony na śmierć i gotów podnieść kotwicę i odpłynąć od razu. Nie odważył się nawet wejść do miasta. Dlatego poprosił mnie, bym przekazał ci tę wiadomość.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene nie będzie cię czekać dłużej niż dwie godziny. Ceni swoje własne życie. Tylko z powodu waszej przyjaźni wciąż przebywa na brzegu Tortugi, a nie chowa się gdzieś z Holendrami. Jednak ten biedny Robert nawet nie podejrzewa, kim naprawdę jest Molly Jones. Wiecie, wy naprawdę zadziwiacie mnie swoim niesamowitym brakiem znajomości mody i wyglądu kobiet! Nie potrafilibyście nawet odróżnić szlachcianki od jej służącej!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "Czego chcesz?";
			link.l1 = "W końcu jakieś mądre słowa od młodego pyszałka! Dobrze, Thibaut: idź tam, gdzie ją ukrywasz, chwyć ją delikatnie za jej lilijowe dłonie i szybko przejdź z nią na Plażę Rybiego Oka, gdzie jest 'Voltigeur' Martene'a. Powiedz mu, że plany się zmieniły...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene musi spełnić swoją obietnicę wobec mnie, nie powinien nawet próbować zabrać dziewczyny na swój statek. Ona zostanie na plaży i będzie na mnie czekać. Powiedz Robertowi, że jeśli nie spełni swoich zobowiązań, albo zabierze Catherine, albo jeśli jeden włos spadnie z jej pięknej główki, spędzę resztę życia na jej poszukiwaniach. A kiedy ją znajdę, dostarczę ją pułkownikowi Fox... żywą. Ale dla was dwóch... przywiozę was w kawałkach. Tak, nawiasem mówiąc, to dotyczy także ciebie, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Kim jestem i jakie mam możliwości, możesz zapytać Roberta. On doskonale wie. Jeśli obaj zrobicie tak, jak powiedziałem, wszyscy wygramy. Robert będzie mógł kontynuować swoje pirackie interesy, a ty zachowasz wszystkie swoje przywileje i otrzymasz spadek po swoim drogim starym wujaszku, gdy ten wykorkuje. A co do mnie... Ja też nie wyjdę na przegranego. Czy to wszystko jasne?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "Wolę spłonąć w wiecznym ogniu piekielnym, niż spełniać twoje żądania... "+GetFullName(pchar)+"! Jakże to, że nie rozpoznałem cię od początku? Rzeźniku! Nie zamierzasz zostawić mnie ani Roberta przy życiu! Twoje 'metody' są powszechnie znane! Nie ma mowy, żebym oddał Molly... czy Catherine, jeśli o to chodzi, łajzie takiej jak ty! Nie opuścisz Tortugi żywy, skurwielu!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Stój, tchórzu!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "W końcu! Kapitanie "+GetFullName(pchar)+", jestem bardzo zadowolony, że przyszedłeś. Wejdź, usiądź. Coś do picia? Mam dla ciebie całkiem intratną propozycję biznesową, mój przyjacielu...";
			link.l1 = "A niech mnie, czyżbyś był dzisiaj w najgrzeczniejszym z nastrojów, Monsieur Thibaut... Nie ociągajmy się. Przejdźmy od razu do sedna sprawy.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "Propozycja dotyczy mojego dawnego przyjaciela i towarzysza, którego znasz jako Roberta Martene, byłego kapitana galeonu 'Voltigeur'...";
			link.l1 = "Więc ty i Robert nie jesteście już kompanami? Fascynujący rozwój wydarzeń.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Kapitanie, proszę, wysłuchaj moich powodów, dla których szukam twojej pomocy, a wszystko stanie się jasne. Jak sam wiesz, Martene zmagał się z angielskim brygiem i pojmał jako więźniarkę Angielkę, jakąś służącą znaną jako Molly Jones, cały powód, dla którego te wszystkie kłopoty się rozpoczęły.";
			link.l1 = "Oczywiście, wiem. Jak rozumiem, spełniłeś moje zalecenia i doprowadziłeś dziewczynę na statek Martene'a?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Tak, zrobiłem to. Ale żałuję tego każdego dnia. Musisz wiedzieć, że Molly to bardzo urocza i piękna dziewczyna, nigdy wcześniej nie spotkałem nikogo takiego jak ona. Muszę przyznać, zakochałem się w niej. Ona też mnie lubiła, sama tak powiedziała! Nie mogłem pozwolić, by mój wuj ją zabrał\nKiedy eskortowałem ją na 'Voltigeur', miałem nadzieję, że wujek się uspokoi, gdy tylko dowie się, że nikt nie ukrywa przed nim dziewczyn, stary rozpustnik. Wtedy Robert zabrałby ją z powrotem na Tortugę, żebym mógł bezpiecznie przenieść ją do siebie. W każdym razie, taki był układ z Martenem. Ale wszystko potoczyło się inaczej\nGdy dowiedziałem się, że mój wujek został zabity, nie było sensu ukrywać Molly, więc cierpliwie czekałem na przybycie 'Voltigeur' z Molly na pokładzie.";
			link.l1 = "Czy ona przybyła?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Tak. Niestety, Molly nie było na statku. Robert był wstrząśnięty, jakby sam Lucifer go spotkał. Podczas swojej krótkotrwałej ekspedycji, jakoś dowiedział się jednego strasznego szczegółu: dziewczyna, Molly, wcale nie była Molly Jones, lecz Catherine Fox! Sama córka pułkownika Foxa, dowódcy Morskich Lisów, elitarnego angielskiego regimentu morskiego! Wiesz, co to oznacza!";
			link.l1 = "Cholera jasna, cóż za niespodzianka! Bez wątpienia Robert ma się czego obawiać. Ale jak to się mogło tak stać?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "Kiedy Catherine została pojmana, celowo ukryła swoją tożsamość, udając Molly Jones, służącą, która zginęła podczas abordażu. Bała się, że Martene odkryje, kim naprawdę jest. I udało jej się go oszukać. Ale podczas ostatniego rejsu Robert jakoś dowiedział się, kim naprawdę jest. Powiedział, że znalazł jakieś jej listy albo dokumenty...";
			link.l1 = "A gdzie teraz jest dziewczyna, jeśli nie weszła na 'Voltigeur'?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "Nie żyje. Przerażona bliską karą od Foxa za atak na angielską brygantynę, Martene postanowił ukryć jedyny pozostały dowód w wodzie. Była ostatnim świadkiem jego ataku na 'Albatrosa'.";
			link.l1 = "Wtedy mógłby równie dobrze zamordować wszystkich swych marynarzy... Jak Fernand Luc. W przeciwnym razie, pewnego dnia upiją się i za szeroko otworzą usta w karczmie...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "On czuje, że cała jego załoga przysięgła mu wierność krwią. Może ma częściowo rację. Ale ja znam pułkownika Foxa! Będzie kopał aż do końca swoich dni, aby dowiedzieć się, kto porwał jego córkę!";
			link.l1 = "Nie wątpię w to. Zwłaszcza po tym, jak francuski pirat zabił jego żonę. Teraz jego córka też... Nawiasem mówiąc, jesteś absolutnie pewien, monsieur, że Catherine naprawdę nie żyje? Może Robert ukrył ją gdzieś przed tobą.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "Jestem pewien. Rozmawiałem z marynarzem z 'Voltigeur'. Uwierzyłem mu. Widział to na własne oczy, jak poderżnęli dziewczynie gardło, a potem przywiązali do jej stóp kulę armatnią i wrzucili ją za burtę.";
			link.l1 = "Boże w niebie! Ta biedna kobieta... czego ode mnie chcesz, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "Nie mogę spać po nocach od tamtego dnia. Wciąż widzę Molly przed oczami... Catherine, raczej. Poprowadziłem ją na śmierć, "+GetFullName(pchar)+". Nie mogę sobie tego wybaczyć. Ponadto, nie mam żadnych złudzeń co do Foxa. Ten człowiek nie jest zadowolony i nie sądzę, żeby w ogóle spał. Prędzej czy później, wpadnie na trop Martene'a, zmusi kogoś do mówienia, a kiedy dowie się, kto zabił jego córkę, rozpęta się piekło. Ciężko będzie każdemu, kto w jakikolwiek sposób był związany z całą tą historią.";
			link.l1 = "To obejmuje mnie.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Aye, mnie też. Dlatego chcę, abyś znalazł Martene'a, zanim zrobi to Fox. Znajdź tego drania i zabij go. A jeśli możesz, spraw, by cierpiał. Dla biednej Catherine. Gdy to zrobisz, odetnij ten gruby pierścień, który nosi na ręce z palcem w środku i przynieś mi go jako dowód\nZnam jego krzywy palec i ten pierścień dobrze. Jeśli to zrobisz, zapłacę ci ćwierć miliona w srebrze.";
			link.l1 = "Wygląda na to, że dostałeś spadek po swoim drogim, starym wujaszku, który spoczywa w pokoju, co? Powiedz mi, Henry, czemu postanowiłeś poprosić mnie o pomoc w tej sprawie?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Ponieważ dowiedziałem się również kilku rzeczy o tobie, "+GetFullName(pchar)+". To było łatwe, jesteś sławnym człowiekiem. Nie wiadomo jednak, dla kogo naprawdę pracujesz, czy dla de Poincy, czy dla Holendrów, czy dla Anglików, czy dla barona Jana Svensona... Ale jedno jest jasne: podejmujesz się delikatnych, dyskretnych zadań i wykonujesz je. Potem jesteś za nie sowicie wynagradzany. A co najlepsze, nie masz powiązań z Hiszpanami\nW końcu, brałeś udział w wydarzeniach, po których odziedziczyłem fortunę mojego wujka. Nie zaprzeczaj... Ćwierć miliona to dobre pieniądze. Powiem ci, gdzie znaleźć Martena. Musisz tylko przechwycić jego statek i go abordażować.";
			link.l1 = "Jeszcze sto tysięcy i zajmę się Martenem dla ciebie.";
			link.l1.go = "tibo_34";
			link.l2 = "Ach, monsieur Thibaut, będziesz musiał poradzić sobie z waszym problemem z Martenem i pułkownikiem Foxem beze mnie. Ze swojej strony obiecuję ci, że nie przekażę żadnej wieści pułkownikowi o losie jego córki i tych, którzy są winni jej śmierci. Wszystkiego najlepszego, sir.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Panie, bój się Boga... Nie mam milionów ukrytych w skrzyniach skarbów, uwierz mi! Rozumiem, że twoje usługi kosztują, dlatego od razu zaoferowałem ci dwieście pięćdziesiąt tysięcy... Dobrze... No cóż, dodam jeszcze pięćdziesiąt tysięcy złota. Nie mogę ci zaoferować więcej!";
			link.l1 = "Dobrze. Umowa stoi. Gdzie ostatnio widziałeś Martene?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "Płynął na południe do hiszpańskich posiadłości w Karakas i udało mu się uzyskać audiencję u Don Diego Francisco de Kerres, gubernatora. Wydaje się, że jakoś go przekupił, ponieważ Don Diego przyznał Robertowi ochronę hiszpańskiej korony. Sprzedał 'Voltigeur' i teraz jest kapitanem ciężkiego galeonu 'Infanta'. Musiał mieć naprawdę dobre oszczędności, skoro mógł sobie pozwolić na przekupienie gubernatora oraz zakup i wyposażenie tak dużego okrętu wojennego. Następnie wypłynie z Karakas do Santo Domingo na swoim nowym statku jako część hiszpańskiej eskadry. To wszystko, co mój agent zdołał odkryć. Jedyną szansą na złapanie Martene jest dogonienie tej hiszpańskiej eskadry. Jeśli dotrą do Santo Domingo, to koniec. Nie wiadomo, dokąd Robert uda się dalej. Zniknie jak królik w norze i nigdy go nie znajdziemy.";
			link.l1 = "Zrozumiano. Przechwycę ich.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "I nie zapomnij o palcu z pierścieniem! To obligatoryjny warunek naszej umowy! Chcę być absolutnie pewien, że Robert nie żyje!";
			link.l1 = "Dobrze. Nie traćmy czasu, wyruszam natychmiast!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Tryb eksploracji: timer nie jest wyłączony. Dotrzymaj terminu!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Czy Martene wciąż zasmradza Karaiby swoją obecnością, kapitanie?";
			link.l1 = "Nie ma już dużo czasu!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Czy Martene zasmradza Karaiby swoją obecnością, kapitanie?";
			link.l1 = "Już nie. Nie musisz się obawiać pułkownika Foxa i twoja Catherine została pomszczona. Oto twój dowód.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Tak... To jest palec Martene'a, bez wątpienia. Nigdy nie przestajesz mi imponować, Kapitanie "+GetFullName(pchar)+"! Naprawdę zasługujesz na reputację, którą ci przypisują.";
			link.l1 = "Przejdźmy do zapłaty, dobrze, Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("Otrzymałeś 500 dublonów");
			PlaySound("interface\important_item.wav");
			dialog.text = " Wszystko gotowe. Prosze, weź swoją nagrodę.";
			link.l1 = "Moja wdzięczność. Cieszę się, że udało ci się to przygotować z wyprzedzeniem. Cóż, Henry, mam nadzieję, że nie wpadniesz w dalsze tarapaty jak te i w przyszłości wybierzesz lepszych przyjaciół. Wszystkiego najlepszego!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Dziękuję za pomoc, kapitanie! Polecę cię wszystkim znajomym. Powodzenia!";
			link.l1 = "... ";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Tak, monsieur "+GetFullName(pchar)+" ? Czy masz do mnie jakąś sprawę?";
			link.l1 = "Nie, monsieur Thibaut. Po prostu postanowiłem wpaść na chwilę. Do widzenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ach, "+GetFullName(pchar)+"...No dalej, co tak długo cię zatrzymuje! Teraz, kto do diabła wie, gdzie jest Robert Martene?! Jeśli pułkownik Fox dowie się wszystkiego, myślę, że będę w niezłych tarapatach...";
			link.l1 = "Rozumiem. Byłem za późno. Moje przeprosiny, Monsieur Thibaut, ale opóźniły mnie pewne bardzo pilne sprawy. Nie będę marnować twojego czasu. Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "Czego chcesz, "+GetFullName(pchar)+". Nie mam czasu na pogawędki. Mam ważniejsze sprawy na głowie. Muszę znaleźć Martene, zanim zrobi to Fox...";
			link.l1 = "Tak, tak. Już idę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Czy jesteś kapitanem "+GetFullName(pchar)+"?";
			link.l1 = "Trafiłeś na właściwego człowieka, kumplu. Jestem cały uszy.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Twój wierzyciel poprosił mnie, aby Ci przekazać, że czyn został dokonany, a ryba wpłynie do sieci za niecałą godzinę. Więc pośpiesz się.";
			link.l1 = "Rozumiem. Dziękuję!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Do diabła, co ty tu robisz? Kim jesteś? Odpowiadaj natychmiast!";
			link.l1 = "Kim, do cholery, jesteś i dlaczego zadajesz mi takie głupie pytania?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "Co?! Ty smarkaczu bez nosa! Kim jestem? Jestem gubernatorem tej wyspy, François Levasseur, Senior de Renet de Boidouflet de Lettre! I wszystko na tej wyspie jest pod moją jurysdykcją! To dotyczy ciebie, kiedy jesteś na moim terenie, szczeniaku!";
			link.l1 = "Prosze, prosze... Sam wielki zły wilk, co? Trochę się zgubiłeś, Levasseur, Senior de Renet de cokolwiek to było. Twój czas się skończył. Na rozkaz gubernatora generalnego François Longvillier de Poincy zostałeś usunięty ze stanowiska i skazany na natychmiastową śmierć! Jestem twoim sędzią i katem w jednym! Jakieś ostatnie słowa?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "Przypuszczam, że nie zamierzasz się poddać, a błaganie o litość na nic się nie zda, więc dobywaj stali!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Cholera! To agent de Poincy! Do broni! Zabij go!";
			link.l1 = "Zatańczmy.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "Co, do cholery, tu robisz? Kim jesteś? Odpowiadaj, natychmiast!";
			link.l1 = "A to ci dopiero! Tego się nie spodziewałem... Sam pan Levasseur, jak mniemam?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Tak, jestem gubernatorem tej wyspy, Francois Levasseur, Senior de Renet de Boidouflet de Lettre! I wszystko na tej wyspie jest w mojej jurysdykcji! I ty również, gdy stąpasz po moim terenie, łotrze! Odpowiadaj na pytania! Sierżancie, zamknij te drzwi. Ten człowiek ma złe zamiary!";
			link.l1 = "Jesteś niezwykle przenikliwy, monsieur Levasseur, Senior de Renet de cokolwiek. Moja obecność tutaj nie sprawi ci radości. Na rozkaz generała-gubernatora François Longvillier de Poincy zostałeś usunięty ze swojego stanowiska i skazany na natychmiastową śmierć! Jestem twoim sędzią i katem w jednym!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "Przypuszczam, że się nie poddasz, a proszenie mnie o łaskę ci nie pomoże, więc dobywaj stali! Jesteś moim zadaniem, nic osobistego. Po prostu służę Koronie, ha! Sierżancie, nie radzę ci się wtrącać, gdy będę wykonywał rozkazy generała-gubernatora!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Nie słuchaj go, sierżancie! On jest hiszpańskim agentem! Zabijcie go! Straże, pomocy! Są tu Hiszpanie!";
			link.l1 = "Tak naprawdę nigdy nie byłem w Hiszpanii, tylko w Narbonne.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Auć! Pomocy! Żołnierze!";
			link.l1 = "Zamknij się, głupcze! Jeśli nie będziesz krzyczeć, nic ci nie zrobię!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Nie zabijaj mnie!";
			link.l1 = "Nie bądź głupia! Przed chwilą przebiegł tędy człowiek, dziesięć minut temu. Dobrze ubrany szlachcic. Gdzie się ukrywa? I nawet nie próbuj mi mówić, że go nie widziałaś!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut?";
			link.l1 = "Cóż, znasz go zatem! Dokąd uciekł? Zamierzasz odpowiedzieć, czy mam potrząsnąć twoją głową, żeby zaczęła działać?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "O nie, proszę, nie krzywdź mnie! Monsieur Thibaut uciekł, tam w stronę morza. I skoczył z dźwigu prosto do wody. Pewnie zginął, to tak wysoko...";
			link.l1 = "Nie sądzę. On nie jest typem, który popełniłby samobójstwo. Powinnaś wejść do środka. Niebezpiecznie jest być tutaj na zewnątrz tej nocy..";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Auć! A-auć! Nie strzelaj!";
			link.l1 = "Co?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Kimże jesteś? Przyszedłeś mnie zabić czy... gorzej?";
			link.l1 = "Nic podobnego, madame. Odwiozę cię, Catherine Fox, do twego ojca w St. John's. Jeśli po tym cię ukarze za nieposłuszeństwo, moja wina się powtórzy. Jednakże mam nadzieję, że pułkownik ucieszy się, widząc swoją córkę żywą, mimo wszystkich zmartwień, które mu przysporzyła.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Dzięki Bogu! Muszę śnić! Nie wiesz kim jestem? Jesteś Francuzem i katolikiem, a mimo to zdecydowałeś się przybyć tutaj, by mnie ratować z rąk moich własnych rodaków? Zaryzykowałeś swoje życie tylko dla córki pułkownika Foxa?";
			link.l1 = "Powód mojego pobytu na Tortudze był zupełnie inny. Ale nie mogłem też zostawić pięknej damy w rękach bandy złodziei i rabusiów.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "Jesteś szlachetnym dżentelmenem! Jak masz na imię, monsieur?";
			link.l1 = ""+GetFullName(pchar)+". Kapitan "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Powiedz mi kapitanie, czy naprawdę zabierzesz mnie do mojego ojca w St. John's?";
			link.l1 = "Tak, chociaż on nie przepada za Francuzami. Cóż, przypomnę mu, że są również Anglicy, którzy są łajdakami, w tym angielscy oficerowie! Byłem świadkiem przynajmniej jednego z nich... Richard Fleetwood się zwał.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "Jeśli dotrzemy do Antigui, zrobię wszystko, co w mojej mocy, aby przekonać mego ojca, że wśród Francuzów są prawdziwi rycerze.";
			link.l1 = "Byłbym bardzo wdzięczny... Dobrze, mam nadzieję, że moje anioły stróże śledziły mój szlak po dachach miasta i już wypatrują naszego powrotu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "Nie mogłam uwierzyć, że dotrzymasz obietnicy aż do teraz! Tak wiele okropnych i odrażających rzeczy przytrafiło mi się ostatnio... Dziękuję ci, kapitanie, za przywrócenie mi wiary w ludzi i rycerskość. Powinieneś odwiedzić mojego ojca, kiedy będziesz mógł!\nSzanuje takich ludzi jak ty. I nie ma znaczenia, że jesteś Francuzem. Zrobię wszystko, aby przekonać mojego ojca do zmiany nastawienia do twojego narodu.";
			link.l1 = "Dziękuję, Catherine. Może skorzystam z twojej uprzejmej oferty.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "Mam nadzieję, że tak będzie, kapitanie. Ogromne dzięki raz jeszcze za to, co dla mnie zrobiłeś. Nigdy tego nie zapomnę.";
			link.l1 = "Idź, pośpiesz się do ojca. Będzie zachwycony, widząc cię. Może już wrócił z pola. Cóż, w każdym razie, czas na mnie. Żegnaj!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "Tam jesteś, kapitanie! Martwiliśmy się o ciebie do szaleństwa! Taki bieg po dachach i taki skok z zawrotnej wysokości to było coś do zobaczenia! Na Boga, obawialiśmy się, że nie dasz rady... Witaj z powrotem na pokładzie, kapitanie, szalupa jest gotowa!";
			link.l1 = "Świetnie. Katarzyno, za mną!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Witaj, monsieur. Czy jesteś kapitanem "+GetFullName(pchar)+"?";
			link.l1 = "Owszem, to ja. Co się dzieje?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Uff, ledwo cię dogoniłem... Przychodzę do ciebie w imieniu dżentelmena, którego znasz pod imieniem Henry Thibaut.";
			link.l1 = "Henry? A cóż on chce? Podzielić się swą radością z powodu niespodziewanego spadku, który mu przypadł po śmierci jego zmarłego drogiego wujaszka?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Monsieur Thibaut pilnie prosił, abyś jak najszybciej odwiedził go w jego rezydencji na Tortudze. Ma dla ciebie dobrze płatną pracę. Powiedział mi również, bym wspomniał ci jedno imię: Robert Martene. To powinno cię zainteresować.";
			link.l1 = "Czyżby? A co takiego Henry'emu to zasugerowało?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Również, jeśli to nie przekonało cię, aby już go odwiedzić, poprosił mnie, abym dodał następujące: 'Robert Martene musi umrzeć'.";
			link.l1 = "Dobrze, dobrze... Teraz robi się ciekawie. Dwóch zaprzysiężonych przyjaciół właśnie się pokłóciło... Jak mówisz, spróbuję odwiedzić Henry'ego, gdy będę miał okazję.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Pan Thibaut prosił, abyś nie zwlekał z wizytą. 'Ryba wypłynie z sieci za dziesięć dni' - to były jego dokładne słowa...";
			link.l1 = "On i Robert mają ten sam sposób mówienia. Dobrze, odwiedzę Henry'ego.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Tryb eksploracji: timer nie jest wyłączony. Dotrzymaj terminu!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
