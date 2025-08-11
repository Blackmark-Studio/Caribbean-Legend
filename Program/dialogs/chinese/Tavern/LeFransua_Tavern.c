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
            //Jason, 加斯科涅人的负担
            if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
            {
                link.l1 = "听着, " + npchar.name+ ", 我来找你是为了一件不寻常的事。 我需要找一个人, 他愿意在圣皮埃尔的一家商店里担任商人的助手, 在海湾过上平静的生活。 薪水不错, 还包吃住。 你能给我推荐个人吗? ";
                link.l1.go = "storehelper";
            }
            if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
            {
                link.l1 = "我是为了你要装到我船上运往瓜德罗普岛的葡萄酒桶而来的... ";
                link.l1.go = "seabattle";
            }
            //加斯科涅人的负担
            //Jason, 葡萄牙人
            if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
            {
                link.l1 = "你知道吗, " + npchar.name+ ", 我在找我的一个朋友。 他应该已经到这里了, 而且他身体不舒服。 也许他的朋友帮了他... ";
                link.l1.go = "Portugal";
            }
            //葡萄牙人
        break;
        
        case "storehelper":
            dialog.text = "嗯... 我们这里有几个人想从水手转行过陆地生活。 我可以帮你, 但我现在就告诉你: 这不是免费的。 ";
            link.l1 = "嘿! 你想要多少? ";
            link.l1.go = "storehelper_1";
        break;
        
        case "storehelper_1":
            dialog.text = "一千枚八里亚尔银币。 你什么都不用做, 一个小时后, 你要找的候选人就会在我的酒馆里, 有好几个。 你可以和他们交谈, 选择你最喜欢的那个。 ";
            if (sti(Pchar.money) >= 1000)
            {
                link.l1 = "啊... 好吧, 给你, 拿一千! ";
                link.l1.go = "storehelper_2";
            }
            link.l2 = "对不起, 我没那么多钱! ";
            link.l2.go = "storehelper_exit";
        break;
        
        case "storehelper_2":
            AddMoneyToCharacter(pchar, -1000);
            dialog.text = "别担心, 伙计。 你会从候选人那里拿回一半的钱。 我会告诉他那是你的服务费, 呵呵... 他们不会给超过五百的。 一个小时后到我的酒馆来, 到时候我会把你需要的人都找来等你。 ";
            link.l1 = "好的。 我一个小时后回来, " + npchar.name+ "。 ";
            link.l1.go = "storehelper_3";
            npchar.quest.storehelper = "true";
            DelLandQuestMark(npchar);
        break;
        
        case "storehelper_3":
            DialogExit();
            SetLaunchFrameFormParam("一小时过去了... ", "", 0, 5);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, 1, 0); // 流逝时间
            RecalculateJumpTable();
            Storehelper_hire("");
        break;
        
        case "storehelper_exit":
            dialog.text = "很抱歉你也没有那么多钱。 但你自己也知道, 这种事情可不是一句‘谢谢’就能办成的。 所以... ";
            link.l1 = "我明白。 但我真的没有钱。 好吧, 再见... ";
            link.l1.go = "exit";
            //pchar.quest.storehelper.over = "yes";
            //AddTimeToCurrent(2,0);
            //DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
            //CloseQuestHeader("SharlieA");
        break;
        
        case "seabattle":
            DelLandQuestMark(npchar);
            dialog.text = "你在说什么, 伙计? 你说的是什么葡萄酒? ";
            link.l1 = "一个叫沃尔特.卡彻的人派我来的。 他说你需要一艘船把一批葡萄酒货物运到瓜德罗普岛, 报酬是一万比索。 而且你特别需要我的船来做这件事... ";
            link.l1.go = "seabattle_1";
            npchar.quest.seabattle = "true";
        break;
        
        case "seabattle_1":
            dialog.text = "听着, 伙计, 我不做葡萄酒生意, 不需要你的服务, 也不认识什么沃尔特.卡彻。 ";
            link.l1 = "真没想到! 那么, 那个卡彻根本不是你派来的... 那么, 这整出戏是怎么回事? ";
            link.l1.go = "seabattle_2";
        break;
        
        case "seabattle_2":
            dialog.text = "嘿! 嗯, 这要么是个误会, 要么是个恶意玩笑, 要么... ";
            link.l1 = "要么是什么? ";
            link.l1.go = "seabattle_3";
        break;
        
        case "seabattle_3":
            dialog.text = "你自己还不明白吗? 有人需要把你引诱到勒弗朗索瓦来, 我不知道是为了什么。 换作是我, 我会尽快小心地离开这里。 这闻起来就像肮脏的勾当, 伙计... ";
            link.l1 = "我想你是对的。 我不喜欢那个卡彻的样子。 好吧, 我会听从你的建议。 再见, 塞萨尔! ";
            link.l1.go = "seabattle_4";
        break;
        
        case "seabattle_4":
            DialogExit();
            AddQuestRecord("Sharlie", "16");
            pchar.quest.seabattle.win_condition.l1 = "location";
            pchar.quest.seabattle.win_condition.l1.location = "Martinique";
            pchar.quest.seabattle.function = "SharlieSeabattle_ship";
            
            pchar.quest.NewGameTip4.win_condition.l1 = "location";
            pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
            pchar.quest.NewGameTip4.function = "ShowNewGameTip";
            pchar.quest.NewGameTip4.text = "你的第一场海战即将来临! 保存游戏! ";                      
        break;
        
        case "Portugal":
            dialog.text = "是的, 你的朋友已经到了, 船长。 他昨天到的, 在楼上租了个房间。 他的同伴也在这里, 呵呵... 他们坐在那边。 去问他们! ";
            link.l1 = "... ";
            link.l1.go = "Portugal_1";
        break;
        
        case "Portugal_1":
            DialogExit();
            AddDialogExitQuestFunction("Portugal_enterPirates");
            npchar.quest.portugal = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}