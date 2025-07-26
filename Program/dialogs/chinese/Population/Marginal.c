// 杰森 街头小贩通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    
    // 调用城市相关对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // 调用城市相关对话 <--
    
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    
    switch(Dialog.CurrentNode)
    {
        case "First time":
            dialog.text = "你想要什么? ";
            link.l1 = "没什么。 ";
            link.l1.go = "exit";
            link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要些信息。 ");
            link.l2.go = "quests";//(转发到城市文件)
            
            if (npchar.quest.meeting == "0")
            {
                if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//劫持乘客
                {
                    dialog.text = "嘿, 船长! 对, 就是你。 过来, 我有笔交易想和你谈... ";
                    link.l1 = "什么交易? ";
                    link.l1.go = "passenger";
                    link.l2 = "我赶时间, 朋友。 或许下次吧。 ";
                    link.l2.go = "exit_quest";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); //移除对话标记
                    break;
                }
                dialog.text = LinkRandPhrase("嘿, 船长, 我其实正忙着呢。 你需要什么? ", "你想要什么, 船长? ", "船长, 我没心情聊天。 你想要什么? ");
                link.l1 = "问候你, " + GetAddress_FormToNPC(NPChar) + "。 等一下, 我想让你告诉我些事。 ";
                link.l1.go = "question";
                link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要些信息。 ");
                link.l2.go = "quests";//(转发到城市文件)
                link.l3 = "没什么, 我正要去酒馆... ";
                link.l3.go = "exit";
                npchar.quest.meeting = "1";
            }
            NextDiag.TempNode = "First time";
        break;

//----------------------------------------劫持乘客以获取赎金------------------------------------------
        case "passenger":
            DeleteAttribute(npchar, "talker");
            dialog.text = "嗯。 你是艘船的船长, 但看起来不像商人。 好像你口袋里有些硬币... 用一把达布隆换些有趣的信息怎么样? ";
            link.l1 = "首先, 证明你的信息值哪怕一个八里亚尔。 ";
            link.l1.go = "passenger_1";
        break;
        
        case "passenger_1":
            dialog.text = "当然值, 船长, 当然值。 它的价值比我要的多得多。 你给我金币, 我就告诉你某个非常重要的人何时会乘坐哪艘船航行。 你可以用很好的价格赎回这个人... 我甚至会告诉你买家的名字。 成交? ";
            link.l1 = "没门! 我不是绑匪。 滚开! ";
            link.l1.go = "exit_quest";
            link.l2 = "我怎么知道你说的是真话? ";
            link.l2.go = "passenger_2";
        break;
        
        case "passenger_2":
            pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
            dialog.text = "欺骗你是很不明智的, 水手。 我住在这个镇上, 不想惹麻烦。 只要" + sti(pchar.GenQuest.Marginpassenger.Dublon) + "个达布隆, 我就提供完整的信息。 你会赚得更多。 ";
            if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
            {
                link.l1 = "你说得有道理。 拿上金币, 开始说吧。 ";
                link.l1.go = "passenger_4";
            }
            link.l2 = "我现在身上没带够硬币。 ";
            link.l2.go = "passenger_3";
            link.l3 = "你在开玩笑吗? 为了空口承诺付真金? 滚开... ";
            link.l3.go = "exit_quest";
        break;
        
        case "passenger_3":
            dialog.text = "是吗? 好吧, 船长。 我可以多等几天, 这信息也可以等。 等你拿到金币再来找我。 找到我不难... 今天, 哈哈哈! ";
            link.l1 = "别那样龇牙咧嘴。 好吧, 我会把金币带来... 如果我没改变主意的话。 ";
            link.l1.go = "passenger_wait";
        break;
        
        case "passenger_wait":
            DialogExit();
            SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
            npchar.dialog.currentnode = "passenger_repeat";
        break;

        case "passenger_repeat":
            dialog.text = "你把我的金币带来了吗? ";
            if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
            {
                link.l1 = "是的。 拿着。 现在别想撒谎... ";
                link.l1.go = "passenger_4";
            }
            link.l2 = "还没。 也许以后... ";
            link.l2.go = "exit";
            Nextdiag.Tempnode = "passenger_repeat";
        break;
        
        case "passenger_4"://设置参数
            pchar.quest.Marginpassenger_Over.over = "yes"; //移除可能的计时器
            RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
            pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
            pchar.GenQuest.Marginpassenger.City = npchar.city;
            pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
            pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
            pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
            pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
            pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
            pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
            SelectMarginpassengerParameter();
            log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
            dialog.text = "保持火药干燥, 你很快就会需要它, 船长。 现在听着, 在" + FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)) + "后, 有一艘船将从我们的殖民地起航, 这艘船是" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))) + ", 名为‘" + pchar.GenQuest.Marginpassenger.ShipName + "’, 它将前往" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity + "Gen") + "。 船上会有一名乘客 - " + pchar.GenQuest.Marginpassenger.Text + ", 名叫" + pchar.GenQuest.Marginpassenger.q1Name + "\n船长" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Gen")) + "像所有商人一样是个胆小鬼, 哈哈哈! 也许你甚至可以避免任何战斗。 只要让他感到恐惧, 他就应该会自己交出目标, 嘿嘿\n如你所知, " + pchar.GenQuest.Marginpassenger.Text1 + ", 你可能会得到你的硬币, 是的, 但之后当地当局会追杀你到死。 你最好把你的猎物带到" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity) + "。 你会在那里找到一个名叫" + pchar.GenQuest.Marginpassenger.q2Name + "的人\n" + pchar.GenQuest.Marginpassenger.Text2 + ", 你甚至不需要说出你的名字。 这是你决定在哪里赎回你的人, 但不要贪多嚼不烂... 但你肯定可以要" + sti(pchar.GenQuest.Marginpassenger.Dublon) * 4 + "个达布隆。 明白了吗? ";
            link.l1 = "是的。 我要回到我的船上, 把它记在日志里。 ";
            link.l1.go = "passenger_5";
        break;
        
        case "passenger_5":
            dialog.text = "没错! 正确的选择。 好的, 船长, 祝你在这个简单的任务中好运。 哦, 对了, 我差点忘了: " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))) + "不会从港口起航, 而是从附近的一个海湾起航。 所以注意了。 祝你好运, 谢谢你的金币! ";
            link.l1 = "不客气。 别一夜之间就把它花光了。 ";
            link.l1.go = "exit_quest";
            npchar.lifeday = 0;
            ReOpenQuestHeader("Marginpassenger");
            AddQuestRecord("Marginpassenger", "1");
            AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City));
            AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity));
            AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
            AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
            AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
            AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
            AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Voc")));
            AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
            AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
            pchar.GenQuest.Marginpassenger = "begin";
            SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
        break;
        
        // 市民类型角色对出鞘武器的评价
        case "CitizenNotBlade":
            dialog.text = NPCharSexPhrase(NPChar, "听着伙计, 冷静下来, 把你的武器收起来。 ", "听着伙计, 冷静下来, 把你的武器收起来。 ");
            link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所愿。 ");
            link.l1.go = "exit";
        break;
        
        case "question":
            dialog.text = LinkRandPhrase("别拐弯抹角了, 船长。 说你想要什么! ", "哦, 好吧。 你想要什么? ", "问题? 好吧, 水手, 我在听。 ");
            link.l1 = LinkRandPhrase("你能告诉我最新的八卦吗? ", "最近这里发生了什么有趣的事吗? ", "加勒比海发生了什么事? ");
            link.l1.go = "rumours_marginal";
        break;
        
        case "exit_quest":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}

