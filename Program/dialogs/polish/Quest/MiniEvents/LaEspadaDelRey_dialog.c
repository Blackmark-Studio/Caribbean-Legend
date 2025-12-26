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
			dialog.text = "Czego chcecie?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Hej, chłopcze! Widzę, żeś dzielny marynarz i pewnie też niezły zawadiaka. Nie pomógłbyś mi zrobić wypad do pewnego miejsca, co?";
			}
			else
			{
				dialog.text = "Hej, piękna! Widzę, że nie brak ci odwagi, skoro się tu pojawiłaś. Nie pomogłabyś mi wybrać się na małą wyprawę w jedno miejsce, co?";
			}
			link.l1 = "Zakładam, że to ty jesteś tym starcem, który szuka przewodnika do starego statku?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Heh... Czyli plotki rozchodzą się szybciej niż wiatr. Tak, to ja. Gonzalo Peralta – jedyny, który wciąż żyje z rozbitków 'La Espada del Rey'.";
			link.l1 = "A ja jestem kapitanem "+GetFullName(pchar)+". Chcesz jeszcze raz rzucić okiem na swój statek?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Tak. Wiesz, od jakiegoś czasu dręczy mnie ten sam koszmar. Ale rzecz даже nie w nim... Wierz lub nie, ale każdego ranka, gdy tylko koszmar się kończy, budzę się i... przede mną stoi cholerny szkielet...";
			link.l1 = "W indiańskim stroju. Słyszałem, że wszystkim opowiadasz tę historyjkę.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "Bajka? Heh... Chciałbym, żeby to była tylko bajka. Jeszcze parę miesięcy temu prowadziłem spokojne życie, jak przystało na starego emerytowanego marynarza. Ale teraz ten worek kości pojawia się u mnie każdego ranka, patrzy na mnie, wydaje przeraźliwy krzyk... knypel mi w żagiel, każdemu bosmanowi krew by zamarzła w żyłach... a potem rzuca się do walki. I wiesz co? Z każdym razem atakuje coraz zacieklej. Właśnie dlatego chcę jak najszybciej dotrzeć do statku – nie opuszcza mnie przeczucie, że muszę tam coś odnaleźć.";
			link.l1 = "Hmm... Ciekawe sprawy. I czego chcesz tam szukać po tylu latach?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "Nie wiem, kapitanie, nie wiem... Ale coś mnie ciągnie do tego statku, jak stary barkas w czasie sztormu. Mój sen, ten szkielet i to dziwne uczucie... Przysięgam na morze, one są ze sobą jakoś powiązane. Tylko jak – nie mam pojęcia.";
			link.l1 = "Co dokładnie dzieje się w twoim śnie? Czy to ma jakiś związek z Indianami?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "Więc nocą masz jakieś wizje, a rano walczysz ze szkieletem? Może problem nie w statku, tylko po prostu czas ci do medyka? Nie będę pobłażać twojej rozbuchanej wyobraźni. Poszukaj innego głupca, który uwierzy w twoje brednie.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "Jeszcze jak jestem związany, niech mnie piorun trafi... W tym śnie jestem z poległą załogą  na 'La Espada del Rey'. My... rabujemy wioski Karaibów na Hispanioli, zabijamy wszystkich bez wyjątku – mężczyzn, kobiety, dzieci. Tych, którzy walczą, i nawet tych, którzy padają na kolana, błagając o litość. Wypalamy osady jedna po drugiej. Strzały Indian, ich maczugi przeciwko nam – to jak dziurawa tartana przeciwko okrętowi wojennemu. Karaibowie, w rozpaczy, proszą o rozmowy, i wtedy...";
			link.l1 = "Panie zmiłuj się! Więc brałeś udział w tych bezecnościach? Tobie nie pomoc potrzebna, tylko konopny krawat!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "Nie! Nie, niech mnie diabli wezmą, nie było czegoś takiego, rozumiesz?! Nie mam pojęcia, czemu to wszystko mi się śni... ale przysięgam na wszystkich świętych, ani ja, ani moja załoga nie braliśmy udziału w takich okrucieństwach!";
			link.l1 = "Lepiej dla ciebie, żeby tak właśnie było. Kontynuuj.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "Карибы запросили переговоров, и капитан согласился. Он пригласил всех их в одну из тех хижин, которые 'мы' захватили. Вожди пришли — два десятка человек, не меньше, во главе с их королевой — Анакоаной. Только вот сам капитан внутрь не зашёл... никто из нас не зашёл. Как только вошёл последний из вождей — дверь захлопнули и подпёрли балками. А потом... чёрт побери... подожгли. Пощадили только королеву, но ненадолго. Её заставили смотреть, как её народ сгорает живьём... А потом вздёрнули на дереве.";
			link.l1 = "I to powtarza się każdej nocy? Ten sam sen, wciąż od nowa? Wiesz, nie zdziwiłbym się, gdyby po czymś takim ten szkielet był tylko wytworem twojego szalonego umysłu...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "To jeszcze nie wszystko. Ci, którzy przeżyli, Karaibowie, uciekli na Kubę, gdzie znaleźli wsparcie u miejscowych plemion i wkrótce zebrali się w jedną armię – pod dowództwem jakiegoś wodza. Atuay – chyba tak się nazywał. Szli za nim jak za ostatnią nadzieją. Ale bez trudu wybiliśmy wszystkich. Atuay został pojmany i przygotowany do egzekucji. Gdy przywiązano go do krzyża, szykując się do spalenia, mnich zaproponował mu przyjęcie prawdziwej wiary – powiedział, że to złagodzi jego cierpienia i zapewni mu miejsce w raju. Atuay zapytał mnicha, czy raj jest otwarty dla Hiszpanów. Kiedy tamten odpowiedział, że dla dobrych Hiszpanów oczywiście jest otwarty, kasik bez wahania odparł, że w takim razie nie chce do raju, tylko do piekła – byle nie dzielić schronienia z ludźmi tak okrutnymi. Potem powiedział jeszcze kilka słów w swoim języku i stos został podpalony. Nie wydał z siebie ani dźwięku, gdy płomienie zaczęły trawić jego ciało. Na morze przysięgam, nie chciałbym widzieć czegoś takiego na jawie. Mój sen zawsze kończy się tak samo: kapitan siedzi nieruchomo. Tylko świeca obok kopci, a on wciąż przewraca jakieś podniszczone strony dziennika. Powoli, jakby każde słowo ważyło tonę, i mamrocze coś pod nosem. Nawet we śnie, "+GetSexPhrase("chłopak","dziewczyna")+", rozumiem – to znak. Czas chwycić za klingę, bo on już atakuje\nPomóż mi pozbyć się tego koszmaru, kapitanie. Chodź ze mną do zatoki. Sam tam nie pójdę – prochu w prochownicach już nie starcza. Ale zanim odpowiesz, muszę cię uprzedzić: nie mam czym ci zapłacić, inaczej już ustawiłaby się tu kolejka chętnych do pomocy. Pozostaje więc liczyć na wsparcie naszego brata – marynarza.";
			link.l1 = "No dobrze. Jeśli wyprawa na statek pomoże ci pozbyć się tych snów i innych wizji, pomogę ci. Wchodź na pokład. Gdy tylko skończę swoje sprawy, ruszamy do zatoki.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "Oto on... Kiedyś duma hiszpańskiej floty handlowej, a teraz - kupa zgniłych desek, cudem trzymających się razem.";
				link.l1 = "Rzadko widuje się taki olbrzym powalony – leżący na brzegu.   Jak on się tu znalazł?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "No to rozejrzyjmy się. Może naprawdę uda ci się tu coś znaleźć.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Nie chcę wyjść na niewdzięcznika ani tchórza... ale teraz nie czuję się tu najlepiej. Wróćmy, gdy wzejdzie słońce.";
				link.l1 = "Dobrze, przyjacielu, jak chcesz.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "Wyszliśmy wtedy z Santiago i obraliśmy kurs na Sewillę. Ładunku było niewiele, za to mieliśmy jednego pasażera – ważną osobistość, biskupa we własnej osobie. Załodze, powiem szczerze, taki rejs nie przypadł do gustu... ale kto nas kiedyś słuchał?\nDo oceanu wtedy nie dotarliśmy. Pod Turks zaatakował nas piracki bryg – szybki, zwrotny, uzbrojony po zęby. Nie byle nędzarze, tylko prawdziwe wilki morskie. Kapitan najpierw chciał dać nogę – nie chciał ryzykować życiem biskupa. Ale przy takim wietrze nie dało się zawrócić, a od południa nadciągała już burza. Więc nie było wyboru – zaczęła się walka.";
			link.l1 = "Znaleźć się między młotem a kowadłem to nie jest godny pozazdroszczenia los.   I co było dalej?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "Bitwa nie trwała długo. Zdążyliśmy odstrzelić im fokmaszt, ale piraci też nie pozostali dłużni – zabłąkana kula zerwała sterlinę i, jakby sam diabeł się wtrącił, statek stanął dziobem wprost na nadciągającą burzę. Nadchodziła tak szybko, że piraci – niech im knippel w grocie utkwi – woleli dać nogę, chowając się w jednej z zatok Turks. Nam pozostało tylko jedno – czekać, aż pochłonie nas sztorm. Kapitan rozkazał zwinąć żagle i wymienić sterlinę, ale było już za późno.";
			link.l1 = "Więc sztorm złapał was koło Turks, przeciągnął tutaj i w końcu wyrzucił na brzeg?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "Dokładnie tak właśnie było. Na statku panowało prawdziwe piekło. Wiatr rwał olinowanie, maszty padały jeden po drugim, roztrzaskiwały pokład i miażdżyły ludzi. Kogo nie zdążyło się przywiązać – zmywało za burtę, a kto zdążył – tego przygniatały szczątki. W ładowni wcale nie było lepiej – działa, skrzynie, kule latały tam i z powrotem jak diabły, miażdżąc wszystko na swojej drodze. Kiedy w końcu wyrzuciło nas na brzeg, byłem nieprzytomny. Ocknąłem się już na piasku. Znalazł mnie bosman Sergio. Było z nim jeszcze dwóch.";
			link.l1 = "Niezbyt dużo, jak na tak duży statek.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ech, kapitanie... Ile tam było trupów... Od razu zrozumieliśmy: nie możemy tu zostać. Fale mogłyby zabrać i statek, i nas za nim. W pobliżu znaleźliśmy jaskinię – tam, wyczerpani, zasnęliśmy ledwie dotykając ziemi. Kiedy się obudziłem, w jaskini nie było ani Sergio, ani tamtych dwóch\nPrzeszukałem całą plażę, ale przysięgam na gromy, ich tam nie było. Sam nie byłem w stanie dostać się na statek, więc postanowiłem ruszyć w głąb wyspy. Tak dotarłem do Sharptown, gdzie przez własną naiwność narobiłem kłopotów\nChciałem dowiedzieć się czegokolwiek o ocalałych, więc zacząłem wszystkim opowiadać, co się z nami stało. Ale tych łotrów nie interesowałem ani ja, ani załoga, tylko skarby, które można było zwędzić ze statku. Wieść szybko rozeszła się po całej wyspie i tłumy tych ladronów ruszyły tam.";
			link.l1 = "Więc los tamtych ludzi wciąż jest ci nieznany?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Powrót na statek był zbyt niebezpieczny. Ci, którzy zaryzykowali i poszli tam po łup, mogli nie podzielić się zdobyczą i strzelić do każdego, kto znajdzie się obok… przypadkiem. A może — i wcale nie przypadkiem\nPrzysięgam na morze, przesiedziałem w tawernie cały tydzień, wypytując każdego, kto odwiedził zatokę. Ale nikt nie słyszał ani o moich chłopakach, ani o tym, co się z nimi stało\nW końcu pogodziłem się z myślą: wygląda na to, że jestem jedynym, który przeżył tę przeklętą burzę. Po prostu los był dla mnie łaskawszy niż dla innych. A może... to wszystko dzięki amuletowi, który kiedyś podarował mi młody, wtedy jeszcze kapitan Eugenio de la Torre. Zawsze miałem go przy sobie. I, do diabła, wygląda na to, że naprawdę przynosił szczęście.";
			link.l1 = "I gdzie on teraz jest? Wygląda na to, że przed szkieletami nie chroni, heh...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "Zerwało go z mojej szyi, kiedy obijaliśmy górną część studni na moim podwórku. Kłoda uderzyła mnie w szyję i amulet wpadł do wody. Studnia była już pełna, więc nikt nie zamierzał jej opróżniać dla jednej błahostki.";
			link.l1 = "I od tego momentu zaczęły ci się śnić koszmary?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "Do diabła! Nigdy się nad tym nie zastanawiałem, ale przecież tak właśnie było! Gdy tylko skończyliśmy budować studnię, zaczęły się koszmary.";
			link.l1 = "Zabawny zbieg okoliczności. No cóż, teraz jesteś tutaj, tak jak chciałeś. Co zamierzasz robić dalej?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "Nie wiem, kapitanie... Nie wiem. Najpierw rozejrzyjmy się – mam coraz silniejsze wrażenie, że powinienem tu coś znaleźć.";
			link.l1 = "Dobrze. Mam nadzieję, że nie przyszliśmy tu na próżno.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Posłuchaj... To uczucie tylko się nasila. Jakbym stał o krok od czegoś, co muszę odnaleźć. Muszę dostać się na statek. Przysięgam na morze, tam jest coś, co wyjaśni, dlaczego ten przeklęty szkielet nie daje mi spokoju.";
			link.l1 = "Może więc nie bez powodu tak się tu pchałeś? Schowałeś na statku coś cennego i teraz postanowiłeś wrócić po swój skarb?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "Co za bzdury? Myślisz, że przylazłbym tu przez cały archipelag dla kilku dubloonów po czterdziestu latach? Gdybyś choć raz zobaczył tego szkieleta, nawet by ci to do głowy nie przyszło.";
			link.l1 = "No dobrze, dobrze, nie denerwuj się. I jak zamierzasz dostać się na statek?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "Na rufie jest ukryte drzwi. Kapitan sam je wyciął – na wypadek, gdyby abordaż nie poszedł po naszej myśli. Przysięgam na gromy, sam nie wcisnę tam swojego starego cielska, ale we dwóch...";
			link.l1 = "No dobrze, prowadź, skończmy z tym.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "Kula armatnia w kark, co za rzeźnia! Dobrze, że ci tutaj nie byli tak wściekli jak ten, który nawiedza mnie co rano. No i co, wierzysz mi teraz?";
			link.l1 = "Po takim widowisku trudno *nie* uwierzyć. Wszystko z tobą w porządku?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "Chyba tak. Przeklęte trupy... nogi mi się ugięły jak połamane maszty.";
			link.l1 = "Skoro jesteś cały, to nie ma co tu siedzieć. Podaj rękę, pomogę ci wstać.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "O, tak lepiej. Wygląda na to, że nie jesteśmy pierwsi, którzy wiedzieli, jak się tu dostać.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "Chyba to moi ludzie. Ci, którzy przeżyli sztorm... Poznałem kamizelkę Sergio... a raczej to, co z niej zostało. Czyli wrócili – albo szukać ocalałych, albo pochować poległych. Tylko wygląda na to, że ta sama zaraza ich wykończyła.";
			link.l1 = "Zadziwiające, że z ubrania zachowały się tylko strzępy kamizelki. I nic więcej.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Nie został nawet ślad po sutannie naszego pasażera – biskupa. Sądzę po kluczu zaciśniętym w jego dłoni, że ten nieszczęśnik to właśnie on. Nigdy nie rozstawał się z tym kluczem, ani na chwilę. Wygląda na to, że nie miał więcej szczęścia niż reszta. Na morze – te trupy nie kręciły się tu bez powodu. Coś je tu trzyma... albo czegoś pilnują.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Nie został nawet ślad po sutannie biskupa. Sądzę po kluczu zaciśniętym w jego dłoni, że ten nieszczęśnik to właśnie on. Nigdy nie rozstawał się z tym kluczem, ani na chwilę. Wygląda na to, że nie miał więcej szczęścia niż reszta. Na morze – te trupy nie kręciły się tu bez powodu. Coś je tu trzyma... albo czegoś pilnują.";
			}
			link.l1 = "Też mam wrażenie, że mamy tu coś znaleźć. Załatwmy to szybko — nie mam ochoty siedzieć tu dłużej niż trzeba.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "No i co tam, kapitanie? Udało się coś znaleźć?";
			link.l1 = "Wygląda na to, że to była skrzynia biskupa. Ja nasz"+GetSexPhrase("szedł","ла")+"   jest tam coś. Spójrz.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velasquez... Niech mnie piorun trafi... Widziałem ten dziennik w swoich snach! To właśnie jego przeglądał kapitan, zanim...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "Diabeł, on jakby palił mi dłonie!";
			link.l1 = "Pali ci ręce? Daj spokój, to tylko stary dziennik. Czy naprawdę wierzysz, że kryje się w nim jakaś mroczna siła?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "Przysięgam na wszystkich świętych, nie żartuję! Ten przeklęty dziennik jakby palił mi dłonie. Trzeba go zniszczyć! Podrzeć, spalić, utopić – cokolwiek! Chociaż nie... Lepiej spalić. Tak, właśnie spalić, żeby nie został po nim nawet popiół!";
			link.l1 = "Jak sobie życzysz. W takim razie chodźmy na brzeg, rozpalimy ognisko i wrzucimy tę kronikę występków w ogień.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "No i to już wszystko... Jakby kotwica spadła mi z duszy.";
			link.l1 = "Myślisz, że to już koniec?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Kto wie... Ale przysięgam na morze, dawno już nie oddychałem tak lekko. Jakby stary dług w końcu został spłacony. Tylko jednak... Lepiej by było, gdybym nigdy nie widział tego przeklętego dziennika. I nie wiedział, co w nim napisano.";
			link.l1 = "Nic dziwnego, że ci się to śniło. Chociaż nie brałeś w tym wszystkim udziału, jesteś jedynym z żyjących, kto miał jakikolwiek związek z tym dziennikiem.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Ani złoto, ani wiara nie usprawiedliwiają tego, co ludzie robili pod dowództwem Velasqueza. I cieszę się, że wszystko, co mogło o tym przypominać, spłonęło. Takie rzeczy nie powinny trafiać w ręce tych, którzy mogliby zechcieć brać z nich przykład.";
			link.l1 = "Velázquez to tylko jeden z wielu. Kto wie, ile jeszcze takich dzienników krąży po rękach w starej Europie, podsycając chciwość i bezkarność nowych zdobywców? Jedno cieszy – ten już nikogo nie zatruje. A tak przy okazji, w kufrze biskupa był nie tylko dziennik, ale i niezły zapas dublonów – trzy setki. Połowa z nich słusznie należy do ciebie.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velázquez zapłacił za swoje grzechy, a jeśli ktoś zdecyduje się pójść jego śladem – spotka go ten sam los. Prędzej czy później los odpłaci każdemu według zasług.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "Skoro tak – nie odmówię. Każdemu są potrzebne pieniądze, a mi teraz szczególnie. Już mnie na żaden statek nie wezmą jako marynarza – za stary jestem. Więc dziękuję, kapitanie, że mnie nie odprawiłeś."+GetSexPhrase("ся","ась")+", jak inni.";
			link.l1 = "Przyznam, na początku twoja opowieść wydała mi się brednią szaleńca. Ale mówiłeś o tym tak przekonująco, że czy chcesz, czy nie, zaczynasz w to wierzyć. A jednak pojawienie się tych indiańskich nieumarłych zaskoczyło mnie zupełnie.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Po prostu postanowiłem sprawdzić, czy nie jesteś szalony. Sam rozumiesz, w takie historie trudno uwierzyć.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "Chciałoby się w to wierzyć... Ale przysięgam na morze, widziałem zbyt wielu, którym los się uśmiechał, mimo wszystkich ich czarnych uczynków. Może zapłata ich jeszcze dosięgnie – ale już tam, w diabelskim kotle. A tobie dziękuję, kapitanie. Za to, że nie odwróciłeś się, wysłuchałeś i odprowadziłeś. Wiesz, to naprawdę wiele znaczy.";
			link.l1 = "Przyznam, na początku twoja historia wydała mi się brednią szaleńca. Ale opowiadałeś ją tak przekonująco, że czy chcesz, czy nie, zaczynasz w to wierzyć. A jednak pojawienie się tych indiańskich nieumarłych zaskoczyło mnie całkowicie.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Po prostu postanowiłem sprawdzić, czy nie jesteś szalony. Sam rozumiesz, trudno uwierzyć w takie historie.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Teraz już wiesz, co czułem, gdy po raz pierwszy zobaczyłem tę nieumarłą. Mam nadzieję, że to już koniec na zawsze... Inaczej kolejnego takiego spotkania raczej nie przeżyję.";
			link.l1 = "No dobrze, skoro tu skończyliśmy, czas się stąd zbierać. Wchodź na pokład, wysadzę cię w porcie Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Teraz już wiesz, co czułem, gdy po raz pierwszy zobaczyłem to nieumarłe stworzenie. Mam nadzieję, że to już koniec na zawsze... Inaczej kolejnego takiego spotkania raczej nie przeżyję.";
			link.l1 = "No dobrze, skoro tu skończyliśmy, czas się stąd zabierać. Wchodź na pokład, wysadzę cię w porcie Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Jeszcze raz dziękuję, kapitanie "+GetFullName(pchar)+". Przysięgam na morze, to dziwne uczucie zniknęło i mam nadzieję, że zabrało ze sobą swój przeklęty worek kości. Może wypijemy po kufelku, co?";
			link.l1 = "Dziękuję za zaproszenie, Gonzalo, ale mam jeszcze mnóstwo spraw na głowie. Może innym razem. Wypij za nas obu.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "Rozumiem. Ale powiem ci tak, kapitanie: po wszystkim, co razem przeszliśmy, nie mogę tak po prostu odejść, nie podziękowawszy ci. To nie po ludzku. Proszę, trzymaj. Za młodu nieraz goniłem za skarbami, przysięgam na morze. Teraz jednak zdrowie już nie to, a i kręgosłup zawodzi. Ty za to jesteś młody, doświadczony wilk morski. Poradzisz sobie bez trudu. Powodzenia, "+GetFullName(pchar)+", pomyślnych wiatrów i siedmiu stóp pod kilem.";
				link.l1 = "Dzięki, Gonzalo. Powodzenia i żegnaj.";
				AddMapPart();
			}
			else
			{
				dialog.text = "No cóż, nadszedł czas się pożegnać. Pomyślnych wiatrów i siedmiu stóp pod kilem, kapitanie "+GetFullName(pchar)+"!";
				link.l1 = "Wszystkiego dobrego, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}