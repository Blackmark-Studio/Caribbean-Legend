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
            // 肺结核的代价
            if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
            {
                link.l1 = "我听说你们堡垒里肺结核肆虐。 你觉得这种流行病会蔓延到镇上吗? ";
                link.l1.go = "Consumption";
            }
            if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
            {
                link.l1 = "你对堡垒的司令官有什么看法? ";
                link.l1.go = "Consumption_8";
            }
            if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
            {
                link.l1 = "告诉我, ‘胡安’这个名字对你有什么意义吗? ";
                link.l1.go = "Consumption_12";
            }
            if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
            {
                link.l1 = "听着, 1654年4月, 一艘由米格尔.迪乔索船长指挥的护卫舰停靠在你们港口, 之后他就失踪了。 你能告诉我些什么吗? ";
                link.l1.go = "guardoftruth";
            }
        break;
        
        //--> 肺结核的代价
        case "Consumption":
            dialog.text = "司令官说没有危险。 那些太好奇的人最后都被锁在地牢里了。 抱歉, 我不是那种人。 ";
            link.l1 = "是这样吗? 一个酒馆老板竟然不想听谣言 —这可真新鲜! 也许 pesos 的叮当声能让你重新产生好奇心? ";
            link.l1.go = "Consumption_1";
        break;
        
        case "Consumption_1":
            dialog.text = "银钱当然很诱人, 但我自己的小命更值钱。 也许我可以告诉你其他事情, 先生? 实际上我总是很乐意聊天, 开始聊吧! ";
            link.l1 = "事情就是这样展开的... 好吧, 这个钱包里有三千八里亚尔, 我们就聊聊天气, 成交? ";
            link.l1.go = "Consumption_2";
        break;
        
        case "Consumption_2":
            AddMoneyToCharacter(pchar, -3000);
            dialog.text = "哦, 你真执着, 先生。 只是记住, 这次谈话从未发生过。 (低语) 整整一年, 我已经听过好几次了, 说我们的监狱里有人因肺结核而逐渐衰弱死去。 你可以责怪当局, 责怪上帝, 或者魔鬼, 但大部分都归因于厄运。 这种该死的疾病夺走生命的速度太快了。 有时他们把一个完全健康的人关进去, 一两周后他就没了。 就这样... ";
            link.l1 = "哇... 你说整整一年? 那什么, 没人愿意承担责任做点什么吗? ";
            link.l1.go = "Consumption_3";
        break;
        
        case "Consumption_3":
            dialog.text = "谁在乎呢, 先生? 谁在乎囚犯? 社会的败类 —那些穿丝绸的大人物是这么说的。 曾经有一位医生在地牢里工作, 试图治愈那些可怜的灵魂。 但他没坚持多久, 似乎也被疾病除掉了。 现在司令官不让人进去, 我们的当局也不关注这类事情, 尤其是当他们可以少付监狱口粮的时候。 ";
            link.l1 = "有意思, 但这种疾病到底有什么可怕的, 让我们被锁在坚固的围墙里, 像忏悔室里的修女一样低语? ";
            link.l1.go = "Consumption_4";
        break;
        
        case "Consumption_4":
            dialog.text = "我很难告诉你, 但这里有过一个家伙。 他因走私被抓, 关了大约半年, 直到他的伙伴把他赎出来。 嗯, 你知道的 —他们给需要的人量金子, 按要求等了那么久, 那家伙就出来了。 但从那以后他就疯了。 ";
            link.l1 = "比舱底的老鼠还疯? ";
            link.l1.go = "Consumption_5";
        break;
        
        case "Consumption_5":
            dialog.text = "我想是的。 从那以后他对他的伙伴就没用了, 整天在这里喝酒等死。 看起来他想从脑子里抹去什么东西。 每次喝醉, 他都会讲关于悄无声息夺走人们生命的肺结核的故事。 这是他的原话。 据他说, ‘肺结核’是一个人可能遇到的最糟糕的事情。 ";
            link.l1 = "一个醉汉的胡言乱语。 那又怎样? ";
            link.l1.go = "Consumption_6";
        break;
        
        case "Consumption_6":
            if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
            {
                dialog.text = "没什么, 除了他找到了一些酒后之勇, 开始说越来越多的话, 然后就有人割开他的喉咙, 把他扔到排水沟里... 是谁干的, 为什么, 对我来说都一样。 ";
                link.l1 = "你对司令官有什么看法? ";
                link.l1.go = "Consumption_8";
            }
            else
            {
                dialog.text = "没什么, 除了他变得勇敢, 开始说越来越多的话, 然后就有人割开他的喉咙, 把他扔到排水沟里... 是谁干的, 为什么, 对我来说都一样。 (提高声音) 是的, 这里的海湾和礁石真的很危险, 先生。 当风暴从大安的列斯群岛袭来时, 你必须小心, 错过风向, 你就完了! 祝你休息愉快, 先生, 谢谢你的光临! ";
                link.l1 = "风暴... 对。 也谢谢你。 ";
                link.l1.go = "Consumption_7";
            }
            pchar.questTemp.Consumption.Contra = "true";
        break;
        
        case "Consumption_7":
            DialogExit();
            npchar.quest.Consumption = "true";
            AddQuestRecord("Consumption", "2");
        break;
        
        case "Consumption_8":
            dialog.text = "关于他有什么好说的? 他是一名上校, 几年前从欧洲来到这里, 接管了这个地方。 据说他在旧世界因为做了一些肮脏的事而被降级。 我不知道是不是真的, 但一开始有传言。 但谁没有关于他们的传言呢, 对吧? ";
            link.l1 = "你说肮脏的事... 那很有趣。 还有别的吗? ";
            link.l1.go = "Consumption_9";
        break;
        
        case "Consumption_9":
            dialog.text = "嗯, 我能说什么... 上校看起来是一个非常关心自己安全的人。 当然, 由于海盗。 土匪。 印第安人和其他败类, 这些地方并不安全, 但司令官先生出门从不离开几个保镖。 他在这个城市有一座豪宅, 他把它变成了一个小堡垒 —他的仆人装备精良, 窗户都上了闩。 ";
            link.l1 = "但白天他在监狱里服役, 不是吗? ";
            link.l1.go = "Consumption_10";
        break;
        
        case "Consumption_10":
            dialog.text = "是的, 但那座豪宅基本上是在等待伏击或入侵。 不管怎样, 司令官先生显然不常回那里, 真正的堡垒更像是他的堡垒, 呵呵。 ";
            link.l1 = "谢谢你, 你帮了大忙。 回头见, " + npchar.name+ "! ";
            link.l1.go = "Consumption_11";
        break;
        
        case "Consumption_11":
            DialogExit();
            if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
            else AddQuestRecord("Consumption", "5");
            DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
            pchar.questTemp.Consumption = "current";
        break;
        
        case "Consumption_12":
            dialog.text = "胡安? 哪一个? 这里有很多胡安, 人们通常也有姓氏... 或者至少有一个绰号... ";
            link.l1 = "我只是在想... 也许他的绰号是‘肺结核’, 听说过吗? ";
            link.l1.go = "Consumption_13";
        break;
        
        case "Consumption_13":
            dialog.text = "哦, 我的上帝, 你又在说那个! 不, 谢天谢地, 我没听说过。 我发誓! 现在让我们换个话题。 求你了! ";
            link.l1 = "好吧, 好吧, 别心脏病发作... ";
            link.l1.go = "exit";
            pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan) + 1;
            if (sti(pchar.questTemp.Consumption.AskJuan) == 3)
            {
                pchar.quest.Consumption2.win_condition.l1 = "location";
                pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
                pchar.quest.Consumption2.function = "Consumption_CreateSergio";
            }
            npchar.quest.Consumption_1 = "true";
        break;
        //< —肺结核的代价
        
        case "guardoftruth":
            dialog.text = "我记得他。 经常来我的酒馆, 但不多说话。 喝几杯朗姆酒, 和一些顾客低语几句就走了。 像那艘护卫舰上的每个人一样, 非常阴郁和严肃。 看起来很危险的雇佣兵, 随时准备好刀刃。 有传言说那艘护卫舰装满了宝藏, 但我不相信这样的故事。 贵重货物从来不会在没有护航的情况下用单艘船运输。 他们在这里待了一天, 然后离开了。 我听说去了欧洲。 这就是我所知道的。 ";
            link.l1 = "我明白了。 嗯, 至少有了一些线索... ";
            link.l1.go = "exit";
            npchar.quest.guardoftruth = "true";
            AddQuestRecord("Guardoftruth", "40");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}