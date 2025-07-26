// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想做什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
        break;
        
        case "info":
        // 替换为某些NPC的描述, 关于任务
            dialog.text = "你以为我是" + NationNameGenitive(sti(NPChar.nation)) + "的特工吗? ";
            link.l1 = "好吧... 不是。 那么再见。 ";
            link.l1.go = "exit";
            link.l2 = "那么, 还有其他问题吗? ";
            link.l2.go = "new question";
        break;
        
        case "town":
        // 替换为如何通行的描述, 关于任务
            dialog.text = "我看起来像调查局的人吗? 我不知道, 什么都不知道。 ";

            link.l1 = "你真是个糊涂虫! 走开。 ";
            link.l1.go = "exit";
            link.l2 = "那么, 还有其他问题吗? ";
            link.l2.go = "new question";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}