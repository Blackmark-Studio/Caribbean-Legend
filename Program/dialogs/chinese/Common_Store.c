// boal 08/04/04 商人通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // 商店所在城市
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // 需要替换为 GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// 调用按城市的对话 -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// 调用按城市的对话 <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("镇上拉起了警报, 所有人都在找你。 如果我是你, 就不会待在这里。 ", "所有城卫军都在城里搜捕你。 我不是傻瓜, 不会和你说话! ", "快跑, " + GetSexPhrase("伙计","姑娘") + ", 在士兵把你打成筛子之前... "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("无赖","恶棍") + "? ! 城卫军已经盯上你了, 你跑不远的, " + GetSexPhrase("肮脏的海盗"," murderous filth") + "! ", "肮脏的凶手, 马上离开我的房子! 卫兵! ", "我不怕你, " + GetSexPhrase("爬虫","臭家伙") + "! 很快你就会在我们的堡垒里被绞死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("嘿, 警报对我来说从来不是问题... ", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭上你他妈的嘴, " + GetWorkTypeOfMan(npchar, "") + ", 不然我就撕掉你肮脏的舌头!! ", "嘿, " + GetWorkTypeOfMan(npchar, "") + ", 那里的所有人都是来抓海盗的! 我告诉你, 伙计: 安静坐着, 你就不会死... "));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("嘿, 混蛋! 你以为你可以想拿什么就拿什么吗? 当然不行! 伙计们! 拿起武器! 干掉这个疯子! ", "如果你想要什么, 就买, 你这野兽! 现在我要让你知道厉害! 伙计们, 拿武器! 警报! ");
				link.l1 = RandPhraseSimple("嗯? 什么? ", "呃, 你为什么要这样做? ");
				link.l1.go = "fight";
				bDisableFastReload = true;//关闭传送
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason 加斯科涅的重担
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> 短缺商品迷你任务
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "我想从你这里购买一批欧洲葡萄酒 --五六十瓶。 听说你库存很充足。 "; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "又见面了。 请看看这封信 --也许你会重新考虑把葡萄酒卖给我的立场? "; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "又是我。 我们能继续中断的葡萄酒交易吗? 我筹到了足够的钱。 "; 
					link.l13.go = "Wine_Price";
				}
				// <—— 短缺商品迷你任务
				dialog.text = "先生, 您想买点什么吗? ";
				Link.l1 = "当然 --商店不就是干这个的吗? 给我看看你的商品。 ";
				Link.l1.go = "trade_1";
				Link.l2 = "我来是有特定的生意目的... ";
				Link.l2.go = "quests";
				Link.l3 = "抱歉, 我得走了。 ";
				Link.l3.go = "exit";
				// 马提尼克教程
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "听着, 先生, 我在找工作。 不是全职或搬运货物的体力活, 而是跑腿之类的。 你需要帮手吗? ";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "我完成了你的差事。 我找到格拉勒姆.拉沃伊了。 ";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "先生, 见见你的新助手。 ";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "又是我, 先生。 我来拿我的报酬。 ";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "先生, 看看这些耳环。 我在丛林里杀死的一个强盗身上找到的。 这显然是优秀珠宝匠的作品, 我肯定不是本地的。 你能说说这些耳环吗? ";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<—— 加斯科涅的重担
			
			// Warship, 29.05.11。 荣誉之事 - 懦弱的击剑手。 
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "船长, 谢谢你救了我。 ";
				Link.l1 = "哦, 不客气。 ";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// 加勒比习俗
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "怎么了, 船长? 你丢东西了吗? 为什么在我店里这样跑来跑去? ";
				Link.l1 = "嗯, 你猜怎么着 --我确实丢了! 那个该死的热拉尔.勒克鲁瓦在哪? 我完成了弗洛里安.肖克交给我的所有任务, 让鲨鱼吞了我吧, 我费了好大劲! 现在我来拿报酬, 结果这只鸟飞走了! ";
				Link.l1.go = "trial";
				// belamour 传奇版 -->
				Link.l2 = "怎么说呢... 丢了。 你见过我的客户吗? 他叫热拉尔.勒克鲁瓦。 ";
				Link.l2.go = "trialA";
				//<—— 传奇版
				DelLandQuestMark(npchar);
				break;
			}
			// belamour 传奇版 不诚实的竞争对手 -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "船长, 我想请你帮个忙。 你愿意吗? ";
				link.l1 = "我怎么帮你? "; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <—— 传奇版			
            dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("很高兴见到你, 先生! 你是新来的吗? ","欢迎, 船长! 我的商店为你服务, 先生。 ","先生, 请进! 我很高兴为你提供这个群岛能买到的最好商品。 "), LinkRandPhrase("哦, 船长先生! 所有法国殖民地最好的商品 --就在这里, 现在, 专门为你! ","多好的见面啊, 先生! 提供最好法国商品的最好商店 --为你服务! ","我们以前见过吗, 船长先生? 你知道, 我的商店和母国最好的商店一样好! "), LinkRandPhrase("哦! 船长先生! 很高兴在我的店里见到你! ","我很高兴在所有西班牙殖民地最好的商店里迎接如此出色的绅士! ","哦, 高贵的idalgo! 命运把你带到了我简陋的商店! 在这里你会找到你想要的任何东西! "),LinkRandPhrase("下午好, 船长先生。 这是你第一次来吗? ","你好, 先生。 你是第一次来吗? 我向你保证, 我们荷兰商品的质量会让你惊喜! ","请进, 船长先生! 最好的商品, 最低的价格 --这就是荷兰的商业方式! "));
			Link.l1 = LinkRandPhrase("我也很高兴见到你。 我叫" +GetFullName(pchar)+ ", 我刚来这里。 那么, 给我看看群岛的财富吧! ","我也很高兴见到你。 我是" +GetFullName(pchar)+ "。 " +pchar.ship.name+ "号船长。 那么, 有什么热门交易? ","" +GetFullName(pchar)+ ", " +pchar.ship.name+ "号船长, 很高兴见到你。 那么, 你能给我提供什么? ");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "海伦船长! 总是很高兴。 ";
				link.l1 = "我也一样, 谢谢。 ";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("镇上拉起了警报, 所有人都在找你。 如果我是你, 就不会待在这里。 ", "所有城卫军都在城里搜捕你。 我不是傻瓜, 不会和你说话! ", "快跑, " + GetSexPhrase("伙计","姑娘") + ", 在士兵把你打成筛子之前... "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("无赖","恶棍") + "? ! 城卫军已经盯上你了, 你跑不远的, " + GetSexPhrase("肮脏的海盗"," murderous filth") + "! ", "肮脏的凶手, 马上离开我的房子! 卫兵! ", "我不怕你, " + GetSexPhrase("爬虫","臭家伙") + "! 很快你就会在我们的堡垒里被绞死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("嘿, 警报对我来说从来不是问题... ", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭上你的嘴, " + GetWorkTypeOfMan(npchar, "") + ", 不然我就撕掉你肮脏的舌头! ", "嘿, " + GetWorkTypeOfMan(npchar, "") + ", 那里的所有人都是来抓海盗的! 我告诉你, 伙计: 安静坐着, 你就不会死... "));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, 可疑的提议
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "请原谅, 我现在没时间理你。 ";
				link.l1 = "好的, 当然。 那我下次再来。 ";
				link.l1.go = "exit";
				break;
			}
			//<—— 可疑的提议
            
			// Warship, 29.05.11。 荣誉之事 - 懦弱的击剑手。 
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "船长, 谢谢你救了我。 ";
				Link.l1 = "哦, 不客气。 ";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// 加勒比习俗
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "怎么了, 船长? 你丢东西了吗? 为什么在我店里这样跑来跑去? ";
				Link.l1 = "嗯, 你猜怎么着 --我确实丢了! 那个该死的热拉尔.勒克鲁瓦在哪? 我完成了弗洛里安.肖克交给我的所有任务, 让鲨鱼吞了我吧, 我费了好大劲! 现在我来拿报酬, 结果这只鸟飞走了! ";
				Link.l1.go = "trial";
				// belamour 传奇版 -->
				Link.l2 = "怎么说呢... 丢了。 你见过我的客户吗? 他叫热拉尔.勒克鲁瓦。 ";
				Link.l2.go = "trialA";
				//<—— 传奇版
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour 传奇版 不诚实的竞争对手 -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "船长, 我想请你帮个忙。 你愿意吗? ";
				link.l1 = "我怎么帮你? "; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <—— 传奇版           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("哦, 看看谁在那儿! 嗯, 俗话说, 金钱无臭, 所以进来吧, 船长, 我们交易... ","我不能说很高兴见到你, " +GetFullName(pchar)+ "... 但我仍然可以和你交易。 ","嘿嘿... 好吧, 我不会邀请你到我家, 船长 --但我的商店仍然为你服务。 "),LinkRandPhrase("哦, 看看谁在那儿! 那不是" +GetFullName(pchar)+ "吗! 想交易还是免费拿东西? 嘿, 开玩笑的... ","不能说很高兴在这里见到你, " +GetAddress_Form(NPChar)+ "。 但如果你有钱花 --进来, 进来... ","想交易吗, " +GetFullName(pchar)+ "船长? 如果是, 请快点? 其他顾客都避开你, 这对我的生意不好, "),LinkRandPhrase("想交易吗, 先生? 稍等, 我要结账 --你知道, 周围有可疑的人... 当然, 我不是说你, 船长! ","如果我在公海上看到你, " +GetAddress_Form(NPChar)+ ", 我可能会下令升帆... 但在这里, 在我的店里, 我可以提议和你交易。 ","船长, 我马上警告你: 如果布料沾了血, 咖啡有火药味, 我不会要的。 否则看看, 挑一挑。 ")),LinkRandPhrase(LinkRandPhrase("我也很高兴再次问候你, " +GetAddress_Form(NPChar)+ "! 买或卖 --我总是很高兴帮助你。 ","我求你, " +GetAddress_Form(NPChar)+ ", 进来! 我总是很高兴在这里见到我最喜欢的顾客。 这次要买还是卖? ","哦, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "! 很高兴再次见到你! 这次要买还是卖? "),LinkRandPhrase("你喜欢我们的商品吗, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "? 我随时为你服务 --看看, 挑一挑。 ","你好, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "。 很高兴再次见到你! 想看看我们的商品 assortment 吗? ","很高兴见到你, 船长! 我就知道你会喜欢我们的优质商品。 想看看有什么新货吗? "),LinkRandPhrase("哦, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "! 请进! 所有商品都为你准备 --这次还有大折扣! ","" +GetFullName(pchar)+ "船长, 你再次光临让我很高兴! 请挑, 喜欢什么就拿什么! ","这次你想要什么, 船长? 很高兴你还记得怎么找到我。 我们有你需要的所有商品 --最好的质量! ")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("这就是你欢迎我的方式, 伙计? 好吧, 如果我们在海上相遇, 我会记住的... 别发抖, 我只是开玩笑。 给我看看你有什么。 ","好吧, 伙计。 我可能需要你的商品, 但不需要你的舌头。 你能忍住还是需要帮忙? 闭嘴, 给我看看你的商品。 "),RandPhraseSimple("我们言归正传吧, 小贩。 我没时间和你讨论道德问题, 所以我们就像体面人一样交易吧。 ","别着急, 伙计。 开玩笑没关系, 但记住我会生气... 所以别惹我, 给我看看你的商品。 ")),RandPhraseSimple(RandPhraseSimple("总是很高兴拜访你, 伙计。 你有什么值得我注意的库存? ","总是很高兴见到你, 伙计。 那么, 有什么新东西给在海上漂泊数月的流浪者? "),RandPhraseSimple("又一次来到" +XI_ConvertString("Colony"+npchar.City+"Acc")+"! 很高兴我没有忘记。 但你的仓库里还有我的东西吗? 都整理好了吗? ","你怎么能不来? 你总是比那更让我高兴。 那么, 你有什么? ")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple("全体船员注意! ","进行检查! ") +LinkRandPhrase("一位" + GetSexPhrase("绅士","绅士, 哦, 请原谅 --一位女士") + " of fortune 在我的店里需要什么, 嘿嘿? ",
													                                 "对一个可怜的老店主来说真是惊喜! 嘿嘿! ", "那么, 什么好风把你吹到我的店里? "),
            														LinkRandPhrase("打开港口! ","钩子到一边! ","直航! ")+RandPhraseSimple(" 这里你会找到"," 我的商店有")
																	+LinkRandPhrase(" 全岛最好的价格。 "," 出色的商品 assortment。 "," 可获得的最好质量的商品。 ")
																	+RandPhraseSimple(" 我为你服务"," 无论你想要什么")+", 船长! "),
													 pcharrepphrase(RandPhraseSimple("为" + GetSexPhrase("绅士","绅士和女士") + " of fortune 准备的任何商品! 嘿嘿! 直到他们被挂在太阳下晒干! ",
													                                 "风在港口吹动绞架上的人, 带着链条的叮当声。 但金钱无臭, 不是吗? "),
                 												"你想" +LinkRandPhrase("购买" + NationNameGenitive(sti(NPChar.nation)) + "的最好商品", "买卖你的货物", "得到有利可图的货运? ")
																	+RandPhraseSimple("? 我为你服务! ","? 我的商店为你服务! ")
																	+RandPhraseSimple(" 很高兴见到你"," 请自便") +", 船长! ")),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase("如果你想听我的建议, 船长 --不要在葡萄弹上省钱。 你知道, 死人更容易搜查! ",
													                "我一眼就看出你是个" + GetSexPhrase("机灵的伙计","机灵的姑娘") + "。 " +RandPhraseSimple("但现在我可以看出你是个真正的" + GetSexPhrase("英雄","胆大的人") + "。 ", "你很年轻, 但"
																	+RandPhraseSimple("你很有头脑。 ", "你肯定不容易被骗。 "))),
													 pcharrepphrase("我愿意从你这里购买所有缴获的货物。 用银或金买? 那东西总是很贵。 ",
													                "商业航海是一项有利可图的生意, " +GetFullName(pchar)+ "船长, 不是吗? ")),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple("我们用主帆的绳索把他们紧紧捆了二十圈, 然后把他们扔了出去! ",
													   RandPhraseSimple("十五个人在死人的箱子上! ","酒和魔鬼把其余的都带走了! ") +" 哟吼吼和一瓶朗姆酒! ")
													   +RandPhraseSimple("怎么了, 船长? ","想买点什么吗, 船长? "),
													 pcharrepphrase("我看你是个很会讨价还价的人, " +GetFullName(pchar)+ "船长。 既然你是回头客, 我给你很好的价格! ",
													                "好吧, " +GetFullName(pchar)+ "船长, 出于对你的尊重, 我可以多给一点! 你想要什么? ")),
												  NPCharRepPhrase(npchar,
												     "我发誓, 和你说话让我恶心。 "
													 +LinkRandPhrase("买几颗花生。 猪喜欢那东西。 ","你指望有人在这里用朗姆酒擦你的靴子? ",
													 pcharrepphrase("我知道你的类型。 灌醉了就上绞架。 ","我想知道你母亲怎么允许你当水手的! 一个水手! 你更适合当裁缝... ")),
													 pcharrepphrase(RandPhraseSimple("我以为","我希望")+RandPhraseSimple("你已经永远离开我们的岛了。 ","我再也见不到你了。 ")
													 +RandPhraseSimple(" 死者像磨石一样挂在你的脖子上... "," 你让多少水手在珊瑚中腐烂? ! "),
													 " " +GetFullName(pchar)+ "船长, 你对商业的热情超出了我的所有期望! "
													 +RandPhraseSimple(" 想在起航前做最后采购? "," 在找特别的东西吗? "))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			// belamour 传奇版 和阿库拉一起 -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("哦, 看看谁在那儿! 嗯, 俗话说, 金钱无臭, 所以进来吧, 船长, 我们交易... ","我不能说很高兴见到你, " +GetFullName(pchar)+ "... 但我仍然可以和你交易。 ","嘿嘿... 好吧, 我不会邀请你到我家, 船长 --但我的商店仍然为你服务。 "),LinkRandPhrase("哦, 看看谁在那儿! 那不是" +GetFullName(pchar)+ "吗! 想交易还是免费拿东西? 嘿, 开玩笑的... ","不能说很高兴在这里见到你, " +GetAddress_Form(NPChar)+ "。 但如果你有钱花 --进来, 进来... ","想交易吗, " +GetFullName(pchar)+ "船长? 如果是, 请快点? 其他顾客都避开你, 这对我的生意不好, "),LinkRandPhrase("想交易吗, 先生? 稍等, 我要结账 --你知道, 周围有可疑的人... 当然, 我不是说你, 船长! ","如果我在公海上看到你, " +GetAddress_Form(NPChar)+ ", 我可能会下令升帆... 但在这里, 在我的店里, 我可以提议和你交易。 ","船长, 我马上警告你: 如果布料沾了血, 咖啡有火药味, 我不会要的。 否则看看, 挑一挑。 ")),LinkRandPhrase(LinkRandPhrase("我也很高兴再次问候你, " +GetAddress_Form(NPChar)+ "! 买或卖 --我总是很高兴帮助你。 ","我求你, " +GetAddress_Form(NPChar)+ ", 进来! 我总是很高兴在这里见到我最喜欢的顾客。 这次要买还是卖? ","哦, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "! 很高兴再次见到你! 这次要买还是卖? "),LinkRandPhrase("你喜欢我们的商品吗, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "? 我随时为你服务 --看看, 挑一挑。 ","你好, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "。 很高兴再次见到你! 想看看我们的商品 assortment 吗? ","很高兴见到你, 船长! 我就知道你会喜欢我们的优质商品。 想看看有什么新货吗? "),LinkRandPhrase("哦, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "! 请进! 所有商品都为你准备 --这次还有大折扣! ","" +GetFullName(pchar)+ "船长, 你再次光临让我很高兴! 请挑, 喜欢什么就拿什么! ","这次你想要什么, 船长? 很高兴你还记得怎么找到我。 我们有你需要的所有商品 --最好的质量! ")));
					link.l14 = "听着, 我现在要去贝洛港, 想从你这里买一批咖啡和可可。 各三百单位。 "; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("哦, 看看谁在那儿! 嗯, 俗话说, 金钱无臭, 所以进来吧, 船长, 我们交易... ","我不能说很高兴见到你, " +GetFullName(pchar)+ "... 但我仍然可以和你交易。 ","嘿嘿... 好吧, 我不会邀请你到我家, 船长 --但我的商店仍然为你服务。 "),LinkRandPhrase("哦, 看看谁在那儿! 那不是" +GetFullName(pchar)+ "吗! 想交易还是免费拿东西? 嘿, 开玩笑的... ","不能说很高兴在这里见到你, " +GetAddress_Form(NPChar)+ "。 但如果你有钱花 --进来, 进来... ","想交易吗, " +GetFullName(pchar)+ "船长? 如果是, 请快点? 其他顾客都避开你, 这对我的生意不好, "),LinkRandPhrase("想交易吗, 先生? 稍等, 我要结账 --你知道, 周围有可疑的人... 当然, 我不是说你, 船长! ","如果我在公海上看到你, " +GetAddress_Form(NPChar)+ ", 我可能会下令升帆... 但在这里, 在我的店里, 我可以提议和你交易。 ","船长, 我马上警告你: 如果布料沾了血, 咖啡有火药味, 我不会要的。 否则看看, 挑一挑。 ")),LinkRandPhrase(LinkRandPhrase("我也很高兴再次问候你, " +GetAddress_Form(NPChar)+ "! 买或卖 --我总是很高兴帮助你。 ","我求你, " +GetAddress_Form(NPChar)+ ", 进来! 我总是很高兴在这里见到我最喜欢的顾客。 这次要买还是卖? ","哦, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "! 很高兴再次见到你! 这次要买还是卖? "),LinkRandPhrase("你喜欢我们的商品吗, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "? 我随时为你服务 --看看, 挑一挑。 ","你好, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "。 很高兴再次见到你! 想看看我们的商品 assortment 吗? ","很高兴见到你, 船长! 我就知道你会喜欢我们的优质商品。 想看看有什么新货吗? "),LinkRandPhrase("哦, " +GetAddress_Form(NPChar)+ " " +GetFullName(pchar)+ "! 请进! 所有商品都为你准备 --这次还有大折扣! ","" +GetFullName(pchar)+ "船长, 你再次光临让我很高兴! 请挑, 喜欢什么就拿什么! ","这次你想要什么, 船长? 很高兴你还记得怎么找到我。 我们有你需要的所有商品 --最好的质量! ")));
				link.l14 = "我来买咖啡和可可。 "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <—— 和阿库拉一起
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("给我看看你有什么, 老海盗! ",
													               "我只是想看看你的商品, 好心人。 "),
													pcharrepphrase("我以绞架发誓, " +GetFullName(npchar)+ ", 我不会让你拖延! 马上给我看看你的商品! ",
													               "我们看看你的商品吧, " +GetAddress_FormToNPC(NPChar)+ "。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("那是肯定的! 死人不会咬人! 现在, 你的货舱里有什么? ",
													               "你最好开始做生意, 好心人。 你能给我提供什么商品? "),
												    pcharrepphrase("总有一天你会成为我的战利品, 嘿嘿。 开玩笑的。 给我看看你的商品。 ",
													               "我们讨论一下我们的商业事务吧, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("我想要什么? 我想买东西! ",
													               "喝酒会让你送命, " +GetFullName(npchar)+ "。 我想看看你的商品。 "),
												    pcharrepphrase("我知道你的折扣! 两磅可可豆卖三磅的价格! 现在给我看看你的商品。 ",
													               "那总是好的。 我们还价吧。 ")),
											  "给我看看你的商品。 话越少, 事越快。 我很匆忙。 ",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("哦, 我真的想捅人, 好吧, 我们谈正事吧。 ",
													               "我们谈点别的事吧, 好心人。 "),
													pcharrepphrase("哎呀! 我来这有别的事! ",
													               "我想和你谈一件特定的生意, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("我和你有生意, 老海盗! ",
													               "我们谈正事吧, 伙计! "),
													pcharrepphrase("我以魔鬼发誓, 你骗不了我, 无赖! 我和你有别的生意! ",
													               "我完全同意, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", 我想和你讨论其他事务。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("已经装货了? 我和你有生意。 ",
													               "我来这不是为了交易, 好心人。 我有别的事。 "),
													pcharrepphrase("愿雷电劈了你这样的价格! 我和你有生意。 ",
													               "折扣总是好的, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", 但我和你有别的生意。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("闭嘴, 老醉鬼, 我和你有生意",
													               "你大概是因为朗姆酒恶心了。 我也不喜欢你。 我们谈正事吧。 "),
													pcharrepphrase("你已经骗了我, 无赖! 我和你有生意。 ",
													               "你的讽刺不合适。 我和你有别的生意。 ")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("先谈生意, 再寻欢作乐。 我想问你点事。 ",
													               "现在不行。 我需要信息。 "),
													pcharrepphrase("去你的价格! 你先告诉我我需要的一切。 ",
													               "很乐意。 我想问点事。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("谢谢你的建议, 老凶手。 我想问你点事。 ",
													               "我有个特定的问题。 "),
												    pcharrepphrase("金子可以等。 我想问你点事。 ",
													               "是的, 我同意。 我想问你点事。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("我相信你知道我要问什么。 ",
													               "我希望你能回答我的问题。 "),
													pcharrepphrase("除了你的价签, 你还能想到什么? 我就是要问这个。 ",
													               "那我不感兴趣。 我需要信息。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("别太激动, 伙计! 我只是想问你个问题。 ",
													               "别太激动, 不然你会中风的。 就回答一个问题, 我就走"),
													pcharrepphrase("我不指望你说什么聪明话, 因为你有蟑螂的脑子。 但你肯定知道点什么。 ",
													               "我不会耽误你太久。 就一个问题。 ")),
											   npchar, Dialog.CurrentNode);*/
			//link.l3 = "我来办别的事。 ";
			//link.l3.go = "quests";
			// --> Jason, 生成2级邮政信使
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "我给你带来了" +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"镇的价目表。 ";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--生成2级邮政信使	
						
			//Jason --> 短缺商品迷你任务
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "我想从你这里购买一批欧洲葡萄酒 --五六十瓶。 听说你库存很充足。 "; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "又见面了。 请看看这封信 --也许你会重新考虑把葡萄酒卖给我的立场? "; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "又是我。 我们能继续中断的葡萄酒交易吗? 我筹到了足够的钱。 "; 
				link.l13.go = "Wine_Price";
			}
			// <—— 短缺商品迷你任务
			
			// 马提尼克教程
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "听着, 先生, 我在找工作。 不是全职或搬运货物的体力活, 而是跑腿之类的。 你需要帮手吗? ";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "我完成了你的差事。 我找到格拉勒姆.拉沃伊了。 ";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "先生, 见见你的新助手。 ";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "又是我, 先生。 我来拿我的报酬。 ";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "先生, 看看这些耳环。 我在丛林里杀死的一个强盗身上找到的。 这显然是优秀珠宝匠的作品, 我肯定不是本地的。 你能说说这些耳环吗? ";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "你好, 我是应你儿子的邀请来的。 "; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "这是关于你女儿的... ";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("再见, 老醉鬼。 ",
													               "祝你愉快, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "。 "),
													pcharrepphrase("哎呀! 别离开, 我会再来的。 ",
													               "很高兴在这里见到你, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! 再见! ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("起航! ",
													               "再见, 好心人。 "),
													pcharrepphrase("嘿! 你在那里藏了什么? 朗姆酒? 没有? 好吧, 我去润润喉咙。 ",
													               "抱歉, 我在城里有急事。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("嘿! 好吧, 再见! ",
													               "我得走了。 再见, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! "),
													pcharrepphrase("别甚至想和我争论! 我没时间! ",
													               "也许我需要去看看我的船上怎么样了。 再见, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("怎么了, 老伙计? 是我 --" +GetFullName(pchar)+ "! 睡个觉醒醒酒, 我稍后再来。 ",
													               "恐怕你的肝脏会在我有机会再来之前把你干掉。 "),
													pcharrepphrase("继续数你的几尼和达布隆吧, 老狐狸! 我会回来的。 ",
													               "很高兴见到你, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! ")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "我能为你做什么? 给彩虹号补货, 卖点战利品? 我怀疑你对当前的有利可图的货运感兴趣, 哈哈。 ";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("给我看看你有什么, 老海盗! ",
													               "我只是想看看你的商品, 好心人。 "),
													pcharrepphrase("我以绞架发誓, " +GetFullName(npchar)+ ", 我不会让你拖延! 马上给我看看你的商品! ",
													               "我们看看你的商品吧, " +GetAddress_FormToNPC(NPChar)+ "。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("那是肯定的! 死人不会咬人! 现在, 你的货舱里有什么? ",
													               "你最好开始做生意, 好心人。 你能给我提供什么商品? "),
												    pcharrepphrase("总有一天你会成为我的战利品, 嘿嘿。 开玩笑的。 给我看看你的商品。 ",
													               "我们讨论一下我们的商业事务吧, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("我想要什么? 我想买东西! ",
													               "喝酒会让你送命, " +GetFullName(npchar)+ "。 我想看看你的商品。 "),
												    pcharrepphrase("我知道你的折扣! 两磅可可豆卖三磅的价格! 现在给我看看你的商品。 ",
													               "那总是好的。 我们还价吧。 ")),
											  "给我看看你的商品。 话越少, 事越快。 我很匆忙。 ",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("哦, 我真的想捅人, 好吧, 我们谈正事吧。 ",
													               "我们谈点别的事吧, 好心人。 "),
													pcharrepphrase("哎呀! 我来这有别的事! ",
													               "我想和你谈一件特定的生意, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("我和你有生意, 老海盗! ",
													               "我们谈正事吧, 伙计! "),
													pcharrepphrase("我以魔鬼发誓, 你骗不了我, 无赖! 我和你有别的生意! ",
													               "我完全同意, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", 我想和你讨论其他事务。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("已经装货了? 我和你有生意。 ",
													               "我来这不是为了交易, 好心人。 我有别的事。 "),
													pcharrepphrase("愿雷电劈了你这样的价格! 我和你有生意。 ",
													               "折扣总是好的, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", 但我和你有别的生意。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("闭嘴, 老醉鬼, 我和你有生意",
													               "你大概是因为朗姆酒恶心了。 我也不喜欢你。 我们谈正事吧。 "),
													pcharrepphrase("你已经骗了我, 无赖! 我和你有生意。 ",
													               "你的讽刺不合适。 我和你有别的生意。 ")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("先谈生意, 再寻欢作乐。 我想问你点事。 ",
													               "现在不行。 我需要信息。 "),
													pcharrepphrase("去你的价格! 你先告诉我我需要的一切。 ",
													               "很乐意。 我想问点事。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("谢谢你的建议, 老凶手。 我想问你点事。 ",
													               "我有个特定的问题。 "),
												    pcharrepphrase("金子可以等。 我想问你点事。 ",
													               "是的, 我同意。 我想问你点事。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("我相信你知道我要问什么。 ",
													               "我希望你能回答我的问题。 "),
													pcharrepphrase("除了你的价签, 你还能想到什么? 我就是要问这个。 ",
													               "那我不感兴趣。 我需要信息。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("别太激动, 伙计! 我只是想问你个问题。 ",
													               "别太激动, 不然你会中风的。 就回答一个问题, 我就走"),
													pcharrepphrase("我不指望你说什么聪明话, 因为你有蟑螂的脑子。 但你肯定知道点什么。 ",
													               "我不会耽误你太久。 就一个问题。 ")),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("再见, 老醉鬼。 ",
													               "祝你愉快, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "。 "),
													pcharrepphrase("哎呀! 别离开, 我会再来的。 ",
													               "很高兴在这里见到你, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! 再见! ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("起航! ",
													               "再见, 好心人。 "),
													pcharrepphrase("嘿! 你在那里藏了什么? 朗姆酒? 没有? 好吧, 我去润润喉咙。 ",
													               "抱歉, 我在城里有急事。 ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("嘿! 好吧, 再见! ",
													               "我得走了。 再见, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! "),
													pcharrepphrase("别甚至想和我争论! 我没时间! ",
													               "也许我需要去看看我的船上怎么样了。 再见, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! ")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("怎么了, 老伙计? 是我 --" +GetFullName(pchar)+ "! 睡个觉醒醒酒, 我稍后再来。 ",
													               "恐怕你的肝脏会在我有机会再来之前把你干掉。 "),
													pcharrepphrase("继续数你的几尼和达布隆吧, 老狐狸! 我会回来的。 ",
													               "很高兴见到你, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "! ")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//PGG 忙碌
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do 填入名称
			{
				dialog.text = "抱歉, 但我现在太忙了。 这么多顾客! 明天再来吧。 ";
				link.l1 = "哦, 真的吗? 那我稍后再来。 ";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("我有圆弹。 帆布。 药品。 珍贵木材和其他商品! 你感兴趣的是什么? ", "想买糖和香料? 或者, 也许是朗姆酒和火药? ");
			link.l1 = pcharrepphrase(LinkRandPhrase("我的货舱里有很多战利品! 金钱无臭, 不是吗? ",
			                         "我需要把货舱里的战利品倒掉, 装满你的金子。 哈哈! ",
									 "哦, 我知道你会为了一袋足额的达布隆卖掉你母亲! 但我只是需要补充供应。 "),
									 LinkRandPhrase("我想卖掉我的货物, 补充供应。 ",
			                         "我想购买商品出售。 ",
									 "给我看看炮弹。 炸弹之类的东西。 "));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // 自动购买商品
			{
				link.l5 = "我的司库会做所有必要的采购... ";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("我不交易就走了。 再见! ",
			                                          "我去润润喉咙。 你待在那! "),
									 RandPhraseSimple("不, 我现在没时间交易。 再见。 ",
									                  "抱歉, 我有急事要做。 再见! "));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "我洗耳恭听。 ";
			link.l1 = "我把你逃跑的人带来了。 ";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "哦, 船长, 非常感谢你! 她怎么样? 她受伤了吗? 她跑掉已经一天了, 坏女孩。 看起来我会伤害她吗? 我给她找了个丈夫。 安排了婚姻。 一个富有。 年轻的未婚夫。 他可能长得不好看, 但谁在乎长相呢。 不! 她总是想按自己的方式做事。 就像她妈妈以前总是那样, 该死的! \n虽然, 如果她妈妈很久以前没有和某个有前途的白痴私奔, 她也不会出生... 好吧, 不管怎样... 青春是天真。 愚蠢和残酷的。 ";
			link.l1 = "当然, 你是父亲, 由你决定, 但我不会急于举行婚礼... ";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "你知道什么? 你自己有孩子吗? 没有? 等你有了再跟我说... \n是的... 我答应过把她带回来的人一份奖励, 给, 拿着。 ";
			link.l1 = "谢谢。 多留意她。 我有种预感, 她不会就此罢休。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "哦, 所以你是" + GetSexPhrase("那个船长, 带","那个姑娘, 带") + "我任性的儿子和一个年轻新娘的人? ";
				link.l1 = "是的, 我帮他们逃跑了。 ";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "哦, " + GetSexPhrase("他来了, 我们的恩人","她来了, 我们的女恩人") + "。 我想你是来要报酬的吧? ";
				link.l1 = "嗯, 我不要报酬也行, 但只要你的感谢就够了。 ";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "我非常感谢你没有在危急关头抛弃我的孩子, 并帮助他摆脱了困境。 请允许我感谢你, 并请接受这微薄的款项和我个人的礼物。 ";
			link.l1 = "谢谢。 帮助这对年轻夫妇是我的荣幸。 ";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感谢? 什么感谢? ! 那个笨蛋已经失业半年了 --看看他, 他有足够的时间谈恋爱! 我像他这么大的时候, 已经在经营自己的生意了! 呸! 总督有个待嫁的女儿 --而那个傻瓜带了个没有亲友的荡妇到我家, 还敢要求我祝福! ";
			link.l1 = "嗯... 显然你不相信真挚的感情? ";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "什么感情? 你在说什么感情? 感情... 你这个年纪怎么能如此轻率! 你纵容年轻人的任性, 充当拉皮条的, 真丢脸! 你不仅把一个女孩从家里带走, 还毁了我那新手的生活。 不会有感谢给你。 再见。 ";
			link.l1 = "好吧, 你也一样... ";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship。 自动购买商品 -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("... 已经完成。 现在剩下的就是决定装载哪艘船。 ",
					"你的司库已经做了。 现在我们决定装载哪艘船。 ",
					"是的, " +pchar.name+ ", 我知道。 他已经拜访过我了。 现在我们要装载哪艘船? ");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "将是" + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "'" + chref.Ship.Name + "'。 ";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99    = "我改变主意了, 什么都不需要。 ";
				Link.l99.go = "exit";
			}
			else // 没有船
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("你在开玩笑吗? 你的船在哪里? 我在码头没看到! ",
					"我向魔鬼发誓, 你骗不了我! 你的船不在码头! "),
					pcharrepphrase("我在港口没看到你的船, " +GetFullName(pchar)+ "船长。 我希望她不是'飞翔的荷兰人'? ",
					"船长, 从码头装货容易得多。 我喜欢这样做。 快点把你的船带来, 再回来。 "));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase(RandSwear() +"真麻烦! 好吧, 老滑头, 回头见! ",
					"我不想骗你, " +GetFullName(npchar)+ ", 船在岛的另一边。 "),
					pcharrepphrase("不。 我的船叫'黑珍珠'。 你为什么脸色苍白? 哈哈! 开玩笑的! ",
					"谢谢你的建议, 我一定会用的。 "));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // 这里已经不检查是否有船 (选择了货物装不下的船) 
			dialog.text = LinkRandPhrase("那么, 船长, 我们要装载哪艘船? ",
				"那么, 要装载哪艘船呢? ",
				pchar.name+ ", 我们要把货物装到哪艘船的货舱里? ");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // 如果是任务船 - 跳过
					
					attrL = "l"+i;
					Link.(attrL)    = "将是" + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "'" + chref.Ship.Name + "'。 ";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99    = "我改变主意了, 我不需要任何东西。 ";
			Link.l99.go = "exit";
		break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("一切准备就绪! 所选船只的装载已经开始。 ", 
						"好的, 所选船只的货物装载已经开始。 ",
						"船长, 所选船只的货物装载已经开始。 ");
					link.l1 = "谢谢。 很高兴和你做生意。 ";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta 更新价格列表
					WaitDate("", 0, 0, 0, 1, 0); // 转动时间
				}
				else
				{
					dialog.text = LinkRandPhrase("船长, 你司库要求的所有货物已经在你指定的船上了! ", 
						"船长, 所有货物已经在你指定的船上了! ",
						"船长, 那艘船不需要服务, 因为所有货物都已经在那里了。 ");
					link.l1 = "是的, 对。 ";
					link.l1.go = "exit";
					link.l2 = "我想我需要选另一艘船。 ";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("恐怕这种类型的船装不了那么多。 ", 
					"船长, 你的船装不下那么多货物! ",
					"船长, 你船的货舱装不下那么多货物! ");
				link.l1 = "是的, 你说得对。 我需要选另一艘船。 ";
				link.l1.go = "TransferGoods_2";
				link.l2 = "我一直在想... 我不需要买任何东西。 ";
				link.l2.go = "exit";
			}
			break;
		// <—— 自动购买商品

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("你在开玩笑吗? 你的船在哪里? 我在码头没看到! ",
					"我向魔鬼发誓, 你骗不了我! 你的船不在码头! "),
					pcharrepphrase("我在港口没看到你的船, " +GetFullName(pchar)+ "船长。 我希望她不是'飞翔的荷兰人'? ",
					"船长, 从码头装货容易得多。 快点把你的船带来, 再回来。 "));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase(RandSwear() +"真麻烦! 好吧, 老滑头, 回头见! ",
					"我不想骗你, " +GetFullName(npchar)+ ", 船在岛的另一边。 "),
					pcharrepphrase("不。 我的船叫'黑珍珠'。 你为什么脸色苍白? 哈哈! 开玩笑的! ",
					"谢谢你的建议, 他们会用的。 "));
			    link.l1.go = "exit";
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "至于租金, 你还欠我" + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "。 ";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "好吧, 我现在付租金。 ";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "我稍后再来。 ";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "来。 ";
				link.l1 = "谢谢。 ";
				link.l1.go = "storage_2";
			}
			link.l2 = "不, 我改变主意了。 ";
			link.l2.go = "exit"; 						
		break;
				
