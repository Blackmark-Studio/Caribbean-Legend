// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Oczywisty błąd. Powiedz o tym deweloperom.";
			link.l1 = "O, zrobię to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Witaj, kapitanie! Mam propozycję biznesową, która cię bardzo zainteresuje.";
			link.l1 = "Kontynuuj, monsieur.";
			link.l1.go = "citizen_1";
		break;
		
		case "citizen_1":
			dialog.text = "Chcę wynająć twój statek do przewozu z Gwadelupy na Hiszpańskie Wybrzeże.";
			link.l1 = "Chcesz tam płynąć jako pasażer?";
			link.l1.go = "citizen_2";
			link.l2 = "Hiszpańska Główna? Podziękuję. Nie jesteśmy naprawdę przyjaciółmi z Hiszpanami. Sugeruję, żebyś znalazł innego głupca.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Jak pan sobie życzy, kapitanie, choć to nie jest podróż wysokiego ryzyka. Żegnaj.";
			link.l1 = "Żegnaj.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Jak sobie życzysz, kapitanie. Żegnaj!";
			link.l1 = "Żegnaj.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			DelLandQuestMark(npchar); // Rebbebion, снять марку
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Nie całkiem tak, monsieur. Pasażer to człowiek zależny od woli kapitana. Chcę wynająć ciebie, twoją załogę i twój statek, aby dostać się razem z dwoma przyjaciółmi do Panamy.";
			link.l1 = "Do Panamy? Jak? Chcesz opłynąć cały kontynent?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Ha-ha-ha! Dobry żart, kapitanie. Oczywiście, że nie. Wszystko, co musisz zrobić, to dostarczyć nas do Zatoki Komarów, która nie jest daleko od Portobello. Sami dotrzemy do Panamy, to nie będzie nasza pierwsza wyprawa przez dżunglę.";
			link.l1 = "A co z zapłatą?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Dwa kufry z dublonami. Trzysta sztuk. Jeden dostaniesz z góry, gdy tylko będziemy na pokładzie. Drugi kufer będzie twój, gdy tylko dotrzemy do celu.";
			link.l1 = "Solidna nagroda za tak łatwą robotę. Gdzie jest haczyk, mój dobry człowieku?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Kapitanie, czas to pieniądz, moi przyjaciele i ja nie mamy go. Musimy wypłynąć stąd tej nocy i musimy być tam za dziesięć dni. To będzie nasz drugi rejs. Więc, jesteś z nami?";
			link.l1 = "Umowa stoi!";
			link.l1.go = "citizen_6";
			link.l2 = "Przykro mi, monsieur, ale twoja propozycja brzmi dla mnie zbyt podejrzanie. Znajdź sobie innego głupca.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Znakomicie. Moi przyjaciele są obecnie w dżungli, poinformuję ich o naszej umowie. Znajdziesz nas dziś wieczorem na plaży Capster o dziesiątej. Nie spóźnij się, kapitanie!";
			link.l1 = "Dobrze. Plaża Capster, tej nocy, o dziesiątej.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Chwila, kapitanie, nawet się nie przedstawiliśmy. Mam na imię Bertrand Pinette. A ty jesteś...";
			link.l1 = ""+GetFullName(pchar)+". Kapitanie "+GetFullName(pchar)+"Do widzenia, monsieur Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", 20.0);
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
			DelLandQuestMark(npchar); // Rebbebion, снять марку
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Kapitan "+GetFullName(pchar)+" , oto jesteś. Czy jesteśmy gotowi do drogi?";
			link.l1 = "Tak. Witaj na pokładzie.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Zgoda. Przyjmij zaliczkę - skrzynię pełną dublonów. I pamiętaj - masz tylko dziesięć dni, aby nas dostarczyć do celu. Ani dnia dłużej!";
			link.l1 = "Pamiętam warunki. Nie martw się, zdążymy na czas. Siadajcie.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Więc, kapitanie, całkowicie wypełniłeś swoją część umowy. Teraz moja kolej. Przyjmij tę skrzynię wraz z naszymi najgłębszymi wyrazami wdzięczności.";
			link.l1 = "Przyjemność robić interesy z tobą, monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Podobnie. Żegnaj, kapitanie "+GetFullName(pchar)+".";
			link.l1 = "Żegnaj!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "Więc, kapitanie, oto jesteśmy. Wypełniłeś tylko połowę swojej części umowy, więc i ja zrobię to samo. Zachowaj swoją zaliczkę jako pełną zapłatę. Mam nadzieję, że nie będziesz miał nic przeciwko, to w końcu była twoja wina.";
			link.l1 = "Nie mogę powiedzieć, że mi się to podoba, ale przyznaję, że masz rację. Rozstańmy się teraz.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "W każdym razie, dziękuję za usługę, kapitanie "+GetFullName(pchar)+"Żegnaj!";
			link.l1 = "Żegnaj.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "O! Co za spotkanie! "+TimeGreeting()+", "+GetFullName(pchar)+"Ale jak?";
			link.l1 = TimeGreeting()+", monsieur Pinette. Nie było łatwo was znaleźć.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "I jaki jest powód, kapitanie?";
			link.l1 = "Mój dobry panie, jest człowiek o imieniu "+GetFullName(sld)+" i jest bardzo chętny, by cię zobaczyć. Zakładam, że wiesz dlaczego.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Oczywiście, że tak, ale ty, mój drogi Kapitanie, musisz także wiedzieć, że nie jestem chętny, by widzieć monsieur "+GetFullName(sld)+" w ogóle. Jesteś jego łowcą nagród? Po prostu tego nie rozumiem.";
			link.l1 = "Ach, ale właśnie taką osobą jestem w tej chwili i nie jestem z tego zadowolony. Popełniłem błąd i teraz monsieur "+GetFullName(sld)+", niech go diabli, postawił mnie przed wyborem. Albo twój wspaniały powrót do Gwadelupy, albo mój tyłek jako wspólnik w twoim małym przedsięwzięciu uwolnienia don Carlosa de Milyar. To mnie zaboli, wiesz o tym.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ach, ten drań! To bardzo grzeszny sposób na szantażowanie ludzi!.. Więc, kapitanie, co zamierzasz zrobić, dokonasz wyboru czy pozwolisz, by ktoś taki cię szantażował?";
			link.l1 = "A co ty o tym myślisz? Wierzę, że idziesz ze mną do Basse-Terre.";
			link.l1.go = "citizen_19";
			link.l2 = "Czy mam tutaj wybór?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Och, muszę cię rozczarować, Kapitanie. Nie mam ochoty wchodzić na pokład twego pięknego statku. Nic tu nie osiągniesz siłą, miejsce jest otoczone strażnikami, a ja będę krzyczeć o pomoc, jeśli tylko okażesz jakiekolwiek gwałtowne zamiary. Oczywiście, możesz spróbować mnie dźgnąć, ale nasz dobry przyjaciel nic nie zyska z zimnego trupa. Tak więc, najrozsądniejszym dla ciebie w tej chwili sposobem jest zostawić mnie w spokoju. Pozwolę ci odejść bez szwanku.";
			link.l1 = "Czy naprawdę wierzysz, że po wszystkim co się stało, po prostu odejdę? Wciągnąłeś mnie w to bagno, łotrze, czas zapłacić!";
			link.l1.go = "citizen_20";
			link.l2 = "Masz rację, przypuszczam. Podoba mi się pomysł przebicia cię sztyletem, ale to bezcelowe. Nawet nie próbuj mieć nadziei, że to koniec. Teraz udaję się do Basse-Terre, gdzie poinformuję naszego dobrego przyjaciela o twoim miejscu pobytu. A potem wyśle zamaskowanych ludzi za tobą.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ach! Żołnierze! Pomocy!!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "Oczywiście. Powiedz swojemu szefowi, żeby trzymał swoich zamaskowanych ludzi w ryzach - ostatnio staję się bardzo popularny. Żegnaj, kapitanie.";
			link.l1 = "... ";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "Czekaj! Poddaję się! Poddaję się!";
			link.l1 = "Dokładnie tak! Teraz rzuć broń i marsz na statek!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "Zawsze jest wybór, kapitanie. O ile rozumiem, nie ścigałbyś mnie, gdyby nie groźby od tego bankiera?";
			link.l1 = "Dokładnie.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Dobrze. W takim razie zorganizuję ci solidny sposób na zamknięcie mu ust. Napiszmy list, który zaniesiesz swojemu pracodawcy. Powiedz mu, że jeśli kiedykolwiek zacznie mówić, gubernator Gwadelupy dowie się o człowieku, który zaplanował i zainwestował w zniknięcie 'Courage' - kuriera lugra na misji transportu dużej partii diamentów.";
			link.l1 = "Hm. Myślę, że zaczynam rozumieć, monsieur Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Cieszę się, że jesteś taki bystry, Kapitanie. De Lion osobiście przybije głowę przebiegłego sknery do bram miasta, jeśli dowie się prawdy o zniknięciu Courage. W tym liście, który zaraz napiszę, znajdziesz dowody, które uspokoją szantażystę. Daj mi chwilę, abym mógł wziąć pióro.";
			link.l1 = "Dobrze...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(pisanie) Proszę, weź to. W tym pakiecie są dwa podobne listy. Jeden daj bankierowi, niech się nacieszy. Drugi zatrzymaj dla siebie i trzymaj w ukryciu.";
			link.l1 = " Czy informacje są godne zaufania?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "Przysięgam na to, pomogłeś mi, a teraz ja pomogę tobie. Bądź pewien, że szantażysta zostawi cię w spokoju, gdy przeczyta ten testament. Ach, tak... Jeszcze jedna rzecz, kapitanie. Skoro załatwiliśmy to pokojowo... Mam skrytkę i powiem ci, gdzie ją znaleźć, jeśli obiecasz trzymać się z dala od moich operacji w przyszłości. I tak nigdy nie pozwolą mi postawić stopy na Gwadelupie.";
			link.l1 = "Jeśli list zadziała zgodnie z zamierzeniem, to z całą pewnością mogę ci to obiecać.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "Zgoda zatem. Poszukaj pośród skał w jaskini Guadeloupe. Niech to posłuży ci jako skromna rekompensata za twoje kłopoty. Powodzenia, kapitanie.";
			link.l1 = "To samo do ciebie, monsieur Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "Witaj, monsieur! Jesteś kapitanem "+GetFullName(pchar)+", prawda?";
			link.l1 = "Zgadza się. Co mogę dla ciebie zrobić?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", właściciel banku w Basse-Terre prosi cię, abyś odwiedził go jak najszybciej. Polecił mi codziennie sprawdzać nasze biuro portowe, aby upewnić się, że twoje przybycie nie zostanie przeoczone.";
			link.l1 = "Interesujące, a dlaczego miałby tak bardzo chcieć mnie zobaczyć?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+"  osobiście powie ci, dlaczego. Mam nadzieję, że nie odrzucisz jego zaproszenia.";
			link.l1 = "Hm.. Dobrze. Ci bankowcy to potężny lud i nigdy nie marnują czasu na płotki. Odwiedzę tego człowieka tak szybko, jak to możliwe.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Dziękuję, kapitanie. Żegnaj!";
			link.l1 = "Żegnaj.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh! Ty szumowino! Nie ma mowy, że to przypadkowe spotkanie...";
			link.l1 = "Prawda to, Jean... wybacz, miałem na myśli Juan. Wytropiłem cię. Teraz bądź łaskaw ruszyć się do mojego ładowni? Odpocznij i porozmawiamy.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "Spełniłem swoją część umowy. Teraz twoja kolej. Zastrzel to i pamiętaj o konsekwencjach kłamstwa.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Znajdziesz Bertranda Pinette na Barbadosie, a dokładniej na głównej plantacji. Zamierzał tam kontynuować swoje operacje. Nadzorca plantacji jest jego przyjacielem.";
			link.l1 = "Jakiego rodzaju operacje?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "To samo, co miał na Gwadelupie. Półlegalny handel, przemyt, niewolnicy. Myślę, że chce zająć się handlem niewolnikami i cukrem, dlaczego inaczej przeniósłby się na plantację?";
			link.l1 = "Rozumiem. Czy ma on jakichś protektorów wśród angielskich władz?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Chyba tak. Ciekawa postać z niego. Zawsze ma przyjaciół wszędzie.";
			link.l1 = "Coś jeszcze?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Jakie? Przebiegły i sprytny, zawsze zna się na rzeczy, zawsze ma asa w rękawie. Nie miałem zbyt wiele czasu, by dowiedzieć się o nim więcej.";
			link.l1 = "Rozumiem. Dobrze, muszę popłynąć do Bridgetown. Jesteś wolny, don Juan. Nawet nie myśl o ostrzeganiu Pinette'a. Jeśli go tam nie znajdę, znowu będziesz miał kłopoty.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "Przykro mi, kolego. Nic osobistego. Wiesz za dużo, to twój problem.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
