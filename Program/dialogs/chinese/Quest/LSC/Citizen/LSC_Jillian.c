// 吉莉安.施泰纳 - 普通女孩
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
				dialog.text = "哦... 你好! 你吓到我了。 你过来得这么安静... 你想要什么? ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 我是这里的新来者, 想认识当地人, 终于决定来和你这样漂亮的女士聊聊。 你叫什么名字? ";
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
			dialog.text = "你让我脸红了, 先生, 但无论如何我都很高兴。 谢谢你的赞美。 我叫吉莉安, 吉莉安.施泰纳。 很高兴见到你。 ";
			link.l1 = "我也很高兴, 吉莉安。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "你是新来的吗? 你怎么到这里的, 告诉我? 你是从沉船中幸存下来的吗? ";
			link.l1 = "嗯... 差不多。 我乘三桅帆船航行到这里, 差点穿过礁石, 但不幸撞上了船只残骸, 我的船沉没了。 我自己游到了这里。 ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "哦! 所以你是自己选择来这里的? 难以置信! ";
			link.l1 = "是的, 我就是这么疯狂。 我决定找到那个正义之岛, 终于找到了。 不过现在我不知道怎么离开这里。 ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "你非常勇敢或鲁莽。 乘三桅帆船航行到这里... 现在你将和我们一起住在这里, 因为过去十年里没有人能离开这个地方。 ";
			link.l1 = "我仍然抱有希望。 好吧, 吉莉安, 我不打扰你了。 回头见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//-------------------------------------—— 问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "是的, 当然, " +pchar.name+ "。 我在听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你想离开这个岛吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你的一天是怎么过的? 你做什么? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你说你没有结婚... 这样漂亮的女孩在这里没有爱慕者吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "我和父母从英国航行过来。 我们想开始新生活, 而... 我在这里开始了新生活。 父母去世了, 我勉强活了下来。 我到达了外环的某艘船, 在那里无意识地躺了一天, 直到一个当地人在那里发现了我。 如果没有被发现, 我可能已经死在那里了。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "那去哪里呢? 谁需要我, 又去哪里呢? 我没有家, 没有丈夫, 也没有钱。 除了这个岛和伦敦的贫民窟, 我从未去过任何地方。 看来我命中注定要在这里生活... ";
			link.l1 = "你确定吗? ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "我主要在教堂帮助朱利安兄弟。 我也在阿克塞尔的商店做一些轻松的工作。 我就是这样赚钱的。 我是个女孩, 不能在外环的船只残骸周围攀爬。 ";
			link.l1 = "当然... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "嘻嘻... 有爱慕者, 是的, 但不值得。 我不喜欢他们中的任何一个, 也不想和不喜欢的男人生活在一起。 我喜欢的男人却不注意我。 嗯, 我只是个普通的穷女孩... ";
			link.l1 = "这只是你新生活的开始... ";
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