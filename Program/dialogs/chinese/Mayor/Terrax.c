// 马库斯.蒂拉克斯, 拉维吉男爵
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sLoc, sTemp;
    int i;
    bool bOk;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------愤怒模块-----------------------------------------------
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
            switch (npchar.angry.kind) //此处配置愤怒反应 (npchar.angry.name 已删除空格) 
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------愤怒模块-----------------------------------------------

    switch(Dialog.CurrentNode)
    {
        // --------------------------------- —首次对话 - 初次见面
        case "First time":
            // Addon 2016-1 Jason 海盗线补丁17/1
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
            {
                if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
                {
                    dialog.text = "啊, 王子, 你终于来了。 至少你们中还有人记得露面! 活儿等着呢, 你们却全消失了! 其他人到底在哪儿? ";
                    link.l1 = "天知道... 马库斯, 我退出。 我受够了。 死人在我梦里纠缠, 连路西法都在背后盯着我。 最近流的血太多了。 ";
                    link.l1.go = "mtraxx_113";
                    break;
                }
            }
            // Jason 国家任务
            // 如果《萨迦》任务中断, 则马库斯在两处有节点且提前支付
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
            {
                dialog.text = "有什么‘差事’给我吗? ";
                link.l1 = "问候你, 马库斯。 是的, 我有一桩‘差事’, 既赚钱又实际。 ";
                link.l1.go = "patria_x";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
            {
                dialog.text = "你把钱带来了吗? ";
                link.l1 = "带来了。 ";
                link.l1.go = "patria_x8";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
            {
                dialog.text = "那是我们的客户! 任务完成了, 你的男爵正坐在戒备森严的地牢里。 或许你想看看他, 呵呵? ! ";
                link.l1 = "我以后有的是时间看, 哈哈。 他被善待了吗? ";
                link.l1.go = "patria_10";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
            {
                dialog.text = "查尔斯, 搞什么鬼? ! ";
                link.l1 = "马库斯, 一切都搞砸了。 我既来不了也没法通知你... ";
                link.l1.go = "patria_x33";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
            {
                dialog.text = "我们的幕后操纵者来了! ";
                link.l1 = "哈哈! 这场戏太完美了! ";
                link.l1.go = "patria_x29";
                break;
            }
            dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("你有什么要告诉我的吗? 没有? 那就别烦我! ", "哈, " +pchar.name+ "! 有什么事找我吗? 没有? 那就别打扰我。 ") + "",
                         "我以为我已经说清楚了... 我让你离开, 但你还在烦我! ",
                         "够了, 我受够这种无礼了。 ", "repeat", 3, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("我这就走。 ",
                                               "好的, 马库斯... ",
                                               "抱歉, 马库斯... ",
                                               "哦... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "First time";
			
            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都在生你的气, 小子, 你最好离开这里... ", "看来你变成疯狗了, 小子。 想伸展拳脚? 无意冒犯, 但这儿没你的事, 滚吧! ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题。 ", "请帮我解决这个麻烦... ");
                link.l1.go = "pirate_town";
                break;
            }
            // 《萨迦》- 结束巴尔巴宗的诱惑
            if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
            {
                // Addon 2016-1 Jason 海盗线补丁17/1
                if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
                {
                    link.l1 = "马库斯, 你就不能别再生我的气吗? 我救了你朋友文森特 —和我们一起突袭卡塔赫纳的那个, 还救了你的命! 难道伯纳德没告诉你? ";
                    link.l1.go = "Temptation_13";
                }
                else
                {
                    link.l1 = "你为什么这么无礼, 马库斯? 伯纳德没跟你说过我吗? ";
                    link.l1.go = "Temptation";
                }
            }
            // Addon 2016-1 Jason 海盗线
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
            {
                link.l2 = "我在找工作... 你有什么赚钱的门路吗? ";
                link.l2.go = "Mtraxx";
            }
            if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
            {
                link.l2 = "我有些丝绸要卖。 ";
                link.l2.go = "Mtraxx_silktrade";
            }
            if (pchar.questTemp.Mtraxx == "silk_14")
            {
                link.l1 = "我给你找到了买家。 是皇家港的一个造船商, 他的生产需要船用丝绸, 每月能以每卷25杜布隆的价格购买一百卷。 他的人会在10号到15号夜间在内格里尔角接货, 密码是‘A merchant of Lyons’(里昂的商人)。 Bald Geffrey已经把第一批货送到牙买加了。 ";
                link.l1.go = "mtraxx_13";
            }
            if (pchar.questTemp.Mtraxx == "silk_15")
            {
                link.l1 = "我给你找到了买家。 是皇家港的一个造船商, 他的生产需要船用丝绸, 每月能以每卷25杜布隆的价格购买一百卷。 他的人会在10号到15号夜间在内格里尔角接货, 密码是‘A merchant of Lyons’(里昂的商人)。 我花了两个多月才找到这样的买家, Geffrey肯定已经把丝绸卖给走私者了。 对不起, 马库斯。 ";
                link.l1.go = "mtraxx_15";
            }
        break;

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
            {
                dialog.text = RandPhraseSimple("你疯了吗? 想当屠夫? 所有海盗都在生你的气, 小子, 你最好离开这里... ", "看来你变成疯狗了, 小子。 想伸展拳脚? 无意冒犯, 但这儿没你的位置, 滚吧! ");
                link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "请帮我解决这个麻烦... ");
                link.l1.go = "pirate_town";
                break;
            }
            // Jason 国家任务
            if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
            {
                dialog.text = "查尔斯, 搞什么鬼? ! ";
                link.l1 = "马库斯, 一切都搞砸了。 我既来不了也没法通知你... ";
                link.l1.go = "patria_33";
                break;
            }
            if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
            {
                dialog.text = "很高兴见到你, 朋友! ";
                link.l1 = "我也很高兴见到你。 谢谢你安排的精彩好戏! ";
                link.l1.go = "patria_29";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
            {
                dialog.text = "很高兴见到你, 小子! 我能为你做什么? ";
                link.l1 = "我有个提议给你, 你知道, 很适合海盗的提议! ";
                link.l1.go = "patria";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
            {
                dialog.text = "那是我们的客户! 任务完成了, 你的男爵正坐在戒备森严的地牢里。 或许你想看看他, 呵呵? ! ";
                link.l1 = "我以后有的是时间看, 哈哈。 他被善待了吗? ";
                link.l1.go = "patria_10";
                break;
            }
            // 如果《萨迦》任务中断, 则马库斯在两处有节点且提前支付
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
            {
                dialog.text = "有什么差事给我吗? ";
                link.l1 = "问候你, 马库斯。 是的, 有一桩差事, 既赚钱又带海盗味。 ";
                link.l1.go = "patria_x";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
            {
                dialog.text = "你把钱带来了吗? ";
                link.l1 = "带来了。 ";
                link.l1.go = "patria_x8";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
            {
                dialog.text = "那是我们的客户! 任务完成了, 你的男爵正坐在戒备森严的地牢里。 或许你想看看他, 呵呵? ! ";
                link.l1 = "我以后有的是时间看, 哈哈。 他被善待了吗? ";
                link.l1.go = "patria_10";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
            {
                dialog.text = "查尔斯, 搞什么鬼? ! ";
                link.l1 = "马库斯, 一切都搞砸了。 我既来不了也没法通知你... ";
                link.l1.go = "patria_x33";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
            {
                dialog.text = "我们的幕后操纵者来了! ";
                link.l1 = "哈哈! 这场戏太完美了! ";
                link.l1.go = "patria_x29";
                break;
            }
            // 过往阴影
            if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
            {
                dialog.text = "很高兴见到你, 小子! 我能为你做什么? ";
                link.l1 = "马库斯, 我得和你谈谈。 我不确定你会不会喜欢, 但我无论如何都需要你的帮助。 ";
                link.l1.go = "shadows";
                break;
            }
            if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
            {
                dialog.text = "哈, 你来了, " +pchar.name+ "。 我一直在等你。 森林恶魔跟我念叨了你在托尔图加的麻烦... ";
                link.l1 = "他说你找到了解决办法, 对吗? ";
                link.l1.go = "terrapin";
                break;
            }
            // Addon 2016-1 Jason 海盗线
            if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
            {
                link.l2 = "我有丝绸要卖。 ";
                link.l2.go = "Mtraxx_silktrade";
            }
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", 很高兴见到你! 伙计, 你这次需要什么? ",
                         "你想要什么? ", "又来? 没事就别打扰别人! ",
                         "你是个" + GetSexPhrase("不错的私掠者", "不错的姑娘") + ", 所以暂时还能活着。 但我不想再和你说话了。 ", "repeat", 10, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("只是想见见你。 ",
                                               "没什么。 ",
                                               "好吧, 马库斯, 对不起。 ",
                                               "该死, 我真的很抱歉, 马库斯! ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "I_know_you_good";
        break;

// ============== 光天化日之下的抢劫, 试图翻找箱子 =========================
        case "Man_FackYou":
            dialog.text = LinkRandPhrase("抢劫!!! 这不可容忍! 准备受死吧, 老鼠... ", "嘿, 你在那儿干什么? ! 以为能抢我? 你完蛋了... ", "等等, 搞什么鬼? ! 原来你是个小偷! 混蛋, 受死吧... ");
            link.l1 = LinkRandPhrase("该死! ", "卡兰巴! ", "啊, 见鬼! ");
            link.l1.go = "PL_Q3_fight";
        break;
                    
        // ======================== 愤怒节点模块 ===============>>>>>>>>>>>>>>>
        case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("" + GetSexPhrase("滚开", "滚开") + "这里! ", "从我的家里滚出去! ");
            link.l1 = "哦... ";
            link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
                    dialog.text = "别用你那些没用的话打扰我工作。 下次就不会这么便宜你了... ";
                    link.l1 = "知道了, 马库斯。 ";
                    link.l1.go = NextDiag.TempNode;
                    CharacterDelAngry(npchar);
                }
            }
        break;
        case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("我受够你了。 ", "我不想和你说话, 你最好离我远点。 ");
            link.l1 = RandPhraseSimple("好吧... ", "嗯, 那好吧... ");
            link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
                    dialog.text = "我希望你别再用空话烦我, 否则我不得不杀了你。 我是说, 我不想那么做。 ";
                    link.l1 = "你放心, 马库斯, 我不会的... ";
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
            DoReloadCharacterToLocation("Lavega_town", "reload", "reload6");
        break;
        // <<<<<<<<<<<<============= 愤怒节点模块 =============================
		
//--> -----------------------------萨迦 - 巴尔巴宗的诱惑 收尾阶段---------------------------
        case "Temptation":
            dialog.text = "哈! 土耳其人的英雄? 抱歉刚才招呼有点粗鲁, 小子。 伯纳德已经跟我讲了你精彩的参与, 还说有人给我设了陷阱。 我想听听细节... ";
            link.l1 = "确实是个陷阱。 他们盯上的是你, 不是伯纳德。 他只是诱饵。 "
            link.l1.go = "Temptation_1";
        break;
        
        case "Temptation_1":
            dialog.text = "";
            link.l1 = "计划很简单。 他们想让你去救朋友, 然后第一个登上‘分离器’号。 就在那一刻, 他们会炮击那艘船, 把它炸成碎片。 那艘双桅帆船装满了火药, 就像撒了硫磺的地狱。 ";
            link.l1.go = "Temptation_2";
        break;
        
        case "Temptation_2":
            dialog.text = "该死! 这疯狂的主意是谁想出来的? 我怎么会知道他们把伯纳德藏在哪儿? ! ";
            link.l1 = "策划者是杰克曼和他弟弟大卫。 会有信使通知你说‘分离器’号在土耳其岛南部海湾等你救援。 他们选了我当信使, 这是他们的失误。 ";
            link.l1.go = "Temptation_3";
        break;
        
        case "Temptation_3":
            dialog.text = "我不明白! 你在这整件事里是什么角色? ";
            link.l1 = "我盯着那个混蛋杰克曼很久了。 如果你不知道, 我和扬.斯文森一起做事。 我和森林恶魔决定揭发他。 扬确信 blaze 的死该归咎于他, 而史蒂文是被冤枉的。 ";
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
            else link.l1.go = "Temptation_4"; //补丁17/1
        break;
        
        case "Temptation_4":
            dialog.text = "呵! 但在 blaze 尸体上发现了一颗刻有他名字缩写的鲨鱼牙 —S.D。 —所有人都知道那是史蒂文的... ";
            link.l1 = "那是栽赃。 杰克曼下了大赌注。 他除掉了纳撒尼尔.霍克, 取代了他在马龙镇的位置, 然后谋杀了Sharp, 让鲨鱼背负罪名。 我有足够证据证明他的罪行, 是在雅各布的箱子里找到的, 里面还有Sharp地图的第二部分和霍克的碎片。 ";
            link.l1.go = "Temptation_5";
        break;
        
        case "Temptation_5":
            dialog.text = "该死! 所以史蒂文是无辜的? 雅各布为什么要这么做? ";
            link.l1 = "他想成为兄弟会的首领, 还惦记着伊斯莱索罗岛的事。 他得不到你和斯文森的支持, 所以决定把你们俩都除掉, 你是第一个目标, 扬作为最危险的人是第二个。 ";
            link.l1.go = "Temptation_6";
        break;
        
        case "Temptation_6":
            dialog.text = "那个混蛋在哪儿? ! 我要把他撕成碎片! ";
            if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) //鲨鱼还活着
            {
                link.l1 = "杰克曼和他弟弟都死了, 其他猎手也一样。 我亲手解决了他们。 这个混蛋再也不能害人了。 马库斯, 你会投史蒂文.多德森一票吗? 这是我个人的请求。 ";
                link.l1.go = "Temptation_7";
            }
            else
            {
                link.l1 = "杰克曼和他弟弟都死了, 其他猎手也一样。 我亲手解决了他们。 这个混蛋再也不能害人了。 不幸的是, 史蒂文被杀了... ";
                link.l1.go = "Temptation_10";
            }
        break;
        
        case "Temptation_7":
            dialog.text = "我当然会投! 我一直认为鲨鱼是继 blaze 之后我们中最有价值的人。 我差点都相信他有罪了, 我们都差点信了! 给, 拿着我的碎片。 ";
            link.l1 = "很好! 现在你可以安心了。 ";
            link.l1.go = "Temptation_8";
        break;
        
        case "Temptation_8":
            GiveItem2Character(pchar, "splinter_mt"); //给碎片
            dialog.text = "没错... 据我所知, 你代表鲨鱼的利益? ";
            link.l1 = "是的, 我和扬.斯文森。 好了, 马库斯, 再见! ";
            link.l1.go = "Temptation_9";
        break;
        
        case "Temptation_10":
            dialog.text = "死了? ! 怎么死的? 也是杰克曼干的? ";
            link.l1 = "不, 是他自己的水手长干的, 叫查德.卡珀。 他已经得到了应有的惩罚... 马库斯, 斯文森认为你是最适合成为兄弟会新领袖的人, 其他男爵会支持这个决定。 你接受吗? ";
            link.l1.go = "Temptation_11";
        break;
        
        case "Temptation_11":
            dialog.text = "呵! 不用问第二遍。 成为兄弟会首领是极大的荣誉! 别以为我会反对。 ";
            link.l1 = "太好了。 很高兴你接受了。 ";
            link.l1.go = "Temptation_12";
        break;
        
        case "Temptation_12":
            GiveItem2Character(pchar, "splinter_mt"); //给碎片
            dialog.text = "给, 拿着我的碎片, 交给斯文森。 我猜他现在负责吧? ";
            link.l1 = "是的。 好了, 马库斯, 再见! ";
            link.l1.go = "Temptation_9";
        break;
        
        case "Temptation_9":
            dialog.text = "是的, 我还想感谢你救了我朋友伯纳德。 给, 拿着这个装满金子的钱包。 ";
            link.l1 = "谢谢! 再见! ";
            link.l1.go = "Temptation_exit";
        break;
        
        case "Temptation_exit":
            DialogExit();
            TakeNItems(pchar, "gold_dublon", 300);
            Log_Info("你收到了300杜布隆");
            PlaySound("interface\important_item.wav");
            NextDiag.CurrentNode = "I_know_you_good";
            AddQuestRecord("BarbTemptation", "25");
            if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
            ChangeCharacterComplexReputation(pchar, "fame", 1);
        break;
        
        // Addon 2016-1 Jason 海盗线补丁17/1
        case "Temptation_13":
            dialog.text = "是啊, 他跟我讲了查理王子在土耳其岛的英勇登场... 你说救了我的命? 怎么救的? 伯纳德跟我提过有陷阱... ";
            link.l1 = "没错, 是个陷阱。 你是目标, 伯纳德只是诱饵... ";
            link.l1.go = "Temptation_1";
        break;
        
        case "Temptation_14":
            dialog.text = "哈哈哈, 为森林恶魔效力啊, 王子? 这么说, 你跟他混比跟我混挣得多? 跟我说实话! ";
            link.l1 = "马库斯, 我们永远别再提过去了。 我们现在有共同的目标, 这比抢劫商队更重要。 该死! 这是现在最重要的事! 兄弟会的未来危在旦夕! ";
            link.l1.go = "Temptation_15";
        break;
        
        case "Temptation_15":
            dialog.text = "好吧, 王子, 我明白了! 毕竟你是自由私掠者, 为森林恶魔效力是你的选择, 而且你做了个正确的决定... 那么史蒂文... 你说他是被诬陷的, 对吗? ";
            link.l1 = "完全正确。 ";
            link.l1.go = "Temptation_4";
        break;
        
        // 过往阴影
        case "shadows":
            dialog.text = "当然, 我会尽力帮你! 说吧。 ";
            link.l1 = "看看这个, 马库斯... 这是一颗鲨鱼牙。 你能告诉我什么? ";
            link.l1.go = "shadows_1";
        break;
        
        case "shadows_1":
            RemoveItems(pchar, "shark_teeth", 1);
            dialog.text = "哈! 这是史蒂文.多德森杀死的白鲨的牙齿, 他当时想给一个女孩留下印象, 从那以后人们就开始叫他鲨鱼。 很少有人能在水下只用一把军刀做到这一点。 但他当时年轻又愚蠢, 而Beatrice Sharp是加勒比海最美的女孩... 你怎么得到它的? ";
            link.l1 = "是圣约翰前刽子手给我的。 这颗牙被用来杀了一个人, 他叫... 约书亚.利德比特。 ";
            link.l1.go = "shadows_2";
        break;
        
        case "shadows_2":
            dialog.text = "那是个老故事了。 史蒂文杀了那个人。 他对Beatrice的死感到震惊, 认为利德比特是唯一该为此负责的人。 但后来他在约书亚的尸体上发现了一些文件, 研究之后他后悔了。 \n面具不该为Beatrice的死负责, 他只想要屠夫。 屠夫嫉妒的前女友杰西卡策划了这一切。 ";
            link.l1 = "你看过那些文件吗? ";
            link.l1.go = "shadows_3";
        break;
        
        case "shadows_3":
            dialog.text = "我为什么要看? 当然没看。 我对它们不感兴趣。 但如果你有时间, 我可以告诉你为什么面具在追捕屠夫。 喝醉的史蒂文跟我讲过很多次这个故事。 ";
            link.l1 = "我有时间。 相信我, 我的兴趣是有目的的, 我甚至可以把这个故事写下来。 ";
            link.l1.go = "shadows_4";
        break;
        
        case "shadows_4":
            dialog.text = "我知道你从不浪费时间。 那就听着。 约书亚.利德比特是英国海军上尉, 传奇的‘Neptune’号由他指挥... ";
            link.l1 = "... ";
            link.l1.go = "shadows_5";
        break;
        
        case "shadows_5":
            DialogExit();
            SetLaunchFrameFormParam("一小时后", "Saga_FinalLedbitterStory", 0, 4);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, 1, 10); //转动时间
            RecalculateJumpTable();
        break;
        
        case "shadows_6":
            AddQuestRecordInfo("Mask", "1");
            dialog.text = "... 但利德比特活了下来, 被一艘船救起。 他的伤毁了容, 从那以后就一直戴着面具。 一段时间后, 人们开始叫他面具。 向那个让他终身毁容的人复仇成了他的人生目标。 ";
            link.l1 = "我明白了... 我都记下来了。 我想我得重新读一遍, 把它和我已有的所有信息联系起来。 真是个悲伤的故事。 你见过杰西卡吗? ";
            link.l1.go = "shadows_7";
        break;
        
        case "shadows_7":
            dialog.text = "当然! 在屠夫甩了她之前, 她跟着屠夫参加了所有航行。 杰西无法原谅他。 人们称她为屠夫的护身符, 因为有她在, 屠夫总是很幸运。 \n信不信由你, 他在巴巴多斯甩了她之后, 生意就开始走下坡路, 战利品变少了, ‘Neptune’号也经常光顾伊斯莱索罗岛的造船厂。 但这也可以解释为屠夫大部分时间都在船舱里陪Beatrice, 而不是在甲板上。 \nBeatrice不像杰西卡, 她不喜欢冒险和战争, 尽管尼古拉斯教过她击剑和航海。 是的, 她喜欢海上浪漫故事, 但她内心不够坚强。 屠夫的‘Neptune’号不适合她, 最终害死了她。 ";
            link.l1 = "那杰西卡呢? ";
            link.l1.go = "shadows_8";
        break;
        
        case "shadows_8":
            dialog.text = "哦, 她可了不起... ‘Neptune’号上的每个水手都服从她的命令, 不只是因为她是船长的女朋友。 杰西是击剑和航海大师, 屠夫的心血没有白费。 她坚韧不拔, 无所畏惧, 而且非常美丽。 \n很多男人想和她上床, 但她只想要屠夫, 惹她很危险, 很多人亲身体验过后果, 对于最执着的人, 她的击剑课成了他们人生的最后一课。 \n杰西有一把非常特别的剑, 加勒比海独一无二, 我不知道她从哪弄来的。 火焰刃剑。 剑身不能用手抓, 哪怕轻轻一碰也会留下可怕的伤口。 \n杰西天生不是冒险家, 而是职业使然。 顺便说一句, 如果你想了解更多关于她的事, 可以和你的一个熟人谈谈, 他能比我告诉你更多。 ";
            link.l1 = "真的吗? 这个人是谁? ";
            link.l1.go = "shadows_9";
        break;
        
        case "shadows_9":
            dialog.text = "扬.斯文森。 森林恶魔永远不会承认, 但他曾对杰西卡有过计划。 那时他已经占领了西缅因, 名声令人羡慕, 所以那个母老虎对他来说很合适。 \n屠夫甩了杰西后, 扬开始异常频繁地访问巴巴多斯, 把驻军吓得够呛, 他就是这样。 如你所知, 杰西卡是布里奇敦种植园主的女儿。 \n总之, 他的计划在私人圈子里众所周知, 但没人敢说出来。 扬现在可能在布鲁维尔德无所事事, 但那时任何对他不敬的话都可能带来严重后果。 \n最后, 他们的计划没有成功。 杰西无法承受被屠夫背叛的痛苦, 一年后在面具的帮助下进行了报复。 这场报复对所有人都很糟糕: 屠夫。 Beatrice。 面具和她自己, 他们都死了。 ";
            link.l1 = "不, 屠夫还活着。 ";
            link.l1.go = "shadows_10";
        break;
        
		case "shadows_10":
			dialog.text = "什么? ! 我听错了吗? ! 他还活着? ! ";
			link.l1 = "是的。 布彻船长并没有被绞死。 嗯, 实际上他被绞过, 但多亏了雅各布.杰克曼和刽子手亨利 —亨利恐吓了执行绞刑的人 —他才活了下来。 那次绞刑只是一场表演。 我有证据。 ";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "难以置信! 他现在在哪里? ";
			link.l1 = "他现在用的名字是劳伦斯.贝尔特罗普, 住在皇家港。 但看起来他一点都没变, 仍然很危险。 在兄弟会里惹出很多麻烦的杰克曼, 当时就是在执行他的命令。 ";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "该死! 那个军需官终究还是找到了他的船长! 过了这么多年... 你说贝尔特罗普... 等等! 现在我明白为什么在Blaze的文件里会有那份奇怪的审讯记录了... 看来Blaze发现了布彻-贝尔特罗普的一些有趣事情... ";
			link.l1 = "你在说什么? ";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "我住进这处住所后, 花时间看了看Blaze的文件。 我发现了一份对一个叫塞缪尔.布鲁克斯的人的审讯记录, 里面有很多关于托马斯.贝尔特罗普的冒险细节 —他是著名的海盗, 也是Nicholas Sharp最亲密的朋友。 看来他是布彻的父亲。 ";
			link.l1 = "有意思。 看来贝尔特罗普和Sharp的后代继承了父辈的事业... ";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "似乎是这样... 告诉我, 朋友, 你为什么对这些早已作古的人的过去如此感兴趣? 这一切到底是为了什么? ";
			link.l1 = "我需要文件来证明埃伦.麦克阿瑟是Beatrice Sharp的女儿。 Nicholas Sharp的外孙女, 并且有权使用这个姓氏。 我不在乎她的姓氏可能是贝尔特罗普。 ";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "我在Blaze的档案里没有找到任何关于埃伦.麦克阿瑟的内容。 奇怪的是, Beatrice没有告诉Blaze他侄女出生的事, 这不像她的风格。 ";
			link.l1 = "听着, Sharp的文件里可能还有关于这个故事的其他内容吗? 我需要能找到的每一个细节! ";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "嗯... 也许有。 根据Blaze的笔记, 他当时在试图找到他妹妹去世的那个岛。 有一些关于利德比特惩罚性远征的档案文件副本, 没什么有趣的, 除了几个纬度数值。 \n这条纬线穿过加勒比海的北部, 但没有经度标记。 显然, Blaze的搜索失败了 —你都无法想象在那个纬度有多少小岛。 ";
			link.l1 = "纬度是多少? ";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "让我看看... 这里: 北纬21°32′。 我不知道这能怎么帮到你。 ";
			link.l1 = "能帮上忙。 非常感谢你, 马库斯, 谢谢你坦诚相告。 再见! ";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// 礁石岛可访问
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// 禁止官员进入
			LAi_LocationDisableOfficersGen("Shore67", true);
			// 任务立即中断
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// 激活亚历克斯的时钟任务
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// 海龟汤
		case "terrapin":
			dialog.text = "好吧, 我可以帮你做点什么。 如你所知, 托尔图加的安全不仅由拉罗什堡保障, 还由一支持续守卫岛屿海岸的海盗中队负责。 托尔图加港是安全的, 这些家伙懂行, 而且他们有强大的船只。 勒瓦瑟长期以来一直在拉拢这些船长。 \n他们甚至有能力与战列中队作战, 会是难缠的对手。 所以, 作为《法典》的守护者和海岸兄弟会的领袖, 我可以让这些看门狗离开托尔图加的海岸。 ";
			link.l1 = "就这样? ";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "这还不够吗? 反正我也帮不了更多了。 你必须摧毁堡垒, 但至少不需要和那些守卫船战斗了。 相信我, 它们比堡垒更危险, 所以我的帮助会让一切变得更容易。 ";
			link.l1 = "好吧, 如果我无论如何都要进攻, 海盗中队的离开确实会有帮助。 谢谢你, 马库斯! 我什么时候可以进攻托尔图加? ";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "随时可以。 守卫船会按我的信号离开。 ";
			link.l1 = "好的。 那我得去准备了。 ";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// 勒瓦瑟拉到屏障处! 
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // 移除海盗中队
		break;
		
		case "pirate_town":
            dialog.text = "解决问题? 你知道自己做了什么吗? 不管怎样, 给我一百万比索, 我会说服兄弟们忘记你的所作所为。 如果你不喜欢这个主意, 那就见鬼去吧。 ";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "好, 我愿意付钱。 ";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "再见... ";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//关闭快速转移
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "很好! 就当你又清白了。 但我希望你不会再做这种恶心的事了。 ";
			link.l1 = "不会了, 这对我来说太贵了。 再见... ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ----------------------- —海盗线 --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "先给自己弄艘船, 再来找工作。 陆地上的无赖在这儿没什么可做的。 滚蛋! ";
				link.l1 = "嗯... 知道了。 ";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "你完全疯了吗? 半个西班牙世界都在追捕你。 你只会帮倒忙。 解决你的问题, 然后再来申请。 我就想说这些! 滚出去! ";
				link.l1 = "嗯... 知道了。 ";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "想找点刺激, 嗯? 哈哈! 好... 不过我警告你, 小子, 跟着我你别想有安宁日子。 如果你害怕火药味, 或者不敢流血 —门在你身后。 我受不了娘娘腔。 另外, 如果你是个告密者, 或者是个想偷同伴战利品的老鼠, 你在我这儿也待不了多久。 所以, 你加入吗? ";
			link.l1 = "我加入, 马库斯。 我不怕战斗, 而且没有谁能说我是懦夫或叛徒。 ";
			link.l1.go = "Mtraxx_1";
			link.l2 = "哇, 这对我来说太苛刻了! 请原谅, 马库斯, 我还是告辞吧... ";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "怎么, 你还在这儿? ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "我有些丝绸要卖。 ";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "我这就走。 ";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "... ";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "哈哈, 好啊好啊, 我勇敢的小海盗, 那我们来谈谈生意吧。 我在圣多明戈的线人告诉我, 有个西班牙船长富得流油, 手里的蓝琥珀多到拿来送给妓女。 你听说过蓝琥珀吗? ";
			link.l1 = "听说过。 一种稀有且贵重的宝石。 ";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "没错。 即使在这里, 银行家和珠宝商也愿意出高价购买, 而在古老的欧洲, 价格能高出十倍。 琥珀在加勒比并不稀有, 但蓝色的却很罕见。 现在有个狡猾的卡斯蒂利亚混蛋在吹嘘, 说他的蓝琥珀比古巴和伊斯帕尼奥拉的银行家们的黄琥珀加起来还多。 ";
			link.l1 = "一些喝醉的西班牙人的故事能信吗? 捡到三个杜布隆, 就告诉所有人他找到了黄金国。 ";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "我本来也不信, 但他确实在用蓝琥珀送妓女。 他的吹嘘中肯定有可信之处。 去圣多明戈调查一下。 如果你能找到蓝琥珀矿, 那就更好了。 完成这个任务, 我可以保证你能得到奖励, 并在拉维加获得尊重。 ";
			link.l1 = "如果你的信息毫无价值呢? ";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "那就向我证明那个卡斯蒂利亚人是个骗子。 ";
			link.l1 = "很好。 你在圣多明戈的线人是谁? ";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour传奇版本: 如果没有, 则给予荷兰西印度公司旗帜和许可证 -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = "。 等一下, 拿一张60天的贸易许可证。 "; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // 没有旗帜
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = "。 等一下, 拿一张60天的贸易许可证和一面西班牙国旗, 以便在圣多明戈靠岸。 从现在起, 我建议你自己弄一面, 这有助于在贸易中欺骗那些蠢货。 这面得还给我。 ";
						GiveNationLicence(HOLLAND, 60);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("你收到了西班牙国旗");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // 有许可证
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = "。 等等, 没有合适的旗帜你怎么贸易? ! 给你, 这是比你的更长的60天贸易许可证, 还有在圣多明戈靠岸用的西班牙国旗。 从现在起, 我建议你自己弄一面, 这有助于在贸易中欺骗那些蠢货。 这面得还给我。 ";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("你收到了西班牙国旗");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = "。 等等, 没有合适的旗帜你怎么贸易? ! 拿着, 这是在圣多明戈靠岸用的西班牙国旗。 从现在起, 我建议你自己弄一面, 这有助于在贸易中欺骗那些蠢货。 这面得还给我。 ";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("你收到了西班牙国旗");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
// < —legendary edition
            dialog.text = "你需要找一个名叫Gabriela Chapada的妓院姑娘。 说出我的名字和密码‘Amber Necklace’(琥珀项链), 她会告诉你详情。 别浪费时间 —消息现在还算新鲜, 但过一两天可能就过时了" + sTemp;
			link.l1 = "明白了, 马库斯。 我这就去圣多明戈。 ";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // 与荣誉事件冲突
			pchar.questTemp.ZA.Block = true;			// 与'麻烦的贵族'任务冲突
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "我已经得知你到了。 给我汇报! ";
			link.l1 = "我解决了那个蓝琥珀爱好者, 虽然不容易。 我设法找到了他的矿脉并掠夺了它们。 我给你带来了" + FindRussianQtyString(i) + "块蓝琥珀。 ";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("你上交了" + FindRussianQtyString(GetCharacterItem(pchar, "jewelry7")) + "块蓝琥珀");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "呵呵... 小子, 还记得我警告过你当叛徒的下场吗? 你当时怎么说的? 没人能指责你? 你觉得我很蠢吗, 小子? 我清楚地知道你在蚊子海岸掠夺了" + FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty)) + "块蓝琥珀。 现在滚吧, 小叛徒, 快滚, 祈祷我们再也别见面! ";
				link.l1 = "该死! ";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour传奇版本: 收回西班牙国旗
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("你归还了西班牙国旗");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("你上交了" + FindRussianQtyString(GetCharacterItem(pchar, "jewelry7")) + "块蓝琥珀");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "干得漂亮, 小子! 你展现了自己最好的一面: 解决了难题, 还把掠夺的东西全带来了。 做得好! 很高兴我没看错你。 ";
				link.l1 = "我的分成呢, 马库斯? ";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty) / 2;
			PlaySound("interface\important_item.wav");
			Log_Info("你收到了" + FindRussianQtyString(i) + "块蓝琥珀");
			TakeNItems(pchar, "jewelry7", i);
			// belamour传奇版本: 收回西班牙国旗
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("你归还了西班牙国旗");
			}
            dialog.text = "这才像个真正的海盗, 哈哈哈! 战利品分你一半, 拿着吧。 ";
			link.l1 = "谢了, 船长。 还有其他任务吗? ";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "我总有任务给能干的小伙子。 有件棘手的事想让你处理。 卡普斯特维尔停泊着一艘名为‘毒蛇’的船, 船长是杰弗里.布鲁克, 人称‘秃头杰弗里’, 他为我做事。 他是个出色的战士, 对枪炮和刀剑了如指掌, 但在生活的其他方面完全是个白痴。 不过别对秃头太苛刻, 人无完人, 哈哈哈! \n听着, 这个硬汉在圣马丁北部袭击了一支荷兰船队, 俘获了一艘装满小麦袋的三桅帆船。 他竟然在麻袋里发现了隐藏的船用丝绸, 货物量非常大。 这种商品极其珍贵稀有, 荷兰人从欧洲运来只为满足军队需求, 用于制作特殊帆具, 能提高船速和迎风航行能力。 \n这东西几乎买不到, 卖出去不难, 但很难找到合适的价格。 那些该死的商人总是压价! 我知道加勒比有人愿意出高价买这种丝绸, 你的目标就是找到这样的人。 \n怎么? 任何傻瓜都能掠夺商队, 但只有脑袋里有点脑子的人才能做贸易。 我计划每月出售船用丝绸, 所以你的目标是找到一个固定买家, 每卷至少支付20枚金币。 你有两个月时间, 我不能让秃头杰弗里在卡普斯特维尔待太久。 \n就这些。 起航去卡普斯特维尔, 在杰弗里把货物贱卖给走私犯之前和他谈谈。 我告诉过你, 他有点‘单纯’。 ";
			link.l1 = "嗯... 知道了。 这就出发。 ";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "哈! 勇敢的" +GetFullName(pchar)+ "船长来了! 买家怎么样了? ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "我给你找到了买家, 是皇家港的一个造船商。 他生产需要船用丝绸, 每月能以每卷25杜布隆的价格购买100卷。 他的人会在10号到15号夜间, 在尼格瑞尔角接货, 密码是‘A merchant of Lyons’(里昂的商人)。 我花了两个多月才找到这样的买家, 杰弗里肯定已经把丝绸卖给走私犯了。 对不起, 马库斯。 ";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "我给你找到了买家, 是皇家港的一个造船商。 他生产需要船用丝绸, 每月能以每卷25杜布隆的价格购买100卷。 他的人会在10号到15号夜间, 在尼格瑞尔角接货, 密码是‘A merchant of Lyons’(里昂的商人)。 秃头杰弗里已经把第一批货送到牙买加了。 ";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "太好了, 朋友! 干得漂亮。 很难找到能同时动手和动脑的人。 20天后来找我拿奖励, 到时候秃头杰弗里会把第一笔交易的钱带回来。 "; // 测试3修正
			link.l1 = "好的, 马库斯。 很快见。 希望你还有其他任务给我。 ";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "会有的。 回头见。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // 测试3修正
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "可惜, 但仍是巨大的成功。 你做得很好! 你拿不到杰弗里那批货的分成, 但仍该得到奖励。 一个月后来找我, 到时候我会把第一批货卖给你的买家, 然后我们再谈。 ";
			link.l1 = "好的, 马库斯。 很快见。 希望你还有其他任务给我。 ";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "你来了, " +pchar.name+ "。 我们谈谈你的奖励。 ";
			link.l1 = "我喜欢谈这种事, 哈哈哈! 洗耳恭听。 ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "秃头杰弗里把第一批105卷船用丝绸卖给了你的买家。 因为我原本期望每卷卖20杜布隆, 所以我觉得把差价给你是公平的。 这是我的决定。 你的分成是525杜布隆, 加上每卷1杜布隆的奖金, 总共630杜布隆。 拿着吧。 ";
			link.l1 = "多谢, 马库斯! ";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("你收到了630枚杜布隆");
			PlaySound("interface\important_item.wav");
            dialog.text = "还有一件事, 你可以从中获得额外利润。 ";
			link.l1 = "有意思... 说吧。 ";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "你的买家希望未来两个月交付超过100卷丝绸。 如果你有货, 就以每卷24杜布隆的价格卖给我20到100卷。 这个报价有效期两个月。 ";
			link.l1 = "好! 如果有的话我会多带些来。 ";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// 丝绸贸易
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "你有多少? ";
			link.l1 = "" + FindRussianQtyString(iTotalTemp) + "。 ";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp * 24);
            dialog.text = "很好。 拿上金子 —按约定每卷24杜布隆。 ";
			link.l1 = "多谢! ";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "我要100卷。 拿上金子 —按约定每卷24杜布隆。 ";
			link.l1 = "多谢! ";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "我们谈点更紧急的事, 你想处理危险的任务吗? ";
			link.l1 = "当然! 我和我的人准备好立即起航。 ";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "该死的, " +pchar.name+ ", 你到底去哪了? 记得我让你来找我吗? 我本来有任务给你, 现在因为你绝佳的时间观念, 任务泡汤了。 你让我很失望, 小子。 滚吧, 我不跟不可靠的人合作。 ";
			link.l1 = "好吧, 该死... ";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour传奇版本: 若缺少则给予荷兰西印度公司旗帜和许可证 -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", 还有40天的贸易许可证。 "; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // 无旗帜
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", 还有40天的贸易许可证。 另外, 你打算怎么骗过堡垒里的蠢货? ! 你这么马虎早晚会让我失望... 拿着... 回来时还我。 新一代啊, 呸... ";
						GiveNationLicence(HOLLAND, 40);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("你获得了西班牙国旗");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // 有许可证
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = "。 告诉我, 你打算怎么骗过堡垒里的蠢货? ! 没有合适的旗帜, 你的文件没用。 我觉得你这么马虎早晚会让我失望... 给你, 40天的贸易许可证, 比你的长。 还有在马拉开波靠岸用的西班牙国旗。 回来时还我。 新一代啊, 呸... ";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("你获得了西班牙国旗");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = "。 告诉我, 你打算怎么骗过堡垒里的蠢货? ! 没有合适的旗帜, 你的文件没用。 我觉得你这么马虎早晚会让我失望... 拿着... 回来时还我。 新一代啊, 呸... ";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("你获得了西班牙国旗");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// < —legendary edition
            dialog.text = "那就仔细听着。 两个月前我和一位名叫让.皮卡德的船长约好见面, 他也被称为‘英俊的让’。 他没来赴约, 因为我本打算和他谈重要的事, 所以我调查了他的下落。 结果发现我们这位勇敢的私掠船长和他的双桅帆船, 与唐.爱德华多.德.洛萨德指挥的西班牙重型大帆船打了一仗, 而洛萨德是个难缠的混蛋。 结果, 让和他剩下的船员被带到马拉开波, 卖给了当地的种植园。 目前他就在那里忙着‘诚实的劳动’。 \n你的任务是: 第一, 调查他遭遇不幸的细节; 第二, 把他从种植园活着救出来带到这里; 我真的需要知道他的经历详情。 我会派一艘名为‘海鳗号’的三桅帆船船长协助你, 船长名叫保罗.尚特, 人称‘佩利.卡特勒斯’。 还记得杰弗里吗? 他几乎和杰弗里一样蠢, 但也很能打。 \n他会在巴巴多斯的拉格特角等你。 找到他和他的‘海鳗号’, 然后航行到马拉开波。 卡特勒斯会服从你的命令, 不会问愚蠢的问题 —实际上他根本不会问问题。 做好你的工作然后回来, 我会等你。 这里有一万比索作为预支费用" + sTemp + "。 有问题吗? ";
			link.l1 = "没了。 都清楚了。 这就去巴巴多斯。 ";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "那祝你好运。 动作快点, 别让卡特勒斯和可怜的让等太久。 ";
			link.l1 = "没问题, 老大! 这就走。 ";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour传奇版本: 途中若没有奴隶可去莫斯科维特处
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "欢迎回来, 我勇敢的海盗, 哈哈! 你干掉了一支西班牙中队吗? 皮卡德已经告诉我了。 干得漂亮! ";
			link.l1 = "是啊, 我们从马拉开波撤离时, 弟兄们把他们揍惨了。 ";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "欢迎回来, 我勇敢的海盗, 哈哈! 皮卡德已经告诉我了。 干得漂亮! ";
				link.l1 = "... ";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "从你眼里就能看出你在等奖励。 这很公平。 让会付你钱, 毕竟我们救的是他的命。 过后再给他发账单吧 —这小子现在没船员没船。 他和你一样聪明, 所以他现在的窘境不会持续太久。 ";
			link.l1 = "嗯... 好吧... 我会等时机。 有什么工作给我吗, 马库斯? 别再是救人或找人的。 ";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "当够了最亮的蜡烛? 那我得让你失望了: 像卡特勒斯那样没脑子的莽夫我有的是, 你的才能得用在刀刃上。 一个月后有任务给你, 现在你该航行到宝藏岛去找夏普敦的商人帕斯夸莱.拉沃西耶。 \n他要求尽快派一个厉害的海盗去办大事 —很可能是你想要的: 少动脑多开枪。 你有一周时间去见他, 别浪费时间, 不然任务就泡汤了。 还有, 礼貌点, 别想着骗他, 这人在兄弟会里很受尊敬。 现在去, 一个月后再来见我。 别迟到! ";
			link.l1 = "好的, 马库斯。 再见! ";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour传奇版本: 收回西班牙国旗
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("你归还了西班牙国旗");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "哇! 死人回来了! 我们都已经把你埋了, 小子! 但看来你还活着";
			link.l1 = "如你所见, 马库斯... ";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "那你从马拉开波到伊斯帕尼奥拉怎么花了这么久? 你现在退出我的组织了, 小子。 很高兴看到你还活着, 但这里没你工作了。 ";
			link.l1 = "唉! ... 真可惜... ";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // 迟到
			{
				dialog.text = "该死的" +pchar.name+ ", 你去哪了? ! 我让你一个月后见我! 这不是军队, 但也得有点纪律! 滚吧, 我不会再和你合作了! ";
				link.l1 = "如你所愿... ";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // 来早了
			{
				dialog.text = ""+ PChar.name+ ", 我让你‘一个月后见我’。 我现在没时间陪你。 ";
				link.l1 = "好吧... ";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "拉沃西耶的一个手下告诉我, 你在黑木生意上坑了他。 我警告过你别当叛徒, 要对帕斯夸莱公平。 你两条都违反了。 你是个聪明的小子, 但这不可接受。 滚出这里, 忘了来这里的路。 ";
				link.l1 = "该死... ";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "拉沃西耶的一个手下告诉我, 你在黑木生意上坑了他 —没把整批货带来。 如果是没脑子的卡特勒斯或秃头, 我或许会相信他们真的没抢到全部货物, 但像你这么聪明的小子... 是想骗帕斯夸莱吗? 我告诉过你‘别骗他’! 我再也不信任你了, 也没什么生意可跟你做了。 滚出这里, 忘了来这里的路! ";
				link.l1 = "你的拉沃西耶自己才是叛徒! ";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // 属性: 主角是知名海盗 // 测试3修正
				dialog.text = "哈! 查理.普林斯, 勇敢的船长! 如果你不知道的话, 这是你在拉维加的新名字。 那么, 当莽夫过瘾吗? 没有? 这次幸运女神没眷顾你? 我那些没脑子的手下, 像卡特勒斯, 就是这么活的: 今天在妓院狂欢, 把赚的钱挥霍一空, 一周后就到我门口求我给几千比索, 好付给和他一样蠢的船员。 不管了。 谈正事? ";
				link.l1 = "当然! ";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "哈! 查理.普林斯, 勇敢的船长! 哈哈! 拉沃西耶的一个手下告诉我你干得不错。 很高兴你知道尊重我们的投机商。 ";
			link.l1 = "他要是能大方点就好了... ";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // 测试3修正
            dialog.text = "还记得我怎么说没脑子的莽夫和赃物买家吗? 对。 以后别再接这种活了。 留给卡特勒斯他们吧。 不管了。 谈正事? ";
			link.l1 = "当然! ";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "太好了! 让.皮卡德要过来了, 他会跟你细说。 你和让会一起执行这次任务。 另外, 这也是他还你人情的机会... 他来了! ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// 改造皮卡德
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
		
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "bullet", 40);
			TakeNItems(sld, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "我的人会加入你的突袭队。 他叫卢卡.巴亚尔, 大多时候被称为‘小妖精卢克’。 他和他的手下是海盗 —在伊斯帕尼奥拉森林里猎了大半辈子的猎人。 所以他们是丛林徒步大师, 加上你的战士, 梅里达就归你们了。 你拿三分之一战利品, 剩下的让拿走。 让, 你从自己那份里还这位勇敢船长的人情, 然后把剩下的带给我。 之后我们再算。 有问题? 太好了! 小妖精会在我们的港口等你。 祝你们好运, 海盗们, 哈哈! ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "欢迎回来, 我勇敢的杀手! 你突袭的传闻已经传到我们这里了。 ";
			link.l1 = "不得不说我不喜欢听到这个。 这种事最好不为人知... ";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "相信我, 朋友, 它们从来都藏不住。 不管怎样, 皮卡德还清欠你的债了吗? ";
			link.l1 = "是的。 ";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "非常好。 小矮人卢克给你留下好印象了吗? ";
			link.l1 = "是的。 ";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "那就完美了。 人人开心, 人人有报酬。 ";
			link.l1 = "马库斯, 你有工作给我吗? ";
			link.l1.go = "mtraxx_44";
			// belamour传奇版 梅里达事件后的拒绝
			link.l2 = "你知道吗, 马库斯, 我权衡了所有事情, 这份工作不适合我。 很抱歉, 但我已经下定决心了。 ";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "还没有真正的工作。 不过我有个私人忙想请你帮。 有兴趣吗? ";
			link.l1 = "当然, 老板。 什么忙? ";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "在拉维加海岸附近有一艘名为'基蒂'的轻帆船。 它已经在那里等了好几天, 等着护卫队前往布里奇顿。 显然, 我不可能让它独自航行。 你能好心护送它吗? 等你回来我会给你一份真正的工作, 当然, 也会付钱给你作为护送报酬。 ";
			link.l1 = "成交。 ";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "太好了! 一路顺风。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour传奇版 -->
		case "mtraxx_44a":
            dialog.text = "什么? ! 我把你从街上拉来, 让你口袋塞满琥珀和宝石! 你就这么报答我? ";
			link.l1 = "梅里达让我明白, 我还不够狠心做这份工作。 不像你和你的人那样狠心。 别作恶了。 ";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "懦夫! 好吧, 滚吧! 去搬货度日, 或者更好, 像其他失败者一样喝死自己! ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // 设置到门后
		break;
		// <- —legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "啊, 你来了... 我已经在等你了。 这是护送'基蒂'号的10000金币。 ";
			link.l1 = "谢谢... 马库斯, 我有件事想和你谈谈。 ";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "哦? ! 哈哈! 说吧! ..";
			link.l1 = "还记得让.皮卡德是怎么被奴役的吗? 起初, 他和一个英国私掠者一起掠夺了一支荷兰商队, 然后他同样被一艘西班牙重型大帆船掠夺了。 ";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "记得。 然后呢? ";
			link.l1 = "在布里奇顿, 伊格纳西奥.马可找到了我。 就是那个为英国服务的葡萄牙私掠者。 他提议我去掠夺库拉索岛和特立尼达岛之间一个有人居住的岛屿附近的荷兰商队。 ";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "嗯... 你同意了吗? ";
			link.l1 = "我同意了。 首先, 这是个好交易。 其次, 我想起了皮卡德的故事, 决定调查一下... ";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "我就知道你会。 ";
			link.l1 = "是的。 那里有一支商队, 我们干净利落地完成了任务。 然后我们在岸上分赃, 但首先我悄悄派了一个带望远镜的守望者到山上。 这很奏效, 因为不久之后一支西班牙中队出现了, 由一艘重型大帆船率领。 ";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "你的伙伴肯定逃跑了, 所以西班牙人追你? ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "正是。 他们甚至没注意到他。 对他们来说太糟糕了: 我们和西班牙人打得太狠了, 他们永远不会忘记。 这些卡斯蒂利亚人是优秀的战士, 但我们设法摧毁了整个中队。 ";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "正是。 他们甚至没注意到他。 不过我设法逃脱了。 多亏了我的守望者... ";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "嘿! 摧毁了爱德华多.德.洛萨德的一个中队! 你真是个海魔, 王子! 我敢打赌西班牙人已经派猎人来追你了。 ";
			link.l1 = "他们倒霉... 不过我们应该处理掉伊格纳西奥这个混蛋。 如果你明白我的意思。 ";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "嘿! 我能想象当卡斯蒂利亚人意识到你从他们手中溜走时发生的混乱! 干得漂亮! ";
			link.l1 = "那是他们的问题, 不是我的。 不过我们应该处理掉伊格纳西奥这个混蛋。 如果你明白我的意思。 ";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "我会处理的。 我们应该多了解一下这个伊格纳西奥.马可。 他可能在为某人工作。 他对我的人‘感兴趣’很可疑。 他有什么船? ";
			link.l1 = "一艘名为'斗牛士'的双桅纵帆船。 一艘独特的船, 肯定是原创设计。 ";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "好, 这样更容易追踪她... 我知道了。 至于你, 王子, 我有份工作。 准备好了吗? ";
			link.l1 = RandSwear()+"当然, 头儿! ";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "听着。 不久前我们这一带有个奇怪的海盗。 名叫伍尔夫里克.约根森, 也被称为红狼。 一个非常富有传奇色彩的人物。 他几年前从北欧来到这里。 这个维京人不向勒瓦瑟交保护费, 不交朋友, 独来独往。 他是个非常神秘的人, 从来没有船员能活着离开他的队伍。 有传言说, 如果船员在酒馆里谈论他们的突袭, 他会亲自割掉他们的舌头... \n与我们大多数人不同, 伍尔夫里克从不把钱浪费在妓女或喝酒上。 从不贱卖他的战利品。 从不信任银行家, 也从不换船。 他有一艘漂亮的护卫舰'芙蕾雅'号, 还有一群忠诚的船员, 他为他们的服务和沉默支付了高薪。 我相信他是在计划尽可能多地藏匿黄金, 然后返回欧洲, 像国王一样生活。 \n但由于西班牙猎人的追捕, 他的计划没有成功。 这个人给西班牙造成了巨大的损失, 所以惩罚性远征队在伊斯帕尼奥拉岛水域追捕他, 击沉了'芙蕾雅'号, 杀死了包括红狼在内的全体船员。 红狼被西班牙船只围困在浅水区, 迎接了他的死亡。 \n问题是, 拉维加的每个人都知道红狼的宝藏, 甚至找到了沉没的'芙蕾雅'号, 但当地和印第安潜水员都没有找到任何宝藏。 他不是傻瓜, 一定在那个只有他和他的船员知道的地方藏了一大笔宝藏, 但我们不能问他们... 原因很明显。 但现在有趣的部分来了: 我有他未损坏的航海日志, 它被藏在他船上的锁箱里。 日志中没有明显的宝藏线索, 但你可以试着从字里行间找到它们。 阅读日志, 找出这个维京人在加勒比海掠夺两年后把宝藏藏在哪里, 然后找到它们。 如果你成功了 —三分之二归你。 你加入吗? ";
			link.l1 = "嗯... 听起来像在黑暗的房间里找黑猫。 日志在哪里? ";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "给你, 拿着。 祝你好运! ";
			link.l1 = "谢谢, 我会需要的... ";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//关闭地图
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "啊, 我们勇敢的船长来了。 红狼的宝藏怎么样了? ";
			link.l1 = "我正在处理。 我需要你的帮助。 ";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "我洗耳恭听。 ";
			link.l1 = "在伍尔夫里克的日志里有一个我不认识的词'Gord', 写了好几次。 我必须知道它的意思才能在调查中继续前进。 ";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "嗯... 你说'Gord'... 我也从没听过。 好吧, 一周后见我: 我会咨询一些在船上当会计的聪明人。 至少他们知道如何计算和阅读。 他们可能会给我们一些想法。 ";
			link.l1 = "好的, 马库斯。 一周后见。 ";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "我有答案了。 一个聪明人启发了我。 Gord是自由伯爵的 fortified 定居点。 ";
			link.l1 = "自由伯爵? 那是谁? ";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "类似维京海盗舰队司令的角色。 比如, 我是自由伯爵, 拉维加就是我的gord。 看来红狼很喜欢他祖先的历史, 哈哈! 这个信息帮到你了吗? ";
			link.l1 = "暂时还不知道。 我得先对比笔记。 原来Gord是定居点的意思... 谢谢你, 马库斯! ";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "那么? 你得意的表情告诉我你成功了。 ";
			link.l1 = "是的。 红狼的宝藏找到了! 不过过程并不容易。 ";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "我们的维京人藏了多少? ";
			link.l1 = "75万比索和900枚达布隆金币。 ";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "吼吼! 干得好, 王子。 我的分成呢? ";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour传奇版
			{
				link.l1 = "给, 拿着。 根据我们的约定: 25万比索和300枚达布隆。 ";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "所有比索和达布隆都在我的船舱里。 给我一分钟去拿来! ";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "你把我的分成带来了吗? ";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour传奇版
			{
				link.l1 = "给, 拿着。 根据我们的约定: 25万比索和300枚达布隆。 ";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "是是是, 我这就去! ";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour传奇版
			PlaySound("interface\important_item.wav");
            dialog.text = "非常好。 你又一次表现出色。 干得漂亮! ";
			link.l1 = "马库斯, 你查到伊格纳西奥.马可的消息了吗? ";
			link.l1.go = "mtraxx_70";
			// mitrokosta 伊斯莱莫纳任务延迟可能性
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "是的, 但我需要先核实一下... ";
			link.l1 = "什么? ";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "我怀疑马可和某人有联系... 我需要你去查清楚。 航行到马提尼克岛。 把你的船停在圣皮埃尔, 然后穿过丛林到勒弗朗索瓦。 有人告诉我在那里见过我们要找的人。 不要询问周围的海盗, 只需观察。 一旦找到那个人, 跟着他, 看看他去哪里或和谁见面。 不要攻击他或他的船, 因为那样会破坏我正在准备的计划! 我警告过你! \n跟着并监视他, 一旦了解到足够信息就回来找我。 我知道你想掐死那个混蛋, 但保持冷静。 现在出发。 你有三周时间。 祝你好运。 ";
			link.l1 = "这就去, 老板。 ";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // 迟到
			{
				dialog.text = "该死的王子! 如果你没这么慢, 本可以报仇并拿到一大笔钱! 没想到你会这样, 但既然你是个好孩子, 我原谅你。 一个月后你有机会在我面前挽回声誉。 我正在召集所有人准备突袭! \n一个月后驾一艘坚固的单桅船来见我。 卢克。 卡特勒斯。 杰弗里和让也会参加。 不要迟到, 哪怕一天! ";
				link.l1 = "我明白, 马库斯。 不会再有下次了! ";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "来得正好! 现在向我汇报。 ";
			link.l1 = "我在勒弗朗索瓦跟踪了目标人物。 他的双桅纵帆船是一支中队的一部分, 中队包括一艘护卫舰和一艘巡防舰。 马可本人去拜访了巴尔巴松, 他们在巴尔巴松的住所会面了两小时, 其他访客都被卫兵赶走了。 然后他和两个阴沉的家伙走出房子: 一个是穿胸甲的红头发大胡子, 另一个留着小胡子, 穿着厚重的 trench 盔甲。 所有人都去了港口, 在我到达圣皮埃尔之前就起航了。 ";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour传奇版 延长计时器
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "很好。 现在我看清了全貌。 你看到的这两个混蛋要么为巴尔巴松工作, 要么为杰克曼工作。 他们几乎和我的鲍德与卡特勒斯一样, 但战斗力更强。 红头发的那个叫普劳勒, 是巡防舰'墨鱼'号的船长, 留小胡子的那个是古尔, 驾驶护卫舰'无情'号。 至于我们的朋友伊格纳西奥 —他不仅为英国人。 西班牙人多斯.洛萨德工作, 还为巴尔巴松工作。 这就是他试图陷害你和皮卡德的原因。 ";
			link.l1 = "为什么? ";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "巴尔巴松的命令。 你不知道, 但雅克从不放过给我使绊子的机会。 出于明显的原因, 他从不公开反对我, 所以暗地里给我使坏。 他知道皮卡德和你是我的人。 派他的雇佣兵对付你符合他的风格, 而且他派的不是蠢货, 正如你所确认的。 ";
			link.l1 = "我解决掉马可后就去拜访巴尔巴松... ";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "打消这个念头! 你公开对抗巴尔巴松没有任何胜算。 他会轻易摧毁你。 我们要用他自己的伎俩回报他 —打击他的同伙。 准备好做这件事了吗? 这是件麻烦事。 ";
			link.l1 = "听起来像是我擅长的事! ";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "伊格纳西奥.马可。 普劳勒。 古尔和另一个叫小丑吉姆的巴尔巴松手下, 计划夺取西班牙黄金舰队的一艘船。 整个行动由巴尔巴松亲自设计, 我从间谍那里设法了解到了细节。 黄金舰队的一艘重型大帆船滞留在哈瓦那的造船厂, 而整个中队已驶往西班牙。 这艘大帆船已修复, 很快将与另外两艘船一起前往欧洲。 中队将从古巴向东北方向航行, 但我不知道具体航线。 \n我得到消息称, 西班牙船只原计划航行到圣多明戈, 然后沿着波多黎各海岸直接进入大洋。 巴尔巴松也知道这一点。 然而, 由于伊斯帕尼奥拉岛不仅可以从南部绕行, 也可以从北部绕行, 改变航线并通过特克斯或宝藏岛进入大洋, 而不经过圣多明戈, 雅克决定保险起见, 派狡猾的狐狸伊格纳西奥前往古巴。 \n马可的任务是获取即将从古巴起航。 稍后将与舰队其余部分会合的西班牙大帆船的航行日程。 他在西班牙内部有关系, 所以这个任务对他来说不难。 巴尔巴松的其他手下在圣马丁岛等待马可, 那里是开始狩猎这个战利品的最佳地点。 由于马可和荷兰人关系不太好, 他无法进入圣马丁岛水域, 因此必须向同伙发送远程信息... ";
			link.l1 = "我想我知道该做什么了... ";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "看来你很聪明, 但我还没说完。 我在Gabriela Chapada的帮助下干扰了这个计划。 你认识她。 我们一起告知西班牙人, 海盗伏击将设在波多黎各附近。 因此, 大帆船不会经过该地区, 但他们秘密派了一支海盗猎人中队前往那里。 你有多项任务。 第一项是找到并捕获'斗牛士'号。 我想你知道该怎么处理她的船长。 ";
			link.l1 = "当然... ";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "第二, 你需要查明西班牙黄金大帆船的真实航线。 马可一定有她的日程表。 拿到它并送给我。 ";
			link.l1 = "怎么送? ";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "通过空中。 拿一个笼子... 这是斯派克, 一只在拉维加出生长大的信鸽。 即使从特立尼达出发, 它也总能找到回这里的路。 一旦你拿到日程表, 写一张便条, 绑在它的腿上, 然后放飞。 斯派克几小时后就会飞到我这里。 照顾好它, 王子! ";
			link.l1 = "当然, 老板! ";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "第三, 驾驶'斗牛士'号前往圣马丁岛。 只能单独驾驶她! 否则他们会过早起疑。 向他们发送信号, 让他们航行到波多黎各, 那里有西班牙人在等待。 他们的信号代码一定在马可的文件里。 或者你可以亲自从他那里了解。 ";
			link.l1 = "明白了。 把巴尔巴松的人送给西班牙人, 真是个聪明的举动, 哈哈! ";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "正是! 我会从暗处给他一击。 就像他对我做的那样。 还有最后一件事: 一旦你向他们发送信号, 立即起航拦截西班牙大帆船及其护航队。 时间紧迫, 不能浪费。 ";
			link.l1 = "驾驶双桅纵帆船? 对抗一艘重型大帆船和另外两艘船, 而且肯定不是纵帆船? 他们会把我撕成碎片的! ";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "别像个小女孩一样哭哭啼啼! 你以为为什么要把斯派克送给我? 你不会没有后援的。 只要别让商队逃跑, 别让他们进入大洋。 明白了吗? ";
			link.l1 = "明白了, 老板。 ";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "你的奖励将是一大笔黄金, 加上马可的双桅纵帆船。 人们说她是一艘非常棒的船。 有什么问题吗? 你理解你的任务吗? ";
			link.l1 = "我不是卡特勒斯, 我知道该做什么。 我该在哪里拦截'斗牛士'号? ";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "我们说话间, 这艘船正从古巴迅速驶向菲利普斯堡。 现在应该在托尔图加附近或其稍东的位置。 所以起锚驶向圣马丁岛, 在离岛不远的地方抓住'斗牛士'号, 只是别让巴尔巴松的人看到战斗, 否则我的计划就泡汤了。 ";
			link.l1 = "马上出发! ";
			// belamour传奇版 西班牙旗帜发放条件 -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("你获得了西班牙旗帜");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "搞什么鬼? 王子, 这简直能用壁炉里的拨火棍把你敲醒。 我没想到还得跟你讲这些基本常识。 拿着西班牙旗帜, 否则你还没开始就会搞砸整件事。 把它还给我。 现在滚出去! ";
			link.l1 = "我已经在海上了, 老板";
			link.l1.go = "mtraxx_86";
		break;
		// < —传奇版
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // 拦截斗牛士号的时间, 在沉没或捕获时移除
		break;
		
		case "mtraxx_87":
            dialog.text = "所以王子, 你把一切都搞砸了, 嗯? ";
			link.l1 = "是的。 这次任务比我想象的要困难得多。 你可以对我大发雷霆, 然后把我赶出去。 ";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // 传奇版延长时间
            dialog.text = "得了吧, 别这样。 这事常有。 你是个优秀的海盗, 我们都有失败的时候。 可惜我们没拿到那笔金子... 但如果我们在一个地方没拿到, 就该从另一个地方拿, 哈哈! 你有机会挽回声誉: 三周后来找我, 最好开一艘更强的船, 但只能一艘 —我们会组成整个中队。 我正在召集所有人准备突袭! \n三周后驾一艘坚固的单桅船来见我。 卢克。 卡特勒斯。 杰弗里和让也会参加。 不要迟到! ";
			link.l1 = "不会的, 老板! ";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// 传奇版收回旗帜
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("你已归还西班牙旗帜");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // 传奇版延长计时器
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "吼吼, 喂, 小子! 没想到会在这里见到我, 对吧? 哈哈哈! 我们终究还是找到了西班牙商队... ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // 发生过登船
			{
				link.l1 = "是的老板, 我们找到了, 虽然并不容易。 ";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "是的, 但黄金大帆船和她所有的黄金都沉没了。 ";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "我们拿到了多少金子, 王子? ";
			if (iTotalTemp < 1) link.l1 = "呃... 什么都没有。 ";
			else link.l1 = "嘿... 总共" + iTotalTemp + "! ";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "该死! 西班牙人一定是把金子扔到海里了, 这样我们就拿不到了。 至少他们付出了代价。 巴尔巴松的人也是如此, 这也算一场胜利... ";
				link.l1 = "关于金子我很抱歉... 接下来做什么, 马库斯? 我们要去拉维加吗? ";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "少得可怜。 甚至不够补偿我这次出行的花费。 西班牙人一定是把金子扔到海里了, 这样我们就拿不到了。 至少他们付出了代价。 巴尔巴松的人也是如此, 这也算一场胜利... ";
				link.l1 = "关于金子我很抱歉... 不管怎样我们还是分了吧。 ";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "这战利品太差了。 刚好够支付开销。 西班牙人一定是把一部分金子扔到海里了, 这样我们就拿不到了。 至少他们付出了代价。 巴尔巴松的人也是如此, 这也算一场胜利... ";
				link.l1 = "关于金子我很抱歉... 不管怎样我们还是分了吧。 ";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "还不错, 虽然我期望更好。 西班牙人一定是把一部分金子扔到海里了, 这样我们就拿不到了。 至少他们付出了代价。 巴尔巴松的人也是如此, 这也算一场胜利... ";
				link.l1 = "我们分了战利品吧! ";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "太棒了! 我们拿到了不错的战利品, 我的朋友! 巴尔巴松的人也得到了应有的下场, 哈哈! ";
			link.l1 = "嘿, 那可是大量的金子! 我们分了吧! ";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... 就像我们在兄弟会中一直做的那样 —每人一份公平的分成。 你可以留着‘斗牛士’号, 她是你的战利品。 ";
			link.l1 = "接下来做什么, 马库斯? 我们要去拉维加吗? ";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // 传奇版将时间延长至3个月
            dialog.text = "我肯定会在拉维加, 我会在那里等你三周。 你准备好了就来。 最好开一艘更强的船, 但只能一艘 —我们会组成整个中队。 我要让我所有的人都行动起来。 你将在我的指挥下, 还有英俊的让。 光头杰弗里。 克利弗.佩利和小矮人卢克。 准备好。 我们在等待一次重要的远征和相当丰厚的战利品。 你稍后会知道所有细节。 ";
			link.l1 = "好的, 老板! 三周后在拉维加见。 ";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "再见, 杀手! 哈哈! ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// 传奇版收回旗帜
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("你已归还西班牙旗帜");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "还有别的事吗? ";
			link.l1 = "没有了, 我想没有。 我已经要回我的船了。 ";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "嘿! 那是谁的错呢, 王子? 是你的吗? ";
			link.l1 = "对不起, 老板, 但我们都尽力了... 你的射击也很出色。 顺便说一句, 瞄得很准... ";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "不管怎样。 我们都有责任。 不过我们也不是一无所获 —巴尔巴松的人得到了我们给他们的‘礼物’, 这本身就是一场胜利... ";
			link.l1 = "关于金子我很抱歉... 接下来做什么, 马库斯? 我们要去拉维加吗? ";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "王子, 你脑子坏掉了吗? 我告诉过你只带一艘船! 去处理掉多余的船, 尽快回来! 现在就去! ";
				link.l1 = "好的, 好的! ";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // 商船
			{
				dialog.text = "王子, 你决定成为我的第二个卡特勒斯了吗? 为什么给我带一艘商船来? 我可是指望你的! 去弄一艘像样的战船来! 现在就去! ";
				link.l1 = "好的, 好的! ";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "王子, 你让我惊讶。 我告诉过你带一艘战船! 你驾着这破船怎么帮我? 开一艘三级或二级船回来, 不能更低也不能更高! 现在就去! 我不会等任何人。 ";
				link.l1 = "好的, 好的! ";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "王子, 你为什么不把‘海洋主权号’带到这里来? 当我告诉你带一艘战船时, 我不是指带一艘该死的战列舰! 开一艘三级或二级船回来! 现在就去! 我不会等任何人。 ";
				link.l1 = "好的, 好的! ";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "来得正好, 海盗! 很高兴看到你安然无恙! 准备好航行了吗? ";
			link.l1 = "当然, 头儿。 随时准备。 ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "顺便问一句, 你想知道你派去波多黎各的巴尔巴松中队怎么样了吗? ";
			link.l1 = "我完全忘了这回事。 当然想知道。 他们遭遇厄运了吗? ";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "当然! 旗舰 —小丑吉姆的护卫舰‘猫头鹰号’被烧成了灰烬。 小丑吉姆本人也消失得无影无踪。 流浪汉号和古尔号遭到重创, 但他们设法逃脱了: 流浪汉号躲到了托尔图加岛, 在拉罗查的炮火保护下; 古尔号则逃到了宝藏岛。 帕斯夸莱告诉我, 古尔号还在夏普敦附近的礁石上搁浅了, 勉强才脱险。 现在阿莱克修斯大师可有不少活要干了, 呵呵。 总的来说, 西班牙人让我有点失望, 我本以为他们会把所有人都干掉。 ";
			link.l1 = "嘿, 不管怎样, 我们还是给巴尔巴松添了麻烦, 给他捎了个信。 ";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "没错。 我们谈谈正事吧。 ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "我好朋友贝尔纳.文桑的情报显示, 西班牙人在卡塔赫纳囤积了大量金条。 更确切地说, 是在其堡垒之下。 通常这会被归为西班牙黄金舰队的一部分, 但这次该轮到我们夺取了。 我们正前往南美洲大陆突袭卡塔赫纳。 ";
			link.l1 = "啊! 我没听错吧? 我们要去掠夺一整个殖民地, 还有那该死的堡垒? ";
			link.l1.go = "mtraxx_95";
			// 贝拉姆传奇版拒绝大规模远征
			link.l2 = "我不会和你去卡塔赫纳, 马库斯。 烧毁整座城市不是我想做的事。 ";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "你没听错。 我们就是要这么做。 我的战船会处理掉堡垒, 当然需要你的帮助。 大胆的杰弗里会驾驶从荷兰人那里偷来的新东印度船运载地面部队。 佩利终于摆脱了他那破旧的双桅帆船, 得到了一艘像样的巡防舰, 当然少不了我的资助。 保罗.尚和你负责消灭巡逻舰队, 你们的船员也要参与突袭, 而你, 查尔斯, 作为一名优秀的战士和船长, 要帮我摧毁堡垒。 \n奇怪的是让.皮卡德没来, 因为有人在皇家港见过他的巡防舰。 好吧, 如果他对西班牙黄金不感兴趣, 那是他的问题, 去他的。 我的朋友贝尔纳.文桑将代替他参加突袭。 此外, 小矮人卢克和他的海盗们会协助我们的部队。 我们将从堡垒夺取黄金, 并向城市索要赎金。 他们不会忘记的, 哈哈! \n现在, 去休息吧。 今晚来酒馆和我及其他船长会合! 我们要为我们的事业干杯! 我会让酒保把所有当地酒鬼都赶出去, 这样酒馆里就只有我们六个人和一些迷人的姑娘。 今晚你要和你的伙伴们痛饮, 明天早上你将率领中队, 开辟航线。 尽量尽快带我们到卡塔赫纳。 清楚了吗? ";
			link.l1 = "是, 长官! ";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // 移除敌对遭遇战
		break;
		// 贝拉姆传奇版 -->
		case "mtraxx_94a":
            dialog.text = "你... 你这个疯狂的王子! 你在耍我吗? 知道吗, 去你的! 你本有机会加入兄弟会, 有机会摆脱所有这些无用之辈。 但你却懦弱地错过了这个机会。 带着你的抱怨滚出去! 懦夫! 你会再看到的 —我会放狗咬你! ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // 关闭一个月
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // 设置到门后
		break;
		// < —传奇版
		case "mtraxx_97":
            dialog.text = "王子, 终于来了! 看, 伙计们 —我们给他准备了礼物, 他却不知道在哪里闲逛! 坐下, 我们开始! \n那么, 勇敢的海盗们! 卡塔赫纳的黄金在等着我们, 哈哈! 我以雷霆之名发誓, 我们会拿到它! 但努力工作的人也必须好好休息! 这就是为什么今天我们要在这个好地方好好享受。 给自己倒点朗姆酒, 越多越好! 把杯子倒满! 为财富之风, 为幸运之风! 我们一饮而尽! \n给你, 从我们酒馆酒窖里拿出的最好的酒, 还有岛上最美丽的女士们, 哈哈哈! \n而给你, 查尔斯, 我们送你一顶漂亮的帽子。 试试吧, 别争辩! \n海盗们, 唱我们的歌! 我们最喜欢的那首! ... ";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "是时候让他们知道我们是谁了, 海盗们。 小矮人卢克! 带上你的人, 控制城门。 我们不想让他们向堡垒派增援! 当我们冲向堡垒的士兵时, 从背后狠狠打击他们! ";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "王子和保罗! 你们看到有三艘船的军事中队了, 解决掉它们。 远离堡垒, 不要登船。 我们没有时间和位置处理战利品。 都清楚了吗? 王子, 我特别对你说, 我知道你有英雄主义情结, 以后会有机会的! \n不要靠近堡垒, 解决掉这些船, 然后回来! 我们在这里等你。 都清楚了吗? 太好了, 哈哈哈! 冲锋! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "那么, 西班牙中队已经彻底消失了。 现在该‘红龙号’登场了。 我们要把卡塔赫纳的堡垒变成一堆瓦砾。 你跟我来吗? ";
			link.l1 = "当然! ";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "‘红龙号’是一艘非常坚固的船, 加农炮威力强大, 你的船比不上她。 所以要小心, 不要逞英雄, 离我的炮远点! ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//首次输出的福利
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//首次输出的福利
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = "真是一场该死的战斗! 就是这样, 我勇敢的海盗们! 卡塔赫纳是我们的了! 抵抗已经被粉碎! 大胆的杰弗里, 小矮人卢克! 跟我来堡垒 —伯尼肯定已经找到黄金了。 王子, 带上卡特勒斯, 和总督谈判, 让他们支付25万比索的赎金! 他们有钱, 所以要坚持。 我知道你能做到。 ";
			link.l1 = "嘿! 乐意之至, 老板! ";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// 禁止在城市。 官邸。 堡垒中战斗
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "你怎么样, 王子? ";
			link.l1 = "一切顺利。 我迫使卡塔赫纳最富有的人支付了35万比索。 ";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "吼吼, 这才是我的好小子! 但钱在哪里? ";
				link.l1 = 随机咒骂()+"我马上拿来! ";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "吼吼, 这才是我的好小子! 你和卡特勒斯每人可以保留5万比索, 作为对你们速度和机智的奖励。 剩下的以后再在我们所有人之间分配。 ";
				link.l1 = "给你! ";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "那么? 别再玩了, 把钱拿到这里来! ";
				link.l1 = "这就去! ";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "太好了! 你和卡特勒斯每人可以保留5万比索, 作为对你们速度和机智的奖励。 剩下的以后再在我们所有人之间分配。 ";
				link.l1 = "给你! ";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "你一定很关心我们的黄金吧? 已经找到了 —5000单位, 而且已经在运往我们船上了。 分配已经完成, 大家都同意, 希望卡特勒斯和你也不会反对。 ";
			link.l1 = "我能分多少? ";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "由于整个行动是我策划的, 再加上‘红龙号’承担了对付堡垒的最艰巨任务, 我和我的人将获得一半的战利品。 另一半将根据其他四艘船的船员数量在船长之间分配。 你有" + GetCrewQuantity(pchar) + "名船员, 你的份额是" + sti(pchar.questTemp.Mtraxx.Cartahena.Gold) + "单位黄金和" + sti(pchar.questTemp.Mtraxx.Cartahena.Money) + "比索。 ";
			link.l1 = "好吧, 既然大家都没问题, 我也没问题! ";
			link.l1.go = "mtraxx_111";
		break;
		
case "mtraxx_111":
            dialog.text = "太棒了。 祝贺这次航行成功, 海盗们! 这里没什么可留恋的了, 该回家了。 包括我在内的所有人都有一个月的假期。 不过你除外, 王子, 我还有另一个任务给你。 你看, 托尔图加妓院的老板娘珍妮特抱怨你: 她说查理王子对她的生意不太关注和喜爱。 因此, 我命令你航行到托尔图加, 去珍妮特的妓院, 把你的奖金花在那里。 这是你应得的。 让老板娘和她的姑娘们开心。 在你在托尔图加休息好之前, 我不想见到你, 哈哈哈! ";
			link.l1 = "明白了, 老板。 这是我收到的最愉快的任务。 一定完成! ";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "再见, 先生们! 登上你们的船, 扬帆起航! 拉维加见! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason 海盗系列补丁17/1
		case "mtraxx_113":
            dialog.text = "什么? ! 让现在成了英国人的走狗, 博尔德和卡特勒斯失踪了, 小矮人和他的人也无影无踪! 现在连你也? ! ";
			link.l1 = "马库斯, 我已经做出了决定。 我赚了不少钱, 你也从我这里赚了不少钱。 但我受够了。 我要离开了。 ";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "你和皮卡德一样, 认为自己单干能赚更多钱? 是吗? 认为没有我你也能行? 哈哈哈! 滚出这里, 王子, 我不留你了。 很快, 很快你就会明白自己错得有多离谱, 然后回来求我把你那可怜的屁股收回来。 你知道吗? 我不会的! 哈哈! 从我的视线里消失! ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason 国家特殊行动
		case "patria":
			dialog.text = "吼吼! 你来得正是时候! 有什么就说吧! ";
			link.l1 = "有个家伙不怕海盗, 不把他们当回事。 他需要被教训一下, 学会尊重。 记住, 别杀他。 ";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "哈! 不是别人, 正是老查尔斯! 我打赌你又卷入什么事了! 说详细点, 这次的目标是谁, 我们该教他什么? ";
			link.l1 = "一位来自欧洲的客人, 法国财政部的督察员 —诺埃尔.福盖男爵。 他想在这里成立一家法国贸易公司, 但我和我的一个好朋友反对。 我们试图说服男爵, 在这里贸易非常危险, 因为有荷兰人。 英国人, 尤其是在莱瓦瑟被击败后的海盗, 但他不听。 我们需要让他感到恐惧, 让他亲身感受。 ";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "吼吼! 你来得正是时候! 有什么就说吧! ";
			link.l1 = "有个家伙不怕海盗, 不把他们当回事。 他需要被教训一下, 学会尊重。 记住, 别杀他。 ";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "哈! 你怎么突然决定利用海盗了? 好吧, 只要你付钱, 我不在乎。 说详细点, 这次的目标是谁, 我们该教他什么? ";
			link.l1 = "一位来自欧洲的客人, 法国财政部的督察员 —诺埃尔.福盖男爵。 他想在这里成立一家法国贸易公司, 但我和我的一个好朋友反对。 我们试图说服男爵, 在这里贸易非常危险, 因为有荷兰人。 英国人, 尤其是在莱瓦瑟被击败后的海盗, 但他不听。 我们需要让他感到恐惧, 让他亲身感受。 ";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "是是... 一位真正的男爵! 我们要袭击他的船吗? ";
			link.l1 = "计划是这样的: 他的船很快会从太子港出发前往卡普斯特维尔。 你必须在圣基茨附近拦截男爵, 把他扣为人质。 最好不要沉船, 避免杀人。 毕竟法国人是我们的朋友。 你能做到吗? ";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "嗯, 我不能保证什么, 但我会试试。 是什么船? ";
			link.l1 = "一艘名为‘法沃里’的双桅船。 ";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "双桅船不是我的‘红龙号’的对手。 我们很容易就能对付他们。 如果他们投降, 我会让所有人活下去。 ";
			link.l1 = "很好。 吓唬他们, 让他们投降。 之后, 把男爵送到满是老鼠的船舱。 尽量找最脏的地方, 但别让他在那里超过一天, 否则他可能会生病死去。 然后把他安置在船舱里, 找个隐蔽的地方把他锁起来。 让你的一些人穿上被俘法国商人的衣服, 扮演他们。 连续三天, 他们应该把无情的海盗如何追逐他们。 抢劫他们。 索要赎金。 折磨他们... 的所有细节都告诉他。 ";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "哈哈哈! 这肯定是我很久以来接过的最有趣的工作! 那么, 小伙子, 我会找到这样的演员。 毫无疑问, 听完他们的故事, 你的男爵会吓得屁滚尿流! 他们会给他看弯刀和烧热的推杆留下的伤疤... ";
			link.l1 = "太好了! 然后你要逼他给德.潘西写信, 索要赎金。 对这样的大人物来说, 35万不算多。 ";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "好的。 接下来我们做什么? ";
			link.l1 = "然后你把男爵带到特克斯岛。 在那里你收取赎金, 然后把男爵交给我。 另外, 你应该告诉他, 所有法国人都要为托尔图加和莱瓦瑟负责, 而且不止一次。 ";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "哈哈哈! 这真是个该死的诡计! 我们亲自, 嗯, 你知道我们对莱瓦瑟做了什么, 现在... 哈哈哈! ... 好吧, 小伙子。 会办妥的! 你说船很快就到? ";
			link.l1 = "很快。 我们需要留意。 ";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "哈哈哈! 这真是个该死的诡计! 这场闹剧我该收你多少钱? 好吧, 10万成交。 把钱给我。 ";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "拿去吧。 ";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "好吧, 我去拿。 ";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "太好了! 你说船很快就到? ";
			link.l1 = "很快。 我们需要留意。 ";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "别担心, 我不会让你失望的。 我会亲自处理。 当你听到男爵被俘的传闻时, 来找我。 ";
			link.l1 = "好的。 谢谢你, 马库斯。 ";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "当然, 小伙子。 如约定的那样。 关于邪恶海盗的恐怖故事, 屠杀无辜的法国商人, 鞭子的声音, 呻吟和尖叫。 带煤的火盆和烧焦的手铐。 就该这样。 ";
			link.l1 = "哇哦哇哦! 等等! 我需要他活着";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "别担心, 他会活下来的。 他用颤抖的手写了这封信。 给你。 ";
			link.l1 = "上面写了什么? 他在求潘西救他出去? ";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "没错, 小伙子! 他在乞求, 哈! ";
			link.l1 = "把这封信扔掉, 或者更好 —烧掉它。 我们一周后在特克斯岛见面。 必须看起来好像我们需要时间筹集赎金。 ";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "明白了。 一周后, 特克斯岛的北湾。 别忘了带钱: 这必须看起来像那么回事。 这一切结束后, 来找我, 我们再讨论。 ";
			link.l1 = "当然, 回头见, 马库斯! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请在截止日期前完成! ");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //取消计时器
			dialog.text = "嘿, 法国佬! 站住! ";
			link.l1 = "我不动。 ";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "这是你的男爵。 有点憔悴, 呵呵, 但还活着。 还认得出吧? 哈哈哈! ";
			link.l1 = "是的... 还能认出来。 ";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "很好。 现在把钱交出来, 否则他就完了! 别想骗我们, 我们盯着你呢! ";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "给你, 拿去吧。 ";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "该死! 我把钱忘在船上了... ";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "哈哈哈! 你是个聪明的小家伙, 法国佬。 带上你的‘阁下’。 告诉潘西, 他应该准备好钱: 你们要为对莱瓦瑟和托尔图加所做的事付出代价。 你们的商人会用他们的货物和船只来补偿我们。 哈哈哈! 别忘了再给我们带些男爵来群岛, 他们能给我们带来很多利润! 哈哈哈! ";
			link.l1 = "请上我的船, 男爵。 ";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "船长, 别想着追我们。 你知道我是谁。 我还俘虏了更多法国佬, 如果我不能按时回家, 他们都会被处决。 明白了吗? ";
			link.l1 = "时间会到的, 我们会收拾你们这些该死的亵渎者! ";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "哈哈哈哈! 你当然会! ";
			link.l1 = "... ";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); //关闭岛屿直到运送男爵
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//添加乘客
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// 特克斯岛恢复正常
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "你在开玩笑吗? ! 这是在耍什么把戏? ! ";
			link.l1 = "等一下, 我去拿... ";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
            dialog.text = "";
            link.l1 = "啊, 马库斯, 你的蠢货都干了些什么! ";
            if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
            else link.l1.go = "patria_x25";
        break;
        
        case "patria_25":
            dialog.text = "查尔斯, 你在做什么? 钱在哪里? 我没告诉我的手下这不是真的... 所以这个蠢货觉得你在骗我们... ";
            link.l1 = "灾难啊! 男爵死了... 现在德庞西会怎么做? ";
            link.l1.go = "patria_26";
        break;
        
        case "patria_x25":
            dialog.text = "查尔斯, 你在做什么? 钱在哪里? 我没告诉我的手下这不是真的... 所以这个蠢货觉得你在骗他们... ";
            link.l1 = "灾难啊! 男爵死了... 现在德庞西会怎么做? ";
            link.l1.go = "patria_x26";
        break;
        
        case "patria_x26":
            dialog.text = "好吧, 小子, 这是你的错, 希望你明白。 也许这是最好的结果, 死人不会惹麻烦。 ";
            link.l1 = "我真是个蠢货! 把一切都搞砸了。 好吧, 我去找庞西... 原谅我的愚蠢, 马库斯, 再见。 ";
            link.l1.go = "patria_28";
        break;
        
        case "patria_26":
            dialog.text = "好吧, 小子, 这是你的错, 希望你明白。 也许这是最好的结果。 ";
            link.l1 = "我真是个蠢货! 把一切都搞砸了。 好吧, 我去找庞西... 原谅我的愚蠢, 马库斯, 再见。 ";
            link.l1.go = "patria_27";
        break;
        
        case "patria_27":
            dialog.text = "你需要休息, 你状态越来越差了。 有空来找我, 我给你弄点朗姆酒和漂亮姑娘。 ";
            link.l1 = "谢谢, 我有空会来拜访你的。 ";
            link.l1.go = "patria_28";
        break;
        
        case "patria_28":
            DialogExit();
            AddQuestRecord("Patria", "75");
            LAi_SetActorType(npchar);
            if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
            else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
            sld = CharacterFromID("Terks_pirat");
            LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
            pchar.questTemp.Patria = "epizode_12_barondie";
            // 特克斯恢复正常状态
            LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
            LAi_LocationDisableOfficersGen("Shore56", false);
        break;
        
        case "patria_29":
            dialog.text = "不客气, 小子。 对我来说, 这是今年最有趣的事! 我和我的伙计们笑个不停! 所以我想为此谢谢你。 这是你的钱。 ";
            link.l1 = "你应该留一部分作为你的报酬。 ";
            link.l1.go = "patria_30";
        break;
        
        case "patria_x29":
            AddMoneyToCharacter(pchar, 350000);
            dialog.text = "拿上你的钱吧, ‘策划者’。 哈哈! 这事儿挺有意思。 ";
            link.l1 = "谢谢你的帮助, 马库斯。 祝你好运! ";
            link.l1.go = "patria_32";
        break;
        
        case "patria_30":
            AddMoneyToCharacter(pchar, 350000);
            dialog.text = "算了吧。 我这么做是为了我们的友谊。 海岸兄弟会欠你更多, 但你连一个达布隆都没要。 ";
            link.l1 = "不过, 至少拿五万作为服务费和补偿。 谢谢你, 马库斯! ";
            link.l1.go = "patria_31";
        break;
        
        case "patria_31":
            AddMoneyToCharacter(pchar, -50000);
            dialog.text = "不客气。 查尔斯, 有空就来拜访我! ";
            link.l1 = "我很乐意! ";
            link.l1.go = "patria_32";
        break;
        
        case "patria_32":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
        break;
        
        case "patria_33":
            dialog.text = "你迟到了一周! 我没告诉我的手下这不是真的... 他们不愿再等, 决定把你的男爵解决掉! ";
            link.l1 = "我真是个蠢货! 把一切都搞砸了! 我该怎么跟庞西说? ";
            link.l1.go = "patria_34";
        break;
        
        case "patria_x33":
            dialog.text = "你迟到了一周! 我没告诉我的手下这不是真的... 他们不愿再等, 决定把你的男爵解决掉! ";
            link.l1 = "我真是个蠢货! 把一切都搞砸了! 我该怎么跟庞西说? ";
            link.l1.go = "patria_x34";
        break;
        
        case "patria_34":
            dialog.text = "好吧, 小子, 这是你的错, 希望你明白。 也许这对你来说更好。 ";
            link.l1 = "好吧, 我去找庞西... 原谅我的愚蠢, 马库斯, 再见。 ";
            link.l1.go = "patria_35";
        break;
        
        case "patria_x34":
            dialog.text = "你自找的, 这是你的错。 ";
            link.l1 = "再见, 我想... ";
            link.l1.go = "patria_36";
        break;
        
        case "patria_35":
            dialog.text = "你需要休息, 你状态越来越差了。 有空来找我, 我给你弄点朗姆酒和漂亮姑娘。 ";
            link.l1 = "谢谢, 我有空会来拜访你的。 ";
            link.l1.go = "patria_36";
        break;
        
        case "patria_36":
            DialogExit();
            AddQuestRecord("Patria", "75");
            pchar.questTemp.Patria = "epizode_12_barondie";
            DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
        break;
        
        // Rebbebion, 任务'导航星'
        case "PZ_1":
            DelLandQuestMark(npchar);
            
            if (pchar.questTemp.Mtraxx == "full_complete")
            {
                dialog.text = "好久不见, 王子。 ";
                link.l1 = "我不确定这个名字给我带来的除了厄运还有什么, 马库斯。 ";
                link.l1.go = "PZ_Prince1";
            }
            else
            {
                dialog.text = "德莫尔! 你来这里做什么? ";
                link.l1 = "你好, 马库斯。 我想问你点事。 ";
                link.l1.go = "PZ_DeMaure1";
            }
        break;
        
        case "PZ_Prince1":
            dialog.text = "我看恰恰相反。 你来这里做什么? ";
            link.l1 = "你听说托尔图加新开的妓院了吗? ";
            link.l1.go = "PZ_2";
        break;
        
        case "PZ_DeMaure1":
            dialog.text = "那就问吧。 你知道我不喜欢客套, 有话直说。 ";
            link.l1 = "你听说托尔图加新开的妓院了吗? ";
            link.l1.go = "PZ_2";
        break;
        
        case "PZ_2":
            dialog.text = "你喝醉了吗? 这算什么问题? 如果这就是你真正想谈的, 别浪费我的时间。 ";
            link.l1 = "我猜你没听说? 那里最近开了一家新妓院 —非常昂贵, 只雇最漂亮。 健康。 穿着得体的姑娘。 ";
            link.l1.go = "PZ_3";
        break;
        
        case "PZ_3":
            dialog.text = "哦, 那个! 我当然听说了 —谁没听说过? ";
            link.l1 = "嗯, 我前几天才知道。 ";
            link.l1.go = "PZ_4";
        break;
        
        case "PZ_4":
            dialog.text = "哈哈哈哈, 你这个无赖, 真没想到! 不过, 你为什么要和我讨论这个? 为什么不先试试霍克斯? 呵呵。 不过... 你已经在那里玩得开心了吗? ";
            if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
            {
                link.l1 = "去过了。 顺便说一下, 他们只收达布隆。 ";
                link.l1.go = "PZ_Fucked1";
            }
            else
            {
                link.l1 = "我去过那个地方, 但没享受服务。 不过... ";
                link.l1.go = "PZ_NoFucked1";
            }
        break;
		
        case "PZ_Fucked1":
            dialog.text = "所以你是来炫耀的! 哈, 真是个无赖。 ";
            link.l1 = "其实不是。 我真的想问你点事, 马库斯。 ";
            link.l1.go = "PZ_5";
        break;
        
        case "PZ_NoFucked1":
            dialog.text = "你没去? ! 你个蠢货, 德莫尔。 如果我是你... ";
            link.l1 = "我知道你肯定会好好放纵一番。 但这不是我想和你讨论的事。 ";
            link.l1.go = "PZ_5";
        break;
        
        case "PZ_5":
            dialog.text = "到底什么事? 快点, 别让我悬着心。 ";
            link.l1 = "我在找那个地方的老板。 有人说她想见你, 并提供一个投资她生意的机会。 你不会认错的 —她是中国人。 ";
            link.l1.go = "PZ_6";
        break;
        
        case "PZ_6":
            dialog.text = "嗬嗬。 最近我还没荣幸见过中国女人。 但我不介意见见她并投资她的生意。 毕竟, 你不能大摇大摆进入莱瓦瑟的地盘, 而作为你国王的臣民, 他一旦发现我的‘龙’号, 就会被迫用海岸船只向它开火。 ";
            link.l1 = "看来她首先在考虑太子港... ";
            link.l1.go = "PZ_7";
        break;
        
        case "PZ_7":
            dialog.text = "你这么认为? 那是个错误。 即使德.穆萨克比我有钱 —我对此表示怀疑 —他也不能把任何城市预算拨给妓院, 不管它能带来多少金子。 ";
            link.l1 = "有道理。 显然她没好好想过自己的野心。 ";
            link.l1.go = "PZ_8";
        break;
        
        case "PZ_8":
            dialog.text = "你知道, 我一直想知道其他妓院是怎么维持下去的。 这不是女人的思考能力, 尤其是统治能力 —记住我的话。 ";
            link.l1 = "好吧, 你这话错了。 谢谢你的时间, 马库斯! 如果我先见到她, 我会告诉她你愿意见她。 ";
            link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
        break;
    }
}