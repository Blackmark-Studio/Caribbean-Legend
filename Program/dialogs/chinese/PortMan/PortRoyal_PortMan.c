// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用你的问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "日安。 弗朗索瓦.贡捷船长在这里登记过吗? 他驾驶一艘名为‘" + pchar.questTemp.Slavetrader.ShipName + "’的护卫舰从贝略港驶来。 ";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("不, 他没有。 而且‘" + pchar.questTemp.Slavetrader.ShipName + "’号护卫舰也没在罗亚尔港出现过。 ", "你已经问过这个问题了, 我也回答过了。 ", "我告诉你, 你已经问过这个叫贡捷的家伙了。 ", "请不要打扰我工作! ", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("谢谢。 我会继续寻找。 ", "嗯, 好吧... ", "是的, 我确实问过... ", "抱歉, " + npchar.name+ "... ", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}