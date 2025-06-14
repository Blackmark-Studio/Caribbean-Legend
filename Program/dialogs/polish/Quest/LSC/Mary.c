// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czego potrzebujesz?";
			link.l1 = "Nie, to nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, znam go. To przyjaciel Rivadosa i piratów. Adolf nigdy by z nim nie współpracował. Poczuj powietrze... czy wyczuwasz zapach prochu? A na ścianie jest krew... Zabił Adolfa i teraz próbuje nas oszukać! Musi pracować dla admirała! Zabij go!";
			link.l1 = "Hello, sailor.";
			link.l1.go = "Cabin_fight";
		break;
		
		case "Cabin_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			sld = characterFromId("Marchello");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			{
				for (i=1; i<=3; i++)
				{
					sld = characterFromId("CyclopGuard_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// на улице
		case "Town":
			dialog.text = "Och, przepraszam... Mogę cię prosić o pomoc?";
			link.l1 = "„Hm. Zawsze jestem gotów pomóc pięknej damie. Jaki jest problem?”";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "Widzisz, kupiłam skrzynię pełną wszelakich kawałków metalu od Sessile Gallard. Ona mieszka na 'Evie'. Jurgen obiecał wykuć dla mnie coś porządnego, tak, co nie... Kupiłam to, tak, ale nie mogę mu tego zanieść. Jakże to głupie z mojej strony!\nMoże mógłbyś mi pomóc przenieść skrzynię z 'Evy' do bloku Narwhala na 'Esmeraldzie'? Proszę, byłabym bardzo wdzięczna!";
			link.l1 = "I to wszystko? Oczywiście, panienko, pomogę ci. To nie jest wielki kłopot.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Dziękuję! Pokażę ci, gdzie jest skrzynia.";
			link.l1 = "Milady...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "I oto jesteśmy... Teraz powiedz mi, draniu, gdzie jest klucz?!";
			link.l1 = "Wow! Ha, wygląda na to, że żadna pomoc nie jest potrzebna... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Sprytny chłopiec, co? Mniej gadania, do diabła z tobą! Gdzie jest klucz? Daj go, albo pożałujesz!";
			link.l1 = "Jak niegrzecznie! Taki niecny język u tak pięknej dziewczyny. Jaki klucz?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "Klucz, który zabrałeś od Adolfa Barbiera. I nie zaprzeczaj – widziano cię, jak wychodziłeś z jego kajuty. Adolf nie żyje i to twoja robota... Teraz, oddaj mi klucz!";
			link.l1 = "„Więc to jednak byłaś ty... To był błąd, dziewczyno, bardzo wielki błąd!”";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "„Co powiedziałeś?... Do diabła, nie jesteś zwykłym rabusiem! On pracuje dla admirała! Złapcie go, chłopcy!”";
			link.l1 = "Ha, jesteś prawdziwym dżentelmenem: ledwo schowałeś szablę do pochwy, a już zasypujesz mnie komplementami. Dzięki za pomoc. Naprawdę mnie uratowałeś, tak, co nie? Przedstaw się, proszę, bo pierwszy raz cię widzę. Długo już jesteś na Wyspie?";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, to on! Cholera, przyprowadził pomocnika! Chłopcy, zabić ich wszystkich!";
			link.l1 = "Ha, jesteś prawdziwym dżentelmenem: ledwo schowałeś szablę do pochwy, a już zasypujesz mnie komplementami. Dzięki za pomoc. Naprawdę mnie uratowałeś, tak, co nie? Przedstaw się, proszę, bo pierwszy raz cię widzę. Długo już jesteś na Wyspie?";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "Jesteś w samą porę... Nigdy bym sobie z nimi nie poradziła sama... Fuh! Szczerze mówiąc, myślałam, że to już mój koniec!";
			link.l1 = "Walczysz jak Walkiria! Nigdy nie widziałem, żeby taka piękna dziewczyna walczyła z takim zapałem...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, jesteś dżentelmenem, prawda: komplementujesz mnie z szablą w ręku. Dzięki za pomoc. Uratowałeś mi życie, tak, co nie? Przedstaw się, dżentelmenie, nigdy cię wcześniej nie widziałam. Jesteś tu nowy?";
			link.l1 = " Nazywam się "+GetFullName(pchar)+", ale piękne damy mogą mnie nazywać "+pchar.name+". . Czy jestem tu nowa? Hm... Jestem.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Widać od razu – bo inaczej dawno bym już wypatrzyła takiego przystojniaka. A ja jestem Mary, Mary Casper, choć wszyscy tutaj nazywają mnie Czerwoną Mary. Bo jestem ruda, tak, co nie?";
			link.l1 = "Miło mi cię poznać, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Och, jestem podwójnie wdzięczna... zważywszy, że byłabym martwa, gdyby nie ty! Ten drań Chad nie blefował. Takie plugastwo! A ja byłam głupia, że zostawiłam dolne drzwi otwarte. Tak właśnie wszedłeś, tak, co nie?";
			link.l1 = "Tak. Pływałam wokół wyspy, próbując znaleźć miejsce, gdzie mogłabym się wydostać.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Widzę. Te otwarte drzwi prawie mnie zabiły. Sam Jurgen wykuł dla mnie zamki, nie otworzysz ich bez odpowiedniego klucza, a wytrychy nie pomogą. Poza tym, nie będę stała bezczynnie, gdy ktoś próbuje się dostać do środka – cztery lufy mojego pistoletu zostawią cztery dziury w drzwiach albo w ciele, ha-ha!\nAle przeklęty Chad nie da mi spokoju. Już wysłał zbirów, żeby 'przekonali' mnie do jego strony, zdecydowanie jest poważny w tym temacie. Gdyby nie ty, powiedziałabym tak. Będę musiała zostać tutaj pod oblężeniem, "+pchar.name+"Tak, co nie? Dzięki Bogu, że to przewidziałam, mam wystarczająco zapasów, a Jurgen jest moim sąsiadem, z nim się nie pokłóciłam.";
			link.l1 = "Mary, dlaczego nie opowiesz mi więcej o swoich problemach? Widzę, że potrzebujesz mojej pomocy, ale nic nie zrozumiałem z tego, co powiedziałaś.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Tak, potrzebuję pomocy, tak, co nie! Jestem teraz sama. Pokłóciłam się z Donaldem, a potem Chad okazał się łajdakiem. Och, przepraszam, znowu paplam. Dobrze, opowiem ci o sytuacji, w jakiej się znalazłam...";
			link.l1 = "Pamiętaj, że jestem tu nowa, więc jeszcze niewiele rozumiem. Kim jest ten Chad, który próbuje cię 'przekonać' lub zabić? Kim jest Donald?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad jest piratem z załogi admirała Shark Dodsona, strażnikiem na 'Tartarusie'...";
			link.l1 = "Poczekaj! Co powiedziałeś? Rekin Dodson? Czy on tu jest?";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Musiałeś przybyć dzisiaj wieczorem, skoro jeszcze o tym nie wiesz. Gdzie indziej mógłby być Rekin, jeśli nie tutaj? Moje kłopoty zaczęły się, gdy przybył tu kilka miesięcy temu. Przyznaję jednak, że to wszystko wina Narwali i Rivados. Kiedy Rekin przybył tu ze swoją załogą, chciał założyć bazę, ale nasi ludzie i Rivados naprawdę nie lubili tego pomysłu. Nocą zaatakowali brygantynę Rekina i podpalili ją\nTo lepiej, że tego nie zrobili! Załoga Rekina to sami diabły, a nie ludzie, tak, co nie. Najpierw zniszczyli wrogie łodzie, potem wylądowali i zaczęli prawdziwą rzeź. Narwale się wycofali, a Rivados uciekli, jak tylko mogli. W końcu piraci zdobyli San Augustine, gdzie znajduje się większość zapasów i prowiantu wyspy, a potem zajęli Tartarus\nRekin uwięził naszego przywódcę Alana Milrowa, który był też moim... moim bliskim przyjacielem, i maga Rivadosów, Chimiseta. Wysłał ich do gnicia w klatkach Tartarus jak zwierzęta. Łatwo jest dopłynąć do Tartarus stąd i udało mi się odwiedzić Alana kilka razy. Tam spotkałam Chada Kappera, którego Rekin mianował strażnikiem. Poprosiłam Chada, by uwolnił Alana, obiecałam mu pieniądze, ale bał się konfrontacji z admirałem\nA potem Alan został zamordowany w więzieniu. Chad powiedział mi, że to Rekin to zrobił, tak, co nie. Więc poszłam do Donalda, który został wybrany przywódcą na miejsce Alana, i zażądałam natychmiastowego ataku na piratów, ale odmówił, twierdząc, że te morskie diabły są dla nas zbyt groźne. Wtedy powiedziałam mu, żeby się pieprzył\nMoi ludzie byli bezwartościowi w tej sprawie, więc zawarłam układ z Kapperem, łajdakiem, który chciał zająć miejsce Rekina. Mieliśmy plan - zwabić admirała z jego fortecy do jakiegoś podejrzanego miejsca i tam go zabić. Znaleźliśmy też snajpera z dobrą strzelbą. Mógł strzelić do admirała z masztu Fury\nTeraz najciekawsza część, przedwczoraj wieczorem odwiedziłam Tartarus nocą, chciałam powiedzieć coś ważnego Chadovi dotyczącego naszego planu. Dopłynęłam do łodzi i przypadkiem podsłuchałam, jak Chad rozmawia z dwoma Narwalami. Okazało się, że to nie Rekin zabił Alana. Chad to zrobił. Potem potajemnie rozpuścił plotki o udziale admirała\nZabił go z mojego powodu. Po pierwsze, chciał mnie wziąć za zabawkę do swojego łóżka. Po drugie, chciał mnie użyć, by pozbyć się Rekina - wiedział, że zawsze będę szukać zemsty. Możesz sobie wyobrazić? Co za tchórz!";
			link.l1 = "Tak, co nie? Spotkałam już takich jak on...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Skurwysyn jest gorszy! On... brakuje mi słów, by opisać to monstrum! Wtedy odeszłam, a następnego ranka znalazłam go i wygarnęłam mu wszystko, co o nim myślę. Tak, powiedziałam mu, że nie będę miała nic wspólnego z jego spiskiem przeciwko admirałowi.";
			link.l1 = "A on oczywiście tego nie polubił... To było zrobione w gniewie, Mary. Powinnaś być bardziej ostrożna.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "Nie mogę, nie mogłam trzymać języka za zębami. Drań zabił Alana i próbował mnie wykorzystać, by osiągnąć swoje brudne cele! Kanalia! Tak, oczywiście, wściekł się i obiecał, że tego pożałuję. Powiedziałam, że obetnę mu jaja i nakarmię nimi kraby!\nGroził, że wyśle swoich kumpli z Narwala, jeśli się nie rozmyślę. Śmiałam się, nie sądziłam, że Narwal ośmieli się podnieść na mnie rękę.";
			link.l1 = "Wydaje się, że się myliłeś.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Tak, "+pchar.name+"Tak, co nie? Zlekceważyłam Chada i przeceniłam siebie. On znalazł drani, którzy odważyliby się zaatakować samotną dziewczynę w jej własnej kajucie. I co powinnam teraz zrobić? Nie mogę nikomu ufać. Nie mogę ufać nawet swoim ludziom. Ci dwaj to Narwale, znałam ich oboje, tak, co nie? Dopóki Chad żyje - jestem w niebezpieczeństwie, na pewno wyśle więcej, bez wątpienia\nBoję się wyjść, snajper, którego znaleźliśmy, by zabić Rekina, może mnie zastrzelić z terenu Rivados i łatwo uciec. Nie pójdę do Donalda, nie posłucha mnie\nAdmirale? Nie mogę wyjaśnić mojej roli w przygotowaniach do jego zabójstwa! Wyśle mnie gnić w celach 'Tartarusa', jestem tego pewna! Cholera, jestem w pułapce. Zamierzam tu siedzieć z załadowanymi pistoletami, dopóki zapasy się nie skończą, a potem... Nie mam pojęcia, co się ze mną stanie!";
			link.l1 = "„Cóż, w takim razie nie mam wyboru, muszę ci pomóc, tak, co nie? Twoja sytuacja i tak wpisuje się w moje plany tutaj...”";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Zamierzasz mi pomóc? Ale jak? Zamierzasz zabić Chada?";
			link.l1 = "Ta część planu, pewnie.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Słuchaj, "+pchar.name+"Doceniam twoje intencje, ale Chad jest poza twoim zasięgiem. Jest jednym z najbardziej zaufanych przyjaciół admirała, a nawet gdybyś do niego dotarł - piraci Rekina cię zabiją, nie znają prawdy, tak, co nie?";
			link.l1 = "Spokojnie. I tak będę musiał porozmawiać z Rekinem.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Więc ty też jesteś piratem?! Opowiedz mi o sobie, spójrz na siebie: wdarłeś się do mojego domu, uratowałeś mi życie, obiecałeś pomóc, taki przystojny, a ja nic o tobie nie wiem!";
			link.l1 = "Dobrze... Nie jestem piratem, ale obecnie pracuję z pewnym pirackim baronem Janem Svensonem. Przybyłem tutaj, aby znaleźć Nathaniela Hawka. Słyszałeś o nim?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "Nie, kim on jest?";
			link.l1 = "On jest kolejnym znanym piratem. Szkoda, że się z nim nie spotkałeś, musi być gdzieś tutaj. Szukałam też Rekina, ale nie spodziewałam się go tutaj znaleźć.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "Jak się tu dostałeś? Wyglądasz zbyt dobrze jak na rozbitka.";
			link.l1 = "A dlaczego sądzisz, że rozbiłem się na morzu?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "To jedyny sposób, aby się tu dostać. Tylko Rekin jakoś tu dopłynął.";
			link.l1 = "No cóż, Jak widać, Rekin nie był jedyny.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "Masz więc statek? Wspaniale!";
			link.l1 = "Nie ekscytuj się tak szybko, Mary. Dotarłem tu przez... na barku, ale poszedł na dno.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "„A-ach... Cóż, jak mówiłam - rozbicie statku. Teraz jesteś uwięziony tutaj z nami, tak, co nie?”";
			link.l1 = "Mary, pozwól mi opowiedzieć ci mój plan. Wspomniałaś, że Chad planował zabić Rekina. Potrzebuję Rekina żywego, Jan i ja zamierzamy uczynić go głową piratów. Dlatego muszę go ostrzec, bo z twojej opowieści jestem pewien, że Chad spróbuje to zrobić z twoją pomocą lub bez niej.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Tak, prawdopodobnie. Ma ludzi, żeby to zrealizować...";
			link.l1 = "To oznacza, że moim głównym celem jest zdobycie zaufania Rekina i uratowanie go. Potem oficjalnie dotrę do Chada. Masz jakieś dowody, które potwierdzają jego zamiary?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "   Mam jego list, który przyniósł tu jeden z tych... idiotów na podłodze. Są tam groźby i szczegóły, które admirał może uznać za interesujące. Czekaj! A co ze mną? Rekin dowie się, że współpracowałam z Chadem!";
			link.l1 = "Mary, czy zamierzasz siedzieć tu wiecznie uzbrojona w pistolety i ukrywać swoją słodką twarz przed wszystkimi? Czy naprawdę uważasz mnie za jednego z idiotów, którzy chcą piękną damę martwą? Pokaż mi najpierw list, zobaczmy, co mogę zrobić...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Proszę. Co o tym sądzisz?";
			link.l1 = "Trzymaj się... (czyta). Tak, wygląda na to, że Chad to wyjątkowy rodzaj łajdaka, który zaraża tę Ziemię. Ten list wystarczy, aby Rekin sam chętnie założył stryczek na szyję Chada. Nie martw się, milady, dopilnuję, aby Rekin niczego o tobie nie podejrzewał. I tak będzie zbyt zajęty Chadem.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Zrobisz to? Obiecaj mi, tak, co nie! Przysięgnij, że mnie nie zdradzisz!";
			link.l1 = "Mary, przysięgam ci, że cię nie zdradzę. Nie martw się o to, nie uratowałem cię tylko po to, żeby do tego doszło\nChad na pewno cię nie zostawi w spokoju, wiesz za dużo. Zostań tutaj, dopóki on nie zginie.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Tak, zostanę tutaj. Nie chcę zostać zastrzelona przez snajpera ani dźgnięta w plecy.";
			link.l1 = "Grzeczna dziewczynka. Zamknij wszystkie drzwi, w tym te na dole. Masz tylko jeden klucz?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "Nie. Jest jeszcze jeden. Chcesz go?";
			link.l1 = "Tak, co nie? Ufasz mi?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Cóż, jeśli dżentelmen, który właśnie uratował mi życie, mnie zdradzi, to nie ma już sensu żyć... Weź to.";
			link.l1 = "Nie bój się, piękności! Nie zawiodę cię. Zobaczę się z tobą, jak tylko rozwiążę ten bałagan. Mam nadzieję, że to nie potrwa długo.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "To w porządku, mogę utrzymać to miejsce przez kilka tygodni.";
			link.l1 = "Świetnie. Nie będę więc tracić czasu. Wyniosę trupy i porozmawiam z Rekinem. On jest na 'San Augustine', tak?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Tak, on zawsze tam jest. I wyjdź tą samą drogą, którą tu przyszedłeś - nie pozwolę ci wchodzić na górny pokład 'Ceres Smithy'.";
			link.l1 = "Interesujące, a dlaczego tak jest?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Bo nie będziesz w stanie mi pomóc, jeśli zginiesz. To terytorium Narwali i zabiją cię jako obcego.";
			link.l1 = "„Hm... Rozumiem. Cóż, Mary, do zobaczenia. Wrócę, jak tylko będzie bezpiecznie.”";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "Możesz mnie odwiedzić, kiedy tylko chcesz, nie mam z tym problemu. (chichocze)";
			link.l1 = "Żegnaj, piękna!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Cześć, "+pchar.name+"Masz dla mnie jakieś dobre wieści? Wszystko w porządku?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Problem z admirałem został rozwiązany. Nie interesuje go ściganie cię, a jedyną rzeczą, która go martwi, jest zdrada Chada.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Jeszcze nie, Mary. Ale zrobię wszystko, co w mojej mocy.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "„Och, dzięki Bogu! Dziękuję, nie zapomnę tego, tak, co nie! Przynajmniej nie ma zagrożenia ze strony admirała. A co z Chadem? Co zrobił Rekin?”";
			link.l1 = "Przekonaliśmy Rivados, by go zaatakowali. Layton Dexter wyprowadził strażników z „Tartarusa” i dał klucz Czarnemu Eddie. Czarni uwolnili swojego czarownika Chimiseta, ale nie udało im się zabić Chada. Zabili dwóch jego przyjaciół z Narwala, ale on uciekł i się gdzieś ukrywa.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Cholera! To znaczy, że muszę teraz być jeszcze bardziej ostrożna...";
			link.l1 = "Uspokój się, Mary. Jestem pewien, że ma bardziej groźnych ludzi, którymi musi się martwić. Pewnie wie, kto podżegał Rivados do ataku na niego. Zrobi wszystko, by zabić Rekina, nie ciebie.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Naprawdę w to wierzysz? Chad nie jest kimś, kto tak łatwo odpuszcza. Ach, jestem zbyt zmęczona, by dłużej się bać...";
			link.l1 = "Hm. Nie sądziłem, że jesteś z tych dam, które łatwo się płoszą.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! Czyż nie? Nie boję się walczyć twarzą w twarz, ale siedzieć na tyłku czekając na śmierć? Bardzo się boję "+pchar.name+"Tak, co nie!...";
			link.l1 = "Zaufaj mi Mary: Kapper ma teraz pełne ręce roboty z admirałem... Potrzebuję twojej rady.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "Moja rada? Jakiego rodzaju rada?";
			link.l1 = "Eddie znalazł dwa listy napisane przez Chada. Przeczytaj je, może będziesz wiedział, co on knuje. W końcu byłeś w zmowie z Chadem...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Daj je tutaj... (czyta). Axel jest naszym kupcem na 'Esmeraldzie', tak, co nie? Chad chciał kupić od niego whiskey z jakiegoś powodu. Dziwne! Chad pije tylko rum, mówi, że whiskey to 'bimber dla chłopów'...";
			link.l1 = "A co z drugim listem?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "Marcello? Marcello Cyklop, były królewski łowca. To główny powód, dla którego odmawiam opuszczenia tej kajuty.";
			link.l1 = "Czy to on jest snajperem, którego wynająłeś?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Tak, co nie? Marcello potrafi ustrzelić muchę z odległości czterdziestu stóp, mimo że brak mu jednego oka, tak, co nie? Jego zadaniem było zdjąć Rekina z pomocą dalekosiężnego sztucera z bukszprytu Santa Florentiny lub platformy Fury'ego...";
			link.l1 = "„Więc wygląda na to, że Chad postanowił załatwić Rekina. Ale po co wtedy Eva? Cecille? Napitki?”";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Eva to neutralny statek, a Cecille to Cecille Halard, zabawna starsza kobieta, która tam mieszka. Przeprowadziła się tam niedawno z Santa Florentina. Orelie Bertine to jej przyjaciółka. Mieszkały tu razem, zanim się jeszcze urodziłam, tak, co nie?";
			link.l1 = "Hm. Bzdura. Dwóch wielkich chłopów chowa się przed starą babą, żeby wspólnie wypić beczkę whiskey. Niedorzeczność... Nie najlepszy czas na picie, Chad!";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "Już ci mówiłam, że on nie pije whisky. Tylko rum, coś tu się nie zgadza.";
			link.l1 = "Dobrze, jak tam chcesz. Wiesz, gdzie znaleźć Cyklopa?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "Nie. On jest bardzo skryty. Codziennie strzela do ptaków na zewnętrznym kręgu i nikt nie wie, gdzie śpi. Często odwiedzał Rivados wcześniej.";
			link.l1 = "Co za pech... No cóż, pójdę i porozmawiam z Axelem. Może on lepiej to zrozumie. Do zobaczenia, Mary! Zamknij drzwi!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"Proszę, znajdź Chada. Pośpiesz się, nie spałam od ostatniego ataku.";
			link.l1 = "Trzymaj się, kochanie. Zrobię, co w mojej mocy.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Jak się tu dostał? Czy przybył, by...";
			link.l1 = "Tak, żeby cię zabić, Mary. Przyszedł tutaj przez kajutę Jurgena i użył liny, by zejść na dół.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ach! Jestem taką głupią, że zapomniałam o tej drodze! Chad go nauczył, jestem pewna, tak, co nie?";
			link.l1 = "Najprawdopodobniej. Ledwo mi się udało. On szedł za tobą.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "A ja spałam. Zabiłby mnie w sekundę... Ale skąd wiedziałeś, że on tu zmierza?";
			link.l1 = "Zrobiłem... Właśnie to zrobiłem, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "Znowu mnie uratowałeś, przystojniaku. Zawsze przychodzisz w idealnym momencie, tak, co nie. Jak ty to robisz?";
			link.l1 = "„Cóż, nie wiem. Jeden z moich licznych talentów. Oblężenie się skończyło - Chad Kapper nie żyje, a razem z nim wszyscy jego przyjaciele. Cyklop był ostatnim z jego zgniłej załogi.”";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Naprawdę? To prawda, "+pchar.name+"Nie próbujesz mnie oszukać, tak, co nie?";
			link.l1 = "Wcale nie. Eh, potrzebuję trochę odpoczynku po wydarzeniach ostatnich dni...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Mogę wreszcie swobodnie oddychać! Dziękuję... Bardzo ci dziękuję! Jesteś moim bohaterem, tak, co nie?";
			link.l1 = "Podoba mi się to, być twoim bohaterem, to znaczy. Cieszę się, że jesteś w końcu bezpieczna.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "Więc?";
			link.l1 = "Co to, ślicznotko?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Dlaczego tam stoisz? Chodź, dżentelmenie.";
			link.l1 = "I co niby?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Jesteś prawdziwym dżentelmenem... Chodź tu i przytul mnie, pocałuj wreszcie, chcesz tego, widzę to, tak, co nie?";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Nie zostawiaj mnie...";
			link.l1 = "Jestem tutaj, Mary, kochanie...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Wszystko może poczekać. Admirał poczeka, twoi piraci poczekają. Ta noc jest tylko dla nas dwojga, tak, co nie?!";
			link.l1 = "Oczywiście...";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "I wszystkie kolejne noce po tym też...";
			link.l1 = "Tak, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Jesteś z powrotem... bez niej. Więc nie mogła cię ode mnie zabrać!";
				link.l1 = "Mary, twoje podejrzenia były bezpodstawne. Jesteś dla mnie jedyna. Zawsze byłem z tobą w myślach i snach.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", , dlaczego walczysz z Narwalami? Mieszkam na ich terytoriach, właściwie to jestem jednym z nich, jeśli zapomniałeś. Proszę, idź do Fazio i zawrzyj pokój, błagam cię.";
				link.l1 = "Dobrze, Mary, zrobię, jak prosisz, tak, co nie?";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", coś cię trapi. Co się stało?";
				link.l1 = "Mary, muszę z tobą porozmawiać.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+" ! Wszystkie Narwale o tobie mówią!";
				link.l1 = "Naprawdę, mój drogi?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Ten pałas jest niesamowity! Jeszcze raz dziękuję!.. Chcę ci też dać prezent. Oczywiście, nie można go porównać z twoim, ale chcę, żebyś go przyjął, tak, co nie.";
				link.l1 = "Mary, wartość prezentu nie ma znaczenia... Dziękuję, moja miłości";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Pracowity dzień przed sobą, "+pchar.name+"Powodzenia!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, musimy iść i zobaczyć się z Jurgenem dzisiaj.";
					link.l3.go = "narval";
				}
				link.l1 = "Dzięki, Mary! Nie mam co do tego wątpliwości.";
				link.l1.go = "exit";
				link.l2 = "Nie, Mary. Chcę tu trochę odpocząć. Czy to ci odpowiada, tak, co nie?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Cóż, "+pchar.name+", jak się masz? Biegasz po Wyspie jak zwykle?";
				link.l1 = "Tak, Mary. Jest wiele rzeczy do zrobienia...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Już wieczór, "+pchar.name+", o jakich rzeczach mówisz? Zostań tutaj, napijmy się i zrelaksujmy, tak, co nie! To może poczekać do rana!";
				link.l1 = "(śmiejąc się) Oczywiście, kochanie, nie musisz mówić więcej...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, chodźmy dziś do tawerny!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, kochanie, teraz jestem bardzo zajęty. Wrócę trochę później.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Nie zapomnij odwiedzić mnie wieczorem. I nie waż się mnie unikać, tak, co nie!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, musimy iść dziś zobaczyć się z Jurgenem.";
					link.l3.go = "narval";
				}
				link.l1 = "Jasne, Mary, jak mógłbym? Na pewno cię odwiedzę.";
				link.l1.go = "exit";
				link.l2 = "Nie, Mary. Chcę odpocząć tutaj tej nocy. Pasuje ci to, tak, co nie?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "Co ty gadasz? Już jest noc! Nie, nigdzie się nie wybierasz, zostaniesz tutaj, ze mną, tak, co nie?";
			link.l1 = "(śmiejąc się) jak sobie życzysz, kochanie...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Nawet nie próbuj...";
			link.l1 = "   Witaj, przyjacielu. ";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("Świetny pomysł, "+pchar.name+"Tak, co nie! Zgadzam się!","Tak, chodźmy, "+pchar.name+"! Sancho ma wyśmienitą kolekcję win, jest w czym wybierać!","O, byłabym zachwycona, tak, co nie? W karczmie Sancho zawsze jest zabawa, a on ma świetny wybór win!");
			link.l1 = "Chodźmy!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Oczywiście, "+pchar.name+"Tak, oczywiście, odpocznij trochę, tak, co nie?";
			link.l1 = "Zostanę do południa...";
			link.l1.go = "rest_day";
			link.l2 = "Zostanę do wieczora...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Oczywiście, "+pchar.name+"Tak, odpocznij sobie, tak, co nie?";
			link.l1 = "Zostanę do wieczora...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+" !  Wróciłeś... bez niej. Więc ona nie mogła cię ode mnie zabrać!";
				link.l1 = "Mary, twoje podejrzenia były nieuzasadnione. Jesteś dla mnie jedyną. Zawsze byłem z tobą w myślach i snach.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+"Tak, co nie? Dlaczego walczysz z Narwalami? Żyję na ich terytoriach, właściwie, jestem jednym z nich, na wypadek gdybyś zapomniał. Proszę, idź do Fazio i zawrzyj pokój, błagam cię.";
				link.l1 = "Dobrze, Mary, zrobię, jak prosisz.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Ten pałasz jest niesamowity! Jeszcze raz dziękuję!.. Chcę również dać ci prezent. Oczywiście, nie dorównuje on wartością twemu, ale chcę, żebyś go przyjął, tak, co nie.";
				link.l1 = "Mary, wartość prezentu nie ma znaczenia... Dziękuję, moja miłości";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Już odchodzisz, "+pchar.name+"Powodzenia i nie zapomnij o mnie, tak, co nie...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "„Mary, powinniśmy iść i zobaczyć się z Jurgenem dzisiaj.”";
					link.l3.go = "narval";
				}
				link.l1 = "Oczywiście, Mary.";
				link.l1.go = "exit";
				link.l2 = "„Nie, Mary. Chcę tutaj trochę odpocząć. Czy to ci pasuje, tak, co nie?”";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Czy nie idziesz na to swoje Kukulcanowe coś, "+pchar.name+"?";
				link.l1 = "Jeszcze nie, wciąż się przygotowuję.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Już jest wieczór, "+pchar.name+" Dlaczego nie zostaniesz tutaj? Chcę być z tobą.";
				link.l1 = "Tak, co nie, kochanie, zostaję...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, chodźmy dzisiaj do tawerny!";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Powodzenia i nie zapomnij o mnie... Przyjdź do mnie wieczorem, jeśli możesz, tak, co nie!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, powinniśmy zobaczyć się z Jurgenem dziś.";
					link.l3.go = "narval";
				}
				link.l1 = "Bardzo dobrze, kochanie.";
				link.l1.go = "exit";
				link.l2 = "Mary, chcę tu trochę odpocząć. Czy to ci pasuje, tak, co nie?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "O czym ty mówisz? Jest noc! Nie, nigdzie nie idziesz, zostaniesz tutaj, tak, co nie?";
			link.l1 = "(śmiejąc się) Tak, co nie, zostanę...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Kapitanie "+pchar.name+"! Oficer Mary Casper jest gotowa służyć pod twoim dowództwem!";
				link.l1 = "Dobra robota, oficerze! Rozkazuję ci natychmiast wejść na pokład statku. Ale najpierw: pocałuj swojego kapitana!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "To było niesamowite, kochanie... Dzień dobry!";
				link.l1 = "Dzień dobry, kochanie! Jesteś wspaniały!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Rozmawiałeś z Donaldem? To prawda, że admirał chciał zawrzeć sojusz z Rivados i walczyć przeciwko Narwalom? To prawda, że go od tego odwiodłeś? Będzie pokój między piratami a Narwalami, tak, co nie?";
			link.l1 = "Tak, Mary. To prawda.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", brak mi słów... Mówią także, że Donald uważa cię za przyjaciela. Możesz zostać jednym z Narwali, tak, co nie?";
			link.l1 = "„Zobacz się z Donaldem, kiedy będziesz mógł - on też chce się z tobą pogodzić. Prosi cię o wybaczenie za swoje słowa i za to, że nie zdołał cię ochronić przed tymi dwoma łajdakami.”";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "Do diabła z Donaldem! Chociaż oczywiście cieszę się, że to słyszę. Zobaczę się z nim. Ale ty! Ja... nie, nie tak... Jestem z ciebie dumna, tak, co nie?";
			link.l1 = "Na Boga, Mary... ty jesteś... ach, sprawiasz, że moje serce bije szybciej!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Porozmawiajmy! Masz kłopoty?";
			link.l1 = "Nie. Mary, pamiętasz noc, kiedy pierwszy raz się spotkaliśmy? Po tym, jak rozprawiliśmy się z tymi dwoma łajdakami, powiedziałem ci, że przybyłem tu na statku.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Pamiętam, tak. Twoja bark była zatopiona i musiałeś dopłynąć tutaj... tak, co nie?";
			link.l1 = "Kłamałam. Pomyslałbyś, że zwariowałam, gdybym wtedy powiedziała ci prawdę. Nie było żadnego barku. Użyłam niewytłumaczalnej siły indiańskiego boga 'Kukulcan', aby dostać się w to miejsce.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... O czym ty mówisz? Kukulcan?";
			link.l1 = "Mary, kochana, musisz mi uwierzyć, bo nie ma w tym nic racjonalnego, i nie mogę się tym podzielić z nikim innym, tylko z tobą. Nathaniel Hawk zniknął, dotykając indiańskiego idola, był ścigany i to go uratowało...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "Szukałam Nathaniela. Rozmawiałam z indiańskim szamanem i musiałam zrobić to samo, co Hawk. Zostałam teleportowana do ładowni 'San Augustine', wyszłam przez dziurę w jego kadłubie i los sprowadził mnie do ciebie.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Czy to ma być zabawna historia naszego pierwszego spotkania, którą opowiemy naszym dzieciom pewnego dnia? Czy może postradałeś zmysły?";
			link.l1 = "Jestem poważny, Mary. Rozumiem, że trudno w to uwierzyć i musi wydawać się tobie szaleństwem, ale proszę, zaufaj mi.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Wydaje się, że opowieści Erika były prawdziwe...";
			link.l1 = "Kim jest Eric? I co ci powiedział?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric był jednym z miejscowych, starym marynarzem. Już nie żyje. Kiedy byłam dzieckiem, opowiadał mi historie o złotym idolu, świątyni, gdzie Rivados składał ofiary z ludzi. Tutaj, na Wyspie\nCi, którzy go dotknęli, znikali i nigdy więcej ich nie widziano. Myślałam, że to tylko opowieści, mające na celu przestraszenie dzieci.";
			link.l1 = "To prawda, Mary. Eric nie kłamał.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Na szczęście statek z tym strasznym idolem zatonął. Nigdy nie widziałam go na własne oczy.";
			link.l1 = "Znalazłam to, spoczywające na dnie.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Zanurkowałeś tam?! Czy ten przeklęty wynalazca Vedecker dał ci swój skafander? Tam na dole pełno krabów, tak, co nie! Drań! narażać cię na takie niebezpieczeństwo!";
			link.l1 = "Mary, nie martw się o mnie. Poradzę sobie z potworami. Nie są tak groźne, jak mówią. Szukałam posągu od pierwszego dnia na tej wyspie i w końcu go znalazłam.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "I co teraz się stanie?";
			link.l1 = "To jedyna droga stąd. Dotarłem tu przez taki sam idol i znów go użyję, żeby wrócić... Mary! Płaczesz? Mary! Przestań!";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Dlaczego miałabym? Będę płakać, chcę płakać, tak, co nie... (szlochanie) Takie rzeczy zawsze przydarzają się moim ludziom! Znów będę sama!";
			link.l1 = "Co myślisz, co się ze mną stanie? Naprawdę myślisz, że zostawiłbym cię tutaj?! Wrócę po ciebie, na statku. Muszę zabrać zarówno ciebie, jak i "+sTemp+"Nathaniel wrócił ze mną. Czy pójdziesz za mną do zewnętrznego świata?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(we łzach) Oczywiście.... Pewnie, że tak... Wrócisz po mnie, tak, co nie? Jak do licha planujesz wrócić na wyspę? Tylko Rekin wie, jak tu dopłynąć. I nie waż się o mnie zapomnieć, bo jak cię znajdę, to cię przetrzepię!";
			link.l1 = "Mary, dosyć tych twoich dzikich myśli! Oczywiście, że wrócę po ciebie, kto inny ma sprawić, by moje serce biło tak samo, jak od dnia, gdy cię poznałem? Nie martw się, moja miłości, Rekin podzielił się ze mną współrzędnymi i wskazówkami. Znajdę do ciebie drogę.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "Powiedziałeś, że posąg przeniósł cię tutaj prosto z Main, ale co jeśli ten posąg zabierze cię gdzie indziej, może do Afryki? Co ja wtedy zrobię bez ciebie?!";
			link.l1 = "Kukulcan jest indiańskim bogiem, zabierze mnie gdzieś na Karaiby lub Kontynent. Muszę tylko znaleźć osadę, a wtedy łatwo odnajdę swój statek i załogę.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(płacze) Obiecaj mi... nie, przysięgnij, że wrócisz, tak, co nie!";
			link.l1 = "Mary, kochanie, przysięgam ci, że wrócę. I zabiorę cię z tego przeklętego miejsca. Nie musisz tęsknić za mną zbyt długo. Dość już tych łez.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Dobrze, "+pchar.name+"... ... Wróć do mnie, będę czekać, tak, co nie! Kiedy zamierzasz odejść?";
			link.l1 = "Jeszcze nie wiem. Muszę się najpierw przygotować, potem zanurzę się i dotknę posągu. Powiedzą ci, że utonęłam - nie wierz im. Wszystko będzie dobrze.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "Mam to. "+pchar.name+", kochanie, przytul mnie... Pocałuj mnie...";
			link.l1 = "Mary... Moja droga Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen? Dlaczego?";
			link.l1 = "Zobaczysz. To będzie miła niespodzianka.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "„Och, jakże interesujące! Przyjemne? To świetnie, tak, co nie? Ruszajmy, zanim umrę z ciekawości!”";
			link.l1 = "Spodoba ci się, jestem pewna. Chodźmy!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Chodźmy, "+pchar.name+"!";
			link.l1 = "Tak, co nie...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "„Cóż, ”"+pchar.name+", , co za niespodziankę masz dla mnie?";
			link.l1 = "Mary! Jurgen i ja postanowiliśmy zrobić ci prezent od nas obojga. To jest unikalne ostrze, miecz szeroki noszący nazwę Narwal. Na świecie istnieją tylko dwa takie miecze: pierwszy należał do Alana Milrowa, ten będzie twój. Jest wykonany ze specjalnej stali, wykutej dzięki mistrzowskiemu dotykowi Jurgena, która nigdy się nie stępi ani nie zardzewieje.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "Nasza droga dziewczyno... Wszystkie Narwale wiedzą, jak cierpiałaś. Sądzę, że zasługujesz na noszenie tego pałasza, symbolu klanu Narwala. Noś go z dumą. Ten miecz będzie zagrożeniem dla twoich wrogów i ochroną w bitwie.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? To... dla mnie?...";
			link.l1 = "Tak, Mary. "+sld.name+"  poprosił mnie, abym to dla ciebie zrobił, i przyniósł unikalne żelazo z dna morza, żaden stal nie dorówna wadze ani sile tego materiału. Włożyłem w ten miecz swoją duszę, tak jak kiedyś zrobiłem to z mieczem Alana.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "Nie wiem, co powiedzieć... Dziękuję, Jurgen! Dziękuję, tak, co nie! Będę nosić to z dumą i dorównam wartości ostrza, przysięgam, tak, co nie! Nie trenowałam wystarczająco z szablami, ale teraz będę ciężko trenować!";
			link.l1 = "W to nie wątpię, dziewczyno.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... czekaj, nie... Jesteś najlepszym człowiekiem, jakiego kiedykolwiek spotkałam! Jesteś niesamowity, tak, co nie! Czy wiesz, ile to dla mnie znaczy? Ten miecz to najlepszy prezent, jaki mogłam kiedykolwiek dostać! Zrobiłeś dla mnie już tak wiele, uratowałeś mi życie dwa razy, a mimo to nigdy nie przestajesz mnie zaskakiwać! Dziękuję, mój ukochany!";
			link.l1 = "Nie mogło być inaczej, Mary. Będę cię zaskakiwał każdego dnia, aż do ostatniego tchu! Twój uśmiech sprawia mi radość i cieszę się, że podoba ci się prezent.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(chichot) Dziękuję! To wspaniała klinga, tak, co nie? Potrzebuje silnej ręki, by nią władać... Nie mogę się doczekać, żeby zacząć z nią trening!";
			link.l1 = "Nie widzę problemu. Pędź do swojej kajuty i wypróbuj nowy pałasz!";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "To właśnie zamierzam zrobić. Dziękuję jeszcze raz, dżentelmenie! "+pchar.name+" ... Przyjdź do mnie dziś wieczorem, kiedy będziesz gotowy... (chichocze)";
			link.l1 = "Oczywiście, milady. Zobaczymy się wieczorem.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Spójrz tutaj. Znalazłem to na jednym ze statków w zewnętrznym pierścieniu, w skrzyni kapitana. Każdy doświadczony marynarz mówi, że ten przedmiot jest niezwykle cenny dla nawigatora, potrafi ochronić statek przed najgorszymi burzami. Niektórzy z nich byli nawet chętni, by go kupić, ale nie sprzedałem... Chcę, żebyś miała ten amulet, kochanie. Użyj go, by chronił cię na morzu.";
			link.l1 = "Dziękuję, Mary! To bardzo miłe z twojej strony, kocham cię!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Naprawdę? Podoba ci się? Och, to świetnie! Bardzo się cieszę, tak, co nie?";
			link.l1 = "To bardzo rzadki i cenny talizman. Oczywiście, że mi się podoba! Dziękuję, kochanie!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... Wróciłeś. Czekałam na ciebie, codziennie wypatrywałam horyzontu, tak, co nie! Wróciłeś do mnie...";
			link.l1 = "Tak, Mary. Jestem tutaj, jak obiecałem. Pozwól, że cię przytulę, kochanie!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "„Ach, ”"+pchar.name+"... Nie możesz sobie nawet wyobrazić, jak się czułam! Narwale mówiły o twojej śmierci, twierdziły, że utonąłeś. Wszyscy byli pewni, że nie żyjesz. Ciągle im powtarzałam, że jesteś żywy... Oczywiście, nikt mi nie wierzył, myśleli, że oszalałam po tym wszystkim, co się stało.";
			link.l1 = "Mary... Moja droga! Co się z tobą dzieje? Drżysz... Czy jest ci zimno?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Nie, nie jest mi zimno. Po prostu... Nie chcę o tym tutaj rozmawiać. Przyjdź do mojej kajuty, gdy skończysz. Chcę z tobą zostać sama, tak, co nie? Czy nie idziesz teraz do admirała i Nathaniela?";
			link.l1 = "Tak. Muszę porozmawiać z Rekinem i, oczywiście, zabrać Danielle do Nathaniela. To nie zajmie zbyt dużo czasu. Wkrótce cię zobaczę, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Czekam z niecierpliwością... by cię zobaczyć. Przyjdź tak szybko, jak to możliwe, tak, co nie?";
			link.l1 = "Ah, jesteś prawdziwym dżentelmenem, co nie?";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"Nareszcie. Musimy porozmawiać, tak, co nie?";
			link.l1 = "Co się dzieje, Mary? Widzę, że coś cię trapi! Co się stało?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "Stało się... "+pchar.name+"„Kim jest ta dziwka na twoim statku?”";
			link.l1 = "Kto? Mówisz o Danielle? Ale już przecież wiesz...";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "Nie, nie Danielle. Mam na myśli tamtą blondynkę, ledwie ubraną, która przechadza się po pokładzie twojego statku! Widziałam ją przez lunetę, tak, co nie?";
			link.l1 = "„A-ach! To jest Helen McArthur. Ona jest zamieszana w tę dziwną historię tak samo jak Danielle. Służy jako mój oficer. Tymczasowo, oczywiście.”";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Oficer? Ona jest oficerem?!";
			link.l1 = "Cóż, tak. Co jest z tym nie tak?.. Mary, do diabła! Jesteś zazdrosna!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "Co sobie myślałeś?!... (w łzach) Czekałam na ciebie cały ten czas, nie spałam przez ciebie, a ty śmiesz wracać tutaj z jakąś wiedźmą...";
			link.l1 = "Mary! Przestań płakać! Co się z tobą dzieje? Możesz zadźgać każdego bez wahania, a jednak twoje oczy są zawsze mokre... Mary, kochana, Helen to tylko oficer, służąca tymczasowo, aż sprawiedliwość zostanie wymierzona, a nasze wspólne cele osiągnięte, nic więcej.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I have been training hard with the broadsword you gave me, and in your absense I have mastered it perfectly.";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I have been training hard with rapiers and I have mastered them perfectly.";
			dialog.text = "„(szlochając) Oficerze... To ja też chcę być twoim oficerem, tak, co nie! Potrafię walczyć, wiesz o tym! ”"+sTemp+" I strzelam dobrze! Może nie mam żadnych umiejętności morskich, ale szybko się uczę, jestem utalentowana, tak, co nie?";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "Mary... chciałem sam ci zaproponować to stanowisko. Nie ma lepszej, bardziej utalentowanej, ognistej dziewczyny niż ty! Chcę cię mieć przy sobie!";
			link.l1.go = "adversary_hire";
			link.l2 = "Mary! Bycie oficerem abordażowym jest zbyt niebezpieczne! Nie rozumiesz, o co prosisz. Nie mogę ryzykować twojego życia.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "„Nie możesz, co nie? Ta blond dziwka może być oficerem, a ja nie mogę? Kłamiesz mnie, ”"+pchar.name+", po prostu nie chcesz być ze mną! (płacze) Czy tamta dziewczyna jest lepsza ode mnie, tak, co nie?";
			link.l1 = "Mary, nie rozumiesz!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "Tak, co nie! Widziałam jej płonące oczy zwrócone na ciebie! Ona nie jest tylko oficerem, tak, co nie! Rozumiem to (łkanie). Oczywiście, nie mogę z nią konkurować - ona wie, jak prowadzić statek...";
			link.l1 = "Mary, o czym ty mówisz, tak, co nie!";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "„To koniec... (szlochając) Odejdź! Odejdź do swojej dziwki! A ja zostanę tutaj... Nigdzie się nie wybieram! Oddaj mi mój klucz!”";
			link.l1 = "Ale Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Odejdź...";
			link.l1 = "Ha, jesteś prawdziwym dżentelmenem: ledwo schowałeś szablę do pochwy, a już zasypujesz mnie komplementami. Dzięki za pomoc. Naprawdę mnie uratowałeś, tak, co nie? Przedstaw się, proszę, bo pierwszy raz cię widzę. Długo już jesteś na Wyspie?";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Naprawdę? Naprawdę chciałeś mnie jako swoją oficer?"+pchar.name+", do diabła, nawet nie wiesz, jak bardzo się cieszę! Chcę być twoim oficerem tak bardzo... ale nie na tym samym statku co ta blondynka!";
				link.l1 = "Mary, ale dlaczego?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Naprawdę? Naprawdę chciałeś mnie jako swojego oficera? "+pchar.name+", cholera, nie wyobrażasz sobie, jak bardzo się cieszę! Przysięgam, nie zawiodę cię, zobaczysz!";
				link.l1 = "Jezusie, Mary, kochanie, jesteś bezcenna. Jeszcze chwilę temu płakałaś, a teraz twoja twarz jest rozświetlona! I, Mary, nie jesteś dla mnie tylko kolejnym oficerem. Jesteś kimś więcej i wątpię, że możesz mnie w jakikolwiek sposób zawieść.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "Możesz uważać ją tylko za swoją oficer, choć wątpię, że ona widzi w tobie tylko kapitana. Widziałam, jak na ciebie patrzyła, znam to spojrzenie, tak, co nie! Tylko ja mogę ci tak patrzeć w oczy!";
			link.l1 = "Mary, kochanie, ale już ci mówiłem, nie mam do niej żadnych uczuć, i koniec! Nic między nami nie ma! Przysięgam, do diabła! Potrzebuję jej pomocy, żeby uporać się z bałaganem wśród Braci Wybrzeża. Jan Svenson nie pomoże mi zdobyć Tortugi, jeśli jej nie pomogę, a jego potrzebuję!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+"Tak, kochanie, przytul mnie... Przepraszam. Wierzę ci. Ale nie będę w stanie być blisko niej i patrzeć, jak próbuje z tobą flirtować, tak, co nie! W końcu wezmę swój miecz i przetnę ją na pół!";
			link.l1 = "Tak, zdecydowanie możesz to zrobić... Masz niezły temperament, tak, co nie?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "I jeśli ją zabiję - zostawisz mnie, tak, co nie... Nigdy bym sobie tego nie wybaczył.";
			link.l1 = "Więc co proponujesz, Mary? Co mam z nią zrobić?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "Powiedziałeś, że ona jest tymczasowym oficerem. Dołączę do ciebie, jak tylko zostawisz ją na lądzie. Mam nadzieję, że na jakiejś bezludnej wyspie (chichot), będę cię śledzić aż po kres świata, tak, co nie!"+pchar.name+", kochanie, czy ona naprawdę jest lepsza ode mnie?";
			link.l1 = "Bzdura! Przestań tak mówić, Mary, kochana, nie ma kobiety lepszej od ciebie!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Udowodnij mi to wtedy. Nie chcę się tobą dzielić, "+pchar.name+"Lepiej być samą niż dzielić się tobą z kimś innym, tak, co nie...";
			link.l1 = "Zgoda, Mary. Zawrzyjmy umowę. Nie mogę teraz pozbyć się Helen, jest ważna dla tej pogoni. Pomogę jej w jej problemach, uczynię ją panią Isla Tesoro, puszczę wolno i nic między nami nie zostanie. Mam nadzieję, że nie potrwa to dłużej niż miesiąc lub dwa. Czy poczekasz na mnie tak długo?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Oczywiście, że tak, tak, co nie! To moja decyzja... Jeśli do mnie wrócisz, to znaczy, że wybrałeś mnie, a nie ją. A jeśli nie wrócisz... to taki mój los. Zostanę tutaj i założę własny klan. Klan Casperów...";
			link.l1 = "„Znowu płaczesz? Mary, daj spokój. Dość już tych bzdur! O czym ty mówisz? Jaki klan... Głupiutka dziewczyno, oczywiście, że wrócę, nie ośmieliłbym się zostawić cię wśród tych zgniłych starych statków! Zalałabyś wyspę swoimi łzami!”";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Wróć tak szybko, jak to możliwe, tak, co nie? "+pchar.name+", kochanie, pocałuj mnie, proszę...";
			link.l1 = "Wracam. Obiecuję!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = "Żartujesz sobie ze mnie? "+pchar.name+"Tak, co nie, czy naprawdę o mnie nie zapomniałeś?";
			link.l1 = "Oczywiście! Czy kiedykolwiek cię zdradziłem? Przeszedłem wiele podczas naszej rozłąki i nie mam zamiaru ponownie się z tobą rozstawać... mój talizmanie.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Naprawdę? "+pchar.name+"! Zawsze będę za tobą podążać! Nigdy cię nie okłamię, nigdy cię nie zdradzę, przysięgam!";
			link.l1 = "Wierzę ci, moja droga... Ja również nie."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", kochanie, przytul mnie... Będziemy razem, tak, co nie? Powiedz mi!";
			link.l1 = "Tak, będziemy razem, Mary. Na zawsze.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Tak jak Danielle i Nathaniel?";
			link.l1 = "„(śmiejąc się) Tak, zupełnie jak oni.”";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... Kocham cię! Wyjdę za ciebie, jeśli chcesz, tak, co nie...";
			link.l1 = "Moja droga Mary... Oczywiście - porozmawiamy o tym później. Twoje życie na tym cmentarzu statków się skończyło, najpierw cię stąd zabierzemy - witaj na pokładzie mojego okrętu i w wielkim świecie, moja miłości!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Spędźmy naszą ostatnią noc na tej wyspie razem, w 'Kowalstwie Ceres'. Tylko my dwoje. Tylko ty i ja... Nie puszczę cię nigdzie, dopóki nie nadejdzie poranek, tak, co nie?";
			link.l1 = "Cóż, nie jesteśmy na moim statku, więc będę podążać za twoim rozkazem... Moja droga Mary!";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "Hello, friend.";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! Mam pomysł...";
			link.l1 = ""+npchar.name+"Nie jest tu bezpiecznie, a ja kazałam ci zostać na statku...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", na tym starym kadłubie jest tyle prochu, że jeśli wybuchnie, cała wyspa poleci w powietrze. Nie ma znaczenia, gdzie teraz stać. Po prostu posłuchaj mnie!";
			link.l1 = "Słucham, proszę szybko.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Piratka korweta i fregata. Myślą, że jesteśmy jednym z nich... Nóż, tak, co nie. To może być okazja dla nas. Weźmy kilka beczek prochu, lont i żeglujmy w ich kierunku.\nGdy pozwolą nam się zbliżyć, zapalamy lont, wrzucamy beczkę na jeden z okrętów i odpływamy najszybciej jak możemy. To musi być idealna okazja, żeby zobaczyć trochę fajerwerków... Co o tym myślisz?";
			link.l1 = "Ryzykowne, choć, twój plan może zadziałać... Tylko jeśli nie rozpoznają nas.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Zaryzykujmy to, "+pchar.name+"?";
			link.l1 = "Dobrze. Zabierajmy się za to! Chłopaki! Weźcie trzy beczki prochu! Wynosimy się stąd, do diabła! Uwielbiam twoją wyobraźnię, "+npchar.name+"...nigdy bym sama na to nie wpadła.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = " Mówiłam ci, mam swoje talenty! ";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Tak, oczywiście, kochanie. Zawsze jestem gotowa pomóc, tak, co nie! O co chodzi?";
			link.l1 = "Statek Jackmana znajduje się w Zatoce Sabo-Matila, ciężka fregata 'Centurion'. Ten statek należał kiedyś do Hawkesów, więc w kabinie Jackmana muszą być ważne przedmioty i dokumenty...musimy go abordażować.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Rozumiem. Jak zamierzasz wykonać to na naszym małym ptaszku? Mają więcej ludzi i dział. Patrzyłam przez lunetę, tak, co nie!";
			link.l1 = "Masz rację. Jackman ma co najmniej dwa razy więcej ludzi niż my, a wszyscy oni to wprawieni rzezimieszkowie i najemnicy. Byłoby szaleństwem zaokrętować się bez odpowiednich przygotowań. Przedłużająca się bitwa na morzu też nie wchodzi w grę. Więc myślałem o innych możliwościach, aby wykonać zadanie.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", jeszcze nas nie rozpoznali jako wroga, tak jak ci idioci z Turks... Możemy spróbować naszego triku jeszcze raz...";
			link.l1 = "Mary, właśnie powiedziałem ci, że musimy wejść na fregatę, zatopienie jej nie wchodzi w rachubę.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Wiem to, "+pchar.name+". nie zatopimy jej. Słuchaj, weźmiemy kilka pustych beczek po rumie i napełnimy je prochem, kartaczami i krótkimi lontami. Następnie podpłyniemy bliżej ich fregaty i wrzucimy improwizowane ładunki wybuchowe na ich pokład.";
			link.l1 = "Ha! Czy naprawdę myślisz, że to zadziała?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "A czemu nie? Ich burty są wyższe niż nasze, ale dwóch lub trzech ludzi wspomaganych blokiem może z łatwością podnieść i rzucić w pełni załadowaną beczkę. Zawołamy - 'Oto darmowy rum od Knive!' A beczki wybuchną, zanim zdążą zareagować.";
			link.l1 = "Wystrzał z kartacza zamieni jego najlepszych ludzi na pokładzie w siekaninę... Cholera, brzmi kusząco.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Użyjmy pięciu beczek. "+pchar.name+"Tak, co nie? Mamy element zaskoczenia. Oni niczego nie podejrzewają! Musimy natychmiast odpłynąć, zanim nas abordażują.";
			link.l1 = "Cóż, spróbujmy. Nie mogą nas zidentyfikować, zanim nie wrzucimy beczek... Cholera, nie będzie łatwo się do nich zbliżyć. Jackman nie jest idiotą jak Ghoul.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Zaryzykujmy to, "+pchar.name+"!   I tak to nie zaszkodzi.";
			link.l1 = "Dobra myśl, nie mamy nic do stracenia... Przygotuj fougasses!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Zrobię to, kapitanie! Przygotuję ich doskonale, tak, co nie?";
			link.l1 = "Hej, nie pozwolili ci ogłuszyć tych krabów na wyspie, więc pozwalam ci teraz rozwalić parę pirackich tyłków, eh... Mary, jesteś cudowna!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Dziękuję, "+pchar.name+"Nie zawiodę cię!";
			link.l1 = "W to nie mam wątpliwości. Mam nadzieję, że to my nie zawiedziemy cię, psując ten twój plan... Do broni!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Tam jesteś! Trzeba było się natrudzić, żeby cię znaleźć... To było niesamowite, kapitanie! Nigdy wcześniej nie widziałam tak zapierającego dech w piersiach skoku! Zawsze jesteś moim bohaterem! Chociaż przyznam, że prawie przyprawiłeś mnie o zawał serca\nKiedyś zabijesz mnie tymi swoimi sztuczkami, drogi... No cóż, kim do cholery ona by była? Oh "+pchar.name+", Ledwie na chwilę cię spuściłam z oczu, a już widzę, że otoczyły cię hordy szumowin!";
			link.l1 = "Mary, ta 'szmata' to Catherine Fox, córka pułkownika Foxa, dowódcy Morskich Lisów. Musimy ją zabrać na Antiguę.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "„Och, doprawdy? Co za rozkosz! Dobrze, opowiesz mi o niej... dziś wieczorem, kiedy spędzimy noc razem, sami. Teraz chodźmy, musimy się spieszyć!”";
			link.l1 = "Jesteś najlepsza, Mary. Co bym bez ciebie zrobił? Catherine, chodź!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "W końcu się obudziłeś, mój drogi... Drań! Nigdy więcej mnie tak nie strasz!";
			link.l1 = "Mary... kochana, co się stało? Głowa mi pęka...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Kiedy weszliśmy do kajuty kapitana, leżałeś na podłodze nieruchomy jak trup. Serce mi waliło! Chłopaki cię podnieśli i przeciągnęli na nasz statek – w samą porę, bo martwi leżący na pokładzie zaczęli znów wstawać. Co za koszmar! Nie mogliśmy nic z nimi zrobić! Szybko przecięliśmy liny i próbowaliśmy odpłynąć, ale salwa z ich statku poważnie uszkodziła nasz statek i straciliśmy kontrolę. To byli prawdziwi diabli, tak, co nie! A potem postawili żagle i zniknęli w mgnieniu oka. Nasz statek osiadł na mieliźnie, więc musieliśmy uciekać na ten brzeg, zanim burza mogła go zniszczyć. Wielu dobrych ludzi zginęło dziś, ale statek ostatecznie przetrwał...";
			link.l1 = "Dobra robota, Mary... Co ja bym bez ciebie zrobił?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Może byś utonął, albo zostałbyś na tym statku, a umarli rozszarpaliby cię na strzępy... Moje ręce wciąż się trzęsą!";
			link.l1 = "Dzięki, kochanie. Jak długo byłam nieprzytomna?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Przez cały dzień. Oczyściłam twoje rany, dałam ci lekarstwa i wlałam w ciebie trochę rumu. Powinieneś szybko wyzdrowieć. I nie waż się umierać na moich oczach!";
			link.l1 = "Obiecuję, że tym razem nie umrę, kochanie. Chociaż nie czuję się zbyt dobrze...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "To na pewno... Czy to był 'Latający Holender', kapitanie? Dlaczego nas zaatakowali? I dlaczego nie strzelali, zanim weszli na pokład?";
			link.l1 = "Ich kapitan potrzebował amuletu, tego, o którym rozmawiałem z Tuttuathapak, szamanem indiańskim. Dlatego musieli nas abordażować, ale jak tylko ich kapitan zabrał amulet, nie potrzebowali nas już więcej... Co za koszmar! Statek obsadzony przez umarłych! Niewiarygodne...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Tak, wygląda na to, że 'Latający Holender' w końcu by nas dopadł. Gdy tylko będę miała okazję, pójdę do kościoła, zapalę świecę za nasze cudowne ocalenie i pomodlę się do naszego Pana...";
			link.l1 = "Ja też, Mary, tak sądzę. Muszę wrócić do tamtej wioski. Powiadomić Tuttuathapaka, co się stało. Ten statek zaatakował nas z powodu amuletu! Mam nadzieję, że ten czerwono-skóry diabeł ma wytłumaczenie, dlaczego do diabła te żywe trupy w ogóle go potrzebowały.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Dobrze. Ale bądź ostrożny - twoje rany ledwo się zagoiły.";
			link.l1 = "Jesteś całym lekarstwem, jakiego potrzebuję. I... Mary, kocham cię...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Ja również cię kocham, mój drogi...";
			link.l1 = "Ha, jesteś prawdziwym dżentelmenem: ledwo schowałeś szablę do pochwy, a już zasypujesz mnie komplementami. Dzięki za pomoc. Naprawdę mnie uratowałeś, tak, co nie? Przedstaw się, proszę, bo pierwszy raz cię widzę. Długo już jesteś na Wyspie?";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+"Nie ma dla mnie większego szczęścia niż być w twoich ramionach, tak, co nie... Chodźmy!",""+pchar.name+"Tak, co nie? Chciałabym być z tobą każdą chwilę, gdyby to było możliwe. Chodźmy!");
			link.l1 = RandPhraseSimple("Jesteś najlepszy, mój kochany...","Jesteś cudowny, mój talizmanie...");
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Kochańku, byłeś niesamowity... zawsze taki jesteś!","To było wspaniałe!");
			link.l1 = RandPhraseSimple("Jestem szczęśliwa, że jesteś szczęśliwy, mój miły...","Kochać cię, Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", nie ma dla mnie większego szczęścia niż być w twoich ramionach, tak, co nie... Ale to nie jest najlepszy moment - musimy złapać tego łajdaka Thibauta, zanim ucieknie.";
				link.l1 = "Masz rację jak zawsze, moja dziewczyno...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", nie ma dla mnie większego szczęścia niż być w twoich ramionach, tak, co nie... Chodźmy!",""+pchar.name+"Tak, co nie? Chciałabym być z tobą w każdej chwili, gdyby to było możliwe. Chodźmy!");
			link.l1 = RandPhraseSimple("Jesteś najlepsza, moja dziewczyno...","Jesteś wspaniały, mój rudy talizman...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "GiveKissInRoom");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestCheckDelay("Mary_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+"Tak, co nie? Za długo już nie kochaliśmy się... Zupełnie o mnie zapomniałeś, tak, co nie! Kochanie, chcę się zrelaksować, wynajmijmy pokój na noc i zostawmy nasze kłopoty na inny dzień!",""+pchar.name+", byłeś zbyt zajęty i zaczynam myśleć, że całkiem o mnie zapomniałeś! Kochanie, chcę... zostać z tobą na osobności. Wynajmijmy pokój na noc, tak, co nie?",""+pchar.name+"Tak, co nie? Czyś ty rozum postradał? Chcę spędzić z tobą noc, napić się wina i odpocząć. Byłeś zbyt zajęty na morzu i całkiem o mnie zapomniałeś!");
			link.l1 = "Mary, kochanie, o czym ty mówisz - 'całkowicie o mnie zapomniałeś'? Głuptasie... Ale naprawdę byłem zbyt zajęty, problemy wymagające mojej uwagi są niekończące się. Wybacz mi, moja miłości. Chodźmy na górę, jestem cały twój na noc, świat może poczekać!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Dziś nie, kochanie. Boli mnie głowa.","Mary, kochanie, jakże mógłbym o tobie zapomnieć? Chodź, później - mamy trochę roboty do zrobienia..."),RandPhraseSimple("Zawsze jesteś w moich myślach, Mary, ale teraz nie możemy sobie pozwolić na odpoczynek, tak, co nie?","Mary "+npchar.lastname+", nie mamy dziś czasu na bzdury"));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "Cóż ... Co jeszcze mogę powiedzieć ... Tak, kapitanie!";
			link.l1 = "Ha, jesteś prawdziwym dżentelmenem: ledwo schowałeś szablę do pochwy, a już zasypujesz mnie komplementami. Dzięki za pomoc. Naprawdę mnie uratowałeś, tak, co nie? Przedstaw się, proszę, bo pierwszy raz cię widzę. Długo już jesteś na Wyspie?";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, kochanie, o czym Ty mówisz - 'całkowicie o mnie zapomniałeś'? Głuptasie... Ale naprawdę byłem zajęty, te problemy nie mają końca. Wybacz mi, dziewczyno. Chodźmy na górę, świat może poczekać!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Tak, oto on! Już mnie nie lubisz, co nie? Powiedz mi!";
			link.l1 = "Co?! Mary, co za bzdury opowiadasz? Dlaczego tak myślisz?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "„To dlaczego odwiedzałeś te dziwki, te burdelowe ladacznice? Wiem, że to zrobiłeś, nie kłam mi! Coś ci we mnie nie odpowiada, gdy się kochamy, tak? (płacze) Powiedz mi...”";
			link.l1 = "Mary, Mary... uspokój się, proszę, moja dziewczyno. Tak, byłem w burdelu kilka razy, ale tylko w sprawach biznesowych. Nie szukałem zabawy!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "I co to za 'sprawy biznesowe' przywiodły cię na górę do pokoju rozpusty? (szlochając) Kłamiesz, "+pchar.name+"!";
			link.l1 = "Mary, kochanie, przestań wreszcie... Naprawdę miałem pewne sprawy do załatwienia z właścicielką burdelu.  I kilka razy poszedłem na górę. Ostatnim razem w sprawie osobistej gubernatora - poprosił mnie, abym znalazł jego obrączkę. Jak mogłem odmówić Jego Ekscelencji?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "„A jak mogłem wytłumaczyć gospodyni, że muszę zajrzeć pod łóżko na górze? Nie mogłem. Więc musiałem kupić dziwkę na noc, by móc wejść na górę... Za drugim razem powiedziano mi, że kupiec zgubił tam dokumenty swojego statku. Musiałem znów zapłacić dziewczynie, by móc przeszukać pokój, ale dobrze mi zapłacono za dokumenty...”";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "Trzeci raz pomagałem miejscowemu komendantowi: musiałem wypytać dziwki o jakiegoś oficera z garnizonu. Ten oficer był podejrzewany o szpiegostwo i powiązania z piratami. W końcu go złapaliśmy, a ja otrzymałem piękną nagrodę...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "Widzisz teraz? Mówię ci, to wszystko chodziło o interesy. Mary, to ciebie kocham i potrzebuję. Jesteś najlepsza, przysięgam! Czy naprawdę myślisz, że będę zadawał się z jakąś portową dziwką, kiedy mam ciebie? Jak mogłaś pomyśleć o mnie w ten sposób!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+" ... Czy to wszystko prawda? Czy jesteś ze mną szczery? Nie byłeś z nimi?";
			link.l1 = "Mary, kochana, jesteś jedyną kobietą, którą kocham, to prawda. Podejdź bliżej, kochana. Pozwól, że cię przytulę... Otrzyj łzy i, proszę, przestań być zazdrosna! Już nigdy nie odwiedzę domów publicznych, jeśli tego chcesz!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Tak, to właśnie chcę!... "+pchar.name+"Jestem zazdrosna, bo cię kocham... I nie chcę cię stracić, tak, co nie! Słyszysz mnie? Zabiję każdą sukę, która ośmieli się podejść o cal za blisko ciebie!";
			link.l1 = "Spokojnie... Nie ma potrzeby nikogo zabijać. I nie stracisz mnie, obiecuję. Wszystko w porządku, uspokój się. Jesteś moją jedyną i najlepszą dziewczyną na świecie... Uwierz mi, że tak jest.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+"Tak, co nie? Co za dziwne pytanie? Kocham cię. Uratowałeś mnie. Jestem twoim rudowłosym talizmanem - czy naprawdę myślisz, że pozwolę ci iść tam samemu? Nawet na to nie licz, tak, co nie! Jestem z tobą! Kiedy ruszamy?";
			link.l1 = "Masz rację, kochanie, to było dziwne pytanie... Powiem ci później, kiedy wyruszymy. Najpierw musimy się przygotować.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Jestem gotowa, kapitanie! Pójdę za tobą na koniec świata!";
			link.l1 = "Dziękuję, mój drogi...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
			dialog.text = "Co to za harmider tym razem, kapitanie? Hiszpanie, piraci czy coś gorszego?";
			link.l1 = "„To gorzej, Mary, dużo gorzej. Gubernator zamierza odwiedzić niezwykle drogą kurtyzanę, a ja mam mu towarzyszyć jako osoba zainteresowana, jak obiecano gospodyni. Nudne rozmowy, przewartościowane wino i nudni szlachcice.”";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Wręcz przeciwnie, ciężar zaproszenia na towarzyskie wydarzenie, organizowane przez szlachetną damę. Jego Ekscelencja zaskoczył mnie, gdy poprosił, bym mu towarzyszyła, ale szczerze mówiąc, czekam z niecierpliwością, by oderwać się od codzienności.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "„Naprawdę?! Kurtyzana? Mówisz to, jakby to była błahostka, co? Po prostu zabawa z Jego Ekscelencją? Charles, czy ty pieprzysz...”";
			link.l1 = "Mary, uspokój się, proszę! To nie tak, że idę tam, żeby... to nie jest burdel! No, to jest burdel, ale niech mnie diabli, jeśli nie jestem szlachcicem i człowiekiem honoru. Naprawdę mi nie ufasz? Gubernator poprosił mnie tylko o małą przysługę i muszę mu się podporządkować, to wszystko!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Tak, słyszałam o paru takich 'szlachcicach', tak, co nie? Widziałam ich również w twoim towarzystwie. Kurtyzany są dla nich codzienną potrzebą! 'Wysokie' sfery, 'Godna' rozrywka, psia mać! Nawet małżeństwo ich nie powstrzymuje przed odwiedzaniem tych... dam. Cholera, nie miałam pojęcia, że jesteś dokładnie taki sam. Nawet nie jesteśmy... Do diabła z tobą, z wami wszystkimi!";
			link.l1 = "Mary, czekaj! Cholera...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Zasłużyliśmy na wakacje, tak, co nie? Myślisz, że zniosą widok damy w czerwonym płaszczu? Wyobraź sobie te wszystkie szepty po kątach? Ktoś na pewno zemdleje, to byłoby zabawne, tak, co nie?";
			link.l1 = "Mary, moja droga, to nie jest ten rodzaj przyjęcia, na które zabiera się damę... przynajmniej nie taką damę jak ty. Cóż, to trochę skomplikowane, ale pozwól, że wyjaśnię...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "„Wow, nie kłopocz się. Po prostu powiedz mi wprost: nie jestem dość dobra dla tych bubków w perukach. Prosta dziewczyna, dla zabawy, co? Wstydzisz się pokazać się ze mną w pobliżu? Nie dość dobra na wystawne przyjęcia, tak, szanowny monsieur Charles de Maure?”";
			link.l1 = "Nie, wcale nie. Jesteś niesamowita i nie obchodzi mnie, jakie wrażenie robimy na ludziach wokół nas. Gubernator, jak zawsze, próbuje rozwiązać swoje problemy z moją pomocą. Będę jak cenne trofeum w pokoju. Interesujący gość, aby zaimponować szlachetnym nicponiom.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Więc nie jestem dla ciebie dobra, tak, co nie? Rozumiem, w porządku, szlachta jest dla szlachty, a chłopi dla prostych rozrywek. Powodzenia z twoją wyższą klasą. Porozmawiamy, gdy wrócisz na naszą skromną ziemię, tak, co nie?";
			link.l1 = "Mary, czekaj! Cholera...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Powodzenia z twoją wyższą klasą. Porozmawiamy, gdy wrócisz na naszą skromną ziemię, tak, co nie?";
			link.l1 = "Mary, no weź!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Spójrz na to, tak! Nasz zagubiony w wyższych sferach kapitan!";
			link.l1 = "Ha, jesteś prawdziwym dżentelmenem: ledwo schowałeś szablę do pochwy, a już zasypujesz mnie komplementami. Dzięki za pomoc. Naprawdę mnie uratowałeś, tak, co nie? Przedstaw się, proszę, bo pierwszy raz cię widzę. Długo już jesteś na Wyspie?";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Zniknąłeś w burdelu na cały dzień i teraz ludzie w mieście gadają. Charles, podaj mi tylko jeden dobry powód, dla którego powinnam z tobą teraz rozmawiać, zamiast, powiedzmy, wbić ci Narwala w... brzuch? Niezbyt ci na mnie zależy, tak, co nie?!";
			link.l1 = "Mary, wszystko ci wyjaśnię, ale później. Powinienem się przygotować i pójść na pojedynek. Możesz mnie zabić, jeśli przeżyję. Tymczasem, proszę, zajmij się naszym nowym statkiem, tak, co nie? Wygrałem go wczoraj wieczorem jako nagrodę w grze karcianej.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Zapomnij o statku, wspomniałeś coś o pojedynku, tak? Tubylcy opowiadają różne bzdurne historie, na które nie zwracam uwagi. Mówią, że masz walczyć albo z synem króla, albo z samym pieprzonym papieżem. Powiedz mi teraz, co do diabła się dzieje?!";
			link.l1 = "Ten człowiek to bękart bardzo wpływowego szlachcica, hrabiego de Levi Vantadur. To on pierwszy wyzwał mnie na pojedynek, i muszę wygrać bez krzywdzenia go, by uniknąć gniewu jego ojca.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Podczas gdy ja będę siedziała na tyłku w wannie, którą właśnie wygrałeś? Oszalałeś, Charles?";
			link.l1 = "Obawiam się, że tak musi być. Gubernator przydzielił mi kilku szlachetnych oficerów jako sekundantów, aby uniknąć jakichkolwiek nieporozumień później. Nie mogę wziąć ciebie ani żadnego z chłopaków ze sobą ze względu na oficjalną integralność pojedynku. To zbyt poważne, przepraszam.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Wiesz, co teraz zrobię? Pójdę na ten przeklęty statek i porządnie się upiję, tak! Rób, co chcesz, ale jeśli ten szlachetny łotr nie zdoła cię zabić, przysięgam, że zrobię to sama!";
			link.l1 = "Mary, wszystko będzie dobrze, zaufaj mi. Teraz, czekaj... Cholera! I znowu to samo!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "„O, jesteś! Nie dostaliśmy od ciebie żadnej wiadomości przez cały dzień! Martwiliśmy się, słysząc plotki krążące na targu. Mówią, że grałeś o statki i kobiety, a nawet wdałeś się w pojedynek z jakimś koronowanym księciem albo nawet samym papieżem! Co do diabła się dzieje?”";
			link.l1 = "To skomplikowane, Mary. Wyjaśnienie zajmie trochę czasu. Udało mi się jednak zdobyć fregatę. Musisz się nią zająć, podczas gdy ja rozwiążę mój spór z jej poprzednim właścicielem.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Więc mieli rację co do pojedynku, tak, co nie? Kim jest ten zadufany szlachetny drań? Dlaczego z nim walczysz?";
			link.l1 = "Muszę. To skomplikowane, ale w skrócie: wygrałem jego statek i jego... damę. Publicznie oskarżył mnie o oszustwo i wyzwał na pojedynek. Ten człowiek jest bękartem bardzo wpływowego szlachcica, hrabiego de Levi Vantadur. Będę musiał zrobić wszystko, by go nie zranić.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Bab? Rozumiem, że można grać o statek, ale... kobieta, naprawdę? Naprawdę mówili prawdę na ulicach, co? Przyznajesz to tak po prostu?! Jakbym była... jedną z twoich durnych marynarzy?";
			link.l1 = "Cholera jasna, Mary, to wcale nie tak! On wygrał ją od gubernatora, ja ją odzyskałem od niego, by ją uwolnić, i tyle. Nic więcej za tym nie stoi, przysięgam!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "„Cóż, może to normalne wśród was, szlachty, ale ja taka nie jestem, tak, co nie! Rób, co chcesz, mów, co chcesz... idź i umieraj za nią, jeśli chcesz! Ja pójdę na ten przeklęty statek, który wygrałeś, i się upiję. Wierzyłam, że to było prawdziwe i... będzie trwało wiecznie. Chyba oczekiwałam za dużo!”";
			link.l1 = "Mary, nie obchodzą mnie te babsztyle! Poczekaj tylko, proszę... Cholera! I znowu to samo...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, przybyłeś po mnie, tak, co nie! Wiedziałam, nigdy nie wątpiłam! Jestem tak szczęśliwa, że cię widzę!";
			link.l1 = "Ja też, Mary! To mnie zabijało przez cały ten czas. Dzięki Bogu, że nic ci nie jest!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "A tak przy okazji, co dokładnie zrobiłeś, że uwolnili mnie tak łatwo? Bez porządnej bójki czy strzelaniny, tak, co nie! A, i widziałam tę piękną damę na pokładzie, kiedy mnie wyciągali. Co się stało, Charles?";
			}
			else
			{
				dialog.text = "Co dokładnie zrobiłeś, by mnie tak po prostu uwolnili? Bez walki, bez oddania strzału, tak, co nie? Widziałam na pokładzie kilku brytyjskich pawiów, kiedy mnie wyprowadzali. O co w tym wszystkim chodziło, Charles?";
			}
			link.l1 = "Ważne, że znowu jesteś przy mnie. Zawiodłem cię, Mary. Tak mi przykro! Mam nadzieję, że znajdziesz w sercu wybaczenie dla mnie! Nienawidzę, jak ostatnio się rozstaliśmy.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Już to zrobiłam. Przepraszam również, tak, co nie! Gdybym tylko nie brała tak do siebie twoich interesów z tą damą... ustawiłabym porządną wachtę tej nocy. Nigdy by nas tak łatwo nie pokonali! To było takie głupie z mojej strony!";
			link.l1 = "Co było, to było. Kocham cię i nigdy cię już tak nie opuszczę. Obiecuję!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Wiedziałam, że mnie nigdy nie opuścisz, tak, co nie? Przepraszam, że kiedykolwiek w ciebie zwątpiłam, Charles! Wydaje się, że lepiej nie wiedzieć, co dokładnie zrobiłeś, co nie? Znów jesteśmy razem i to się liczy.";
			link.l1 = "Nie mam przed tobą żadnych tajemnic. Powiem ci...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Co za historia... wątpię, by ktokolwiek inny w to uwierzył, tak, co nie? Wiedziałam to od początku! Wiedziałam, że twoja 'zabawna' noc to jakieś podejrzane sprawy! Ci wszyscy szlachetni pawie... bezduszne bestie! Przynajmniej nie pomyliłam się co do ciebie, wiedziałam, że jesteś inny, tak, co nie?";
				link.l1 = "Jestem całkiem pewna, że wiele osób uważa mnie za znacznie gorszą. Prawdziwy potwór z bajek.";
			}
			else
			{
				dialog.text = "Co za historia... wątpię, żeby ktoś inny w to uwierzył, tak, co nie? Wiedziałam od początku! Wiedziałam, że twoja 'zabawna' noc to była podejrzana sprawa! Polityka, szpiedzy, spiskowcy. I znów uratowałeś nas wszystkich, tak, co nie? Mój bohater!";
				link.l1 = "Nie jestem tego pewien. Istnieje duże prawdopodobieństwo, że wojna z Brytanią rozpocznie się za kilka tygodni. Ale zrobiłem, co musiałem, Mary. Jesteś dla mnie wszystkim.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Nie obchodzi mnie, co ludzie myślą, jeśli tak jest, będziesz moim potworem, Charles! Inni powinni albo iść i płakać z tego powodu, albo zmierzyć się ze mną! Pamiętaj, że zawsze będę przy twoim boku, tak, co nie?";
			}
			else
			{
				dialog.text = "„Wiem, Charles. Zawsze wiedziałam, ale miło usłyszeć, jak to mówisz. Wiedz jedno - zawsze będę przy tobie, tak, co nie?”";
			}
			link.l1 = "   Nigdy w to nie wątpiłem, Mary. Ruszajmy, chłopcy się martwią. Czas postawić żagle i wynosić się stąd do diabła. Jesteś znów przy mnie, a horyzont sam nigdzie się nie wybierze.   ";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Tak, tak, Kapitanie!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, czy to naprawdę ty?! Prawie straciłam wszelką nadzieję, tak, co nie?! Boże, tak bardzo za tobą tęskniłam! Proszę, wybacz mi, tak, co nie?!";
			link.l1 = "Nie, wybacz mi, nie spodziewałem się tego... Dzięki Bogu, że dotarłaś, Mary! Jestem taki szczęśliwy!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Mówiąc o wybaczaniu - szczerze mówiąc, zastanawiam się, czy powinnam cię zastrzelić, czy przytulić. Lepiej mi powiedz, co tu się do diabła dzieje, tak, co nie?";
			link.l1 = "Ko-cham cię, Mary. To wszystko, co chciałem ci powiedzieć, tak, co nie?";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Tak, jakby to było pomocne, ale... Do diabła, ja też, Charles. Też cię kocham, tak, co nie? Boże, wreszcie jesteśmy razem!";
			link.l1 = "I nie chcę marnować czasu, jaki mamy, na rozmowy o rzeczach, które nie mają znaczenia. Chodź ze mną, a nie odważę się zostawić cię tej nocy. Nawet jeśli niebo zacznie się walić na to nędzne miasto. Nigdy cię już nie opuszczę. Nigdy.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Zdaje się, lepiej bym nie wiedziała, co dokładnie zrobiłeś, tak, co nie? Jesteśmy znowu razem i to się tylko liczy.";
			link.l1 = "Nie mam przed tobą żadnych tajemnic. Powiem ci...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "„Czy mówisz, że ta... markiza pomogła ci mnie sprowadzić? I prawie wywołałeś wojnę między Anglią a Francją, tak, co nie? Nie zrozum mnie źle - to takie romantyczne i w ogóle, ale co teraz się stanie? ”";
			link.l1 = "Nie mam pojęcia, Mary. Znów jesteśmy razem, reszta jest nieistotna. Jeśli ci u władzy nie zdołają tego zamieść pod dywan... cóż, jestem gotów wypełnić swój obowiązek wobec Korony.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "A ta twoja markiza? Czy ją też sprowadziłeś z powrotem? Portugalczyk mówił o niej w samych superlatywach. Zapewniał mnie, że oparłeś się jej zalotom niczym zamek Bastille. Chcę mu wierzyć, tak, co nie? ale muszę to usłyszeć od ciebie!";
			link.l1 = "Nic się nie dzieje między mną a panią Botot, Mary. Pomogłem jej, ona pomogła mi, to wszystko. Mówiąc o Bartholomeuszu, gdzie on jest?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Już go nie ma, tak, co nie? Postawił żagle zaraz po tym, jak mnie tu przywiózł. Nigdy nie poszłabym do tego przeklętego domu publicznego, więc wynajął mi pokój, zapłacił z góry na kilka tygodni i po prostu odszedł. Och, prawie zapomniałam, tak, co nie! Mam dla ciebie list!";
			link.l1 = "List? Od Bartholomew Portugalczyka? To coś nowego. Nie podoba mi się, dokąd to zmierza...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Śmiało, przeczytaj to. Ja pójdę zobaczyć chłopaków. Pewnie się martwili. Czy wszyscy dotarli? Mam nadzieję, że nie masz nic przeciwko, że wypijemy kieliszek lub dwa na dole. Nie pakuj się znowu w kłopoty, tak, co nie!";
			link.l1 = "Jasne, ale proszę, bądź z nimi ostrożna, Mary. Wolałbym spędzić z tobą wieczór, zamiast musieć targać pijane ciała z powrotem na statek. Boże, wciąż nie mogę uwierzyć, że cię odzyskałem!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Plaża, ty, ja i dobre wino - Charles, to takie romantyczne! Powinniśmy robić to częściej, tak, co nie?";
			link.l1 = "Cieszę się, że ci się podoba. Myślę, że od teraz będziemy częściej znajdować czas dla siebie na takie okazje.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "O czym ty mówisz? Coś stało się z okrętem, tak? Dlaczego klęczysz, moja miłości?";
			link.l1 = "Bo kocham cię, Mary. Ty o tym wiesz, ja o tym wiem, wszyscy o tym wiedzą. Więc tutaj i teraz, wobec morza i nieba, proszę cię, Mary Casper - o zaszczyt stanięcia ze mną przed ludźmi i Bogiem przez tyle dni, ile nam dane z góry. Ja, Charles de Maure, kawaler de Monper, pytam cię - czy zostaniesz moją żoną?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "Marzyłam, by to usłyszeć, tak, co nie? Ja... znasz moją odpowiedź, Charles... och, przepraszam!";
				link.l1 = "Nie szkodzi, to tylko wino i nigdy nie lubiłem tej koszuli...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, oczywiście, że tak! Tak, tak, tysiąc razy tak!!! Ty... to miejsce... nic nie może mnie bardziej uszczęśliwić!!! O Boże, jestem taka szczęśliwa, tak, co nie?";
				link.l1 = "Uszczęśliwiłeś mnie, Mary. I chcę wznieść toast za ciebie, moja płonąca Karaibska Słońce!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Pijmy za ciebie, mój kapitanie i przyszły mężu, tak, co nie! Jesteś najlepszym, co mi się kiedykolwiek przytrafiło!";
			link.l1 = "Ale to dopiero początek - za nas! I za naszą wspólną przyszłość! Przed nami jeszcze tyle!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Piję za ciebie, mój kapitanie i przyszły mężu, tak, co nie! Jesteś najlepszym, co mi się kiedykolwiek przytrafiło!";
			link.l1 = "Ale to dopiero początek - za nas! I za naszą wspólną przyszłość! Tyle przed nami!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, opat Benoit na Martynice znów, więc możemy działać, tak, co nie? Ale nie założę sukni, nawet dla kościoła, mam nadzieję, że się nie obrazisz?";
			link.l1 = "Mary, kocham cię w każdym stroju i... no cóż, wiesz. Możesz nosić, co tylko zechcesz, rozprawię się z każdym, kto będzie miał z tym problem! Ale, chciałem tylko poradzić się ciebie w sprawie gości i ceremonii.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "Wiesz, większości z tych, którzy szczerze cieszyć się mogą naszym szczęściem, nawet nie wpuszczą do tego miasta, nie mówiąc o kościele, tak, co nie. Dlatego - pobierzmy się tutaj z wszystkimi ważnymi ludźmi, jak się należy, a potem popłyniemy na Isla Tessoro i uczcimy to jak należy z prawdziwymi przyjaciółmi! Co o tym myślisz, tak, co nie?";
				link.l1 = "Świetna opcja! Więc zróbmy to. Porozmawiam z opatem Benoit, ale musimy wysłać zaproszenia i jeszcze więcej...";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = " Wiesz, nie mam wielu przyjaciół poza naszymi chłopakami z załogi. Więc zaproś tych, których uważasz za stosownych, a ja po prostu będę zadowolona z tego, co jest, tak, co nie!";
				link.l1 = "Jak mówisz, kochanie. Porozmawiam z opatem Benoit i wszystko zorganizuję, jesteś godna najwspanialszej ceremonii.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Nie martw się, jako dobra żona wezmę część przygotowań na siebie, tak, co nie? Napiszę do naszych przyjaciół i wszystko zorganizuję, ale najpierw powiedz mi: jak widzisz to wesele?";
			link.l1 = "„Mój ideał to ty, ja i nasi najbliżsi przyjaciele. Po wszystkich oficjalnych twarzach tutaj na Martynice, będziemy pragnąć szczerości.”";
			link.l1.go = "LongHappy_10";
			link.l2 = "Musimy zapamiętać ten dzień. Zwołaj wszystkich! Nikt nie zostanie pominięty!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "Z tobą, ceremonia z kapelanem okrętowym na rufowym pokładzie, pod zachodem słońca na morzu, byłaby wystarczająca, tak, co nie. Ale jeśli tego chcesz - będziemy świętować! Charles... Zaraz się rozpłaczę, przytul mnie, tak, co nie...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "Tak, uspokoiłam się, tak, co nie. Przepraszam, to wszystko jest takie niezwykłe. Ale Charles, jako dobra żona, zajmę się organizacją. Musimy też zorganizować przyjęcie dla chłopaków, tak, co nie, ale mało prawdopodobne, że cała załoga zmieści się w kościele. Zajmę się umową z tawerną, ale będziemy potrzebować alkoholu i pieniędzy - wiesz, jak marynarze lubią się bawić.";
			link.l1 = "Dobrze, tak właśnie zrobimy. Co muszę przygotować?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "Myślę, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" pesos wystarczy, tak, co nie. "+sti(pchar.questTemp.LongHappy.MarryRum)+" beczki rumu, nie ma nic gorszego niż brak alkoholu. Jak tylko zbierzesz wszystko, czego potrzebujemy, przyjdź do tawerny, ja zajmę się resztą.";
			link.l1 = "Dobrze, kochanie, zrobię to.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Zrozumiano, zabierajmy się do roboty. Ale będziemy musieli odwiedzić Sharptown i wszystko przygotować. Myślę, że pięćdziesiąt beczek rumu i kilka tuzinów beczek wina wystarczy w zupełności, tak, co nie? Ale, na wszelki wypadek, będę potrzebować trzysta tysięcy pesos.";
			link.l1 = "To dużo, ale okazja jest tego warta. Zbieram to, nie martw się. Teraz wpadnę do opata i pójdę do Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Świetnie, zbierzemy wszystkich razem, tak, co nie! Ale będziemy musieli odwiedzić Sharptown i przygotować wszystko - będziemy potrzebowali galeonu pełnego trunków! Myślę, że sto beczek rumu i pięćdziesiąt beczek wina wystarczy. Ale, na wszelki wypadek, dodam pięćset tysięcy pesos. Jeśli świętowanie skończy się szybko, co to za świętowanie, tak, co nie?";
			link.l1 = "Tak, nasi przyjaciele nie mogą umrzeć z pragnienia - zdobędę wszystko, nie martw się! Teraz muszę wpaść do opata i udać się do Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Wszystko gotowe, Charles, tak, co nie? Zajmę się rozładunkiem trunku, idź do miejscowej tawerny, spotkaj barona i wręcz zaproszenia. Czekaj tutaj, tak, co nie?";
			link.l1 = "Jesteś u steru, kochany! To ja po prostu gdzieś się pokręcę. Naprawdę nie sądziłam, że przygotowania do wyprawy w dżunglę Maine będą łatwiejsze niż do ślubu.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Załatwiliśmy to tutaj, Charles, tak, co nie! Wszystko zaaranżowałam, uwierz mi – będzie cudownie! Jedna rzecz jest kłopotliwa: miejscowa tawerna spłonęła podczas jakiejś uczty tydzień temu. Ale prawie ją odbudowali, większą i lepszą niż stara, tak, co nie! Wszyscy powinniśmy się pomieścić.";
			link.l1 = "Obyśmy tylko nie spalili tego. Naprawdę polubiłem 'Starego Dzięcioła'! W każdym razie, mamy jeszcze dużo do zrobienia. Czas na wypłynięcie. I tak, Mary - jesteś najlepsza, wiesz o tym, tak, co nie?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "No to ruszamy, co? Goście przybyli, kościół gotowy. Wiem, że jesteśmy bliżej niż wielu małżonków, a to tylko kilka ważnych słów w pięknej sali, ale niech mnie diabli – w tym starożytnym, tubylczym mieście mniej się martwiłam, tak, co nie?";
			link.l1 = "To całkowicie normalne, moja miłości, całkowicie normalne. Też się denerwuję. Myślę, że ojciec Benoit już czeka, pójdę do niego i dowiem się, kiedy zacznie się nabożeństwo.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Zgoda, przejdę się po mieście na chwilę, chcę się przygotować, tak, co nie! Charles, rozumiesz, że nie ma odwrotu?";
			link.l1 = "Mary, kochana, dla mnie nie było odwrotu odkąd się spotkaliśmy. Czekałem na ten dzień z całego serca. Nie martw się, wszystko będzie dobrze.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Tak.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Tak.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Tak.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Ja, Charles Henry de Maure, kawaler de Monper, biorę ciebie, Mary Casper, za żonę, aby mieć i trzymać od tego dnia naprzód, na dobre i na złe, w bogactwie i w biedzie, w chorobie i w zdrowiu, aż śmierć nas nie rozłączy. Zgodnie ze Świętym Prawem Bożym, w obecności Boga, składam tę przysięgę.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Ja, Mary Casper, biorę ciebie, Charlesie de Maure, za męża, abyśmy byli razem od tego dnia na dobre i na złe, w bogactwie i w biedzie, w zdrowiu i w chorobie, aż śmierć nas nie rozłączy. Według Świętego Prawa Bożego, w obecności Boga, składam tę przysięgę.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "To jest niewiarygodne, tak, co nie? Ja... ja płaczę, przepraszam Charles, ja... mój nos zrobił się czerwony, tak, co nie?";
			link.l1 = "Mary de Maure, moja żono, jesteś piękna tego dnia, jak i każdego innego!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Dziękuję Ci, Charles, dziękuję... Wszystko jest takie uroczyste i wspaniałe! To najlepszy dzień mojego życia, tak, co nie!!! Spójrz, jak wszyscy są szczęśliwi! Ale, czas, abyś przeszedł się wśród gości i przyjął gratulacje! Kiedy skończysz - wracaj - sprawdźmy, co u chłopaków w tawernie.";
			else dialog.text = "Dziękuję, Charles, dziękuję... Wszystko jest takie uroczyste i cudowne! To najlepszy dzień mojego życia, tak, co nie!!! Spójrz, jak wszyscy są szczęśliwi! Ale, czas, byś przeszedł się wśród gości i przyjął gratulacje! Kiedy skończysz, wróć, oczekują nas w Sharptown.";
			link.l1 = "Zaraz to zrobię, kochanie. Jeden pocałunek i idę!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, mój drogi, czy już rozmawiałeś z gośćmi?";
			link.l1 = "Jeszcze nie, bądź cierpliwa, kochanie, wkrótce wrócę.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Tak, nigdy wcześniej nie słyszałam tylu gratulacji naraz. I wiesz co - większość z nich mówiła szczerze!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "„Tak, tak! Mówili mi też wiele miłych rzeczy! Nie wszyscy, oczywiście, niektórzy są wyraźnie zaskoczeni moim strojem, tak, co nie! Ale jestem tak szczęśliwa, że połowa rzeczy, które ludzie mówią, po prostu mnie omija. A w ogóle, wszyscy są tacy uroczy. Charles, chłopaki w tawernie już na nas czekają - powinniśmy do nich iść. Będą szczęśliwi, mogąc pogratulować swojemu kapitanowi, tak, co nie!”";
				link.l1 = "Idziemy teraz. Ale chciałbym zakończyć ten dzień w bardziej romantycznym miejscu niż pokój w tawernie portowej. Mam nadzieję, moja żono, że nie masz nic przeciwko spędzeniu tej nocy w naszej kajucie? Poza tym, teraz na statku nie ma wachty...";
			}
			else
			{
				dialog.text = "Tak, tak! Powiedzieli mi też tyle miłych rzeczy! Nie wszyscy, oczywiście, niektórzy wyraźnie są zaskoczeni moim strojem, tak, co nie! Ale jestem tak szczęśliwa, że połowa rzeczy, które ludzie mówią, po prostu mnie omija. A w ogóle, wszyscy są tacy słodcy. Charles! Ale czekają na nas w Sharptown, kiedy wyruszamy w morze?";
				link.l1 = "Natychmiast. Nie możemy pozwolić naszym gościom wypić wszystkich zapasów! Mam nadzieję, moja żono, że nie masz nic przeciwko spędzeniu tej nocy w naszej kajucie?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Choćby w chacie na bezludnej wyspie, ale tylko z tobą, oczywiście!";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Wiem. Ja też cię kocham. Chodźmy, zanim chłopaki wypiją cały nasz rum i podpalą tawernę.";
			else link.l1 = "Ja też. Też cię kocham. Więc - wyruszmy w rejs!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "O mój drogi, jestem taka szczęśliwa! Dziś jest wspaniały dzień...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Urwij mu tę nieumywaną głowę, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "U mnie wszystko w porządku, tak, co nie? Jak Nathan, czy żyje?";
			link.l1 = "Tak dużo krwi... Dannie, czy on oddycha? Widzę, że oddycha!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Szybciej, kochanie, nie trać czasu!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Wygraliśmy, tak, co nie! Wybacz mi, jestem spóźniona. Utknęliśmy na górze, było tam tuzin tych drani, więc byłam trochę zajęta!";
			link.l1 = "Nie ma sprawy, poradziłam sobie. Cieszę się, że mogłam wreszcie zakończyć tę historię z Jacques'em... w końcu. Dostał to, na co zasłużył.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "To skończ tutaj i wracaj do Sharptown! Powinniśmy sprawdzić, co u Nathana, tak, co nie! On ryzykował dla nas życie!";
			link.l1 = "Masz rację, moja miłości. Idź, jestem tuż za tobą.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "A tak przy okazji, kochanie, znaleźliśmy Marcusa, tak, co nie? Był w ładowni, związany i nieprzytomny.";
			link.l1 = "On żyje?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Jest ranny, ale będzie dobrze. Nie złamiesz naszego barona, tak, co nie! Ledwo się obudził, a już gotowy do walki.";
			link.l1 = "To nasz dobry stary Marcus! Cóż, skończ tutaj i na brzeg.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Tak mi przykro, Charles, tak, co nie, ja... Poszłam na spacer. Widziałam, że wróciłeś, słyszałam, że wszyscy żyją w euforii zwycięstwa, ale ja... Ale co ze mną jest nie tak, tak, co nie!";
				link.l1 = "Wszystko będzie dobrze, kochanie, wszystko będzie dobrze. Ja też jestem smutna. Ale wygraliśmy, a Jacques Barbazon zapłacił za wszystko, co zrobił.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "„Czuję się tak źle z powodu Gino, Charles, tak, co nie! Kiedy się dowiedziałam, nie mogłam w to uwierzyć! Jak się masz?”";
					link.l1 = "Nie mogę w to uwierzyć... wyszło tak głupio, nie wyobrażałam sobie tego dnia w ten sposób.";
				}
				else
				{
					dialog.text = "Znowu wygraliśmy, tak, co nie! Mój mąż to burza dla zbuntowanych baronów Bractwa Wybrzeża! Przyjaciele żyją, a wrogowie martwi - chwalebny dar, tak, co nie!";
					link.l1 = "Tak, co za świętowanie, ale udało się nam, moja miłości. Udało się nam.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Ledwo trzymasz się na nogach, tak, co nie! Chodź, Dannie znalazł nam dom tutaj na obrzeżach, nie chcę teraz wracać na statek. Usiądziemy i wypijemy za naszych poległych przyjaciół. To wszystko jest za dużo na trzeźwą głowę, tak, co nie.";
			link.l1 = "Tak, Mary, chodźmy.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Czuję się tak źle z powodu Gina, Charles, tak, co nie! Kiedy się dowiedziałam, nie mogłam w to uwierzyć! Jak się masz?";
				link.l1 = "Też nie mogę w to uwierzyć... wyszło to tak głupio, nie wyobrażałam sobie tego dnia w ten sposób.";
			}
			else
			{
				dialog.text = "Przepraszam, że się spóźniłam, mój drogi, tak, co nie? Poszłam na spacer, a potem zobaczyłam, jak się zbliżasz i pobiegłam najszybciej, jak mogłam! Dannielle mnie uspokoiła, kiedy Gino powiedział 'niebezpieczeństwo minęło', tak, co nie? Cieszę się, że wszystko jest teraz w porządku!";
				link.l1 = "Ja też, kochanie. I wygraliśmy. Barbazon nie żyje, baronowie zbierają to, co zostało z ich załóg. Walka dobiegła końca.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, widzę, że ledwo stoisz na nogach, ale nikt nie może znaleźć Tichingitu.";
			link.l1 = "Jan dał mi jakąś wskazówkę... Wydaje mi się, że nasz surowy maskogue poszedł na popijawę. Przejdźmy się do Sabo-Matila Cove, kilka osób widziało, jak wyruszył w tamtym kierunku.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "„Cóż, to nasz surowy tubylec, tak, co nie? Chodź, Dannie znalazł nam dom tutaj na obrzeżach - lunatykujesz w tym momencie, Charles, tak, co nie?”";
			link.l1 = "Tam to jest ... porwij mnie, moja piękna squaw. I niech jutro wszystko wydaje się złym snem.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Nie zrozum mnie źle, mój mężu, w kościele wszystko było po prostu luksusowe, ale tutaj atmosfera jest wyraźnie bardziej duszna, tak, co nie! No cóż, to wszystko, Charles, teraz, gdy wszystkie kłopoty są już za nami, możemy się zrelaksować.";
			link.l1 = "„Cóż, to nie do końca 'wszystko', moja żono - nasze życie trwa razem! Ogólnie można powiedzieć, że dopiero się dziś zaczęło. Więc chodźmy, napijmy się z naszymi chłopakami, a potem - cóż, pamiętasz: kajuta, wino i my...”";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "Mój mąż... To brzmi tak słodko, tak, co nie! Teraz jesteś mój, na zawsze!";
			link.l1 = "Jestem twoja już od dawna i będę na zawsze, moja miłości...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "Jestem taka szczęśliwa, Charles! A teraz, musimy znów się ruszać, tak, co nie?";
			link.l1 = "Oczywiście, kochanie! Ramię w ramię, razem i na zawsze!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Obawiam się, że ta pandemia odciska swoje piętno na twoich dziewczynach, Rodrigo. Trzymaj je zajęte robieniem na drutach czy czymkolwiek!";
			link.l1 = "Ta rozmowa wyraźnie donikąd nie prowadzi. Ustaliliśmy, że jutro pójdziemy do kościoła. Pomodlić się... oczywiście.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Jestem z ciebie dumna, mój ukochany!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "„Cóż, Charles...”";
			link.l1 = "Co znowu masz na myśli, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "„(śmiech) To, że ja i Alan chcieliśmy zrobić na wyspie to samo, co ty zrobiłeś tutaj”";
			link.l1 = "Twój... Alan?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Tak, był niesamowitym marzycielem, moglibyście zostać świetnymi przyjaciółmi, gdyby żył!";
			link.l1 = "No cóż, nasze gusta na pewno spotkały się w jednej kwestii!";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Co? Ha-ha-ha! Przestań, Charles!\nTak czy inaczej, to niesamowite, daliśmy tym ludziom tyle radości!";
			link.l1 = "„Daliśmy im szansę na szczęście, ale resztę zrobili sami. Więc, co o tym myślisz?”";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Znajdź mnie później, a się dowiesz...";
			link.l1 = "Oczywiście, że tak!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Mary_LoveSex", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Lubię ciemność i ciasne przestrzenie. Sprawiają, że czuję się spokojna. W końcu mogę zebrać myśli\nTo tak, jakby wszystkie zmartwienia i kłopoty... zniknęły, tak! Naprawdę tęsknię za tym uczuciem...";
			link.l1 = "Musisz zobaczyć się z lekarzem.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Prawda. To jakbyś wrócił na 'Ceres Smithy'.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "Szkoda, że nie jestem sama. W ciszy, w ciemności i w samotności, tak, co nie? To byłoby idealne.";
			link.l1 = "Tak trzymaj, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "Raz krab wpełzł mi do łóżka - pociąłem go i zjadłem. Aye.";
			link.l1 = "Tak trzymaj, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Zamaskowany drań! Ała! Pomóż mi, mój drogi - musimy rozwalić te kraty!";
			link.l1 = "Cicho! Próbuję wymyślić, co zrobić!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Kochańcu, te zamaskowane diabły są wszędzie! Zrobiły ogromną wyrwę w kadłubie i pełzają przez nią jak te kraby! Musimy wszystkich wyciąć, tak, co nie?";
			link.l1 = "Mary, stay here, find the senior officer, and take command! Take the ship out of the battle; we won't withstand another boarding!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "A dokąd się wybierasz? Nie mam zamiaru cię puścić!";
			link.l1 = "Muszę pomóc Hercule'owi i naszej załodze! Zaufaj mi, Mary!";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Tak tak, kochany!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Zwycięstwo, aye! Chodź do mnie, kochanie! Chcę cię na godzinę czy dwie!";
			link.l1 = "Ech...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Chodźmy!";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "„Hej, Hercule! Tak się cieszę, że cię widzę, siwa brodo!”";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary, Mary, zaczekaj! Potrzebuję twojego raportu!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Hę? No, wygraliśmy, tak! Ta przeklęta łajba uciekła. Rozłupałam czaszkę jednego drania na pół!\nUf, przeklęte guziki!";
			link.l1 = "O, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "O Boże, nie patrz na mnie, kochany! Zaraz... uff!";
			link.l1 = "Trzymaj się, dziewczyno. Jestem tutaj!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! Muszę z tobą porozmawiać, tak, co nie! Serio!";
				Link.l1 = "Co się stało, Mary? Czy jest jakiś problem?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Słucham, mój drogi kapitanie!","Tak, "+pchar.name+"Tak, co nie? Cała zamieniam się w słuch!","Masz dla mnie jakieś zadanie, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, zamierzam odwiedzić stare indiańskie miasto Tayasal. Nie będę cię oszukiwał: ta podróż jest bardzo niebezpieczna, a co więcej - obejmuje teleportację przez idola, o którym ci mówiłem. Czy... pójdziesz za mną?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, daj mi pełny raport o statku.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Chcę, abyś kupował pewne towary za każdym razem, gdy jesteśmy zacumowani.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, potrzebuję twojej porady.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, mam dla ciebie rozkaz...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("„Kochanie, chcę cię teraz. Czy to ci pasuje, tak, co nie?”","Mary, co powiesz na to, żebyśmy... zostali razem przez jakiś czas? Tylko we dwoje, tak, co nie?");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, wynajmijmy pokój i zostańmy razem?","Kochanie, chcę z tobą zostać na osobności... co powiesz na to, by wynająć pokój i zapomnieć o wszystkim na kilka godzin?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "To na razie nic takiego, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, to prawdziwa piękność, tak, co nie? Naprawiliśmy tę maleńką dziurkę poniżej linii wodnej i wysuszyliśmy żagle. Co- Czego się spodziewałeś? Nie patrz na mnie tak, nigdy nie studiowałem na intendenta.";
			Link.l1 = "Przepraszam, Mary, naprawdę tego nie przemyślałem.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, ale u mnie wszystko w porządku! Mam już swoją garderobę i klingę. Ale dzięki, że pytasz, to takie miłe z twojej strony, tak, co nie?";
			link.l1 = "Ale ja nawet nie... Cokolwiek, zapomnij o tym, kochanie, wszystko jest w porządku.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Rozkazy?";
            Link.l1 = "Stój tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Podążaj za mną i trzymaj tempo!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mary, zmień amunicję do broni palnej.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybór rodzaju amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Natychmiast, mój kapitanie!";
            Link.l1 = "   ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Już się robi, kapitanie!";
            Link.l1 = "Ha, jesteś prawdziwym dżentelmenem: ledwo schowałeś szablę do pochwy, a już zasypujesz mnie komplementami. Dzięki za pomoc. Naprawdę mnie uratowałeś, tak, co nie? Przedstaw się, proszę, bo pierwszy raz cię widzę. Długo już jesteś na Wyspie?";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
