// 荷兰西印度公司办公室NPC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要什么? ";
			link.l1 = "不。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 军官
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警报! 敌人在这里! 拿起武器! ";
				link.l1 = "该死! ";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "你, 站住! 你很面熟... 当然! 你因犯罪被通缉! 伙计们, 抓住他! ";
				link.l1 = "该死! ";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "欢迎来到荷兰西印度公司。 有话快说, 时间就是金钱。 ";
				link.l1 = "我来谈贸易事务, 比如许可证。 导航仪器之类的... ";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "我想为公司提供服务, 当然是为了金子。 你们招人吗? ";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "欢迎来到荷兰西印度公司。 有话快说, 时间就是金钱。 ";
				link.l1 = "抱歉, 我好像搞错了, 我这就走。 ";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "我来谈贸易事务, 比如许可证。 导航仪器之类的... ";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "有话快说, 时间就是金钱。 ";
			link.l1 = "我来谈贸易事务, 比如许可证。 导航仪器之类的... ";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "我想为公司提供服务, 当然是为了金子。 你们招人吗? ";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "那就上楼去罗登堡先生的办公室。 ";
			link.l1 = "谢谢, 我这就去。 ";
			link.l1.go = "HWIC_officer_exit";
			// belamour传奇版本 已迁移至其他地址
			LocatorReloadEnterDisable("GVIK", "reload2", false);//打开办公室
		break;
		
		case "HWIC_officer_2":
			dialog.text = "公司目前不招人。 ";
			link.l1 = "太遗憾了, 抱歉打扰。 ";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "去和格里茨先生谈, 你进来后左边那张桌子就是他的, 他负责和签约船长谈生意。 ";
			link.l1 = "谢谢你, 军官... ";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour传奇版本 已迁移
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// 士兵
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警报! 敌人在这里! 拿起武器! ";
				link.l1 = "该死! ";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "啊哈! 我想我知道你是谁了... 当然! 你因犯罪被通缉! 伙计们, 抓住他! ";
				link.l1 = "该死! ";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "和我们的军官或格里茨先生谈, 我没什么可对你说的, 我在值班。 ";
			link.l1 = "你们的纪律令人钦佩。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// 职员
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警报! 敌人在这里! 士兵们! ";
				link.l1 = "该死! ";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "去和格里茨先生谈。 ";
			link.l1 = "好的, 我知道了。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// 首席职员 - 格里茨先生
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警报! 敌人在这里! 士兵们, 抓住他! ";
				link.l1 = "该死! ";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "嗯, 我觉得你有点不对劲... 当然! 你因对荷兰犯下众多罪行而被通缉! 士兵们, 抓住他! ";
				link.l1 = "该死! ";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "想要什么, 先生? ";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "我想买一张荷兰西印度公司的贸易许可证。 ";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "我听说这里可以买到导航仪器和其他有用的物品, 是真的吗? ";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "你今天卖什么? ";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "我有一份有趣的文件给你, 先生。 看看前几行, 关系到共和国的存亡和公司的利润, 里面还有某次会议的坐标。 如果你感兴趣, 我可以卖给你, 当然得给个好价钱。 ";
				link.l3.go = "depeshe";	
			}
			// 卡莱uche
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "有个叫雷金纳德.杰克逊的船长一定在为你们工作, 他驾驶一艘名为'哈比'的泽贝克帆船。 你能告诉我怎么找到他吗? 我和他有重要生意。 ";
				link.l4.go = "caleuche";	
			}
			// Sinistra 导航星
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "我急需见罗登堡先生, 非常重要。 他在哪里? ";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "不, 没什么。 ";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// 贸易许可证
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "好吧, 你可以买。 但我必须警告你, 公司重视严格中立的声誉, 因此持有此许可证时禁止攻击任何国家的贸易船只\n如果我们发现你有此类行为, 将取消你的许可证。 此外, 如果你因任何原因与荷兰或公司发生冲突, 许可证也将被取消。 明白了吗? ";
				link.l1 = "一清二楚, 我会记住的。 ";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "欢迎购买许可证。 那么, 要多少天? ";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "该许可证允许自由进入任何国家的港口, 表明你的和平意图并解释你的目的-贸易。 但如果您有任何法律问题, 它也帮不了你, 这种情况下他们只会没收它。 记住, \n进港前别忘了升起友好旗帜, 巡逻队和堡垒的炮手喜欢先开枪后问话\n许可证最短期限为20天, 最长期限为6个月或180天\n对了, 我差点忘了... 根据我们的传统, 所有涉及许可证的交易都用达布隆支付。 现在我们来讨论条款, 你想要许可证有效期多久? ";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "抱歉, 我还得再考虑一下, 回头见。 ";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "先生, 请说清楚, 我没听清楚。 那么要多久? ";
				link.l1 = "让我想想... ";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "许可证的最短期限是20天。 那么? 20天或更长? ";
				link.l1 = "让我想想... ";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "许可证的最长期限是半年, 180天或更短? ";
				link.l1 = "让我想想... ";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "有效期"+FindRussianDaysString(sti(fQty))+"天? 很好, 这将花费你"+FindRussianDublonString(sti(npchar.quest.lcc_summ))+"达布隆。 这些条款可接受吗? ";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "是的, 我接受。 ";
				link.l1.go = "licence_2";
			}
			link.l2 = "不幸的是, 我现在没带那么多钱, 以后再来买许可证。 ";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "抱歉, 我还需要再考虑一下, 以后见。 ";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour传奇版本 与鲨鱼一起
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("任务:'与鲨鱼同行'- 你的许可证少于180天");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "等一下... 让我在这里签字盖章... 密封完成, 拿好你的文件。 ";
			link.l1 = "谢谢! 再见, 先生。 ";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "确实如此。 你可以在这里购买导航工具, 如指南针。 星盘。 天文钟和沙漏。 但除了沙漏, 我们并不总是有充足库存, 其他工具我们的承包商和船长会很快买光。 所以如果你找不到需要的东西, 一周后再来, 我们会补货\n我们也卖地图和望远镜。 想看看我们有什么吗? ";
			link.l1 = "是的, 请。 ";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// 克伦威尔急件
		case "depeshe":
			dialog.text = "嗯, 给我看看... (阅读) 好吧, 好吧... 克伦威尔的胃口越来越大了。 该死! 这些清教徒狗在自己的岛上流的血还不够吗, 还要把他们的污秽带到这里来! 你从哪里得到这份急件的? ";
			link.l1 = "我从一个英国信使那里拿到的。 那么你想买吗? ";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "是的, 彼得.斯特伊弗桑特肯定会很高兴读到它, 我相信他会采取有效措施阻止它... 我可以用金达布隆支付, 或者给你一张半年期的许可证。 你更喜欢哪种? ";
			link.l1 = "我选金子。 ";
			link.l1.go = "depeshe_dublon";
			link.l2 = "我想要许可证。 ";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("你获得了700达布隆");
			dialog.text = "很好, 这是你的七百达布隆, 为即将提供的服务支付的丰厚报酬。 ";
			link.l1 = "这是你的急件。 ";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "好的, 这是你半年期的许可证。 ";
			link.l1 = "谢谢! 这是你的急件。 ";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //取消中断
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "谢谢。 很高兴你表现出对共和国的意识和忠诚, 我会告诉马蒂亚斯.贝克和彼得.斯特伊弗桑特你的善举。 ";
			link.l1 = "很高兴知道, 再见! ";
			link.l1.go = "exit";
		break;
		
		// Sinistra 导航星
		case "PZ_RazgovorGerrits_1":
			dialog.text = "恐怕他已经和施努尔家族一起回旧大陆了, 我相信他和你提过。 ";
			link.l1 = "没错, 他提过。 但我希望他可能因为群岛上的最近事务耽搁了。 告诉我, 格里茨, 公司里有人和罗登堡先生保持联系吗? 也许通过信使船? ";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "完全没有-他离开前要求我们永远不要打扰他, 说他要开始更好的新生活。 ";
			link.l1 = "希望我们的生活也会更好, 再见。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// 卡莱uche
		case "caleuche":
			dialog.text = "让我查一下 manifest 日志... .伊克玛, 伊默泽尔, 雅各布斯... 杰克逊, 找到了。 嗯, 雷金纳德.杰克逊船长目前在皇家港和菲利普斯堡之间进行定期航运, 在那条航线上找他。 现在船长, 我必须事先警告你-如果你策划什么恶作剧, 最好不要, 因为杰克逊船长在我们的保护之下, 明白吗, 先生? ";
			link.l1 = "我只是和他有生意, 普通贸易, 无意伤害他。 ";
			link.l1.go = "caleuche_1";
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
		break;
		
		case "caleuche_1":
			dialog.text = "很好。 杰克逊船长通常不在皇家港或菲利普斯堡久留, 时间就是金钱。 他的船装卸完毕后, 通常立即起航, 你在海上航线上更容易遇到他。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_PrepareCreateGarpiya");
		break;
		
		// 荷兰西印度公司新老板
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "啊哈, " +GetFullName(pchar)+ "船长! 你来得正好, 我有个商业提议给你。 ";
						link.l1 = "有意思! 我听着, 先生。 ";
						link.l1.go = "silk_info";
						break;
					}
					else Notification_Reputation(false, 61, "low");
				}
			}
			dialog.text = "日安, " +GetFullName(pchar)+ "船长! 我能为你做什么? ";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // 丝绸贸易
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "关于那船丝绸... ";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "日安, 不, 我不需要什么, 只是想打个招呼。 ";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "我最近与一位来自里昂的商人建立了贸易联系, 打算向加勒比供应船用丝绸。 你知道吗? 世界上最好的帆就是用这种丝绸做的, 所以你一定感兴趣。 ";
			link.l1 = "真让我吃惊, 是的, 这听起来很悦耳。 你的条件是什么? ";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "小批量但定期发货, 我可以每两周为你预留30卷。 每卷成本20达布隆。 就这样: 我每月1号和15号为你预留30卷, 如果你届时不来取, 我就卖给其他客户。 ";
			link.l1 = "那么没有义务? ";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "正是如此, 船长。 如果你想要就买丝绸, 你为整批货付款-600达布隆。 希望你能成为常客。 ";
			link.l1 = "谢谢你的提议, 先生。 成交。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// 丝绸贸易
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "当然, 船长。 你的丝绸在等你, 准备好付款了吗? ";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "当然! 给, 拿2550达布隆。 ";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "该死, 我把钱忘在船上了, 马上拿来! ";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "当然, 船长。 你的丝绸在等你, 准备好付款了吗? ";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "当然! 给, 拿600达布隆。 ";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "该死, 我把钱忘在船上了, 马上拿来! ";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // 增加丝绸供应量
			{
				link.l4 = ""+npchar.name+"先生, 我想讨论增加丝绸供应的可能性。 ";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // 增加丝绸供应量, 如果第一次没带来
			{
				link.l4 = "我把达布隆带来了, "+npchar.name+"先生, 请收下。 ";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("你支付了600达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "很高兴与你做生意, 船长。 你的丝绸将通过长艇送到你的船上。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "希望很快见到你, 再来。 ";
			link.l1 = "一定, 再见! ";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // 定时器
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "我欣赏你的商业态度, 并愿意考虑你的请求。 也许我们可以把数量增加五倍。 然而, 组织这样的供应需要大量资源, 我们需要扩大存储空间, 加强安全保障, 并确保可靠的运输路线。 既然这对你也有好处, 我建议我们共同承担这些费用。 ";
				link.l1 = "这一切听起来很合理, 你认为需要多少资金来支付这些费用? ";
				link.l1.go = "UpgradeSilk_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "我理解你想增加供应的兴趣, 但在这个阶段我很难同意这样的改变。 我不怀疑你对发展的渴望, 但这种交易需要更多的贸易事务经验和对自己行为的信心。 我建议你增加谈判艺术的知识, 然后带着更具体的提议回来。 当你准备好时, 我很乐意加强我们的合作。 ";
				link.l1 = "嗯... 好吧, 我以后再谈这个。 ";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "考虑到所有细节, 你需承担的费用份额是三千金达布隆。 这些资金将使我们能够毫不拖延地组织必要的措施。 ";
			link.l1 = ""+npchar.name+"先生, 三千达布隆? 这是开玩笑吗? 我是带着真诚的提议来找你, 而你却要我为组织供应支付如此高昂的费用? ";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "请正确理解我, 我不是想欺骗你。 这笔钱是确保供应组织正常运作的必要金额, 这不仅关乎仓库扩建和安全, 还关乎保证货物交付无延误和损失, 尽管这门生意充满不可预测性。 这些是此类规模的标准费用, 最终你的投资会有回报, 你将收到状态良好且准时的货物。 ";
			link.l1 = "你的解释有些令人放心, 但这笔金额仍然太高。 如果你至少把价格降到两千五百达布隆, 我准备同意你的条款。 我相信这足以组织供应和遵守所有安全措施。 ";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "我明白, 金额很大, 但正如我已经说过的, 这是正确执行工作所必需的。 我不能降低, 因为这会危及我们所有的努力。 然而, 为了让你不觉得被欺骗, 我准备为你未来的所有供应提供百分之十五的折扣。 我希望这能让你补偿这些费用。 ";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "嗯, 百分之十五的折扣当然是一个进步。 好吧, 我准备接受你的提议, 尽管价格对我来说似乎极高。 我希望我们的合作能达到我的期望, 这是你的钱。 ";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = ""+npchar.name+"先生, 你的提议让我别无选择。 就三千达布隆吧, 尽管这是一笔可观的数目。 但我现在不能一次付清, 等我拿到钱就回来。 ";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "百分之十五的折扣? "+npchar.name+"先生, 这不是我所期望的。 这笔金额不仅是费用, 简直是明目张胆的抢劫! 但我不打算中断与你的业务关系, 我们回到之前的条款-30卷丝绸, 每卷20达布隆。 ";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "很高兴你同意, "+pchar.name+"。 现在谈细节: 150卷丝绸, 每卷17达布隆, 总计2550达布隆整批货。 你可以像往常一样提货-每月1日和15日。 我认为这笔交易将为双方带来良好利润。 ";
			link.l1 = "太好了! 这才像话, 先生。 祝你一切顺利, 很快见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "这只是一种商业手段, 并非如你所想的抢劫。 但如你所愿, 像往常一样, 1日和15日来取丝绸, 我会很高兴达成新交易。 ";
			link.l1 = "当然, 先生, 再见。 ";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "很高兴你做出了正确的决定, 等你把钱带来, 我们就讨论交易的所有细节并开始执行。 ";
			link.l1 = "再见, "+npchar.name+"先生, 等我凑够所需金额就来见你。 ";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}