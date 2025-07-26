// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref FortChref;
    FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听你说, 有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不了。 地点和时间不对。 "), "确实... 但以后吧, 不是现在... ",
                      "我会问的... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);              
            link.l1.go = "exit";
            // Addon 2016-1 Jason 海盗任务线
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
            {
                link.l1 = "阁下, 我来是为了被监禁的军官洛佩.蒙托罗... ";
                link.l1.go = "Mtraxx";
            }
        break;
        
        case "Cupture_after":
            dialog.text = RandPhraseSimple("你已经拿走了所有东西。 还想要什么? ", "还有什么是你没拿的吗? ");
            link.l1 = RandPhraseSimple("只是四处看看... ", "只是检查一下, 我可能忘了拿什么... ");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
        break;
        
        case "Slavetrader_HavanaAttack":
            dialog.text = "该死的强盗! 你竟敢袭击哈瓦那? ! 你想要什么? ! ";
            link.l1 = "想想看, 你会明白的。 ";
            link.l1.go = "Slavetrader_HavanaAttack_1";
            pchar.quest.Slavetrader_HavanaOver.over = "yes";
            AfterTownBattle();
        break;
        
        case "Slavetrader_HavanaAttack_1":
            dialog.text = "当然是金子! 除了金子, 你们这些混蛋还能对什么感兴趣? ! 而我们没有... 仓库里只有几箱。 ";
            link.l1 = "哈哈... 不, 我们对金子不感兴趣。 我们是为象牙来的... 黑色的那种。 你明白我的意思吗? ";
            link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
        
        case "Slavetrader_HavanaAttack_2":
            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//针对特别狡猾的人-别从陆地靠近
            {
                dialog.text = "哈! 我就怀疑你们是为奴隶来的。 但他们在堡垒里。 我们的援军马上就到, 你的团伙马上会被消灭。 ";
                link.l1 = "该死! 好吧, 坐在这别动... 我们离开这里! 该死... ";
                link.l1.go = "Slavetrader_HavanaAttack_lose";
            }
            else
            {
                dialog.text = "但怎么... 你怎么知道的? ";
                link.l1 = "哈! 只有傻瓜才会把5000个奴隶集中在一个地方, 还指望没人知道。 他们的气味从这里传到该死的托尔图加岛... 希望你明白, 我们要把他们从你这里带走。 ";
                link.l1.go = "Slavetrader_HavanaAttack_3";
            }
        break;
        
        case "Slavetrader_HavanaAttack_3":
            dialog.text = "好吧, 反正你赢了, 我们不得不屈服于你的暴力。 但别指望在那次抢劫和击沉两艘西班牙战舰后能逃脱正义的制裁。 ";
            link.l1 = "别这么趾高气扬, 不然你会犯心脏病的。 坐在这别动... ";
            link.l1.go = "Slavetrader_HavanaAttack_4";
            ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
            ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
        
        case "Slavetrader_HavanaAttack_4":
            string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
            DialogExit();
            SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            pchar.quest.Slavetrader_DieHardHavana.over = "yes";//现在可以在地图上显示
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));//超载也能带走
            Log_SetStringToLog("奴隶已被装上你的船");
            Log_SetStringToLog("你有30天时间将奴隶交付给雇主");
            chrDisableReloadToLocation = false;
            sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
            AddQuestRecord("Slavetrader", "27");
            AddQuestUserData("Slavetrader", "sQty", sTemp);
            SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);    //计时器
            pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
        
        case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
            DialogExit();
            SetReturn_Gover_Dialog_Exit(NPChar);
            ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            chrDisableReloadToLocation = false;
            pchar.quest.Slavetrader_DieHardHavana.over = "yes";//可以在地图上显示
            pchar.quest.Slavetrader_HavanaAttack.over = "yes";//如果从圣地亚哥陆路来-移除船只
            AddQuestRecord("Slavetrader", "27_1");
            AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
            CloseQuestHeader("Slavetrader");
            pchar.questTemp.Slavetrader = "End_quest";
        break;
        
        // Addon 2016-1 Jason 海盗任务线
        case "Mtraxx":
            dialog.text = "真有意思... 又是投诉? ";
            link.l1 = "不不, 恰恰相反, 阁下。 洛佩是我的老战友, 我们在欧洲一起打过仗... 我想帮他, 所以来请您帮忙。 ";
            link.l1.go = "Mtraxx_1";
            DelLandQuestMark(npchar);
        break;
        
        case "Mtraxx_1":
            dialog.text = "嗯... 好吧, 既然你来找我, 应该已经知道这个... 荒谬的故事了? ";
            link.l1 = "是的, 阁下。 ";
            link.l1.go = "Mtraxx_2";
        break;
        
        case "Mtraxx_2":
            dialog.text = "我建议你联系唐.罗萨里奥.古斯曼。 他和你一样想帮唐.洛佩.蒙特罗。 他试过联系受害者, 但谈判没成功。 去见他吧, 他会解释细节。 你可以在下午四点到八点在街上找到唐.罗萨里奥。 他每天都会全面检查城市警卫哨位。 ";
            link.l1 = "感谢您, 阁下! ";
            link.l1.go = "Mtraxx_3";
        break;
        
        case "Mtraxx_3":
            DialogExit();
            pchar.questTemp.Mtraxx = "jewelry_7";
            AddQuestRecord("Roger_1", "17");
            Mtraxx_CreateRosario();
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}