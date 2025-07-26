// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想问什么? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "又是问题, " + GetAddress_Form(NPChar) + "... ", "问题, 问题... 我们做笔交易如何, " + GetAddress_Form(NPChar) + "? ",
                          "听着, 你打算聊多久? ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("现在没什么问题... ", "抱歉, 我现在没什么要说的... "), "再次抱歉... ",
                      "也许真的该做笔交易了... ", "对不起, 我们交易吧... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}