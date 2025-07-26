// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("说吧, 你想要什么? ",
                          "我们刚刚还在谈论这个。 你一定是忘了... ", "这是你今天第三次问我问题了... ",
                          "听着, 这是一家商店。 人们在这里买东西。 别打扰我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道的, " + Npchar.name+ ", 也许下次吧。 ", "是的, 不知为什么我忘了... ",
                      "是的, 这确实是第三次了... ", "嗯, 我不会了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason 国家任务
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = "你仓库里存着我的货物。 茶叶。 可可和愈创木。 我现在要取走。 ";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "你仓库里存着我从圣马丁岛运来的货物。 是诺埃尔.福格男爵留给我的。 ";
                link.l2.go = "patria_goods_3";
			}
		break;
		
		case "patria_goods":
			dialog.text = "没错, 船长, 你的货物我收着。 你确定要取走吗? ";
			link.l1 = "是的。 ";
			link.l1.go = "patria_goods_1";
			link.l2 = "等等, 我得先检查一下船舱是否有足够空间。 ";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "很好。 我会命令搬运工把货物送到码头。 ";
			link.l1 = "成交! ";
			link.l1.go = "patria_goods_2";
		break;
		
		case "patria_goods_2":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); // 时间流逝
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.Goods");
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE) + 500);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE) + 500);
			SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(pchar, GOOD_SANDAL) + 50);
		break;
		
		case "patria_goods_3":
			dialog.text = "是的, 没错。 根据男爵的命令, 我把货物存放在这里。 你确定要取走吗? ";
			link.l1 = "是的。 ";
			link.l1.go = "patria_goods_4";
			link.l2 = "等等, 我得先检查一下船舱是否有足够空间。 ";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "很好。 我会命令搬运工把货物送到码头。 ";
			link.l1 = "成交! ";
			link.l1.go = "patria_goods_5";
		break;
		
		case "patria_goods_5":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); // 时间流逝
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.GoodsSM"); // 17-添加
			SetCharacterGoods(pchar, GOOD_TOBACCO, GetCargoGoods(pchar, GOOD_TOBACCO) + 500);
			SetCharacterGoods(pchar, GOOD_EBONY, GetCargoGoods(pchar, GOOD_EBONY) + 200);
			SetCharacterGoods(pchar, GOOD_MAHOGANY, GetCargoGoods(pchar, GOOD_MAHOGANY) + 250);
			SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + 200);
			SetCharacterGoods(pchar, GOOD_SILVER, GetCargoGoods(pchar, GOOD_SILVER) + 400);
			SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(pchar, GOOD_SHIPSILK) + 200);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}