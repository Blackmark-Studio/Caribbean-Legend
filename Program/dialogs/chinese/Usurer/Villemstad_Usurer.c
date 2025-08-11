// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前刚问过我这个问题... ", "是的, 让我猜猜... 又在绕圈子了? ",
                          "听着, 我在这里管财务, 不回答问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性哪去了... ",
                      "你猜对了, 抱歉... ", "我明白了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "先生, 我有件不寻常的事。 我知道一个叫盖乌斯.马尔凯的法国私掠船船长最近卖给你两件独特的物品: 一个黄金圣体盒和一个黄金香炉。 我想从你这里买下它们。 ";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "我给你带来了一小箱杜布隆金币。 ";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "哦, 是的! 我当然记得它们! 是的, 它们真的很独特, 更重要的是, 很昂贵。 但是你太迟了, 船长, 我已经没有它们了。 我已经把它们卖掉了。 ";
			link.l1 = "难以置信! 谁会对那种教会用品感兴趣呢? 先生, 你把它们卖给谁了? 我想试着把它们买回来... ";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "嗯, 我为什么要告诉你我的客户名字呢? ";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "也许, 因为在总督马蒂亚斯.贝克眼里我是个好朋友, 我可以请他给你相应的制裁? ";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "也许, 因为我和荷兰西印度公司关系很好, 并且为群岛上的许多荷兰定居者提供了很大的帮助? ";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "也许因为我会为此付钱? ";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "啊, 你肯定是" +GetFullName(pchar)+ ", 总督本人的朋友, 揭露了卢卡斯.罗登堡的犯罪阴谋... 我怎么能忘记呢? 当然, 我会告诉你。 ";
			link.l1 = "那么, 我洗耳恭听。 ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "啊, 对了, 你是" +GetFullName(pchar)+ ", 海盗'幽灵船'的伟大征服者。 我怎么能忘记呢? 当然, 我会告诉你。 ";
			link.l1 = "那么, 我洗耳恭听。 ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "好吧, 那么。 对于满满一箱黄金杜布隆, 我想我会告诉你那些抢先购买的人。 ";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "给你。 它们对我来说非常珍贵... ";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "好吧, 我会给你带来你想要的东西。 它们对我来说非常珍贵... ";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("你给了一箱杜布隆金币");
			PlaySound("interface\important_item.wav");
			dialog.text = "太好了。 在这种情况下, 我愿意和你分享一些信息。 ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "那个黄金香炉被一个叫罗兰.摩西的人买走了, 他更出名的名字是'帽子罗利'。 我不知道这个屠夫要一件珍贵的教会物品干什么, 但出于某种原因, 他对此欣喜若狂... 顺便说一句, 我怀疑你会见到罗利本人。 ";
			link.l1 = "为什么这么说? ";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "因为这个热衷于抢劫孤独英国商人的强盗最近带着他的纵帆船直接落入了福克斯上校的手中。 你知道他是谁吗? ";
			link.l1 = "当然! 安提瓜岛圣琼斯'海狐'的指挥官... ";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "嗯, 那你就明白为什么我们再也见不到可怜的罗兰了。 上校没收了他的纵帆船和所有幸存的船员, 并把他们送到了圣琼斯, 在那里他们可能已经被绞死了。 ";
			link.l1 = "我明白了。 那圣体盒呢? ";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "圣体盒最近被来自库马纳的贝琳达.德.里韦罗夫人买下了。 一位非常有名的夫人, 库马纳总督费尔南多.德.比列加斯本人的亲戚。 我想她是想把它作为礼物送给教堂。 ";
			link.l1 = "贝琳达.德.里韦罗夫人? 我可以在库马纳找到她, 对吧? ";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "当然。 她自己说她要从威廉斯塔德直接回家。 ";
			link.l1 = "好的。 谢谢, " + npchar.name+ ", 你帮了大忙! ";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "随时为您效劳, 先生。 有空常来! ";
			link.l1 = "祝你有富有的客户, 钱包鼓鼓的, 脑子空空的... 哈哈! ";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}