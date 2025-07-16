// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Mój synu","Moja córko")+"niestety, nie mogę dać ci schronienia. Uciekaj!","Straż miejska przeszukuje miasto, szukając cię, "+GetSexPhrase("mój synu","moja córko")+". Drzwi mojego kościoła są zawsze otwarte dla cierpiących, lecz nie mogę dać ci schronienia...","Здравствуйте, святой отец."+GetSexPhrase("Mój synu","Moja córko")+" , musisz uciekać! Nie zwlekaj, błagam cię!"),LinkRandPhrase("Co robisz w kościele, upadła duszo? Żądam, abyś natychmiast opuścił to miejsce, zanim żołnierze cię tu znajdą i dokonają masakry!","Opuść tą świątynię natychmiast, szyderco! Nigdy nie będę chronił takiego łotra jak ty!","Opuść świątynię naszego Pana natychmiast! Nie potrzebujemy tu morderców!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Oj, no dalej, ojcze...","Nie potrzebuję twojej pomocy i tak..."),LinkRandPhrase("Nie stawaj mi na drodze, Ojcze...","Odejdę, nie martw się...","Ojcze, przestań robić zamieszanie - naprawdę nie mam na to czasu"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...będą płonąć w ognistym piekle na wieki! Nigdy nie ujrzą...";
					link.l1 = RandPhraseSimple("Ahem! Czy przeszkadzam, ojcze?","To jest przemowa!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mój synu","Moja córka")+" , cieszę się, że znów cię widzę!";
					link.l1 = "I cieszę się, że widzę cię w dobrym zdrowiu, ojcze "+NPChar.name+"...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mój synu","Moja córka")+"Jestem rad widzieć cię ponownie w dobrym zdrowiu i w dobrym nastroju. Pan musiał nam pomóc w naszej sprawie, prawda?";
					link.l1 = "Tak, "+RandPhraseSimple("padre","święty Ojcze")+"Choć nie zawsze wiatr pomyślny wiał w moje żagle, choć spędziłem trochę więcej czasu, sił i pieniędzy - twoja misja jest wykonana.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Witaj w naszym świętym przybytku, "+GetSexPhrase("mój synu","moja córka")+".";
				link.l1 = "Witaj, święty Ojcze.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "Witaj, Ellen, moje dziecko.";
					link.l1 = "I Tobie, Ojcze.";
				}
				link.l1.go = "node_3";
				Link.l2 = "Nie jesteś moim ojcem i nigdy więcej tak się do mnie nie zwracaj.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Odejdź z świątyni Pana, bluźnierco! Nie mamy o czym rozmawiać!";
				Link.l1 = "Ja nawet nie chciałem.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "O, bluźnierco! Odejdź! Nie waż się bezcześcić świątyni naszego Pana swoją obecnością!";
			link.l1 = "Nie miałem nawet zamiaru tu zostawać.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Cieszę się, że pomimo twoich... zajęć z Janem, nie zapominasz o naszym Panu i Jego domu. Jak mogę ci pomóc?";
			}
			else
			{
				dialog.text = "Niech Pan błogosławi tobie i twoim sprawom... Czy przyszedłeś do mnie z jakiegoś szczególnego powodu?";
			}
    		link.l1 = RandPhraseSimple("Chciałbym złożyć datek.","Chcę przekazać datek na szczytny cel.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Myślę, że nadszedł czas na spowiedź.","Chcę się wyspowiadać, "+RandPhraseSimple("padre.","święty Ojcze."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("  Mam z tobą interes, "+RandPhraseSimple("padre.","święty Ojcze."),"Przybyłem w interesach, "+RandPhraseSimple("padre.","święty Ojcze."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "Chcę zamówić nabożeństwo za spokój duszy pewnej damy.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "Ojcze, potrzebuję pomocy. Jestem naprawdę chory. Jakaś plugawa pogańska klątwa mnie dopadła. Proszę, pomóż mi, błagam cię!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "Ojcze, potrzebuję pomocy. Jestem naprawdę chory. Jakaś plugawa, pogańska klątwa na mnie spadła. Proszę, pomóż mi, błagam cię!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "Ojcze, potrzebuję pomocy. Jestem naprawdę chory. Spadła na mnie jakaś plugawa pogańska klątwa. Powiedziano mi, że to Ty możesz mi pomóc. Błagam Cię...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Ojcze, potrzebuję pomocy. Jestem naprawdę chory. Jakaś plugawa pogańska klątwa na mnie spadła. Wysłała mnie do ciebie... Jessica Rose. Powiedziała, że będziesz w stanie mi pomóc.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "O świecach...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "Jestem gotów do modlitwy, Ojcze.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Straszne rzeczy się dzieją, święty Ojcze.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Przepraszam, ale muszę iść.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Nie martw się, synu mój. Pan ujrzy twoje cierpienie i wyciągnie pomocną dłoń. Zawsze noś przy sobie krzyż, aby wzmocnić swoją wiarę.";
			Link.l1 = "Dziękuję, święty Ojcze.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "Będę pokornie spełniał twoją wolę za 1000 pesos.";
			Link.l1 = "Proszę, Ojcze - weź te monety.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Dziękuję, mój synu. Jakie jest imię senory, za której duszę mam się modlić?";
			Link.l1 = "Jej imię to Chica Gonzales, i opuściła ten świat wiele lat temu.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "To dziwne... Czy coś się stało z Alvarezem, i zapytał cię o to?";
			Link.l1 = "A kim jest ten Alvarez i co takiego dziwnego w mojej prośbie?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Cóż, jakże! Każdego miesiąca Alvarez, strażnik naszej latarni przez dwie dekady, zamawia nabożeństwo modlitewne za spokój duszy tej damy. Nikt inny oprócz niego jeszcze nie troszczył się o Lady Gonzales. A ty przychodzisz tutaj. Tak pomyślałem. Jednak to nie moja sprawa. Z pewnością, z radością i pokorą spełnię twoje życzenia, by pomóc zagubionej duszy znaleźć spokój i drogę do raju.";
			Link.l1 = "Dziękuję, święty Ojcze.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "Czy jest ktoś jeszcze, za kogo duszę chciałbyś zamówić requiem?";
			Link.l1 = "Mmm... Nie, nie sądzę. Czy muszę zamówić dla kogoś innego?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "Cóż, być może za setki niewinnych ludzi, którzy padli z twojej ręki lub ostrzy bezbożnych towarzyszy, gdy splądrowałeś to nieszczęsne miasto?.. Jednakże, pokorny kapłan raczej nie ma nadziei dotrzeć do sumienia człowieka, który bez wyrzutów sumienia zabijał prostych pokojowych obywateli...";
			Link.l1 = "Ojcze, nie rozumiesz... To wszystko już przeszłość. Tu i teraz, nie zamierzam nikogo skrzywdzić.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = " Czy mogę zaufać twemu słowu...? Ale w każdym razie, to jest święta ziemia, która nie powinna być splamiona krwią. Więc, nie zawołam straży. Idź w pokoju. Być może zanim staniesz przed sądem Bożym, będziesz miał czas odkupić przynajmniej część swoich grzechów.";
			Link.l1 = "Być może. Niech się stanie wola Boża.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "Jessica? Pamiętam ją. Biedna grzesznica. Ale czy ona nie umarła?";
			link.l1 = "Zmarła, święty Ojcze. Teraz nie żyje, niech Pan odpoczywa jej duszę. Ale zapewniła mnie, że będziesz w stanie mi pomóc.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Kto rzucił na ciebie te zaklęcia, mój synu? Powiedz mi szczerze.";
			link.l1 = "Tak... tak zrobiła. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Niech Bóg nas strzeże! Tak właśnie myślałem. Zagłębianie się w pogańskie obrzędy może rzucić nawet najsilniejsze dusze w otchłań ciemności... Ale... czy ona naprawdę umarła? Czy... nie całkiem?";
			link.l1 = "Jesteś niezwykle przenikliwy, ojcze. Teraz jest całkowicie martwa.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "Ten biedny grzesznik wyznał mi swoje winy nie raz. Nienawiść zupełnie ją zniszczyła od środka. Wiedziałem, do czego zmierza. Próbowałem ją powstrzymać, starałem się nakłonić ją do nawrócenia, ale wszystkie moje wysiłki były daremne. Ostrzegłem ją przed strasznym niebezpieczeństwem i okropnymi konsekwencjami bezbożnych czynów...";
			link.l1 = "Tak, święty Ojcze. To, co widziałem, było rzeczywiście straszne. Ale... jak mogę zostać wyleczony?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Za sprawą modlitwy, mój synu. Za sprawą świętej oczyszczającej modlitwy w naszej świątyni. Będziesz musiał modlić się bardzo długo, i to nie tylko za siebie. Będziesz musiał modlić się także za nią.";
			link.l1 = "Dla Jessiki?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Tak. Dla siebie i dla jej duszy. Przyjdź tutaj o dziesiątej wieczorem, aby nikt cię nie rozpraszał. Będziesz musiał modlić się przez całą noc. Przynieś ze sobą dwadzieścia grubych woskowych świec, zapal je i módl się, aż wszystkie się wypalą.";
			link.l1 = "I wtedy będę uzdrowiony?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Wszystko jest w rękach Pana. Nauczę cię, jak się modlić, i zostawię ci Święte Pismo. Moc świętej modlitwy zniszczy plugawą magię, która cię nawiedziła, a także oczyści duszę biednej Jessiki.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Mam ze sobą dwadzieścia woskowych świec. Jestem gotów zostać w świątyni i rozpocząć modlitwę.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "Jeszcze nie mam dwudziestu świec. Zdobędę je!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "Dobrze, mój synu. Będę na ciebie czekał. Nie trać czasu!";
			link.l1 = "Będę tu wkrótce...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "Czy przyniosłeś dwadzieścia świec, mój synu?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Tak, Ojcze. Mam przy sobie dwadzieścia woskowych świec. Jestem gotów zostać w świątyni i zacząć się modlić.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Jeszcze nie - ale zdobędę je za wszelką cenę.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Cóż, mój synu. Oddaj mi je i wróć jutro po dziesiątej wieczorem. Nauczę cię potrzebnych modlitw i zostawię cię w kościele na noc.";
			link.l1 = "Dzięki, święty Ojcze. Do zobaczenia jutro!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "I have prepared the texts of the prayers for you , my son. I also left your twenty candles and the Holy Scripture. Light the candles and start praying. Pray without a stop; pray for your recovery and for the soul of this poor sinner Jessica. If you forget something or if you don't understand something - it doesn't really matter. Pray from your heart, your sincere desire is what matters to our Lord.";
			link.l1 = "Dziękuję, ojcze. Rozumiem.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "Wrócę rano. Będę się modlił także za ciebie...";
			link.l1 = "Dziękuję, święty Ojcze.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "Jakie pogańskie zaklęcia cię dotknęły, mój synu?";
			link.l1 = "I don't know how they are called. I am weak and sluggish; I cannot run around, and it is very difficult for me to fight.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "Słyszałem o tych... Zostały one sprowadzone na nasz świat przez nieświęte wiedźmy tych czerwonoskórych pogan. Radziłbym ci udać się do ojca przełożonego kościoła w Bridgetown - spędził on kilka lat badając zgubny wpływ indiańskich klątw na ciała i dusze chrześcijan.";
				link.l1 = "I on mógłby mi pomóc?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "Słyszałem o nich... Zostały sprowadzone do naszego świata przez bezbożne wiedźmy tych czerwonoskórych pogan. Niestety, jedyną radą, jaką mogę ci dać, jest spędzanie więcej czasu na modlitwie, mój synu, i pokładanie nadziei w miłosierdziu naszego Pana.";
				link.l1 = "Ale czy naprawdę nic nie można z tym zrobić, Ojcze?! Czy zostanę taki... do końca moich dni?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Nie rozpaczaj, synu mój. Pan usłyszy cię i pośle ci pomoc. Ale zalecałbym, byś popytał w innych świętych miejscach - może znajdą się kapłani, którzy wiedzą, jak zdjąć pogańskie klątwy.";
			link.l1 = "Dziękuję, Ojcze! Zostanę uzdrowiony - nawet jeśli będę musiał odwiedzić każdy kościół na archipelagu!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Idź, synu mój, i niech Pan czuwa nad tobą.";
			link.l1 = "Żegnaj, ojcze.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Tylko Pan może ci pomóc - i ty sam, mój synu. Kapłan może ci jedynie nauczyć, co robić i jak. Przyjdź do niego.";
			link.l1 = "Dziękuję, padre! Ocaliłeś mnie! Natychmiast popłynę na Barbados!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Idź teraz, a niechaj Pan czuwa nad tobą.";
			link.l1 = "Do widzenia, Ojcze.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "Jakie pogańskie klątwy cię spotkały, mój synu? Pozwól, że zgadnę: nie możesz biegać, szabla jest dla ciebie zbyt ciężka, a twoje ruchy są powolne i ociężałe?";
			link.l1 = "Skąd to wiedziałeś, Ojcze?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Nie było trudno to dostrzec, patrząc na twój krok, gdy się do mnie zbliżałeś, mój synu. Niech Pan będzie miłosierny dla naszych grzesznych dusz... Powiedz mi, mój synu, i bądź szczery - kto rzucił na ciebie te zaklęcia?";
			link.l1 = "Czy potrzebujesz imię, Ojcze?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "Jeśli znasz imię, to wypowiedz je.";
			link.l1 = "Jej imię było... Jessica Rose.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "Niech nas Bóg strzeże! Zgłębianie pogańskich rytuałów może rzucić nawet najsilniejsze dusze w otchłań ciemności... Co się z nią stało, z tą biedną duszą?";
			link.l1 = "Umarła, ojcze.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "Ale... czy ona naprawdę umarła? Czy... nie do końca?";
			link.l1 = "Jesteś niezwykle przenikliwy, święty Ojcze. Teraz jest całkowicie martwa.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "... i miłosierdzie Pana! Niech powszechna ciemność pochłonie ich dusze za ich grzechy...";
			link.l1 = LinkRandPhrase("Święty Ojcze","Padre"," Ojcze")+", czy nie jesteś zbyt gorliwy? Wiesz, możesz dostać apopleksji...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "No cóż... cholera. Żegnaj zatem.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Och, "+GetSexPhrase("mój synu","moja córka")+", straszne świętokradztwo, najohydniejsza zbrodnia właśnie się wydarzyła! Kradzież z kościoła!!! To jak wkładanie ręki do kieszeni samego Pana!";
			link.l1 = "Och, rozumiem... Jak to się stało?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("To bardzo smutne i wszystko, ale naprawdę muszę iść...","Moje kondolencje, ojcze, ale muszę już iść...","Musiałeś zbytnio polegać na Wszechmogącym. Powinieneś był używać bezpieczniejszych zamków. Cóż, muszę iść...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Pod osłoną nocy, jakieś łotry zagrabiły wszystko, co zebrała parafia! Ci bluźniercy zabrali nawet kielich ofiarny!";
			link.l1 = "O czasy, o obyczaje... Ale mam nadzieję, że podjąłeś się czegoś na gorącym tropie?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "Ale oczywiście! Ekskomunikowałem tych bluźnierczych rabusiów, a teraz rzucam na nich anathemę!";
			link.l1 = "Nie wątpię, że jest to niezwykle skuteczny środek. Ale miałem na myśli coś bardziej praktycznego. Na przykład zorganizowanie pościgu.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ach, co może uczynić prosty ksiądz, związany ślubem niestawiania oporu złu? Ci łotrzy z pewnością już są daleko stąd, pijąc w tawernach zebrane z rabunku lub oddając się rozpuście i rozpustności w towarzystwie upadłych kobiet! Mam nadzieję, że tam spotka ich koniec!";
			link.l1 = RandPhraseSimple("Jestem pewien, że taki koniec jest znacznie bardziej atrakcyjny niż powieszenie. Jednak nie będę cię już więcej odciągać. Wszystkiego najlepszego.","Cóż, prędzej czy później wszyscy pójdziemy do przodków, ale nie powiedziałbym nie szybszemu końcowi dla nich. Jednak muszę iść. Powodzenia.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Święty Ojcze","Padre","Ojcze")+", ale jestem wolny od wszelkich ślubów i z gotowością pomogę Panu sprowadzić czas odpłaty.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Będę się za ciebie modlił, synu! Idź teraz i daj tym oszustom to, na co zasługują!";
			link.l1 = "Nie miej wątpliwości, Ojcze";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Cóż, być może wszechdobry Stwórca zsyła swym głupim dzieciom zarazy i głód, by ukarać ich za grzechy...";
				link.l1 = "Na przykład z powodu pychy lub chciwości... Dlaczego zbladłeś, ojcze?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Jezusie, mój Panie, zmiłuj się nad swym grzesznym sługą... Czy ty... Czy znalazłeś złodziei? Czy ich zgładziłeś?";
					link.l1 = "Przypomnijmy sobie dziesięć przykazań, znanych każdemu dobremu chrześcijaninowi od kołyski: nie zabijaj, nie kradnij, nie mów fałszywego świadectwa przeciw bliźniemu swemu. Czy osoba bogobojna może je złamać - a tym bardziej duchowny kapłan...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "Powietrze tutaj jest tak gęste... Czy znalazłeś rabusiów? Zabiłeś ich?";
					link.l1 = "Pamiętajmy o dziesięciu przykazaniach, znanych każdemu dobremu chrześcijaninowi od kołyski: nie zabijaj, nie kradnij, nie mów fałszywego świadectwa przeciw bliźniemu swemu. Czy człowiek bogobojny może je złamać - a tym bardziej duchowny kapłan?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("Mój synu","Moja córka")+"... Boże, przebacz mi... takie pieniądze, taka pokusa... człowiek jest słaby, naprawdę słaby! Nie wytrzymałem... postradałem zmysły... Modliłem się dniem i nocą, pokutowałem, surowo pościłem, umartwiałem ciało... Niegodny, błagałem Niebiosa jedynie o oszczędzenie tych biednych ludzi, których zwiodłem, kierowany własną chciwością...";
			link.l1 = LinkRandPhrase("Ojcze","Padre","Ojcze")+", uspokój się. Nic o tym nie mówili... i na pewno nie będą mówić. Nawiasem mówiąc, dobrowolnie zwrócili mi kielich komunijny, który przyniosłem z powrotem do ciebie.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Panie mój, dziękuję Ci! Boże mój, usłyszałeś modlitwy swego niegodnego sługi, potkniętego grzesznika zanurzonego w brudzie i występkach...";
			link.l1 = "Każdemu mogło się to przydarzyć... Ale skoro twoja skrucha wydaje się szczera, powiem tak: jesteś przyzwoitym człowiekiem i dobrym kapłanem. Jeśli staniesz przed sądem, nic dobrego z tego nie wyniknie. To do ciebie należy decyzja, czy chcesz pozostać na służbie Pana - tylko On może ci to powiedzieć i cię poprowadzić...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("Mój synu","Moja córka")+"... Ze łzami pokuty i wdzięczności przyjmę od ciebie ten kielich. Czystość i szlachetność twojej duszy naprawdę mnie poruszyły. Błogosławię cię z całego serca i pokornie proszę, byś przyjął tę skromną nagrodę "+FindRussianMoneyString(iMoneyToCharacter)+"... Mam nadzieję, że wystarczy to na pokrycie twoich wydatków?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "To niepotrzebne, święty Ojcze "+NPChar.name+"Nie jestem dokładnie najbiedniejszą osobą, więc lepiej użyj tych pieniędzy dla dobra swojej parafii.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "Dziękuję, "+LinkRandPhrase("Ojcze","ojcze","święty Ojcze")+"To więcej niż wystarczająco.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = " "+GetSexPhrase("Mój synu","Moja córka")+"... Łzami skruchy i wdzięczności przyjmę ten kielich od ciebie jako znak miłosierdzia i przebaczenia Pana. Czystość i szlachetność twojej duszy naprawdę mnie poruszyły. Błogosławię cię z całego serca!";
				link.l1 = "Dziękuję za błogosławieństwo, "+LinkRandPhrase("padre.","Ojcze.")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "Zaiste, błogosławieństwo jest konieczne, ale nie zaszkodziłoby wesprzeć je czymś bardziej materialnym, biorąc pod uwagę znaczne wydatki, jakie poniosłem...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Och, dziecko, naprawdę mi przykro... Mam nadzieję, że ten drobny datek "+FindRussianMoneyString(iMoneyToCharacter)+" wystarczy, by pokryć wasze wydatki?";
			link.l1 = "Tak, "+LinkRandPhrase("padre.","Ojcze.")+"wystarczy, dziękuję.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "Nie do końca rozumiem twoje insynuacje, "+GetSexPhrase("mój synu","moja córka")+", o czym ty mówisz?!";
			link.l1 = "Mówię o strasznych rzeczach, które chciwość może zrobić z człowiekiem, i które dostałem od szubrawców rzekomo okradających wasz kościół... Czy chciałeś coś powiedzieć?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Rzekłbym ci, dziecko, że rozmawiasz z duchownym i powinieneś okazać nieco więcej szacunku, bo inaczej możesz tego żałować. Co do tego kielicha - nigdy go wcześniej nie widziałem, ale jeśli chcesz go podarować parafii, wtedy...";
			link.l1 = "Trzymaj konie, ojcze. Nie dostaniesz tego, dopóki się nie wytłumaczysz.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "Co tu jest do wyjaśnienia?! Teraz spójrz - jesteś "+GetSexPhrase("mądry człowiek","sprytna dziewczyna")+", i z pewnością musisz zrozumieć, że cokolwiek ci ci łotrzy mówili - że rzekomo ich wynająłem - to bezwstydne kłamstwo! Pan ukarze tych bluźnierców nie tylko za świętokradztwo, ale także za fałszywe zeznania!";
				link.l1 = "Zostaw Pana w spokoju! Skąd możesz wiedzieć, co mi powiedziały te biedne dusze, które na mnie napuściłeś? Może zabiłem ich, zanim zdążyli powiedzieć mi coś złego o tobie?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "There's nothing for me to talk about with you! You haven't fulfilled your obligation in the face of our Lord; you're swearing at the temple; you're attempting to blackmail a priest, displaying some church utensils - and it remains yet to be seen how you got it! Thank the God that I am not calling the acolytes to catch you red-handed!";
				link.l1 = "Cóż... Widzę, że ugrzązłeś w grzechu tak głęboko, że nie boisz się już ludzkiego sądu. Ale istnieje jeszcze boska sprawiedliwość, przed którą każdy z nas kiedyś odpowie. Weź swoje 'kościelne utensylia' i zastanów się, czy jesteś godzien ich dotknąć, Ojcze "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Proszę, wybacz mi moje wątpliwości, Ojcze, bo serce śmiertelnika jest słabe, a dusza zagubiona. Proszę, weź kielich i udziel mi swego błogosławieństwa.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+GetSexPhrase("Mój synu... Panie... Szanowny Panie...","Moja córka... Panna... Dama...")+" "+PChar.name+"... Jestem gotów uklęknąć przed tobą... i rozważyć nasze różnice zdań, że tak powiem... i zrekompensować twoje wydatki tą skromną sumą "+FindRussianMoneyString(iMoneyToCharacter)+"... oczywiście, jeśli nie zamierzasz angażować innych w tę sprawę...";
			// При этом варианте репу плюсуем
			link.l1 = "Nie zamierzam nikogo angażować. Weź kielich! I nawet nie myśl, że przyjąłbym złoto, które potajemnie wyciągałeś z kieszeni swoich parafian!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Nie zamierzam nikogo wciągać. Weź kielich! To złoto biorę tylko dlatego, że poświęciłem na ciebie mnóstwo czasu i pieniędzy.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Straszne wieści, "+LinkRandPhrase("Ojcze","Padre","Ojcze")+": rabusie okazali się zbyt zdradzieccy i przebiegli, więc nie udało mi się odzyskać złota kościelnego...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Straszne wieści, "+LinkRandPhrase("Ojcze","Padre","Ojcze")+": Udało mi się dogonić rabusiów, ale jedynym moim trofeum był ten kielich.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Jestem pewien, że spodoba ci się ta wiadomość - odpowiednio ukarałem rabusiów i odebrałem im pieniądze parafialne, a także ten kielich.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Ojcze","Padre","Ojcze")+", przynoszę złe wieści... Musiałem poświęcić mnóstwo czasu, sił i zasobów, by wytropić łajdaków, ale gdy ich znalazłem, odkryłem, że zdążyli przepić i wydać wszystko, z wyjątkiem tego kielicha...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+GetSexPhrase("mój synu","moja córka")+", cóż mogło mi się przydarzyć? To twoja droga pełna jest niebezpieczeństw i niepokoju, a moja spokojna cela, królestwo refleksji i modlitwy, jest cichą wyspą w burzliwym oceanie ludzkich namiętności...";
					link.l1 = "I nic nie może zakłócić spokoju twej błogosławionej samotności?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Jestem pewien, że ta wiadomość cię ucieszy - ukarałem rabusiów i przyniosłem pieniądze parafii.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Ojcze","Padre","Ojcze")+"... Muszę cię rozczarować. Ścigałem rabusiów po całym archipelagu, pokonałem wiele niebezpieczeństw i przeszkód, prawie się zrujnowałem, i w końcu ich dopadłem, ale niestety... zdążyli już roztrwonić kościelne pieniądze.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "O, "+GetSexPhrase("mój synu","moja córka")+"Twoje słowa pogrążyły mnie w głębokim smutku - lecz nie w rozpaczy, ponieważ rozpacz to grzech śmiertelny! Pan postawił przed nami kolejną próbę, aby wzmocnić naszą wiarę.";
						link.l1 = "Amen, Ojcze...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("Mój synu","Moja córka")+", nie kłam swojemu duchowemu pasterzowi.";
						link.l1 = "Naprawdę mi przykro, Ojcze, ale przysięgam, że mówię prawdę.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+GetSexPhrase("mój synu","moja córka")+"Twoje słowa pogrążyły mnie w głębokim smutku - lecz nie w rozpaczy, bo desperacja to grzech śmiertelny! Pan wystawił nas na kolejną próbę, by umocnić naszą wiarę. Ale twoje wysiłki i wydatki powinny zostać wynagrodzone, mimo że były bezowocne. Proszę, przyjmij tę skromną sumę - "+FindRussianMoneyString(iMoneyToCharacter)+" - i kontynuuj swoją sprawiedliwą ścieżkę!";
					link.l1 = "Hmm!... Dziękuję, ojcze, użyję tych pieniędzy na szlachetny cel.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Ojcze","Padre"," Ojcze")+"... Nie mogę przyjąć nagrody za pracę, której nie wykonałem. Lepiej wykorzystaj te pieniądze na odnowienie ołtarza.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "Dobrze, wierzę ci, "+GetSexPhrase("mój synu","moja córka")+"Pan nawiedził nas kolejnym doświadczeniem, aby wzmocnić naszą wiarę.";
				link.l1 = "Amen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Niegodziwy, czy naprawdę myślałeś, że możesz oszukać naszego Pana?! Niech przekleństwo cię dosięgnie"+GetSexPhrase(", łotrze",", dziewko")+" Precz i pamiętaj, że te pieniądze nie przyniosą ci żadnej korzyści!";
				link.l1 = "Jak to możliwe?! Padre!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+GetSexPhrase("mój synu","moja córka")+". Twoje słowa pogrążyły mnie w głębokim smutku - ale nie w rozpaczy, gdyż rozpacz to grzech śmiertelny! Pan postawił przed nami kolejną próbę, aby umocnić naszą wiarę.";
				link.l1 = "Amen, Ojcze...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Tak, to właśnie ten kielich, który został skradziony razem z pieniędzmi... Ale... skoro go odzyskałeś, to dlaczego nie przyniosłeś też pieniędzy? To była pokaźna suma, i z pewnością te łotry nie mogli jej tak szybko roztrwonić... "+GetSexPhrase("Mój synu","Moja córka")+", pamiętaj, że nie ma większego grzechu niż kłamstwo swojemu duchowemu pasterzowi i składanie fałszywych świadectw w świątyni przed obliczem Boga!";
				link.l1 = "Święty Ojcze "+NPChar.name+", O mało nie straciłem życia, zdobywając tę wazę, myślałem, że cię to ucieszy. Nie wspomnę nawet, ile pieniędzy na to wszystko wydałem!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = " Wynoś się  i dziękuj Wszechmocnemu, który obdarzył mnie pokornym sercem. To jedyny powód, dla którego wciąż nie jesteś oznaczony jako złodziej i łotr!";
			link.l1 = "Jak to możliwe?! "+LinkRandPhrase("Święty Ojcze","Padre","Ojcze")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+GetSexPhrase("mój synu","moja córka")+". Twoje słowa pogrążyły mnie w głębokim smutku - ale nie w rozpaczy, ponieważ rozpacz jest śmiertelnym grzechem! Pan postawił przed nami kolejną próbę, aby wzmocnić naszą wiarę.";
			link.l1 = "Amen, Ojcze...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Panie, dziękuję Ci! Rzeczywiście, byłeś Jego narzędziem, moje dziecko! Wiedziałem, że nasz Niebiański Ojciec wskaże ci drogę i zapewni całą potrzebną pomoc. Modliłem się bez przerwy, i...";
			link.l1 = "Wiesz, ojcze, w takich sprawach broń jest na pewno bardziej użyteczna niż modlitwy. Ale, najwyraźniej, twoje modlitwy rzeczywiście zostały wysłuchane.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("Mój synu","Moja córka")+", chcę cię należycie wynagrodzić, ty"+GetSexPhrase(", jak prawdziwy rycerz Matki Kościoła,"," ")+" zrobiliśmy wszystko, co w naszej mocy, aby przejąć...";
			link.l1 = "Padre, naprawdę przesadzasz z moimi skromnymi osiągnięciami. Teraz zostawię Cię, byś mógł chwalić naszego Pana...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "Oczywiście, "+GetSexPhrase("mój synu","moja córka")+" Ile chciałbyś ofiarować na rzecz Świętego Kościoła?";
			Link.l1 = "Przepraszam, święty Ojcze, ale zmieniłem zdanie.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "Moja ofiara będzie skromna - tylko 100 pesos.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 pesos. Myślę, że to powinno wystarczyć.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Mam szczęście z pieniędzmi, więc przekażę 5000 pesos.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Ojcze, chcę złożyć datek nie w swoim imieniu. Robię to na prośbę.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hmm... cóż, to twoja decyzja, i jesteś wolny, by zmienić zdanie. I nie zapominaj, że to zostanie rozliczone w Dniu Sądu Ostatecznego.";
			Link.l1 = "Jak wiele innych rzeczy również. Zmieńmy temat.";
			Link.l1.go = "node_3";
			Link.l2 = "Przepraszam, Ojcze, ale nadszedł czas, bym odszedł.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "W imieniu Świętego Kościoła dziękuję ci, "+GetSexPhrase("mój synu","moja córka")+" , za twój dar.";
			Link.l1 = "Muszę z tobą porozmawiać, ojcze.";
			Link.l1.go = "node_3";
			Link.l2 = "Przykro mi, Ojcze, ale nadszedł czas, bym odszedł.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "W imieniu Świętego Kościoła dziękuję ci.";
            Link.l1 = "Muszę z tobą porozmawiać, ojcze.";
			Link.l1.go = "node_3";
			Link.l2 = "Przykro mi, Ojcze, ale nadszedł czas, bym odszedł.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "W imieniu Świętego Kościoła dziękuję ci za twój dar.";
            Link.l1 = "Muszę z tobą porozmawiać, ojcze.";
			Link.l1.go = "node_3";
			Link.l2 = "Przykro mi, Ojcze, ale czas, abym odszedł.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Oczywiście, "+GetSexPhrase("mój synu","moja córka")+"Słucham cię.";
			link.l1 = "Zmieniłem zdanie. Może następnym razem.";
			link.l1.go = "exit";
			link.l2 = "Jestem tak pełen grzechów, Ojcze. Dzień nie wystarczy, by wymienić wszystkie moje występki...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Wszyscy jesteśmy grzesznikami, moje dziecko...";
			link.l1 = "Tak, ale na moim sumieniu spoczywa ciężar tysięcy śmierci. Okradałem i topiłem statki...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = " Mam nadzieję, że nie było nikogo wśród tych, którzy żeglowali pod banderą "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Nie, oczywiście, że nie, Ojcze.";
			link.l1.go = "ispoved_3";
			link.l2 = "Wszelkiego rodzaju, ojcze...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Wtedy nasz Pan odpuści ci te grzechy. Bo to jest okrutna epoka, a niszcząc wrogów twego władcy, ratujesz życie jego wiernych poddanych.";
			link.l1 = "Dziękuję, Ojcze, to była wielka pociecha... Teraz już pójdę.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Pan nie odpuści ci takiego grzechu! Módl się i pokutuj, pokutuj i módl się! Jest tylko jedna droga dla ciebie teraz - do klasztoru!";
			link.l1 = "Klasztor będzie musiał poczekać. Nie w tym życiu, przynajmniej. Żegnaj...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Przykro mi, "+GetSexPhrase("mój synu","moja córka")+", ale wszystkie konfesjonały są zajęte w tej chwili. Będę mógł wysłuchać twojej spowiedzi za co najmniej pół godziny.";
				link.l1 = "Przepraszam, "+RandPhraseSimple("ojcze","Ojcze")+", to inna sprawa. Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+", z "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+", kiedyś dał ci bezcenne skarby teologicznej biblioteki. Poprosił mnie, abym je zwrócił.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Co za interesy cię tu sprowadziły, "+GetSexPhrase("mój synu","moja córka")+"?";
			link.l1 = "Chciałbym zadać ci jedno pytanie, Ojcze...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("Chciałem porozmawiać o pracy na rzecz dobra kościoła "+NationNameGenitive(sti(NPChar.nation))+".","Jak się mają sprawy w parafii? Potrzebujecie jakiejś pomocy?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre","Ojcze")+"Chcę porozmawiać z tobą o sprawach finansowych."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "Potrzebuję uzdrowienia.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Ksiądz","Święty Ojcze")+", jestem tu na prośbę pewnego człowieka. Jego imię to gubernator "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Padre, przyniosłem ci dokumenty od mnicha z miasta "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Ojcze, przybyłem z kolonii "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+"Kościół lokalny potrzebuje więcej modlitewników, a lokalny mnich zasugerował, aby zwrócić się do ciebie w tej sprawie.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Ojcze, przyniosłem modlitewniki dla twojej parafii.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "Zmieniłem zdanie, mam wiele do zrobienia.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "To wspaniale. A jednak, w tych ponurych czasach, "+GetSexPhrase("mój synu","moja córka")+", nie każdy odwiedzający świątynię może być użyteczny dla naszej Matki Kościoła.";
				link.l1 = LinkRandPhrase("Ojcze","Księże","Ojcze")+"Jestem prawdziwym chrześcijaninem, a moje intencje służenia naszej Matce Kościołowi są jak najbardziej szczere."+GetSexPhrase(" Kto ją wesprze, jeśli nie jej lojalny rycerz, taki jak ja?","")+" ";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "W parafii jak dotąd wszystko jest cicho, "+GetSexPhrase("mój synu","moja córka")+" Dziękuję za ofertę.";
    		link.l2 = "Cóż, jeśli wszystko w porządku, to chyba zajmę się swoimi sprawami.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Cóż, mam jedno delikatne zadanie, które wymagałoby nie tylko czystości intencji, ale także wielkiej odwagi i znacznej dyskrecji...";
			link.l1 = LinkRandPhrase("Ojcze","Padre","Ojcze")+", Będę szczęśliwy mogąc świadczyć ci jakąkolwiek usługę, nawet jeśli w tym celu będę musiał udać się prosto do piekła! Niech Bóg wybaczy mi moje nieświęte słowa.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "O! Dobrze... Ale, znów, to bardzo delikatna sprawa... Jakiś czas temu ojciec przeor "+PChar.GenQuest.ChurchQuest_1.ToName+" z "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Generale")+" na "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"pożyczył mi kilka dzieł teologicznych i starożytnych manuskryptów z biblioteki kościelnej na jakiś czas. Ponieważ prośba była poparta naleganiem arcybiskupa, aby nie zapobiegać rozprzestrzenianiu się uroczej światłości wiedzy, nie mogłem odmówić, mimo że przypuszczałem, iż trudności morskich podróży uniemożliwią mu zwrócenie manuskryptów na czas... Czy mógłbyś mi pomóc rozwiązać ten problem?";
			link.l1 = "Obawiam się, "+LinkRandPhrase("Ojcze","padre","święty Ojcze")+" , nie będę w stanie tego dla Ciebie zrobić. To bardzo delikatna sprawa i tylko prawdziwy dyplomata zdołałby ją rozwiązać.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Ojcze","Padre","Ojcze")+", twoja misja nie wydaje mi się zbyt skomplikowana. Wyruszam tam natychmiast.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "O! Tak... Rzeczywiście, teraz sobie przypominam... Ale, "+GetSexPhrase("mój synu","moja córka")+", te skarby mają bardziej duchowy niż materialny charakter! Już ogromnie pomogły moim parafianom i mogą zrobić to ponownie w przyszłości!";
				link.l1 = "Ale, "+LinkRandPhrase("Ojcze","Padre","Ojcze")+", parafianie Ojca "+PChar.GenQuest.ChurchQuest_1.PriestName+" również potrzebują zbawienia, a bez tych dzieł będzie mu brakowało wsparcia filarów teologii, a jego kazania będą pozbawione inspiracji.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "O, tak!.. Rzeczywiście... "+GetSexPhrase("Mój synu","Moja córka")+", te skarby mają bardziej duchowy niż materialny charakter! Już ogromnie pomogły moim parafianom, więc, ku mojemu wstydowi, 'zapomniałem' zwrócić je prawowitemu właścicielowi...";
				link.l1 = "Owszem, "+RandPhraseSimple("Ojcze","Padre","Ojcze")+", rzeczywiście. Dlatego Ojciec "+PChar.GenQuest.ChurchQuest_1.PriestName+" poprosił mnie, abym osobiście dostarczył mu te książki.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Rozumiem, moje dziecko, ale czyż nie modlimy się codziennie do naszego Pana: 'i odpuść nam nasze winy, jako i my odpuszczamy naszym winowajcom'? A kościół "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" bardziej bogata niż moja skromna parafia.";
			link.l1 = "Na pewno masz rację, ojcze, ale właśnie przypomniały mi się inne wersety z Pisma Świętego: 'nie szukaj łatwej ścieżki, bo to tam diabeł na nas czeka, a jego głos jest tym bardziej subtelny, a pokusa tym bardziej silna, im łatwiejsza jest ścieżka!' A padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" już zamierzał wysłać wiadomość do arcybiskupa o twojej niepamięci - ledwo go od tego odwieść.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "T-T-Tak do a-arcypiskupa?! Z tak błahego powodu!.. Dlaczego? Naprawdę? I tak zamierzałem wysłać te dzieła do mojego ukochanego brata w Chrystusie - po prostu nie było dobrej okazji, aby je do niego dostarczyć. Ale w tobie, "+GetSexPhrase("mój synu","moja córka")+", widzę prawdziwie zasłużonego sługę naszego Pana. Proszę - weź te księgi i rękopisy i dostarcz je Ojcu "+PChar.GenQuest.ChurchQuest_1.PriestName+"cały i zdrowy. I dodaj do tego moje najszczersze wyrazy wdzięczności.";
			link.l1 = "Oczywiście, "+LinkRandPhrase("Bracie","Padre","Ojcze")+"Oczywiście...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "Ale, "+GetSexPhrase("mój synu","moja córka")+"... Widzisz, rzecz w tym, że w zeszłym tygodniu spotkałem kapitana statku '"+sld.Ship.Name+"', gdzie zostałem wezwany, aby udzielić komunii umierającemu żeglarzowi. Ku mojej wielkiej radości, kapitanie "+GetFullName(sld)+" powiedział mi, że zamierzał "+XI_ConvertString("Colony"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+". I chociaż nie zasłużył na żadne warunki, zgodził się pomóc i zapewnił mnie, że port "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" z pewnością odwiedzi. Więc skorzystałem z tej okazji, odesłałem księgi z tym dobrym człowiekiem i powierzyłem ich dalszy los Panu.";
				link.l1 = "Zastanawiam się, czy ten kapitan rzeczywiście jest godzien zaufania? Czy on zdaje sobie sprawę z wartości powierzonych mu dzieł i znaczenia tej misji?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Oh, "+GetSexPhrase("mój synu","moja córka")+" ! Jesteś tylko kilka godzin spóźniony! Już wysłałem księgi Ojca "+PChar.GenQuest.ChurchQuest_1.PriestName+" z kapitanem "+PChar.GenQuest.ChurchQuest_1.CapFullName+" Tego ranka, ten bogobojny człowiek przyszedł się wyspowiadać i wspomniał, że dziś jego statek wypływa do "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+". I chociaż pan kapitan nie zagwarantował żadnych warunków, zgodził się pomóc i zapewnił mnie, że port "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Rodzaj")+"z pewnością odwiedzi.";
				link.l1 = LinkRandPhrase("Ojcze","Padre","Ojcze")+"... czy jesteś pewien, że temu kapitanowi można zaufać? I chcę również wiedzieć, jak nazywa się jego statek.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "Ufamy ludziom, "+GetSexPhrase("mój synu","moja córka")+"Każdy z nas jest stworzony na obraz i podobieństwo naszego Pana, a Jego święty ogień płonie w każdej duszy!";
			link.l1 = "Och. To z pewnością mocny argument. Cóż... Więc pobłogosław mnie, Ojcze, i życz mi szczęścia w poszukiwaniach tego kapitana.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "Powinieneś ufać ludziom, "+GetSexPhrase("mój synu","moja córka")+"Co do jego statku - nie mam nic do powiedzenia.";
			link.l1 = "I przekazałeś cenne rękopisy jakiemuś kapitanowi, nie zadając sobie nawet trudu, by poznać nazwę jego statku?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Widzisz, "+GetSexPhrase("mój synu","moja córka")+", kapitanie "+PChar.GenQuest.ChurchQuest_1.CapFullName+"jest bardzo bogobojny...";
			link.l1 = "Cóż, już to słyszałem.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Cierpliwości, "+GetSexPhrase("młody człowieku","młoda dama")+"! Kapitanie "+PChar.GenQuest.ChurchQuest_1.CapFullName+" to bardzo bogobojna osoba, a do dziś jego okręt nosił nazwę, której duchowny nigdy nie powinien nawet pomyśleć, a co dopiero wypowiedzieć na głos! I dziś podczas jego spowiedzi zwróciłem mu na to uwagę. Albowiem, jak mówi Biblia, czystość duszy musi być przez nas, grzeszników, zachowana bardziej niż czystość ciała, gdyż nasz Pan odmawia swego Królestwa tym, którzy bluźnią...";
			link.l1 = "Widzę, "+LinkRandPhrase("Ojcze","Padre","Ojcze")+"Rozumiem!"+PChar.GenQuest.ChurchQuest_1.CapFullName+", notoryczny hazardzista i pijak, znany w całych Karaibach, postanowił przemianować swą starą krypę na Twoją sugestię?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Jesteś bardzo przenikliwy, "+GetSexPhrase("mój synu","moja córka")+"Nie znam nowej nazwy tego statku, ale z pewnością jest to coś wzniosłego.";
			link.l1 = "Oh, "+RandPhraseSimple("Ojciec","Padre","Ojcze")+"... Dziękuję za wszystko. I módl się za moją grzeszną duszę...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Oh, moje dziecko! Modliłem się gorliwie, i wszystko zdaje się rozwiązać w najlepszy możliwy sposób! Za twoją pomoc i wiarę, "+GetSexPhrase("mój synu","moja córka")+", raj i anielskie śpiewy z pewnością będą czekać na...";
			link.l1 = RandPhraseSimple("Padre.","Ojcze.")+", nie zamierzam spotkać się z Świętym Piotrem w najbliższym czasie, uchowaj Boże. Jeśli chodzi o żywych - oni potrzebują wielu materialnych rzeczy oprócz obietnic niebiańskiej szczęśliwości...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Tak, tak, "+GetSexPhrase("mój synu","moja córka")+"oczywiście. Wynagrodzę cię zasłużenie. Oto, weź to i pamiętaj, że nasz Pan karze te głupie dusze, które zbyt pragną ziemskich błogosławieństw i czczą żółtego diabła!";
			link.l1 = "Dziękuję, "+LinkRandPhrase("Ojcze","Padre","święty Ojcze")+". Proszę, weźcie wasze długo oczekiwane księgi i rękopisy i módlcie się za moją grzeszną duszę... Żegnajcie!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "Twoje zdrowie to "+GetHealthNameMaxSmall(pchar)+", a rany same się zagoją. Musisz tylko unikać rozlewu krwi i dbać o swoje zdrowie.";
    			link.l1 = "Dziękuję, to z pewnością ulga. Spróbuję powstrzymać się od walk przez jakiś czas.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Twoje zdrowie to "+GetHealthNameMaxSmall(pchar)+", a chociaż rany same się zagoją, powinieneś się nimi zająć.";
    			link.l1 = "Czego potrzeba do tego?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "A dlaczego moje zdrowie się pogarsza?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "To bardzo proste, "+GetSexPhrase("mój synu","moja córka")+"Za każdym razem, gdy zostajesz ranny, otrzymujesz obrażenia. To nie przechodzi bez śladu. Twoje zdrowie pogarsza się z każdą raną, a w rezultacie stajesz się słabszy. Twoja załoga, widząc słabego kapitana, traci do ciebie szacunek. Jednak stajesz się bardziej ostrożny, a zdolność do obrony wzrasta tymczasowo. Odpoczynek i minimalizowanie ran pomogą ci zachować pełnię sił.";
			link.l1 = "Dziękuję za oświecenie.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Modlitwy i powstrzymywanie się od przemocy, "+GetSexPhrase("mój synu","moja córka")+" Wtedy Pan zwróci ci to, co straciłeś.";
			link.l1 = "Możesz się za mnie pomodlić?";
			link.l1.go = "healthAdd_3";
			link.l2 = "Więc nie ma żadnego sposobu? Hmm... Naprawdę mnie uspokoiłeś, dzięki.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Mnie? To jest prawdopodobne. Ale będziesz musiał złożyć datek na naszą parafię.";
    			link.l1 = pcharrepphrase("Ile to kosztuje?","Z przyjemnością! Ile to kosztuje?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Chyba poradzę sobie sam...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = " "+GetSexPhrase("Mój synu","Moja córka")+", Już modlę się za twoje dobro. Te modlitwy zajmą cały mój czas aż do końca miesiąca.";
    			link.l1 = "Dziękuję, "+RandPhraseSimple("padre.","Święty Ojcze.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "Sto tysięcy pesos będzie wystarczającą zapłatą za cud uzdrowienia.";
			link.l1 = pcharrepphrase("Co?!! Czyś ty kompletnie oszalał? Zapłaciłbym taką sumę dopiero po obrabowaniu kilku kościołów!","To dla mnie za dużo. Mówią prawdę - zdrowia nie można kupić za pieniądze.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Zgadzam się!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Dobrze. Twoje zdrowie nieco się poprawi. Ale nadal musisz unikać potyczek i dbać o siebie, w przeciwnym razie ten efekt zaniknie. Będę musiał spędzić cały miesiąc na modlitwach za twoje znikome ciało.";
			link.l1 = "Dzięki. Jeśli coś się wydarzy, przyjdę do ciebie znowu za miesiąc.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "A któż to taki dobry człowiek ofiarowuje te pieniądze?";
			link.l1 = "Hmm... To madame z lokalnego burdelu.";
			link.l1.go = "HostessChurch_call";
			link.l2 = " Wolałbym zachować te imiona w tajemnicy. Można dokonać anonimowej darowizny, prawda?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "Jesteś grzesznikiem, a jednak o co pytać? Lepiej pomyśl najpierw o swojej duszy, w końcu wszyscy staniemy przed Panem!";
					link.l1 = "To prawda. Mam nadzieję, że nasz Pan będzie miłosierny dla mnie... A co z datkiem?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Odejdź ode mnie, szatanie!!! Zabierz swoje nieświęte pieniądze i wynoś się!";
					link.l1 = "Jak to, Ojcze?! Przyszliśmy do ciebie z otwartym sercem, a ty...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "Jestem rad, że pomagasz grzesznikom odnaleźć drogę do naszego Pana. Za to zostaniesz odpowiednio nagrodzony w Niebie!";
					link.l1 = "To byłoby wspaniałe! A co z datkiem?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Nie mogę przyjąć pieniędzy zdobytych w grzechu. Zwróć je tej upadłej kobiecie, "+GetSexPhrase("mój synu","moja córka")+" Nikt nie znajdzie drogi do Boga przez pieniądze.";
					link.l1 = "To szkoda, że ją odrzucasz. Wielka szkoda.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Przyjąć te pieniądze, nie wiedząc nawet, skąd pochodzą...";
				link.l1 = "Tak, ojcze, dokładnie. Proszę, przyjmij ten dar serca!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Brać te pieniądze, nie wiedząc nawet, skąd pochodzą? Czyś ty oszalał?! A co, jeśli te pieniądze są splamione krwią!";
				link.l1 = "Ojcze, wszystkie pieniądze są splamione krwią...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Przyjmuję to, "+GetSexPhrase("mój synu","moja córka")+"Idź i powiedz to swojej upadłej kobiecie.";
			link.l1 = "Dobrze, padre. Dziękuję.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "Przyjmuję to, "+GetSexPhrase("mój synu","moja córka")+"Opowiedz o tym swojemu darczyńcy.";
			link.l1 = "Dobrze, padre. Dziękuję.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Precz, pomiocie piekielny, i nie waż się tu pokazywać ponownie!";
			link.l1 = "Heh, jak sobie życzysz.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "To moja decyzja. Idź w pokoju, "+GetSexPhrase("mój synu","moja córka")+".";
			link.l1 = "Żegnaj, ojcze.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "Tak myślisz, bluźnierco?! Opuść świątynię natychmiast i nie waż się tu więcej pokazać!";
			link.l1 = "O, naprawdę? Nieważne, odchodzę...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "Już prawie straciłem nadzieję, że zobaczę te dokumenty ponownie. Czemu to tyle trwało, mój synu?";
				link.l1 = "To były... nieprzewidziane wydarzenia, Ojcze.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "Czekałem na te dokumenty, synu. Dziękuję za szybką dostawę. Proszę, przyjmij te monety i idź z moim błogosławieństwem.";
				link.l1 = "Dziękuję, Ojcze. Z przyjemnością pomogłem Świętemu Kościołowi!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "Jesteśmy wszyscy w rękach Boga, mój synu... Człowiek planuje, a Bóg decyduje. Podaj mi te papiery i idź w pokoju.";
			link.l1 = "Oto masz, padre. Wszystkiego najlepszego!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "Błogosławieństwo Boże, mój synu. Niech Wszechmogący czuwa nad tobą w twoich podróżach!";
			link.l1 = "Żegnaj, ojcze.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "Zostałeś wysłany, aby zabrać od nas modlitewniki - dla kościoła "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"? Cóż. Mam paczkę z trzydziestoma modlitewnikami. Weź ją, mój synu.";
			link.l1 = "Dziękuję, ojcze. Do widzenia!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "Niech Pan czuwa nad tobą w twoich podróżach! Idź w pokoju...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Dziękuję za pomoc, mój synu, choć dotarła z pewnym opóźnieniem.";
				link.l1 = "Zatrzymały mnie nieprzewidziane okoliczności, Ojcze.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Dziękuję za twoją pomoc, mój synu. Przyniosłeś te książki w samą porę. Proszę, przyjmij ten poświęcony amulet jako nagrodę - uratuje cię od niebezpieczeństwa w najciemniejszej godzinie.";
				link.l1 = "Dziękuję, Ojcze. Z przyjemnością pomogłem Świętemu Kościołowi!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "To wszystko w rękach Boga, mój synu. Idź w pokoju!";
			link.l1 = "Żegnaj, ojcze.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "Boże błogosławieństwo, mój synu. Niech Wszechmogący chroni cię przed złem na twoich drogach!";
			link.l1 = "Żegnaj, Ojcze.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
