// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("有问题吗, " + GetAddress_Form(NPChar) + "? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "" + GetSexPhrase("嗯, 你打什么主意, " + GetAddress_Form(NPChar) + "? ", "又来问奇怪的问题? 伙计, 去喝点朗姆酒什么的吧... ") + "", "一整天里, 这已经是你第三次问这类问题了... " + GetSexPhrase(" 这是在引起注意吗? ", ""),
                          "我猜你又有问题要问吧, " + GetAddress_Form(NPChar) + "? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了", "我现在没什么想聊的。 "), "不, 没什么要紧的... ",
                      "没门儿, 亲爱的... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;

        case "helendrinking":
            dialog.text = "先生, 您睡得怎么样? 麦克阿瑟小姐吩咐我们要确保您完全舒适! ";
            link.l1 = "我做了个非常奇怪的梦... ";
            link.l1.go = "helendrinking_1";
        break;

        case "helendrinking_1":
            dialog.text = "啊! ... ";
            link.l1 = "怎么了, 小姐? 我能为你做什么吗? ";
            link.l1.go = "helendrinking_2";
        break;

        case "helendrinking_2":
            dialog.text = "抱歉, 船长... 这是罪过, 但我忍不住! 我不太有经验, 但别拒绝这个女孩, 船长! 您太英俊了! 我想取悦您, 想触摸... ";
            link.l1 = "确实要完全舒适... 你也很美! 来吧, 别害羞。 ";
            link.l1.go = "helendrinking_sex";
            link.l2 = "小姐, 现在最好别碰我 --我浑身都是朗姆酒味。 但你可以取悦我 --要是有早餐就太好了! ";
            link.l2.go = "helendrinking_nosex";
        break;
        
        case "helendrinking_sex":
            dialog.text = "哦天哪, 哦天哪! ";
            link.l1 = "";
            link.l1.go = "exit";
            
            NextDiag.TempNode = "exit";
            
            pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
            notification("海伦不赞成", "海伦娜");
            AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
        break;

        case "helendrinking_nosex":
            dialog.text = "真无礼! ";
            link.l1 = "那没有早餐吗? ";
            link.l1.go = "exit";
            
            NextDiag.TempNode = "exit";
            
            pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
            notification("海伦赞成", "海伦娜");
            AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}