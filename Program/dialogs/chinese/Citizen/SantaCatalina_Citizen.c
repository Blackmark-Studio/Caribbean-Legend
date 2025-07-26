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
            dialog.text = LinkRandPhrase("你对谁感兴趣? ", "你指的是谁? ", "那么, 是谁呢? ");
            if (CheckAttribute(pchar, "questTemp.Saga"))
            {
                link.l1 = "我想了解更多关于扬.斯文森的事。 ";
                link.l1.go = "svenson";
            }
            link.l2 = "我们换个话题吧... ";
            link.l2.go = "new question";
        break;
        
        case "town":
            dialog.text = LinkRandPhrase("你想去哪里? ", "你在找什么? ", "你具体需要什么? ");
            if (CheckAttribute(pchar, "questTemp.Saga"))
            {
                link.l1 = "扬.斯文森的家在哪里? ";
                link.l1.go = "svenson_house";
            }
            link.l2 = "我们换个话题吧... ";
            link.l2.go = "new question";
        break;
        
        case "svenson":
            dialog.text = RandPhraseSimple("哦, 我们的扬.斯文森是个非常重要的人物。 过去他是西印度群岛最潇洒的海盗, 即使现在他也没衰老, 哈! 但那些日子已经过去了, 他不像以前那样活跃了。 他拥有一座豪宅, 和他年轻的妻子住在那里, 他总是总督府的贵客。 很多客人来找扬, 大多是海盗。 ", "扬.斯文森是西印度群岛的传奇人物! 当他把西班牙人从这里赶走时, 他们称他为'森林魔鬼'。 他曾是著名的私掠船船长, 但现在是我们殖民地受人尊敬的公民。 尽管他仍在做一些'生意', 但不再亲自下手了。 自从娶了一位年轻美女后, 他很少离开家。 ");
            link.l1 = "谢谢。 ";
            link.l1.go = "exit";
        break;
        
        case "svenson_house":
            dialog.text = RandPhraseSimple("从码头直走直到看到广场, 喷泉附近右边的房子就是斯文森的豪宅。 ", "从总督府穿过广场到码头, 喷泉附近左边的房子就是斯文森的豪宅。 ");
            link.l1 = "谢谢。 ";
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}