void SelectMarginpassengerParameter()
{
    if (hrand(1) == 0)
    {
        pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
        pchar.GenQuest.Marginpassenger.model = "women_" + (rand(5) + 11);
        pchar.GenQuest.Marginpassenger.sex = "woman";
        pchar.GenQuest.Marginpassenger.ani = "towngirl";
        pchar.GenQuest.Marginpassenger.Text2 = "他想娶她, 并会为这个女孩支付一笔可观的费用。 ";
        switch (hrand(4))
        {
            case 0:
                pchar.GenQuest.Marginpassenger.Text = "店主的女儿";
                pchar.GenQuest.Marginpassenger.Text1 = "从她的父亲, 店主那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
                break;
            case 1:
                pchar.GenQuest.Marginpassenger.Text = "造船厂师傅的女儿";
                pchar.GenQuest.Marginpassenger.Text1 = "从她的父亲, 造船厂师傅那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
                break;
            case 2:
                pchar.GenQuest.Marginpassenger.Text = "酒馆老板的女儿";
                pchar.GenQuest.Marginpassenger.Text1 = "从她的父亲, 酒馆老板那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
                break;
            case 3:
                pchar.GenQuest.Marginpassenger.Text = "银行家的女儿";
                pchar.GenQuest.Marginpassenger.Text1 = "从她的父亲, 银行家那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
                break;
            case 4:
                pchar.GenQuest.Marginpassenger.Text = "港务长的女儿";
                pchar.GenQuest.Marginpassenger.Text1 = "从她的父亲, 港务长那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
                break;
        }
    }
    else
    {
        pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
        pchar.GenQuest.Marginpassenger.model = "citiz_" + (rand(9) + 11);
        pchar.GenQuest.Marginpassenger.sex = "man";
        pchar.GenQuest.Marginpassenger.ani = "man";
        pchar.GenQuest.Marginpassenger.Text2 = "他一直计划讨好这个家庭, 并且会为囚犯支付很多钱";
        switch (hrand(4))
        {
            case 0:
                pchar.GenQuest.Marginpassenger.Text = "商人的亲戚, 船长";
                pchar.GenQuest.Marginpassenger.Text1 = "从他的亲戚, 船长那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
                break;
            case 1:
                pchar.GenQuest.Marginpassenger.Text = "造船厂师傅的亲戚";
                pchar.GenQuest.Marginpassenger.Text1 = "从他的亲戚, 造船厂师傅那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
                break;
            case 2:
                pchar.GenQuest.Marginpassenger.Text = "酒馆老板的亲戚";
                pchar.GenQuest.Marginpassenger.Text1 = "从他的亲戚, 酒馆老板那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
                break;
            case 3:
                pchar.GenQuest.Marginpassenger.Text = "银行家的亲戚";
                pchar.GenQuest.Marginpassenger.Text1 = "从他的亲戚, 银行家那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
                break;
            case 4:
                pchar.GenQuest.Marginpassenger.Text = "港务长的亲戚";
                pchar.GenQuest.Marginpassenger.Text1 = "从他的亲戚, 港务长那里";
                pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
                break;
        }
    }
    if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
    if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
    if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
    if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
    if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}