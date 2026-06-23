// Рамона Лоцано - горячая испанская сеньорита
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zmykaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Cześć, cześć! Nowicjusz? A może ukrywałeś się w ładowniach, bo pierwszy raz widzę twoją twarz w okolicy?";
				link.l1 = TimeGreeting()+". Ukrywanie się w ładowniach to nie dla mnie. Wolę miejsce kapitana... Tak, jestem tu nowicjuszem.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+pchar.name+"! "+TimeGreeting()+" ! Cieszę się, że cię widzę! Co powiesz";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się miewasz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Cóż, poznajmy się zatem... kapitanie. Jestem Ramona Lozano, ale nawet nie próbuj nazywać mnie senora Lozano, nienawidzę tego. Jak masz na imię?";
			link.l1 = ""+GetFullName(pchar)+"Przyjemność cię poznać, Ramono.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Czy naprawdę jesteś zadowolony, czy tylko udajesz uprzejmość, "+GetFullName(pchar)+"Powiedz, czy naprawdę jesteś kapitanem, czy żartowałeś?";
			link.l1 = "Oho, tyle pytań naraz! Czy mogę odpowiedzieć na nie po kolei? Po pierwsze, naprawdę się cieszę, nie spotykam codziennie pięknych dziewczyn, po drugie, jestem kapitanem, to prawda. Ale mój statek jest teraz u wybrzeży Zachodniego Głównego...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Zabawne! A jak to możliwe, kapitanie? Jesteś tutaj, ale twój statek jest przy brzegach Main. Czy nie boisz się, że twoja załoga się rozproszy, a twój okręt zostanie ci odebrany?";
			link.l1 = "Płynąłem tutaj na barku w celu... eksploracji, ale wszystko poszło nie tak i znalazłem się na waszej Wyspie. Następnie zderzyliśmy się z jakimiś szczątkami w ciemności, przewróciliśmy się i voila! Oto jestem. Mój statek będzie na mnie czekał tak długo, jak będę chciał. Dannie Hawk będzie w stanie kontrolować moich ludzi.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk? Ta Danielle Hawk? Chcesz powiedzieć, że żeglujesz z nią?";
			link.l1 = "Gówno wypływa na wierzch, Dannie służy mi jako oficer. Została, by dowodzić, gdy mnie nie ma... Skąd ją znasz?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha! Wszyscy w hiszpańskich koloniach znają piratkę Danielle Hawk i jej męża, Nathaniela. Tak, ty, señor "+GetFullName(pchar)+", musi być twardym facetem... Jesteś więc piratem? Nie martw się, dobrze dogaduję się z takimi jak ty. Lubię twardych facetów.";
			link.l1 = "„Cóż, nie jestem tak naprawdę piratem... Po prostu teraz współpracuję z Janem Svensonem i szukam męża Dannie, Nathaniela.”";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "A teraz zamierzasz mi powiedzieć, że nie jesteś piratem? Pracujesz dla Diabła Leśnego, twój pierwszy oficer to Dannie Hawk, a szukasz Nathana Hawka... i jestem pewien, że przyszedłeś tutaj po admirała. Prawda?";
			link.l1 = "Ramona, możesz mnie nazywać piratem, jeśli chcesz, nie mam nic przeciw temu. Możesz nawet nazwać mnie kotwicą, tylko nie wrzucaj mnie do wody...";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Wydaje się, że jesteś jednym z tych naprawdę poważnych gości, "+pchar.name+" Dobrze, muszę iść. Do zobaczenia! Czuję, że możemy zostać przyjaciółmi... bardzo bliskimi przyjaciółmi.";
			link.l1 = "Czemu nie? Powodzenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "O, naprawdę? Cóż, pytaj, odpowiem, jeśli będę mógł...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak się tu dostałeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Z pewnością nigdy nie próbowałeś stąd uciec...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Jak tu żyjesz?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Co tu robisz? Rozumiem, że jedzenie nie jest za darmo, prawda?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "To długa historia... Mój ojczym jest temu winien. Cztery lata temu mieszkałem w Hawanie i nie mogłem sobie nawet wyobrazić, jak potoczą się moje losy. Moja matka zmarła, a ja byłem jej prawnym spadkobiercą. Nie byliśmy bogaci, ale mieliśmy wystarczająco pieniędzy, więcej niż potrzeba na przyzwoite życie. Mojemu ojczymowi się to nie podobało i postanowił się mnie pozbyć\nOczywiście, dowiedziałem się o tym dopiero po tym, jak dwóch wynajętych oprychów zaatakowało mnie tuż za bramami miasta. Ci głupcy sami mi powiedzieli, kto ich wynajął, żeby mnie zabić i dlaczego. Na szczęście, nie byli profesjonalistami, leżałbym teraz w krzakach z poderżniętym gardłem, gdyby tak było. Idioci postanowili najpierw trochę się zabawić\nLos ocalił mnie tego dnia, kapitan taki jak ty przechodził obok bram. Zobaczył przedstawienie i natychmiast zabił tą hołotę. Nie mieli żadnych szans. Opowiedziałem mu, co mi się przytrafiło i dlaczego. Trochę popłakałem... Wiedział, że nie mam dokąd pójść, więc zabrał mnie na swój statek, bym tam zamieszkał. Najpierw tymczasowo, a potem\nWierzę, że zostałbym z nim, ale dwa miesiące później walczył z patrolem, stracił maszt, wpadł w silny sztorm i znalazł pokój na dnie zewnętrznego pierścienia. Przeżyłem mimo wszystko i dołączyłem do społeczności Wyspy Sprawiedliwości.";
			link.l1 = "Smętna opowieść, nie mam nic do powiedzenia...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Oczywiście, że nie. Bo to niemożliwe. Widziałem człowieka, który próbował opuścić to miejsce na szalupie... wrócił dwa dni później. Przywiązany do wraku masztu, żeby się nie utopić. Był siny i absolutnie martwy\nWięc powiedz mi, "+pchar.name+", co mam zrobić, jak tylko stąd ucieknę? Hawana jest dla mnie zbyt niebezpieczna, ojczym znowu spróbuje mnie zabić. Nie mam domu, ani pieniędzy. Dokąd mam się udać? Do burdelu?";
			link.l1 = "Jednakże, chcesz wrócić do archipelagu?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "A co ty myślisz? Oczywiście, że chcę. Ale to niemożliwe i właśnie ci powiedziałem dlaczego. Ech, gdyby tylko ktoś mógł rozprawić się z moim ojczymem... ostrym stalowym czy kulą, wtedy byłaby jakaś szansa, bym wrócił do normalnego życia. Ale kto by się odważył to zrobić, skoro mój ojczym to najlepszy przyjaciel alcalde z Hawany? I dlaczego o tym rozmawiamy? Stąd nie ma wyjścia...";
			link.l1 = "Zobaczymy. Przyjdzie czas...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Jakoś żyję. Nie ma innej opcji. Moi przyjaciele to głównie mężczyźni, bo dwie nasze piękne kandydatki na małżonki - Gillian i Tanneke nie lubią mnie z powodu mojego charakteru, a ich pokazowa przyzwoitość mnie mdli. Natalie była fajną dziewczyną, dopóki nie zaczęła spędzać dużo czasu z tymi głupkami, głupota jest zaraźliwa.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Pracuję jak inne dziewczęta. Naszym głównym celem jest pomoc mężczyznom. Na Wyspie Sprawiedliwości jest dużo pracy dla kobiet, więc jestem dość zajęta. Często dostaję prezenty, to tutaj normalne. Ale nie myśl o mnie źle, nie jestem jakąś ladacznicą. Byłam dobrze wychowana w porządnej rodzinie. Po prostu nie udaję świętej, jak niektórzy.";
			link.l1 = "Nie myślałem, że coś z Tobą jest nie tak...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodziej!","Spójrz tylko na to! Jak tylko pogrążyłem się w zadumie, postanowiłeś zajrzeć do mojej skrzyni!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się zajrzeć do moich skrzyń? Nie ujdzie ci to na sucho!";
			link.l1 = "Niemądra dziewczyno!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż to, nie pasuje do ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Jasne.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i proszę cię o schowanie ostrza.","Słuchaj, jestem obywatelem tego miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Jasne.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kolego, biegnąc z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z gotową do użycia bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiałem.","Zabieram to.");
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
