// диалоги Уракана, Канека и прочих индейцев ица
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
		case "First time":
			dialog.text = "Czy jest coś, czego potrzebujesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Kolejna blada twarz... Wielki kapłan chętnie wyrzeźbi z ciebie twe serce...","Blada twarz wie, jak dotrzeć do Tayasal, ale nikt nie opuszcza miasta!","Jestem zaskoczony, blada twarzy: jeszcze nie poszedłeś do krainy duchów... Idź, póki możesz, wkrótce ujrzysz swoich przodków.");
			link.l1 = LinkRandPhrase("No cóż, zobaczymy...","Nie próbuj mnie straszyć, czerwonoskóry wojowniku. Widziałem gorsze rzeczy niż to.","Idź, idź. Spróbuj przestraszyć dzieci.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("Błogosław mnie na bitwę z wrogiem, wielki Cavilu!","Wielki Cavil i wielki Kukulcan zaszczycają nas swoją obecnością. Nawet w czasach starożytnych Majów to się nie zdarzało!","Przekażemy legendę o wielkiej bitwie Kukulkana i Cavila naszym dzieciom!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "Jesteś wielkim wojownikiem, blada twarzy. Zaniesiemy twoją krew bogom. Umrzesz z godnością.";
			link.l1 = "Spokojnie, wojowniku czerwonej skóry. Nie pozwolę, by twój Kanek złożył mnie w ofierze Kukulkanowi czy komukolwiek innemu. Twoi wojownicy nie zdołali mnie pojmać. Każdy z nich poległ w walce.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Tak, łaskawy wojowniku, blada twarzo. Lecz nie wytrzymasz setek wojowników Tayasal Itza. Ale, mówisz ciekawie. Skąd wiesz o wielkim Kaneku i Kukulkanie?";
			link.l1 = "Cóż, pozwól, że zgadnę... Skoro nie jesteś Kanek, to twoje imię musi być Urakan i jesteś synem kapłana Kaneka?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Twoje wargi mówią prawdę, blada twarzy. Jestem Urakan i jestem zaskoczony.";
			link.l1 = "Jeszcze bardziej się zdziwisz, gdy na to spojrzysz... Zobacz.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "O, bogowie! Jeśli blada twarz ma maskę, to znaczy, że nadszedł czas... Jesteś tym, o którym mówił Kukulcan. Rozkazał, by cię do niego przyprowadzić, gdy dotrzesz do Tayasal. Wie, że przybywasz.";
			link.l1 = "Kukulcan?! On jest tutaj w Tayasal?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Tak, biały wojowniku. Quetzalcoatl przybywa do Tayasal. Wkrótce wyruszy, by przynieść światło przodkom, wielkiemu miastu Majów.";
			link.l1 = "Do diabła! Więc on już tu jest... (ściszając głos) Urakan, wiem wszystko. Wiem, że to ty wysłałeś Ksatl Cha ze Strażnikiem Prawdy, aby szukać Ksocheatem i maski Kukulkana...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "Widzę zaskoczenie w twoich oczach, ale także wątpliwość, wielki wodzu Urakan. Nie jesteś zadowolony z Kukulkana, prawda?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Każdy wojownik Itza szczęśliwy, że wielki Kukulkan przybył, biały wojowniku. Musisz stanąć przed Kukulkanem. Czeka na ciebie wiele nocy. Jest wielkim prorokiem. Zna wszystko z wyprzedzeniem. Idź do Latającego Węża, nie masz innej drogi. Nie pozwolimy ci opuścić Tayasal.";
			link.l1 = "Czy nie rozumiesz, że gdy tylko Kukulcan przejdzie przez bramy czasu, wszyscy wy, a także ty osobiście, przestaniecie istnieć? A najlepsze jest to, że odrodzisz się w innym wizerunku, w innym ciele... Może jako prosty wojownik, a może nawet jako kaleka lub żebrak...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Idź, bladolicy wojowniku. Znajdziesz Kukulkana w Wielkiej świątyni wojowników Itzy. Idź prosto przez most, aż zobaczysz wielką piramidę. Wejdź przez dolne drzwi świątyni i podejdź do sanktuarium.";
			link.l1 = "Dobrze. Pójdę do Kukulkana, bo widzę, że nie unikniemy tego spotkania. Ale ostrzegłem cię.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Idź, biały wojowniku. Kukulkan czeka na ciebie.";
			link.l1 = "Jestem w drodze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "To się spełniło! Kiedy zobaczyłem, jak walczysz z Kukulkanem, wiedziałem, że jesteś samym Cavilem. Przybyłeś do Tayasal, by ocalić lud Itza przed śmiercią z powodu ojca i Kukulkana. Mój ojciec, wielki kapłan Kanek, skazał lud Itza na zagładę w chwale dawno zmarłych przodków Majów.\nJestem wodzem wojennym Urakanem, który chronił lud Itza przez wiele lat. Żaden blady człowiek nie opuszcza Tayasal żywy. Ja i wojownicy zapewniamy, że lud Itza będzie chroniony i żywy przez wiele, wiele lat. Nie chcę poświęcać całego mojego ludu.";
			link.l1 = "Wiedziałem o tym, Urakan. Dlatego poprosiłem cię o pomoc na moście.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Nic nie umknie oczom wielkiego Cavila. Wybacz Urakanowi, że nie zrozumiał, kim naprawdę jesteś.";
			link.l1 = "Nie martw się o to, wodzu. Pokonałem śmiertelne wcielenie Kukulkana, ale mamy przed sobą drugie ważne zadanie - zamknięcie bram do przeszłości. Ta nienaturalna dziura w czasie musi zostać wyeliminowana. Pomożesz mi?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "Jak Urakan może ci pomóc, o Cavil?";
			link.l1 = "Posłałeś Ksatl Cha ze Strażnikiem Prawdy na poszukiwania Ksocheatem i maski Kukulkana. Więc wiesz, że można jej użyć do zamknięcia bram czasu. Czy twój ojciec ci o tym powiedział?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Ojciec nie mówi. Studiuję pisma w świątyni Wiedzy i Mądrości. Ale wiele jest niejasne dla Urakana. Może Cavil zrozumie?";
			link.l1 = "Czego dokładnie się dowiedziałeś?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "Uczę się na pamięć. Pisanie głosi: 'Gdy słońce wschodzi naprzeciw deszczu, a ogień między nimi w trójkącie, uderzaj nogą Tohil o nogę i spal maskę Kukulkan na ołtarzu czasu. I zapieczętuj bramy czasu Itzamna aż do końca dni.'";
			link.l1 = "Co.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Tak.";
			link.l1 = "Jezu... Pokaż mi bramy.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "Znajdują się w świątyni Kukulkana. Ale drzwi tam są zamknięte. Tylko mój ojciec może je zamknąć i otworzyć. Gdy otwiera drzwi do świątyni Kukulkana, mówi: 'Słońce przychodzi i odchodzi, woda spada i ustępuje, ogień zapala się i gaśnie, wojna i pokój się zmieniają, ale tylko niebo jest wieczne. Ponad czasem jest tylko niebo.'";
			link.l1 = "Interesujące... Zapamiętajmy to i zobaczmy, co możemy zrobić...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "Zostaję tutaj, na dole, blisko ołtarza czasu. Widzę każdą piramidę i budynek w Taysal od środka. Znajdź klucze. Ja zostaję tutaj.";
			link.l1 = "Jeśli będę miał jakieś ważne pytania, na pewno zwrócę się do ciebie.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "Jak Urakan może pomóc wielkiemu Cavilowi radą lub działaniem?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Spójrz na tę tabliczkę, którą znalazłem. Sądzę po miejscu, gdzie ją znalazłem, że musi mieć coś wspólnego z twoim ojcem i zdecydowanie nie jest to zwykły przedmiot...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "Znalazłem inne wejście na szczycie Wielkiej Świątyni, ale jest zapieczętowane. Jak mogę się tam dostać? Może to, czego szukam, jest tam w środku.";
				link.l1.go = "treasure";
			}
			link.l9 = "W niczym, Urakan. Poradzę sobie sam...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "Kamienna płyta bogów. Ojciec ma kilka różnych kawałków i są dla niego bardzo cenne. Starożytni budowniczowie Tayasal używali płyt do aktywowania ukrytych mechanizmów, otwierania i zamykania drzwi, a nawet do magicznych rytuałów.\nDziałają, jeśli umieści się je w odpowiednim miejscu - to właśnie robi mój ojciec. Ale ja jestem wojownikiem, tak jak ty, nie wiem, jak ich używać właściwie. Może Cavill wie?";
			link.l1 = "Z pewnością dotrzemy do sedna sprawy...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "To są drzwi do skarbów Tayasal. Tam leżą bogactwa Indian Itza. Drzwi wewnętrzne tylko mój ojciec otwiera i zamyka. Nikt nie śmie wchodzić do skarbów bez niego. Nawet ja nie.";
			link.l1 = "Jak twój ojciec otworzył wejście?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "Mój ojciec mówi: 'Każde bogactwo ma dwie strony. Tylko ten, kto zna te dwie strony, wejdzie do skarbów Tayasal.' Co to znaczy - nie wiem. Może, Cavil zgadnie?";
			link.l1 = "Z tym też sobie poradzimy...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Zrobiłeś to, o wielki Cavilu! Lud Itza teraz bezpieczny. Ja, Urakan, syn Kaneka, zapewniam cię, że nie przyniosę wstydu honorowi, który mi dajesz, i ochronię Tayasal przed każdą inwazją niehonorowych bladych twarzy w twoim imieniu.";
			link.l1 = "Mogę w to uwierzyć, wodzu. No cóż, możemy teraz świętować: położyliśmy kres zdradzieckim planom Kukulkana. Nigdy więcej nie będzie w stanie zmaterializować rewolucji czasu.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Chwała wielki Cavil! Na mnie i moje pokolenie spada wielki zaszczyt widzieć w Tayasal dwóch bogów. Piszemy tę historię dla naszych dzieci. Oni będą wiedzieć o bitwie bogów w Tayasal! Chwała Cavil! Chwała!";
			link.l1 = "O matko Boska, musze się czegoś napić...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "Stoisz przed Skrzydlatym Wężem, blada twarzo. Duch potężnego Kukulkana w ludzkim ciele. Masz szczęście być jego bratem przez ojca jego wcielenia, tak jak ja mam szczęście być ojcem jego matki, kobiety, która go urodziła. To wielki zaszczyt. Być może dlatego stałeś się silnym wojownikiem i wciąż żyjesz.\nAle twój czas się skończy, blada twarzo. Rozpoczniemy nową erę, erę wielkich Majów. Ustanowimy własną władzę i nigdy nie pozwolimy bladym twarzom wejść do naszego świata. Wkrótce. Ja, kapłan Kanek, rozpocznę rytuał!";
			link.l1 = "Wspaniale...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, słyszałeś, co powiedział nasz pan. Poddaj się teraz!";
			link.l1 = "Kiedy wielcy walczą ze sobą, lepiej dla nas, prostych śmiertelników, stanąć z boku i obserwować z daleka, ojcze...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "Co?! Opamiętaj się, synu!";
			link.l1 = "Ten człowiek to brat Kukulkana i wielki wojownik. Widzę w nim ucieleśnienie samego Cavila! Nikt poza nim nie zdołałby wytrzymać z bogiem jak ON. Żaden drobiazg w pojedynku bogów, ojcze! A jeśli przyniesiesz ofiary Kukulkanowi, moi wojownicy oddadzą swą krew Cavilowi!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "Czyś ty rozum postradał, Urakan?";
			link.l1 = "Wiele lat ja, nazwany Urakan, z powodzeniem chroniłem nasze ziemie w imieniu Cavila przed najazdami obcych. Setki z nich padły pod naszymi pałkami i nikt nie opuścił Tayasal. Ale nigdy w życiu nie widziałem wojownika tak silnego i zwinnego jak ta blada twarz. Jeśli on potrafi pokonać Kukulkana, to jest ucieleśnieniem ducha samego Cavila!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
