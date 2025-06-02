// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ach, Kapitanie! Wiesz, powiedziałem Helen wszystko. Nie wyobrażasz sobie, jaki ciężar spadł mi z serca!";
				link.l1 = "Zrobiłaś wszystko, co trzeba, panna McArthur. Dziewczyna musi znać prawdę. A ja jestem tutaj z jej powodu.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Witaj, "+pchar.name+"! Cieszę się, że cię widzę! Chcesz trochę rumu?";
				link.l1 = "Dziękuję, panno McArthur, ale teraz jestem zbyt zajęty.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "Czego sobie życzycie, Panie?";
			link.l1 = "Czy jesteś Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Jestem. Nie pamiętam cię, młody człowieku. Więc czy zechcesz wyjaśnić, czego ode mnie chcesz?";
			link.l1 = "Interesuje mnie historia zniknięcia waszej córki, panno McArthur. Co sprawiło, że pomyśleliście, iż zniknęła? Słyszałem, że Helen miała bardzo wprawną załogę...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ach, jestem absolutnie pewna! Zobacz, rocznica śmierci mojego świętej pamięci męża była pięć dni temu. Helen kochała swojego ojca i nigdy nie przegapiłaby tej daty. Wyjechała tylko na kilka dni, aby odebrać ładunek czerwonego drewna od przyjaznych ludzi Miskito.\nIndianie szanują i boją się naszego patrona Jana Svensona, nigdy by jej nie skrzywdzili. Pan Svenson już z nimi rozmawiał. Drewno zostało załadowane tego samego dnia. Nikt nie widział Helen od tamtej pory.";
			link.l1 = "Może piraci ją zaatakowali?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Nonsens! Już musisz wiedzieć, że pan Svenson jest jednym z pięciu baronów piratów i członkiem rady Braci Wybrzeża. Żaden pirat nie ma prawa polować tutaj bez jego zgody. To jednak mógł być nowicjusz...";
			link.l1 = "A co z Hiszpanami? Czy mogła napotkać hiszpański patrol?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Nie znam się na polityce, ale mówią, że miejscowe kopalnie złota i srebra są całkowicie wyczerpane, nie ma już wiele skarbów, dla których warto ryzykować życie szlachetnych hidalgos. Dlatego są tu rzadkimi gośćmi. Poza tym Indianie są wobec nich wrogo nastawieni.\nPrzypadkowe spotkanie z hiszpańskim patrolem nie mogło źle skończyć się dla Helen, z ich punktu widzenia nie zrobiła nic nielegalnego. 'Tęcza' miała holenderską banderę, a wszystkie papiery Helen były w porządku, łącznie z licencją handlową.";
			link.l1 = "Czy wydarzyło się coś szczególnego przed jej ostatnią podróżą? Może jakieś dziwne zdarzenie, które umknęło twojej uwadze?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ach, nie! Dzięki Bogu, żyjemy tu spokojnie. Jednakże, kilka tygodni temu Helen otrzymała list od kolejnego niechcianego adoratora, który błagał o spotkanie. Jest ładną dziewczyną, ale nie bogatą.\nMa wielu adoratorów, choć żadnego z nich nie lubi i nie chce się żenić. Już w ten sposób oszukała wielu ludzi. Taka lekkomyślna, zupełnie jak jej matka!";
			link.l1 = "Nie wyglądasz na taką kobietę, panno McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "Co? Ah, nieważne, jestem załamany. O czym to mówiłem? Ah, tak, o liście. W każdym razie, ten list napisał Jimmy Higgins. Jest jednym z ludzi Jackmana i mieszka w Maroon Town. Odwiedza nasze miasto dość często. Jackman to też baron piratów, ale pan Svenson go nie lubi, nie wiem dlaczego.";
			link.l1 = "A Helen?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Ona śmiała się na głos. Dostała propozycję od kapitana angielskiej korwety dzień wcześniej i nawet jego odrzuciła. A teraz ten zwykły bosman ze starego pirackiego statku... Nie ma szans, córka Seana McArthura żąda bardziej imponującego męża!";
			link.l1 = "I jakże się zwał ten angielski kapitan?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Och, skąd mam wiedzieć? Prawdziwi dżentelmeni rzadko tutaj goszczą. Przepraszam, nie chciałam Cię obrazić. Zapytaj tego Higginsa. On musi pamiętać jego imię. Jimmy próbował wyzwać tamtego kapitana na pojedynek dla Helen. Jego kumple ledwo zdołali go powstrzymać przed tym. Ale obaj opuścili Blueweld kilka dni przed tym, jak Helen odpłynęła.";
			link.l1 = "Cóż, dzięki za twoją opowieść. Spróbuję odnaleźć twoją ukochaną. Jeśli czegoś się dowiem, powiem tobie lub panu Svensonowi. Mam nadzieję znaleźć twoją córkę żywą i całą.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Idziesz jej szukać? Niech Bóg będzie z tobą, niech cię prowadzi i wzmacnia twoją dłoń! Będę się za ciebie modlić! Powiedz mi swoje imię, szlachetny człowieku?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+" Mam nadzieję, że wkrótce powrócę z dobrymi wieściami, panno McArthur. Żegnaj!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Czy masz jakieś nowe informacje o mojej biednej córce, "+pchar.name+"? ";
			link.l1 = "Przepraszam, panno McArthur, jak dotąd nie mam nic nowego do powiedzenia, ale nie trać nadziei. Będę kontynuować poszukiwania. Brak złych wieści to także dobre wieści.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Spóźniłeś się, kapitanie. Ciało mojej biednej córki znaleziono na brzegu Antigui. Panie, jakże ją torturowali przed śmiercią! Nie zdołałem ocalić mojej pięknej dziewczyny...";
			link.l1 = "Przykro mi. Nie mogłem nic zrobić...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ach, młodzieńcze, proszę, zostaw mnie samego z moim żalem...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Nie wiem nawet, jak ci dziękować, Kapitanie, za uratowanie mojej córki. Powiedziała mi wszystko i podziwiam twoją odwagę i honor. Proszę, weź te złote dublony. To niewiele, ale oferuję je z całego serca. I nawet nie myśl o odmowie!";
			link.l1 = "Dobrze, Gladys, nie zrobię tego. Ale uratowałem twoją córkę nie dla monet i mam nadzieję, że o tym wiesz.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Zachowaj te pieniądze dla siebie, Gladys. Potrzebujesz ich bardziej niż ja.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Cieszę się, że mogłem w jakiś sposób odpłacić ci za twój honorowy czyn. Drzwi mojego domu są zawsze dla ciebie otwarte. Helen i ja będziemy z radością cię witać o każdej porze.";
			link.l1 = "Dziękuję, panna McArthur. Odwiedzę ciebie i Helen, gdy nadarzy się okazja.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ach, proszę... Chciałem tylko odpłacić ci za twój honorowy czyn. Wiedz, że drzwi mojego domu są zawsze dla ciebie otwarte. Helen i ja będziemy zadowoleni widzieć cię w każdej chwili.";
			link.l1 = "Dziękuję, panna McArthur. Odwiedzę was z Helen, gdy tylko nadarzy się okazja.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Kapitanie, zawsze jesteś mile widziany w naszym domu! Czy przyszedłeś po Helen? Obawiam się, że zamknęła się w swoim pokoju - musi być wyczerpana po ostatnich kilku dniach. Nie martw się, czasami jej się to zdarza.";
				link.l1 = "Naprawdę? Jesteś pewien, że z nią wszystko w porządku?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ach, Monsieur de Maure! Zawsze cieszę się, widząc wybawcę mojej córki w moim domu. Chcesz zobaczyć Helen? Jest na górze, w swoim pokoju. Po utracie 'Tęczy' i jej cudownym ocaleniu unika wychodzenia na zewnątrz. To pierwszy raz, kiedy widzę ją w takim stanie zamieszania...";
			link.l1 = "Dziękuję, panna McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ach, Monsieur de Maure! Zawsze cieszę się, widząc zbawcę mojej córki w mym domu. Czy chcesz zobaczyć Helen?";
			link.l1 = "Nie. Chcę zadać ci kilka pytań i naprawdę liczę na twoją szczerość. Od tego zależy bezpieczeństwo Helen. Czy ten pierścień jest ci znany?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Na Boga! To jest... pierścień jej ojca!";
			link.l1 = "Pana McArthura?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "Nie. Helen jest naszą pasierbicą, ale ona o tym nie wie, jej rodzice zmarli, więc postanowiłem przyjąć ją jako moje dziecko. Sean ją adoptował, ale nawet on nie wiedział, że nie jest moją córką.";
			link.l1 = "Kim są jej prawdziwi rodzice?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "Znam jej ojca, był piratem zwanym 'Rzeźnik' na fregacie 'Neptune'. Widziałem go tylko dwa razy. A jej matka była piękną młodą kobietą, rude włosy, ubrana w męskie ubrania. To wszystko, co mogę ci o niej powiedzieć, poza tym, że była złą matką.\nNigdy nie zostawiłbym takiego dziecka w rękach obcych. Oboje zginęli tragicznie. A obiecany kurier pojawił się dwadzieścia lat później i okazało się, że to ty. Czy Rzeźnik cię wysłał? Czy on żyje?";
			link.l1 = "Spokojnie, panno Gladys! Nie ma powodów, by podejrzewać, że Rzeźnik ożył, choć jesteś drugą osobą, która to zasugerowała. Niedawno spotkałem człowieka, który miał ci pokazać ten pierścień...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "";
			link.l1 = "Prosty incydent przeszkodził mu w wykonaniu zadania na czas i cierpiał przez całe życie, ponieważ nie wykonał ostatniego rozkazu swojego kapitana. Zmarł niedawno i... cóż, dość smutnych wieści. Powiedz mi, Gladys, czy matka Helen nie zostawiła żadnej pamiątki dla swojego dziecka ku pamięci jej? Może jakąś drobnostkę?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Zostawiła mi dziwny kawałek starej mapy. Żartowała, że to jej dziedzictwo. Co dobrego może zrobić ten kawałek papieru? Wierzę, że to był tylko zły żart. Była nadmiernie podekscytowana i trochę niespełna rozumu. Ale zachowałem ten 'prezent'.\nKto wie... Jeśli chcesz, mogę ci go dać, jeśli obiecasz, że pewnego dnia opowiesz mi całą historię.";
			link.l1 = "Absolutnie, panna McArthur. Zabiorę ten skrawek ze sobą na chwilę. Muszę porozmawiać z panem Svensonem.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Znowu nam pomogłeś, Monsieur de Maure! I nie mam pojęcia, jak ci podziękować. Weź przynajmniej pistolet mojego męża. Zawsze był z niego dumny i mówił mi, że to bardzo rzadka rzecz. Leży tu od dawna. Niech ci służy! Weź go, weź!";
			link.l1 = "Dzięki, Gladys. Ta pistolet jest naprawdę doskonała. Dziękuję i żegnaj.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Niech ten pistolet służy Helen. Mam wystarczająco broni.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "Ale dlaczego ciągle odrzucasz moje dary? Sprawiasz, że jestem zmartwiony...";
			link.l1 = "Myślę, że teraz będę w stanie cię uszczęśliwić. Oddam złoto, które kurier miał dostarczyć tobie na godne utrzymanie córki kapitana Rzeźnika. Oczywiście, te dublony nie spłacą całej twojej miłości i lojalności, ale i tak należą do ciebie. Możesz z nimi zrobić, co tylko zechcesz.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ach, Kapitanie! Nie wiem, co powiedzieć... Nie mogłem sobie wyobrazić, że tacy... honorowi ludzie istnieją! Idź do mojej córki i przekaż jej te dobre wieści!";
			link.l1 = "Jestem w drodze, Panna McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Jesteś poważny? Co masz na myśli?";
			link.l1 = "Zgodnie z żądaniem pana Svensona, zamierzam zatrudnić Helen na moim statku jako oficera. Jest w wielkim niebezpieczeństwie. Helen będzie potrzebowała solidnej ochrony, podczas gdy Jan i ja zajmujemy się tą sprawą. Mam nadzieję, że będę w stanie zapewnić taką ochronę.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ach, toż to wspaniale! Nie śmiałbym prosić cię o to sam. To będzie najlepsza ochrona dla mojej dziewczyny. Helen będzie zachwycona, że znów może żeglować!";
			link.l1 = "Dziękuję za komplement, panno McArthur. A teraz muszę zobaczyć twoją... pasierbicę.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "O, Boże! Moja mała dziewczynka!";
			link.l1 = "Gladys, czy nie wiesz, że trzeba pukać?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "O, wybaczcie mi, młodzi ludzie! Odchodzę! Helen, pamiętaj, co ci powiedziałem!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = " Myślę, że tym razem po prostu się przepracowała. Powiedziała mi wszystko, Kapitanie! Dziękuję, że pomogłeś jej wybrać nowy statek wczoraj!";
			link.l1 = "Co? Hm, proszę bardzo. Żegnaj, pani MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
