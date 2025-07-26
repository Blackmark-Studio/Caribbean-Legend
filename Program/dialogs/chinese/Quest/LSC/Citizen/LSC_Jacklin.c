// 雅克林.蒂勒姆 - 贸易船长
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
				dialog.text = "日安, 先生。 你是新来的, 对吗? ";
				link.l1 = TimeGreeting() + "。 是的, 我想我是这里最新来的。 我叫" +GetFullName(pchar)+ "。 你叫什么名字? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! " +TimeGreeting()+ "! 想要点什么吗? ";
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
			dialog.text = "雅克林.蒂勒姆。 两年前我还是个体面又富有的商人, 拥有自己的长笛帆船并担任船长。 唉, 现在我一贫如洗, 也不指望情况能有所改变\n有些人在这里很幸运 --他们找到珠宝。 黄金。 装满宝藏的船只, 但我不是其中之一。 我只找到一个装着达布隆金币的箱子和一些小饰品\n至少足够买食物, 不至于饿死... 很高兴认识你, 先生, 我不介意聊聊天... ";
			link.l1 = "我也很高兴认识你, 雅克林。 再见! ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息块
			NextDiag.TempNode = "First time";
		break;
		
//-------------------------------------—— 问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "我洗耳恭听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你在这里做什么? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "告诉我, 我看到岛上有女孩和女人... ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你想回到外面的大世界吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没什么。 ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "你想听听我的故事吗? 好吧。 如你所知, 我曾是一名贸易船长。 有一天, 我驾驶着我的老长笛帆船从托尔图加驶往伯利兹。 我的货舱里装满了黑木和可可, 我把所有的钱都花在了货物上\n我和一个人谈成了一笔非常赚钱的交易, 他想以极高的价格购买我的货物。 我本可以通过这笔交易发财。 一切都很顺利, 天空万里无云, 我的船快如飞鸟。 我们没料到会有麻烦\n我在古巴附近航行, 远离西班牙巡逻队, 但突然遭到一艘海盗大帆船的袭击。 他们在那里做什么 --在西班牙领土的中间? 我们试图逃跑, 但失败了, 那艘大帆船快得惊人\n海盗追着我们攻击。 他们的臼炮装着葡萄弹, 第一轮齐射就严重伤害了我的船员, 让他们士气低落。 我想和他们好好打一场, 但我的船员和军官阻止了我。 我们投降了\n海盗迅速抢走了我们的货物, 扔掉了我们的大炮。 我以为一切都完了。 失去货物是一个沉重的打击, 但我仍然可以通过货运赚钱, 总有一天能重新站起来\n但结果不同。 海盗混蛋们向我毫无防御的长笛帆船开火。 我们成了完美的射击目标\n我还记得他们的笑声... 大帆船驶离了, 我们在残骸中挣扎。 然后来了一场强风巨浪, 从那以后我再也没见过我的船员。 我设法把自己绑在一根桅杆上, 漂浮在水面上\n我就不跟你细说鲨鱼袭击的细节了。 不知过了多久, 我被海流带到了这里。 我就是这样活下来的。 ";
			link.l1 = "是的, 这确实是个悲伤的故事。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "我像其他当地人一样生活 --只是活着。 我在外环寻找贵重物品, 然后用它们交换食物。 我梦想找到一个装满宝藏的印第安国王的箱子... 或者至少是一艘载有西班牙黄金的大帆船, 呵呵。 别太在意, 只是我这么想\n我想吃点咸牛肉和鱼以外的东西。 唉, 这里曾经有一个人, 他捕猎那些巨大的螃蟹。 我曾经花五个达布隆金币买一只蟹爪, 可以吃好几天\n可惜那个猎人死了... 不过也不意外 --捕猎那些东西非常危险。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "我明白你的意思。 是的, 这里存在爱情和阴谋。 为什么不呢? 男人为女人而生, 女人也为男人而生。 这是天性。 你可以试试吉莉安和坦妮克。 她们年轻漂亮, 不介意谈恋爱\n我给自己找了个女人 --娜塔莉亚。 她是桑乔酒馆的女招待。 告诉你, 她是个很棒的女孩。 我相信她是我在这里生活的头几个月没有发疯的唯一原因。 她帮了很多忙, 现在我们在一起了。 ";
			link.l1 = "嗯... 我知道了! ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "问得好。 当然, 我想回去。 但仔细想想... 我已经一无所有了。 我把一切都投资在货物上, 我的船也沉了。 我没有钱生活了。 对我来说, 唯一能赚钱的方法就是为荷兰西印度公司工作, 如果他们雇佣我的话\n要是我有足够的钱买一艘纵帆船和足够的补给就好了... 所以我最好还是留在岛上。 至少在这里我不必从早到晚为了一片面包而工作。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <—— 问答块
		
//---------------------------------------—— 特殊反应 -----------------------------------------------
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
			link.l1 = LinkRandPhrase("好吧。 ", "好吧。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我希望你把刀收起来。 ", "听着, 我是这个城市的公民, 我希望你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好吧。 ", "随便吧。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 伙计, 带着武器乱跑。 我会紧张的... ", "我不喜欢男人拿着武器在我面前走来走去。 这让我害怕... ");
				link.l1 = RandPhraseSimple("明白了。 ", "我收起来。 ");
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