void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "你想要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "欢迎来到寒舍! 我是克里斯蒂安。 克里斯蒂安.德吕斯, 为您效劳。 什么风把您吹到我家门口了? ";
			link.l1 = "在下"+GetFullName(pchar)+"船长。 我想采购大量烈酒。 相信我表达得很清楚? ";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "什么??? 谁在散播这种谎言? 严重的误解, 我向您保证! 我绝不做任何烈酒生意! ";
			link.l1 = "嗯, 看来我找对人了。 ";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "哦, 天哪, 不-不-不! 您这是在指控什么! 做烈酒生意? 我? 我只是, 呃, 也就是说... 好吧, 我确实有一些酒, 但完全合法! 我只是为市民采购饮品, 啊... 用于庆祝活动和小型社交聚会! ";
			link.l1 = "您为什么发抖, 好人? 我不是来抓您的狱卒, 而是来给您送福利的。 您的财富可能会增加, 我的钱包也能多几个杜布隆。 ";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "我? 紧-紧张? 荒谬! 我有什么可紧张的? 我是个品格无瑕的人 --我的住所就在总督官邸的阴影下! 我以名誉担保, 绝不触犯任何法律! ";
			link.l1 = "所以您不做烈酒生意? 真是太遗憾了。 我本想给您带来一个赚大钱的机会。 那种普通的秘密商人难以想象的杜布隆。 但既然您不是我要找的人, 我就不打扰了, 这就告辞。 除非... ? ";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "啊... 等一下... "+GetAddress_Form(NPChar)+"... 请原谅, 我脑子像暴风雨中的海鸥一样混乱, 完全忘了您尊贵的名字。 ";
			link.l1 = "我是"+GetFullName(pchar)+"船长。 ";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("先生","女士")+" "+pchar.lastname+", 说实话, 我... 也就是说... 我可能知道您要找的人在哪里。 我可以把您的慷慨提议转告给这个人... ";
			link.l1 = "转告? 您一定是在开玩笑。 您真的认为这种微妙的事情应该经过不必要的人手吗? ";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "您说得对。 但是... 上帝保佑我... 事已至此... 是的, 我确实是您要找的人。 ";
			link.l1 = "现在我们相互理解了, 克里斯蒂安。 酒馆严重缺酒, 我相信我们都能从这种情况中获利。 ";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "船长, 我很清楚酒馆老板的困境。 人们一直来我这里, 这让我害怕继续做小生意 --现在太多人关注了。 我曾希望也许您... 嗯, 像您这样有地位的人可能... ";
			link.l1 = "您为什么不自己带着货物去找酒馆老板? ";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "他... 他宁愿拥抱麻风病人也不愿和我做生意。 那个自大的傻瓜对我这种地位的小商人只有蔑视。 ";
			link.l1 = "的确, 他的名声在外。 他可能会直接拒绝您的货物。 但通过我来介绍 --那就是另一回事了。 ";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "您愿意做中间人? 我觉得这个安排很合适... 我们最近进了一批数量惊人的货 --以前从未有过这么多! 本来可以让我的地窖储备半年。 但感谢万能的上帝, 我们侥幸逃脱了被发现的命运\n仍然无法想象我们是如何躲过总督的法网的。 这样的命运诱惑两次简直就是自毁。 ";
			link.l1 = "那么也许是时候您走向光明了。 不过不是完全公开, 而是足以让您的事务在更少风险的情况下进行。 ";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "走-走向光明? 但是... 为什么, 那需要强大的朋友! 还有大量的钱! 为了什么目的? 当然, 您, 一位有自己船只的船长, 不打算永久停泊, 成为一个 mere 酒馆供应商吧? ";
			link.l1 = "至于关系, 我的人脉延伸到您无法到达的地方。 关于资金... 投资应该是适度的。 至于您最后的顾虑 --别担心。 您将在这些事务中作为我的代理人。 我将是您的盾牌, 您是我可靠的货源。 我们的安排将是持久且互利的。 您获得可靠的客户, 我获得可靠的商品。 您觉得这个提议如何? ";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "我曾确信这是一个精心策划的陷阱。 但事实上, 您的提议听起来... 确实很诱人。 稳定, 可靠... 我从未想过这样的幸运会降临到我身上。 "+GetSexPhrase("先生","女士")+", 我全心全意同意! 您想购买多少? ";
			link.l1 = "我们首先要让您的生意步入正轨, 然后再讨论细节。 您的仓库里现在有多少朗姆酒和葡萄酒? ";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "现在吗? 啊... 也许我们应该检查一下我的地窖, 在那里我可以准确统计我的库存。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// 我们下到地窖
		break;
		
		// 地窖
		case "Kristian_15":
			dialog.text = "让我看看... 下面有什么宝贝? 啊, 是的\n我目前的库存正好是一百瓶优质朗姆酒和一百瓶优质葡萄酒。 ";
			link.l1 = "我应该说, 这是一个不错的开始。 一旦我们解决了您的进口困难, 您能每月持续供应这样的数量吗? ";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "当然可以, 船长! 不, 我可以管理三倍, 不-不... 四倍这个数量! 您不会有任何延迟 --我会随时保持充足的储备, 确保任何不幸都能迅速克服, 不影响您的供应。 ";
			link.l1 = "给这批货报价吧。 ";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "我认为合理的价格是: 每十瓶葡萄酒十杜布隆, 每十瓶朗姆酒三杜布隆。 总共, 整批货一百三十杜布隆。 ";
			link.l1 = "很好。 我会和酒馆老板谈谈, 然后马上回来。 ";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "船长, 有什么消息? 您和酒馆老板谈得怎么样? ";
			link.l1 = "我还没和他谈。 那是我接下来要去的地方。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "怎么样, 船长? 您和酒馆老板达成协议了吗? ";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "我做得非常出色, 克里斯蒂安。 他会以二百四十杜布隆的价格购买这批货和未来的所有货物。 第一批货, 我会付您要的一百三十杜布隆, 剩下的作为我的报酬。 不过, 未来的利润将全部归您。 ";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "我做得很好, 克里斯蒂安。 他会以二百杜布隆的价格购买这批货和未来的所有货物。 第一批, 我会付您要求的一百三十杜布隆, 差价作为合理补偿。 所有未来的利润都归您。 ";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "这是惊人的消息, 船长! 我从未敢梦想这样的交易 --谢谢您! 但是... 也许您行动太快了? 总督... 我... 也就是说... ";
			link.l1 = "总督很清楚。 从现在起, 您每月支付一百杜布隆的费用, 并提交适当的贸易报告。 ";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "难以置信! 您是怎么做到的, 船长? 总督是个严厉的人, 是黑市商人的死敌... ";
			link.l1 = "关键就在这里, 克里斯蒂安 --他反对非法贸易, 而不是诚实交易。 他听了我的话, 并为岛上的酒类贸易制定了明确的条件。 您现在将以我的名义经营。 任何不当行为, 我和您一样承担责任。 所以不要让我失望, 否则即使在来世我也会追捕您。 ";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "我发誓, 船长, 您不会后悔的! ";
			link.l1 = "现在我们必须和酒馆老板了结此事, 然后我们将解决我们安排的细节。 ";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "当然, 船长。 您现在准备好取货了吗? 一百三十杜布隆。 ";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "是的, 这是您的杜布隆。 ";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "目前, 我缺乏所需的资金。 请留在这里 --我会带着付款回来。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "船长! 您回来取货了? 价格仍然是一百三十杜布隆。 ";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "确实! 这是您的付款。 ";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "遗憾的是, 我仍然缺乏资金。 我稍后再来。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "非常感谢! 拿去吧! 一百瓶葡萄酒和一百瓶朗姆酒, 如承诺的那样。 ";
			link.l1 = "我的船员会处理货物。 同时, 我必须和酒馆老板说句话。 ";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! 您回来得真快! 告诉我, 我们的安排进展顺利吗? ";
			link.l1 = "一切都很顺利, 克里斯蒂安。 酒馆老板每月需要两次相同的货物。 保持稳定供应他的 establishment, 您很快就会摆脱贫困的想法。 ";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "船长... 您... 仿佛上帝亲自指引您来到我的门槛! 一个真正的奇迹在我面前展开 --我几乎不敢相信我的幸运! 我做了什么值得这样的仁慈? 言语无法表达我的感激之情! ";
			link.l1 = "然而, 我可以告诉您, 克里斯蒂安。 每个月, 您将为我的购买预留一部分最好的商品, 不提供给任何其他买家。 我将按您 stated 的价格购买 --每十瓶葡萄酒十杜布隆, 每十瓶朗姆酒三杜布隆。 ";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "为"+pchar.name+"预留商品将是我最大的荣幸! 我以名誉担保, 您永远不会发现我有任何不足! 您需要多少数量? 五十瓶? 也许一百瓶? 说出任何您想要的数量! ";
			link.l1 = "这些数量超过了我目前的需求。 每种二十瓶就足够了。 如果我的需求增加 --您将立即得到通知。 ";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "当然, 当然! 那就这么定了 --二十瓶葡萄酒和二十瓶朗姆酒, 二十六杜布隆。 每个月的第十五天, 您的商品将等待您的收集。 无论您何时来访, 即使只是寒暄, 我都将欢迎您的尊贵光临! ";
			link.l1 = "太好了! 还有一件事需要强调, 克里斯蒂安。 我已经用我的声誉担保了您的诚信。 不要让我失望, 否则您会发现后果。 ";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "我... 您这是什么意思, 船长... 当然您... 不-不, 我永远不会让您失望! 一切都将以无可挑剔的适当方式进行, 以我的灵魂起誓! ";
			link.l1 = "那么, 直到我们再次相遇! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "你这个爱管闲事的"+GetSexPhrase("杂种","婊子")+"! 难道没人教过你, 干涉与自己无关的事情只会招致不幸吗? ";
			link.l1 = "是你无缘无故袭击我的船, 现在你竟敢指责我干涉? 你完全疯了吗? ";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "让雷劈了我的前桅! 所以你这个"+GetSexPhrase("可怜的家伙","一文不值的婊子")+", 对自己卷入的事情一无所知? 你以为酒馆的供应只是偶然消失的吗? ";
			link.l1 = "你声称是你把那个酿酒厂烧成了灰烬? ";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "哈哈, 真相终于刺穿了你厚厚的头骨, 让链弹撕裂我的内脏吧! 确实是我干的! 那个供应商在贸易中根基太深了。 但如你所见, 我从不失手击败对手。 你也将分享他们的命运, 让葡萄弹把我的帆撕成碎片! ";
			link.l1 = "非常有趣。 那么, 让我们看看你的本事, 让Neptune的野兽吞噬你的尸体吧! 哈哈! ";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "问候, "+pchar.name+"! 什么好风把你吹到我家门口了? ";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // 用葡萄酒和朗姆酒进行贸易
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "日安, 克里斯蒂安。 你把我的货准备好了吗? ";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "日安, 克里斯蒂安。 我只是想确保你的事务进展顺利。 现在不打扰你了。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "当然, 船长! 你能对我的勤奋有丝毫怀疑吗? ";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "一刻也没有, 克里斯蒂安。 这是约定的付款。 我现在要拿走我的烈酒。 ";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "丝毫没有。 唉, 我发现目前我的钱包不太方便。 我有足够的钱时会回来。 ";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "当然, 船长! 你能对我的勤奋有丝毫怀疑吗? ";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "一刻也没有, 克里斯蒂安。 这是约定的杜布隆。 我现在要占有我的烈酒。 ";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "丝毫没有。 唉, 我发现目前没有足够的付款。 我钱包合适时会回来。 ";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // 增加葡萄酒和朗姆酒的供应量
			{
				link.l4 = "克里斯蒂安, 我想增加我的定期订单。 准确地说, 每月各一百瓶朗姆酒和葡萄酒。 ";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // 增加葡萄酒和朗姆酒的供应量, 如果第一次没有带来
			{
				link.l4 = "克里斯蒂安, 我想重新考虑扩大我们的安排。 ";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "太好了。 和以往一样, 新货将在十五号等待您的光临。 期待您的下次来访。 ";
			link.l1 = "您可以指望我回来。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // 定时器
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // 购买计数器
		break;

		case "UpgradeVino":
			dialog.text = "船长, 虽然这样的扩张对生意来说非常受欢迎, 但并非没有相当大的费用! 更大的数量需要额外的劳动力, 扩大仓储, 租用更大的船只... 没有适当的投资, 我永远无法确保如此大量订单的及时交付。 ";
			link.l1 = "这样的安排需要多少资金? 什么投资能保证这个扩大企业的顺利运作? ";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "五万比索就足够了。 任何进一步的费用我将从自己的金库中承担。 ";
			link.l1 = "五万? 我的天哪... 那不是小数目。 你真的不能用更适度的资金来管理吗? ";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "非常遗憾, 船长, 我必须坚持这笔款项是绝对的最低要求。 如果偷工减料, 我们的企业可能会... 可以说, 灾难性地偏离轨道。 这样的灾难对您的利益和我的利益都没有好处, 我敢说。 ";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "这是您的全额付款。 确保您值得这样的信任, 克里斯蒂安。 ";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "进一步考虑后, 克里斯蒂安, 这次扩张可能有些操之过急。 让我们在情况更有利时再谈此事。 ";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "如您所愿, 船长。 如果您的考虑改变, 我随时为您服务。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "船长, 最精彩的消息! 您带来了五万银币来立即进行吗? ";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "这是您的全额付款。 确保您值得这样的信任, 克里斯蒂安。 ";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "目前, 我的金库缺乏必要的资金。 我有资金进行这样的投资时会回来。 ";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "我以名誉担保, "+pchar.name+", 您永远不会后悔这个决定! 我将立即开始准备。 从您下次收集开始, 您可以收到一百瓶最好的朗姆酒和等量的优质葡萄酒, 所有这些只需每批一百三十杜布隆。 ";
			link.l1 = "非常满意。 但记住 --在所有事情上都要极其谨慎。 您的行为直接反映了我在这些水域的声誉。 ";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}