// 查理的兄弟, 米歇尔.德.蒙佩, 又名迪霍佐, 又名库库尔坎的化身, 又名大反派
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "欢迎你, 航海者查理! 我听说了你在马提尼克岛东海岸击败那些海盗的所有事迹。 现在我完全确定, 我对你的看法没错, 兄弟。 ";
				link.l1 = "那些混蛋设下了陷阱抓住了我。 但他们低估了我们。 我的领航员。 我的船员和我最终占了上风。 不过我得承认, 亲爱的兄弟, 一开始... 情况看起来很糟糕。 ";
				link.l1.go = "trial";//中间阶段
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "你好, 兄弟! 我欣赏你想把我从这里救出去的真诚热情, 但你还没准备好进行下一步。 我的计划需要一位经验丰富的船长。 继续探索加勒比海, 赚取奖励并学习! 等你准备好了, 我们再继续。 ";
						link.l1 = "好吧, 不管你怎么说, 兄弟。 你坐在这儿, 又不是我。 ";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "很高兴见到你, 兄弟。 别忘了你对别人的承诺。 一旦你有空, 我就会等你 --我对我们的下一步有想法! ";
						link.l1 = "知道了, 兄弟。 我会抽出时间处理我的承诺, 但我很快就会回来! ";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("需要12级");
					dialog.text = "航海者查理! 听说了你的冒险经历! 你几乎准备好执行我计划的下一阶段了。 一旦你获得更多经验, 就回来。 ";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "你好, 兄弟! 我欣赏你想把我从这里救出去的真诚热情, 但你还没准备好进行下一步。 我的计划需要一位经验丰富的船长。 继续探索加勒比海, 赚取奖励并学习! 等你准备好了, 我们再继续。 ";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "很高兴见到你, 兄弟! 听说你在取得进步! 但你还没准备好我计划的下一步。 继续做你一直在做的事, 等你准备好了再回来找我。 ";
						}
					}
					link.l1 = "好吧, 不管你怎么说, 兄弟。 你坐在这儿, 又不是我。 ";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "我不这么认为, 兄弟。 也许你已经习惯了这个牢笼, 但我不打算在这里久留 --我们的父亲不能永远等下去。 说出来吧。 ";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "下午好, 查理。 看到你让我心生喜悦: 你肯定在向好的方向转变。 ";
					link.l1 = "是这样吗? 你怎么看出来的? ";
					link.l1.go = "gambit";//跳转到甘比
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//标志: 甘比已完成或失败
			{
				dialog.text = "我明白了。 我知道你有消息要告诉我, 查理! 那么, 是什么消息? 希望不是什么糟糕的事吧? ";
				link.l1 = "我听从了你上次给我的建议... ";
				link.l1.go = "saga";//跳转到传奇
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//标志: 甘比在所有三个选项上都失败了
			{
				dialog.text = "你终于来了... 有什么消息吗, 亲爱的兄弟? ";
				link.l1 = "我听从了你上次给我的建议... ";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//传奇已准备好开始
			{
				dialog.text = "很高兴见到你, 查理! 你见过德.潘西骑士了吗? 你们的会面怎么样? ";
				link.l1 = "是的, 亲爱的兄弟。 我们见过面了。 我有两个消息要告诉你, 一个好消息和一个坏消息。 我先说好消息。 我已经处理了你欠德.潘西的债务。 坏消息是, 在我履行你承诺的与某个异教徒解决问题之前, 他不会释放你... ";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason 海盗线
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // 海盗线失败或未完全完成
			{
				dialog.text = "你在拉维加怎么样, 兄弟? ";
				link.l1 = "真的没什么可吹嘘的。 泰瑞克斯是个有趣的人, 但他的做事方式就是不适合我。 ";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // 海盗线失败或未完全完成, 但接下来有4个任务
			{
				dialog.text = "你在拉维加怎么样, 兄弟? 我听到了一些传言, 说实话, 我对此并不高兴... 查理.普林斯。 ";
				link.l1 = "我想我知道那些传言是关于什么的。 但那都是过去的事了。 我不再和泰瑞克斯合作了, 这份工作对我的口味来说太肮脏了。 ";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // 海盗线完全完成
			{
				dialog.text = "那么, 问候你... 海盗查理.普林斯。 告诉我, 查理, 你怎么会堕落到如此地步? 我简直不敢相信。 我那个有一次我提到掠夺西班牙商船时会做鬼脸的兄弟, 现在成了这个地区最受通缉和最危险的海盗之一! 即使是我, 坐在这里深陷困境, 每次听到你的恶名都会脸红。 我诅咒我派你去拉维加的那一天。 真遗憾! 一个法国贵族加入了海盗, 并且这么短时间内就成了他们中最坏的一个! 现在怎么办, 兄弟? 你是在寻找海盗男爵的空缺吗? ";
				link.l1 = "不。 我永远不再当海盗了。 ";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "还有什么, 查理? 我想我们已经讨论了所有事情。 时间就是金钱, 亲爱的兄弟 --赶紧吧! ";
			link.l1 = "是, 是, 我这就走... ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "查理! .. 很高兴见到你, 兄弟! 当然, 我明白你很难相信, 但你在这里我他妈的很高兴... ";
			link.l1 = "哈! 看看他! 他很高兴! 所以当你骑着你的‘教团’高头大马时, 查理是家族的耻辱, 一个微不足道的艺术家, 靠交际花的钱生活, 还是个宫廷‘骑士’, 嗯? 但现在你被自己的同志关进了监狱, 你‘他妈的很高兴’见到你这个一无是处的兄弟! ";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "查理, 你... ";
			link.l1 = "我还没说完呢! 你为什么要向法国报告关于你自己的任何事情? ! 你被剥夺了通信权吗? ! 我们的父亲因为担心你而完全病倒了! 他让我至少查明你的命运... ";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "查理, 我该用什么话来告诉父亲我发生了什么事? 我该给他写什么? 不, 兄弟, 不管有多难, 最好现在不让父亲知道任何事情。 而且给你写信也没用 --你在巴黎总是在不同的地址... 你是怎么找到我的? ..";
			link.l1 = "在父亲的恳求下, 我去了马耳他。 在那里, 我从你的朋友德.拉.布里尼亚骑士那里得到了一些信息。 他写信给我讲了你的问题, 说你可能在马提尼克岛的某个地方。 然后我回到法国看望了父亲。 在那之后, 我来到了这个炎热的地狱, 这里的蚊子简直把人咬得半死... ";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "你把这一切都告诉父亲了吗? ";
			link.l1 = "没有。 而且德.拉.布里尼亚骑士没有回复他的信, 担心会有可悲的后果... 父亲仍然不知道你的命运。 我决定找到你, 弄清事情的真相。 告诉你吧, 我来马提尼克岛不是为了你, 而是为了我们可怜的父亲! ";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "真的吗? 查理, 你什么时候关心起你的家人了? 说实话, 兄弟, 巴黎的每个人都知道你父亲是谁。 你可能拥有德.莫尔家族的姓氏, 但你不想让德.蒙佩的名字蒙羞。 \n因为在那种情况下, 你将无法利用你的血统来告诉每个人关于你英雄事迹的虚构故事, 对吗? 巴黎最好的房子的大门将对你关闭, 他们不会让你靠近卢浮宫一英里以内。 \n你真的相信你的交际花和情妇们 --她们的丈夫在战场上为我们的祖国而战时, 你让他们戴绿帽子 --会很高兴地欺骗她们的主人和老爷, 和我这样一个国家罪犯的兄弟在一起吗? \n我猜你是直接从某个已婚女人的床上来到这里的, 对吗? 查理, 你的脸怎么了? 我说到痛处了吗? ";
			link.l1 = "你... 你! ..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "好了, 兄弟。 我们已经互相指责过了, 够了。 我承认我不完美。 但你也不是天使。 查理, 现在真的不是吵架的时候。 我们都有相同的目标, 那就是拯救蒙佩家族的荣誉和尊严... 不管我们的动机是什么。 兄弟, 在我们的生命中, 就这一次, 让我们用和平取代敌意。 成交? ";
			link.l1 = "我们试试吧... 但你能向我解释一下你被指控什么吗? ";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "官方说法是关于社团资金的支出问题。 实际上, 事情要复杂得多。 ";
			link.l1 = "那么, 你挪用了你的组织的钱? 好吧... ";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "我告诉过你那些是官方指控。 我没拿一分钱。 事情是这样的... 你看, 只要我还在坐牢, 我就不能详细向你解释一切。 我没有道德权利泄露我们社团的秘密。 ";
			link.l1 = "请试着解释一下, 亲爱的兄弟。 我有权知道, 不是吗? ";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "好吧。 我曾收到一笔钱, 用于一项非常危险和微妙的行动, 该行动本应改变加勒比海的政治平衡。 我是按照法属殖民地总督菲利普.德.潘西的直接命令行事的。 但尽管我尽了一切努力, 行动还是失败了。 \n德.潘西因为他所有的长远计划都泡汤而大发雷霆。 他亲自签署了逮捕我的命令, 并确保其执行。 然后他来到这里, 宣布如果我的亲属或我不归还用于该行动的资金, 他将指控我挪用公款和背叛教团。 ";
			link.l1 = "真是太好了。 据我了解, 我们家族不得不为你的失误支付的这笔钱在哪里? ";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "这笔钱用于准备行动。 贿赂。 组织探险队。 购买各种商品和设备。 我的开销相当大。 就像我说的 --我没拿一分钱。 ";
			link.l1 = "那么要求的金额是多少? ";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "一百万。 ";
			link.l1 = "该死的! 你在开玩笑, 对吗? ! ";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "我看起来像是在开玩笑吗? 不, 亲爱的兄弟, 这是残酷的事实。 我们需要给德.潘西送去一百万比索。 ";
			link.l1 = "但该死的! 我们家族根本没有那么多钱! 我们二十年也凑不到那么多! ";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "如果我没有被监禁, 并且不受我对社团的义务的限制, 我最多在六个月到一年, 最多一年半内就能赚到。 查理, 这是新世界。 这里的一切都不同。 一个有动力。 有野心的人可以在这里发财, 而不必像在欧洲那样奉献一生。 ";
			link.l1 = "半年内一百万? ! 你疯了吗? 如果你这么确定, 那你为什么不告诉你的德.潘西? 让他释放你。 全力以赴... ";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "哦, 别胡说八道了, 查理! 潘西不可能把我从这个牢房里释放出来。 如果那么容易, 我就不会请求你的帮助了。 ";
			link.l1 = "所以我必须为你的自由筹集资金? ! ";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "不仅仅是我的自由。 或者你忘了? 我们要不要回到关于宫殿。 舞会和与贵族妓女上床的谈话? 是的, 查理, 你必须这么做。 当然, 如果你想继续像以前一样在巴黎过着浮华的生活。 你愿意, 不是吗, 兄弟? ";
			link.l1 = "但该死的, 我到底该去哪里弄这笔钱? 你知道这附近有什么老林子, 里面长的是金路易而不是树叶吗? ";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "整个新世界就是一片金钱树的丛林, 但人们太懒了, 不愿抬起他们愚蠢的头, 伸出手去够树枝。 别担心, 查理, 你会做得很好的。 我从童年就认识你, 如果我认为你愚蠢或懒惰, 我就不会浪费时间说服我们的父亲派你到这里来。 \n尽管我之前提到了你的缺点, 但你勇敢。 有野心。 聪明, 你很会说话, 而且你知道如何使用细剑, 这在这里是一项极其重要的技能... ";
			link.l1 = "非常感谢。 我亲爱的兄弟真的屈尊给我赞美了吗? 我还以为我只是个可怜的艺术家。 廷臣... ";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "别废话了。 我们达成协议了吗? ";
			link.l1 = "对不起, 兄弟。 话脱口而出了。 我只是不太习惯从你那里听到这些话。 这就像一个街头妓女在宣讲拯救灵魂。 ";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "我们继续吧, 兄弟。 正如我所说, 你拥有在这里取得成功所需的一切。 不仅如此, 你并不孤单。 我会帮助你, 告诉你该做什么以及如何正确去做。 听我的, 我们会成功的。 相信我, 你找不到能取代我经验的人。 你准备好停止说废话, 终于切入正题了吗? ";
			link.l1 = "是的, 看来我要在这里待一段时间了... 好吧。 我洗耳恭听, 米歇尔。 ";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "是的, 兄弟, 你要在这里待一段时间。 很高兴你现在能明白这一点。 所以如果有哪个交际花在巴黎等你回来, 我建议你忘了她。 但别难过, 当地女孩有她们自己的魅力。 \n不过, 她们喜欢真正的男人, 强壮。 有冲劲, 甚至粗鲁。 所以如果你要和某个殖民地女孩上床, 别指望有诗歌。 关于绘画的讨论或月下散步。 她们不会喜欢的。 ";
			link.l1 = "好吧, 兄弟。 你是被夸夸其谈击中了吗? 我们切入正题吧。 我愿意听取你的建议, 但不是你那些肮脏的暗示。 ";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "太好了。 为了让你取得任何成功, 你需要拥有一艘船。 加勒比海是一个群岛。 你知道这一点, 对吗? 生活与海洋交织在一起。 拥有自己船只的人有无限的赚钱潜力。 ";
			link.l1 = "但我不是水手! ";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "那么, 是时候成为一名水手了。 反正你也别无选择。 你没想过成为港口办公室职员或在驻军登记吧? 没有? 那你就当船长。 ";
			link.l1 = "我的职业生涯发生了怎样的转折啊! 我在哪里能找到一艘船? ";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "我们当地的造船厂有一艘很棒的小帆船在等着。 它不大, 但却是一艘非常舒适的船, 非常适合作为水手的第一步。 这艘小帆船是专为我建造的。 在朋友们的帮助下, 我为这艘船支付了五千比索的定金。 你去找造船匠, 告诉他是米歇尔.德.蒙佩派你来的。 他会明白你的来意。 ";
			link.l1 = "这艘船只值五千? 那有点奇怪... ";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "兄弟, 你在听我说话吗? 五千只是定金。 这艘小帆船的价格大约是两万比索。 所以你得自己赚剩下的钱。 除此之外, 你还需要钱来雇佣船员和领航员。 ";
			link.l1 = "太好了! 那我怎么弄到这笔钱? ";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "这并不奇怪。 赚钱。 不然还能怎样? 在这里, 钱就在每棵树后面, 你只需要知道去哪里找, 并且不惧怕逆境。 在这附近的不同场所走走。 和当地人谈谈。 你肯定会得到某种工作。 但要小心, 这里的骗子比诚实的人多得多。 如果你不是诚实的人, 你可以试着从房子里偷些有价值的东西。 ";
			link.l1 = "但我们是贵族, 对吧? ";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "在这里, 头衔一文不值。 像其他人一样工作。 战斗。 偷窃。 你买船后, 雇佣船员。 一开始你自己无法驾驶船只, 所以你需要一名领航员。 你可以和酒馆老板谈谈所有这些, 他会帮助你。 当然, 确保你不会迷路。 当你出海时, 直接起航前往瓜德罗普... ";
			link.l1 = "那是什么? 一个城镇? ";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "那是一个离这里将近两天路程的岛屿。 尽快弄到一张群岛地图, 并像背诵‘主祷文’一样学习它, 这样你就不会在每个能区分城镇和岛屿的人面前看起来像个傻瓜。 你将不得不多次航行经过群岛, 所以提前做好准备。 ";
			link.l1 = "嗯。 好的。 那么我在这个, 呃... 瓜德罗普岛上做什么? ";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "在那里找一个名叫‘法迪’的人。 他在码头附近有自己的房子。 告诉他你认识我, 并要求他偿还债务 --他在一场纸牌游戏中输给了我很多钱。 你收到的钱将帮助你站稳脚跟。 用它来开始做事。 ";
			link.l1 = "你说‘开始做事’是什么意思? ";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "我的意思是用这笔钱来赚更多的钱, 等等。 例如通过贸易。 我们稍后会再谈这个。 现在你应该处理船只的事情, 航行到瓜德罗普岛, 找到那个胖俄罗斯人, 向他讨回债务。 \n当然不是字面意义上的, 法迪在瓜德罗普岛是一个非常受尊敬的人, 也是当地总督的朋友。 所以争吵没有意义。 相反, 试着和他交朋友。 你一有钱就回来找我。 明白了吗, 兄弟? ";
			link.l1 = "知道了。 哦, 为什么... .我做了什么要受这种惩罚... ";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "别难过, 查理。 把它当作一种不可避免的邪恶, 或者... 一件好事。 以后, 你会感激命运让你的生活发生了这样的转折。 你, 兄弟, 终于有机会做些事情来证明你是一个真正的男人。 你甚至可能成为一个正派的人... ";
			link.l1 = "(开始教程) 又是那套废话? ";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(跳过教程) 兄弟, 我没时间搞这个。 我想跳过无聊的部分, 立即起航前往公海。 我越早有船, 你越早离开这个鬼地方。 或者你更喜欢在这里多待一段时间? ";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason 海盗线 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "不, 不。 别误会... 好了, 查理, 别浪费时间了。 你知道该做什么。 我会等你从瓜德罗普岛回来, 成为自己船只的船长, 带着法迪的钱。 祝你好运, 兄弟。 我指望你了。 ";
			link.l1 = "我会尽量不让你失望。 好了, 米歇尔。 下次见! ";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//标志: 启动收集资金的迷你任务
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//打开码头
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// 酒馆关闭
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// 教堂关闭
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// 裁缝店关闭
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// 妓院关闭
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// 妓院关闭
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// 监狱关闭
			bDisableFastReload = false;//open 快速切换
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//记住日期
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//妓院和丛林的迷你任务
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//设置丛林中断
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// 向导
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason 海盗线 1
			dialog.text = "嘿! 这个‘无聊的部分’也许有一天会救你的命... 不管怎样。 现在有一个简单的方法可以马上拿到钱。 \n去当地的教堂和贝努瓦神父谈谈。 他是我们父亲的老朋友。 告诉他情况, 跪下求他借给你足够的硬币买船。 ";
			link.l1 = "(跳过教程) 现在好多了! 去找神父。 ";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(开始教程) 你想让我开始把你的债务增加到更高的水平吗? 你认为我是个傻瓜吗, 兄弟? 我看在这件事上你根本帮不了我。 那这一切都靠我了。 ";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "哇! 看来我没看错你, 兄弟。 期待你从瓜德罗普岛回来, 成为自己船只的船长, 带着法迪的钱。 一路顺风! ";
			link.l1 = "再见。 在这里玩得开心。 ";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // 加速开始
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//打开码头
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//记住日期
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// 向导
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "你是想说那很可怕吗? 别紧张, 兄弟。 完全没事。 我第一次海战的时候也没觉得自己像个英雄。 胡说八道。 一两个月后, 这样的遭遇会感觉像家常便饭... 你去过法迪那里吗? ";
			link.l1 = "我去过... 但有这样的‘成功’... 我为什么还要费心? ";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "嗯。 为什么会这样? ";
			link.l1 = "因为他陷入了困境。 他最近被抢劫了, 自己也有资金问题。 作为替代, 他给了我一把他收藏的匕首。 他说这把匕首有价值, 其价值超过整个债务的金额。 所以, 我拿了... ";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "法迪? 陷入困境? 资金问题? 哈哈哈! 你给我逗乐了, 亲爱的兄弟! 那个该死的俄罗斯人一眼就看穿了你, 马上就认出你是个新手, 而且... 啊, 那个混蛋! 把那个老人用来抵债务给你的匕首给我看看。 ";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "给你... ";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "我没带在身上。 肉眼看只是一把普通的匕首。 法迪告诉我它被一个印第安萨满施了魔法, 叫做‘酋长之爪’。 ";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "嗯。 好吧, 让我看看... 上帝会审判那个矮胖的家伙。 像那样的垃圾, 查理, 你在任何当地商店都能买到。 他利用你的缺乏经验占了你的便宜... 给你, 把这块废铁拿回去。 留作纪念吧。 你可以把它挂在你船舱的床上。 ";
			link.l1 = "混蛋! 哦, 谁在乎呢... 我会回到瓜德罗普岛见他, 给这个油腻的混蛋一点颜色看看! ";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "被萨满施了魔法? 酋长之爪? 是啊... 明白了。 上帝会审判那个矮胖的家伙。 像那样的垃圾, 查理, 你在任何当地商店都能买到。 他利用你的缺乏经验占了你的便宜... 他想给我讲某种童话故事, 我马上让他回到了原位。 所以你可以把这个爪子挂在你船舱的床上作为纪念... 如果你还没把它扔进垃圾桶的话。 ";
			link.l1 = "混蛋! 哦, 谁在乎呢... 我会回到瓜德罗普岛见他, 给这个油腻的混蛋一点颜色看看! ";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "冷静点, 亲爱的兄弟, 放松。 没有必要那样做, 除非你想在巴斯特尔的监狱里待上几个月。 你忘了我告诉过你的话吗? 那个胖家伙是瓜德罗普岛总督克劳德.弗朗索瓦.德.里昂的朋友。 我一离开这个地方, 就会和他谈谈... 推心置腹地谈。 他哪儿也去不了。 ";
			link.l1 = "好吧。 你最好处理他... 看来我将得不到承诺的启动资金了? ";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "看来是这样, 查理。 但保持乐观。 在加勒比海, 有船有头脑的人不会出错。 而你两者都有, 不是吗? ";
			link.l1 = "你在暗示什么? 我在这把匕首上搞砸了, 所以我该... ";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "冷静点, 亲爱的兄弟! 你为什么突然这么紧张? 保持冷静, 你会活得更久。 我没有暗示任何事情。 我甚至没有这些想法! ";
			link.l1 = "对不起, 米歇尔。 只是我有点... 好吧, 也试着理解我! ";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "我明白。 我真的想帮助你! 所以仔细听着。 在承担更严肃的事情之前, 你必须获得一些经验并至少存一点钱。 没有必要的准备就匆忙冒险纯粹是自杀。 我不想让你这么快就被这个地方压垮。 ";
			link.l1 = "非常鼓舞人心。 你在详述什么样的冒险, 米歇尔? 不知为什么, 我已经跟不上你的胡言乱语了。 ";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "兄弟, 让我提醒你, 我, 或者更具体地说, 我们, 欠德.潘西一百万比索。 你真的认为你能诚实地赚到它们吗? 当然, 你可以做那么多生意, 如果事情顺利的话是可能的, 但在加勒比海做生意也不是和平的活动。 \n即使你不想参与, 冒险也会自己找到你, 问题是 --当那一刻来临时, 你会准备好吗? 最好先发制人。 Si vis pacem, para bellum (如果你想要和平, 就准备战争) , 查理... ";
			link.l1 = "又来花哨的词? 我求你说法语... ";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "这是拉丁语, 亲爱的兄弟。 我说, ‘如果你想要和平, 就准备战争’。 把这句话作为行动的领导心态。 你可以把它写在你的航海日志里, 每天早上祈祷后重读。 你有很多东西要学习, 还有很多东西要掌握... ";
			link.l1 = "好了, 够了。 我已经厌倦了你的科学论文。 我们切入正题吧。 ";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "我是具体的, 只是你还没跟上。 好吧。 首先, 你需要熟悉群岛, 习惯你作为船长的新生活。 你将不得不努力工作来确保你的幸福和船员的工资。 有很多赚钱的方法。 \n在船上装载货物和乘客是最简单的。 商店里的商人可能会给你货运合同, 乘客会在街上亲自找你。 你还应该考虑查看港口办公室, 拥有一艘小帆船或任何快速船只将允许你在信使工作中赚很多钱。 \n一旦你有了更大的船, 港口主管会为你提供非常有利可图的货运合同。 与人交谈, 不要吹嘘你的血统, 保持友好, 一切都会顺利的。 拜访殖民地总督, 他们经常提供高薪工作。 \n你可以尝试贸易, 但在这种情况下, 你应该雇佣一个像样的事务长。 在海上要小心, 避开西班牙军事中队和军舰。 如果你遇到一艘西班牙商船或无保护的护航队 --你可以尝试捕获它们。 ";
			link.l1 = "什么? ! 米歇尔, 我是不是听错了? 你是在建议我过海盗的生活吗? 你, 社团的骄傲, 上帝和三位一体的仆人, 向我提议这样的生活方式? ";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "哦, 查理... 我建议你永远摆脱你的挑剔, 在这里这不被欣赏。 关于教团... 别天真了, 兄弟。 也许在欧洲, 卢浮宫和埃斯科里亚尔有某种和平, 但在这里有战争。 任何西班牙袭击者都会毫不犹豫地掠夺你的船只, 把你和你的船员吊死在桅杆上。 \n因此, 我向你保证, 没有人会责怪你掠夺敌对国家的贸易船只。 有了私掠许可证, 你甚至会得到当局的官方支持... ";
			link.l1 = "我开始理解你的生活原则了。 就像我理解你显然能够在半年内‘赚取’一百万的方法一样。 ";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "而你将不得不使用这些方法, 查理。 毕竟, 这得到了执政当局公开或私下的支持。 即使你坚持贸易, 有一天你也会被迫与海盗或西班牙袭击者战斗, 因为对他们来说, 你就是战利品。 \n忘记你以前的生活观点符合你的最佳利益。 相信我, 兄弟, 你可以做很多事情, 不仅不会丢脸, 还能赢得当局的青睐和人民的爱戴。 ";
			link.l1 = "你总是让我惊讶, 米歇尔。 现在你告诉我要成为海盗。 接下来是什么? ";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "别把这戏剧化, 查理。 这很简单: 要么捕猎, 要么被捕猎。 这就是全部哲学。 我更喜欢前者, 我希望你效仿我的榜样。 我不是告诉你成为海盗, 而是对敌对国家采取军事行动, 而且只有在有充分理由的情况下。 ";
			link.l1 = "你是说利益? ";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, 对话的小改动
		case "trial_15":
			dialog.text = "看, 你确实明白了, 兄弟。 但话说够了。 是时候考验一下自己了。 只有当你感觉准备好了才来见我。 赚些体面的钱, 买艘更好的船, 了解群岛并提升你的技能。 \n但要注意, 如果你在酒馆和妓院里度过接下来的几个月, 却没有学到任何有用的东西... 那就别回来了。 我们清楚了吗, 查理? ";
			link.l1 = "别担心。 我来这里不是为了娱乐... 那之后会发生什么? ";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "以后我会告诉你那之后该做什么。 我已经制定了一个计划。 查理, 如果你准确地听从我的建议和推荐, 你面前有一个光明的未来。 ";
			link.l1 = "与如此光明。 伟大的未来相比, 我更喜欢我平凡的过去... ";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "相信我, 兄弟, 你会嘲笑你那无价值的过去, 并感谢命运把你从它手中拯救出来。 保持乐观和积极。 你会喜欢这种生活的。 你会看到的。 \n哦, 还有一件事: 拜访我们的共同朋友法迪, 让他给你找份工作。 那家伙有很好的人脉, 我相信他会给你找些事情做。 不要拖延, 否则你可能会错过机会。 请不要让我失望。 ";
			link.l1 = "又是道德说教... 主啊, 这一切何时才会结束? 好吧, 米歇尔... 我可以走了吗? ";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "等等。 再给你一些战术建议。 如果你与任何国家为敌并成为亡命之徒, 就去当地的教堂和贝努瓦神父谈谈。 告诉他是我派你来的。 他在天主教徒和加尔文教徒社会中都有联系, 不止一次在这类事情上帮了我很多忙。 但要注意, 这既不容易也不便宜, 所以尽量避免树敌。 \n等等, 还有一件事! 我们是贵族, 但对自己动手制作有厌恶是愚蠢的, 尤其是在这里。 如果你有必要的工具和组件, 你可以制作很多有用的物品... 告诉我, 兄弟, 你如何装填你的任何一把手枪? ";
			link.l1 = "嗯。 像往常一样, 一颗子弹和一小撮火药。 ";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "哈! 我没指望听到不同的答案。 ";
			link.l1 = "你知道另一种方法吗, 亲爱的兄弟? ";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "当然。 但由于无知和单纯的懒惰, 很少有人这样做。 花几个小时的时间, 你可以用火药和子弹制作纸壳。 使用它们可以将枪的重新装填时间减半。 印象深刻吗? ";
			link.l1 = "嗯。 我想是的。 很有趣。 ";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "拿着这些纸壳的制作说明, 在你的空闲时间学习, 不要太懒于应用你的新知识\等等, 兄弟。 别忘了顺便去看看我们亲爱的总督。 ";
			link.l1 = "有什么场合吗? ";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, 暗示'捕鼠'
		case "trial_22":
			dialog.text = "与总督保持联系总是好的, 尤其是如果他们在自己的岛屿上监禁了你的亲戚。 ";
			link.l1 = "告诉我关于他的情况。 ";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "不是每个人都能保住马提尼克岛的王位。 教团的利益。 王室的利益。 海盗的利益... 一个贵族不应该忘记自己的利益。 如果帕奎特不那么放纵和受罪恶诱惑, 他甚至可以让潘西认真对待他。 ";
			link.l1 = "我对他有什么用? ";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "官员们总是为自由船长提供工作。 不过, 他们支付得很少, 而且只在涉及公共利益而不是个人利益时。 无论如何, 在加勒比海, 没有比为总督工作更好的提升荣誉和改善国家关系的方法了。 抓住机会, 尤其是因为帕奎特现在面临一些麻烦。 什么样的麻烦? ";
			link.l1 = "什么样的麻烦? ";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "对不起, 兄弟。 涉及教团的利益。 我只能说, 我们不是唯一需要快速致富方法的人。 ";
			link.l1 = "你又在含糊其辞了... 好吧, 我有时间会去拜访的。 ";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "现在走吧。 祝你好运, 兄弟! ";
			link.l1 = "谢谢你... 回头见, 米歇尔。 ";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			TakeNItems(pchar, "bullet", 5);
			TakeNItems(pchar, "gunpowder", 5);
			DialogExit();
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "trial";
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
			pchar.questTemp.Trial = "begin"; // 启动中间线
			SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 24, false); // 计时器
			AddMapQuestMarkCity("Baster", false);
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddQuestRecord("Sharlie", "19");
			// 打开所有岛屿
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
			}
			DeleteAttribute(pchar, "questTemp.Sharlie.Lock"); //移除锁定
			LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // 打开商店仓库
			sld = characterFromId("Benua");
			sld.quest.help = "true";
			npchar.greeting = "mishelle_3";
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000;
			// Addon-2016 Jason, 法国迷你任务 (FMK) 
			pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
			pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
			// Sinistra - 迷你任务'Delюк'
			PChar.quest.Del_Alonso.win_condition.l1 = "location";
			PChar.quest.Del_Alonso.win_condition.l1.location = "FortFrance_town";
			PChar.quest.Del_Alonso.win_condition = "Del_Alonso";
			// 达到等级时给予任务'荷兰甘比'的标志
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.value = 9;
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_9.function = "Sharlie_GambitStage_level_9";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.value = 12;
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_12.function = "Sharlie_GambitStage_level_12";
			// 任务'树上的钱'的走私者标记
			AddLandQuestMark(characterFromId("FortFrance_Smuggler"), "questmarkmain");
			PChar.quest.MOT_UbratMarku.win_condition.l1 = "MapEnter";
			PChar.quest.MOT_UbratMarku.win_condition = "MOT_UbratMarku";
			// Sinistra - 任务'捕鼠'开始
			pchar.questTemp.TK_TravlyaKrys = true;
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			SetTimerCondition("TK_Timer", 0, 0, 30, false);
			// 任务'不公平的竞争对手'的巴斯特商人标记
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "gambitA":
			dialog.text = "那就按你的方式来吧。 我相信你, 兄弟。 当我现在看着你时, 我就知道你正在变好。 ";
			link.l1 = "是吗。 怎么说? ";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "我能看出来, 亲爱的兄弟。 我能看到你的走路姿势和脸上的表情。 终于, 那个简直让我发疯的自负小男孩的面具从你身上融化了。 你的新生活显然已经让你受益了。 ";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "我不明白, 兄弟, 你的话是赞美还是侮辱。 但我会告诉你真相: 我对你在那边怎么看我不感兴趣。 我已经筹集了偿还你债务所需的一百万, 所以你很快就会自由了。 我在哪里可以找到德.潘西? ";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "我不明白, 兄弟, 你的话是赞美还是侮辱。 但我会告诉你真相: 我对你在那边怎么看我不感兴趣。 我有一片海的事情要处理, 而不是一堆, 我没有时间在这里和你争论, 咬文嚼字。 你有什么相关的话要说吗? 如果没有, 那我就走了... ";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// 如果不打算完成 FMK, 就移除标记
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "你设法凑齐了一百万? 干得好, 查理, 太棒了! 但不幸的是, 菲利普.德.潘西不再在他的住所了, 他已经因社团的事务出发进行一次秘密远征。 所以你得等一会儿才能拜访他。 ";
			link.l1 = "去你的和你的秘密事务! 我以为我已经处理完这一切可以回家了, 现在... ";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "现在你已经开启了赚更多钱的机会, 而不仅仅是那样。 兄弟, 你已经积累了老狐狸要求的金额, 这很了不起, 但我不会那么自信和冷静... 德.潘西是个相当狡猾的人, 他对你平凡的角色表现出了相当大的兴趣, 而且... ";
			link.l1 = "现在你担心一百万对他来说不够? ! 或者你上次有什么没说的? ";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "我什么都不怕, 但我必须警告你, 潘西不是一个简单的人。 当他不在时, 你有机会树立自己的地位, 这样你就可以平等地和他说话, 而不是像主仆一样。 因此, 我坚持要求你执行我的计划, 我现在就向你阐述。 ";
			link.l1 = "好吧。 覆水难收。 我会在这个地狱里多待一会儿。 德.潘西不会永远航行的。 让我了解你的计划。 ";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "哦! 一个值得称赞的回答。 我很高兴, 查理, 你已经成为一个男人了。 然而, 不要对你的兄弟那么严厉。 当然, 我有事情要告诉你。 我一直期待我们再次见面, 并且已经为你接下来要做的事情制定了一个计划。 ";
			link.l1 = "很好。 那就向我简要介绍一下。 ";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "听着。 当然, 钱在加勒比海扮演着重要角色, 就像在其他地方一样, 但钱不能解决一切。 一个成功的人不仅必须有一个沉重的钱包, 还必须有广泛和各种联系, 而且不是和卑鄙小人, 而是和这个世界上有影响力的人。 \n他们的国籍或阶层无关紧要。 联系打开了金钱无法独自打开的门。 ‘金钱加联系’的组合给了一个人世界上最有价值的东西 --权力。 \n你应该考虑建立这样的联系, 而你无法通过做货运工作。 贸易。 小规模海盗活动, 甚至获得总督的青睐来做到这一点。 ";
			link.l1 = "你提议什么? ";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "在加勒比海没有那么多强大的组织。 其中一个是荷兰西印度公司。 你可以加入他们。 他们的总部在库拉索岛的威廉斯塔德。 该公司经常雇佣第三方船长, 并向最有用的船长提供特殊的长期合同。 \n如果你幸运的话, 你可能会在那里有一个不错的职业生涯。 我听说他们现在正经历严重的麻烦 --某个英国私掠船船长向该公司发起攻击, 不断击沉他们的船只。 他们对他无能为力, 他是一名海军军官, 对他们来说太强硬了。 \n他们说他不知何故与英国军事情报部门有关联, 他们是非常严肃的人。 所以, 也许站在这位船长一边对你来说会更有利, 但问题是 --我不知道他的名字, 我只知道安提瓜是他的行动基地。 \n你可以航行到那里并四处打听。 我还听说有某个奇怪的组织也参与了这场英荷冲突, 但我不知道他们站在哪一边。 我只知道线索指向巴巴多斯, 布里奇顿... ";
			link.l1 = "所以你提议我报名为荷兰提议我报名为荷兰人服务, 或者去寻找一个可疑的船长或一个更可疑的‘组织’? ";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "选择在你。 无论如何, 你没有其他方法可以快速与在加勒比海决定他人命运并拥有重要权力的人建立联系。 我希望你没有想过为总督做两三个帮忙就能直接进入皇家海军。 ";
			link.l1 = "你知道, 亲爱的兄弟。 我实际上并没有希望在法国海军有一个军事生涯。 上帝保佑我不要像你一样, 因为我没能完成某项任务而被困在牢房里... 好吧, 我明白了。 我想我会毫不费力地找到荷兰公司的总部, 但我对如何寻找其余各方一无所知";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "至于英国私掠船船长, 你可以在安提瓜的圣约翰四处打听。 肯定有人能告诉你。 告诉他们你在寻找为英国舰队工作的机会。 至于‘第三势力’, 你可以和布里奇顿的人谈谈。 那里肯定有人与这个组织有关联。 ";
			link.l1 = "至少他们的工作会有报酬吗? 公司, 这个私掠船船长... 或者这一切都是为了‘联系’? ";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "查理, 你让我惊讶。 荷兰西印度公司运作的金额让国王都羡慕。 我告诉你的那个私掠船船长, 他掠夺了如此多的荷兰船只, 他肯定已经财富泛滥了。 而‘组织’的人不只是有很多钱。 他们有大量的钱。 \n为他们工作将始终保证你得到一块甜蜜的馅饼。 像他们这样的人总是玩大的。 如果你聪明, 你总是可以玩自己的游戏, 赚更多的钱。 ";
			link.l1 = "好吧。 我会考虑一下, 决定我的最佳选择。 你有任何其他指示吗? ";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "是的。 你应该学习如何使用导航工具。 唉, 很多领航员只能通过指南针和星星来定位, 无法估计坐标。 这是至关重要的。 \n所以。 使用罗盘来估计纬度。 这是一种相当罕见的工具, 你在商店里找不到, 但你可以用两个常见的物品自己制作 --一个指南针和一个星盘。 给, 拿着说明。 \n估计经度有点棘手。 你需要一个额定的精密计时器。 你可以通过用沙漏调整普通的船用计时器来制作一个。 问题是, 这样的工具在一个月后就会因为误差而变得太不可接受, 无法有效工作。 \n计时器总是需要重置。 沙漏可以在荷兰西印度公司的办公室购买。 我也在那里买过计时器。 给, 拿着这些说明。 ";
			link.l1 = "谢谢你。 我会立即开始学习。 ";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "尽快尝试获得所有这些工具。 所有经验丰富和受人尊敬的船长都使用纬度和经度。 在你知道这些数字的含义之前, 你将被视为航海新手。 \n好吧, 一旦你在我们最近讨论的事情中找到成功, 就回来吹嘘吧。 祝你好运, 查理! ";
			link.l1 = "谢谢你, 亲爱的兄弟。 我觉得这肯定会派上用场! ";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//标志: 荷兰甘比
			pchar.questTemp.HWIC.CanTake = "true"; //荷兰甘比可以接受
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, 移除标记
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "那你有什么可吹嘘的? ";
			link.l1 = "目前什么都没有。 我找到了所有三个组织, 并尝试与他们合作, 但就像一支雪茄, 实际上在第一阶段就化为烟雾了。 就像命运在针对我... ";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "那么传言是真的... 亲爱的兄弟, 命运并没有针对你。 这叫做头脑迟钝和手笨。 你让我失望了。 回法国吧, 这里没有你要做的事了。 ";
			link.l1 = "但怎么... ";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "这不再是你的事了。 我会自己处理。 我有其他更有能力的人来帮助解决我的问题。 我担心向你透露会让我在这里待到生命的尽头。 无论如何。 离开这里, 回到你的交际花那里去。 ";
			link.l1 = "好吧, 去死吧... ";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "我没什么可和你说的。 走。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "我已加入荷兰西印度公司并成为特别任务特工, 同时也是公司副主管卢卡斯.罗登伯格的密友。 我成功执行了几项重要任务, 特别是铲除了真正的英国私掠船船长。 此外, 我现在在安提瓜有了自己的住所, 口袋里装满了金币。 "; break;
				
				case "holl_fail": sTemp = "我加入了荷兰西印度公司, 但进展平平, 因失败了一项重要任务而被迫不光彩地离职, 一无所获。 "; break;
				
				case "eng_win": sTemp = "我找到了真正的英国私掠船船长理查德.弗利特伍德, 并以英国海军的名义执行了几项重要任务, 特别是摧毁了海盗‘幽灵船’并亲手解决了公司副主管卢卡斯.罗登伯格。 此外, 我现在在安提瓜有了自己的住所, 口袋里装满了金币。 "; break;
				
				case "eng_win_half": sTemp = "我找到了真正的英国私掠船船长理查德.弗利特伍德, 并以英国海军的名义执行了几项重要任务, 特别是摧毁了海盗‘幽灵船’。 当然, 弗利特伍德已返回英国, 我与他的合作也结束了, 但至少... "; break;
				
				case "eng_fail": sTemp = "我加入了来自安提瓜的英国私掠船团队, 但进展平平, 因失败了一项重要任务而被迫不光彩地离职, 一无所获。 "; break;
				
				case "self_win": sTemp = "我在巴巴多斯发现了‘秘密组织’, 开始谋划自己的计划并取得了显著成果: 解决了英国私掠船船长理查德.弗利特伍德, 将公司副主管卢卡斯.罗登伯格送入监狱, 成为总督马蒂亚斯.贝克和公司董事彼得.施托伊弗桑特的密友。 此外, 我现在在安提瓜有了自己的住所, 口袋里装满了金币。 "; break;
				
				case "self_fail": sTemp = "我在巴巴多斯发现了‘秘密组织’, 开始谋划自己的计划, 但在关键时刻一切都化为泡影... "; break;
			}
			dialog.text = "然后呢? 来吧, 亲爱的兄弟, 别卖关子了。 有什么好消息? 我听到一些传言说你干劲十足, 但我想听你亲自讲。 ";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "太棒了! 干得好, 查理! 我一刻都没怀疑过你! 你前途无量, 亲爱的兄弟... 你如此投入并与这些重要人物建立关系, 我确实没料到。 恭喜你! ";
			}
			else
			{
				dialog.text = "别沮丧, 查理。 如果没成功, 你也无能为力。 我们会用其他方法达成目标。 ";
			}
			link.l1 = "我们现在做什么, 米歇尔? 是时候拜访德.潘西骑士了吗? 我觉得我已经准备好和他谈谈了。 ";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "你已经凑齐了所需的一百万比索吗? ";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "是的, 我现在拥有所需的金额。 ";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "不, 我还没有那么多钱。 ";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "太好了! 那我在这个小牢房里待不了多久了... 去圣克里斯托弗的卡普斯特维尔, 请求与德.潘西会面。 他应该在他居住的总督府。 除此之外, 就根据情况判断, 记住: 潘西很狡猾, 非常狡猾... 我有种不好的预感, 这整件事不会那么容易。 去吧, 兄弟, 小心点! ";
			link.l1 = "我会记住你的提醒, 米歇尔。 别担心, 我也不是昨天才出生的。 我这就去找那只老狐狸。 回头见! ";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "那跟德.潘西谈也没意义。 他甚至不会让你进去。 筹集资金吧, 我的兄弟, 你已经很有经验了, 这不会是大问题。 一旦你筹到钱, 就起航去圣克里斯托弗的卡普斯特维尔。 \n骑士一定在他的总督府。 请求会面, 他们会让你进去的。 然后自己看吧, 小心点: 潘西很狡猾, 非常狡猾... 有什么事告诉我, 这个故事不会就这样结束。 ";
			link.l1 = "我会记住你的提醒, 米歇尔。 别担心, 我也不是昨天才出生的。 一旦我筹到钱, 就马上去找那只老狐狸。 回头见! ";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//标志: 海盗传奇线
		break;
		
		case "saga_5":
			dialog.text = "该死的! 这正是我担心的, 查理。 潘西关注你很久了。 这就是为什么他对你如此感兴趣! 你在加勒比海已经建立了相当的声誉, 所以他决定利用你去完成那些失败的任务... ";
			link.l1 = "我感觉, 米歇尔, 你早就知道了, 只是之前不想告诉我。 事情发展得太顺利了... 先是钱, 现在是你的工作... 这不是偶然的。 ";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "查理, 别在没有秘密的地方寻找秘密。 如果你第一天到这里就把钱给潘西... 嗯, 我是说, 如果你当时有钱的话。 骑士就不会再要求你做任何事了。 但现在他关注你, 看到你在这里适应得如此轻松, 以及你所能取得的成就, 他决定利用你的才能。 ";
			link.l1 = "对... 因为你的才能对他来说已经不够了, 对吧? 该死的! 好吧。 我知道我现在走投无路了。 这个异教徒是谁? 我怎么找到他? ";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "不需要找他! 他从不离开托尔图加, 一直待在他建造的堡垒和成群忠诚的胡格诺派教徒的保护下, 这些教徒在他的驻军中担任士兵。 因此, 每个士兵都忠于他。 潘西指的是弗朗索瓦.勒瓦瑟, 托尔图加的总督。 \n西班牙人仍然无法将他从那里赶走, 而德.潘西坚信, 我能够在没有海军支持的情况下独自完成, 只因为考虑到圣多明各驻军的近距离, 发动内战将是一个错误的政治失策。 \n这个老混蛋太担心他干净的职业生涯和即将到来的养老金, 不敢冒这个险。 然而, 勒瓦瑟做得太过分了, 对王室构成了威胁。 \n德.潘西亲自任命勒瓦瑟担任目前的职位, 他认为这个可怕的胡格诺派是个人敌人, 并渴望用马耳他骑士德.丰特奈取代他, 我就是在他的指挥下从马耳他来到这里的。 ";
			link.l1 = "太好了! 首先, 赚一百万, 然后暗杀托尔图加的总督。 我的下一个任务会是什么? 在埃斯科里亚尔组织阴谋? 该死的! 你把事情搞砸了我一点也不惊讶。 干掉总督不像抢劫西班牙商人。 我希望你发誓要解决这个麻烦时, 有什么计划吧? ";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "说实话, 我没有任何计划, 因为无论如何我都打算退役, 如果我的冒险成功, 就回到我们家族的庄园。 就个人而言, 我一点也不在乎德.潘西的问题。 \n当然, 一旦他看到印第安黄金, 他会变得灵活得多... 嗯, 目前他对我们持有所有王牌。 我想只要勒瓦瑟还是托尔图加的总督, 我就会留在这里。 ";
			link.l1 = "为什么马耳他人在德.丰特奈的带领下, 觊觎总督的位置, 却不自己进攻托尔图加? ";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "想象一下。 教团向路易宣战。 别荒谬了! 这种丑闻是不可能的。 只有私人个体才能占领托尔图加。 一个海盗, 或者像你这样的天主教冒险家。 \n在那之后, 他可以将岛屿交给德.潘西将派遣的新总督控制。 从大政策制定者的角度来看, 这样的行为看起来会很棒。 ";
			link.l1 = "所以和海盗谈判有意义吗? ";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "问题是勒瓦瑟在兄弟会和其他海盗中拥有权威。 他允许他们躲在托尔图加的炮台后面, 并为了战利品的分成自由出售他们掠夺的东西。 \n他过去和德.潘西分享, 但现在不再分享了。 海盗船将保护托尔图加及其驻军, 这使得进攻堡垒更加困难。 ";
			link.l1 = "你认为这件事没有希望了吗? ";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "总有解决办法的, 弟弟。 只是并不总是表面可见。 并非所有海盗都同情托尔图加的胡格诺派。 我知道至少有两个有权威的海盗认为勒瓦瑟是叛徒和败类。 我说的是史蒂文.多德森, 也被称为‘鲨鱼’, 以及蚊子湾的传奇男爵扬.斯文森。 \n我不知道在哪里可以找到‘鲨鱼’, 我听说发生了一些事情, 他不得不离开他在宝藏岛的基地。 但你总能在布鲁维尔德找到斯文森。 他在那里是个重要人物。 ";
			link.l1 = "你认为这个... 斯文森会帮助我吗? ";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "如果你帮助他, 他会的。 他现在过得不太好, 这个人需要忠诚和有才华的人。 在进行严肃对话之前, 你需要先证明自己对他有用。 你到那里后会找到办法的。 我在这里很难给出建议。 \n我想你已经决定继续了, 查理, 因为你一直在问问题? ";
			link.l1 = "你看, 米歇尔, 我刚刚把自己的一大笔银子给了德.潘西。 那是我用血汗赚来的! 我不确定如果我在你的位置, 你是否会为我冒险哪怕一个金路易。 ";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "查理... ";
			link.l1 = "别打断我! 空着手回到父亲身边是愚蠢的。 问题仍然没有解决, 你被监禁并面临被指控背叛社团的威胁。 如果我不执行他的‘请求’, 德.潘西会毫不犹豫地玷污蒙佩的名字。 他脸上写满了这一点。 所以我要去布鲁维尔德寻找接近斯文森的方法。 同时, 你想想还有什么‘忘记’告诉我的。 例如, 这是我第一次从你那里听说你不得不带给德.潘西一些印第安黄金。 ";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "有些事情最好隐藏起来。 你是对的, 我没有告诉你我知道的一切。 也许有一天我会告诉你更多, 但在你解决勒瓦瑟之前不会, 现在这是无用的知识。 \n我毫不怀疑你对我的关心只是出于拯救我们家族荣誉的愿望。 通过拯救我, 你首先是在拯救自己, 其次是保留了访问巴黎最好房子的可能性。 我说错了吗? ";
			link.l1 = "恐怕不再是这样了, 兄弟。 你说得对。 我在加勒比海度过的这几个月改变了我的每一根纤维和整个世界观。 而且我确定这是向好的方向改变。 我真的不再需要那些巴黎的客厅了, 有一天没有蒙佩这个名字我也能继续生活。 德.莫尔也不差... ";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "... ";
			link.l1 = "现在唯一真正伤害我的是, 你的耻辱会给我们的老父亲留下污点。 他不知道真实的情况和这里发生的事情。 此外, 正如你正确指出的, 遗产必须从不祥的状态中恢复。 为你自由支付的一百万已经显著缓解了我的财政, 所以显然需要补充。 ";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "你已经出色地掌握了所有人生教训, 查理。 我真的为你高兴。 我也很高兴你确实接受了德.潘西的请求, 而不是航行回法国。 我希望一切都对你有利, 你将能够完成我自己无法完成的事情。 ";
			link.l1 = "恐怕我别无选择。 自从我在加勒比海的第一天起, 我就独自做所有事情。 回头见, 米歇尔。 我想我们下次见面时会有释放你的命令。 ";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason 海盗线
		case "saga_17a":
            dialog.text = "等一下! 在你去见扬.斯文森之前, 一定要去拜访马库斯.泰瑞克斯 --他是法典守护者。 他统治着伊斯帕尼奥拉岛的拉维加。 他在海盗中拥有无限的权威, 西班牙人怕他怕得要死。 ";
			link.l1 = "他能帮助我们处理这件事吗? ";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "怀疑。 我真的不知道他站在哪一边, 很可能他只站在自己一边。 无论如何你需要‘鲨鱼’和斯文森, 但此刻 --泰瑞克斯是这里最强大的海盗。 他们选他为法典守护者是有原因的。 你不应该忽视这样一个重要人物。 在会见斯文森之前, 更好地了解海盗可能会有用。 你甚至可以在他们中间成名... ";
			link.l1 = "然而, 我们又回到了海盗的话题。 我无法摆脱它, 是吗? 很好。 我会去拜访他。 ";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "当海盗和与他们做生意是完全不同的游戏, 兄弟。 我希望你能看到区别。 去拉维加, 向泰瑞克斯请求一份工作。 如果你们合不来 --去他的, 回来找我。 ";
			link.l1 = "很好, 米歇尔。 再见! ..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "至少你试过了。 你有机会‘熟悉’一位臭名昭著的海盗男爵。 没关系。 去找扬.斯文森, 他在布鲁维尔德。 试着让他成为你的盟友, 否则我们与勒瓦瑟的交易将变成一场血战。 ";
			link.l1 = "好的。 我这就去。 ";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "很高兴你停下来了, 兄弟。 我曾经告诉过你, 当海盗和与他们做生意是完全不同的游戏。 而你迷失了方向。 我希望你不会对‘鲨鱼’和斯文森犯同样的错误。 做这份工作, 但与他们保持距离。 你毕竟是法国贵族, 所以要高于他们。 现在去找扬.斯文森, 他在布鲁维尔德。 试着让他成为你的盟友, 否则我们与勒瓦瑟的交易将变成一场血战。 ";
			link.l1 = "好的。 我这就去。 ";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "如果你说的是真的, 我很高兴听到。 但我真的能相信一个焚烧城市的海盗的话吗, 即使是西班牙的城市, 并且谋杀包括妇女在内的平民? ";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "住手.. 我真的为我在泰瑞克斯手下时所做的事感到抱歉。 我亲眼看到了地狱, 兄弟... 不, 结束了! 我不再当海盗了, 再也不会踏足拉维加。 我会尽一切努力恢复我的好名声。 ";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "信不信由你。 你在坐牢, 不是我。 ";
					link.l1.go = "saga_17gxa";
				}
			}
			else //占位符
			{
				link.l1 = "住手... 我真的为我在与泰瑞克斯合作时所做的恶行感到后悔。 我亲眼看到了地狱, 兄弟! .. 不, 我的海盗过去结束了! 我不再在拉维加了。 我会采取一切措施恢复我的好名声。 ";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "哦, 兄弟... 不要触怒上帝... 我希望斯文森和‘鲨鱼’不会再发生这种情况。 做事, 但保持距离, 记住这些是什么样的人。 法国贵族变得像他们一样是不合适的。 要更高尚。 现在去布鲁维尔德的扬.斯文森那里, 试着找到接近老海盗的方法。 没有他, 就不可能用少量流血解决勒瓦瑟的问题。 ";
			link.l1 = "好的。 我不会拖延。 ";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "你将不得不为此付出巨大努力, 兄弟。 你还记得我以前告诉过你的吗? 当海盗和与他们做生意是完全不同的游戏。 你... 忘了它, 我希望你不会对‘鲨鱼’和斯文森犯同样的错误。 做这份工作, 但与他们保持距离。 你毕竟是法国贵族, 所以要高于他们。 现在去找扬.斯文森, 他在布鲁维尔德。 试着让他成为你的盟友, 否则我们与勒瓦瑟的交易将变成一场血战。 ";
			link.l1 = "好的。 我这就去。 ";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // 关闭斯文森的办公室
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "现在不是谈话的时候, 兄弟! 敌人在我们的避难所里! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition 修复检查制服和滑膛枪
			if(IsUniformEquip()) sTemp = "我看到你已经成为海军上尉... 说实话, 我没料到。 我真心祝贺你! ";
			dialog.text = "你来得正是时候, 亲爱的兄弟! 我真高兴见到你! 这些该死的卡斯蒂利亚人已经完全占领了圣皮埃尔! 我以为我们肯定完了! "+sTemp+"";
			link.l1 = "我们还没脱离险境, 城市是清了, 但混蛋们退回了堡垒, 还有一支由战列舰率领的庞大中队。 但我确实给你带来了非常好的消息: 米歇尔, 你自由了! ";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "我不敢相信自己的耳朵! 真的吗? 自由了? ! ";
			link.l1 = "勒瓦瑟死了, 托尔图加现在由你的前指挥官领导, 老狐狸德.潘西已经撤销了对你的所有指控。 从现在起, 我们的好名声没有任何威胁。 ";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "我一直怀疑到最后一刻... 你让我惊讶, 查理, 在我遭遇惨败的地方取得了成功。 ";
			link.l1 = "勇者幸运垂青, 兄弟... 如你所见, 我现在也懂拉丁语了。 你牢房的钥匙在哪里? ";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "我牢房的钥匙应该在值班军官的桌子上。 在那里找找。 也许它们掉在地上滑到某个地方了... ";
			link.l1 = "我去找它们, 马上回来! ";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "终于 - 自由了! 我等这一刻等了太久! ";
			link.l1 = "你不知道我也等了多久! 米歇尔, 我们能召集任何人反击吗? ";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "你在想什么, 查理? ";
			link.l1 = "西班牙人的威胁还没有消失。 我想把他们赶出堡垒, 然后联合起来从陆地和海上攻击中队! 通过使用堡垒的大炮, 我将能够与战列舰搏斗! ";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "我们有人力。 大量骑士已经离开去保护总督府。 我们肯定能在城里找到人... 我会召集所有能找到的人。 城门外见! ";
			link.l1 = "... ";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // 隐藏的不死状态
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "看, 兄弟, 这是我们的军队。 我能找到的所有人。 人数不多, 但我们将为祖国而战! 我们要把这些该死的入侵者赶出堡垒! 出其不意将帮助我们 - 他们没有料到我们会进攻。 前进! ";
			link.l1 = "为国捐躯, 死得其所! 前进! ";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//打开位置
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "完成了, 兄弟! 堡垒是我们的了! ";
			link.l1 = "很遗憾, 在与西班牙中队的战斗中它受到了如此大的打击... 但它仍然很有能力领导一场战斗。 ";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "我会尽我的一份力。 我们将装载大炮, 给敌人沉重的打击! 但只有在我们看到你的中队接近后, 否则战舰会很快把我们炸成木屑。 ";
			link.l1 = "召集人员, 米歇尔! 我立即返回岸边! ";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "查理, 记住: 中队中最危险的是战列舰! 试着先拿下它。 我们也会用堡垒剩下的炮台集中火力攻击它。 ";
			link.l1 = "好的, 兄弟。 也许, 我应该捕获它。 ";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "从情况来看, 不该由我来教你。 现在我们不应该浪费时间! ";
			link.l1 = "... ";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // 释放到海上
			// 关闭城市设施
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "胜利荣耀! 恭喜你的胜利, 兄弟! 你太棒了! 西班牙人被彻底摧毁了! ";
			link.l1 = "我希望这会让他们在攻击法国殖民地之前三思。 ";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "现在告诉我, 查理: 你的过去生活值得什么... 与现在相比? ";
			link.l1 = "别提醒我... ";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "你还记得我们第一次在这里见面时我告诉你的吗? ‘你会喜欢这种生活’, 就是这样! 是的, 还要非常感谢你, 兄弟, 谢谢你的帮助。 没有你, 我可能永远无法逃离那个地下基地的束缚。 ";
			link.l1 = "不客气, 米歇尔。 你毕竟是我的兄弟, 我有义务帮助你。 ";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "看看你, 兄弟, 我印象深刻: 眼中充满力量, 动作自信, 姿态挺拔... 那个糟糕的艺术家和宫廷小丑去哪里了? 确实! 你超出了我最大胆的期望, 说实话, 我从未想过你会成为... 这样。 \n这甚至... 让我有点害怕。 因为为了达到目标, 你会不择手段。 你很好, 太好了... ";
			link.l1 = "出于某种原因, 我又开始难以理解你了。 你又对我不满意了吗? ";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "不! 你在说什么? ... 一点也不! 我只是在表达我的兴奋。 ";
			link.l1 = "好吧。 那么, 你接下来会做什么, 兄弟? 你会继续为社团服务吗? 还是会回到我们的遗产? 是的, 我差点忘了: 你答应过告诉我一件事。 ";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "具体是关于什么? ";
			link.l1 = "关于你为德.潘西的服务。 关于你打算带给他的一些印第安黄金。 关于你入狱前的一切。 有很多你还没来得及告诉我, 米歇尔, 让我几乎像个盲人。 所以... ";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "兄弟, 我清楚地记得我说过的话。 我会告诉你一切。 但不是在一个燃烧的城市中间! \n我们现在都有很多事情要做。 你需要安顿你的中队, 修理它并让船只重新准备好。 我和总督将组织并安抚当地人。 \n我们明天早上用一杯好的法国葡萄酒讨论一切。 相信我, 兄弟, 我有一个大计划。 一个非常大的计划。 但不是现在。 明天早上九点拜访贝努瓦神父。 我将在他那里过夜, 他是我的老朋友。 ";
			link.l1 = "好吧, 米歇尔。 就这么定了。 我期待着我们明天的谈话。 ";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "对话 28.";
			link.l1 = "好吧, 米歇尔。 就这么定了。 我期待着我们明天的谈话。 ";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "不需要道别, 查理! ";
			link.l1 = "... ";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以加速时间
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// 分发经验
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("所有居住在法国殖民地的人都欠你, 船长。 从西班牙人的邪恶袭击中保卫圣皮埃尔是一项壮举! ", FRANCE, 30, 15);
			AddSimpleRumour("能与击败一群西班牙入侵者的勇敢船长交谈是我的荣幸! ", FRANCE, 30, 15);
			AddSimpleRumour("当像你这样勇敢的海军军官为国王服务时, 法国殖民者可以安睡! ", FRANCE, 30, 15);
			AddSimpleRumourCity("我们都永远感激你, 船长! 你把我们的殖民地从毁灭中拯救出来! ", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("你是一位勇敢而精明的海军军官。 所有居住在圣皮埃尔的人都在为你祈祷, 知道吗! ", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("你是我们国家的骄傲和圣皮埃尔的英雄。 我们永远不会忘记! ", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "所以我们又见面了, "+pchar.name+"。 尽管我警告过你, 你还是继续寻找我, 而你的搜索已经把你带到了很远很远的地方... ";
			link.l1 = "米歇尔? ... 不知为何我并不惊讶。 米格尔.迪霍索又回到塔亚萨尔寻找另一堆宝藏了吗? 嗯嗯嗯。 是的, 我一直渴望与你会面, 亲爱的兄弟。 我只是迫不及待地想看看你那无耻的眼睛。 除此之外, 你在墓地地窖暗杀我的企图更是雪上加霜。 但首先, 告诉我, 我该怎么称呼你? 米歇尔.德.蒙佩还是米格尔.迪霍索? ";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "这些名字不再重要了, "+pchar.name+"。 这一切都属于过去, 而过去很快就会从历史中消失。 现在是真相的时刻, 这是我自第一次登陆以来的四分之一个世纪里一直朝着这个时刻前进... ";
			link.l1 = "什么? ! 这... 这不可能!!! ";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "是的, "+pchar.name+"。 从你脸上我看到你明白我是谁, 但你无法相信。 我就是你过去几个月渴望见到的人。 就是与你的上帝的代表, 圣地亚哥的宗教裁判官, 祝福您与之战斗的人。 ";
			link.l1 = "库库尔坎? ! ";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "我同意, "+pchar.name+", 这很难相信。 生活比任何童话都更复杂。 更令人惊讶... ";
			link.l1 = "我准备好了面对一切, 但... 我的兄弟! ";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "兄弟? 只是同父异母。 我们有不同的母亲, "+pchar.name+"。 要知道我的母亲是卡内克的女儿, 名叫肖奇克扎尔。 她在愚蠢地离开塔亚萨尔后被著名的尼古拉.戈捷指挥的法国船员绑架。 他们决定奴役她。 其中有一个名叫塞尔日.贝努瓦的人。 \n他为船长的行为感到羞耻, 离开了他, 戴上了面纱, 现在你知道他是贝努瓦神父。 我们的父亲亨利.德.蒙佩当时是一名海军军官。 他买下了肖奇克扎尔, 并把她带到法国, 在那里她生下了我。 大约在同一时间, 你也出生了, "+pchar.name+"。 你的母亲在分娩时去世, 我们的父亲宣布他的合法妻子生下了双胞胎。 \n肖奇克扎尔, 我的母亲, 成为了我们两人的乳母。 你是喝着伊察人的印第安女人的奶长大的, "+pchar.name+"! 后来你母亲家族的祖母决定带你去接受教育, 你被赋予了你母亲的名字 - 德.莫尔。 ";
			link.l1 = "你是怎么发现这一切的? ! ";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "兄弟, 你不觉得我知道的比普通人多吗? 而且, 我们的父亲告诉了我很多, 我也知道很多... 就像他们说的, 凭直觉。 ";
			link.l1 = "现在一切都清楚了... 你母亲怎么了? 为什么我从未见过她? ";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "她为了救我的命而死。 在我出生后一年多, 我差点因病去世。 我的母亲, 一位伊察祭司的女儿, 为我进行了秘密的玛雅魔法治疗仪式。 我好了, 但这个仪式伴随着一些... 破坏性的副作用, 表现为雷电和热带飓风。 肖奇克扎尔被谴责并指控使用巫术, 被宗教裁判所的火刑烧死... ";
			link.l1 = "而你好了... ";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "除了治愈我, 这个仪式还赋予了我其他一些能力, 除了打开与神之世界的连接。 剩下的你已经知道了。 如你所知, 我将把白人种族的知识和经验之光带回过去, 并传递给玛雅人。 历史将被改写, 你们白人将不再统治这个世界。 我会确保这一点。 ";
			link.l1 = "所以你的一生, 在最好的海军学院学习, 在军队和马耳他教团服役, 基本上都是为了积累军事经验? ";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "正是。 当我意识到我知道得足够多时, 我安排自己被命令前往加勒比海。 我说服德.潘西骑士在马提尼克岛建立一个基地。 接下来, 我必须设法到达塔亚萨尔。 这对我来说并不容易, 因为这个肉身仍然是凡人, 而加勒比海的传送门工作不正常。 ";
			link.l1 = "然后你成为了米格尔.迪霍索... ";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "亲爱的兄弟, 我在欧洲的战场上得到了这个绰号。 我也在那里遇到了拉蒙.德.门多萨.伊.里巴。 你认为生活是由机会组成的吗? 不, 完全不是, 每个机会都是未知的规律。 为了我返回塔亚萨尔, 做了很多事情。 我不得不过两种生活。 米歇尔.德.蒙佩和米格尔.迪霍索。 我还必须确保人们相信他们是不同的人。 \n为了获得德.潘西的信任。 好感和金钱, 我不得不像你一样当海盗, 为德.潘西服务。 为了得到远征的士兵, 我不得不作为对拉蒙.德.门多萨的帮助, 谋杀了海盗领袖之一Blaze Sharp。 \n我不得不用地亚萨尔的宝藏诱惑德.潘西和德.门多萨。 我从德.潘西的国库收到了七十五万银币, 并把西班牙军舰卖给了海盗多德森。 然后远征发生了。 我回到了塔亚萨尔, 却遭遇了失败... ";
			link.l1 = "我明白... 当你还是个五岁的男孩, 在我们父亲的遗产中追逐蝴蝶时, 伟大的祭司卡内克, 被唐.阿隆索.德.马尔多纳多入侵塔亚萨尔吓坏了, 安全地隐藏了对穿越过去至关重要的库库尔坎面具... 请原谅, 我是说 YOUR 面具。 ";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "是的, 卡内克在那里聪明反被聪明误。 他执行了最困难的仪式, 甚至古人都不敢执行的仪式。 他把面具藏在新形成的荒岛上, 并设法丢失了真理守护者克索切特姆的钥匙。 \n我不得不耍聪明。 这个仪式阻止任何载有塔亚萨尔国库保护物品的船只离开加勒比海, 将这些船只扔到克索切特姆的海岸上。 我打算利用这一点。 我拿了足够的宝藏来安抚门多萨。 我还拿了一件受仪式保护的特殊物品。 \n一艘载有这件物品的船注定会被送到克索切特姆, 送到我的面具那里。 所以我出海, 让门多萨知道我的存在。 ";
			link.l1 = " 那么, 你自己离开了塔亚萨尔? ";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "你是说没有门多萨的士兵? 当然。 所有西班牙人都在塔亚萨尔这里被杀了。 伊察人自己把宝藏带到了岸边, 我告诉门多萨士兵被米斯基托人伏击了。 他相信了我, 因为他只对黄金感兴趣, 而不是人。 \n我计划将载有宝藏的船置于‘格里芬多’的大炮下, 但结果好多了: 男爵决定在我的监视下将宝藏送往西班牙。 这是最好的结果, 我只需要等到船越过加勒比海的无形边界。 \n然而, 结果船长有不同的命令。 我发现一旦我们到达大西洋, 一个特殊的登船队应该叛变, 杀死船员和所有军官。 船长接到命令后要把印第安黄金还给门多萨。 \n多么优秀的白人标本, 不是吗, 兄弟? 我不得不冒险, 我不知道叛变何时发生。 但一切按计划进行: 一旦‘圣基特里亚’号到达特立尼达和多巴哥岛的东侧, 风暴就袭击了我们。 护卫舰被冲回加勒比海, 驶向克索切特姆。 \n然后我遭遇了人生中最大的失败 - 一个海浪把我从船上冲了下来, 几天后我在马提尼克岛的勒马林峡醒来。 渔民发现了我, 把我带到勒弗朗索瓦。 但当我在塞萨尔.克雷格的地方恢复知觉时, 德.潘西的人抓住了我。 ‘格里芬多’号没有在我指定的地方找到‘圣基特里亚’号。 德.潘西骑士一得知印第安黄金和从教团国库拿走的钱一起消失了, 就大发雷霆。 \n他逮捕了我。 不过他不能杀我, 他不想。 他想要黄金。 黄金! 这是你们的人唯一想要和关心的东西! 为了得到它, 你们会做任何事... 我当时处境艰难: 我身上没有面具, 口袋里没有一枚硬币, 只能在牢房里腐烂。 \n就在那时我召唤了你。 是的-是的, 亲爱的兄弟, 你本应释放我, 这样我就可以做我生来要做的事。 而你做得非常出色。 看来你吮吸的伊察牛奶对你有好处。 ";
			link.l1 = "我感兴趣的是, 当你逃离圣皮埃尔时, 你指望什么? 你的计划是什么? ";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "你一直是我的计划, 兄弟。 库库尔坎可以读懂人们的心。 我在神父那里留给你的信应该让你行动起来。 我对你的看法是对的。 自从你第一次与圣地亚哥的宗教裁判官会面以来, 我一直在关注你的进展。 你为我做了一切。 你制作了真理守护者。 你消灭了竞争对手。 你找到了克索切特姆。 \n我在那里, 跟着你。 虽然我没料到你会进入塔亚萨尔。 你超出了我所有的期望。 在你的帮助下, 我将做我生来要做的事。 我以凡人之躯出生的原因。 ";
			link.l1 = "你的推理中只有一个小问题, 亲爱的兄弟。 你没有你的面具, 没有它你什么都不是。 我有它。 而且我没有渴望把它交给你。 我更愿意把它炸成碎片, 也不愿让它落在你手里。 ";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "你无法改变命运的安排。 我不会允许你损坏我的神器。 我能感觉到... 它在你身上。 而你在这里, 在我的神庙里, 在我完全的力量范围内! 你永远不会离开这个地方。 亲爱的兄弟, 是时候进行你的最后测试了, 看看你在与库库尔坎的战斗中有什么价值! ";
			link.l1 = "我想你的凡胎肉体仍然会流血! ";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "哈! 我为你感到难过, 查理。 这真的很悲哀。 但你应该有机会与神战斗。 即使这是毫无意义的。 如果你能挺过第一幕, 我稍后会告诉你。 ";
			link.l1 = "我想你的凡胎肉体仍然会流血! ";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // 最终分支 - 有真正的面具或没有
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "看来你的力量正在离你而去, 伟大的库库尔坎... 你可能很强, 但你的身体仍然是凡人! ";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "我想这娱乐就够了。 你确实是一位剑术大师和伟大的战士, 我甚至敢说你是你那个时代最伟大的战士, 但这场战斗你输了, "+pchar.name+"... ";
				link.l1 = "我们只是... ";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "够了, 亲爱的兄弟。 当库库尔坎与他的神器在一起时, 你无法承受他的力量! 我让你活了这么久, 只是为了看看你真正能取得什么成就。 ";
			link.l1 = "操... 最后那一击... 但你说的是什么神器? 面具? 它在我这里! ";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "可怜的, 可怜的"+GetFullName(pchar)+"船长... 你走了这么远, 度过了所有危险, 杀死了许多最强的敌人, 最终却被打败了! .. 你在克索切特姆沉船附近的金属盒子里找到的玉面具是假的! 它只是塔亚萨尔国库的一个古老面具。 它不是库库尔坎的面具! .\n我在失败的远征后亲自从这里拿走了它, 它受到古老仪式的保护。 这个面具是风暴将‘圣基特里亚’号带到克索切特姆的原因。 它还有第二个目的。 它本应愚弄任何来这里寻找我真正神器的人。 ";
			link.l1 = "但... 真正的面具在哪里? ! 我搜遍了整个克索切特姆! ..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "你没有, "+pchar.name+"。 我的神器躺在岛上与‘圣基特里亚’号相对的一侧, 在一个守卫森严的圣所。 通往那里的道路穿过地下洞穴。 它很难找到, 对于凡人的粗糙眼睛来说并不明显。 就在那里! 好好看看, 最后一眼... ";
			link.l1 = "不可能! ";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "你活了下来, 打了很多仗, 兄弟。 但你输了这场, "+pchar.name+"... ";
			link.l1 = "现在怎么办? ";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "我将直接穿越到10世纪, 回到七个世纪前。 这将足以让玛雅文明在军事和科学上超越白人种族, 达到不可动摇的实力。 ";
			link.l1 = "我们的世界会发生什么? 它会消失吗? ";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "不。 它会改变。 也许会有你的位置, 但你不会记得这个世界发生了什么。 在这里出生的一些人在那里永远不会出生, 反之亦然。 死者会复活, 生者会死亡, 无论如何, 每个人都会重生。 各得其所, "+pchar.name+"。 \n别害怕, 小兄弟。 你永远不会意识到发生了什么, 你会自然地接受新的现实。 只有我, 库库尔坎, 会保留记忆... 但够了! 卡内克已经为仪式做好了一切准备。 \n你将跟随我, "+GetFullName(pchar)+", 你将见证这个你如此渴望保存的现实存在的最后时刻。 ";
			link.l1 = "... ";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "时间之门已经打开! rejoice, 我的孩子们, 因为你们离伟大如此之近! 我们将创造一个新世界, 一个没有苍白入侵者位置的世界! \n再见, "+pchar.name+", 准备好接受你的新命运, 无论它是什么。 各得其所! ";
			link.l1 = "... ";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "这场战斗还没有结束, 凡人。 你已经相当疲惫, 而我的援军正在赶来! 你将放弃我的神器。 要么这样, 要么我从你尸体上拿走, 对我来说没什么区别... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "乌拉坎! 我命令你立即杀死这个人! ";
			link.l1 = "... ";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "乌拉坎! 你没听见吗? 我重复: 我命令你和你的战士们抓住并杀死这个人! ";
			link.l1 = "... ";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "乌拉坎! 搞什么鬼? 卡内克! 把我他妈的命令重复给你儿子!!! ";
			link.l1 = "... ";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "你背叛了你的人民, 乌拉坎! 面对如此卓越的变革, 你已经畏缩了! 战士们, 我命令你们不仅要抓住并杀死这个自称是我兄弟的人, 还要杀死叛徒乌拉坎! ";
			link.l1 = "战士们, 以卡维尔和胡拉坎的名义, 我命令你们站在原地, 如果你们珍惜自己的生命! 你们中没有人能在与卡维尔的战斗中幸存! 让众神自己决定他们中谁是地球上最强的! ";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "这一天变得越来越好了。 你没料到会有这样的行动过程, 对吧, 兄弟? 众神必须自己决定他们中谁才是真正最强的。 每个人都会得到应得的, 米歇尔。 各得其所! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}