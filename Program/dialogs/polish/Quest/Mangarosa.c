// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
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
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "Czego chcesz w moim domu?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Twoje imię to Amelia, prawda? Przyszedłem zapytać cię o jedną roślinę. Manga Rosa.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "Nie mam ci jeszcze nic do powiedzenia. Ale pewnego dnia wrócę...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "Interesujące! A któż ci o mnie powiedział, dzielny młodzieńcze?";
			link.l1 = "Jedna z twoich. Powiedziała, że znasz sekrety tej rośliny i możesz nauczyć mnie, jak zrobić z niej specjalne mikstury...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "Najpierw pokaż mi roślinę, o której mówisz. Może nie masz o niej pojęcia i tylko marnujesz mój czas. Gdzie jest twoja Manga Rosa?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Oto, spójrz.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "A co miałeś mi pokazać? Nie masz Manga Rosa. Więc wynoś się, nieznajomy, zanim się wkurzę. Ta rozmowa jest skończona.";
			link.l1 = "Ale...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "Znowu ty? Nie prowokuj kłopotów, chłopcze...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Spokojnie, Amelia. Zgubiłem to gdzieś ostatnim razem. Proszę, przyniosłem ci Manga Rosa. Spójrz.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "Zobaczmy... Wydaje się, że coś o tym wiesz. I chcesz, żebym opowiedział ci sekrety moich mikstur?";
			link.l1 = "Dokładnie. I nie za darmo, jak rozumiem...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "Rozumiesz to dobrze, młody człowieku! Nie wyglądasz na kompletnego idiotę. Cóż, mogę nauczyć człowieka, który poszukuje wiedzy i nie marnuje tej rzadkiej rośliny na bezużyteczne fajki...";
			link.l1 = "Amelio, zanim zaczniemy targowanie... czy byłabyś tak uprzejma, by opowiedzieć mi nieco podstawowej wiedzy o miksturach, które mogę zrobić z Manga Rosa?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "Nie ma targowania, kolego. Podam ci cenę, a decyzja, czy ją zapłacisz, należy do ciebie. Nie licz na targi czy rabaty, to nie jest targ. A co do twojego pytania... Możesz zrobić specjalne mikstury z Manga Rosa, które wzmocnią twoje fizyczne zdolności. Mogą uczynić cię silniejszym, bardziej wytrzymałym lub szybszym, lub mogą całkowicie zmienić twoje ciało, czyniąc cię silniejszym we wszystkich aspektach, ale taka mikstura miałaby słabszy efekt niż poprzednie dwie.";
			link.l1 = "Bardzo interesujące. Podaj swoją cenę.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "Mogę nauczyć cię trzech przepisów. Za każdy przepis proszę o jedną roślinę i pięćset złotych monet.";
			link.l1 = "Opowiedz mi więcej o tych miksturach. Co każda z nich robi?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "Musisz być mistrzem sztuki alchemii, jeśli chcesz zrobić choćby jedną miksturę. Każda mikstura działa przez dwa dni lub mniej, zależy kiedy ją wypijesz, jeśli wypijesz ją o północy, będzie działać blisko dwóch pełnych dni\nPierwsza mikstura dodaje ci siły i wytrzymałości. Będziesz lepiej walczyć, odniesiesz mniejsze obrażenia i uniesiesz większy ciężar\nDruga mikstura uczyni cię szybszym, zwinniejszym, niestrudzonym, a także poprawi twój cel\nTrzecia mikstura ma dwa razy słabsze efekty od obu poprzednich mikstur. Ale daje ci również urok, pewność siebie i szczęście\nWszystkie mikstury oparte na Manga Rosa mają pozytywny wpływ na twoje zdrowie. Musisz pić tylko jedną miksturę na raz, nigdy ich nie mieszaj, w przeciwnym razie nie przyniosą ci żadnej korzyści, przeciwnie, dostaniesz silne zatrucie\nWięc, przystojniaku, jesteś gotów zapłacić za tę wiedzę już teraz, czy potrzebujesz czasu na zastanowienie?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "Tak, jestem gotowy.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "Muszę się zastanowić. To ważna decyzja do podjęcia.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, you seem to have a knack for such things. Can you tell me if there is a demand for such stones among your people? I find them everywhere - it's like everyone is obsessed with them!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Here you go, Amelia. Just as you ordered: one hundred and thirteen adder stones.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "Ach, to ty, młodzieńcze! Czy moje mikstury ci pomogły?";
				link.l1 = "Oni naprawdę tak zrobili, Amelia. Dziękuję!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, to ty, młody człowieku! Chcesz kupić jakieś przepisy?";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "Dokładnie. Dlatego tu jestem.";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "Jeszcze nie, Amelia. Po prostu cię odwiedzam.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Bardzo dobrze. Jaki rodzaj przepisu chcesz kupić?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "Przepis na miksturę siły i wytrzymałości.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "Przepis na miksturę zwinności i niestrudzoności.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "Przepis na złożony eliksir.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Dobrze. Nazwałem go 'Tidal Wave'. Proszę, oto instrukcja. Przeczytaj ją uważnie. I nie zapomnij, jak używać jej poprawnie!";
			link.l1 = "Dzięki, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Zgoda. Nazwałem to 'Szkwał'. Proszę, oto instrukcja. Przeczytaj ją uważnie. I nie zapomnij, jak używać jej poprawnie!";
			link.l1 = "Dzięki, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Zgoda. Nazwałem go 'Morski Uścisk'. Oto instrukcja. Przeczytaj ją uważnie. I nie zapomnij, jak jej używać poprawnie!";
			link.l1 = "Dzięki, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 500 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "Bax de adder, rzeczywiście! To ma niewielką wartość, ale może być użyteczne dla tych, którzy wiedzą. Przynieś mi sto trzynaście z nich, a otworzę dla ciebie jedną z moich skrzyń.";
			link.l1 = "To cała sterta kamieni! Dlaczego najpierw nie powiesz mi, po co ci one potrzebne?";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "Nie, kochanie, jeśli musisz pytać, to ta wiedza nie jest jeszcze dla ciebie przydatna.";
			link.l1 = "A co jest w skrzyni, którą tak hojnie obiecałeś otworzyć?";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "Wiele rzeczy, przydatnych dla kapitanów, którzy nie gardzą pracą fizyczną. Nie marnuj mojego czasu, kochanieńka, i tak nie zbierzesz tylu kamyków.";
			link.l1 = "Zobaczymy o tym!";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "Ha-ha-ha! To był żart, kochanie!";
			link.l1 = "Żarty będą na twoją niekorzyść, gdy cię spalą, wiedźmo, w twojej własnej chałupie!";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "To nie mój los, kochana... Sprawiłaś, że ta cyganka jest dumna! Oto, skrzynia jest twoja do splądrowania.";
			link.l1 = "Dziękuję, Amelia. Ale naprawdę mam nadzieję, że jest tam coś pożytecznego oprócz twojej starej bielizny...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
