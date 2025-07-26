// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想做什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
            
            // 雷贝比恩, "导航星"任务
            if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
            {
                link.l1 = "你不会刚好认识一个叫乔普.范德温克的人吧? ";
                link.l1.go = "PZ1";
            }
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
        
        case "PZ1":
            dialog.text = "嗯, 我个人不认识他, 但我时不时会在这里看到他。 你为什么问这个? ";
            link.l1 = "我被派去亲自给他送一个包裹。 但没人想谈论他, 我不知道为什么。 你知道吗? 他是个坏人吗? 我想听听你诚实的看法。 ";
            link.l1.go = "PZ2";
        break;
        
        case "PZ2":
            dialog.text = "再说一遍, 我们并不认识, 所以我几乎一无所知。 但他在镇上有个密友, 他们经常一起出现。 去找他吧 --他会决定是否告诉你更多信息。 他朋友的名字是罗伯.马滕。 ";
            link.l1 = "你说罗伯.马滕... 他是谁? 我在哪里可以找到他? ";
            link.l1.go = "PZ3";
        break;
        
        case "PZ3":
            dialog.text = "各个地方都有可能, 但现在他在我们的灯塔那里 --在一场可怕的风暴后修理他的大帆船。 那艘船叫'伏尔泰格'号。 ";
            link.l1 = "非常感谢你! 你都不知道你帮了我多大的忙。 ";
            link.l1.go = "Exit";
            AddDialogExitQuest("PZ_CreateRobertMartin");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}