// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
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
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " To koniec. Teraz opuść to miejsce, "+pchar.name+"Posprzątam ten cały bałagan.";
					link.l1 = "Dobrze, wypłynę na morze!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Miasto jest w stanie alarmu i szukają cię wszędzie! Na twoim miejscu nie zostawałbym tu długo.","Wszyscy strażnicy cię szukają. Nie jestem idiotą i nie będę ryzykować rozmowy z tobą!","Uciekaj, "+GetSexPhrase("towarzyszu","dziewczyna")+"...zanim żołnierze zrobią z ciebie sito..."),LinkRandPhrase("Czego chcesz, nikczemna kreaturo?! Straż miejska zna twoje położenie i nie uciekniesz, "+GetSexPhrase("plugawy pirat","ty piracka dziwko")+"!","Brudny morderco, wynoś się z mojego miejsca! Straże!","Nie boję się ciebie, plugawa kreaturo! Wkrótce zostaniesz powieszony w naszym forcie, nie uciekniesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, to nie problem dla mnie...","Nie złapią mnie nigdy."),RandPhraseSimple("Zamknij gębę, "+GetWorkTypeOfMan(npchar,"")+", albo odetnę ci ten cholerny język!","Heh, "+GetWorkTypeOfMan(npchar," ")+"Chcesz też złapać pirata, co? Słuchaj, chłopcze, siedź tu cicho, a będziesz żył..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Potrzebujesz czegoś, monsieur?";
				Link.l1 = "Potrzebuję informacji... Chcę cię o coś zapytać.";
				Link.l1.go = "quests";
				Link.l2 = "Co powiesz na małą pożyczkę?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "Nie, zmieniłem zdanie.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Spójrz na te kolczyki, monsieur. Znalazłem je w kieszeni bandyty w dżungli. To z pewnością dzieło wytrawnego jubilera, które, jestem pewien, nie pochodzi z tej dziczy. Co ty na to?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "Wiem, że masz dłużnika o imieniu Folke Deluc. Powiedz mi, jak bardzo jest on... zaległy?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Przychodzę w sprawie długu Folke Deluca.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "Zakończyłem twoje zadanie, monsieur. Oto twój... hiszpański przyjaciel.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Cóż, nareszcie godny kapitan odwiedził moje miejsce, tak się zmęczyłem idiotami, którzy myślą, że po prostu sadzę ich dublony i gineje, a potem zbieram plony co miesiąc, aby zapłacić im ich odsetki\nObserwują każdy grosz, nie mając pojęcia, jak biedny lichwiarz ucieka się do różnych sztuczek, aby sam nie umrzeć z głodu, a jednocześnie zapewnić im możliwość kupienia gęsi na Boże Narodzenie.";
				Link.l1 = "Przypuszczam, że twoi klienci nie będą zadowoleni słysząc takie słowa od człowieka, który trzyma ich oszczędności.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Słuchaj, stary chomiku, naprawdę musisz się postarać, aby mi to wszystko wyjaśnić! W ładunku tego statku nie było żadnych niewolników, tylko kompania żołnierzy! To była naprawdę trudna misja, by się z nimi uporać! Jestem bardzo wściekły, więc lepiej się wytłumacz!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, nareszcie jesteś! Cały archipelag plotkuje o twoim śmiałym ataku. Miło cię widzieć!";
				Link.l1 = "Wolałbym nieznaność niż tego rodzaju sławę... To zbyt niebezpieczne.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Czy przywiozłeś moje pięć tysięcy niewolników?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Mam. Są w moim ładowni.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Nie, wciąż nad tym pracuję.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm.. Wciąż żyjesz? Dziwne. Ale to nie potrwa długo. Żołnierze! Pomocy! Mam tu bandytę!";
				link.l1 = "Taki drań!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Dzień dobry. Nazywam się "+GetFullName(npchar)+"Jak mogę służyć?";
				link.l1 = "O! Co pan tutaj robi?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hejże, ty łotrze. Czyżbyś miał genialny pomysł? Wynająłeś zbirów, żeby mnie zabić? Chciałeś mnie uciszyć? Mów, teraz!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Och, kapitanie! Proszę spojrzeć, co dziś mam. Niektóre rzeczy zdobyłem od ludzi Blackwooda. Potrzebują pieniędzy na nową wyprawę, a my - cóż, my na tym skorzystamy, prawda?";
				link.l1 = "Czy Blackwood wie, że jego ludzie sprzedają znaleziska?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Dzień dobry, "+GetAddress_Form(NPChar)+"Jak mogę ci pomóc? Czy my się znamy?","Wejdź, kapitanie. Nazywam się "+GetFullName(npchar)+" a ja jestem miejscowym bankierem.","Miło cię poznać, "+GetAddress_Form(NPChar)+"! Jestem miejscowym bankierem, a jeśli masz problem z pieniędzmi, to mogę ci pomóc."),LinkRandPhrase("Czy już się spotkaliśmy, kapitanie? Ja jestem "+GetFullName(npchar)+", a ja jestem miejscowym bankierem.","Wejdź, kapitanie. Nazywam się "+GetFullName(npchar)+" a ja jestem miejscowym bankierem.","Witaj, "+GetAddress_Form(NPChar)+" . Jestem "+GetFullName(npchar)+", lokalny bankier."),LinkRandPhrase("Miło cię poznać, "+GetAddress_Form(NPChar)+", jestem "+GetFullName(npchar)+" tylko skromny bankier w tym cudownym mieście.","To twoja decyzja, kapitanie! Chcesz pożyczyć ode mnie trochę monet czy pożyczyć pieniądze na procent?","Panie kapitanie! Bardzo się cieszę, że odwiedziłeś moje skromne biuro!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("Z przyjemnością! Właśnie spacerowałem po mieście i postanowiłem cię odwiedzić.","Z przyjemnością, jestem "+GetFullName(pchar)+", miło cię poznać."," "+GetFullName(pchar)+" , kapitan statku o nazwie "+pchar.ship.name+" , miło cię poznać. To jest bank, prawda?"),RandPhraseSimple("Miło cię poznać. Ja jestem "+GetFullName(pchar)+". Kapitan statku o imieniu "+pchar.ship.name+" Chciałem cię tylko poznać.","Aha, więc macie tu bank, prawda? Miło cię poznać, jestem "+GetFullName(pchar)+", kapitan własnego statku."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Dama MacArthur, witaj, proszę wejdź.";
					link.l1 = "I tobie, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("To ty! Czego chcesz, "+GetAddress_Form(NPChar)+"?","Co cię tu sprowadza, kapitanie? Przykro mi, ale twoja reputacja nie czyni cię zbyt pożądanym klientem.","Aha, kolejny klient! Na początku myślałem, że jesteś rabusiem... ha-ha Tylko żartuję."),LinkRandPhrase("O! Czego chcesz? To bank, nie tawerna.","Dzień dobry, kapitanie. Muszę cię poinformować, że jestem dość wybredny w doborze swoich klientów.","Czego chcesz, "+GetFullName(pchar)+"? Mam nadzieję, że pamiętasz, iż twoja renoma nie pozwoli ci na zaciągnięcie dużej pożyczki?"),LinkRandPhrase("Mam nadzieję, że chcesz zainwestować pieniądze, "+GetAddress_Form(NPChar)+"Nie będzie łatwo uzyskać dla ciebie pożyczkę.","Kapitana "+GetFullName(pchar)+" czego chcesz od skromnego bankiera? Przykro mi, ale nie będę mógł zaaranżować dla ciebie pożyczki. Możesz jedynie pożyczać mi pieniądze na procent.","Wejdź, "+GetAddress_Form(NPChar)+"Przykro mi poinformować, że nie jesteś najbardziej mile widzianym klientem, ale zazwyczaj nie odrzucam ludzi od razu.")),LinkRandPhrase(LinkRandPhrase("Witaj, panie "+GetFullName(pchar)+"Zawsze jestem gotów pomóc ci w problemach biznesowych.","Witaj, panie "+GetAddress_Form(NPChar)+"Zawsze jestem gotów udzielić pożyczki lub przyjąć każdą inwestycję.","Drogi "+GetFullName(pchar)+" ! Cieszę się, że cię widzę! Czego sobie życzysz?"),LinkRandPhrase("Kapitanie "+GetFullName(pchar)+"! Zawsze do Twoich usług. Chcesz wziąć pożyczkę lub zainwestować pieniądze na procent?","Witam cię, kapitanie! Zawsze jesteś tu pożądanym klientem. Masz doskonałą reputację w interesach!","Dzień dobry, "+GetFullName(pchar)+" Cieszę się, że znów mnie odwiedziłeś. Mam nadzieję, że przyszedłeś w celu zawarcia korzystnej umowy handlowej?"),LinkRandPhrase("Dzień dobry, kapitanie! Czego sobie życzysz? Chcesz wziąć pożyczkę czy zainwestować?","Kapitanie "+GetFullName(pchar)+"! Chcesz pożyczyć pieniądze na korzystnych warunkach? Zawsze cieszę się widząc tak szanownego klienta.","Cieszę się, że znowu cię widzę, kapitanie! Zawsze jestem gotów ci pomóc, czy to wziąć pożyczkę, czy dokonać inwestycji.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Bez żartów, bankierze, mam tu interes.","Za dużo gadania, kumplu. Przejdźmy od razu do interesów.","Czy słyszałeś, że pieniądze nie pachną? Więc zatkaj nos i przejdźmy do interesów."),LinkRandPhrase("A tak traktujesz swoich klientów? Masz szczęście, że dziś jestem w dobrym humorze.","Ha! Czyż nie cieszysz się na mój widok, co? I czyż nie jestem jak złoty dublon, by wywrzeć na tobie pozytywne wrażenie. W każdym razie, przejdźmy do interesów, lichwiarzu.","Eh, chciałbym nauczyć cię szacunku, ale nie mam na to czasu. Porozmawiajmy więc o pieniądzach.")),RandPhraseSimple(LinkRandPhrase("Cieszę się, że widzę mojego starego przyjaciela!","Zawsze to przyjemność tu przybyć, druh. Przejdźmy od razu do interesów.","Ja też się bardzo cieszę. Porozmawiajmy o interesach, przyjacielu."),LinkRandPhrase("Naprawdę miło cię poznać. Co nowego na finansowych morzach?","Miło, że wciąż mnie pamiętasz. Spieszę się, więc przejdźmy od razu do interesów.","Witaj, stary przyjacielu! Cieszę się, że znowu cię widzę!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Jak mogę ci pomóc?","Czego pragniesz tym razem?","Hm... jakie są twoje obawy?","Eh, "+GetAddress_Form(npchar)+", nie możesz sobie nawet wyobrazić, jak irytujący potrafią być klienci...","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nie, dziękuję, tylko spaceruję i rozmawiam.","To znowu ja. Chciałem z tobą porozmawiać.","Tak, to znowu ja. Nic poważnego, po prostu chciałem z tobą porozmawiać.","Tak, bycie bankierem czasem nie jest takie łatwe. Chciałem tylko porozmawiać...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Chcę omówić nasze sprawy finansowe.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Interesują mnie klejnoty i niezwykłe idole lub kamienie szlachetne.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Potrzebuję informacji. Cóż, mam coś, o co chciałbym cię zapytać.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Przyniosłem ci dokumenty biznesowe z "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Przybyłem tu z rozkazu jednego człowieka. Jest gubernatorem "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+"  wysłał mnie tutaj. Muszę coś od ciebie odebrać.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Dzień dobry, zostałem zaproszony przez twojego syna."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Jestem ciekaw, kto jest właścicielem tego dokumentu.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Chcę porozmawiać o długu twojego klienta. Jego imię to "+pchar.GenQuest.Noblelombard.Name+". Zastawił swoją rodzinną relikwię. Reprezentuję tu jego interesy i mam prawo omówić z tobą jej zwrot.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Mieliśmy spotkanie trzy miesiące temu i rozmawialiśmy o relikwii pewnego człowieka. Nazywał się "+pchar.GenQuest.Noblelombard.Name+". Pamiętasz to? Musiał otworzyć depozyt na moje nazwisko. Kwota wynosi "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"... ";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Chodzi o twoje ... zadanie z niewolnikiem.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+NPChar.name+"Porozmawiajmy o twoim zadaniu.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+NPChar.name+"Porozmawiajmy o twoim zadaniu.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dobry dzień, "+NPChar.name+", porozmawiajmy o twoim zadaniu.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Przyszedłem, jak się umówiliśmy. Masz dla mnie jakieś zadanie?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Przyszedłem, jak obiecałem. Co powiesz na robotę?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+"Jak się miewasz? Masz dla mnie nowe zadanie?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Twoje zadanie zostało wykonane. Udało mi się znaleźć tych uciekinierów. Nie było to jednak takie łatwe.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+". Przyszedłem po nowe, zyskowne zadanie.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Złe wieści,"+npchar.name+"Nie udało mi się zdobyć brygantyny.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Spójrz,  "+npchar.name+". Ścigałem brygantynę, ale nie znalazłem żadnych dokumentów. Czy jesteś pewien, że tam były?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dobre wieści,"+npchar.name+"  Udało mi się wytropić tę brygantynę i znaleźć dokumenty. Oto one.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+" Czy przygotowałeś dla mnie nowe zadanie?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", udało mi się przechwycić ten tak zwany 'galeon'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = " "+npchar.name+"Przykro mi, ale nie mogłem wejść na ten galeon.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+"  Przyszedłem po moje pieniądze.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", twoja misja jest zakończona. Ten drań Gontier nie żyje, podobnie jak jego załoga.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Przykro mi, ale nie udało mi się złapać Francois Gontiera, chociaż śledziłem go do Tortugi. Udało mu się uciec ode mnie na korwecie.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry,"+npchar.name+"Opowiedz mi o tej nowej misji, którą dla mnie przygotowałeś.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("Nie powiedziałbym, że potrzebujesz pieniędzy lub chcesz pomnożyć swoje bogactwo. Co sprowadza cię do mego biura?","Czego chcesz tym razem?","Hm... jakie są twoje obawy?","Eh, "+GetAddress_Form(npchar)+", nie możesz sobie nawet wyobrazić, jak irytujący mogą być klienci...","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nie, dziękuję, tylko spaceruję i rozmawiam.","Znowu ja. Chciałem tylko z tobą porozmawiać.","Tak, to znowu ja. Nic poważnego, po prostu chciałem z tobą porozmawiać.","Tak, bycie bankierem czasami nie jest takie łatwe. Po prostu chciałem porozmawiać...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Chcę omówić nasze sprawy finansowe.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Interesują mnie klejnoty i niezwykłe idole lub kamienie szlachetne.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Potrzebuję pewnych informacji. Cóż, mam coś, o co chciałbym cię zapytać.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Przyniosłem ci dokumenty biznesowe z "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Jestem tu na rozkaz jednego człowieka. Jest gubernatorem "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" wysłał mnie tutaj. Muszę coś od ciebie odebrać.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Dzień dobry, zostałem zaproszony przez waszego syna."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Interesuje mnie, kto jest właścicielem tego dokumentu.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Chcę porozmawiać o długu twojego klienta. Nazywa się "+pchar.GenQuest.Noblelombard.Name+". Zastawił rodzinną relikwię. Reprezentuję tutaj jego interesy i mam prawo rozmawiać z tobą o jej zwrocie.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Mieliśmy spotkanie trzy miesiące temu i rozmawialiśmy o relikwii jednego człowieka. Jego imię to "+pchar.GenQuest.Noblelombard.Name+" Pamiętasz to? Musiał otworzyć lokatę na moje nazwisko. Kwota to "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Chodzi o twoje... zlecenie na niewolnika.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+NPChar.name+", porozmawiajmy o twoim zadaniu.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+NPChar.name+"Porozmawiajmy o twoim zleceniu.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+NPChar.name+", porozmawiajmy o twoim zadaniu.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Przyszedłem, jak się umówiliśmy. Masz dla mnie robotę?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Przyszedłem, jak obiecałem. Co z pracą?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+"Jak się masz? Masz dla mnie nowe zadanie?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Twoja misja została wykonana. Udało mi się znaleźć tych uciekinierów. Nie było to jednak takie proste.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+"Przyszedłem po nowe, zyskowne zadanie.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Złe wieści,"+npchar.name+"Nie udało mi się zdobyć brygantyny.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Spójrz,  "+npchar.name+". Ścigałem brygantynę, ale nie znalazłem żadnych dokumentów. Jesteś pewien, że tam były?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dobre wieści,"+npchar.name+"Zdołałem wytropić tamtą brygantynę i znaleźć dokumenty. Oto one.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+" Czy przygotowałeś dla mnie nowe zadanie?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", udało mi się przechwycić ten tak zwany 'galeon'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Bardzo mi przykro, ale nie mogłem wejść na ten galeon.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry, "+npchar.name+"Przyszedłem po moje pieniądze.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", twoja misja jest zakończona. Ten drań Gontier nie żyje, podobnie jak jego załoga.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Przykro mi, ale nie udało mi się złapać Francoisa Gontiera, chociaż śledziłem go do Tortugi. Udało mu się uciec na swoim korwecie.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Dzień dobry,"+npchar.name+"Opowiedz mi o tej nowej misji, którą dla mnie przygotowałeś.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Chcesz kupić trochę złotych dubloonów albo skrzyń na nie? Uwierz mi, to bardzo wartościowa inwestycja.";
			link.l1 = "Tak, to bardzo interesujące.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Czy chcesz handlować za pesos czy dublony?";
			link.l1 = "Dla pesos.";
			link.l1.go = "items";
			link.l2 = "Za dublony.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Zajmie mi to dużo czasu, aby przeczytać te dokumenty, a mój czas jest bardzo cenny.";
			link.l1 = "Być może, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos zrekompensuje twój czas?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Jak sobie życzysz. Żegnaj!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Pozwól, że rzucę okiem! Nie, nigdy wcześniej nie widziałem tego nazwiska. Pokaż je naszemu mistrzowi portu.";
				link.l1 = "Przykro mi, ale mieliśmy umowę! Obiecałeś mi opowiedzieć o tym kapitanie!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+" Mówią, że jest udanym przemytnikiem. Czy to właśnie chciałeś usłyszeć?";
				link.l1 = "Wydaje się, że tak...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"Te dokumenty są podpisane dla naszego kolonialnego okrętu patrolowego, a jego kapitan znany jest ze swoich mocnych zasad.";
				link.l1 = "Patrol? Pod dowództwem komendanta?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Obiecałem ci, że spojrzę na te dokumenty i nic więcej. Możesz iść.";
			link.l1 = "Dzięki... chyba.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "To twój wybór. Nasz komendant od dawna wykazuje spore 'zainteresowanie' tą jedną osobą. Masz już jakieś pomysły? A tu mamy listy przewozowe bez żadnych oznaczeń...";
			link.l1 = "Rozumiem. Moja wdzięczność!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"I jak już wspomniałem wcześniej, właściciel papieru to człowiek zasad i niezbyt przepada za lokalnymi przestępstwami.";
			link.l1 = "Rozumiem. Moja wdzięczność!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ach, zakładam, że jesteś kapitanem, który przywiózł mojego marnotrawnego syna z jego młodą żoną?";
				link.l1 = "Tak, to ja pomogłem im uciec.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ach, oto jesteś, mój dobroczyńco. Czekasz na nagrodę, jak mniemam?";
				link.l1 = "Twoje podziękowania byłyby przynajmniej w porządku...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Jestem naprawdę wdzięczny za pomoc mojemu dziecku i za to, że nie zostawiłeś go w tej kłopotliwej sytuacji. Proszę, pozwól mi podziękować Ci, jak najlepiej potrafię. Przyjmij tę skromną sumę i mały prezent ode mnie.";
			link.l1 = "Dziękuję. Z przyjemnością pomogłem tej młodej parze.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Dzięki? Za co? Ten głupiec przez pół roku był bezrobotny, a już zdążył znaleźć sobie dziewczynę! W jego wieku prowadziłem własny interes. Jest do wzięcia córka gubernatora, a on przyprowadza tu tę ladacznicę, Panie, wybacz mi, że to mówię! A teraz szuka mojego błogosławieństwa!";
			link.l1 = "Rozumiem, że nie wierzysz w uczucia?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Uczucia? Jakie uczucia? Jesteś dorosłym mężczyzną i też mówisz o tych uczuciach? Wstydź się, że jesteś stręczycielem młodzieży. Odebrałeś dziewczynę jej rodzicom i zniszczyłeś życie mojego syna. Nie dostaniesz ode mnie żadnych podziękowań. Żegnaj.";
			link.l1 = "Żegnaj zatem...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "Porozmawiajmy o tym. Słucham.";
				}
				else
				{
					dialog.text = "Uh, uh. Obawiam się, że muszę ci odmówić, "+GetAddress_Form(NPChar)+"Przykro mi, ale mój bank nie świadczy usług wrogom Hiszpanii.";
					link.l1 = "Pieniądze nie mają narodowości, señor bankierze.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Mhm, "+GetAddress_Form(NPChar)+"Muszę Cię poinformować, że Twój depozyt nie jest już ważny.";
							Link.l1 = "Na jakiej podstawie?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "Porozmawiajmy o tym. Słucham.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Jestem ci dłużny "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", jestem gotów zwrócić twoje pieniądze","Chcę spłacić dług.","  W końcu nadszedł czas, by spłacić dług.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Chcę pożyczyć kilka monet.","Naprawdę muszę zdobyć trochę pesos.","A może mała pożyczka?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Chciałbym zdeponować moje pieniądze na procent.","Czy zgodziłbyś się przechować kilka worków mojego srebra?","Czy mogę zostawić u was trochę srebra na nieszczęśliwy dzień?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Chcę zdeponować trochę dublonów na procent.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Przyszedłem odzyskać swoją inwestycję, w pesos."," Czas odzyskać moje srebro, które jesteś mi winien. ","Potrzebuję zwrotu mojej inwestycji w pesos z wszystkimi odsetkami.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("Chcę odzyskać swoją inwestycję w dublony.","Czas odzyskać moje złoto, które jesteś mi winien.","Potrzebuję z powrotem mojej inwestycji w dubloony z całym oprocentowaniem.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Pamiętam mój dług, ale nie jestem gotów go spłacić...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Moja pomyłka, nie mam z tobą żadnych spraw finansowych. Żegnaj.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Nie, nie mogę ci pomóc. Mogę jedynie przyjmować inwestycje w tym kłopotliwym miejscu. Możesz zainwestować srebrne peso lub złote dublony.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Chcę zainwestować pesos, porozmawiajmy o kwocie.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Chcę zainwestować dubloony. Wyjaśnijmy sumę.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Nie jestem zainteresowany.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Twoje imię to "+GetFullName(pchar)+", prawda? Masz "+RandPhraseSimple("zła reputacja ","zła reputacja ")+"i nie chcę z tobą robić interesów.";
				link.l1 = RandPhraseSimple("Nie może człowiek popełnić błędu?",RandSwear()+"Cokolwiek!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Och, zawsze jesteś mile widziany. Jaką sumę potrzebujesz?";
			Link.l1 = "Mała.";
			Link.l1.go = "Small";
			Link.l2 = "Umiarkowany.";
			Link.l2.go = "Medium";
			Link.l3 = "Jak największy.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Doskonale! Zawsze łatwiej jest zajmować się małymi sumami - mniejsze ryzyko dla obu stron. Mogę ci zaoferować "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "Zgoda. Co z twoimi odsetkami?";
			Link.l1.go = "Interest";
			Link.l2 = "To mi nie pasuje. Zmieńmy to.";
			Link.l2.go = "Loan";
			Link.l3 = "Przypuszczam, że lepiej nie popadać w długi. Żegnaj.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Nie ma problemu. Mam nadzieję, że "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" pomoże ci rozwiązać twoje problemy. To dość pokaźna suma.";
			Link.l1 = "Umowa stoi. Jakie są twoje odsetki?";
			Link.l1.go = "Interest";
			Link.l2 = "To mi nie pasuje. Zmieńmy to.";
			Link.l2.go = "Loan";
			Link.l3 = "Przypuszczam, że lepiej trzymać się z dala od długów. Żegnaj.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Cóż... to ryzykowne. Dobrze, jestem gotów udzielić ci pożyczki na "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". Mam nadzieję, że rozumiesz, kapitanie, to naprawdę pokaźna suma. Proszę, traktuj to poważnie.";
			Link.l1 = "Umowa stoi. A co z twoimi odsetkami?";
			Link.l1.go = "Interest";
			Link.l2 = "To mi nie pasuje. Zmieńmy to.";
			Link.l2.go = "Loan";
			Link.l3 = "Przypuszczam, że lepiej dla mnie trzymać się z dala od długów. Żegnaj.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest+"%% miesięcznie. Nie mogę zaoferować ci lepszych warunków na podstawie tego, co o tobie wiem."; 
			Link.l1 = "Pasuje mi to. Porozmawiajmy o czasie.";
			Link.l1.go = "Period";
			Link.l3 = "Przypuszczam, że lepiej trzymać się z dala od długów. Żegnaj.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "Uwzględniając moje informacje o tobie, "+Pchar.name+", poczekam na zwrot tej pożyczki przez "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+"Po tym podejmę pewne środki. Mam nadzieję, że to rozumiesz."; 
			Link.l1 = "Z radością przyjmuję twoje warunki... i twoje monety.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Przepraszam, ale to mi nie odpowiada. Żegnaj.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Jestem szczerze zadowolony. Ale pozwól, że cię ostrzegę. Zajmuję się tym od dawna i wiem, jak odzyskać swoje inwestycje. Więc jeśli kiedykolwiek miałbyś jakieś głupie pomysły, sugeruję je porzucić\nBez urazy, tylko ostrzeżenie.";
			Link.l1 = "Hm.. Dobrze. Żegnaj.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "To twój wybór, kapitanie. Moje oprocentowanie rośnie, a ty nie masz tyle czasu.";
			Link.l1 = "Nie martw się tym. Do zobaczenia.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Cudownie! Przyjdź do mnie, gdy potrzebujesz monet. Będę do Twojej dyspozycji w każdej chwili.","Moja wdzięczność. Zawsze to przyjemność mieć do czynienia z człowiekiem, który potrafi spłacać swoje długi na czas. Czasami coś się dzieje, i to rozumiem, wiesz... ale wolę, żeby problemy były rozwiązywane.","Och, miałem rację, ufając ci, "+GetAddress_Form(NPChar)+" Mam nadzieję, że to nie ostatni raz, kiedy korzystasz z moich usług. Może uda nam się nawet wynegocjować dla ciebie lepsze interesy, skoro teraz wiem, że jesteś uczciwym człowiekiem.");
			Link.l1 = LinkRandPhrase("Chcę pożyczyć trochę pieniędzy.","Naprawdę muszę zdobyć trochę pesos.","Co powiesz na małą pożyczkę?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Chciałbym zainwestować swoje pieniądze.","Czy zatrzymasz trochę pirackiego łupu?","Czy mogę zostawić ci trochę srebra na pechowy dzień?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Chcę zainwestować trochę dublonów na procent";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Żegnaj, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Widzę mądrego człowieka! Jaką sumę chciałbyś zainwestować?","Dobrze. Zaufaj mi, ta suma będzie tu na ciebie czekać bezpiecznie, z całymi odsetkami.","Widzę, że wiesz, co jest naprawdę ważne w tym życiu. Ile chciałbyś zainwestować?");
			link.l1.edit = 3;
			link.l1 = " ";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Żartujesz, co?";
				link.l1 = "Mój błąd.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hm, niestety nie masz tyle pieniędzy. Bądźmy poważni...";
				link.l1 = "Zgoda.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Dobrze. Mogę ci zaoferować... powiedzmy..."+Pchar.QuestTemp.Deposits.(sDepositType1).Interest+" %. Miesięcznie, oczywiście.";
			Link.l1 = "Pasuje mi to.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Lepiej zmienię sumę.";
			Link.l2.go = "Deposit";
			Link.l3 = "Wygląda na to, że to był zły pomysł... Żegnaj.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Wybacz mi, kapitanie, ale ta suma jest zbyt duża dla mojego kolonialnego banku. Nie będę w stanie wypłacić ci odsetek. A brak niezawodnej ochrony... Mam nadzieję, że rozumiesz. W każdym razie, maksymalna suma, jaką mogę od ciebie przyjąć, to "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Szkoda, muszę zatem znaleźć innego bankiera.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Możesz być teraz pewien, że nawet najsilniejsza burza nie pozostawi cię bez grosza.";
				Link.l1 = "Dobrze. Do zobaczenia.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Uwzględniając obiecane odsetki i upływ czasu, jestem ci winien "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... Czy jesteś pewien, że chcesz wziąć pieniądze?";
			Link.l1 = "Zdecydowanie. Daj mi to.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Chcę wypłacić część moich pieniędzy.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Masz rację. Zostawię to u ciebie na jakiś czas. Miłego dnia.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "Ileż to?";
			link.l1.edit = 4;
			link.l1 = " ";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "To był taki głupi żart, sir!";			
				link.l1 = "Cholera! Przepraszam... Zmieńmy sumę.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Nie masz tyle pieniędzy na swoim koncie.";			
				link.l1 = "Do diabła! Mój błąd. Zmieńmy sumę.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Wszystko? Dobrze, jak sobie życzysz. Oto twoje pieniądze.";			
				link.l1 = "Wdzięczność!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Dobrze. Weź to. Oto twoje pieniądze.";			
			link.l1 = "Dzięki!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... Tak trudno to stracić. Naprawdę przyzwyczaiłem się do tych pieniędzy. Wróć jednak ponownie.";			
			Link.l1 = "Jeśli zajdzie potrzeba. Żegnaj.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Widzę mędrca! Jaką sumę chcesz zainwestować?","Dobrze. Zaufaj mi, ta suma będzie tutaj bezpieczna, a odsetki się zgromadzą.","Widzę, że wiesz, co jest naprawdę ważne w tym życiu. Ile chciałbyś zainwestować?");
			link.l1.edit = 3;
			link.l1 = " ";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/20.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Żartujesz, co?";
				link.l1 = "Chyba się pomyliłem...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Chm, niestety nie masz tylu pieniędzy. Bądźmy poważni...";
				link.l1 = "Hm... dobrze.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Dobrze. Mogę Ci zaoferować... powiedzmy..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Miesięcznie, oczywiście.";
			Link.l1 = "Działa dla mnie.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "Lepiej zmienię sumę.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Przypuszczam, że lepiej zatrzymać moje złoto. Żegnaj.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Proszę wybaczyć, kapitanie, ale ta suma jest zbyt wielka dla mojego kolonialnego banku. Nie będę w stanie wypłacić ci odsetek. A brak zaufanej ochrony... Mam nadzieję, że to rozumiesz. W każdym razie, maksymalna suma, którą mogę od ciebie przyjąć, to "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Szkoda, muszę wtedy znaleźć innego bankiera.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Możesz być teraz pewny, że nawet najsilniejsza burza nie pozostawi cię bez grosza.";
				Link.l1 = "Miło. Żegnaj.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Z uwzględnieniem obiecanego oprocentowania i upływu czasu, jestem ci winien "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... Czy jesteś pewien, że chcesz wziąć pieniądze?";
			Link.l1 = "Absolutnie. Daj mi to.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Chcę wziąć część moich pieniędzy.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Masz rację. Pozwolę, aby to zostało u ciebie na jakiś czas. Miłego dnia.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "Ile?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Co za głupi żart, panie!";			
				link.l1 = "Cholera! Bardzo mi przykro... Zmieńmy tę sumę...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Nie masz tyle złota na swoim koncie, panie.";			
				link.l1 = "Cholera! Mój błąd. Zmieńmy sumę...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Wszystko? Dobrze, jak sobie życzysz. Oto twoje pieniądze.";			
				link.l1 = "Dzięki!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Dobrze. Weź to. Oto twoje pieniądze.";			
			link.l1 = "Wdzięczność!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... Tak trudno to stracić. Naprawdę się przyzwyczaiłem do tych pieniędzy. W każdym razie przyjdź ponownie.";			
			Link.l1 = "Zrobię to, jeśli zajdzie potrzeba. Żegnaj.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Jeszcze żyjesz? Chcesz może oddać mi moje pieniądze? Do diabła z tobą! Straciłem tyle pieniędzy, że nigdy mi ich nie zwrócisz! I nie zaznam spokoju, dopóki nie zobaczę twego bezwładnego ciała!";
            Link.l1 = "Chcę tylko załatwić sprawy w pokojowy sposób.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Bardzo dobrze, zobaczmy zatem! Wiedz, że i ciebie śmierć nie ominie!","Groźba?! Zobaczymy zatem, co zamierzasz zrobić...","Pieniądze nie są najważniejszą rzeczą w naszym życiu. Nie zadręczaj się zbytnio i nie zabijaj ludzi, no dalej, śmiem cię.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Precz! Mam nadzieję, że już nigdy cię nie zobaczę.";			
			Link.l1 = "... ";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Naprawdę? A jakie są twoje obawy?";
			Link.l1 = "Na dzisiaj jestem ci winien "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+" . A ja oferuję ci te pieniądze.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Oferuję ci mój dług, aby ponownie nawiązać z tobą dobre stosunki. To jest "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Teraz rozmawiamy! W końcu mogę z tobą robić interesy.";
			Link.l1 = "Dzięki. Już cię nie zawiodę.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ach, daj spokój! Jesteśmy poważnymi ludźmi, ty i ja, jesteśmy lepsi od tych idiotów, którzy są gotowi umrzeć za jednego dublona, ale nigdy nie próbują zrobić z niego dwóch\nSzukam człowieka, któremu mogę zaproponować poważny interes. Człowieka odważnego i aktywnego, uczciwego i punktualnego, ale nie obciążonego... eh... zbytnią skrupulatnością w kwestiach moralnych dylematów. I mam nadzieję, że to ty jesteś tym człowiekiem, którego szukam.";
			Link.l1 = "To zależy od tego, jakiego rodzaju 'umowę' mi zaproponujesz.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Bardzo dobrze, słuchaj zatem. Niewolnictwo to obecnie najbardziej dochodowy interes na Karaibach. Nie jestem plantatorem, ale mam zaufanych klientów\nWięc potrzebuję następującej liczby niewolników - "+pchar.questTemp.Slavetrader.iSlaveQuantity+"głów. Jestem gotów zapłacić Ci 250 pesos za każdą. Uwierz mi, to dobra cena. W sumie zarobisz "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+"pesos.";
			Link.l1 = "Nie, nie jestem handlarzem niewolników. Znajdź sobie innego pomocnika, który nie ma sumienia.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Kusząca oferta. Chciałbym to zrobić. Jak szybko będziesz potrzebować niewolników?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Meh, wydaje się, że nikt nie kwapi się ruszyć tyłka i zabrać złoto spod nóg. Jestem rozczarowany, bardzo. Żegnaj i nawet nie myśl o rozpowiadaniu plotek o naszej rozmowie. Moje ramię ma długi zasięg...";
			Link.l1 = "Twoje wpływy są 'brudne'... tak samo jak twój język. Żegnaj.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "Nie będę ograniczać twojego czasu, ale postaraj się wykonać swoją misję jak najszybciej. Popyt na 'czarne złoto' jest ogromny. Jeśli dobrze wykonasz swoją pracę, będę zlecał ci tego typu zadania od czasu do czasu w przyszłości.";
			Link.l1 = "Brzmi dobrze. Cóż, czekaj na dobre wieści.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Czy udało ci się zdobyć tę przesyłkę 'czarnej kości słoniowej'?";
            if (amount < 0)
			{
				Link.l1 = "Jeszcze nie. Tylko sprawdzam, czy nasze porozumienie jest nadal aktualne.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Mam. Wszystkie są w moim ładunku.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Wybornie. Moi ludzie się nimi zajmą... Nie martw się o celnika ani komendanta fortu. Prowadzę tu ogromną operację, więc nie spodziewaj się kłopotów i nikt cię nie oskarży o przemyt.";
			Link.l1 = "Wydaje się, że masz tu mocną pozycję... A co z moją zapłatą?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Oto jest. Nie mówię na darmo. Zostań ze mną, kapitanie, a wkrótce będziesz posiadał tyle złota, że potrzebny ci będzie galeon, by je przewieźć!";
			Link.l1 = "To byłoby świetne ha-ha... Co dalej?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Następny? Przyjdź tu znowu za trzy tygodnie. Przygotowuję teraz pewną transakcję i powinna być gotowa w tym czasie.";
			Link.l1 = "Bardzo dobrze, zgoda. Żegnaj.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Mam dla ciebie zadanie, ale twój statek jest zbyt słaby. Nie chcę, abyś nie wykonał misji, ani nie chcę wysyłać cię na pewną śmierć. Masz jeszcze czas, więc zdobądź większy statek, jak barkentynę, brygantynę, bryg lub flautę przynajmniej. Nie trać czasu!";
				Link.l1 = "Rozumiem, zajmę się tym. Do zobaczenia.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "W końcu! Czekałem na ciebie. Teraz przejdźmy od razu do rzeczy. Jak wiesz, w każdym interesie są konkurenci... i ja mam swoich. Ci chciwi i bezwzględni dranie zawsze są gotowi odebrać mi klienta! Właściwie chcę wyeliminować jednego z nich i jednocześnie zarobić trochę grosza.";
				Link.l1 = "Zamieniam się w słuch.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Najwyborniej. Słuchaj teraz. Ten łotr, zwany "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", przywiózł niewolników z Afryki i zarzucił kotwicę w "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+", znajduje się na wyspie zwanej "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". Czeka tam na przemytników. Jego galeon nazywa się '"+pchar.questTemp.Slavetrader.ShipName+"Ich umowa musi być zerwana za wszelką cenę!";
			link.l1 = "A co ze niewolnikami? Szkoda byłoby zatopić ich!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Po cóż miałbyś tak czynić? Nie ma potrzeby tego robić. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" ma złą reputację i nikt nie będzie zmartwiony jego zniknięciem. Wejdź na jego galeon, zabij go i upewnij się, że pozostanie martwy, przynieś mi ładunek, a ja go sprzedam. Według moich źródeł jest tam około półtora tysiąca niewolników.";
			Link.l1 = "Wow. To całkiem spora suma. A co z moją zapłatą?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Nie, sir, te intrygi nie są dla mnie. Dlaczego miałbym psuć swoje relacje z przemytnikami?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "„Cóż.. Wygląda na to, że się co do ciebie pomyliłem... Żegnaj i zapomnij o naszej rozmowie. I nie rozpowiadaj plotek o tym, co tu usłyszałeś. Jestem właścicielem tego miasta. A jeśli planujesz wejść na pokład ''"+pchar.questTemp.Slavetrader.ShipName+" dla siebie... Upewnię się, że skończysz na szubienicy. Przemyśl to.";
			Link.l1 = "Nie martw się, nie zgłoszę tego władzom i nie potrzebuję twojego galeonu. Żegnaj.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = " Biorąc pod uwagę, że podałem ci lokalizację ładunku i nie musisz żeglować w poszukiwaniu 'łupu', zapłata jest nieco niższa - 200 pesos za głowę. I wciąż to jest wielka suma - trzysta tysięcy pesos w przypadku sukcesu oraz statek.";
			Link.l1 = "Umowa stoi. Ile mam czasu?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho! Mówisz tak, jakby ci niewolnicy sami dopłynęli do mojego statku, licząc na to, że jak najszybciej dostaną się do mojego ładunku! Naprawdę chcesz, aby moi ludzie ryzykowali głowy za tak nędzną sumę? Zwiększ moją nagrodę, albo wychodzę z interesu.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Masz dwa tygodnie. Nie spóźnij się, bo przetransportuje swój ładunek i wszystko przepadnie.";
			link.l1 = "Muszę się wtedy pospieszyć. Oczekuj mnie z dobrymi wieściami.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Cóż, "+GetFullName(pchar)+", co z naszą misją? Twoja ponura twarz mówi mi, że zawiodłeś.";
			link.l1 = "Cholera, masz rację... Ja... no wiesz... spóźniłem się. Wyglądało na to, że już opuścił to miejsce, bo nikogo tam nie znalazłem. Musiałem płynąć z wiatrem całą drogę, do diabła...";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Cóż, "+GetFullName(pchar)+", co dziś złowiłeś? Powiedziano mi, że "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" karmi ryby! Ha-ha-ha!";
			link.l1 = "Tak, byłem tuż na czas! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+"przemycał niewolników na statek przemytników. Musiałem wejść na oba statki i wysłać ich prosto do Davy'ego Jonesa, więc teraz masz mniej konkurentów.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Tak, chyba się co do ciebie pomyliłem. Spóźniłeś się? A może po prostu byłeś zbyt przestraszony, by walczyć? Nieważne. To teraz nie ma znaczenia. Znikaj. Nie chcę cię więcej widzieć. Zapomnij o wszystkim, co tu widziałeś lub słyszałeś.";
			link.l1 = "Żegnaj zatem.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "Miałem co do ciebie rację - "+GetSexPhrase(" jesteś czarującym łotrem"," jesteś dzielną dziewicą")+"! Potrzebuję ludzi takich jak ty. Udało ci się wypełnić misję w doskonały sposób - przyprowadziłeś ponad półtora tysiąca niewolników! Niestety, mogę zapłacić tylko za tysiąc sześćset niewolników. Nie mam wystarczająco monet, aby zapłacić za resztę, więc musisz je sprzedać sam. Twoja nagroda to 320 000 pesos.";
				link.l1 = "Wdzięczność. Miło było robić z tobą interesy, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "Miałem rację co do ciebie - "+GetSexPhrase(" jesteś szarmancki opryszek"," jesteś dzielną Panną")+"! Potrzebuję ludzi takich jak ty. Odniosłeś sukces w swojej misji w doskonały sposób - przyniosłeś mi "+sTemp+"niewolnicy. Twoja nagroda to "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Wdzięczność. Miło robić interesy z tobą, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Przynajmniej przetrwałeś najtrudniejszą sytuację z honorem. Chociaż nagroda jest mniejsza, niż się spodziewałem, jestem wciąż zadowolony. Przyniosłeś "+sTemp+" niewolników. Twoja nagroda to "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "Podziękowania. Miło robić interesy z tobą, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Widzę... Rozumiem to, ale spodziewałem się znacznie więcej. Przyniosłeś tylko "+sTemp+" niewolników. Przynajmniej zniszczyłeś moich konkurentów, a to jest coś warte. Twoja nagroda to "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Moje podziękowania. Doceniam twoje zrozumienie, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Brzmi wspaniale, ale... hmmm. Wygląda na to, że się co do ciebie pomyliłem. Co przyniosłeś? "+sTemp+" niewolników? A co z resztą? I nie mów mi, że zatopiłeś ich. Jestem pewien, że sprzedałeś ich przemytnikom, a nawet gorzej - temu łajdakowi Lavoisierowi. Wynoś się, nie chcę mieć z tobą więcej do czynienia!";
				link.l1 = "Jak sobie życzysz, żegnaj.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Brzmi świetnie, ale... gdzie są nasi niewolnicy? Gdzie jest nasz ładunek? I nie mów mi, że go zatopiłeś. Musiałeś go sprzedać przemytnikom albo, co gorsza, temu łajdakowi Lavoisierowi. Zjeżdżaj, skończyłem z tobą.";
			link.l1 = "Jak sobie życzysz, do widzenia.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "To jeszcze nie koniec. Nikt nie śmie mnie oszukać! I zapłacisz za swoją próbę – upewnię się, że będziesz miał kłopoty. A teraz wynoś się stąd!";
			link.l1 = "Pierdol się i swój handel niewolnikami! Powinienem cię tu na miejscu pociąć, ale jestem lepszym człowiekiem, niż ty kiedykolwiek będziesz.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Wydaje się, że dobrze nam się razem wiedzie, "+pchar.name+" . Bardzo się cieszę. Zobacz się ze mną za miesiąc, a może znajdę pracę właśnie dla ciebie. Mam już kilka pomysłów.";
			link.l1 = "Jasne, zobaczymy się za miesiąc. Moja współpraca z tobą jest bardzo dochodowa.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "To przyniesie ci fortunę... Jeszcze jedno pytanie, "+pchar.name+", czy znalazłeś coś niezwykłego w kajucie galeonu?";
			link.l1 = "Nic specjalnego właściwie... Czy coś przegapiłem?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Masz na myśli tę starą klamrę, jakiś amulet 'skorpiona'?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Może tak, a może nie... To teraz nie ma znaczenia. Do zobaczenia za miesiąc. Żegnaj!";
			link.l1 = "Do zobaczenia, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Dokładnie! To jest fibula Medici... czy kiedykolwiek o nich słyszałeś? To oznacza, że naprawdę była w kajucie tego drania... Czy mogę rzucić okiem?";
			link.l1 = "Oczywiście, weź to.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "No cóż... Naprawdę tak jest. Posłuchaj, "+pchar.name+", sprzedaj mi to. Jestem gotów zapłacić sto tysięcy pesos.";
			link.l1 = "Sto tysięcy? Hm.. Zgadzam się. Proszę bardzo!";
			link.l1.go = "Buystatue";
			link.l2 = "Nie, nie sprzedam tego. Prawdziwej wartości tej fibuli nie można ocenić ani srebrem, ani złotem. Wiem, jak takie rzeczy działają.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Doskonałe! Cieszę się, że doszliśmy do porozumienia. Weź swoje pieniądze. Czekam na Twoją wizytę za miesiąc.";
			link.l1 = "Żegnaj, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "Widzisz, desperacko potrzebuję tej fibuli! Całkowicie się z tobą zgadzam, nie da się jej wycenić na pieniądze, żaden głupi sprzedawca nie zapłaci ci za nią nawet pięciu tysięcy. Ale wydaje się, że naprawdę wiesz, co ona potrafi, skoro odmawiasz jej sprzedaży za taką sumę.\n Czy mogę zaoferować ci wymianę, jeśli nie chcesz pieniędzy. Mam coś, co może cię zainteresować. Oto, spójrz. Niezwykła lekka zbroja! Zobacz sam! Oferuję ją w zamian za fibulę.\nNie jest zresztą unikalna. Wy, żeglarze, zawsze możecie znaleźć więcej dla siebie, a ja nie mogę. Zgadzasz się teraz?";
			link.l1 = "Heh... Przypuszczam. Daj mi zbroję i weź tę fibulę.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Nie, ta brosza ma dla mnie znacznie większą wartość niż ta zbroja. Zatrzymam ją dla siebie.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Znakomicie! Cieszę się, że doszliśmy do porozumienia. Teraz to twoja zbroja. Weź ją. Do zobaczenia za miesiąc. Żegnaj.";
			link.l1 = "Do zobaczenia, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Szkoda... Naprawdę szkoda. No cóż, weź to. Nie oceniam cię. Do zobaczenia za miesiąc. Żegnaj.";
			link.l1 = "Żegnaj.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Jesteś właśnie na czas, "+pchar.name+" Mam dla Ciebie misję, jeśli jesteś gotów ją rozpocząć.";
			link.l1 = "Oczywiście, jestem gotowy.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Doskonale! Teraz, przejdźmy do sedna. Czy słyszałeś najnowsze wieści?";
			link.l1 = "Hm, co masz na myśli? Codziennie dociera wiele nowin.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "To wszystko dotyczy naszego biznesu. Była to największa ucieczka niewolników w historii Nowego Świata! Ponad tysiąc dusz uciekło, a w międzyczasie zniszczyli i spalili kilka holenderskich placówek.";
			link.l1 = "Intrygujące. Kontynuuj.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "Ale oni nie tylko uciekli, jakoś udało im się opuścić wyspę! Żadnych śladów. Mathias Beck jest oburzony. Ale nie o to chodzi... Chodzi o to, że proszę cię, byś popłynął na Curacao, dowiedział się, co się tam wydarzyło, znalazł uciekinierów i pojmał ich\nI, oczywiście, byś uratował ich przed rękami holenderskiej sprawiedliwości, która byłaby dla nich bezlitosna. Zapłacę 300 pesos za głowę - słyszałem, że są bardzo dobrymi niewolnikami.";
			link.l1 = "Zrozumiano. Udaję się na Curacao. Czekaj na mnie z dobrymi wieściami.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Wiesz, nie wezmę tej misji. Nie pozbawię ludzi ich wolności. Zaryzykowali życie, by ją zdobyć. Zasłużyli na nią.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Jaka szkoda... Nie spodziewałem się tego po tobie... i to w najmniej odpowiednim momencie. Przypuszczam, że jest dla ciebie jasne, że nasze partnerstwo dobiegło końca. Żegnaj.";
			link.l1 = "Miłego dnia.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ha! Nie tylko odniosłeś sukces w swojej trudnej misji, ale przywiozłeś więcej niewolników, niż prosiłem - "+sTemp+" niewolnicy. Ale "+sNum+"niewolnicy nie uciekli z Curaçao. Płacę ci 100 pesos za głowę. Przypuszczam, że to ci odpowiada. Twoja nagroda to 330 000 pesos i "+FindRussianMoneyString(iSlaveMoneyH)+" za nadmiar, ha-ha.";
				link.l1 = "Ha! Z pewnością nie można cię oszukać. Zgadzam się, cokolwiek powiesz, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "Zakończyłeś tę niełatwą misję w najznakomitszy sposób i przyniosłeś mi "+sTemp+"niewolników. Twoja nagroda to "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Moje podziękowania. Przyjemność robić z tobą interesy, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Udało ci się w tej trudnej misji. Nagroda nie jest tak bogata, jak się spodziewałem, ale i tak jestem zadowolony. Więc przyniosłeś tutaj "+sTemp+" niewolników. Twoja nagroda to "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Dzięki. Miło robić z tobą interesy, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Znalazłeś ich? Hm... co mi przyniosłeś?"+sTemp+" niewolnicy? Gdzie jest reszta ładunku? I nawet nie próbuj mi mówić, że go zatopiłeś. Musiałeś go sprzedać przemytnikom, a może nawet gorzej - temu łajdakowi Lavoisierowi z Isla-Tesoro. Wynoś się stąd, nie mam już ochoty z tobą współpracować.";
				link.l1 = "Żegnaj.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Znalazłeś ich? Co ze niewolnikami? Gdzie jest nasz ładunek? I nawet nie próbuj mówić mi, że go zatopiłeś. Na pewno sprzedałeś go przemytnikom albo, co gorsza, temu łajdakowi Lavoisierowi z Isla-Tesoro. Wynoś się stąd, nie chcę już więcej z tobą współpracować.";
			link.l1 = "Żegnaj.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Naprawdę cię doceniam, "+pchar.name+"Naprawdę. Przyjdź tu za miesiąc, a przygotuję nowy interes, korzystny dla nas obojga.";
			link.l1 = "Również jestem zadowolony z naszej współpracy, "+npchar.name+"Do zobaczenia za miesiąc.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Przybywasz w samą porę, "+pchar.name+"  Szukam odważnego i niezbyt skrupulatnego żeglarza, ha-ha. Czy jesteś gotów podjąć się mojego zadania?";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "To dość proste tym razem. Dziś, pinasa '"+pchar.questTemp.Slavetrader.ShipName+" pod banderą "+NationNameGenitive(sti(npchar.nation))+" zarzucił kotwicę w "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" zatoka. Był załadowany dużą partią 'hebanów' z pomocą lokalnych przemytników. Dwa tysiące głów, nie mniej\nŻadnych żołnierzy na pokładzie, a kapitan to kupiec. W sumie, żadnego zagrożenia. Wejdź na statek i przynieś mi ładunek. 200 pesos za głowę, jak zwykle.";
			link.l1 = "Hm... To nie to samo, co ostatnia robota. Sugierujesz mi zaatakowanie statku własnego narodu!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Nie rozumiem, "+pchar.name+" Czy flaga statku ma znaczenie? Czy naprawdę cię to obchodzi?";
			link.l1 = "Czy tak? Nie, nie obchodzi mnie to, złoto nie ma narodowości. To było po prostu trochę niespodziewane...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Obchodzi mnie to. Nie chcę mieć "+NationNameAblative(sti(npchar.nation))+" wśród moich wrogów.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Jesteś poważny? Żartujesz sobie ze mnie, nie można nikomu ufać w tych czasach... W takim razie, odejdź. I zapomnij o wszystkim, co tu widziałeś lub słyszałeś!";
			link.l1 = "Do zobaczenia,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Cóż cię dziwi? Że nie obchodzi mnie narodowość monet? Zapewniam cię, że naprawdę mnie to nie obchodzi. Szczerze mówiąc, patriotyzm jest zgubny dla zawodowego bankiera, chyba że pragnie zbankrutować któregoś dnia\nAle dość filozofii. Przejdźmy do rzeczy - statek zostanie tutaj do północy, więc nie masz zbyt wiele czasu. Czy jesteś gotów, by przejść dalej?";
			link.l1 = "Tak, "+npchar.name+"  Wyruszam w drogę.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Znakomicie. Nie mam wątpliwości, że odniesiesz sukces w naszej misji. Powodzenia."+pchar.name+".";
			link.l1 = "Dzięki! Żegnaj.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Cóż, "+GetFullName(pchar)+", co z twoją misją? Twoja posępna twarz mówi mi, że zawiodłeś.";
			link.l1 = "Masz cholerną rację... Ja... Cóż... Byłem za późno. Byłem w tawernie, a kiedy wypłynąłem, nikogo nie było na morzu.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", proszę, uspokój się. To nie moja wina! Cholera, otrzymałem raport za późno... Doszło do zdrady! Jeden z moich zaufanych ludzi mnie zdradził!";
			link.l1 = "Dobrze, widzę, że mówisz prawdę. Masz szczęście, że kapitan pinasy powiedział mi, że nasz 'interes' został odkryty. Już bym cię zabił, gdyby się nie wygadał. Ale ty, cholerny wór pieniędzy, cały czas mówiłeś mi, że 'rządzisz tym miastem'!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "Zasadzka nie została zorganizowana przez lokalne władze, inaczej bym wiedział... "+pchar.name+", to nie jest odpowiednia pora na kłótnie. Oboje jesteśmy w niebezpieczeństwie, jeden z moich byłych kontrahentów wrobił nas\nUdało mi się dowiedzieć, że wszystkie zgromadzone dowody - paczka dokumentów - są transportowane do naszego gubernatora generalnego. Jeśli je dostanie, jesteśmy skończeni! Ty ucierpisz najbardziej, nawiasem mówiąc.";
			link.l1 = "Teraz widzę, co ten parszywy kapitan miał na myśli!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Słuchaj uważnie. Wciąż mamy szansę. Paczka została wysłana na brygantynie '"+pchar.questTemp.Slavetraderbrig.ShipName+"To jest jedyna rzecz, której jestem pewien. Dokumenty są dostarczane gubernatorowi generalnemu do jego rezydencji na "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". Musisz go przechwycić, wejść na pokład i znaleźć te kompromitujące dowody.";
			link.l1 = "Nie mam tu zbyt wielkiego wyboru. Módl się za mnie, za siebie i miej nadzieję, że uda mi się to złapać. Porozmawiamy o tym wszystkim ponownie, gdy wrócę. Nie myśl, że po prostu to odpuszczę.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Dostarczenie tej przesyłki to twój główny priorytet! Nie będę pewien swojego bezpieczeństwa, dopóki jej nie dostarczysz... Do diabła..."+pchar.name+"Wygląda na to, że mamy tutaj problem...";
			link.l1 = "Czego sobie życzysz?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Cholera... Liczyłem na ciebie, "+pchar.name+" . Dobrze więc. Ale nie będziemy już robić żadnych interesów. Jeśli nie będę w stanie przekupić śledczego, będę musiał uciekać. I nie polecam ci tu zostawać - żołnierze mogą przyjść w każdej chwili. Żegnaj.";
			link.l1 = "Żegnaj, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Byli tam. Cóż, nie możemy już prowadzić żadnych interesów, to już niebezpieczne. Żegnaj.";
			link.l1 = "Żegnaj, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Doskonale! Nie miałem co do Ciebie wątpliwości, "+pchar.name+" Proszę, daj mi te dokumenty, jestem zbyt zdenerwowany.";
			link.l1 = "Weź je.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Dobrze... Teraz jestem bezpieczny. Gubernator-general niczego się nie dowie, a ja już rozwiązałem wszystkie problemy z lokalnymi władzami, ale było to kosztowne, mówię ci.";
			link.l1 = "Brzmi świetnie, ale czy nie uważasz, że powinieneś mi zrekompensować moje kłopoty spowodowane twoimi bezmyślnymi działaniami?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Oczywiście, "+pchar.name+"Co więcej, jestem ci wiele winien. I naprawdę oczekuję kontynuacji naszego interesu. Ale proszę, zrozum mnie - wydałem ogromną sumę - lojalność gubernatora i komendanta kosztuje dużo. A musiałem zająć się tym morderstwem całego patrolu w moim banku...";
			link.l1 = "Chcesz powiedzieć, że nie zrekompensujesz mi kosztów?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Nie bądź taki surowy, "+pchar.name+". Naprawdę mam teraz problemy z pieniędzmi, więc oferuję ci inny rodzaj zapłaty.";
			link.l1 = "Słucham cię zatem.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Ja i mój towarzysz zostaliśmy złapani przez burzę blisko południowych wybrzeży Main rok temu. Nasze statki zostały wyrzucone na skały wybrzeża Boca de la Serpienta, choć szybko zatonęły, udało nam się przetransportować nasz ładunek na brzeg. Skrzynie wypełnione cennymi kamieniami i biżuterią. Zatoka wydawała się całkiem przytulna, więc bez trudu ukryliśmy skarby\nAle następnego ranka, gdy tylko burza się skończyła, zostaliśmy zaatakowani przez Indian. Tak zginęła większość ocalałych, w tym mój towarzysz. Ja i kilku marynarzy zdołaliśmy uciec na szalupie\nBezpiecznie dotarliśmy do Cumany, ale nie zaryzykowałem powrotu po skarby. Jestem pewien, że miejscowi dzicy nadal chronią swoje wybrzeże, jak i moje skrzynie. Ale ty możesz poradzić sobie z tą bandą czerwonoskórych\nBiżuteria, którą tam znajdziesz, jest wystarczająca, by pokryć wszystkie twoje wydatki, w tym ekspedycję na południowy Main.";
			link.l1 = "Hm... dobrze. W takim razie ruszam do Cumana";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Możesz być pewien, "+pchar.name+", że wszystko co powiedziałem, było prawdą. Spodziewam się zobaczyć cię za miesiąc. Mam już na myśli jeszcze jedną umowę i jak powinienem pomóc mojemu zachwianemu interesowi. Żegnaj.";
			link.l1 = "Do zobaczenia, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "I oto jesteś, "+pchar.name+". Doskonale, jak zwykle jesteś na czas. Chciałbym przekazać ci więcej informacji o karaibskim rynku niewolników, zanim dam ci kolejną misję. Czy wiesz, co oznacza słowo 'repartimiento'?";
			link.l1 = "Hm, nie, "+npchar.name+", nie wiem. Ale przypuszczam, że chodzi o zabranie czegoś komuś. Czy mam rację?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Zaskakujesz mnie. Czego się po mnie spodziewałeś? Odejdź!";
			link.l1 = "Nielegalny biznes jest zbyt trudny dla mojej moralności. Zwłaszcza handel niewolnikami.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Już prawie masz to,"+pchar.name+"Zabieranie komuś wolności. Repartimiento to podstępny i legalny sposób na zniewolenie lokalnych Indian. Tak to ujmując. Władze hiszpańskie używają tego przeciwko rdzennym mieszkańcom Kontynentu. Czy jesteś zainteresowany dowiedzeniem się więcej?";
			link.l1 = "Dlaczego nie?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Przedstawiciele hiszpańskiej korony odwiedzają osiedla indiańskie. Używając cynicznych oszustw i bezpośrednich gróźb, zmuszają Indian do kupowania wszelkiego rodzaju śmieci, jak zgniłe mięso i stare brzytwy, po bajecznych cenach. Na kredyt\nJakiś czas później, powiedzmy rok, przedstawiciele wracają i żądają zapłaty. Jeśli Indianie nie mogą się wywiązać z długu, co zazwyczaj ma miejsce, Hiszpanie zabierają część ich mężczyzn zdolnych do pracy, rzekomo na jakiś czas i by 'nauczyć ich uprawy ziemi'\nJak rozumiesz, nigdy nie wracają do swoich osiedli. W ten sposób nasi ufni czerwonoskórzy trafiają na plantacje cukru i do fabryk sekwoi.";
			link.l1 = "Cholera... naprawdę... Co robią Indianie w tej sprawie? Opierają się, gdy Hiszpanie ich zniewalają? Czy po prostu nie rozumieją, co się dzieje?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Przypuszczam, że zawsze to przewidują, ale tylko nieliczni odważają się otwarcie sprzeciwić, zwłaszcza gdy Hiszpanie pokazują papier z odciskiem palca wodza. Oczywiście, takie taktyki zazwyczaj stosuje się wobec pokojowych plemion jak Arawakowie czy Miskito. Taki trik nie zadziała z wojowniczymi Itza czy Akawojami\nCóż, porozmawiajmy o twojej misji.";
			link.l1 = "Już czuję zapach wielu monet! Słucham cię, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Wkrótce z Caracas wypłynie ciężki galeon. Nazywa się "+pchar.questTemp.Slavetrader.ShipName+". Zawiera ogromną ilość niewolników - około 3000 ludzi - Indian Orinoko, pojmanych zgodnie z polityką repartimentos. Galeon płynie do Santiago, plantacje cukru na Kubie potrzebują wielu pracowników. Musisz przejąć galeon z jej ładunkiem. Wziąłbym ze sobą co najmniej dwa statki, gdybym był tobą, mówią, że galeon jest najlepszy w swoim rodzaju. Stawki płatności pozostają zwyczajne - 200 pesos za głowę.";
			link.l1 = "Heh! Brzmi dobrze. Zgadzam się.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Wiesz, że nie podoba mi się to twoje repartimiento. Jest zbyt cyniczne. Nie zamierzam tego robić.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Życzę ci więc powodzenia. Wiedz, że kapitan tego galeonu to bardzo doświadczony i wykwalifikowany żeglarz wojenny. To nie będzie łatwa walka, więc przygotuj się. Nie trać czasu, zajmie mu piętnaście lub dwadzieścia dni, aby dotrzeć "+sTemp+" Santiago. Postaraj się go nie przegapić, choć ta galeona jest naprawdę trudna do przeoczenia\nTak! Prawie zapomniałem! Na statku jest mnóstwo indiańskich bibelotów, czerwonoskórzy często spłacają swoje długi swoimi kultowymi przedmiotami i rzemiosłem. Przynieś mi cokolwiek wyjątkowego, co znajdziesz, zapłacę ci sowicie za każdy cenny przedmiot, który przyniesiesz.";
			link.l1 = "Rozumiem.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Cóż, "+pchar.name+", to była moja ostatnia nadzieja... Dlatego właśnie zaproponowałem ci tę robotę. Nikt inny, tylko ty jesteś w stanie to zrobić... i widzę, że ty także nie jesteś w stanie. Powiedzmy więc pożegnania. Po ostatniej porażce i tych wszystkich plotkach, wszyscy moi klienci odeszli. I jestem prawie bankrutem, być może muszę opuścić to miasto. Nie obwiniam cię - ta praca była zbyt trudna. Eh... Żegnaj,"+pchar.name+".";
			link.l1 = "Przykro mi bardzo, "+npchar.name+", to zaszło za daleko. Naprawdę mi przykro. Być może wszystko się ułoży. Do widzenia.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Fuh, teraz czuję się lepiej... Miałem rację, ufając tobie... Skąd ta ironia? Co się stało?";
				link.l1 = "Szanowny panie, to nie był galeon... ani bardzo duży galeon... Do diabła! To był okręt liniowy! A nawet mnie nie ostrzegłeś! Ale udało mi się go abordażować. Mam "+sTemp+"niewolników i jestem gotów przekazać ich tobie. Zgodnie z naszą umową jesteś mi winien - "+FindRussianMoneyString(iSlaveMoney)+"Byłoby wspaniale otrzymać jakieś zadośćuczynienie za twoje błędne informacje.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Znalazłeś galeon? A co ze niewolnikami? Ma ich być trzy tysiące i ani jednego mniej! Do diabła, wszyscy to szczury i zdrajcy! Nie spodziewałem się tego po tobie... byłeś moją ostatnią nadzieją\nBardzo dobrze... Przysięgam, wydam każdy pozostały mi grosz, by cię zniszczyć, by cię zabić! Cała flota "+NationNameGenitive(sti(npchar.nation))+" będzie cię ścigać! Wynoś się stąd!";
				link.l1 = "Cóż...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "Ho, nie mów! Przysięgam, nie miałem pojęcia. Miał płynąć ciężki galeon, a nie przeklęty okręt liniowy! Wygląda na to, że zmienili plany w ostatniej chwili... Ale jednak ci się udało!\nCałkowicie zgadzam się z tobą w kwestii pieniędzy i rekompensaty twoich wydatków, problem w tym, że nie posiadam takiej sumy w tej chwili. Wiesz o moich ostatnich kłopotach... Ale nie denerwuj się, "+pchar.name+", na miłość boską. Daj mi ładunek, a ja go sprzedam, mój klient już czeka\nBędę miał całą sumę za pięć dni, więc dostaniesz to, na co zasługujesz. Możesz na mnie polegać. Tu, weź całą gotówkę, którą teraz mam.";
			link.l1 = "Hm... Spodziewałem się otrzymać pieniądze teraz. Życzyłbym sobie, żebyś wiedział, przez jaką walkę musiałem przejść! Ach, nieważne... Będę ci współczuł. Ale pamiętaj, że jeśli spróbujesz mnie oszukać, znajdę cię nawet w Europie!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Wiesz, "+npchar.name+", do diabła z tobą! To nie była umowa. Nie możesz sobie nawet wyobrazić, z jaką walką musiałem sobie poradzić. Biorę wszystkich niewolników dla siebie i sprzedaję ich bez twojego pośrednictwa.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "A teraz mówisz! Wygląda na to, że niczego nie podejrzewający "+npchar.name+" była tylko krową do dojenia, wystarczy proste opóźnienie, byś mnie wydymał i zaczął operację na własną rękę. Wygląda na to, że zapomniałeś, że to ja dałem ci tę robotę i cynk o łupie\nBardzo dobrze... Przysięgam, że wydam każdą monetę, która mi została, by cię zniszczyć, by cię zabić! Cała flota "+NationNameGenitive(sti(npchar.nation))+"będzie cię ścigać! Znikaj mi z oczu!";
			link.l1 = "Nie waż się mnie straszyć, pusty skarbiec. Zatopię wszystkie twoje floty i nakarmię nimi kraby.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Dziękuję za zrozumienie, "+pchar.name+". Obiecuję, że wszystko będzie w porządku, nie ma potrzeby grozić\nWeź to jako zaliczkę. Piętnaście skrzyń. Pięć z nich posłuży jako rekompensata za szkody moralne. Przyjdź do mnie za pięć dni, żeby odebrać resztę.\nNie zapomnij przynieść wszystkich indiańskich przedmiotów, które znalazłeś na statku... jeśli w ogóle je znalazłeś, oczywiście. I tak nie mam czym ci za nie zapłacić.";
			link.l1 = "Za pięć dni,"+npchar.name+"W ciągu pięciu dni...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "Jak obiecałem, "+pchar.name+", jestem gotów ci zapłacić. Niewolnicy sprzedani, klient zadowolony, a my również. Po odliczeniu zaliczki twoja nagroda wynosi"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+" Proszę, weź swoje pieniądze.";
			link.l1 = "Znakomicie, "+npchar.name+"Miło mieć do czynienia z człowiekiem, który potrafi dotrzymać słowa...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Zawsze możesz ufać mojemu słowu, "+pchar.name+". Nigdy nie dałem ci powodu, by we mnie wątpić. Partnerzy muszą być ze sobą szczerzy, to klucz do biznesu\nPorozmawiajmy teraz o artefaktach indiańskich. Pokaż mi, co masz, nie każ takiemu kolekcjonerowi jak ja czekać.";
			link.l1 = "Hm... Spójrz.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Tak! Wspaniale! Złoty rytualny nóż! To rzadkość. Zawsze chciałem mieć coś takiego w swojej kolekcji. Oferuję ci za niego 30 000 lub amulet 'Ehecatl' w zamian. Mam ich zresztą dwa.";
				link.l1 = "Wziąłbym pieniądze.";
				link.l1.go = "BG_money";
				link.l2 = "Wezmę amulet 'Ehecatl' w zamian.";
				link.l2.go = "BG_change";
				link.l3 = "Zabiorę ten nóż ze sobą.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Zobaczmy... Niestety, nie masz nic interesującego dla mnie.";
				link.l1 = "Cokolwiek powiesz.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Wspaniale. Bierz swoje 30 000, a ten indiański nóż jest teraz mój.";
			link.l1 = "Dobrze. I to wszystko, co cię interesuje...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Znakomicie! Oto twój amulet, a ten indiański nóż jest teraz mój.";
			link.l1 = "Dobrze. I to wszystko, czym jesteś zainteresowany...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Jak zwał, tak zwał. Ale to i tak wielka szkoda...";
			link.l1 = "Dobrze.   I to wszystko, czym jesteś zainteresowany...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Zaczekaj! Niech spojrzę jeszcze raz...";
			link.l1 = "Jasne. Chodź, zerknij i wybierz, co chcesz.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "To! I nawet tego początkowo nie zauważyłem. Interesuje mnie ta kość z pierścieniem z miedzi. Tak interesująca rzecz, powiem ci... Mogę ci zapłacić 20 000 pesosów lub dać ci amulet 'Cimaruta' w zamian.";
				link.l1 = "Wezmę pieniądze.";
				link.l1.go = "PF_money";
				link.l2 = "Wziąłbym amulet 'Cimaruta' w zamian.";
				link.l2.go = "PF_change";
				link.l3 = "Zatrzymałbym ten artefakt przy sobie.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Nie... nie masz tu niczego więcej, co by mnie interesowało.";
				link.l1 = "Cokolwiek!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Wyśmienicie! Oto twoje 20 000 pesos, a ta kość jest teraz moja.";
			link.l1 = "Miło. Czuję się dobrze z naszą umową.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Znakomicie! Oto twój amulet, a ta kość jest teraz moja.";
			link.l1 = "Miło. Czuję się dobrze z naszą umową.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Co za szkoda, tak czy inaczej...";
			link.l1 = "Potrzebuję tej kości dla siebie, bardzo mi przykro.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Cóż... abordażując galeon, o przepraszam, okręt liniowy, uratowałeś mnie. Naprawdę doceniam nasze partnerstwo, "+pchar.name+"Jesteś moim najlepszym agentem.";
			link.l1 = "Jestem zaszczycony. Znacznie przeceniasz moje osiągnięcia...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Jestem całkowicie poważny. I poproszę cię o wykonanie kolejnej misji ze względu na twoje niezwykłe umiejętności i ponieważ ci ufam.";
			link.l1 = "Heh! Zaskakujące! Słucham. Gdzie jest kolejny galeon z niewolnikami?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "Tym razem sprawa nie dotyczy niewolników. Zaskoczony? Zapłacę ci dobrze za tę misję... Bardzo dobrze.";
			link.l1 = "Przejdźmy od razu do interesów.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Ten interes jest powiązany z niedawnymi wydarzeniami, w których również brałeś udział... Jak zapewne wiesz, prowadzę dość nielegalny biznes - handel niewolnikami. Możesz też wiedzieć, że zatrudniam korsarzy takich jak ty do wszelkiego rodzaju zadań\nJeden z moich ludzi zdradził mnie niedawno z nieznanych powodów. Zebrał dowody i sporządził raport dla władz. Miałeś przyjemność zobaczyć konsekwencje na własne oczy. Statek z żołnierzami dotarł tutaj... znasz resztę\nZajęło mi sporo wysiłku, aby rozwiązać tę sytuację. Jak zapewne rozumiesz, nie mogę pozwolić, aby ta zdrada pozostała bez odpowiedzi. Poza tym, nie mogę żyć i pracować spokojnie, wiedząc, że szczur wciąż żyje. Wysłałem łowców nagród, ale nie ma jeszcze żadnego rezultatu\nProszę cię, abyś osobiście zajął się tą sprawą. Tym bardziej, że jego działania również na ciebie wpłynęły.";
			link.l1 = "Hm... ten drań musi zawisnąć na rei! Powiedz mi więcej o nim i oczywiście o mojej zapłacie za tę robotę.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Nie martw się o to. Zapłacę dużo za jego eliminację i nie mówię tylko o pieniądzach. Nie pożałuję najlepszych przedmiotów z mojej kolekcji. Porozmawiajmy o tym człowieku. Nazywa się Francois Gontier\nWie o moim polowaniu, więc sprzedał swoją fregatę, aby ukryć swoje ślady. Moi koledzy powiedzieli mi, że widziano go w Panamie. Wierzę, że powinieneś zacząć poszukiwania właśnie tam.";
			link.l1 = "Cóż, w takim razie ruszam w drogę.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Życzę ci więc powodzenia. Wiedz, że ten Gontier to bardzo doświadczony żeglarz i ma załogę złożoną z bezwzględnych rzezimieszków. Nie ma nic do stracenia, więc będzie walczył w bardzo desperacki sposób.";
			link.l1 = "Nie boję się takich ludzi jak on, ale rozważę, co powiedziałeś. Żegnaj, i bądź pewien, że dopadnę go nawet w piekle.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Wyśmienicie! Teraz może pisać swoje raporty do meduz. Nikt nie odważy się ze mną zadzierać. Dzięki tobie, "+pchar.name+", jesteś nieocenionym człowiekiem.";
			link.l1 = "Dziękuję, "+npchar.name+", za tak pozytywną ocenę moich działań. Co z moją zapłatą?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Oczywiście. Zapłaciłbym odpowiednią cenę za tak trudne zadanie. Najpierw przedstawiam ci tę doskonałą lunetę.";
			link.l1 = "Och, cóż za dar!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Oprócz tego, oto 100 000 pesos jako twoja główna płatność i 50 000 jako rekompensata za twoje własne koszty.";
			link.l1 = "Dzięki, "+npchar.name+"Powtarzam, że to prawdziwa przyjemność mieć z tobą do czynienia.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Będę czekać na ciebie za miesiąc, jak zawsze. To bardzo poważna sprawa i będziesz potrzebować dobrze wyposażonej eskadry. Proszę, abyś to zrozumiał i dobrze się przygotował. Jeśli mój plan się powiedzie, będziemy bogaci.";
			link.l1 = "Dobrze,"+npchar.name+". Wrócę, gdy będę gotowy.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Szkoda, co za wstyd... Cóż, nie martw się, nie jesteś pierwszym, którego ten łotr oszukał. Kiedyś go dorwę, tak czy inaczej.\nCo do ciebie, przyjdź do mnie za miesiąc. To będzie coś dużego, więc zbierz dobrze wyposażoną i uzbrojoną eskadrę. Proszę, podejdź do tego poważnie i zrób wszystko, co w twojej mocy, aby się przygotować. Jeśli mój plan się powiedzie, będziemy bogaci.";
			link.l1 = "Dobrze, "+npchar.name+"  Wrócę, gdy będę gotowy.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Jesteś w samą porę, "+pchar.name+"! Byłem bliski zmartwienia się, miałem zamiar wysłać człowieka, by cię znalazł\nZabierajmy się do pracy! Twoja misja jest teraz naprawdę wielka i ryzykowna, ale nagroda jest adekwatna. Otrzymasz ponad milion pesos po zakończeniu zadania.";
			link.l1 = "Teraz rozmawiamy! Słucham, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "Zniewoleni Indianie byli przenoszeni małymi grupami do Hawany z całego kontynentu, a także kilka galeonów przybyło z Afryki i zostało rozładowanych. Obecnie za wysokimi murami fortu w Hawanie znajduje się prawie pięć tysięcy niewolników.";
			link.l1 = "Mam przeczucie, że umowa dotyczy szturmu na Hawanę.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Masz dobre przeczucie, "+pchar.name+". Dokładnie o to chcę cię prosić. Ciebie i tylko ciebie. Wątpię, by którykolwiek z moich agentów był w stanie to zrobić\nWierzę, że się zgadzasz?";
			link.l1 = "Szczerze mówiąc, "+npchar.name+",   jestem teraz trochę oszołomiony. Nie miałem pojęcia, że twoja działalność jest tak... na dużą skalę. Pewnie, jestem na pokładzie. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Wiesz co, "+npchar.name+", to już przesada. Mam dość tych twoich niespodzianek. Następnym razem twoja chciwość każe mi wypowiedzieć wojnę Hiszpanii i będę musiał walczyć z nimi sam. Jeśli naprawdę potrzebujesz tych niewolników, to szturmuj Hawanę sam.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Nie spodziewałem się tego po tobie... Cholera, co mam powiedzieć mojemu klientowi? Dobrze. To twój wybór i muszę znaleźć nowego partnera. Żegnaj, "+pchar.name+"   I nie skorzystam z waszych usług w przyszłości. Pamiętajcie, że odrzuciliście umowę, która mogła uczynić wasze potomstwo bogatym aż do siódmego pokolenia.";
			link.l1 = "Nie możesz zdobyć wszystkich pieniędzy na świecie, a bierzesz więcej, niż możesz przełknąć. Żegnaj, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Wiedziałem, że się zgodzisz. Teraz posłuchaj szczegółów. Fort w Hawanie zawsze był trudnym celem, ale teraz jest jeszcze trudniejszy\nDwa okręty liniowe strzegą wybrzeży Kuby i najpierw musisz się z nimi uporać, zanim szturmem weźmiesz fort...";
			link.l1 = "Rozumiem. To nie pierwszy raz, kiedy walczę z okrętami liniowymi, ha-ha. Ile mam czasu?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Nie za wiele. Nie więcej niż trzy tygodnie, a potem niewolnicy zostaną przeniesieni do hiszpańskich posterunków na Kubie. Musisz się pospieszyć. ";
			link.l1 = "Nie traćmy więc czasu. W drogę!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Chwileczkę!"+pchar.name+", nigdy nie mieliśmy żadnych nieporozumień ani niezgodności. Niemniej jednak chcę, abyś wiedział, co się tutaj dzieje. Liczę na ciebie, a klient liczy na mnie\nZainwestowaliśmy dużo wysiłku i pieniędzy w tę operację. Każdy pojedynczy niewolnik, wszystkie pięć tysięcy, muszą być dostarczone do mnie\nW przeciwnym razie podejmiemy bardzo radykalne kroki przeciwko tobie. Bez urazy, to tylko ostrzeżenie. ";
			link.l1 = "Nie martw się, "+npchar.name+", Rozumiem, czym jest interes, dlatego powinieneś również pamiętać, aby mi zapłacić, gdy je dostarczę. Żegnaj.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Cóż.. A co z nagrodą za twoje zwycięstwo?";
				link.l1 = "Mam "+sTemp+" niewolnicy.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "No cóż, no cóż. Czy zapomniałeś, co powiedziałem? Musiałeś przyprowadzić mi tutaj nie mniej niż pięć tysięcy niewolników, a masz "+sTemp+" Dlaczego tak jest?";
				link.l1 = "Hmm.. Część z nich nie przetrwała drogi z Hawany... jedzenie i lekarstwa się kończyły.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "No cóż... Chcesz mnie oszukać? Zapomniałeś, co powiedziałem? Gdzie są moi niewolnicy, pytam cię! Gdzie oni są?!";
			link.l1 = "Hm.. Cóż, widzisz...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Dobrze. Nie potrzebuję twoich wyjaśnień. Mieliśmy umowę i dam ci tydzień na zdobycie nie mniej niż pięciu tysięcy niewolników. W przeciwnym razie będziesz miał wiele problemów.";
			link.l1 = "Dobrze, dobrze, tylko się odpręż, zdobędę je dla ciebie.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Znakomicie! Wykonałeś moje zadanie jak zawsze. Jestem z ciebie bardzo zadowolony.";
			link.l1 = "Ja również... Ale byłbym jeszcze bardziej zadowolony, gdybym otrzymał moje pieniądze za ładunek.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Jestem z tego bardzo zadowolony. Spóźniłeś się, ale wykonałeś moje zadanie w najwyborniejszy sposób.";
			link.l1 = "I teraz chcę dostać pieniądze za ładunek.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Oczywiście. Sprzedam niewolników mojemu klientowi, on zapłaci, a ty dostaniesz swoje monety. Tak jak ostatnim razem. Zobaczmy, przyprowadziłeś tutaj "+sTemp+"niewolników. Kwota to "+FindRussianMoneyString(iSlaveMoney)+"Przyjdź tu po zapłatę za tydzień.";
			link.l1 = "Dobrze, "+npchar.name+", mamy umowę. Będę tu za tydzień. Ale bądź bardzo ostrożny...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = " "+pchar.name+", proszę, nie. Jesteśmy partnerami i nie ma miejsca na oszustwo i brak zaufania między nami. Obiecałem ci dużo monet i je otrzymałeś. Obiecałem ci interesujące zadania i je również otrzymałeś. Zawsze kompensowałem twoje koszty nawet w najciemniejsze dni dla mojego biznesu. Czy kiedykolwiek nie dotrzymałem słowa?";
			link.l1 = "Hmm... Nie... Po prostu chcę dostać zapłatę, to wszystko.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Zobacz teraz..."+pchar.name+", jesteś moim najlepszym agentem i liczę na dalsze interesy z tobą w przyszłości. ";
			link.l1 = "Dobrze, "+npchar.name+"  Ale musisz mnie zrozumieć - milion peso to ogromna suma.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Rozumiem cię doskonale, ale najpierw muszę sprzedać niewolników, a dopiero potem otrzymam pieniądze.";
			link.l1 = "Dobrze. Myślę, że się zrozumieliśmy.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Znakomicie. Do zobaczenia za tydzień. A teraz muszę się przygotować i wyruszyć, by handlować z moim klientem.";
			link.l1 = "Nie będę cię zatem niepokoił. Do zobaczenia za tydzień, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "Co ja tu robię? Cóż... to mój bank. Kupiłem go dwa dni temu. Jesteś moim pierwszym klientem i mogę zaoferować ci bardzo kuszące warunki kredytu...";
			link.l1 = "Pierdolić kredyty! Gdzie jest "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Proszę się uspokoić! On uciekł już dawno temu.";
			link.l1 = "Jak?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Nie wiesz? Zniknął tydzień temu. Okazało się, że zabrał wszystkie inwestycje swoich klientów. Mówią, że nawet gubernator ucierpiał. Ten dom został opuszczony, a ja go kupiłem od kolonii.";
			link.l1 = "Zniknął? Jak?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "Słyszałem, że uciekł z naszej kolonii... Rozumiem, że jest ci coś winien. Dużo?";
			link.l1 = "Ponad milion! Ale dorwę tego szczura prędzej czy później! Gdzie on się podział? Jak się nazywa jego statek?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Nikt niczego nie zauważył. Poważnie. Po prostu zniknął. Statek o nazwie 'Mauritius' lub 'Maurdius' odpływał tego dnia, być może użył go, aby uciec.";
			link.l1 = "Cholera! A zaufałem temu łajdakowi! Cuchnął zdrajcą już od pierwszego dnia! A ja byłem na tyle głupi, by uwierzyć, że jesteśmy prawdziwymi partnerami! Ale sprawię, że pewnego dnia pożałuje... Dobrze,"+npchar.name+", Przepraszam za moje zachowanie... Jeśli jesteś dobrym człowiekiem, w przyszłości na pewno się z tobą skontaktuję, ale na razie, żegnaj.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "To w porządku. Rozumiem. Jeśli będziesz potrzebować pieniędzy lub zechcesz zainwestować, zawsze jestem do twojej dyspozycji.";
			link.l1 = "Dzięki. Ale lepiej zatrzymam moje pieniądze przy sobie. Do zobaczenia.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Naprawdę? Wydaje się, że sam nie chce ze mną rozmawiać... Dobrze, porozmawiajmy zatem z tobą o tej sprawie. "+pchar.GenQuest.Noblelombard.Name+" jest mi winien "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" a także moje odsetki - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+"   przez trzy miesiące. Jeśli nie zobaczę pieniędzy w najbliższym czasie, to sprzedam jego relikwię i nie obchodzi mnie jej wartość dla niego. Interes to interes.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Świetnie! W takim razie zamierzam natychmiast spłacić całą sumę wraz z odsetkami - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Sam odbierze swoją relikwię. Oto twoje pieniądze.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Mój klient będzie miał pieniądze za trzy miesiące. Zawrzyjmy umowę, zapłacę ci odsetki za ostatnie trzy miesiące i za następne trzy miesiące."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+" A sam dług zostanie spłacony później.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Mój klient będzie miał pieniądze za trzy miesiące. Co powiesz na to, że zapłacę ci odsetki za ostatnie trzy miesiące, a ty poczekasz, aż mój klient będzie miał wystarczająco pieniędzy?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Ten rarytas kosztuje fortunę! Wygląda na to, że mój klient sam musi za to zapłacić.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Doskonale! Wszystko poszło dobrze, dostałem moje pieniądze i "+pchar.GenQuest.Noblelombard.Name+" odzyska swój relikt.";
			link.l1 = "Miło robić z tobą interesy, "+npchar.name+"Żegnaj teraz.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm.. Dobrze. To mi pasuje. Ale jeśli "+pchar.GenQuest.Noblelombard.Name+" nie znajdzie pieniędzy w ciągu trzech miesięcy, to nie przedłużę terminu ponownie. Upewnij się, że o tym wie.";
				link.l1 = "Zrobię to! Cieszę się, że doszliśmy do porozumienia. Żegnaj teraz.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "Nie. To nie zadziała. Potrzebuję całej sumy i to przed zachodem słońca. Upewnij się, że twój 'klient' o tym wie. Nie mam ci nic więcej do powiedzenia.";
				link.l1 = "Hm... dobrze. Szkoda, że nie chcesz iść na kompromis.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm.. Dobrze. Zgadzam się tylko z szacunku do twojego klienta. Ale jeśli "+pchar.GenQuest.Noblelombard.Name+"nie znajdzie pieniędzy w ciągu trzech miesięcy, to nie przedłużę terminu ponownie. Upewnij się, że o tym wie.";
				link.l1 = "Zrobię to! Cieszę się, że udało nam się dojść do porozumienia. Żegnaj teraz.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "Nie. To nie zadziała. Potrzebuję całej sumy i to przed zachodem słońca. Upewnij się, że twój 'klient' o tym wie. Nie mam ci nic więcej do powiedzenia.";
				link.l1 = "Hm... dobrze. Szkoda, że nie chcesz pójść na kompromis.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "Nie mówisz poważnie! "+pchar.GenQuest.Noblelombard.Name+" nie otworzył depozytu na twoje nazwisko. On nawet nie jest w naszej kolonii - odpłynął do Europy. Mówię ci, że nigdy nie widziałem tak nieuczciwego człowieka. Chciał mnie oszukać, ale mu się nie udało - mam kilka własnych sztuczek...";
				link.l1 = "Łajdak! Dał mi swoje słowo....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Zgadza się. "+pchar.GenQuest.Noblelombard.Name+" zdeponował na twoje nazwisko. Proszę, weź to...";
				link.l1 = "Wspaniale! Żegnaj, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Nie ma czegoś takiego dla ludzi takich jak "+pchar.GenQuest.Noblelombard.Name+" ponieważ nie mają honoru ani sumienia. Czyżby cię oszukał?";
			link.l1 = "Ma, przypuszczam. Cokolwiek, "+npchar.name+", nie zamierzam tu długo zostawać, a Europa jest mała... Może pewnego dnia się spotkamy. Żegnaj!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard"); // лесник с нпчара на пчара
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard); // Addon-2016 Jason уменьшаем раздачу дублонов
			AddMoneyToCharacter(pchar, iTemp);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard");// с нпчара на пчара  лесник
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Panie, nie znam cię. Pożyczam pieniądze tylko miejscowym obywatelom lub kapitanom. Wybacz mi...";
			link.l1 = "Rozumiem. Szkoda jednak.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "Co-co... Co masz na myśli?";
			link.l1 = "Ty parszywy szczurze! Teraz słuchaj mnie uważnie: nie jestem aż tak głupi. Pinette napisał dwa egzemplarze listu. Jeden dałem tobie, drugi jest w posiadaniu mojego zaufanego agenta. Jeśli coś mi się stanie - mój człowiek dostarczy go prosto w ręce gubernatora...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = " ";
			link.l1 = "Więc sugeruję, byś modlił się o moje zdrowie w kościele na każdej porannej mszy zamiast wynajmować zabójców na moje życie. Ostatnie ostrzeżenie! Spróbuj czegokolwiek przeciwko mnie, a jesteś zgubiony. Zrozumiano? Dobrze. Weź głęboki oddech i dalej licz swoje dublony.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "Nie chcę z tobą rozmawiać.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Oczywiście! Wielu chce po prostu odzyskać pieniądze i odejść. Zwłaszcza w świetle ostatnich plotek...";
			link.l1 = "Jakie plotki?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "Mówią, że warunki w załodze są coraz gorsze. Pan Blackwood zaczął nawet tolerować regularne straty - co wcześniej nigdy się nie zdarzało. Ale to nie moja sprawa. Ja tylko sprzedaję towar. Więc, czym pan się interesuje?";
			link.l1 = "Przejdźmy do rzeczy.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}
