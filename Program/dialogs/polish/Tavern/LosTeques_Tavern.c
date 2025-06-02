#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("W mieście podniesiono alarm. Wszyscy cię szukają! Na twoim miejscu nie czekałbym tu zbyt długo.","Cała straż przeczesuje miasto, próbując cię znaleźć. Nie jestem idiotą i nie zamierzam z tobą rozmawiać!","Uciekaj, kamracie, zanim żołnierze zrobią z ciebie siekaninę..."),LinkRandPhrase("Czego potrzebujesz, łotrze?! Straż miejska już depcze ci po piętach. Daleko nie zajdziesz, piracie!","Brudny morderco, wynoś się z mojego domu! Straże!!","Nie boję się ciebie, psie! Stryczek wzywa, daleko nie uciekniesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple(" Heh, nie martwię się o alarm...","Nie mają szans mnie złapać."),RandPhraseSimple("Zamknij gębę, "+GetWorkTypeOfMan(npchar,"")+", albo wytnę ci ten przeklęty język.","Heh, "+GetWorkTypeOfMan(npchar," ")+", ty też chcesz polować na pirata? Słuchaj, kumplu, zachowaj spokój, a może przeżyjesz..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" ! Witaj, "+GetAddress_Form(NPChar)+" do tawerny Kopalni Los-Teques. Jedzenie, napitki i dziewki, wszystko w przystępnych cenach! Mam na imię "+GetFullName(npchar)+" i zawsze jestem do twojej dyspozycji.";
				Link.l1 = "Zobaczmy... Jestem "+GetFullName(pchar)+"Miło cię poznać, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ha, to mój stary znajomy, kapitan "+GetFullName(pchar)+" ! Cieszę się, że cię widzę, starcze! Rum, dziewki?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Nalej mi rumu, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Chciałbym się zdrzemnąć. Czy macie wolny pokój?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Masz jakieś aktualne wiadomości?","Co nowego w tych stronach?","Jak się wiedzie na lądzie?");
				link.l3.go = "rumours_tavern";
				link.l4 = "Nie, niczego nie potrzebuję, "+npchar.name+"  Wpadłem tylko, by się przywitać z tobą.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Och, jestem taki szczęśliwy! Nowe twarze to rzadkość w naszym mieście. Może naleję ci rumu i sobie pogadamy...";
			link.l1 = "Jestem tu po raz pierwszy i chciałbym dowiedzieć się trochę więcej o tej osadzie.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Nalej mi trochę rumu, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Chciałbym się przespać. Masz wolny pokój?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Nic ciekawego do opowiedzenia. Codziennie to samo: nuda, słońce i kurz. Tylko żołnierze, murzyni i Indianie tu mieszkają. Możesz również znaleźć kilka przygód i bandytów głodnych złota\nCzasami odwiedzają nas dżentelmeni, kapitanowie tacy jak ty, aby sprzedać niewolników za sztabki i kupić metale szlachetne. Nasz kupiec to całkiem interesujący człowiek, sprzedaje nie tylko złote i srebrne grudki, ale także półszlachetne kamienie\n Twierdzi, że ludzie z specjalną wiedzą mogą znaleźć te kamyki bardzo przydatnymi. Więc sprawdź nasz sklep. Sama kopalnia znajduje się dalej pod górą. Możesz ją odwiedzić, jeśli chcesz, ale polecam unikać denerwowania straży\nNie rozmawiaj z więźniami i niech Bóg cię chroni przed kradzieżą. Tak czy inaczej, najlepszym miejscem w tej osadzie jest moja tawerna, najlepsze miejsce na odpoczynek od tego piekącego piekła!";
			link.l1 = "Dzięki za informacje!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Kapitanie, myślę, że lepiej by było, gdybyś przestał. Broń Boże, żebyś nie narobił awantury pod wpływem alkoholu. Jesteśmy tutaj naprawdę surowi w tej kwestii. Nawet twoja władza ci nie pomoże.";
				link.l1 = "Hm... Przypuszczam, że masz rację - już wystarczy. Dzięki za troskę!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Proszę bardzo, kapitanie. Tylko pięć ośmiorek za kufel mojego najlepszego czarnego jamajskiego rumu!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Zatem, na zdrowie i pomyślność twojej tawerny, kamracie!","Zatem, za tych na morzu!","Zatem, za dobrobyt waszego miasta!"),LinkRandPhrase("Dobrze, na wiatry produkcji, na podmuch szczęścia, abyśmy wszyscy żyli lżej i bogaciej!","Zatem, niech wiatr zawsze dmie nam w plecy we wszystkich sprawach!","Zatem, za szczęście, pomyślność, radość i dziewki!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "Panie, zapłaciłeś za pokój i dziewczynę. Idź na górę, czeka na ciebie od jakiegoś czasu.";
				link.l1 = "Dobrze.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Mamy. Jak długo zamierzałeś zostać?";
			if(!isDay())
			{
				link.l1 = "Do rana.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Do wieczora.";
				link.l1.go = "room_night";
				link.l2 = "Do następnego ranka.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "To będzie dziesięć sztuk srebra. Chcesz dziewkę do pokoju w komplecie? Tylko tysiąc pesos za dziewczynę.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nie, nie potrzebuję dziewczyny. Proszę, weź to za pokój.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Tak, wezmę pokój i dziewczynę. Oto pieniądze.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Ach, nie stać mnie na pokój.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "To będzie dziesięć sztuk ośmiu. Chcesz też dziewkę do pokoju? Tylko tysiąc pesos za ladacznicę.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nie, nie potrzebuję dziewczyny. Proszę, weź to za pokój.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Dobrze. Weźmy pokój i dziewczynę. Oto pieniądze.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Ach, niestety nie stać mnie na pokój.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "To będzie dziesięć sztuk osiem. Czy chciałbyś dziewkę do pokoju w zestawie? Tylko tysiąc peso za dziewkę.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nie, nie potrzebuję dziewczyny. Proszę, weź to za pokój.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Dobrze. Weźmy pokój i dziewczynę. Oto pieniądze.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Niestety, nie stać mnie na pokój.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Idź na górę, señor. Dziewczyna będzie na Ciebie czekać. Miłego pobytu!";
			link.l1 = "Dzięki, kamracie...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Jak tam, biały panie. Nie patrz na "+npchar.name+" jak to, "+npchar.name+"wie, jak robić wszystko nawet lepiej niż biała squaw z burdelu. Ach, señor, jesteś taki przystojny... Obiecuję, ta squaw będzie cię kochać długo.";
			link.l1 = "Brzmi dobrze, pokaż mi swoje najlepsze indiańskie amulety. Nie będę potrzebował tańca deszczu, żeby cię zmoczyć...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rozbój w biały dzień!!! Co tu się dzieje?! Poczekaj, chwila, kumplu...","Hej, co tam robisz?! Próbujesz mnie okraść? Teraz masz przechlapane...","Zaczekaj, co do diabła robisz? Okazuje się, że jesteś złodziejem! Uznaj to za koniec drogi, dupku...");
			link.l1 = LinkRandPhrase("Diabeł!","Cholera!","A, cholera");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
