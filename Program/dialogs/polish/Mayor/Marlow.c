// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat("Masz do mnie jakiś interes? Jeśli nie, to wynoś się stąd!","Chyba wyraziłem się jasno.","Chociaż wyraziłem się jasno, dalej mnie wkurzasz!","Racja, zaczynam mieć dość tej nieuprzejmości.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Już odchodzę.","Oczywiście, Pastorze.","Przepraszam, Pastorze.","Ojeju...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Zwariowałeś? Chciałeś się pobawić w rzeźnika? Wszyscy piraci są na ciebie wściekli, chłopcze, lepiej opuść to miejsce.","Wydaje się, że oszalałeś, chłopcze. Chciałeś trochę rozruszać ręce? Bez urazy, ale nie masz tu nic do roboty. Zmykaj!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomóż mi rozwiązać ten problem...");
				link.l1.go = "pirate_town";
				break;
			}
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "Próbuję znaleźć Rekina Dodsona. Mówią, że jesteś ostatnim, kto go widział. Czy możesz mi w tym pomóc?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Dlaczego jesteś taki niegrzeczny? A może nie interesuje cię zdobycie wymarzonej książki ode mnie?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Chcę porozmawiać o twoim więźniu.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Witaj, Pastorze. Chcę porozmawiać o twojej misji.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Chcę porozmawiać o twoim więźniu.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson? Nie wiem, jak moja opowieść miałaby ci pomóc, bo Rekin zaginął na kilka ostatnich miesięcy i nikt go nie widział. Choć to nie jest zaskoczenie, zabił Blaze'a Sharpa i zdyskredytował swoje własne imię tym głupim czynem. Uczynił kilku potężnych korsarzy swoimi wrogami.";
			link.l1 = "Mam wszelkie powody sądzić, że Rekin jest niewinny śmierci Sharpa. Nie mogę tego udowodnić, może sam Rekin to potrafi. Czy zamierzasz mi coś o nim powiedzieć?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Kilka miesięcy temu Steven przyszedł do mnie i zaproponował bardzo dziwny układ: zostawił swoją fregatę 'Fortune' w zastaw na miesiąc w zamian za bryg w pełni załadowany zaopatrzeniem. Potem albo zwraca mi bryg i pieniądze za zaopatrzenie, albo zatrzymuję jego fregatę. Miesiąc minął - ani śladu ani Rekina, ani mojego brygu, ani pieniędzy.\nPoza tym słyszałem plotki, że Blaze został zamordowany, a Rekin był podejrzanym. Co miałem myśleć? Oczywiście! Pomyślałem, że Steven uciekł od najgorszego. Sprzedałem jego fregatę jakiemuś Anglikowi o imieniu William Patterson, był bardzo zadowolony i zapłacił kupę dublonów za statek.\nZatem całkowicie zrekompensowałem swoje wydatki i nie żywię do niego urazy. Nie obchodzi mnie śmierć Sharpa, mam swoje własne problemy, o które muszę się martwić.";
			link.l1 = "Czy nie sądzisz, że gdyby chciał uciec, nie potrzebowałby twojej brygantyny? Miał własny statek, sto razy lepszy niż jakakolwiek brygantyna. Wygląda na to, że Rekin miał plan, ale coś poszło nie tak i nie wrócił na czas.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Jak już ci powiedziałem, nie obchodzi mnie problemy Dodsona. Wykonałem swoją część umowy. Co do statku, lepiej zapytaj go, po co mu ten cholerny bryg. Nie zmuszałem go, żeby go wziął.";
			link.l1 = "Zgoda, nie rozmawiajmy już o tym. Masz rację, oczywiście. Powiedz mi, czy wiesz, dokąd Steven zmierzał na twoim brygu?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Kto to wie na pewno. Ale mam pewne domysły. Odpłynął na północny zachód w kierunku Main. Więc to albo Zatoka Niebezpieczeństw, znana z wrogich Indian, albo Nowa Hiszpania, znana z Papistów i Inkwizycji.\nWątpię, aby popłynął do któregokolwiek z tych miejsc. Ale mówią, że istnieje dziwne miejsce zwane 'Miasto Opuszczonych Statków', znajdujące się na północny zachód od Kuby. Wielu ludzi uważa to za mit, ale nie ja. Nie dlatego, że jestem takim romantykiem, ale dlatego, że są prawdziwi ludzie, którzy tam płyną na swoich szalupach. Przynajmniej kiedyś tak robili.";
			link.l1 = "A kim oni są?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Piraci z Kuby. Ładowali swoje barki tuszami byków i żeglowali na północny zachód. Zawsze wracali nieco później z kieszeniami pełnymi pieniędzy lub z rzadkimi i cennymi towarami.";
			link.l1 = "Intrygujące! Gdzie mogę znaleźć tych bukanierów?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = " Dlaczego mnie o to pytasz? Przeszukaj lasy Kuby. Nawet jeśli ich znajdziesz, nic ci nie powiedzą, dlaczego mieliby ujawniać źródło swojego dostatniego życia? Więc nie trać czasu, nikt nie widział, żeby to znowu robili od dłuższego czasu.\nSłyszałem też o notatkach napisanych przez hiszpańskiego żeglarza Alvarado, który sam odwiedził wyspę. Jestem więc ciekawy, może Steven jednak tam popłynął.";
			link.l1 = "Nieznana wyspa, której nie ma na mapach... Cóż. To nie jest obiecująca informacja.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Powiedziałem ci na początku, że moja opowieść ci nie pomoże. A po co ci ten Dodson?";
			link.l1 = "Ja i Diabeł Lasu chcemy go wybrać na przywódcę Bractwa Wybrzeża. Jak już ci mówiłem, są poważne powody, by sądzić, że Blaze został zamordowany przez kogoś innego.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Heh! Zakładam, że Jan za nim stoi? Cóż, znasz prawo - Dodson będzie musiał uzyskać głos od każdego barona.";
			link.l1 = "Znam prawo. Moje drugie pytanie zatem. Czy zagłosujesz na Dodsona w wyborach?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Cóż, najpierw powinien wrócić. Właściwie, nie obchodzi mnie, kto będzie prowadził Bractwo dopóki robi to dobrze i nie przeszkadza mi. Jak już mówiłem, mam własne problemy. Wiesz, ile wiedźm i czarowników jest na naszej wyspie? Nie? Powiem ci: legion! Poza tym, w Santiago i Hawanie jest także mnóstwo papistów.\nMówiąc o czarownikach. Jest taka książka zatytułowana 'Młot na czarownice'. Bardzo chciałbym ją zdobyć, ale tylko po angielsku, nie potrzebuję tłumaczeń na łacinę, niemiecki ani hiszpański, nie znam tych języków. Przynieś mi książkę, a zagłosuję na Dodsona.\nBądź świadom, że Jackman obiecał mi również ją znaleźć, więc jeśli uda mu się pierwszy... wtedy nie obwiniaj mnie.";
			link.l1 = "Dobrze, rozważę to. Dzięki za poświęcony czas. Do zobaczenia.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "Księga? Rozumiem, że mówisz o 'Młocie na czarownice'?";
			link.l1 = "Oczywiście. Udało mi się to dla ciebie znaleźć. Jest to po angielsku, jak prosiłeś.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ha, przepraszam za tak szorstkie powitanie, kamracie. To się więcej nie powtórzy... Pozwól, że zobaczę ten cud!";
			link.l1 = "Jasne, rzucaj okiem.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "Wreszcie! Drżyjcie teraz, słudzy piekieł! Nie zostawię was w spokoju, dopóki moja ręka jest w stanie uderzać...";
			link.l1 = "Cieszę się z twojego szczęścia, Pastorze. A co z twoim głosem?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "Jak ci powiedziałem: 'Nie obchodzi mnie, kto zostanie szefem'. Jestem pewien, że Svenson nie wybierze niegodnego człowieka. Więc masz mój głos. Rób z nim, co chcesz. Oto mój kawałek.";
			link.l1 = "Dziękuję, Zachariaszu. Do zobaczenia tam!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", Cieszę się, że cię widzę! Czego chcesz?","Czego jeszcze chcesz?","Znowu? Nie zawracaj ludziom głowy, jeśli nie masz nic do roboty!","Jesteś "+GetSexPhrase("dobry korsarz","grzeczna dziewczynka")+", więc możesz żyć na razie. Ale nie chcę już z tobą rozmawiać.","powtórz",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Przychodzę tylko z wizytą.","Nic...","Dobrze, Pastorze, przepraszam...","Cholera, moja wina!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Czyś ty oszalał? Chciałeś bawić się w rzeźnika? Wszyscy piraci są na ciebie wściekli, chłopcze, więc lepiej opuść to miejsce...","Wydaje się, że oszalałeś, chłopcze. Chciałeś trochę rozprostować ręce? Bez urazy, ale nie masz tu nic do roboty. Zjeżdżaj!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomóż mi rozwiązać ten problem...");
				link.l1.go = "pirate_town";
				break;
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "O twoim więźniu.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Chodzi o twojego więźnia.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Witaj, Pastorze, jestem tu z powodu twojej misji.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "Słyszałem, że zajmujesz się interesami związanymi z więźniami...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Myślisz, że mam tu tylko jednego więźnia? Nazwij go.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Jest tutaj?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Był. Sprzedałem go temu właścicielowi plantacji z Barbadosu - pułkownikowi Bishopowi, kiedy był tutaj tydzień temu.";
				link.l1 = "Cholera...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, wreszcie. Myślałem, żeby go sprzedać temu właścicielowi plantacji z Barbadosu, będzie tu za tydzień lub dwa... Masz okup?";
				link.l1 = "Spójrz, jest pewien mały problem... Właściwie to nie mam tyle pieniędzy. Ale jestem gotów do pracy.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150.000 pesos. Gdzie mogę go znaleźć?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Byłeś za wolny... A dlaczego ci na nim zależy? Negocjowałem tylko z jego krewnymi.";
			link.l1 = "Poproszono mnie, abym tu przyszedł.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "No, spóźniłeś się. Nic nie mogę zrobić.";
			link.l1 = "Słuchaj, za ile go sprzedałeś, jeśli to nie tajemnica?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, to nie tak. Ale ci nie powiem... będziesz się śmiał, jeśli to zrobię. Ha-ha-ha-ha! Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Cóż, "+pchar.name+", wiesz, to tak nie działa. Wróć z pieniędzmi, a dostaniesz swojego słabeusza, ha-ha.";
				link.l1 = "Zgoda. Do zobaczenia.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Cóż, cóż... Mam jeden interes... Nawet nie wiem, jak zacząć. Muszę zatopić jednego pirata, który przekroczył granicę.";
				link.l1 = "Czy nie można go po prostu zabić w dżungli?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "To nie tak, jak działa biznes, wiesz... Nie potrzebuję jego śmierci, muszę nauczyć niektórych trzymać się z dala od mojej części łupu. Ale nie będę żałować jego śmierci.";
			link.l1 = "Dlaczego nie wyślesz swoich ludzi po niego?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Cóż, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+"przekonał niektórych piratów, że ich część łupu trzymana jest w naszej skrytce niedaleko od "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Ich dwa statki '"+pchar.GenQuest.CaptainComission.ShipName1+"' i '"+pchar.GenQuest.CaptainComission.ShipName2+"' podnieśli kotwice niedawno i popłynęli do "+sLoc+"Teraz widzisz, dlaczego nie mogę ufać moim ludziom, że wykonają tę robotę?";
			link.l1 = "Tak, jak długo mam czas?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 do 15 dni, nie więcej, to dla mnie ważne, jeśli nie dotrą do skrytki, bo to będzie nonsens zatopić ich z cennym ładunkiem. W takim razie lepiej, żeby to tutaj przywieźli...";
			link.l1 = "Dobrze, wchodzę w to. Spróbuję ich złapać.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Nie martw się. Moi ludzie dostarczą go na twój statek. A dlaczego ci zależy na nim?";
			link.l1 = "Nie. Jego krewni poprosili mnie, bym go dostarczył.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ach, to dobrze. Prawie żałowałem, że dałem tak niską cenę za twojego człowieka. Ha-ha-ha-ha. Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Więc, , "+GetFullName(pchar)+", zatopiłeś moich kumpli? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nie. Nie udało mi się ich złapać. I nie spotkałem ich po powrocie.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Zrobiłem to. Wysłałem ich na pożarcie rekinom.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Cholera! Spotkałeś ich czy nie, teraz to bez znaczenia! A jaka będzie twoja następna propozycja?";
			link.l1 = "Może masz dla mnie łatwiejsze zadanie?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Słuchaj, "+NPChar.name+", obniż cenę za więźnia...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nie.";
			link.l1 = "Żegnaj zatem...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Obniżyć cenę?! Przez twoją niekompetencję straciłem swój skarb! A teraz mogę podnieść cenę! Możesz go wziąć za 200.000 pesos, jeśli chcesz, albo możesz się stąd wynosić.";
			link.l1 = "To zbyt drogie... Żegnaj...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Cholera, bierz swoje monety.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Możesz zabrać tego słabeusza...";
			link.l1 = "Żegnaj.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Dobra robota! Zabieraj swego słabeusza i powodzenia.";
			link.l1 = "Dzięki. Żegnaj.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Przyniosłeś okup"+GetSexPhrase("","ла")+"Bo nie żartowałem, gdy powiedziałem, że sprzedam go plantatorom.";			
			link.l1 = "Słuchaj, "+NPChar.name+", widzisz, sprawa wygląda tak... W sumie, nie mam takich pieniędzy. Ale jestem gotów"+GetSexPhrase(" ","а")+" odpracować.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150000 pesos. Gdzie mogę go znaleźć?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Przyniosłeś pieniądze? Nie żartowałem, mówiąc o sprzedaniu tego człowieka na plantację.";			
			link.l1 = "Nie mam pieniędzy, "+NPChar.name+", ale nad tym pracuję.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150.000 peso. Gdzie mogę go znaleźć?"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "A dlaczego cię obchodzi, co robię? Wiesz co, lepiej odejdź...";
			link.l1 = "Tshh, uspokój się. Mam interes z tobą. Chodzi o twojego więźnia.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ach, dobrze. Kogo chcesz wykupić?";
			link.l1 = "Poczekaj. Nie przyszedłem tutaj się wykupić, przyszedłem zaoferować ci kupno więźnia. Cóż, i będziesz miał okazję otrzymać za niego okup.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. A dlaczego potrzebujesz mojego pośrednictwa? Czemu nie chcesz zdobyć pieniędzy bezpośrednio dla siebie?";
			link.l1 = "To dla mnie dość ryzykowne. Mogę mieć problemy z władzami.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... dobrze więc. Spójrzmy. Kto jest twym więźniem?";
			link.l1 = "To jest "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Rozumiem... byłby to dobry handel, jeśli nie kłamiesz. Myślę, że mogę zapłacić ci za tego człowieka "+iTemp+" pesety albo podziel się ciekawymi informacjami. Wybór należy do ciebie.";
			link.l1 = "Lepiej wezmę pesos. Mam dość tego interesu...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Opowiedz mi więcej. Jestem pewien, że zaoferujesz mi coś interesującego.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Pieniądze zatem. Weź je. Teraz to nie twój problem. Dostarcz tu przedmiot sprzedaży.";
			link.l1 = "On musi już być przy bramach miasta. Dzięki! Naprawdę mi pomogłeś.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Nie ma za co, przynieś mi więcej... Do zobaczenia!";
			link.l1 = "Powodzenia...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Miło robić interesy z mądrym człowiekiem. Teraz słuchaj: za kilka dni do "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"To")+" hiszpańska ekspedycja przybędzie z lądu, załadowana cennymi towarami. Będą czekać na statek, który ma zabrać ładunek. Jeśli dotrzesz tam w ciągu tygodnia, będziesz miał szansę zabrać ładunek dla siebie.\nGdybym był na twoim miejscu, już bym się ruszał na swój statek. I przynieś tu więźnia.";
					link.l1 = "Dzięki! Towary będą miłą rekompensatą za moje kłopoty. A mój pasażer musi już być blisko bram miasta. Zostanie do ciebie przyprowadzony.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Miło robić interesy z mądrym człowiekiem. Teraz słuchaj: za około tydzień hiszpańska brygantyna '"+pchar.GenQuest.Marginpassenger.ShipName1+" załadowany cennymi towarami wypłynie z "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" do "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Rodzaj")+". Jeśli się pośpieszysz, złapiesz go łatwo.\nJesteś jeszcze tutaj? Na twoim miejscu już bym ruszał na swój statek. I przyprowadź tu więźnia.";
					link.l1 = "Dzięki! Towary będą miłym zadośćuczynieniem za moje kłopoty. A mój pasażer musi już być blisko bram miasta. Zostanie do ciebie przyprowadzony.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Napad!!! To jest nie do zaakceptowania! Przygotuj się, "+GetSexPhrase("chłopcze","dziewczyna")+"...","Hej, co do diabła tam robisz?! Myślałeś, że możesz mnie okraść? Już po tobie...","Poczekaj, co do diabła? Zabieraj łapy! Okazuje się, że jesteś złodziejem! Koniec linii, draniu...");
			link.l1 = LinkRandPhrase("Cholera!","Carramba!!","Cholera!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(" "+GetSexPhrase("Odejdź ","Odejdź")+" stąd!"," Wynoś się z mego domu!");
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Nie zawracaj mi głowy swoimi tanimi gadkami. Następnym razem nie spodoba ci się wynik...";
        			link.l1 = "Zrozumiałem.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("To koniec, bez gadania.","Nie chcę z tobą dłużej rozmawiać, więc lepiej mnie nie niepokój.");
			link.l1 = RandPhraseSimple("Jak sobie życzysz...","Hm, dobrze więc...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Mam nadzieję, że okażesz więcej szacunku i przestaniesz być niegrzeczny?";
        			link.l1 = "Możesz być pewien, Pastorze, zrobię to.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Rozwiązać problem? Czy masz pojęcie, co narobiłeś? Tak czy inaczej, przynieś mi milion pesos, a przekonam chłopców, żeby zapomnieli o twoim czynie. Jeśli ten pomysł ci się nie podoba, to możesz iść do diabła.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Dobrze, jestem gotów zapłacić.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Zrozumiano. Wychodzę.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Dobrze! Uważaj się znów za czystego. Ale mam nadzieję, że nie będziesz już robił takich ohydnych rzeczy.";
			link.l1 = "Nie będę. Zbyt drogie dla mnie. Żegnaj...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
