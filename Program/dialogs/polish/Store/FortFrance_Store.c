// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Śmiało, czego chcesz?","Przecież właśnie o tym rozmawialiśmy. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, gdy mówisz o jakimś pytaniu...","Słuchaj, to jest sklep. Ludzie tu kupują rzeczy. Nie przeszkadzaj mi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Racja, z jakiegoś powodu zapomniałem...","Tak, to naprawdę już trzeci raz...","Hm, nie będę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Słuchaj, monsieur, szukam pracy. Nie takiej na pełen etat ani noszenia worków z ładunkiem, ale raczej biegania z poleceniami, że tak powiem. Czy przypadkiem potrzebujesz pomocy?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "Ukończyłem twoje zlecenie. Znalazłem Gralama Lavoie.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Poznaj swojego nowego asystenta, monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "To znowu ja, monsieur. Przyszedłem po moją nagrodę.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Spójrz na te kolczyki, monsieur. Znalazłem je na ciele bandyty, który został zabity w dżungli. To jest wyraźnie dzieło wyśmienitego jubilera, który, jestem pewien, nie pochodzi stąd. Czy możesz powiedzieć coś o tych kolczykach?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Przepraszam, panie, ale gdzie jest pańska szabla? Niebezpiecznie jest opuszczać miasto bez klingi. Nigdy nie wiadomo, co może się wydarzyć w dżungli!";
				link.l1 = "Do diabła, całkiem zapomniałem! Wszystko zostało zabrane!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "Praca? Hm. Przypuszczam, że mam dla ciebie pracę, która cię zainteresuje. Mój asystent zaginął, pracował w moim magazynie. Nie ma go już od tygodnia i to cholernie irytujące, bo muszę wykonywać jego obowiązki i nie mam na to czasu.\nProszę, znajdź tego idiotę i dowiedz się, dlaczego do diabła porzucił swoją pracę. A jeszcze lepiej - sprowadź go do mnie. Zapłacę ci tysiąc sztuk ośmiu.";
			link.l1 = "Dobrze, wchodzę w to. Powiedz mi jego imię i opisz, jak wygląda. Masz jakieś pomysły, gdzie go szukać?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Szukaj człowieka Bóg wie gdzie za marny tysiąc? Musisz żartować!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hej, monsieur. Kto szuka pracy, ty czy ja? Jeśli nie chcesz, nie zmuszam cię. Miłego dnia.";
			link.l1 = "Hm... Think I'll go check the port authority; perhaps they'll offer something more substantial there.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Imię to Gralam Lavois. Jego wygląd? Trzydzieści pięć lat, broda i wąsy, długi brązowy płaszcz, biała koszula. A, i zawsze nosi ten głupi kapelusz z daszkiem, udaje admirała z kotwicą w dupie.\nNie ma go w St. Pierre, sprawdziłem całe miasto. Musi być w dżungli lub w Les Francois, ukrywając się z piratami, którzy tam czają się.\nZ drugiej strony, prawdopodobnie jest w osadzie piratów Le Francois, która znajduje się we wschodniej części naszej wyspy. Może rozmawia z piratami, albo spędza czas w tawernie, albo kłóci się z miejscowym kupcem w sklepie.\nJak dotrzeć do Le Francois? Wyjdź przez bramy miasta do dżungli, na rozwidleniu dróg skręć w lewo, potem podążaj drogą, aż skręcisz w prawo, a następnie wejdź w lewy przesmyk między skałami, a znajdziesz Le Francois. Nie sądzę, żebyś się zgubił.";
			link.l1 = "Dobrze. Zajmę się poszukiwaniami. Jak tylko coś się pojawi, natychmiast cię poinformuję.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "A tak? A gdzie on jest?";
			link.l1 = "Znalazłem go w Le Francois. Nie będzie już dla ciebie pracować. Powiedział też wiele dość pikantnych rzeczy na twój temat... Czy jesteś zainteresowany, by to usłyszeć?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "Nie. Oszczędź mi szczegóły... Co za szkoda! Co ja teraz zrobię bez asystenta?";
			link.l1 = "Wynajmij kogoś innego.  Czy naprawdę jest to taki wielki problem, jak powiedział Gralam?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Rzeczywiście, parszywe szczęście. A co powiedział ten obibok?";
			link.l1 = "Cóż, na początek, on oczywiście nie traci czasu, he-he. Powiedział, że nikt w całym Saint Pierre nie zgodzi się zaciągnąć do ciebie na służbę, bo... nie płacisz swoim pracownikom wystarczająco. Tak, przy okazji, "+npchar.name+", jesteś mi winien tysiąc pesos, jak obiecano.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Proszę, weź swoje pieniądze. Ha! Nie płacą wystarczająco! Oczywiście, nikt nie chce dla mnie pracować. Drań zrobił wszystko, żeby rozpuścić brudne plotki. Co mogę zrobić? Nie mogę zrobić wszystkiego sam!\nNie mogę iść spać, dopóki nie policzę każdego kawałka ładunku, bo ci cholerni robotnicy zawsze coś kradną. Po ostatnim załadunku brakuje mi pięciu beczek rumu. Jestem pewien, że robotnicy 'przypadkowo' je zabrali...";
			link.l1 = "Cóż, nie wiem, co doradzić. Dobrze, wszystkiego najlepszego. Czas na mnie.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Poczekaj! Myślę, że możesz mi pomóc. Skoro zdołałeś odnaleźć tego drania, to być może będziesz w stanie...";
			link.l1 = "A co bym mógł zrobić, zastanawiam się, jeśli nikt w tym mieście ci nie wierzy? Jestem tu nowy i...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Pozwól mi dokończyć, sir. Byłeś w Le Francois. Chciałbym, abyś ponownie tam pojechał i spróbował znaleźć dla mnie pracownika. Być może Gralam nie całkowicie zrujnował moją reputację w tym pirackim siedlisku. Praca jest łatwa - liczenie ładunków i pilnowanie robotników portowych, aby zapobiec kradzieżom. Czasami trzeba wykonać moją robotę tutaj zamiast mnie, gdy mnie nie ma, oczywiście za dodatkową opłatą. Powiedz im, że oferuję pokój w sklepie do zamieszkania i pięćset sztuk osiem na tydzień. Monsieur, zamierzałem rozszerzyć mój biznes i w końcu wszystko idzie dobrze, potrzebuję asystenta! A propos, najlepiej szukać pomocy w znalezieniu pracownika u lokalnego karczmarza, Cesare Craiga. Ten drab z pewnością ci pomoże, choć nie za darmo, znaleźć osoby, które byłyby zainteresowane pracą dla mnie.";
			link.l1 = "Hm. Mogę spróbować, chociaż nie jestem pewien... Ile mi zapłacisz za tę robotę?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "To będzie zależało od tego, jakiego pracownika uda ci się zatrudnić. Im lepszy się okaże, tym więcej zapłacę ci za twoje starania. To uczciwe, prawda?";
			link.l1 = "Nie uważasz, że zmuszasz mnie do płynięcia na ślepo? Skąd mam wiedzieć, jak ocenisz pracownika? Możesz każdego sklasyfikować jako złego lub...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Monsieur! Może i można mnie nazwać trochę skąpym, ale nikt nie mógłby mnie nazwać nieuczciwym! Jeśli mówię ci, że zapłacę za twoje wysiłki w zależności od wyniku, to mam to na myśli. Spójrz na to także z mojej perspektywy. Możesz mi tu przyprowadzić jakiegoś leniwego cygana, który nie tylko będzie się obijał i nic nie robił, ale nawet może mnie okraść w nocy!";
			link.l1 = "Dobrze. Zgadzam się. Wezmę cię za słowo, "+npchar.name+"Na pewno nie przyprowadzę żadnych Cyganów.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Czy znalazłeś dla mnie pracownika? Wspaniale. Pozwól mi z nim porozmawiać, wróć za godzinę po swoją nagrodę.";
			link.l1 = "Dobrze. Wrócę za godzinę.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Jestem całkiem zadowolony z pracownika, którego dla mnie znalazłeś, choć więcej gada niż robi, ale nie martw się, wybiję mu to gadanie z głowy z czasem. Twoja nagroda to trzy tysiące sztuk osiem. Proszę, oto one.";
					link.l1 = "Dziękuję! Powiedz mi, monsieur, czy wiesz, czy ktoś jeszcze w mieście potrzebuje pomocy w jakiejś ważnej sprawie?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Udało ci się znaleźć naprawdę wartościowego pracownika! Jest nawet lepszy niż ten łotr Gralam. Jestem bardzo, bardzo zadowolony, sir. Proszę, oto twoja nagroda - pięć tysięcy sztuk ośmiu.";
					link.l1 = "Dziękuję! Powiedz mi, Monsieur, czy wiesz, czy ktoś jeszcze w mieście może potrzebować pomocy w jakiejś ważnej sprawie?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "Znalazłeś dobrego pracownika. I choć nie zna wszystkich sztuczek handlu, jestem pewien, że bez trudu sobie z nimi poradzi. Jestem z ciebie zadowolony, sir. Oto twoja nagroda - cztery tysiące sztuk srebra.";
					link.l1 = "Dziękuję! Powiedz mi, monsieur, czy wiesz, czy ktoś jeszcze w mieście potrzebuje pomocy w jakiejś ważnej sprawie?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hmm... Niedawno widziałem zarządcę portu, wyraźnie zmartwionego, zmierzającego do władz portowych. Sprawdź z nim, kto wie, co mogło się wydarzyć.";
			link.l1 = "Zrobię właśnie to. Dziękuję, Monsieur.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Cóż, cóż mam powiedzieć, wspaniałe kolczyki. Mogę ci dać... zobaczmy... cztery tysiące sztuk srebra za nie. Wątpię, by ktokolwiek zaoferował ci więcej. Czy mamy umowę?";
			link.l1 = "Umowa stoi! Są twoje.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Nie. Myślę, że te klejnoty zatrzymam dla siebie.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "To nie wystarczy. Sugeruję, byś zwrócił się do naszego gubernatora i poprosił go o pomoc.";
			link.l1 = "Dzięki za radę. Tak właśnie zamierzam zrobić.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
