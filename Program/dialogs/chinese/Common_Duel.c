//navy 26.07.06
//决斗生成器... 
//在NPC对话中创建带有侮辱标志检查的链接... 据此跳转到"outraged"
//如果NPC对主角做了什么(销售假货)或者主角冒犯了NPC, 就给他挂上这个标志
//对于某些角色, 例如主角, 可以直接跳转到调用:"let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//移除标志
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("你怎么敢侮辱我, 无赖? ! ", "这些话会让你付出代价的! "), 
				RandPhraseSimple("你侮辱了我的荣誉, " + GetAddress_Form(NPChar) + "! 你会为此付出代价的。 ", "你怎么敢? 马上收回你的话! "));

		//这是个陷阱.. 为了让玩家读文本:)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("哈? ! 我甚至不想用你的血玷污我的剑! ", "哈? ! 我甚至不想用你的血玷污我的剑! "), 
				RandPhraseSimple("我随时奉陪! ", "我不会和暴民咬文嚼字! ")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("我不是故意的! ", "我太激动了... "), 
				RandPhraseSimple("那是个错误, 我很抱歉。 ", "我把你认错了, " + GetAddress_FormToNPC(NPChar) + "。 请原谅我。 ")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,  
				RandPhraseSimple("我要割下你的耳朵! ", "我要挖出你的心! "), 
				RandPhraseSimple("我希望能听到你的道歉, 否则我不能保证能控制自己! ", "你意识到这意味着什么了吗... 你明白吗? "));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("我希望你的剑和你的舌头一样快! ", "我的刀刃会为我说话。 "), 
				RandPhraseSimple("我向你挑战决斗! ", "这是荣誉问题! ")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("我想我还没准备好! ", "想想, 我们不应该激动! 只是些言语而已! "), 
				RandPhraseSimple("我想起来了, 我在等人。 愿你一切安好... ", "啊! 好像我的船已经起航了。 再见。 ")), "change_mind");
		break;

	case "let_s_duel":
		//检查已开始的决斗
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "首先, 你先处理好和别人的事, 然后我们再谈。 ";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "我们已经达成协议了。 ";
			}
			link.l1 = RandSwear() + "哦, 我怎么忘了... ";
			link.l1.go = "exit";
			break
		}
		//可能拒绝
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("决斗? ! 滚开, 你不值得我浪费时间。 ", "决斗? 你不配得到那份荣誉! 滚开! ");
			link.l1 = RandPhraseSimple("好吧... ", "我想我可以等... ");
			link.l1.go = "exit";
/**/
			//可以让玩家无论如何都有机会战斗:)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("你这么认为吗? 别太自信了, 混蛋!!! ", "哦, 真的吗? ! 我倒要看看你的血是什么颜色的! ");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//同意
		Dialog.Text = RandPhraseSimple("你说决斗? 我没问题。 我们将用剑和手枪决斗。 ", 
			"你甚至能握住剑吗? ");
		link.l1 = RandPhraseSimple("你会跪在地上求饶的。 ", "我会用这双手掐死你, 你这个无赖! ");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + " 或者我们可以出海, 看看谁更厉害! ", 
				"决斗? ! 哈, 我会像拍虫子一样打死你! 选择你想怎么死吧! ");
			link.l2 = RandPhraseSimple("在海上, 我是最厉害的。 ", "我的船会轻易击沉你那破旧的 tub! ");
			link.l2.go = "sea_duel";
		}
		link.l3 = "我改变主意了... ";
		link.l3.go = "change_mind";
		break;

	//水下小船决斗 :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("我在港口没看到你的船... ", "在你至少找到一艘破旧的 tub 之前, 滚开! ");
		link.l1 = RandPhraseSimple("是我错了... ", "那我走了。 ");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "好吧, 我会在海湾出口等你... ";
			link.l1 = "我不会让你等太久的。 ";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//在陆地上
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //取消注释以仅在夜间进行决斗
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple("拔出剑来, 让我看看你的血是什么颜色的! ", "好吧, 如果你想找死... ");
		link.l1 = RandPhraseSimple("我们最好去一个没有太多目击者的地方。 我知道城门外有个好地方。 我们 " + iHour + " 小时后在那里见面。 ",
			"等等。 这种事情最好在没有目击者的情况下解决。 " + iHour + " 小时后来城门口。 ");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("好吧, 如果你这么想死... ", "该死的! 我会帮你亲眼看看地狱! ");
		link.l2.go = "fight_right_now";
		link.l3 = "我改变主意了... ";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("我想我们最好出城去。 我会在 " + pchar.questTemp.Duel.WaitTime + " 小时后在那里等你。 不要迟到! ", 
				"这里不是解决争端的最佳地点。 我们最好离开城镇。 " + pchar.questTemp.Duel.WaitTime + " 小时后我会在那里。 ");
			link.l1 = RandPhraseSimple("你不配得到那份荣誉! 保护好自己! ", "我没时间了! 拔剑! ");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("好吧, 我们走。 ", "你可能是对的。 我们在城门外见面。 ");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//提议"我们出去"被考虑
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("你不配得到那份荣誉! 保护好自己! ", "我没时间了! 就在这里现在! ");
		link.l1 = RandPhraseSimple("好吧, 如果你这么想死... ", "该死的! 我会帮你亲眼看看地狱! ");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("好吧, 我们走。 ", "你可能是对的。 我们在城门外见面。 ");
			link.l1 = RandPhraseSimple("我会在那里等你。 ", "不要迟到。 ");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//好吧, 我们出去
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//哪里? 
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//按时到达
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//以防万一, 如果等不到, 一小时足够
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // 以免与国家发生冲突
				DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // 活到决斗
				}
			}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//战斗前的最后一句话
	case "talk_off_town":
		Dialog.Text = "那么, 你准备好了吗? ";
		link.l1 = "是的。 让我们看看谁更厉害! ";
		link.l1.go = "fight_right_now";
		link.l2 = "不, 我决定向你道歉。 我错了, 太激动了。 ";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("嘿, 听着, 我一直在想, 现在我意识到我错了。 我道歉。 ", 
				"该死的! 都是那该死的朗姆酒!!! 我道歉, " + GetSexPhrase("兄弟","姐妹") + "! ");
			link.l1 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("不, 只有你的血能让我满意! ", "拔剑, 别像个哭哭啼啼的女孩! "), 
				RandPhraseSimple("不! 我要求得到满足! ", "你是家族的耻辱! 拔出你的剑! "));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("好吧, 我同意。 我们有点激动了。 ", "朋友之间谁会计较呢! "), 
				RandPhraseSimple("你可能是对的。 我们不应该为这种小事流血。 ", "我的慷慨是无限的! 你被原谅了! "));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//开始决斗!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	//改变主意, 嗯... 不好;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("那就滚开! ", "趁我改变主意之前滚开。 "), 
				RandPhraseSimple("那样的话, 我就不再耽误你了! ", "趁我改变主意之前, 你最好离开。 "));
		link.l1 = "我这就走... ";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("滚开! ", "在我改变主意之前, 从我的视线中消失。 "),
				RandPhraseSimple("我能帮你吗? ", "你想要什么? "));
		link.l1 = "我走了。 ";
		link.l1.go = "peace";
		break;

	//和平等等
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}