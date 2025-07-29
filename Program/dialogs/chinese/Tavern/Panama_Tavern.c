// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为你效劳。 你想了解什么? ",
                          "我们刚刚还在谈这个。 你一定是忘了... ", "今天这已经是你第三次问这类问题了... ",
                          "你像鹦鹉一样重复着同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 也许下次吧。 ", "对, 不知为何我忘了... ",
                      "是的, 确实是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "我听说你们镇上有个叫弗朗索瓦.贡捷的私掠者。 你知道去哪里找他吗? ";
                link.l1.go = "Panama_rat_1";
            }
            // Addon-2016 Jason 'FMK-瓜德罗普
            if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "听着, 我在找一个叫贝特朗.皮内特的人, 你听说过他吗? 他不久前到了巴拿马。 一个戴着卷发假发的威风绅士, 可能来过这里... ";
                link.l1.go = "FMQG";
            }
        break;

        //-->奴隶贸易商
        case "Panama_rat_1":
            dialog.text = NPCStringReactionRepeat("是的, 镇上有过这样一个人。 他总在阴暗的地方鬼鬼祟祟... 后来他的几个伙伴来找他, 看起来像一群亡命之徒。 他和他们一起离开了镇子。 ", "你已经问过这个问题了, 我也回答过了。 ", "我告诉过你, 你已经问过那个贡捷了。 ", "听着, 走开别烦我! 你是不是完全昏了头? ", "block", 0, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("你知道他去哪儿了吗? ", "嗯, 我想是这样... ", "是的, 对, 我问过... ", "抱歉, " + npchar.name+ "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "Panama_rat_2";
        break;
        
        case "Panama_rat_2":
            dialog.text = "好吧, 从这里步行出去只有一条路 —贝洛港。 他步行走了。 所以去那里找他吧。 ";
            link.l1 = "谢谢, 你帮了大忙! ";
            link.l1.go = "exit";
            pchar.questTemp.Slavetrader = "FindRatPortobello";
            AddQuestRecord("Slavetrader", "21_1");
        break;
        //<--奴隶贸易商
        
        // Addon-2016 Jason 'FMK-瓜德罗普
        case "FMQG":
            DelLandQuestMark(npchar);
            DelMapQuestMarkCity("panama");
            dialog.text = "贝特朗.皮内特? 法国人? 从没听说过。 不, 伙计, 我们有段时间没见过法国人了。 ";
            link.l1 = "真遗憾... 你确定吗? 他是一位重要的西班牙绅士唐.卡洛斯.德.米利亚的朋友。 他们本应一起到这里的。 ";
            link.l1.go = "FMQG_1";
        break;
        
        case "FMQG_1":
            dialog.text = "德.米利亚先生? 那位绅士一年前访问过巴拿马。 实际上, 唐.卡洛斯.德.米利亚住在贝洛港。 他是当地总督的密友。 ";
            link.l1 = "明白了。 没必要在丛林里浪费时间和精力了。 谢谢你, 伙计。 ";
            link.l1.go = "FMQG_2";
        break;
        
        case "FMQG_2":
            DialogExit();
            pchar.questTemp.FMQG = "headhunter_portobello";
            AddQuestRecord("FMQ_Guadeloupe", "8");
            AddMapQuestMarkCity("PortoBello", true);
            AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}