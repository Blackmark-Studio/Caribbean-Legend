// LSC任务的其他NPC对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-----------------------------------鲨鱼帮守卫在补给舱--------------------------------------
		case "PantryGuard":
			dialog.text = "吼吼, 看看这是谁, 伙计们! 来拜访我们的小偷! 偷别人箱子的贼! 过来! 还有你, 伙计, 别装傻充愣, 拔出你的刀 --这么近的距离我不会失手的... 查德会很高兴见到你的! ";
			link.l1 = "但我... 我刚到这里! ";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "你说得对, 哈哈! 你刚陷入了真正的麻烦, 伙计... 而且你逃不掉了。 现在, 交出武器跟我走! ‘塔尔塔罗斯’号上的笼子等你很久了, 小偷! ";
			link.l1 = "... ";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("几小时后... ", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //转动时间
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "别想从这里偷任何东西。 我会盯着你的。 ";
			link.l1 = "非常感谢。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "去做查德让你做的事。 别多说废话! ";
			link.l1 = "好的, 我这就去... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "嘿! 你他妈的在那里做什么? 混蛋! 现在你完蛋了! ";
			link.l1 = "... ";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // 禁止搜索尸体
		break;
		
		// ----------------------------------马塞洛.西克洛普--------------------------------
		// 如果在船舱等待
		case "Cabin":
			dialog.text = "嘿, 你他妈的在这里做什么, 该死的? 巴比尔呢? ";
			link.l1 = "我们的朋友阿道夫... 病了。 他不能来开会, 所以让我在他的船舱里坐一会儿等你。 ";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "嘿, 你他妈的在这里做什么, 该死的? ";
			link.l1 = "我们的朋友阿道夫... 病了。 他不能来开会, 所以让我代替他。 可以这么说。 ";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "听起来很奇怪... 他早上还好好的, 现在就病了。 ";
			link.l1 = "嗯, 你知道事情就是这样。 突然发烧... ";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "哦, 我不喜欢你的脸。 你在撒谎。 巴比尔绝不会把这次会议交给别人。 说吧, 混蛋, 你是谁, 你对他做了什么? ";
			link.l1 = "你知道, 你的脸也不好看。 我已经告诉过你巴比尔病了。 你是反应慢还是要我重复? 他应该给你钥匙和... ";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// 在刻瑞斯铁匠号号 - 拯救玛丽
		case "mary":
			dialog.text = "该死! 你还是找到我了... ";
			link.l1 = "是的, 人渣! 你休想碰她! 准备受死吧! ";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// 鲨鱼帮信使 (选项N) 
		case "SharkCureer":
			dialog.text = "你是" +GetFullName(pchar)+ "吗? ";
			link.l1 = "是的, 是我。 怎么了? ";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "鲨鱼派我来的。 他请你尽快去见他。 他有重要的事找你。 ";
			link.l1 = "这么急? ... 好吧, 我马上就去‘圣奥古斯丁’号。 ";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// 如果一天内不来, 可设置鲨鱼死亡计时器
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // 鲨鱼的节点
		break;
		
		// 鲨鱼帮信使 (选项M) 
		case "SharkCureer_3":
			dialog.text = "你是" +GetFullName(pchar)+ "吗? ";
			link.l1 = "是的, 是我。 怎么了? ";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "呃, 我找你找得好累... 鲨鱼和莱顿.德克斯特。 他们请你立刻去见他们。 事情很重要, 快点。 ";
				link.l1 = "是吗? 好吧, 我马上就去‘圣奥古斯丁’号。 ";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "呃, 我找你找得好累... 莱顿.德克斯特上将请你立刻去见他。 事情很重要, 快点。 ";
				link.l1 = "上将? ";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "是的。 作为二把手, 鲨鱼死后他成了我们的上将。 ";
			link.l1 = "我明白了。 好吧, 我马上就去‘圣奥古斯丁’号。 ";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// 代替卡珀的狱警
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "啊, 你来了... 我记得你, 你是最后一个和奇米塞特说话的人。 是你杀了他吗? ";
				link.l1 = "少废话! 你很清楚不是我。 我觉得你知道凶手是谁。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "唉, 整天待在这里太无聊了! 如果你能带点朗姆酒和牌来, 伙计, 我们可以赌一把... ";
				link.l1 = "抱歉, 伙计, 我没时间。 也许以后吧。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "我有几个猜测, 是的, 但没有证据。 没人看到那个黑人的死。 岛上到处都是流言, 说我们鲨鱼帮的人负责, 还说某个新手受上将的命令干的。 明白了吗? 所以现在别去里瓦多斯那里。 他们太生气了。 ";
			link.l1 = "好的。 我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "唉, 整天待在这里太无聊了! 如果你能带点朗姆酒和牌来, 伙计, 我们可以赌一把... ";
			link.l1 = "抱歉, 伙计, 我没时间。 也许以后吧。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// 商店里代替阿克塞尔的助手
		case "AxelHelper":
			dialog.text = "你想要什么, 伙计? ";
			link.l1 = "嗯。 你在这里做什么? 阿克塞尔呢? ";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "阿克塞尔很忙。 他在和唐纳德.格林斯彭开会, 会一直待到今天结束。 所以如果你想买东西 --明天早上再来找他。 我在看店, 别想偷东西... ";
			link.l1 = "我知道了。 他今天为什么开会? 好吧, 我明天早上再来。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("我已经告诉你所有事情了。 明天再来。 ", 
				"别烦我, 伙计。 滚开! ", 
				"别让我生气, 混蛋! ",
				"走开!! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("好的。 ", 
				"知道了, 知道了。 ",
				"闭嘴... ", 
				"什么? ! ", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// 白男孩的母亲 - 阿格尼丝.克里斯蒂安森
		case "agnes":
			dialog.text = "你想要什么, 先生? ";
			link.l1 = "嗯... 对不起, 夫人。 请原谅我的无礼和失礼, 但我想问你一件事: 你认识一个叫奥莱.克里斯蒂安森的人吗? ";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "再说一遍你刚才说的... 奥莱.克里斯蒂安森? 奥莱? ! ";
			link.l1 = "是的。 因为他头发的特殊颜色, 人们也叫他白男孩。 你认识他吗? ";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "我认识他? ! 他是我儿子, 已经失踪十年了! 你知道他在哪里吗, 先生? 快告诉我他在哪里, 他怎么样了? ! ";
			link.l1 = "冷静点, 夫人, 别这么担心。 他很好。 他在我的船上。 他只需要上岸到这里来。 ";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "哦... 看来上帝终于听到了我的祈祷! 你无法想象他失踪时我有多担心! 这都是我的错! 你在哪里找到他的? 他不是普通的孩子... 嗯, 你一定知道我在说什么。 ";
			link.l1 = "我知道。 是的, 他很特别。 而且他没变。 看起来他还是个孩子。 我在一个岛上找到他的。 我们偶然相遇。 他向我要一颗白色珠子... 该死的! ... 一颗珍珠。 ";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "珍珠? 哦, 上帝! 珍珠就是我儿子失踪的原因! 都怪那条该死的项链! ";
			link.l1 = "奥莱... 真的因为扯断你的珍珠项链离家出走了吗? ... 冷静点, 夫人, 别哭! ";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "是的, 是真的。 奥莱在码头扯断了我的项链, 所有的珍珠都掉进了水里。 我对他和我已故的丈夫发了那么大的火... 惩罚了他。 奥莱第二天就不见了。 你无法想象我为此有多自责! ";
			link.l1 = "奥莱收集珍珠很多年了。 他称之为白色珠子。 他把它们都收集起来给你, 并让我带你去见你。 除了红屋顶的房子, 我没有其他细节。 但我终于找到你了。 ";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "收集珍珠? ! 哦, 上帝! 我对我可怜的孩子太愧疚了! 我... 而他一直在收集珍珠! 哦! ";
			link.l1 = "我想我最好叫你的儿子来, 夫人。 他非常想见你。 他说你看到珍珠会很高兴。 但我想你高兴的原因不是因为珍珠... ";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "先生... 请你行行好。 把我的奥莱带给我。 我想拥抱他, 请求他的原谅... ";
			link.l1 = "当然, 夫人。 他们会马上带他来这里。 ";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("一小时后", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //转动时间
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "那么, 夫人, 这是你的儿子 - 奥莱.克里斯蒂安森。 你认出他了吗? ";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // 转移pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "先生... 对不起, 我还没问你的名字... " +pchar.name+ "? ";
			link.l1 = "" +GetFullName(pchar)+ ", 夫人。 " +GetFullName(pchar)+ "船长。 ";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "船长, 你无法想象我对你有多感激! 你帮助了他, 把他带到了这里。 你让我重新活了过来! 我会为我的孩子做一切, 我会把他多年来缺失的所有爱都给他。 ";
			link.l1 = "我为你高兴, 夫人。 也为奥莱高兴。 他是个好孩子, 在艰难的情况下帮助了我。 他有一颗善良的心。 我认识一个被奥莱从死神手中救出来的人。 ";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "先生, 我坚持请你明天或任何你有空的时候来这里。 我想为你对我儿子和我所做的一切表示感谢。 现在我只是有点... 嗯, 你知道的。 ";
			link.l1 = "我知道, 夫人。 ";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "明天再来这里。 我会适当地奖励你为我儿子和我所做的一切好事。 ";
			link.l1 = "好的。 我一定会来拜访你! ";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//解锁界面
			chrDisableReloadToLocation = false;//打开地点
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// 从乘客中删除奥莱
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "啊, 你来了, " +GetFullName(pchar)+ "先生! 来, 坐下... ";
			link.l1 = "谢谢! 奥莱怎么样了? ";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "哦, 你无法想象你做了什么! 你是母亲眼中的救星... 我欠你的, 我会永远为你祈祷。 ";
			link.l1 = "你让我脸红了, 夫人... ";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "我一直知道谦逊是使高尚的人高尚的品质... 我为你所做的准备了礼物。 是的-是的! 甚至不要拒绝! 来, 拿着这个... 首先, 有一个装满达布隆的箱子。 其次, 拿着这个魔法护身符, 他们称之为圣甲虫\n这是我丈夫的, 我相信他会很高兴知道他的宝藏将属于这样一位高尚的船长, 是你把我的儿子还给了我。 我丈夫是个木匠, 他常说圣甲虫加快了他的工作\n我希望这枚戒指能很好地为你服务。 毫无疑问, 你值得佩戴它! 最后, 拿着我的裁缝工具。 这是一套很好的工具。 你可以用它制作很多好东西。 ";
			link.l1 = "哦! 这些对任何船长来说都是真正宝贵的礼物! 谢谢, 夫人。 ";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("你收到了一个装满达布隆的箱子");
			Log_Info("你收到了‘圣甲虫’护身符");
			Log_Info("你收到了一套裁缝工具");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "我想让你知道, 我家的大门随时为你敞开。 你在这里总能找到食物。 一瓶好酒和任何你想要的东西。 ";
			link.l1 = "感谢你的美言, 夫人。 我下次来这个小镇时会很高兴见到你。 ";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "一定得来! ";
			link.l1 = "现在我得走了。 再见, 祝你好运! ";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "啊, " +GetFullName(pchar)+ "船长! 很高兴见到你! 来坐, 我给你倒杯酒... ";
			link.l1 = "谢谢! 我只是想问候你, 知道你和奥莱都好。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 啊? 小偷! ", "看看那个! 我一沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会得逞的! ");
			link.l1 = "该死! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子? 你不会得逞的! ";
			link.l1 = "愚蠢的女孩! ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}