void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

	string ret;

	switch (Dialog.CurrentNode)
	{
	case "exit":
		NextDiag.CurrentNode = NextDiag.Tempnode;
		DialogExit();
		break;

	case "start":
		dialog.text = "Despierta, " + Pchar.name + "¡ Hemos llegado a la " + Pchar.HeroParam.Land + "¡por fin, después de todas estas tormentas!" + "  ¿Qué vas a hacer ahora? Has perdido tu barco, compañero.";
		link.l1 = "¡No es mi primera vez! La fortuna es una perra.";
		link.l1.go = "start1";
		link.l2 = "¿Quieres ofrecerme un trabajo, Abraham?";
		link.l2.go = "start2";
		break;

	case "start1":
		dialog.text = "Espero que tengas más suerte de ahora en adelante que con tu 'Mercurio'. Adiós.";
		link.l1 = "Sin duda alguna. ¡Adiós, capitán!";
		link.l1.go = "game_begin";
		break;

	case "start2":
		ret = Pchar.name + ", Soy contrabandista, no gobernador, ¿de qué tipo de trabajo estás hablando?";
		if (sti(Pchar.nation) == PIRATE)
		{
			dialog.text = ret + "Revisa la taberna de Inness. Ella está al tanto de todos en el pueblo." + "  Ve a Urksen, él es el líder aquí. Pero primero habla con los piratas locales.";
		}
		else
		{
			dialog.text = ret + "Pide prestado algo de dinero, vende tus cosas. Sabes qué hacer.";
		}
		link.l1 = "Bien, gracias por el consejo. Adiós.";
		link.l1.go = "game_begin";
		link.l2 = "¿Sabes?, Abraham, será mejor que tome tu barco. ¡Este me gusta!";
		link.l2.go = "start3";
		break;

	case "game_begin":
		DialogExit();
		addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;

	case "start3":
		dialog.text = "Mala broma, amigo.";
		link.l1 = "¡No te preocupes, viejo. ¡Adiós!";
		link.l1.go = "game_begin";
		link.l2 = "¿Quién dijo que estaba bromeando? Le dirás a tu gente que has vendido tu barco a mí. Y te perdonaré la vida. ¿Trato?";
		link.l2.go = "start4";
		break;

	case "start4":
		dialog.text = "He oído que asesinaste a tu maestro Malcolm Hatcher por un sable barato. Pensé que solo eran rumores. Qué tonto fui. ¡Estarás alimentando a los peces esta noche, chico! No tienes ninguna oportunidad.";
		link.l1 = "¿Oh, de verdad crees eso?";
		link.l1.go = "exit";
		addDialogExitQuest("Tut_KillOnShip");
		break;

	case "First time":
		dialog.text = "";
		Link.l1 = "Vaya...";
		Link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		////////////////////////////////////////////////////////////////////////////////
	case "Travel_talkStart":
		NPChar.location = "none"; // чтоб на палубе не болтался
		// Шанс на то что продадут на рудники.
		int iRnd = (rand(100) == 30);
		if (iRnd)
		{
			dialog.text = "Bueno, compañero. Sabes, pensamos que sería una buena idea venderte como esclavo. ¡Ja, ja! El dinero siempre es útil.";
			link.l1 = "¿¡Qué?!";
			// заглушка, пока нет рудников.
			link.l1.go = "Travel_fight";
			//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
		}
		else
		{
			dialog.text = "Hemos llegado a nuestro destino. Adiós.";
			link.l1 = "Adiós.";
			link.l1.go = "Travel_end";
			link.l2 = "Me gusta tu barco. Quiero quedármelo para mí.";
			link.l2.go = "Travel_fight";
		}
		break;

	case "Travel_fight":
		ChangeContrabandRelation(pchar, -60);

		LAi_group_MoveCharacter(NPChar, "TmpEnemy");
		LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
		LAi_SetPlayerType(PChar);
		// Вытащим саблю
		LAi_SetFightMode(Pchar, true);

		NextDiag.CurrentNode = NextDiag.Tempnode;
		DialogExit();
		LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Travel_end":
		NextDiag.CurrentNode = NextDiag.Tempnode;
		DialogExit();
		// Квест бук
		AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetLocationNameByID(pchar.GenQuest.contraTravel.destination.loc)));

			LAi_SetPlayerType(PChar);
			// грузим ГГ куда нужно....
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
								   pchar.GenQuest.contraTravel.destination.group,
								   pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
			chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			// трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
	}
}
