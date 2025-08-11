// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
    {
        case "quests":
            // 帆船赛
            if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
            {
                dialog.text = "你想要什么? 啊哈, 你是帆船赛的参赛者! 对吗? ";
                link.l1 = "正是, 先生。 我需要按规则在这里登记。 ";
                link.l1.go = "Regata_check";
                break;
            }
            // 帆船赛
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用你的问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // 荷兰 Gambit
            if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "我正航行去布鲁维尔德卖些辣椒粉。 告诉我, 先生, 你有乘客要去布鲁维尔德吗? 或者至少去罗亚尔港。 载乘客赚点钱就好了, 能帮我支付船员的工资。 我已经把工资降到最低了, 但这些懒鬼还是要钱... ";
                link.l1.go = "PortofficeDone";
            }
            // 真理守卫
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
            {
                link.l1 = "有一艘名为‘Admirable’的大帆船在菲利普斯堡装载货物, 由盖乌斯.马沙伊斯指挥。 他本该运送一批辣椒粉到这里。 你能帮我找到这位船长吗? ";
                link.l1.go = "guardoftruth";
            }
            // 卡莱乌切
            if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
            {
                if (CheckAttribute(npchar, "questTemp.caleuche"))
                {
                    link.l1 = "我想问一艘名字奇怪的三桅小帆船。 ";
                    link.l1.go = "caleuche_2";
                }
                else
                {
                    link.l1 = "我听说一艘属于杰克船长... 或杰克逊船长的三桅小帆船经常造访你们港口。 你能告诉我去哪里找他吗? ";
                    link.l1.go = "caleuche";
                }
            }
        break;

        // 荷兰 Gambit
        case "PortofficeDone":
            dialog.text = "遗憾的是, 没有去布鲁维尔德或罗亚尔港的乘客。 明天或后天再来吧。 ";
            link.l1 = "太糟了。 那再见。 ";
            link.l1.go = "exit";    
            npchar.quest.HWICTalked = "true";
            pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter) + 1;
            AddQuestRecord("Holl_Gambit", "2-9");
            DelLandQuestMark(npchar);
            if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
            {
                AddQuestRecord("Holl_Gambit", "2-6");
                pchar.quest.GotoBridgetownOver.over = "yes";// 移除计时器
                DelMapQuestMarkCity("Bridgetown");
                pchar.questTemp.HWIC.Eng = "SeekVanBerg";
                pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
                pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
            }
        break;

        // 帆船赛
        case "Regata_check":
        iTest = FindColony(npchar.city); 
        if (iTest != -1)
        {
            rColony = GetColonyByIndex(iTest);
            sFrom_sea = rColony.from_sea;
        }
        ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)// 检查港口是否有船
        {
            bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
            pchar.quest.Regata_PU.over = "yes"; // mitrokosta 移除中断
            if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
            {
                dialog.text = "嗯... 你违反了帆船赛规则, 我必须取消你的资格。 抱歉。 你不能参加下一次航行。 我已经准备好发往罗亚尔港的急件了。 ";
                link.l1 = "唉... 真遗憾! 但我无能为力, 你太警觉了。 再会! ";
                link.l1.go = "exit";
                DeleteAttribute(pchar, "questTemp.Regata");
                AddQuestRecord("Regata", "45");
                CloseQuestHeader("Regata");
            }
            else
            {
                pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());// 玩家在1+2+3+4次转换中消耗的小时数
                dialog.text = "船长, 你可能注意到这座城市被围困了。 我们随时预计西班牙人会进攻, 正在动员兵力。 但帆船赛仍在继续\n让我们登记: " +GetFullName(pchar)+ "船长, 船是 - " + pchar.Ship.Name + "... 帆船赛用时为" + sti(pchar.questTemp.Regata.FourthTransitionTime) + "小时。 完成, 你的成绩已登记, 你可以继续前行了。 ";
                link.l1 = "告诉我我的排名。 ";
                link.l1.go = "Regata_info";
            }
        }
        else
        {
            dialog.text = "你在这里, 但我没看到你的船。 它在哪里? ";
            link.l1 = "抱歉, 先生。 我会立即把船转移到港口。 ";
            link.l1.go = "exit";
        }
        break;
        
        case "Regata_info":
            int n = 1;
            string sTemp, sName, sShip;
            for (int i = 1; i <= 5; i++)
            {
                if (i == 1) sTemp = "a";
                if (i == 2) sTemp = "b";
                if (i == 3) sTemp = "c";
                if (i == 4) sTemp = "d";
                if (i == 5) sTemp = "e";
                if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
                {
                    n++;
                    sName = pchar.questTemp.Regata.AdversaryName.(sTemp);// 最近对手的名字
                    sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);// 他的船
                }
            }
            if (n == 1)
            {
                dialog.text = "啊, 对... 抱歉我太忙了。 你是第一名。 ";
                link.l1 = "我知道了。 谢谢你的信息。 ";
                link.l1.go = "exit";
                AddQuestRecord("Regata", "22");
            }
            else
            {
                if (n == 6)
                {
                    dialog.text = "啊, 对... 抱歉我太忙了。 你是最后一名。 ";
                    link.l1 = "我知道了。 谢谢你的信息。 ";
                    link.l1.go = "exit";
                    AddQuestRecord("Regata", "27");
                }
                else
                {
                    if (n == 2)
                    {
                        dialog.text = "啊, 对... 抱歉我太忙了。 你是第二名。 只有一位船长超过了你。 他叫" + sName + ", 船是" + sShip + "。 ";
                        link.l1 = "我知道了。 谢谢你的信息。 ";
                        link.l1.go = "exit";
                        AddQuestRecord("Regata", "23");
                    }
                    else
                    {
                        dialog.text = "啊, 对... 抱歉我太忙了。 你的排名是第" + n + "。 你最近的对手是" + sName + ", 船是" + sShip + "。 ";
                        link.l1 = "我知道了。 谢谢你的信息。 ";
                        link.l1.go = "exit";
                        if (n == 3) AddQuestRecord("Regata", "24");
                        if (n == 4) AddQuestRecord("Regata", "25");
                        if (n == 5) AddQuestRecord("Regata", "26");
                    }
                }
            }
            AddCharacterExpToSkill(pchar, "Sailing", 50);// 航海
            AddCharacterExpToSkill(pchar, "Defence", 30);// 防御
            AddCharacterExpToSkill(pchar, "Repair", 30);// 修理
            AddCharacterExpToSkill(pchar, "Fortune", 30);// 幸运
            AddCharacterExpToSkill(pchar, "Sneak", 30);// 潜行
            npchar.quest.regatatalk = "true";
            pchar.questTemp.Regata.Bridgetown = "true";// 布里奇敦标记
            pchar.quest.Regata_Check1.win_condition.l1 = "location";
            pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
            pchar.quest.Regata_Check1.function = "RegataCheck";// 检查1
            pchar.quest.Regata_Check2.win_condition.l1 = "location";
            pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
            pchar.quest.Regata_Check2.function = "RegataCheck";// 检查2
            pchar.quest.Regata_Check3.win_condition.l1 = "location";
            pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
            pchar.quest.Regata_Check3.function = "RegataCheck";// 检查3
            pchar.quest.Regata_Check.win_condition.l1 = "location";
            pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
            pchar.quest.Regata_Check.function = "RegataCheck";// 检查4
            pchar.questTemp.Regata.AttackIsland = "Curacao";
            pchar.questTemp.Regata.AttackNation = HOLLAND;
            pchar.quest.Regata_Attack.win_condition.l1 = "location";
            pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
            pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
            pchar.quest.Regata_Attack1.win_condition.l1 = "location";
            pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
            pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";// 第三次埋伏
            pchar.quest.Regata_Hunter.win_condition.l1 = "location";
            pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
            pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";// 巴巴多斯的DU
            pchar.quest.Regata_Finish.win_condition.l1 = "location";
            pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
            pchar.quest.Regata_Finish.function = "RegataFinishSea";
            pchar.quest.Regata_Finish1.win_condition.l1 = "location";
            pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
            pchar.quest.Regata_Finish1.function = "RegataFinishTown";// 帆船赛结束
            // 情况
            pchar.quest.Regata_Siege.win_condition.l1 = "location";
            pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";// 关于疏散居民的任务
        break;
        // 帆船赛
        
        // 真理守卫
        case "guardoftruth":
            dialog.text = "是的, 这艘大帆船来过这里, 卸下货物后离开了我们港口。 关于它的目的地... 嗯... 没有, 什么都没有。 抱歉, 我无能为力。 ";
            link.l1 = "我知道了。 太糟了... 我会继续寻找它。 ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            DialogExit();
            AddQuestRecord("Guardoftruth", "13");
            pchar.questTemp.Guardoftruth = "barbados1";
        break;
        
        // 卡莱乌切
        case "caleuche":
            dialog.text = "先生, 我需要船的确切名字。 我们港口有很多叫杰克和杰克逊的人。 那么, 船名是什么? ";
            link.l1 = "";
            Link.l1.edit = 2;
            link.l1.go = "caleuche_name";
            link.l2 = "问题是我不知道他那破船的名字。 很奇怪, 有个鸟女, 出生... ";
            link.l2.go = "caleuche_1";
        break;
        
        case "caleuche_1":
            dialog.text = "先生, 去酒馆讲你的故事和谜语吧, 我们这里是正经场所。 要么告诉我那艘三桅小帆船的名字, 要么别打扰我工作。 ";
            link.l1 = "好吧, 我会设法查明。 ";
            link.l1.go = "exit";
            npchar.questTemp.caleuche = "true";
        break;
        
        case "caleuche_2":
            dialog.text = "那么? 你有船的名字吗? 我在听。 ";
            link.l1 = "";
            Link.l1.edit = 2;
            link.l1.go = "caleuche_name";
        break;
        
        case "caleuche_name":
            if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
            {
                dialog.text = "‘哈皮’? 当然, 我知道那艘三桅小帆船。 船长是雷金纳德.杰克逊。 但他很久没来布里奇敦了。 我听说他现在为荷兰西印度公司工作。 所以你应该去威廉斯塔德找他。 ";
                link.l1 = "非常感谢! 你帮了我大忙。 ";
                link.l1.go = "caleuche_3";
            }
            else
            {
                dialog.text = "抱歉, 这名字没印象。 你确定这位船长来过布里奇敦吗? ";
                link.l1 = "我确定。 好吧, 也许我会想到什么... ";
                link.l1.go = "exit";
            }
        break;
        
        case "caleuche_3":
            DialogExit();
            AddQuestRecord("Caleuche", "18");
            pchar.questTemp.Caleuche.Garpiya = "gwik"; 
            npchar.quest.garpiya = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}