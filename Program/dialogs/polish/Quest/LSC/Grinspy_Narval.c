// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Czego? Czego chcesz?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+"Chciałem spotkać się z przywódcą klanu.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"Chcesz czegoś?";
				link.l5 = "Chciałem cię tylko przywitać. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Teraz mnie znasz. Mam na imię Donald Greenspen i nie denerwuj mnie ani moich ludzi. I nie próbuj odwiedzać 'San Gabriel', dopóki nie masz hasła. Sklep jest otwarty dla wszystkich, każdy potrzebuje handlować. Jakieś pytania?";
			link.l2 = "Nie, rozumiem. Do zobaczenia.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "Jakie masz dla mnie sprawy?";
			link.l1 = "Bardzo nieprzyjemna, Donaldzie. Ostatniej nocy dokonano zamachu na życie Stevena. Wzięli w nim udział wojownicy z twojego klanu.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Nie wiem o tym. Czemu sądzisz, że to byli moi ludzie?";
			link.l1 = "Ponieważ tam byłem. Potrafimy dostrzec różnicę między waszymi ludźmi, piratami a Rivados. Grupą dowodzili Mary Casper i Chad Kapper. Potrzebujesz więcej dowodów?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Jedyne, co mogę zapewnić, to że ja i moi ludzie nie mamy z tym nic wspólnego.";
			link.l1 = "Będziesz musiał przekonać o tym admirała, a to nie będzie łatwe. Dodson jest bardzo wściekły na wszystkich Narwali po ataku. Zamierza wypowiedzieć wam wojnę - przestanie dostarczać prowiant i będzie strzelał do waszych ludzi przy każdej nadarzającej się okazji. I to nie są tylko słowa.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Mam nadzieję, że admirał rozumie, co zamierza zrobić. Czy wątpi, że moi ludzie też potrafią strzelać?";
			link.l1 = "Myślę, że tak. Jest gotowy zamienić 'San Augustine' w twierdzę i walczyć, aż wszyscy umrzecie z głodu. Poza tym, Dodson zamierza porozmawiać z Rivados i zaproponować im współpracę. Nie macie szans przeciwko admirałowi i Rivados razem.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Cholera! Ale my nie jesteśmy częścią tej próby! Dlaczego cały klan musi płacić za działania tej głupiej dziewczyny Mary i bandy szumowin z mojej załogi?\nPoza tym, porozmawiajmy logicznie, zabijając Marlow, sam Dodson sprowokował Mary i moich żołnierzy. To właśnie się dzieje, gdy popełniasz takie podłości.";
			link.l1 = "Nic nie rozumiesz. Zostałeś oszukany. Dlaczego jesteś tak pewien, że to Dodson zabił Alana? Właściwie on myśli, że to ty to zrobiłeś, aby zająć jego miejsce...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Nie obchodzi mnie, co on myśli. Wszystkie dowody są przeciwko niemu. Tylko on i jego ludzie mieli dostęp do więzienia. Alan był w jego rękach. Czerwona Mary opowiedziała mi wiele. Zanim Alan został zamordowany, Dodson osobiście odwiedził więzienie i nie robi tego często.";
			link.l1 = "Widziałeś jego śmierć?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Bzdury! Oczywiście, że nie.";
			link.l1 = "A Chimiset ma. Tak-tak, czarodziej Rivados, który siedział obok Alana. On również został tam niedawno zamordowany. Byłem w więzieniu dzień przed jego śmiercią i rozmawiałem z nim. Milrow został zabity przez Chada Kappera, bosmana Rekina.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Czy to prawda?";
			link.l1 = "Pomyśl o tym: Chimiset nie przejmował się twoimi relacjami z admirałem. Nie miał powodu, by kłamać. Stary czarodziej bał się Chada, przypuszczał, że będzie następny. Miał rację, Chad zamordował go, gdy tylko dowiedział się, że admirał zamierza go uwolnić.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Ale dlaczego Kapper chciał śmierci Alana?";
			link.l1 = "Do diabła, naprawdę nie rozumiesz? Mówiłem ci, że Kapper współpracował z Czerwoną Mary. Chciał przejąć pozycję Rekina i stworzył przebiegły plan, aby to zrobić. Zabicie Alana Milrowa i rozpuszczanie plotek o udziale Rekina w jego śmierci uczyniło klan Narwali wrogim wobec admirała...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "Naiwna dziewczyna Mary zaufała mu i stanęła po stronie prawdziwego zabójcy swojego chłopaka. Przekonali kilku Narwali, by do nich dołączyli, to musiało być łatwe dla Mary. Następnie zorganizowali atak na admirała w kajucie Fazia, który został zmuszony do napisania zaproszenia dla admirała...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "Mam list od Fazio, który wszystko wyjaśnia. Chimiset został zabity przez Chada jako niebezpieczny świadek. Współpracował z Narwalami, a Rivados byliby naprawdę zadowoleni, słysząc to podczas rozmowy z Rekinem. Łatwo udowodnimy Czarnemu Eddiemu, że Chad stał się jednym z twoich, pokazując ten list.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. Masz wszystkie asy, co więc tutaj robisz? Chcesz czegoś ode mnie, prawda?";
			link.l1 = "Wiem. Bo wierzę, że to był cały plan Chada, a ty nie jesteś w to zamieszany. Chad zdradził Mary, ona wezwała swoich przyjaciół z twojego klanu, aby jej pomogli, i to cała historia. Przynajmniej nie znalazłem żadnych dowodów przeciwko tobie ani innym z klanu Narwalów...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "Ale to nie znaczy, że nie ma innych spiskowców. Chcę, byś ich odnalazł. Może wtedy załatwimy sprawy bez rozlewu krwi.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "Już ci mówiłem, że żaden z moich ludzi nie brał w tym udziału. Po śmierci Marlow'a Mary praktycznie opuściła klan i zamknęła się w swojej kajucie. Właściwie, nie mam pojęcia, jak udało jej się przekonać innych do udziału, ale wydaje się, że jej się udało. Przysięgam, że ani ja, ani nikt inny z mojego klanu nie działa przeciwko admirałowi.\nStraciliśmy ostatnio zbyt wielu ludzi, więc nie chcemy teraz wchodzić w jakieś kłopotliwe sprawy. Nie boję się ataku admirała, nawet połączonego z Rivados. Narwale to prawdziwi wojownicy i udowodnimy to w naszej ostatniej bitwie. Ale to byłoby bezcelowe\nJuż zdecydowaliśmy, że utrzymamy pokój z admirałem. Rivados to inna sprawa, nie negocjujemy z Negros. Jestem gotowy osobiście przeprosić admirała, poprosić o wybaczenie za moje podejrzenia wywołane śmiercią Milrowa i za atak na jego życie. Przysięgnę na Biblię, aby udowodnić swoją szczerość. Czy ty i Dodson zgadzacie się na to?";
			link.l1 = "Jestem. Czy jesteś pewien, że nie należy spodziewać się żadnych sztuczek od twoich ludzi?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Absolutnie. Poinformuję mój klan o prawdziwym zabójcy Alana Milrowa. Relacje moich ludzi z admirałem zmienią się natychmiast, zapewniam cię. Powiedz mi, czy rzeź będzie potrzebna po tym?";
			link.l1 = "Nie, nie dopuścimy do tego. Jestem tu, aby temu zapobiec. Ufam Ci, Donaldzie, i spróbuję przekonać Rekina. Mam jeszcze kilka argumentów... Do zobaczenia, Donaldzie!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "Rozmawiałeś już z admirałem? Jakieś rezultaty?";
			link.l1 = "Jestem w trakcie. Zobaczymy się później...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Rozmawiałeś już z admirałem? Jakieś wyniki?";
			link.l1 = "Tak, mam. Twoje przeprosiny są przyjęte, oskarżenia twojego klanu są wycofane. Co więcej, Rekin zaprasza cię, abyś przyszedł do niego i omówił warunki przyszłego pokojowego porozumienia między Narwalami a piratami.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "Szczerze mówiąc, nie spodziewałem się... To wspaniała nowina. Być może będziemy nawet w stanie przemyśleć ceny zaopatrzenia dla naszego klanu i nową politykę wobec Rivados.";
			link.l1 = "To dotyczy tylko ciebie i admirała.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Tak, oczywiście. Wyświadczyłeś wielką przysługę klanowi Narwalów, zapobiegając bezsensownemu rozlewowi krwi, a być może nawet całkowitemu unicestwieniu moich ludzi. Weź tę muszkietę wieżową jako dowód mojej wdzięczności, nie znajdziesz drugiej takiej broni\nPoza tym, masz pozwolenie odwiedzać nasze zastrzeżone obszary tak samo jak każdy członek klanu.";
			link.l1 = "Dziękuję! Żegnaj teraz, mam wiele rzeczy do zrobienia.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Powodzenia. Odwiedź mnie, jeśli będziesz miał jakieś pytania.";
			link.l1 = "Zrozumiano. Do zobaczenia!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ho! "+GetFullName(pchar)+"! Ty jesteś... nie, to niemożliwe! Czy ty żyjesz?!";
				link.l1 = "Wieści o mojej śmierci były nieco przesadzone, Donaldzie. Ha-ha, miło cię widzieć!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, mój przyjacielu "+GetFullName(pchar)+" ! Potrzebujesz czegoś?";
			link.l1 = "Nie, nie chciałem. Po prostu chciałem cię powitać.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "Jaką sprawę masz do mnie?";
			link.l1 = "Bardzo nieprzyjemna, Donaldzie. Był zamach na życie Stevena. Uczestniczyli w nim wojownicy z twojego klanu.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "Nie wiem o tym. Dlaczego myślisz, że moi ludzie byli w to zamieszani?";
			link.l1 = "Ponieważ osobiście zabiłem kilku z nich wraz z Chadem Kapperem, bosmanem admirała, który jest odpowiedzialny za cały ten bałagan. Nie był w stanie zrobić tego sam, więc twoi ludzie mu bardzo pomagali. Admirał o tym wie i jest bardzo, bardzo wściekły.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "Moi ludzie? Kto dokładnie, możesz ich wymienić?";
			link.l1 = "Nie przedstawili się. Po prostu strzelali i szermierkowali. Wasi ludzie są lekkomyślni. Mogą zaatakować nawet jednego ze swoich. Do diabła ze mną czy z admirałem, ale próbować zabić dziewczynę?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. O kim mówisz?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Z kim rozmawiam? Mówię o ataku na Czerwoną Mary. Dwóch Narwali próbowało ją zabić. Dostałem się do jej kajuty w krytycznym momencie przez czysty przypadek. Zabraliby ją, gdybym przyszedł później. Nie zapytałem o ich imiona, przepraszam, nie miałem czasu z nimi rozmawiać, ale Mary powiedziała, że to byli Narwale.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "O kim mówię? Mówię o ataku na Czerwoną Marię i tych dwóch Narwalach, którzy ją zabili.";
				link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "Co? Dlaczego mi nie powiedziała?! Działałbym natychmiast!";
			link.l1 = "Bała się ostatnio nawet opuścić swoją kajutę. Niedawno miała z tobą sprzeczkę, więc dlaczego miałaby do ciebie biec i prosić o pomoc?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "Nie kłóciłem się z nią! Żądała ode mnie niemożliwego, mieliśmy ostrą rozmowę i odesłałem ją. Ale to nie znaczy, że ja...";
			link.l1 = "Dobrze, cokolwiek. W końcu wszystkie problemy są teraz rozwiązane. Ale wśród twoich ludzi są łajdaki, to fakt.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "Co? Zabiły ją Narwale? Dlaczego?";
			link.l1 = "Na rozkaz Chada Kappera, Donaldzie. Wiedziała za dużo i nie chciała pomóc Chadzie. A teraz biedna dziewczyna nie żyje!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "Przysięgam, nie wiedziałem o tym!";
			link.l1 = "Jasne, że nie... Ale porozmawiajmy o admirale. Chad Kapper zorganizował zamach, a twoi ludzie mu pomogli. Próbowali otruć Dodsona, a ja ledwo temu zapobiegłem.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "Nie zamawiałem niczego takiego. Dodson wie, że nie popieram polityki zmarłego Alana i uważam, że chudy kompromis jest lepszy niż gruby proces.";
			link.l1 = "Musisz w tym upewnić admirała, a to nie będzie łatwe. Dodson jest bardzo rozgniewany na wszystkie Narwale po tej próbie. On zamierza wypowiedzieć ci wojnę.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "Mam nadzieję, że admirał rozumie swoje działania. Czy wątpi, że moi ludzie potrafią odpowiedzieć ogniem?";
			link.l1 = "Tak myśli. Uważa, że wasz klan to banda zbójów i musi zostać zniszczony, zanim zaczniecie zabijać wszystkich. Poza tym mamy silne powiązania z Rivados. Mogę po prostu porozmawiać z Czarnym Eddiem i zaproponować mu sojusz. Nie stawicie nam czoła.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Cholera! Dlaczego cały klan musi płacić za działania kilku idiotów? Nie myśl, że się boję. Jesteśmy wojownikami i udowodnimy to nawet w naszej ostatniej bitwie. Ale chcę sprawiedliwości. Właściwie to admirał jest odpowiedzialny za zabicie Alana Milrowa w więzieniu.";
			link.l1 = "Jak możesz być liderem, Donald... Nie wiesz ani o Mary, ani o Alanie. Chad Kapper go zabił. "+sTemp+" Zrobił to, aby uczynić Narwali wrogimi wobec admirała i przeciągnąć niektórych z nich na swoją stronę.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "Rozumiem. Dobrze. Porozmawiajmy w inny sposób. Jesteś tu z jakiegoś powodu, prawda? Czego chcesz?";
			link.l1 = "Nie chcę krwawej rzezi na Wyspie. Nie chcę, żeby ludzie ginęli. Nie podoba mi się pomysł eliminacji wszystkich Narwali, choć zapewniam cię, że Rivados i my jesteśmy w stanie to zrobić. Myślę również, że cały klan nie powinien odpowiadać za działania niektórych drani...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "Ale mój głos nie wystarczy - powinieneś oficjalnie zapewnić admirała, że ta próba nie była przez ciebie zatwierdzona i twój klan nie planuje zabić Dodsona.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "Co mogę zrobić? Jestem gotów przeprosić za próbę i za moje podejrzenia dotyczące śmierci Marlowa. Mogę go zapewnić, że Narwale nie planują niczego przeciwko niemu i przysięgnę na świętą Biblię. Czy ty i Dodson uznacie to za wystarczające?";
			link.l1 = "Zrobię to. Jestem pewien, że Dodsonowi również spodoba się, jeśli odwiedzisz go osobiście. Ale najpierw powiem mu o twoich zamiarach, a potem odwiedzę cię ponownie z wynikami.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "Dobrze. Będę czekać.";
			link.l1 = "Zaraz wrócę...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "Rozmawiałeś już z admirałem? Jakieś rezultaty?";
			link.l1 = "Tak, mam. Jeśli złożysz mu oficjalną wizytę, problem zostanie rozwiązany.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "Szczerze mówiąc, nie spodziewałem się... To wspaniała wiadomość.";
			link.l1 = "Tak, wiesz, ja też się cieszę.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "Wyświadczyłeś wielką przysługę klanowi Narwali, zapobiegając bezsensownej masakrze, a być może nawet całkowitemu wyniszczeniu mego ludu. Przyznaję ci tę wieżową muszkietę - nie znajdziesz drugiej takiej broni. Masz również pozwolenie na odwiedzanie naszych statków bez żadnych ograniczeń.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Dziękuję. Bardzo cenny dar. Tak, Donald, jeszcze jedna rzecz: pogódź się z Czerwoną Mary. Jest porywcza, ale także szczera i uczciwa. Kłótnia z tobą sprawiła, że odeszła z klanu i prawie przypłaciła to życiem.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Dzięki. Bardzo cenny dar. I naprawdę cieszę się, że wszystko tak dobrze się skończyło.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Powiedz jej, że proszę o wybaczenie za to, że ją skrzywdziłem oraz za tych dwóch łajdaków, którzy ośmielili się ją zaatakować. Wy oboje jesteście... przyjaciółmi, prawda?";
			link.l1 = "Masz rację, Donaldzie. Powiem jej. I naprawdę cieszę się, że wszystko skończyło się tak dobrze.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Powodzenia. Zgłoś się do mnie, jeśli będziesz miał jakieś pytania.";
			link.l1 = "Dobrze. Do widzenia!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Popatrz tylko na to! Jak tylko pogrążyłem się w zadumie, ty postanowiłeś przejrzeć moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Głupia dziewczyno!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swą broń. Przez nią się denerwuję.","Wiesz, bieganie z ostrzem tutaj nie jest tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Schowaj go, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Z pewnością.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i prosiłbym cię, byś schował swój miecz.","Słuchaj, jestem obywatelem tego miasta i prosiłbym cię, abyś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Pewnie.","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, przyjacielu, zbiegać z bronią. Mogę się zdenerwować...","Nie lubię, kiedy mężczyźni chodzą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiano.","Zabieram to.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
