// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么, " + GetAddress_Form(NPChar) + "? "), "你不久前刚问过我问题, " + GetAddress_Form(NPChar) + "... ", "这已经是你第三次烦我了... ",
                          "我猜又是问题吧? ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记忆去哪了... ",
                      "是的, 真的是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//荷兰 Gambit /为英国/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "我想喝一杯。 给我倒你最好的朗姆酒。 ";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "听着, 卡洛.加斯顿在哪里? ";
                link.l1.go = "Tonzag_Letter";
            }
			//荷兰 Gambit /对抗所有人/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "你碰巧有什么工作吗? 或者你能推荐什么吗? ";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "我完成了任务。 费尔南多.罗德里格斯死了。 ";
                link.l1.go = "Task_check";
            }
			//真理守卫
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "听着, 这里有没有一个来到这个镇上的炼金术士, 一个医生? 他是意大利人, 大约三十岁, 名叫吉诺.格维内利。 你听说过吗? ";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//荷兰 Gambit /为英国/
		case "TavernDone":
			dialog.text = "这是你的酒。 为我们的新客人准备的最好的朗姆酒! 这是特殊场合还是你只是顺道来喝一杯? ";
			link.l1 = "是的, 可以说是特殊场合。 我要带一些黑人去布鲁维尔德。 我最近专门为我的新双桅船的船舱做了改装。 我刚去了一个种植园和监工谈过, 他向我订购了一批不错的‘黑象牙’。 所以很快在你的酒馆等我。 我会把货物送到布鲁维尔德, 然后我会在巴巴多斯这里做更多生意, 哟吼! ";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "真的吗? 好吧, 为一笔好交易喝酒没什么可羞耻的! 所以, 你说你要去巴巴多斯做生意? 那太好了! 为你干杯, 船长! ";
			link.l1 = "非常感谢, 伙计。 好的... 我去找个地方坐下。 ";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//移除计时器
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "加斯顿在你‘交易员’表演后两天离开了这个城镇。 你在这里上演了一场戏, 哈! 你的欺骗很快就被揭穿了, 这个城镇很小, 流言蜚语传播得很快。 这导致加斯顿离开了。 从那以后, 这里再也没有人见过他。 不过他给你留了一封信\n他要求如果你来这里比他早, 就把信亲自交给你。 实际上, 你不是第一个找加斯顿的人。 有一个窄眼的大个子和一个老人, 看起来像西班牙人或葡萄牙人, 我不确定。 但我不会忘记他的脸, 他身上有些东西非常不对劲... ";
			link.l1 = "把那封信给我... 谢谢! ";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//关闭弗利特伍德的房子
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//关闭药店
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//关闭地下室
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//荷兰 Gambit /对抗所有人/
		case "Tonzag_check"://开始根据所有条款检查我们的主角
			if(sti(pchar.reputation.nobility) > 48)//高声望
			{
				// belamour legendary edition 显示标准
				notification("声望太低! (流氓)", "None");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "我不需要无赖的服务。 我没有任何任务可以给你。 ";
				link.l1 = "嘿, 嘿。 说话客气点, 伙计! ";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//击剑能力弱
			{
				// belamour legendary edition 显示标准 -->
				notification("技能检查失败 (35)", SKILL_F_LIGHT);
				notification("技能检查失败 (35)", SKILL_FENCING);
				notification("技能检查失败 (35)", SKILL_F_HEAVY);
				notification("技能检查失败 (35)", SKILL_PISTOL);
				// <--
				dialog.text = "船长, 你太软弱了。 我需要一个比你更有名望的战士。 等你学会如何使用你腰带上悬挂的钢铁再来吧。 射击的精准度也不会有坏处。 ";
				link.l1 = "我明白了。 那我以后再来拜访你。 ";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "嗯... 你实际上很准时。 我有一个必须立即完成的差事。 如果你表现出色, 我会把你介绍给一些有影响力的人。 现在听着, 你要做的是。 ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "最近有一个从塞维利亚来的绅士, 为了避免在欧洲决斗的一些不必要后果。 但复仇是没有界限的, 一个西班牙贵族家庭希望这个绅士死。 以任何必要的方式完成他们的请求\n带上他手上戴着戒指的手指作为证明。 还要带上你在他尸体上找到的所有其他物品。 你准备好接受这份工作了吗? ";
			link.l1 = "如果报酬好, 那我就加入。 ";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "当刺客? 没门! ";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//标记为已接受对抗所有人
		break;
		
		case "Tonzag_exit":
			dialog.text = "那就滚蛋, 忘记我们谈过的话。 ";
			link.l1 = "我走了。 ";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//回滚到另外两个选项
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "你的报酬将是30,000八里亚尔, 不错的钱。 除此之外, 你可以拿走你在他身上找到的每一枚硬币。 现在让我们讨论细节。 名字是唐.费尔南多.罗德里格斯, 35岁, 高个子, 皮肤黝黑, 穿着像军官。 他是个好水手, 也是经验丰富的击剑手\n不知道在哪里可以找到他, 我只知道他在加勒比海的某个地方\n搜索每个西班牙城市, 直到你找到他。 你有两个月的时间。 最后一件事: 我知道他身上携带了什么, 所以不要想对我隐瞒任何物品。 有问题吗? ";
			link.l1 = "我没有任何问题。 我这就去! ";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //计时器
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // 丹尼拉 。 以便从档案中退出																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "你有带着戒指的手指吗? 让我看看。 ";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "是的, 当然。 给你。 ";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "没有。 费尔南多和他的船一起沉入了水中, 手指也和费尔南多一起沉了下去。 ";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "带戒指的手指是合同中的强制性条件。 它应该作为客户死亡的确认。 谁知道罗德里格斯是否从沉没的船上游到了岸边? 你检查过吗? 没有。 你基本上失败了任务, 所以我们的协议结束了。 一切顺利。 ";
			link.l1 = "但我解决了他。 他走了! 哦, 去你的... 加勒比海还有很多其他事情可做。 再见。 ";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//清除以便回滚到荷兰选项
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "太好了! 我自己保留手指。 现在看看他口袋里的东西。 让我们看看你带来了什么。 ";
			link.l1 = "去吧, 看看... ";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "啊哈, 这就是我需要的全部。 干得好! 你做得很好。 我对你非常满意。 ";
				link.l1 = "谢谢! 工作做得好时得到表扬总是很高兴的。 ";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "嗯... 我警告过你, 我知道罗德里格斯永远不会不带什么东西。 而我在这里没有看到我需要的东西。 你把那些东西私吞了吗? 你把它们弄丢了吗? 反正都没关系。 我不想再和你有任何牵连。 滚出去。 ";
				link.l1 = "哦, 去你的... ";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//清除以便回滚到荷兰选项
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "这是我承诺的报酬, 三万比索。 我还有一个额外的。 高责任。 高风险的任务, 但报酬也会相应提高, 四万比索。 ";
			link.l1 = "我洗耳恭听。 下一个客户是谁? ";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//第二个任务
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "这次你要猎取的不是一个人, 而是一件物品。 你必须潜入安提瓜岛理查德.弗利特伍德的家中, 偷走他的日志。 他是一名英国船长。 这个地方戒备森严, 而理查德本人很少光顾他的家\n计划很简单。 圣琼斯的总督将在十天后举办一个私人派对, 弗利特伍德会参加。 你必须在夜间一点到三点之间潜入他的家。 里面只会有一名士兵\n解决掉他。 在理查德的公寓里寻找一本日记。 拿着这把钥匙。 ";
			link.l1 = "嗯... 有意思。 我明白我需要做什么了。 我准备好出发了! ";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "小心点。 在我指定的日期之前不要潜入房子。 否则, 最好的情况是他们只是把你赶出去, 最坏的情况是你会进监狱。 向我重复日期和时间。 ";
			link.l1 = "正好十天后, 凌晨一点到三点之间。 ";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "很好。 你可以走了。 祝你好运! ";
			link.l1 = "谢谢你, 加斯顿。 ";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//其他选项不再可能
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//关闭房间
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//放在衣柜里
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//还有沙漏
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//房子里有4个士兵
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守截止日期! ");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//计时器
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//门可以打开
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//如果他想提前出现
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("不, 我没听说过。 我们有草药师和医生, 但没有一个叫这个名字的。 ","这是我第一次听到这么奇怪的名字。 不, 我们从未有过你所说的那个人来访。 ","我们根本没有任何炼金术士。 我们有医生, 但没有一个叫这么奇怪名字的。 ");
			link.l1 = "我明白了。 太遗憾了。 我会继续寻找! ";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}

string FindSpainCity()//Jason选择一个随机的西班牙城市 - 让他逃吧
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}