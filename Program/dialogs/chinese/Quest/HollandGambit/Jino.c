// 吉诺.格维尼利 - 炼金术士
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> 真理守护者
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "哦! 日安, 先生。 你怎么到这里来的? ";
				link.l1 = "日安, 吉诺。 我们来认识一下。 我是" +GetFullName(pchar)+ "船长, 我在约翰的允许下来到这里。 我得说明白 —我需要你的帮助, 但我也能帮你。 ";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "哦! 日安, 先生。 你怎么到这里来的? 约翰在哪里? ";
				link.l1 = "嗯, 嗯... 原来一直躲在这扇紧闭门后的就是你! 有意思... 关于约翰... 他走了。 现在这房子是我的了。 但别担心。 我们来认识一下, 你是谁, 在这里做什么? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> 真理守护者
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "你好, " +pchar.name+ "。 你的表情告诉我你找到了重要的东西。 你找到真理守护者的所有组件了吗? ";
					link.l1 = "正是! 我把三件物品都带来了: 匕首。 地图和指南针! ";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "你好, " +pchar.name+ "。 发生什么事了? 你脸上的表情很奇怪... ";
					link.l1 = "我有事情要和你谈, 吉诺。 事情很重要。 ";
					link.l1.go = "guardoftruth";
					break;
				}
				// 克索奇特姆
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"。 是的, 我记得, 两天过去了, 你想知道真理守护者的事, 对吗? ";
					link.l1 = "是的, 你说得对! 你能查到什么吗? ";
					link.l1.go = "ksochitam";
					break;
				}
				// --> 葡萄牙人
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "你带了5000比索吗, " +pchar.name+ "? ";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "当然。 给, 拿钱去买你需要的东西。 ";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "不幸的是, 我现在身上没有钱。 ";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "唉, " +pchar.name+ ", 我很抱歉 —病人去世了。 他突然恶化, 很快就过去了。 ";
					link.l1 = "太糟了... 愿上帝怜悯他的灵魂! ";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "你好, " +pchar.name+ "。 发生什么事了? 你看起来很担心... ";
					link.l1 = "吉诺, 我有个不寻常的请求! 我船上有个人发高烧, 他神志不清, 昏迷不醒... 你能帮他吗? ";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+ pchar.name+ ", 我在等病人。 快点, 你把他带来得越早, 我救他的机会就越大。 ";
					link.l1 = "是的, 是的, 他马上就会被送到这里。 ";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "你来得正是时候, " +pchar.name+ "。 他情况危急, 但还有机会。 \n船长, 我快没原料了, 没时间去丛林里收集。 我得从当地草药师那里买, 要5000比索。 你能提供这笔钱吗? ";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "当然。 给, 拿钱去买你需要的东西。 ";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "不幸的是, 我现在没有钱。 ";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//一天内不带钱来 - 葡萄牙人死亡
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "现在我没什么可说的, " +pchar.name+ "。 我在为病人的生命而战, 还有希望。 过会儿再来, 我想很快就能告诉你更具体的情况。 ";
					link.l1 = "好的, 吉诺, 我稍后再来。 ";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "我有消息了, " +pchar.name+ "。 我不敢说你那个人没事了, 但他还活着, 病情在好转, 有起色。 老实说, 我没想到我的药水对他帮助这么大。 ";
					link.l1 = "好消息, 吉诺, 但告诉我什么时候能接他? 我们还有很长的航程, 时间紧迫。 ";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "日安, 船长。 很高兴见到你。 ";
					link.l1 = "我们的病人怎么样了, 吉诺? ";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// < —葡萄牙人
				dialog.text = "日安, 船长。 你好吗? 需要我的帮助吗? ";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "是的。 吉诺, 我觉得你是个博学的人, 也许还懂拉丁语... ";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "我有别的东西。 给你一个小礼物。 看, 这本书。 ";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "是的, 吉诺。 我想给你看这把枪。 你见过这样的东西吗? ";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "我给你带来了我手枪的子弹示例。 ";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "手枪的子弹怎么样了? 有线索了吗? ";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason 海盗系列
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "吉诺, 我在一个船长的日志里发现了一个我不认识的词'gord'。 你知道是什么意思吗? ";
					link.l3.go = "mtraxx";
				}
				link.l9 = "日安, 吉诺。 我很好, 不需要帮助。 只是想看看你, 聊聊天。 ";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason 海盗系列
			dialog.text = "我叫吉诺, 吉诺.格维尼利。 我是科学家, 我的工作是为默多克先生制作粉末。 混合物和其他药物。 但既然他走了... ";
			link.l1 = "嗯, 我是" +GetFullName(pchar)+ ", 自己船的船长。 那么, 你是炼金术士? ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "不仅是炼金术士, 还是医生。 我有相当的医学知识, 了解很多治疗草药, 能从中酿造混合物和药水。 但化学是我的专长, 我做了很多实验, 我的一些发明可能对你这样的人有帮助。 \n我懂拉丁语。 法语。 英语和意大利语。 如果你想像默多克先生那样开药店, 我的帮助必不可少... ";
			link.l1 = "哦! 不是每天都能遇到这么博学的人。 药店生意当然不错, 但我是水手... 嗯, 这听起来甚至有点奇怪... 不管怎样, 我相信我们会成为朋友, 吉诺。 你可以继续住在这里做你的科学研究... ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "如果我需要炼金术士。 治疗师或科学家的帮助, 就知道该找谁了... 告诉我, 你为什么总是待在屋里? 不出去吗? ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "需要买实验材料或草药时我会出去。 我喜欢独处, 这是我的生活方式。 我把一生都献给了科学, 对日常生活没有兴趣。 书。 著作。 试管。 蒸馏器... \n默多克先生给了我这个机会, 作为帮他制药的交换。 ";
			link.l1 = "现在你有更多时间了, 吉诺。 但如果我需要帮助, 你得放下一些实验时间, 成交? ";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "当然, 船长。 如果你不介意, 我会叫你" + GetAddress_Form(NPChar) + "船长? 如果你需要我的实践技能或理论知识, 我会放下所有研究。 ";
			link.l1 = "太好了。 很高兴我们这么快就相互理解了。 别担心费用, 我或我的事务长会不时给你留些合理的钱。 ";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "谢谢, 船长。 我需要的不多... 船长, 我有个想法... 你为什么不学点炼金术技能? 可能对你很有用。 ";
			link.l1 = "嗯。 就像我哥哥曾经说的 —不要羞于学习用双手做事。 所以当然, 为什么不呢。 你能教我什么? ";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "当然, 你不能把铁变成金, 那不可能... 不过, 你可以学习按说明混合原料, 从而得到药水或其他有用的物品。 这里, 拿这个袋子, 里面装着初学者炼金术士需要的一切: 试管。 烧瓶。 蒸馏器。 研钵。 玻璃管。 燃烧器等等... ";
			link.l1 = "太迷人了! ";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("你获得了一套炼金工具");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "制作药水或物品必须知道配方。 配方可以从商人那里买或在任何地方找到。 一旦你研究了配方, 就需要收集所有需要的原料, 并严格按说明操作。 \n使用你的炼金工具, 找或买研钵和研杵, 找坩埚, 可惜我没有多余的给你。 草药。 烈酒。 药水。 矿物。 废料 —只要你有正确的配方和工具, 都可以用。 ";
			link.l1 = "我明白了。 我会在空闲时间试试混合。 谢谢, 吉诺! 能给我一个简单的配方吗? 起点的东西? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "我没有简单的... 但给你这个解毒剂的配方, 我想你能处理这个任务, 拿去吧。 ";
			link.l1 = "感谢! 我会学习的。 现在再见, 吉诺! 照看我的房子, 恐怕我不常来, 所以你不仅可以用你的房间, 还可以用这栋楼的其他地方。 ";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour传奇版本
			Log_Info("你获得了解毒剂配方");
			PlaySound("interface\notebook.wav");
			Log_Info("你需要拥有炼金术技能才能制作药水。 护身符和物品! ");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "是的, 船长, 我懂古罗马的语言。 每个科学家, 尤其是治疗师或炼金术士, 都必须懂拉丁语。 你需要我的拉丁语知识吗? ";
			link.l1 = "是的。 吉诺, 别觉得我傻, 但是... 嗯, 怎么解释... ";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "直说吧, 船长。 别害羞。 ";
			link.l1 = "好吧。 你能给我列一份学者拉丁语格言吗? 你看, 有... 一个喜欢吹嘘自己'博学'的人, 有时他用那些拉丁语短语来显示我比他无知。 比如...'pasem-bellum'... ";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "你是说'Si vis pacem, para bellum'? ";
			link.l1 = "是的, 是的。 我想学习它们来打败我那个傲慢的混... 我的朋友。 ";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "你的请求没什么奇怪或可耻的, 船长。 了解历史上留名的古人格言, 会让你成为一个有教养的人。 给, 拿这个文本, 这就是你要的。 ";
			link.l1 = "谢谢, 吉诺! 很感激! 我会在空闲时间读... ";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("你给了拉瓦锡的化学教科书");
			dialog.text = "给我看看... (阅读) 不可能! 你说'小礼物'? 这本书是无价的! 你从哪弄来的? ! 这是... 真正的宝藏! ";
			link.l1 = "很高兴你喜欢。 ";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = " (阅读) 难以置信! 我从未听说过... 还有这个? 我一点都不懂... 但我会的, 该死的! 哦, 我的实验室很快就会忙起来! " +pchar.name+ ", 你甚至不知道你给了我什么... ";
			link.l1 = "为什么不知道? 我知道。 给科学家的科学书... ";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "但这个奇迹的作者是谁? 安托万-洛朗.德.拉瓦锡, 法国... 从没听说过。 但等等! 怎么可能! 印刷年份是1789年? 但怎么... ";
			link.l1 = "我也不知道为什么上面写着那个年份。 嗯, 也许我知道。 但我建议你别想太多, 书有用, 这才是最重要的。 ";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "这很有前途, 那个年份一定是某种印刷错误... 不管怎样。 非常感谢你, 船长! ";
			link.l1 = "不客气, 吉诺。 它全是你的了。 ";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "不止这些, 吉诺。 我想给你看这把枪。 你见过这样的吗? ";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "我不是枪匠, 但我看看... 不, 我从未见过这样的。 你为什么问? ";
			link.l1 = "这把枪威力大, 有破坏力, 但需要特殊的子弹才能用, 其他都不行。 我不知道怎么多做子弹, 所以来征求你的建议。 ";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "你至少有一颗子弹给我看看作为例子吗? 如果没有, 恐怕我帮不了你。 ";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "有。 子弹由两部分组成: 带子弹的弹体和这个引爆火药的东西。 ";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "真失败! 太遗憾了! 好吧, 也许我会找到更多带来给你。 ";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("你给了左轮手枪子弹");
			Log_Info("你给了火帽");
			PlaySound("interface\important_item.wav");
			dialog.text = "有意思! 看起来简单, 里面有火药, 子弹从上面装进去, 但看起来有点奇怪。 这个'东西'... 嗯。 没有它火药不会爆炸, 对吗? 好奇... 看, 船长, 把这一切都留给我: 手枪和子弹。 一个月后来看我, 我需要时间弄清楚。 ";
			link.l1 = "太好了! 试着弄清楚它怎么工作, 我真的想开枪。 ";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "主要问题是找出引爆火药的这种物质是由什么制成的。 这本书会派上用场, 我会试着弄清楚。 ";
			link.l1 = "好的。 再见, 吉诺! ";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // 定时器
		break;
		
		case "cartridge":
			dialog.text = "是的, 我弄清楚了手枪子弹的成分。 我得感谢你给我的那本书, 没有它不行。 但我得警告你, 船长, 为这武器制作子弹和火帽不容易。 ";
			link.l1 = "火帽? ";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "火帽就是你说的那个引爆火药的'东西'。 但让我们从头开始。 你准备好了吗? ";
			link.l1 = "是的! 我在认真听你说。 ";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "所以, 首先, 你需要制作特殊的子弹, 普通子弹不行。 它必须有某种特殊的锥形。 你得找这种子弹的模具, 我称之为子弹模具。 取普通铅弹, 在坩埚中熔化, 把熔化的铅倒入子弹模具, 冷却铸件, 把成品子弹拿出来。 ";
			link.l1 = "我在哪里能找到这样的子弹模具? ";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "我不知道, 船长。 我是炼金术士, 不是铁匠。 把这颗子弹作为例子, 也许你会知道怎么做。 ";
			link.l1 = "好的。 继续... ";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "然后你得做一个装火药的容器, 把子弹装进去。 我给你写了一份不错的说明, 仔细读, 试试。 ";
			link.l1 = "好的... ";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "现在我们得做火帽。 你需要一张很薄的铜片 —用铜块自己做。 在上面刻出和子弹一样大小的圆圈, 然后用蜡把雷酸银放进去。 ";
			link.l1 = "雷酸银? 那是什么? ";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "我自己也不知道, 我从你的书里学到了这个秘密。 它是一种白色粉末, 由银。 酒精和硝酸制成。 它很容易因摩擦或震动而爆炸, 这就是为什么它很适合点燃你手枪子弹里的火药。 这东西很讨厌, 我测试时爆了两次才想出配方。 ";
			link.l1 = "幸好我带着这本书! ";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "一定要小心, 这东西极其易爆! 我自己可以做一些, 但储存雷酸银太危险了, 必须在制作后立即把它放进火帽里。 我不能做铜火帽, 我之前告诉过你, 我不是铁匠。 ";
			link.l1 = "好的。 把配方给我, 我自己学。 ";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "给你。 严格按照配方, 注意工艺顺序, 否则你会和你的烧瓶一起飞上天。 ";
			link.l1 = "我会小心的。 ";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "还有, 拿这两个烧瓶。 这个里面是硝酸, 这个是酒精。 你可以做足够装满约20个火帽的雷酸银。 ";
			link.l1 = "谢谢你, 吉诺! ";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("你获得了一瓶硝酸");
			Log_Info("你获得了一瓶酒精");
			PlaySound("interface\important_item.wav");
			dialog.text = "再拿上你的手枪和子弹示例。 祝你好运, 船长, 制作子弹时希望你能活着, 完好无损。 ";
			link.l1 = "我会尽力保护自己。 还有, 吉诺, 我告诉过你你是天才吗? ";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "你让我脸红了, 船长, 我是认真的... ";
			link.l1 = "好的。 再见, 吉诺! 你是我最好的炼金术士! ";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason 海盗系列
		case "mtraxx":
			dialog.text = "Gord, gord... 你能告诉我更多关于那个船长的事吗? 他来自哪里? ";
			link.l1 = "不知道, 不过他出生在北方某个地方, 有时人们叫他维京人。 ";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			dialog.text = "维京人! 是的-是的, 我记得, 我在一本历史书里读过。 Gord是自由伯爵的设防定居点。 ";
			link.l1 = "自由伯爵? 那是谁? ";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			dialog.text = "是北方人的王子。 几个世纪前, 自由伯爵和他们的战团曾乘坐他们的龙船 (Drakkars) 袭击和掠夺欧洲。 我想你可以称他们为海盗。 Gord是他们的基地和家园, 在那里他们可以休息。 耕种和宴饮。 ";
			link.l1 = "我明白了。 那么这个gord一定是他的海盗巢穴... 谢谢, 吉诺! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// --------------------------------------- —葡萄牙人 ----------------------------------------------------
		case "Portugal":
			dialog.text = "你说发烧和妄想, 这很有趣。 马上把他送来! 我会看看能做什么。 但如果他情况太糟, 我不能保证什么... 他是你的军官吗? ";
			link.l1 = "不, 谢天谢地, 他不是。 吉诺, 听着, 别问他是谁, 尽你所能, 这对我真的很重要! ";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "好吧, 把他抬进房子到你的房间。 我会准备一些混合物... 也许这种根会... ";
			link.l1 = "我马上把他送来! ";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "那就尽快找到钱, 没有药我治不了他, 如果你不快点, 可能就太晚了。 ";
			link.l1 = "好的, 我会找到钱的。 ";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "太好了, 船长。 现在我来准备一些混合物, 建议你离开我的病人。 明天再来。 ";
			link.l1 = "好的, 吉诺。 我相信你的混合物和你的天才。 ";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//禁止等待
		break;
		
		case "Portugal_4":
			dialog.text = "嗯, 我想他两周后会好起来。 我不能保证他能跳舞, 但至少他肯定能自己站起来。 ";
			link.l1 = "该死, 我没有这两周! 我需要... 尽快起航! ";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "船长, 我不是法师, 我可以向你保证, 现在这个人太虚弱了。 我不确定他能在船上撑几天, 你不能移动他! ";
			link.l1 = "好吧-好吧, 但两周, 不, 甚至一周都太多了! ";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "三天... 是的, 我想三天后你可以试试航行, 但他需要护理和药物, 你必须中途停靠。 ";
			link.l1 = "我有医生, 他会照顾他。 我三天后回来接他, 这是我能承受的最大限度。 我们必须出发, 即使中途停靠... 是的, 还有一件事-吉诺, 你是个天才! ";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "谢谢, 船长。 三天后回来接你的朋友, 但在此之前不要打扰他, 他需要充分休息。 ";
			link.l1 = "好的, 我知道了。 三天后我来接他。 ";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//以免拖延
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "他情况不错, 但进展缓慢。 现在还不能带走。 ";
			link.l1 = "是的-是的, 吉诺, 我记得。 三天... ";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "没有恶化, 但也没真正好转。 他仍然昏迷, 不知道自己在哪里为什么在这里, 不过他好像不太在意。 他还在发烧, 所以我不确定现在带他上船是否明智。 ";
			link.l1 = "我不能再等了, 我们已经在这里太久了。 他还是昏迷的, 虽然这似乎没让他太担心。 他还在发烧, 所以我不确定现在带他上船是否是个好主意。 ";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "等等, 船长! 我治的是个死刑犯吗? 这算什么? 我在这里做了大量工作, 你知道做干粉有多难吗... ";
			link.l1 = "吉诺, 你不需要知道。 别太担心, 他是个海盗, 是同类中最可怕的之一。 我必须尽快带他去库拉索岛, 和公司当局'约会'。 就这样。 ";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "好吧, 你更清楚。 海盗... 库拉索岛。 不管怎样, 听我说, 他大部分时间会睡觉, 但船的摇晃和闷热会影响恢复。 我建议航行几天后停靠, 让你的... 囚犯在陆地上休息。 否则有风险, 他们可能只能在库拉索岛绞死一具尸体... ";
			link.l1 = "好的, 我会的。 马提尼克岛就行, 去库拉索岛差不多半路。 希望风向有利。 我现在就带他走, 我们出发。 再次感谢你, 吉诺。 ";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "不客气, 船长。 记住你有四天, 嗯, 五天, 但不能更多。 还有最后一件事... 你知道, 我通常治病不是为了让他们被治愈后被绞死。 医生对病人负责, 不管他们是谁。 我感觉很不好... ";
			link.l1 = "很抱歉把你卷入这一切, 但没有你我们别无选择。 我们现在必须起航, 否则葡萄牙人的手下会聚集在我们门口迎接他们的老大。 ";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// < —Португалец
		case "guardoftruth_0":
			dialog.text = "有趣... 你怎么帮我? 我不需要帮助, 也没请求帮助... ";
			link.l1 = "但你会需要的。 先听我说, 然后再下结论。 ";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "我洗耳恭听。 ";
			link.l1 = "我最近去了圣地亚哥... 拜访文森特神父。 他在找失踪的秘书, 名叫... 天哪, 你为什么脸色这么苍白, 吉诺? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "你... 见过宗教裁判官? 他是... ";
			link.l1 = "别担心, 吉诺。 我不可能把你交给他, 虽然那是他的命令: 找到你并把你带给他。 我需要获取一些关于伊察族印第安人的信息。 告诉我关于塔亚萨尔。 它的宝藏和其中的'邪恶'。 ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "看来你消息灵通。 是文森特神父告诉你的? ";
			link.l1 = "我从他那里和其他人那里得到了一些信息。 但我想听你说。 你曾是他的秘书, 所以一定记录了审讯过程, 对吗? ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "你无法想象他对那个可怜的印第安人做了什么! ... 每次我想起那次审讯, 就毛骨悚然。 ";
			link.l1 = "尽管如此, 我们还是谈谈吧。 那个印第安人是谁? 他怎么落到文森特神父手里的? ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "他是伊察族印第安人中的一员, 从塔亚萨尔出发寻找库库尔坎面具 —古玛雅神库库尔坎的神器。 那些印第安人遇到了一群由苏格兰寻宝者阿奇博尔德.卡尔霍恩带领的白人冒险家, 只有一个印第安人幸存, 他叫克萨特.查。 他身上有三件有趣的物品, 稍后我会告诉你。 \n卡尔霍恩试图强迫囚犯说出宝藏的事, 但他保持沉默。 于是苏格兰人把他送到圣地亚哥给文森特神父, 以换取在西班牙城市访问一年的许可。 他知道宗教裁判官对各种当地奥秘和传说非常感兴趣。 文森特让印第安人开口了, 他说了很多, 告诉了我们他知道的一切, 我们从他那里得到的信息让宗教裁判官自己都震惊了。 ";
			link.l1 = "你不是在说吧? 什么能让大人颤抖? ";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "我会按顺序告诉你。 在尤卡坦丛林深处有一座古老的玛雅城市叫塔亚萨尔, 居住着玛雅人的后裔 —伊察人。 他们试图按照祖先的规则和传统生活。 当然, 他们不喜欢现代世界的状态 —我指的是白人的统治。 \n他们梦想着过去的美好时光。 现在到了最有趣的部分。 一群白人冒险家意外接近塔亚萨尔, 绑架了伊察人最高酋长的女儿。 这几乎发生在四分之一个世纪前。 \n这是最后一根稻草, 酋长卡内克被激怒了。 他决定进行玛雅最危险和秘密的仪式 —召唤印第安神, 以抹去所有白人征服者的后代... ";
			link.l1 = "嗯... 那一定是文森特神父说的恶魔。 但这个印第安神该如何对付白人殖民者? 以龙的形式出现并烧死他们所有人? ";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "哦, " +pchar.name+ ", 把那些火怪故事留给老奶奶吧! 实际上, 你不算太错, 但我们的情况更困难和严重。 即使洪水也无法阻止欧洲向新世界扩张, 一个人死了会有十个人来代替。 卡内克需要摧毁欧洲殖民化的可能性本身。 ";
			link.l1 = "嗯, 这已经发生了。 ";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "你的思路是对的, 船长... 卡内克仪式的目的不仅是召唤高等存在, 还要创造一个时空空洞。 ";
			link.l1 = "什么? ";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "玛雅古人拥有相当的知识, 船长。 卡内克找到了一个仪式的描述, 允许控制时间。 ";
			link.l1 = "哇! 难以置信! ";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "听着。 仪式的最终目标是改变过去, 使白人出现在新世界成为不可能。 为了做到这一点, 他们打算把某人送回过去, 这个人必须拥有权威。 力量和改变人们命运的能力。 但最重要的是, 这样的人必须拥有现代知识。 \n想想看, " +pchar.name+ ", 如果哥伦布的帆船遇到一支装备现代大炮的印第安护卫舰和大帆船舰队, 会发生什么? 如果白人士兵的火绳枪不是对抗弓箭和长矛, 而是面对迫击炮和滑膛枪, 又会怎样? ";
			link.l1 = "我想美洲根本不会被发现... ";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "正是! 也许某个印第安'哥伦布'会发现欧洲... ";
			link.l1 = "有趣, 卡内克打算把谁送回过去? 他的某个裸体战士? 我怀疑他能教祖先... ";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "别笑, 船长。 卡内克不是在玛雅神庙里浪费岁月读经。 必须以人的形式把印第安神送回过去... ";
			link.l1 = "吉诺, 你在说什么废话? 你是... .";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "甚至我们的主耶稣基督也以人的形式来到我们的地球, 由圣母玛利亚所生... ";
			link.l1 = "天哪, 吉诺... 你是认真的? ";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "当然认真。 克萨特.查很有说服力... ";
			link.l1 = "但卡内克选择了哪个神来执行这个'崇高'的任务? ";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "仪式只打算召唤一位高等存在。 羽蛇神, 魁札尔科亚特尔, 库库尔坎... ";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "库库尔坎? ! 我已经冒昧地见过住在雕像里的他的'灵魂'。 现在我明白了... 继续! ";
			else link.l1 = "嗯。 有趣。 我已经从文森特神父那里听过这个名字... 继续! ";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "卡内克决定召唤库库尔坎, 因为伊察人已经有这个神的古代神器 —库库尔坎面具。 拥有面具的人能够穿过门户, 只有他会被古代玛雅人接受为活神。 \n祭司进行了仪式, 召唤库库尔坎化身到某个凡人的身体里。 他还创造了一个时间空洞, 从未来随机提取了几个人到我们的时间。 \n这个提取的目的是不仅给库库尔坎的化身我们时代的知识, 还要有未来的知识。 但出了问题, 所有那些人都到达了其他地方, 而不是塔亚萨尔。 我从未见过他们中的任何一个。 \n群岛内创建了几个门户, 本应将拥有未来知识的人和伊察特工运送到整个地区和塔亚萨尔。 但这些门户未能达到目的, 过去25年没有人被送到塔亚萨尔... ";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "当然... 因为这些门户只把被俘的人相互传送。 难以置信! ";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "有意思... ";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "你见过那些门户吗? 告诉我! ";
			link.l1 = "也许以后, 吉诺... 目前我对你的故事更感兴趣。 继续! ";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "文森特神父知道我告诉你的一切。 这当然让他担心。 如果库库尔坎以人的形式带着面具和他收集的所有知识到达门户... 世界末日, 天启。 \n如果过去改变 —未来也会改变。 我们的现实将改变, 它将消失, 溶解。 你和我可能永远不会出生, 或者我们会不同。 一旦库库尔坎到达过去 —我们将不复存在。 ";
			link.l1 = "库库尔坎的化身是谁? ";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "谁知道呢。 他可能是任何在仪式进行时出生的人, 比如你... 只是开玩笑。 但我们还有机会。 首先, 库库尔坎的化身只是一个凡人, 他可能淹死。 被刺伤。 被枪击或死于发烧。 在这种情况下, 永远不会有天启。 \n其次, 没有面具不可能到达过去, 卡内克把它藏得很好, 似乎太好了。 可能即使化身的库库尔坎也找不到它。 ";
			link.l1 = "多告诉我些。 ";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "仪式后一段时间, 一群西班牙征服者几乎到达塔亚萨尔, 差点进入宝库。 伊察人设法杀死了所有人, 除了一个 —一个七英尺高的强壮巨人。 \n卡内克担心面具可能被任何陌生人偷走, 所以决定保护这件遗物。 他利用古代玛雅的知识发明了自己的仪式。 他拿了三件他认为拥有白人力量的物品: 一把曾属于科尔特斯本人的匕首, 一个指南针。 他还用那把匕首从被俘的西班牙巨人背上割下一块皮肤作为第三件物品。 这个人自己在库库尔坎的祭坛上被献祭了。 三件物品被用于仪式。 \n从这个仪式中, 在公海诞生了一个新岛屿, 离尤卡坦不远。 没人知道它的位置, 但面具藏在那里。 为了找到它, 必须使用匕首。 指南针和那块皮肤。 此外, 宝库里的所有物品都被诅咒了, 没有一件能离开群岛。 \n试图这样做会引发风暴, 把船带到藏有面具的岛屿的岩石上。 它被称为克索奇特姆。 聪明, 不是吗? ";
			link.l1 = "也许太聪明了。 无可争辩。 但克萨特.查怎么知道这么多? 我怀疑卡内克会和普通战士分享这些知识... ";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "问题是, 伊察人的现任酋长, 卡内克的儿子乌拉坎, 把这一切都告诉了这个战士。 他派克萨特.查和一群战士去寻找秘密岛屿和库库尔坎面具。 他给了他真理守护者来完成这个任务, 这是三件物品的共同名字 —匕首。 指南针和用人皮做的地图。 ";
			link.l1 = "地图? 乌拉坎为什么需要面具? 他决定自己改变过去? ";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "皮肤上有群岛的轮廓, 所以他们称之为地图。 乌拉坎想要面具的原因很简单 —他不想摧毁现有的现实, 不想为古人的荣耀牺牲自己和人民的生命。 \n这就是为什么他打算不惜一切代价摧毁面具。 但克萨特.查被卡尔霍恩俘虏, ... 好吧, 你知道剩下的故事。 他从未到达克索奇特姆。 ";
			link.l1 = "所以可以通过找到并摧毁面具来阻止世界末日? 那个... 真理守护者现在在哪里? ";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "匕首'酋长之爪'和指南针'道路之箭'被留给了卡尔霍恩, 人皮地图'双貌'还在宗教裁判所的某个地方。 卡尔霍恩用它作为堵住囚犯嘴的东西, 他不知道这些物品的用途。 ";
			link.l1 = "你刚才说什么?'酋长之爪'? 该死, 这把匕首现在在我身上! 法迪把它给了我, 作为偿还他对我哥哥的债务! 看看! ";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "难以置信... 真的是。 我记得它。 ";
			link.l1 = "吉诺, 告诉我, 文森特神父对你的故事到底知道多少? ";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "一切, 除了关于真理守护者以及如何让它显示藏有库库尔坎面具的秘密岛屿的位置。 克萨特.查在我给他喝毒药结束他的痛苦之前, 单独告诉了我。 他面带微笑死去。 \n当然, 在我做了那件事后, 我不能留在圣地亚哥。 我严重怀疑自己成了宗教裁判官重要而危险的证人。 文森特神父总是能得到他想要的, 不惜任何代价。 克萨特.查告诉了他塔亚萨尔的宝库。 ";
			link.l1 = "这些宝藏已经被一个叫米格尔.迪乔索的冒险家找到了。 你听说过他吗? ";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "没有。 他现在带着他的宝藏在哪里? ";
			link.l1 = "我自己也想知道。 这就是我来找你的原因, 我在找那些印第安黄金。 迪乔索把宝藏带到了欧洲, 然后带着它们消失了。 ";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "我会告诉你宝藏和迪乔索本人在哪里。 ";
			link.l1 = "吉诺, 你让我惊讶。 你怎么会知道? ! ";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "你自己能从我的故事中弄清楚, 船长。 塔亚萨尔的宝藏被诅咒了 —没有一件物品能被带出群岛。 任何船... ";
			link.l1 = "... 会被风暴困住, 扔到藏有库库尔坎面具的岛上! 我之前瞎了眼, 但现在明白了。 看来我知道足够多的信息来找到克索奇特姆。 宝藏和面具本身! ";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "想拯救世界吗, 船长? ";
			link.l1 = "我想找到我那浪子哥哥... 吉诺, 我怎么让真理守护者显示岛屿的位置? 你说你知道怎么做! ";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "我知道方法, 但不知道细节。 除非我有真理守护者的所有组件, 否则无法帮助你。 ";
			link.l1 = "嗯。 我们已经有了匕首。 只剩指南针和地图了。 卡尔霍恩有指南针, 文森特神父有地图... ";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "你打算回到宗教裁判官那里? 但你怎么报告... ";
			link.l1 = "我得让文森特神父相信你死了, 吉诺。 只有这样他才会停止搜索。 就说你看到我时突然中风了。 你应该给我一件我能用作你死亡证明的物品。 ";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "文森特不会相信心脏病发作的说法, 但如果你告诉他我喝了某种有杏仁味的毒药自杀了, 他会相信你。 把我的年鉴给他, 他知道我从不离身。 ";
			link.l1 = "好的。 因为我需要和宗教裁判官保持联系, 他可能对我们的事知道很多。 ";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "小心文森特神父。 他像老虎一样危险, 有自己的算盘。 他不会和你分享宝藏或名声。 ";
			link.l1 = "我明白。 好的, 吉诺, 把你的年鉴给我, 试着记住印第安人告诉过你的关于真理守护者的一切, 因为我想组装它。 我需要找到克索奇特姆, 我确信在那里不仅能找到面具和宝藏, 还能找到我亲爱的哥哥。 ";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "拿去吧。 祝你好运, 船长! ";
			link.l1 = "我不说再见, 吉诺... ";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("你获得了一本年鉴");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "难吗, 船长? ";
			link.l1 = "我们别谈这个了... 为了得到这些物品, 死了太多人。 太多了。 看来我不是唯一渴望找到神秘的克索奇特姆的人。 ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "可以想象... 顺便问一下, 文森特神父怎么样了? 你经常和他联系吗? ";
			link.l1 = "到目前为止是的, 但我想没必要再这样了。 我有了真理守护者的所有组件, 这意味着我拥有了找到克索奇特姆位置的钥匙。 不知为何, 我不想向大人报告我的成功。 ";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "小心, " +pchar.name+ "。 文森特神父有数百只眼睛和手, 非常长的手... ";
			link.l1 = "过去几个月我经历了很多, 现在我当然不怕文森特神父, 也不怕他的眼睛和手。 不管怎样。 现在我们该用真理守护者的组件找到克索奇特姆了。 你知道怎么做吗? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "不太清楚。 克萨特.查说得很含糊。 我想那个印第安人其实不知道如何让真理守护者工作。 把组件留给我, 我会试着弄清楚。 两天后来看我, 也许我能解开这个谜。 ";
			link.l1 = "好的, 吉诺。 我指望你了。 给, 拿着它们。 ";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "你可以放心, 它们在我这里会安全无损。 ";
			link.l1 = "我不怀疑。 好吧, 现在不打扰你了, 吉诺。 祝你研究顺利! ";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "部分知道。 我的意思是, 我找到了一些线索, 但不知道如何真正让它起作用。 我们一起试试解开这个谜吧。 ";
			link.l1 = "我们试试! 说说你的想法。 ";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "克萨特.查说过类似的话:'酋长之爪会让地图显露自身, 道路之箭会指明Appearance的方向.'";
			link.l1 = "你设法做了什么? ";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "我猜到了如何让地图'显露'自身。 你看过'双貌地图'吗? ";
			link.l1 = "嗯。 有什么特别的吗? 一些模糊的群岛轮廓... ";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "拿着再看一遍, 仔细点。 ";
			link.l1 = "好吧, 如果你坚持的话。 ";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//关闭地点
		break;
		
		case "ksochitam_wait":
			dialog.text = "你还没看地图, " +pchar.name+ "... ";
			link.l1 = "是的-是的, 我现在就看... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "我看了。 没看到新东西, 只是一些模糊的岛屿和大陆形状。 我该看什么? ";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "等一下。 现在你得让这张地图显露自身。 拿起匕首, 用刀刃轻轻触摸地图, 不要用力, 我们需要避免任何损坏。 拿起匕首, 仔细看! ";
			link.l1 = "有意思! 让我看看... ";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "那么, 你现在看出什么不同了吗? ";
			link.l1 = "是的。 当你用匕首触碰地图时, 两个骷髅标记会出现, 而且总是在相同的位置... ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "在两个相同的位置, " +pchar.name+ "! 这就是为什么它被称为‘双貌地图’! ";
			link.l1 = "这是什么意思? ";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "我觉得意义重大... 但接下来还有更多谜题。 我认为这些骷髅就是克萨特.查所说的‘表象’。 所以指南针必须从这些位置指向克索奇特姆的正确方向。 你见过那个指南针吗, " +pchar.name+ "? ";
			link.l1 = "见过。 它看起来像普通的航海指南针, 但表现很奇怪, 指针会向不同方向抽搐, 或者开始疯狂旋转。 ";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "我本以为把指南针放在骷髅标记上会让指针停止, 并在地图上显示明确的方向。 为了做到这一点, 我把它放在一个骷髅上, 然后在匕首触碰地图时再放在另一个上。 ";
			link.l1 = "然后呢? ";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "徒劳无功。 指南针的行为没有改变, 指针仍在疯狂旋转。 看来我做错了什么, 或者误解了克萨特.查的话。 ";
			link.l1 = "所以匕首和地图有用, 指南针没用? ";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "‘道路之箭’肯定是可用的, 我们只是还不知道如何操作。 " +pchar.name+ ", 你比我更了解群岛的地理... 告诉我, ‘双貌地图’显示的是哪些地方? ";
			link.l1 = "等一下! (查看地图) ... 嗯 —嗯... 左边的表象是西部大陆, 右边的看起来像多米尼加岛, 差不多是这样。 ";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "告诉我: 这些地方有什么显著之处吗? ";
			link.l1 = "你是什么意思? ";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "我自己也不确定... 嗯, 有什么特别的吗? ";
			link.l1 = "吉诺, 别打哑谜, 简单解释一下。 ";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "我只能推测这些骷髅向我们展示了一些真实的地点。 ‘道路之箭’放在地图的表象上不起作用, 也许在地图显示的真实地理表象附近会起作用? ";
			link.l1 = "吉诺, 你真是个天才! 西部大陆, 多米尼加? 但骷髅标记太大了, 无法显示精确位置。 ";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//打开地点
			dialog.text = "" +pchar.name+ ", 我们这样做: 给我带一张群岛的纸质地图, 与‘双貌地图’叠加, 用十字标记出这些表象。 也许这能让你有一些推测? ";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "我有这张古老的群岛地图。 ";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "我有这张精细的群岛地图。 ";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "我有这张精美的群岛地图。 ";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "成交。 我会给你带张地图, 然后我们继续... ";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "哦, 得了吧, " +pchar.name+ "! 这张哥伦布时代的羊皮纸并不比人皮地图好多少。 我肯定世上有比这垃圾更好的地图。 给我另一张更新的! ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "太好了! 现在在上面标记出表象的位置, 这将更容易进行推测。 ";
			link.l1 = "稍等, 吉诺! ";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "我们不能用这样精美的地图来做标记, " +pchar.name+ "。 你自己会需要它的。 给我另一张更普通的地图! ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "你给我带群岛地图了吗, " +pchar.name+ "? ";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "我有这张古老的群岛地图。 ";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "我有这张精细的群岛地图。 ";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "我有这张精美的群岛地图。 ";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "还没有, 但我已经订购了。 很快就会有, 我们继续... ";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "完成了... 我已经做了标记, 但信息仍然不准确。 第一个地点在布鲁维尔德西北部某处, 第二个在多米尼加岛中心。 ";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "有什么想法吗? ";
			link.l1 = "没有。 但我认为我们应该把‘道路之箭’带到那里, 观察它的行为。 当然, 这就像大海捞针, 但我们也没有更好的主意了。 ";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "我同意你的看法, " +pchar.name+ "。 你能让我和你一起航行吗? ";
			link.l1 = "你有兴趣验证你的推测吗? 吉诺, 能邀请你到我的船甲板上是我的荣幸。 收拾东西! ";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "不会花太多时间, 我几小时后就准备好。 给, 拿着‘道路之箭’。 ";
			link.l1 = "欢迎登船! ";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//打开地点
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "是的 —是的, " +pchar.name+ ", 我在做准备, 很快就好。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "那么, " +pchar.name+ ", 我们的搜索有收获吗? ";
			link.l1 = "我们是对的, 就是这里。 印第安神像是其中一个表象。 ";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "哦! 这一定是那些本应把人传送到塔亚萨尔的神像之一! 我告诉过你, 记得吗? 那么, ‘道路之箭’指向哪里? ";
			link.l1 = "指向西北。 我在地图上标记了方向, 尽管这条线几乎穿过整个加勒比海。 我们必须在多米尼加找到另一个表象来定位克索奇特姆。 ";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "我相信我们会在那里找到另一个神像... 你同意我的假设吗, " +pchar.name+ "? ";
			link.l1 = "我同意, 吉诺。 现在别浪费时间, 开始搜索吧。 ";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //开启遭遇战
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "那么, " +pchar.name+ ", 你发现什么有趣的东西了吗? ";
			link.l1 = "我们是对的, 就是这里。 印第安神像是其中一个表象。 ";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "哦! 这一定是那些本应把人传送到塔亚萨尔的神像之一! 我告诉过你, 记得吗? 那么, ‘道路之箭’指向哪里? ";
			link.l1 = "西北。 我在地图上标记了方向, 尽管这条线几乎穿过整个加勒比海。 我们必须在大陆找到另一个表象来定位克索奇特姆。 ";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "那么, " +pchar.name+ ", 你找到第二个神像了吗? ";
			link.l1 = "是的。 我已经画出了‘道路之箭’指示的方向。 现在我们知道克索奇特姆的位置了, 虽然不是精确位置, 但我们知道去哪里搜索! 我会搜索线交叉的整个区域, 一定能找到那个该死的岛屿! ";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "很高兴听到你声音里的热情。 但我们必须为即将到来的探险做好准备, 不知道在那里会面对什么。 我怀疑我们不会受到欢迎... ";
			link.l1 = "你是在担心具体的事情, 还是只是表达担忧? ";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "想想看, " +pchar.name+ "... 克索奇特姆是卡内克用玛雅魔法创造的, 它不是自然形成的, 上面有邪恶和毁灭的力量。 不知道我们在那里会遇到什么, 我怀疑不会有阳光。 平静的海洋。 妓女和顺风。 ";
			link.l1 = "好的, 吉诺。 我会考虑你的话, 为探险做好准备。 我会准备好我的船, 准备好药水和弹药... ";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "非常明智的决定。 那么, 我们回船上吧? ";
			link.l1 = "当然! 走吧! ";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "我们到了, " +pchar.name+ "! 呃, 风在呼啸! ";
			link.l1 = "是的, 吉诺, 你说得对, 没有阳光迎接我们... 也没看到妓女。 实际上, 根本不知道这里等待我们的是什么。 ";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "好吧, 船长, 你选了个糟糕的登陆点! 到处都是岩石和悬崖! 你打算怎么从这里进入岛内? ";
			link.l1 = "因为该死的风暴, 我没看到岛上其他合适的海湾! 不管怎样, 这总比什么都没有好。 我会在这些岩石中找到路, 我经历过更糟的。 别慌, 朋友! ";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "我不喜欢这个岛, " +pchar.name+ "! 它很诡异, 而且这场风暴一定和岛屿有关。 这个地方肯定被诅咒了! ";
			link.l1 = "我也不太喜欢这个地方, 吉诺! 但这个岛确实存在, 这意味着库库尔坎的故事是真的。 如果他带着面具到达塔亚萨尔, 我们都将处于危险之中... ";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "试着找到面具, 船长! 这比世界上所有的宝藏都重要! 它一定在附近某个地方! 一旦我们拿到它, 就会摧毁库库尔坎的计划, 不让他改变过去! ";
			link.l1 = "那面具长什么样, 你知道吗? ";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "不知道! 但我想你会认出来的, 它是古代印第安神器, 很难和其他东西混淆! ";
			link.l1 = "我明白了。 我会留意的! 好了, 吉诺, 回船上吧! 你不必在岛上走动, 你的头脑太宝贵了, 不能冒险! ";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "不瞒你说, 船长, 我战斗很烂, 在这个地方也不舒服。 想听听建议吗? 真理守护者的每个组件都与这个岛的魔法相连。 克萨特.查提到匕首对当地居民有力量, 不过我不知道他是什么意思。 \n我会待在船上, 如果你需要帮助, 到那里找我。 ";
			link.l1 = "好的。 现在祝我好运吧, 吉诺! ";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "祝你好运, " +pchar.name+ "! 愿上帝保佑你! ";
			link.l1 = "... ";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "你怎么样, " +pchar.name+ "? 需要建议吗? ";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "这个该死的岛上爬满了不死生物, 那些骷髅出乎意料地强壮, 我不知道怎么对付它们。 ";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "如果你从岔路口向左走, 最终会到达洞穴。 但接下来我该去哪里? 恐怕洞穴是死胡同... ";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "我找到了进入湿洞穴的路, 你可以潜入水下部分, 但我没看到那里有出口... ";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "如果你从岔路口向左走, 会到达洞穴。 但接下来我该去哪里? 恐怕洞穴是死胡同... ";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "在大洞穴里有个地方可以潜入被淹没的部分, 但似乎没有出路... ";
				link.l1.go = "adversary_5";
			}
			link.l10 = "到目前为止一切顺利, 吉诺, 我很好。 ";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "克萨特.查提到过‘酋长之爪’。 试着用它对付骷髅, 印第安人说这把匕首对克索奇特姆的居民有力量。 ";
			link.l1 = "我肯定会试试! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "那个洞穴是什么样子的? ";
			link.l1 = "嗯, 岩石中有个小洞穴, 很潮湿, 底部的水像海浪一样晃动... ";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "如果水在晃动, 那么洞穴与大海有连接, 不可能是死胡同。 寻找通道, 一定存在。 ";
			link.l1 = "这就去... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "如果从主洞穴可以进入被淹没的洞穴, 且主洞穴的水像海浪一样晃动, 那么被淹没的洞穴有第二个通道。 仔细搜索, 但要小心, 否则会淹死。 ";
			link.l1 = "我要潜水... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "那个洞穴是什么样子的? ";
			link.l1 = "嗯, 它相当大, 有几个洞室, 很潮湿, 有一个静止的小水坑... ";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "如果水是静止的, 那么洞穴与大海没有连接, 可能是死胡同。 ";
			link.l1 = "我也这么想。 我在那里搜索了很久, 只有一个出入口... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "如果洞穴里的水是静止的, 也许你是对的。 再搜索一下, 但如果什么都找不到也别难过, 很可能是死胡同。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = "" +pchar.name+ ", 西班牙船在追我们! 现在不是谈话的时候! ";
			link.l1 = "是的, 当然... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "你喜悦的眼神告诉我, 你找到了要找的东西。 ";
			link.l1 = "是的。 米格尔.迪乔索的宝藏和库库尔坎面具。 现在他的化身永远无法改变未来了! ";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "难以置信! 你是英雄, " +pchar.name+ "... ";
			link.l1 = "吉诺, 你确定这足以阻止库库尔坎吗? ";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "根据克萨特.查的说法 —是的, 他引用了乌拉坎的话。 是他的父亲卡内克引发了这一切。 有疑问吗? ";
			link.l1 = "我在海湾遇到了一位来自过去的客人 —阿隆索.德.马尔多纳多。 卡内克进行创造真理守护者的仪式时, 他在塔亚萨尔。 他被卷入时空空洞, 但活了下来... 直到今天。 ";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "他说我必须关闭传送门本身, 才能永远保护我们的世界。 为此, 我必须在塔亚萨尔的某个祭坛上摧毁面具。 ";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "你要去塔亚萨尔? 这太疯狂了! " +pchar.name+ ", 你已经拿到面具, 库库尔坎的化身什么也做不了! 卡内克自己也确信这一点! 这就是为什么乌拉坎派克萨特.查去寻找克索奇特姆 —拿到面具并摧毁它。 ";
			link.l1 = "如果这个乌拉坎打算在塔亚萨尔摧毁面具呢? ";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = "" +pchar.name+ ", 到目前为止只有一个人活着逃离塔亚萨尔, 那就是米格尔.迪乔索, 马尔多纳多也是例外。 即使库库尔坎的化身回到过去, 也会被古代玛雅人杀死! ";
			link.l1 = "如果他们不杀他, 而是认出他呢? ";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "那么你计划远征塔亚萨尔? ";
			link.l1 = "我不知道, 吉诺, 我真的不知道... ";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "那么想想, 你为什么要这么做? 你已经听过我的意见, 现在由你决定... " +pchar.name+ ", 你能带我去圣约翰吗? ";
			link.l1 = "当然, 吉诺。 我们尽快起航, 我受够了这个可怕的岛。 ";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "我们很快就回家了吗, " +pchar.name+ "? 我真想念我的烧瓶和试管... ";
			link.l1 = "是的 —是的, 吉诺, 很快就到安提瓜了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "很高兴我们终于回来了! 我无法想象你们水手怎么在船上花这么多时间... ";
			link.l1 = "这是习惯问题, 吉诺。 ";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "我会很高兴躺在坚实地面上的床上... 我希望, " +pchar.name+ ", 你已经放弃了访问塔亚萨尔的想法? ";
			link.l1 = "我还不知道, 吉诺。 说实话, 我仍然不确定。 ";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "摧毁库库尔坎的面具, 无忧无虑地生活吧, 船长。 如果你愿意, 我们会用我最强的酸溶解面具, 我不会为此介意。 ";
			link.l1 = "你知道, 我会等一段时间, 我们总有时间摧毁它。 ";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "这是你的选择。 如果你决定让世界免受这件神器的影响 —来找我。 感谢这次美妙的航行, 船长! ";
			link.l1 = "随时, 吉诺。 回头见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是个" + GetSexPhrase("小偷, 先生! 卫兵, 抓住他","小偷, 女士! 卫兵, 抓住她 ") + "!!! ", "看看那个! 我一陷入沉思, 你就想检查我的箱子! 抓住小偷!!! ", "卫兵! 抢劫! 抓住小偷!!! ");
			link.l1 = "该死! ";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}