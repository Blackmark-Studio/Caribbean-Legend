// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "怎么了, " + GetAddress_Form(NPChar) + "... ", "这已经是你第三次来烦我了... ",
                          "我猜你又有问题要问? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么想聊的。 "), "嗯, 我的记性哪去了... ",
                      "是的, 确实是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            //Jason, 海龟汤
            if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
            {
                link.l1 = "我在找我的老伙伴费尔南.吕克。 我有几个问题要问他。 我听说他一周前在这里玩得很开心... ";
                link.l1.go = "terrapin";
            }
            //Sinistra 导航星
            if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
            {
                link.l1 = "我和朋友约好在这儿见面, 但我哪儿都找不到他。 你知道他去哪儿了吗? 他还在镇上, 或者至少在岛上? 他叫朗威 —是中国人。 ";
                link.l1.go = "PZ_BasTerTavern_1";
            }
            //--> 合法贸易
            if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
            {
                link.l2 = "好消息, " + npchar.name+ "。 我正好有能帮你摆脱困境的东西。 一百瓶上等葡萄酒和一百瓶朗姆酒。 有了这批货, 你的顾客又能沉浸在酒的海洋里了。 你准备好付款了吗? ";
                link.l2.go = "TPZ_Tavern2_1";
            }
            if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
            {
                link.l2 = "那么, " + npchar.name+ ", 你准备好讨论交易条款了吗? ";
                link.l2.go = "TPZ_Tavern2_11";
            }
            if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
            {
                link.l2 = "那么, " + npchar.name+ "。 我这边一切都已安排好, 货物已经在运往酒馆的路上了。 我们可以进行付款了吗? ";
                link.l2.go = "TPZ_Tavern3_1";
            }
            //< —合法贸易
        break;
        
        //海龟汤
        case "terrapin":
            dialog.text = "他可能还在地狱里玩得开心呢。 你的伙伴死了, 所以你来得有点晚了, 船长。 坐在最远那张桌子旁的那个人付了他的丧葬费, 不过我感觉就是他导致了这一切。 正如人们所说, 他长着一张吊死鬼的脸。 他叫罗伯特.马滕。 如果你愿意, 可以过去亲自问问他。 ";
            link.l1 = "谢谢, 伙计。 我会去和罗伯特先生谈谈。 我们会为可怜的老吕克的灵魂干杯, 愿他安息... ";
            link.l1.go = "terrapin_1";
            npchar.quest.terrapin = "true";
        break;
        
        case "terrapin_1":
            DialogExit();
            AddQuestRecord("Terrapin", "4");
            pchar.questTemp.Terrapin = "rober";
        break;
        
        // Sinistra - 任务"旧罪的长影" ==>
        case "DTSG_BasTerTavern_1":
            dialog.text = "有什么好讨论的? 他袭击了你和你的朋友, 你们反击了, 我几乎每天都看到这种事。 干得好。 现在我只需要清理残局... ";
            Link.l1 = "你会清理的, 我相信你现在已经习惯了。 你对他了解多少? ";
            Link.l1.go = "DTSG_BasTerTavern_2";
        break;
        
        case "DTSG_BasTerTavern_2":
            dialog.text = "真的不多。 他几天前出现的。 喜欢这里, 甚至在小镇郊区租了房子。 经常来, 定期付款。 最重要的是, 这段时间他一直表现良好, 从未对任何人说过坏话。 我仍然很震惊他会袭击你和你的朋友。 我以为他可能会在这里永久定居。 ";
            Link.l1 = "在某种程度上, 他确实定居了。 好吧, 信息不多, 但谢谢你, 我的朋友。 回头见。 ";
            Link.l1.go = "DTSG_BasTerTavern_3";
        break;
        
        case "DTSG_BasTerTavern_3":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
            LAi_LocationDisableOfficersGen("BasTer_tavern", false);
            SetQuestHeader("DTSG");
            AddQuestRecord("DTSG", "1");
            bDisableFastReload = false;
            chrDisableReloadToLocation = false;
            Return_KnippelOfficer();
            
            PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
            PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
            PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
            PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
            PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
            
            SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
            SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
        break;
        // <== 任务"旧罪的长影" - Sinistra
        
        // Sinistra - 任务"导航星" ==>
        
        case "PZ_BasTerTavern_1":
            dialog.text = "那个名字对我来说毫无意义, 而且一般来说, 我不让像他这样的人进入我的场所, 也不对他们感兴趣。 ";
            Link.l1 = "好吧。 行, 回头见。 ";
            Link.l1.go = "PZ_BasTerTavern_2";
        break;
        
        case "PZ_BasTerTavern_2":
            DialogExit();
            bDisableLandEncounters = true;
            DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
            DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
            pchar.questTemp.PZ_BasTerTavern2 = true;
            DeleteQuestCondition("PZ_BasTer_Opozdal");
            DelMapQuestMarkIsland("Guadeloupe");
            
            PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
            PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
            PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
        break;
        
        // <== 任务"导航星" - Sinistra
        
        //--> 合法贸易
        case "TPZ_Tavern_1":
            dialog.text = "哦, " + GetAddress_Form(NPChar) + ", 情况比那更糟。 我从安提瓜来的供应商失去了他的酿酒厂 —海盗袭击了那里, 一切都被烧毁了。 现在他说我们至少两个月都别想拿到任何朗姆酒或葡萄酒了。 ";
            link.l1 = "那就找个新供应商。 你不会打算就这么干等两个月吧? ";
            link.l1.go = "TPZ_Tavern_2";
        break;
        
        case "TPZ_Tavern_2":
            dialog.text = "找到一个可靠的供应商并不容易。 我尝试过和小商人打交道, 但他们不可靠。 有时货物会到, 有时不会。 和大供应商合作, 一切都像 clockwork 一样 —稳定的交货和高质量。 ";
            link.l1 = "那么, 如果正规供应商有问题, 也许你应该在暗处找找? 他们很少让你失望, 而且货物总是有库存。 ";
            link.l1.go = "TPZ_Tavern_3";
        break;
        
        case "TPZ_Tavern_3":
            dialog.text = "你要明白, " + GetAddress_Form(NPChar) + ", 这家酒馆处于公众的监督之下。 我不想和当局惹上麻烦。 如果有声誉良好的人带来货物, 我不仅会买一批, 还会欣然对货物来源睁一只眼闭一只眼。 毕竟, 当情况如此糟糕时, 谁还会在乎这些琐事呢? 最主要的是避免怀疑。 但从长远来看, 我只会和认真诚实的商人打交道。 ";
            link.l1 = "我明白。 好吧, 也许我以后再来。 任何问题都可以用聪明的方法解决。 ";
            link.l1.go = "TPZ_Tavern_4";
        break;
        
        case "TPZ_Tavern_4":
            DialogExit();
            AddQuestRecord("TPZ", "2");
            pchar.questTemp.TPZ_ContraInfo = true;
            AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
        break;
        
        case "TPZ_Tavern2_1":
            dialog.text = "船长, 这太不可思议了! 你是怎么做到的? 不过没关系。 告诉我, 你想要什么来交换这批豪华的酒类货物? 还有, 文件会没问题吗? ";
            if (sti(pchar.reputation.nobility) >= 40)
            {
                link.l1 = "文件? 当然一切都完全合规。 你不会真的打算检查吧? ";
                link.l1.go = "TPZ_Tavern2_2";
                notification("荣誉检查通过", "None");
            }
            else
            {
                link.l1 = "文件? ";
                link.l1.go = "TPZ_Tavern2_2_badrep";
                notification("荣誉等级太低! ("+XI_ConvertString(GetReputationName(40))+")", "None");
            }
            DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
            DelLandQuestMark(npchar);
        break;
        
        case "TPZ_Tavern2_2_badrep":
            dialog.text = "船长, 请理解, 得到这批酒类货物对我来说至关重要。 但我的自由和声誉同样宝贵。 总督对黑市商人非常无情, 即使是最小的商人。 如果人们对你评价好, 我可以对缺乏文件睁一只眼闭一只眼, 但现在... 你吸引了太多不必要的关注... ";
            link.l1 = "看来是时候做些好事了。 等我, 我很快就回来。 ";
            link.l1.go = "exit";
            pchar.questTemp.TPZ_Tavern_3 = true;
        break;
        
        case "TPZ_Tavern2_2":
            dialog.text = "这次, 我想我会相信你的话。 那么, 这批货你想要多少钱? ";
            link.l1 = "每十瓶葡萄酒我要三十杜布隆, 每十瓶朗姆酒要五杜布隆。 整批货 —各一百瓶 —将花费你三百五十杜布隆。 ";
            link.l1.go = "TPZ_Tavern2_3";
        break;
        
        case "TPZ_Tavern2_3":
            dialog.text = "等等, 船长! 这简直是敲诈! 是的, 我的处境很绝望, 但我不会做亏本生意! ";
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
            {
                link.l1 = "也许我可以给你打折。 但这还不是全部。 我想成为你的常规供应商。 我保证顺利及时的交货。 我会在巴斯特尔租一个仓库, 你可以直接从那里收到货物, 不会有延误。 总会有足够的酒储存着, 以防止任何短缺。 有了折扣, 价格将是二百四十杜布隆。 你觉得怎么样? ";
                link.l1.go = "TPZ_Tavern2_4";
                notification("检查通过", SKILL_COMMERCE);
            }
            else
            {
                link.l1 = "好吧, 我愿意把价格降到每批二百四十杜布隆 —我的目标是长期合作。 将来, 我可以满足你所有的需求, 并确保可靠的供应。 你觉得怎么样? ";
                link.l1.go = "TPZ_Tavern2_7";
                notification("技能太低(50)", SKILL_COMMERCE);
            }
        break;
        
        case "TPZ_Tavern2_4":
            dialog.text = "这仍然比我过去付的多。 但我已经吸取了教训 —稳定性是值得这个价格的。 我同意你的条件, 但要知道: 一旦出了差错, 我就会找另一个供应商。 我需要了解我多付的钱是为了什么。 还有一件事 —你打算如何处理当局? ";
            link.l1 = "我现在就去处理。 一旦一切都解决了, 我会带着货物回来。 ";
            link.l1.go = "TPZ_Tavern2_5";
        break;
        
        case "TPZ_Tavern2_5":
            dialog.text = "请不要拖延。 我迫不及待地想看到我的顾客们的杯子再次装满。 ";
            link.l1 = "别担心, 我不会让你久等的。 ";
            link.l1.go = "TPZ_Tavern2_6";
        break;
        
        case "TPZ_Tavern2_6":
            DialogExit();
            AddQuestRecord("TPZ", "5");
            DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
            AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
            pchar.questTemp.TPZ_guber_1 = true;
            pchar.questTemp.TPZ_Vino240 = true;
            
            AddCharacterExpToSkill(pchar, "Commerce", 200);
        break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "还是太贵了, 船长。 这个价格比我之前付给供应商的还要高。 即使我现在同意, 几个月后一旦生产恢复, 我还是得回到他那里。 我看不出有什么理由多付钱。 ";
			link.l1 = "我明白了。 好吧。 我的最终报价 —两百杜布隆。 如果这都不能接受, 那我们就没必要再谈下去了。 ";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "好吧, 成交。 两百可以接受。 但告诉我, 你打算如何应对岛上的当局? 正如我之前所说, 总督严格监视岛上的走私活动。 他不会容忍在他眼皮底下进行交易。 ";
			link.l1 = "哈哈, 嗯, 我对此有不同看法。 但请放心 —我打算迅速处理所有官僚障碍。 ";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "请不要拖延。 我迫不及待地想看到我的顾客们的酒杯再次满上。 ";
			link.l1 = "别担心, 我不会让你久等的。 ";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "当然, 船长! 那么, 你的这批货想要多少钱? ";
				link.l1 = "每十瓶葡萄酒我要三十杜布隆, 每十瓶朗姆酒要五杜布隆。 整批货 —各一百瓶 —将花费你三百五十杜布隆。 ";
				link.l1.go = "TPZ_Tavern2_3";
				notification("荣誉检查通过", "None");
			}
			else
			{
				dialog.text = "对不起, 船长, 但你的声誉还有很大的提升空间。 ";
				link.l1 = "该死... ";
				link.l1.go = "exit";
				notification("荣誉太低! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "当然, 船长, 当然! 两百四十杜布隆, 就像我们约定的那样。 给你! ";
				link.l1 = "很高兴与你做生意! 现在酒馆将再次充满朗姆酒和葡萄酒。 ";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "当然, 船长, 当然! 两百杜布隆, 就像我们约定的那样。 给你! ";
				link.l1 = "很高兴与你做生意! 现在酒馆将再次充满朗姆酒和葡萄酒。 ";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "你是我的救星, 船长! 我希望每两周能收到类似的货物。 我希望你能严格履行你的义务。 再经历一次那样的缺货期, 我的酒馆就撑不下去了... ";
			link.l1 = "不必担心, "+npchar.name+"。 我在城里的代表是克里斯蒂安.德鲁斯。 他会确保你的酒馆永远不缺葡萄酒或朗姆酒。 ";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "克里斯蒂安? 我认识他。 一个负责任的人, 不过... 好吧, 没关系。 既然你已经和当局疏通好了, 我想我可以信任他。 ";
			link.l1 = "太好了。 现在, 如果你不介意的话, 我还有一件事要在这个镇上解决。 ";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "请经常来光顾! ";
			link.l1 = "我一定会的。 ";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- 合法贸易
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}
