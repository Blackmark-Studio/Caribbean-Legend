void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
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
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "Czego chcesz, "+GetSexPhrase("kolega","dziewczyna")+"? Jeśli proponujesz mi trochę rumu, nie odmówię. Obszedłem to przeklęte miasto już tyle razy, że nogi zaraz mi się w supeł zwiążą. Jak się nazywasz?";
			link.l1 = "Kapitan "+GetFullName(pchar)+". Nie jesteś z 'Orła', prawda?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "A ja - "+GetFullName(npchar)+". Tak, jestem z 'Orła'. Podoba się panu nasz statek, kapitanie?";
			}
			else
			{
				dialog.text = "Kapitán? No proszę... Ekhm... Nazywam się Antonio Velenta. I tak, jestem z 'Orła'. Nasz statek wpadł ci w oko, kapitanie?";
			}
			link.l1 = "Statek to statek. Lepiej się pospiesz i wejdź na pokład zamiast wałęsać się po mieście — twój kapitan już zieje gniewem. Zamierza opuścić port, zanim odpłynie przypływ, i coś mi mówi, chłopcze, że nie będzie na ciebie czekał.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Cholera jasna... Wiem, wiem... Ale mam tu jeszcze kilka niedokończonych spraw. Masz ochotę zarobić parę dublonów, co, Kapitanie?";
			link.l1 = "Dublony zawsze się przydadzą. Ale zarobić je to jedno, a wpakować się w kłopoty to drugie. Jaka robota? Mów, o co chodzi.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Widzisz, kiedy rozładowywałem ładownię, natknąłem się na list. Nie wyglądało na to, żeby był celowo ukryty, po prostu leżał tam wśród starych beczek. Nasz fluit przeżył niejedne abordaż, więc trudno powiedzieć, skąd się wziął.";
			link.l1 = "Więc znalazłeś list, ale co z tego?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "Adresowany jest do pewnej Marisy Caldery z Porto Bello. Zapieczętowany woskiem... Czuję w kościach, że to nie błaha sprawa. Może od kapitana, może od kupca... ale na pewno nie od zwykłego marynarza, takiego jak ja! Tylko że nie będę miał czasu znaleźć adresatki – nasz kapitan nie żartuje z takimi rzeczami.  Nie chcesz go ode mnie odkupić? Oddam za tysiąc pesos. Jesteś kapitanem, łatwo ci będzie wytropić tę señorę. A kto wie, może cię wynagrodzi złotem, albo czymś jeszcze... rozumiesz, o co chodzi?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "No dobrze, może znajdę twoją Marisę.  Tak czy inaczej, nie mam nic do stracenia. Z wyjątkiem tysiąca pesos. Dawaj ten list.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				notification("Za mało pieniędzy (1000)", "Money");
			}
			link.l2 = "Wybacz, ale musisz poszukać kogoś innego. Mam ważniejsze sprawy na głowie niż roznoszenie listów.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Proszę bardzo. No, trzymaj się, "+GetSexPhrase("kolega","dziewczyno")+", powinienem już iść – nie chciałbym, żeby moje rzeczy odpłynęły razem z 'Orłem'.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Kim jesteś? Czego chcesz?";
			link.l1 = "Nazywam się kapitan "+GetFullName(pchar)+". Szukam Marisy Caldery.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Nie znam żadnej Marisy. Pomyliłeś drzwi. Odejdź teraz, zanim zawołam strażników – wyrzucą cię stąd w mgnieniu oka.";
			link.l1 = "Ojciec "+sld.name+" powiedziała mi, że jesteś jej przyjacielem. Mam do niej list. Sądząc po jego wyglądzie, jest bardzo spóźniony. Chcę dostarczyć go osobiście.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ach, ojciec... Jest zbyt uprzejmy dla wszystkich, ale rzadko myli się co do ludzi. Możesz zostawić list u mnie. Dopilnuję, żeby trafił w jej ręce.";
			link.l1 = "Wybacz mi, señorita, ale wolałbym przekazać to osobiście. Może mieć pytania, skąd to mam i dlaczego dotarło tak późno.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "I ty oczekujesz, że po prostu uwierzę w twoje dobre intencje? Widziałem już wielu łotrów o cnotliwych twarzach. Zostaw list albo odejdź.";
			link.l1 = "Daję ci słowo kapitana, że nie zrobię krzywdy ani tobie, ani Marisie. Co więcej, możesz zaprosić strażnika lub kogokolwiek innego, kto potrafi władać bronią, na nasze spotkanie. Nie mam innego celu, jak tylko osobiście przekazać ten list Marisie.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "W porządku. Przyjdź jutro po jedenastej w nocy. Nie mogę obiecać, że zgodzi się na spotkanie, ale przekażę wszystko, co powiedziałeś.";
			link.l1 = "Będę tam. Do zobaczenia wkrótce.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Cześć, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Szukałeś mnie, a oto jestem. Dolores powiedziała, że masz dla mnie list?";
			link.l1 = "Dzień dobry, pani Caldera. Zgadza się, oto pani jest. Niestety, wygląda na to, że dotarcie do pani zajęło sporo czasu.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Przekazano: List do Marisy Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... To jest jego pismo... Pismo Ramira!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "Ale jak to możliwe? Minęły już dwa lata!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Kapitanie... Jak wszedłeś w jego posiadanie? Gdzie je znalazłeś? Muszę wiedzieć wszystko! Proszę, powiedz mi wszystko, co wiesz.";
			link.l1 = "Ten list dostałem od marynarza. Znalazł go w ciemnym kącie ładowni swojego statku i chciał osobiście ci go przekazać, ale musiał w pośpiechu wracać na pokład. Poprosił więc mnie, żebym cię odnalazł, i oto jestem. To wszystko, co wiem...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Dziękuję, "+GetAddress_Form(NPChar)+"! Dziękuję ci bardzo! Proszę, nie odchodź. Chcę jeszcze z tobą porozmawiać, ale najpierw... muszę przeczytać ten list.";
			link.l1 = "Oczywiście, Lady Caldera. Będę tutaj.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Minęło dwadzieścia minut, Marisa przeczytała list...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Napisał ten list przed swoją ostatnią podróżą. Chciał mi powiedzieć, że miał szansę kupić dużą partię hebanu od kupca w Belize, ale nie miał wystarczająco pieniędzy. Wtedy wziął tę pożyczkę... Dwieście doblonów... Przez którą teraz nie mogę zaznać spokoju.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "To wszystko wyjaśnia... Ale, niestety, nie ulży to twojemu ciężarowi. Bądź silna, Marisa. Ciemność nie trwa wiecznie, a ten dług nie będzie cię prześladował bez końca.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "Nie, Dolores, nie będzie! Ramiro napisał, że ma skrytkę... w naszym miejscu. Jeśli wciąż jest nietknięta, może uda mi się spłacić dług i w końcu uciec z tego koszmaru.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "Pan okazał ci łaskę! Wysłuchał naszych modlitw...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Kapitánie, jeszcze raz dziękuję, że przyniósł mi pan ten list. To dla mnie naprawdę wiele znaczy... Ale muszę prosić pana o jeszcze jedną przysługę. Wie pan, mój mąż Ramiro był dla mnie wszystkim i nigdy nie szukałam ochrony u żadnego innego mężczyzny. Teraz, gdy go już nie ma, nie mam się do kogo zwrócić, nie mam własnej rodziny\nMuszę dotrzeć do jego kryjówki – jest poza miastem. Ale boję się iść sama, ścigają mnie wierzyciele mojego zmarłego męża. Zachował się pan bardzo szlachetnie, znajdując mnie, by doręczyć list... Proszę, pomóż mi jeszcze raz.";
			link.l1 = "Oczywiście, Marisa, odprowadzę cię. Kiedy chciałabyś wyruszyć?";
			link.l1.go = "Marisa_16";
			link.l2 = "Przepraszam, señora, ale mój pobyt w waszym mieście już trwa zbyt długo. Spacery po okolicy nie są częścią moich planów.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Rozumiem... Zrobiłeś już dla mnie więcej, niż mogłem się spodziewać. Dziękuję ci, kapitanie, i żegnaj.";
			link.l1 = "Do widzenia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Dziękuję, Kapitanie. Przyjdź jutro o świcie, do siódmej. Będę gotowy.";
			link.l1 = "Zatem do zobaczenia, señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, oto jesteś... Jesteś prawdziwym człowiekiem honoru! Ruszajmy. Nasza droga prowadzi przez dżunglę do groty niedaleko Zatoki Moskitów.";
				}
				else
				{
					dialog.text = "Kapitanko, oto jesteś... Wiedziałem, że przyjdziesz. Wiesz, to pierwszy raz, kiedy spotykam kobietę dowodzącą własnym statkiem. I już widzę, że dorównujesz każdemu mężczyźnie — zarówno honorem, jak i szlachetnością!";
				}
				link.l1 = "Doskonale, señora. Nie traćmy więc czasu. Trzymaj się blisko i nawet na chwilę się nie oddalaj.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Dziękuję ci, Marisa. Mój ojciec był kapitanem i człowiekiem honoru – od dziecka wpajał mi te same wartości.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Przyjdź o świcie, około siódmej. Będę gotowy.";
				link.l1 = "Do zobaczenia, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Czy tak? Spotkał ten sam los co mój Ramiro?";
			link.l1 = "Z pewnością wolałby odejść z mieczem w dłoni albo podczas sztormu. Ale los miał wobec niego inne plany – zgubiła go choroba, o której nikomu nigdy nie wspominał.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Przykro mi z powodu twojej straty, "+pchar.name+" Pan zabiera najlepszych spośród nas... I choć nie zawsze rozumiemy dlaczego, taka jest Jego wola. Jedyne, co możemy zrobić, to modlić się o spokój ich nieśmiertelnych dusz.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Ruszajmy. Nasza droga prowadzi przez dżunglę do groty niedaleko Zatoki Komarów.";
			link.l1 = "Oczywiście. Trzymaj się blisko i nie oddalaj się ani na chwilę.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Jesteśmy na miejscu... Ramiro i ja kiedyś schroniliśmy się tu przed deszczem, gdy byliśmy młodzi, zanim został moim mężem. To wtedy powiedział mi, że zdobędzie moje serce, bez względu na wszystko.";
			link.l1 = "Przykro mi, że musiałaś tu przyjść sama, bez męża, señora. Takie miejsca kryją wiele wspomnień. Rozejrzyjmy się – może oprócz wspomnień znajdziemy też to, co Ramiro zostawił na najtrudniejsze chwile.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"...   Znalazłeś coś?   To to, co zostawił Ramiro?   Nawet nie wiem, co mnie bardziej przeraża – że jest pusto, czy że to nie wystarczy, by spłacić dług...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(pokazuje) Proszę, to wszystko, co było w skrzyni. Mam nadzieję, że to wystarczy, by odmienić twój los na lepsze.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Wciąż przeglądam skrzynię.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ach, Kapitanie! Oczywiście! To powinno wystarczyć! Ale nie mogę pozwolić, żeby twoja pomoc została bez nagrody. Weź sto doblonów. Gdyby nie ty, nigdy nie dowiedziałbym się o tej skrytce i wciąż ukrywałbym się przed ludźmi nasłanymi przez wierzyciela Ramira...";
			link.l1 = "Jest pani bardzo hojna, señora, dziękuję. W naszej branży złoto nigdy się nie marnuje.";
			link.l1.go = "Marisa_34";
			link.l2 = "Nie, señora. To pani bardziej potrzebuje tych pieniędzy niż ja. Najważniejsze, że teraz może pani zostawić kłopoty za sobą i żyć w spokoju. To mi w zupełności wystarczy.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Przekazano: Amulet 'Cimaruta'", "None");
			notification("Przekazano: Amulet 'Rybak'", "None");
			notification("Przekazano: Muszkiet z zamkiem zapłonowym", "None");
			notification("Przekazano: Diament (10)", "None");
			notification("Przekazano: Rubin (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "No to w takim razie, "+GetSexPhrase("señor",""+pchar.name+"")+", powinniśmy ruszać. Jeśli ktoś mnie zauważył w mieście, mogą nas śledzić. Lepiej tu nie zwlekać.";
			link.l1 = "Masz rację, Marisa. Chodźmy.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Kapitanie, proszę... mój mąż trzymał tę broń, by chronić naszą rodzinę, i jestem pewna—w twoich rękach posłuży słusznej sprawie. Ramiro byłby szczęśliwy, wiedząc, że trafiła do osoby, która uratowała mnie, gdy wszelka nadzieja już zgasła.";
			link.l1 = "Dobrze, Marisa, dziękuję. Jesteś dobrą i szlachetną kobietą, i naprawdę żałuję, że los obszedł się z tobą tak okrutnie.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Czasem Pan zsyła nam trudne dni, a nawet lata, by wystawić naszą wiarę na próbę, ale nigdy nie opuszcza tych, którzy kroczą właściwą drogą. To On posłał cię, byś mi pomógł, i teraz mam nadzieję, że mój największy kłopot wkrótce zostanie za mną.  Ale na razie musimy wracać. Zatrzymaliśmy się tu już wystarczająco długo, a to może być niebezpieczne, bo wciąż mnie szukają.";
			link.l1 = "Oczywiście, señora, chodźmy.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ha! A więc tu jest nasz zaginiony! Naprawdę myślałeś, że możesz się tu ukryć, w tej norze jak mysz, i że cię nie znajdę? Przewróciłem całe miasto do góry nogami nie raz, a ty przez cały czas byłeś właśnie tutaj"+GetSexPhrase(", a na dodatek poszłaś na randkę z jakimś gówniarzem. Gdzie są moje pieniądze, ty mała dziwko? Lepiej oddaj je natychmiast, bo inaczej ta jaskinia stanie się twoim grobem.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Ty...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Więc to ty zarabiasz na życie, ściągając długi z kobiet? Patrząc na to, czym się zajmujesz, rozumu nigdy ci nie brakowało... aż dziw, że sam tu trafiłeś, zamiast po prostu podążać za kimś mądrzejszym... na przykład za własnym butem.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Zamknij się, bohaterze. Twoja kolej jeszcze przyjdzie, ale najpierw zajmę się nią. Jest mi winna pięćset dwadzieścia pięć doblonów – to jej dług z odsetkami. Albo spłaci wszystko, albo zostanie tu na zawsze – na pożarcie robakom. Ale skoro taki z ciebie sprawiedliwy, możesz zapłacić za nią, a ja zniknę.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Myślisz, że możesz tu po prostu wejść, obrazić damę, zignorować mnie i wyjść stąd w jednym kawałku, jeszcze z tymi dublonami? Wygląda na to, że nie grzeszysz rozumem. Ale nie zamierzam wszczynać bójki przy kobiecie. Mam więc dla ciebie propozycję: przeproś panią Calderę, zabierz swoje dublony i wynoś się stąd. W przeciwnym razie będę musiał nauczyć cię trochę ogłady.";
					link.l1.go = "Naemnik_5";
					notification("Sprawdzenie zakończone pomyślnie (525)", "Dubloon");
				}
				else
				{
					notification("Za mało złota (525)", "Dubloon");
				}
			}
			else
			{
				dialog.text = "Zamknij się i czekaj na swoją kolej. Z tobą porozmawiam później, jak skończę z tą nędznicą. Jest mi winna pięćset dwadzieścia pięć doblonów – tyle wynosi jej dług z odsetkami. Skoro jesteś taki sprawiedliwy, możesz za nią zapłacić, a ja znikam.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Cóż, jestem gotów wybaczyć ci twoje szorstkie maniery, a nawet nieuprzejmość wobec mnie. Ale jeśli chcesz dostać swoje dublony i wyjść stąd w jednym kawałku, będziesz musiał przeprosić Lady Calderę. W przeciwnym razie przekonamy się, kto lepiej włada bronią. I uwierz mi, nie noszę swojej tylko na pokaz.";
					link.l1.go = "Naemnik_5";
					notification("Sprawdzenie zakończone pomyślnie (525)", "Dubloon");
				}
				else
				{
					notification("Za mało złota (525)", "Dubloon");
				}
			}
			link.l2 = "Najwyraźniej nie masz zbyt wiele rozumu, skoro myślałeś, że będę czekać na swoją kolej. A jeszcze mniej, jeśli wierzyłeś, że przymknę oko na wszystkie kłopoty, które ty i twoi ludzie sprowadziliście na Lady Calderę.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "No dobrze, niech będzie po twojemu. Jeśli możemy zdobyć pieniądze bez zbędnego ryzyka, nie widzę powodu, by się wychylać. Oddaj dubloony – i znikaj.";
			link.l1 = "Najpierw przeproś damę.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Wybacz mi, señora. Diabeł mnie poniósł.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Szczęśliwy"+GetSexPhrase("","")+"   Oddaj złoto i pójdę swoją drogą. Mam mnóstwo spraw na głowie, nie będę tu stał i wdawał się z tobą w pogawędki.";
			link.l1 = "Weź swoje dublony i wynoś się stąd.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Kapitánie, naprawdę nie rozumiem... Co to ma znaczyć?";
			link.l1 = "To znaczy, że już nic nie jesteś winien. Jesteś wolny.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Ale... nie mam teraz całej sumy, żeby ci oddać. Gdybyś mógł jeszcze trochę poczekać...";
			link.l1 = "Nie rozumiesz, Marisa. Nic mi nie jesteś winna. Nikomu już nic nie jesteś winna. A pieniądze, które znalazłaś, bardzo ci się przydadzą. Wróć do swojego dawnego życia – kościół na ciebie czeka.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Ja... Ja po prostu nie mogę w to uwierzyć. Takie rzeczy się nie zdarzają, "+GetSexPhrase("caballero","senorita")+"! Zapłaciłeś za mnie fortunę... tak po prostu? I co, to już koniec? Żadnych długów, żadnej pogoni? Powiedz mi, czy to prawda?";
			link.l1 = "To prawda, señora. To już koniec. Nikomu już nic nie jesteś winna.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "O, Kapitanie, jesteś taki szlachetny! Czuję, jakbyś został zesłany przez Boga! Ale nawet nie wiem, jak mogłabym ci podziękować. Ty... całkowicie odmieniłeś moje życie, a ja... co mogłabym dla ciebie zrobić?";
			link.l1 = "Nie musisz nic robić, Mariso. Po prostu żyj. Bez strachu, bez kajdan przeszłości. Wróć do dawnego życia i odnajdź w nim szczęście – to będzie dla mnie najlepsze podziękowanie. Chodź, odprowadzę cię do miasta.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "Coś ty zrobił, kapitanie, zabiłeś go!";
			link.l1 = "Zgadza się, señora. Musiałem cię chronić i bronić twojego honoru...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "O Kapitanie, odebranie życia, nawet komuś takiemu jak on, to straszny i ciężki grzech! Będziesz musiał modlić się dniami i nocami, by choć trochę zmyć go ze swojej nieśmiertelnej duszy. Bóg mi świadkiem, mogłem po prostu oddać mu wszystko, co miałem, i odszedłby... Ale teraz... teraz jego krew jest na twoich rękach, i tylko niebiosa zdecydują, czy zostaniesz przebaczony!";
			link.l1 = "Może tak chciał Pan. Ale nie roztrząsajmy tego. Lepiej wydostańmy się z tej jaskini.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Kapitánie, pozwól mi raz jeszcze podziękować! Będę się modlić o twoje zdrowie i pomyślność, "+pchar.name+". Proszę, przyjdź do naszego kościoła – niech Pan obdarzy cię przebaczeniem wszystkich twoich grzechów i swoim błogosławieństwem.";
			link.l1 = "Może kiedyś wpadnę. I pamiętaj, Marisa, jeśli nie zobaczę tam twojej uśmiechniętej twarzy, bardzo się rozczaruję.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Jesteś dla mnie taki dobry. Naprawdę ucieszę się, gdy znów cię zobaczę w naszym mieście. Ale teraz wybacz, nie mogę się doczekać, by uporządkować swoje życie i podzielić się dobrymi wieściami z Dolores.";
			link.l1 = "Oczywiście, Marisa. Do widzenia. Dbaj o siebie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Kapitánie, pozwól mi raz jeszcze wyrazić moją bezgraniczną wdzięczność! Uczyniłeś dla mnie coś niemożliwego! Za twoją dobroć i szlachetność chcę ci opowiedzieć, jak udało mi się unikać najemników przez ostatnie dwa lata. Może ta wiedza kiedyś i tobie się przyda.";
			link.l1 = "Dziękuję, señora. W takich sprawach wiedza jest warta tyle co złoto. Słucham.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "W ten sposób spędziłem te dwa lata. W świecie, gdzie siła znaczy tak wiele, umiejętność pozostania w cieniu otwiera możliwości, o których inni mogą tylko marzyć.";
			link.l1 = "Dziękuję, że podzieliłaś się swoją historią, Marisa. Przeszłaś naprawdę wiele, a twoje doświadczenie jest niezwykle cenne.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Będę naprawdę szczęśliwy, widząc cię ponownie w naszym mieście. Proszę, przyjdź do naszego kościoła—niech Pan obdarzy cię przebaczeniem wszystkich twoich grzechów i swoim błogosławieństwem.";
			link.l1 = "Może kiedyś wpadnę. I pamiętaj, Marisa, jeśli nie zobaczę tam twojej uśmiechniętej twarzy, będę bardzo rozczarowany.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ach, Kapitanie... Jesteś dla mnie taki dobry. Ale teraz, wybacz mi, nie mogę się doczekać, by uporządkować swoje życie i podzielić się dobrą nowiną z Dolores.";
			link.l1 = "Oczywiście, Marisa. Do widzenia. Dbaj o siebie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Słyszeliście? Kapitan "+GetFullName(pchar)+" z własnej kieszeni spłacił długi wdowy po Calderze! Niewielu byłoby gotowych poświęcić taką sumę dla obcej osoby. W Hiszpanii wciąż żyją prawdziwi caballeros!", "Serce się raduje, gdy widzi się, że w Hiszpanii żyją nie tylko godni caballeros, ale i kobiety, których odwaga i honor dorównują męskim.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("Mówią, że jakiś kapitan oddał własne pieniądze, by uwolnić wdowę po Calderze od długów jej zmarłego męża! Nie każdy zdobyłby się na taki szlachetny czyn. Prawdziwy człowiek honoru, prawda?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitánie, to prawdziwa przyjemność znów cię widzieć! Miałam nadzieję, że zajrzysz. Może dziś znajdziesz chwilę, by zostać dłużej i pomodlić się?";
						link.l1 = "Cieszę się"+GetSexPhrase("","")+" spotkanie, Marisa. Ale obawiam się, że nie mogę sobie pozwolić na dłuższy postój. Pamiętam o swoim obowiązku wobec Pana, ale modlitwa będzie musiała poczekać.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Kapitánie, znowu pan! Zawsze miło pana widzieć. Wygląda na to, że Pan nie pozwoli panu zapomnieć drogi do kościoła... Może jednak znajdzie pan chwilę na modlitwę?";
						link.l1 = "Marisa, dobrze cię widzieć. Ale nie mogę zostać – moje sprawy nie mogą czekać. Wierzę, że Pan zna moje myśli nawet bez modlitwy.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitanie, cóż za radość znów cię widzieć! Każdego dnia dziękuję Bogu za twoją dobroć. Świat stał się jaśniejszy, gdy mi pomogłeś.";
						link.l1 = "Cieszę się"+GetSexPhrase("","")+"   Miło cię widzieć w dobrym zdrowiu, Marisa. Mam nadzieję, że życie nie przyniosło ci więcej przykrych niespodzianek. Wyglądasz na dużo szczęśliwszą.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Kapitanie, tak się cieszę, że pana widzę! Za każdym razem, gdy przychodzi pan do naszego kościoła, ogarnia mnie spokój. Przynosi pan ze sobą światło dobrych uczynków.";
						link.l1 = "I ja się cieszę"+GetSexPhrase("","")+" Miło cię widzieć, Marisa. Przywykłaś już do spokojnego życia, czy wciąż czasem oglądasz się za siebie?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", gdyby wszyscy wciąż odkładali modlitwę, świat już dawno pogrążyłby się w ciemności. Odłóż na chwilę swoje troski – skrucha daje siłę, by iść dalej.";
			link.l1 = "Rozumiem, Marisa, ale naprawdę nie mogę teraz. Wierzę, że Pan mnie usłyszy nawet bez słów.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", zmieniłeś zdanie? Grzechy nie znikają same z siebie, a im dłużej zwlekasz, tym stają się cięższe.";
			link.l1 = "Niestety, muszę już iść. Ale następnym razem obiecuję, że się pomodlę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "Ale wiara to nie tylko wiedza, ale też działanie! Nie możesz w nieskończoność odkładać drogi do odkupienia. Czy nie chcesz poczuć ulgi, zrzucając z siebie ciężar grzechu?";
			link.l1 = "Może, ale nie teraz. Niech Pan mnie wysłucha, nawet jeśli modlitwa musi poczekać.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Kapitánie, czy nie sądzisz, że odkładanie pokuty to już samo w sobie grzech? Pewnego dnia może być za późno.";
			link.l1 = "Może, ale obawiam się, że dziś nie mam czasu. Wiara jest przy mnie, a Pan widzi moją skruchę nawet bez modlitwy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Tak, dzięki tobie znów mogę swobodnie oddychać. Niech Pan czuwa nad tobą i twoją podróżą. Może pomodlisz się ze mną?";
			link.l1 = "Wierzę, że twoje modlitwy są już wystarczająco silne. Najważniejsze jest to, że teraz otacza cię tylko dobroć.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", zmieniłeś jednak zdanie? Pomodlimy się do naszego Stwórcy?";
			link.l1 = "Niestety, Marisa, muszę już iść, mam jeszcze sprawy do załatwienia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Staram się patrzeć tylko przed siebie. Teraz mam przed sobą przyszłość, i to wszystko dzięki tobie. Może powinniśmy razem podziękować za to Panu?";
			link.l1 = "Myślę, że poradzisz sobie lepiej ode mnie. Najważniejsze, żeby twoje modlitwy przynosiły ci spokój.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", może uda mi się namówić cię na choćby jedną modlitwę?";
			link.l1 = "Wybacz mi, Mariso, ale niestety nie mam teraz czasu. Pomódl się za mnie, proszę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Kapitanie, to nie tutaj. Jaskinia, której szukamy, jest przy Mosquitos Bay.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}