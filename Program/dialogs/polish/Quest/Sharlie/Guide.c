// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "Miło powitać pana w koloniach, panie! Pozwolę sobie się przedstawić: "+GetFullName(npchar)+". Czy przybywa pan z Europy? Pierwszy raz u nas?";
			link.l1 = "Dzień dobry, monsieur. Nazywam się "+GetFullName(pchar)+". Tak, właśnie zsedłem ze statku.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Widząc szlachetnego dworzan, uznałem za swój obowiązek zaoferować pomoc. Tutaj, w Nowym Świecie, panują swoje porządki — a ich nieznajomość może drogo kosztować, szlachetni ludzie tacy jak my powinni sobie pomagać. Nie uwierzyliby państwo, ile tutaj zebrało się wszelkiej maści szumowin, gotowych zdradzić bliźniego za garść monet\n"+
			"Czy mogę oprowadzić pana po mieście i krótko wprowadzić w sprawę?";
			link.l1 = "To bardzo szlachetne z pana strony, monsieur! Z radością przyjmę pana propozycję.";
			link.l1.go = "guide_2";
			link.l2 = "Dziękuję za troskę, panie, jestem panu naprawdę wdzięczny, ale myślę, że bez trudu we wszystkim się rozeznām sam.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Jak pan sobie życzy, monsieur. W każdym razie cieszyłem się z naszej znajomości. Szlachetni ludzie są tak rzadcy w tej głuszy. Wszystkiego dobrego i powodzenia!";
			link.l1 = "I panu również, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Wspaniale! Życie na Karaibach jest nieskomplikowane, a każda osada zbudowana jest według tych samych zasad. Jeśli oswoi się pan w Saint-Pierre — oswoi się w każdym innym mieście.";
			link.l1 = "";
			link.l1.go = "guide_tavern";			
		break;
		
		case "guide_tavern":
			dialog.text = "Tawerna — serce portu. Tutaj znajdzie pan nocleg, rum, plotki i będzie mógł najmować marynarzy i oficerów. A także — grać w karty, znaleźć pracę lub skorzystać z usług przemytników i handlarzy mapami skarbów.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Rynek. Towary do użytku osobistego zawsze można kupić na rynku. U zbrojmistrza — broń, zbroje i amunicja, u zielarki — lecznicze mikstury. Cyganki i mnisi handlują amuletami, a starociarz sprzedaje wszelkie graty, przydatne tym, którzy nie stronią od majsterkowania własnymi rękami.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Burdel. Nie ma lepszego lekarstwa dla ciała niż miłosne uciech w objęciach wprawnej kobiety. Jeśli zdrowie się zachwiało — zajrzyj tutaj, rozerwij się, otrzymaj porcję pieszczot i poczujesz się jak inny człowiek.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Bank. Dom lichwiarza. Można pożyczyć lub zainwestować pieniądze, wymienić pesos na dublony. A także — to najlepsze miejsce do sprzedaży klejnotów.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Więzienie. Prawdziwych przestępców jest tu niewielu — głównie wszelkie szumowiny. Jeśli chce pan znaleźć pracę wśród szumowin społecznych — porozmawiaj z komendantem. Za niewielką łapówkę może przepuścić do cel.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Pałac. Pałac najważniejszej osoby w kolonii — gubernatora. Ludzie interesu i kapitanowie przychodzą tutaj po poważną pracę. Być w dobrych stosunkach z gubernatorem — to wielka sprawa, bo od niego w dużej mierze zależy, jak będzie się do pana odnosić cały jego naród.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Spieszy się pan gdzieś, a ja pana zatrzymuję?";
			link.l1 = "Cóż... chyba tak. Monsieur, przybyłem tu, aby znaleźć swojego brata. Mówią, że jest gdzieś w Saint-Pierre. To ważna persona i z pewnością znana gubernatorowi...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Ah, rozumiem. Nasz gubernator nazywa się Jacques Dyel du Parquet. Jestem pewien, że przyjmie pana bez zwłoki.";
			link.l1 = "Kogo jeszcze mogę zapytać o mojego brata? Może nie powinienem niepokoić Jego Ekscelencji od razu?";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Jeśli pański brat jest rzeczywiście znany na Martynice — popytaj przechodniów. Może ktoś coś podpowie. Swoją drogą, jak on się nazywa?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "To imię obiło mi się o uszy, ale niestety nie miałem zaszczytu być przedstawionym osobiście. Proszę popytać w mieście — albo udać się prosto do gubernatora. Powodzenia, monsieur. Na pewno jeszcze się spotkamy i pogawędzimy!";
			link.l1 = "Dziękuję, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "O, to znowu pan, mój przyjacielu! Widzę, że został pan dopuszczony do świętego świętych Saint-Pierre — twierdzy rycerzy maltańskich. Wszystko wskazuje na to, że jest pan ptakiem wysokiego lotu. Znalazł pan brata?";
			link.l1 = "No cóż, znalazłem...";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Przepraszam za natarczywość, monsieur, ale wydaje mi się, że nie słyszę radości w pana głosie...";
			link.l1 = "To prawda, panie. Liczyłem na to, że stąd wrócę do Francji najbliższym statkiem, ale los najwyraźniej postanowił sobie ze mnie zakpić: zostaję tu na długo... nie, do diabła — na nieokreślony czas! I, wyobraża pan sobie, w dodatku muszę zostać marynarzem, pfe!";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Z jakiegoś powodu nie jestem zaskoczony. Słyszałem już o pańskiej przygodzie na pinasie 'Ulysse'. Niech pan nie traci ducha — bycie właścicielem własnego statku i kapitanem jest bardzo zaszczytne. Zamierza pan kupić statek, prawda?";
			link.l1 = "Tak, do diabła, właśnie to muszę zrobić... Zostało tylko znaleźć stocznię i jakoś zebrać pieniądze. Ale nie wiem ani gdzie jest stocznia, ani jak sterować statkiem, ani skąd wziąć pieniędzy — nic!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Z pieniędzmi, niestety, nie mogę pomóc — sam jestem teraz spłukany. Ale w pozostałych kwestiach — jestem do usług. Gotów pan kontynuować wycieczkę?";
			link.l1 = "Tak, chyba tak, przecież nie bez powodu mówią: wiedza to potęga.";
			link.l1.go = "guide_25";
			link.l2 = "Dziękuję z całego serca, monsieur, ale dalej poradzę sobie sam.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "È stato un piacere conoscervi. E per quanto riguarda i soldi per la nave — parlate con le persone influenti della città. Per esempio, con il mercante nel negozio.\n"+
			"Buona fortuna, "+pchar.name+" — siate audace e ce la farete.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Więc proszę za mną! Zacznijmy od podstaw — od statków.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Stocznia. Tutaj kupuje się i naprawia statki. Wybór niewielki — głównie drobiazgi, ale czasem trafiają się poważne jednostki. Można tu też kupić armaty i ozdobić żagle.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Molo - brama do morza. Jak tylko będziesz miał statek — będzie tu na ciebie czekała szalupa. A na razie polecam zatrudnić nawigatora, kwatermistrza i kanoniera — z nimi będziesz czuł się pewniej na morzu.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Tutaj możesz zostawić statek na postoju, a także znaleźć uczciwą pracę dla kapitana: fracht, eskortę, dostawę poczty. Im więcej zadań wykonasz - tym bardziej opłacalne się staną.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Sklep. Kapitanowie bywają tu najczęściej - po zapasy, rum, lekarstwa, proch i amunicję. Jeśli czegoś brakuje - szukaj przemytników w tawernie. Ale pamiętaj: bez dobrego skarbnika handel to strata czasu i pieniędzy.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Jeśli molo to brama na morze, to tu jest brama do dziczy. Niebezpiecznie, ale niezbędne, gdy musisz dostać się do fortu, znaleźć skarb lub przejść lądem do innej osady.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Pamiętaj, że nie we wszystkich koloniach będziesz mile widziany. Jeśli nie chcesz czekać na noc, by przeniknąć wrogą kolonię, najpierw podnieś inny sztandar na statku, a potem polegaj na umiejętności skradania się lub kup licencję handlową.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Jesteś świetnym słuchaczem, mój przyjacielu. A może dla rozrywki? Proponuję treningowy pojedynek za bramą.";
			link.l1 = "Oczywiście! To będzie idealnie.";
			link.l1.go = "guide_47";
			link.l2 = "Serdeczne dzięki, monsieur, ale dalej poradzę sobie sam.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Amico mio, suppongo che non siate un principiante nella scherma?";
			link.l1 = "Ah! Ho già superato un abbordaggio e persino...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Ottimo. Iniziamo?";
			link.l1 = "Balliamo!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "Ty... ty jesteś człowiekiem, który wie, jak trzymać swój miecz. Dobrze zrobione, Monsieur. Potrzebujesz więcej praktyki, ale masz potencjał, by stać się prawdziwym mistrzem szermierki.";
			link.l1 = "Dziękuję bardzo. Co teraz?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "Więcej ćwiczeń mówisz? Jesteś poważny? Mam dość tego protekcjonalnego tonu odkąd tylko postawiłem stopę w tym nędznym miejscu!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Znacznie lepiej! Widzisz, wystarczy się skoncentrować. Potrzebujesz więcej praktyki, pewnego dnia staniesz się przyzwoitym szermierzem.";
			link.l1 = "Dziękuję bardzo. Co teraz?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "Wygrałem, Monsieur. Ruchy szybciej, paruj moje pchnięcia, odskocz. Rewanż?";
			link.l1 = "Oui! Bez litości, Monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "Nie, wystarczy. Skończmy lekcję. Co teraz?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "Znowu wygrałem, "+pchar.name+"! Nie trać inicjatywy. Chwytaj moje uderzenia, zwódź je. Jeśli widzisz, że zamierzam uderzyć mocno - odskocz lub sparuj, nie tylko się broń. Jeszcze raz!";
			link.l1 = "Chodź, monsieur, tym razem cię zleję!";
			link.l1.go = "guide_56";
			link.l2 = "Nie, mam już dość. Zakończmy lekcję. Co teraz?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "Musisz się jeszcze wiele nauczyć, "+pchar.name+"Nie martw się, masz jeszcze dużo czasu, aby opanować szermierkę. Ale bądź ostrożny, nie ryzykuj, dopóki nie nauczysz się trzymać broni.";
			link.l1 = "Rozważę to, Monsieur, ale muszę przyznać, że miałeś po prostu za dużo szczęścia! To przeklęte upał... jedyny powód, dla którego nie obiłem cię po pysku. Merde, zakończmy naszą lekcję szermierki. Co teraz?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Teraz czas się pożegnać, Monsieur. To była przyjemność. Mam nadzieję, że moja prezentacja i szkolenie przyniosły ci trochę korzyści i okażą się przydatne w przyszłości. Być może, pewnego dnia znowu się spotkamy.\nA co do pieniędzy, których potrzebujesz - porozmawiaj z ważnymi ludźmi naszego miasta. Odwiedź wszystkie miejsca, które ci dziś pokazałem i porozmawiaj z ich właścicielami. Dopytuj się. Wybierz się na spacer do dżungli i do fortu. Znajdź pracę albo... cóż, nie jestem księdzem ani sędzią, sprawdź domy ludzi i zobacz, jakie błyskotki znajdziesz w ich niezamkniętych skrzyniach. Po prostu zrób to, gdy są odwróceni plecami, albo strażnicy cię złapią.\nPowodzenia, "+pchar.name+", Mam silne przeczucie, że masz w sobie iskrę prawdziwej wielkości. Zrób wszystko, co w twojej mocy, by rozniecić ją w płonący ogień!";
			link.l1 = "Dziękuję, Monsieur. Przyjemność po mojej stronie. Szczęśliwej drogi!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Trzymaj język za zębami, Monsieur! Nie będę dłużej tolerować takiej bezczelności. Jednakże, rozumiem twoją reakcję na nowe otoczenie, dlatego tym razem wybaczam twoje wybuchy. Ale od teraz pilnuj swoich słów. Żegnaj, Monsieur de Maure.";
			link.l1 = "Bez obrazy, Monsieur Valinnie. Gdybyśmy byli teraz w Luwrze, uważałbyś na swój ton! Czas nauczyć prowincję ostatniej lekcji. Broń się!";
			link.l1.go = "guide_65";
		break;
		
		case "guide_65":
			DialogExit();
			
			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE*10+300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}