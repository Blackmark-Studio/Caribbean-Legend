// 曼加罗莎任务角色对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "你想干什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		// 阿梅利亚 - 吉普赛女巫师
		case "amelia":
			dialog.text = "你到我家来想干什么? ";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "你叫阿梅利亚, 对吗? 我来向你打听一种植物, 曼加罗莎。 ";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "我暂时没什么要告诉你的, 但我还会再来的... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "有意思! 是谁告诉你我的, 勇敢的年轻人? ";
			link.l1 = "你的一个族人。 她说你知道这种植物的秘密, 还能教我用它制作特殊药水... ";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "首先, 让我看看你说的那种植物。 也许你对它一无所知, 只是在浪费我的时间。 你的曼加罗莎呢? ";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "给, 你看。 ";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "嗯... ";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "那你本来想给我看什么? 你根本没有曼加罗莎。 趁我没发火之前滚出去, 伙计。 谈话结束了。 ";
			link.l1 = "但是... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "又是你? 别惹麻烦, 小子... ";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "冷静点, 阿梅利亚。 上次我把它掉在什么地方了。 给, 我把曼加罗莎带来了。 你看。 ";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "... ";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "让我看看... 看来你对它有所了解。 你想让我告诉你我的药水秘密吗? ";
			link.l1 = "正是。 而且我知道这不是免费的... ";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "你说得对, 年轻人! 你看起来不是个十足的傻瓜。 好吧, 我可以教一个追求知识。 不把这种稀有植物浪费在无用烟料上的人... ";
			link.l1 = "阿梅利亚, 在我们开始讨价还价之前... 你能先告诉我用曼加罗莎可以制作哪些基本药水吗? ";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "没有讨价还价, 伙计。 我会告诉你价格, 由你决定付不付。 别指望讨价还价或打折, 这里不是市场。 至于你的问题... 用曼加罗莎可以制作特殊药水, 增强你的身体能力。 它们可以让你更强壮。 更持久或更快, 或者完全改变你的身体, 让你在各方面都更强, 但这种药水的效果比前两种弱。 ";
			link.l1 = "很有趣。 说你的价格吧。 ";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "我可以教你三个配方。 每个配方我要一株植物和五百金币。 ";
			link.l1 = "多告诉我一些这些药水的情况。 每个有什么作用? ";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "如果你想制作单一药水, 必须是炼金术大师。 每种药水持续两天或更短, 取决于你何时饮用, 如果在午夜饮用, 效果接近整整两天\n第一种药水增加你的力量和耐力。 你会打得更好, 受到更少伤害, 携带更多重量\n第二种药水会让你更敏捷。 灵活。 不知疲倦, 还能提高你的瞄准能力\n第三种药水具有前两种药水两倍的弱效。 但它也会给你魅力。 自信和运气\n所有基于曼加罗莎的药水都对你的健康有积极影响。 你一次只能喝一种药水, 永远不要混合, 否则它们不会有任何好处, 相反你会严重中毒\n那么, 帅哥, 你准备好现在为知识付费, 还是需要时间考虑? ";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "是的, 我准备好了。 ";
				link.l1.go = "amelia_8";
			}
			link.l2 = "我需要考虑一下。 这是个重大决定。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "阿梅利亚, 你似乎对这种东西很有诀窍。 你能告诉我你的族人中是否需要这种石头吗? 我到处都能找到 —好像每个人都对它们着迷! ";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "给你, 阿梅利亚。 正如你所吩咐的: 一百一十三块蝰蛇石。 ";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "啊, 是你, 年轻人! 那么, 我的药水帮到你了吗? ";
				link.l1 = "确实帮到了, 阿梅利亚。 谢谢你! ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "啊, 是你, 年轻人! 想买些配方吗? ";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "正是。 这就是我来的原因。 ";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "还没, 阿梅利亚。 只是来拜访你。 ";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "很好。 你想买哪种配方? ";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "力量和耐力药水的配方。 ";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "敏捷和耐力药水的配方。 ";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "复合药水的配方。 ";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "好的。 我给它取名为‘潮汐’。 给, 拿上说明书。 仔细阅读。 别忘了正确使用方法! ";
			link.l1 = "谢谢, 阿梅利亚... ";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "好的。 我给它取名为‘暴风’。 给, 拿上说明书。 仔细阅读。 别忘了正确使用方法! ";
			link.l1 = "谢谢, 阿梅利亚... ";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "好的。 我给它取名为‘海拥’。 给, 拿上说明书。 仔细阅读。 别忘了正确使用方法! ";
			link.l1 = "谢谢, 阿梅利亚... ";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("你支付了500达布隆和一株曼加罗莎");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "确实是蝰蛇石! 它没什么价值, 但对懂行的人有用。 给我带来一百一十三块, 我就为你打开一个我的箱子。 ";
			link.l1 = "那可是一大堆石头! 为什么不先告诉我你需要它们干什么? ";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "不, 亲爱的, 如果你需要问, 那这知识暂时对你没用。 ";
			link.l1 = "你慷慨承诺打开的箱子里有什么? ";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "很多东西, 对不鄙视体力劳动的船长有用。 别浪费我的时间, 亲爱的, 你反正收集不到那么多鹅卵石。 ";
			link.l1 = "走着瞧! ";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "哈哈哈! 我开玩笑的, 亲爱的! ";
			link.l1 = "等他们在你自己的茅屋里烧死你时, 女巫, 你就知道什么是玩笑了! ";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "那不是我的命运, 亲爱的... 你让这个吉普赛人感到骄傲! 给, 这个箱子归你掠夺了。 ";
			link.l1 = "谢谢你, 阿梅利亚。 但我真的希望里面除了你的旧内衣还有些有用的东西... ";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
}