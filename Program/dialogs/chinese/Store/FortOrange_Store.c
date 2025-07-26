// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题吗? ", "我能帮你什么忙? "), "你不久前在店里的时候就想问我问题... ", "这已经是今天的第三个问题了。 我得做生意, 没功夫聊些没用的... ",
                          "还有问题? 不如我们做笔交易如何? ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "是的, 没错。 我之前试过... 在店里的时候... ",
                      "是的, 这是第三个问题了... ", "嗯, 也许我们可以做笔交易... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;				
	}
	UnloadSegment(NPChar.FileDialog2);
}