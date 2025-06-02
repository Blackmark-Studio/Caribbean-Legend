// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "Co Senor sobie życzy? Przepraszam, ja tylko...'szlocha'... oh... Prosze wybaczyć.";
					link.l1 = "Dlaczego jesteś tak zmartwiona, droga Pani? Łzy na tak pięknej twarzy? Co się stało?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = "Panie! Panie, pomóż! Mordują!";
				link.l1 = "Co? Kogo mordują? Gdzie? To jakiś żart, moja droga?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Jak miło znów cię widzieć... Dziękuję, że wpadłeś... ale wydaje się, że teraz nie jest najlepszy czas na nasze rozmowy. Przyjdź, kiedy będziesz sam. Wtedy będziemy mogli omówić... bardziej osobiste sprawy.";
							link.l1 = "Zawsze miło porozmawiać, ale muszę już iść. Być może jeszcze się zobaczymy.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... Już zaczynałam myśleć, że zapomniałeś drogę do naszej tawerny. Szkoda, że nie jesteś sam. Miałam nadzieję, że będziemy mogli porozmawiać na osobności.";
							link.l1 = "Myślę, że los wciąż da nam szansę na rozmowę na osobności.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Wiedziałam, że nie każesz mi zbyt długo tęsknić. Wiesz, nie chcę tracić ani minuty więcej. Pokój na górze jest wolny... tylko dla nas dwojga. Chyba nie zamierzasz mi odmówić?";
							link.l1 = "Wiesz, jak zwabić w swoje sieci... Cóż, nie mam powodu, by się opierać. Idziemy?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Obawiam się, że dziś naprawdę muszę zająć się czymś ważnym. Ale obiecuję, że następnym razem zrekompensuję swoją winę.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! Zaczynałam myśleć, że sprawia ci przyjemność zmuszanie mnie do nudzenia się. Chyba nie zamierzasz po prostu stać tu jak posąg, kiedy jest tak wiele przyjemniejszych sposobów na spędzenie tego czasu?";
							link.l1 = "Przeciwko twoim czarom nie można się oprzeć... Nie widzę sensu w traceniu ani sekundy – idę na górę w tej chwili.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Umiesz uwodzić, Betsy... Ale niestety, teraz muszę być gdzie indziej.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Chcę ci zadać kilka pytań.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Poprosiłam cię, żebyś poszedł na górę. Nie stój tutaj i nie zwracaj na siebie uwagi.";
					link.l1 = "Dobrze, idę, nie chcę cię wrobić...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Jestem tu nowa, więc proszę mnie nie rozpraszać. Nadal nie mogę się do tego przyzwyczaić...";
					link.l1 = "A gdzie jest kelnerka, która pracowała tu przed tobą?"+pchar.questTemp.different.FackWaitress.Name+", jak sobie przypominam...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Przyjdź jeszcze raz, kochanie. Możemy znów się zabawić. Gdybym miała więcej wolnego czasu...";
					link.l1 = "Pewnie, byłaś wspaniała!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "Nie znam cię, więc nie zawracaj mi głowy...";
					link.l1 = "Gdzie są moje pieniądze?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Przykro mi, "+GetSexPhrase("przystojniaku","skarbie")+", Jestem teraz zbyt zajęta. To dobry czas na karczmę, ale nie na rozmowy!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Proszę tutaj nie walczyć! Błagam... Ciężko się to miejsce sprząta.";
					link.l1 = ""+GetSexPhrase("Hm... Nawet nie zamierzałem.","Czy wyglądam na pijaczke szukającej bójki? Jestem tylko dziewczyną, taką samą jak ty, nie martw się więc.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("Oh, Kapitanie! Czy chciałbyś się dziś wygrzać ze mną w łóżku? Nie lubię się chwalić, ale...","Usiądź, Kapitanie. Zawsze jest przyjemnością spotkać prawdziwego wilka morskiego jak ty.")+"";
						link.l1 = "Wielka szkoda, bo akurat strasznie się spiesze. Może następnym razem!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "Z wielką przyjemnością, kochanie!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Usiądź, kapitanie. Spróbuj naszego rumu, zagraj w karty lub w kości. Czuj się jak u siebie w domu! Zawsze to przyjemność spotkać prawdziwego wilka morskiego jak ty.";
						link.l1 = "Dziękuję Ci, piękna.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Porozmawiaj z karczmarzem, jeśli chcesz coś zamówić. Jest za barem.";
					link.l1 = "Dzięki za radę.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Jeśli chcesz odpocząć i zadbać o swoje zdrowie - wynajmij sobie pokój. Spędzenie całej nocy w hałaśliwej sali niezbyt ci pomoże.";
					link.l1 = "Dziękuję.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Chcę ci zadać kilka pytań.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Słuchaj więc. Wynajmij pokój tutaj w karczmie. Idź tam i na mnie poczekaj. Przemkne się tam nieco później...";
			link.l1 = "Ha! Zrobię to, kochanie! Będę na ciebie czekać!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Ona już tu nie pracuje, zawineła się... Przykro mi, ale muszę wrócić do pracy.";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Słuchaj uważnie, pożądliwy idioto. Nie wiem, gdzie są twoje pieniądze! A jeśli będziesz na mnie naciskać, to zawołam strażników i znajdziesz się w więzieniu!";
			link.l1 = "Dobrze, nie potrzebujemy strażników... Jaki dureń ze mnie...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Dokładnie, taki głupiec. Następnym razem będziesz mądrzejszy i przyzwoitszy.";
			link.l1 = "Spróbuję... (szeptem) Jebana kurwa...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Słyszysz mnie?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Źle sie czujesz? Boli cię głowa?";
			link.l1 = "Cholera... gdzie ja jestem?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Nie pamiętasz? Zostałeś okradziony.";
			link.l1 = "Co? Oh... Moja głowa... Kto by się odważył?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Skąd mam wiedzieć? Wparowali, grozili śmiercią, sprawdzili twoje kieszenie i odeszli.";
			link.l2 = "Rozumiem... Cholera... Chciałbym trochę wody... Dziękuję.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "Nie, to nic takiego, Senor... dziękuję za twoją życzliwość, ale ja... (płacze)";
			link.l1 = "Ktoś cię obraził? Uspokój się, piękna, opowiedz mi wszystko.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Nie, nie, Senor to naprawde nic. Przepraszam za brak opanowania, tylko... Chodzi o mojego brata, mówią, że nie żyje, ale ja w to nie wierzę. Nie wiem, w co wierzyć, ale czuję własnym sercem, że jest w wielkich tarapatach. A poza Angelo, po śmierci naszych rodziców, nie mam nikogo... (płacze)";
			link.l1 = "Rozumiem, ale proszę cię, uspokój się. Co się stało z twoim bratem?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Senor... proszę mnie nie zrozumieć źle, ale dlaczego taki kapitan miałby się troszczyć o zwykłą i skromną dziewczynę z karczmy? Nawet nie mam nic, co mogłabym Ci obiecać za twoją pomoc...";
			link.l1 = "Właściwie, masz rację. Altruizm nie jest dla mnie, więc bądź silna, gdyż wszyscy tracimy naszych krewnych. C'est la vie jak mówimy we Francji...";
			link.l1.go = "exit";
			link.l2 = "Kobieta zawsze znajdzie sposób, aby podziękować mężczyźnie... Ha-ha. Teraz przestań już płakać i opowiedz mi o swoim problemie.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Młoda damo, czy nie wiesz, że nasz Kościół uczy nas pomagać sobie nawzajem? Spróbuję ci pomóc, jeśli będę w stanie, oczywiście.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "Czy to była 'sugestia'? Przepraszam, to był błąd rozmawiać z tobą! Do widzenia 'caballero'...";
				link.l1 = "Jak sobie życzysz, kochanie.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Cóż... Przynajmniej jesteś szczery w swoich pragnieniach. Obiecuję, że jeśli znajdziesz Angelo lub powiesz mi, co naprawdę się z nim stało, to dostaniesz to, o co prosiłeś...";
				link.l1 = "Droga senorito, to przyjemność robić z tobą interesy... Teraz przejdźmy od razu do rzeczy. Co się stało z twoim bratem?";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Żartujesz sobie, Senor? Naprawdę chcesz mi pomóc za darmo?";
			link.l1 = "Tylko okrutny człowiek nie pomógłby płaczącej dziewczynie. Nie martw się, naprawdę chcę ci pomóc. Co dokładnie stało się z Angelo?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Bardzo dobrze, Senor. Mój brat, on... och, nie jest mi łatwo powstrzymać łzy, jest mi tak przykro... Byliśmy naprawdę biedni z powodu mojej... skromności w pracy, być może... A Angelo zaczął pracować z lokalnymi przemytnikami. Myślał, że jego łódź rybacka przyniesie więcej pieniędzy, jeśli będzie coś przewozić, unikając przy tym cła.";
			link.l1 = "Aby to ująć prościej, twój brat stał się przestępcą, prawda?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Nie, Panie, nie rozumiesz... on nie jest taki! Zrobił to dla mnie! Aby uratować mnie przed zarabianiem dodatkowych pieniędzy w... wie Pan, co mam na myśli. Byliśmy zadłużeni i zrobił to dla mnie i mojej duszy. A potem... został złapany. To nie był duży problem, nawet pożyczałam więcej pieniędzy, aby zapłacić za jego uwolnienie... Lecz niedawno powiedzieli, że zginął.";
			link.l1 = "Powiedzieli? Kto powiedział? I dlaczego im nie wierzysz? Zmarł w więzieniu?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Tak. Kiedy przyniosłam pieniądze na jego zwolnienie, komendant powiedział mi, że Angelo umarł na gruźlice. Prosze pomyśleć! Dotarł tam w dobrym zdrowiu, a umarł dwa tygodnie później w tych komorach. Oni... oni nawet nie pozwolili mi zobaczyć ciała. Powiedzieli, że chowają więźniów w zatoce obok fortu, aby uniknąć epidemii.";
			link.l1 = "Epidemia? Brzmi bardzo prawdziwie. Czy ty po prostu nie chcesz w to uwierzyć, czy masz poważniejsze powody?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "Nie... Nie! (płacząc) Wiem, że to brzmi głupio, ale jestem pewna, że wiedziałabym, gdyby umarł. Wiesz, Angelo zawsze był silny - to prawdziwy żeglarz. Ale jest jeszcze jedna rzecz. Mój dziadek zmarł na gruźlicę, kiedy byłam dzieckiem, a on, stary człowiek, walczył z nią przez lata! Wiem, jak to działa, gruźlica nie zabija ludzi w ciągu kilku dni, uwierz mi!";
			link.l1 = "Hm... Również wzbudziłeś we mnie wątpliwości, coś tu jest bardzo nie tak. Nie mogę Ci niczego obiecać, ale postaram się dowiedzieć więcej.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Nawet prosta obietnica to o wiele więcej, niż liczyłam! Jesteś taki uprzejmy, Senor! Będę tu czekać!";
			link.l1 = "Och, młodość! Tak niekonsekwentna w uczuciach... czy mógłabyś mi uprzejmie oddać moją rękę, skarbie, nadal jej potrzebuję ha-ha... Dobrze więc, pójdę i poszukam dookoła.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "Nie, to nie żart! Na górze! Dwóch rzezimieszków mordują szlachcica! Pomóż mu, Kapitanie, jesteś tu jedynym uzbrojonym człowiekiem!";
			link.l1 = "Uciekaj więc na zewnątrz, i wołaj strażników! Idę na górę!";
			link.l1.go = "FMQP_1";
			link.l2 = "Moja droga, musiałaś pomylić mnie ze strażnikiem. Wezwij patrol w razie morderstwa.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "A-ah, straże! Pomóżcie mi!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
