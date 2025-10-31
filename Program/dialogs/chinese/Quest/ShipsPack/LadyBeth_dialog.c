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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "你的决定是什么, 船长? 也许我们不该这么做? ";
				link.l1 = "你设法为任务召集更多志愿者了吗? ";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "船长, 有句话要说。 ";
				link.l1 = "报告, 阿隆索。 ";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "船员们想知道你对开曼岛的计划。 大家都很担心。 ";
			link.l1 = "我还没决定。 阿隆索, 为什么大家会担心? ";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "这个岛是布莱克伍德船长的地盘。 水手们说他像着了魔一样在岛上四处挖掘, 据说他在挖掘过程中毁了几十个人... 而那些离开他的人... 会讲述一些奇怪的故事。 ";
			link.l1 = "什么样的故事? ";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "说布莱克伍德不再是以前的他了, 他痴迷于寻找西班牙征服者的宝藏, 为了宝藏准备牺牲一切和所有人。 我们知道你有多喜欢陷入精彩的故事里, 独自登陆然后掉进陷阱... 但这次你逃不掉的。 ";
			link.l1 = "谢谢你的报告和警告。 如果我决定登陆, 一定会带上先头部队和我们最优秀的战士分队。 ";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "这可能很困难, 船长。 登船是一回事, 但在海军陆战队的子弹和据说布莱克伍德从背风群岛各个角落雇来的乌合之众的军刀下登陆完全是另一回事。 而且关于开曼岛有不好的传言... 不, 这种任务不会有很多志愿者。 ";
			link.l1 = "那我们只能凑合着用能找到的人了。 阿隆索, 你必须参加。 ";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "在我看来, 我已经向所有人证明了一切能证明的。 所有优秀的战士和射手都会去。 这是命令。 ";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "嗯... 我需要好好想想。 也许我们稍后再讨论这个问题。 ";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "是, 船长! ";
			link.l1 = "布莱克伍德的船怎么办? 不会有问题吗? ";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40 || sti(pchar.rank) >= 12)
			{
				dialog.text = "是, 船长! ";
				link.l1 = "布莱克伍德的船怎么办? 不会有问题吗? ";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40) Notification_Skill(true, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) >= 12) Notification_Level(true, 12);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "恐怕还不行, 船长。 ";
				}
				else
				{
					dialog.text = "你不必向我或其他军官证明什么, 我们会按命令前往你指示的任何地方, 但普通水手有不同的想法。 恐怕会有问题, 船长。 ";
				}
				link.l1 = "那我们只能凑合着用能找到的人了。 阿隆索, 你必须参加。 ";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "嗯... 我需要好好想想。 也许我们稍后再讨论这个问题。 ";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 40) Notification_Skill(false, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) < 12) Notification_Level(false, 12);
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "一艘雪帆船。 他们说那是艘真正的美人儿, 脾气也很烈。 我不担心她。 很可能全体船员都在岸上苦干, 而船安全地藏在海岸线的褶皱里。 如果我们赢了, 之后可以从岸上把她当作战利品。 ";
			link.l1 = "召集人手。 今天是个好日子 —幸运会站在我们这边。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// 在酒馆与布莱克伍德的对话
		case "LadyBeth_DialogInCity": // 主菜单
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "很高兴见到你, 船长。 我想我们已经讨论过所有事情了。 ";
				link.l1 = "确实。 再见。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "... ";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "... ";
				link.l1 = ""+TimeGreeting()+", 布莱克伍德船长。 ";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "... ";
				link.l1 = "你好。 你是布莱克伍德船长吗? ";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "... ";
				link.l1 = ""+TimeGreeting()+"。 你是阿尔伯特.布莱克伍德船长, 对吗? ";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // 重复对话
			dialog.text = "很高兴见到你, 船长。 我想我们已经讨论过所有事情了。 ";
			link.l1 = "确实。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // 首次对话
			dialog.text = "是的, 是我。 你是? ";
			link.l1 = "我是"+GetFullName(pchar)+"船长。 我指挥'"+PChar.Ship.Name+"'号船。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "船长... 你去过开曼岛吗? ";
			link.l1 = "只是路过。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "你听说过那里的宝藏吗? ";
			link.l1 = "没有, 没什么具体的。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "西班牙人的踪迹? 古老的武器? 征服者时代的硬币? ";
			link.l1 = "没找到过那样的东西。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "当地传说? 关于科尔特斯的故事? 任何关于埋葬的事情? ";
			link.l1 = "抱歉, 船长, 但我没有这样的信息。 而且这已经开始像审讯了。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "我道歉... 以前军官的坏习惯。 只是... 这对我极为重要。 ";
			link.l1 = "你为什么特别对开曼岛感兴趣? ";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "这不重要。 再次道歉。 ";
			link.l1 = "我明白。 祝你搜索顺利。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "晚安";
			else sStr = "祝你今天愉快";
			dialog.text = "如果你找到任何有价值的东西, 来见我。 我很乐意与另一位船长交谈... 与懂海的人。 " + sStr + "。 ";
			link.l1 = ""+Goodbye(true)+"。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // 与海伦的首次对话
			dialog.text = "正是本人。 而你... 海伦.麦克阿瑟船长? 扬.斯文森的门生, 对吗? 我听说过你。 ";
			link.l1 = "你消息很灵通, 布莱克伍德船长。 但英国军官知道我并不奇怪。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "以前的军官。 所有穿红衣的人都知道你和你... 对王室的独特偏好。 正如他们所说, 铁石心肠闻不到味道。 而你父亲肖恩.麦克阿瑟从小带你出海并把你培养成船长的故事, 在舰队里已经成了传奇。 ";
			link.l1 = "见到这个传奇是什么感觉? ";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "我个人印象深刻。 不过我必须承认, 我的许多以前的同事觉得这相当恼人。 但要成为船长, 需要的不仅仅是高贵的出身或王室许可证, 不是吗? ";
			link.l1 = "没错。 需要知识。 经验和不断准备证明自己的能力。 尤其是在我这种情况下。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "正是! 在海上, 如同在生活中, 重要的不是头衔, 而是结果。 很高兴认识你, 麦克阿瑟船长。 希望我们能再见面。 也许等我探险回来, 你能来喝杯酒? ";
			link.l1 = "也许吧。 祝你搜索顺利, 船长。 ";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "没兴趣。 但祝你搜索顺利, 船长。 ";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // 第二次对话
			dialog.text = "啊, "+pchar.lastname+"船长! 很高兴见到你。 你想坐吗? ";
			link.l1 = "荣幸之至。 ";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "船长... 告诉我, 真正的宝藏对你意味着什么? ";
			link.l1 = "真正的宝藏是爱。 身边有对的人。 没有什么比孤独更糟糕的了。 ";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "当然是金钱。 不然还能是什么宝藏? ";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "有价值且独特的装备。 一把好剑或手枪比黄金更有价值。 ";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "知识。 最有价值的宝藏是头脑中的东西。 ";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "爱? 嗯... 没想到海盗的女儿会给出这样的答案。 我... 我曾订过婚。 和伊丽莎白。 巴巴多斯一个种植园主的女儿。 但她父亲... 他认为我钱不够。 除了我的爱, 我还能给她什么? 你很幸运, 麦克阿瑟船长。 你有一个更看重你能力而非嫁妆的父亲。 ";
				link.l1 = "也许这不是运气, 而是真正的爱不是用黄金衡量的。 我父亲明白这一点。 你的未婚妻呢? 她也认同父亲的观点吗? ";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "爱? 是的... 也许你是对的。 我... 我曾在巴巴多斯订过婚。 我们彼此相爱, 但... 她父亲认为我配不上。 哈! 不够富有。 这就是我在这里的原因 —寻找宝藏来证明他们都错了。 也许这是徒劳的? ";
				link.l1 = "也许你应该直接和她谈谈? 去他的种植园主。 ";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "谈谈... 是的, 也许。 但我该说什么? ‘对不起, 我无法给你体面的生活’? 不。 我必须作为赢家回来。 否则就不回来。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "伊丽莎白? 不... 她爱我。 但我... 我不能让她过贫穷的生活。 她值得更好的。 而我必须证明我配得上她。 ";
			link.l1 = "有时骄傲比贫穷更阻碍幸福, 船长。 ";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "我不能空手而归。 我就是不能。 抱歉, 我有很多工作要做。 和你聊天很愉快, 麦克阿瑟船长。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "多么平庸的答案。 但很难反驳。 确实, 当你在布里斯托尔的贫民窟长大, 当你不得不为残羹冷炙而奋斗... 你就会开始理解金钱的真正价值。 不是奢侈, 而是自由。 是永远不必再回到你艰难爬出的那个泥潭的能力。 ";
			link.l1 = "我同意。 金钱解决大多数问题。 如果解决不了 —说明钱还不够。 ";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "正是! 你明白。 金钱不会让你幸福, 但缺钱肯定会让你不幸福。 我太清楚这一点了... ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "有趣。 实用。 我有一把火绳枪... 真正的, 征服者时代的。 一位神父送的礼物。 有时我觉得它比我找到的所有黄金都值钱。 但是... 它解决不了我的问题。 ";
			link.l1 = "好武器能解决很多问题。 而且它们永远不会背叛你。 ";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "这话有道理。 但有些战斗无法用武力取胜。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "知识... 是的, 我明白。 我研究了所有能找到的关于征服者和宝藏的资料。 我编写了一整本寻宝手册。 为船上的步枪连设计了定期训练和物质奖励制度。 任何船长都会很高兴得到我的手册。 但所有这些知识... 如果不能带来结果, 就毫无用处。 要真正的结果。 ";
			link.l1 = "但知识正是帮助实现结果的东西。 没有知识, 任何搜索都只是在黑暗中徘徊。 ";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "嗯, 已经很晚了, 我还有很多工作要做";
			else sStr = "嗯, 我有很多工作要做";
			dialog.text = "" + sStr + "。 谢谢你的谈话, 船长。 真的很有趣。 ";
			link.l1 = "我也谢谢你。 "+Goodbye(true)+"。 ";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // 第三次对话
			dialog.text = "啊, "+pchar.name+"! 很高兴见到你。 我有个好消息 —我终于找到解决问题的办法了。 很快我就要出发探险, 这次我会带着真正的宝藏回来! 顺便说一句, 友好建议 —远离开曼岛。 现在它是我的地盘了。 ";
			link.l1 = "开曼岛不属于你, 阿尔伯特。 你没有王室对它的权利。 这是海盗行为。 ";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "你在威胁我吗, 布莱克伍德? ";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "王室权利? 你应该在布里斯托尔的贫民窟生活过, "+pchar.name+", 然后你就会明白这些文件有什么价值。 当你饥饿时, 法律毫无意义。 不过... 你是对的。 正式来说, 我对这个岛没有权利。 但我在那里找到了我多年来寻找的东西。 我不会让任何人夺走它。 ";
			link.l1 = "我希望你明白你在走一条危险的路。 ";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "我一直明白我的路不会容易。 再见, "+pchar.name+"。 也许我们会再见面。 ";
			link.l1 = ""+Goodbye(true)+"。 ";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "威胁? 不, 完全不是。 只是一位船长给另一位船长的友好建议。 开曼岛很危险... 尤其是对那些干涉我事务的人。 ";
			link.l1 = "我会记住你的‘建议’。 祝你在开曼岛好运。 ";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "也祝你好运, 船长。 希望你用不上。 再见。 ";
			link.l1 = ""+Goodbye(true)+"。 ";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// 陷阱, 船舱内的登船突袭
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "是你? ! 以为我会投降? 以为我会回到贫穷? 我宁愿死也不愿再在贫民窟里挨饿! 没有怜悯, 没有奖励, 没有胜利! 铺位下面有个火药桶... 我们一起沉下去! ";
				link.l1 = "... ";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "你是谁, 竟敢攻击我? ! 以为我会投降? 不! 我宁愿死也不愿再在贫民窟里挨饿! 没有怜悯, 没有奖励, 没有胜利! 铺位下面有个火药桶... 我们一起沉下去! ";
				link.l1 = "... ";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// 布莱克伍德在开曼岛战斗前与主角对话
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "船长! 我警告过你。 现在你要为你的好奇心付出代价。 ";
			}
			else
			{
				dialog.text = "你是谁, 竟敢入侵我的领地? ! 这个岛是我的! ";
			}
			link.l1 = "我们走着瞧, 布莱克伍德。 今天这个世界上会少一个痴迷的人。 ";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "我们和平解决吧, 布莱克伍德。 我可以离开。 ";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "布莱克伍德, 你是个理智的人! 你是名军官! 看在上帝的份上, 你的营地上飘扬着王室旗帜! 我们不能达成协议吗? ";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "痴迷? 哈! 我只是个知道自己想要什么的人! ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "离开? 在你看到这些之后? 不, 不, 不! 不能让任何人知道我在这里找到的东西。 任何人! ";
			link.l1 = "我向你保证我不会告诉任何人。 我以船长的荣誉发誓。 ";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "这个世界上没有荣誉, 船长。 只有肮脏。 贫穷和蔑视。 我很遗憾, 但你必须死在这里。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "我想过。 想了很多。 并意识到 —这是我唯一的机会。 要么我找到科尔特斯的黄金, 要么... 一无所有。 明白吗? 一无所有! 我不会回到以前的生活! 不会回到肮脏和贫穷! 宁愿死在这里! ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "战斗吧! 布洛克, 弗雷泽 —如果他们靠近就开火! 霍普金斯, 冲锋! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// 与军官们的对话
		case "LadyBeth_Helena_1": // 海伦
			dialog.text = "你没事吧? ";
			link.l1 = "是的, 一切都好。 你呢? ";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "还活着。 但这些陆战不适合我。 给我脚下的甲板, 我能撕裂任何船只, 但在这里... 奇怪的地方。 让一百个海狼上岸, 挥舞鹤嘴锄, 建造防御工事... 我做不到。 ";
			link.l1 = "布莱克伍德知道如何激励他的船员。 ";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "我在蓝菲尔德就听说过他。 许多英国水手都尊敬地谈论他。 舰队中最优秀的军官, 辉煌的职业生涯... 然后他突然放弃一切去寻宝。 ";
			link.l1 = "你怎么看他? ";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "我认为布莱克伍德的例子清楚地表明了我们... 我是说你, 对... 你的手下所承担的责任。 求你了, 不要成为他那样的船长。 ";
			link.l1 = " 我会努力, 海伦。 ";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "谢谢你, 我的船长。 我知道你会成功的。 ";
			link.l1 = "我们会的。 ";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "我们会的。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			ReturnOfficer_Helena();
		break;
		
		case "LadyBeth_Mary_1": // 玛丽
			dialog.text = "查尔斯... 这里太可怕了。 ";
			link.l1 = "你没事吧, 玛丽? 你表现得像个真正的士兵。 ";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "不, 我不好, 真的。 看看这些人! 他们工作到精疲力尽, 生活在饥饿中, 死于疾病... 为了什么? 为了可能根本不存在的黄金。 ";
			link.l1 = "布莱克伍德相信它在这里。 ";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "这件红外套... 和我的一模一样。 一名英国军官... 你知道, 我突然想起了我的父母, 真的。 关于我的根... 关于我从未知道的事情。 也许我也是其中之一? ";
			link.l1 = "其中之一? ";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "那些寻找可能不存在之物的人。 然后在寻找中迷失自我。 我... 我想以后再谈这个, 真的。 等我们离开这个可怕的地方。 ";
			link.l1 = "当然, 玛丽。 ";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "先把他埋了, 好吗? 即使他不值得。 为了他曾经的样子。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			ReturnOfficer_Mary();
		break;
		
		case "LadyBeth_Tichingitu_1": // 蒂钦吉图
			dialog.text = "船长, 蒂钦吉图看到这里是个坏地方。 非常坏的地方。 ";
			link.l1 = "你是什么意思? ";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "这个岛现在被诅咒了。 土地吸收了太多的血和泪。 每个在这里挖掘的人, 都在呼吸这个诅咒。 ";
			link.l1 = "你认为布莱克伍德被附身了? ";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "不只是被附身。 他是... 怎么说... 空容器。 有东西进入他身体, 挤出了他的灵魂。 我以前见过。 当我部落的萨满向神灵献上人祭时。 那个萨满就有同样的眼神。 ";
			link.l1 = "但什么会导致这种痴迷? ";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "内心空虚的人很容易被其他想法填满。 有人发现了他的弱点并利用了它。 蒂钦吉图几乎为这个人感到难过。 ";
			link.l1 = "几乎? ";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "是的, 几乎。 每个战士都要为自己的选择负责。 即使有恶魔在他耳边低语。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			ReturnOfficer_Tichingitu();
		break;
		
		case "LadyBeth_Irons_1": // 汤米
			dialog.text = "该死的, 船长! 看看这个! 就像过去的好日子! ";
			link.l1 = "你很清楚陆战是什么样的。 ";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "让我想起纳斯比战役。 我们的骑兵翼与鲁珀特的骑兵交锋。 他们为他们的国王战斗得同样凶猛。 ";
			link.l1 = "你怎么看布莱克伍德? ";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "这个布莱克伍德要么是个天才, 要么是个彻底的疯子。 我认为两者都是。 你知道什么让我惊讶吗? 他的人。 他们很多是以前的军人。 不是街头混混, 而是真正的军人。 他们都跟着他陷入了这种疯狂。 甚至福克斯的海军陆战队。 哈! 有人会为今天的屠杀感到高兴! 他从未原谅他们开小差。 ";
			link.l1 = "也许是为了钱? ";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "不, 还有别的。 这个人对他们有影响力。 真正的影响力。 我还听说他和巴巴多斯某个富家女订了婚。 奇怪的是, 他找到所有这些宝藏后却没娶她。 典型的军人 —不知道何时结束战争。 ";
			link.l1 = "谢谢你, 汤米。 你真是个思想家。 ";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "嗯? ";
			link.l1 = "没什么。 ";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			ReturnOfficer_Irons();
		break;
		
		case "LadyBeth_Knippel_1": // 克尼佩尔
			dialog.text = "看到这个多痛苦啊, 船长。 我们沦落到什么地步了? ! ";
			link.l1 = "我们? ";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "英国舰队! 看看: 小红点躺在这堆死人堆里! ";
			link.l1 = "有些‘人渣’是我们的人, 查理。 我理解你的感受, 但是... ";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "去他的, 先生! ";
			link.l1 = "我理解你的感受, 但你最好把愤怒和失望指向布莱克伍德。 是他从你心爱的英国舰队开小差, 把他们带到了这里。 ";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "确实。 我们走, 今天还没结束。 ";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "他们只是在服从指挥官! ";
			link.l1 = "就像你服从弗利特伍德一样? ";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "确实。 我们走, 今天还没结束。 ";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "就像我服从你一样! ";
			link.l1 = "我希望我能证明自己是比布莱克伍德和弗利特伍德更好的船长。 我们走, 今天还没结束。 ";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "是, 船长。 等这结束 —我要喝到下一次结束。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			ReturnOfficer_Knippel();
		break;
		
		case "LadyBeth_Alonso_1": // 阿隆索
			dialog.text = "我的上帝, 船长! 你没事吧? ";
			link.l1 = "有待观察。 我们损失了多少人? ";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "阵亡? 在这次行动中我们损失了"+sti(pchar.SailorDiedInBattleInfo)+"人。 不想显得无礼, 船长, 但... 我警告过你! ";
			link.l1 = "我会忽略那句话, 因为今天你证明了自己, 阿隆索。 你从哪里得到这么多才能? ";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "有一天我会告诉你那个故事, 船长 —如果我们活得足够长, 当然。 ";
			link.l1 = "还有其他有价值的建议吗? ";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "如果这里有宝藏 —他们早就找到了。 但我们还是应该搜索岛屿, 找到幸存者, 然后决定怎么处理他们。 而且我们不应该忘记布莱克伍德的船: 我只听说过那艘雪帆船的好话。 错过这样的战利品太可惜了, 船长。 当然, 我只是在传达船员在这个问题上的立场。 ";
			link.l1 = "当然。 我们走。 战利品在等着! ";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// 在开曼岛洞穴与水手的对话
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "别开枪! 我们投降! ";
			link.l1 = "你们是谁? ";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "我们... 我们是‘贝丝女士’号的。 布莱克伍德船长的船员。 他... 他还活着吗? ";
			link.l1 = "不。 你们的船长死了。 ";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "所以一切都结束了... 感谢上帝。 ";
			link.l1 = "你们似乎不为船长哀悼。 ";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "你不明白。 布莱克伍德是个伟大的人。 我见过的最好的船长。 但最近几个月... 他变了。 变得痴迷。 残忍。 让我们日夜工作, 寻找可能根本不存在的东西。 ";
			link.l1 = "我要把你们编入我的船员。 我们需要有经验的水手。 ";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "战败者活该, 伙计们。 现在你们该待在我的船舱里。 如果幸运 —你们能活到巴巴多斯的某个种植园。 ";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "真的吗? 你... 你不担心我们... 经历这一切后我们有什么问题吗? ";
			link.l1 = "每个人都值得第二次机会。 ";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "谢谢你, 船长。 我发誓, 你不会后悔的。 我们是好水手。 而且... 也许现在噩梦会停止。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "谢谢, 谢谢! 至少我们能活着。 请带我们离开这里。 这个岛... 好像被诅咒了。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// 在"贝丝女士"号上与敌方水手的对话
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "搞什么鬼? ! 你怎么敢攻击‘贝丝’号, 杀了杰里米? 你们这些混蛋别想活着离开, 船长会回来的, 而且... ";
			link.l1 = "你们的船长死了。 杰里米先开的火, 我把你们的‘贝丝’号作为用鲜血支付的合法战利品。 ";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "船长... 死了? 你在撒谎, 狗东西! 你连他制服上的纽扣都不值! ";
			link.l1 = "如果那制服有什么意义的话, 也是对那个早已消失的布莱克伍德而言。 是战斗为一个死人还是保住你们的性命, 由你们选择。 ";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "我们不会不战而降! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "听着, 伙计们。 我知道你们忠于船长。 这值得尊重。 但他死了, 你们还活着。 你们必须决定如何继续生活。 我们给你们一个重新开始的机会。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "船长, 这些人不是敌人。 他们只是在服从命令。 他们很多是以前的王室水手, 训练有素, 纪律严明。 不利用他们的技能是浪费。 伙计们, 在我漫长的舰队服役中, 我不止一次处于你们的位置。 我做出了正确的选择。 你们也做出正确的选择。 ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "好吧, 水手小子们! 选择很简单 —要么活着, 要么作为囚犯待在船舱里, 要么加入我们的船员, 有好的口粮和定期薪水, 要么... (用手指划过喉咙) 如果是我, 我会选择第一个! ";
			link.l1 = "... ";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "... ";
			link.l1 = "你们将成为我船员的一部分。 ";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "战败者活该, 伙计们。 现在你们该待在我的船舱里。 如果幸运 —你们能活到巴巴多斯的某个种植园。 ";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "你要把我们编入你的船员? 在这一切之后? ";
			link.l1 = "好水手总是有价值的。 而且布莱克伍德船长知道如何挑选他的人。 ";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "谢谢你, 船长。 我们不会让你失望的。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "好吧... 至少这是这场冒险可能结束的唯一方式。 原谅我们, 布莱克伍德船长。 我们没能保护你。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "我们不会不战而降! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// 与伊丽莎白.毕晓普的对话
		case "LadyBeth_Elizabeth_1":
			dialog.text = "... ";
			link.l1 = "打扰一下。 你是伊丽莎白吗? ";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "是的, 是我。 你是谁? ";
			link.l1 = "我是"+GetFullName(pchar)+"船长。 我... 认识阿尔伯特.布莱克伍德。 ";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "我的阿尔伯特? 哦, 上帝... 他... 他还好吗? ";
			link.l1 = "很遗憾, 不好。 他在战斗中牺牲了。 战斗到了最后一刻。 ";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "我... 我猜到了。 这么多年没有一句话... 你知道, 我等过他。 等了很久。 父亲说阿尔伯特只需要等待晋升。 总督已经决定了一切, 只是几个月的事。 但阿尔伯特... 他对那次谈话的理解完全不同。 说他会带着财富回来, 配得上我的手。 然后他就走了。 就这么... 走了。 ";
			link.l1 = "他直到最后一天都在想你。 ";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "多愚蠢啊。 我不需要他的宝藏。 我爱他, 不是他的钱。 我准备和他私奔... 但他太骄傲了。 我等了一封信, 任何消息... 然后只收到了这本奇怪的手册。 如此冰冷。 精于计算的文件... 一点也不像我认识的阿尔伯特。 那时我才意识到我失去了他。 ";
			link.l1 = "在他的物品中, 我找到了这个。 ";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "一张到我家的地图? 我是他的主要宝藏? 多么讽刺。 他在整个加勒比海寻找财富, 而对他来说唯一重要的东西一直在这里... 等等。 我有东西给你。 这是阿尔伯特的手册。 他一年前寄给我的。 说这会帮助他找到宝藏并回到我身边。 现在它对你更有用。 ";
			link.l1 = "谢谢你, 伊丽莎白。 很抱歉事情变成这样。 ";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "我结婚了, 船长。 嫁给了毕晓普先生。 父亲坚持的。 你不认识这个人... 也不会想认识。 每天我都在想, 如果阿尔伯特只是... 回来, 我的生活会怎样。 ";
			link.l1 = "现在我也会想那个。 ";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "再见, 船长。 还有... 照顾好自己。 不要追逐幻影。 ";
			link.l1 = ""+Goodbye(true)+"。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "是的, 是我。 ";
			link.l1 = " 海伦.麦克阿瑟船长。 我... 认识阿尔伯特.布莱克伍德。 ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "我的阿尔伯特? 哦, 上帝... 他... 你是谁? ";
			link.l1 = "海伦.麦克阿瑟船长, 我刚说过。 我指挥自己的船。 ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "船长? 女船长? 你... 你和阿尔伯特在一起? 在哪种意义上... 认识他? ";
			link.l1 = "只是作为船长。 抱歉, 阿尔伯特死了。 我目睹了他最后的战斗。 ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "我明白。 原谅我的怀疑。 只是... 布莱克伍德船长总是吸引女性的注意。 即使在这里, 在巴巴多斯。 尤其是在这里。 ";
			link.l1 = "你爱他。 ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "全心全意。 父亲说阿尔伯特只需要等待晋升。 只是几个月的事。 但他把父亲的话理解为因贫穷而拒绝。 说他会带着宝藏回来。 然后他就走了。 ";
			link.l1 = "男人和他们的骄傲! ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "你很幸运, 麦克阿瑟船长。 你是自由的。 你可以航行到任何你想去的地方。 没有种植园主, 没有父亲决定你的命运。 没有丈夫把你视为他们的财产。 ";
			link.l1 = "自由来之不易。 你必须每天捍卫它。 ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "我可能有东西能帮助你捍卫自由。 拿着。 这是他的寻宝手册。 阿尔伯特大约一年前寄给我的。 说这是他创造的最好的东西。 说这会帮助他致富并回到我身边。 但每一页都让他越来越不像我认识的阿尔伯特。 ";
			link.l1 = "谢谢你。 我会留着它。 ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "求你了, 船长... 珍惜你的自由。 我嫁给了毕晓普上校。 一个连我父亲都害怕的男人。 如果我像你一样自由... 一切都会不同。 ";
			link.l1 = "我知道。 ";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "再见, 船长。 祝你一帆风顺。 ";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
}