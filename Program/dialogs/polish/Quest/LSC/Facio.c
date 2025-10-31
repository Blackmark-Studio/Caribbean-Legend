// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

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
				dialog.text = "Cześć, cześć... Czy jesteś tutaj nowy? Nie przypominam sobie twojej twarzy. Pozwól, że się przedstawię - jestem Giuseppe Fazio, specjalistą w rozwiązywaniu problemów na tej małej wyspie.";
				link.l1 = TimeGreeting()+", Mam na imię "+GetFullName(pchar)+"Masz rację, jestem tu nowy. Wybacz moją ciekawość - ale jakie problemy rozwiązujesz?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, to znowu ty, drogi "+pchar.name+"! Co cię sprowadza do mego skromnego domu?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, mam poważny konflikt z jednym klanem. Muszę rozwiązać ten problem.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, szukam człowieka o imieniu Adolf Barbier. Powiedziano mi, że niedawno piłeś z nim w tawernie...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, mówią, że jesteś całkowicie odporny na trunki. Nieważne, ile wypijesz, nadal stoisz na nogach.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Jestem gotów zagrać w twoją grę. Oto moja stawka.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Chcę znać aktualne hasło klanów, by wejść na ich terytoria.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?"," Czy na wyspie wydarzyło się coś nowego?","Czy opowiesz mi najnowsze plotki?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Nic szczególnego, Giuseppe. Po prostu chciałem cię zobaczyć.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Wszelakie, moja droga, wszelakie. Na przykład, łagodzę sytuacje między admirałem a klanami. Jak zapewne już wiesz, Riwados, Narwale i admirał są wzajemnymi wrogami. Działam jako mediator, gdy sprawy się komplikują.\nPoza tym, często pełnię rolę neutralnej strony, gdy admirał sprzedaje zapasy klanom. Ale to tylko niewielka część mojego interesu. Więc jeśli masz problemy z Riwados lub Narwalami - nie wahaj się poprosić o moją pomoc, zobaczymy, co da się zrobić.";
			link.l1 = "Dobrze. Rozważę to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Jaki klan?";
			link.l1 = "Narwale.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivodosi.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Chcesz zobaczyć Donalda Greenspana, mam rację?";
			link.l1 = "Zgadza się. Czy znasz hasło?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Chcesz zobaczyć Czarnego Eddiego, prawda?";
			link.l1 = "Coś w tym stylu. Więc znasz hasło?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Pewnie! Ale pozwól, że najpierw podam ci kilka szczegółów. Hasła zawierają tylko jedno słowo i zmieniają się co tydzień. Co siódmego, czternastego, dwudziestego pierwszego i dwudziestego ósmego dnia miesiąca\nWięc zwracaj uwagę na aktualną datę, aby uniknąć błędów. W końcu, jak musisz zrozumieć, to nie jest działalność charytatywna. Pięćdziesiąt dublonów za hasło. Pamiętaj, tylko dublony.";
				link.l1 = "Pięćdziesiąt doblonów? To ogromna suma!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Oczywiście, chłopcze. Znasz cenę. Masz pięćdziesiąt dublonów?";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "Tak. Weź swoje monety.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Niestety, nie wiem. Może później...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Cóż, cóż, mój chłopcze, uspokój się. Nie bądź chciwy, uwierz mi: znam prawdziwą cenę moich informacji. Nie zamierzasz po prostu chodzić po statkach "+pchar.questTemp.LSC.parol+" prawda? Prawda. Więc musisz być gotowy stracić trochę monet... Zatem, jesteś gotowy zapłacić pięćdziesiąt dublonów?";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "Tak. Weź swoje monety.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Nie mam niestety takich pieniędzy. Może później...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "Świetnie! Miło było robić z tobą interesy. Obecne hasło do "+pchar.questTemp.LSC.parol+" jest: '"+sTotalTemp+"Pamiętaj to dobrze i nie popełnij błędu, bo nie dam ani grosza za twoje życie.";
			link.l1 = "Wiem, wiem... Dzięki!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ach, ależ oczywiście, mój dobry, stary Adolfo! Tak, rozmawiałem z nim. Widzisz, mój drogi, cieszyłem się, że odzyskałem moje pieniądze, pieniądze, które myślałem, że już nigdy nie zobaczę! Adolfo pożyczył dużą sumę pod zastaw swojego znakomitego karabinu i miał problemy z oddaniem mi pieniędzy\nStraciłem wszelką nadzieję na ich odzyskanie i zamierzałem sprzedać ten sztucer naszemu ukochanemu Axelowi Yostowi. Ale nagle drogi Adolfo przyniósł mi moje złoto! Okazało się, że udało mu się zdobyć wystarczająco monet nie tylko na wykupienie swojego sztucera, ale także na zakup kabiny Sessile Gallard na dziobie 'Santa Florentina'!\nOczywiście, to znacznie lepsze niż życie w półzatopionym ładowni\nDlatego Adolfo odzyskał swój karabin, nowy dom, a ja mam swoje pieniądze. Dlaczego miałbym odmówić wypicia z nim, zwłaszcza gdy on stawiał?";
			link.l1 = "Ach, pewnie! Miałeś wiele rzeczy, za które można pić. I to za darmo... Dzięki, Giuseppe, bardzo mi pomogłeś. Teraz wiem, gdzie znaleźć Adolfa.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Zawsze z przyjemnością, drogi. Ale nie szukaj Adolfa w jego kajucie, dopóki nie nadejdzie wieczór, jest bardzo zajęty, kręci się w sprawach... Tak, i odwiedzaj mnie częściej, pogadajmy!";
			link.l1 = "Zaproszę cię, gdy będę miał własną kajutę... Żegnaj i powodzenia!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Ah? Dlaczego włamujesz się do mojego miejsca, jakby tu był pożar? Kim myślisz, że jesteś??";
					link.l1 = "Twoja sprawiedliwość... trucicielu!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Wybacz mi! Przysięgam, zmusili mnie! Przystawili mi pistolet do...";
					link.l1 = "Zamknij się. Wiem to. Gdzie jest ten ostatni drań? Gdzie jest Marcello Cyklop?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Przysięgam, zmusili mnie! Już wszystko powiedziałem admirałowi! Nie mogłem im się oprzeć, oni by...";
					link.l1 = "Zamknij się. Wiem to. Gdzie jest ten ostatni drań? Gdzie jest Marcello Cyklop?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "Co... co powiedziałeś?";
			link.l1 = "Wiem wszystko, łotrze. Pracowałeś z Chadem Kapperem. Przyniosłeś beczkę zatrutego rumu do admirała. Teraz módl się, nędzny łajdaku...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Poczekaj! Zatrzymaj się! Oszczędź mnie! Przysięgam, zmusili mnie! Mieli broń przy mojej...";
			link.l1 = "Zamknij się. Wiem o tym. Gdzie jest ostatni drań? Gdzie jest Marcello Cyklop?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Ja... ja... ja nie wiem!";
			link.l1 = "Kłamiesz, ścierwo! Widzę to. Gdzie jest Cyklop?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "On... on otrzymał jakiś rozkaz od Kappera i odszedł. Nie wiem, gdzie jest!";
			link.l1 = "Kłamiesz znowu. Wiesz wszystko. Nie bądź tchórzem, ty plugawa kreaturo - Kapper nie żyje i nie zrobi ci krzywdy. Ale jeśli mi nie powiesz, gdzie jest Marcello - zarżnę cię jak świnię teraz! Co Chad rozkazał Cyklopowi?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Wysłał go, by zabił... Czerwoną Mary.";
			link.l1 = "Co?! Mów natychmiast, jak on zamierza to zrobić? To niemożliwe, by dostać się do jej kabiny! Jak on planuje ją zabić?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "On dostanie się do kabiny Jurgena, gdy kowal będzie poza nią. Potem przejdzie do dna ładowni, przekroczy ją i dotrze do kabiny Mary\nPotem pozostaje mu tylko poczekać, aż dziewczyna odwróci się plecami lub zaśnie. Tak mi powiedział Chad. Nic więcej nie wiem, przysięgam!";
			link.l1 = "To wystarczy. Kiedy on poszedł? Kiedy, pytam cię, Cyklop poszedł do 'Kuźni Ceres'?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "On musi już być w kajucie Jurgena... albo schodzić do ładowni...";
			link.l1 = "Cholera! Nie mam czasu pływać wokół Wyspy! Powiedz mi hasło do statków Narwali! Mów, a jeśli mnie okłamiesz, i tak przeżyję, ale ty na pewno zginiesz!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "Zrozumiano. Teraz módl się, by dziewczyna przeżyła.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Powiedziałem już wszystko, co wiedziałem! Przysięgam!";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "On... On jest gdzieś wewnątrz 'Fleron'. Chad kazał mu tam się ukryć i czekać na kolejne rozkazy.";
			link.l1 = "Rozumiem. Lepiej, żeby to była prawda...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Czyżby? Cóż, mój chłopcze, który klan cię niepokoi?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narwale.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "Piratów admirała.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Nic takiego. Żartowałem, Giuseppe, wszystko w porządku.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "No cóż, to właściwie nie konflikt, tylko małe nieporozumienie, he-he. "+sti(npchar.quest.price)+"  dublony i twój problem zostanie rozwiązany w ciągu dnia.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Oczywiście, słyszałem o tym. Narobiłeś niezłego bałaganu, mój drogi. Ale jest na to sposób. "+sti(npchar.quest.price)+" dublony i twój problem zostanie rozwiązany w ciągu dnia.";
				else dialog.text = "Cała Wyspa jest świadoma rzezi, którą popełniłeś. Nie będzie łatwo ci pomóc, ale jest szansa."+sti(npchar.quest.price)+" dubloonów i spróbuję rozwiązać twój problem.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Masz tutaj swoje monety i zajmij się tym.";
				link.l1.go = "pay";
			}
			link.l2 = "Niestety, nie mam przy sobie wystarczającej ilości dublonów w tej chwili. Ale przyniosę je później i porozmawiamy ponownie.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "„Cóż, to nie jest właściwie konflikt, tylko małe nieporozumienie, he-he.”"+sti(npchar.quest.price)+"  dublony i twój problem zostanie rozwiązany w ciągu dnia.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Jasne, słyszałem o tym. Narobiłeś niezłego bałaganu, mój drogi. Ale jest wyjście. "+sti(npchar.quest.price)+"  dublony i twój problem zostanie rozwiązany w ciągu dnia.";
				else dialog.text = "Cała Wyspa jest świadoma rzezi, której dokonałeś. Nie będzie łatwo ci pomóc, ale jest szansa."+sti(npchar.quest.price)+"  дублоны, a spróbuję rozwiązać twój problem.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Proszę, weź swoje monety i zajmij się tym.";
				link.l1.go = "pay";
			}
			link.l2 = "Niestety, nie mam teraz przy sobie wystarczającej liczby dublonów. Ale przyniosę je później i porozmawiamy ponownie.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Cóż, to właściwie nie konflikt, tylko małe nieporozumienie, he-he. "+sti(npchar.quest.price)+"  дублоны, a twój problem będzie rozwiązany w ciągu dnia.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Oczywiście, słyszałem o tym. Niezły zamęt narobiłeś, mój drogi. Ale jest wyjście."+sti(npchar.quest.price)+"  dubloony i twój problem zostanie rozwiązany w ciągu dnia.";
				else dialog.text = "Cała Wyspa wie o rzezi, którą uczyniłeś. Nie będzie łatwo ci pomóc, ale jest szansa. "+sti(npchar.quest.price)+"doblony i spróbuję rozwiązać twój problem.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Proszę, weź swoje monety i załatw to.";
				link.l1.go = "pay";
			}
			link.l2 = "Niestety, nie mam teraz przy sobie wystarczającej liczby dublonów. Ale przyniosę je później, i porozmawiamy ponownie.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "Wspaniale. Teraz usiądź i odpocznij. Lepiej zostań w mojej kajucie, dopóki nie rozwiążę twojego problemu. Nie chcę, abyś go jeszcze pogorszył, mój drogi.";
			link.l1 = "Dobrze...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Chodź, chłopcze! Kłamią, wszyscy kłamią, he-he. Moja głowa jest tylko trochę twardsza niż przeciętna głowa, ale jestem człowiekiem tak jak ty, więc też upijam się rumem. Ludzie piją rum, żeby się upić, to jego jedyny cel. Czy kiedykolwiek o tym myślałeś, drogi?";
			link.l1 = "Całkiem prawda.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Chcesz zagrać ze mną w zabawną grę? Nazywa się 'pić do dna!', ha-ha! Jestem pewien, że już o niej słyszałeś. Czy mam rację?";
			link.l1 = "Tak, były jakieś szepty na ten temat... Nazwałbym to 'twarz na stole'.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ha-ha-ha, mój drogi chłopcze, rozbawiłeś starego człowieka, cóż mogę powiedzieć! 'Twarz na stole!' Zapamiętam to... Więc co powiesz? Zagramy o sto dublonów?";
			link.l1 = "Sto doublonów?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Tak, a przegrany płaci za drinki. Umowa?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "Tak, umowa stoi. Oto moja stawka.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hm. Nie mam tylu dubloonów.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Cóż, przyjdź do mnie, gdy je będziesz miał, a zagramy!";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Doskonale, mój drogi! W takim razie spotkajmy się o dziewiątej wieczorem w tawernie Sancho! Tak, twoja stawka zostanie u mnie, jeśli się spóźnisz, to jedna z zasad. Ale nie spóźnisz się, chłopcze, prawda?";
			link.l1 = "Oczywiście, Giuseppe. Szykuj się na walkę na butelki!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "I ty, i ty, mój drogi! Twarzą na stół! Ha-ha!";
			link.l1 = "Do zobaczenia o dziewiątej w tawernie!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Cóż, mój drogi, jesteś gotów pocałować stół, he-he? Dobry Sancho już przyniósł nam rum. Nie muszę chyba tłumaczyć zasad, prawda? Są dość proste: pijemy tę samą butelkę, aż jeden z nas padnie.\nTak, możemy rozmawiać, powinniśmy rozmawiać! Rozmowa z przyzwoitymi ludźmi to wspaniała rzecz, prawda? A jeśli wygrasz, możesz odebrać swoją nagrodę od Sancho. Gotów?";
			link.l1 = "Rzekłbym tak. Zaczynajmy, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Piętna-astu l-ludzi na martwym... hic! Aha! Jo-ho-ho-kha... I... butelka...";
			link.l1 = "Wspaniałe...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
