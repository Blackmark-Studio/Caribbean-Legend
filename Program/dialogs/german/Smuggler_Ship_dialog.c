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
			dialog.text = "Wach auf, "+Pchar.name+"! Wir haben das erreicht "+Pchar.HeroParam.Land+" endlich, nach all diesen Stürmen!"+"  Was wirst du jetzt tun? Du hast dein Schiff verloren, Kumpel.";
			link.l1 = "Nicht mein erstes Mal! Das Glück ist eine Schlampe.";
			link.l1.go = "start1";
			link.l2 = "Möchten Sie mir einen Job anbieten, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "Ich hoffe, dass Sie ab jetzt mehr Glück haben als mit Ihrer 'Mercury'. Lebewohl.";
			link.l1 = "Kein Zweifel daran. Lebewohl, Kapitän!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+" Überprüfen Sie die Taverne von Inness. Sie kennt jeden in der Stadt."+"  Gehe zu Urksen, er ist der Anführer hier. Aber sprich zuerst mit den örtlichen Piraten.";
            }
            else
            {
                dialog.text = ret+"Leihe etwas Geld, verkaufe deine Sachen. Du weißt, was zu tun ist.";
            }
            link.l1 = "Gut, danke für den Rat. Lebewohl.";
			link.l1.go = "game_begin";
			link.l2 = "Du weißt, Abraham, ich nehme lieber dein Schiff. Dieses gefällt mir!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Schlechter Witz, Kumpel.";
			link.l1 = "Mach dir keine Sorgen , alter Mann. Lebewohl!";
			link.l1.go = "game_begin";
			link.l2 = "Wer sagt, dass ich scherze? Du wirst deinen Leuten sagen, dass du mir dein Schiff verkauft hast. Und ich werde dein Leben verschonen. Abmachung?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "Ich habe gehört, dass du deinen Meister Malcolm Hatcher für einen billigen Säbel ermordet hast. Ich dachte, es wären nur Gerüchte. Was für ein Narr ich war. Du wirst heute Nacht die Fische füttern, Bursche! Du hast keine Chance.";
			link.l1 = "Ach, meinst du das wirklich?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Hoppla...";
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
				dialog.text = "Nun, Kumpel. Weißt du, wir dachten, es wäre eine gute Idee, dich als Sklaven zu verkaufen. Ha-ha! Geld ist immer nützlich.";
				link.l1 = "Was?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "Wir haben unser Ziel erreicht. Lebewohl.";
				link.l1 = "Auf Wiedersehen.";
				link.l1.go = "Travel_end";
				link.l2 = "Ich mag dein Schiff. Ich möchte es für mich behalten.";
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
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetLocationNameByID(pchar.GenQuest.contraTravel.destination.loc)));


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
