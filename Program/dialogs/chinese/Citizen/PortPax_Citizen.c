// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想做什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
            {
                link.l1 = "告诉我, " + GetAddress_FormToNPC(NPChar) + ", 不久前'圣玛格丽塔'号大帆船是不是来过这里? 可能是作为私掠船的战利品? ";
                link.l1.go = "guardoftruth";
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
        
        case "guardoftruth":
            dialog.text = LinkRandPhrase("不, 我不记得有任何叫这个名字的大帆船。 我们这里很少见到那么大的船。 ", "什么? 大帆船? 在这里? 我不知道。 ", "没有, 先生, 那艘船最近没在这里停泊过, 至少我不记得有这回事。 ");
            link.l1 = LinkRandPhrase("好吧... ", "很好... ", "我知道了, 真遗憾... ");
            link.l1.go = "exit";
            npchar.quest.Guardoftruth = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}