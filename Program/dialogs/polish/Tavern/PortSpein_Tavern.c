// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"... ","Przez cały ten dzień, to już trzeci raz, gdy mówisz o jakimś pytaniu...","Więcej pytań, jak sądzę?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Umph, gdzie podziała się moja pamięć...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "Słyszałem, że konsumpcja szaleje w waszym forcie. Myślisz, że epidemia rozprzestrzeni się na miasto?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Co możesz powiedzieć o komendancie fortu?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Czy imię 'Juan' coś ci mówi?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Słuchaj, w kwietniu 1654 roku do waszego portu zawinął fregat pod dowództwem kapitana Miguela Dichoso i zniknął potem. Czy jest coś, co możesz mi o tym powiedzieć?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Komendant twierdzi, że nie ma niebezpieczeństwa. Ci, którzy są zbyt ciekawi, kończą zamknięci w kazamatach. Ja do takich nie należę, przepraszam.";
			link.l1 = "Czyżby? Karczmarz nie ma ochoty słuchać plotek - to coś nowego! Czyżby brzęk pesos mógł przywrócić twoją ciekawość?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Srebro jest kuszące, rzecz jasna, ale moja własna skóra jest cenniejsza. Może mógłbym ci opowiedzieć o czymś innym, señor? Zawsze chętnie porozmawiam, po prostu zacznij rozmowę!";
			link.l1 = "Więc tak to się rozwija... Dobrze, w tej sakiewce jest trzy tysiące sztuk ośmiu, a my sobie miło pogawędzimy o pogodzie, zgoda?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Ach, jesteś uparty, señor. Pamiętaj tylko, że tej rozmowy nigdy nie było. (szepcząc) Już od roku słyszałem kilka razy, że ludzie płonęli w naszych więzieniach, umierając na suchoty. Możesz winić władze, możesz winić Boga albo Diabła, ale większość przypisuje to złemu losowi. Ta przeklęta choroba tak szybko kradnie życie. Czasami wsadzą tam zupełnie zdrowego człowieka, a po tygodniu czy dwóch już go nie ma. Tak po prostu...";
			link.l1 = "Oj... Cały rok, mówisz? I co, nikt się nie pofatygował, żeby coś z tym zrobić?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Kogo to obchodzi, señor? Kogo obchodzą więźniowie? Szumowiny społeczeństwa - tak mówią wielcy panowie w jedwabiach. Był lekarz, który pracował w lochach. Próbował leczyć te biedne dusze. Nie zagościł długo, wydaje się, że choroba pozbyła się i jego\nKomendant teraz nikogo nie wpuszcza, a nasze władze nie zwracają uwagi na takie sprawy, zwłaszcza gdy muszą mniej płacić za racje więzienne.";
			link.l1 = "Interesujące, ale co to takiego w tej chorobie, że przeraża cię tak bardzo, że zamknięci w bezpiecznych murach szeptamy jak zakonnice w konfesjonale?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Trudno mi to powiedzieć, ale był tu jeden gość. Zabrano go za przemyt i siedział zamknięty przez około pół roku, dopóki jego kumple go nie wykupili. No wiesz - odważyli złoto, komu trzeba, poczekali tyle, ile im kazano, i gość wyszedł. Ale od tamtej pory jest zupełnie szalony.";
			link.l1 = "Bardziej szalony niż szczur z zęz?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Tak przypuszczam. Od tego czasu był bezużyteczny dla swoich kamratów, spędzając całe dnie tutaj, upijając się na śmierć. Wyglądało, jakby chciał coś wymazać z głowy. Za każdym razem, gdy się upijał, opowiadał historie o chorobie, która zabiera ludzi w ciszy\nTo były jego dokładne słowa. Według niego, 'choroba' to najgorsza rzecz, jaka może spotkać człowieka.";
			link.l1 = "Bełkot pijaka. I co z tego?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Niczego innego, poza faktem, że znalazł trochę płynnej odwagi i zaczął gadać coraz więcej, aż nagle ktoś poderżnął mu gardło i wrzucił go do rynsztoka... a kto to zrobił i po co, jest mi zupełnie obojętne.";
				link.l1 = "Co możesz powiedzieć o komendancie?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Nic, poza tym, że stał się odważny i zaczął coraz więcej mówić, a potem po prostu ktoś podciął mu gardło i wrzucił do rynsztoka... a kto to zrobił i dlaczego, to dla mnie jedno i to samo. (podnosi głos) Tak, zatoki i rafy są tutaj naprawdę niebezpieczne, señor. Musisz być ostrożny, gdy burze nadciągają z Wielkich Antyli, przegapisz pogodę i cię nie ma! Miłego odpoczynku, señor, dzięki za odwiedziny!";
				link.l1 = "Burze... racja. Dzięki i tobie.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "Co można o nim powiedzieć? Jest pułkownikiem, przybył z Europy kilka lat temu, otrzymawszy to miejsce. Podobno został zdegradowany tam w Starym Świecie za jakieś brudne uczynki, które popełnił. Nie wiem, czy to prawda, ale na początku były plotki. Ale kto nie ma o sobie plotek, prawda?";
			link.l1 = "Brudne uczynki, mówisz... To interesujące. Coś jeszcze?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Cóż, co mogę powiedzieć... Pułkownik wygląda na człowieka, który bardzo dba o własne bezpieczeństwo. Oczywiście te miejsca nie są bezpieczne z powodu piratów, bandytów, Indian i innego łajdactwa, ale Senor Komendant nigdy nie opuszcza domu bez kilku ochroniarzy\nJego rezydencja znajduje się w tym mieście i zamienił ją w małą fortecę - jego służący są dobrze uzbrojeni i trzymają okna zakratowane.";
			link.l1 = "Ale w dzień służy w więzieniu, prawda?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Tak, ale ten dworek to właściwie czeka tam na zasadzkę lub najazd. Zresztą, Señor Komendant nieczęsto tam wraca, prawdziwą twierdzą jest bardziej jego forteca, he-he.";
			link.l1 = "Dziękuję, bardzo mi pomogłeś. Do zobaczenia później, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan? Który? Jest ich tutaj wielu, ludzie zazwyczaj mają też nazwiska... albo przynajmniej przezwisko...";
			link.l1 = "Tak sobie myślałem... Może jego przezwisko to 'Suchotnik', słyszałeś o tym?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "O mój Boże, znowu o tym mówisz! Nie, dzięki Bogu, nie słyszałem. Przysięgam! A teraz zmieńmy temat. Proszę!";
			link.l1 = "Dobrze, dobrze, nie dostawaj zawału serca...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		case "guardoftruth":
			dialog.text = "Pamiętam go. Często wpadał do mojej tawerny, ale niewiele mówił. Wypił kilka kieliszków rumu, szepnął coś do niektórych klientów i wyszedł. Bardzo ponury i poważny, jak wszyscy na tym fregacie. Niebezpiecznie wyglądający najemnicy, którzy trzymali swoje miecze w pogotowiu\nKrążyła plotka, że fregata była pełna skarbów, ale nie wierzę w takie bajki. Cenne ładunki nigdy nie są transportowane na jednym statku bez konwoju. Spędzili tu dzień, a potem odpłynęli. Słyszałem, że do Europy. To wszystko, co wiem.";
			link.l1 = "Widzę. Cóż, to przynajmniej coś...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
