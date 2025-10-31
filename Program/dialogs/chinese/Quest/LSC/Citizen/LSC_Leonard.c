// 伦纳德.马斯凯特 - 酒鬼
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "我不想和你说话。 你无缘无故攻击和平的平民, 还挑衅他们打架。 走开! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			// --> 喝到见底
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "伙计, 你来得正是时候... 我想和你谈谈... 关于一笔生意。 一笔重要的生意。 ";
				link.l1 = "真的吗? 看起来你没喝醉。 发生什么事了? 看到你清醒可不常见。 ";
				link.l1.go = "facio";
				break;
			}
			// < —喝到见底
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "啊-a... 嗝! 你好啊, 伙计... ";
				link.l1 = TimeGreeting() + "。 看来你已经喝够了, 伙计。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! 嗝! 你想要什么? ";
				link.l1 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
				link.l1.go = "rumours_LSC";
				link.l2 = "我想问你几个关于这个岛的问题。 ";
				link.l2.go = "int_quests"; // 信息块
				link.l5 = "只是想知道你过得怎么样。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "是啊! 喝够了? 不-ope! 我是个疯狂的酒鬼, 嗨-嗝! 没错, 伦纳德.马斯凯特喝醉了, 这才是正常的! ";
			link.l1 = "喜欢喝酒, 嗯? 是的, 我叫" +GetFullName(pchar)+ "。 很高兴见到你。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "如果你这么说的话。 我们都在这里... 嗝, 互相认识。 ";
			link.l1 = "好吧, 看来你没心情聊天。 再见! ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息块
			NextDiag.TempNode = "First time";
		break;
		
		// --> 喝到见底
		case "facio":
			dialog.text = "是的, 伙计, 我几乎清醒了。 那是因为我有笔生意给你, 一笔重要的生意。 而且看起来你能做... ";
			link.l1 = "什么? 你在想什么? 说吧, 别浪费我的时间! ";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "伙计, 你想赚钱吗? 银币, 金币? 我会告诉你怎么做。 但你得和我分账 - 我们一起干。 ";
			link.l1 = "我总是想赚钱。 但这取决于你的提议: 即使很赚钱, 我也不做任何工作。 ";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "这生意确实不合法, 但很赚钱... 而且我们能惩罚一个变得太挑剔的人。 他不会变穷, 他钱太多了。 每个人都和他分享, 现在该轮到他了。 告诉我, 你能喝朗姆酒吗? 你能喝多少才会醉倒? ";
			link.l1 = "视情况而定。 我不确定我有没有疯狂喝酒的习惯... 你终于要告诉我细节了吗? ";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "我正在说重点, 你只是还没明白。 好吧。 我具体说。 岛上有个又胖又丑的混蛋 - 朱塞佩.法西奥。 一个罕见的人渣。 他活剥独角鲸。 里瓦多和当地人的皮。 我观察他一段时间了, 终于有了发现\n在他卡罗莱纳的船舱里有两个箱子: 第一个装文件, 第二个装金银。 两个箱子都用不同的钥匙锁着。 胖子总是把钥匙带在身上。 ";
			link.l1 = "嗯, 看来你要抢劫法西奥? 我不会参与的。 你最好庆幸我不会告诉任何人。 如果你想检查胖子的箱子, 应该找另一个伙伴。 ";
			link.l1.go = "facio_exit";
			link.l2 = "哈! 有趣! 继续... ";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "太糟了, 真的太糟了... 有很多金子, 够我们俩分的。 好吧, 回头见... ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "他的船舱有两扇门。 其中一扇总是锁着。 但打开装金子箱子的钥匙也能打开那扇门。 我不知道这有什么意义, 但这是事实。 你只需要一把钥匙就能打开船舱并拿到金子。 接下来是个逻辑问题 - 如何弄到钥匙? 所以, 我有个计划\n一个绝妙的计划, 如果顺利的话, 法西奥永远不会意识到发生了什么, 该怪谁。 他们会认为是神秘的小偷干的。 问题是, 我需要一个有钢铁意志的伙伴来完成这件事。 你明白吗? ";
			link.l1 = "我在听。 继续。 ";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "法西奥喜欢坐在桑乔酒馆好好喝一杯, 但他太胖了, 朗姆酒对他影响不大。 所以他想出了一个喝酒游戏 - 人们试图灌醉他的游戏。 如果你提议和他玩这个游戏, 他肯定会同意\n然后有趣的部分来了。 你和他打赌, 去酒馆, 拿起朗姆酒喝到其中一个亲吻桌子。 如果你醉倒了, 整个计划就失败了, 我一个人做不到\n这就是我问你意志的原因。 如果你能让法西奥像猪一样哼哼唧唧, 就算成功了。 我会一直待在附近。 等他喝光了, 我就拿他的钥匙\n然后我们把胖子搬到楼上的床上, 趁他睡着时溜进他的船舱。 我会在我们抢完箱子后马上还回钥匙, 他甚至不会意识到被抢了\n我负责拿钥匙和还钥匙, 你的任务是把法西奥灌醉并溜进他的住处。 我会放哨, 以防有人出现, 这样你就有足够时间从后门逃跑\n我们把箱子里的东西对半分, 这很公平。 那么, 你加入吗? ";
			link.l1 = "好计划! 当然, 试试吧! ";
			link.l1.go = "facio_6";
			link.l2 = "不, 伙计。 我放弃。 我担心我喝不了那么多, 无法站稳并灌醉法西奥。 找另一个比我强壮点的伙伴吧。 ";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "很高兴我没看错你。 现在去找法西奥, 安排晚上九点后在酒馆见面。 希望你能灌醉那头猪。 祝你好运, 晚上见! ";
			link.l1 = "我会试试... 再见! ";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // 醉酒结果
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3天
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "伙计, 我就靠你了。 灌醉那个胖子... ";
			link.l1 = "当然... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "搞定了, 那个肥猪在楼上睡着了。 我拿到钥匙了。 你做得很好, 看起来还够清醒! ";
			link.l1 = "是吗? 我好久没喝成那样了。 感觉有点头晕... 我们走? ";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "搞定了, 那个肥猪在楼上睡着了。 我拿到钥匙了。 你做得很好, 真的把那头猪灌醉了... ";
			link.l1 = "是啊, 但我好久没喝成那样了。 我头晕眼花... 那我们走吧? ";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "唉, 伙计, 你没能灌醉那个胖子... 太糟了。 好吧, 至少我们试过了... ";
			link.l1 = "真-真该死, 他就像个... 不-不-不沉的桶。 啊, 我需要休-休-休息... 结束了, 滚-滚蛋! 嗝! ..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "是的。 走吧! 跟我去‘卡罗莱纳’! 别磨蹭, 我们时间不多! ";
			link.l1 = "走吧! ";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; // 移除计时器
			dialog.text = "给。 拿上钥匙。 你需要的箱子在入口左边。 尽快拿尽可能多的东西。 别忘了再锁上。 如果我看到什么, 就敲三下门。 如果那样的话, 从后廊逃跑。 ";
			link.l1 = "好的。 你放哨! ";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// 计算从箱子里拿的钱和金币
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "一个比索都没有";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "一个杜布隆都没有";
			else sDubl = ""+iDubl+" 个杜布隆";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "多可怜的战利品... 我们值得为此冒险吗? 唉... 好吧, 我们分了所得的东西。 ";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "我以为会多得多... 冒险不值得。 唉... 好吧, 我们分了所得的东西。 ";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "嗯。 不错。 但我以为我们会得到更多。 好吧, 我们分了吧。 ";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "太棒了! 我们干得好, 伙伴! 这是一大笔钱! 我们分了吧! ";
						else
						{
							sTotalTemp = "哇! 我从没想过那个胖子的藏匿处这么大。 干得好, 伙伴! 我们分了吧! ";
						}
					}
				}
			}
			dialog.text = "终于! 你从那个恶棍的箱子里拿了什么? 给我看看, 我迫不及待地等着呢! ";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "里面什么都没有。 只有一些废料。 护身符之类的东西。 ";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "我从箱子里拿了" + sPeso + "和" + sDubl + "";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "不可能! 看来这一切都白费了... 也许那个混蛋把他的藏匿处放在另一个箱子里了。 唉! 好吧, 把钥匙给我, 我会在他发现之前把它还给主人。 再见, 伙计... ";
			link.l1 = "... ";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "我们分吧... ";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveDublonsFromPCharTotal(iDubl);
			Log_Info("你给了" + iDubl + "个杜布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "好吧, 把钥匙给我, 我会在他发现之前把它还给主人。 再见, 伙计... ";
			link.l1 = "祝你好运, 伙计... ";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("法西奥在抱怨有人清空了他的箱子。 看来是那个神秘的小偷干的。 ", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("你听说了吗? 法西奥被抢了! 他是在和你玩游戏喝醉后被抢的。 ", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("你酒量真好! 喝了这么多朗姆酒还能站稳! 真了不起... ", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // 锁上箱子
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // 到走廊
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;// 打开地点
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // 锁上箱子
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// < —喝到见底
		
//------------------------------------- —问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "真的吗? ... 嗝! 我在听... ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你怎么会到这里来? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你总是喝酒吗? 你从哪里弄钱买酒? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "关于当地人, 你能告诉我什么? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你想离开这个地方去大陆吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "耶! 我发誓, 我不记得了。 是的, 是的, 我不记得了! 那是很久以前的事了。 我不知怎么航行到了某个地方, 最后到了这里。 嗝! ";
			link.l1 = "嗯... 好吧, 好吧。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "是的, 我是个酒鬼... 喝酒, 该死的, 因为我无事可做... 你看, 伙计, 我完了。 一瓶朗姆酒是我唯一想要的。 所以我会继续喝酒。 而钱... 他-他, 朗姆酒不贵。 不管怎样, 我甚至不必买它\n有个地方装满了朗姆酒, 但如果你想得到它, 就需要游泳, 所以我只在醉得不能游泳时才买朗姆酒... 嗝! Jizjezezejizeze, 不, 我不会告诉你去哪里游泳, 他-他, 别问... ";
			link.l1 = "太棒了。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "我能说什么呢, 嗝... 关于他们? 很好的聊天和喝酒的人。 朱塞佩.法西奥是个重要人物, 当地的大人物, 他的箱子里装满了金子... 但他仍然尊重老利奥, 在酒馆给他买酒。 不过, 有时他也会要求回报, 但没什么, 嗝! \n嘿, 你不知道法西奥有多少杜布隆吧, 啊-哈-哈-哈! 足够你在加勒比最好的房子里不工作, 喝世界上最好的朗姆酒度过余生。 但他还是留在这个岛上。 看来钱对他来说还不够... ";
			link.l1 = "知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "离开? 嗝! 为什么? 不, 我不想去大陆也不想去穷岛。 有免费朗姆酒吗? 没有! 那里没有免费朗姆酒, 嗝! 这意味着我在那里无事可做... 伙计, 我在这里感觉很好。 我再告诉你 - 问问人们是否想离开这个地方。 除了两三个, 没人想走, 嗝! ";
			link.l1 = "有趣... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// < —问答块
		
//--------------------------------------- —特殊反应 -----------------------------------------------
		// 发现主角在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里干什么, 啊? 小偷! ", "看看这个! 我一不留神, 你就决定检查我的箱子了! ", "决定检查我的箱子了? 你逃不掉的! ");
			link.l1 = "该死! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子了? 你逃不掉的! ";
			link.l1 = "愚蠢的女孩! ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// 对露出武器的评论
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 这让我很紧张。 ", "你知道吗, 在这里带着刀乱跑是不被允许的。 把它收起来。 ", "听着, 别扮演中世纪的骑士, 拿着剑到处跑。 把它收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好吧。 ", "好的。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我希望你把刀收起来。 ", "听着, 我是这个城市的公民, 我希望你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好吧。 ", "好的。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 伙计, 带着武器乱跑。 我会紧张的... ", "我不喜欢男人拿着武器在我面前走来走去。 这让我害怕... ");
				link.l1 = RandPhraseSimple("明白了。 ", "我收起来。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// < —特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}