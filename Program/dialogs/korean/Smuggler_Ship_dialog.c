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
			dialog.text = "일어나라, "+Pchar.name+"! 우리는 도착했다 "+Pchar.HeroParam.Land+" 마침내, 이 모든 폭풍을 지나서!"+"  이제 뭐 할 거야? 네 배를 잃었잖아, 이 친구.";
			link.l1 = "처음은 아니지! 운명은 정말 지독한 년이야.";
			link.l1.go = "start1";
			link.l2 = "나한테 일자리를 주고 싶은 거야, Abraham?";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "이제부터는 '머큐리'호 때보다 더 좋은 운이 따르길 바라오. 안녕히 가시오.";
			link.l1 = "그건 의심할 여지가 없지. 잘 가, 선장!";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+" 이네스의 선술집을 확인해 봐. 그 여자는 마을 사람들에 대해 모르는 게 없어."+"  우르크센에게 가. 여기가 그가 우두머리야. 하지만 먼저 이곳 해적들과 얘기 좀 해봐.";
            }
            else
            {
                dialog.text = ret+"돈 좀 빌리고, 네 물건 팔아. 뭘 해야 할지 알잖아.";
            }
            link.l1 = "좋아, 조언 고마워. 안녕.";
			link.l1.go = "game_begin";
			link.l2 = "있잖아, Abraham, 네 배를 가져가기로 했어. 이 배가 마음에 드는걸!";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "재미없는 농담이군, 이봐.";
			link.l1 = "걱정 마, 영감. 잘 가!";
			link.l1.go = "game_begin";
			link.l2 = "내가 농담한다고 누가 그랬지? 네 놈은 네 사람들에게 배를 나한테 팔았다고 전해라. 그러면 목숨은 살려주지. 어때?";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "네가 값싼 세이버 한 자루 때문에 주인 말콤 해처를 죽였다는 소문을 들었지. 그냥 헛소문인 줄 알았는데, 내가 바보였군. 오늘 밤엔 네가 물고기 밥이 될 거다, 이놈아! 넌 가망 없어.";
			link.l1 = "오, 정말 그렇게 생각해?";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "이런...";
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
				dialog.text = "그래, 친구야. 있잖아, 우린 널 노예로 팔면 좋겠다고 생각했지. 하하! 돈은 언제나 쓸모가 있으니까.";
				link.l1 = "뭐라고?!";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "목적지에 도착했어. 잘 가.";
				link.l1 = "안녕히 가시오.";
				link.l1.go = "Travel_end";
				link.l2 = "네 배가 마음에 들어. 내가 가지려고 한다.";
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
