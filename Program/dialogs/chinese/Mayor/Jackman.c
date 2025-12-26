// 雅各布.杰克曼
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sLoc;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

// ============================= 愤怒模块 ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //首次触发陷阱
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //此处配置愤怒反应。 npchar.angry.name 已删除空格!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= 愤怒模块 ===================================
// ============================================================================

    switch(Dialog.CurrentNode)
    {
        // --------------------------------- —首次对话 - 初次见面
        case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都在生你的气, 小子, 你最好离开这里... ", "看来你疯了, 小子。 想活动一下手脚? 无意冒犯, 但你在这里无事可做。 滚吧! ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "帮我解决这个问题... ");
                link.l1.go = "pirate_town";
                break;
            }
			
			link.l0 = ""+npchar.name+", 我想和你谈谈我在海上的安全问题。 " + GetSexPhrase("兄弟们","姐妹们") + "对我这点微不足道的名声表现得过于热情。 你能不能帮我敲打敲打他们?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("你有什么事要告诉我吗? 没有? 那就滚开! ",
                         "我想我已经说清楚了, 别再烦我。 ", "尽管我说得很清楚, 你还是在烦我! ",
                         "好吧, 我受够这种无礼了。 ", "repeat", 3, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("我这就走。 ",
                                               "好的, "+npchar.name+"... ",
                                               "抱歉, "+npchar.name+"... ",
                                               "哎哟... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "First time";

            //--> 传奇任务
            if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
            {
                link.l1 = "我在哪里可以找到吉米.希金斯? ";
                link.l1.go = "Saga_Jimmy";
            }    
            if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
            {
                link.l1 = "又是我, 杰克曼。 他们说你在找一些失踪的人... ";
                link.l1.go = "Saga_search";
            }    
            //< —传奇任务

            //船长委托 - 赎金
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
            {
                if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
                {
                    link.l1 = "是关于你的囚犯的事。 ";
                    link.l1.go = "CapComission1";
                    DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
                }    
                if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
                {
                    link.l1 = "你好, 杰克曼。 关于你的任务... ";
                    link.l1.go = "CapComission3";
                }
                if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
                {
                    link.l1 = "是关于你的囚犯的事。 ";
                    link.l1.go = "CapComission6";
                }
            }    
        break;

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都在生你的气, 小子, 你最好离开这里... ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "帮我解决这个问题... ");
                link.l1.go = "pirate_town";
                break;
            }
			
			link.l0 = ""+npchar.name+", 我想和你谈谈我在海上的安全问题。 " + GetSexPhrase("兄弟们","姐妹们") + "对我这点微不足道的名声表现得过于热情。 你能不能帮我敲打敲打他们?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("你有什么事要告诉我吗? 没有? 那就滚开! ",
                         "我想我已经说清楚了, 别再烦我。 ", "尽管我说得很清楚, 你还是在烦我! ",
                         "好吧, 我受够这种无礼了。 ", "repeat", 3, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("我这就走。 ",
                                               "好的, "+npchar.name+"... ",
                                               "抱歉, "+npchar.name+"... ",
                                               "哎哟... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "First time";

            //船长委托 - 赎金
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
            {
                link.l1 = "是关于你的囚犯的事。 ";
                link.l1.go = "CapComission1";
                DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
            }                
        break;

//-----------------------------------------海盗传奇----------------------------------------------------
        case "Saga_Jimmy":
            dialog.text = "真的! 有人需要这个懒鬼! 他已经在自己的小屋里独自喝了好几天朗姆酒了。 我不建议你去拜访他。 即使他清醒的时候, 也不是什么好人... ";
            link.l1 = "没关系, 我也不是圣人。 他的小屋在哪里? ";
            link.l1.go = "Saga_Jimmy_1";
        break;
        
        case "Saga_Jimmy_1":
            dialog.text = "就在酒馆前面。 他选了个好地方, 方便快速跑去喝酒。 ";
            link.l1 = "谢谢! ";
            link.l1.go = "Saga_Jimmy_2";
        break;
        
        case "Saga_Jimmy_2":
            DialogExit();
            pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
            pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
            pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
            pchar.questTemp.Saga = "jimmy";
        break;
        
        case "Saga_search":
            dialog.text = "谁告诉你的? 那个醉鬼希金斯? 你找到关于格拉迪斯.钱德勒或刽子手亨利的什么线索了吗? ";
            link.l1 = "说实话, 没什么特别的, 但我想知道关于那个刽子手的具体情况。 ";
            link.l1.go = "Saga_search_1";
        break;
        
        case "Saga_search_1":
            dialog.text = "没什么好知道的。 现在很少有人记得他了, 但二十年前, 亨利在从布里奇敦到托尔图加的妓女中很受欢迎。 你敢打赌! 他是‘Neptune’的水手长, 由屠夫船长亲自指挥! 当然, 如果他还活着, 现在一定很老了。 \n机会很低, 但你知道, 没有什么是不可能的。 任何关于他的信息我都付两万比索, 如果你能活着把他带来, 就翻倍。 ";
            link.l1 = "你愿意为格拉迪斯和她的女儿付多少钱? ";
            link.l1.go = "Saga_search_2";
        break;
        
        case "Saga_search_2":
            dialog.text = "哦, 她不是她的女儿。 如果你能活着把那个女孩带来, 我会付你一堆达布隆。 我对格拉迪斯不感兴趣。 还有问题吗? ";
            link.l1 = "我希望我能知道这么麻烦的原因, 但我不会问。 看起来这可能会缩短我的寿命。 ";
            link.l1.go = "Saga_search_3";
        break;
        
        case "Saga_search_3":
            dialog.text = "也许吧... 这些秘密与你无关。 知道得越少, 活得越久。 别再问我这样的问题了, 因为我开始怀疑你有问题。 在我改变主意之前滚吧。 ";
            link.l1 = "再见, 男爵! ";
            link.l1.go = "Saga_search_4";
        break;
        
        case "Saga_search_4":
            DialogExit();
            AddQuestRecord("Saga", "6");
            if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
            {
                AddQuestUserData("Saga", "sText", "现在去安提瓜。 必须登上那艘护卫舰。 ");
                DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
            }
            pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
            pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
            pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
            pchar.questTemp.Saga = "donovan";
        break;
        
        // 登船, 在船舱里
        case "Jackman_abordage":
            dialog.text = "哈! 我们又见面了, " +GetFullName(pchar)+ "船长。 我承认, 你是个值得尊敬的对手, 尽管你在马龙镇试图把自己塑造成一个傻瓜。 我发现了一些关于你的事情, 你与荷兰西印度公司的阴谋被揭露了... 我现在明白你是什么样的人了。 ";
            link.l1 = "我也知道你的类型, 雅各布。 所以我们别再自欺欺人了。 ";
            link.l1.go = "Jackman_abordage_1";
        break;
        
        case "Jackman_abordage_1":
            dialog.text = "你是如何用‘马林号’欺骗我的! 我想我可怜的弟弟已经死了... ";
            link.l1 = "我猜你想为他报仇? 但我也有一长串账要跟你算。 为走投无路的纳撒尼尔。 他的妻子。 他的护卫舰。 被诽谤的鲨鱼。 Blaze Sharp... ";
            link.l1.go = "Jackman_abordage_2";
        break;
        
        case "Jackman_abordage_2":
            dialog.text = "Blaze? 我没有杀他。 ";
            link.l1 = "即使这是真的, 我名单上的其余人也足够了。 我厌倦了你的名字。 够了, 杰克曼! 我们的刀刃会说话! ";
            link.l1.go = "Jackman_abordage_3";
        break;
        
        case "Jackman_abordage_3":
            dialog.text = "如此冲动的傻瓜.. 该死的! 现在你最好坚持住! 雅各布.杰克曼从未被打败过! 卡帕乔, 你来得正是时候! 过来! ";
            link.l1 = "... ";
            link.l1.go = "Jackman_abordage_4";
        break;
        
        case "Jackman_abordage_4":
            DialogExit();
            LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogFree();
            LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
            AddDialogExitQuest("MainHeroFightModeOn");
            // 支援
            int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
            int iScl = 30 + 2*sti(pchar.rank);
            sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
            LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
            LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
            ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            sld = characterFromId("Danielle");
            RemovePassenger(Pchar, sld);
        break;

        //*************************** 生成器 "船长的提议 - 赎金" **********************
        case "CapComission1":
            dialog.text = "哈哈。 你以为我这里只有一个囚犯吗? 说出他的名字。 ";
            link.l1 = pchar.GenQuest.CaptainComission.SlaveName + "。 他在这里吗? ";
            link.l1.go = "CapComission2";
            DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
        break;

        case "CapComission2":
            if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
            {
                dialog.text = "他以前在。 一周前巴巴多斯的种植园主毕晓普上校来的时候, 我把他卖给了他。 ";
                link.l1 = "该死的... ";
                link.l1.go = "CapComission2_1";
            }
            else
            {
                dialog.text = "啊, 终于来了。 我正想把他卖给那个巴巴多斯的种植园主, 他一两周后会来... 你有赎金吗? ";
                link.l1 = "听着, 有个小问题... 实际上, 我没有那么多钱。 但我愿意工作。 ";
                link.l1.go = "CapComission2_2";
                if(makeint(pchar.money) > 150000)
                {
                    link.l2 = "幸好你还没卖掉他。 这是15万比索。 我在哪里可以找到他? "
                    link.l2.go = "CapComission2_3";
                }    
            }
        break;
        
        case "CapComission2_1":
            dialog.text = "你太慢了... 你为什么关心他? 我一直在和他的亲戚谈判。 ";
            link.l1 = "他们让我来这里。 ";
            link.l1.go = "CapComission2_11";
        break;
        
        case "CapComission2_11":
            dialog.text = "好吧, 你迟到了。 我无能为力。 ";
            link.l1 = "听着, 如果不是秘密的话, 你把他卖了多少钱? "; 
            link.l1.go = "CapComission2_12";
        break;
        
        case "CapComission2_12":
            dialog.text = "嗯, 这不是。 但我不会告诉你... 如果你知道了会笑的。 哈哈哈哈! 再见。 ";
            link.l1 = "再见... ";
            link.l1.go = "exit";
            AddQuestRecord("CaptainComission1", "10");
            AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
            //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
            CaptainComission_GenerateManager();
        break;
        
        case "CapComission2_2":
            if(rand(1) == 0)
            {
                dialog.text = "好吧, 好吧.. 我有一些生意... 甚至不知道如何开始。 我需要击沉一个越界的海盗。 ";
                link.l1 = "不能在丛林里杀了他吗? ";
                link.l1.go = "CapComission2_2_1";
            }
            else
            {
                dialog.text = "好吧, " +pchar.name+ ", 你知道, 事情不是这样的。 带着钱回来, 你就会得到你的弱者, 哈哈。 ";
                link.l1 = "好的。 再见。 ";
                link.l1.go = "CapComission2_4";
            }
        break;

		case "CapComission2_2_1":
			dialog.text = "你知道, 这可不是做生意的方式... 我不需要他死, 我要给其他人一个教训, 让他们别打我那份赃物的主意。 不过要是他喂了鲨鱼, 我也不会难过。 ";
			link.l1 = "你为什么不派自己的人去追他? ";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "嗯... 听着, "  + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " 煽动了一些海盗, 让他们相信我们在离" + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + "不远的地方藏有他们的那份赃物。 他们的两艘船'" + pchar.GenQuest.CaptainComission.ShipName1 + "'和'" + pchar.GenQuest.CaptainComission.ShipName2 + "'不久前起锚, 朝着" + sLoc + "驶去了。 现在你明白为什么我不能派自己的人去完成这个任务了吧? ";
			link.l1 = "明白了。 我有多少时间? ";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "我想最多12到15天。 我不希望他们先找到藏匿点, 否则击沉载有贵重货物的船只就毫无意义了。 那样的话, 他们把货物带到这里反而更好... ";
			link.l1 = "好吧, 我接下了。 我会尽力追上他们。 ";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "别担心。 我的人会把他送到你的船上。 你为什么关心他? ";
			link.l1 = "我不关心。 是他的亲戚让我来送他的。 ";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "啊, 那很好。 我几乎为给你那个人这么低的价格而感到抱歉。 哈哈哈哈。 再见。 ";
			link.l1 = "再见。 ";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "那么, " +GetFullName(pchar)+ ", 你击沉我的伙伴了吗? 嘿嘿嘿... ";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "没有。 我没能抓住他们。 而且我在回来的路上也没遇到他们。 ";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "我做到了。 我把他们送去喂鲨鱼了。 ";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "该死! 遇到他们与否, 现在都不重要了! 你接下来有什么建议? ";
			link.l1 = "也许你有更简单的工作给我? ";
			link.l1.go = "CapComission4_1";
			link.l2 = "听着, 杰克曼, 把囚犯的价格降下来... ";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "没有。 ";
			link.l1 = "那么再见... ";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "降价? 由于你的无能, 我刚刚失去了我的藏匿点! 现在我可以提高价格! 如果你想要, 你可以用20万比索带走他, 否则你就滚出这里。 ";
			link.l1 = "太贵了... 再见... ";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "该死的, 拿上你的钱。 ";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "好吧, 你可以带走这个弱者... ";
			link.l1 = "再见。 ";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "嗬嗬! 干得好! 带上你的弱者, 祝你好运。 ";
			link.l1 = "谢谢。 再见。 ";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "查尔斯, 你把钱带来了吗? 我之前说要把那人卖到种植园可不是开玩笑的。 ";			
			link.l1 = "听着, " + Npchar.name+ ", 有个问题... 我没有那么多钱。 但我愿意干活抵账。 ";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "幸好你还没把他卖掉。 这是15万比索。 我在哪儿能接到他? "
				link.l2.go = "CapComission2_3";
			}			
		break;
		
		// ============== 光天化日之下的抢劫, 试图打开箱子 =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("抢劫!!! 这是不可接受的! 准备好, " + GetSexPhrase("小子","丫头") + "... ", "嘿, 你在那儿搞什么鬼? 以为你能抢劫我? 你完蛋了... ", "等等, 搞什么鬼? 把手拿开! 原来你是个小偷! 你的死期到了, 混蛋... ");
			link.l1 = LinkRandPhrase("该死! ", "卡兰巴!! ", "该死的!! ");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== 愤怒节点模块 ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("从这里滚开! ","滚出我的家! ");
			link.l1 = "哎呀... ";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //与杰克曼在10天后和解。 
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "别用你廉价的话语来烦我。 下次你不会喜欢结果的... ";
        			link.l1 = "我知道了。 ";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "结束了, 没什么好说的。 " "我不想再和你说话了, 所以你最好别烦我。 ";
			link.l1 = RandPhraseSimple("如你所愿... ", "那好吧... ");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //与杰克曼在10天后和解。 
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "我希望你能表现出更多的尊重, 不再无礼? 否则我就不得不杀了你。 那会非常不愉快。 ";
        			link.l1 = "你可以放心, 杰克曼, 我会的。 ";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= 愤怒节点模块 =============================
		case "pirate_town":
            dialog.text = "解决问题? 你明白你做了什么吗? 无论如何, 给我一百万比索, 我会说服伙计们忘记你的‘壮举’。 如果你不喜欢这个主意, 那你可以去死了。 ";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "好的, 我准备付钱。 ";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "知道了。 我这就走。 ";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//关闭传送
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "好! 算你又清白了。 但我希望你不会再做这种令人厌恶的事情了。 ";
			link.l1 = "我不会了。 对我来说太贵了。 再见... ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("今天我们已经讨论过这个问题了。",
													  "我说得还不够清楚吗?",
													  "你这烦人的劲儿快把我逼疯了。",
													  "我已经受够了。滚出去!",
													  "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("那就改天再说吧…… ",
												   "当然, "+npchar.name+"…… ",
												   "对不起, "+npchar.name+"…… ",
												   "呃…… ", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "哈! 看来咱们兄弟最近没少让你头疼, " + GetSexPhrase("伙计", "姑娘") + "? 我当然可以暂时让他们收敛点。 不过你得大出血一回。 " + FindRussianDublonString(iBarbazonTotalTemp) + "放在桌上, 我们就算谈妥了。";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "当然, 这是你的钱。";
					else link.l0 = "看样子我没得选。这是你的钱。";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "那我还是改天再来吧…… ";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "你疯了" + GetSexPhrase("", "吗") + "? 兄弟们一看到你就像见了瘟疫一样闪得远远的。 别烦我, 赶紧走人。";
				else
					dialog.text = "你在说啥, " + GetSexPhrase("伙计", "姑娘") + "? 你这人惹人烦得很, 连狗都不乐意跟你扯上关系。 谁都不想搭理你。";
				link.l1 = "明白了…… ";
				link.l1.go = "exit";
			}
		break;
	}
}