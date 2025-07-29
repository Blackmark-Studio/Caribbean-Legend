void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // 伐木工. 特殊变量.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
			Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
			{
				arDis = GetAttributeN(arRld, i);
				if (arDis.go == npchar.location)
				{
					arDis.disable = true; // 关闭房屋入口
					break;
				}
			}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
			Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
			{
				arDis = GetAttributeN(arRld, i);
				if (arDis.go == npchar.location)
				{
					arDis.disable = true; // 关闭房屋入口
					break;
				}
			}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//------------------------------- —农夫 ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = PCharRepPhrase(LinkRandPhrase("镇上拉起了警报, 看来我也该拿起武器了... ", "说不定城里的卫兵正在追你? ", "你在这里找不到庇护所, 但可能会在肋骨间发现几英寸的冷钢! "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("恶棍", "无赖") + "? 卫兵已经闻到你的气味了, 你跑不远的, " + GetSexPhrase("肮脏的海盗", "你这个海盗婊子") + "! ", "肮脏的凶手! 卫兵!!! ", "我不怕你, " + GetSexPhrase("爬虫", "婊子") + "! 很快你就会在我们的堡垒被绞死, 你跑不远的... "));
				link.l1 = PCharRepPhrase(RandPhraseSimple("看来你活腻了... ", "看来在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "的市民没有安宁的生活! "), 
					RandPhraseSimple("去死吧! ", "呵, 这将是你生命的最后几秒... "));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "我警告过你。 现在你可以自己决定是否想惹麻烦。 ";
					link.l1 = "呵! ";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "你在我家里做什么, 恶棍? ! 你有十秒钟离开这里! ";
					link.l1 = LinkRandPhrase("呵, 看来这里也认识我! ", "我的名声已经先到了... ", "嗯, 我知道了。 ");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("欢迎来到我家。 你有什么事吗? ", 
						"我能为你做什么? ", 
						"嗯... 我能为你做什么? ",
						"抱歉, 如果你没有事, 请不要打扰我... ", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("不, 只是四处看看, 认识新朋友... ", 
						"不, 没什么特别的... ",
						"没什么... ", 
						"好吧, 如你所说。 ", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("抱歉, 晚上不是拜访的最佳时间, 因此请你立刻离开我的家! ", 
						"我已经说过, 时间很晚了。 请离开。 ", 
						"我不想显得无礼, 但我坚持请你立刻离开我的家! ",
						"该死的, 怎么回事? ! 卫兵! 有小偷! ", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("好吧, 我知道了... ", 
						"是的, 稍等... ",
						"好吧, 别这么激动。 ", 
						"什么小偷? ! 闭嘴! ", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "哦, 请允许我自我介绍 --" + GetFullName(npchar) + "。 我们很高兴你成为我们的客人。 在这个镇上, 待客之道是受到尊重的。 ";
			link.l1 = GetFullName(pchar) + ", 请多关照... ";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是" + GetSexPhrase("小偷, 我看见了! 卫兵, 抓住他", "小偷, 我看见了! 卫兵, 抓住她") + "!!! ", "真不敢相信! 我一转身 —你就翻我的东西! 抓小偷!!! ", "卫兵! 抢劫! 抓小偷!!! ");
			link.l1 = "啊啊啊, 魔鬼!!! ";
			link.l1.go = "fight";
		break;
		// ------------------------------- —农妇 ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = PCharRepPhrase(LinkRandPhrase("我警告你, 我丈夫很快就会回来! 你最好现在就离开我家! ", "我认为你逃不掉的! 要知道我丈夫很快就会回家! ", "我丈夫很快就会回家! 你必须马上离开! "), 
					LinkRandPhrase("可惜我丈夫不在家... 出去! 现在!!! ", "肮脏的凶手, 马上离开我家! 卫兵! ", "" + GetSexPhrase("真是个恶棍", "真是个污秽") + "... 我丈夫很快就会回来, 他会看看你的血是什么颜色的! "));
				link.l1 = PCharRepPhrase(RandPhraseSimple("哦, 你丈夫... 哦哦... 我好害怕... ", "呵... 你知道吗, 姑娘, 你丈夫只是一个人... 你不会希望他死在你面前吧? "), 
					RandPhraseSimple("闭嘴, 婆娘, 不然我把你开膛破肚... ", "我想待多久就待多久。 如果你知道好歹, 就闭上嘴... "));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "我警告过你。 出去, 否则你会后悔的! ";
					link.l1 = "真是个愚蠢的婆娘... ";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "你在我家里做什么, " + GetSexPhrase("恶棍", "无赖") + "? ! 如果你十秒内不离开, 我就叫卫兵了! ";
					link.l1 = "真是个愚蠢的婆娘... ";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("很高兴在我们家见到你。 我叫" + GetFullName(npchar) + "。 有什么可以为你效劳的吗? ", 
						"你还在这里? ", 
						"嗯, 打扰一下, 你不觉得该离开了吗? ",
						"请不要辜负我们的款待。 ", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar) + "为你效劳。 我来这里没有特别的原因, 只是想认识一下。 ", 
						"还在这里。 ",
						"嗯, 我不知道... ", 
						"好吧。 ", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("哦, 我的天, 你为什么在这个时候闯进我家! 你真的吓到我了... 请明天再来拜访吧! ", 
						"请离开我们家! " + GetSexPhrase("", "我是有夫之妇! ") + "", 
						"我最后一次请你离开我们家! ",
						"但这里发生了什么? ! ", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("别害怕, 我不会伤害你。 ", 
						"好吧, 别这么激动。 ",
						"我这就走。 ", 
						"怎么了? ", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "我们总是欢迎客人。 只是不要在这里待太久, " + GetSexPhrase("因为我是有夫之妇... ", "因为我有很多事要做... ") + "";
			link.l1 = "哦, 是的, 当然... ";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "原来是这样? 我把你当客人欢迎, 你却在翻我们的箱子? ! 卫兵! ";
			link.l1 = "闭嘴, 婊子! ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "我友好地请你离开我们家, 但你就是不听! 够了! 救命! 卫兵! ";
			link.l1 = "闭嘴, 你这个愚蠢的女人! 你疯了吗? ! ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//------------------------------- —仓库管理员 ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("镇上拉起了警报, 看来我也该拿起武器了... ", "说不定城里的卫兵正在追你? ", "你在这里找不到庇护所, 但可能会在肋骨间发现几英寸的冷钢! "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("恶棍", "无赖") + "? ! 卫兵已经闻到你的气味了, 你跑不远的, " + GetSexPhrase("肮脏的海盗", "婊子") + "! ", "" + GetSexPhrase("肮脏的", "肮脏的") + "凶手! 卫兵!!! ", "我不怕你, " + GetSexPhrase("爬虫", "婊子") + "! 很快你就会在我们的堡垒被绞死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("看来你活腻了... ", "看来在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "的市民没有安宁的生活! "), 
					RandPhraseSimple("去死吧! ", "呵, 这将是你生命的最后几秒... "));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("欢迎! 我叫" + GetFullName(npchar) + "。 这里由我负责, 所以别想带走任何东西... ", 
				"规矩点, 记住我在盯着你。 ", 
				"只要你不偷看箱子, 你可以待在这里。 反正我一个人也无聊... ",
				RandPhraseSimple("哦, 我太无聊了! ", "该死的, 做什么好呢? 在这里太无聊了! "), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("好的, 别担心。 ", 
				"当然! ",
				"我知道了... ", 
				"是啊, 这听起来是个问题。 ", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("镇上拉起了警报, 看来我也该拿起武器了... ", "说不定城里的卫兵正在追你? ", "你在这里找不到庇护所, 但可能会在肋骨间发现几英寸的冷钢! "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("恶棍", "无赖") + "? ! 卫兵已经闻到你的气味了, 你跑不远的, " + GetSexPhrase("肮脏的海盗", "婊子") + "! ", "" + GetSexPhrase("肮脏的", "肮脏的") + "凶手! 卫兵!!! ", "我不怕你, " + GetSexPhrase("爬虫", "婊子") + "! 很快你就会在我们的堡垒被绞死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("看来你活腻了... ", "看来在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "的市民没有安宁的生活! "), 
					RandPhraseSimple("去死吧! ", "呵, 这将是你生命的最后几秒... "));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("这里由我负责, 所以别想带走任何东西... ", 
				"规矩点, 记住我在盯着你。 ", 
				"只要你不偷看箱子, 你可以待在这里。 反正我一个人也无聊... ",
				RandPhraseSimple("哦, 我太无聊了! ", "该死的, 做什么好呢? 在这里太无聊了! "), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("好的, 别担心。 ", 
				"当然! ",
				"我知道了... ", 
				"是啊, 这听起来是个问题。 ", npchar, Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			// 打开造船厂的门 (工业间谍任务) 
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "听着, 伙计, 我想和你开诚布公地谈谈。 ";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> 为玩家提供货物仓库
			if(CheckAttribute(NPChar, "Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "我有一个诱人的提议, 也许你会感兴趣。 ";
					link.l7 = "真的吗? 好吧, 我听听。 ";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar, "Storage.Activate"))
					{
						link.l7 = "带我去仓库, 我想看看它的状况。 ";
						link.l7.go = "storage_0";
						link.l8 = "我决定退租仓库, 不再需要了。 ";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar, "Storage.NoActivate"))
						{
							link.l7 = "你提到过一个仓库, 它还空着吗? ";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// < —ugeen
			}		
		break;
		
		//------------------------------- —仓库租赁 ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "我们有一个适合作为仓库的地方。 你想以合理的价格租用吗? 想想看, 你将有自己的仓库来存放贵重货物... ";
			link.l1 = "你说仓库? 是的, 确实很诱人... 它足够大吗? 租金是多少? ";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "即使作为港口仓库, 它也相当宽敞, 可以容纳... 50000公担货物。 我可以为你提供货物保管服务, 每月" + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "。 " +
				"这包括我的人守卫。 防潮和灭鼠。 你觉得如何? 哦, 还有保密, 这是不言而喻的。 ";
			link.l1 = "好的。 我可以看看吗? ";	
			link.l1.go = "storage_rent2";
			link.l2 = "太贵了。 我打赌它还被水淹了, 到处都是老鼠。 ";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "当然, 当然。 但是... 我需要提前支付一个月的租金。 ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "你真是... 精于经商, 必须说。 给你钱... 我租这个棚子。 ";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "你真是... 精于经商, 必须说。 好吧, 我去取钱。 ";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "如你所愿。 如果你改变主意, 告诉我。 记住, 这样好的仓库不太可能长期空置... ";
			link.l1 = "没问题。 如果需要, 我会告诉你。 ";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "还有租金, 你还欠我" + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "。 ";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "好的, 我现在付租金。 ";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "我稍后再来。 ";
					link.l1.go = "exit";
				}
			}		
			else
			{ // 伐木工。 如果忘了带船就没办法.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "去吧。 ";
				link.l1 = "谢谢。 ";
				link.l1.go = "storage_2";
				}
				else
				{
				dialog.text = RandPhraseSimple("船长, 你的船在哪里? 你打算如何搬运货物? ", "我没看到你的船停在港口。 你到底打算如何装货? ");
				link.l1 = RandPhraseSimple("哦.. 我完全忘了! ", "该死的, 对! ");
				link.l1.go = "exit";
				break;
				}			
			}
			link.l2 = "不, 我改变主意了。 ";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "不, " + GetSexPhrase("先生", "女士") + ", 仍然空着, 在等你。 我就知道你最终不会拒绝我的提议。 ";
			link.l1 = "很好。 我租了。 ";
			link.l1.go = "storage_1";
			link.l2 = "不, 只是想到... ";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "你应该记得, 我需要提前支付一个月的租金。 ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "当然, 我记得。 给你。 ";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "该死的。 好吧, 我去取钱。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "已经要走了? 真可惜, 这真是个条件优越的好地方。 我向你保证, 在加勒比海其他地方你找不到这样的交易。 ";
			link.l1 = "我说过, 我要退租。 难道你要我为储存空气付费吗? 你可以另找租户。 ";
			link.l1.go = "storage_4";
			link.l2 = "你说在加勒比海其他地方找不到? 好吧, 那我再保留一段时间。 但必须说, 租金有点太高了。 ";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "还有租金, 你还欠我" + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "。 ";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "好的。 ";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // 伐木工。 如果没有船就无法取货
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "收拾你的货物, 我会关闭仓库。 ";
				link.l1 = "好的。 ";
				link.l1.go = "storage_6";
				}
				else
				{
				dialog.text = RandPhraseSimple("船长, 你的船在哪里? 你打算如何搬运货物? ", "我没看到你的船停在港口。 你到底打算如何装货? ");
				link.l1 = RandPhraseSimple("哦.. 我完全忘了! ", "该死的, 对! ");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//------------------------------- —仓库租赁 ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "呵! 好吧, 我们谈谈。 ";
			link.l1 = "我需要在晚上没人的时候进入造船厂。 ";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "看看你! 嘿, 卫兵, 这里有个小偷!!! ";
				link.l1 = "什么小偷? 我只是想谈谈! ";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "哇! 看看你, " + GetSexPhrase("伙计", "姑娘") + "。 带着这样的请求来到造船厂的仓库! ";
				link.l1 = "我需要进入造船厂本身, 我根本不在乎你的仓库。 ";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "但你为什么需要它? ";
			link.l1 = "有需要。 而且我愿意为此付费... ";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "嗯, 这就对了... 好吧! 给我" + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + ", 我会在第二天把造船厂的门打开。 ";
			link.l1 = "太贵了。 那我只好不用了... ";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "好吧, 我同意。 拿你的钱, 按我们说的做。 ";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "别担心, 会办妥的。 ";
			link.l1 = "希望如此... ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			// 移除close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			// 设置恢复close_for_night的计时器
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}