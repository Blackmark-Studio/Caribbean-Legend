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
            if (pchar.questTemp.Slavetrader == "FindRatTortuga") // 奴隶贸易商
            {
                link.l1 = "听着, 我该去哪里找弗朗索瓦.贡捷? 他应该已经到托尔图加了。 ";
                link.l1.go = "Tortuga_ratT_1";
            }
            // 海龟汤
            if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
            {
                link.l1 = "我在找亨利.蒂博。 我该去哪里找他? ";
                link.l1.go = "terrapin";
            }
            if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
            {
                link.l1 = "我在找亨利.蒂博。 我该去哪里找他? ";
                link.l1.go = "terrapin_2";
            }
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
            {
                link.l1 = "告诉我, 最近有没有一艘名叫‘圣玛格丽塔’的大帆船停靠在你们殖民地? 也许是作为私掠船的战利品? ";
                link.l1.go = "guardoftruth";
            }
            // Addon 2016-1 Jason 海盗系列
            if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
            {
                link.l1 = "听着伙计, 我在找加斯帕尔.帕门捷。 我该去哪里找他? ";
                link.l1.go = "mtraxx_jew";
            }
            // Rebbebion, "导航星"
            if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
            {
                link.l1 = "伙计, 你能帮我个忙吗? 我在找一个叫乔普.范德温克的人。 你认识他吗? ";
                link.l1.go = "PZ1";
            }
        break;
        
        case "Tortuga_ratT_1":
            dialog.text = "弗朗索瓦.贡捷? 他是谁? 我不认识叫这个名字的人。 ";
            link.l1 = "他是‘" + pchar.questTemp.Slavetrader.ShipName + "’号护卫舰的船长。 ";
            link.l1.go = "Tortuga_ratT_2";
        break;
        
        case "Tortuga_ratT_2":
            dialog.text = "我一点头绪都没有, 伙计。 而且我们港口也没停靠过叫这个名字的护卫舰, 我可以肯定地说。 ";
            link.l1 = "那好吧, 你最近在镇上看到过什么外来者吗? ";
            link.l1.go = "Tortuga_ratT_3";
        break;
        
        case "Tortuga_ratT_3":
            dialog.text = "问得好! 这是个港口城镇, 不是村庄。 每天都有陌生人经过。 不过我听说过五个奇怪的小伙子, 他们总是待在一起, 还随时准备好刀刃。 巡逻队甚至四处打听他们的情况, 但没有结果。 但我敢肯定他们不是乘护卫舰来的, 附近没见过那样的船, 明白吗? ";
            link.l1 = "嗯... 好吧, 我知道了。 谢谢你, " + npchar.name+ "。 ";
            link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "21_8");
            pchar.questTemp.Slavetrader = "wait1";// placeholder
        break;
        
        // 海龟汤
        case "terrapin":
            DelMapQuestMarkCity("SentJons");
            dialog.text = "蒂博先生在托尔图加是个名人。 他的豪宅位于港务局附近。 离开酒馆后, 径直朝港口方向走。 走到通往港口的拱门, 在十字路口左转, 一直走到街道尽头, 你会看到一栋带红屋顶的两层石头建筑。 那就是蒂博先生的豪宅。 ";
            link.l1 = "谢谢你! 我会去拜访他... ";
            link.l1.go = "terrapin_1";
        break;
        
        case "terrapin_1":
            DialogExit();
            pchar.questTemp.Terrapin = "house";
            sld = characterFromId("Tibo");
            ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
            LAi_SetOwnerType(sld);
        break;
        
        case "terrapin_2":
            dialog.text = "蒂博先生今天很忙, 总督的信使刚跑到这里来。 他也很感兴趣。 找到他有那么难吗? 他在我这里的二楼租了个房间有很长时间了, 尽管他有一整栋豪宅可以住。 我不知道他需要什么, 但他来的次数比离开的次数多得多。 而且他只在晚上待在那里。 ";
            link.l1 = "也许他现在就在这里。 ";
            link.l1.go = "terrapin_3";
        break;
        
        case "terrapin_3":
            if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
            {
                dialog.text = "不在。 他说今天要到晚上八点才回来。 你可以试着去他的豪宅找他, 但我觉得你在那里找不到他。 我看到他乘巡逻帆船出海了。 ";
                link.l1 = "谢谢你! 我稍后再去拜访他。 ";
                link.l1.go = "terrapin_4";
            }
            else
            {
                dialog.text = "在。 如果你想的话, 可以上来。 ";
                link.l1 = "谢谢你! 我会去拜访他... ";
                link.l1.go = "terrapin_4";
            }
        break;
        
        case "terrapin_4":
            DialogExit();
            pchar.questTemp.Terrapin = "tavern";
            sld = characterFromId("Tibo");
            sld.dialog.currentnode = "tibo_9";
            LAi_SetLoginTime(sld, 20.0, 8.0);
            ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
            LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // 打开房间
            LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);// 禁止战斗
            LAi_SetStayType(sld);
            // Addon 2016-1 Jason 海盗系列
            if (GetCharacterIndex("Mary") != -1)
            {
                sld = characterFromId("Mary");
                if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
                {
                    ChangeCharacterAddressGroup(sld, "none", "", "");
                }
            }
            if (GetCharacterIndex("Helena") != -1)
            {
                sld = characterFromId("Helena");
                if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
                {
                    ChangeCharacterAddressGroup(sld, "none", "", "");
                }
            }
        break;
        
        case "guardoftruth":
            dialog.text = "不知道那艘船的名字, 是‘圣玛格丽塔’还是‘卡斯蒂利亚婊子’, 但他们带来了一艘被俘的西班牙大帆船。 而且还是被一艘单桅帆船俘获的! 这才是真正他妈的航海技术! 盖乌斯.马沙, 它的船长, 已经在酒馆里吹嘘了两天 --他的第一次航行就获得了这样的战利品! 是啊, 非常英勇的行为, 登上一艘满载着教会老鼠却没有士兵守卫的大帆船。 看来那些天主教的混蛋忘了他们说过的自助者天助... ";
            link.l1 = "是的, 自助者天助, 这肯定是胡格诺派的说法。 我怎么才能见一见那个幸运的船长? 他在托尔图加吗? ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            dialog.text = "啊, 谁他妈知道。 我很久没在我的酒馆里见过他了。 他一清醒就用战利品的钱买了一艘闪亮的新船, 像个疯子一样在甲板上跑来跑去。 我不知道马沙现在在哪里。 也许他在托尔图加, 也许在海上。 ";
            link.l1 = "好吧。 谢谢你讲的故事, 伙计! ";
            link.l1.go = "guardoftruth_2";            
        break;
        
        case "guardoftruth_2":
            dialog.text = "不客气, 先生。 我总是很高兴帮助我们敬爱的" +pchar.name+ "船长, 圣皮埃尔的救世主! 稍后再来! ";
            link.l1 = "... ";
            link.l1.go = "exit";    
            AddQuestRecord("Guardoftruth", "8");
            pchar.questTemp.Guardoftruth = "tortuga1";
        break;
        
        // Addon 2016-1 Jason 海盗系列
        case "mtraxx_jew":
            dialog.text = "看来加斯帕尔在你们这类人中越来越受欢迎了。 他的房子在城墙旁边。 从酒馆左转, 朝港口方向走, 但不要到港口, 再左转, 直走, 然后右转。 一栋两层楼的房子。 ";
            link.l1 = "谢谢! ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
        break;
        
        case "PZ1":
            dialog.text = "从没听说过他。 ";
            link.l1 = "也许他用的是另一个名字。 也许你听说过他是‘班坦’号双桅横帆船的船长? ";
            link.l1.go = "PZ2";
        break;
        
        case "PZ2":
            dialog.text = "也从没听说过那艘双桅横帆船。 ";
            link.l1 = "我听说他最近在这里。 也许一点银币能让你想起什么? ";
            link.l1.go = "PZ3";
        break;
        
        case "PZ3":
            npchar.quest.PZ.Ask.Block = true;
            
            dialog.text = "嗯, 问问你是从哪里听说的。 不过我不介意拿你的银币。 ";
            link.l1 = "那这次没有银币了。 再见。 ";
            link.l1.go = "Exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}