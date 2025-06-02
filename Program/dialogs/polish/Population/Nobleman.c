//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Hm. Pływasz pod banderą "+NationNameGenitive(sti(pchar.nation))+", kamracie. Co do cholery robisz tutaj, w naszym mieście? Zjeżdżaj!","Nie chcę być podejrzewany jako przyjaciel "+NationNameAblative(sti(pchar.nation))+"Zjeżdżaj, albo doniosę strażnikom!","To twoja ostatnia szansa, by uciec. Inaczej będziesz mógł winić tylko siebie.","Przestrzegałem cię. Teraz zapłacisz za swoją zuchwałość, bękarcie!","zablokować",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Taki patriota, ha!","Dobrze, dobrze, uspokój się. Już wychodzę.","Nie hałasuj tak. Odchodzę.","Co?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Spójrz tylko na to! Jak to się dzieje, że nasi strażnicy pozwalają takiemu łajdakowi jak ty swobodnie chodzić po mieście? To niemożliwe...","Zjeżdżaj, nawet nie chcę z tobą gadać! Wisielec...","To twoja ostatnia szansa, żeby uciec. W przeciwnym razie będziesz mógł winić tylko siebie.","Ostrzegałem cię. Teraz zapłacisz za swoją bezczelność, łajdaku!","blokada",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Hej hej! Okaż mi więcej szacunku, panie!","Spójrz na siebie, święty...","Uspokój się...","Co?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "Witaj, "+GetAddress_Form(NPChar)+" Widzę, że jesteś kapitanem solidnego okrętu. Chcę cię o coś poprosić. Możesz się tego podjąć lub odmówić.";
					link.l1 = "Słucham, "+GetAddress_FormToNPC(NPChar)+"Co masz na myśli?";
					link.l1.go = "passenger";
					link.l2 = "Przepraszam, "+GetAddress_FormToNPC(NPChar)+", ale się spieszę.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "Pozdrowienia, "+GetAddress_Form(NPChar)+" Widzę, że jesteś kapitanem solidnego statku. Chcę cię o coś poprosić. Możesz to przyjąć lub zostawić.";
					link.l1 = "Słucham, "+GetAddress_FormToNPC(NPChar)+"  Co masz na myśli?";
					link.l1.go = "passenger";
					link.l2 = "Proszę wybaczyć, "+GetAddress_FormToNPC(NPChar)+", ale się śpieszę.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, dobrze widzieć dżentelmena w naszym małym miasteczku! Jestem pewien, że jesteś prosto z Europy. Słuchaj, chcę cię prosić o pomoc - dżentelmen do dżentelmena. Mam nadzieję, że mnie dobrze zrozumiesz.";
					link.l1 = "Dzień dobry, panie. Słucham.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Dzień dobry, "+GetAddress_Form(NPChar)+" ! Dobrze spotkać dżentelmena na ulicach naszego miasta! Czy pozwolisz mi zabrać ci kilka minut?";
					link.l1 = "Tak, panie. Słucham.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Dzień dobry, kapitanie! Cieszę się, że cię widzę, bo wyglądasz na człowieka, który potrafi rozwiązywać problemy.";
					link.l1 = "Zależy od problemu. Specjalizuję się w rozwiązywaniu ich przy użyciu przemocy, czy tego właśnie szukasz, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Witaj, "+GetAddress_Form(NPChar)+"Czy czegoś ode mnie chcesz?","Czego sobie życzysz, panie?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"Nie zajmę dużo czasu, tylko chciałbym zapytać...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Potrzebuję informacji o twojej kolonii.","Potrzebuję informacji.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Całe miasto jest spięte - przybył don Fernando de Alamida, królewski inspektor. Wiesz, widziałem tu wiele, ale to... To nie żałoba zmienia ludzi, ale to, jak sobie z nią radzą. Mówią, że stał się innym człowiekiem po śmierci ojca. Teraz nie znajdziesz bardziej nieprzekupnego i... bezlitosnego sługi Korony w całym Archipelagu.","Spójrz tylko na 'Świętą Miłosierdzie'! Mówią, że sam król kazał ją zbudować według specjalnych projektów. I zauważ - ani jednej rysy. Jakby sama Matka Boska jej strzegła. Choć słyszałem plotki... może to wcale nie Matka Boska.","Wiesz, ile razy próbowali zabić don Fernando? Dwanaście ataków na otwartych wodach - i to tylko w zeszłym roku! Cóż, z tak lojalną i wyszkoloną załogą, oraz pod ochroną Pana - przetrwa trzynasty również!"),LinkRandPhrase("Słyszałeś? Don Fernando de Alamida przybył do naszego miasta, a mówią, że teraz gdzieś krąży po ulicach. Chciałbym go zobaczyć na własne oczy...","Skomplikowany człowiek, ten don Fernando. Niektórzy mówią, że to zbawca, oczyszczający Ojczyznę z plugastwa. Inni szepczą, że coś w nim pękło po śmierci ojca i wkrótce wszyscy będziemy płakać. Ale powiem ci jedno: nie bój się go. Bój się tych, którzy go takim uczynili.","Taki przystojny mężczyzna, ten don Fernando! Ale wiesz co jest dziwne? Jakby nikogo nie zauważał. Wszystko obowiązek i służba. Słyszałam, że była jakaś dziewczyna... ale po spotkaniu z jakimś księdzem, całkowicie odrzucił ziemskie przyjemności. Jakby złożył ślub."),RandPhraseSimple(RandPhraseSimple("Przeklęty inspektor! Kiedy on tu jest - miasto jakby umarło. Żadnego handlu, żadnej zabawy. Nawet oddychać, zdaje się, trzeba ciszej. I wiesz, co jest najbardziej przerażające? To samo dzieje się w każdym porcie. Jak w zegarku. Jego Królewska Mość nie mógłby celowo wymyślić tej tortury dla nas wszystkich!","Don Fernando znowu odwiedził sierociniec. Hojnie daruje, modli się godzinami. Tak szlachetnego człowieka należy stawiać za przykład tym przeklętym defraudatorom!"),RandPhraseSimple("Ha! 'Święty' Fernando znów zamknął wszystkie burdele. Cóż, nieważne, wkrótce odpłynie i znowu się otworzą.","Inspekt... inspektor przybył, to co! Don Fernando de Almeyda, czy jak mu tam, Alamida! Tak ważny, że sam gubernator chodzi wokół niego na paluszkach. Mówią, że patrzy ci w oczy i od razu widzi wszystkie twoje grzechy. Przerażające!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Co? Znowu? Nie mam dla ciebie czasu. Poszukaj kogoś innego do rozmowy. Wiele pospólstwa krąży po ulicach. A ja muszę iść, dziś wieczorem będzie bankiet w rezydencji gubernatora i muszę przygotować swój strój...","Nie, teraz to naprawdę irytujące! Czy ty tego po prostu nie rozumiesz? Czy jesteś tępy?","Proszę pana, zaczynam podejrzewać, że nie tylko jesteś idiotą, ale także prostakiem i gburem. Ostrzegam cię, zostaw mnie w spokoju albo pożałujesz, że mnie niepokoiłeś.","Dosyć. Nauczę cię, zuchwały draniu!","blokada",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Rozumiem. Żegnaj.","Tak-tak, tylko zapomniałem, o co chciałem zapytać...","Źle mnie zrozumiałeś...","Co?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Idź dalej.","Czego chcesz?","Masz pytania? Dobrze, marynarzu, słucham.");
			link.l1 = LinkRandPhrase("Nie zechcesz mi opowiedzieć najnowszych plotek z twojego miasta?","Zdarzyło się tu ostatnio coś interesującego?","Jakieś nowiny z Karaibów, panie?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = " "+GetSexPhrase("Panie","Madame")+", muszę dotrzeć do kolonii"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"jak najszybciej to możliwe"+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", dla "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+"Twoja łajba wygląda solidnie i szybko w porównaniu z większością tych małych beczek pływających tutaj. Mogę ci zapłacić "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+"Co byś powiedział?"; // belamour gen
			}
			else
			{
				dialog.text = "Cześć, "+GetSexPhrase("panie","pani")+"! Muszę dostać się do "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! To jest na "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", przy okazji. Tak, tak, wiem - te dranie tylko czekają, aż się tam pojawimy. Ale mam tam bardzo pilne i ważne spotkanie! Nie jestem skąpy - choć nie lubię płacić, zawsze płacę. Rzuć wszystko, co robisz, a jak tylko przybędziemy, dam ci "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "Hm. Zmierzam w tę stronę, więc jestem gotów zabrać cię na pokład na tych warunkach.";
			link.l1.go = "passenger_1";
			link.l2 = "Przykro mi, "+GetAddress_FormToNPC(NPChar)+", ale płynę w innym kierunku. Nie mogę ci pomóc.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Szkoda. Cóż, poczekam na inny statek. Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Świetnie! Mam dość czekania. Otrzymasz zapłatę, gdy tam dotrzemy.";
			link.l1 = "Idź na mój statek, "+GetAddress_FormToNPC(NPChar)+" . Wkrótce wypływamy.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Oto jesteśmy, najzacniejszy! Podróż na Twoim statku była całkiem satysfakcjonująca. Masz zdyscyplinowaną załogę i czyste pokłady! Moje podziękowania. Weź swoje pieniądze, sir.";
			link.l1 = "Powodzenia, "+GetAddress_FormToNPC(NPChar)+"Żegnaj.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "Mam dość delikatną sprawę..."+sTemp+" Potrzebuję pieniędzy teraz albo będę w wielkich tarapatach. Nigdy normalnie nie poprosiłbym innego dżentelmena o pieniądze, ale sytuacja jest naprawdę zła.";
			link.l1 = "Ile potrzebujesz?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "Kwota jest dość mała, to "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+" Więc co, możesz mi pomóc?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Tak, oczywiście. Weź to.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Chętnie bym pomógł, ale moje kieszenie są również puste - ani jednego wolnego peso.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "Moja wdzięczność, "+GetAddress_Form(NPChar)+"! Uratowałeś mnie! Mam przyjaciół w rezydencji gubernatora i opowiem im o twojej hojności. Jeszcze raz tysiąckrotne dzięki!";
			link.l1 = "Proszę bardzo, sir. Jestem pewien, że zrobiłbyś to samo dla mnie.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "Potrzebuję twojej pomocy. Jesteś bogaty i dżentelmenem, więc mam nadzieję, że zrozumiesz. Niedawno bardzo potrzebowałem pieniędzy, więc musiałem udać się do bankiera i zastawić "+pchar.GenQuest.Noblelombard.Item+"\nZaproponował dobre warunki. Dziesięć procent za każdy miesiąc, łącznie trzy miesiące. Ale czas minął, a ja nie mam pieniędzy na wykupienie przedmiotu z powodu niefortunnego przebiegu wydarzeń\nTeraz mówi, że znalazł kupca na "+pchar.GenQuest.Noblelombard.Item+" i sprzeda to, jeśli nie spłacę mojego długu i odsetek natychmiast. Ale teraz nie mam dużo pieniędzy, a przedmiot, który zastawiłem, jest bardzo drogi...";
			link.l1 = "A jak mogę ci w tym pomóc, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "Proszę cię, porozmawiaj z naszym bankierem. Zaoferuj mu pieniądze, poręcz za mnie... albo zrób coś innego. Niestety, nie mam kogo poprosić, wszyscy moi dobrzy przyjaciele nagle 'zbankrutowali'. W ciągu trzech miesięcy "+pchar.GenQuest.Noblelombard.Text+", a ja zwrócę ci wszystkie twoje koszty, podwójnie! Masz moje słowo jako dżentelmen!";
			link.l1 = "Dobrze, spróbuję ci pomóc w tej sprawie.";
			link.l1.go = "lombard_2";
			link.l2 = "Niestety, ja też jestem teraz 'bankrutem'. Więc nie mogę ci pomóc, bardzo mi przykro!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Dziękuję za zrozumienie. Będę czekał na ciebie w tawernie. Przyjdź tam tak szybko, jak to możliwe.";
			link.l1 = "... ";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+hrand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = hrand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "Co możesz powiedzieć, "+GetAddress_Form(NPChar)+"? Byłeś w banku? Masz dobre czy złe wieści?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "Zrobiłem to. Spłaciłem cały twój dług. Możesz tam iść i odzyskać swoją relikwię.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "Mam. Spłaciłem wszystkie odsetki za ostatnie trzy miesiące i nawet za kolejne trzy. Możesz spokojnie czekać na swoje pieniądze. Tylko nie zapomnij spłacić głównego długu za trzy miesiące.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "Spłaciłem. Spłaciłem wszystkie odsetki za ostatnie trzy miesiące. Bankier zgodził się poczekać jeszcze trzy miesiące, aż uzbierasz całą sumę.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "Co możesz powiedzieć, "+GetAddress_Form(NPChar)+"? Byłeś w banku? Masz dobre wieści czy złe?";
				link.l1 = "Mam. Ten sknera zażądał niesamowitej sumy. Odrzucił wszelkie prośby o ustępstwa i nie mam wymaganej sumy. Więc nie mogłem ci pomóc. Przepraszam.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "Co możesz powiedzieć, "+GetAddress_Form(NPChar)+"? Byłeś w banku? Masz dobre wieści czy złe?";
				link.l1 = "Już się robi. Czekaj.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Meh, "+GetAddress_Form(NPChar)+"... Teraz jesteś również świadkiem nieposkromionej chciwości tych przeklętych, krwiożerczych lichwiarzy. Na Boga, panie, oni zawstydzają Żydów! Pamiętaj o tym, gdy spróbujesz pożyczyć od nich pieniądze, jak ja to zrobiłem. Dziękuję ci przynajmniej za próbę...";
			link.l1 = "Nigdy ich nie lubiłem. Cóż, kto lubi lichwiarzy? Przykro mi, "+GetAddress_FormToNPC(NPChar)+"Żegnaj.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = "Niesamowite! Właśnie mnie uratowałeś, "+GetAddress_Form(NPChar)+"! Nigdy tego nie zapomnę. Zapewniam cię, że wszystkie twoje koszty zostaną podwójnie zwrócone. Przyjdź do naszego bankiera za trzy miesiące. Otworzę depozyt na twoje imię.";
			link.l1 = "Dobrze, zrobię, jak mówisz. Do zobaczenia!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Dzięki jeszcze raz, kapitanie. Powodzenia!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Jestem właścicielem "+LinkRandPhrase("fabryka","moje","plantacja")+" i zawsze potrzebuję świeżych niewolników. Klimat naprawdę daje im w kość. W tej chwili potrzebuję "+sti(npchar.quest.slaves.qty)+" głowy. Jestem gotów zamówić ich partię. Zapłacę złotem za każdą głowę, "+sti(npchar.quest.slaves.price)+"	dublony\nNie spiesz się, nie będę cię ograniczać czasowo, jeśli zdobędziesz to, czego potrzebuję. No cóż, oczywiście w granicach rozsądku, nie przedłużaj tego na więcej niż pół roku. Co powiesz? Umowa?";
			link.l1 = "Umowa stoi! Handel niewolnikami to brudny interes, ale wart ryzyka.";
			link.l1.go = "slaves_1";
			link.l2 = "Przepraszam, ale nie jestem handlarzem niewolników. To nie moja branża.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Bardzo dobrze, zatem. Będę czekał na ciebie, gdy przyniesiesz ładunek. Możesz mnie znaleźć w kościele od 11:00 do 13:00 każdego dnia. Przez resztę dnia jestem zajęty lub w pracy.";
			link.l1 = "Dobrze. Zapamiętam to. Do zobaczenia, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Czy przyniosłeś "+sti(npchar.quest.slaves.qty)+"niewolników, jak prosiłem, kapitanie?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Tak. Cała partia jest w mojej ładowni. Jestem gotów ci je przekazać.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "Nie, jestem na tym.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Kapitanie, jeśli jesteś tu w sprawie tych niewolników... Już kupiłem wystarczająco i teraz więcej nie potrzebuję. Za długo zwlekałeś, przepraszam.";
				link.l1 = "Jaka szkoda! Ale masz rację, nie byłem wystarczająco szybki. Żegnaj!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Doskonale. Natychmiast wyślę szalupę po nich.";
			link.l1 = "A co z moją zapłatą?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Nie martw się, pamiętam o tym. Proszę, weź tę sumę, "+sti(npchar.quest.slaves.price)+"   дублонów za głowę. Dobra umowa dla nas obojga, prawda?";
			link.l1 = "Dzięki. Miło robić z tobą interesy.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Powinienem tak powiedzieć... Wybacz mi teraz, muszę iść. Do zobaczenia!";
			link.l1 = "Powodzenia, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jako obywatel tego miasta proszę cię, żebyś schował swój miecz.","Słuchaj, jako obywatel tego miasta proszę cię, abyś schował swoją broń.");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz.","Dobrze.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}
