// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kapitanie. Nazywam się Longway. Longway oddaje swój statek pod twoje dowództwo. Longway także jest pod twoim dowództwem. Rozkaz od pana Rodenburga.";
			link.l1 = "Witaj, Longway. Charles de Maure, do usług. Czy masz jakieś informacje na temat operacji eliminacji Jacoba van Berga?";
			link.l1.go = "Longway_friend";
			link.l2 = "Dobrze cię widzieć, Longway. Nazywam się Charles de Maure. Nie ma czasu do stracenia - mynheer Rodenburg docenia szybką i wysokiej jakości pracę. Gdzie teraz ukrywa się Jacob van Berg?";
			link.l2.go = "Longway_neutral";
			link.l3 = "Cóż, a moje to Charles de Maure! Miejmy nadzieję, że nasze będą dobrze współpracować! Więc, mynheer Longway, powiedz mi, proszę, gdzie nasze powinny szukać Jacoba van Berga?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Longway jest pewien, że będziemy dobrze współpracować, chuanzhang. Jacob van Berg obecnie w "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Generał")+"Zaaranżowałem spotkanie z nim w lokalnej tawernie. Będzie tam.";
			link.l1 = "Wypłyńmy w morze!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "Rozkaz prawa mynheera Rodenburga dla Longway... Jacob van Berg obecnie w "+XI_ConvertString("Kolonia"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+"Zaaranżowałem spotkanie z nim w lokalnej tawernie. Będzie tam.";
			link.l1 = "Wypływamy w morze!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			notification("Longway disapproves", "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "Longway zrobi wszystko, co w jego mocy, chuanzhang. A Jacob van Berg obecnie w "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"Umówiłem się z nim na spotkanie w lokalnej tawernie. Będzie tam.";
			link.l1 = "Wyruszajmy w morze!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			notification("Longway approves", "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Co może zrobić Longway, chuanzhang?";
			link.l1 = "Nic na razie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Ty głupcze, mongolski bałwanie, chuanzhang! Mieliśmy łatwe zadanie - zdobyć 'Mirage' bez straty 'Meifeng'. Była łatwym celem bez swojego chuanzhang, a jednak nie udało ci się wykonać zadania\nLongway ani nie będzie ci służył, ani cię więcej nie zobaczy. Longway jest pewien, że Mynheer Rodenburg zatwierdzi jego decyzję.";
				link.l1 = "Do diabła z tobą i twoim panem!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Ty idioto Mongoł, chuanzhang! Zmarnowaliśmy zbyt wiele czasu na rozwiązywanie twoich spraw zamiast spotkać się z Jacobem van Bergiem. On już odszedł z "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nNie udało ci się wykonać zadania. Longway nie chce ci ani służyć, ani cię więcej widzieć. Longway jest pewien, że Mynheer Rodenburg zatwierdzi jego decyzję.";
				link.l1 = "Do diabła z tobą i twoim panem!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Chuanzhang, zmarnowałeś zbyt wiele czasu bez rezultatu. To nie jest twój statek, a Longway nie jest twoim kulisem. Longway wraca do Willemstad\nLongway ani ci nie służy, ani cię więcej nie zobaczy. Longway jest pewien, że Mynheer Rodenburg zaaprobuje jego decyzję.";
				link.l1 = "Do diabła z wami i waszym panem!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "Chuanzhang, Longway opuścił pana Rodenburga. Longway nigdy do niego nie wróci. Byłeś dobry dla Longwaya i jesteś odważnym chuanzhang. Longway chce dołączyć do twojej załogi jako twój sługa, Panie Kapitanie.";
			link.l1 = "Nie jako sługa, ale jako oficer! Witaj na pokładzie, przyjacielu!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "Nie, dziękuję, Longway. Jesteś wolnym człowiekiem. Nie potrzebuję twoich usług.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "  Dlaczego   przestajesz?    Zabij.     Longway zmęczony, Longway pragnie śmierci.    Xing... wybacz mi.";
			link.l1 = "Nie tak szybko, Chińczyku. Zabiję cię, jeśli zechcę, ale najpierw muszę z tobą porozmawiać. Twój los zależy od twoich przyszłych działań. Na razie, witaj w mojej ładowni!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "Teraz możemy porozmawiać bez dźwięku zderzających się mieczy dzwoniącego w moich uszach. Słuchaj, Longway, potrzebuję informacji i nie mam wątpliwości, że wiesz, co muszę wiedzieć. Pytanie brzmi: powiesz mi to po dobroci, czy po złości?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Milczysz? Dobrze. Proponuję ci umowę. Oszczędzę ci życie i wysadzę na najbliższym brzegu. W zamian powiesz mi, gdzie i dlaczego Lucas Rodenburg cię wysłał. Umowa?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "Wiem, że rozumiesz angielski, holenderski i francuski. Jesteś także dobrym słuchaczem. Teraz nadszedł czas, byś zaczął mówić. W końcu powiesz mi wszystko, co wiesz. Wiem, że wy, Chińczycy, jesteście dumni ze swojej sztuki tortur, ale my, ludzie Zachodu, dokonaliśmy własnych postępów w tej starożytnej nauce. Alonso tutaj jest mistrzem w rozwikływaniu języków ludziom. Był przesłuchującym dla Świętej Inkwizycji w Santiago, zanim zatrudnił się na moim statku. Zna wszelakie sztuczki, których nauczył się od świętych ojców, którzy doskonalili sztukę zmuszania ludzi do przyznania się... nawet nie musisz być protestantem!";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "Moja dowcipność jest na ciebie marnowana. Powiesz mi wszystko, mój skośnooki przyjacielu... Wszystko... Ale długo nie pożyjesz po tym, nie, nie pożyjesz. Twoje ciało dozna wielkich cierpień po spotkaniu z Alonsem. Więc wybór należy do ciebie. Albo powiesz mi całą prawdę i będziesz żył, albo powiesz mi całą prawdę i umrzesz w agonii na torturach. Dręczony bólem na torturach. Rozumiesz? Nie martw się, zadbam o to, by obecny był ksiądz, aby ochrzcił cię na chrześcijanina, by oszczędzić twojej pogańskiej duszy wiecznych ogni piekielnych.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Widzę, że w twych czarnych oczach rośnie zwątpienie. Czemu masz umierać za grzechy swego pana? Czy on jest tego wart? Czy Rodenburg naprawdę jest wart, by wyrwano twą duszę z cierpiącego ciała?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Longway mówi. Ale najpierw Longway chce mieć pewność, że dotrzymasz słowa, chuanzhang.";
			link.l1 = "Ha! Mądre słowa! Daję ci słowo, chłopcze.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Przepraszam, chuanzhang, twoje słowo nie wystarczy. Zdobywasz informacje i zabijasz Longwaya później! Longway chce gwarancji.";
			link.l1 = "Targujesz się jak Żyd. Jakie chcesz gwarancje?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "Jest mała wyspa na południe od Gwadelupy. Przylądek Niedostępny. Tam wysadź Longwaya i daj mu broń. Tylko wtedy Longway powie ci wszystko, co wie o Lucasie Rodenburgu.";
			link.l1 = "Nie jesteś w pozycji, by się ze mną targować, Chińczyku.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Zrobiłbyś to samo, gdybyś był Longwayem, chuanzhang. Nie byłoby łatwo twoim ludziom wydobyć ze mnie słowa, nawet przy torturach. Longway nie jest słabym białym człowiekiem.";
			link.l1 = "Dobrze. Umowa stoi. Ale ostrzegam cię - nie próbuj mnie oszukać, bo osobiście posiekam cię na kawałki. Na tysiąc kawałków, i to powoli...tak jak robią to wasi cesarze. Alonso!";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "Mówisz prawdę. Ale pamiętaj - zaszedłem zbyt daleko, abyś mógł to zepsuć. Jeśli spróbujesz mnie powstrzymać, skończę z tobą jak z owadem pod butem.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Dotarliśmy do Gwadelupy, chuanzhang?";
			link.l1 = "Uspokój się, wkrótce tam będziemy.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Dotrzymałeś słowa, chuanzhang. Longway też dotrzyma. Chciałeś wiedzieć o misji Longwaya?";
			link.l1 = "Tak. Ale pozwól mi przypomnieć ci o twojej własnej obietnicy dla mnie: opowiesz mi *wszystko*, co wiesz.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway pamięta. Odpowie na wszystko, o co zapytasz o Rodenburgu, chuanzhang.";
			link.l1 = "Zacznij gadać.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng' wypływał z portu Willemstad na północ, ku brzegom St. Christopher. Za pięć dni będzie tam galeon pod dowództwem Petera Stuyvesanta. Rozkaz Longweia był taki, by zatopić ten statek wraz z jego kapitanem na pokładzie.";
			link.l1 = "Boże na niebie! Rodenburg kazał ci zabić Stuyvesanta? To szaleństwo!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway mówi prawdę, kapitanie. To był rozkaz pana Rodenburga. Longway tego nie lubił, ale Longway nie kwestionuje rozkazów.";
			link.l1 = "Jakże to typowe dla Chińczyka. Jaką grę knuje twój mistrz?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Nie mój mistrz już, chuanzhang. Longway nie zamierza wracać do Mynheer Rodenburga. Rodenburg przejął władzę na Curacao. Mathias Beck był łatwą zdobyczą, autorytet Rodenburga i jego związki z komendantem wystarczyły, by wsadzić gubernatora do więzienia\nJedyną przeszkodą pozostał dyrektor Kompanii Zachodnioindyjskiej, Mynheer Stuyvesant. Gdy Stuyvesant zostanie wyeliminowany, Rodenburg będzie trzymał wszystkie urzędy władzy w holenderskich koloniach.";
			link.l1 = "Powiedz mi, Longway, co skłoniło szanowanego i potężnego człowieka jak Rodenburg do podjęcia tak radykalnych działań przeciwko swojej kompanii i republice? I nie mów mi, że to z powodu udaru słonecznego czy wybuchu szaleństwa.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway chciał dowiedzieć się osobiście od ciebie, chuanzhang. To ty przechwyciłeś statek pocztowy Kompanii i dostarczyłeś list do Rodenburga, prawda? Powód jest w tym liście.";
			link.l1 = "Teraz widzę... Wygląda na to, że w archiwum Johna Murdocka jest wiele cudownych rzeczy, które wystarczą, by przestraszyć Rodenburga na tyle, by wszcząć bunt przeciwko własnemu krajowi.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Chcesz wiedzieć coś jeszcze, chuanzhang?";
			link.l1 = "Tak. Co jeszcze zrobił Rodenburg?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Mynheer Rodenburg rozkazał cię zabić. Longway był w Caracas przed polowaniem na Stuyvesanta i spotkał się z Chuanzhangiem Jacobem, przekazując mu rozkazy.";
			link.l1 = "Kapitan Jacob van Berg?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "Jesteś dobrze poinformowany. Tak. Chuanzhang Jacob van Berg cię ściga, kapitanie. W końcu cię znajdzie. Nikt nie jest w stanie ukrywać się przed van Bergiem zbyt długo.";
			link.l1 = "Jeśli krwawi, mogę go zabić. Zajmę się van Bergiem i jego wychwalaną nawiedzoną łajbą.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Wiesz dużo, chuanzhang. Longway nie ma nic do dodania. Zapytaj, jeśli masz jeszcze jakieś pytania.";
			link.l1 = "Czy Stuyvesant będzie blisko wybrzeży St. Christopher?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Tak, chuanzhang. Będziesz mógł znaleźć jego galeon w pobliżu brzegów tej wyspy za około tydzień.";
			link.l1 = "Świetnie! Złapmy tego lisa w jego własną pułapkę... Nie mam więcej pytań. Wiem wszystko, co chciałem wiedzieć.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Jedna ostatnia rada, chuanzhang. Musisz zabrać 'Meifeng', jeśli chcesz zbliżyć się do galeonu, nie będąc zaatakowanym.";
			link.l1 = "Zrozumiano. Dzięki za informacje.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway wychodzi teraz. Żegnaj, chuanzhang.";
			link.l1 = "Pomyslności, mój orientalny druhu.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Longway słucha, chuanzhang.";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, wybieram się do starożytnego indiańskiego miasta Tayasal. Powiem wprost, to będzie naprawdę niebezpieczna wyprawa, a przy tym mistyczna - dotrzemy tam przez teleportujący idol. Czy... dołączysz do mnie?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, daj mi pełny raport o statku.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Chcę, abyś kupował pewne towary za każdym razem, gdy jesteśmy przy nabrzeżu.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Przybyłem na wasze rozporządzenie, kapitanie.";
				Link.l2 = "Muszę dać ci kilka rozkazów.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Słuchaj mojego rozkazu!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nic. Wolne!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway nigdy nie był kwatermistrzem, chuanzhang. Longway może ci powiedzieć, jak nawigować z Trynidadu do Hawany i ile to potrwa. Ale Longway nigdy nie liczy ładunków, sprzedaży i handlu.";
			Link.l1 = "Chyba masz rację. Szkoda byłoby zmarnować takiego wspaniałego nawigatora.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Longway nie handluje z gwailo, chuanzhang. Longway zawsze stał za sterem, nie w sklepie, gdzie stary haczyk nos targuje się do ostatniego grosza.";
			link.l1 = "Hm, masz rację. Pewnie przestraszyłbyś kupców.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Słucham.";
			Link.l1 = "Porozmawiajmy o abordażu.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Porozmawiajmy o twoim statku.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Chcę, abyś opuścił moją eskadrę na jakiś czas i sam szukał szczęścia.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Jak dotąd nic.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Jakie jest twoje życzenie.";
			Link.l1 = "Nie abordażuj wrogich statków. Dbaj o siebie i załogę.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Chcę, żebyś agresywnie abordował wrogie statki.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Jaka jest twoja wola.";
			Link.l1 = "Nie zamieniaj swojego statku na inny po wejściu na jego pokład. Jest zbyt wartościowy.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Kiedy abordujesz wrogie statki, możesz je przejąć dla siebie, jeśli są przyzwoite.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Tak jest.";
			Link.l1 = "Spokojnie.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "To będzie zrobione.";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Tak jest.";
			Link.l1 = "To zostanie zrobione.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Zostanie to zrobione.";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Rozkazy, chuanzhang?";
            Link.l1 = "Stójcie mocno!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Podążaj za mną i trzymaj się blisko!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Zmień rodzaj amunicji do swojej broni palnej.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Zmień rodzaj amunicji w swojej muszkiecie.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Zmień swoją priorytetową broń do walki.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Chcę, abyś strzelał do wrogów z określonej odległości, Lonway.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybieranie rodzaju amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
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

		case "SetMusketBullets":
			Dialog.Text = "Wybierz rodzaj amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Na początku walki użyjesz:";
			Link.l1 = "Szabla";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muszkiet";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Nastąpiła zmiana nastroju!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Zmiana nastroju!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "I jakaż to odległość by była? Pamiętaj, Panie Kapitanie, że z muszkietu nie trafisz w nic na odległość większą niż dwadzieścia metrów.";
			link.l1 = " ";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Co masz na myśli, Panie Kapitanie?";
				link.l1 = "Przepraszam, czasami zapominam, że nie jesteś dobry w żartach.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Zajmę pozycję, lecz strzelę do każdego wroga, który się zbliży. Czy tego chcesz?";
				link.l1 = "Tak, dokładnie, Lonway.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "To zbyt daleko, Panie Kapitanie. Możesz trafić w tłum, ale celowanie w pojedynczy cel - nie ma szans.";
				link.l1 = "Warto spróbować, ale dobrze.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Rozumiem, Panie Kapitanie.";
			link.l1 = "Znakomicie.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway śledzi cię od dawna. Longway będzie cię śledzić jak zawsze. Longway nie opuści swojego chuanzhang.";
			link.l1 = "Dziękuję, Longway! Cieszę się, że miałem rację co do ciebie.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Kiedy zaczniemy?";
			link.l1 = "Nieco później. Musimy się do tego przygotować.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
