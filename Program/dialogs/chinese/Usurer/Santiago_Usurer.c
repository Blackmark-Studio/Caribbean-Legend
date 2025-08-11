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
			//荷兰策略, 荷兰
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "先生, 我是" +GetFullName(pchar)+ "船长, 受卢卡斯.罗登堡的委托前来。 我有一个他给您的包裹。 ";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "我来取卢卡斯.罗登堡先生的回信。 ";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//荷兰策略, 荷兰
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "想想看... 一个包裹! 好吧, 给我吧, 先生。 ";
			link.l1 = "另外, 罗登堡先生让我转交给您这个... ";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "据我所知, 除了包裹之外, 我还应该收到别的东西, 船长。 那么... 它在哪里? 你明白我在说什么吗? ";
			link.l1 = "当然! 箱子在我的船上妥善保管着。 我会立即给您送来。 ";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "嗯... 有意思。 所以他'表示歉意'。 好吧好吧。 不过, 罗登堡先生的歉意相当有说服力, 很难拒绝。 先生, 写一封合适的回信需要一些时间, 你能明天中午左右再来见我, 以便取走回信吗? 去酒馆休息一下, 在城里走走。 圣地亚哥有很多值得一看的地方。 ";
			link.l1 = "好的, 我明天中午左右回来。 到时候见, 先生。 ";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //移除计时器
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//禁止军官生成 // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "是的, 当然... 但我认为我们可以不用书面的客套话。 只要告诉他这句话‘这个人必须死’。 考虑到收到的歉意的‘价值’, 这将是公平的, 我们也不会有任何问题。 这件事将被视为完全解决。 ";
			link.l1 = "好的, 我会记住的, 先生。 还有别的吗? ";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "是的, 当然。 我说的话是吉拉尔迪家族的意愿。 当然, 你可以代我向卢卡斯先生问好。 祝你一帆风顺, " +GetFullName(pchar)+ "船长。 ";
			link.l1 = "我明白了。 再见, " + npchar.name+ "先生。 ";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//允许军官生成 // 291112
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}