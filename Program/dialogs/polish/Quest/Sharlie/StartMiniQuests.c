void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic w tej chwili.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "Czy potrzebujesz czegoś, monsieur?";
			link.l1 = "Jesteś Gralam Lavoie, prawda?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Kto pyta? Nie zawracaj mi głowy, gdy piję rum, panie. Nie mam ochoty na rozmowę.";
			link.l1 = "Nie zajmę Ci dużo czasu. Zostałem wysłany tutaj przez kupca z Saint-Pierre. Byłeś jego byłym pracownikiem. On Cię szuka i...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, szuka mnie!? To dopiero bogactwo tego pieprzonego skąpca! Naprawdę myślał, że spędzę całe życie pracując za takie marne pieniądze? Jest najchciwszym dusigroszem na Karaibach! Harowałem dla niego przez pięć lat i nigdy nie zapłacił mi ani grosza więcej, niż absolutnie musiał! Bah, nawet nie wystarczyło na drinka!\nTeraz niech sam liczy swoje towary, rzucam to. Nikt w Saint-Pierre nie będzie pracował dla tego sknerusa, to pewne. Ma tylko jedno na uwadze - zarobić więcej dla siebie i płacić swoim ludziom mniej.";
			link.l1 = "Zakładam, że nie zamierzasz znowu dla niego pracować?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "Nie, niech mnie Bóg zabije, jeśli to zrobiłem! Będę tu czekać w Le Francois, aż przybędzie jakiś statek, i zaciągnę się jako kwatermistrz, jeśli mnie wezmą. A jeśli to się nie uda, to będę żył jak zwykły marynarz. Nie mogę nawet znieść widoku tego skąpca. Jeśli mam być biedny, to wolę być wolnym człowiekiem...";
			link.l1 = "Rozumiem, to wszystko, co musiałem wiedzieć. Powodzenia, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Proszę pana, odsuń się. Stoisz mi na drodze!";
			link.l1 = "Jedno tylko pytanie, monsieur. Czy jesteś Gralam Lavoie?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha! Tak, to ja. Czego chcesz?";
			link.l1 = "Handlarz z St. Pierre cię szuka. Pracowałeś dla niego, prawda?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha! Co za żart! I czego potrzebuje ode mnie jego królewska mość? Czy postanowił wypłacić mi brakującą pensję za ostatnie dwa tygodnie pracy? A może ma kłopoty z liczeniem swoich beczek i jednoczesnym oszukiwaniem klientów, co? Ha-ha-ha!";
			link.l1 = "Poprosił mnie, bym cię poszukał i wyjaśnił, dlaczego nie przychodzisz już do jego sklepu do pracy.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = " Dlaczego? Bo to cholerny skąpiec i okropny pracodawca! Teraz należę do Bractwa Wybrzeża, jestem wolnym człowiekiem, a nie niewolnikiem! Rozejrzyj się, naprawdę się bawię! \nWkrótce wypłynę w morze i będę liczyć pesos i dublony zabrane Hiszpanom, zamiast skrzyń z bananami! A co do tego skąpca - wątpię, czy znajdzie kogoś na moje miejsce. Nikt w Saint-Pierre nie jest na tyle głupi, by dla niego pracować, roznieśliśmy wieści o jego reputacji do wszystkich uczniów na wyspie, ha-ha!";
			link.l1 = "Rozumiem. To wszystko, co musiałem wiedzieć. Powodzenia, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "Jak mogę ci pomóc?";
			link.l1 = "Dzień dobry. Gralam Lavoie, jak mniemam?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Tak. Czego chcesz, monsieur?";
			link.l1 = "Handlarz z Saint-Pierre cię szuka. Pracowałeś dla niego, prawda?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Cóż, niech dalej szuka. Nic mu nie jestem winien. On nadal mi zalega dwutygodniową pensję, ale nawet nie będę się trudził, żeby odzyskać swoje pieniądze. Mam nadzieję, że zadławi się własnymi miedziakami.";
			link.l1 = "Hm.  Więc opuściłeś go na dobre, jak sądzę?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "Masz absolutną rację, panie. Mój były pracodawca to rzadki okaz skąpca, naprawdę biblijnych rozmiarów. Teraz jestem Bratem Wybrzeża i moje talenty są wysoko cenione przez moich nowych kompanów. Zarabiam dwa razy więcej, plus premie\nWątpię, by nasz drogi przyjaciel znalazł kogoś na moje miejsce. Jego chciwość jest dobrze znana mieszkańcom Saint-Pierre, nikt tam nie jest na tyle głupi, by dla niego pracować.";
			link.l1 = "Zrozumiałem. To wszystko, co musiałem wiedzieć. Powodzenia, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Witaj, monsieur. Nie chcę być zbyt bezpośredni, ale sądzę, że moja kandydatura będzie doskonale pasować do oferowanej przez pana pozycji.";
			link.l1 = "Dzień dobry. A dlaczego tak myślisz?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Witaj, panie! Pozwól, że opowiem ci nieco o sobie.";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Zdrowie niech ci sprzyja, drogi panie. Czy oferujesz stanowisko kupca?";
			link.l1 = "Tak, to ja. Co możesz mi o sobie powiedzieć?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Służyłem jako kwatermistrz pod dowództwem samego kapitana Francisa Dubois. Był bardzo zadowolony z moich umiejętności, ale zostałem ranny w bitwie i musiałem wziąć urlop, by się leczyć. Teraz jestem w porządku, w pełni zdrowy, ale na myśl o falujących falach robi mi się niedobrze. Nie, moim jedynym pragnieniem teraz jest pozostać na stałym lądzie\n(szeptem) A jeśli mnie wybierzesz, zapłacę dodatkowo pięćset peso i dwadzieścia pięć złotych dublonów.";
			link.l1 = "Rozumiem. Zastanowię się nad tym.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "Kiedyś byłem domokrążcą, ale musiałem uciekać przed wierzycielami i zostałem intendentem na statku handlowym. Los przywiódł mnie do tej wioski. Tak czy inaczej, życie marynarza nie bardzo mi się podobało, i z chęcią przyjmę twoją ofertę\n(szeptem) A jeśli mnie wybierzesz, dam ci nie tylko pięćset pesos, ale także tę ciężką paczkę bursztynu.";
			link.l1 = "Rozumiem. Zastanowię się nad tym.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "Byłem urzędnikiem w jednym z magazynów portowych w Glasgow. Przybyłem na Karaiby w poszukiwaniu bogactwa i udało mi się zarobić dość pieniędzy, by przeżyć starość z godnością. Ale zmęczyły mnie morskie podróże i chciałbym prowadzić spokojne życie na brzegu\n(szeptem) A jeśli wybierzesz mnie, dam ci pięćset peso plus dodatkowe dwa tysiące pięćset peso jako bonus.";
			link.l1 = "Rozumiem. Zastanowię się nad tym.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, dokonaj właściwego wyboru. I nie zapomnij o dublonach...";
			link.l1 = "Zdecydowałem na twoją korzyść. Zbierz się do kupy. Jedziemy do Saint-Pierre.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Jeszcze się nie zdecydowałem...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "Mam nadzieję, że wybierzesz mnie, monsieur. A bursztyn to także całkiem cenne, przydatne coś...";
			link.l1 = "Zdecydowałem na twoją korzyść. Zbierz się w sobie. Jedziemy do Saint-Pierre.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Jeszcze nie zdecydowałem...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "Handlarz nie będzie rozczarowany moją pracą. I nie zapomnij o swojej premii.";
			link.l1 = "Zdecydowałem na twoją korzyść. Ogarnij się. Jedziemy do Saint-Pierre.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Jeszcze się nie zdecydowałem...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Pozwól mi tylko zebrać moje rzeczy! Będę czekał na ciebie przy wejściu do tawerny.";
			link.l1 = "... ";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "Zaraz tam będę, monsieur! Będę czekał na ciebie przy wejściu do tawerny.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Przyniosę swoją starą walizę i będę czekać na was przy wejściu do tawerny, panie!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			chrDisableReloadToLocation = true;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.quest.storehelper2.win_condition.l1 = "location";
			pchar.quest.storehelper2.win_condition.l1.location = "LeFransua_town";
			pchar.quest.storehelper2.function = "NewstorehelperAdd";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Cóż, rozumiem, że to tutaj teraz pracuję? Dziękuję, monsieur, za wybór mnie. Oto twoje pięćset pesos i obiecany bonus.";
			link.l1 = "Moja wdzięczność... Pozwól, że przedstawię cię twojemu pracodawcy.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Monsieur, muszę prosić pana o natychmiastowe opuszczenie mojego statku. Podnosimy kotwicę i odpływamy!";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Cóż? Kim jesteś, kumplu?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Napij się rumu, żeglarzu! Ha-ha! Witaj na pokładzie mojej łajby. Przyszedłeś po towar?";
			link.l1 = "Tak. Po cóż innego miałbym tu być?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Napij się rumu, żeglarzu! Ha-ha! Witaj na pokładzie mojego lugra. Przybyłeś po towar?";
				link.l1 = "Tak. Po cóż innego miałbym tu być?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Oho, oho, co za zielony sukinsyn! Chłopcy, ten wygląda jak świeży rekrut! Wrzucimy go za burtę!";
				link.l1 = "Hup!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Chłopcy! Załadujcie skrzynie na szalupę!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Wszystkie skrzynie rumu są na twojej szalupie. Port Le Francois znajduje się na południe stąd. Pośpiesz się, czas też, bym i ja podniósł kotwicę!";
			link.l1 = "Nie traćmy czasu, panowie! Powodzenia!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Nawzajem, kamracie...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "Czekaliśmy na ciebie, monsieur. Jak poszło? Masz skrzynie?";
			link.l1 = "Wszystko poszło spektakularnie. Skrzynie z rumem są na łodzi.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Świetnie. Od teraz my się tym zajmiemy. Ty udaj się do St. Pierre do tawerny po zapłatę. Bądź uważny i ostrożny w nocnych dżunglach.";
			link.l1 = "Wszystkiego najlepszego, panowie.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "Dzień dobry, monsieur! Powiadam, nie wyglądacie jak ci obdrapani łotrzy zazwyczaj kręcący się po naszej kolonii. Sądząc po waszym odzieniu, musieliście przebyć długą drogę... Przybyliście z Europy, czyż nie?";
			link.l1 = "Dokładnie, monsieur. "+GetFullName(pchar)+", do usług. Czego potrzebujesz?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Pozwól mi się przedstawić - "+GetFullName(npchar)+" . Przybyłem do tego strasznego miejsca z Francji kilka lat temu. Ale to ani tu, ani tam. Mam dla ciebie bardzo delikatną sprawę\nProszę zrozumieć, że gdybym nie był pewien, że jesteś dżentelmenem, nigdy nie prosiłbym cię o taką przysługę.";
			link.l1 = "Proszę, przedstaw swoją prośbę, monsieur. Jeśli to leży w moich możliwościach, to oczywiście postaram się pomóc.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "I am glad to hear that, monsieur de Maure. Now, how to put this delicately...There is a brothel in this town. A new girl appeared there recently; young, pale, blonde, stunningly beautiful! Now, I've been watching her for weeks and... got a very strong desire to spend some time with her in private\nBut my estate and status make it...inconvenient to visit such a place. Imagine the gossip!\nThat is why I am appealing to you. Plainly put, you are a newcomer to our island, people don't know you and they don't care about what you do... yet. You could do me a great favour, monsieur.";
			link.l1 = "Wydaje mi się, że rozumiem, do czego zmierzasz.";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "Doceniam pańską dyskrecję, monsieur. Nie mogę przyjść do dziewczyny, więc dziewczyna musi przyjść do mnie. Do mojego domu. Proszę, byś udał się do burdelu i umówił się z madame, aby pozwoliła ci zorganizować 'wizytę domową' blondynki na jedną noc.\nAurora nie odmówi, jest dobrze znana z tego, że świadczy takie usługi dostawcze, choć zawsze kosztuje to trochę więcej. Potem sprowadzisz dziewczynę do mojego domu. W ramach zapłaty dam ci sześć tysięcy pesos. Aurora zazwyczaj bierze trzy tysiące lub trzy i pięćset za jedną noc z dziewczyną w domu. Możesz zatrzymać resztę jako rekompensatę za swoje kłopoty.";
			link.l1 = "Nie brzmi to zbyt skomplikowanie. Mogę to zrobić.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, traktuję swoją reputację jako dżentelmen równie poważnie jak pan. Proszę o wybaczenie, lecz nie mogę spełnić pańskiej prośby. Muszę odmówić. Powinienem raczej udać się do tawerny i sprawdzić, czy karczmarz ma dla mnie jakieś zajęcie.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "I am damn glad to hear it. Now listen, the girl's name is Lucille. I ask you to deliver her to my place when it's dark, no earlier than eleven p.m., in order to avoid unwanted attention from any gawkers. Knock on the door, and I will open.\nMy house is located to the left of the governor's residence, facing away from it - a two-story mansion with a red roof. You can easily find it, and there's a shop nearby, too. Actually, I am heading to my house now; feel free to follow me to see what it looks like and where it is exactly, so you won't get lost at night.\n Regarding the matter at hand - here, take six thousand pesos. I expect you by the agreed-upon time!";
			link.l1 = "Mamy umowę. Twoja blondynka Lucille będzie u twoich drzwi tej nocy.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Dzień dobry, monsieur. Czyżby to pan mnie zatrudnił na dzisiejszy wieczór? Och, muszę przyznać, że jestem szczęściarą, trafiając na tak przystojnego i zadbanego dżentelmena, zupełnie innego niż te brutale, które schodzą z doków śmierdzące smołą i potem...";
				link.l1 = "Przepraszam, ale nie dzisiaj, Lucille. Jestem tutaj w imieniu mojego dobrego przyjaciela, który z wielu bardzo skomplikowanych powodów nie może opuścić swojego domu, więc zabiorę cię do niego. Nie martw się, jest to delikatny mężczyzna i bardzo cię lubi. Myślę, że na końcu będziesz zadowolona.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Uhm... Masz całkowitą rację, kochana. Czyż nie?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Panie, mam nadzieję, że rozumiesz, iż nie mogę po prostu spacerować z tobą nocą. Musisz mnie szybko zabrać do domu swojego przyjaciela, inaczej wrócę prosto do Madamy, a ty zmarnujesz swoje pieniądze.";
				link.l1 = "Dobrze, rozumiem. Chodź za mną!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "Szkoda... Polubiłam cię od razu, monsieur. Chciałabym spędzić z tobą noc... może następnym razem. Czy ruszamy?";
			link.l1 = "Tak. Chodź za mną!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Co za wspaniały dom. Czy to tutaj?";
			link.l1 = "Tak. Wejdź. Nie bój się, mój przyjaciel to dobry człowiek.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Nie doceniasz mnie, nie boję się, monsieur. Wiem, jak sobie poradzić. Może później możesz zapłacić Madame za noc ze mną? Obiecuję, że to będzie najlepsza noc w twoim życiu!";
			link.l1 = "Wszystko jest możliwe, Lucille. Może jeszcze się spotkamy. Żegnaj!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "Co to jest!? Kim jesteś? Czego tutaj chcesz? No dalej, wynoś się stąd do diabła!";
			link.l1 = "Nie jesteś zbyt uprzejmy, hultaju.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Słuchaj chłopcze, nie wychowano mnie, bym był uprzejmy, tak samo jak nie nauczyłem się czytać i pisać, ale rozłupanie twej czaszki szablą jest dla mnie tak samo łatwe, jak prostytutka padająca do tyłu. Przysięgam na moje oczy, że jeśli nie wyjdziesz stąd w tej chwili, wyniosą cię. Zrozumiano?";
			link.l1 = "Nie, to ty mnie posłuchaj, łotrze. Twój plan wyszedł na jaw. Potrzebuję tego człowieka żywego, więc rzuć broń i uciekaj. Za mną w dżungli jest oddział francuskich żołnierzy. Jeśli pobiegniesz wystarczająco szybko, może uda ci się uratować swoje żałosne życie.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "Dobrze, dobrze, uspokój się. Wychodzę.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Co-o? Blefujesz, kamracie! Do niego, chłopcy, do broni!";
			link.l1 = "Na własną odpowiedzialność, do broni!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Dzięki Bogu! Ah, jesteś Francuzem? Cholera, odpędziłeś tych rzezimieszków z klasą. Ale nie myśl, że się po prostu poddam, pokażę ci, jak walczy Hiszpan! Santiago!";
			link.l1 = "Nie, poczekaj, proszę!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "Wolę umrzeć, niż dać się schwytać Francuzom. Wziąłem szablę z jednego z martwych ciał, gdy walczyłeś... teraz sprawię, że zatańczysz do hiszpańskiej quadrilli!";
			link.l1 = "Wy Hiszpanie jesteście uparci jak muły!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Maldito... Wygrałeś. Poddaję się, przeklęty Francuzie. Jestem na twojej łasce.";
			link.l1 = "Schowaj swój miecz i pozwól mi mówić, uparty Kastylijczyku! Nie chcę, żebyś umarł, i nie zamierzam cię też do więzienia wysłać!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Więc co robisz? Dlaczego zabiłeś piratów? I gdzie są twoi żołnierze?";
			link.l1 = "Nie ma żołnierzy. Próbowałem przechytrzyć drani, ale jak widzisz wokół nas, nie zadziałało. Jestem tu sam, na prośbę twojego starego przyjaciela. Nazywa się "+pchar.questTemp.Sharlie.Captive.Name+", jest bankierem w St. Pierre.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? Nie znam nikogo o tym imieniu...";
			link.l1 = "Nie wiedziałem też nic o tobie ani o twoim uwięzieniu. Dowiedziałem się o twoim przeniesieniu na angielski statek od niego. Moim zadaniem jest dostarczyć cię do niego i przysiągłem, że to wypełnię! A teraz, chodź ze mną, jeśli chcesz żyć.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "Nie mam wyboru... Ten wasz bankier nie może być gorszy niż Anglicy i ich okropne gotowanie...";
			link.l1 = "Ostatecznie podejmujesz mądrą decyzję. Na razie dość gadania, płyniemy do St. Pierre. Trzymaj się blisko mnie i nie oddalaj się. Jeśli uciekniesz, złapię cię i znowu zleję na kwaśne jabłko.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "Czego potrzebujesz, monsieur? Nie mam czasu na rozmowy, więc bądź zwięzły.";
			link.l1 = "Jesteś Prosper Trubal, prawda?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Tak, to ja. Ale masz nade mną przewagę. Proszę, poinformuj mnie, kim jesteś i czego, do diabła, chcesz.";
			link.l1 = "Nazywam się "+GetFullName(pchar)+" . Zostałem przysłany do ciebie przez "+GetFullName(characterFromId("Fortfrance_portman"))+",   mistrz portu. Powiedział, że potrzebujesz pilnej pomocy...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Na Boga, tak! Ten łajdak komendant nawet nie wysłuchał mojej skargi! Albo jest zbyt leniwy, albo tchórzliwy, by pomóc. Czy naprawdę przyszedłeś mi pomóc? Jeśli tak, nie zostawię cię bez nagrody!";
			link.l1 = "Tak Prosper. Powiedz mi, co się stało i co muszę zrobić, aby pomóc. Słyszałem, że twoja córka zniknęła...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Tak, moja droga córka Celene zaginęła na dwa dni. Poszła na spacer do fortu niedaleko stąd. Ale nie wróciła, więc sam poszedłem do fortu, a żołnierze powiedzieli mi, że nigdy tam nie była!\nAle potem, gdy wracałem, zostałem zaatakowany przez dwóch dzikich Indian! Rzucili się na mnie z pałkami i próbowali mnie pobić.\nAle nie jestem żadnym kotkiem, więc walnąłem jednego w twarz, co dało mi wystarczająco czasu, by wyciągnąć pistolet i strzelić. Chybiłem, ale ich przestraszyłem. Udało mi się dotrzeć do bram miasta i powiedziałem strażnikom o ataku. Pobiegli do dżungli, ale dzikusy już dawno zniknęły.\nJestem pewny, że to oni są odpowiedzialni za zniknięcie Celene. Poza tym, jeszcze dwie osoby zaginęły w zeszłym tygodniu - Cesar Blanchet i Gilbert Courcy! Jeden szedł do zatoki, a drugi do Le Francois. Nigdy nie wrócili.";
			link.l1 = "Więc Indianie atakują mieszczan tuż przy bramach miasta? To niewiarygodnie zuchwałe...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "W międzyczasie sam wyruszyłem do dżungli, by jej szukać i znalazłem jaskinię na północ od miasta. Znalazłem tam drani, którzy się tam zagnieździli. Widziałem kilku Indian przy wejściu, ale niektórzy muszą być też wewnątrz\nUsłyszałem krzyk dziewczyny... To była moja Celene, jestem tego pewien, to był jej głos! Wymagało to ode mnie ogromnej powściągliwości, by nie wbiec tam od razu - szanse nie były po mojej stronie i zmasakrowaliby mnie. Nie jestem jej przydatny martwy.";
			link.l1 = "Ale dlaczego, na Boga, oni atakują i biorą mieszkańców jako więźniów?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Nie wiem... Może żeby sprzedać je piratom lub handlarzom niewolników? Może po prostu je zjedzą żywcem, w końcu to dzikusy.";
			link.l1 = "Na Boga w Niebie, czyżby to byli kanibale? Myślałem, że to tylko historie, by straszyć dzieci w Europie...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Historie? Cóż, kilku ludzi takich jak ty myślało to samo, dopóki Karibowie nie ugotowali ich na ogniu i nie zjedli... Więc natychmiast zwróciłem się do komendanta i poprosiłem o wyprawę karną, by ocalić moją Celene. Odmówił! Powiedział, że gdy znikają dziewczęta, prawdopodobnie uciekły z jakimś chłopcem, a nie Indianami. Zasugerował, bym szukał jej w lokalnych stodołach\nA jeśli chodzi o pozostałych dwóch zaginionych... powiedział, że jeden z nich był podejrzewany o przemyt, a drugi prawdopodobnie upija się na śmierć w tawernie Le Francois. Podsumowując, niczego nie osiągnąłem i postanowiłem działać na własną rękę.";
			link.l1 = "Co zamierzasz zrobić?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Pójdę tam i zabiję każdego z tych czerwonych drani. Mam tylko nadzieję, że Celene wciąż żyje. Jak widzisz, kupiłem muszkiet - i umiem z niego strzelać. Zapłaciłem za niego dużo monet, ale nie obchodzi mnie to\nMoja misja będzie znacznie łatwiejsza, jeśli mi towarzyszysz. Razem możemy wykończyć dzikusów bez większych problemów, jeśli będziesz pilnować mi pleców, gdy będę przeładowywał. Czy pójdziesz ze mną, aby uratować moją córkę?";
			link.l1 = "Oczywiście! To kwestia honoru! Nie mogę po prostu pozwolić, by dziewczyna zginęła od noża jakiegoś dzikusa.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hm. Wiesz, myślę, że słowa komendanta mają sens. Może powinniśmy jednak najpierw posłuchać jego rady?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Monsieur, gdzie jest twój ostrze?";
			link.l1 = "Zdaje się, że gdzieś to zgubiłem.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "To po prostu nie wystarczy. Będę czekać na ciebie do wieczora, radzę ci paść do stóp naszego gubernatora i błagać o jego pomoc.";
			link.l1 = "Płaszczyć się u jego stóp, co? Cóż, jak sobie życzysz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "Cóż, monsieur? Zdobyłeś sobie broń?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Jeszcze nie, proszę poczekać trochę dłużej...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Zrozumiałem. Jestem gotów ci pomóc!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "Mój Boże, uciekasz? Nie! Wynoś się stąd! Tchórz!";
			link.l1 = "Hej-hej, spokojnie, ty prostaku! Lepiej pójdę na zewnątrz i zobaczę, czy jakiś szlachcic na ulicach Saint-Pierre potrzebuje pomocy.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "Cieszę się, że w tym mieście jest przynajmniej jeden odważny człowiek. Proszę, weź te trzy fiolki. To są zioła lecznicze, kupiłem je od naszego zielarza. Mogą być znaczną pomocą w bitwie.";
			link.l1 = "A co z tobą?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie martw się, mam więcej. Jesteś gotowy?";
			link.l1 = "Tak, nie traćmy czasu. Naprzód!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "Jesteśmy prawie na miejscu, "+pchar.name+"Za tym zakrętem znajduje się wejście do jaskini. Podejdź bliżej, a opowiem ci o naszym planie.";
			link.l1 = "Zamieniam się w słuch, Prosperze.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Muszę ustabilizować cel z tym ciężkim muszkietem, ale jeśli dasz mi trochę czasu, nie chybię. Jeśli będę musiał walczyć wręcz, zapomnij o wsparciu ogniowym, będę mógł tylko odpierać ludzi beczką jak maczugą. Ta walka będzie zależała od twojej umiejętności szermierki.";
			link.l1 = "Co próbujesz powiedzieć?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Wszystko, czego potrzebujesz, to odwrócić ich uwagę, aby pozwolić mi ich wszystkich zastrzelić. Nie mogę się poruszać i strzelać, więc zostanę w jednym miejscu. Trzech drani jest blisko wejścia do jaskini. Powinieneś ich zaatakować jak najszybciej z ostrzem w ręku\nUderz jednego z nich i spraw, by cię ścigali. Zwróć ich uwagę ode mnie. Jeśli wszyscy trzej skoncentrują się na tobie, mogę ich zestrzelić jak ptaki, gdy będziesz parował i unikał. Ale jeśli ci dzikusi rzucą się na mnie, jesteśmy zgubieni. Jesteś gotowy?";
			link.l1 = "To nie pierwszy raz, gdy trzymam miecz, te dzikusy nie stanowią zagrożenia.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "Ha! Nie martw się o mnie. To jak polowanie w Le Mans! Tylko nie strzelaj mi przez pomyłkę w plecy!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Idź pierwszy, jestem za tobą. Pamiętaj: nie możesz pozwolić im się do mnie zbliżyć!";
			link.l1 = "Pamiętam, ruszajmy. Naprzód!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "Zatem przygotuj się do akcji. Idź pierwszy, będę za tobą. Pamiętaj: nie możesz pozwolić im zbliżyć się do mnie!";
			link.l1 = "Pamiętam. Zrobię wszystko, co w mojej mocy. Naprzód!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "Dobra robota, "+pchar.name+"! Te pogańskie dzikusy nie będą już więcej mordować. Teraz czas na główną atrakcję - jaskinię. Wierzę, że w środku jest trzech lub czterech z nich, ale nie mogę być pewien. Teraz słuchaj\nByłem tam dziesięć lat temu. W jaskini jest wąski tunel. Prowadzi do małej groty, podzielonej ścianą z dziurą pośrodku. Powtórzmy nasz plan z wcześniejszego razu. Ja stoję nieruchomo blisko wejścia, a ty wpadasz do środka\nProwokuj ich, nie próbuj walczyć ze wszystkimi naraz, po prostu uniemożliw im atak na mnie. Zajmij pozycję przy tunelu, o którym wspomniałem, jest wąski, więc tylko jeden lub dwóch z nich będzie mogło walczyć z tobą naraz\nBędę strzelał nad twoim ramieniem. Gotowy?";
			link.l1 = "Naprzód! Zakończmy z tym gniazdem dzikusów!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "Moja córka żyje! Dzięki Bogu! Dotarliśmy tu na czas, "+pchar.name+"Jestem ci dłużny, sir. Jesteś odważnym człowiekiem i dobrym wojownikiem!";
			link.l1 = "Cieszę się, że to szczęśliwe zakończenie, Prosper. To była naprawdę krwawa robota, wyeliminować wszystkich tych Indian.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Raz jeszcze najgłębsze podziękowania, "+pchar.name+"! Teraz wracajmy do miasta. Życie mojej córki jest bezcenne, nie da się go wycenić żadną sumą pieniędzy, ale chcę ci podziękować, dając ci to, co zostało z moich oszczędności. Gdy tylko dotrzemy do Saint-Pierre, z radością ci je wręczę. I nawet nie myśl o odmowie!";
			link.l1 = "Nie odmówię, Prosperze. Choć pieniądze nie były moim celem, pomagając ci.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Jesteś prawdziwym chrześcijańskim rycerzem, "+pchar.name+"Nie ma co tu się kręcić. Wróćmy szybko do domu!";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Oto jesteśmy, Charles. Jeszcze raz dziękuję ci za pomoc i dołączam do tych słów tę skromną sumę peso i złotych dublonów. Proponuję nie tracić dublonów i trzymać je na specjalne okazje. Wiem, że to nie dużo pieniędzy za taką usługę, jaką mi oddałeś, ale jest to od serca. Weź również ten amulet, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Dziękuję! Żegnaj Prosperze, życzę szczęścia tobie i twojej drogiej córce!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ach, mąż taki jak ty dobrze by jej zrobił. Cały czas gonią ją po mieście banda chudonogich, bezbrodych fircyków. Szkoda tylko, że wszyscy po kolei znikają gdzieś... i dobrze im tak. Powodzenia, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Ach! Boże, ratuj mnie! (płacząc) Ty... ty nawet nie możesz sobie wyobrazić, jaki horror tu się dzieje! Ci... ci Indianie zaciągnęli nas tu, żeby nas zabić i zjeść! Cesar Blanchet był tutaj... Dzicy zabrali go... Przeprowadzili jakiś okropny diabelski rytuał, a potem... Panie, nawet nie mogę o tym mówić! Miałem być następny! Zamierzali mnie zarżnąć... jutro!";
			link.l1 = "Spokojnie, Celine. To już koniec. Te dranie dostali to, na co zasłużyli i już nikomu nie zrobią krzywdy.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie jest tu również. Tam... on, uh... on wciąż się jeszcze nie odzyskał. Porozmawiaj z nim... Potem pośpieszmy się i wyjdźmy stąd!";
			link.l1 = "Już dobrze, już dobrze. Wszystko w porządku, dziewczyno. Wystarczy płaczu. Wszystko jest dobrze. Masz wspaniałego ojca. Nie pozwoli nikomu cię skrzywdzić... Wyjdź na zewnątrz, pomogę...uh... Gilbertowi się stąd wydostać, a później cię dogonię.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "„Bóg i Najświętsza Matka wysłuchali moich modlitw! Czy przyszedłeś nas ocalić?”";
			link.l1 = "Ty... Twoje imię to Celine, prawda?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Tak... (płacze) Ty... ty nawet nie możesz sobie wyobrazić, jaki koszmar tu się dzieje! Ci... ci Indianie przywlekli nas tutaj, żeby nas zabić i zjeść! Cesar Blanchet był tutaj... Zabrali go... Odprawili jakiś diabelski rytuał, a potem... Panie, nawet nie mogę o tym mówić! Mam być następny! Mieli mnie zarżnąć... jutro!";
			link.l1 = "Spokojnie, dziewczynko... Przykro mi, ale przynoszę złe wieści. Przybyłem tu z twoim ojcem. Został zabity tuż za drzwiami przez tych czerwonoskórych dzikusów, gdy walczyliśmy, by się do ciebie dostać. Oddał życie, aby cię ocalić.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "Co?! Mój ojciec... O Boże! Ja... Ja... (szloch)";
			link.l1 = "Moje kondolencje, Celine. Jest z tobą ktoś jeszcze, mam rację?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(przez łzy) Tak... Gilbert Coursie. On tam jest... Jeszcze się nie pozbierał. Porozmawiaj z nim... A potem uciekajmy stąd!";
			link.l1 = "Tak, oczywiście. Nie możemy tracić ani minuty stojąc tutaj bezczynnie.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Mój ojciec... Mój biedny, drogi ojciec! Ach, monsieur, nawet ci nie podziękowałem za to, że mnie uratowałeś...";
			link.l1 = "Selina, cieszę się, że ty i Gilbert wyszliście z tej jaskini żywi. Bohaterska śmierć twojego ojca nie poszła na marne.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(płacząc) Proszę, monsieur, zabierzcie nas ze sobą do miasta. Musimy wysłać po żołnierzy, by przybyli po ciało mojego ojca, aby mógł mieć godny chrześcijański pochówek...";
			link.l1 = "Oczywiście, Celine. Chodź za mną!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Dziękuję, monsieur, za towarzyszenie memu biednemu ojcu... Dziękuję za uratowanie mnie od pewnej śmierci. Ja... Ja... Oto, weź tę torbę z dublonami. Znalazłam ją w domu w skrzyni ojca. Proszę, nawet nie waż się myśleć o odmowie!";
			link.l1 = "Dziękuję, Celine. Cieszę się, że udało nam się cię ocalić. I moje szczere kondolencje z powodu straty twojego ojca.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Jesteś szlachetnym człowiekiem, monsieur. Nigdy cię nie zapomnę. Żegnaj!";
			link.l1 = "Żegnaj, Celine.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "O Panie, czy to naprawdę już za nami? Nie mogę w to uwierzyć... Uratowałeś zarówno mnie, jak i Celine. Gdyby nie ty, ten sam los, który spotkał nieszczęsnego Cesara, czekałby na nią jutro, a mnie za kilka dni.";
			link.l1 = "Ci Indianie, czy oni naprawdę są kanibalami?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Wątpisz w to? Jeśli masz mocny żołądek, zajrzyj w popiół ich ogniska. Znajdziesz tam biednego starego Cesara. Teraz to tylko jakieś obgryzione kości...";
			link.l1 = "Przenajświętszy Sakrament... Nie, podziękuję. Dopiero co przybyłem tutaj z Europy i nie mogłem nawet sobie wyobrazić, że takie podłe, diabelskie rzeczy wciąż mają miejsce na Ziemi.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "W Karaibach dzieją się dziwne rzeczy, o których tylko szeptano w Starym Świecie... Indianie, szamani, magia, tajne rytuały. Zostań tu dłużej, a zobaczysz wszelkiego rodzaju diabelstwa. Ale wybacz mi, jeszcze ci nie podziękowałem za ocalenie mnie - wciąż jestem w szoku\nOcaliłeś moje życie i zamierzam wyrazić moją wdzięczność nie tylko słowami, ale także złotem. Eskortuj Celine i mnie do miasta. Tam będę mógł podziękować ci tak, jak na to zasługujesz, monsieur.";
			link.l1 = "Dobrze. Wyjdź na zewnątrz. Najpierw rozejrzę się tutaj.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Pozwól, że raz jeszcze wyrażę moją głęboką wdzięczność za ocalenie mnie, monsieur! Jak obiecałem, dołączam do mojej werbalnej wdzięczności materialną wdzięczność w postaci srebrnych pesos i złotych doublonów.";
			link.l1 = "Cieszę się, że wszystko skończyło się szczęśliwie, Gilbercie.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie możesz sobie nawet wyobrazić, jak bardzo się z tego cieszę! Dziękuję raz jeszcze i pozwól mi odejść, monsieur.";
			link.l1 = "Powodzenia, Gilbert! Przy okazji, czy wiesz może, czy ktoś jeszcze w Saint-Pierre potrzebuje pomocy?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "Nie wiem, ale... Możesz zapytać mieszkańców na ulicach, Monsieur. Zwykli mieszczanie, a nawet zamożni, raczej nie zaoferują nic wartego uwagi, ale bogaci szlachcice... mogą mieć dla ciebie jakieś zajęcie.";
			link.l1 = "Zrozumiałem, Gilbert, dzięki. Do zobaczenia!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj no, jestem praworządnym obywatelem tego miasta. Muszę cię prosić, byś nie chodził z odsłoniętym ostrzem jak rabuś.","Proszę, panie, prawo jest jasne, że mężczyźni nie mogą chodzić z wyciągniętą bronią w murach miasta.");
			link.l1 = LinkRandPhrase("Dobrze.","Bardzo dobrze.","Jak sobie życzysz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
