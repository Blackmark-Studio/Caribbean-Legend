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
			dialog.text = "Réveille-toi, "+Pchar.name+"! Nous avons atteint le "+Pchar.HeroParam.Land+" enfin, après toutes ces tempêtes!"+"  Que vas-tu faire maintenant? Tu as perdu ton navire, camarade.";
			link.l1 = "Ce n'est pas ma première fois ! La fortune est une garce.";
			link.l1.go = "start1";
			link.l2 = "Voulez-vous me proposer un travail, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "J'espère que vous aurez plus de chance à partir de maintenant qu'avec votre 'Mercure'. Adieu.";
			link.l1 = "Aucun doute la-dessus. Adieu, capitaine!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+"Vérifiez la taverne d'Inness. Elle est au courant de tout le monde en ville."+"  Allez voir Urksen, c'est le chef ici. Mais parlez d'abord avec les pirates locaux.";
            }
            else
            {
                dialog.text = ret+"Emprunte de l'argent, vends tes affaires. Tu sais quoi faire.";
            }
            link.l1 = "D'accord, merci pour le conseil. Adieu.";
			link.l1.go = "game_begin";
			link.l2 = "Tu sais, Abraham, je ferais mieux de prendre ton navire. Celui-ci me plait!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Mauvaise blague, mon pote.";
			link.l1 = "Ne t'inquiète pas, vieux. Adieu!";
			link.l1.go = "game_begin";
			link.l2 = "Qui a dit que je plaisantais ? Vous direz à vos gens que vous avez vendu votre navire à moi. Et je vais épargner votre vie. Marché conclu ?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "J'ai entendu dire que tu as tué ton maître Malcolm Hatcher pour un sabre bon marché. Je pensais que ce n'étaient que des rumeurs. Quel imbécile j'étais. Tu nourriras les poissons ce soir, mon garçon ! Tu n'as aucune chance.";
			link.l1 = "Oh, pensez-vous vraiment cela?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Oups...";
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
				dialog.text = "Eh bien, mon pote. Tu sais, nous avons pensé que ce serait une bonne idée de te vendre comme esclave. Ha-ha! L'argent est toujours utile.";
				link.l1 = "Quoi?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "Nous avons atteint notre destination. Adieu.";
				link.l1 = "Adieu.";
				link.l1.go = "Travel_end";
				link.l2 = "J'aime votre navire. Je veux le garder pour moi.";
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
