// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "不久前你在我店里时就想向我提问... ", "这已经是今天第三个问题了。 我得做生意, 不是来进行无意义的对话... ",
                          "又要问问题? 不如我们做笔交易如何? ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "是的, 没错。 我之前试过... 在店里的时候... ",
                      "对, 这是第三个问题了... ", "嗯, 或许我们可以做笔交易... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}