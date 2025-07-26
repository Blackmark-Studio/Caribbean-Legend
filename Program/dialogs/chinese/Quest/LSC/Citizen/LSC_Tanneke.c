// 坦妮克.埃弗斯 - 普通女孩
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
				dialog.text = "我不想和你说话。 你无故攻击和平市民, 还挑衅他们打架。 滚开! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "日安! 我认识你吗? 肯定没见过你... ";
				link.l1 = TimeGreeting() + "。 确实, 我是新来的... 访客。 我叫" +GetFullName(pchar)+ ", 是个船长。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! " +TimeGreeting()+ "! 想要点什么? ";
				link.l1 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
				link.l1.go = "rumours_LSC";
				link.l2 = "我想问你几个关于这个岛的问题。 ";
				link.l2.go = "int_quests"; // 信息区块
				link.l5 = "只是想知道你过得怎么样。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "你曾是船长? ";
			link.l1 = "怎么是曾是? 我现在还是船长... 啊, 我懂了! 你觉得我的船沉了或者触礁了。 不, 它在西部大陆海岸附近。 我是乘三桅帆船到这里的, 但结局不好, 船身破了个洞沉了。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "你乘三桅帆船来的? 怎么在风暴中活下来的? ";
			link.l1 = "什么风暴? 我不记得有风暴... ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "怎么会? 岛周围总是有风暴, 大家都这么说。 ";
			link.l1 = "呃, 可能没有, 或者我运气好绕开了。 海面风平浪静... 请问, 我能知道这么漂亮的女士叫什么名字吗? ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "哦! 抱歉, 忘了自我介绍... 我叫坦妮克。 很高兴认识你。 ";
			link.l1 = "我也很高兴认识你, 坦妮克... 荣幸之至。 ";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "那你为什么决定乘三桅帆船来我们岛? 啊, 我知道了 --你被洋流冲到这里的。 没人知道这个岛, 大家都是偶然来的。 ";
			link.l1 = "不对, 关于这个岛的传闻很真实, 包括位置。 所以我决定亲自来看看... ";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "现在明白了。 你和阿道夫.巴比尔一样, 读了太多阿尔瓦拉多船长的故事, 想找德贝坦库尔特舰队司令的金子。 可惜, 船长, 连巴比尔这么狡猾的无赖都没找到, 我怀疑你也不行\n而且我觉得根本没有舰队司令的金子, 安东尼奥肯定是为了显示他爷爷多重要才编出来的... 好吧, 你会留下来和我们一起。 来这里容易, 想离开可没可能。 我是说活着离开。 ";
			link.l1 = "没关系, 我觉得我能解决, 不是你说的德贝坦库尔特的金子 --我第一次听说, 我说的是离开这个岛, 活着离开。 和你聊天很愉快, 坦妮克。 再见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//-------------------------------------—— 问答区块 ---------------------------------------------
		case "int_quests":
			dialog.text = "问吧, 船长... ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你试过离开这个岛吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你在这里怎么生活? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "女孩们需要从舰队司令那里买食物吗? 有免费的吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "我是荷兰人, 但住在圣地亚哥。 父母送我去给银行家杰拉迪家当女仆, 听说过他们吗? 三年前, 其中一人乘信使小帆船去新西班牙, 我被派去陪同。 航行第二天, 我们遇到一艘挂西班牙国旗的双桅帆船\n他们的军官登船和我们船长谈话, 船长生气地把军官赶走了。 客人一回到自己船上, 我们就遭到了攻击。 我们想逃, 但他们登上了我们的船。 据我所知, 他们要抓我的主人杰拉迪, 因为他们冲进船舱抓住了他并带走了。 我和水手被关进货舱\n我以为他们会沉了我们, 但他们直接开走了。 水手们设法逃出货舱, 但船长在战斗中被杀, 幸存者中没人知道如何导航。 我们漫无目的地航行了一段时间, 然后遇到了强风\n几小时后, 小帆船被冲到外围环, 现在还在那里。 我很幸运活了下来, 黎明后我和其他几个'幸运儿'来到了岛上。 ";
			link.l1 = "我知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "没试过。 你觉得怎么离开? 这里没有适合航行的船, 用长艇等于自杀。 我说过, 这里经常有风暴。 我只记得一次离开的尝试 --五个市民造了艘像样的带帆和桨的长艇\n他们和洋流搏斗了几小时, 终于进入公海。 几天后, 其中一人回到外围环... 绑在桅杆残骸上, 已经死了。 这打消了其他人的勇气。 ";
			link.l1 = "知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "还行, 不比给那个傲慢的放债人家庭当仆人差。 你只需要习惯这里, 之后可能会喜欢上。 顺便说, 不止我一个人这么想。 帮派... 他们不打扰我。 ";
			link.l1 = "有意思... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "当然要花钱买。 哦, 船长, 女孩能做的工作很多: 打扫。 做饭。 帮助别人... 我们不闲着, 但也不拼命。 和帮派不同, 海盗卖给市民的食物很便宜, 所以我们饿不着\n我帮吉利安和娜塔莉, 需要时她们也帮我, 我们是朋友。 岛上还有另一个女孩, 西班牙人, 叫拉蒙娜, 但她大多独来独往, 我们不太想和她做朋友。 ";
			link.l1 = "为什么? ";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "嗯... 可以说我们的生活观念不同。 和她聊聊你就知道了。 ";
			link.l1 = "有意思... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <—— 问答区块
		
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 啊? 小偷! ", "看看那个! 我一沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会得逞的! ");
			link.l1 = "该死! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子? 你不会得逞的! ";
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
		
		// 注意到露出的武器
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 它让我紧张。 ", "你知道, 在这里挥舞武器是不被容忍的。 收起来。 ", "听着, 别扮演中世纪骑士到处挥剑。 收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好的。 ", "如你所愿... ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你收剑。 ", "听着, 我是这个城市的公民, 我请你收剑。 ");
				link.l1 = LinkRandPhrase("好的。 ", "如你所愿... ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 朋友, 带着武器跑。 我可能会紧张... ", "我不喜欢男人在我面前拿着武器。 这让我害怕... ");
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