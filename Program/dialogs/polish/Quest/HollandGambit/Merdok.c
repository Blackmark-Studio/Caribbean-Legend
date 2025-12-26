// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Panie, wybrałeś piekielnie zły moment na pogawędkę. Cały garnizon cię szuka. Lepiej się stąd szybko wynoś...";
			link.l1 = "Nie martw się. Nie zostanę tu długo.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Witaj, kapitanie. Czy interesuje cię intrygująca propozycja? ";
				link.l1 = "Wokół kręci się tyle osób z podobnymi ofertami, a ja jestem ciekawskim człowiekiem. Cóż to takiego? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Dzień dobry. Witaj w mojej aptece. Mam lekarstwa na większość chorób i dolegliwości. Co mogę ci zaoferować?";
			link.l1 = "Słuchaj, John, krążą plotki, że ktoś mieszka u ciebie na drugim piętrze...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Dzień dobry. Cieszę się, że widzę cię w mojej aptece. Mam lekarstwa na większość chorób i dolegliwości. Co mogę ci zaoferować?";
				link.l1 = "Witam pana, panie Murdock. Jestem tutaj w imieniu Lucasa Rodenburga. Przysłał mnie do pana, aby omówić sprawę dotyczącą Richarda Fleetwooda.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Dzień dobry. Jaki masz problem? Mam zarówno miksturę na kaszel, jak i proszek na biegunkę!";
				link.l1 = "Witaj, panie Murdock. Jestem tutaj w imieniu Lucasa Rodenburga. Wysłał mnie do ciebie, aby omówić sprawę dotyczącą Richarda Fleetwooda.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, oto wynajęty pies Rodenburga... Hercule, Longway - czy moglibyście tu wyjść?\nZabijcie tego człowieka!";
				link.l1 = "Poczekaj, mam receptę!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Dzień dobry. Cieszę się, że widzę cię w mojej aptece. Mam lekarstwa na większość chorób i niedomagań. Co mogę ci zaoferować?";
			link.l1 = "Na tę chwilę nic, dziękuję. Czuję się całkiem dobrze.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Witaj, nieproszony gościu. Nie zasłaniasz twarzy maską i nie wyglądasz na rabusia. Dochodzę więc do wniosku, że potrzebujesz czegoś innego od biednego aptekarza. Może czegoś na biegunkę?";
			link.l1 = "Witam cię również, Johan van Merden. Przynoszę pozdrowienia od Hercule'a Tonzaga. Widzę, że znasz to imię.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ach, więc tu jesteś. No cóż, czy spotkałeś się z Hercule'em? ";
					link.l1 = "Tak. Doszliśmy do porozumienia. John, zamierzam pomóc Hercule'owi, i mam kilka pytań do ciebie odnośnie Richarda Fleetwooda.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Cześć! Cieszę się, że cię widzę, "+pchar.name+"!";
					link.l1 = "Cześć, John. Czy udało ci się coś wykopać na temat Fleetwooda?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "Spóźniłeś się. Ptak opuścił gniazdo. Charlie Knippel odwiedził Willemstad i przywiózł stamtąd dziewczynę dla Richarda. Teraz płyną do Anglii z eskadrą wojskową za dzień lub dwa. Fleetwood zniknął, nigdy nie zobaczysz go w tym życiu.";
					link.l1 = "Cholera jasna. Całkowicie zapomniałem o Richardzie i straciłem poczucie czasu. Do zobaczenia.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Witaj z powrotem, "+pchar.name+"! Nic dla ciebie teraz. Nie ma żadnych wiadomości o Fleetwoodzie, a Charlie Knippel jeszcze nie wrócił z Kurakao...";
					link.l1 = "I nigdy nie będzie. Ani on, ani jego brygantyna.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ach, mamy gości! Witaj, Charlie! Dzień dobry, panno!";
					link.l1 = "Dzień dobry, John! Pozwól, że przedstawię ci moją towarzyszkę, narzeczoną Richarda, uroczą Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Ścisz głos... Co zamierzasz zrobić dalej?";
					link.l1 = "Dalej? Wolałbym się trochę przespać, ale niestety nie ma na to czasu. Zamierzam wyciągnąć Fleetwooda z dziury, w której się ukrywa, i dokończyć robotę Hercule'a.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Czy skończyłeś pisać? Pozwól, że zobaczę... Mój Boże Charlie, jesteś prawdziwym szaleńcem! Nie sądzisz, że zrobiłeś to trochę zbyt szczegółowo? Mam na myśli część o palcach, uszach i twarzy panny Shneur? Masz chore talenty, to pewne. Do diabła, zaraz stracę obiad!";
					link.l1 = "Blefuję, John. Nie zabiję dziewczyny. Mogę sprawić, że straci palec... Ale nic więcej. W końcu ma jeszcze dziewięć.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "Czy poszło dobrze? Widzę to w twoich oczach - udało ci się!";
					link.l1 = "Tak. Fleetwood przyjął moje warunki. Szczęki pułapki się zamykają. Teraz czekamy.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ach, witaj z powrotem, mój przyjacielu! Co możesz mi powiedzieć?";
					link.l1 = "Fleetwood nie żyje. Wszystko poszło zgodnie z planem. Przybył na wyspę, gdzie zorganizowałem zasadzkę na plaży. Walczył dzielnie, ale to mu nie pomogło. Tylko jeden z nas opuścił tę plażę.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "Dobrze "+pchar.name+", Mam dla Ciebie poważną ofertę. Sprawa, którą zamierzam omówić, jest bardzo niebezpieczna, ale biorąc pod uwagę sposób, w jaki pozbyłeś się Fleetwooda, jestem pewien, że sobie poradzisz. Masz...rzadką umiejętność rozwiązywania trudnych problemów.";
					link.l1 = "Jestem zaszczycony. Mów dalej.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Witaj z powrotem, "+pchar.name+" ! Jakieś dobre wieści dla mnie?";
					link.l1 = "John, od teraz możesz spać bez noża pod poduszką. Lucas już nie stanowi dla ciebie zagrożenia. Jest aresztowany i zamknięty, a wkrótce zostanie wysłany do Holandii, gdzie będzie sądzony za powstanie, usiłowanie morderstwa i inne występki.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Miło cię widzieć, "+pchar.name+"! Jesteś żywy - i to dobra rzecz. Jakieś wieści?";
					link.l1 = "Tak. Van Berg odszedł na dobre. Tak jak mówiłeś, znalazł mnie i zaatakował w najbardziej niewygodnym momencie. Van Berg był twardym orzechem do zgryzienia, ale w końcu go rozgryzłem.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Czy potrzebujesz czegoś jeszcze?";
			link.l1 = "Nie, John, nic. Odchodzę.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Dzień dobry. Cieszę się, że mogę cię zobaczyć w mojej aptece. Mam leki na większość chorób i dolegliwości. Co mogę ci zaoferować?";
			link.l1 = "Nic w tej chwili, dziękuję. Czuję się całkiem dobrze.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "Nie mam pojęcia, o czym mówisz, panie. Jaki Lucas Rodenburg? Nie mam żadnych spraw z Holendrami. Musiałeś się pomylić.";
			link.l1 = "Co? Mynheer Rodenburg mnie do ciebie przysłał!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Pozwól, że powiem to jeszcze raz - nie znam żadnego człowieka o imieniu Mynheer Rodenburg. Co do Holendrów, nie mam z nimi do czynienia. Są tylko dwie rzeczy, których nie mogę znieść na tym świecie: Ludzie, którzy są nietolerancyjni wobec innych kultur, oraz Holendrzy. Więc jeśli nie potrzebujesz żadnego lekarstwa, proszę, pozwól mi pracować.";
			link.l1 = "Coraz dziwniej i dziwniej...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Cóż, cóż... Jesteś od pana Rodenburga? Dobrze. Słucham cię.";
			link.l1 = "Muszę zorganizować spotkanie z kapitanem Fleetwoodem w ustronnym miejscu. Pożyczyłem 'Miraż' od Jacoba van Berga, holenderskiego kapra, którego pan Fleetwood tak bardzo chce pojmać. Chciałbym go poinformować, że 'Mirage' będzie wkrótce wygodnie zakotwiczony u wybrzeży Dominiki.";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Czy Jacob dał ci swój statek? Hm, więc teraz potrzebujesz kogoś, kto powie panu Fleetwoodowi, że 'Miraż' wkrótce będzie u wybrzeży Dominiki, ponieważ z pewnych powodów nie możesz sam o tym powiedzieć Richardowi...";
			link.l1 = "Dokładnie. Pan Rodenburg zalecił, abym zwrócił się do ciebie z tą sprawą.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "W tym przypadku Charlie Knippel jest człowiekiem, którego potrzebujesz. Lojalny przyjaciel Fleetwooda... i jego szpieg. Porozmawiaj z nim i wspomnij o wszystkim, co chcesz, aby Richard wiedział. Uważaj, Knippel może wydawać się dość prosty, ale nie jest głupcem.\nZnajdziesz go w małej chacie, niedaleko brzegu morza. Musi tam być.";
			link.l1 = "Rozumiem. Dziękuję, panie Murdock. Żegnaj!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			ForceAutolevel(sld, GEN_TYPE_ENEMY, GEN_BOSS, GEN_ARCHETYPE_RANDOM, GEN_ARCHETYPE_RANDOM, GEN_RANDOM_PIRATES, 0.6);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Naprawdę? Myślałem, że biedny Gaston już od jakiegoś czasu płonie w piekle.";
			link.l1 = "Mogło tak być, ale nie ma nikogo takiego jak Gaston. Znalazłem jego głowę w skarbcu starego Żyda na tajemniczej wyspie. Ale mimo to udało mu się przesłać ci pozdrowienia. Wspomniał też, że mamy wspólnego wroga: pana Rodenburga. Tonzag powiedział, że możesz mieć dokumenty ważne dla Lucasa, które mogą go wywabić z jego kryjówki na Kurakao.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "Miał rację. To moje archiwum spędza Rodenburgowi sen z powiek. Wygląda na to, że wciąż się kręci tylko z tego powodu. Rzecz w tym, że obiecano mu wygodną posadę w Komitecie Dyrektorów w Kompanii w Zjednoczonych Prowincjach. Jeśli informacje zawarte w tym archiwum, które zawiera wiele interesujących rzeczy o przeszłości i teraźniejszości Lucasa, staną się powszechnie znane, jego aspiracje zawodowe zostaną zduszone. W takim przypadku najlepsze, na co mógłby liczyć, to ścięcie zamiast powieszenia.";
			link.l1 = "Daj mi archiwum, a ja zajmę się naszym wrogiem.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "Musisz mnie mieć za głupca. Wciąż żyję tylko dlatego, że mam to przy sobie. Skąd mam wiedzieć, że teraz nie pracujesz dla Lucasa?";
			link.l1 = "Musisz mi uwierzyć na słowo - albo zginąć.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Zła odpowiedź, zginiesz tu i teraz! Longway, gongji!";
			link.l1 = "Oh ho, Chińczyk wyłania się z cieni! Bez obaw, zrobię z was obu chop suey!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "W końcu stanąłeś na nogi. Obawiałem się, że się nie obudzisz.";
			link.l1 = "Co...? Kim jesteś? Gdzie do diabła jestem? Jak się tu dostałem?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Spokojnie, nie zadawaj tylu pytań naraz, to nie jest dobrze, byś się zbytnio ekscytował. Nazywam się John Murdock, jestem aptekarzem tutaj w St. John's. Straciłeś przytomność w walce z ludźmi Fleetwooda. Muszę przyznać, że nieźle cię poturbowali... To Hercule przyprowadził cię tutaj do mojej apteki, a cóż, uleczyłem twoje rany moimi miksturami i lekarstwami.";
			link.l1 = "Hercule? Kto? Człowiek, który przyszedł mi pomóc na ulicy? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Tak. To on. Swoją drogą, chciałby z tobą porozmawiać. Musisz się z nim spotkać w mieście. Możesz jeszcze chodzić? Dobrze. Wyrusz w nocy - użyj tajnego tunelu, który zaczyna się za drzwiami na parterze mojego domu. Nie wychodź, dopóki nie zapadnie zmrok - ludzie Fleetwooda cię szukają.";
			link.l1 = "Aj... Gdzie jest mój statek?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Twój statek został skonfiskowany, a twoja załoga rozproszona w obawie przed zabiciem przez ludzi Fleetwooda. Przykro mi.";
				link.l1 = "Cholera...";
			}
			else
			{
				dialog.text = "Jest w porcie, na swoim zwykłym miejscu.";
				link.l1 = "Uff...dobrze to słyszeć. Myślałem, że go straciłem.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "Powinieneś poznać Hercule'a. Udaj się do miasta nocą przez tajny tunel. On się do ciebie zbliży. Teraz odpocznij, a ja muszę wrócić do swojej pracy.";
			link.l1 = "Dobrze, John. I... dziękuję za twoją pomoc i uzdrowienie!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood? Co chcesz o nim wiedzieć?";
			link.l1 = "Wszystko. Powiedz mi wszystko, co wiesz. Wydaje mi się, że nie jest dla ciebie tajemnicą, dlaczego Hercule przybył do Antigui. Jestem po jego stronie.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Bardzo dobrze. Kapitan Richard Fleetwood z Królewskiej- to znaczy Marynarki Wspólnoty... cholera, ciągle zapominam, że ten fanatyk Cromwell jest u władzy i zmienił nazwę. Niezależnie od tego, Fleetwood to dobry wojownik i doświadczony żeglarz. Dowodzi brygiem o nazwie 'Walkiria' - doskonałym statkiem, chciałbym zaznaczyć, z załogą elitarnych żeglarzy i marines. Prowadzi prywatną wojnę przeciwko Zjednoczonym Prowincjom ogólnie, a w szczególności z Holenderską Kompanią Zachodnioindyjską. Splądrował niezliczone holenderskie statki handlowe i wywindował koszty ubezpieczeń do niebotycznych wysokości. Gubernator Curaçao wyznaczył rekordową nagrodę za jego głowę.";
			link.l1 = "Hmm...  Wydaje się to nieco nietypowe, by oficer 'Marynarki Wspólnoty' zajmował się piractwem...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Tak, rzeczywiście. On chodzi po cienkiej linie. Anglicy oficjalnie nie uznają jego działań i odmawiają jakiejkolwiek współpracy, ale faktycznie zachęcają go w ukryciu. Mam powody przypuszczać, że jest jakoś związany z angielską siatką szpiegowską na Karaibach, a z tymi łotrami nie ma żartów.";
			link.l1 = "Poważny człowiek... To wszystko? Hercule opowiedział mi o jednym ze swoich pomocników... innym Charliem... jak on się nazywa... Kanister? Kula armatnia?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel? Tak, jest taki jegomość. Charlie Knippel był kiedyś głównym artylerzystą w Angielskiej Marynarce Wojennej, teraz jest na emeryturze. Teraz wiedzie spokojne życie na brzegu. Jest oczami i uszami Fleetwooda w St. John's, więc bądź ostrożny z nim i nawet nie myśl o wypytywaniu go o Richarda - skończysz w więzieniu albo gorzej.";
			link.l1 = "Rozumiem. Czy możesz mi powiedzieć coś jeszcze wartego wzmianki o Fleetwoodzie?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "Idol dla wszystkich kobiet na Antigui od szesnastu do sześćdziesięciu lat. Wydaje się, że to wszystko o nim. Cóż, myślę, że teraz wiesz, co się z nim stało. Leży w łóżku i liże rany.";
			link.l1 = "Na pewno ma jakieś słabe punkty czy też występki...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "Co masz na myśli?";
			link.l1 = "Cóż, może lubi hazard, pije ciężko lub nie może oprzeć się płci pięknej - coś w tym stylu. Czy jest żonaty?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "Nie, kawaler. Co do rzeczy, które wspomniałeś - nie jest znany z żadnej z nich.";
			link.l1 = "Rozumiem. Ale może jednak jest w nim coś wyjątkowego? Nawet ktoś taki musi mieć jakieś słabe punkty!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "Nie wiem. Słuchaj, zróbmy tak. Przyjdź do mnie za tydzień, a ja zbadam prywatne życie Fleetwooda. Zgoda?";
			link.l1 = "Umowa stoi. Dziękuję, John! Będę tu za tydzień.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Tak, ale niestety niewiele. I obawiam się, że to i tak na niewiele się przyda.";
			link.l1 = "Wykrztuś to! Każdy najmniejszy szczegół jest bardzo ważny, jeśli ma coś wspólnego z Fleetwoodem.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Niedawno Richard zabrał dwóch żydowskich uchodźców z nieznanej wyspy - starca i jego córkę, płynących do Willemstad. Statek, którym płynęli, został zatopiony przez piratów. Fleetwood potajemnie przywiózł ich na Curacao, ryzykując własnym karkiem. Od tamtej pory minęło kilka miesięcy. Teraz wysłał swojego wiernego psa Charlie'ego Knippela do Willemstad...";
			link.l1 = "Hmm... Jak to się łączy?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "Zdołałem się dowiedzieć, że Charlie otrzymał zlecenie, by dostarczyć tutaj jakąś dziewczynę z Willemstad, Żydówkę o imieniu Abigail Shneur. Tak, tę samą dziewczynę z wyspy. Wygląda na to, że Richard się w niej zakochał, skoro wysyła po nią swojego najlepszego agenta.\nTo wszystko. Nie wiem, czy to w ogóle pomoże.";
			link.l1 = "Oh ho ho! Hahaha! Wygląda na to, że nasz zatwardziały kawaler uległ chytrym urokom Żydówki. To doskonała robota, John, dziękuję! Kiedy nasz przyjaciel Knippel wyruszy na Curaçao?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "Opuścił wczoraj.";
			link.l1 = "Na którym okręcie?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "Wiedziałem, że o to zapytasz. Jest na brygantynie zakontraktowanej przez Wspólnotę - do diabła z tym, 'Królewską Marynarkę Wojenną'. Nazywa się 'Zeekalf'.";
			link.l1 = "'Zeekalf'? Toż to mocno holenderska nazwa dla angielskiego statku... ooo, już rozumiem.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "Jesteś bystry... Jej dawna nazwa to 'Royal Mary', ale na tę podróż została nazwana 'Zeekalf'. I powiewa na niej holenderska flaga.";
			link.l1 = "Twoja pomoc była nieoceniona, John. Wyruszam teraz. Wkrótce wrócę i będę potrzebował twojego pokoju na drugim piętrze, gdzie mnie przyjąłeś, gdy dochodziłem do siebie.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "Co knujesz?";
			link.l1 = "Opowiem ci wszystko, gdy wrócę. Życz mi szczęścia, John! Żegnaj.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Naprawdę? Dlaczego jesteś tego taki pewien?";
			link.l1 = "Bo Charlie leży na dnie morza, karmiąc ryby. Wziąłem na abordaż 'Zeekalf' i wysłałem Knippela do diabła. Oczywiście, wcześniej go przesłuchałem... Miał przy sobie list, który pozwolił mi udawać Knippela, gdy rozmawiałem z naszą Żydówką Abigail, ukochaną naszego dzielnego Richarda.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm... To sprytne. Więc mówisz, że...";
			link.l1 = "Tak. Przywiozłem Żydówkę na Antiguę. Jest na pokładzie mojego statku. Teraz mam asa atutowego w mojej grze z Fleetwoodem! Zrobi dla niej wszystko...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Jesteś pewien? Może się okazać, że nie wszystko jest tak proste, jak sugerujesz...";
			link.l1 = "O tak, jestem absolutnie pewien. Z listu wywnioskowałem, że ojciec Abigail był przeciwko jej małżeństwu z Richardem z powodu pieniędzy. Wiem, typowy żydowski teść. Więc Fleetwood postanowił zapłacić jej ojcu posag - 200000 pesos! Powiedz mi teraz, ile dziewczyn na świecie jest wartych takich pieniędzy?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! Z pewnością nie Żydówka! W życiu nie spotkałem chrześcijańskiej dziewczyny, która byłaby tego warta, to pewne."+pchar.name+", jesteś przebiegłym łajdakiem. Co z nią zrobisz?";
			link.l1 = "Przyprowadzę tu Żydówkę i zatrzymamy ją w twoim pokoju. Powiem jej, że Richard wypłynął w morze i jeszcze nie wrócił, więc będzie naszym gościem przez tydzień. Myśli, że jestem Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "To ciekawe. Więc postanowiłeś zatrzymać dziewczynę w moim domu? Hmm...";
			link.l1 = "John, ona jest Żydówką. Bezpaństwowa wędrowniczka sprowadzona z holenderskiej kolonii. Jest nikim tutaj w St. John's i nikt jej nie zna. Uspokój się, możemy robić, co nam się podoba, a ona nie odważy się pisnąć słowa. Nie ma grosza ani przyjaciela. I tak, nie będzie naszym gościem zbyt długo. Zwabię Fleetwooda, używając jej jako przynęty, a potem nie będziemy jej już potrzebować.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "Zaczynasz mnie przerażać, Charles. Nie zamierzasz wykorzystać tej dziewczyny, prawda? Albo doprowadzić ją do takiego samego końca jak Knippela?";
			link.l1 = "Nie, oczywiście, że nie. 'Przebiegły łotr' mogę być, ale nie jestem wrogiem pięknych dziewcząt - Żydówek ani Chrześcijanek. Albo z brzydkimi, jeśli o to chodzi. Jeśli będzie się dobrze zachowywała, przywiozę ją do jej ojca w Willemstad, kiedy to wszystko się skończy. Stary skąpiec prawdopodobnie padnie na kolana i podziękuje mi za uratowanie jej przed tym perfidnym Anglikiem.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "Ona ma swoją rolę do odegrania w tej maskaradzie. Kiedy przedstawienie się skończy, nie będę jej potrzebował.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "Rozumiem, czyli na razie muszę się nią opiekować.";
			link.l1 = "Nie będę nalegał, kamracie. Jeśli jesteś całkowicie przeciwny temu, może zostać na pokładzie mojego statku. Ale wtedy będę musiał zakłuć ją w kajdany dla bezpieczeństwa i trzymać w ładowni z szczurami, by chronić ją przed moją załogą. To dla nich nowość mieć kobiety na pokładzie, wiesz. Szkoda byłoby tak traktować taką piękną dziewczynę.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "Rozumiem, więc na razie muszę się nią zająć.";
			link.l1 = "Nie będę nalegał, kamracie. Jeśli jesteś całkowicie przeciwny temu, może zostać na pokładzie mojego statku. Ale wtedy będę musiał skuć ją w kajdany dla bezpieczeństwa i trzymać w ładowni z szczurami, aby chronić ją przed moją załogą. To dla nich nowość mieć kobiety na pokładzie, wiesz. Szkoda by było traktować taką piękną dziewczynę w ten sposób.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "Rozumiem. Dobrze, przyprowadź ją tutaj. Moim obowiązkiem jest pomóc ci w walce przeciwko Fleetwoodowi. Przyprowadź ją tutaj, a przygotuję jej 'pokój gościnny'.";
			link.l1 = "Dzięki, John. Wiedziałem, że mogę na ciebie liczyć.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "O! Z największą przyjemnością. Cieszę się, że mogę powitać tak ważną i... elegancką damę. Panno, czy mogłaby Pani udać się na drugie piętro, proszę. Czeka tam na Panią kolacja, a łóżko jest pościelone. Jestem pewien, że będzie chciała Pani dobrze się wyspać po tak długiej podróży.";
			link.l1 = "Tak. Abigail z pewnością jest zmęczona po tak długiej podróży z Willemstad.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Masz już plan?";
			link.l1 = "Racja. Musimy napisać list do Richarda z żądaniem okupu za Abigail. Zorganizuj spotkanie gdzieś na bezludnej wyspie - na przykład na Turks. A jeśli się nie zgodzi, to, jakby to ująć, wyślemy mu jego hebrajską ukochaną w kawałkach.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "Po cóż takie komplikacje z bezludną wyspą?";
			link.l1 = "Neutralny grunt. To bezpieczniejsze. I tak nie zamierzam przyprowadzać Abigail. Potrzebuję Fleetwooda. Na pewno przygotuje zasadzkę na Antigui, ale na Turks nie będzie miał takiej przewagi.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Zgoda. Kto przekaże list? To bardzo niebezpieczne.";
			link.l1 = "Nieznajomy. Wybierz pijaka z tawerny, takiego, który wygląda na godnego zaufania. Będą skłonni zrobić cokolwiek, o co ich poprosisz, za trochę rumu. Jeśli Richard zabije go w napadzie wściekłości, wyślemy kolejnego. I dołączymy jeden z palców Abi do listu. To uczyni go znacznie bardziej uległym.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = " "+pchar.name+"...";
			link.l1 = "Nie martw się, John. Jestem pewien, że do tego nie dojdzie. Musisz tylko znaleźć kuriera, a ja od razu napiszę list. Masz trochę papieru i atramentu?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Tak, znam. I przypadkiem znam również odpowiedniego pijaka. Polecam Jacka Harrisona. Spędza każdy wieczór w tawernie, tankując się rumem. Łatwo go znajdziesz.";
			link.l1 = "Dobrze, przynieś mi pióro i atrament, a ja napiszę list z żądaniem okupu dla Richarda.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "Kiedy zamierzasz mu wręczyć list? Czy zamierzasz obserwować dostarczenie w trakcie?";
			link.l1 = "Oczywiście. Richard nie jest głupcem, ale wątpię, że podejmie ryzyko. Przynajmniej mam taką nadzieję. Nie chcę skrzywdzić dziewczyny, ale zrobię to, jeśli będę musiał. Cóż, czas znaleźć pijanego, o którym wspomniałeś. Jack... jakie było jego pełne imię?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "On się nazywa Jack Harrison. Zazwyczaj odwiedza tawernę wieczorem. Bądź ostrożny!";
			link.l1 = "Wszystko będzie dobrze. Poczekaj na mnie.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Cóż, nie powiedziałbym tak. Fleetwood jest przebiegły i niebezpieczny. Na dodatek jest mistrzem szermierki i doświadczonym żeglarzem. Nie będzie łatwą zdobyczą.";
			link.l1 = "Przestałem iść na łatwiznę, kiedy przybyłem na Karaiby. Cóż, John, czas na mnie. A tak przy okazji, wspomniałeś, że nasz dzielny Fleetwood ma dobry statek, prawda?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "Ma najwspanialszy bryg, jaki kiedykolwiek widziałem. A widziałem ich całkiem sporo.";
			link.l1 = "To dobrze. Lubię dobre statki. Czas podnieść kotwicę!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "Brak mi słów! Doskonałe połączenie, świetny pomysł i mistrzowska realizacja! Moje gratulacje, "+pchar.name+"! I udało ci się również zdobyć jego brygantynę jako nagrodę!";
				link.l1 = "Dziękuję! A gdzie jest Hercule? Chciałbym go zobaczyć. Kiedy ostatnio się spotkaliśmy, powiedział mi, że będę mógł go znaleźć z twoją pomocą.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "Doskonale połączenie, świetny pomysł i mistrzowska realizacja! Moje gratulacje, "+pchar.name+"!";
				link.l1 = "Dziękuję! A gdzie jest Hercule? Chciałbym go zobaczyć. Kiedy ostatnio się spotkaliśmy, powiedział mi, że będę mógł go znaleźć z twoją pomocą.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Oczekuję go w każdej chwili. Powinien przybyć tutaj przez tajemny tunel. A ty powinieneś wyjaśnić się Abigail. Zaczęła martwić się o nieobecność Richarda.";
			link.l1 = "Dobrze, ale czy nie powinniśmy odesłać jej do domu?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Jeszcze nie... Najpierw muszę z tobą porozmawiać. Ale najpierw poczekaj na przybycie Hercule'a. Idź i pociesz Abigail. Opowiedz jej jakąś historię, wymyśl coś. Potem przyjdź do piwnicy. Zgoda?";
			link.l1 = "Tak, tak, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Cóż, nadszedł czas, by odkryć karty. Jak zapewne się domyślasz, nie jestem zwykłym aptekarzem. Moje prawdziwe imię to Johan van Merden i do niedawna byłem agentem Holenderskiej Kompanii Zachodnioindyjskiej oraz prawą ręką jej wiceprezesa Lucasa Rodenburga.";
			link.l1 = "Naprawdę!  To ciekawe...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "To teraz inaczej. Lucas chce opuścić grę i wrócić do Niderlandów, więc musi zakopać wszystko i wszystkich związanych z jego przeszłością\nMyślę, że wciąż oddycham tylko z powodu moich archiwów, które zawierają wszystkie informacje o zbrodniach Lucasa... jak historia 'statku widmo', który jest zwykłym pirackim statkiem pod dowództwem lekkomyślnego i bezwzględnego łotra Jacoba van Berga. Rodenburg zatrudnił tego człowieka do plądrowania i zatapiania angielskich statków handlowych\nVan Berg jest również odpowiedzialny za zatopienie flauty z Abigail i jej ojcem na pokładzie. Abigail jest ważną postacią w tej grze, Rodenburg również chciał jej ręki i serca, podobnie jak Fleetwood, więc byłem dość zaskoczony, gdy ją tutaj przyprowadziłeś...";
			link.l1 = "Rodenburg... to ten zięć, o którym opowiadał ekscentryczny ojciec Abigail!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Tak, dlatego chcę, aby została tutaj na chwilę. Może być moim ostatnim asem w grze przeciwko Rodenburgowi, choć wolałbym jej nie używać dalej, jest dobrą dziewczyną, nie chcę, żeby cierpiała. Myślę, że Lucas wybrałby moje archiwum zamiast niej, gdyby taka była możliwość wyboru.\nWięc proponuję, abyś był moim sojusznikiem w grze przeciwko Lucasowi... pozbądź się go, użyj wszelkich dostępnych środków. Nagroda będzie znaczna.";
			link.l1 = "Hmm... Nie sądzę, żeby to było trudniejsze niż z Fleetwoodem. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "Nie, mylisz się. W końcu Fleetwood był samotnym wilkiem, działającym na własną rękę. Rodenburg jest wiceprezesem Kompanii. To bardzo wpływowy człowiek, tylko gubernator Curacao ma więcej władzy. Jacob van Berg jest jego agentem, bardzo niebezpiecznym człowiekiem. Lucas siedzi na swoim zadku w Willemstad pod ochroną strażników Kompanii, są równie dobrzy jak ludzie Fleetwooda.\nTo nie będzie łatwe.";
			link.l1 = "Zasady gry są takie same - zwabić tygrysa z jego legowiska... Mam już plan. Co jeszcze możesz mi powiedzieć o Lucasie?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Cóż, powiedziałem ci prawie wszystko. Posiada szybki statek o nazwie 'Meifeng' - Piękny Wiatr. Jej kapitanem jest Chińczyk o imieniu Longway - przysięgły człowiek Rodenburga. On również jest wrogiem, z którym nie chciałbyś się zmierzyć. W załodze Lucasa nie ma amatorów.";
			link.l1 = "Od samego początku mieliśmy asa w rękawie - twój archiwum. Jeśli ceni swoje życie bardziej niż Żydówkę, to zrobi wszystko, by informacje w archiwum pozostały poufne... Ale... czy to archiwum naprawdę istnieje, John? Blefujesz?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "Archiwum istnieje. I Lucas o tym wie. Czy już coś wymyśliłeś?";
			link.l1 = "Mam. John, jeśli naprawdę byłeś agentem kompanii, powinieneś coś wiedzieć.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "Co dokładnie? Zapytaj mnie.";
			link.l1 = "Muszę przechwycić statek kompanii. Najlepiej, żeby to był statek bez eskorty - kurier albo coś w tym rodzaju. Czy możesz mi coś na ten temat powiedzieć?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... Nie posiadam takich informacji. Czekaj! Na pewno wiem, że Kompania ma statek pocztowy na szlakach morskich między Philipsburg a Willemstad raz w miesiącu. Dostarcza dokumenty biznesowe. To brygantyna o nazwie 'Hoop'.\nOpuszcza Philipsburg dzisiaj lub jutro.";
			link.l1 = "Tak jest! Tyle mi potrzeba, by wyruszyć na brzegi Świętego Krzysztofa. Morska droga do Curaçao przebiega tuż obok.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Powodzenia, "+pchar.name+"Nie będę pytał cię o szczegóły twojego planu. Będę czekał na twój powrót!";
			link.l1 = " Wszystko będzie dobrze, John. Zajmij się Żydówką i traktuj ją dobrze!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Niewiarygodne! Nie mogę uwierzyć własnym uszom! Jak to się stało?";
			link.l1 = "Przechwyciłem statek pocztowy i wysłałem list do Lucasa w imieniu Fleetwooda, w którym stwierdziłem, że przejąłem pewne archiwum należące do jakiegoś aptekarza ze St. John's, i że wkrótce dowody jego wszelkich niegodziwości staną się znane od Amsterdamu po Londyn. Oczekiwałem, że zacznie mnie ścigać, ale okazało się, że stało się odwrotnie.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas oskarżył Matthiasa Becka o zdradę i współpracę z Anglikami, wsadził go za kratki i zajął rezydencję w pałacu gubernatora. Najprawdopodobniej wyeliminował kapitana brygantyny. Potem nakazał swojemu wiernemu Chińczykowi z Meifeng zatopić statek z dyrektorem Kompanii Peterem Stuyvesantem na pokładzie!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg to bezwzględny człowiek. Ale nawet ja nie sądziłem, że mógłby posunąć się do takich skrajności...";
			link.l1 = "Przechwyciłem Meifeng i przesłuchałem Longwaya. Powiedział mi wszystko. Znalazłem Stuyvesanta i ostrzegłem go o zamiarach Rodenburga, a my razem popłynęliśmy do Willemstad. Stuyvesant uwolnił Becka i aresztował Lucasa. Teraz jest w więzieniu.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! Masz prawdziwy talent, mój przyjacielu... Powinieneś zrobić karierę w Marynarce Kompanii lub jako polityk w Zjednoczonych Prowincjach - masz wszelkie szanse, by zostać gubernatorem! I co zrobiłeś z Longwayem?";
			link.l1 = "Pozwoliłem mu odejść. Poddał się honorowo, więc nie zrobiłem mu krzywdy.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "To dobrze. Longway to porządny człowiek, w przeciwieństwie do jego byłego szefa. Cóż, "+pchar.name+", wykonałeś świetną robotę! Przygotuję twoją nagrodę, ale potrzebuję trochę czasu... W międzyczasie...";
			link.l1 = "John, prawdę mówiąc, jest pewien haczyk. Longway, a potem Rodenburg, powiedzieli mi, że Jacob van Berg mnie ściga. Jak źle to jest?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg? Charlie, to jest poważne. On jest bezlitosnym piratem, zręcznym żeglarzem i wojownikiem, który sprawia, że Fleetwood wygląda jak kociak. Profesjonalny łowca. To on niszczył statki na rozkazy Rodenburga.\nOn cię znajdzie, więc musisz się przygotować. Powinienem sam zadbać o swoje bezpieczeństwo.";
			link.l1 = "Jak mogę znaleźć tego van Berga?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "Nie wiem. Lucas i Longway byli jedynymi, którzy wiedzieli, gdzie go znaleźć. Więc bądź ostrożny i gotowy\nZamykam to miejsce. Przejdź przez tajny tunel, jeśli chcesz mnie zobaczyć. I zabierz Żydówkę, zbyt niebezpiecznie dla niej tu zostać.";
			link.l1 = "Nie martw się, John. Niech się pojawi, a ja się nim zajmę. Gdzie jest Abigail?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "Poszła do kościoła. Żal mi jej. Ostatnio była bardzo zdenerwowana.";
			link.l1 = "Cóż...To miła niespodzianka. Być może zdaje sobie sprawę, że Chrystus jest Mesjaszem, na którego jej ludzie od dawna czekali. Czas więc, by ją odesłać do ojca.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "Ona chciała cię zobaczyć. Jestem pewien, że poprosi cię, abyś zabrał ją z powrotem do domu.";
			link.l1 = "Abi, co?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Cóż, muszę przyznać, że staliśmy się przyjaciółmi. Nie żałuję, że mieszkała w moim domu, i dzięki Bogu, nigdy się nie dowie, dlaczego została tu przywieziona.";
			link.l1 = "Dobrze, John, pójdę do kościoła spotkać się z Abigail. Potem kieruję się do Willemstad.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Ty... rozbiłeś mu orzechy? Och - metafora. Cóż, czy to orzechy, czy nie, zrobiłeś to! Gratulacje!";
			link.l1 = "Nie skłamałbym ci, heh. Teraz możesz odetchnąć swobodnie, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Wreszcie! Myślę, że lepiej zrezygnować z tych wszystkich politycznych gier i intryg. Teraz czas porozmawiać o twojej nagrodzie za wykonaną pracę.";
			link.l1 = "Cóż, na pewno bym to docenił.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "Zamierzam opuścić Karaiby na zawsze. W ramach podziękowania za twoją pomoc i ocalenie mnie od Rodenburga, przekazuję ci akt własności tego domu i mojej apteki. Teraz są one twoje. Weź klucze.";
			link.l1 = "To wspaniale! Jestem bardzo szczęśliwy. Masz bardzo wygodny dom i przytulną piwniczkę...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "A także proszę przyjąć tę skromną sumę 100 000 pesos oraz tę muszkietę. Dobrze mi kiedyś służyła, a i Tobie dobrze posłuży.";
			link.l1 = "Nie odrzucam takich darów!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "W pokoju na piętrze znajdziesz młodego filozofa przyrody. Jest najlepszym aptekarzem, jakiego znam. To on przygotował te mikstury, które pomogły ci wyzdrowieć w kilka dni. Zadbaj o jego wynagrodzenie, a jego wiedza wynagrodzi wszystkie twoje koszty z nawiązką.";
			link.l1 = "Mój własny mol książkowy? Bardzo dobrze, zajmę się nim.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "Muszę teraz się pożegnać. Idę do piwnicy, aby spakować swoje rzeczy. Jutro mnie tu nie będzie - odpływam z Antigui. Cieszę się, że cię poznałem i cieszę się, że byłeś po mojej stronie, a nie z moimi wrogami.";
			link.l1 = "Również cieszę się, że cię poznałem, John. Może jeszcze się spotkamy...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Nie w tym życiu, przyjacielu. Zbieram się. Żegnaj, "+pchar.name+"!";
			link.l1 = "Żegnaj, John! Powodzenia!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ach, dobry panie, nie słuchaj tych głupich rozmów. Tam nikogo nie ma. Tam jest moje laboratorium, przygotowywane są mikstury, wiesz...";
			link.l1 = "Wszystkie żarty na bok, John. Czy imię Gino Gvineili coś ci mówi?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Aha! Widzę to w twoich oczach - mam rację... Tam mieszka i dla kogo przygotowuje swoje zioła!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Panie, mówię ci raz jeszcze - tu nikogo nie ma.";
			link.l1 = "Odłóżmy na bok wymówki, John. Nie skrzywdzę twego alchemika - ale jeśli ojciec Vincento z Santiago go znajdzie, nie mogę być pewien. Inkwizytor już planuje wysłać swoich 'Domini Canes' na Antiguę...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Czego od niego chcesz?";
			link.l1 = "Po prostu porozmawiać. Ma dla mnie dość ważne informacje. Obiecuję, że nie wydam go Inkwizycji i w żaden sposób go nie skrzywdzę.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino to dobry człowiek. Nie wierz w nic, co ojciec Vincento ci o nim powiedział. I pamiętaj - stanę w obronie mojego alchemika.";
			link.l1 = "Dałem ci moje słowo. Czy to nie wystarczy?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Idź na górę, zatem. Drzwi są otwarte. I miej nadzieję, że dotrzymasz słowa.";
			link.l1 = "Bądź pewien, że zrobię to.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Kapitánie, czyż nie chciałbyś zapoznać się z hermetycznymi sztukami? Mogłoby to być dla ciebie bardzo przydatne.";
			link.l1 = "Przykro mi, ale moje zajęcie jest nieco inne. Jestem przyzwyczajony do trzymania rękojeści miecza - nie flaszek czy probówek.";
			link.l1.go = "alchemy_exit";
			link.l2 = "'Są rzeczy na niebie i ziemi, o których nie śniło się waszej filozofii.' Oczywiście, z chęcią. Czego potrzeba?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "Jak sobie życzysz. Ja tylko oferowałem...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "Powinieneś nauczyć się mieszać zioła własnoręcznie. Ale nie uda ci się bez zestawu alchemika. Spójrz na tę torbę. Jest tam wszystko, czego potrzebuje początkujący alchemik - probówki, kolby, alembik, szpatułki, szklane rurki, palnik i wiele podobnych rzeczy...";
			link.l1 = "Bardzo interesujące! A co mogę z tego przygotować?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Cóż, nie będziesz w stanie zamienić ołowiu w złoto, ale będziesz mógł mieszać składniki według różnych przepisów i w ten sposób uzyskiwać mikstury i inne przydatne rzeczy.";
			link.l1 = "Przepisy?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "Prawda. Musisz znać przepis, aby stworzyć miksturę lub przedmiot. Przepisy można kupić od kupców lub znaleźć gdziekolwiek. Gdy już przestudiujesz przepis, powinieneś zebrać wszystkie potrzebne składniki i postępować dokładnie według tego, co tam jest napisane\n Użyj swoich narzędzi alchemicznych, znajdź lub kup moździerz i tłuczek, poszukaj tygla, niestety, nie posiadam dodatkowego, aby ci go dać. Zioła, spirytusy, mikstury, minerały, śmieci - wszystko się przyda, pod warunkiem, że masz odpowiedni przepis i narzędzia.";
			link.l1 = "Bardzo interesujące. A ile chcesz za ten zestaw?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Dwadzieścia tysięcy pesos. To bardzo dobry zestaw i szybko pokryje swoje koszty.";
			link.l1 = "Drwisz ze mnie, prawda? Torebka ze szkłem za cenę lugra? Nie, podziękuję.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "Zgadzam się. Myślę, że interesujące będzie spróbować zrobić coś własnymi rękoma.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie pożałujesz tego zakupu, jestem absolutnie pewien. Zdecydowanie bardziej opłaca się robić mikstury samodzielnie, gdy ich potrzebujesz, niż odwiedzać stragany zielarzy i kupować wszystko, czego potrzebujesz, po kawałku. Poza tym, nie zawsze będzie możliwe kupienie wszystkiego, czego potrzebujesz. ";
			link.l1 = "Uczmy się. Myślę, że dam radę!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("złodziej, panie! Strażnicy, bierzcie go","złodziejka, dziewczyno! Straże, złapcie ją")+"!!!","Spójrz tylko na to! Ledwie zamyśliłem się, a ty postanowiłeś sprawdzić moją skrzynię! Łap złodzieja!!!","Straże! Napad! Łapać złodzieja!!!");
			link.l1 = "Do diabła!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
