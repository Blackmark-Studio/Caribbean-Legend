void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chciałeś czegoś?";
			link.l1 = "Nie, nic takiego.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "Ładnie, prawda?";
			link.l1 = "To piękno próbuje mnie zabić już od dwóch miesięcy. Jak dotąd bezskutecznie.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Bardzo. Czasami ocean przypomina, jak mali jesteśmy wobec natury.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "Nauczyłem się, że na morzu są tylko dwa stany: nuda albo terror.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "StartSailor_1_fencing":
			dialog.text = "Ha! Pierwszy raz na morzu, monsieur? Kiedy jest tak spokojnie, każdy może pobawić się w kapitana. Więc korzystaj z okazji.";
			link.l1 = ""+GetFullName(pchar)+". Szlachcic, nawiasem mówiąc. Nie 'monsieur', ale panicz.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "StartSailor_1_leadership":
			dialog.text = "Ha! Pierwszy raz na morzu, monsieur? Kiedy jest tak spokojnie, każdy może pobawić się w kapitana. Więc korzystaj z okazji.";
			link.l1 = ""+GetFullName(pchar)+". Szlachcic, nawiasem mówiąc. Nie 'monsieur', ale panicz.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_1_fortune":
			dialog.text = "Ha! Pierwszy raz na morzu, monsieur? Kiedy jest tak spokojnie, każdy może pobawić się w kapitana. Więc korzystaj z okazji.";
			link.l1 = ""+GetFullName(pchar)+". Szlachcic, nawiasem mówiąc. Nie 'monsieur', ale panicz.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_2":
			dialog.text = "Jak sobie pan życzy. A więc to pierwszy taki rejs dla pana, panie "+pchar.lastname+"?";
			link.l1 = "Czy to takie oczywiste? Tak, pierwszy raz. I nie jestem stworzony do ciasnych kajut i zgniłych sucharów.";
			link.l1.go = "StartSailor_3";
		break;

		case "StartSailor_3":
			dialog.text = "Widać jak na dłoni, że pan to szczur lądowy, panie.";
			link.l1 = "Pilnuj języka! Człowiekowi honorowemu rzuciłbym rękawicę i zażądał satysfakcji. Ale wieśniakowi takiemu jak ty - po prostu utnę uszy.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "Może w Paryżu. Ale tutaj takie słowa mogą człowieka wysłać na pożarcie rybom. Nie machałbym tą szpadą na prawo i lewo, panie - i niech pan nie sprawi, że kapitan pożałuje, że pozwolił panu chodzić uzbrojonym po pokładzie. Ostatniego awanturnika wysłał do ładowni - na spleśniałe suchary i szlam, którego nawet szczury nie chciały pić. I wie pan co? Biedak musiał jeszcze dopłacić, gdy dotarliśmy do portu.";
			link.l1 = "Czego się można spodziewać... Dobrze, zapomnijmy o tym nieporozumieniu. Muszę sobie ciągle przypominać, że ta łajba to nie Luwr.";
			link.l1.go = "StartSailor_5";
		break;

		case "StartSailor_5":
			dialog.text = "Eh? Luwr? Co to ma być?";
			link.l1 = "Ha! Luwr to miejsce dla wybranych. Bale, przyjęcia, intrygi...";
			link.l1.go = "StartSailor_6";
		break;

		case "StartSailor_6":
			dialog.text = "A-a... burdel więc. Mamy ich pod dostatkiem. Nie można powiedzieć, żeby były dla wybranych - płać i wszystko będzie twoje.";
			link.l1 = "Ha! Niedaleko ci do prawdy, marynarzu.";
			link.l1.go = "StartSailor_7";
		break;

		case "StartSailor_7":
			dialog.text = "A tak w ogóle, to na imię mi Alonso. I cóż takiego zaprowadziło pana na koniec świata, panie? Wątpię, żeby pan przepłynął Atlantyk tylko po to, by sprzeczać się ze zwykłym marynarzem.";
			link.l1 = "Mój ojciec jest chory i nie może opuścić naszej posiadłości w Gaskonii. Mam za zadanie odnaleźć mojego... starszego brata. Wyruszył tu w interesach i od dawna nie daje znaku życia.";
			link.l1.go = "StartSailor_8";
		break;

		case "StartSailor_8":
			dialog.text = "A czemu po prostu nie posłać zaufanego człowieka, zamiast samemu znosić trudy morskiej podróży?";
			link.l1 = "Rodzina jest najważniejsza. Nie mogę powierzyć jej losu pierwszemu lepszemu.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "Chętnie bym to zrobił – ale według ojca to właśnie ja powinienem się tym zająć. Dlaczego – nie mam pojęcia.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "A jak nazywa się pański brat?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "StartSailor_9_nobilityminus":
			dialog.text = "A jak nazywa się pański brat?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "StartSailor_10":
			dialog.text = "De Monper? A pan to "+pchar.lastname+"? Jak to możliwe?";
			link.l1 = "Nie patrz się tak na mnie. Jestem prawowitym synem. Po prostu noszę nazwisko matki.";
			link.l1.go = "StartSailor_11";
		break;

		case "StartSailor_11":
			dialog.text = "Nie ma się czego wstydzić. Wpisze się pan idealnie – w Nowym Świecie co drugi ma jakąś historię. Ja, na przykład...";
			link.l1 = "Wcale się nie wstydzę! Lepiej opowiedz mi o Martynice. To duże miasto? Coś jak Tuluza?";
			link.l1.go = "StartSailor_12";
		break;

		case "StartSailor_12":
			dialog.text = "Miasto? Ha! Martynika to cała wyspa. Jedna z największych francuskich posiadłości na Karaibach. Uprawiają tam ognista kawę, wydobywają piekielną siarkę i rodzą najpiękniejsze kobiety świata. Świetna mieszanka, jak dla mnie.";
			link.l1 = "Kawa i siarka mnie nie interesują. Ale zaraz... wyspa? Jak ja znajdę brata na całej wyspie?";
			link.l1.go = "StartSailor_13";
		break;

		case "StartSailor_13":
			dialog.text = "Nie przejmuj się tak. Saint-Pierre to niewielkie miasteczko – nie Luwr, oczywiście, ale i nie dżungla. A w bandyckim Le François, nie daj Boże – porządny człowiek nie ma czego szukać.";
			link.l1 = "Jeśli zajdzie potrzeba – odwiedzę i bandytów. Michelle zawsze ratował mnie z kłopotów. Teraz moja kolej.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "Nieźle powiedziane... jak na szczura lądowego.";
			link.l1 = "Znowu to samo? Ile jeszcze do tej przeklętej Martyniki?";
			link.l1.go = "StartSailor_15";
		break;

		case "StartSailor_15":
			dialog.text = "Z pięć dni.";
			link.l1 = "Pięć?!";
			link.l1.go = "StartSailor_16";
		break;

		case "StartSailor_16":
			dialog.text = "To co najmniej. A jak zaatakują piraci – możemy w ogóle nie dotrzeć. Małe Antyle to niebezpieczne miejsce, nawet bez cennego ładunku na pokładzie.";
			link.l1 = "Poza pasażerami!";
			link.l1.go = "StartSailor_17";
		break;

		case "StartSailor_17":
			dialog.text = "Ha-ha! Nie martw się. W najgorszym razie osobiście schowam cię w ładowni – żaden pirat nie wpadnie na to, żeby szukać gaskońskiego szlachcica wśród beczek z rumem! Przecież nie jesteśmy głupi – mieszać żywego Gaskończyka z rumem. Wybuchnie jak proch, ha-ha!";
			link.l1 = "Ha! Całe szczęście, że rum skończył się już miesiąc temu!";
			link.l1.go = "StartSailor_18";
		break;

		case "StartSailor_18":
			dialog.text = "E... takich rzeczy lepiej nie mówić przy ludziach. Jeszcze pomyślą, że to przez ciebie nie mamy już rumu.";
			link.l1 = "Dobra, Alonso, nie będę. I tak tego świństwa nigdy nie wziąłbym do ust. A co do twojego genialnego planu schować mnie w ładowni przed bitwą – nie ma mowy.";
			link.l1.go = "StartSailor_20";
		break;

		case "StartSailor_20":
			dialog.text = "A to niby czemu?";
			link.l1 = "Jestem szlachcicem, potrafię dobrze władać szpadą i nie będę siedział w ładowni.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Jeśli dojdzie do walki – będę bronić statku razem z innymi. A jak inaczej?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Sam zdecyduję – czy walczyć, czy uciekać. Zobaczymy, jak się sytuacja rozwinie.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ha. Może rzeczywiście coś w tobie jest. Ale uważaj — Karaiby lubią zdzierać skórę z tych, którzy chodzą z zadartym nosem. Pierwszego kontaktu z piratami możesz nie przeżyć. Powiem więcej — pierwszy obdartus za bramą Saint-Pierre poderżnie ci gardło.";
			link.l1 = "Wcale mnie nie znasz.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "StartSailor_21_leadership":
			dialog.text = "Ha. Może rzeczywiście coś w tobie jest. Ale uważaj — Karaiby lubią zdzierać skórę z tych, którzy chodzą z zadartym nosem. Pierwszego kontaktu z piratami możesz nie przeżyć. Powiem więcej — pierwszy obdartus za bramą Saint-Pierre poderżnie ci gardło.";
			link.l1 = "Wcale mnie nie znasz.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_21_fortune":
			dialog.text = "Ha. Może rzeczywiście coś w tobie jest. Ale uważaj — Karaiby lubią zdzierać skórę z tych, którzy chodzą z zadartym nosem. Pierwszego kontaktu z piratami możesz nie przeżyć. Powiem więcej — pierwszy obdartus za bramą Saint-Pierre poderżnie ci gardło.";
			link.l1 = "Wcale mnie nie znasz.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_22":
			dialog.text = "Ale ja znam Nowy Świat i jego mieszkańców. Jeśli nie zamierzasz siedzieć nad księgami albo usługiwać gubernatorowi – będziesz musiał wszystkiego uczyć się od zera.";
			link.l1 = "Dobrze, że nie zamierzam tu długo zostawać.";
			link.l1.go = "StartSailor_23";
		break;

		case "StartSailor_23":
			dialog.text = "Tobie się tylko tak wydaje. Rzadko zabieramy pasażerów z powrotem do Europy. Jedni umierają — na febrę, przez stryczek albo kulę. Inni zostają — na zawsze. Widziałem, jak cherlawi arystokraci stawali się kapitanami, a zatwardziali bandyci — szanowanymi plantatorami. I jak błyskotliwi oficerowie staczali się do poziomu żebraków.";
			link.l1 = "Brzmi kusząco, do diabła, ale wrócę do Francji. Czekają tam na mnie.";
			link.l1.go = "StartSailor_24";
		break;

		case "StartSailor_24":
			dialog.text = "Ach tak, racja. Chory ojciec?";
			link.l1 = "Powiedzmy... jest pewna dama, której mąż nie chce mnie za bardzo widzieć w Paryżu. Ale za parę miesięcy wszystko ucichnie.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "Ha-ha-ha! W takim razie naprawdę jesteś we właściwym miejscu. Karaiby to raj dla tych, którzy uciekają przed zazdrosnymi mężami. A czas tutaj płynie niepostrzeżenie. Daj sobie trochę czasu — jeszcze zostaniesz marynarzem!";
			link.l1 = "Prędzej już kapitanem. Żaden ze mnie marynarz. Nie jestem stworzony do pracy fizycznej.";
			link.l1.go = "StartSailor_26";
		break;

		case "StartSailor_26":
			dialog.text = "We Francji to ludzie z urodzenia rządzą, a na statku — kapitan: król, sędzia i Bóg. I nikt nie wie, przez co musiał przejść, żeby zasłużyć na kapitańską czapkę. Tutaj każdy dostaje to, na co zasłuży. Jak mówimy na pokładzie — każdemu według zasług.";
			link.l1 = "Co za nonsens. A propos kapitanów — muszę porozmawiać z twoim. W końcu to on mnie szukał. Do zobaczenia, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Chciałeś mnie o coś zapytać?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Przysyła mnie monsieur Pinchon.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Nie, nie.";
			link.l2.go = "AlonsoWait_2";
		break;

		case "AlonsoGold_2":
			dialog.text = "O, nasz czterooki i ciebie w to wciągnął?";
			link.l1 = "Czterooki?";
			link.l1.go = "AlonsoGold_3";
		break;

		case "AlonsoGold_3":
			dialog.text = "Widziałeś jego okulary? No właśnie! Ale nie myśl sobie – załoga monsieur Pinchona bardzo szanuje. Dobrych lekarzy na pokładzie zawsze się ceni. A i jako skarbnik jest niezły.";
			link.l1 = "Co cię z nim łączy?";
			link.l1.go = "AlonsoGold_4";
		break;

		case "AlonsoGold_4":
			dialog.text = "Eee... Przepraszam, to nasza wewnętrzna sprawa. Ale nie bój się – prawa okrętowego nie łamiemy.";
			link.l1 = "A prawa lądowego?";
			link.l1.go = "AlonsoGold_5";
		break;

		case "AlonsoGold_5":
			dialog.text = "A tym się nie przejmujemy. No i ile tam wyszło?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 dublonów.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 dublonów.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 dublonów.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "Muszę wszystko sprawdzić. Wrócę później.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "No proszę, złotko. Trzymaj się, Saint-Pierre! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "No proszę, złotko. Trzymaj się, Saint-Pierre! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "No proszę, złotko. Trzymaj się, Saint-Pierre! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ach, "+pchar.name+". Niezbyt się pan spieszył. Jeśli kapitan statku chce z panem rozmawiać, pan ma się natychmiast stawić. Ma pan problem z wykonywaniem rozkazów?";
			link.l1 = "Nie jestem przyzwyczajony do rozkazów, kapitanie.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Przepraszam, kapitanie, coś mnie zatrzymało.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Już mi wyjaśniono, że na tym statku obowiązują pana zasady.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (pomiń samouczek i rozpocznij grę na Martynice)";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;

		case "Captain_2_fencing":
			dialog.text = "Nie pozwolę, by kwestionowano mój autorytet. Nawet pan sobie nie wyobraża, jak często coś złego przytrafia się pasażerom na morzu. Ma pan niesamowite szczęście, że zależy mi na tym, by bezpiecznie dostarczyć pana do Saint-Pierre.";
			link.l1 = "O czym pan mówi?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Captain_2_leadership":
			dialog.text = "Przeprosiny przyjęte. Ciesz się chwilą. Rzadko będzie panu dane podziwiać taki zachód słońca.";
			link.l1 = "O czym pan mówi?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Captain_2_sailing":
			dialog.text = "Dobrze, że chociaż czegoś się pan nauczył podczas tej podróży. Władza kapitana jest absolutna, czasem nawet sięga lądu, daleko poza pokład.";
			link.l1 = "O czym pan mówi?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Kapitan. Proszę się do mnie zwracać zgodnie z regulaminem morskim.";
			link.l1 = "O co panu chodzi, kapitanie?";
			link.l1.go = "Captain_4";
		break;

		case "Captain_4":
			dialog.text = "Chciałem tylko powiedzieć, że opuściliśmy żagle i dryfujemy. Niestety, pańskie przybycie na Martynikę opóźni się o kilka dni.";
			link.l1 = "Dlaczego, kapitanie?";
			link.l1.go = "Captain_5";
		break;

		case "Captain_5":
			dialog.text = "Bo tak postanowiłem.";
			link.l1 = "Czy to ma coś wspólnego z naszą wczorajszą wizytą w karawanie handlowej, która płynęła do... no, jak to się nazywało...";
			link.l1.go = "Captain_6";
		break;

		case "Captain_6":
			dialog.text = "Capsterville. Słuchaj, "+pchar.name+": musimy porozmawiać na poważnie. Zapraszam cię na kolację do mojej kajuty. Zaraz wybije czas, więc spędzimy ten wieczór jak cywilizowani ludzie — dopijając ostatnią butelkę wina na statku.";
			link.l1 = "Dziękuję za zaproszenie. To dla mnie zaszczyt, kapitanie.";
			link.l1.go = "Captain_7";
		break;

		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Daj mi znać, kiedy będziesz gotów. Mamy jeszcze trochę czasu, więc możesz swobodnie pochodzić po statku — pod warunkiem, że nie będziesz przeszkadzać moim ludziom w pracy.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "Jeszcze jakieś pytania?";
			link.l1 = "(Zakończ sprawy) Jestem gotów, kapitanie. Z panem wypiję nawet burgunda!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Co tam pan tak uważnie obserwuje przez lunetę... kapitanie?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Kapitanie, miałem przyjemność porozmawiać z Alonso. Jaką pełni funkcję na statku?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Kapitanie, proszę opowiedzieć o tym statku. To pinasa, prawda?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "Do zobaczenia, kapitanie.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Nic konkretnego, po prostu obserwuję horyzont. Statek dryfuje – jesteśmy łatwym łupem.";
			link.l1 = "Szukasz piratów?";
			link.l1.go = "Captain_7_question_1_2";
		break;

		case "Captain_7_question_1_2":
			dialog.text = "Albo Hiszpanów. Płyniemy pod francuską banderą i bez eskorty, a Małe Antyle to prawdziwy korytarz i domena Jacquesa Barbazona.";
			link.l1 = "Kto to? Gubernator?";
			link.l1.go = "Captain_7_question_1_3";
		break;

		case "Captain_7_question_1_3":
			dialog.text = "Gorzej – jeden z baronów pirackich. Te szubrawce stworzyli coś na kształt organizacji i nazywają się Bractwem Wybrzeża. Podzielili Karaiby na sześć części i wyznaczyli na każdą barona, by nie gryźć się nawzajem.";
			link.l1 = "Dlaczego władze nic z tym nie robią?";
			link.l1.go = "Captain_7_question_1_4";
		break;

		case "Captain_7_question_1_4":
			dialog.text = "Jesteś naiwny, "+pchar.name+". Piractwo istnieje tylko dlatego, że lokalne władze pozwalają im naprawiać i zaopatrywać statki w wybranych portach w zamian za większość łupów. Niechętnie to przyznaję, ale jedyni, którzy coś z tą czarną zarazą robią – to Hiszpanie. Gdyby nie oni, trzeba by było nie tylko wyposażyć statek w drogie działa, ale jeszcze wynajmować eskortę.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Captain_7_question_2_1":
			dialog.text = "Starszy marynarz. Niewiele o nim wiem, ale jedno jest pewne – jeśli każdy człowiek ma w szafie trupa, to Alonso ma z pewnością całe cmentarzysko.";
			link.l1 = "Brzmi jakbyś mu nie ufał.";
			link.l1.go = "Captain_7_question_2_2";
		break;

		case "Captain_7_question_2_2":
			dialog.text = "Wcale nie. Myślisz, że łatwo znaleźć doświadczonych ludzi do załogi? Trzeba co najmniej roku i świetnego bosmana, żeby zbieranina z karczmy zaczęła przypominać załogę. Poza tym Alonso to głos załogi. Kapitan nie musi gadać z pospólstwem, ale byłoby głupotą i śmiertelnym zagrożeniem nie brać pod uwagę, że zwykli marynarze też mają swoje interesy. On je reprezentuje.";
			link.l1 = "A co jeśli załoga jest niezadowolona?";
			link.l1.go = "Captain_7_question_2_3";
		break;

		case "Captain_7_question_2_3":
			dialog.text = "Mnie powieszą, a ciebie – po prostu zaszlachtują. Ale nie drżyj tak. Dopóki załoga dostaje żołd, rum, prowiant i leczenie – kontrakt między kapitanem a załogą jest dotrzymany. Nie ryzykuję ich życia bez potrzeby, nie karzę z kaprysu, dzielę się łupem i czasem częstuję darmową gorzałą i innymi uciechami na lądzie. Tak zachowujemy kruchą równowagę, a statek zawsze dociera do celu.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "Trafiłeś w czuły punkt, "+pchar.name+"! O mojej piękności mogę gadać bez końca. Trzecia klasa, dwadzieścia dział, doskonała prędkość — nie daj się zwieść, że 'kupiecki'!";
			link.l1 = "Działa i prędkość — jasne. A co to za 'klasa'? 'Kupiecki'?";
			link.l1.go = "Captain_7_question_3_2";
		break;

		case "Captain_7_question_3_2":
			dialog.text = "Klasy — to umowny podział statków według liczby dział. Siódma klasa to ledwo łódka, a pierwsza to już niemal forteca. Ale nie powtarzaj tego w Europie, zwłaszcza przy oficerach marynarki.";
			link.l1 = "Dlaczego? To jakiś morski dowcip?";
			link.l1.go = "Captain_7_question_3_3";
		break;

		case "Captain_7_question_3_3":
			dialog.text = "Uznać cię mogą za kompletnego dyletanta i wyśmiać. Szczerze mówiąc, na poważnych flotach klasy dział dotyczą tylko okrętów wojennych. Ale tu, na Karaibach, jak zwykle, wszystko jest po naszemu.";
			link.l1 = "A co miałeś na myśli, mówiąc że twój statek jest 'kupiecki'?";
			link.l1.go = "Captain_7_question_3_4";
		break;

		case "Captain_7_question_3_4":
			dialog.text = "To też umowny termin. Okręty wojenne są wytrzymalsze i mają lepszą artylerię, korsarze — rabują i uciekają. Kupieckie — mogą przewozić dużo ładunku, załogi lub dział, ale trzeba coś poświęcić, inaczej ich prędkość będzie śmieszna. Są jeszcze uniwersalne jednostki, ale o nich trudno coś konkretnego powiedzieć poza tym, że dostosowują się do potrzeb właściciela.";
			link.l1 = "Aż się ożywiłeś, kapitanie.";
			link.l1.go = "Captain_7_question_3_5";
		break;

		case "Captain_7_question_3_5":
			dialog.text = "Kocham mój statek, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;

		// теперь можно пострелять из пушки
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "To masz szczęście — zostało mi tylko burgundzkie... Zaczekaj, "+pchar.name+". Skąd masz mój stary kapelusz?!\nCzekajcie. Hej, na masztach! Co tam macie?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "To masz szczęście — zostało mi tylko burgundzkie\nCzekajcie. Hej, na masztach! Co tam macie?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Przepraszam, panie de Maure, ale tam wejść nie można.";
			link.l1 = "Mam wstęp do kajuty kapitana. Mógłbyś to już zapamiętać.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Szkoda, że mój nikczemny plan się nie powiódł. Żegnaj, marynarzu.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;

		case "OhrannikCabin_1":
			dialog.text = "Przepraszam, panie, ale sytuacja się zmieniła.";
			link.l1 = "A co się właściwie stało?";
			link.l1.go = "OhrannikCabin_2";
		break;

		case "OhrannikCabin_2":
			dialog.text = "Do końca rejsu już niedaleko, a kapitan nie chce, by ktoś ogołocił jego dobra i potem bezkarnie zniknął u bandytów w Le François.";
			link.l1 = "Wątpię, żeby kapitan miał mnie na myśli, wydając ten rozkaz.";
			link.l1.go = "OhrannikCabin_3";
		break;

		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "W sumie... ma pan rację. I jadał już pan w kajucie kapitana nieraz. Proszę, panie de Maure.";
					link.l1 = "No właśnie!";
					link.l1.go = "OhrannikCabin_4";
					notification("Test zaliczony", SKILL_Leadership);
				}
				else
				{
					dialog.text = "Ins... Insynu... Co? Niczego takiego nie miałem na myśli, panie de Maure!";
					link.l1 = "To znaczy, że masz obowiązek mnie przepuścić.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Panie, sam pan rozumie, że kajuta kapitana to nie przechodni pokój. A z rozkazami nie ma żartów.";
					link.l1 = "Do licha, byle do lądu. To po prostu upokarzające!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Panie, już to omawialiśmy. Nie mogę pana przepuścić.";
					link.l1 = "Aleś uparty, marynarzu. Żegnaj.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Za mało rozwinięta umiejętność (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Ehh. No dobrze, sądzę, że wielkiej szkody z tego nie będzie.";
			link.l1 = "Właśnie!";
			link.l1.go = "OhrannikCabin_4";
			notification("Test zaliczony", SKILL_Leadership);
		break;

		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;

		case "OhrannikCabin_again":
			dialog.text = "Jeszcze coś, panie? Nie mogę pana przepuścić — kapitan obawia się o swoje dobra.";
			link.l1 = "Co to ma znaczyć, marynarzu, sugerujesz kradzież? Uważaj na język. Czysta insynuacja!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Nic, marynarzu.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Hej, szlachetny idioto! Co ty wyczyniasz z kabestanem?!\nSwoją szlachecką nóżką zerwałeś blokadę! Chciałeś nas wszystkich posłać na dno, co?!\nZrób nam przysługę i niczego nie dotykaj, chyba że to francuski katar!";
			link.l1 = "A co to właściwie jest?";
			link.l1.go = "SailorWithWindlass_2";
		break;

		case "SailorWithWindlass_2":
			dialog.text = "To kabestan, dzbanie. Służy do podnoszenia kotwicy. A jak go nie zablokujesz, to rozerwie statek na strzępy albo owinie kogoś liną jak śledzia w beczce!";
			link.l1 = "Ha... A jak w drugą stronę, to opuszcza kotwicę, tak?";
			link.l1.go = "SailorWithWindlass_3";
		break;

		case "SailorWithWindlass_3":
			dialog.text = "Nie, mądraliński, wtedy cofa czas. Tylko żeś się już urodził — i masz pecha!";
			link.l1 = "No cóż, nikt nie ucierpiał — prawda? Statek to zadziwiająco skomplikowana rzecz. Będę ostrożniejszy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Patrzysz na tę lufę armaty z takim samym zachwytem, z jakim niedawno wpatrywałeś się w zachód słońca.";
			link.l1 = "Widzę, że lubisz mnie obserwować, Alonso. Lepiej powiedz coś więcej o tym cudzie sztuki wojennej.";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "To szesnastofuntówka. Nawet na wielu okrętach wojennych nie uświadczysz takiej.";
			link.l1 = "A łatwo z niej trafić?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "Z bliska rozwalimy każdego. Sto jardów i już możemy działać. Dalej to już tylko hałas i ogień, ale i to dobre.";
			link.l1 = "Sto jardów — i wróg może zrobić to samo.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "Zgadza się. Ale wtedy liczy się, która załoga jest lepiej zgrana i kto ma lepszych artylerzystów. Szkoda, że nasz kanonier teraz śpi — to by ci wszystko opowiedział, a potem sam by cię załadował do działa, ha-ha!";
			link.l1 = "Kanonier to też oficer?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "Zazwyczaj tak. Bez choćby średnio ogarniętego kanoniera lepiej nie wdawać się w bój — lepiej od razu wyrzucić działa za burtę i w nogi\nKupieccy kapitanowie rzadko mają coś większego niż sześciufuntówki — liczą na eskortę albo szczęście\nI słusznie: bez ciężkich dział i amunicji statek lepiej płynie, a i więcej towaru do ładowni się zmieści\nGdyby nasz kapitan nie wydał się na te piękności — może i rum by się nie skończył. Ech!";
			link.l1 = "A kapitan sam nie kieruje ogniem?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "Z dobrym kanonierem i zgraną załogą nie musi. Ale powiem ci tak: jak kapitan sam celuje, a nie tylko wrzeszczy z nadbudówki 'Ognia!' — to dziur w wrogim kadłubie robi się więcej.";
			link.l1 = "Mogę strzelić?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Dzięki za fascynującą lekcję, Alonso. Jesteś prawdziwą skarbnicą morskiej wiedzy.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Oczywiście! Ale mimo wszystko — nie dotykaj działa i nie denerwuj załogi.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "Strzelić? Mało prawdopodobne. Ale oddać salwę — to trzeba zapytać kapitana. Już pytam!";
			link.l1 = "Nie trzeba!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "Kapitaaan!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;

		case "CaptainWithCannon_1":
			dialog.text = "O co biega, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "Pan "+pchar.name+" proponuje oddać salwę z działa — wyłącznie w celach szkoleniowych.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_5":
			dialog.text = "Myślałem, że dbasz o interesy załogi, Alonso. Proponujesz obudzić następną wachtę i wszcząć panikę najbardziej barbarzyńskim sposobem?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "Myślę, że warto ich trochę rozruszać i postawić w gotowości. Nie podoba mi się, że dryfujemy na widoku. Jeszcze coś się stanie.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "Nie kracz!.. Dobrze. Jeden strzał. Na wiwat.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "Bawcie się dobrze, "+pchar.name+". Pobudzimy załogę... na wasz koszt, ha-ha!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Chwileczkę, panie.";
			link.l1 = "Mów, marynarzu.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "Miło pana poznać. Nazywam się Henry. Chciałby pan zarobić trochę pieniędzy?";
			link.l1 = "Trochę — to ile?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Pięćset pesos.";
			link.l1 = "Ile?! I co mam zrobić za takie pieniądze? Mam nadzieję, że nie chodzi o wzniecanie buntu?";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "Na miłość boską, panie! Po co tak krzyczeć?";
			link.l1 = "To sporo pieniędzy, marynarzu. Nawet w Paryżu można za nie dobrze pożyć.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Ech, nie będę wykorzystywał pańskiej niewiedzy i powiem wprost: na Karaibach pięćset pesos to nic. Kapitanowie i kupcy przywożą tyle towarów, że ceny szybują w górę za wszystko, co ma jakąkolwiek wartość użytkową. Bywa, że rzadki miecz kosztuje tyle, co mały statek.";
			link.l1 = "To jakieś szaleństwo.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "Co tu dużo mówić? Wszyscy czekamy, aż wszystko trochę się unormuje i ceny wrócą do normy. Więc, interesuje pana pięćset pesos?";
			link.l1 = "Najpierw chcę usłyszeć, o co dokładnie chodzi.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "Na pewno wie pan o smutnej sytuacji z rumem na statku. Jestem jednak pewien, że jeśli dobrze poszukać, można jeszcze znaleźć kilka butelek. Rum w butelkach to nie to samo, co breja z beczki. Ma świetny smak, chroni przed zatruciami, wzmacnia rękę i zdrowie — słowem, bardzo przydatna rzecz. Zwłaszcza pod koniec rejsu, kiedy człowiek wariuje od widoku horyzontu.";
			link.l1 = "I co z nim zrobisz? I czemu sam nie poszukasz?";
			link.l1.go = "SailorWantRum_7";
		break;
		
		case "SailorWantRum_7":
			dialog.text = "Kiedy niby? Załogi mamy za mało, więc harujemy za trzech. A rum sprzedam dalej — znajdę kogoś.";
			link.l1 = "Cenię sobie szczerość.";
			link.l1.go = "SailorWantRum_8";
		break;

		case "SailorWantRum_8":
			dialog.text = "Więc jak, podejmiesz się? Potrzebuję trzech butelek.";
			link.l1 = "Postaram się, ale niczego nie obiecuję.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Chyba sobie odpuszczę. Taka robota nie jest dla mnie.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "Szkoda, ale nie będę żywił urazy. Dobrego wieczoru, panie.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;
		
		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Tak, panie "+pchar.lastname+"?";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Oto twoje trzy butelki rumu.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, mam coś dla ciebie od monsieur Pinchona.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Nic takiego.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;

		case "RumGold_2":
			dialog.text = "Znakomicie! Ile tym razem mam dostać?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 dublonów.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 dublonów.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 dublony.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "Muszę wszystko jeszcze raz sprawdzić. Wrócę później.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;
		
		case "RumGold_DatDeneg_gold28":
			dialog.text = "Dziękuję, panie "+pchar.lastname+". Proszę przekazać moje pozdrowienia panu kwatermistrzowi.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "Dziękuję, panie "+pchar.lastname+". Proszę przekazać moje pozdrowienia panu kwatermistrzowi.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "Dziękuję, panie "+pchar.lastname+". Proszę przekazać moje pozdrowienia panu kwatermistrzowi.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;

		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Dziękuję, panie "+pchar.lastname+". Szybko się pan uwinął!";
			link.l1 = "Mam nadzieję, że moje pieniądze dostanę równie szybko.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "A może przyjmie pan zapłatę w innej formie niż pieniądze?";
			link.l1 = "Nie taki z ciebie uczciwy człowiek, jak myślałem.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Ależ nie! Jeśli wybierzesz pieniądze — dostaniesz pieniądze! Po prostu mogę się też podzielić wiedzą.";
			link.l1 = "Jakiego rodzaju wiedzą?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Mogę ci powiedzieć wiele przydatnych rzeczy o żegludze. Tego nie przeczytasz w żadnych uczonych książkach.";
			link.l1 = "No to dawaj, poprowadź najdroższą lekcję w moim życiu.";
			link.l2 = "Pięćset rad nie zastąpi pięciuset monet. Wybieram pieniądze.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Proszę bardzo, panie "+pchar.lastname+". I jeszcze raz dziękuję!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "Mam wielką nadzieję, panie "+pchar.name+", że moja lekcja naprawdę taka się okaże. Wie pan, czym jest nawigacja?";
			link.l1 = "Zdziwisz się, ale wiem. I nawet czytać potrafię. Nawigacja to określanie pozycji i wyznaczanie trasy, na przykład statku.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Aaaa. Chodzi panu o gwiazdy i mapy. Nie, na tym się nie znam. To sprawa nawigatora albo kapitana. My nawigacją nazywamy zdolność do prowadzenia i dowodzenia statkiem.";
			link.l1 = "Kto to „my”?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "Na Karaibach. Tak już jest, nie pytajcie czemu. Im lepiej znasz się na nawigacji, tym większą prędkość i zwrotność wyciśniesz ze statku. I załoga szybciej obsłuży żagle. Ale to nie najważniejsze.";
			link.l1 = "Widzę, że umiesz trzymać napięcie.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Im lepszy masz poziom nawigacji, tym większym okrętem możesz dowodzić! A jeśli masz statek ponad swoje możliwości, to zmęczenie, rozkojarzenie, a nawet pogorszenie zdrowia są nieuniknione!";
			link.l1 = "Brzmi groźnie. Aż dziwne, że wcześniej dawałem sobie radę.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Na szczęście nie musisz znać się na wszystkim. Możesz zatrudnić dobrego nawigatora — i on zajmie się nawigacją. Ale upewnij się, że dostaje pensję i cię wspiera. Zostać bez nawigatora na statku, który przerasta twoje umiejętności, to średnia przyjemność.";
			link.l1 = "Dzięki za lekcję, Henry. Nie wiem, czy mi się to przyda, ale wiedzy nigdy za wiele.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "Proszę bardzo, panie "+pchar.lastname+". I jeszcze raz dziękuję!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(śpiewa) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "Co ty tu robisz, marynarzu?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;

		case "OldSailor_1":
			dialog.text = "Chyba jestem jak madame Michel — szukam kota. Tylko nie krzyczę — ona nie lubi, gdy się na nią krzyczy.";
			link.l1 = "Widziałem ją rano — znów drapała moje buty.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "To jeszcze nic. Ale buty kapitana miały mniej szczęścia. Lubisz koty, panie?";
			link.l1 = "Oczywiście, że lubię.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Nieszczególnie.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "To zrozumiałe. W końcu kto inny miałby tępić te piekielne szczury?";
			link.l1 = "Ale przecież nie możesz wiecznie polegać na kotach? To bardzo kapryśne stworzenia.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Szkoda. Koty są bardzo cenione na statkach. W końcu kto inny miałby tępić te piekielne szczury?";
			link.l1 = "Ale przecież nie możesz wiecznie polegać na kotach? To bardzo kapryśne stworzenia.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "OldSailor_5":
			dialog.text = "To prawda. Dlatego pozostaje tylko arszenik. Tylko spróbuj go znaleźć na Karaibach. Tracimy towar — szczury sikają do rumu, psują suchary i gryzą, co popadnie\nA nasz kwatermistrz mówi: «Nie przejmujcie się, to jak podatek handlowy»\nAle my wiemy swoje: po prostu mu się nie chce. Gdyby nie nasza droga Chantal — kapitan już dawno kazałby mu mieszkać w ładowni i osobiście łapać szczury, ha-ha!";
			link.l1 = "Powodzenia z kotem. Muszę już iść.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "Poczekaj, panie. Zazwyczaj prosty marynarz może zobaczyć szlachetnego pasażera co najwyżej na pokładzie, a ty zszedłeś aż do ładowni!";
			link.l1 = "Ciekawość to pierwszy stopień do piekła, ha-ha!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "Interesuje cie żegluga?";
			link.l1 = "Chyba każdy członek załogi postawił sobie za cel wysłać mnie na brzeg jako prawdziwego marynarza.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "To nic dziwnego. Choć wielu z nas morze przyniosło tylko nieszczęście, to swoją pracę kochamy. I każdy marynarz się cieszy, kiedy nowicjusz wykazuje zainteresowanie.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;

		case "OldSailor_9":
			dialog.text = "To powiedz mi: jaka jest najważniejsza umiejętność kapitana?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Nawigacja. Od niej zależy, jakim statkiem może dowodzić.";
				link.l1.go = "OldSailor_10";
				notification("Pomyślnie zaliczono test", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Nie będę kłamać — nie wiem.";
				link.l1.go = "OldSailor_9_1";
				notification("Niewystarczająca umiejętność (6)", SKILL_Sailing);
			}
		break;
		
		case "OldSailor_9_1":
			dialog.text = "Nie przejmuj się, panie. Porozmawiaj z załogą, pospaceruj po statku. Jeśli odpowiesz — opowiem ci coś bardzo ciekawego. Jak swojemu.";
			link.l1 = "Zapamiętam. Trzymaj się!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "Zgadza się! A teraz pytanie z podstępem: co lepsze — żagle rejowe czy skośne?";
			link.l1 = "Nie będę osądzać, ale czuję podstęp. Myślę, że każde ma swoje zalety.";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "Znowu trafnie! Rejowe są świetne, gdy wiatr dmucha z tyłu. A żaglowiec ze skośnymi potrafi łapać boczny wiatr. Cieszy mnie, że nie traciłeś czasu, panie.";
			link.l1 = "Nie wiem, czy kiedykolwiek mi się to przyda... Może tylko, by zrobić wrażenie na damach z wyższych sfer jako rzekomy wilk morski, ha-ha!";
			link.l1.go = "OldSailor_12";
		break;

		case "OldSailor_12":
			dialog.text = "Ach, nie wiem, panie "+pchar.name+". Może i jesteś szlachcicem — ale zachowujesz się po ludzku. A my to doceniamy. Nasz kapitan coś planuje. Czarna kotka przebiegła między wami.";
			link.l1 = "Co za bzdury. O czym ty mówisz, marynarzu?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Gadają, że nie bez powodu wysłał list do Capsterville spotkanym ostatnio przy okazji statkiem\nI nie bez powodu zarządził dryf — tuż przed końcem rejsu, kiedy wszyscy mają już dosyć i chcą na ląd.";
			link.l1 = "Nie obchodzą mnie plotki. I po co? Mogę go po prostu zapytać. Nie odmówi szlachcicowi szczerej odpowiedzi.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "Nie znasz go, panie "+pchar.name+". Odmówi — i to jeszcze jak. A teraz jest zły — zgubił klucz.";
			link.l1 = "Klucz?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "Od swojej skrzyni w kajucie. Myślę, że nie będzie trudno go znaleźć. Gdzieś się pewnie wala.";
			link.l1 = "Nie rozumiem. Ja mam znaleść klucz?";
			link.l1.go = "OldSailor_16";
		break;
		
		case "OldSailor_16":
			dialog.text = "To już zależy od pana\nA propos, panie "+pchar.name+", czy przypadkiem nie zostało ci trochę rumu? Nie wszystko chyba oddałeś Henry'emu, ha-ha!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Mam. Proszę.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Niestety, nie. Cudem znalazłem te trzy butelki.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "Rzeczywiście. Powodzenia, panie "+pchar.name+". Idę dalej szukać tej paskudnej pasiaczki.";
			link.l1 = "Powodzenia, marynarzu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_17":
			dialog.text = "Och, bardzo pan pomógł! Pięknie się pan zachował wobec załogi, panie "+pchar.name+". Proszę, mały prezent na szczęście!";
			link.l1 = "Kamień z dziurką? Urocze.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Śmiej się, śmiej. Ale ja powiem tak: na morzu talizmany jeszcze nikomu nie zaszkodziły.";
			link.l1 = "Zabobonny z was lud, marynarzu. Powodzenia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_again":
			dialog.text = "Już znasz odpowiedź? Jaka jest najważniejsza umiejętność kapitana?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Nawigacja. Od niej zależy, jakim statkiem może dowodzić.";
				link.l1.go = "OldSailor_10";
				notification("Pomyślnie zaliczono test", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Jeszcze nie.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Niewystarczająca umiejętność (6)", SKILL_Sailing);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Hej, synku!";
			link.l1 = "Nie wyglądasz jak mój ojciec. I całe szczęście.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Ha! A ja cieszyłbym się z takiego rosłego i szlachetnego syna. Tylko sól tej ziemi mogła urodzić takiego jak ja.";
			link.l1 = "No dobrze, przyjmuję komplement. Co się stało?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Potrzebna mi prosta, ludzka pomoc, synku. Kazano mi ułożyć kule armatnie przy działach — w razie, gdyby coś się wydarzyło w tych niebezpiecznych wodach. Połowę wachty dźwigałem te żelazne dranie z ładowni i przy ostatniej skrzyni plecy już nie wytrzymały.";
			link.l1 = "Czemu po prostu nie poprosisz kolegów? Myślałem, że marynarze sobie pomagają.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Jeśli jest coś, czego nasza brać naprawdę nie lubi, to dźwigać ciężary bez pilnej potrzeby. Taki mi dziś przypadł los — nosić skrzynie z kulami z ładowni. Ohydna robota, niegodna takiego marynarza jak ja. Ale cóż poradzić?";
			link.l1 = "Nie narzekaj tak. Pomogę ci. Przynajmniej zobaczę ten ładownię, którą mnie tu ciągle straszą.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Atleta) Widzisz mój miecz przy pasie? Sam waży więcej niż ty. Pójdę po twoje kule, to dla mnie żaden problem.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Nie pracuję fizycznie, marynarzu. Sam dźwigaj swoje skrzynie.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Dzięki, synku. Tylko nie nadwyręż się!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ждёт ядра
			dialog.text = "Jak tam, synku?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Masz swoje kule. Myślałem, że będą większe.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Masz na imię Paul, prawda?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Na razie.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Euh... t-tak.";
			link.l1 = "Twoje nazwisko jest na liście, którą dał mi pan Pinchon.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Ouf, j'ai cru un instant... Oui, Paul - c'est bien moi. Combien avez-vous là pour moi ?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 dublońców.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 dublońców.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 dublońców.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "Muszę wszystko sprawdzić. Wrócę później.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Dzięki, synku.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Dzięki, synku.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Dzięki, synku.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;
		
		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Większych już się nie da! Dobrze, jeśli taki prezent trafi tylko w burtę — wtedy co najwyżej drzazgi z kadłuba kogoś skaleczą. A jak przebije rufę i zacznie skakać po całym pokładzie jak piłka?!";
			link.l1 = "Znajomy widok?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;

		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Bywało, synku. Człowiek to zdolna bestia do wymyślania narzędzi śmierci. Weźmy kartacz — nie strzela daleko, kadłuba nie przebije, ale tuzin ludzi na tamten świat pośle bez problemu. Albo kula łańcuchowa — trafi w żagle i wszystko w strzępy! A o bombach... o nich nic nie powiem — nie widziałem, i całe szczęście! Diabelski wynalazek. I drogi.";
			link.l1 = "O zabójczej sile kul już się przekonałem — po twoich biednych plecach.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Naprawdę mi pomogłeś. I ja nie pozostanę dłużny. Proszę — butelka pierwszorzędnego rumu, prawie pełna, ha-ha!";
			link.l1 = "Skąd ją masz? Cały czas słyszę, że rumu na statku zabrakło stanowczo za wcześnie. Z takim towarem na ręku mógłbyś każdego z załogi uprosić, żeby nie tylko jedną, ale wszystkie skrzynie z ładowni przyniósł.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "Tak już wyszło, synku. Dzięki ci i trzymaj się.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ach, monsieur "+pchar.lastname+". Jeśli zamierzałeś iść spać — masz pecha. Twoją koje zajął nasz kanonier. Sam wiesz, że obudzić go nie zdołasz.";
			link.l1 = "Kiedy chce, to słyszy doskonale!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "Нет.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;

		case "OfficerTorgovets_1":
			dialog.text = "To jeszcze nic. Słyszałem, że u Sharpa w załodze był zupełnie ślepy kanonier. Podobno celował po dźwięku wystrzałów.";
			link.l1 = "Jesteś dziś wyjątkowo rozmowny, monsieur bosman.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "I mam ku temu powód! Wkrótce będziemy na lądzie, a to znaczy — czas zamienić towar na dźwięczące peso. W burdelu w Saint-Pierre zawsze są mile widziane, ha-ha!";
			link.l1 = "Zadziwiające, że to ty, a nie skarbnik, zajmujesz się handlem na pokładzie.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "On nie potrafi rozmawiać z ludźmi! Właśnie dlatego mamy bosmana — zna się na słowach i czynach, ha-ha. Skarbnik też ma swoje sprawki — ale ja się w takie mętne wody nie zapuszczam.";
			link.l1 = "A co dziś masz na sprzedaż?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Ostatnia butelka rumu na statku, kilka przydatnych amuletów... i voilà! Cała mapa skarbu.";
				link.l1 = "Powinieneś zostać handlarzem, nie bosmanem! Pokaż, co tam masz.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Coś jeszcze?";
				link.l1 = "Pokaż, co tam masz.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Amulety? Taki sam jak ten, co ci wisi na piersi?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Przepraszam... Mapa skarbu?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Może innym razem.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, bystre oko, monsieur. Tak, „Koralowa Głowa” — pożyteczna rzecz. Zwłaszcza dla mnie. Jeśli przyjdzie, nie daj Boże, prowadzić abordaż — z nią szybko postawię ludzi do pionu.";
			link.l1 = "Naprawdę pan w to wierzy?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "Nie muszę wierzyć. Takie są zasady Karaibów i nasz los marynarzy. Amulety to użyteczne rzeczy. Więc jeśli zostaniesz z nami na dłużej, radzę mieć przy sobie kilka — na różne okazje.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "O tak. Na Karaibach to nic dziwnego. Ktoś ma szczęście — zgarnia dużą pulę. Potem dwie drogi: płaci podatki, żyje cicho i długo, albo chowa złoto w jaskini — i zostaje po nim grób, skarb... i kawałek papieru.";
			link.l1 = "Tak po prostu?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Nie całkiem. Mapy są drogie i przyciągają takich samych poszukiwaczy jak ty. A sam łup czasem ledwo pokrywa zachód. Nawet wielki Albert Blackwood nie od razu się wybił. Zrób z tego zawód — im więcej skarbów znajdziesz, tym większe będą nagrody. A jeśli kupisz amulet na szczęście — pójdzie ci jeszcze lepiej!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! Chwileczkę.";
			link.l1 = "Znów będzie mnie pan pouczał, monsieur Pinchon? Nie ruszałem pana drogocennego atramentu!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "A czym pan wtedy potajemnie coś zapisuje w swoim kajecie? Wodą święconą? Atramentu nie było w wykazie rzeczy pasażera. Zresztą, teraz ma pan poważniejsze problemy.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "I jeszcze — dwieście, za uszkodzony kabestan. Lina kotwiczna pękła.";
			dialog.text = "Przypominam, że wciąż jest pan winien trzydzieści peso z kasy okrętowej — za zepsutą beczkę deszczówki. Pańska komiczna próba wyprania koszuli mogła kosztować więcej, gdyby wtedy znów nie zaczęło padać. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Tego mi brakowało — długów zaraz po przybyciu. Proszę.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Tego mi brakowało — długów zaraz po przybyciu. Proszę.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "I to wszystko? To przecież nie dług karciany, na miłość boską. Teraz nie mam czasu. Musi pan poczekać do portu.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Szkoda. W takim razie do rzeczy — mam dla pana zadanie.";
			link.l1 = "Nie najlepiej pan dogaduje się z ludźmi, co?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "Chwileczkę, przeliczę.";
			link.l1 = "Po kolacji niech pan też przeliczy moje okruszki chleba, które zostały na stole.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "Gratuluję. Skarbiec okrętowy nie ma już do pana żadnych pretensji. Póki co.\nA teraz do rzeczy – mam dla pana pracę.";
			link.l1 = "Nie jest pan zbyt towarzyski, co?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "Z ludźmi – średnio. Ale za to dobrze liczę.\nA pan, monsieur "+pchar.lastname+", potrafi liczyć?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Księgowy) Znam się na księgach rachunkowych i wekslach. A pojęcie zera nie jest mi obce. Prosze nie pytać skąd to wiem.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Wystarczająco, by rozciągnąć skromne ojcowskie kieszonkowe na cały sezon.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "Ooo! Szkoda, że nie powiedział mi pan wcześniej – ten rejs mógłby być o wiele ciekawszy.";
			link.l1 = "Wspominał pan coś o pracy?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "Dla pańskiego dobra – mam nadzieję, że nigdy nie zostanie pan armatorem. Zbankrutuje pan nie tylko siebie, ale i całą załogę.";
			link.l1 = "Wspominał pan coś o pracy?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Tak. Nie wiem, czy pan wie, ale skarbnik i lekarz to najważniejsze osoby po kapitanie.\n"+
			"Wypłynąć w morze bez tych dwóch – to jak ryzykować pieniędzmi, a bez pieniędzy okręt to tylko bardzo drogi kawałek drewna.\n"+
			"Bez skarbnika nawet mały szkuner może doprowadzić kapitana do bankructwa. A pierwsza walka bez lekarza może wykończyć całą załogę, co rozpocznie żmudny i kosztowny proces rekrutacji i szkolenia.\n"+
			"Na nasze szczęście, łączę obie funkcje. Dlatego mogę prowadzić własne interesy i korzystać z drobnych usług załogi.\n"+
			"Naturalnie, usługi są sowicie opłacane – i właśnie teraz mam dobrą okazję, by to zrobić.\n"+
			"Chcę, żeby pan wziął tę listę, kuferek z dublonami – i wypłacił członkom załogi należności.\n"+
			"Ściśle według listy! Dlatego właśnie pytałem, czy potrafi pan liczyć.";
			link.l1 = "A dlaczego pan sam tego nie zrobi? W końcu jeśli ludzie czekają na wypłatę – niech przyjdą.";
			link.l1.go = "OfficerKaznachey_10";
		break;

		case "OfficerKaznachey_10":
			dialog.text = "Mam teraz zbyt dużo na głowie. Do końca rejsu zostało kilka dni, a zaraz ustawi się kolejka stu osób domagających się wypłaty.";
			link.l1 = "Wspominał pan coś o dublonach...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "Złota hiszpańska moneta. Prawdziwa waluta i miara bogactwa. Najrzadsze, najdroższe i najpotrzebniejsze usługi – tylko za nie.\n"+
			"Przechowuje się je w takich oto kuferkach, dla wygody.";
			link.l1 = "A co ja z tego będę miał?";
			link.l1.go = "OfficerKaznachey_12";
		break;
		
		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Księgowy) 150 peso, i jeszcze 5 dublonów ekstra za to, że prawie jesteś moim kolegą. No i możliwość wymiany peso na dublony po godziwym kursie.";
			}
			else
			{
				dialog.text = "150 peso i możliwość wymiany peso na dublony. Niewiele, ale i robota najprostsza.";
			}
			link.l1 = "Dobrze. Daj mi listę i skrzynię.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Obawiam się, że taka praca zupełnie mi nie odpowiada. Żegnam, monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;

		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Twoja sprawa. W takim razie nie przeszkadzaj mi w pracy, monsieur "+pchar.lastname+".";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Proszę. Tylko na Boga — nie zapomnij wyjąć dublonów ze skrzyni, ściśle trzymać się listy i nie próbuj nic sobie przywłaszczyć. Pustą skrzynię też mam nadzieję odzyskać\n"+
				"Tylko się nie przeciąż, monsieur. Po co tyle gratów ze sobą nosisz? Radzę zostawić część rzeczy w jakiejś skrzyni."; 
			}
			else
			{
				dialog.text = "Proszę. Tylko na Boga — nie zapomnij wyjąć dublonów ze skrzyni, ściśle trzymać się listy i nie próbuj nic sobie przywłaszczyć. Pustą skrzynię też mam nadzieję odzyskać.";
			}
			link.l1 = "Jak pan każe. Do zobaczenia, monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			SetFunctionExitFromLocationCondition("Tutorial_Logbook", pchar.location, false);
			Tutorial_Dubloons("");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
		
		case "OfficerKaznachey_12_Wait": // ждёт выполнения квеста
			dialog.text = "Jak tam postępy? Zapłatę rozdano? Wszystko przyniesione? Reszta dublonów, pusty kufer?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && GetCharacterItem(pchar, "gold_dublon") >= 18)
			{
				link.l1 = "Wszystko gotowe.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Jeszcze nie, monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "No dobrze, zobaczmy...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "A mówiłeś, że potrafisz liczyć. Tu jest mniej, niż powinno być. A to oznacza, że moja księgowość właśnie się skomplikowała i stworzyłeś mi nowy problem zamiast rozwiązać aktualny\n"+
				"Tak więc, monsieur "+pchar.lastname+", zapłata ci się nie należy.";
				link.l1 = "Ale dublony i tak wymienisz?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "A mówiłeś, że potrafisz liczyć. Tu jest więcej, niż powinno być. A to oznacza, że moja księgowość właśnie się skomplikowała i stworzyłeś mi nowy problem zamiast rozwiązać aktualny\n"+
				"Tak więc, monsieur "+pchar.lastname+", zapłata ci się nie należy.";
				link.l1 = "A co z wymianą?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Wszystko się zgadza. Miło widzieć, że młode pokolenie potrafi obchodzić się z liczbami. Dziękuję, monsieur "+pchar.lastname+". Oto twoja zapłata – i niewielka premia, jak dla niemal kolegi.";
					link.l1 = "A co z wymianą?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Wszystko się zgadza. Miło widzieć, że młode pokolenie odpowiedzialnie podchodzi do pieniędzy. Dziękuję, monsieur "+pchar.lastname+". Oto twoja zapłata.";
					link.l1 = "Czy nadal wymieniasz dublony?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "A czemu nie. Sto piętnaście pesos za dublon. Proszę się zgłosić, jeśli będziesz zainteresowany.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Oczywiście. Sto pięć pesos za dublon. Proszę się zgłosić, jeśli będziesz zainteresowany.\n"+
			"Pozwól też, że doradzę: jeśli, nie daj Boże, los postawi cie na czele okrętu — zatrudnij najpierw skarbnika. Nawet słaby specjalista oszczędzi ci majątek.";
			link.l1 = "Dziękuję, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Oczywiście! Sto pesos za dublon — uczciwy kurs. Banki karaibskie zdzierałyby więcej\n"+
			"Pozwól też, że doradzę: jeśli, nie daj Boże, los postawi cie na czele okrętu — zatrudnij najpierw skarbnika. Nawet słaby specjalista oszczędzi ci majątek.";
			link.l1 = "Dziękuję, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;

		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Obijasz się, monsieur "+pchar.lastname+"?";
			link.l1 = "Ciebie też zesłali do ładowni?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;

		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Jestem lekarzem okrętowym, "+pchar.lastname+"! Wkrótce mesa będzie pełna rannych, a ja zobaczę więcej krwi niż którykolwiek z uczestników bitwy. I nawet gdybym nie był lekarzem, a tylko skarbnikiem — stanąłbym do walki jak wszyscy. Nie, jedynym, którego zesłano do przytulnej ładowni, to ciebie.";
			link.l1 = "To co tu robisz?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "La battaglia non inizierà per un paio d'ore, quindi è il momento perfetto per chiudere i conti giornalieri. Avete il mio forziere di dobloni, de Maure. Cortesemente restituitelo.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Prendetelo. E non mostrate più la vostra faccia quaggiù.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "Ho lasciato la vostra roba da qualche altra parte.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			dialog.text = "Bitwa zacznie się dopiero za kilka godzin, więc to najlepszy moment, by zamknąć dzienny bilans. Masz mój kuferek z dublonami, "+pchar.lastname+". Upraszam się o zwrot.";
			link.l2 = "...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "Da qualche altra parte... Ne discuteremo dopo la battaglia - in presenza del capitano. Arrivederci.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;

		case "TreasurerTrade":
			dialog.text = "Interesują cie dublony, monsieur "+pchar.lastname+"?";
			link.l1 = "Potargujmy się.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Na razie nie.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;

		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Kapitanie, żagiel na horyzoncie! Piraci na horyzoncie!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, uprzejmie odprowadź monsieur "+pchar.lastname+" do ładowni. I sprawdź, żeby monsieur Drussac raczył się obudzić i przygotował załogi armat do walki.";
			link.l1 = "Kapitanie, jestem gotowy walczyć! Szlachcic nie może...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Jeśli mogę w czymś pomóc...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Więc nie będzie burgundzkiego?..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, zabierz go. Do roboty, lenie! Podnieść żagle!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, zabierz go. Do roboty, lenie! Podnieść żagle!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, zabierz go. Do roboty, lenie! Podnieść żagle!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		// <-- Матрос сообщает о приближающихся кораблях
		
		// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Do diabła! Uparte z was bestie!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "A ty co tu robisz?! Porzuciłeś swoich i chowasz się przed walką, szczurze z ładowni?! Zaraz ci flaki wypruje!";
			link.l1 = "Źle trafiłeś, że wlazłeś do mojej ładowni. To ja ci wypruje flaki.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Ledwie stoisz na nogach, a większość krwi na tobie nie jest twoja.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Pojedynkowicz) Tego mi brakowało.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "Hehe. No to próbuj, paniczyku.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "Hehe. No to znaczy, że nie mam nic do stracenia.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "EnemyPirate_3_Duelyant":
			dialog.text = "Co ty pleciesz?!";
			link.l1 = "Dwa miesiące. Dwa miesiące musiałem trzymać szpadę w pochwie. Zatańczmy!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Dobrze, że żyjesz... A ja już po wszystkim. Skwaśniałem. Dostałem nieźle po rumpelu...";
			link.l1 = "Co się stało?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "Był abordaż. Ar-r-gh! Uparte z nich bestie!\nSłuchaj uważnie: pokład działowy utrzymaliśmy, ale na górze zabawa się dopiero zaczyna. Daję słowo, zaraz znów się tu wpakują. Trzymaj kartaczownicę! Diabli nadali, ostrożnie! Jest naładowana!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Strzelec) Nie martw się o mnie. Kto się zbliży — zrobię z niego sito.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "Tam jest kartacz. Jeśli dobrze to rozegrasz — możesz zdjąć dwóch-trzech naraz\nWierzę w ciebie, "+pchar.name+". Jak się obronisz, przeszukaj trupy. Może znajdziesz coś do picia dla mnie... inaczej nie będę pomocny.";
			link.l1 = "Trzymaj się, Alonso. A oto i goście!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Dobrze... Dobrze sobie poradziłeś, "+pchar.name+". Znalazłeś coś dla mnie?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Myślę, że tak. Choć wygląda podejrzanie.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Jeszcze szukam!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;
		
		case "SailorAlive_12":
			dialog.text = "A w smaku niezłe, ha-ha! Dzięki, "+pchar.name+". I tych trzech ładnie położyłeś. Skoro naprawdę jesteś takim szlachetnym dżentelmenem, to przejmij dowodzenie. We dwóch na pewno utrzymamy pokład, a jeśli chłopaki na górze też dadzą radę — dzień będzie nasz!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Tak lepiej. Załadowałeś kartaczownicę?";
				link.l1 = "Właśnie się tym zajmuję... A czemu nagle tak ucichło?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Skoro naprawdę jesteś takim szlachetnym dżentelmenem, to przejmij dowodzenie.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Tak lepiej. Załadowaliście kartaczownicę?";
			link.l1 = "Właśnie się tym zajmuję... A czemu nagle tak ucichło?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "Dla większego dramatyzmu. Zaraz się zacznie.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "I znowu kończymy tam, gdzie zaczynaliśmy. Dzięki za uratowanie mojego tyłka, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Myślę, że jesteśmy kwita. Nawet nie pamiętam, jak mnie stamtąd wyciągnąłeś.";
			}
			else
			{
				link.l1 = "Myślę, że jesteśmy kwita. Gdyby nie ty i chłopaki, zostałbym tam na dobre.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Mogłeś przesiedzieć w ładowni, jak ci kazano. Szkoda, że kapitan nie dożył, żeby ci sprawić lanie.";
			link.l1 = "Musieliśmy wyciągać go spod góry ciał. Ilu łajdaków zdążył załatwić?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Ktoś widział, jak położył trzech. Inni mówią, że nie mniej niż tuzin. Myślę, że tylko diabeł prowadził dokładny rachunek.";
			link.l1 = "Jeszcze mi nie powiedziałeś, dlaczego tak się stało.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "A co tu opowiadać? Szesnastofuntowe działa nie uratowały nas przed jednym pirackim brygiem. Oto co znaczy okręt do prawdziwej roboty\n"+
			"W mgnieniu oka podpłynął, zanim zdążyliśmy się obrócić, ostrzelał nas kartaczem i natychmiast rzucił się do abordażu. Powinieneś był zobaczyć, co działo się na pokładzie — lekarzowi nie było już czego składać\n"+
			"Najgorsze w walce z piratami jest to, że nic z nich nie ma. Golasy, jednym słowem. Nawet brygu nie udało się przejąć.";
			link.l1 = "I co dalej?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "Statek pływa, a ludzi zachowaliśmy dość, by dostarczyć cie do Saint-Pierre zgodnie z planem, gdzie ja będę szukał nowego kapitana, a ty znajdziesz brata i opowiesz mu o swoich przygodach. A co dalej — to już tylko Bóg wie.\n"+
			"Jedno wiem na pewno — odnajdziesz się tu. Nieźle jak na szczura lądowego, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;
		
		case "AfterBattle_Alonso_6":
			dialog.text = "O-ho! Zaraz zacznie was wykręcać. Nie krępuj się. To strach cie opuszcza. Witamy na Karaibach!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}