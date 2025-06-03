// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę pomóc?"),"Próbowałeś mi zadać to pytanie niedawno...","Tak, pozwól, że zgadnę... Znowu kręcisz się w kółko?","Słuchaj, to ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili o czym rozmawiać."),"Umph, gdzie podziała się moja pamięć...","Zgadłeś, przykro mi...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Spójrz na te kolczyki, monsieur. Znalazłem je w kieszeni bandyty w dżungli. To z pewnością dzieło wykwintnego jubilera, który, jestem pewien, nie pochodzi z tej dziczy. Co powiesz?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Wiem, że masz dłużnika o imieniu Folke Deluc. Powiedz mi, jak źle z jego... zaległościami?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Przychodzę w sprawie długu Folke Deluca.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Zakończyłem twoje zlecenie, monsieur. Oto twój... hiszpański przyjaciel.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Przyszedłem w sprawie...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "Czy przyniosłeś 100 doublonów?";
				if (PCharDublonsTotal() >= 100)
				{
					link.l1 = "Oto twoje pieniądze za mojego oficera...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "Nie, wciąż się zastanawiam.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "A dlaczego cię to obchodzi, mogę zapytać?";
			link.l1 = "Potrzebuję, aby ten człowiek był wolny, a nie za kratami. I o ile mi wiadomo, dopóki ten dług nie zostanie spłacony, nie zostanie uwolniony. Jestem zainteresowany spłatą tego długu.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, to zmienia wszystko. Jestem też zainteresowany, żeby moje pieniądze do mnie wróciły... Ten Folke Deluc to dziwny osobnik. Pożyczył stosunkowo niewielką kwotę - pięć tysięcy pesos. Po prostu nie chciał jej oddać i zaczął się ukrywać. W końcu odsetki wzrosły do ceny oryginalnego długu i znalazł się za kratkami.";
			link.l1 = "Z tego wynika, że jego dług wynosi obecnie dziesięć tysięcy?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Dziesięć tysięcy czterysta pięćdziesiąt pesos dokładnie, monsieur. Tak więc jego wolność kosztuje tyle. Jesteś gotów zapłacić mi tę sumę? Jestem nieco zaskoczony...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Nie bądź zdziwiony. Oto pieniądze.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... Rzeczywiście, pokaźna suma. Posłuchaj, monsieur, może powinniśmy spróbować się dogadać? Na przykład, masz coś, czym mógłbym się zająć, a ty mógłbyś ocenić moją przysługę na te dziesięć tysięcy pięćset...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Tak, wydaje się, że naprawdę potrzebujesz tego żeglarza, skoro jesteś gotów wyłożyć taką sumę pieniędzy za niego. W każdym razie, to nie moja sprawa, prawda, monsieur? Oto jego weksel, teraz masz prawo do jego długu i masz prawo żądać od niego pieniędzy. No i oczywiście, wystąpić o jego zwolnienie z więzienia.";
			link.l1 = "Dokładnie tego chciałem. Do widzenia, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "Przysługa? Niestety, nie potrzebuję żadnych przysług od ciebie. Przynajmniej na razie.";
			link.l1 = "Szkoda. Powinienem wtedy przynieść pieniądze dla Folke. Do widzenia!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Przysługa? Hm... Wiesz, monsieur, wczoraj odpowiedziałbym przecząco, ale teraz... tak, mam coś, czym trzeba się zająć, ale ostrzegam, że jest to dość niebezpieczne.";
			link.l1 = "Niebezpieczne dla czego?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Oczywiście, dla twojego cennego życia. Więc zastanów się, zanim się zgodzisz i zdecyduj, czy jesteś gotów coś takiego zrobić, czy nie.";
			link.l1 = "Panie, niebezpieczeństwo nie jest mi obce. Już tyle razy byłem w groźnych sytuacjach. Przejdźmy więc do szczegółów. Dopóki nie chodzi o samodzielne wyeliminowanie całego garnizonu fortu, być może będę w stanie dokonać tego, do czego tak tajemniczo nawiązujesz.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Zgoda. Posłuchaj więc. Dziś wieczorem kilku piratów i więzień opuszczą piracką kryjówkę Le Francois i udadzą się do zatoki Le Marin. Więzień jest hiszpańskim oficerem i wielkim ekspertem w dziedzinie inżynierii fortyfikacyjnej. Brytyjczycy zamierzają wykorzystać go do swoich celów, więc wyślą okręt wojenny, by zabrać go z zatoki.\nOficer jest moim starym przyjacielem i nie chcę, by skończył jako angielski jeniec. Nie mogę prosić lokalnych władz o pomoc, ponieważ jesteśmy w stanie wojny z Hiszpanią. Gdybym miał więcej czasu, zatrudniłbym ludzi zdolnych do odbicia Hiszpana... przepraszam, do odbicia mojego przyjaciela, ale niestety!\nJesteś jedynym człowiekiem, któremu mogę powierzyć to zadanie. Musisz udać się do zatoki Le Marin i... przekonać piratów, by oddali ci więźnia. Wątpię, by okazali wiele współpracy, więc to zależy od ciebie.";
			link.l1 = "Ilu piratów będzie w konwoju?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Nie wiem. Może dwie osoby, może trzy lub cztery. Więc, co byś powiedział?";
			link.l1 = "Już ci mówiłem, że 'nie boję się niebezpieczeństwa' i wiem, z której strony trzymać miecz.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Hm. Masz rację, to niebezpieczne. Nie zaatakuję sam całej załogi piratów.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "To twoja decyzja. Jeśli uważasz, że nie podołasz temu zadaniu, to lepiej od razu odmów. Wówczas będę czekać na spłatę długu Deluca.";
			link.l1 = "Dobrze. Przyniosę dla niego pieniądze. Do zobaczenia później!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Bardzo dobrze. Miło to słyszeć. W takim razie powinieneś udać się do zatoki Le Marin, piraci będą tam od siódmej wieczorem do czwartej rano. Nie przegap ich! I nawet nie myśl o używaniu statku! Takie działania ich spłoszą, idź tam przez dżunglę!\nPrzyprowadź mi więźnia, gdy go znajdziesz, zostawię drzwi otwarte. Polecam poczekać do pierwszej w nocy, zanim wrócisz do miasta, ponieważ musisz unikać uwagi strażników. Bądź ostrożny i powodzenia!";
			link.l1 = "Dziękuję! Z pewnością będę potrzebować trochę szczęścia...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Poczekaj chwilę! Widzę, że nawet nie masz pistoletu. Weź jeden z moich. Mam też kilka kul do niego. Myślę, że się przyda.";
			link.l1 = "Tak, to na pewno się przyda. Dziękuję, monsieur.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "A teraz idź, niech Bóg ci pomoże!";
			link.l1 = "... ";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Cudownie! Bardzo się cieszę, że udało się to pomyślnie załatwić. Przypuszczam, że nie muszę znać szczegółów operacji, prawda? Więc mój drogi hiszpański gość może teraz czuć się bezpiecznie w moim domu...";
			link.l1 = "A co z długiem Folke Deluca?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Oczywiście, tak. Weź jego weksel, teraz jesteś uprawniony do jego długu i masz prawo żądać od niego pieniędzy. No cóż, i oczywiście, petycja o jego zwolnienie z więzienia. Czy zrobiłem wszystko, jak obiecałem?";
			link.l1 = "Tak, monsieur. Wszystko jest ściśle zgodne z umową. Teraz pozwól, że się oddalę.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Zatem, czy jesteś gotów spłacić jego dług?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Tak. Oto pieniądze.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Niestety, wciąż nie zebrałem wymaganej kwoty...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Hm. Wygląda na to, że masz rację, to są drogie kolczyki i na pewno zostały wykonane w Starym Świecie... Co mogę powiedzieć? Dam ci za nie trzydzieści... nie, nawet trzydzieści pięć złotych dublonów. Weź pieniądze, nie sprzedasz ich za więcej.";
			link.l1 = "Trzydzieści pięć doublonów? To nie jest zła cena. Zgadzam się. Proszę, oto one.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Nie. Myślę, że te kolczyki zostawię dla siebie.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Znam, znam, kapitanie. Wygląda na to, że twój nawigator zaciągnął długi niemal w każdej francuskiej kolonii. Prawdę mówiąc, wiedziałem o tym od dawna. Skonsultowałem się z moimi kolegami, standardowa procedura, wiesz...";
			link.l1 = "A nie uważałeś, że to wystarczająco ważne, by poinformować mnie podczas naszej poprzedniej umowy?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Dlaczego? W tamtym czasie głównie interesował mnie dług Deluca wobec mnie, który, nawiasem mówiąc, był największy. Gdy go uregulowałeś, natychmiast powiadomiłem moich kolegów... Mamy ogromną flotę profesjonalnych kurierów, więc nie minęło dużo czasu, zanim zgromadziłem stos rachunków Deluca na swoim biurku.";
			link.l1 = "Widzę... Kupiłeś ich, wiedząc, że mam żywotny interes w nim i środki na zapłatę... To jest wymuszenie, Monseniorze.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "To tylko interesy, kapitanie! Całkowity dług Deluca wynosi sto dublonów, a odsetki rosną... Czy jesteś gotów go wykupić?";
			link.l1 = "Nie jestem jeszcze gotowy, by odpowiedzieć, ale rozważę to. Do widzenia!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Doskonale! Wiesz, co robić dalej - tak samo, jak ostatnim razem. Oto dokumenty - przedstaw je komendantowi więzienia. To była przyjemność robić z Tobą interesy, Kapitanie.";
			link.l1 = "Nie ma w tej sytuacji zbyt wiele do radości. Żegnaj.";
			link.l1.go = "exit";
			RemoveItems(pchar, "gold_dublon", 100);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
