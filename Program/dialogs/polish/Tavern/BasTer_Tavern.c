// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Czego chcesz, "+GetAddress_Form(NPChar)+"...","To już trzeci raz, kiedy mnie niepokoisz...","Więcej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Gdzież to moja pamięć się podziała...","Tak, to naprawdę trzeci raz...","Nie, o co chodzi?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Szukam mojego starego kamrata Fernanda Luca. Mam do niego kilka pytań. Słyszałem, że miał tu naprawdę niezłą zabawę tydzień temu...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Mój przyjaciel i ja umówiliśmy się tutaj spotkać, ale nigdzie go nie widzę. Wiesz, dokąd poszedł? Czy nadal jest w mieście, czy przynajmniej na wyspie? Nazywa się Longway - jest Chińczykiem.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l1 = "Dobre wieści, "+npchar.name+". Mam coś, co uratuje twoją sytuację. Sto butelek doskonałego wina i sto butelek rumu. Z taką partią twoi goście znów będą tonąć w rzece alkoholu. Gotów zapłacić?";
				link.l1.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l1 = "No więc, "+npchar.name+", jesteś gotów omówić warunki transakcji?";
				link.l1.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l1 = "Zatem, "+npchar.name+". Z mojej strony wszystko załatwione, a towar już zmierza do tawerny. Przejdźmy do rozliczenia?";
				link.l1.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Może nadal dobrze się bawi, będąc w piekle. Twój kumpel nie żyje, więc jesteś trochę spóźniony, kapitanie. Tamten człowiek, który siedzi przy najdalszym stole, zapłacił za jego pogrzeb, chociaż mam wrażenie, że to on sam go spowodował. Ma wisielczy wyraz twarzy, jak mówią. Nazywa się Robert Martene. Jeśli chcesz, możesz podejść i zapytać go sam.";
			link.l1 = "Dzięki, kumplu. Pójdę pogadać z monsieur Robertem. Napijemy się za duszę biednego starego Luca, niech jego dusza spoczywa w pokoju...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "Co tu omawiać? On zaatakował ciebie i twojego przyjaciela, ty się broniłeś, widzę to prawie codziennie. Dobra robota. Teraz muszę tylko posprzątać bałagan...";
			Link.l1 = "Posprzątasz to, jestem pewien, że już się do tego przyzwyczaiłeś. Co o nim wiesz?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Nie za wiele, naprawdę. Pojawił się parę dni temu. Spodobało mu się tutaj, nawet wynajął dom na obrzeżach miasta. Odwiedzał często, płacił regularnie. I, co najważniejsze, przez cały ten czas zachowywał się dobrze, nigdy nie mówiąc złego słowa nikomu. Nadal jestem w szoku, że zaatakował ciebie i twojego przyjaciela\nMyślałem, że może tu osiedli się na stałe.";
			Link.l1 = "Poniekąd tak zrobił. Cóż, to niewiele, ale dzięki za to, przyjacielu. Do zobaczenia.";
			Link.l1.go = "DTSG_BasTerTavern_3";
		break;
		
		case "DTSG_BasTerTavern_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			SetQuestHeader("DTSG");
			AddQuestRecord("DTSG", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
			PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
			
			SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
			SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "To imię nic dla mnie nie znaczy, a generalnie nie wpuszczam takich ludzi do mojego przybytku, ani się nimi nie interesuję.";
			Link.l1 = "Zgoda. Dobrze, do zobaczenia później.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Och, "+GetAddress_Form(NPChar)+", sprawy mają się o wiele gorzej. Mój dostawca z Antiguy stracił destylarnię – piraci napadli, wszystko spłonęło doszczętnie. Teraz mówi, że przez najbliższe dwa miesiące ani rumu, ani wina nie będzie.";
			link.l1 = "To znajdź nowego dostawcę. Nie będziesz przecież siedział z założonymi rękami i czekał dwa miesiące?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Znalezienie dobrego dostawcy nie jest łatwe. Próbowałem dogadać się z drobnymi handlarzami, ale są oni niewiarygodni. Czasem towar przychodzi, a czasem nie. Z dużym dostawcą wszystko działa jak w zegarku — regularne dostawy i wysoka jakość.";
			link.l1 = "Skoro z typowymi dostawcami są takie problemy, może warto rozejrzeć się za tymi, którzy działają w cieniu? Zwykle nie zawodzą, a towar zawsze mają pod ręką.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Rozumiesz przecież, "+GetAddress_Form(NPChar)+", tawerna jest na widoku. Nie chcę problemów z władzami. Gdyby towar przywiózł ktoś z dobrą reputacją, nie tylko kupiłbym partię, ale też przymknąłbym oko na jego pochodzenie\nW końcu, gdy problem jest naprawdę poważny, kto zwraca uwagę na takie drobiazgi? Najważniejsze, by nie wzbudzać podejrzeń. Ale na dłuższą metę chcę współpracować tylko z poważnymi i uczciwymi kupcami.";
			link.l1 = "Rozumiem. Cóż, może jeszcze do ciebie zajrzę. Każdy problem da się rozwiązać, jeśli podejść do niego z głową.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Kapitanie, to po prostu niesamowite! Jak wam się to udało? Choć właściwie to nieważne. Lepiej powiedzcie, czego chcecie za tak luksusową partię alkoholu? I czy wszystko będzie w porządku z dokumentami?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Z dokumentami? Oczywiście, wszystko w najlepszym porządku. Nie zamierzacie ich przecież sprawdzać?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("Test honoru zaliczony", "None");
			}
			else
			{
				link.l1 = "Z dokumentami?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("Zbyt niski poziom honoru! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;

		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Kapitanie, zrozumcie, że zdobycie tej partii alkoholu jest dla mnie sprawą życia i śmierci. Ale wolność i reputacja są dla mnie równie cenne. Gubernator jest bezlitosny wobec przemytników, nawet tych najmniejszych. Gdybyście mieli lepszą opinię, przymknąłbym oko na brak dokumentów, ale teraz... przyciągacie zbyt wiele niepotrzebnej uwagi...";
			link.l1 = "Wygląda na to, że czas zabrać się za dobre uczynki. Poczekajcie na mnie, wkrótce wrócę.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "Tym razem uwierzę wam na słowo. A więc, ile chcecie za tę partię?";
			link.l1 = "Za każde dziesięć butelek wina chcę trzydzieści dubloonów, za rum – pięć. Cała partia to sto butelek rumu i tyle samo wina, czyli razem trzysta pięćdziesiąt dubloonów.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Zaraz, kapitanie! Toż to rozbój w biały dzień! Tak, moja sytuacja jest naprawdę trudna, ale nie będę działać na własną niekorzyść!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Mogę dać wam zniżkę. Ale to nie wszystko. Chcę zostać waszym stałym dostawcą. Gwarantuję brak opóźnień. Wynajmę magazyn w Basse-Terre i towar będzie dostarczany stamtąd bez zwłoki. Alkohol zawsze będzie w zapasie, by zapobiec wszelkim niedoborom. A co do ceny – zniżka sprawia, że partia wyniesie was tylko 240 dubloonów. Co wy na to?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("Test umiejętności zdany", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Cóż, mogę zejść z ceny do dwustu czterdziestu dubloonów za partię, ponieważ zależy mi na długoterminowej współpracy. W przyszłości będę w stanie całkowicie zaspokoić wszystkie wasze potrzeby i zapewnić nieprzerwane dostawy. Co wy na to?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Niewystarczający poziom umiejętności (50)", SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "To wciąż więcej niż płaciłem wcześniej. Ale nauczyłem się, że stabilność jest cenniejsza. Zgadzam się na wasze warunki, ale pamiętajcie – jedno potknięcie i znajdę innego dostawcę. Muszę wiedzieć, za co płacę więcej. I jeszcze jedno – jak zamierzacie rozwiązać sprawę z władzami wyspy?";
			link.l1 = "Zajmę się tym natychmiast. Gdy wszystko zostanie załatwione, wrócę z towarem.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Proszę, nie zwlekajcie. Nie mogę się doczekać, aż moje kufle znów będą pełne.";
			link.l1 = "Nie martwcie się, nie każę wam długo czekać.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "TPZ_Tavern2_7":
			dialog.text = "To wciąż zbyt drogo, kapitanie. Ta cena jest wyższa niż u mojego poprzedniego dostawcy. Nawet jeśli teraz się zgodzę, za kilka miesięcy i tak będę musiał wrócić do niego, gdy wznowi produkcję. Nie widzę powodu, by przepłacać.";
			link.l1 = "Rozumiem. Dobrze. Moja ostateczna oferta to dwieście dubloonów. Jeśli to wam nie odpowiada, nie ma sensu kontynuować rozmowy.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Dobrze, zgoda. Dwieście mi odpowiada. Ale powiedzcie, jak zamierzacie uregulować sprawę z władzami wyspy? Jak już wspominałem, gubernator bardzo pilnuje porządku i nie toleruje transakcji pod swoim nosem.";
			link.l1 = "Ha-ha, z tym bym się spierał. Ale możecie być spokojni – wszystkie biurokratyczne formalności załatwię w możliwie najkrótszym czasie.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Proszę, nie zwlekajcie. Moi goście nie mogą się już doczekać, kiedy ich kufle znowu się napełnią.";
			link.l1 = "Nie martwcie się, nie każę wam długo czekać.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Oczywiście, kapitanie! A więc, ile chcecie za swoją partię?";
				link.l1 = "Za każde dziesięć butelek wina chcę trzydzieści dubloonów, a za rum – pięć. Cała partia to sto butelek rumu i tyle samo wina, razem daje to trzysta pięćdziesiąt dubloonów.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("Test honoru zdany", "None");
			}
			else
			{
				dialog.text = "Przykro mi, kapitanie, ale wasza reputacja wciąż pozostawia wiele do życzenia.";
				link.l1 = "Cholera...";
				link.l1.go = "exit";
				notification("Zbyt niski poziom honoru! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Oczywiście, kapitanie! 240 dubloonów, jak się umawialiśmy. Proszę!";
				link.l1 = "Miło z wami handlować! W waszej tawernie znowu będzie rzeka rumu i wina.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Oczywiście, kapitanie! 200 dubloonów, jak się umawialiśmy. Proszę!";
				link.l1 = "Miło z wami handlować! W waszej tawernie znowu będzie rzeka rumu i wina.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "Jesteście moim wybawcą, kapitanie! Będę oczekiwał takich samych partii co dwa tygodnie. Mam nadzieję, że będziecie trzymać się umowy. Kolejnej suszy moja tawerna nie przetrwa...";
			link.l1 = "Nie martwcie się, "+npchar.name+". Mój przedstawiciel w mieście – Christian Delouche – będzie pilnował, żeby w waszej tawernie nie zabrakło rumu i wina.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian? Znam go, to odpowiedzialny człowiek, choć wydaje się... Zresztą, nieważne. Skoro wszystko załatwiliście z władzami, mogę mu zaufać.";
			link.l1 = "To dobrze. A teraz proszę wybaczyć – muszę załatwić jeszcze jedną sprawę w mieście.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Odwiedzajcie nas częściej!";
			link.l1 = "Z pewnością.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
