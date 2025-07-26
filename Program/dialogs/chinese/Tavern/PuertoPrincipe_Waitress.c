// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("有什么问题吗, " + GetAddress_Form(NPChar) + "? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "" + GetSexPhrase("嗯, 你有什么打算, " + GetAddress_Form(NPChar) + "? ", "又是这些奇怪的问题? 伙计, 去喝杯朗姆酒什么的吧... ") + "", "一整天下来, 这已经是你第三次问这类问题了... " + GetSexPhrase(" 这是在引起注意吗? ", ""),
                          "我猜你又有问题要问吧, " + GetAddress_Form(NPChar) + "? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了", "我现在没什么想聊的。 "), "不, 没什么要紧的... ",
                      "没门儿, 亲爱的... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            //--> 旧账
            if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
            {
                link.l1 = "我需要问你几个问题。 杜松子酒桶失踪那天, 你在酒馆工作, 对吧? 关于那天这里发生的事, 你能告诉我什么? ";
                link.l1.go = "OS_Tavern2_1";
            }
            //<—— 旧账
        break;

        //--> 旧账
        case "OS_Tavern2_1":
            dialog.text = "我... 我不知道该说什么。 一切都很正常, 没有什么异常。 ";
            link.l1 = "是吗? 没有什么奇怪的? 那个来自'海兽号'的水手骚扰你的事呢? 他似乎确信你会欢迎他陪你过夜。 ";
            link.l1.go = "OS_Tavern2_2";
            DelLandQuestMark(npchar);
        break;

        case "OS_Tavern2_2":
            dialog.text = "哦, 是他! 他... 他只是喝多了, 仅此而已。 你知道, 这种事在这里经常发生。 我当然没有鼓励他, 但他开始献殷勤。 所以我让他知道自己的身份。 ";
            link.l1 = "没有鼓励? 他说的可不是这样。 为什么这次你大吵大闹, 而其他时候却没有? ";
            link.l1.go = "OS_Tavern2_3";
        break;

        case "OS_Tavern2_3":
            dialog.text = "我... 我不知道还能告诉你什么! 我真的什么都不知道! 我... 我整个晚上都在显眼的地方! 什么都没看见, 什么都没听见! 关于那个桶... 我不了解它发生了什么! 为什么要审问我? 我只是... 只是像往常一样做我的工作! ";
            link.l1 = "我怀疑你在隐瞒什么。 在没有光线和食物的船舱里呆一晚, 对人的记忆力会有奇效。 想试试吗? 还是我们好好谈谈? ";
            link.l1.go = "OS_Tavern2_4_HO";
            link.l2 = "我相信你知道的远比你透露的要多。 你现在有一个难得的机会 --把一切都告诉我, 我会替你保守在这场小戏中的角色。 但如果你保持沉默 --对你来说会更糟。 不管有没有你的帮助, 我都会查明真相。 ";
            link.l2.go = "OS_Tavern2_4_harizma";
        break;

        case "OS_Tavern2_4_HO":
            dialog.text = "我... 我... 我会告诉你一切! 这都是我的... 追求者, 杰克。 杰克.维尔斯! 他说服我引诱'海兽号'上的任何一个水手。 当他献殷勤时, 我就要大吵大闹, 把酒馆老板从柜台后面引开。 当骚动开始平息时, 两个水手就会开始打架, 把他困在大厅里。 事情就是这样发生的。 在那段时间里,'海兽号'的船长设法偷走了酒桶。 这... 这就是我所知道的一切, " + GetSexPhrase("先生", "女士") + "! 请不要告发我! 我只是... 我只是... 我只是想让杰克终于能尊重我! 毕竟我帮了他... ";
            link.l1 = "你毫不犹豫地帮助了一个人, 却把另一个人推向了狼群! 尽管如此, 我还是会遵守诺言 --我不会揭露你在这件事里的角色。 但你必须为自己的所作所为负责! 你的愚蠢可能让客栈老板陷入了极大的危险。 我在哪里可以找到你的杰克? 记住: 对我撒谎, 我会回来的。 相信我, 你不会喜欢我的回访。 ";
            link.l1.go = "OS_Tavern2_5";
            AddComplexSelfExpToScill(40, 40, 40, 0);
            ChangeCharacterComplexReputation(pchar, "nobility", -3);
        break;

        case "OS_Tavern2_4_harizma":
            dialog.text = "我... 我... 我会告诉你一切! 这都是我的... 追求者, 杰克。 杰克.维尔斯! 他说服我引诱'海兽号'上的任何一个水手。 当他献殷勤时, 我就要大吵大闹, 把酒馆老板从柜台后面引开。 当骚动开始平息时, 两个水手就会开始打架, 把他困在大厅里。 事情就是这样发生的。 在那段时间里,'海兽号'的船长设法偷走了酒桶。 这... 这就是我所知道的一切, " + GetSexPhrase("先生", "女士") + "! 请不要告发我! 我只是... 我只是... 我只是想让杰克终于能尊重我! 毕竟我帮了他... ";
            link.l1 = "你毫不犹豫地帮助了一个人, 却把另一个人推向了狼群! 尽管如此, 我还是会遵守诺言 --我不会揭露你在这件事里的角色。 但你必须为自己的所作所为负责! 你的愚蠢可能让客栈老板陷入了极大的危险。 我在哪里可以找到你的杰克? 记住: 对我撒谎, 我会回来的。 相信我, 你不会喜欢我的回访。 ";
            link.l1.go = "OS_Tavern2_5";
            AddCharacterExpToSkill(pchar, "Leadership", 100);
        break;

        case "OS_Tavern2_5":
            dialog.text = "我没意识到事情这么严重! 毕竟只是一个桶... 杰克住在街对面。 他租了那里的房子, 我... 我知道的就这些! 请原谅我! 船长, 我发誓我再也不会做这样的事了! ";
            link.l1 = "回去做你的工作, 别再哭哭啼啼的 --酒馆老板不能怀疑任何事情。 ";
            link.l1.go = "OS_Tavern2_6";
        break;
        
        case "OS_Tavern2_6":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
            AddQuestRecord("OS", "4");
            
            //
            pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
            pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
            pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
            pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
            pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
            
            PChar.quest.OS_Zasada.win_condition.l1 = "item";
            PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
            PChar.quest.OS_Zasada.function = "OS_Zasada";
            
            SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
        break;
        //<-- 旧账
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}