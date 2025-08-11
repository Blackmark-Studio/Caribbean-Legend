// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想做什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次想问了... ", "这是你第三次想问了... ",
                          "这要到什么时候才结束? ! 我忙着处理殖民地事务, 你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不行。 地点和时间不对"), "确实... 但过会儿吧, 不是现在... ",
                      "我会问的... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // Jason 比黄金更珍贵
            if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
            {
                link.l1 = "大人, 我想告诉您, 我掌握一些关于‘墨丘利号’失踪的信息。 ";
                link.l1.go = "G_Girl";
            }
        break;
        
        // Jason 比黄金更珍贵
        case "G_Girl":
            dialog.text = "信息? 又关于什么? ";
            link.l1 = "那艘双桅帆船, 大人。 运送邮件的那艘。 装着重要文件之类的。 我听说了调查的事, 显然, 作为英国王室的忠实朋友, 我想帮忙。 ";
            link.l1.go = "G_Girl_1";
        break;
        
        case "G_Girl_1":
            dialog.text = "太好了! 科特尼准男爵会很高兴接见你! 我马上安排会面。 ";
            link.l1 = "谢谢您, 先生。 我时间紧迫, 如果能快点就太好了。 ";
            link.l1.go = "G_Girl_2";
        break;
        
        case "G_Girl_2":
            dialog.text = "别担心, 你有的是时间。 卫兵! 抓住他! ";
            link.l1 = "谢谢... 等等, 什么? 这是在开玩笑吗? ! ";
            link.l1.go = "G_Girl_3";
        break;
        
        case "G_Girl_3":
            DialogExit();
            GoldenGirl_AntiguaArest();
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了在此处卸载
}