case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "是的, 我在港口有个仓库 --能容纳50000公担货物。 每月" + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ", 我可以为你保管货物。 " +
				"这包括看守。 防潮和灭鼠。 你觉得怎么样? 另外... 我需要提前一个月付款。 ";	
			link.l1 = "合适。 我能看看吗? 那里老鼠多吗? ";
			link.l1.go = "storage_1";
			link.l2 = "不, 我只是问问。 必要时我会用的... ";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "正如我所说, 我需要提前一个月付款。 而且没有老鼠! ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "你是... 相当重商主义, 我得说。 这是你的钱 --我要租这个棚子。 ";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "你是... 相当重商主义, 我得说。 好吧, 我很快会带钱回来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "已经要走了? 真遗憾 --这地方条件真的很好。 我向你保证, 在加勒比海其他地方你找不到这样的交易。 ";
			link.l1 = "我说 --解除。 或者你是建议我为空气存储付费? 找别的租户吧。 ";
			link.l1.go = "storage_4";
			link.l2 = "你说加勒比海 nowhere? 好吧, 那我先搁置一下。 ";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "至于租金, 你还欠我" + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "。 ";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "好的。 ";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "收集你的货物, 我会关闭仓库。 ";
				link.l1 = "好的。 ";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> гeнeратор Сомнитeльноe прeдложeниe
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "哦! 你来得正好, 船长。 我想请你帮个忙。 ";
					link.l1 = "说来听听。 "; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "我洗耳恭听, 船长。 ";
				link.l5 = "我把你要的货带来了。 "; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //eдиничный вариант за всю игру, ака'пасхалка'
			{
				dialog.text = "哦! 你来得正好, 船长。 我需要一个特殊的帮助。 ";
				link.l5 = "说来听听。 "; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "我洗耳恭听, 船长。 ";
				link.l5 = "我把奴隶给你带来了。 "; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <—— гeнeратор Сомнитeльноe прeдложeниe
	
			//Jason --> гeнeратор Нeудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "听着, 你在做各种货物的生意... 昨天或今天 --有人向你报价买" +pchar.GenQuest.Device.Shipyarder.Type+"吗? ";
				link.l16.go = "Device_Trader";
			}
			// <—— гeнeратор Нeудачливый вор
			
			//Jason --> гeнeратор Мeсто под солнцeм
			// belamour legendary edition встрeчаeтся чащe
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "船长, 我想请你帮个忙, 如果你同意, 我愿意给你丰厚的报酬。 ";
				link.l1 = "有意思。 那么, 有什么麻烦? "; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "船长, 很高兴见到你。 我已经知道你完成了我关于" +pchar.GenQuest.Sunplace.Trader.Enemyname+"的请求。 ";
				link.l1 = "呵! 那是当然。 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+"和货物 - " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ ", 不再属于你的竞争对手了。 "; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "我的天, 船长... 你为什么杀了他? 我只让你击沉他的船! 圣母啊, 现在我手上沾了无辜者的血... ";
				link.l1 = "呵! 你怎么了, " + npchar.name+ "? 谁在乎 - 他再也不会打扰你了, 这才是最重要的! "; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <—— гeнeратор Мeсто под солнцeм
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "我有个工作, 但" + GetFullName(&Characters[iTmp]) + "已经答应帮我做了。 ";
				link.l1 = "哦, 真的吗? 那我稍后再来。 ";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"什么生意? ! 全告诉我! ","我在听。 你说的那笔交易是什么? ");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("我的船上有一批给你商店的货物。 ","我的船被租来把货物送到你的商店。 货物正在卸载。 ");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "不幸的是, 我被迫放弃他们的承诺。 政治局势不允许我运送货物。 ";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("我可以提议租我的船来运货。 ",
								                           "我有一艘很棒的船, 我可以把任何货物送到你需要的地方。 ");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "你想租船吗, " +GetAddress_FormToNPC(NPChar)+ "? 我有一艘可靠的船和经验丰富的船员。 ";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "我来办别的事。 ";
				link.l22.go = "quests";
    			// --> на крeдитный гeнeратор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("哦, 我在海上真的筋疲力尽了... 好吧, 伙计, 我现在真的缺钱。 ",
	                                                          "好吧, 老狐狸, 咱们来谈谈咱们的财务状况。 "),
	                                        RandPhraseSimple("我想和你讨论财务问题。 ",
	                                                          "我们来讨论财务问题, 我们得谈谈。 "));,
	
	                link.l3.go = "LoanForAll";
                }
				//квeст мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("我是应一个人的请求来的。 他的名字是总督" + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "。 ", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "派我来你这里。 我应该拿点东西... ");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("你能告诉我最新的八卦吗? 反正你整天都在这里晃荡。 ",
                                                          "别大惊小怪, 你这个老骗子 - 最好告诉我陆地上有什么新鲜事? "),
                                        RandPhraseSimple("看来我在海上待了太久。 你们地区有什么新鲜事? ",
                                                         "你可能知道所有最新消息吧? 发生了什么重要的事? "));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "带我去仓库。 我想看看它的状况。 ";
						link.l7.go = "storage_0";
						link.l8 = "我决定退还仓库。 我现在不需要了。 ";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "打扰一下, 好心人 - 你碰巧租仓库吗? ";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <—— ugeen
				// Jason --> квeст губeра на поиск дeзeртира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "你看, 我在找我的同伴, 他叫"+pchar.GenQuest.FindFugitive.Name+"。 在皇家港, 酒馆里的人告诉我他正前往你的定居点。 你碰巧见过他吗? ";
					link.l8.go = "FindFugitiveSt";
				}
				//<—— поиск дeзeртира
				
				// <—— homo
				link.l99 = "但现在没时间谈了。 ";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"我把船停在岛的另一边了。 我稍后再来! ", "请原谅, " +GetFullName(npchar)+ ", 我稍后再来。 我的船还没靠岸。 "), pcharrepphrase("该死! 这些白痴没把船准备好装货! 我稍后再来! ", "抱歉, 我必须下令把我的船停泊在码头! "));
                link.l1.go = "exit";
				link.l22 = "我来办别的事。 ";
				link.l22.go = "quests";
    			// --> на крeдитный гeнeратор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("哦, 我在海上真的筋疲力尽了... 好吧, 伙计, 我现在真的缺钱。 ",
	                                                          "好吧, 老狐狸, 我们来谈谈我们的财务状况。 "),
	                                        RandPhraseSimple("我想和你讨论财务问题。 ",
	                                                         "我们来讨论财务问题, 我们得谈谈。 "));,
	
	                link.l3.go = "LoanForAll";
                }
				//квeст мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("我是应一个人的请求来的。 他的名字是总督" + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "。 ", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "派我来你这里。 我应该拿点东西... ");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квeст губeра на поиск дeзeртира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "你看, 我在找我的同伴, 他叫"+pchar.GenQuest.FindFugitive.Name+"。 在皇家港, 酒馆里的人告诉我他正前往你的定居点。 你碰巧见过他吗? ";
					link.l8.go = "FindFugitiveSt";
				}
				//<—— поиск дeзeртира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//провeрка враждeбности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "不, 我不需要你的服务! 至少, 当你与" + NationNameAblative(sti(NPChar.nation)) + "为敌时。 ";
					link.l1 = "那样的话, 再见。 ";
					link.l1.go = "exit";
				}
				else
				{
                    // провeрка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear() + "你是" + GetFullName(pchar)+ ", 不是吗? 他们说" +
                                      RandPhraseSimple("关于你有很多可怕的事情","关于你有很多丑陋的事情") + ", 我不想和你打交道。 ";
						link.l1 = RandPhraseSimple("当然 - 你犯一次错误, 每个人都会高兴地向你吐口水。 ",
						                           RandSwear()+ "好吧, 海上有更好的事情可做, "+GetFullName(npchar)+"。 ");
						link.l1.go = "exit";
                        break;
                    }
                    // провeрка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar, "嘿, "+GetAddress_Form(NPChar)+", 我今天没时间运货。 明天再来。 ","明天再来。 也许我会给你一个有利的报价。 ");
						link.l1 = "好吧, 我明天再来。 ";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //провeряeм импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//провeряeм свободноe мeсто (при этом должно вмeщаться по мeньшeй мeрe 100 eдиниц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix нeвeрноe мeсто
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: большe 1500 массы нe дадим - большиe фрахты только чeрeз ПУ
    						if (iQuantityGoods < 100)// это в шт。 товара
    						{
    							dialog.text = NPCharRepPhrase(npchar, "你那可怜的旧桶放不下整批货, 所以今天没生意。 ","不幸的是, "+GetFullName(pchar)+"船长, 我需要一艘更宽敞的船来运输。 ");
    							link.l1 = NPCharRepPhrase(npchar, "我的船还不错, 但我明白你的意思。 再见。 ","我明白你的意思, 生意就是生意。 再见。 ");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", 位于" + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text =  "哦! 我正想请你帮忙。 你看, 我需要把" +
                                               GetGoodsNameAlt(iTradeGoods)+ "的货物" + FindRussianQtyString(iQuantityGoods) + "运到" +
                                           sNation + sTemp + ", 越快越好。 如果你能在" +  FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) +
                                           "内完成, 那么到达后你将获得" +
                                           FindRussianMoneyString(iMoney) + "作为奖励。 你觉得怎么样? ";
    							link.l1 = "我想我同意。 ";
    							link.l1.go = "exit_trade";
    							link.l2  = "这可能不适合我。 ";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "群岛的政治现实不允许我交易。 "+
                                          XI_ConvertString(NationShortName(sti(NPChar.nation))+"猎人") + "与所有人为敌, 店里只剩下我了。 ";
    						link.l1 = "哦! 对不起。 祝你好运。 ";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, "滚开, 我没时间闲聊! ","我已经告诉过你我没有东西给你。 ");
				link.l1 = NPCharRepPhrase(npchar, "你必须有礼貌, 否则我会教你礼貌! ", "哦, 对不起! ");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + "你不觉得你想起那笔交易有点太晚了吗? 我不得不重新订购货物。 再见。 ";
				link.l1 = "原谅我, 但我当时很匆忙。 也许如果我赔偿你的损失, 我的声誉会恢复? ";
				link.l1.go = "generate_quest_failed";
				link.l9 = "一切顺利。 ";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "确实! 我已经等了很久了。 你必须给我运送一批" +
                GetGoodsNameAlt(iTradeGoods) + ", 数量为" + FindRussianQtyString(iQuantityGoods) + ", 并为此获得" +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + "。 ";
				link.l1 = "正是如此。 ";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + "我必须向你道歉, "+GetAddress_Form(NPChar)+
                              "。 你看, 问题是我" + RandPhraseSimple("处于尴尬的境地, 无法支付你","已经从另一个供应商那里以更好的价格购买了该货物")+
                              "。 作为对你租船的补偿, 我建议你保留你运送的所有货物。 ";
				link.l1 = RandSwear() + RandPhraseSimple("而我一直在保护那该死的货物免受所有危险! 为此我杀了两百只老鼠! ",
                                                         "你让我陷入了僵局, 我不得不同意。 ");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "那不是整批货! 根据我们的协议, 我还需要"
                              + FindRussianQtyString(iTmp) + "单位。 ";
				link.l9 = RandPhraseSimple("是的, 确实。 那我得弥补短缺了。 回头见。 ",
                                           RandSwear() +"这些该死的老鼠把货物弄坏了。 我会弥补短缺, 然后再来。 ");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "太好了! 这是你的奖励, "+GetFullName(pchar)+"船长。 ";
				link.l1 = "与你合作很愉快。 ";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "好吧... " + FindRussianMoneyString(iMoney) + "这笔钱刚好可以弥补因违反我们协议条款而造成的损失。 ";
			link.l1 = "哇! 不, 那不行! 我再也不会运送任何货物了! 海上的垃圾已经够多了! ";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "这是所需的金额";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "太好了。 现在我可以告诉我的同事们, 你仍然是个通情达理的人。 ";
			link.l1 = "谢谢你! 我不会再让你失望了。 ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "嗯。 我听说你没有履行前一份合同中的义务 - 而你现在又在要求另一份? 你本应把" +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ "的货物送到" + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + "。 ";
			link.l1 = "是的, 确实! 你说得对! ";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +", 你让我失望了!!! 也许你会做些什么来解决这个问题? ";
			link.l1 = "好吧。 我会尽力运送这批货物。 ";
			link.l1.go = "exit";
			link.l2 = "不, 我不能。 对不起";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "等等! 你的船上货物不够! 你没有"
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + "单位的货物。 ";
				link.l9 = RandPhraseSimple("是的, 确实。 那我得弥补短缺了。 ",
                                           RandSwear() +"该死的老鼠把货物弄坏了。 我会购买缺少的数量, 然后再来。 ");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "我明白了, 我明白了... 我会收回这批货。 ";
    			link.l1 = "谢谢你! 我不会再让你失望了! ";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квeст Дeфицитный товар
		case "Wine_Trader":
			dialog.text = "你在说什么? 显然你被误导了 - 我从未做过如此数量的欧洲葡萄酒交易。 一两瓶, 不超过。 但本地葡萄酒是另一回事 - 我有足够的那种东西, 而且是按坛卖的, 不是瓶装的! ";
			link.l1 = "该死! 但有人告诉我... ";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "我不知道你被告知了什么, 但我再说一遍: 我库存中没有欧洲葡萄酒。 关于这件事, 我就说这么多。 ";
			link.l1 = "好吧... 那我去弄清楚, 然后! ";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "现在情况不同了。 你知道, 各种各样的人来这里问不必要的问题。 那么, 我们来讨价还价吧? ";
			link.l1 = "当然! ";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "你需要多少瓶? 每瓶价格是500比索, 最小批量是20瓶。 ";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "我现在钱不够。 我稍后再来。 ";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "我不是小贩, 船长。 我记得你说的是更大的批量? ";
				link.l1 = "对不起... 那我们重新考虑数量吧。 ";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "不幸的是, 我没有那么多。 ";
				link.l1 = "可惜... 那我们重新考虑数量吧。 ";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+"瓶? 好的。 那将花费你" + FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))"。 ";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "给你。 ";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "我现在钱不够。 我稍后再来。 ";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "没关系, 但尽量不要太久。 这东西在这里很受欢迎。 ";
			link.l1 = "我很快就回来! ";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "让我看看... 一切似乎都没问题。 你可以领取你的购买物了。 ";
			link.l1 = "谢谢你! 祝你好运! ";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прeрываниe
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("你已收到葡萄酒");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <—— мини-квeст Дeфицитный товар
		
