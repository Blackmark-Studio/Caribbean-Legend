// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

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
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Do diabła, kimże ty, u licha, jesteś?";
				link.l1 = "Dzień dobry, don Lope. Choć nie mieliśmy jeszcze okazji się poznać, teraz jest tak samo dobry moment jak każdy inny. Zwłaszcza teraz, gdy tak bardzo chcę pomóc ci wyjść z tej trudnej sytuacji...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "Czego chcesz?";
				link.l1 = "Powinienem iść...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Pomoc? Ja? Co za zwrot akcji! Czy mógłbyś mnie oświecić, señor, skąd taka szczodrość pochodzi?";
			link.l1 = "Oczywiście. Szukam twojego byłego kapitana, Esberdo Cabanasa, i nie mam zbyt wiele czasu... najlepiej, gdybym mógł spotkać się z nim w tym miejscu, które trzyma w tajemnicy. Jeszcze lepiej, gdybym dotarł tam przed nim.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha! Mówiłem temu żałosnemu durniowi, żeby trzymał gębę na kłódkę! Niebieska ambra, prawda?";
			link.l1 = "Idziesz we właściwym kierunku, mój dobry panie.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Więc pośpieszmy się. Chciałbym opowiedzieć ci każdy szczegół, jeśli znajdziesz sposób, by mnie stąd wydostać. Wiesz, jak tu trafiłem?";
			link.l1 = "Ogólnie rzecz biorąc, tak.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "Byłem kompletnie pijany, kiedy to się stało. Do diabła z tym przeklętym barmanem! Nic nie pamiętam. Wszystko mi opowiedziano dopiero, gdy obudziłem się w ładowni 'Cantavro'. Wszystko byłoby za nami, gdybyśmy tylko odpłynęli, zarówno komendant, jak i alcalde byli skłonni przymknąć na to oko. Ale ten przeklęty don Esberdo po prostu wsadził mnie do więzienia. Myślisz, że zrobił to 'aby postąpić słusznie'? Gdyby tylko, ten łajdak po prostu chciał zatrzymać mój udział w bursztynach\nTo ja wspomniałem, że pod wodą może być więcej bursztynów, niż to, co znaleźliśmy na plaży. To ja znalazłem sposób, by je zdobyć. Miałem otrzymać sporą część, ale... oh, ten skurwysyn! Ugh, ale dość o tym. Ani alcalde, ani komendant, ani don de Toledo nie są zadowoleni, że trzymają mnie tutaj, bym gnił. Gdyby nie ten wieśniak i jego krowa żona, którzy wzbudzili zamieszanie... tak czy inaczej, nie będą się sprzeciwiać, jeśli mi pomożesz\nPorozmawiaj z gubernatorem, udaj, że jesteś moim starym przyjacielem z Europy - sam to potwierdzę. Jak się nazywasz, tak przy okazji?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = "I'm sorry, there seems to be nothing to translate as the original text is empty. Could you please provide the text that needs translation?"+GetFullName(pchar)+"wspaniale. Idź zobaczyć się z don Diegiem de Toledo i poproś go o radę. Pamiętaj, masz tylko trzy dni, pogoń za 'Cantavro' będzie bezcelowa po tym czasie. Uwolnij mnie, a dam ci wszystko, czego potrzebujesz, by rozprawić się z tym łajdakiem, Cabanasem.";
			link.l1 = "Natychmiast udam się do gubernatora, don Lope. Zrobię wszystko, co w mojej mocy, aby rozwiązać tę sytuację dla naszego wspólnego dobra.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "Więc, kramarz i jego zegarowa kura dostali swoją zemstę, a ja w końcu skończyłem z tą dziurą. Jestem ci wdzięczny, señor, zrobiłeś swoje. Teraz pozwól mi zrobić moje.";
			link.l1 = "Zamieniam się w słuch!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Dobrze. Podczas naszego poprzedniego patrolu natknęliśmy się na sztorm, który zmusił nas do porzucenia kursu. Wylądowaliśmy na plaży Zachodniego Lądu, niedaleko Wybrzeża Komarów, aby zdobyć trochę świeżej wody. Znaleźliśmy tam dobre złoże niebieskiego bursztynu. Zrobiłem trochę rozpoznania i znalazłem jego stos pod wodą. Potrzebowaliśmy lepszego sprzętu, aby go zebrać, dlatego postanowiliśmy wrócić później.\nEsberdo kupił pięć długich łodzi w Hawanie dla Indian, aby nurkowali i zbierali bursztyn. Resztę historii znasz - drań się mnie pozbył i odpłynął. Znajdź go na Wybrzeżu Komarów na północ od Blueweld i pośpiesz się - według moich obliczeń masz tylko około siedmiu dni, aby tam dotrzeć. Mam nadzieję, że złapiesz tego sukinsyna w trakcie zbierania, zabierzesz cały jego bursztyn i zadźgasz go w brzuch wielokrotnie. Ale bądź ostrożny, mój były kapitan to doświadczony wojownik i marynarz. Powodzenia, señor.";
			link.l1 = "Nawzajem, Lope. Żegnaj!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Czy chce pan o coś zapytać, kapitanie?";
			link.l1 = "Odnośnie dona Montoro. Jesteśmy starymi znajomymi i byłem naprawdę zasmucony, gdy dowiedziałem się o jego nieszczęściach. Don Diego de Toledo wysłał mnie do ciebie, powiedział, że już próbowałeś uwolnić naszego wspólnego przyjaciela...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... señor, to jest trochę... niespodziewane, ale cieszę się, że mogę spotkać przyjaciela Lope! On już od jakiegoś czasu ma pecha, a teraz to...";
			link.l1 = "Co możemy dla niego zrobić? Nie ma mowy, żeby szlachetny hidalgo gnił wśród szumowin społeczeństwa!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Człowiek interesu! Pomóc biednemu Lope to zarówno łatwe, jak i trudne zadanie. Rozmawiałem z dorobkiewiczem, z którym biedny Lope miał nieszczęście się pokłócić. Zgodził się pójść na ustępstwa za pięćset dublonów. Niezła suma za jego i jego żony 'cierpienia'. Niestety, udało mi się zebrać tylko połowę potrzebnej kwoty - dwieście pięćdziesiąt dublonów.";
			link.l1 = "Więc, jeśli dostarczę ci kolejne dwieście pięćdziesiąt dublonów, to don Lope zostanie uwolniony?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Tak. Chciwy drań obiecał, że rozpuści wieść, iż Lope zrekompensował mu wszystkie szkody. Poprosi też gubernatora o ułaskawienie.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Mam przy sobie wymaganą sumę. Niech ten chciwy burżuj się nią zakrztusi.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Zrobię co w mojej mocy, by jak najszybciej zdobyć pieniądze.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Nie mogę uwierzyć własnym uszom! Señor, musiał cię przysłać sam Pan!";
			link.l1 = "Kiedy uwolnią naszego człowieka?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Cieszę się to słyszeć, señor. Jesteś prawdziwym przyjacielem Lope i prawdziwym szlachcicem.";
			link.l1 = "Żegnaj!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Czy przyniosłeś pieniądze?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Mam teraz przy sobie wymaganą sumę. Oto, niech ten chciwy burżuj się nią zadławi.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Jeszcze nad tym pracuję.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Przyniosę pieniądze temu przebiegłemu łajdakowi dziś wieczorem. Wierzę, że będą mieli rozkaz o uwolnieniu naszego przyjaciela do południa. I mam nadzieję, że później zbierzemy się, by świętować?";
			link.l1 = "Jasna sprawa, don Rosario. Muszę już iść. Do zobaczenia!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Wkrótce nasz przyjaciel będzie wolny!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Hej, co do diabła robisz na moim statku? Nie sądzę, że dostałeś moje zaproszenie, co?";
			link.l1 = "Spokojnie, Geffrey. Jestem od Tyrexa w sprawie interesu z jedwabiem na statku.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, cóż, porozmawiajmy zatem. Co on planuje? Już rozmawiałem z przemytnikami, jeśli mnie pytasz, oferują dobrą cenę za towary...";
			link.l1 = "Ile to będzie, jeśli mogę zapytać?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1300 pesos za rzut. Myślę, że to dobra cena.";
			link.l1 = "Tak, a Tyrex chce dwadzieścia złotych monet za beczkę. Ani grosza mniej. I mam na myśli dubloony. Dał mi zadanie znaleźć odpowiedniego kupca za tę cenę.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, chłopcze, ale masz szczęście! Marcus ma niezły apetyt! No, idź znajdź takiego kupca, będzie wspaniale patrzeć, jak próbujesz.";
			link.l1 = "Tak, to wszystko jest cholernie zabawne i śmieszne. Wyglądam na szczęśliwego? Nie wyglądam. Więc radzę ci przestać się śmiać i mi pomóc.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Dobrze, dobrze, kolego... Jezusie, nie przepadasz za żartami, co? Ale rozumiem, nie można cię winić za fantazje Tyrexa, wszyscy dostaniemy swoją dolę, zaufaj mi. A jak mogę ci pomóc? Nie możesz tego sprzedać w sklepach, urząd celny też odpada, zostają tylko przemytnicy. Kto jeszcze tego potrzebuje? Masz jakieś pomysły?";
			link.l1 = "Rozmyślam nad tym od czasu Hispanioli... Nieważne. Mam tylko dwa miesiące, by znaleźć stałego kupca. Trzeba coś z tym zrobić. Twoje rozkazy to wylądować w najbliższej zatoce i dokonać napraw.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Dwa miesiące?! Co do diabła? A, do cholery z tym. 'Wąż' rzeczywiście potrzebuje naprawy i czyszczenia, bo inaczej nie dogoni nawet barki. Hej, francuskie dziwki! Załoga Łysego Geffreya zostaje w Capsterville na dwa miesiące! Ha-ha-ha!... No, powodzenia, przyjacielu, w tych bezsensownych poszukiwaniach. Jeśli znajdziesz idiotę gotowego zapłacić cenę Marcusa za ten cholerny jedwab - wiesz, gdzie mnie znaleźć.";
			link.l1 = "Czekaj! Daj mi jedną rolkę tego jedwabiu. Muszę pokazać towar potencjalnym kupcom.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Oczywiście, nie ma problemu. Możesz zabrać to ze sobą na łódź... Hej chłopcy! Wrzućcie jedną belę jedwabiu na łódź kapitana!";
			link.l1 = "Dobrze. Cóż, zobaczymy się, gdy znajdę kupca!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Coś jeszcze, kumplu?";
			link.l1 = "Nic w tej chwili...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Jak się masz, kumplu?";
			link.l1 = "Świetnie sobie radzę. Znalazłem nam kupca. Dwadzieścia pięć doblonów za beczkę. Wierzę, że Tyrexowi się spodoba.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Nie do wiary! Jesteś przebiegłym synem diabła! Jak ci się to udało, co?";
			link.l1 = "To długa historia, Geffrey. Teraz słuchaj. Powinieneś dotrzeć do Przylądka Negril na Jamajce między 10 a 15. Będą tam na ciebie czekać nocami. Hasło to 'Kupiec z Lyonu'. Zrozumiałeś? Powtórz.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "Handlarz z Lyonu. Rozumiem. Powinienem powiedzieć mojemu kwatermistrzowi, by to zapisał, tylko on tutaj potrafi pisać. Ha-ha!";
			link.l1 = "Czy masz sto rulonów w ładowni?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "Mam jeszcze więcej.";
			link.l1 = "Wspaniale. Czas, byś stawiał żagle. Nie zawiedź mnie!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Odpocznij, kumplu, wszystko będzie zrobione tak, jak powinno być zrobione.";
			link.l1 = "Szczęśliwej drogi, Geffrey. Być może, spotkamy się ponownie.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho-ho-ho! Przebiegły Charlie Prince, we własnej osobie! Miło cię znowu widzieć, stary druhu!";
			link.l1 = "Łysy Geffrey! Mówiłeś, że Charlie Prince? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Nie słyszałem wcześniej twojego drugiego imienia? Tak cię teraz nazywają w La Vega.";
			link.l1 = "Widzę, skąd się wziął Charlie, ale czemu Książę?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Cóż, jesteś jedynym szlachetnym synem suki w La Vega! Ha-ha-ha! Jak się masz? Byłeś w sklepie Pasquale'a? Kupiłeś zapasy od starego łajdaka?";
			link.l1 = "Już nigdy więcej!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Czemuż, nie polubiłeś go? Sprzedał ci soloną wołowinę po cenie rumu?";
			link.l1 = "Gorzej! Dostałem od niego cynk o holenderskiej karawanie załadowanej hebanem. Nie było łatwo ją znaleźć, wejść na pokład kupieckiego statku i potem chronić to cholernie drewno przed kilkunastoma szczurami! I wiesz co, drań zapłacił mi 150 pesos za sztukę. Za sztukę cholernego hebanu, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "To się zdarza cały czas, kolego, zapewniam cię. Lavoisier już oszukał tuzin dobrych chłopaków takich jak ty. Właściwie ci coś zapłacił, co jest u niego rzadkością. Nie bierzemy jego 'wskazówek', nawet jeśli głodujemy.";
			link.l1 = "Dziękuję, przyjacielu, przynajmniej teraz wiem, że nie byłem jedynym i pierwszym idiotą! Ale tym razem drań sam się wkopie. Dopilnuję, by pożałował dnia, w którym mnie zobaczył.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Hej-hej-hej! Czekaj, książę, uspokój się trochę. Ten handlarz jest tutaj nietykalny. Odważysz się go obrabować – Marcus cię dorwie. Powiedz mi, to Tyrex wysłał cię do Lavoisiera?";
			link.l1 = "Hm. Tak... Dlaczego?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Słuchaj... (obniżając głos) Mówią, że czterooki dzieli się z Marcusem. Teraz mnie rozumiesz? Dlatego żaden pirat nigdy nie odważy się zaatakować statków Lavoisiera, bo inaczej będą skończeni.";
			link.l1 = "Zanotowane. Dzięki za ostrzeżenie, Geffrey. Żegnaj i niech Bóg cię prowadzi!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Nawzajem, kumplu.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho-ho-ho, Książę! Zastanawiałem się, kto zrobił te fajerwerki! Przyprowadziłem oddział muszkieterów na wypadek, gdyby to byli Hiszpanie.";
			link.l1 = "Geffrey? Ty też tu jesteś? Ale jak? Czy też kupiłeś mapę skarbu?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Kumplu, nie marnuję swoich pieniędzy na takie bzdury. Dostałem dziennik jakiegoś podróżnika, który pisał o bezpiecznej drodze do tych lochów.";
			link.l1 = "Kto ci to przyniósł?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Jakiś ćpun. Wszystko, czego potrzebował, to sto pesos na drinka.";
			link.l1 = "Czy to stało się na Tortudze?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Nah. To było Barbados? Książę, czemu się tak martwisz? Im nas więcej, tym szybciej przeniesiemy skarby!";
			link.l1 = "To mi się nie podoba. Nie wierzę w takie przypadki. Czyżby to ojciec Camilli napisał ten dziennik?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Kim jest Camilla?";
			link.l1 = "Dziewka, która sprzedała mi mapę tego miejsca za dwieście pesos!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Heh... Książę, za dużo myślisz. Chodźmy na poszukiwanie skarbów. No dalej!";
			link.l1 = "Nie trzeba. Już ich znalazłem... Są na dole w lochu, za żelaznymi kratami. Będziemy musieli je złamać. Posłuchaj Geffrey, jest jeszcze jedna rzecz! Pelly Szabla też tu był!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Szabla? No to mamy szczęśliwy dzień! Ale gdzie on teraz jest?";
			link.l1 = "Na dole... martwy. Spotkałem go niedaleko skarbu. Oszalał, zaczął krzyczeć z chciwości. Potem on i jego towarzysze zaatakowali mnie.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly zawsze miał pecha z pieniędzmi. Musiał oszaleć, widząc tę masę złota.";
			link.l1 = "Może i tak... ale Geffrey, nie pojmujesz! Wszyscy trzej tu dotarliśmy! I wszyscy mamy te same wskazówki! Myślisz, że to przypadek? Ktoś wyraźnie chce nas wszystkich w jednym miejscu, a to miejsce naprawdę przypomina grób.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Widziałeś jednak złoto?";
			link.l1 = "Widziałem to na własne oczy. Kilka olbrzymich skrzyń wypełnionych monetami i sztabami.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "W takim razie, czemu się martwisz, książę? Prowadź, zobaczmy te twoje sztabki. Potem podzielimy się złotem.";
			link.l1 = "Ach, może masz rację, cokolwiek... Chodźmy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            //PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "Co za spektakl! To ogromna kupa złota! Teraz rozumiem, dlaczego Cutlass oszalał. Mamy wielkie szczęście, książę! Jak myślisz, ile złota tu znajdziemy?";
			link.l1 = "Wiele. Dowiemy się na pewno, gdy uporamy się z tymi kratami.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Tak, krata jest bardzo mocna, nie przełamiemy jej gołymi rękami ani mieczami. Masz rację, kumplu - musimy znaleźć jakieś narzędzia albo dużo prochu strzelniczego. Hej, spójrz! Co to jest!?";
			link.l1 = "... ";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"Co za cholerny cymbał!";
			link.l1 = "Ty pieprzona żmijo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Niech mnie rekin pożre, jeśli to się wydarzyło na 'Latającej Rybce' w tym roku... chłopcy, mamy tu gościa! Co takiego złego w twym życiu, że postanowiłeś odwiedzić mój stary koryto?";
			link.l1 = "Witaj! Ty jesteś tym, którego zwą Husky Billy, prawda?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Nie poznajesz głosu, kapitanie? Dawno temu potrafił sprawić, że brytyjscy i hiszpańscy kupcy trzęśli portkami. To były wspaniałe czasy!... Teraz stary Billy czeka na koniec swojego życia u wybrzeży swojej ulubionej wyspy na swojej cennej łodzi...";
			link.l1 = "Mam dla ciebie interes, Billy. Powiedziano mi, że znasz wszystko, co dzieje się tutaj wokół Jamajki. Czy to prawda?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Jeśli tak ci powiedziano, to musi tak być, nie sądzisz? Nie ciągnij kraba za jaja, mów. Jaką masz dla mnie sprawę?";
			link.l1 = "Zgoda. Jest stoczniowiec w Port Royal. Zapewnia swoim klientom specjalne usługi, a do produkcji i owych usług potrzebuje jedwabiu żeglarskiego. Ponieważ handel tym towarem jest tu nielegalny, znalazł sobie nielegalnego dostawcę. Chcę wiedzieć, kto i jak dostarcza mu jedwab żeglarski.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho-ho, spójrz na to! Pracujesz dla pułkownika D'Oyley, synu?";
			link.l1 = "Znowu to samo! Nie, pracuję z Marcusem Tyrexem. On chce udziału w rynku jedwabiu na statkach, a ten budowniczy statków boi się do cholery mieć do czynienia z 'nieznajomymi'...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Och, pracujesz dla Stróża Kodeksu! To wspaniałe wieści... o ile oczywiście nie kłamiesz. Nie obchodzi mnie, że stateczni budowniczowie, aresztuj jednego - przyjdzie inny. Obchodzi mnie moja stara dziewczyna. 'Latająca Ryba' jest w kiepskim stanie. Rozumiesz mnie?\nPrzynieś mi kolejną długą łódź, nową, i rolkę jedwabiu żaglowego, tego samego, o którym mówisz - Billy zrobi z tego porządny żagiel, żeby mógł się bawić z patrolami, ha-ha-ha! W zamian Billy powie wszystko o budowniczym statków i jego źródle jedwabiu. Zaufaj mi, synu, wiem wszystko, co chcesz wiedzieć, po prostu muszę się upewnić, że jesteś uczciwym piratem, a nie jakimś dupoliznym czerwonym płaszczem!";
			link.l1 = "Nowa długa łódź? Co powiesz na to, że dam Ci wystarczająco dużo pieniędzy, abyś mógł ją sam kupić? Dodam nawet coś ekstra.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "He-eh, kapitanie, stary Billy nie jest mile widziany w mieście. Zbyt dobrze mnie pamiętają w Port Royal i nie uśmiecha mi się myśl wiszenia wśród moich starych przyjaciół na tej skale. Więc, synu, czekam, aż dostarczysz mi nową, świeżą szalupę. Będę czekał trzy dni na Przylądku Negril. I nie zapomnij o jedwabiu!";
			link.l1 = "Bardzo dobrze, Billy. Dostaniesz swoją szalupę i rolkę żaglowego jedwabiu. Wrócę wkrótce.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = " Bardzo dobrze, Billy będzie czekał na ciebie na brzegu, kapitanie. Do zobaczenia wkrótce!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "Co? Czy już przyniosłeś mi szalupę?";
			link.l1 = "Jesteś dowcipnisiem, co, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "Więc, kapitanie, co z moją nowiutką łodzią długą?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "Zrobione, Husky. Jest dostarczona wraz z belą jedwabiu okrętowego w jej ładowni. Jesteś wolny, by zatopić swoją starą łódź.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "Jeszcze nad tym pracuję. Poczekaj.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Cholera jasna! To najlepsza wiadomość w ciągu ostatnich pięciu lat starego życia Billy'ego! Heh, dobry powód, by otworzyć tę butelkę...";
			link.l1 = "Podziękuję.  A co z dostawcą jedwabiu?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Szkoda, mogliśmy wypić za mój świeżo zdobyty 'Latający Ryba'! Nieważne... Słuchaj, synu\nBrygantyna pod angielską banderą przypływa do Portland Cove w środku każdego miesiąca, gdzieś pomiędzy 10 a 15 dniem. Żadnego rumu dla mnie aż do śmierci, jeśli ona naprawdę jest angielska! Nazywa się 'Utrecht' i przypływa z południowego-zachodu, gdzie leży Curacao. To wyraźnie holenderski statek kapitanie, możesz to zobaczyć\nZawsze ta sama grupa ludzi spotyka ich na brzegu, prowadzona przez głównego mistrza tego przebiegłego szkutnika. On jest odbiorcą jedwabiu okrętowego, który Holendrzy tam rozładowują. Jestem pewien, że to jedwab okrętowy, ponieważ tylko Holendrzy pakują go w ten sposób.";
			link.l1 = "Co miesiąc, powiadasz?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Rzeczywiście mój chłopcze, ani jednego miesiąca nie opuścili w zeszłym roku. Jeśli chcesz pogadać z tym ponurym brodatym towarzystwem, sugeruję czekać na nich w Portland Cove od 10. do 15. każdego miesiąca, w nocy. Przysięgam na świeżo nowy, jedwabny żagiel mojej długiej łodzi!";
			link.l1 = "Heh! Wygląda na to, że moje pieniądze zostały dobrze wydane. Powodzenia, Billy, dbaj o swoje stare dupsko i unikaj patroli, bo inaczej naprawdę mnie zdenerwujesz.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, stary Billy zamierza zrobić prawdziwą zabawę wzdłuż wybrzeży Jamajki! Powodzenia, kapitanie! Dobrych łowów!";
			link.l1 = "Nawzajem, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Hej, żeglarzu, właśnie przybyłeś na Jamajkę, co?";
			link.l1 = "Hm. Zgadza się. Co się dzieje?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Widziałeś coś, co się wydarzyło na pobliskim morzu?";
			link.l1 = "Aj, mam. Jakaś brygantyna wdała się w bój z angielskim patrolowym korwetą. Brytyjczycy mocno ich uderzyli, Holendrzy pozbyli się ładunku próbując uciec.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Skąd ta pewność, że była Holenderką? Żaden Holender przy zdrowych zmysłach nawet nie pomyśli o zbliżeniu się tak blisko Port Royal...";
			link.l1 = " Miała angielskie barwy, lecz nazwa... 'Utrecht'. Niezbyt brytyjska, co? Mówię ci, byli to Holendrzy, może nawet przemytnicy. Patrol zapewne się ich spodziewał.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Cholera!";
			link.l1 = "Wydaje się, że nie jesteś z tego zbyt zadowolony...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Czekałeś na tę brygantynę tutaj?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Czemu miałbym być?";
			link.l1 = "Chodźże. Wiem, kim jesteś. Jesteś majstrem stoczni w Port Royal i czekasz na bardzo specjalny ładunek, który ma być dostarczony przez brygantynę.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "Masz to wypisane na twarzy, właśnie tam!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Chłopcy, to patrol przebrany za swoich! Wykończcie ich i w nogi stąd!";
			link.l1 = "Cholera! Poczekaj, jesteś wr...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Jesteś niegrzeczny, 'wilku morski'? Uważaj na język, bo...";
			link.l1 = "Chodź. Wyglądasz na wyraźnie zmartwionego. Czy naprawdę czekałeś na przybycie tych Holendrów?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Albo co? Nauczysz mnie lekcji życia?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "A co, jeśli tak było? Dlaczego cię to obchodzi?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Nie, nie do końca. To ty jesteś tutaj tym, kto czeka, nie ja. Masz przed sobą wieczność.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Och, mam wszelkie powody, by się tym przejmować. Wiem, co było w ładowni brygantyny. Jedwab okrętowy. Jesteś tu z tego powodu, prawda?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Wieczność?";
			link.l1 = "Powrót z dna morza trwa wieczność. Twoja brygantyna została zatopiona przez patrolującą korwetę, kumplu. Ot tak. Jednakże wojna przynosi zarówno łupy, jak i straty. Dobrze zarobię na tym zatopionym Holendrze.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = " I jak dokładnie, zastanawiam się?";
			link.l1 = "Sprzedam to, co wyrzucili za burtę, próbując uciec. Prawie wszystko przepadło, ale cenny jedwab ze statku unosił się jak... korek. Uratowałem większość z tego, więc jutro ruszam do miasta, by znaleźć kupca. Nigdy nie wiadomo, gdzie się zyska, a gdzie straci.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Czekaj!";
			link.l1 = "Caramba!  Co teraz?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Ile jedwabiu udało ci się zebrać?";
			link.l1 = "I dlaczego cię to obchodzi? To moje jedwabie! A może jesteś psem gubernatora? Ty jesteś de...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Trzymaj miecz w pochwie, żeglarzu. Nie jestem psem i nie jestem donosicielem. Pracujemy w lokalnej stoczni... Ten jedwab był dla nas i o ile rozumiem, teraz masz go ty. Kupię go całego od ciebie, potrzebujemy tego jedwabiu, kumplu.";
			link.l1 = "Naprawdę? Interesujące... Ile?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Dwa tysiące pięćset za rolkę. To dobra cena, lepszej nie znajdziesz.";
			link.l1 = "Wygląda na to, że mi się poszczęściło! Mam "+FindRussianQtyString(i)+"Pokaż mi pieniądze, a rozkażę dostarczyć je na brzeg natychmiast.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Umowa stoi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachim miał dostarczyć tylko osiemdziesiąt bel - nie ma mowy, żebyś mógł tyle zdobyć... co oznacza, że albo próbujesz grać nieczysto, albo... jesteś kapusiem! Chłopcy, zabijcie go i wynośmy się stąd!";
			link.l1 = "Cholera!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Znakomita transakcja, kumplu! Czemu taki ponury? Martwisz się o Holendrów na dnie morza? Gówno się zdarza, nie przejmuj się tym!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Tak, jasne... Byli naszymi stałymi dostawcami. Skąd teraz mamy wziąć jedwab? Zawsze go brakuje, a cały handel jest pod bezpośrednią kontrolą pułkownika D'Oyley. Cholera jasna...";
			link.l1 = "Hm... Słuchaj, przyjacielu, przypuszczam, że mogę ci w tym pomóc.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Naprawdę? A jak sobie wyobrażasz, że nam pomożesz? Będziesz dostarczał nam co miesiąc partię stu bochenków?";
			link.l1 = "„Ja? Hmm, raczej nie, ale Marcus Tyrex by tak zrobił. Słyszałeś o nim?”";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! Więc, jesteś piratem?";
			link.l1 = "Nie, tylko załatwiam z nimi interesy przy specjalnych okazjach. Wiem na pewno, że Marcus regularnie otrzymuje partie jedwabiu okrętowego i sprzedaje je każdemu, kto może sobie na to pozwolić. I nie mówię tutaj o 2500 peso za rolkę, powiedziałbym, że jeśli możesz zapłacić mu 25 dublonów w złocie za każdą rolkę, to cię w nich utopi, możesz na to liczyć.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "To są interesujące wieści... Marcus Tyrex powiadasz? Tylko w dublonach?..";
			link.l1 = "No dawaj, kumpel, czy naprawdę ma dla ciebie znaczenie, od kogo dostajesz swój jedwab? A pieniądz to pieniądz, zawsze możesz wymienić peso na dublony w banku. To co, mam szepnąć o tobie słówko czy dwa w uszy strażnika kodeksu? I tak jadę do La Vega.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Bardzo dobrze. Zróbmy interes. Oto nasze warunki: partia stu zwojów co miesiąc między 10 a 15. Będziemy tu czekać... czekaj, zmieńmy miejsce spotkania, to miejsce jest teraz zagrożone. Będziemy czekać na Przylądku Negril, w pobliżu miasta Maroon, tam powinno być bezpieczniej. Hasło - 'Kupiec z Lyonu'.";
			link.l1 = "Umowa stoi, przyjacielu. Co za piekielna podróż to była! Tyrax zapłaci mi dukata lub dwa za takiego kupca! Ha-ha! Bardzo dobrze, muszę iść. Czekaj na statek Tyraxa w przyszłym miesiącu. Powodzenia tobie i twojej rodzinie!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "Nie będziecie potrzebować żadnych lekcji życia, gdy nauczymy was, jak być grzecznym.";
			link.l1 = "Gryziesz się, cieślo? Dobrze, czekaj na swoją brygantynę, choć to potrwa.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Hej, nauczycielu, mam dla ciebie kilka lekcji również!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Stolarz? Do diabła, skąd wiesz? K-ha! Cholera, chłopaki, to patrol w przebraniu! Zabijcie go i wynośmy się stąd!";
			link.l1 = "Cholera!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Odczep się, ty rybia łusko, nie mamy czasu. Spadaj!";
			link.l1 = "Czy jesteś zajęty czekaniem na pewien holenderski statek? Powodzenia z tym. Masz przed sobą wieczność.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "Czego do diabła mówisz?";
			link.l1 = "Rozumiem. Ale na wypadek, gdybyś jednak czekał, zapomnij o tym. Nie przypłynie dzięki patrolowej korwecie. Przez lunetę widziałem koniec walki. Stało się to tak szybko i niedaleko stąd.";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Znów na nic ani na nikogo nie czekamy i...";
			link.l1 = "Patrz, naprawdę mnie to gówno obchodzi. Nie należę do straży miejskiej i nie interesują mnie twoje sprawki, sam nie jestem aniołem. Jeśli przemycasz - to twoja sprawa. Chciałem tylko cię ostrzec. Powodzenia, kumplu.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Czekaj... Czy jesteś pewien, że 'Utrecht' zatonął?";
			link.l1 = "Absolutnie. Próbowała uciec, wyrzuciła wszystko, co miała w ładowniach, nawet nie oszczędzili cennego jedwabiu okrętowego, ale takie drastyczne środki nie mogły pomóc przeciwko przewadze korwety w prędkości.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Co za szkoda... i co mamy zrobić bez jedwabiu? Do diabła!";
			link.l1 = "Czy potrzebujesz jedwabiu okrętowego?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Dlaczego pytasz, sprzedajesz to?";
			link.l1 = "Nie jestem, ale znam człowieka, który jest. Szuka hojnego i stałego kupca. Myślisz, że możesz się nadać?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "A kimże jest ten człowiek?";
			link.l1 = "Marcus Tyrex, baron La Vega, lepiej znany jako Strażnik Kodu. Stale otrzymuje partie jedwabiu okrętowego, więc zawsze ma coś na sprzedaż. Przypuszczam, że rozważy sprzedaż tobie również, jeśli zapłacisz wystarczająco dużo.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Więc jesteś piratem?";
			link.l1 = "Co cię to obchodzi? Mogę zorganizować umowę między tobą a Tyram, jeśli masz odwagę. Jeśli nie - żegnaj wtedy.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Dobrze, dobrze, nie złość się. Jasne, że tak. Chcę ubić interes z Tyreksem. Ale co ty z tego będziesz miał?";
			link.l1 = "Jeśli zaoferujesz dobrą cenę za ładunek, prawdopodobnie dostanę od Markusa przyzwoitą sumę za moją pomoc. Więc jak będzie?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Dwadzieścia pięć doublonów za rzut. To najlepsza cena, jaką możesz dostać, uwierz mi na słowo.";
			link.l1 = "Dwadzieścia pięć złotych monet? Hm. Nieźle. Wierzę, że Tyrex będzie mi dużo winien za takiego kupca. Bardzo dobrze, powiadomię go. Jednakże, jeśli skłamałeś mi o cenie, to twoja dupa będzie na szali.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Nie martw się, jesteśmy uczciwymi ludźmi. Oto nasze warunki: partia stu rulonów każdego miesiąca między 10 a 15. Będziemy czekać tutaj... czekaj, zmieńmy miejsce spotkania, to miejsce jest już spalonym. Będziemy czekać na Przylądku Negril, niedaleko Maroon, tam powinno być bezpieczniej. Hasło - 'Kupiec z Lyonu'.";
			link.l1 = "Zrozumiałem. Czekaj na pierwszą partię w przyszłym miesiącu.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Powiedz Tyreksowi, że może przywieźć więcej ładunku tym razem, zostaliśmy bez jedwabiu na ten miesiąc.";
			link.l1 = "Zrobię to. Niech ci sprzyja wiatr, przyjacielu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Ahoy! Co cię sprowadza na pokład mojej łajby, przyjacielu?";
			link.l1 = "Hej, Szabla. Marcus Tyrex mnie przysłał. Marsz do Maracaibo na nas czeka.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, nareszcie. Więc to ty musisz być moim nowym szefem na tę podróż. Dobrze. Jak się nazywa mój nowy admirał?";
			link.l1 = "Kapitan "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Rozkazy, Admirale "+GetFullName(pchar)+"?";
			link.l1 = "Popłyniemy osobno do Jeziora Maracaibo. Powinieneś tam dotrzeć nocą i potajemnie wylądować w Zatoce Guajira. Poczekaj tam na mnie, a w międzyczasie załóż mały obóz. Ja natomiast wyląduję w hiszpańskim porcie.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Aye-aye, Admiral!";
			link.l1 = "Ile czasu zajmie ci dotarcie tam?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... Powinno to zająć około tygodnia. Dzień mniej, dzień więcej, wszystko zależy od wiatru.";
			link.l1 = "Dobrze. Nie traćmy więc czasu. Do zobaczenia w Zatoce Guajira, przyjacielu.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Tak jest, admirale!";
			link.l1 = "... ";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Rozkazy, admirale?";
			link.l1 = "Nic w tej chwili. Jestem zajęty naszą operacją.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Przygotujcie pojemną skrzynię na brzegu. Będziemy do niej zbierać broń dla naszych uwięzionych braci.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "Więc, co z tym Przystojniakiem? Ręce mnie świerzbią, by przelać trochę krwi Donów!";
				link.l1 = "To bardziej skomplikowane niż myśleliśmy. Powiedział, że strażnicy na plantacji są zbyt czujni. Jedynym sposobem na przemycenie broni jest ukrycie jej w towarach. Musimy pilnie zdobyć przesyłkę kawy, kopry lub wanilii - lokalny plantator handluje tylko tymi towarami i niczym innym.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Opuść obóz i zgromadź oddział szturmowy. Czas ruszać, atakujemy pod osłoną ciemności.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Słuchaj, Admirale, myślałem...";
			link.l1 = "Co to, Terrax płaci ci za myślenie zamiast machania tą szablą, co, Cutlass?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Ho! Bunt na plantacji, czyż nie, admirale? Płomienie! Zdobędziemy z tego trochę złota!..";
			link.l1 = "Potrzebuję skrzyni na brzegu, Cutlass.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Natychmiast, Admirale!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Natychmiast, Admirale!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Ludzie są gotowi i przygotowani, admirale!";
			link.l1 = "Naprzód!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Admirale, wygląda na to, że przyjaciel Tyrexa, którego mieliśmy uratować, jest... w pewnym sensie martwy.";
			link.l1 = "Tak, ale nic nie dało się tam zrobić. Widziałeś strażników, mieliśmy szczęście, że przeżyliśmy.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Admirale, Marcus będzie na ciebie wściekły. Nie idź do niego teraz. Ja odlatuję. Ty też powinieneś.";
			link.l1 = "Tak...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Złe wieści, Admirale. Od wschodu nadciąga na nas hiszpańska eskadra. Nie mamy czasu na ucieczkę.";
			link.l1 = "Ilu ich jest?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Trzy statki. Mnóstwo dział. Jesteśmy w dupie."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Zobaczymy.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean, idź na statek Cutlassa.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Cutlass, powinieneś wznieść hiszpańską flagę i wynosić się stąd do diabła. Odciągnę ich od ciebie. Zobaczymy się wszyscy w La Vega.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "Ale...";
			link.l1 = "Żadnych ale! Szabla, to twoja skóra na szali, jeśli Picard nie dotrze na miejsce Tyrexa. Wszyscy na pokład!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Rozkazy, Admirale?";
			link.l1 = "Szykujcie się do walki. Atakujcie na mój rozkaz!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Tak jest, Admirale... na twój rozkaz!";
			link.l1 = "... ";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho-ho! Witaj, Książę. Co cię sprowadza na Tortugę?";
			link.l1 = "Zadanie od Markusa znowu. Słuchaj, Szabliński, dlaczego ten drań, co mieszka w tym domu, nie wpuszcza mnie?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Złotezęby? On pracuje tylko z zaufanymi kompanami. Inni potrzebują rekomendacji, by z nim współpracować. Chcesz sprzedać jakieś błyskotki? Mogę za ciebie poręczyć, jeśli chcesz...";
			link.l1 = "Więc on jest lichwiarzem? Jakie ma procenty?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Bracie, czegoś ci brakuje. Gaspard to nie lichwiarz, powinieneś iść do "+GetFullName(characterFromId("Tortuga_usurer"))+" jeżeli potrzebujesz. Złotouz kupuje kamienie szlachetne i biżuterię wszelkiego rodzaju. Przy okazji, dobrze płaci i nigdy nie zadaje głupich pytań. Każdy kapitan pirat jest jego klientem.";
			link.l1 = "Widzę... Powiedziano mi, że niektórzy nawet powierzają mu swoje pieniądze...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha! To kłamca ci to powiedział, idź i napluj mu w bezwstydne oczy. Gaspard zajmuje się tylko biżuterią, zawsze tak było. Po co mu kłopoty z cudzymi pieniędzmi?";
			link.l1 = "Rozumiem. Dziękuję, Szabla, do zobaczenia na morzu!";
			link.l1.go = "Pelly_27";
			link.l2 = "Hmm, rzeczywiście. Więc, kupuje błyskotki? Interesujące... Mówisz, że możesz za mną poręczyć?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "Do zobaczenia, Książę.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Oczywiście! Jesteś teraz jednym z nas, hehe! Zaczekaj tu chwilę.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Wszystko jest załatwione! Teraz Złotozębny wie, że Charlie Prince może do niego przyjść, aby sprzedać świecidełka. Pamiętaj tylko, że jego cena, choć dobra, jest wciąż niższa niż to, co płacą ci skąpi lichwiarze. Ale on kupuje wszystko na tony! I bez zbędnych pytań, jak już mówiłem.";
			link.l1 = "To mój przystojny chłopak! Świetna robota, Paul! Teraz mam miejsce, żeby wyładować cały łup!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "Nie, Jean Picard to 'Przystojniak', ja jestem 'Szabla', haha! Żegnaj, Książę!";
			link.l1 = "Dzięki, Szabla, powodzenia na morzu!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "Mam dla ciebie trzy ptaszyny, książę. Znalazłem je chowające się w szafach i pod łóżkiem. Ładne, co? Ha-ha-ha!";
			link.l1 = "Rzekłbym, że rzeczywiście tak jest. I są również dobrze zadbane. Don Uparty musi się o nie bardzo troszczyć.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Alle hagel! Co do cholery robisz tutaj, Książę?";
			link.l1 = "Szabla?.. Podążałem za głosami i hałasem, ale nigdy bym nie pomyślał, że to będziesz ty. Jak do diabła tutaj trafiłeś?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "Nie, dlaczego tu jesteś! Zawsze kręcisz się wokół! Tyrax musiał cię wysłać po ten skarb, prawda? Caramba, znowu jestem spóźniony...";
			link.l1 = "Tyrax? Nie... Kupiłem mapę od jednej dziewki. Pewnie sprzedała ci kopię, co? Na Tortudze? Co za przebiegła suka. Ale nie kłamała - spójrz na tę kupę złota! Wrócę z większą ekipą, żeby to wszystko przetransportować...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Do diabła, to kupa złota! Ale nie twoja ani Tyreksa! To ja ją znalazłem pierwszy! Jest moja! Nie ma znaczenia, jak się o niej dowiedziałem! To nie twoja sprawa!";
			link.l1 = "Spokojnie, Szablo, czemuś tak wściekły? Spójrz na tę kupę - musi tam być milion. Może nawet więcej! Wystarczy dla nas obu!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Zawsze dostajesz lepszy kawałek tortu, Książę! Ale nie tym razem! Skarb jest mój! Ja go znalazłem pierwszy!";
			link.l1 = "Do cholery, Paul, co z tobą nie tak? Czy nie możemy się tu dogadać? Nawet połowa tego złota to fortuna. Nigdy wcześniej nie miałeś takiej sumy w rękach. Poza tym mogę pewnego dnia znaleźć dochodowy trop i ci o nim powiedzieć.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Chcesz mnie rozwalić, Książę? Nie ma mowy! Nie dam ci ani monety, ani jednego ginea! Jesteś spóźniony!\nA-ah, widzę, co kombinujesz! Nie ma mowy, że dostaniesz to złoto!!!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Zabawne. Naprawdę. Jesteś komikiem, admirale. Ale to prawda - Marcus nie lubi tych, którzy próbują go przechytrzyć, jak ty. Ale ceni sobie sprytnych ludzi.";
			link.l1 = "Dobrze, dobrze. Więc, co ci chodzi po głowie?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Coś, czego ty i Przystojniak wyraźnie nie uwzględniliście. Planowaliście bunt na plantacji. Świetny pomysł - jeśli celem było łupienie lub sianie chaosu. Ale...";
			link.l1 = "Ale co? Ty przeciwko buntowi? Przerażające?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Ja? Ha! Nigdy. Ale pomyśl, co się stanie, jeśli Przystojniak zginie podczas rzezi. Co powiemy Marcusowi? Powiem ci co - nie będzie miało znaczenia, co powiemy. I tak nas obedrze ze skóry.";
			link.l1 = "Hmm. Więc jaki jest twój genialny plan? Musimy go jakoś wydostać.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "Mamy. Dlatego... dlaczego go nie kupić? Oficjalnie, to jest. Garść złota może kupić każdego z tych drani - nawet ich własne matki. Co tu mówić o biednym Jeanie?";
			link.l1 = "Ha! Szabla, czy naprawdę sugerujesz, że mam wejść na plantację i zapytać o kupno Picarda? Czy powinienem też powiedzieć im, dla kogo pracuję, dla zabawy? Straciłeś rozum?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "Nie trzeba tego mówić. W rzeczywistości, wręcz przeciwnie - udawaj kupca. Oczywiście, nie masz do tego smykałki, ale nie wyglądasz też jak pirat. Bez urazy, Admirale, ale taka jest prawda. Po prostu wkrocz na tę plantację, zachowuj się pewnie i zapytaj o Jeana. Właściciel może się domyśleć, kim jesteś, ale tego nie pokaże. Jak mówiłem - garść złotych zamyka usta.";
			link.l1 = "I ile by nas kosztowała ta... ręka złota? Cała góra?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Może i tak. Ale lepiej rozstać się ze złotem niż z głową. Nie próżnowałem, gdy byłeś na lądzie - przebrałem się w coś mniej pirackiego i wypytałem o plantację i jej skromnego właściciela.";
			link.l1 = "A co znalazłeś, Szablo?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Można rzec, ceny rynkowe. To nie pierwszy raz, gdy cenny więzień trafia w jego ręce. Zwykle kończą na szubienicy lub, co gorsza - w lochach Inkwizycji.";
			link.l1 = "I za ile je sprzedaje?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "Za kogoś ważnego? Pięćset monet. W dublonach, oczywiście.";
			link.l1 = "PIĘĆSET?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Plantatorzy, czego się spodziewaliście?";
			link.l1 = "Za tę cenę mógłbym wyposażyć małą armię! Czemu do diabła gromadzę na statku arsenał na bunt? Tego wystarczy na małą wojnę.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "Broń przyda się twojej załodze później, bez względu na wszystko. Więc, co powiesz?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(Godny zaufania) Powiem tylko, że będzie zabawnie, jeśli nagroda od Terraxa będzie mniejsza niż to, co tu wydajemy. Ale masz rację - nasze życie jest warte więcej. Mam dubloony.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "Nie mam teraz takiej złotej góry.";
				link.l2.go = "Pelly_44_1";
				notification("Trustworthy", "Trustworthy");
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "Wiesz co, Cutlass? Zapomnij o tym. Jesteśmy piratami, czy nie? A Jean? Czy jego ładna buźka to jedyny jego atut? Przygotuj skrzynię - trzymamy się oryginalnego planu.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "Byłbym zaskoczony, gdybyś to zrobił - to ogromna suma. Dobrze, kiedy będziesz gotowy, lub jeśli wymyślisz coś lepszego, znajdź mnie.";
			link.l1 = "Zrobię to. Czekaj tutaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Cóż, Admirale, czy zebrałeś wystarczająco złota, by uratować Picarda?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Tak, w końcu to zrobiłem. Miejmy nadzieję, że to zadziała.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "Jeszcze nad tym pracuję, Szabla.";
			link.l2.go = "exit";
			link.l3 = "Nie oddam moich ciężko zarobionych pieniędzy tym chciwym plantatorom! Przygotujcie skrzynię - będziemy działać jak Dżentelmeni Fortuny. To moja decyzja.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Oho. Jesteś nowy w naszej załodze, a już rzucasz się na takie pieniądze!";
			link.l1 = "Pieniądze to nie wszystko. Ale pławić się w chwale Terraxa? Bezcenne.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "Nie mogę z tym dyskutować. Ale jak powiedziałeś, tu nie chodzi tylko o pieniądze - jest coś jeszcze ważnego, Admirale.";
			link.l1 = "Teraz jestem ciekawy. Co takiego?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "Powiedziałem ci, że zbadałem wszystko o plantacji. Włącznie z tym, jakie towary są tu poszukiwane i krążą na rynku. Jeśli chcesz uchodzić za legalnego handlarza, lepiej zaopatrz się w nie, zamiast po prostu rzucać stos złota na biurko plantatora.";
			link.l1 = "Ma sens. O jakiego rodzaju towarach mówimy?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Cóż, poza żywymi towarami, heh-heh, lokalny właściciel plantacji kupuje, handluje i odsprzedaje kawę, coprę i wanilię. Więc...";
			link.l1 = "Muszę gdzieś szybko uzupełnić zapasy. Albo napaść na karawanę i mieć nadzieję, że przewozi to, czego potrzebuję.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Nie byle jaka karawana. Niechętnie się z nią rozstaję, ale mam dla siebie jedną wskazówkę. Wkrótce pojawi się karawana niosąca dokładnie to, czego potrzebujesz. Ale jest pewien haczyk...";
			link.l1 = "Och, co teraz?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "Pod francuską banderą.";
			link.l1 = "Co?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "Rozumiem twoją frustrację, ha-ha. Decyzja należy do ciebie... Admirale. Chcesz szczegóły?";
			link.l1 = "Cholera... Dobrze, mów wszystko. Nie mamy wiele czasu - jeśli ty albo ja się nimi nie zajmiemy, ktoś inny to zrobi.";
			link.l1.go = "Pelly_52";
			// link.l2 = "Nie ruszam Francuzów, chyba że nie mam innego wyboru. Koniec dyskusji.";
			// link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "To lepiej zacznij sam zbierać te towary i to szybko, zanim Piękniś zostanie sprzedany komuś. Nie mogę tu też wiecznie czekać.";
			link.l1 = "Tak właśnie myślałem.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_52":
            dialog.text = "Tak mi się podoba! Wiedziałem, że masz to w sobie... Admirale. Więc, oto umowa: mój zaufany kontakt doniósł niedawno, że za około dwa tygodnie, francuska karawana przewożąca kawę i przyprawy pojawi się na wodach Gwadelupy. Jest duża i dobrze uzbrojona, więc przygotuj się dokładnie.";
			link.l1 = "Jakie mam inne wyjście.";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "Wyglądasz na przygnębionego, Admirale. Gdzie jest Przystojniak? Czy wszystko poszło na marne?";
			link.l1 = "Rzeczywiście. Zarobiłem przyzwoite pieniądze, ale ten uparty muł odmówił sprzedaży mi Picarda - nawet za stertę dublonów!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "Co za głupiec! Co teraz?";
			link.l1 = "Już się dogadałem z plantatorem, żeby rozładować towary. Musimy wrócić do pierwotnego planu - teraz albo nigdy!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "Ale przecież nie przygotowaliśmy jeszcze niczego dla Przystojnego i reszty!";
			link.l1 = "Nie ma czasu! Na pokład statków - przemycimy broń i medykamenty z naszych ładowni do worków z towarem. I nie zapomnijcie podnieść hiszpańską flagę!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Brzmi jak plan.";
			link.l1 = "W każdym razie nie mamy czasu na nic innego. Ruszaj się! Rozładunek wkrótce się zacznie.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Spójrz, kto to jest! Przystojniak! I sądząc po twojej nienaruszonej twarzy i pewnym kroku, rozumiem, że wszystko poszło gładko?";
			link.l1 = "Płynnie to mało powiedziane - nie tylko uniknąłem walki i wykupiłem Jeana, ale też zarobiłem trochę pieniędzy. Twój plan zadziałał bezbłędnie, Paul. Wszystko cicho na horyzoncie?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "Cicho jak makiem zasiał. Wracasz do Markusa?";
			link.l1 = "Dobrze.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("shore37", "boat", false);
			bQuestDisableMapEnter = false;
			AddQuestRecord("Roger_3", "29");
			pchar.questTemp.Mtraxx = "plant_success";
			QuestSetCurrentNode("Terrax", "mtraxx_27");
			//SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
			SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);
			
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			
			sld = &Locations[FindLocation("shore37")];
			sld.DisableEncounters = false;
			sld = ItemsFromID("fire");
			sld.shown = false;
			DeleteAttribute(sld, "fire");
			for (i=1; i<=4; i++)
			{
				if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
				{
					sld = characterFromId("Pelly_sailor_"+i);
					sld.lifeday = 0;
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
				}
			}
			sld = characterFromId("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 5);
			sld = characterFromId("mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
		break;
		
		case "Pelly_62":
            dialog.text = "Hmm, jak sobie życzysz, Admirale. Ale jeśli coś się stanie Przystojnemu, upewnię się, że Terrax dowie się, że zignorowałeś moją radę. Wszystko gotowe do ucieczki?";
			link.l1 = "Pozwól, że jeszcze raz sprawdzę i policzę, co mam w skrzyni.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Upewnij się o tym. Mogę pomóc za skromną opłatą, by pokryć moje wysiłki, heh-heh.";
			link.l1 = "Jak tam?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "Mam kontakt, handlarza bronią w Maracaibo. Przebiorę się, wkradnę, zapłacę mu i zorganizuję przemyt broni tutaj. Ale to cię będzie kosztować - złote dublony, żeby być dokładnym.";
			link.l1 = "A dlaczego nie przedstawiłeś mi tego gościa wcześniej? Ile mnie to będzie kosztować?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Czy powinienem przedstawić ci wszystkich moich informatorów również? Dobrze. Z wydatkami, ryzykiem i moim udziałem... to kosztuje mniej więcej tyle samo co okup za Przystojnego.";
			link.l1 = "Szabla, bój się Boga...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "Nie lękam się ani Boga, ani ciebie, Admirale. Ale gniew Marcusa, jeśli nie uratujemy Jeana? To już inna historia. Więc, jak będzie? Potrzebujesz pomocy z kufrem?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "W porządku, idź naprzód - już wystarczająco dużo czasu zmarnowano. Oto, to powinno być odpowiednią ilością.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "To dużo pieniędzy, Paul. Muszę to przemyśleć.";
			link.l2.go = "Pelly_67";
			link.l3 = "To stanowczo za drogo za małą partię broni, którą mogę kupić hurtowo znacznie taniej! Nie, dziękuję, poradzę sobie sam.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Cóż, myśl sobie. Ale pamiętaj-podczas gdy myślisz, liczba siniaków na twarzy i ciele Przystojniaka rośnie z każdą godziną, heh-heh-heh.";
			link.l1 = "Dostanę ci te dublony...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "Nie chodzi o wielkość ładunku-chodzi o czas i ryzyko. Ale rób, jak uważasz.";
			link.l1 = "Zaufaj mi, wiem. Przygotuj tylko skrzynię - dalej zajmę się tym sam.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Gotowy, Admirale? Potrzebujesz pomocy z bronią czy nadal brakuje ci złota?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "W końcu wystarczy! Weź to i załatw to już - działa mi to na nerwy.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Zważaj na ton, Cutlass. Jestem gotów, ale potrzebuję więcej czasu, aby zebrać pieniądze.";
			link.l2.go = "Pelly_67";
			link.l3 = "To zbyt drogie za niewielką partię broni, którą mogę kupić hurtowo znacznie taniej! Nie, dzięki, poradzę sobie sam.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "O, co za ładunek dublonów! Ale nie martw się - każda moneta pójdzie na plan. Inaczej Marcus wykopałby mnie z grobu później, heh-heh. Teraz, idź do Przystojnego, Admirale, i powiedz mu, że wszystko jest gotowe.";
			link.l1 = "To ja tu wydaję rozkazy. A teraz, ruszaj się.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Tak, to problem. Jaki masz plan, Admirale?";
			link.l1 = "Muszę gdzieś szybko uzupełnić zapasy. Albo napaść na karawanę i mieć nadzieję, że przewozi to, czego potrzebuję.";
			link.l1.go = "Pelly_49";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "Czego ode mnie chcesz?";
			link.l1 = "Mój przyjacielu, szukam Jeana Picarda. Czy przypadkiem nosisz to samo imię?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "Jest szansa. Jednakże, nie przypominam sobie twojej twarzy.";
			link.l1 = "Nie bądź zbyt szorstki, Jean. Zostałem tu przysłany przez Marcusa Tyrexa. Moim rozkazem jest wyciągnąć cię stąd.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Cicho... Cicho. Przykro mi, przyjacielu, nie wiedziałem o tym. Ale nie powinniśmy tu rozmawiać, cholerni strażnicy są wszędzie i zawsze nasłuchują... Widzę, że jesteś mile widzianym gościem wśród Hiszpanów, znajdź mnie w jednej z chat wieczorem i porozmawiamy. Będę na ciebie czekał, bracie.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Cóż, tutaj jest bezpiecznie... Jak masz na imię, bracie?";
			link.l1 = "Kapitanie "+GetFullName(pchar)+"Teraz powiedz mi, jak wpakowałeś się w to gówno. Tyrex chce wiedzieć wszystko.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Podszedł do mnie nieznajomy w tawernie w Willemstad... Poprosił mnie, bym został jego towarzyszem w grabieniu jakiegoś holenderskiego karawanu. Miałem brygantynę, on miał polakrę, bardzo wyjątkową zresztą. Więc ścigaliśmy karawanę niedaleko Caracas i ją splądrowaliśmy... Była noc, dzieliliśmy łupy, gdy w ciemności pojawiła się ogromna hiszpańska galeona\nMój towarzysz uciekł i ja również. Ale nie było szans, by moja uszkodzona brygantyna uciekła przed galeoną i dwoma innymi okrętami. Zajęli nas i sprzedali wszystkich ocalałych do tego miejsca jak bydło.";
			link.l1 = "Rozumiem. Myślisz, że to był wypadek? Mówię o galeonie.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Cholera wie, jeśli bym wiedział. Mogli usłyszeć strzelaninę, to nie było daleko od Głównej.";
			link.l1 = "Hmm. To możliwe. Spotkałeś wcześniej swojego byłego towarzysza? Kim on jest?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Nie spotkałem go wcześniej. Powiedział, że nazywa się Ignacio Marco, korsarz Anglii. Sprawił wrażenie poważnego człowieka, dlatego zgodziłem się wziąć udział w tej przedsiębiorczości. Jest doświadczonym żeglarzem i kapitanem, to pewne, ma załogę pełną śmiałków, a jego polakra to piękność, nie co dzień można zobaczyć taki statek.";
			link.l1 = "Ignacio Marco? Angielski kaper? Czy on jest Hiszpanem?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "On jest Portugalczykiem, nie Hiszpanem. Co złego w brytyjskiej kaperskiej licencji? Mamy wielu Hiszpanów wśród nas, wiesz o tym.";
			link.l1 = "Widzę. Dobrze, porozmawiajmy o twojej ucieczce stąd. Jakieś pomysły?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Jakie są twoje liczby?";
			link.l1 = "Moja łajba, barkentyna i ludzie Pelly'ego Szabli. Moja jednostka stacjonuje w porcie Maracaibo. Szabla wylądował w Zatoce Guajira i założył tam obóz.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hmm...";
			link.l1 = "Cóż, spodziewałeś się, że Tyrex wyśle tutaj okręt liniowy?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Nie spodziewałem się niczego. Właściwie, jestem zaskoczony, że Marcus o mnie nie zapomniał.";
			link.l1 = "Nie zrobił tego, oczywiście. Więc, jakieś pomysły?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "Nie ma szans na ucieczkę stąd - ta plantacja jest zbyt dobrze strzeżona, a wokół są dzikie dżungle. Nie ma sensu jej szturmować, nie masz wystarczająco ludzi, a w pobliżu jest fort.";
			link.l1 = "Może ty i twoi chłopcy możecie nam pomóc od środka? Uderzcie ich mocno od tyłu.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Z czym? Gołymi rękami i zardzewiałymi maczetami?";
			link.l1 = "A co, jeśli miałbyś broń?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "W takim razie dalibyśmy im piekło. Jest jednak problem, sprawdzają wszystko, co przynosisz do środka, nie ma sposobu na przemycenie broni. Sugeruję więc, by o tym zapomnieć.";
			link.l1 = "I mimo to, to nasza najlepsza opcja na ten moment. Pomyślę, jak dostarczyć wam i waszym ludziom broń... Powiedz mi, ilu z was jest zdolnych do walki?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Trzydzieści głów, powiedziałbym.";
			link.l1 = "Trzydzieści szabel zatem... Pistoletów też by się przydało, jak mniemam.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Kapitánie, czy naprawdę masz zamiar to zrobić?";
			link.l1 = "Jestem. Przybyłem tutaj celowo, żarty nie są częścią tego. Czego jeszcze mógłbyś potrzebować?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Bardzo dobrze... Przynajmniej spróbujmy. Potrzebujemy prostego zimnego żelaza - moi chłopcy nie są wyszkoleni do pracy z wyszukanymi rapierami i tym podobnymi. To samo można powiedzieć o pistoletach, najtańsze będą w sam raz. Jeśli zdobędziesz dla nas muszkiet lub dwa, bardzo by nam to pomogło, mam kilku chłopców, którzy dobrze radzą sobie z muszkietami. Kule, proch strzelniczy. Mikstury lecznicze są najbardziej pożądane.";
			link.l1 = "Zrozumiano. Ostrza i topory można zabrać z arsenału na statku. Resztę trudniej zdobyć. Dam ci znać, gdy wszystko będę miał.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Proszę, pospiesz się, bracie. Nie mamy tu pół roku, ta cholernie niewolnicza praca zabija nas jednego po drugim. Jeśli będziesz mnie potrzebował - przyjdź do mnie w nocy.";
			link.l1 = "Zrozumiałem, kumplu. Trzymaj się, postaram się nie kazać ci długo czekać. I uważaj, nie dawaj im jeszcze powodu, by cię skreślili.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Jakieś wieści, kamracie? Zgromadziłeś broń?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Tak. Skrzynia z amunicją jest w Zatoce Guajira. Teraz trzeba tylko znaleźć sposób, by przemycić ją na plantację.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Zaraz się tym zajmę. Czekaj.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Bardzo dobrze, kapitanie. Już myślałem, jak to wykonać.";
			link.l1 = "Cieszę się, że to słyszę. Co masz na myśli?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "Na tej plantacji produkują cukier i uprawiają ziarna kakaowe. Czasem jej właściciel sam sprzedaje towar, tak jest bardziej opłacalne. Złóż mu ofertę. Zapłać nie pieniędzmi, a towarem. Coś, co można zapakować w skrzynie jak kopra, wanilia czy kawa. Włóż trochę wysiłku w targowanie, ale nie przesadzaj\nUkryj broń w jednej lub dwóch skrzyniach i oznacz je. Umów się na wymianę wieczorem, żeby musieli zostawić skrzynie na zewnątrz na noc\nW nocy znajdziemy twoje oznaczone skrzynie, uzbroimy się i damy Hiszpanom popalić. Oczywiście z twoją pomocą.";
			link.l1 = "Świetna myśl, bracie! Bardzo dobrze, podoba mi się ten plan. Trzymajmy się go.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "Jeszcze jedna rzecz - oferuj tylko jeden rodzaj towarów do wymiany. Więcej rodzajów towarów - więcej skrzyń sprawdzanych przez strażników.";
			link.l1 = "Zgadzam się. Wybiorę więc tylko jeden typ. Kawa, wanilia i kopra, tak powiedziałeś?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Tak. To będzie brzmiało jak dobry interes dla szefa plantacji.";
			link.l1 = "Zrozumiano. Dam ci znać, gdy umowa zostanie zawarta.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Idź, mój przyjacielu, czas to złoto, a my go nie mamy...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "... ";
			link.l1 = "(cicho) Układ został zawarty. Skrzynie zostaną dostarczone na plantację jutro wieczorem. Skrzynie, których potrzebujesz, są oznaczone literą 'W'. Na pozostałych jest reszta alfabetu. Przygotuj swoich ludzi. Zaatakujemy przed świtem około trzeciej.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "Zaczniemy na twój sygnał...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Wreszcie! Zaraz znów ujrzę morze! Już zapomniałem, jak wygląda i pachnie. Dobrze zrobione, kapitanie! Jestem ci dłużny.";
			link.l1 = "Nie martw się tym, załatwimy to później... Teraz wsiadamy na pokład i wynosimy się stąd!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Witaj "+pchar.name+" Cieszę się, że znów cię widzę, cieszę się również, że jesteś moim towarzyszem w tej przygodzie. To zadanie będzie trudne, ale jestem pewien, że damy radę.";
			link.l1 = "Miło cię znów widzieć, Picard. Zamieniam się w słuch, opowiedz mi o tej swojej przygodzie.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Już powiedziałem to Markusowi, teraz powiem tobie. Kiedy byłem niewolnikiem na plantacji w Maracaibo, nauczyłem się czegoś od Hiszpanów. Są dość gadatliwi, kiedy są pijani... Słuchaj, na południowy wschód od zatoki Maracaibo jest mała wioska. Jest ukryta między dwoma górami głęboko w dżungli. Ma piekielną nazwę: Santiago-de-Los-Caballeros-de-Merida. Nazwijmy ją Merida\nBrzmi to jeszcze nieciekawie, co? Góry otaczające wioskę okazały się bogate w klejnoty. Szmaragdy, opale i legendarne ogniste opale\nJak rozumiem, osadnicy Meridy nie powiedzieli o tych klejnotach generalnemu gubernatorowi. Jednak wkrótce się o nich dowie, dlatego powinniśmy odwiedzić Meridę przed przybyciem hiszpańskich urzędników kolonialnych.";
			link.l1 = "Chcesz splądrować osadę?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Dokładnie. Zagubione wśród dżungli i gór, z małym garnizonem - łatwy łup dla korsarskiej jednostki. Poza tym, są daleko od morza, nie spodziewają się ataku od nikogo, oprócz dzikusów z dzidami i łukami.";
			link.l1 = "Jak bardzo jesteś pewien, że osada ma drogocenne kamienie?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Jeśli nasze przygody okażą się fałszywym tropem, sam będę służył na twoim statku jako oficer lub marynarz, będę czyścić pokłady i walczyć w niezliczonych abordażach, aż mój dług wobec ciebie i Marcusa zostanie spłacony.";
			link.l1 = "Rozumiem... Dobrze, wiesz jak dotrzeć do Meridy?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Oczywiście nie znam dokładnej drogi przez dżunglę, ale zatrudnimy przewodnika z ludu Indian. Powinniśmy wylądować na południe od jeziora Maracaibo, znaleźć indiańską wioskę i znaleźć tych, którzy wiedzą, jak tam dotrzeć.";
			link.l1 = "... ";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Kapitanie, bardzo przepraszam za moje słowa, ale dlaczego, do cholery, nie jesteśmy jeszcze w Meridzie? Co? Splunąłeś na naszą wspólną sprawę! Leprechaun i ja odchodzimy bez ciebie. Wyjaśnię wszystko Tyreksowi, a ty powinieneś iść. Oto, weź 50 000 pesos za twoją pomoc w Maracaibo, pożyczyłem je od przyjaciół. Pożegnanie, cholerny wstyd, myślałem o tobie lepiej.";
			link.l1 = "Hmm... Przykro mi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Jesteśmy na miejscu. Przed nami dżungla. Najpierw powinniśmy znaleźć wioskę indiańską i zapytać o przewodnika.";
			link.l1 = "Zróbmy to. Luke, masz coś do powiedzenia... a może jakąś radę?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "Garnizon Meridy jest skończony. Nie spodziewam się poważnego oporu wewnątrz wioski. Ruszajmy!";
			link.l1 = "Szarża!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "Zrobione! Nie ma już bohaterów. Teraz powinniśmy porozmawiać z gubernatorem tego 'miasta'. Mam nadzieję, że jest podatny na perswazję.";
			link.l1 = "Zgadzam się, 'przekonajmy' go!.. Jean! Za mną!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Ładnie zrobione, "+pchar.name+" !  Czas podzielić łupy. Mam już liczby. W skrzyni było prawie 2000 klejnotów: 1560 szmaragdów, 1032 opale i 363 ogniste opale. Twój udział to jedna trzecia: 350 szmaragdów, 244 opale i 63 ogniste opale. Proszę, weź je.";
            }
            else
           	{
           	dialog.text = "Dobrze zrobione, "+pchar.name+" Czas podzielić łupy. Już mam liczby. W skrzyni było prawie 2000 klejnotów: 1050 szmaragdów, 732 opale i 189 opali ognistych. Twój udział to jedna trzecia: 350 szmaragdów, 244 opale i 63 opale ogniste. Proszę, weź je.";
           	}
			link.l1 = "Świetnie!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Teraz porozmawiajmy o moim długu wobec ciebie za moje ocalenie. Rozumiem, że poniosłeś poważne wydatki. Jakie wynagrodzenie uznasz za uczciwe? Płacę z mojego udziału w klejnotach.";
			link.l1 = "Jedna trzecia twojej działki wystarczy. Ty też potrzebujesz pieniędzy - by kupić i zaopatrzyć statek, opłacić załogę...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Dziękuję, przyjacielu! Myślałem, że zażądasz nie mniej niż połowy. Teraz naprawdę potrzebuję pieniędzy. Weź, oto klejnoty.";
			link.l1 = "Co za napad, Jean! Ruszajmy na Hispaniolę, do Tyrexa.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "O, cóż za spotkanie! Przyjemność cię widzieć, "+pchar.name+" Jak się miewasz?";
			link.l1 = "Całkiem nieźle. Niedawno znalazłem skarby Czerwonego Wilka. Teraz zmierzam na Martynikę, aby spotkać się z naszym wspólnym znajomym. Chcesz zobaczyć Tyrexa?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Tak. Chcę z nim porozmawiać w sprawie Pasquale'a Lavoisiera. Marcus wysłał mnie do tego pół bandyty-pół kupca. Zrobiłem, o co prosił, a on zapłacił jakimś gównem, twierdząc, że to cholernie dobra zapłata. Zabiłbym drania tam, gdzie stał, ale Marcus kazał traktować go z szacunkiem... więc to on musi się z tym bałaganem uporać.";
			link.l1 = "Przykro mi, ale Marcus nic nie zrobi. Czterooki jest z nim w interesach.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Co do cholery?";
			link.l1 = "Tak, ale nie mówiłem ci o tym, dobrze? Lavoisier też mnie niedawno oszukał. Tyrex poprosił mnie o pomoc, tak jak ciebie. Ostrzegano mnie na Isla Tesoro, że zadrzeć z czterookim to jak zadrzeć z Marcusem. Więc sugeruję, żebyś o tym zapomniał. Nie jesteś ani pierwszym, ani ostatnim w tej sytuacji.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Widzę. Ciebie też wykiwali ci dwaj, co?";
			link.l1 = "Cóż, tak. Myślałem, żeby zrobić kłopoty temu czterookiemu, zanim dowiedziałem się o nim więcej. Nie warto tego robić.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Spróbowałbyś odpłacić sukinsynowi, gdybyś wiedział, że nikt się nigdy nie dowie?";
			link.l1 = "Ha! Pewnie, że bym to zrobił! Choć nie wiem jak. Zaatakuj flauty Lavoisiera, a któregoś pięknego dnia twoi marynarze upiją się i wygadają wszystko. Nie wiesz, jak to działa?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Zmierzacie teraz na Martynikę? Kiedy znów przybędziecie do La Vega?";
			link.l1 = "Marcus dał mi trzy tygodnie.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Spróbuj zrobić to w dwa. Przemyślę to... Znajdź mnie w Zatoce Gonaives za 14 dni. Kieruj się tam, i nie wchodź do La Vega.";
			link.l1 = "Widzę, że coś kombinujesz, ha-ha. Dobrze. Spróbuję.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "Lepiej to zrób. Do zobaczenia!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Gdzie jest twój statek? Przybyłeś tu z La Vega? Merde! Prosiłem cię, byś przybył tu niepostrzeżenie i w tajemnicy. Mój plan jest teraz zrujnowany. Cholera!";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Jesteś tu, "+pchar.name+" . Dobrze, że jesteś tutaj. Odeślij swoich ludzi z powrotem na statek. To prywatna rozmowa.";
				link.l1 = "Bardzo dobrze.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "O, jesteś , "+pchar.name+" . Dobrze, że jesteś tutaj. Mam dla ciebie pewną sprawę. Gotów, by jej wysłuchać?";
				link.l1 = "Jasne!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Już ci mówiłem - odeślij swoich oficerów!";
				link.l1 = "Tak-tak, rozumiem.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Świetnie. Teraz możemy rozmawiać swobodnie. Mam dla ciebie interes. Gotowy, by go wysłuchać?";
				link.l1 = "Jasne!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Znasz dobrze La Vegę?";
			link.l1 = "Cóż... Myślę, że tak. Dlaczego pytasz?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Kiedykolwiek zauważyłeś magazyn po prawej stronie od lokalnego sklepu? Jedyne duże domostwo wśród szałasów.";
			link.l1 = "Zawsze zamknięty? Tak, widziałem go. A co z nim?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Świetnie zauważone - jest zawsze zamknięty. Podczas gdy byłeś na misji na Martynice, nasz wspólny przyjaciel Lavoisier przebywał tutaj przez trzy dni jako gość Marcusa Tyrexa. Spędzali czas w tym domu pijąc rum i bawiąc się.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Wtedy ludzie Lavoisiera wciągnęli do domu jakieś skrzynie i paczki. Potem odszedł. Co do Marcusa, to zostaje w tym miejscu codziennie przez kilka godzin.";
			link.l1 = "Jakieś sugestie?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "Jakie sugestie? Jestem pewien, że ten dom musi być bazą Lavoisiera w La Vega. Nie widziałem wiele przez okno, ale są tam przechowywane towary. Myślę, że czterooki ma środki, by spłacić to, co nam jest winien.";
			link.l1 = "No cóż... Chcesz się włamać? A co z zamkniętymi drzwiami? Są ciężkie i solidne, nie ma mowy, żebyśmy się włamali po cichu.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", czy uważasz mnie za idiotę? Już to załatwiłem. Zrobiłem klucz używając woskowej maski zamka. Kosztowało mnie to niemało, ale to mój problem.";
			link.l1 = "Heh! Dlaczego więc na mnie czekasz?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Będzie bezpieczniej w ten sposób, poza tym jesteś jedynym, komu mogę zaufać. Jedna głowa dobra, dwie lepsze, a cztery oczy lepsze niż dwa.";
			link.l1 = "Cóż, tak, skrzyżowanie z Lavoisierem będzie wymagało tylu oczu, ile on ma, ha-ha-ha! Ale co z Tyreksem? Co jeśli wejdzie do domu, gdy będziemy sprawdzać rzeczy Pasquale'a?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "Nie wróci. Zawsze jest z powrotem w swoim domu przed północą. Gotowy, by wyruszyć do La Vega następnej nocy? Nigdy nie zrozumieją, kto ich wykiwał: ty wciąż jesteś na Martynice, a ja opuściłem La Vega tydzień temu.";
			link.l1 = "Z chęcią bym przyłożył temu czterookiemu enculé. Ale powiedz mi, Jean, jak mamy przenieść beczki i skrzynie z domu?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Jestem pewien, że znajdziemy tam więcej cennych przedmiotów niż skrzynie i beczki z towarami, które będą znacznie lżejsze. Więc, jesteś ze mną?";
			link.l1 = "Do diabła, oczywiście, że jestem!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Świetnie, cieszę się, że się nie pomyliłem co do ciebie. Odpocznijmy teraz, wyruszamy do La Vega o północy.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Czas ruszać. Powinniśmy obrabować tego drania i wynieść się stamtąd przed świtem.";
			link.l1 = "Naprzód!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Cicho... Teraz ruszaj, po cichu, do domu Pasquale'a. Podążaj za mną.";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Spójrz na to - tyle rzeczy leży wokoło. Zaczynajmy. Sprawdź skrzynię przy drzwiach, potem idź na górę i zajmij pokój. Ja zostanę tutaj: znam sztuczki z ukrywaniem kosztowności wśród rupieci. Trzymaj oczy i uszy otwarte i trzymaj się z dala od okien.";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", co masz? Coś interesującego?";
			link.l1 = "Chodź i zobacz. To jest coś.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Do diabła! Teraz rozumiem, dlaczego Tyrex przychodzi tu codziennie. To nie tylko magazyn czterookiego, ale też burdel.";
			link.l1 = "Wydaje się, że ona jest tu niewolnicą.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Pewnie. Spójrz na nią - to oczywista portowa dziwka... Zły los dla nas. Musimy ją zabić.";
			link.l1 = "Czy naprawdę musimy?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Widziała nasze twarze i słyszała twoje imię. Powie wszystko Tyrexowi.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "To twój wybór. Jej życie może kosztować cię twoje.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Nie myśl nawet o zaufaniu tej dziwce. Jutro Tyrex będzie wiedział wszystko. Chcesz otrzymać czarną markę?";
			link.l1 = "Nie, nie chcę. I nie chcę zabijać tej dziewki - mam dla niej użytek. Ona idzie ze mną.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Nie bądź głupcem! Ucieknie, jak tylko nadarzy się okazja. Spójrz na jej czoło, widzisz ten znak? Jest złodziejką.";
			link.l1 = "Hm. Prawdopodobnie masz rację, Jean. Dobrze, skończ z nią i uciekajmy stąd.";
			link.l1.go = "rocur_82";
			link.l2 = "Nie planuję trzymać jej na moim statku. Mam dla niej miejsce, z którego nigdy nie ucieknie, a nie ma tam też uszu, które usłyszałyby jej krzyki. Będzie tam również kontynuować swoją pracę... Osobista kurtyzana, za darmo, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "To koniec, teraz nie ma mowy, żeby powiedziała cokolwiek Marcusowi...";
			link.l1 = "Biedna dziewczyna... hah, jak to mówią, fortuna to suka...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Jesteś dobrym człowiekiem, "+pchar.name+". Dlaczego chcesz się nią przejmować? Ach, nieważne, to twój wybór. Upewnij się, że jest cicho, gdy będziemy odchodzić.";
			link.l1 = "Jeśli jej nie będzie - to znaczy, że nie żyje.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "Co znalazłeś?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "Więcej szczęścia po mojej stronie. Tu masz swoją dolę. Nigdy nie zdołałbym zabrać wszystkiego na brzeg. Czterooki zapłacił nam w całości.";
			link.l1 = "Wspaniale! Dobra robota, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Teraz idź!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Świetnie. Zrobione. Cicho i spokojnie. Teraz wracajmy do statków.";
			link.l1 = "Hah, dobry pomysł.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Cóż, "+pchar.name+"  Czas, by nasze drogi się rozeszły. Nie jestem pewien, czy kiedykolwiek się jeszcze spotkamy, ale wiedz, że było mi przyjemnie cię poznać, przyjacielu.";
			link.l1 = "Och, no dalej, będziemy się często widywać w La Vega.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "Nie. Skończyłem z Tyreksem. Ten bałagan z Lavoisierem to była ostatnia kropla.";
			link.l1 = "Hmm... Rozumiem, po prostu zapomnij o tym. Mamy to, co nam się należało. Tyrex daje korzystne wskazówki, prawda? Ostatnim razem zarobiłem ponad pół miliona na skarbie Czerwonego Wilka.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Powiedz mi więc, czy włożyłeś dużo wysiłku w jego znalezienie?";
			link.l1 = "No cóż... To nie było łatwe. Dużo myślałem, podróżowałem i walczyłem. To było tego warte, myślę.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "Ile zapłaciłeś Tyreksowi?";
			link.l1 = "Jedna trzecia.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "Jaka była jego rola w tym interesie? Co dokładnie zrobił Marcus?";
			link.l1 = "Hm... Dał mi dziennik Czerwonego Wilka...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "I to wszystko? Prawda?";
			link.l1 = "Cóż... Inaczej nigdy bym się nie dowiedział o kapitanie Wulfricu...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", nie widzisz, że Tyrex zmusza innych do brudnej roboty? Myślisz, że dałby ci zadanie znalezienia tego skarbu, gdyby mógł to zrobić sam? Cholera, nie! Założę się, że najpierw próbował zrobić to sam i kiedy wszystko spieprzył, wezwał cię do roboty. A podczas gdy ty myślałeś, spędzałeś tygodnie na morzu, walczyłeś i ryzykowałeś własne życie, ten drań wraz ze swoim obrzydliwym, czterookim przyjacielem pieprzyli dziwkę w La Vega. I za to też dostał ćwierć miliona peso. Ot tak\nMyślisz, że wysłał swojego psa Leprechauna, aby pomógł nam w nalocie na Meridę? Nie, chciał się upewnić, że jego interesy są bezpieczne. Wszystko, co Marcus może zrobić sam, robi to, albo sam, albo z pomocą Cutlassów, Łysych, Leprechaunów i innych głupich idiotów, którzy pracują dla niego za grosze. Ludzie tacy jak ty i ja dostajemy namiary, których Marcus jest zbyt głupi, by wykonać samodzielnie\nPamiętasz wszystkie zadania, które dla niego wykonałeś? Policz, ile na tobie zarobił. Mam tego dość. Teraz mam pieniądze, wspaniałą korwetę i lojalną załogę... od teraz jestem wolnym strzelcem. Kieruję się na Jamajkę, może tam otrzymam list kaperski.";
			link.l1 = "Nie sądzę, że masz całkiem rację co do Tyrexa... Ale życzę ci powodzenia, Jean! Mam nadzieję, że odniesiesz sukces na Jamajce.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "Zrobię to. Powodzenia także tobie i pomyśl o tym, co powiedziałem. Bycie dziwką Marcusa to nie najlepsza rola dla ciebie, wiem, że stać cię na o wiele więcej. No cóż... żegnaj, bracie! Niech cię Bóg prowadzi!";
			link.l1 = "Udanych łowów, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", powiedz mi, jak spędziliśmy tyle czasu w dżungli? Teraz mój plan jest skopany. Eh... Żegnaj, kumplu...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "Czas odpływać, chłopcy. Cholera, Książę, zaskoczyłeś mnie. Spaliłeś całe miasto, ale odmówiłeś pobrudzenia rąk, gdy to miało znaczenie.";
				link.l1 = "Nie kazałem spalić miasta!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "Czas ruszać, chłopcy. Lucas, przegapiłeś to. Książę poradził sobie genialnie – i wyciągnął niezły zysk!";
				link.l1 = "A co z miastem, Przystojniaku?! Dałem słowo!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "Przynajmniej nie próbowałeś tego ratować. W przeciwnym razie nasi ludzie najpierw by cię wypatroszyli. Dla nich to był ciężki dzień. Zasłużyli na to, by się odprężyć. Przyzwyczaisz się. Masz wszystkie predyspozycje do tego.";
			link.l1 = "Dzięki za radę, ale nie przypominam sobie, żebym o nią prosił. Chodźmy.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " Myślałem, że żartujesz. No cóż... byłeś zbyt pochopny. Miasto skończone. Zawsze tak jest, gdy Bractwo Wybrzeża zabiera się do pracy. Przyzwyczaisz się do tego.";
			link.l1 = "Nie jestem pewien, czy to zrobię. Dobrze, chodźmy.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Kumplu... co to było przed chwilą?";
			link.l1 = "Co, nie zrozumiałeś? Kupiłem cię. Kiedyś powiedziałeś, że mam dostęp do Hiszpanów, więc to wykorzystałem.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "Zrozumiałem to - nie jestem idiotą. Ale czy nie pracowaliśmy nad innym planem?";
			link.l1 = "No cóż, Cutlass i ja pomyśleliśmy, że nie byłoby dobrze, gdybyś zginął podczas powstania czy pościgu, więc postanowiliśmy cię wykupić.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Hah, nie obrażaj mnie. Jestem w końcu jednym z kapitanów Terraxa. Wiem, jak trzymać ostrze.";
			link.l1 = "Nie wątpię w to, ale czy naprawdę martwisz się, że jesteś wolny?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "Nie, nie - jestem wdzięczny. Tylko że... czy to nie było trochę za dużo wydać całe to złoto? Czuję się chory na samą myśl o tym. Z drugiej strony, plantator wyglądał jak błyszcząca srebrna taca.";
			link.l1 = "Tak, 'Umowa Stulecia', rzeczywiście. Trochę boli, to prawda. Ale czas jest cenniejszy niż złoto, Jean. Szukanie pistoletów i lekarstw dla was wszystkich...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "Jestem wdzięczny, ale kumpel, jesteś głupcem - bez urazy. Mówiłem ci, że moi chłopcy nie są najlepsi z mieczami. Ale każdy potrafi pociągnąć za spust. Mogłeś przynieść jakiekolwiek pistolety i medykamenty z ładowni, tak jak z szablami i toporami - nie są wybredni.";
			link.l1 = "Hmm, szczerze mówiąc, nie pomyślałem o tym... W każdym razie, chodźmy - Szabla pewnie już się niecierpliwi.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Witaj, kapitanie "+GetFullName(pchar)+"Luke Leprechaun do usług! Powiedziano mi, że wybieramy się do dżungli Południowego Głównego.";
			link.l1 = "Dokładnie. Na pokład łodzi, wyruszamy natychmiast.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Pozwól, że stary bukanier da ci kilka rad, kapitanie. Skoro zmierzamy do dżungli - z pewnością spotkamy Indian. Weź ze sobą prezenty dla nich. Indiańscy wojownicy uwielbiają piękne pistolety, zwłaszcza pojedynkowe. Lubią też kompasy i lunety. Traktują je jak magiczne przedmioty\nIch kobiety wolą tanie klejnoty i błyskotki, takie jak lustra i muszle. Jeśli wpadniemy w walkę z nimi, używajcie trombonów i arkebuzów: kartacz ogólnie jest bardzo dobry przeciwko wrogom, którzy nie noszą zbroi. Jeśli chodzi o samo osiedle, sugeruję działa, które mogą używać papierowych nabojów.";
			link.l1 = "Bardzo dobrze, Luke. Twoje słowa zostały zanotowane. Witaj na pokładzie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "Zobacz się z wodzem, jak tylko dotrzemy do wioski. I przynieś dary, inaczej to bez sensu. Upewnij się, że zapytasz, czy ktoś z jego ludzi zna tajne przejścia w dżungli przed nami, i poproś o tych, którzy nie boją się podróży. Idę z tobą, zwracaj się do mnie w razie jakichkolwiek trudności.";
			link.l1 = "Naprzód! Jean, Luke - za mną!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Jakieś pytania, kapitanie?";
			link.l1 = "Na razie nic, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Tak! Rozmawiałem z ich wodzem, obdarowałem go, a potem zwołał swoich czerwonoskórych na naradę. Są wśród nich tacy, którzy wiedzą, jak dotrzeć do Meridy, ale nikt nie chce się tam wybrać - boją się innego plemienia zwanego Capongs. Ci straszą miejscowych na śmierć. Czerwonoskóry drań twierdzi, że nie mamy szans znaleźć ścieżki sami, a żadnego przewodnika nie uda nam się wynająć. Więc co mamy teraz zrobić, co?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "Mam przy sobie antidota.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, rozumiem... Kapitanie, musisz wiedzieć, że tchórzostwo często pokonuje chciwość. Obiecaj tak hojną nagrodę, że człowiek podejmie się zadania... Wiesz co, właściwie? Spróbuj bardziej przebiegłej opcji - ich kobiety. Podaruj im coś i zapytaj o ich mężczyzn, a jest szansa, że znajdziesz przewodnika, którego potrzebujemy. Obiecaj jej stosy paciorków i luster za pomoc jej męża. Bądź hojny i obiecaj wiele, przekonaj ich.";
			link.l1 = "Heh! Cóż, najmniej, co mogę zrobić, to spróbować, choć nie jestem pewien, czy to zadziała...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Cóż, jest jeszcze jedna opcja... Ale nie jest ona zbyt dobra, jeśli rozumiesz, co mam na myśli.";
			link.l1 = "Inna opcja? Dawaj mi ją! Nie jestem zbyt chętny, by biec do indiańskich kobiet i błagać je, by przekonały swoich mężów do przyłączenia się do nas.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "Ta opcja jest stara jak świat. Pokaż im, że powinni bać się ciebie bardziej niż Kapongów. Wiesz... Możesz powiedzieć wodzowi, co twoi piraci mogliby zrobić wszystkim kobietom we wiosce, zwłaszcza jego żonie i córkom. Możesz nawet dorzucić jakieś groźby tortur.\nW każdym razie, jestem pewien, że wymyślisz coś, co sprawi, że ci Indianie zaczną cię bać. Osobiście nie jestem fanem tej drogi, i są ku temu powody.";
			link.l1 = "Powody? Jakie na przykład? Według mnie to dość skuteczne i bezpośrednie rozwiązanie.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "Na początek, nie będziemy raczej ulubieńcami miasta po tym. Możemy wpaść w pułapkę lub inną nieprzyjemną sytuację. Po drugie, cóż... to po prostu nie wydaje się właściwe. Co innego wyeliminować uzbrojonych przeciwników, ale zupełnie czym innym jest grozić kobietom. Sugerowałbym znalezienie sposobu na bardziej... dyplomatyczne postępowanie z Indianami.";
			link.l1 = "Zrozumiałem, przemyślę to. Może spróbuję uwieść jakąś damę koralikami... Albo wymyślę jakieś wyrafinowane sposoby tortur dla córek wodza, haha!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "Jeszcze jedna rzecz, kapitanie, według wodza możemy napotkać w dżungli wrogie plemię Indian, bardzo prawdopodobne, że to tylko mała grupa kanibali, ale lepiej dmuchać na zimne. Jeśli to wojownicze plemię, zatrują swoje bronie, więc upewnij się, że zaopatrzysz swoich ludzi w antidota.\nJa i moi ludzie zawsze mamy przy sobie mnóstwo mikstur. Jeśli chodzi o twoich piratów... Po prostu przynieś mi antidota, a ja je rozdzielę między twoimi ludźmi. Potrzebuję co najmniej tuzina mikstur na to. Upewnij się, że przyniesiesz też trochę dla siebie i swoich oficerów.";
			link.l1 = "Dobrze. Przyniosę antidota.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Bardzo dobrze. Daj mi je. Resztę załatwię sam.";
			link.l1 = "Tam...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Czterdzieści dwa mikstury wystarczą. Resztę powinieneś zachować dla siebie.";
			link.l1 = "Dobrze...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Kapitanie, twoi Indianie - Hayami i Tagofa czekali zbyt długo na dostarczenie obiecanych im darów i odeszli do innej wioski, by tańczyć i pić kasheeri. Mam przeczucie, że twój sposób prowadzenia interesów nie przyniesie nam nic dobrego. Przykro mi, ale jesteś wykluczony z tego. Picard poprowadzi ekspedycję.";
			link.l1 = "Do diabła z wami wszystkimi!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Kapitanie, co do diabła? Straciliśmy za dużo czasu na nic! Czuję, że twój sposób prowadzenia interesów nie przyniesie nam nic dobrego. Przykro mi, ale jesteś poza tym. Picard poprowadzi ekspedycję.";
			link.l1 = "Do diabła z wami wszystkimi!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Kapitanie, do diabła? Miałeś dziesięć dni, by znaleźć skórę i deski. Niedaleko stąd jest miasteczko Maracaibo! Mam przeczucie, że twój sposób prowadzenia interesów nie przyniesie nam nic dobrego. Przykro mi, ale jesteś poza tym. Picard poprowadzi ekspedycję.";
			link.l1 = "Cholera z wami wszystkimi wtedy!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Kapitanie, przykro mi, ale dawno już powinienem być w La Vega, podobnie jak ty. Musiałeś zapomnieć o moim i Markusa istnieniu. Tak czy inaczej, odchodzę. Powinieneś kontynuować to, co robisz, a ja wszystko wyjaśnię Markusowi. Żegnaj, szkoda, myślałem o tobie lepiej.";
			link.l1 = "Hmph...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "Więc, z tego co rozumiem, mieliście bójkę. Nie udało się podzielić łupu, prawda, książę Charlie?";
			link.l1 = "Krasnoludek? Jesteś tutaj... Choć to żadna wielka niespodzianka. Tak, chciwe dranie splunęły na Kodeks i próbowały mnie zabić.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "Tak, nieźle cię pobili, Książę. Wyglądasz jak mokra kupa gówna\nCo mówiłeś o Kodeksie? Pozwól, że cię oświecę: pracowałem z Marcusem, który rzekomo jest Strażnikiem tego Kodeksu, widziałem, jak ludzie spluwają na niego tyle razy, że nie śmiałbym liczyć. Niektórzy z tych ludzi zapłacili straszną cenę. Niektórzy z nich nie\nMożesz robić wszystko, co chcesz, jeśli nagroda to pokryje. Zwłaszcza jeśli nikt nie patrzy.";
			link.l1 = "Więc... ty też jesteś tutaj po skarb?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Co za głupie pytanie. Cóż innego bym robił tutaj, tak daleko od mojej ojczyzny na Hispanioli? Chociaż w końcu jestem mądrzejszy od was wszystkich: znając waszą zgniłą piracką naturę. Po prostu czekałem, pozwalając wam, szczury, rozszarpać się nawzajem, zostawiając tylko jednego wroga przy życiu, ale rannego i zmęczonego.";
			link.l1 = "Wróg? Tak przestrzegasz Kodeksu swego patrona?! Zabija ludzi za to!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "Nie podlegam Kodeksowi, książę, nie jestem piratem. Nie mam nawet własnego statku - musiałem wynająć łajbę, żeby tu dotrzeć. Jestem niczym więcej jak korsarzem w pigułce. Jestem myśliwym, poluję na bawoły i robię buccan. Cholerni Hiszpanie, którzy twierdzą, że my, francuscy korsarze, psujemy im życie, zmusili mnie do szukania wsparcia i ochrony u Markusa. Pomagam mu w jego interesach czasami.\nChociaż nie jestem piratem, ja i moi ludzie walczymy dobrze, widziałeś nas w akcji.";
			link.l1 = "Napadaliśmy i walczyliśmy razem, Leprechaun. Chroniliśmy się nawzajem, ryzykując życie, by ocalić drugiego. Czy to wszystko nie znaczy dla ciebie nic?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "Powiem ci szczerze, Książę: nigdy cię nie lubiłem. Jesteś parweniuszem. Bezczelny młokos, miłośnik trunków i upadłych kobiet, który wykonał kilka dochodowych zleceń dla Tyrexa i pomyślał o sobie jako o wielkim piracie\nPoza tym, jesteś rzeźnikiem z natury. Myślisz, że Cartagena dała ci większą wagę wśród Bractwa? Ho-ho, o nie, tylko wśród potworów takich jak ty.";
			link.l1 = "O, to jest przezabawne! Ha-ha-ha, wypowiedziane przez samego prawdziwego anioła! Ty stary draniu!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = " Myślę, że wszystko już wyjaśniliśmy. Czas zakończyć tę komedię. Diabły za długo czekały na ciebie w piekle.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Podoba ci się, co?";
				link.l1 = "Odwal się!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "Cóż, co o tym myślisz?";
				link.l1 = "To nie jest śmieszne, Krasnoludzie. Co do diabła?! Nie zamawiałem masakry! Nie sądzisz, że to przesada?! Terrax nie będzie zadowolony!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "Więc czemu ten winny wyraz twarzy? Nie podoba ci się to? Pozwól, że ci powiem - będzie tylko gorzej. Myślisz, że dzisiejsza masakra to tylko przypadek dnia? Hah, jasne. To rutyna. Picard nawet nie drgnął. Dla nich to po prostu kolejny dzień robienia tego, co kochają.";
			link.l1 = "A co z tobą? Po prostu przechodzisz?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "Nie jestem piratem. I wolałbym nie brać udziału w dzisiejszych wydarzeniach. A... jeśli tak cię porusza widok ciał kobiet na spalonej ziemi Meridy, to dlaczego postąpiłeś tak, jak postąpiłeś z Indianami, książę?";
			link.l1 = "Co miałem zrobić? Rzucić wszystko i czołgać się do Markusa z przeprosinami?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "Po prostu myślałem, że całkowicie to zaakceptowałeś, zacząłeś myśleć i działać jak kapitanowie Tiraxa. Ale nie, ha! Jesteś zbyt miękki do tego rodzaju pracy. Lepiej oddaj swoją część Marcusowi i odejdź z podkulonym ogonem. To nie jest twoje powołanie.";
			link.l1 = "To nie twoja sprawa decydować za mnie, Krasnoludku. I na pewno nie masz prawa mnie obrażać. Nie oddam nikomu mojej części. Podzielę się uczciwie z Terraxem.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "Oczywiście. Ale lepiej wyjdźmy, zanim zemdlejesz.";
			link.l1 = "To nie jest śmieszne, do diabła.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "W takim razie nie znasz go dobrze. Jednakże, skoro dzisiejsze wydarzenia nie przynoszą ci radości, posłuchaj, co mam do zaoferowania.";
			link.l1 = "Cóż możesz zaoferować po tym?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "Lepiej się postaraj słuchać, chłopcze.";
			link.l1 = "Hmm, nie podoba mi się twój ton, Lucas, ale dobrze, mów dalej.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "Mogę sobie na to pozwolić - żyłem dłużej niż ty, Książę. Mam więc bystre oko, nie tylko do strzelania. Chcesz wiedzieć, co zauważyłem?";
			link.l1 = "Po prostu powiedz to!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "Nie pasujesz tutaj. Tak, jesteś dobry. Robisz postępy. Ale tylko dlatego, że jesteś silnym kapitanem, a nie dlatego, że to naprawdę twoje powołanie. Nie wiem, jak trafiłeś do Terraxa, ani dlaczego, ale uwierz mi, to nie jest twoja rzecz.";
			link.l1 = "Mam... cel. Nie mogę ci powiedzieć, jaki to jest.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "I czy zbliżyłeś się do tego?";
			link.l1 = "Jeszcze nie.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Cóż, jeśli nawet dzisiejszy dzień cię nie zbliżył, to tutaj już nic więcej nie zyskasz. Jesteś dobrym człowiekiem, Książę. Traktowałeś Indian jak ludzi. To ironiczne, że skończyłeś tutaj z nami. Moja rada: oddaj swoją część Terraxowi, by uniknąć problemów, i trzymaj się z dala od tego wszystkiego - ocal swoją duszę, póki możesz.";
			link.l1 = "Przemyślę to.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa wita cię, synu morza. Czy chcesz, abym pokazał ci drogę do hiszpańskiej osady w górach?";
			link.l1 = "Zgadza się. Widzę, że dobrze posługujesz się naszym językiem, w przeciwieństwie do reszty twojego ludu.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa często miał do czynienia z yalanaui... Większość drogi będziemy podróżować rzeką. Będziesz potrzebować długich łodzi. Masz je?";
			link.l1 = "Czyżby? Moglibyśmy je pożyczyć na chwilę...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Nasza wioska jest mała, mamy bardzo niewiele szalup i wszystkie są użyteczne tylko do łowienia ryb. Teraz potrzebujemy dobrych szalup, takich które wytrzymają długą podróż, jak te na twoich statkach.";
			link.l1 = "Hmm... Potrzebujemy więc sześciu długich łodzi. Statek nie ma ich tylu.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Zbudujcie je więc. Wy, biali, możecie naprawiać swoje olbrzymie okręty na brzegu, więc z pewnością potraficie zrobić kilka długich łodzi.";
			link.l1 = "Heh, wygląda na to, że masz rację, Tagofa. Zawieź nas do rzeki, mam nadzieję, że to niedaleko stąd?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "To nie tak. Chodź za mną.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Oto rzeka, o której ci mówiłem. Stąd rozpoczniemy naszą podróż. Ty zbudujesz łodzie, a potem zaczniemy.";
			link.l1 = "Zrozumiano, Tagofa. Powiem ci, gdy będzie zrobione.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Gotowe są łodzie, biały wodzu?";
			link.l1 = "Tak. Moi ludzie zaraz się do nich dobiorą.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Bardzo dobrze. Wsiadaj na pierwszy razem ze mną. Tagofa pokaże drogę.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "Rzeka jest już za nami. Nie jesteśmy daleko od hiszpańskiej osady. Oto ścieżka, trzymajmy się jej, a nie zgubimy się. Udało nam się ominąć las pełen myśliwych Capong, ale to również ich ziemia. Musimy być ostrożni.";
			link.l1 = "Nie martw się. Wytępimy ich, jak tylko pokażą nam swoje brzydkie pomalowane gęby.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = " ";
			link.l1 = "Ej! Tagofa! Spójrz! Co to jest... na środku ścieżki? Jakaś indiańska rzecz.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "To jest znak Kapongów. Ostrzeżenie. Mówi ci, żebyś się zatrzymał i nie szedł dalej. Kapongi już nas dostrzegli.";
			link.l1 = "A co, jeśli pójdziemy dalej? Czy oni nas zaatakują?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Tak, biały wodzu. Musisz wyglądać groźnie dla nich skoro jeszcze nas nie zaatakowali. A jednak zostawili dla ciebie znak.";
			link.l1 = "Pieprzyć znak. Ruszamy naprzód... Wszyscy słuchajcie! Do broni! Gotowi! Bądźcie czujni! Jeśli te dzikusy pokażą nam swoje paskudne mordy, zabijemy ich wszystkich!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "Wódz biały i jego ludzie zmiażdżyli capongas, Tagofa jest pod wrażeniem. Hiszpańskie miasto jest blisko. Jest dolina, gdzie zobaczysz wodospad. Tagofa nie pójdzie do Hiszpanów. Będę czekać na ciebie przy wodospadzie.";
			link.l1 = "Znakomicie. Na przód!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Wróciliśmy, biały wodzu. Tagofa zrobił, co obiecał.";
			link.l1 = "Podziękowania, Tagofa. Spisałeś się dobrze.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa powinien odejść. Hayami bardzo na mnie czeka. Żegnaj, synu morza.";
			link.l1 = "Powodzenia, synu dżungli. Przekaż moje pozdrowienia swojej żonie. I dziękuję za pomoc.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Hej! Kim jesteś i czego chcesz?";
			link.l1 = "Musimy dostać się do Meridy i pogadać z waszym gubernatorem lub kimkolwiek, kogo macie zamiast niego...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "Nie wpuszczamy obcych do Meridy. Wynoś się!";
			link.l1 = "Kamracie, wiosłowaliśmy ciężko przez dwa dni, a potem walczyliśmy z hordami Indian, by nie odejść tak po prostu. Powtarzam, chcę porozmawiać z wodzem waszej wioski! Mamy dla niego... propozycję biznesową, tak! A jeśli wszyscy się zgodzimy, wasza wioska pozostanie nietknięta.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Czy grozisz mi, ladron?";
			link.l1 = "Jak to wykombinowałeś? Ach tak, rzeczywiście, grożę. Albo dostaniemy to, po co tu przyszliśmy, pokojowo albo siłą, a ty masz zaszczyt zdecydować o losie swojej wioski.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Nie wejdziesz do Meridy, ty cholerny piracie! Alarm! Wróg u bram!";
			link.l1 = "Taki nierozsądny dżentelmen...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Przeklęci łotrzykowie! Czego od nas chcecie?! To mała, skromna osada. Nie mamy ani złota, ani srebra! Skąd w ogóle o nas się dowiedzieliście?";
			link.l1 = "Ach, nie udawaj niewinnego i nieświadomego, Wasza Ekscelencjo. Cały świat już huczy od plotek o twoich opalach.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "A ty wywołałeś tę bezbożną masakrę z powodu... plotek?! Nikogo nie oszczędziłeś! Bestie... Niech będzie ci wiadomo: złoża są daleko stąd. Nic tu dla ciebie nie ma do zdobycia. Odejdź.";
			link.l1 = "Ty rozpocząłeś tę bezbożną masakrę. Cywile walczyli ramię w ramię z twoimi żołnierzami. Nigdy nie uwierzę, że takie bezsensowne bohaterstwo jest możliwe tylko po to, by chronić kilka gołych ścian.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Czy wiesz, ile wysiłku włożono w budowę tych murów? Nie wynajmowaliśmy zewnętrznych budowniczych - zbudowaliśmy je sami, cegła po cegle. Każdy mieszkaniec. Nawet ja, własnymi rękoma.";
			link.l1 = "Co za wzruszająca opowieść... A co z meblami? Też zrobiliście je sami? Jaki piękny rzeźbiony fotel. I stół. I szafki. Czy to dąb barwiony? Czy heban? Trochę zbyt luksusowe jak na 'skromną osadę', nie sądzisz?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "Chciwość zaślepiła twój umysł, ladron.";
			link.l1 = "Nie ma potrzeby komplikować spraw, Senor Gubernatorze. Albo tego pożałujesz.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Zamierzasz mnie torturować, przeklęty piracie? Szkoda dla ciebie - wierzę w Boga Wszechmogącego. I wstąpię do nieba jako męczennik, jeśli przesadzisz.";
			link.l1 = "Hm-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "Mój przyjacielu, on nie będzie tak rozmawiał. Pozwól mi się tym zająć.";
			link.l1 = "Och?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "Pamiętam wszystko, co ci nadęci Hiszpanie zrobili mi na tej przeklętej plantacji. Chętnie ci to pokażę, Książę. A przy okazji opowiem ci kilka historii. Nie będziesz się nudził.";
			link.l1 = "A co jeśli dasz się ponieść?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "On nie będzie mówił ładnie. Znam takich jak on.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(Godny zaufania) (Honor) (Przywództwo) Wystarczy krwi na dzisiaj, Jean. Zajmę się tym sam.";
				link.l1.go = "merida_head_dobro_1";
				notification("Trustworthy", "Trustworthy");
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(50))+")", "None");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Zrób to. Nie będę się mieszał. I nie będę też patrzył.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "Gdybym nie był ci dłużny, miałbym kilka wyborowych słów dla ciebie... Cholera. No dalej. Teraz czas na prawdziwą robotę.";
			link.l1 = "Nie przemęczaj się.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "Jak sobie życzysz, przyjacielu. Będzie zabawnie to oglądać.";
			link.l1 = "Nie uśmiechaj się za wcześnie.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "Twierdzisz, że załatwisz to sam, bez rozlewu krwi, ty przeklęty ladronie? Nie ma nic, co mógłbyś powiedzieć, by kamienie pojawiły się znikąd!";
			link.l1 = "nie lepiej, jak się pojawią, Gubernatorze. W przeciwnym razie zrównamy miasto z ziemią i zabijemy wszystkich oprócz ciebie. Nie lubię tego rozwiązania, ale jestem gotów poświęcić swój honor dla mojej sprawy. Twoim obowiązkiem jest jednak chronić cywilów, ocalałych żołnierzy i robotników Meridy. Czy wolisz 'wznieść się jako męczennik' kosztem ich cierpienia? To nie brzmi dla mnie zbyt bosko.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "Przeklęty...\nTam... w skrzyni. Tylko oszczędź mieszkańców miasta!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Skradaj się) Czy wszystko jest w skrzyni?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "Dotrzymuję słowa. Żegnaj, Gubernatorze.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "Niech cię diabli!\nSkrzynia ma również fałszywe dno. Weź wszystko!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Gładko, Książę. Przepraszam, że cię nie doceniłem.";
			link.l1 = "Zadowolony?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Gładko, książę.";
			link.l1 = "Zadowolony?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "More than. But... you'll see for yourself. You go ahead; I'll dig around a little more.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "Obiecałeś opuścić miasto, gdy zdobędziesz klejnoty... Teraz je masz, a twoi ladroni podpalili nasze domy! Jesteś kłamcą i nikczemnym piratem! Mam nadzieję, że płomienie piekieł będą dla ciebie równie gorące!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", szanowny panie. Jaki jest cel twego przybycia tutaj?";
			link.l1 = "Jestem od Tyreksa. Powiedziano mi, aby eskortować twój statek do Bridgetown. Jesteś gotów?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Och, wreszcie! Tak, moja załoga jest gotowa do natychmiastowego wypłynięcia!";
			link.l1 = "Wspaniale. Przygotuj żagle, kapitanie. Ruszajmy w drogę!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Dziękuję za pomoc, kapitanie! Z tobą u boku byłem tak bezpieczny, jakbym był za murami fortu.";
			link.l1 = "Hah, nie ma sprawy, kumplu! Wszystko na rachunek Marcusa. Powodzenia, kamracie!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Witaj, dzielny kapitanie! Pozwól, że się przedstawię - jestem korsarzem Anglii, Ignacio Marco de Torero.";
			link.l1 = TimeGreeting()+", przyjacielu. Kapitan "+GetFullName(pchar)+" do usług. Jak mogę pomóc?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "O, znam cię! Monsieur "+GetFullName(pchar)+"Plotki o twoich zasobach i patronach docierały do mnie przez całe Archipelag. Wierzę, że moja oferta będzie dla ciebie bardzo interesująca.";
			link.l1 = "Jaka oferta?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Chodźmy do tawerny na drinka. Opowiem ci wszystko. To nie jest rozmowa na ulicy.";
			link.l1 = "Bardzo dobrze... Ruszajmy!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "Kolejkę, kapitanie?";
			link.l1 = "Jasne!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Heh, tutaj faktycznie nie mieszają rumu z wodą...";
			link.l1 = "I nie traktuj klientów zgniłą rybą, tak-tak. Więc w czym rzecz?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "Lubię twoją bezpośredniość, monsieur. Powiedz mi, czy jesteś świadom wojny handlowej między Anglikami a Holendrami?";
			link.l1 = "Jestem. Miałem przyjemność wziąć w tym udział.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Nie ma potrzeby tego wyjaśniać. Jako angielski kaper, walczę po ich stronie w tej wojnie. Ty jesteś głównie freelancerem. Co czyni cię obojętnym na to, po której stronie walczyć...";
			link.l1 = "Prawie. Nie zdradzam Francji, przykro mi.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Jak najbardziej, kapitanie! Więc, do rzeczy: jest mała zamieszkana wyspa pomiędzy Curacao a Trynidadem, nie ma jej na mapach... Od niedawna, powiedziałbym bardzo niedawno, Holendrzy zaczęli jej używać jako tymczasowego przystanku do zaopatrzenia i napraw. Wydaje się, że wierzą, że tylko oni wiedzą o tej wyspie. Błąd. He-he\nKilka dni temu karawan srebra został trafiony przez... sztorm i teraz Holendrzy naprawiają swoje statki na tej wyspie. Okręt flagowy stracił maszt, więc naprawa zajmie trochę czasu. Holendrzy są zajęci naprawami, a załogi są głównie rozproszone po wyspie...";
			link.l1 = "A potem nagle pojawiamy się, by uratować sytuację?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Dokładnie, kapitanie. Sam nie dam rady, ale z tobą - to zupełnie inna historia. Zaryzykujesz? Mam świetny statek, załoga jest znakomita i mam spore doświadczenie. Twoje umiejętności... również są godne pochwały.";
			link.l1 = "Ile mamy czasu?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Dużo, jeśli nie marnujemy czasu i natychmiast ruszymy w drogę.";
			link.l1 = "W takim razie zaopatrzmy się w amunicję i broń, kapitanie Ignacio Marco, i podnieśmy żagle. Jakie są dokładne współrzędne wyspy?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 Północ, 64'11 Zachód. Zrozumiano?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha! Deja vu... Mam to.";
			else link.l1 = "Rozumiem.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Wyruszam do 'Torero'. Będę czekać na ciebie, kapitanie!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Piekielna walka, prawda, kapitanie? Teraz przyjemna część: podzielmy łupy. Połowa idzie dla mnie i moich ludzi.";
			link.l1 = "Bardzo dobrze, zróbmy to...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Kapitanie, co się dzieje? Gdzie jest nasze srebro? Zatopiłeś naszą zdobycz?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "Srebro jakoś się zmarnowało, chociaż zdobyliśmy trochę czerwonego drewna. Podzielmy to.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm.. To bieda. Myślałem, że będzie tego znacznie więcej.";
				link.l1 = "Mamy to, co mamy.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Nieźle, nieźle. Chociaż myślałem, że będzie więcej.";
				link.l1 = "Mamy to, co mamy.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Dobrze wykonane, Monseniour. To jest znakomita zdobycz...";
			link.l1 = "Nie mogę się z tobą nie zgodzić, kapitanie.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Wygląda na to, że masz poważny problem z głową. Odchodzimy! Chłopcy!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "Przynajmniej coś z tego mamy... Chłopaki! Ruszamy!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "To coś. Rozstańmy się.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "To coś. Rozstańmy się. To w końcu sukces, heh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Mieliśmy bardzo dochodowe spotkanie. Być może to nie ostatni raz, gdy robimy interesy razem, kapitanie!";
			link.l1 = "Zawołaj mnie, jeśli znajdziesz więcej tłustych kupców, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "Zakładam, że to nie jest przypadek, kapitanie?";
			link.l1 = "Nie byłbyś mądry, gdybyś tego nie widział. Jesteś mi winien za ustawienie. Wiesz, o czym mówię. Także jesteś mi winien za ustawienie mojego przyjaciela Jeana Picarda. Został sprzedany na plantację po twoim planie... Straciłeś Ignacio. Powieszę cię, ale możesz złagodzić swoją karę...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Zastanawiam się nawet - co mógłbym zrobić, abyś mnie pożałował?";
			link.l1 = "Potrzebuję informacji. Włożę cię do mojego ładowni, gdzie porozmawiamy o twoich planach w Hawanie...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Nie spodziewałem się tego! Nawet o tym nie myśl. Barbazon dowie się o mojej zdradzie w mgnieniu oka. Lepiej nie wiedzieć, co robi z ludźmi, którzy go zdradzili. Widziałem to.";
			link.l1 = "Więc powieszenie to lepsza opcja?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Wolałbym zginąć w walce!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Kapitanie! Kapitanie! Pośpiesz się! Hiszpańska eskadra wojskowa nas ściga!";
			link.l1 = RandSwear()+"Spodziewałem się tego... To samo przydarzyło się Picardowi. Widziałeś, ilu z nich tam było?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Tak, kapitanie. Trzy okręty. Ich flagowy statek to galeon, największy jaki kiedykolwiek widziałem i porusza się szybko, pozostałe dwa to korweta i szebek.";
			link.l1 = "Wszyscy na pokład. Może jeszcze uda nam się uciec.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Ajaj! Cholerny yalanaui wchodzi do naszego lasu! Zabij go! Ajaj!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Hej! Co do diabła tu robisz? A-aha, kradniesz cudze rzeczy? No to masz przechlapane!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Hej! Wszystkich zatrzymać się na miejscu! Albo zaraz was wszystkich posiekam kartaczami! "+RandSwear()+"";
			link.l1 = "Nie ruszamy się teraz nigdzie. Ale słuchaj, kumplu - nie ma mowy, żebyś zabił nas wszystkich jednym strzałem. Niektórzy z nas rozszarpią cię na kawałki, gdy będziesz przeładowywał. Lepiej porozmawiajmy teraz.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Czy to ty tu dowodzisz? Odpowiadaj mi!";
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+"  A ty musisz być zastępcą Czerwonego Wilka, kiedy go tu nie ma, prawda?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "Co ty tu robisz, kapitanie "+GetFullName(pchar)+"Nie zapraszamy gości do tego miejsca!";
			link.l1 = "Jak się zwiesz? Chcę wiedzieć, z kim rozmawiam.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Nazywam się Rodgar Janssen.";
			link.l1 = "Widzę, że wy, chłopcy, jesteście tu w ciemności. Nie macie już kapitana. I wasza korweta też zniknęła. 'Freyja' została zbombardowana przez Hiszpanów nieopodal Hispanioli. Jej załoga została wybita do ostatniego...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+"Wulfric... Aahhh-ghhhhh!!! ... Ale jak mogę wiedzieć, że mówisz prawdę?";
			link.l1 = "Mam dziennik twojego byłego kapitana! Mamy kilka przedmiotów z wraku Freyi. Dzięki dziennikowi znalazłem tę wyspę i te... twoje skarby.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Heh! Nadal jesteś mi winien odpowiedź: dlaczego jesteś tutaj na tej nieznanej ziemi?";
			link.l1 = "Nie będę kłamać, kumplu. Mówią, że Czerwony Wilk posiadał niemały majątek. Jestem tutaj, aby go znaleźć, ponieważ na jego statku nie znaleziono żadnego skarbu. Uważam, że powinny należeć do porządnych ludzi, bo Wulfricowi i tak już się nie przydadzą.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha! Mate, rozczaruję cię: ani ja, ani nikt z załogi nigdy nie widział skarbów Wilka. Było zbyt ryzykowne, by go pytać.";
			link.l1 = "W takim razie powinienem ich poszukać w twojej wiosce. Odłożysz broń, czy mam zacząć szturmować wioskę? Nie masz szans, Rodgar. Przyprowadzę więcej ludzi i armat, jeśli będzie trzeba.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Zanim zginiemy, zabierzemy ze sobą do piekła wielu z was, łajdaki! Może i ciebie też!";
			link.l1 = "Jesteś pewien? Nie masz kapitana, nie masz statku i nikt nie przyjdzie cię uratować. Nawet jeśli po prostu odejdę, wkrótce wszyscy umrzecie z głodu!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Hmm... masz jakieś sugestie?";
			link.l1 = "Tak, mam. Odsuń się od działa i trzymaj swoich ludzi na wodzy. Przysięgam, że nie zrobię krzywdy tobie ani twoim ludziom. Jeśli chcesz, możesz dołączyć do mojej załogi, albo zabierzemy cię do jakiejś cywilizacji.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Przysięgnij to przed swoimi ludźmi głośno i wyraźnie!";
			link.l1 = "Przysięgam! Masz moje słowo: ty i twoi ludzie nie zostaniecie skrzywdzeni.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "Mam nadzieję, że dotrzymasz słowa, kapitanie.";
			link.l1 = "Zawsze tak robię. Ilu z was zostało?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Widzisz nas wszystkich. Trzech. Reszta zginęła w dżungli, atakując cię. Mówiłem im, żeby tego nie robili, ale nie posłuchali...";
			link.l1 = "Widzę...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "Jedzenie się kończyło. Zaczęliśmy polować na papugi. 'Freyja' zniknęła na zbyt długo. Mieliśmy swoje podejrzenia i one się potwierdziły.";
			link.l1 = "Dzięki Bogu, że postanowiłem wyruszyć na poszukiwanie skarbów. Gdzie myślisz, że je ukrył?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Już ci mówiłem: nikt ich nigdy nie widział. Wulfric był ostrożny z swoją częścią, nigdy nie pozwalał, aby się zmarnowała. Był wobec nas uczciwy, ale każdy, kto próbował znaleźć jego skrytkę, zaginął. Możesz przeszukać wioskę, jeśli chcesz.";
			link.l1 = "To mój plan. Gdzie jest dom Czerwonego Wilka?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "Jedyny dwupiętrowy budynek, jaki tu mamy.";
			link.l1 = "Dobrze. A tak przy okazji, czym się zajmujesz?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"),"Islamona");
            dialog.text = "Jestem cieślą, a ci dwaj to moi pomocnicy. Zajmowaliśmy się naprawą i udoskonalaniem 'Freyja' wcześniej. Możemy się przydać w twojej załodze.";
			link.l1 = "Widzę. Bardzo dobrze, jesteś w grze, o szczegółach porozmawiamy później. Weź ten pistolet z wejścia. A Rodgar, nie opuszczaj wioski, gdy szukam skrytki.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Rozkazy, kapitanie?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Tak. Skarby twojego kapitana zostały odnalezione. Dobrze je ukrył, ale przechytrzyłem go!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, co sądzisz, czy jest coś jeszcze, co możemy zrobić z tą bazą?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, przyniosłem narzędzia. Powinny już były zostać dostarczone do ciebie.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Witaj! To jest Rodrigo Jimenez, przywódca niewielkiej, lecz bardzo pracowitej społeczności z Kadyksu. Señor Jimenez uprzejmie zgodził się tymczasowo osiedlić na naszej ziemi i pomóc nam w budowie.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgarze, jak się masz? Masz dla mnie jakieś dobre rady?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, potrzebuję przysługi.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && GetCharacterItem(pchar, "gold_dublon") >=600)
			{
				link.l1 = "Przyniosłem dubloony dla ciebie, tylko nie przepij ich wszystkich od razu.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, sprawdź magazyn. Przywiozłem lekarstwa i zapasy.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Cześć, Rodgarze, jak sprawy w nowej osadzie?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, mój statek potrzebuje napraw. Czy ty i twoi ludzie jesteście gotowi?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgarze, chciałbym zostawić tutaj jeden z moich statków.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgarze, chciałbym odzyskać jeden z moich statków.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Spójrz, czy jest jakiś pusty budynek, który mógłbym wykorzystać jako magazyn?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, chcę zobaczyć magazyn.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, chcę zostawić część załogi na wyspie.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, chcę zabrać swoich marynarzy z powrotem na morze.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Jeszcze nic...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Gratulacje, kapitanie. Co robimy dalej? Odpływamy?";
			link.l1 = "Czy byłeś tu długo?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Zbyt długo. Minął rok, odkąd Wulfric powierzył mi tutaj dowodzenie.";
			link.l1 = "Zdecydowałem, że ta tajna baza jest zbyt dobra, by ją zmarnować. Wioska jest teraz moja. Mogę zostawić ciebie i twoich ludzi tutaj, jeśli chcesz. Rum, zapasy, medykamenty - wszystko twoje.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Byłoby wspaniale, kapitanie. Przyzwyczaiłem się do życia na tej plaży, na tej wyspie.";
			link.l1 = "Wspaniale. A tak przy okazji, jak nazywa się ta wyspa?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Być może pewnego dnia zbudujemy tu więcej domów i budowli... Ale później. Na razie będziesz pełnił tę samą rolę tutaj, ale pod nowym kapitanem.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Umowa stoi. Ty tylko dbaj o siebie, kapitanie, i nie zapomnij zaopatrywać nas w prowiant.";
			link.l1 = "Oczywiście, Rodgarze. Powodzenia, powinienem popłynąć do La Vega.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "Trudno powiedzieć, Kapitanie. Świętej pamięci Wulfric nigdy nie zostawiał tu więcej niż dwudziestu ludzi. Teraz jest nas tylko trzech,"+sTemp+"Niewiele możemy zrobić.";
			link.l1 = "Czy chcesz powiedzieć, że gdyby mieszkało tu więcej ludzi, mógłbyś przekształcić to miejsce w pełnoprawną osadę?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "Wyspa jest mała, więc nie można na niej założyć kolonii, ale osada jest całkowicie możliwa! Można łowić ryby, polować na ptaki i kozy, zbierać owoce. Możemy się utrzymać, ale nie wzbogacimy się na tym.\nAle jest jedna rzecz, której nie do końca rozumiem, Kapitanie. Dlaczego ci to potrzebne?";
			link.l1 = "To jest mój dom i moja ziemia, moi ludzie. Kim się stanę, jeśli się nimi nie zaopiekuję?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "Chcę zainwestować pieniądze w dochodowy interes.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "Ta mała wyspa znajduje się w samym sercu tego regionu. Byłoby rozsądne przekształcić ją w pełnoprawną i sekretną bazę wojskową.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "Martwię się o ciebie, Rodgarze, wszyscy wy kompletnie oszaleliście na tym etapie.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "Jesteś dziwny. Cóż, nieważne. Przynajmniej będzie coś do roboty...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "Jesteś dziwny. Cóż, nieważne. Przynajmniej będzie coś do roboty...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "Jesteś dziwny. Cóż, nieważne. Przynajmniej będzie coś do roboty...";
			link.l1 = " ";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "Jesteś dziwny. No cóż, nieważne. Przynajmniej będzie coś do roboty...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "Przede wszystkim, będziesz musiał znaleźć bardzo specjalnych ludzi. Tych, których można przekonać do przeniesienia się na tę dzicz, by żyli i pracowali tutaj przez lata, w całkowitej izolacji od reszty świata. To właśnie takich wyjątkowych ludzi będziesz musiał szukać. Mam nadzieję, że nie tylko jednego. W końcu, nie możesz rozkazać swojej załodze, by tu mieszkała, przynajmniej jeszcze nie teraz. Koloniści nie chcieliby opuszczać swoich ustalonych domów i stabilnych prac. A my sami nie potrzebujemy tutaj włóczęgów i innych nieudaczników.\nPonadto, kwestia tajemnicy otaczającej tę wyspę zawsze będzie obecna. Jeśli komuś powiesz, natychmiast pojawi się zagrożenie ze strony łowców, którzy będą chcieli zbadać sprawę.";
			link.l1 = "Rozumiem, jakieś sugestie?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "Nie, kapitanie. Byłem tu zbyt długo i całkowicie straciłem kontakt z cywilizowanym życiem.";
			link.l1 = "Świetnie, to pomocne!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "Pracuję z drewnem, nie z ludźmi. I bardzo mnie to cieszy, ha-ha! A tak przy okazji, oprócz ludzi, będziesz musiał tu również przywieźć zestaw wysokiej jakości narzędzi do kuźnictwa i budownictwa. Są one produkowane tylko w starej Europie, więc będą cię kosztować niemało grosza. Zapytaj właścicieli stoczni, tych większych.";
			link.l1 = "Wszystko jasne. Podsumujmy: jeśli chcę przekształcić tę bazę w coś większego, muszę sprowadzić tu więcej osadników i narzędzi?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "To prawda!";
			link.l1 = "Zobaczę, co da się zrobić.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Tak jest, Kapitanie! Pierwszorzędny zestaw, jesteśmy gotowi budować kolonię! Czy to było kosztowne?";
			link.l1 = "Kosztowało mnie to fortunę, mam nadzieję, że było warto!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "Kilka lat temu powiedziałbym, że to bardzo drogie. Ale teraz... nawet nie wiem.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "Nie mogłeś zadowolić się tym, co już miałeś, prawda? W każdym razie, bądź gotów na to, że twoje wydatki będą tylko rosły. Czy rozwiązałeś sprawę z osadnikami?";
			link.l1 = "Nie, Rodgarze. Jeszcze nie dowiedziałem się, gdzie ich znaleźć. W końcu nie mam suwerennych praw do zakładania osiedli na tych wodach.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "Nie mogłeś się zadowolić tym, co już miałeś, prawda? W każdym razie, bądź przygotowany na to, że twoje wydatki będą tylko rosnąć. Czy rozwiązałeś problem z osadnikami?";
			link.l1 = "Nie, Rodgarze. Jeszcze nie ustaliłem, gdzie ich znaleźć. W końcu nie mam suwerennych praw do zakładania osiedli na tych wodach.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "Na tych wodach, kapitanie, każdego dnia panuje chaos. Posłuchaj, co mówią ludzie, może dostrzeżesz ukrytą okazję. Ja zajmę się narzędziami na razie.";
			link.l1 = "Dobrze, będę wypatrywać takich informacji.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "Hiszpanie? Kapitanie, musisz żartować. Myślałem, że przyprowadzisz obiboków z Le Francois, a nie tych...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Czy jesteś z Europy? Hehe, nie trudno to zgadnąć. Nie martw się, przyzwyczaisz się.";
			link.l1 = "Jimenez, zatrzymasz się u mnie na jakiś czas. Jest tam piwnica, dużo miejsca. Rodgar, przyniosłem narzędzia i osadników również. Co dalej?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "Do zobaczenia jutro, Kapitanie. Porozmawiamy za dzień, gdy ci... osadnicy osiedlą się ze swoimi skarbami...";
			link.l1 = "Dobrze, będziemy kontynuować jutro.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Kapitanie, porozmawiaj z Hiszpanem. On już w pełni zaangażowany w swoją pracę.";
			link.l1 = "Zrozumiałem, zrobię to.";
			link.l1.go = "IslaMona_19";
			link.l2 = "Czy coś jest nie tak?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Kapitanie, leniuchuję tu z chłopakami od kilku lat. Teraz, ta gorączkowa aktywność Hiszpanów zaczyna działać mi na nerwy.";
			link.l1 = "Żadnych konfliktów! I zakazuję tobie i twoim ludziom nawet patrzeć w stronę ich kobiet! Przynajmniej na razie... Jeśli sytuacja się zaostrzy, weźcie szalupę i idźcie... na ryby na parę dni.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Tak jest, panie!";
			link.l1 = "Doskonale. Dobrze, pójdę zobaczyć, co on knuje.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "Już wiem, kapitanie. Hiszpan chce, żebyśmy zbadali wyspę? Skakać po skałach z mapą jak banda idiotów?";
			link.l1 = "To prawda, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Sześćset doublonów i zrobię to.";
			link.l1 = "Jesteś szalony? Ugryzł cię lokalny pająk czy jadowity wąż? Co zamierzasz zrobić ze skrzynią złota na bezludnej wyspie? Zakopać ją?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Chodź, kapitanie. Pewnego dnia opuścimy to miejsce, a kto będzie nas potrzebował w wielkim świecie bez grosza przy duszy? Oczywiście, mamy ukryty mały skarb, ale to zdecydowanie za mało. Wulfric nigdy nie wyrównał swoich długów z nami i chłopakami za jego ostatnie przedsięwzięcia.\nTo jedno, by lenić się na plaży przez miesiące i serwisować swoją flotę raz na pół roku. Ale ciężko pracować na stałym lądzie każdego dnia, jak przeklęty bukanier - to zupełnie inna historia! To praca, a praca płaci. Płacisz swojej załodze, prawda, kapitanie?";
			link.l1 = "Brzmi rozsądnie. Zdobędę dla ciebie te 600 dublonów. Mam nadzieję, że nie oczekujesz zapłaty z góry, prawda?";
			link.l1.go = "IslaMona_23";
			link.l2 = "Mam inną propozycję. Pracujesz na lądzie, nie zeskrobując pąkli z okrętów na morzu. Teraz pilnie potrzebujemy takiej pracy.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Kapitanie, jestem gotów zacząć od razu, ale moi ludzie będą pracować znacznie ciężej, gdy zobaczą dubloony w swoich rękach. Obiecuję, że nie zostawimy ani kawałka niezbadanej ziemi na tej wyspie.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "Dobrze. Oto twoje złoto. Tylko nie zmarnuj go od razu na trunki.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "Dobrze, przyniosę ci twoje dublony.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha! Masz rację, kapitanie! Och, prawie zapomniałem. Teraz mieszka tu całkiem sporo ludzi i potrzebują czegoś do jedzenia. Widziałeś te damy? Nie są przyzwyczajone do przetrwania i żywienia się z ziemi. Nie będą żadną pomocą.";
			link.l1 = "Tylko nie mów mi, że będę musiał znaleźć więcej bukanierów, żeby ci pomóc.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Tak jest, kapitanie! Jesteśmy gotowi do pracy na lądzie! Ach, i jeszcze jedno, prawie zapomniałem. Teraz mieszka tu całkiem sporo ludzi i potrzebują czegoś do jedzenia. Widziałeś te damy? Nie są przyzwyczajone do przetrwania i zdobywania pożywienia na ziemi. Nie będą żadną pomocą.";
			link.l1 = " Tylko nie mów, że będę musiał szukać jeszcze i bukanierów na waszą pomoc.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "Nie, dlaczego mielibyśmy? Wyszkolimy i przygotujemy najbardziej zdolnych spośród nich do życia. Ale dopóki ten cudowny moment nie nadejdzie, będziesz musiał dostarczać nam jedzenie. Wystarczą parę tysięcy zestawów zaopatrzenia okrętowego. I kwintal lekarstw na przyszłość. Rozładuj to wszystko z okrętów do naszego magazynu na wyspie.";
			link.l1 = "Zrobię to. Ile czasu potrzebujesz na misję zwiadowczą?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "Zakończymy za dwa-trzy dni, już znaleźliśmy kilka interesujących rzeczy.";
			link.l1 = "Świetnie!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "Jak tylko skończymy, ruszaj prosto do tego śmiejącego się Hiszpana. Ten szaleniec musi wyciągnąć wnioski z naszej pracy.";
			link.l1 = "Widzę, że już prawie się zaprzyjaźniliście. Odwiedzę go więc za trzy dni. No cóż, oby do pracy. Powodzenia dla nas wszystkich!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Wow! Dzięki, Kapitanie. Teraz mamy czas, by przygotować panie na to szalone życie na wolności.";
			link.l1 = "Tylko uważaj, żebyś nie zrobił z nich piratów! Dziękuję, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Kapitanie! Muszę przyznać, że zaczynam się czuć nieco nieswojo mieszkając tutaj.";
			link.l1 = "Dlaczego tak, Rodgarze? Tęsknisz za urokiem biedy i ruiny?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "Można tak powiedzieć. Teraz cywilizacja dociera nawet tutaj. A ludzie tacy jak ja nie mają w niej miejsca.";
			link.l1 = "Kup sobie żabot i laskę. Wpasujesz się idealnie.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Raczej chodźmy zobaczyć się z twoim Hiszpanem i omówić wyniki zwiadu. Mam jeszcze jeden szalony pomysł...";
			link.l1 = " Właśnie z nim rozmawiałem! Dobrze, chodźmy, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "Jak ci się podoba praca z nim?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Wysoko wykształceni i pracowici ludzie! A Jimenez to prawdziwy mistrz. W dawnych czasach można było za takich ludzi dostać sporo złota. A ich dziewczyny są również piękne...";
			link.l1 = "Nie chcę tego słyszeć, Rodgar! Chodźmy porozmawiać z naszym panem";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "Jeśli nie poradzą sobie z robotą, sprzedamy ich. Ale dziewczyny zostawimy, ha-ha! Chodźmy zobaczyć mistrza.. ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Serio, kapitanie? Tylko żartowałem, chodźmy...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "Wiedziałem, że mnie wesprzesz, Kapitanie! Ruszajmy...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "Nie śmieje się, kapitanie...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "To również, kapitanie. Omówimy to później...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "Szlachcic ma rację, Kapitanie. Żaden z nas nie będzie się łamał w dżungli. Interes może być brudny, ale nic więcej z tego miejsca nie wyciągniesz, jak tylko gniazdo piratów.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Captain, when you build the factory, the slaves will need protection. My guys will take care of that. One of them even shoots like Thor with lightning. Nothing motivates work like a hunting scope. We already have one gun; now we need a second. Any musket will do.";
			link.l1 = "I'm sorry, I need the English text to perform the translation. Could you provide the text you want translated?";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "I moi ludzie będą potrzebować takiej samej ilości złota i jeszcze tuzina butelek dobrego rumu.";
			link.l1 = "Ile drewna jesteście w stanie dostarczyć w każdej partii? I dlaczego potrzebujecie złota?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Cóż, przede wszystkim życie bez wypoczynku jest bezsensowne, a wkrótce nawet pobożni, hehe, katolicy zaczną wspinać się po ścianach. A po drugie, jeśli na wyspie jest tawerna, będziesz mógł zostawić tu część załogi w pogotowiu. Widzisz, przekonanie ludzi do życia jak dzikusy za darmo w chatkach na plaży przez cały rok jest dość trudne. Ale jeśli w pobliżu jest osada z tawerną, ciepłym jedzeniem, muzyką i rozrywką... Czego jeszcze potrzebuje marynarz na przepustce?";
			link.l1 = "Kurwy?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Napoje?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "Masz rację, ale rozwiążmy problemy po kolei. Najpierw odbudujemy twój dom...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "On nawet o tym nie pomyślał, kapitanie.";
			link.l1 = "Dziękuję, Rodgarze. Rozumiem, że teraz będę mógł obsługiwać więcej statków w tej małej zatoce, prawda?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Witaj, Kapitanie! Przyszedłeś omówić pracę?";
			link.l1 = "Nie, wcale nie. Po prostu tęskniłem za twoją północną fizjonomią.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Może pójdziemy? Pokażę ci twoją fabrykę.";
			link.l1 = "Prowadź.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hik! Kapitanie, świętujemy!";
			link.l1 = "Rodgar! Rodrigo! No cholera!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "Co się stało, k-k-kapitanie? Nie podoba ci się kolor ścian?";
			link.l1 = "Dopiero teraz uświadomiłem sobie, że wy dwaj macie takie samo imię! Ha-ha-ha! Hiszpan i pirat, z tym samym imieniem, zbudowali tawernę na bezludnej wyspie i piją razem, jakby bogowie indyjscy mieli pożreć wszystkich i zakończyć świat o wschodzie słońca! Ha-ha! Jestem z wami!";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ha-ha-ha! Tak prawda! Na zdrowie!";
			link.l1 = "Zdrowie!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Chcesz drinka, kapitanie?";
			link.l1 = "Czy zostajesz karczmarzem, Rodgar?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Na chwilę! Hiszpanie szczególnie cenią sobie pirata za barem - to dla nich prawdziwa egzotyka i przygoda. Ale ogólnie, jest tu miło. Jeśli zdecydujesz się zostawić kogoś z załogi w tym osiedlu na zapas, po prostu daj mi znać - zorganizuję to.";
			link.l1 = "Gdzież oni będą mieszkać?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Proste - zbudujemy kilka chat na plaży. W ten sposób będą biegać z tawerny do brzegu. Przypomnienie, ta wyspa nie pomieści więcej niż trzysta osób, więc miej to na uwadze na przyszłość. Czasami poprosimy cię, byś przyniósł rum i wino, więc byłoby wspaniale, gdybyś ty, Kapitanie, mógł z wyprzedzeniem zaopatrzyć magazyn w te towary.";
			link.l1 = "Zapamiętam to. No cóż, compadre. Zabaw Hiszpanów i odpocznij. Tylko proszę, nie pij do momentu, aż cała wioska spłonie - nie zniosłabym tego widoku!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Kapitanie! Do diabła, cieszę się, że cię widzę! Dzięki Freyji, przybyłeś w samą porę!";
			link.l1 = "Aj, wpakowaliśmy się w kolejną niezłą kabałę. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "Bez strat w ludziach. Ocalali Hiszpanie dotarli do nas pierwsi, zgłosili, że istnieje możliwość spotkania większej liczby gości, i udało nam się przynieść prawie wszystkie zapasy i sprzęt z okolicy do osady. Sytuacja z niewolnikami nie potoczyła się oczywiście dobrze.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "A co, jeśli wciągną nas w otwarty atak?";
			link.l1 = "W takim razie działamy bez broni. Jak na paradzie, maszerujemy razem do bram, a potem atakujemy ich od tyłu. Ty trzymasz bramy i zapewniasz wsparcie. To wszystko, powodzenia nam!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Hura, Kapitanie!";
			link.l1 = "Zgoda! To było takie bum, że sam chciałem się położyć. Chłopaki, co tam załadowaliście?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Podwójny ładunek, Kapitanie. By jeden wystrzał zniechęcił ich do dalszej walki!";
			link.l1 = "Czyż nie obawiałeś się, że broń wybuchnie z tak delikatnym traktowaniem?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "Mam specjalny talizman pozostawiony przez Wulfrica. Jakieś wspomnienie naszej rodzimej Danii. Czy pójdziemy wszyscy do tawerny, kapitanie? Wszyscy jesteśmy zmęczeni po dzisiejszym dniu.";
			link.l1 = "Tak, to byłoby świetne. Zagrajmy w karty - postawimy na twój cudowny talizman.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, po takim boskim występie dzisiaj, kapitanie, mogę nawet rozważyć tę opcję!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Kapitanie, czy słyszałeś to? Nadal dzwoni mi w uszach. Czyj to żałosny głos?";
			link.l1 = "To, Rodgarze, jest żywym problemem. Zabierz go do fabryki, przykuj do łańcucha i czekaj na dalsze instrukcje.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Tak jest, kapitanie!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Kapitanie, czy przyszedłeś rozwiązać sprawę z więźniem? Jestem zmęczony staniem tutaj na straży.";
			link.l1 = "Musimy go zabić. Ryzyko jest zbyt duże, więc nie mamy wyboru. W przeciwnym razie lepiej nie pokazywać się we francuskich koloniach.";
			link.l1.go = "IslaMona_79";
			link.l2 = "Nie mogę go puścić, bo w przeciwnym razie lepiej, żebym się nie pokazywał w francuskich koloniach. Załóżcie mu kajdany i niech pracuje w fabryce. To lepsze niż go zabić.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Zrozumiano! Załatwmy to szybko. Śmiało, kapitanie. Do zobaczenia jutro.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Wow. Jesteś niezłym geniuszem zła. Nie chciałbym być twoim wrogiem. No cóż, najpierw musimy przeprowadzić z nim pewne wyjaśniające działania. Śmiało, Kapitanie. Do zobaczenia jutro.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "Co za rzeź! Szkoda, że nie mogliśmy strzelać z armaty, ale wpadli prosto w twoją zasadzkę - miło było patrzeć!";
			link.l1 = "Tak, na tej ziemi przelaliśmy wiele krwi. Ale najwyraźniej nie ma innego sposobu na zbudowanie domu w tym świecie.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Nie rozmyślaj nad tym zbyt wiele, Kapitanie. To los sam przywiódł ich na Isla Mona. A powiem ci, los potrafi być prawdziwą suką!";
			link.l1 = "Przeznaczenie, czy wyspa?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "Obaj odegrali swoją rolę.";
			link.l1 = "Haha! I oba są piękne! Dobra, dzielny Wiking. Zbierz trofea i usuń te ciała. Pochowaj je z godnością. To w końcu nasi własni...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Tak, Kapitanie. To prawda! Rodrigo powiedział to tak pięknie, że łza zakręciła mi się w oku. Jasne, dlaczego święci ojcowie chcą nadziać jego zadek na pal!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, a tu wpadłem prosto na naszego prałata w buduarze... I powiem ci, to najlepszy przybytek w Santiago!";
			link.l1 = "Najlepsze miejsce, jeśli lubisz także prałatów.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "Tak, rzeczywiście zmienił łotra i heretyka Rodrigo w prawdziwego pirata.";
			link.l1 = "Przy okazji, oświeć mnie, Rodgarze. Dlaczego jest tak mało hiszpańskich piratów?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = " Dlaczego tak mało? Ach, masz na myśli kapitanów piratów? Cóż, jest ich mnóstwo, tylko że głównie działają pod Casa de Contratación w Sewilli. To jak wojskowy wywiad, ale z jakiegoś powodu nazywają to domem handlowym...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Tak, dlaczego by nie wysłać im wiadomości i zaprosić ich tutaj. Cóż, wszyscy mają patenty, a do tego są idealistami. Zwykle nie rabują swoich, tylko gdy rajd się nie udał, ha-ha! Zatrzymują się tylko w Puerto Principe i nieustannie ścierają się z Pastorem.\nOstatnio jeden się wyróżniał... Diego de Montoya. Kiedy ostatni raz wyruszyłem na kampanię z Wulfrikiem, dużo słyszałem o jego przygodach. Ty, kapitanie, masz z nim coś wspólnego. A jednocześnie jesteś bardzo różny... W każdym razie, o czym ja mówię? Wypijmy jeszcze jedną kolejkę i zagrajmy w karty.";
			link.l1 = "Nie masz żadnych pieniędzy. Nie grasz chyba w dublony, co?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "Stawiamy po jednym peso każdy. Gramy do dwudziestu? Hymenes, wchodzisz?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Zagrajmy, kapitanie?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Zaczynaj to!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "Ja też podziękuję, Rodgarze. Pesos czy nie, ludzie tracą w ten sposób statki. Z wyspami. Baw się dobrze tutaj, a ja jeszcze się rozejrzę.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Przechodzę! No cóż, nie gram z tobą więcej! Jestem pewny, że oszukiwałeś, kapitanie! A pozwolenie oszustowi odejść tak po prostu nie byłoby w porządku!";
				link.l1 = "Słucham cię, Rodgarze.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Wygrałem, kapitanie. Ale nie mogę pozwolić, byś odszedł z pustymi rękami, haha!";
					link.l1 = "Dobrze, łotrze. To będzie dla mnie nauczka...";
				}
				else
				{
					dialog.text = "Ja wygrałem, kapitanie. Ale nie mogę pozwolić, żebyś odszedł z pustymi rękami, haha!";
					link.l1 = "Dobrze, łotrze. To będzie dla mnie nauczka...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ach, no dalej! Dałeś mnie i mojej załodze szansę na prawdziwe życie z dala od ciasnych kajut, stęchłej wody i ryzyka dostania odłamka w... czaszkę. Tutaj. Ten amulet został przywieziony przez Wulfrika z dalekiej Danii, a potem przekazany mi, żebym... heh, nie musiał za bardzo zagłębiać się w jego piwnicę. Już go nie potrzebuję, ale ty - och, znajdziesz go całkiem przydatnym.";
			link.l1 = "Dziękuję, Rodgar. Rzeczywiście, użyteczny przedmiot. I piękny również...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Zachowaj to, Rodgarze. Bez ciebie, to miejsce by nie istniało. Niech to będzie przypomnieniem o twojej ojczyźnie.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "Cieszę się, że ci się podobało, kapitanie. Kolejna kolejka?";
			link.l1 = "Wy tutaj odpocznijcie, a ja rozejrzę się jeszcze trochę.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "Jak sobie życzysz! To dam jednego szczęściu, haha! Kolejna kolejka?";
			link.l1 = "Wy chłopaki odpocznijcie tutaj, a ja rozejrzę się jeszcze trochę.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Cóż, Kapitanie. Załatwiłeś sprawy z Hiszpanem, mieliśmy naszą uroczystość, a ból głowy trochę ustąpił. Życie jest dobre!";
			link.l1 = "Co knujesz, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "Jak zwykle będę polować, pilnować mojej... naszej tawerny, kopać niewolników w fabryce. Idealna emerytura.";
			link.l1 = "Jesteś tylko pięć lat starszy ode mnie, Rodgarze. A co z tobą, Rodrigo? Jak się miewasz?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Jak najbardziej, kapitanie! Wszystko, czego potrzebujemy, to deski i płótno żaglowe. Idź na miejsce lądowania i rozkaż załodze przygotować materiały.";
				link.l1 = "Już idę. Zrób to szybko.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Oczywiście, kapitanie, ale jak widzę, twoja łajba teraz nie potrzebuje naprawy.";
				link.l1 = "Po prostu zapytałem...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "To możliwe, kapitanie. Są jednak pewne ograniczenia: na tej wyspie są tylko dwa miejsca odpowiednie do tego. Ponadto, nie możesz tu zostawić nikogo oprócz jednego oficera dla każdego statku. Po prostu nie mamy jeszcze wystarczających zasobów, aby utrzymać tutaj załogi. I wreszcie, nie ma miejsca dla statków pierwszej klasy.";
			link.l1 = "Zrozumiano. Jestem gotów zostawić tu statek.";
			link.l1.go = "shipstock";
			link.l2 = "Bardzo dobrze, przygotuję ją.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Kapitanie, na nabrzeżu są już trzy z twoich statków. Nie ma więcej dostępnego miejsca.";
					link.l1 = "Masz rację, zapomniałem.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Kapitanie, przy nabrzeżu już stoi zakotwiczony okręt pierwszej klasy. Nie ma już wolnego miejsca.";
						link.l1 = "Masz rację, zapomniałem.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Kapitanie, dwa z twoich statków są już zakotwiczone przy nabrzeżu. Nie ma więcej dostępnego miejsca.";
					link.l1 = "Masz rację, zapomniałem.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Kapitanie, masz tylko jeden statek.";
				link.l1 = "Hm... Powinienem mniej pić...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Jaki statek chcesz tu zostawić?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Czekaj, zmieniłem zdanie.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Zobaczmy...";
			Link.l1 = "Bardzo dobrze.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Czekaj, zmieniłem zdanie.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Zobaczmy...";
			Link.l1 = "Bardzo dobrze.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Czekaj, zmieniłem zdanie.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Zobaczmy...";
			Link.l1 = "Bardzo dobrze.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Poczekaj, zmieniłem zdanie.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Zobaczmy...";
			Link.l1 = "Bardzo dobrze.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Czekaj, zmieniłem zdanie.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Kapitanie, wspominałem wcześniej, że nasza kotwicowisko może pomieścić tylko jeden okręt pierwszej klasy. Jest zbyt duże na dostępne miejsce.";
					Link.l1 = "Masz rację, zapomniałem.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Kapitanie, okręty pierwszej klasy są zbyt duże dla naszych wybrzeży. Już ci to mówiłem.";
					Link.l1 = "Masz rację, zapomniałem.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Kapitanie, zabierz całą jej załogę na swój okręt flagowy, z wyjątkiem oficera.";
				Link.l1 = "Ach, racja! Zrobię to!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Zatem, mamy tu zatrzymać"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Akceptuj")+" nazwany '"+chref.Ship.Name+"'. Prawda?";
			Link.l1 = "Dobrze.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Poczekaj, zmieniłem zdanie.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
			if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				npchar.FstClassInHarbour = 1;
			}
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Bardzo dobrze, dostarczymy ją do bezpiecznej przystani.";
			Link.l1 = "Doskonale!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Który statek zamierzasz wziąć, kapitanie?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Poczekaj, zmieniłem zdanie.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Kapitanie, nie masz miejsca w swojej eskadrze na jeszcze jeden statek.";
				link.l1 = "Hm. Wygląda na to, że masz rację.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Zabierasz ją?";
			link.l1 = "Tak.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Zaczekaj, zmieniłem zdanie.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Tu? Nie. Ale Wulfric zbudował ogromną stodołę niedaleko stąd. Solidna budowla, dobrze pokryta liśćmi palmowymi i nasmołowanym płótnem żaglowym. Ma zamek i pomieszczenie na ładunek wystarczający, by wypełnić tuzin statków handlowych\nTeraz jest pusta, ale mam klucz, jeśli chcesz ją obejrzeć. Ruszamy?";
			link.l1 = "Oczywiście! Przy okazji: co z szczurami na tej wyspie? Czy zniszczą moje towary w stodole?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Wilk też o to zadbał: przywiózł tu dwa koty z kontynentu. Zapomniał jednak o samcach, więc te szalone futrzane suki wydają okropne dźwięki za każdym razem, gdy przychodzi ich sezon. Ale świetnie polują na myszy i szczury. Nie martw się, kapitanie. Twoje towary będą bezpieczne od szkodników i wiatrów.";
			link.l1 = "Świetnie! Zrobię z tego dobry użytek. Trzymaj klucz przy sobie i pokaż mi ten magazyn.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Chodź za mną, kapitanie.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ach...";
			link.l1 = "Cóż to... Dziewczyna... Co ty tu robisz?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Och...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Senor! Senor "+pchar.name+" nie zabijaj mnie, proszę! Błagam cię! Nic nie powiem Tyreksowi! Nienawidzę tego potwora! Błagam cię, por favor!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Hej, dziewczyno! Słyszałaś to? Pójdziesz ze mną, albo ten twardy drań cię zabije.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Pójdę z tobą, señor, dokądkolwiek mnie zabierasz!";
			link.l1 = "Dobrze więc. Trzymaj gębę na kłódkę, bo cię zabiję, jeśli zaczniesz wrzeszczeć lub wołać Tyreksa. Jak się nazywasz?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Zachowuj się dobrze, Mirabelle, a skończy się to dla ciebie dobrze. Trzymaj się blisko mnie i nie rób hałasu.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Przysięgam, że nie będę, señor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Señor?";
			link.l1 = "Spisałaś się dobrze, dziewczyno, to mi się podoba. Teraz idziemy na mój statek, gdzie zostaniesz umieszczona w małej kajucie na jakiś czas. Przykro mi, ale nie chcę, żebyś pobiegła do Tira i powiedziała mu cokolwiek.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "Nie ma mowy señor! Nigdy bym nie poszedł do Tyrexa, este bastardo! Nienawidzę go! Lo odio!!!";
			link.l1 = "Ło! Co on ci zrobił?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Wiele... Nienawidzę go, nienawidzę go!";
			link.l1 = "Rozumiem. Gdy dotrzemy na miejsce, będziesz mieszkała w całkiem eleganckim domu. Sama. Trzymaj mnie w dobrym humorze, a nikt cię nigdy nie skrzywdzi. Teraz idź do łodzi... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Czy dotarliśmy, señor?";
			link.l1 = "Tak, kochanie. To moja wioska i mój dom. Jestem właścicielem tego miejsca. Rzadko tu jednak bywam - zbyt wiele pracy czeka na mnie tam na zewnątrz. Upewnij się, że utrzymujesz mój dom w czystości, gdy w nim mieszkasz, inaczej oddam cię Rodgarowi i jego stolarzom. Swobodnie spaceruj po wyspie, jest bardzo piękna, ale i tak nie ma z niej ucieczki.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Cóż, oto jesteśmy. To jest mój dom. Wszystko na tej wyspie należy do mnie. Nie bywam tutaj często - w końcu mieszkam na statku, ale ktoś musi zajmować się domem. Rodgar łaskawie zgodził się przekazać ci tę honorową rolę. Możesz chodzić, gdzie chcesz, nawet po dżungli czy plażach, ale upewnij się, że masz towarzysza, bo wciąż są tu dzikie zwierzęta. W każdym razie, nie możesz stąd odpłynąć bez statku.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "Nie mam dokąd uciec, señor "+pchar.name+"Nie mam nikogo, i nikt mnie nie potrzebuje. Chyba że sprzedasz mnie do burdelu...";
			link.l1 = "Przy palenisku jest klapa, która prowadzi do podziemi, nie idź tam, bo wpadniesz do jaskini i złamiesz sobie kości, albo nie będziesz mógł wrócić i możesz umrzeć z głodu. I wtedy szkoda będzie, że uratowałem cię na próżno.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "Nie mam gdzie zostawić señor "+pchar.name+"Nie mam rodziny ani żadnego pożytku. Mogę znów skończyć w burdelu.";
			link.l1 = "Tam jest właz prowadzący do jaskini, trzymaj się od niego z daleka. Tam na dole jest ciemno i niebezpiecznie.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Trzymam się z daleka, señor.";
			link.l1 = "Na górze jest także sypialnia. Chodź za mną.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "Tam. Pokazałem ci cały dom. Nie jest gorszy niż miejsce Tyrexa, w którym mieszkałeś wcześniej. Mam nadzieję, że ci się podoba.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Tak, señor. Masz wspaniałą rezydencję. Obiecuję dobrze się nią opiekować podczas twej nieobecności.";
			link.l1 = "Cieszę się, że jesteś wobec mnie tak współpracująca. Mam nadzieję, że jesteś szczera. Bądź szczera ze mną, bo inaczej będziesz tego żałować. Bądź dobrą dziewczyną i nie zasmucaj mnie, a ja będę dla ciebie dobry. Charlie Prince dotrzymuje słowa!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = " Wierzę ci, kochana. Myślę, że będziesz tu bezpieczniejsza niż związana w kajdanach w tym ciemnym magazynie, gdzie trzymał cię Tyrax.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Dziękuję, señor "+pchar.name+". Dziękuję, że nie pozwoliłeś swojemu... kompanowi mnie zabić. Jesteś dla mnie taki dobry...";
			link.l1 = "Heh, a ty jesteś zabawny,... A twoja twarz jest całkiem ładna, nawet z piętnem na czole. Mam nadzieję, że reszta też jest na miejscu... No, teraz pokaż swojemu kapitanowi, co potrafisz. Zrelaksujmy się na parę godzin po morskiej kołysance.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Zgoda. To wszystko, mam - dużo pracy do wykonania. A ty się rozgość, poznaj Rodgara i chłopaków. Gdy wrócę, pogadamy jeszcze.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Dziękuję, seniorze "+pchar.name+"  Dziękuję, że nie pozwoliłeś swojemu... kompanie mnie zabić. Jesteś bardzo uprzejmy.";
			link.l1 = "Heh, jesteś zabawnym małym słodziakiem... I ładną buzią mimo znaku. Mam nadzieję, że reszta też jest na swoim miejscu... Teraz pokaż swojemu kapitanowi, co potrafisz.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Bardzo dobrze. To wszystko, mam - dużo pracy do wykonania. A ty się osiedl, poznaj Rodgara i chłopaków. Kiedy wrócę, pogadamy jeszcze.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Senor "+pchar.name+" jesteś taki słodki... Jesteś prawdziwym dżentelmenem. Musiałeś przybyć z Europy niedawno.";
			link.l1 = "Pochlebiaj mi, ty mały kłamczuszku, kupuję to. Heh, jesteś dobra, Mirabelle! Tyrax ma dobry gust, he-he...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "Nie jestem. Jesteś dżentelmenem. Ale udajesz grubianina z jakiegoś powodu. Mhmm... Bardzo mi się to podobało. Będę czekać na nasze kolejne spotkanie...";
			link.l1 = "Ach tak, dżentelmen... dżentelmen fortuny, ha-ha! Bardzo dobrze, kochanieńka, osiedl się tu na razie.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Żegnaj, señor.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", señor "+pchar.name+"! Bardzo się cieszę, że cię widzę. Jak się masz?";
			link.l1 = RandSwear()+" "+RandPhraseSimple("Niech mnie kule biją, niech mnie diabli!","Och, lepiej żyć i umrzeć, pod odważną czarną flagą, którą wznoszę!")+" Charlie Prince ma się dobrze, skarbie.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Kochanie, co powiesz na to, by uszczęśliwić kapitana?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = " Wszystko dla ciebie, señor!";
			link.l1 = RandPhraseSimple("Przygotować haki abordażowe!","Na abordaż!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Señor, jesteś czarodziejem! Mam nadzieję, że tobie także się spodobało? Starałem się jak mogłem.";
			link.l1 = "Spisałaś się świetnie, kochanie.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "To nieprawda, nieprawda! Senor "+pchar.name+" jest dobry i życzliwy! On tylko udaje złego pirata! Jesteś, señor "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", señor "+pchar.name+" ! Bardzo się cieszę, że cię widzę. Jak się masz? Dlaczego jesteś taki smutny?";
			link.l1 = "Cześć, Mirabelle. Czemu myślisz, że jestem smutny?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Cóż, widzę to. Nie jesteś sobą. Chcesz, żebym cię rozweselił? No dalej! Zebrałem trochę naprawdę słodkich owoców z dżungli, a ryba, którą Rodgar i jego chłopcy złowili wczoraj, jest upieczona i nadal ciepła.";
			link.l1 = "Zaczekaj. Chcę z tobą porozmawiać.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Oczywiście, señor, cokolwiek powiesz. Zamieniam się w słuch.";
			link.l1 = "Powiedz mi, jak trafiłeś w ręce Tira i dlaczego masz na czole znak złodzieja. Nie bój się, nigdy cię nie skrzywdzę. Chcę tylko usłyszeć twoją historię.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ach, señor! Moja historia jest krótka i nudna. Urodziłem się w Puerto Rico, mój ojciec był białym dżentelmenem, a matka - Indianką. Nigdy nie widziałem mojego ojca. Kiedy byłem dzieckiem, byłem służącym, a kiedy dorosłem, popełniłem głupstwo, kradnąc biżuterię mojego pana. Nigdy nie miałem swojej własnej i tak bardzo chciałem spróbować ją nosić przez jeden dzień. Oczywiście, wszystko się wydało\nBył proces, zostałem wychłostany, napiętnowany i osadzony w więzieniu w San Juan. Nie zostałem tam długo: jeden z oficerów dogadał się z naczelnikiem i sprzedano mnie do burdelu w Philipsburg za garść złotych dublonów\nSpędziłem tam około roku. Pewnego niefortunnego dnia odwiedzili nas Tyrex i jego kiepski przyjaciel w okularach.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Tak-tak, nazywał się señor Pasquale Lavoisier. Nie mam pojęcia, co we mnie widzieli, ale krótko po ich wizycie Tyrex wykupił mnie od Madame Johanny i zamknął w domu pełnym skrzyń i towarów. To był najgorszy okres w moim życiu, nawet gorszy niż dni spędzone w więzieniu w San Juan. Tyrex odwiedzał mnie codziennie, chyba że był na morzu, wtedy mogłam oddychać swobodnie, ale za każdym razem, gdy przychodził señor Lavoisier, ja... ja.... To było najgorsze ze wszystkiego. Señor "+pchar.name+", por favor, czy mogę o tym nie mówić?\nNie wiem, jak długo tam byłem. A potem przyszedłeś i zabrałeś mnie z tego okropnego domu. Miałem wielkie szczęście, że byłeś tak uprzejmy.";
			link.l1 = "Rodzaj? Mirabelle, ale zrobiłem z tobą dokładnie to samo: zabrałem cię na wyspę i zamknąłem w domu.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "Nie, señor, to nieprawda. Czy jestem tutaj zamknięty? Codziennie spaceruję po wyspie. To cudowne i spokojne miejsce. Czy muszę dużo pracować w domu? Wcale nie, i tak się do tego przyzwyczajam. A ty nie jesteś jak Tyrex, nie jak jego przyjaciel kupiec. Zawsze się cieszę, gdy cię widzę, jesteś taki młody i przystojny. I dżentelmen też...";
			link.l1 = "Mirabelle, chcesz, abym zabrał cię do jakiegoś miasta? Dam ci wystarczająco dużo pieniędzy. Dokąd? Wybierz dowolną kolonię.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Señor, chcesz mnie odprawić? Proszę nie, te lo ruego!";
			link.l1 = "Cóż... Myślałem, że chcesz wrócić do normalnego życia...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ach, señor "+pchar.name+", a co mi z tego? Jak mam wyjść za mąż będąc naznaczoną półkrwi? Znowu zostanę sprzedana do burdelu. Proszę, nie odsyłaj mnie. Lubię to miejsce, nigdzie indziej nie czułam się tak spokojnie i bezpiecznie jak tutaj. Rodgar i jego chłopcy to dobrzy ludzie, jesteśmy przyjaciółmi i nigdy mnie nie skrzywdzili, każdy z nich zaryzykowałby dla mnie życie. Lubię spędzać z nimi czas, to zabawa! Czasami rozpalamy ognisko na plaży i tańczę sambę. Proszę, señor, zrobię wszystko dla ciebie, pozwól mi tylko zostać!";
			link.l1 = "Dobrze, Mirabelle, zostań tutaj, skoro tak bardzo lubisz to miejsce. Wiedz tylko, że nie jesteś tu więźniem, zawsze możesz poprosić mnie, bym cię stąd zabrał.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Mój drogi, dobry señorze, dziękuję! Dziękuję! Dziękuję! Nigdy nie poproszę cię o coś podobnego - chcę zostać więźniem tej wyspy... i twoim więźniem, hi-hi... Jesteś taki miły, ale dzisiaj smutny! Nie śpiewasz i nie przeklinasz jak zwykle.";
			link.l1 = "Mogę śpiewać, ale bez przeklinania, Mirabelle. I... przepraszam, jeśli kiedykolwiek byłem dla ciebie niegrzeczny.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Czy będziesz surowy i wymagający jak angielski lord?.. Ach... señor, chcesz, żebym dziś wieczorem tańczyła i śpiewała? Tylko dla ciebie. Chodź ze mną! Nie ma lepszego lekarstwa na smutek niż miłość. Tak bardzo za tobą tęskniłam.";
			link.l1 = "Hah! Dobra uwaga, moja droga dziewczyno... Chodźmy.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ach, señor "+pchar.name+", byłeś dziś taki delikatny, mhm... Czy jesteś zadowolony ze mnie, mój drogi kapitanie?";
			link.l1 = "Wszystko było rozkoszne, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", señor "+pchar.name+"! Tak się cieszę, że cię widzę! Jak się masz?";
			link.l1 = ""+LinkRandPhrase("Cieszę się, że cię widzę, moja dziewczyno.","Witaj, Mirabelle. Zawsze jesteś taka sama - radosna i piękna, co za przyjemny widok.","Witaj, piękna. Wyglądasz olśniewająco!")+"Czuję się całkiem dobrze. Mam nadzieję, że u Ciebie też wszystko w porządku.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, już zaczynam tęsknić za tobą i twoim łasicowatym. Czy pocałujesz swojego morskiego wilka?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ach, mój słodki kapitanie, też tęskniłem za tobą! Chodź, jestem na krawędzi!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Señor Kapitan! Kapitan "+pchar.name+"! Jestem tak szczęśliwy! Uratujesz nas!";
			link.l1 = "Cieszę się, że cię widzę, Mirabelle. Więc, jakie są straty?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Kapitanie, Kapitanie, dziękuję! Jesteś najlepszy, najwspanialszy! Nie tylko uratowałeś mnie przed potworami, ale także dałeś mi nowe życie! Nam wszystkim!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Senor Kapitan!";
			link.l1 = "Witaj i tobie, piękności. Nie nudzisz się, prawda?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ach, Kapitanie! Odkąd uratowałeś mnie z tego strasznego domu, moje życie nabrało barw i radości.";
			link.l1 = "Czy jesteś szczęśliwy?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Oczywiście! I chciałbym podzielić się tym szczęściem z tobą... Będę czekać na ciebie w twoim pokoju, na górze.";
			link.l1 = "Co za kobieta...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Señor Kapitanie!";
			link.l1 = "Witaj również, piękności. Nie nudzisz się, prawda?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ah, kapitanie! Odkąd uratowałeś mnie z tego okropnego domu, moje życie nabrało barw i radości.";
			link.l1 = "Czy jesteś szczęśliwy?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Zdecydowanie! Tylko że...";
			link.l1 = "Widzę, że chcesz mnie o coś zapytać?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Tak, Kapitanie! Chciałbym... podzielić się moim szczęściem z pewnym człowiekiem...";
			link.l1 = "Czy będzie miał coś przeciwko?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "Nie, nie, Kapitanie. Byłoby nam razem dobrze, wiem to na pewno. Tylko... czy pozwolisz na to?";
			link.l1 = "Ty bardziej niż ktokolwiek inny zasługujesz na to. Ale nie będę udzielać wam ślubu, nawet nie pytaj!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha! Mój panie! Dziękuję, Senor Kapitanie. Nie wiem, co o tobie mówią w wielkim świecie, ale zawsze widziałem w tobie najżyczliwszą i najjaśniejszą osobę.";
			link.l1 = "Powodzenia, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Cholerne ladrony! Nieważne, nasz kurier już jest w drodze do Porto Bello. Wkrótce nasza eskadra przybędzie i...";
			link.l1 = TimeGreeting()+" , Wasza Wysokość. Przyjemność zobaczyć Was w tak pięknej rezydencji. Mam nadzieję, że utrzymacie ją po naszym odejściu. Na Waszym miejscu nie liczyłbym na eskadrę, poza tym nie zostajemy tu dłużej niż trzy dni. Założę się, że rozumiecie, iż szlachetni donowie z Porto Bello nie przybędą tutaj, by wam pomóc, tak szybko. Więc przejdźmy od razu do interesów, dobrze?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Już o interesach mówimy? Spójrz przez okno! Spójrz, co twoi rzezimieszkowie robią na ulicach i w domach!";
			link.l1 = "O, Wasza Wysokość, to nic w porównaniu z tym, co zrobią, jeśli nie będziecie wystarczająco współpracować. Mam nadzieję, że rozumiecie, kim są ci ludzie...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "Wiem, do czego zdolny jest nikczemny pirat Charlie Prince! Wiem, kto jest jego szefem! Z czasem wypalimy waszą bandycką norę na Hispanioli! Ile?";
			link.l1 = "Nie trać słów, mój drogi gubernatorze. Lepiej dostarcz mi 250 000 pesos.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "Co?! Twoja bezczelność nie zna granic! To jest rabunek!";
			link.l1 = "Oczywiście, że to rabunek. Czymże innym mogłoby to być? Zbierzcie swoich elit, kupców i handlarzy, zgromadźcie złoto w wielkiej skrzyni, bo inaczej... zrobię wam i waszym ludziom znacznie gorzej.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Cholerny pirat! Bastardo! Heretyk! Idź do diabła!";
			link.l1 = "Z powodu twojego parszywego języka zwiększam okup do 300 000.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "PŁOŃ W PIEKLE, SUKINSONIE!!!";
			link.l1 = "350 000. Chcesz kontynuować?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "Nie ma takich pieniędzy w mieście!";
			link.l1 = "Kłamiesz. To po prostu niemożliwe. Jesteśmy w stanie zebrać tu przynajmniej milion, ale obawiam się, że nie mamy na to wystarczająco czasu. Dlatego będę miły i hojny. Znasz sumę. Idź i zdobądź ją.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Mówię ci jeszcze raz, Charlie Prince: w Kartagenie nie ma takich pieniędzy!";
			link.l1 = "Och... jak możesz być tak nudny. Szabla! Przeszukaj okolicę i przyprowadź tutaj każdego, kogo znajdziesz. Szukaj dobrze! A my tutaj poczekamy, wasza łaskawość...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Ej, señor 'Uparty'! Czyżbyś zmienił zdanie co do zbierania pieniędzy w dobrym mieście Cartagena?... Co się stało, dlaczego nagle jesteś taki poważny?! Wszystko w porządku? Przynieść ci wody?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Z tego co rozumiem, te dwie damy to twoja żona i córka, mam rację? Trzecia dziewczyna wygląda na służącą, wydaje się, że masz ją gdzieś, więc jej nie zrobimy krzywdy, ale te dwie piękności mogą przyciągnąć uwagę mojego towarzysza, señor Cutlass. Wydaje się, że mu się podobają, señor. I co teraz? Zamierzasz zapłacić okup?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "Ja... Będę potrzebował czasu.";
			link.l1 = "Aha! Teraz gadasz! Więc kto tu jest bastardo? Nie obchodziło cię, że moi ludzie terroryzują twoich obywateli, ale te dwie kobiety to już zupełnie inna sprawa, prawda? Odważyłeś się ze mną pieprzyć, draniu? Pokażę ci, co znaczy zadrzeć z Charliem Princem!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Idź i zbierz, kurwa, okup. 350 000 i ani peso mniej. Masz jeden dzień. My zostaniemy tutaj, by napić się wina i pobawić z tymi słodkimi kobietami... Bądź szybki, amigo, bo ja i mój przyjaciel tutaj, señor Cutlass, możemy się zakochać w waszych pięknościach, a wtedy będziesz musiał wykupić także i je. Naprzód! Marsz!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Weź swoje krwawe pieniądze, Charlie Prince!";
			link.l1 = "Czy zebrałeś okup? Wspaniale! Ale spóźniłeś się o godzinę, mój drogi gubernatorze. Ta dodatkowa godzina dała mi i Cutlassowi zrozumienie, że nasze życie będzie zbyt nudne bez tych piękności, które były tak miłe i rozmowne z nami...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Ty... ty!";
			link.l1 = "Ach, jesteś zbyt nerwowy przez swoją robotę, mój przyjacielu. Żartowałem... Szabla! Chodźmy, wychodzimy!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "O, więc to jest Charlie Książę, słynny pirat, postrach hiszpańskiego południowego wybrzeża!";
			link.l1 = RandSwear()+"Heh, nie miałem pojęcia, że jestem tak popularny na Tortudze. Jak się nazywasz, słodka dziewczyno?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "Na imię mi Camilla.";
			link.l1 = "Camilla... Kiedyś znałem dziewczynę o tym samym imieniu we Francji. To było tak dawno temu!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = " ";
			link.l1 = "(wymiotując) ... kurwa... Przepraszam księżniczko, ale Książę jest dzisiaj trochę pijany. Więc... hmm.. dlaczego do mnie przyszłaś?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Z różnych powodów. A może bez żadnego powodu.";
			link.l1 = "Boże, to zbyt skomplikowane. Wydajesz się być zagadką, dziewczyno.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Każda dziewczyna musi mieć tajemnicę.";
			link.l1 = "Wygląda na to, że chcesz, abym rozwiązał tę zagadkę. Nie? Jestem mistrzem rozwiązywania dziewczęcych tajemnic, przysięgam! Może pójdziemy do tawerny i wypijemy trochę wina? Zafunduję ci najlepszy poczęstunek!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... Lubię twardzieli. Ale nie będę piła wina na dole w towarzystwie pijanych łajdaków. Załatw nam pokój, tam sobie wypijemy i pogadamy.";
			link.l1 = RandSwear()+"Jesteś gorący! Chodź za mną!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Chodźże... Nalej, nie każ damie czekać!";
			link.l1 = "Oczywiście, moja słodka!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Jak pomyślę, że jestem tu sama z Charliem Księciem, pijąc wyborne wino...";
			link.l1 = " Będziesz się dobrze bawić podczas tej podróży ze mną, o obiecuję! Charlie Prince jest łagodny i uprzejmy dla dam, które się mu poddają. Czy się poddasz, księżniczko?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Hee-hee... Oczywiście, kochanie! Twoje obietnice brzmią tak kusząco, wiesz...";
			link.l1 = "Cóż, nie traćmy zatem czasu, piękności?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "O! Uwielbiam! Prawdziwi mężczyźni!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Czy podobało ci się, moja księżniczko?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Na pewno! Mam nadzieję, że też mnie polubiłeś.";
			link.l1 = "Ha! Nawet mój łeb teraz jest krystalicznie czysty!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Książę, mam do ciebie prośbę. Pomożesz mi?";
			link.l1 = "Zdobyłbym dla ciebie gwiazdę z nieba, ha-ha! Śmiało.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "Muszę dotrzeć do La Vega, aby zobaczyć Tyreksa. Boję się go, ale robicie interesy razem. Proszę, zaprowadź mnie do niego.";
			link.l1 = "Spójrz na to! I dlaczego taka słodka, krucha dziewczyna chciałaby zobaczyć Strażnika Kodeksu?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Ta słodka, delikatna dziewczyna chciałaby zarobić trochę grosza. Mój zmarły ojciec i bracia nie zostawili mi wiele pieniędzy. Tyrex może to naprawić.";
			link.l1 = "O, naprawdę? I jak? Chcesz trop na hiszpańską galeonę? Ha-ha!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Plądrowanie karawan i miast to robota dla twardzieli, tak jak ty, kochanie. Mam inny interes dla Markusa. On kupuje i sprzedaje informacje, prawda? Mam coś... Nie ma mowy, żebym mógł to sam wykorzystać, ale on mógłby. Będę wystarczająco zadowolony, jeśli dostanę z tego mały procent.";
			link.l1 = "Interesujące! Powiedz mi więcej.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm... Nie wiem...";
			link.l1 = "Oh, daj spokój. Uważaj mnie za prawą rękę Tyrexa, sporo już dla niego zrobiłem, uwierz mi. Jeśli twoja informacja jest tego warta - sam ją kupię.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Dobrze. Opowiem ci więcej, ale szczegóły dopiero, jak dostanę pieniądze. Umowa stoi, skarbie?";
			link.l1 = "Jasne, ślicznotko. Charlie Prince nie pierdoli swoich wspólników... rozumiesz, co mam na myśli, ha-ha-ha! Śmiało, zamieniam się w słuch.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... Mój tata był kapitanem na kupieckiej szkunerze. Pewnego dnia dowiedział się o starym hiszpańskim osiedlu górniczym leżącym głęboko w dżunglach Main. Dwadzieścia lat temu zostało zniszczone przez trzęsienie ziemi. Górnicy je opuścili, a tajne przejścia zostały zapomniane. Z wyjątkiem jednego. Mój ojciec je znalazł\nZabrał tam moich braci i przewodnika, a oni znaleźli miejsce wypełnione złotem wydobytym i wytopionym lata temu. Dużo złota. Co najmniej milion pesos. Ojciec wrócił na statek, aby przyprowadzić ludzi do transportu złota, ale był zszokowany, gdy dowiedział się, że statek zniknął. Wygląda na to, że jego pierwszy oficer rozpoczął bunt i zostawili go oraz moich braci na opuszczonym brzegu\nZbudowali szalupę i popłynęli wzdłuż brzegu, desperacko szukając zamieszkanego miejsca, ale... (szlocha) uderzyła ich burza i moi (szlocha) bracia zginęli. Ojciec przeżył, ale nie żył długo po powrocie do domu - śmierć moich braci powoli go zabijała dzień po dniu. Przed śmiercią sporządził mapę i dał mi ją\nPowiedział mi, że kiedy wyjdę za mąż, mój mąż powinien tam pojechać, zdobyć złoto i będziemy żyć jak królowie. Z pewnością, ale nie pozwolę mojemu mężczyźnie wejść do tych przeklętych dżungli. Nigdy więcej! Milion pesos, mówił mój ojciec, ale to nie moja liga. Taka nagroda, tylko najlepsi i najtwardsi mężczyźni mogą ją zdobyć - mężczyźni jak Marcus Tyrex. Dlatego zamierzam się z nim spotkać.";
			link.l1 = "Ile chcesz za tę mapę?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Dwieście złotych dublonów. To nic w porównaniu z nagrodą. Tyrex się na to zgodzi, jestem pewien. Jest bogaty jak Krassus.";
			link.l1 = "Heh! A co jeśli to wszystko jest podstęp?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Czy wyglądam na samobójcę? Próbować przechytrzyć Tyrexa? Kochanie, lepiej żyć w biedzie niż wcale. Więc zabierzesz mnie tam? Proszę...";
			link.l1 = "Gdzie jest mapa? Czy mi ją pokażesz?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "Mój ksiądz trzyma to w bezpiecznym miejscu. Pokażę ci to za 200 doublonów.";
			link.l1 = "Bardzo dobrze! Kupuję to. Nieznajomi w tawernach czasem żądają dużo więcej za śmieci.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Czyżby? To prawda, kochanie? Tak się cieszę, że nie jadę do La Vega! Szczerze mówiąc, boję się Markusa. Ciebie też się boję, swoją drogą... ale trochę mniej.";
			link.l1 = "Taka słodka dziewczynka nie musi się mnie bać. Gdzie mam przynieść pieniądze?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Zawrzyjmy umowę: znajdź mnie w naszym kościele każdego dnia od dziesiątej rano do pierwszej po południu. Będę czuł się o wiele bezpieczniej pod ochroną tego świętego miejsca. Tam zawrzemy naszą umowę.";
			link.l1 = "Czy wciąż się mnie boisz? Ha-ha! Nie bój się Camillo, nie zdradzę cię. Charlie Prince nie zrobiłby czegoś tak niskiego za dwieście dublonów, poza tym chcę ci pomóc.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Cudownie. Bardzo dobrze, przystojniaku, będę na ciebie czekać... Dziękuję za wspaniały czas, który spędziliśmy razem dziś wieczorem! Jestem taka szczęśliwa, że się spotkaliśmy!";
			link.l1 = "Do zobaczenia wkrótce, piękna.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "A więc? Przyniosłeś pieniądze, kochanie?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Tak. Mam swoje złoto, a teraz daj mi mapę.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Jestem tuż po tym.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Dzięki, kochanie... Proszę, weź to. Przysięgam na pamięć mojego ojca - ta mapa nie jest fałszywa, zaprowadzi cię prosto tam, gdzie powinieneś iść...";
			link.l1 = "Dobrze, skarbie. Jakbyśmy uczcili naszą umowę tak samo jak ostatnim razem?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "Chciałbym, książę, ale przygotowuję się do spowiedzi przed moim księdzem, więc muszę unikać wszelkich pokus teraz. Zróbmy to następnym razem.";
			link.l1 = "Ach, droczysz się ze mną, dziewczyno. Dobrze! Nie ma czasu do stracenia: zaraz podnosimy żagle. Przysięgam, podwoję twój udział, jeśli mapa twego ojca rzeczywiście doprowadzi mnie do złota.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Jesteś tak hojny, kochanie. Bon voyage!";
			link.l1 = "Jo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Twoje bękarty zabiły mego ojca i braci. Twój atak na Kartagenę przyniósł żałobę każdej rodzinie tam. Mam nadzieję, że teraz się boisz, boisz się tak samo, jak my, obywatele Kartageny, kiedy twoi brutale bawili się na ulicach i w domach. Spłoniesz w piekle, Charlie Prince.";
			link.l1 = " ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "Tak niewiele rzeczy na tym świecie cieszy mnie tak bardzo, jak oglądanie, jak szczury w pudełku rozszarpują się nawzajem!\nPrzeżywa tylko najsilniejszy i najbardziej obrzydliwy szczur. Potem wystarczy go tylko zgnieść...";
			link.l1 = "Argh! Kimże jesteś?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "Jestem don Enrico. Angielska hołota nazywa mnie Lisem, Holendrzy mówią Vos, Francuzi Renaud. Lecz ja wolę moje hiszpańskie domowe przezwisko - Zorro. Karzę zło, które dręczy i terroryzuje pospólstwo, najmniej chronioną część ludu\nDzisiejszy proces osądzi czterech piratów Marcusa Tyrexa: Śmiałego Jeffry'ego, Pelly'ego Szabla, Luke'a Skrzata i Charlie'go Księcia - ci bandyci są odpowiedzialni za masakrę w Meridzie i Cartagenie. Ostatni drań, zwany Przystojnym Jeanem, nie pojawił się tutaj, musi być najmądrzejszy z waszej bandy.";
			link.l1 = "Co?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Ty jesteś szumowiną, Charlie Prince, ale nie jesteś idiotą. Już to rozgryzłem, myślę. To pułapka na ciebie, ustawiona przeze mnie przy pomocy fałszywych map, dokumentów, słów i obietnic złota i srebra. Zwabiłem was wszystkich do tych lochów, gdzie zniszczyliście się nawzajem pod wpływem waszych obrzydliwych cech: zazdrości, chciwości, nikczemności i bezwzględności. To była prawdziwa i sprawiedliwa zemsta!";
			link.l1 = "Camilla... Powinienem był wiedzieć, że z tą dziewczyną coś jest nie tak!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Dziewczyna imieniem Camilla wiodła spokojne życie w Kartagenie ze swoim ojcem i braćmi, miała wkrótce wyjść za mąż, gdy ty i twoje diabły zaatakowaliście miasto. Twoi piraci zabili wszystkich jej bliskich, więc przysięgła zrobić wszystko, by ich pomścić. To była dla niej ciężka rola do odegrania. Musiała nawet spać z bękartem odpowiedzialnym za śmierć jej rodziny. Boję się wyobrazić, co czuła podczas tego aktu\nBiedna dziewczyna spędziła dni w kościele, modląc się o przebaczenie. Podarowała krwawe dukaty, które jej dałeś, ofiarom, które najbardziej ucierpiały w wyniku twojego ataku. Teraz jest w klasztorze, biedna dusza. Zrujnowałeś jej życie, ścierwo! Pomyśl o tym! Pomyśl, ile Camilli, Isabelek, Rosit zgwałciłeś i uczyniłeś wdowami! Ilu Juanów, Carlosów, Pedro, wy bękarty, zabiliście i torturowaliście!\nPamiętaj Meridę! Pamiętaj, jak obiecałeś burmistrzowi miasta, że nie podpalicie miasta, a potem spaliłeś całe miejsce na popiół!";
			link.l1 = "Nie chciałem tego zrobić! Gdy opuszczałem rezydencję, ogień był już wszędzie. Nie wydałem takiego rozkazu...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Jesteś odpowiedzialny za czyny swoich piratów. Martwi wiszą ci na szyi i wkrótce pociągną cię do piekła!";
			link.l1 = "Chodź więc! Co? Walcz ze mną! Tego chcesz, prawda?! No to zróbmy to!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "Nie, Charlie Prince. Nie sięgaj po broń, to bezcelowe... Mógłbym cię łatwo zabić, jednak szybka śmierć to za mało dla takiego drania jak ty. Zostaniesz w tym lochu na zawsze. Drzwi, przez które tu wszedłeś, są zablokowane kamieniem z zewnątrz, drzwi za mną również będą zablokowane, a poza tym chronią je solidne kraty. To wszystko, nie ma wyjścia poza tymi dwoma drzwiami\nCo do... Zamknąłem wszystkie drzwi!";
				link.l1 = "Co się dzieje...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "Nie, Charlie Prince. Nie chwytaj za broń, to bezcelowe... Mógłbym cię zabić łatwo, jednak szybka śmierć to za mało dla takiego drania jak ty. Zostaniesz w tej loch na zawsze. Drzwi, którymi tu wszedłeś, są zablokowane kamieniem z zewnątrz, drzwi za mną też będą zablokowane, poza tym chronią je solidne kraty. To wszystko, nie ma wyjścia poza tymi dwoma drzwiami\nPoniżej jest woda, więc będziesz miał dość czasu, by pomyśleć o swoich czynach. Samotny tutaj, w ciemności, być może pokutujesz za to, co zrobiłeś, zanim umrzesz z głodu lub oszalejesz\nJeszcze jedna rzecz - skarb poniżej to podróbka. Złote sztabki to nic innego jak kolorowany ołów. Doubloony są prawdziwe, ale jest ich tylko tyle, by pokryć kamienie w skrzyniach. Godny koniec dla piratów, co? Zabiliście się nawzajem dla fałszywego skarbu, Prince. Żegnaj teraz. Módl się za swoją grzeszną duszę, Charlie Prince, jeśli jeszcze pamiętasz jak...";
		// belamour legendary edition -->
				link.l1 = " Właśnie zabiłem całą awangardę Marcusa Tyrexa! Myślisz, że te zardzewiałe kraty mnie powstrzymają?! Roztrzaskam je twoją własną głową!";
				link.l1.go = "enrico_5a";
				link.l2 = "Może na to zasłużyłem. Ale się nie poddam, słyszysz?! Znajdę sposób, zawsze znajduję!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "Masz rację, drzwi są solidne, nawet jeśli stare. Dzięki, że nie opuściłeś bramy - to by mnie opóźniło. Ale nie na długo.";
			link.l1 = "Hercule Tonzag, Łysy Gaston! Powinienem był się domyślić, że ktoś taki jak ty stanie po stronie Księcia i jego całej zgrai. Szczęście dla mnie, że spotykam cię tu również.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Szczęśliwy, powiadasz? Cóż, jeśli spieszno ci umierać... Chociaż myślałem, że nie, skoro zostawiłeś go, by zginął z głodu, zamiast stawić mu czoła.";
			link.l1 = "Oskarżasz mnie o tchórzostwo? Jakże głupio z twojej strony. Jak powiedziałem Księciu, śmierć to zbyt łatwa kara dla niego. On nie ma ze mną szans.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "A nie dasz mi rady, Donie.";
			link.l1 = " Dziesięć lat temu? Z pewnością. Teraz? Trudno. Co więcej...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "Ponadto co? Co to za dramatyczna pauza? Choć, biorąc pod uwagę twoją karnawałową maskę... Trochę za wcześnie, by mnie skreślić, prawda?";
			link.l1 = "Wyważyłeś drzwi, ale sama siła nie wystarczy przeciwko mnie. Jak z twoimi refleksami? Twoim wzrokiem? Tylko jedno oko. Ja mam oba.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Cóż, na razie, w każdym razie. Heh-heh.";
			link.l1 = "Dla Porto Bello zasługujesz na gorsze męki niż książę!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "O, więc słyszałeś, co zrobiłem? Chyba będą o tym plotkować wśród was jeszcze przez jakiś czas. Więc wiesz, przez co przeszedłem.";
			link.l1 = "Jesteś stary, Tonzag, a tym razem twoja arogancja będzie twoim upadkiem. I tak, nie tylko o tym słyszałem - Cartagena, Merida to twoje dzieło. Tak samo jak Porto Bello.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "Uznałbym to za pochlebstwo, ale nie, to nie moje dzieło. Choć z daleka może wyglądać podobnie. Zbyt amatorskie. Z drugiej strony, nawet w Porto Bello, były... incydenty.";
			link.l1 = "Incydenty?! Tego dnia zginęła jedna osoba... A biorąc pod uwagę, że to ty rozpocząłeś tę masakrę, wciąż cię za to winię, nawet jeśli nie zabiłeś wszystkich sam. Obwiniam cię za każdy 'incydent'.";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "Jedna osoba, mówisz... Wielu zginęło tego dnia. Bądź bardziej precyzyjny.";
			link.l1 = "Naprawdę, nie masz serca, jeśli możesz to powiedzieć! Ale odpowiem: ten, którego nie powinieneś był zabić. Mój ojciec, Don de la Vega. Gdyby żył, nie obrałbym tej drogi, a wy wszyscy bylibyście wciąż żywi.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Zamknij gębę, szczeniaku. Moja droga żona... też tam zginęła.";
			link.l1 = "Oczekujesz kondolencji? Nie dostaniesz ich. To kara od Pana dla ciebie. Wygląda na to, że masz serce - malutkie i czarne. I znajdę je moim ostrzem.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Och, te dramaty o moim sercu. Mylisz się, jeśli sądzisz, że widziałeś gorsze rzeczy niż ja.";
			link.l1 = "Czy myślisz, że jestem tylko rozpieszczonym bogaczem marnującym pieniądze? Wiedz to: nie wydałem ani dubloona na hazard czy kobiety! Wszystko wrzuciłem w walkę przeciwko takim jak ty i poświęciłem temu swoje życie!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "A po co? Nie wydaje się to zbyt udane. Szlaki handlowe wciąż roją się od piratów. Jesteś sam w swojej krucjacie. A oni to cała legion.";
			link.l1 = "Ktoś musi. Przynajmniej ktoś. A może, zabijając tylko jednego kapitana piratów, uratuję kilka żyć.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "Nierozważny. Idealistyczny. I... w pewnym sensie, szlachetny, rzekłbym, gdyby nie twoje metody. Niegodne, jak twoi wrogowie. W końcu jesteś... nie lepszy.";
			link.l1 = "Nie pouczaj mnie! Honor jest dla tych, którzy przestrzegają jego praw. Rozumiem cię. Myślę jak ty. I karzę.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "Masz rację. Nauczanie ciebie nie ma sensu. Więc nie rozejdziemy się pokojowo. Ale mam cię gdzieś, Don Enrico. Nie jesteś nawet wart mojego czasu.";
			link.l1 = "Cóż masz na myśli...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "Czy wszystko w porządku, kapitanie? Ostrzegałem cię, byś był ostrożny. Powinienem był posłuchać swojego instynktu.";
			link.l1 = "Tak, wszystko w porządku. Dzięki, Hercule. Tylko trochę...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...zszokowany? Nie bój się tego przyznać - to normalne dla kogoś w twoim wieku i w takiej sytuacji. Poza tym, ten Don to dobry manipulator.";
			link.l1 = "Uh-huh. Choć, wydawał się bać ciebie. To mnie zaskoczyło. Ale też przywróciło do rozsądku. Przy okazji, czy on wciąż żyje? Wygląda na to. Nie powinieneś stać do niego tyłem.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Żywy, ale oszołomiony. Dochodzi do siebie. Powinienem celować w głowę, a nie w tors - okazuje się, że nasz szlachetny hidalgo nosi pod płaszczem lekką, ale solidną kirysę. Heh, nawet Fleetwood ograniczył się do prostego pourpoint. W przeciwnym razie, już byłaby tutaj kałuża krwi.";
			link.l1 = "I jak się tu znalazłeś? W tym samym miejscu co on?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "Nie ma teraz na to czasu. Wkrótce znów stanie na nogi. Na razie podniesiemy tę bramę.";
			link.l1 = "Co... co?? Pewnie, możesz być Herkulesem, ale...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Mężczyźni z mojej młodości byli hartowani na twardo. Te zawiasy mają krótkie bolce. Chodź, pomóż mi, Kapitanie - mogę być Herkulesem, ale lata lecą.";
			link.l1 = "Dobrze, na trzy! I podnośmy!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Czy myślisz, że zrujnowałeś wszystkie moje plany i wygrałeś? To było nieoczekiwane, oczywiście, ale wciąż wiele przewidziałem!";
			link.l1 = "Podobnie jak ta lekka kirys pod twoimi ubraniami. Czemu to, a nie pełna na wierzchu? Po prostu, aby się popisać swoim płaszczem?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "Nie jestem żadną panną, Książę. Moje powody są czysto praktyczne - pełna zbroja zbytnio ogranicza moje ruchy. Każdy ma swoje podejście.";
			link.l1 = "Jednak oto jestem, Francuz, już przyzwyczajony do noszenia kirysów, w przeciwieństwie do Hiszpana. Ironia. Więc, co teraz? Nie udało ci się nas złapać. Przygotowałeś się na wszystko... Czy pojedynek wchodził w możliwości? A może ostrze - a nawet kirys - do wszystkiego poza prawdziwymi walkami?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Czy próbujesz również nazwać mnie tchórzem? Jak już mówiłem, zasługujesz na długie cierpienie, a nie śmierć w pojedynku. Jaki to ma sens, jeśli twoje dusze nie będą miały czasu, aby wytrwać i pojąć wszystkie swoje grzechy tu, na Ziemi?";
			link.l1 = "Droga do piekła jest wybrukowana dobrymi intencjami, jak mówią... I czy dręczenie swoich ofiar nie splamiłoby twojej własnej duszy?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Przenigdy. Nigdy. Bowiem pozostaję wierny sobie i swoim zasadom.";
			link.l1 = "Aha, nie jak my. Powiedziałeś tak wiele o tym, jak jesteśmy nikczemną hołotą bez krzty honoru, więc... czemu nie sprostać twoim oczekiwaniom? Sami się tobą zajmiemy. Razem.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "Mam dla ciebie propozycję, Don Enrico. Wyzwanie do pojedynku, tutaj i teraz. Jak szlachcic do szlachcica.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Hm-m. W przeciwnym razie nie miałbyś szans. Tonzag będzie oczywiście podstępny... Więc najpierw zajmę się tobą.";
			link.l1 = "Jakby on ci na to pozwolił.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "Ty? Szlachetny? Może jesteś „księciem”, ale wątpię, że masz w sobie choć kroplę szlachetnej krwi.";
			link.l1 = "Ujawniłeś mi swoje prawdziwe imię. Ujawnię ci moje. Nazywam się Charles de Maure. I obrażaliśmy nawzajem swoje honory wystarczająco, by każdy z nas miał prawo żądać satysfakcji. Broń się, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "Ale nie żałuj później swojej decyzji.";
			link.l1 = "Żałowałem wielu decyzji w moim życiu, ale to nie będzie jedna z nich. En garde!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "Czy wszystko w porządku, Kapitanie? Nasz szlachetny hidalgo nie tylko nosił kirys - zatruł też swój miecz. Weź to. Zawsze noszę kilka przy sobie, gdy przechadzam się przez dżunglę - nigdy nie wiadomo, kiedy wąż może ugryźć albo czerwonoskóry rzuci zatruty pocisk.";
			link.l1 = "Dzięki, Hercule. Mam się dobrze. Twoje przybycie w samą porę pomogło mi się pozbierać.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "Nie ma sprawy. Chodźmy, wyciągnę cię stąd - wspomniał o zablokowaniu wejścia kamieniami. Znalazłem inne przejście, skrót.";
			link.l1 = "Powiedz mi, Hercule... co dokładnie wydarzyło się w Porto Bello? I kiedy?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "Nie mam dziś nastroju, by o tym rozmawiać. Może kiedyś, przy kielichu wina albo czegoś mocniejszego. Na razie, chodźmy stąd - smarkacz miał rację, starzeję się. Chcę odpocząć na statku.";
			link.l1 = "Wtedy prowadź drogę.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Powiedz mi, bracie - jak stałeś się takim potworem? Kiedy mówiłem ci, żebyś zapoznał się z piratami, nie miałem na myśli palenia miast, zabijania niewinnych cywilów i torturowania kobiet. Nawet wojna może być prowadzona z honorem i godnością\nJesteś hańbą naszej rodziny. Dobrze, że nasz ojciec tego nie widzi: umarłby ze wstydu, wiedząc, że jego syn stał się piratem i bandytą!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Bracie! Bracie!\nCzy mnie słyszysz?\nZa jednymi z dwóch drzwi jest przejście. Drzwi można otworzyć. Klucz jest blisko ciebie!\nZnajdź go na schodach. Na schodach!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, witaj mój dzielny rzezimieszku! Czemu jesteś taki smutny? Morze, złoto, rum i kobiety - czego ci jeszcze brakuje? Pamiętasz nasze pierwsze spotkanie? Powiedziałem ci wtedy - potrzebuję ludzi, którzy nie boją się zapachu prochu ani krwawienia do ostatniej kropli. Przewyższyłeś moje wszelkie nadzieje! Stałeś się prawdziwym piratem, Charlie Prince! Ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Prawdziwy cholerny pirat! Ah-ah-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Kim jesteś? Co tutaj robisz? Odpowiadaj szybko!";
			link.l1 = "Jestem od Fadeya, przybyłem po partię czarnych kości. Powinien cię uprzedzić.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah! Nie przejmuj się skórą, przyjacielu. Rozpoznaliśmy cię, Moskal podał bardzo szczegółowy opis. Poprosił również, by nie obrażać się na cenę. A więc, biorąc pod uwagę zaliczkę, pozostaje ci zapłacić 10 000 srebra. Albo, jeśli zapłacisz w złocie, to tylko 50 dublonów. No, na co się zdecydowałeś? Nie ciągnij kota za ogon!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "Zapłacę 50 dublonów. To bardziej opłacalne.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "Zapłacę 10 000 pesos.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "Przykro mi, ale nie stać mnie teraz na niewolników.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "To świetnie. Daj znak swoim ludziom, by zabrali towar.";
			link.l1 = "Z pewnością.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "To świetnie. Daj sygnał swoim ludziom, by zabrali towar.";
			link.l1 = "Oczywiście.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "No cóż, jak sobie życzysz. Zawsze znajdzie się kupiec na ten towar. Do zobaczenia, przyjacielu.";
			link.l1 = "Żegnaj.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Witaj, Kapitanie. Jesteś Charlie Książę, jeśli się nie mylę? Nie martw się, moje ściany nie mają uszu. Szczerze mówiąc, nie obchodzi mnie, jak się nazywasz. Liczy się to, że zostałeś mi polecony, co oznacza, że możemy robić interesy.";
			link.l1 = "Witam cię również, Gaspardzie 'Złoty Ząb'. Choć szczerze mówiąc, nie obchodzi mnie, jak się nazywasz. Słyszałem, że możesz być zainteresowany zakupem jakichś drobiazgów?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		case "GasparGold_meeting_01":
            dialog.text = "Zgadza się. Nikt nie zaoferuje ci lepszej ceny niż ja. No, może poza lombardzistami, ale oni nie kupują zbyt wiele. Jestem gotów kupić wszystko, co mi zaoferujesz. Nawet nie musisz osobiście przynosić mi kosztowności: mam tylne drzwi prowadzące do ustronnego nabrzeża. Śmiało sprzedaj mi wszystkie drobiazgi, które masz schowane w skrzyniach na swoim statku.";
			link.l1 = "Cóż, to doskonałe! Cieszę się, że możemy się poznać.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "To teraz moja osobista sprawa. Wolałbym, żebyś się w to nie wtrącał. Powiem tylko, że mam wszystko pod kontrolą, więc możesz handlować ze mną bez obaw. Reszta cię nie dotyczy.";
			link.l1 = "No cóż, najważniejsze jest, że bez ryzyka! Jeszcze chciałem o coś zapytać...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "Jak mogę pomóc? Chcesz pozbyć się nadmiaru pereł czy klejnotów? Może złota, srebra, biżuterii? Kupię wszystko.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Powiedz, jak to jest być nabywcą kradzionych towarów? Nie boisz się władz?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "Mam tu coś... Chcę to wymienić na twardą monetę.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Cóż, dokonajmy wymiany. Dublony czy peso?";
			link.l1 = "Przejdźmy na pesos - nie potrzeba dubloonów. Zwykłe pieniądze są powszechnie akceptowane wszędzie.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "Zgadłeś - szczególnie potrzebuję dublonów. Więc będę sprzedawał tylko za nie.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "Nie mam teraz nic na sprzedaż. Chciałem tylko upewnić się, że jesteś gotów kupić cenne przedmioty, gdy je będę miał. Do następnego razu!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Znowu uciekasz się do zastraszania, kapitanie? Słyszałem groźby nawet z zewnątrz.";
			link.l1 = "Nie zostawili mi wyboru. Oferowałem żonie tego Tagofy podarki w zamian za jego pomoc. Nawet nie chciała mnie słuchać. Teraz niech wódz z nimi porozmawia. A jeśli nie zdoła przywołać tych uparciuchów do porządku, własnoręcznie wyrwę mu serce z piersi. A tak przy okazji, kim jest Yahahu?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "Nie powinieneś był psuć relacji z Indianami. My, piraci, mamy tylko miecz i statek jako sprzymierzeńców. Ale skoro taka jest twoja decyzja, niech tak będzie. A Yahahu to zły demon. Nie wiem nic więcej o nim.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "Marnowanie czasu na przekonywanie, Leprechaunie - to nierozsądne. Czy wolisz zrezygnować z bogatego łupu i utrzymać dobre stosunki z Indianami?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "Wolałbym zdobyć oba.";
			link.l1 = "Nie da się stać jedną nogą w dwóch obozach. Nie tym razem. Dość kłótni, wszystko już zostało zrobione. Jutro naczelnik poinformuje nas o decyzji Tagofy, i mam nadzieję, że mnie nie zawiedzie. W przeciwnym razie... będę musiał podjąć skrajne środki. Czego oczywiście chciałbym uniknąć.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Cóż, jak się sprawy mają?  Czy będziemy mieć przewodnika?";
			link.l1 = "Nie, Jean, nie zrobimy tego. Wódz i całe plemię boją się Kapongów jak diabeł boi się kadzidła. Wygląda na to, że będziemy musieli porzucić nasz plan.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax nie będzie zadowolony z takiego obrotu wydarzeń.";
			link.l1 = "Czy myślisz, że jestem niesamowicie szczęśliwy, że wszystko potoczyło się w ten sposób? Tchórzliwi Lokono nie chcą zadzierać z Kapongami. Nie kuszą ich ani perswazje, ani nagrody.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "W takim razie będziemy musieli użyć gróźb. Powiedz im, że spalisz ich cholerną wioskę do cna i będziesz torturować tych, którzy przeżyją, dopóki ktoś nie zgodzi się nas poprowadzić.";
			link.l1 = "Jean, czy ty całkiem straciłeś rozum? Nie zamierzam palić domów niewinnych ludzi. I na pewno ich nie torturować.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince jest wzorem dobroczyńcy. Nigdy nie spodziewałem się takich wybuchów czułości z twojej strony.";
			link.l1 = "To nie jest czułość, Przystojniaku. Cóż, będziemy torturować jakiegoś Indianina do półśmierci. Z zemsty poprowadzi nas prosto w ręce Kapongów i zniknie ścieżkami znanymi tylko jemu. Nie zaryzykuję życia moich ludzi w ten sposób.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "W takim razie, Leprechaun i ja się wynosimy. Oto pięćdziesiąt tysięcy srebra za uwolnienie mnie z plantacji Maracaibo. Oszczędzałem to na nowy statek. I moja rada dla ciebie: trzymaj się z dala od Marcusa przez jakiś czas. Żegnaj, Charlesie Książę.";
			link.l1 = "Żegnaj, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "Wszyscy z okolicy będą teraz tutaj pędzić! Czy jesteś pewien, że wysadzenie tych drzew to był dobry pomysł, Kapitanie?";
			link.l1 = "Cholera! Może lepiej by było, gdyby wszyscy pracowali z siekierami... Ale na to już za późno.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "Prawda. Będziemy musieli radzić sobie z tym, co mamy. Przygotuj się.";
			link.l1 = "Ty też, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "Oni wciąż idą w tę stronę. Więc, czy powinniśmy zająć się także nimi?";
			link.l1 = "A co jeśli ich nie ma końca? Nie jesteśmy tu dla takich kłopotów.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Cóż, wszystko ma swój kres... Ale masz rację. Wycofajmy się. I to szybko.";
			link.l1 = "Pośpieszmy się!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "Tak nieustępliwi, dogonili nas. Jest tu ścieżka, powinniśmy tam wejść? Łatwiej będzie utrzymać linię.";
			link.l1 = "Zaczekaj, Hercule. Słyszysz to? Ktoś już tam jest. Ty i chłopaki zajmijcie się sprawami tutaj. Wejdę do środka, zanim zabiorą skarb - wątpię, żeby ktoś wszedł tam przypadkiem.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "Dobrze. Ale bądź ostrożny, mam złe przeczucia co do tego.";
			link.l1 = "I ty! Idę tam.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "Chcesz coś powiedzieć, Kapitanie? Byłeś pogrążony w myślach przez całą naszą drogę do statku.";
			link.l1 = "Zgadza się. Myślałem ostatnio o tym, co robiłem. O Terraxie i... dokąd mnie to doprowadziło. Czy jestem bliżej uratowania mojego brata? Albo powrotu do domu?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Hm-m. Dobre pytania. A jakie są twoje odpowiedzi?";
			link.l1 = "Jeszcze jedno pytanie. Jeśli wcześniej to było bezcelowe, czy znowu będzie bezcelowe? Terrax mi nie pomoże. Ani z moim bratem, ani z Tortugą.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Prawdopodobnie nie. Nie ma z tego żadnego pożytku. Zaskakujące, że zdałeś sobie z tego sprawę dopiero teraz. Ale jakie jest twoje następne pytanie?";
			link.l1 = "Dlaczego, do diabła, biegałem za Terraxem jak piesek, wyciągając dla niego kasztany z ognia przez cały ten czas?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "To dopiero dobre pytanie. Właściwe. Czy masz teraz odpowiedź?";
			link.l1 = "Bardziej jak postanowienie. Dziś miałem szczęście. Ale czy będę miał szczęście ponownie? Ważne jest, by wiedzieć, kiedy przestać. I... szanować siebie. Mam dość.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Zdecydowałeś się zakończyć współpracę z Terraxem?";
			link.l1 = "Tak. Mam ważniejsze rzeczy do zrobienia. Rodzina, przyjaciele. Z nimi osiągnę swoje cele. I nie w ten sposób. A nawet jeśli... to nie z Markusem. Będę swoim własnym panem. Sam podejmę decyzje.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "  Człowiek, którego kiedyś śledziłem, znów przemawia. Nie wikłaj się znowu z nieodpowiednimi ludźmi. Nie marnuj potencjału, który kiedyś mnie zaintrygował. ";
			link.l1 = "Zrozumiałem, Hercule. I jeszcze raz dziękuję. Tym razem za to, że pomogłeś mi to w pełni zrozumieć. Nie jestem już Księciem, pachołkiem. Jestem Charles de Maure, dumnym szlachcicem. Wchodźmy na pokład statku - obaj jesteśmy zmęczeni.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "To była niezła eksplozja, panie - knippel do mojej rufy! Brzmiało jak salwa z Valkyrie. Ale obawiam się, że tamci ludzie też to zauważyli...";
			link.l1 = "Jeśli zauważyli, to ich problem. Nikt ich tu nie zapraszał. Gotowy dać im nauczkę, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Zawsze gotowy, panie!";
			link.l1 = "Doskonale. Do dzieła.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "Obawiam się, kapitanie, że będziemy mieli więcej towarzystwa. Jakie są wasze rozkazy?";
			link.l1 = "Wędrujemy głębiej w dżunglę i skryjemy się - nie ma szans wszystkich odeprzeć, a nie po to tu przybyliśmy.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Tak, panie.";
			link.l1 = "Więc ruszajmy!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "Śledzili nas, Kapitanie! Ale możemy się tutaj schronić - wygląda na to, że ta ścieżka dokądś prowadzi, chociaż myślę, że ktoś tam już jest.";
			link.l1 = "Nie szukamy schronienia! Wygląda na to, że ktoś inny dowiedział się o skarbie. Oto plan: ja pójdę zobaczyć, co się dzieje, zanim zabiorą wszystko, a ty z chłopakami ich tu powstrzymasz!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Tak, sir.";
			link.l1 = "Doskonale. Schodzę na dół! Wierzę, że zajmiesz się tu wszystkim.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... Czy wszystko w porządku, panie?";
			link.l1 = "Charlie! Wybrałeś idealny moment, by się o mnie martwić. Oszczędź sobie słów. Trzymasz się? Powinienem był zostawić cię na statku i zamiast tego wziąć więcej ludzi...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Ach, tylko zadrapanie, panie. Trochę zmęczony. Nigdy tak nie walczyłem, nawet w młodsze dni! Ale dałem im takie lanie, że będą słyszeć kniple po wieki!";
			link.l1 = "Marynarka Królewska, stara szkoła! Wygląda na to, że walczyłeś jak lew, Charlie. Ale mimo to ledwo stoisz. Nie blefuj - jak poważna jest rana?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "To nic poważnego, Kapitanie, tylko wyczerpanie. Wejście za tobą zawaliło się niemal natychmiast, a my odpieraliśmy tych ludzi przez wieki. W końcu zostałem sam, ranny. Więc dotarłem tutaj, aby oczyścić drogę i uzyskać pierwszą pomoc.";
			link.l1 = "Rozumiem. Cóż, zrobiłeś dziś swoje. Jeśli chodzi o mnie... zawiodłem. Wszyscy byliśmy oszukani i nastawieni przeciwko sobie dla czyjejś rozrywki-nie było nawet żadnego skarbu. I nie byłem jedynym głupcem tam.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "Nie udało się?.. Ale żyjesz, panie. Co się stało? Uciekłeś?";
			link.l1 = "Nie, ale i tak trzeba było trochę pobiegać. Przepraszam, stary przyjacielu, ale to, co tam się stało, nikomu nie powiem - nawet moim najbliższym przyjaciołom. Jednakże, wyciągnąłem potrzebne wnioski.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "Jakie wnioski, panie? Nie zawsze rozumiem twoje rozumowanie. Moja filozofia jest prosta - dobry culverin i knippels na maszt.";
			link.l1 = "Powiedz mi, musiałeś już wcześniej zabijać Hiszpanów, tak jak ja ostatnio. Jeszcze za czasów służby w Królewskiej Marynarce. I później, z Fleetwoodem.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "Tak zrobiłem. Hiszpanie, Holendrzy-wielu innych też. Jak mi kiedyś powiedział Dick, nasza służba jest niebezpieczna i wymagająca. Ale dlaczego pytasz? Jaki masz cel?";
			link.l1 = "Wyjaśnię. Ale najpierw, kolejne pytanie. Czy kiedykolwiek wątpiłeś w to, co robiłeś i dlaczego to robiłeś, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Hm-m. Powiedziałem sobie, że działam dla dobra Korony. Martwienie się o rozkazy to niewdzięczna robota - i tak trzeba je wykonywać.";
			link.l1 = "Korona... Cóż, miałeś swoje powody. Ja nawet tego nie miałem - Michel kazał mi zbliżyć się do Terraxa. Ale czy to było warte wszystkich poświęceń? Czy to pomogło mi czy jemu? Tak, tak, nie lubimy donów... ale wszyscy jesteśmy ludźmi.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "Chyba zaczynam rozumieć, do czego zmierzasz, panie.";
			link.l1 = "Dobrze. Powiedz mi, kiedy Fleetwood odszedł, czy cieszyłeś się, że już nie musisz ostrzeliwać holenderskich kupców? Niektórzy z nich byli uczciwymi ludźmi.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "Nie myślałem o tym nigdy, kapitanie. Ale powiem tak - zawsze cieszyłem się służąc z tobą, sir. Niech mnie pokręci z kniplem na szyi, jeśli kłamię!";
			link.l1 = "Ha-ha-ha, dobrze. Ale powiedz mi to - kto twoim zdaniem miał gorzej? Ty, wykonując rozkazy? Czy ja, który nie byłem zmuszony robić tego, co zrobiłem?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "Nie wiem, panie...";
			link.l1 = "Ani ja. Ale to nie ma znaczenia. Liczy się to, że nie chcę mieć już nic wspólnego z Terraxem. Dość tego. Koniec z Charliem Princem. Tylko Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "Ale czyż to nie było częścią twojego planu, by ocalić brata?";
			link.l1 = "Było tak. Ale w końcu wcale mi to nie pomogło. Więc jeśli kiedykolwiek będę musiał zrobić coś takiego ponownie - to będzie tylko moja decyzja. I tylko jeśli naprawdę przybliży mnie to do mojego celu.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "Mam nadzieję, że wiesz, co robisz, Kapitanie. I że nie skończysz jak Terrax. Albo na szubienicy.";
			link.l1 = "Też mam taką nadzieję. Ale jestem pewien, że od teraz moje cele i interesy będą na pierwszym miejscu. Teraz zajmijmy się twoimi ranami.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "Twoja eksplozja przyciągnęła uwagę, Lordzie Kapitanie. Wydaje się, że wrogowie zbliżają się do nas.";
			link.l1 = "Do diabła! ...Myślisz, że był lepszy sposób na poradzenie sobie z tymi drzewami? A co byś zrobił?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "Nie wiem. Ale wiem, co teraz robić - zająć się tymi ludźmi.";
			link.l1 = "Cóż, w porządku. Przypuszczam, że dokładnie to zrobimy.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "Nowi ludzie przybywają, Lordzie Kapitanie.";
			link.l1 = "Tak, zauważyłem, dziękuję, Longway. Ale nie mamy czasu na tych, więc wycofajmy się do dżungli - może nas zgubią.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Hmm, moglibyśmy sobie z nimi poradzić, oczywiście, ale jak mówisz.";
			link.l1 = "Nie potrzebujemy tej walki, więc ruszajmy dalej.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "Nie odpuszczą i nas złapią, Panie Kapitanie! Mówiłem ci, że powinniśmy ich zabić wcześniej. Czy powinniśmy przygotować zasadzkę w tej jaskini? Chociaż wydaje się, że ktoś już tam jest.";
			link.l1 = "Lepiej urządzić tu zasadzkę z chłopakami! Tego skarbu na pewno nie przegapię. Wygląda na to, że ktoś inny już dowiedział się o skarbie... Więc sprawdzę to sam.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Bądź ostrożny, Panie Kapitanie. Pamiętaj, że nawet wielki smok kiedyś umarł na szczycie góry złota.";
			link.l1 = "Będę miał to na uwadze, Longway. Spróbujmy dzisiaj nie umrzeć.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Panie Kapitanie, wygląda na to, że udało ci się stamtąd uciec.";
			link.l1 = "Zaskoczony, Longway? Choć muszę przyznać, że sam jestem nieco zaskoczony. Wygląda na to, że tylko ty wyszedłeś stąd żywy. Ale jak ci się to udało?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "Stado drapieżnych kotów nie pokona tygrysa. Gniazdo węży nie powali smoka. Wśród białych ludzi niewielu jest godnych przeciwników dla mnie.";
			link.l1 = "Ale pamiętaj, Longway, sfora psów może rozszarpać lwa.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "Teraz Pan Kapitan podzieli się swą mądrością z Longway'em? Szkoda, że nie posłuchałeś mojej rady wcześniej.";
			link.l1 = "O smoku na górze złota? To prawda, prawie nim zostałem - prawie umarłem, w rzeczywistości. Ale nie na górze złota - tego tam nie było. Zamiast tego znalazłem coś innego, równie ważnego.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "Następnym razem 'prawie' może się nie zdarzyć. Co znalazłeś, Panie Kapitanie?";
			link.l1 = "Tak, teraz to widzę. To, co znalazłem, to... mądrość. Doświadczenie. Zrozumienie. Decyzja. Powiedz mi, Longway, co ostatnio robiliśmy?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Jesteśmy piratami. Pracujemy dla waszego nowego pana, Lorda Terraxa. Przemycanie, plądrowanie miast, zabijanie, ratowanie i pomaganie jego ludziom.";
			link.l1 = "On nie jest moim panem, wiesz. Ale do licha, opisałeś to wszystko tak doskonale! Zapomniałem o dumie, szacunku do siebie i biegałem za nim jak piesek na smyczy.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway rozumie cię, Panie Kapitanie. Ja też pracowałem dla van Merdena i Rodenburga, zapominając o honorze, dumie i szacunku dla ukochanego celu.";
			link.l1 = "Powiedz mi, czy potępiasz się za to? Czy nienawidzisz siebie?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Potępiać? Czasami. Nienawidzić? Nie. Wiem i pamiętam, kim jestem. Pamiętam mój cel, moją gwiazdę przewodnią. Nic nie jest ważniejsze w życiu. A czy ty masz cel?";
			link.l1 = "Nie gwiazda przewodnia jak ty, ale wciąż ważny cel, tak - uratować brata. Lecz zboczyłem z tej ścieżki. I na to nie mogę sobie pozwolić powtórnie.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Pozwól, że podzielę się z tobą kolejną mądrością z Cesarstwa Niebios. Nie ma ludzi całkowicie dobrych ani złych. Każdy człowiek posiada zarówno Yin - ciemność i ignorancję - jak i Yang - światło i mądrość. Równowaga zmienia się w każdym z nas.";
			link.l1 = "A więc, moim Yang jest Charles de Maure. A moim Yin jest Charlie Prince. Chociaż może nawet Charles de Maure będzie musiał pewnego dnia podjąć mroczne i trudne decyzje.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "Takie jest życie, Panie Kapitanie. Każdy człowiek jest skazany na podejmowanie zarówno mrocznych, jak i jasnych wyborów.";
			link.l1 = "Jednak maska Księcia niemal się ze mną zrosła. Ale ją zrzucę. Charles de Mort jest szlachcicem, nie posłańcem. Od tej pory, tylko tak będzie. Odzyskuję swoją dumę i godność. Od teraz, jestem swoim własnym panem.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Długodystansowy aprobuje twoją decyzję, Panie Kapitanie.";
			link.l1 = "Dzięki, Longway. A tak przy okazji, czy nie żałujesz, że nie jesteś wolnym kapitanem? Służąc mi, jak mówisz, 'waszemu panu'?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. Longway tęskni za dowodzeniem własnym statkiem. Ale mój rozpoznaje twój. Za okazanie szacunku i mądrości mojemu, w przeciwieństwie do typowego białego barbarzyńcy. Być może mój chciałby innego życia. Ale mój nie żałuje, że pomógł tobie.";
			link.l1 = "Cieszę się, że to słyszę, Longway. Teraz... opuśćmy to miejsce i ścieżkę Yin. I wprowadźmy więcej Yang do naszego życia. Czy dobrze to zrozumiałem?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Tak, to prawda. Mam nadzieję, że od teraz podążysz dużo lepszą drogą.";
			link.l1 = "Dao?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "Droga, Panie Kapitanie. Lub Istota. Ale w naszym przypadku - Droga.";
			link.l1 = "Cokolwiek przyniesie mi przyszłość, nie zboczę znów z tego, co naprawdę ważne. Opuszczajmy to miejsce, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Kapitanie Charles, wielu ludzi zmierza w tę stronę. Twój sygnał dymny ich przyciągnął. I wyraźnie nie są nam przyjaciółmi.";
			link.l1 = "O, gdyby to był tylko 'sygnał dymny', jak to nazwałeś - to echo rozeszło się po całej dżungli. Nie ma wyboru - brońmy się. Zdecydowanie nie potrzebujemy ataku z tyłu przez cały oddział.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Tak, Kapitanie Charles. Uderzaj pierwszy!";
			link.l1 = "Atak! Nie oszczędzajcie kul!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "Nadchodzą jeszcze! Jeszcze więcej ludzi.";
			link.l1 = "Wycofajmy się do dżungli, Tichingitu! Skryjemy się i przeczekamy. Przybyłem tu po skarb, a nie po walkę!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "Jeśli zajdzie potrzeba, możemy zastawić zasadzkę w dżungli.";
			link.l1 = "Racja. Teraz ruszajmy - szybko, ale cicho.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Kapitanie Charles, spójrz! Przed nami jest przejście. Słyszę tam kroki i głosy.";
			link.l1 = "Ktoś inny dowiedział się o skarbie? Do diabła! Czy również słyszysz ten hałas za nami? Wygląda na to, że nas dogonili. Tichingitu! Pójdę sprawdzić, co jest przed nami. Ty zatrzymaj ich z chłopakami!";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "Próbujemy! Idź!";
			link.l1 = "Liczyłem na ciebie!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Kapitanie Charles! Przeżyłeś! Tichingitu będzie z tego zadowolony.";
			link.l1 = "Dziękuję, mój przyjacielu. Ja też się cieszę. Cieszę się, że przeżyłem i że z tobą wszystko w porządku. Wygląda na to, że jesteś jedynym, który pozostał z całego oddziału. Czy było ich wielu? Naprawdę dobrze ich powstrzymywałeś.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Wiele. Ale ja jestem jednym z najlepszych wojowników z naszej wioski Maskog. Co się tam z tobą stało? Znalazłeś skarb, którego szukałeś?";
			link.l1 = "Nie, Tichingitu. Zostaliśmy oszukani - nie było żadnego skarbu. Powiedz mi, co myślisz o tym, co ostatnio wszyscy robiliśmy?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "Co my robimy, Kapitanie Charles? Żeglujemy. Bijemy wrogów.";
			link.l1 = "Wydaje się, że mnie nie rozumiesz. Powiedz mi więc, czy jesteś smutny z powodu wygnania z twojego plemienia? Chcesz wrócić, tęsknisz za swoimi braćmi?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Oczywiście, tęsknię za przyjaciółmi i rodziną. Ale wrócić? Mój dom już nie istnieje bez... niej. Poza tym, jest ten zły kojot, szaman!";
			link.l1 = "Przepraszam, nie chciałem tego poruszać. Wiesz, niedawno dołączyłem do plemienia, tak to ujmijmy. Plemienia kapitanów jak ja. Ale w końcu zrozumiałem, że to tylko banda szakali, którzy myślą o sobie jako morskie wilki...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "I co teraz się dzieje? Co teraz robimy?";
			link.l1 = "Dobre pytanie. Sam prawie stałem się szakalem z tymi szakalami. Więc, wystarczy mi tego. Moi przyjaciele i moja załoga - to moja 'wataha'.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu jest zadowolony, że znalazłeś swoje plemię, kapitanie Charles.";
			link.l1 = "Dzięki, przyjacielu. Musiałem to powiedzieć. Ty i ja jesteśmy swoimi własnymi wodzami i plemionami. A teraz czas wrócić do naprawdę ważnych spraw.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Ktoś nadchodzi! I sądząc po odgłosach, nie po to, by dołączyć do nas w obchodach Dnia Dziękczynienia.";
			link.l1 = "Przeklęte korzenie! Dobra, teraz musimy rozprawić się z tymi łajdakami - lepiej teraz niż wtedy, gdy będziemy taszczyć skarb na statek.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "Masz rację. Gotowy?";
			link.l1 = "Nie musiałeś pytać. To nie tak, że mamy wybór.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "Są wszędzie, jak szczury w londyńskich slumsach, Wasza Wysokość! Jaki jest plan - mamy się trzymać i bić się z chłopakami?";
			link.l1 = "Nie teraz, wycofać się! Jesteśmy tu po skarb, nie po walkę!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Heh, tutaj nie ma sprzeciwu.";
			link.l1 = "Więc przyspiesz kroku!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "Hej, Kapitanie, spójrz - wygląda na to, że ta ścieżka gdzieś prowadzi. I brzmi tam całkiem żywo, sądząc po hałasie!";
			link.l1 = "Czyżby ktoś inny dowiedział się o skarbie? Tommy, słyszysz to? Dogonili nas. Dobra, ja idę naprzód, a wy przyjmijcie ich tutaj jak należy!";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Teraz to słyszę! Kimkolwiek oni są, lepiej się pospiesz, he-he. W przeciwnym razie, po co my się tutaj w ogóle włóczyliśmy?!";
			link.l1 = "Ach, nie chciałbym, żeby tak się stało.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Ach, to ty, kapitanie! Kurczę, przeżyłeś. Nie będę kłamać - nie spodziewałem się tego. Ale cieszę się, nie zrozum mnie źle, heh-heh.";
			link.l1 = "Nie spodziewałem się tego również, nie będę kłamać. Ale fakt, że przeżyłeś – to mnie wcale nie dziwi. Uciekłeś?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "Źle mnie oceniasz! Tommy Irons nigdy nie ucieka! On tylko wraca z posiłkami. Ale to nie było konieczne – moi ludzie i ja sobie z tym poradziliśmy, choć znowu, jestem jedynym, który wyszedł z tego cało, heh...";
			link.l1 = "Może tym razem powinieneś był poszukać posiłków. Ale ja... ja uciekłem.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "Uciekłeś? Heh, znów mnie zaskoczyłeś. Ale tak naprawdę chciałem się do ciebie rzucić, jak tylko skończyłem! Jestem lepszy niż jakiekolwiek posiłki, wiesz. Tylko że...";
			link.l1 = "Co się stało, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "Cholera, podczas gdy ja się grzebałem, wejście za tobą zostało zablokowane skałami. Nie mogłem się przedostać. To nawet żenujące, że zajęło mi to tyle czasu, by to oczyścić i nie mogłem ci tam pomóc. Trochę się sam pogubiłem, szukając drogi powrotnej, żeby znaleźć chłopaków i pomóc przesunąć skały... Jak wróciłem, ty już byłeś z powrotem.";
			link.l1 = "Tak, może będzie mi wstyd przyznać się, co się dziś ze mną stało.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "A co się stało? Nie bój się, powiedz mi. Ale jeśli to coś śmiesznego, będę się śmiać, żebyś wiedział. Jak inaczej miałoby być? Przyjaciel oferuje swoje ramię i szturcha cię łokciem w śmiechu.";
			link.l1 = "Cóż, na pewno wiesz, jak pocieszyć. Powiedz mi, Tommy. Mówiłeś, że lubisz piractwo. Byłeś zadowolony, że wróciłeś do tego ze mną?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "Powiem to tak. Czy jestem piratem, czy nie, zawsze cholernie uwielbiałem przygodę! Widzę, że moja odpowiedź cię nie satysfakcjonuje. Te rzeczy, te wielkie sprawy, to nie moja bajka.";
			link.l1 = "To nie to, że mnie to nie satysfakcjonuje. Ale nie o tym chciałem rozmawiać. Wiesz... Zrozumiałem, że z Tiraqsem całkowicie zboczyłem z moich celów. Poza tym... Charlie Prince był jakimś pachołkiem, a nie odważnym kapitanem piratów, rozumiesz, Tom? Mam tego dość.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "Rozumiem. Dlatego byłem zaskoczony, że pozwoliłeś, by Terrax tak tobą sterował. To nawet nie wyglądało na ciebie.";
			link.l1 = "Może rzeczywiście byłem wtedy Charliem Princem. Ale czy wrócimy do piractwa, czy nie, to ja zdecyduję! I tylko wtedy, gdy naprawdę będzie to służyć moim interesom i przybliży mnie do celu!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "To mi się podoba! Ale chcę powiedzieć, czy to Charlie Prince czy Charles de Maure - to wciąż ty. A z tobą zawsze było cholernie interesująco!";
			link.l1 = "Cieszę się, że to słyszę, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Pamiętaj, prawie nikt nie pomoże ci poza tobą samym. Lepiej robić to, co kochasz, nawet w pojedynkę, niż pozwolić innym podejmować za ciebie decyzje!";
			link.l1 = "Prawda. Dokładnie to czułem z Terraxem. Nawet jeśli znów komuś podążę, to tylko na godnych warunkach, a nie jak jakiś cholerny goniec!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "Masz rację! Teraz, wynośmy się stąd - nogi już mi się trzęsą.";
			link.l1 = "Ej, właśnie miałem to powiedzieć, ha-ha. Ale masz rację, ruszajmy. Mamy przed sobą dużo ważnej roboty, Tom. Nie takie rzeczy.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Kapitanie, wygląda na to, że mamy towarzystwo! Nie jesteśmy tu sami.";
			link.l1 = "Tego nam brakowało... Dobra, załatwmy ich teraz. Później będą tylko większym kłopotem.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Oj, Kapitanie.";
			link.l1 = "Gotów się szykuj!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "Jest ich coraz więcej!";
			link.l1 = "W takim razie nie ma sensu tego kontynuować! Wycofać się! Zgubimy ich i udamy się prosto po skarb!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "Ruszaj się, ruszaj się!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Kapitanie, wygląda na to, że jest tu wejście! I ktoś już jest w środku.";
			link.l1 = "Słuchaj uważnie - jesteśmy śledzeni. Wejdę i sprawdzę to, podczas gdy ty utrzymasz tę pozycję. Osłaniajcie mnie, chłopcy!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "Trzymaj się. Powodzenia tobie - nam wszystkim!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("widzę, złodziej! Strażnicy, chwytajcie go","widzę, złodziejka! Strażnicy, schwytajcie ją")+"!!!","Nie mogę w to uwierzyć! Odwróciłem się na sekundę - a ty już grzebiesz w moich rzeczach! Stój, złodzieju!!!","Strażnicy! Napad! Zatrzymać złodzieja!!!");
			link.l1 = "Aaaah, diable!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
