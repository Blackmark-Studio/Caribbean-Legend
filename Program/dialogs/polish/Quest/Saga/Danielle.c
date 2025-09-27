// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Poczekaj, przystojniaku! Myślę, że powinniśmy porozmawiać.";
			link.l1 = "Czy ja cię znam? Tak czy inaczej, zawsze mam kilka dodatkowych godzin dla damy.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Jeszcze nie planuj, kapitanie. Znajdź sobie jakąś młodszą, głupio wyglądającą dziewczynę na kilka dodatkowych godzin. Mam dla ciebie interes. Jestem mężatką. Mój mąż nazywa się Nathaniel Hawk.";
			link.l1 = "Toż to coś niesamowitego! Więc musisz być tym, hmm... Dannie Hawk, pan Svenson cię wspomniał.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "W ciele. Tak, wiem, że Leśny Diabeł nie ma o mnie wysokiego mniemania, uczucie jest wzajemne, ale musiał cię ostrzec, że noszę szablę nie tylko dlatego, że jest ładna. Więc przejdźmy do rzeczy, synu!\nŚledziłam Swensona i jego gości przez jakiś czas, ponieważ to on wysłał mojego męża do dżungli na śmierć. Myślałam, że współpracuje z Jackmanem, ale teraz widzę, że tak nie jest. Ukrywałam się pod oknem podczas waszej rozmowy. Nie mogłam podsłuchać wszystkiego, ale dowiedziałam się wielu przydatnych informacji.\nCzy naprawdę chcesz odnaleźć mojego męża i skopać Jackmanowi tyłek? Czy tylko rzucałeś tanie słowa?";
			link.l1 = "Podsłuchiwanie to zła rzecz, Madame Hawk. Ale wybaczę ci, jeśli będziesz rozmawiać ze mną w bardziej szacowny sposób. Szukam Hawk albo nie, to tylko moja sprawa. Mów, jeśli masz coś pożytecznego do powiedzenia, albo zostaw mnie w spokoju, jeśli nie masz. Nie będę pytał dwa razy.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A-ha, taki gorąca głowa! No dalej, Kapitanie... Mój temperament na pewno nie sprawia, że czujesz się komfortowo. Widzę, że nie jesteś tchórzem i znasz swoją wartość. Więc... zapoznajmy się. Obiecuję, że będę ostrożny z tym, co ci mówię. Potrzebuję cię, a ty mnie. Dzielimy wspólne cele. Przyjmij mnie do swojej załogi, a nie pożałujesz. Będę ci służył z dobrą wiarą i wiernością, dopóki nie znajdziemy Nathana, masz moje słowo.";
			link.l1 = "Uważaj się za przyjętą... Dannie. Svenson powiedział mi, że już szukałaś swojego męża. Czy znalazłaś coś interesującego?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Nie za wiele, ale wystarczająco, by oskarżyć Jackmana o kłamstwo. Drań powiedział, że strażnicy kopalni, ci, z którymi zmierzył się mój Nathan, nie brali jeńców. I chociaż prawdą jest, że nikt nie widział ciała mojego męża w zatoce, to jak mogli, skoro faktycznie został zabrany do kopalni jako więzień. Snake Eye, szaman ludu Miskito, znalazł go tam.\nOn również zorganizował jego ucieczkę. Ale gdzie teraz jest mój mąż, to pozostaje nieznane. Szaman mamrotał coś o jakimś Kukulcanie, który go pożarł, ale nic nie zrozumiałam. Poza tym czerwonoskóry jasno dawał do zrozumienia, że białe kobiety to dla niego tylko żart. Powinieneś z nim porozmawiać, może będzie bardziej rozmowny.";
			link.l1 = "To przynajmniej coś! Takie wieści mnie cieszą. Gdzie mogę znaleźć tego Indianina?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Jest wioska głęboko w dżungli. Musimy wylądować w Zatoce Amatique i iść na zachód przez dżungle. Pokażę ci drogę, jeśli sam jej nie znajdziesz. Kamienny idol można znaleźć niedaleko wioski, a dzikusy czczą go jako swojego boga. Byłem tam kilka razy. Nic specjalnego, naprawdę. Po prostu zwykły kamień pokryty mchem.";
			link.l1 = "Interesujące. Dobrze, chodźmy. Porozmawiamy z szamanem i zobaczymy, co dalej robić. Gotowy?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Oczywiście! Oczywiście, jestem gotowy. Podróżuję cały czas odkąd opuściłem Maroon Town. Poza tym nie chcę być tylko jednym z twoich pasażerów.";
			link.l1 = "Dobrze. Chodźmy na mój statek.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = " "+pchar.name+" ! Chodź! Pokażę ci kamiennego idola, o którym mówił indiański szaman. Po prostu zwykły kamienny filar. Chodźmy!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Hej! Spójrz, to tylko kamienna statua. Nic szczególnego...";
			link.l1 = "Widzę... Choć postać na szczycie jest nieco złowieszcza, nie sądzisz? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "Wszystkie indyjskie posągi są przerażające i wyglądają złowrogo. Widziałem coś podobnego wcześniej. Wszystkie są takie same. Tak czy inaczej, chodźmy, wioska jest niedaleko!";
			link.l1 = "Chodźmy!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "Więc, co powiesz, "+pchar.name+"? Co ten czerwonoskóry brzuchomówca ci powiedział? Czy dowiedziałeś się czegoś z jego filozoficznych słów?";
			link.l1 = "Czy znowu podsłuchiwałeś, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Cóż... trochę. Wiesz, my kobiety po prostu takie jesteśmy. Ale musisz zrozumieć - po prostu martwię się o mojego męża. Tak naprawdę go kocham. I co z tego, że podsłuchuję? W każdym razie, dowiedziałeś się czegoś użytecznego?";
			link.l1 = "Próbuję się zastanowić... nie było łatwo zrozumieć Wężowe Oko. Jednakże, wydaje się, że idol, który widzieliśmy w drodze do wioski, to jakiś magiczny portal, który może teleportować ludzi.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Nie patrz na mnie tak. To nie mój pomysł i jak dotąd nie mam problemów z głową. Pytałeś, co mi powiedział szaman, więc ci mówię.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Proszę, wybacz mi. Nie będę już tak na ciebie patrzył. Idź dalej.";
			link.l1 = "Powiedział, że gdy Nathan był niemal schwytany przez swoich prześladowców, Indianin pokazał mu posąg jako sposób na ratunek, nazywając go Kukulcan i mówiąc, że pochłonął Nathana żywcem i wypluł go gdzieś indziej. Mówiąc prosto, wydaje się, że Nathan został teleportowany przez posąg.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Boże, co do... Ja i Nathan już wcześniej wpadliśmy w podobne tarapaty, a teraz to się powtarza. Mieliśmy dość przygód z tym indiańskim świątynią pełną magii Majów...";
			link.l1 = "Coś ty powiedział?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Ach, to nic, "+pchar.name+", to nie ma znaczenia. Tylko wspomnienia mej gorącej młodości. Ale jak Nathan mógł to zrobić? Mam na myśli teleportację? Przecież byliśmy tylko przy tym idolu, chodziłem wokół niego i dotykałem go... to tylko kamień!";
			link.l1 = "Wężowe Oko powiedział mi, że idol ożywa o północy. Tylko wtedy zaczyna świecić złotym kolorem, gdy duch Kukulkana do niego wchodzi. To czas, kiedy nie powinno się go dotykać. Albo wręcz przeciwnie, powinno się...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Straszne... I co teraz? Poczekajmy do północy i wtedy idźmy do dżungli?";
			link.l1 = "Nie. Szaman powiedział, że idol nie tylko teleportuje ludzi, ale także pożera ich życie. Jak go zrozumiałem, chodziło mu o to, że wysysa ich zdrowie. Wężowe Oko przeszedł przez te posągi trzy razy i leczył się jakimś unikalnym eliksirem po każdej teleportacji.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Pytałeś go o tę miksturę?";
			link.l1 = "Oczywiście. Ale po pierwsze, zostały tylko trzy flakony, a po drugie, zażądał trzech amuletów w zamian za nie.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "A może by tak bez mikstury? Chodźmy do posągu nocą i dotknijmy go...";
			link.l1 = "Zbyt ryzykowne. Przyznaję, że Indianin jest trochę szalony i robi nas w balona, ale nie wygląda na psychopatę, więc wierzę, że mówi prawdę. Pamiętam, że mówiłeś mi coś o indiańskiej magii... Czy wątpisz w jej istnienie?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Tak, byłem. Nie wątpię, ponieważ widziałem to na własne oczy. Więc, przypuszczam, że masz rację, nie ma sensu ryzykować.";
			link.l1 = "Dokładnie. Dlatego najpierw znajdziemy amulety, potem zdobędziemy ten cudowny eliksir od szamana i pójdziemy do posągu. Pójdę. Sam.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Dlaczego tak? A co ze mną?";
			link.l1 = "Zostaniesz na moim statku i będziesz dowodzić, gdy mnie nie będzie. Nawet nie próbuj się sprzeczać, Dannie. Są tylko trzy fiolki mikstury. Nie wiadomo, dokąd prowadzi portal, jeśli szaman ma rację i to coś naprawdę działa. Być może nawet nie będę w stanie znaleźć tam Nathana.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Jesteś taki sam jak Nathan. Wszyscy mężczyźni są tacy sami... Dobrze, zgadzam się.";
			link.l1 = "To dobrze, że się rozumiemy. Chodźmy teraz, musimy znaleźć amulety.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "Więc co? Zdobyłeś mikstury?";
			link.l1 = "Tak. Mam mikstury i kilka wskazówek. Jedyne, co pozostało do zrobienia, to udać się do idola o północy i go dotknąć.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Boisz się?";
			link.l1 = "Tak. Obawiam się, że szaman może okazać się po prostu szalony i teleportacja się nie wydarzy.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Cóż, cóż... Naprawdę się nie boisz? Ani trochę?";
			link.l1 = "Dannie, nie naciskaj mnie... Jeśli naprawdę chcesz wiedzieć, to cóż, muszę przyznać, że nie czuję się zbyt pewnie.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Pójdę z tobą.";
			link.l1 = "Czy zamierzasz znowu się kłócić? Myślałem, że mamy umowę...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Źle mnie zrozumiałeś. Będę tylko przy tobie. Muszę się upewnić, że posąg działa... lub że nie działa.";
			link.l1 = "Nie mam żadnych zastrzeżeń. Ale nawet nie myśl o podążaniu za mną, jeśli posąg mnie 'pożre'. Słyszysz mnie?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Tak, obiecuję, że nie będę cię śledzić... Kapitanie.";
			link.l1 = "Dobrze. A, Dannie, wydaje się, że nie jesteś taką suką, jak mówią.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Nie znasz mnie zbyt dobrze, "+pchar.name+"Ale nie rozmawiajmy o tym teraz.";
			link.l1 = "Niechże... Cóż, powinniśmy się przygotować do naszej nocnej wyprawy!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Spójrz, "+pchar.name+" ! Przysięgam na wszystko, co święte, nad posągiem unosi się dziwne światło!";
			link.l1 = "Zdaje się, że szaman nie kłamał. A jeśli ciemność mnie nie zwodzi, to szczyt posągu nie wygląda już na taki kamienny.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Dokładnie... Wygląda na to, że jest wykonane z czystego złota! Niesamowite!";
			link.l1 = "Nadszedł czas, Dannie. Życz mi powodzenia i trzymaj kciuki za mnie. Nie zbliżaj się do posągu! Zostań tutaj.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Powodzenia, "+pchar.name+"  Miejmy nadzieję, że to zadziała... Czy przygotowałeś miksturę szamana?";
			link.l1 = "Tak, mam to tutaj. Wszystko będzie dobrze, Dannie. No to ruszam! (Naciśnij T, aby aktywować idola)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ach?! Cholera! Co to za potwór, do diabła?! Pierdol się! Widziałem gorsze stworzenia w swoim życiu, w tym samego Van der Deckena! Teraz dam ci to, czego żądasz!";
			link.l1 = "(cicho) Dannie, czekaj! Przestań! Teraz!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(słabo) Van der Decken? Ha-ha-ha-ha! Ten robak już mi służy! Teraz twoja kolej! Skłoń się przede mną, wierny sługo! Poprowadzisz moją armię umarłych!";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
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
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Odejdź! To nie może się teraz dziać!";
			link.l1 = "(cicho) Dannie, zaczekaj! Przestań! Teraz!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Ah?! Co powiedziałeś?! Dannie?";
			link.l1 = "(słabo) Przestań natychmiast! Trzymaj swój szablę! Pozwól mi to zdjąć!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Cholera, brzmiesz jak potwór... "+pchar.name+"?!";
			link.l1 = "O-o... Nie mów!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Do diabła, prawie mnie na śmierć przestraszyłeś! Byłem o krok od tego, żeby cię ciąć moją szablą!";
			link.l1 = "Widziałem to... a dlaczego jesteś taki zapalczywy, co?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "To właśnie ja... Och, moje serce wciąż bije jak oszalałe...";
			link.l1 = "Dannie, gdzie teraz jesteśmy? Niedaleko wioski Miskito, prawda?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Gdzież indziej moglibyśmy być! To jest posąg, który sprawił, że zniknąłeś. To było spektakularne! Zapamiętam to do końca życia.";
			link.l1 = "Widzę, że czekałeś na mnie tutaj cały czas?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Powiedz mi, co innego miałem zrobić? Po tym, jak posąg cię pożarł, mogłem tylko mieć nadzieję, że pewnego dnia cię wypluje. Poza tym, Wężowe Oko powiedział, że to najprawdopodobniej się stanie.\nŻyłem z Miskito i obserwowałem idola każdego dnia. Dlaczego w ogóle rozmawiamy o takich bzdurach? Powiedz mi! Co się tam stało? Gdzie byłeś?";
			link.l1 = "Dannie, ta historia jest zdecydowanie za długa, widziałem tak wiele... Ale żeby ulżyć sobie, powiem ci, że znalazłem Nathaniela!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Znalazłeś Nathana? Gdzie on jest? I jak sobie radzi?!";
			link.l1 = "Nie będę kłamał - on żyje, ale czuje się naprawdę kiepsko. Nie miał mikstury Komanczów, a idol wyssał całą jego energię. Leży w kajucie jakiegoś starego i zniszczonego statku na dziwnej Wyspie Porzuconych Statków. Mnie również tam teleportowano, więc Snake Eye miał rację!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = " Biedny Nathan... Gdzie jest ta przeklęta wyspa? Jak się tam dostać?! Tylko przez bożka? Spróbuję wykupić każdą zdrowotną miksturę od Miskito i pójdę tam tej nocy! Jakoś się uda...";
			link.l1 = "Stój! Czekaj! Nathan jest chory, ale jego życiu nic nie grozi. Jeden chłopak się nim opiekuje i karmi go. Jeśli przejdziesz przez idol, zrujnujesz swoje zdrowie, a wyspa jest naprawdę niebezpieczna. To zbyt ryzykowne!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "A więc co sugerujesz? Nic nie robić, podczas gdy Nathan cierpi lub może umiera?";
			link.l1 = "Przestań histeryzować. Po pierwsze, powiedziałem ci, że Nathan jest chory, ale nie umiera. Rozmawiałem z nim. Po drugie, popłynę na wyspę i ty popłyniesz ze mną.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Czy wiesz, gdzie znajduje się ta wyspa?";
			link.l1 = "Oczywiście, że tak! Znalazłem tam nie tylko Nathana, ale także Rekina Dodsona. Mam przybliżone współrzędne Wyspy i wskazówki, jak ominąć rafy wokół niej. A teraz wracamy na mój statek i płyniemy do Blueweld...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "Po co? Dlaczego nie możemy teraz popłynąć prosto na Wyspę?";
			link.l1 = "Dannie, muszę zorganizować wyprawę. Na Wyspie brakuje zapasów, więc kupię tyle jedzenia, ile zdołam. Potem będę musiał wybrać statek, który tam popłynie, nie wszystkie statki będą w stanie ominąć rafy Wyspy. Chcę też najpierw porozmawiać ze Svensonem...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Nie zajmie to dużo czasu, by się przygotować. Wyspa nie jest daleko stąd, leży na północny zachód od Hawany, na wschód od Zatoki Meksykańskiej.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Dobrze... zróbmy to zatem. Znalazłeś Nathana i to najważniejsze. Dziękuję! Czy on się tam czuje źle?";
			link.l1 = "Cóż... jest chory. A na dodatek jest też przygnębiony i zrozpaczony. Tęskni za tobą. I tak, Nathan poprosił mnie, bym powiedział, że bardzo cię kocha.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "„(wycierając łzę) Stary głupiec! Nigdy mnie nie słuchał... ”"+pchar.name+", ruszajmy na twój statek! Chcę tam popłynąć jak najszybciej!";
			link.l1 = "Oczywiście, Dannie. A ja opowiem ci o swoich przygodach. Chodźmy!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "    Nigdy wcześniej nie widziałem takiego miejsca. Cała wyspa zrobiona jest z okrętów!  ";
			link.l1 = "Opowiadałem ci o tym, Dannie...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Ale teraz mogę to zobaczyć na własne oczy. W każdym razie, powiedz mi, gdzie znaleźć Nathaniela?";
			link.l1 = "On jest wewnątrz jednego ze statków. Ale musisz tam dopłynąć.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Nie obchodzi mnie to. Powiedz mi, jak dotrzeć do tego statku.";
			link.l1 = "Dannie, uspokój się. Ty i Nathan czekacie już długo, więc miejcie jeszcze trochę cierpliwości! Zaprowadzę was do niego, sami go nigdy nie znajdziecie. Nie chcę, żebyście natknęli się na Narwale lub Rivados, zaczniecie się z nimi kłócić i to się źle skończy.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Dobrze, chodźmy więc. Pójdę za tobą.";
			link.l1 = "Nie zapomnij, że będziemy musieli dużo pływać.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "W porządku, dam sobie radę.";
			link.l1 = "Cieszę się, że to słyszę... Wkrótce zobaczysz swojego męża!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! Cholera! Moja miłości...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Jezu, spójrz tylko na siebie... Dlaczego to sobie zrobiłeś?!.. (płacząc) Nigdy mnie nie słuchasz, nigdy! Mówiłem ci, żebyś nie szedł do tej selvy! Ale i tak tam poszedłeś! Dlaczego, Nathan?!";
			link.l1 = "Dannie... Przykro mi. Nie miałem wyboru, wiesz o tym...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Ja to wiem! O Boże, kochanie... co się z tobą stało! (przez łzy) Wszystko będzie dobrze, kochanie, wszystko będzie dobrze... Jestem tutaj. Zabierzemy cię do Miskito, do Oka Węża."+sld.name+"  powiedział mi, że szaman będzie w stanie cię uzdrowić. Mamy statek... Wszystko będzie dobrze!";
			link.l1 = "Dannie, kochanie... moja miłości! Twoja obecność tylko w połowie mnie uzdrowiła. Pójdziemy, gdzie tylko powiesz. Jeśli do Snake Eye, to do niego.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Spakuj swoje rzeczy. Och, ależ ja jestem głupi... Nie ma rzeczy do spakowania, oprócz pustych butelek. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... wybacz mi i Nathanowi za tę scenę.";
			link.l1 = "Dannie! Wybaczyć ci za co? Wszystko w porządku. Czy wstydzisz się swoich uczuć?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "Nie, nie jestem... To tylko...";
			link.l1 = "Nikt nigdy nie dowie się o tej scenie. Obiecuję. I nikt nie dowie się, co się stało z Nathanem. Piraci z Maroon Town ujrzą silnego i groźnego Nathaniela Hawka!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Dziękuję, "+pchar.name+" ! Jestem ci wdzięczna... Zabiorę mojego męża na statek. Nie martw się, dam sobie radę, żeby go tam przetransportować, pamiętam drogę. Położę go do łóżka i zostanę przy nim. Odpłyniemy do Węża Oka, gdy skończysz wszystko, co musisz tutaj załatwić. Wierzę w jego zdolność do uzdrowienia Nathana.";
			link.l1 = "Dobrze, Dannie. I tak nie zostaniemy tu długo. Jesteś pewien, że nie potrzebujesz pomocy?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Jestem pewna. Dotrzemy do statku. Nie martw się, nie pozwolę, by mój mąż umarł!";
			link.l1 = "Dannie, jesteś... cudowna!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(ocierając łzę) Idź... po prostu idź, "+pchar.name+"... i proszę, nie trać tu czasu!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "A cóż z tego? Czy on uleczy mojego męża? Powiedz mi, że go uleczy!";
			link.l1 = "Dannie, Nathan będzie musiał tu zostać. Sam. Szaman prosił, by nie przeszkadzać jego rytuałom. To dotyczy także ciebie. Obiecał wyleczyć Nathana w ciągu miesiąca.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Wiesz, "+pchar.name+", teraz wreszcie mogę znów swobodnie oddychać. Mocno wierzę, że szaman przywróci mojego męża do normalnego stanu. Zostawię tu Nathana bez wahania, bo jeśli Wężowe Oko nie będzie w stanie go wyleczyć - nikt nie będzie.";
			link.l1 = "Wszystko będzie dobrze, Dannie. Wężowe Oko nigdy mnie nie okłamało. Ufaj mu.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Ja też. Zostanę z tobą na jakiś czas, "+pchar.name+", jesteś z tym w porządku? W końcu musimy jeszcze znaleźć tego drania Jackmana, to on jest odpowiedzialny za wszystkie nasze kłopoty. To on zorganizował zasadzkę! Zajął miejsce Nathana w Maroon Town! Ukradł naszą fregatę 'Centurion'!";
			link.l1 = "Zgoda. Musimy się rozprawić z Jackmanem. Nikt z nas nie jest bezpieczny, dopóki Jackman nie zginie. Nie będzie łatwo go zabić jednakże.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Masz jakieś plany, "+pchar.name+"?";
			link.l1 = "Jeszcze nie. Muszę udać się do Jana Svensona i poprosić go o radę. Róbmy jedno po drugim, musimy promować "+sTemp+" do przywódcy Bractwa Wybrzeża najpierw. Więc, musimy zdobyć głos każdego barona piratów, by to zrobić.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = " Dobrze, idźmy do Swensona. Posłuchajmy, co powie ten stary piernik...";
			link.l1 = "Wiesz, nie powinieneś być tak negatywnie nastawiony do Jana. Właściwie, byłoby o wiele lepiej, gdybyś się z nim pogodził... w końcu wszyscy mamy wspólny cel!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Ale tylko dlatego, że cię szanuję... Dobrze, "+pchar.name+", Przepraszam. Nie chciałem obrazić Svensona, po prostu jestem zdenerwowany. To się nie powtórzy.";
			link.l1 = "Dobrze. Dannie, wszystko będzie w porządku. Mogę ci to obiecać!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Całkowicie ci ufam, "+pchar.name+"Chodźmy do Svensona?";
			link.l1 = "Chodźmy, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Tak? Słucham. Jak mogę pomóc?";
			link.l1 = "Masz jakieś pomysły, gdzie Jackman może się ukrywać? Znasz tego drania lepiej niż ja. Może ma jakieś miejsce, bazę...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Cholera, jeśli wiem! Jacob zawsze był bardzo tajemniczy. Nigdy nie słyszałem o jego kryjówce. Pewnie lepiej spróbować pomyśleć logicznie... Przeczytajmy jeszcze raz list, który dostałeś od Knive'a. Może znajdziemy tam jakąś wskazówkę.";
			link.l1 = "Spróbujmy...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Hmm... wspomina o Isla Tesoro i jakimś testamencie... Brzmi znajomo?";
			link.l1 = "Ja i Jan myślimy, że Blaze Sharp został zabity przez Jackmana na Isla Tesoro, a Shark został za to obwiniony. A testament... cholera... to musi być o Helen... Do diabła, jak mogłem tego wcześniej nie zrozumieć! Ten drań musi żeglować w pobliżu Isla Tesoro!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Nie traćmy zatem czasu, "+pchar.name+"?";
			link.l1 = "Tak. Chodźmy na Isla Tesoro. Stary 'Marlin' pomoże nam w tym rajdzie.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "Ostatni ten drań nie żyje... Nie mogę w to uwierzyć - znowu stoję na pokładzie 'Centuriona'! Znam każdy gwóźdź tutaj i wygląda na to, że statek mnie też rozpoznał.";
			link.l1 = "Znowu jest twoja, Dannie. Twoja i Nathaniela.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "Nie możesz sobie nawet wyobrazić, jak bardzo się cieszę. Nathaniel często mówił o naszym statku, ucieszy się, gdy dowie się, że znów jest nasz.";
			link.l1 = "Co teraz zamierzasz zrobić, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Ja? Wezmę statek do miasta Sharp, wynajmę przynajmniej minimalną załogę i popłynę do Blueweld. Poproszę Jana Swensona, aby zaopiekował się 'Centurionem', udam się do ludu Miskito i poczekam tam, aż Wężowe Oko wyleczy mego męża.";
			link.l1 = "Naprawdę zamierzasz odwiedzić Jana Swensona? Jestem zaskoczony...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", to wszystko dzięki tobie. Myślałem o twoich słowach: 'wszyscy mamy ten sam cel'. Pamiętasz? Chcę zawrzeć pokój ze Svensonem, w końcu pomógł mi odzyskać Nathana. Czas przestać się kłócić.";
			link.l1 = "Mądre słowa, Dannie! Nathaniel będzie mógł odzyskać swoje stanowisko w Maroon Town, gdy tylko poczuje się lepiej.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Może... rzecz w tym, że baron piratów to urząd wybieralny. A co, jeśli inni zdecydują inaczej?";
			link.l1 = "Niech Svenson się tym zajmie. Potrafi każdego przekonać. Eliminacja Jackmana też odegra swoją rolę.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Dobrze. Muszę i tak zaprzyjaźnić się ze Svensonem... "+pchar.name+"! Chcę podziękować Ci za wszystko, co dla mnie i Nathana zrobiłeś. Uratowałeś mojego męża i oddałeś nam wszystko, co straciliśmy. Jestem Ci winna.";
			link.l1 = "Chodź, Dannie. Jesteśmy przyjaciółmi.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Chcę, żebyś wiedział, że zawsze będziemy się cieszyć, widząc cię w Maroon Town. Znajdź nas tam, gdy będziesz miał trochę czasu. Nathaniel i ja znajdziemy sposób, aby cię wynagrodzić.";
			link.l1 = "Na Boga, Dannie! Przyjmuję twoje zaproszenie z przyjemnością. Usiądziemy, wypijemy i porozmawiamy o tym, jak ty i Nathan zatopiliście Van der Deckena...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Powiedział? Och, nie przypominaj mi o tym...";
			link.l1 = " Dobrze, Dannie. Masz przed sobą dużo pracy, a ja muszę odwiedzić naszych zaprzysiężonych przyjaciół - Marcusa i Barbazona. Mam nadzieję, że pozwolisz mi przewrócić tę kajutę do góry nogami, jestem pewien, że w skrzyniach Jackmana kryje się wiele interesujących rzeczy.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Jasne, naprawdę uważasz, że będę się sprzeciwiał?";
			link.l1 = "Miło. Tak naprawdę szkoda się z tobą rozstawać, Dannie... Do zobaczenia w Maroon Town!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = " "+pchar.name+" , bardzo się cieszę, że cię widzę! Znowu jesteśmy w Maroon Town, a Nathan jest znowu na swoim miejscu. Właściwie, wszyscy w wiosce się z tego cieszą. Teraz wszystko będzie szło tak dobrze, jak dawniej! Jestem bardzo wdzięczna za twoją bezinteresowną pomoc!\nChcę ci dać prezent. Proszę, weź to. Ten talizman może uczynić walkę o wiele łatwiejszą dla ciebie. A ta formuła pozwoli ci zrobić więcej z nich dla siebie.";
			link.l1 = "Dzięki, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "To nie wszystko. Znalazłem tutaj również dwie skrzynie pełne złota. Bez wątpienia należały do Jackmana. Weź je jako dowód mojej wdzięczności. I nie waż się odmówić! Wiem, ile pieniędzy zmarnowałeś, aby mi i Nathanowi pomóc.";
			link.l1 = "Dobrze, dobrze, Dannie, przyjmuję ich!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Doskonale! "+pchar.name+", chcę, żebyś wiedział, że od teraz jesteś naszym najlepszym przyjacielem. Nathan i ja zawsze będziemy się cieszyć, widząc cię w Maroon Town! Odwiedzaj nas częściej!";
			link.l1 = "Dzięki! Będę zadowolony, by zobaczyć cię znów, więc oczekuj mnie!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "Co możemy dla ciebie zrobić, "+pchar.name+"?";
				link.l1 = "Ach, właśnie wychodzę... Żegnaj, Danny.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "A oto "+GetFullName(pchar)+"Z twojej twarzy można wyczytać, że nie marnowałeś czasu!";
					link.l1 = "Muszę przyznać, że wiesz, jak się bawić! Dziękuję, bawiłem się świetnie.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "Cieszę się, że cię widzę, "+pchar.name+"Rum, wino? A może dziewka?";
			link.l1 = "Dzięki, Dannie! Po prostu chciałem cię zobaczyć...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "Ta dziewczyna? Cicho, Danny! Nie chcesz chyba znaleźć mnie pociętego na kawałki i starannie złożonego pod swoim progiem, prawda? Ha-ha. Moja wierna dama, która stoi tuż za drzwiami, nie wybaczy mi takich sztuczek.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "Dziewczyna? To brzmi interesująco, Danny. Tęskniłem za... biciem kobiecego serca... Myślę, że powinienem się przyjrzeć - nie zaproponowałbyś byle kogo, prawda?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Naprawdę? Czemu jesteś taki blady? Ha-ha, tylko żartowałem. Opiekuj się nią, słyszysz?";
			link.l1 = "Oczywiście. Jest dla mnie cenniejsza niż wszystkie skarby w tych stronach!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "To lepiej, ha-ha. No już, idź, twoja ukochana pewnie zaczyna się niepokoić.";
			link.l1 = "Żegnaj, Danny. I dziękuję za troskę, ha-ha.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "Zapewniam cię, ta młoda piękność z pewnością wie, jak zapewnić ci niezapomniany czas, "+pchar.name+". Baw się dobrze! Będzie czekała na Ciebie w pokoju tawerny.";
			link.l1 = "Dziękuję, Danny. Już idę. Nie chcę tracić ani minuty!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", zawsze jesteś mile widziany w Maroon Town. Najlepsze dziewczęta są do twojej dyspozycji!";
			link.l1 = "O, Danny. Przysięgam, to mój drugi dom.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "A oto mój kapitan. Dziś jesteś tylko mój! Chodź do mnie, czekałam na ciebie tak długo...";
			link.l1 = "O, naprawdę? Nie możesz już dłużej czekać? Cóż, nie traćmy czasu!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("Mój kapitanie... naprawdę wiesz, jak podbijać damy! Nigdy wcześniej czegoś takiego nie miałem! Może zostaniesz jeszcze na parę godzin?","Już odchodzisz, mój drogi?");
			link.l1 = RandPhraseSimple("Wiedziałem, że nie będziesz chciała mnie tak łatwo puścić. Żegnaj, maleńka. Wielkie rzeczy na mnie czekają...","Niestety, praca stoi na przeszkodzie. Ale może jeszcze się spotkamy...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Wreszcie ja i Nathan możemy znów swobodnie oddychać! Ten przeklęty sukinsyn Jackman nie żyje! Żal mi 'Centuriona', ale już pogodziłem się z jej stratą, gdy ten drań ją mi ukradł. Więc nie martwię się zbytnio.";
			link.l1 = "Ależ ja wiem. Jestem idiotą! Wszystkie dowody zatonęły na dnie morza razem ze statkiem. Mogły nam pomóc w wyborze nowego przywódcy Bractwa Wybrzeża. Teraz... wszystko przepadło.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Nie denerwuj się zbytnio! To się zdarza. Następnym razem będziesz mieć więcej szczęścia... Nieważne. Chcę ci podziękować za to, co zrobiłeś dla mnie i Nathana. Uratowałeś życie mojego męża. Jestem ci bardzo wdzięczna.\nChcę, żebyś wiedział, że Maroon Town zawsze będzie cię chętnie widzieć. Odwiedź mnie i Nate'a tam, kiedy będziesz miał czas. Znajdziemy sposób, żeby ci się odwdzięczyć.";
			link.l1 = "Dobrze, Dannie. Na pewno cię odwiedzę. Czy już odchodzisz?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Tak, pójdę do Miskito, mam nadzieję, że Wężowe Oko już uleczył Nathana. Potem wrócimy do Maroon Town.";
			link.l1 = "Heh, już się do ciebie przyzwyczaiłem, szkoda, że muszę się z tobą rozstać... Powodzenia, Dannie!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Och, nie udawaj głuptasa, kochanie. Charles, ten amorek kręcił się wokół tego idola dniem i nocą, i ciągle męczył biednego Wężowe Oko pytaniami. A potem pobiegła do domu i coś mu przyniosła, prawda?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "O, dzięki za przedstawienie, Charles. Całe Maroon Town będzie o tym plotkować, ha-ha!";
			link.l1 = "Nie mam wątpliwości, że to teraz twój priorytet - upewnić się, że tak się stanie.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "Na samym dole mojej listy, właściwie. Nie złość się na dziewczynę - to jej pierwszy raz. Kiedy Nathan i ja mieliśmy nasze przygody, całe archipelag też się z nas śmiał.";
			link.l1 = "Zmienićmy temat i nastrój. Mam dość tego bożka, chodźmy.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "Zgoda, ruszajmy, bohaterze.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "Czego chcesz, kapitanie?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, chcę Cię prosić o radę!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Słuchaj mojego rozkazu!";
            Link.l1.go = "stay_follow";
			link.l2 = "To nic. Zwolniony!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Rozkazy?";
            Link.l1 = "Stań tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Podążaj za mną i trzymaj się blisko!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Zmień rodzaj amunicji do swojej broni palnej.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybór rodzaju amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Zaszła zmiana nastawienia!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Nastąpiła zmiana usposobienia!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
