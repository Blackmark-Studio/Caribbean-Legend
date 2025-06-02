void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Niczego.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Łajdak! Wielka niespodzianka dla ciebie!";
    		link.l1 = "Co?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ha-ha! Nie ma tu niewolników! Przyszedłeś po nich, prawda?";
			link.l1 = "Cholera. A ja się zastanawiałem, dlaczego do diabła było tylu żołnierzy na handlowej pinasie... Pułapka!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Tak, draniu, to pułapka. Nie jestem kupcem, jestem oficerem wojskowym! Chociaż wygrałeś walkę, nie umkniesz przed sprawiedliwością!";
			link.l1 = "A dlaczego? Skończę z tobą teraz, zatopię twój statek i nikt się o tym nie dowie.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "Jesteś w błędzie. Twój interes z tamtym bankierem został ujawniony. Wkrótce, gubernator-generalny dowie się o twoim małym interesie i nie uciekniesz od szubienicy. Ale zrobię ci przysługę, zabijając cię tutaj i teraz!";
			link.l1 = "Spróbuj tylko, psie gubernatora!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+", w imię prawa, jesteś aresztowany! Oddaj broń i chodź z nami!";
			link.l1 = "Co się dzieje, oficerze? Na jakiej podstawie mamy się poddać?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Nie udawaj głupiego, kapitanie! Twój brudny biznes został ujawniony. A za rzeź, którą popełniłeś, i za statek "+NationNameGenitive(sti(npchar.nation))+" które zatopiłeś, zobaczymy cię wiszącego!";
			link.l1 = "Dobrze, skoro tak to ujmujesz... Pierdol się!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "Hej, co ty tu robisz?!";
    		link.l1 = "Dlaczego jesteś taki nieuprzejmy, dobry panie? Czy ten szczur Gontier ukrywa się gdzieś tutaj, co?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "Nie, nie ma go tu! Wynoś się!";
			link.l1 = "Wygląda na to, że kłamiesz. Przeszukam dom i sam zobaczę...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Pierdol się! Francois! Biegnij! Chłopaki, pomóżcie mi!";
			link.l1 = "Cholera!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "O! Nie gwałć mnie!";
    		link.l1 = "Co do...? Gdzie jest Francois Gontier? Odpowiadaj, ty plugawa ladacznico, albo skończysz jak twoi kumple!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "Nie, nie, powiem ci wszystko! Wyskoczył przez okno i uciekł na swój statek.";
    		link.l1 = "Jaki statek? Wiem, że jego statku nie ma w porcie. Nie okłamuj mnie, dziewczyno, bo będzie gorzej...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "Nie kłamię, przysięgam! Powiedział, że wylądował na małej wyspie i dotarł tutaj na łodzi... Musi tam być! Nie krzywdź mnie!";
    		link.l1 = "Dobrze, wygląda na to, że mówisz prawdę. Zostań tutaj i bądź cicho. I spróbuj w przyszłości nawiązywać przyjaźnie w bardziej sprytny sposób. Ale, wiesz, widzę to w twoich oczach i one mówią mi, że nie masz rozumu.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Daruj nam! Litości! Poddajemy się!";
    		link.l1 = "Oh, naprawdę? Prędko do ładowni! Zastrzelę każdego, kto spróbuje się wygłupiać!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Ho, ho... Co my tu mamy? Nie wiesz, że handel towarami z nieautoryzowanymi osobami i między nimi jest zabroniony w naszej kolonii?";
			link.l1 = "Czyżby, oficerze? Szczerze mówiąc, pierwszy raz o tym słyszę. Ten dekret został wydany niedawno, prawda?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "Cóż, handel "+GetGoodsNameAlt(iCGood)+"? Nie widzę żadnych "+GetGoodsNameAlt(iCGood)+" wokół, oficerze. Widzę tylko te błyszczące monety... I on widzi to samo. Dlaczego ty i twoi żołnierze nie przyjrzycie się również naszym monetom?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "Nie wiedziałeś, co? Hmm... wygląda na to, że nie kłamiesz. Ale mimo to naruszyłeś prawo. Nie aresztuję cię, ale muszę nałożyć na ciebie grzywnę. A jeśli chodzi o ładunek... porozmawiamy o nim z drugim uczestnikiem umowy.";
				link.l1 = "Ile wynosi ta kara?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Nie udawaj głupiego, kapitanie! Wszyscy już o tym wiedzą, i to od dawna, dodam. Aresztuję was obu za przemyt, a wasz ładunek zostanie skonfiskowany.";
				link.l1 = "Nie lubię kazamatów, oficerze. Lubię otwarte morze... i zamierzam tam teraz popłynąć. Ale wygląda na to, że będę musiał to zrobić tylko po twoim trupie.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Nie mam wyboru, muszę się poddać. Ale naprawdę nie miałem pojęcia!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "Teraz mówisz do rzeczy... Zobaczmy twoje monety... Wierzę, że usłyszałem dość konkretną liczbę - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Ponieważ mamy teraz trzech uczestników, chciałbym dostać "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". To od ciebie i to samo od twojego przyjaciela.";
				link.l1 = "Oczywiście, oficerze. Oto moje błyszczące monety, czy raczej, przepraszam, wasze błyszczące monety - właśnie przez przypadek upuściliście je na plaży... I nie ma żadnego "+GetGoodsNameAlt(iCGood)+" tutaj, ha-ha, jak ci mówiłem.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Oho! Jesteś zbyt chciwy, oficerze. Czy matka nie nauczyła cię, że chciwość to zła rzecz? Sądzę, że taniej będzie mi rozprawić się z tobą moim ostrzem.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Żartujesz, kapitanie? Chcesz mi zaproponować łapówkę? Jesteś aresztowany! Zatrzymać go!";
				link.l1 = "Cóż, jeśli nie chcesz spojrzeć na moje pieniądze, to spójrz na mój miecz!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Nie mam wyboru, muszę się poddać. Ale naprawdę nie miałem pojęcia!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Tak, wygląda na to, że masz rację... Nic interesującego tutaj oprócz kilku dżentelmenów i moich błyszczących monet. Możesz iść, kapitanie, a my porozmawiamy z twoim wspólnikiem.";
			link.l1 = "Do widzenia, oficerze. Nie krzywdź go.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+"Podziękuj mojemu dobremu humorowi.";
			link.l1 = "Dziękuję, oficerze. Naprawdę nie miałem pojęcia... Proszę, jestem gotów zapłacić swoją grzywnę.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "Zakładam, że ty też nie jesteś zbyt uczciwy, oficerze. Twoja grzywna jest zbyt wysoka. Sądzę, że pomogę tej kolonii, ratując ją od twojego istnienia.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Dobrze. Możesz teraz odejść. I radzę ci zapoznać się z lokalnymi prawami, aby w przyszłości unikać takich sytuacji. Idź już, musimy zająć się drugim uczestnikiem tego handlu, on wiedział o wszystkim, to pewne.";
			link.l1 = "Cóż, w takim razie, dobrego dnia, oficerze.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "Komendant się z tobą rozprawi. Chodź za mną!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Dobry dzień. Czy chcesz czegoś?";
			link.l1 = "Ja też, kumplu. Zakładam, że to ty jesteś moim człowiekiem. To ty ukradłeś "+pchar.GenQuest.Device.Shipyarder.Type+"  z lokalnej stoczni? Wszystko prowadzi do ciebie, więc bez dyskusji.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "Błagam cię, panie! Tak, ukradłem tę dziwną rzecz ze stoczni. Ale nie udało mi się jej sprzedać, nikt nie potrzebuje takiego przedmiotu. Więc się go pozbyłem. Oszczędź mnie, dobry panie, obwiniaj mój głód, nie mnie... Nigdy nie odważyłbym się niczego ukraść, gdyby nie to!";
					link.l1 = "To jest problem... A ciebie też nie potrzebuję. Muszę znaleźć tę "+pchar.GenQuest.Device.Shipyarder.Type+". Powiedz mi, gdzie to wyrzuciłeś?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "Błagam cię, mój panie! Tak, ukradłem tę dziwną rzecz ze stoczni. Ale nie udało mi się jej sprzedać, nikt nie potrzebuje takiego przedmiotu. Oddam ci to. Weź to, tylko nie krzywdź mnie i nie wołaj żołnierzy!";
					link.l1 = "Dobrze, możesz żyć, łotrze. Nie potrzebuję twojej skóry, potrzebuję tego instrumentu. Oddaj mi go natychmiast i znikaj!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "Co masz na myśli? Co to jest "+pchar.GenQuest.Device.Shipyarder.Type+" ? Nie rozumiem tego!";
					link.l1 = "Dostaniesz to, gdy przeszukam ciebie lub twoje zwłoki! Oddaj mi to teraz!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Oh... Co to jest "+pchar.GenQuest.Device.Shipyarder.Type+"? Ja... a co to jest?";
					link.l1 = "Nie próbuj udawać głupiego ani uciekać, i tak cię złapię. Po prostu pozwól mi sprawdzić twoje kieszenie...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "Zaraz za bramami miasta, niedaleko od dżungli. Błagam cię, dobry panie! Jeśli naprawdę potrzebujesz tej rzeczy, możesz ją odebrać sam. Na pewno wciąż tam jest, jestem pewien.";
			link.l1 = "Powinienem zmusić cię, byś to znalazł i przyniósł mi, ale obawiam się, że spędziłbym więcej czasu na szukaniu ciebie niż "+pchar.GenQuest.Device.Shipyarder.Type+"Zrobię to sam. Ale znajdę cię, jeśli mnie okłamałeś!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Proszę, weź to. Dziękuję, dobry panie!";
			link.l1 = "Cóż, to musi być to, czego szukałem... ha! Teraz jesteś wolny. Ruszaj się. I następnym razem bądź ostrożny.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "Słuchaj, czy mówisz o tym instrumencie? Należy do mnie i nie ukradłem go! I nie zamierzam oddawać go za darmo. Jeśli chcesz go zdobyć, zapłać mi "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "Hm... Dobrze. Zapłacę ci. Oto twoje monety, a teraz daj mi instrument!";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "Oh, doprawdy? Czy naprawdę myślałeś, że ci zaufam, nędzny złodzieju? Oddaj "+pchar.GenQuest.Device.Shipyarder.Type+" do mnie teraz, albo zawołam strażników, abyśmy mogli razem udać się do stoczni i zdecydować, czyje to narzędzie naprawdę jest.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Jesteś głupi, czy co? Słuchaj, draniu, masz dwie opcje: albo dasz mi "+pchar.GenQuest.Device.Shipyarder.Type+"albo cię zadźgam i wezmę narzędzie z twojego martwego ciała!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Udana transakcja, kapitanie! Przypuszczam, że wszyscy dostaniemy nasze zyski, he-he... bierz to.";
			link.l1 = "Mniej gadania, złodzieju! Nie myśl, że mnie oszukałeś, po prostu chcę to załatwić spokojnie i z mniejszą ilością problemów. Te monety i tak nie przyniosą ci nic dobrego. Zjeżdżaj!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Nie! Nie wołaj straży! Ja...ja dam ci ten przeklęty instrument. Proszę, weź to!";
				link.l1 = "To teraz o wiele lepiej! Zmykaj stąd! Albo skończysz wisząc na szubienicy, to tylko kwestia czasu.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "Jakie straże, kapitanie? Jesteśmy tu tylko ty i ja. Za dużo się kłócisz, więc będę musiał cię uspokoić... moim ostrzem.";
				link.l1 = "Śmiesz mi grozić, łajdaku?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ach! Pomocy! Morderca!";
				link.l1 = "Stój tam, psie!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Cóż, zobaczymy, kto kogo dźgnie, kapitanie!";
				link.l1 = "Śmiesz mi grozić, łotrze?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Szukać? Proszę, dobry panie!";
			link.l1 = "Teraz słuchaj, albo spokojnie oddasz mi rzecz, którą właśnie ukradłeś z stoczni, albo zaprowadzę cię do biura komendanta. Tak czy inaczej oddasz mi tę rzecz, ale najpierw twoje pięty zostaną przypalone rozżarzonym żelazem. Może nawet cię potem powieszą. Wybór należy do ciebie.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Oddawaj natychmiast to, co ukradłeś, draniu, albo zakończę cię tam, gdzie stoisz!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "Cóż, najpierw musisz mnie złapać, jeśli chcesz zaprowadzić mnie do biura komendanta ...";
				link.l1 = "Stój tam, psie!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "Nie, nie zabieraj mnie do gabinetu komendanta! Sam to oddam! Proszę, weź to, pewnie tego szukasz. I tak nikt by tego nie kupił...";
				link.l1 = "Eh, przypuszczam, że mogę cię zabrać do fortu mimo wszystko... Dobrze, daj mi narzędzie i znikaj!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Ała! Nie krzywdź mnie, oddam ci wszystko, co mam! Proszę, weź to!";
			link.l1 = "Teraz gadasz! Zjeżdżaj, dostarczę cię do komendanta, jeśli jeszcze raz cię zobaczę w tym mieście. Żegnaj!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Stój, przyjacielu! Potrzebujemy rzeczy, którą niesiesz. Oddaj ją nam, a potem idź swoją drogą.";
			link.l1 = "O czym ty mówisz?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "Ci ulicznicy są zbyt zuchwali w dzisiejszych czasach... Przygotujcie się, łajdaki!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Nie udawaj głupca! Oddaj nam paczkę, a przeżyjesz. W przeciwnym razie... zabierzemy ją z twojego trupa!";
			link.l1 = "Los jest po twojej stronie... bierzcie to, dranie, nie mam wyboru.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Możesz spróbować, jak chcesz!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Pilnuj języka, kumplu... Dobrze, że nie próbowałeś szczęścia. Koniec byłby taki sam, ha-ha! Pożyjesz jeszcze trochę... Do zobaczenia.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Czekaj, "+GetAddress_Form(NPChar)+", nie spiesz się tak. Mam dla ciebie interes.";
			link.l1 = "Jaki interes? Nie znam cię.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "Znam cię, kapitanie. Teraz prosto do interesów. Właśnie otrzymałeś "+pchar.questTemp.WPU.Current.Add+" w "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+"Nie próbuj tego zaprzeczać, wiemy to na pewno - w końcu szukaliśmy tego dokumentu od kilku dni.";
			link.l1 = "Teraz widzę. I co z tego?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Daj mi paczkę, a nasze krótkie spotkanie się zakończy. Nie próbuj bawić się w bohatera, kapitanie, zamierzamy zdobyć te dokumenty i jesteśmy gotowi walczyć z garnizonem miasta, jeśli zajdzie taka potrzeba\nJak możesz zrozumieć, zginiesz pierwszy, jeśli wybuchnie potyczka. Więc oddaj nam dokumenty i rozstaniemy się jak przyjaciele.";
			link.l1 = "Szanse są po waszej stronie... bierzcie to, dranie, nie mam innego wyboru.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "Próbujesz mnie przestraszyć, widziałem małe ryby, które stawiały większy opór niż ty kiedykolwiek mógłbyś! Spadaj.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "Cieszę się, że byłeś rozsądny, kapitanie. Postawiłeś się w wielkim niebezpieczeństwie, podejmując się tego zadania. Teraz zamierzam się oddalić, jeśli nie masz nic przeciwko.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "To była twoja decyzja...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap();//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Czekaj, "+GetAddress_Form(NPChar)+", nie spiesz się tak. Mam dla ciebie interes.";
			link.l1 = "Co za sprawa? Mów szybko, śpieszę się.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "Znam cię. I wiem również, że właśnie otrzymałeś "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Generał")+"Te dokumenty są powodem, dla którego tak bardzo pragnę z tobą porozmawiać.";
			link.l1 = "I nie chcę omawiać tej sprawy z ludźmi, których nie znam. Chcesz zdobyć te papiery? Po prostu daj mi powód...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Dość, kapitanie! Czy wyglądam na rabusia? Jestem kupcem i reprezentuję interesy "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+"Chcę ci zaproponować bardzo opłacalny interes, ale nie tutaj. Chodźmy do pokoju w karczmie i omówmy tę sprawę. Nie zajmie ci to dużo czasu.";
			link.l1 = "To jest zbyt podejrzane... Nie będę z tobą robił interesów, panie! Zmykaj!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm.. Zobaczmy, co możesz mi zaoferować. Ale nawet nie próbuj mnie atakować, to się źle skończy. Ruszajmy, pójdę za tobą.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "Jesteś upartym i głupim człowiekiem, kapitanie! Oferowałem ci szansę na łatwe pieniądze. A ty... będziesz tego żałował.";
			link.l1 = "Spadaj!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Znakomicie! Chodź za mną.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Teraz możemy rozmawiać swobodnie.";
			link.l1 = "A jaka jest twoja propozycja?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "Jak już mówiłem, chodzi o dokumenty, które otrzymałeś w urzędzie portowym. Wszystko, czego potrzebuję, to ich kopia, i to wszystko\nZachowasz oryginał, więc zapłacą ci za pracę. Nikt nigdy się nie dowie, co się stało, a ja dobrze ci za to zapłacę.";
			link.l1 = "Przepraszam... Ale paczka jest zapieczętowana. Nie będziesz mógł zrobić kopii bez złamania pieczęci!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "Spodziewałem się tego pytania. Będę musiał złamać pieczęć, ale nie martw się, będę w stanie ją przywrócić. Mam duplikat kliszy i oczywiście lak. Nikt nie zauważy, że paczka była otwarta.";
			link.l1 = "Czy masz fałszywy stereotyp administracji portu "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = " Dlaczego pytasz, kapitanie? Tak, mam jeden. Naprawdę myślisz, że tylko się bawię? Oferuję ci "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" za możliwość obejrzenia tych dokumentów. Więc, czy w końcu dasz mi paczkę? Proszę.";
			link.l1 = "Weź to, ale potrzebuję ich z powrotem i zapieczętowanych!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "Wiesz, nie zrobię tego. Nie podoba mi się to.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Nie martw się. Jestem profesjonalistą. Usiądź i odpocznij. To zajmie około godziny.";
			link.l1 = "Dobrze.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... Nie spodziewałem się tego. Jesteś zbyt uparty, kapitanie, więc będę musiał cię zabić tam, gdzie stoisz, i zabrać paczkę za darmo. Módl się, bo posługuję się moją szablą równie dobrze, jak fałszywymi kliszami.";
			link.l1 = "To ty powinieneś się modlić, szpiegu!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Zrobione. Jak mówiłem, zostało to zrobione w najdokładniejszy sposób. Weź paczkę i obiecane "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". I muszę iść. Powodzenia, kapitanie, cieszę się, że zawarliśmy umowę.";
			link.l1 = "Żegnaj...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Witaj! Och, tak się cieszę, że cię widzę!";
			link.l1 = "Dzień dobry. Hm, powiedz mi, czyż nie dowodzisz "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Oh! A jak się o tym dowiedziałeś? "+pchar.questTemp.WPU.Escort.ShipName+"Tak, jestem jej kapitanem. A raczej byłem... Statek został zatopiony niedaleko stąd.";
			link.l1 = "Ach, zatem cię znalazłem... Pozwól, że się przedstawię - "+GetFullName(pchar)+" . Jestem tutaj na prośbę kapitana portu "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Opowiedział mi krótko o kłopotach waszej karawany i wysłał mnie, bym odnalazł wasz statek.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "Więc jesteś kapitanem ekipy ratunkowej?";
			link.l1 = "Coś w tym rodzaju. Moim zadaniem było znaleźć twój statek lub dowody na to, że zatonął lub nie jest w stanie żeglować. Niestety, nie znalazłem statku, ale jej kapitan żyje, to z pewnością dobra rzecz...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Och, przepraszam, zapomniałem się przedstawić. Jestem "+GetFullName(npchar)+" Czy już wiesz, jak to się stało, że tu trafiliśmy? Burza uczyniła nasz statek niekontrolowalnym\nKilka dni później uderzył w rafy niedaleko tej zatoki, a wichura zniszczyła go w kilka minut. Tylko kilka dziesiątków mojej załogi przeżyło. Reszta leży na dnie. Modlimy się za ich dusze każdego dnia...";
			link.l1 = "Proszę przyjąć moje kondolencje, kapitanie "+GetFullName(npchar)+" Przepraszam najmocniej.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Dziękuję... Ocaleni założyli obóz na brzegu, mając nadzieję na pomoc. Przybyłeś w samą porę, kapitanie! Miejscowi wojowniczy Indianie wiedzą o naszej obecności, nie mamy szans przeciw nim, jeśli nas zaatakują.\nJest również statek piracki, który krąży w tej okolicy, wygląda na to, że nas szukają. Spotkałeś tego pirata, kapitanie?";
			link.l1 = "Nie, nie mam.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Chwała Panu za to. On jest jednym z tych, którzy zaatakowali nas przed tą przeklętą burzą. Jak hiena, jest chętny, by dobić ranną ofiarę, więc przybył tutaj, na tę wyspę.";
			link.l1 = "Rozumiem. Teraz czas zdecydować, co robimy dalej.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "Aby zdecydować co, kapitanie? Weź nas na pokład i uciekajmy z tego przeklętego miejsca.";
			link.l1 = "Zaiste. Nie zdołałem ocalić statku, przynajmniej ocalę jego załogę. Zwijajcie swój obóz, a ja rozkażę wysłać tutaj łodzie. Witajcie na pokładzie!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Podziękowania, kapitanie! To nie potrwa długo. Czekaj... Co do diabła? Argh! Te czerwono-skóre diabły znowu do nas idą! Alarm! Do broni!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Fuh, udało się... Widzisz, kapitanie, mówiłem ci, że ta zatoka to prawdziwe piekło. To już trzeci atak Indian! Musimy opuścić to miejsce jak najszybciej, nie przetrwamy kolejnego ataku.";
			link.l1 = "Tak, masz rację. Zbierz każdą żywą duszę i przenieście się na mój statek! Rozkażę natychmiast wysłać nam szalupy!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hip... Czego ode mnie chcesz? Zjeżdżaj, nie mam ochoty z tobą gadać.";
			link.l1 = "Jesteś "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Tak, jestem. A jaki masz interes?";
			link.l1 = "To całkiem proste. Jest ktoś w tym mieście, kto ma dość twoich sztuczek. Ta osoba jest nimi zmęczona. Teraz patrzę na ciebie i widzę dlaczego. Nigdy więcej nie pokazuj się w lokalnym burdelu, bo będziesz miał kłopoty. Zrozumiano?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh! Śmiesz mi grozić, hultaju? Nadzieję cię na mój ostrze i upiekę jak kurczaka na rożnie!";
						link.l1 = "Przygotuj się, draniu!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "Co? Jakie sztuczki? Nie było żadnych sztuczek. Upijałem się i szalałem kilka razy w burdelu. Nikt nie jest doskonały... Dobra, dobra, dobra... Nigdy więcej nie skorzystam z ich usług. Teraz zadowolony? Masz moje słowo.";
						link.l1 = "Mam nadzieję, że dane słowo coś dla ciebie znaczy i jesteś świadomy konsekwencji w przypadku jego złamania. Miej to na uwadze. Żegnaj teraz.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "Jesteś tak bezczelnym człowiekiem, panie! Przysięgam, że sprawię, iż pożałujesz swoich słów przed zachodem słońca. Wyzwanie przyjmuję! Sądzę, że lepiej będzie walczyć na osobności, gdzieś w ciszy. Dżungla będzie w sam raz, spotkajmy się tam za dwie godziny!";
					link.l1 = "Wspaniały pomysł! Przynajmniej nie byłoby problemu z ukryciem twojego trupa.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "Co? Jakie sztuczki? Nie było żadnych sztuczek. Upijałem się i korzystałem z uciech kilka razy w burdelu. Nikt nie jest doskonały... Dobrze, dobrze, dobrze... Nigdy więcej nie skorzystam z ich usług. Teraz jesteś zadowolony? Masz moje słowo.";
					link.l1 = "Mam nadzieję, że słowo honoru coś dla ciebie znaczy i jesteś świadom konsekwencji w razie jego złamania. Pamiętaj o tym. Żegnaj teraz.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Poczekaj! Zatrzymaj się! Poddaję się! Oszczędź mnie!";
			link.l1 = "I tak właśnie teraz mówisz!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "Błagam cię, proszę, oszczędź mnie! Zrobię, co zechcesz! Nigdy nie pojawię się w tym burdelu!";
			link.l1 = "Ta poza pasuje tylko do takiego łajdaka jak ty. Mam nadzieję, że to będzie dla ciebie lekcja na resztę życia. I zachowuj się przyzwoicie w tym mieście.";
			link.l1.go = "Badboy_exit";
			link.l2 = "Pewnie, że nie. Twoje sztuczki zakończą się tutaj i teraz.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "Czas iść do diabła, skurwysynu! Módl się za siebie, ale rób to szybko, nie mam na to całego cholernego dnia...";
			link.l1 = "Mniej gadania, więcej walki, łajdaku!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "A oto i on, ten bezczelny drań! Pokażmy mu, kto rządzi w tym mieście, chłopaki!";
			link.l1 = "Ach, jesteś takim degeneratem! Ale ostrzegałem cię. Ty i twoje małpy zostaniecie wysłani prosto do piekła za chwilę!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Witajcie. Czego chcecie?";
			link.l1 = "Czyż nie jesteś "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Nie uwierzysz mi, ha-ha. Chcę twojej głowy.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... Nie... To nic. Wygląda na to, że się pomyliłem. Wybacz, że cię niepokoiłem.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "Co za głupi żart, panie! Wytłumacz się, albo ja...";
			link.l1 = "A co zamierzasz zrobić, nędzna śledziu? Zaszkodziłeś dobremu człowiekowi i jest naprawdę wściekły. Więc módl się teraz i rób to szybko, bo się spieszę.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "Co... co robisz, panie! Pomocy! Niech ktoś pomoże! Morderca!";
			link.l1 = "A ja myślałem, że spędzisz swoje ostatnie chwile na modlitwie, przynajmniej miałbyś szansę dotrzeć do nieba...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "Znowu ty? Czemu byś mi nie powiedział, czego chcesz?";
			link.l1 = "To nic.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ah?! Co? Co do diabła tu robisz, do cholery? Kto cię wpuścił?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "Liga potrzebuje twojego życia, kapitanie...";
			link.l1 = "Co? Kurwa!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i proszę cię, abyś schował swoją szablę.","Słuchaj, jestem obywatelem tego miasta i proszę cię, abyś schował swój miecz.");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jasne...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ostrożnie, "+GetSexPhrase("kumplu","dziewczyna")+", gdy biegnę z bronią. Mogę się zdenerwować...","Nie lubię, gdy są "+GetSexPhrase("ludzie, którzy","ludzie, którzy")+" idą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = LinkRandPhrase("Zrozumiałem.","W porządku.","Nie martw się...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
