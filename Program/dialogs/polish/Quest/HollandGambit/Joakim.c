// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Dzień dobry, sir! Jestem doktor Joachim Merriman. Czy mam przyjemność rozmawiać z kapitanem "+GetFullName(pchar)+"?";
					link.l1 = "Tak, to ja. Jak diabli znasz moje imię? Nie przypominam sobie, żebyśmy się wcześniej spotkali.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Cieszę się, że cię widzę, kapitanie. Po sprężystym kroku widzę, że zamierzasz mnie bardzo uszczęśliwić. Czy masz czaszkę Yum Cimila?";
					link.l1 = "Posiadam czaszkę, o której mówisz. Wręcz trzeszczy od energii, niczym ryczący piec.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Czy masz coś jeszcze do powiedzenia, kapitanie?";
				link.l1 = "Nie, señor Merriman. Odchodzę...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Dzień dobry, sir! Jestem doktor Joachim Merriman. Czy mam przyjemność rozmawiać z kapitanem "+GetFullName(pchar)+"?";
					link.l1 = "Tak, to ja. Jakim cudem znasz moje imię? Nie przypominam sobie, żebym cię wcześniej spotkał.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "Cieszę się, że cię widzę, kapitanie. Widzę po twoim kroku, że zamierzasz mnie bardzo uszczęśliwić. Czy masz czaszkę Yum Cimil?";
					link.l1 = "Posiadam czaszkę, o której mówisz. Aż trzeszczy od energii, niczym ryczący piec.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Czy masz coś jeszcze do dodania, kapitanie?";
				link.l1 = "Nie, doktorze Merriman. Odchodzę.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Dzień dobry. Chcesz czegoś ode mnie?";
			link.l1 = "Nie, przepraszam.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "Jeśli przyszedłeś do doktora Merrimana, to go tu nie ma. Już tu nie mieszka.";
			link.l1 = "Widzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "Jeśli przyszedłeś zobaczyć Doktora Merrimana, to muszę ci powiedzieć, że nie ma go w domu. W tej chwili podróżuje i nie wiem, kiedy wróci.";
			link.l1 = "Widzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "Jeśli przyszedłeś zobaczyć się z doktorem Merrimanem, to go tu nie ma. Już tu nie mieszka.";
			link.l1 = "Widzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Twoje sprawy nie są tak prywatne, jak możesz sądzić, kapitanie! Ale nie bój się, mam dla ciebie propozycję! Jestem człowiekiem nauki, swego rodzaju przyrodnikiem, badającym fascynującą kulturę indiańskich pogan hiszpańskich kolonii i Indii Zachodnich. Czy byłbyś tak uprzejmy, by pójść ze mną do mojego domu i omówić w moim salonie potencjalnie bardzo zyskowne szczegóły?";
			link.l1 = "Masz moją ciekawość i moją uwagę. Prowadź.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "Nie odrzucicie tego, panie! Mój dom jest niedaleko stąd. Chodźcie za mną!";
			link.l1 = "... ";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Możemy tu rozmawiać bez obaw o ciekawskie uszy. Ostatnio odwiedzałeś mojego sąsiada, Solomona Shneura. Przechodziłem obok i, musisz mi wybaczyć kapitanie, przypadkiem usłyszałem kilka szczegółów twojej rozmowy z Solomonem. To było tak fascynujące, że musiałem wysłuchać wszystkiego!";
			link.l1 = "Podsłuchiwacz, który boi się innych podsłuchiwaczy, co?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Teraz, teraz, kapitanie! Wcale nie tak! Salomon jest moim sąsiadem i często mnie odwiedza. Jesteśmy dobrymi przyjaciółmi mimo naszych różnic religijnych! Znam jego nieszczęścia... tak samo jak wszyscy inni w Willemstad! Salomon opowiada o swoich kłopotach każdemu, kto zechce słuchać, rano, w południe i wieczorem. Ale dość o tym. Stary Żyd musiał już ci powiedzieć o starym jadeitowym czaszce, która jest ukryta razem z jego złotem na jakiejś nieznanej wyspie. Czy ci o tym mówił?";
			link.l1 = "Opowiedział mi o czaszce, nie wspomniał, że jest zrobiona z jadeitu. Powiedział także, że to czaszka jego dziadka, prawdę mówiąc, myślałem, że to albo jakiś kabałistyczny horror, albo stary dziwak ma nietoperze w dzwonnicy.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "Nie, kapitanie, Salomon jest całkiem przy zdrowych zmysłach, tylko ekscentryczny. Czaszka naprawdę istnieje. To starożytny indiański skarb, jadeitowa czaszka Yum Cimil! Nie mam pojęcia, jak stary Żyd zdobył ją w swoje szpony. Szukałem jej przez połowę życia\nSzukaj tej wyspy, gdzie Salomon ukrył majątek swojej rodziny. Czaszka musi tam być w jego skrzyni. Dostarcz mi tę jadeitową czaszkę, a zapłacę ci pół miliona peso.";
			link.l1 = "Połowa tysiąca? To ledwie warte mojej uwagi - zaczekaj chwilę... powiedziałeś pół miliona sztuk srebra?! Żartujesz sobie? Nigdy w życiu nie widziałem tylu pieniędzy w jednym miejscu!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "Jesteś jeszcze młodym kapitanem... Więc jak, wchodzisz w to? Dajesz mi jadeitową czaszkę, a ja dam ci w zamian pięćset tysięcy sztuk srebra. Umowa?";
			link.l1 = "Ha, majątek za starą czaszkę? Oczywiście, że się piszę.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Znakomicie. Zawsze to przyjemność pracować z człowiekiem, który rozumie zysk. Znajdziesz mnie tutaj w moim domu, jeśli będziesz mnie jeszcze potrzebował. Powodzenia!";
			link.l1 = "Dziękuję, doktorze Merriman. Nie każę ci czekać zbyt długo.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "O, tak! Zdecydowanie masz rację co do jego mocy... Ale dość słów, pozwól mi to zobaczyć, trzęsę się z niecierpliwości.";
			link.l1 = "Proszę, weź to. Mam nadzieję, że się nie pomyliłem?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ach, niesamowite! Tak, to jest to. Doskonale, kapitanie, najdoskonalej! Wreszcie! Mam to przy sobie, wreszcie! Czekałem na tę chwilę przez tyle lat!";
			link.l1 = "Co z pieniędzmi, które obiecałeś, doktorze Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "O, tak, oczywiście! Pół miliona sztuk ośmiu. Weź je, zasłużyłeś na nie.";
			link.l1 = "Przyjemność robić z tobą interesy. Trudno uwierzyć, że taka mała rzecz może być tyle warta...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Mała rzecz? Nie masz pojęcia, o czym mówisz. To jest... bah, twój filistyński umysł ledwie może pojąć wielkość niesamowitej mocy, która kryje się za tym cennym czaszką. Prawdę mówiąc, i tak nie mam czasu do stracenia\nDziękuję ci, kapitanie, za to, co zrobiłeś. Teraz czas się pożegnać. Muszę iść.";
			link.l1 = "Żegnaj, Doktorze Merriman. Być może spotkamy się ponownie.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Możemy tu porozmawiać, kapitanie. Wiem, że jesteś bliskim współpracownikiem Abigail Shneur, córki mojego sąsiada Solomona. Odpłynęła na twoim statku do swojego kochanka... ale to naprawdę nie ma znaczenia.";
			link.l1 = "Dokąd zmierzasz, doktorze?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "Jeśli znasz Salomona, to musisz znać jego historię o rozbiciu statku i jego zgubionych skarbach, które ukrył na jakiejś nieznanej wyspie. Już opowiedział tę historię wszystkim w Willemstad.";
			link.l1 = "Dlaczego przypuszczasz, że zarówno coś o tym słyszałem, jak i obchodzi mnie nieszczęście starego Żyda?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Nie lubisz Salomona? Zapewniam cię, że to tylko nieszkodliwy stary ekscentryk. Zapomnij o nim. Porozmawiajmy o interesach\nMiałem kilka długich rozmów z Salomonem. Nawet nie możesz sobie wyobrazić, jak się poczułem, kiedy dowiedziałem się, że ten stary Żyd jest właścicielem starożytnego bezcennego artefaktu, którego szukałem od lat! Szalony staruszek ukrył go razem z jego żałosnymi pieniędzmi na jakiejś wyspie i nie może nawet przypomnieć sobie jej lokalizacji\nPotrzebuję tego artefaktu. Przynieś go do mnie, a zapłacę ci pół miliona sztuk ośmiornic.";
			link.l1 = "Pół miliona sztuk srebra? Musisz żartować, doktorze. Nigdy w życiu nie widziałem tylu pieniędzy razem w jednym miejscu!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "Jesteś jeszcze młodym człowiekiem. Więc jak, wchodzisz w to? Dajesz mi czaszkę, a ja dam ci w zamian pięćset tysięcy sztuk złota. Na dodatek, możesz zabrać też pieniądze Solomona. Według słów starca, powinno tam być około dwustu tysięcy pesos... Razem siedemset tysięcy sztuk złota dla ciebie. Umowa stoi, kapitanie?";
			link.l1 = "Niech mnie piorun trzaśnie! Oczywiście, że to umowa! Ale jak mam znaleźć tę wyspę?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Porozmawiaj z Abigail. Może coś pamięta. Zapytaj Solomona. Widzisz, gdybym wiedział, gdzie znaleźć wyspę, nie prosiłbym cię o pomoc na początku.";
			link.l1 = "Rozumiem. Przepraszam za moje głupie pytanie. Teraz muszę znaleźć tę wyspę. Upewnij się tylko, że czekasz z moją zapłatą.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Dokładnie. Cieszę się, że się rozumiemy, kapitanie. Powodzenia w poszukiwaniach. Zawsze możesz mnie znaleźć tutaj, w moim domu.";
			link.l1 = "Nie każę ci długo czekać, doktorze Merriman. Do widzenia!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "Takkkkk. Kamienie ofiarne spływają krwią moich wrogów! Yum Cimil obdarzył mnie mocą władania umarłymi! Dzięki tej mocy wkrótce będę rządzić żywymi!";
			link.l1 = "Jakie melodramatyczne, Merriman. Co zamierzasz zrobić ze swoją armią chodzących trupów? Grasz w Cezara, próbując podbić świat?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Milcz, głupcze! Czy oczekujesz, że ujawnię mój tajny plan w monologu?! Cóż, nie widzę powodu, by tego nie zrobić, nie przeżyjesz tego spotkania! Moje nieumarłe legiony najpierw zajmą wszystkie mroczne jaskinie i lochy Karaibów. Moje posterunki będą rozmieszczone w każdej wiosce, czekając na mój sygnał. A gdy nadejdzie czas, moje chodzące trupy wyruszą i pokryją ziemie żywych!\nSzkoda, że nie dożyjesz tego, ty żałosny mały aniołku, udający bohatera! Wszedłeś do mojego sanktuarium - i nie wyjdziesz z niego żywy! Poprowadzę moją armię ciemności!";
			link.l1 = "Słuchaj, kumplu, nie prowadzisz niczego oprócz Jacka i gówna, a Jack właśnie opuścił miasto.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "O ho ho! Ośmielisz się rzucić wyzwanie mnie i moim szkieletowym sługom?! Zatem zobacz, czym naprawdę jestem, i drżyj z przerażenia!";
			link.l1 = "Chodź, dostaniesz swoje.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "Ahhh! Słodki Jezu!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "Teraz rozumiesz, kto stoi przed tobą, ty jęczący robaku?! Mam z tobą do wyrównania rachunki! Sam Yum Cimil mnie faworyzuje! Pożrę twoją duszę!";
			link.l1 = "Dobrze, kościotrupie. Zatańczmy.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("złodziej, panie! Strażnicy, łapcie go","złodziejka, dziewko! Straże, schwytajcie ją")+"!!!","Popatrz tylko na to! Ledwo się odwróciłem, a już postanowiłeś sprawdzić moją skrzynię! Łapać złodzieja!!!","Straż! Rabunek! Łapać złodzieja!!!");
			link.l1 = "Cholera!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
