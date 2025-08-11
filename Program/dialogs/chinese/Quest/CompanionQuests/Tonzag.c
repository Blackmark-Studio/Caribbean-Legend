void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "你需要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		case "startoff":
			dialog.text = "德莫尔船长! 欢迎来到托尔图加! ";
			link.l1 = "日安, 中尉。 和你的朋友们欣赏海景吗? ";
			link.l1.go = "startoff_joke";
			link.l2 = "让开, 中尉。 ";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "船长, 你的名声 precedes you, 上级决定安排一次我们可爱的托尔图加岛美景小游览。 我们现在就开始 —从镇上的牢房开始。 你的军官们也被邀请了。 ";
			link.l1 = "中尉, 我不是你在海滩上抓到的卑鄙走私犯。 请别开玩笑。 好好解释一下情况。 ";
			link.l1.go = "startoff_joke_1";
			link.l2 = "那我们别浪费时间了! 带路吧, 中尉! ";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "我明白和你们这些水手打交道需要不同的方式。 士兵们, 准备战斗! 德莫尔船长, 你和你的军官们被捕了。 交出武器! ";
			link.l1 = "我可以给你一颗子弹 —你想打在哪里, 中尉? 和你们这些陆老鼠, 没有其他办法。 ";
			link.l1.go = "startoff_silence_1";
			link.l2 = "依据什么法律? 如果你想不流血就逮捕一个武装团体, 中尉, 你得再加把劲。 ";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = "对我来说, 你们都一样... 抱歉, 但不会有任何解释, 船长。 上级命令。 请交出武器。 ";
			link.l1 = "我不需要任何麻烦... 现在不需要。 照他们说的做。 ";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "呃... 我想你没太明白我的意思。 船长, 你和你的军官们被捕了! 交出武器跟我们走! ";
			link.l1 = "我不需要任何麻烦... 现在不需要。 照他们说的做。 ";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "再说一个字, 船长, 我们就把你埋在这里。 马上把武器放在地上! ";
			link.l1 = "我不需要任何麻烦... 现在不需要。 照他们说的做。 ";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "我不怕流血, 船长。 即使你奇迹般地活下来, 也永远不能再踏上托尔图加岛。 而且我们的军事情报认为你非常重视对这个岛的访问权。 ";
			link.l1 = "我不需要任何麻烦... 现在不需要。 照他们说的做。 ";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "船长, 情况糟透了! 敌人紧紧抓住我们, 恐怕他们不会放手, 直到我们死! 我们的人现在真的有麻烦了, 大多数炮手都被击倒了! ";
			link.l1 = "我会帮助他们。 指挥并让我们离开这里! ";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "是, 长官! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "胜利了, 船长! 登陆队已被摧毁, 敌人选择撤退并向南进发。 船的状况尚可。 幸存船员: " + GetCrewQuantity(pchar) + "人。 报告完成! ";
			link.l1 = "谢谢! 每人朗姆酒, 并在我们到达港口前加强警戒! ";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "万岁! 是, 是! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "他本人来了! 你看到外面的血腥屠杀了吗? 都是你的所作所为, 叛徒! 但你要为一切负责: 为了贝洛港, 为了格鲁奥, 还有这个矿井! ";
			link.l1 = "等等, 那应该是... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "啊! 这不是好兆头... ";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "圣圣地亚哥, 保佑我! 邪恶! 什么怪物能犯下这样的行为? 回答, 先生! ";
			link.l1 = "冷静点, 先生! 先介绍你自己! 是的, 这里发生了可怕的屠杀, 但犯下罪行的人已经死了。 我亲自用他们的遗体'装饰'了矿井... ";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "我是" + GetFullName(npchar) + ", 皇家 Los Teques 矿的总工程师。 我刚从一个长达数月的任务中回来, 然后... 我看到了什么! 这里发生的事情是对上帝和人类的犯罪, 所以我要求你立即交出武器。 加拉加斯当局将调查这一恶行! ";
			link.l1 = "我不能服从, 先生, 我发誓我与这场屠杀无关! 但如果你坚持, 你自己的身体将被添加到尸堆中。 ";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "我不怕死, 但我总是知道什么时候该撤退。 走吧, 但记住, 我会报告这里发生的事情, 而且我不会漏掉一个细节! ";
			link.l1 = "我不能同意, 先生。 很抱歉事情到了这一步。 战斗吧! ";
			link.l1.go = "mine_head_fight";
			link.l2 = "看来你在找死, 先生。 但今天, 不会再有人死了。 我们要走了, 我希望这个细节也能出现在你的报告中! ";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "我们怎么处理这个囚犯, 船长? ";
			link.l1 = "没什么特别的, 只是别让他死或逃跑。 ";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "是, 是! 我明白了, 今天的审讯我不需要参加了, 船长? ";
			link.l1 = "为什么不? 决定改变你的职业了, 阿隆索? ";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "哈哈, 不, 船长。 我喜欢这份工作, 但似乎你船上有了一个新的行业大师! ";
			link.l1 = "赫拉克勒斯? 你从哪来的这个想法? ";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "嗯, 船长, 老人为此带来了他的工具包并使用了它。 我甚至不必拿出我的。 哈! ";
			link.l1 = "我明白了... 照常! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "啊... 查尔斯.德莫尔。 请允许我代表整个联盟向你道歉。 让你独处的命令到达我们这里太晚了。 我们组织对你没有要求, 船长。 至于这个秃头动物... 呃! 只要他在你的控制下, 他就安全, 但我给你的建议是不要留着他, 让他烂在他该在的排水沟里! ";
			link.l1 = "谢谢你的建议, 但我更感兴趣的是为什么有人保护我免受你的雇佣兵伤害。 ";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "我不知道, 船长。 我想指令来自我们的新赞助人。 听说过他吗, 叛徒? 联盟现在又回到了顶峰! ";
			link.l1 = "他是谁? ";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "我不知道, 船长, 即使我知道, 这种事情我们也不透露。 ";
			link.l1 = "既然如此, 告诉我别的, 你可以去任何你想去的地方。 我向你保证。 ";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "就这样? 好吧, 船长, 问你的问题然后放我走。 我保证即使我能回到联盟, 我也不会回去。 ";
			link.l1 = "你为什么如此专注于赫拉克勒斯? 仅仅为了一个逃兵, 麻烦太多了。 ";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "你告诉他什么了, 你这狗东西? 事情并不像看上去的那样, 船长! 联盟在不断移动, 密码在改变, 雇主也在变化。 想离开? 当然! 只有高级官员的出口是关闭的, 而这个人渣从来都不是。 他的妻子, 当然, 但我们太尊重唐扎格夫人了, 不能不给她例外。 ";
			link.l1 = "那为什么? ";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "有个叫贝洛港的地方... 它很大。 你看, 你的朋友不只是离开, 不只是违反合同, 不只是杀死了来完成他工作的团队。 他在街头造成了真正的屠杀, 极大地复杂化了我们与卡斯蒂利亚人的关系。 一次罕见的海盗袭击所带来的恐惧, 就像那天善良的天主教徒所经历的那样。 见鬼, 如果是别人做的, 我甚至可能会印象深刻。 ";
			link.l1 = "另一场屠杀? 真有趣。 继续说。 ";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "当时的公司副总裁罗登堡介入了。 他不知何故设法掩盖了整个事件, 但在那之前, 我们在西班牙的惩罚行动中失去了许多最优秀的人。 然而, 一段时间后, 我们再次与他们做生意... 啊! 但我们什么都没忘记, 一有机会, 我们就试图报复。 这一切的煽动者唐扎格必须被杀。 ";
			link.l1 = "你们没有成功。 那矿井呢? ";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "我们被迫这样做。 摆脱那个人渣需要太多费用; 我们需要黄金。 都是因为他... 但暗杀企图失败了, 我回到 Los Teques 稍微整理一下... 你怎么知道去哪里找? ";
			link.l1 = "这不重要。 我需要见你的领导人。 我想亲自解决这个误会, 因为你神秘赞助人的保证随时可能失效。 ";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "我确定他们已经在加拉加斯等你了, 船长。 看, 我什么都没瞒你。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "阿诺指挥官死了, 现在由奥斯汀负责。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "我已经回答了你所有的问题, 船长。 遵守你的诺言。 ";
			link.l1 = "我放你走。 离开我的船, 祈祷在加拉加斯没有埋伏等着我。 ";
			link.l1.go = "captive_spare";
			link.l2 = "谢谢你有趣的谈话。 不过, 在我看到矿井里的情况后, 指责赫拉克勒斯造成屠杀有点过分了。 滚去地狱吧, 你该去的地方。 ";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "先生们, 你们被邀请参加一个会议。 他们在教堂等你们, 所以安全有保障。 ";
			link.l1 = "那很快... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "查尔斯.德莫尔。 赫拉克勒斯。 你们不会活着离开这里。 ";
			link.l1 = "总是开始对话的好方式。 你真的需要所有这些吗? ";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "和你在一起, 船长, 事情不是很简单。 你看, 我们的新赞助人坚持要让你独处... 而他可以把他的要求塞进屁股里! 我非常讨厌你这种人! 你乘着漂亮的白帆航行, 以为冰在你嘴里不会融化。 但当我的刀刃刺入你时, 你们都像女孩一样尖叫。 查尔斯, 你得喜欢那个, 让我告诉你! 我已经有一段时间没这么做了... 现在你就在我面前, 漂亮男孩。 ";
			link.l1 = "你病了, 伙计。 ";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "不, 我不能让你走。 另一方面, 和你的朋友在一起, 就简单多了 —我的孩子们不需要他, 但还有一些他的老联盟伙伴不太相信我的方法的有效性... 太习惯于为干净的达布隆工作, 来自干净的公司。 但我知道什么会改变他们的想法 —一个大胆的罪人被斩首示众, 哈哈! ";
			link.l1 = "你选错了地点, 你这个疯子。 你真的要在教堂里开始战斗吗? ";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "当然, 为什么不呢? 为人们感到难过? 这可能不像在 Los Teques 那样有利可图, 但我们仍然会玩得很开心。 我们会粉刷上帝之家的墙壁, 啊哈! 船长, 你会提供足够的油漆。 ";
			link.l1 = "我明白了。 你嫉妒我们, 不是吗, 你这个疯老鼠? 嫉妒我们的自由? 女孩们很高兴见到我们, 硬币在我们口袋里叮当作响? 看看你自己: 你的赞助人从哪里把你挖出来的, 猪? 谁让你进教堂的? ";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "吃土吧, 你这个小混蛋! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
}