//Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Dzień dobry, "+GetAddress_Form(NPChar)+" . Jestem świadom, że jesteś kapitanem własnego statku. Mam dla ciebie propozycję.";
					link.l1 = "Słucham, "+GetAddress_FormToNPC(NPChar)+". Jaką propozycje?";
					link.l1.go = "crew";
					link.l2 = "Przepraszam, "+GetAddress_FormToNPC(NPChar)+", ale się spieszę.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hej, kapitanie! Czego chcesz od zwykłego marynarza?","Dzień dobry, panie. Jak mogę ci pomóc?","Dzień dobry, panie. Czy czegoś pan sobie życzy?");
				link.l1 = "Miło cię poznać, kumplu! Nazywam się "+GetFullName(pchar)+". Masz chwilę, żeby porozmawiać?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji o tej kolonii.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Tylko chciałem się przywitać. Do zobaczenia!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Znowu pan, sir? Czego jeszcze pan chce?";
				link.l1 = "Masz chwilę na rozmowę?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji o tej kolonii.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Nie, kumplu, to nic. Powodzenia!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(" "+GetFullName(npchar)+" do usług, dobry panie! Co chcesz wiedzieć?","Miło z tobą porozmawiać, kapitanie!","No cóż... Przypuszczam, że mam jeszcze trochę czasu na rozmowę...","Na nieszczęście, muszę teraz odejść. Żegnaj!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Masz coś ciekawego do opowiedzenia?","Masz coś ciekawego do opowiedzenia?","Masz coś ciekawego do opowiedzenia?","Pewnie. Powodzenia!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (hrand(2))
			{
				case 0: sTemp = "Ja i moi towarzysze zostaliśmy przeniesieni na ląd z naszego ostatniego statku z powodu różnych chorób i urazów. Ale wszyscy jesteśmy już zdrowi i chcemy wrócić do pracy jako marynarze. Chcesz nas zatrudnić?"; break;
				case 1: sTemp = "Ja i kilku moich chłopaków otrzymaliśmy wypłatę od statku handlowego z powodu wygaśnięcia jego kontraktu. Od dłuższego czasu nie mamy ani jednej jednostki, więc chcemy wrócić do pracy. Potrzebujesz doświadczonych żeglarzy do swojej załogi?"; break;
				case 2: sTemp = "Ja i moi kumple wróciliśmy z rejsu dwa tygodnie temu. Kapitan statku nas zwolnił i świetnie się bawiliśmy. Ale nasze kieszenie są teraz puste, więc czas znów wypłynąć. Chcesz nas zatrudnić, kapitanie?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Cóż, jestem gotów omówić twoją propozycję. Ilu was jest i w czym jesteście dobrzy?";
			link.l1.go = "crew_1";
			link.l2 = "Przykro mi, marynarzu, ale mam już wystarczająco ludzi. Powinieneś znaleźć sobie innego kapitana.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "Jesteśmy najlepsi w obsłudze żagli i takielunku. Nie będę przesadnie skromny, ale powiedziałbym, że jesteśmy profesjonalistami w obsłudze statków, więc bez obaw, nie zawiedziemy Cię nawet w najsilniejszych sztormach."; break;
				case 1: sTemp = "Najbardziej lubimy przebywać na pokładzie działowym. Niewielu z nas służyło nawet na prawdziwych okrętach wojennych. Potrafimy ładować i strzelać z armat w sposób, w jaki nie potrafi tego nikt z Waszej załogi. Możecie na nas liczyć w każdej ciężkiej walce!"; break;
				case 2: sTemp = "Jesteśmy naprawdę dobrymi kapitanami abordażowymi, mieliśmy już kilka wypadów na korsarzy. Znamy blask kordelasów i zapach prochu i krwi. To nasze powołanie. Niełatwo nas pokonać w walce wręcz, więc zawsze możesz liczyć na nasze ostrza, kapitanie!"; break;
			}
			dialog.text = "Jest "+sti(npchar.quest.crew.qty)+" z nas i zatrudnimy się tylko razem. Możemy wykonywać wszystkie podstawowe zadania marynarza. "+sTemp+" ";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Brzmi jak ludzie, których szukam. A co z twoją zaliczką?";
				link.l1.go = "crew_2";
				link.l2 = "Przykro mi, marynarzu, ale w tej chwili potrzebuję innych umiejętności. Powinieneś poszukać sobie innego kapitana.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Przykro mi, marynarzu, ale nie mam wystarczająco miejsca na moim statku. Powinieneś znaleźć sobie innego kapitana.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" za każdą. A potem zwyczajną pensję marynarza na miesiąc. Nie będziemy żądać niczego nadmiernego, kapitanie.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Jesteś zatrudniony! Weź swoje monety. Teraz idź na mój statek, nazywa się '"+pchar.ship.name+"', prosto w porcie. Bosman przydzieli wam wszystkim hamaki w kajutach załogi i zajmie się waszymi posiłkami.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Niestety, nie stać mnie na opłacenie was wszystkich. Powinniście znaleźć sobie innego kapitana.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Tak jest, kapitanie! Zbiorę chłopaków i zaraz wyruszymy.";
			link.l1 = "Śpiesz się, wypływamy niezwłocznie.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hej, schowaj swój miecz, kapitanie. Żaden z nas nie potrzebuje problemów, prawda?","Hej, schowaj szablę, kapitanie. Nikt z nas nie potrzebuje problemów, prawda?");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz.","Jak powiadasz.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
