// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前刚问过我这个问题... ", "没错, 让我猜猜... 又在绕圈子了? ",
                          "听着, 我在这里管财务, 不回答问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性哪去了... ",
                      "你猜对了, 抱歉... ", "我明白了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> 加斯科涅人的负担
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "先生, 看看这对耳环。 我在丛林里一个强盗的口袋里找到的, 这显然是一位优秀珠宝匠的作品, 我肯定这不是这片荒野里的东西。 你觉得呢? ";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "我知道你有个叫福尔克.德吕克的债务人。 告诉我, 他的... 拖欠情况有多严重? ";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "我是为福尔克.德吕克的债务来的。 ";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "我完成了你的任务, 先生。 这是你的... 西班牙朋友。 ";
                link.l1.go = "Sharlie_14";
			}
			//< —加斯科涅人的负担 */
			
			//--> 迷你任务"德吕克" (德吕克再次入狱) 
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "我来是为了... ";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "你带了40枚杜布隆吗? ";
				if (PCharDublonsTotal() >= 40)
				{
					link.l1 = "这是给我军官的钱... ";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "没, 我还在考虑。 ";
				link.l2.go = "exit";
			}
			//< —迷你任务"德吕克"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "请问你为什么关心这个? ";
			link.l1 = "我需要这个人自由, 而不是被关在牢里。 据我所知, 在这笔债务还给你之前, 他不会被释放, 我有兴趣偿还这笔债务。 ";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "啊, 这就不一样了。 我也希望我的钱能还回来... 这个福尔克.德吕克是个奇怪的家伙。 他借了一笔相对小额的钱 —五千比索。 他只是不想还, 开始躲藏。 最后, 利息累积到了原始债务的数额, 他发现自己进了监狱。 ";
			link.l1 = "也就是说, 他的债务目前累积到了一万? ";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "确切地说是一万零四百五十比索, 先生。 所以他的自由标价为这个数额。 你愿意付给我吗? 我有点惊讶... ";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "别惊讶。 给你钱。 ";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "嗯... 这确实是一笔巨款。 听着, 先生, 也许你我应该试着做个交易? 例如, 你有一些我能处理的事情, 你可以把我的帮助估值为这一万零五百... ";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason 海盗系列 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "是的, 看来你真的需要这个水手, 如果你愿意为他拿出这么多钱的话。 不管怎样, 这不关我的事, 对吧, 先生? 这是他的债务账单, 现在你有权收回他的债务, 并有权利向他要钱。 当然, 还有请求释放他出狱。 ";
			link.l1 = "这正是我想要的。 再见, " + npchar.name+ "! ";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("你收到了一份债务账单");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason 海盗系列 1
			dialog.text = "帮忙? 唉, 我不需要你帮忙。 至少现在不需要。 ";
			link.l1 = "真遗憾。 那我应该把福尔克的钱带来。 再见! ";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "帮忙? 嗯... 你知道, 先生, 如果你昨天来, 我会给否定的回答, 但现在... 是的, 我有件事需要处理, 但我警告你, 这相当危险。 ";
			link.l1 = "对什么危险? ";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "当然是对你宝贵的生命。 所以在同意之前好好想想, 决定你是否愿意做这样的事情。 ";
			link.l1 = "先生, 危险对我来说并不陌生。 我已经多次处于危险境地。 那么, 让我们谈谈细节。 只要不涉及单枪匹马消灭整个堡垒的驻军, 也许我能完成你如此神秘地暗示的事情。 ";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "好的。 那就听着。 今晚, 几个海盗和一名囚犯将离开勒弗朗索瓦的海盗巢穴, 步行前往勒马林峡。 囚犯是一名西班牙军官, 也是一位伟大的防御工程专家。 英国人打算利用他达到自己的目的, 所以他们会派一艘军舰到海湾接他。 \n这位军官是我的老朋友, 我不想让他成为英国的俘虏。 我不能请求当地当局帮助我, 因为我们正在与西班牙交战。 如果我有更多时间, 我会雇佣能够夺回西班牙人... 抱歉, 夺回我朋友的人, 但唉! \n你是我唯一可以信任这项工作的人。 你必须去勒马林峡... 说服海盗把囚犯交给你。 我怀疑他们不会表现出太多合作, 所以这取决于你。 ";
			link.l1 = "护送队里会有多少海盗? ";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "我不知道。 也许两个人, 也许三四个。 那么, 你怎么说? ";
			link.l1 = "我已经告诉过你‘危险对我来说并不陌生’, 而且我知道从哪一侧握剑。 ";
			link.l1.go = "Sharlie_10";
			link.l2 = "嗯。 你说得对, 这很危险。 我不会独自攻击一群海盗。 ";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "那是你的决定。 如果你认为自己无法胜任这项工作, 那么你最好马上拒绝。 然后我会等待德吕克的债务钱。 ";
			link.l1 = "好吧。 我会把他的钱带来。 回头见! ";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "很好。 很高兴听到这个。 那么你应该去勒马林峡, 海盗们从晚上七点到凌晨四点会在那里。 不要错过他们! 甚至不要考虑使用船! 这样的行为会吓跑他们, 穿过丛林走到那里! \n找到囚犯后把他带给我, 我会把门开着。 我建议等到凌晨一点再返回城市, 因为你需要避开卫兵的注意。 小心点, 祝你好运! ";
			link.l1 = "谢谢你! 我肯定需要一些运气... ";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "等一下! 我看你甚至没有枪。 拿一把我的。 我还有几颗子弹。 我想这会派上用场。 ";
			link.l1 = "是的, 这肯定会派上用场。 谢谢你, 先生。 ";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("你收到了一把战斗手枪");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "现在走吧, 愿上帝帮助你! ";
			link.l1 = "... ";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以加速时间
			// Rebbebion, 新的目的地标记
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, 新的目的地标记
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "太棒了! 我很高兴你能成功处理这件事。 我想我不需要知道行动的细节, 对吧? 那么, 我亲爱的西班牙客人现在可以在我家感到安全了... ";
			link.l1 = "那福尔克.德吕克的债务呢? ";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "当然, 没错。 拿着他的债务账单, 现在你有权追讨他的债务, 也有权利要求他还钱。 当然, 还有请求释放他出狱。 我已经按承诺做了所有事吗? ";
			link.l1 = "是的, 先生。 一切都严格按照协议进行。 现在请允许我告辞。 ";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "那么, 你准备好偿还他的债务了吗? ";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "是的。 给你钱。 ";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "遗憾的是, 我还没凑够所需的金额... ";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "嗯。 看来你是对的, 这是一对昂贵的耳环, 肯定是旧大陆制造的... 我能说什么呢? 我给你三十... 不, 甚至三十五枚黄金杜布隆。 拿着钱吧, 你卖不了更高的价格了。 ";
			link.l1 = "三十五枚杜布隆? 这价格不错。 我同意。 给你。 ";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "不。 我想我会自己留着这对耳环。 ";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("你已交出耳环");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> 迷你任务"德吕克"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "我知道, 我知道, 船长。 你的领航员似乎在几乎每个法属殖民地都欠了债。 说实话, 我早就知道了。 我和同事核实过, 这是标准程序... ";
			link.l1 = "那你之前和我谈条件时, 怎么不觉得这很重要, 应该告诉我? ";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "为什么? 当时我主要关心的是德吕克欠我的债, 顺便说一下, 那是最大的一笔。 你一还清那笔债, 我就立即通知了同事... 我们有庞大的专业信使队伍, 所以很快我的桌上就堆满了德吕克的账单。 ";
			link.l1 = "我明白了... 你知道我对他有切身利益, 也有能力偿还, 就把这些账单买了下来... 这是敲诈, 先生。 ";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "这只是我的工作，船长！到今天为止，您航海士的总债务为40达布隆，而且别忘了，利息也在累积……您会支付吗？";
			link.l1 = "我还没准备好回答, 但我会考虑的。 再见! ";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "太好了! 你知道接下来该怎么做 —和上次一样。 这是文件 —把它们交给监狱长。 和你做生意很愉快, 船长。 ";
			link.l1 = "这种情况没什么愉快的。 再见。 ";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(40);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("你收到了一份债务账单");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//< —迷你任务"德吕克"
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}