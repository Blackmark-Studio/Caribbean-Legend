// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Oups... Witaj, wujku. Masz białą koralik? Daj mi białą koralik...";
			link.l1 = "Hm. Dzień dobry. Czy ty jesteś... Białym Chłopcem?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Pacior! Biały pacior dla białego chłopca! Masz biały pacior, wujku?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hm, nie mam koralików, ale mogę dać ci tę perłę. Jest biała i jest jak koralik. Czy to ci odpowiada?";
				link.l1.go = "store_2";
			}
			link.l2 = "Nie, nie mam żadnych paciorków ani białych, ani czerwonych. Nie jestem ani dziewczyną, ani Indianinem, żeby nosić paciorki. Powiedz mi...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Korale! Białe korale! Bez korali - nie ma rozmowy. Zły wujek... Daj mi korale!";
			link.l1 = "Cholera! Co za szalony gość! Wężowe Oko i Chimiset mieli rację - to słaba głowa... Jakiego paciorka on potrzebuje?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Daj paciorek, wujku. Dobry wujku... Biały paciorek!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Proszę, weź swój paciorek. Czy tego chcesz?";
				link.l1.go = "store_2";
			}
			link.l2 = "O, cholera...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Tak, tak! To jest! Wujek dał koralik! Dzięki, dobry człowieku! Teraz Ole ma jeszcze jeden koralik. Wkrótce zobaczę mamę...";
			link.l1 = "Cieszę się dla ciebie. Cóż, możemy teraz porozmawiać?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Owszem, dobry człowieku. Czy jesteś dobrym człowiekiem, wujku? Będziemy przyjaciółmi. Ole chętnie porozmawia. Jak się nazywasz?";
			link.l1 = " Nazywam się "+pchar.name+"  Ole, jeden człowiek opowiedział mi o tobie i już go tutaj nie ma. Powiedział, że mu pomogłeś i możesz pomóc także mnie.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "Wujek dał Ole koralik - to dobry wujek. Ole lubi pomagać dobrym ludziom. Niewielu jest dobrych ludzi - źli wujkowie są wszędzie. Pomogę ci, oczywiście. Lubię pomagać.";
			link.l1 = "Miło! No cóż, teraz jesteśmy przyjaciółmi. Ole, powiedz mi, czy pamiętasz człowieka o czerwonej skórze i wspaniałym kapeluszu z piórami? Powiedział mi, że dawno temu go uratowałeś.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "Pamiętam tego wujka. To dobry człowiek. Uratowałem go. Zabrałem go do posągu. A ostatnio uratowałem innego dobrego człowieka z ładowni z jedzeniem. Uratowałem go przed wujkami złego admirała. Oni by go zabili. Chciałem go również zabrać do posągu, ale odmówił. Całkowicie.";
			link.l1 = "Z ładowni? Heh, przypuszczam, że wiem, kogo masz na myśli... I znam tego wujka. Powiedz mi, Ole, kim jest ten człowiek, którego uratowałeś?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "Jego imię to wujek Nathan. Jest chory, bardzo-bardzo chory. Ledwo mógł chodzić, gdy Ole go znalazł.";
			link.l1 = "Oczywiście... To dziwne, że mógł to w ogóle zrobić.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "Nie, to nie jest dziwne. Znalazłem go i dałem trochę ognistego rumu. Wpłynąłem do środka dziury, bo tam na statku jest jedzenie. Źli ludzie zamykają drzwi, ale ja zawsze je otwieram. He-he-he... Głupi źli ludzie. Wabią kraby, wiem to. Źli ludzie\nDostałem się tam i znalazłem Nathana. Nie czuł się dobrze. Miałem ognisty rum - dałem mu go wypić, więc poczuł się lepiej. Potem dałem mu nalewkę, zawsze jedną noszę, na wypadek gdyby straszny krab ugryzł Olego. Dobry wujek Chimiset kazał mi to robić...";
			link.l1 = "Dałeś mu antidotum i rum? Heh, nie jesteś takim głupcem, jak wszyscy myślą. Dobra robota, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Podli wujkowie uważają Olego za głupca i drwią z niego: Ole głupiec... Ole nie jest głupcem, tylko musi zebrać wszystkie białe koraliki, bo inaczej matka go wygoni. Czy dasz mi później kolejny koralik?";
			link.l1 = "Hm... Pewnie, Ole, jesteśmy przyjaciółmi. Powiedz mi, jak zamierzałeś wysłać Jastrzębia... wujka Nathana do posągu. Wujek Chimiset powiedział mi, że zatonął z okrętem...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "Posąg jest na dnie. Ole wie. Ale nie jest głęboko i dobry wujek Henrik może tam wysłać wujka Nathana. Wujek Henrik wie, jak chodzić pod wodą. Ale jest tam dużo strasznych krabów. Ole się ich boi. One bolesnie gryzą.";
			link.l1 = "Wujek Henrik? Kim on jest?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Wujek Henrik mieszka wśród złych wujków Narwali. Wszyscy go znają. Potrafi chodzić pod wodą i uczy wujków Narwali, jak tam nurkować. Wujek Henrik jest dobry, dał białą koralikę Ole.";
			link.l1 = "A jak to się stało, że Narwale cię wpuścili? A może ich terytorium jest dla ciebie otwarte?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Tee-hee... Złe wujki nie pozwalają Ole wejść, ale Ole może wejść do każdej kajuty na ich statkach w nocy. Są duzi i hałaśliwi, ale Ole jest cichy i ostrożny. I spotkałem wujka Henrika, pływając wokół statku, z którego wujek Henrik skacze do wody. Wujek Henrik dał Ole białą koralik i teraz jesteśmy przyjaciółmi.";
			link.l1 = "Interesujące... Ja również chcę być przyjacielem wujka Henrika.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "Chcesz nurkować i iść do posągu? Tam jest, w wraku starego statku. Jest tam wiele dużych i przerażających krabów. Nie boisz się ich? Mogą ugryźć.";
			link.l1 = "Nie, nie boję się ich. Zabiłem już jednego, więc lepiej, żeby mnie się bali.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Oh, "+pchar.name+" jest bardzo odważny! W takim razie powinieneś iść do wujka Henrika, nauczy cię, jak chodzić po dnie i zabijesz tam każdego kraba. Znajdziesz tam także jeszcze jedną dużą koralik dla Ole. prawda?";
			link.l1 = "Oczywiście, zrobię to. Ale najpierw muszę znaleźć wujka Henrika.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "I dlaczego go szukasz? Mieszka na statku nazwanym 'San Gabriel', w warsztacie. Ale źli wujkowie Narwale mogą cię nie przyjąć.";
			link.l1 = "Sam rozprawię się z tymi nikczemnymi wujami. I ostatnie pytanie, gdzie teraz jest wuj Nathan? Szukałem go i to on jest powodem, dla którego tu jestem.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "Ukryłem wuja Natana w moim sanktuarium na 'Fernandzie'. Jest daleko stąd i nikt tam nie mieszka. Wszyscy myślą, że wkrótce zatonie, ale Ole wie, że jest inaczej. Uratowałem wuja Natana i zabrałem go tam\nJest nadal bardzo chory i cały czas pije ognisty rum. Ledwo chodzi i nie jest w stanie podnieść nic cięższego niż pięć funtów. Czuję się źle z powodu wuja Natana, przynoszę mu ognisty rum z kufrów i jedzenie z ładowni złych ludzi admirała. Także gotuję mu szczury, które łapię. Bardzo smaczne szczury!";
			link.l1 = "Szczury smakowite? Rozumiem. Czy Nathan jest na statku nazwanym... jak to powiedziałeś - 'Fernanda'? Nie znam jej...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Wujek "+pchar.name+", Właśnie ci powiedziałem, że to niedaleko stąd. Musisz dopłynąć, by się do niej dostać. Na jej rufie są drzwi, ale wujek Nathan ich nie otwiera. Ole mu powiedział, żeby nie. Ale jeśli jesteś przyjacielem wujka Nathana, powiem ci, jak je otworzyć. Zapukaj do drzwi tak: puk-puk... puk-puk. Wtedy je otworzy.";
			link.l1 = "Zapamiętam to. Dzięki, Ole! Naprawdę mi pomogłeś! Nie wiem, jak ci odpowiednio podziękować.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Przynieś mi jeszcze jeden biały koralik. Jeśli go oczywiście znajdziesz.";
			link.l1 = "Ach, tak! Białe koraliki! Dobrze. Do zobaczenia, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ach, wujku "+pchar.name+"! Cieszę się, że cię widzę! Jak się masz?";
			link.l1 = "Dzięki, Ole, mam się dobrze. Cieszę się, że cię również widzę.";
			link.l1.go = "exit";
			link.l2 = "Słuchaj, Ole, mówiłeś, że piraci admirała zamykają drzwi do ładowni, a ty zawsze je otwierasz... Wszystkie kufry tam są zamknięte, a mówiłeś, że bierzesz rum dla wujka Nathana z nich. Jak to robisz?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole ma zestaw wspaniałych kluczy. Otwierają każde drzwi czy skrzynię. No, nie wszystkie. Niektórych nie można otworzyć, ale większość można. Ole znalazł je w kabinie złego wuja Jurgena. On codziennie pracuje młotem przy swoim piecu. Robi zamki i klucze. A także robi duże i straszne muszkiety dla złych Narwali.";
			link.l1 = "Rozumiem. Ole, czy możesz sprzedać mi te klucze? Mogę za nie zapłacić...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Dobrze, wujku "+pchar.name+", sprzedam ci klucze. Zostawię tylko jeden dla siebie. Otwiera pokój admirała. Jest tam dużo jedzenia i rumu dla wujka Nathana. Zresztą, w skrzyniach nie zostały już żadne paciorki ani rum.";
			link.l1 = "Ile za nie chcesz?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "Najpierw powiedz mi, wujku "+pchar.name+", masz duży statek?";
			link.l1 = "Tak, widziałem ją. Ale nie jest tutaj, jest na zewnętrznym pierścieniu. Wkrótce opuszczę wyspę i wrócę tutaj na moim dużym statku dla wujka Nathana.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "Dla wujka Nathana? Och, to wspaniale! Słuchaj wtedy, obiecaj mi, że zabierzesz mnie stąd na swoim wielkim statku i pozwolisz żeglować z tobą tak długo, jak będę potrzebował. Mogę być użyteczny. Mogę łapać i gotować szczury... Poza tym, daj mi pięć białych paciorków. A ja dam ci klucze.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Oczywiście! Oto twoje koraliki. Weź je.";
				link.l1.go = "lock_4";
			}
			link.l2 = "Łapać i gotować szczury? Heh! Ciekawa umiejętność. Pewnie, Ole, mamy umowę. Przyniosę ci pięć paciorków i moje słowo.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ach, wujku "+pchar.name+" ! Cieszę się, że cię widzę! Jak się masz?";
			link.l1 = "Dzięki, Ole, mam się dobrze. Również cieszę się, że cię widzę.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Przyniosłem ci pięć białych koralików do twoich kluczy.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Korale! Białe korale! Wujku "+pchar.name+"  dał koraliki Ole! Wkrótce cię zobaczę, mamo!... Wujku "+pchar.name+", obiecujesz, że zabierzesz mnie stąd, kiedy wrócisz?";
			link.l1 = "Robię to, Ole. Jeszcze nie jadłem szczurów. Zabiorę cię ze sobą.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Dziękuję, dziękuję, dobry wujku "+pchar.name+" ! Weź swoje klucze. Łatwo ich używać, po prostu wkładaj je jeden po drugim i próbuj. Jeden z nich w końcu otworzy zamek, którego potrzebujesz. Jeśli nie, to zamek jest zbyt skomplikowany i zdecydowanie będziesz potrzebować specjalnego klucza.";
			link.l1 = "Rozumiem. Chyba sobie z tym poradzę.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Czekaj, wujku "+pchar.name+"! Mam jeszcze jeden klucz. Jest piękny i mądry. Zły wujek Jurgen nie robi takich kluczy. Nie wiem, co on otwiera, ale może ty to odkryjesz. Spójrz, to naprawdę piękny klucz, na pewno nie widziałeś wcześniej czegoś takiego.";
			link.l1 = "Pokaż mi... Tak, klucz jest bardzo interesujący. Ale jaki z niego pożytek, jeśli nie wiesz, co można nim otworzyć?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Wujku "+pchar.name+", , jesteś bardzo dziwny. Jaki z tego pożytek? Jeśli jest klucz, to gdzieś jest zamek. Jeśli jest zamek, to gdzieś jest moneta. Znalazłem klucz na wyspie. To znaczy, że zamek też tu jest. Nie ma co do tego wątpliwości. To sprytny klucz i tylko bardzo cenne przedmioty są takimi kluczami zamykane. Ole wie.";
			link.l1 = "Szczerze mówiąc, jesteś zabawny, Ole. Dobrze, kupię to. Chcesz za to koraliki?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Tak, Ole chce pięciu koralików. Czy dasz je, wujku "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Proszę, weź swoje paciorki.";
				link.l1.go = "key";
			}
			link.l2 = "Nie mam ich, ale na pewno przyniosę ci paciorki.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Koraliki! Białe koraliki dla białego chłopca! Dla jego mamusi! Tutaj, wujku "+pchar.name+", weź klucz. A zamek znajdziesz, Ole wie. Jesteś odważny, nie boisz się nawet strasznych krabów.";
			link.l1 = "Ach, nie rozśmieszaj mnie, Ole! Dzięki za klucz. Do zobaczenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ach, wujku "+pchar.name+" ! Cieszę się, że cię widzę! Jak się masz?";
			link.l1 = "Dzięki, Ole, mam się dobrze. Też się cieszę, że cię widzę.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Przyniosłem ci pięć białych paciorków za twój klucz.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ach, wujku "+pchar.name+" ! Cieszę się, że cię widzę! Jak się masz?";
			link.l1 = "Dzięki, Ole, mam się dobrze. Również cieszę się, że cię widzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "O, wujku "+pchar.name+", wróciłeś! Jesteś z powrotem na wielkim statku! Czy zabierzesz mnie stąd? Wujku "+pchar.name+", obiecałeś mi, pamiętasz?";
			link.l1 = "Oczywiście, że tak, Ole. Witaj na pokładzie! Przypuszczam, że szczury mają kłopoty, ha-ha!";
			link.l1.go = "return_1";
			link.l2 = "Naprawdę? A kiedy ci to obiecałem? Nie pamiętam żadnych takich obietnic...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Dzięki, wujku! Ole będzie przydatny, zobaczysz! Och, może zobaczę mamę? Już idę!";
			link.l1 = "Nie spiesz się tak, Ole. Możesz spakować swoje rzeczy. Nie zamierzam wypływać natychmiast.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "Obiecałeś mi, obiecałeś! Obiecałeś zabrać Ole stąd! Zły wujku! Oszukałeś Ole! Zły wujku!";
			link.l1 = "... ";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Wujku, wujku... Potrzebuję jeszcze jednego białego koralika. Proszę, daj Ole biały koralik!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Wiedziałem, że o to zapytasz. Proszę, oto twoja koralik. Zadowolony?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Och, co za udręka... Nie mam już koralików, Ole, nie mam!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Dziękuję! Dobry, dobry wujku "+pchar.name+"! Ole ma jeszcze jedną perłę, a niewiele pereł zostało! A ja pójdę do mamy...";
			link.l1 = "Och, a dlaczego jesteś taki dziwny...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = int(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Dziękuję za paciorek, dobry wuju "+pchar.name+"!";
			link.l1 = "Jesteś mile widziany...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "Nie ma koralika? Ale jak to, wujku "+pchar.name+"?! Jeszcze tylko kilka koralików... Muszę je zebrać. W takim razie wyląduję. Będę szukał koralików...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "A dokąd zamierzasz iść? Co zrobisz sam? Nie, nie chcę być odpowiedzialny za twój los. Poczekaj, sprawdzę swoje kieszenie... Oto! Weź swoją paciorkę i zostań ze mną. Zadowolony?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "To twoje prawo, Ole. Jeśli znudziło ci się żeglowanie ze mną, to cię nie powstrzymam. Mieliśmy umowę. Choć łapałeś te stawki całkiem dobrze...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Żegnaj, wuju "+pchar.name+". Ole potrzebuje białych koralików, inaczej nigdy nie wróci do swojej mamy...";
			link.l1 = "Och, tak mi przykro, ale co mogę zrobić? Idź, Ole. Powodzenia.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Wujek "+pchar.name+"! Potrzebuję jeszcze jednego białego koralika. Ostatniego. Proszę, daj go Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Wiedziałem, że o to poprosisz. Proszę, weź swoją koralik. Zadowolony?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Och, i co za utrapienie... Nie mam już koralików, Ole, nie mam!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Dziękuję, dziękuję, dobry wuju "+pchar.name+"Ole ma teraz wszystkie koraliki. Tak, wszystkie! Teraz Ole może je zanieść mamie, a ona nie odeśle Ole...";
			link.l1 = "Słuchaj, kim jest ta matka, o której ciągle mówisz? I wytłumacz mi w końcu, po co ci te perły... białe koraliki? I co to znaczy - masz je wszystkie?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "Dobry wujku "+pchar.name+" pomógł Ole zebrać paciorki dla swojej mamy... Ole był mały, kiedy rozerwał naszyjnik mamy z białych paciorków. Wszystkie wpadły do wody. Mama była tak zła na Ole, że nie może wrócić do domu, dopóki nie zbierze wszystkich zgubionych paciorków\nPamiętam, ile ich było. Pięć razy po dziesięć paciorków. Teraz Ole ma je wszystkie. Wujek "+pchar.name+"Proszę, zabierz mnie do domu! Chcę uszczęśliwić mamę, zwrócić koraliki. Zabierz mnie do domu!";
			link.l1 = "Boże, co za niesamowita historia... Dostałeś się na Wyspę będąc dzieckiem. Czy wygnały cię, bo zerwałeś naszyjnik z pereł swojej matki? Przerażające...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Zabierz mnie do mojej mamy, dobry wujku "+pchar.name+"Chcę ją zobaczyć. Ucieszy się na widok koralików.";
			link.l1 = "Chciałbym, ale czy wiesz, gdzie jest twój dom? Gdzie mieszka twoja matka?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "Mieszka na wyspie, w domu z czerwonym dachem.";
			link.l1 = "Naprawdę! Czy wiesz, ile tu jest wysp i ile domów z czerwonym dachem? Jak nazywa się ta wyspa? Daj mi szczegóły...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "Nie znam jego nazwy. Wiem, że to była wyspa, mama mówiła ojcu, że byliśmy na wyspie! I mieszkaliśmy w domu z czerwonym dachem. Ładny dom, duży. Zabierz mnie do mamy, wujku "+pchar.name+" Proszę...";
			link.l1 = "Och, dobrze. Będziemy szukać takiego domu na każdej wyspie i pytać o twoją matkę. Jak się nazywa?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "Jej imię? Jesteś taki dziwny, wujku "+pchar.name+". Imię matki to matka. Czy imię twojej matki jest inne?";
			link.l1 = "O Boże, proszę, daj mi trochę cierpliwości... Dobrze, Ole. Spróbujemy znaleźć twój dom. Teraz idź na statek.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Dzięki, wujku "+pchar.name+"Jesteś bardzo, bardzo miły i dobry! Wkrótce Ole zobaczy mamę!";
			link.l1 = "Och...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Matko... Matko, mamo! Wróciłem!";
			link.l1 = "Synu...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Mamo, przyniosłem ci białe koraliki! Zebrałem je wszystkie! Znów będziesz miała naszyjnik. Czy nadal jesteś na mnie zła?";
			link.l1 = "Boże...(płacze) Ole! Synu, dlaczego? Dlaczego odszedłeś? Nie obchodzą mnie te perły!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Mamo, weź je... Zbierałem je przez długi czas. Dobrzy wujkowie mi pomagali, zwłaszcza wujek "+sld.name+"Zabrał mnie na swój wielki statek, pomógł zebrać koraliki i przywiózł mnie do domu...";
			link.l1 = "Ole... Naprawdę dorosłeś, ale nadal jesteś dzieciakiem... Pozwól mi cię przytulić, synu! Przepraszam, wybacz mi ten przeklęty naszyjnik! Nigdy cię nie opuszczę, nigdy! Będziemy razem żyć, a ja będę o ciebie dbał... Odpokutuję, obiecuję!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Mamo, tęskniłem za tobą... Chcę z tobą zostać. Czy nadal jesteś na mnie zła? Dlaczego płaczesz?";
			link.l1 = "(płacząc) Nie, nie... Bardzo mi przykro, proszę wybacz mi, synu!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Wujek "+pchar.name+"! To takie dobre, że przyszedłeś! Dzięki, że przyprowadziłeś mnie do mojej mamy. Tak dobrze być tutaj z nią... Czyż nie wspaniale być w domu, prawda, wujku "+pchar.name+"?";
			link.l1 = "Tak. Ole. To prawda. Cieszę się, że jesteś zadowolony.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Odsuń je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Schowaj to, nie pasuje do ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i prosiłbym cię, abyś schował szablę.","Słuchaj, jestem obywatelem miasta i proszę cię, schowaj swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bądź ostrożny, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy ludzie przechodzą przede mną z bronią gotową do użycia. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiano.","Zabieram to.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
