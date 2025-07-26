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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "你想要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;

		case "Juli":
			dialog.text = "... ";
			if (pchar.sex == "woman")
			{
				link.l1 = "小姐, 人们说太子港没有你的微笑就会失去魅力。 今天似乎就是这样的日子。 请原谅我的直率, 是不是有什么事困扰着你? ";
			}
			else
			{
				link.l1 = "小姐, 关于你的美丽和优雅的传闻早已传入我耳, 我必须说 --传闻远不及本人。 人们还说太子港没有你的微笑就会失去魅力, 可惜今天似乎就是这样的日子。 告诉我是哪个恶棍敢让你心情黯淡, 我发誓会向他挑战决斗, 让你重拾美丽的笑容。 ";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "啊, 小姐, 你的关心太让人感动了... 我必须承认, 你的担忧让我很感动。 但唉, 我悲伤的原因不是几句交谈就能驱散的。 这不是任何人的错, 而是我担心连最坚定的人也无法克服的 circumstances。 ";
				link.l1 = " circumstances? 我向你保证, 小姐, 对"+GetFullName(pchar)+"来说没有不可逾越的障碍。 告诉我发生了什么 --也许我能帮忙。 ";
			}
			else
			{
				dialog.text = "哦, 先生, 你真是甜言蜜语的大师。 我承认, 你差点就让我笑出来了。 但唉, 决斗解决不了我的问题。 让我心情黯淡的不是恶棍, 而是连你这样英勇的绅士也无法克服的 circumstances。 ";
				link.l1 = " circumstances? 我亲爱的小姐, "+GetFullName(pchar)+"船长能经受任何风暴! 如果我失败了, 我发誓会吃掉第一个过路人的帽子! ";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "如果你真的坚持, 我会告诉你发生了什么。 但首先, 我需要你保证这次谈话只在我们之间。 ";
				link.l1 = "我向你郑重承诺, 小姐。 无论你告诉我什么, 都会烂在我心里, 即使我必须把它带到海底。 ";
			}
			else
			{
				dialog.text = ""+ PChar.lastname+"先生, 你确实有让最烦恼的女士开心的天赋。 但请饶了无辜路人的帽子吧。 如果你真的坚持, 我会告诉你发生了什么。 只要答应我, 我的话只会是我们之间的秘密。 ";
				link.l1 = "我向你保证, 小姐, 你对我说的一切都会绝对保密, 即使面临死亡威胁。 ";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "那好吧。 我的房间里丢了一条项链... 但你要知道, 这远不止是一件饰品。 它是一个在我心中占据珍贵位置的人送给我的。 它的丢失感觉像一道伤口, 远比失去一件物品要深得多\n我一直在想谁可能是罪魁祸首, 只能得出一个结论。 我担心一定是我自己的仆人。 只有他们能进入我的私人房间, 并且可能觊觎这样贵重的东西。 但我不敢公开指控... ";
			link.l1 = "这确实是件微妙的事, 特别是如果你希望保密的话。 但如果我要提供帮助, 我必须明白你为什么如此谨慎地保守这个秘密。 如果不知道我们面临的危险, 我可能会无意中让我们都陷入困境。 告诉我我们必须避开谁, 阴影中潜伏着什么威胁。 ";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "你不能自由地说吗? 那么我担心, 小姐, 我只能给你美好的祝愿了。 我对阴谋和秘密既没有兴趣也没有天赋。 在我看来, 你的困难可以在镇卫队的帮助下迅速解决。 但似乎你选择了在这些麻烦的水域中航行更危险的路线。 ";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "你不能直截了当地说吗? 那么我必须请求你的原谅, 小姐, 因为我发现在这个秘密的迷雾中完全无能为力。 我对秘密事务和阴暗交易没有什么兴趣。 你的困境看起来非常简单: 一个由镇卫队解决的简单问题。 但你似乎决心把它编织成一个值得欧洲王室宫廷的阴谋。 ";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "这就是著名的"+GetFullName(pchar)+"船长面对逆境的方式吗? 一看到复杂情况就退缩? 也许你的才能更适合数朗姆酒桶或与码头商人斗嘴。 我只问你: 如果你还有一丝荣誉, 就把我告诉你的话严格保密。 再见, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "你说得对, "+GetAddress_Form(NPChar)+"。 那么真相是: 这条项链来自我叔叔 --这个岛上法国领土的总督 --极其憎恨的一个人。 他禁止一切接触, 甚至提到这个人的名字。 如果我叔叔发现这件礼物的来源, 后果将是灾难性的, 不仅对我, 而且对... ";
			link.l1 = "别说了, 小姐。 我完全理解。 请放心, 我会极其谨慎地找回你的项链, 像龙守护宝藏一样珍惜你的秘密。 ";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "我对你感激不尽, "+GetSexPhrase(pchar.lastname+"先生",pchar.name+"")+"。 在这些困难时期, 你的英勇和理解温暖了我的心。 我完全相信我的秘密在你手中是安全的。 愿幸运之风在这个微妙的冒险中为你扬帆。 ";
			if (pchar.sex == "woman")
			{
				link.l1 = "幸运眷顾敢于行动的人, 小姐。 请放心 --我会找回你的项链, 就像潮水一定会回到岸边一样确定。 ";
			}
			else
			{
				link.l1 = "幸运青睐有勇气的人, 小姐。 我一找回你珍贵的项链, 就会把它归还给你那双优雅的手, 它本来就属于那里。 ";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "啊, 船长, 你回来了! 有什么消息吗? 我祈祷你找回了我的项链。 请告诉我是这样。 ";
				link.l1 = "你的麻烦结束了, 朱莉。 项链已经找回, 我非常高兴能把它归还给它应在的地方 --你纤细的手中。 ";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "啊, 船长, 你回来了! 有什么消息吗? 我祈祷你找回了我的项链。 请告诉我是这样。 ";
				link.l1 = "很遗憾让你失望了, 朱莉。 搜索还在继续。 但请振作起来 --在你珍贵的项链归还给你之前, 我不会放过任何一个角落。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "问候你, 先生。 什么风把你吹到我们船上来了? ";
			link.l1 = "我找特里斯坦.雷尼尔船长; 我来提一个能让他赚大钱的建议。 ";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "我必须和特里斯坦.雷尼尔船长谈一件微妙的事情 --你明白的, 私事。 ";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "恐怕船长上岸了。 如果你的事紧急, 你可能会在镇上某个地方找到他。 ";
			link.l1 = "你知道他的目的地吗? 他访问这个港口时有没有特别喜欢去的地方? ";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "恐怕船长上岸了。 如果你的事紧急, 你可能会在镇上某个地方找到他。 ";
			link.l1 = "你知道他的目的地吗? 他访问这个港口时有没有特别喜欢去的地方? ";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "对不起, "+GetAddress_Form(NPChar)+", 但船长对他的行踪守口如瓶。 我只知道他几小时前下船了。 ";
			link.l1 = "即使这样也有帮助。 谢谢你的帮助。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "你到底是谁? 你有什么权利敢擅自闯入我的私人 quarters? ";
				link.l1 = "我是"+GetFullName(pchar)+"船长。 我来是为了一件重要的事。 ";
			}
			else
			{
				dialog.text = "你是谁, 我的女士? 我不记得今晚邀请过任何人。 不过我必须承认, 有些不速之客更... 引人入胜。 是什么风把这样一位佳人吹到我简陋的住所来的? ";
				link.l1 = "我是"+GetFullName(pchar)+"船长。 我的来访是为了一件公事, 不是私事。 ";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "公事, 是吗? 什么样的事情值得如此无礼的打扰? ";
				link.l1 = "很简单。 你有一条我来取回的项链。 ";
			}
			else
			{
				dialog.text = "你说公事? 真有意思... 是什么紧急的商业事务驱使你这样有魅力的女士到我的私人 chambers 来找我? ";
				link.l1 = "省省你的甜言蜜语吧, 先生。 我是为你手里的项链来的。 是的, 我清楚地知道你有它。 ";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "哈! 你说项链? 事实上我最近确实得到了这样一件东西, 但这关你什么事? 你肯定不会指望我把我的财产交给第一个要求它的陌生人吧? ";
			}
			else
			{
				dialog.text = "项链? 确实... 我最近得到了这样一件饰品。 请问船长, 你打算用什么方法让我交出这件理应属于我的珠宝? ";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "我准备出五千比索买这件东西。 这是一笔可观的数目, 足够你买一件同样好的饰品, 也许甚至更华丽。 同时, 这条项链将归还给一个比任何金钱都更珍视它的人 --远超过它的货币价值。 ";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "让我直说了吧, 先生。 你的选择已经大大减少了: 自愿交出项链, 活下去继续航行; 或者反抗, 让我从你冰冷的尸体上取回它。 决定在你, 但我建议你快点做决定。 ";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "你说五千? 那么, 船长, 你的议价很有说服力。 给你, 如果你这么看重这玩意儿的话。 ";
				link.l1 = "你的智慧与慷慨相当, 先生。 这个决定不会让你后悔的。 ";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Check passed", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "我得到这条项链不是为了把它卖给第一个挥着硬币的流浪汉! 这是给我妻子的礼物, 我不想再听这件事了。 在我叫人把你赶出去之前, 离开我的视线! ";
				link.l1 = "如果你拒绝绅士的协议, 那么我将用不那么文明的方式得到我想要的东西。 ";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Insufficient skill level (25)", SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "啊... 你这个傲慢的小子... 你以为你幼稚的威胁能吓到我吗? 哈! 你不知道你在和谁打交道! ";
				link.l1 = "我不在乎你是谁。 把项链交出来, 我就离开。 或者你真的愿意为一件对你毫无意义的饰品而死? ";
				link.l1.go = "Captain_4_leadership_2";
				notification("Check passed", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "我买这条项链不是为了和你这种人讨价还价! 这是给我妻子的礼物, 你无权在这里。 在我们把你扔出去之前, 滚出去! ";
				link.l1 = "如果你不和平地交出它, 我就强行拿了。 ";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Skill not high enough (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "该死的你和那条该死的项链! 拿去吧。 拿了就走, 趁我还没改变主意。 ";
			link.l1 = "明智的决定! 再见。 ";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+ PChar.name+", 你把快乐带回了我的心里! 你不仅找回了项链, 还找回了我的一部分灵魂。 你的高贵令人钦佩, 我保证会告诉所有我能告诉的人你的英勇! ";
			link.l1 = "请别这样, 小姐, 我不是为了名声才找回它的。 你的微笑是我真正珍视的唯一回报。 ";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "你太谦虚了, "+pchar.name+"。 但请接受这箱达布隆。 只有知道你接受了我的礼物, 我才会觉得我对你的感谢是恰当的。 ";
			link.l1 = "请别坚持, 小姐。 你的好话对我来说比任何一箱达布隆都更有意义。 ";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "如果这能让你安心, 小姐, 我会接受你的礼物。 但要知道, 我这样做不是为了报酬。 "+GetSexPhrase("你的认可","你的感激")+"对我来说远比这些达布隆重要。 ";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "我完全忘了问 --你知道是谁偷了项链吗? ";
			link.l1 = "我只知道, 小姐, 一个商人从一个叫吉赛尔的人那里收到了它。 从情况来看, 这可能不是她计划出售的最后一件珠宝。 ";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "我完全忘了问 --你知道是谁偷了项链吗? ";
			link.l1 = "我只知道, 小姐, 一个商人从一个叫吉赛尔的人那里收到了它。 从情况来看, 这可能不是她计划出售的最后一件珠宝。 ";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "吉赛尔? 但她是我的女仆! 我有过怀疑... 但我不愿相信。 最糟糕的是, 我甚至不能适当地惩罚她。 她可能会暴露我的秘密 --这是我不能允许的。 ";
			link.l1 = "那你会怎么做? 让她逃脱惩罚, 继续偷你的东西? ";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "哦不, 当然不会。 首先, 我要确保她不再靠近我。 然后我会想办法惩罚她, 让它看起来惩罚来自其他地方。 ";
			link.l1 = "女人的狡猾是一种危险的武器, 尤其是在像你这样优雅和敏锐的人手中。 我敢肯定你的女仆甚至没有意识到游戏已经输了 --而且不是对她有利。 ";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "啊, 船长... 我不想诉诸诡计, 但是... 有时候狡猾是唯一的前进道路。 ";
			link.l1 = "确实如此, 朱莉。 我不想离开你, 但职责在召唤。 如果不是我, 谁来照顾我的船员呢? ";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "再见, "+pchar.name+"。 请多访问我们的港口。 我们的城市急需"+GetSexPhrase("像你这样高贵英勇的男人。 ","像你这样心地如此高贵。 精神如此勇敢的女士。 ")+"";
			link.l1 = "你过奖了, 小姐。 我保证不会错过任何一次回到你美丽城市的机会。 下次见。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+ PChar.name+"! 真是惊喜! 还在征服海洋吗? ";
						link.l1 = "很高兴见到你, 小姐。 尽我所能地征服, 尽管大海仍然变幻莫测。 你呢 --是否享受着宁静? ";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "啊, "+pchar.lastname+"船长, 再次见到你真是太好了! 希望你一切顺利? ";
						link.l1 = "见到你我也很高兴, 小姐。 生意一如既往地需要时间和精力, 但这样的会面让任何一天都充满光明。 你这些日子过得怎么样? ";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+ PChar.lastname+"船长, 你又回来了? 我们这个简陋的小镇真的还有你没为了一把金币而出卖的人吗? ";
						link.l1 = "小姐, 我理解你的感受, 但我是按我认为正确的方式行事。 有时候正确的决定会带来痛苦, 我很遗憾它伤害了你。 ";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = ""+ PChar.lastname+"船长, 又来? 你的贪婪如此无止境, 不能让我们的小镇安宁, 还要寻找下一个受害者吗? ";
						link.l1 = "小姐, 很抱歉我的行为给你带来了痛苦, 但我是按照我的良心行事的。 ";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "最近一切都很平静 --没有什么打扰安宁。 请多访问我们的港口, 船长。 我相信你会在这里找到你想要的一切, 无论是在我们的商店还是其他地方。 ";
			link.l1 = "谢谢你, 小姐。 我会尽量多来。 我相信你的小镇仍然有许多令人愉快的惊喜。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "多亏了你, 船长, 我现在的日子平静多了。 我真的希望你能再次访问我们。 ";
			link.l1 = "当然, 小姐。 你的小镇总是给人留下最愉快的印象。 下次见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = ""+ PChar.lastname+"船长, 我们又见面了。 很神奇, 不是吗? ";
					link.l1 = "看来今天命运眷顾我们的相遇, 小姐。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = ""+ PChar.lastname+"船长, 看来我们的道路又一次交叉了。 ";
					link.l1 = "确实如此, 小姐。 很高兴再次见到你。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "看来我们见面太频繁了, 船长。 还是说你无法远离你已经背叛的人? ";
					link.l1 = "小姐, 我们的相遇纯属巧合, 但我理解你的痛苦。 我只希望有一天你能理解我的理由。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "你现在想要什么? 当然, 你的运气不会差到这是一个巧合。 或者你只是来提醒我你的耻辱? ";
					link.l1 = "小姐, 我无意打扰或揭开旧伤疤。 这次见面确实是偶然的。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}