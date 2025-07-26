// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "你不久前刚问过我问题, " + GetAddress_Form(NPChar) + "... ", "一整天下来, 这已经是你第三次问这类问题了... ",
                          "我猜你又有问题要问? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么想聊的。 "), "嗯, 我的记性哪去了... ",
                      "是的, 确实是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "一个叫弗朗索瓦.贡捷的人来过你们镇上吗? 我真的很需要找到他。 ";
                link.l1.go = "Jamaica_ratF_1";
            }
            // 2016-1扩展包 Jason海盗线
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "听着, 伙计, 皇家港有一艘船正在为他的造船厂购买一些丝绸... 非常特别的丝绸, 你肯定听说过。 据说这种丝绸的卖家住在这个定居点的某个地方。 你有什么线索能帮我找到他吗? 我有个商业提议要和他谈谈。 ";
                link.l1.go = "mtraxx";
            }
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "我带了五十枚杜布隆金币。 拿了钱就开始说吧。 ";
                link.l1.go = "mtraxx_4_1";
            }
        break;

        case "Jamaica_ratF_1":
            dialog.text = "他来过。 他租了几天房间。 我跟你说, 他可不是个最讨人喜欢的家伙。 此外, 他一直偏执地担心被人追捕。 他总是很害怕, 四处张望。 你就是他那么害怕的人吗? ";
            link.l1 = "不, 不是我。 你知道, 私掠船船长树敌很多。 那么, 我在哪里能找到他? 我和他本打算达成一项协议, 但现在他好像人间蒸发了。 ";
            link.l1.go = "Jamaica_ratF_2";
        break;
        
        case "Jamaica_ratF_2":
            dialog.text = "他已经乘自己的船出海了。 我不知道他去了哪里。 他没告诉我。 ";
            link.l1 = "啊, 太遗憾了! 我现在去哪里找他呢? ";
            link.l1.go = "Jamaica_ratF_3";
        break;
        
        case "Jamaica_ratF_3":
            dialog.text = "我不知道, 伙计。 如果我知道, 我会告诉你的。 ";
            link.l1 = "好吧, 我明白了。 我去问问别人... ";
            link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "21_4");
            pchar.questTemp.Slavetrader = "FindRatJamaica_H";
        break;
        
        // 2016-1扩展包 Jason海盗线
        case "mtraxx":
            dialog.text = "哼, 如果你怀疑我们的商人, 那个开商店的, 我可以告诉你不是他, 他不做丝绸船帆生意。 走私者也不来这里, 没有海关, 他们没必要来。 再说了, 除了我们的商人, 这里也没有其他人做生意。 你四处看看, 我们可不是那种人, 哈哈! ";
            link.l1 = "但有人在给皇家港供应丝绸 --这是无可辩驳的。 你有什么线索能知道谁可能是供应商吗? ";
            link.l1.go = "mtraxx_1";
        break;
        
        case "mtraxx_1":
            dialog.text = "也许是来自皇家港的走私者? 或者是 rogue 海盗? 他们肯定在某个隐蔽的海湾卸货... 哈! 我有个主意, 伙计。 有一个当地人, 他知道这片海域发生的所有事情。 如果他都没有什么推测, 那就没有丝绸商人了。 ";
            link.l1 = "太好了! 那个人叫什么名字? ";
            link.l1.go = "mtraxx_2";
        break;
        
        case "mtraxx_2":
            dialog.text = "嗯... 我想回忆他的名字, 但不知为什么就是想不起来... ";
            link.l1 = "几枚硬币能帮助你回忆起来吗? ";
            link.l1.go = "mtraxx_3";
        break;
        
        case "mtraxx_3":
            dialog.text = "我想可能会有帮助... 五十枚金杜布隆肯定能照亮这个老脑袋。 ";
            if (PCharDublonsTotal() >= 50) // Rebbebion, 计算从货舱中取出的杜布隆数量
            {
                link.l1 = "我明白了。 给你, 拿去吧。 ";
                link.l1.go = "mtraxx_4_1";
            }
            else
            {
                link.l1 = "我明白了。 我会回来的... ";
                link.l1.go = "mtraxx_4_2";
            }
        break;
        
        case "mtraxx_4_1":
            RemoveDublonsFromPCharTotal(50);
            PlaySound("interface\important_item.wav");
            dialog.text = "你要找的人是沙哑的比利。 他在牙买加住了一辈子, 认识街上的每一条狗。 他曾经是个海盗, 让英国人头疼不已, 直到三年前受伤。 现在他主要在牙买加的海湾捕鱼。 猎鲨和收集琥珀。 他只有去买更多的朗姆酒和饼干时才会离开他的旧长船。 你应该在牙买加周围的水域寻找他。 据说他在北侧航行, 一直到最东端。 但追赶一艘长船是傻瓜才会做的事, 你最好在西南角附近守候, 据说他每周会在尼格瑞尔角附近出现一次。 他的小船叫‘飞鱼号’。 ";
            link.l1 = "谢谢, 伙计。 你这钱赚得值。 ";
            link.l1.go = "mtraxx_5";
        break;
        
        case "mtraxx_5":
            dialog.text = "祝你好运, 伙计! 我希望你能找到你要找的东西! ";
            link.l1 = "... ";
            link.l1.go = "mtraxx_6";
        break;
        
        case "mtraxx_4_2":
            DialogExit();
            AddQuestRecord("Roger_2", "6");
            pchar.questTemp.Mtraxx = "silk_5";
        break;
        
        case "mtraxx_6":
            DialogExit();
            AddQuestRecord("Roger_2", "7");
            pchar.questTemp.Mtraxx = "silk_6";
            /*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
            pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
            pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
            pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
            pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
            PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
            PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
            pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
            SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
            if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请在截止日期前完成! ");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}