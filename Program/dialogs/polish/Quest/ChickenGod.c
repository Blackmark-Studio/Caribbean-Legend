int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Nie powinieneś tego widzieć.";
			link.l1 = "Czas złożyć raport o błędzie.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Uh-oh! Ta'kahi, młody człowieku. Nie chcę być niegrzeczny, ale jak tu wszedłeś? Zdecydowanie doradziłem Madame, aby zamknęła przybytek na czas mojego pobytu.";
			link.l1 = "Och, rzeczywiście. Jak cię tu wpuścili? Dlaczego ten burdel nie został jeszcze spalony przez rozwścieczonych bogobojnych?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Złote dublony otwierają wszystkie ścieżki i sprawiają, że biali ludzie są szczęśliwsi. Nie wiedziałbyś?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" Wyczuwam niemal zwietrzały zapach Wersalu, gdzie wpuszczono cię z takim skrzypieniem.";
			}
			link.l1 = "Nie mów do mnie w ten sposób, czerwony pysku. To prawda, że jestem tu nowy, chociaż nie wiem, jak się o tym dowiedziałeś. Mógłbym cię zastrzelić dokładnie tam, gdzie stoisz, i zdobyć jakąkolwiek dziewczynę na noc, żeby zrekompensować sobie niedogodności.";
			link.l1.go = "native_var1";
			link.l2 = "Nie wiem, kto ci naopowiadał te bzdury, ale muszę przyznać, że gadasz całkiem gładko. Pierwszy raz widzę tak wykształconego tubylca.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+"Wersal, do diabła!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "Nie, Kapitanie, nic nie wiesz. Jestem tu całkowicie bezpieczny... na razie. Jednakże, skoro tak szybko się zaprzyjaźniliśmy, spróbujmy jeszcze raz. Napitek?";
			link.l1 = "Mogę to zrobić, zdecydowanie wzbudziłeś moje zainteresowanie.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Brawo! Widzę, że jesteśmy już na ty i wymieniamy się docinkami. Teraz proponuję, byśmy wypili za pokój i porozmawiali o interesach.";
			link.l1 = "Mogę to zrobić, zdecydowanie wzbudziłeś moje zainteresowanie.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Zważywszy na przeznaczenie tego miejsca, wasz komentarz, Kapitanie, mocno mnie niepokoi! Utknąłem tu już prawie miesiąc. Próbowałem wszystkiego, co przyszło mi do głowy, i jestem gotów wspiąć się na ścianę z nudów i bezsensu.";
			link.l1 = "Odejdź zatem. Odwiedź kościół dla odmiany... do którego cię nie wpuszczą.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "To nie takie proste, ponieważ jestem zobowiązany spędzić kolejne dwadzieścia cztery godziny w tym burdelu, zgodnie z moim... kontraktem.";
			link.l1 = "Brzmi okropnie, oczywiście, ale nie dostaniesz ode mnie współczucia. Wynajem ekskluzywnego domu publicznego na miesiąc to spełnienie marzeń!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Obawiaj się swoich pragnień, Kapitanie. Nie wiem, jak się tu dostałeś, bo miałem spędzić ten miesiąc samotnie. Samotnie z Indianką i winem, ale do trzeciego dnia mogłem tylko z winem. A dziś nadszedł dzień, kiedy i tego miałem dość.";
			link.l1 = "I czego ode mnie chcesz? Żebyś mógł się podzielić dziewczętami i winem?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Może, ale proponuję najpierw zagrać w hazard! Tysiąc srebra za kartę! A tak przy okazji, nazywam się Agueybana.";
			link.l1 = "Moje to "+GetFullName(pchar)+" Pewnie, zagrajmy.";
			link.l1.go = "native_accept";
			link.l2 = "Moje to "+GetFullName(pchar)+" Tysiąc pesos? Nieźle. Zastanowię się nad tym, ale nic nie obiecuję.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Zmieniłeś zdanie, kapitanie? Ruszamy?";
			link.l1 = "Oczywiście, czemu do cholery nie.";
			link.l1.go = "native_accept";
			link.l2 = "Jeszcze nie.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Dzięki za grę, kapitanie. Myślałem, że poczuję się lepiej, ale tak się nie stało. Proszę, zostaw mnie w spokoju - jakoś poradzę sobie jeszcze jeden dzień na własną rękę. Cholera, ten drań!";
			link.l1 = "To wszystko? Przyznaję, że moje rozczarowanie jest większe niż gorycz utraty całej masy pieniędzy.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Nie powinno cię tu nawet być, kapitanie. Ale jeśli pragniesz dowiedzieć się, o co chodziło... poszukaj starożytnej świątyni na kontynencie. I przynieś dużo tuunich kaane'. Proszę, weź jedno.";
			link.l1 = "Kamień żmii? Kamień z dziurą z pewnością pasuje do tego miejsca. Dzięki, Agueybana";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Żegnaj, kapitanie.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Uh-oh! Dziękuję, kapitanie! Szkoda tych pieniędzy, ale przynajmniej znów poczułem smak życia!";
			link.l1 = "Tak, to pierwszy raz, kiedy widziałem, żeby ktoś był tak podekscytowany trasą jak ta. Skąd w ogóle masz te wszystkie pieniądze?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Niegrzeczne pytanie, którego nigdy nie zadałbyś równemu sobie, kapitanie! Ale noc jeszcze młoda, a ja mam jeszcze sporo monet. Co powiesz na rewanż?";
			link.l1 = "Do diabła, czemu nie? Zróbmy jeszcze jeden!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Proponuję tym razem zagrać w kości i nieco podnieść stawkę. Mam też historię do opowiedzenia, więc wynajmij pokój na górze dla nas obu. Za dużo tu uszu! Byłbym wdzięczny, gdybyś poszedł do Madame i zapłacił za pokój. Niestety, mój kredyt cię nie obejmuje.";
			link.l1 = "Wynająć pokój? Dla dwóch? Tutaj? Pierdol się, Agueybana! Wynoszę się stąd!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "O, do diabła. Ta historia zakończy się albo jako dobra anegdota, albo jako bardzo kosztowna rzeźnia. Mój miecz zostaje ze mną, więc żadnych sztuczek, ha-ha! Poczekaj tutaj, ja to załatwię.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "Więc?";
			link.l1 = "Mam szczerą nadzieję, że wezwałeś mnie tutaj tylko na trunki i hazard.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Nie martw się, kapitanie, nie interesują mnie takie bzdury! Chociaż, gdybyś pojawił się tutaj pierwszego dnia... ha ha! Zaczynamy?";
			link.l1 = "Fortuna sprzyja odważnym!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "O rany! To jest dobre! Gratulacje z powodu waszego zwycięstwa, Kapitanie.";
			link.l1 = "Nie przesadzaj. Czas, abyś mnie oświecił, co do cholery się tu dzieje?";
			link.l1.go = "native_dice_story";
			link.l2 = "Jesteś dziwny, Agueybana. Teraz, jeśli nie opuszczę tego miejsca natychmiast, moja reputacja jako szlachcica i mężczyzny zostanie nieodwracalnie zniszczona. Daj mi moje srebro i rozstańmy się.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Co za szkoda, miałem nadzieję zakończyć dzień w inny sposób...";
			link.l1 = "To pierwszy raz, kiedy widzę, żeby ktoś był tak zirytowany wygraną w tę plebejską grę. Czy możesz mi wreszcie wyjaśnić, co tu się do diabła dzieje?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Pierdole cię, Agueybana! Mam tego dosyć!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "Ile mogę, kapitanie. Nie jestem pewien, czy mogę, ale mimo to rozjaśniłeś moje ostatnie dni... W tym burdelu, mam na myśli.";
			link.l1 = "A o co tu chodziło?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Nieważne... Posłuchaj, białasie! Ja jestem wielkim wodzem ludu Taino, Agueybana. Czasami śnię, że urodziłem się sto lat wcześniej i przegnałem hiszpańskich najeźdźców z moich wysp! Ale zamiast tego sprzedałem trzy tysiące moich współplemieńców do kopalń za dziesięć dukatów za głowę.";
			link.l1 = "Warta biografia. Nagle mam ochotę cię zastrzelić, Agueybana, i zostawić, byś gnił w tej cuchnącej winem norze.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Cokolwiek, kapitanie. Zawsze chciałem być jak ty.";
			link.l1 = "Jak ja?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "Widziałem wasze statki - cuda ludzkiego geniuszu - i chciałem mieć jeden dla siebie. Widziałem wasze kobiety w obcisłych gorsetach i marzyłem, by zdjąć jeden dla siebie. Obserwowałem nawet najgorszych z waszych komendantów, dzierżących władzę, o jakiej nie śniło się żadnemu z naszych przywódców. Słyszałem opowieści o Europie i wielkich kamiennych domach, gdzie ludzie żyją, a nie tylko przetrwają. I miałem to wszystko! Co więcej, byłem nawet w Europie, i to wszystko w ciągu ostatniego roku!";
			link.l1 = "Zbyt wiele wina, szefie. Jedynymi biletami do Europy dla ciebie byłyby kajdany, ku radości Watykanu i ulicznych artystów. To, o czym mówisz, jest po prostu niemożliwe w świecie, w którym żyjemy.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "To jest świat, w którym żyjemy, kapitanie. Już mi wyjaśniono, że nasz świat jest zły, wyimaginowany, i wszystko jest możliwe.";
			link.l1 = "A kto ci to powiedział, mądrala? Najwyraźniej nie wpuszczają cię tylko do burdeli, ale i do przytułków!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Teraz dochodzimy do sedna mojej opowieści. Wiesz, jak tutaj wszystko działa, prawda? Hiszpanie i Anglicy płacą za naszych jeńców wojennych bronią, narzędziami i prochem strzelniczym. Ja zapłaciłem za moich współplemieńców waszymi pieniędzmi. Jak myślisz, dlaczego tak jest?";
			link.l1 = "Czuję, że zaraz mnie oświecisz.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Tylko bogowie mogą spełnić nasze najgłębsze i najbardziej haniebne pragnienia. Jeśli nie możesz żyć tak, jak chcesz, poproś ich, by ingerowali w los. Tylko oni mogą spełnić nasze najgłębsze i najbardziej haniebne pragnienia. To jest droga. Ale oto problem: prawie wszyscy nasi bogowie już nie żyją, a nawet gdyby żyli, nigdy nie interesowali się złotem. Na szczęście natura nie znosi próżni, i nowy bóg pojawił się w jednej ze starych piramid. Nie obchodzi go, kim jesteś: tubylcem czy Europejczykiem, łotrem czy bohaterem - po prostu zapłać, a dostaniesz to, o co prosiłeś! Wszystkie plemiona to wiedzą, a niektórzy z twoich ludzi również. Zapłaciłem cenę w złocie i żyłem jak jeden z was. Jutro minie rok.";
			link.l1 = "Jaki bóg? Do Europy i z powrotem w rok? A największym osiągnięciem tej podróży był jakiś marny burdel na Karaibach? Cóż, do diabła. Brzmi jak opowieść pijaka, i jako taką ją kupię. Napijmy się i kontynuuj swoją opowieść.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Wszystko, co ci powiedziałem, to prawda. Nie ma już nic do opowiedzenia.";
			link.l1 = "Nie żyłeś wystarczająco długo w naszym świecie, Agueybana. Każda opowieść inspirowana alkoholem, zwłaszcza opowiedziana po pijaku w burdelu, musi kończyć się morałem. Zdecydowanie powinniśmy filozofować, zanim należycie zakończymy nasz salon.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "Jak zazwyczaj się kończą?";
			link.l1 = "Nie wiesz? To zależy od płci uczestnika oczywiście! Z mężczyznami walcz na pięści, kobiety zabieraj do łóżka. Czasem moda każe robić odwrotnie. Jaka więc jest morał twojej bajki? Pieniądze szczęścia nie dają? Nudne!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "To nie jest morał mojej bajki, jak to ująłeś. Ale skoro już zacząłeś, czuję potrzebę, by powiedzieć, że nie zgadzam się z twoim punktem widzenia. Wręcz przeciwnie, wierzę, że pieniądze kupują szczęście i czynią ludzi lepszymi.";
			link.l1 = "Bzdura! Wydajesz się teraz sobie przeczyć. Zgromadziłeś znaczną fortunę poprzez handel własnym ludem. Czy przypominasz sobie całkowitą sumę, którą zarobiłeś? Prawie trzydzieści tysięcy złotych monet? Zastanów się chwilę, ale dla mnie jest jasne, że pieniądze nie dały ci szczęścia. Kupiły ci jednak ten ładny apartament.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Dobrze, dostosuję mój początkowy punkt: pieniądze czynią życie i ludzi lepszymi.";
			link.l1 = "To lepiej, ale dlaczego uważasz, że to czyni ludzi lepszymi? Więc teraz jesteś wzorem cnót? A co z tymi, którzy nie mają dużo pieniędzy? Czy zamierzamy nazywać ich złymi ludźmi?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Wiesz, kapitanie, naprawdę doceniam tę rozmowę. Pozwól, że się poprawię: pieniądze czynią życie i ludzi lepszymi, ale tylko tych, którzy już posiadają iskrę cnoty.";
			link.l1 = "Słuchaj, słuchaj! A więc, brak iskry dla ciebie, co?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "Nie. Byłem wodzem mojego ludu i, w przeciwieństwie do pieniędzy, władza zdecydowanie psuje ludzi. Wiesz co, kapitanie? Patrzę na ciebie teraz i zdaję sobie sprawę, że pewnego dnia staniesz przed tym samym dylematem.";
			link.l1 = "Czy twój bożek obdarzył cię także darem jasnowidzenia? W takim razie "+GetSexPhrase("powinieneś","powinnaś")+" udać się do Santiago, słyszał"+GetSexPhrase("em","am")+", że tam szczególnie interesują się wszelkiego rodzaju mediami i wróżbitami.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Zakończmy nasz... ekhem, salon bez bójek na pięści i bez pościeli, proszę. Nie udało mi się wymyślić morału dla mojej opowieści, więc zamiast tego chciałbym zaproponować toast.";
			link.l1 = "Całkiem się pogubiłeś, wodzu. Ale w jednym masz rację. Lepiej się napijmy!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Oby to, czego pragniemy, zawsze odpowiadało temu, czego potrzebujemy. Dziękuję, Kapitanie, to odpowiednie zakończenie... naszego wieczoru. Jeśli pewnego dnia zechcesz sprawdzić prawdę mojej przypowieści, udaj się na kontynent i znajdź tam starożytną świątynię. Zabierz ze sobą sto trzynaście tuunich kaane'. Mam dziewięćdziesiąt dziewięć - weź je i żegnaj!";
			link.l1 = "Sterta kamieni z dziurami? Pasuje do tego miejsca. Dziękuję za wieczór, Agueybana. Zobaczymy się ponownie?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "Nie, nie zrobisz tego. Żegnaj, kapitanie.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Rozumiem, kapitanie. Na dobre czy na złe, dam ci wskazówkę na temat skarbu. W końcu rozjaśniłeś moje ostatnie dni... W tym burdelu, mam na myśli. Szukaj starożytnej świątyni na wielkiej ziemi i przynieś stos tuunich kaane'. Tutaj, weź jeden.";
			link.l1 = "Kamień z dziurą? Jakże urocze i kamień z dziurą z pewnością pasuje do tego miejsca. Mam dość twojego traktowania!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Rozumiem, że jesteś zdenerwowany, kapitanie. Na dobre czy na złe, dam ci wskazówkę dotyczącą skarbu. W końcu rozświetliłeś moje ostatnie dni... W tym burdelu, mam na myśli. Poszukaj starożytnej świątyni na wielkiej ziemi i przynieś stos tuunich kaane'. Proszę, weź jeden.";
			link.l1 = "Kamień addera? Jak uroczo, a kamień z dziurą zdecydowanie pasuje do tego miejsca. Mam dość twojego traktowania!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Żegnaj, kapitanie.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Jeszcze jeden? Na miłość boską, mam was wszystkich serdecznie dosyć!";
			link.l1 = "A-a-ach! Odejdź!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Eh? Tak, właśnie. Kłaniaj się przede mną, śmiertelniku! Oto moc mojej piramidy!";
			link.l1 = "(krzycząc desperacko)";
			link.l1.go = "joruba_2";
			link.l2 = "zabij potwora";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Właśnie tak. Witaj w mojej skromnej faktorii, kapitanie.";
			link.l1 = " K-kim jesteś?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Pochwalam cię za wytrwałość. Jaki jest twój następny ruch, kapitanie? Co sądzisz o zrobieniu jakiegoś handlu?";
			link.l1 = "C-czym jesteś?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Nie ma znaczenia, kim jestem, liczy się funkcja, którą pełnię. W tej chwili prowadzę interesy handlowe z mieszkańcami tej nory dla obopólnej korzyści.";
			link.l1 = "Szczurza nora? Masz na myśli tę świątynię?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Twoje pierwsze i ostatnie ostrzeżenie, kapitanie! Jednakże ta piramida jest rzeczywiście trochę ciasna, najwyraźniej już z niej wyrosłem.";
			link.l1 = "Powiedziałeś coś o handlu. O jakim rodzaju handlu mówisz?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "Daję to, czego ludzie najbardziej potrzebują.";
			link.l1 = "Spełniasz życzenia? Jak dżin z bajki? Dobry Boże, co tu się dzieje?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "Nie bądź śmieszny! Tylko pomagam ludziom zdobyć to, po co przyszli na ten świat, w najszybszy i najprzyjemniejszy sposób.";
			link.l1 = "Czy jesteś szamanem czy coś w tym rodzaju?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Spotkałeś Agueybanę, to powinno dać ci pewne pomysły.";
			link.l1 = "Czy ten biedny, zagubiony i pijany Indianin to twoja robota?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "To nie ja sprzedałem jego plemię za kilka tysięcy funtów złota, to nie ja wlewałem beczki alkoholu do jego gardła, i z pewnością nie zmusiłem go, by zebrał każdą chorobę, znaną i nieznaną, od setek dziwek. Poprosił mnie, bym uczynił go białym arystokratą, więc to zrobiłem. Tak jak jego przeznaczenie mi nakazało.";
			link.l1 = "Spełniasz życzenia? Jak dżin z baśni? Dobry Boże, co tu się dzieje?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Nie bądź absurdalny! Pomagam tylko ludziom zdobyć to, po co przyszli na ten świat, w najszybszy i najprzyjemniejszy sposób. Agueybana miał uratować swój lud spod jarzma europejskich najeźdźców, ale zamiast tego za bardzo ślinił się na gorset córki komendanta i postanowił zastawić swój własny\nOd tego czasu jedynym sensem jego życia było uświadomienie sobie głębi swojego błędu i szybkie rozpoczęcie od nowa. Rok w Europie, marskość i czas, który spędziliście razem w burdelu, musiały pomóc. Ale przyznam, miał wspaniałe wakacje, ha ha!";
			link.l1 = "Cirrho co? Jesteś szamanem czy coś?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Albo coś. Ale spodoba ci się moja oferta. I dla odmiany, będę naprawdę szczęśliwy, mogąc pomóc.";
			link.l1 = "Dobrze. Ile?";
			link.l1.go = "joruba_9A";
			link.l2 = "Czemu? Czy jestem wyjątkowy?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Nieźle, kapitanie. Albo jesteś sprytny, albo głupi jak osioł, ale twoje szanse właśnie trochę wzrosły. Cena nie będzie problemem.";
			link.l1 = "Potrzebujesz kogoś zabić? Ja się tym nie zajmuję.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Bo twój cel w tym życiu to robić dziury w dobrym przyjacielu moim, ha ha!";
			link.l1 = "Czy potrzebujesz kogoś zabić? Ja tego nie robię.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Po pierwsze, ty. Po drugie, przeprowadzimy cztery główne transakcje i cztery mniejsze. Każda z nich uczyni cię znacznie silniejszym i zwiększy twoje szanse w tym okrutnym i dziwnym świecie. Jeśli zakończysz każdą transakcję, gwarantuję, że pewnego dnia będziesz mógł wyjść i walczyć z bogami na równych warunkach, nie wspominając o zwykłych śmiertelnikach.";
			link.l1 = "Brzmi zabawnie. Opowiedz mi o tym.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Sprytny wybór! Zwykle moje przemowy kończą się tym, że ludzie są wynoszeni do Blueweld z podejrzeniem zawału serca, ale trzymasz się całkiem dobrze. Oto lista zadań: drobne zlecenia o charakterze handlowym, które oczekuję, że wykonasz. Bez terminów, hehe.";
			link.l1 = "Ciekawe. Przeczytam listę później. Coś jeszcze?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Tak, pierwsza duża transakcja. Dwa tysiące dublonów to cena.";
			link.l1 = "Może się skuszę... Ale to dużo pieniędzy! Dlaczego potrzebujesz aż tyle? Czy mogę zapłacić w pesos?";
			link.l1.go = "joruba_13";
			link.l2 = "Czyś ty oszalał? Za takie pieniądze mogę kupić fregatę!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "Piramida wymaga naprawy - murarstwo czasami spada na głowy klientów i to niedobrze dla interesu. Moi ludzie naprawiają ją codziennie, ale nasza organizacja potrzebuje pilnego zastrzyku pieniędzy z zewnątrz, aby na stałe rozwiązać problem. Co do pesos - nie przepadam za nimi, ponieważ ich kurs wymiany jest raczej niestabilny.";
			link.l1 = "Jesteś niesprawiedliwy wobec uczciwych pesos... Chwileczkę, nie jesteś tu sam?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Nie, jestem fasadą poważnej organizacji. Więc, wchodzisz?";
			link.l1 = "Pomyślę o tym, ale najpierw chciałbym wiedzieć, co dostaję za taką pokaźną sumę.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Po co psuć niespodziankę? Poza tym, potraktuj te pieniądze jak podatek. Twoim najcenniejszym nabytkiem będzie odblokowanie kolejnych umów. Nagrody będą boskie. Unikalne też, pamiętaj, bo nigdzie indziej ich nie znajdziesz!";
			link.l1 = "Świetnie. Jak się nazywasz?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba, Wspaniała. Jeszcze jedna rzecz, "+pchar.name+", wejście do piramidy jest dozwolone tylko raz dziennie. Nie opóźniaj innych klientów i nie zawracaj mi głowy bez powodu.";
			link.l1 = "Nie widzę, żeby kolejka się ustawiła... Żegnaj, wasza mość.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ahoy, kapitanie. Co masz dla mnie?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Następnym razem zatem.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Nieźle, dobrze spożytkuję to złoto. Proszę, mała błyskotka, którą niegdyś posiadał bardzo cnotliwy wódz Taino. Pomaga nosić stosy złota. Na pewno jemu pomogła, heh-heh...";
			link.l1 = "Dziękuję i mam nadzieję, że tego nie pożałuję. Jaki jest następny interes?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Chwileczkę. Dałem ci kupę złota, a w zamian dostałem bryłę gliny? No cóż, potrzebuję zwrotu pieniędzy!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "Eh? Aye, następny interes. To złoto powinno wystarczyć na teraz, więc czas pomyśleć o bardziej duchowych towarach. Muszę znaleźć sobie lekarstwo.";
			link.l1 = "Czemu, jesteś chory?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "Moja dusza jest. Widzisz, kapłani unikają mojej pokornej piramidy od tego incydentu z Inkwizycją, więc musimy polegać na bardziej tradycyjnych metodach. Potrzebuję, cóż, moja faktoria potrzebuje piętnastu roślin magarosa, by pozostać operacyjną.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Czy to zioło?";
			} else {
				link.l1 = "Wiem, co to jest, heh-heh.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Będę szczery - to rzadka roślina o wielkiej wartości. Zastanów się dobrze, czy naprawdę chcesz spędzić lata na jej zbieraniu po całym archipelagu?";
			link.l1 = "Żadnych obietnic, ale życzę ci zdrowia i mam nadzieję, że moja nagroda za zioło będzie tego warta.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "Tak jest, oficjalnie ogłaszam to moim dniem wolnym! Taka okazja to prawdziwy skarb. Oto ona!\nTo maczeta była raz o włos od rozbicia głowy temu imbecylowi Kanekowi! Dlatego jest mi bardzo droga i pokornie proszę, abyś dobrze się nią opiekował. Jest stara, ale wykonana niezwykle dobrze, takiej stali już się nie robi.";
			link.l1 = "Kanek? Kto to?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Och, wy dwaj się spotkacie. Teraz, mam nadzieję, że nie jesteś jednym z tych nadętych dupków, którzy gardzą pracą ręczną? Jeśli tak, to masz przechlapane, bo druga część nagrody to schematy amunicji z podwójnym ładunkiem.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "O, uwielbiam to. Ale co w nich wyjątkowego? Podwójny ładunek prochu to żadna nowość, więc wnioskuję, że oczywiście nie opuściłeś swojej piramidy od czasów tego muzealnego maczety.";
			} else {
				link.l1 = "To wszystko? Hej...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Nie bądź cwaniakiem i słuchaj! Każdy głupek może wrzucić dwie kupki prochu do beczki i ryzykować oślepieniem, poparzeniem twarzy lub złamanym nosem. Proponuję ci mały magiczny trik: sprawdź dokładnie jakość prochu, zmiel go na odpowiednią konsystencję, włóż kulę lub śrut i dopraw to posiekanym dubloonem. Huk rozerwie nawet kirys na strzępy!";
			link.l1 = "Strzelasz pieniędzmi, co? To do ciebie podobne.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Jesteś nie do zniesienia! Dobrze, weź ręczną moździerz i tuzin granatów do niego. Jeśli jesteś taki cholernie mądry, sam zdobędziesz schematy granatów w mgnieniu oka!";
			link.l1 = "Wielkie dzięki, mój panie. Co dalej?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Nie pokochasz tego. Potrzebuję statku... nie, potrzebuję tego statku. Wiesz, z historią za nią.";
			link.l1 = "Po co? Nawet nie jesteś kapitanem.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Nie twój interes! Lepiej skup się na swojej nagrodzie, bo mogę zażądać, żebyś wyczyścił tę piramidę od góry do dołu za to, a i tak będziesz mi winien!";
			link.l1 = "Ty na pewno nie jesteś kapitanem, w przeciwnym razie wiedziałbyś, że statek potrzebuje molo lub zatoki, aby zacumować. Jak do diabła oczekujesz, że wprowadzę statek do twojej piramidy?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Czy przypadkiem zauważyłeś olbrzymie jezioro za moją piramidą? Zgadza się. Po prostu zacumuj właściwy statek w pobliskiej eskadrze, a moi ludzie zajmą się resztą. Teraz wynoś się stąd, blokujesz kolejkę.";
			link.l1 = "Ależ oczywiście. Żegnaj!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Świetnie! Mam to!";
			link.l1 = "Przestań zgrywać mądralę i daj mi moją nagrodę!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "A co z pozostałymi dwoma? Nie mogłeś ich zatrzymać dla siebie? Heh-heh.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "A co z pozostałą dwójką? Nie mogłeś ich zachować dla siebie? Heh-heh.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "A co z pozostałymi dwoma? Nie mogłeś ich zachować dla siebie? Heh-heh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Cholera, jestem pod wrażeniem, że nie chciałeś zatrzymać jej dla siebie. To nazywam statkiem z historią! Cholera jasna, Williamie... Naprawdę chciałem, żebyś wrócił do domu i założył wielki bank, o którym zawsze marzyłeś.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Popatrz tylko na to! Jesteś hańbą dla swego stanowiska, "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince postanowił pozbyć się obciążających dowodów w mojej starej piramidzie? Popieram!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Powodzenia w wyjaśnianiu swoim przełożonym utraty okrętu flagowego, Admirale. Och, wybacz mi, generał-gubernatorze.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Jesteś przesądnym głupcem czy po prostu głupcem? Ona jest warta fortunę! Nie jestem pewien, czy to uczciwa wymiana, ale co tam.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Czy jesteś przesądnym głupcem, czy po prostu głupcem? Ona jest warta fortunę! Nie jestem pewien, czy to uczciwa wymiana, ale cóż.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Jesteś przesądnym głupcem czy po prostu głupcem? Ona jest warta fortunę! Nie jestem pewien, czy to uczciwy handel, ale mniejsza z tym.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "Dobra decyzja! Uwielbiam Kastylijczyków, wiesz. Może oddam ją im, gdy skończę.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "Zaiste, brak ci serca, Kapitanie. Ta łajba cuchnie zdradą. Wezmę ją.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Aye, ten statek może mieć swoją historię... ale czy nie było zbyt łatwo go zdobyć? Ach, dobrze. Twoja sprawa jest wyjątkowa, moja droga, więc ją przyjmę. Przynajmniej przywołuje wspomnienia z mojej młodości.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Aye, ten statek może mieć swoją historię... ale czy nie było zbyt łatwo go zdobyć? Cóż, do diabła. Dobrze, kapitanie, przymknę na to oko, skoro świetnie poradziłeś sobie z tymi zadaniami z mojej listy. Wezmę go. Przynajmniej przywołuje wspomnienia z mojej młodości.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "  A widzieliście księdza? No cóż, spotkacie go. I lepiej zaopatrzcie się w naboje do pistoletu z podwójnym ładunkiem. Jeśli to nie pomoże - spróbujcie drewnianego kołka.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "  A widzieliście księdza? No cóż, spotkacie go. I lepiej zaopatrzcie się w naboje do pistoletu z podwójnym ładunkiem. Jeśli to nie pomoże - spróbujcie drewnianego kołka.";
				break;
			}
		break;
		
		/*case "joruba_p3_HolyMercy":
			dialog.text = "I widzieliście księdza?";
			link.l1 = "Jaki ksiądz?";
			link.l1.go = "joruba_p3_HolyMercy_2";
		break;
		
		case "joruba_p3_HolyMercy_2":
			dialog.text = "Cóż, spotkasz go. I lepiej zaopatrz się w podwójne ładunki do pistoletu. Jeśli to nie pomoże - spróbuj drewnianego kołka.";
			link.l1 = "...";
			link.l1.go = "joruba_p3_1";
		break;*/
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Aye, ten statek może mieć swoją historię... ale czyż nie było zbyt łatwo go zdobyć? Nie ma mowy! Masz jeszcze mnóstwo niedokończonej roboty z listy. Gdy to zrobisz, porozmawiamy ponownie o tej ofierze.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Błogosławię cię, "+GetFullName(pchar)+"Niech morze będzie dla ciebie łaskawe. A teraz omówmy następną transakcję...";
			link.l1 = "Co? Nawet wiejscy idioci nie dają się nabrać na takie bzdury w naszych czasach rozsądku! Nie wrzuciłem centyma do twojej skrzynki charytatywnej, dałem ci pełnoprawny okręt wojenny!";
			link.l1.go = "joruba_insult";
			link.l2 = "Chwileczkę. Co dokładnie oznacza dla mnie twoje błogosławieństwo?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Każdy statek, którym dowodzisz, od teraz będzie miał wzmocniony kadłub, podczas gdy twoi wrogowie będą cierpieć odwrotnie. Ponadto, czas na morzu będzie płynął wolniej dla ciebie. A jeśli to ci nie wystarczy, by rzucić to całe gówno na kolana, lepiej idź do swojego tatusia i zażądaj zwrotu pieniędzy!";
			link.l1 = "Jeśli to nie zadziała, przysięgam, że wrócę tu dziś wieczorem i spalę twoją piramidę! Opowiedz mi o następnym interesie!";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Zasmakowało ci, co kapitanie? Niestety dla ciebie, mi również. Dlaczego myślisz, że wybrałem tę piramidę na moje biuro?";
			link.l1 = "Może dlatego, że polowanie na czarownice wciąż jest aktualne?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, nie, nie całkiem. Prowadzę tu swoje interesy, ponieważ najlepsze interesy wymagają krwi. Ta piramida wymaga krwi. Ja wymagam krwi. Tak było i tak będzie.";
			link.l1 = "Nie waż się o tym myśleć, potworze. Nie będę dostarczał ci ofiar do zabicia!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "Ile ich zabiłeś, co? Poczekaj, nawet powiem ci dokładną liczbę: osobiście zabiłeś "+(Statistic_AddValue(pchar,"Żołnierz_s",0)+Statistic_AddValue(pchar,"Obywatel",0)+Statistic_AddValue(pchar,"Wojownik_s",0)+Statistic_AddValue(pchar,"Żołnierz_g",0)+Statistic_AddValue(pchar,"Obywatel_g",0)+Statistic_AddValue(pchar,"Wojownik_g",0))+"Ludzie! Złożyliście górę trupów na ołtarzu waszej ambicji i żądzy bogactwa!";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" Dług twojego brata zabił już więcej ludzi niż przeciętna europejska wojna! ";
			}
			dialog.text = dialog.text+"Nie próbuj nawet moralizować tutaj ze mną, zwłaszcza że nie zamierzam cię oceniać. Sukces jednych zawsze będzie opłacony tragediami innych, a bogowie, och, bogowie, będą patrzeć i zbierać swoją część!";
			link.l1 = "Nie mogę ci teraz odpowiedzieć... Muszę stąd wyjść.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Pilna potrzeba oczyszczenia głowy? Dobrze, ale najpierw posłuchaj mnie. Dam ci moc i pełną kontrolę nad ciałem i umysłem, jeśli przyniesiesz mi człowieka o wielkiej wartości. Nie podrzędnego, nie bezimienną szarą myszkę z ulic ani szczura z cuchnących ładowni. Przynieś mi człowieka, który cię śledzi i odgrywa ważną rolę w twojej tragikomedii.";
			link.l1 = "Jeden z moich oficerów? Nie możesz niżej upaść, Aruba! Jeśli to się rozniesie...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Zajmę się dyskrecją, jak zawsze. A zanim znów zaczniesz narzekać, dam ci znać, że istnieje inna droga.";
			link.l1 = "Co to ma znaczyć? Że nie muszę ciągnąć swoich ludzi do ołtarza?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Nie, ale nie spodoba ci się alternatywa. Jeśli nie chcesz płacić krwią, możesz zapłacić złotem. Trzy tysiące dublonów i czyste sumienie. Pieniądze mogą to zrobić i więcej - uwielbiam to!";
			link.l1 = "Żegnaj, Aruba. Nie chcę już z tobą rozmawiać.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Wiesz, gdzie mnie znaleźć.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Zróbmy to szybko, zanim pojawi się Hiszpańska Inkwizycja. Sangre u oro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Złoto to jest. Oto twoje trzy tysiące, chociaż nie mogę sobie wyobrazić, jak można wydać tak ogromną sumę w tej dziczy.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Krew.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Nieważne.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "Już skończyłeś? Porozmawiajmy o mojej nagrodzie.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "Niech będzie. Powiedz imię.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand nie jest oficerem, lecz bezwzględnym najemnikiem, więc wybierz inną ofiarę.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Przyjmuję twój hołd. Nie musisz patrzeć.";
			link.l1 = "Nie, nie wiem. Wrócę po swoją nagrodę za godzinę.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Świetny wybór. Nienawidzę czyścić ołtarza z tej całej krwi, więc złoto jest lepsze. Weź tę miksturę - prezent od dobrego przyjaciela.";
			link.l1 = "Smak wcale nie jest zły...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Zakończyłeś? Porozmawiajmy o mojej nagrodzie.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Porozmawiaj ze mną, kiedy tylko zechcesz zmienić swój los.";
			link.l1 = "Ale co to dokładnie dla mnie znaczy?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Władza nad sobą! Spróbuj czasami, a pokochasz to. W międzyczasie pozwól, że opowiem Ci o następnej transakcji. Najważniejszej.";
			link.l1 = "Nie jestem pewien, czy to już warte!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Chodź, wygadaj się już.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Masz okazję nie tylko zmienić swój los, ale stanąć obok geniuszy i bogów naszych czasów. Aye, możesz teraz zmieniać swoje ciało i umysł, jak tylko chcesz, ale nigdy nie przeskoczysz ponad swoją głowę, bo zwykły człowiek nie może być we wszystkim dobry. To, co sugeruję, to że przełamiesz te granice.";
			link.l1 = "Co mnie to będzie kosztować? Więcej krwi? Złota?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Aye. Albo przyniesiesz mi dwadzieścia pięć tysięcy dublonów, albo jednego ze swoich towarzyszy. Gdy skończymy, nie będzie już żadnych transakcji.";
			link.l1 = "Zastanowię się nad tym.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Wiesz gdzie mnie znaleźć. I nie wahaj się odwiedzić mnie, kiedy tylko zechcesz zmienić swój los.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Jak sobie życzysz.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Po pierwsze, to moja żona, a nie panna młoda. Po drugie, masz problem z Kastylijczykami, nie ze mną. I wreszcie, już ją zabrałem i odprawiłem twoich ludzi. A jeśli chodzi o honorowe intencje... Spójrz na mnie, czyż nie jestem wzorem przyzwoitego dżentelmena? Tlazolteotl, błogosław mu, aby i on pewnego dnia poznał prawdziwą kobietę. Albo mężczyznę.";
			link.l1 = "Chrzanić cię, Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Nieźle, dziękuję. Szczerze mówiąc, naprawdę tego nie potrzebuję, ale może założę to w jakimś salonie czy coś. W imię Isztar błogosławię cię. Teraz idź i grzesz.";
			link.l1 = "Co za dziwne uczucie...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Wezmę ich. Co? Potrzebuję trupów w mojej załodze tak samo jak ty, z tą różnicą, że w przeciwieństwie do ciebie nie mogę chodzić po tawernach i rekrutować. Teraz, Bast, pobłogosław bohatera w jego przyszłych przedsięwzięciach.";
			link.l1 = "Co za dziwne uczucie...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Tak, będziemy musieli je znowu rozrzucić, bo ludzie ciągle je gubią, a my potrzebujemy klientów. Freya, chroń tego wspaniałego zbieracza kamieni.";
			link.l1 = "Co za dziwne uczucie...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Zróbmy to szybko, zanim pojawi się hiszpańska inkwizycja. Sangre u oro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Nie szkodzi.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Powiedz imię.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "To dość kuszące, ale tym razem zrobię wyjątek - nie przyjmę twej ofiary. Nie ujawnię tego twemu "+sTemp+", chociaż pewnie powinienem. Pamiętaj, że jesteś niczym bez niej. Teraz zjeżdżaj i nie zawracaj mi dziś głowy.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand nie jest oficerem, lecz bezwzględnym najemnikiem, więc wybierz inną ofiarę.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Niech będzie. Weź tę miksturę - komplement od dobrego przyjaciela.";
			link.l1 = "Smak wcale nie jest zły...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Do następnego razu, kapitanie.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Ahoy-hoy! Nareszcie, wszystko skończone!";
			link.l1 = "Co?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Zakończyliśmy tutaj, Kapitanie. Umowy są zawarte, wszyscy są zadowoleni, a na zwroty nie ma miejsca. Nasze biuro się zamyka i przenosi.";
			link.l1 = "Poczekaj chwilę, Aruba. Dałem ci mnóstwo złota, zapłaciłem krwią, przyprowadziłem kobiety i więźniów do tej diabelskiej kryjówki. Potrafię poradzić sobie z nadprzyrodzonymi wydarzeniami, które rzekomo mają miejsce na Karaibach. Ale nasze 'transakcje' z tobą przeczą wszelkiej logice. Proszę wyjaśnij.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "You know what? I'll tell you.\nI'm fed up with this world, and I want out. Every day, it's the same old routine: an ancient pyramid with a crumbling ceiling, those loathsome identical palm trees, and a never-ending stream of captains, each with their own ingenious ideas. Yes, I provide people with what they desire; it's my calling, and I take pride in it. But by the gods, how I detest all of you!";
			link.l1 = "Czy ktoś cię tu trzyma? Wyjście jest tuż tam, geniuszu!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Masz absolutną rację, nikt mnie tu nie trzyma. Już nie. I to wszystko dzięki tobie, przyjacielu.";
			link.l1 = "To nagła zmiana serca. Spodziewałem się opowieści, ale jak dotąd słyszałem tylko bezsensowne tyrady nikczemnego małego boga w zakurzonej piramidzie.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Cóż, każdy musi się czasem wyżyć, prawda? Naprawdę się cieszę, że tu przyszedłeś, bo dzięki tobie mogę w końcu opuścić ten świat. Złoto, załoga, sprzęt i statek, mój przyjacielu. Pamiętasz? Brzmi znajomo? To wszystko, czego potrzebowałem, a ty dostarczyłeś wszystko.";
			link.l1 = "Nie ma za co. Jednakże to nadal nie wyjaśnia twojego osobliwego sposobu mówienia i niemal boskich mocy. Jeśli jesteś taki wszechmocny, mógłbyś już dawno wyczarować sobie statek, załogę i złoto!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Co uczyniłem, jak widzisz. Każdy ma swoje metody.";
			link.l1 = "Ale jakim cudem? Kimże jesteś, dokładnie?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Cóż... to po prostu to, co robię. Do zobaczenia w nowym świecie, "+GetPersonaName()+". Naprawdę nowy następnym razem, mam nadzieję. Dziękuję i do widzenia.";
			link.l1 = "Nie, nie chcę cię już nigdy więcej widzieć.";
			link.l1.go = "exit";
			link.l2 = "W takim razie do zobaczenia, Aruba... to było ciekawe.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Wygląda na to, że wszystkie umowy są nieaktualne. Czas ruszać, kapitanie.";
			link.l1 = "Czas na twoje p...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "W imię Hiszpańskiej Inkwizycji, przedstaw się!";
			link.l1 = "Kapitan "+GetFullName(pchar)+". I to prawda, co mówią, nikt nie spodziewa się Hiszpańskiej Inkwizycji...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Ten żart zawsze trafia w sedno, mimo że doprowadził wielu niewinnych chrześcijan na stos.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Żartowałem, kapitanie. Ty żartowałeś, a ja żartowałem. Nazywam się Padre Emilio Bocanegra, a ci żołnierze Chrystusa to moi uzbrojeni strażnicy.";
			link.l1 = "Co mogę dla ciebie zrobić, ojcze?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Czy znasz pewnego seniora Arubę?";
			link.l1 = "Tak, do niedawna mieszkał w tej starej piramidzie.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "Co masz na myśli, mówiąc, że tam mieszkał? Czy można tam mieszkać? I dlaczego 'do niedawna'?";
			link.l1 = "Ten señor właśnie opuścił nas na okręcie kilka minut temu.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Skąd to wiesz? Najbliższa zatoka jest oddalona o kilka dni!";
			link.l1 = "To jezioro musi być większe, niż wygląda. Nie mam innego wytłumaczenia dla ciebie, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Dziwne rzeczy dzieją się na ziemiach Wicekrólestwa.";
			link.l1 = "To są angielskie ziemie, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Niech heretycy nadal tak myślą. Na pewno odzyskamy nasze. Wybacz mi, synu, że zadaję tyle pytań: Santiago polecił mi przeprowadzić oficjalne śledztwo w sprawie tej piramidy... i jej byłego mieszkańca.";
			link.l1 = "Co dokładnie się stało, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Ponieważ sprawa prawdopodobnie zostanie zamknięta, mogę zabawić cię małą opowieścią.\nPlotki o tym miejscu krążyły po całym Main od jakiegoś czasu. Otrzymaliśmy wiarygodne raporty, że kilka osób, które zostawiły znaczący ślad w historii regionu, regularnie odwiedzało to miejsce w przeszłości.\nJednak Santiago zaczął naprawdę zwracać uwagę na te plotki po incydencie w Panamie.\nPewien Indianin narobił wielkiego szumu w tym wspaniałym mieście i nawet wygłosił kilka kazań o dość filozoficznej naturze. Niestety, mieszkańcy Panamy wyciągnęli raczej powierzchowne wnioski i przekonali się, że ta piramida zawiera nieopisane skarby i spełnia wszelkie życzenia.\nHerezja najczystszej postaci, oczywiście... więc musieliśmy wszcząć postępowanie przeciwko niektórym mieszkańcom Panamy i temu Indianinowi, Aguebana.";
			link.l1 = "Dlaczego władze panamskie nie rozprawiły się z tym?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Jak zawsze w takich przypadkach, twierdzili, że zostali zaczarowani. Ta luka prawna mogłaby zostać zamknięta, gdybyśmy przesłuchali Aguebana, ale on nagle zmarł.";
			link.l1 = "Jak on zginął?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "Pijaństwo go zabiło. Jednak jego śmierć nie rozwiązała naszych problemów, bo herezja zakorzeniła się na całym archipelagu, a setki ludzi udały się na swego rodzaju pielgrzymkę do tej starożytnej świątyni.";
			link.l1 = "Jeszcze nigdy wcześniej nie widziałem tu tłumów ludzi... Więc co, zamierzaliście najechać Arubę i postawić go przed sądem?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Oczywiście, że nie, synu. Osąd Inkwizycji jest surowy, ale sprawiedliwy. Musi być dobry powód do procesu. Nie, zamierzałem tylko zebrać zeznania señor Aruby i dostarczyć je do Santiago.";
			link.l1 = "Cóż, to dla ciebie pech.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "Nie wiadomo, mój synu. To wola Boża.";
			link.l1 = "Żegnaj, ojcze.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
