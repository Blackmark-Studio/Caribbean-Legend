// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为你效劳。 你想了解什么? ",
                          "我们刚刚还在谈这个。 你一定是忘了... ", "今天这已经是你第三次问这类问题了... ",
                          "你像鹦鹉一样重复着同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 也许下次吧。 ", "对, 不知为何我忘了... ",
                      "是的, 确实是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // 奴隶贸易商
            if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "我听说岛上出了大乱子... 奴隶起义了? ";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
            // 葡萄牙人
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "我听说那个卑鄙的混蛋‘葡萄牙人巴特’终于得到了正义的审判! 他进监狱了吗? 你知道他什么时候处决吗? 我想去看看, 我跟那个混蛋有笔账要算... ";
                link.l1.go = "Portugal";
            }
            //--> 贝琪.普莱斯之谜
            if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
            {
                link.l1 = "听着, " + npchar.name+ ", 我听说你最近新来了一位漂亮的女服务员... 可她又消失了? ";
                link.l1.go = "TBP_Tavern_1";
            }
            if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
            {
                link.l1 = "告诉我, " + npchar.name+ ", 贝琪失踪的那晚, 你有没有注意到她附近有可疑的人? 也许她在和什么人说话? ";
                link.l1.go = "TBP_Tavern2_11";
            }
            if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
            {
				sld = CharacterFromID("Villemstad_waitress");
					if (CheckAttribute(sld, "model") && sld.model != "Marquesa")
					{
						link.l1 = "好了, " + npchar.name+ ", 告诉你个好消息 —你那位宝贝女服务员安然无恙。 你得重新备足朗姆酒了, 很快客人们就会回来的。 ";
						link.l1.go = "TBP_Tavern3_21";
					}
					else
					{
						link.l1 = "好了, "+npchar.name+", 事情搞定了——你那宝贵的女招待已经回来了。 你得再多囤点朗姆酒, 过不了多久客人们就会回来。";
						link.l1.go = "TBP_Tavern3_21_1";
					}
            }
            //< —贝琪.普莱斯之谜
        break;

        // 奴隶贸易商
        case "EscapeSlaveVillemstad_T1":
            dialog.text = "是啊, 从来没出过这么大的乱子... 一千多个黑人起义了。 两座种植园被夷为平地, 每个种植园主都被杀害了。 司令官担心奴隶会进攻城市, 所以实施了戒严。 而这一切都是因为两个黑人, 一个叫塔曼戈的壮汉和一个叫伊索拉的女人... ";
            link.l1 = "听起来很戏剧性。 把整个故事告诉我, 这些黑人是谁? ";
            link.l1.go = "EscapeSlaveVillemstad_T2";
        break;
        
        case "EscapeSlaveVillemstad_T2":
            dialog.text = "塔曼戈和伊索拉 —布伦海姆种植园的奴隶, 第一座被烧毁的种植园。 这两个黑人彼此相爱。 但种植园主的儿子莱昂西奥从欧洲来了, 他看中了那个女人。 他想让伊索拉做他的私人小妾。 黑人大汉塔曼戈不接受这个主意, 伊索拉也不愿意, 她真的爱着那个黑鬼。 那个塔曼戈在非洲好像是个酋长什么的... 一个巨人般的壮汉 —比罪恶还黑, 用斧头杀人很厉害, 其他黑人都怕他。 尊敬他。 于是这个黑人带领其他奴隶起义了。 他们在夜里袭击了守卫, 把大房子外面的每个白人都杀了, 混血儿也没放过。 然后伊索拉打开了种植园的大门, 那些野蛮的'猿猴'把里面的人全杀了。 布伦堡被烧成了平地。 然后奴隶们逃进丛林消失了... ";
            link.l1 = "嗯, 这故事怎么样, 听起来像小说的情节! 一场真正的奴隶起义, 就像古罗马一样。 顺便问一下, 你是怎么知道这些的? ";
            link.l1.go = "EscapeSlaveVillemstad_T3";
        break;
        
        case "EscapeSlaveVillemstad_T3":
            dialog.text = "传闻而已, 先生, 这世上到处都是传闻。 朗姆酒能让人打开话匣子, 你只需要倾听... ";
            link.l1 = "那最后怎么样了? 他们找到那些黑人了吗? ";
            link.l1.go = "EscapeSlaveVillemstad_T4";
        break;
        
        case "EscapeSlaveVillemstad_T4":
            dialog.text = "哈, 怎么可能! 在增援部队终于到达之前, 没人敢踏入丛林一步。 后来一艘公司的战舰带着一支部队到达, 他们搜查了整个岛屿。 连一个逃跑黑人的黑皮肤或卷发都没找到。 ";
            link.l1 = "哦, 是这样! 一千个黑人就这样消失得无影无踪了? ";
            link.l1.go = "EscapeSlaveVillemstad_T5";
        break;
        
        case "EscapeSlaveVillemstad_T5":
            dialog.text = "实际上是消失在水里了。 ";
            link.l1 = "你在说什么, " + npchar.name+ "? 你我都知道黑人不会游泳。 ";
            link.l1.go = "EscapeSlaveVillemstad_T6";
        break;
        
        case "EscapeSlaveVillemstad_T6":
            dialog.text = "嘿嘿... 哦不, 那些黑人可不会那么快就成为鲨鱼的饵料。 问题是起义后的第二天晚上, 一艘三桅帆船从码头失踪了。 如果不是那个叫塔曼戈的壮汉和他的黑人干的, 我就把自己涂成黑色, 弹着班卓琴给你跳舞! 这就是为什么他们不再岛上的原因。 ";
            link.l1 = "哈, 现在我什么都听说了, " + npchar.name+ "。 你指望我相信一群半野蛮的黑人能操纵船帆和导航? 我宁愿相信一艘猴子船从几内亚猛冲过来。 ";
            link.l1.go = "EscapeSlaveVillemstad_T7";
        break;
        
        case "EscapeSlaveVillemstad_T7":
            dialog.text = "我也不信, 先生, 但证据就是那艘失踪的船。 也许那些黑人中有一个曾经在船上当乘务员, 学到了一些航海技术。 也许他们用了黑魔法, 谁知道呢! 下次再来拜访我吧, " +pchar.name+ ", 下次我再给你讲些故事。 ";
            link.l1 = "谢谢! 好吧, 我该走了。 ";
            link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "22_2");
            pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
        break;                           

        case "Portugal":
            dialog.text = "是的, 没错。 他们抓住了那个海盗。 你能相信吗? 他是在海上独自乘坐一艘小艇被抓住的。 在被扔进船舱喂老鼠之前, 他甚至一声不吭。 真的很有趣, 你知道, 这么危险的海盗被抓得像个新手一样! ";
            link.l1 = "那他为什么独自在海上? ";
            link.l1.go = "Portugal_1";
        break;
        
        case "Portugal_1":
            dialog.text = "他可能决定和他的手下分道扬镳, 毫无疑问... 他们不能公平地分配战利品。 现在他落在公司自己手里, 那些人可不喜欢开玩笑。 他们说他占有了公司的一艘船, 里面有贵重物品。 显然, 只是因为他们想从他那里榨取一些信息, 他还没有被绞死。 ";
            link.l1 = "那么, 你知道他什么时候处决吗? ";
            link.l1.go = "Portugal_2";
        break;
        
        case "Portugal_2":
            dialog.text = "没人知道。 我想一旦公司得到它想要的信息, 他们就会在他脖子上系上一根麻绳。 那个葡萄牙人现在在监狱里, 有可靠的守卫看守。 最近他们也把他的水手长带到了这里。 他的故事更令人惊讶, 他在菲利普斯堡向荷兰人自首了。 所以, 他们把他安排在他前船长隔壁的牢房里, 现在他们是邻居了, 嘿嘿... ";
            link.l1 = "奇迹确实会发生! 好吧, 我会留意消息的。 我不想错过那次绞刑。 再见, " + npchar.name+ "! ";
            link.l1.go = "Portugal_3";
        break;
        
        case "Portugal_3":
            DialogExit();
            pchar.questTemp.Portugal = "PortugalInPrison";
            AddQuestRecord("Portugal", "32");
        break;
        
        //--> 贝琪.普莱斯之谜
        case "TBP_Tavern_1":
            dialog.text = "哦, 要是你见过她就好了, 船长! 贝琪... 那么优雅, 那么甜美的笑容! 男人们会蜂拥到这里只是为了看看她。 还有他们留在我酒馆里的银币... 但三天前, 她没来上班。 当然, 我派人去她家, 但她不在那里。 家里一片混乱, 她的个人物品都不见了。 我现在不知道该怎么想了。 卫兵们一如既往地耸耸肩。 说他们有更重要的事情要做, 而不是寻找一个失踪的女孩。 说她可能只是出去了, 很快就会回来。 船长, 也许你能找到她? 如果你把她带回来, 我会付你一百达布隆。 我不能就这样失去她, 你明白吗? 她是真正的宝藏! 我必须不惜一切代价把她找回来! ";
            link.l1 = "让我看看我能做什么。 她失踪前有没有表现得很奇怪, 或者收到什么坏消息? ";
            link.l1.go = "TBP_Tavern_2";
            link.l2 = "寻找一个可能只是跑掉的女孩? 我有更重要的事情要做。 你自己处理吧。 ";
            link.l2.go = "TBP_Tavern_End";
            DelLandQuestMark(npchar);
        break;

        case "TBP_Tavern_End":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.TBP_Tavern");
            CloseQuestHeader("TBP");
        break;

        case "TBP_Tavern_2":
            dialog.text = "在她失踪的前一天, 她情绪高昂, 甚至很开心! 没有任何麻烦的迹象, 也没说要离开。 她就这么消失了! ";
            link.l1 = "有意思... 我在哪里可以找到她的房子? ";
            link.l1.go = "TBP_Tavern_3";
        break;

        case "TBP_Tavern_3":
            dialog.text = "她住在街道更远处, 在蓝色阳台豪宅对面的房子后面的一个棚屋里。 离这里不远。 ";
            link.l1 = "好吧, 我不浪费时间了。 如果我找到什么, 我会告诉你的。 ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("TBP_Poorman");
        break;

        case "TBP_Tavern2_11":
            dialog.text = "可疑的人? 她周围总是有成群的追求者, 每个人都有自己可疑的地方! 她很会调情, 知道如何吸引注意力。 ";
            link.l1 = "这一点我已经想到了。 但是有没有特别突出的人? ";
            link.l1.go = "TBP_Tavern2_12";
            DelLandQuestMark(npchar);
        break;

        case "TBP_Tavern2_12":
            dialog.text = "嗯... 好吧, 有一个。 那天晚上, 他给了她一个镶宝石的吊坠。 他坐在这里, 眼睛一直盯着她, 整晚都在她身边转。 ";
            if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
            {
                link.l1 = "那个吊坠, 碰巧不会是这个吧? (出示从乞丐那里买的浮雕) ";
                link.l1.go = "TBP_Tavern2_13";
            }
            else
            {
                link.l1 = "你说镶宝石的吊坠... ";
                link.l1.go = "exit";
                AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
            }
        break;

        case "TBP_Tavern2_13":
            dialog.text = "就是那个! 没错! 船长, 你已经找到什么了吗? ";
            link.l1 = "稍后再谈细节, " + npchar.name+ ", 现在没时间浪费了。 ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
            RemoveItems(pchar, "jewelry24", 1); 
            notification("Given: Cameo pendant", "None");
        break;

        case "TBP_Tavern3_21":
            dialog.text = "太好了, 船长! 我开始以为再也见不到她了。 那么发生了什么事? 她真的想逃跑吗? ";
            link.l1 = "这么说吧, 她不得不处理一些过去的问题。 但似乎现在一切都过去了, 她很快就会回来工作。 ";
            link.l1.go = "TBP_Tavern3_22_leadership";
            link.l2 = "嗯, 这么说吧, 她需要稍微休息一下, 不用看你那张无聊的脸。 哈哈! 别皱眉头, 我开玩笑的。 每个女士都应该有自己的小秘密... ";
            link.l2.go = "TBP_Tavern3_22_fortune";
            DelLandQuestMark(npchar);
        break;

        case "TBP_Tavern3_22_leadership":
            dialog.text = "嗯, 最重要的是她会回来工作。 你已经赢得了你的奖励, 船长。 给, 拿着 —一百达布隆, 如约而至。 还有, 拿着这张地图。 有个顾客把它留在这里, 再也没回来。 看起来它通向宝藏。 ";
            link.l1 = "好吧, 我会去看看的。 谢谢。 ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("TBP_BetsiBackToWork");
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
            else AddMapPart();
        break;

        case "TBP_Tavern3_22_fortune":
            dialog.text = "嗯, 最重要的是她会回来工作。 你已经赢得了你的奖励, 船长。 给, 拿着 —一百达布隆, 如约而至。 还有, 拿着这张地图。 有个顾客把它留在这里, 再也没回来。 看起来它通向宝藏。 ";
            link.l1 = "好吧, 我会去看看的。 谢谢。 ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("TBP_BetsiBackToWork");
            AddCharacterExpToSkill(pchar, "Fortune", 100);
            AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
        break;
		
		case "TBP_Tavern3_21_1":
			dialog.text = "你救了我一命, 船长! 我本来已经不抱希望能再见到她了……  到底发生了什么? 她真的想逃走? 我不敢亲口问她。";
			link.l1 = "这么说吧, 她得处理一些过去的麻烦事。 不过看起来已经解决了, 她很快就能恢复工作了。";
			link.l1.go = "TBP_Tavern3_22_leadership_1";
			link.l2 = "这么说吧, 她只是想暂时逃离你那张无聊的脸罢了。 哈哈! 别这么板着脸, 我是开玩笑的。 每位女士都该有点小秘密…… ";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership_1":
			dialog.text = "总之, 她能回来工作就好。 您值得这个奖励, 船长。 来, 拿着——一百枚达布隆, 就像我们说好的。另外, 还请收下这张地图, 是某位客人留下的, 后来就没再出现了。 看起来像是藏宝图。";
			link.l1 = "那我就去看看。 多谢。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune_1":
			dialog.text = "总之, 她能回来工作就好。 您值得这个奖励, 船长。 来, 拿着——一百枚达布隆, 就像我们说好的。 另外, 还请收下这张地图, 是某位客人留下的, 后来就没再出现了。 看起来像是藏宝图。";
			link.l1 = "那我就去看看。 多谢。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
        //<-- 贝琪.普莱斯之谜
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}