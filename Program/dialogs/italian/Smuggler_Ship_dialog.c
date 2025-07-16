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
			dialog.text = "Svegliati, "+Pchar.name+"! Abbiamo raggiunto il "+Pchar.HeroParam.Land+" finalmente, dopo tutte queste tempeste!"+"  Cosa farai ora? Hai perso la tua nave, compagno.";
			link.l1 = "Non è la mia prima volta! La fortuna è una stronza.";
			link.l1.go = "start1";
			link.l2 = "Vuoi offrirmi un lavoro, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "Spero che avrai più fortuna da ora in poi rispetto alla tua 'Mercury'. Addio.";
			link.l1 = "Non c'è dubbio su questo. Addio, capitano!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+"Controlla la taverna di Inness. Lei sa tutto su tutti in città."+"  Vai da Urksen, lui è il capo qui. Ma prima parla con i pirati locali.";
            }
            else
            {
                dialog.text = ret+"Prendi in prestito del denaro, vendi le tue cose. Sai cosa fare.";
            }
            link.l1 = "Bene, grazie per il consiglio. Addio.";
			link.l1.go = "game_begin";
			link.l2 = "Sai, Abraham, preferirei prendere la tua nave. Mi piace questa!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Cattivo scherzo, amico.";
			link.l1 = "Non preoccuparti, vecchio. Addio!";
			link.l1.go = "game_begin";
			link.l2 = "Chi ha detto che stavo scherzando? Dirai al tuo popolo che hai venduto la tua nave a me. E risparmierò la tua vita. Affare?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "Ho sentito dire che hai ucciso il tuo maestro Malcolm Hatcher per una sciabola a buon mercato. Pensavo fossero solo voci. Che sciocco che ero. Stanotte nutrirai i pesci, ragazzo! Non hai nessuna possibilità.";
			link.l1 = "Oh, davvero lo pensi?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Ops...";
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
				dialog.text = "Ebbene, compagno. Sai, abbiamo pensato che sarebbe stata una buona idea venderti come schiavo. Ah-ah! I soldi sono sempre utili.";
				link.l1 = "Cosa?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "Abbiamo raggiunto la nostra destinazione. Addio.";
				link.l1 = "Addio.";
				link.l1.go = "Travel_end";
				link.l2 = "Mi piace la tua nave. Voglio tenerla per me.";
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
