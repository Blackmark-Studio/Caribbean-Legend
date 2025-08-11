// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("说吧, 你想要什么? ",
                          "我们刚聊过这个。 你肯定是忘了... ", "这已经是今天你第三次问这类问题了... ",
                          "听着, 这是商店。 人们来这儿买东西。 别打扰我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么就忘了... ",
                      "是啊, 真的是第三次了... ", "嗯, 我不会了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 卡莱乌切
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "听着, 有没有一个叫约阿希姆.梅里曼的人来过你的商店? 一位中年先生, 葡萄牙人, 留着小胡子。 帝王须和锐利的眼睛? 也许买过什么东西? ";
				link.l1.go = "caleuche";
			}
		break;
		
		// 卡莱乌切
		case "caleuche":
			dialog.text = "不, 我的顾客里没有像你描述的那样的人。 而且, 我以前从未听过这个名字。 抱歉, 我帮不了你更多了。 ";
			link.l1 = "我明白了。 真遗憾。 好吧, 我会继续我的搜索... ";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}