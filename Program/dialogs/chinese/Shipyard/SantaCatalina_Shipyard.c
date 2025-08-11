// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题吗? ", "我能帮你什么忙? "), "你刚才已经问过我问题了... ", "在我的造船厂或是这个镇上的任何地方, 我从未见过如此好奇的人。 ",
                          "问这么多问题干什么? 我的工作是造船。 我们还是专注于此吧。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么好说的。 "), "嗯, 我的记性去哪儿了... ",
                      "嗯, 好吧... ", "继续... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... 先生, 这是个不错的选择。 那么, 成交吗? ";
			link.l1 = "当-当然! 干杯! 把它包好送到码头。 快点, 有位女士在街上等我! ";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "先生, 全部一共五万银币。 ";
			if (sti(pchar.money) >= 55000) {
				link.l1 = "你-你说多少? 五-五万? 好吧, 你自己数! 再拿五千当小费。 我们走! ";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "不-不, 我也许是个有钱人, 嗝! ... 但我不会花那么多钱买它。 不, 先生! 再见, 船夫。 ";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "谢谢您, 先生。 愿它为您好好效力! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "行吧, 滚吧, 有钱人。 我们三小时前就打烊了。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某个地方通过return退出, 别忘了进行卸载
}