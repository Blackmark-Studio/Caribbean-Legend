// 亨利克.维德克. 他也是机械师. 
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "日安, 先生。 我以前从没见过你。 你是新来的吗? 这是你第一次决定访问这个平台? ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 我是这里的新人, 只是四处看看, 认识一下大家... ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "听着, " +pchar.name+ ", 如果你继续打扰我, 我永远修不完。 ";
					link.l1 = "是是, 我记得。 抱歉打扰你了! ";
					link.l1.go = "exit";
					break;
				}
				// 归还迷失的潜水服
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "啊! 看看那个! 溺水的人从另一个世界回来了! 现在告诉我, 你是怎么做到的? 他们已经为你举行了葬礼, 以防万一你不知道... ";
					link.l1 = "太糟了, 我还不打算死。 技巧很简单 --我只是触摸了底部的库库尔坎神像。 它把我传送到了多米尼加, 直接到了加勒比人的村庄... ";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "啊, " +GetFullName(pchar)+ "! " +TimeGreeting()+ "! ";
				// 任务分支
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "亨利克, 我有笔生意找你。 非常重要的生意。 奥莱.克里斯蒂安森跟我提起过你。 他也被叫做‘白人男孩’。 ";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "亨利克, 我给你带来了足够的‘银’。 正如你要求的: 你的一块加上额外十块。 给, 拿着。 ";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "又是我, 亨利克。 你的潜水服怎么样了? 修好没? ";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "我有足够的金属, 就是你要的那种。 拿着吧。 ";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "日安, 亨利克。 那么, 潜水服准备好下潜了吗? ";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "结束了, 我解决了我的问题, 准备好下潜了。 我们什么时候开始? ";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "你好, 亨利克。 那么, 潜水服准备好下潜了吗? ";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "我想还你的潜水服。 ";
					link.l5.go = "immersion_next_2";
				}
				// 任务分支
				link.l1 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
				link.l1.go = "rumours_LSC";
				link.l3 = "我只是想知道你过得怎么样。 ";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "我是亨利克.维德克。 不过, 大多数当地人都叫我‘机械师’, 这确实是个很贴切的称呼。 ";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "你就是亨利克.维德克? 很高兴见到你! 我一直在找你。 ";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "你一定是那个多才多艺的人, 对吧? ";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "哦, 是的, 独角鲸帮很欣赏我的技能。 我的工具让他们能从外环的沉船里获得很多贵重物品, 这样他们就能从多德森舰队司令那里买补给了\n实际上, 科学和探索是我的爱好。 所以, 如果我不能在你身上花足够的时间, 我道歉 --我的实验几乎占据了我所有时间。 ";
			link.l1 = "我明白。 我向你保证, 维德克先生, 我不会无缘无故打扰你。 很高兴见到你! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "是吗? 为什么? ";
			link.l1 = "奥莱.克里斯蒂安森跟我提起过你。 他也被叫做‘白人男孩’。 ";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "啊, 那个有趣的家伙! 是的, 我认识他。 他跟你说了什么? ";
			link.l1 = "抱歉, 如果我接下来的问题听起来很愚蠢, 但... 我还是要问。 奥莱告诉我你可以教我如何在水下潜到海底。 如果这只是他的想象, 请不要嘲笑我。 ";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "是真的。 我自己也下潜过几次海底。 不过, 我现在不再潜水了, 现在浅滩里爬满了巨型螃蟹, 而且, 正如你所见, 我无法与它们战斗, 我是科学家, 对付不了那些东西。 \n此外, 还有另外两个人, 两个独角鲸帮的人, 以前也潜水, 但他们最终也不再这么做了 --事实证明, 抢劫外环船只的货舱比潜入满是巨型螃蟹的地方更安全\n现在他们很少使用我的设备, 因为潜水服的裂缝, 过去几个月都没有下潜过... ";
			link.l1 = "你真的有可以潜到海底的潜水服吗? 我没听错吧? ";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "你耳朵没听错, 年轻人。 这潜水服是我自己发明和制作的。 它由厚实的完全防水帆布。 金属部件和我在尤尔根的铁匠铺里锻造的钢盔制成\n我还为潜水服加上了金属胸甲。 护膝。 护胸和靴子, 以更好地抵御螃蟹和增加重量\n特殊的罐子充满压缩空气, 提供生命支持功能, 让你能在水下待一段时间。 这潜水服独一无二, 我为此感到相当自豪。 ";
			link.l1 = "太棒了。 但你提到潜水服损坏了? ";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "不幸的是, 确实如此。 潜水服的几个部分通过金属板连接, 以实现灵活性和额外保护, 但海水对它们影响很大。 这些金属板在多年的使用中生锈了, 失去了防水能力\n幸好我注意到了损坏, 避免了人们送命。 即使是干式潜水服也进了一些盐和水, 他们的工作彻底搞砸了。 ";
			link.l1 = "嗯.. 但你可以修理潜水服! 你可以用新的部件替换生锈的旧部件... 对吗? ";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "为了什么? 一年后再换一次吗? 你知道这工作有多难吗? 要把潜水服做成灵活的关节并保证防水? 至少需要一周不停歇的工作。 ";
			link.l1 = "这就是你打算扔掉自己发明的原因? ";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "不, 当然不是。 我有个想法。 我需要用不会被水和盐腐蚀的金属来做关节。 我知道什么金属能帮上忙... ";
			link.l1 = "那问题是什么? ";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "问题是这种金属非常稀有。 我只有一块, 显然不够。 我至少还需要十块, 甚至十五块。 ";
			link.l1 = "你说的这种... 金属到底是什么? ";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "哦, 这是一种独特的金属, 真的被很多人低估了。 它具有高耐久性。 可塑性, 而且完全不受侵蚀 --水和盐都无法损坏它\n也许你以前已经见过这种金属。 它是白色的, 看起来像银, 所以西班牙人叫它‘银’。 哈! 它比银好一百倍! 甚至比金还好! 总有一天他们会明白的, 但时机尚未到来。 ";
			link.l1 = "听着, 你为什么不能用其他金属代替? 为什么不用金来做那些板? 我从没听说金会生锈或损坏。 ";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "你思维灵活活跃, 年轻人。 很高兴知道这一点。 不幸的是, 你的提议行不通。 我首先想到的就是金。 但金太软了, 无法连接潜水服的不同部分\n唉, 铂金是唯一适用的材料。 我只会用它来制作部件, 即使需要花几年时间收集足够的量。 但我以前在岛上见过这种金属 --由于外观相似, 它经常和银混在一起。 ";
			link.l1 = "嗯。 如果我帮你找到足够的这种... ‘银’, 你会把潜水服借给我让我水下潜水吗? ";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "不用问! 当然会。 我已经告诉过你, 因为螃蟹我不会去那里潜水, 而且也没有其他人愿意这么做。 ";
			link.l1 = "那就给我看看这块金属, 帮我明白需要找什么。 ";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "所以你要去找? 太好了。 拿着这块作为例子。 在银矿石和 Nuggets 中寻找。 找到它并不容易, 但你能做到。 银上有小的暗色斑点, 但我们的金属是纯净的, 比银硬得多。 测试它最简单的方法是用银币在上面划, 如果银币受损, 那你就找到了。 ";
			link.l1 = "好的。 我马上就去找。 你有什么建议我该去哪里找吗? ";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("你收到了一块铂金锭");
			dialog.text = "唉, 我不知道。 如果我知道去哪里找, 我自己就去了。 但我可以给你一个建议。 在里瓦多斯的船只上找找。 我不去那里, 所以很可能他们有。 ";
			link.l1 = "我会考虑的, 亨利克。 希望我能幸运。 ";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "再收集十块。 这是修理潜水服的最低要求。 祝你好运! ";
			link.l1 = "谢谢。 再见, 机械师! ";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "好, 好, 给我看看... 太棒了! 干得好, 年轻人! 难吗? ";
			link.l1 = "不算太难... ";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "好, 现在我可以开始修理了。 我不会浪费时间, 明天就开始。 你真的很想潜水, 是吗? ";
			link.l1 = "确实。 我真的很想探索水下世界。 ";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "那很好, 因为当我们组织你潜水时, 我会有个请求。 但我们以后再谈。 五天后来看我, 希望我能完成修理。 ";
			link.l1 = "好的。 祝你好运! ";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "当然需要运气, 但修理潜水服主要需要技能。 此外, 我需要和尤尔根在熔炉旁花一天时间, 用你带来的金属制作板。 ";
			link.l1 = "那我就不打扰你了。 五天后见。 再见! ";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // 计时器
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "是的。 我和尤尔根费了很大功夫, 你带来的数量足够完成修理。 潜水服已修好并准备就绪。 我只需要进行几次测试, 但我确定没问题。 明天上午10点来 --我会给罐子充好气, 你就可以做想做的事了。 ";
				link.l1 = "太棒了! 我很期待。 明天见, 亨利克! ";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "我不得不让你失望了, " +pchar.name+ "。 正如我所料, 金属不够。 我还需要" + FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)) + "块才能完成修理。 我不得不再次请求你的帮助。 ";
				link.l1 = "好吧, 我没料到会这样。 好的, 我会尽力找到你缺少的 Nuggets。 ";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "我会等你。 你可以确信这个数量肯定足够。 只要带来, 我一天就能完成工作。 ";
			link.l1 = "希望如此... 再见! ";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "太好了! 现在潜水服将被修复。 我只需要进行几次测试, 但我确定没问题。 明天上午10点来 --我会给罐子充好气, 你就可以做想做的事了。 ";
			link.l1 = "太棒了! 我很期待。 明天见, 亨利克! ";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "后天";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "明天";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "但我在潜水前必须先找到纳撒尼尔.霍克。 "; // 未与纳撒尼尔交谈过
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "是的, 潜水服已准备好并充好气。 你可以潜水了。 ";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // 未与纳撒尼尔交谈过
			{
				link.l1 = "好的。 但我现在不能潜水, 我需要解决一个关于我的... 朋友纳森.霍克的问题。 我找不到他。 潜水服能等一下吗? ";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "太好了! 我们什么时候开始? 现在? ";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "当然。 可以等。 你不会要找一年吧? ";
			link.l1 = "当然不会。 也许我今天就能找到他。 我一处理完和他的事就来拜访你。 ";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "好的。 等你准备好潜水了再来。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "如果你想的话, 现在就可以。 但先让我给你一个小指示。 你将从‘凤凰’平台开始潜水, 从圣盖博号的船尾可以到达那里。 有一个起重机可以把你送到海底再拉回来。 这是唯一的返回方式\n所以你最好记住水下起重机的位置, 不要迷路。 潜水服的罐子有足够的空气供你潜水二十分钟。 注意时间, 否则你会窒息\n不要离起重机太远, 否则你无法及时返回, 上帝保佑你不要离开我们的浅滩 --你会被压得像比目鱼一样平\n小心螃蟹。 如果你靠得太近, 它们会攻击你。 没必要冒险, 你杀不死一整群螃蟹, 而且在那里快跑也不可能。 ";
			link.l1 = "我会对付螃蟹。 其他的我知道了。 不潜太深, 不离起重机太远, 别忘了时间。 我什么时候可以潜水? ";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "随时可以, 但只能在早上7点到晚上9点之间。 黑暗中你什么也看不见。 ";
			link.l1 = "知道了。 ";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "就是这样。 从平台的房间里拿潜水服。 潜水后脱下, 带给我。 我会再给它充好气。 但不要尝试一天潜水超过一次, 即使是20分钟的潜水和呼吸压缩空气也对你的健康有害。 ";
			link.l1 = "好吧, 那我一天最多潜水一次。 ";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "很高兴你明白。 现在去吧, 祝你好运! ";
			link.l1 = "谢谢! ";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // 首次潜水标志
			pchar.questTemp.LSC.immersion = "true"; // 可以潜水
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // 发放潜水服
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // 找到雕像
			NextDiag.CurrentNode = "after_first_immersion"; // 首次潜水后的节点
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "那么, 你为什么还在这里? 潜水服在等你。 ";
				link.l1 = "是是。 我这就去。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "那么, 第一次潜水怎么样? ";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "非常棒, 我对结果很满意。 我在沉没的圣赫罗尼莫号大帆船里找到了一个石制神像。 我听说里瓦多斯以前会向它献祭。 告诉我, 亨利克, 你知道有谁能告诉我更多关于它的事吗? ";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "很好。 我做到了! 真的很有趣, 虽然有点惊险。 ";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "你对我们的历史感兴趣? 去找安东尼奥.贝坦科特。 他出生在这里。 他住在长笛冥王星号上。 如果他不知道, 就没人知道了。 ";
			link.l1 = "太好了! 我一定会去拜访他。 ";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "把潜水服留在这里。 明天或其他时间再来, 我会给它充好气。 ";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "当然。 这是你的潜水服。 谢谢! ";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "当然。 我马上带来! ";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "那么, 你把我的设备带来了吗? ";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "当然。 这是你的潜水服。 谢谢! ";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "我马上就带来! ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// 启动与螃蟹的迷你任务
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// 潜水块, 除首次外
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // 需要押金
			{
				dialog.text = "是的, 当然。 潜水服已测试并充好气。 你带押金了吗? 50万比索? ";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "是的, 当然。 给, 拿着。 ";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "哎呀! 我忘了。 我马上带来... ";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "是的, 当然。 潜水服已测试并充好气。 像往常一样检查‘凤凰’平台。 ";
				link.l1 = "那我去潜水了。 谢谢! ";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); // 打开凤凰入口
			pchar.questTemp.LSC.immersion = "true"; // 可以潜水
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // 发放潜水服
		break;
		
		case "immersion_next_2":
			dialog.text = "好的。 明天或以后再来。 我会准备好潜水服。 ";
			link.l1 = "谢谢, 机械师! ";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // 退还押金
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "你归还潜水服时会拿回你的钱。 公平交易。 ";
			link.l1 = "谢谢, 机械师! 我现在去潜水了。 ";
			link.l1.go = "immersion_next_1";
		break;
		// 潜水块
		
	//--------------------------------------返回岛屿---------------------------------------------
		case "return":
			dialog.text = "请等一下! 什么雕像? 啊-啊, 我现在明白了。 你是说沉没的‘圣赫罗尼莫’号船上的那个神像, 对吗? 所以那些里瓦多斯的传说都是真的? ";
			link.l1 = "正是! 而且不是传说。 我知道群岛上还有两个神像, 触摸它们的人会被从一个传送到另一个, 按循环传送。 ";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "我明白了, 我明白了。 我得相信你, 尽管你的话是反科学的胡说八道。 传送门。 雕像... 哈! 谁能想到, 这些东西是怎么工作的? ";
			link.l1 = "就相信我, 别试图在这里找任何逻辑。 我没撒谎。 ";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "好吧。 但我希望你在那次传送中没有弄丢潜水服? ";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "当然没有。 可以说它从加勒比人手中救了我。 给你。 ";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "当然没有。 可以说它从加勒比人手中救了我。 但我现在没带在身上。 ";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "那就拿来给我, 该死的! 在你还给我之前我们别说话, 知道吗! ";
			link.l1 = "冷静点, 机械师。 我会还给你的! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "啊, 你真的把我的潜水服带来了! 谢谢, 我开始担心了。 ";
				link.l1 = "没必要担心。 我答应过你会还的。 ";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "在你没带我的潜水服之前别来这里。 ";
				link.l1 = "好, 好。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "非常好。 我开始考虑做一件新的, 但那至少需要一年的工作... 很高兴你表现出良好的节俭, 把我的财产完好无损地还给了我。 我甚至会给你一份礼物。 ";
			link.l1 = "你是认真的? ";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "当然, 我是认真的! 你帮我修理了潜水服, 没有在第一次机会就扔掉它。 你一直在照顾它, 最后把它归还给了我。 不管怎样, 这是一个很好的工具箱。 学会使用它。 你可以用它制作很多有用的东西。 ";
			link.l1 = "从机械师那里还能期待什么呢! 当然, 工具箱! 非常感谢, 亨利克, 我很感动... 我不配得到这样的礼物。 ";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("你收到了一个工具箱");
			PlaySound("interface\important_item.wav");
			dialog.text = "我更清楚你应得什么, 不应得什么。 拿着吧! 它会对你有用的。 但我只会在你抵押50万比索的情况下再把潜水服给你, 因为你有通过神像传送的习惯。 ";
			link.l1 = "哇! 嗯, 我明白... 预防措施... ";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "当然。 如果有一天你带着它逃跑怎么办? 那笔钱将是我的补偿。 ";
			link.l1 = "好的, 亨利克。 我同意。 老实说, 我以为你再也不会把它给我了。 ";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "没机会。 抵押50万, 它就是你的了。 ";
			link.l1 = "成交! 那我可以像往常一样拿它去潜水吗? 从明天开始? ";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "正是。 ";
			link.l1 = "谢谢! 再见, 亨利克! ";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // 潜水服押金
			NextDiag.CurrentNode = "First time";
		break;
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 嗯? 小偷! ", "看看那个! 我一沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会得逞的! ");
			link.l1 = "该死! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子? 你不会得逞的! ";
			link.l1 = "愚蠢的女孩!... ";
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
		
		// 注意到露出的武器
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 它让我紧张。 ", "你知道, 在这里挥舞武器是不被容忍的。 收起来。 ", "听着, 别扮演中世纪骑士到处挥剑。 收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好的。 ", "当然。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你把剑收起来。 ", "听着, 我是这个城市的公民, 我请你把剑收起来");
				link.l1 = LinkRandPhrase("好的。 ", "当然。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 朋友, 带着武器跑。 我可能会紧张... ", "我不喜欢人们在我面前拿着武器。 这让我害怕... ");
				link.l1 = RandPhraseSimple("知道了。 ", "我收起来。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <—— 特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}