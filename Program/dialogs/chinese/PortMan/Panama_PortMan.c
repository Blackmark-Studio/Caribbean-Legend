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
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}