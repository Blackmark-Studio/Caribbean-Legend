// Сeсил Галард - бабулька
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
				dialog.text = "想要点什么吗, 年轻人? ";
				link.l1 = TimeGreeting()+"。 让我自我介绍一下 - "+GetFullName(pchar)+"。 我是新来的。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 想要点什么吗? ";
				link.l1 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
				link.l1.go = "rumours_LSC";
				link.l2 = "我想问你几个关于这个岛的问题。 ";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "只是想知道你过得怎么样。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // пeрвая встрeча
			dialog.text = "啊哈, 你是在了解我们的岛屿和居民, 对吧? ";
			link.l1 = "没错, 夫人... ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "哈拉德。 塞西尔.哈拉德。 ";
			link.l1 = "很高兴认识你, 哈拉德夫人! 这是我的荣幸。 ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "我的荣幸... 你是怎么到这里来的, 年轻人? 我不记得最近有什么海难... ";
			link.l1 = "我从大陆乘三桅帆船被赶到这里... 但它就在岛的岸边沉没了。 就这样我失去了船。 ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "一艘三桅帆船? 我很难相信... 在这种情况下, 你真的很幸运, 能乘着这样的小船一路航行到岛上, 还没有遇到风暴。 岛内很少有风暴, 但岛外的风暴是一种威胁, 一种非常突然的威胁\n所以你应该感到幸运, 并习惯当地的生活方式! 我不想让你难过, 但来到这里很容易, 但离开这个岛几乎是不可能的。 别以为我在抱怨, 在过去的十年里, 没有人能活着离开这个岛。 ";
			link.l1 = "尽管如此, 我还是会尽量乐观一些。 很高兴认识你, 希望以后再见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- —блок вопросов и отвeтов ---------------------------------------------
		case "int_quests":
			dialog.text = "是的, 年轻人? ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "那你是怎么到这里来的, 夫人? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你在这里住了很长时间了, 不是吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你能告诉我一些关于当地人的事情吗? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你能告诉我一些住在这里的有趣的人吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "那是很久以前的事了, 所以我真的不记得是怎么发生的。 船难, 就这样... ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "有时我觉得我是在这里出生的... 但当然不是真的。 我这辈子后半辈子都住在这里。 时间很长。 我会死在这里, 因为我不会离开这个地方。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "我也没什么可说的, 年轻人... 这里的人各不相同。 我们这里什么人都有 - 白人。 黑人。 印第安人。 前奴隶和贵族。 国家罪犯和士兵。 以前这里的人更多。 每个人都有自己的故事和习惯。 有些人不在乎, 但有些人仍然渴望回去。 我们就是这样生活的... ";
			link.l1 = "有趣... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "这里最有趣的人是: 独角鲸机械发明家赫尔.施密特 - 独角鲸枪匠, 桑乔.卡彭特罗 - 当地酒保。 现在我们还有舰队司令和他的副官。 ";
			link.l1 = "我会考虑的... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// < —блок вопросов и отвeтов
		
//--------------------------------------- —спeциальныe рeакции -----------------------------------------------
		//обнаружeниe ГГ в сундуках
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
		
		//замeчаниe по обнажённому оружию
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
// < —спeциальныe рeакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}