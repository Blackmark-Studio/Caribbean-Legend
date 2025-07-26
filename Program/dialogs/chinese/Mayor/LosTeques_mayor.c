void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int i;
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
                    LinkRandPhrase("你竟敢来这里? ! 胆子不小... ", "那些蠢货怎么会让敌人闯进来? ! 真让我难以置信... ", "好吧, 如果有蠢货在我住所里乱逛, 我的卫兵就太没用了... "), 
                    LinkRandPhrase("你想要什么, 混蛋? ! 我的士兵已经追踪到你了, 你跑不掉的" + GetSexPhrase(",肮脏的海盗", "肮脏的海盗") + "! ", "肮脏的凶手, 滚出我的住所! 卫兵们!!! ", "我不怕你, 混蛋! 你会被绞死的, 你跑不掉... "));
                link.l1 = NPCharRepPhrase(pchar,
                    RandPhraseSimple("士兵一文不值... ", "他们永远抓不到我。 "), 
                    RandPhraseSimple("闭嘴, " + GetWorkTypeOfMan(npchar, "") + ", 否则我就割下你的舌头塞进你喉咙里... ", "伙计, 我劝你: 安静坐着, 或许还能多活一天... "));
                link.l1.go = "fight";
                break;
            }
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
            {
                dialog.text = "我住所里有敌人! 警报!!! ";
                link.l1 = "该死! ";
                link.l1.go = "fight"; 
                break;
            }            
            if (npchar.quest.meeting == "0")
            {
                dialog.text = TimeGreeting() + " 先生。 我是" + GetFullName(npchar) + ", 洛斯特克斯矿场的指挥官, 该矿场属于" + NationKingsName(npchar) + "。 现在, 请您告诉我您的来意, " + GetAddress_Form(NPChar) + "。 ";
                link.l1 = "这是我第一次来这里, 我想了解更多关于这个定居点及其法律的信息... ";
                link.l1.go = "info";
                link.l2 = "只是想问候您, 我这就离开。 ";
                link.l2.go = "exit";
                npchar.quest.meeting = "1";
                break;
            }
            dialog.text = "又是你, 先生? 你还想要什么? ";
            link.l1 = "没什么。 我这就走。 ";
            link.l1.go = "exit";
            NextDiag.TempNode = "First time";
        break;
        
        case "info":
            dialog.text = "我欣赏这种纪律性。 好吧, 既然你这么感兴趣, 我就给你讲讲情况。 \n洛斯-特克斯矿场是西班牙王室的财产。 我们在这里开采银和金的原矿, 以及金银块。 所有金银都属于西班牙, 并被运往旧大陆。 \n矿场守卫森严, 一直驻扎着一支西班牙精锐士兵部队。 海盗曾多次试图抢劫我们的矿场, 但后果总是对他们不利... \n如你所见, 这是个小镇。 我们有一家酒馆和一家商店。 你可以在那里以合理的价格购买金银锭。 此外, 我们的军需官也是商店的商人, 可以卖给你其他有趣的金属和矿石。 \n我们的工人大多是囚犯, 但也有少量黑奴。 如你所见, 我们总是需要新的劳动力, 每天至少有一个该死的囚犯死去。 \n所以, 如果你给我们带来奴隶, 我们会用 Nuggets 交换。 这类事情可以联系我们的首席工程师, 你可以在矿井里找到他。 \n在这里要守规矩。 不要开始决斗或打架, 不要试图偷任何东西, 尤其是金银。 我们这里没有监狱, 但有军事法庭。 \n差不多就是这些了。 遵守这些简单的规则, 你就不会有问题。 你可以在矿场内自由活动。 别忘了去酒馆, 在我的许可下, 他们提供某些... 服务。 欢迎! ";
            link.l1 = "谢谢! ";            
            link.l1.go = "exit";
        break;

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;

        // ============== 光天化日之下的抢劫, 试图打开箱子 =========================
        case "Man_FackYou":
            dialog.text = "抢劫!!! 这是不可接受的! 准备好, " + GetSexPhrase("伙计", "姑娘") + "... ";
            link.l1 = LinkRandPhrase("该死! ", "卡拉姆巴!! ", "见鬼! ");
            link.l1.go = "PL_Q3_fight";
        break;
        
        case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
            Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
            Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
            Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;

            LAi_LockFightMode(Pchar, true); // 用脚逃跑的路被锁死
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            LAi_group_Attack(NPChar, Pchar); // 对不朽的市长不起作用 :(
            i = GetCharIDXByParam("CityType", "location", Pchar.location); // 幽灵士兵
            if (i != -1)
            {
                LAi_group_Attack(&Characters[i], Pchar);
            }
        break;
    }
}