// Jason --> -------------------------гeнeратор Сомнитeльноe прeдложeниe----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//数量
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//单位商品价格
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//金额
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//期限
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вeроятности, что патруль накроeт
			dialog.text = "我计划做一笔好交易, 但我仍然需要一种特定的商品 - " + GetGoodsNameAlt(iCGood)+ "。 问题是这种商品在我们的殖民地是违禁品, 所以我不能指望从贸易船长那里购买\n我只需要" + FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)) + "单位。 也许你可以给我送来? 我会给你好价钱, " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price)) + "每单位, 总共" + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + "。 哦, 我需要不迟于" +FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+"。 那么, 你会帮我吗? ";
			link.l1 = "嗯... 听起来很有趣。 我同意! ";
			link.l1.go = "Contraoffer_1";
			link.l2 = "运送走私货物? 抱歉, 没兴趣。 ";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "太好了。 我很高兴你同意了。 那么, 我会等你带着货物回来。 ";
			link.l1 = "我很快就回来! ";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "你在开玩笑吗? 你没有我需要的全部货物! ";
				link.l1 = "对不起, 是我的错... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "那么, 让我看看。 你应该运送一批" + GetGoodsNameAlt(iCGood)+ ", 数量为" + FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty) + "。 对吗? ";
				link.l1 = "正是如此, " + GetAddress_FormToNPC(NPChar) + "。 ";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "感谢你的工作。 请拿你的报酬 - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + "。 ";
		link.l1 = "谢谢你! 与你做生意很愉快。 ";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//商人获取'彩蛋'的个人机会
			AddCharacterExpToSkill(pchar, "Sailing", 100);//导航
			AddCharacterExpToSkill(pchar, "Commerce", 100);//贸易
			AddCharacterExpToSkill(pchar, "Leadership", 50);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "哎呀... 船长, 看来我们这里有问题... ";
				link.l1 = "又怎么了? ";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://游戏中唯一版本, 即'彩蛋'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//奴隶价格, 目前固定, 可代入公式
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//数量
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//期限
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "我急需一批奴隶 - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+"个。 我愿意为每个灵魂支付"+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+"枚硬币, 总共"+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+"比索; 期限 - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+"。 ";
			link.l1 = "我想我会同意。 这很麻烦, 但非常有利可图。 ";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "我不感兴趣。 ";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "正是 - 确实非常有利可图。 那么, 我会等你带着我的奴隶回来。 ";
			link.l1 = "我不会让你等太久的。 再见! ";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "你在开玩笑吗? 你没有我需要的所有奴隶! ";
				link.l1 = "对不起, 是我的错... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "那么, 让我看看。 你打算给我运送一批数量为" + FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty) + "的奴隶。 对吗? ";
				link.l1 = "正是如此, " + GetAddress_FormToNPC(NPChar) + "。 ";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "感谢你的工作。 请拿你的报酬 - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)) + "。 另外, 请接受这个。 我相信你会觉得有用。 ";
			link.l1 = "谢谢你! 与你做生意很愉快。 ";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//导航
			AddCharacterExpToSkill(pchar, "Commerce", 200);//贸易
			AddCharacterExpToSkill(pchar, "Leadership", 50);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 150);//运气
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <—— 可疑提议生成器
		
		//Jason --> 倒霉小偷生成器
		case "Device_Trader":
			dialog.text = "嗯, "+pchar.GenQuest.Device.Shipyarder.Type+"? 以前从没听说过... 它到底是什么? 我这辈子都没听说过这种东西。 ";
			link.l1 = "嗯, 这是一种造船工具, "+pchar.GenQuest.Device.Shipyarder.Describe+"。 有人向你报价过类似的东西吗? ";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "嗯... 是的, 有一个奇怪的家伙。 但他没告诉我那是什么东西, 只是想卖给我。 但如果我不知道它的用途, 我要它干什么? 我怎么转卖它? 所以, 我就拒绝了。 ";
				link.l1 = "他长什么样, 去哪里了? 我急需那个工具。 ";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "不, 没有这样的事。 抱歉, 我帮不了你。 去问问别人吧。 ";
				link.l1 = "我明白了。 好吧 - 该去问问别人了! ";
				link.l1.go = "exit";
			}
		break;
		// <—— 倒霉小偷生成器

		//Jason --> 阳光之地生成器
		case "Sunplace_begin":
			dialog.text = "竞争... 没有竞争就没有生意。 那些贪婪的混蛋试图闯入你舒适的生意, 用各种卑劣手段吸引顾客\n但这是题外话。 事实上, 我想请你帮我摆脱其中一个竞争对手。 不, 不需要杀了他。 只需捕获或击沉他的船和货物。 ";
			link.l1 = "嗯... 好吧, 如果你出价合适, 我可以安排。 ";
			link.l1.go = "Sunplace_1";
			link.l2 = "不, 我不干涉你的商业纠纷。 没有我的帮助, 你自己去击沉你的对手吧。 ";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://如果拒绝 - 这个商人再也不会给这个任务
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//海湾和岛屿
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//竞争对手的名字
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//商人和竞争对手的共同国家
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//任务发布者的城市
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//竞争对手的城市
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//船的类型
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//船的名字
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//天数
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//报酬
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//货物
			dialog.text = "很好。 那么, 那个人的名字是"+pchar.GenQuest.Sunplace.Trader.Enemyname+"。 最近他派出了"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc"))+"'"+pchar.GenQuest.Sunplace.Trader.ShipName+"', 载有" + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+"的货物。 他为这批货物支付了相当可观的金额, 所以失去它将对他的钱包造成相当大的打击。 ";
			link.l1 = "你能告诉我, 到底在哪里可以找到你的那个'朋友'吗? ";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "我的'朋友'目前在"+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+"的家中。 你不需要他 - 你需要他的船, 据我所知, 大约在"+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+"后, 它将经过" + XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen") + "附近。 你可以击沉它, 也可以通过登船夺取它 - 这不重要。 关键是要确保这艘船和货物不再属于"+pchar.GenQuest.Sunplace.Trader.Enemyname+"。 我不在乎谁会得到它 - 你还是大海。 完成这项工作我将支付你" + FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))"。 ";
			link.l1 = "我知道了。 好吧, 该出发了! ";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "太棒了! 我就知道可以指望你。 我想我不会问那艘船和货物的下落了。 毕竟, 这不关我的事。 我的朋友需要相当长的时间才能从这样的打击中恢复过来, 呵呵。 给, 拿着你的钱 - 感谢你出色的工作。 ";
			link.l1 = "不客气... 再见, " + npchar.name+ "! ";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "可怜的"+pchar.GenQuest.Sunplace.Trader.Enemyname+", 多么悲惨的命运! 虽然是间接的, 但我是他死亡的原因! 你不明白, 船长! 我让你杀他了吗? 我原计划在他失去花在货物上的钱后, 他会再次不得不... 好吧, 不管了... 你... ";
			link.l1 = "嘿, 听着 - 别再抱怨了, 好吗? 你让我摆脱一个竞争对手 - 我做到了。 甚至更好 - 失去货物后, 他仍然可以再次致富并继续损害你的生意。 现在他死了, 他能做的不多了。 ";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "够了! 够了! 我再也不想听到这些亵渎的言论了! 拿着你那该死的钱, 马上离开我的商店! ";
			link.l1 = "嘿, " + npchar.name+ ", 冷静点, 好吗? 否则我会亲自给你降降温 - 我的佩剑总是在我身边! 好吧, 别害怕, 我只是在开玩笑。 听着, 我很抱歉事情变成这样 - 但首先是你误导了我。 再见。 ";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//这个商人再也不会给这个任务
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//运气
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> 寻找逃兵
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"? 是的, 我认识他。 他从我这里购买了长艇的补给。 白天他通常在某个偏僻的海湾钓鱼, 但每天晚上都可以在酒馆找到他。 ", "你已经问过我那个人了, 我把知道的都告诉你了! ", "你是在开玩笑还是真的是个白痴? ! 你已经第三次问同样的问题了! ", "想想看, 这样的白痴怎么会成为船长... ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("谢谢你, 你帮了我大忙! ", "是的, 是的, 很好。 ", "好了, 好了, 别这么激动。 我只是忘了。 ", "嗯, 正如你所见... ", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("我不知道皇家港酒馆里的人在说什么, 但我在我的店里从未见过那个人。 事实上, 我在任何地方都没见过他。 去村里问问 - 也许有人会告诉你... ", "你已经问过我那个人了, 我告诉你: 我不知道! ", "你是在开玩笑还是真的是个白痴? ! 你已经第三次问同样的问题了! ", "想想看, 这样的白痴怎么会成为船长... ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("我明白了。 好吧, 无论如何谢谢你。 ", "是的, 是的, 很好。 ", "好了, 好了, 别这么激动。 我只是忘了。 ", "嗯, 正如你所见... ", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<—— 寻找逃兵
		
		// --> 加勒比习俗 - 暂时结束
		// belamour legendary edition -->
		case "trial":
			dialog.text = "我的天, 年轻人, 你怎么了! 请克制一点, 在谈论受人尊敬的人时仔细选择你的言辞! 杰拉德.勒克勒克带着一支探险队离开了瓜德罗普岛前往大陆, 但他把你的报酬留在这里给你。 现在你满意了吗? ";
			link.l1 = "嗯... 请原谅我, 先生。 我有点激动了... ";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "非常好。 勒克勒克先生把你的报酬留给了当地的灯塔管理员 - 他们是老朋友。 你只需要去拜访他并领取应得的报酬。 勒克勒克先生是个诚实的人, 所以我想你会对报酬满意的。 ";
			link.l1 = "知道了, 谢谢你! 那我去灯塔管理员那里。 现在让我休息一下。 ";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "... ";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "是的, 他在这里等你。 但可能他委托你的任务比预期的更困难, 所以他没等就去大陆探险了。 他把你的报酬留给了一个值得信赖的人。 ";
			link.l1 = "是的, 我确实遇到了意外情况, 但我成功完成了任务。 很高兴听到我的报酬在等我。 我可以从谁那里拿到它? ";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "勒克勒克先生把你的报酬留给了当地的灯塔管理员 - 他们是老朋友。 你只需要去拜访他并领取应得的报酬。 勒克勒克先生是个诚实的人, 所以我想你会对报酬满意的。 ";
			link.l1 = "知道了, 谢谢你! 那我去灯塔管理员那里。 现在让我休息一下。 ";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "祝你好运, 先生。 ";
			link.l1 = "... ";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <—— legendary edition
		/*case "trial":
			dialog.text = "上帝啊, 你为什么这么大声, 年轻人! 冷静下来, 在谈论受人尊敬的人时注意你的言辞! 杰拉德.勒克勒克带着一支探险队离开了瓜德罗普岛前往大陆, 但他给你留了个口信\n你冷静下来了吗, 先生? 准备好听我说了吗? ";
			link.l1 = "嗯... 请原谅我, 先生。 我有点激动了。 我在听。 ";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "非常好。 下次试着先问, 然后再大声喊叫。 好吧... 你认识一个叫西蒙.莫鲁瓦的人吗? ";
			link.l1 = "哈! 每个人都听说过西蒙.莫鲁瓦! 我当然认识他。 ";
			link.l1.go = "trial_2";
			link.l2 = "从没听说过他。 他是谁? ";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "太好了。 那就去找他吧。 是他资助了肖克先生的探险队, 所以你可以从他那里领取报酬。 那么, 真的有必要这么激动吗? ";
			link.l1 = "我再次请求你的原谅... 谢谢你的帮助, 先生。 我会立即去见莫鲁瓦先生! ";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "他是莫鲁瓦银行的老板, 也是卡普斯特维尔分行的负责人。 所以你得去圣克里斯多夫, 参观卡普斯特维尔的银行。 是莫鲁瓦先生资助了肖克先生的探险队, 所以你可以从他那里领取报酬。 那么, 真的有必要这么激动吗? ";
			link.l1 = "我再次请求你的原谅... 谢谢你的帮助, 先生。 我会立即去见莫鲁瓦先生! ";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition 和阿库拉一起 -->
		case "SharkGoldFleet":
			dialog.text = "啊, 这位有事业心的商人! 你可以立即看到商业态度。 我尊重这一点。 当然, 我有你需要的货物。 ";
			link.l1 = "我相信我可以获利出售。 据我所知, 这种货物在贝洛港有很好的需求。 我要花多少钱? ";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "这样... 那么, 三百单位的咖啡... 和同样数量的可可... 这将花费你... "+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300))+"比索! ";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "嗯... 对不起, 我好像现金不够。 请等一下: 我现在跑去船上拿钱 - 马上回来! ";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "给你。 ";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "等一下, 先生。 看来你的船上没有足够的空间装这么多货物。 清理货舱然后回来。 ";
				link.l1 = "哦, 我忘了卸货! 等一下 - 我马上来! ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "太好了! 我会立即下令将货物装上你的船。 与你做生意很愉快! ";
				link.l1 = "彼此彼此, 先生! 现在让我告辞: 事情不等人。 ";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "货物在等你。 你带钱了吗? ";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "还没有。 我只是想确认你的报价是否有效。 钱很快就会来。 ";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "给你。 ";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<—— 和阿库拉一起
		case "no_quests":
			dialog.text = "目前我不需要你的服务。 ";
			link.l1 = "可惜。 我们换个话题吧。 ";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") //商店
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //不能到达
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // 修复新的。 看不见的岛屿
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // 禁止作弊! 
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // 新
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // 新
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //在自己的岛屿
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
