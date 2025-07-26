// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前刚问过我这个问题... ", "没错, 让我猜猜... 又在绕圈子了? ",
                          "听着, 我在这里管财务, 不回答问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性哪去了... ",
                      "你猜对了, 抱歉... ", "我明白了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// 巴拿马银行家对主角声望或剧情中洗劫卡塔赫纳的反应
		case "Panama_Deposit_NoReputation":
			dialog.text = "没错... 无论国籍如何, 受国王子民爱戴的荣誉之人永远不会被我的银行拒绝。 ";
			link.l1 = "我明白了。 再见。 ";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "但不幸的是, 我的女儿和岳父曾住在那里。 他们住在卡塔赫纳。 离开吧, " + GetAddress_Form(NPChar) + "。 这里不欢迎你。 ";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "原谅我。 再会。 ";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "你的损失。 再见。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "资金已被王室没收, 用于援助卡塔赫纳城遭洗劫的受害者。 我帮不了你。 在我叫卫兵之前, 请立即离开我的银行! ";
			link.l1 = "你会后悔的... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}