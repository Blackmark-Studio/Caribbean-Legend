// 桑乔.卡彭特罗 - 酒吧老板
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "我不想和你说话。 你无缘无故攻击和平的人, 还挑衅他们打架。 从我的酒馆滚出去! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! 见到你真高兴! 我就知道, 那些流言蜚语都是骗人的! 该死的, 我们现在绝对得为此干一杯! ";
				link.l1 = "好啊, 兄弟! 我们喝一杯! 我也很高兴见到你! ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// 一饮而尽
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", 对你的失败我很遗憾。 很少有人能喝赢那个胖子。 你头还疼吗? ";
				link.l1 = "是啊, 兄弟, 你这儿的朗姆酒真带劲。 我欠你酒钱... 多少? ";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "你打败了法奇奥, "+pchar.name+"! 我很惊讶, 只有少数人能喝赢他。 拿着, 这是你的二百杜布隆。 ";
				link.l1 = "谢谢你的夸奖, 兄弟! ";
				link.l1.go = "drunk_win";
				break;
			}
			// 螃蟹沙拉
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? 听说你穿着独角鲸机械师做的潜水服潜到了海底。 是真的吗, 还是像往常一样只是流言? ";
				link.l1 = "是真的, 兄弟。 我真的潜下去了。 ";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "欢迎来到我的酒馆的新客人! 欢迎! 在我的酒馆里你总能找到喝的, 我的酒窖里堆满了酒, 不过食物就不好说了, 哈哈... 开玩笑的。 我叫桑乔.卡彭特罗, 是这家店的老板。 ";
				link.l1 = TimeGreeting()+", 桑乔。 我叫"+GetFullName(pchar)+"。 很高兴认识你。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, 我的朋友"+pchar.name+"! 很高兴在我的酒馆见到你! 想喝点什么吗? ";
				// 任务分支
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "听着, 桑乔, 你知道哪里能弄到好的滑膛枪吗? 不是普通士兵的副武器, 而是精准的, 也许用于打猎的? ";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "听着, 桑乔, 我有几个问题要问你。 我在找一个叫阿道夫.巴比尔的人。 据说他经常来这个地方... ";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "听着, 桑乔, 据说查德.卡珀从你这里买了些砒霜... ";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "桑乔, 想看看有趣的东西吗? 这就是你一直想要的蝙蝠面具吗? ";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "桑乔, 我来拿我的胸甲。 这是钱。 ";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "桑乔, 我来拿我的胸甲。 这是钱。 ";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "给我来些朗姆酒, 桑乔。 ";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "我想在这里过夜。 ";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "无聊... 桑乔, 我想在这里喝瓶酒打发时间直到晚上... ";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("有什么有趣的事可讲吗? ", "岛上最近发生了什么事? ", "有什么流言吗? ");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "桑乔, 我想把螃蟹爪子卖给你。 ";
					link.l10.go = "crab_trade";
				}
				link.l4 = "桑乔, 我想问你一些关于这个岛的事。 ";
				link.l4.go = "int_quests"; // 信息块
				link.l5 = "不, 兄弟。 只是想看看你在这里怎么样。 ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "我也是。 我希望你至少每隔一天甚至每天晚上都来, 哈哈! 酒馆里来客人我真心高兴。 ";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "给我来些朗姆酒, 桑乔。 ";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "我想在这里过夜。 ";
				link.l2.go = "room";
			}
			link.l3 = "桑乔, 我想问你一些关于这个岛的事。 ";
			link.l3.go = "int_quests"; // 信息块
			link.l4 = "再见, 桑乔! ";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "不, 朋友, 我帮不了你。 你知道, 我是啤酒杯和葡萄酒瓶方面的专家 - 但不是滑膛枪方面的, 哈哈! 去商店看看吧, 我听说阿克塞尔有时会卖一些有趣的武器。 你可能会在那里找到你需要的东西。 ";
			link.l1 = "谢谢你的建议。 ";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "阿道夫? 是的, 他偶尔会来我这里, 不过我已经好几天没见到他了。 自从他和那个胖子朱塞佩聊过天后, 就一直没露面。 ";
			link.l1 = "朱塞佩? 你是说朱塞佩.法奇奥? ";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "哈哈, 兄弟, 岛上只有一个朱塞佩 - 朱塞佩.法奇奥。 是的, 就是他。 他们坐了几个小时, 喝着朗姆酒, 聊得很热闹。 ";
			link.l1 = "他们吵架了吗? ";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "没有。 他们看起来像老朋友一样。 听着, 去‘卡罗琳’找法奇奥, 问问他关于阿道夫的事。 ";
			link.l1 = "好的, 我会去的。 ";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "就这些吗? 你说你有几个问题... ";
			link.l1 = "是的。 告诉我, 红玛丽和独眼龙马塞洛是谁? ";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "红玛丽是独角鲸成员之一。 年轻漂亮的女孩, 但完全野性, 是的。 她用刀和手枪的技术和任何男人一样好。 在舰队司令杀了艾伦.米尔罗之前, 她曾是独角鲸部落前首领艾伦.米尔罗的女朋友\n艾伦的死对她打击很大, 大部分时间她都在‘刻瑞斯铁匠号’的船舱里哭泣和诅咒鲨鱼... 但她会挺过去的, 生活毕竟还要继续\n我对马塞洛了解不多, 只见过几次。 可疑的家伙。 据说他曾经是皇家猎人, 在一次战斗中失去了一只眼睛, 后来作为登船军官出海\n他讨厌海盗, 看起来他对他们怀恨在心。 考虑到他以前在商船登船队的服役经历, 这并不奇怪。 ";
			link.l1 = "我明白了。 非常感谢, 桑乔, 你帮了大忙! ";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "不客气, 兄弟, 再来看我, 我们一起喝杯麦芽酒... ";
			link.l1 = "一定! ";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; // 指向朱塞佩的标志
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// 给鲨鱼的威士忌
		case "whiskey":
			dialog.text = "卡珀? 没有。 他最近没来过酒馆。 独眼龙马塞洛十五分钟前刚买了一瓶砒霜 - 他也被老鼠困扰。 我完全理解他... 该死的老鼠。 ";
			link.l1 = "独眼龙马塞洛? ! ";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "嗯, 是的。 有什么奇怪的吗? ";
			link.l1 = "不, 当然不! 我找了他好几天, 结果他最近来过这里。 你能告诉我他去哪儿了吗? ";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "他和住在‘圣弗洛伦蒂娜’的阿道夫.巴比尔在一起。 也许他们是去那里了。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "如果你需要砒霜, 我可以以二十杜布隆的价格卖你一瓶。 ";
			link.l1 = "好的。 我们稍后再谈, 桑乔。 再见! ";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // 标志 - 威士忌被下毒
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // 给鲨鱼的节点
			// 重要时刻! 取决于玩家后续行为决定结果
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // 在圣弗洛伦蒂娜的中断
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // 在阿瓦的中断
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // 离开酒馆的中断
			// 关闭去法奇奥的入口
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// 一饮而尽
		case "drunk_fail":
			dialog.text = "来吧, 兄弟! 你不欠我任何东西。 你已经输了一百杜布隆。 和法奇奥打赌是个错误... ";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "不-不, 桑乔! 谢谢你, 请收下这五百比索。 据我记忆, 这应该够付酒钱了。 我不想欠你人情。 ";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "嗯, 谢谢, 桑乔。 你说得对。 ";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("你获得了200杜布隆");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// 螃蟹沙拉
		case "crab":
			dialog.text = "嗯... 那我有个提议给你。 你在那里看到过大螃蟹吗? ";
			link.l1 = "我看到螃蟹了吗? 那里成群结队! 你说的是什么提议? ";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "如果你杀了一些螃蟹, 一定要把爪子带给我。 我会用杜布隆给你好价钱 - 每个五枚。 相信我, 阿克塞尔.约斯特不会出这么高的价。 我不是要你专门为了这个去猎蟹 - 但如果你遇到了, 请记住... ";
			link.l1 = "为什么要爪子? 螃蟹的其他部分呢? 你用那些做什么? ";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "为什么要爪子? 因为大部分肉都在爪子上。 螃蟹的腿上没多少肉, 身体覆盖着坚硬的外壳。 蟹肉在这里是美味佳肴, 味道极佳且非常有营养\n我还有一个独特的食谱, 所以每个蟹钳我给你五杜布隆。 ";
			link.l1 = "好的。 我会记住的。 ";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "太好了! 你有多少? ";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+"。 ";
			link.l1.go = "crab_trade_1";
			link.l2 = "我改变主意了。 ";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "成交。 给你杜布隆 - "+FindRussianQtyString(iTotalTemp*5)+"。 谢谢, 兄弟, 如果你有更多, 带给我。 ";
			link.l1 = "当然, 朋友。 ";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("你获得了"+iTotalTemp*5+"杜布隆");
		break;
		
		// 老鼠
		case "rat":
			dialog.text = "什么? ! 给我看看! 让我看看! ";
			link.l1 = "当然。 ";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "就是这个... 真的是! 和一个水手给我画的图片上的一模一样! 朋友, 你把这个带给我一定有原因, 你想要什么回报? 多少钱? ";
			link.l1 = "我当然是有原因才带给你。 但至于报酬, 你能提供什么? 我记得你答应过我为了这个东西会给我丰厚的奖励... ";
			link.l1.go = "rat_2";
			link.l2 = "对不起, 兄弟, 这是非卖品。 我自己需要它。 只是想确认一下这是不是你说的那个护身符。 ";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "唉, 真遗憾... 是的, 伙计, 这正是那个护身符。 幸运的家伙! 现在老鼠不会再给你添麻烦了。 而我还得继续用砒霜灭鼠... ";
			link.l1 = "对不起逗你玩了, 桑乔。 我以前从没见过, 所以需要咨询一下。 抱歉。 ";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "为了这个, "+pchar.name+", 我会给你机会购买我拥有的最精美。 最有价值的物品。 对于这样的护身符来说, 这是一个很好的交换, 尤其是对像你这样勇敢的战士。 让我给你拿来\n看看: 这是一件独特的。 华丽的米兰胸甲, 工艺精湛! 它在战斗中提供出色的保护, 允许自由移动, 而且轻便舒适。 这种质量的盔甲在加勒比和欧洲都很罕见\n几年前我在一艘西班牙战船的船长室里偶然发现了这件胸甲, 正是为了这样的场合才保留下来。 我愿意以两千金币和‘鼠神’护身符的价格卖给你! ";
			link.l1 = "嗯... 这确实是一件很棒的胸甲! 我认为这个交换适合我。 我会解决老鼠的问题, 但要找到另一件这样的胸甲几乎是不可能的。 我以前从未见过这样的。 真的, 这是一件独特的盔甲。 ";
			link.l1.go = "rat_yes";
			link.l2 = "多少? 桑乔, 你今天早上被老鼠咬了几口吗? 你说两千是什么意思? 你知道我为了给你弄这个偶像付出了多少吗? 现在降价! ";
			link.l2.go = "rat_torg";
			link.l3 = "多少? ! 你是个鲨鱼, 你知道吗, 桑乔? ‘给你机会购买’! 哈! 用这么多钱, 我可以在大陆订购一件能防弹还能治愈我的盔甲! 你要这么多金子做什么? 让于尔根为你铸造一尊雕像, 在‘圣奥古斯丁’全高展示? ";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "我很高兴你同意, 我的朋友。 谢谢你没有忘记我的问题! 那么, 我等着你的杜布隆。 盔甲会等着你。 ";
			link.l1 = "我马上带来! ";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", 在不同的情况下, 我会要五千。 舰队司令本人也表示过兴趣, 相信我, 不止他一个。 慢慢考虑。 盔甲会等你多久都行。 我只卖给你。 ";
				link.l1 = "我会考虑的, 桑乔。 我会好好考虑的。 ";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", 在不同的情况下, 我会要五千。 舰队司令本人也表示过兴趣, 相信我, 不止他一个。 好吧, 考虑到你没有忘记我和我的问题, 我会少要五百。 看来一路上你经历了一些冒险。 ";
				link.l1 = "这就好多了。 但我还是不明白为什么在这个同样独特的物品交易中我应该多付钱。 也许你应该付我, 嗯桑乔? ";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "不, "+pchar.name+", 不可能。 我可以用毒药对付老鼠, 但这件盔甲有一天可能会救你的命。 你穿上它会像个意大利公爵。 一千五, 这是我的最终报价。 慢慢考虑, 告诉我。 盔甲会等你多久都行, 我只卖给你。 ";
				link.l1 = "桑乔, 如果你不是这个沉闷墓地里唯一的酒馆老板... 我会考虑你的提议。 ";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "作为一名军事 captain 和海盗, 你确实很会谈判! 还记得约斯特吗? 有一次他设法以折扣价买了我所有的砒霜, 而那时老鼠已经在折磨我了。 好吧, "+pchar.name+", 你赢了。 我再给你少五百! 但这是最终报价! ";
				link.l1 = "这仍然感觉像敲竹杠, 但至少现在我在丛林里不会像典型的落难少女了。 等我带钱来; 我很快就来。 ";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "冷静点, "+pchar.name+"。 换作别人, 我会要五千! 舰队司令本人也表示过兴趣, 相信我, 不止他一个。 盔甲会等你多久都行。 这也包含在偶像的价格里。 ";
			link.l1 = "真是荣幸! 继续擦你的杯子吧, 我这就走。 两千! ";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "成交! 很高兴你同意了, 兄弟。 谢谢你没有忘记我的问题! 拿着胸甲, 希望它在战斗中对你有用。 ";
			link.l1 = "给, 也拿着你的护身符 - 看来你酒馆里的老鼠黑暗日子要来了! ";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("你送出了护身符‘鼠神’");
			Log_Info("你获得了米兰盔甲");
			Log_Info("你给了"+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("你给了"+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "你还欠我"+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+"。 ";
			link.l1 = "别提醒我! ";
			link.l1.go = "exit";
		break;
		
		//--> 信息块
		case "int_quests":
			dialog.text = "我在听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "这是什么地方? 你能多告诉我一些吗? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "我怎么离开这个岛? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "关于这个岛我应该知道什么? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你在这里怎么样? 你的酒馆如何? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "我没有问题了, 算了... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "这个地方? 嗯, 他们叫它正义岛。 废弃船只岛, 或者废弃船只城 - 但我们就叫它岛。 它是由船只残骸形成的, 这些残骸卡在礁石中的浅滩上。 岛的中心部分是生活区, 外围无人居住。 这里与外界已经十年没有联系了。 ";
			link.l1 = "知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "造一艘长船或木筏。 但这对你不会有好结果。 岛周围有一个异常风暴区, 你不冒生命危险就无法通过外围。 另外, 岛被一股强流环绕\n你需要一个团队才能有一线生存机会。 而且很少有当地人愿意离开这个地方。 愿意冒险的人更少。 人们喜欢这里的生活方式。 如果你不信, 可以问问周围的人。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "首先, 你应该记住岛上有几个禁区。 两个部落 - 独角鲸和里瓦多斯, 他们在这里生活了很长时间, 互相争斗, 无畏地保护他们认为属于自己的领土。 试着不请自来拜访他们, 你就死定了\n如果你想进入他们的领土, 必须知道当前的密码。 别担心会不小心闯进去, 守卫在开枪前会给你几次警告。 ";
			link.l1 = "我会记住的... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "你知道, 我的朋友, 还不错。 我过去从事食品和饮料工作: 很久以前在欧洲当厨师, 在驻军当军需官, 酒馆老板, 船上的厨师; 所以我在这里做的第一件事就是开了一家酒馆\n我喜欢我的工作, 我的生活也出奇地令人满意。 这里的人大多很友好。 至少他们不经常互相残杀。 部落不干涉我的活动。 总的来说, 这是我生活过的最好的地方。 我在这里很自由, 没有人告诉我该做什么\n唯一让我发疯的是老鼠。 它们折磨我, 吃我的食物, 毁坏我的餐具。 我很难摆脱它们。 ";
			link.l1 = "老鼠? 是的, 它们是每个人的麻烦... ";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "唉, 说到老鼠, 我是这里最不幸的人。 其他船只没有这么受老鼠困扰, 而阿克塞尔.约斯特不知怎么的彻底解决了它们。 至于我, 这里爬满了成群的老鼠。 嗯, 他们告诉我有一个特殊的护身符, 叫做鼠神\n它看起来像蝙蝠面具。 据说这个护身符能把老鼠吓得屁滚尿流。 我猜有人把这个护身符卖给了阿克塞尔, 他买和转卖他们在外围找到的每一件垃圾\n我希望有人把护身符带给我, 我会给那个人丰厚的奖励! ";
			link.l1 = "有意思... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//< —信息块
		
		//--> 饮酒
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", 我认为你应该停下来。 上帝保佑你别惹上麻烦或掉进海里成为螃蟹的食物... 在这里喝太多不是好主意, 很多人因此而死。 ";
				link.l1 = "嗯... 我想你是对的, 桑乔 - 我已经喝够了。 谢谢你的关心! ";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "不客气, 兄弟。 一品脱我最好的朗姆酒只要二十五比索! ";
				link.l1 = RandPhraseSimple(LinkRandPhrase("好吧, 为你的健康和酒馆的繁荣, 兄弟! ","好吧, 为海上的人! ","好吧, 为岛上的居民! "), LinkRandPhrase("好吧, 为了这个岛, 愿它永远存在! ","好吧, 愿我们所有的行动都一帆风顺! ","好吧, 为了运气。 幸福和... 女人! "));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") // 进行中任务
			{
				dialog.text = "我认为你现在喝酒不是个好主意。 相信我... ";
				link.l1 = "好吧。 ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // 与玛丽交往
			{
				dialog.text = "呵呵, 你是个奇怪的人... 你在岛上没有可以一起打发时间的人吗? 兄弟, 如果我让你一个人在这里喝醉, 玛丽会杀了我的。 如果你愿意, 晚上一起过来玩到天亮。 ";
				link.l1 = "好吧... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "没问题, 兄弟。 只要三百比索, 你就可以得到一瓶优质的"+LinkRandPhrase("西班牙","意大利","法国")+"葡萄酒 - 想玩多久就玩多久。 ";
				link.l1 = "谢谢! ";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//< —饮酒
		
		//--> 在酒馆睡觉
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") // 进行中任务
			{
				dialog.text = "我认为你现在不应该睡觉。 相信我... ";
				link.l1 = "好吧。 ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // 与玛丽交往
			{
				if(!isDay())
				{
					dialog.text = "我从未见过如此奇怪的人。 有一个漂亮的女孩在‘刻瑞斯铁匠号’等他, 而他却要在酒馆过夜。 别想我会让你在这里睡觉。 玛丽会为此杀了我的。 ";
					link.l1 = "好吧... ";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "你可以在楼上休息到晚上。 但我不会让你在这里过夜 - 玛丽会为此杀了我的。 对不起... ";
					link.l1 = "好吧。 我会在这里待到晚上... ";
					link.l1.go = "hall_night_wait";
					link.l2 = "好吧... 我不睡觉也能应付。 ";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "你可以花二十比索在楼上的床上睡觉。 我什么时候叫醒你? ";
			if(!isDay())
			{
				link.l1 = "早上。 ";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "黄昏前。 ";
				link.l1.go = "hall_night_wait";
				link.l2 = "第二天早上。 ";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "我改变主意了。 我不想睡了。 ";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//< —在酒馆睡觉
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}