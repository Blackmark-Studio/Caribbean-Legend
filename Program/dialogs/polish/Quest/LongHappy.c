// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "Czego potrzebujesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Panie de Maure, cóż za szczęście! Szukałem cię od miesięcy!";
			link.l1 = "Mój drogi, nie kupuję fałszywych map, wątpliwych informacji ani domowego rumu - dziękuję!  A może jesteś łowcą nagród?  I ile teraz wynosi nagroda za moją głowę?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Och, monsieur, ja... Ja nie handluję rupieciami i nie zabijam ludzi - nie dotykaj miecza, nie będzie ci potrzebny, nie mam złych zamiarów! Wszystko jest dużo bardziej prozaiczne - jestem kapitanem statku kurierskiego. Roznoszę pocztę. I dla ciebie mam ważną korespondencję!";
			link.l1 = "List?  Kto jest nadawcą, jeśli wolno zapytać?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Jeden opat wręczył mi to i poprosił, bym dostarczył to osobiście kapitanowi de Maure, z ręki do ręki. Już straciłem wszelką nadzieję na znalezienie cię i chciałem zostawić to w biurze portowym w Saint Pierre, ale co za szczęście - oto jesteś!";
			link.l1 = "Tak, oto jestem, czekam - daj mi list.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Jest jeden problem... Opat powiedział, że dostawa zostanie opłacona przez odbiorcę. Więc jesteś winien dziewięć tysięcy dwieście pesos.";
			link.l1 = "Za takie pieniądze powinno to być dostarczone na otwartym morzu prosto do kajuty, razem z poranną kawą! List możesz sobie zatrzymać.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "A dlaczego nie zajmowałem się dostarczaniem poczty?! To bardziej opłacalne niż piractwo! Oto twoje srebro, moja droga, daj kopertę.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Miło robić z tobą interesy! Ojciec Benoit przesyła najlepsze życzenia! Żegnaj, monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "Jak sobie życzysz. Zostawię kopertę w biurze portowym. Ale to wpłynie na cenę, ostrzegam cię. A tak, opat Benoit przesyła najlepsze życzenia.";
			link.l1 = "List od Opata Benoita? Czemu nie powiedziałeś tego od razu! To musi być ważne!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "Więc odbierz to z głowy portu. Nie zapomnij wziąć pożyczki z góry. Żegnaj, kapitanie de Maure.";
			link.l1 = "Znałem piratów bardziej szczerych niż ty. Powodzenia, moja droga.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Ojcze Święty, dziś jesteś wcześniej niż zwykle. Proszę, twoja eskorta czeka. A ty, señor de Maure - ojciec Vincento dowiedział się, że jesteś w mieście i nalega, byś dołączył do niego na kolację.";
			link.l1 = "Obawiam się, że Inkwizytor zje kolację samotnie. Mam nadzieję, że nie wpłynie to na jego apetyt. A opat Benoit także pozbawi go swego towarzystwa. Wiesz, kim jestem, więc radzę ci. przepuścić nas bez żadnych konfliktów i przekazać moje najlepsze życzenia ojcu Palottiemu.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "Tak, wiele o tobie słyszałem i mam jasne instrukcje, aby nie zamieniać miasta w krwawą łaźnię, jeśli będziesz uparty. Możesz przejść. Ale ojciec Vincento będzie... niezadowolony. Miej to na uwadze.";
				link.l1 = "Zachowałeś się rozsądnie, monsieur. Jakoś przeżyję ból w moim sercu spowodowany niezadowoleniem ojca-inkwizytora. Miłego wieczoru!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "Tak, słyszałem o tobie... wiele interesujących rzeczy. Jednakże odrzucanie takich zaproszeń jest niebezpieczne dla zdrowia, senior. Podobnie jak porywanie gości ojca Vincento. Zatrzymać ich!";
				link.l1 = "Każdy dokonał swego wyboru. Żałuję, że musiało do tego dojść. Do broni, caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, gratuluję! Wiesz - zawsze cię lubiłem, a Helen jest dla mnie jak córka, więc cieszę się za was oboje. Cholera... uronić łzę w kościele to wszystko, czego kiedykolwiek pragnąłem, czy ja się starzeję, czy co?";
			link.l1 = "Wszystko w porządku, Janie, prawie się popłakałem przy ołtarzu. Kadzidło, pewnie?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Racja, kamfora, do diabła. Zastanawiałem się, czemu moje oczy pieką, a nos swędzi! Dobrze, pogadamy w Sharptown, przytulimy Gladys i pójdziemy do innych. Mają takie miny, jakbyśmy podpisywali pokój westfalski.";
			link.l1 = "Dzięki, że przyszedłeś, Janie. Cieszę się, że cię widzę, to wiele znaczy dla Heleny.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Nareszcie jesteś, Charles! Mój korwet wyprzedził cię o prawie dzień - to powód do dumy.";
			link.l1 = "Nie ma sprawy Jan, ale gdzie jest Gladys i twoja żona?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "Wysłałem Gladys z powrotem do Blueveld na statku handlowym - nie pochwala tych wszystkich szalonych zabaw. Joanna nie mogła przyjechać - och, nie miałem czasu ci powiedzieć na Martynice! Wyobraź sobie - na stare lata zostanę prawnym ojcem, co ty na to? Spójrz, jeśli się pośpieszysz, nasze potomstwo będzie prawie w tym samym wieku, hahaha!";
			link.l1 = "Jan, moje gratulacje, to wspaniałe wieści!!! Powinniśmy się napić za to!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Zdecydowanie! Ale najpierw, dla ciebie i twojej lepszej połowy! Hej, tam, zamknijcie się!!! Stary Leśny Diabeł musi przemówić!\nKhe-khe... Więc, nasze drogie Monsieur i Madame de Maure... Do diabła! Nie potrafię tak mówić! Charles, Helen - wy dwoje, jesteście dla mnie jak moje własne dzieci, i wiem, że w tym pokoju nie ma nikogo, kto by się nie cieszył z waszego związku! Więc wypijmy, moi Bracia, za szczęście naszych wiernych przyjaciół, za pomyślny wiatr w ich żaglach i za miłość Pani Fortuny, równie silną jak ich uczucia do siebie nawzajem!!! Na zdrowie!";
			link.l1 = "Na zdrowie! Dzięki Jan... och, ten rum jest znacznie mocniejszy niż zwykle... Co Nathan do niego domieszał?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "Nie mam pojęcia, ale to trafia słusznie. Stary Jastrząb jest zazwyczaj ekspertem od napojów. Chodź, idź do innych, muszę zrobić trunki dla dobrej setki dusz chciwych na napełnienie się.";
			link.l1 = "Diabeł Leśny nalewa drinki - taki widok! Dziękuję, że wzięłaś na siebie organizację przyjęcia. Na pewno wrócę, jak tylko obejdę wszystkich - może ktoś potrzebuje pomocy.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Wszystko w porządku, Charles?";
			link.l1 = "Świetnie, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "I oto jesteś, wreszcie! Jak poszło na Martynice? Czy czujesz, że twoje życie zmieniło się na zawsze?";
			link.l1 = "Zmieniło się dużo wcześniej, Janie. Ale wszystko poszło zaskakująco dobrze. Gdzie jest Joahnna i...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen? Dziewczyna odpłynęła, gdy tylko dowiedziała się, co kombinujemy, i popłynęła ku horyzontowi. Przekazała ci wszelkie ciepłe gratulacje, ale mimo to... złamałeś jej serce, naprawdę to zrobiłeś. Jednak wszystko będzie dobrze, to tylko młodość.";
			link.l1 = "Cóż, serce chce tego, czego chce, rozumiesz to.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "Wiem. Cóż, Joahnna nie mogła przybyć, wyobraź sobie - na starość zostanę prawnym ojcem, co ty na to? Spójrz, jeśli się pospieszysz, nasze potomstwo będzie prawie w tym samym wieku, hahaha!";
			link.l1 = "Jan, moje gratulacje, to są dobre wieści!!! Powinniśmy to uczcić kielichem!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Zdecydowanie! Ale najpierw, dla ciebie i twojej lepszej połowy! Hej, wy tam, zamknąć się!!! Stary Lasowy Diabeł musi wygłosić mowę!\nCharles i Mary, cała Brać podnosi teraz kielichy na waszą cześć! Szczęście prawdziwych przyjaciół raduje duszę każdego wilka morskiego, niemal tak samo jak przepych hiszpańskiego złota, ha-ha! Płyńcie dobrze, a niech pomyślne wiatry towarzyszą wam w waszej rodzinnej podróży!!! Na zdrowie!";
			link.l1 = "Na zdrowie! Dzięki Jan... och, ten rum jest znacznie mocniejszy niż zwykle... Co Nathan do niego dodał?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "Nie mam pojęcia, ale to wydaje się słuszne. Stary Jastrząb generalnie jest ekspertem od napojów. No dalej, idź do innych, muszę przygotować napoje dla dobrej setki dusz chciwych napełnić swoje brzuchy.";
			link.l1 = "Ta tawerna z pewnością wymaga zmiany nazwy - 'Sam Diabeł Leśny stał tutaj za ladą'! Dziękuję, Jan, na pewno wrócę, jak tylko obejdę wszystkich - może ktoś potrzebuje pomocy.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "Jak się masz, Charles? Jak tam ślub?";
			link.l1 = "Bardzo wzruszające, Janie. Cieszę się, że udało nam się wszystkich tu sprowadzić. Wygląda na to, że beczki rumu Jastrzębia zaczynają pokazywać swoje dno, prawda?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Tak, są! Więc czas otworzyć to, co przyniosłeś. I jeszcze jedno - ci faceci, którzy mi na początku pomogli, upili się na umór w tylnej izbie. Wydajesz się jeszcze stać na nogach, panie młody - możesz przynieść skrzynkę kolejnego sherry?";
			link.l1 = "Pewnie, po prostu powiedz mi, dokąd mam iść. Może po drodze znajdę kilka trzeźwych głów, które mi pomogą. Chociaż, większość moich ludzi pewnie już pijana jak bela.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "Wino było składowane w piwnicach pod stocznią, pamiętasz je? Hawk powiedział, żeby trzymać je w najdalszym korytarzu, ''zachować na święto'' - tak mówi. Mówi też, że tam jest idealna temperatura i wilgotność, mówi, że to by było idealne miejsce na piwniczkę na wino. No cóż, jest wielkim snobem.";
			link.l1 = "Podjął właściwą decyzję, Janie. Pójdę, ale najpierw powiedz mi - widziałeś moją żonę?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "Poszła gdzieś z Dannie. Niech dziewczyny sobie pogadają, Charles, a my musimy zacząć prawdziwą zabawę. Zejdź do piwnic, podczas gdy ja zajmę się jedzeniem. Bo śmierdzi mi tu, że niedługo będziemy jeść węgiel zamiast jagnięcych żeber!";
			link.l1 = "Dobrze, idź uratować mięso, a ja przyniosę nasze wino.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, co się stało, zaczęliście bójkę po pijanemu?!";
			link.l1 = "Nie, Janie, walczyliśmy razem przeciwko uzbrojonym kutrom w lochach. Poradziliśmy sobie z nimi, ale to byli tylko zwiadowcy - główny oddział jest tuż za nami!";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Załoga? O czym ty mówisz?! Marcus, chodź tutaj! Charles, no dalej, opowiedz nam wszystko.";
			link.l1 = "Jak powiedziałem: w lochach pod stocznią czają się jakieś dranie. Dobrze uzbrojeni. Nathan i ja walczyliśmy z nimi i cudownie powaliliśmy wszystkich. Ale więcej z nich jest w drodze - słyszałem, że jeden z nich został wysłany po pomoc. I tak, jeden z nich wspomniał jakiegoś Jacquesa.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "Rozpoznaję ich twarze... ten tutaj i ten drań leżący przy drzwiach. To zbiry Jacquesa Dobrego Człowieka. Nie pamiętam ich imion, ale wiem to na pewno.";
			link.l1 = "Więc to wina Barbazona? Czy on oszalał, czy co?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "Nie wiem, ale wydaje się, że Kindman postanowił skorzystać z okazji i przeprowadzić radykalną przemianę wśród baronów Bractwa.";
			link.l1 = "W tym przypadku mam nadzieję, że sam się pojawi - tak długo marzyłem o tym, żeby zrobić parę dziur w jego ciele. Drań, zrujnował moje wesele, tylko pomyśl o tym! Ruszamy na ulice! Przygotujemy właściwe powitanie dla naszych gości!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "A oto nasz zmęczony bohater! Ha, Charles, to było coś! Jacques, taki szczur! Zobacz, jak to wszystko zaaranżował - prawie mu się udało!";
			link.l1 = "Tak, prawdopodobnie, powinniśmy byli zabić tego drania, gdy skończyliśmy z Jackmanem. Jednak to już koniec. Barbazon nie żyje.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Cóż, nie mogę powiedzieć, że to koniec - nasze życie trwa nadal! Chociaż czuję się całkowicie wykończony. Jestem za stary, by skakać do morza z okrętu pokrytego ogniem i płynąć całą godzinę do brzegu, wypatrując rekinów. Mam nadzieję, że wciąż mamy trochę rumu...";
			else dialog.text = "Cóż, nie mogę powiedzieć, że to koniec - nasze życie trwa dalej! Cholera, czuję się o dziesięć lat młodszy! Dawno nie walczyłem w ten sposób! Mam nadzieję, że twoje zapasy rumu i wina nie zostały skradzione podczas zamieszania - musimy to dobrze opić!";
			link.l1 = "Tak, też bym się napił, ale najpierw muszę sprawdzić rezydencję, nie wiem, czy ci powiedziano, czy nie...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "Chodzi o twojego indiańskiego kumpla? Tak, słyszałem, jak to się stało?";
				link.l1 = "Skoczył, by osłonić moją żonę i Dannielle przed kulą wystrzeloną przez jednego drania. Powinniśmy iść, opowiem ci po drodze.";
			}
			else
			{
				dialog.text = "Chodzi o Nathana? Tak, słyszałem, tylko nie zrozumiałem, jak to się stało?";
				link.l1 = "Skoczył, by osłonić nasze żony przed kulą wystrzeloną przez jednego łajdaka. Powinniśmy iść, opowiem ci po drodze.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Trzymaj się, Charles. Naprawdę mi przykro z powodu twoich chłopaków. Dziś wielu dobrych ludzi odeszło, a za każdego z nich Barbazon w piekle dostanie więcej oleju do swojego kotła.";
				link.l1 = "To nie ma sensu... cholera! To trudne, Janie... Już straciłem przyjaciół, ale nie mogę się do tego przyzwyczaić. Nie wiem, czy mogę tak dalej.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Więc ten cichy facet-medic? Przykro mi, Charles, szczerze. Był dobrym człowiekiem.";
					link.l1 = "Tak, Janie, ja też. Ale obawiam się, że świat nauki stracił o wiele więcej niż ja. Był geniuszem... wyrafinowanym, jak wszyscy oni, ale... cholera...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Cóż, zdaje się, że to już koniec. Dzisiaj wielu dobrych ludzi odeszło, a za każdego z nich w piekle Barbazon dostanie więcej oleju do swojego kotła, ale "+sTemp+"Będzie dobrze i to jest najważniejsze.";
					link.l1 = "Masz rację, Janie, i to wielka ulga dla mnie. Jak się mają inni baronowie? Czy wszystko z nimi w porządku?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "Ostatni plugawiec Jacques'a Barbazona. Masz rację, gdybyśmy go zabili wcześniej, wszystko mogłoby być inaczej.";
			link.l1 = "Ale cóż z tego, że się żałuje przeszłości? Przeszłości nie można zmienić. Jak się mają inni baronowie? Czy wszyscy przeżyli?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = " Nikt nie może się do tego przyzwyczaić. Napijemy się za naszych chłopaków? Znalazłem butelkę na stole, cudownie przetrwała ten bałagan.";
			link.l1 = "Wlej, ja... Cholera... tysiąc cholernych przekleństw!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Opowiedz mi o nich. Ten medyk wydawał się bystry. Wypowiadał się tak mądrze.";
			link.l1 = "Zrobił to. Ale obawiam się, że świat nauki stracił znacznie więcej niż ja. Był geniuszem... wyrafinowanym, jak wszyscy oni. Mistrzem cudów!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "O tym Indianinie? Gdzie go znalazłeś?";
			link.l1 = "Uratowałem go z więzienia na Gwadelupie, prawie natychmiast po moim przybyciu. Naprawdę zabawna i głupia historia. Więc, został ze mną. Wybrał to, dałem mu wolność, ale został przy mnie - uratowałem go, a on myślał, że jest mi dłużny aż do końca życia. Oszczędny w słowach, dziwnie ubrany, ale wierniejszy niż jakikolwiek rycerz, miał też talent, potrafił trafić monetę z muszkietu w powietrzu na każdą odległość.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Cóż, zapłacił ci dług, co mogę powiedzieć. Uratowany "+sld.name+" i Dannielle od tego drania. Wydaje mi się - to godny koniec dla tak dzielnego wojownika.";
			link.l1 = "Tak jest, Janie. Wypijmy za pamięć poległych... Niech znajdą spokój. Jak się mają inni baronowie? Czy wszystko z nimi w porządku?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "Ta noc kosztowała nas drogo. Nie wiem nawet, kiedy Braterstwo otrząśnie się z tej masakry. Kindman doskonale wybrał czas i miejsce na atak. Prawie mu się udało - jeszcze trochę, a wszystko byłoby skończone. Ale straciliśmy znacznie mniej, niż mogliśmy.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "Rekin jest w lazarecie, jego statek dostał salwę z dwudziestu czterech funtów. Poleciał za burtę, złamał parę żeber, nałykł się morskiej wody, ale żyje, za kilka dni będzie jak nowy.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard odniósł tylko parę zadrapań - bronił wybrzeża i oczyszczał katakumby. Teraz jest w porcie, organizując szpitale dla rannych i pogrzeby dla tych, którzy mieli pecha.";
			else dialog.text = "Bernard miał pecha, sprzątał domy po ataku z katakumb i natknął się na grupę tych drani w magazynach. Dostał kulę, prosto w głowę. Szkoda, był dobrym kapitanem... Tyrex będzie wściekły, kiedy się o tym dowie.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard odniósł tylko kilka zadrapań - bronił wybrzeża i oczyszczał katakumby. Teraz jest w porcie, organizując szpitale dla rannych i pogrzeby dla tych, którzy mieli pecha.";
			else dialog.text = "Bernard miał pecha, sprzątał domy po ataku z katakumb i natknął się na bandę tych drani w magazynach. Dostał kulę, prosto w głowę. Szkoda, był dobrym kapitanem... Tyrex będzie wściekły, kiedy się o tym dowie.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "O Jastrzębiu wiesz. Dannie nie pozwoli mu opuścić wyspy przez co najmniej miesiąc, to pewne. Miał jedno przedsięwzięcie na głowie... no cóż.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus ma się dobrze jak zawsze. Ledwie zszedł na ląd, od razu zaczął wytrząsać dusze ze strażników, którzy przegapili to całe plugastwo. Nadal zdołał rozkazać przywrócenie porządku w mieście. Człowiek z żelaza, inaczej nie powiesz.";
				link.l1 = "Żelazo jest miększe. Myślę, że nasz baron zrobiony jest z metalu, który wciąż jest nieznany nauce, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Tylko z Marcusem jest niezrozumiałe, jego statek został zaatakowany, ale ocalałe twierdzą, że udało mu się wyskoczyć za burtę. Już wysłałem szalupy, by przeszukać zatokę. Mam nadzieję, że okaże się, iż nasz baron jest na tyle twardy, by tak łatwo się nie poddać.";
				link.l1 = "To źle, ale za wcześnie, by płakać nad nim, Marcus tak łatwo by nas nie porzucił. Poczekajmy na wynik poszukiwań.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus dopłynął do brzegu po tym, jak jego statek zatonął. Wiesz, Tyrex to nie jest ktoś, kto utonie przez taką błahostkę. Teraz jest gdzieś w mieście. Pewnie wytrząsa dusze z wartowników, którzy przeoczyli całe to plugastwo. Żelazny człowiek, inaczej się nie da powiedzieć.";
				link.l1 = "Żelazo by zatonęło. Chyba nasz baron jest zrobiony z materiału, który wciąż jest nieznany nauce, haha!";
			}
			else
			{
				dialog.text = "Marcus ma się dobrze jak zawsze. Jak tylko wyszedł na brzeg, natychmiast zaczął wytrząsać dusze ze strażników, którzy przegapili całe to plugastwo. Nadal udaje mu się dowodzić przywracaniem porządku w mieście. Żelazny człowiek, nie inaczej.";
				link.l1 = "Żelazo jest miększe. Przypuszczam, że nasz baron jest zrobiony z metalu, który wciąż jest nieznany nauce, haha!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "To wszystko. No cóż, mogło być gorzej. Nawet twoje wesele, Charles, wyszło... walecznie. Najważniejsze, że oboje żyjecie. Mała rada, ogólnie... kochajcie się... i nie ważcie się rezygnować z walki o to!";
			link.l1 = "Dzięki Jan. Dzięki wam wszystkim... Muszę przyznać, że zapomniałem, że zaczęliśmy od świętowania.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "Więc oto przypomnienie.";
			link.l1 = "Tak, to była... dzika impreza.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Ach, tak, na pewno tak było, czekaj chwilę. Jest coś - wydawało się, że miałeś ze sobą Indianina, prawda, zawsze przy tobie albo rozglądającego się, jakby ktoś ci celował. Śmiesznie ubrany i bardzo wyróżniający się w tłumach.";
			link.l1 = "Tak, Tichingitu, zniknął na samym początku tego bałaganu, szczerze mówiąc zaczynam się martwić. Czy wiesz coś?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Wygląda na to. Nasz barman hałasował, że jego siostrzenica została porwana, tylko rzekomo przed atakiem. Mówi, że widzieli ją z jakimś Indianinem, niósł ją na ramieniu wzdłuż brzegu na wschód od miasta. Nie zauważyłem wśród łajdaków Kindmana żadnych Indian, ale przypomniałem sobie o twoich, kiedy to usłyszałem, więc nic nie powiedziałem. Powinieneś iść, szukać go czy coś, zanim wpadnie w jakieś kłopoty. Bo barman grozi, że go zabije, jeśli znajdzie go pierwszy. Jest dobrym chłopem, ale dla swojej siostrzenicy odkręci każdą głowę.";
			link.l1 = "Tak, znam ten typ, nie martw się, i dzięki Jan, pójdę i poszukam go od razu.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Cóż, ogólnie rzecz biorąc, coś w tym stylu... Przepraszam, kiepsko mi idzie z przemowami. A teraz jest jeszcze gorzej - ta noc wycisnęła nas wszystkich do cna. Wszyscy powinniśmy odpocząć przynajmniej jeden dzień - potem zdecydujemy, jak postępować.";
			link.l1 = "Masz rację, Janie. Powinienem iść, muszę odświeżyć umysł.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Wyglądasz dobrze, Charles. Dobrze spałeś?";
			link.l1 = "Tak, dostaliśmy przytulny dom na obrzeżach miasta. Nawet pomyślałem, że to wszystko, co się wczoraj wydarzyło, było tylko snem. A tu jesteś, Janie, wyglądasz okropnie. Co się jeszcze stało?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "O nie, to nic takiego, po prostu jeszcze nie spałem. Wiesz... sprzątanie miasta po wszystkim, co się tu wydarzyło, to ciężkie zadanie.";
			link.l1 = "Jak się mają Dannie i Nathan? Gdzie są wszyscy?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = " Odpoczywają. Nie przeszkadzaj im, Dannie ostrzegła wszystkich, że dziś zabrała pistolety do łóżka... Dodson jest na morzu, wyruszył, by znaleźć więcej statków do zabezpieczenia wyspy, by to się nie powtórzyło, inni grzebią zmarłych na północy wyspy.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcusa jeszcze nie znaleziono, ale damy sobie z tym radę, nie martw się. Zrobiłeś tak wiele dla nas wszystkich, więc nie przejmuj się. Tyrax wróci prędzej czy później - znajdziemy go.";
			else dialog.text = "Marcus skończył tutaj i ruszył na czyimś lugrze na Hispaniolę. Konieczne jest rozwiązanie pewnych spraw, które pojawiły się po śmierci Barbazona. Przesłał pozdrowienia i najlepsze życzenia dla ciebie i twojej żony.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Cóż, Bracia przetrwali ten cios. Wkrótce powstaniemy silniejsi niż kiedykolwiek. Kindman i Jackman zbyt długo trzęśli naszą jednością, teraz ich nie ma, a moje serce czuje - sprawimy, że Karaiby drgną nie raz. Złoty Wiek nadchodzi dla tych, którym prawa i królowie nie są miłe, zapamiętajcie moje słowa.";
			link.l1 = "To byłoby miłe. Nie jestem pewien, czy będę w stanie wytrzymać Stary Świat dłużej. Nigdy nie myślałem, gdy tu przyjechałem, że zakocham się w wolności morza, tych szalonych kolorach zachodów i wschodów słońca, że znajdę najlepszą kobietę na świecie i... przyjaciół, którym powierzyłbym swoje życie.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Cóż, znasz kurs, po prostu zdecyduj się. W naszych domach zawsze jesteś mile widziany.";
			link.l1 = "Dzięki, Jan. To wiele dla mnie znaczy.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "  Ale najpierw, jest jeszcze coś ważnego. Charles, gdy spałeś, zebraliśmy się i podjęliśmy decyzję. Skoro Barbazon nie żyje, Bracia potrzebują nowego barona. Ponieważ była tutaj wyraźna większość z nas, a decyzja została podjęta jednogłośnie, oto ona. Gratulacje - jesteś nowym Baronem Le Francois. Ale zaczekaj... Rozumiem - jesteś osobą świecką i nie masz czasu prowadzić interesów w tym miłym miejscu, więc umieściliśmy tam zaufaną osobę, a ty robisz, co chcesz. Pamiętaj tylko - twój głos jest teraz w Bractwie.";
			link.l1 = "Jan, ja... ja nie wiem, co powiedzieć... To wielki zaszczyt, nawet nie wiem...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "Chodźże! Udowodniłeś się doskonale wtedy z Tyrexem, a potem z całą tą historią z dziedzictwem Sharpa. Jesteś błogosławieństwem samego Boga. Dla ciebie nic się nie zmieni - rób, jak zaplanowano, a pod twoją nieobecność, twój człowiek zajmie się wszystkimi sprawami\nJest jeden obiecujący facet Jan David, jest jednym z bukanierów. Francuz, uczciwy gość, z błyskotliwym umysłem i wie, jak go używać, jak ty. Ale zajmie mi trochę czasu, aby go znaleźć - wydaje się, że został złapany przez Hiszpanów, ale to da się rozwiązać, nie martw się. Upewnię się, że wyśle ci twoją część, jak tylko zaznajomi się z interesami.";
			link.l1 = "Naprawdę nie spodziewałem się, że wszystko tak się potoczy. Cóż, skoro już tak zdecydowałeś, niech tak będzie. Piracki Baron Charles de Maure!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Niech żyje baron! Jeśli ktoś zasługuje na to miano, to właśnie ty. Noś je z dumą i nie zapominaj - teraz jesteś jednym z nas, bez względu na to, jak piękny mundur nosisz, tutaj, pod nim, bije serce prawdziwego pirata.";
			link.l1 = "Nie wiem, może przesadzasz... Ale zrobię wszystko, co w mojej mocy, by uzasadnić twoje zaufanie.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "Co teraz zamierzasz zrobić? Wrócić do Europy, do ojca, żeby przedstawić mu żonę?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Tak, lecz najpierw muszę pożegnać się z kimś... Wiesz, co mam na myśli.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Może nie tak szybko. Jeszcze raz przepłynę przez archipelag, chcę po raz ostatni zaczerpnąć tego powietrza Wolności.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Cóż, masz statek, możesz żeglować do domu, kiedy tylko zechcesz.";
			link.l1 = "Mam nadzieję. Dzięki Jan, dzięki wam wszystkim i do zobaczenia później, mój stary przyjacielu! Pozdrów Jastrzębie i Rekina!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "Tak, to trudne, ale musimy to zrobić. Na morze?";
			link.l1 = "Nie, popłynę na Antiguę. "+sTemp+" by spocząć w pokoju w miejscu, które stało się naszym domem, na jakiś czas.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Powiedz kilka miłych słów ode mnie. I nie martw się - damy sobie radę sami od teraz. Wszystko będzie dobrze.";
			link.l1 = "Dzięki Jan. Do zobaczenia wkrótce, mój stary przyjacielu! Przekaż moje pozdrowienia Jastrzębiom i Rekinowi!... Cóż, Antigua to jest.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Młodzieńcze, dziś jeszcze bardziej urosłeś w moich oczach. Zrobiłeś tak wiele dla Helen, że żadne słowa wdzięczności nie będą wystarczające. Mam tylko nadzieję, że będziesz się nią dalej opiekował. Gdyby jej ojciec żył i to zobaczył, jakże byłby szczęśliwy... och, przepraszam.";
			link.l1 = "Jest w porządku, Gladys. Przepłynęłaś przez archipelag, aby wesprzeć Helen w tym dniu. Oboje naprawdę doceniamy twoją wizytę z Janem, dziękujemy.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Monsieur de Maure, przepraszam za tę poufałość, ale powiem to w ten sposób - Charles, mój przyjacielu, szczerze się cieszę z twojego szczęścia! Jeśli mogę coś zrobić dla ciebie lub twojej narzeczonej, po prostu powiedz!";
			link.l1 = "Dziękuję ci, Baronie, jestem tak szczęśliwy, a winnice, które mój ojciec chciał jako wiano, myślę, że mogę odkupić - na szczęście, moja sytuacja finansowa podczas pobytu w Nowym Świecie znacznie się poprawiła.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Tak, przypuszczam, że możesz sobie pozwolić na wszystko, czego zapragniesz, Charles. Wybacz, ale wniosę swój wkład jako reprezentujący ojciec - Dziś napiszę do mojego dobrego przyjaciela, Ministra Finansów. Twoja wybranka otrzyma tytuł szlachecki, a myślę, że znajdziemy dla niej jakieś dobre włości, powiedzmy w Gaskonii, spośród tych, które zostały zajęte za długi, i przypiszemy je jej wstecznie. Więc nikt nie ośmieli się powiedzieć, że Chevalier de Monper znalazł żonę z niskiej pozycji!";
			link.l1 = "Nie sądzę, żebym przejmował się takimi plotkami, ale dzięki, Baronie. Mimo to, nie powinieneś";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "Więcej niż powinienem! Teraz idź, Charles, poświęć uwagę reszcie gości. I raz jeszcze, przyjmij moje najszczersze gratulacje!";
			link.l1 = "Ja i moja żona dziękujemy ci. Do zobaczenia, Baronie.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, przepraszam za poufałość, ale powiem to w ten sposób - Charles, mój przyjacielu, szczerze się cieszę z twojego powodu! Jeśli mogę coś zrobić dla ciebie lub twojej narzeczonej, po prostu powiedz!";
			link.l1 = "Dziękuję, baronie, ale już wiele dla mnie zrobiłeś. Wystarczy nam, że odpowiedziałeś na zaproszenie.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "Jakże mógłbym nie odpowiedzieć, Charles! Ale słuchaj - chcę podarować tobie i twojej pięknej narzeczonej godny prezent, ale nie potrafię wymyślić niczego, czego nie mógłbyś zdobyć sam za pieniądze albo mieczem. Dlatego napiszę do mojego przyjaciela, Ministra Finansów w Paryżu, i zanim dotrzecie do Europy, będziecie oczekiwani na podpisanie królewskiego reskryptu o wyniesieniu nazwiska de Monper do tytułu Baronów de Monper! Nie, ani słowa, to najmniej, co mogę dla was zrobić.";
			link.l1 = "Nie wiem nawet, co powiedzieć, Baronie... Ojciec będzie taki szczęśliwy. Szczerze dziękuję.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, proszę, przyjmij moje szczere gratulacje! Twoja wybranka to prawdziwy cud! Myślę, że dzisiaj kolonialna moda otrzymała silny... impuls w nowym kierunku. Twoja oryginalność zawsze mnie fascynowała! Niech ty i twoja piękna połowa żyjecie długo i szczęśliwie!";
			link.l1 = "Dziękujemy, Baronie. Zaszczyciłeś nas swoją wizytą.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "Jakże mógłbym się oddalić, mój przyjacielu? Przeszliśmy razem wiele i jestem dumny, że mogę nazwać cię przyjacielem, Charles. Pamiętaj - moje drzwi są zawsze dla ciebie otwarte, bez względu na to, co się stanie.";
			link.l1 = "Drzwi rodziny de Monper zawsze będą dla ciebie otwarte, Baronie.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, mój przyjacielu, to bardzo ważny dzień i cieszę się, że zaprosiłeś mnie, bym go z tobą dzielił. Ty i ja przeszliśmy długą i trudną drogę, a zostać przedstawicielskim ojcem mademoiselle... proszę, wybacz mi - Madame de Maure, to dla mnie zaszczyt, uwierz mi. Z całego serca życzę ci szczęścia!\nI proszę, daj mi znać, kiedy wybierasz się do Europy - ja, jako przedstawicielski ojciec twojej wybranki, wyślę twojemu ojcu wszystkie niezbędne prezenty ślubne. Uwierz mi, nikt nie powie, że narzeczona kawalera de Monper jest biedna czy niegodna!";
			link.l1 = "Jeśli można spytać, Kawalerze, kilka mil na północ od posiadłości de Monper, znajdują się dobre winnice, należące do rodziny La Brigne, a ja...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Dość słów, mój przyjacielu, dość słów! Natychmiast napiszę do mojego upoważnionego przedstawiciela w Lyonie - na twój przyjazd te winnice zostaną przekazane twojemu wybrańcowi.";
			link.l1 = "Dziękuję, Chevalier. Masz rację - nasze... przyjaźń, przeszła przez... wiele. Ale, naprawdę się cieszę, że spędziłeś ten dzień z nami. Do zobaczenia i jeszcze raz dziękuję!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, mój przyjacielu, to bardzo ważny dzień i cieszę się, że zaprosiłeś mnie, bym go dzielił z tobą. Przeszliśmy długą i trudną drogę, a świadkowanie dziś na twoim ślubie jest dla mnie zaszczytem. Z całego serca życzę ci szczęścia! Daj mi znać, kiedy wybierasz się do Europy - wyślę twojemu ojcu godne prezenty ślubne.";
			link.l1 = "Nie ma potrzeby, Chevalier. Dziękuję za odpowiedź na moje zaproszenie.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "Jak już powiedziałem - to dla mnie zaszczyt! Ale zaczekaj, przyjacielu, chciałbym wręczyć ci coś z tej okazji - jestem pewien, że to ucieszy zarówno ciebie, jak i twoją wybrankę. Piękne kamienie z naszych kopalń w Nowej Gwinei - dobierz dla nich porządną oprawę, a madame de Maure będzie błyszczeć nawet na królewskim przyjęciu! O ile przekonasz ją do założenia sukni, oczywiście...";
			link.l1 = "Och, naprawdę nie powinieneś, kawalerze. Jeszcze raz dziękuję.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, mój przyjacielu, pozwól, że ci pogratuluję! Przeszliśmy długą i trudną drogę, i szczerze cieszę się, że jesteśmy tu dziś. Nasz Pan jest świadkiem - zasługujesz na swoje szczęście! Zachowaj je i chroń - życzę ci wielu szczęśliwych lat przed sobą!";
			link.l1 = "Dziękujemy, Kawalerze, ja i moja żona jesteśmy bardzo wdzięczni.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, co za świętowanie, i ilu ważnych ludzi! Pozwól, że z całego serca życzę ci szczęścia i dobrego zdrowia, a dzieci dla radości! Jak mówimy - 'gorzko'!";
			link.l1 = "Dziękuję, Fadey, zaszczyciłeś mnie swoją zgodą na przybycie.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "Ale nie do końca rozumiem, dlaczego jest tu tylu ludzi, jakbyśmy nie zawierali małżeństwa, ale wielki kontrakt handlowy, a piwa i wódki wciąż za mało na mój gust... haha! No, żartuję, Charles, czemu całkowicie zbladłeś? Przytul mnie, ty żonaty kapitanie!";
			link.l1 = "O rany... Fadey, jesteś silny jak niedźwiedź!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Poczekaj, Charles, nie odchodź - nie przystoi, aby gość przychodził na wesele bez prezentów. Weź je. Wiem, że próbowałeś znaleźć wszystkie te ostrza, a niektóre oczywiście przypadły Ci do gustu. Więc przyjmij je - powieś je w rodowej posiadłości i wspomnij Fadeya Moskwita ciepłym słowem!";
			link.l1 = "To prawdziwy dar! Dziękuję, Fadey. To są naprawdę wspaniałe bronie, i obiecuję, że zajmą należne im miejsce w posiadłości de Monper!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, cóż za świętowanie, i ilu ważnych ludzi! Pozwól, że z całego serca życzę ci szczęścia i zdrowia, oraz dzieci na pociechę! Jak to mówimy - 'gor'ko'! Uściskaj mnie, ty żonaty kapitanie!";
			link.l1 = "Wow... Fadey, jesteś silny jak niedźwiedź!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Czarku, nie mogłem tego przegapić, z całego serca gratuluję Tobie i Twojej wybrance! Bądźcie szczęśliwi! Wiesz, kilka miesięcy temu oddałem swoją córkę za dobrego człowieka i z miłości, ale szczerze mówiąc, byłem zasmucony, że to nie Ty... No cóż, dobrze... o czym ja w ogóle mówię - gratulacje! Niech żyjecie długo i szczęśliwie!";
			link.l1 = "Dzięki, Prosper, cieszę się, że przyszedłeś.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Gratulacje, kapitanie! Dziwny obrzęd, ale piękny - Tichingitu się podobał. Chociaż, kapitan powinien po prostu uprowadzić swoją squaw i wysłać okup jej krewnym.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Cóż, w pewnym sensie tak, to tylko formalność. Dziękuję, przyjacielu!";
			else link.l1 = "Cóż, w pewnym sensie tak, i to tylko formalność. Dziękuję, mój przyjacielu! Ty i ja porozmawiamy więcej w Sharptown - będzie znacznie mniej oficjalnie i bardziej szczerze, obiecuję!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Znowu ognista woda? Tichingitu nie może powiedzieć, że to lubi. Może lepiej sprawdzi się świętowanie abordażu, albo przynajmniej tańce wokół ogniska?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Liczę, że nie dojdzie do tańców wokół ognisk długo przed końcem, a wolałbym trzymać się z dala od abordażu. Dobrze, bądź cierpliwy - zostało tylko trochę, a natychmiast ruszymy do tawerny.";
			else link.l1 = "Obawiam się, że dojdzie do tańców wokół ognisk na długo przed końcem, a ja wolałbym uniknąć abordażu. Dobrze, bądź cierpliwy - zostało już tylko trochę, a natychmiast wypływamy do Sharptown.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kapitanie, gratulacje raz jeszcze! Tichingitu bardziej podoba się ta uroczystość niż poprzednia. Kapitan wie, jak wybierać przyjaciół - tu jest więcej szczerości, mniej obłudy i fałszywych włosów.";
			link.l1 = "Dziękuję, mój przyjacielu! Tylko nie pij ognistej wody - tutaj jest bardzo mocna.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Dziękuję, mój przyjacielu! Wypijmy coś? Wiem, że tego nie lubisz, ale dzisiaj powinieneś spróbować!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu nie lubi ognistej wody, ale jeśli kapitan nalega, dziś można to zrobić. Na twoje szczęście i twoją squaw!";
			link.l1 = "I tobie, Tichingitu! Za twoją przyjaźń i lojalność!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Fajna impreza, kapitanie.";
			link.l1 = "Cieszę się, że jesteś zadowolony.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Kapitanie, wyszedłeś popatrzeć na gwiazdy? Noc zapowiada się bardzo piękna. Tichingitu kocha noc nad morzem. Jest bardzo spokojnie.";
			link.l1 = "Cieszę się, że wciąż stoisz na nogach, przyjacielu! Ja i Nathaniel potrzebujemy twojej pomocy - chłopaki w tawernie nie mają trunków, musimy przynieść kilka skrzyń napojów z magazynu pod stocznią.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Prowadź, kapitanie. Tichingitu podąża za tobą, jak zawsze.";
			link.l1 = "Dobrze, ruszajmy!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Kapitanie, są tam ludzie, i są uzbrojeni, Tichingitu słyszy brzęk ich broni i stają się głośniejsi z każdą sekundą. Nie podoba mi się to. Schowajmy się.";
			link.l1 = "Chodź, kamracie - to jest Sharptown, tutaj nawet do wychodka ludzie chodzą uzbrojeni w pistolety. Hej Nathan... no, cholera! To jedna butelka stracona. Jeśli tak dalej pójdzie, potłuczesz wszystkie butelki! Stań na nogi, do diabła! Ha-Ha!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Kapitanie... ty... Głowa Tichingitu wali jak maszt w burzy. Co się stało?";
			link.l1 = "Chciałem zapytać cię o to samo! Gdzie byłeś przez cały ten czas?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu obudził się godzinę temu z powodu krzyków tej dziewczyny. Biegła wzdłuż plaży prawie naga i krzyczała coś o porywaczach i dzikusach... Ale tu nie ma nikogo oprócz nas. Masz wodę? Nie znowu ognistą, Tichingitu teraz jej nienawidzi?";
			link.l1 = "Była gdzieś flaszka, jeśli jej nie zgubiłem w bitwie... proszę bardzo. Jak udało ci się to zrobić? Jej wuj, miejscowy barman, szuka Indianina, który porwał jego siostrzenicę, i grozi, że oderwie mu pióropusz z pustej głowy. Jak myślisz, o kim on mówi?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu pamiętał. Pomagała Leśnemu Diabłu w karczmie z weselem. Piliśmy ognisty napój z tobą, a Tichingitu chciał więcej. A potem, ta squaw... była taka urocza i... Kapitanie, myślę, że sobie przypomniałem! Tichingitu chciał ją poślubić... Chciał zbudować kanoe i zabrać ją ze sobą... Duchy miłosierdzia! Bardzo źli ludzie przyszli z ognistym napojem. Może to demony albo złe duchy! Tichingitu już nigdy więcej...";
			link.l1 = "Aby ją zabrać? Zbudować kajak?! Ahah, jesteś romantykiem, mój przyjacielu... Ha-ha... ha-ha-ha-ha-ha-ha oh, nie mogę przestać... nie mogę przestać się śmiać!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Kapitanie, Tichingitu ukradł squaw, tak... ale, czy możemy, cóż... teraz się nie żenić? Ona jest... głośna, jak papagallo, i... niezbyt piękna.";
			link.l1 = "Tak, mój przyjacielu, kobiety, bawiące się całą noc, to żałosny widok rano. Nie martw się, bohaterze-kochanku, wymyślimy coś. Chodź, musimy wracać do Sharptown, przegapiłeś swoje świąteczne zakwaterowanie...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "Abordaż? Kapitan wspominał wcześniej o bitwie. Myśli nadal nie słuchają Tichingitu. Co się stało w mieście?";
			link.l1 = "Prawdziwa bitwa na lądzie i na morzu. Działa strzelały całą noc, przypuszczam, że były słyszane nawet w San Jose. Jednak byłeś zajęty inną 'bitwą', wszystko dobrze, rozumiem to... Chodź, opowiem ci wszystko po drodze.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Dzięki, kapitanie... Tichingitu nigdy nie...";
			link.l1 = "Tak, 'ogier z dalekich równin' zdecydowanie nie powinieneś już więcej pić. Idź się wyspać. Ja już też padam z nóg.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Kapitanie, gratulacje raz jeszcze! Tichingitu bardziej podoba się ta uroczystość niż poprzednia. Kapitan wie, jak wybierać przyjaciół - tu jest więcej szczerości, mniej hipokryzji i fałszywych włosów.";
			link.l1 = "I o wiele więcej ognistej wody. Przy okazji, napijesz się ze mną? Wiem, że tego nie lubisz, ale mamy niezwykłą okazję!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu nie lubi ognistej wody, ale jeśli kapitan nalega, dzisiaj jest to możliwe. Na wasze szczęście i waszą squaw! Niechaj kroczycie tą samą ścieżką, a słońce i księżyc niech zawsze na nią świecą.";
			link.l1 = "Dziękuję, mój przyjacielu. Wznieśmy toast za ciebie, Tichingitu! Za naszą przyjaźń!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Wspaniała ... uroczystość, bardzo się cieszę z twojego powodu, Charles. Chociaż nadal cię nie rozumiem... Trzymać w dłoniach bezcenną różę i wymienić ją na... polny kwiat. Ale serce chce tego, czego chce... Bądź szczęśliwy, przyjacielu. Niechaj żyjesz długo i szczęśliwie!";
				link.l1 = "W kwiecie, który trzymasz, najpiękniejsza jest twoja do niego miłość. Bez niej to tylko kawałek więdnącej tkanki. Cieszę się, że wpadłeś, Wasza Wysokość.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "Wspaniały dzień, mój przyjacielu, i wspaniała okazja! Przyjmij moje szczere gratulacje! Byłem żonaty trzy razy, i za każdym razem drżałem jak za pierwszym, ach, młodość...";
				link.l1 = "Monsieur, nie jesteś jeszcze stary, nie zniechęcaj się. Dzięki za przybycie, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Poczekaj, Charles. Źle mnie zrozumiałeś, szczerze się cieszę z całego serca! I tak... tutaj, weź to. Nasz wspólny... Przyjaciel naprawdę prosił, żebyś dostał to dokładnie dzisiaj.";
			link.l1 = "Podejrzewam, że wiem od kogo to jest. Dziękuję i do zobaczenia wkrótce.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "Rozkoszna liturgia, prawda, Charlesie? Jestem szczerze szczęśliwy za Ciebie! Ode mnie osobiście i wszystkich obywateli Basse-Terre - składamy Ci nasze gratulacje Tobie i Twojej... czarującej żonie. Jesteście wspaniałą parą! Niechaj żyjecie długo i szczęśliwie!";
			link.l1 = "Dziękuję, Wasza Łaskawość. Cieszę się, że się spodobało.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Taka wspaniała obsługa, monsieur de Maure, po prostu wspaniała! A panna młoda jest tak... oryginalna w tym stroju. W imieniu wszystkich mieszkańców naszego miasta - przyjmij moje najszczersze gratulacje! Życzę wielu szczęśliwych lat!";
			link.l1 = "Dziękuję, Wasza Łaskawość.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "Tak uroczo - ty i twoja małżonka, monsieur de Maure, wyglądaliście tak niezwykle! Jednak jesteś niezwykłym człowiekiem. Życzę wam długiego i szczęśliwego życia rodzinnego. Niech żyjecie długo i szczęśliwie!";
			link.l1 = "Jestem bardzo wdzięczny, Wasza Łaskawość.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "Dla dobra twojego ślubu warto było przepłynąć Karaiby! Gratulacje, kapitanie, w imieniu mieszkańców wszystkich angielskich kolonii! Ty i twoja narzeczona, przepraszam, już żona, jesteście wspaniałą parą!";
			link.l1 = "Dzięki za wizytę i miłe słowa, pułkowniku!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "A co robi ten żonaty laluś na mojej pirackiej plaży, co?! Powiedz mi, monsieur, co zrobiłeś z moim starym przyjacielem - surowym Piratem Charliem Princem?";
					link.l1 = "Charlie Prince nie żyje, pamiętasz to, Marcus... Ha-ha-ha, chodź tu, morski diable! Cieszę się, że cię widzę! Jak się macie tutaj, wszyscy się zebrali?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "A co robi ten żonaty fircyk na mojej pirackiej plaży, co?! Powiedz mi, monsieur, co zrobiłeś z moim starym przyjacielem - surowym kapitanem Charlesem de Maure?";
					link.l1 = "Ahoy, Marcusie, cieszę się, że cię też widzę! Jak się tu miewacie, czy wszyscy się zebrali?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "A cóż to za żonaty dandys robi na mojej pirackiej plaży, co?! Powiedz mi, monsieur, co zrobiłeś z moim starym przyjacielem - surowym Kapitanem Charlesem de Maure?";
				link.l1 = "Ahoy, Marcus, cieszę się, że cię widzę! Jak się tu miewacie, czy wszyscy się zebrali?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Tak, Diabeł z Lasu przybył zaledwie wczoraj i od razu zaczął dowodzić - więc goście są tutaj i wszystko jest gotowe na uroczystość. Twoja łajba została zauważona w pobliżu raf, a chłopaki nie wytrzymali - wpadli do tawerny i najprawdopodobniej już otworzyli beczkę Jastrzębia. Pośpiesz się, może jeszcze zdążymy wypić kielich - Nathaniel przechwalał się, że to jakiś specjalny rum!";
			link.l1 = "Teraz tak to robimy - prosto ze statku na zabawę! Poczekam na moją lepszą połowę i jesteśmy tuż za tobą, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Tak, Diabeł Lasu przypłynął wczoraj i od razu zaczął dowodzić - więc goście są tutaj i wszystko jest gotowe na uroczystość. Twój statek zauważono w pobliżu raf, a chłopaki nie wytrzymali - rzucili się do tawerny i najprawdopodobniej już otworzyli beczkę Jastrzębia. Spiesz się, może jeszcze zdążymy wypić kielicha - Nathaniel chwalił się, że to jakiś specjalny rum!";
			link.l1 = "Teraz robimy to tak - prosto ze statku na imprezę! Poczekam na moją lepszą połowę i jesteśmy tuż za tobą, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ożeniłam się z Charlesem de Maure - nadal nie mogę się do tego przyzwyczaić... Najpierw Svenson, teraz ty - a potem co? Pastor Marlow, czy Jacques Dobroduszny?";
			link.l1 = "Zapomniałeś o Jastrzębiach. A co z tobą, Marcus? Nie zmęczyło cię bycie samotnym wilkiem morskim?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie i Nathan to starzy znajomi - już się z tym pogodziłem, ale zaskoczyłeś mnie, nie ma co mówić! Jednak uczennica Leśnego Diabła jest piękna - nie ma co mówić, zawsze gotowa użyć słowa i pistoletu, a i każda burza jej niestraszna. Raczej nie mógłbyś znaleźć sobie bardziej godnej kobiety. Masz szczęście, kapitanie - dbaj o nią!";
			}
			else
			{
				dialog.text = "Dannie i Nathan to długotrwała sprawa - już się z tym pogodziłem, ale zaskoczyłeś mnie, nie ma co mówić! Chociaż, jak słyszałem, twoja Mary dużo wie o mieczach i wyraźnie umie ich używać - moje uszanowanie! Prawdziwa wojownicza dziewczyna. Powiem ci w sekrecie, dla takiej dziewczyny sam mógłbym przemyśleć moje przekonania jako kawalera. Masz szczęście, kapitanie - dbaj o nią!";
			}
			link.l1 = "Ja wiem, ona jest cudem i znów jestem w siódmym niebie z radości - tak jak w te dni, kiedy spotkaliśmy się po raz pierwszy!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "A zatem, toast!... Za miłość!... Ale nie za tę, która zmusza nas do przekroczenia progu i podążania ku horyzontowi!... Ale za tę, która czeka na nas w tym progu! Za miłość, która sprawia, że wracamy do niej, nawet z końca świata i złotych gór! Żyj z nią i bądź szczęśliwy!";
			link.l1 = "Świetny toast, Marcusie, dzięki!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Na zdrowie, za twoje wesele, kumplu!";
			link.l1 = "Dzięki, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? To zdecydowanie nie jest dobre...";
			link.l1 = "Marcus, czy myślisz...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "Nie ma czasu! Są za drzwiami! Wszyscy, do broni!";
			link.l1 = "Zaczynamy!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "Nie pamiętam, kiedy ostatnio tak dobrze się bawiłem na przyjęciu! To jeszcze nie koniec! Słyszysz to? Ktoś strzela na zewnątrz! Zasypmy ulice ich krwią!";
			link.l1 = "Stój! Kim do diabła oni są!? I czego, do cholery, w ogóle chcą?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Młody kapitanie de Maure, rzadko spotykałem bardziej szczere powody do toastu. Wznieśmy kielichy - to nie jest zwykły kapuściany napitek. Jest nasączony czarną herbatą z Dalekiego Wschodu i przyprawiony prawdziwymi perskimi przyprawami!";
			link.l1 = "A ja się zastanawiałem, dlaczego pali mnie w gardle, jakbym wypił płynny ołów. No cóż, Nathan, zdrówko...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Zaczekaj, najpierw toast! Hej, panowie, w górę kufle! Dziś nasz przyjaciel i wspólnik Charles de Maure wkracza na ścieżkę życia rodzinnego. Przyjmij od nas najszczersze kondolen.. och, Dannie, proszę, odłóż broń! Gratulacje, oczywiście! Teraz jesteście żaglami tego samego statku, więc prowadźcie ją przez wszelkie burze do najbardziej urodzajnych brzegów!";
			link.l1 = "Dzięki, Nathan, szczerze. Ty i Danielle jesteście przykładem do naśladowania.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Miło to słyszeć. Moja żona i ja może nie jesteśmy najlepszą parą na świecie, ale jesteśmy razem szczęśliwi, a ty zrobiłeś dla nas tak wiele, że jeśli mnie pytasz, jesteś częścią mojej rodziny i będę tu dla ciebie, gdy tylko mnie potrzebujesz. Bądź szczęśliwy i proszę, napij się!";
			link.l1 = "Pijmy zatem! O... ten rum powinien mieć swoje miejsce w arsenale Świętej Inkwizycji. Cholera! Pali aż do końca... aghhh! Uff!... Lubię to!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "Wyglądasz zupełnie jak ja i Dannie dwadzieścia lat temu!";
			link.l1 = "Jeszcze jeden kubek, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Co!? Czy Jan wysłał cię do piwnic po wino? Przejdźmy się, trochę ci pomogę, a świeże powietrze się przyda.";
			link.l1 = "Ale gdzie jest Dannie i "+sld.name+"? Jan powiedział mi, że poszli porozmawiać.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Tak, Dannie wie, że obecność nawet najlepszej dziewczyny z bronią nie da dżentelmenom szczęśliwego czasu na pełny relaks. Więc wysłuchały wszystkich komplementów, jakie otrzymały, i udały się do rezydencji, aby pozwolić chłopakom się zabawić.";
			link.l1 = "Cóż więc, ruszajmy! Udało mi się wypić parę kufli, ale do diabła, teraz naprawdę czas porządnie się upić!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Więc, oto skrzynia. Bierzemy tyle, ile możemy unieść i wracamy, zanim ten stary zrzęda nas tu zamknie.";
			link.l1 = "Wyolbrzymiasz, Nathan. On nie jest taki zły... Czekaj, czy to słyszałeś?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan prawdopodobnie znalazł więcej ludzi i wysłał ich, aby nam pomogli. Cholera!";
			link.l1 = "Chodź, butelki rozbijają się na szczęście. Weź jeszcze jedną i ruszajmy.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "Co się do diabła dzieje, kim są ci dranie? Rozumiesz cokolwiek, Charles?";
			link.l1 = "Nie wiem, Nathan, ale jeden z nich pobiegł po pomoc, a wydaje mi się, że słyszę więcej kroków. Musimy wracać do tawerny!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "Zgładziliśmy tych drani, ale działa grzmią od morza, słyszysz? Mamy tylko dwie załogi gotowe do walki, na fregacie Marcusa i korwecie Jana. Ja, Dannie i inni zeszliśmy na ląd z naszymi chłopakami - w końcu to wesele - więc Centurion odpada. Co z twoim statkiem? Musimy szybko zdecydować, co robić!";
			link.l1 = "Wylądowałem z połową załogi, mam nadzieję, że reszta jest trzeźwa. Ale najpierw muszę znaleźć moją żonę i upewnić się, że wszystko z nią w porządku.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Tak, Danniego też nigdzie nie widać. W takim razie działamy tak - Tyrex i Svenson już pognali do portu, dotrą do swoich statków na łodziach. My idziemy do rezydencji po żony, reszta - niech zorganizują obronę na brzegu. Możesz wysłać kilku swoich oficerów, by zebrali ludzi na twoim statku? Pomoc tam na pewno nie zaszkodzi.";
			link.l1 = "Ruszajmy wszyscy! Liczy się każda sekunda!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Szybciej, na górę! Dannie i "+sld.name+" muszą tam być! A jeśli ci dranie ich skrzywdzili...";
			link.l1 = "Nie waż się nawet o tym myśleć! Na górę! Ruszajmy!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Cholera! Twój towarzysz, on rzucił się prosto na działo, żeby ten drań nie strzelał do dziewczyn!";
			link.l1 = "I dostał kulę... Czekaj, Nathan... on oddycha! Wciąż żyje! Cholera, potrzebuję Gina!"+sld.name+", kochanie, jak się masz?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Jesteśmy cali, Charles! Idę ją rozwiązać. Słyszę strzały w porcie - ty i Nathan musicie tam iść, inaczej Barbazon zniszczy wszystkie nasze statki. Nie traćcie czasu!";
			link.l1 = "Znajdę Gino i przyślę go tutaj, on pomoże ... musi!"+sld.name+", kochani, zostańcie tutaj, zajmijcie się nim, obaj.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, pośpiesz się! cokolwiek zdecydujesz, czas jest teraz wart swojej wagi w złocie! Jeśli statki Jacques'a przedrą się do brzegu, wszystko pójdzie na marne!";
			link.l1 = "Tak, wiem. Cholerny drań!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Szybciej, nie mamy czasu na rozmowy!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Cholera! Wybacz mi Charles. Utknęliśmy na górze, było tam tuzin tych drani... Szkoda, że nie dotarłem na czas, ale widzę, że poradziłeś sobie z sytuacją najlepiej jak mogłeś.";
			link.l1 = "Nie mogę powiedzieć, że to było łatwe, ale, cholera, miałem wielką przyjemność, kiedy zabiłem tego 'dobrego człowieka'! Czas zejść na ląd, Nathan, Nasi ludzie tam na nas czekają!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Tak, musimy odwiedzić twojego indyjskiego chłopca, skończyć tutaj i udać się do Sharptown.";
			link.l1 = "Masz rację, jestem za tobą.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "Przy okazji, znaleźliśmy Marcusa! Był w ładowni, związany i nieprzytomny.";
			link.l1 = "On żyje?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "Jest w kiepskim stanie, ale będzie w porządku. Tyrex jest silniejszy niż gwóźdź do trumny, więc nie martw się, już został przeniesiony na twój statek i poprosił o szablę.";
			link.l1 = "W końcu, dobre wieści! Dobrze, skończmy tutaj i wracajmy.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = " Witaj, Karolu. Niechże spojrzę na ciebie - wypiękniałeś, nie mogę narzekać! Prawie jak Nathan, jakieś dziesięć lat temu! Wejdźże, nie stój na progu, wszyscy właśnie na ciebie czekali!";
			link.l1 = "Dziękuję, Dannie, bardzo się cieszę, że cię widzę! Przyjdę do ciebie i Nathana trochę później, a wtedy porozmawiamy!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, usiądź - Nathan i ja jesteśmy z ciebie tacy dumni! Marcus, Jan i mój mąż przygotowali coś dla ciebie - ale prezenty poczekają. Na razie pozwól, że ci pogratuluję i życzę szczęścia! Twoja wybranka to prawdziwy cud! Powiedz mi, nie udało ci się jej przekonać do założenia białej sukni tam na Martynice, prawda?";
			link.l1 = "Dzięki, Dannie. Tak, z tą suknią wyszło śmiesznie - jestem pewien, że w wyższych sferach nasz ślub wywołał wiele skandalicznych plotek. Wszyscy szczerze odwracali wzrok i udawali, że nic nadzwyczajnego się nie dzieje. Maniery i wszystkie te rzeczy - ale nie przejmuję się plotkami, kocham ją i to jest najważniejsze.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "Masz absolutną rację! Ja również szedłem do ołtarza z mieczem i parą pistoletów za pasem. Ale to było w Port Royal, jeszcze zanim stało się godną rezydencją kolonialną. W tamtych czasach było tyle zabawy, nawet więcej niż na Tortudze pod Levasserem i nikt się nie dziwił... eh. Jednak cały czas gadam - obejdź gości, wszyscy tu na ciebie czekali, daj mi tylko uścisk!";
			link.l1 = "Ach Dannie, jakże miałbym ci odmówić ha-ha! Nie możesz sobie nawet wyobrazić, jak bardzo ja i moja żona cieszymy się, że was widzimy!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "Jesteście piękną parą, Charles!";
			link.l1 = "Dzięki, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, ma rację... nie masz wyboru. Nie wierzę w miłosierdzie Jacquesa Dobrodzieja, jeśli ma do czynienia z Tyreksem i resztą. Wiesz, co należy zrobić.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Nie słuchaj go! Jeśli Kindman zdecydował się na takie szaleństwo, nikogo nie oszczędzi!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Jesteśmy w porządku, Charles! Rozwiążę ją. Słyszę działa w porcie, ty i Nathan musicie tam iść, inaczej Barbazon zatopi nasze statki jak kaczki w beczce. Nie powinieneś tracić ani minuty!";
			link.l1 = "Znajdę Gino i wyślę go tutaj, on pomoże ... on musi, do diabła! "+sld.name+", kochanie, zostań tutaj, opiekuj się Tichingitu.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, nie!!!";
			link.l1 = "Złapał chwilę i rzucił się do działa, by cię osłonić, Dannie... "+sld.name+", kochanie, jak się masz?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Tak, Charles, on żyje! Serce ledwo bije, ale on żyje! Co powinniśmy zrobić?!";
			link.l1 = "Potrzebujemy Gina, natychmiast! Znajdę go i wyślę tutaj, on pomoże... musi!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, nie mamy czasu! Jeśli statki Jacquesa przedrą się na brzeg, wszystko pójdzie na marne! Mój mąż ... zrobił to, co musiał. Teraz twoja kolej. Zostanę z nim. Wy dwoje powinniście iść i znaleźć Gina!";
			link.l1 = "Tak, wiem. Cholerny drań, zapłaci za to!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "W końcu jesteś! Czy wszyscy są w porządku?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "Jesteśmy cali, Dannie, nie martw się. Jacques nie żyje, jego statki spoczywają na dnie. Jak się ma Tichingitu?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "Jesteśmy w porządku, Dannie, nie martw się. Jacques nie żyje, jego statki są na dnie. Jak się ma Nathan?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Ma się dobrze! Twój włoski doktor to geniusz! Nathan śpi na górze, ale według Gino nic mu nie grozi. Tydzień lub dwa w łóżku, czerwone wino, i jak powiedział 'wizyta damy dobrze do niego usposobionej' ahem... Ogólnie rzecz biorąc - wszystko jest dobrze, znów nas uratowałeś, Charles, jak mogę ci podziękować?";
				link.l1 = "To Nathaniel uratował moją żonę i ciebie. I będę mu za to zawsze wdzięczny. Nawet sobie nie wyobrażasz, jak się cieszę, że wraca do zdrowia. Niech odpoczywa, sprawdzę, co u ciebie później.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "U niego wszystko w porządku, kula przeszła na wylot, a nasz chirurg z 'Centuriona' był niedaleko. Ukrywał się przed tym całym zamieszaniem. Więc Nathan przeżyje, parę tygodni w łóżku - mały problem!";
				link.l1 = "Dannie, zasłonił moją żonę i ciebie przed kulą i na zawsze będę mu za to wdzięczny. Nawet nie możesz sobie wyobrazić, jak bardzo się cieszę, że dochodzi do siebie. Niech odpocznie, sprawdzę, jak się masz, później.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Oczywiście! Ale, muszę cię opuścić, muszę iść do mojego męża... Nie masz nic przeciwko, jeśli pożyczymy twojego przyjaciela? Kiedy Nathan wyzdrowieje, sama przyprowadzę go na Antiguę. Centurion jakimś cudem przetrwała, potrzebuje tylko zrekrutować nową załogę.";
			link.l1 = "Dobrze, Dannie, pozdrów Gino i Nathana. Powinienem iść.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Oczywiście, Charles, ale... Mam złe wieści. Ten Włoch, Guineili, który był na twoim weselu... Jego ciało znaleziono w pokoju w tawernie. Przykro mi, Charles.";
			link.l1 = "Co? Gino?! Nie! Jak?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "Nie wiem, pewnie jeden z tych drani, którzy przeszli przez katakumby i zaatakowali miasto. Najwyraźniej ukrywali się tam, czekając na odpowiedni moment do ucieczki, i znaleźli go...";
			link.l1 = "Cholera! Nie, nie wierzę...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "Przykro mi, Charles. To była cholernie krwawa jatka, a on nie był wojownikiem... Jeśli chcesz, wyślemy jego ciało na twój statek, zabierzesz go do domu i pochowasz, jak należy. Naprawdę mi przykro...";
			link.l1 = "Dzięki, Dannie. Wydaj rozkaz, aby załadować ciało na statek. Muszę już iść... Muszę pomyśleć. I pozdrów Nathana.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Ma się dobrze! Twój włoski lekarz to geniusz! Śpi w pokoju na górze, a Gino się nim opiekuje. Mówi, że 'tydzień lub dwa i będzie dobrze'.";
				link.l1 = "Wspaniałe wieści! Chyba nie mogę go odwiedzić teraz?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "Przykro mi, Charles. Znalazłem naszego chirurga z Centuriona, ale on nic nie mógł zrobić... Twój przyjaciel zmarł parę godzin temu.";
				link.l1 = "Tichingitu?! Nie! Nie wierzę!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nie, Włoch stanowczo zakazał go niepokoić, niech odpoczywa, a Gino powinien odpocząć po tych wszystkich zmartwieniach. Nawet powiedziałem "+sld.name+" wyjść na spacer, gdy dowiedzieliśmy się, że wszystko będzie w porządku\nI jeszcze jedno... twój przyjaciel, osłonił mnie przed kulą. Nawet nie wiem, jak mu podziękować, powiedz mu, że od teraz jest także częścią naszej rodziny, a ty - znowu nas uratowałeś, Charles!";
			link.l1 = "Wszystko dobre, co się dobrze kończy, Dannie. Idź do Nathana, czeka na ciebie, a ja tu sobie zrobię małą przerwę i poszukam mojego "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Przykro mi, zrobiłem wszystko, co mogłem, i "+sld.name+", też. Osłonił nas przed tą kulą i nigdy tego nie zapomnę, uwierz mi.";
			link.l1 = "... Dawno temu powiedział, że gotów jest umrzeć za mnie... Chyba nigdy nie wiedział, że poświęci swoje życie dla nas wszystkich... a teraz jest bohaterem i będę go pamiętał jako nikogo mniej... Gdzie jest "+sld.name+"? Czy ona jest w porządku?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "Nie mogę tak powiedzieć... To znaczy, fizycznie tak. Ale... wiesz... Powiedziała, że wyszła na spacer, żeby oczyścić umysł. Pewnie zobaczyła twój statek i wkrótce wróci.";
			link.l1 = "Klątwa na ciebie, Jacques Barbazon... Powinniśmy go zabić wcześniej!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Zaczekaj... to jeszcze nie wszystko. Ten Włoch, Guineili, tak? Ten cichy młodzieniec. Został... znaleziono jego ciało w tawernie... Nie wiem, pewnie jeden z tych drani, którzy przeszli przez katakumby i zaatakowali miasto. Podobno ukrywali się tam, szukając momentu na ucieczkę, i znaleźli go...";
			link.l1 = "I Gino też?! Dziś to naprawdę deszczowy dzień...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "Przykro mi, Charles... Jeśli chcesz, wyślemy ich ciała na twój statek, zabierz chłopaków do domu i pochowaj ich, jak należy. Naprawdę mi przykro...";
			link.l1 = "Dzięki Dannie. Zrób to... Powinienem iść... Muszę... pomyśleć.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, czy możesz sobie wyobrazić, ile dziewczęcych serc złamałeś tym swoim ślubem? Tak, połowa dziewczyn z archipelagu musiała opłakiwać twój ślub, haha!";
			link.l1 = "Cóż mogę zrobić - potrzebowałem tylko jednej i ją zdobyłem. Ale jest za wcześnie, by dziewczyny się martwiły, bo wciąż mają ciebie, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "I to prawda! Skończymy tutaj, a ja natychmiast się nimi zajmę, do diabła! Chodź, Charles, wypijmy za twoje szczęście i życie rodzinne. Tak więc, jak to mówią, żyli długo i szczęśliwie!";
			link.l1 = "Dziękuję, mój przyjacielu!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "Za szczęśliwe życie rodzinne, ha-ha!";
			link.l1 = "Na zdrowie!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, czy potrafisz sobie wyobrazić, ile dziewczęcych serc złamałeś tym swoim ślubem? Tak, połowa dziewczyn z archipelagu musiała opłakiwać twój ślub, haha!";
			link.l1 = "Co mogę zrobić - potrzebowałem tylko jednej i ją zdobyłem. Ale dla dziewczyn jeszcze za wcześnie, by się martwić, bo wciąż mają ciebie, Bernard.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "A to jest prawda! Skończymy tutaj, a ja natychmiast się nimi zajmę, do diabła! Chodź, Charles, napijmy się za twoje szczęście i życie rodzinne. Tak więc, jak mówią, żyli długo i szczęśliwie!";
			link.l1 = "Żyli długo i szczęśliwie!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "Dla szczęśliwego życia rodzinnego, ha ha!";
			link.l1 = "Wielki toast!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, więc ty też się ożeniłeś i stałeś się nudny, jak nasz stary Nathan! Gorące romanse i cała reszta to teraz przeszłość, co? Wzorcowy mąż!";
			link.l1 = "Zaczekaj, Bernardzie! Moja żona nie jest jedną z tych, które będą się nudziły siedząc pod oknem rodzinnego wraku! Jedyną rzeczą, która się zmieni, jest pełnia sakiewek dziewcząt z burdelu odtąd aż do Curaçao!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Nie wielka strata, powiadam! Lepiej mieć jedną złotą monetę niż worek nikli. Napijmy się! Na zdrowie tobie i twojej żonie! Strzeż swego złota i bądź szczęśliwy!";
			link.l1 = "Dzięki Bernard. O, to naprawdę mocny rum. Uff!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "Do twojej narzeczonej, to znaczy, już żony!";
			link.l1 = "Dziękuję!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "Jesteś w samą porę, Charles, dzięki!";
			link.l1 = "Co tu za zabawa? Myślałem, że już ładujesz się na statki w porcie.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus zostawił mnie, bym zorganizował obronę na brzegu. Brakuje nam ludzi, chłopaki w porcie potrzebują prochu strzelniczego. Pomyślałem, że wpadnę, wezmę parę beczek... a tu te łotry. Ha, schowali się, zgaduję, chcieli przeczekać albo kogoś obrabować. A ja wciąż pełen rumu od Hawka, więc bez ciebie, nie wiem, czy bym jeszcze żył, czy nie.";
			link.l1 = "Zawsze jesteś mile widziany. Dobrze, Bernardzie, upewnij się, że miasto jest zabezpieczone, a ja muszę iść, bądźcie bezpieczni!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kapitanie, pozwól mi serdecznie pogratulować tobie i twojej ukochanej w ten pomyślny dzień! Bądźcie szczęśliwi i dbajcie o siebie nawzajem!";
			link.l1 = "Dzięki, Gino. Cieszę się, że zdecydowałeś się przyjść! Mam nadzieję, że lokalny... koloryt nie przeszkadza ci?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "To jest... bardzo pouczająca podróż. Muszę przyznać - od dawna nie opuszczałem Antigui, a w tym towarzystwie nie jest mi łatwo czuć się swobodnie. Ale zawsze potrafiłeś zrozumieć ludzi, więc postaram się zachować spokój, bo ci ufam.";
			link.l1 = "Może potrzebujesz wypić coś mocniejszego? Zrelaksuj się i znajdź kogoś do pogawędki?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Dziękuję, kapitanie, mam już dość rozwodnionego wina. Alkohol, muszę cię ostrzec, nie jest zbyt dobry dla wątroby i możliwie serca. Jeśli chodzi o rozmowy, próbowałem omówić lecznicze właściwości Chirik-Sanango z tym dżentelmenem tam, jest to również nazywane Manaka. Tubylcy z Maine używają go do...";
			link.l1 = "Pozwól, że zgadnę - tamten dżentelmen nie potrafił prowadzić rozmowy? Gino, dla mnie i tylko dzisiaj - spróbuj rumu, który Jan tam nalewa przy ladzie. Jeśli zgadniesz wszystkie jego składniki, Nathaniel Hawk, tam, będzie niezwykle pod wrażeniem. Jestem pewien, że również będzie zadowolony z twojego towarzystwa, podobnie jak Svenson, człowiek przy ladzie, obaj szanują wykształconych ludzi.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "Za twoje zdrowie i zdrowie twojej uroczej małżonki!";
			link.l1 = "Dzięki, przyjacielu!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Kapitanie, to ty, dzięki Bogu! Ci zamaskowani ludzie, widziałem ich i schowałem się tutaj, a oni próbowali wyważyć drzwi...";
			link.l1 = "Nie martw się, Gino, nikt cię już nie skrzywdzi. To wielkie szczęście, że cię znalazłem, potrzebuję twojej pomocy. Mój przyjaciel jest ranny - został postrzelony i stracił dużo krwi. Musimy się spieszyć!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Strzał... krew... dobrze, kapitanie. Gdy przychodziłem, zabrałem ze sobą skrzynkę kempingową ze wszystkimi narzędziami na wypadek obrażeń. Prowadź mnie do niego, zobaczę, co da się zrobić. A ci... zamaskowani ludzie, może ukryli się gdzie indziej?";
			link.l1 = "Jestem pewien, to byli ostatni. Gino, w porcie trwa bitwa i muszę tam natychmiast iść. Musisz dotrzeć do rezydencji sam, to niedaleko. Duży dom jest za rogiem - nie przegapisz go. Nie bój się - ulice są pełne naszych ludzi, a teraz pośpiesz się, błagam cię!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Kapitanie, pozwól, że z całego serca pogratuluję ci i twojej ukochanej w tym szczęśliwym dniu! Bądźcie szczęśliwi i dbajcie o siebie nawzajem.";
			link.l1 = "Dzięki, Gino. Cieszę się, że zdecydowałeś się przyjść! Mam nadzieję, że podróż przebiegła gładko?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = " Wszystko w porządku, kapitanie, dzięki za troskę. Muszę powiedzieć - nie byłem poza Antiguą od dłuższego czasu, a wśród elity... nie czuję się zbyt komfortowo. Ale powód przybycia nie pozostawił mi wyboru. Przy okazji - obsługa była doskonała, jestem bardzo zadowolony z was obojga! Panna młoda w tym stroju jest urocza - czy to nowa moda? Okazuje się, że zostaję w tyle z życiem, ale podoba mi się to, naprawdę.";
			link.l1 = "Moda... W pewnym sensie tak, a przynajmniej wkrótce się stanie. Dobrze, baw się dobrze, Gino, a jeśli szlachetni rozmówcy cię znudzą, to przyjdź do portu. Cała załoga jest w tawernie. Chłopaki będą się cieszyć, że cię zobaczą.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Kapitanie, raz jeszcze gratuluję tobie i twojej pięknej żonie! Długich i szczęśliwych lat razem!";
			link.l1 = "Dzięki, Gino. Cieszę się, że przyszedłeś! Mam nadzieję, że lokalny... koloryt, ci nie przeszkadza?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "To towarzystwo nie jest dla mnie łatwe, by czuć się swobodnie. Ale zawsze potrafiłeś wybierać ludzi, więc spróbuję zachować spokój, bo ci ufam..";
			link.l1 = "Może potrzebujesz czegoś mocniejszego do picia? Zrelaksuj się i znajdź kogoś do pogadania?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Dziękuję, kapitanie, mam już dość rozwodnionego wina. Alkohol, muszę cię ostrzec, nie jest zbyt dobry dla wątroby i być może serca. Co do rozmów, próbowałem omówić lecznicze właściwości Chirik-Sanango z tamtym dżentelmenem, nazywany jest również Manaka. Tubylcy z Maine używają go do...";
			link.l1 = "Pozwól, że zgadnę - ten gentleman nie mógł podołać dyskusji? Gino, dla mnie i tylko dziś - spróbuj rumu, który Jan tam nalewa przy ladzie. Jeśli zdołasz odgadnąć wszystkie jego składniki, Nathaniel Hawk tam będzie niezwykle zaimponowany. Jestem pewien, że będzie zadowolony z twojego towarzystwa, jak i Svenson, człowiek przy ladzie, obaj szanują wykształconych ludzi.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = " 'Samotny teraz w obcym kraju, czując się obcy, w ten jasny dzień święta podwójnie tęsknię za moimi krewnymi' ";
			link.l1 = "Longway, nigdy bym nie pomyślał, że jesteś mistrzem słowa!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Przepraszam, Kapitanie, dużo myślałem. To są słowa Wang Wei - poety, który żył w okresie dynastii Tang, która rządziła dawno temu w mojej ojczyźnie.";
			link.l1 = "Te słowa są tak piękne. Mam nadzieję, że pewnego dnia znów ujrzysz swoją ojczyznę...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''Czy można ręczyć i wiedzieć, że pod łukiem tajemniczych kamiennych płyt nie da się, próbując, znaleźć przejścia, za którym znajduje się dolina U-lin?'\nNie, Kapitanie, wiesz o tym - Longway nie zamierza wracać do domu. Teraz tu jest mój dom i mamy tutaj dziś wielkie wydarzenie! Przesyłam najlepsze życzenia tobie i twojej pięknej narzeczonej! Niech wasze szczęście będzie tak długie jak rzeka Jangcy, usiana diamentami gwiazd, pomiędzy perłami lotosu.";
			link.l1 = "Dziękuję, mój stary przyjacielu. Twoje słowa są nie mniej piękne niż słowa Wang Wei.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Napiijmy się, Kapitanie! Ten rum zabiera smutek i odświeża radość nie gorzej niż maotai.";
			link.l1 = "Na zdrowie, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Wspaniałe wesele, kapitanie!";
			link.l1 = "Pij i baw się dobrze!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Uderz mnie kartaczami łańcuchowymi! Wszyscy nasi ludzie gratulują ci! Jak poszedł serw?";
				link.l1 = "Wszystko w porządku, Charlie! Teraz jestem oficjalnie żonaty i szanowany, a moim pierwszym oficerem jest teraz madame de Monper.";
			}
			else
			{
				dialog.text = "Uderz mnie szrapnelem, co za wydarzenie, kapitanie! Prawie każdy baron Bractwa tutaj! Myślę, że każdy hiszpański purytanin wyobraża sobie piekło w ten sposób! A rum, to coś wyjątkowego, szrapnel do mojej beczki!";
				link.l1 = "Tak, ludzie tutaj nie są najbardziej praworządnymi obywatelami, ale my sami nie jesteśmy aniołami, Charlie, a każdy z tych ludzi jest mi drogi na swój sposób.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "To cudowne, łańcuchowy strzał w mój zadek! Kapitanie, mam na myśli, że to świętowanie jest na twoją cześć, cóż, ja... ja, gratuluję, mam na myśli... także... Szczęścia i... to, nie jestem dobry w przemówieniach. Ale musisz wiedzieć, że wszyscy cię kochamy i będziemy cię śledzić nawet do piekła, kapitanie!";
				link.l1 = "Dziękuję, stary przyjacielu.";
			}
			else
			{
				dialog.text = "Poczekaj, to znaczy... Co ja w ogóle mam na myśli, łańcuch do mojego tyłka?! Kapitanie, miałem na myśli, że ten dzień jest dla twojej chwały, cóż, ja... Gratuluję ci... a także... Życzę ci szczęścia i... i przepraszam kap, mogę być trochę zbyt pijany, żeby wygłosić przemowę, łańcuch do mojej szyi, nie byłem trzeźwy od dłuższego czasu ha-ha-ha!";
				link.l1 = "Hah! W porządku... dziękuję, stary przyjacielu.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ach! I tak, kapitanie, przyjmij to, proszę. Dla ciebie i twojej damy. Trzymałem te kamienie na czarną godzinę... Rozumiem, że nie brakuje ci złota, ale nie będą zbędne, prawda?";
			link.l1 = "Charlie, jesteś prawdziwie hojna dusza, a te szmaragdy będą świetnie wyglądać w kolczykach rodziny madame de Monper!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = " Cóż, wznieśmy toast za to, łańcuchowa kula do mojej... hm. Po prostu bądźcie szczęśliwi, zarówno ty, jak i twoja piękność, kapitanie!";
			link.l1 = "Zrobimy to, Charlie!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Wspaniałe wesele, kapitanie!";
			link.l1 = "Pij i baw się dobrze!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Nie myślałem nigdy, kapitanie, że zobaczę cię poślubionego. Zwykle ścieżka, którą obraliśmy, prowadzi samotną drogą prosto do samotnego grobu. W mojej pamięci jesteś pierwszym, który zdołał z niej zejść. To warte dodatkowego toastu, czyż nie?";
			link.l1 = "To jest to, kumplu! I naprawdę, cieszę się, że ta część mego życia została za mną. Na zdrowie!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Zdrowie wasze i długie, szczęśliwe życie razem! Cholera, patrząc na was, przypominam sobie, że ja sam kiedyś byłem żonaty.";
			link.l1 = "Ty? Żonaty? Ciekawą rzecz mi opowiadasz! Ale co się stało?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "Co, myślisz kapitanie, że zawsze byłem starym cyklopem pachnącym prochem i krwią? Ależ nie. Madame Tonzag ona... ona mnie kochała, jak sądzę. A potem, zdarzyła się nieprzyjemna historia. W której para Tonzag zginęła, a tylko Łysy Gaston z zestawem blizn zdołał przetrwać.";
			link.l1 = "Przykro mi, Hercule, nie wiedziałem...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Zapomnij o tym, kapitanie, ta historia wydarzyła się dawno temu. Ale teraz, patrząc na ciebie, myślę, że moja opowieść wciąż może mieć dobre zakończenie. Więc, napijmy się za to!";
			link.l1 = "Chodźmy, kumplu. Wiesz - odkąd cię poznałem, zawsze patrzyłem na ciebie jak na własnego ojca, więc może pewnego dnia będziesz miał szansę zostać pradziadkiem. W każdym razie, zdrowie! Muszę zająć się resztą, pogadamy później.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Wielka uroczystość, Kapitanie!";
			link.l1 = "Pij i baw się dobrze!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Oto nasz kapitan! Gratulacje, ty i twoja żona jesteście piękną parą! Niech żyjecie długo i szczęśliwie!";
			link.l1 = "Dziękuję, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "Wydaje się, że jesteś zbyt trzeźwy na własne wesele, kapitanie. Chciałbyś to naprawić? Wziąłem butelkę doskonałego sherry w barze. Mieszanka z lokalnym rumem pasuje idealnie!";
			link.l1 = "Chciałbym, ale ktoś musi tu pilnować spraw. Inaczej, w "+sTemp+" nie tylko tawerna będzie brakować, gdy nadejdzie poranek.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Wyborne jedzenie i wyborny rum, kapitanie! Zdrowie twoje i twojej młodej żony!";
			link.l1 = "Dzięki!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Młodzi ludzie, dlaczego się włamujecie, mogę zapytać? Stocznia jest zamknięta, czyż nie jest to zauważalne? Wróćcie jutro.";
			link.l1 = "Panie, przepraszam za niepokojenie, przejdziemy tylko przez lochy. Są zapasy na wesele, w tawernie prawie skończyły się napoje.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "O, Charles de Maure i Nathan Hawk osobiście! Świętujecie chyba czyjeś wesele, prawda? Dobrze - idźcie po wasze paliwo. Młodzi powinni się bawić - to prawo w każdym czasie. Tylko nie hałasujcie butelkami w drodze powrotnej - idę spać!";
			link.l1 = "Dziękujemy, panie, będziemy cisi jak najspokojniejsza rzeka.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "Chodźże, nie stój, idź! No, kapitanie, jesteś ze wszystkiego zadowolony?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "Co do cholery?! Jacques powiedział 'Nikt tu nie schodzi'! Hugo - wracaj, zawołaj innych, oczyścimy drogę. Zabijcie ich chłopaki!";
			link.l1 = "Cholera!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Chłopcy, zapomnijcie o skrzyniach, mamy gości!";
			link.l1 = "Myślałem, że bękarty takie jak ty zginęły z Jackmanem. Dobrze, zakończmy to!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Kurwa... Zostaliśmy znalezieni! Alarm!";
			link.l1 = "Z drogi, dupku!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Panie de Maure, dobry wieczór, czy to już prawie ranek? Proszę wejść, usiąść.";
			link.l1 = "Angerran De Chievous! Toż to nie dziwota, że cię widzę! Nędznik, co tylko z kobietami potrafi walczyć! Też je związałeś?! Teraz dokończę to, co zacząłem w tamtym pojedynku na Martynice!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Spokojnie, młody człowieku, widzisz tę broń? Są dwa lufy. Może nie jestem najlepszy w szermierce, ale strzelam całkiem celnie - odłóż swój miecz, albo przegapisz kilka pięknych dam, zapewniam cię.";
			link.l1 = "Draniu... Cholera cię.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "I ty, monsieur piracie, odłóż swoją broń również, właśnie tak, tak. A teraz - usiądź, możesz nalać wina - tam na stole. Musimy poczekać chwilę, aż monsieur Barbazon skończy rozbijać statki twoich przyjaciół, pirackich baronów. Potem zdecydujemy, jak ty i ja rozwiążemy nasze... hm, nieporozumienia.";
			link.l1 = "Rozstrzygnąć nieporozumienia? A jakże? Chcesz pojedynku?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Nie bądź taki śmieszny, Charles. Ty i madame Botot przysporzyliście mi wiele kłopotów, i zamierzam wam się odpłacić w pełni. Chociaż ona sprawiła mi o wiele więcej problemów niż ty... jednak jeśli ty i ten imponujący monsieur pirat usiądziecie spokojnie, to daję wam słowo honoru - wasze żony pozostaną przy życiu. Myślę, że w hiszpańskich koloniach na Maine takie niewolnice są cenione. Nawet nieoficjalnie. Ale to wciąż życie, prawda?";
			link.l1 = "Angerran, jesteś tchórzem, skurwysynem i... Cholera, nie ma jeszcze odpowiednich słów dla ciebie w żadnym języku!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "Wiesz o tym, nie masz wyboru. Mogę tylko obiecać, że będzie szybko. Więc, jeśli kochasz te kobiety - zachowuj się, ocal ich życie i ulżyj swojemu losowi. A tak, zamknij drzwi, jeśli to nie jest dla ciebie trudne. Dziękuję.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Tak wojownicze damy. Wciąż proszę was o rozwagę. Nigdy nie lubiłem zabijać kobiet.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Cholera...";
			link.l1 = "Zgiń, bękarcie!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Kapitanie Charles de Maure, baronie Hawk - cóż za miła niespodzianka! Pozwólcie, że się przedstawię - Mauritz Dussak, tak się nazywam.";
			link.l1 = "Zejdź mi z drogi, draniu! Gdzie jest moja żona?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Spokojnie, panowie! Widzicie tę broń? Są dwa lufy. Nie bez powodu mnie tak przezywają - kocham szable, owszem... ale strzelam też dobrze, uwierzcie mi. Opuście swoje miecze, bo inaczej stracicie parę swoich dam!";
			link.l1 = "Zarżnę cię jak świnię, szumowino...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "Ale już będziesz wdowcem. Nie chcesz tego? To się uspokój i odłóż broń. Baron Hawk, proszę, zamknij drzwi. A my się uspokoimy i poczekamy chwilę, aż Jacques Barbazon w porcie skończy z przywódcami Bractwa.";
			link.l1 = "I co dalej? Przytulimy się i pójdziemy razem w zachód słońca?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "Nie sądzę. Za twoją niewolę Jacques obsypie mnie złotem, a z odrobiną szczęścia może zostanę baronem. Co do twoich kobiet, być może je uwolnimy, ale co do ciebie - niestety... Jeśli będziesz miał szczęście, poproszę o prawo, aby zabić cię osobiście, kapitanie. Jesteś sławnym szermierzem - byłoby interesujące cię sprawdzić. Wiesz, ja także uważam się za mistrza.";
			link.l1 = "Mistrz włamywania się do domów nocą i wiązania półprzytomnych kobiet? Jesteś robakiem, co więcej - śmierdzącym robakiem!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Posłuchaj, madame, nigdy nie zabijałem kobiet, nie każ mi zaczynać, dobrze? Denerwujesz kapitana i swojego męża... Cholera!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Merdo...";
			link.l1 = "Zdychaj, bękarcie!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Pierdolony Francuz, nie było żadnej szabli ani kuli?!";
			link.l1 = "Wiesz, Jacques, mam oba dla ciebie. Szczerze mówiąc, prawie żałuję, że zostawiłem cię przy życiu, kiedy dowiedziałem się o twoich sztuczkach z Jackmanem. Ale teraz zamierzam to naprawić.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "Jesteś taki odważny tylko wtedy, gdy idziesz z tłumem swoich ludzi? Zmieńmy sytuację! Z baronami poradzę sobie później, ale ty stąd żywy nie wyjdziesz, szczurze!";
			link.l1 = "Oczekiwane...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Kapitanie, pomóż, ten dzikus, on mnie porwał! Ja... muszę wrócić do domu - wujek prawdopodobnie już przewrócił całe miasto do góry nogami!";
			link.l1 = "Spokojnie, piękna, wszystko będzie dobrze. Odejdź na bok, muszę porozmawiać z twoim 'dzikusem'.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Dziękuję, kapitanie! Uratowałeś mnie! Kiedy obudziłem się dziś rano na tej plaży, nie mogę uwierzyć, że miałam poślubić tego dzikusa, on...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Tak, poranek jest surowym młotem dla nocnego kryształu nadziei. Zrozum. Lecz on jest z plemienia Muscogue i żyje według surowych praw swojej ziemi. Porwał cię za twoją zgodą i spędziliście razem noc. Więc teraz, w oczach jego Bogów, jesteście mężem i żoną. Chodźmy spakować twoje rzeczy, a ja załatwię kwestię okupu z twoim wujem.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "Przepraszam za to. Tichingitu żyje według praw swojego plemienia, ale jest dobrym człowiekiem. Proszę, zapomnij tę historię o porwaniu.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Żona? W oczach jego Bogów?! Nie, kapitanie, błagam cię, ratuj mnie przed tym! To była tylko... przygoda, był tak szarmancki i miły, nie jak ci prostacy... Ale poślubić? Jestem za młoda, by przenieść się do chaty do dzikusa!";
			link.l1 = "On jest moim oficerem i najlepszym przyjacielem, więc nie martw się, dobrze mu płacę, a ty będziesz mieć najlepszą chatę, jaką kiedykolwiek chciałeś. Tichingitu jest dobrym myśliwym, zdobędzie dla ciebie jedzenie, a ty urodzisz i będziesz opiekować się dziećmi.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Dzieci? Zorganizować jedzenie?! Nie kapitanie, błagam, nie rób mi tego!";
			link.l1 = "Cóż, może zdołam go przekonać. Ale to nie będzie łatwe. Plemię Muskogue bardzo poważnie podchodzi do takich spraw, jeśli ktoś się dowie, że porwał squaw i się nie ożenił...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "Musisz spróbować, proszę! Nikomu nie powiem, nikt się nie dowie! Okłamię wujka, to nie pierwszy raz!";
			link.l1 = "Dobrze, powinnaś iść, piękna squaw. Spróbuję trzymać mojego przyjaciela z daleka.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "Ukradł mnie jak... jak kozę z obory! Powiem wszystkim! Wujek go zabije! On jest straszny, gdy się złości! Kiedyś rabował hiszpańskie statki - z nim nie ma żartów!";
			link.l1 = "Dobrze, cicho, piękna damo, cicho. Może dwadzieścia tysięcy 'powodów' do przebaczenia będzie bardziej wymowne niż moje słowa? A może powinienem je przekazać twemu wujowi, jak okup za żonę? W końcu wszyscy są na wyspie, prawda? Jutro możemy zorganizować kolejne wesele...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "Nie nie, kapitanie, czekaj! Przekonałeś mnie. Wymyślę coś, żeby mój wujek się nie gniewał. Żegnaj! I do widzenia tobie, mój rumaku z dalekich równin! Zobacz mnie następnym razem, gdy odwiedzisz...";
			link.l1 = "Zgadza się. Cieszę się, że się zgadzamy. Biegnij do domu, piękności.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "„Cóż, kapitanie, jesteś zadowolony ze wszystkiego? Najlepszy rum, żeberka jagnięce, szynki wieprzowe, a nawet doskonałe wino z moich osobistych zapasów dla twojego przyjaciela naukowca! I - moje gratulacje dla ciebie i twojej pięknej żony!”";
			link.l1 = "Dzięki! Muszę przyznać, że wszystko zorganizowałeś perfekcyjnie. Mam nadzieję, że masz wystarczające zapasy rumu w swoich piwnicach, bo poranek jest daleko.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Nie martw się tym, jeśli beczki pokażą dno, wyślę pomocnika do magazynu w porcie. Baw się dobrze, monsieur, i nie martw się o nic.";
			link.l1 = "W porządku, "+npchar.name+"  Wtedy pójdę do moich gości.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "Czego sobie życzysz, kapitanie? Smażone żeberka, wędzona szynka czy mostek? Może wino dla twej lepszej połowy?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Za zdrowie kapitana i jego żony!","Niech żyje kapitan długo i szczęśliwie!","Długiego życia i szczęścia dla was obojga!"),LinkRandPhrase("Wiwat dla kapitana i jego piękności!","Niech szczęście podąża za kapitanem i jego małżonką przez całe ich życie!","Pomyslnych wiatrów w życiu rodzinnym, kapitanie!"));
			link.l1 = LinkRandPhrase("Dzięki!","Dziękuję!","Na zdrowie!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Oszalałeś? Chciałeś się zabawić w rzeźnika? Wszyscy piraci są na ciebie wściekli, kumplu, więc lepiej opuść to miejsce.","Wydaje mi się, kumplu, że zwariowałeś. Chciałeś trochę rozprostować ręce? Bez urazy, ale nie masz tu nic do roboty. Zjeżdżaj!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomoż mi rozwiązać problem...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ach, czekałem na twoją wizytę, szefie. Jan Svenson ostrzegł, że z pewnością przybędziesz, by sprawdzić, jak się mają sprawy w Le Francois. Wziąłem wszystko w swoje ręce i przysięgam na pioruny, ta wioska będzie żyła lepiej niż z przeklętym Kindmanem, niech diabły mają z nim uciechę w najciemniejszych lochach piekła!";
					link.l1 = "Jesteś Jean David, prawda? Svenson mówił coś o mojej działce...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" szefie. Wszystko w porządku w Le Francois, jak zawsze. Dlaczego przybyłeś? Czy mogę ci w czymś pomóc?";
					link.l1 = "Zajrzałem tylko, żeby sprawdzić, jak się sprawy mają.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "Co z moją działką?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" kamracie. Dlaczego przyszedłeś? Czy mogę ci w czymś pomóc?";
				link.l1 = "Tylko wpadłem, żeby się przywitać.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "Do usług, szefie! Co do udziału - piątego dnia każdego miesiąca zostanie odjęta część złotych monet z czynów naszych chłopaków, i będzie na Ciebie czekać tak długo, jak będziesz potrzebować. Od przyszłego miesiąca możesz po to przyjść.";
			link.l1 = "Świetnie!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "I ja zajmę się resztą. Leśny Diabeł powiedział, że nie będziesz miał czasu zajmować się takimi drobnostkami jak Le Francois...";
			link.l1 = "Powiedziano ci słusznie. Dobrze, Jean, polegam na tobie, mam nadzieję, że mnie nie zawiedziesz.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Wszystko będzie dobrze, szefie. Wszystko jest pod kontrolą tutaj, ha-ha, i niech mnie piorun trzaśnie, jeśli coś schrzanię!";
			link.l1 = "Dobrze, do zobaczenia!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Czekamy na ciebie, szefie. W tym czasie zebraliśmy dla ciebie "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+" Weź to.";
			link.l1 = "Słuchaj, nieźle. Dobra robota, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "Robię, co w mojej mocy, szefie. Wróć w przyszłym miesiącu albo kiedy chcesz - twoje pieniądze będą u mnie bezpieczne.";
			link.l1 = "W porządku, do zobaczenia, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Rozwiązać problem? Czy masz jakiekolwiek pojęcie, co narobiłeś? W każdym razie, przynieś mi milion pesos, a przekonam chłopaków, by zapomnieli o twoim uczynku. Jeśli ci się to nie podoba, to możesz iść do diabła.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Dobrze, jestem gotów zapłacić.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Zrozumiałem. Odchodzę.";
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
            dialog.text = "Dobrze! Uznaj się za oczyszczonego. Ale mam nadzieję, że nie zrobisz już takich obrzydliwych rzeczy.";
			link.l1 = "Nie będę. Zbyt drogie dla mnie. Żegnaj...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
