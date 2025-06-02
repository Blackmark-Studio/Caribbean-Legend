void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Jakie dziewczyny, drogi?! Połowa garnizonu jest za tobą, a ty idziesz prosto do domu publicznego!","Znikaj już, dobrze? Połowa garnizonu jest za tobą!")+"","Każdy strażnik miasta szuka cię. Nie jestem głupcem, żeby świadczyć ci usługi w tym momencie...","Nie masz tu nic do roboty!"),LinkRandPhrase(""+GetSexPhrase("Tylko spróbuj dotknąć moje dziewczyny, a oskubię cię ze skóry na żywca!","Spływaj, ty szumowino!")+"","Brudny"+GetSexPhrase("","")+" morderco, opuść mój lokal, teraz! Strażnicy!!!","Nie boję się ciebie, "+GetSexPhrase("łotrze","gówniaro")+"! Wkrótce cie powieszą w naszym forcie, nie uciekniesz daleko..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm to nigdy nie jest dla mnie problem...","Nigdy mnie nie złapią."),RandPhraseSimple("Wystarczy się zamknąć, głupia wiedźmo.","Zamknij się, jeśli nie chcesz problemów..."));
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Oh, "+GetSexPhrase("młody człowieku","słodkie dziecko")+", dziś jesteśmy zamknięci.";
				link.l1 = "Zamknięte?";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "O mój Boże! Jak się tu dostałeś? Drogi kapitanie, proszę wyjdź - błagam cię! Nasz lokal jest obecnie zamknięty!";
				link.l1 = "Dobrze cię widzieć, drogi "+npchar.name+". Byłem na liście gości. Jednakże, w takich lokalach, nawet goście muszą płacić, więc... Proszę, nie utrudniaj mi tego, ale chcę zapłacić za pokój.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Słuchaj, Aurora, potrzebuję dziewczyny na noc. I chcę zabrać ją ze sobą do domu. Czy możesz to załatwić?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "Jesteś takim dostojnym mężczyzną. Co więcej, moje dziewczyny bardzo cię lubią. Chciałabym prosić cię o małą przysługę dla mojego lokalu.";
				link.l5 = "Jestem zaszczycony, to na pewno. W czym potrzebujesz mojej pomocy?";
				link.l5.go = "Badboy";
				link.l8 = "Przykro mi, ale teraz jestem zajęty.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Oh, wróciłeś! Czy załatwiłeś to "+pchar.GenQuest.Badboy.Brothel.Name+"aby zostawić moje dziewczyny w spokoju?";
					link.l5 = "Tak. On już tu więcej nie pokaże swojej twarzy.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "Kapitanie, czy mogę prosić Cię o przysługę?";
					link.l5 = "Dla ciebie, madame, wszystko co zechcesz! Jestem do twojej usługi!";
					link.l5.go = "Portugal";
					link.l8 = "Przykro mi, ale teraz jestem zajęty.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Czy rozmawiałeś z Hugo, kapitanie mój panie?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Ponadto, pani, oto twoje pieniądze. Wszystko poszło w najbardziej korzystny sposób...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Tak, przekazałem mu twoją prośbę.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "O mój Boże, popatrz na to! Charlie Prince, sławny korsarz! W ciele!";
				link.l1 = RandSwear()+"Witaj, Janette. Jestem tu w misji dla Marcusa Tyrex.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Czy jesteś gotowy na niezapomniane lecznicze zabiegi, mój dzielny korsarzu?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "Jestem! Charlie Prince nie marnuje słów jak marnuje pieniądze, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Prawie... Chyba zgubiłem sakiewkę w twoim lokalu... Wrócę z pieniędzmi!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Witaj w moim domu miłości. Nazywam się "+npchar.name+", a ja jestem właścicielem. "+GetSexPhrase("Co mogę dla ciebie zrobić, "+GetAddress_Form(NPChar)+"?","Szczerze mówiąc, jestem nieco zaskoczony, widząc cię tutaj, "+GetAddress_Form(NPChar)+", ale zapewniam cię, że świadczymy usługi nie tylko dla mężczyzn.")+"",TimeGreeting()+". Witam cię, "+GetSexPhrase("nieznajomy","młoda dama")+", do mojego skromnego lokalu. Pozwól, że się przedstawię, jestem "+NPChar.Name+" - właściciela tego azylu dla mężczyzn spragnionych kobiecego dotyku. "+GetSexPhrase("Co mogę dla ciebie zrobić?","Mimo że mamy też coś dla panien, czy dwie...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". Co mogę dla ciebie zrobić, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", Chcę spędzić trochę jakościowego czasu z jedną z twoich dziewczyn.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "Minęło trochę czasu od ostatniego razu, kiedy rozpieszczałem moich ludzi. Czy mogę złożyć hurtowe zamówienie dziewczyn dla moich chłopaków?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "Mam pytanie.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Słuchaj, "+npchar.name+", Szukam pierścionka gubernatora. Odpoczywał w waszym lokalu i prawdopodobnie tutaj go zgubił.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Spójrz, chciałbym wziąć najlepszą dziewczynę, jaką masz.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Nie ważne, już wychodzę.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("Co chcesz, przystojniaku?","Słucham cię, Kapitanie.");
				link.l1 = "Słuchaj, "+npchar.name+", znalazłem te papiery w prywatnym pokoju twojej instytucji ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Pozwól mi zobaczyć! Hmm... jakiś kapitan zgubił swoje dokumenty, tak? Myślę, że powinieneś zapytać o to naczelnika portu.";
				link.l1 = "Być może, być może...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Pozwól mi rzucić okiem! O! Sądząc po nazwisku, należą do mojego szanownego klienta i godnego obywatela naszego miasta. Mogę mu osobiście wręczyć te dokumenty.";
				link.l1 = "Prawdopodobnie, nie...";
				link.l1.go = "exit";
				link.l2 = "Doskonale! Zawsze chętnie pomogę dobrej osobie i godnemu lokalu.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+GetSexPhrase("Zawsze jesteśmy zadowoleni, że możemy obsłużyć klienta. Powiedz mi teraz, przystojniaku - czy już kogoś wybrałeś, czy to ci niezbyt przeszkadza?","Cóż, moje dziewczyny na pewno są w stanie... ci pomóc. Czy już kogoś wybrałeś, czy to ci niezbyt zależy?")+"";
					Link.l1 = ""+GetSexPhrase("Heh, potrzebuję tylko kurtyzany i potrzebuję jej natychmiast. Nie obchodzi mnie, która, wszystkie twoje dziewczyny wyglądają na mnie dobrze...","Każdy będzie w porządku, jeśli zna swoje obowiązki, oczywiście...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Tak, jest jeden, "+GetSexPhrase("Kto skradł moje serce...","ona byłaby najmiłszą...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Nie mam dla ciebie dziś wolnych dziewczyń, mamy już zbyt wielu klientów. Przyjdź jutro, a nie pożałujesz!";
					Link.l1 = "Szkoda, dopiero zaczynałem się bawić.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Już zapłaciłeś za dziewczynę. Nie rozpraszaj mnie, proszę.";
				Link.l1 = "Dobrze, już idę.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Nie mam teraz żadnych wolnych dziewcząt, musisz sprawdzić za kilka dni.";
				Link.l1 = "Dobrze, jak mówisz.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("Cóż, rumaku, to doskonałe!","Mam ich wszystkich zręcznych, możesz być pewien.")+"Mogę zaoferować piękną dziewczynę o imieniu "+GetFullName(sld)+", jest wolna teraz.\nO, co to ukrywasz tak skromnie?! Czy to najwyższe odznaczenie we Francji? Plotki głoszą, że nosiciele tego znaku są legendarni nie tylko na polu bitwy... No wiesz, co mam na myśli, mój filibuście... Poza tym, każdy uznałby za zaszczyt dotknąć twojego 'Orderu', więc dzisiaj odpoczywasz na koszt mojej instytucji. Odmowy nie są akceptowane, przystojniaku.";
					Link.l1 = "Oczywiście, że się zgadzam, jakie mogą być pytania?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("Cóż, doskonale, mój rumaku!","Wszyscy są bardzo uzdolnieni w tym, co robią, nie ma wątpliwości.")+"Mogę ci zaproponować bardzo miłą dziewczynę, nazywa się "+GetFullName(sld)+", a ona jest teraz wolna. Ta przyjemność będzie cię kosztować "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Zgadzasz się?";
				Link.l1 = "Nie. Chyba nie. To zbyt drogie...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Oczywiście, jak mogłem odmówić?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "O cholera, nie mam przy sobie tyle pieniędzy...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Dobrze, "+GetSexPhrase("przystojny","piękny")+". "+sld.name+" będzie na ciebie czekać w prywatnym pokoju na drugim piętrze.";
				Link.l1 = ""+GetSexPhrase("Dobrze, idę, więc","Dobrze, idę tam, wtedy")+"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "Oh, widzisz, problem polega na tym, że "+sld.name+" nie jest tanią dziewczyną, jej cena to "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". I widzę, że na razie po prostu nie stać cię na nią. Wróć, kiedy będziesz bogaty"+GetSexPhrase(", drogi","")+"...";
				Link.l1 = "To moje szczęście...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Zawsze cieszę się, kiedy dziewczyny i klienci zaczynają do siebie ciepło czuć... Powiedz mi jej imię.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm... chyba się mylisz. Nie ma takiej dziewczyny w moim lokalu. Być może pomyliłeś jej imię.";
				Link.l1 = "Hmm... ale właśnie rozmawiałem z nią.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Być może. Lepiej zapytać jej ponownie o imię, tak na wszelki wypadek. Porozmawiamy o tym później.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", mówisz o niej?";
				Link.l1 = "Tak, o niej.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "Nie, to nie ona.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "W takim razie, może powinieneś powiedzieć mi jej imię jeszcze raz, a może zrozumiem, o kim mówisz.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Być może. Lepiej byłoby zapytać o jej imię jeszcze raz, tylko na wszelki wypadek. Porozmawiamy o tym później.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm... Chcesz pomóc swoim chłopakom 'rozładować parę'? Widzisz, mój lokal to renomowane miejsce, a ja mam najlepsze dziewczyny w okolicy. Ale znam kilka portowych dziewek, które z przyjemnością zaspokoją wszystkich twoich żeglarzy. To będzie cię kosztować "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "Dobrze, zgadzam się.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Chyba sobie bez tego poradzą...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "To nie moja sprawa, ale myślę, że najpierw powinieneś zarobić wystarczająco dużo pieniędzy, aby zatrudnić załogę, a dopiero potem martwić się o jej ducha.";
			    link.l1 = "Prawdopodobnie masz rację...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Drogi, co ty właśnie robisz?! A wyglądałeś na przyzwoitego kapitana... Tym razem nie 'odlecisz', przystojniaku. Strażnicy obetną ci skrzydła...";
			link.l1 = "Zamknij się, stara wiedźmo.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Nie znalazłem żadnego pierścienia.";
			link.l1 = "A co z twoimi dziewczynami?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "Oni też nie. Jeśli klient zapomni lub zgubi coś, moje dziewczyny przynoszą mi to. Ale nikt nie przyniósł mi pierścienia gubernatora.";
			link.l1 = "Rozumiem... Ale czy mogli zdecydować się zatrzymać to dla siebie?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Mało prawdopodobne. Dziewczęta mogą zachować prezenty od klientów, ale to wszystko.";
			link.l1 = "Rozumiem. No, dzięki, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "O, tutaj jesteś...";
			link.l1 = "Tu jestem, moja pani!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! Mój bohaterze, widzę, że nie zmarnowałeś czasu na dole!";
				link.l1 = "Mam nadzieję, że wybaczysz mi tę słabość, moja królowo?";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Lepiej opuść ten lokal!","Wszyscy strażnicy w mieście szukają cię! Lepiej dla ciebie odejść...","Narobiłeś bałaganu i teraz się tu pokazujesz?! Nie, nie tym razem..."),LinkRandPhrase("Znikaj!","Brudny morderco, wynoś się stąd! Strażnicy!","Nie boję się ciebie,"+GetSexPhrase("łotr","szczur")+"! Wkrótce zostaniesz powieszony w naszym forcie, nie uciekniesz daleko..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm nigdy dla mnie nie jest problemem...","Oni nigdy mnie nie złapią."),RandPhraseSimple("Heh, jaka głupia suka jesteś...","Zamknij swoje usta, kurwo, albo zamknę je czymś innym..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Witaj, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", hi-hi..")+". Musisz zobaczyć panią i wypełnić zamówienie.","Znowu ty? Proszę, porozmawiaj z karczmarką. Jest w swoim biurze.","Spójrz, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", Mam nadzieję, że jesteś tak uparty w innych sprawach, jak w rozmowaniu... Znowu","Ponownie")+"Proszę cię, abyś odwiedził właściciela tego lokalu.","Oh, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", czyż nie jesteś uparty!",", Hee-hee... Jesteś uparty, nieprawdaż?")+"Musisz zobaczyć panią i wypełnić zamówienie.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Dobrze, "+GetSexPhrase("piękno, ","")+"Mam to"+GetSexPhrase("","")+".","Tak, jasne...",""+GetSexPhrase("Nie miej wątpliwości, moja piękna, jestem uparty i silny jak byk!","Tak, tak...")+"",""+GetSexPhrase("O cholera, musiałem coś przegapić... Przykro mi, droga.","Dobrze, w porządku.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "A gdzie ona jest?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("Och, piękność, założę się, że mógłbym utonąć w tych twoich oczach...","Wyglądasz pięknie, kochanie!")+"",""+GetSexPhrase("Wiesz, nigdy wcześniej nie spotkałem tak pięknej kobiety!","Wiesz, nigdy wcześniej nie spotkałem tak miłej laski!")+"",""+GetSexPhrase("Kochanie, wyglądasz pięknie.","Cholera, tak mi się nudziło z tymi wszystkimi wieśniakami... A ty jesteś taki uroczy!")+"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Słuchaj, "+GetSexPhrase("piękno","kochanie")+", nie znalazłeś przypadkiem tutaj obrączki ślubnej? Wygląda na to, że jeden mężczyzna ją zgubił...","Kochanie, widziałeś może obrączkę ślubną czy coś w tym stylu?","Słuchaj, "+GetSexPhrase("mój kotek","kochanie")+", nie widziałeś tu gdzieś obrączki ślubnej?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Hej, kochanie. Marcus Tyrex mnie wysłał, spójrz na ten bursztynowy naszyjnik...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "Ona jest w swoim biurze. Możesz tam dotrzeć stąd przez drzwi naprzeciwko wyjścia na ulicę, lub z ulicy po drugiej stronie domu. Nazywa się "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "Rozumiem, "+GetSexPhrase("kochanie","drogusieńka")+", dzięki.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("O mój Boże, tak miło słyszeć takie rzeczy! Hej, jestem teraz wolny, więc jeśli mnie wybierzesz, nie pożałujesz...","Naprawdę tak myślisz? Wiesz, to takie urocze... Słuchaj, jestem teraz wolna, więc możesz mnie wybrać."+GetSexPhrase("Obiecuję ci morze miłości i ocean pieszczot...","")+"",""+GetSexPhrase("Czy tak myślisz? Och, naprawdę jestem zaszczycony. Wiesz, rzadko słyszę takie komplementy...","Och, dziewczyno... gdybyś tylko wiedziała, jak mi doskwiera ciągłe obcowanie z wieśniakami...")+"Hej, posłuchaj, teraz jestem wolny, więc możesz wybrać mnie, aby cię uszczęśliwić. Nie zawiodę cię, obiecuję...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "Mój drogi, to właśnie miałem zamiar zrobić! Jak szczęśliwie, że twoja gospodyni już zorganizowała prywatne spotkanie ze mną na górze. Chcesz dołączyć?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "No cóż, wybieram cię, więc!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("Nie, to był tylko komplement dla miłej damy","To był tylko komplement")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("Wiesz co mówię, kochanie? Nie potrzebuję tych tanich rozmów. Prowadź interesy albo wychodź!","To wszystko, czego potrzebowałem! Komplementy od kobiet!")+"",""+GetSexPhrase("Czy jesteś jednym z tych, którzy myślą, że kobiety kochają uszami? Cóż, drogi, to po prostu nieprawda. Jeśli mnie chcesz, to zapłać madame i oszczędź mi swoich pustych słów.","Dziewczyno, nie marnuj się na puste rozmowy. Jeśli mówisz poważnie - to zapłać...")+"",""+GetSexPhrase("O, kolejny miłośnik zmysłowości... Po prostu zapłać, a będę twój. To takie proste, bez całego tego delikatnego nonsensu!","Co u ciebie, kochanie? Jeśli chcesz oddać się przyjemnościom, to po prostu zapłać i przestań z tymi bzdurami!")+"");
				link.l1 = "O, co za chwyt!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" kończy wszystkie formalności w swoim gabinecie. Idź do niej"+GetSexPhrase(", mój bohaterze,","")+" i powiedz moje imię - "+npchar.name+". Będę na ciebie czekać...";
			Link.l1 = "Widzę, kochanie, wrócę wkrótce...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("Już zapłaciłeś.","Powiedziałem ci 'idź na górę'.","Do góry, młody człowieku.","Niektórzy ludzie myślą tak wolno...","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tak, wiem.","Pamiętam.","Och, nie powtarzaj się, pamiętam.","Hmm, co masz na myśli?",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Po prostu nie do końca cię rozumiem."+GetSexPhrase(" Najpierw robisz komplementy, a potem wycofujesz swoje słowa. Co za dziwaczny typ...","")+"","Znowu komplementy?","Gospodyni jest w swoim biurze. Zrozumiałeś?","Nie powinniśmy obrażać naszych klientów, ale ty naprawdę o to prosisz"+GetSexPhrase("","")+"...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("To po prostu się stało, jak się stało...","W porządku, zrobię to.","Tak, mam to.","Przepraszam, moja miłości.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Dzięki za komplement. Jeśli chcesz mnie zabrać, po prostu idź i zobacz panią. Biznes jak zwykle.";
				Link.l1 = "Widzę.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Drogi, już wszystko obgadaliśmy. ","")+"Nie kaź mi czekać zbyt długo...",""+GetSexPhrase("Hmm... Słuchaj, drogi, ja","Ja")+" uważam twoje słowa za bardzo miłe i wszystko, ale czy mógłbyś przejść do rzeczy...","Być może, porozmawiasz o tym z madame, prawda?","Hm... Nawet nie wiem, co powiedzieć...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Nigdy bym tego nie zrobił, zaczekaj na mnie!","Z pewnością!","Oczywiście, jak mówisz!","Już biegnę, aby zobaczyć twoją madame...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Czekałem na ciebie, ale nie przyszedłeś po mnie... Nie mogę powiedzieć, że mi się to podobało...";
					Link.l1 = "Widzisz, to po prostu zdarzyło się tak, jak się zdarzyło...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "O, to znowu ty, moj "+GetSexPhrase("chwalebny korsarz","ładna dziewczyna")+"! Jeśli chcesz mnie znowu, przyjdź do pani, nie będziesz zawiedziony..."+GetSexPhrase(" Mimochodem, rozpoznałam cię, drogi, ale mówią nam, że musimy rozmawiać ze wszystkimi klientami na równi, nie powinno być ulubieńca, przepraszam za to...","")+"";
				Link.l1 = "Nie martw się, kochanie. Poczekaj na mnie tylko chwilę, "+GetSexPhrase("uroczysko","uroczysko")+", a wkrótce spotkamy się na prywatce znowu.";
				Link.l1.go = "exit";
				Link.l2 = "To bardzo miłe, że mnie pamiętasz, ale nie mogę spędzić tej nocy z tobą, przepraszam.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Więc,"+GetSexPhrase(" drogi przyjacielu,","")+"lepiej zajmij się biznesem. Będzie to bardziej użyteczne niż nic nie robienie.",""+GetSexPhrase("Hmm, dlaczego jesteś ","Dlaczego jesteś")+" mówiąc ciągle to samo?","Hej, czy to nie wystarczy?!","Hm, co za niespodzianka, nic nowego"+GetSexPhrase(", znowu te głupie próby uwodzenia! Jeśli chcesz ze mną uprawiać seks, idź i zobacz madame, ty ptaszkopysku!","...")+"","blokada",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Tak, słyszałem"+GetSexPhrase("","")+" ty...","Cóż, tak to się okazuje...","Hmm, może to wystarczy, a może nie...","Uważaj na swoje słowa"+GetSexPhrase(", koza","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ohh, to znowu ty! "+GetSexPhrase("I znowu te same głupie komplementy. Nic się nigdy nie zmienia w tym świecie... Jeśli ","Tylko przypomnienie: jeśli ")+"chcesz"+GetSexPhrase("baw się dobrze","baw się dobrze")+" ze mną, zapłać właścicielowi miejsca. Twoje słowa nic mnie nie obchodzą.";
				Link.l1 = "To nie jest wielkim zaskoczeniem...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "Nie mogę powiedzieć, że to mnie ucieszyło... Szkoda.";
			Link.l1 = "Przykro mi...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, w końcu przybyłeś! Świetnie! Możemy rozmawiać swobodnie, nikt nas nie słucha...";
				Link.l1 = "Czyli to Hiszpan dał ci ten bursztyn?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Bardzo się cieszę, że cię widzę. "+GetSexPhrase("No więc, co zamierzamy robić dalej?","Co powiesz na to, żebyśmy się dobrze bawili?")+"","Nie bądź nieśmiały"+GetSexPhrase(", poczuj się jak w domu przynajmniej przez dwie godziny.",". Będę mógł cię zabawić, nie miej wątpliwości.")+"");
					Link.l1 = RandPhraseSimple("Nie sądzę, żeby to było nudne...",""+GetSexPhrase("Spędźmy trochę dobrego czasu, kochanie!","Nie marnujmy czasu!")+"");
				break;
				case "1":
					dialog.text = "O, to znowu ty, moj "+GetSexPhrase("chwała korsarzu! Obiecałem ci coś i jestem gotów dotrzymać słowa","ładna dziewczyna! Nigdy nie zapomnisz następnych dwóch godzin")+"...";
					Link.l1 = "Teraz to brzmi kusząco...";	
				break;
				case "2":
					dialog.text = "Ohh, oto jesteś, w końcu. Nie marnujmy czasu!";
					Link.l1 = ""+GetSexPhrase("Nie róbmy tego, cipa...","Teraz pokaż mi co potrafisz...")+"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Kapitanie, dlaczego jesteś taki cichy?";
				link.l1 = LinkRandPhrase("Cóż, to ja.","Porozmawiamy następnym razem.",RandPhraseSimple("Nie płacę ci za rozmowę.","Ale ty, "+GetSexPhrase("piękno","drogusieńki")+", nie byli tak cicho cały ten czas."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("Byłeś po prostu wspaniały, prawie straciłem zmysły! To bardzo rzadka okazja, kiedy kobieta jest zarówno piękna, jak i gorąca","Ohh, na pewno wiesz, jak zadowolić kobietę... Jestem taka podekscytowana.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Czy ci się podobało?","No więc, co możesz powiedzieć? Czy wszystko było w porządku?","Więc,"+GetSexPhrase(" korsarz, jest, wszystko","wszystko")+" dobrze?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("Oczywiście, wszystko jest w porządku","Na pewno znasz swoje obowiązki")+".",""+GetSexPhrase("Wszystko w porządku, kochanie","Wiesz, byłem całkiem zadowolony")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("Czy dotrzymałem mojej obietnicy?","No,"+GetSexPhrase(" czy ci się podobałem",", czy ci się podobało")+"?","Mam nadzieję, "+GetSexPhrase("byłeś zadowolony, bo ja jestem ba-a-ardzo zadowolony","byłeś zadowolony, bo dałem z siebie wszystko")+"...");
						Link.l1 = RandPhraseSimple("Tak, bardzo mi się podobało.",""+GetSexPhrase("Spędziliśmy wspaniały czas, byłeś przepiękny!","Wszystko było po prostu wspaniałe!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("No cóż, to wszystko, musisz iść.","Twój czas się skończył,"+GetSexPhrase(" Kapitan,","")+".");
						Link.l1 = RandPhraseSimple("Tak, do zobaczenia...","Do widzenia i dziękuję...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "No więc, jak ci się tu podobało?";
				link.l1 = "Powiedz mi piękności, czy nie widziałaś nigdzie walizki?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Zajrzyj tu czasami...","Do widzenia. Będziemy na ciebie czekać w każdej chwili...","Będziemy zadowoleni, gdy znowu tu wrócisz...");
				Link.l1 = "W porządku...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "Czy to była ta brązowa skrzynia z uchem?";
			link.l1 = "Tak, coś w tym rodzaju...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Ponieważ właściciel tego skrzyni nie pojawił się, pani zabrała go do swojego boudoir.";
			link.l1 = "Dzięki, kochanie. Do widzenia.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Wtedy wpadnij kiedykolwiek, zawsze będę się cieszyć na twój widok. Jesteś taki "+GetSexPhrase("łagodny, nie jak tamci inni","łagodny, nie jak te wieśniaki")+" ani cześć, ani do widzenia, a często nawet próbują zaszkodzić...";
			link.l1 = "Co masz na myśli mówiąc to?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Tuż przed tobą był sierżant sztabowy. Zazwyczaj nie odwiedza nas, ale tym razem jakiś diabeł go tu przyprowadził. Co więcej, wybrał mnie... Jęczał, będąc nade mną przez kilka minut, a potem nazwał mnie niewykwalifikowanym i pognal do jakiejś zatoki. Zmykał tak szybko, że prawie zostawił tam spodnie, ha-ha-ha...";
			link.l1 = "Czy ty nie wiesz, "+GetSexPhrase("piękność","kochanie")+", kim naprawdę są mężczyźni? Powiedział swojej żonie, że pójdzie do domu publicznego na 'inspekcję', potem powiedział swojej kochance, że spieszy się do swojej żony, ale jedyną rzeczą, której zawsze chciał, było patrolowanie tej zatoki. "+GetSexPhrase("He-he-ah!..","Ha-ha-ha!")+"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("Nie, kochanie, przepraszam, ale nie. Chętnie bym ci pomógł, ale nie mogę.","Nie, "+GetSexPhrase("przystojny","młoda dama")+", nie widziałem żadnego pierścionka...","Przykro mi, ale nie. Nie widziałem żadnego pierścionka.");
				link.l1 = "Szkoda... Cóż, dziękuję mimo wszystko.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Czy masz na myśli pierścień gubernatora?";
					link.l1 = "Dokładnie, kochanie!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("Nie, kochanie, przepraszam, ale nie. Chciałbym ci pomóc - ale nie mogę.","Nie, "+GetSexPhrase("przystojny","młoda dama")+", nie widziałem żadnego pierścienia...","Przykro mi, ale nie. Nie widziałem żadnego pierścienia.");
					link.l1 = "Szkoda... No cóż, dziękuję mimo wszystko.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Przykro mi, ale pierścień został mi podarowany jako prezent, więc nie jestem zobowiązany go zwrócić.";
			link.l1 = "Prezent?! A kto ci go dał?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "Oczywiście sam gubernator!";
			link.l1 = "Ale on był... powiedzmy, nietrzeźwy. Niczego nie pamięta.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "I co ja mam z tym wspólnego? Jeśli był pijany, to jest jego problem, nie mój!";
			link.l1 = "Czy naprawdę musisz się z nim kłócić? To jest pierścionek ślubny, a ty o tym wiesz... Oddaj go po prostu, taka drobnostka nie jest warta żadnych kłopotów.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Cóż, oddam pierścień, ale zapłacisz mi pięć tysięcy peso.";
				link.l1 = "Dobrze, weź swoje pieniądze i daj mi pierścionek.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Och, dobrze. Niech on to weźmie!";
				link.l1 = "Na pewno, kochanie!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Proszę bardzo...";
			link.l1 = "Dobrze, więc. Dzięki za pomoc, kochanie.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Widzisz, mamy jednego nieprzyjemnego klienta - "+pchar.GenQuest.Badboy.Brothel.Name+". I naprawdę denerwuje nas za każdym razem, kiedy tu przychodzi! Najpierw upija się w karczmie, potem przychodzi tutaj, bierze dziewczynę i robi gwałtowny hałas\nI najgorsze w tym wszystkim jest to, że jest szlachcicem! Jest dalekim krewnym naszego gubernatora, więc jesteśmy zmuszeni znosić wszystkie jego wybryki. Może mógłbyś sprawić, że ten młody bezczelny człowiek... cóż... trochę się uspokoi... tak, żeby przestał odwiedzać mój lokal?";
			link.l1 = "Krewny gubernatora, mówisz? Hmmm... Wolałbym nie wdawać się w konfrontację z władzami. Naprawdę mi przykro.";
			link.l1.go = "exit";
			link.l2 = "Myslę, że mogę to załatwić. Powiedz mi, gdzie mogę znaleźć tego łajdaka?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Zazwyczaj o tej porze jest już w karczmie. Upija się tam, a potem przychodzi do nas w odwiedziny.";
			link.l1 = "Rozumiem. Cóż, prawdopodobnie spotkam go tam.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "Och, jesteś prawdziwym mężczyzną, prawda? Zawsze wiedziałam, że mogę na tobie polegać..";
			link.l1 = "Zawsze chętnie pomogę takiej miłej damie i jej... podopiecznym.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "Nie jesteś tylko odważny, ale również bardzo szarmancki. Chciałabym podziękować Ci w szczególny sposób - tak, jak tylko kobieta może podziękować mężczyźnie. Nigdy tego nie zapomnisz, obiecuję. Chodź na górę, odważny żeglarzu...";
			link.l1 = "..., przyjacielu.";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "Jest jeden człowiek i dłużny mi jest pewną sumę pieniędzy... Nie wiem jak to powiedzieć...";
			link.l1 = "Bez słów! Znajdę go i wstrząsnę nim do ostatniego peso tylko za jeden rzut oka na twoje bezdennne oczy! Powiedz mi tylko jego imię!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Nie, nie, nie zrozumiałeś mnie dobrze, Kapitanie! Ten człowiek... nie rób mu krzywdy. Przypomnij mu tylko o jego długach. Nazywa się Hugo Avendell, a myślę, że znajdziesz go tam, gdzie sprzedają bardzo tanie gorzałki. Na miłość boską, nie stosuj wobec niego przemocy!\nPo prostu powiedz... przypomnij mu, że obiecał zapłacić. Nie chcę kontaktować się z gwardią, ale mam przyjaciół oficerów, więc powiedz mu, że czekam i z całym szacunkiem dla niego, będę zmuszony podjąć działania nie później niż jutro. Przypomnij mu po prostu o obietnicy.";
			link.l1 = "Twoje słowo jest moim prawem, madame. Z przyjemnością spełnię twoją prośbę.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			//создаем Хьюго
			sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
			sld.name = "Hugo";
			sld.lastname = "Avendell";
			sld.dialog.FileName = "Quest\Portugal_dialog.c";
			sld.dialog.currentnode = "Avendel_tavern";
			sld.greeting = "avendel_1";
			sld.rank = 12;
			LAi_SetHP(sld, 80, 80);
			SetSelfSkill(sld, 10, 12, 10, 10, 70);
			SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
			SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			TakeNItems(sld, "bullet", 10);
			AddItems(sld, "gunpowder", 10);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			LAi_SetImmortal(sld, true);
			LAi_SetSitType(sld);
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "Dziękuję, kapitanie. Mam nadzieję, że okaże należytą roztropność.";
			link.l1 = "Jestem pewien tego, pani. Teraz pozwól mi odejść.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "O nie! Nie mów mi, że zrobiłeś mu coś strasznego... Nie miał pieniędzy, a ja o tym wiedziałem! Wyrastaliśmy w tym samym małym miasteczku, nigdy bym nie zwrócił się do straży! Chciałem go tylko trochę przestraszyć... aby go wstrząsnąć zanim utonie w butelce!";
			link.l1 = "Hmm... Mimo wszystko, oto twoje pieniądze. I nie martw się o Hugo, on jest w porządku... Przynajmniej będzie, jeśli wytrzeźwieje.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Oh, Kapitanie, nie rozumiesz! Był jednym z... cóż, wiesz, nazywają ich łowcami nagród - najemnikami, tropią piratów i rabusiów i eliminują ich. Ale, nie był najszczęśliwszym, delikatnie mówiąc\nNiedawno w końcu przeholował i stracił załogę i statek, od tamtej pory tonie na dnie kufła, dzień po dniu. Ja, ze względu na stare czasy, pozwalam mu tu czasem przychodzić. Jest taki... taki żałosny teraz. Był najprzystojniejszym mężczyzną w naszym mieście na wybrzeżu La Manche, a teraz na niego patrz\nWiem, że obiecał ci coś, a ty płaciłeś z własnej kieszeni! Oddam ci te pieniądze, tylko nie rób mu krzywdy, błagam cię, kapitanie!";
			link.l1 = "Dobrze, dobrze, madame, rozumiem. Zatrzymaj te pieniądze, są twoje. Co do twojego przyjaciela, obiecuję, że mu nie zaszkodzę. A teraz pozwól mi odejść, mam trochę pracy do wykonania. Zresztą, cieszyłem się, że mogłem pomóc tak pięknej damie.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Cicho, mów cicho... Idź poproś Madame Lolita o spotkanie ze mną. Potem przyjdź na górę, tam będziemy mogli rozmawiać swobodnie. I ani słówka do tego czasu... Hej, marynarzu, zapłać Madame zanim mnie dotkniesz! (chichot)";
			link.l1 = "W drodze, kochanie...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Nie, nie ja. Opowiem ci całą historię, tylko mnie nie przerywaj.";
			link.l1 = "Jestem cały uchem!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Dobrze zatem. Mniej więcej tydzień temu, do Santo Domingo przybył wojskowy okręt. Był uszkodzony, czy to przez burzę, czy przez walkę, więc naprawy rozpoczęły się od razu, a załoga przeniosła się do fortu. Jego kapitan natomiast spędzał cały swój wolny czas właśnie tutaj. Przez dwa dni bez przerwy pił i relaksował się w towarzystwie jednej z naszych dziewcząt. To ona dostała klejnot, i to nie jeden. Chwaliła się nim na prawo i lewo - Lolita pozwala nam zatrzymywać prezenty od klientów. \nGłupia dziewczyna nawet nie wiedziała, jaką prawdziwą wartość ma ten prezent, podczas gdy ja od razu go oceniłem. Kiedy opowiedziała mi, jak pijany kapitan chwalił się górą pełną bursztynów, natychmiast wysłałem list do Tyrexa...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Do następnego przyjazdu kapitana wszystko zaaranżowałem tak, że jego ulubiona dziewczyna była zajęta innym klientem, a 'pracę' dostałem dla siebie. Próbowałem wydobyć od niego koordynaty, niestety, na próżno. On tylko chwalił się, jak stanie się bogaty jak Krassus i wróci do Starego Świata\nAni słowa o lokalizacji. Jedyne, co udało mi się dowiedzieć, to że jego statek został naprawiony i miał płynąć do Hawany, gdzie spróbuje zorganizować misję w odpowiednim kierunku. W końcu to nie on jest właścicielem statku.";
			link.l1 = "Czyli, jest teraz w Hawanie?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Odpłynął dwa dni temu o świcie. Ty jesteś tutaj marynarzem, ty liczysz.";
			link.l1 = "Imię kapitana, typ jego statku i nazwa, cokolwiek?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "Co, uważasz mnie za głupca? Jego imię to Esberdo Cabanas, kapitan Cantavro. Myślę, że marynarze nazywali to szkunerem.";
			link.l1 = "I to wszystko, co wiesz?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "Co jeszcze chcesz? Jestem pewien, że mógłbyś go dogonić przed Hawaną. Nie marnuj jednak czasu, nie sądzę, aby zrobił długą przerwę przed opuszczeniem Kuby w kierunku swojego schowka, a potem to już przegrana sprawa. Z drugiej strony, moglibyście zatrzymać się na godzinę czy dwie, przecież za to zapłaciliście.";
			link.l1 = "Dobrze powiedziane, kochanie. Dwie godziny nie zrobią wielkiej różnicy...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Inny czas, drogi. Pomyśl o przerwie na lunch. Idź do kościoła, czy coś w tym stylu.";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "O-oj... Co za szkoda. A myślałam, że jesteś tu na wakacjach. Moje dziewczyny tak tęsknią za odważnymi korsarzami. Bardzo dobrze, mów więc, jaka jest zadanie?..";
			link.l1 = "Marcus zlecił mi zorganizować diabelską imprezę w twoim lokalu na dwa dni, wypić całe wino i poderwać każdą dziewczynę. Kiedy zaczynamy?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie Prince, twój humor jest tak ostry jak twój szabla! Prawie mnie zdenerwowałeś... Dziewczyny! Mamy gościa, specjalnego gościa! Przynieście wino i jedzenie!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Zwołaj tu każdą ładną dziewczynę! Będziemy odpoczywać i bawić się! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Zaczekaj chwilę, Janette. Muszę zdobyć złoto z mojego statku dla ciebie i twoich dam. Do zobaczenia za minutę!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "Chciałabym, aby wszyscy nasi klienci byli tak słodcy, przystojni i hojni jak ty... Damy ci doskonały relaks. Dziewczyny!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "O, widzę, że mamy tu smakosza, hi hi ... No dobrze, mam taką dziewczynę. Ale ona nie jest tania: "+makeint(pchar.GenQuest.NightAdventure_money)+" pesos."; 
			link.l1 = "Umowa.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "To świetnie, drogi. Kapłanka Miłości będzie na ciebie czekać na górze. Ufaj mi, nie pożałujesz."; 
			link.l1 = "Już nie.";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "Dla ciebie i m'lorda Agueybana? Oczywiście. To będzie dziesięć tysięcy, kapitanie.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Poczekaj, nie tak!.. Cholera! Cóż, tutaj jest zapłata.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Czy mogę dostać pożyczkę?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Ciesz się pobytem, kapitanie. Proszę wrócić ponownie, gdy jesteśmy otwarci. Nasz lokal oferuje wszelkiego rodzaju rozrywkę dla szlachetnych mężczyzn i kobiet.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Pani "+npchar.name+", czy przynajmniej możesz wyjaśnić, co tu się dzieje? Czy gubernator jest nawet świadomy, że przez miesiąc byłeś pod opieką tubylca? Żadna osada nie przetrwa zamknięcia domu publicznego na dzień, mogę ci to powiedzieć!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "Pokój jest twój, kapitanie. Teraz, jeśli pozwolisz mi.";
			link.l1 = "Urocze. Do widzenia, pani.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Dlaczego, Panie, dlaczego? Wynoś się stąd! Idź sobie, idź sobie, już nie mogę tego znieść! Drań!";
			link.l1 = "To poszło dobrze.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... Zazwyczaj tego nie robię... ale dla ciebie jestem gotów zaryzykować. To twój szczęśliwy dzień, Kapitanie!";
			link.l1 = "Chodźmy!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "Jestem na ciebie zły, Kapitanie... Ale okażę ci łaskę, jeśli na nią ciężko zapracujesz.";
			link.l1 = "O, tak zrobię. Czy otworzymy wino?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "Dopóki ten przeklęty de Alamida nie odejdzie. Przeklęty święty człowiek...";
			link.l1 = "Ale może...";
			link.l1.go = "SantaMisericordia_2";
		break;
		
		case "SantaMisericordia_2":
			dialog.text = "Bez może. Co jeśli on wejdzie tutaj teraz? Wszyscy na zewnątrz.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
		break;
		//<-- прибыла инспекция на Святом Милосердии
		
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
