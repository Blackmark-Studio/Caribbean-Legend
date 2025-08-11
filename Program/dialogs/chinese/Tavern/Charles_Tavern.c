// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "你不久前刚问过我问题, " + GetAddress_Form(NPChar) + "... ", "一整天下来, 这已经是你第三次问这类问题了... ",
                          "我猜你又有问题要问? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么想聊的。 "), "嗯, 我的记性哪去了... ",
                      "是的, 确实是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // 传奇任务
            if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
            {
                link.l1 = "我在找一个绰号叫‘侍从’的人。 你认识他吗? ";
                link.l1.go = "valet_1";
                link.l2 = "我在找一艘名为‘马林鱼号’的三桅帆船船长。 你能告诉我去哪里找他吗? ";
                link.l2.go = "valet_2";
            }
        break;
        
        case "valet_1":
            dialog.text = NPCStringReactionRepeat("不, 我不认识, 伙计。 所以我帮不了你。 ", "我已经告诉过你我不认识! ", "你是喝醉了还是在胡闹? ", "别烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("明白了。 真遗憾... ", "太可惜了。 我还以为你会记得... ", "我没醉! 我只是坚持不懈... ", "嗯... ", npchar, Dialog.CurrentNode); 
            link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
        break;
        
        case "valet_2":
            dialog.text = NPCStringReactionRepeat("啊, 大卫.法克曼先生! 他在造船厂附近租了一间房子。 去那里找他吧。 ", "我刚回答过你。 你怎么听的? ", "你是喝醉了还是在胡闹? ", "别烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("谢谢你! ", "好的。 对不起。 ", "我没醉! 我只是坚持不懈... ", "嗯... ", npchar, Dialog.CurrentNode); 
            link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}