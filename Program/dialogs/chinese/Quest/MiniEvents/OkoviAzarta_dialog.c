void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "你想干嘛?";
			link.l1 = "没事。";
			link.l1.go = "exit";
		break;

		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "您找我有什么事, "+GetAddress_Form(NPChar)+"?不好意思, 我现在不接新订单, 实在是……太忙了。";
			link.l1 = "是吗?听说你最近在牌桌上输了件很贵重的东西, 是真的吗?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;

		case "OZ_Kuznets_2":
			dialog.text = "哼, 如果你是来幸灾乐祸的, 那就排队吧——像你这样的人多得很。不过没人愿意帮我一把。我命悬一线, 全看哈维尔·卡斯蒂略的脸色, 而人们只知道拿我的失败当笑话。";
			link.l1 = "我不是那种会嘲笑别人不幸的人。说说看, 事情是怎么发生的。也许我能帮你。";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "帮忙?凭什么有人要帮你?我才不会。你自己的幸福……甚至不幸, 都是你亲手铸成的。别装可怜了——接受你行为的后果吧, 那是理所当然的。";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;

		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;

		case "OZ_Kuznets_3":
			dialog.text = "那晚本不该成为我的噩梦。我只是去酒馆喝杯朗姆酒, 因为连海军上将欧赫尼奥·德·拉·托雷都刚刚下了个大订单给我。但喝得有点多后, 我坐下来玩了局牌。这时, 哈维尔盯上了我。\n起初运气站在我这边——我甚至赢了不少钱。但我一旦开始自信, 情况立刻急转直下。哈维尔不断往我杯里加朗姆酒, 我则一把把地输光了:先是现钱, 然后是买材料的钱, 最后是所有积蓄。\n等我意识到自己输了多少时, 已经无路可退。我脑子里只剩一个念头——无论如何也要翻盘。于是我把一本书压上了赌桌。那个混蛋哈维尔只愿出五千比索买它。\n其实这本书远不止这个价, 但我被赌瘾冲昏了头, 居然答应了。接下来……你应该知道了。我输了。你知道吗?我从没遇过这种事。我觉得那混蛋一定在我酒里下了什么。";
			link.l1 = "那我能帮你什么呢?你自己去玩牌, 自己拿出财产做赌注, 最后也自己输光了。你只是不想面对结果罢了。到底那本书有什么特别之处, 让你如此后悔?";
			link.l1.go = "OZ_Kuznets_4";
		break;

		case "OZ_Kuznets_4":
			dialog.text = "那本书是我最宝贵的东西。里面记载着代代铁匠师傅传下来的秘诀。它是我铁匠铺的灵魂, 是我技艺的核心。我已经接受了失败, "+GetAddress_Form(NPChar)+", 但我实在无法接受失去那本书。我曾向哈维尔出价五千比索赎回它。\n我甚至愿意背债, 只为取回它。但你知道他怎么说吗?他说他要十万!十万, "+GetAddress_Form(NPChar)+"!我根本拿不出这么多钱。他也不愿降价, 更不接受分期付款。我求他了……可他只是嘲笑我。我看得出, 您是"+GetSexPhrase("个硬汉, 是名水手……甚至可能是船长, 看您那把佩剑可不是装饰用","位不简单的姑娘, 相信您一定懂得如何与男人周旋")+"\n请您帮我和哈维尔谈谈。也许他会听您的, 愿意给我宽限点时间。没有那本书……我的人生毫无意义。作为回报, 将来我一定以优惠价格为您提供优质材料, 等我东山再起, 甚至还能为您打造点特别的东西, 船长。";
			link.l1 = "谈谈这事倒不难。看看结果如何吧。不过首先容我自我介绍:我叫"+GetFullName(pchar)+", 是我这艘船的船长。";
			link.l1.go = "OZ_Kuznets_5";
		break;

		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("我叫塞巴斯蒂安·科尔多瓦……","一位女船长?我听说过, 但这是我第一次亲眼见到, 还能交谈。")+" 很高兴认识您, "+pchar.lastname+"船长。谢谢您。如今这年头, 愿意帮助别人的人太少了, 大多数人只会嘲笑别人的不幸。您知道吗?如果我的书能重回我手, 我发誓:再也不碰赌博了。";
			link.l1 = "现在还不必谢我。我要先处理自己的事, 然后看看是否有空去找哈维尔。";
			link.l1.go = "OZ_Kuznets_6";
		break;

		case "OZ_Kuznets_6":
			dialog.text = "恐怕您得快点。哈维尔比我想象中动作还快……他已经找到了那本书的买主——是法国的枪械大师埃蒂安·雷诺阿。如果上将知道因为我, 那本宝贵的书落入法国人手里……我可就完了。坐牢都算轻的。";
			link.l1 = "哼……好吧, 我现在就去处理这事。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;case "First time":
			dialog.text = "你想干嘛?";
			link.l1 = "没事。";
			link.l1.go = "exit";
		break;

		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "您找我有什么事, "+GetAddress_Form(NPChar)+"?不好意思, 我现在不接新订单, 实在是……太忙了。";
			link.l1 = "是吗?听说你最近在牌桌上输了件很贵重的东西, 是真的吗?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;

		case "OZ_Kuznets_2":
			dialog.text = "哼, 如果你是来幸灾乐祸的, 那就排队吧——像你这样的人多得很。不过没人愿意帮我一把。我命悬一线, 全看哈维尔·卡斯蒂略的脸色, 而人们只知道拿我的失败当笑话。";
			link.l1 = "我不是那种会嘲笑别人不幸的人。说说看, 事情是怎么发生的。也许我能帮你。";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "帮忙?凭什么有人要帮你?我才不会。你自己的幸福……甚至不幸, 都是你亲手铸成的。别装可怜了——接受你行为的后果吧, 那是理所当然的。";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;

		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;

		case "OZ_Kuznets_3":
			dialog.text = "那晚本不该成为我的噩梦。我只是去酒馆喝杯朗姆酒, 因为连海军上将欧赫尼奥·德·拉·托雷都刚刚下了个大订单给我。但喝得有点多后, 我坐下来玩了局牌。这时, 哈维尔盯上了我。\n起初运气站在我这边——我甚至赢了不少钱。但我一旦开始自信, 情况立刻急转直下。哈维尔不断往我杯里加朗姆酒, 我则一把把地输光了:先是现钱, 然后是买材料的钱, 最后是所有积蓄。\n等我意识到自己输了多少时, 已经无路可退。我脑子里只剩一个念头——无论如何也要翻盘。于是我把一本书压上了赌桌。那个混蛋哈维尔只愿出五千比索买它。\n其实这本书远不止这个价, 但我被赌瘾冲昏了头, 居然答应了。接下来……你应该知道了。我输了。你知道吗?我从没遇过这种事。我觉得那混蛋一定在我酒里下了什么。";
			link.l1 = "那我能帮你什么呢?你自己去玩牌, 自己拿出财产做赌注, 最后也自己输光了。你只是不想面对结果罢了。到底那本书有什么特别之处, 让你如此后悔?";
			link.l1.go = "OZ_Kuznets_4";
		break;

		case "OZ_Kuznets_4":
			dialog.text = "那本书是我最宝贵的东西。里面记载着代代铁匠师傅传下来的秘诀。它是我铁匠铺的灵魂, 是我技艺的核心。我已经接受了失败, "+GetAddress_Form(NPChar)+", 但我实在无法接受失去那本书。我曾向哈维尔出价五千比索赎回它。\n我甚至愿意背债, 只为取回它。但你知道他怎么说吗?他说他要十万!十万, "+GetAddress_Form(NPChar)+"!我根本拿不出这么多钱。他也不愿降价, 更不接受分期付款。我求他了……可他只是嘲笑我。我看得出, 您是"+GetSexPhrase("个硬汉, 是名水手……甚至可能是船长, 看您那把佩剑可不是装饰用","位不简单的姑娘, 相信您一定懂得如何与男人周旋")+"\n请您帮我和哈维尔谈谈。也许他会听您的, 愿意给我宽限点时间。没有那本书……我的人生毫无意义。作为回报, 将来我一定以优惠价格为您提供优质材料, 等我东山再起, 甚至还能为您打造点特别的东西, 船长。";
			link.l1 = "谈谈这事倒不难。看看结果如何吧。不过首先容我自我介绍:我叫"+GetFullName(pchar)+", 是我这艘船的船长。";
			link.l1.go = "OZ_Kuznets_5";
		break;

		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("我叫塞巴斯蒂安·科尔多瓦……","一位女船长?我听说过, 但这是我第一次亲眼见到, 还能交谈。")+" 很高兴认识您, "+pchar.lastname+"船长。谢谢您。如今这年头, 愿意帮助别人的人太少了, 大多数人只会嘲笑别人的不幸。您知道吗?如果我的书能重回我手, 我发誓:再也不碰赌博了。";
			link.l1 = "现在还不必谢我。我要先处理自己的事, 然后看看是否有空去找哈维尔。";
			link.l1.go = "OZ_Kuznets_6";
		break;

		case "OZ_Kuznets_6":
			dialog.text = "恐怕您得快点。哈维尔比我想象中动作还快……他已经找到了那本书的买主——是法国的枪械大师埃蒂安·雷诺阿。如果上将知道因为我, 那本宝贵的书落入法国人手里……我可就完了。坐牢都算轻的。";
			link.l1 = "哼……好吧, 我现在就去处理这事。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = pchar.lastname+"船长!您和哈维尔谈过了吗?有什么消息?";
			link.l1 = "还没有, 我正打算去酒馆找他。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "谈过了"+GetSexPhrase("",", 而且很顺利")+"。哈维尔已经匆匆去见上帝了, 不过在那之前他还来得及把书还给你。拿着吧。";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;

		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 您不知道这对我意味着什么!多亏了您, 我现在能完成所有订单, 甚至还有海军上将的工作!虽然我手头没有钱, 但我还是准备了一份谢礼。\n来, 这是我为某位贵族打造的胸甲——他等等应该没关系。另外还有些材料, 如果您打算自己动手, 这些应该很有用。";
			link.l1 = "谢谢你, "+npchar.name+", 你真是太慷慨了!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;

		case "OZ_Kuznets_12":
			dialog.text = "还有, 如果您需要材料, 记得常来找我。我每月进货一次, 总会留点好货给您, 而且价格公道。我说话算话。";
			link.l1 = "我一定会的!那么, "+npchar.name+", 保重。我还有事, 先走一步。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;

		case "OZ_Kuznets_Fail":
			dialog.text = pchar.lastname+"船长!您和哈维尔谈过了吗?有什么消息?";
			link.l1 = "这么说吧……书一度在我手中。但……情况发展得很复杂, 它最终还是被卖掉了。";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;

		case "OZ_Kuznets_Fail_2":
			dialog.text = "什么?!你……你把书卖了?!那是我的书!";
			link.l1 = "是你当初赌输的那本书。它已经卖给哈维尔承诺的那位法国人了。";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;

		case "OZ_Kuznets_Fail_3":
			dialog.text = "不……这下我真的完了。书落到法国人手里, 将军的订单也完不成……我完蛋了……彻底完了!";
			link.l1 = "是你自己把自己逼到了这个地步。我希望这对你是个教训。再见。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OZ_Shuler_1":
			//PlaySound("Voice\Russian\tavern\Igroki v Tavernah-06.wav"); 
			dialog.text = "嘿, "+GetSexPhrase("水手","小可爱")+", 想不想来试试运气?来一局牌如何?赌注很友好……至少对新人来说是这样。";
			link.l1 = "我想, 你正是我在找的人。你也是这样勾引塞巴斯蒂安上桌, 然后把他输得精光的吧?我来是为了把他的书拿回来。";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;

		case "OZ_Shuler_2":
			dialog.text = "很好啊, 那就拿十万来——书就是你的。这书对我没用, 我连钳子和锤子都分不清。";
			link.l1 = "我出五千——你就是这个价骗那个铁匠上桌的。";
			link.l1.go = "OZ_Shuler_3";
		break;

		case "OZ_Shuler_3":
			dialog.text = "哈!你把我当傻子吗?我清楚这本书真正的价值。十万, 一分钱都不能少。否则它就归法国人了——他们可不差钱。";
			link.l1 = "你以为当局会允许你把西班牙图纸卖给法国人?等上将知道这事, 他会勃然大怒。";
			link.l1.go = "OZ_Shuler_4";
		break;

		case "OZ_Shuler_4":
			dialog.text = "哦, 别逗了。官府才不管这点小书, 他们有的是麻烦。至于上将?他是恨法国人没错, 但我可不打算等他来——拿着这笔钱, 我去任何殖民地都能受欢迎。";
			link.l1 = "那我们谈个条件吧。钱你还是能拿到, 但不是一次性。铁匠会分期还你, 而书今天就得交还他, 我以船长的名誉担保。这对你来说没什么损失——他迟早会还清, 而你一分钱也不会少。";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "你是不是没听懂?我说得再清楚不过了——我要的钱是现在立刻。不是一周后、不是一个月后、也不是等那个铁匠凑够, 而是现在。我想尽快离开这个倒霉岛。所以, 要么我现在就拿到全部钱, 要么书就归法国人, 而你的船长名誉嘛……留给上将的刽子手吧。";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "这样吧, 我们赌一把。我出十万, 你出书。如果你赢了, 就能发财离岛;要是你输了——书归我。还是说你只敢骗新手下水?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;

		case "OZ_Shuler_6_No_Money":
			DialogExit();
			notification("金钱不足 (100000) ", "Money");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				notification("通过检定 (30) ", SKILL_SNEAK);
			}
			else
			{
				notification("技能不足 (30) ", SKILL_SNEAK);
			}
		break;

		case "OZ_Shuler_6":
			dialog.text = "哈!我不需要变成富人——我已经是了!我干嘛冒险赌掉这本能带来一大笔钱的书?";
			link.l1 = "真没想到, 连哈维尔·卡斯蒂略也怕赌了?我还以为你是老牌高手呢, 结果不过是个靠醉汉赢钱的骗子罢了"+GetSexPhrase("","")+"。";
			link.l1.go = "OZ_Shuler_7";
			notification("通过检定 (100000) ", "Money");
			notification("通过检定 (30) ", SKILL_SNEAK);
		break;

		case "OZ_Shuler_7":
			dialog.text = "我不是怕, 只是觉得没必要——我现在已经什么都有了。";
			link.l1 = "得了吧, 我一眼就看出你那手已经痒痒得不行。你这么急着离开, 是不是因为怕别人发现你赢不了清醒的人?只敢对付醉鬼吗?";
			link.l1.go = "OZ_Shuler_8";
		break;

		case "OZ_Shuler_8":
			dialog.text = "你竟敢这么说我?!我赢过的人比你强多了!我们的赌局里, 池底大得能买下一艘船和一个你这样的嚣张船长!赌就赌!每张牌五千, 每人十万, 谁先输光谁输。看看谁厉害!";
			link.l1 = "少废话, 发牌吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;

		case "OZ_Shuler_Win_1":
			dialog.text = "见鬼!这怎么可能……";
			link.l1 = "怎么?换别人赢你就不高兴了?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;

		case "OZ_Shuler_Win_2":
			dialog.text = "你是个骗子!你以为我看不出来吗?别想骗我!我宁愿把你剁成碎块!";
			link.l1 = "骗子?哈哈!你只是不甘心罢了, 伙计。但既然你非要送死——我就成全你。拔剑吧!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;

		case "OZ_Shuler_Lose_1":
			dialog.text = "哈!怎么样, "+GetSexPhrase("伙计","小可爱")+", 被剥得精光的感觉如何?有人说脸皮厚是福气, 不过你可不是这种人。";
			link.l1 = "别太得意。你不过是走运罢了。";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;

		case "OZ_Shuler_Lose_2":
			dialog.text = "失败者总这么说。好了, 赌就赌输了"+GetSexPhrase("","")+", 别生气。哪天你再凑齐十万, 不妨再来挑战一下……虽然我怀疑结果会有变化……";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;

		case "OZ_Felip_1":
			dialog.text = "您好, "+GetAddress_Form(NPChar)+"。请问找我有什么事?";
			link.l1 = "您好。我是船长"+GetFullName(pchar)+", 想跟您谈谈关于哈维尔·卡斯蒂略的事。";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "哼……如果那个家伙也欠你钱, 那你恐怕得排在长队后头了。哈维尔从不急着还债。不过就算他真有了钱, 首先也得还我——我已经安排得他别无选择。";
			link.l1 = "幸好我不是他的债主。他到底欠你多少?你又做了些什么?";
			link.l1.go = "OZ_Felip_3";
		break;

		case "OZ_Felip_3":
			dialog.text = "他总共欠我十五万比索。只还了区区一万, 也许他觉得这样就够了。但我很快让他明白他错了。我的人又逼他交了两万。剩下的得在一周内还清——而期限快到了。幸运的是, 我听说他很快就会靠卖一本书拿到一大笔钱。";
			link.l1 = "你真相信他会还你钱?我劝你别抱太大希望。哈维尔根本不掩饰他一拿到钱就打算逃跑。";
			link.l1.go = "OZ_Felip_4";
		break;

		case "OZ_Felip_4":
			dialog.text = "我当然知道, 船长。放心, 我已经安排得他没还清前哪儿也逃不掉。";
			link.l1 = "我看你确实掌握全局。但多做点保险从不嫌多。碰巧我就是个专门讨债的"+GetSexPhrase("专家","女专家")+"。如果你允许, 我可以代表你把钱要回来。";
			link.l1.go = "OZ_Felip_5";
		break;

		case "OZ_Felip_5":
			dialog.text = "遗憾的是, 船长, 这笔债的追回已经让我损失不少, 我也没法再支付你的服务费了……";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", 不用担心。我自己也有点私心, 所以这次免费帮你。";
			link.l1.go = "OZ_Felip_6";
		break;

		case "OZ_Felip_6":
			dialog.text = "那能告诉我你的动机吗?";
			link.l1 = "这么说吧, 他在赌桌上的那些勾当我可不能睁一只眼闭一只眼。";
			link.l1.go = "OZ_Felip_7";
		break;

		case "OZ_Felip_7":
			dialog.text = "既然你不收费, 我也没理由拒绝。唯一的要求是, 船长, 请别做得太过火。如果那混蛋在还清前就去见祖宗, 那我什么也得不到。";
			link.l1 = "放心吧, 费利佩, 我会谨慎行事的。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;

			case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"!你不会是这么快就搞定了吧?";
			link.l1 = "很遗憾, 还没有。但我正在处理这事。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;

		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "哟, "+GetSexPhrase("船长","小可爱")+", 又来了!怎么, 想再输几千比索?";
			}
			else
			{
				dialog.text = "又是你?我不是说了吗:钱拿出来, 否则就滚。";
			}
			link.l1 = "收起你的嘴脸, 哈维尔。把钱包准备好——我不是闲逛来的。 你不会忘了欠费利佩·阿拉尔孔的钱吧?现在我代表他。所以选吧:要么现在还钱, 要么等我从你尸体上搜。";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "该死的!我这儿正有笔交易, 你没看见吗?几个小时后再来——那时候我们再谈。";
			link.l1 = "你是不是没听清?我可是清楚"+GetSexPhrase("","地")+"说明了——我要的钱是现在立刻。不是一周后, 不是一个月后, 不是你什么时候凑够, 而是现在。十二万比索, 不少一分。书我可以算你五千。";
			link.l1.go = "OZ_Shuler_13";
		break;

		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("肮脏的混蛋","你个小贱人")+"!你真以为能轻松摆平我?那你这可怜的一生可就大错特错了。";
			link.l1 = "走着瞧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;

		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "真是一场好戏……我得承认, "+GetAddress_Form(NPChar)+", 你让我大开眼界。你的剑术真是令人惊叹。容我自我介绍——我是"+GetFullName(npchar)+"。这个倒霉蛋, 我猜你就是哈维尔·卡斯蒂略?";
				link.l1 = "正是他。而我是——船长"+GetFullName(pchar)+"。";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "真是一场好戏……我得承认, "+GetAddress_Form(NPChar)+", 你让我大开眼界。你的剑术令人敬佩。世事无常, 那本让我千里迢迢而来的书就这么换了主人。不过我还是希望, 自己不会空手而归。";
				link.l1 = "哼……你估这本书值多少钱?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;

		case "OZ_Frantsuz_1_1":
			dialog.text = "你看, 船长, 我可不是随便路过的。我千辛万苦, 就是为了那本书……现在, 它似乎在你手上。我真心希望我们能达成协议——我可不想空手离开。";
			link.l1 = "哼……你估这本书值多少钱?";
			link.l1.go = "OZ_Frantsuz_2";
		break;

		case "OZ_Frantsuz_2":
			dialog.text = "哦, "+GetAddress_Form(NPChar)+", 我对稀世之物的价值一清二楚。八万比索。这可是很慷慨的报价了, 信我, 你不会再遇到这种机会了。";
			link.l1 = "这书确实值钱, 说实话我问"+GetSexPhrase("","了")+"也只是出于好奇。但我不会拿一个人的命运做交易。对不起, 先生, 这笔交易我拒绝了——这本书应该回到它真正的主人手中。";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "这价钱真可笑。这本书包含了最顶尖铁匠的秘密。十五万比索——你要是不同意, 那就还给原主, 没得谈。";
			link.l2.go = "OZ_Frantsuz_4";
		break;

		case "OZ_Frantsuz_3":
			dialog.text = "请别急着拒绝。我为它跋山涉水, 远道而来。我愿意提高到十万比索, 算是对你那精彩表现的敬意。";
			link.l1 = "我话已说尽。抱歉, 我还有事, 告辞。";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;

		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;

		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 我欣赏你的自信, 但十五万……这不叫开价, 这叫胡来。别把这笔交易搞得像闹剧。十万比索是合理价, 再多就没人买了。";
			link.l1 = "看来我们说不到一块儿去。那就不必浪费彼此时间了。再会, 先生。";
			link.l1.go = "OZ_Frantsuz_5";
		break;

		case "OZ_Frantsuz_5":
			dialog.text = "等一下!好吧, 你赢了。十五万, 比索。成交?";
			link.l1 = "很高兴你作出了正确选择。书是你的。希望你能在加勒比成为顶尖的大师。";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 即便没有这本书, 我也从未有敌手。但我得承认, 得到这样一份稀有的战利品, 确实令人愉快。现在请原谅我——我已迫不及待想看看它是否真的配得上那些溢美之词了。";
			link.l1 = "既如此, 我就不打扰您了。再会。";
			link.l1.go = "OZ_Frantsuz_7";
		break;

		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;

		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "哟, 这是什么阿猫阿狗?想偷走我们的箱子就溜?做梦, 伙计!我们现在就把你塞进箱子里, 然后钉死!";
			}
			else
			{
				dialog.text = "哟哟……你是谁啊, 小妞?是不是迷路了?想偷走箱子就跑?想得美, 宝贝!我们可得好好搜搜你——看看你兜里……还有衣服下面藏了啥。";
			}
			link.l1 = "废话真多, 一群臭虫。拔剑吧, 让我看看你们除了嘴还能干什么。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;

		case "OZ_Felip_11":
			dialog.text = "船长!我听说哈维尔已经上了西天, 全是你的‘功劳’。我可不是嘱咐过你别太早动手?希望你这次来, 是把我的钱带回来了?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "正是如此。我找到了他藏的钱, 共十万比索。这就是他留下的全部财产了。";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "没错, 我确实杀了他。但他先动手, 我只是自卫。他身上啥也没有, 一分钱都没找到。很遗憾, 债务追回失败。";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;

		case "OZ_Felip_12":
			dialog.text = "十万……虽然不全, 但了解哈维尔的人都知道, 从他那儿能拿出这么多已经是奇迹了。谢谢你, 船长。我真是雇错人了——你才是真正的高手。";
			link.l1 = "这事其实不难。不过现在, 恕我失陪"+GetSexPhrase("","了")+", 还有事要处理。";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;

		case "OZ_Felip_13":
			dialog.text = "再见了, 船长。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;

		case "OZ_Felip_14":
			dialog.text = "你这"+GetSexPhrase("混蛋","骗子")+"!敢当着我面撒谎?!这事没完!";
			link.l1 = "呃……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;

		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\\Russian\\Master_02.wav");
			//PlaySound("VOICE\\Spanish\\Master_02.wav");
			dialog.text = "您好, "+pchar.name+"!您是想买些材料还是成品?";
			link.l1 = ""+TimeGreeting()+"。让我看看你今天都有什么货。";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "您好, "+npchar.name+"!谢谢你的好意, 我只是来打个招呼"+GetSexPhrase("","罢了")+"。";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar"))
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;

		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", 决定买点什么了吗?";
			link.l1 = "正是如此。让我看看你今天都带来了什么。";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "抱歉, 我要走了。";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}