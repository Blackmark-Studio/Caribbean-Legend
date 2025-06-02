// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"...","To już trzeci raz, kiedy mi przeszkadzasz...","Więcej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież to zaginęła moja pamięć...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Chciałbym się napić. Nalej mi najlepszego rumu, jaki macie.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Słuchaj, gdzie jest Callow Gaston?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Czy masz może jakąś pracę? A może mógłbyś coś zasugerować?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "Zadanie wykonane. Fernando Rodriguez nie żyje.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Słuchaj, czy przybył tu do miasta alchemik, lekarz? Jest Włochem, ma około trzydziestu lat, nazywa się Gino Gvineili. Słyszałeś coś o tym?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "Oto twój napitek. Najlepszy rum dla naszego nowego gościa! Czy to jakaś specjalna okazja, czy po prostu wpadłeś, by zwilżyć gardło?";
			link.l1 = "„Aye, można rzec, że to wyjątkowa okazja. Zabieram kilku Murzynów do Blueweld. Niedawno zmodyfikowałem ładownię mojego nowego brygu specjalnie do tego celu. Zatrzymałem się na plantacji i rozmawiałem z nadzorcą, zamówił u mnie ładny transport 'czarnej kości słoniowej'. Czekaj więc na mnie z powrotem w swojej tawernie. Dostarczę towar do Blueweld, a potem zajmę się kolejnymi interesami tutaj na Barbadosie, yo ho!”";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Naprawdę? Cóż, nie ma wstydu w piciu dla dobrego interesu! Więc mówisz, że zamierzasz robić interesy na Barbadosie? To świetnie! Na zdrowie, kapitanie!";
			link.l1 = "Dziękuję uprzejmie, kamracie. Dobrze... Pójdę poszukać miejsca, gdzie mogę usiąść.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston opuścił miasto dwa dni po twoim 'handlowym' występie. Odstawiłeś tu niezły spektakl, ha! Twoje oszustwo szybko wyszło na jaw, to małe miasteczko i plotki rozchodzą się szybko. To sprawiło, że Gaston postanowił się wycofać. Od tamtej pory nikt go tu nie widział. Zostawił jednak dla ciebie list\nProsił, bym przekazał go osobiście, jeśli pojawisz się tu przed nim. W rzeczywistości nie jesteś pierwszym, kto szuka Gastona. Był tu jakiś wąsko-oczny duży mężczyzna i stary człowiek, wyglądał na Hiszpana lub Portugalczyka, nie jestem pewien. Ale nie mogę zapomnieć jego twarzy, coś z nim było bardzo nie tak...";
			link.l1 = "Daj mi ten list... Dzięki!";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Rogue)", "None");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Nie potrzebuję usług łajdaka. Nie mam żadnego zadania, które mógłbym ci zaoferować.";
				link.l1 = "Hej, hej. Uważaj na język, kumplu!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				notification("Skill Check Failed (35)", SKILL_F_LIGHT);
				notification("Skill Check Failed (35)", SKILL_FENCING);
				notification("Skill Check Failed (35)", SKILL_F_HEAVY);
				notification("Skill Check Failed (35)", SKILL_PISTOL);
				// <--
				dialog.text = "Kapitanie, jesteś zbyt miękki. Potrzebuję wojownika o nieco lepszej reputacji niż ty. Wróć, gdy nauczysz się obsługiwać tę stal wiszącą przy pasie. Odrobina celności w strzelaniu też by nie zaszkodziła.";
				link.l1 = "Rozumiem. W takim razie odwiedzę cię później.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Hm... Jesteś nawet na czas. Mam jedno zadanie, które musi być wykonane od razu. Jeśli się dobrze spiszesz, przedstawię cię kilku wpływowym osobom. Teraz słuchaj, oto co musisz zrobić.";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "Jakiś hidalgo niedawno przybył z Sewilli, chcąc uniknąć niepożądanych konsekwencji pojedynku w Europie. Ale zemsta nie zna granic, i jedna hiszpańska rodzina szlachecka pragnie śmierci tego hidalgo. Wykonaj ich prośbę wszelkimi niezbędnymi środkami. Przynieś jako dowód jego palec z pierścieniem. Przy okazji, przynieś również wszystkie inne przedmioty, które znajdziesz przy jego zwłokach. Czy jesteś gotów podjąć się tego zadania?";
			link.l1 = "Jeśli zapłata jest dobra, to wchodzę w to.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Pracować jako zabójca? Nie ma mowy!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "To spadaj i zapomnij, o czym rozmawialiśmy.";
			link.l1 = "Odchodzę.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "Twoja nagroda wyniesie 30 000 sztuk srebra, niezłe pieniądze. Poza tym możesz zabrać każdą monetę, którą znajdziesz przy jego ciele. Teraz omówmy szczegóły. Nazywa się Don Fernando Rodriguez, 35 lat, wysoki, śniady, ubrany jak oficer wojskowy. Jest dobrym żeglarzem i doświadczonym szermierzem\nNie mogę powiedzieć, gdzie go znaleźć, wiem tylko, że jest gdzieś na Karaibach\nPrzeszukaj każde hiszpańskie miasto, aż go złapiesz. Masz dwa miesiące. Ostatnia rzecz: wiem, co ma przy sobie, więc nawet nie próbuj ukrywać przede mną żadnych przedmiotów. Pytania?";
			link.l1 = "Nie mam żadnych pytań. Wyruszam w drogę!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Czy masz przy sobie palec z pierścieniem? Pokaż mi go.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Tak, oczywiście. Oto jest.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "Nie. Fernando zatonął w wodzie wraz ze swoim statkiem, a palec zatonął z Fernando.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "Palec z pierścieniem był obowiązkowym warunkiem w kontrakcie. Miał służyć jako potwierdzenie śmierci klienta. Kto wie, czy Rodriquez dopłynął do brzegu z zatopionego statku? Sprawdziłeś? Nie. W zasadzie nie wykonałeś zadania, więc nasza umowa jest zakończona. Wszystkiego najlepszego.";
			link.l1 = "Ale się go pozbyłem. Zniknął! A, pierdol się... Na Karaibach jest mnóstwo innych rzeczy do roboty. Żegnaj.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Cudownie! Zatrzymam palec dla siebie. A teraz zawartość jego kieszeni. Zobaczmy, co przyniosłeś.";
			link.l1 = "Śmiało, rozejrzyj się...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, to wszystko, czego potrzebuję. Dobra robota! Wykonałeś świetną pracę. Jestem z ciebie bardzo zadowolony.";
				link.l1 = "Dziękuję! Zawsze miło jest otrzymać pochwałę za dobrze wykonaną robotę.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Hm... Ostrzegałem cię, że wiem, bez czego Rodriguez nigdy by się nie obył. I nie widzę tutaj tego, czego potrzebuję. Schowałeś te rzeczy do kieszeni? Zgubiłeś je? To i tak nie ma znaczenia. Nie mam ochoty mieć z tobą nic wspólnego. Wynoś się stąd.";
				link.l1 = "O, do diabła z tobą...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Oto twoja nagroda, jak obiecane, trzydzieści tysięcy. Mam również dodatkowe zadanie, wymagające dużej odpowiedzialności i ryzyka, ale zapłata wzrośnie odpowiednio, 40 000 pesos.";
			link.l1 = "Zamieniam się w słuch. Kto jest następnym klientem?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "Tym razem będziesz polować nie na człowieka, lecz na przedmiot. Musisz zakraść się do domu Richarda Fleetwooda na Antigui i ukraść jego dziennik. Jest on angielskim kapitanem. Miejsce jest ściśle strzeżone, a sam Richard rzadko odwiedza swój dom\nPlan jest prosty. Gubernator St. Jones zorganizuje prywatną imprezę za dziesięć dni, Fleetwood będzie na niej obecny. Musisz dostać się do jego domu w nocy między pierwszą a trzecią godziną. W środku będzie tylko jeden żołnierz\nPozbądź się go. Szukaj dziennika w mieszkaniu Richarda. Weź ten klucz.";
			link.l1 = "Hm... Interesujące. Zrozumiałem, co muszę zrobić. Jestem gotowy, by wyruszyć!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Uważaj. Nie zakradaj się do domu przed datą, którą ci wskazałem. W przeciwnym razie, w najlepszym przypadku, po prostu cię stamtąd wyrzucą, a w najgorszym, skończysz za kratami. Powtórz mi datę i czas.";
			link.l1 = "Właśnie za dziesięć dni, między pierwszą a trzecią nad ranem.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Dobrze. Możesz iść. Powodzenia!";
			link.l1 = "Dziękuję, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nie, nie znam. Mamy zielarzy i medyków, ale żaden z nich nie nosi takiego imienia.","Pierwszy raz słyszę takie dziwne imię. Nie, nigdy nie odwiedził nas człowiek, o którym mówisz.","Nie mamy tu żadnych alchemików. Mamy medyków, ale żaden nie nosi tak dziwnego imienia.");
			link.l1 = "Rozumiem. To kiepsko. Będę szukał dalej!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
