// 文森托神父
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "终于亲眼见到著名的法国船长" +GetFullName(pchar)+ "了。 我听闻了许多您的英雄事迹。 您是一位勇敢的战士, 我希望您也是我们神圣罗马天主教会忠诚而虔诚的儿子。 请坐, 我的孩子。 不必因为我而站着。 愿主与你同在! ";
				link.l1 = "也与你的灵魂同在, 大人。 我来此的道路漫长而艰辛... 历经磨难, 终达星辰... ";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "是的, 我从您眼中看出您有消息要告诉我。 我全神贯注听您说。 ";
				link.l1 = "大人, 我找到了您失踪的秘书... ";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "你给我带来圣何塞的消息了吗, 我的孩子? ";
				link.l1 = "是的, 大人。 我查明了我们共同的熟人米格尔.迪乔索和他失踪的护卫舰的遭遇。 他的船一进入前往西班牙的大西洋, 就立即被逆风卷入加勒比海。 ";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "愿平安与你同在, 我的孩子... 我能为你做什么? ";
				link.l1 = TimeGreeting() + ", 大人。 您有关于我们约定的消息吗? ";
				link.l1.go = "guardoftruth_17";
				break;
			}
			dialog.text = "你有什么事吗, 我的孩子? ";
			link.l1 = "不, 没什么, 神父。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'你们要从窄门进去; 因为引到死亡的门是宽的, 路是大的, 进去的人也多。 引到生命的门是窄的, 路是小的, 找着的人也少.'我的孩子, 正义之路总是艰难的。 但所成就的目标会充分回报正义之人的劳作。 ";
			link.l1 = "我同意, 大人。 我已完成您交给我的任务。 您已经抓到了从教会偷取珍贵器皿的懦弱海盗。 现在我把被拿走的所有东西都归还: 圣体匣。 十字架和香炉。 把它们交给圣地亚哥教区。 ";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "赞美主! 我从心底感谢您对圣母教会和圣地亚哥教区的忠诚服务, 我的孩子。 您的劳作不会没有回报。 教区居民为归还被盗物品的勇敢战士筹集了一份祭品, 我很高兴代表他们交给您.'工人得工价是应当的.'";
			link.l1 = "谢谢您, 大人。 真是个惊喜! ";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("你收到了一箱杜布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "对圣母教会的忠诚服务总是会得到忠诚的回报, " +pchar.name+ "。 我希望您能继续成为捍卫基督教世界的 dedicated 战士, 因为有一个致命的威胁像神话中的达摩克利斯之剑一样笼罩着我们。 ";
			link.l1 = "那会是什么, 大人? ";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "也许您注定要成为我们在即将到来的与这个世界黑暗势力战斗中的冠军, 我的孩子, 因为有许多迹象和预兆表明某种邪恶正在逼近。 ";
			link.l1 = "迹象和预兆? ";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "很多, 我的孩子... 其中之一是您渴望寻找异教塔亚萨尔失落的印第安黄金, 因为他们宝库中保存的东西正是对整个基督教世界构成威胁的东西。 ";
			link.l1 = "您能给我讲讲这些黄金吗, 尊敬的神父? 我已经听说过它消失的历史, 但您所说的是什么样的威胁? ";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "仔细听着, 我的孩子, 要知道你即将听到的一切只对你一人说。 在米格尔.迪乔索从那座古老的印第安城市取出那件异教宝藏之前很久, 我曾审问过一个伊察印第安人俘虏, 询问我们在加勒比海的使命。 伊察人是玛雅人的后裔, 玛雅帝国甚至在克里斯托瓦尔.哥伦布和他的人首次踏上新世界之前几个世纪就已失落。 玛雅帝国用铁腕统治周围的部落, 通过与恶魔的邪恶交易获得了难以言喻的力量。 用世代人类牺牲的鲜血换来的黑暗魔法。 \n这个伊察人知道塔亚萨尔, 一座失落的玛雅城市, 以及仍然封印在其中的难以置信的邪恶。 他告诉了我们他所知道的一切。 如果这些封印被打开, 后果将是世界末日。 从那一刻起, 我就尽我所能阻止这种可怕的邪恶被唤醒。 我绝望地写信给埃斯科里亚尔和罗马请求援助。 \n他们听取了意见, 派遣了唐.拉蒙.德.门多萨.里巴, 他在普罗维登斯建立了基地, 开始寻找塔亚萨尔。 就在那时, 我发现善良的唐.门多萨... 寻找失落城市的动机不同。 他不是为了阻止世界末日, 而是寻求侍奉玛门而不是基督。 \n这就是为什么上帝抛弃了他, 将死亡天使送入他的营地。 他的所有行动都是徒劳的, 只导致西班牙士兵和忠实的印第安皈依者无谓的死亡。 我写信给埃斯科里亚尔, 请求因严重无能解除拉蒙.德.门多萨的职务, 他们同意解除他的职务, 但是... ";
			link.l1 = "米格尔.迪乔索来了。 ";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "库库尔坎? ! 圣母玛利亚, 天主之母, 为我们祈祷! 又是库库尔坎, 那条老蛇... ";
			else sTemp = "嗯... ";
			dialog.text = "正是如此。 那个魔鬼派来的冒险家找到了塔亚萨尔以及古代玛雅人的宝藏。 然而, 唐.门多萨的喜悦是短暂的。 所有这些宝藏都随着迪乔索返回西班牙的途中消失了。 很可能, 米格尔除了所有的金锭和饰品外, 还带走了一个古老的邪恶源头, 一个名为库库尔坎的古代玛雅恶魔之神的可怕面具。 ";
			link.l1 = sTemp + "但您说的是什么邪恶, 大人? 您怎么知道的? ";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "这是一种会给加勒比海。 新世界甚至可能旧世界的所有受洗基督徒带来死亡的邪恶。 结局会像夜间的小偷一样到来, 没有人会意识到发生了什么。 而且这已经到处都是预兆了! ";
			link.l1 = "什么预兆? 我不明白... ";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "我的孩子, 您真的如此盲目, 甚至没有注意到它们吗? 它们已经持续了二十五年, 几乎没有停止过! ";
			link.l1 = "我想温和地提及, 大人, 我的生命历程正好是这个长度, 更不用说我大部分时间都在欧洲生活。 我的无知应该稍微被原谅。 ";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "我明白, " +pchar.name+ "。 现在, 您从欧洲来到这里后, 难道没有注意到加勒比海各地发生的奇怪事情吗? 您不觉得奇怪吗, 巫术。 黑魔法和其他仪式在这里比在老家强大得多? 印第安萨满附魔的异教护身符拥有任何人只要持有就能体验到的真正力量。 \n甚至我们的基督教炼金术士 —愿上帝让他们看到自己的错误! —已经掌握了制作附魔物品的艺术。 他们没有意识到这样做是在为魔鬼本身服务。 您没有感觉到某种地狱般的存在潜伏在您的视野之外吗? ";
			link.l1 = "您说得对, 神父。 起初我对此感到惊讶, 但现在我想我已经习惯了... 毕竟这是新世界! ";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "但并非一直如此。 我所说的黑暗大约在二十五年前来到这里, 并且每天都在获得越来越多的力量。 这意味着只有一件事:'它'已经来了,'它'在我们中间, 并且'它'在起作用... ";
			link.l1 = "您在说谁? 这个神秘的'它'是谁? ";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "基督徒的 sworn enemy, 渴望摧毁教会和整个基督教世界。 ";
			link.l1 = "... 您是在说敌基督吗? ";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "无论是'那个'敌基督还是'一个'敌基督, 我不敢说。 当这头野兽穿上凡人的肉身, 怪诞地模仿我们救世主的道成肉身时, 它叫什么名字并不重要。 重要的是它要做什么。 我来这里是为了阻止它, 而您要帮助我。 但我们有点忘乎所以了。 您是个行动派。 您可能更愿意着手工作, 跳过神学, 对吗? ";
			link.l1 = "相反, 我从您这里了解到了很多新的重要事情, 大人。 我准备继续听下去。 ";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "您很有礼貌, 教养良好, 我的孩子。 那很好。 现在回到您与我商谈的原因。 我们的共同目标是找到迪乔索带走的塔亚萨尔宝藏。 我们可能会在这些宝藏中找到一种武器, 用于即将到来的与魔鬼的战斗。 ";
			link.l1 = "但迪乔索可能已经离开加勒比海, 在西班牙坐在一堆金子上了? ";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "不。 我有证据表明这些宝藏仍在加勒比海。 您现在不需要知道我的消息来源, 您必须相信我。 此外, 我认为迪乔索在对男爵撒谎。 \n他关于塔亚萨尔废墟的故事与我审问的伊察印第安人告诉我的不符。 更不用说迪乔索作为蚊子伏击的唯一幸存者, 这有点太方便了。 ";
			link.l1 = "我想唐.门多萨也这么认为, 因为他突袭圣皮埃尔试图找到迪乔索? ";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "我的孩子, 男爵的行为不应该让您担心。 他只被对黄金和个人利益的欲望所驱使。 当周围善良的基督徒男女都在与地狱的力量交战时, 他的贪婪将成为他脖子上的磨石。 ";
			link.l1 = "您有什么线索可以让我们寻找迪乔索和宝藏吗? ";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "我每分钟都在想这个问题, 我的孩子, 但我没有具体的事情可以告诉您。 但这里有一个人会帮助我们, 一位来自热那亚的自然哲学家。 我带他来这里帮助分类新世界中可能对教会使命有用的东西。 他目睹了对伊察印第安人的审讯, 根据我的判断, 他所听到的事情震惊了他, 并反常地吸引了他。 \n魔鬼利用他的好奇心像带饵的狼钩一样, 占据了他的身体和灵魂。 主赐予了他在医学和炼金术方面的巨大能力, 但我们的热那亚人陷入了黑魔法和巫术的诱惑。 他未经我的允许与我俘虏的伊察人谈过几次, 然后就消失了。 我们必须找到他并拯救他的灵魂。 ";
			link.l1 = "我想我应该去找他? ";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "是的, 我的孩子。 他是找到宝藏和我们可以用来对抗威胁我们的邪恶力量的武器的第一步。 ";
			link.l1 = "这个热那亚人是谁? ";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "他的名字是吉诺.格维内利。 三十岁左右, 上下差几岁。 一位有才华的医生和炼金术士。 正如我所说, 现在他研究黑魔法。 根据我的最佳情报, 他藏在加勒比海的英国殖民地某处。 \n找到吉诺.格维内利, 我的孩子。 如果您能找到那个偷我们教堂器皿的海盗, 那么您也能找到我逃跑的秘书并把他带到这里。 我会祈求圣安东尼为您代祷。 ";
			link.l1 = "我明白了, 大人。 我不会再浪费一分钟。 回头见! ";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "我几乎因惊讶的呼喊而暴露自己。 文森托神父命令我找到并带给他他逃跑的秘书, 一位名叫吉诺.格维内利的医生炼金术士。 就是那个住在圣约翰我家二楼空房间里的吉诺! ");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "我必须找到一个名叫吉诺.格维内利的人, 藏在加勒比海的英国殖民地某处。 他是一名医生和炼金术士。 像他这样的人能藏在哪里? ");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "我完全相信您会这么说, " +pchar.name+ "。 现在我的信心因确信您是由神圣天意亲自派给我的而进 一 步增强。 我那可怜的浪子在哪里? ";
			link.l1 = "恐怕您不会喜欢即将听到的话, 但我别无选择。 您的秘书死了。 ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "愿上帝拯救他的灵魂并宽恕他的罪孽... 这是怎么发生的, 我的孩子? ";
			link.l1 = "我在安提瓜找到了吉诺。 他藏在实验室下面的一栋旧建筑里。 他不愿意安静地跟我来。 听到您的名字并看到我准备使用武力后, 他从长袍的褶皱里拿出一个透明液体的小瓶, 瞬间喝了下去... ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "然后发生了可怕的事情: 他变红了, 然后变成深蓝色。 他倒在地板上抽搐, 一分钟后在可怕的痛苦中死去。 房间里充满了强烈的杏仁味。 ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "吉诺... 你这个可怜的傻瓜... 他甚至在生命的最后一分钟还在犯罪, 自杀了。 多么悲惨的损失。 我会为他的灵魂祈祷... ";
			link.l1 = "他死后, 我搜查了他的住所, 在那里找到了这个对开本。 它可能对您有兴趣或帮助我们寻找吗? 这里有一些奇怪和深奥的笔记... ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("你给了年鉴");
			PlaySound("interface\important_item.wav");
			dialog.text = "这是可怜的吉诺的年鉴。 他在里面记录了他所有的探索笔记。 把它给我, 我的孩子, 我会研究里面写的内容。 也许我们会找到线索。 \n虽然您没有把吉诺.格维内利送回给我, 但我对您的努力感到满意, 我的孩子。 现在我有消息要告诉您。 ";
			link.l1 = "我听着, 神父。 ";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "我获得了情报, 特立尼达岛是最后一次看到迪乔索护卫舰的地方。 我也知道一个大概时间 —1654年4月初。 \n去特立尼达, 试着了解这艘护卫舰的命运: 她要去哪里, 船长有什么计划, 任何您能找到的信息。 我知道时间已经很久了, 人们的记忆有限, 但溺水的人会抓住稻草。 ";
			link.l1 = "我会尽我所能。 ";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "让我看看您的安全通行证。 我会添加允许您访问圣何塞殖民地的许可。 ";
			link.l1 = "给您。 ";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "好了... 就这样。 别忘了在您的船上悬挂西班牙国旗。 向前来接受上帝的祝福, 我的孩子! ";
			link.l1 = "等一下, 大人。 我可以问您一个问题吗? ";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "是的, 当然。 您想知道什么? ";
			link.l1 = "在我们上次见面时, 您谈到了一个告诉您塔亚萨尔的伊察印第安人。 我想了很多... 告诉我, 那个人身上有什么东西吗? 某种物品。 文字或类似的东西? 这可能被证明是有用的。 ";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "没有特殊物品, 我的孩子。 一块腰布。 原始珠宝。 一个装有一些草药的竹管, 以及一块用作 gag 的粗糙皮革。 \n所有这些都被送给了唐.拉蒙.德.门多萨.里巴。 但我向您保证, 没有什么值得关注的。 ";
			link.l1 = "我明白了。 谢谢您, 神父。 下次见! ";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "愿全能的上帝保佑您, 保守您... 米格尔.迪乔索怎么样了? 您查明了吗? ";
			link.l1 = "唉, 没有。 目击者能告诉我的最后一件事是圣奎特利亚号被大风吹向马提尼克岛方向。 不知道这艘船是得救了还是沉没了。 但我怀疑米格尔.迪乔索活了下来。 ";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "您为什么这么认为, 我的孩子? ";
			link.l1 = "关键是这艘护卫舰藏在马提尼克岛方向的某个地方。 最近, 一位名叫迭戈.德.蒙托亚的勇敢绅士, 他自己就是唐.拉蒙.德.门多萨的人, 袭击了圣皮埃尔, 目的是找到据说藏在那里的米格尔.迪乔索。 ";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "所以, 男爵认为迪乔索和法国人一起躲藏... ";
			link.l1 = "我很了解圣皮埃尔和总督雅克.迪耶尔.迪.帕凯, 大人。 那里没人认识一个叫米格尔.迪乔索的西班牙人。 您能告诉我如何找到迭戈.德.蒙托亚吗? 我想和他谈谈迪乔索。 ";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "您确定他愿意和您说话吗, 我的孩子? 我认为他不会, 除非您用剑和手枪交谈。 ";
			link.l1 = "也许您的名字会让他更愿意? ";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "哦, " +pchar.name+ "。 我怀疑唐.门多萨的 sworn man 会愿意与您达成协议。 命令他到圣迭戈来听我审问可能是一个选择, 但我也不确定迭戈会对我完全真诚。 ";
			link.l1 = "我们现在该采取什么行动, 神父? ";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "离开我一会儿, 我的孩子。 我需要处理您告诉我的事情, 并将我已经从各种渠道了解到的所有事实整合起来。 之后我会告诉您我们的下一步行动。 稍后再来。 ";
			link.l1 = "好的, 大人。 会的。 我会定期来查看... ";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "愿上帝保佑您, 我的孩子... 我能为您做什么? ";
			link.l1 = "您有什么消息吗, 大人? ";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "目前没有, 我的孩子。 但不要绝望。 我和我的人正在努力。 稍后再来。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "是的, 我的孩子。 我有一些关于米格尔.迪乔索的信息。 我相信迪乔索仍在加勒比海并且活着不是没有根据的。 看来唐.迭戈.德.蒙托亚是对的。 我们从一个认识米格尔.迪乔索的人那里得到了证据, 在圣奎特利亚号失踪后的1654年4月, 有人在马提尼克岛的海盗定居点勒弗朗索瓦看到了这位失踪的绅士... ";
			link.l1 = "那么, 这艘护卫舰在马提尼克岛海岸沉没了? ";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "慢点, 我的孩子。 我们现在没有任何关于当时马提尼克岛有船只失事的信息。 而护卫舰不是小帆船。 它的毁灭肯定会引起一些注意, 并为当地的食腐者创造大量的打捞机会。 ";
			link.l1 = "是否值得搜索海岸线和海滩, 以找到船只的残骸? ";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "我的孩子, 唐.迭戈.德.蒙托亚已经做了所有这些, 没有结果。 继续听着。 我在普罗维登斯的消息来源报告说, 男爵确信圣奎特利亚号仍在加勒比海航行, 尽管换了个名字。 \n这就是为什么他如此拼命地追捕米格尔.迪乔索。 根据他的说法, 圣奎特利亚号在宝藏岛附近被看到, 最近在英国国旗的护送下被一支军事中队看到。 ";
			link.l1 = "什么? 这难以置信。 他们说承受如此规模的风暴是不可能的... 现在圣奎特利亚号不仅幸存下来, 而且现在在英国国旗下航行? 这两个事实不符。 是什么让男爵认为那是圣奎特利亚号? 她真的是如此独特的船吗? ";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "哦, 是的。 这艘护卫舰是用欧洲最新技术建造的。 她在她的级别中装备精良, 她的速度让她能逃脱任何可能比她火力更强的船只。 这是我的消息来源告诉我的。 ";
			link.l1 = "如果不是圣奎特利亚号, 她现在叫什么? ";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "不幸的是, 我不知道... 去宝藏岛, " +pchar.name+ ", 试着了解一些关于迪乔索护卫舰的事情。 我们也可能通过这种方式找到她的前船长, 一举两得。 或者一陷阱抓两只老鼠。 ";
			link.l1 = "考虑到了, 大人! ";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// 检查鲨鱼是否活着以及在哪里, 如果活着
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // 一点娱乐
		break;
		
		case "tieyasal":
			dialog.text = "我很高兴您决定来看我, 我的孩子。 ";
			link.l1 = "您好, 大人。 在与唐.阿隆索.德.马尔多纳多会面后, 我甚至没想到会再见到您。 ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "唐.阿隆索.德.马尔多纳多违反了我的直接命令。 我严格禁止他与您对抗, 我的孩子, 我知道这对他来说会有什么结果。 我所预见的已经成真。 他的任务是护送您到塔亚萨尔, 因为他以前去过那里。 \n除此之外, 他的中队和一队西班牙士兵应该保护您免受伊察或蚊子的攻击。 阿隆索被自私的复仇欲望所驱使, 行为不当。 \n他不仅使塔亚萨尔探险失败, 使托付给他的士兵和船只陷入绝境, 还在您心中种下了对我不信任和怨恨的种子。 我向您保证, 我的孩子, 我完全站在您这边。 我们必须共同对抗当前的黑暗。 ";
			link.l1 = "我愿意相信。 ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "放心, " +pchar.name+ "。 我, 作为我们主和救主耶稣基督的忠诚和 dedicated 仆人, 以及他教会的代表, 动机只有一个: 阻止世界末日的到来, 直到所有灵魂都有机会听到我们神圣主的话语。 这意味着阻止目前在 一 个被恶魔附身的印第安人手中的邪恶代理人。 我一开始就怀疑这一点, 现在我完全确定了。 您已被主选为他对抗撒旦战斗中的冠军。 ";
			link.l1 = "但您为什么这么说, 神父? ";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "您已经做到了一些事情, 无论是我和我所有的代理人, 还是门多萨男爵和唐.迭戈, 或者其他任何人都未能做到的。 您成功找到了那个该死的岛屿, 并在上面寻找库库尔坎的神器。 不是吗? ";
			link.l1 = "是的, 我有库库尔坎的面具。 ";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "您会声称这一切都是偶然发生的吗? 纯属巧合?'人心筹算自己的道路, 惟主指引他的脚步.'我的孩子, 全能的上帝引导您走上了这条道路! 他在战斗中坚固了您的手, 指引您的脚走正确的道路, 并在危险时刻保护了您!'看哪, 主的剑降下来要审判以东, 就是我所咒诅的民!'";
			link.l1 = "嗯... 神父, 但任务基本上已经完成了。 我有面具。 这是否意味着库库尔坎被附身的外壳不能进入我们的历史并改变它... ? ";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "您错了, 我的孩子。 无论有没有这个面具, 恶魔都可能穿过那扇门。 面具只是让他更容易执行他的黑暗行为。 唯一能阻止他的是彻底摧毁地狱之门。 ";
			link.l1 = "唐.阿隆索也这么告诉我... ";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "他是对的! 以我们主耶稣基督和他神圣母亲的名义, 我召唤您拿起十字架对抗这种邪恶, 我的孩子! 您不能拒绝降临在您身上的伟大使命。 我和整个基督教世界都依赖您, 我的孩子。 ";
			link.l1 = "大人, 这太多了。 我真的觉得... 有点尴尬... ";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "您的谦虚是合适的, 我的孩子, 但现在不是扮演害羞处女的时候。 不要胆怯或害怕, 因为主你的上帝在你前面给你胜利! 为了您所爱的人, 为了所有基督徒... 如果不是为了他们, 也是为了您自己, 因为如果那个恶魔获胜, 您将和其他人一起灭亡。 ";
			link.l1 = "我想您已经说服了我, 神父。 我曾犹豫是否要向塔亚萨尔发起十字军东征, 但现在我不再有任何疑虑。 您能帮我什么? ";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "只有两个人知道如何到达塔亚萨尔: 阿隆索.德.马尔多纳多和米格尔.迪乔索。 唐.阿隆索死了。 而迪乔索... 他们告诉我最近在宝藏岛的夏普敦看到了他。 也许他还在那里。 您必须找到迪乔索并说服他做您的向导。 \n通过金钱或武力, 您必须让这个人带您到塔亚萨尔。 在那里您会找到地狱之门, 在那里您将封印它们。 ";
			link.l1 = "那人员呢? ";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "我最后的一营士兵由阿隆索.德.马尔多纳多指挥。 唉, 我没有机会再召集另一队西班牙士兵了。 我已经用完了与当地驻军的所有信誉。 您必须用您自己的人来做, 我的孩子。 但我会在其他方面给您我能给的帮助。 ";
			link.l1 = "什么样的帮助? ";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "在这场战斗中, 我们必须利用我们拥有的每一个优势, 无论是物质上的还是精神上的。 我已请求阿德里安神父五天后到这个教堂来见我。 他会给您带来神圣的护身符。 这些护身符可以帮助基督的战士在战斗中。 他还会为您提供各种药水。 至于我, 接受这把剑, 我的孩子。 \n这是圣殿骑士的一把古老宝剑, 我们祖先的 formidable 武器。 仍然锋利, 并闪耀着教会的祝福。 只有最伟大的骑士才有荣誉挥舞它。 拿着它, 自豪地拥有它, 用你口中的耶稣基督之名粉碎我们信仰的敌人! ";
			link.l1 = "谢谢! 这把剑绝对令人惊叹。 我无话可说... ";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("你收到了塔纳思");
			PlaySound("interface\important_item.wav");
			dialog.text = "愿上帝保佑你, " +GetFullName(pchar)+ ", 在这场即将到来的战斗中。 我用圣十字为你祝福。 全能的上帝, 胜利在你手中, 你也赐给大卫奇迹般的力量来粉碎歌利亚: 我们谦卑地祈求你的怜悯, 通过你赋予生命的怜悯来祝福这些武器; 并赐给愿意携带它们的仆人" +GetFullName(pchar)+ ", 使他可以自由而胜利地使用它们, 捍卫圣母教会免受所有可见和不可见敌人的攻击。 通过我们的主基督。 阿门。 ";
			link.l1 = "阿门! ";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "现在离开吧, 我的孩子。 愿上帝看顾你, 愿他永不离开你, 无论是在你的搜索中, 在你的道路上, 还是在战斗中。 寻找米格尔.迪乔索, 并在他的帮助下前往塔亚萨尔。 不要忘记阿德里安神父, 他会为你配备任何你可能需要的护身符和药物。 现在我该返回圣地亚哥了。 再见, 我的孩子。 愿主与你同在。 ";
			link.l1 = "再见, 文森托神父... ";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}