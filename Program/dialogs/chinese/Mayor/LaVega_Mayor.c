// 拉维加的马库斯.蒂拉克斯副官
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sLoc;

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
            switch (npchar.angry.kind) //此处配置愤怒反应, npchar.angry.name中无空格!!!
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
        // ---------------------------------—— 首次对话 - 初次见面
        case "First time":
            dialog.text = NPCStringReactionRepeat("你有什么要告诉我吗? 没有? 那就离我远点! ",
                         "我想我已经说清楚了, 别再烦我。 ", "尽管我已经说清楚了, 你还是在烦我! ",
                         "对, 我受够这种无礼了。 ", "repeat", 3, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("我这就走。 ",
                                               "当然"+npchar.name+"... ",
                                               "抱歉, "+npchar.name+"... ",
                                               "哎哟... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "First time";
        break;

        case "Exit":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
        break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", 很高兴见到你! 你有什么愿望? ",
                         "还有什么事? ", "又是你? 没事就别烦别人! ",
                         "我知道你是个正派的人。 但我不想再和你说话了。 ", "repeat", 10, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("没什么。 只是想见见你。 ",
                                               "没什么... ",
                                               "好吧, "+npchar.name+", 抱歉... ",
                                               "该死, 这全是我的错... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            NextDiag.TempNode = "I_know_you_good";
        break;

        // ============== 光天化日之下的抢劫, 试图撬箱子 =========================
        case "Man_FackYou":
            dialog.text = LinkRandPhrase("小偷!!! 你认真的吗? ! 你完了, 伙计... ", "等等, 到底怎么回事? 原来你是个小偷! 你完了... ");
            link.l1 = LinkRandPhrase("Shit!", "Carramba!!", "Damn it!!");
            link.l1.go = "PL_Q3_fight";
        break;
                    
        // ======================== 愤怒节点模块 ===============>>>>>>>>>>>>>>>
        case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("走开","离开 ") +"这里! ", "滚出我的家! ");
            link.l1 = "Oups... ";
            link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
                    dialog.text = "别再用你廉价的谈话烦我。 下次你不会喜欢结果的... ";
                    link.l1 = "我明白了。 ";
                    link.l1.go = NextDiag.TempNode;
                    CharacterDelAngry(npchar);
                }
            }
        break;
        case "AngryRepeat_2":
            dialog.text = "结束了, 别说话。 ";
            link.l1 = RandPhraseSimple("如你所愿... ", "那好吧... ");
            link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //10天后和解
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
                    dialog.text = "我希望你能对我更尊重些, 别再无礼了? 否则我就得杀了你。 那会非常不愉快。 ";
                    link.l1 = ""+npchar.name+", 你放心, 我会的。 ";
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
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
        break;
        // <<<<<<<<<<<<============= 愤怒节点模块 =============================
        
        // Rebbebion, 任务'导航星'
        case "PZ1":
            dialog.text = "啊, 是你, 德.莫尔。 嗯, 真让人惊讶。 看在海魔的份上, 你的到来是很长时间以来最有趣的事情了, 该死。 ";
            link.l1 = "见到你也很高兴, 文桑。 统治这个村庄很享受吗? ";
            link.l1.go = "PZ2";
            DelLandQuestMark(npchar);
        break;
        
        case "PZ2":
            dialog.text = "我怎么会享受? 我是个船长, 而且是个该死的好船长, 不是什么该死的会计。 我等马库斯的信使召唤我去新的航程比等圣诞节的时间还长, 该死的诅咒! ";
            link.l1 = "一句话里既有圣诞节又有诅咒, 这可真是新鲜。 是啊, 我不同情你。 不过, 很多人都想处于你现在的位置。 但我是来找你谈正事的, 文桑。 ";
            link.l1.go = "PZ3";
        break;
        
        case "PZ3":
            dialog.text = "正事? ! 好吧, 快说 --你想出什么了? 有什么好线索吗? 我都快无聊到把当地地窖喝干了, 还有这些该死的计算。 ";
            link.l1 = "嗯, 其实我只是有个问题要问你, 没别的。 ";
            link.l1.go = "PZ4";
        break;
        
        case "PZ4":
            dialog.text = "该死! 但好吧, 我听着呢, 查尔斯。 ";
            link.l1 = "有没有一个女人来看过你? 或者你在拉维加见过她? 她叫贝儿.埃托伊尔, 不过那只是个化名, 所以她可能用别的名字介绍自己。 重要的是她... 她皮肤是黄色的。 但不是奴隶或劳工 --她是个富有的女人。 ";
            link.l1.go = "PZ5";
        break;
        
        case "PZ5":
            dialog.text = "黄皮肤但很富有? 我们这里从来没有过这样的人, 从来没有! 看来你还过着那种有趣的生活, 德.莫尔! 我都有点嫉妒了。 ";
            link.l1 = "是这样啊... 好吧, 谢谢你的时间, 文桑。 我不再打扰你记账了, 呵呵。 ";
            link.l1.go = "Exit";
            
            AddQuestRecord("PZ", "40");
            
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