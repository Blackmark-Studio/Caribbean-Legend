// 任务'寻找真理守护者'的NPC对话
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
		case "First time":
			dialog.text = "我能为你做什么? ";
			link.l1 = "抱歉, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 西班牙俘虏
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "你想要什么? 又来审讯? 见鬼去吧! ";
			link.l1 = "先生, 你叫什么名字? ";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "你他妈为什么关心一个你要吊死或枪毙的人的名字? 混蛋! 毕竟我不小心落入了你的手中... ";
			link.l1 = "先生, 表明身份。 我不知道你的名字就无法和你交谈。 ";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "唐" + GetFullName(npchar) + "。 给你, 你满意了吗? 现在我有幸和谁说话? ";
			link.l1 = "我叫" +GetFullName(pchar)+ "。 你以前听说过我吗? ";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "不, 该死! 我看起来像是认识西印度群岛每个流浪的流浪汉吗... ";
			link.l1 = "够了。 我们不要互相侮辱, 表现得像绅士一样。 你的命运将取决于你能告诉我什么。 如果你告诉我一些有趣的事情, 我会请求将你释放到我的监护下。 这将使你逃脱现在等待你的火枪子弹或绞索。 ";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "我的上帝, 这是一个我无法拒绝的提议。 你想知道什么, 先生? ";
			link.l1 = "谁组织了对圣皮埃尔的大规模攻击, 为什么? ";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "普罗维登斯岛驻军指挥官拉蒙.德.门多萨.里巴男爵。 他派遣了一支中队突袭和掠夺该镇, 夺取我们可能找到的任何贵重物品。 ";
			link.l1 = "你在攻击中的直接任务是什么? 具体来说, 你的命令是什么? ";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "我是海军营的指挥官。 我们的命令是夺取堡垒并确保其炮台不会在我们的登陆艇接近城镇时向它们开火。 之后, 我的人参与了对圣皮埃尔本身的攻击。 ";
			link.l1 = "你是否得知了城内贵重物品的位置? 数量和质量? ";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "我们没有确切的数量信息, 但门多萨.里巴男爵告诉我们堡垒下面有银, 港口仓库有对战争至关重要的战略原材料: 铁木和船用丝绸。 ";
			link.l1 = "你找到那些贵重物品了吗? ";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "没有。 我们什么都没找到。 仓库里装满了典型的殖民地商品, 堡垒下面是火药。 武器和铅。 但我们没有足够的时间进行更彻底的搜索... 法国援军呼啸而至, 我们被迫应战。 ";
			link.l1 = "你不觉得没找到贵重物品很奇怪吗? ";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "当然觉得, 但我通常不质疑命令。 ";
			link.l1 = "听着我接下来要告诉你的话。 圣皮埃尔堡从来没有银, 那些仓库也从未储存过铁木和丝绸。 好好想想, 先生, 在回答之前, 因为如果你的回答不能让我满意, 我会转身离开, 留下你面对你的命运... 一个悲惨的命运。 ";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "我在听。 ";
			link.l1 = "我不相信你们袭击的唯一目标是简单的抢劫。 圣皮埃尔是一个不起眼且相对贫穷的殖民地, 派一整支中队由一艘一流的主力舰率领到这里。 当然你或你的指挥官或其他人有额外的命令或指示。 他们告诉你什么了? 回答前好好想想... ";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "你要保持沉默? 好吧。 考虑一下, 我等你。 ";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "先生, 我的生命将取决于我的回答? ";
			link.l1 = "正确。 ";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "我有一些... 但你必须向我发誓你会把我弄出去, 并把我赎回到西班牙。 ";
			link.l1 = "如果你告诉我一些值得我注意的事情, 我以圣十字架发誓你将被送到我的船上赎金, 你将逃脱处决。 ";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "好吧。 迭戈.德.蒙托亚先生指示我们海军营, 我们必须在所有保密和重要的情况下找到并俘虏一个名叫米格尔.迪乔索的人, 他在圣皮埃尔的某个地方受到当局的保护。 ";
			link.l1 = "继续说。 迭戈.德.蒙托亚是谁? ";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "中队指挥官。 在你... 戏剧性到来后不久他就逃跑了。 ";
			link.l1 = "他是谁, 这个唐.迭戈? ";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "我只知道他是门多萨.里巴男爵的授权代表, 他的得力助手和关键任务的代理人。 ";
			link.l1 = "有趣... 而米格尔.迪乔索是谁, 显然这场灾难就是为了抓住他而安排的? 一定是个坏蛋, 嗯? ";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "你还记得你的誓言吗, 先生? ";
			link.l1 = "是的。 我确认如果你继续讲述你的故事, 你将作为关键证人被送到我的船上, 然后... 好吧, 我会想办法把你送到西班牙定居点。 但在你告诉我你所知道的一切之前不会。 ";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "米格尔.迪乔索是男爵的前战友, 然而有人说米格尔背叛了他。 门多萨.里巴先生想要他活着, 所以我们接到命令在任何情况下都不能杀死迪乔索。 ";
			link.l1 = "迪乔索也是西班牙人吗? ";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "是的。 迭戈.德.蒙托亚先生给了我们一个大致的描述, 并命令任何看起来像迪乔索的人必须直接交给他。 但考虑到在你反击之前我们的时间很短, 我们从来没有时间搜索。 ";
			link.l1 = "你个人认识迪乔索吗? ";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "不, 只是听说过。 我有一些同事认识他。 他们都死了。 ";
			link.l1 = "迪乔索对你的唐.门多萨的背叛有多严重, 以至于他决定派整个中队去追他? ";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "我会告诉你。 男爵最近才从西班牙来到加勒比海。 他的命令是确保西班牙珍宝船队护航队的安全, 但他却看向内陆... 寻找印第安黄金。 他被隐藏宝藏的谣言冲昏了头脑。 他认为在尤卡坦的丛林深处存在一座古老的玛雅城市 - 塔亚萨尔, 传说中的黄金之城\n男爵派了几次探险队去寻找这座城市, 但都被彻底消灭在荒野中。 毫无疑问, 他们每个人都被住在那里的好战的伊察人屠杀了\n最终, 宗教裁判官文森托受够了唐.门多萨的幻想和优秀士兵的无谓死亡。 宗教裁判官向马德里通报了情况。 总督禁止唐.门多萨寻找这座神秘的城市, 并专注于他的职责。 就在那时, 米格尔.迪乔索出现了\n他说服男爵组织另一次探险, 令人惊讶的是这次成功了。 他们发现了一座古城的废墟和一堆镶满珠宝的黄金。 但在返回的路上, 他们遭到了蚊子部落的袭击\n除了米格尔, 所有人都死了, 印第安人的飞镖浸有当地毒药, 即使是小划痕也会在几天内导致痛苦的死亡。 迪乔索带着他能携带的宝藏回到了普罗维登斯\n该死! 男爵高兴得无法形容, 他紧急写信给马德里和圣地亚哥的文森托神父, 毫无疑问他想在尊敬的神父面前炫耀他的成功。 然后准备了一艘护卫舰将宝藏运回西班牙。 迪乔索自愿护送它。 ";
			link.l1 = "让我猜猜。 他没有运送黄金? ";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "正确, 先生! 护卫舰连同全部货物和船员, 包括迪乔索, 都消失得无影无踪。 男爵勃然大怒。 他再次在埃斯科里亚尔面前蒙羞, 这让文森托神父非常满意。 现在唐.门多萨是一个痴迷于恢复受伤的骄傲。 丢失的宝藏和米格尔.迪乔索的人";
			link.l1 = "有没有可能护卫舰只是遇到了风暴而沉没了? 或者被海盗俘虏了? ";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "男爵当场发誓说他确信迪乔索背叛了他。 我不知道细节。 几周后, 迭戈.德.蒙托亚先生带着新的信息到来, 说米格尔.迪乔索可能在圣皮埃尔。 ";
			link.l1 = "嗯。 有趣。 又是那些印第安宝藏。 一切似乎都可疑地与它们有关... 那么, 你没有找到迪乔索? ";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "没有。 老实说, 如果他曾经在这里, 我会感到惊讶。 男爵如此痴迷于捕捉迪乔索的想法, 以至于他会相信最牵强的幻想。 ";
			link.l1 = "告诉我, " + npchar.name+ ", 唐.门多萨是如何发现这个... 呃... 塔亚萨尔城的? 他不是梦到的, 对吧? 有没有一些事实或其他什么? ";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "是文森托神父首先听说了塔亚萨尔和黄金之城的所谓存在。 他从哪里得知的, 我不知道... ";
			link.l1 = "这是一个有趣的发展。 文森托神父自己提出了塔亚萨尔存在的理论, 自己通知了西班牙, 并开始给男爵制造麻烦... ";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "作为一名天主教徒, 你应该知道神圣法庭的这些神父是如何工作的... 他不是无缘无故通知马德里的。 他有某种目的, 但男爵的到来显然不是他计划的一部分。 无论如何, 我对那方面一无所知。 我从来没有与宗教裁判所打交道的欲望。 ";
			link.l1 = "好吧。 你给了我很多有趣的信息, " + npchar.name+ ", 并且忠于我的誓言, 我要把你从这里带出去。 我稍后会回来接你, 但现在... 让我想想你告诉我的话... ";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//禁止对话
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "先生? 你会遵守你的承诺吗? ";
			link.l1 = "我总是信守承诺。 今天是你的幸运日, " + npchar.name+ "。 你将和我一起去古巴的圣地亚哥。 到达后我会告诉你更多关于我的计划。 但现在, 欢迎登船。 你将被护送到港口并送到我的船上。 ";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "感谢你, 船长。 我很高兴你是一个守信用的绅士。 ";
			link.l1 = "你可以稍后表达你的感激之情。 你将是我的客人, 但在守卫下。 不要误解, 我仍然需要你。 ";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "我明白, 先生。 我以西班牙军官的名义向你保证, 我不会试图逃跑。 ";
			link.l1 = "上帝保佑谨慎的人。 船上见。 ";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//禁止对话
			chrDisableReloadToLocation = false;//打开地点
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "船长, 你在古巴的目的是什么? 你是来送我下车的吗? 我甚至不敢奢望... ";
			link.l1 = "正是如此, 我是来把你送回你的同胞那里。 现在, 我来这里的原因比那更复杂一点。 但那不再与你有关。 我现在就让你走, 不用赎金, 但条件是你要向我发誓两件事。 ";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "它们是什么? ";
			link.l1 = "第一, 我会给你一封密封的信。 你要亲自把这封信交给圣地亚哥的宗教裁判官文森托神父。 如果他问你信是谁写的, 你怎么得到的, 告诉他真相... ";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "第二, 你至少一周内不得协助或帮助任何寻找我和攻击我船的企图。 同意吗? ";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "就这些? ";
			link.l1 = "是的, 就这些。 满足我的条件, 你就可以走了。 ";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "我向你发誓, 先生, 我会亲自把信交给文森托神父, 并且我不会采取任何可能激起圣地亚哥驻军对你或你的船的攻击的行动。 请放心, 我会信守诺言。 我是西班牙人, 我尊重强大而高贵的对手。 ";
			link.l1 = "好吧, 唐" + GetFullName(npchar) + ", 我接受你的誓言, 现在让你走。 给你, 把这封信带给宗教裁判官。 你现在自由了。 ";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("你给了信");
			PlaySound("interface\important_item.wav");
			dialog.text = "再见, 先生。 我希望我们永远不会在战场上再见面。 那会让我非常难过。 ";
			link.l1 = "再见... ";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//打开地点
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "我的上帝, 多么幸运的相遇! 你好, " +GetFullName(pchar)+ "先生! 我看到你已经成为圣地亚哥的受欢迎的客人。 你在为神圣宗教裁判所工作吗? ";
			link.l1 = "问候你, " + npchar.name+ "先生。 我以为我们再也见不到了, 至少不会在友好的情况下! 不, 我只是顺道拜访文森托神父。 你呢? 现在在圣地亚哥服役? ";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "在你把我从逮捕中解救出来后, 我不得不留在圣地亚哥, 回到普罗维登斯对我来说不安全... 但如你所见, 我信守了诺言。 没有西班牙船只紧追你... ";
			link.l1 = "我很高兴我们都是守信用的人。 ";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "听着, 船长, 你介意喝杯朗姆酒吗, 可以说是为了我们的重逢? 我从没想过我会向一个法国人提议, 但你, 先生, 是个例外。 ";
			link.l1 = "当然! 我不介意用朗姆酒漱漱口。 我们去酒馆吧。 ";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "啊,  salud! ";
			link.l1 = "我们为什么干杯, 军官先生? ";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "让我们为中立的事情干杯, 但与我们俩有关。 例如, 为祖国英勇而成功的服务! 我们都有自己的! ";
			link.l1 = "也让我们为我们的君主达成协议, 法国和西班牙在国内和加勒比海都停止战斗干杯。 ";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "说得好, 船长! 为和平干杯! 我会告诉你在西班牙怎么喝! Arriba, abajo, al centro y pa'dentro! ";
			link.l1 = "为和平... (喝酒)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "啊哈! 古巴朗姆酒确实是加勒比海最好的... ";
			link.l1 = "我同意。 告诉我, 他们有没有因为你在圣皮埃尔被俘而惩罚你? ";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "幸运的是, 我只受到了轻微的惩罚。 那场灾难已经过去了。 毕竟, 殖民地需要军官。 ";
			link.l1 = "你的指挥官... 他叫什么名字... 迭戈, 对吧? 那场徒劳的突袭对他有什么影响? 他被降职了吗? ";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "哦, 不! 只要我们亲爱的迭戈.德.蒙托亚有唐.拉蒙.德.门多萨.里巴支持, 他就不会受影响。 顺便说一句, 唐.迭戈昨天刚到圣地亚哥。 他从圣何塞来。 ";
			link.l1 = "你不是在说吧? 有趣! 幸好我们没有在街上相遇。 恐怕那件事可能会以决斗告终, 哈哈! ";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "迭戈先生现在没有时间陪你, 船长。 他现在有太多的利害关系, 不敢在决斗中冒险。 他和门多萨男爵在西大陆想出了一些计划。 他在哈瓦那组建了一支中队, 不日就要起航回西班牙了。 ";
			link.l1 = "你也在他的船员里吗? ";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "不。 明天我要出发去波多黎各的圣胡安驻军。 有门多萨在, 我在普罗维登斯不再受欢迎。 ";
			link.l1 = "那么, 让我们为你的新职位干杯, 愿那里只有快乐时光和美丽女孩等着你。 ";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "非常感谢, 先生。 也祝你各种好运。 啊, 我想我该走了。 我喝完这杯就离开你。 ";
			link.l1 = "愿主与你同在, " + npchar.name+ "先生。 也许我们会在和平时期再见面。 ";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "正如我告诉你的, 迭戈先生: 鱼上钩了; 上钩, 线和沉子... 哦, 看来我们又见面了, 先生。 不幸的是, 不是在我们希望的和平氛围下。 ";
			link.l1 = "" + npchar.name+ "? 好吧! 我没想到。 出于某种原因, 我以为你是一个诚实。 高贵的军官。 原来我错了。 ";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "我哪里错了? 我信守了诺言, 我没有发誓要和你永远友好。 没什么改变, 先生。 你仍然是西班牙的敌人和我个人的敌人。 这里不是圣地亚哥, 没有文森托神父, 他的安全通行证也帮不了你... ";
			link.l1 = "哦, 是这样吗? 我恰好认为一边喝朗姆酒一边友好交谈, 同时试图引诱我进入陷阱是相当背信弃义的, 你不觉得吗, " + npchar.name+ "先生? ";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "你敢说我背信弃义, 你这个娘娘腔? ! ";
			link.l1 = "... ";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// 文森托使者
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "嘿, 你! 是的, 就是你! " +GetFullName(pchar)+ "? ";
			link.l1 = "是的, 伙计。 是我。 ";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "我有一封重要人物的信。 你已经知道是谁了。 ";
			link.l1 = "我知道, 给我。 ";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "给你。 给我几个硬币作为我的辛苦费怎么样? ";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "拿点银币。 你诚实地挣到了。 ";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "你想骗我吗, 伙计? 你已经收到送货费了。 ";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "谢谢, 小伙子。 很高兴与慷慨的绅士打交道。 ";
			link.l1 = "好了, 滚吧, 关于这里发生的事一个字也不要说。 ";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "哈瓦那狼是你的朋友... ";
			link.l1 = "嗯? 你还在这里... ";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//打开地点
		break;
		
		// 船夫盖亚.马什
		case "boatsvandega":
			dialog.text = "欢迎登上'令人钦佩号', " +GetFullName(pchar)+ "船长! ";
			link.l1 = TimeGreeting() + "! 令人惊讶。 你认识我? ";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "法国殖民地谁没听说过伟大的" +GetFullName(pchar)+ "船长, 那个把攻击圣皮埃尔的由一艘战列舰率领的西班牙中队打得落花流水并杀死了整个敌人袭击队的人! 你是民族英雄! ";
			link.l1 = "哦, 得了吧.'英雄'... 我只是一名履行对法国职责的士兵。 ";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "不要以为很多士兵能做到你所做的, 船长... 呃, 我想请你在酒馆喝杯朗姆酒, 但唉: 船长禁止让船员喝一滴朗姆酒, 我不想树立坏榜样... ";
			link.l1 = "嗯... 所以你自己不是船长? ";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "我看起来像船长吗? 呵呵! 不, 我只是水手长。 名字是塞尔日.德加。 我们的船长盖乌斯.马沙整天泡在酒馆里, 与此同时我们一直在等待一些'商人'商队。 船长欠水手们津贴, 也欠我们, 全体船员完全没钱了.. ";
			link.l1 = "怎么了? 西班牙香草商队没有出现被掠夺? ";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "没门! 我们的船长在捕获这艘大帆船后就结束了海盗生涯。 你看, 他听说很快有一支前往欧洲的贸易商队将在瓜德罗普岛停留, 他们会购买香草。 所以他在布里奇顿把我们的货舱装满了香草! 以为他能以每箱三百比索的价格出售, 是啊, 机会渺茫! \n当然, 我们到达时没有香草商队, 卖给当地人会亏损。 所以我们在这里, 等待'商人', 我相信他们总有一天或三年后会出现... 船长整天坐在酒馆里, 成为一个皇家麻烦, 纠缠每个人。 现在, 最后, 他准备以两百比索出售, 只是为了保本\n我们所有的钱都投入了那批货物。 有一天, 船员们会把他绑起来, 廉价出售香草只是为了偿还我们的债务... 我发誓我看到它随时可能发生。 ";
			link.l1 = "是的... 你的船长怎么了? ";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "嗯, 如果一件事值得做, 就值得做好。 他两者都不做。 他是个糟糕的谈判者。 如果他也运送货物, 情况会不同, 但他想感觉自己像个真正的商人。 我希望他有一天晚上掉进海里... ";
			link.l1 = "我明白了, 塞尔日。 别担心, 我相信有一天你的... 商队会出现。 ";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "哦, 我不相信奇迹, 船长。 也许我们有一天会再见面, 喝杯朗姆酒... 我现在愿意为一些朗姆酒做任何事... ";
			link.l1 = "祝你好运, 伙计。 ";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// 激活大帆船
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "呃, 船长, 我真的想喝一口朗姆酒! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// 盖伊.马什
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho! 你碰巧是商船来的吗? 不? 哦, 对不起。 当然不是... 我搞错了。 ", "我没心情, 先生, 所以找别人聊吧。 ", "啊, 又是你? ! ", "嗯... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("别担心, 伙计。 这种事时有发生。 ", "喝杯朗姆酒, 船长。 这会让你轻松一点... ", "别紧张, 伙计。 这对你的健康不好。 ", "好吧, 好吧。 我走了。 ", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "啊 呃... 嗯... 这到底是什么? ..";
			link.l1 = "安静, 伙计... 别出声... ";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "嗯? 什么? 该死! ";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "啊啊! 你是谁? 你想从我这里得到什么? ";
			link.l1 = "如果你不闭嘴, 我就把你的牙打掉, 明白吗? 你抢这艘船时拿的圣器在哪里? ";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "什么器皿? 我不知道你在说什么! 这是我的船! ";
			link.l1 = "你的船? 直到不久前她还叫'圣玛格丽塔号', 悬挂西班牙国旗航行... 我问你, 那些圣器在哪里? 一个金质圣体匣, 一个镶有青金石的十字架, 和一个金香炉? 你对它们做了什么? 你没卖掉它们, 是吗? ";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "哦, 上帝, 我不敢相信我的耳朵... 你是西班牙人? 哦, 不... 你不是西班牙人! 你是法国人! 那更糟! 你已经卖给了那些卑鄙的卡斯蒂利亚人! 这些天他们买法国人的灵魂多少钱? 我什么都不会告诉你, 叛徒! 你不会得到那些小饰品的! ";
			link.l1 = "一句话也不说? 那对我来说没问题。 反正这里不是审讯的最佳地点... 我们要堵住你的嘴, 防止你尖叫, 然后我们要进入我的长艇... 你最终会说话的, 伙计。 我毫不怀疑。 ";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "你这个西班牙叛徒! 你最好... ";
			link.l1 = "安静, 恶棍... 紧跟在我后面, 否则我会把你打倒, 拖着你的脚穿过甲板。 ";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// 大帆船船长 - 卡洛斯.格瓦拉
		case "gevarra":
			dialog.text = "我能为你做什么, 先生? ";
			link.l1 = "情况如何, 船长? 是什么风把你吹到巴斯特尔的? 据我了解, 你是西班牙人, 悬挂荷兰国旗航行? ";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "有什么问题吗, 先生? 是的, 我是西班牙人。 从名字和我的船的类型很容易猜到, 但我在这里是完全合法的。 我有荷兰西印度公司的许可证, 所以... ";
			link.l1 = "别大惊小怪, 先生! 实际上我们很高兴你是西班牙人... 告诉我, 你是来进口还是出口的? ";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "我从哈瓦那带来了商品, 并在当地市场出售。 现在, 我在等待一些有利可图的货物, 以避免空舱回家。 ";
			link.l1 = "先生, 我有一个商业提议给你! 如果你帮助我, 你可以赚很多钱。 我们可以讨论一下吗? 顺便问一下, 你叫什么名字? ";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "卡洛斯。 卡洛斯.格瓦拉船长。 你的提议是什么? ";
			link.l1 = "我需要购买一批香草并将其送到古巴, 给一个名叫" + pchar.questTemp.Guardoftruth.LMname + "的人, 圣地亚哥灯塔的看守人。 然而, 我有一个严重的问题。 首先, 没有商店有我需要的香草数量... ";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "其次, 我必须立即出发前往圣克里斯托弗, 我不知道我会离开多久。 我每天都在赔钱, 明白吗? 这真他妈的遗憾! ";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "我明白。 真遗憾, 先生。 毕竟, 你不能赚世界上所有的钱。 那么你想从我这里得到什么? ";
			link.l1 = "看那边。 看到那艘大帆船了吗? 她装满了我急需的香草。 问题是大帆船的船长脑子里有一些胡说八道, 关于很快会有一个香料商队来这里以利润购买他的货物, 几乎每箱三百比索! ";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "是的, 现在周围有很多天真的人, 傻瓜和他的钱很快就会分开... ";
			link.l1 = "天真一是回事, 但他简直是愚蠢! 我提出以两百一十比索购买他的香草, 他甚至在这里的商店都卖不到两百。 你能相信吗, 他让我滚开! 他说他只卖两百五十! ";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "哈哈! 真是个白痴! ";
			link.l1 = "是的! 这基本上就是我对他说的。 当然他对我很生气... 但我真的需要那些香草! 这是我的提议, 先生。 我不是商人, 但我认为你是交易艺术的真正大师。 而且你有一个宽敞的货舱... ";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "说服这个该死的傻瓜把货物卖给你。 在我当面侮辱他之后, 他现在不会卖给我了。 我愿意支付每箱两百一十比索。 如果你降低价格, 差价留给你自己。 为此, 我会包租你的船把香草送到圣地亚哥";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "你愿意为运输支付我多少钱? ";
			link.l1 = "你想要多少? ";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "圣地亚哥相当远... 三万比索。 ";
			link.l1 = "太多了, 朋友。 在这里和我妥协。 ";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "好吧, 反正这是我的路... 两万五千, 一分不少。 ";
			link.l1 = "很好。 大帆船的船长叫盖乌斯.马沙。 他整天在酒馆里生闷气。 我希望你能说服他放弃他的香料。 ";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "我以前和更大的白痴做过生意。 我会告诉他所有关于谁在散布关于商队的谣言, 谁应该以天价购买商品的细节。 一旦我让他相信这一切都是他想象的虚构, 他就会卖掉, 我敢肯定。 ";
			link.l1 = "那么, 我们成交了? ";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "如果你有现金支付香草和运费, 我们就成交。 正如迷人的爱尔兰谚语所说:'让我看看钱.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "给你, 看看。 都在这里。 ";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "我的船上有银。 我去拿, 马上回来! ";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "你把钱带来了吗? ";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "给你, 看看。 都在这里。 ";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "我现在就去拿! ";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "明天";
				iTemp = 1;
			}
			else
			{
				sTemp = "今天";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "太好了! 我喜欢和明智的合作伙伴做生意。 " + sTemp + "早上十点回来。 我想那时我们共同的朋友盖乌斯会醒悟过来。 ";
				link.l1 = "太好了! 回头见! ";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "太好了! 我喜欢和明智的合作伙伴做生意。 我要上岸了。 三小时后回来。 我想那时我们共同的朋友盖乌斯会醒悟过来..";
				link.l1 = "太好了! 回头见! ";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // 钱立即扣除
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "先生, 我清楚地记得我的角色。 别担心, 他可能是个硬坚果, 但我会破解他。 ";
			link.l1 = "谢谢你。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "完成了, 先生。 这个可怜的人很高兴我想买他的香草。 当我数预付款时, 他的手高兴得发抖 - 或者也许只是因为朗姆酒。 我们明天中午将在卡普斯特海滩装货, 以避免港口海关人员的任何不必要的注意\n我一装货就立即起航前往圣地亚哥。 到达后, 我会联系你在灯塔的合作伙伴, 并在那里交货后将香草签给他。 你想让我给他带个口信吗? ";
			link.l1 = "是的。 这是一封信。 你说明天中午在卡普斯特海滩成交? 好吧, 万一发生什么事, 我会在岬角外抛锚, 无法进入岛屿。 ";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("你把信交了");
			PlaySound("interface\important_item.wav");
			dialog.text = "你可以信任我, 先生。 我是个诚实的人。 此外, 我不想和你争吵, 商人没有声誉就什么都不是。 但如果你想观看并验证, 这对我来说也不困难。 ";
			link.l1 = "我很感激, 先生。 我明天会观看交易, 你一启航, 我就去圣克里斯托弗处理我的事。 ";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//禁止等待
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "船长, 我向你保证: 我不会让你失望, 我会全面履行我们的交易条件。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// 马沙的水手
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("嗨! 嘿- 万岁! 老船长终于给了我们工资! 为船长三声欢呼! 嗨!","它是一品脱装的吗? 我要一个! ","愿我们的钱包鼓鼓, 我们的女人更丰满! 万岁!","他们躺在那里, 所有善良的死人, 嗝! 就像在酒馆里到破晓。 哟吼吼, 再来瓶朗姆酒! ","哟吼吼, 再来瓶朗姆酒!");
			link.l1 = LinkRandPhrase("是的, 伙计。 ","你不觉得你已经喝够朗姆酒了吗? ","喝酒和魔鬼已经为其他人做了... ");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "停下! 谁在那里? 警报! 击退登船者! ";
			link.l1 = "... ";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// 多米尼加湾的英国人
		case "dominica_hunter":
			dialog.text = "哈哈! 你也来找罗利船长的宝藏, 嗯? 我们找啊找啊找, 就是找不到。 我希望这些笨蛋中至少有一个能猜到游到瀑布后面的岩架上! ";
			link.l1 = "你是福克斯上校的人, 不是吗? ";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "我可能与海狐有联系。 你不需要知道, 没有意义。 你现在不需要知道任何事情。 你找到了我的宝藏, 我们现在欠你一个巨大的感谢... ";
			link.l1 = "我明白了。 你不是海狐, 更像是海狗... 或者豺狼。 什么更适合你? ";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "看起来我们手上有一个自然哲学家, 孩子们。 动物王国的真正专家! ";
			link.l1 = "你想检查我的军刀的锋利度吗, 豺狼? ";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// 贝琳达.里贝罗
		case "belinda":
			dialog.text = TimeGreeting() + ", 先生。 我能为你做什么? ";
			link.l1 = "你好。 你是唐娜.贝琳达.德.里贝罗吗? ";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "是的, 我是。 我有幸与谁交谈? ";
			link.l1 = "我是" +GetFullName(pchar)+ "船长, 夫人。 请不要被我的法国姓氏吓倒, 目前我正在执行圣地亚哥尊敬的宗教裁判官文森托神父的任务。 ";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "真有趣! 我听说神圣法庭和耶稣会充满了来自各个阶层和民族的人, 但我以前从未亲自见过为他们工作的外国人。 我能为你做什么, 先生? ";
			link.l1 = "你拥有一件尊敬的神父非常感兴趣的物品。 一个金质圣体匣, 一个你最近从威廉斯塔德银行家那里获得的圣体显供架。 ";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "你消息很灵通, 先生。 好吧, 知道你为谁工作, 这应该不足为奇。 是的, 我买了那个圣体匣, 它当然不应该像一些小玩意儿一样被留在商人的店里, 旁边是被盗的饰品和典当品。 ";
			link.l1 = "你有那个显供架吗, 夫人? ";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "是的。 我本打算把它送给我们的教区教堂, 但这里发生了这么多事... 我不能... 哦, 对不起... ";
			link.l1 = "你在哭泣吗, 夫人? 我的话给你带来悲伤了吗? 如果是这样, 请原谅我。 ";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "哦, 求你了, 先生... 让我们回到我们的谈话。 据我了解, 文森托神父需要这个圣体匣? 你想让我把它交给你? ";
			link.l1 = "这个珍贵的容器原本是为圣地亚哥大教堂准备的, 但被一个普通海盗捕获, 并与其他圣物一起卖给了一个高利贷者。 我的任务是把被盗的东西归还原处。 当然, 我会全额补偿你的费用。 ";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "哦, 你不必这样! 你真的认为这笔钱对我意义重大吗? 我为圣母教堂买了这个圣体匣, 我会毫不犹豫地把它交给它的真正主人, 更不用说为文森托神父服务的耶稣会成员了。 但是, 另一件事让我深感不安。 你能在一位教会的忠实女儿需要时帮助她吗? ";
			link.l1 = "你是一位高贵的女性, 夫人。 什么烦恼困扰着你? 我如何帮助你? ";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "哦, 但是先生... 我不敢向耶稣会的兄弟本人求助。 你们总是那么忙... ";
			link.l1 = "你已经问了。 怎么了? ";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "你能作为圣教会的代表向我保证, 永远不会有人知道我向你请求的事情吗? ";
			link.l1 = "我向你庄严宣誓, 夫人。 这不是忏悔的印章, 但我不会向任何人透露一个字。 ";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "很好。 我信任你。 我非常亲爱的朋友埃斯特班.索萨遇到了麻烦。 他在旅行时被土匪抓住, 他们要求十万比索的赎金。 我没有那么多钱, 只能从我的津贴中凑集大约一半。 我不能在这种事情上向任何人求助, 因为他们发誓如果我这样做就会杀了他\n此外, 我为我亲爱的... 朋友担心, 害怕最坏的情况。 他们可能一拿到钱就杀了他, 以确保他不会向卫兵告发他们。 也许你, 一位勇敢的船长, 一位基督徒, 也是协会的兄弟, 可以说服土匪接受我拥有的钱, 不要伤害他... ";
			link.l1 = "交换何时何地进行? ";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "他们的头目是一个叫'屠夫巴蒂'的人。 他说他每天晚上11点到午夜都会在丛林的洞穴入口等待埃斯特班的赎金... ";
			link.l1 = "这些条件异常具体... ";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "显然他们想让我迅速凑齐全部赎金, 不想让我向任何人求助... 但我找不到这么多钱, 我永远也做不到! ";
			link.l1 = "别哭, 夫人。 我会尽力帮助你。 耶稣会的兄弟永远不会让一位正义的基督徒女性处于危险之中。 ";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "我必须信任你... 但是船长,'屠夫巴蒂'还说, 如果赎金携带者不单独来, 或者我去卫兵那里, 他会立即杀死可怜的埃斯特班! ";
			link.l1 = "我会记住的。 ";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "给你, 拿着这个。 这是我能凑集的五万比索。 说服那些强盗至少接受这个。 告诉他们我再也没有一分钱了! 把埃斯特班带回来! 一旦你这样做, 我会很高兴地把圣体匣交给文森托神父。 ";
			link.l1 = "我会尽我所能, 夫人。 让我们抱最好的希望。 ";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "愿上帝帮助你, 勇敢的船长! 我会为你祈祷! ";
			link.l1 = "... ";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//关闭地图
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //关闭遭遇战
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "你有什么消息吗, 船长? ";
			link.l1 = "还没有。 请等待, 夫人。 我不会让你失望的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "你有什么消息吗, 船长? ";
			link.l1 = "是的, 夫人。 恐怕不是好消息。 ";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "告诉我, 别让我等! 你和强盗见面了吗? ";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "给你, 拿回你的五万比索。 我不需要它。 也拿着这枚戒指。 我相信你会觉得熟悉。 ";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "给你, 拿着这枚戒指。 我相信你会觉得熟悉。 ";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "它... 是的, 很熟悉。 埃斯特班怎么了? ";
			link.l1 = "我按照你告诉我的在洞穴里找到了强盗.'屠夫巴蒂'和埃斯特班.索萨是同一个人。 他策划了绑架来敲诈你。 他告诉了我关于你们... 的关系。 他还说他不想再见到你了。 我拿了你给他的戒指作为证据。 ";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "这个... 是的, 是的, 我知道。 埃斯特班怎么了? ";
			link.l1 = "我按照你告诉我的在洞穴里找到了强盗。 他们袭击了我, 把我绑起来, 拿走了你的钱.'屠夫巴蒂'和埃斯特班.索萨是同一个人。 他策划了绑架来敲诈你。 他告诉了我关于你们... 的关系。 埃斯特班放了我, 给了我这枚戒指作为证据。 他说你再也见不到他了。 ";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "出于对你的尊重, 我给了他一个教训, 但没有杀他。 ";
			dialog.text = "我的上帝! 我不敢相信我的耳朵! 为什么这一切都发生在我身上, 为什么? ! 我做了什么让他... .";
			link.l1 = "夫人, 我求你, 不要为此自责。 那个无赖不值得你掉一滴眼泪。 " + sTemp + "";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "此外, 这是一份礼物, 让你振作起来。 ";
			dialog.text = "哦... 我会努力冷静下来。 先生, 我必须感谢你的帮助。 给你, 拿着你的圣体匣。 " + sTemp + " 愿主与你同在。 ";
			link.l1 = "谢谢你, 夫人。 别担心, 洞穴里发生的事不会有人知道。 我们耶稣会士总是信守诺言。 现在如果你愿意, 我必须走了。 ";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("你收到了一个金质圣体匣");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("你收到了一个护身符");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// 埃斯特班的强盗
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "站住, 伙计! ";
			link.l1 = "我就站在这里。 ";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "你带钱了吗? ";
			link.l1 = "多么愚蠢的问题。 不, 我出来摘曼加罗萨... 否则你认为我为什么会来这里? ";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "哦吼吼! 一个喜剧演员! 进洞穴去, 巴蒂在等你。 ";
			link.l1 = "你显然是一个经验丰富的守卫... 有了这种态度, 你适合守卫菲利普国王本人。 我会自己进去。 ";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//打开地点
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//禁止等待
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// 埃斯特班-巴蒂
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "你让我等了... 你带钱了吗? ";
			link.l1 = "你是'屠夫巴蒂'吗? 在我看来你不像普通强盗。 ";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "你在乎我长什么样干什么? 你到底有没有该死的钱? ";
			link.l1 = "人质在哪里? ";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "你会得到你的人质。 来吧, 把硬币给我。 别让我生气, 小子。 ";
			link.l1 = "巴蒂, 我看起来像个傻瓜吗? 在我看到埃斯特班.索萨活蹦乱跳之前, 你不会看到一分钱。 他在哪里? ";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "哦, 你在固执己见, 嗯? 好吧, 我们会给你一个深刻的教训... 伙计们, 让我们给这个混蛋开个新洞! ";
			link.l1 = "混蛋! ";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// 强制军官
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //允许军官
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "你跳够舞了吗? 埃斯特班.索萨在哪里? 来吧, 告诉我, 否则我会把你的头按在水下直到气泡停止! ";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "不... 请不要伤害我! 我是埃斯特班.索萨。 ";
			link.l1 = "什么? ";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "是的, 是的。 我不是'屠夫巴蒂'。 我只是... ";
			link.l1 = "你这个无赖! 所以你决定通过'绑架'自己从德.里贝罗夫人那里吸走十万比索? ! ";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "你需要理解我, 男人对男人。 贝琳达... 她对我的痴迷爱真的让我厌烦。 她日夜缠着我, 伙计! 甚至她丈夫也开始怀疑我们, 而他半瞎! ";
			link.l1 = "好吧, 那怎么样! 所以你们是情人? ";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "不再是了。 我刚从她那里跑出来。 ";
			link.l1 = "你决定拿些硬币作为路费, 嗯? 那么, 我现在该怎么处理你? 像你试图对我做的那样把你的尸体藏在丛林里? ";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "不! 我不想见血, 我发誓! ";
			link.l1 = "这就是为什么你让你的狗攻击我? ";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "我们只是想翻你的口袋, 就这样! ";
			link.l1 = "让我在丛林里赤身裸体? 我应该把你绑起来, 吊在我船的最高桅杆上, 你这个恶棍! 但纯粹出于对那位不幸与你有牵连的善良女士的尊重, 我不会那样做。 你知道吗? 我应该把你带给她, 让她决定如何处理你。 ";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "不, 除了那个什么都行! 我不回库马纳! ";
			link.l1 = "你宁愿永远待在这个洞穴里? ";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "饶了我吧, 先生! 让我走, 我会从这里航行离开, 再也不回库马纳! 我不想等贝琳达的丈夫在决斗中把我切成碎片, 或者派刺客来杀我! ";
			link.l1 = "好吧。 为了德.里贝罗夫人, 我不会把你带给她。 但不要以为这一切都会被掩盖。 她会发现她决定调情的是个多么可悲的废物。 你有什么她能认出来的信物? ";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "给你。 这里的这个绿松石戒指。 是她亲自给我的。 ";
			link.l1 = "完美。 把它给我, 从我的视线中消失! ";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "完美。 你知道吗, 索萨, 我改变主意了 - 现在我为耶稣会服务。 正如圣经所说,'你必须从你们中间清除恶人.'而你是一个邪恶的自恋者, 一个罪犯, 一个无用的废物。 我想我会把你淹死在这个洞穴里。 安息吧。 ";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("你收到了一枚绿松石戒指");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// 如果没有佩戴手枪或步枪, 就发放制式武器 -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// < —legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("你收到了一枚绿松石戒指");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//打开地点
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//允许军官
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //打开遭遇战
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//允许战斗
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以移动时间
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// 猎人
		case "spa_hunter":
			dialog.text = "你有我们需要的东西, 伙计... ";
			link.l1 = "真的吗? 那会是什么? ";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "我没问, 富家子弟。 我只是奉命拿走你的财物, 你身上的一切。 我们是来软的还是硬的? 选择权在你。 ";
			link.l1 = "认为你是个战士, 嗯? 你根本不知道你在和谁打交道。 我把你这样的败类当早餐吃。 ";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "你是个真正的小丑, 不是吗, 法国佬? 那么, 让我们看看你的血在地上是什么样子! ";
			link.l1 = "它看起来和你的一样, 白痴。 让我给你上一堂解剖课! ";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "哈哈, 好吧, 伙计... 赶紧掏空你的口袋! 如果你是个好孩子并听话, 你会保持完整, 明白吗? ";
			link.l1 = "该死的, 又是你们这群人? 你们也一路来到这里? 到底谁雇了你们? ! ";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "与你无关。 现在投降并活着, 或者反抗, 我们只会从你尸体上拿走你的战利品。 这个交易怎么样? ";
			link.l1 = "我有一个反建议。 我从你尸体上拿走你的战利品怎么样? ";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// 登船队指挥官
		case "batabano_officer":
			dialog.text = "等待命令, 船长! ";
			link.l1 = "穿过丛林向圣安东尼奥角移动。 走左边的小径, 一直往前走。 保持低调, 准备在岸边伏击。 准备好。 我将从海上前往那里, 在那里与你会合。 你需要多长时间到达那里? ";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "我们将在六小时内到达, 船长! ";
			link.l1 = "好的。 行动! ";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// 在海角
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// 时间, 专门为不读对话和攻略的傻瓜
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// 帕特森的雇佣兵
		case "housemercen":
			dialog.text = "顽强的混蛋! 他还活着... 我就知道我们应该多用些火药! 好吧, 好吧, 我会解决你, 你这个狗娘养的... ";
			link.l1 = "... ";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			bDisableCharacterMenu = false;//解锁F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}