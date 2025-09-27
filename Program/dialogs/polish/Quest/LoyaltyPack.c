void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "Pozwolenie na zwrócenie się, kapitanie?";
					link.l1 = "Później, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Mów.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "Pozwolenie na zwrócenie się, kapitanie?";
					link.l1 = "Później, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Mów.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "Pozwolenie na zwrócenie się, kapitanie?";
					link.l1 = "Później, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Mów.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "Pozwolenie na zwrócenie się, kapitanie?";
					link.l1 = "Później, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Mów.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = "Nie ma nic do zameldowania, kapitanie.";
			link.l1 = "Tak trzymać, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "Jak się trzymacie, kapitanie?";
			link.l1 = "O czym ty mówisz?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "Już kilka miesięcy żeglujecie po Karaibach, a niektórzy nie przetrwają tu nawet tygodnia. Załoga was szanuje, to pewne, ale ja? Martwię się o waszą przyszłość.\n"+
                          "Podzielcie się swoimi myślami, zróbcie to dla załogi. Dokąd płynie "+pchar.ship.name+"?";
                          
            link.l1 = "Nie mam planu. Chcę najpierw poznać te wody. Przygoda sama nas znajdzie.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "Te wody pełne są drapieżników, Alonso. A "+pchar.ship.name+" jest najmniejszym z nich. Na razie.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "Lubię zarabiać pieniądze. Najlepiej legalnie. Ale zobaczymy, jak to wyjdzie.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "Przecież wiesz. Po naszej pamiętnej rozmowie na 'Ulissesie' wszystko się tylko skomplikowało…";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "Oto prawdziwa wolność! Byle starczyło na utrzymanie statku i coś zostało w skrzyniach na czarną godzinę.\n"+
                          "Dokądkolwiek poprowadzi was nastrój, zadanie czy mapa skarbów - bierzcie pasażerów, frachty, każdą drobną robotę po drodze.\n"+
                          "Drobny handel też nie zaszkodzi - kupujcie tanio, gdzie to oczywiste, sprzedawajcie, gdzie się da.\n"+
                          "A jeśli po drodze zobaczycie samotnego kupca… Hehe. Macie rację, kapitanie. Przygoda rzeczywiście nas znajdzie.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "Dzięki za dobrą radę, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Interes dochodowy, jeśli statek na to pozwala. Szukajcie samotnych kupców i pokażcie im, co znaczy 'skąpy dwa razy traci'.\n"+
                          "Na nieszczęście, wchodzi tu inne powiedzenie: 'Prawda w końcu wyjdzie na jaw'. Zawsze znajdzie się gadatliwy język w załodze, który rozgada o waszych wyczynach w pierwszym porcie.\n"+
                          "Więc albo rabujcie wszystkie flagi po trochu, albo wybierzcie sobie wroga na całe życie.\n"+
                          "Choć może się zagalopowałem. Jeśli będzie naprawdę ciężko, w Port Royal jest adwokat, który za brzęczące peso załatwi każdy problem z władzami. Nazwijmy to podatkiem pirackim, hehe!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "Dzięki za dobrą radę, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Ech, tu wam nie pomogę, kapitanie. Potrzebny wam prawdziwy statek handlowy: barkentyna, a najlepiej bark. Pewnie tego pożałuję, ale weźcie lżejsze działa albo w ogóle je wyrzućcie.\n"+
                          "Bierzcie zlecenia na dostawy od właścicieli sklepów, po drodze handlujcie na własną rękę i woźcie pasażerów.\n"+
                          "Jak zaoszczędzicie dość pieniędzy, inwestujcie w sklepy i banki. Zobaczcie, kapitanie - nadejdzie dzień, gdy pieniądze zaczną robić pieniądze, i będziecie mogli pozwolić sobie na wielki statek z dwustu chłopakami na pokładzie.\n"+
                          "Za który, nawiasem mówiąc, nie wy będziecie płacić, a wasz interes.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Dzięki za dobrą radę, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "Ja to widzę inaczej, kapitanie. Na 'Ulissesie' byliście tylko pasażerem - te biedne dusze nie mają kontroli nad swoim losem. Teraz jesteście kapitanem, który zasłużył na swój kapelusz, co znaczy, że możecie rozwiązać każdy problem. Mówiłem wam już - nie ma wyższego stanu w naszym świecie.\n"+
                          "Czuję w kościach, że ta epopeja z waszym bratem potrwa jeszcze lata, więc zadbajcie najpierw o siebie. Monsieur Michel nigdzie nie ucieknie, hehe…\n"+
                          "Nie tylko wy macie problemy na Karaibach. Najwyższy czas pomóc innym, przy okazji zarabiając pieniądze, zdobywając sprzęt i znajomości. Po drodze nauczycie się wszystkiego, co będzie potrzebne w tej rodzinnej sprawie…";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Dzięki za dobrą radę, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "Nie ograniczajcie się do jednej roli, kapitanie. Róbcie tylko to, co chcecie. Bierzcie wszystko i nic nie oddawajcie. Wszystko się ułoży.";
            link.l1 = "I dzięki też za dobre słowo.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "Ech, za to mi płacicie, kapitanie. Myślicie, że załodze wystarcza skromny żołd, żeby wykonywać wasze rozkazy?\n"+
                          "Dziesiątki facetów stłoczonych w ciasnej przestrzeni, nikt nie wie, kiedy zobaczy ląd i czy w ogóle. A zatopić statek? Pestka.";
            link.l1 = "Tak, tak, znam te gadki, Alonso. Co tam mówiłeś o statkach?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "Hehe! Statek to więzienie, obóz wojskowy i klasztor w jednym. Męskie zbiorowisko, krótko mówiąc. Więc problemy rozwiązuje się albo słowem, albo batem. W waszym przypadku to drugie, hehe, odpada, więc pomyślałem, że sobie pogadamy. Żeby wam było lżej, znaczy się.";
            link.l1 = "A ty sam byłeś kiedyś w więzieniu? W wojsku? W klasztorze, broń Boże? I w ogóle, Alonso, opowiedz o sobie. Przecież prawie nic o tobie nie wiem.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "W klasztorach nie byłem, nie będę kłamał. Choć służyłem kiedyś w Świętej Inkwizycji…";
            link.l1 = "Jak cię tam diabli przynieśli?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "O! To było tak. Ciągnąłem swoją służbę jako najemnik w wojnie europejskiej. Diabli wiedzą, jak się zaczęła i kto z kim walczył. Wiedzieliśmy tylko, że wojna trwa już trzydzieści lat i który dowódca w miarę regularnie płaci żołd. To była dopiero przygoda!\n"+
                          "To było w czterdziestym drugim… czy czterdziestym pierwszym? Nieważne. Dwie kompanie, obie w służbie cesarza, spotkały się w lesie. We mgle. I zaczęły się wzajemnie rąbać! Trzy dni rzezi!";
            link.l1 = "Jak to możliwe?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "Spróbuj rozróżnić swojego od wroga we mgle. A że nie płacili nam już trzy miesiące, każdy myślał o łupach.\n"+
                          "Połowę się nawzajem położyliśmy. Jak się zorientowaliśmy, było za późno. Wtedy poznałem jednego Moskala. Wielki jak niedźwiedź, ale dusza ze złota!";
            link.l1 = "I co dalej?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "Wiecie, jak to na wojnie? Kto pierwszy zamelduje, ten bohater. Więc pomyśleliśmy - trzeba z tej hańby wyciągnąć korzyść!\n"+
                          "Dogadaliśmy się z chłopakami, poszliśmy do płatnika, zameldowaliśmy o 'wielkiej bitwie'. Poległym żołd ucięli, żywym wypłacili, ja i mój kumpel - premia, a dowódcy - udział.";
            link.l1 = "To jesteś bogaty, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "Ha! Potem tydzień wino piliśmy i w karty graliśmy. Szczęście, że mój nowy towarzysz z dalekiego Carstwa Moskiewskiego miał słabość do rzadkich rzeczy, bo trafiłbym do więzienia za długi. Wykupił ode mnie trofeum: wspaniały trzylufowy pistolet, i to za dobrą cenę - nie naciągnął mnie w biedzie.";
            link.l1 = "Fantastyczna historia, Alonso. Wydaje mi się, że właśnie ją wymyśliłeś.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "Obrażacie mnie, kapitanie. Proszę, mały prezent.";
            link.l1 = "Co to jest?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "Ładownica do walki muszkietowej. W ojczyźnie mojego moskiewskiego przyjaciela wszyscy takie noszą. Tak przynajmniej mówił.\n"+
                          "Niech wam dobrze służy, kapitanie. Uznajcie to za prezent od załogi.";
            link.l1 = "Niespodziewanie! Dzięki, Alonso. To co z tą służbą w inkwizycji?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Ech…\n"+
                          "Dzwony biją, kapitanie! Czas do roboty. Dokończymy innym razem.";
            link.l1 = "Na pewno dokończymy tę rozmowę. Dzięki za prezent!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Уровень 8) - Продолжаем историю
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Wiele osiągnęliście od naszej ostatniej rozmowy i nikt - ani załoga, ani ja - nie wątpi już w wasze talenty.";
			link.l1 = "Były wątpliwości?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Oczywiście, że były. Jesteśmy prostymi ludźmi - przyzwyczajonymi przygotowywać się na najgorsze. Cieszcie się wolnością, kapitanie. Tak dalej, a zobaczycie zupełnie inną stronę Karaibów.";
            link.l1 = "Miło słyszeć. A teraz opowiedz o swojej służbie w inkwizycji. Ostatnim razem zacząłeś od jakiejś wojskowej historyjki i na niej też skończyłeś.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "Co tu opowiadać? Po tej bezsensownej, ale bardzo dochodowej rzezi w lesie, zaprzyjaźniliśmy się z tym Moskalem i przekręciliśmy jeszcze niejeden interes.\n"+
                          "Pamiętam, jak postanowiliśmy obrabować cesarski konwój. Zwiadowcy donieśli - wiozą trofea, złoto, broń...";
            link.l1 = "I co, udało się?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Łatwizna. Zaatakowaliśmy z dwóch stron, rozgoniliśmy straż, otwieramy wozy - a tam kapusta! Zgniła, śmierdząca kapusta dla jakiegoś garnizonu! Ale wiecie co? Tydzień nie żarliśmy, więc nawet temu się ucieszyliśmy!";
            link.l1 = "Jakby na moim statku karmili lepiej.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "No teraz to już przywykłem. Ale wtedy… Po tygodniu na tym, co się znajdzie - choćby korę z drzew byś obgryzał!\n"+
                          "Ale mój przyjaciel się nie poddawał. Wyciągnął manierkę ze swoją firmową nalewką - moskiewski przepis, mówi. A nam wszystko jedno, byle nie ocet! Po paru łykach nawet kapusta wydawała się przysmakiem!";
            link.l1 = "Obrzydliwe.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "Obrzydliwy jest stan naszych beczek z wodą, a ten moskiewski bimber uratował mi wtedy życie.";
            link.l1 = "Jak to?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "Upiliśmy się jak świnie prosto w błocie drogowym z pływającą kapustą. No i słowo za słowem, pokłóciłem się z jednym szlachciurą. Niemiec był, taki wypieszczony, wystrojony. Brzydził się z nami pić, tylko czyścił swój muszkiet i ciskał zjadliwe słówka.\n"+
                          "Siedzimy sobie, odpoczywamy, zalewamy żale nad kapustą. A on zaczyna nas pouczać o wojskowej mądrości. Że nasze wierne pałasze i piki wkrótce pójdą w zapomnienie, ale bagnet - to przyszłość i klucz do wszystkiego.\n"+
                          "No i pokłóciłem się z nim, i jakoś doszło do tego, że umówiliśmy się bić na śmierć - akurat na bagnety. Nie pytajcie, jak do tego doszło, sam nie pamiętam.\n"+
                          "A bagnetów w całej rocie było tylko dwa. Jeden tego oficerka, drugi Foxa, Anglika. Pożyczyłem od niego fuzję i zatłukłem nią Niemca na śmierć, po czym się ulotnił.";
            link.l1 = "Przecież byłeś głodny i pijany.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "Potem zrozumiałem, że nalewka mojego przyjaciela naprawdę wzmacnia rękę, gdy machujesz ciężkim muszkietem. Więc teraz skłaniam się ku pomysłom martwego Niemca.";
            link.l1 = "I jak to się ma do twojej służby w inkwizycji?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "Znowu mi nie wierzycie, kapitanie! Proszę, weźcie to.";
            link.l1 = "Butelka i kartka papieru?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "To ta nalewka, o której wam mówiłem. I przepis. Może się spodoba, hehe.";
            link.l1 = "Wybacz, przyjacielu, ale bazgroły i jakaś mętna mikstura to nie…";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "Dobra, dobra, kapitanie. I tak zamierzałem wam to podarować. Mi taka broń nie pasuje, ale wam się przyda. Bagnety to rzadkie bestie. Ale jak się nauczycie, zapomnicie o machaniu szablami.";
            link.l1 = "Czekaj, to ten muszkiet cesarskiego oficera? Którego zabiłeś?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Ten sam. Jak widzicie, powiedziałem wam prawdę, kapitanie.";
            link.l1 = "Ale nie o to pytałem.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "Dzwony biją, kapitanie! Czas do roboty. Dokończymy innym razem.";
            link.l1 = "Na pewno dokończymy tę rozmowę. Dzięki za muszkiet!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Kapitanie, w sprawie nowych rekrutów...";
			link.l1 = "Coś się stało?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "Chciałem zameldować, że przy kolacji jeden z rekrutów wspomniał, że chciał zaciągnąć się właśnie na wasz statek.";
            link.l1 = "I co to dokładnie znaczy?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "Że wkrótce takich ludzi może być więcej. Macie już imię, kapitanie.";
            link.l1 = "Zabawne, że wciąż nie wiem, co kryje się za twoim imieniem. I tej historii o inkwizycji tak i nie dokończyłeś.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "O, gdzie ja skończyłem... A tak! Postanowiliśmy zostać dostawcami wojskowymi. Wojna dobiegała końca, trzeba było myśleć o przyszłości. A mój przyjaciel zawsze miał głowę pełną planów na przyszłość.";
            link.l1 = "To duży skok kariery. Niedawno upijaliście się przy rozgrabionym wozie z kapustą.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "A co? Dostaliśmy zamówienie na sto hełmów dla jakiegoś pułku. Dali dobry zadatek. Ucieszyliśmy się, poszliśmy świętować... Zagraliśmy w karty.\n"+
                          "Rano się budzimy --- zadatku nie ma, armia wyrusza za dwa dni, a my nie mamy ani jednego hełmu!";
            link.l1 = "I co zrobiliście?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "Poszliśmy na świeże pole bitwy, pozbieraliśmy kapelusze z trupów. Potem poprzybijaliśmy różne żelazka, przymocowaliśmy płytki... Śmiesznie wyglądało, ale działało! Od szabli na pewno chroniło. No, raz na pewno. Czym nie hełm?!";
            link.l1 = "Kwatermistrz docenił waszą pomysłowość?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Wysłał nas przed trybunał za defraudację i oszustwo. Ale wiecie co? Żołnierze potem mówili, że te kapelusze nie raz uratowały im życie. No i nam też, jak się okazało.";
            link.l1 = "Jak to?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "No więc obaj trafiliśmy do więzienia. A naszą rotę wysłali na misję. Nie wiem gdzie i przeciw komu, i oni pewnie też nie wiedzieli. Nigdy nie wrócili.\n"+
                          "...\n"+
                          "Przepraszam, kapitanie. Dokończymy innym razem. Weźcie ten kapelusz i instrukcję. Zmajstrowałem wczoraj, żeby was rozweselić... Ale tylko sam się na darmo zasmuciłem.";
            link.l1 = "Oczywiście, Alonso. Dzięki za prezent.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

       // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Kapitanie, chciałem tylko zameldować, że waszą załogę przyjmują z honorami w tawernach i burdelach. Służba pod waszą banderą to dziś coś znaczy!";
			link.l1 = "Dzięki, Alonso... Szkoda tylko, że sam jeszcze nie widzę za bardzo tego \"przyjmowania z honorami\".";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "Wkrótce zobaczycie. Karaiby to tort, który dzieli między sobą kilkadziesiąt kapitanów. Niedługo zasiądziecie przy tym stole i złapiecie swój kawałek.\n"+
                          "I kto wie? Może to wy zostaniecie karaibską legendą, która zabierze cały tort.";
            link.l1 = "To dokończysz swoją historię? Skończyliśmy na tym, jak trafiłeś do więzienia.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "Ha! Sprawa wielkich złodziei kapeluszy. Moskal i Portugalczyk w maleńkiej celi gdzieś we Flandrii. Czekają na wyrok. Śmierci, oczywiście.\n"+
                          "Uratował nas jakiś ważny pan - okazał się moskiewskim ambasadorem! Stary przyjaciel Fadeja. Był przejazdem, dowiedział się o naszej biedzie, wykupił nas!";
            link.l1 = "Fadeja? TEGO Fadeja? I milczałeś?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "Aha. Na tym się rozstaliśmy: on wrócił do swojej Moskwy, albo bić się z Polakami, albo kręcić wielkie interesy. A ja jeszcze pokręciłem się po starej ojczyźnie, i oto jestem.";
            link.l1 = "Imponujące, Alonso. Tyle czasu minęło, a ty zdołałeś opowiedzieć o wszystkim, tylko nie o sobie. Dziwne, jak taki sprytny gość jak ty wygadał się o inkwizycji.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "I powiedziałem czystą prawdę, kapitanie! Nie wierzycie - zapytajcie samego Fadeja. Nietrudno go znaleźć w Basse-Terre.";
            link.l1 = "Może i zapytam. A prezent będzie?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "Co?";
            link.l1 = "Na koniec każdej historii dawałeś mi prezent.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Słyszycie? Dzwony biją. Czas do roboty.";
            link.l1 = "Tak trzymać, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
	}
} 