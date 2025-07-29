// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前刚问过我这个问题... ", "嗯, 让我猜猜... 又在兜圈子? ",
                          "听着, 我在这里管财务, 不回答问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记忆去哪了... ",
                      "你猜对了, 抱歉... ", "我明白... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 卡莱乌切
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "听着, 有没有一个叫约阿希姆.梅里曼的人来过这里? 一个中年先生, 葡萄牙人, 留着小胡子。 帝王须和锐利的眼睛? 也许他想贷款? ";
				link.l1.go = "caleuche";
			}
		break;
		
		// 卡莱乌切
		case "caleuche":
			dialog.text = "恐怕我帮不了你, 年轻人。 我完全不知道你在说谁。 ";
			link.l1 = "我知道了。 真遗憾。 我会继续寻找... ";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}