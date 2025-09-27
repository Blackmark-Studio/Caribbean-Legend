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
			dialog.text = "Ébresztô, " + Pchar.name + "! Végre elértük a "+ Pchar.HeroParam.Land +" , ennyi vihar után!"+
                          "  Most mit fogsz csinálni? Elvesztetted a hajódat, pajtás.";
			link.l1 = "Nem ez az elsô alkalom! A szerencse egy szuka.";
			link.l1.go = "start1";
			link.l2 = "Akarsz nekem munkát ajánlani, Ábrahám?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "Remélem, hogy mostantól több szerencséd lesz, mint a 'Mercury'. búcsúval.";
			link.l1 = "Ebben nincs kétségem. Viszlát, kapitány!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret + " Nézz be az Inness kocsmába. Ô mindenkirôl tud a városban."+
                              "  Menj Urksenhez, ô itt a vezetô. De elôbb beszéljetek a helyi kalózokkal.";
            }
            else
            {
                dialog.text = ret + "Kérj kölcsön egy kis pénzt, add el a cuccaidat. Tudod, hogy mit kell tenned.";
            }
            link.l1 = "Rendben, köszönöm a tanácsot. Viszlát.";
			link.l1.go = "game_begin";
			link.l2 = "Tudod, Ábrahám, jobb, ha elviszem a hajódat. Ez tetszik nekem!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Rossz vicc, haver.";
			link.l1 = "Ne aggódj, öregem. Viszlát!";
			link.l1.go = "game_begin";
			link.l2 = "Ki mondta, hogy vicceltem? Majd elmondod az embereidnek, hogy eladtad a hajódat nekem. És én megkímélem az életed. Megegyeztünk?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "Hallottam, hogy megölte a mesterét, Malcolm Hatchert egy olcsó szablyáért. Azt hittem, hogy csak pletykák. Micsoda bolond voltam. Ma este halat fogsz etetni, fiam! Nincs esélyed.";
			link.l1 = "Ó, tényleg így gondolod?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Hoppá...";
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
				dialog.text = "Nos, haver. Tudod, úgy gondoltuk, hogy jó ötlet lenne eladni téged rabszolgának. Ha-ha! A pénz mindig hasznos.";
				link.l1 = "Micsoda?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "Elértük a célunkat. Viszontlátásra.";
				link.l1 = "Ég veled!";
				link.l1.go = "Travel_end";
				link.l2 = "Tetszik a hajód. Szeretném megtartani magamnak.";
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
