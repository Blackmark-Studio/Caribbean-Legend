// 国家任务相关的NPC对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "你在找什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		// 检查员诺埃尔.弗尔热
		case "noel":
			dialog.text = "很高兴见到你, 船长! ";
			link.l1 = "我也很高兴见到你, 弗尔热先生。 在这片荒野中遇到来自大都市的客人可是难得的机会... ";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "我很高兴这次航行能搭乘你的船, 船长。 德.潘西骑士给我讲了很多关于你的有趣故事。 我相信晚餐后在餐厅我们会有很多话题可聊, 再来杯葡萄酒就更好了。 ";
			link.l1 = "我完全赞成舒适的交谈, 尤其是吃饱的时候。 我很乐意做你的同伴, 男爵。 ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "太好了。 当我们到达殖民地时, 我请你带我去见总督, 我会亲自向他解释需要做什么。 你只需等我处理完事务, 成交? ";
			link.l1 = "好的, 弗尔热先生。 欢迎登船! ";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "船长, 托尔图加是个小殖民地。 我估计在这个岛上完成所有检查需要大约三天时间。 ";
			link.l1 = "明白了, 男爵。 那么三天后我来这里接你。 祝你好运! ";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "我在托尔图加的工作完成了, 该起锚了。 ";
			link.l1 = "明白了, 男爵。 我们马上出发。 ";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "是是, 我们肯定会在卡普斯特维尔汇报此事。 如此重要的殖民地被征服的威胁... 不可思议, 我会亲自确保德.潘西骑士采取严厉无情的措施! 船长, 我将在这个岛上停留一周, 这里有很多种植园, 需要一些时间。 ";
			link.l1 = "知道了, 男爵。 七天后我会在总督府等你。 玩得开心, 别太劳累! ";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "你来了, 船长。 我在伊斯帕尼奥拉岛的工作完成了, 该起锚了。 ";
			link.l1 = "明白了, 男爵。 我们马上出发。 ";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "船长, 这个岛我好像熟悉。 这不是圣克里斯托弗吗? ";
			link.l1 = "是的, 男爵, 正是。 我们快到了。 ";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "快到了? ! 我们不是还该去圣马丁吗? 它也属于法国殖民地。 ";
			link.l1 = "你是说圣马丁? 那是荷兰殖民地, 弗尔热先生。 ";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "是吗? 在巴黎它被认为是法国的。 怎么回事? ";
			link.l1 = "不知道, 男爵。 自从我第一次踏上群岛, 圣马丁就是荷兰殖民地。 也许我有所不知, 你应该考虑和德.潘西骑士谈谈这事。 ";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "好吧, 船长, 就这样。 反正我们快到卡普斯特维尔了。 ";
			link.l1 = "... ";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", 船长。 很高兴见到你。 听说你升职了, 请接受我的祝贺! 说实话, 你确实是德.潘西麾下最明智且有才华的军官之一。 ";
			link.l1 = "谢谢你, 先生。 ";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "终于, 只剩最后一个殖民地了, 圣马丁。 说实话, 我已经厌倦了这些旅行。 很高兴完成这次检查, 可以开始安排下一次法属西印度贸易行动了。 我们准备好起锚了吗? ";
			link.l1 = "是的, 男爵。 请登船。 ";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "船长, 你能告诉我刚才发生了什么吗? 这意味着战争吗? 为什么我们差点被荷兰人击沉? ";
			link.l1 = "男爵, 我自己也不明白! 这肯定是某种误会, 毫无疑问。 ";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "船长, 我敢打赌这个‘误会’有名字! 彼得.斯特伊弗桑特, 所谓圣马丁的‘租借者’, 也是我们亲爱的德.潘西骑士的合伙人! ";
			link.l1 = "我不知道, 男爵。 我们最好赶紧去卡普斯特维尔向总督汇报此事。 ";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "毫无疑问, 我们就该这么做! 我会要求解释! 我就知道把岛租给荷兰人是个大错误! 船长, 我们尽快离开这里, 趁有人决定追我们之前! ";
			link.l1 = "正是如此, 先生... ";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "先生, 首先请允许我祝贺你的晋升! 我热切支持德.潘西大人任命你为副舰队司令的决定。 你当之无愧! 现在, 我最近从圣马丁回来。 在菲利普斯堡的仓库里, 我们进行了清点, 所有荷兰货物都被没收, 现在属于法国国库。 作为战斗行动的指挥官, 你被授予一份战利品。 我同意骑士的看法, 这是公平的。 你的货物已转移到圣克里斯托弗商店的仓库, 你随时可以去取。 ";
			link.l1 = "谢谢你, 男爵。 让货物先放在那里吧。 我从库拉索回来后会去取。 ";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "祝你下一次战役好运, 副舰队司令! 我相信你会带着胜利归来, 并公正地惩罚这个恶棍斯特伊弗桑特。 ";
			link.l1 = "... ";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "这不是谁来了! 查尔斯.德.莫尔副舰队司令! 很高兴见到你! 你在太子港有什么事? ";
			link.l1 = "我也很高兴见到你, 男爵。 我来这里是出于职责, 我得去拜访杰里米.德尚.迪穆萨卡先生... ";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "这次相遇真是太幸运了, 因为我等了很久想亲自见你。 我想和你谈谈, 但不是在这里。 ";
			link.l1 = "那我们去酒馆吧, 好吗? ";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "这里没有多余的耳朵, 我们可以安全地交谈... ";
			link.l1 = "我洗耳恭听, 男爵。 ";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "副舰队司令, 你似乎是个重荣誉的人。 这样的英勇海军军官就该如此... ";
			link.l1 = "嗯... 我想我不太明白你的意思, 先生... ";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "德.莫尔先生, 我想问你: 你如何看待你的君主, 菲利普.德.潘西总督? ";
			link.l1 = "军官的职责不是评判指挥官, 而是服从命令。 ";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "哦, 得了吧, 副舰队司令, 我们不在军营, 也不在德.潘西的大厅。 我这么说吧: 你不觉得德.潘西先生... 滥用权力吗? 我仍然无法忘记我们在圣马丁的堡垒炮火下差点沉没的情景。 我确信荷兰人的背叛是有原因的。 ";
			link.l1 = "他们想征服那个岛。 ";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "是的, 是的, 但为什么恰好在我决定检查它的时候? 为什么不是一个月前? 或者两个月后? 我不相信这是巧合, 先生。 你没有怀疑吗? 我们俩在那里都命悬一线。 ";
			link.l1 = "我每天都在冒生命危险, 弗尔热先生。 我想你明白... ";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "你的勇气毋庸置疑。 但这不是我想说的。 你看... 当我在你解放的圣马丁工作时, 我多次听到当地人小声谈论岛深处的某个矿场。 我试图询问人们, 但他们只是装傻。 他们很害怕... 很明显, 我看起来不太值得信任, 但这只会加强我的怀疑: 这个神秘的矿场会不会是这一切的原因, 德.莫尔先生? 战争都是为了黄金, 对吗? ";
			link.l1 = "群岛上有很多矿场。 大多数都已枯竭, 变得毫无价值。 我知道一个主要的运营金矿, 属于南美洲的西班牙人。 但我从未听说过圣马丁有金矿。 ";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "你很擅长辞令, 副舰队司令! 我明白: 你不信任我。 我是新来的... 德.莫尔先生, 但我在巴黎是有影响力的人。 财政部长是我的密友。 我经常觐见国王。 我的权威比菲利普.德.潘西大得多, 当然, 正式来说, 因为这里总督是最高长官。 但说实话, 在殖民地, 弱肉强食是唯一的规则。 ";
			link.l1 = "在这一点上我完全同意你。 ";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "但在巴黎不是。 在那里, 最有影响力的人是国王和财政部长... 我的密友。 德.莫尔先生, 你是个杰出的军事家, 但我认为菲利普.德.潘西在利用你达到个人目的。 你很聪明, 肯定有所怀疑。 你可以信任我。 我保证你完全匿名, 并得到巴黎当局的支持。 我以我的头衔发誓。 ";
			link.l1 = "***对潘西保持忠诚***";
			link.l1.go = "noel_39"; // 分支
			link.l2 = "***站在弗尔热男爵一边***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "我理解你, 弗尔热先生。 对于不熟悉当地思维方式的人来说, 德.潘西的行为确实可能显得奇怪。 当我第一次来到群岛时, 这里发生的事情让我震惊。 我还记得我听到的第一句话: ‘如果你遇到没有防护的西班牙船, 可以尝试登船。 ’背叛。 阴谋。 欺骗 --这里步步皆是。 海盗。 掠夺。 抢劫... ";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "我们在欧洲与西班牙和平相处。 但在这里我们是死敌。 荷兰人今天看起来友好无害, 明天公司官员就会没收你的货物, 只因为他们突然宣布禁止进口, 而你根本不可能知道。 英国军官公开当海盗, 击沉公司的船只, 而公司雇佣一个伪装成幽灵船的恶棍, 恐吓英国商人... ";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "在这个狼窝里, 我们有时不得不做出一些对不熟悉这一切的人来说不太明显的奇怪决定。 而你觉得可疑的事情, 实际上是唯一正确的行动。 同时处理多件事并设法向母国输送利润是很困难的。 德.潘西骑士完美地应对了这一点, 他是一位经验丰富的管理者和有远见的政治家。 当然, 他可能会犯错, 但我们在人生中都有犯错的时候... ";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "而你需要考虑到所有人和事。 考虑到认为整个新世界都属于他们的西班牙人的野心, 考虑到荷兰商人的贪婪, 考虑到英国人的冷酷谨慎和无情残忍。 甚至还要考虑海盗。 ";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "考虑海盗? ! ";
			link.l1 = "是的, 你没听错。 荷兰人和英国人在与海盗积极合作... 当然是非官方的。 海岸兄弟会是一支可以挑战该地区任何国家的重要力量, 他们与遇到的每个人都在不断冲突, 没有人能阻止他们。 唯一让他们危险性稍低的是他们分散且各自为战。 你知道吗, 托尔图加的前总督莱瓦瑟实际上完全依靠海盗建立了国中之国? ";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "我好像听说过... ";
			link.l1 = "几艘保护该岛的强大私掠船经常停靠在托尔图加港。 莱瓦瑟背叛了法国, 成为了某种地方权威。 现在, 在海盗巢穴和他们的主人一起被摧毁后, 海盗们对法国人非常愤怒... ";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "真的吗! ";
			link.l1 = "是的。 我们不得不这么做, 否则托尔图加就会离我们而去, 尽管我们得到的结果并不理想。 现在没有法国商船在加勒比海能感到安全。 西班牙人也没有与海盗首领达成协议, 至少他们有强大的西班牙大帆船舰队和能击退海盗的强大军舰。 就像荷兰人有他们的东印度船和泽贝克船。 但我们却不能以此自夸, 唉。 而且法国海盗经常抢劫法国商人。 ";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "这太疯狂了! 没有办法结束这一切吗? ";
			link.l1 = "很多人尝试过。 最后, 他们没有战斗, 而是用黄金收买他们的忠诚。 我是说颁发私掠许可证。 ";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "嗯... ";
			link.l1 = "所以根据经验, 在群岛上成立法国贸易公司将是一个非常糟糕的主意。 你现在明白你将面临什么困难了吗? 有多少混蛋想在这里分一杯羹? 而且他们不会轻易放手。 还有海盗, 他们能做出不可思议的事情, 你可以说他们疯狂, 但他们几乎总能达到肮脏的目的? 为了保护商船, 你必须维持一支庞大的海军舰队, 但从财务角度看这会盈利吗? ";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "但法国商人在这里还是设法生存了下来? ";
			link.l1 = "没错, 就是设法生存。 尤其是现在, 莱瓦瑟在托尔图加的海盗堡垒被攻占后... ";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "你的话与德.潘西说的一致。 ";
			link.l1 = "这是事实。 群岛上的情况就是这样, 一直如此。 ";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "你说得如此热切。 甚至很多事情我都不知道, 而且你说得对: 我仍然不知道。 我想我对潘西的怀疑是没有根据的。 你让我开了眼界。 谢谢你, 副舰队司令。 但法国部长指望公司的成立。 国王需要钱... ";
			link.l1 = "我明白。 但请考虑我刚才说的话, 如果法属西印度公司的成立不可避免, 那么请确保我们有一支强大的海军舰队来保护它。 ";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "你的宽宏大量真是令人钦佩, 副舰队司令! 如此高尚的品格! 难怪你在这里待了这么久, 不急于回家。 但我们会再见面的: 我半年后会回到这里。 法国贸易公司将崛起。 至于海盗, 我觉得你有点夸大其词了。 总之, 我们有军舰和勇敢的船长, 比如你。 ";
			link.l1 = "抱歉, 男爵, 但我只是一个人, 除了我, 法国在群岛上只有一艘强大的船‘埃克利亚顿’, 这不够, 我们的损失会超过收益... 唉, 不管怎样, 事情就是这样, 我想我们同时会想办法的... 你什么时候去法国? ";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "两周后我会回到圣克里斯托弗, 从那里回家。 德.潘西先生给了我一艘好船 --一艘名为‘法沃里’的双桅船和一位出色的船长。 这艘船很快, 船长也很有经验, 但当然, 和你在一起我更安全。 我记得我们在群岛的旅行, 副舰队司令, 那真是一段美妙的经历。 ";
			link.l1 = "谢谢你的美言, 男爵。 好吧, 我想我们该分手了... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "这里的人互相利用。 早在我成为海军军官之前, 骑士就利用我为他做事。 ";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "这可以接受吗? 你怎么看? ";
			link.l1 = "不。 但骑士让我别无选择: 要么服从他的命令, 要么我弟弟就会在牢里待到死, 我家族的好名声也会被毁。 ";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "太可怕了! 这简直是恐怖主义! 他有什么理由发出这样的威胁? ";
			link.l1 = "我弟弟不幸成为了他的亲信。 就像我现在一样。 ";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "你弟弟现在在哪里? ";
			link.l1 = "我设法救了他, 但第二天就失去了他的消息, 他选择不再为任何人服务。 ";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "我就知道潘西不是他所说的那样! 披着羊皮的狼! 副舰队司令, 你可以信任我。 我是个重荣誉的人。 如果我们能找到潘西犯罪活动的切实证据, 我会把你从这个‘赞助人’的枷锁中解救出来。 你知道斯特伊弗桑特这个乏味的故事吗? 公开说吧, 别担心, 你只是个军人, 必须执行命令。 ";
			link.l1 = "我知道。 圣马丁确实有个矿场。 但他们在那里开采的不是黄金, 而是盐。 这在西班牙人中需求量很大。 潘西不能直接与西班牙人交易, 所以斯特伊弗桑特充当了中间人。 ";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "所以潘西和斯特伊弗桑特是商业伙伴? ";
			link.l1 = "曾经是。 在你表示想检查圣马丁后, 斯特伊弗桑特决定把潘西踢出局, 自己独占盐矿的所有利润。 潘西不能告诉任何人... 但正如我们所见, 斯特伊弗桑特算错了。 ";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "你认为矿场还在运营吗? ";
			link.l1 = "我确定。 似乎潘西现在有了新的贸易盟友。 不是别人, 正是多伊利上校本人。 ";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "我们能向部里提供证据吗? ";
			link.l1 = "嗯。 在攻占矿场时, 顺便说一下, 是西班牙人而不是荷兰人攻占的, 我们俘虏了矿主。 他还在我的船上。 你可以和他谈谈。 有可能他为了自由会说出很多有趣的事情。 ";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "我们马上到你的船上去。 命令把你的俘虏送到你的船舱。 我会和他谈谈。 ";
			link.l1 = "好的, 走吧。 ";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "太好了, 副舰队司令。 我会和他谈谈。 请留在这里。 ";
			link.l1 = "当然... ";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "我记录下了你俘虏的所有证据, 他也签了字。 现在我们必须兑现对他的承诺, 一有机会就在卡塔赫纳让他下船。 但你自己也听到了一切\n现在看看我们的潘西是个多么卑鄙的人! 把岛租给荷兰人, 在那里进行非法活动, 还允许西班牙人去那里管理矿场! 我都不敢想象因为他的自私, 国王的国库损失了多少钱! ";
			link.l1 = "这些证据足以指控潘西吗? ";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "不幸的是, 恐怕不够。 证据很重要, 但还不够。 但出于我们都明白的原因, 我不想让你卷入其中。 ";
			link.l1 = "那个西班牙人同意在你的委员会到达时作证。 ";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "这至少要六个月后才会发生, 谁知道那个西班牙人会怎样, 我们以后还能不能在卡塔赫纳找到他... 我们需要更有价值的证据。 即: 证明矿场仍在秘密运营, 并继续填满我们亲爱的总督的口袋。 ";
			link.l1 = "所以你建议我们去圣马丁? ";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "是的。 你知道怎么去矿场吗? ";
			link.l1 = "我知道。 ";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "那么, 晚上我们悄悄潜入那里, 不让任何人看到, 看看那里发生了什么。 ";
			link.l1 = "非常好。 ";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "但骑士呢, 嗯? 现在我明白为什么他如此大胆地暗示我在群岛上成立法国贸易公司将无利可图... 当然, 这对他来说将非常无利可图! ";
			link.l1 = "既然我们现在是盟友, 男爵, 我就告诉你全部真相, 潘西让我... 说服你不要在这里成立贸易公司。 ";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "原来是这样! 我希望至少他没让你用剑或手枪除掉我? ";
			link.l1 = "没有。 他让我用其他方式说服你。 ";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "潘西会为此付出代价, 但现在我们需要立即起航去圣马丁。 之后再把西班牙人送到大陆。 我们走, 副舰队司令! ";
			link.l1 = "你乘我的船离开这个岛, 似乎有点奇怪, 你不觉得吗? ";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "不觉得。 你不是应该说服我吗? 你确实做到了, 哈哈! 是的, 在起航去欧洲之前, 我会告诉骑士我同意他的观点, 贸易公司不会成立。 让他暂时活在谎言的幸福中... 我们走! ";
			link.l1 = "... ";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "带路吧, 副舰队司令。 黑夜会用它的帷幕掩护我们。 ";
			link.l1 = "跟我来... ";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(低声说) 我看到了! 我看到了! 你看到了吗? 红衣兵! 那些是英国士兵! ";
			link.l1 = "我告诉过你 - 潘西现在和多伊利上校有生意往来。 ";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "你说得对。 我看得够多了。 现在趁没被发现, 我们尽快离开这里! ";
			link.l1 = "同意... ";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "你看到我们亲爱的骑士的‘商业项目’导致了什么! 英国人在法国岛上表现得像主人! 这太离谱了! ";
			link.l1 = "我们得走了, 否则肯定会有人来这里。 我们不能被认出来。 ";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "副舰队司令, 在我们前往圣马丁的途中, 我一直在思考, 我决定了一件事: 你能安排我和彼得.斯特伊弗桑特见一面吗? ";
			link.l1 = "和斯特伊弗桑特? 但为什么? ";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "前商业伙伴可能有一些重要线索, 以及一些证明骑士参与其中的重要证据。 我相信斯特伊弗桑特对潘西不太满意, 会寻求报复, 尤其是在最近这些事件之后... ";
			link.l1 = "我相信是这样, 男爵。 我个人不敢去斯特伊弗桑特的宫殿。 在我对他们做了这一切之后, 这对我来说太冒险了... ";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "我已经想过了。 我们去库拉索, 在远离城市的海湾下船, 派我们从矿场俘虏的西班牙人带着信给斯特伊弗桑特。 我不会在信中提到你, 而是告诉他我在领导一项针对潘西的调查之类的。 我想那个荷兰人会来赴约。 ";
			link.l1 = "嗯。 我认为这不是个好主意。 斯特伊弗桑特不是傻瓜, 他会能拿多少拿多少, 甚至可能试图监禁你并索要巨额赎金, 但如果我们让他相信这一切都是因为潘西, 他可能会站在我们这边。 好吧, 如果你这么坚决, 我们试试。 ";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "德.莫尔先生, 请原谅我的愚蠢。 你对斯特伊弗桑特的看法是对的。 我早该猜到只有更大的恶棍才能挑战德.潘西! ";
			link.l1 = "哈! 一百万... 潘西要一百万, 斯特伊弗桑特也要一百万... 看来我们在兜圈子... ";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "你在说什么, 副舰队司令? ";
			link.l1 = "我到达加勒比时, 潘西要我支付一百万作为我弟弟的赎金。 ";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "你真的付了那么多? ";
			link.l1 = "我挣到了并付了。 当然不是一个月内。 说实话, 那时我只是个新手。 但骑士还是没放米歇尔走。 ";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "然后你就入伍为潘西效力了? 我真不明白你。 ";
			link.l1 = "我入伍是为了服务法国和我所爱的人, 除了国王, 我不向任何人低头。 ";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "对不起, 德.莫尔先生。 当然, 你为法国和国王服务! 潘西会为一切付出代价! 包括他给你带来的所有痛苦。 ";
			link.l1 = "很好, 男爵, 我会凑出一百万。 请登船... 我会解决这个问题。 ";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请在截止日期前完成! ");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // 一个月的计时器
		break;
		
		case "noel_90":
			dialog.text = "你想见我, 副舰队司令? ";
			link.l1 = "是的。 我和斯特伊弗桑特见了面。 这是他的账本。 ";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "我不敢相信! 嗯, 让我看看... (阅读中)";
			link.l1 = "... ";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "就是这个! 我们亲爱的骑士完蛋了。 一旦财政部部长看到所有这些账目... 我都无法想象他会怎么样。 我们甚至不用再找卡塔赫纳的那个西班牙人了。 德.莫尔先生, 你真的为这本书付了一百万? ";
			link.l1 = "是的。 如果我尝试其他方法, 法国可能会因为内战而失去加勒比的殖民地, 我可能会赢, 但如果我和自己人战斗, 我算什么舰队司令? ";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "你真是名不虚传。 我向你发誓, 副舰队司令, 你会收回这笔钱。 我相信我们会在潘西的箱子和他的放债人那里找到一大笔钱。 我只请你等六个月, 直到我带着委员会从欧洲回来。 ";
			link.l1 = "别忘了带一营训练有素。 装备精良的士兵。 还有像‘埃克利亚顿’这样的船。 我也相信‘埃克利亚顿’的船长到时候会站在我们这边。 ";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "别怀疑, 他也是个重荣誉的人。 我意识到道德价值观在你做决定时起着重要作用。 你做得很好, 信任我并揭露了这个国家罪犯。 现在带我去卡普斯特维尔, 我会向潘西报告你任务的成功 - 你设法说服了我, 我将放弃成立贸易公司的想法。 也许潘西甚至会为此奖励你 - 问心无愧地接受奖励, 什么都不用担心, 你最该得到它。 你不会被卷入其中, 你的名字也不会被你上级的恶行玷污, 事实上, 我见到国王时会把你夸上天。 弗尔热男爵是个重荣誉。 守诺言的人。 ";
			link.l1 = "我很高兴, 男爵。 我们出发吧! ";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//打开地图
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "那么, 副舰队司令, 我们终于到了。 你的任务结束了, 现在轮到我了。 去处理你自己的事务吧, 像以前一样捍卫法国的利益。 大约六个月后, 这个卑鄙的故事就会结束。 需要你时我会派信使找你。 再见, 德.莫尔先生, 我很幸运在这里遇到一个重荣誉的人! 部长和国王会听到你的事迹, 我保证。 他们会听到所有好话。 ";
			link.l1 = "谢谢你, 男爵。 一路顺风! ";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // 计时器
		break;
		
		case "noel_98":
			dialog.text = "很高兴见到你, 副舰队司令。 我按约定又来了。 和我一起的是财政部长的第一助理, 奥利维耶.布尔丹男爵。 ";
			link.l1 = "德.潘西骑士在哪里? ";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "他该在的地方, 监狱里。 他被捕了, 将被带到法国接受调查和审判。 鉴于他的职位, 他肯定会避免死刑, 但无法逃避巨额罚款。 降级, 可能还有监禁。 ";
			link.l1 = "逮捕顺利吗? ";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "不太顺利。 骑士在这里, 在官邸里, 有一整队忠诚的士兵护卫。 但我们提前做好了应对这种情况的准备。 ";
			link.l1 = "那么, 我祝贺你, 男爵! 也许现在你会处理法国贸易公司的事? ";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "我? 是的。 布尔丹先生将和德.潘西骑士一起回法国。 而你, 副舰队司令, 也该期待一些变化了。 现在你有了新职位。 布尔丹先生会告诉你更多。 ";
			link.l1 = "... ";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "德.莫尔先生! 等一下! ";
			link.l1 = "是的, 男爵。 我在听。 ";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "至于你付给斯特伊弗桑特的那一百万... 我没有告诉部里, 以便... 避免诸如法国军官如何拥有这么多钱的问题。 这可能会对你有害, 因为他们可能会要求你用自己的钱充实国王的国库。 ";
			link.l1 = "我明白, 谢谢你。 ";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "在卡普斯特维尔从潘西那里找到的所有钱都被布尔丹男爵没收了。 但事实证明, 潘西还有一笔由英国放债人藏匿的 stash。 我会和他谈谈归还投资的事, 然后想办法补偿你。 ";
			link.l1 = "恐怕你要从英国放债人手里拿到东西不容易。 ";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "我同意。 但我们会努力的, 我会让你知道结果。 ";
			link.l1 = "如你所愿。 ";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "副舰队司令, 你看起来不太好, 还是我看错了? 你刚刚在殖民地获得了最高职位! ";
			link.l1 = "不, 不是... 只是一切发生得太突然, 我有点不知所措。 ";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "别担心。 你会习惯新职位的。 此外, 你担任圣马丁总督半年非常成功, 所以这对你来说不算新鲜。 ";
			link.l1 = "哦, 我相信我会习惯的。 我在加勒比期间遇到过更糟糕的情况。 我想我也能应付这个。 ";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "好吧, 好的。 此外, 我还有一个惊喜给你。 我相信你会喜欢的。 但首先请你回官邸。 我想有人在那里等我们。 ";
			link.l1 = "你引起了我的好奇心, 弗尔热先生。 好吧, 我们回去。 ";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "没关系, 侯爵。 真正的船长应该总是先照顾好自己的船, 对吧? 查尔斯, 你还记得战列舰‘埃克利亚顿’的船长于贝尔.达西埃侯爵吗? ";
			link.l1 = "当然记得! 如果不是他, 我今天就不会活着。 海军军官之间最牢固的友谊来自并肩作战的战斗。 而达西埃先生原来是一位经验极其丰富的船长。 ";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "副舰队司令, 我荣幸地通知你以下事项。 除了任命你为群岛法属殖民地的代理总督外, 我还提出了你的旗舰问题。 ";
			link.l1 = "旗舰? ";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "正是。 据我所知, 你进入法国服务时, 得到了轻型护卫舰‘Gryffondor’供你使用。 这无疑是艘很棒的船, 但它只适合军官, 不适合副舰队司令和现在的总督。 你是法国在这里的代表。 你的旗舰应该与之匹配。 所以我们决定将在加勒比经历首次战斗的船加入你的中队... ";
			link.l1 = "弗尔热先生, 你是想说... ";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "从现在起, 法国海军的骄傲, 66门炮的战舰‘埃克利亚顿’归你指挥! 这个决定得到了国王的批准! ";
			link.l1 = "但男爵, 我不能就这样拿... ";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "你可以的, 查尔斯。 这不容讨论。 在法国, ‘埃克利亚顿’专门为你进行了一些升级, 因为事实证明, 加勒比海没有像欧洲那样的大海战, 因此对单个船只的要求更高。 在这里, 一切都由船只的性能和船长的经验决定。 ‘埃克利亚顿’加强了船体, 增加了载重和船员规模, 稍微改装了帆具使其能更急转弯, 还将所有加农炮完全更换为42磅口径, 这是我们拥有的最强加农炮。 ";
			link.l1 = "是的, 现在这艘船简直是海上霸主... 但弗尔热先生, 因为这艘船的船长是于贝尔.达西埃侯爵。 我不能从他那里拿走... ";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "只是我还没告诉你, 侯爵本人强烈希望在你的指挥下服役... 达西埃先生? ";
			link.l1 = "... ";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "是的, 达西埃先生, 我想我们不会再耽误你了。 ";
			link.l1 = "... ";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "私下说, 查尔斯, 我强烈建议你让侯爵继续为你效力。 我向你保证, 你找不到这么有经验的船长了。 ";
			link.l1 = "相信我, 男爵, 在与西班牙和荷兰的战斗中, 我有幸亲眼见识过。 达西埃先生确实是一位出色的战斗军官, 也是我的朋友。 ";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "那么, 现在请允许我告辞了, 总督大人! 事务不等人: 贸易公司的组建工作已经开始了第一天。 很快再见! ";
			link.l1 = "祝你好运, 弗尔热先生。 也祝你在贸易事业中顺风顺水! ";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// 在欧洲升级后设置"埃克利亚顿"号
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//打开跳转
			bQuestDisableMapEnter = false;//打开地图进入
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// 允许"比黄金更珍贵"任务
			pchar.questTemp.Patria = "end"; // 主线结束
			pchar.questTemp.Patria.GenGovernor = "true"; // 查尔斯成为总督
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <—— 传奇版本
		
		case "noel_final":
			dialog.text = "请允许我向你表达最诚挚的感谢, 副舰队司令! 你把我从那些该死的海盗手中救了出来, 救了我的命。 我感谢你, 也感谢菲利普.德.潘西。 我必须承认, 我对他的评价完全错误, 请原谅我的误解。 你和骑士是对的: 法国贸易公司在这里会有很多麻烦, 看来我们只会在这里赔钱\n只有像潘西这样有经验的人, 和像你这样勇敢的士兵, 才能抵御每个岛上的这些豺狼。 我需要去宫殿, 之后会尽快离开欧洲, 忘记这场噩梦。 ";
			link.l1 = "很高兴一切顺利结束, 男爵。 再见! ";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // 计时器
		break;
		
		// "埃克利亚顿"号船长
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", 先生。 什么风把你吹到‘埃克利亚顿’号的甲板上了? ";
			link.l1 = TimeGreeting()+", 先生。 请允许我自我介绍 --查尔斯.德.莫尔船长, 我来自群岛法属殖民地总督, 德.潘西骑士。 我奉命将你的船编入我的中队并由我指挥。 这是命令书... ";
			// 传奇版本修复检查带步枪的制服
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "这好像是个误会, 先生。 你现在站在法国海军的一艘主力舰上, 我只听从皇家海军人员发出的命令。 而你似乎没有任何属于那支舰队的标志。 也许你把我们的船认错了。 ";
			link.l1 = "但是... ";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "哈, 我穿着这身制服都没认出你, 船长。 那么, 让我看看你的信, 我想看看内容。 ";
				link.l1 = "给你。 ";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "我们已经讨论过了, 先生... ";
				link.l1 = "嗯... ";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "好吧, 让我看看... (阅读中) 有意思。 那么, 我和我的船要归你指挥了, 德.莫尔船长? ";
			link.l1 = "这是总督的命令。 ";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "是是, 命令不容置疑。 很好。 请允许我自我介绍: 我是于贝尔.达西埃侯爵, 法国海军66门炮主力舰‘埃克利亚顿’号的船长, 带领这支训练有素的船员, 我以荣誉发誓, 这是法国拥有过的最好的船只之一。 ";
			link.l1 = "很高兴听到这个, 因为总督分配给我们的任务需要良好的航海和加农炮知识。 ";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "你能告诉我即将进行的行动细节吗? ";
			link.l1 = "当然。 我们将前往西班牙的特立尼达岛, 从这里向东南航行大约一周的路程。 我们将突然袭击守卫圣何塞殖民地的堡垒, 把它夷为平地。 然后, 我们会和西班牙人谈谈他们最近袭击法国圣皮埃尔定居点的补偿问题。 ";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "我明白了。 我们什么时候出发? ";
			link.l1 = "尽快。 我们必须在一个月内完成这项任务, 所以我们有足够的时间。 ";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "好的, 德.莫尔船长。 我们将听从你的命令出发。 ";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "你有什么命令或问题吗, 德.莫尔船长? ";
			link.l1 = "还没有... ";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "但是, 德.莫尔船长, 首先你得缩小你的中队规模 --我的船不能加入, 否则中队就太大了。 ";
			link.l1 = "哈。 你说得对。 我会留一艘船在港口。 ";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "你还没缩小你的中队规模吗, 先生? ";
				link.l1 = "是是, 我记得, 我正在处理。 ";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "那么, ‘埃克利亚顿’号准备好加入你的中队了, 先生。 ";
				link.l1 = "那我回我的船, 你应该准备出海了。 ";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "问候你, 准将。 我们前面还有一场战斗吗? ";
			link.l1 = "确实有。 我们将再次联手。 我们要突袭菲利普斯堡。 总督命令我们把荷兰人从圣马丁清除出去。 ";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "是的, 船长, 但稍后。 我会告诉你什么时候。 ‘埃克利亚顿’号必须随时准备出海。 ";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "明白了。 这将是一项艰巨的任务, 先生。 据我所知, 菲利普斯堡的堡垒有很多大炮。 ";
			link.l1 = "我相信是这样, 我的朋友, 但我们会处理好的。 准备出海, 我们很快出发。 ";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "很高兴在‘埃克利亚顿’号的甲板上见到你, 副舰队司令! 你有什么命令? ";
			link.l1 = "准备‘埃克利亚顿’号出发。 首先, 我们将航行到牙买加海岸, 然后与多伊利上校的中队一起进攻库拉索。 ";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "会有命令的, 船长, 但稍后。 我会告诉你什么时候。 ‘埃克利亚顿’号必须随时准备出海。 ";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "‘埃克利亚顿’号及其船员已准备好, 副舰队司令! ";
			link.l1 = "太好了。 那我们立即出发。 ";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "抱歉, 先生们, 我之前没能加入你们, 我正忙着在船上发布命令。 我还以为我已经很晚了, 因为我在官邸没找到你们, 所以我正要回船... ";
			link.l1 = "... ";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "与你并肩作战是我的荣幸, 德.莫尔先生! 我必须说, 我很少遇到像你这样有能力和技巧的军官。 我相信我自己不可能这么快就拿下那个西班牙殖民地的堡垒! ";
			link.l1 = "你低估自己了, 达西埃先生。 我们是一起完成的。 ";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "没错。 虽然我是侯爵, 但我仍然是个水手。 对我来说, 加勒比群岛是新的。 未被探索的, 充满了新的冒险。 上次我在这里只待了几个月, 但回到欧洲后, 我开始想念这个地方。 我想在这里为祖国服务。 而你是一位非常有才华和经验的船长, 你赢得了我诚挚的尊重和友谊。 能在你的指挥下服役, 副舰队司令, 我将不胜荣幸! ";
			link.l1 = "好吧, 我不能也不想拒绝你, 达西埃先生! ";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "我也明白‘埃克利亚顿’号现在是你的旗舰, 所以如果你决定亲自指挥它, 我完全理解。 在这种情况下, 你可以让我做你的军官, 给我另一艘船, 或者干脆解除我的职务 --弗尔热先生好心地答应我, 那时他会在法属西印度公司的舰队里给我找一个合适的职位。 ";
			link.l1 = "我可以向你保证, 我的朋友, 不会到那一步的。 你是我见过的最好的船长之一, 有你在我身边, 我们将不可阻挡。 ";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "谢谢你对我能力的如此高的评价。 还有一件事, 副舰队司令。 我现在不知道你的中队规模, 所以以防万一, 我会在卡普斯特维尔码头的‘埃克利亚顿’号船长桥上等你。 一旦你决定让这艘船归你指挥 --只要告诉我一声。 ";
			link.l1 = "很好, 达西埃先生。 ";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "那么我请求允许退下。 副舰队司令, 男爵... ";
			link.l1 = "很快见, 达西埃先生。 ";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "副舰队司令, 欢迎登船。 你想让‘埃克利亚顿’号归你指挥吗? ";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "还没, 侯爵。 等待命令。 ";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "是的, 侯爵, 我请你加入我的中队。 这艘漂亮的船将成为法国在加勒比海伟大和力量的象征! ";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "我完全同意, 大人! ";
			link.l1 = "... 现在, 让我们看看我们真正的能力! ";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// 删除埃克利亚顿的 group, 否则会有克隆-幽灵
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <—— legendary edition
		
		// 多伊利在安提瓜
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "哦, 真是巧会! 这不是查尔斯.德.莫尔船长本人吗? ! 我听说, 你现在在法国海军有了职位。 真让人惊讶, 考虑到你以前是做什么的, 这么说吧... ‘工作’... ";
				link.l1 = "问候你, 先生。 你是在说伊斯莱.特索罗的事吗? 哦, 但不是我写的英国法律, 根据法律, 该岛根据发现者的遗嘱传给了他的继承人。 所以, 我没有罪, 我只是帮助Sharp小姐得到了她应得的东西。 ";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", 船长。 我想, 法国海军的代表来到安提瓜, 心里有一个重要的目标吧? ";
				link.l1 = "确实, 先生。 我是由法属殖民地总督菲利普.德.潘西派来的。 圣克里斯托弗已被西班牙和荷兰海军中队围困。 骑士请求你和乔纳森.福克斯先生的帮助。 这是他给你的信, 上校。 ";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "我在想, 船长, 你从中赚了多少钱? 我想, 相当多, 因为你已经设法支付了无赖洛克斯利的服务费用, 那可不便宜。 我相信, 海盗首领们定期给你回扣, 让你把岛留在他们手中。 我们都很清楚, 海伦.夏普只是个幌子。 ";
			link.l1 = "上校, 我们也都知道, 海盗首领们主要是为英国利益服务, 当然不是官方的... 没有他们, 要抵抗该地区西班牙的霸权会相当困难, 你不同意吗? 所以, 从政治家的角度来看, 海岸兄弟会把岛留在自己手中, 也许比伊斯莱.特索罗成为英国海军基地更有利可图... ";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "这可能是真的, 船长, 但是... 不管怎样。 我想你来到安提瓜有重要的目标吧? 也许是因为两个前盟友 --法国和荷兰的关系已经大大恶化? ";
			link.l1 = "完全正确。 我是由法属殖民地总督菲利普.德.潘西派来的。 圣克里斯托弗已被西班牙和荷兰海军围困。 骑士请求你的帮助。 这是他给你的信, 上校。 ";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "让我看看... (阅读中)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "嗯... 非常有趣! 船长, 你的指挥官知道如何引起我的兴趣, 人们称他为狡猾的狐狸也不奇怪。 我们早就该这样做了, 而不是试图与荷兰人交朋友。 我们都很清楚荷兰公司和他们的董事代表什么。 那么, 我认为在这种情况下, 我们真的不应该拒绝帮助被围困的卡斯特维尔, 我们有足够的军队来做到这一点。 \n他们的中队有多少艘船。 什么类型, 船长? ";
			link.l1 = "我数了六艘船: 一艘80门炮的三级主力舰和五艘四级船。 他们可能还有护卫舰和大帆船。 ";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "嗯... 我们可以派出我们的中队, 由一艘100门炮的一级舰。 两艘四级舰和一艘重型护卫舰组成, 来对抗他们。 ";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "先生, 我们还有一艘66门炮的战舰‘埃克利亚顿’号, 从瓜德罗普海岸驶来帮助圣克里斯托弗防御。 ";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "一级舰将在即将到来的战斗中提供很大帮助。 ";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "完美。 在这种情况下, 我们的火力远超敌人。 胜利将属于我们。 ";
			link.l1 = "别忘了我自己的船, 先生。 我不会错过这样的战斗, 别想了。 ";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "没错。 包括来自卡斯特维尔堡垒的帮助, 胜利将属于我们。 ";
			link.l1 = "别忘了我自己的船, 先生。 我不会错过这样的战斗, 别想了。 ";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "当然, 德.莫尔先生。 无论如何, 你的航海才能在整个群岛都有耳闻。 你的旗舰将率领中队。 ";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "那我将把我中队的其余船只留在原地, 然后回来找你, 我们将赶去帮助被围困的地方。 ";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "我很快就会准备好我的船, 我们将赶去帮助被围困的地方。 ";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "那么, 你准备好出发了吗? ";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "请稍等, 先生。 ";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "是的, 先生。 ";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "那么让我们开始吧, 愿上帝帮助我们! ";
			link.l1 = "... ";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "你还有什么问题吗, 先生? ";
			link.l1 = "没有, 上校... ";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "给斯特伊弗桑特拿信, 先生。 如果你不知道我是谁, 让我自我介绍一下: 爱德华.多伊利上校, 皇家港总督和这次远征的指挥官! \n说实话, 我非常想把威廉斯塔德这个强盗窝夷为平地。 加勒比海最卑鄙。 最两面派。 最可鄙的组织, 所谓的荷兰西印度贸易公司, 认为群岛上的所有贸易都是他们的专属权利, 他们雇佣雅各布.范.伯格和其他海盗来俘获和击沉英国商人的船只... ";
			link.l1 = "... ";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "我来这里是为了结束这些 outrageous 行为, 幸运的是, 对你来说, 我提出了一种外交方式。 目前... 但如果这个可恶组织的董事不到这里来谈判, 我就把他的生意夷为平地。 我们攻占城市后, 我只会留下灰烬, 我们找到的任何火药, 都会放进你堡垒的地下室, 然后炸掉。 你的种植园也会有同样的命运, 斯特伊弗桑特本人将被吊死在我旗舰的桅杆上... ";
			link.l1 = "... ";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "你需要一年多的时间来重建你的殖民地, 然后你就没有时间搞你的阴谋诡计了。 把我刚才说的一切告诉你的‘主任先生’, 别以为这些是笑话和空洞的承诺。 我已经失去耐心了, 所以你必须完全理解我。 你明白吗, 军官? ! ";
			link.l1 = "一切都很清楚, 上校先生。 ";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "很好。 那么离开吧。 我给你整整一天时间考虑。 如果二十四小时后彼得.斯特伊弗桑特没有像你一样站在这里, 让他自己负责。 ";
			link.l1 = "... ";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//解锁界面
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "我想那个卑鄙的斯特伊弗桑特会来这里的。 如果不来 --他只能怪自己! ";
			link.l1 = "... ";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // 多伊利在岸边
			dialog.text = "你在堡垒干得不错, 德.莫尔先生。 现在我们将从陆路接近城门。 我会从这里拿大炮, 这条路更短更方便, 你将在圣玛丽亚角卸下你的海军陆战队连, 然后向威廉斯塔德移动。 如果你在路上遇到敌人, 你知道该怎么做。 不能留下任何人在我们后面。 ";
			link.l1 = "当然, 上校。 我会在城门口见你! ";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "那么, 看来我们的任务完成得相当成功。 恭喜你, 船长! 哦, 抱歉 --副舰队司令! 我们回船上吧。 我会让我的人站岗 --那个傻瓜斯特伊弗桑特可能不会冒险在我们撤退时攻击我们, 但小心点也无妨。 ";
			link.l1 = "我相信荷兰人不敢打破刚刚签署的条约。 ";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "与你合作很愉快, 德.莫尔先生。 我想我们会在皇家港或卡普斯特维尔再次见面。 ";
			link.l1 = "毫无疑问, 上校。 现在, 让我们告诉我们的人撤退。 ";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "看来, 荷兰人终于知道他们无法从那条狭窄的小路上接近我们, 因为我们的炮火覆盖了那里。 被困在城里的人可能不会冒险出击, 除非他们完全疯了。 现在我们要制造一些恐慌: 用我们的大炮轰炸城市。 我船上的人会看到, 他们会装作准备下船。 一两个小时后, 斯特伊弗桑特会吓得屁滚尿流, 准备派出休战使者。 ";
			link.l1 = "一切都在按我们的计划进行, 上校! 我们动手吧! ";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// 荷兰议会代表在威廉斯塔德城墙下
		case "holoff":
			dialog.text = "我来这里开始谈判。 你们的要求是什么? ";
			link.l1 = "我们要求与公司董事彼得.斯特伊弗桑特会面。 具体来说, 我们想谈谈由于他的公司和他自己的过错, 威廉斯塔德目前面临毁灭的威胁。 ";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "很好, 我会告诉斯特伊弗桑特先生, 我们会为你的代表团安排一条安全进入城市的路线... ";
			link.l1 = "那安全离开呢? ";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "我不明白, 先生? ";
			link.l1 = "我说: 你会为我们安排安全离开城市的路线吗? 我不确定。 我担心斯特伊弗桑特先生可能只是决定把我们的使者扣为人质。 因此, 我邀请斯特伊弗桑特先生亲自到这里来谈判。 ";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "但是... ";
			link.l1 = "军官, 我们在这里 dictate 条件。 你们的舰队被摧毁了, 驻军与城市隔绝, 如果我们决定攻城, 我们会像护卫舰穿透划艇一样穿透威廉斯塔德的防御。 现在, 你将收到一封给斯特伊弗桑特先生的信, 你将把它和我们的邀请一起交给他... ";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // 把 pchar 转给军官并和多伊利说话
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//锁定界面
		break;
		
		// 特立尼达灯塔上的西班牙军官
		case "SanJoseSpanish":
			dialog.text = "那么, 船长, 你召集休战使者是因为你想 dictate 你的要求? ";
			link.l1 = "你说得完全正确, 先生。 让我简要解释一下我来到特立尼达的原因 --这是我们对你们最近袭击圣皮埃尔的回应。 你们对城市造成了相当大的破坏, 现在你们将被迫赔偿。 赔偿金额是三十万比索。 考虑到你们的士兵在马提尼克所做的 vile 行为, 这并不多。 ";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "对不起, 先生, 但圣何塞和圣皮埃尔有什么关系? 为什么我们的殖民地要付钱? ";
			link.l1 = "因为袭击者是西班牙人, 不是荷兰人或英国人。 然后你可以把账单交给普罗维登斯的唐.德.门多萨, 连同我最诚挚的问候。 如你所知, 如果你拒绝支付赔偿, 我将命令我的人下船, 然后圣何塞将损失更多。 我相信你们的殖民地总督会做出正确的决定。 你有一天时间回应。 祝你们一切顺利, 先生们。 ";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "那么, 据我了解, 总督做出了正确的决定? ";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "拿上你的三十万, 离开我们的殖民地。 ";
			link.l1 = "太好了, 先生们。 我向你们保证 --这是最好的方式。 我希望这能阻止唐.德.门多萨和其他人袭击我们的殖民地。 别忘了把信息送到普罗维登斯和他本人那里。 祝你们好, 先生们。 ";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// 第五个任务的信使
		case "fraofficer":
			dialog.text = "查尔斯.德.莫尔船长, 请允许我报告: 菲利普.德.潘西骑士想通知你, 诺埃尔.弗尔热男爵准备出发前往圣马丁, 并将在码头等你。 ";
			link.l1 = "太好了! 谢谢你, 先生。 ";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "查尔斯.德.莫尔船长! 总督现在召见你。 一支强大的敌人中队出现在圣克里斯托弗海岸! ";
			link.l1 = "那我们不要浪费时间! ";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// 矿场的巡逻队
		case "engofficer":
			dialog.text = "你是谁? 你在这里做什么? ";
			link.l1 = "呃... ";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "这里不允许陌生人进入! 你们是谁, 间谍? 我要把你们带到指挥官办公室, 他们会处理你们的。 ";
			link.l1 = "但我们不能去指挥官办公室... ";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "如果你自己不去 --我们就只好强行拖你了! 交出你的武器! ";
			link.l1 = "没门... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// 前矿场管理员
		case "miner":
			dialog.text = "";
			link.l1 = "那么, 一切都清楚了? ";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "是的, 先生。 这封信必须亲自交给彼得.斯特伊弗桑特先生或马蒂亚斯.贝克。 ";
			link.l1 = "我相信你找从威廉斯塔德到卡塔赫纳的船不会有麻烦。 我们给了你所有必要的资金来支付旅行和住宿费用。 如果需要的话 --你会在半年后在法国委员会面前确认你的报告吗? ";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "先生, 我信守诺言。 ";
			link.l1 = "很好。 那么祝你好运。 这条路通向威廉斯塔德, 沿着走。 离这里不远。 ";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// 卡斯特维尔的信使
		case "cureer":
			dialog.text = "查尔斯.德.莫尔副舰队司令, 对吗? ";
			link.l1 = "正是。 我有幸和谁说话? ";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "我有诺埃尔.弗尔热男爵给你的口信。 他让你尽快到卡斯特维尔的总督府去。 ";
			link.l1 = "哦! 好消息! 谢谢你, 我马上出发! ";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "问候你, 副舰队司令。 弗尔热男爵给我讲了你的故事。 很多故事。 我衷心感谢你在殖民地为法国的利益所做的忠诚而出色的服务, 以及你在揭露骗子德.潘西的阴谋方面的帮助。 现在, 我和财政部长将亲自处理他, 你将取代你前任指挥官的位置。 至少, 暂时是这样。 ";
			link.l1 = "但是... ";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "没有‘但是’, 副舰队司令! 这个决定已经做出并得到了国王的批准。 我这里有一份他亲自签署的命令, 任命你为群岛法属殖民地的实际总督。 我们没有更好的人选来担任这个职位。 你在战争中的杰出经验, 你对该地区和这里负责人的了解, 你的技能和才能, 都配得上这个崇高而受人尊敬的职位。 如果我可以说实话, 我预计一段时间后你将再次被任命为这个职位, 没有‘实际’这个词。 ";
			link.l1 = "但我梦想着回到巴黎... ";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "法国需要你在这里! 财政部长现在正在欧洲集结一支海军, 我们在群岛的存在也不会被忽视。 你的主要任务将是加强和巩固殖民地, 增加我们舰队的军事力量, 而弗尔热男爵和法属西印度贸易公司将专注于贸易和国内发展! 如果不是你, 还有谁能帮助准备法国海军? \n那么, 开始工作吧, 总督! 我知道你不喜欢整天坐在房间里, 但你的任务甚至不需要这样做! ";
			link.l1 = "马上, 大人! 命令不容置疑! ";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "我很高兴你正确理解了我的意思。 我还请你去拜访德.潘西骑士: 他坚持要见你。 在他出发去巴黎之前, 我们不能拒绝他这样的乐趣, 对吧? 你会在监狱里找到他。 ";
			link.l1 = "很好, 大人... ";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// 普安斯的裁缝 Xenon
		case "Tailor":
			dialog.text = "... 会拖延的, 你明白吗? 这些材料我几个月前就订了! ";
			link.l1 = "... ";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "他们是如何确定第一艘船和第二艘船该运什么的? ! 我不只是某个乡下的裁缝 --我甚至有总督德.潘西骑士大人的订单! ";
			link.l1 = "... ";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "那么, 我现在还能做什么... 我会等。 但要知道: 我不会为未完成的订单负责! ";
			link.l1 = "问候你。 我看你遇到麻烦了? ";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "麻烦? 这说得太轻了! 哦, 我想我认出你了... 你是新任副舰队司令, 对吗? ";
			link.l1 = "反应很快。 没错, 站在你面前的是法属殖民地的第二号人物, 法国舰队副舰队司令, 查尔斯.德.莫尔。 ";
			link.l1.go = "Tailor_06";
			link.l2 = "别来这套了, 我们不在船上。 别担心, 我不会因为你没有马上认出我就叫卫兵。 就叫我查尔斯.德.莫尔吧。 ";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//魅力
			dialog.text = "大人, 请原谅我没有立即认出你! 是的, 你说得对, 我遇到了无法预见的情况。 ";
			link.l1 = "那些情况会是什么? 据我理解, 他们没有从巴黎给你带来材料? ";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//运气
			dialog.text = "哦, 非常感谢。 你说得对, 我遇到了无法预见的情况, 这就是为什么我没有立即意识到我面前的是谁。 ";
			link.l1 = "那些情况会是什么? 据我理解, 他们没有从巴黎给你带来材料? ";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "是的, 没错。 我几个月前就订了。 那时总督签署了任命你的命令, 并坚持要我为新上将的制服准备所有必要的材料, 确信这会在大都市得到批准。 ";
			link.l1 = "我想, 材料没有送到? ";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "你能想象吗! 我解释了这有多重要, 下了订单... 但他们有更紧急的货物要处理! 我该怎么办? 提前一年下订单, 希望他们能屈尊给我带来材料? ";
			link.l1 = "你具体缺什么? 也许在加勒比可以弄到? ";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "即使有可能, 我也不知道在哪里... 在这里你找不到好材料。 不过... 如果你允许, 我可以用你的旧军官夹克作为基础。 一旦你有了上将制服, 你可能就不需要它了, 对吗? ";
			link.l1 = "如果我有上将制服, 那我当然不需要简单的军官夹克了。 还有什么? ";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "我需要为制服找袖扣和领子。 通常, 我直接从巴黎工坊订购。 即使它们很基本, 我也可以修改它们, 让它们看起来更体面。 不过在这种情况下, 我需要更多... ";
			link.l1 = "因为加勒比没有巴黎工坊, 我会给你找一整批带有可拆卸领子和袖扣的当地服装。 还有什么? ";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "对于最后的修饰, 我需要非常高质量的面料。 我确实有一个 spinner 可以用粗糙的纤维甚至做出这样的面料。 但为此, 我需要材料 --最好是棉花。 一包就足够了。 ";
			link.l1 = "那也可以弄到。 接下来是什么? ";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "他们本应从巴黎送来一顶上将的三角帽, 但如果有材料, 我可以自己做。 虽然给你准备的三角帽本应是布料的, 但对于加勒比的咸风和烈日来说, 皮革会更好。 它会更耐用。 ";
			link.l1 = "我会给你弄皮革的; 别担心。 我甚至不用在伊斯帕尼奥拉的丛林里追公牛。 就这些吗? ";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "他们还应该从里昂送来高质量的丝绸。 它轻盈。 透气, 容易吸汗, 干燥更快。 最重要的是, 它不拉伸, 保持形状。 ";
			link.l1 = "是的, 我知道你说的是哪种丝绸。 不过在殖民地可能更难弄到。 ";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "材料就这些了。 我还听说你被授予了法国的最高荣誉... 圣路易勋章不应该像腰带里的小饰品一样佩戴。 它有它的位置。 所以, 请把它带给我, 我会把它缝在应该缝的地方。 ";
			link.l1 = "好吧, 我也会把它带来。 只是别弄丢了! ";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "当然不会! 我会用我的生命来守护它! ";
			link.l1 = "好吧。 如果就这些, 我去拿材料。 ";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "还有一件事... 我的缝纫工具已经没法用了。 我从巴黎订购了新工具, 但可惜... 如果你能找到所有必要的材料并把工具借给我 --只是借, 我以后会买新的! --我会立刻开始缝制。 ";
			link.l1 = "好吧, 我能怎么办呢? 我会把你需要的东西都带来。 在哪里能找到你? 你不会在港务局等我吧? ";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "我的工作室就在码头边的那栋楼里 --你上岸时, 它就在你的右手边。 ";
			link.l1 = "成交。 我会把材料拿来。 ";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "您好, 副舰队司令! 您把新制服所需的一切都带来了吗? ";
			link.l1 = "还没, 我没时间。 等等, 我会把所有东西都拿来。 ";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "是的, 我都带来了。 这是我的旧外套。 勋章和缝纫工具。 其余的材料, 我的水手很快会送到你的工作室。 ";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "太棒了! 说实话, 我没想到你能弄到所有这些东西。 我习惯只用巴黎的面料工作, 但看来用当地材料也能做出相当不错的制服。 ";
			link.l1 = "我的新制服多久能做好? ";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "通常至少需要一周, 但考虑到客户是法国在殖民地的两位最高官员... 三天后来找我, 我保证一切都会以最好的方式准备好! 我们不需要量尺寸, 我会根据你的旧外套来做。 ";
			link.l1 = "太好了! 那我三天后再来。 ";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "副舰队司令! 很高兴见到您! ";
				link.l1 = "嗯, 我按约定来取新制服了。 ";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "您好, 副舰队司令! 抱歉, 您的制服还没准备好。 ";
				link.l1 = "好吧, 我至少能看看进展如何吗? ";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "不行, 不行! 现在看起来完全不成样子, 我不想让您的期望落空。 请耐心等待。 ";
			link.l1 = "好吧, 我等。 ";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "是的, 当然! 我必须告诉您, 成品不比巴黎做的差! 您说得对, 即使在殖民地, 只要知道去哪里找, 也能找到合适的材料。 稍等一下。 给您! 请检查并试穿。 ";
			link.l1 = "谢谢。 质量太好了! 而且很合身。 ";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "不止是合身! 您可以自豪地穿着它担任法国在殖民地的副舰队司令! 还有您的勋章, 正如我承诺的, 现在被缝在合适的位置, 不会再在腰带上晃来晃去了。 ";
			link.l1 = "干得好! 您见到德.潘西骑士时, 可以告诉他我很满意。 ";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "我一定会告诉他的! 愿这件制服为您忠诚服务! 祝您好运! ";
			link.l1 = "谢谢! 再见。 ";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("你已获得副舰队司令制服! ");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//贝洛穆尔传奇版本
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "你想升级哪把武器? ";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": 攻击力 - " + FloatToString(stf(rItem.attack),1) + ", 平衡性 - " + FloatToString(stf(rItem.Balance),1) + ", 重量 - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "我改变主意了";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}