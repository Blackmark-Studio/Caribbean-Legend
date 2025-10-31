// 勒弗朗索瓦的雅克.巴尔巴宗
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------愤怒模块-------------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) // 首次触发陷阱
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) // 此处配置愤怒反应 (npchar.angry.name 已去除空格) 
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
//< —-------------------------------------------愤怒模块------------------------------------------------------

    switch(Dialog.CurrentNode)
    {
    // --------------------------------- —首次对话 - 初次见面---------------------------------------
        case "First time":
            dialog.text = NPCStringReactionRepeat("你有什么事要告诉我吗? 没有? 那就滚开! ",
                         "我想我已经说清楚了, 别再烦我。 ", "尽管我说得很清楚, 你还是在烦我! ",
                         "好吧, 我受够这种无礼了。 ", "repeat", 3, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("我这就走。 ",
                                               "好的, 雅克... ",
                                               "抱歉, 雅克... ",
                                               "哎哟... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "First time";
			
            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都在生你的气, 小子, 你最好离开这里... ", "看来你脑子坏了, 小子。 想活动下筋骨? 无意冒犯, 但你在这里无事可做, 滚吧! ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "帮我解决这个麻烦... ");
                link.l1.go = "pirate_town";
                break;
            }
			
        //----------------------------------传奇 - 巴尔巴宗的诱惑---------------------------------------
            if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
            {
                link.l1 = "我需要和你谈谈, 雅克... 私下谈。 ";
                link.l1.go = "Temptation";
            }
            if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
            {
                link.l1 = "我从圣马丁来, 雅克... ";
                link.l1.go = "Temptation_6";
            }
            if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
            {
                link.l1 = "雅克, 你打算什么时候别再乱吠, 像个男人一样说话? 没想到会见到我吧? ";
                link.l1.go = "terrax";
            }
			
            // 船长委托 - 赎金
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
            {
                if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
                {
                    link.l1 = "我来是为了你的囚犯。 ";
                    link.l1.go = "CapComission1";
                    DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
                }
             	
                if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // 樵夫: 新检查, 排除跳过15天直接交任务的可能
                {
                    link.l1 = "你好, 雅克, 我来是为了你的任务。 ";
                    link.l1.go = "CapComission3";
                }
                if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar, "GenQuest.CaptainComission.vikupzaplatil")) 
                { // 樵夫: 第二次对话检查, 若主角未支付赎金
                    link.l1 = "我来是为了你的囚犯。 ";
                    link.l1.go = "CapComission6";
                }
            }    
            if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
            {
                link.l1 = "我听说你在做与囚犯相关的生意... ";
                link.l1.go = "Marginpassenger";
            }
        break;
            

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + "! 你这次需要什么? ",
                         "你是不是忘了什么事要告诉我? 我在听。 ", "这要持续多久... 如果你没事做, 就别打扰别人! ",
                         "你让我礼貌待人, 但我也要求你同样礼貌! ", "repeat", 10, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("没什么, 只是来看看。 ",
                                               "没什么... ",
                                               "好吧... ",
                                               "你说得对, 抱歉。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "I_know_you_good";

            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都在生你的气, 小子, 你最好离开这里... ", "看来你脑子坏了, 小子。 想活动下筋骨? 无意冒犯, 但你在这里无事可做, 滚吧! ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "帮我解决这个麻烦... ");
                link.l1.go = "pirate_town";
                break;
            }

            // 船长委托 - 赎金
            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
            {
                link.l1 = "我来是为了你的囚犯。 ";
                link.l1.go = "CapComission1";
                DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
            }    
            if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // 樵夫修正: 新检查, 排除在此直接交任务
            {
                link.l1 = "你好, 雅克, 是关于你的任务。 ";
                link.l1.go = "CapComission3";
            }
            /* if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak")) // 樵夫冗余对话
            {
                link.l1 = "我来是为了你的囚犯。 ";
                link.l1.go = "CapComission6";
            }*/
            if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
            {
                link.l1 = "我听说你在做与囚犯相关的生意... ";
                link.l1.go = "Marginpassenger";
            }
        break;

