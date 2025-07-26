// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题要问士兵吗? ", "士兵的一生都已规划好 --守卫。 奔波... 我能为你做什么, " + GetAddress_Form(NPChar) + "? "), "你不该用愚蠢的问题打扰士兵, " + GetAddress_Form(NPChar) + "... ", "这是今天你第三次想向我提问了... ",
                          "士兵的命运不易, 而你这个家伙现在快把我逼疯了... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可谈的。 "), "知道了... ",
                      "是的, 你说得对, 已经第三次了... ", "抱歉... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//朗姆酒的价格
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "告诉我, 胡安这个名字有什么含义吗? ";
				link.l1.go = "Consumption";
			}
		break;
		
		//朗姆酒的价格
		case "Consumption":
			dialog.text = "不知道。 就这些吗? ";
			link.l1 = "是的。 抱歉打扰你了, 士兵... ";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部通过return退出, 别忘了执行卸载
}