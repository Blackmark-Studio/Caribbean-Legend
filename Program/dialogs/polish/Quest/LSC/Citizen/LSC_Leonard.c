// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zmykaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Przyjacielu, jesteś tu właśnie na czas... Chcę z tobą porozmawiać... o interesach. Ważnych interesach.";
				link.l1 = "Naprawdę? Wygląda na to, że nie jesteś pijany. Czy coś się stało? To niezwykłe widzieć cię trzeźwego.";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Witaj, druh...";
				link.l1 = TimeGreeting()+"Wygląda na to, że już ci wystarczy, kolego.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! Hik! Czego chcesz?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak ci się wiedzie. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Tak! Wystarczy? N-nie! Jestem szalonym pijakiem, hi-hic! Tak, Leonard Musket jest pijany i to jest w porządku!";
			link.l1 = "Lubisz napitki, co? Tak, nazywam się "+GetFullName(pchar)+"Miło cię poznać.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Skoro tak mówisz. My wszyscy tutaj... hic, spotykamy się nawzajem.";
			link.l1 = " Dobrze, wygląda na to, że nie masz ochoty rozmawiać. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "Tak, kumplu, prawie jestem trzeźwy. A to dlatego, że mam dla ciebie interes, ważny interes. I wygląda na to, że ty możesz to załatwić...";
			link.l1 = "Co? Co ci chodzi po głowie? Mów i nie marnuj mojego czasu na nic!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Kumpel, chcesz zarobić trochę pieniędzy? Srebrne peso, złote dublony? Powiem ci jak. Ale będziesz musiał się podzielić ze mną - będziemy współpracować.";
			link.l1 = "Zawsze chcę. Ale wszystko zależy od twojej propozycji: nie podejmuję się żadnej pracy, nawet jeśli jest bardzo dochodowa.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "Interes nie jest zupełnie legalny, pewnie, ale jest dochodowy... i będziemy w stanie ukarać człowieka, który stał się zbyt wybredny. Nie zbiednieje, ma za dużo pieniędzy. Wszyscy się z nim dzielą, więc teraz jego kolej, by postąpić tak samo. Powiedz mi, radzisz sobie z rumem? Ile jesteś w stanie wypić, zanim padniesz pod stół?";
			link.l1 = "To zależy. Nie jestem pewien, czy mam zwyczaj szalonego picia... Czy w końcu zdradzisz mi szczegóły?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "Przechodzę do sedna, tylko jeszcze tego nie widzisz. Dobrze. Będę konkretny. Na Wyspie jest tłusty, brzydki drań - Giuseppe Fazio. Rzadki łajdak. Obdziera ze skóry Narwale, Rivados i miejscowych. Obserwuję go od jakiegoś czasu i w końcu mam coś\nW jego kabinie w Karolinie są dwie skrzynie: pierwsza zawiera papiery, druga złoto i srebro. Obie są zamknięte na różne klucze. Gruby zawsze trzyma klucze przy sobie.";
			link.l1 = "Cóż, wygląda na to, że zamierzasz okraść Fazio? Nie wezmę w tym udziału. I lepiej się ciesz, że nikomu o tym nie powiem. Jeśli chcesz sprawdzić skrzynię grubasa, powinieneś znaleźć innego wspólnika.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha!   Interesujące!   Kontynuuj...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "To źle, naprawdę źle... Jest tu dużo złota, wystarczająco dla nas obu. Dobrze, do zobaczenia wkrótce...";
			link.l1 = "Żegnaj.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Do jego kajuty prowadzą dwa drzwi. Jedne z nich są zawsze zamknięte. Ale klucz, który otwiera skrzynię ze złotem, otwiera także drzwi. Nie wiem, jaki jest w tym wszystkim sens, ale to fakt. Potrzebujesz tylko jednego klucza, aby otworzyć kajutę i zdobyć złoto. Kolejne logiczne pytanie - jak zdobyć klucz? Więc mam plan\nDoskonały plan, jeśli się uda, Fazio nigdy nie zorientuje się, co się stało i kogo obwiniać. Pomyślą, że to był tajemniczy złodziej. Problem w tym, że potrzebuję partnera z żelazną głową, aby to zrobić. Czy nadążasz?";
			link.l1 = "Słucham. Mów dalej.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio uwielbia przesiadywać u Sancho i nieźle sobie popić, ale jego tusza jest zbyt ciężka, by rum mógł zadziałać. Więc wymyślił grę alkoholową - grę, w której ludzie próbują go przepić. Jeśli zaproponujesz mu tę grę, bez wątpienia się zgodzi\nA potem zaczyna się zabawa. Zakładasz się z nim, idziesz do tawerny, chwytasz rum i pijesz, aż któreś z was nie całuje stołu. Jeśli się poddasz, cały plan upada, nie dam rady zrobić tego sam\nDlatego zapytałem o Twoją głowę. Jeśli sprawisz, że Fazio będzie piszczeć i chrząkać jak świnia, to uznaj, że załatwione. Będę cały czas w pobliżu. Kiedy skończy, zabiorę jego klucze\nPotem przenosimy grubasa do łóżka na górze i zakradamy się do jego kabiny, gdy będzie spał. Zwrócę klucz zaraz po tym, jak obrabujemy jego skrzynię, nawet nie zauważy, że został okradziony\nJa zajmę się zdobyciem i zwrotem klucza, twoim zadaniem jest upić Fazio i zakraść się do jego majątku. Będę stał na straży, gdyby ktoś się pojawił, więc będziesz miał wystarczająco dużo czasu, by uciec tylnymi drzwiami\nPodzielimy zawartość skrzyni po połowie, to będzie uczciwe. Więc, jesteś w?";
			link.l1 = "Świetny plan! Pewnie, spróbujmy!";
			link.l1.go = "facio_6";
			link.l2 = "Nie, przyjacielu. Odpuszczam. Obawiam się, że nie będę w stanie tyle wypić, aby utrzymać się na nogach i przewyższyć Fazio. Znajdź sobie innego partnera, trochę silniejszego ode mnie.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Jestem zadowolony, że miałem rację co do ciebie. Teraz idź do Fazio i zorganizuj spotkanie w tawernie wieczorem po dziewiątej. Mam nadzieję, że przepijesz tę świnię. Powodzenia i do zobaczenia wieczorem!";
			link.l1 = "Spróbuję... Żegnaj!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Druhu, liczę na ciebie. Przy drinku ten gruby człowiek...";
			link.l1 = "Z pewnością...";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "Zrobione, ten tłusty wieprz śpi na górze. Mam klucz. Dobrze ci idzie, wydajesz się wystarczająco trzeźwy!";
			link.l1 = "Naprawdę? Minęło sporo czasu odkąd byłem tak pijany. Czuję się trochę skołowany... Ruszamy?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "Zrobione, ten tłusty wieprz śpi na górze. Mam klucz. Dobrze ci idzie, naprawdę udało ci się przepić tego prosiaka...";
			link.l1 = "Tak, ale minęło dużo czasu, odkąd byłem tak pijany. Głowa mi się kręci... No, to idziemy?";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, kumplu, nie udało ci się przepić grubasa... Szkoda. Cóż, przynajmniej spróbowaliśmy...";
			link.l1 = "Ch-cholera, on jest jak jakaś... b-b-bezdenna beczka. Argh, muszę o-odpocząć... To koniec, z-zjeżdżaj! Hic!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Tak. Chodźmy! Podążaj za mną do 'Karoliny'! I nie włócz się, nie mamy dużo czasu!";
			link.l1 = "Ruszajmy!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Proszę. Weź klucz. Skrzynia, której potrzebujesz, jest po lewej stronie od wejścia. Weź tyle, ile możesz szybko. Nie zapomnij zamknąć jej z powrotem. Jeśli coś zobaczę, zapukam do drzwi trzy razy. W takim przypadku uciekaj przez tylną galerię.";
			link.l1 = "Dobrze. Bądź czujny!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable loot... And were we risking for it? Eh... Fine, let's share what we have got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there will be much more... Risk wasn't worth it. Eh... Fine, let's share what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought that we will get more. Fine, let's share it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We have done well, partner! This is a whole lot of coins! Let's share!";
						else
						{
							sTotalTemp = "Wow! I haven't ever thought that the fat man's stash is so huge. Well done, partner! Let's share!";
						}
					}
				}
			}
			dialog.text = "Nareszcie! Co udało ci się zabrać z kufra tego łotra? Pokaż mi, czekam z niecierpliwością!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "Nie było niczego. Tylko kilka strzępów, amuletów i tym podobnych rzeczy.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "Zabrałem z kufra "+sPeso+" i "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Niemożliwe! Wygląda na to, że wszystko to było na darmo... Może ten drań ukrył swoje skarby w innym kufrze. Eh! Dobra, daj mi klucz, a ja go zwrócę właścicielowi, zanim się zorientuje, że go brakuje. Żegnaj, kumplu...";
			link.l1 = "... ";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Podzielmy się...";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Dobrze, daj mi klucz, a ja go zwrócę właścicielowi, zanim ten go zauważy. Żegnaj, druh...";
			link.l1 = "Powodzenia, druh...";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone has cleaned out his chest. It seems that the mysterious thief did that.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Have you heard? Fazio was robbed! He was robbed while being drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your own feet! That 's something...", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Naprawdę?... hic! Słucham...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak tu trafiłeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Czy zawsze pijesz? I gdzie znajdujesz monety na napitki?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Co możesz mi powiedzieć o miejscowych?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy chciałbyś opuścić to miejsce i udać się na kontynent?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Wybacz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Tak! Przysięgam, nie pamiętam. Tak, tak, nie pamiętam! To było dawno temu. Płynąłem gdzieś jakoś i w końcu tu wylądowałem. Hic!";
			link.l1 = "Hm... Dobrze, dobrze.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Tak, jestem pijakiem... Piję, cholera, bo nie mam już nic do roboty... Widzisz, kumplu, jestem skończony. Butelka rumu to jedyne, czego chcę. Więc będę pił dalej. A pieniądze... he-he, rum nie kosztuje dużo. Zresztą, nawet nie muszę go kupować.\nJest miejsce pełne rumu, ale musisz pływać, jeśli chcesz go zdobyć, dlatego kupuję rum tylko wtedy, gdy jestem zbyt pijany, by pływać... hik! Jizjezezejizeze, nie, nie powiem ci, gdzie pływać, he-he, nawet nie pytaj...";
			link.l1 = "Cudownie.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Co mogę powiedzieć, hic... o nich? Dobrzy ludzie do pogadania i do picia. Giuseppe Fazio to taki ważny człowiek, miejscowy notabl, jego skrzynie są wypełnione złotem... a mimo to szanuje starego Leo, stawia mu drinki w tawernie. Chociaż czasem też prosi o coś w zamian, ale to nic, hic!\nHeh, nie wiesz, ile dublonów ma Fazio, aha-ha-ha! Wystarczająco, żeby spędzić resztę życia w najlepszym domu na całych Karaibach, nie pracując i pijąc najlepszy rum na świecie. Ale on zostaje tutaj, na Wyspie. Wciąż wydaje się, że nie ma dla niego wystarczająco pieniędzy...";
			link.l1 = "Zrozumiano...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Opuszczać? Hic! Dlaczego? Nie, nie chcę iść ani na ląd, ani na biedną wyspę. Czy jest jakiś darmowy rum? Nie! Nie ma żadnego darmowego rumu, hic! A to znaczy, że nie mam tam nic do roboty... Przyjacielu, czuję się tutaj dobrze. Powiem ci więcej - zapytaj ludzi, czy chcą opuścić to miejsce. Nikt nie chce, oprócz dwóch czy trzech, hic!";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co ty tam robisz, co? Złodziej!","Spójrz tylko na to! Ledwie pogrążyłem się w rozmyślaniach, a ty postanowiłeś sprawdzić moją skrzynię!","Postanowiłeś zajrzeć do moich skrzyń? Nie ujdziesz z tym na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Niemądra dziewczyna!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. Denerwuje mnie to.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż to, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę, byś opuścił swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, żebyś schował swoją klingę.");
				link.l1 = LinkRandPhrase("W porządku.","Dobrze.","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bądź ostrożny, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z gotową bronią. Przeraża mnie to...");
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