//--> -----------------------------------传奇 - 巴尔巴宗的诱惑---------------------------------------------
        case "Temptation":
            dialog.text = "你知道打扰我很危险吗? 好吧, 我听你说。 ";
            link.l1 = "我欠了债, 一大笔债。 还款期限快到了, 但我没钱。 好心人说你擅长制定计划, 总能知道哪里能赚大钱... ";
            link.l1.go = "Temptation_1";
        break;
        
        case "Temptation_1":
            dialog.text = "听着, 小子! 我‘善良的雅克’只对忠于我的人友善, 对其他人我是巴尔巴宗, 有时甚至是路西法。 我怎么知道能信任你? ";
            link.l1 = "考验我吧, 我发誓你不会后悔! ";
            link.l1.go = "Temptation_2";
        break;
        
        case "Temptation_2":
            dialog.text = "嗯... 我想你知道‘善良的雅克’会怎么对待欺骗他的人, 对吧? 不管怎样, 我不会用可怕的细节吓你。 我有个小任务, 如果你成功了, 所有财务问题都解决了。 ";
            link.l1 = "别怀疑我, 我经历过很多战斗, 而且... ";
            link.l1.go = "Temptation_3";
        break;
        
        case "Temptation_3":
            dialog.text = "闭嘴听我说! 几周前, 一支荷兰巡逻队在圣马丁附近抓获了我的一名手下, 他当时在给我运送荷兰丝绸。 这东西很稀有, 荷兰人只运来少量供公司海军使用。 \n我好不容易弄到了六包丝绸, 西蒙.莫雷尔本该用他的双桅帆船‘盐狗号’运来, 但他意外遭遇了荷兰巡逻队 —或许不是意外。 莫雷尔的领航员说他是战斗中唯一的幸存者, \n还交给我莫雷尔的航海日志, 证实了这个故事。 根据日志, 莫雷尔在逃跑时扔掉了丝绸。 很奇怪, 对吧? 丝绸很轻, 他们本该扔掉大炮, 反正也打不过巡逻队。 ";
            link.l1 = "这里面肯定有问题。 ";
            link.l1.go = "Temptation_4";
        break;
        
        case "Temptation_4":
            dialog.text = "什么可能都有。 为我工作的勇士很多, 但聪明的不多。 无意冒犯, 呵呵。 你必须去莫雷尔丢弃货物的地点看看, 根据船长日志, 坐标是北纬21度10分, 西经61度30分。 \n荷兰人把丝绸绕在软木杆上, 所以包裹应该还浮在水面上, 应该有六包。 立即起航, 时间很关键。 ";
            link.l1 = "我这就去! ";
            link.l1.go = "Temptation_5";
        break;
        
        case "Temptation_5":
            DialogExit();
            SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // 计时器
            if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请遵守最后期限! ");
            pchar.quest.BarbTemptation.win_condition.l1 = "location";
            pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
            pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
            pchar.questTemp.Saga.BarbTemptation = "silk";
            AddQuestRecord("BarbTemptation", "2");
        break;
        
        case "Temptation_6":
            dialog.text = "太好了! 找到我的丝绸了吗? ";
            link.l1 = "找到了, 正如你说的六包。 ";
            link.l1.go = "temptation_wrong";
            if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
            {
                link.l2 = "找到了, 但比你说的多, 有九包, 不是六包。 我全带来了, 你自己想想怎么回事吧。 ";
                link.l2.go = "temptation_right";
            }
        break;
        
        case "temptation_wrong":
            dialog.text = "回答错误。 应该有九包。 如果你找到了六包, 就该找到剩下的。 所以你要么是个骗子, 要么就是个懒惰的白痴。 你欠我三包丝绸, 再加三包作为... ‘道德补偿’, 因为你想骗我。 ";
            if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
            {
                link.l1 = "你可真精明! 我会记住的。 这是你的丝绸, 忘了我的错吧。 ";
                link.l1.go = "temptation_wrong_1";
            }
            link.l2 = "我听说只有六包, 没多的。 我把找到的都给你了, 不在乎你怎么想, 我没有更多丝绸了。 ";
            link.l2.go = "temptation_wrong_2";
        break;
        
        case "temptation_wrong_1":
            RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
            dialog.text = "很好。 希望别再发生这种事, 因为我想给你一个重要任务。 你想赚多少钱? ";
            link.l1 = "钱总是受欢迎的, 现在五万比索就好。 ";
            link.l1.go = "junior";
        break;
        
        case "temptation_wrong_2":
            dialog.text = "哦, 你现在这么说话! 你不会就这么算了的。 我警告过你 —别他妈骗我! 卫兵! 住宅里有个该死的骗子! ";
            link.l1 = "该死! ";
            link.l1.go = "temptation_wrong_fight";
        break;
        
        case "temptation_wrong_fight":
            chrDisableReloadToLocation = true; // 关闭地点传送
            DialogExit();
            LAi_SetWarriorType(npchar);
            ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
            LAi_SetImmortal(npchar, true);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            for (i = 1; i <= 3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
                FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
                ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
                LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            AddDialogExitQuest("MainHeroFightModeOn");    
        break;
        
        case "temptation_right":
            RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
            dialog.text = "干得好。 我在测试你的贪婪, 你通过了考验。 本来就该有九包, 其中一包是你的。 现在我们可以认真谈谈了。 你需要多少钱? ";
            link.l1 = "钱总是受欢迎的, 现在五万比索就好。 ";
            link.l1.go = "junior";
        break;
        
        case "junior":
            dialog.text = "你有机会赚更多。 有个大人物让我找个像你这样可靠的人, 执行一项微妙而危险的任务。 这个人很富有, 如果你不辜负他, 他会给你相应的报酬。 ";
            link.l1 = "我准备好了。 ";
            link.l1.go = "junior_1";
        break;
        
        case "junior_1":
            dialog.text = "很好。 听着, 你要找到他的代理人, 名叫‘无赖’, 他是双桅纵帆船‘马林号’的船长, 我只知道这些。 你可以在卡普斯特维尔找到他, 暗号是‘the hunt has begun’(狩猎开始了)。 他会告诉你该做什么。 你不欠我什么, 我只是想帮你。 如果你够幸运, 我们会再见面的。 ";
            link.l1 = "谢谢你的帮助, 我这就去! ";
            link.l1.go = "junior_2";
        break;
        
        case "junior_2":
            DialogExit();
            AddQuestRecord("BarbTemptation", "7");
            Saga_SetJuniorInCharles(); // 设置瓦莱塔
            pchar.questTemp.Saga.BarbTemptation = "valet";
        break;
		
        case "terrax":
            dialog.text = "什么? ! 我要把你... ";
            link.l1 = "你不会的, 巴尔巴宗。 咱们亮底牌吧! 我为扬.斯文森效力。 我已经揭露了你和杰克曼的阴谋。 我知道一切, 包括你们的计划和你的角色。 杰克曼和他弟弟都死了, 前者杀了Blaze Sharp, 这决定了他的命运, 而后者恐怕不太会说话... ";
            link.l1.go = "terrax_1";
        break;
        
        case "terrax_1":
            dialog.text = "该死! 泰雷克斯永远不会原谅我, 但我仍然... ";
            link.l1 = "别做傻事, 雅克。 我知道这不会是轻松的谈话, 所以我做好了准备。 看看窗外... 你的小屋被我的火枪手包围了。 我的人遍布你的村庄, 门外还有一支突击队。 想开始屠杀吗? 太简单了! ";
            link.l1.go = "terrax_2";
        break;
        
        case "terrax_2":
            dialog.text = "该死的! 你想要什么? ";
            link.l1 = "你不会相信的, 巴尔巴宗, 但我想要的只是... 和平! 我想要和平。 所以我不会告诉泰雷克斯你在反他的阴谋中扮演的角色。 但前提是你按我说的做... ";
            link.l1.go = "terrax_3";
        break;
        
        case "terrax_3":
            dialog.text = "你想从我这里得到什么? 钱? 多少? ";
            if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // 鲨鱼存活
            {
                link.l1 = "哦不, 把钱留给你那些没脑子的代理人吧。 我需要别的东西。 我需要你投票给史蒂文.多德森。 ";
            }
            else
            {
                link.l1 = "哦不, 把钱留给你那些没脑子的代理人吧。 我需要别的东西。 我需要你投票给马库斯.泰雷克斯。 ";
            }
            link.l1.go = "terrax_4";
        break;
        
        case "terrax_4":
            if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "而且史蒂文.多德森是我们这边的。 ";
            else sTemp = "";
            dialog.text = "认真的吗? 让我想想... 如果我拒绝呢? ";
            link.l1 = "那你将孤立无援, 彻底孤立。 斯文森。 泰雷克斯和霍克都会反对你。 " + sTemp + "我只需要给他们看‘无赖’的信。 杰克曼的弟弟, 我的话也会被相信。 现在你觉得, 在那之后你还能在你舒适的位置上坐多久? ";
            link.l1.go = "terrax_5";
        break;
        
        case "terrax_5":
            dialog.text = "霍克? 他还活着? ! ";
            link.l1 = "是的。 我把他从杰克曼设的陷阱里救了出来。 所以雅各布最亲密的朋友将成为他的死敌。 记住, 巴尔巴宗, 我会加入他们。 ";
            link.l1.go = "terrax_6";
        break;
        
        case "terrax_6":
            dialog.text = "杰克曼不是我的朋友! 该死的! 你把我逼到绝路了! ";
            link.l1 = "胡说。 按我说的给那个人投票, 你不会有任何改变。 我已经告诉过你, 雅克, 我想要和平。 我可以让所有男爵都恨你, 但我不会... 暂时不会。 ";
            link.l1.go = "terrax_7";
        break;
        
        case "terrax_7":
            GiveItem2Character(pchar, "splinter_jb"); // 给予碎片
            dialog.text = "好吧, 我同意。 我向你保证。 拿着, 这是我的石片, 你需要它, 对吗? ";
            link.l1 = "没错。 很高兴我们达成了协议, 雅克。 把‘无赖’的信当作甜蜜的纪念吧。 或者最好烧掉它, 你不会想让它被发现的。 哦, 还有最后一件事... ";
            link.l1.go = "terrax_8";
        break;
        
        case "terrax_8":
            RemoveItems(pchar, "letter_chad", 1);
            dialog.text = "最后一件事? ! 你还想从我这里得到什么? ";
            if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
            {
                link.l1 = "让我提醒你一些事。 不久前你派你的狗伊格纳西奥.马可来暗杀我。 是我杀了他。 是我破坏了你掠夺西班牙运金大帆船的计划。 是我把你的朋友引到圣马丁附近的西班牙埋伏圈。 我叫查理.普林斯! 我们现在两清了, 雅克, 下次见面时对我礼貌点。 相信我, ‘小子’, 我们会再见面的, 我猜不止一次。 ";
                link.l1.go = "terrax_8_1";
            }
            else
            {
                if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
                {
                    link.l1 = "让我提醒你一些事。 不久前你派你的狗伊格纳西奥.马可来暗杀我。 是我杀了他。 是我破坏了你掠夺西班牙运金大帆船的计划。 我叫查理.普林斯! 我们现在两清了, 雅克, 下次见面时对我礼貌点。 相信我, ‘小子’, 我们会再见面的, 我猜不止一次。 别忘了, 所有海盗男爵都站在我这边。 再见, 巴尔巴宗... ";
                    link.l1.go = "terrax_9";
                }
                else
                {
                    link.l1 = "下次见面时对我礼貌点。 相信我, ‘小子’, 我们会再见面的, 我猜不止一次。 别忘了, 所有海盗男爵都站在我这边。 再见, 巴尔巴宗... ";
                    link.l1.go = "terrax_9";
                }
            }
        break;
        
        case "terrax_8_1":
            dialog.text = "";
            link.l1 = "别忘了, 所有海盗男爵都站在我这边。 再见, 巴尔巴宗... ";
            link.l1.go = "terrax_9";
        break;
        
        case "terrax_9":
            DialogExit();
            NextDiag.CurrentNode = "I_know_you_good";
            AddQuestRecord("BarbTemptation", "26");
            if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
            for (i=1; i<=2; i++)
            {
                sld = characterFromId("Saga_SGM_"+i);
                LAi_SetCitizenType(sld);
                LAi_SetActorType(sld);
                LAi_ActorFollow(sld, pchar, "", -1);
                sld.lifeday = 0;
            }
            ChangeCharacterComplexReputation(pchar, "fame", 1);
            bDisableFastReload = false;
            LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
        break;

//-----------------------------------船长委托 - 赎金-------------------------------------------------
        case "CapComission1":
            dialog.text = "哈哈。 你以为我这里只有一个囚犯吗? 说出他的名字。 ";
            link.l1 = pchar.GenQuest.CaptainComission.SlaveName + "。 他在这里吗? ";
            link.l1.go = "CapComission2";
            DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
        break;

        case "CapComission2":
            if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
            {
                dialog.text = "他之前在。 一周前巴巴多斯的种植园主毕晓普上校来这里时, 我把他卖给了他。 ";
                link.l1 = "该死... ";
                link.l1.go = "CapComission2_1";
            }
            else
            {
                dialog.text = "啊, 终于来了。 我正想把他卖给那个巴巴多斯的种植园主, 他一两周后会来... 你有赎金吗? ";
                link.l1 = "听着, 有个小问题... 实际上, 我没有那么多钱。 但我愿意工作。 ";
                link.l1.go = "CapComission2_2";
                if(makeint(pchar.money) > 150000)
                {
                    link.l2 = "幸好你还没卖掉他。 这是你的硬币 —15万比索。 我在哪里可以找到他? ";
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
            dialog.text = "呃, 这不是秘密。 但我不会告诉你... 我说了你会笑的。 哈哈哈哈! 再见。 ";
            link.l1 = "再见。 ";
            link.l1.go = "exit";
            AddQuestRecord("CaptainComission1", "10");
            AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//樵夫修正: 在SЖ中下方记录不工作
            //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
            CaptainComission_GenerateManager();
        break;
        
        case "CapComission2_2":
            if(rand(3) == 1)
            {
                dialog.text = "好吧, " +pchar.name+ ", 你知道, 事情不是这样的。 带钱回来, 你就会得到你的弱者, 哈哈。 ";
                link.l1 = "好的。 再见。 ";
                link.l1.go = "CapComission2_4";
            }
            else
            {
                dialog.text = "嗯, 嗯... 我有件事... 甚至不知道怎么开始。 我需要击沉一个越界的海盗。 ";
                link.l1 = "不能在丛林里杀了他吗? ";
                link.l1.go = "CapComission2_2_1";
            }
        break;

        case "CapComission2_2_1":
            dialog.text = "你知道, 这不是做生意的方式... 我不需要他死, 我需要教一些人别拿我的战利品份额。 但如果他去喂鲨鱼, 我也不会难过。 ";
            link.l1 = "你为什么不派自己的人去追他? ";
            link.l1.go = "CapComission2_2_2";
        break;
        
        case "CapComission2_2_2":
            CaptainComission_GetRandomShore();
            pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
            pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
            pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
            sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
            dialog.text = "嗯... 好吧, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + "说服了一些海盗, 说他们的战利品份额藏在我们离" + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + "不远的藏匿处。 他们的两艘船‘" + pchar.GenQuest.CaptainComission.ShipName1 + "’和‘" + pchar.GenQuest.CaptainComission.ShipName2 + "’不久前起航前往" + sLoc + "。 现在你明白为什么我不能信任我的人去做那件事了吧? ";
            link.l1 = "我明白。 我有多少时间? ";
            link.l1.go = "CapComission2_2_3";
        break;
        
        case "CapComission2_2_3":
            dialog.text = "最多12到15天, 如果他们不到达藏匿处对我很重要, 否则击沉他们和贵重货物就毫无意义。 在那种情况下, 他们把货物带到这里会更好... ";
            link.l1 = "好的, 我加入。 我会尽力抓住他们。 ";
            link.l1.go = "CapComission2_2_4";
        break;
        
        case "CapComission2_2_4":
            AddQuestRecord("CaptainComission1", "24");
            AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//修正
            //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//在SЖ中名字不工作 。 樵夫
            AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
            AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
            AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
            AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
            pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
            SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
            DialogExit();
        break;
        
        case "CapComission2_3":
            dialog.text = "别担心。 我的人会把他送到你的船上。 你为什么关心他? ";
            link.l1 = "我不关心。 他的亲戚让我送他。 ";
            link.l1.go = "CapComission2_31";
        break;
        
        case "CapComission2_31":
            dialog.text = "啊, 那很好。 我几乎为给你那个人这么低的价格感到抱歉。 哈哈哈哈! 再见。 ";
            link.l1 = "再见。 ";
            link.l1.go = "CapComission2_32";
        break;
        
        case "CapComission2_32":
            AddQuestRecord("CaptainComission1", "9");
            AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
            addMoneyToCharacter(pchar, -150000);
            pchar.GenQuest.CaptainComission.vikupzaplatil = true; // 新检查, 如果夏尔为囚犯支付了赎金。 樵夫
            DialogExit();
            AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");    
        break;
        
        case "CapComission2_4":
            if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
            {
                AddQuestRecord("CaptainComission1", "31");
                AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");    // 樵夫
                //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); 在SЖ中不工作
            }    
            pchar.GenQuest.CaptainComission.RepeatSpeak = true;        
            DialogExit();
        break;
		
        case "CapComission3":
            dialog.text = "那么, " +GetFullName(pchar)+ ", 你把我的伙伴们解决了吗? 呵呵呵... ";
            if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
            {
                link.l1 = "没有。 我没能追上他们, 回来的路上也没遇到。 ";
                link.l1.go = "CapComission4";
            }
            if(pchar.GenQuest.CaptainComission.PirateShips == "died")    
            {
                link.l1 = "是的。 我已经送他们去喂鲨鱼了。 ";
                link.l1.go = "CapComission5";
            }
            DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
        break;
        
        case "CapComission4":
            dialog.text = "该死! 遇到没遇到都不重要了! 你接下来有什么打算? ";
            link.l1 = "也许你有更简单的任务给我? ";
            link.l1.go = "CapComission4_1";
            link.l2 = "听着, " + Npchar.name+ ", 把囚犯的价格降低点... ";
            link.l2.go = "CapComission4_2";
        break;
        
        case "CapComission4_1":
            dialog.text = "没有。 ";
            link.l1 = "那么再见... ";
            link.l1.go = "CapComission4_3";
        break;
        
        case "CapComission4_2":
            dialog.text = "降价? ! 因为你的无能, 我刚丢了我的 stash! 现在我甚至可以涨价! 如果你想要, 就拿20万比索来, 否则就滚出去。 ";
            link.l1 = "太贵了... 再见... ";
            link.l1.go = "CapComission4_4";
            if(sti(pchar.money) >= 200000)
            {
                link.l2 = "该死, 拿上你的钱。 ";
                link.l2.go = "CapComission4_5";
            }    
        break;
        
        case "CapComission4_3":
            ChangeCharacterComplexReputation(pchar,"nobility", -2);
            AddQuestRecord("CaptainComission1", "27");
            AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
            AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // 猎人
            //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// 在 СЖ 中不工作
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
            DialogExit();
        break;
        
        case "CapComission4_4":
            ChangeCharacterComplexReputation(pchar,"nobility", -2);
            AddQuestRecord("CaptainComission1", "28");
            AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
            AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // 修正 猎人
            //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); 在 СЖ 中不工作
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
            DialogExit();        
        break;
        
        case "CapComission4_5":
            dialog.text = "你可以带走这个弱者... ";
            link.l1 = "再见。 ";
            link.l1.go = "CapComission4_6";
        break;
        
        case "CapComission4_6":
            addMoneyToCharacter(pchar, -200000);
            AddQuestRecord("CaptainComission1", "29");
            AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // 修正 СЖ 中的名字 猎人
            //AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//在 СЖ 中不工作 // belamour gen : 这很好, 但需要注释掉)))
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
            pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
            DialogExit();    
            AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");    
        break;
        
        case "CapComission5":
            dialog.text = "哈哈! 干得好! 带走你的俘虏, 祝你好运。 ";
            link.l1 = "谢谢。 再见。 ";
            link.l1.go = "CapComission5_1";
        break;
        
        case "CapComission5_1":
            AddQuestRecord("CaptainComission1", "34");
            AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
            DialogExit();        
            AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");    
        break;
		
	   	/*case "CapComission6":    // eСЛИ В ПeРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩeТ
		     ИНАЧe ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРeВРАЩАeТ КВeСТ В КАШУ.. лeсник
			dialog.text = "Ты выкуп привёз"+ GetSexPhrase("","ла") +"? Вeдь я нe шутил, когда сказал, что продам eго плантаторам.";			
			link.l1 = "Слушай, "+ Npchar.name+", тут такоe дeло... В общeм, у мeня нeт таких дeнeг。 Но я готов"+ GetSexPhrase("","а") +" отработать.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "It's good that you haven't sold him。 Here are your coins - 150000 pesos。 Where can I get him?"
				link.l2.go = "CapComission2_3";
			}			
		break;*/        
        case "CapComission6":                        // 猎人。 让夏尔去找钱, 或者放弃囚犯。 
            dialog.text = "你把钱带来了吗? 我没开玩笑, 我真的会把那个人卖给种植园。 ";            
            link.l1 = "我没那么多钱, " + Npchar.name+ ", 但我正在想办法。 ";
            link.l1.go = "exit";
            if(makeint(pchar.money) > 150000)
            {
                link.l2 = "还好你没把他卖了。 这是你的钱 - 15万比索。 我在哪里可以找到他? ";
                link.l2.go = "CapComission2_3";
            }            
        break;
																																					 																																													  																																															
//--------------------------------------------劫持者------------------------------------------------------
        case "Marginpassenger":
            dialog.text = "你为什么关心我的所作所为? 要知道, 你最好还是走开... ";
            link.l1 = "嘘, 冷静点。 我是来和你谈生意的, 关于你的囚犯。 ";
            link.l1.go = "Marginpassenger_1";
        break;
        
        case "Marginpassenger_1":
            dialog.text = "啊, 好。 你想赎谁? ";
            link.l1 = "等等, 我不是来赎人的, 我是来提议你买下一个囚犯。 这样你也有机会从他身上拿到赎金。 ";
            link.l1.go = "Marginpassenger_2";
        break;
        
        case "Marginpassenger_2":
            dialog.text = "嗯。 那你为什么需要我的中介? 为什么不自己直接拿钱? ";
            link.l1 = "这对我来说太冒险了, 可能会和当局产生麻烦。 ";
            link.l1.go = "Marginpassenger_3";
        break;
        
        case "Marginpassenger_3":
            dialog.text = "哈哈... 那好吧。 我们看看, 你的囚犯是谁? ";
            link.l1 = "这是" + pchar.GenQuest.Marginpassenger.Text + ", 来自" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen") + "。 ";
            link.l1.go = "Marginpassenger_4";
        break;
        
        case "Marginpassenger_4":
            int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
            dialog.text = "我明白了... 如果你没撒谎, 这会是笔不错的交易。 我可以给你" + iTemp + "比索买下这个人, 或者给你一些有趣的情报作为交换, 你自己选。 ";
            link.l1 = "我还是拿钱吧, 这生意我受够了... ";
            link.l1.go = "Marginpassenger_money";
            link.l2 = "哈! 告诉我更多, 我肯定你会给我些有意思的东西。 ";
            link.l2.go = "Marginpassenger_offer";
        break;
        
        case "Marginpassenger_money":
            dialog.text = "那就拿钱, 拿着。 现在这不关你的事了, 把要卖的人送到这里来。 ";
            link.l1 = "他已经在城镇大门附近了。 谢谢! 你真是帮了我大忙。 ";
            link.l1.go = "Marginpassenger_money_1";
        break;
        
        case "Marginpassenger_money_1":
            iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
            dialog.text = "不客气, 再给我带更多来... 再见! ";
            link.l1 = "祝你好运... ";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, iTemp);
            sld = characterFromId("MarginPass");
            RemovePassenger(Pchar, sld);
            sld.lifeday = 0;
            AddQuestRecord("Marginpassenger", "12");
            AddQuestUserData("Marginpassenger", "sSum", iTemp);
            CloseQuestHeader("Marginpassenger");
            DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
        break;
        
        case "Marginpassenger_offer":
            pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
            pchar.GenQuest.Marginpassenger.GoodsQty = 200 + rand(10) * 10;
            switch (hrand(1))
            {
                case 0: //南缅因的海湾
                    SelectSouthshore();
                    while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
                    dialog.text = "和聪明人做生意真好。 现在听着: 几天后, 一支西班牙探险队将从缅因州抵达" + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat") + ", 船上载有贵重货物。 他们会等着一艘来接货的船。 如果你一周内赶到那里, 就有机会把货物据为己有。 \n如果我是你, 现在就已经朝我的船出发了。 把囚犯带到这里来。 ";
                    link.l1 = "谢谢! 这些货物会是对我麻烦的不错补偿。 我的乘客已经在城镇大门附近了, 会被带给你。 ";
                    link.l1.go = "Marginpassenger_offer_1";
                break;
                
                case 1: //只是艘小船
                    SelectSouthcity();
                    pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
                    dialog.text = "和聪明人做生意真好。 现在听着: 大约一周后, 一艘载有贵重货物的西班牙双桅帆船‘" + pchar.GenQuest.Marginpassenger.ShipName1 + "’将从" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen") + "驶往" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen") + "。 如果你动作快, 很容易就能追上它。 \n你还在这儿? 如果我是你, 现在就已经朝我的船出发了。 把囚犯带到这里来。 ";
                    link.l1 = "谢谢! 这些货物会是对我麻烦的不错补偿。 我的乘客已经在城镇大门附近了, 会被带给你。 ";
                    link.l1.go = "Marginpassenger_offer_2";
                break;
            }
            sld = characterFromId("MarginPass");
            RemovePassenger(Pchar, sld);
            sld.lifeday = 0;
            pchar.GenQuest.Marginpassenger = "final";
        break;
        
        case "Marginpassenger_offer_1":
            DialogExit();
            AddQuestRecord("Marginpassenger", "13");
            AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat"));//樵夫 - SЖ中的词尾 // belamour gen
            AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
            SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
            pchar.quest.Marginpassenger.win_condition.l1 = "location";
            pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
            pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
        break;
        
        case "Marginpassenger_offer_2":
            DialogExit();
            AddQuestRecord("Marginpassenger", "16");
            AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
            AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
            AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Acc")); // 樵夫 - SЖ中的词尾
            AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
            SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + rand(2), false);
        break;
        
