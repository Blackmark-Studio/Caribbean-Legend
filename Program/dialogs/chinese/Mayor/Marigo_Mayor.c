// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不了。 地点和时间不对。 "), "确实... 但以后吧, 不是现在... ",
                      "我会问的... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);              
            link.l1.go = "exit";
            // 杰森, 葡萄牙人
            if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
            {
                link.l1 = "大人, 我有绝对紧急的好消息要告诉你! 我抓住了葡萄牙人巴托洛梅奥, 那混蛋正在被看守, 等着公正审判! 而我在期待公司给点小小的谢礼... ";
                link.l1.go = "Portugal";
            }
            // 葡萄牙人
            
            // Addon-2016 杰森 FMK-圣克里斯托弗
            if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
            {
                link.l1 = "你坚持要见我, 总督先生... ";
                link.l1.go = "FMQN";
            }
            if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
            {
                link.l1 = "我来是为了英国间谍的事, 总督先生... ";
                link.l1.go = "FMQN_7";
            }
        break;

        case "Cupture_after":
            dialog.text = RandPhraseSimple("你已经拿走了所有东西。 还想要什么? ", "还有什么是你没拿的吗? ");
            link.l1 = RandPhraseSimple("只是四处看看... ", "只是检查一下, 我可能忘了拿什么... ");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
        break;
        
        // 杰森, 葡萄牙人
        case "Portugal":
            dialog.text = "巴托洛梅奥... 葡萄牙人巴特在我的镇上? ! 还活着? ! ";
            link.l1 = "是的, 大人, 他被可靠地看守着。 等我收到公司承诺的巴托洛梅奥头颅的账单后就把他交给你。 金币也行... ";
            link.l1.go = "Portugal_1";
        break;
        
        case "Portugal_1":
            dialog.text = "账单, 金币? 你疯了吗? ! 你怎么想的, 把这野兽带到我的镇上? ! 如果他在这里, 那他的护卫舰就在岛附近, 船员可能现在就在镇上! ";
            link.l1 = "我杀了和他一起的人, 其他人不知道, 但我想这不重要, 因为巴托洛梅奥... ";
            link.l1.go = "Portugal_2";
        break;
        
        case "Portugal_2":
            dialog.text = "重要! 你真不明白你做了什么吗? ! ‘信天翁号’就在岛附近, 而你抓了个连自己嗜血的手下都怕的海盗! 离开这里! 离开这个岛! 把这怪物带走! ";
            link.l1 = "但听着, 承诺的奖励和... ";
            link.l1.go = "Portugal_3";
        break;
        
        case "Portugal_3":
            dialog.text = "我不想因为你的贪婪和公司的报复而看着我的城市被烧毁! 我的堡垒里只有新兵, 他们一半人一旦知道谁和为什么攻击他们的堡垒就会逃跑! 然后屠杀就会开始... 我不想冒险, 你听到了吗? ! 滚蛋, 如果你公司那么想要他的头, 就自己把他送到库拉索去! \n趁现在还来得及赶紧做! 你可以对他做任何事, 甚至把他扔下船, 只要别在我的城市里! \n汉斯! 汉斯, 你这懒惰的白痴在哪里? ! 给我拿瓶缬草药水什么的, 看在上帝的份上, 谁把这个冒险家从我的住所扔出去! ";
            link.l1 = "但大人... ";
            link.l1.go = "Portugal_4";
        break;
        
        case "Portugal_4":
            DialogExit();
            DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
        break;
        
        // Addon-2016 杰森 FMK-圣克里斯托弗
        case "FMQN":
            DelLandQuestMark(npchar);
            dialog.text = "很好! 告诉我船长, 你在靠近我们岛的途中遇到过英国军事或贸易船只吗? ";
            link.l1 = "没有, 先生。 在你的水域内, 我既没看到英国国旗的军事船只, 也没看到贸易船只。 ";
            link.l1.go = "FMQN_1";
        break;
        
        case "FMQN_1":
            dialog.text = "我明白了。 你预计在这里待多久? ";
            link.l1 = "三天左右... ";
            link.l1.go = "FMQN_2";
        break;
        
        case "FMQN_2":
            dialog.text = "既然如此, 我给你一个提议。 根据我们的情报, 这里有英国间谍的风险。 任何关于岛上。 镇上。 附近。 海岸等地可疑船只和人员的信息, 我都将给予一万比索的奖励。 如果协助当局拘留或消灭敌人, 奖励将大幅增加。 \n欢迎每位民用船长参与调查, 突袭当地海岸和丛林寻找间谍。 \n你可能会遇到我们的军事护卫舰‘泽帕德号’, 不要害怕, 它在巡逻。 如果你发现英国人, 可以自由联系它的船长。 ";
            link.l1 = "唉, 大人, 但我来这里只有和平贸易的意图。 我一补充物资并完成这里的事务就必须离开这个岛。 ";
            link.l1.go = "FMQN_3";
            link.l2 = "很有吸引力的提议! 我想我会参与并突袭你岛的水域和海岸。 我甚至可能在这里待一段时间。 ";
            link.l2.go = "FMQN_5";
        break;
        
        case "FMQN_3":
            dialog.text = "这只是无偿提供信息, 船长。 没有压力。 你知道如果看到任何可疑情况该找谁。 ";
            link.l1 = "很好, 先生, 我知道了。 再见! ";
            link.l1.go = "FMQN_4";
        break;
        
        case "FMQN_4":
            DialogExit();
            pchar.questTemp.FMQN = "way_eng_1";
            AddQuestRecord("FMQ_Nevis", "8");
            chrDisableReloadToLocation = false;
            FMQN_SetSoldiersInCave();
        break;
        
        case "FMQN_5":
            dialog.text = "太好了, 船长! 既然你这么认真, 一定要也和我们的指挥官谈谈。 他负责抓间谍, 能给你更多信息。 ";
            link.l1 = "好的, 先生。 我这就去见他。 ";
            link.l1.go = "FMQN_6";
        break;
        
        case "FMQN_6":
            DialogExit();
            pchar.questTemp.FMQN = "way_div";
            AddQuestRecord("FMQ_Nevis", "9");
            chrDisableReloadToLocation = false;
            AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
        break;
        
        case "FMQN_7":
            DelLandQuestMark(npchar);
            dialog.text = "我们一直在等你, " +GetFullName(pchar)+ "先生。 请允许我对您消灭危险的英国袭击队的行为表示感谢。 接受这一万比索。 此外: 200船丝绸将装载到您的船舱, 还有一份非常特别的奖励 --荷兰西印度贸易公司三年许可证。 我希望您知道这是一份极其宝贵的文件? ";
            link.l1 = "当然! 三年许可证 --这肯定很重要。 ";
            link.l1.go = "FMQN_8";
        break;
        
        case "FMQN_8":
            dialog.text = "请接受你的奖励。 此外, 你可以指望所有荷兰公民和当局的感谢。 你在菲利普斯堡是个轰动人物, 我们很高兴再次见到你。 ";
            link.l1 = "听到如此温暖的话语比许可证更有价值。 谢谢你, 这是我的荣幸。 现在, 我该上路了。 再见! ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
        break;
        
        // 杰森 圣马丁岛
        case "tomas":
            dialog.text = "我们投降! 以所有神圣的名义, 我求你了, 不要掠夺和抢劫菲利普斯堡及其公民! 我准备听取你的要求! ";
            link.l1 = "不用担心市民, 先生。 法国王室的臣民不应该害怕法国士兵。 ";
            link.l1.go = "tomas_1";
        break;
        
        case "tomas_1":
            dialog.text = "法国王室? ";
            link.l1 = "正是。 这个岛属于法国, 而你们只是这里的租户。 傲慢的租户, 以为这个岛可以成为他们的财产。 从今天起, 荷兰在圣马丁岛的统治结束了。 清楚了吗? ";
            link.l1.go = "tomas_2";
        break;
        
        case "tomas_2":
            dialog.text = "但... 但是我们会怎么样, 向你投降的荷兰士兵, 还有伤员? 还有什么... ";
            link.l1 = "这完全取决于你, 托马斯先生。 如果你帮我个忙, 那么我会允许所有投降的人带上伤员, 乘坐我们在码头找到的一艘或多艘船, 前往库拉索, 去找施托伊弗桑特先生。 ";
            link.l1.go = "tomas_2_1";
        break;
        
        case "tomas_2_1":
            dialog.text = "";
            link.l1 = "否则你将被关在我的船舱和圣基茨的炮台里。 此外, 一些重要的荷兰官员将不得不被绞死, 只是为了确保施托伊弗桑特会失去征服我们殖民地的兴趣... ";
            link.l1.go = "tomas_3";
        break;
        
        case "tomas_3":
            dialog.text = "(结结巴巴地) 什... 什么... 关... 关于什... 什么 kind of 帮... 帮忙? ";
            link.l1 = "在岛的深处有一个争端焦点 --一个盐矿。 我知道那里不仅有矿工和奴隶, 还有荷兰士兵, 全副武装。 他们一定是公司卫队的, 对吧, 先生? 我会让他们投降, 否则我会在他们拒绝时使用武力。 我需要一个向导, 带我去矿场。 给我找这样一个向导。 ";
            link.l1.go = "tomas_4";
        break;
        
        case "tomas_4":
            dialog.text = "盐... 盐矿? ";
            link.l1 = "正是。 别害怕, 托马斯先生, 如果矿场的守卫足够明智地放下武器, 我会给他们离开岛屿的机会。 我不需要不必要的流血。 别担心, 你的良心会是清白的: 即使你不告诉我矿在哪里, 圣马丁岛也足够小, 我可以在没有你帮助的情况下找到矿, 我只是不想浪费时间在灌木丛和沼泽中闲逛。 所以这个交易对你来说比我更有利。 ";
            link.l1.go = "tomas_5";
        break;
        
        case "tomas_5":
            dialog.text = "好... 好的, 我会告诉你怎么去矿场, 但你必须答... 答... 应我, 所有... 我们所有人都要离开这个岛! ";
            link.l1 = "我以军官和贵族的身份向你保证。 ";
            link.l1.go = "tomas_6";
        break;
        
        case "tomas_6":
            dialog.text = "在大凯斯湾... 在它的最边缘, 靠近水的地方, 有... 有石头。 在那里... 在它们后面, 沿着海岸线, 有一条沿着水边的通道, 那里... 那里水很浅, 齐腰或更浅。 你需要绕过岩石, 就会到达一个大沙滩, 那里... 因为周围有珊瑚礁, 你的船无法靠岸。 从这个沙滩有一条小路直接... 到... 到矿场。 ";
            link.l1 = "太好了。 我这就出发。 而你, 先生, 将留在这里, 在我的士兵的严密看守下, 直到我回来。 ";
            link.l1.go = "tomas_7";
        break;
        
        case "tomas_7":
            DialogExit();
            SetReturn_Gover_Dialog_Exit(NPChar);
            LAi_SetActorType(npchar);
            pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
            pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
            pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
            AfterTownBattle();
            AddQuestRecord("Patria", "50_1");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}