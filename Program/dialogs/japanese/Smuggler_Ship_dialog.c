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
			dialog.text = "「起きろ」 "+Pchar.name+"！俺たちは到着したぜ "+Pchar.HeroParam.Land+" やっとだ、あの嵐の数々を越えて！"+"  これからどうするつもりだ？お前は船を失っちまったな、相棒。";
			link.l1 = "初めてじゃねえよ！運命なんざ、気まぐれな女だぜ。";
			link.l1.go = "start1";
			link.l2 = "「俺に仕事を頼みたいのか、アブラハム？」";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "これからは『マーキュリー』号の時より運が良くなることを願っているぜ。さらばだ。";
			link.l1 = "間違いないぜ。じゃあな、船長！";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + ", I am a smuggler not a governor, what kind of job are you even talking about?";
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret+" イネスの酒場を調べてみろ。あの女は町の誰についても何でも知ってるんだ。"+"  ウルクセンのところへ行け、ここを仕切ってるのはあいつだ。だが、まずは地元の海賊どもと話をしてみろ。";
            }
            else
            {
                dialog.text = ret+"金を借りるか、持ち物を売るんだ。どうすればいいか分かってるだろう。";
            }
            link.l1 = "助かったよ、忠告ありがとう。じゃあな。";
			link.l1.go = "game_begin";
			link.l2 = "なあ、アブラハム、お前の船をいただくことにするぜ。俺はこの船が気に入ったんだよ！";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "悪い冗談だな、相棒。";
			link.l1 = "心配するなよ、じいさん。じゃあな！";
			link.l1.go = "game_begin";
			link.l2 = "俺が冗談を言ってると思ったのか？お前は自分の船を俺に売ったと仲間に伝えるんだ。そうすりゃ命は助けてやる。 どうだ？";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "安物のサーベル欲しさに主人のマルコム・ハッチャーを殺したって聞いたぜ。噂話かと思ってたが、俺もバカだったな。 今夜は魚のエサになってもらうぜ、坊や！お前に勝ち目はねえ。";
			link.l1 = "「おや、本当にそう思うのか？」";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "おっと…";
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
				dialog.text = "さて、相棒。実はな、お前を奴隷として売り飛ばすのがいい考えだと思ったんだよ。ハハッ！ 金はいくらあっても困らねえからな。";
				link.l1 = "何だって！？";
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = "目的地に着いたぜ。じゃあな。";
				link.l1 = "さらば。";
				link.l1.go = "Travel_end";
				link.l2 = "お前の船、気に入ったぜ。俺のものにしたいんだ。";
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
