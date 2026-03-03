void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "To jest błąd. Daj znać deweloperom.";
			link.l1 = "Będę!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Pozdrowienia, blada twarzy. Widzę, że jesteś kapitanem dużej łodzi. Ja Kanauri. Jestem wodzem Kajmanów - potężnego plemienia Arawaków. Chcę z tobą rozmawiać.";
			link.l1 = "Słucham, wodzu. Jakie kłopoty cię do mnie sprowadziły?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "Czego chcesz ode mnie, ty plugawa, czerwonoskóra małpo? Wracaj do swojej dżungli i nie zawracaj mi głowy swoimi prośbami.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! Czyżby biały kapitan nie był uczony grzeczności? Otrzymałem ofertę. Zarabiasz kupę wampum, ale teraz idę. Żegnaj, bladolicy.";
			link.l1 = "Idź, zjeżdżaj...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "Biały brat bystry jak sowa, przebiegły jak wąż. Kłopoty przydarzają się Indianinowi. Wielka-wielka łódź białych ludzi przybywa do mojej wioski. Zabierają wielu Kajmanów, moich ludzi, umieszczają ich na swojej łodzi i zabierają na Matkę Wszystkich Wód...";
			link.l1 = "Czekaj... czy mówisz, że twoi ludzie zostali zniewoleni przez białych ludzi z okrętu?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "Mówisz prawdę, biały bracie. Wiem, że ci bladolicy nie są ci przyjaciółmi. Ci okrutni biali ludzie z hiszpańskiego plemienia. Oni biorą moich ludzi. Ale ja ich znajdę. Hiszpanie zmuszają Indian do pracy od świtu do zmierzchu, zanurzają się głęboko w Matkę Wód, znajdują muszle wypełnione łzami bogów.";
			link.l1 = "Nurkowanie po perły... To brutalna robota.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = " Prawda to, biały bracie. Wiem, że ci ludzie nie są ci przyjaciółmi. Oni z angielskiego plemienia. Zabierają moich ludzi. Ale ja ich znajdę. Anglicy zmuszają Indian do pracy od świtu do zmierzchu, nurkować w Matce Wód, szukać muszli pełnych łez bogów.";
			link.l1 = "Nurkowanie po perły... To ciężka praca.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Indianin choruje i umiera z powodu niewolnictwa. Biały człowiek nie ma litości dla Indianina. Bat i pistolet to prawo białego dla Indianina. Ja stary. Nie mam ludzi do walki. Kajmańscy Arawakowie to pokojowy lud, wynaleźliśmy fajkę pokoju. Proszę cię, biały bracie, dobądź miecza i pistoletu przeciw złemu białemu, ocal Indianina Arawaka.";
			link.l1 = "Czy prosisz mnie, abym wypowiedział wojnę? Musisz zrozumieć, wodzu, moje zasoby są ograniczone.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "Nie idź na wojenną ścieżkę. Uwolnij Indianina. Moi ludzie. Damy ci wszystkie łzy bogów, jakie mamy na kanoe. Zabij złego białego, pomóż Indianinowi, zdobądź łzy bogów, sprzedaj je za dużo-dużo wampum. Mnóstwo wampum.";
			link.l1 = "Ach, teraz rozumiem. Nie, Canauri, nie mogę ci pomóc. Nie mogę tego teraz zrobić - mój statek wymaga naprawy, nie ma już zapasów...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "W takim razie, będzie mi miło. Omówmy szczegóły. Gdzie są twoi ludzie? Powiedziałeś, że już ich znalazłeś...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! Mogę poczekać, biały bracie... Będę w tym porcie jeszcze jeden księżyc, szukając obrońcy mojego ludu. Znajdziesz mnie tutaj, gdy będziesz gotowy.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "Wracasz, biały bracie? Pomożesz mi ukarać złych ludzi i uratować Indianina?";
			link.l1 = "Gotowy, jak tylko mogę być.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "Muszę się jeszcze przygotować.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "Będę tu, biały bracie.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "Jestem bardzo rad, że się zgodziłeś, biały bracie!";
			link.l1 = "Porozmawiajmy o szczegółach, Canauri. Gdzie są twoi ludzie? Mówiłeś, że już ich znalazłeś...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Hiszpański";
				pchar.questTemp.RedChieftain.Add2 = "Zatoka Carupano, niedaleko Kumany";
				dialog.text = "Są w obozie w Zatoczce Carupano, niedaleko hiszpańskiego obozu zwanego Kumana. Każdego dnia wypływają łodziami na morze, nurkują w wodę, głęboko-głęboko...";
				link.l1 = "Rozumiem. A Hiszpanie czuwają nad nimi, gdy nurkują?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "Anglików";
				pchar.questTemp.RedChieftain.Add2 = "Przylądek Pereł, niedaleko Blueweld";
				dialog.text = "Rozbijają obóz na Przylądku Perlas w pobliżu angielskiego obozu zwanego Blueweld. Każdego dnia wypływają łodziami na morze, nurkują w wodę, głęboko-głęboko...";
				link.l1 = "Rozumiem. I, oczywiście, Anglicy ich pilnują?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Tak, dwie duże kanoe bladych twarzy z ognistymi kijami i dużymi nożami. Obóz na brzegu również strzeżony - Indianin nie może uciec.";
			link.l1 = "Jakie to były statki? Czy możesz je opisać? Jakie są duże? Jakie mają żagle?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Ta kanoe jest duża, ale Canauri widział większe. Przedni żagiel jest bardzo-bardzo pochylony, tworzy trzy boki jak te. (Rysuje trzy żagle łacińskie i trapezoidalny żagiel na ziemi) Góra jest wąska, dół szeroki.";
			link.l1 = "Wydaje się i wygląda jak szkuner...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri nie znać tego słowa. Blada twarz bardzo ostrożna, jeśli zobaczy inną kanoę - wylądować Indian i czekać, aż inna kanoa odpłynąć.";
			link.l1 = "Ostrożne sukinsyny... jak mogę się do nich zbliżyć?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "Jeśli bladolicy brat weźmie małą łódź, to może podkraść się blisko brzegu. Pokażę drogę. Ale przyprowadź tylko jedną małą łódź, bo blade lice pies zobaczy i wypędzi Indianina z łodzi do dżungli...";
			link.l1 = "Zrozumiano. Będę potrzebował lugiera lub slupa do tej operacji. Świetnie. Slup przeciwko dwóm szkunerom... Boże... a myślałem, że to będzie łatwe!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Czy idziemy, biały bracie? Mamy mniej niż miesiąc.";
			link.l1 = "Tak. Wchodź na mój statek, wodzu. Nie traćmy czasu!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Tryb eksploracji: timer nie jest wyłączony. Dotrzymaj terminu!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Dziękuję, biały bracie! Ratujesz plemię Arawak z Kajmanów! Jesteśmy ci wielce zobowiązani. Ścieżka jest wolna od białolicych psów i Indianin może swobodnie biegać po dżunglach. Dajemy ci wszystkie łzy bogów pozostawione na łodziach.";
			link.l1 = "No, zobaczmy, co masz...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("Wódz przekazał ci "+iSmallPearl+" małych i "+iBigPearl+" dużych pereł.");
			dialog.text = LinkRandPhrase("Cieszę się, że łzy bogów są twoje, bracie Arawaka!","Dziękuję ci, odważna blada twarzy!","Weź nasz połów, biały bracie!");
			link.l1 = LinkRandPhrase("Ciesze się, że mogłem pomóc!","Dzięki, czerwonoskóry bracie!","Świetnie!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Canauri dziękuje ci ponownie, blady bracie! Ratujesz wszystkie kanoe z Indianami! Dla Canauri jest bardzo ważne, aby uratować wszystkie kanoe, ponieważ także ratujesz wnuka Canauri, którego zły blady twarz wziął do niewoli. Jako dziecko, mój wnuk bardzo lubił pływać, a Kanauri dał mu ten zaczarowany amulet, aby wnuk się nie utopił. Teraz wnuk już nie chce pływać i daje mi amulet, abym mógł go tobie dać, blady bracie. Mam nadzieję, że łzy bogów i ten dar będą wystarczającą nagrodą za życie Arawaka. A teraz żegnamy się - czas wracać do naszej rodzimej wioski.";
				link.l1 = "Powodzenia, Cunauri! Cieszę się, że twój wnuk przeżył! Modlę się, aby to zło nigdy więcej cię nie spotkało!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri dziękuje ci ponownie, bladolicy bracie! Mam nadzieję, że łzy bogów będą wystarczającą nagrodą za życie Indian. Teraz żegnaj, idziemy do rodzimej wioski.";
				link.l1 = "Powodzenia, Cunauri! Nigdy więcej nie popadnij w niewolę!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
