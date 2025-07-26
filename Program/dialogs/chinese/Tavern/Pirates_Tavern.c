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
            if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
            {
                link.l1 = "听着, " + npchar.name+ ", 你有没有听说过一个叫米格尔.迪乔索的人? 据说, 有人在宝藏岛水域见过他的船... ";
                link.l1.go = "guardoftruth";
            }
            if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
            {
                link.l1 = "听着, " + npchar.name+ ", 你最近在宝藏岛见过米格尔.迪乔索吗? ";
                link.l1.go = "tieyasal";
            }
        break;
        
        case "guardoftruth":
            dialog.text = "是的, 我见过。 那个西班牙老爷在还住在这里的时候, 把一艘非凡的船卖给了沙克.多德森, 那是一艘护卫舰。 啊, 那艘船... 她真是令人难以置信... ";
            link.l1 = "让我猜猜: 她有现代流畅的船身, 能达到16节航速? 她的名字是‘圣基塔里亚号’? ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            dialog.text = "至于船身和速度, 你完全正确, 但她的名字不同: ‘圣马丁号’。 沙克为了那艘船给了那个无赖一大笔金子。 ";
            link.l1 = "你确定是‘圣马丁号’而不是‘圣基塔里亚号’吗? 他什么时候买的? 你为什么叫迪乔索无赖? ";
            link.l1.go = "guardoftruth_2";
        break;
        
        case "guardoftruth_2":
            dialog.text = "该死, 我绝对确定是‘圣马丁号’, 因为我亲眼看见亚历克苏斯的工人从船尾拆下一块刻有天主教胡话的牌子。 沙克.多德森给她取名‘幸运号’, 对这样的美人来说更合适。 (吐口水) 他是在54年冬天买的, 就在Blaze被谋杀前不久。 我为什么叫米格尔老爷无赖? 因为他从普罗维登斯的西班牙海军那里偷了那艘该死的船! 多德森像他喝醉时总跟我说的那样, 给圣胡安堡垒和驻军上演了一场烟火表演。 沙克牺牲了两艘受损的小帆船, 让与护卫舰的战斗看起来像真的。 夜幕降临时, 他秘密将‘圣马丁号’驶往宝藏岛。 沙克得到了船, 迪乔索得到了钱。 那个狡猾的混蛋后来告诉他的上级, 护卫舰在与海盗舰队的战斗中沉没了, 圣胡安堡垒的指挥官也证实了这一点。 ";
            link.l1 = "哦, 那些西班牙老爷们真是中饱私囊! 多狡猾啊! 告诉我, 你确定那是1654年冬天发生的吗? 会不会是春天? 那艘护卫舰有没有因风暴而磨损的迹象? ";
            link.l1.go = "guardoftruth_3";
        break;
        
        case "guardoftruth_3":
            dialog.text = "我很确定是冬天... 哦, 谁知道呢。 也许是春天。 我记不太清了。 我可能当时喝醉了。 不过那艘护卫舰一点也没有磨损, 它是全新的。 ";
            link.l1 = "那艘美丽的护卫舰现在在哪里? ";
            link.l1.go = "guardoftruth_4";
        break;
        
        case "guardoftruth_4":
            dialog.text = "这是个黑暗的故事... Blaze被谋杀时, 每个人都怀疑沙克, 因为在尸体上发现了他的项链 --一颗鲨鱼牙。 另外, 有人看到沙克那晚在Blaze的住所。 沙克在被打上黑标记之前逃离了宝藏岛。 他拜访了黑暗牧师, 用他的护卫舰换了一艘双桅船。 现在没人知道他在哪里。 扎卡里后来把护卫舰卖给了威廉.帕特森。 ";
            link.l1 = "这个帕特森是谁? ";
            link.l1.go = "guardoftruth_5";
        break;
        
        case "guardoftruth_5":
            dialog.text = "什么, 你从没听说过威利.帕特森? 他是苏格兰人, 刚到加勒比海。 他自认为是皇家舰队的船长, 是福克斯上校的宠儿! 顺便说一句, 他也刚开始和杰克曼做些生意。 帕特森的旗舰就是‘幸运号’本身。 ";
            link.l1 = "我明白了。 你知道迪乔索现在在哪里吗? ";
            link.l1.go = "guardoftruth_6";
        break;
        
        case "guardoftruth_6":
            dialog.text = "我不知道。 在‘幸运号’那档子事之后, 我就没在宝藏岛见过他, 也没听到过他的任何消息。 ";
            link.l1 = "好的, " + npchar.name+ ", 谢谢你的详细信息! 你是个出色的酒馆老板! 但愿多些像你这样的人... 再见! ";
            link.l1.go = "guardoftruth_7";
        break;
        
        case "guardoftruth_7":
            dialog.text = "祝你好运, " +pchar.name+ "! ";
            link.l1 = "... ";
            link.l1.go = "guardoftruth_8";
        break;
        
        case "guardoftruth_8":
            DialogExit();
            AddQuestRecord("Guardoftruth", "60_1");
            pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
            // 小娱乐
            pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
            pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
        break;
        
        case "tieyasal":
            dialog.text = "伙计, 看起来你们俩在互相追逐。 是的, 迪乔索就在你站的这个地方来过。 上次你在夏普敦时, 他也是这样盘问关于你的事。 ";
            link.l1 = "该死! 真是这样... 米格尔现在在哪里? ";
            link.l1.go = "tieyasal_1";
        break;
        
        case "tieyasal_1":
            dialog.text = "我不知道。 他出海去了... 他说过什么布鲁维尔德。 他可能就去那里找你了。 ";
            link.l1 = "碰巧是你把他派到布鲁维尔德的吗? ";
            link.l1.go = "tieyasal_2";
        break;
        
        case "tieyasal_2":
            dialog.text = "不。 我只告诉他我很久没见过你了。 ";
            link.l1 = "我明白了。 好吧, 那就这样。 谢谢, 伙计! ";
            link.l1.go = "tieyasal_3";
        break;
        
        case "tieyasal_3":
            DialogExit();
            AddQuestRecord("Tieyasal", "3");
            npchar.quest.tieyasal = "true";
            pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
            pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
            pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}