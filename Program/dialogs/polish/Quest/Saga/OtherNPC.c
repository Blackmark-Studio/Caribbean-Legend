// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chcesz coś?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Czego chcesz? Nie widzisz, że jestem w żałobie! Zjeżdżaj, zanim kopnę cię ze schodów!";
			link.l1 = "Cóż, kup sobie większy dom ze schodami do tego. Wtedy porozmawiamy o zrzucaniu ludzi ze schodów, bohaterze...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Czemu jesteś taki zdenerwowany, Jimmy? Nie dostanę rumu do końca mojego przeklętego życia, jeśli nie chodzi o jakąś piękną kobietę! Tylko kobieta mogłaby sprawić, że taki stary morski wilk jak ty groziłby swoim starym przyjaciołom...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Nienawidzę takich pedantów jak ty! Zawsze dostajecie lepsze kawałki ciasta. Nie pozwolili mi zabić jednego pyszałka, więc wyładowam swoją złość na tobie!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Tak?! Znam cię? Nie pamiętam cię, cholera jasna...";
			link.l1 = "To ja, "+pchar.name+"! Mieliśmy miły czas w Blueweld, kiedy prawie wypatroszyłeś tego bezczelnego typka w płaszczu. Jak on się nazywał? Już zapomniałem... W każdym razie, nie będę się przejmował armatami jego korwety, jeśli kiedyś spotkam go na morzu!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Jego imię było Artur! Artur Donovan, kapitan korwety 'Arbutus'! Plugawy drań! Zgadzasz się, że byłem bliski wysłania go do diabła?";
			link.l1 = "Oczywiście! Nie miał absolutnie żadnych szans, ale twoi kumple się wtrącili. Wybacz im, nie chcieli, żebyś został powieszony za morderstwo oficera marynarki.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Argh! Gdybym tylko miał statek! Tego drania można łatwo wytropić w pobliżu Antiguy... ha! Będę ci wdzięczny, jeśli poślesz go na dno!";
			link.l1 = "Umowa stoi, ha-ha! A tak przy okazji, czy Rumba naprawdę jest warta twojego cierpienia?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Jak najbardziej! Nigdy nie spotkałem nikogo lepszego niż ona. Ale ona tylko się ze mnie śmieje. Wszyscy chcą tej syreny. Niektórzy marynarze powiedzieli mi po cichu, że nasz Jacob szuka jakiejś dziewczyny, która wygląda dokładnie jak moja Rumba. On też jej chce! Jak teraz mogę wykonywać jego rozkazy?";
			link.l1 = "Trzymaj język za zębami, kumplu! Ściany mają uszy... I dlaczego myślisz, że Jackman szuka Rumby?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Z pewnością jest! Szuka jakiegoś Henryka Wisielca i dwudziestoletniej dziewczyny z blond włosami i niebieskimi oczami. Jakaś Gladys Chandler z Belize musi być jej opiekunką.";
			link.l1 = "Czekaj! Gladys ma inne nazwisko. I to jej matka!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman jest przebiegły! Nie złapiesz go nieprzygotowanego! Zalecam się do Rumby od jakiegoś czasu i dowiedziałem się, że Gladys poślubiła Seana McArthura dokładnie dwadzieścia lat temu. I wcześniej mieszkała w Belize. Jej pierwszym mężem był Pete Chandler.\nBiedny Pete zginął w pijackiej bójce. Mówią, że to sam McArthur był za to odpowiedzialny, bo miał wtedy uczucia do pulchnej Gladys. Została wdową z dzieckiem na rękach. Dziecko nie przeżyło długo po ojcu i zmarło na gorączkę wkrótce potem.\nI zaledwie kilka miesięcy później Gladys i Sean pojawili się z dziewczynką, rzekomo córką McArthura, w Blueweld. Więc jak Gladys mogła urodzić kolejne dziecko tak szybko? Rozumiesz?";
			link.l1 = "Czy powiedziałeś o tym komuś innemu?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Jeszcze nie. Trzymaj gębę na kłódkę, bo... no, wiesz, jaki jestem!";
			link.l1 = "Tak, mam. Masz zgniły język, który zdradza wszystkim swoje sekrety. Rumba miał rację, że cię odesłał, gaduło...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Oczywiście! Będę trzymał język za zębami! A teraz muszę iść. Żegnaj, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Co... co powiedziałeś?!";
			link.l1 = "Nie będziesz mógł tego nikomu innemu powiedzieć...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Argh, ty potworze!";
			link.l1 = "Rozmawiasz sam ze sobą, panie?! Gdzie jest Rumba?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Jaka Rumba? Nie mam na moim statku łajdaków z przydomkami. To jest angielski okręt wojenny!";
			link.l1 = "Nie udawaj głupca, Donovan. Doskonale wiesz, o kogo mi chodzi. Gdzie jest dziewczyna? Gdzie jest Helen? Odpowiadaj, ty parszywy draniu...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen? Nie ma żadnych lądowych dziwek na moim statku, ty kawałku gówna!";
			link.l1 = "Żadnych ladacznic na lądzie? Ciężko uwierzyć, skoro jedna z nich stoi przede mną w tej chwili... Rozumiem, że nie ma sensu kontynuować naszej rozmowy. Zdychaj, żałosny robaku!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Kapitanie, przeszukaliśmy wszystkie kajuty i ładownię, tak jak nam kazałeś. Znaleźliśmy dziewczynę w łańcuchach w ładowni...";
			link.l1 = "Co za drań! Tak jak myślałem... Czy uwolniłeś dziewczynę?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Oczywiście, Kapitanie. Została bezpiecznie przetransportowana na twój statek.";
			link.l1 = "Dobra robota! Zabierz ją do mojej kajuty, chcę z nią porozmawiać, gdy tylko tu skończymy.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Cześć, Kat! Kapitan Rzeźnik przesyła pozdrowienia.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = " Nazywam się Charles de Maure. Szukam Enrique, syna senory Gonzales w imieniu jej starego przyjaciela. Myślę, że to ty jesteś nim...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Co do diabła! Nie znam żadnego Rzeźnika!";
			link.l1 = "Chodź, Henryku. Powiedz mi, dlaczego piraci Jackmana cię szukają, a nie zrobię ci krzywdy.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Pomocy! Piraci! Morderstwo!";
			link.l1 = "Zamilcz, idioto! Połowa miasta tu przyleci z powodu twojego wrzasku. Ach, czy to tego chcesz?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Panie, musisz się mylić. Wychowałem się w obcej rodzinie, nie pamiętam mojej matki biologicznej. Przyjąłem nazwisko mojego opiekuna. Nie znam imienia mojej matki, ale wątpię, by było to Gonzales. Możesz zapytać o mnie, a każdy stary mieszkaniec potwierdzi moje słowa. Mój ojczym był znanym człowiekiem, nie miał własnych dzieci, więc odziedziczyłem ten dom i...";
			link.l1 = "Przepraszam. Wydaje się, że się pomyliłem. Żegnaj.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Nie sądzę.";
			link.l1 = "Przepraszam?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Wiesz, niedawno nasza kolonia została brutalnie zaatakowana przez piratów. Wierzę, że słyszałeś o tym? W wyniku tego ataku niezliczona liczba ludzi cierpiała. Ja nie doznałem krzywdy, ale mój odziedziczony biznes przechodzi teraz ciężkie czasy. A winowajcą całego tego nieszczęścia jest przywódca tych piratów, łotrzyk o imieniu Charlie Prince.";
			link.l1 = "Strasznie mi przykro, ale co to ma ze mną wspólnego?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ha-ha, spójrzcie tylko na tę niewinną owieczkę! Proponuję, byś pokrył moje straty, skoro jesteś ich przyczyną. Zadowolę się sumą piętnastu tysięcy peso. I udam, że nigdy nie byłeś w moim domu.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Jakie to wszystko mściwe... Oto twoje pieniądze. I pamiętaj, jeśli ktokolwiek dowie się, że byłem w tym mieście, wrócę po ciebie.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Piętnaście tysięcy? Hm... Nie sądzę, żeby twoje życie było tyle warte. Chyba taniej będzie cię po prostu wykończyć, żebyś nie paplał.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Straże! Piraci! Morderstwo!";
			link.l1 = "Zamknij się, idioto!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Widzę, że podoba ci się moja szabla. Mogę ci ją sprzedać, jeśli chcesz. Nie będę prosić o wiele, umieram z pragnienia na rum, a moje kieszenie są puste.";
			link.l1 = "I po co mi to do cholery? Leśny Diabeł kazał mi przekazać ci pozdrowienia.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Cóż, tak. Masz naprawdę zacny kordelas. Ile kosztuje?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Lepiej by było, gdyby dał mi ze dwieście peso zamiast tego!";
			link.l1 = "Więc znasz Svensona?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Pierdole ciebie i pierdole twojego Svensona, niech go diabli wezmą. Do leśnego diabła czy morskiego diabła, mnie to nie obchodzi. Jeśli nie chcesz pomóc choremu człowiekowi, kupując jego szablę, to wsadzę ci ją w dupę za darmo.";
			link.l1 = "Naprawdę? Zobaczymy, jak zamierzasz to zrobić, gnojku!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Widzę, że masz doświadczenie! Tysiąc pesos i jest twoje.";
			link.l1 = "Umowa stoi!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Takie kordelasy są tylko dwa w Kartagenie - mój i stary Alvaresa z latarni. Ale on swojego nie sprzeda. Jest hipokrytą, wyczuwam byłego pirata na milę. Ostrze to dla niego jakiś talizman.\nWygląda na to, że biedna dusza opłakuje rzeczy, które chce zapomnieć. To musi być powód, dla którego co miesiąc chodzi do kościoła, z powodu grzechów, które nie dają mu spać.";
			link.l1 = "I widzę, że ty też masz jakąś historię. To musisz być ty, o kim Svenson mówił. Kazał mi przekazać ci serdeczne pozdrowienia, jeśli cię spotkam w Kartagenie.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson? Nigdy o nim nie słyszałem. Nazywam się Enrique Gallardo. Ale jeśli twój Svenson ma dla mnie butelkę rumu, mogę być Henrykiem dla niego. Nazywaj mnie, jak chcesz, bylebyś nie zawołał mnie późno na kolację. Więc, idziemy?";
			link.l1 = "Nie dzisiaj. Svenson jest daleko, ale tawerna jest blisko. Twoje kieszenie nie są już puste, więc uważaj, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "Jednakże nie są całkowicie pełne. Chcę więcej. I zapłacisz mi.";
			link.l1 = "Jestem zdezorientowany... Czy nie cenisz swojego życia? Planujesz obrabować mnie w środku miasta? I to po tym, jak sam mi sprzedałeś swoją broń?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "Nie, zapłacisz mi sam. I wiesz dlaczego?";
			link.l1 = "Jestem ciekaw, by to usłyszeć.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Rozpoznałem cię. Byłem w lochach za pijacką bójkę w tawernie, kiedy twoi ludzie wpadli do więzienia i wyrżnęli wszystkich strażników. Udało mi się dotrzeć do trupa strażnika z kluczami i wydostałem się na ulicę. Miasto płonęło, trupy, krew i dym prochowy wszędzie... Jak podczas abordażu! I przez ten dym zobaczyłem cię wychodzącego z rezydencji gubernatora. Poetyckie, prawda? Jo-ho-ho, witaj, Charlie Prince!";
			link.l1 = "Przestań tak wrzeszczeć! Wiedząc to, co wiesz, tym bardziej nie powinieneś próbować wyciągać ode mnie pieniędzy. Czy zdajesz sobie sprawę, co mogę ci zrobić?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "W środku miasta, które kiedyś okradłeś? Nic nie możesz zrobić. A więc, podsumowując... zrobimy to tak: dajesz mi... powiedzmy, dziesięć tysięcy pesos teraz. Myślę, że to wystarczy na miesiąc. A ty idziesz swoją drogą! Czy to do twego ukochanego Henryka, do Swensona, czy do jakiegokolwiek innego diabła, którego wybierzesz... A jeśli nie, wystarczy, że krzyknę, a wciągną cię do specjalnie przygotowanej osobistej komnaty pełnej narzędzi tortur.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Do diabła, weź swoje dziesięć tysięcy i zniknij mi z oczu! I nie daj Boże, żebym cię jeszcze raz zobaczył.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Dość tego, mam tego po dziurki w nosie. Twoja broń jest moja, więc nie masz szans, szumowino.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Haha, jesteś dobry! Wiesz co? Każdemu innemu już bym rozpłatał brzuch aż po gardło. Ale tacy jak ty są mi potrzebni. Co powiesz na to: dam ci dziesięć tysięcy pesos, zwrócę twojego 'Wisielca' i dorzucę dodatkowe trzy tysiące każdego miesiąca - Powinno wystarczyć na gorzałę - A ty zostaniesz pasażerem na moim statku.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Dobrze, dobrze, już mnie nie ma! Powodzenia w poszukiwaniach, Książę Charlie!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Straże! Straże!!! To książę Charlie!!!";
			link.l1 = "Ty draniu!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Czy sugerujesz, żebym dołączył do twojej załogi?";
			link.l1 = "Dokładnie. Ale to jest oferta jednorazowa. Więc, co ty na to? Zgadzasz się, czy mam rozlać twoje flaki. Nie sądzisz chyba, że tak łatwo możesz szantażować Charliego Prince'a, prawda?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Diabeł! Sam Charlie Prince proponuje mi dołączyć do jego załogi! Cholera, zgadzam się! Oddaj mi mój miecz i dziesięć tysięcy pesos. Nigdy nie sądziłem, że tak to się potoczy!";
				link.l1 = "Tu. I trzymaj gębę na kłódkę: nikt w tym mieście nie musi wiedzieć, kim jestem, zrozumiano?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "Nie. Może jesteś porządnym kapitanem, ale wydaje mi się, że jesteś trochę zbyt spięty. Tak, nauczyłeś Hiszpanów się bać, przeprowadzając śmiały najazd na Cartagenę - ale wszystko to było tylko z pomocą Marcusa Tyrexa. Nie masz odwagi, by prowadzić uczciwe grabieże na własną rękę. Więc, wyciągaj kasę!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "Nie. Z pewnością jesteś notorycznym piratem, ale jako kapitan nie wydajesz się zbyt imponujący. Udało ci się splądrować kolonię tylko z pomocą Marcusa Tyrexa - nawet nie odważyłbyś się samodzielnie wejść na pokład zrujnowanego slupa. Więc, wyłóż kasę!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Do diabła, weź swoje dziesięć tysięcy i znikaj mi z oczu! A nie daj Boże, żebym cię znów zobaczył.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Dość tego, mam tego dość. Twoja broń jest moja, więc nie masz szans, łajdaku.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Zrozumiano, nie jestem głupcem.";
			link.l1 = "Dobrze.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Nie spodziewam się gości, ani dzisiaj, ani w jakikolwiek inny dzień. Czego chcesz?";
			link.l1 = "Cześć, Kat. Leśny Diabeł mnie przysłał. Dobrze, że znalazłem cię przed chłopakami Jackmana. Jego ludzie szukają cię po całych Karaibach. Na szczęście dla ciebie, Henryku, tylko Svenson wie, gdzie się urodziłeś. Poprosił mnie, bym cię ostrzegł.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Widzę teraz... Więc wydaje się, że Svenson wciąż żyje i nie zapomniał o swoim starym przyjacielu. Wiele krwi przelano, odkąd pierwszy raz zobaczyłem go jako żółtodzioba stojącego na pokładzie uszkodzonego brygu... Życie minęło zbyt szybko i nie zostało mi wiele czasu\nChciałem umrzeć z przyczyn naturalnych na tym pustkowiu, z dala od ludzkości i blisko morza. Ale jeśli Jackman wrócił na Karaiby, nie zostawi mnie w spokoju. To nie była moja wina, ale jestem dłużny jego panu. W każdym razie, kto mi teraz uwierzy.\nNie boję się śmierci, lecz bólu. A Jackman wie wiele o bólu. Sama myśl o tym sprawia, że moje serce staje, a wszystko wokół ciemnieje.";
			link.l1 = "Rzeźnik został powieszony dwadzieścia lat temu, więc nie musisz spłacać długów nikomu. Możesz oddać swój dług mnie, jeśli boisz się Jackmana. Myślę, że i tak go spotkasz.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Nie jest łatwo powiesić takich ludzi jak Rzeźnik. Były kat z St. John's mógłby ci opowiedzieć wiele ciekawych historii o zmarłych, którzy powrócili z piekła. A Jacob został dobrze nauczony przez swego kapitana, więc nie jestem pewien, kogo obawiam się bardziej.";
			link.l1 = "Po co Jackmanowi jesteś potrzebny?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Musiałem dostarczyć złoto wdowie jako zapłatę za opiekę nad córką Rzeźnika. Czemu tak na mnie patrzysz? Tak, urodziła się niedługo przed zatopieniem 'Neptuna'. Nie mógł wrócić po nią na czas, więc wysłał mnie, bym zajął się dzieckiem i jej opiekunką.";
			link.l1 = "Czy opiekunka nazywała się Gladys Chandler?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Nie udawaj idioty. Jeśli Jackman mnie szuka, to dlatego, że potrzebuje córki Rzeźnika. Musisz już wiedzieć, że szuka kobiety z Belize imieniem Gladys i jej przybranego dziecka. Bądź ze mną szczery, a może ci zaufam.";
			link.l1 = "Co miałeś powiedzieć Gladys?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Nic. Miałem jej pokazać pierścień Rzeźnika, tak miała poznać, że jestem kurierem wysłanym przez kapitana. Musiałem też wręczyć jej skrzynię z dublonami na potrzeby dziecka. Musiałem zabić drania, żeby odebrać pierścień. Przez to przedłużyłem mój pobyt na Antigui o dodatkowy miesiąc.\nA gdy w końcu dotarłem do Belize, Gladys już jej nie było, a miasto zostało spalone i splądrowane przez Hiszpanów. Udało jej się sprzedać dom i uciec z nowym chłopakiem i małą Helen. Mam nadzieję, że się nią zajęła i nie sprzedała dziewczynki Cyganom ani do burdelu.";
			link.l1 = "Imię córki Rzeźnika to było Helen, prawda?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Dokładnie. Na cześć matki Rzeźnika. Jeśli nie boisz się żywych trupów i piratów patrzących na ciebie martwymi oczami, to mogę ci dać pierścień i złoto. Nigdy ich nie tknąłem. Umierałem z głodu, ale ich nie tknąłem. Rób z nimi, co chcesz. W zamian proszę o...";
			link.l1 = "Co się dzieje, Henryku?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Ty...u... Ja py...t... o!";
			link.l1 = "Nie!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				CoolTraderHunterOnMap();
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, oto nasz ciekawski przyjaciel! Czy znalazłeś w końcu Gonzaleza? Dobra robota, doprowadziłeś nas do niego... nie potrzebujemy cię już. Chłopcy, zabijcie tego błazna!";
			link.l1 = "Czas umrzeć, krabowe flaki!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! Wielki Kukulcan żąda nowej ofiary! O-eh! Duch potężnego wojownika z przeszłości przybył do naszej wioski, by zostać złożonym w ofierze wielkiemu Kukulcanowi! O-eh! Wszyscy pokłońcie się potężnemu duchowi wojownika!";
			link.l1 = "(słabo) Co do licha, gdzie ja jestem?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Wielki wojownik chce zostać pożarty przez wielkiego Kukulkana! Słońce wschodzi, cienie się skracają! Wielki Kukulkan wkrótce ożyje! Zawiedziemy cię do niego, o potężny wojowniku, a ty nadal będziesz przechodzić przez ziemię przodków!";
			link.l1 = "(cicho) Nonsens... Kukulcan znowu? Hej, wódzu, przybyłem w pokoju! Jestem tutaj, aby...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! Wielki wojownik mówi, że chce być natychmiast złożony w ofierze Kukulcanowi. O, wielki wojowniku! Idziemy teraz do Kukulcana i czekamy na jego wizytę! Wojownicy! Mamy wielki zaszczyt zabrać ducha przodka do Kukulcana!";
			link.l1 = "(słabo) Idiota... Dobra, muszę z nimi iść. Dobrze, że mnie jeszcze nie zaatakowali, nie byłbym w stanie się bronić w tym czymś...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Przychodzimy do Kukulkana, wielkiego ducha przodków. Wkrótce słońce zachodzi, cienie rosną i Kukulkan nas odwiedzi. Czekaj, wielki wojowniku...";
			link.l1 = "(słabo) Teraz widzę, indiański wódz wojenny...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan żywy! Kukulcan z nami! Wielki wojownik może być złożony w ofierze Kukulcanowi! Wojownicy, pokłońcie się wielkiemu duchowi przodka!";
			link.l1 = "(słabo) Trzymaj się z daleka, Wodzu. Zrobię to sam. To nie pierwszy raz...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Jak mogę ci pomóc, panie?";
			link.l1 = "No cóż, no cóż... powiedz mi, kumplu, co tu robisz?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Co ja tu robię? Jestem rybakiem i łowię tutaj ryby. A czemu, do diabła, przesłuchujesz mnie w takim tonie?";
			link.l1 = "Nie kłam mi, kumplu. Może faktycznie jesteś rybakiem, ale tutaj ryb nie łowiłeś. Cenny jedwab ze statku został wyrzucony do morza, właśnie w tym miejscu. A twoja obecność sama w sobie wydaje mi się dość podejrzana.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Co za bzdury? O jakim jedwabiu ty w ogóle mówisz?";
			link.l1 = "Jaki jedwab? Chiński... Nie udawaj idioty! Słuchaj mnie teraz: albo natychmiast wyciągasz jedwab z ładowni i dajesz mi go, albo sam go wezmę. Ale najpierw moja grupa abordażowa zajmie się tobą i twoimi ludźmi. No i co? Mam zawołać moich ludzi?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Nie! Panie, nie wiedziałem... Te bele po prostu pływały, więc postanowiłem...";
			link.l1 = "Przynieś jedwab na mój statek. Pospiesz się!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Tak, tak, oczywiście. Zrobimy to natychmiast, tylko nie zabieraj mojego statku!";
			link.l1 = "Ruszaj się, do cholery! Nie mam dużo czasu...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Tu, przywiozłem wszystko, co znaleźliśmy - wszystkie dziewięć bel. To wszystko, przysięgam...";
			link.l1 = "Dobrze. Możesz kontynuować swoje łowienie, ale nie miej oka na cudze mienie w przyszłości!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Już dostałeś, czego chciałeś. Nie mam już nic więcej! Czego jeszcze potrzebujesz?";
			link.l1 = "Spokojnie, kumplu. Odchodzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Jeśli jesteś wysłany przez Barbazona, to powiedz mu, że nie chcę sam opuścić więzienia. Lepiej poczekam na proces. Nawet holenderskie konopie na mojej szyi są lepsze niż jego łaskawość.";
			link.l1 = "Jeszcze nie pierdź. Twój nawigator powiedział Jacquesowi, że nie żyjesz. Wysłał mnie, bym znalazł jedwab, który wrzuciłeś do morza. Ile go było na twoim brygantynie?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "To była moja wina, do diabła. Kurier przywiózł dziewięć bel jedwabiu dla Barbazon. Kazałem go śledzić. Zrobił się głośny, więc musieliśmy mu podciąć gardło. Miał dodatkowe trzy bele w swojej skrytce, które zabrałem dla siebie i schowałem w mojej własnej skrytce. Ale wydaje się, że przyciągnęliśmy niechcianą uwagę.\nZnaleźli nas szybko, a holenderski patrol czekał na 'Salt Dog' na otwartym morzu. Nie udało nam się uciec. Możesz wziąć jedwab dla siebie, jeśli nie powiesz o mnie Barbazonowi. Skrytka znajduje się na plaży Grand Case między kamieniami blisko ślepego zaułka. Mało prawdopodobne, że będę go znowu potrzebować.";
			link.l1 = "Dobrze. Nie powiem Barbazonowi, że wciąż żyjesz. Jeśli to, co o nim mówią, jest prawdą, lepiej dla ciebie, by Holendrzy cię powiesili. Albo może będziesz miał szczęście i skazują cię na katorgę.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Czekam na człowieka, który wie, kiedy rozpocznie się polowanie na białego rekina.";
			link.l1 = "Polowanie się rozpoczęło.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Wreszcie! Słuchaj uważnie. Będziesz musiał odwiedzić Marcusa Tyrex w La Vega i powiedzieć mu, że brygantyna 'Separator' została zaatakowana w pobliżu wyspy Turks i teraz ukrywa się w Południowej Zatoce. Jej kapitan jest ciężko ranny, a załoga czeka na pomoc. Zabrałeś marynarza z 'Separatora' i opowiedział ci o wszystkim. Teraz jest martwy. To wszystko, co wiesz. Rozumiesz?";
			link.l1 = "A dlaczego w ogóle potrzebujesz mnie do tego? Czekałem zbyt długo tylko na to...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Jesteś opłacany za wykonywanie swojej pracy, a nie za zadawanie pytań. Masz jednak rację. Muszę cię ostrzec, że Tyrex nie pozwoli ci odejść, dopóki nie będzie pewien, że mówisz prawdę. Ale gdy dowie się wszystkiego, dobrze ci zapłaci. O ile będzie w stanie to zrobić...";
			link.l1 = "Zasłaniasz mi oczy, panie... Czemu sam nie chcesz przyjąć jego podziękowań?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Carramba! Nie podoba mi się twoja ciekawość! Twoje gadanie przywiedzie cię kiedyś prosto do grobu.";
			link.l1 = "Tak, czasami jestem nie do zniesienia. Zwłaszcza gdy widzę, że ktoś próbuje mnie oszukać. Nie, kolego, teraz będziemy grać według moich zasad. Kto jest twoim panem, cholera jasna? Odpowiedz, albo cię zmuszę!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Ty... drań! Barbazon za to zapłaci, a twoje życie się skończy, gówniarzu!";
			link.l1 = "Ha! Spodziewałem się tego. Przygotuj się, łotrze!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince? Co ty tutaj robisz? A-aaargh, do diabła, to ty! To wszystko twoja robota!";
				link.l1 = "Odpocznij Bernie. Jestem po twojej stronie. Zasadzka została zlikwidowana, ty i twój statek jesteście bezpieczni.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Kim jesteś, do diabła? Jak się tu dostałeś? Odejdź teraz, mój statek jest zaminowany, a dranie na brzegu mogą go wysadzić jednym strzałem.";
				link.l1 = "Nie martw się, panie. Zasadzka na brzegu została zlikwidowana. Twój statek jest teraz bezpieczny, o ile oczywiście nie zamierzasz zapalić fajki na pokładzie. Jak się nazywasz?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. A jakże ci na imię?";
			link.l1 = "Kapitan "+GetFullName(pchar)+"Przetnę te liny i uwolnię cię...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Och... moja wdzięczność. Jak mogę ci podziękować?";
			link.l1 = "To jeszcze nie koniec, Panie. Czy ktoś z twojej załogi wciąż żyje?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Trzy tuziny moich ludzi są zamknięte w ładowni...";
			link.l1 = "Wypuść ich i natychmiast się stąd wynoś.";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Ale...";
			link.l1 = "Nie trać czasu, Bernard. Podziękujesz mi później w La Vega... Tyrex może mi również podziękować.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Więc nie jesteś tu przypadkiem? Wiedziałeś o wszystkim?";
			link.l1 = "Tak, wiedziałem. Udało mi się odkryć machinacje Jackmana i jego plany zabicia Marcusa. Och, poproś Tyrexa, aby siedział spokojnie, jego mieszanie się może odstraszyć Jackmana.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Na pewno mu to powiem! Wyjeżdżasz teraz?";
			link.l1 = "Tak. I ty też powinieneś się pośpieszyć.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Naprawdę? Spójrz, przepraszam Cię, bracie...";
			link.l1 = "Zapomnij o tym. Pozwól, że przetnę liny i uwolnię cię.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Cholera... Nie czuję moich rąk...";
			link.l1 = "Bernie, czy na statku są jeszcze jacyś ocalali?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Trzydziestu ludzi jest zamkniętych w ładowni...";
			link.l1 = "Wypuść ich i wynoś się stąd, do diabła. Teraz!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Ale...";
			link.l1 = "Żegluj natychmiast do La Vega. Opowiedz Marcusowi o całym tym bałaganie ze wszystkimi szczegółami.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Czy Marcus cię przysłał?";
			link.l1 = "Nie zrobił tego. Udało mi się odkryć spisek jednego drania. Planował wyeliminować Marcusa przez tę intrygę. Poproś go, aby na razie się nie wtrącał... Wszystko mu później wyjaśnię osobiście. I proszę, powiedz mu, żeby przestał się na mnie gniewać.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Czego chcesz na moim statku, panie?";
			link.l1 = "Dzień dobry, Paul. Twoje imię to Paul Molligan, prawda?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Tak, to ja. Jak mogę ci pomóc?";
			link.l1 = " Nazywam się "+GetFullName(pchar)+" a Jan Svenson mnie przysłał.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan? A-ah, pamiętam cię. Oczywiście! Ostatnio ciągle odwiedzasz jego dom. Czego Jan ode mnie chce?";
			link.l1 = "Pędziłeś, by odpłynąć z Blueweld. Jan chciał załadować na twój statek dodatkowe dwieście cetnarów mahoniu, aby dostarczyć je lordowi Willoughby w Bridgetown. Przygotuj swój statek, moi ludzie załadują ten mahoń do twojej ładowni.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Mahoniowe drewno? Powiedział to Jan? Hm. A czemu sam nie dostarczysz go na Barbados? Czemu ja?";
			link.l1 = "Ponieważ ty tam płyniesz, a ja nie. Mam pilne zadanie od Svensona, więc nie mogę marnować czasu na podróż do Bridgetown. Poza tym, Jan nie ufa mi w interesach z lordem Willoughby i chce, żebyś to ty się tym zajął. Przepraszam. Teraz załadujemy towar, muszę iść.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Słuchaj, nie mam żadnego wolnego miejsca w ładowni. Nie będę w stanie zrobić tego, o co Jan mnie prosi, choć bym chciał.";
			link.l1 = "Brak miejsca? Dziwne... Jan powiedział mi, że macie trochę wolnej przestrzeni.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "Prawda to, lecz Jan nie wiedział, że wyposażyłem 'Ostrygę' w cięższe działa. Nie mogę załadować więcej towaru, niż już mam. Więc dostarcz drewno na Barbados sam, hej, kumplu? Powiedz Janowi, że nie mogłem tego zrobić. Zajmowanie się Willoughbym jest proste: po prostu go odwiedź, daj mu ładunek i weź pokwitowanie. To proste.";
			link.l1 = "Hm. To nie było w moim planie... Sprawdźmy twoją ładownię, dobrze? Mój kwatermistrz jest bardzo utalentowany w pakowaniu towarów, będzie w stanie umieścić towary w twojej ładowni i nawet zostawi ci trochę wolnego miejsca...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Kamracie, nie mogę przyjąć więcej towarów. Chcesz, żebym wyrzucił swoje działa i zostawił 'Ostrygę' bez ochrony?";
			link.l1 = "Cóż, jeśli jesteś tego taki pewien... Ale Janowi się to nie spodoba, weź to pod uwagę!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Wyjaśnię to Svensonowi, nie martw się. W końcu to jego wina, nie zapytał mnie o tonaż mojego statku.";
			link.l1 = "Eh, a teraz będę musiał płynąć z tymi kłodami aż na Barbados, do diabła... Żegnaj, kumplu.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Rozumiemy się, prawda?";
			link.l1 = "Tak, tak. Idę na mój statek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Czego ode mnie chcesz? Nie lubię plotek ani hazardu. A rum pijam w samotności. Poza tym, jestem w złym humorze po ostatnim rejsie.";
			link.l1 = "A cóż takiego szczególnego wydarzyło się podczas twego ostatniego rejsu?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Jeden dobry człowiek mi zaufał, a ja wyrzuciłem go za burtę, bo moja załoga tego żądała.";
			link.l1 = "A co było jego winą?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Jestem nowicjuszem i nie znam tu wielu ludzi. Dlatego zatrudniłem tego dobrotliwego grubasa jako chirurga, nie wiedząc o jego przeszłości. Piraci ścigali nas odkąd opuściliśmy Barbados. Dlaczego mieliby potrzebować mojej skorupy jajka?\nLedwo udało nam się uciec, dzięki silnemu wichrowi. Wypiliśmy za taką okazję. A ten gruby głupiec nie wymyślił nic lepszego, niż powiedzieć wszystkim, że piraci najprawdopodobniej go ścigali, bo jest byłym katem i zna rzeczy, których nie powinien znać.\nOczywiście moi ludzie naprawdę się wściekli. Naprawdę?! Kat na pokładzie, służący jako chirurg! I nikt nie chciał również zadzierać z piratami... Więc musiałem wysadzić biedną duszę. To wszystko jego wina, po prostu musiał otworzyć usta. Ale szkoda mi tego wieśniaka, był doskonałym lekarzem. Zajęło mu tylko minutę, by wyleczyć mój kac.";
			link.l1 = "Cholera! Twój lekarz nazywał się Raymond Baker, prawda?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Tak. Dokładnie. A skąd wiesz? Śledziłeś mnie?";
			link.l1 = "Nie, to nie byłem ja. Po prostu potrzebuję tego człowieka, jest wspaniałym lekarzem. Gdzie go zostawiłeś?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Szerokość geograficzna 15 stopni 28' na północ, długość geograficzna 63 stopnie 28' na zachód. Pośpiesz się, panie! On musi jeszcze żyć, a ty zdejmiesz ze mnie winę, jeśli go uratujesz!";
			link.l1 = "Już podnoszę kotwice!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Kapitanie, pośpiesz się! On musi jeszcze żyć!";
			link.l1 = "Tak, tak, już idę...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Ej! Zostań tam! Nie ruszaj się. To terytorium jest zabezpieczone!";
				link.l1 = "Nie bądź zbyt surowy, kumplu! Przyjaciele! Jackman nas przysłał. Musimy dostać się do kopalni. Rozkaz pana...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hej! Stój tam, gdzie stoisz! Nie ruszaj się. Ten teren jest zabezpieczony!";
				link.l1 = "Hm. Ale chcę przejść... Dlaczego do diabła mnie zatrzymujesz?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, znowu ty? Widzę, że nie rozumiesz... Chłopcy, ognia!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Chodź, ruszaj się!";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Ponieważ kopalnia za mną to własność prywatna, a ja jestem tutaj, aby powstrzymać każdego obcego, takiego jak ty, przed przejściem. Lepiej się odwróć i opuść to miejsce, nieznajomy. Nasze działa są załadowane kartaczami, jeszcze jeden krok i zamienisz się w mokrą kałużę.";
			link.l1 = "Ha, rozumiem. Twoja kopalnia ma poważną straż. Dobrze, odchodzę.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Ty, draniu! No cóż, zobaczymy, kto stanie się kałużą!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Dałem ci szansę... Chłopcy, ognia!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Ej! Odejdź! Ten teren jest zabezpieczony!";
				link.l1 = "Hej, wyluzuj, przyjacielu! Jackman nas przysłał. Musimy dotrzeć do kopalni. Rozkaz pana...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ej! Odejdź! To terytorium jest zabezpieczone!";
				link.l1 = "Hm. A co tam jest?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-a, znowu ty? Widzę, że nie rozumiesz... Chłopcy, ognia!!";
				link.l1 = "Hello, friend.";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Nie twój interes. Zjeżdżaj stąd, albo cię zastrzelimy, przysięgam!";
			link.l1 = "Spokojnie. Już odchodzę.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Ty, draniu! No cóż, zobaczymy, kto kogo zastrzeli!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Dałem ci szansę... Muszkiety gotowe! Ognia!!";
			link.l1 = "... ";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Naprawdę? Musisz wtedy znać hasło. Mów, ale pożałujesz, jeśli kłamiesz...";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attackx_1";
		break;
		
		case "mine_attackx_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Zgadza się. Ale ty, kolego, przyszedłeś tu z niewłaściwej strony. Nie ostrzegli cię? Wróć się i wybierz lewą ścieżkę od suchej studni. Potem obejdź wzgórze i tam zobaczysz główną bramę.";
				link.l1 = "Czy nie mogę tu wejść?";
				link.l1.go = "mine_attackx_2";
			}
			else
			{
				dialog.text = "Chłopaki, mamy szpiega! Muszkiety gotowe! Ognia!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_attackx_2":
			dialog.text = "Nie. Tylko przez centralne wejście.";
			link.l1 = " Dobra, koleś... Hej! Patrz! Co to, do diabła, jest na szczycie palisady?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Naprawdę? W takim razie powinieneś znać hasło. Powiedz je głośno, żebym mógł je usłyszeć. A jeśli spróbujesz mnie oszukać, będzie to ostatni dowcip, jaki w życiu zrobisz komuś.";
			link.l1.edit = 5;
			link.l1 = " ";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Zgadza się. Idź dalej. Głowa obozu znajduje się w domu po lewej stronie od wejścia do kopalni. Idź i zobacz się z nim.";
				link.l1 = "Dobrze, kumplu...";
				link.l1.go = "mine_attack_2";
			}
			else
			{
				dialog.text = "Chłopaki, mamy szpiega! Armaty, otworzyć ogień!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_attack_2":
			DialogExit();
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Cóż jeszcze? Czy coś zapomniałeś?";
			link.l1 = "Tak. Poproszono mnie, bym przekazał ci najlepsze pozdrowienia.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Do mnie? Ha-ha! Od kogo?";
			link.l1 = "Jan Svenson, ty draniu!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			LAi_SetPlayerType(pchar);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			if (pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
			}
			else
			{
				for (i=1; i<=6; i++)
				{
					sld = characterFromId("Mine_bandit_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
				AddDialogExitQuest("MainHeroFightModeOn");	
			}
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
			pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
			pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Rozszarpiemy tych drani na kawałki!","Nie mogę się doczekać, aż skopię tym szumowinom tyłki!","Sługusy Jackmana nie mają prawa przebywać na Zachodnim Wybrzeżu! Przepędzimy ich stąd!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Jesteśmy gotowi do walki!","Pokażemy im!","Nie wiedzą nawet, z kim zadzierają!");
			link.l1 = "...to jest naprawdę nieoczekiwane.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Dowódco, armata jest gotowa. Została załadowana bombą, dokładnie tak, jak kazałeś.";
			link.l1 = "Rozumiem, że nikt się nas tu nie spodziewa... Czas się przedstawić. Jan powiedział mi, że ich obóz jest za tym wzgórzem. Czy będziesz w stanie tam dotrzeć?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Łatwizna, dowódco. Podnieśmy beczkę trochę, to powinno wystarczyć... zrobione.\nGotowi!.. Ogień!!";
			link.l1 = "... ";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, myślisz, że w coś uderzyliśmy? Chciałbym usłyszeć twoją opinię.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Dowódco, trafiliśmy w coś lub kogoś, ale nie mogę być bardziej precyzyjny... ta przeklęta góra zasłania widok. Zmienię kąt.\nGotowy! Ognia!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha! Spójrz, dowódco! Dym! Cholera, musieliśmy trafić w jakąś bandycką stodołę! Hurra-ah!";
			link.l1 = "Tak, widzę dym... Już epickie zwycięstwo, bez wątpienia. Przeładuj broń i skieruj ją na ścieżkę, wygląda na to, że nadchodzą nasi goście. Przywitamy ich odpowiednio!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Tak jest, dowódco! Załaduj bombę! Załoga dział gotowa! Lont gotowy! Ognia na mój rozkaz!";
			link.l1 = "... ";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ha-ha, to musi boleć!";
			link.l1 = "Jeszcze się nie rozluźniaj! Ładuj działo! Nie sądzę, żeby mieli dość. Nadciągają kolejni!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Aj-aj, dowódco! Załaduj bombę! Gotowe! Ognia na mój rozkaz!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ha-ha-ha, pokazały nam swoje plecy, dranie! Psia kość! Kartacz miażdży ich z takiej odległości! Wygląda na to, że nie są na tyle odważni, by zaatakować nas ponownie!";
			link.l1 = "Teraz nasza kolej. Randolph, zostaniesz tutaj przy armatce. Strzel kilka razy w stronę ścieżki, a potem celuj w dym - spal ich legowisko! Tylko nas nie zastrzel.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Aye-aye, Komendancie! Przygotować armatę! Załadujcie bombę!";
			link.l1 = "Ludzie! Do broni! Za mną, atak! Hurra!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Nie krzywdź mnie, nie jestem jednym z nich! Zabij bandytów!","Uwolnij nas, kumplu! I zabij ich wszystkich!","Potnij ich, przyjacielu, potnij! Zabij ich!");
				link.l1 = "Ha! Nie martw się, właśnie tym się teraz zajmujemy.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Czy nasza niewola się skończyła? Czy uwolnisz nas?","Heh, czyżby udało mi się przetrwać, by zobaczyć ten dzień?","Sukinsyny wyssały z nas całą krew....");
				link.l1 = "Myślę, że wkrótce będziesz mógł cieszyć się wolnością, kumplu...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Lepiej opuść to miejsce, panie. Nie kryjemy przestępców i nie potrzebujemy żadnych konfliktów z władzami kolonii.";
				link.l1 = "Dobrze, wychodzę...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ach, Helen. Mogłaś ubrać się nieco przyzwoiciej, zanim przyszłaś zobaczyć się z Janem, zamiast pokazywać mu, jaka naprawdę jesteś. Szkoda, że mi nie wierzy.";
					link.l1 = "A jakiż to ja jestem? On pomógł mnie wychować od dzieciństwa i zna mnie lepiej niż ktokolwiek inny. Nie mam przed nim tajemnic. Cierpię z tego upału od małego, więc musiałem sobie z tym radzić na swój sposób, ot co.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", sirze. Czy chcesz zobaczyć Jana?";
				link.l1 = "Dzień dobry. Miło było cię poznać, panno?..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan jest w środku. Idź naprzód, nie ma tu nic do zobaczenia, a ty działasz mi na nerwy.";
					link.l1 = "Tak czy siak, nie miałem na to ochoty.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "I zdrowia dla ciebie też, pani Svensson.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Kapitanie "+GetFullName(pchar)+". Jeśli jesteś tu po Jana, to muszę cię rozczarować - nie ma go tutaj. Wyjechał załatwiać jakieś ważne sprawy.";
					link.l1 = "Do diabła! A ja go potrzebuję! Powiedz mi, pani Svenson, czy mówił, kiedy wróci?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-a, znowu ty, Kapitanie "+GetFullName(pchar)+"... idź dalej, Jan jest na górze, jak zwykle.";
				link.l1 = "Dziękuję, pani Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Proszę pani, pani Johanna Svenson.";
			link.l1 = "Kapitan "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Kapitana? Cóż, cieszę się, że mogę powitać cię w moim domu. Ale jeśli jesteś tu z powodu Jana, to muszę cię rozczarować - jego tu nie ma. Wyjechał załatwiać jakieś ważne sprawy.";
				link.l1 = "Cholera! A ja go potrzebuję! Powiedz mi, pani Svenson, czy mówił, kiedy wróci?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Kapitanie? Cóż, cieszę się, że mogę powitać cię w moim domu. Mój mąż jest na drugim piętrze w swoim gabinecie. Idź na górę.";
			link.l1 = "Zrozumiałem, pani Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Nie. Nawet nie powiedział mi dokładnej daty powrotu, bo sam nie wie, jak długo potrwa poszukiwanie.";
			link.l1 = "Przepraszam za wtrącanie się, ale naprawdę go potrzebuję... Jakie poszukiwania prowadzi?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Powiem ci. Urocza Helen, znana również jako Rumba, córka jego zmarłego przyjaciela Seana McArthura, zniknęła. Jan traktuje młodą diablicę jak własną córkę. Przypomina mu jego dawną miłość, która miała ten sam lekkomyślny temperament. Przynajmniej to jest według mnie powód przyciągania.\nTak czy inaczej, dziewczyna zniknęła tydzień temu wraz ze swoją szkunerem 'Tęcza' i całą jego załogą. Sean McArthur nauczył ją żeglugi, a 'Tęcza' została jej przekazana w testamencie. A teraz bawi się w kapitana...";
			link.l1 = "Co mogło się jej przydarzyć?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Kto wie... Tydzień to nie tak długo, ale wdowa po McArthurze jest pewna, że coś stało się jej córce i udało jej się przekonać do tego również Jana. Zorganizował swoich ludzi i sam zaczął jej szukać, jak dotąd bez rezultatu. Osobiście, myślę, że Helen ma się dobrze, a Jan tylko męczy się bez powodu.\nZa dużo nasłuchał się bzdur tej starej, grubej kobiety i spanikował. Dziewczyna najprawdopodobniej w tej chwili bawi się z innym chłopakiem, daleko od ludzkich oczu, w bezpiecznym miejscu. Wróci, jak tylko zaspokoi swój głód.";
			link.l1 = "Johanna, gdzie mogę znaleźć Gladys? Chcę z nią porozmawiać...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Jej dom jest blisko przystani, po lewej stronie. Ale prawdopodobnie jej tam nie ma. Codziennie marnuje czas stojąc na murach fortu, wypatrując swojej ukochanej córki.";
			link.l1 = "Rozumiem. Dzięki wielkie za informacje!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan jeszcze nie dotarł, kapitanie, więc wróć później.";
			link.l1 = "Widzę...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "You're always in heat, I'd say. You should go to church; I've barely ever seen you there.";
			link.l1 = "Sumienie mam czyste - nie mam za co prosić o przebaczenie. Nadal złoszczę się, że pomógł zaopatrzyć mój statek zamiast kupić dla ciebie kolejną suknię, Joanno?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Ja? Zgorzkniały? Nie jesteś tego wart. Po prostu wszystko przychodzi ci zbyt łatwo, a nie zasługujesz na to.";
			link.l1 = "Lecz jak tylko zdobyłem ten statek, zacząłem zarabiać na własną rękę. A odkąd on cię przygarnął jak bezdomnego kota, nie przepracowałeś ani dnia. Więc kto tak naprawdę żyje na jego koszt?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Jeśli będziesz tak dalej gadać, to pewnego dnia dostaniesz, na co zasłużyłeś. Jan i Gladys powinni cię nauczyć manier. Dobrze, mów, co masz do powiedzenia - i znikaj mi z oczu, Helen. On jest w środku.";
			link.l1 = "Głupia kura. Pewnie, zrobię to.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Hej! Co ty tu robisz?";
			link.l1 = "Chciałbym zadać ci to samo pytanie - co ty i twoi kumple robicie tutaj, w mojej lochach?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ha! Twoje lochy? A kiedy stały się twoje, cioto?";
			link.l1 = "Dzień, w którym twój ojciec popełnił błąd, pieprząc twoją matkę.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Szukasz kłopotów?";
			link.l1 = "Słuchaj, kumplu, daję ci ostatnią szansę, żeby stąd wyjść. To jest moje lochy i nie pozwolę nikomu swobodnie się tu kręcić, zrozumiałeś? Wystarczy, że raz zagwiżdżę, a połowa piratów z Isla Tesoro będzie tu w minutę.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "No cóż, spróbujemy cię uciszyć!";
			link.l1 = "Ha-ha! Jesteś żałosny, łajdaku!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Chwila, sokołu!";
			link.l1 = "Niezbyt dobry moment, skarbie.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Och, mylisz się, przystojniaku. Ta dziewczyna cię lubi, a to uczucie jest wzajemne, widzę to.";
			link.l1 = "Nie najlepsza rekomendacja... Dobrze, czego chcesz? Jałmużny?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Chcę zaproponować ci wsparcie w twoim trudnym przedsięwzięciu. Spójrz tu! Magiczny kubek i zakazany maść. Kubek pomoże ci w sprawach picia, a maść - w sprawach miłości. Co wybierasz? Tylko dwa tysiące!";
			link.l1 = "Nie potrzebuję niczego - już dałem całe mnóstwo srebra twoim podobnym.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Zakazany balsam, mówisz? Cóż, nie jestem świętym, przyznaję. Daj go tutaj.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Kufel? Czy wyglądam na pijaka? No, kogo ja oszukuję... Wezmę go!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Przystojny, ale głupiec. Odleć więc, sokole.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Ach, nie chowaj tego w swoich bezdennych kieszeniach! Leć, sokole, i nie grzesz!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Och, nie chowaj tego do swoich bezdennych kieszeni! Leć, sokołe, i nie grzesz!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ach! Wynoś się stąd, łajdaku! Ile razy ci mówiłem, żebyś nie właził do mojego domu! A kto to jest?";
			link.l1 = "Proszę pani, już się znamy.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure? No toż to wspaniale! Tak właśnie załatwiasz interesy z moim mężem?! Wiedziałam! Ostrzegałam Jana: pewnego dnia ta flądra zacznie sprowadzać jego ludzi na manowce! A co masz w rękach?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Wha-a-a-at?! How dare you, wretch?! You're not going anywhere; my husband will be here any moment now and he'll teach you how to talk to the elders!";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "Co się tu dzieje? Panno MacArthur! Miałem ogromny szacunek do twego ojca, a pan Svensson jest naszym przyjacielem... Ale czy nie pamiętasz, jak to się skończyło ostatnim razem?\nTo rozczarowujące, słowo oficera, rozczarowujące! Mogłaś nas zaprosić!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Dziękuję za twoją gościnność, Panno MacArthur. Pozwól, że powiem, iż wszyscy jesteśmy bardzo zadowoleni z twojego powrotu. To, co się stało, jest wielką tajemnicą, ale nie jest zaskoczeniem, że miasto o tym wie. Mimo to mogę obiecać, że nikt nie będzie plotkować. Składam szczere przeprosiny za ostatnie zachowanie jednego z naszych kapitanów. I chciałbym podziękować tobie osobiście, panie de Maure.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Wszystko będzie dobrze, panienko. Panie de Maure, będę szczery - mimo że Donovan zachowuje się jak prawdziwy łotr i bandyta, flota nigdy otwarcie go nie potępi. Bardziej prawdopodobne, że nawet go obronią. Wasza mała ekspedycja trafiła do raportów i znacznie skomplikowała stosunki między naszymi krajami. Niemniej jednak, biorąc pod uwagę wpływy pana Svenssona, jak również niezwykłe ustępstwa poczynione Wam przez Capsterville, nie macie się czego obawiać.";
			link.l1 = "Toż to wspaniałe. Powiadam, że napijemy się za to!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Przepraszam uprzejmie, a co z pracą?";
			link.l1 = "Czy nadal tu jesteś?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Drogi panie, dokądże mogę się udać? Właśnie poszedłem się odlać, podsłuchałem waszą sentymentalną rozmowę i trochę się rozgrzałem. Emocjonalnie, mam na myśli!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Panie Boże! Cóż, skoro dałem ci moje słowo, nie da się nic zrobić. Idź, przejmij dowodzenie.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Nie mam dla ciebie pracy, panie.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Szkoda! W każdym razie, dzięki za poczęstunek, Kapitanie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "W imię Ojca i Syna, i Ducha Świętego... wejdź, mój synu.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Witaj, Matko Amelio. Czy zamierzasz na mnie też krzyczeć?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Zniknij! Co to za koszmar? Co się dzieje? Czy to sen?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "Nie, mój mały sokołku. I wybacz Janowi - biedak się uniósł. Ale tak, chcę cię zganić. Dlaczego przyszedłeś do kościoła? Aby pokutować za grzechy? A może interesowała cię ta rudowłosa?";
			link.l1 = "Sam nie wiem...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Widziałeś ją też? Przykuła mój wzrok.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Zniknij sam. Powinniśmy już się spotkać, ale wszystko przeciągasz. Dlaczego przyszedłeś do kościoła? Żeby pokutować za swoje grzechy? A może chodziło ci o rudowłosą?";
			link.l1 = "Sam nie wiem...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Widziałeś ją też? Przyciągnęła mój wzrok.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Dzień dobry, mój sokole. Przyjęcie jeszcze się nie rozpoczęło, proszę poczekać w kolejce.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Witaj, Wasza Ekscelencjo. Czy zamierzasz również na mnie krzyczeć?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Zniknij! Co to za koszmar? Co się dzieje? Czy ja śnię?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "No, my falcon. And forgive Jan, the poor man got worked up. No need to scold you; you did everything right - didn't go after the red-haired one to the church. Good boy!";
			link.l1 = "Chwalą mnie? To miłe. Zwłaszcza jeśli wiadomo, za co.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Widziałeś ją też? Przykuła mój wzrok.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Znikaj stąd. Powinniśmy się już spotkać, ale wszystko przeciągasz. Chodź tu, pochwalę cię - nie poszedłeś za tą rudą do kościoła. Dobry chłopak!";
			link.l1 = "Chwalić się jest miło. Zwłaszcza, gdy wiadomo za co.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Widziałeś ją też? Przykuła mój wzrok.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Nie będę cię zanudzać szczegółami, głuptasie, ale powiem ci to: jesteś przeznaczony na wielkość. Przyniesiesz wiele zła, lecz znacznie więcej dobra. Ale szczęście nie jest ci zagwarantowane. Szczęście, mój sokołu, jest dane tylko tym, którzy kroczą swoją ścieżką i nie zbaczają z niej. A wierna kobieta pomoże ci nie zbaczać.\nBędziesz miał dwie z nich, i obie przyniosą szczęście, ale musisz wybrać tę jasnowłosą.";
			link.l1 = "Dlaczego tak miałoby być? Sam o tym zadecyduję!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Oczywiście, wybierz sam, ale ta jasnowłosa jest lepsza. Tak postanowiliśmy.";
			link.l1 = "Kto to my?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "Ta nieszczęsna nawet nie zna swego prawdziwego imienia. Wypowiedz je, a będzie twoja. Tak się mówi.";
			link.l1 = "Już nic nie rozumiem.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Słyszysz to pukanie? Otwórz, i nie myl się.";
			link.l1 = "Rzeczywiście, ktoś puka... Proszę wejść!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, pan Svensson prosił, byś poświęcił mu chwilę czasu.";
			link.l1 = "Cholera, to nie wróży dobrze. Spróbuję, ale bez obietnic.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Szczęśliwy dzień, chłopcy! Mówiłem wam, że prędzej czy później tu przyjdzie, prawda? Dobra, Słodziutka, oddaj broń i chodź z nami.";
			link.l1 = "Źle to pojęliście, chłopcy. Ona jest ze mną.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Trzymaj się z dala od tego, albo zastrzelę cię jak psa. Za dziewczynę oferują dobrą sumę, a my jesteśmy głodnymi facetami, którym brak zasad.";
			link.l1 = "Jeśli będziesz dalej do mnie mówić w takim tonie, to rozwiążę twój problem z głodem na zawsze.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Oszalałeś kompletnie, Lucky? To my ją znaleźliśmy pierwsi! Lepiej miej dobry powód, żeby drzeć na mnie ten swój głupi pysk!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "You're the rat here! We had just torn a big fat Spaniard apart; we can sit on our asses for a year!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Cóż, kogoż to my tu mamy. Dobra, wszyscy inni, wynocha, a ty, pani, chodź z nami.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Przewyższamy was liczebnie i jesteśmy twardsi, Duńczyku. Jakiego innego powodu potrzebujesz, ty szczurze lądowy? Minęło sześć miesięcy, odkąd widziałeś przyzwoity łup, a ty jesz okruchy chleba z Vuazie'ego stołu!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Wygląda na to, że tutaj nie będzie pokojowego rozwiązania.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "Co powiedziałeś? Szczęściarz? Słyszałem plotkę, że on i Vuazie spiskowali, by dawać ci podejrzane wskazówki. To wyjaśnia twoją serię pecha na morzu.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Zmęczony jestem tą farsą. Isla Tesoro, słuchajcie mnie! Kto był ze mną w Cartagenie?! Kto spalił Meridę ze mną?! Te szczury śmią atakować samego Księcia Charliego! Pokażmy im, chłopcy!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Jeszcze tu jesteś, galareto? Dobra, chłopcy, ruszamy: przywiążcie kapitana, a z dziewczyną zajmiemy się później, zrozumiano?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Jasne, przynajmniej rozlejmy trochę krwi. Hehe.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "Co?! Diable, wiedziałem, że knujesz z tym okularnikiem łajdakiem! Przetnijcie ich wszystkich, chłopcy, a dziewczynę odbierzemy później!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "„Co ty bredzisz, kapitanie? Zjeżdżaj, zanim porządni ludzie omówią interesy.”";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "Co tam gawędzisz, kapitanie? Widziałem Charlie'ego Prince'a, a ty mu nie dorównujesz. Zmykaj stąd, gdy szanowni ludzie omawiają interesy.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure? Syn Henriego de Monpe?";
			link.l1 = "To prawda, monsieur. A kimże jesteś?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Colonel Francois de Tavanne. You may consider this a direct challenge, monsieur; the gauntlet for the duel has been laid. I don't even wish to dirty my hands with you, but I swear, my blade will taste your blood!";
			link.l1 = "Pojedynek? W takim razie musisz się bardziej postarać, pułkowniku. W tej chwili, można by cię pomylić jedynie z bandytą, a w tych stronach rozmowy z takimi są krótkie! Wytłumacz się!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Uwiodłeś moją żonę, monsieur! Podczas gdy ja przelewałem krew dla króla i ojczyzny, ty... ty bawiłeś się z moją żoną!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Cisza, pani. Twoje zuchwałe stroje hańbią honor każdej kobiety, chociaż wydajesz się całkiem odpowiednia obok tego niegodnego uwodziciela szlachetnej kobiety!";
			link.l1 = "To wciąż zbyt mały powód do pojedynku, pułkowniku. I pozwolę sobie zauważyć, że również tu zachowujesz się niegodnie.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Czy to nie wystarcza? Dowiadywałem się - na moim miejscu mogłoby być teraz tuzin szlachetnych mężów, panie. Ale jeśli chcesz szczegółów, to ze wstydem przyznaję, że jedną z twoich pasji była Lulu de Tavann, najpiękniejsza i najuczciwsza z kobiet!";
			link.l1 = "Lulu, mówisz... A jak się miewa?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Milcz! Moja żona, nie mogąc znieść męki, którą zadałeś, niedawno zmarła! Spędziłem prawie rok i majątek, by cię odnaleźć, łotrze! Dość słów! Albo przyjmij wyzwanie, albo zabiję cię jak psa. Richard! Bądź moim świadkiem!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Cisza, panie! Przyjmij wyzwanie albo stracisz wszelkie resztki honoru, które ci jeszcze pozostały!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = " Pojedynek to pojedynek. Nie będę kłamać, lubię je. Kapitanie, przekaż pułkownikowi, że czas, by zamówił odpowiednią trumnę.";
			} else {
				link.l1 = "Chcesz walki? To ją dostaniesz! Kapitanie, przekaż pułkownikowi, że czas, aby zamówił odpowiednią trumnę.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "To nie Europa, Pułkowniku. Honor na Karaibach trudniej zdobyć, ale też nie tak łatwo stracić. Odmawiam pojedynku, bo po prostu go nie chcę.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Twój ojciec już jedną nogą w grobie, łajdaku! I upewnię się, że dowie się o twoim tchórzostwie!";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Panie Pułkowniku, potwierdzam pańskie prawo do pojedynku, ale nie pozwolę na zwykłe bandytyzm! Monsieur de Maure, jestem kapitan Richard Small. Czy jest Pan gotowy zadowolić pułkownika de Tavann?";
			link.l1 = "Chwileczkę, Kapitanie. Dobrze znałem Lulę... a ona... miała skłonność do częstej zmiany adoratorów, a jej zdrowie było lepsze niż moje... Jak zmarła, Pułkowniku? Przed czy po twoim powrocie do domu?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Proszę, Francois, pozwól mi. Monsieur de Maure, zostałeś wyzwany. Oficerskie towarzystwo Blueweld uznało, że żądanie satysfakcji pułkownika de Tavann jest uzasadnione. Przyjmij wyzwanie albo stracisz honor.";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, proszę, jesteśmy tutaj szlachcicami. To nieodpowiednie. Pułkownik przebył taką drogę, by cię spotkać! To skandal!";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = " T-tak, oczywiście, panienko. Ale ja...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Kapitanie de Maure, dzień należy do ciebie! Nie była to najwłaściwsza walka, ale dziś obroniłeś swój honor.";
			link.l1 = "Czy coś mówiłeś, kapitanie? Może uda mi się wcisnąć jeszcze jeden pojedynek w dzisiejszy rozkład.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Moje przeprosiny, Kapitanie. To tylko nerwy!";
			link.l1 = " Myślę, że twoja obecność tutaj nie jest już konieczna.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Sprawiedliwa decyzja! Nawet jeśli nie została przedstawiona w najbardziej godny sposób... Panowie! Zaczynajmy!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Kapitanie, może nie rozumiem wszystkich tych wyszukanych słów, które rzucają te dygnitarze, ale widzisz, jeśli ktoś zostaje nazwany tchórzem, zwykle nie puszczasz tego płazem. Uderz go, Kapitanie, bo nasza załoga zacznie się martwić.";
			link.l1 = "Chcecie krwi? Życie za nudne, brak emocji? Dostaniecie swoją krew, wy zwierzęta!";
			link.l1.go = "francois_duel";
			link.l2 = "Bu-hu, tak się boję. Czy skończyliście już, panowie? Mam miejsca, gdzie muszę być.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "It won't look good if our captain backs down from a public challenge. Just give that nobleman a good whack; we know you're great with a sword!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Tchórz! Libertyn! Szczur! Boisz się, łajdaku? Czy wszyscy to widzieliście?! Richard, i tak go zabiję!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "Ty łotrze! Nic to, jestem przyzwyczajony do ran. Dojdę do siebie, i...";
			link.l1 = "Brzmi jak groźba, pułkowniku. A groźby nie są miłym słowem.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Kiedy już dojdziesz do siebie, nie zapomnij pochwalić się oficerom okolicznościami swojego zranienia.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen approves", "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
