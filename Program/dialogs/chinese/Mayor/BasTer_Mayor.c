// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在不断提问! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不行。 地点和时间不对。 "), "确实... 但以后吧, 不是现在... ",
                      "我会问的... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "我有件棘手的事找您。 不久前一名私掠船船员将一枚镶有青金石的金十字架赠予了巴斯特尔教区。 问题在于这枚十字架是从圣地亚哥教区盗窃而来, 且盗窃过程中一名神职人员被杀害... ";
                link.l1.go = "guardoftruth";
			}
			// 杰森 圣马丁岛
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "我奉总督菲利普.德.潘西之命前来接管您的武装护卫舰。 ";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "我准备好将护卫舰编入中队了。 ";
                link.l1.go = "patria_2";
			}
			// 杰森 比黄金更珍贵
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "我来这里和某人见面... ";
                link.l1.go = "baster_goldengirl";
			}
			//--> 合法贸易
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "先生, 我打算在镇上开展商业活动。 具体来说, 我对稳定的大规模酒类贸易感兴趣。 ";
				link.l1.go = "TPZ_guber_1";
			}
			//<—— 合法贸易

		break;
		//************************** 任务分支 ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("你已经拿走了所有东西。 还想要什么? ", "还有什么是你没拿的吗? ");
            link.l1 = RandPhraseSimple("只是四处看看... ", "只是检查一下, 我可能忘了拿什么... ");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "嗯, 这很有趣。 但你为什么认为我会关心西班牙人的问题? ";
			link.l1 = "这不是西班牙人的问题, 先生。 宗教不会按国籍划分人群。 您的教区里有一件沾着圣职人员鲜血的物品, 而圣地亚哥教区遭到了亵渎... ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "我请求您主持正义, 命令神父将十字架归还给它的主人。 ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "你什么时候变得如此虔诚了, 哈, " +pchar.name+ "? 西班牙人不是我们的朋友, 我看不出有什么理由在这件事上逼迫神父。 十字架是礼物, 这样就好。 我们的神父与那起盗窃和谋杀无关, 所以... ";
			link.l1 = "所以您帮不了我, 对吗? ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "说实话, " +pchar.name+ ", 我觉得我没必要帮你。 我对那些天主教狂热分子没有好感。 ";
			link.l1 = "我明白了。 抱歉打扰您了, 先生... ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// 杰森 圣马丁岛
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "船已准备就绪, 但你的中队没有空位容纳它。 船长, 缩减你的中队后再来, 我会立即把护卫舰交给你。 ";
				link.l1 = "好的。 ";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "是的, 当然, 船已准备好起航。 船长已知晓并会服从你所有的命令。 ";
				link.l1 = "那我们出发了。 再见, 大人。 ";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "太好了。 准备迎接你的新船吧。 船长已知晓并会服从你所有的命令。 ";
			link.l1 = "那我们出发了。 再见, 大人。 ";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // 加入护卫舰
		break;
		
		// 杰森 比黄金更珍贵
		case "baster_goldengirl":
			dialog.text = "啊, 查尔斯.德.莫尔先生, 来得正是时候! 我的老朋友非常想见你, 并让我通知他你的到来。 请来到我的客厅, 我马上通知安杰伦。 顺便问一下, 你们俩是怎么认识的? ";
			link.l1 = "一起赌过钱。 他输了, 我们打了一架。 我想德.谢沃先生想修复我们之间的关系。 ";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "毫无疑问! 我希望你们俩能把事情说开。 安杰伦可能不是最容易相处的人, 但他和你一样聪明且正直。 这是难得的品质。 ";
			link.l1 = "您过奖了, 大人。 如果您不介意, 我就在客厅等他。 ";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "当然, 随便, 别拘束。 也许你得等一会儿。 我会吩咐上些饮料。 ";
			link.l1 = "谢谢您, 大人, 但不必了。 我就坐着等我们共同的... 朋友。 ";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> 合法贸易
		case "TPZ_guber_1":
			dialog.text = "船长, 你来找我是明智的。 我们正竭尽全力打击本岛的非法贸易, 我真心欢迎寻求通过合法渠道开展业务的正直船长。 ";
			link.l1 = "那么, 开始贸易需要什么条件和步骤? ";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "这很简单。 要经营酒类贸易, 你必须每月向国库缴纳一百枚达布隆的税, 保持适当的记录, 并定期提交活动报告。 资金到位后, 你就可以正式开始贸易了。 ";
			link.l1 = "太好了。 这些条件完全合理。 一位名叫克里斯蒂安.德吕斯的当地居民将代表我行事。 我相信这不会有问题吧? ";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "如你所愿, 船长。 但请记住 --你要对你的代理人负全部责任。 如果他违规, 你将承担同样的后果。 ";
			link.l1 = "当然。 感谢您的说明, 总督。 我们会做好安排, 克里斯蒂安会处理纳税事宜。 ";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "太好了。 我很高兴看到如此认真的态度。 祝你事业成功。 ";
			link.l1 = "非常感谢。 我相信我们的合作将使这座城市受益。 再见。 ";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- 合法贸易
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}