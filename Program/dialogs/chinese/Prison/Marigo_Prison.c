// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
            // 巴尔巴宗的诱惑
            if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "你们在这里逮捕了西蒙.莫雷勒。 他是个走私犯, 他的纵帆船不久前被巡逻队击沉了。 我能见见他吗? ";
                link.l1.go = "BarbTemptation";
                DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
            // Addon-2016 Jason FMK-圣克里斯托弗
            if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
            {
                link.l1 = "军官, 我是被菲利普斯堡的总督阁下派来的。 他让我突袭这个岛屿及其海域, 搜寻英国间谍。 阁下还说你能给我提供有用的信息。 ";
                link.l1.go = "FMQN";
            }
            if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
            {
                link.l1 = "军官, 我找到了失踪的巡逻队, 还发现了英国间谍, 他们就在这个岛上。 ";
                link.l1.go = "FMQN_3";
            }
            if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
            {
                link.l1 = "又是我, 军官。 你们拘留那些间谍了吗? ";
                link.l1.go = "FMQN_8";
            }
        break;
        
        // 巴尔巴宗的诱惑
        case "BarbTemptation":
            dialog.text = "先生, 你为什么需要见他? ";
            link.l1 = "我想告诉他, 他是个该死的混蛋和无赖。 希望这能帮他站到绞刑架上。 ";
            link.l1.go = "BarbTemptation_1";
        break;
        
        case "BarbTemptation_1":
            dialog.text = "哈哈! 先生, 你真幽默... 好吧, 两千比索, 你就可以过去了。 ";
            if(sti(Pchar.money) >= 2000)
            {
                link.l1 = "拿着, 军官。 谢谢! ";
                link.l1.go = "BarbTemptation_2";
            }
            link.l2 = "嗯... 你知道吗, 我改变主意了。 我最好把钱浪费在酒馆里。 ";
            link.l2.go = "BarbTemptation_4";
        break;
        
        case "BarbTemptation_2":
            AddMoneyToCharacter(pchar, -2000);
            dialog.text = "不客气... 过去吧! ";
            link.l1 = "... ";
            link.l1.go = "exit";
            pchar.questTemp.jailCanMove = true;
        break;
        
        case "BarbTemptation_4":
            dialog.text = "如你所愿, 下次不会再有这样的提议了。 ";
            link.l1 = "反正我也不需要。 再见, 军官! ";
            link.l1.go = "exit";
        break;
        
        // Addon-2016 Jason FMK-圣克里斯托弗
        case "FMQN":
            DelLandQuestMark(npchar);
            dialog.text = "有用的信息? 哈! 转念一想, 等等, 我确实有有用的事要告诉你。 我们的一支巡逻队在丛林中失踪了。 他们本该现在回到营房的, 但看来他们更喜欢和鹦鹉作伴, 或者真的发生了什么事。 如果你在搜查时找到他们, 请告诉他们编一个像样的理由解释延误, 否则后果自负... 巡逻队的指挥官叫扬内斯.霍夫曼。 ";
            link.l1 = "就这些吗, 军官? ";
            link.l1.go = "FMQN_1";
        break;
        
        case "FMQN_1":
            dialog.text = "是的, 该死的。 抱歉, 我没有别的要告诉你了。 祝你好运, 船长。 ";
            link.l1 = "谢谢你... ";
            link.l1.go = "FMQN_2";
        break;
        
        case "FMQN_2":
            DialogExit();
            pchar.questTemp.FMQN = "way_div_1";
            AddQuestRecord("FMQ_Nevis", "10");
            FMQN_SetSoldiersInCave();
        break;
        
        case "FMQN_3":
            DelLandQuestMark(npchar);
            dialog.text = "什么? ! 希望你不是在开玩笑? 给我一份报告! ";
            link.l1 = "我在丛林里的一个洞穴附近遇到了一支巡逻队。 他们拦住我, 问我要去哪里。 为什么去, 然后放我走了。 该死的, 如果那些不是穿着荷兰制服的英国人就怪了! 我还在丛林里看到了一些奇怪的东西, 看起来就像一群 naked 男人藏在灌木丛里。 我猜英国突击队解除了你巡逻队的武装, 拿走了他们的制服。 ";
            link.l1.go = "FMQN_4";
        break;
        
        case "FMQN_4":
            dialog.text = "... ";
            link.l1 = "如你所知, 我没有冒险与一队训练有素的红衣士兵战斗, 所以我赶紧来向你报告。 ";
            link.l1.go = "FMQN_5";
        break;
        
        case "FMQN_5":
            dialog.text = "嗯嗯... 你说的洞穴? 你数了有多少人? ";
            link.l1 = "五个人。 是的, 我想他们进了那个洞穴。 ";
            link.l1.go = "FMQN_6";
        break;
        
        case "FMQN_6":
            dialog.text = "我马上派一队人去洞穴! 船长, 如果那些你遇到的人真的是英国间谍, 你会得到应得的奖励。 如果你想协助当局拘留那些混蛋并获得额外奖励, 你可以加入队伍, 毕竟这是总督的命令。 那么, 你要一起去吗? ";
            link.l1 = "不, 军官, 追捕间谍是你的工作。 确保你派全副武装的队伍, 这些混蛋太危险了... ";
            link.l1.go = "FMQN_7";
            link.l2 = "我想我可以帮忙。 有我的帮助, 你的人会更快找到间谍。 ";
            link.l2.go = "FMQN_10";
        break;
        
        case "FMQN_7":
            dialog.text = "这是你的选择, 船长, 我会考虑你的建议。 明天来找我, 听听我们行动的结果。 ";
            link.l1 = "明天见。 ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("FMQN_HollandPeace");
        break;
        
        case "FMQN_8":
            DelLandQuestMark(npchar);
            dialog.text = "你的信息是正确的, 船长。 我们在洞穴里找到了那些混蛋。 他们毫无投降之意, 还发起了战斗。 结果是我们消灭了所有敌人... 我们也找到了失踪的巡逻队。 他们没事, 还活着, 不过有点被打惨了... 谢谢你, 船长, 我代表菲利普斯堡所有善良的市民感谢你。 你的警惕性将按承诺得到奖励。 请收下这个。 ";
            link.l1 = "谢谢你! ";
            link.l1.go = "FMQN_9";
        break;
        
        case "FMQN_9":
            AddMoneyToCharacter(pchar, 10000);
            dialog.text = "在圣马丁岛, 你永远是受欢迎的客人。 现在, 请原谅, 我还有其他事情要处理。 ";
            link.l1 = "我也是。 再见。 ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
        break;
        
        case "FMQN_10":
            dialog.text = "很好。 非常感谢你的帮助。 去城门口吧, 惩罚小队一小时后在那里集合。 ";
            link.l1 = "一个小建议, 你应该派你手下最优秀的士兵执行这次任务, 那些间谍很危险。 ";
            link.l1.go = "FMQN_11";
        break;
        
        case "FMQN_11":
            dialog.text = "别担心。 我会派我们最有经验的士兵, 由军官汉斯.舒尔特指挥 --他是菲利普斯堡的剑术大师。 ";
            link.l1 = "太好了! 那我们别浪费时间了。 ";
            link.l1.go = "exit";
            WaitDate("",0,0,0,1,5);
            AddDialogExitQuestFunction("FMQN_HollandBattle");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}