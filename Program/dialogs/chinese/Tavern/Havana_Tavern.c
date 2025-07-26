// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为你效劳。 你想了解什么? ",
                          "我们刚刚还在谈这个。 你一定是忘了... ", "今天这已经是你第三次问这类问题了... ",
                          "你像鹦鹉一样重复... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 也许下次吧。 ", "对, 不知为何我忘了... ",
                      "是的, 确实是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "弗朗索瓦.贡捷有没有可能刚好路过你们镇? 他有一艘名为‘" + pchar.questTemp.Slavetrader.ShipName + "’的护卫舰, 以防万一... ";
                link.l1.go = "Havana_ratT_1";
            }
            if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "告诉我, 伙计, 我在哪里可以找到唐.迭戈.德.蒙托亚? 我来晚了吗? 他已经出发去大陆了吗? ";
                link.l1.go = "guardoftruth";
            }
            // 卡勒幽船
            if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
            {
                link.l1 = "听着, 有没有一个叫约阿希姆.梅里曼的人来过这里? 一个中年医生, 葡萄牙人, 留着小胡子。 帝王须和锐利的眼睛? 也许他想租个房间? ";
                link.l1.go = "caleuche";
            }
        break;

        case "Havana_ratT_1":
            dialog.text = "啊哈, 那个阴沉的家伙? 是的, 他来过我这里。 我告诉你: 他和俄勒冈-哈斯科恩有个约会。 他申请获得专利, 但没成功, 然后就离开了。 ";
            Link.l1 = "你知道他航去哪里了吗? 我从贝略港就开始追他, 一直找不到他。 ";
            Link.l1.go = "Havana_ratT_2";
        break;
        
        case "Havana_ratT_2":
            dialog.text = "你找他干什么? 他怕外人, 总是躲着所有人, 一看到带武器的陌生人就会拔剑。 他走路总是被四个卫兵围着。 你会不会就是他防备的那个人? ";
            Link.l1 = "天哪, 人们总是这么说! 什么, 我看起来像个杀手吗? 他是我的老伙计, 我急着给他捎个消息, 他会很高兴知道再也不用躲了, 没人在找他。 ";
            Link.l1.go = "Havana_ratT_3";
        break;
        
        case "Havana_ratT_3":
            dialog.text = "不用躲了? 哈哈哈! 就在他离开哈瓦那的前一天, 一群流氓在丛林里试图杀他... 当然, 他有自己的人, 他们立刻把那些人打成了肉泥。 而你现在却说... ";
            Link.l1 = "哦, 得了吧。 可能只是一些当地土匪想抢他的钱包。 你自己也知道丛林里有多少无赖。 那他去哪儿了? ";
            Link.l1.go = "Havana_ratT_4";
        break;
        
        case "Havana_ratT_4":
            dialog.text = "嗯, 在他被从住所远远打发走后, 他一直唠叨着要向法国人自首, 向他的同胞自首。 他出发去托尔图加岛, 找某个德奥热龙... 他还嘀咕了一些关于他情人的事, 但我没太听懂。 ";
            Link.l1 = "所以, 托尔图加岛? 太好了! 希望我能在那里抓住他。 谢谢你, " + npchar.name+ ", 你帮了大忙。 再见。 ";
            Link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "21_7");
            pchar.questTemp.Slavetrader = "FindRatTortuga";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
        break;

        case "guardoftruth":
            dialog.text = "嗯... 一个法国人为什么会对唐.迭戈感兴趣, 嗯? ";
            link.l1 = "我是法国人这个事实无关紧要。 重要的是这份由宗教审判官签署的文件。 看看... 现在明白了吗? 我有紧急消息要给迭戈。 ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            dialog.text = "啊哈, 所以你为尊敬的文森特神父工作? 这就不一样了。 唐.迭戈.德.蒙托亚两天前带着他的中队离开了, 但很快就乘他的信使帆船回来了。 他的一艘船在古巴南部的礁石上沉没了, 所以他今天一直在购买修理材料。 去南边的海湾看看, 你会在那里找到那艘船和他本人。 我怀疑他们已经设法把洞补好了。 ";
            link.l1 = "谢谢, 伙计! 你帮了大忙! ";
            link.l1.go = "guardoftruth_2";
        break;
        
        case "guardoftruth_2":
            dialog.text = "不客气, 随时效劳。 我总是很高兴帮助耶稣会的兄弟。 ";
            link.l1 = "是的, 愿平安与你同在之类的。 ";
            link.l1.go = "guardoftruth_3";
        break;
        
        case "guardoftruth_3":
            DialogExit();
            DeleteAttribute(npchar, "quest.batabano");
            AddQuestRecord("Guardoftruth", "47");
            pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
            pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
            pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
        break;
        
        // 卡勒幽船
        case "caleuche":
            dialog.text = "天知道, 伙计。 他可能来过, 但我不知道。 抱歉。 ";
            link.l1 = "明白了。 真遗憾。 我会继续寻找... ";
            link.l1.go = "exit";
            npchar.quest.caleuche = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}