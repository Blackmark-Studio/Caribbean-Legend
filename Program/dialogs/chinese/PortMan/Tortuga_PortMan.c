// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "日安。 我在找弗朗索瓦.贡捷。 他的护卫舰‘" + pchar.questTemp.Slavetrader.ShipName + "’应该在你们港口停靠过。 ";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("嗯... 我得让你失望了。 护卫舰‘" + pchar.questTemp.Slavetrader.ShipName + "’从未到过这里, 弗朗索瓦.贡捷也没在这里登记过。 ", "你已经问过这个问题了, 我也回答过了。 ", "我告诉过你, 你已经问过关于贡捷的事了。 ", "请别打扰我工作! ", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("谢谢。 我会继续寻找。 ", "嗯, 好吧... ", "是的, 我确实问过... ", "抱歉, " + npchar.name+ "... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}