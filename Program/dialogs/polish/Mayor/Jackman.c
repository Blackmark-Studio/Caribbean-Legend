// Якоб Джекман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Masz mi coś do powiedzenia? Nie? To wynoś się stąd!","Ha, "+pchar.name+"! Masz do mnie interes? Nie? To mnie nie zawracaj głowy.")+"","Mam nadzieję, że wyraziłem się dość jasno, przestań mnie irytować.","Chociaż jasno się wyraziłem, nadal mnie denerwujesz!","Dobrze, mam już dość tej bezczelności, wynoś się, dziwaku.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Już odchodzę.","Jasne, Jackman...","Przykro mi, Jackman...","Ała...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Jesteś szalony? Chciałeś się pobawić w rzeźnika? Wszyscy piraci są na ciebie wściekli, chłopcze, lepiej opuść to miejsce...","Wydaje się, że ci odbiło, chłopcze. Chciałeś trochę rozprostować ręce? Bez urazy, ale nie masz tu nic do roboty. Zmiataj!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomożesz mi rozwiązać ten problem...");
				link.l1.go = "pirate_town";
				break;
			}

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Gdzie mogę znaleźć Jimmy'ego Higginsa?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "To znowu ja, Jackman. Mówią, że szukasz kilku zaginionych ludzi...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Chodzi o twojego więźnia.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Cześć, Jackman. Co do twojej misji...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Chodzi o twojego więźnia.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", Cieszę się, że cię widzę! Czego chcesz?","Czego chcesz?","Znowu ty? Nie zawracaj ludziom głowy, jeśli nie masz nic do roboty!","Jesteś "+GetSexPhrase("dobry kaper"," dobra dziewczyna")+", więc możesz żyć na razie. Ale nie chcę już z tobą gadać.","powtórz",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Po prostu wpadłem z wizytą.","Nic..."," W porządku, Jackman, przepraszam...","Cholera! No cóż, jak mówisz...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Oszalałeś? Chciałeś pobawić się w rzeźnika? Wszyscy piraci są na ciebie wściekli, chłopcze, lepiej opuść to miejsce...");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomóż mi rozwiązać ten problem...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Chodzi o twojego więźnia.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Naprawdę! Komuś potrzebny ten leniwy drań! Od kilku dni pije sam rum w swojej chałupie. Nie radzę ci do niego zaglądać. Nawet na trzeźwo nie jest najlepszym człowiekiem...";
			link.l1 = "W porządku, ja też nie jestem święty. Gdzie jest jego chatka?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "To tuż przed tawerną. Wybrał dobre miejsce na szybkie wypady po drinka.";
			link.l1 = "Dzięki!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "A kto ci to powiedział? Ten pijany dureń Higgins? Dowiedziałeś się czegoś o Gladys Chandler albo Henryku Kat?";
			link.l1 = "Niczego szczególnego, ale chcę wiedzieć coś konkretnego o tym Kacie.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "Nie ma o czym wiedzieć. Teraz niewielu o nim pamięta, ale dwadzieścia lat temu Henry był bardzo popularny wśród dziwek od Bridgetown po Tortugę. Zakład? Bosman 'Neptuna', pod dowództwem samego kapitana Butchera! Musi być teraz naprawdę stary, jeśli wciąż żyje, oczywiście.\nSzanse są niskie, ale wiesz, nic nie jest niemożliwe. Zapłacę dwadzieścia tysięcy peso za jakiekolwiek informacje o nim, podwójnie, jeśli przyprowadzisz go tu żywego.";
			link.l1 = "Ile zapłacisz za Gladys i jej córkę?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Ach, to nie jest jej córka. Jeśli przyprowadzisz tę dziewczynę żywą, zapłacę ci kupę dublonów. Gladys mnie nie interesuje. Pytania?";
			link.l1 = "Chciałbym wiedzieć, z jakiego powodu to zamieszanie, ale nie będę pytał. Wygląda na to, że może skrócić moją biografię.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Być może... Te sekrety nie są twoją sprawą. Wiesz mniej, żyjesz dłużej. Nie próbuj zadawać mi takich pytań ponownie, bo zaczynam podejrzewać, że coś z tobą nie tak. Zmykaj, zanim zmienię zdanie.";
			link.l1 = "Do zobaczenia, baronie!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ha! Znów się spotykamy, kapitanie "+GetFullName(pchar)+"Przyznaję, jesteś godnym przeciwnikiem, mimo że próbujesz się przedstawiać jako prostak w Maroon-Town. Dowiedziałem się o tobie czegoś, twoje intrygi z Holenderską Kompanią Zachodnioindyjską zostały odkryte... Teraz rozumiem, jakim jesteś typem.";
			link.l1 = "Znam też twój typ, Jacob. Więc nie twórzmy złudzeń.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "A jakżeś mnie oszukał z tym 'Marlinem'! Przypuszczam, że mój biedny brat już nie żyje...";
			link.l1 = "Biorę to tak, że chcesz zemsty za niego? Ale mam również długą listę dla ciebie. Za osaczonego Nathaniela, jego żonę, jego fregatę, oszczerstwa na Sharku, Blaze Sharp...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze? Nie zabiłem go.";
			link.l1 = "Nawet jeśli to prawda, reszta mojej listy jest wystarczająca. Mam dość twojego imienia. Dość słów, Jackman! Nasze ostrza przemówią!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "Taki zapalczywy głupiec.. Do diabła z tobą! Teraz lepiej się trzymaj! Jacob Jackman nigdy nie został pokonany! Carpacho, jesteś w samą porę! Chodź tutaj!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ha-ha. Myślisz, że mam tu tylko jednego więźnia? Nazwij go.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Jest tutaj?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Był. Sprzedałem go temu właścicielowi plantacji z Barbadosu - pułkownikowi Bishopowi, gdy był tutaj tydzień temu.";
				link.l1 = "Cholera...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ach, w końcu. Już myślałem, żeby go sprzedać tamtemu właścicielowi plantacji z Barbadosu, będzie tutaj za tydzień lub dwa... Masz okup?";
				link.l1 = "Patrz, jest mały problem... W rzeczywistości nie mam aż tyle pieniędzy. Ale jestem gotów do pracy.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150.000 pesos. Gdzie mogę go dostać?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Byłeś zbyt wolny... A dlaczego ci na nim zależy? Rozmawiałem tylko z jego krewnymi.";
			link.l1 = "Prosili mnie, bym tu przyszedł.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Cóż, jesteś spóźniony. Nic nie mogę zrobić.";
			link.l1 = "Słuchaj, za ile go sprzedałeś, jeśli to nie tajemnica?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, nie jest. Ale ci nie powiem... Będziesz się śmiał, jeśli to zrobię. Ha-ha-ha-ha! Żegnaj.";
			link.l1 = "Do zobaczenia...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Cóż, cóż... Mam pewien interes... Nawet nie wiem, jak zacząć. Muszę zatopić jednego pirata, który przekroczył granicę.";
				link.l1 = "Nie można go po prostu zabić w dżungli?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Cóż, "+pchar.name+", wiesz, to tak nie działa. Wróć z pieniędzmi, a dostaniesz swojego słabeusza, ha-ha.";
				link.l1 = "Dobrze. Do zobaczenia.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "To nie jest sposób, w jaki działa interes, wiesz... Nie potrzebuję jego śmierci, muszę nauczyć niektórych ludzi, żeby trzymali się z dala od mojej części łupu. Ale jeśli pójdzie nakarmić rekiny, nie będę zasmucony.";
			link.l1 = "Dlaczego nie wyślesz swoich ludzi za nim?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Cóż, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+"przekonał kilku piratów, że ich część łupu jest przechowywana w naszym skarbcu niedaleko "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Generał")+". Ich dwa statki '"+pchar.GenQuest.CaptainComission.ShipName1+"' i '"+pchar.GenQuest.CaptainComission.ShipName2+"' podniósł kotwice niedawno i odpłynął do "+sLoc+"Teraz widzisz, dlaczego nie mogę zaufać moim ludziom, by wykonali tę robotę?";
			link.l1 = "Tak, mam. Ile mam czasu?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 do 15 dni, nie więcej, przypuszczam. Nie chcę, żeby dotarli do skrytki, bo byłoby bez sensu zatapiać ich z cennym ładunkiem. W takim przypadku lepiej, żeby go tutaj przywieźli...";
			link.l1 = "Dobrze, wchodzę w to. Spróbuję ich złapać.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Nie martw się. Moi ludzie dostarczą go na twój statek. A dlaczego się nim interesujesz?";
			link.l1 = "Nie. Jego krewni poprosili mnie, bym go dostarczył.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ach, to dobrze. Prawie mi było żal, że dałem tak niską cenę za twojego człowieka. Ha-ha-ha-ha. Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Więc, , "+GetFullName(pchar)+", zatopiłeś mojego kumpla? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nie. Nie udało mi się ich schwytać. I nie spotkałem ich po powrocie.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Zrobiłem to. Wysłałem ich na pożarcie rekinom.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Cholera! Spotkałeś ich czy nie, to teraz nie ma znaczenia! A jakie będzie twoje następne sugestia?";
			link.l1 = "Może masz dla mnie łatwiejsze zadanie?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Słuchaj, Jackman, obniż cenę za więźnia...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nie.";
			link.l1 = "Żegnaj zatem...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Zbić cenę? Właśnie straciłem swój skarb przez twoją nieudolność! I teraz mogę podnieść cenę! Możesz go wziąć za 200,000 pesos, jeśli chcesz, albo możesz się stąd wynosić do diabła.";
			link.l1 = "To za drogo... Żegnaj...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Do diabła, bierz swoje monety.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Dobrze, możesz wziąć tego słabeusza...";
			link.l1 = "Żegnaj.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Dobra robota! Zabierz swojego słabeusza i powodzenia.";
			link.l1 = "Dzięki. Żegnaj.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Przyniosłeś pieniądze, Charles? Nie żartowałem o sprzedaniu człowieka na plantację.";			
			link.l1 = "Słuchaj, "+NPChar.name+", jest problem... Nie mam tyle pieniędzy. Ale jestem gotów pracować.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150 000 pesos. Gdzie mogę go dostać?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rozbój!!! To jest nie do przyjęcia! Przygotuj się, "+GetSexPhrase("chłopcze","dziewczyna")+"... ","Ej, co do cholery tam robisz?! Myślałeś, że możesz mnie okraść? Już po tobie...","Poczekaj, co do cholery? Zabierz swoje łapy! Okazuje się, że jesteś złodziejem! To koniec, draniu...");
			link.l1 = LinkRandPhrase("Cholera!","Carramba!!","Cholera!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Odejdź stąd!"," Wynocha z mojego domu!");
			link.l1 = "Ojej...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Nie zawracaj mi głowy swoimi tanimi gadkami. Następnym razem nie spodoba ci się wynik...";
        			link.l1 = "Mam to.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "To koniec, bez gadania.""Nie chcę z tobą więcej rozmawiać, więc lepiej mnie nie zawracaj głowy.";
			link.l1 = RandPhraseSimple("Jak sobie życzysz...","Dobrze więc...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Mam nadzieję, że okażesz więcej szacunku i przestaniesz być niegrzeczny? W przeciwnym razie będę musiał cię zabić. To byłoby bardzo nieprzyjemne.";
        			link.l1 = "Możesz być pewien, Jackman, zrobię to.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Rozwiązać problem? Czy ty rozumiesz, co zrobiłeś? Tak czy inaczej, przynieś mi milion pesos, a przekonam chłopaków, żeby zapomnieli o twoich 'wyczynach'. Jeśli nie podoba ci się ten pomysł, to możesz iść do diabła.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Dobrze, jestem gotów zapłacić.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Zrozumiano. Wychodzę.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Dobrze! Uważaj się za oczyszczonego. Ale mam nadzieję, że nie będziesz już robić takich obrzydliwych rzeczy.";
			link.l1 = "Nie będę. Zbyt drogie dla mnie. Żegnaj...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}
