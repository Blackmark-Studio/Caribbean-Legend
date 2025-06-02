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
			link.l1 = "Niczego.";
			link.l1.go = "exit";
		break;
		
		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hej, piękna, co powiesz na wytworną ozdobę do twojej damskiej kolekcji? Prawdziwy skarb! Dla ciebie - pełne podziwu spojrzenia, a dla mnie - kilka monet na chleb i łyk rumu.";
			}
			else
			{
				dialog.text = "Hej, kapitanie, co powiesz na wytworny prezent dla twojej damy? Prawdziwy skarb! Dla ciebie - jej ciepła wdzięczność, a dla mnie - kilka monet na chleb i łyk rumu.";
			}
			link.l1 = "Żeby za godzinę przyszli po mnie żołnierze i wtrącili do więzienia za kradzież? Skąd to masz, włóczęgo?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "Wytworny prezent? I skąd niby miałby się taki wziąć u bezdomnego, takiego jak ty?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;
		
		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Kapitanie, ","")+"znalazłem ten piękny wisiorek z kameą, słowo honoru! Niech się zapadnę, jeśli kłamię! Leżał sobie, nikomu niepotrzebny. Nie mogłem przecież zostawić takiego piękna w błocie, prawda?";
			link.l1 = "No dobrze. Pokaż, co tam masz?";
			link.l1.go = "Poorman_3";
			link.l2 = "Któż by uwierzył na słowo takiemu szanownemu panu jak ty? Poszukaj kogoś innego, kto będzie bardziej łatwowierny.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Kapitanie, ","")+"znalazłem ten piękny wisiorek z kameą, słowo honoru! Niech się zapadnę, jeśli kłamię! Leżał sobie, nikomu niepotrzebny. Nie mogłem przecież zostawić takiego piękna w błocie, prawda?";
			link.l1 = "No dobrze. Pokaż, co tam masz?";
			link.l1.go = "Poorman_3";
			link.l2 = "Któż by uwierzył na słowo takiemu szanownemu panu jak ty? Poszukaj kogoś innego, kto będzie bardziej łatwowierny.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Spójrz... niezła rzecz! Znalazłem to na rabatce, przy domu z latarnią, obok karczmy. Ale od dawna nikt tam nie mieszka, więc nie ma komu tego oddać.";
			link.l1 = "Ciekawy drobiazg. I ile chcesz za niego?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Tylko sto peso"+GetSexPhrase(", kapitanie","")+"... to drobnostka dla kogoś takiego jak ty! A dla mnie - cały tydzień bez martwienia się o kawałek chleba. Tylko popatrz, jaka to piękność!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Dobrze, trzymaj swoje sto peso.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Chyba się obejdę. Spróbuj szczęścia u kogoś innego.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Dziękuję, "+GetAddress_Form(NPChar)+"! Teraz szczęście na pewno się do ciebie uśmiechnie! Dobry z ciebie człowiek, od razu to widać.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;

		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "O-o-o, któż to nas odwiedził? Wygląda na to, że nie pomyliłaś drzwi, kochanie... wchodź, wchodź! Rozbieraj się, czuj się jak u siebie.";
				link.l1 = "No, no... Kogo my tu mamy? Czyż to nie ci sami łajdacy, którzy zostawili dla Betsy 'czułe' pogróżki?";
			}
			else
			{
				dialog.text = "A c-c-co to za dziwadło?! Pomyliłeś drzwi, ty kozia głowo? Wynoś się stąd, zanim rozpruję ci brzuch!";
				link.l1 = "No, no... Kogo my tu mamy? Czyż to nie ci sami głupcy, którzy zostawili dla Betsy miły liścik z groźbami?";
			}
			link.l1.go = "Pirate_2";
		//PlaySound("Voice/Spanish/citizen/Pirati v Gorode-12.wav");
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy? A do diabła z tą Betsy! O wiele ciekawsze jest to, co ty tu robisz, słodka... Skoro już weszłaś - nie śpiesz się z wychodzeniem, znajdziemy ci zajęcie...";
			}
			else
			{
				dialog.text = "Co za Betsy, do diabła? Nie kuś losu, głupcze. Póki możesz wyjść o własnych siłach - wychodź. W przeciwnym razie będziemy musieli zbierać cię po kawałkach i wynosić w wiadrze!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;
		
		case "BetsiPrice_1":
			dialog.text = "Pomocy! Pomocy, błagam cię!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;

		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "A oto i ona. Wpadłeś po uszy w kłopoty, przyjacielu, i jeśli nie chcesz, żeby to był twój ostatni błąd, radzę ją uwolnić. Natychmiast.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ha! Słyszałeś, Reggie? On"+GetSexPhrase("","a")+" nam jeszcze grozi. "+GetSexPhrase("Co za zarozumiały ślimak","Co za zarozumiała szmata")+". Ej, chłopaki, pokażmy "+GetSexPhrase("temu zarozumialcowi, jakiego koloru są jego flaki","tej zarozumiałej, co to prawdziwy ból")+"!";
			link.l1 = "Tym gorzej dla was.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "A teraz wypuść dziewczynę. Albo położysz się obok swojego kumpla.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "Przeklęte psy! Myśleliście, że będę milczeć?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "A ty... Wygląda na to, że nie jesteś z nimi. Kim jesteś?";
			link.l1 = "Kapitan "+GetFullName(pchar)+", do usług.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "Czyli jestem ci winna życie?";
			link.l1 = "Wygląda na to. Ale teraz ważniejsze jest co innego - kim są ci ludzie i w co się wpakowałaś?";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "Ci ludzie... Wysłał ich pewien ważny angielski urzędnik. Kiedyś był mi bardzo bliski... a teraz, jak widzisz, pragnie mojej śmierci.";
			link.l1 = "Zaczynam rozumieć twoją historię. Byłaś jego kochanką, ale w pewnym momencie uznałaś, że możesz to wykorzystać na swoją korzyść. Chciałaś go nastraszyć... powiedzieć rodzinie?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Jesteś zaskakująco blisk"+GetSexPhrase("o","a")+" prawdy, "+GetSexPhrase("przystojniaku","ślicznotko")+"... a jednocześnie bardzo daleko od niej. Gdyby tak było, byłabym już martwa. Tak, byłam jego kochanką, ale nigdy nie przyszło mi do głowy urządzać rodzinnych dramatów\nWszystko było znacznie bardziej skomplikowane: pewnego dnia dowiedziałam się, że znalazł sobie nową zabawkę i postanowił pozbyć się mnie, zostawiając z pustymi rękami. Po prostu wyrzucić jak niepotrzebną rzecz. Cóż, nie jestem przyzwyczajona do odchodzenia z niczym\nWzięłam więc to, co naprawdę miało wartość - papiery, które mogły zniszczyć jego życie - i uciekłam do Nowego Świata. A potem zaproponowałam układ: jego sekrety w zamian za moje bezpieczeństwo i sowite odszkodowanie\nDlatego wciąż żyję - potrzebują tych dokumentów. A ja nie spieszyłam się z ujawnieniem, gdzie były ukryte.";
			link.l1 = "Cóż, jesteś nie tylko piękna, ale i diabelnie sprytna. Zagrałaś odważnie, ale bądźmy szczerzy - ta gra już wymknęła się spod twojej kontroli. Może czas pomyśleć o innej opcji, póki jest jeszcze szansa, by spróbować wyjść z gry? Jeśli znaleźli cię tutaj, mało prawdopodobne, że zdołasz ukryć się gdzieś indziej. Prędzej czy później twoje szczęście się skończy.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "Co więc proponujesz? Po prostu oddać mu dokumenty i zostać z pustymi rękami? Po wszystkim, co przeszłam?";
			link.l1 = "Zdajesz sobie sprawę, że dla nich jesteś tylko problemem do usunięcia. Nie zatrzymają się, póki nie dostaną tego, czego chcą. Ale wciąż masz wybór. Daj dokumenty temu głupkowi. Niech przekaże je swojemu panu i zapewni, że zrezygnowałaś ze swoich zamiarów i po prostu chcesz, by to wszystko się skończyło.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Jeśli to moja jedyna szansa... Dobrze, zaryzykuję. Dokumenty zawsze miałam przy sobie. Wszyłam je w gorset, żeby się z nimi nigdy nie rozstawać. Poczekaj chwilę...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Proszę, weź. To wszystkie dokumenty, które miałam. Powiesz tej kreaturze kilka słów na pożegnanie? Potrafisz przecież być przekonując"+GetSexPhrase("y","a")+", prawda?";
			link.l1 = "Myślę, że już zrozumiał najważniejszą lekcję. Teraz musimy tylko upewnić się, że wie, co ma zrobić.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;

		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Słuchaj mnie uważnie, draniu. Oto dokumenty, po które was wysłano. Zanieś je swojemu panu i przekaż: jeśli nadal będzie wysyłał zabójców za Betsy, spotka ich ten sam los, co twoich kumpli. Powiedz mu, że ona odchodzi z jego życia na zawsze - i nie ma już powodu jej ścigać. Niech przyjmie to jako jej dobrowolny krok w stronę pojednania. Mam nadzieję, że okaże się wystarczająco rozsądny, by na tym się wszystko skończyło. Zrozumiałeś wszystko, czy muszę wbić te informacje do twojej głowy?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "Zrozumiałem wszystko, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "W takim razie wynoś się stąd. I nawet nie myśl o ociąganiu się - jeśli zobaczę cię tu ponownie, nie dostaniesz drugiej szansy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;
		
		case "BetsiPrice_8":
			dialog.text = "Cóż, "+GetSexPhrase("mój bohaterze","moja furio")+", chyba zapomniałam ci podziękować... To wszystko przez emocje. Nie codziennie człowiek znajduje się w niewoli, a potem odzyskuje wolność dzięki "+GetSexPhrase("odważnemu wybawcy","odważnej wybawczyni")+". Powiedz, czy to twój zwyczaj - ratowanie dam z opresji, czy po prostu miałam niesamowite szczęście?";
			link.l1 = "Cóż mogę powiedzieć, Betsy, mam słabość do efektownych wejść i "+GetSexPhrase("pięknych dam","różnego rodzaju przygód")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "Mam na imię Miranda. Miranda Bell. Przyjęłam imię Betsy, gdy musiałam zniknąć - nowe życie, nowe imię, sam"+GetSexPhrase("","a")+" rozumiesz. Uciekłam z Europy tak pospiesznie, że zabrałam jedynie kilka monet i parę ozdób\nReszta prawdopodobnie trafiła do tych draniów, którzy mnie ścigali. Teraz zamiast wystawnych przyjęć i drogich strojów - nędzna chatka na uboczu i praca w karczmie. Nigdy nie myślałam, że kiedyś będę podawać rum, zamiast delektować się winem w dobrym towarzystwie...";
			link.l1 = "Nawet mimo tego wszystkiego wyglądasz tak, jakbyś trzymała los w swoich rękach. Być może w tym tkwi twój prawdziwy talent.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Pochlebca. Ale wiesz, pasuje ci to","Schlebiasz mi")+"... Po tym wszystkim czuję się trochę nieswojo. A co, jeśli już czekają na mnie za rogiem? Odprowadź mnie do domu, bądź "+GetSexPhrase("moim wybawcą","moją wybawczynią")+" jeszcze przez chwilę.";
			link.l1 = "Nie jestem z tych, którzy porzucają rozpoczęte sprawy w połowie drogi. A zatem, madame, jestem na pani usługi. Chodźmy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "No i jesteśmy. Wiesz, nawet nie zapytałam, jakim wiatrem zawiało cię do tego domu?";
			link.l1 = "Nie znalazł"+GetSexPhrase("em","am")+" się tam przypadkiem. Karczmarz wydawał się poważnie zmartwiony twoim zniknięciem i poprosił mnie, żebym sprawdził"+GetSexPhrase("","a")+", co się stało. No a czy miał"+GetSexPhrase("em","am")+" wybór, by odmówić? Porzucenie damy w potrzebie to czyn niegodny kapitana.";
			link.l1.go = "BetsiPrice_12";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "​Nie znalazł"+GetSexPhrase("em","am")+" się tam przypadkiem. Ten wisiorek zaprowadził mnie tam. Weź go.​ Karczmarz wydawał się poważnie zmartwiony twoim zniknięciem i poprosił mnie, żebym sprawdził"+GetSexPhrase("","a")+", co się stało. No a czy miał"+GetSexPhrase("em","am")+" wybór, by odmówić? Porzucenie damy w potrzebie to czyn niegodny kapitana.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
		break;

		case "BetsiPrice_12":
			dialog.text = "Ach, to takie szlachetne, kapitanie "+pchar.name+"! Chociaż jestem pewna, że karczmarz bardziej martwił się o swoje zyski niż o mnie. Niestety, nie mogę cię dzisiaj zaprosić do siebie - muszę dojść do siebie. Czas spędzony w piwnicy raczej nie dodał mi urody. Ale jeśli się już nie spotkamy - tego ci nie wybaczę. Wpadnij jutro do karczmy, będę miała dla ciebie... prezent.";
			link.l1 = "Cóż, teraz mam jeszcze jeden powód, żeby tam zajrzeć. Do zobaczenia, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Ach, to takie szlachetne, kapitanie "+pchar.name+"! Chociaż jestem pewna, że karczmarz bardziej martwił się o swoje zyski niż o mnie. Niestety, nie mogę cię dzisiaj zaprosić do siebie - muszę dojść do siebie. Czas spędzony w piwnicy raczej nie dodał mi urody. Ale jeśli się już nie spotkamy - tego ci nie wybaczę. Wpadnij jutro do karczmy, będę miała dla ciebie... prezent.";
			link.l1 = "Cóż, teraz mam jeszcze jeden powód, żeby tam zajrzeć. Do zobaczenia, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "No proszę... Co za czułe pożegnanie. Kim jest ta potargana dama? Wygląda, jakby przez tydzień siedziała w piwnicy, ale nawet to nie powstrzymało cię od pożerania jej wzrokiem, prawda, "+pchar.name+"?";
			link.l1 = "To nie jest tak, jak myślisz. Dziewczyna znalazła się w trudnej sytuacji, a ja pomogłem jej się z niej wydostać. To wszystko.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "I ty, oczywiście, postanowiłeś zostać jej rycerzem w lśniącej zbroi?";
			link.l1 = "Wiesz, że nie potrafię stać z boku, gdy ktoś jest w niebezpieczeństwie.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Dobrze. Ale następnym razem, "+pchar.name+", bądź ostrożniejszy... i nie dawaj mi powodów do zazdrości.";
			link.l1 = "Oczywiście, kochanie. Chodźmy stąd, mamy jeszcze wiele do zrobienia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "TBP_Mary_1":
			dialog.text = "No proszę... Co za czułe pożegnanie. Taka troska, takie czułe obietnice... Nawet zwracasz się do niej po imieniu z takim uczuciem, tak, co nie? Może też powinnam zniknąć na kilka dni, żebyś szukał mnie z takim samym zapałem?";
			link.l1 = "Mary, wiesz, że jesteś moim drogowskazem, a ona... to tylko dziewczyna, która wpadła w kłopoty.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Ach, no oczywiście! Po prostu biedactwo, które potrzebuje rycerza! A to twoje spojrzenie - też tylko z uprzejmości? Prawie rozebrałeś ją wzrokiem!";
			link.l1 = "Mary, przesadzasz! Popatrz, jak na ciebie patrzę? Widzisz różnicę? Czy będę musiał ci przypomnieć... z bliska?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Dobrze, "+pchar.name+", tym razem się wywinąłeś, tak, co nie?. Ale jeśli jeszcze raz zobaczę taką scenę...";
			link.l1 = "To będę musiał jeszcze raz przypomnieć ci, kto w moim sercu zajmuje pierwsze i jedyne miejsce. Chodźmy, kochanie, mamy jeszcze wiele do zrobienia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... Nie masz pojęcia, jakie myśli krążą mi po głowie, gdy jestem tak blisko ciebie... I jak bardzo pragnę je urzeczywistnić.";
					link.l1 = "To przestań tylko o nich myśleć... i pokaż mi każdą z nich.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ach, mój"+GetSexPhrase(" drogi","a droga")+"... Nie wiesz, jak trudno mi się opanować, gdy jesteś w pobliżu...";
					link.l1 = "Wystarczy już tej słodkiej tortury... Chodź do mnie...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Ach, "+GetSexPhrase("mój słodki kapitanie","moja słodka "+pchar.name)+"... Wciąż jestem w tym słodkim szaleństwie.";
					link.l1 = "To chyba szaleństwo warte zapamiętania... a może nawet kiedyś powtórzenia.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Och, "+pchar.name+"... Jeśli powiem, że to było niesamowite, nie staniesz się zbyt pewn"+GetSexPhrase("y","a")+" siebie?";
					link.l1 = "Tylko jeśli obiecasz, że powiesz to jeszcze raz... szeptem.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}