// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为你效劳。 你想了解什么? ",
                          "我们刚刚还在谈论这个。 你一定是忘了... ", "这是你今天第三次问这类问题了... ",
                          "你像鹦鹉一样重复同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道的, " + Npchar.name+ ", 也许下次吧。 ", "对, 不知怎么就忘了... ",
                      "是的, 真的是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了进行卸载
}