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

		case "Naemnik":
			dialog.text = "Jesteś dobry"+GetSexPhrase("","a")+"... cholernie dobry"+GetSexPhrase("","a")+". Ale zanim dokończysz sprawę, wysłuchaj mnie. Jestem pewien, że to, co powiem, cię zainteresuje.";
			link.l1 = "W porządku, możesz mówić przed śmiercią. Ale nie łudź się. Z tej jaskini już nie wyjdziesz.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Nadzorca portu, tak? To on cię przysłał po moją głowę?";
			link.l1 = "Bystrość cię nie opuszcza.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Wysłał cię, żeby mnie zabić, prawda? Nie schwytać, nie uwięzić, tylko zabić?";
			link.l1 = "Zgadza się. I co z tego?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Och... ale z ciebie "+GetSexPhrase("głupek","naiwna dziewczynka")+". Czy choć raz zastanowił"+GetSexPhrase("eś","aś")+" się, dlaczego tak bardzo zależy mu, żeby mnie zabić, a nie tylko wsadzić za kratki? Nie? Nawet nie masz pojęcia, kogo próbujesz uratować. Ten pająk portowy oplótł to miejsce pajęczyną kłamstw, a ty, "+GetSexPhrase("chłopcze","dziewczynko")+", jesteś w niej uwięzion"+GetSexPhrase("y","a")+".\nMyślisz, że on jest uczciwym zarządcą? Ha, uczciwość śni mu się chyba tylko po nocach! Sprzedaje namiary piratom i Holendrom. Wydaje tych, którzy mu zaufali. Taki śmieć zasługuje tylko na grób!";
			link.l1 = "Niech pierwszy rzuci kamieniem... Sam nie wyglądasz jak mnich.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Nie wyglądam i nie udaję. Mój miecz nigdy nie kłamie. Wystarczy jedno spojrzenie, by człowiek zrozumiał – śmierć przyszła po niego. Nie uśmiecham się do ofiar, nie ściskam im dłoni wiedząc, że są już skazane. Nie. Moje intencje są jasne. A ten urzędas...\nZdradza każdego, kto mu zaufał, udając, że im pomaga. Jest gorszy od każdego sukinsyna, którego posłałem do grobu.";
			link.l1 = "Załóżmy, że mówisz prawdę. Kto cię wynajął?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "Nie podam ci imienia – sam go nie znam. Ale to ktoś, kto przez niego wiele wycierpiał. Człowiek, który pragnie sprawiedliwości... albo zemsty. Nazywaj to jak chcesz – sens pozostaje ten sam. Pięćset dubloonów za głowę zgniłego urzędasa! Pomóż mi, a podzielimy się pieniędzmi po równo.";
			link.l1 = "Dość już twojego gadania! Powiesz wszystko, byle ocalić swoją żałosną skórę. Pozwolił"+GetSexPhrase("em","am")+" ci się wypowiedzieć, teraz czas umierać.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Piękna historia. Ale nie uwierzę ci na słowo, przyjacielu. Masz coś oprócz słów? Dowody, świadków? Czy to tylko kolejna sztuczka, by uniknąć śmierci?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Te papiery znaleziono w kajucie pirata, którego mój zleceniodawca pokonał w walce. Otrzymywał wskazówki od szefa portu. W notatkach wyraźnie wskazano trasy statków, godziny wypłynięcia oraz przewożone ładunki. Trasy zgadzają się z tymi, które zostały napadnięte, zniknęły lub zaatakowane.\nA co najważniejsze – charakter pisma w notatkach dokładnie odpowiada temu z dokumentów ładunkowych. Te dokumenty to klucz do jego zdemaskowania. Mój zleceniodawca chce, by znalazły się na zwłokach. Zwykły sąd to za mało.\nTen łajdak ma zbyt duże wpływy i wielu skorumpowanych przyjaciół. Gdyby sprawa trafiła do sądu, i tak by się wywinął. Tacy jak on nie powinni żyć. Śmierć w hańbie – to wszystko, na co zasługuje.";
			link.l1 = "Podły drań! Ludzie powierzają mu swoje losy, a on sprzedaje ich życie piratom! Wchodzę w to. Tacy ludzie nie mają miejsca na tym świecie.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "Mam klucz do jego domu – zdobyłem go od stolarza, który naprawiał meble w jego rezydencji. Wszystko szło gładko, dopóki nie okazało się, że nie mieszka tam sam. Kiedy przyszedłem zakończyć sprawę, jego żona była w środku.\nJej obecność zaskoczyła mnie. Nikt nie zapłaciłby za jej skórę, a władze z pewnością z większym zapałem szukałyby mordercy. Dlatego zmieniłem plan i zaczaiłem się przy administracji.";
			link.l1 = "Cholera. Całe miasto jest w gotowości, po prostu wejść i go zabić już się nie da. I co teraz?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "Obserwowałem miasto, czekając, aż opadnie kurz. Po mojej wizycie ten tchórzliwy szczur postanowił ukryć swoją małżonkę. Widziałem na własne oczy, jak weszła na pokład statku i opuściła port.\nTeraz został sam – to najlepszy moment, by dokończyć robotę. W nocy możesz zakraść się do jego nory i zamknąć ten rozdział. Potem zostaw notatki na widoku, by wszyscy poznali prawdę, jakim był plugastwem.\nAle ja nie mogę teraz wrócić do miasta. Ty natomiast... masz szansę. Nikt cię się nie spodziewa. Bez problemu się przekradniesz. Jego dom znajduje się w pobliżu miejskiego więzienia. Pięćset dubloonów! Połowa twoja, jeśli to dokończysz.";
			link.l1 = "Dobrze. Osobiście poślę tego drania do piachu. Te dokumenty zostaną w jego domu – wszyscy muszą poznać prawdę. Czekaj tutaj. Wrócę, jak tylko to będzie załatwione.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Czemu tak stoisz"+GetSexPhrase("","a")+"? Jakbyś w ziemię wrosł"+GetSexPhrase("","a")+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "Ty? Co do diabła? Jak się tu dostałeś?";
			link.l1 = "To, jak się tu dostał"+GetSexPhrase("em","am")+" - nie ma znaczenia. I sądzę, że w głębi duszy wiesz, po co tu przyszedł"+GetSexPhrase("em","am")+".";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "Nie, nie wiem! Jeśli przyszedłeś po nagrodę, przyjdź jutro do urzędu, wszystko oddam.";
			link.l1 = "Przestań udawać niewinnego! Wiem wszystko. Sprzedawałeś piratom informacje o statkach swoich klientów. Tak nikczemny człowiek nie zasługuje na pełnienie żadnej funkcji. Ba, nie zasługuje nawet na życie wśród uczciwych ludzi. Proszę pana, twoje miejsce jest wśród tobie podobnych – w piekle.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "O, nie-nie-nie! Nie! Wszystko źle zrozumiałeś! O-oni mnie zmusili... Przyszli do mnie i zagrozili mojej rodzinie, jeśli im nie pomogę... nie rozumiesz...";
			link.l1 = "Mam dość twoich żałosnych wymówek! Mam twoje notatki, w których domagasz się procentu za wskazówki! Twoje obłudne zachowanie jest odrażające i nie mam zamiaru dłużej tego znosić. Wyciągaj broń i broń się, jeśli masz odwagę!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "No i co słychać? Sprawa załatwiona?";
			link.l1 = "A wątpiłeś? Próbował z całych sił wydusić z siebie jakieś usprawiedliwienie, ale nic mu to nie dało. Zostawił"+GetSexPhrase("em","am")+" notatki w widocznym miejscu, tak jak się umawialiśmy.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Żałosne ślimaki takie jak on zawsze myślą, że mogą wykupić się od sprawiedliwości tanimi kłamstwami i pieniędzmi.";
			link.l1 = "Cóż, teraz już o niczym nie myśli. Dawaj moje pieniądze i pójdę.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Oto twoje dubony. Doskonała robota, muszę przyznać. Ale wiesz, gdybym miał wtedy w rękach coś poważniejszego, wszystko mogłoby potoczyć się inaczej... dla ciebie. W ciasnych ścianach domu nie ma za bardzo miejsca na wymachiwanie, więc wziąłem ten żałosny wykałaczka, planując szybko załatwić sprawę\nGdybym wiedział, jak się sprawy potoczą, wziąłbym solidniejsze narzędzie.";
			link.l1 = "Ha-ha. A nasz biedak mówił, że byłeś uzbrojony jak sam Roland przed Wąwozem Roncevaux!";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Heh. Cóż, strach ma wielkie oczy. Sam"+GetSexPhrase("","a")+" widzisz, jakim ostrzem prawie dotknąłem twojego serca.";
			link.l1 = "Chcesz powiedzieć, że gdybyś miał cięższy kawałek żelaza, mógłbyś ze mną konkurować?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "We władaniu bronią średniej wagi jestem mistrzem, to już fakt. Nie wierzysz? No cóż, podzielę się z tobą kilkoma sztuczkami, które nieraz mnie ratowały. Słuchaj uważnie - to nie są tylko słowa, ale coś, co pewnego dnia może uratować twoją skórę. Takich sekretów nie opowiada się byle komu.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			
			SetLaunchFrameFormParam("Minęła godzina...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Widzę, że naprawdę znasz się na swoim fachu. Dzięki za naukę. Ale jeśli to wszystko, to muszę już iść.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Bywaj, "+GetSexPhrase("kapitanie","kochanie")+". Mam nadzieję, że nie spotkamy się więcej w walce. Szkoda byłoby cię zabijać. Ha-ha.";
			link.l1 = "Nie miałbyś żadnych szans, nawet gdybym był"+GetSexPhrase("","a")+" pijany"+GetSexPhrase("","a")+" i stał"+GetSexPhrase("","a")+" na jednej nodze, heh! No, żegnaj, najemniku.";
			link.l1.go = "Naemnik_29";
		break;

		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);
			
			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);
			
			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");
			
			AddSimpleRumourCity("Mówią, że naczelnika portu znaleziono martwego w jego własnym domu. Znaleziono przy nim notatki, dowodzące jego udziału w zniknięciu statków. Pomyśleć tylko, co za wstyd dla naszego miasta...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Słyszałeś już? Ktoś wślizgnął się do domu naczelnika portu, zabił straż i wykończył go. Znaleźli na zwłokach notatki z trasami zaginionych statków - napisane przez niego samego! Sługa korony, a w rzeczywistości - zdrajca! Dostał to, na co zasłużył! I gdzie patrzył gubernator przez wszystkie te lata?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Naczelnik portu zabity! Prosto w swoim domu! Straż wybita, a wśród jego rzeczy - notatki z trasami zaginionych statków. Nie ma co myśleć, zniknięcia - to jego sprawka! Cóż, łotra dosięgnął sprawiedliwy los.", "Beliz", 30, 1, "");
		break;
	}
}