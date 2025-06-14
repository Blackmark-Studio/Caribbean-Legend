void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

    string ret;
    
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
		break;

		case "start":
			dialog.text = "Obudź się, "+Pchar.name+"! Dotarliśmy do "+Pchar.HeroParam.Land+" w końcu, po wszystkich tych burzach!"+"  Co zamierzasz teraz zrobić? Straciłeś swój statek, kumplu.";
			link.l1 = "To nie mój pierwszy raz! Fortuna jest suką.";
			link.l1.go = "start1";
			link.l2 = "Czy chcesz mi zaproponować pracę, Abrahamie?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "Mam nadzieję, że będziesz miał więcej szczęścia od teraz niż z twoim 'Merkury'. Do widzenia.";
			link.l1 = "Bez wątpienia. Do widzenia, kapitanie!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", Jestem przemytnikiem, nie gubernatorem, o jakiej pracy w ogóle mówisz?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+"Sprawdź karczme Inness. Ona wie o każdym w mieście."+"  Idź do Urksena, on jest tutaj liderem. Ale najpierw porozmawiaj z lokalnymi piratami.";
            }
            else
            {
                dialog.text = ret+"Pożycz trochę pieniędzy, sprzedaj swoje rzeczy. Wiesz co robić.";
            }
            link.l1 = "Dobrze, dzięki za radę. Do widzenia.";
			link.l1.go = "game_begin";
			link.l2 = "Wiesz, Abraham, lepiej wezmę twój statek. Ten mi się podoba!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Kiepski żart, kolego.";
			link.l1 = "Nie martw się, stary człowieku. Do widzenia!";
			link.l1.go = "game_begin";
			link.l2 = "Kto powiedział, że żartuję? Powiesz swoim ludziom, że sprzedałeś mi swój statek. A ja oszczędzę ci życie. Umowa?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "Słyszałem, że zamordowałeś swojego mistrza Malcolma Hatchera za tanią szablę. Myślałem, że to tylko plotki. Takim głupcem byłem. Będziesz karmił ryby dzisiaj wieczorem, chłopcze! Nie masz szans.";
			link.l1 = "Oh, naprawdę tak myślisz?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Ups...";
			Link.l1.go = "exit";
		break;

////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel_talkStart":
            NPChar.location = "none"; // чтоб на палубе не болтался
			//Шанс на то что продадут на рудники.
			int iRnd = (rand(100) == 30);
			if (iRnd)
			{
				dialog.text = "Cóż, kumplu. Wiesz, pomyśleliśmy, że dobrym pomysłem będzie sprzedać cię jako niewolnika. Ha-ha! Pieniądze zawsze się przydają.";
				link.l1 = "Co?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "Dotarliśmy do celu. Do widzenia.";
				link.l1 = "Żegnaj.";
				link.l1.go = "Travel_end";
				link.l2 = "Podoba mi się twój statek. Chcę go zatrzymać dla siebie.";
				link.l2.go = "Travel_fight";
			}
		break;

		case "Travel_fight":
			ChangeContrabandRelation(pchar, -60);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//Вытащим саблю
   			LAi_SetFightMode(Pchar, true);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_end":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			//Квест бук
			AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt")));


			LAi_SetPlayerType(PChar);
			//грузим ГГ куда нужно.... 
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
									pchar.GenQuest.contraTravel.destination.group,
									pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
	}
}
