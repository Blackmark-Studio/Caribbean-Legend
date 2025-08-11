// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想做什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
            //加斯科涅人的负担
            if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
            {
                link.l1 = "打扰了, " + GetAddress_FormToNPC(NPChar) + ", 你能告诉我在哪里可以找到米歇尔.德.蒙佩尔吗? 我听说他在这个镇上。 ";
                link.l1.go = "Sharlie";
            }
            if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
            {
                link.l1 = "听着, " + GetAddress_FormToNPC(NPChar) + ", 我想问你一件事... 我在找一名领航员在我的船上任职, 你认识这样的人吗? ";
                link.l1.go = "Sharlie_1";
            }
            //加斯科涅人的负担
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
        
        //--> 加斯科涅人的负担
        case "Sharlie":
            if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
            {
                dialog.text = "嗯... 我猜你是刚到这里, 居然敢无所顾忌地问这种问题... 如果你不想惹麻烦, 我劝你收手。 去和修道院院长谈谈, 他或许能帮你'清醒清醒'。 你可以在教堂找到他。 ";
                link.l1 = "我知道了... ";
                link.l1.go = "exit";
                AddDialogExitQuest("Sharlie_SetBenua");
                DelLandQuestMark(characterFromId("FortFrance_Mayor"));
            }
            else
            {
                dialog.text = LinkRandPhrase("不, 我没听说过他。 ", "我帮不了你, 我有工作要做。 ", "谁? 没印象, 不认识。 我得走了。 ");
                link.l1 = "我知道了... 那我先走了。 ";
                link.l1.go = "exit";
                npchar.quest.Sharlie = "true";
            }
        break;
        
        case "Sharlie_1":
            dialog.text = LinkRandPhrase("不, 我不认识任何领航员。 ", "我有工作要处理, 不认识, 去问别人吧... ", "很遗憾, 我帮不了你, 我不认识这样的人。 ");
            link.l1 = "我知道了。 那我去别处问问。 ";
            link.l1.go = "exit";
            npchar.quest.Sharlie1 = "true";
            npchar.dialog.currentnode = "first time";
        break;
        //<-- 加斯科涅人的负担
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}