// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
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
			dialog.text = "To oczywisty błąd. Powiedz o tym deweloperom.";
			link.l1 = "O, zrobię to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", kapitanie. (salutuje) Pozwól, że się przedstawię - Porucznik "+GetFullName(npchar)+", Antigua Regiment Piechoty Morskiej, stacjonujący w St. Johns. Mam prośbę.";
			link.l1 = "Witaj, poruczniku Gretton. Nazywam się "+GetFullName(pchar)+". Jaka przysługa?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Pozwól mi krótko wyjaśnić sytuację. Czterech moich ludzi i ja płynęliśmy ze St. Johns do Sint-Maarten, gdy burza uderzyła w nasz statek. Zła pogoda nie trwała długo, ale wystarczyło, by nasza stara kobyła zaczęła przeciekać. Musieliśmy zmienić kurs i zatrzymać się tutaj na naprawy. To zajmuje czas, którego nie mamy\nŚpieszymy się do Sint-Maarten, a konkretnie na plażę Grand Case. Pomóż mi kapitanie, a uczynię to opłacalnym dla ciebie. Dwa dni podróży za hojną zapłatę!";
			link.l1 = "To musi być naprawdę hojna zapłata, poruczniku, jeśli chcesz, abym potajemnie wprowadził angielskich marynarzy na holenderską wyspę.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", to nie powinno pana niepokoić. Nic panu nie grozi. Proszę nas tylko wysadzić w zatoce i tyle. No i co, umowa stoi?";
			link.l1 = "Dobrze, wchodzę w to. To nie jest zbyt daleko stąd. Posłuchajmy o tej zapłacie.";
			link.l1.go = "seafox_3";
			link.l2 = "Przykro mi, ale mam pilne sprawy w innym kierunku i wolałbym nie denerwować Holendrów.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Jak mówisz, kapitanie. Będę dalej szukać. Żegnaj i niech ci Bóg sprzyja!";
			link.l1 = "Żegnaj, poruczniku.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("Otrzymałeś sakiewkę dublonów");
			dialog.text = "Dziesięć tysięcy sztuk srebra. Oto zaliczka.";
			link.l1 = "Dobrze. Zabierz swoich ludzi na pokład, nie traćmy czasu.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "FMQN_SailMaarten", 10.0);
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Dziękuję za spokojną podróż, kapitanie! Bardzo mi przykro, ale nie mogę ci zapłacić w tej chwili... w tej okolicy miała być nasza szalupa, ale jej tu nie ma. Jak możesz wyraźnie zobaczyć. Muszę prosić cię o pomoc jeszcze raz. Czy mógłbyś poczekać w tej zatoce przez dwa lub trzy dni? Musimy iść i rozejrzeć się. Kiedy wrócimy, zabierz nas do Antigui. Pułkownik Fox hojnie cię wynagrodzi.";
			link.l1 = "Hm... To nie do końca to, na co się umawialiśmy...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Proszę, nie złość się kapitanie. Wiem, jak się musisz czuć, ale niestety: nie mam w ogóle pieniędzy. Mogę obiecać ci, że otrzymasz rekompensatę zarówno za oba rejsy, jak i za czekanie na nas tutaj. A także podziękowania samego pułkownika Foxa!";
			link.l1 = "Nie mogę cię tak po prostu zostawić... Dobrze, poruczniku Gretton. Poczekam trzy dni, ale nie dłużej.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Dziękuję, "+GetAddress_Form(NPChar)+"! Zmierzamy w głąb lądu. Przysięgam, że wrócimy za 72 godziny, ani minuty dłużej.";
			link.l1 = "Pomóż Bóg, poruczniku. Nie daj się złapać.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Coż za przypadkowe spotkanie! Myślałem, że będziesz na nas czekał na plaży Grand Case, kapitanie "+pchar.lastname+"!";
			link.l1 = "Witaj poruczniku, zaskoczenie jest obopólne. Nie spodziewałem się zobaczyć cię ubranego jak holenderski żołnierz.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "To nasze przebranie... Dlaczego tu jesteś, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "To niebezpieczne przebranie, żołnierzu. Szpiedzy mogą być natychmiast straceni bez procesu. A skoro mowa o egzekucji, jeśli chcesz uniknąć swojej, lepiej posłuchaj.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Masz moje pełne zainteresowanie.";
			link.l1 = "Popłynąłem do Philipsburga i rozmawiałem z miejscowymi po twoim zejściu na ląd. Holendrzy cię śledzą. Wiedzą o twojej misji ratowania tych pojmanych angielskich oficerów wysokiej rangi.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Do diabła i niech to szlag! Jak do cholery się o tym dowiedzieli?";
			link.l1 = "Jeden z pojmanych angielskich oficerów. W zamian za wolność powiedział Holendrom wszystko, co wiedział o operacji ratunkowej. Cały Philipsburg jest gotowy na to, że ty i twoi ludzie spróbujecie wejść do miasta. Co gorsza, holenderska korweta patroluje morze wokół Sint-Maartin. To pułapka, poruczniku.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+". Ten niehonorowy łotr! Dowiem się, kim jest ten zdrajca, i ujawnię go przed Parlamentem!";
			link.l1 = "To będzie musiało poczekać, panie Gretton. Wróć na plażę Grand Case tej nocy i wracaj na mój statek, zanim cię złapią.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "I porzucić angielskich dżentelmenów w holenderskim więzieniu? Prędzej bym zginął, panie. Nie zawiodę pułkownika Foxa.";
			link.l1 = "Czy myślisz, że Holendrzy pozwolą ci wybrać szubienicę albo pluton egzekucyjny, gdy cię pojmą?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Nie sądź, że pozwolą ci tak po prostu stąd wypłynąć, kapitanie de Maure. Oboje jesteśmy w tym po uszy.";
			link.l1 = "Cholera, pewnie masz rację. Ta korweta runie na nas w chwili, gdy podniesiemy kotwicę...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "Holendrzy mogą wiedzieć, że nadchodzimy, ale nie wiedzą *jak* nadchodzimy. Już zajęliśmy się przebieranką - spójrz na ten mundur. Piękny, prawda? Gdyby nasz plan nie został zdradzony, po prostu poszlibyśmy do lokalnego więzienia, zaskoczyli ich i zabili wszystkich w środku. Ale z pewnością tam czają się w zasadzce. Więc improwizujemy\nKapitanie, idź do kościoła w Philipsburgu i znajdź tam kaznodzieję o imieniu Filippe Jacobsen. Powinien tam być od szóstej do dziesiątej rano. Filippe jest jednym z naszych ludzi wewnątrz\nPowiedz mu to hasło: 'Jak dawno temu uwięzieni marynarze wyznali winy?'. Następnie opowiedz mu o sytuacji i zażądaj jego pomocy w imieniu pułkownika Foxa. Potem przekaż mi jego odpowiedź. Proste i bez ryzyka dla ciebie.";
			link.l1 = "Brzmi cholernie ryzykownie pytać o spowiedź w holenderskim kościele kalwińskim, poruczniku. Pastor spróbuje mnie powiesić za to, że jestem papistą. Dobrze, opowiedz mi o tych mundurach... czy zabrałeś je z holenderskiego patrolu?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Tak jest, panie.";
			link.l1 = "A gdzie oni teraz są?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Trzymani jako zakładnicy w zaroślach niedaleko tej jaskini.";
			link.l1 = "Zrozumiano. Trzymaj ich w bezpiecznym miejscu, ja ruszam do miasta. Czekaj tu na mnie i nie wychylaj się - Holendrzy przeczesują dżunglę i morze, szukając ciebie.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Będziemy cisi jak myszy kościelne, kapitanie. Proszę, pośpiesz się!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Jesteś z powrotem? Kapitanie, co ty tutaj robisz? Idź do miasta, przyciągasz uwagę do naszej kryjówki!";
			link.l1 = "Wróciłem z miasta. W jakie gry wy, Anglicy, gracie?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Proszę o wybaczenie?";
			link.l1 = "Poszedłem do kościoła. Duży budynek, ładny i surowy, dokładnie taki, jaki lubią ci holenderscy ikonoklaści. Zgadnij, poruczniku? Nie ma tam kaznodziei o imieniu Filippe Jacobsen.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "To niemożliwe, odwiedza to miejsce każdego ranka-";
			link.l1 = "Zamknij się i słuchaj mnie! Jeśli ten twój Jacobsen w ogóle istnieje, to nie chodzi do kościoła! Nigdy go tam nie widziano! Ani rano, ani wieczorem! Do cholery jasnej! Dlaczego w ogóle zgodziłem się na tę cholerną robotę?! Prowadzony przez głupiego, psiego syna, żółtodzioba, który nie ma pojęcia o niczym, porucznika-";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Panie, żądam satysfakcji za tę zniewagę. Gdy tylko stąd wyjdziemy, będziemy pojedynkować się według zwyczajów-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Zamknijcie się wszyscy do cholery!!! ... Coś właśnie usłyszałem.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "Na Boga, ktoś jest na zewnątrz! Ty! Sprowadziłeś tu z powrotem tych Holendrów, łotrze!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Miło cię widzieć, panie, jakie nowiny?";
			link.l1 = "Spotkałem twojego człowieka. Dziś wieczorem dostarczy on do garnizonu więzienia trochę 'zaprawionego' wina. Dostał od cyganki miksturę, która nie zabija, ale spawi że będą spać jak zabici. Musisz się tam dostać tej nocy i wyciągnąć swoich pojmanych dżentelmenów. A tak przy okazji, ta dostawa wina kosztowała mnie dwadzieścia pięć dublonów. Upewnij się, że wspomnisz o tym w raporcie.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Nie martw się o pieniądze. Kapitanie, proszę cię, dołącz do nas w tej operacji i pokaż nam drogę do więzienia. Byłeś już w Philipsburgu, więc znasz miasto lepiej niż my. Nie musisz wchodzić z nami do więzienia, sami zajmiemy się ucieczką. Po prostu doprowadź nas do drzwi.";
			link.l1 = "Do diabła, panie Gretton, ta robota staje się coraz lepsza. Lepiej, żeby zapłata wzrastała proporcjonalnie.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Z całą pewnością, kapitanie. Nie pożałujesz, że nam pomogłeś. Czy twój statek jest na plaży Grand Case?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Tak.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "Nie.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Dobrze. W takim razie przygotuj się i spotkajmy się przy bramach miasta o jedenastej wieczorem.";
			link.l1 = "Widzimy się tam.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Upewnij się, że go tam przeniesiesz, bo musimy wyprowadzić naszych ludzi przez dżunglę. Wypłynięcie z portu lub Zatoki Simpsona jest niemożliwe z powodu fortu. Przygotuj wszystko i spotkaj się z nami przy bramach miasta o jedenastej wieczorem.";
			link.l1 = "Do zobaczenia tam.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Gotowy, kapitanie?";
			link.l1 = "Tak.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "W takim razie ruszajmy.";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Ciii... Kapitanie! Skończone, wynośmy się stąd do diabła!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Nie wiem, jak nam się to udało, ale daliśmy radę! Nic z tego nie byłoby możliwe bez twojej pomocy, "+GetAddress_Form(NPChar)+". Teraz czas na stosunkowo łatwą część - musimy opuścić Sint-Maartin żywi i w jednym kawałku. Ruszajmy na plażę Grand Case!";
			link.l1 = "Ruszajmy!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Kapitanie "+pchar.lastname+"... "+GetAddress_Form(NPChar)+", dziękuję za pomoc! Błagam, nie opuszczaj natychmiast portu, lecz zostań tu jeszcze jeden dzień, podczas gdy ja zdam raport pułkownikowi Foxowi. Odwiedź go jutro, jego biuro jest w pałacu gubernatora.";
			link.l1 = "Bardzo dobrze, poruczniku Gretton. Proszę, aby to było warte mojej fatygi. Naprawa mojej reputacji u Holendrów zajmie dużo czasu z powodu waszej eskapady.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Dziękuję za twoją pomoc, kapitanie! Zachowałeś się "+GetSexPhrase("jak prawdziwy bohater","jak bardzo odważna dziewczyna")+", "+GetAddress_Form(NPChar)+"! To tragedia, że porucznik Gretton nie przeżył. Zginął jako prawdziwy dżentelmen i syn Anglii. Poprosiłbym o pozostanie tu jeszcze jeden dzień, podczas gdy złożę raport pułkownikowi Foxowi. Odwiedź go jutro, jego biuro znajduje się w pałacu gubernatora.";
			link.l1 = "Bardzo dobrze. Proszę, wynagrodź mi to. Naprawa mojej reputacji u Holendrów z powodu twojej eskapady zajmie dużo czasu.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Nie martw się, "+GetAddress_Form(NPChar)+". Dam ci najwyższą możliwą ocenę w moim raporcie. (salutuje) To była przyjemność, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Kapitan "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Tak, co mogę dla ciebie zrobić?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "Urząd portowy poinformował nas o niedawnym przybyciu twojego statku. Jego Ekscelencja Mynheer Martin Thomas, gubernator Philipsburga, pragnie cię zobaczyć.";
			link.l1 = "Po co to wszystko? Czy jestem aresztowany?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "O nie, nie, "+GetAddress_Form(NPChar)+" kapitanie, nie jesteś aresztowany. Gubernator nakazał zaprosić każdego nowo przybyłego kapitana do swojego pałacu na kawę i przedstawienie się. Chodź za mną!";
			link.l1 = "Brzmi jak oferta, której nie mogę odrzucić. Prowadź.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", pokaż nam, gdzie widziałeś tych angielskich żołnierzy.";
			link.l1 = "Ukrywają się w jaskini w dżungli, jak pospolici bandyci.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Prowadź, idziemy za tobą!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Poczekaj kapitanie! Wspomniałeś, że spotkałeś szpiegów tam - blisko wejścia do jaskini?";
			link.l1 = "Tak. Krótko widziałem, jak wchodzili do środka po tym, jak ze mną rozmawiali.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Najprawdopodobniej wciąż tam są. Jeśli wszyscy naraz tam wpadniemy, wycofają się do jaskini. To będzie koszmar wyciągać ich stamtąd... Zróbmy to mądrze. Kapitanie, idź tam sam i ich rozprosz. Ja i moi ludzie przejdziemy do tej suchej studni za rogiem. Ona prowadzi prosto do jaskini. Draństwo nie zobaczy, jak nadchodzimy od tyłu\nWejdź do środka, a jeśli szpiedzy wciąż tam są, rozmawiaj z nimi, zadawaj głupie pytania i zajmij ich czymś. Kiedy już zdobędziesz ich absolutną uwagę - przeklnij tak plugawo, jak tylko potrafisz. Jesteś żeglarzem, więc powinno ci to przyjść naturalnie. To będzie nasz sygnał. Dwóch moich ludzi będzie pilnować głównego wejścia, by uniemożliwić im ucieczkę tą drogą. Złapiemy ich.";
			link.l1 = "Twój plan brzmi niezwykle niebezpiecznie dla mojego zdrowia. Jak to widzę, po prostu spróbują mnie najpierw zabić.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Nie martw się, kapitanie. Twoim celem jest krzyczeć tak głośno, jak tylko możesz, gdy zobaczysz wrogą grupę napadającą. Jeśli cię zaatakują - wtedy uciekaj i krzycz dalej. Moi ludzie są dobrze wyszkoleni, więc nie martw się, zlikwidują tych szpiegów, zanim zostaniesz zraniony.";
			link.l1 = "Lepiej, żeby tak było. Wchodzę tam.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Twarde skurczybyki to byli... Dobrze zrobione, kapitanie, angielskie psy zostały wyeliminowane. Sabotażyści zostali zlikwidowani, komendant i gubernator będą zadowoleni.";
			link.l1 = "Nie spieszyłeś się, mynheer...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Obwiniaj linę, miała na końcu wiadro, które robiło okropny hałas. Musieliśmy być ostrożni.";
			link.l1 = "Tak... lina. Cokolwiek. Jeden z twoich zaginionych patroli jest tam związany w krzakach. Powinni jeszcze być żywi.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Zajmę się nimi. Powinieneś udać się do miasta i trochę odpocząć. Jutro odwiedź naszego gubernatora, do tego czasu będzie miał mój raport z pochwałą dla ciebie.";
			link.l1 = "Zrobię to. Szczęść Boże, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "Co mogę dla ciebie zrobić, synu?";
			link.l1 = "Witaj, pastorze, tak z ciekawości, jak dawno temu uwięzieni marynarze wyznali swe winy?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Wczoraj wieczorem, mój synu... (szeptem) Zakładam, że wiesz, iż plan został zdradzony?";
			link.l1 = "Nie stałbym tutaj w przeciwnym razie. Porucznik Casper Gratton i jego ludzie są obecnie w dżungli. Wszyscy są ubrani jak holenderscy żołnierze, ale potrzebujemy dodatkowej pomocy, ponieważ strażnicy więzienni na nich czekają.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(głośno) Modliłem się każdego dnia, aby ocalić jego anglikańską duszę od potępienia! (szeptem) Mam plan, ale potrzebuję dwóch tuzinów złotych dublonów, aby zdobyć wszystko, czego potrzebuję.";
			link.l1 = "Drogi plan. Na co te pieniądze?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Bycie strażnikiem więziennym to nudna służba. Aby podnieść morale, oficer dowodzący zamawia co wieczór wino do kolacji. Wino pochodzi z magazynu, do którego mam dostęp. W mieście jest cygańska kobieta, która jest mi winna przysługę, ona zrobi nam miksturę nasenną. Wszystko, czego potrzebuję, to kupić kilka butelek dobrego wina, dodać miksturę i zamienić butelki w magazynie. Dlatego potrzebuję złota.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Mam dublony. Weź je.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Pozwól, że wrócę na swój statek i przyniosę ci trochę.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ach, mój synu, czy masz 'darowiznę', o której rozmawialiśmy?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Tak, tutaj.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Wkrótce ją zdobędę...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Znakomicie. Przyjdź do mnie o tej samej porze jutro - powiem ci wyniki.";
			link.l1 = "Bardzo dobrze...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Witaj, mój synu.";
			link.l1 = "Witaj, pastorze. Jakieś nowiny?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Tak. Zrobione. Wino zostało 'przyprawione' i strażnicy dostaną dziś wieczorem wyjątkowy przysmak. Mają kolację o dziewiątej wieczorem, wszyscy będą spać do północy. To jest twoje jedyne okno, aby wykonać zadanie, bez drugiej szansy. Bądź ostrożny, nie możesz całkowicie polegać na swoim holenderskim przebraniu.";
			link.l1 = "Zrozumiano. Nie traćmy czasu. Żegnaj.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
