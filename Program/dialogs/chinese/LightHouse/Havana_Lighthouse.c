// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? ", "你想了解什么? "), "你需要什么, " + GetAddress_Form(NPChar) + "? ", "这是你第三次想问我了... ", "我受够你了, 滚开! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("抱歉, 我改变主意了。 ", "没什么, 抱歉。 "), "我忘了, 抱歉... ",
                      "事不过三, 对吧? 打扰了... ", "抱歉抱歉! 那我先告辞了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 卡勒幽船
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "听着 --有没有一个叫约阿希姆.梅里曼的人来过这里? 他是个中年葡萄牙先生, 留着小胡子。 帝王须和一双锐利的眼睛。 也许他在某个海湾或灯塔附近上岸了? 你见过这样的人吗? ";
				link.l1.go = "merriman";
			}
		break;
		
		// 卡勒幽船
		case "merriman":
			dialog.text = "没见过, 伙计, 我没见过像他这样的人。 我肯定会注意到的, 是的。 ";
			link.l1 = "我知道了, 真遗憾。 感谢你的时间, 我会继续寻找。 ";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}