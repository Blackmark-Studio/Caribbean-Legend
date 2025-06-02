// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Wszystkie plotki o "+GetCityName(npchar.city)+" do usług. Czego chciałbyś się dowiedzieć?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Powtarzasz to wszystko jak papuga...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Racja, z jakiegoś powodu zapomniałem...","Tak, to naprawdę już trzeci raz...","Tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "Słyszałem, że na wyspie był niezły bałagan... Niewolnicy?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "Słyszałem, że ten nędzny drań Bart Portugalczyk wreszcie spotkał się ze sprawiedliwością! Czy jest w więzieniu? Kiedy będzie jego egzekucja, wiesz może? Chcę to zobaczyć, mam z nim na pieńku...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "Posłuchaj, "+npchar.name+", słyszał"+GetSexPhrase("em","am")+", że niedawno pojawiła się u ciebie nowa piękna kelnerka... i już zdążyła zniknąć?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "Posłuchaj, "+npchar.name+", czy w wieczór zniknięcia Betsy zauważyłeś kogoś podejrzanego w jej pobliżu? Może z kimś rozmawiała?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{
				link.l1 = "No cóż, "+npchar.name+", dobra wiadomość - twoja cenna kelnerka żyje i ma się dobrze. Będziesz musiał znowu zwiększyć zapasy rumu, ludzie wkrótce zaczną wracać.";
				link.l1.go = "TBP_Tavern3_21";
			}
			//<-- Тайна Бетси Прайс
		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Aye, nigdy nie było takiego bałaganu... Ponad tysiąc murzynów się zbuntowało. Dwie plantacje zostały spalone do cna, a każdy z ich panów został zamordowany. Komendant obawia się, że niewolnicy przyjdą zaatakować miasto, więc wprowadził stan wojenny. A wszystko zaczęło się z powodu dwóch murzynów, kozła imieniem Tamango i kozy imieniem Isauri...";
			link.l1 = "Brzmi to dość dramatycznie. Opowiedz mi całą historię, kim są ci murzyni?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango i Izaura - niewolnicy na plantacji Blenheim, pierwszej plantacji, która spłonęła. Ci dwaj Murzyni kochali się nawzajem. Jednak syn plantatora, Leonsio, przybył z Europy i upodobał sobie tę kozę. Chciał uczynić Izaurę swoją osobistą konkubiną. Czarny byk Tamango nie przepadał za tym pomysłem, a Izaura też nie, naprawdę kochała czarnego diabła\nTamango był jakimś naczelnikiem czy kimś takim w Afryce... Olbrzymi byk - czarny jak grzech i śmiertelny z toporem, inni Murzyni bali się go i szanowali. Więc ten Murzyn poprowadził innych niewolników do buntu. Zaatakowali strażników nocą, zabili wszystkich białych poza wielkim domem, mulatów też\nPotem Izaura otworzyła drzwi plantacji, a dzikie małpy zamordowały wszystkich w środku. Blenburg został spalony do ziemi. Następnie niewolnicy uciekli do dżungli i zniknęli...";
			link.l1 = "Cóż, cóż za historia, brzmi jak fabuła powieści! Prawdziwe powstanie niewolników, zupełnie jak w starożytnym Rzymie. Jak się o tym wszystkim dowiedziałeś, swoją drogą?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Plotki, mój panie, ziemia jest nimi przepełniona. Rum rozwiązuje języki, wystarczy tylko słuchać...";
			link.l1 = "I jak to wszystko się skończyło? Czy znaleźli tych murzynów?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Ha, nie ma mowy! Dopóki posiłki w końcu nie zdołały przybyć, nikt nie zrobił kroku do dżungli. Potem przypłynął okręt wojenny Kompanii z oddziałem żołnierzy i przeszukali wyspę. Nie znaleźli czarnego futra ani kręconego włosa żadnego zbiegłego murzyna.";
			link.l1 = "Cóż, co o tym sądzisz! Tysiąc czarnuchów po prostu wyparowało w powietrze?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Właściwie to do wody.";
			link.l1 = "O czym ty mówisz, "+npchar.name+" ? Wiesz tak dobrze, jak ja, że murzyni nie potrafią pływać.";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "He-he... o nie, ci czarni nie są tak szybko przynętą na rekiny. Rzecz w tym, że następnej nocy po buncie zniknęła z doków brygantyna. Możesz mnie pomalować na czarno, a ja zagram na banjo i zatańczę dla ciebie, jeśli to nie było rękami tego łajdaka Tamango i jego Murzynów! Dlatego nie ma ich już na wyspie.";
			link.l1 = "Ha, teraz słyszałem już wszystko, "+npchar.name+"Spodziewasz się, że uwierzę, iż grupa półdzikich Murzynów potrafi obsługiwać żagle i nawigować? Prędzej spodziewałbym się, że statek małp wpłynie tu z Gwinei.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Ja też w to nie wierzyłem, mynheer, ale dowodem jest brakujący statek. Może któryś z tych murzynów kiedyś służył jako steward na statku i nauczył się jakiejś techniki żeglarskiej. Może użyli czarnej magii, kto wie! Wpadnij i odwiedź mnie ponownie, "+pchar.name+"Przy następnym razem przyniosę ci więcej opowieści.";
			link.l1 = "Dzięki! Cóż, czas, żebym ruszał w drogę.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Tak, to prawda. Złapali tego pirata. I możesz w to uwierzyć jak? Został schwytany na łodzi wiosłowej sam pośrodku morza. Nawet nie pisnął, zanim został wtrącony do ładowni dla szczurów. To naprawdę zabawne, wiesz, taki niebezpieczny pirat został złapany jak taki żółtodziób!";
			link.l1 = "A dlaczego był zupełnie sam na morzu?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Zapewne postanowił rozstać się ze swymi zbójami, nie ma co... Nie mogli sprawiedliwie podzielić łupu. Teraz jest w rękach samej Kompanii, a ci nie mają poczucia humoru. Mówią, że przejął jeden z ich statków z czymś cennym. Najwyraźniej chcą tylko wydusić z niego trochę informacji, skoro jeszcze nie dynda na szubienicy.";
			link.l1 = "Kiedy będzie jego egzekucja, wiesz może?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Nikt nie wie. Myślę, że gdy Kompania dowie się, czego chce, szybko zawiążą mu konopną pętlę na szyi. Portugalczyk jest teraz w więzieniu pod niezawodną strażą\nNiedawno przyprowadzili tu również jego bosmana. Jego historia była jeszcze bardziej zaskakująca, dobrowolnie oddał się w ręce Holendrów w Philipsburgu. Więc umieścili go w celi tuż obok jego byłego kapitana, teraz są sąsiadami, he-he...";
			link.l1 = "Cuda się zdarzają! Dobrze, będę wypatrywał wieści. Nie chcę przegapić tego wieszania. Do widzenia, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "Och, gdybyś ją tylko widział, kapitanie! Betsy... taka gracja, taki uśmiech! Mężczyźni walili tu drzwiami i oknami, żeby tylko na nią spojrzeć. A ile srebra zostawiali w mojej tawernie... Ale trzy dni temu nie przyszła do pracy. Oczywiście, wysłałem ludzi do jej domu, ale jej tam nie było. W domu bałagan, rzeczy osobiste zniknęły\nJuż nie wiem, co myśleć. Straż, jak zwykle, tylko wzruszyła ramionami. Mówią, że mają ważniejsze sprawy niż szukać zaginionych dziewczyn – że się zabawiła, to wróci. Kapitanie, może ty ją znajdziesz? Jeśli mi ją tu przyprowadzisz, zapłacę ci sto dublonów. Nie mogę jej stracić, rozumiesz? To prawdziwy skarb! Muszę ją odzyskać za wszelką cenę!";
			link.l1 = "Zobaczmy, co da się zrobić. Może przed zniknięciem zachowywała się jakoś dziwnie albo dostała złe wieści?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "Szukać dziewczyny, która po prostu postanowiła zniknąć? Mam ważniejsze sprawy. Radź sobie sam.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "W ostatni dzień przed zniknięciem była zadowolona, nawet szczęśliwa! Ani śladu niepokoju, ani słowa, że chce gdzieś odejść. Po prostu – zniknęła!";
			link.l1 = "Ciekawe... Gdzie znajdę jej dom?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "Mieszkała wyżej na ulicy, w chacie tuż za domem naprzeciwko rezydencji z niebieskim balkonem. To niedaleko stąd.";
			link.l1 = "Nie będę tracić czasu. Jak coś odkryję – dam ci znać.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "Podejrzanego? Przecież wokół niej kręciły się tłumy adoratorów, każdy na swój sposób podejrzany! Była kokietką, wiedziała jak przyciągnąć uwagę.";
			link.l1 = "To już zauważył"+GetSexPhrase("em","am")+". Ale może ktoś wyróżniał się szczególnie?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "Hmm... był jeden taki. Tego wieczoru dał jej wisior z kameą. Siedział tu, nie spuszczał z niej oczu i cały wieczór się wokół niej kręcił.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "To przypadkiem nie ten wisior? (Pokaż kameę kupioną od żebraka)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "Wisior z kameą, mówisz...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "To on! Na pewno! Kapitanie, udało ci się już czegoś dowiedzieć?";
			link.l1 = "Szczegóły później, "+npchar.name+", teraz nie możemy tracić czasu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Oddano: Wisiorek z kameą", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "To wspaniale, kapitanie! Już myślałem, że jej nie zobaczę. Więc co się właściwie stało? Naprawdę chciała uciec?";
			link.l1 = "Powiedzmy, że musiała poradzić sobie z pewnymi problemami z przeszłości. Ale wygląda na to, że to już za nią – wkrótce wróci do pracy.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "Powiedzmy, że potrzebowała przerwy od patrzenia na twoją nudną gębę. Ha-ha! Nie marszcz się tak, tylko żartuję. Każda dama powinna mieć swoje małe tajemnice...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "Najważniejsze, że wróci do pracy. Zasłużyłeś na swoją nagrodę, kapitanie. Proszę – sto dublonów, jak się umawialiśmy. I jeszcze – weź tę mapę. Jeden z gości ją tu zostawił i już nie wrócił. Wygląda na to, że prowadzi do skarbu.";
			link.l1 = "Sprawdzę to. Dziękuję.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "Najważniejsze, że wróci do pracy. Zasłużyłeś na swoją nagrodę, kapitanie. Proszę – sto dublonów, jak się umawialiśmy. I jeszcze – weź tę mapę. Jeden z gości ją tu zostawił i już nie wrócił. Wygląda na to, że prowadzi do skarbu.";
			link.l1 = "Sprawdzę to. Dziękuję.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
