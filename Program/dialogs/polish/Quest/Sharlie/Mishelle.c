// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
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
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Witaj, Charles Podróżniku! Słyszałem już wszystko o tym, jak pokonałeś tych piratów na wschodnim wybrzeżu Martyniki. Teraz jestem absolutnie pewien, że się w tobie nie pomyliłem, bracie.";
				link.l1 = "Sukinsyny złapały mnie w pułapkę. Ale nas nie docenili. Mój nawigator, moja załoga i ja wyszliśmy z tego cało. Chociaż muszę przyznać, drogi bracie, na początku... sprawy wyglądały kiepsko.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Witaj, bracie! Doceniam twój szczery zapał, by mnie stąd wyciągnąć, ale na następny krok jeszcze nie jesteś gotowy. Mój plan wymaga doświadczonego kapitana. Kontynuuj eksplorację Karaibów, zdobywaj nagrody i ucz się! Gdy będziesz gotowy, ruszymy dalej.";
						link.l1 = "Cóż, cokolwiek powiesz, bracie. To ty tu siedzisz, nie ja.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Dobrze cię widzieć, bracie. Nie zapomnij o swoich zobowiązaniach wobec innych. Jak tylko będziesz wolny, będę na ciebie czekał - mam pomysły na nasz następny krok!";
						link.l1 = "Rozumiem, bracie. Znajdę czas na swoje zobowiązania, ale wkrótce wrócę!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "Charles Nawigatorze! Słyszałem o twoich przygodach! Jesteś prawie gotowy na kolejny etap mojego planu. Wróć, gdy tylko zdobędziesz trochę więcej doświadczenia.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Witaj, bracie! Doceniam twój szczery zapał, by mnie stąd wydostać, ale jeszcze nie jesteś gotowy na kolejny krok. Mój plan wymaga doświadczonego kapitana. Kontynuuj odkrywanie Karaibów, zdobywaj nagrody i ucz się! Gdy będziesz gotowy, będziemy kontynuować.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Dobrze cię widzieć, bracie! Słyszałem, że robisz postępy! Ale jeszcze nie jesteś gotowy na kolejny krok mojego planu. Rób to, co robiłeś dotychczas i wróć do mnie, gdy będziesz gotów.";
						}
					}
					link.l1 = "Cóż, cokolwiek powiesz, bracie. To ty tu siedzisz, nie ja.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "Nie sądzę, bracie. Może ty już się przyzwyczaiłeś do tej klatki, ale ja nie zamierzam tu długo zostawać - nasz ojciec nie będzie czekał wiecznie. Wypluj to.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "Dzień dobry, Charles. Twój widok raduje me serce: zdecydowanie zmieniasz się na lepsze.";
					link.l1 = "Czyżby? A jak to sobie wyobrażasz?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "Rozumiem. Widzę, że masz dla mnie wieści, Charles! Cóż, co nowego? Mam nadzieję, że nic ponurego?";
				link.l1 = "Posłuchałem rady, którą mi ostatnio dałeś...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "W końcu jesteś tutaj... Co słychać, drogi bracie?";
				link.l1 = "Posłuchałem rady, którą mi dałeś ostatnio...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Miło cię widzieć, Charles! Czy widziałeś Chevaliera de Poincy? Jak poszło wasze spotkanie?";
				link.l1 = "Tak, drogi bracie. Spotkaliśmy się. I mam dla ciebie dwie wiadomości, dobrą i złą. Zacznę od dobrej. Uregulowałem twój dług wobec de Poincy. Zła wiadomość jest taka, że nie wypuści cię, dopóki nie spełnię twojej obietnicy uporządkowania spraw z jakimś heretykiem...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "Jak ci poszło w La Vega, bracie?";
				link.l1 = "Nie ma się czym chwalić, naprawdę. Tyrex to barwna postać, ale jego sposoby prowadzenia interesów po prostu nie są dla mnie.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "Jak ci poszło w La Vega, bracie? Słyszałem plotki i szczerze mówiąc, nie czuję się z nimi dobrze... Charlie Prince.";
				link.l1 = " Myślę, że wiem, o co chodziło w tych plotkach. Ale to już przeszłość. Nie pracuję już z Tyreksem, ta robota stała się zbyt brudna jak na mój gust.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Cóż, witaj... Korsarzu Charlie Książę. Powiedz mi, Charles, jak mogłeś tak nisko upaść? Nie mogę w to uwierzyć. Mój brat, który skrzywił się, gdy wspomniałem o plądrowaniu hiszpańskiego galeonu handlowego, jest teraz jednym z najbardziej poszukiwanych i niebezpiecznych piratów w tym regionie! Nawet ja, siedząc po uszy w gównie, czerwienię się za każdym razem, gdy słyszę o twojej niesławie. Przekląłem dzień, kiedy wysłałem cię do La Vega. Co za wstyd! Francuski szlachcic dołączył do piratów i w tak krótkim czasie stał się najgorszym z nich wszystkich! I co teraz, bracie? Szukasz wakatu na stanowisku barona piratów?";
				link.l1 = "Nie. Kończę z piractwem raz na zawsze.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "Co jeszcze, Charles? Myślę, że omówiliśmy wszystko. Czas to pieniądz, drogi bracie - pośpiesz się!";
			link.l1 = "Tak, tak, już idę...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles!.. Cieszę się, że cię widzę, bracie! Rozumiem oczywiście, że trudno ci będzie w to uwierzyć, ale jestem cholernie szczęśliwy, że tu jesteś...";
			link.l1 = "Ha! Popatrz na niego! Jest szczęśliwy! Podczas gdy ty siedziałeś na swoim wysokim koniu z 'Porządkiem', Charles był wstydem rodziny, marnym artystą, żyjącym na pieniądze kurtyzan, i dworskim 'rycerzem', co? Ale teraz, gdy twoi własni towarzysze zamknęli cię za kratami, jesteś 'szczęśliwy jak diabli', widząc swojego nic niewartego brata!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, ty...";
			link.l1 = "Jeszcze nie skończyłem! Dlaczego nic nie zgłosiłeś o sobie do Francji?! Czy został ci odebrany prawo do korespondencji?! Nasz ojciec całkowicie się rozchorował z niepokoju o ciebie! I poprosił mnie, abym przynajmniej coś dowiedział się o twoim losie!..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, w jakich słowach miałbym opowiedzieć ojcu, co się ze mną stało? Co miałbym mu napisać? Nie, bracie, niezależnie od tego, jak ciężko jest, lepiej, żeby nasz ojciec jeszcze niczego nie wiedział. I nie ma sensu pisać do ciebie - zawsze jesteś pod różnymi adresami w Paryżu... Jak mnie znalazłeś?..";
			link.l1 = "Na prośbę ojca udałem się na Maltę. Tam otrzymałem pewne informacje od twojego przyjaciela, kawalera de La Brignais. Napisał mi o twoich problemach i że prawdopodobnie jesteś gdzieś na Martynice. Następnie wróciłem do Francji i odwiedziłem ojca. A po tym wszystkim udałem się do tej dziury piekielnej w skwarze, gdzie komary dosłownie gryzą cię na śmierć...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Czy opowiedziałeś ojcu o tym wszystkim?";
			link.l1 = "Nie. A kawaler de La Brignais nie odpowiedział na jego listy, obawiając się smutnych konsekwencji... Ojciec wciąż nic nie wie o twoim losie. Postanowiłem cię odnaleźć i dotrzeć do sedna sprawy. Żebyś wiedział, przybyłem na Martynikę nie dla ciebie, lecz dla naszego biednego ojca!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Naprawdę? Charles, od kiedy troszczysz się o swoją rodzinę? Bądźmy szczerzy, bracie, każdy w Paryżu wie, kim jest twój ojciec. Możesz nosić nazwisko de Maure, ale nie chcesz, by nazwisko de Monpe zostało zhańbione.\nBo w takim przypadku nie mógłbyś używać swojego rodowodu, by opowiadać wszystkim fikcyjne historie o swoich heroicznych czynach, prawda? Drzwi najlepszych domów w Paryżu będą dla ciebie zamknięte i nie pozwolą ci zbliżyć się na milę do Luwru.\nCzy naprawdę wierzysz, że twoje kurtyzany i kochanki, których mężów robisz rogaczami, gdy oni walczą na polu bitwy za naszą ojczyznę, będą szczęśliwe, zdradzając swoich panów i władców z bratem takiego państwowego przestępcy jak ja?\nDomyślam się, że przybyłeś tutaj prosto z łóżka jakiejś zamężnej panienki, mam rację? Charles, co jest nie tak z twoją twarzą? Czy trafiłem w czuły punkt?";
			link.l1 = "Ty... Ty!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "Dobrze, bracie. Wymieniliśmy się złośliwościami, to wystarczy. Zgadzam się, że nie jestem doskonały. Ale ty też nie jesteś aniołem. Charles, to naprawdę nie jest czas na kłótnie. Oboje mamy ten sam cel, aby ocalić honor i godność rodziny Monper... niezależnie od naszych motywów. Bracie, chociaż raz w naszym życiu, zastąpmy wrogość pokojem. Zgoda?";
			link.l1 = "Spróbujmy... Ale czy możesz mi wyjaśnić, o co cię oskarżono?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Oficjalnie brzmi to jakby chodziło o wydatki pieniędzy Towarzystwa. W rzeczywistości, jest to znacznie głębsze.";
			link.l1 = "Więc przywłaszczyłeś sobie pieniądze swojej organizacji? No cóż...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "Powiedziałem ci, że to były oficjalne zarzuty. Nie wziąłem ani jednego louis d'or. Oto, jak to się stało... widzisz, nie mogę ci wszystkiego dokładnie wyjaśnić, dopóki jestem za kratami. Nie mam moralnego prawa rozpowszechniać tajemnic naszego Towarzystwa.";
			link.l1 = "Proszę, spróbuj to wyjaśnić, drogi bracie. Mam prawo wiedzieć, nie sądzisz?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = " Dobrze. Otrzymałem pieniądze na bardzo niebezpieczną i delikatną operację, która miała zmienić polityczną równowagę na Karaibach. Działałem na bezpośredni rozkaz Philippe'a de Poincy, który jest generalnym gubernatorem francuskich kolonii. Ale operacja zakończyła się niepowodzeniem mimo wszystkich moich starań.\nDe Poincy wpadł w furię, ponieważ wszystkie jego dalekosiężne plany poszły w diabły. Osobiście podpisał rozkaz mojego aresztowania i dopilnował jego wykonania. Następnie przybył tu i oświadczył, że oskarży mnie o sprzeniewierzenie i zdradę przeciwko Zakonowi, jeśli moi krewni lub ja nie zwrócimy pieniędzy wydanych na operację.";
			link.l1 = "Oto piękny klops. Gdzie są te pieniądze, które, o ile rozumiem, nasza rodzina musi zapłacić za twoje fanaberie?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "Zostało wydane na przygotowanie operacji. Łapówki, organizacja ekspedycji, zakup wszelkiego rodzaju towarów i wyposażenia. Miałem dość duże wydatki. Jak już mówiłem - nie wziąłem ani grosza.";
			link.l1 = "I jaka to suma jest żądana?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "Jeden milion.";
			link.l1 = "Cholera! Żartujesz sobie, prawda?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Czy wyglądam na kogoś w żartobliwym nastroju? Nie, drogi bracie, to jest gorzka prawda. Będziemy musieli dostarczyć de Poincy milion pesos.";
			link.l1 = "Do diabła! Nasza rodzina nie ma takich pieniędzy! Nie zdołalibyśmy zebrać takiej kwoty nawet w ciągu dwudziestu lat!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "Jeśli nie byłbym za kratami i ograniczony moimi zobowiązaniami wobec Towarzystwa, zrobiłbym to w ciągu sześciu miesięcy do roku, półtora roku najwyżej. Charles, to jest Nowy Świat. Wszystko jest tutaj inne. Zmotywowany, ambitny człowiek może tu zrobić majątek, nie poświęcając na to całego życia jak w Europie.";
			link.l1 = "Milion w pół roku?! Oszalałeś? Jeśli jesteś taki pewien, to czemu nie powiesz tego Poinciemu? Niech cię uwolni. Pokaż, na co cię stać...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Och, nie gadaj bzdur, Charles! Nie ma mowy, żeby Poincy wypuścił mnie z tej celi. Gdyby to było takie proste, nie prosiłbym cię o pomoc.";
			link.l1 = "Więc to ja muszę wymyślić, skąd wziąć pieniądze na twoją wolność?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Nie tylko moja wolność. Czy może zapomniałeś? Czy wrócimy do naszej rozmowy o pałacach, balach i seksie ze szlacheckimi dziwkami? Tak, Charles, to ty musisz to zrobić. Jeśli, oczywiście, chciałbyś nadal prowadzić swoje błyskotliwe życie w Paryżu, tak jak przedtem. Chciałbyś tego, prawda, bracie?";
			link.l1 = "Do diabła, gdzie, do cholery, mam to zdobyć?! Znasz jakieś stare lasy, gdzie zamiast liści rosną louisy d'ors?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "Cały Nowy Świat to gaj drzew pieniężnych, a ludzie są zbyt leniwi, by podnieść swoje głupie głowy i wyciągnąć ręce do gałęzi. Nie martw się, Charles, poradzisz sobie świetnie. Znam cię od dzieciństwa i nigdy nie marnowałbym czasu na przekonywanie naszego ojca, by cię tu wysłał, gdybym myślał, że jesteś głupi lub leniwy.\nPomimo twoich wad, które wcześniej wspomniałem, jesteś odważny, ambitny, bystry, język masz dobrze zawieszony i wiesz, jak posługiwać się rapierem, co jest niezwykle ważną umiejętnością tutaj...";
			link.l1 = "Dziękuję bardzo. Czy mój drogi brat naprawdę raczył mnie pochwalić? A ja myślałem, że jestem tylko żałosnym artystą, dworzaninem...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Przestań pieprzyć. Mamy umowę, czy nie?";
			link.l1 = "Przepraszam, bracie. Wyrwało mi się. Po prostu nie jestem przyzwyczajony do słyszenia takich słów od ciebie. To jakby ulicznica głosiła o ratowaniu duszy.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Przejdźmy dalej, bracie. Jak mówiłem, masz wszystko, czego potrzeba, by odnieść tu sukces. Co więcej, nie jesteś sam. Pomogę ci radą, co robić i jak to robić właściwie. Słuchaj mnie, a osiągniemy sukces. Wierz mi, nie znajdziesz kogoś, kto zastąpi moje doświadczenie. Jesteś gotów przestać gadać bzdury i wreszcie przejść do rzeczy?";
			link.l1 = "Tak, wygląda na to, że zostanę tu na jakiś czas... Dobrze. Zamieniam się w słuch, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Tak, bracie, zostaniesz tu na jakiś czas. Dobrze, że teraz to widzisz. Więc jeśli jakaś kurtyzana czeka na twój powrót w Paryżu, radzę ci o niej zapomnieć. Ale nie martw się, miejscowe dziewczyny mają swoje uroki.\nJednakże, lubią prawdziwych mężczyzn, silnych i natarczywych, nawet szorstkich. Więc jeśli zamierzasz przelecieć jakąś kolonialną dziewczynę, nie licz na poezję, dyskusje o obrazach czy spacery pod księżycem. Nie zaakceptują tego.";
			link.l1 = "Dobrze, bracie. Czy uderzył cię piorun gadulstwa? Przejdźmy do sedna. Jestem gotów wysłuchać twoich rad, ale nie twoich plugawych insynuacji.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Wspaniale. Abyś mógł odnieść jakikolwiek sukces, musisz posiadać statek. Karaiby to archipelag. Wiesz o tym, prawda? Życie jest splecione z morzem. Człowiek z własnym statkiem ma nieskończony horyzont możliwości zarobku.";
			link.l1 = "Ale ja nie jestem żeglarzem!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "W takim razie, czas się nim stać. Nie masz innego wyboru. Nie myślałeś o tym, by zostać urzędnikiem portowym lub zarejestrować się w garnizonie, prawda? Nie? W takim razie zostaniesz kapitanem.";
			link.l1 = "Co za zwrot w mojej karierze! A gdzież znajdę sobie statek?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "Na naszej lokalnej stoczni czeka doskonały lugier. Nie jest duży, ale to bardzo wygodna łódź, idealna na pierwsze kroki w świecie żeglarzy. Ten lugier został zbudowany specjalnie dla mnie. Z pomocą przyjaciół wpłaciłem zaliczkę w wysokości pięciu tysięcy pesos za ten statek. Udaj się do szkutnika i powiedz mu, że wysłał cię Michel de Monper. On zrozumie, po co tam jesteś.";
			link.l1 = "Statek kosztuje tylko pięć tysięcy? To trochę dziwne...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Bracie, słuchasz mnie? Pięć tysięcy to tylko zaliczka. Cena lugra to około dwadzieścia tysięcy pesos. Więc resztę pieniędzy będziesz musiał zarobić sam. Poza tym, będziesz potrzebował pieniędzy, by wynająć załogę i nawigatora.";
			link.l1 = "Świetnie! A jak to zdobędę?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Nic w tym dziwnego. Zarób je. Jak inaczej? Pieniądze można znaleźć za każdym krzakiem tutaj, trzeba tylko wiedzieć, gdzie szukać i nie bać się przeciwności. Przejdź się po różnych miejscach tutaj. Porozmawiaj z miejscowymi. Na pewno znajdziesz jakąś pracę. Ale bądź ostrożny, oszustów jest znacznie więcej niż uczciwych ludzi. Jeśli nie jesteś uczciwym człowiekiem, możesz spróbować ukraść coś cennego z domów.";
			link.l1 = "Ale przecież jesteśmy szlachtą, prawda?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "Tu tytuły gówno znaczą. Pracuj, walcz, kradnij jak wszyscy inni. Po zakupie łajby, najmi załogę. Na początku nie będziesz w stanie sam sterować statkiem, więc potrzebujesz nawigatora. O tym wszystkim możesz pogadać z właścicielem tawerny, on ci pomoże. I upewnij się, że się nie zgubisz, oczywiście. Gdy wypłyniesz na morze, obierz kurs prosto na Guadalupe...";
			link.l1 = "Co to jest? Miasto?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "To wyspa oddalona stąd o prawie dwa dni. Spróbuj zdobyć mapę archipelagu jak najszybciej i naucz się jej jak 'Ojcze nasz', abyś nie wyglądał na głupca przed każdym, kto potrafi odróżnić miasto od wyspy. Będziesz musiał dużo żeglować po archipelagu, więc przygotuj się z wyprzedzeniem.";
			link.l1 = "Hm. Dobrze. Więc co mam robić na tej, uh... Gwadelupie?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Znajdź tam człowieka o imieniu 'Fadey'. Ma swój własny dom niedaleko nabrzeża. Powiedz mu, że mnie znasz i poproś, aby spłacił swój dług - przegrał ze mną sporo w kartach. Pieniądze, które otrzymasz, pomogą ci stanąć na nogi. Wykorzystaj je, aby zacząć działać.";
			link.l1 = "Co masz na myśli, mówiąc, żeby zacząć działać?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "Mam na myśli wykorzystanie tych pieniędzy, aby zarobić jeszcze więcej pieniędzy i tak dalej. Na przykład poprzez handel. Wrócimy do tej rozmowy później. Teraz powinieneś zająć się statkiem, popłynąć na Gwadelupę, znaleźć tego tłustego Moskala i wydobyć z niego dług. \nNie dosłownie, oczywiście, Fadiej to bardzo szanowany człowiek na Gwadelupie i przyjaciel samego miejscowego gubernatora. Więc nie ma sensu się kłócić. Wręcz przeciwnie, spróbuj się z nim zaprzyjaźnić. Wróć do mnie, gdy tylko będziesz miał pieniądze. Zrozumiano, bracie?";
			link.l1 = "Zrozumiałem. Och, dlaczego....Co zrobiłem, aby zasłużyć na tę karę...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Nie smuć się, Charles. Zaakceptuj to jako nieuchronne zło, albo... jako coś dobrego. Później będziesz wdzięczny losowi, że twoje życie przybrało taki obrót. Ty, bracie, masz w końcu okazję zrobić coś, by udowodnić, że jesteś prawdziwym mężczyzną. Może nawet staniesz się przyzwoitym człowiekiem...";
			link.l1 = "(ROZPOCZNIJ SAMOUCZEK) Znowu te bzdury?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = " (POMIŃ SAMOUCZEK) Bracie, nie mam na to czasu. Chcę pominąć nudną część i od razu wypłynąć na pełne morze. Im szybciej będę miał statek, tym szybciej wyciągnę cię z tej dziury. Czy wolisz tu zostać dłużej?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "Nie, nie. Nie zrozum tego źle... Dobrze, Charles, nie trać czasu. Wiesz, co robić. Będę czekał na ciebie wracającego z Gwadelupy jako kapitan własnego statku z pieniędzmi Fadeja. Powodzenia, bracie. Liczę na ciebie.";
			link.l1 = "Spróbuję cię nie zawieść. Dobrze, Michel. Do następnego razu!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh! Ta 'nudna część' może pewnego dnia uratować ci życie... Nieważne. Jest łatwy sposób, aby teraz zdobyć pieniądze.\nIdź do lokalnego kościoła i porozmawiaj z opatem Benoit. To stary przyjaciel naszego ojca. Opowiedz mu o sytuacji, padnij na kolana i błagaj, aby pożyczył ci wystarczającą ilość monet na zakup statku.";
			link.l1 = "Teraz znacznie lepiej! Udaję się do opata.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(START TUTORIAL) Czy chcesz, żebym zaczął od zwiększenia twoich długów do jeszcze wyższych poziomów? Myślisz, że jestem idiotą, bracie? Widzę, że w tym nie możesz mi w ogóle pomóc. Wszystko więc spada na mnie.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Whoa! Wygląda na to, że się nie pomyliłem co do ciebie, bracie. Nie mogę się doczekać twojego powrotu z Gwadelupy jako kapitan własnego statku z pieniędzmi Fadeya. Powodzenia!";
			link.l1 = "Do zobaczenia. Baw się tu dobrze.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Chcesz powiedzieć, że to było przerażające? Nie napinaj się, bracie. Wszystko jest w porządku. Ja też nie czułem się jak bohater podczas mojej pierwszej bitwy morskiej. Bzdura. Za miesiąc lub dwa takie spotkania będą wyglądały jak coś zupełnie zwyczajnego... Odwiedziłeś Fadeya?";
			link.l1 = "Mam... Ale z takim sukcesem... Po co się w ogóle fatygowałem?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Dlaczego tak jest?";
			link.l1 = "Ponieważ jest na dnie. Niedawno go obrabowano i ma własne problemy finansowe. W zamian zaoferował mi sztylet ze swojej kolekcji. Powiedział, że jest cenny i że jego wartość przewyższa kwotę całego długu. Więc wziąłem go...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey? Na skałach? Problemy z pieniędzmi? Ha-ha-ha! Rozbawiłeś mnie, drogi bracie! Ten cholerny Moskal przejrzał cię na wylot i od razu rozpoznał cię jako nowicjusza i... ah, ten łajdak! Pokaż mi sztylet, który starzec dał ci w zamian za swój dług.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Oto i masz...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "Nie mam tego przy sobie. Na pierwszy rzut oka to tylko zwykły sztylet. Fadey powiedział mi, że jest zaczarowany przez indiańskiego szamana i nazywa się Pazur Wodza.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Cóż, zobaczmy... Bóg osądzi tego tłuściocha. Takie śmieci, Charles, możesz kupić w każdym lokalnym sklepie. Oszukał cię, korzystając z twojego braku doświadczenia... Proszę, weź ten kawałek stali z powrotem. Zachowaj go jako pamiątkę. Możesz powiesić go nad łóżkiem w swojej kajucie.";
			link.l1 = "Skurwiel! O, kto by się przejmował... Wrócę do niego na Gwadelupę i porządnie potrząsnę tym tłustym palantem!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Zaczarowany przez szamana? Pazur Wodza? Tak... wszystko jasne. Bóg osądzi tego tłuściutkiego niedźwiedzia. Taki złom, Charles, mógłbyś kupić w każdym lokalnym sklepie. Nabrał cię, wykorzystując twój brak doświadczenia... Próbował opowiadać mi jakieś bajki, a ja szybko sprowadziłem go na ziemię. Możesz więc powiesić ten pazur w swojej kajucie nad łóżkiem jako pamiątkę... Jeśli jeszcze nie wyrzuciłeś go do śmieci.";
			link.l1 = "Skurwysyn! Ach, kto by się przejmował... Wrócę, by zobaczyć go na Gwadelupie i potrząsnąć tym tłustym gorącym draniem!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Spokojnie, drogi bracie, zrelaksuj się. Nie ma potrzeby, chyba że chcesz spędzić kilka miesięcy w celi więziennej w Basse-Terre. Czy zapomniałeś, co ci powiedziałem? Ten puchaty niedźwiedź to przyjaciel Claude'a Francois de Lyon, gubernatora Gwadelupy. Jak tylko stąd wyjdę, porozmawiam z nim... od serca. On nigdzie się nie wybiera.";
			link.l1 = "Dobrze. Lepiej się z nim zajmij... Wygląda na to, że zostanę bez obiecanych początkowych funduszy?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Wydaje się, że tak, Charles. Ale trzymaj głowę wysoko. Ten, kto ma statek i głowę na karku, nie może popełnić błędu na Karaibach. A ty masz oba, prawda?";
			link.l1 = "Cóż insynuujesz? Schrzaniłem z tym sztyletem, więc co powinienem...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Spokojnie, drogi bracie! Czemu nagle jesteś taki nerwowy? Zachowaj spokój, będziesz żył dłużej. Niczego nie sugeruję. Nawet nie miałem takich myśli!";
			link.l1 = "Przepraszam, Michel. Po prostu jestem trochę... no, spróbuj mnie też zrozumieć!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "Rozumiem. I naprawdę chcę ci pomóc! Więc słuchaj uważnie. Musisz zdobyć trochę doświadczenia i przynajmniej zaoszczędzić trochę pieniędzy, zanim zajmiesz się poważniejszymi sprawami. Porywanie się na przygody bez odpowiedniego przygotowania to czyste samobójstwo. Nie chcę, żeby to miejsce cię jeszcze zmiażdżyło.";
			link.l1 = "Jakże inspirujące. O jakich przygodach się rozwodzisz, Michel? Z jakiegoś powodu zgubiłem wątek twojego wywodu.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Bracie, pozwól, że przypomnę ci, że ja, a mówiąc precyzyjniej, my, jesteśmy winni de Poincy'emu milion pesos. Naprawdę sądzisz, że możesz je zarobić uczciwie? Oczywiście, możesz tyle zarobić na handlu, to możliwe, jeśli los ci sprzyja, ale handel na Karaibach również nie jest spokojnym zajęciem. \nPrzygody znajdą cię same, nawet jeśli nie chcesz w nich uczestniczyć, pytanie brzmi - czy będziesz na nie gotów, gdy nadejdzie moment? Lepiej uderzyć pierwszy. Si vis pacem, para bellum, Charles...";
			link.l1 = "Znowu te wymyślne słowa? Mów po francusku, błagam cię...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "To łacina, drogi bracie. Powiedziałem: 'Chcesz pokoju, szykuj się do wojny'. Weź tę frazę jako mentalność przywódcy do działania. Możesz ją zapisać w swoim dzienniku i czytać co rano po modlitwie. Jest wiele, czego musisz się nauczyć i dużo, co jeszcze musisz pojąć...";
			link.l1 = "Dobrze, wystarczy. Zmęczyłem się twoimi naukowymi wywodami. Przejdźmy do sedna.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "Jestem konkretny, po prostu jeszcze nie nadążasz. Dobrze. Najpierw musisz zapoznać się z archipelagiem i przyzwyczaić do nowego życia jako kapitan statku. Będziesz musiał ciężko pracować, aby zapewnić sobie dobrobyt i wynagrodzenie dla swojej załogi. Istnieje wiele sposobów na zarabianie monet.\nZabieranie ładunków i pasażerów na pokład to najprostsze. Kupcy w sklepach mogą dać ci umowy na przewóz ładunków, a pasażerowie sami zwrócą się do ciebie na ulicy. Powinieneś również rozważyć sprawdzenie biur portowych, posiadanie lugra lub jakiejkolwiek szybkiej łodzi pozwoli ci zarobić dobre pieniądze na pracy kuriera.\nKapitanowie portów dostarczą ci bardzo opłacalne umowy na przewóz ładunków, gdy zdobędziesz większy statek. Rozmawiaj z ludźmi, nie chwal się swoim rodowodem, bądź przyjazny, a wszystko pójdzie jak należy. Odwiedzaj gubernatorów kolonii, często oferują dobrze płatną pracę.\nMożesz spróbować handlu, ale w takim przypadku powinieneś zatrudnić przyzwoitego kwatermistrza. Uważaj na morzu, unikaj hiszpańskich eskadr wojskowych i okrętów wojennych. Jeśli napotkasz pojedynczego hiszpańskiego kupca lub niechroniony konwój - możesz spróbować ich przechwycić.";
			link.l1 = "Co?! Michel, czy straciłem słuch? Sugerujesz, żebym zajął się życiem pirata? Ty, duma Towarzystwa, sługa Boga i Trójcy, proponujesz mi taki styl życia?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "O, Charles... Radzę ci pozbyć się swojej wybredności raz na zawsze, tutaj nie jest to doceniane. A co do Zakonu... nie bądź naiwny, bracie. Być może w Europie Luwr i Escorial są w jakimś rodzaju pokoju, ale tutaj jest wojna. Każdy hiszpański korsarz nie zawaha się splądrować twojego statku i powiesić ciebie i załogę do wyschnięcia na rei.\nDlatego nikt nie obwini cię za splądrowanie handlowego statku wrogiego narodu, zapewniam cię. A z listem kaperskim otrzymasz nawet oficjalne wsparcie od władz...";
			link.l1 = "Zaczynam rozumieć zasady twojego życia. Tak samo jak rozumiem metody, dzięki którym najwyraźniej mógłbyś 'zarobić' milion w pół roku.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "A te metody będziesz musiał wykorzystać, Charles. W końcu są one wspierane przez działające władze otwarcie lub za zamkniętymi drzwiami. Nawet jeśli trzymasz się handlu, pewnego dnia będziesz zmuszony walczyć z piratami lub hiszpańskimi najeźdźcami, bo dla nich jesteś łupem.\nW twoim najlepszym interesie jest zapomnieć o swoich dotychczasowych poglądach na życie. Uwierz mi, bracie, możesz zrobić wiele rzeczy nie tylko nie tracąc twarzy, ale także zyskać przychylność władz i miłość ludu.";
			link.l1 = "Nie przestajesz mnie zaskakiwać, Michel. Teraz mówisz mi, żebym został piratem. Co dalej?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Nie dramatyzuj tego, Charles. To naprawdę proste: polować albo być upolowanym. To cała filozofia. Ja wolę to pierwsze i chciałbym, żebyś poszedł za moim przykładem. I nie mówię ci, żebyś stał się piratem, ale żebyś zaangażował się w działania wojskowe przeciwko wrogiej nacji i tylko wtedy, gdy jest ku temu dobry powód.";
			link.l1 = "Świadczenie, masz na myśli?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "Widzisz, jednak rozumiesz, bracie. Ale dość słów. Czas się sprawdzić. Przyjdź do mnie tylko wtedy, gdy będziesz gotowy. Zarób przyzwoite pieniądze, zdobądź lepszy statek, poznaj archipelag i doskonal swoje umiejętności.\nAle pamiętaj, jeśli spędzisz następne kilka miesięcy w tawernach i burdelach, nie ucząc się niczego pożytecznego w tym czasie... wtedy nawet nie wracaj. Czy jesteśmy jasni, Charles?";
			link.l1 = "Nie martw się. Nie przybyłem tu dla rozrywki... Co będzie potem?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Później powiem ci, co zrobić dalej. Już opracowałem plan. Czeka cię świetlana przyszłość, Charles, jeśli dokładnie będziesz przestrzegał moich rad i zaleceń.";
			link.l1 = "Wolę moją skromną przeszłość od takiej jasnej, wielkiej przyszłości...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Zaufaj mi, bracie, będziesz śmiał się z twojej bezwartościowej przeszłości i dziękował losowi za to, że cię od niej uratował. Bądź optymistyczny i pozytywny. Pokochasz to życie. Zobaczysz.\nAch, jeszcze jedno: odwiedź naszego wspólnego przyjaciela Fadeya i poproś go o znalezienie ci pracy. Niedźwiedź ma dobre kontakty, jestem pewien, że coś ci znajdzie. Nie zwlekaj, bo możesz przegapić okazję. I proszę, nie zawiedź mnie.";
			link.l1 = "Nauki moralne znowu... Panie, kiedy to się skończy? Dobrze, Michale... Czy mogę już iść?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Poczekaj. Jeszcze kilka taktycznych porad. Jeśli zadrzesz z jakimś narodem i staniesz się wyjętym spod prawa, odwiedź miejscowy kościół i porozmawiaj z opatem Benoit. Powiedz mu, że ja cię przysłałem. Ma on kontakty zarówno w społeczeństwie papistycznym, jak i kalwińskim, i nie raz mi pomógł w takich sprawach. Ale pamiętaj, że to ani łatwe, ani tanie, więc staraj się unikać wrogów.\nPoczekaj, jeszcze jedna rzecz! Jesteśmy szlachtą, ale głupotą byłoby mieć awersję do rzemiosła własnymi rękami, zwłaszcza tutaj. Możesz stworzyć wiele użytecznych przedmiotów, pod warunkiem, że masz potrzebne narzędzia i komponenty... Powiedz mi, bracie, jak ładujesz którąkolwiek ze swoich pistoletów?";
			link.l1 = "Hm. Jak zwykle, kula i zawias prochu strzelniczego.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha! Nie spodziewałem się usłyszeć niczego innego.";
			link.l1 = "Znasz inny sposób, drogi bracie?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Oczywiście. Ale niewielu się tym zajmuje z powodu ignorancji i zwykłego lenistwa. Poświęcając parę godzin, możesz zrobić papierowe łuski z prochu i kul. Ich użycie skraca czas przeładowania broni o połowę. Imponujące?";
			link.l1 = "Hm.  Sądzę, że tak.  To interesujące.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Weź te instrukcje do tworzenia papierowych powłok, przestudiuj je w wolnym czasie i nie bądź zbyt leniwy, by zastosować swoją nową wiedzę\Zaczekaj, bracie. Nie zapomnij wpaść do naszego drogiego gubernatora.";
			link.l1 = "Czy jest jakaś okazja?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "Zawsze dobrze jest utrzymywać kontakt z gubernatorami, zwłaszcza jeśli trzymają twoich krewnych w więzieniu na swoich wyspach.";
			link.l1 = "Opowiedz mi o nim.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Nie każdy potrafi utrzymać tron Martyniki. Interesy Zakonu, Korony, piratów... a szlachcic nie powinien zapominać o swoich własnych interesach. Gdyby Parquet nie był tak rozwiązły i skłonny do grzechu, mógłby nawet sprawić, że Poincy traktowałby go poważnie.";
			link.l1 = "Jakiż pożytek mógłby mieć ze mnie?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "Urzędnicy zawsze mają pracę dla wolnych kapitanów. Płacą skąpo, co prawda, i tylko gdy chodzi o interesy publiczne, a nie osobiste. W każdym razie, nie ma lepszego sposobu na Karaibach, by podnieść honor i poprawić stosunki narodowe, niż pracując dla gubernatorów. Wykorzystaj moment, zwłaszcza że Parquet ma teraz pewne kłopoty. Jakie to kłopoty?";
			link.l1 = "Jakie kłopoty?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "Przykro mi, bracie. Chodzi o interesy Zakonu. Powiem tylko, że nie jesteśmy jedynymi, którzy potrzebują szybkich sposobów na zdobycie bogactwa.";
			link.l1 = "Znowu mówisz zagadkami... Cóż, wpadnę, kiedy będę miał czas.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Idź teraz. Powodzenia, bracie!";
			link.l1 = "Dziękuję... Do zobaczenia, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			TakeNItems(pchar, "bullet", 5);
			TakeNItems(pchar, "gunpowder", 5);
			DialogExit();
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "trial";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Trial = "begin"; // старт промежуточной линейки
			SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 24, false); // таймер
			AddMapQuestMarkCity("Baster", false);
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddQuestRecord("Sharlie", "19");
			// открываем все острова
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
			}
			DeleteAttribute(pchar, "questTemp.Sharlie.Lock"); //снимаем блокировку
			LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // откроем склад магазина
			sld = characterFromId("Benua");
			sld.quest.help = "true";
			npchar.greeting = "mishelle_3";
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000;
			// Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
			pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
			// Sinistra - миниквест "Делюк"
			PChar.quest.Del_Alonso.win_condition.l1 = "location";
			PChar.quest.Del_Alonso.win_condition.l1.location = "FortFrance_town";
			PChar.quest.Del_Alonso.win_condition = "Del_Alonso";
			// при достижении уровня даём флаг на квест "Голландский Гамбит"
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.value = 9;
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_9.function = "Sharlie_GambitStage_level_9";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.value = 12;
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_12.function = "Sharlie_GambitStage_level_12";
			//маркер на контрабандиста по квесту "Деньги на деревьях"
			AddLandQuestMark(characterFromId("FortFrance_Smuggler"), "questmarkmain");
			PChar.quest.MOT_UbratMarku.win_condition.l1 = "MapEnter";
			PChar.quest.MOT_UbratMarku.win_condition = "MOT_UbratMarku";
			// Sinistra - Старт квеста "Травля крысы"
			pchar.questTemp.TK_TravlyaKrys = true;
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			SetTimerCondition("TK_Timer", 0, 0, 30, false);
			//маркер на торговца БасТера по квесту "Бесчестный конкурент"
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "gambitA":
			dialog.text = "Miej to po swojemu. Wierzę w ciebie, bracie. Kiedy teraz na ciebie patrzę, po prostu wiem, że zmieniasz się na lepsze.";
			link.l1 = "Nie mów. Jak to?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "Widzę to, drogi bracie. Widzę twój chód i wyraz twarzy. Wreszcie maska zarozumiałego młodzieńca, która dosłownie doprowadzała mnie do szaleństwa, spłynęła z ciebie. Twoje nowe życie wyraźnie ci przysłużyło.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Nie mogę pojąć, bracie, co myśleć o twoich słowach, czy to pochwały, czy obelgi. Ale powiem ci prawdę: nie interesuje mnie, co o mnie myślisz z tamtej strony. Zebrałem milion, który jest potrzebny, aby spłacić twój dług, więc wkrótce będziesz wolny. Gdzie mogę znaleźć de Poincy?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "Nie mogę zrozumieć, bracie, co z twoich słów wynika, czy to pochwały, czy obelgi. Ale powiem ci prawdę: nie interesuje mnie, co o mnie myślisz stamtąd. Mam morze, nie stertę, spraw do załatwienia i nie mam czasu na spory z tobą tutaj i na żonglowanie słowami. Masz coś istotnego do powiedzenia? Jeśli nie, to ruszam w drogę...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "Zdołałeś zebrać milion? Dobra robota, Charles, po prostu nieskazitelnie! Ale Philippe de Poincy, niestety, nie jest już w swojej rezydencji, wyjechał w sprawach Towarzystwa na tajną ekspedycję. Więc będziesz musiał trochę poczekać, zanim go odwiedzisz.";
			link.l1 = "Pierd*l się i swoje tajne sprawy! Myślałem, że skończę z tym wszystkim i wrócę do domu, a teraz...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "A teraz otworzyłeś sobie możliwość zarobienia znacznie więcej pieniędzy i nie tylko to. Bracie, fakt, że zgromadziłeś kwotę wymaganą przez starego lisa, jest niesamowity, ale nie byłbym tak pewny siebie i spokojny... De Poincy to dość śliski węgorz, a wykazał niemałe zainteresowanie twoją skromną osobą, i...";
			link.l1 = "A teraz boisz się, że milion nie wystarczy dla niego?! Czy może coś pominąłeś ostatnim razem?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "Nie boję się niczego, ale muszę cię ostrzec, że Poincy nie jest prostym człowiekiem. Pod jego nieobecność masz okazję zbudować sobie pewien prestiż, abyś mógł z nim rozmawiać jak równy z równym, a nie jak pan i sługa. Dlatego usilnie zachęcam cię do podążania za moim planem, który przedstawię ci teraz.";
			link.l1 = "Dobrze. Nie ma sensu płakać nad rozlanym mlekiem. Zostanę w tej dziurze jeszcze trochę. De Poincy nie będzie żeglować wiecznie. Wprowadź mnie w szczegóły swojego planu.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "O! Godna pochwały odpowiedź. Cieszę się, Charles, że stałeś się mężczyzną. Jednakże, nie bądź tak surowy wobec swego brata. Przyznaję, że mam coś do powiedzenia. Czekałem z niecierpliwością na nasze ponowne spotkanie i już opracowałem plan, co zrobisz dalej.";
			link.l1 = "Miło. Zatem wprowadź mnie w szczegóły.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Posłuchaj. Jasne, pieniądze odgrywają dużą rolę na Karaibach, tak samo jak wszędzie indziej, ale pieniądze nie mogą rozwiązać wszystkiego. Człowiek sukcesu musi mieć nie tylko ciężki mieszek, ale także rozległe i różnorodne kontakty, i to nie z żebrakami, ale z ludźmi, którzy coś znaczą na tym świecie.\nNie ma znaczenia, jakiej są narodowości czy stanu. Kontakty otwierają drzwi, których samymi pieniędzmi nie da się otworzyć. Połączenie 'pieniądze plus kontakty' daje człowiekowi najcenniejszą rzecz na świecie - władzę.\nPowinieneś rozważyć nawiązanie takich kontaktów, a nie będziesz w stanie tego zrobić, wykonując prace frachtowe, handlując, zajmując się drobnym piractwem czy nawet zdobywając przychylność gubernatorów.";
			link.l1 = "Co proponujesz?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "Nie ma zbyt wielu potężnych organizacji na Karaibach. Jedną z nich jest Holenderska Kompania Zachodnioindyjska. Możesz do niej dołączyć. Ich główna siedziba znajduje się w Willemstad na Curacao. Kompania często zatrudnia kapitanów z zewnątrz i oferuje specjalne długoterminowe kontrakty tym najprzydatniejszym.\nJeśli masz szczęście, możesz tam zrobić przyzwoitą karierę. Słyszałem, że teraz mają poważne problemy - jakiś angielski korsarz podniósł broń przeciwko Kompanii i nieustannie zatapia ich statki. Nie mogą nic na niego poradzić, jest oficerem marynarki, co czyni go zbyt trudnym przeciwnikiem.\nMówią, że jest w jakiś sposób powiązany z brytyjskim wywiadem wojskowym, a to bardzo poważni ludzie. Więc może opowiedzenie się po stronie tego kapitana będzie dla ciebie jeszcze bardziej opłacalne, ale problem polega na tym, że nie znam jego imienia, wiem tylko, że jego bazą operacyjną jest Antigua.\nMożesz tam popłynąć i popytać. Słyszałem również o jakiejś dziwnej organizacji, która również bierze udział w tym angielsko-holenderskim konflikcie, ale nie wiem, po której stronie są. Wszystko, co wiem, to że ślady prowadzą na Barbados, do Bridgetown...";
			link.l1 = "Więc proponujesz, żebym zaciągnął się na służbę u Holendrów albo szukał podejrzanego kapitana lub jeszcze bardziej podejrzanej 'organizacji'?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = " Wybór należy do ciebie. W każdym razie nie będziesz miał innej możliwości, by szybko zbliżyć się do ludzi decydujących o losach innych na Karaibach i posiadających znaczną władzę. Mam nadzieję, że nie wpadło ci do głowy, iż dwa czy trzy przysługi dla gubernatora wprowadzą cię od razu do królewskiej marynarki.";
			link.l1 = "Wiesz, drogi bracie. Właściwie to nie liczyłem na karierę wojskową we francuskiej marynarce. Broń Boże, bym skończył jak ty, utknąwszy w celi za jakieś zadanie, którego nie udało mi się wykonać... Dobrze, zrozumiałem. Myślę, że znajdę Generalną Kwaterę Holenderskiej Kompanii bez większych przeszkód, ale nie mam pojęcia, jak szukać reszty stron.";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "Jeśli chodzi o angielskiego kapra, możesz popytać w St. John's na Antigui. Ktoś na pewno będzie mógł ci coś powiedzieć. Powiedz im, że szukasz pracy z angielską flotą. Co do 'trzeciej siły', możesz porozmawiać z ludźmi w Bridgetown. Ktoś tam z pewnością musi być związany z tą organizacją.";
			link.l1 = "Czy ich praca będzie przynajmniej wynagrodzona? Kompania, ten kaper... Czy wszystko to będzie tylko dla 'kontaktów'?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, zaskakujesz mnie. Holenderska Kompania Zachodnioindyjska operuje sumami, których pozazdrościłby król. Kaper, o którym ci mówiłem, złupił tyle holenderskich statków, że musi już tonąć w bogactwie. A ludzie z 'organizacji' nie mają po prostu dużo pieniędzy. Mają cholerne mnóstwo pieniędzy.\nPraca dla nich zawsze zagwarantuje ci słodki kawałek ciasta. Ludzie tacy jak oni zawsze grają na dużą skalę. A jeśli jesteś sprytny, zawsze możesz grać swoją własną grę i zarobić jeszcze więcej.";
			link.l1 = "Dobrze. Przemyślę to i zdecyduję, co będzie dla mnie najlepsze. Czy masz jakieś inne instrukcje?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Tak. Powinieneś nauczyć się korzystać z narzędzi nawigacyjnych. Niestety, wielu nawigatorów potrafi orientować się jedynie przy pomocy kompasu i gwiazd i nie potrafi oszacować współrzędnych. A to jest kluczowe.\nWięc. Użyj busoli, aby oszacować szerokość geograficzną. To dość rzadkie narzędzie i nie znajdziesz go w sklepach, ale możesz je samodzielnie stworzyć, używając dwóch powszechnych przedmiotów - kompasu i astrolabium. Oto instrukcje.\nOszacowanie długości geograficznej jest nieco bardziej skomplikowane. Będziesz potrzebować chronometru o określonej wartości. Możesz go zrobić z zwykłego chronometru okrętowego, dostosowując go za pomocą klepsydry. Problem polega na tym, że takie narzędzie działa efektywnie tylko przez miesiąc, zanim stanie się zbyt niedokładne z powodu błędów.\nChronometr zawsze wymaga resetowania. Klepsydry można kupić w biurze Holenderskiej Kompanii Zachodnioindyjskiej. Tam też kupiłem chronometry. Oto te instrukcje.";
			link.l1 = "Dziękuję. Natychmiast zabiorę się do nauki.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Postaraj się zdobyć wszystkie te narzędzia tak szybko, jak to możliwe. Wszyscy doświadczeni i szanowani kapitanowie operują szerokością i długością geograficzną. Będziesz uważany za nowicjusza w żegludze, dopóki nie zrozumiesz, co te liczby oznaczają.\nCóż, wróć, by się pochwalić, gdy tylko odniesiesz sukces w sprawach, o których niedawno rozmawialiśmy. Powodzenia, Charles!";
			link.l1 = "Dziękuję, drogi bracie. Czuję, że to na pewno się przyda!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "A czymże masz się chwalić?";
			link.l1 = "Na razie nic. Znalazłem wszystkie trzy organizacje i próbowałem z nimi współpracować, ale jak cygaro wszystko to wybuchło w dym dosłownie na pierwszym etapie. To jakby los był przeciwko mnie...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "Więc plotki są prawdziwe... Drogi bracie, los nie jest przeciwko tobie. To się nazywa tępy umysł i krzywe ręce. Rozczarowałeś mnie. Wracaj do Francji, nie masz tu już nic do roboty.";
			link.l1 = "Аle jak...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "To już nie twoja sprawa. Poradzę sobie sam. Mam innych, bardziej zdolnych ludzi, którzy pomogą mi rozwiązać mój problem. Bałem się, że zwierzanie się tobie zatrzyma mnie tu do końca moich dni. Tak czy inaczej. Wynoś się stąd, wracaj do swoich kurtyzan.";
			link.l1 = "Dobrze, idź do diabła...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "Nie mam z tobą o czym gadać. Idź.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "I? Dalejże, drogi bracie, nie odwlekaj tego. Jakie dobre wieści? Pewne plotki dotarły do mnie o twojej gorliwej pracowitości, ale chciałem usłyszeć wszystko od ciebie.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Znakomicie! Dobra robota, Charles! Nie wątpiłem w ciebie ani przez chwilę! Zajdziesz daleko, drogi bracie... Tak się angażować i nawiązywać relacje z tak ważnymi ludźmi, oczywiście, tego się nie spodziewałem. Gratulacje!";
			}
			else
			{
				dialog.text = "Nie martw się, Charles. Jeśli się nie udało, nic na to nie poradzisz. Użyjemy innych sposobów, aby osiągnąć potrzebne nam wyniki.";
			}
			link.l1 = "Co teraz robimy, Michel? Czy nadszedł czas, by odwiedzić kawalera de Poincy? Czuję się całkiem gotowy na rozmowę z nim.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Czy udało ci się już zebrać wymaganą sumę jednego miliona pesos?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Tak, obecnie posiadam wymaganą sumę.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "Nie, nie mam jeszcze takiej sumy pieniędzy.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Doskonale! W takim razie nie będę długo siedział w tej kazemacie... Udaj się do Capsterville, to na Saint Christopher, i poproś o audiencję u de Poincy. Powinien być w pałacu gubernatora, gdzie rezyduje. Poza tym, oceniaj na podstawie sytuacji i pamiętaj: Poincy jest przebiegły, bardzo przebiegły... Mam złe przeczucie, że ta cała heca nie pójdzie tak łatwo. Idź, bracie, i bądź ostrożny!";
			link.l1 = "Zachowam twoje środki ostrożności w pamięci, Michale. Nie martw się, ja też nie urodziłem się wczoraj. Ruszam do starego lisa. Do zobaczenia później!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "Nie ma sensu rozmawiać z de Poincy. Nawet cię nie wpuszczą. Zdobądź pieniądze, bracie, masz już spore doświadczenie, więc to nie będzie problem. Płyń do Capsterville na Saint Christopher, jak tylko je zdobędziesz.\nChevalier musi być w swoim pałacu gubernatora. Poproś o audiencję, a wpuszczą cię. Potem przekonaj się sam i bądź ostrożny: Poincy jest przebiegły, bardzo przebiegły... Coś mi mówi, że ta historia tak po prostu się nie skończy.";
			link.l1 = "Zapamiętam twoje przestrogi, Michel. Nie martw się, też nie urodziłem się wczoraj. Jak tylko zbiorę pieniądze, od razu pójdę do starego lisa. Do zobaczenia później!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Nom d'une pipe! Tego właśnie się obawiałem. Poincy od dawna cię ściga, Charlsie. Dlatego tak bardzo się tobą interesował! Zbudowałeś sobie niezłą reputację na Karaibach i dlatego postanowił cię wykorzystać do realizacji zadań, które poszły na marne...";
			link.l1 = "Mam wrażenie, Michel, że doskonale wiedziałeś i po prostu nie chciałeś mnie informować wcześniej. Wszystko układa się zbyt gładko... Najpierw pieniądze, teraz twoja praca... To nie dzieje się przypadkiem.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, nie szukaj tajemniczej wiadomości tam, gdzie jej nie ma. Gdybyś tylko dał Poincy pieniądze pierwszego dnia, kiedy tu przybyłeś... No cóż, powiedzmy, gdybyś je miał. Chevalier nie poprosiłby cię o nic więcej. Ale teraz, kiedy zainteresował się tobą i zobaczył, jak łatwo się tutaj osiedliłeś i co udało ci się osiągnąć, postanowił wykorzystać twoje talenty.";
			link.l1 = "Racja... bo twoje talenty już mu nie wystarczają, prawda? Merde! Dobrze. Widzę, że jestem tu w ślepej uliczce. Kim jest ten heretyk? Jak mogę go znaleźć?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Nie trzeba go szukać! Nigdy nie opuszcza Tortugi i pozostaje pod ochroną bastionu, który zbudował, oraz hord wiernych hugenotów, służących jako żołnierze w jego garnizonie. Zatem każdy żołnierz jest mu wierny. Poincy miał na myśli François Levasseura, gubernatora Tortugi. \nHiszpanie wciąż nie mogą go stamtąd wyrwać, a de Poincy naprawdę wierzył, że uda mi się to zrobić samemu, bez żadnego wsparcia marynarki, tylko dlatego, że rozpoczęcie wojny domowej byłoby złym krokiem politycznym ze względu na bliską lokalizację garnizonu Santo Domingo. \nStary łajdak zbyt martwi się o swoją nieskazitelną karierę i nadchodzącą emeryturę, by ryzykować wszystko w ten sposób. Niemniej jednak, Levasseur posunął się za daleko i stanowi zagrożenie dla korony. \nDe Poincy, który sam mianował Levasseura na jego obecną pozycję, uważa tego straszliwego hugenota za osobistego wroga i pragnie zastąpić go maltańskim kawalerem de Fontenay, moim bezpośrednim przełożonym, pod którego dowództwem przybyłem tu z Malty.";
			link.l1 = "Wspaniale! Najpierw zarób milion, potem zabij gubernatora Tortugi. Jakie będzie moje kolejne zadanie? Zorganizować spisek w Escorialu? Cholera! Nie dziwię się, że to schrzaniłeś. Zlikwidowanie gubernatora to nie to samo, co okradanie hiszpańskich kupców. Mam nadzieję, że miałeś jakiś plan, kiedy przysiągłeś wyciągnąć kasztany z ognia?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Aby być całkowicie szczerym, nie miałem żadnego planu, ponieważ i tak zamierzałem opuścić służbę i wrócić do naszego rodzinnego dworu w razie sukcesu mego ryzykownego przedsięwzięcia. Osobiście nie obchodzi mnie ani trochę problemy de Poincy'ego.\nZ pewnością stałby się dużo bardziej elastyczny, gdyby tylko zobaczył indiańskie złoto... Cóż, obecnie trzyma wszystkie atuty przeciwko nam. Myślę, że zostanę tutaj, dopóki Levasseur jest gubernatorem Tortugi.";
			link.l1 = "A dlaczego Maltańczycy dowodzeni przez de Fontenay, mając na oku fotel gubernatora, nie zaatakowaliby sami Tortugi?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Wyobraź sobie to. Zakon wypowiada wojnę Ludwikowi. Nie bądź absurdalny! Taki skandal jest nie do przyjęcia. Tylko osoba prywatna może zdobyć Tortugę. Pirat albo katolicki awanturnik jak ty.\nNastępnie może przekazać wyspę pod kontrolę nowego gubernatora, którego de Poincy wyśle. Taki akt będzie wyglądał wspaniale z punktu widzenia wielkich decydentów politycznych.";
			link.l1 = "Zatem jest sens w negocjacjach z piratami?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Problem polega na tym, że Levasseur ma autorytet wśród wielu piratów Bractwa i poza nim. Pozwala im ukrywać się za bateriami Tortugi i sprzedawać to, co splądrowali, swobodnie za część łupu.\nKiedyś dzielił się z de Poincy, ale już się nie dzieli. Statki pirackie będą chronić Tortugę i jej garnizon, co sprawia, że szturmowanie fortu jest jeszcze trudniejsze.";
			link.l1 = "Czy myślisz, że ta sprawa jest przegrana?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Zawsze jest jakieś rozwiązanie, braciszku. Po prostu nie zawsze jest widoczne na powierzchni. Nie wszyscy piraci są przychylni hugenotom z Tortugi. Znam przynajmniej dwóch wpływowych piratów, którzy uważają Levasseura za zdrajcę i szumowinę. Mówię o Stevenie Dodsonie, znanym również jako Rekin, oraz legendarnym baronie Zatoki Moskitów, Janie Svensonie.\nNie wiem, gdzie znaleźć Rekina, słyszałem plotki, że coś się stało i musiał opuścić swoją bazę na Isla Tesoro. Ale zawsze możesz znaleźć Svensona w Blueweld. Jest tam ważną postacią.";
			link.l1 = "Czy sądzisz, że ten... Svenson mi pomoże?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Zrobi to, jeśli mu pomożesz. Sprawy nie idą zbyt dobrze dla niego w tej chwili, a człowiekowi przydaliby się lojalni i utalentowani ludzie. Najpierw musisz udowodnić swoją przydatność, zanim będziecie mogli poważnie porozmawiać. Znajdziesz sposób, aby to zrobić, kiedy tam dotrzesz. Trudno mi udzielać rad stąd.\nZakładam, że postanowiłeś iść dalej, Charles, skoro nadal zadajesz pytania?";
			link.l1 = "Widzisz, Michale, właśnie oddałem kupę mojego własnego srebra de Poincy. Zebrałem je krwią, potem i łzami! Nie jestem pewien, czy ryzykowałbyś choćby jednego ludwika dla mnie, gdybym był na twoim miejscu.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Nie przerywaj mi! Byłoby głupotą wrócić do ojca z pustymi rękami. Problem wciąż nie jest rozwiązany, siedzisz za kratkami i grozi ci oskarżenie o zdradę Towarzystwa. Poincy bez wahania splamiłby nazwisko Monper, jeśli nie wykonam jego 'prośby'. Było to wypisane na jego twarzy. Wyruszam więc do Blueweld, by znaleźć sposób na podejście do Svensona. W międzyczasie pomyśl, co jeszcze 'zapomniałeś' mi powiedzieć. Na przykład, to pierwszy raz, gdy słyszę od ciebie o jakimś złocie Indian, które miałeś dostarczyć de Poincy.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Niektóre rzeczy lepiej pozostawić w ukryciu. Masz rację, nie powiedziałem ci wszystkiego, co wiem. Może pewnego dnia powiem ci więcej, ale nie wcześniej niż poradzisz sobie z Levasseurem, na razie byłaby to bezużyteczna wiedza.\nNie mam wątpliwości, że twoja poruszająca troska o mnie jest spowodowana jedynie chęcią ocalenia honoru naszej rodziny. Ratując mnie, ratujesz przede wszystkim siebie, a po drugie możliwość odwiedzania najlepszych domów w Paryżu. Czy się mylę?";
			link.l1 = "Obawiam się, że już tak nie jest, bracie. Miałeś rację. Te ostatnie miesiące spędzone na Karaibach zmieniły każdą cząstkę mnie i całe moje spojrzenie na świat. I jestem pewien, że na lepsze. Nie potrzebuję już tych paryskich salonów i pewnego dnia będę mógł się obejść bez nazwiska Monper. De Maure wcale nie jest gorsze...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "A teraz jedyna rzecz, która faktycznie mnie rani, to fakt, że twoja hańba pozostawi ślad na naszym starym ojcu. On nie zna prawdziwego status quo i tego, co się tutaj naprawdę dzieje. Ponadto, jak słusznie zauważyłeś, majątek musi być przywrócony z jego złowrogiego stanu. A milion zapłacony za twoją wolność znacząco uszczuplił moją kasę, więc z pewnością będzie wymagał uzupełnienia.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "Doskonale pojąłeś wszystkie lekcje życia, Charles. Jestem naprawdę szczęśliwy z twojego powodu. I cieszę się, że poszedłeś naprzód i przyjąłeś prośbę de Poincy'ego zamiast żeglować z powrotem do Francji. Mam nadzieję, że wszystko dobrze się dla ciebie ułoży i że będziesz w stanie zrealizować to, czego sam nie mogłem.";
			link.l1 = "Obawiam się, że nie mam wyboru. Od pierwszego dnia na Karaibach robię wszystko sam. Do zobaczenia później, Michel. Myślę, że nasze następne spotkanie będzie obejmować zlecenie na twoje uwolnienie.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Zaczekaj chwilę! Zanim udasz się do Jana Svensona, koniecznie odwiedź Marcusa Tyrexa - On jest Strażnikiem Kodu. Rządzi La Vegą na Hispanioli. Ma nieograniczoną władzę wśród piratów, a Hiszpanie boją się go na śmierć.";
			link.l1 = "Czy mógłby mi pomóc w naszej sprawie?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Wątpię. Nie potrafię naprawdę powiedzieć, po której jest stronie, najprawdopodobniej działa tylko dla siebie. Będziesz potrzebował Rekina i Svensona w każdym razie, ale w tej chwili - Tyrex jest najpotężniejszym piratem tutaj. Wybrali go na Strażnika Kodu nie bez powodu. Nie powinieneś ignorować tak ważnej postaci. Może okazać się przydatne lepiej poznać piratów, zanim spotkasz Svensona. Możesz nawet wyrobić sobie imię wśród nich...";
			link.l1 = "I znowu wracamy do pirackiej gadki. Nie ma mowy, żebym się od tego uwolnił, co? No dobrze. Złożę mu wizytę.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "Być piratem i robić z nimi interesy to zupełnie inna gra, bracie. Mam nadzieję, że dostrzeżesz różnicę. Udaj się do La Vega i poproś Tyrexa o pracę. Jeśli się nie dogadacie - olej go i wracaj do mnie.";
			link.l1 = "Bardzo dobrze, Michel. Do zobaczenia!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "Przynajmniej próbowałeś. Miałeś okazję 'zapoznać się' ze znanym pirackim baronem. Nieważne. Udaj się do Jana Svensona, on jest w Blueweld. Spróbuj uczynić go swoim sojusznikiem, albo nasze sprawy z Levasseurem przerodzą się w rozlew krwi.";
			link.l1 = "Dobrze. Już idę.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Cieszę się, że się zatrzymałeś, bracie. Kiedyś ci powiedziałem, że to zupełnie inna gra - być piratem i robić z nimi interesy. I zgubiłeś swoją drogę. Mam nadzieję, że nie popełnisz tego samego błędu z Rekinem i Svensonem. Wykonaj zadanie, ale trzymaj się od nich z daleka. Jesteś w końcu francuskim szlachcicem, więc bądź ponad nimi. Teraz idź do Jana Svensona, on jest w Blueweld. Spróbuj uczynić go swoim sojusznikiem, albo nasze interesy z Levasseurem przerodzą się w rzeź.";
			link.l1 = "Dobrze. Jestem w drodze.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "Jestem bardzo rad to słyszeć, jeśli mówisz prawdę. Ale czy naprawdę mogę zaufać słowu pirata, który pali miasta, nawet jeśli są hiszpańskie, i morduje cywilów, w tym kobiety?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Stop... Naprawdę żałuję tego, co robiłem podczas mojego czasu z Tyrexem. Widziałem piekło na własne oczy, bracie... Nie, to koniec! Skończyłem z piractwem i nie ma mowy, żebym znów postawił stopę w La Vega. Zrobię wszystko, co w mojej mocy, by przywrócić swoje dobre imię.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "Wierz lub nie. To ty siedzisz za kratkami, nie ja.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Przestań... Naprawdę żałuję obrzydliwości, które popełniłem, pracując z Tyreksem. Widziałem piekło na własne oczy, bracie! .. Nie, moja piracka przeszłość to już koniec! Nie jestem już w La Vega. Zrobię wszystko, aby przywrócić moje dobre imię.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Och, bracie... Nie gniewaj Boga... Mam nadzieję, że to nie powtórzy się z Svensonem i Sharkiem. Rób, co musisz, ale trzymaj się z dala i pamiętaj, kim są ci ludzie. Nie przystoi francuskiemu szlachcicowi stać się takim jak oni. Bądź wyżej. Teraz idź do Jana Swensona w Blueweld i spróbuj znaleźć sposób, by zbliżyć się do starego korsarza. Bez niego nie uda się rozwiązać problemu z Levasseurem bez dużego rozlewu krwi.";
			link.l1 = "Dobrze. Nie będę zwlekać.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "Musisz włożyć w to dużo wysiłku, bracie. Pamiętasz, co ci kiedyś powiedziałem? Że to zupełnie inna gra - być piratem i robić z nimi interesy. Ty... Zapomnij, mam nadzieję, że nie popełnisz tego samego błędu z Rekinem i Svensonem. Wykonaj zadanie, ale trzymaj się od nich z daleka. W końcu jesteś francuskim szlachcicem, więc bądź ponad nimi. Teraz idź do Jana Svensona, on jest w Blueweld. Spróbuj uczynić go swoim sojusznikiem, bo inaczej nasze interesy z Levasseurem zamienią się w rozlew krwi.";
			link.l1 = "Dobrze. Jestem w drodze.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Teraz nie czas na rozmowy, bracie! Wróg jest w naszym schronieniu!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "Jesteś na czas, drogi bracie! Tak się cieszę, że cię widzę! Ci przeklęci Kastylijczycy już całkowicie przejęli Saint-Pierre. Myślałem, że jesteśmy zgubieni na pewno!"+sTemp+"";
			link.l1 = "Jeszcze nie jesteśmy bezpieczni, miasto jest czyste, ale dranie siedzą z powrotem w fortecy, a tam jest ogromna eskadra prowadzona przez pancernik. Ale przynoszę ci całkiem wspaniałą wiadomość: Michel, jesteś wolny!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "Nie wierzę własnym uszom! Czy to możliwe? Wolność?!";
			link.l1 = "Levasseur nie żyje, Tortugą teraz dowodzi twój były dowódca, a stary lis Poincy usunął wszystkie swoje oskarżenia przeciwko tobie. Od teraz nic nie zagraża naszemu dobremu imieniu.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "Wątpiłem do ostatniej chwili... Zaskoczyłeś mnie, Charles, i odniósłeś sukces tam, gdzie ja poniosłem gorzki fiasko.";
			link.l1 = "Śmiałym szczęście sprzyja, bracie... Jak widzisz, teraz też znam łacinę. Gdzie jest klucz do twojej celi?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "Klucz do mojej kazamaty powinien być na biurku oficera służbowego. Poszukaj go tam. Może upadł na ziemię i gdzieś się zsunął...";
			link.l1 = "Znajdę ich i wrócę!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Wolność wreszcie! Och, jak długo na to czekałem!";
			link.l1 = "Nie możesz sobie nawet wyobrazić, jak długo czekałem na tę chwilę... Michel, czy mamy ludzi zdolnych do walki?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "Co masz na myśli, Charles?";
			link.l1 = "Groźba ze strony Hiszpanów jeszcze nie zniknęła. Chcę wyprzeć ich z fortu, a potem połączyć siły, by zaatakować eskadrę zarówno z lądu, jak i z morza! Dzięki użyciu armat z bastionu będę mógł zmierzyć się z okrętem liniowym!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "Posiadamy siłę roboczą. Duża liczba rycerzy opuściła miasto, aby chronić pałac gubernatora. Z pewnością znajdziemy kogoś w mieście... Zgromadzę wszystkich, których tylko uda mi się znaleźć. Do zobaczenia za bramami miasta!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Oto jest, bracie, nasza armia. Wszyscy ludzie, których udało mi się znaleźć. Nie za wielu, ale będziemy walczyć za naszą Ojczyznę! Wypędzimy tych cholernych intruzów z fortu! Element zaskoczenia nam pomoże - nie spodziewają się naszego ataku. Naprzód!";
			link.l1 = "Dulce et decorum est pro patria mori! Naprzód!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "Zrobione, bracie! Fort jest nasz!";
			link.l1 = "To szkoda, że otrzymał takie obrażenia w bitwie z hiszpańską eskadrą... ale wciąż jest całkiem zdolny do prowadzenia bitwy.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "Zagram swoją rolę. Załadujemy działa i zadamy wrogowi potężny cios! Ale dopiero gdy zobaczymy, że wasza eskadra nadciąga, bo inaczej okręt liniowy szybko zmiecie nas w trociny.";
			link.l1 = "Zbierz ludzi, Michel! Natychmiast wracam na brzeg!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, pamiętaj: najniebezpieczniejsza część eskadry to okręt wojenny! Spróbuj najpierw go unieszkodliwić. Skoncentrujemy również ogień na nim za pomocą pozostałości baterii fortu.";
			link.l1 = "W porządku, bracie. Być może powinienem ją pojmać.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "Patrząc na okoliczności, to nie ja powinienem cię pouczać. Teraz powinniśmy przestać marnować czas!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Chwała zwycięzcom! Gratulacje z okazji zwycięstwa, bracie! Byłeś wspaniały! Hiszpanie zostali całkowicie zniszczeni!";
			link.l1 = "Mam nadzieję, że to nauczy ich dwa razy się zastanowić, zanim zaatakują francuskie kolonie.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Powiedz mi teraz, Charles: ile jest warta twoja przeszłość... w porównaniu z tą?";
			link.l1 = "Nie przypominaj mi...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Czy pamiętasz, co ci powiedziałem podczas naszego pierwszego spotkania tutaj? 'Pokochasz to życie', właśnie to! Tak, i ogromne dzięki tobie, bracie, za twoją pomoc. Bez ciebie prawdopodobnie nigdy nie udałoby mi się uciec z tej podziemnej bazy.";
			link.l1 = "Nie ma o czym mówić, Michel. W końcu jesteś moim bratem i czułem się zobowiązany ci pomóc.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Spójrz tylko na siebie, bracie, jestem pod wrażeniem: tyle siły w oczach, pewności w ruchach, postawy w sylwetce... gdzie podział się ten kiepski artysta i błazen dworski? Rzeczywiście! Przerosłeś moje najśmielsze oczekiwania, prawdę mówiąc, nigdy nie sądziłem, że staniesz się... tym.\nTo nawet... trochę mnie przeraża. Bo nie zatrzymasz się przed niczym, by osiągnąć swój cel. Jesteś dobry, aż za dobry...";
			link.l1 = "Z jakiegoś powodu znów mam problem z zrozumieniem cię. Czy znowu jesteś ze mnie niezadowolony?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "Nie! O czym ty mówisz?... Wcale nie! Po prostu wyrażałem swoje podekscytowanie.";
			link.l1 = "Dobrze. Więc, co zrobisz dalej, bracie? Czy będziesz dalej służył Towarzystwu? A może wrócisz do naszego dziedzictwa? Tak, i prawie zapomniałem: obiecałeś mi opowiedzieć o jednej rzeczy.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "O czym dokładnie?";
			link.l1 = "O twojej służbie dla de Poincy. O pewnym indiańskim złocie, które miałeś mu dostarczyć. O wszystkim, co poprzedziło twoje uwięzienie. Jest wiele rzeczy, których mi nie powiedziałeś, Michel, pozostawiając mnie praktycznie w ciemności. Więc...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Bracie, doskonale pamiętam, co powiedziałem. Powiem ci wszystko. Ale nie w środku płonącego miasta!\nObaj mamy teraz wiele do zrobienia. Musisz zająć się swoją eskadrą, naprawić ją i przygotować statki na nowo. Ja i gubernator zorganizujemy i uspokoimy miejscowych.\nOmówimy wszystko jutro rano przy kieliszku dobrego francuskiego wina. Zaufaj mi, bracie, mam wielki plan. Naprawdę wielki. Ale nie teraz. Odwiedź opata Benoita jutro o dziewiątej rano. Spędzę noc u niego, to mój stary przyjaciel.";
			link.l1 = "Dobrze, Michel. Zatem jesteśmy umówieni. Nie mogę się doczekać naszej rozmowy jutro.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Dialog 28.";
			link.l1 = "Dobrze, Michel. Zatem ustalone. Czekam z niecierpliwością na naszą jutrzejszą rozmowę.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "Nie ma potrzeby się żegnać, Charles!";
			link.l1 = "... ";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "Znów się spotykamy, "+pchar.name+"  Mimo moich ostrzeżeń, nadal mnie szukałeś, a twoje poszukiwania zaprowadziły cię bardzo, bardzo daleko...";
			link.l1 = "Michel?... Z jakiegoś powodu nie jestem zaskoczony. Czy Miguel Dichoso powrócił do Tayasalu po kolejną kupę skarbów? Hm-hm-hm. Tak, szukałem spotkania z tobą, drogi bracie. Umierałem z chęci, by spojrzeć w twoje bezwstydne oczy. Na dodatek, twoja próba zamachu na mnie w krypcie cmentarnej była wisienką na torcie. Ale najpierw, powiedz mi, jak mam cię nazywać? Michel de Monper czy Miguel Dichoso?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "Te imiona nie mają już znaczenia, "+pchar.name+"  To wszystko już przeszłość, która wkrótce zniknie nawet z samej historii. Teraz nadszedł moment prawdy, do którego dążyłem przez długie ćwierć wieku, odkąd po raz pierwszy postawiłem stopę na lądzie...";
			link.l1 = "Co?!! To... to nie może być!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Tak, "+pchar.name+" Widzę po twojej twarzy, że rozumiesz, kim jestem, ale nie możesz w to uwierzyć. Jestem tym, z kim marzyłeś się spotkać przez ostatnie miesiące. Tym, z którym przedstawiciel twego Boga, Inkwizytor z Santiago, pobłogosławił cię do bitwy.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "Zgadzam się, "+pchar.name+", że trudno w to uwierzyć. Życie jest bardziej skomplikowane i bardziej zaskakujące niż jakakolwiek bajka...";
			link.l1 = "Byłem gotowy na wszystko, ale... mój brat!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Brat? Tylko z krwi ojca. Mamy różne matki, "+pchar.name+"  Wiedz, że moja matka była córką Kaneka, zwaną Shochikezhal. Została uprowadzona przez francuskich korsarzy pod dowództwem słynnego Nicolasa Gotiera, gdy lekkomyślnie opuściła Tayasal. Postanowili ją zniewolić. Wśród nich był człowiek o imieniu Serge Benoit.\nWstydząc się czynu swego kapitana, opuścił go, przywdział habit i teraz znasz go jako opata Benoit. Henri de Monper, nasz ojciec, był wtedy oficerem marynarki. Kupił Shochikezhal i zabrał ją do Francji, gdzie mnie urodziła. W mniej więcej tym samym czasie urodziłeś się również ty, "+pchar.name+". Twoja matka zmarła przy porodzie, a nasz ojciec ogłosił, że jego prawowita żona urodziła bliźnięta.\nShochikezhal, moja matka, została naszą mamką. Byłeś karmiony mlekiem Indianki z ludu Itza, "+pchar.name+"! Później twoja babka ze strony matki postanowiła wziąć cię na wychowanie i nadano ci imię twojej matki - de Maure.";
			link.l1 = "Jak się wszystkiego tego dowiedziałeś?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Czyżbyś nie sądził, bracie, że wiem więcej niż zwykli ludzie? Nasz ojciec także wiele mi powiedział i jestem świadomy wielu rzeczy... To właśnie, jak mówią, na mojej własnej skórze.";
			link.l1 = "Teraz wszystko jasne... A co się stało z twoją matką? Dlaczego nigdy jej nie widziałem?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "Zginęła, ratując mi życie. Nieco ponad rok po moim narodzeniu, niemal umarłem z powodu choroby. Moja matka, córka kapłana Itza, przeprowadziła dla mnie tajną magiczną ceremonię uzdrawiającą Majów. Polepszyło mi się, ale towarzyszyły jej pewne... destrukcyjne skutki uboczne w postaci grzmotów, błyskawic i tropikalnego huraganu. Shochikezhal została uznana za czarownicę, oskarżona o czary i spalona na stosie Inkwizycji...";
			link.l1 = "I stałeś się lepszy...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Poza uzdrowieniem mnie, ten rytuał dał mi również inne zdolności, a także otworzył połączenie ze światem bogów. A resztę już znasz. Jak już wiesz, poniosę światło wiedzy i doświadczenia białej rasy w przeszłość i przekażę je ludowi Majów. Historia zostanie przepisana i wy, biali, nie będziecie dominować w tym świecie. Dopilnuję tego.";
			link.l1 = "Więc całe twoje życie, nauka w najlepszej akademii morskiej, służba w armii i w Zakonie Maltańskim to w zasadzie było tylko zbieranie doświadczenia wojskowego?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Dokładnie. Gdy zdałem sobie sprawę, że wiem wystarczająco dużo, zaaranżowałem, by wysłano mnie na Karaiby. Przekonałem Kawalera de Poincy, by stworzył bazę na Martynice. Następnie musiałem dotrzeć do Tayasal. Nie było to dla mnie proste zadanie, ponieważ to fizyczne naczynie pozostaje śmiertelne, a portale na Karaibach nie działały poprawnie.";
			link.l1 = "I stałeś się Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = " Drogi bracie, otrzymałem ten przydomek na polach bitew Europy. Tam też poznałem Ramona de Mendoza y Riba. Myślisz, że życie składa się z przypadków? Nie, wcale nie, każdy przypadek to nieznana regularność. Wiele zostało zrobione dla mojego powrotu do Tayasal. Musiałem żyć dwoma życiami. Michel de Monper i Miguel Dichoso. Musiałem również upewnić się, że ludzie uwierzą, iż to różne osoby.\nMusiałem być piratem, tak jak ty, na służbie dla de Poincy, aby zdobyć jego zaufanie, względy i pieniądze. Musiałem zamordować Blaze'a Sharpa, jednego z przywódców piratów, jako przysługę dla Ramona de Mendoza, aby uzyskać żołnierzy na wyprawę.\nMusiałem kusić zarówno de Poincy, jak i de Mendoza opowieściami o skarbach Tayasal. Otrzymałem siedemset pięćdziesiąt tysięcy sztuk srebra z skarbca de Poincy i sprzedałem hiszpańską fregatę wojenną piratowi Dodsonowi. A potem nastąpiła wyprawa. Wróciłem do Tayasal tylko po to, by ponieść porażkę...";
			link.l1 = "Rozumiem... Kiedy miałeś zaledwie pięć lat i goniłeś motyle w majątku naszego ojca, wielki kapłan Kanek, przestraszony inwazją Don Alonso de Maldonado na Tayasal, bezpiecznie ukrył maskę Kulkulkana, która jest tak istotna do podróży w przeszłość... wybacz, miałem na myśli TWOJĄ maskę.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Tak, Kanek przechytrzył sam siebie. Wykonał najtrudniejszy rytuał, rytuał, którego nawet starożytni nie ośmielili się wykonać. Ukrył maskę na świeżo powstałej bezludnej wyspie i zdołał zgubić klucz do Ksocheatem - tak zwanego Strażnika Prawdy.\nMusiałem działać mądrze. Rytuał uniemożliwiał opuszczenie Karaibów każdemu statkowi, który przewoził chronione przedmioty ze skarbca Taysal, wyrzucając takie jednostki na brzegi Ksocheatem. Zamierzałem to wykorzystać. Wziąłem wystarczająco dużo skarbów, aby uspokoić Mendozę. Wziąłem też specjalny przedmiot chroniony przez rytuał.\nStatek z tym przedmiotem na pokładzie byłby skazany na dostarczenie prosto do Ksocheatem, prosto do mojej maski. Więc wypłynąłem na morze i dałem znać o sobie Mendozie.";
			link.l1 = " Więc opuściłeś Tayasal sam?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "Masz na myśli bez żołnierzy Mendozy? Oczywiście. Wszyscy Hiszpanie zostali zabici tutaj, w Tayasal. Itzas sami przynieśli skarby na brzeg, a ja powiedziałem Mendozie, że żołnierze zostali zasadzani przez ludzi Miskito. Uwierzył mi, ponieważ interesowało go tylko złoto, a nie ludzie.\nPlanowałem ustawić statek ze skarbami pod działami 'Gryffondor', ale wszystko poszło znacznie lepiej: baron postanowił wysłać skarby do Hiszpanii pod moim nadzorem. To było najlepsze możliwe rozwiązanie, musiałem tylko czekać, aż statek przekroczy niewidzialną granicę Karaibów.\nJednak okazało się, że kapitan miał inne rozkazy. Dowiedziałem się, że specjalna jednostka abordażowa miała wzniecić bunt, jak tylko dotrzemy do Oceanu Atlantyckiego, zabijając załogę i wszystkich oficerów. Kapitan miał rozkaz zwrócić złoto Indii z powrotem do Mendozy.\nTaki wspaniały przykład białej rasy, prawda, bracie? Musiałem zaryzykować, nie wiedziałem, kiedy miało nastąpić powstanie. Ale wszystko poszło zgodnie z planem: burza uderzyła nas, gdy tylko 'Santa Quiteria' dotarła na wschodnią stronę wyspy Trynidad i Tobago. Fregata została zniesiona z powrotem na Karaiby w kierunku Ksocheatem.\nPotem poniosłem największą porażkę w moim życiu - fala zmyła mnie ze statku i znalazłem się w Le Marin Cove na Martynice kilka dni później. Rybacy mnie znaleźli i zabrali do Le Francois. Ale ludzie de Poincy'ego złapali mnie, gdy dochodziłem do siebie u Cesara Craiga. 'Gryffondor' nie znalazł 'Santa Quiteria' w miejscu, które określiłem. Chevalier de Poincy wpadł w furię, gdy tylko dowiedział się, że złoto Indii zniknęło razem z pieniędzmi zabranymi ze skarbca Zakonu i jego własnymi oszczędnościami.\nKazał mnie aresztować. Nie mógł mnie jednak zabić, nie chciał. Chciał złota. Złota! Tylko tego chcą i o to dbają twoi ludzie! Zrobisz wszystko, by je zdobyć... Byłem w strasznej sytuacji: nie miałem na sobie maski i pozostawiono mnie gnijącego w celi bez ani jednej monety w kieszeniach.\nWtedy wezwałem cię. Tak-tak, drogi bracie, miałeś mnie uwolnić, abym mógł zrobić to, do czego się urodziłem. I wykonałeś niezwykłą pracę. Wydaje się, że mleko Itza, które ssałeś, dobrze ci zrobiło.";
			link.l1 = "Czymże się kierowałeś, kiedy uciekłeś z Saint-Pierre? Jaki był twój plan?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "Zawsze byłeś moim planem, bracie. Kukulcan potrafi czytać ludzkie serca. List, który zostawiłem ci u opata, miał skłonić cię do działania. Miałem rację co do ciebie. Śledziłem twoje postępy od pierwszego spotkania z inkwizytorem z Santiago. Zrobiłeś wszystko dla mnie. Stworzyłeś Strażnika Prawdy. Wyeliminowałeś konkurentów. Znalazłeś Ksocheatem.\nByłem tam, podążając za tobą. Choć nie spodziewałem się, że dostaniesz się do Tayasal. Przekroczyłeś wszystkie moje oczekiwania. I z twoją pomocą zrobię to, do czego się urodziłem. Powód, dla którego narodziłem się w śmiertelnym ciele.";
			link.l1 = "Jest tylko jeden mały haczyk w twoim rozumowaniu, drogi bracie. Nie posiadasz swojej maski i nic nie znaczysz bez niej. Ja ją mam. I nie pałam pragnieniem, by ci ją oddać. Wolałbym raczej rozwiać ją w strzępy, niż pozwolić, by trafiła w twoje ręce.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "Nie możesz zmienić tego, co jest przeznaczone przez los. Nie pozwolę ci uszkodzić mojego artefaktu. Czuję to... Jest z tobą. A ty jesteś tutaj, w mojej świątyni, w zasięgu mojej pełnej mocy! Nigdy nie opuścisz tego miejsca. Nadszedł czas na twój ostateczny test, drogi bracie, by zobaczyć, ile jesteś wart w walce przeciw Kukulcanowi!";
			link.l1 = "Przypuszczam, że twoje śmiertelne ciało wciąż może krwawić!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha! Czuję się źle z twojego powodu, Charles. To naprawdę smutne. Ale zasługujesz na szansę walki z Bogiem. Nawet jeśli to bezcelowe. Powiem ci później, jeśli przetrwasz pierwszy akt.";
			link.l1 = "Przypuszczam, że twoje śmiertelne ciało wciąż może krwawić!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "Zdaje się, że twoje moce cię opuszczają, wielki Kukulcanie... Możesz być silny, ale twoje ciało wciąż jest śmiertelne!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = " Myślę, że to wystarczy rozrywki. Jesteś prawdziwym mistrzem szermierki i wielkim wojownikiem, ośmieliłbym się nawet powiedzieć, że największym wojownikiem swoich czasów, ale tę bitwę przegrałeś, "+pchar.name+"I'm here to see Governor Pouancey.";
				link.l1 = "Jesteśmy tylko...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Dosyć, drogi bracie. Nie możesz stawić czoła potędze Kukulkana, gdy jest on razem ze swoim artefaktem! Pozwoliłem ci żyć tak długo tylko po to, by zobaczyć, co naprawdę jesteś w stanie osiągnąć.";
			link.l1 = "Kurwa... Ten ostatni cios... Ale o jakim artefakcie mówisz? Maska? Jest przy mnie!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = " Biedny, biedny Kapitanie "+GetFullName(pchar)+"...  Dotarłeś tak daleko, przetrwałeś wszystkie niebezpieczeństwa, pokonałeś wielu z najsilniejszych wrogów tylko po to, by zostać pokonanym na końcu!.. Jadeitowa maska, którą znalazłeś wewnątrz metalowej skrzynki blisko wraków 'Santa Quiteria' na Ksocheatem, jest fałszywa! To tylko starożytna maska z skarbca Taysala. TO NIE JEST MASKA KUKULKANA!.\nOsobiście zabrałem ją stąd po mojej nieudanej wyprawie, jest strzeżona przez starożytny rytuał. Ta maska była powodem, dla którego burza zniosła Santa Quiteria do Ksocheatem. Miała też drugi cel. Miała zmylić każdego, kto przybył tam po mój PRAWDZIWY artefakt.";
			link.l1 = "Ale... Gdzie więc była prawdziwa maska?! Przeszukałem całe Ksocheatem!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "Nie masz, "+pchar.name+". Mój artefakt leżał po przeciwnej stronie wyspy od 'Santa Quiteria', w dobrze strzeżonym sanktuarium. Droga tam prowadzi przez podziemne jaskinie. Trudno go znaleźć i nie jest oczywisty dla niewprawnego oka śmiertelnika. Oto on! Spójrz na niego dobrze, po raz ostatni...";
			link.l1 = "To nie może być!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "Przeżyłeś i wygrałeś wiele bitew, bracie. Ale tę przegrałeś, "+pchar.name+"...";
			link.l1 = "I co teraz?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "Podróżuję bezpośrednio do dziesiątego wieku, siedem wieków wstecz. To wystarczy, by cywilizacja Majów osiągnęła niezachwianą potęgę militarną i naukową nad białą rasą.";
			link.l1 = "A co się stanie z naszym światem? Czy zniknie?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "Nie. To się zmieni. Może znajdzie się dla ciebie miejsce, ale nie będziesz pamiętał nic z tego, co się tutaj wydarzyło. Niektórzy z tych, którzy się tu urodzili, nigdy tam się nie narodzą, odwrotnie także jest prawdą. Zmarli powrócą do życia, a żywi umrą, w taki czy inny sposób, wszyscy zostaną odrodzeni. Suum cuique, każdemu to, co mu się należy, "+pchar.name+".\nNie bój się, braciszku. Nigdy nie pojmiesz, co się stało, i naturalnie przyjmiesz nową rzeczywistość. Tylko ja, Kukulcan, zachowam wspomnienia... Ale dość tego! Kanek już wszystko przygotował do rytuału.\nPójdziesz za mną, "+GetFullName(pchar)+", a ty będziesz świadkiem ostatnich chwil istnienia tej rzeczywistości, którą tak usilnie pragnąłeś zachować.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "  Wrota czasów zostały otwarte! Radujcie się, moje dzieci, gdyż stoicie tak blisko wielkości! Stworzymy nowy świat, świat bez miejsca dla bladych najeźdźców!\nŻegnajcie, "+pchar.name+", i bądź gotów zaakceptować swój nowy los, cokolwiek to będzie. Suum cuique!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "Ta bitwa jeszcze się nie skończyła, śmiertelniku. Jesteś znacznie wyczerpany, a ja mam nadciągające posiłki! Oddasz mi mój artefakt. Albo to, albo zabiorę go z twego martwego ciała, dla mnie to bez różnicy...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakanie! Rozkazuję ci natychmiast zabić tego człowieka!";
			link.l1 = "... ";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Nie słyszałeś mnie? Powtarzam: rozkazuję tobie i twoim wojownikom pojmać i zabić tego człowieka!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! Co do diabła? Kanek! Powtórz moje rozkazy twemu cholernemu synowi!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "Zdradzasz swój lud, Urakanie! Zadrżałeś w obliczu tak znamiennych przemian! Wojownicy, rozkazuję wam pojmać i stracić nie tylko tego człowieka, który nazywa siebie moim bratem, ale również Urakana zdrajcę!";
			link.l1 = "Wojownicy, w imię Cavila i Hurakana rozkazuję wam stać na miejscu, jeśli życie wam miłe! Żaden z was nie przetrwa walki z Cavilem! Niech bogowie sami zdecydują, który z nich jest najsilniejszy na Ziemi!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "Ten dzień staje się coraz lepszy. Nie spodziewałeś się takiego obrotu spraw, prawda, bracie? Bogowie sami muszą zdecydować, kto z nich jest naprawdę najsilniejszy. I każdy dostanie to, na co zasłużył, Michel. Suum cuique! Każdemu, co mu się należy...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
