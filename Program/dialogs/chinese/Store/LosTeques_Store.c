void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sLoc;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch(Dialog.CurrentNode)
    {
        case "First time":
            if (LAi_grp_playeralarm > 0)
            {
                dialog.text = NPCharRepPhrase(pchar,
                    LinkRandPhrase("镇上已经拉响警报了。 所有人都在找你! 如果我是你, 就不会在这里久留。 ", "整个城镇卫兵都在搜捕你。 我不是傻瓜, 不会跟你说话的! ", "快跑, 伙计, 趁士兵还没把你剁成肉泥... "),
                    LinkRandPhrase("你需要什么, 恶棍? ! 城镇卫兵现在正在追你。 你跑不远的, 肮脏的海盗! ", "滚出我的房子, 凶手! 卫兵!! ", "我不怕你, 小混蛋! 很快他们就会绞死你, 你逃不掉的... "));
                link.l1 = NPCharRepPhrase(pchar,
                    RandPhraseSimple("呵, 我不太担心警报... ", "他们没机会抓到我。 "),
                    RandPhraseSimple("闭上你的嘴, " + GetWorkTypeOfMan(npchar, "") + ", 不然我就割下你该死的舌头! ", "呵, " + GetWorkTypeOfMan(npchar, "") + ", 你也想追捕海盗! 听着, 伙计, 保持冷静, 你就能活下去... "));
                link.l1.go = "exit";
                break;
            }
            if (npchar.quest.meeting == "0")
            {
                dialog.text = TimeGreeting() + "! 我以前从没见过你, 先生。 我能猜你是船长... 对吗? 我叫" + GetFullName(npchar) + ", 我的商店为你服务。 黄金。 白银, 还有更多能引起好奇之人兴趣的东西。 ";
                Link.l1 = "原来如此。 我是" +GetFullName(pchar)+ "。 很高兴见到你, " + npchar.name+ "。 ";
                Link.l1.go = "meeting";
                npchar.quest.meeting = "1";
            }
            else
            {
                dialog.text = TimeGreeting() + ", 先生! 很高兴再次在我的商店见到你。 你想购买一些金块吗? 或者今天可能对矿石感兴趣? ";
                link.l1 = "给我看看你的商品, " + npchar.name+ "。 ";
                link.l1.go = "trade";
                link.l4 = "不, 我不需要任何东西, " + npchar.name+ "。 我只是顺道来跟你打个招呼。 ";
                link.l4.go = "exit";
            }
            NextDiag.TempNode = "First time";
        break;
        
        case "meeting":
            dialog.text = "我也很高兴, 先生。 你会看看我的商品吗? 我肯定有你感兴趣的东西。 ";
            link.l1 = "这是我第一次来这里, 我想多了解一点这个定居点。 ";
            link.l1.go = "info";
            link.l2 = "那就给我看看你有什么出售的。 ";
            link.l2.go = "trade";
        break;
        
        case "info":
            dialog.text = "我们的小镇是因金矿而建的。 他们开采金矿石。 白银和金块。 有时甚至还有宝石。 在友好的印第安人和一些白人定居者加入我们之前, 这里只有驻军\n伊格纳西奥.奥尔特加建了一家酒馆, 让我们的生活更愉快了些。 各种各样的冒险家来到这里, 怀着抢劫我们的愚蠢意图。 我们这里没有法庭, 所以在我们在镇中央绞死几个白痴后, 他们的数量就减少了\n金矿石在士兵和友好印第安人的保护下被运到船上, 不过你可以在这家商店买到金块\n此外, 我有时会提供非常有趣的矿石, 所以你有时间就来看看, 我总是会补充库存。 ";
            link.l1 = "谢谢你讲的有趣故事! 我会记住的。 ";            
            link.l1.go = "exit";
        break;
        
        case "trade":
            DialogExit();
            if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
            {
                GiveItemToTrader(npchar);
                SaveCurrentNpcQuestDateParam(npchar, "trade_date");
            }
            LaunchItemsTrade(npchar, 0);
        break;

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;

        // ============== 光天化日之下的抢劫, 试图打开箱子 =========================
        case "Man_FackYou":
            dialog.text = LinkRandPhrase("光天化日之下抢劫!!! 这里发生了什么? ! 等等, 等等, 伙计... ", "嘿, 你在那里做什么? ! 想抢劫我吗? 现在你完蛋了... ", "等等, 你到底在做什么? 原来你是个小偷! 准备完蛋吧, 混蛋... ");
            link.l1 = LinkRandPhrase("魔鬼!! ", "天啊!! ", "啊, 该死! ");
            link.l1.go = "fight_owner";
        break;
        
        case "fight_owner": // 樵夫 。 退出对话 。 如果在箱子里翻找过。 
            LAi_SetOwnerTypeNoGroup(NPChar);
            LAi_group_Attack(NPChar, Pchar);
            if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            NextDiag.CurrentNode = "First time";
            DialogExit();
        break;
    }
}