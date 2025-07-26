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
			// Addon-2016 Jason FMK-瓜德罗普
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "我是" +GetFullName(pchar)+ "船长。 你的人告诉我你想见我, 我洗耳恭听。 ";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "又是我, " +GetFullName(pchar)+ "先生。 我把贝特朗.皮内特带来了, 他在我的货舱里。 ";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "又是我, " +GetFullName(pchar)+ "先生。 我们谈谈吧。 ";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "又是我, " +GetFullName(pchar)+ "先生。 我们谈谈吧。 ";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "又是我, " +GetFullName(pchar)+ "先生。 我猜你没料到会再见到我。 ";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason FMK-瓜德罗普
		case "FMQG":
			dialog.text = "啊, " +GetFullName(pchar)+ "船长! 很高兴见到你! 我等你很久了... 很好, 我有个问题想问你。 不久前, 一个叫贝特朗.皮内特的人在港口找到你, 想登上你的船。 他看起来很富有, 戴着豪华假发, 有印象吗? ";
			link.l1 = "是的, 有印象。 他确实带着这个目的来找过我。 ";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("你收到了一个沉重的钱袋");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "他想雇佣你和你的船吗? 船长, 如果你能把这件事的所有细节都告诉我, 我会非常感激。 这是值得的, 拿着这个装满硬币的钱袋, 它是你的了, 现在请告诉我关于贝特朗.皮内特的事。 ";
			link.l1 = "好吧。 皮内特先生雇佣我的船, 把他和他的两个朋友从瓜德罗普送到西班牙属美洲, 具体来说是贝洛港的蚊子湾。 我完成了任务, 他们下了船, 径直走进了丛林。 ";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "我明白了。 皮内特先生提到过他的最终目的地吗? 他的同伴呢? ";
			link.l1 = "据他自己说, 他们要去巴拿马。 他的朋友很有趣: 两个军官, 一个西班牙人, 一个法国人。 我还是不明白是什么把他们联系在一起, 但我没拿到问问题的钱。 ";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "一个西班牙军官? 和一个法国军官? 哦! 那可真不简单! 干得好, 皮内特先生! 真是个狡猾的家伙! 甚至在这里也找到了赚钱的方法! 你说巴拿马? ";
			link.l1 = "是的, 我已经告诉你我知道的一切了。 我可以走了吗? ";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "等等, 船长。 我有个商业提议给你。 你介意赚些硬币吗? 不过, 首先, 让我告诉你一些关于你乘客的事。 ";
			link.l1 = "好吧, 说来听听。 ";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "贝特朗.皮内特先生两年前出现在我们的殖民地, 立刻开始和船长们做生意。 这生意也挺黑暗的... 他们给他运送这个地方极度短缺的货物。 贵重物品。 走私品, 有时甚至是奴隶... 他有计划地在我办公室为他的非法活动贷款, 但总是连本带利地偿还。 \n在你帮忙离开这个岛之前, 他贷了一大笔款, 比平时大得多。 他... 曾经是一个值得信赖的客户, 有着无可挑剔的信用记录, 所以我才给他贷款。 这是个大错误。 皮内特先生跑了, 显然他不打算还我的钱了。 ";
			link.l1 = "如果我可以问的话, 这笔钱有多大? ";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "很大。 大约十五万比索的杜布隆。 十箱, 每箱一百五十枚杜布隆。 还不算所有的利息。 ";
			link.l1 = "嗯... 他付了你两年的钱, 让你习惯了, 然后贷了一大笔款, 然后就跑路了。 真聪明。 ";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "正是如此, 船长。 这就是为什么我想雇你做一件事: 找到那个混蛋, 把他带到这里来。 我。 总督和指挥官会想办法让他还清债务。 你见过那个人, 他是你的乘客, 这意味着你比任何人都有更好的机会找到皮内特先生。 当然, 我也会雇一个专业的赏金猎人来追捕他, 但我觉得你的帮助会更有效。 ";
			link.l1 = "报酬呢? ";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "完成这项工作, 我会给你一整箱杜布隆, 一百五十枚硬币。 ";
			link.l1 = "我觉得在西班牙城镇追踪和绑架一个活人, 这个报酬可真够可怜的。 ";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "船长, 我想皮内特先生用我的钱给了你丰厚的报酬, 因为你把我的提议看得这么便宜。 我向你保证, 这值得你付出努力。 当然, 你完全有权拒绝... 但我有件事要告诉你, 肯定会让你改变主意。 ";
			link.l1 = "是什么事? ";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "在皮内特逃离瓜德罗普的前几天, 一名囚犯从巴斯特尔的监狱逃跑了。 他的名字是唐.卡洛斯.德.米利亚尔, 一位西班牙贵族和军官。 他能逃跑多亏了一名法国军官的背叛, 一名海军中尉... 你明白我的意思吗? ";
			link.l1 = "嗯... 这和我有什么关系? 我只是运送乘客, 仅此而已。 ";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "当然, 你只是运送乘客! 就我个人而言, 我毫不怀疑你与组织唐.德.米利亚尔的逃跑无关。 但我们的总督和指挥官可能不这么想。 幸运的话, 你会被指控同谋, 不幸的话... 我真的不想继续说下去了。 你自己看看, 你把一个逃跑的西班牙军官带上了船, 很可能是在某个隐蔽的海湾... 对吗, 船长? ";
			link.l1 = "我明白了。 你在敲诈我。 我来这里是个错误... ";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "你说什么, 船长? ! 我不是在敲诈你! 我只是请求你帮我一个忙, 给你丰厚的报酬。 你能好心找到皮内特先生, 把他送到巴斯特尔吗? 我会等你回来。 我相信两个月足够往返巴拿马了。 ";
			link.l1 = "你让我别无选择。 不过我怀疑这种商业手段对我们成为朋友没有任何好处。 再见, 先生。 ";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//打开城市出口
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - 任务"卑鄙的神鸡"开始
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "好消息, 船长! 我马上派人去你的船上接这个混蛋。 这只小鸟这次不会从我这里飞走了... 你应得的报酬, 拿上这个箱子。 请不要对我生气, 这是给你的护身符, 是礼物。 ";
			link.l1 = "谢谢。 我想你的沉默也是我报酬的一部分吧? ";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("你收到了一箱杜布隆金币");
			Log_Info("你收到了一个'渔夫'护身符");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "沉默? 关于什么? 我很高兴在我的客户中见到你。 你知道人们怎么说沉默和黄金吗? ";
			link.l1 = "有时候它比黄金值钱得多, 先生。 学到了教训。 再见! ";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "我在听。 我猜贝特朗.皮内特在你的船上? ";
			link.l1 = "不在。 不过我有更适合你的东西, 读这个。 ";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "这是什么? ";
			link.l1 = "继续读, 先生。 我们稍后再继续。 ";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(阅读中) 咳咳... 这是什么发热病人的胡言乱语? ";
			link.l1 = "你是认真的吗? 好吧, 我会把这个'胡言乱语'带给总督。 我相信他会对了解'勇气号'及其钻石货物失踪的真相表现出极大的兴趣... 你为什么脸色这么苍白? ";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "这么说, 你终究还是找到了皮内特... ";
			link.l1 = "是的。 所以我给你提个交易。 忘了卡洛斯.德.米利亚尔。 让.德诺和其他先生们, 如果你这么做, 我就忘了这封信。 ";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "很好, 船长... 我同意你的条件。 ";
			link.l1 = "太好了。 我希望你不要生我的气, 我想我们现在两清了。 再见。 ";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//关闭地图
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// 填充箱子
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "哈... 你说得对, 船长。 ";
			link.l1 = "我有东西给你。 拿着看看吧。 ";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "这么说, 你终究还是找到皮内特了... ";
			link.l1 = "没错。 所以我跟你提个条件: 恢复我在法属殖民地的声誉, 我就当没见过这封信。 ";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "可是... ";
			link.l1 = "我他妈不管你怎么去办。 如果明天之前对我的追捕还不停止, 总督就会知道所有事情。 ";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}