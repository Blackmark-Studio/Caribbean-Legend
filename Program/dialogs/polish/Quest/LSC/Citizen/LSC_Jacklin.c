// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zjeżdżaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Dzień dobry, monsieur. Jesteś tu nowy, prawda?";
				link.l1 = TimeGreeting()+"Tak, chyba jestem tutaj najnowszy. Nazywam się "+GetFullName(pchar)+" A jakie jest twoje?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacqueline Turam. Dwa lata temu byłam przyzwoitą i zamożną kupcową, właścicielką i kapitanem własnego fleuty. Niestety, teraz jestem biedna jak mysz kościelna i nie mogę mieć nadziei, że moja sytuacja się jakoś zmieni\nNiektórym tutaj się poszczęściło - znajdują klejnoty, złoto, statki pełne skarbów, ale ja nie należę do nich. Znalazłam tylko skrzynię z dublonami i kilka drobiazgów\nPrzynajmniej to wystarczy, żeby kupić jedzenie, więc nie głoduję... Miło cię poznać, panie, nie mam nic przeciwko pogadaniu...";
			link.l1 = "Miło cię również poznać, Jacqueline. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","  Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi najnowsze plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Zamieniam się w słuch.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak się tu dostałeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Co tutaj robisz?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Powiedz mi, widzę, że na Wyspie są dziewczyny i kobiety...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Chcesz wrócić do wielkiego świata?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "To nic.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Chcesz usłyszeć moją opowieść? Dobrze. Jak już wiesz, byłem kapitanem handlowym. Pewnego dnia płynąłem z Tortugi do Belize na moim starym dobrym flecie. Moje ładownie były pełne czarnego drewna i kakao, wydałem wszystkie monety na ten ładunek\nZorganizowałem bardzo korzystny interes z jednym człowiekiem, chciał kupić mój ładunek za niezwykle wysoką cenę. Mogłem na tej transakcji zbić majątek. Wszystko szło dobrze, nie było ani jednej chmurki na niebie, mój statek był szybki jak ptak. Nie spodziewaliśmy się kłopotów\nPłynąłem w pobliżu Kuby, trzymając się z dala od hiszpańskich patroli, ale nagle zaatakowała nas piracka galeona. Co oni tam robili - w środku hiszpańskiego terytorium? Próbowaliśmy uciec, ale nie udało się, galeon był zaskakująco szybki\nPiraci ścigali nas i zaatakowali. Ich kuleweryny były naładowane śrutem, pierwsza salwa mocno uszkodziła moją załogę i zdemoralizowała ją. Chciałem dać im dobrą walkę, ale moi własni marynarze i oficerowie mnie powstrzymali. Poddaliśmy się\nPiraci szybko zabrali nasz ładunek i wyrzucili nasze działa. Myślałem, że to koniec. Utrata ładunku była ciężkim ciosem, ale nadal mogłem zarabiać na frachtach i pewnego dnia stanąć na nogi\nAle okazało się inaczej. Pirackie łajdaki otworzyły ogień do mojego bezbronnego fletu. Byliśmy idealnym celem strzeleckim\nWciąż pamiętam ich śmiech... Galeon odpłynął, a my toniemy, trzymając się wraków. Potem przyszła silna wichura z falami i nigdy już nie widziałem nikogo z mojej załogi. Udało mi się przywiązać do części masztu i utrzymać na powierzchni\nOszczędzę ci dodatkowych szczegółów o ataku rekinów. Po jakimś wiecznym okresie czasu prąd morski przywiódł mnie tutaj. Tak właśnie przeżyłem.";
			link.l1 = "Tak, to naprawdę smutna historia.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Żyję jak reszta miejscowych - po prostu żyję. Szukam cennych rzeczy na zewnętrznym pierścieniu i wymieniam je na jedzenie. Marzę o znalezieniu skrzyni indiańskiego króla pełnej skarbów... Albo przynajmniej galeonu z hiszpańskim złotem, he-he. Nie zwracaj na to zbyt dużej uwagi, to tylko ja\nMarzę o zjedzeniu czegoś innego niż peklowana wołowina i ryby. Eh, był tu człowiek, który polował na te gigantyczne kraby. Zwykłem płacić pięć dublonów za pazur i żywić się nim przez kilka dni\nSzkoda, że myśliwy zginął... choć nie mogę powiedzieć, że to było nieoczekiwane - polowanie na te rzeczy to bardzo niebezpieczne zajęcie.";
			link.l1 = "Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Widzę, do czego zmierzasz. Tak, miłość i intrygi istnieją tutaj. A dlaczego by nie miały? Mężczyzna stworzony jest dla kobiety, a kobieta dla mężczyzny. Natura. Możesz spróbować z Gillian i Tanneke. Są młode, piękne i nie mają nic przeciwko zalotom\nZnalazłem sobie kobietę - Natalię. Jest kelnerką w tawernie Sancho. Wspaniała dziewczyna, mówię ci. Wierzę, że to jedyny powód, dla którego nie straciłem rozumu podczas pierwszych miesięcy życia tutaj. Bardzo pomogła i teraz jesteśmy razem.";
			link.l1 = "Chm... Mam to!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Dobre pytanie. Chciałbym tego, oczywiście. Ale jak o tym pomyślę... Jestem załamany. Zainwestowałem wszystko w ładunek, a mój statek zatonął. Nie mam nic na życie. Jedynym sposobem, by zarobić pieniądze, jest praca dla Holenderskiej Kompanii Zachodnioindyjskiej, jeśli mnie zatrudnią, oczywiście\nGdybym tylko miał wystarczająco pieniędzy, by kupić szkuner i wystarczające zapasy... Więc lepiej zostanę na Wyspie. Przynajmniej nie muszę tu pracować od świtu do świtu za kawałek chleba.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodziej!","Spójrz tylko na to! Ledwie się zamyśliłem, a ty postanowiłeś zajrzeć do mojej skrzyni!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tutaj tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Schowaj to, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase(" W porządku.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, byś opuścił swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, abyś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Zatem cokolwiek.","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Rozumiem.","Biorę to ze sobą.");
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
