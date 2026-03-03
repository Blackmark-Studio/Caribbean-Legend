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
			dialog.text = "Acorde, "+Pchar.name+"! Chegamos ao "+Pchar.HeroParam.Land+" Finalmente, depois de tantas tempestades!"+"  E agora, o que vai fazer? Você perdeu seu navio, camarada.";
			link.l1 = "Não é a minha primeira vez! A sorte é uma desgraçada.";
			link.l1.go = "start1";
			link.l2 = "Você quer me oferecer um trabalho, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "Espero que você tenha mais sorte daqui pra frente do que teve com o seu 'Mercúrio'. Adeus.";
			link.l1 = "Sem dúvida. Adeus, capitão!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+" Vá até a taverna da Inness. Ela sabe tudo sobre todo mundo na cidade."+"  Vá até Urksen, ele é o líder aqui. Mas converse primeiro com os piratas locais.";
            }
            else
            {
                dialog.text = ret+"Pegue um dinheiro emprestado, venda suas coisas. Você sabe o que fazer.";
            }
            link.l1 = "Tudo bem, obrigado pelo conselho. Até logo.";
			link.l1.go = "game_begin";
			link.l2 = "Sabe, Abraham, acho que vou ficar com o seu navio. Gostei bastante deste aqui!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Piada ruim, camarada.";
			link.l1 = "Não se preocupe, velho. Adeus!";
			link.l1.go = "game_begin";
			link.l2 = "Quem disse que eu estava brincando? Você vai dizer ao seu pessoal que vendeu seu navio para mim. E eu poupo sua vida. Fechado?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "Ouvi dizer que você matou seu mestre, Malcolm Hatcher, por um sabre barato. Achei que eram só boatos. Que tolo eu fui. Hoje à noite você vai servir de comida pros peixes, garoto! Você não tem a menor chance.";
			link.l1 = "Ah, você acha mesmo?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Opa...";
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
				dialog.text = "Bem, camarada. Sabe, achamos que seria uma boa ideia te vender como escravo. Ha-ha! Dinheiro sempre faz falta.";
				link.l1 = "O quê?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "Chegamos ao nosso destino. Adeus.";
				link.l1 = "Adeus.";
				link.l1.go = "Travel_end";
				link.l2 = "Eu gostei do seu navio. Quero ficar com ele para mim.";
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
