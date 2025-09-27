// колдун ривадос - Чимисет
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
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Nie, nieważne.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Poczekaj! Zatrzymaj się... Błagam cię, wysłuchaj mnie, zanim popełnisz błąd.";
			link.l1 = "Słucham... Mam nadzieję, że masz rozsądny argument, by powstrzymać mnie od...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "Że chcesz mnie zabić, prawda? Słyszałem, jak rozmawiałeś z Chadem na górze, i nie winię cię - każdy prawdopodobnie zrobiłby to samo. Ale mylisz się, myśląc, że Chad pozwoli ci odejść po moim zabiciu.";
			link.l1 = "Hm... Interesujące, a dlaczego nie chce? Jedyne co wiem, to że będę musiał się nieźle napocić, żeby się stąd wydostać, chyba że po prostu cię zabiję.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "Nie będziesz miał żadnej przyszłości, jeśli mnie zabijesz. Posłuchaj, Narwale i Chad chcą się mnie pozbyć, ale boją się mnie na tyle, że sami tego nie zrobią - mój zabójca będzie przeklęty na zawsze. Więc chcą, żebyś to ty wykonał całą brudną robotę\nChad wie, że nie jesteś z Rivados, on cię oszukuje. Po tym, jak mnie zabijesz - zrobią z tobą to samo i użyją twojego ciała, by oszukać Rekina.";
			link.l1 = "Rekin? Steve Dodson? Czy on naprawdę tu jest? I wytłumacz mi wreszcie - kim do diabła są ci Rivados?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Heh, wygląda na to, że faktycznie tu nie mieszkasz... Ale to nie jest odpowiedni czas na opowieści. Musimy się ratować. Mam plan.";
			link.l1 = "Wiesz co, czarowniku, niedawno odbyłem podróż przez jakiś mistyczny portal i ledwo to przeżyłem, więc twoje klątwy mnie nie przerażają. Mam tego dość - czas cię wykończyć.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "Dobrze, ufam ci. Jaki jest plan?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "Tam jest skrzynia. Zawiera przyzwoitą broń i mikstury. Jest zamknięta, ale zamek jest stary i uszkodzony, więc znajdź łom, aby go złamać\nWeź wszystko ze skrzyni, uzbrój się i idź do schodów. To dobra pozycja obronna, będą zmuszeni walczyć z tobą jeden po drugim, tylko uważaj na muszkieterów\nMam nadzieję, że dobrze posługujesz się ostrzem, jestem zbyt stary, aby pomóc ci w walce. Jeśli uda ci się ich wszystkich zabić i przeżyć - gwarantuję ci ochronę Rivados, mojej rodziny...";
			link.l1 = "Dobrze. Módl się za mnie do swoich bogów - walka będzie ciężka. Ci ludzie na górze wyglądają naprawdę poważnie.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Nie trać czasu! Szybko wyłam zamek...";
			link.l1 = "Tak, tak, jestem w drodze.";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Dobra robota! Jesteś prawdziwym mistrzem szermierki. Jestem ci dłużny, nieznajomy. Powiedz mi, jak się nazywasz?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". A jak ci na imię?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Nazywam się Chimiset, jestem szamanem Rivados i doradcą naszego wodza - Czarnego Eddiego. Będzie zadowolony, że mnie uwolniłeś i ocaliłeś moje życie. Jesteś przyjacielem Chimiset, Czarnego Eddiego i wszystkich Rivados. Od teraz zawsze będziesz mile widzianym gościem na naszej Wyspie...";
			link.l1 = "Zaczekaj... Chimiset, na wypadek gdybyś jeszcze nie zrozumiał, jestem tutaj zaledwie od kilku godzin. Czy możesz mi wyjaśnić, gdzie się znajduję, kim są Rivados i gdzie mogę znaleźć Rekina Dodsona?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "To miejsce nazywa się Miastem Porzuconych Statków. Choć brzmi to bardziej jak drwina. To nie jest miasto. To miejsce to wyspa uformowana z setek martwych statków. Centrum nadaje się do zamieszkania. Zamieszkują je ludzie, którzy przetrwali niewytłumaczalne wraki statków spowodowane burzami, które ich tutaj przywiodły.\nRivados to klan, grupa ludzi, którzy żyją razem od dłuższego czasu. Są tu również trzy inne grupy: klan Narwali, nasi wrogowie, piraci Rekina Dodsona i zwykli ludzie. Rekin to w zasadzie głowa wyspy, nazywa siebie admirałem.\nPrzybył całkiem niedawno i brutalnie przejął władzę. Zajął 'San Augustine', gdzie przechowywaliśmy nasze zapasy żywności. Teraz musimy kupować prowiant po cenach ustalonych przez Rekina. Wygląda na to, że już byłeś w tym magazynie.\nChad Kapper był bosmanem Rekina i głową więzienia. Layton Dexter był pierwszym oficerem Rekina, on też ma pewne wpływy. Ta trójka i ich piraci są dominującą siłą na wyspie, mierzącą się zarówno z Rivados, jak i Narwalami.";
			link.l1 = " Dlaczego Chad Kapper chciał, żebym cię zabił?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad nawiązał kontakty z Narwalami, naszymi wrogami. Chciał zabić Rekina z ich pomocą i zająć jego miejsce. Narwale chowają urazę do admirała za śmierć Alana Milrowa, ich byłego przywódcy. Wierzą, że Rekin jest odpowiedzialny za jego śmierć, ale się mylą. Wiem, kto to zrobił. To Chad. Jestem jedynym świadkiem tej zbrodni\nDlatego Chad nie mógł pozwolić mi odejść wolno, ale bał się też mnie skrzywdzić. Piraci są nieustraszeni w bitwach, ale są bardzo przesądni. Więc chciał wykorzystać ciebie. Chad i Narwale mieli zabić Rekina i obwinić Rivados.";
			link.l1 = "Czyżby? Powiedz mi dlaczego...";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", mój przyjacielu, porozmawiajmy później. Musimy się pospieszyć, zanim pojawią się piraci Rekina. Przeszukaj ciało Chada i weź jego klucze. Ale najpierw sprawdź jego biurko, może tam być coś interesującego\nIdź do Rekina Dodsona, znajdziesz go na 'San Augustine', dużym statku, rozbitym w oddali od innych, prowadzi do niego most ze statku o nazwie 'Pluto'. Powiedz mu, że Chad knuł zdradę i że za wszystkim stoją Narwale, a my, Rivados, nie mamy z tym nic wspólnego.\nChętnie udzielę ci wszelkich informacji o tej wyspie, o moim klanie i innych, gdy tylko dotrzesz do naszej rezydencji w Protektorze. Wynośmy się stąd!";
			link.l1 = "Dobrze, Chimiset. Znajdę cię później w... 'Protector'. Wynośmy się stąd!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Jeszcze jedna rzecz. Nasze statki, w tym 'Protektor', są niedostępne dla obcych. Musisz być Rivados albo znać hasło, aby wejść. Powiedziałbym ci, ale zmienia się co tydzień, a jestem tu zbyt długo, więc nie znam aktualnego hasła\n Powinieneś najpierw odwiedzić 'San Augustine'. Powiem naszym ludziom, kim jesteś, gdy będziesz rozmawiał z Rekinem, będą cię oczekiwać. Ale nie idź teraz na 'Protektor', najpierw porozmawiaj z Rekinem i pozwól mi spotkać się z moimi ludźmi, w przeciwnym razie Rivados będą wrogo nastawieni do ciebie";
			link.l1 = "Rozumiem. Zmierzam do 'San Augustine'. Do zobaczenia!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("Ha, they say that you are a friend of clan Rivados. This is interesting. Congratulations...", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you have saved the Rivados wizard Chimiset from 'Tartarus'. Now you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So it was you who has set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I am not sure whether to congratulate you or to sympathize...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Czego chcesz ode mnie, nieznajomy?";
			link.l1 = "Twoje imię to Chimiset, prawda?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Tak, to ja. Masz do mnie interesy, czy po prostu chcesz porozmawiać?";
			link.l1 = "Mam pewne sprawy do omówienia. Przybyłem tu od Admirała, Rekina Dodsona. Przyniosłem rozkaz twojego uwolnienia, ale pod jednym warunkiem: musisz odpowiedzieć na kilka moich pytań.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Czy Dodson zdecydował się mnie uwolnić? Cieszę się, że to słyszę. Zadaj swoje pytania. Mam nadzieję, że nie ma w tym podstępu, w przeciwnym razie mój entuzjazm będzie na próżno.";
			link.l1 = "Bez sztuczek, potrzebuję tylko twojej pomocy. Powiedz mi, Chimiset, czy na tej wyspie jest dziwny kamienny idol? O północy zamienia się w złoto. Nie myśl, że jestem szalony...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Jeszcze jakieś pytania?";
			link.l1 = "Tak. Czy znasz człowieka zwanego Białym Chłopcem?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Biały chłopak? Oczywiście, że go znam. To przezwisko Olle Christiansena, naszego miejscowego głupka. Jest już dorosły i nie wygląda już jak chłopiec, choć jego umysł wciąż jest dziecinny.";
			link.l1 = "Czyżby? Powiedz mi, gdzie mogę go znaleźć?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Wszędzie w naszym mieście. Często można go znaleźć w sklepie, tawernie lub spacerującego po ulicach. Ma białe włosy, rozpoznasz go.";
			link.l1 = "Doskonale! Jeszcze jedno pytanie: czy spotkałeś tutaj człowieka o imieniu Nathaniel Hawk? Musiał się tu pojawić jakiś czas temu i może być poważnie chory.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Nie mogę ci w tym pomóc, obcy. Nie znam człowieka o takim imieniu. Mogę cię zapewnić, że nie ma go na statkach Rivados, nie powinno go być także w neutralnej strefie. Nie mogę tego samego powiedzieć o terytoriach Narwali, Rivados ich nie odwiedzają.";
			link.l1 = "Cóż, i tak dziękuję... Bardzo mi pomogłeś, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "To wszystko? Czy Rekin teraz mnie uwolni?";
			link.l1 = "Tak. Nie mam już więcej pytań do ciebie. Chad Kapper cię uwolni. Cóż, muszę iść...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Stój! Czekaj... Wróć.";
			link.l1 = "Masz mi coś jeszcze do powiedzenia?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Nie do końca... (ściszając głos) Widzę, że nie jesteś jednym z ludzi Kappera. Nie ufaj mu. To wstrętna kanalia. Niedawno z zimną krwią zabił nieuzbrojonego Alana Milrowa szpadą. Był przywódcą klanu Narwali. Nie spodziewałem się tego, Chad po prostu podszedł do jego celi i go wykonał. Słyszałem też plotki, że ludzie Admirała planują jego zamach. Powiedz o tym Rekinowi. I powiedz mu, że powiem więcej, gdy porozmawiamy twarzą w twarz.";
			link.l1 = "Hm. Dobrze, powiem o tym Dodsonowi. Do zobaczenia!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Idź do Rekina i powiedz mu wszystko, co ci powiedziałem. Eh, mam nadzieję, że wkrótce otworzą tę klatkę...";
			link.l1 = "Tak, tak. Już idę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "Oto jesteś, mój drogi przyjacielu. Jeszcze raz dziękuję za to, że mnie ocaliłeś i zaufałeś mi, zamiast Kapperowi. Dam ci te amulety w nagrodę. Jestem pewien, że uznasz je za przydatne.";
			link.l1 = "Dziękuję! Nie spodziewałem się tego...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "A teraz jestem gotów cię wysłuchać. Chciałeś mnie o coś zapytać, prawda?";
			link.l1 = "Masz rację, Chimiset. Potrzebuję twojej pomocy. Najpierw muszę wiedzieć, czy na tej wyspie znajduje się dziwny kamienny idol? O północy zamienia się w złoto. Nie myśl, że jestem szalony...";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "Widzę, co masz na myśli, przyjacielu. Widziałem ten posąg indyjskich bogów na własne oczy. Choć zamienia się w złoto tylko pod promieniami porannego słońca, a nie księżyca... wiele razy składaliśmy ofiarę nikczemnym Narwalom, a bóg pożerał ich wszystkich. Ale nie ma go już na Wyspie.";
			link.l1 = "Jak to nie?! Czy mówisz, że nagle zniknęło?!";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Nie do końca tak. Ta statua znajdowała się wewnątrz 'San Geronimo'. Ten statek zatonął ze statuą kilka lat temu.";
			link.l1 = "Co za pech! Wygląda na to, że teraz niemożliwe jest opuszczenie wyspy... A gdzie był ten statek?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Niedaleko terytoriów Narwali, w pobliżu wraków statku o nazwie 'Feniks'. W pogodny dzień możesz zobaczyć statek spoczywający na dnie morza.";
			link.l1 = "Ha! Więc leży na mieliźnie? Mogę do niego dopłynąć, więc...";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "You can't, my friend. First, it's too deep down there; second, there are many giant crabs. They will tear you apart before you get to the 'San Geronimo'.";
			link.l1 = "Hm. Dobrze, zastanowię się nad tym. Przynajmniej wiem, że posąg istnieje, a to jest najważniejsze.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Widzę, że masz więcej pytań. Śmiało pytaj, przyjacielu.";
			link.l1 = "Rekin Dodson poprosił mnie, abym znalazł wspólników Chada w zbrodni. Znalazłem list w skrzyni Chada. Jest tam coś o jakimś snajperze i broni. Wygląda na to, że chcą zabić Rekina z daleka. Czy masz coś na myśli?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "Hm. Zamierzają zastrzelić admirała? Muszę pomyśleć... Rzecz w tym, że admirał prawie nigdy nie opuszcza swojej rezydencji, a gdy to robi, jest chroniony przez pół tuzina piratów. Ale ma jeden nawyk, lubi spacerować po rufie późnymi wieczorami\nSą dwie pozycje dla snajpera, aby strzelić do rezydencji admirała - dziób 'Santa Florentina' i maszt 'Fury'. Ale snajper i tak nie zdoła zabić admirała z tych pozycji, musiałby być strzelcem o sokolim oku, aby oddać taki strzał. Ponadto potrzebowałby doskonałej strzelby. Powinieneś popytać na wyspie o ludzi, którzy mają dostęp do takiej broni palnej.";
			link.l1 = "Heh, wygląda na to, że masz rację, w liście jest coś o pistolecie... Czy widziałeś kogoś z takim pistoletem?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "Nie. Nigdy w życiu nie widziałem takiej broni. Spytaj ludzi, może ktoś ci powie.";
			link.l1 = "Dobrze... W każdym razie, twoje informacje są cenne, dziękuję! Cóż, teraz ostatnie pytanie, chociaż nie oczekuję, że odpowiesz... Czy słyszałeś o Białym Chłopcu?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Chłopiec biały? Jasne, znam go. To przezwisko Ollego Christiansena, naszego lokalnego idiotę. Jest już dorosły i nie wygląda już jak chłopiec, choć jego umysł wciąż jest dziecinny.";
			link.l1 = "Czyżby? Powiedz mi, gdzie mogę go znaleźć?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Gdziekolwiek w naszym mieście. Często można go znaleźć w sklepie, tawernie lub na ulicach. Ma białe włosy - na pewno go rozpoznasz.";
			link.l1 = "Świetnie! Dzięki, Chimiset, bardzo mi pomogłeś!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Zawsze chętnie pomogę! Przyjdź do mnie, jeśli będziesz miał więcej pytań.";
			link.l1 = "Jasne! Muszę już iść. Do zobaczenia!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "I oto mój drogi przyjaciel, któremu zawdzięczam moją wolność, a być może nawet życie. Dziękuję za pomoc moim braciom w ocaleniu mnie od tego plugawca Kappera. Dam ci te amulety w nagrodę. Jestem pewien, że okażą się przydatne.";
			link.l1 = "Dziękuję! Nie spodziewałem się tego...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "Masz jeszcze jakieś pytania, biały przyjacielu?";
			link.l1 = "Powiedz mi, Chimiset, czy znasz Białego Chłopca?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "O! Mój biały przyjacielu "+pchar.name+"! Nie utonąłeś? Duchy cię ocaliły, wiem to...";
				link.l1 = "Jestem zdrów i cały, Chimiset. Duchy? Może masz rację, to wszystko stało się przez Kukulkana...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Co cię tu sprowadza, mój dobry przyjacielu?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Powiedz mi, jak zginął przywódca Narwali. Tylko ty to widziałeś.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = " Wspomniałeś o krabach na dnie w pobliżu 'San Geronimo'. Czy możesz opisać te potwory?";
				link.l2.go = "crab";
			}
			link.l9 = "Nic specjalnego, Chimiset. Po prostu chciałem cię zobaczyć.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Historia śmierci Alana Milrowa zostanie tu napisana.";
			link.l1 = "Zgoda!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "Nikt nie wie, skąd się wzięły i dlaczego osiągnęły tak ogromne rozmiary. Niewiele wiemy o tych bestiach. Istnieją, wielu ludzi je widziało. Grupy ich można znaleźć wśród wraków statków na płytkich wodach. Czają się na dnie morza, polując na ryby i zjadając wszelkie śmieci, które wyrzucamy. Są prawdziwym zagrożeniem. Ich szczypce mogą zadać poważne rany, a ich szczęki uwalniają niebezpieczną truciznę, podobną do trucizny ryb morskich. Jeśli zatruty i nieleczony, człowiek spotka się z twórcą. Na szczęście toksynę można zneutralizować antidotum z lokalnych ziół. Był wśród nas łowca krabów. Kiedyś przynosił ich mięso, cholernie pyszne danie. Ale najważniejsze: często przynosił szczypce tych potworów i szczęki z trucizną. były głównym składnikiem niektórych moich mikstur. Szkoda, że minęło już dużo czasu, odkąd ktoś mi je przyniósł...";
			link.l1 = "A gdzie teraz jest ten łowca?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Zrozum wskazówkę. Musisz być gotów sam stać się ofiarą, polując na te bestie. Pewnego dnia po prostu nie wrócił. Dlatego ostrzegam cię, byś był ostrożny i czujny w pobliżu tych stworzeń.";
			link.l1 = "Widzę...";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
