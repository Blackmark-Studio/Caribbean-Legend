void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		// 与阿隆索在成功登船后的对话
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "船长, 我们赢了。 先头部队正在清扫下层甲板。 没有俘虏... 哈! 看来你也没手下留情。 ";
			link.l1 = "不知为何, 我本想发表一番豪言壮语, 但他直接冲上去了。 ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
			if (sti(pchar.rank) <= 13) Achievment_Set("ach_CL_156");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "允许我直言不讳吗? ";
			link.l1 = "允许。 ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "不必了, 我们谈完了。 ";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "我们为什么攻击他们? 那艘双桅船没有威胁, 也没运输货物。 当然, 关于格林的传言很多, 但只有奴隶贩子怕他。 今天死了很多人 --为了什么? ";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "... ";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "你现在是在为船员说话吗? ";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "而且这不是第一次了... ";
			link.l1 = "你现在是在为船员说话吗? ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "不。 相信我, 如果船员有那样的疑问, 说明我不称职, 而你已经是个死人了\n"+
			"你很幸运, 伙计们从这次血腥行动中赚了不少。 船上每个水手的口袋里都塞满了达布隆金币! \n"+
			"不过没有贵重货物 --只有本地小饰品和诡异的护身符。 尽管如此, 船员们还是像强盗一样赚了一笔。 看来格林给他们的报酬不错\n"+
			"我希望你不打算索要那份金子, 船长? ";
			link.l1 = "我不打算, 阿隆索。 谢谢你告知。 ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "我打算。 确保把我的那份送到我的舱室。 ";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "永远支持你, 船长。 顺便问一下, 你打算怎么处理‘纪念号’? ";
			link.l1 = "把它当作战利品 --还能怎样? ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "还没决定"+GetSexPhrase(""," 呢")+"。 ";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "永远支持你, 船长。 顺便问一下, 你打算怎么处理‘纪念号’? ";
			link.l1 = "把它当作战利品 --还能怎样? ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "还没决定"+GetSexPhrase(""," 呢")+"。 ";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "最好别这样。 它覆盖着某种本地符号。 而且有不好的传言 --据说它曾在一场可怕的瘟疫中幸存下来, 甲板上几乎堆满了尸体\n"+
			"至于船尾的骷髅, 我都不想提: 除非有蠢货敢为了好玩去抢头骨, 否则除了我没人敢在那里站岗。 ";
			link.l1 = "知道了, 阿隆索。 回去工作吧。 ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "是, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// 第一晚与阿隆索的对话
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "船长, 抱歉在这个时候打扰你。 ";
			link.l1 = "报告, 阿隆索。 ";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "船长? 你在这里做什么? 你在这里睡觉吗? ";
				link.l1 = "不重要。 ";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "我的舱室感觉... 让人不安。 ";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "情况很糟。 船员士气低落! 大家公开说这艘船被诅咒了。 抱怨晚上看到奇怪的东西。 ";
			link.l1 = "到底看到了什么? ";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "主要是噩梦。 但最糟糕的是我们有个人死于发烧。 一个年轻小伙子, 强壮如牛, 几小时内就烧得不行了。 ";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "那是医生的事。 "+sld.name+"知道该怎么做。 ";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "这不正常。 让船员保持秩序, 阿隆索。 这是你的工作。 ";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "是是! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// 第二晚与阿隆索的对话
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "我明白。 现在很多船员都成群睡觉 --害怕独处。 好像在这艘船上真的能独处一样... ";
			link.l1 = "看来我没做到。 发生了什么? ";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "一场斗殴 --何塞刺伤了马塞尔。 他大喊着‘自己携带了瘟疫’。 ";
			link.l1 = "情况在恶化吗? ";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+"今天早上已经报告了。 我们失去了十一个人。 我们该怎么办? ";
			}
			else
			{
				dialog.text = "又失去了十一个人。 我们该怎么办? ";
			}
			link.l1 = "我会做决定。 ";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "希望如此, 船长。 何塞怎么办? 杀人不是玩笑。 ";
			link.l1 = "钟响后绞死他。 表明我们在掌控局面。 ";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "三十鞭。 如果他活下来 --那就是上帝的旨意。 ";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "是是! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "是是! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// 第三晚与阿隆索的对话
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "船长! 警报! 您必须立即到加农炮甲板去! ";
			link.l1 = "发生了什么? ";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "你最好自己看看。 来吧, 快点! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// 已经是早晨
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "早上好, 船长! ";
			link.l1 = "嗯? ! ";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "呃, 你看起来糟透了。 昨晚没睡好? 好吧, 我有好消息。 瘟疫结束了。 事实证明 --根本没有瘟疫。 ";
			link.l1 = "你是什么意思? ";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "船员被吓坏了, 开始相信那些愚蠢的幽灵船故事。 心理暗示的力量 --很可怕, 我告诉你。 它沉掉的船不止一艘。 ";
			link.l1 = "但有人死了! ";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "斗殴。 肮脏的伤口。 变质的咸肉 --只是普通的水手死亡率。 如果我们没有用被诅咒的船的故事吓唬自己, 也许损失会更少\n"+
			"船尾的那个骷髅也帮了倒忙。 幸好有个... 恶作剧的人在夜里偷了它的帽子\n"+
			"既然闪电没有因为这种亵渎而劈中我们, 船员们就振作起来, 开始搞恶作剧。 比如... ";
			link.l1 = "不准碰那个骷髅! ";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "呃... 好吧, 如果你喜欢它, 我们当然不会碰。 祝您今天愉快, 船长\n"+
			"顺便说一句, 帽子不错! 你戴着很好看。 显然不适合前主人。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// 与纪念号船员的对话
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "问候您, 船长。 您应该和格林船长谈谈。 ";
				link.l1 = "抱歉, 水手, 但你在这里很显眼。 ";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "还有什么事吗, 船长? ";
				link.l1 = "没什么。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "我明白你的意思, 船长。 我曾为一位自由船长服务 --和你很像。 他搜寻宝藏, 做贸易, 接货运。 然后他决定抢劫一些商人 --结果失败了。 幸存者因海盗罪被判处绞刑。 ";
			link.l1 = "格林船长买下了你? ";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "他把我们当货物一样批量买下。 每艘船都需要经验丰富的水手, 而格林不在酒馆招募... 但他给我们吃的, 工资也不错。 我们服务 --然后抽签。 ";
			link.l1 = "抽签? ";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "抱歉, 我们不应该谈论那个。 ";
			link.l1 = "为什么不直接离开? ";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "去哪里? 至少在这里还有机会。 也许运气会眷顾。 每艘船都有自己的命运。 格林有他的, 你有你的。 我们不是人, 只是船日志里的数字。 ";
			link.l1 = "在我的船上情况不同。 ";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "如你所说, 船长。 日安。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "我们这艘好船很久没有访客了! ";
				link.l1 = "你是水手吗? 你看起来不像。 ";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "还有什么事吗, 船长? ";
				link.l1 = "没什么。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "哈! 船长直接从牢房里买下了我。 我本应在皇家港被绞死 --因为刺伤了某个不停背诵诗歌的花花公子。 那混蛋活该。 ";
			link.l1 = "所以你很幸运, 对吗? ";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "当然! 船长不吝啬, 尽管有时你得玩他的... 游戏。 ";
			link.l1 = "什么样的游戏? ";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "每周我们都抽木棍: 短的那个意味着危险的工作, 或者有时你得跳海。 真的很有趣。 不是所有人都喜欢, 但船长说这是他筛选不合格者的方式。 ";
			link.l1 = "不合格什么? ";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "我怎么知道? 船长喜欢说话, 像牧师一样布道: ‘只有面对死亡, 你才能真正活着! ’\n"+
			"(他吐了口唾沫。 )";
			link.l1 = "在甲板上吐痰会被鞭打。 你表现得像个强盗, 而不是水手。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "问候您, 船长。 ";
				link.l1 = "你怎么会在这里? ";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "还有什么事吗, 船长? ";
				link.l1 = "没什么。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "格林船长劫持了我所在的奴隶船。 我当时病了, 在货舱里奄奄一息... 我记得不太清楚。 等我醒来时, 已经在‘纪念号’上了。 ";
			link.l1 = "其他奴隶怎么样了? ";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "我不知道。 船长说他释放了所有人, 但只有我被带上船。 其余的人一定是散落在岛屿上或因伤死亡。 那天对我来说一片模糊。 ";
			link.l1 = "至少你现在自由了。 ";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "自由? 这里没人是自由的。 船长给金子。 食物。 衣服, 但作为回报, 他要求绝对忠诚 --并让我们抽那些该死的签。 ";
			link.l1 = "抽签? ";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "每周, 有人抽到短签, 得到危险的工作 --不是所有人都能回来。 船长说这是区分生者和死者的方式。 ";
			link.l1 = "你能忍受吗? ";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "每个人都希望运气眷顾自己。 船长知道什么能驱动每个人: 对绞索的恐惧。 对金子的贪婪。 偿还救命之恩的渴望。 这些对我都不重要。 我不需要钱, 而且对于不记得的事情, 你能欠什么债? ";
			link.l1 = "你不怕这么公开地说吗? ";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "他们能把我怎么样? 这是一艘死亡之船, 船长, 而我属于这里。 但你 --你不属于。 ";
			link.l1 = "如果你这么说。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "欢迎登上‘纪念号’, 船长。 ";
				link.l1 = "海盗船上的西班牙士兵? 这可不是每天都能见到的。 ";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "还有什么事吗, 船长? ";
				link.l1 = "没什么。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "我是逃兵。 格林船长在圣何塞广场的绞刑架下买下了我。 为了我这可怜的皮囊, 他付了一大袋达布隆金币。 ";
			link.l1 = "他们为什么绞死你? ";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "萨尔多大尉派我们去丛林看守劳工, 那里一半的人一周内就死于发烧。 我觉得我的生命更有价值。 现在我为那个给我的生命标价的人服务。 ";
			link.l1 = "不后悔吗? ";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "绳子可能会缠绕很久... 船长对忠于他的人很慷慨。 尽管有时他会让我们进行奇怪的考验 --抽签。 不是每个人都幸运。 ";
			link.l1 = "抽签? ";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "你知道的。 有些人在暴风雨中被派到高处, 有些人作为先头部队。 船长说这是测试你是否准备好。 准备好什么, 我说不清, 但我希望运气站在我这边。 ";
			link.l1 = "祝你好运... 我想。 ";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "谢谢你, 船长。 死亡总会降临到我们所有人身上, 迟早而已。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "对话5";
				link.l1 = "对话5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "还有什么事吗, 船长? ";
				link.l1 = "没什么。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "欢迎登上‘纪念号’, 同行。 我叫莫蒂默.格林。 ";
				link.l1 = GetFullName(pchar)+"船长。 感谢您的接待... ";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "我们还聊点什么? ";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "你那把剑很了不起, 船长。 ";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "你的望远镜在骷髅旁边看起来很棒。 ";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "我得说, 你的船员真是五花八门。 ";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "没什么... 同行。 祝你顺风。 ";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "加勒比海对那些冲向绞刑架的人很慷慨, 这一点我知道。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "怎么? 你有什么想问的吗? ";
			link.l1 = "你身后挂着一具骷髅。 ";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "今天风不错, 不是吗? 天气也很好。 ";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "什么骷髅? 我身后只有蓝色的加勒比海。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "同意, 同行。 真希望每天都这样! ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "哈哈哈! 这个笑话永远不会过时! 别惊慌: 老约里克, 就像这艘船一样, 是我前世的纪念品。 我向你保证, 字面意思。 ";
			link.l1 = "‘字面意思? ’";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "同行, 你怕死吗? 不是威胁, 我真的很好奇。 ";
			link.l1 = "当然。 任何说不怕的人都是骗子。 ";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "不怕。 我们都会走到那一步。 ";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "你呢? ";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "哦! 死亡是所有恐惧之母。 孤独。 黑暗。 惩罚 --它们都只是她的面具。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "哦! 死亡是所有恐惧之母。 孤独。 黑暗。 惩罚 --它们都只是她的面具。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "哦! 死亡是所有恐惧之母。 孤独。 黑暗。 惩罚 --它们都只是她的面具。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "不用看太远。 以老约里克为例: 一堆骨头, 肋骨里插着灯笼 --然而即使是像你这样可怕的船长也会惊慌! ";
			if (startHeroType == 4)
			{
				dialog.text = "不用看太远。 以老约里克为例: 一堆骨头, 肋骨里插着灯笼 --就连无畏的埃伦, 伟大的肖恩.麦克阿瑟的女儿, 也被吓到了! ";
			}
			link.l1 = "你说得很好, 但你还没说该怎么处理那一切。 ";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "我知道该怎么做, 但我的方法并不适合所有人。 你可以试试, 但首先, 告诉我你的想法。 ";
			link.l1 = "圣经说没有死亡。 ";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "如果我开始害怕, 船就完了。 ";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "答案淹没在一瓶朗姆酒的瓶底。 ";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "没错。 这是那本书里我唯一同意的观点。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "令人钦佩。 但你担心是多余的: 没有死亡。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "哟嗬嗬! 一个愤世嫉俗者。 但即使没有朗姆酒, 我也要说: 没有死亡。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "很简单: 只有当你征服死亡时, 真正的生命才会开始。 我曾到过帷幕之外, 相信我, 从那以后我才真正开始生活。 ";
			link.l1 = "你说什么? ";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "没关系, 同行。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "很高兴你注意到了, 同行! 我不是爱炫耀的人, 但没有一把可怕的弯刀, 我算什么海盗? ";
			link.l1 = "那真的重要吗? ";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "正是! 我唯一一次为了个人原因从船上的宝库中拿出大笔钱, 就是为了这把刀。 两千枚达布隆金币, 同行! 见鬼, 如果我能第二次从坟墓里爬出来, 我会为了它的价格回来的! \n"+
			"这把武器本身很棒。 但不知怎么的... 感觉缺了点什么。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "某人送的礼物。 一个出色的交谈者, 他对死亡的理解无人能及 --而且想象力丰富, 如你所见。 ";
			link.l1 = "看起来很阴森。 ";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "记住你终有一死, 同行。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "我的船员彼此之间的共同点比你的多, 比如... 他们都是我从绳索和锁链中解放出来的。 每个人都感受过死亡的气息。 这比血缘或旗帜更能凝聚人心。 ";
			link.l1 = "所以, 我想你不在酒馆里招人? ";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "你会惊讶于前奴隶和死刑犯报名的意愿: 把奴隶船的货舱或绞刑架换成‘纪念号’的甲板? 我现在有178名船员 --每个人都欠我的。 ";
			link.l1 = "但你仍然必须支付他们工资并维护船只。 仅凭感激是不够的。 ";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "我是一个成功的海盗, 同行。 一个真正的人类公敌。 这是人类真正的敌人 --奴隶贩子和君主 --会称呼我的方式。 他们之间的唯一区别是头衔。 \n"+
			"幸运的是, 他们有很多金子。 我用奴隶贩子箱子里的硬币来拯救那些被王室定罪的人。 剩下的给我的船员 --我什么都不需要。 一个死人要金子有什么用? 他们很快就会明白... ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// 与阿隆索的对话
		case "Memento_Alonso_phantom_11":
			dialog.text = "这就是我们所处的糟糕情况, 船长。 ";
			link.l1 = "这是什么? ! ";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "只剩你一个了。 疾病夺走了我们所有人。 你让我们失望了。 ";
			link.l1 = "不可能! ";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "你带我们上了一艘被诅咒的船。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "你把我们都害死了! ";
			link.l1 = "阿隆索, 你怎么了? ! ";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "死者教导生者。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// 与格林的对话
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "你为什么停下来, 同行? 改变主意了? 那为什么一开始要攻击? ";
			link.l1 = "格林? 但你已经死了! ";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "哈! 死亡之物永不死亡。 而且, 你操之过急了: 也许你赢得了登船战, 但你能活下来吗... 好吧, 让我们看看! ";
			link.l1 = "那场战斗几周前就结束了! 你已经死了! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "现在结束了。 祝贺你的胜利。 ";
			link.l1 = "格林? ";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "你知道, 我很高兴。 真的很高兴你杀了我。 真的。 ";
			link.l1 = "你在说什么? ";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "我是个懦夫, 同行。 只是一个可怜的懦夫, 害怕死亡 --就像之前的成千上万的人一样。 当船员死于瘟疫时... 那是我的错, 我因恐惧而发疯。 我独自一人在一艘死亡之船上漂流了一个月。 ";
			link.l1 = "到底发生了什么? ";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "我没有通过死亡的考验。 我没有接受它。 生存下来并学到什么, 而是变得更加害怕。 为了抑制这种恐惧... 我开始强迫别人经历我所经历的。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "谢谢你, 同行。 感谢你把我从这种... 存在中解放出来。 现在我真正知道没有死亡。 我不再害怕了。 没有其他人可以指责或奴役了。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "不要把‘纪念号’和它的船长分开。 莫蒂默... 莫蒂默船长是个好人。 在多米尼加找到他。 而这艘船... 这艘船会接受你。 ";
			link.l1 = "... ";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "死者教导生者, 同行。 再见。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
}