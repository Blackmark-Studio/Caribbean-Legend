// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, o co chodzi?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, kiedy znowu próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracującym nad sprawami kolonii, a ty wciąż próbujesz o coś pytać!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz. Nieodpowiednie miejsce i czas."),"Prawda... Ale później, nie teraz...","Zapytam... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, znalazłem w dżungli ciało bandyty. Został zabity przez Indian. Na jego ciele były kolczyki, wygląda na to, że przywieziono je z Europy. Może należały do jednego z szlachciców w waszym mieście?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Wasza Ekscelencjo, sprawa załatwiona! Jednakże z żalem informuję, że przestępca nie przeżył starcia i tym samym nie będzie poddany egzekucji.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Wasza Ekscelencjo, zadanie wykonane! Więzień czeka na swój los w moim areszcie.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Przybyłem na rozkaz gubernatora generalnego Philippe de Poincy, aby objąć dowództwo nad waszą uzbrojoną fregatą.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Jestem gotów włączyć fregatę do mojej eskadry.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "Przybyłem na Twoje zaproszenie, monsieur...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "To było niefortunne, monsieur";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Wasza Ekscelencjo, weszłpan"+GetSexPhrase("em","am")+" w posiadanie informacji dotyczących nielegalnego handlu, który wkrótce będzie miał miejsce na tych brzegach. Ośmielam się twierdzić, że ta sprawa może okazać się godna pańskiej uwagi.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Wasza Ekscelencjo, przybywam, aby dowiedzieć się o losie tego przemytniczego statku, o którym rozmawialiśmy.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Zobaczmy, co masz... Niesamowite! To po prostu niesamowite, Charles! To są kolczyki mojej żony. Podarowałem je jej, zanim opuściłem Europę i przybyłem do kolonii. Zniknęły kilka miesięcy temu w tajemniczych okolicznościach. Wiedziałem, że zostały skradzione!\nCharles, bardzo się cieszę, że przyszedłeś bezpośrednio do mnie, a nie sprzedałeś rzeczy, którą tak bardzo cenię, kupcom. Odpłacę ci za tę przysługę. Jak słyszałem, zamierzasz kupić statek? Skoro zdecydowałeś się uczestniczyć w żegludze, z pewnością będziesz potrzebował mapy naszego archipelagu. Proszę, weź ją. Jestem pewien, że się przyda!";
			link.l1 = "Dziękuję, Wasza Łaskawość!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "Niestety, Charles, ale musimy sobie radzić z obecną sytuacją. Oto twoja nagroda: pięć tysięcy pesos, po opodatkowaniu.";
			link.l1 = "Jestem zadowolony, że mogę służyć St. Pierre i Tobie osobiście. Choć bitwa była trudna, znalazłem w niej pewną przyjemność.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "To była trudna bitwa, Wasza Ekscelencjo. Mój statek doznał poważnych uszkodzeń. Czy byłoby możliwe zrekompensować mi moje straty?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Brawo, Charles! Nie mam wątpliwości, że zajdziesz daleko w naszych szeregach.";
			link.l1 = "Do zobaczenia, Wasza Ekscelencjo.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Muszę przyznać, że jestem nieco zaskoczony twoją prośbą, Charles... Bardzo dobrze, z mojej strony weź jeszcze dwa tysiące pesos jako gest dobrej woli. Żegnaj.";
			link.l1 = "Dziękuję, Wasza Ekscelencjo.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Doskonale, Charles! Ucieszy cię wiadomość, że twój sukces wspomoże twoich maltańskich przyjaciół w delikatnej operacji... Oto twoja nagroda: osiem tysięcy pesos po opodatkowaniu.";
			link.l1 = "Cieszę się, że mogę służyć St. Pierre, Zakonowi i Wam osobiście. Choć walka była wymagająca, odnalazłem w niej pewną satysfakcję.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "To była ciężka bitwa, Wasza Ekscelencjo. Mój statek doznał znacznych uszkodzeń. Czy mógłbym prosić o odszkodowanie za moje straty?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Brawo, Charles! Jestem pewien, że zajdziesz daleko.";
			link.l1 = "Do zobaczenia, Wasza Ekscelencjo";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Przypuszczam, że na to zasłużyłeś. Zatrzymaj dodatkowe dwa tysiące ode mnie osobiście jako gest dobrej woli. Dziękuję, mój przyjacielu.";
			link.l1 = "Dziękuję, Wasza Ekscelencjo.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Okręt jest gotowy, ale nie masz na niego wolnego miejsca w swojej eskadrze. Kapitanie, zmniejsz swoją eskadrę i wróć, wtedy natychmiast przekażę ci fregatę.";
				link.l1 = "Dobrze.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Tak, oczywiście, statek jest gotowy do wypłynięcia. Kapitan jest poinformowany i będzie przestrzegał wszystkich twoich rozkazów.";
				link.l1 = "W takim razie wyruszamy. Żegnaj, Wasza Łaskawość.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Doskonałe. Przygotuj się na powitanie nowego statku. Jego kapitan jest poinformowany i będzie wykonywać wszystkie twoje rozkazy.";
			link.l1 = "W takim razie wyruszamy. Żegnaj, Wasza Łaskawość.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Kapitanie Charles de Maure, wreszcie! Czekałem na ciebie z niecierpliwością! Proszę, wejdź, dołącz do mnie.";
			link.l1 = "Dzień dobry również Wasza Ekscelencjo. Zawsze jest jakiś powód takiej Waszej uprzejmości. Co to tym razem? Piraci, Hiszpanie, czerwonoskórzy kanibale?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Nie bądź taki ironiczny, Kapitanie. To nie moja wina, że zawsze wpadamy w kłopoty, ty i ja. Ale proszę, nie martw się, tym razem nie będzie strzelaniny... prawdopodobnie.";
			link.l1 = "Intrygujesz mnie, mów dalej. Jak mogę pomóc?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Słyszałżeś kiedyś o wspaniałym przybytku Madame Botot? Podczas oblężenia nasz... dom publiczny spłonął doszczętnie. Pewnego dnia pewna dama zgłosiła się na ochotnika, by go odbudować.";
			link.l1 = "Pożar w burdelu i to beze mnie? A tak przy okazji, tego dnia też dostałem kulę od Hiszpanów.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Do diabła, Charles, co się z tobą dziś dzieje? Twój dowcip jest niestosowny! Chociaż to nie jest sprawa państwowa, to wciąż jest to ważna sprawa, dla mnie, osobiście! Potrzebuję twojej pomocy! Na miłość boską, weź się w garść i wysłuchaj mnie!";
			link.l1 = "Proszę wybaczyć, Wasza Ekscelencjo. Czuję ogromną ulgę, ot co. Szczerze mówiąc, zmęczyło mnie to ciągłe wojowanie i bijatyki. Spodziewałem się, że wciągniecie mnie w kolejny krąg przemocy. Proszę kontynuować. Nigdy nie słyszałem o tej Madame Botot.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Tak więc, ta szlachetna dama wyniosła przybytek na zupełnie nowy poziom. Teraz jest to miejsce wysokiego i szlachetnego towarzystwa, a nie szczurza nora, jak dawniej. Miejsce wyrafinowanych występków, drogiego wina i nieograniczonego hazardu. Sam wszystko zobaczysz!";
			link.l1 = "Wasza Ekscelencjo, nie jestem pruderyjny, a wasz opis był bardzo barwny, ale czemu mi to mówicie?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Bo jesteś na liście, dlaczego inaczej?! Widzisz, czuję się winny wobec markizy i obiecałem przedstawić cię jej na jednej z jej przyjęć jutro. Juliana nie robi tego często, więc bądź tak uprzejmy i dołącz do nas. Żadnych bójek, strzelanin i pościgów tym razem, obiecuję. Wszystko będzie uprzejme i godne: wino, piękne kobiety, karty i inne szlachetne rozrywki.";
			link.l1 = "Karty i dziwki. To było dawno temu, w innym życiu. Nadal cię nie rozumiem jednak. Dlaczego ja?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Czy jesteś głuchy? Juliana Botot, ona... kolekcjonuje jasne i sławne twarze. One sprawiają, że jej przyjęcia są wyjątkowe i świeże. Zrobiłeś sobie niezłą reputację, markiza długo czekała, aby mieć cię jako gościa. Mój błąd dał jej okazję i nie skorzystam z niej, jeśli odmówi mnie ponownie przyjąć. To wszystko, co dostanę, jeśli cię do niej nie dostarczę!";
			link.l1 = "Wasza Ekscelencjo, jesteście przystojnym wdowcem i gubernatorem... Dlaczego w ogóle przejmujecie się opinią jakiejś kurtyzany? To oni powinni szukać waszej łaski, a nie odwrotnie.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "Markiza Botot jest pod ochroną hrabiego Henryka de Levi-Vantadur - który, z łaski Jego Królewskiej Mości, jest głową stanów Nowej Francji w Ameryce Północnej. Uwierz mi, Charles, nikt tutaj nie chce z nim zadrzeć.";
			link.l1 = "Już prawie mnie miałeś - myślałem, że tu chodzi tylko o pożądanie i miłość. Teraz widzę, że to była polityka od samego początku. Błahe, ale spodziewane. Bardzo dobrze, pomogę ci. Miło będzie powrócić do dni mojej młodości choćby na jedną noc.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Kapitanie, jesteś niewątpliwie doświadczonym człowiekiem, jednak nie próbuj udawać starca. To nie tylko kwestia polityki. Cenię obecność Juliany i jestem wdzięczny za twoją pomoc. To dla mnie osobiście ważne, naprawdę. Przyjdź do posiadłości Markizy Botot po zmierzchu, jutro. Obiecuję ci, że polityka nie zepsuje nocy.";
			link.l1 = "Wino, karty, kobiety. Jak za dawnych, dobrych czasów. Żegnaj, Wasza Ekscelencjo!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, co się stało, wyglądasz jak diabli!";
			link.l1 = "Angerran, przeklęty, Chievous, Ekscelencjo. Ukradł moją fregatę zeszłej nocy. Zabił moją załogę i odpłynął w mgle.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "To nieprzyjemny obrót wydarzeń, rozumiem, ale uwierz mi - taki wynik jest całkiem zadowalający. Nie potrzebujesz pilnie statków i ludzi, podczas gdy de Levi Vantadur zapłaci znaczną sumę, aby ukryć prawdę o pewnym niedawnym pojedynku. Albo zapamięta naszą rolę w ukrywaniu tego za darmo, co także jest warte sporo. De Chievous dwukrotnie postąpił nieuczciwie, ale teraz jest daleko, podczas gdy my wciąż mamy przeciwko niemu przyzwoite karty.";
			link.l1 = "Trzykrotnie, Wasza Ekscelencjo. Angerran przyznał się do oszustwa podczas naszej gry w karty. Ale nie spłaci mnie pieniędzmi, jeśli o to chodzi. Przekroczył granicę. Na tym statku była dziś rano pewna osoba... jest mi bardzo droga! Nie pozwolę, by drań jej zaszkodził! Słyszysz to, Jacques, nie pozwolę!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Myślę, że wiem, o kim mówisz - przypominam sobie, że widziałem cię z jakąś... dziewczyną, ubraną jak mężczyzna i uzbrojoną po zęby jak pirat. Charles, nie bądź idiotą! Miałeś szczęście, uniknąłeś wielkich kłopotów i co, próbujesz się w nie znowu wpakować? Zostaw to. De Chievous jest w ucieczce - dzięki Bogu! A co do twojej 'dziewczyny w broni' - posłuchaj rady przyjaciela - idź do Julianny i zapomnij o tym wszystkim.";
			link.l1 = "Nie ma mowy, Wasza Ekscelencjo. Niektóre rzeczy są po prostu poza waszym zrozumieniem, dobrze? Teraz powiedz mi wszystko, co wiesz o tym draniu. Dokąd mógł się udać z Saint Pierre? I nie próbuj mnie zniechęcać ponownie - miałem na pieńku z Holenderską Kompanią, z baronami piratów, gubernatorami generalnymi, nawet z Świętą Inkwizycją! Nie jestem łatwym człowiekiem do przestraszenia. Odzyskam ją za wszelką cenę!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, czy kiedykolwiek zastanawiałeś się, kto mianuje gubernatorów generalnych? To jest zupełnie inny świat! Ledwie go dotknąłeś, jest poza twoim zrozumieniem, jesteś jak dziecko w magazynie prochu. A ty prosisz mnie, bym podał ci zapaloną świecę. Co do gubernatorów generalnych: sam de Poincy nigdy nie przeciwstawia się hrabiemu ani w kwestiach finansowych, ani w kwestiach politycznych. Wicekról, termin tak popularny wśród pospólstwa, pasowałby Henriemu de Levi Vantadur jak ulał.";
			link.l1 = "A oto jestem, zamierzając obedrzeć ze skóry jego jedynego męskiego potomka, wiem, na co się tutaj narażam. Powiedz mi teraz tylko: czy jest coś użytecznego, co wiesz, co mogłoby mi pomóc?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "W innym dniu uznałbym ten ruch w stronę twojego pistoletu za koniec naszej przyjaźni, Charles. Ale rozumiem twój obecny stan umysłu. Dlatego jestem gotów o tym zapomnieć. Nie wiem nic użytecznego dla ciebie, fregata odpłynęła na zachód wcześnie rano. Powinieneś odwiedzić markizę... Czekaj, nie tak! Julianna wie dużo o twoim wrogu i była osobiście... zaznajomiona z jego ojcem przez jakiś czas. Zapytaj ją. W przeciwieństwie do mnie, ona cię nie powstrzyma.";
			link.l1 = "Tak jest w planie. Do zobaczenia, Ekscelencjo. Dziękuję za poświęcony czas.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Przemyt, powiadasz? Hmm... niezwykle intrygujące. Proszę, oświeć mnie szczegółami swojego odkrycia.";
			link.l1 = "Trzy dni temu statek załadowany kontrabandą miał zrzucić kotwicę w Zatoce Le Marin. Statek nie dotarł na spotkanie, ale mam solidne powody, by wierzyć, że wkrótce zawinie do portu. Być może pańscy ludzie mogliby przygotować odpowiednie powitanie dla tych opryszków, gdy przybędą, Wasza Ekscelencjo.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;
		
		case "VPVL_Magor_2":
			dialog.text = "Bezimiennny statek przewożący nienazwany ładunek... I pan"+GetSexPhrase("","i")+" zakłada, że powinienem wysłać siły Jego Królewskiej Mości na podstawie tak mglistych informacji?";
			link.l1 = "Wasza Ekscelencjo, przyznaję, że szczegóły są skąpe. Ale proszę pozwolić mi opowiedzieć, w jaki sposób te informacje weszły w moje posiadanie. (opowiada)";
			link.l1.go = "VPVL_Magor_3";
		break;
		
		case "VPVL_Magor_3":
			dialog.text = "Dobrze, sprawdzimy pan"+GetSexPhrase("a","i")+" informacje. Jeśli statek z kontrabandą rzeczywiście zrzuci kotwicę u wybrzeży Le Marin, pan"+GetSexPhrase("","i")+", Kapitanie, zostanie sowicie nagrodzon"+GetSexPhrase("y","a")+" za swoją służbę dla Korony. Proszę wrócić do mnie za trzy dni. Do tego czasu mgła niepewności powinna się rozwiać.";
			link.l1 = "Świetnie. Zatem do zobaczenia za trzy dni.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;
		
		case "VPVL_Magor_4":
			dialog.text = "Ach, Kapitanie! Przyjemność znów pan"+GetSexPhrase("a","ią")+" gościć. pan"+GetSexPhrase("a","i")+" informacje okazały się niezwykle cenne. Moi ludzie przechwycili statek dokładnie tam, gdzie pan"+GetSexPhrase("","i")+" wskazał"+GetSexPhrase("","a")+". Oto—sto pięćdziesiąt hiszpańskich dublonów, świeżo wybitych i ciężkich w sakiewce. Proszę je przyjąć wraz z moją wdzięcznością.";
			link.l1 = "Jestem bardzo wdzięczny/wdzięczna za pańskie względy, Wasza Ekscelencjo. To dobry los, że mój okruch informacji posłużył interesom Korony. Gdyby nadarzyła się ponownie okazja, proszę wiedzieć, że moje zbrojne ramię i bystrze oko pozostają do pańskiej dyspozycji.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;
		
		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;
		
		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
