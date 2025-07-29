// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想做什么? 问吧。 ", "我在听你说, 有什么问题? "), "这是你第二次想问... ", "这是你第三次又想问... ",
                          "这要到什么时候才结束? ! 我是个大忙人, 在处理殖民地的事务, 而你还在试图问些什么! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不行。 地点和时间不对。 "), "确实... 但以后吧, 不是现在... ",
                      "我会问的... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> 加斯科涅的负担
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "先生, 我在丛林里发现了一具强盗的尸体。 他被印第安人杀了。 他身上有耳环, 看起来像是从欧洲带到这里的。 也许它们属于你镇上的某个贵族? ";
                link.l1.go = "Sharlie_junglejew";
			}
			//< —加斯科涅的负担 */
			//--> Sinistra, 灭鼠行动
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "大人, 事情已经办妥了! 不过, 我很遗憾地告诉你, 那名罪犯在交战中没有幸存下来, 因此无法面临处决。 ";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "大人, 任务完成了! 囚犯在我的 brig 里等待他的命运。 ";
                link.l1.go = "TK_Plen";
			}
			//< —灭鼠行动
			// Jason 国家海军
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "我是奉总督菲利普.德.庞西的命令来指挥你的武装护卫舰的。 ";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "我准备将这艘护卫舰加入我的中队。 ";
                link.l1.go = "patria_2";
			}
			// Jason 比黄金更珍贵
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "先生, 我应你的邀请而来... ";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "先生, 发生了不幸的事";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> 伟大猎物的捕获
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "大人, 我得到了有关不久将在这些海岸进行非法贸易的情报。 我敢说这件事可能值得你关注。 ";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "大人, 我来打听我们讨论过的那艘走私船的消息。 ";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== 伟大猎物的捕获  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "让我看看你有什么... 难以置信! 太不可思议了, 查尔斯! 这是我妻子的耳环。 我在离开欧洲来到殖民地之前送给她的。 几个月前它们在神秘的情况下消失了。 我就知道它们是被偷的! \n查尔斯, 我很高兴你直接来找我, 没有把我如此珍视的东西卖给商人。 我会报答你的恩情。 我听说你打算买一艘船? 既然你决定从事航海, 你无疑需要我们群岛的地图。 给, 拿着吧。 我相信它会派上用场的! ";
			link.l1 = "谢谢您, 大人! ";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, 灭鼠行动
		case "TK_Potopil":
			dialog.text = "那很不幸, 查尔斯, 但我们必须应对眼前的情况。 这是你的奖励: 五千比索, 税后。 ";
			link.l1 = "我很高兴为圣皮埃尔和您个人服务。 虽然战斗很艰难, 但我从中找到了一些乐趣。 ";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "大人, 这是一场艰苦的战斗。 我的船遭受了重大损坏。 能否补偿我的损失? ";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "好样的, 查尔斯! 我毫不怀疑你会在我们的队伍中步步高升。 ";
			link.l1 = "大人, 后会有期。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "查尔斯, 我得说, 我对你的请求有点惊讶... 好吧, 考虑到我个人再给你两千比索, 作为善意的表示。 再见。 ";
			link.l1 = "谢谢您, 大人。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "太好了, 查尔斯! 你会很高兴地知道, 你的成功将帮助你的马耳他朋友完成一项微妙的行动... 这是你的奖励: 八千比索, 税后。 ";
			link.l1 = "我很高兴为圣皮埃尔。 骑士团和您个人服务。 虽然战斗很有挑战性, 但我从中找到了一些满足感。 ";
			link.l1.go = "TK_Plen_3";
			link.l2 = "大人, 这是一场艰苦的战斗。 我的船遭受了相当大的损坏。 我可以请求补偿我的损失吗? ";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "好样的, 查尔斯! 我相信你会有远大前程。 ";
			link.l1 = "大人, 后会有期";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "我想你已经赢得了它。 作为善意的表示, 再从我个人这里拿两千。 谢谢你, 我的朋友。 ";
			link.l1 = "谢谢您, 大人。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//< —灭鼠行动
		
		// Jason 国家海军
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "船已经准备好了, 但你的中队里没有空位容纳它。 船长, 缩减你的中队然后回来, 我会立即把护卫舰给你。 ";
				link.l1 = "好的。 ";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "是的, 当然, 船已准备好起航。 它的船长知道并会听从你的所有命令。 ";
				link.l1 = "那么我们出发了。 再见, 大人。 ";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "太好了。 准备迎接你的新船。 它的船长知道并会听从你的所有命令。 ";
			link.l1 = "那么我们出发了。 再见, 大人。 ";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // 加入护卫舰
		break;
		
		// Jason 比黄金更珍贵
		case "goldengirl":
			dialog.text = "查尔斯.德.莫尔船长, 终于见到你了! 我一直在急切地等你! 请进, 加入我。 ";
			link.l1 = "大人, 您好。 您如此礼貌总是有原因的。 这次是什么? 海盗。 西班牙人。 红皮肤的食人族? ";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "别这么讽刺, 船长。 我们总是陷入麻烦不是我的错。 但是请不要担心, 这次可能不会有枪战... 大概。 ";
			link.l1 = "你引起了我的兴趣, 继续说。 我能帮上什么忙? ";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "听说过博托夫人的高级场所吗? 在围攻期间, 我们的... 妓院被烧成了灰烬。 有一天, 某位女士自愿重建它。 ";
			link.l1 = "妓院着火了, 却没有我? 顺便说一句, 那天我也被西班牙人开枪打了。 ";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "该死的, 查尔斯, 你今天怎么了? 你的机智不合适! 尽管这不是国家大事, 但对我个人来说仍然是重要的事情! 我需要你的帮助! 看在上帝的份上, 振作起来听我说! ";
			link.l1 = "请原谅我, 大人。 我只是感到如释重负, 仅此而已。 老实说, 我厌倦了所有这些持续的战斗。 我以为你又要把我拖入另一个暴力循环。 请继续。 从未听说过这位博托夫人。 ";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "对, 所以这位可敬的女士将这个场所提升到了一个全新的水平。 现在它是一个上流社会的地方, 不再是以前的鼠洞。 一个有着高贵恶习。 昂贵葡萄酒和无限赌博的地方。 你自己会看到一切的! ";
			link.l1 = "大人, 我不是一个拘谨的人, 你的描述非常生动, 但你为什么要告诉我这些? ";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "因为你在名单上, 不然为什么? 看, 我对侯爵夫人感到内疚, 并答应明天在她的一个聚会上把你介绍给她。 朱莉安娜不常这样做, 所以请务必加入我们。 这次没有战斗。 射击和追逐, 我保证。 一切都将是礼貌和有尊严的: 葡萄酒。 美丽的女人。 纸牌和其他高贵的享受。 ";
			link.l1 = "纸牌和妓女。 在另一种生活中, 这已经有一段时间了。 不过我还是不明白你。 为什么是我? ";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "你聋了吗? 朱莉安娜.博托, 她... 收集杰出和著名的人物。 他们让她的聚会特别和新鲜。 你已经很有名了, 侯爵夫人等了很久才让你成为她的客人。 我的失误给了她一个机会, 如果她拒绝再接待我, 我就得不到这个机会了! 如果我不把你交给她, 这就是我得到的全部! ";
			link.l1 = "大人, 你是一个英俊的鳏夫和总督... 你为什么要关心某个妓女的意见? 应该是她们寻求你的善意, 而不是相反。 ";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "博托侯爵夫人受到亨利.德.列维-万塔杜尔伯爵的保护 - 感谢陛下的恩典, 他是北美新法兰西各州的负责人。 相信我, 查尔斯, 这里没有人想惹他。 ";
			link.l1 = "你差点让我相信了 - 我以为这只是关于欲望和爱情。 现在我看到这一直是政治。 微不足道, 但意料之中。 很好, 我会帮助你。 仅仅一晚回到我年轻的日子会很甜蜜。 ";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "船长, 你无疑是一个经验丰富的人, 但不要试图假装是一个老人。 这不仅仅是政治。 我重视朱莉安娜的存在, 我感谢你的帮助。 这对我个人来说很重要, 真的。 明天黄昏后到博托侯爵夫人的地方来。 我保证政治不会破坏今晚的气氛。 ";
			link.l1 = "葡萄酒。 纸牌。 女人。 就像过去的好时光一样。 再见, 大人! ";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//关闭传送
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请遵守最后期限! ");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // 到明天午夜的计时器
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // 妓院关门的计时器
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // 可能关闭妓院, 仅通过侧门进入
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // 聚会开始的计时器
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "查尔斯, 发生什么事了, 你看起来糟透了! ";
			link.l1 = "大人, 是安格兰那个混蛋, 奇沃斯。 他昨晚偷了我的护卫舰, 把我获奖的船员都杀了, 然后在雾中起航了。 ";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "我知道这是个不愉快的转折, 但相信我 —这样的结果相当令人满意。 你并不急需船只和人手, 而德.列维.万塔杜尔会支付一大笔钱来掩盖最近一场决斗的真相。 或者他会记住我们免费为他隐瞒真相, 这也很有价值。 奇沃斯做了两次不诚实的事, 但他现在已经远走高飞了, 而我们仍然有对付他的好牌。 ";
			link.l1 = "三次, 大人。 安格兰在我们玩牌时承认作弊。 但他不会用钱来收买我, 如果您是这个意思的话。 他越界了。 今天早上那艘船上有个人... 她对我非常重要! 我不会让那个混蛋伤害她! 你听到了吗, 雅克, 我不会! ";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "我想我知道你在说谁 —我记得见过你和某个... 女孩在一起, 她穿着男装, 像海盗一样全副武装。 查尔斯, 别当傻瓜! 你很幸运, 避开了巨大的麻烦, 怎么, 你又想把自己拖进去? 放手吧。 谢天谢地, 奇沃斯在逃跑! 至于你的‘战友女友’ —听你朋友的建议 —去见朱莉安娜, 把这一切都忘了。 ";
			link.l1 = "不可能, 大人。 有些事情你就是无法理解, 好吗? 现在告诉我你知道的关于那个混蛋的一切。 他从圣皮埃尔可能去哪里? 别再试图劝阻我了 —我和荷兰公司。 海盗男爵。 总督, 甚至和宗教裁判所都闹过! 我不是一个容易被吓倒的人。 无论如何我都要把她救回来! ";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "查尔斯, 你有没有想过谁任命总督的问题? 这是一个完全不同的世界! 你几乎没有接触过, 你无法理解, 你就像一个在火药库里的孩子。 而你却要我递给你一根点燃的蜡烛。 至于总督: 德.庞西本人在金钱和政治问题上从不与伯爵作对。 副国王, 这个在平民中如此流行的术语, 非常适合亨利.德.列维.万塔杜尔。 ";
			link.l1 = "而我现在打算剥他唯一的男性继承人的皮, 我知道我在这里冒的风险。 现在, 告诉我: 你知道什么有用的信息可以帮助我吗? ";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "查尔斯, 前几天我会认为你拔枪的举动意味着我们友谊的结束。 但我理解你现在的心情。 这就是为什么我准备忘记这件事。 我知道的对你没用, 护卫舰一大早就向西驶去了。 你应该去拜访侯爵夫人... 等等, 不是那样的! 朱莉安娜对你的敌人了解很多, 而且她个人... 和他的父亲有过一段时间的交往。 问问她。 不像我, 她不会阻止你。 ";
			link.l1 = "这就是计划。 再见, 大人。 感谢你的时间。 ";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// 伟大猎物的捕获, andre39966
		case "VPVL_Magor_1":
			dialog.text = "你是说走私货物? 嗯... 非常有趣。 请告诉我你发现的细节。 ";
			link.l1 = "三天前, 一艘载有违禁品的船本应在勒马林峡抛锚。 这艘船没有按时到达, 但我有充分的理由相信它很快就会进港。 也许你的人可以在这些强盗到达时为他们安排一个适当的欢迎仪式, 大人。 ";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "一艘无名的船载着无名的货物... 你认为我应该根据如此模糊的情报派遣陛下的军队吗? ";
			link.l1 = "大人, 我承认细节很少。 但请允许我讲述一下我是如何得到这个情报的。 (过场动画) ";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "很好, 我们会测试你的情报。 如果一艘载有违禁品的船确实在勒马林海岸抛锚, 你将因对王室的服务而获得丰厚的奖励。 三天后再来见我。 到那时, 不确定性的迷雾将散去。 ";
			link.l1 = "太好了。 那三天后见。 ";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "啊, 船长! 很高兴再次见到你。 你的情报确实非常有价值。 我的人恰好在你指出的地方拦截了那艘船。 给你 —一百五十枚西班牙达布隆, 刚铸造的, 钱包里沉甸甸的。 带着我的感激收下吧。 ";
			link.l1 = "大人, 我谦卑的感谢。 我的一点情报能为王室利益服务, 真是幸运。 如果再有机会, 请知道我的剑和敏锐的眼睛仍然为您所用。 ";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== 伟大猎物的捕获
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了在此处卸载
}