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
			dialog.text = "Uyan, "+Pchar.name+"! Hedefimize ulaştık "+Pchar.HeroParam.Land+" Sonunda, bunca fırtınadan sonra!"+"  Şimdi ne yapacaksın? Gemini kaybettin, dostum.";
			link.l1 = "İlk defa değil! Şans denen şey tam bir kaltak.";
			link.l1.go = "start1";
			link.l2 = "Bana bir iş teklif etmek mi istiyorsun, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "Umarım bundan sonra 'Merkür'le yaşadığınız şanssızlığı telafi edecek kadar iyi bir talihiniz olur. Hoşça kalın.";
			link.l1 = "Hiç şüphe yok. Hoşça kal, kaptan!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+" Inness'in meyhanesine bak. Kasabadaki herkes hakkında her şeyi bilir."+"  Burada lider Urksen, ona git. Ama önce buradaki korsanlarla konuş.";
            }
            else
            {
                dialog.text = ret+"Biraz borç al, eşyalarını sat. Ne yapacağını biliyorsun.";
            }
            link.l1 = "Pekala, tavsiyen için teşekkürler. Hoşça kal.";
			link.l1.go = "game_begin";
			link.l2 = "Biliyor musun Abraham, galiba gemini alacağım. Bu hoşuma gitti!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "Kötü şaka, dostum.";
			link.l1 = "Endişelenme, yaşlı adam. Hoşça kal!";
			link.l1.go = "game_begin";
			link.l2 = "Şaka yaptığımı kim söyledi? Adamlarına gemini bana sattığını söyleyeceksin. Ve ben de hayatını bağışlayacağım. Anlaştık mı?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "Ucuz bir kılıç için ustan Malcolm Hatcher'ı öldürdüğünü duydum. Sadece dedikodu sanmıştım. Ne kadar da safmışım. Bu gece balıklara yem olacaksın, oğlan! Hiç şansın yok.";
			link.l1 = "Gerçekten öyle mi düşünüyorsun?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "Oops...";
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
				dialog.text = "Pekala, dostum. Biliyor musun, seni köle olarak satmanın iyi bir fikir olacağını düşündük. Ha-ha! Para her zaman işe yarar.";
				link.l1 = "Ne?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "Hedefimize vardık. Elveda.";
				link.l1 = "Elveda.";
				link.l1.go = "Travel_end";
				link.l2 = "Gemini beğendim. Onu kendime almak istiyorum.";
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