//---------------------------------------试图翻找箱子--------------------------------------------
        case "Man_FackYou":
            dialog.text = LinkRandPhrase("抢劫!!! 这不可接受! 准备好, " + GetSexPhrase("小子", "丫头") + "... ", "嘿, 你到底在那儿干什么? ! 以为能抢我? 你完了... ", "等等, 搞什么? 把手拿开! 原来你是个贼! 到此为止吧, 混蛋... ");
            link.l1 = LinkRandPhrase("该死! ", "卡兰巴!! ", "见鬼!! ");
            link.l1.go = "PL_Q3_fight";
        break;
                    
//----------------------------------------------愤怒节点块--------------------------------------------------
        case "AngryRepeat_1":
            dialog.text = "滚出去! ";
            link.l1 = "哦... ";
            link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
                    dialog.text = "别用你那些廉价说辞烦我, 下次你不会喜欢后果的... ";
                    link.l1 = "我知道了。 ";
                    link.l1.go = NextDiag.TempNode;
                    CharacterDelAngry(npchar);
                }
            }
        break;
        
        case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("够了, 别说话。 ", "我不想再和你说话了, 你最好别烦我。 ");
            link.l1 = RandPhraseSimple("如你所愿... ", "嗯, 那好吧... ");
            link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
                    dialog.text = "我希望你能表现得更尊重些, 别再无礼了? ";
                    link.l1 = "你放心, 雅克, 我会的。 ";
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
            DoReloadCharacterToLocation("LeFransua_town", "reload", "reload6");
        break;
        
        case "pirate_town":
            dialog.text = "解决问题? 你知道自己做了什么吗? 不管怎样, 给我一百万比索, 我会说服兄弟们忘记你的‘壮举’。 如果你不喜欢这个主意, 那就滚蛋。 ";
            if (sti(Pchar.money) >= 1000000)
            {
                link.l1 = "好, 我愿意付钱。 ";
                link.l1.go = "pirate_town_pay";
            }
            link.l2 = "知道了, 我走。 ";
            link.l2.go = "pirate_town_exit";
        break;
        
        case "pirate_town_exit":
            DialogExit();
            bDisableFastReload = true; //关闭快速转移
            pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
            pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
            pchar.quest.pirate_in_town.function = "TownPirate_battle";
        break;
        
        case "pirate_town_pay":
            dialog.text = "很好! 就当你又清白了。 但我希望你别再做这种恶心事了。 ";
            link.l1 = "不会了, 这对我来说太贵了。 再见... ";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, -1000000);
            pchar.GenQuest.Piratekill = 0;
        break;
    }
}

void SelectSouthshore()
{
    switch (rand(6))
    {
        case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
        case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
        case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
        case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
        case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
        case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
        case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
    }
}

void SelectSouthcity()
{
    switch (hrand(2))
    {
        case 0: 
            pchar.GenQuest.Marginpassenger.Southcity = "马拉开波";
            pchar.GenQuest.Marginpassenger.Southcity1 = "哈瓦那"; 
        break;
        
        case 1:
            pchar.GenQuest.Marginpassenger.Southcity = "卡塔赫纳";
            pchar.GenQuest.Marginpassenger.Southcity1 = "圣地亚哥"; 
        break;
        
        case 2:
            pchar.GenQuest.Marginpassenger.Southcity = "贝洛港";
            pchar.GenQuest.Marginpassenger.Southcity1 = "圣多明戈"; 
        break;
    }
}