//Jason 丛林印第安人对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("白皮肤的","白皮肤的女人") + "想说话? ", 
				"又是你, " + GetSexPhrase("白皮肤的","白皮肤的女人") + "。 ", 
				"" + GetSexPhrase("白皮肤的喜欢说话, 看起来像个女人。 ","白皮肤的女人喜欢说话。 ") + "",
				"神灵给我带来了白皮肤的" + GetSexPhrase("兄弟。 ","姐妹。 ") + "。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("是的。 ", 
				"是我, 又来了。 ",
				"很有诗意。 ", 
				"我也很高兴见到你。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = " hail, 白人兄弟。 你想和印第安人说话? ";
				link.l1 = "问候你, 丛林之子。 很高兴见到你, 但我必须继续我的旅程。 ";
				link.l1.go = "exit";
				link.l2 = "是的。 我听说你卖有趣的东西。 你有什么可卖的吗? ";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": // 印第安人交易
			switch (hrand(7))
			{
				case 0: // 通过界面交易
					dialog.text = "你很幸运, 白人兄弟。 " + npchar.name+ "有一些东西要卖。 看这里。 ";
					link.l1 = "展示你的商品... ";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "等等。 我有东西要卖。 这是一种叫曼加罗萨的植物。 我听说你喜欢这东西... ";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // 不交易
					dialog.text = "不, 白人兄弟。 " + npchar.name+ "不交易。 " + npchar.name+ " 是战士。 ";
					link.l1 = "我明白了。 好吧, 再见, 红皮肤的兄弟。 ";
					link.l1.go = "exit";
				break;
				
				case 2: // 大珍珠
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = "" + npchar.name+ "有神灵的眼泪。 大颗的, 白人兄弟。 数量为" + FindRussianQtyString(sti(npchar.quest.item.qty)) + "。 你想买吗? 我卖" + FindRussianMoneyString(sti(npchar.quest.item.price)) + "一个。 ";
					link.l1 = "不, 我不感兴趣。 ";
					link.l1.go = "exit";
					link.l2 = "当然! 这么便宜我很乐意买。 ";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "等等。 我有东西要卖。 这是一种叫曼加罗萨的植物。 我听说你喜欢这东西... ";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // 小珍珠
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = "" + npchar.name+ "有神灵的眼泪。 小颗的, 白人兄弟。 数量为" + FindRussianQtyString(sti(npchar.quest.item.qty)) + "。 你想买吗? 我卖" + FindRussianMoneyString(sti(npchar.quest.item.price)) + "一个。 ";
					link.l1 = "不, 我不感兴趣。 ";
					link.l1.go = "exit";
					link.l2 = "当然! 这么便宜我很乐意买。 ";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "等等。 我有东西要卖。 这是一种叫曼加罗萨的植物。 我听说你喜欢这东西... ";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: // 金块
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = "" + npchar.name+ "有你们白皮肤人很喜欢的黄色金属。 数量为" + FindRussianQtyString(sti(npchar.quest.item.qty)) + "。 我只卖" + FindRussianMoneyString(sti(npchar.quest.item.price)) + "一个。 ";
					link.l1 = "不, 我不感兴趣。 ";
					link.l1.go = "exit";
					link.l2 = "当然! 这么便宜我很乐意买。 ";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "等等。 我有东西要卖。 这是一种叫曼加罗萨的植物。 我听说你喜欢这东西... ";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // 银块
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = "" + npchar.name+ "有你们白皮肤人很喜欢的白色金属。 数量为" + FindRussianQtyString(sti(npchar.quest.item.qty)) + "。 我只卖" + FindRussianMoneyString(sti(npchar.quest.item.price)) + "一个。 ";
					link.l1 = "不, 我不感兴趣。 ";
					link.l1.go = "exit";
					link.l2 = "当然! 这么便宜我很乐意买。 ";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "等等。 我有东西要卖。 这是一种叫曼加罗萨的植物。 我听说你喜欢这东西... ";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // 重复通过界面交易
					dialog.text = "你很幸运, 白人兄弟。 " + npchar.name+ "有一些东西要卖。 看这里。 ";
					link.l1 = "展示你的商品... ";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "等等。 我有东西要卖。 这是一种叫曼加罗萨的植物。 我听说你喜欢这东西... ";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // 重复不交易
					dialog.text = "不, 白人兄弟。 " + npchar.name+ " 不交易。 " + npchar.name+ " 是战士。 ";
					link.l1 = "我明白了。 好吧, 再见, 红皮肤的兄弟。 ";
					link.l1.go = "exit";
				break;
			}
		break;
		
		case "torg":
			DialogExit();
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = "First time";
			LaunchItemsTrade(NPChar, 0);
			ChangeIndianRelation(1.00);
		break;
		
		// 大珍珠
		case "big_pearl":
			dialog.text = "你想买多少颗眼泪? ";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "你在开玩笑吗, 白皮肤的? 你不需要神灵的眼泪? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "我告诉过你我有多少眼泪。 你在和印第安人开玩笑吗, 白皮肤的? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = "" + iQty + "颗眼泪? 好吧。 你给我" + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", 白人兄弟。 ";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "给你钱, 红皮肤的兄弟。 ";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "我现在钱不够。 抱歉, 我不能买你的珍珠。 ";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "拿去吧, 白人兄弟。 现在它们是你的了。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// 小珍珠
		case "small_pearl":
			dialog.text = "你想买多少颗眼泪? ";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "你在开玩笑吗, 白皮肤的? 你不需要神灵的眼泪? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "我告诉过你我有多少眼泪。 你在和印第安人开玩笑吗, 白皮肤的? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = "" + iQty + "颗眼泪? 好吧。 你给我" + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", 白人兄弟。 ";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "给你钱, 红皮肤的兄弟。 ";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "我现在钱不够。 抱歉, 我不能买你的珍珠。 ";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "拿去吧, 白人兄弟。 现在它们是你的了。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// 金块
		case "gold":
			dialog.text = "你想买多少? ";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "你在开玩笑吗, 白皮肤的? 你不需要金属? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "我告诉过你我有多少。 你在和印第安人开玩笑吗, 白皮肤的? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = "" + iQty + "块? 好吧, 给我" + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", 白人兄弟。 ";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "给你钱, 红皮肤的兄弟。 ";
				link.l1.go = "gold_1";
			}
			link.l2 = "我现在钱不够。 抱歉, 我不能买你的金子。 ";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "拿去吧, 白人兄弟。 现在它们是你的了。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// 银块
		case "silver":
			dialog.text = "你想买多少? ";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "你在开玩笑吗, 白皮肤的? 你不需要金属? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "我告诉过你我有多少。 你在和印第安人开玩笑吗, 白皮肤的? 那再见。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = "" + iQty + "块? 好吧, 给我" + FindRussianMoneyString(sti(npchar.quest.item.Summ)) + ", 白人兄弟。 ";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "给你钱, 红皮肤的兄弟。 ";
				link.l1.go = "silver_1";
			}
			link.l2 = "我现在钱不够。 抱歉, 我不能买你的银子。 ";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "拿去吧, 白人兄弟。 现在它们是你的了。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// 曼加罗萨
		case "mangarosa":
			dialog.text = "曼加罗萨? 我想看看。 ";
			link.l1 = "给, 看看... ";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "是的。 这是它的一个名字 —曼加罗萨。 我用它换给你一个护身符。 非常好的护身符, 它的名字是 --" + XI_ConvertString(npchar.quest.mangarosa) + "。 你交易吗? ";
			link.l1 = "听着, 红皮肤的兄弟, 我想多了解一下这种植物。 你能告诉我为什么你这么需要它吗? ";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = "" + npchar.name+ "不明白。 如果你想交易, 我用曼加罗萨换给你护身符。 如果不想, 那我走了。 ";
			link.l1 = "哦, 好吧。 我们交易吧。 ";
			link.l1.go = "mangarosa_3";
			link.l2 = "不。 我不会用这种植物换一个护身符。 ";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("你获得了一个护身符");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "拿着你的" + XI_ConvertString(npchar.quest.mangarosa) + "。 它会有用的。 ";
			link.l1 = "毫无疑问。 祝你好运, 红皮肤的朋友。 ";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// 对citizen类型角色展示武器的评论
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "你别试探命运, 白皮肤的! 收起你的剑! ", "听着白皮肤的, 收起你的武器让我们谈谈, 我不需要麻烦。 ");
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}