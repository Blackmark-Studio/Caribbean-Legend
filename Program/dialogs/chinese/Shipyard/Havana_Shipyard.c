// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题吗? ", "我能帮你什么忙? "), "你刚才已经问过我问题了... ", "在我的造船厂或是这个镇上的任何地方, 我从未见过如此好奇的人。 ",
                          "问这么多问题干什么? 我的工作是造船。 我们还是专注于此吧。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么好说的。 "), "嗯, 我的记性去哪儿了... ",
                      "嗯, 好吧... ", "继续... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 幽灵船任务
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "听着, 最近有没有一个叫若阿金.梅里曼的人来过这里? 一位中年绅士, 葡萄牙人, 留着小胡子。 络腮胡, 眼神犀利? 也许他想买艘船? ";
				link.l1.go = "caleuche";
			}
		break;
		
		// 幽灵船任务
		case "caleuche":
			dialog.text = "没有, 先生。 没见过这样的客户。 ";
			link.l1 = "我明白了。 真遗憾。 那我继续找找看... ";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某个地方通过return退出, 别忘了进行卸载
}