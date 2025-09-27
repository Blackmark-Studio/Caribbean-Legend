// лидер клана ривадос - Чёрный Эдди
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
			dialog.text = "Co robisz na terytorium Rivados, białasie?";
			link.l1 = "Poznaję tylko miejscowych. Przepraszam, jeśli cię niepokoję.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "Cieszę się, że mogę powitać przyjaciela Rivados i dobrego człowieka! Chimiset opowiedział mi, co dla niego zrobiłeś. Wszyscy Rivados, w tym ja, jesteśmy ci teraz dłużni. Pozwól, że się przedstawię - Edward Black, znany także jako Czarny Eddie, szef gangu Rivados.";
			link.l1 = ""+GetFullName(pchar)+"Chociaż myślę, że Chimiset już ci o mnie opowiedział. Obiecał, że ci powie...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "A on to zrobił. Teraz możesz swobodnie odwiedzać nasze statki. Strażnicy cię nie zatrzymają i będziemy się cieszyć na twój widok. Uważaj na Narwale, na pewno już się dowiedzieli, że uratowałeś Chimiseta, a im się to nie spodoba, ponieważ jesteśmy wrogami.";
			link.l1 = "Rozważę to. Dzięki za ciepłe przyjęcie, Eddie! Teraz proszę, pozwól mi porozmawiać z Chimisetem.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Biały brat? Żywy? Cieszę się! Czyli Narwale kłamali, mówiąc wszystkim, że się utopiłeś...";
				link.l1 = "Również cieszę się, że cię widzę, Eddie. Pogłoski o mojej śmierci są mocno przesadzone.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Cieszę się, że cię widzę, "+pchar.name+"   Jakieś nowiny?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, czy znasz człowieka o imieniu Nathaniel Hawk? On musi tu być, o ile mi wiadomo.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Opowiedz mi więcej o gangu Rivados.";
				link.l2.go = "rivados";
			}
			link.l9 = "Nic specjalnego, naprawdę. Chciałem tylko powiedzieć cześć.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk? Nie, nie znam tego człowieka. Nie ma go ani na statkach Rivadów, ani na neutralnym terytorium. Nie mogę powiedzieć tego samego o gangu Narwali, nie odwiedzamy ich.";
			link.l1 = "Widzę...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "Gang Rivados został założony wiele lat temu. Był to pierwszy klan w tym Mieście Porzuconych Statków. Ponad pięćdziesiąt lat temu ekspedycja admirała Betancourta przybyła tutaj z Afryki Zachodniej z kilkoma dużymi statkami niewolniczymi. Ładownie Tartarusa były wypełnione setkami czarnych niewolników przeznaczonych na karaibskie plantacje. Wśród tych niewolników był człowiek o imieniu Pedro Rivados, kilku portugalskich księży nauczyło go czytać i pisać\nUdało mu się uwolnić kilkudziesięciu niewolników z kajdan i wzniecił bunt. Niestety, reszta niewolników nie dołączyła do niego. Bunt został stłumiony. Niewolnicy związali Rivadosa ręce i nogi i zostawili go w ładowni statku, by umarł z głodu i pragnienia. Kilka dni później pogoda się pogorszyła i eskadra Betancourta została porwana przez potężną burzę.\nKilka dni później, walcząc z pogodą, 'San Augustine' i 'Tartarus', jedyne dwa statki, które pozostały nienaruszone, utknęły pośrodku tej Wyspy. Wiele osób zginęło podczas tych wydarzeń, zarówno czarnych jak i białych, ale wielu więcej udało się przeżyć. Byli niewolnicy rozpoczęli nowe życie razem i nazwali się Rivados na cześć Pedra Rivadosa, wyzwoliciela.";
			link.l1 = "Bardzo interesująca opowieść... Dziękuję!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "Czego potrzebujesz na terytoriach Rivadów, białasie?";
			link.l1 = "Moje imię to "+GetFullName(pchar)+" i jestem tu z rozkazu admirała Dodsona. Muszę porozmawiać z Czarnym Eddiem. Z tego, co rozumiem, to ty.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Tak, jestem Edward Black, znany również jako Czarny Eddie. Powiedz mi, czego admirał ode mnie potrzebuje.";
			link.l1 = "Na 'Tartarusie' jest człowiek o imieniu Chimiset. Admirał jest gotów go uwolnić.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "To bardzo dobra wiadomość. Chimiset jest naszym duchowym przywódcą, a wszyscy Rivados za nim tęsknią. Ale rozumiem, że admirał chce coś w zamian za jego wolność, prawda?";
			link.l1 = "Niczego. On po prostu chce go uwolnić jako gest dobrej woli. Ale jest problem...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Śmiało, biały człowieku.";
			link.l1 = "Były bosman admirała, obecny strażnik Chad Kapper dołączył do Narwali, stał się zdrajcą i teraz jest poza kontrolą admirała. Wiemy, że Chad planuje zabić Chimiseta. Admirał nie chce, by tak się stało. Oferujemy ci wspólną operację, aby wyeliminować zdrajcę i uwolnić twojego człowieka.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "Twoje słowa brzmią nieco dziwnie, ale mów dalej. Czy Chimiset ma kłopoty?";
			link.l1 = "Tak. Chad planuje go zabić. Kapper zamierza użyć Narwali, aby przejąć kontrolę nad Miastem. Musimy działać szybko, jeśli chcemy ocalić Chimiseta, bo Chad niczego się teraz nie spodziewa. Admirał zabrał wszystkich strażników z 'Tartaru', przejście jest wolne. Oto klucz, który otwiera drzwi do więzienia. Weź go.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "Zbierz swoich ludzi, idź na Tartaros i uwolnij Chimiset. Wszystkie karty są w twoich rękach.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "To pachnie pułapką... A co jeśli to zasadzka? Co jeśli admirał zdecydował się zniszczyć Rivados? Dlaczego sam nie zajmie się Kapperem?";
			link.l1 = "Dodson powiedział, że zależy ci na życiu Chimiseta... Zrobił wystarczająco: oto klucz, a strażnicy zniknęli. Musisz tylko wejść do środka, rozprawić się z Chadem i uwolnić swojego człowieka. Masz moje słowo, że nie ma żadnej pułapki. Tak, i jeszcze jedna rzecz: admirał chce głowy Chada w zamian za życie i wolność Chimiseta. Czy mamy umowę?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "Życie Chimiseta jest dla Rivados bezcenne. Natychmiast przeniesiemy się na 'Tartarus'. Ale ty zostaniesz tutaj jako nasz zakładnik. Jeśli czeka na nas zasadzka, poznasz gniew Rivados!\nZikomo! Stój przy drzwiach i pilnuj naszego gościa. Nie wypuszczaj go. Osobiście poprowadzę atak na 'Tartarus'!";
			link.l1 = "Powodzenia, Eddie. I pamiętaj: potrzebuję głowy Chada Kappera!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset jest uwolniony! Nie kłamałeś, biały człowieku, jestem gotów nazwać cię przyjacielem Rivados!";
			link.l1 = "Cieszę się. Czy Chad Kapper nie żyje?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "Muszę prosić o twe przebaczenie, biały przyjacielu: zrobiłeś wszystko, co mogłeś dla nas, ale zawiedliśmy cię... Zawiodłem cię! Ten przeklęty Kapper uciekł. Były z nim dwa Narwale. Zabiliśmy ich, ale ten plugawy strażnik odpłynął przez dolne drzwi do terytoriów Narwali.";
			link.l1 = "Cholera... Nie wiedziałeś, że z 'Tartaru' są dwa wyjścia?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "Nie pomyśleliśmy o tym. Zaatakowaliśmy od głównego wejścia...";
			link.l1 = "Szkoda. Liczyłem na jego głowę. Zbyt źle. Teraz będzie nadal działał przeciwko nam.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "Przyznaję się do winy. Ale nie mogliśmy podążać za nim do wrogich statków. Zamiast głowy Chada, otrzymasz naszą przyjaźń i szacunek. Od teraz możesz swobodnie odwiedzać nasze terytorium. Mądrość Chimiset'a również ci się przyda, porozmawiaj z nim, jeśli czegoś potrzebujesz. Porozmawiaj z nim, jeśli potrzebujesz. Powiedz również admirałowi, że doceniam jego działanie.";
			link.l1 = "Dobrze.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Poczekaj! Straciliśmy Chada, ale znalazłem kilka dokumentów na jego biurku, które studiował, gdy przybyliśmy. Oto one. Może okażą się przydatne, biały bracie.";
			link.l1 = "Ha! Może... Chad pokłada wielką wiarę w papierze...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "Zawsze jesteś tu mile widzianym gościem, biały przyjacielu. Wszyscy Rivados zostaną o tym poinformowani. Powodzenia!";
			link.l1 = "Nawzajem, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
