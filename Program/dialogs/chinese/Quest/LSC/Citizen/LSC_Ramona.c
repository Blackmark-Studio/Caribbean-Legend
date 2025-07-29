// 拉莫娜.洛萨诺 - 热情的西班牙小姐
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
				dialog.text = "我不想和你说话。 你无缘无故攻击和平的平民, 还挑衅他们打架。 走开! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "你好, 你好! 新来的? 还是说你一直躲在货舱里, 毕竟这是我第一次在附近见到你? ";
				link.l1 = TimeGreeting()+"。 躲在货舱里不是我的风格。 我更喜欢船长的位置... 是的, 我是这里的新来者。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +pchar.name+ "! " +TimeGreeting()+ "! 很高兴见到你! 你有什么事? ";
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
			dialog.text = "好吧, 那我们就互相认识一下吧... 船长。 我是拉莫娜.洛萨诺, 但别想着叫我洛萨诺女士, 我讨厌这个称呼。 你叫什么名字? ";
			link.l1 = "" +GetFullName(pchar)+ "。 很高兴认识你, 拉莫娜。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "你是真的很高兴还是只是出于礼貌, " +GetFullName(pchar)+ "? 告诉我, 你真的是船长还是在开玩笑? ";
			link.l1 = "哦吼, 一下子这么多问题! 我可以按顺序回答吗? 首先, 我是真的很高兴, 我不是每天都能遇到漂亮女孩; 其次, 我是船长, 这是真的。 但我的船现在在西部大陆的海岸附近... ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "有趣! 那是怎么回事, 船长? 你在这里, 可你的船在大陆海岸附近。 你不怕船员散开, 船被别人夺走吗? ";
			link.l1 = "我乘三桅帆船来这里... 探险, 但一切都出了问题, 我发现自己到了你们的岛上。 然后我们在黑暗中撞上了一些残骸, 船翻了, 瞧! 我就到了这里。 我的船会一直等我, 只要我想。 丹妮.霍克能管住我的人。 ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "丹妮.霍克? 丹妮尔.霍克? 你是说你和她一起航行? ";
			link.l1 = "垃圾才随波逐流, 丹妮是我的军官。 我失踪时她留下来指挥... 你怎么认识她? ";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "哈! 西班牙殖民地的每个人都知道海盗丹妮尔.霍克和她的丈夫纳撒尼尔。 是的, 你, " +GetFullName(pchar)+ "先生, 一定是个硬汉... 那么你是海盗? 别担心, 我和你们这类人相处得很好。 我喜欢硬汉。 ";
			link.l1 = "嗯, 我不算真正的海盗... 我现在只是和扬.斯文森合作, 在找丹妮的丈夫纳撒尼尔。 ";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "现在你是要告诉我你不是海盗? 为森林恶魔工作, 大副是丹妮.霍克, 还在找纳撒尼尔.霍克... 我肯定你是为了舰队司令而来的。 对吗? ";
			link.l1 = "拉莫娜, 如果你想叫我海盗就叫吧, 我不介意。 你甚至可以叫我锚, 只要别把我扔进水里... ";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "看来你是个真正认真的人, " +pchar.name+ "。 好吧, 我得走了。 再见! 我有种感觉, 我们可能会成为朋友... 非常亲密的朋友。 ";
			link.l1 = "为什么不呢? 祝你好运! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- —问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "哦, 真的吗? 好吧, 问吧, 我会尽力回答... ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你怎么到这里的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "当然, 你从没试过离开这里吧... ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你在这里怎么生活? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你在这里做什么? 我猜食物不是免费的, 对吧? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "说来话长... 都怪我的继父。 四年前我住在哈瓦那, 根本想不到事情会变成这样。 母亲去世后, 我成了法定继承人。 我们不算富裕, 但钱也不少, 足够体面地生活。 继父对此很不满, 决定除掉我\n当然, 直到两个雇来的暴徒在城门外袭击我, 我才发现。 那些蠢货自己说了是谁雇他们杀我, 以及为什么。 幸运的是他们不专业, 不然我早就在灌木丛里被割喉了。 这些白痴决定先找点乐子\n那天命运救了我, 一个像你一样的船长正朝城门走来。 他看到了这一幕, 立刻杀了那些混蛋。 他们毫无还手之力。 我告诉了他发生的事和原因, 还哭了一会儿... 他知道我无处可去, 就把我带上船生活。 一开始是暂时的, 后来\n我本以为会和他在一起, 但两个月后, 他与巡逻队交战, 失去了桅杆, 遭遇强风, 最终沉在外环海底。 尽管如此, 我还是活了下来, 加入了岛上的社区。 ";
			link.l1 = "悲伤的故事, 我无话可说... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "当然没试过。 因为不可能。 我见过一个人想乘长艇离开这里... 两天后他回来了。 被绑在桅杆残骸上才没被淹死。 他浑身发青, 简直像死人一样\n那么告诉我, " +pchar.name+ ", 一旦离开这里我该做什么? 哈瓦那对我来说太危险了, 继父会再杀我一次。 我没有房子, 没有钱。 我该去哪里? 去妓院吗? ";
			link.l1 = "不过, 你想回群岛吗? ";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "你觉得呢? 当然想。 但不可能, 我刚告诉你为什么。 唉, 要是有人能解决掉我继父... 用锋利的刀或子弹, 那我就有机会回到正常生活了。 但继父是哈瓦那市长的最好朋友, 谁敢这么做? 我们为什么要谈这个? 这里根本没有出路... ";
			link.l1 = "等着看吧。 时间会证明... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// 此处指向任务
		break;
		
		case "ansewer_3":
			dialog.text = "我就这么活着。 没有其他选择。 我的朋友大多是男人, 因为我们适婚的两个美女 —吉莉安和坦妮克不喜欢我的性格, 而她们装出来的端庄也让我恶心。 娜塔莉本来是个好女孩, 直到她开始花很多时间和这些傻瓜在一起, 愚蠢是会传染的。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "我和其他女孩一样工作。 我们的主要任务是帮助男人。 岛上有很多适合女性的工作, 所以我很忙。 我也经常收到礼物, 在这里很常见。 但别误会我, 我不是那种荡妇。 我在体面家庭受过良好教育, 只是不像某些人那样装圣人。 ";
			link.l1 = "我没有误会你... ";
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
			link.l1 = LinkRandPhrase("好吧。 ", "当然。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我希望你把刀收起来。 ", "听着, 我是这个城市的公民, 我希望你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好吧。 ", "当然。 ", "如你所说... ");
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