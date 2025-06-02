// диалоги персонажей по квесту Дороже золота
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
			dialog.text = "Czego chcesz?";
			link.l1 = "Powinienem iść...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Kapitanie Charles de Maure! Wreszcie! Jego Ekscelencja Jacques Dille do Parkuet żąda, żeby cię zobaczyć! To pilne!";
			link.l1 = "Dlaczego nie jestem zaskoczony? Dobrze, proszę przekaż Jego Ekscelencji, że wkrótce przybędę.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "Moje oczy muszą mnie mylić, jeśli to sam Charles de Maure! Nieczęsto mam takie przyjęcia i jestem zachwycony, że udało ci się znaleźć trochę czasu, by odwiedzić mój skromny zaułek. Szczęściarz ze mnie! To zasługuje na toast!";
			link.l1 = "Moje uszanowanie, pani. Proszę wybaczyć możliwe rozczarowanie moimi manierami - minęło bardzo dużo czasu, odkąd ostatnio brałem udział w takich... wydarzeniach. Etos statku sprowadza się do podporządkowania, czystych chust i regularnej filiżanki orzeźwiającej kawy każdego ranka.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "Tak uroczy, Kapitanie, wciąż masz ze sobą paryski blask. Widzę jego nieśmiałe spojrzenie pod tą doświadczoną i zasoloną maską. Nie martw się, cieszę się, że wreszcie cię spotykam, że mogę ci wiele wybaczyć. Na razie. Zobaczymy, jak nam się dalej ułoży. Wino? Czerwone czy białe?";
			link.l1 = "Doskonały moment na żart o rumie, ale niestety, nie mam nastroju, przepraszam. Z przyjemnością wypiję wszystko, co naleją twoje piękne ręce.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Pięknie. Ale nalegam. Gust wina może wiele powiedzieć o człowieku, a ja zamierzam dowiedzieć się o tobie wszystkiego tej nocy. Więc pytam ponownie: czerwone czy białe?";
			link.l1 = "Miej to na swój sposób. Widzę, że pijesz czerwone. Dla mnie to samo - chciałbym się czegoś o tobie dowiedzieć.";
			link.l1.go = "Julianna_3";
			link.l2 = "W takim razie, wezmę białe, ale ty wybierasz. To powinno działać w obie strony, nie sądzisz?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Znakomicie, więc teraz moja kolej? To jest Pinot Noir z Burgundii, winiarze nazywają go 'niegrzeczną dziewczynką'. To niełatwa odmiana do opanowania, a jej posmak również może być dość zwodniczy. Zadowolony?";
			link.l1 = "Pinot Noir, co? Pasuje mi. Niezawodne i tajemnicze, początkowo ponury smak, ale pozwól mu pooddychać chwilę, a będziesz zaskoczony. Lekkie tańczenie odcieni i smaków, wybór doświadczonego konesera. Pierwsze wrażenia mylą, prawda? Piję za twoje oczy, pani!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Znakomicie, więc teraz moja kolej? Mam wspaniałe Sauvignon Blanc, prosto z doliny Loary. Całkiem dzikie, prawie można poczuć, jak musuje na języku. A wisienka na torcie - nuta prochu strzelniczego. Przypuszczam, że macie coś wspólnego.";
			link.l1 = "Spodziewałem się czegoś lepszego, może czegoś jak Riesling. Cóż, napijmy się tego prostego brutala pachnącego latem i prochem. Słyszałeś kiedyś, że niektórzy mylą to z pipi de chat? Wypiję za twój uśmiech, jasny jak te szafiry!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Zdumiewające, Charles! Mogę tak cię nazywać? Nie myliłem się co do ciebie, w inny dzień byłbyś gwiazdą mojej nocy. Ale niestety, mój Kapitanie, dzisiaj masz silną konkurencję. Wygląda na to, że tam jesteśmy na krawędzi skandalu, widzisz?";
			link.l1 = "Słyszę gniewne głosy. Kim jest ten nieprzyjemny monsieur i co takiego zrobił, by nie zadowolić naszego najdroższego gubernatora?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "Ten 'nieprzyjemny' monsieur to Angerran de Chievous, nieuznawany bękart hrabiego de Levi Vantadur. Zajmujesz się ich tematem sporu. De Chievous próbował zyskać moje względy od lat i podążył za mną tutaj, myśląc, że może zastąpić swojego ojca dla mnie. Mimo że nie jest prawowitym synem, jest bogaty i wpływowy. Upór to kolejna z jego cech, dla niektórych ludzi zastępuje mądrość. Tuż przed twoim przybyciem on i Jacques zaczęli się sprzeczać o oczywisty temat. Jego Ekscelencja zawsze chroni mnie w bardzo wzruszający sposób, powinieneś to zobaczyć! Chodź, obserwujmy i zobaczmy, jak to się tym razem skończy.";
			link.l1 = "Czuję kłopoty w powietrzu... Dlaczego zawsze musi być jakiś haczyk, nawet w tak cudowną noc...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Proszę wybaczyć, Charles?";
			link.l1 = "Nieważne. Przedstaw mnie, proszę, swojemu natarczywemu przyjacielowi, a potem zobaczymy...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Panie, pozwólcie, że przedstawię wam mojego drogiego gościa - Kapitana Charlesa de Maure, we własnej osobie, zaszczycił nas swoją wizytą! Takie sławne postacie rzadko goszczą tutaj.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles, nie podoba mi się, dokąd to zmierza! Jacques jest głuchy na moje argumenty, a Angerran na pewno coś knuje. Ta walka miała cel i potrzebuję twojej pomocy!";
			link.l1 = "Obawiam się, że cię nie rozumiem... Co mogę tu zrobić? Już odmówił pojedynku ze mną...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Kapitanie, proszę, nie zawiedź mnie. Przed chwilą byłeś wirtuozem rozmów, a teraz twój świat dzieli się na rzeczy, które można dźgnąć mieczem i te, których nie można. Myśl nieszablonowo! Zepsujmy przedstawienie Angerrana. Chce wyzwać biednego Jacques'a na pojedynek, ale to jest po prostu nudne! Zorganizujmy turniej! Kilku dżentelmenów tutaj może postawić poważne stawki, a twoje szczęście już jest znane jako legendarne! Może karty będą mu dziś sprzyjać?";
			link.l1 = "Nie bardzo widzę, jak to powstrzyma de Chievousa przed walką z naszym kochanym gubernatorem, ale wchodzę, milady. Cokolwiek, by zmazać ten jego mały uśmieszek.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Wyśmienicie, teraz idź do stołu i zjedz coś, noc będzie długa. Gdy będziesz gotowy, spotkaj mnie w sali, potrzebujemy więcej miejsca na to. W międzyczasie rzucę przedstawienie, przekonując innych, by dali mi widowiska i gry o wysokie stawki. Mogę nawet na nich nakrzyczeć, aby te koguty zauważyły damę tonącą w znudzeniu. Proszę, nie wtrącaj się, nikt nie może wiedzieć, że jesteśmy w tej samej drużynie tej nocy. Do zobaczenia później, mój Kapitanie!";
			link.l1 = "Cokolwiek powiesz, madame, cokolwiek powiesz...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Gratuluj mi, udało się! Trochę dumy, trochę uprzedzeń i voila! Zrób znudzoną minę, obserwują nas. Niech myślą, że interesuje cię picie, a nie ja\nTurniej zaraz się zacznie, stawki są wysokie, nie ma drugiej szansy ani rewanżów. Jakoś wiem, że jesteś do tego przyzwyczajony. Poradzisz sobie. Pamiętaj, Angerran na pewno coś knuje, zamierza działać przeciwko naszemu przyjacielowi Jacquesowi, ale nie przewidział twojego przybycia. Bądź moim asem w rękawie, bo widok jego pewnej siebie pyszałkowatej twarzy nigdy nie wróży nic dobrego. Mamy ośmiu graczy, ale zadbałem, żebyś nie zmierzył się z nim aż do finału\nO! Twój pierwszy przeciwnik! Pułkownik i Komendant naszego fortu. Morze kontra ląd - godne wyzwanie dla gości z doświadczeniem wojskowym! Brawa!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Spisałeś się świetnie, Charles, po prostu wspaniale. Angerran i Jacques zaraz staną naprzeciw siebie. Szkoda, że nie posłuchali i nie przełożyli turnieju na tydzień. Mógłabym zebrać prawdziwie gwiazdorską ekipę, której plotki dotarłyby do Paryża! Cóż, może następnym razem. Wygląda na to, że twój następny przeciwnik jest godnym konkurentem dla twego szczęścia, prawdziwym wilkiem morskim, kapitan Moreno! Kapitanowie, proszę!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Niestety, szczęście cię opuściło, Kapitanie. Przykro mi, ale gra dla ciebie się skończyła. Angerran już gra przeciwko Jacquesowi, więc powinnam iść. Żegnaj.";
				link.l1 = "To była przyjemność... pani.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Gratuluję ci zasłużonego zwycięstwa, kapitanie! Nadal nie jest jasne, kto zmierzy się z tobą w finale... Przejdźmy na bok. Ścisz głos i spójrz na tamten stół. Patrz, oto on! Zaczynam rozumieć, co Angerran knuje! Już ogołocił słodkiego Jacques'a z pieniędzy, ale nie pozwala mu opuścić stołu. Gdy przechodziłam obok, biedny dureń grał na jakieś dokumenty o cały statek z ładunkiem. Niestety, szczęście nie jest dziś po jego stronie. Albo ktoś jej powiedział, by nie było.";
				link.l1 = "Myślisz, że de Chievous oszukuje?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Niestety, szczęście Cię opuściło, kapitanie. Przykro mi, ale gra już jest dla ciebie skończona. Angerran już gra przeciwko Jacquesowi, więc muszę iść. Żegnaj.";
				link.l1 = "To była przyjemność... madam.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Z pewnością mógłby, gdyby chciał, ale nie mam dowodów. Nasz drogi gubernator jest dobry w karty, ale jego przeciwnik też. Angerran nawet nie mrugnął, gdy postawił swoją fregatę, wyobraź sobie to. Gdybyśmy mieli ten pojedynek w Paryżu lub w Lionie, stałby się legendą, Charles! Niemniej jednak może mieć po prostu szczęście tej nocy. Podejdźmy do nich i przekonajmy się sami.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, trzymaj mnie albo upadnę... A może nie - ci idioci nawet nie zauważą, że mdleję. Widziałeś to? Jacques, niech cię szlag trafi za twoją głupotę! Jak dziecko, Jezus Maria! Imbecylne dziecko!";
			link.l1 = "Markizo, nie sądzę, bym za tobą nadążał.  Co się dzieje przy tym stole teraz? O co oni grają?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Na mnie, Charles. Nasz słodki, głupi Jacques postawił na mnie. Angerran znalazł jego jedyną słabość i uderzył w odpowiednim momencie.";
			link.l1 = "A niech to! Ależ jestem następny w turnieju, mógłbym wygrać z powrotem jego przeklęty statek! Dlaczego?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Bo Angerran dobrze to przemyślał i wszystko zaplanował. Słuchaj mnie, nie mamy dużo czasu. Musisz zrobić to samo z nim. Odbierz mu wszystko, zabierz wszystkie jego pieniądze, wszystkie jego statki, sprowokuj go! Spraw, żeby stracił głowę na reputacji, honorze, pasji, na czymkolwiek! Widziałeś, jak to się robiło tej nocy. Zepchnij go w róg i zmusz go do postawienia stawki\nBłagam cię, Charles! Jestem gotów na wszystko, ale do niego nie pójdę. Nie w ten sposób! Nawet hrabia Vantadur nie stanie przeciwko uczciwej wygranej w karty, nawet nie kiwnie palcem, żeby mi pomóc. Widzisz, karty są cholernie święte dla szlachetnych ludzi, niech ich diabli wezmą! Jesteś moją ostatnią i jedyną nadzieją, Charles!";
			link.l1 = "Jeszcze nie grzebmy naszego gubernatora, madam. Może odzyska swój statek? Pani Fortuna to kapryśna... kobieta.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Jeszcze nie rozumiesz, prawda? Szczęście nie ma miejsca przy tym stole! Angerran de Chievous wszystkim rządzi. Odkrył sposób, by zarówno mnie mieć, jak i trzymać swojego ojca z dala od tego. Nie mam pojęcia, jak długo to planował, ale już prawie wygrał. On rządzi grą, a my mamy tylko jedną szansę, by ją przerwać. Tutaj, weź to! Zamierzam zemdleć, dam ci minutę lub dwie. Wykorzystaj je mądrze.";
			link.l1 = "Markizo... Ktoś, proszę, pomóżcie! Pani źle się czuje! Szybko!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "Nie, nie, wszystko w porządku... Trochę tu duszno... Bardzo przepraszam, panowie. Zostawię was na chwilę, żeby zaczerpnąć świeżego powietrza. Możecie kontynuować beze mnie.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Nie w tej chwili i nie w St. Pierre, ale znam kogoś. Obiecuję ci, Angerran, to będzie warte malowidło...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, jesteś niemożliwy! Naucz się przegrywać! To tylko gra i nie możesz przewidzieć wszystkiego. Wypij swoje wino i ubierz się - zasady pozostają - pokonany opuszcza nasze wygodne przyjęcie.";
			link.l1 = "Markizo, poczekaj...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "To już za daleko, panowie! Przestańcie natychmiast! Wszyscy jesteśmy bardzo zmęczeni po wyczerpującej nocy i obawiam się, że muszę poprosić moich gości o pożegnanie. Możecie kontynuować wasz spór jutro, jak przystało na ludzi honoru, chyba że zmienicie zdanie. Ale nikt tu nie sięga po broń, czy to jasne?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, obawiam się, że będę musiał również prosić cię o opuszczenie nas. Idź na górę i weź pokój dla siebie. Wszystko załatwię. Jestem nieskończenie wdzięczna za wszystko, co dla mnie zrobiłeś, ale potrzebuję trochę czasu dla siebie, a ty musisz być strasznie zmęczony.";
			link.l1 = "Nie jest tak źle, madame, ale nie odmówię łóżka. Ta luźna biesiada uderzyła mnie mocniej niż potężna wroga eskadra morska. Rozumiem, że i dla ciebie to wszystko nie było łatwe, markizo. Odpocznij i nie martw się, niczego mi nie jesteś winna. Wszystko, czego teraz potrzebuję, to sen.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Upewnię się, że obudzą cię w południe. Już świta, więc nie mogę już życzyć ci dobrej nocy. Śpij dobrze.";
			link.l1 = "Ty również, markizo.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "Tam jesteś, Charles. Szczerze mówiąc, wcale nie spałam, ale wyglądasz na wypoczętego. Jak ci się spało? Śniadanie jest w drodze.";
			link.l1 = "Twoja gościnność jest legendarna, madame, ale obawiam się, że nie mam czasu, by się nią cieszyć. Jego Ekscelencja, sekundanci de Chievousa, statki, które zdobyłem - wszystko to czeka na mnie.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Zdobyłeś nie tylko statki. To kolejna rzecz, o którą chciałam cię zapytać, Charles...";
			link.l1 = "Nie jestem ani Jacques, ani Angerran, markizo. Nie hazarduję się o kobiety, by zdobyć ich przychylność. Nic mi nie jesteś winna.";
			link.l1.go = "Julianna_41";
			link.l2 = "Jesteś pod moją ochroną, markizo. Ani Jacques, ani Angerran nigdy cię nie zaniepokoją, mogę ci to obiecać.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "Jesteś albo niesamowicie honorowy, albo zakochany, Charles. I to nie we mnie. Ale znowu, jestem ci wiecznie wdzięczna z całego serca. Jeśli mogę ci w czymś pomóc - po prostu powiedz mi.";
			link.l1 = "Julianne, czas ucieka, a przede mną stoi najtrudniejsze zadanie. De Chievous to kanalia i nawet uczciwy pojedynek może szybko skończyć się jak ten, który obserwowaliśmy zeszłej nocy. Porozmawiamy później, gdy wszystko to się zakończy. Dziękuję ci za możliwość spania w ciszy i nie mogę się doczekać, by cię znów zobaczyć.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Jestem ci wdzięczna z całego serca, Charles... Uwierz mi, bycie twoją zdobyczą to dla mnie także pewnego rodzaju zwycięstwo. Powiedz, że powinniśmy kontynuować tę rozmowę w bardziej... prywatnym otoczeniu?";
			link.l1 = "Julianne, czas ucieka, a przede mną najtrudniejsze zadanie. De Chievous to łajdak i nawet uczciwy pojedynek może szybko skończyć się jak ten, który obserwowaliśmy zeszłej nocy. Porozmawiamy później, gdy wszystko to zostanie zakończone na dobre. Dziękuję ci za możliwość przespania się w ciszy i nie mogę się doczekać, by znów cię zobaczyć.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "Nie będę cię dłużej zatrzymywał, kapitanie. Pamiętaj jednak, Angerran jest niebezpieczny. Nie mogę ocenić jego umiejętności bojowych, ale brał udział w kilku wojnach i walczył pod Rocroi. Słyszałam też o kilku pojedynkach, które wygrał, głównie na pistolety. Przede wszystkim jest to podstępny typ, jak sam zauważyłeś. Błagam cię, bądź ostrożny i proszę, odwiedź mnie później!";
			link.l1 = "Opieka niesamowicie Ci pasuje, markizo. Uwierz mi, de Chievous nie jest pierwszym bękartem, który stoi mi na drodze. Poradzę sobie. Teraz naprawdę muszę iść do Jego Ekscelencji i omówić sprawę pojedynku.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Z Bogiem, Kapitanie! I powiedz Jacquesowi, żeby trzymał się jak najdalej od drzwi mojego domu.";
			link.l1 = "Masz moje słowo. Do zobaczenia, markizo!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Kapitanie, udało się, co za ulga! Jak poszło? Czy krwawisz?!";
			link.l1 = "To nie jest moja krew... przynajmniej nie cała. Markizo, gdzie jest de Chievous?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "Miałem ci zadać to samo pytanie - nie położyłeś go? Co się stało? Dlaczego widzę połowę straży miejskiej na zewnątrz?";
			link.l1 = "Powiedziałem gubernatorowi, że możesz być w niebezpieczeństwie. De Chievous został ranny i uciekł, spuścił na nas swoich zbirów. To była masakra. Jednak takie opowieści nie są dla twoich pięknych uszu. To już koniec. Jesteś wolna od niego i od naszego 'słodkiego' Jacques'a.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "To takie złe, Charles. Wrogowie tacy jak Angerran de Chievous powinni być zabici na dobre, gdy masz okazję. Znałam tego człowieka przez wiele lat - nie jest typem, który wybacza. Prędzej czy później znajdzie sposób na zemstę. Ale nie podoba mi się, jak się garbisz, czy twoja rana została opatrzona?";
			link.l1 = "To tylko zadrapanie, bywało znacznie gorzej. Trochę boli, to wszystko. Dziękuję za troskę, pani, ale powinienem iść...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Kapitanie, postawiłeś na mnie w grze, ryzykując swoje statki i majątek, walczyłeś o mnie w umowie, ryzykując życie i karierę. Najmniej, co mogę dla ciebie zrobić, to zatroszczyć się o twoje rany i dać ci miejsce do bezpiecznego odpoczynku. Nie! Nie chcę już o tym słyszeć. Weź moją rękę i chodź za mną na górę. Twój pokój na ciebie czeka.";
			link.l1 = "Przyjmuję twoją propozycję, pani, dziękuję. Ale wolałbym cię nie obciążać. Sam dotrę na górę.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Markizo, jesteś moim aniołem stróżem. Obawiam się, że teraz to ja jestem ci dłużny.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, jesteś przykładem rycerskości! Przysięgam na Boga, jeśli tak dalej będziesz postępować, stracę głowę! Dobrze, mój rycerzu, wyślę ci Denise, ona zajmie się twoimi ranami jak przystało na porządnego medyka.";
			link.l1 = "Dziękuję, markizo. Gdyby moje serce nie było już zajęte, chętnie bym się przyłączył. Ale niestety! Dobranoc!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "W tym przypadku żądam, abyś spełnił moje żądanie natychmiast. Chwyć moją dłoń i rób, co mówię. Denise! Przynieś len, gorące wino i coś do jedzenia na górę! Ruszajmy, mój Kapitanie. I pamiętaj - tym razem bez sprzeciwów!";
			link.l1 = "Jak sobie życzysz, markizo, jestem cały twój.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Dzień dobry, Charles. Jak się mają te twoje 'zadrapania'?";
				link.l1 = "Dzięki twym wysiłkom czuję się odrodzony. Przyjmij, proszę, moje szczere podziękowania, Julianno.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Dzień dobry, mój bohaterze. Jak się mają te twoje 'drobne zadrapania'?";
				link.l1 = "Dziękuję za troskę, pani, jestem całkowicie w porządku. Zapłaciłbym fortunę, by wasza Denise służyła jako lekarz na moim statku. Jest cudem!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Obawiam się, że nie będzie łatwo to załatwić. Ale nigdy nie odważyłabym się cię obudzić bez poważnego powodu. Uwierz mi, strzegłam twego snu bez lęku, ale ten człowiek na dole jest bardzo uparty. Twierdzi, że jest jednym z twojej załogi i to jest pilne.";
			link.l1 = "Mój członek załogi? Zrobiłaś dobrze, że mnie obudziłaś, markizo! Zaraz wyruszam.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "W innych okolicznościach bym to zrobiła, mój kapitanie, ale będziemy musieli to odłożyć. Czeka na ciebie na dole wyjątkowo niewykształcony monsieur. Twierdzi, że jest jednym z twojej załogi i to jest pilne.";
			link.l1 = "Wracamy do tego, Madame, kiedy wrócę. Mam nadzieję, że to nie chodzi o to, że Hiszpanie znów oblegają.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, wróciłeś! Jakie wieści przyniósł twój człowiek? Nawet nie pożegnałeś się!";
			link.l1 = "Przepraszam, markizo. De Chievous znów zagrał nieczysto. Ukradł mój statek i odpłynął tej nocy. Jeden z moich zaufanych oficerów był na tym statku i nie mogę zostawić jej w rękach tego drania.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "Ją? Masz kobietę oficer na swoim statku? To sprzeczne ze wszystkim, co wiem o żegludze. Co sprawia, że myślisz, że ona jeszcze żyje?";
			link.l1 = "Mam nadzieję. Julianna, nadzieja to wszystko, co mam do tej pory. Muszę dowiedzieć się więcej o Angerran de Chievous. Absolutnie muszę się dowiedzieć, dokąd poszedł! Muszę ją sprowadzić z powrotem!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Teraz widzę! Jesteś rzeczywiście zakochany, mój rycerzu! Chętnie oddałabym połowę mojego życia za taką lojalność i przywiązanie bez chwili zastanowienia!";
			link.l1 = "Nie składałem żadnych ślubów, ale ta kobieta wiele dla mnie znaczy, marquise.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "To zazdrość dotykająca. Posłuchaj tego, Charles, jestem gotowa być o ciebie zazdrosna! Ale która kurtyzana może pozostać głucha na głos prawdziwej miłości? Poza tym, uratowałeś mnie, mój rycerzu, oczywiście, że ci pomogę. Pytaj śmiało.";
			link.l1 = "Dziękuję. Znasz de Chievousa od jakiegoś czasu. Dokąd mógłby się udać po całym tym zamieszaniu, aby przeczekać gniew ojca?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "A co, jeśli mogę cię uwieść śniadaniem? Nie myślałeś o tej... dziewczynie przez dwa dni, może warto poczekać jeszcze jeden dzień?";
			link.l1 = "Markizo, zdaję sobie sprawę, jak mogę wyglądać w twoich oczach, ale to, co się stało, nie da się cofnąć. Choć nie złożyłem żadnych ślubów, moje serce należy do niej. Błagam cię, zrozum mnie i pomóż mi.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Chodź, Charles! Bronić się rozmowami o miłości przed kurtyzaną? Dawno się tak nie śmiałam! Jesteś niesamowity! Spokojnie, co się wydarzyło w tym domu, zostaje w tym domu. Pamiętam, co ci jestem winien. Pytaj śmiało.";
			link.l1 = "Dziękuję. Znasz de Chievousa od dłuższego czasu. Dokąd mógł się udać po całym tym zamieszaniu, aby przeczekać gniew ojca?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "Prawda jest taka, że choć zaproszenie Angerrana de Chievousa może nie być najprzyjemniejszą rzeczą do zrobienia, to jednak jest to bardzo politycznie użyteczne. Jest on mile widzianym gościem wszędzie, w tym w narodach sprzymierzonych z Francją. Ale znam tylko jednego człowieka w pobliżu, który zawsze poda mu rękę i schronienie. Francois de Lyon, gubernator naszej kolonii na Gwadelupie. Jest starym współpracownikiem hrabiego de Levi Vantadur i zawsze miał słabość do tego łajdaka.";
			link.l1 = "Guadeloupe to jest! To najlepsza wskazówka, na jaką mogłem się odważyć! Jeśli wyruszymy w rejs dziś wieczorem, będziemy tylko dzień za nimi.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Poczekaj, Charles, jest jeszcze coś. Niedawno otrzymałam dla ciebie list. Przypuszczałem, że ma coś wspólnego z pojedynkiem, ale już nie jestem tego taka pewna. Oto on.";
			link.l1 = "„Nie ma pieczęci, ale papier jest drogi. Nie podoba mi się to...”";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Chodź, Charles! Nie trzymaj mnie w niepewności, czy to od niego?";
			link.l1 = "Tak, to od niego. Ona żyje! Złapał ją, gdy kradł mój statek. Teraz sugeruje, byśmy się spotkali i omówili to w cywilizowanym otoczeniu. Tak jak mówiłeś, Guadeloupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monsieur de Lyons z pewnością wybierze syna Leve Vantadura zamiast ciebie. De Chievous może znowu zastawić na ciebie pułapkę! Zyskałeś bardzo potężnego wroga, broniąc mnie, Charles. Chciałabym ci pomóc, ale obawiam się, że wszystko, co mogę zrobić, to prosić cię o ostrożność.";
			link.l1 = "Julianne, nigdy bym sobie nie poradził w Nowym Świecie, gdybym zawsze wybierał bezpośrednie podejście. Ciemne interesy nie są moją najmocniejszą stroną, ale wiem, jak grać w tę grę.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Wiadomości, kapitanie?";
			link.l1 = "Niestety, nic...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Witaj z powrotem, Charles! Cieszę się, że żyjesz i masz się dobrze. Jakie wieści?";
			link.l1 = "Wszystko, co wiedzieliśmy o zdolnościach de Chievousa, okazało się być poważnym niedopowiedzeniem. Drań trzyma mojego... oficera jako zakładnika, a ja mam tylko dwa tygodnie na zebranie okupu. Obawiam się, że nie obejdzie się bez twojej pomocy.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, twa miłość jest niczym wiatrówka, jednakże jestem ci wiele winien i pomogę, jak tylko zdołam. Jak mogę ci służyć?";
			}
			else
			{
				dialog.text = "Charles, już ci mówiłam, że nigdy nie zapomnę, co dla mnie zrobiłeś. Zrobię, co w mojej mocy, by ci się odwdzięczyć. Jestem gotów, choć nie do końca rozumiem, jak mogę ci się przydać w tej kwestii?";
			}
			link.l1 = "Proszę, usiądź, Julianno. Widzisz, okup za Angerrana... to ty. I nie mam na myśli oficjalnego patronatu, mam na myśli więźnia związanego w ładowni jego statku.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Brak mi słów... Ale twoja twarz mówi mi, że to nie żart. Czy on stracił rozum?";
			link.l1 = "Bardziej, jakby wierzył, że to zrobiłem. Jest na tyle zdesperowany, by przekroczyć wszelkie możliwe granice.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "I co, pytasz mnie? Żebym nie krzyczała podczas mojego porwania? Kapitanie, czy nie sądzisz, że to trochę za dużo, by o to prosić? Jestem ci wiele winna, ale ratowanie czyjejś miłości oddając własne życie w ręce niechlubnego drania... Ty jesteś rycerzem, a ja jestem skrajnie realistyczną i materialistyczną kobietą.";
			link.l1 = "Obawiam się, madame, że dokładnie o to cię proszę. Spakuj swoje rzeczy, wyjeżdżamy. Bardzo mi przykro z tego powodu, lecz czas nagli.";
			link.l1.go = "Julianna_76";
			link.l2 = "Markizo, nie porywam kobiet, które pokładają we mnie zaufanie. A to może być nasza szansa.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Jesteś pełen niespodzianek, Charles. Słyszałeś to? To była cała łaska, jaką miałem dla ciebie, właśnie się roztrzaskała. Miłość czy nie, nie pozwolę ci mnie porwać. Straż! Pomocy!!! Ktokolwiek!!!!";
			link.l1 = "A ja myślałem, że jesteśmy przyjaciółmi.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "To jest skandal! W co zamieniłeś mój salon?! Co to za demoniczny koszmar? Charles, wróć do swoich zmysłów! Jesteś szlachcicem, nie przeklętym piratem!!";
			link.l1 = "Już cię przeprosiłem. Prosiłem, abyś nie komplikowała spraw bardziej - nie posłuchałaś. Uwierz mi, nie podoba mi się to, co robię, ale nie mam wyboru. Zrobię wszystko, co trzeba, dla dobra tej kobiety.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "Jakaż to dama wybrałaby takiego kawalera jak ty? Pójdę sama, trzymaj swoje ręce z dala ode mnie! Nie kradniesz przecież krowy, więc pokaż odrobinę godności!";
			link.l1 = "Dobrze. Chodź ze mną, pani. Trzymaj się za moimi plecami i schyl głowę - może zaczną strzelać.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Przez chwilę myślałem, że w ogóle cię nie znam, Charles. To spojrzenie... Ale co zamierzasz teraz zrobić? Jaką szansę wspomniałeś?";
			link.l1 = " Dlaczego drań używa mnie, aby dotrzeć do ciebie? Dlaczego zaaranżował tę grę w karty zamiast po prostu wziąć to, czego chciał? Czego się boi?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Niestety, ale przyczyny tego wszystkiego są nudne i prymitywne. Hrabia Henri wciąż ma do mnie słabość. Angerran wiele by ryzykował, gdyby zrobił mi coś wbrew mojej woli. Przykro mi, Charles, ale to ślepy zaułek. On wszystkiemu zaprzeczy i wyjdzie z tego bez szwanku. Nikt nie uwierzy w twoje słowa, jako porywacza, podczas gdy jego ojciec cię zniszczy.";
			link.l1 = "Do diabła! Żałuję, że do tego doszło... Przygotuj się, markizo, musimy iść. I tak, proszę cię o milczenie.";
			link.l1.go = "Julianna_76";
			link.l2 = "  Ale ten drań musi mieć inne słabości oprócz swojego ojca, prawda? Nie jest doskonały, wręcz przeciwnie, jest przeciwieństwem doskonałości!  ";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "Nie wiem, czy to będzie dla nas użyteczne... Angerran miał jakieś sprawy z miejscowym baronem piratów. Jacques Baraban?";
			link.l1 = "To Barbazon, madam. Miła para, oboje! Ale Jacques Dobry nie darzy mnie sympatią i nie mogę przypuścić ataku na Le Francois bez solidnej pewności.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Znowu jesteś zbyt bezpośredni, mój rycerzu. Pamiętasz kapitana Moreno? Twojego drugiego przeciwnika w hazardzie? Założę się, że przyszedł tu z powodu Angerrana. Musi wiedzieć coś wartościowego dla nas.";
				link.l1 = "Kapitan Moreno, ha! Tak, oczywiście. Czy on wciąż jest w mieście? Gdzie mogę go znaleźć?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Znowu jesteś zbyt bezpośredni, mój rycerzu. Zawsze ktoś coś wie, a nie każdy potrafi trzymać język za zębami w pewnych sytuacjach. Moi... uczniowie słyszą różne rzeczy w tym domu. Daj mi dzień, a dowiem się więcej albo znajdę kogoś, kto to zrobi.";
				link.l1 = "Markizo, myślałem, że zmartwienie ci pasuje, ale gniew pasuje ci jeszcze bardziej. Dziękuję, dajesz mi nadzieję!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Tak, wciąż tu jest i oszczędzę ci biegania w jego poszukiwaniach. Przyjdź tu jutro wieczorem - kapitan Moreno będzie na ciebie czekał tutaj, w tym pokoju. Chciałbym móc zrobić więcej, ale nie mogę, Charles.";
			link.l1 = "To już wystarczająco, markizo. Z nim po mojej stronie wszystko będzie znacznie łatwiejsze. Dziękuję. Do zobaczenia jutro wieczorem.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "Chciałbym to usłyszeć od ciebie w innej sytuacji, Charles. Przyjdź do mnie jutro wieczorem. Mam nadzieję, że dostanę to, czego potrzebujesz.";
			link.l1 = "Dziękuję jeszcze raz, Julianno! Zatem do jutra wieczorem.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "Proszę bardzo, mój przyjacielu! Kapitan Moreno już na ciebie czeka.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, myślę, że coś znalazłem. Pamiętasz kapitana Moreno? Tego, który grał przeciwko tobie tamtej niefortunnej nocy?";
				link.l1 = "Robię, co za włóczęga. Co z nim?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Zawsze to wiedziałem, Bartolomeo de la Cueva. Dlatego właśnie dotarłeś na moją imprezę. To było jak dodanie jalapenos do obiadu. Wiem, że ty i twoi chłopcy kręcicie się po tej wyspie już od kilku tygodni. Wiem, że to musi być w jakiś sposób powiązane z pirackim baronem Le Francois i Angerranem de Chievous. Opowiedz mojemu przyjacielowi wszystko o tym, a my utrzymamy twoje legendarne imię w tajemnicy w zamian. W przeciwnym razie wezwę strażników, którzy już stoją za drzwiami. Wezwałem ich na twoje przybycie.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Nie tylko oni! Angerran podarował mi naszyjnik, piękny! Duże i czyste perły, w tym jedna, ciemna jak południowa noc, pośrodku. Ale zamówił go u lokalnych jubilerów!";
			link.l1 = "... ";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Założę się, że nie zrobił tego tylko po to, by zadowolić mnie luksusowym prezentem. Chociaż, ten prezent był jego ostatnią deską ratunku, by zdobyć moją przychylność w granicach przyzwoitości. Angerran nie ma tytułów ani ziemi, nawet jego fregata pozostaje jego własnością jedynie do momentu, gdy jego ojciec zdecyduje inaczej. Korzysta z władzy i wpływów, ale nie ma własnego źródła dochodu. Być może zmęczyło go czekanie na datki od ojca i postanowił naprawić swoją sytuację finansową?";
			link.l1 = "Zaczekaj, pani! Gra w karty! Jeśli mamy rację, a de Chievous zaplanował to wszystko wcześniej, musiał potrzebować dużo pieniędzy na stawki, aby wystarczająco mocno przycisnąć naszego gubernatora. Prośba do rodzica o takie pieniądze mogłaby zwrócić jego niepożądaną uwagę na tę sprawę. Kradzież już skradzionych skarbów od korsarzy wydaje się cichym i bezpiecznym sposobem na zdobycie potrzebnej monety. Nikt by się nie dowiedział!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "Dla nas, Charles! Angerran nie może tym razem ujść z tym na sucho. Jego pozycja nade mną zaszła za daleko i chciałbym pomóc ci się tym zająć.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "Pirat-przegryw i niemal zakochana kurtyzana. Charles, masz dla siebie zespół marzeń!";
			link.l1 = "Niemniej jednak, dziękuję, wam obu. Szczerze! Teraz muszę to przemyśleć i opracować plan.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Ten dom ma wszystko, czego pragną jego goście. Zajmę się przygotowaniami. Dołącz do nas, gdy będziesz gotowy, Charles.";
			link.l1 = "Bardzo dobrze, pani.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Nic, ale ktoś w mieście go szuka. Aktywnie wypytują o ciebie i innych gości tamtej nocy. Nie wiem jeszcze, o co chodzi, ale jestem pewien, że wdepnąłeś w coś większego, niż myślisz.";
			link.l1 = "Coś większego? Co masz na myśli, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... to znaczy Monseniour de Chievous podarował mi w prezencie wspaniały naszyjnik z pereł. Jedna z pereł była czarna jak noc. Myślałam, że to tylko podróbka z ładną historią w tle. Nigdy go nie nosiłam, nie chciałam dawać fałszywych nadziei, ale jest tak hipnotyzująco piękny.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "Co zamierzasz zrobić, Charles? Masz jakiekolwiek pojęcie, co się dzieje?";
			link.l1 = "Jeszcze nie, ale to zrobię. De Chievous jest po uszy w coś poważnego, i to moja szansa. Jego ojczyzna nie tknie go, ale brytyjskie władze mogą. Wolałbym cię nie porywać, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "To bardzo miłe z twojej strony, Charles, ale niezbyt zabawne.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, dowiedziałeś się czegoś? Wyglądasz na zdenerwowanego... Co się stało?";
			link.l1 = "Cholera! Życzyłbym sobie, żeby sprawy wyglądały inaczej... Pakuj swoje rzeczy, powinniśmy iść, Markizo. Proszę, nie sprawiaj żadnych kłopotów.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, wejdź. Baronet już tu jest i mieliśmy miłą pogawędkę. Właśnie opowiadałem mu o twoim zainteresowaniu bieżącymi wydarzeniami.";
			link.l1 = "Julianne, nie jestem pewien, czy to było mądre...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronecie, wygląda na to, że twoi ludzie właśnie coś upuścili za drzwiami! Mógłbyś im powiedzieć, żeby lepiej się zachowywali?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Okropne! Co teraz robimy?!";
			link.l1 = "Do diabła! Chciałbym, żeby było inaczej... Spakuj swoje rzeczy, powinniśmy iść, Markizo. Proszę, nie rób żadnych kłopotów.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "Boże wszechmogący! Coście uczynili z moim salonem, panowie?! To wygląda jak średniowieczny koszmar! Kim są ci ludzie? I gdzie są strażnicy?";
			link.l1 = "W porządku, Julianne? Dobrze. Założę się, że strażnicy wydają swoją zasłużoną łapówkę w tawernie. Baronecie, należą Ci się gratulacje - udało Ci się naprawdę wkurzyć Dobrego Jacka. Taka niechlujna i nieprzygotowana próba zabójstwa to zupełnie nie w jego stylu.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Przepraszam za przerwanie tej ekscytującej dyskusji, ale jeśli nikt z was nie jest ranny, przejdźmy do gabinetu. Widok taki jak ten nie jest zbyt pocieszający dla damy... Tylko sufit jest bezkrwawy!";
			link.l1 = "Więc idź na górę, markizo. Naprawdę powinnaś się położyć na chwilę i z dala od tej całej krwi. Baroneta Cortney i ja omówimy to. Czy możemy kontynuować?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, czy jesteś gotowy podzielić się z nami swoim planem?";
			link.l1 = "Prawie. Powiedz mi, czy de Chievous to pedantyczny typ? Czy trzyma swoje księgi i dzienniki w porządku?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran to uosobienie ociągania się, jeśli chodzi o finanse! Podpisuje więcej papierów niż jakikolwiek bankier, którego znam. Chyba taki był od dzieciństwa, kiedy nie wiedział, kim był jego ojciec i żył w biedzie na ulicach.";
			link.l1 = "Wspaniale! Teraz potrzebujemy jego dziennika i ksiąg! To będzie wystarczający dowód dla Brytyjczyków. Musimy dowiedzieć się, jak je zdobyć! Żałuję, że nie wiedziałem o tym, kiedy miałem jego statek w swoim posiadaniu... ech.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Czekaj, Charles, naprawdę myślisz, że po tym wszystkim, co się wydarzyło, pozwolę sprzedać się de Chievousowi jak jakaś koza z farmy?";
			link.l1 = "Nie martw się, Julianne, to zajmie tylko kilka dni. Obiecuję, że będą traktować cię jak bezcenny wazon z Chin. Popraw mnie, jeśli się mylę, ale de Chievous nigdy nie pokaże się na wymianie?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "Jestem tego pewien. Angerran będzie czekał pod skrzydłem Francoisa de Lyons i nigdy nie ośmieli się spotkać z tobą na otwartym morzu. Ale co do mojego pojmania...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, przykro mi, że przeszkadzam, ale czy nie zapomniałeś zapytać o moje zdanie w tej sprawie? Tygodnie w tych skrzypiących trumnach... Czy zdajesz sobie sprawę, o co mnie prosisz?! Oczywiście jesteś przywiązany do tej... dziewczyny, ale nie jestem jednym z twoich załogantów! Przykro mi, ale to wszystko nie brzmi jak poważna historia miłosna.";
				link.l1 = "Obawiam się, markizo, że będę musiał nalegać. Nie mogę sobie pozwolić na jej stratę.";
				link.l1.go = "Julianna_127";
				link.l2 = " Wszyscy popełniamy błędy, Julianno. Ty powinnaś wiedzieć o tym najlepiej. Proszę cię o pomoc. ";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, przepraszam, że przerywam, ale czy nie zapomniałeś zapytać mnie o zdanie na ten temat? Tygodnie w tych skrzypiących trumnach... Czy zdajesz sobie sprawę, o co mnie prosisz?! Twoje uczucia są godne klasycznej literatury o rycerstwie, ale ja jestem tylko zwykłą kurtyzaną. Podziwiam cię i chcę ci pomóc, ale wszystko ma swoje granice!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Rozumiem, Charles. Chcę wierzyć w doskonałą prawdziwą miłość, ale chyba nie ma czegoś takiego na tym świecie.";
				link.l1 = "Dziękuję, markizo. Tym razem wszystko naprawię. Dużo się nauczyłem z tej historii i modlę się, bym nie zapłacił zbyt straszliwej ceny za to, co zrobiłem.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Podjąłeś decyzję, wspierałem cię na każdym kroku, ale dość tego. Poświęcić wszystko dla miłości, którą już porzuciłeś w mojej sypialni. Wszystko to jest bardzo wzruszające, Charles, ale nie jestem już taka młoda i naiwna.";
				link.l1 = "Obawiam się, markizo, że będę musiał nalegać. Nie mogę sobie pozwolić na jej utratę.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "No cóż, Kapitanie, rób co chcesz. Nie będę ci się opierać, ale wiedz, że robię to wbrew swojej woli.";
			link.l1 = "Pomyśl o mnie, co chcesz, Julianno, zasłużyłem na to. Ale odzyskam ją bez względu na koszt\nJulianno, posłuchaj, wiem, czego od ciebie żądam. Porzucić wszystko i pozwolić innym wciągnąć cię w wątpliwą grę. Ale w tej chwili jesteś moją jedyną nadzieją! Potrzebuję twojej pomocy w tym, a pozostanę twoim dłużnikiem aż do śmierci!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Zgoda, kapitanie. W końcu Angerran musi zostać ostatecznie pokonany. Pomogę ci, ale powiedz mi, jak zamierzasz mnie uratować z jego statku?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Zaczekaj. Możesz wziąć mój naszyjnik z perłą, Anglicy polują na czarną perłę, prawda? Ta sprawi, że cię wysłuchają. Co dalej?";
			link.l1 = "Następnie zabiorę śledczego na pokład i popłyniemy na Gwadelupę. Przeprowadzimy oficjalne przeszukanie fregaty de Chievous, gdy wróci z tobą na pokładzie. Sprawa Mercurego była poważnym incydentem z udziałem naszego sojusznika, więc De Lyon będzie musiał to umożliwić!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Powiedzą wszystkim, że to jego ludzie uratowali mnie z niewoli. I wiedz, Kapitanie, że jeszcze nie zdecydowałem, co im powiem.";
				link.l1 = "Nie mówienie niczego byłoby w porządku, markizo. Uwierz mi, wyciągnę cię stąd i sprawię, że Angerran zapłaci za wszystko.";
			}
			else
			{
				dialog.text = "Powiem im, że zostałem uprowadzony przez obcych, prosto z mojego domu, by trafić na statek Angerrana. Będzie to wyglądało, jakby zapłacił najemnikom za moje porwanie.";
				link.l1 = "Kolejny gwóźdź do trumny Angerrana, markizo.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Daj mi czas do rana, chyba że chcesz mnie nosić w worku. Wyślij też kilku ludzi, by mi pomogli - kobieta o moim statusie nie może podróżować bez wygód. Charles, uratowałeś mnie i pomogę ci, a także proszę, weź tę bezcenną czarną perłę, mój dar dla ciebie. Jeśli to się uda, będziemy kwita.";
				link.l1 = "Jak mówisz, markizo. Szczęśliwej drogi, wam obojgu! Do zobaczenia tutaj, gdy to się skończy.";
			}
			else
			{
				dialog.text = "Do świtu będę gotów do wypłynięcia. Nie zamierzam tłuc się po ładowni, więc upewnij się, że przygotujesz dla mnie porządny pokój, czy jakkolwiek to nazywasz. Charles, weź to. To cenny czarny perła. Zdaję sobie sprawę, że jest wart więcej niż to miejsce, ale nie wszystko można zmierzyć złotem. Mam nadzieję, że będzie ci to przydatne. Niech cię Bóg strzeże!";
				link.l1 = "Pomścij was obu! Zobaczymy się tutaj znowu, gdy to się skończy.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Gratulacje, kapitanie. Twój plan się powiódł. Jakież to ogromne skandale zorganizowałeś! Anglicy pojmali Angerrana i jego statek z całym ładunkiem z wyjątkiem mnie.";
				link.l1 = "Sir William nawet nie przyszedł, by się pożegnać. Obiecał przeprosić.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, zrobiliśmy to! W każdej chwili cię wypuszczą! Musimy jednak jak najszybciej opuścić wyspę. Gubernator jest bardzo zaniepokojony ostatnim aresztowaniem Angerrana.";
				link.l1 = "Cieszę się, że cię widzę, Julianne. Jak się masz? Jak poszła wymiana? Czy z nią wszystko w porządku?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Zakładam, że był zbyt zajęty, by się tym zająć. Jak nasz gubernator teraz. Lepiej opuść miasto, zanim przypomni sobie o twoim istnieniu. Kochał syna Henriego, ale brytyjskie papiery całkowicie go przycisnęły. Nie czekałbym, aż postanowi wyładować na tobie całą swoją frustrację.";
			link.l1 = "Sprawiedliwie. Poza tym, czeka na mnie na Martynice. Jak poszedł wymiana? Czy wszystko z nią w porządku?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Przebacz mi, lecz nie chcę o tym rozmawiać. Zapytaj ją zamiast tego. Żegnaj, Kapitanie. Wrócę sam. Muszę odpocząć od morza - Francois to całkiem miły gospodarz, kiedy nie jest nękany przez nudnych brytyjskich urzędników.";
			link.l1 = "Jest mi szczerze przykro z powodu tego wszystkiego, Madame. Dziękuję za współpracę mimo wszystko. Cieszy mnie, że zdobyłaś nowego... przyjaciela.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Dziękuję również, Charles, za dotrzymanie słowa. Znajdź Bartłomieja w moim domu w St. Pierre. Żegnaj. Zobaczymy się ponownie.";
			link.l1 = "Żegnaj, Julianne. Z Bogiem.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nie widziałem jej, ale Bartholomew wziął ją żywą i zdrową. Ten Anglik aresztował de Chievousa i jego majątek tuż pod nosem lokalnego gubernatora - nawet nie pisnął słowa! Cudowne!";
			link.l1 = "Wiesz, poszło zaskakująco gładko, biorąc pod uwagę okoliczności tego aresztowania. Choć, w dalszym ciągu powinno to się odbić czkawką później. Cokolwiek! Muszę natychmiast udać się na Martynikę, muszę zobaczyć ją jak najszybciej!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Bez wątpienia macie sobie wiele do powiedzenia. Ach, Charles, chciałabym mieć przy sobie mężczyznę z takim ogniem w oczach. Pospieszmy się, naprawdę tęsknię za gorącą kąpielą i czystą pościelą. Bartholomew będzie czekał na nas w moim domu w St. Pierre.";
			link.l1 = "Tak, romantyzm morskich podróży jest przeceniany. Oddam ci moją kajutę, markizo, to najmniej, co mogę zrobić. Chodźmy.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Już zrobiłeś dla mnie wszystko, co tylko mogłeś, Charles. Sprawiłeś, że cyniczna kobieta znów uwierzyła.";
			link.l1 = "Ja też, Julianne. Ja też.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, cieszę się, że przyszedłeś! Jak się miewa twoja dama? Wszystko u niej w porządku?";
				link.l1 = "Wszystko jest dobrze, dzięki tobie, Julianne. Chciałem powiedzieć to tobie jeszcze raz. Jesteś cudowną kobietą i będę ci na zawsze wdzięczny za całą twoją odwagę i pomysłowość.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, tak się cieszę, że przyszedłeś! Jak tam twoja dama? Czy wszystko z nią w porządku?";
				link.l1 = "Wszystko jest w porządku, dzięki tobie, Julianne. Chciałem ci to powiedzieć jeszcze raz. Jesteś cudowną kobietą i będę ci wiecznie wdzięczny za całą twoją odwagę i pomysłowość.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Może to ja jestem twoim dłużnikiem. W końcu uratowałeś mnie przed dwoma wyjątkowo natrętnymi klientami. Myślę, że wciąż jestem ci coś winien. Proś o cokolwiek, Charles.";
			link.l1 = "W takim razie mam małą prośbę, moja pani. Możesz coś zrobić, abyśmy się wyrównali.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Zamieniam się w słuch, kapitanie. O co chodzi?";
			link.l1 = "Ludzie popełniają błędy, ale to nie czyni świata złym. Pamiętaj o tym i bądź szczęśliwa, Julianne. Zasługujesz na szczęście.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "Ja... spróbuję, Charles. Dziękuję. Czy będziesz mnie odwiedzał od czasu do czasu... jako przyjaciel? Zawsze będziesz mile widziany u mnie!";
			link.l1 = "Doceniam to, markizo. Żegnaj i pamiętaj, co mi obiecałeś.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Jednak najwyraźniej nie na tyle cudowny... ale cieszę się, że dobrze się dla ciebie skończyło. Nic mi nie jesteś winien, po tym, co zrobiłeś, nie mogę ci wystarczająco podziękować! Odwiedzaj mnie, gdy tylko będziesz na lądzie. Zawsze będziesz mile widziany u mnie, jako przyjaciel!";
			link.l1 = "Dziękuję, markizo. Życzę wszystkiego najlepszego. Żegnaj!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, mój przyjacielu, jesteś taki niegrzeczny - odwiedzasz mnie tak rzadko! Tęskniłem za tobą, wiesz o tym? Masz ochotę na wino? Umieram z ciekawości, by posłuchać ekscytujących opowieści z pierwszej ręki! I wypróbować twoje słynne szczęście!";
			link.l1 = "Markizo, chciałem tylko przywitać się i upewnić się, że wszystko z tobą w porządku.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "A oto jesteś, mój przyjacielu! Cieszę się, że znowu cię widzę!";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Cóż, sposób, w jaki traktujesz mojego przyjaciela, nie pozostawia mi wyboru, monsieur. Przyjmuję twoje wyzwanie. Czas i miejsce?";
			link.l1 = "Tu i teraz. Zawołaj sługi, każ im przynieść świece, taki przytulny zmierzch nie wystarczy. To miejsce musi być jasne jak dzień!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Mój przyjacielu, proszę, nie bierz tego zbyt osobiście. Angerran to nieznośny typ, to prawda, ale nie powinieneś na niego polować. Zostaw to mnie.";
			link.l1 = "Jesteś pewny, Wasza Ekscelencjo? Jest pijany jak mój kwatermistrz po tygodniu na lądzie, ale z pewnością wie, jak posługiwać się szpadą. Od razu to widzę.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "Broń mnie Boże, Charles! Nie będę się z nim pojedynkował. Zagramy w karty, to broń cywilizowanych ludzi. Ogolę go do suchej nitki i wyślę do ciebie błagającego o pożyczkę na bezpieczny powrót do Quebecu.";
			link.l1 = "To całkiem solidny plan. Ale jeśli mnie pytasz, wolałbym, żeby drań był martwy, nie biedny. Powodzenia, Wasza Ekscelencjo!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "Do diabła, Angerran, nie ma mowy, żeby tam była dziesiątka! Nie ma mowy!";
			link.l1 = "Czy to było oskarżenie? To była twoja transakcja, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "Nie było tak. Ja tylko... jestem trochę podekscytowany i przepraszam. To był wypadek i żądam szansy na rewanż! Ten statek, ja... muszę go odzyskać! Albo do diabła z grą, po prostu powiedz mi, za ile jesteś gotów ją mi sprzedać? Podaj cenę, a ja zapłacę ją jutro przed południem!";
			link.l1 = "Niestety, lecz wierzę z całego serca, że łupów hazardu nie można odkupić. Można je tylko odzyskać. Flet jest teraz mój i nie zamierzam go sprzedawać. Przykro mi, że twoja pasja postawiła cię w takiej sytuacji, czasami powinniśmy być bardziej realistyczni co do naszych możliwości... Może masz więcej papierów okrętowych?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Jesteś łajdakiem, Angerran, a ty mnie przypierasz do muru. Wierzę, że mogę dać stawkę, którą zaakceptujesz.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, jesteś moją jedyną nadzieją, błagam cię, pomóż mi! Ta flet i jej... ładunek zostały już sprzedane Holenderskiej Kompanii. Muszę im przekazać wszystkie dokumenty jutro. Myślałem, że zostanę tu całą noc, więc przyniosłem je ze sobą. Stawię czoła katastrofalnej sytuacji, jeśli transakcja zostanie odwołana!";
			link.l1 = "Ale 'słodki Jacques', czyż nie zgadzasz się, że kobieta, którą faworyzowałeś, stoi teraz w obliczu jeszcze bardziej katastrofalnej sytuacji? Sam miałem swoją przygodę z hazardem i rozumiem coś takiego jak stawianie statku w zakładzie, nawet jeśli nie jest on twój. Ale zakładać się o damę?! Zaskoczyłeś mnie, naprawdę! A teraz wszystko, co cię obchodzi, to los twojej umowy?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Nie osądzaj mnie, Charles. Faworyzowanie dawnej kochanki potężnego hrabiego i nawet krótkie zakochanie się jest niczym w porównaniu z długiem miliona pesos wobec Petera Stuyvesanta. Jak mam to wyjaśnić jego agentowi? Wyobraź sobie całe to zniszczenie reputacji!";
			link.l1 = "Miałem podobny dług wcześniej, ale nie miałem absolutnie nic, a jednak jakoś sobie poradziłem. Ty też sobie poradzisz. Do zobaczenia, Jacques. Nie obiecuję i nawet nie zapytam, jaki towar jest wart milion, że trzymasz go we flecie.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "Tam jesteś, Charles. Miałem już wysłać po ciebie. De Chievous nalega na pojedynek i odrzuca wszelkie szanse na pojednanie. Dobrze ci poszło z kartami, ale czy jesteś pewien, że chcesz to kontynuować?";
			link.l1 = "Mam swędzącą podejrzliwość, Wasza Ekscelencjo, że od dawna pragnąłeś tego wyniku. Więc mówię tak. To musi być rozwiązane raz na zawsze. A co z warunkami pojedynku?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Za bardzo jesteś w swojej głowie, przyjacielu. Niektóre części naszego świata wciąż nie kręcą się wokół ciebie. Uwierz mi, jestem głęboko rozczarowany, jak wszystko potoczyło się zeszłej nocy. Bardzo głęboko. Ale najpierw, porozmawiajmy o losie twoich... wygranych.";
			link.l1 = "Dobrze. Czy chcesz wiedzieć, jak zwrócić swoją fletę, czy jak się miewa Madame Julianne?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Widzę, że zamieniłeś swoją niestosowną ironię na złośliwość? Charles, jesteśmy po tej samej stronie, nie zapominaj o tym.";
			link.l1 = "Sporna argumentacja, Wasza Ekscelencjo. Delikatnie mówiąc. Od czego zaczniemy: od statku czy od damy?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "Umowa ze Stuyvesantem, oczywiście - jego agent czekał na mnie cały poranek, a ja kończę się z wymówkami. Potrzebuję dokumentów dotyczących fletu, Charles.";
			link.l1 = "Dobrze. Ona jest twoja. Nie wierzę, że de Chievous grał uczciwie, dlatego możesz odzyskać swoją własność za połowę ceny. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "Z chęcią spełnię tę prośbę. Jaka była cena statku, o której mówiłeś? 500 000? Pasuje mi.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Teraz to będzie czterysta sześćdziesiąt tysięcy pesos wraz z podatkami. Umowa. 135 000.";
			link.l1 = "Słuchaj... Męczy mnie już ta kłótnia. Więc zapłać, weź swoje dokumenty i skończmy z tym.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "Nie masz litości dla starych przyjaciół, co Charles? Teraz, z wszystkimi podatkami wliczonymi...";
			link.l1 = "Długi karciane i przyjaźń nie mają ze sobą nic wspólnego, Wasza Ekscelencjo. Podatki zapłacisz sam jako kupujący albo sprzedaję statek w Le Francois. Pamiętaj, nie korzystam jeszcze z twojej pozycji...";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Zgoda, niech tak będzie. Teraz, pojedynek. Nie potrzebuję kłopotów z hrabią de Levi Vantadur, dlatego wszystko musi być jak najbardziej zgodne z prawem. Słyszałeś mnie, Charles? Zgodnie z prawem! Wyślę z tobą dwóch oficerów mojego garnizonu - obaj są szlachetnymi i szanowanymi ludźmi. Będą twoimi sekundantami zamiast twoich zwykłych... towarzyszy. Chcę, aby wszystko było krystalicznie jasne, aż do zakończenia interesu!";
			link.l1 = "Jakże miło z twojej strony. A co, jeśli nasz dobry przyjaciel postanowi grać nieczysto? Wolę ufać moim plecom ludziom, których nazywam przyjaciółmi, i tym, którzy wiedzą, co robić w takich sytuacjach, niż ludziom, którzy urodzili się w dobrych rodzinach.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, przestań zachowywać się, jakby ten pojedynek był tylko między tobą a mną. To poważna sprawa. De Chievous nie jest człowiekiem, którego można zabić i po prostu uciec bez konsekwencji. Każdy wynik będzie miał swoje dochodzenia, być może nawet sąd. Potrzebujemy godnych zaufania świadków. Widzisz, dbam o ciebie! Najważniejsze jednak jest to, że nie możesz go zabić\nRozumiem, Angerran jest zdeterminowany i najprawdopodobniej jest przyzwoitym wojownikiem, ale Charles, nie możesz go zabić! Zranić go, upokorzyć nawet, ale na tym się zatrzymaj. Jeśli go zabijesz - będą konsekwencje, których żaden z nas nie będzie w stanie uniknąć ani przeżyć. Mimo że hrabia de Levi Vantadur nigdy oficjalnie nie uznał swojego bękarta, nie ma innych synów. Jego gniew nie będzie miał końca.";
			link.l1 = "Wspaniale, więc wolałbym dać się zabić, niż pozwolić rozwścieczonemu hrabiemu wyrzucić cię z twojego gubernatorskiego stołka?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Obawiam się, że jeśli nie posłuchasz, nie przeżyjemy Angerrana de Chievousa zbyt długo. Pamiętaj o tym i bądź ostrożny. Pojedynek jest ustalony na dziesiątą wieczorem za bramami miasta. Moi oficerowie spotkają się tam z tobą. Teraz, ostatnia kwestia: Madame Julianne Botot - jak się miewa?";
			link.l1 = "Chcesz wiedzieć, czy już skorzystałem z mojej nagrody? Nie, Ekscelencjo, jeszcze nie lub nigdy - to nie ma znaczenia. Co ma znaczenie, to że nigdy więcej nie odwiedzisz domu markizy. Była co do tego krystalicznie jasna. Nie mogę jej za to winić. Julianne sama wybierze swojego następnego patrona.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Wiesz, jak zaskoczyć, Charles. Cóż, mam nudne spotkanie z agentem Kompanii, na które muszę się udać. Ty też powinieneś iść, przygotuj się, a ja pamiętam, o czym cię ostrzegałem.";
			link.l1 = "Z pewnością spróbuję, Ekscelencjo. Ale to walka, więc nic nie obiecuję. Dzięki za pomoc.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "Żyjesz, Charles! Co za ulga, jak sobie poradziłeś? Czy to krew?! Czy de Chievousowi się udało?";
			link.l1 = "Niestety tak. Jest ranny, ale nie poważnie. Musiał uciekać, ale rzucił na nas swoich zbirów. Krótko mówiąc, część tej krwi nie jest moja.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Dranie! A moi ludzie? Czy żyją, by zaświadczyć, co się stało?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Są w porządku, Ekscelencjo. Trochę poturbowani, ale przeżyją.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "Nie wszyscy, Ekscelencjo. Jeden dżentelmen nie dotarł - de Chievous zadał sobie trud, by przyprowadzić muszkieterów. Nie mogłem nic zrobić.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "„To było piekło na ziemi, Ekscelencjo. Obaj dzielni panowie polegli w walce. Gdyby nie oni, byłoby ze mną krucho. De Chievous zorganizował prawdziwą cholerną zasadzkę.”";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Wspaniale! Zdobędę ich pisemne zeznania w obecności wiarygodnych świadków. De Chievous za to zapłaci!";
			link.l1 = "Nie sądzę, że możemy nawet w najmniejszym stopniu zaszkodzić jego imieniu. Wolałbym go znaleźć i samemu dokończyć robotę mimo wszystkich twoich ostrzeżeń. Taki tchórz nie zasługuje na życie.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Okropne. Ale przynajmniej otrzymamy pisemne zeznania od jednego świadka. De Chievous zapłaci za to!";
			link.l1 = "Nie sądzę, abyśmy mogli choćby w najmniejszym stopniu zaszkodzić jego imieniu. Wolałbym go znaleźć i dokończyć robotę sam, mimo wszystkich twoich ostrzeżeń. Taki tchórz nie zasługuje na życie.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Cholera go! To byli dobrzy ludzie, Charles! Przysięgam, że drań zapłaci!";
			link.l1 = "Nie sądzę, abyśmy mogli choćby w najmniejszym stopniu zaszkodzić jego imieniu. Wolałbym go znaleźć i samemu dokończyć robotę, mimo wszystkich twoich ostrzeżeń. Taki tchórz nie zasługuje na życie.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Zapomnij o tym, Charles. Drań zrobił całe potrzebne szkody sam. Założę się, że teraz ucieka, ukrywając się w błocie jakiejś biednej kolonii. Mało prawdopodobne, że teraz stanowi dla ciebie jakiekolwiek zagrożenie. To łotrostwo było tylko ugryzieniem uciekającego węża. Wygląda na to, że również jesteś ranny, czy potrzebujesz lekarza?";
			link.l1 = "Dziękuję za troskę, Ekscelencjo, ale mam się dobrze.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Dobrze wiedzieć. Możesz teraz swobodnie odetchnąć, ta historia się skończyła. Zrelaksuj się i wróć do swoich spraw. A tak przy okazji, o tym... Nie skończyliśmy naszej wcześniejszej rozmowy o twoich ostatnich wygranych. Czy zdecydowałeś, co z tym zrobisz...?";
			link.l1 = "Nie do końca cię rozumiem, Jacques. Co to? Chodzi ci o markizę? Cholera! Madam Botot! De Chievous jest na wolności, nie jest już dla mnie zagrożeniem, ale jest zdesperowany i może zrobić wszystko! Powinienem iść! Wyślij straż do domu markizy! Teraz!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "Sławny kapitan, mówisz? Ten, który odparł atak Hiszpanów i prawie doszczętnie spalił to małe miasteczko? Rozumiem. Co pijesz?";
			}
			else
			{
				dialog.text = "Sławny kapitan, mówisz? Nigdy o tobie nie słyszałem... Co pijesz?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, tak jak nasza piękna gospodyni? Czy jesteś pewien, że potrafisz właściwie smakować po całej tej soli morskiej? Zwykle, ludzie twojego kalibru wolą pić rzeczy, które mogą rozpuścić stary but.";
			link.l1 = "Jeśli to była sugestia, żeby razem przejść przez bramy, to jestem za. Też cię nie lubię i cieszę się, że to uczucie jest wzajemne. Przejdźmy do rzeczy, i tak nie jesteś w tym dobry. Zostawiam ci wybór warunków i broni.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "Bukiet brudu i kociego siki? Uroczo! Tego kwaśnego ścierwa nawet nie dojrzewają w beczkach, bo i tak nigdy nie stanie się winem. Powiedz, czy sól morska aż tak mocno uderza w smak?";
			link.l1 = "Jeśli to była sugestia, aby przejść razem przez bramy, to się zgadzam. Też cię nie lubię i cieszę się, że to uczucie jest wzajemne. Przestańmy gadać, i tak nie jesteś w tym dobry. Zostawiam ci wybór warunków i broni.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ha, taki odważny chłopak! Teraz uspokój się i trzymaj dystans. Nie jesteśmy w tawernie, a ja nie jestem twoim kompanem do picia. Jesteś znacznie poniżej mojej klasy, nie powinniśmy nawet rozmawiać, ale dama tego zażądała. Teraz, Jacques i ja mamy niedokończone interesy...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne, wszystko w porządku? Woda, wy idioci! Przynieście wodę!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Masz całkowitą rację, jest tu duszno. Jak dotąd to była bardzo zabawna gra, ale zróbmy małą przerwę przed finałem. Do widzenia, Jacques - pamiętaj o zasadach naszego turnieju?\nA oto Charles de Maure, prawda? Kapitan o kiepskim guście do wina, pamiętam cię. Nie martw się, gdy skończę tutaj, będziesz pił tylko wodę. Więc nie śpiesz się, ciesz się chwilą, napij się czegoś. Kiedy będziesz gotowy, dołącz do mnie w tym małym pokoju. Zakończymy noc w bardziej komfortowym otoczeniu...";
			link.l1 = "Nie mogę się tego doczekać, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "Nareszcie jesteś. Gotów rozstać się ze swoimi pieniędzmi?";
			link.l1 = "Wolałbym dodać twoje do nich. Proszę!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Cóż za mądre słowa, niestety nasz drogi gubernator nalegał na zmianę zasad tuż przed swoją haniebną porażką. Teraz jesteśmy zobowiązani dodać coś więcej do pieniędzy na szali. Stawki muszą być uznane za równe przez obie strony. Moim wkładem jest flet ze srebra.";
			link.l1 = "Chodź, to jest nudne - mogę zdobyć pięć takich za złoto w kilka tygodni najazdów. Daj mi coś większego.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Tak, widziałem twój statek, muszę przyznać, że to naprawdę widok do podziwiania. Podnieśmy więc tę stawkę - dwa statki przeciwko jednemu. Moja fregata i flauta z srebrem przeciwko twojemu statkowi?";
				link.l1 = "Godna gra! Pani Botot się myliła - TEN pojedynek przejdzie do legend. Zgoda!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Spójrz na to, nasz kapitan to łobuz! Jednakże kaperstwo to święta rzecz. A co powiesz na okręt wojenny? Fregata, 48 dział. Szybsza niż wiele korwet - produkt królewskich stoczni, udoskonalony przez najlepszych szkutników na świecie. Niesie ze sobą kolubryny o doskonałym zasięgu i celności. Co ty na to?";
					link.l1 = "Znacznie lepiej, wchodzę! Ruszajmy!";
				}
				else
				{
					dialog.text = "Słyszałem, że zacumowaliście tu, Kapitanie. Bądź wdzięczny, że zgodziłem się przyjąć waszą starą łajbę jako stawkę. Chodź więc, chyba że odmawiasz?";
					link.l1 = "Zgoda, masz rację. Chodźmy.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Gra skończona, Kapitanie, dostałeś to, czego chciałeś. Chełp się, jeśli chcesz. Sugeruję, abyśmy omówili warunki wykupu mojego fregaty jutro w południe.";
					link.l1 = "To wszystko? Szczerze wierzę, tak jak ty, że co stracone w hazardzie, nie można odkupić, tylko odzyskać. Albo sprzedam ją rybakom na drewno i opowiem im o twojej hojnej darowiznie.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "Zatem Fortuna miała swoje zdanie. To wyszło nader osobliwie. Gratulacje. Kapitanie de Maure. Proponuję, abyśmy omówili warunki wykupu mojego fregaty jutro w południe.";
						link.l1 = "Tak szybko? Rozczarowujemy innych gości, monsieur. Jeśli dobrze pamiętam, masz jeszcze jeden statek. Szczerze wierzę, podobnie jak ty, że to, co przegrałeś w hazardzie, nie może być odkupione, jedynie odzyskane.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "Tak więc Szczęście przemówiło. To wyszło bardzo ciekawie. Gratulacje. Kapitanie de Maure. Zarobiłeś na porządny napitek, spróbuj Sangiovese. Zakładam, że Jacques dobrze ci zapłaci za tę łajbę, wydaje się, że ma do niej uczucia, uczucia dużo większe niż do innych pewnych rzeczy. To wystarczy, by kupić przyzwoite wino.";
						link.l1 = "Poddajesz się już? Rozczarowujemy innych gości, monsieur. Jeśli dobrze pamiętam, masz jeszcze jeden statek. Stawiam twój fregat przeciwko mojemu flecie ze srebrem, skoro uznałeś mój statek za zbyt skromny.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Nieszczęście, Kapitanie. Niemniej jednak doceniam twoją odwagę, a do tego dzisiaj mam dobry humor. Zatrzymam twoje złoto, ale możesz zatrzymać swój statek. Zejdź mi z oczu i proszę, unikaj hazardu w przyszłości. Pewnego dnia cię to zgubi.";
				link.l1 = "Bardzo szlachetne z twojej strony, nie spodziewałem się tego. Żegnaj, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Jest znacząca różnica między chełpieniem się a drwieniem z pokonanego przeciwnika, monsieur de Maure.";
			link.l1 = "Już się uważasz za pokonanego? Ale wszystko zaczęło się tak dobrze... ach! Madam Botot, wierzę, że Twój salon właśnie zyskał kolejną bogatą opowieść o różnicach między mówieniem a działaniem!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "Czego jeszcze chcesz? Nie mam więcej statków w zanadrzu, a także wystarczająco gotówki, by pokryć nawet jeden statek. Hazard na doubloony to nie jest poważna sprawa po tym wszystkim, co dziś widzieliśmy.";
			link.l1 = "Czy jesteś mniej zaradny niż nasz słodki Jacques Dille do Parkuet? Daję ci najpiękniejszą szansę, by udowodnić, że nie wszystko w miłości jest na sprzedaż. Fortuna też nie sprzedaje swojej łaski. Srebrny statek i twój fregata kontra to, co cenisz bardziej niż złoto.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Kapitanie, to nawet nie jest śmieszne. Załatwmy to szybko - świt już blisko. Omówimy wykup mojego fregaty jutro.";
			link.l1 = "Niech ci będzie, masz to - trzy statki! W tym prawdziwy okręt wojenny przeciwko naj... cóż, najdroższej damie Nowego Świata. Czy możesz w ogóle odmówić takiej stawce?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "To byłoby szaleństwo. Choć to jest szaleństwo, monsieur de Maure. Proszę. Ale pamiętaj, to był twój pomysł.";
			link.l1 = "To będzie legenda, którą będą smakować przez rok za zamkniętymi drzwiami! Hej ty, więcej wina i świec! Gra musi trwać!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Niedawno uznałeś tę fletę za niegodny zakład przeciwko naszym statkom. Co się zmieniło?";
			link.l1 = "Znudzony. Dodajmy trochę pikanterii do naszego pojedynku - twoja fregata i mój statek przeciwko...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "Flet, który tak nisko ceniłeś? Czy przypadkiem masz gorączkę? Nie wyglądasz zbyt dobrze.";
			link.l1 = "Jestem całkowicie w porządku, dziękuję. Nie słuchałeś. Stawki dwa do jednego nie są zbyt imponujące, to prawda, więc wyrównajmy szanse! Nie wszystkie wartości można ocenić w złocie, czyż nie? A może po prostu wolisz nie walczyć z wiatrem, jeśli coś nie idzie zgodnie z planem, więc zmieniasz kurs? Szkoda, wydaje się, że się myliłem co do ciebie. Pani Botot, wierzę, że twój salon właśnie zyskał kolejną bogatą opowieść o różnicach między mówieniem a działaniem...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Nie próbuj działać mi na nerwy, monsieur de Maure, jesteś na to zbyt naiwny.";
			link.l1 = "Rzeczywiście. Brak woli nie jest grzechem... chyba że jesteś wojskowym, oczywiście. Albo szlachcicem, honor rodzinny, jak zapewne wiesz, jest czasami takim ciężarem. Raczej nie jesteś w ogóle zaznajomiony z takimi dylematami.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Próbujesz wyzwać mnie na pojedynek czy kontynuować grę?";
			link.l1 = "Oba będą odpowiednie. Będę chwalił kolekcję win Markizy, podczas gdy ty się ogarniesz.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "Niech tak będzie. Ta noc powinna zakończyć się godnie. Dwa wielkie okręty przeciw staremu kadłubowi wypełnionemu srebrem i najlepszej kobiecie Nowej Francji! Oddychaj głębiej, monsieur de Maure, ten zakład stanie się legendą wśród plotek wyższych sfer.";
			link.l1 = "Twoja porażka stanie się legendą, rzeczywiście, monsieur de Chievous. Przynieście nam więcej wina i świec! Zróbmy to!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "Straciłeś głowę przez szczęście, monsieur de Maure. Ryzykujesz tutaj, a łaska fortuny jest krótka.";
			link.l1 = "Krótka przysługa to droga do prawdziwej miłości. Co można powiedzieć o kupionej lojalności. Prowadzi jedynie do pogardy lub nudy.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "Twoje próby wyprowadzenia mnie z równowagi mnie bawią. Lepiej zapytaj panią Julianę o takie rzeczy jak względy, miłość i wszystko inne, co można kupić lub nie. Ale pośpiesz się - jutro opuszcza miasto.";
			link.l1 = "Przynajmniej twoja wiedza na ten temat jest jednostronna. Nie możesz zdobyć przychylności Lady Fortuny ani wygrywając, ani płacąc tutaj, więc nie możesz znać jej miłości. To wymaga odwagi, monsieur, i niezachwianej woli, by podjąć ryzyko. Nie wspominając o tym, że bardziej... ziemskie damy również cenią te rzeczy. Stawiam dwa moje statki przeciwko jednemu z twoich, wchodzisz w to?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "Chcesz kontynuować tak chciwie? Dobrze, cokolwiek. Ale przynajmniej dodajmy do tego trochę dramatu, monsieur de Maure. Mówiłeś coś o miłości i cenach? Proponuję wyrównać nasze stawki - twoja łajba i flet ze srebra kontra mój fregat i najlepsza kobieta Nowej Francji. Co powiesz teraz?";
			link.l1 = "Mówię, że zdecydowanie umiesz grać w karty z klasą, monsieur! Więcej wina i świec! Do dzieła!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Niewiarygodne, monsieur de Maure, to jest po prostu niewiarygodne!";
				link.l1 = "Tak, właśnie, Europa nie doznała takiej klęski od bitwy pod Rocroi, monsieur de Chievous. Artysta, który mieszka gdzieś we mnie, drży z pragnienia, by uwiecznić taką historyczną chwilę. Szkoda, że już nie rysuję jak w młodości. Ale może madame Julianne ma utalentowanego artystę w pobliżu, czyż nie mam racji?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Nieszczęście, Kapitanie. Niemniej jednak doceniam twoją odwagę, a do tego jestem dziś w dobrym nastroju. Wezmę twoje złoto, ale możesz zatrzymać swój statek. Znikaj mi z oczu i proszę, unikaj hazardu w przyszłości. Pewnego dnia, to cię zabije.";
				link.l1 = "Bardzo szlachetnie z twojej strony, nie spodziewałem się tego. Żegnaj, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "Nie, nie rozumiesz. To jest tak niewiarygodne, że po prostu nie może być prawdą!";
			link.l1 = "Wszyscy widzieliśmy karty, monsieur de Chievous - Fortuna nigdy nie kłamie.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "Fortuna nie, ale ty, monsieur de Maure, owszem! Wydaje mi się, że za twoją bezczelnością krył się plan, a nie tylko pasja. Jesteś kłamcą i oszustem - jestem gotów to potwierdzić przed wszystkimi gośćmi.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Monsieur de Chievous, czy dobrze usłyszałem? Jesteś gotów potwierdzić swoje podejrzenia nie tylko słowami? Wydaje się, że twoje obelgi posuwają się za daleko, a ja, w przeciwieństwie do ciebie, cenię honor mojej rodziny.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Drugi syn, oszust i naciągacz nie będzie mi mówił o honorze rodziny! Zamknij się, Julianne, zajmę się tobą później! Charles de Maure, nalegam, byś natychmiast dał mi satysfakcję! Miecz czy pistolet?";
			link.l1 = "Oba. Szczerze mówiąc, cieszę się, że zmieniłeś zdanie. Pamiętasz, sugerowałem, żebyśmy przeszli się za bramy? Co powiedziałeś o mojej niegodnej klasie? Może gra w karty dała ci jednak trochę odwagi?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Zbyt wielki zaszczyt, ale zgadzam się z markizą. Zakończę cię jak szlachcic, de Maure, mimo że na to nie zasługujesz. Wyzwanie cię na pojedynek jutro w południe, przez Jego Ekscelencję, gubernatora. Przyjdź sam lub wyślij swoich sekundantów, aby omówić warunki. Do zobaczenia. Pani, moje uszanowanie.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "Otóż to, ulubieńcu fortuny. Zająłeś się swoimi sprawami, mam nadzieję? Nie zapomniałeś wyznać grzechów? Mówią, że piekło może być dość niewygodne bez tego.";
			link.l1 = "Mowa jest tania, monsieur. Nie umiesz grać w karty, teraz sprawdźmy twoje umiejętności szermiercze... Zatańczmy!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Nieźle... jeden, do diabła z tobą. Ale wciąż żyję!";
			link.l1 = "Twoja rana nie wygląda dobrze, ale mimo to powinieneś pokazać się lekarzowi. Wyraźnie, nie możesz tak dalej, umrzesz jeśli tak zrobisz. Wygląda na to, że skończyliśmy tutaj. Wygrałem, i nie oszukiwałem. Zwrócę ci twój statek i opuścisz St. Pierre. Nigdy więcej się nie zobaczymy.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "Co za ogromna rycerskość! Zobacz, monsieur de Maure, możesz być naturalnym szermierzem, ale z pewnością oszukiwałeś przy kartach. Zamieszałem talią trzy razy. Do diabła, trzy razy! Żaden cud na świecie nie mógł cię uratować, ale mimo to wygrałeś! Chciałbym wiedzieć, jak to zrobiłeś... Nieważne, wkrótce opowiesz o tym wszystkiego diabłu. Uderzajcie, chłopcy!";
			link.l1 = "Ty draniu! Okazałem ci łaskę, a tak mi się odpłacasz?! Panowie, do broni!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "Przyznaję, Monseniour de Maure, jestem nieco zaskoczony widząc cię tutaj. To oznacza, że nie myliłem się co do ciebie, a ta dzika dziewczyna coś dla ciebie znaczy?";
			link.l1 = "Zastanawiam się, jakie jest stanowisko twojego dobrego przyjaciela de Lyonsa w kwestii porywania oficerów od szanowanych kapitanów naszej Marynarki? Może powinniśmy poprosić go, by do nas dołączył i opowiedzieć mu całą historię?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "To ci wcale nie pomoże, zaufaj mi. Również traktowałem twoją dziewkę lepiej niż pojmanego generała. Na razie. Ale wszystko może się zmienić i to zależy od ciebie, Charles.";
			link.l1 = "Nie przypominam sobie, byśmy mieli z tobą miłosne spotkanie. Nie Charlesuj mnie, Monseniour de Chievous. Przejdź do rzeczy i powiedz mi, czego ode mnie chcesz?";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "Od ciebie? Nic, broń Boże! Ty i ja właśnie załatwiliśmy niefortunną bójkę po jakiejś skandalicznej grze w karty, wypiliśmy kilka drinków i opuściliśmy ten pokój jako starzy dobrzy przyjaciele.";
			link.l1 = "Angerran, wyglądasz dobrze pomimo niedawnej rany, a każda minuta tej bezwartościowej pogawędki sprawia, że chcę to naprawić. Nawet myśl o zniszczeniu tych pięknych dywanów Francoisa de Lyons staje się coraz bardziej kusząca.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "    Ale dobry stary Francois kocha te dywany, Charles. Każdy coś kocha. Skoro tu jesteś, musisz kochać swoją małą przyjaciółkę w ramionach. Jestem gotów oddać ci ją w zamian za moją własność. Popsułeś grę i choć zwykle nie wybaczam takich wykroczeń, mogę zrobić dla ciebie wyjątek. Dajesz mi nagrodę, której tak pragnę, a ja daję ci to samo. Potem pięknie się rozstaniemy. Tyle o miłości.";
			link.l1 = "Ty myślisz, że noszę markizę jak pieprzony klejnot w sakiewce? Bzdura! Jak miałbym ci ją oddać?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nie obchodzi mnie to w ogóle, Charles. Masz dwa tygodnie, by się tym zająć. I tak, chcę, aby ta nagroda została odebrana w tajemnicy. Powiedzmy, jakiś kapitan, który wygrał absurdalnie drogą kurtyzanę, ale nie zdobył jej przychylności, mógłby zrobić coś głupiego, prawda? Myślisz, że jesteś już wystarczająco zdesperowany, Charles?";
			link.l1 = "Chcę najpierw zobaczyć moją oficer, aby upewnić się, czy wciąż żyje.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Nie ma mowy. Będziesz musiał zaufać mojemu słowu. Ona pozostaje w bezpiecznym miejscu i tam zostanie, dopóki nie dostanę swojej nagrody. Ale jeśli będziesz nadal nalegać na zobaczenie jej wcześniej, z przyjemnością cię uraczę, przesyłając ci jakąś jej część. Jakie są twoje ulubione? Ucho, nos, kilka palców?";
			link.l1 = "Połóż na niej rękę, ty łajdaku, a uduszę cię gołymi rękami, przysięgam na Boga! Nie waż się mnie, kurwa, testować!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Uspokój się. Wszystko, co się wydarzy, zależy całkowicie od ciebie. Nie lubię przemocy, używam jej tylko wtedy, gdy muszę. Nie zmuszaj mnie do tego. Po prostu przekaż mi moją nagrodę na Przylądku Scott na Dominice w ciągu mniej niż dwóch tygodni, a otrzymasz to, co jest twoje. Nie obchodzi mnie, jak to zrobisz. Jeśli chcesz kraść - kradnij, w końcu jesteś piratem, tylko dobrze ubranym.";
			link.l1 = "Ty cholernie złudzasz się, jest ogromna różnica między Piratem a przeklętym handlarzem niewolników...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Oddychaj głębiej, zaraz będziemy modnie paradować przed starym Francois. Jesteśmy teraz przyjaciółmi, pamiętasz? Uśmiechnij się, Charles, no dalej! Rozstajemy się. Przylądek Scott Head, Dominika, za dwa tygodnie. Nie spóźnij się.";
			link.l1 = "Zobaczę cię tam.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "Dobry wieczór, pani Botot, kapitanie de Maure. Proszę zachować spokój.";
			link.l1 = "Markizo, za mną, teraz! Monseniour, co to ma znaczyć?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "Mam tuzin ludzi za drzwiami i nadzwyczajne uprawnienia zatwierdzone przez twój Rząd. Strażnicy ci nie pomogą. Dlatego, proszę, odłóż swój miecz, panie. Chcę tylko porozmawiać. Na razie.";
			link.l1 = "Monsieur, kimże jesteś i jak tu trafiłeś?! Powinieneś się wytłumaczyć!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Pozwólcie, że się przedstawię - sir William Cortney, baronet Cortney. Teraz uspokójmy się i porozmawiajmy.";
			link.l1 = "W porządku, Monseniour Cortney, zamieniamy się w słuch.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Proszę wybaczyć podsłuchiwanie, ale obecne okoliczności nie pozostawiają mi innego wyboru. Chociaż pozostaję anonimowy tutaj w St. Pierre, prowadzę niezwykle ważne śledztwo w imieniu Korony Anglii. Dotyczy ono statku kurierskiego zaginionego na morzu. Czy kiedykolwiek słyszałeś o brygantynie Regina?";
			link.l1 = "Nie znam i nie rozumiem twoich podejrzanych aluzji, Monseniour. Jestem uczciwym kapitanem...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "Nie obchodzą mnie najmniejsze niecne interesy wasze, panie. Zrobiłem trochę dochodzenia na wasz temat i, szczerze mówiąc, uczyniłem was moim pierwszym podejrzanym, gdy usłyszałem, że odwiedziliście Martynikę tuż po zniknięciu Reginy. Jednakże, nie jesteście idiotą i wasi ludzie tutaj nie bawili się perłami. Dlatego, na razie, nie jesteście już na mojej liście podejrzanych.";
			link.l1 = "Perły? Jakie perły, o których bredzisz?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Ręcznie wybrane, duże perły z operacji hiszpańskiego Zachodniego Głównego. Perły są również czarne, co oznacza, że są niezwykle rzadkie, czy kiedykolwiek słyszałeś o takich?";
			link.l1 = "Chyba tak, choć zawsze myślałem, że to kolejna bzdurna opowieść żeglarzy. Tak samo jak historie o Latającym Holendrze. Julianne, co się dzieje?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Muszę prosić, byś przedstawiła to tutaj, pani. To sprawa najwyższej wagi. Tymczasem, panie, musisz mi opowiedzieć wszystko o kapitanie Moreno. Podejrzewam, że to on dał ci ten trop. Jestem bardzo ciekawy, jaką rolę odgrywa w tej grze.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno nie jest jego prawdziwym imieniem, Monseniour Cortney. Nazywa się Hernando Vasquez, znanym również jako Krwawy Don, hiszpański pirat, który był kiedyś kwatermistrzem Albatrosa - statku niesławnego Bartholomewa Portugalczyka.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Zamieniliśmy tylko kilka słów. Nie mam wiele do opowiedzenia. Wyglądał jak prawdziwy wilk morski.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Moje, moje. Czy mogę zapytać, skąd to wiesz?";
			link.l1 = "Znałem niegdyś jego kapitana. Właściwie to ja go pojmałem i oddałem Holendrom. To długa historia. Szkoda, że nie złapałem wtedy samego Vasqueza...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Sam jesteś wilkiem morskim, panie. Nie wierzę, że nie zauważyłeś więcej.";
			link.l1 = "Delikatny akcent, sposób w jaki wyglądał i się zachowywał. Założę się, że to Hiszpan, monsieur Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "To jest łamacz gry, panie. I to jest złe. Pani, czy znalazłaś naszyjnik? Pozwól, że go obejrzę\nTak, rzeczywiście, to jedna z hiszpańskich czarnych pereł. Spójrz, to żeglarskie bzdury są całkiem prawdziwe. Pozostaje tylko dowiedzieć się, jak ten de Chievous zdobył jedną z nich. A tak przy okazji, czyż nie jest on bękartem księcia de Levy Vantadur?";
			link.l1 = "To na pewno on. O ile wiemy, miał do czynienia z miejscowym pirackim baronem w Le Francois. Może kupił tę perłę od niego?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Może i tak. Ale nie podoba mi się hiszpański ślad w tej sprawie. W każdym razie dziękuję za współpracę. Obawiam się, że muszę odwiedzić cię ponownie jutro o tej samej porze dnia. Prosiłbym także o obecność kapitana de Maure. Być może będę miał więcej pytań do ciebie. Powinienem teraz udać się do Le Francois.";
			link.l1 = "Monsieur Cortney, zaczekaj. Może mógłbym się do ciebie przyłączyć? Jacques Barbazon nie zyskał swojego przydomka za to, że jest kochającą i łagodną osobą, a ta sprawa również mnie interesuje.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Kapitanie, jestem wzruszony twoją troską, ale to nie wchodzi w grę. To jest sprawa państwowa. Drań zna swoje miejsce i nie odważy się podnieść ręki na emisariusza Korony, w przeciwnym razie jego żałosna wioska zniknie! Jeszcze raz przepraszam za najście, madame. Dobry wieczór.";
			link.l1 = "Do zobaczenia jutro wieczorem, Baronecie.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Nie gniewaj się na nią, Kapitanie. Potrafię być bardzo przekonująca. Twoja historia jest imponująca, naprawdę. Wierzę, że mogę mieć dla ciebie zastosowanie.";
			link.l1 = "Wyglądasz na zadowolonego, jak poszło w Le Francois?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Jak się spodziewałem, ten wasz baron był potulny jak baranek. Powiedział mi wszystko, co chciałem usłyszeć. Jak mówiłem, potrafię być niezwykle przekonujący.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Dziś przyszedłem tu sam, nie ma moich ludzi za tymi drzwiami. Co do diabła?!";
			link.l1 = "Mam złe przeczucia co do tego. Julianne, schowaj się za mną, teraz! Baronecie, czy wysłannicy Korony walczą tak dobrze, jak mówią?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Na pewno wiesz, jak posługiwać się szablą, Kapitanie! Uh, szczerze mówiąc, to nie był spacer po parku. Kim do diabła byli ci ludzie?!";
			link.l1 = "Powinniśmy zapytać ich przyjaciół - słyszę więcej kroków. Chciałbym, żeby to byli strażnicy...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "Niewiarygodne! Myślisz, że drań ośmielił się to wszystko zrobić?! Zapłaci, przysięgam!";
			link.l1 = "Odetchnij. Barbazon wywinie się od wszelkich oskarżeń. Powie ci, że to był zwykły napad drobnych włamywaczy na bogaty dom. Poza tym, to przeklęty pirat, czemu miałby się przejmować władzami! Niemniej jednak, teraz jestem pewien, że udało ci się dowiedzieć czegoś naprawdę wartościowego. Proszę cię, abyś podzielił się ze mną tą wiedzą.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "Nie mogę naprawdę odmówić, prawda? W przeciwnym razie kolejna próba może się powieść? Dobrze, będę udawał, że nie zauważyłem oznak zagrożenia w twoim tonie. Powiedzmy, że oddaję ci przysługę. Jacques Dobroduszny nie sprzedał pereł twojemu szlachetnemu bękartowi. On kupował. To wszystko.";
			link.l1 = "Więc to de Chievous przechwycił Reginę? Łajdak z niego, ale trudno uwierzyć, że zniżyłby się do zwykłego piractwa.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "Trudno byłoby nazwać Reginę zwykłą zdobyczą pirata, Kapitanie. Zakładamy, że miała przynajmniej pół tuzina czarnych pereł. Nawet jedna czarna perła jest bezcenna. Koniecznie muszę spotkać się z tym panem de Chievous za wszelką cenę.";
			link.l1 = "Mogę tu trochę pomóc, Monseniour. Ale pozwól mi najpierw coś wyjaśnić. Nie wydawało mi się, że przejmuję się naszyjnikiem pani Botot, więc perły nie są powodem, dla którego tu jesteś. Co jeszcze miała Regina na pokładzie?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Bardzo dobrze, rozumiem, że będę musiał powiedzieć ci więcej, biorąc pod uwagę... okoliczności. Widzisz, ładunek nie jest tak ważny w porównaniu do samego statku. Kurierowy brygantyna Regina została przypisana do portu w San Jose, Trinidad. Jej kapitan zbierał informacje i wykonywał pewne... zlecenia dla nas. Ostatnim jego zleceniem było przewiezienie łupów, które nasi korsarze zdołali wydobyć z hiszpańskich operacji perłowych. Zajęło nam trzy lata wysiłków, aby zdobyć ten trop. Czarne perły są z pewnością znaczące, ale utrata Reginy jest fatalna. To nie był wypadek, ktoś, kto wiedział o jej perłach, musiał też wiedzieć o reszcie.";
			link.l1 = "Świetnie, więc to jednak sprawa służb wywiadowczych! Obawiasz się, że cała sieć szpiegowska, którą zbudowałeś, jest w niebezpieczeństwie? Teraz widzę pełen zakres twoich kłopotów.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = " Słyszałeś kiedyś o Johnie Thurloe? On jest szefem wywiadu Korony. Pewnego dnia będę w Londynie, osobiście zdawał mu relację o losie Reginy. Muszę znaleźć, skąd pochodzi przeciek i... zająć się źródłem. Poza tym, jest jeszcze ten tajemniczy kapitan Moreno, o którym mówisz. Jeśli Hiszpanie odkryli naszą sieć szpiegowską w koloniach, lata ciężkiej i mozolnej pracy pójdą na marne!";
			link.l1 = "Wiesz, to wszystko zaczyna mieć sens, jeśli spojrzeć na to w szerszej perspektywie. Zaczynam myśleć, że ktoś z hiszpańskim akcentem powiedział de Chievousowi o Reginie i czarnych perłach.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "Myślimy podobnie. Nie ma lepszego sposobu na wykorzystanie zdemaskowanej siatki szpiegowskiej. Incydent dyplomatyczny z udziałem człowieka o tak wysokiej pozycji... Taki incydent może poważnie zaszkodzić relacjom między Brytanią a Francją, wystarczy podsunąć odpowiednie tropy i poczekać na międzynarodowy skandal. Być może nawet ten trop o czarnych perłach został nam celowo podany.";
			link.l1 = "Te przeklęte Kastylijczyki, prawda? Więc co robimy z de Chievous?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "Jeśli mam być szczery, nie mam pojęcia. Jeśli to hiszpańska prowokacja, rozsądnie byłoby ją po prostu zignorować. Ale muszę się dowiedzieć, jak dowiedział się o Reginie i jak źle to wygląda dla naszej sieci w hiszpańskich koloniach. Zawdzięczam ci także moje życie i zamierzam się odwdzięczyć.";
			link.l1 = "Uczciwość za uczciwość, Baronecie. Przydałaby mi się każda pomoc, jaką mogę dostać. Jestem już na tyle zdesperowany, że rozważam porwanie markizy.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "Zdajecie sobie sprawę, że to właśnie tak de Chievous zacierają swoje ślady? Będzie tak łatwo zrzucić całą tę kabałę na was, łącznie z zaginięciem Reginy. Dlatego proponuję co następuje. Markiza Botot powiedziała mi, że de Chievous nie weźmie udziału w wymianie i bezpiecznie pozostanie w Basse-Terre. Albo zdał sobie sprawę, w jaką kabałę się wpakował, albo zaczyna coś podejrzewać. Będzie ostrożny jak mysz kuchenna. Dlatego pójdę z wami na Dominikę.";
			link.l1 = "Ale jego więzień jest moim priorytetem, nie mogę ryzykować jej życia! Ona jest zakładniczką czekającą na wymianę!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "Nie martw się - przycisnę Jacquesa Dille do Parkuet i zdobędę nakaz aresztowania statku de Chievousa. Wątpię, by jego ludzie w pełni zdawali sobie sprawę z sytuacji, w jakiej się znajdują, inaczej byliby bardziej ostrożni z tymi perłami. Popłyniemy do nich szalupą i wręczymy im nakaz bezpośrednio.";
			link.l1 = "Tak, pamiętam twój dar perswazji, Monseniour, ale to ryzyko. I to spore.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Masz całkowitą rację, ale będziesz musiał to zaakceptować, jeśli chcesz mojej pomocy. Gdy skończymy na Dominice, udam się do Basse-Terre i zażądam od gubernatora de Lyon wydania twojego przeciwnika. Moje uprawnienia na to pozwalają. Nie możemy pozwolić, by de Chievous się wymknął.";
			link.l1 = "Naprawdę jesteś na to gotów, Monsieur? To może wywołać wojnę, prawda?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Założę się, że nigdy na to nie pozwolą. To zdecydowanie nie przejdzie, skoro już znamy prawdę. Polityka to dziwka, Kapitanie. Obiecuję, że wprowadzę de Chievousa do brytyjskich lochów, specjalnie dla ciebie. To brzmi jak całkiem dobre rozwiązanie, które nawet jego ojciec uznałby za rozsądną cenę.";
			link.l1 = "Nie mogę powiedzieć, że podoba mi się twój plan, ale nie widzę innego.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Zapewniam cię, że damy radę. Powinienem teraz iść zobaczyć się z gubernatorem i wydać rozkazy moim ludziom. Jeśli zobaczysz markizę, powiedz jej, że może zatrzymać perłę jako wyraz wdzięczności za jej pomoc w śledztwie.";
			link.l1 = "Dzięki, Baronecie. Do zobaczenia na moim statku, wkrótce wypływamy.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Baron Cortney, do usług. Na mocy władzy przyznanej mi przez Imperium Brytyjskie z pełnym wsparciem jej zaufanego sojusznika Francji, wasza jednostka jest niniejszym zatrzymana. Oto dokumenty, proszę się z nimi zapoznać i powiedzieć swoim ludziom, aby trzymali się z dala od broni. Jesteście zatrzymani, ale jeszcze nie aresztowani. Jeśli nie popełnicie żadnych głupstw, zostaniecie uwolnieni w pierwszym porcie.";
			link.l1 = "Baronecie, muszę odzyskać mojego... mojego oficera!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Nie martw się, Kapitanie, odprowadzę ją na twój statek. Proszę, wróć teraz do szalupy. Przejmę dowództwo nad tym statkiem i popłynę do Basse-Terre. Śmiało możesz nas opuścić, jeśli nie zamierzasz osobiście drwić ze swojego arcywroga. Proszę tylko, byś przekazał mi kilku swoich ludzi, aby pomogli nam dotrzeć do Gwadelupy.";
			link.l1 = "Bardzo dobrze, monsieur. Wolałbym nie. Przekaż mu moje najgorsze pozdrowienia. Do widzenia i jeszcze raz dziękuję!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, cieszę się, że cię widzę. Miałem nadzieję na twój powrót, ale nigdy tak naprawdę w to nie wierzyłem.";
			link.l1 = "Podobnie, baroneto. Czy przyszedłeś złożyć wizytę markizie? Gdzie ona jest, tak przy okazji?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = " Wciąż tego nie pojmujesz, prawda? Uciekła. Również, Angerran de Chievous przesyła ci szczere przeprosiny. Udało mi się go przekonać, że nigdy nie byłeś częścią tej gry, a tylko kolejną jej ofiarą. Tak jak i on. Dobry człowiek nie fatygował się, by napisać, ale jest głęboko zasmucony tym, jak się sprawy potoczyły.";
			link.l1 = "Przepraszam głęboko, nieprawdaż?! O czym mówisz, Monseniorze?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Ty i ja, przeoczyliśmy najważniejszą rzecz. Jak on dowiedział się o perłach? Kto zaprosił tego hiszpańskiego kapitana do tego właśnie domu? Kto mógłby skłonić drania do pościgu za takim łupem?";
			link.l1 = "Jesteś poważny? To niemożliwe...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Zdecydowanie może. Markiza odegrała swoją rolę perfekcyjnie, prawie udało jej się doprowadzić wszystko do końca. Jednak dzięki naszemu śledztwu, podszedłem do de Chievousa nie jako do złodzieja i pirata, ale jako do ofiary oszustwa, którą jest. Szybko odkrył, w co go wciągnęła, jednak nie miał dowodów i postanowił działać na własną rękę. Wiesz, co stało się potem.";
			link.l1 = "Chcesz powiedzieć, że to wszystko zostało zaaranżowane przez Markizę? De Chievous połknął to jak nieostrożne niemowlę!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Dokładnie. Pasja to bardzo niebezpieczna rzecz, Charles! Pamiętasz tę noc, kiedy grałeś w karty w tym samym domu? Angerran miał zamiar wydusić dowody, których potrzebował od markizy, zdobywając nad nią protektorat. Tak, oszukiwał, ale był zdesperowany po latach beznadziejnej pasji zakończonej najbardziej niszczycielską zdradą! Ale ty wkroczyłeś, nazwałeś się jej obrońcą i odniosłeś sukces w tej roli. De Chievous myślał, że ty i ona jesteście jednego zdania. Ukradł statek, który przegrał z tobą, aby uniemożliwić ci zdobycie jego dzienników. Wykorzystał twojego oficera, aby próbować napuścić ją na ciebie - swoich śmiertelnych wrogów, jak sądził.";
			link.l1 = "Brak mi słów!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Teraz wiesz, jak to jest, Charles! Markiza jest sprytna, oszałamiająco piękna i nie mniej niebezpieczna. Nie wiem, jak długo manipulowała najlepszymi ludźmi Nowej Francji. Powiedziałbym, że przez wiele lat. W każdym razie to już cię nie dotyczy. Miło było cię znów spotkać, ale mam więcej pokoi do przewrócenia do góry nogami, to duży dom. Pewnie nic nie znajdziemy, ale musimy przynajmniej spróbować\nJeszcze jedna rzecz, zanim się rozstaniemy. Tutaj, weź to. Pamiątka, żeby pamiętać. Może podarujesz to swojej damie, gdy będziesz gotowy. Masz dużo szczęścia, wiesz. Zwłaszcza w porównaniu do de Chievousa, biedny drań!";
			link.l1 = "Masz rację, jestem. Żegnaj i powodzenia w poszukiwaniach, baronecie!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Jaki piękny dzień mamy dzisiaj, co Kapitanie? Słyszałem o twoich wyczynach, lecz nigdy nie wyobrażałem sobie, że jesteś banalnym piratem. Co za bezczelność - przybyć do St. Jones po tym, co zrobiłeś!";
			link.l1 = "Może i jestem piratem, to prawda, panie, ale czy wyglądam na idiotę? Dlaczego, do diabła, miałbym tu przychodzić po splądrowaniu Merkurego i zabraniu hiszpańskich pereł?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Przyznaję, to jedyny powód, dlaczego teraz prowadzisz tę rozmowę zamiast kołysać się na stryczku. Widzisz, jest mały szczegół, który ukryliśmy w tej sprawie. I nie mówię o perle, którą znaleźliśmy przy tobie. Chodzi o nazwę brygantyny.";
			link.l1 = "Znaczenie?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "„Brygantyna kurierska, Regina, była przypisana do portu San Jose przez ostatnie dwa lata. Jej kapitan zbierał dla nas informacje i wykonywał... zadania wszelkiego rodzaju. Oficjalnie poszukujemy jej pod pretekstem zagubionej poczty dyplomatycznej, którą przewoziła. Przyznaję, że to niezbyt wyszukana sztuczka. Niemniej jednak, nie mógłbyś poznać prawdziwej nazwy statku bez dokładnego przeszukania kabiny kapitana.”";
			link.l1 = "Byłem ślepy, ale teraz widzę. Proszę, wysłuchaj mnie, panie, wyjaśnię!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Wytęż się bardziej, kapitanie. Twoje życie wisi na włosku.";
			link.l1 = "Nie mam nic wspólnego z tą szpiegowską historią! Hiszpanie też nie. Twoja sieć jest bezpieczna, nie martw się. Jednak miałeś wyciek i ktoś to wykorzystał. A potem, wdałem się w sprzeczkę z tym kimś. Znalazłem dowody na jego zaangażowanie w interesy z Merkurym i chciałem je wykorzystać, by go pokonać.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "Niech Bóg będzie świadkiem, myślałem, że to zwykły akt piractwa, nawet nie przyszło mi do głowy, że ma z tym coś wspólnego wywiad Korony! Wszystko, co mam, to ta perła, ale doskonale wiem, kiedy i gdzie można znaleźć więcej.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "Słyszałeś kiedyś o Johnie Thurloe? On jest szefem wywiadu Korony. Pewnego dnia będę w Londynie, osobiście zdawał mu raport o losach Merkurego. Dlatego podaj mi imię tego mizernego przeciwnika, którego masz.";
			link.l1 = "Angerran de Chievous, hrabia de Levy Vantadur bękart. Przypuszczam, że uważał Merkurego za jedynie transportowiec łupów korsarzy. Mógł wiedzieć o perłach, lecz nie miał pojęcia o powiązaniach z brytyjskim wywiadem.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "Nie zawodzisz, Kapitanie, to ci przyznam! Co za wybór rozrywek i wrogów! Bardzo dobrze. Jakie inne dowody oprócz perły posiadasz?";
			link.l1 = "De Chievous ma fregatę. Kiedyś do mnie należała... tylko przez jedną noc, ale udało mi się czegoś dowiedzieć. Jest niezwykle pedantycznym człowiekiem, dowiesz się wszystkiego o jego ataku na Mercury z jego dziennika. Jestem pewien, że wciąż posiada część nagrody. Może nawet więcej czarnych pereł, jeśli było ich więcej niż jedna.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Więcej niż jedną, możesz na to liczyć. Nigdy nie narażylibyśmy Reginy dla partii zwykłych pereł. Mam nadzieję, że zdajesz sobie sprawę, iż absolutnie muszę porozmawiać z Monseniour de Chievous. Nie obchodzi mnie perły, ale muszę dowiedzieć się więcej o przecieku. Moi przełożeni mnie zakopią, jeśli nie dostarczę im pełnego obrazu.";
			link.l1 = "Cieszę się, że mogę zaaranżować dla ciebie spotkanie, ale musimy się pospieszyć! W tej chwili fregata de Chievousa zmierza do Gwadelupy, gdzie jej właściciel obecnie przebywa pod ochroną lokalnego gubernatora. Jestem pewien, że jest świadomy tego, co zrobił i ucieknie z Nowego Świata jak najszybciej.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "To są bardzo poważne oskarżenia przeciwko bardzo poważnym ludziom, Kapitanie. Czy zdajesz sobie sprawę, jaka... burza gówna może się z tego wywiązać? Napad zbójecki na statek pod banderą sojusznika? To może poważnie skomplikować relacje między dwoma wielkimi narodami. Trudno mi sobie wyobrazić, jak głęboko udało mu się zajść ci za skórę, by skłonić cię do ryzykowania tak wiele.";
			link.l1 = "Zabrał mi coś, milordzie. Coś, co cenię najbardziej. Bardziej niż własne życie. Muszę to naprawić. Jeśli to prowadzi do wojny, to będę służył mojemu krajowi pod jego flagą. Niemniej jednak, de Chievous dostanie to, na co zasługuje, i to tylko on jest winien!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Czy ktoś ci kiedyś powiedział, że jesteś człowiekiem wielkiego niebezpieczeństwa, kapitanie? Gotów wywołać wojnę na połowie globu, aby osiągnąć swój cel? Bardzo dobrze, zróbmy to po twojemu. Pojadę z tobą do Basse-Terre. Nie mogę zrezygnować z takiego tropu. Wyślę pisarza, żeby zapisał twoje dowody, podczas gdy będę przygotowywać mój statek.";
			link.l1 = "Dziękuję, panie. Ale nie mamy tu czasu do stracenia, ostrzegam cię!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Kapitanie de Maure, zdążymy na czas, nie wątpię w ciebie. Jednakże, jeśli ta przygoda się nie uda... rozumiesz mnie? Nie mogę ci obiecać nawet porządnego grobu.";
			link.l1 = "Tak, panie. Rozumiem cię całkowicie.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "Kości zostały rzucone, Kapitanie. Zażądałem spotkania z Angerranem de Chievous. Jego fregata zostanie przeszukana natychmiast po przybyciu. Francois de Lyon ma swoje wątpliwości, ale pieczęcie na moich dokumentach powstrzymują go na razie. Proszę cię, abyś został w mieście, dopóki sytuacja się nie rozwiąże.";
			link.l1 = "Oczywiście, panie, rozumiem.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "W takim razie mam nadzieję, że to również zrozumiesz. Oddaj swój miecz dżentelmenom tam i podążaj za nimi, abym był pewien, że dotrzymasz obietnicy.";
			link.l1 = "Niewiarygodne... panie Cortney, czy mówisz poważnie?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Śmiertelnie poważnie. Wciąż jesteś jednym z moich głównych podejrzanych i wypuszczenie cię w tych okolicznościach byłoby dla mnie bardzo głupim posunięciem. Przeproszę cię w każdy sposób, jaki uznam za stosowny, kiedy i jeśli twoje słowa okażą się prawdziwe.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Witaj, monsieur de Maure. Czy ruszamy?";
			link.l1 = "Z przyjemnością, jakie są zasady? Szczerze mówiąc, byłem zbyt zajęty jedzeniem i chyba źle usłyszałem warunki.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "Zasady są proste. 10 000 pesos za kartę, gramy, dopóki jeden z nas się nie podda. Nie przyjmujemy paragonów ani kredytów.";
			link.l1 = "Działa dla mnie. Zróbmy to, pułkowniku.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Do diabła! Nigdy więcej! Bardzo dobrze, monsieur de Maure, powodzenia w następnej rundzie.";
				link.l1 = "Z przyjemnością, pułkowniku. Żegnaj.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Walczyłeś dzielnie, ale Lady Fortuna miała własny plan. Żegnaj, monsieur de Maure. Dziękuję za grę.";
					link.l1 = "Tak, chyba przeceniłem swoje siły w tym. Żegnaj, pułkowniku.";
				}
				else
				{
					dialog.text = "Zdecydowałeś się zrezygnować z dalszej gry, przyznając tym samym porażkę! Walczyłeś chwalebnie, ale fortuna zadecydowała inaczej. Żegnaj, monsieur de Maure, dziękuję za grę.";
					link.l1 = "Tak, chyba przeceniłem swoje siły w tym. Żegnaj, pułkowniku.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Kapitanie Charles de Maure, co za cholernie zaskoczenie!";
					link.l1 = "Kapitanie. Moreno, psia jego mać! Co cię tu sprowadza?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Kapitán Charles de Maure, moja przyjemność.";
						link.l1 = "Czy my się już spotkaliśmy, monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Kapitanie Charles de Maure, moja przyjemność.";
						link.l1 = "Czyśmy się już spotkali, monsieur... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Kapitan Charles de Maure, moja przyjemność.";
				link.l1 = "Czy już się spotkaliśmy, monsieur... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "To długa historia. Jak zawsze, kapitanie. Widzę w twoich oczach, że masz pytania. Po prostu zachowaj to w tajemnicy i udawaj, że drwisz z prostego żeglarza.";
			link.l1 = "Tak, ten szykowny strój dobrze na tobie leży, mój prosty przyjacielu. Powiedziałbym, że wiesz, jak go nosić.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Jedynie przy rzadkich okazjach, na szczęście. Dziś jest taki dzień. Zagrajmy, Kapitanie. Ludzie patrzą, nie wypada kazać im czekać.";
			link.l1 = "Zgoda, pogadamy później. Umowa... kapitanie Moreno, jeśli łaska.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Trochę cię znam, ale to nie ma znaczenia. Rozdaj karty, Kapitanie de Maure, ludzie chcą widowiska.";
			link.l1 = "Ciekawe. Zwłaszcza twój hiszpański akcent w połączeniu z zasługami madame Botot dla ciebie. Dobrze. Morze przeciwko morzu, zróbmy to!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Pamiętam cię dobrze. Kiedy ty i mój były kapitan przebiliście moich chłopaków w Le Francois. Drań dostał, na co zasłużył, nie bez twojej pomocy, jak pamiętam. Ale nie czekaj na moje podziękowania, zabiłeś Franza Garke'a i nie wybaczę ci tego.";
			link.l1 = "Kwatermistrz Portugalczyka? Krwawy Don, prawda? Ta noc staje się coraz lepsza. Do dzieła!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "Zdecydowałeś się zrezygnować z dalszej gry i tym samym przyznałeś się do porażki! Rozumiem, że Pani Fortuna miała swoje zdanie. Żegnaj, Kapitanie.";
				link.l1 = "Podobnie, monsieur Moreno. Dziękuję za grę.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Domyślam się, że Lady Fortuna miała swoje zdanie. Żegnaj, Kapitanie, być może spotkamy się ponownie.";
					link.l1 = "Podobnie, monsieur Moreno. Dziękuję za grę.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Rozumiem, że Pani Fortuna miała swoje zdanie. Żegnaj, Kapitanie, być może spotkamy się ponownie w innych okolicznościach, he-he.";
						link.l1 = "Nie mogę się doczekać, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "To wszystko. Fortuna zdecydowała, Kapitanie. Żegnaj.";
						link.l1 = "Żegnaj, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "To wszystko. Fortuna zadecydowała, kapitanie. Żegnaj.";
				link.l1 = "Żegnaj, monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "Tak miło cię widzieć, panie kapitanie de Maure! Szczerze mówiąc, spodziewałem się zobaczyć cokolwiek, w tym pełną eskortę strażników, ale nie ciebie.";
			link.l1 = "Monseniour Moreno, czy masz jakieś problemy z miejscowymi urzędnikami? Miło cię również widzieć, ha-ha!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Mówię, nie można odmówić zaproszenia naszych gospodyń. Przynajmniej, nie tego rodzaju zaproszenia. No dalej, Charles, przestań z tą komedią. Markiza zadbała, bym wiedział, że zna moją prawdziwą tożsamość.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Madame, jesteś urocza! Ten nowy przyjaciel już raz próbował mnie wydać. Właściwie to nie poszło zbyt dobrze, a tak naprawdę uratował mi skórę tyle razy, że straciłem rachubę. W każdym razie teraz jestem mu coś winien, więc nie ma potrzeby grozić, nie martw się.";
			link.l1 = "Doceniam to, Bartholomew. Angerran de Chievous zapędził mnie w bardzo niewygodną sytuację i absolutnie muszę go pokonać. Od tego zależy życie... kogoś bardzo mi drogiego. Uwierz mi, tym razem nic mnie nie powstrzyma.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Dosyć, kapitanie, jesteśmy przyjaciółmi, prawda? Pamiętasz ten wyścig przez połowę Archipelagu? Takie coś wiele dla mnie znaczy. Zrobię wszystko, co w mojej mocy, aby ci pomóc. Słyszałeś kiedyś o Merkurym?";
			link.l1 = "Co to jest? Statek?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Brytyjski brygantyna, by być precyzyjnym. Jej rolą było przewożenie łupów kaprów pułkownika D'Oyley'a, którzy splądrowali hiszpańskie operacje perłowe na Zachodnim Wybrzeżu. Te, które czasami wyławiają legendarne czarne perły, słyszałeś o tym? Jeśli moje źródło informacji jest wiarygodne, kilka takich pereł zostało przechowanych na Mercury. Miesiąc temu urządziłem zasadzkę między Martyniką a Gwadelupą, czekając na tych zacnych panów. Ale było to na próżno! Spędziliśmy tydzień na morzu, aż musieliśmy uznać to za niepowodzenie.";
			link.l1 = "Cóż, więc twoje źródło nie było jednak wiarygodne i nie zdobyłeś żadnej nagrody dla siebie. Co ma z tym wspólnego de Chievous?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Miałem takie same myśli, dopóki nie dowiedziałem się, że Mercury nigdy nie pojawiła się na Antigui. Wyobraź sobie moje zdziwienie, kiedy zobaczyli ją w pobliżu Curacao, a nie mogła przejść obok mnie w pobliżu Martyniki. Brytyjczycy są wściekli! Wyobraź sobie, że przegapiłeś taką zdobycz i wszystko! W każdym razie, zaciekawiłem się i zacząłem dochodzenie, o tym specjalnym kimś, kto zepsuł zabawę wszystkim. Takiego łupu nie można sprzedać szybko, więc udałem się do Le Francois, aby znaleźć tego drania i odzyskać to, co mi się należało.";
			link.l1 = "Twoja opowieść brzmi znajomo. Słyszałeś kiedyś o słowie 'Karma'? Z pewnością wiesz, jak znaleźć kłopoty na swojej drodze. Ale wciąż nie widzę, jak to może być dla mnie użyteczne?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "Nie spiesz się, Kapitanie, zaraz opowiem Ci najlepszą część mojej opowieści. Ten nieumyta, dobrze ubrana przyjaciel twoja - jego chłopcy zostawili zauważalny ślad wielkich pereł w lokalnych sklepach. Dumę hiszpańskich operacji perłowych, które zmarnowali w wielkich ilościach.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "Słyszałeś, kapitanie?";
			link.l1 = "Jak myślisz, czy de Chievous kupił skradzione perły od Jacquesa Życzliwego i jego chłopców? Obawiam się, że to... nie wystarczy.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "Tak jest, kapitanie. On nie kupował, on sprzedawał! Rozmawiałem o tym z Barbazonem i potwierdził, że kupił znaczną partię doskonałych pereł od jakiegoś swojego partnera. Później wysłał je do Europy. Mamy też tę czarną perłę w naszyjniku i fakt, że statek de Chievous przeszedł naprawy. Robotnicy powiedzieli mi, że jego fregata miała dziury po dwunastofuntowych kulach. Kto przy zdrowych zmysłach zaatakowałby fregatę takimi dziećmi?";
			link.l1 = "Brzmi jak nasza brygantyna! Poza tym, pamiętam, jak de Chievous chwalił się, jak szybka jest jego fregata. Ale dlaczego to szaleństwo? Jesteśmy w pokoju z Brytanią, dlaczego ryzykować tak wiele i po co? Czarne perły są niezwykle rzadkie, to prawda, ale nie są niedostępne.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "I tu popełnił błąd! Brytyjczycy już rozpoczęli oficjalne śledztwo w sprawie zniknięcia Mercury, choć nazywają ją zaginionym statkiem kurierskim z jakąś ważną dokumentacją na pokładzie. Wszelkie wskazówki będą hojnie nagradzane, a wszyscy odpowiedzialni zostaną surowo ukarani. Najlepsze jest to, że wysłali specjalnego szlachcica do Antigui, który teraz niestrudzenie grzebie w tej sprawie. Nie pamiętam jego imienia, równie wymyślnego jak jego zarozumiała twarz, ale cieszę się, że nie ściga mnie!";
			link.l1 = "To dopiero coś! Wygląda na to, że bardzo pragną tych czarnych pereł. Zastanawiam się, ile z nich mieli na Mercury i jak cała ta wiedza może mi się przydać?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Jak to, ta szumowina również cię wkurzyła, markizo? Przebiegły drań! Jestem z tobą, Kapitanie de Maure! Nikt nie waży się ukraść łupu Bartolomeo Portugalczyka!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "Potrzebuję porządnego trunku po całej tej gadce. Markizo, skoro teraz jesteśmy przyjaciółmi...";
			link.l1 = "Nie sądzę, żeby mieli rum w tym domu, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Tak, jasne, po prostu zwróć uwagę brytyjskiego śledczego na jego fregatę! Jeśli to jest nasz plan, to nie rozpoznaję naszego starego, dobrego kapitana de Maure!";
			link.l1 = "Zaśmiejesz się, ale taki jest plan. Będę potrzebował pomocy was obojga. Pani - zostaniesz więźniem pirata, którego wynająłem - Bartholomew, to twoja część.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "I o tej mojej nikczemności również! Bartolomeo Portugalczyk nigdy nie porwał kobiety!";
			link.l1 = "I nie zrobi tego, ale tak to będzie wyglądać dla ludzi de Chievous. Poza tym, nie ma potrzeby mówić im swojego imienia. Zabierz naszą damę na pokład i spotkaj się z fregatą Angerrana w pobliżu Cape Scott Head. Wymień Juliannę na mojego oficera i wracaj na Martynikę. Potem czekaj na markiza i mnie.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "To wszystko było bardzo fascynujące i w ogóle, jesteś prawdziwym kawalerem, Charles. Ale jak, do cholery, mamy ją zwrócić po wymianie?";
			link.l1 = "Ja się tym zajmę. Nie mamy dużo czasu, więc się rozdzielmy. Ty i markiza pojedziecie na Dominikę, podczas gdy ja popędzę do St. Jones. Znajdę pułkownika D'Oyley'a lub tego brytyjskiego śledczego i powiem mu, kto jest odpowiedzialny za zniknięcie Mercury'ego.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Zastanawiałeś się nad burzą gówna, która z pewnością nastąpi po takim incydencie, kapitanie? W tej chwili Antigua to gniazdo szerszeni, a ty każesz mi rzucić w nie kamieniem. Pamiętam wojny, które zaczynały się z mniejszych powodów!";
			link.l1 = "Jeden problem na raz... Sprowadzę ją z powrotem za wszelką cenę! Niech de Levy Vantadur posprząta cały bałagan sam, jeśli jest tak potężny, jak mówią! A de Chievous będzie miał trudności z wyjaśnieniem, jak Madame Botot znalazła się na pokładzie jego statku.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Gotowa? Na modlitwę! Markizo, jesteś gotowa do porwania?";
			}
			else
			{
				dialog.text = "Gotowa? Na modlitwie! Markizo, ile czasu zajmie ci się spakowanie?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", monsieur de Maure. Nazywam się "+GetFullName(npchar)+", a to jest "+GetFullName(characterFromId("GG_SecundantGG_2"))+" Jego Ekscelencja poprosił nas, abyśmy byli świadkami twojego pojedynku z monsieur de Chievous.";
			link.l1 = "Dobry wieczór, panowie. Mam nadzieję, że wszystko pójdzie gładko i nikt nie zginie tej nocy. Ale bądźcie gotowi na wszystko. Ten 'dżentelmen' może okazać się rozczarowaniem.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "Wasz niepokój jest bezpodstawny. Zgodnie z ustalonymi warunkami tego pojedynku, w żadnym wypadku sekundanci nie mogą się wtrącać. Ale dziękuję za ostrzeżenie nas mimo to. Twój przeciwnik przybył. Powodzenia, Kapitanie. Jego Ekscelencja prosił, bym przekazał, że będzie modlił się o twoją... rozwagę.";
			link.l1 = "Jestem pewien, że to mi bardzo pomoże. Nieważne, zaczynajmy.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Kapitanie, mamy problem. Nasz statek... cóż, już go nie ma.";
			link.l1 = "Czekaj, co?! Jak, kto? Cały oddział wartowników miał być przy niej stacjonowany, więc o czym do cholery mówisz?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nie, Kapitanie, nie statek. Ona błyszczy. Fregata, którą wygrałeś wczoraj, więc ona też jest teraz nasza, tak? Wysłaliśmy tam tylko załogę nagrodową z tuzinem ludzi. Powiedziała, że to wystarczy.";
			link.l1 = "Po prostu, kurwa, przestań i powiedz mi dokładnie, co się stało od początku!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nie mam pojęcia, kapitanie. Fregata odpłynęła w porannej mgle. Straż zauważyła jej brak kilka godzin później, gdy mgły już nie było.";
			link.l1 = "To po prostu niemożliwe! Nigdy by mi tego nie zrobiła! Chociaż... cholera, ostatnio się pokłóciliśmy. Czy mogła...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Obawiam się, że jest jeszcze gorzej, kapitanie. Rybacy znaleźli dwóch naszych chłopców z załogi nagrodowej wcześnie rano. Obaj martwi, z poderżniętymi gardłami.";
			link.l1 = "Cholerna zmora! De Chievous! Ukradł swój statek, gdy byłem zajęty markizą! Mam nadzieję, że żyje... Jeśli straci choć jeden włos, to ja...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Dasz chłopcom rozkaz, by się szykowali, kapitanie? Możemy wypłynąć za dwie godziny, wszyscy są na skraju wytrzymałości cały ranek, zwłaszcza twój zastępca, ledwo udało nam się powstrzymać go przed wypłynięciem za nimi.";
			link.l1 = "Za wcześnie na to. Muszę... to dobrze przemyśleć i z kimś porozmawiać. Tak! Przygotować statek! Chcę, by wszyscy byli gotowi, wypłyniemy, jak tylko wrócę.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Kapitanie de Maure, co się dzieje? Czy ktoś zaatakował madame?";
			link.l1 = "Nie powinieneś był tu przychodzić. Cóż, Bóg mi świadkiem, nie chciałem tego.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Mości panie, prawie straciliśmy nadzieję, że tu dotrzesz. Widzę markizę Botot na twojej szalupie. Nawet nie będę pytał, jak do tego doszło. Twoja towarzyszka czeka na ciebie. Jest cała i zdrowa, zabierz ją i wynoś się stąd do diabła.";
			link.l1 = "Jeśli tknąłeś ją choć palcem, rozerwę twój stary kocioł na strzępy!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Co za niespodziewany pokaz troski. Nie martw się, traktowano ją jak królową więźniów. Twoje groźby mnie nie dotyczą. A tak przy okazji, Chevalier de Chievous przesyła pozdrowienia.";
			link.l1 = "Pchaj go i jego pozdrowienia. Gdzie jest mój... oficer? Rozpocznijmy wymianę.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monsieur, prawie straciliśmy nadzieję na pańskie przybycie. Pańska towarzyszka czeka na pana. Jest cała i zdrowa... czekaj, kim do diabła jest ten? Gdzie jest markiza?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "Twój miecz, panie. I bez sztuczek, moi chłopcy są teraz trochę nerwowi. Nie chcesz dostać kulki, prawda?";
			link.l1 = "Na serio? Dobrze, weź to, ale bądź ostrożny, kosztuje więcej niż twoje koszary. Żądam spotkania z baronetem Cortneyem, Wasza Ekscelencjo!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Nie martw się, jestem pewien, że znajdzie trochę czasu, by cię odwiedzić.";
			link.l1 = "Kiedy próbujesz pomóc komuś...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "Też mi się to nie podoba, Monseniorze. Niestety, ten bezczelny Brytyjczyk ma taką władzę, że nawet Monsenior de Lyon niewiele może na to poradzić. Przepraszam, Kapitanie, proszę oddać swoją szablę.";
			link.l1 = "Mam nadzieję, że Monsieur de Chievous nie będzie dzielił ze mną tej samej celi. Chodźmy, panowie, jestem śmiertelnie zmęczony. W końcu trochę snu.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "Nie chcę wyjść na nieuprzejmego, monsieur, ale nie mam teraz czasu na rozmowy, widzisz, co się dzieje. Nie chcę niczego przegapić!";
			link.l1 = "Jak sobie życzysz, monsieur.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "Ten wieczór przejdzie do historii, czuję to! Ludzie będą o nim rozmawiać od tutaj aż po Wersal! Moja Marianne będzie zachwycona i będzie chciała znać wszystkie szczegóły. Proszę, monsieur, odsuń się, zasłaniasz mi widok.";
			link.l1 = "Już wychodzę, monsieur, baw się dobrze na przedstawieniu, i przekaż pozdrowienia niezapomnianej Marianne... kimkolwiek ona jest.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Hah! Więc oto monsieur de Maure! Przepraszam... kapitan Charles de Maure! Dołącz do mnie, proszę, oto wspaniały wybór win z dobrej Starej Europy. Czym chcesz rozpocząć wieczór: jest nowość - Cabernet Sauvignon z wybrzeży naszej ukochanej Girondy, czy nieprzemijająca klasyka - włoskie Sangiovese?";
			link.l1 = "Dziękuję, monsieur, napiję się z tobą, ale trochę później.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "O, kapitanie de Maure! Chciałbyś jeszcze trochę wina... czk? Spójrz, co właśnie nam podano - Syrah z roku 1643, prosto z północnych wzgórz Doliny Rodanu. To jest, do diabła, prawdziwa perła! A rok był wspaniały pod każdym względem, mówię ci... samo zwycięstwo nad Hiszpanami pod Przylądkiem Gat jest tego warte! A tak przy okazji... dlaczego wszyscy się tak krzątają, wiesz? Czy ktoś się źle czuje? No cóż - jakby nie było, zdrowie...";
			link.l1 = "Cóż, przynajmniej ktoś oddaje hołd smakołykom. Au Revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "O, kapitanie Charles de Maure, słyszałem o tobie, jak wszyscy w tym mieście! pozwól, że się przedstawię - "+GetFullName(npchar)+", spotkanie z tobą to wielki zaszczyt, wierz mi! Czy naprawdę jesteś w dobrych stosunkach z naszym gubernatorem? Możesz nas przedstawić? Chcę wyrazić mój najgłębszy szacunek dla niego i...";
			link.l1 = "Może później. Dobranoc, monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, widziałeś to?! Nasz szanowny gubernator i monsieur de Chievous osobiście - myślałem, że zabiją się tu nawzajem! Wspaniałe! Markiza Botot przeszła dziś samą siebie - to wszystko jest tak cholernie ekscytujące! Niecierpliwie czekam na dalszy ciąg. A tak przy okazji, może teraz jest odpowiedni moment? Obiecałeś mnie przedstawić... ";
			link.l1 = "Nie pamiętam, żebym coś obiecał. Przykro mi, ale muszę iść.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Panie de Maure, wreszcie dotarłeś do salonu błyskotliwej madame Botot! Już kilkakrotnie krążyły pogłoski, że chciała cię zobaczyć. Udało się ocenić jej 'uczniów'? Tak, gwiazdy jak markiza nie są dla zwykłych śmiertelników jak ty i ja. Ale uwierz mi: te damy to prawdziwe dzieła sztuki. Może mniej zdumiewające, ale jednak - jak Michał Anioł i, powiedzmy, Tycjan.";
			link.l1 = "Interesujące porównanie, monsieur. Cóż, zostawiam cię, byś mógł cieszyć się nocą....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "Nie, tutaj zawsze jest zabawnie, ale teraz powietrze wyraźnie pachnie luksusowym skandalem, czujesz to? Lady Jacqueline czeka na mnie na górze, ale wciąż nie mogę się oderwać od stołów do gry! Jego Lordowskość i monsieur de Chievous są godnymi przeciwnikami i są niezwykle zdeterminowani. Wydaje się, że dzisiejsze zakłady nie tylko polecą do gwiazd, ale przebiją firmament prosto do diabłów!";
			link.l1 = "Diabły są poniżej, monsieur. Muszą być anioły za firmamentem niebios.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Cóż, przynajmniej jedno miłe spotkanie! Już się poznaliśmy, kapitanie de Maure, ale trudno, byś mnie pamiętał. "+GetFullName(npchar)+" - Byłem kapitanem szóstej kompanii piechoty garnizonu, walczyłem z tobą na naszych ulicach z Hiszpanami. Prawda, dostałem kulkę w kolano i większość bitwy podziwiałem, jak ten sam burdel płonął, leżąc w rowie. Teraz tutaj - znów cywil, i znów podziwiam, ale teraz od środka.";
			link.l1 = "Miło cię poznać, monsieur. Tamten dzień był naprawdę gorący, ale przyznać trzeba, że od tamtego dnia to miejsce stało się znacząco piękniejsze!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "A jak ci się podoba atmosfera tutaj, kapitanie? Wygląda na to, że te świeckie ciule postanowiły zrobić cholerny bałagan! Ciekaw jestem, czy fotel gubernatora można obstawić jak zakład w kartach? Pamiętaj moje słowa - skończy się na stali. Szkoda, z moim kolanem takie rozrywki już nie dla mnie. Jednak gdzieś widziałem Jacqueline - jej kawaler jest poważnie zafascynowany tym, co się dzieje... Chyba pójdę i spróbuję szczęścia, póki tu wszystko jeszcze spokojne.";
			link.l1 = "Dobra decyzja, życzę ci powodzenia, monsieur. A ja muszę wrócić do... waletów.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
