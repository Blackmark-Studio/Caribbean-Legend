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
			dialog.text = "醒醒, " +Pchar.name+ "! 经历了这么多风暴, 我们终于抵达" + Pchar.HeroParam.Land +
						  "了! 你现在打算做什么? 你的船和伙伴都没了。 ";
			link.l1 = "这又不是第一次! 命运就是个婊子。 ";
			link.l1.go = "start1";
			link.l2 = "亚伯拉罕, 你想给我提供一份工作吗? ";
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = "希望你从现在开始能比在‘墨丘利号’时更幸运。 再见。 ";
			link.l1 = "毫无疑问。 再见, 船长! ";
			link.l1.go = "game_begin";
		break;
		
		case "start2":
			ret = Pchar.name+ ", 我是个走私犯, 不是总督, 你到底在说什么工作? ";
            if (sti(Pchar.nation) == PIRATE)
            {
				dialog.text = ret + "去英尼斯的酒馆看看。 她认识镇上的所有人。 "+
							  "去找厄克森, 他是这里的首领。 但先和当地海盗谈谈。 ";
            }
            else
            {
				dialog.text = ret + "借点钱, 卖掉你的东西。 你知道该怎么做。 ";
            }
			link.l1 = "好的, 谢谢你的建议。 再见。 ";
			link.l1.go = "game_begin";
			link.l2 = "你知道吗, 亚伯拉罕, 我最好开走你的船。 我喜欢这艘! ";
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = "笑话真烂, 伙计。 ";
			link.l1 = "别担心, 老头。 再见! ";
			link.l1.go = "game_begin";
			link.l2 = "谁说我在开玩笑? 你去告诉你的人, 你把船卖给我了。 我就饶你一命。 成交? ";
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = "我听说你为了一把廉价军刀杀了你的主人马尔科姆.哈彻。 我还以为那只是谣言。 我真是个傻瓜。 小伙子, 今晚你就去喂鱼吧! 你没机会了。 ";
			link.l1 = "哦, 你真这么认为? ";
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = "哎哟... ";
			Link.l1.go = "exit";
		break;

////////////////////////////////////////////////////////////////////////////////
//	海盗地铁
////////////////////////////////////////////////////////////////////////////////
		case "Travel_talkStart":
            NPChar.location = "none"; // 避免在甲板上交谈
			//卖给矿场的概率
			int iRnd = (rand(100) == 30);
			if (iRnd)
			{
				dialog.text = "好吧, 伙计。 你知道吗, 我们觉得把你卖作奴隶是个好主意。 哈哈! 钱总是有用的。 ";
				link.l1 = "什么? ! ";
				//占位符, 暂未实装矿场
				link.l1.go = "Travel_fight";
				//"Travel_mine"; // 其实也可以组织战斗, 主角反抗
			}
			else
			{
				dialog.text = "我们到目的地了。 再见。 ";
				link.l1 = "再见。 ";
				link.l1.go = "Travel_end";
				link.l2 = "我喜欢你的船。 我想自己留着。 ";
				link.l2.go = "Travel_fight";
			}
		break;

		case "Travel_fight":
			ChangeContrabandRelation(pchar, -60);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//取出军刀
			LAi_SetFightMode(Pchar, true);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_end":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			//任务记录
			AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt")));


			LAi_SetPlayerType(PChar);
			//将主角传送至目标地点
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
									pchar.GenQuest.contraTravel.destination.group,
									pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			//删除三个属性
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
	}
}