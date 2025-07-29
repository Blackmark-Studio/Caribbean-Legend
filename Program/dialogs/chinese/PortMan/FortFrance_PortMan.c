// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用你的问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> 加斯科涅人的负担
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "先生, 我在找工作。 但不是搬运工的工作, 而是更符合我身份的任务。 使命。 服务, 需要谨慎处理的事务... 我会接受你提供的任何任务。 ";
			link.l1.go = "Sharlie";
		}
		//< —加斯科涅人的负担
		
		// 杰森'长久而幸福'
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "有人告诉我你有一封给我的信。 我叫查尔斯.德.莫尔船长。 ";
			link.l1.go = "LH_letter";
		}
		break;
		
		case "Sharlie":
			dialog.text = "帮忙? 嗯。 我还好, 感谢上帝。 但我的一个朋友真的急需帮助, 而且很紧急。 他打算独自进入丛林与印第安人战斗, 这简直是疯了! \n我试图说服他, 求他, 但他不听! 他太担心女儿了, 准备为她献出生命! ";
			link.l1 = "等等, 我们重新开始: 你的朋友是谁, 我在哪里可以找到他, 他需要什么样的帮助? ";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "啊, 请原谅, 我只是太焦虑了。 他叫普罗斯珀... 普罗斯珀.特鲁巴勒。 他肯定会死的! 我帮不了他 —我不是士兵。 他的女儿失踪了, 他认为是当地印第安人干的\n你能想象吗, 他打算独自去追捕那些野蛮的野人! 他们会把他切成碎片... 此刻他正在买火枪, 准备进入丛林! ";
			link.l1 = "你讲故事的能力真差, 先生。 我在哪里可以找到你的朋友... 他叫什么来着... 普罗斯珀? ";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "我刚和他谈过, 试图让他改变主意。 他就在城门口附近, 在井边, 检查他的火枪和弹药。 去找他, 做点什么! 如果他一个人进丛林, 肯定回不来, 我敢肯定。 那些红皮肤的恶魔会把他撕碎的... ";
			link.l1 = "别胡扯了, 你说话像个老妇人! 我马上就去找你的朋友。 希望我能帮上他。 ";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// 杰森'长久而幸福'
		case "LH_letter":
			dialog.text = "是的, 你说得对 —有一个信封。 给你, 但首先你需要支付投递费 —一万两千银比索。 ";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "我一直怀疑你的生意本质上是小偷行当, 但不知怎么的我错过了邮件, 嗯。 给你钱。 ";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "我过会儿再来, 我想我把钱包忘在酒馆了。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}