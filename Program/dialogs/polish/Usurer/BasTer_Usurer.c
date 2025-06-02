// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi to pytanie niedawno...","Tak, pozwól, że zgadnę... Znowu krążysz w kółko?","Słuchaj, ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do powiedzenia."),"Umph, gdzież moja pamięć się podziała...","Zgadłeś, przykro mi...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "Jestem kapitanem "+GetFullName(pchar)+". Twój człowiek powiedział mi, że chciałeś mnie widzieć. Zamieniam się w słuch.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "Znowu ja, monsieur "+GetFullName(pchar)+"Przyprowadziłem ci Bertranda Pinette. Jest w mojej ładowni.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "To znowu ja, monseniour "+GetFullName(pchar)+"Porozmawiajmy.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "Znowu ja, monsieur "+GetFullName(pchar)+" Porozmawiajmy.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "Znowu ja, monsieur "+GetFullName(pchar)+"Zakładam, że nie spodziewałeś się mnie znowu zobaczyć.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "A-ah, kapitanie "+GetFullName(pchar)+"! Tak się cieszę, że cię widzę! Czekałem na ciebie dość długo... Dobrze. Mam pytanie do ciebie. Jakiś czas temu człowiek o imieniu Bertrand Pinette podszedł do ciebie w porcie, aby dostać się na pokład twojego statku. Bogato wyglądający jegomość w luksusowej peruce. Czy coś ci to mówi?";
			link.l1 = "Tak, rzeczywiście. Podszedł do mnie z tym właśnie zamiarem.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("You have received a heavy purse");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "Czy chciał wynająć ciebie i twój statek? Kapitanie, wyświadczyłbyś mi wielką przysługę, opowiadając mi wszystkie szczegóły tej sprawy. Odpłacę ci za to. Oto sakiewka pełna monet. Jest twoja, teraz proszę, powiedz mi o Bertrandzie Pinette.";
			link.l1 = "Bardzo dobrze. Monsieur Pinette wynajął mój statek, aby przewieźć jego i dwóch jego przyjaciół z Gwadelupy do hiszpańskiego Maine. Dokładniej mówiąc, do Zatoki Komarów w Portobello. Wykonałem zadanie, zeszli z mojego statku i poszli prosto w dżunglę.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Rozumiem. A czy monsieur Pinette wspomniał o swojej ostatecznej destynacji? A co z jego towarzyszami?";
			link.l1 = "Według jego własnych słów, zmierzali do Panamy. Jego przyjaciele byli dość intrygujący: dwóch oficerów, Hiszpan i Francuz. Nadal nie mogę pojąć, co ich połączyło, ale nie płacono mi za zadawanie pytań.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Hiszpański oficer? I francuski oficer? Och! Czyż to nie coś! Brawo, monsieur Pinette! Co za przebiegły pies! Nawet tutaj znalazł sposób na zarobek! Panama, mówisz?";
			link.l1 = "Tak, i powiedziałem ci wszystko, co wiedziałem. Czy mogę odejść?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "Poczekaj, kapitanie. Mam dla ciebie propozycję biznesową. Czy nie masz nic przeciwko zarobieniu kilku monet? Ale najpierw pozwól, że opowiem ci coś o twoich pasażerach.";
			link.l1 = "No cóż, posłuchajmy.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "Monsieur Bertrand Pinette pojawił się w naszej kolonii dwa lata temu i natychmiast zaczął robić interesy z kapitanami. Interesy, cóż, także mroczne... Dostarczali mu towary, których bardzo brakowało w tym miejscu, kosztowności, kontrabandę, czasami nawet niewolników... Systematycznie brał pożyczki na swoje nielegalne operacje w moim biurze, ale zawsze spłacał z wszystkimi odsetkami\nPrzed opuszczeniem wyspy z twoją dobrą pomocą, wziął ogromną pożyczkę, znacznie większą niż zwykle. Był... był zaufanym klientem z nieskazitelną historią kredytową, dlatego udzieliłem mu pożyczki. Wielki błąd. Monsieur Pinette uciekł i oczywiście nie zamierza zwrócić moich monet.";
			link.l1 = "Jak duża jest suma, jeśli mogę zapytać?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "To duże. Około stu pięćdziesięciu tysięcy pesos w dublonach. Dziesięć skrzyń, każda ze stu pięćdziesięcioma dublonami. I nie wspominając o wszystkich odsetkach.";
			link.l1 = "Hm... Płacił Ci przez dwa lata, przyzwyczaił Cię do tego, wziął spory kredyt, a potem stał się oszustem. Sprytne.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "Dokładnie, kapitanie. Dlatego chciałbym cię zatrudnić do pewnej roboty: znajdź tego łajdaka i przyprowadź go tutaj. Ja, gubernator i komendant znajdziemy sposób, by zmusić go do spłacenia długu. Widziałeś tego człowieka, był twoim pasażerem, to oznacza, że masz większe szanse na znalezienie monsieur Pinette niż ktokolwiek inny. Oczywiście, zatrudnię też zawodowych łowców nagród na jego nieszczęsny tyłek, ale mam przeczucie, że twoja pomoc okaże się bardziej skuteczna.";
			link.l1 = "A co z nagrodą?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "Za wykonanie zadania dam ci skrzynię pełną dublonów, sto pięćdziesiąt monet.";
			link.l1 = "Powiadam, że to byłaby dość żałosna nagroda za śledzenie i porwanie żywej duszy w hiszpańskim mieście.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "Kapitanie, zakładam, że monsieur Pinette dobrze ci zapłacił moimi pieniędzmi, skoro tak tanio oceniasz moją propozycję. Zapewniam cię, że jest warta wysiłku. Oczywiście, masz pełne prawo odmówić... ale mam coś do powiedzenia i to z pewnością sprawi, że zmienisz zdanie.";
			link.l1 = "A cóż to jest?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "Kilka dni przed ucieczką Pinette z Gwadelupy, jeden więzień uciekł z więzienia w Basse-Terre. Nazywa się don Carlos de Milyar, hiszpański grand i oficer. Udało mu się to dzięki zdradzie francuskiego oficera, porucznika piechoty morskiej... Czy rozumiesz, co mam na myśli?";
			link.l1 = "Hm... A cóż mnie to obchodzi? Zajmowałem się przewozem pasażerów, niczym więcej.";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "Na pewno, że byłeś! Osobiście nie mam wątpliwości, że nie masz nic wspólnego z organizacją ucieczki don de Milyara. Ale to nie tak, jak mogą myśleć nasz gubernator i nasz komendant. Zarzut współudziału, jeśli masz szczęście, a jeśli nie... naprawdę nie chcę kontynuować. Przekonaj się sam, wziąłeś na pokład zbiegłego hiszpańskiego oficera, najpewniej w jakiejś ukrytej zatoce... mam rację, kapitanie?";
			link.l1 = "Rozumiem. Szantażujesz mnie. Popełniłem błąd, przychodząc tutaj...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "Co powiesz, kapitanie?! Nie szantażuję cię! Wszystko, o co proszę, to pomóc mi za dobrą nagrodę. Czy byłbyś tak uprzejmy znaleźć monsieur Pinette i dostarczyć go do Basse-Terre? Będę czekał na twój powrót. Wierzę, że dwa miesiące wystarczą, aby popłynąć do Panamy i z powrotem.";
			link.l1 = "Nie zostawiasz mi wyboru. Choć wątpię, by takie podejście do interesów przyczyniło się do naszej przyjaźni. Żegnaj, monsieur.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Znakomite wieści, kapitanie! Wyślę moich ludzi, by natychmiast zabrali tego drania z twojego statku. Tym razem ten ptaszek nie ucieknie mi... Zasłużyłeś na swoją nagrodę, weź tę skrzynię. Proszę, nie gniewaj się na mnie, oto amulet dla ciebie. To prezent.";
			link.l1 = "Wdzięczność. Zakładam, że twoje milczenie to także część mojego wynagrodzenia?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("You have received a chest full of doubloons");
			Log_Info("You have received a 'Fisherman' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "Cisza? O czym? Będę rad widzieć cię wśród moich klientów. Wiesz, co mówią o ciszy i złocie?";
			link.l1 = "Warto czasami więcej niż złoto, monsieur. Lekcja nauczona. Żegnaj!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "Słucham. Bertrand Pinette jest na twoim statku, jak sądzę?";
			link.l1 = "Nie. Choć mam dla ciebie coś znacznie lepszego. Przeczytaj to.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Co to jest?";
			link.l1 = "Czytaj dalej, monsieur. Kontynuować będziemy później.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(czytając) Ahem ... Co to za bzdury chorego z gorączką?";
			link.l1 = "Jesteś poważny? Dobrze, zaniosę te 'bzdury' do gubernatora. Wierzę, że okaże on wielkie zainteresowanie poznaniem prawdy o zniknięciu 'Courage' i jej transportu diamentów... Dlaczego zrobiłeś się taki blady?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "Więc jednak odnalazłeś Pinette...";
			link.l1 = "Tak. Proponuję ci więc umowę. Zapomnij o Carlosie de Milyar, Jean Deno i innych dobrych dżentelmenach, zrób to, a zapomnę o tym liście.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "Bardzo dobrze, kapitanie... Zgadzam się na twoje warunki.";
			link.l1 = "Uroczo. Mam nadzieję, że nie jesteś na mnie zły, teraz skończyliśmy, jak sądzę. Żegnaj.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "Ha... Masz rację, kapitanie.";
			link.l1 = "Mam coś dla ciebie. Weź to i przeczytaj.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "A więc, w końcu znalazłeś Pinette...";
			link.l1 = "Tak. Proponuję więc układ. Przywróć moje dobre imię we francuskich koloniach, a zapomnę o tym liście.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "Ale...";
			link.l1 = "Nie obchodzi mnie, jak to zrobisz. Jeśli polowanie na moją głowę nie skończy się jutro, gubernator dowie się o wszystkim.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
