// 其他和不知名NPC的对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你有什么需要吗? ";
			link.l1 = "不, 暂时没有。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> 船上的水手, 抵达圣皮埃尔
		case "Startsailor":
			dialog.text = "该死的, 终于靠岸了! 醒醒, 先生... 不管你叫什么... 我们到了! ";
			link.l1 = "啊! 已经早上了? 这该死的炎热和潮湿是怎么回事? ";
			link.l1.go = "Startsailor_1";
			link.l2 = "我说! 查尔斯.德.莫尔! 贵族, 你知道的。 这么热怎么喝酒? 看在上帝的份上, 我宁愿喝点水。 ";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "习惯吧, 先生。 这是我们这里唯一的天气... 可能还会更糟。 ";
			link.l1 = "怎么可能更糟? ! 我只穿了件亚麻衬衫, 汗水还是顺着背流! ";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "你会看到的, 哈哈! 可能是飓风季节! 快点, 先生。 长艇不会等你的。 你不想游泳去马提尼克吧? ";
			link.l1 = "给我一点时间, 好吗? 我的剑呢? 啊, 在这里... ";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "你不再欧洲了... 小心点, 先生。 这是多事之秋。 有传言说美洲群岛公司把马提尼克岛卖给了一些宗教狂热分子。 十字军或类似的胡说八道。 至少从甲板上看海岸, 我还没注意到什么异常。 但既然我们离开了一段时间, 我不在的时候可能发生了很多变化。 ";
			link.l1 = "十字军? 胡说八道! ";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "不管是不是胡说八道, 谣言四起。 我们已经有足够的麻烦了。 丛林里的食人族。 热带热病。 海盗。 巷子里的强盗, 更不用说西班牙人和英国人了... ";
			link.l1 = "哦, 又来了... 现在我看到的唯一麻烦是闷热和蚊子... 好吧, 我准备好了。 我们走吗? ";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "到甲板上, 登上长艇, 先生。 欢迎来到加勒比海! ";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "这里没有其他天气,'大人'。 如果说有什么不同的话, 只会更糟。 ";
			link.l1 = "无法忍受的天气, 就像过去几个月我的同伴一样。 我希望群岛上有一些体面的人。 ";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "那么, 我想我们都会很高兴看到你终于离开我们, 先生。 船在等着。 别高兴得忘乎所以。 别忘了你的东西 - 船要继续前进, 如果你不拿, 可能就忘了。 ";
			link.l1 = "好像我会留给你似的。 比索, 剑 - 看来我没被偷。 ";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "我们当然是诚实的人, 但你想得对 - 总是留意你的东西, 否则有人可能会偷你的口袋。 就像在旧欧洲一样。 或者说, 任何地方。 但这个地方不像家。 一些狂热分子在这里建立了基地。 听说他们秘密买下了整个岛。 所以, 保持警惕, 不要引起注意。 ";
			link.l1 = "什么胡说八道! ";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "这是谣言。 感激我费心分享并关心你在这里的停留。 否则, 你那娇嫩的加斯科涅玫瑰可能会在我们炽热的阳光下枯萎。 不管是不是胡说八道, 保持警惕 - 即使没有狂热分子, 我们也有足够的麻烦。 巷子里和丛林里的强盗, 海上的海盗, 还有红皮肤的食人族... ";
			link.l1 = "好了, 好了! 我会处理的。 现在对我来说可能有点热, 但我在家乡已经晒黑了, 不像那些诺曼人。 如果有什么能用剑解决的, 你可以指望我。 但蚊子 - 纯粹的折磨! 好吧, 我所有的东西都在。 你说船准备好了? ";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "急切地等待着。 希望你能自己来, 先生? 上去吧, 希望你不会迷路。 哦, 欢迎来到群岛, 呵呵。 ";
			link.l1 = "是的, 谢谢。 唯一的安慰是我不会在这里待太久。 ";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// < —船上的水手, 抵达圣皮埃尔
		
		// 知道米歇尔的市民
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "打扰一下, " + GetAddress_FormToNPC(NPChar) + ", 你能告诉我在哪里可以找到米歇尔.德.蒙佩吗? 他一定在你们镇上的某个地方。 ";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "嗯... 我看你是刚到这里, 因为你无所畏惧地问这样的问题... 我建议你停止, 否则你会有麻烦。 关于你的问题... 和神父谈谈。 你可以在教堂找到他。 ";
			link.l1 = "谢谢你! ";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> 在官邸被捕
		case "Sharlie_arest":
			dialog.text = "站住! 立即放下武器, 跟我们走! ";
			link.l1 = "这到底是怎么回事? ";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //转动时间
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// 在官邸被捕
		
		// --> 基地军官
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "很高兴见到你, 德.莫尔先生。 有什么事吗? ";
				link.l1 = TimeGreeting() + ", 军官。 我想和我弟弟米歇尔.德.蒙佩谈谈。 当然是私下里。 我想了解他在加勒比海的服役情况。 ";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "审讯怎么样? 你找到什么有价值的东西了吗? ";
				link.l1 = "哦, 是的。 太多了, 我要把这个西班牙人带回我的船上。 他是重要证人, 必须送到圣克里斯托弗进一步审讯。 ";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "你在这里有什么事, 先生? ";
				link.l1 = "我来看我弟弟, 米歇尔.德.蒙佩。 ";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "先生, 我必须温和地提醒你, 你在军事营地内。 请行为得体。 ";
				link.l1 = "是的, 先生。 当然。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "先生, 我必须温和地提醒你, 你在军事营地内。 请行为得体。 ";
				link.l1 = "是的, 先生。 当然。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "米歇尔.德.蒙佩目前在我们的一个炮台里被看守, 根据菲利普.德.潘西骑士的个人命令。 下楼到下层。 你会在那里找到我们用作储藏室和牢房的炮台。 我想你能找到路。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// 基地军官
		
		// --> 基地士兵
		case "Maltie_soldier":
			dialog.text = "你好, 先生。 我能为你做什么吗? ";
			link.l1 = "谢谢你, 士兵, 但不, 我很好。 继续吧。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> 基地士兵
		
		// --> 马耳他向导
		case "Sharlie_maltie":
			dialog.text = "谢谢你的等待, 先生。 所以你在找米歇尔.德.蒙佩? 你是他弟弟? ";
			link.l1 = "是的, 没错。 我是他弟弟查尔斯。 我必须马上见他。 米歇尔有麻烦了吗? ";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "不幸的是, 他有麻烦了, 先生。 米歇尔被关在下面的一个炮台里。 法属新世界殖民地总督菲利普.德.潘西骑士亲自签署了逮捕令。 我们都很震惊。 你弟弟是男子气概。 纪律和勇气的典范, 我们教团的骄傲! 最糟糕的是, 我们, 他的朋友, 不得不把他像普通罪犯一样锁在铁窗后面并看守他! 我们尽力让他舒适, 但是... 监狱仍然是监狱。 ";
			link.l1 = "他被指控什么? 他犯罪了吗? ";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "总督办公室指控米歇尔挪用公款! 多么荒谬! 我们这里所有人都确信这是出于政治动机。 我私下告诉你。 米歇尔一直在代表教团参与某些秘密行动。 也许他发现了不该知道的事情。 或者更糟, 激怒了一些有权势的人。 但偷钱? 没人相信。 这是借口, 不是真正的原因, 懦弱和卑鄙的借口! 但话说够了。 你弟弟期待见到你, 我相信他会亲自告诉你一切。 ";
			link.l1 = "好的。 你们的监狱在哪里? ";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "在我们的地下军械库, 就在城里。 跟我来。 我给你带路。 ";
			link.l1 = "... ";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "我们到了。 这是我们的行动基地 - 耶路撒冷。 罗得岛和马耳他军事医院骑士团加勒比分会。 炮台在我们下面。 穿过餐厅和小教堂走下大厅。 那里的楼梯会带你到下层。 寻找一条排列着牢房的走廊。 你弟弟在后面附近的一个牢房里。 \n去吧, 查尔斯, 上帝与你同在。 请帮助米歇尔! 他是无辜的, 这里的每个人都愿意发誓。 ";
			link.l1 = "我来这个鬼地方的全部原因就是见我弟弟。 我希望至少能让他摆脱这种困境。 ";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//打开位置
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "所以你在找米歇尔.德.蒙佩? 你是他弟弟? ";
			link.l1 = "是的, 没错。 我是他弟弟查尔斯。 我需要马上见他。 他遇到麻烦了, 不是吗? ";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "不幸的是, 他有麻烦了, 先生。 米歇尔被逮捕并关在我们的监狱里。 法属殖民地总督德.潘西骑士亲自下达并签署了命令。 我们都很震惊。 \n你弟弟是男子气概。 坚定和勇气的榜样, 我们教团的骄傲! 最糟糕的是, 我们, 他的朋友, 不得不锁上他的牢房并像罪犯一样看守他! 我们尽力缓解他的状况, 但是... 监狱就是监狱。 ";
			link.l1 = "那么他被指控什么? 他犯罪了吗? ";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "胡说! 纯粹的胡说! 他们指控米歇尔挪用和窃取国家资金。 荒谬! 我们都确信这只是一场政治游戏。 米歇尔一直参与教团的秘密行动, 也许, 他知道的太多了。 \n或者别的什么。 但偷钱! 没人相信。 这只是借口, 不是原因, 如此粗鲁和愚蠢的借口! 但话说够了。 你弟弟期待见到你, 我相信他会亲自告诉你一切。 ";
			link.l1 = "好的。 监狱在哪里? ";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "它位于我们的地下基地, 就在城里。 跟我来。 我给你带路。 ";
			link.l1 = "... ";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//< —cle
		// 马耳他向导
		
		// --> 招募水手
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "然后他靠在栏杆上, 把加勒比海都吐绿了! 哈哈哈! ";
			link.l1 = "阿隆索? ";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "哦! 查尔斯, 我正在给伙计们讲我们的壮举! ";
			link.l1 = "我注意到了。 听着, 阿隆索。 我已经... 成为船长了。 ";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "已经? 我以为你至少需要一个月, 哈哈! ";
			link.l1 = "我是认真的! ";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "如果只是我自己, 我会立刻签约。 但我有四十个来自‘尤利西斯号’的兄弟跟着我。 他们信任我给他们未来; 我必须确保你不会让他们失望\n"+
			"你有什么样的船? ";
			link.l1 = "船就是船, " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")) + "。 为什么, 这很重要吗? ";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "你知道, 在‘尤利西斯号’之后, 我们宁愿不服务于某些三桅帆船或小帆船。 我们已经看过你的船了, 伙计们同意\n"+
			"现在, 钱。 我们要求预付4800比索。 之后 - 像往常一样分成。 我向你保证, 这并不过分。 你能处理吗? ";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "很好, 成交! 这是你的钱。 ";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "不幸的是, 我现在身上没有那么多钱。 ";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "船长, 你的货舱里有食物吗? 还有药品? 没有? 嗯, 那不好。 出去为我们的航行获取最低限度的物资, 然后回来我们再谈。 去商店买你需要的东西。 ";
				link.l1 = "嗯。 你说得对。 好吧, 我会的。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "呸! 恭喜... 船长! 我马上召集兄弟们, 我们前往你的船。 ";
				link.l1 = "很高兴恢复我们的冒险, 阿隆索。 让船准备出海! ";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//如果之前没有移除, 就移除禁止
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "好吧, 一旦你找到足够的钱, 回来。 你会在酒馆找到我们。 反正周围也没有其他船。 我们会继续喝酒嫖妓, 哈哈! ";
			link.l1 = "我会尽快回来。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "你回来了, 船长? 准备雇佣我和我的伙伴们吗? 我们的钱包开始变轻了, 需要再次感受海风! ";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "还没有, 我还在准备一切。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "是的。 拿你的预付款。 现在你为我服务。 ";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// 招募水手
		
		// 向领航员询问舵手
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("啊哈船长! 你需要什么? ", "你好先生。 我能为你做什么? ", "日安。 你想要什么? ");
			link.l1 = RandPhraseSimple("我有个问题要问你。 ", "我需要关于这个殖民地的信息。 ");
			link.l1.go = "skipertalker_1";
			link.l2 = "只是打个招呼。 再见! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("是什么? ", "你需要什么? ");
			link.l1 = "听着, " + GetAddress_FormToNPC(NPChar) + ", 事情是这样的... 我在找一位领航员。 也许你知道镇上有谁适合这份工作? ";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "领航员? 嗯。 好吧, 我知道一个... 但有个问题 - 他在监狱里,  debtors'prison。 这个可怜的混蛋已经在炮台里关了将近一个月了, 直到他或别人还清他的债务。 ";
			link.l1 = "一个债务人? 嗯... 他叫什么名字? ";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "他叫福尔克.德鲁克。 如果你想见他, 问问监狱长。 但我认为他们不会让他走, 除非你还清他的债务, 因为他肯定不会, 哈哈哈! ";
			link.l1 = "也许我会。 谢谢你的信息, 朋友。 ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> 舵手
		case "Folke":
			dialog.text = "我有什么荣幸, 先生? ";
			link.l1 = "你好, 福尔克。 很简单, 我有船, 但没有领航员。 我需要一个。 所以我还清了你的债务... ";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "你是说你把我从这里拖出来是为了让我加入你的船员? ";
			link.l1 = "正是。 我想你很快就会弥补我为你花的钱。 嗯... 我们拭目以待。 ";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "我的感激, 先生。 我已经厌倦了这个腐烂潮湿的牢房。 能再次回到船上将给我带来极大的快乐。 啊, 大海... ";
			link.l1 = "很高兴我们达成了共识, 福尔克。 还有一件事, 除了驾驶船只, 你还有其他技能吗? ";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "什么都会一点, 船长。 我曾经在荷兰西印度公司的一艘私掠船上服役。 在那里我学会了如何操作大炮, 所以如果你需要, 我可以担任炮手军官。 贸易和登船是我最薄弱的环节。 ";
			link.l1 = "感谢分享, 现在跟我到船上。 我希望你用你经验丰富的眼光观察船员, 因为他们正在准备一切以便出发。 然后, 我想尽快前往瓜德罗普。 ";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "是, 船长! 我会在你的船舱等你。 *在海上时使用动作菜单访问船舱和船的其他区域*";
			link.l1 = "谢谢你, 福尔克。 船上见。 ";
			link.l1.go = "Folke_5";
			Log_Info("你获得了护身符‘商人的念珠’");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//打开位置
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//强制任务 - 海盗伏击中断
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "你的大副在等你。 使用动作菜单(ENTER)前往船舱。 ";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // 250912 填充商店
			dialog.text = "一艘漂亮的小帆船, 船长! 相当不错的小船, 索具精良, 木材坚固。 有了这样的船, 我们不仅能安全抵达瓜德罗普, 甚至如果我们愿意, 还能巡航整个加勒比海。 ";
			link.l1 = "太好了。 至少我没有把钱浪费在一艘漏水的船上... 在我们起航前, 你有什么建议吗, 福尔克? ";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "该死的, 这艘单桅帆船漏得像筛子, 船长。 我们勉强能横渡到瓜德罗普。 如果你想完整抵达巴斯特尔, 必须立即在造船厂修理她。 ";
			link.l1 = "我没有选择, 这是唯一出售的船! 他们向我要了一大笔钱。 如你所知, 我们目前没有时间修理她... 在我们起航前, 你有什么建议吗? ";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "好吧, 我们的火药和炮弹供应充足, 船长。 目前这就够了; 只记得及时补充。 ";
				link.l1 = "嗯, 那是不言而喻的。 还有其他意见吗? ";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "啊! 谢谢你的提醒。 我碰巧有一整箱炮弹! ";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "我们的弹药库里没有足够的弹药, 船长。 我们至少需要一百发炮弹。 链弹和炸弹, 以及一百袋葡萄弹和二百桶火药。 购买必要的物资, 船长。 花费不多, 但如果我们被海盗或西班牙人袭击, 这将拯救我们的生命。 ";
				link.l1 = "值得投资。 我去商人那里。 ";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "... 你拖着它多久了? ";
			link.l1 = "将近两周。 ";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "但为什么, 船长? ! ";
			link.l1 = "我喜欢收集零碎东西。 谁知道什么会有用。 ";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "好吧, 你真倒霉。 这些炮弹永远不适合我们的玩具枪。 实际上, 我从未见过这么大的炮弹。 其中一个就能把‘阿德琳号’送入海底。 ";
			link.l1 = "... ";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "你完成购买弹药了吗, 船长? ";
			if (bOk)
			{
				link.l1 = "是的, 我完成了。 还有其他意见吗? ";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "现在没有, 我还在努力。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "做得好, 你为船员购买了足够的武器。 如果我们没有足够的武器, 在登船行动中会损失更多人。 上帝保佑我们不要那样。 别忘了经常检查货舱里的数量\n谨慎起见, 多备一些武器比我们需要的更好。 该死的老鼠喜欢啃咬木柄和枪托。 ";
				link.l1 = "明白了。 我看你还有什么想补充的? ";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "我们船上没有足够的武器给船员。 如果我们没有足够的武器, 在登船行动中会损失更多人。 上帝保佑我们不要那样。 据我所知, 你的船员有四十人\n为每个人购买足够的武器, 甚至多买一些, 五十套就足够了。 谨慎起见, 多备一些武器比我们需要的更好。 该死的老鼠喜欢啃咬木柄和枪托。 ";
				link.l1 = "那我就这么做。 我很快回来。 ";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "你完成购买武器了吗, 船长? ";
			if (bOk)
			{
				link.l1 = "武器在货舱里。 我看你还有什么想补充的? ";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "现在没有, 我还在努力。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "不, 我想就这样。 我们有足够的食物, 你也为船员准备了朗姆酒。 这很明智, 因为没有比轮班后一杯凉爽的朗姆酒更好的治疗所有疾病的方法了。 水手们喜欢并尊重给他们每日朗姆酒配给的船长。 你永远不想听到你的人问: ‘为什么朗姆酒没了? ’";
				link.l1 = "我们现在可以起航了吗? ";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "是的。 食物和朗姆酒。 如果船上没有足够的食物, 那是灾难性的。 总是准备比你认为需要的更多的食物。 你永远不知道航行会持续多久 - 死一般的平静或强风会破坏任何计划。 当食物耗尽时, 人们会叛变或饿死\n朗姆酒供应不那么关键, 但我强烈建议总是在船上保留一些, 没有比轮班后一杯凉爽的朗姆酒更好的治疗所有疾病的方法了。 水手们喜欢并尊重给他们每日朗姆酒配给的船长\n所以去购买我们需要的物资 - 至少一百箱食物和十桶朗姆酒。 你永远不想听到你的人问: ‘为什么朗姆酒没了? ’";
				link.l1 = "我想你是对的。 我会再去拜访商人。 ";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "你完成购买我们的食物和朗姆酒了吗, 船长? ";
			if (bOk)
			{
				link.l1 = "是的。 我们现在可以起航了吗? ";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "不, 我还在努力。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "是的, 船长。 我们可以起锚, 按你想要的向北前往瓜德罗普。 ";
			// belamour legendary edition -->
			link.l1 = "干得好, 福尔克。 没有你我做不到。 ";
			link.l1.go = "Folke_13";
			link.l2 = "好吧, 我们开始工作, 看看你是否值得这些钱。 ";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "那么把我设为领航员, 我会去甲板上我的位置。 ";
			link.l1 = "... ";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// < —legendary edition
			dialog.text = "那么把我设为领航员, 我会去甲板上我的位置。 ";
			link.l1 = "... ";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//在勒弗朗索瓦
			DeleteAttribute(pchar, "NoNavyPenalty"); // 因缺乏导航而惩罚
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> 复制 LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("欢迎 aboard 你的新军官! 按F4将他设为你的领航员。 ");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "准备起航, 船长! ";
			link.l1 = "... ";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "船长, 把我设为领航员, 否则我们很快会搁浅。 ";
				link.l1 = "知道了, 我现在就做。 ";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// 舵手

	// --> 海盗骗子
		case "Seabattle_pirate":
			dialog.text = "抱歉。 " +GetFullName(pchar)+ "? ";
			link.l1 = "正确。 我该为这次会面感谢什么, 先生? ";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "请允许我介绍自己 - " + GetFullName(npchar) + "。 我是塞萨尔.克雷格派来的。 你一定认识他。 他是勒弗朗索瓦酒馆的老板。 据他所知, 你即将出发前往瓜德罗普。 他想给你提供一些轻松的钱。 ";
			link.l1 = "嗯... 有趣! 塞萨尔.克雷格怎么变得如此消息灵通? ";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "很简单, 船长。 你的船是目前圣皮埃尔唯一的船, 任何有两只耳朵和一只眼睛的人都知道你是谁和你要去哪里。 在殖民地这里, 谣言飞得比海鸥还快。 那么你有兴趣听听我们的提议吗? ";
			link.l1 = "当然。 我从不反对赚钱。 ";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "这就对了, 伙计! 我看你有商业嗅觉。 交易是这样的。 塞萨尔急需一批葡萄酒送到瓜德罗普。 二百桶, 你的船舱可以轻松装下。 轻松的工作支付一万比索 - 塞萨尔很着急, 而你的船是港口唯一的船。 你必须承认, 这样有利可图的提议很少见。 ";
			link.l1 = "该死, 一万比索? 好吧, 我们成交! ";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "前往勒弗朗索瓦和塞萨尔谈谈。 他会处理一切。 你要做的就是在勒弗朗索瓦外面的海湾抛锚。 别让我失望, 伙计, 塞萨尔答应我如果说服你, 给我一千比索... ";
			link.l1 = "别担心, 算我被说服了。 一旦我准备好出发, 我会直接航行到勒弗朗索瓦。 ";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "万岁! 我去拿我的一千。 谢谢, 伙计! ";
			link.l1 = "不客气... ";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			chrDisableReloadToLocation = false;//打开位置
			npchar.location = "None";
		break;
	// 海盗骗子

	// 格里芬多军官
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// 圣皮埃尔防御登船队指挥官
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "船长, 登船队已组建并准备就绪! 等待你的命令! ";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//锁定界面
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "是, 船长! 准备好, 孩子们, 跟着船长! 嘿, 一二三四! ";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//锁定界面
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// 离开城市前在丛林的中断
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "该死, 法国增援! 列队! 洛伦佐, 去营地报警! 死吧, 你们这些混蛋! ";
			link.l1 = "... ";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// 真理卫士
		case "spanish":
			dialog.text = "你明白我无权透露此类信息吗? ";
			link.l1 = "你明白吗, 正是由于我及时干预, 圣皮埃尔才没有被西班牙人蹂躏? 我弟弟失踪了, 抛弃了教团! 他一定有原因。 我作为菲利普.德.潘西爵士的代表, 有权调查! ";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "好了, 好了, 德.莫尔先生。 我会回答你的问题。 先冷静下来。 现在问吧。 ";
			link.l1 = "米歇尔被看守之前发生了什么? ";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "米歇尔.德.蒙佩正在与一些海盗男爵谈判, 以安排托尔图加的政权更迭。 ";
			link.l1 = "这我已经知道了。 还有什么? ";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "他还在计划另一场针对西班牙人的行动。 具体来说 - 捕获一艘载有某些贵重货物的西班牙船只。 米歇尔应该把目标引诱到轻型护卫舰‘格里芬多号’的炮火下。 在他计划期间, 我们有很长时间没有看到他的踪迹。 \n但计划出了问题。 西班牙运输船没有到达, 米歇尔自己被当地渔民在勒马林峡的岸边发现, 半死不活。 看来行动失败了。 \n战争就是战争, 事情会出错。 米歇尔幸存下来是个奇迹, 但德.潘西骑士勃然大怒。 他指控米歇尔挪用教团的钱, 并将他监禁。 当然, 我们一句话也不信这些指控。 米歇尔是个诚实的人, 教团真正的骑士。 只有上帝知道是什么让总督发火。 也许, 德.潘西骑士会亲自告诉你? ";
			link.l1 = "可能。 这就是你知道的全部吗? ";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "不幸的是, 没什么可说的了。 你弟弟行动的细节只有他自己和德.潘西骑士知道。 我们是马耳他圣约翰骑士团的骑士。 我们执行命令。 ";
			link.l1 = "如果骑士如此信任米歇尔, 他之前执行秘密计划一定很成功。 你知道米歇尔成功执行过哪些行动吗? ";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "绝对是。 米歇尔.德.蒙佩最近的这次失败也是他的第一次失败, 这就是为什么我们对骑士的反应感到震惊。 不久前, 由于米歇尔的精心策划, ‘格里芬多号’捕获了一艘装满白银的西班牙珍宝大帆船。 仅此一项就应该弥补未来几十次失败。 然而, 你弟弟被捕了。 ";
			link.l1 = "我明白了。 你知道米歇尔为什么逃离圣皮埃尔吗? ";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "我怀疑米歇尔和德.潘西之间的人际冲突是他被捕的原因。 显然, 你弟弟担心骑士即使在他获释后也会继续迫害他, 所以采取了预防措施。 你知道吗, 德.莫尔先生 - 这里没有人责怪他的决定! \n这个人一直勇敢地为教团的利益工作, 但他们在他第一次失败时就把他扔进了恶臭的牢房, 而且是在他重伤的情况下! 一次甚至不算太坏的失败, 没有人死亡, 没有船只沉没! \n顺便说一句, 这次谈话是严格私下的, 我甚至不会在宣誓下重复我刚才说的话, 我们清楚了吗, 德.莫尔先生? ";
			link.l1 = "是的, 先生。 我已经忘记我们有过这次谈话。 告诉我, 圣皮埃尔的西班牙袭击可能是由教团袭击西班牙航运引起的吗? 也许就是你提到的那艘载银的西班牙大帆船? 卡斯蒂利亚人极其热心地寻找你们的基地... ";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "怀疑。 很少有人知道教团在加勒比海的存在, 我们对西班牙人的所有突袭都是精心策划的。 问问我们俘虏的西班牙军官, 他现在正在我们的炮台里冷却他炽热的卡斯蒂利亚脾气。 我们已经审讯过他了。 圣皮埃尔的袭击是一次普通的突袭, 由一个名叫拉蒙.德.门多萨.伊.里巴的西班牙大男爵组织, 目的是为了自己的利益和恐吓法属殖民地。 他还想讨好埃斯科里亚尔。 ";
			link.l1 = "我会和这个西班牙人谈谈。 我在哪里可以找到他? ";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "楼下, 在你弟弟被关押的同一个牢房里。 ";
			link.l1 = "我知道路。 我审问完西班牙人后回来。 我可能有一些额外的问题。 ";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//关闭位置
		break;
		
		case "spanish_10":
			dialog.text = "嗯, 这算什么! 你明白我不能释放那个俘虏, 对吧? 那个恶棍帮助领导了对圣皮埃尔的袭击! ";
			link.l1 = "军官, 这是重要证人。 对圣皮埃尔的袭击不是简单的掠夺。 唐.拉蒙.门多萨在寻找别的东西。 我们需要得到明确的动机。 那么你是把这个西班牙人交给我, 还是我必须向德.潘西要求许可? ";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "看在全能的上帝份上... 好吧, 带他走。 反正我也打算把这个混蛋像普通海盗一样在圣皮埃尔广场上吊死... 现在他是你的麻烦了。 确保他不会逃脱正义! ";
			link.l1 = "毫无疑问。 我会在德.潘西面前为这个西班牙人负责。 把这个俘虏戴上镣铐, 送到镇上码头我的长艇上。 ";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "很好, 船长。 ";
			link.l1 = "还有一件事, 军官。 米格尔.迪乔索这个名字你有印象吗? ";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "没有。 我从没听过。 你为什么问? ";
			link.l1 = "你确定吗? 那你在营地。 总督府或圣皮埃尔的任何地方, 都没见过叫这个名字的人? ";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "没见过。 在我来的地方, 我们对西班牙人评价不高。 ";
			link.l1 = "好吧。 不管怎样, 这也在意料之中。 要是太容易就奇怪了... 谢谢你, 军官! 你帮了大忙。 ";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "不客气... 你觉得呢, 德.莫尔先生, 你弟弟现在在哪里? ";
			link.l1 = "我也想知道答案。 我会找到的... 迟早会。 再见! ";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// 文森托派来的僧侣
		case "monk_vinsento":
			dialog.text = TimeGreeting() + "! 你是" +GetFullName(pchar)+ "船长吗? ";
			link.l1 = "是的, 是我。 有什么能为你效劳? ";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "问候你, 船长。 我是文森托神父派来的。 我有东西给你... ";
			link.l1 = "文森托神父? 我不再为大人工作了。 自从他派迭戈.德.蒙托亚的死党阿隆索.德.马尔多纳多来杀我之后就不了。 你可以给尊敬的神父捎个信: 他失败了。 ";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "等等, 船长。 文森托神父预料到你会有这种反应, 并提醒过我。 我向你保证, 大人没有任何恶意。 请读这封信, 非常非常重要。 ";
			link.l1 = "文森托神父没有恶意? 嗯。 也许他也没告诉你关于我和唐.德.马尔多纳多的事? 我该为什么相信你。 ";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "拿着这封信, 船长。 读完后自己做决定。 要知道, 整个基督教世界的命运都在你手中。 不要掉以轻心。 愿上帝保佑你, 为你指明正义之路! ";
			link.l1 = "好吧, 把信给我。 ";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "给你。 我祈祷你会做出正确的决定。 愿平安与你同在。 ";
			link.l1 = "... ";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// 阿德里安神父
		case "adrian":
			dialog.text = "问候你, 我的孩子。 愿主与你同在。 ";
			link.l1 = "愿主也与你同在, 阿德里安神父。 大人说你能提供护身符和药品。 ";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "是的, 当然。 我刚从圣地亚哥为你收到一批特殊物资。 这些是祝福过的护身符和治疗药水。 最重要的是, 还有一种罕见独特的奥梅托奇利酊剂, 能让你在战斗中无敌。 这些都是给你的, 我的孩子。 拿着, 看看主是仁慈的。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "如果你还需要任何 healing herbs, 我每天可以为你提供每样一小瓶。 我会按你的需要准备。 ";
			link.l1 = "感谢你, 阿德里安神父。 我会记住的。 ";
			link.l1.go = "exit";
			link.l2 = "太好了。 我现在就需要一些。 ";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "愿上帝保佑你, 我的孩子。 你想要什么? ";
			link.l1 = "我想购买一些治疗药水。 ";
			link.l1.go = "potion";
			link.l2 = "目前不需要, 我在准备旅行。 只是顺道来打个招呼, 看看你怎么样。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "当然, 我的孩子。 你需要什么药品? ";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "只要简单的治疗药剂。 ";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "一瓶强身健体的灵药。 ";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "一瓶解毒剂。 ";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "一瓶草药合剂。 ";
				link.l4.go = "potion4";
			}
			link.l5 = "抱歉打扰你, 神父。 我改变主意了。 ";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "一瓶治疗精华? 90比索, 我的孩子。 当然是材料费。 ";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "谢谢你, 神父。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "可惜我钱不够... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "一瓶强身健体的灵药? 500比索, 我的孩子。 ";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "谢谢你, 神父。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "可惜我钱不够... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "一瓶解毒剂? 200比索, 我的孩子。 ";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "谢谢你, 神父。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "可惜我钱不够... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "一瓶草药合剂? 900比索, 我的孩子。 ";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "谢谢你, 神父。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "可惜我钱不够... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "‘因为我要使你痊愈, 医治你的创伤, 这是耶和华说的。 ’这是你的药。 愿主与你同在! ";
			link.l1 = "谢谢你, 阿德里安神父。 ";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// 迪乔索的使者
		case "Dichoso_agent":
			dialog.text = ""+GetFullName(pchar)+" 船长? ";
			link.l1 = "是我。 你想干什么? ";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "我带来了米格尔.迪乔索船长的口信。 他说你认识他。 ";
			link.l1 = "听说过。 但从未有幸当面结识。 ";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "迪乔索船长想改变这一点。 他想和你当面谈谈。 他有个提议, 关于远征西班牙大陆深处, 寻找失落的印第安城市塔亚萨尔。 他说你的经验加上他的知识, 会带来令人满意的结果。 ";
			link.l1 = "这是他的原话? ";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "没错。 迪乔索船长会在圣克里斯托弗等你。 为了避免耳目, 他会在卡普斯维尔公墓的大墓穴里等你。 ";
			link.l1 = "嗯... ";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "迪乔索警告过我你会犹豫。 他让我向你保证, 无论你做什么决定, 谈判期间都不会伤害你。 他还说, 你在某个岛上找到的东西, 和塔亚萨尔的宝藏相比, 只是小菜一碟。 ";
			link.l1 = "是吗... 很有趣。 但为什么迪乔索船长不亲自来见我? 为什么派第三方? ";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "唐.迪乔索先去宝藏岛找你, 然后到这里, 现在去圣克里斯托弗, 希望在那里找到你。 你是菲利普.德.潘西的军官, 对吧? 我奉命在这里等你, 以防你到达布鲁维尔德。 ";
			link.l1 = "那就清楚了。 好吧。 我不会浪费时间, 我该去卡普斯维尔。 ";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// 迪乔索的墓穴使者
		case "Dichoso_crypt_agent":
			dialog.text = "终于见面了, " +GetFullName(pchar)+ "船长... ";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "米格尔.迪乔索在哪? 别耍花样。 我知道他是谁, 我想你也知道。 ";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "我想眼前这位就是米格尔.迪乔索本人吧? ";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "你猜对了, 船长。 我们一直在互相追踪, 不是吗? ";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // 读过圣塔-奎特里亚日志
			{
				link.l1 = "伙计, 我一看就知道你在撒谎。 你不是迪乔索。 我读过‘圣塔-奎特里亚号’船长的日志, 打听过他的长相。 你不像他, 脸上甚至没有骑兵剑留下的伤疤。 拜托, 就算演哑剧也该至少画一道! ";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "正是。 据我理解, 我们是来谈失落的塔亚萨尔城的? ";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "哈! 那没必要继续这场闹剧了。 米格尔警告过我你是个狡猾的家伙... ";
			link.l1 = "米格尔.迪乔索在哪? ";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "他不在这里。 我受权代表他与你见面和交谈。 ";
			link.l1 = "我不会和棋子说话。 我要见幕后的人。 他在哪? ! ";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "船长, 你不太友善啊。 你失态了。 ";
			link.l1 = "够了, 我明白了。 又是埋伏。 你们该想点新花样了。 ";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "哈哈, 又说对了, 伙计! 我的人就在通往地下墓穴的门后等你。 此外, 每个墓碑后面都藏着火枪手, 准备射击。 无处可逃。 尽管这把戏很老套, 但你还是钻进来了! 你对塔亚萨尔的渴望压倒了常识! ";
			link.l1 = "你选了个好地方打架, 人渣。 我不用走多远就能把你和你的强盗朋友埋了。 ";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "哈哈! 我喜欢你的机智! 和米格尔一样! 随便你怎么说, 你们是一路货色... 我会按他的命令行事 —尽快。 无痛地送你下地狱。 动手吧, 伙计们! ";
			link.l1 = "比你强的人都试过了。 替我向魔鬼问好, 无赖! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "你真的想去那座城? 我理解, 船长, 但我觉得这不是个好主意。 ";
			link.l1 = "那我们来谈什么? ";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "我不想和你长谈。 你来了, 对我来说就够了。 ";
			link.l1 = "够了, 我明白了。 又是埋伏。 你们该想点新花样了。 ";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// 登船队指挥官
		case "newcastle_officer":
			dialog.text = "等待你的命令, 船长! ";
			link.l1 = "我们穿过丛林前往卡普斯维尔公墓。 到达后, 不要进入公墓本身。 在门外占据射击位置, 我进去时仔细听着。 如果听到打斗声, 立刻冲进去。 ";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "等待你的命令, 船长! ";
			link.l1 = "我们穿过丛林前往卡普斯维尔公墓。 到达后, 不要进入公墓本身。 在小路上占据射击位置, 包围公墓, 我进去时仔细听着。 这整个计划都透着埋伏的味道。 一旦看到敌人, 立即进攻。 ";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "是, 船长! ";
			link.l1 = "好的。 前进! ";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; // 关闭遭遇战
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; // 关闭遭遇战
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; // 关闭遭遇战
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// 前往公墓前的位置
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// 前往墓穴
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "霍巴特船长! 根据我们间谍的情报, 叛军藏在这片庄园里。 给你五名龙骑兵。 搜查建筑, 逮捕任何里面的人! 别对这些人渣手下留情。 你是在以国王的名义行动! ";
			link.l1 = "是, 长官! ";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		// "结识印第安人"任务中的印第安人
		case "ZsI_ListKakao":
			dialog.text = "啧啧! 海之子! ";
			link.l1 = "呃... 什么? 你在跟我说话? ";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "对。 我是可可叶。 我和你有事, 海之子。 ";
			link.l1 = "我不知道可可长什么样, 也不知道你为什么叫这个名字。 但好吧, 快告诉我你需要什么。 ";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "啧啧! 你去镇上。 买两把手枪, 二十份火药和子弹。 给我。 有报酬。 海之子会高兴的。 ";
			link.l1 = "两把手枪和二十发子弹? 就这些? 你为什么不自己买? ";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "你不明白吗, 白皮? 谁会卖给我火器? ! ";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		// 只有完成"食人族"任务才会触发
			{
				link.l1 = "你知道, 我以前在马提尼克遇到过你们这种人... 食人族。 他们绑架了一个女孩和两个男人, 烤了其中一个吃了。 如果他们有枪, 我们就不会在这里谈话了。 ";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "可可叶, 你要火器干什么? 想杀人? ";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "咕-哦! 可可叶不是强盗, 我只和你们部落的战士战斗。 白皮来我们的土地, 把我们当奴隶。 可可叶自己战斗。 抓奴隶, 不好不坏, 就是这样。 印第安人。 白人, 没区别。 火器才有区别。 ";
			link.l1 = "可可叶, 你要火器干什么? 想杀人? ";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "为了战斗。 但要公平战斗。 白皮有火器, 印第安人没有, 这不公平。 印第安人有火器 —是保护自己, 免受白皮的不公对待。 羞辱或侮辱。 ";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "对, 船长。 白皮看不起我们。 ";
			link.l1 = "我注意到了。 在欧洲, 他们宣扬要教导印第安人真正的信仰, 宣扬我们如何在种植园和平共处... ";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "提钦吉图可能不懂船长的话, 但他懂可可叶。 他想复仇。 ";
			link.l1 = "似乎是这样... 你不想向我们最近的 captors 复仇吗? ";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "也许吧。 但提钦吉图不会那样做。 提钦吉图现在和你在一起。 提钦吉图有自己的想法。 会有太多流血, 白人流血, 印第安人流血, 太多苦难, 这不对。 ";
			link.l1 = "是的, 已经很糟了, 帮可可叶搞到枪只会更糟... 但他说得有道理。 而且我很快还要付船员薪水。 ";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "用你自己的脑子想想, 船长。 ";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "海之子废话真多, 像个长胡子的女人。 ";
			link.l1 = "谁? 给我解释清楚, 可可叶。 我也是白皮, 你却找我要武器打白皮。 这不矛盾吗? 为什么找我? ";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "我听到你和那个穿着奇怪的印第安人的谈话。 你和其他白皮不一样。 你理解提钦吉图, 我肯定你也理解可可叶。 ";
			link.l1 = "哦... 你用武器换什么, 可可叶? ";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "神的眼泪。 你们叫珍珠。 很多珍珠。 ";
			link.l1 = "我决定了, 可可叶。 在这等着, 我去武器商人那里, 买完就回来。 ";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "我决定了, 可可叶。 我刚好有你需要的东西。 给你。 ";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "我决定了, 可可叶。 我不想惹不必要的麻烦。 你别想从我这拿到火器。 走开。 ";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "啧啧! ";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "呃哦! 海之子有滑膛枪吗? 滑膛枪要付高价! ";
			link.l1 = "没有, 但我船上的加农炮行吗? 现在离开, 可可叶, 趁我们没被发现逮捕前。 ";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("你获得了180颗小珍珠");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "好交易! 海之子, 如果进丛林, 带把火器。 遇到印第安人, 有的谈。 ";
			link.l1 = "我会记住的。 再见, 可可叶。 ";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			ReturnOfficer_Tichingitu();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "可可叶会等。 ";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "呸, 看来这里聚集了一群土著! \n你想回监狱吗, 狗东西? \n你在这里干什么, 先生? ";
			}
			else
			{
				dialog.text = "站住! 你在这里干什么, 先生? ";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "嘿, 人渣, 你在等这位高尚的公民? ";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "所有白皮在我看来都一样。 但我从没见过这个。 你, 战士, 对我做你该做的。 烦死了。 可可叶准备好面对森林之灵了。 ";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "地狱在等你, 不是森林之灵。 ";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "船长, 你可以走了。 别挡我的路。 保护城市是严肃的事。 ";
			link.l1 = "我明白... 但这个印第安人呢? ";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "你对印第安人有什么兴趣, 先生? 不过... 好吧, 你刚从欧洲来\n巴黎怎么样? 他们还在踩死城市老鼠, 还是开始邀请它们参加圣餐了? 你看, 我们这里没有老鼠, 只有土著。 他们和海盗做生意, 袭击伐木工, 还吃人, 该死的\n三天前就有个蠢货把滑膛枪卖给了这种人。 猜猜怎么着? 那些混蛋杀了巡逻队的所有士兵, 顺便说一句, 巡逻队是我朋友和战友带领的。 我们找到了那个叛徒殖民者, 把他吊在太阳下晒干, 以儆效尤。 给印第安人提供火器! 这是叛国! 背叛法国! 我们追踪那只花脸猴子有段时间了, 他在各种事件中已经很眼熟了\n现在他将迎来迅速而应得的结局。 你可以走了, 船长。 别插手不关你的事。 你还没卷入这场战争... 还没... 或者已经卷入了? ! ";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(值得信赖) 你看, 军官... 我是查尔斯.德.莫尔船长, 法迪.莫斯科维特的客人。 我们对这个印第安人有一定兴趣... 所以我们别互相干扰职责, 好吗, 中尉? ";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "对新人的态度, 对土著的态度... 殖民者, 土著... 我还不太明白这一切, 但此刻, 中尉, 你的比喻可不太妙... 开战! ";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "你说得对, 中尉, 我没有。 再见。 ";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "咳咳! 明白了, 船长。 请代我向法迪先生问好。 小队, 继续巡逻! ";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "呃哦! ";
			link.l1 = "是啊, 连我都惊讶这办法奏效了。 给你东西, 可可叶。 ";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "海之子口才好。 救印第安人是大事! 大报酬! ";
			link.l1 = "哇, 收获真不少... 还有一块有孔的石头, 和某种护身符。 ";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("你获得了180颗小珍珠");
			Log_info("你获得了护身符‘卡斯卡维拉’");
			Log_info("你获得了护身符‘加法石’");
			Log_info("你获得了3份曼陀罗草药");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "海之子有滑膛枪吗? 滑膛枪要付高价! ";
			link.l1 = "没有, 但我船上的加农炮行吗? 现在离开, 可可叶, 趁我们没被发现逮捕前。 ";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "好交易! 海之子, 如果进丛林, 带把火器。 遇到印第安人, 有的谈。 ";
			link.l1 = "我会记住的。 再见, 可可叶。 ";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "呃哦! 糟糕的决定, 海之子。 你为什么要这么做? ";
			link.l1 = "呃... 五分钟前这似乎是对的... 现在我不太确定了... 。 毕竟我杀了自己人。 我现在该怎么办? 要是他们发现了怎么办? 该死! 该死! ";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "现在会有一场突袭。 士兵会杀死所有人。 两支巡逻队不会原谅。 可可叶会逃跑。 而你, 海之子... 为什么。 可可叶反正会死。 spirits 希望如此。 ";
			link.l1 = "哦... 我们的交易还算数吗? ";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "糟糕的决定, 海之子。 但谢谢你。 大报酬。 ";
			link.l1 = "考虑到所有情况... 报酬不算多... ";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("你获得了180颗小珍珠");
			Log_info("你获得了护身符‘卡斯卡维拉’");
			Log_info("你获得了护身符‘加法石’");
			Log_info("你获得了3份曼陀罗草药");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "海之子, 如果你活下来, 然后进入丛林, 带把火器。 遇到印第安人, 有的谈。 ";
			link.l1 = "我会为将来记住这点。 再见, 可可叶。 ";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//任务"树上的钱"中的商人巴比尔
		case "MOT_Barbie":
			dialog.text = "问候你, 查尔斯.德.莫尔船长。 我叫查尔斯.巴比尔。 能占用你一点时间吗? ";
			link.l1 = "德.莫尔船长... 正是! 请讲, 巴比尔先生。 ";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "很高兴认识同行, 尤其是与我同名的人! 船长, 我有个提议。 你看, 我需要一位护送者前往圣皮埃尔, 并且... ";
			link.l1 = "我知道圣皮埃尔! 但那只有两天路程! 而且我必须承认, 我在护送角色上还很生疏。 我一周前才接管这艘船。 ";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "欣赏你的诚实, 船长。 查尔斯, 请原谅我的随意, 但你正是我需要的人。 ";
			link.l1 = "嗯... 我记得不久前有个类似的提议。 结果在勒弗朗索瓦附近遭遇了海盗伏击。 ";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "我听说了那件事, 所以才找你\n首先, 我携带了相当贵重的货物, 总有掠食者潜伏。 然而, 你最近在勒弗朗索瓦附近击败海盗的胜利会让那里的恶棍们有所顾忌\n其次, 你与法迪.莫斯科维特的关联是有力的背书。 ";
			link.l1 = "很有说服力, 先生。 你提议为这份帮助支付多少报酬? ";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "这不是帮助, 船长, 而是互利的合作! 我会支付你四十枚金币, 及时护送我到圣皮埃尔。 ";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(值得信赖) 因为我正要往反方向航行, 先生, 我需要预付款。 ";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "不错的提议 - 我正好也往那个方向走。 成交! ";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "你说贵重货物? 遗憾的是, 先生, 我暂时已经受够了冒险。 ";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "很难拒绝如此认真的年轻人, 船长。 这是你的四十枚达布隆。 我们立即起航如何? 时间就是金钱。 ";
			link.l1 = "我们不会耽搁太久, 先生。 我们很快就起航。 ";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("你获得了40枚达布隆金币");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "太好了! 我立即准备出发! ";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "我理解, 船长。 我不打扰了。 再见, 日安。 ";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "感谢你出色的护送, 船长。 很高兴我们没有遇到任何事件。 ";
				link.l1 = "与你做生意很愉快, 先生。 现在请原谅, 我有很多事要处理。 ";
			}
			else
			{	
				dialog.text = "感谢你出色的护送, 船长。 很高兴我们没有遇到任何事件。 这是你的报酬 - 四十枚达布隆金币。 ";
				link.l1 = "与你做生意很愉快, 先生。 现在请原谅, 我有很多事要处理。 ";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("你获得了40枚达布隆金币");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "查尔斯... ";
			link.l1 = "怎么了, 查尔斯? 你看起来很困扰。 有什么不对劲吗? ";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "好吧, 既然你是个可靠的人, 又认识法迪... 听着, 商业是有风险的, 对吗? ";
			link.l1 = "如你所说。 ";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "我设法在瓜德罗普以低价从... 你知道的人那里收购了一批绳索。 我打算在圣皮埃尔迅速卖掉, 用所得资金购买咖啡再转卖到威廉斯塔德。 这似乎是个不错的计划。 ";
			link.l1 = "我不质疑你的诚信, 先生, 但这一切听起来相当可疑。 你谈论货物的样子就像在说黄金。 而我的船上堆满了这些绳索, 它们非常便宜。 ";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "查尔斯, 这些绳索质量上乘, 由优质大麻制成, 在莫斯科沙皇的工厂编织。 它们具有战略用途, 用于战舰的索具。 英国人垄断了与莫斯科的贸易路线, 禁止此类绳索的自由商业流通。 其他国家也在激烈争夺, 以确保欧洲造船厂的全部供应。 ";
			link.l1 = "所以, 这是走私? ";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "是的。 不幸的是, 去年我与圣地亚哥的走私者发生了争执。 我几乎忘记了, 但这些人关系密切且记仇。 给你一个建议: 避免激怒他们或违约; 这是你以后无法挽回的局面。 ";
			link.l1 = "谢谢, 但我对走私不感兴趣。 ";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "可惜! 诚实的贸易可以带来可观的利润, 但你永远无法积累巨额财富。 然而, 我并非毫无理由地与你进行这场相当危险的对话。 我提议你从我这里购买一批绳索。 当地走私者经常光顾酒馆, 他们会渴望购买这批货物。 想想看! 你今天就能获得可观的利润, 而无需出海。 ";
			link.l1 = "这批货物你要价多少? ";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "一万比索。 这是个适中数目, 将绳索转卖给走私者将获得丰厚回报。 ";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "如果错过这样的机会, 我永远不会原谅自己。 拿上银币, 确保货物迅速送到我的船上。 ";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "这是一次冒险的尝试, 朋友。 我们各让一步, 如何? 我用七千比索买下你的绳索。 ";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "这是一笔可观的数目, 先生。 我同情你的处境, 但我不能承担这样的风险。 ";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "感谢你, 查尔斯! 你使我免于财务破产! 货物将迅速且谨慎地运送\n允许我以 fellow 商人的身份给你一个建议: 一旦你雇佣了合适的出纳员, 在圣皮埃尔购买咖啡, 然后在威廉斯塔德出售获利。 当地资本为殖民地货物支付高价, 将其出口到欧洲获取巨额利润。 祝你事业顺利, 朋友! ";
			link.l1 = "再见, 先生。 ";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("你获得了30捆绳索");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "感谢你, 查尔斯! 你使我免于财务破产! 货物将迅速且谨慎地运送\n允许我以 fellow 商人的身份给你一个建议: 一旦你雇佣了合适的出纳员, 在圣皮埃尔购买咖啡, 然后在威廉斯塔德出售获利。 当地资本为殖民地货物支付高价, 将其出口到欧洲获取巨额利润。 祝你事业顺利, 朋友! ";
				link.l1 = "再见, 先生。 ";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("你获得了30捆绳索");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Skill Check Failed (31)", SKILL_COMMERCE); 
				dialog.text = "抱歉, 船长。 我的商品很重要, 需要认真对待。 大多数自由船长不敢交易战略物资。 遗憾的是, 这里没有讨价还价的余地。 ";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "如果错过这样的机会, 我永远不会原谅自己。 拿上银币, 确保货物迅速送到我的船上。 ";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "这是一笔可观的数目, 先生。 我同情你的处境, 但我不能承担这样的风险。 ";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "可惜! 再见, 船长。 ";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//迷你任务"折磨老鼠"
		//水手阿隆索
		case "Del_Alonso":
			dialog.text = "麻烦了, 船长。 ";
			link.l1 = "怎么了? ";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "我们的领航员被捕了, 被带到了当地地牢。 他们说是债务问题。 ";
			link.l1 = "什么, 又是这样? ! ";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "他是个麻烦精, 船长。 ";
			link.l1 = "多糟糕的时机! 没有领航员, 我们就被困在这里了。 我得再一次保释他! 我会和典狱长谈谈... ";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "请允许我发言, 船长? ";
			link.l1 = "说吧。 ";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "为什么要经历这些麻烦? 像他这样的人只会给船带来麻烦。 ";
			link.l1 = "我有选择吗? 几乎没有其他领航员可用, 所以我的选择相当有限。 ";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "没错, 顶级领航员很难找到, 但你还不需要大师, 只需要一个称职的。 你知道吗, 过去一周你的情况改变了? 不必再从底层找船员了。 现在人们谈论你如何击败那个海盗以及你的人脉。 船员也支持你, 船长, 我们喜欢你。 ";
			link.l1 = "这让人放心, 阿隆索。 船员对德鲁克有什么看法? ";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "你学得很快, 船长。 船员说虽然他是个有能力的军官, 对我们也公平, 但不值得麻烦。 一艘大商船刚解雇了它的军官们 - 也许去酒馆看看? 合适的人肯定在那里。 忘了德鲁克吧; 这是船员们的意见。 ";
			link.l1 = "感谢你的建议, 阿隆索。 我知道可以依靠你。 回船上值勤, 我处理完这里的事就来。 ";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//德鲁克
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "船... ";
			link.l1 = "我有无数问题, 但只问一个: 你一直和我在一起, 教我航海术, 怎么还能欠下新债? ";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "我羞愧地承认, 船长, 但在加入你的船员之前, 我就已经向各种放贷人借款了。 我的计划是低调行事, 在你的船上工作, 直到赚够钱还清所有债务。 但我犯了个错误, 离开船到圣皮埃尔和某个女人纠缠, 结果士兵就在她那里逮捕了我。 我在马提尼克没有欠下新债, 因为你已经帮我还了最后一笔, 我发誓! ";
			link.l1 = "你是个蠢货, 德鲁克, 你让我成了圣皮埃尔的笑柄! ";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "令人印象深刻, 福尔克。 谢谢你的轶事。 ";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "你会怎么做, 船长? 你能再一次保释我吗? 找到新领航员可不容易, 你知道... ";
			link.l1 = "先待在这。 我会做决定。 我可能会再去拜访银行家。 ";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//导航
			AddCharacterExpToSkill(pchar, "Commerce", 10);//贸易
			dialog.text = "你会怎么做, 船长? 你能再一次保释我吗? 找到新领航员可不容易, 你知道... ";
			link.l1 = "先待在这。 我会做决定。 我可能会再去拜访银行家。 ";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "我也没地方可去... ";
			link.l1 = "... ";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "船长, 谢谢你。 你还清了我的债务, 但现在我欠你更大的债 - 我的生命。 我真的很感激! 我向你保证, 在这个世界上你找不到比我更忠诚的人! ";
			link.l1 = "我想有些债务只能通过背负新债来偿还。 我们回去工作吧, 福尔克。 海上有很多事要做。 ";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "别忘了, 德鲁克。 下次我会直接毙了你。 ";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//导航
			AddCharacterExpToSkill(pchar, "Commerce", 10);//贸易
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//酒馆里的领航员。 标准对话, 但有一些变化 (为新手提供雇佣培训) 
		case "Del_shturman":
			dialog.text = "你需要军官吗, 船长? ";
    		Link.l1 = "军官? 你擅长什么? ";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "不, 我已经满员了。 ";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "我是这片水域最好的领航员。 我还懂一点医术。 我愿意帮你, 在你手下服役。 ";
			Link.l1 = "你想要多少报酬? ";
			Link.l1.go = "Del_price";
			Link.l2 = "你是什么专业的? ";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "唉, 我已经有领航员了。 ";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "我想我们可以商定4000比索。 ";
			Link.l1 = "这是不是有点多? ";
			Link.l1.go = "Del_trade";
			Link.l2 = "我同意。 认为自己是船员的一部分吧。 ";
			Link.l2.go = "Del_hire";
			Link.l3 = "你不值这个钱。 ";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "你改变主意了吗, 船长? 认为新领航员不会有坏处? ";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "差不多。 你想要多少? ";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "你能做什么? ";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "我已经满员了。 再见。 ";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "好吧... 我想我甚至可以同意2500比索。 你说呢? ";
				Link.l1 = "现在好多了。 你被录用了。 ";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "抱歉, 船长, 但我确实值我要的价。 如果对你来说太多, 那就去找别人吧。 ";
				Link.l1 = "好吧, 我同意。 我录用你。 ";
				Link.l1.go = "Del_hire";				
				Link.l2 = "那我就去这么做。 再见。 ";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "谢谢你, 船长。 你不会后悔你的选择。 ";
					Link.l1 = "希望如此。 ";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "我看你现金不足, 船长! 抱歉, 但我不赊账工作。 ";
					Link.l1 = "哦, 该死! ";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "谢谢你, 船长。 你不会后悔你的选择。 ";
					Link.l1 = "希望如此。 ";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "我看你现金不足, 船长! 抱歉, 但我不赊账工作。 ";
					Link.l1 = "哦, 该死! ";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "我刚喝完这杯酒, 船长, 然后就去船上。 别担心, 我会及时到那里。 ";
			Link.l1 = "好吧。 如果你迟到, 我会让你擦洗甲板! ";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//任务"折磨老鼠"
		//海特号船长
		case "TK_Kapitan":
			dialog.text = "好了, 好了! 我投降, 该死的! ";
			link.l1 = "你现在是我的俘虏, 但你很快就会在圣皮埃尔面对绞刑架。 ";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "就这样了... 你怎么知道在哪里找到我? ";
			link.l1 = "总督亲自向我通报了情况。 ";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "真是个混蛋! 他一定是知道了我的计划, 决定在他的巢穴前公开搞我, 给其他船员树立榜样! ";
			link.l1 = "再对大人说一句侮辱的话, 你去圣皮埃尔的旅程就会迅速而难忘。 ";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "呃? 我不是在说你, 伙计。 我说的是好人雅克\n该死, 谣言是真的! 巴尔巴宗意识到我正在成为威胁, 所以把我交给总督, 让我远离他的道路。 这就是为什么你有我的确切位置 - 并且当场抓住了我, 哈哈! ";
			link.l1 = "你在妄想。 马提尼克总督不会屈尊与海盗头目交易! ";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "是啊, 对。 也许不是直接的, 但我认为他和巴尔巴宗做了交易。 这对他来说很方便: 一个危险的海盗被绞死, 报告看起来不错, ‘军事行动费用’也合理了。 我曾为你服务过, 知道那里的情况。 你呢? 你在驻军服役吗? ";
			link.l1 = "我为我的国家服务, 这次谈话结束了。 欢迎来到禁闭室。 ";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "等等, 伙计。 我不是卡斯蒂利亚人, 我今天出海不是为了掠夺法国商人。 我有原则, 该死的! 我们做个交易, 好吗? ";
			link.l1 = "你在浪费口舌, 海盗。 把你关进禁闭室。 ";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "试图逃避绞刑? ";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "我在这里有可靠的线索, 如果你放我走, 我会分你一份。 我的命只值几千银币, 但我可以让你赚更多 - 而且免税。 ";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "这是个诱人的提议... 尽管海盗行为并不完全是我的专长。 ";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "我不是海盗! ";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "由你决定, 伙计。 你想成为幸运儿还是有原则的穷船长。 如果你想要真正的钱和自由, 你就得什么都尝试一下。 抓住任何机会。 ";
			link.l1 = "你确实有说服人的方法... ";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "呃... 我想我会带你去圣皮埃尔。 那似乎是正确的做法。 ";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "去你的! ";
			link.l1 = "... ";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "那么, 我们成交了吗? ";
			link.l1 = "是的。 告诉我你的线索是谁, 你就可以走了。 ";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "有个聪明的英国人, 亨利号的, 一艘三桅帆船。 他即将完成他的小贸易航行, 从法国种植园获取货物, 高价运往威廉斯塔德。 他很快就要离开马提尼克前往库拉索。 这是个轻松的工作 - 没有护航, 而且这艘三桅帆船装载着贵重物品, 却牺牲了防御。 他花了太长时间, 所以谣言四起。 我的建议, 伙计? 不要在酒馆害羞。 请当地人喝几杯, 他们会泄露一些秘密。 ";
			link.l1 = "为什么没有护航? ";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "否则英国人怎么在库拉索安静地做生意? 英国和荷兰之间正在公开战争, 获得贸易许可证既麻烦又昂贵。 ";
			link.l1 = "但法国和英国之间没有战争。 如果我攻击一艘中立船只, 会有什么后果? ";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "如果你谨慎行事, 就没有后果。 船员肯定会在最近的港口吹嘘你的英雄事迹, 但只要你不经常捕食英国或荷兰船只, 你应该没事。 打着法国旗号接近亨利号。 用葡萄弹装填你的大炮, 靠近, 升起黑旗, 发射几轮齐射, 然后登船。 很简单, 伙计。 ";
			link.l1 = "我们走着瞧。 我会遵守我的诺言, 释放你。 不要给我后悔的理由。 ";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "我不会的。 祝你狩猎顺利, 伙计。 ";
			link.l1 = "... ";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//任务"会见迭戈"中桌边的迭戈和吉约姆
		case "VsD_DiegoAndErnat":
			dialog.text = "... 我会处理你的赌博问题。 嘿! 振作点, 伙计! 要么振作起来, 要么我亲自给你点教训。 ";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "先生, 抱歉, 但你有点碍事了。 ";
			link.l1 = "好的, 当然。 祝你们一天愉快, 先生们。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_DiegoInTaverna_3");
		break;
		
		//任务"会见迭戈"中的吉约姆.迪比阿
		case "VsD_GiumDyubua":
			dialog.text = "德.莫尔船长! 等等! ";
			link.l1 = "怎么了, 中尉? ";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "我差点追不上你。 出了点... 小麻烦, 船长。 真是一团糟! ";
			link.l1 = "请喘口气, 冷静一下。 ";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "对, 对。 听着, 我们装完大炮后, 货舱里还有空间吗? ";
			link.l1 = "我还不太熟悉, 所以不完全确定, 但我想应该有。 ";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "太好了! 指挥部希望全力支持贝洛港的行动, 所以下令额外运送两百份火药到‘勇猛号’。 可能看起来不多, 但几轮额外齐射就能扭转战局! ";
			link.l1 = "很好, 中尉。 我准备尽我的职责。 装上火药 - 我完全不介意。 ";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "谢谢你, 船长。 我马上通知装货船员。 幸好他们还没完成‘" + PChar.Ship.Name + "’的装货。 祝你任务顺利! ";
			link.l1 = "谢谢, 尽管到目前为止一直很混乱。 再见, 中尉。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//任务"会见迭戈"中的福尔克或阿隆索
		case "VsD_FolkeAlonso":
			dialog.text = "天啊, 船长! 谢天谢地你没事! ";
			link.l1 = "到底怎么了? ! 我的船怎么了? ! ";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "我不知道, 船长! 我刚在和最近认识的当地女人道别... 哦该死! 欧仁妮! ";
			link.l1 = "她死了, " + npchar.name+ "。 抱歉, 但我们需要集中精力看看有没有船员受伤。 ";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "我们才刚认识... 啊! 该死! 报告船长: 爆炸发生时大部分船员在岸上 - 幸好。 伙计们在下次远航前享受了些岸上休假。 但船上的值班人员... 恐怕无人生还。 看看周围! 碎片甚至在这个码头都伤了人或杀了人! 我们俩安然无恙真是奇迹。 ";
			link.l1 = "那船呢? 她没事吧? ! ";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "她没事? ! 抱歉, 船长。 很难确定, 但爆炸似乎发生在上层甲板, 不是下面。 我没看到明火, 看起来我们躲过了重大损坏。 ";
			link.l1 = "... ";
			link.l1.go = "VsD_FolkeAlonso_5";
			
			VsD_AfterVzriv_1();
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_2");
		break;
		
		case "VsD_Komendant":
			dialog.text = "究竟怎么回事, 船长? ! ";
			link.l1 = "我也在问同样的问题, 上校! ";
			link.l1.go = "VsD_Komendant_1";
			VsD_AfterVzriv_3();
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "注意点, 德.莫尔! 你从海军接受了这份工作, 装载了重炮 - 王室财产, 具有战略重要性! 你明白这些大炮对整个行动的意义吗? ! 你的疏忽让近四百人和一艘法国战舰陷入了危险! 你在这里面临叛国罪的审判! ";
			link.l1 = "冷静点, 上校! 奇迹般地, 我的船似乎幸存了下来, 你宝贵的货物也大部分完好... 大部分。 ";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "你说大部分是什么意思? ! ";
			link.l1 = "我不能保证最后由你的一名中尉装载的两百份火药没有受损。 它们本应最后装载, 很可能就是它们爆炸了。 ";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "这是什么鬼话, 查尔斯? 什么中尉? 什么火药? 我没下过这样的命令! ";
			link.l1 = "这名中尉一定是你驻军的。 我没问他名字, 但他似乎知道这次行动。 ";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "啊, 该死! 看来卡斯蒂利亚人也倾向于玩阴的... 我会处理这个不幸的情况, 船长。 但你还有工作要做: 你确定你的船适航吗? ";
			link.l1 = "她还在漂浮, 但肯定需要大修。 ";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "没时间了, 船长。 立即起航完成任务。 风险太高, 不能拖延。 ";
			link.l1 = "看在上帝的份上, 我们至少能有一天吗? 当地造船厂可以进行必要的维修! 我的船员呢? ! 肯定有伤亡! ";
			link.l1.go = "VsD_Komendant_6";
			VsD_AfterVzriv_4();
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "你没注意到吗, 造船厂着火了。 我们还在确定是故意的还是爆炸的附带结果。 我只能向你保证, 你的伤员会得到医疗护理, 王室将承担埋葬死者的费用。 ";
			link.l1 = "你是认真的? 这就是你能提供的最好条件? ";
			link.l1.go = "VsD_Komendant_7";
			VsD_AfterVzriv_5();
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "船长, 法国急需你的帮助。 我会给你提供木板, 如果你操作得当, 到达牙买加时你的船几乎可以完全修复。 ";
			link.l1 = "抱歉, 但什么木板? 为什么是牙买加? ";
			link.l1.go = "VsD_Komendant_8";
			VsD_AfterVzriv_6();
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "你的船员可以在海上用木板进行紧急维修 - 这是主要的维修材料。 牙买加离你前往贝洛港的路线之一相当近。 如果你不浪费时间, 可以在那里完成维修并招募满船员。 ";
			link.l1 = "那好吧。 我立即起航, 上校。 ";
			link.l1.go = "VsD_Komendant_9";
			
			VsD_AfterVzriv_7();
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_8");
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "为什么这么急, 亲爱的? ";
			link.l1 = "亲爱的, 我现在没时间管这个。 你没看到发生了什么吗? ";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "哦, 当前的麻烦很可怕, 但我从你手上能看出, 地平线上还有更多麻烦正在出现。 ";
			link.l1 = "即使不看我的手, 任何人都能看到这一点, 而且我的手还戴着手套。 好吧, 我陪你玩: 如今避免灾难的代价是什么? ";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "我没有那种力量, 帅哥。 即使有, 我也负担不起。 但我仍然可以帮你... 修你的船。 亲爱的, 这船状态很糟糕。 ";
			link.l1 = "我从没听说过你们吉普赛人有做木匠的野心。 ";
			link.l1.go = "VsD_Tsyganka_3";
			
			VsD_Final_1();
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "你呢, 亲爱的, 你自己也不是木匠。 你以为只有木板就能修船吗? 除非你有一位木匠大师, 否则它们只会增加你的负担... ";
			link.l1 = "或者? ";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "有一个当地人尊敬的强效护身符。 木材会听从它的意愿, 即使不熟悉木工的人戴上它也会变得熟练。 亲爱的, 只要一千比索, 它就是你的了。 ";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "很好, 成交。 我需要所有能得到的帮助。 ";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "我没时间玩你的巫术。 平静地走吧, 女巫, 别多管闲事。 ";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Net");
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Da");
			Log_info("你获得了护身符‘船蛆’");
		break;
		
		//公民类型角色对暴露武器的提醒
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的守法公民。 我必须请你不要像强盗一样露着刀刃到处走。 ", "先生, 请注意, 法律明确规定城内男子不得持械走动。 ");
			link.l1 = LinkRandPhrase("好吧。 ", "行。 ", "如你所愿... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}