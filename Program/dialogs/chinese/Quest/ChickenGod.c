int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "你不应该看到这个。 ";
			link.l1 = "是时候提交错误报告了。 ";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "呃哦! 塔'卡希, 年轻人。 我不想无礼, 但你怎么进来的? 我强烈建议夫人在我逗留期间关闭这家场所。 ";
			link.l1 = "确实呃哦。 他们怎么让你进来的? 为什么这家妓院还没被愤怒的信教者烧掉? ";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "金币打开所有道路, 让白人更快乐。 你不知道吗? ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text + " 我能闻到凡尔赛几乎风化的气味, 你就是在那里被如此尖叫着放进来的。 ";
			}
			link.l1 = "别那样跟我说话, 红脸蛋。 我确实是新来的, 但我不知道你是怎么听说的。 我可以就在你站的地方开枪打死你, 然后找任何一个女孩过夜来弥补不便。 ";
			link.l1.go = "native_var1";
			link.l2 = "我不知道谁告诉你那废话, 但你说话相当流畅, 我承认这一点。 这是我第一次见到如此有教养的本地人。 ";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2 + " 凡尔赛, 去你的! ";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "不, 船长, 你什么都不知道。 我在这里很安全... 目前是这样。 然而, 既然我们这么快就熟悉了, 让我们再试一次。 喝酒吗? ";
			link.l1 = "我可以, 你肯定激起了我的兴趣。 ";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "好极了! 我看我们已经直呼其名并互相嘲讽了。 现在我建议我们为和平干杯并谈谈生意。 ";
			link.l1 = "我可以, 你肯定激起了我的兴趣。 ";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "考虑到这个地方的目的, 你的评论, 船长, 很让我担心! 我已经被困在这里快一个月了。 尝试了所有能想到的事情, 我已经准备好因无聊和无意义而爬墙了。 ";
			link.l1 = "那就离开。 换个地方去教堂... 他们不会让你进去的。 ";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "没那么简单, 因为根据我的... 合同, 我有义务在这家妓院里再待二十四小时。 ";
			link.l1 = "当然听起来很糟糕, 但你不会得到我的同情。 独家妓院租一个月是梦寐以求的! ";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "敬畏你的欲望, 船长。 我不知道你是怎么到这里来的, 因为我本应该独自度过这个月。 独自和女人与酒在一起, 但到第三天左右我只能喝酒了。 今天我也厌倦了。 ";
			link.l1 = "那你想让我做什么? 和你分享一堆女孩和酒? ";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "也许, 但我建议我们先赌博! 每局一千银币! 顺便说一下, 我叫阿圭瓦纳。 ";
			link.l1 = "我的名字是" +GetFullName(pchar)+ "。 当然, 我们玩吧。 ";
			link.l1.go = "native_accept";
			link.l2 = "我的名字是" +GetFullName(pchar)+ "。 一千比索? 不错。 我会考虑一下, 但不保证。 ";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "改变主意了, 船长? 我们玩吗? ";
			link.l1 = "当然, 为什么不呢。 ";
			link.l1.go = "native_accept";
			link.l2 = "还没有。 ";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "谢谢你的游戏, 船长。 我以为这会让我感觉好点, 但没有。 请让我一个人待着 —我会想办法自己再撑一天。 该死的那个混蛋! ";
			link.l1 = "就这样? 诚然, 我的失望大于输掉一大笔钱的痛苦。 ";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "你甚至不应该在这里, 船长。 但如果你渴望知道这一切是关于什么的... 在大陆上寻找一座古老的寺庙。 并带来很多tuunich kaane'。 给, 拿一个。 ";
			link.l1 = "蝰蛇石? 有孔的石头绝对适合这个地方。 谢谢, 阿圭瓦纳";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "再见, 船长。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "呃哦! 谢谢你, 船长! 可惜了钱, 但至少我又尝到了生活的滋味! ";
			link.l1 = "是啊, 这是我第一次看到有人对这样的路线如此兴奋。 顺便问一下, 你从哪里弄来这么多钱? ";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "一个你永远不会问你平等者的粗鲁问题, 船长! 但夜还年轻, 我还剩下很多硬币。 再来一局怎么样? ";
			link.l1 = "为什么不呢? 我们再玩一次! ";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "我建议这次我们玩骰子并提高一点赌注。 我还有一个故事要告诉你, 所以请在楼上为我们俩租一个房间。 这里耳朵太多了! 如果你去找夫人并支付房间费用, 我会很感激。 不幸的是, 我的信用不适用于你。 ";
			link.l1 = "租一个房间? 两个人? 在这里? 去你的, 阿圭瓦纳! 我要离开这里! ";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "哦, 管它呢。 这个故事要么成为一个好轶事, 要么成为一场非常昂贵的血战。 我的剑会跟着我, 所以别耍花招, 哈哈! 在这里等一下, 我会解决的。 ";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "那么? ";
			link.l1 = "我真诚地希望你叫我来这里只是为了喝酒和赌博。 ";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "别担心, 船长, 我对这种废话不感兴趣! 不过, 如果你第一天就出现在这里... 哈哈! 我们开始吧? ";
			link.l1 = "勇者得天助!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "呃哦! 感觉真好! 恭喜你的胜利, 船长。 ";
			link.l1 = "别太过分了。 是时候让我知道这里到底发生了什么了? ";
			link.l1.go = "native_dice_story";
			link.l2 = "你很奇怪, 阿圭瓦纳。 现在, 如果我不立即离开这个地方, 我作为贵族和男人的声誉将受到不可挽回的损害。 把我的银币给我, 我们分道扬镳。 ";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "真可惜, 我本希望以不同的方式结束这一天... ";
			link.l1 = "这是我第一次看到一个男人对赢得这场平民游戏如此沮丧。 你至少现在能让我知道这里到底发生了什么吗? ! ";
			link.l1.go = "native_dice_story";
			link.l2 = "去你的, 阿圭瓦纳! 我受够了这个! ";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "尽我所能, 船长。 我不确定我是否被允许, 但尽管如此, 你照亮了我最后的几天... 我是说在这家妓院里。 ";
			link.l1 = "那这是关于什么的? ";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "没关系... 听着, 白人! 我是泰诺人的伟大酋长, 阿圭瓦纳。 有时我梦想自己早出生一百年, 把西班牙侵略者赶出我的岛屿! 但相反, 我以每人十个金币的价格把三千部落成员卖给了矿山。 ";
			link.l1 = "值得称道的传记。 我突然有冲动要开枪打死你, 阿圭瓦纳, 让你在这个散发着酸酒气味的垃圾场里腐烂。 ";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "不管怎样, 船长。 我所想要的只是像你一样。 ";
			link.l1 = "像我一样? ";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "我见过你的船 —人类天才的奇迹 —我自己也想要一艘。 我见过你穿着紧身胸衣的女人, 梦想着自己脱掉一件。 我甚至看到你最糟糕的指挥官行使着我们任何领导人都无法想象的权力。 听说过欧洲和人们居住的巨大石头房子, 而不是生存。 我已经拥有了一切! 此外, 在过去的一年里, 我甚至去过欧洲和所有那些地方! ";
			link.l1 = "你喝了太多酒, 酋长。 你去欧洲的唯一门票将是锁链, 让梵蒂冈和街头艺人高兴。 你所说的在我们生活的世界里根本不可能。 ";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "那就是我们生活的世界, 船长。 已经有人向我解释过, 我们的世界是错误的, 虚构的, 任何事情都是可能的。 ";
			link.l1 = "是谁那个自作聪明的人告诉你的? 显然他们不仅让你进妓院, 还让你进精神病院! ";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "现在我们要讲我故事的重点了。 你知道这里的情况, 不是吗? 西班牙人和英国人用枪支。 工具和火药支付我们的战俘。 我用你的钱支付了我的部落成员。 你认为为什么会这样? ";
			link.l1 = "我觉得你要告诉我了。 ";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "只有神才能实现我们最深和最羞耻的欲望。 如果你不能过你想要的生活, 那就请求他们干预命运。 只有他们能实现我们最深和最羞耻的欲望。 这就是方式。 但这里有个麻烦: 我们几乎所有的神都已经死了, 即使没有, 他们也从不关心黄金。 幸运的是, 自然厌恶真空, 一个新的神出现在一座古老的金字塔里。 他不在乎你是谁: 本地人或欧洲人, 恶棍或英雄 —只要付钱, 你就会得到你所要求的! 所有部落都知道这一点, 你们中的一些人也是如此。 我已经用黄金付出了代价, 像你一样生活。 明天就一年了。 ";
			link.l1 = "什么神? 一年内往返欧洲? 你旅行的高潮是加勒比海的某个糟糕妓院? 哦, 管它呢。 听起来像醉汉的故事, 我会把它当作这样的故事来接受。 我们喝一杯, 继续你的故事吧。 ";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "我告诉你的一切都是真的。 没有更多可讲的了。 ";
			link.l1 = "你在我们的世界生活的时间还不够长, 阿圭瓦纳。 每一个受酒启发的寓言, 尤其是在妓院里醉酒讲述的寓言, 都必须以道德结尾。 在适当地结束我们的沙龙之前, 我们肯定应该进行哲学思考。 ";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "它们通常如何结束? ";
			link.l1 = "你不知道吗? 当然取决于参与者的性别! 和男人打架, 和女人上床。 不过有时时尚会反过来。 那么你的寓言的道德是什么? 金钱买不到幸福? 无聊! ";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "那不是我所说的寓言的道德, 正如你所说。 但既然你开始了, 我觉得有必要说我不同意你的观点。 相反, 我相信金钱能买到幸福并使人变得更好。 ";
			link.l1 = "胡说! 你似乎现在自相矛盾。 你通过贩卖自己的人民积累了大量财富。 你还记得你从中获利的总金额吗? 将近三万金币? 花点时间反思一下, 但我很清楚, 金钱并没有为你买到幸福。 不过它确实为你买了这套漂亮的套房。 ";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "好吧, 我会调整我的初始观点: 金钱使生活和人变得更好。 ";
			link.l1 = "那更好, 但你为什么认为它使人变得更好? 那么你现在是美德的典范了? 那些没有多少钱的人呢? 我们要把他们贴上坏人的标签吗? ";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "你知道, 船长, 我真的很欣赏这次谈话。 让我再调整一下: 金钱使生活和人变得更好, 但只对那些已经拥有一丝美德的人而言。 ";
			link.l1 = "听着, 听着! 那么, 你没有火花, 是吗? ";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "没有。 我曾是我人民的酋长, 与金钱不同, 权力肯定会腐蚀人。 你知道吗, 船长? 我现在看着你, 意识到有一天你会面临同样的困境。 ";
			link.l1 = "你的神也给了你预知的天赋吗? 所以你应该去圣地亚哥, 我听说他们对各种媒介和算命先生特别感兴趣。 ";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "让我们完成我们的... 嗯, 沙龙, 不要打架和上床。 我未能为我的故事编造一个道德, 所以我想改为提议干杯。 ";
			link.l1 = "你完全迷路了, 酋长。 但有一件事, 你是对的。 我们喝酒吧! ";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "敬我们想要的总是与我们需要的一致。 谢谢你, 船长, 这是... 我们晚上的合适结局。 如果你有一天想测试我寓言的真实性, 去大陆寻找一座古老的寺庙。 给你带来一百一十三块tuunich kaane'。 我还剩九十九块 —拿去吧, 再见! ";
			link.l1 = "一堆有孔的石头? 完全适合这个地方。 谢谢你的夜晚, 阿圭瓦纳。 再见? ";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "不, 你不会。 再见, 船长。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "我明白, 船长。 无论好坏, 我会给你一个关于宝藏的提示。 毕竟你照亮了我最后的几天... 我是说在这家妓院里。 在大地上寻找一座古老的寺庙, 并带一堆tuunich kaane'到那里。 给, 拿一个。 ";
			link.l1 = "蝰蛇石? 多么迷人, 有孔的石头绝对适合这个地方。 我受够了你的对待! ";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "我知道你很沮丧, 船长。 无论好坏, 我会给你一个关于宝藏的提示。 毕竟你照亮了我最后的几天... 我是说在这家妓院里。 在大地上寻找一座古老的寺庙, 并带一堆tuunich kaane'到那里。 给, 拿一个。 ";
			link.l1 = "蝰蛇石? 多么迷人, 有孔的石头绝对适合这个地方。 我受够了你的对待! ";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "再见, 船长。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "又一个? 哦, 该死的! 我受够你们所有人了! ";
			link.l1 = "啊-啊! 滚开! ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "嗯? 是的, 对。 向我鞠躬, 凡人! behold 我的金字塔的力量! ";
			link.l1 = "(绝望地尖叫)";
			link.l1.go = "joruba_2";
			link.l2 = "(杀死怪物)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "没错。 欢迎来到我简陋的工厂, 船长。 ";
			link.l1 = "你是什... 什么? ";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "我赞赏你的坚持。 你的下一步是什么, 船长? 你觉得做些交易怎么样? ";
			link.l1 = "你是什... 什么? ";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "我是什么不重要, 我执行的功能才重要。 在这个时候, 我正在与这个贫民窟的居民进行交易, 以实现互利。 ";
			link.l1 = "贫民窟? 你是指这座寺庙? ";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "这是你的第一个也是最后一个警告, 船长! 然而这座金字塔确实有点狭窄, 显然我已经超过了它的容量。 ";
			link.l1 = "你说过一些关于交易的事情。 你说的是哪种交易? ";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "我给予人们最需要的东西。 ";
			link.l1 = "你 granting 愿望? 像童话里的精灵一样? 天啊, 这里发生了什么? ! ";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "别荒谬了! 我只帮助人们以最快和最愉快的方式得到他们来到这个世界上想要的东西。 ";
			link.l1 = "你是萨满还是什么? ";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "好吧, 你确实遇到了阿圭瓦纳, 这应该给你一些想法。 ";
			link.l1 = "那个可怜的。 迷路的。 醉酒的印第安人是你的杰作? ";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "不是我以几千英镑的黄金卖掉了他的部落, 不是我把几桶酒灌进他的喉咙, 我当然也没有强迫他从数百个妓女那里染上每一种已知和未知的疾病。 他要求我把他变成一个白人贵族, 所以我照做了。 正如他的命运所吩咐我的。 ";
			link.l1 = "你会实现愿望吗? 像童话里的精灵一样? 天啊, 这里发生了什么? ! ";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "别荒谬了! 我只帮助人们以最快和最愉快的方式得到他们来到这个世界上想要的东西。 阿圭瓦纳本应将他的人民从欧洲侵略者的枷锁中拯救出来, 但相反, 他过多地垂涎指挥官女儿的紧身胸衣, 并决定典当自己的... 从那时起, 他生命中剩下的唯一意义就是意识到自己错误的深度并尽快重新开始。 在欧洲的一年, 肝硬化和你们俩在妓院度过的时光一定有所帮助。 但我承认, 他度过了一个很棒的假期, 哈哈! ";
			link.l1 = "肝硬化什么? 你是萨满还是什么? ";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "或其他什么。 不过你会喜欢我的提议的。 而且, 换一种方式, 我会真诚地乐意帮助。 ";
			link.l1 = "对。 多少钱? ";
			link.l1.go = "joruba_9A";
			link.l2 = "为什么? 我很特别吗? ";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "不错, 船长。 要么你聪明, 要么你蠢得像头驴, 但你的机会刚刚增加了一点。 价格不是问题。 ";
			link.l1 = "你需要杀人吗? 我不做那个。 ";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "因为你这辈子的目的就是在我的一个好朋友身上打洞, 哈哈! ";
			link.l1 = "你需要杀人吗? 我不做那个。 ";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "首先, 你做。 其次, 我们将进行四次重大交易, 还有四次较小的交易。 每一次都会让你变得更强大, 并增加你在这个残酷而奇怪的世界中的机会。 如果你完成每一笔交易, 我保证有一天你将能够出去与神平等地战斗, 更不用说普通人了。 ";
			link.l1 = "听起来很有趣。 告诉我吧。 ";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "明智的选择! 通常我的演讲会导致人们因疑似心脏病发作而被送往布鲁维尔德, 但你表现得很好。 这是任务清单: 我希望你做的一些易货性质的小差事。 没有截止日期, 呵呵。 ";
			link.l1 = "好奇。 我稍后再看清单。 还有别的吗? ";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "是的, 第一笔重大交易。 两千金币是价格。 ";
			link.l1 = "也许我会接受... 但那是很多钱! 你为什么需要那么多? 我可以用比索支付吗? ";
			link.l1.go = "joruba_13";
			link.l2 = "你疯了吗? 我可以用那笔钱买一艘护卫舰! ";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "金字塔需要维修 —砖石有时会落在顾客的头上, 这对生意不好。 我的人每天都在修补, 但我们的组织需要从外部紧急注入资金来彻底解决问题。 至于比索 —我不太喜欢它们, 因为它们的汇率相当不稳定。 ";
			link.l1 = "你对诚实的比索太不公平了... 等一下, 你不是一个人在这里? ";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "不, 我是一个严肃组织的门面。 那么, 你加入吗? ";
			link.l1 = "我会考虑的, 但首先, 我想知道花这么一大笔钱能得到什么。 ";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "为什么要破坏惊喜? 此外, 就把那笔钱当作税款吧。 你最有价值的收获将是解锁下一笔交易。 奖励将是神圣的。 也请注意, 你在其他任何地方都找不到它们! ";
			link.l1 = "好吧。 你叫什么名字来着? ";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "非凡的阿鲁巴。 最后一件事, " +pchar.name+ ", 每天只允许进入金字塔一次。 不要耽误其他客户, 也不要无缘无故地打扰我。 ";
			link.l1 = "我没看到排队的人... 再见, 陛下。 ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "啊哈, 船长。 你给我带来了什么? ";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "这是你的金币。 携带那该死的金属已经够难了... 但放弃它更难! ";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "我遵守了我的约定。 这是你的药草, 阿鲁巴。 ";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "阿鲁巴, 啊哈! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + "'" + chref.Ship.Name + "'是你的了! ";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "阿鲁巴, 啊哈! 粉色'" + chref.Ship.Name + "'是你的了! ";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "阿鲁巴, 啊哈! 大帆船'" + chref.Ship.Name + "'是你的了! ";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "我愿意做出牺牲。 ";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "我给你带来了一位新娘和与西班牙当局的麻烦, 先生。 这位女士正在外面散步, 由我的人很好地保护着。 在你让我相信你的意图高尚之前, 我不会把她交给你。 ";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "这是你的盔甲, 阿鲁巴。 确保我的奖励能弥补它。 ";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "我有你要的囚犯。 ";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "我给你带来了你的垃圾。 这里, 一百一十三块石头, 正如你所要求的。 ";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "我愿意做出牺牲。 ";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(重新分配角色属性点)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "我只是路过。 ";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "那就下次吧。 ";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "不错, 我会好好利用那些黄金。 给你, 一个非常有德行的泰诺酋长以前拥有的小饰品。 有助于携带成堆的黄金。 当然帮助过他, 嘿嘿... ";
			link.l1 = "谢谢你, 希望我不会后悔。 下一笔交易是什么? ";
			link.l1.go = "joruba_p1_1";
			link.l2 = "等一下。 我给了你一堆黄金, 却得到了一块粘土? 好吧, 我需要退款! ";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("你收到了泰诺小雕像");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "嗯? 是的, 下一笔交易。 这些黄金现在应该足够了, 所以是时候考虑更多精神商品了。 得给自己找个解药。 ";
			link.l1 = "为什么, 你病了吗? ";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "我的灵魂是。 看, 自从与宗教裁判所的那件事以来, 牧师们都避开我简陋的金字塔, 所以我们不得不依靠更传统的方法。 我需要, 嗯, 我的工厂需要十五株马加罗萨植物来保持运转。 ";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "那是一种药草吗? ";
			} else {
				link.l1 = "我知道那是什么, 嘿嘿。 ";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "我说实话 —这是一种价值很高的稀有药草。 如果你真的打算花几年时间在群岛上收集它, 仔细考虑一下? ";
			link.l1 = "不保证, 但祝你健康, 希望我为药草得到的奖励物有所值。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "好了, 我正式宣布这是我的休息日! 这样的交易值得一个真正的宝藏。 behold! \n这把弯刀曾经差点砍碎那个笨蛋卡内克的头! 因此, 它对我来说非常珍贵, 我谦卑地请求你好好照顾它。 它很旧, 但工艺非常精良, 现在再也没有这样的钢铁了。 ";
			link.l1 = "卡内克? 那是谁? ";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("你收到了征服者弯刀");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "哦, 你们会见面的。 现在, 我希望你不是那些鄙视体力劳动的自大混蛋之一? 如果是这样, 你就倒霉了, 因为奖励的第二部分是双装药弹药的图纸。 ";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "哦, 我喜欢那些。 但它们有什么独特之处? 双火药装药不是新闻, 因此我得出结论, 你显然从那把博物馆弯刀时代起就没有离开过你的金字塔。 ";
			} else {
				link.l1 = "就这样? 嘿... ";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "别自作聪明, 听着! 任何白痴都可以在桶里放两堆火药, 冒着失明。 面部烧伤或鼻梁骨折的风险。 我给你一个小魔术: 仔细检查火药的质量, 将其研磨到合适的稠度, 放入子弹或铅弹, 并用切碎的金币调味。 爆炸声甚至会撕裂胸甲! ";
			link.l1 = "射击金钱, 嗯? 很像你。 ";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "你真让人难以忍受! 好吧, 拿一把手抛式迫击炮, 还有一些手榴弹。 如果你真的那么聪明, 你很快就会自己获得手榴弹图纸! ";
			link.l1 = "非常感谢, 大人。 接下来是什么? ";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("你收到了手 mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "你不会喜欢的。 我需要一艘船... 不, 我需要那艘船。 你知道, 有她背后的故事。 ";
			link.l1 = "为什么? 你甚至不是船长。 ";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "这不关你的事! 最好关注你的奖励, 因为我可以要求为此从顶部到底部清洁这座金字塔, 而你仍然欠我! ";
			link.l1 = "你肯定不是船长, 否则你会知道船需要码头或海湾才能停靠。 你到底期望我如何把船弄进你的金字塔? ! ";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "你有没有注意到我的金字塔后面有一个巨大的湖? 那就对了。 只要在附近的中队中用合适的船停靠, 我的人就会做剩下的事情。 现在离开这里, 你挡住了队伍。 ";
			link.l1 = "当然。 再见! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "不错! 得到它了! ";
			link.l1 = "放下你的自作聪明, 给我我的奖励! ";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "其他两艘呢? 不能为自己保留吗? 嘿嘿。 ";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "其他两艘呢? 不能为自己保留吗? 嘿嘿。 ";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "其他两艘呢? 不能为自己保留吗? 嘿嘿。 ";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "该死, 我很惊讶你不想自己保留她。 这才叫有故事的船! 该死的, 威廉... 我真希望你能回家, 像你一直梦想的那样找到一家大银行。 ";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "你看看这个! 你是对你的 commission 的耻辱, " + sTemp + "! ";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "查理.普林斯决定在我的旧金字塔里销毁罪证? 我赞成! ";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "祝你好运向你的上级解释旗舰的损失,  舰队司令。 哦, 请原谅, 总督大人。 ";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "你是一个迷信的傻瓜还是只是一个傻瓜? 她价值连城! 我不确定这是否是公平交易, 但不管怎样。 ";
				break;
				
				case SHIP_FDM:
					dialog.text = "你是一个迷信的傻瓜还是只是一个傻瓜? 她价值连城! 我不确定这是否是公平交易, 但不管怎样。 ";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "你是一个迷信的傻瓜还是只是一个傻瓜? 她价值连城! 我不确定这是否是公平交易, 但不管怎样。 ";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "好选择! 你知道, 我喜欢卡斯蒂利亚人。 也许我完成后会把她还给他们。 ";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "真的, 你缺乏同情心, 船长。 这艘船散发着背叛的气味。 我会接受她。 ";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "是的, 这艘船可能有历史... 但获得它是不是太容易了? 啊, 好吧。 你很特别, 亲爱的, 所以我会接受它。 至少让我回想起我年轻时的一些回忆。 ";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "是的, 这艘船可能有历史... 但获得它是不是太容易了? 哦, 管它呢。 好吧, 船长, 我会让这件事过去, 因为你在我清单上的那些任务中做得很好。 我会接受它。 至少让我回想起我年轻时的一些回忆。 ";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "你见过牧师吗? 好吧, 你会见到他的。 你最好储备双发手枪子弹。 如果那不起作用 —试试木桩。 ";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "你见过牧师吗? 好吧, 你会见到他的。 你最好储备双发手枪子弹。 如果那不起作用 —试试木桩。 ";
				break;
				
				case SHIP_MEMENTO:
					dialog.text = "你见过那个神父了吗? 好吧, 你会见到他的。 最好多备些双弹筒手枪的子弹。 如果那不管用—试试木桩。 ";
				break;
			}
		break;
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "是的, 这艘船可能有历史... 但获得它是不是太容易了? 没门! 你还有一堆未完成的工作。 一旦你完成了, 我们会再次讨论这个牺牲。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "我保佑你, " +GetFullName(pchar)+ "。 愿大海对你有利。 现在, 让我们讨论下一笔交易... ";
			link.l1 = "等等, 什么? 在我们这个理性时代, 甚至乡巴佬傻瓜都不会相信这种废话! 我没有在你的慈善箱里放一分钱, 我给了你一艘完整的战舰! ";
			link.l1.go = "joruba_insult";
			link.l2 = "等一下。 你的祝福对我到底意味着什么? ";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "你指挥的任何船现在都将被祝福有更强的船体, 而你的敌人将遭受相反的待遇。 此外, 你在海上的时间将过得更慢。 如果这还不足以让你将这个整个烂地方置于死地, 你最好去找你爸爸要求退款! ";
			link.l1 = "如果它不起作用, 我发誓今晚就回来烧掉你的金字塔! 告诉我下一笔交易! ";
			link.l1.go = "joruba_p3_3";
			notification("+10%船体防御", "None");
			notification("+10%对敌方船只船体伤害", "None");
			notification("+5%全局地图速度", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "培养兴趣了, 嗯船长? 不幸的是你, 我也是。 你认为我为什么选择这座金字塔作为我的办公室? ";
			link.l1 = "可能是因为女巫清洗仍然存在? ";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "嘿嘿, 不, 不完全是。 我在这里做生意是因为最好的交易需要鲜血。 这座金字塔需要鲜血。 我需要鲜血。 一直如此, 将来也会如此。 ";
			link.l1 = "甚至别想, 你这个怪物。 我不会把受害者交给你去杀! ";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "你杀了多少人, 嗯? 等等, 我甚至会告诉你确切的数字: 你个人杀死了" + (Statistic_AddValue(pchar, "Solder_s", 0) + Statistic_AddValue(pchar, "Citizen_s", 0) + Statistic_AddValue(pchar, "Warrior_s", 0) + Statistic_AddValue(pchar, "Solder_g", 0) + Statistic_AddValue(pchar, "Citizen_g", 0) + Statistic_AddValue(pchar, "Warrior_g", 0)) + "人! 你把堆积如山的尸体放在你野心和财富欲望的祭坛上! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text + "你兄弟的债务已经杀死了比一场普通欧洲战争更多的人! ";
			}
			dialog.text = dialog.text + "甚至不要在这里开始对我进行道德说教, 尤其是因为我不打算评判你。 一些人的成功总是要以另一些人的悲剧为代价, 而神, 哦, 神, 他们会看着并收取他们的份额! ";
			link.l1 = "我现在无法给你答案... 我需要离开这里。 ";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "急需清醒头脑? 好吧, 但首先, 听我说。 如果你给我带来一个有价值的人, 我会给你力量和对身体和思想的完全控制。 不是一个额外的人, 不是一个来自街头的无脸灰老鼠或来自恶臭舱底的老鼠。 给我带来一个跟随你并在你的悲喜剧中扮演重要角色的人。 ";
			link.l1 = "我的一个军官? 你不能再低级了, 阿鲁巴! 如果这件事传出去... ";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "我会像往常一样处理保密问题。 在你再次开始抱怨之前, 我会让你知道还有另一种方式。 ";
			link.l1 = "那是什么意思? 所以我不必把自己的人拖到祭坛上? ";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "不, 但你不会喜欢替代方案。 如果你不想用鲜血支付, 你可以用黄金支付。 三千金币和一颗清白的良心。 金钱可以做到这一点, 甚至更多 —我爱它! ";
			link.l1 = "再见, 阿鲁巴。 我不想再和你说话了。 ";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "你知道在哪里可以找到我。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "让我们在西班牙宗教裁判所出现之前快点做。 要血还是金? ";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "那就金吧。 这是你的三千金币, 尽管我无法想象你如何在这片荒野中花费如此巨额的款项。 ";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "血。 ";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "没关系。 ";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "... ";
			link.l1 = "你完成了吗? 让我们谈谈我的奖励。 ";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "就这样吧。 说名字。 ";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "克劳德.杜兰德不是军官, 而是一个无情的雇佣兵, 所以选择另一个牺牲品。 ";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "我接受你的贡品。 你不必观看。 ";
			link.l1 = "不, 我不看。 一小时后我会回来取我的奖励。 ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "明智的选择。 我讨厌清理祭坛上的所有血迹, 所以黄金更可取。 给, 喝这个药水 —来自我一个好朋友的赠礼。 ";
			link.l1 = "味道还不错... ";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S。 点数", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "你完成了吗? 我们谈谈我的奖励。 ";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "随时找我改变你的命运。 ";
			link.l1 = "但这对我到底意味着什么? ";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "掌控自我! 偶尔尝试一下, 你会喜欢的。 同时, 让我告诉你下一笔交易。 最重要的那个。 ";
			link.l1 = "我不确定这是否值得了! ";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "来吧, 赶紧说。 ";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "你有机会不仅改变命运, 还能站在我们这个时代的天才和神灵身边。 是的, 你现在可以随心所欲地改变你的身体和思想, 但你永远无法超越自己的局限, 因为普通人不可能擅长所有事情。 我的建议是你打破这些界限。 ";
			link.l1 = "这要花我多少钱? 更多的血? 黄金? ";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "是的。 要么给我两万五千金币, 要么给我一个你的同伴。 一旦我们完成, 就不再有交易了。 ";
			link.l1 = "我会考虑的。 ";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "你知道在哪里可以找到我。 如果你想改变命运, 随时来拜访我。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "如你所愿。 ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "首先, 那是我的妻子, 不是新娘。 其次, 是你和卡斯蒂利亚人有问题, 不是我。 最后, 我已经带走了她并解散了你的人。 至于高尚的意图... 看看我, 我难道不是一个正派绅士的典范吗? Tlazolteotl, 保佑他有一天也能认识一个真正的女人。 或者男人。 ";
			link.l1 = "去你的, 阿鲁巴! ";
			link.l1.go = "exit";
			
			notification("+ 10 生命值, + 10 能量!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "不错, 谢谢。 坦率地说, 我并不是真的需要它, 但也许我会在某个沙龙或别的什么场合穿上它。 以伊什塔尔的名义, 我保佑你。 现在去犯罪吧。 ";
			link.l1 = "多么奇怪的感觉... ";
			link.l1.go = "exit";
			
			notification("+ 15 生命值, + 15 能量!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "我会带走他们。 什么? 我和你一样需要船员中的死人, 只是不像你, 我不能去酒馆招募。 现在, 巴斯特, 保佑英雄未来的努力。 ";
			link.l1 = "多么奇怪的感觉... ";
			link.l1.go = "exit";
			
			notification("+ 15 生命值, + 15 能量!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "是的, 我们得把它们撒回去, 因为人们总是丢失它们, 我们需要顾客。 弗雷亚, 保护这位伟大的石头收藏家。 ";
			link.l1 = "多么奇怪的感觉... ";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 生命值, + 15 能量!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "在西班牙宗教裁判所出现之前, 我们快点做。 要血还是金? ";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "给你黄金, 你这个贪婪的混蛋。 ";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "血。 ";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "没关系。 ";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "说名字。 ";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "未来的妻子";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "现任妻子";
				}
				
				dialog.text = "这很诱人, 但我只破例一次 —我不会接受你的牺牲。 我不会向你的" + sTemp + "透露这一点, 尽管我可能应该。 记住, 没有她你什么都不是。 现在, 滚开, 今天别烦我。 ";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "克劳德.杜兰德不是军官, 而是一个无情的雇佣兵, 所以选择另一个牺牲品。 ";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "就这样吧。 给, 喝这个药水 —来自我一个好朋友的赠礼。 ";
			link.l1 = "味道还不错... ";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S。 点数", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "下次见, 船长。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "啊哈! 终于, 一切都结束了! ";
			link.l1 = "嗯? ";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "我们在这里结束了, 船长。 交易已经达成, 每个人都很满意, 没有退款的余地。 我们的办公室正在关闭并搬迁。 ";
			link.l1 = "等一下, 阿鲁巴。 我给了你很多黄金, 用鲜血支付, 把女人和囚犯带到这个邪恶的巢穴。 我能处理加勒比海发生的超自然事件。 但我们与你的‘交易’违背所有逻辑。 请解释一下。 ";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "你知道吗? 我会告诉你。 \n我受够了这个世界, 我想离开。 每天都是老一套: 一座天花板摇摇欲坠的古老金字塔, 那些令人讨厌的相同棕榈树, 还有源源不断的船长, 每个都有自己的‘巧妙’想法。 是的, 我为人们提供他们想要的东西; 这是我的使命, 我为此感到自豪。 但是天啊, 我多么讨厌你们所有人! ";
			link.l1 = "有人把你留在这里吗? 出口就在那里, 天才! ";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "你说得对, 没有人把我留在这里。 不再是了。 这都要感谢你, 我的朋友。 ";
			link.l1 = "这是突然的转变。 我期待一个故事, 但到目前为止, 我只听到了一个在尘土飞扬的金字塔里卑鄙的小神的无意义咆哮。 ";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "嗯, 每个人都需要时不时发泄一下, 不是吗? 我真的很高兴你来到这里, 因为多亏了你, 我终于可以离开这个世界了。 黄金。 船员。 设备和一艘船, 我的朋友。 记得吗? 听起来熟悉吗? 这就是我所需要的一切, 而你提供了所有这些。 ";
			link.l1 = "不客气。 然而, 这仍然没有解释你独特的说话方式和近乎神圣的力量。 如果你真的那么强大, 你早就可以自己变出船。 船员和黄金了! ";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "正如你所见, 我做到了。 每个人都有自己的方法。 ";
			link.l1 = "但到底是怎么做到的? 你究竟是谁? ";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "嗯... 我就是这么做的, 简单地说。 在新世界见, " + GetPersonaName() + "。 希望下次是真的新世界。 谢谢你, 再见。 ";
			link.l1 = "不, 我不想再见到你。 ";
			link.l1.go = "exit";
			link.l2 = "那么回头见, 阿鲁巴... 这很有趣。 ";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "看来所有交易都取消了。 该走了, 船长。 ";
			link.l1 = "你该去... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "以西班牙宗教裁判所的名义, 报上你的名字! ";
			link.l1 = "船长" +GetFullName(pchar)+ "。 他们说的是真的, 没人预料到西班牙宗教裁判所... ";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... 这个笑话总是切中要害, 尽管它导致不少无辜的基督徒被送上火刑柱。 ";
			link.l1 = "... ";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "只是开玩笑, 船长。 你在开玩笑, 我也在开玩笑。 我叫埃米利奥.博卡内格拉神父, 这些基督的士兵是我的武装护卫。 ";
			link.l1 = "我能为你做什么, 神父? ";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "你认识某个叫阿鲁巴先生的人吗? ";
			link.l1 = "是的, 他直到最近还住在这座古老的金字塔里。 ";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "你说他住在那里是什么意思? 有可能住在那里吗? 为什么是‘直到最近’? ";
			link.l1 = "这位先生几分钟前刚乘船离开我们。 ";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "你怎么知道的? 最近的海湾也有好几天的路程! ";
			link.l1 = "这个湖一定比看起来大。 我没有其他解释给你, 神父。 ";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "在总督辖区的土地上正在发生奇怪的事情。 ";
			link.l1 = "这些是英国的土地, 神父。 ";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "让异端分子继续这样想吧。 我们肯定会把它夺回来的。 原谅我, 我的孩子, 问了这么多问题: 圣地亚哥指示我对这座金字塔... 及其前居住者进行正式调查。 ";
			link.l1 = "到底发生了什么事, 神父? ";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "既然这个案子可能会结案, 我可以给你讲个小故事。 \n关于这个地方的谣言已经在大陆上流传了一段时间。 我们收到可靠报告, 过去有一些在该地区历史上留下重要印记的人定期访问这里。 \n然而, 在巴拿马事件之后, 圣地亚哥开始真正关注这些谣言。 \n某个印第安人在那座辉煌的城市引起了巨大轰动, 甚至发表了几次相当哲学性的布道。 不幸的是, 巴拿马的居民得出了相当肤浅的结论, 说服自己这座金字塔包含无尽的宝藏并能实现任何愿望。 \n当然, 这是最纯粹的异端邪说... 所以我们不得不对一些巴拿马居民和这个叫阿圭瓦纳的印第安人提起诉讼。 ";
			link.l1 = "为什么巴拿马当局没有镇压这个? ";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "正如他们在这些情况下总是做的那样, 他们声称自己被施了魔法。 如果我们能审问阿圭瓦纳, 这个法律漏洞本可以被堵住, 但他突然死了。 ";
			link.l1 = "他怎么死的? ";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "酗酒害死了他。 然而, 他的死并没有解决我们的问题, 因为异端邪说已经在整个群岛扎根, 数百人前往这座古老的寺庙进行某种朝圣。 ";
			link.l1 = "我以前从未在这里见过人群... 那么, 你打算入侵阿鲁巴并审判他吗? ";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "当然不是, 我的孩子。 宗教裁判所的判决是严厉但公正的。 审判必须有充分的理由。 不, 我只是打算收集阿鲁巴先生的证词并将其送达圣地亚哥。 ";
			link.l1 = "嗯, 这对你来说很不幸。 ";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "你永远不知道, 我的孩子。 这是上帝的旨意。 ";
			link.l1 = "再见, 神父。 ";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // 决斗用双发手枪 cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// 三管霰弹枪, 双装药
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// 短号, 双装药
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// 混合枪, 双装药
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// 豪达枪, 双装药
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// 火绳枪, 弹药
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// 塔 musketoon, 弹药
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}