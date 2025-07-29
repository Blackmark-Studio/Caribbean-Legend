// 爱德华.曼斯菲尔德, 海盗首领及权威海盗, 英国任务线
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= 愤怒模块 ==========>>>>>>>>>>>>>>>>>>>>>>>>>
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
            switch (npchar.angry.kind) //此处配置愤怒反应, npchar.angry.name中无空格!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= 愤怒模块 ===================================
// ============================================================================
    switch(Dialog.CurrentNode)
    {
        case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
                if (NPChar.quest.meeting == "0")
                {
                    dialog.Text = TimeGreeting() + "! 我是" + GetFullName(NPChar) + ", 这个地方的新总督。 让当地暴徒安分守己并非易事, 但他们再也无法对西班牙殖民地构成威胁了。 ";
                    Link.l1 = "很高兴见到你。 我是" +GetFullName(pchar)+ "船长。 抱歉, 我得走了。 ";
                    Link.l1.go = "exit";
                    NPChar.quest.meeting = "1";
                }
                else
                {
                    dialog.Text = TimeGreeting() + "。 我很忙, 真的很忙, 我需要管制当地暴徒以防止西班牙殖民地受到任何威胁。 ";
                    Link.l1 = "那我不打扰你了。 ";
                    Link.l1.go = "exit";
                }
            }
            else
            {
                dialog.text = NPCStringReactionRepeat("你有什么要告诉我吗? 没有? 那" + GetSexPhrase("滚远点! ","请不要打扰我。 ") + "",
                             "我想我已经说清楚了... ", "尽管我已经说清楚了, 你还是在烦我! ",
                             "好吧, 你太过分了" + GetSexPhrase("太无礼了, 亲爱的","如此无礼, 姑娘","如此无礼, 姑娘") +"... ", "repeat", 30, npchar, Dialog.CurrentNode);
                link.l1 = HeroStringReactionRepeat("我这就走。 ",
                                               "是的, " + npchar.name+ ", 我明白。 ",
                                               "抱歉, " + npchar.name+ "... ",
                                               "哎哟... ", npchar, Dialog.CurrentNode);
                link.l1.go = "exit";
            }


                    if (npchar.city == sti(pchar.HeroParam.Location))
                    {
                        if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
                        {
                            link.l2 = "你有什么工作给我吗? ";
                            link.l2.go = "pirateStartQuest";
                        }
                        else
                        {
                            if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
                            {
                                link.l2 = "我找到了线索, 但需要些钱 —3万比索来把那老鼠引出洞。 ";
                                link.l2.go = "pirateStartQuest_many";    
                            }
                            if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
                            {
                                link.l2 = "看, 这是我在走私者尸体上找到的信";
                                link.l2.go = "pirateStartQuest_info_1";    
                            }
                            if(pchar.questTemp.pirateStartQuest == "5")
                            {
                                link.l2 = "搞定了。 诺曼.维戈和他的船都归海魔了。 ";
                                link.l2.go = "pirateStartQuest_final";    
                            }
                        }
                    }
        break;

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;
        
        //任务标题: 海盗初始任务 ===================================
        case "pirateStartQuest":
            dialog.text = "嗯.. 你说工作? 其实你问我正好。 我需要一个外人。 我想在最近的镇上打听点事, 但我的人在那里很出名。 不敢保证给你很多, 但你会得到些东西。 ";
            link.l1 = "什么任务? ";
            link.l1.go = "pirateStartQuest_1";
            link.l2 = "抱歉, 我不会为了一点小钱冒险。 再见。 ";
            link.l2.go = "exit";
            pchar.questTemp.pirateStartQuest = "0";
        break;
        case "pirateStartQuest_1":
            dialog.text = "那听着, 一个月前我和‘圣蓝号’纵帆船的船长达成了运送200名奴隶的协议, 想卖给当地种植园主。 时间过去了, 客户开始担心, 但昨天有人告诉我在岛附近看到了那艘纵帆船。 但是! 船长没出现。 今天客户要求我退还预付款, 还说有人给他介绍了另一个卖家的奴隶。 更贵, 但能一次性买到所有奴隶。 ";
            link.l1 = "然后呢? 我得在几天内找200个奴隶, 帮你保住预付款? 就为了一点钱? ";
            link.l1.go = "pirateStartQuest_2";
        break;
        case "pirateStartQuest_2":
            dialog.text = "当然不是。 我看起来像白痴吗? 反正我不会退预付款。 但我需要证明卖给他的那些奴隶是我的。 找到给他提供新交易的人, 你就能得到1万比索。 成交? ";
            link.l1 = "我接了。 你怀疑是谁吗? ";
            link.l1.go = "pirateStartQuest_3";
            link.l2 = "没可能。 找别人吧, 就给1万? 抱歉, 不行。 ";
            link.l2.go = "exit";
        break;
        case "pirateStartQuest_3":
            dialog.text = "我要是知道就不会用你了。 那些人早该死了。 但我很想知道他们怎么知道‘圣蓝号’的货物和我的客户的。 看来他们很容易就知道了。 明白了吗? ";
            link.l1 = "是的, 有人出卖了你。 ";
            link.l1.go = "pirateStartQuest_4";

            pchar.questTemp.pirateStartQuest = "1";
            pchar.questTemp.pirateStartQuest.City = npchar.city;
            pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
            pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

            AddQuestRecord("pSQ", "1");
            AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
            AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
        break;
        case "pirateStartQuest_4":
            dialog.text = "正是! 我在找他。 杀了我的竞争对手和夺回奴隶不是你的首要任务。 说实话, 我需要那只老鼠, 其实是要他的脑袋串在烤叉上。 现在明白为什么我的人不该知道你任务的事了吧? 在找到泄密者之前我会怀疑所有人。 而我真不想要那样... ";
            link.l1 = "明白了。 那我会低调行事。 这就出发。 ";
            link.l1.go = "exit";
        break;

        case "pirateStartQuest_many":
            dialog.text = "你说三万? 这可是一大笔钱... 我只能给你5000比索, 这是我现在所有的钱了。 别想拿钱跑路, 否则我会找到你, 把你吊死在最近的篱笆上! 懂了吗? ";
            link.l1 = "好吧, 那就给我五千... ";
            link.l1.go = "pirateStartQuest_many_1";
        break;
        case "pirateStartQuest_many_1":
            dialog.text = "拿去吧。 我等你调查结果。 ";
            link.l1 = "会搞定的。 ";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 5000);
            pchar.questTemp.pirateStartQuest.many = "";
        break;

        //------------------------------------
        case "pirateStartQuest_info_1":
            dialog.text = "哈! 好消息! 我就知道你能行。 我得到了一些有趣的情报。 ";
            link.l1 = "我完成了工作, 想要那一万比索。 ";
            link.l1.go = "pirateStartQuest_info_2";
            TakeItemFromCharacter(pchar, "letter_open");
        break;
        case "pirateStartQuest_info_2":
            dialog.text = "当然, 这是你的报酬。 但别跑, 我还有一个任务给你。 \n法伊弗是诺曼.维戈的纵帆船‘塞普蒂玛号’的船员。 我确定诺曼.维戈就是那只老鼠, 尽管他是我们的人。 最近有人在岛附近水域看到过他。 你的任务是把这只老鼠送给海魔。 你第一次没让我失望, 所以想请你也处理这件事。 我给你1万5千比索。 成交? ";
            link.l1 = "包在我身上! 就当叛徒已经死了。 ";
            link.l1.go = "pirateStartQuest_info_3";
            link.l2 = "知道吗, 我不想参与... 反正我也没时间。 抱歉, 我走了。 ";
            link.l2.go = "pirateStartQuest_info_noex";
            AddMoneyToCharacter(pchar, 10000);
        break;
        case "pirateStartQuest_info_noex":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            pchar.questTemp.pirateStartQuest = "0";
            CloseQuestHeader("pSQ");
        break;
        case "pirateStartQuest_info_3":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            pchar.questTemp.pirateStartQuest = "4";

            AddQuestRecord("pSQ", "7");
            AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

            pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
            pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
            pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
        break;

        case "pirateStartQuest_final":
            dialog.text = "我知道, 我知道。 我的人一直在观看战斗, 已经向我报告了你完美的胜利。 很好, 你干得不错。 这是1万5千比索, 如我所承诺的。 谢谢你, 帮了我大忙。 ";
            link.l1 = "不客气, 我很乐意帮忙! 但现在我得走了, 在这里待太久了, 还有很多事要做。 再见! ";
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 15000);
            pchar.questTemp.pirateStartQuest = "0";
            CloseQuestHeader("pSQ");
            group_DeleteGroup("pirateStartQuest_Smuggler_group");
        break;
                
        case "No_Mansfield_first_time":
            dialog.text = "你好, 我叫阿利斯泰尔.古德。 曼斯菲尔德死后我被选为海盗首领。 ";
            link.l1 = "很高兴见到你, 阿利斯泰尔。 ";
            link.l1.go = "exit";
            NextDiag.TempNode = "No_Mansfield";
        break;
        case "No_Mansfield":
            dialog.text = "我没时间和你说话。 以后再来。 ";
            link.l1 = "我这就走。 ";
            link.l1.go = "exit";
        break;
        

// ======================== 愤怒节点模块 ===============>>>>>>>>>>>>>>>
        case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("滚","滚") +"出去! ", "从我家滚出去! ");
            link.l1 = "哎哟... ";
            link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //30天后与曼斯菲尔德和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
                    dialog.text = "别烦我, 记住。 ";
                    link.l1 = "知道了。 ";
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
        break;
// <<<<<<<<<<<<============= 愤怒节点模块 =============================
    }
}