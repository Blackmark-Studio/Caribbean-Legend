// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "现在不行。 地点和时间不对。 "), "是的, 我现在没什么要说的, 抱歉。 ",
                      "我稍后再问。 ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // 葡萄牙人
            if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
            {
                link.l1 = "我知道荷兰西印度公司悬赏捉拿一名叫‘葡萄牙人巴托洛梅奥’的海盗。 我已经将他抓获。 他现在在我的货舱里, 我准备将他移交给当局。 ";
                link.l1.go = "Portugeze";
            }
        break;

        case "Cupture_after":
            dialog.text = RandPhraseSimple("你已经拿走了所有东西。 还想要什么? ", "还有什么是你没拿的吗? ");
            link.l1 = RandPhraseSimple("只是随便看看... ", "只是检查一下, 可能忘了拿什么... ");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
        break;
        
        // 葡萄牙人
        case "Portugeze":
            dialog.text = "‘葡萄牙人巴特’? ! 你抓住他了, 还活着? ! ";
            link.l1 = "我知道他死了对你没什么用。 他还活着, 天杀的, 我费了好大劲才没杀了他! ";
            link.l1.go = "Portugeze_1";
        break;
        
        case "Portugeze_1":
            dialog.text = "太好了! 现在他会把一切都告诉我们... 先生, 请准备好移交囚犯。 我们马上派一艘军用小艇到你的船上。 ";
            link.l1 = "如果您不介意的话, 先生, 我想先谈谈我的奖赏。 ";
            link.l1.go = "Portugeze_2";
        break;
        
        case "Portugeze_2":
            dialog.text = "别担心你的奖赏, 先生。 你会得到的。 我们为‘葡萄牙人巴托洛梅奥’的脑袋悬赏了一千五百达布隆。 中尉! 把奖赏给船长拿来! ";
            link.l1 = "嗯... 雨果告诉我是两千达布隆... 算了。 ";
            link.l1.go = "Portugeze_3";
        break;
        
        case "Portugeze_3":
            TakeNItems(pchar, "gold_dublon", 1500);
            Log_Info("你获得了1500达布隆");
            PlaySound("interface\important_item.wav");
            dialog.text = "现在, 先生, 您能否好心地把这个葡萄牙人移交给公司? 我们很想和他谈谈。 ";
            link.l1 = "当然, 先生, 请派小艇到我的船上来。 ";
            link.l1.go = "Portugeze_4";
        break;
        
        case "Portugeze_4":
            DialogExit();
            DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
            DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}