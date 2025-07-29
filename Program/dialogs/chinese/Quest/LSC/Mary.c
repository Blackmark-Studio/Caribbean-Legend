// 玛丽.卡斯帕 - 相互爱慕与军官
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你需要什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------刺杀鲨鱼 - 变体R --------------------------------
		// 在阿道夫的船舱里对话
		case "Cabin":
			dialog.text = "马塞洛, 我认识他。 他是里瓦多斯和海盗的朋友。 阿道夫绝不会和他合作。 闻闻空气... 你闻到火药味了吗? 墙上还有血迹... 他杀了阿道夫, 现在想骗我们! 他一定是为舰队司令工作的! 杀了他! ";
			link.l1 = "... ";
			link.l1.go = "Cabin_fight";
		break;
		
		case "Cabin_fight":
			chrDisableReloadToLocation = true;//关闭地点
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			DialogExit();
			sld = characterFromId("Marchello");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			{
				for (i=1; i<=3; i++)
				{
					sld = characterFromId("CyclopGuard_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// 在街道上
		case "Town":
			dialog.text = "哦, 打扰了... 我能请你帮个忙吗? ";
			link.l1 = "嗯。 我总是乐于帮助一位美丽的女士。 有什么问题吗? ";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "是这样的, 我从塞西莉.加拉德那里买了一个装满各种金属片的箱子。 她住在'夏娃号'上。 于尔根答应为我锻造一件好东西, 好吧... 我买了, 是的, 但我没法把它拿给他。 我太蠢了! \n也许你能帮我把箱子从'夏娃号'搬到'埃斯梅拉达号'上的独角鲸区? 求你了, 我会非常感激! ";
			link.l1 = "就这样? 当然, 小姐, 我帮你。 这不算什么麻烦。 ";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "谢谢你! 我带你去箱子那里。 ";
			link.l1 = "女士... ";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "我们到了... 现在告诉我, 混蛋, 钥匙在哪里? ! ";
			link.l1 = "哇! 哈, 看来不需要帮助了... 玛丽。 ";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "聪明的男孩, 嗯? 少废话, 该死的! 钥匙在哪里? 交出来, 否则你会后悔! ";
			link.l1 = "这么粗鲁! 如此美丽的女孩却有张坏嘴。 什么钥匙? ";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "你从阿道夫.巴比尔那里拿走的钥匙。 别否认 —有人看见你离开他的船舱。 阿道夫死了, 那是你干的... 现在, 把钥匙给我! ";
			link.l1 = "原来果然是你... 那是个错误, 女孩, 一个非常大的错误! ";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "你说什么? ... 该死的, 你不是普通的强盗! 他为舰队司令工作! 抓住他, 伙计们! ";
			link.l1 = "... ";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------刺杀鲨鱼 - 变体N --------------------------------
		case "caroline":
			dialog.text = "查德, 就是他! 该死的, 他带了个帮手来! 伙计们, 杀了他们所有人! ";
			link.l1 = "... ";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			// 鲨鱼加入战斗
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// 设置4名强壮的独角鲸
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// 玛丽和查德加入战斗
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------刺杀鲨鱼 - 变体M --------------------------------
		case "mary":
			dialog.text = "你来得正是时候... 我自己根本对付不了他们... 呼! 说实话, 我以为我完蛋了! ";
			link.l1 = "你战斗得像瓦尔基里! 我从未见过如此美丽的女孩如此勇猛... ";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "哈哈, 你是个绅士, 不是吗: 手里还拿着剑就开始赞美。 谢谢你的帮助。 你救了我的命, 没错! 介绍一下自己吧, 绅士, 我以前没见过你。 你是新来的? ";
			link.l1 = "我叫"+GetFullName(pchar)+", 但美丽的女士可以叫我"+pchar.name+"。 我是新来的吗? 嗯... 是的。 ";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "我看得出来, 要是周围有这么帅的男人, 我肯定会注意到。 我叫玛丽, 玛丽.卡斯帕。 不过他们叫我红玛丽。 因为我是红头发, 没错。 ";
			link.l1 = "很高兴认识你, 玛丽... ";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "哦, 我加倍高兴... 考虑到要不是你我已经死了! 那个混蛋查德没开玩笑。 真是个卑鄙小人! 我真蠢, 把下层的门开着。 你就是这样进来的, 对吗? ";
			link.l1 = "是的。 我在岛周围游泳, 想找个地方上岸。 ";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "我明白了。 这扇没锁的门差点让我送命。 于尔根亲自为我锻造了锁, 没有合适的钥匙你打不开, 撬锁也没用。 而且, 要是有人想闯进来, 我不会坐以待毙 —我手枪的四发子弹会在门或人身上留下四个洞, 哈哈! \n但该死的查德不会放过我。 他已经派杀手来'说服'我站在他那边, 他绝对是认真的。 要不是你, 我就答应了。 我得在这里被围困着, "+pchar.name+", 没错! 感谢上帝我预料到了, 我有足够的物资, 而且于尔根是我的邻居, 我没和他吵架。 ";
			link.l1 = "玛丽, 为什么不告诉我更多你的问题? 我知道你需要我的帮助, 但我完全听不懂你说的话。 ";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "是的, 我需要帮助, 没错! 我现在孤身一人。 我和唐纳德吵架了, 然后发现查德是个恶棍。 哦, 抱歉, 我又说个不停了。 好吧, 我告诉你我的处境... ";
			link.l1 = "记住我是新来的, 所以还不太明白。 这个查德是谁, 为什么要'说服'或杀你? 唐纳德是谁? ";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "查德是舰队司令鲨鱼.多德森船员中的海盗, 是'塔塔罗斯号'上的狱卒... ";
			link.l1 = "等等! 你说什么? 鲨鱼.多德森? 他在这里? ";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "你肯定是今晚到的, 所以还不知道。 鲨鱼不在这还能在哪? 我的麻烦是从他几个月前到这里开始的。 不过, 我承认这都是独角鲸帮和里瓦多斯的错。 当鲨鱼带着船员来到这里时, 他想建立基地, 但我们的人和里瓦多斯人真的不喜欢这个主意。 他们在夜里袭击了鲨鱼的双桅船, 放火烧了它\n他们最好别这么做! 鲨鱼的船员全是魔鬼, 不是人, 没错。 首先, 他们摧毁了敌对船只, 然后登陆并开始了真正的屠杀。 独角鲸帮撤退了, 里瓦多斯人则飞快地逃跑了。 最后, 海盗占领了圣奥古斯丁, 那里有岛上大部分的物资和补给, 然后他们拿下了塔塔罗斯\n鲨鱼囚禁了我们的领袖艾伦.米尔罗, 他也是我的... 我的密友, 还有里瓦多斯的巫师奇米塞特。 他把他们像野兽一样关进塔塔罗斯的笼子里。 从这里游到塔塔罗斯很容易, 我设法去看过艾伦几次。 在那里我遇到了查德.卡珀, 鲨鱼派他当狱卒。 我请求查德释放艾伦, 答应给他钱, 但他害怕对抗舰队司令\n然后艾伦在监狱里被谋杀了。 查德告诉我是鲨鱼干的, 没错。 于是我去找唐纳德, 他在艾伦之后被选为领袖, 要求立即攻击海盗, 但他拒绝了, 说那些海上魔鬼对我们来说太强大了。 就在那时我让他滚蛋\n我的人在这件事上毫无用处, 所以我和卡珀做了交易, 这个混蛋想取代鲨鱼的位置。 我们有个计划 —把舰队司令从他的堡垒引诱到某个阴暗的地方杀了他。 我们还找到了一个有好步枪的狙击手。 他可以从'愤怒号'的桅杆上射杀舰队司令\n现在有趣的是, 前天晚上我去了塔塔罗斯, 想和查德说些关于我们计划的重要事情。 游到船边时, 偶然听到查德和两个独角鲸说话。 原来不是鲨鱼杀了艾伦。 是查德干的。 然后他秘密散布关于舰队司令参与的流言\n他因为我杀了他。 首先, 他想把我当床上的玩物。 其次, 他想利用我来摆脱鲨鱼 —他知道我会一直寻求复仇。 你能想象吗? 真是个懦夫! ";
			link.l1 = "是啊, 我见过这种人... ";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "混蛋更糟糕! 他... 我找不到词来形容那个怪物! 那次我走开了, 第二天早上找到他, 把我对他的想法全说了出来。 是的, 我告诉他我不会再参与他对抗舰队司令的阴谋。 ";
			link.l1 = "显然他不喜欢... 那是愤怒之下做的, 玛丽。 你应该更谨慎。 ";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "我忍不住, 我不能闭嘴。 那个混蛋杀了艾伦, 还想利用我达到他的肮脏目的! 卑鄙! 是的, 当然, 他生气了, 威胁说如果我不改变主意, 就派他的独角鲸朋友来对付我。 我笑了, 没想到独角鲸敢对我动手。 ";
			link.l1 = "看来你错了。 ";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "是的, "+pchar.name+", 我低估了查德, 高估了自己。 他找到了敢在一个女孩自己的船舱里攻击她的混蛋。 现在我该怎么办? 我不能相信任何人。 甚至不能相信自己人。 这两个是独角鲸, 我都认识, 没错。 只要查德还活着 —我就有危险, 他肯定会派更多人来\n我不敢出去, 我们找的刺杀鲨鱼的狙击手可能从里瓦多斯领地射杀我, 然后轻松逃脱。 我不会去找唐纳德, 他不会听\n舰队司令? 我不能解释我在准备刺杀他中的角色! 他会把我送到'塔塔罗斯'的牢房里腐烂, 我确定! 该死, 我被困住了。 我要在这里装满枪支, 直到物资耗尽, 然后... 我不知道我会怎么样! ";
			link.l1 = "好吧, 在这种情况下, 我别无选择, 只能帮你, 嗯? 你的情况反正符合我在这里的计划... ";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "你打算帮我? 但怎么帮? 你要杀了查德? ";
			link.l1 = "计划的一部分, 当然。 ";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "听着, "+pchar.name+", 我欣赏你的意图, 但查德不在你的范围内。 他是舰队司令最信任的朋友之一, 即使你找到他 —鲨鱼的海盗也会杀了你, 他们不知道真相, 没错。 ";
			link.l1 = "冷静点。 我反正要和鲨鱼谈谈。 ";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "所以你也是海盗? ! 告诉我关于你自己的事, 看看你: 闯进我的地方, 救了我的命, 答应帮忙, 还长得帅, 但我对你一无所知! ";
			link.l1 = "好吧... 我不是海盗, 但目前为某个海盗男爵扬.斯文森工作。 我来这里找纳撒尼尔.霍克。 你听说过他吗? ";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "不, 他是谁? ";
			link.l1 = "他是另一个著名的海盗。 可惜你没见过他, 他一定在某个地方。 我也在找鲨鱼, 但没想到在这里找到他。 ";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "但你怎么到这里的? 你看起来不像沉船的幸存者。 ";
			link.l1 = "你为什么认为我是沉船来的? ";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "那是唯一能到这里的方式。 只有鲨鱼不知怎么航行到了这里。 ";
			link.l1 = "好吧, 不止鲨鱼一个, 如你所见。 ";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "所以, 你有船? 太好了! ";
			link.l1 = "别这么快兴奋, 玛丽。 我是通过... 乘三桅帆船来的, 但它沉到海底了。 ";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "啊... 好吧, 就像我说的 —沉船。 你现在和我们一样被困在这里了, 没错。 ";
			link.l1 = "玛丽, 让我告诉你我的计划。 你提到查德打算杀鲨鱼。 我需要鲨鱼活着, 扬和我打算让他成为海盗首领。 所以我必须警告他, 因为从你的故事来看, 我确定查德无论有没有你的帮助都会尝试。 ";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "是的, 可能。 他有足够的人手做到... ";
			link.l1 = "这意味着我的首要目标是赢得鲨鱼的信任并救他。 然后, 我会正式找到查德。 你有什么证据证明他的意图吗? ";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "我有他的信, 是这些... 地板上的白痴之一带来的。 里面有威胁和一些舰队司令可能感兴趣的细节。 等等! 那我呢? 鲨鱼会发现我和查德合作过! ";
			link.l1 = "玛丽, 你打算永远拿着手枪坐在这里, 对每个人隐藏你美丽的脸庞吗? 你真的认为我是想让一位美丽女士死的白痴之一吗? 先给我看看信, 让我看看能做什么... ";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "给。 你觉得怎么样? ";
			link.l1 = "等等... (阅读)。 是的, 看来查德是地球上特别的混蛋。 这封信足以让鲨鱼渴望亲自给查德套上绞索。 别担心女士, 我会确保鲨鱼丝毫不怀疑你。 他反正会忙于处理查德。 ";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "你会那么做吗? 向我保证, 没错! 向我发誓你不会背叛我! ";
			link.l1 = "玛丽, 我向你发誓, 我不会背叛你。 别担心, 我救你不是为了让那种事发生\n查德肯定不会让你安宁, 你知道得太多了。 在他死之前待在这里。 ";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "是的, 我会待在这里。 我不想被狙击手射杀或被背后捅刀。 ";
			link.l1 = "好女孩。 关上所有的门, 包括下层的。 你只有一把钥匙吗? ";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "不。 还有另一把。 你想要吗? ";
			link.l1 = "是的。 你信任我吗? ";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "好吧, 如果刚刚救了我命的绅士背叛我, 那也没理由活下去了... 拿去吧。 ";
			link.l1 = "别害怕, 美人! 我不会让你失望的。 等我解决了这堆烂摊子就来看你。 希望不会太久。 ";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "没关系, 我可以在这里坚持几个星期。 ";
			link.l1 = "太好了。 那我不浪费时间了。 我会把尸体弄出去, 然后和鲨鱼谈谈。 他在'圣奥古斯丁号'上, 对吗? ";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "是的, 他总是在那里。 从你来的路出去 —我不会让你踏上'刻瑞斯铁匠号'的上层甲板。 ";
			link.l1 = "有趣, 为什么? ";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "因为如果你死了就没法帮我了。 这是独角鲸帮的领地, 他们会把你当外人杀掉。 ";
			link.l1 = "嗯... 知道了。 好吧, 玛丽, 再见。 等安全了我就回来。 ";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "你随时都可以来看我, 我没问题。 (咯咯笑)";
			link.l1 = "再见, 美人! ";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // 打开出口
		break;
		
		case "mary_wait":
			dialog.text = "你好, "+pchar.name+", 有好消息给我吗? 你没事吧? ";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "与舰队司令的问题解决了。 他对追捕你没兴趣, 查德的背叛是唯一让他烦恼的事。 ";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "还没有, 玛丽。 但我会尽我所能。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "哦, 感谢上帝! 谢谢你, 我不会忘记的, 没错! 至少没有来自舰队司令的威胁了。 那查德呢? 鲨鱼做了什么? ";
			link.l1 = "我们说服里瓦多斯人攻击他。 莱顿.德克斯特把守卫从'塔塔罗斯号'调走, 把钥匙给了黑埃迪。 黑人救了他们的巫师奇米塞特, 但没能杀死查德。 他们杀了他两个独角鲸朋友, 但他跑了, 躲在某个地方。 ";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "该死! 那意味着我现在必须更加小心... ";
			link.l1 = "冷静点, 玛丽。 我肯定他有更多需要担心的威胁人物。 他可能知道是谁挑动里瓦多斯人攻击他的。 他会不惜一切杀死鲨鱼, 而不是你。 ";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "你真的这么认为吗? 查德不是那种轻易放手的人。 啊, 我太累了, 再也不怕了... ";
			link.l1 = "嗯。 我没想到你是那种容易受惊的女士。 ";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "哈! 我不是吗? 我不怕面对面战斗, 但坐着等死? 我很害怕, "+pchar.name+", 没错!... ";
			link.l1 = "相信我, 玛丽: 卡珀现在满脑子都是舰队司令, 目前... 我需要你的建议。 ";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "我的建议? 什么样的建议? ";
			link.l1 = "埃迪找到了两封查德写的信。 读一下, 也许你知道他在搞什么鬼。 毕竟你和查德一起策划过。 ";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "给我... (阅读)。 阿克塞尔是我们在'埃斯梅拉达号'上的商人, 没错。 查德不知为何想从他那里买威士忌。 奇怪! 查德只喝朗姆酒, 他说威士忌是'农民的私酿酒'... ";
			link.l1 = "那第二封信呢? ";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "马塞洛? 马塞洛.独眼龙, 前皇家猎人。 他是我拒绝离开这个船舱的主要原因。 ";
			link.l1 = "他是你雇的狙击手吗? ";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "是的。 马塞洛能在四十英尺外射中苍蝇, 尽管他少了一只眼睛, 没错。 他的任务是用长管施图岑步枪从圣弗洛伦蒂娜号的船首斜桅或愤怒号的平台上击落鲨鱼... ";
			link.l1 = "看来查德决定干掉鲨鱼。 但夏娃号呢? 塞西莉? 酒? ";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "夏娃号是中立船只, 塞西莉是塞西莉.哈拉德, 一个有趣的老妇人, 住在那里。 她不久前从圣弗洛伦蒂娜号搬到那里。 奥雷莉.伯廷是她的朋友。 在我出生前她们就一起住在这里了, 没错。 ";
			link.l1 = "嗯。 胡说八道。 两个大男人躲着一个老妇人一起喝一桶威士忌。 垃圾... 查德, 现在不是喝酒的时候! ";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "我已经告诉过你他不喝威士忌。 只喝朗姆酒, 有些事情不对劲。 ";
			link.l1 = "好吧, 不管怎样。 你知道在哪里能找到独眼龙吗? ";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "不知道。 他非常私密。 他每天在外环射鸟, 没人知道他在哪里睡觉。 他以前经常拜访里瓦多斯人。 ";
			link.l1 = "真倒霉... 好吧, 我去和阿克塞尔谈谈。 也许他能解释清楚。 再见, 玛丽! 关上门! ";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"! 请找到查德。 快点, 自从上次袭击后我就没睡过。 ";
			link.l1 = "等等, 亲爱的。 我会尽力的。 ";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // 标志指向商店 - 寻找威士忌
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! 他怎么到这里的? 他来是为了... ";
			link.l1 = "是的, 来杀你, 玛丽。 他通过于尔根的船舱, 用绳子爬下来的。 ";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "啊! 我真蠢, 忘了那条路! 肯定是查德教他的, 没错! ";
			link.l1 = "很可能。 我勉强赶到。 他是来找你的。 ";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "而我在睡觉。 他可能瞬间杀了我... 但你怎么知道他在来的路上? ";
			link.l1 = "我就是... 我就是知道, 玛丽。 ";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "你又救了我, 帅哥。 你总是在完美的时间出现, 没错。 你怎么做到的? ";
			link.l1 = "嗯, 我不知道。 我的众多才能之一。 你的围困结束了 —查德.卡珀死了, 他所有的朋友也死了。 独眼龙是他腐烂 crew 中最后一个。 ";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "真的吗? 是真的吗, "+pchar.name+"? 你没骗我, 对吗? ";
			link.l1 = "一点也不。 呃, 过去几天的事让我需要休息一下... ";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "我现在终于可以自由呼吸了! 谢谢你... 非常感谢! 你是我的英雄, 没错! ";
			link.l1 = "我喜欢这个称呼, 做你的英雄。 很高兴你终于安全了。 ";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "那么? ";
			link.l1 = "怎么了, 美人? ";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "你为什么站在那里? 来吧, 绅士。 ";
			link.l1 = "做什么? ";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "你真是个绅士... 过来抱抱我, 最后吻我一次, 你想这样, 我看得出来, 没错! ";
			link.l1 = "玛丽... ";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // 传送前必须告别的属性
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // 从外面打开刻瑞斯
		break;
		
		case "happy_10":
			dialog.text = "别离开我... ";
			link.l1 = "我在这里, 玛丽, 亲爱的... ";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "一切都可以等。 舰队司令可以等, 你的海盗可以等。 今晚只属于我们俩, 没错! ";
			link.l1 = "当然... ";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "之后的每个夜晚也是... ";
			link.l1 = "是的, 玛丽。 ";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("第二天早上... ", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------和玛丽在刻瑞斯铁匠号 ------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // 这个节点甚至比和独角鲸吵架更重要
			{
				dialog.text = ""+pchar.name+"! 你回来了... 没有她。 所以她没能把你从我身边夺走! ";
				link.l1 = "玛丽, 你的怀疑是没有根据的。 你是我的唯一。 我的思绪和梦境中总是有你。 ";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", 你为什么和独角鲸帮打架? 我其实住在他们的领地, 别忘了我也是其中一员。 求你了, 去找法西奥讲和吧。 ";
				link.l1 = "好吧, 玛丽, 我会照你说的做。 ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // 找到雕像 - 告别
			{
				dialog.text = ""+pchar.name+", 你有心事。 怎么了? ";
				link.l1 = "玛丽, 我需要和你谈谈。 ";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! 所有独角鲸都在谈论你! ";
				link.l1 = "真的吗, 亲爱的? ";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // 礼物
			{
				dialog.text = ""+pchar.name+"! 这把大刀太不可思议了! 再次感谢! .. 我也想送你一份礼物。 当然, 比不上你的, 但我希望你收下, 没错。 ";
				link.l1 = "玛丽, 礼物的价值不重要... 谢谢你, 我的爱人";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // 早晨
			{
				dialog.text = "今天很忙吗, "+pchar.name+"? 祝你好运! ";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "玛丽, 我们今天得去见于尔根。 ";
					link.l3.go = "narval";
				}
				link.l1 = "谢谢, 玛丽! 我毫不怀疑。 ";
				link.l1.go = "exit";
				link.l2 = "不, 玛丽。 我想在这里休息一下。 你介意吗? ";
				link.l2.go = "rest_morning"; // 休息
			}
			else
			{
				dialog.text = "好吧, "+pchar.name+", 你好吗? 还是像往常一样在岛上跑来跑去? ";
				link.l1 = "是的, 玛丽。 有很多事情要做... ";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) // 晚上
			{
				dialog.text = "已经是晚上了, "+pchar.name+", 你说的什么事? 待在这里, 我们喝点东西放松一下, 没错! 可以等到早上! ";
				link.l1 = "(笑着) 当然, 亲爱的, 不用多说... ";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "玛丽, 我们今天去酒馆吧! ";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "玛丽, 亲爱的, 我现在很忙。 我稍后回来。 ";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) // 白天
			{
				dialog.text = "别忘了晚上来看我。 你敢躲着我, 没错! ";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "玛丽, 我们今天得去见于尔根。 ";
					link.l3.go = "narval";
				}
				link.l1 = "当然, 玛丽, 怎么会? 我肯定会来看你。 ";
				link.l1.go = "exit";
				link.l2 = "不, 玛丽。 我今晚想在这里休息。 你没事吧? ";
				link.l2.go = "rest_afternoon"; // 休息
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "你在说什么? 已经是晚上了! 不, 你哪也别去, 你要留在这里, 和我一起, 没错! ";
			link.l1 = "(笑着) 好吧, 我留下... ";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "甚至不要... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// 去酒馆
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("好主意, "+pchar.name+", 没错! 我同意! ","好的, 我们走, "+pchar.name+"! 桑乔有很好的葡萄酒收藏, 有很多选择! ","哦, 我很高兴, 没错! 桑乔的酒馆总是很有趣, 他有很棒的葡萄酒选择! ");
			link.l1 = "我们走! ";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> 休息
		case "rest_morning":
			dialog.text = "当然, "+pchar.name+"? 当然, 休息一下, 没错! ";
			link.l1 = "我会待到中午... ";
			link.l1.go = "rest_day";
			link.l2 = "我会待到晚上... ";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "当然, "+pchar.name+"? 当然, 休息一下, 没错! ";
			link.l1 = "我会待到晚上... ";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// < —休息
		
	//--> 如果很快通过传送门离开
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // 这个节点甚至比和独角鲸吵架更重要
			{
				dialog.text = ""+pchar.name+"! 你回来了... 没有她。 所以他没能把你从我身边夺走! ";
				link.l1 = "玛丽, 你的怀疑是没有根据的。 你是我的唯一。 我的思绪和梦境中总是有你。 ";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", 你为什么和独角鲸帮打架? 我其实住在他们的领地, 别忘了我也是其中一员。 求你了, 去找法西奥讲和吧。 ";
				link.l1 = "好吧, 玛丽, 我会照你说的做。 ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // 礼物
			{
				dialog.text = ""+pchar.name+"! 这把大刀太不可思议了! 再次感谢! .. 我也想送你一份礼物。 当然, 比不上你的, 但我希望你收下, 没错。 ";
				link.l1 = "玛丽, 礼物的价值不重要... 谢谢你, 我的爱人";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // 早晨
			{
				dialog.text = "已经要走了吗, "+pchar.name+"? 祝你好运, 别忘了我... ";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "玛丽, 我们今天应该去见于尔根。 ";
					link.l3.go = "narval";
				}
				link.l1 = "当然, 玛丽。 ";
				link.l1.go = "exit";
				link.l2 = "不, 玛丽。 我想在这里休息一下。 你介意吗? ";
				link.l2.go = "rest_morning"; // 休息
			}
			else
			{
				dialog.text = "你不去你的库库尔坎那里吗, "+pchar.name+"? ";
				link.l1 = "还没, 还在准备。 ";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) // 晚上
			{
				dialog.text = "已经是晚上了, "+pchar.name+"。 为什么不待在这里? 我想和你在一起。 ";
				link.l1 = "好吧, 亲爱的, 我留下... ";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "玛丽, 我们今天去酒馆吧! ";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) // 白天
			{
				dialog.text = "祝你好运, 别忘了我... 如果可以的话, 晚上来看我, 没错! ";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "玛丽, 我们应该今天见于尔根。 ";
					link.l3.go = "narval";
				}
				link.l1 = "很好, 亲爱的。 ";
				link.l1.go = "exit";
				link.l2 = "玛丽, 我想在这里休息一下。 你介意吗? ";
				link.l2.go = "rest_afternoon"; // 休息
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "你在说什么? 已经是晚上了! 不, 你哪也别去, 你要留在这里, 没错! ";
			link.l1 = "(笑着) 好吧, 我留下... ";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// < —很快通过传送门离开
		
	// --> 相互关系 - 亲密等
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = ""+ PChar.name+"船长! 玛丽.卡斯帕军官准备好为您效力了! ";
				link.l1 = "干得好, 军官! 我命令你立即登船。 但首先: 吻你的船长! ";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "太神奇了, 爱人... 早上好! ";
				link.l1 = "早上好, 亲爱的! 你太棒了! ";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// < —相互关系
		
		// 成为独角鲸帮的朋友
		case "donald":
			dialog.text = "你和唐纳德谈过了吗? 舰队司令真的想和里瓦多斯人结盟对抗独角鲸帮吗? 你真的说服他放弃了吗? 海盗和独角鲸帮之间会和平, 对吗? ";
			link.l1 = "是的, 玛丽。 是这样的。 ";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", 我找不到词... 他们还说唐纳德把你当朋友。 你可能会成为独角鲸帮的一员, 没错! ";
			link.l1 = "有空见见唐纳德 —他也想和你和解。 他请你原谅他的话, 以及没能保护你免受那两个混蛋的伤害。 ";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "去他的唐纳德! 不过我当然很高兴听到这个。 我会见他的。 但是你! 我... 不, 不是那样... 我为你骄傲, 没错! ";
			link.l1 = "天哪, 玛丽... 你是... 啊, 你让我心跳加速! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// 告别节点
		case "dolly":
			dialog.text = "我们谈谈吧! 你有麻烦吗? ";
			link.l1 = "没有。 玛丽, 你还记得我们第一次见面的那个晚上吗? 在我们解决了那两个混蛋之后, 我告诉你我是乘船到这里的。 ";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "我记得, 是的。 你的三桅帆船沉了, 你不得不游到这里... 没错! ";
			link.l1 = "我撒谎了。 如果当时告诉你真相, 你会觉得我疯了。 根本没有三桅帆船。 我用了印第安神'库库尔坎'的神秘力量来到这个地方。 ";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... 你在说什么? 库库尔坎? ";
			link.l1 = "玛丽, 亲爱的, 你必须相信我, 因为这没有任何道理, 除了你, 我不能和任何人分享这个。 纳撒尼尔.霍克触摸印第安神像后消失了, 他当时在被追捕, 是神像救了他... ";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "我在找纳撒尼尔。 我和一位印第安萨满谈过, 不得不和霍克一样做。 我被传送到'圣奥古斯丁号'的货舱里, 从船体的一个洞出来, 然后命运把我带到了你这里。 ";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "这应该是我们有一天讲给孩子听的有趣故事吗? 还是你疯了? ";
			link.l1 = "我是认真的, 玛丽。 我知道这很难相信, 你肯定觉得这很疯狂, 但请相信我。 ";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "看来埃里克的故事是真的... ";
			link.l1 = "埃里克是谁? 他告诉你什么了? ";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "埃里克是当地人之一, 一位老水手。 他已经死了。 我小时候, 他常给我讲关于一个黄金偶像的故事, 里瓦多斯人在那里献祭人的神龛。 就在这个岛上\n那些触摸它的人消失了, 再也没人见过。 我以为那只是吓唬孩子的故事。 ";
			link.l1 = "是真的, 玛丽。 埃里克没有撒谎。 ";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "幸运的是, 载有那个可怕偶像的船沉了。 我从未亲眼见过。 ";
			link.l1 = "我找到了它, 沉在海底。 ";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "你潜到那里了? ! 那个该死的发明家韦德克给你他的潜水服了? 那里有螃蟹在爬, 没错! 混蛋! 让你陷入危险! ";
			link.l1 = "玛丽, 别担心我。 我能对付那些怪物。 它们不像人们说的那么可怕。 自从我到这个岛的第一天起, 我就一直在寻找这座雕像, 终于找到了。 ";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "现在会发生什么? ";
			link.l1 = "这是离开这里的唯一方法。 我通过这样的偶像来到这个地方, 我将再次用它回去... 玛丽! 你在哭吗? 玛丽! 别哭! ";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "鲨鱼,  ";
			else sTemp = "";
			dialog.text = "我为什么不哭? 我要哭, 我想哭, 没错... (抽泣) 这种事总是发生在我男人身上! 我又要孤单了! ";
			link.l1 = "你以为我会怎么样? 你真的认为我会把你留在这里吗? ! 我会乘船回来接你。 我要把你和"+sTemp+"纳撒尼尔一起带回去。 你愿意跟我到外面的世界吗? ";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(流着泪) 当然... 。 当然, 我会... 你会回来找我, 对吗? 你到底打算怎么回到岛上? 只有鲨鱼知道怎么航行到这里。 你敢忘了我, 等我找到你就揍你! ";
			link.l1 = "玛丽, 别胡思乱想! 我当然会回来找你, 自从遇见你的那天起, 还有谁能让我的心跳保持同样的节奏? 别担心, 爱人, 鲨鱼已经和我分享了坐标和方向。 我会找到你的。 ";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "你说一座雕像直接把你从大陆带到这里, 但如果这座雕像把你带到别的地方, 比如非洲呢? 那时没有你我该怎么办? ! ";
			link.l1 = "库库尔坎是印第安神, 它会把我带到加勒比海或大陆的某个地方。 我只需要找到一个定居点, 然后很容易就能找到我的船和船员。 ";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(哭) 答应我... 不, 向我发誓你会回来, 没错! ";
			link.l1 = "玛丽, 亲爱的, 我向你发誓我会回来。 我会把你从这个该死的地方带走。 你不用等我太久。 别哭了。 ";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "好吧, "+pchar.name+"... ... 回到我身边, 我会等你, 没错! 你什么时候走? ";
			link.l1 = "我还不知道。 我需要先准备好, 然后潜水触摸雕像。 他们会告诉你我淹死了 —别相信。 一切都会好的。 ";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "我知道了。 "+pchar.name+", 亲爱的, 抱抱我... 吻我... ";
			link.l1 = "玛丽... 我亲爱的玛丽... ";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // 可以传送
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); // 转动时间
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// 赠送玛丽独角鲸阔剑
		case "narval":
			dialog.text = "于尔根? 为什么? ";
			link.l1 = "你会看到的。 这将是一个惊喜。 ";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "哦, 真有趣! 惊喜? 太棒了, 没错! 我们走吧, 趁我还没好奇死! ";
			link.l1 = "你会喜欢的, 我确定。 我们走! ";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "走吧, "+pchar.name+"! ";
			link.l1 = "好的... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "那么, "+pchar.name+", 你给我准备了什么惊喜? ";
			link.l1 = "玛丽! 于尔根和我决定送你一份我们俩的礼物。 这是一把独特的剑, 一把刻有独角鲸之名的阔剑。 世界上只有两把这样的剑: 第一把属于艾伦.米尔罗, 这把将属于你。 它由特殊钢材制成, 由于尔根精湛的手艺锻造, 永远不会变钝或生锈。 ";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "我们亲爱的女孩... 所有独角鲸都知道你经历了什么。 我认为你值得拥有这把阔剑, 独角鲸帮派的象征。 自豪地佩戴它吧。 这把剑将是敌人的威胁, 在战斗中保护你。 ";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "于尔根? 这... 是给我的? ... ";
			link.l1 = "是的, 玛丽。 "+sld.name+"让我为你制作它, 并从海底带来了一些独特的铁, 没有任何钢材能比得上这种材料的重量和强度。 我把灵魂注入了这把剑, 就像我曾经为艾伦做的那样。 ";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "我不知道该说什么... 谢谢你, 于尔根! 谢谢你, 没错! 我会自豪地佩戴它, 并匹配这把剑的价值, 我发誓, 没错! 我对阔剑的训练还不够, 但现在我会努力训练! ";
			link.l1 = "在这方面, 我毫不怀疑, 姑娘。 ";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... 等等, 不... 你是我见过的最好的男人! 你太棒了, 没错! 你知道这对我意味着什么吗? 这把剑是我能得到的最好的礼物! 你已经为我做了这么多, 救了我两次命, 但你总是给我惊喜! 谢谢你, 我的爱人! ";
			link.l1 = "别无他法, 玛丽。 我会每天继续给你惊喜, 直到我最后一口气! 你的微笑给我带来快乐, 我很高兴你喜欢这份礼物。 ";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(咯咯笑) 谢谢你! 如此美妙的剑, 没错! 它需要一只强有力的手来挥舞... 我迫不及待地想开始用它训练! ";
			link.l1 = "我看不出有什么问题。 赶紧回你的船舱试试你的新阔剑! ";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "我正打算这么做。 再次感谢你, 绅士! "+pchar.name+"... 今晚准备好后来看我... (咯咯笑)";
			link.l1 = "当然, 女士。 晚上见。 ";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // 打开通过货舱的通道
			// 拥有独角鲸剑提升玛丽的TO技能并解锁硬手 perk
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// 玛丽赠送护身符
		case "talisman":
			dialog.text = "给, 看看。 我在外环的一艘船的船长箱子里找到的。 每个有经验的水手都说这个物品对航海家来说极其珍贵, 它可以保护船只免受最恶劣的风暴。 他们中的一些人甚至渴望购买它, 但我没有卖掉... 我想让你拥有这个护身符, 亲爱的。 用它来保证你在海上的安全。 ";
			link.l1 = "谢谢你, 玛丽! 你真体贴, 我爱你! ";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("你收到了'约拿'的护身符");
			dialog.text = "真的吗? 你喜欢它? 哦, 太好了! 我很高兴, 没错! ";
			link.l1 = "这是一个非常稀有和有价值的护身符。 我当然喜欢它! 谢谢你, 亲爱的! ";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------返回岛屿---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... 你回来了。 我一直在等你, 我每天都在眺望地平线, 没错! 你回到我身边了... ";
			link.l1 = "是的, 玛丽。 我如承诺般在这里。 让我抱抱你, 亲爱的! ";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "啊, "+pchar.name+"... 你甚至无法想象我的感受! 独角鲸们在谈论你的死讯, 他们说你淹死了。 他们都确信你死了。 我一直告诉他们你还活着... 当然, 没人相信我, 他们认为我在经历了这一切后疯了。 ";
			link.l1 = "玛丽... 我亲爱的! 你怎么了? 你在发抖... 你冷吗? ";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "不, 我不冷。 我只是... 我不想在这里谈论它。 等你忙完后来我的船舱。 我想单独和你待在一起, 没错... 你现在不去见舰队司令和纳撒尼尔吗? ";
			link.l1 = "是的。 我必须和鲨鱼谈谈, 当然, 还要把丹妮尔带给纳撒尼尔。 不会花太多时间。 我很快就会见到你, 玛丽。 ";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "我期待着... 见到你。 尽快来, 没错! ";
			link.l1 = "... ";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! 终于。 我们得谈谈, 没错! ";
			link.l1 = "怎么了, 玛丽? 我看你有心事! 发生了什么? ";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "她发生了... "+pchar.name+", 你船上的那个婊子是谁? ";
			link.l1 = "谁? 你说的是丹妮尔吗? 但你已经知... ";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "不, 不是丹妮尔。 我是说那个金发女郎, 几乎没穿衣服, 在你船的甲板上走来走去的那个! 我通过望远镜看到她了, 没错! ";
			link.l1 = "啊! 那是海伦.麦克阿瑟。 她和丹妮尔一样卷入了这个奇怪的故事。 她暂时担任我的军官。 当然是暂时的。 ";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "军官? 她是军官? ! ";
			link.l1 = "嗯, 是的。 那有什么问题? .. 玛丽, 该死的! 你吃醋了! ";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "你以为呢? ! ... (流泪) 我一直在这里等你, 因为你我睡不着, 而你竟敢带着某个老巫婆回来... ";
			link.l1 = "玛丽! 别哭了! 你怎么了? 你可以毫不犹豫地干掉任何男人, 但你的眼睛总是湿润... 玛丽, 亲爱的, 海伦只是一名军官, 暂时任职直到正义得到伸张, 我们的共同目标达成, 仅此而已。 ";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "我一直在用你给我的阔剑努力训练, 在你不在的时候我已经完美掌握了它。 ";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "我一直在用细剑努力训练, 并且已经完美掌握了它们。 ";
			dialog.text = "(抽泣) 军官... 那我也想成为你的军官, 没错! 你知道我能战斗! "+sTemp+" 而且我射击很好! 我可能没有任何航海技能, 但我学得很快, 我很有天赋, 没错! ";
			// 第一次通过 - 主角要么同意, 要么拒绝, 拒绝导致完全破裂
			link.l1 = "(同意) 玛丽... 我自己也想给你这个职位。 没有比你更好。 更熟练。 更热情的姑娘了! 我希望你在我身边! ";
			link.l1.go = "adversary_hire";
			link.l2 = "(拒绝) 玛丽! 成为登船军官太危险了! 你不明白你在要求什么。 我不能拿你的生命冒险。 ";
			link.l2.go = "adversary_fail";
		break;
		
		// 拒绝
		case "adversary_fail":
			dialog.text = "你不能吗? 所以那个金发婊子可以当军官而我不能? 你在骗我, "+pchar.name+", 你只是不想和我在一起! (哭泣) 那个女孩比我好, 是吗? ";
			link.l1 = "玛丽, 你不明白! ";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "我明白! 我看到她发光的眼睛盯着你! 她不仅仅是一名军官, 没错! 我知道那种眼神, 没错! 只有我能给你那种眼神! ";
			link.l1 = "玛丽, 你在说什么! ";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "结束了... (哭泣) 走开! 去找你的婊子! 而我会留在这里... 我哪里也不去! 把我的钥匙还给我! ";
			link.l1 = "但是玛丽... ";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "走开... ";
			link.l1 = "... ";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // 伤害了玛丽 - 再也得不到她的任何回应
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//禁止对话
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // 关闭通往玛丽的入口
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; // 打开地图
			DeleteAttribute(pchar, "GenQuest.CannotWait");// 可以转动时间
		break;
		
		// 同意
		case "adversary_hire":
			// 第二次通过 - 看看海伦是否能成为朋友
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "真的吗? 你真的想让我当你的军官? "+pchar.name+", 该死的, 你无法想象我有多高兴! 我非常想成为你的军官... 但不想和那个金发女郎在同一艘船上! ";
				link.l1 = "玛丽, 但为什么? ! ";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "真的吗? 你真的想让我当你的军官? "+pchar.name+", 该死的, 你无法想象我有多高兴! 我发誓, 我不会让你失望, 你会看到的! ";
				link.l1 = "天啊, 玛丽, 亲爱的, 你真可爱。 你刚才还在哭, 现在脸上却容光焕发! 还有, 玛丽, 你对我来说不仅仅是另一名军官。 你不止于此, 我怀疑你无论如何都不会让我失望。 ";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // 玛丽不会去, 直到主角和海伦分手。 选择谁更重要... 
			dialog.text = "你可能只把她当作你的军官, 但我怀疑她不仅仅把你当作她的船长。 我看到了她看你的眼神, 我知道那种眼神, 没错! 只有我能给你那种眼神! ";
			link.l1 = "玛丽, 亲爱的, 但我已经告诉过你, 我对她没有感觉, 就是这样! 我们之间什么都没有! 我发誓, 该死的! 我需要她的帮助来处理海岸兄弟会的烂摊子。 如果我不帮她, 扬.斯文森就不会帮我夺取托尔图加, 而我需要他! ";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", 亲爱的, 抱抱我... 对不起。 我相信你。 但我不能和她待在一起, 看着她试图和你调情, 没错! 最终我会拿出我的剑把她劈成两半! ";
			link.l1 = "是啊, 你肯定能做到... 你脾气不小, 嗯? ";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "如果我杀了她 - 你会离开我, 没错... 我永远不会原谅自己。 ";
			link.l1 = "那么你建议什么, 玛丽? 我该怎么处理她? ";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "你说过她是临时军官。 等你把她留在陆地上, 我就加入你。 我希望把她困在某个无人岛上(咯咯笑) 我会跟随你到世界的尽头, 没错! "+pchar.name+", 亲爱的, 她真的比我好吗? ";
			link.l1 = "胡说! 别那样说, 玛丽, 亲爱的, 没有女人比你更好! ... ";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "那就证明给我看。 我不想和你分享, "+pchar.name+"! 我宁愿一个人也不愿和别人分享你, 没错... ";
			link.l1 = "好吧, 玛丽。 我们做个交易。 我现在不能摆脱海伦, 她对这次追捕很重要。 我会帮助她解决问题, 让她成为宝藏岛的女主人, 让她走, 我们之间就没有任何关系了。 希望不会超过一两个月。 你会等我那么久吗? ";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "我当然会, 没错! 这是我的决定... 如果你回到我身边, 那意味着你选择了我而不是她。 如果你不回来... 那就是我的命运。 我会留在这里建立自己的帮派。 卡斯帕帮派... ";
			link.l1 = "又哭了? 玛丽, 来吧。 别胡说八道了! 你在说什么? 什么帮派... 傻姑娘, 我当然会回来, 我不敢把你留在这些腐烂的旧船中间! 你会用你的眼泪淹没整个岛屿! ";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "那就尽快回来... "+pchar.name+", 亲爱的, 吻我, 求你了... ";
			link.l1 = "我会回来的。 我保证! "; // 是啊, 看看你会不会骗她
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); // 转动时间
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // 把玛丽在岛上的事情保持有效
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; // 打开地图
			DeleteAttribute(pchar, "GenQuest.CannotWait");// 可以转动时间
		break;
		
		// 与海伦分手后的再次对话
		case "adversary_hire_return":
			dialog.text = "你在耍我吗? "+pchar.name+", 你真的没有忘记我? ";
			link.l1 = "当然! 我骗过你吗? 在我们分开期间我经历了很多, 我无意再与你分开... 我的护身符。 ";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // 海伦肯定不是朋友 - 玛丽立即出发, 或者如果选择了玛丽
			dialog.text = "真的吗? "+pchar.name+"! 我会永远跟随你! 我永远不会对你撒谎, 我永远不会背叛你, 我发誓! ";
			link.l1 = "我相信你, 我亲爱的... 我也不会。 "; // 你还能去哪里 )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", 亲爱的, 抱抱我... 我们会在一起, 对吗? 告诉我! ";
			link.l1 = "是的, 我们会在一起, 玛丽。 永远。 ";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "就像丹妮尔和纳撒尼尔一样? ";
			link.l1 = "(笑着) 是的, 就像他们一样。 ";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... 我爱你! 如果你愿意, 我会嫁给你, 没错... ";
			link.l1 = "亲爱的玛丽... 当然 - 我们以后再谈。 你在这艘船坟场的生活结束了, 先让我带你离开这里 - 欢迎登上我的船, 进入广阔的世界, 我的爱人! ";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "让我们在'刻瑞斯铁匠号'上度过我们在这个岛上的最后一夜。 只有我们俩。 只有你和我... 直到早上来临, 我不会让你去任何地方, 没错! ";
			link.l1 = "好吧, 我们不在我的船上, 所以我会听从你的命令... 我亲爱的玛丽! ";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; // 打开地图
			DeleteAttribute(pchar, "GenQuest.CannotWait");// 可以转动时间
		break;
		
		case "LSC_mary_hire":
			dialog.text = "是, 长官! ";
			link.l1 = "... ";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> 海战咨询
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! 我有个主意... ";
			link.l1 = ""+npchar.name+"? 这里不安全, 我命令你留在船上... ";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", 这艘旧船上有这么多火药, 如果它爆炸, 整个岛都会飞上天。 现在待在哪里都没区别了。 听我说! ";
			link.l1 = "我在听, 请快点说。 ";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "海盗护卫舰和轻帆船。 他们误以为我们是他们的人... 刀, 没错。 这对我们来说是个机会。 我们拿几桶火药, 一根导火索, 然后驶向他们。 \n当他们让我们靠近时, 我们点燃导火索, 把桶扔到其中一艘船上, 然后尽快驶离。 肯定是观赏烟火的绝佳机会... 你觉得怎么样? ";
			link.l1 = "虽然有风险, 但你的计划可能奏效... 前提是他们没认出我们。 ";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "冒个险吧, "+pchar.name+"? ";
			link.l1 = "好吧。 我们开始吧! 伙计们! 拿三桶火药! 我们要离开这里! 我爱你的想象力, "+npchar.name+"... 我自己永远想不到这个主意。 ";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "告诉过你, 我有我的才能! ";
			link.l1 = "... ";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "是的, 当然, 亲爱的。 我随时准备帮忙, 没错! 怎么了? ";
			link.l1 = "杰克曼的船在萨博-马蒂拉峡, 重型护卫舰'百夫长号'。 这艘船曾经是霍克家族的财产, 所以杰克曼的船舱里一定有重要物品和文件... 我们必须登船。 ";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "我明白了。 你打算怎么用我们的小船做到这一点? 他们有更多的人和大炮。 我通过望远镜看过了, 没错! ";
			link.l1 = "你说得对。 杰克曼的人至少是我们的两倍, 而且都是熟练的刺客和雇佣兵。 没有适当的准备就登船是疯狂的。 海上持久战也不是选择。 所以我一直在考虑其他完成任务的选择。 ";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", 他们还没把我们当成敌人, 就像特克斯那些白痴一样... 我们可以再试一次我们的把戏... ";
			link.l1 = "玛丽, 我刚告诉你我们必须登船, 击沉她不是选择。 ";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "我知道, "+pchar.name+"。 我们不会击沉她。 听着, 我们要拿几个空朗姆酒桶, 装满火药。 葡萄弹和短导火索。 然后我们驶近他们的护卫舰, 把简易爆炸物扔到他们的甲板上。 ";
			link.l1 = "哈! 你真的认为这会奏效? ";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "为什么不呢? 他们的干舷比我们高, 但两三个男人借助滑轮可以轻松吊起并投掷装满的桶。 我们会大喊 -'这是 Knive 送的免费朗姆酒!'桶在他们反应过来之前就会爆炸。 ";
			link.l1 = "爆炸的葡萄弹会把他甲板上的精兵变成肉泥... 该死, 听起来很诱人。 ";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "我们用五桶。 "+pchar.name+", 我们有出其不意的优势。 他们不会怀疑什么! 不过我们必须在他们登船前立即驶离。 ";
			link.l1 = "好吧, 试试。 在我们扔桶之前, 他们一定不能认出我们... 该死, 靠近他们可不容易。 杰克曼不像 Ghoul 那样是个白痴。 ";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "冒个险吧, "+pchar.name+"! 反正也没什么损失。 ";
			link.l1 = "说得对, 我们没什么可失去的... 准备炸弹! ";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "我会的, 我的船长! 我会完美地准备好, 没错! ";
			link.l1 = "嘿, 他们没让你在岛上打晕那些螃蟹, 所以现在我让你在这里炸海盗的屁股... 玛丽, 你太棒了! ";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "谢谢你, "+pchar.name+"! 我不会让你失望的! ";
			link.l1 = "这一点, 我毫不怀疑。 我希望我们不会因为搞砸你的计划而让你失望... 准备战斗! ";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// < —海战咨询
		
		// --> 龟汤
		case "terrapin_grot":
			dialog.text = "你在这里! 找到你费了些功夫... 太神奇了, 船长! 我从未见过如此惊人的跳跃! 你永远是我的英雄! 不过我承认, 你差点让我心脏病发作\n总有一天你会用这些把戏杀死我, 亲爱的... 那么, 她到底是谁? 哦, "+pchar.name+", 我让你离开我一会儿, 接下来我就知道, 你被一群荡妇包围了! ";
			link.l1 = "玛丽, 这个'荡妇'是凯瑟琳.福克斯, 福克斯上校的女儿, 海狐队的指挥官。 我们必须把她带到安提瓜。 ";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "哦, 真的吗? 太高兴了! 好吧, 你会告诉我她的事... 今晚, 当我们单独在一起过夜时。 现在, 我们走吧, 我们得快点! ";
			link.l1 = "你是最棒的, 玛丽。 没有你我该怎么办? 凯瑟琳, 来吧! ";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// < —龟汤
		
		// --> 幽灵船
		case "on_coast":
			dialog.text = "你终于醒了, 我亲爱的... 混蛋! 再也不要那样吓我了! ";
			link.l1 = "玛丽... 亲爱的, 发生了什么? 我的头快裂开了... ";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "当我们进入船长的船舱时, 你躺在地板上像具尸体一样一动不动。 我的心跳得飞快! 伙计们把你抬起来, 拖到我们的船上 - 正好及时, 因为躺在甲板上的死人开始再次站起来\n多么噩梦! 我们对他们无能为力! 我们迅速切断缆绳, 试图驶离, 但他们船上的一轮齐射严重损坏了我们的船, 我们失去了控制。 他们真是些魔鬼, 没错! 然后他们升起风帆, 瞬间就消失了\n我们的船搁浅了, 所以我们必须在风暴摧毁她之前逃到这个海岸。 今天很多好人死了, 但船最终幸存了下来... ";
			link.l1 = "干得好, 玛丽... 没有你我该怎么办? ";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "也许你会淹死, 或者你会留在那艘船上, 被死人撕碎... 我的手还在发抖! ";
			link.l1 = "谢谢你, 爱人。 我昏迷了多久? ";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "整整一天。 我清理了你的伤口, 给你喂了药, 还给你灌了些朗姆酒。 你应该很快就会好起来。 别敢死在我面前! ";
			link.l1 = "我保证这次不会死, 亲爱的。 不过我感觉不太好... ";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "那是肯定的... 是'飞翔的荷兰人号'吗, 船长? 他们为什么攻击我们? 为什么在登船前不射击? ";
			link.l1 = "他们的船长需要那个护身符, 就是我和印第安萨满图图阿塔帕克谈过的那个。 这就是他们需要登船的原因, 但一旦他们的船长拿到护身符, 就不再需要我们了... 多么噩梦! 一艘由死人操纵的船! 难以置信... ";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "是的, 看来'飞翔的荷兰人号'迟早会来找我们。 有机会我会去教堂, 点一支蜡烛感谢我们的奇迹般获救, 并向我们的主祈祷... ";
			link.l1 = "我也是, 玛丽, 我想。 我需要回到那个村庄。 让图图阿塔帕克知道发生了什么。 那艘船因为护身符攻击了我们! 我希望那个红皮肤的魔鬼能解释为什么那些活死人一开始需要它。 ";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "好吧。 但要小心 - 你的伤口刚刚愈合。 ";
			link.l1 = "你就是我需要的所有药物。 还有... 玛丽, 我爱你... ";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "我也爱你, 我亲爱的... ";
			link.l1 = "... ";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;// 打开地点
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// < —幽灵船
		
	// --> 玛丽在 LSC 之外
		// 亲密 - 玛丽从不拒绝
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", 对我来说没有比在你怀里更幸福的了, 没错... 我们走吧! ",""+pchar.name+", 如果可能的话, 我想每时每刻都和你在一起。 我们走吧! ");
			link.l1 = RandPhraseSimple("你是最棒的, 我的爱人... ","你是美妙的, 我的护身符... ");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("亲爱的, 你太棒了... 你总是这样! ","太棒了! ");
			link.l1 = RandPhraseSimple("我很高兴你快乐, 我的爱人... ","我爱你, 玛丽... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;// 打开地点
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour 用于无冲突任务							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", 对我来说没有比在你怀里更幸福的了, 没错... 但现在不是最好的时机 - 我们必须在蒂博逃跑前抓住那个混蛋。 ";
				link.l1 = "你总是对的, 我的女孩... ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", 没有比在你怀里更幸福的了, 没错... 我们走吧! ",""+pchar.name+", 如果可能的话, 我想每时每刻都和你在一起。 我们走吧! ");
			link.l1 = RandPhraseSimple("你是最棒的, 我的女孩... ","你是美妙的, 我的红头发护身符... ");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
            pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;// 关闭地点
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "LoveSex_Room_Go");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// 需要亲密, 如果很久没给
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", 我们很久没有亲密了... 你完全忘记我了, 没错! 亲爱的, 我想放松一下, 我们开个房间过夜, 把烦恼留到另一天! ",""+pchar.name+", 你太忙了, 我开始觉得你完全忘记我了! 亲爱的, 我想... 和你私下待在一起。 我们开个房间过夜, 没错! ",""+pchar.name+", 你疯了吗? 我想和你一起过夜, 喝点酒, 放松一下。 你在海上太忙了, 完全忘记我了! ");
			link.l1 = "玛丽, 亲爱的, 你说什么 -'完全忘记我'? 傻女孩... 但我真的太忙了, 需要关注的问题无穷无尽。 原谅我, 我的爱人。 我们上楼吧, 今晚我全属于你, 世界可以等! ";
			link.l1.go = "room_sex_go";
			// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("今天不行, 亲爱的。 我头痛。 ","玛丽, 亲爱的, 我怎么会忘记你? 来吧, 稍后 - 我们有工作要做... "),RandPhraseSimple("你总是在我心里, 玛丽, 但我们现在不能放松。 ","玛丽 "+npchar.lastname+", 我们今天没时间胡闹。 "));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
			if(sti(pchar.reputation.fame) > 60)
			{
				ChangeCharacterComplexReputation(pchar,"authority", 2);
				if (npchar.chr_ai.type == "actor")
				{
					LAi_SetOfficerType(npchar);
					LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
				}
				NextDiag.TempNode = "Mary_officer";
				chrDisableReloadToLocation = false;
				npchar.quest.daily_sex = true;
				DeleteAttribute(npchar, "quest.iwantsex"); 
				SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
				pchar.quest.Mary_giveme_sex.over = "yes"; 
				pchar.quest.Mary_giveme_sex1.over = "yes";
				dialog.text = "好吧... 我还能说什么... 是的, 船长! ";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
			else
			{
				if(bImCasual) Log_Info("To refuse Mary become more famous");
				ChangeCharacterComplexReputation(pchar,"authority", -2);
				dialog.text = "查尔斯... ";
				link.l1 = "玛丽, 亲爱的, 你说什么 -'完全忘记我'? 傻女孩... 但我真的很忙, 那些问题无穷无尽。 原谅我, 我的女孩。 我们上楼吧, 世界可以等! ";
				link.l1.go = "room_sex_go";
			}
		break;
		// < —legendary edition
		// 因逛妓院而生气, 主角狡辩
		case "brothel":
			dialog.text = "是的, 他在那里! 你不再喜欢我了, 是吗? 告诉我! ";
			link.l1 = "什么? ! 玛丽, 你在说什么胡话? 你为什么这么想? ";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "那你为什么一直去那些荡妇那里, 那些妓院的妓女? 我知道你去了, 别骗我! 我们亲热时你对我有什么不满意的, 是吗? (哭泣) 告诉我... ";
			link.l1 = "玛丽, 玛丽... 请冷静, 我的女孩。 是的, 我去过几次妓院, 但只是为了生意。 我不是去寻欢作乐的! ";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "什么样的'生意'把你带到楼上的 fuck 房间? (抽泣) 你在撒谎, "+pchar.name+"! ";
			link.l1 = "玛丽, 亲爱的, 终于停止吧... 我确实和妓院的老鸨有一些生意。 而且我上楼过几次。 上次是为了总督的私事 - 他让我帮他找结婚戒指。 我怎么能拒绝阁下? ";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "我怎么向老鸨解释我需要到楼上的床底下找东西? 我不能。 所以我不得不花钱找个妓女过夜才能被允许上楼... 第二次, 有人告诉我一个商人在那里丢了船的文件。 我不得不再次花钱找个女孩, 以便搜查房间, 我为那些文件得到了丰厚的报酬... ";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "第三次我在帮当地指挥官: 我不得不向妓女询问驻军的一名军官。 那名军官被怀疑从事间谍活动并与海盗有联系。 最后我们抓住了他, 我得到了一笔可观的奖励... ";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "现在明白了? 我告诉你, 都是为了生意。 玛丽, 你是我爱的人, 是我需要的人。 你是最棒的, 我发誓! 你真的认为有了你, 我还会去搞那些肮脏的海港妓女吗? 你怎么能那样想我! ";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+"... 这都是真的吗? 你对我诚实吗? 你没有和她们在一起? ";
			link.l1 = "玛丽, 亲爱的, 你是我唯一爱的女人, 这是真的。 靠近点, 亲爱的。 让我抱抱你... 擦干眼泪, 求你了, 别再吃醋了! 如果你希望, 我再也不去妓院了! ";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "是的, 这就是我想要的!... "+pchar.name+", 我吃醋是因为我爱你... 我不想失去你, 没错! 听到了吗? 我会杀了任何敢靠近你一英寸的婊子! ";
			link.l1 = "冷静点... 没必要杀任何人。 你不会失去我, 我保证。 没事的, 冷静点。 你是世界上唯一的, 最好的女孩... 相信我, 你是。 ";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // 好了, 再也不去妓院了 :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// 在泰亚萨尔
		case "tieyasal":
			dialog.text = ""+pchar.name+", 多么奇怪的问题? 我爱你。 你救了我。 我是你的红头发护身符 - 你真的认为我会让你一个人去那里吗? 别指望了, 没错! 我和你一起去! 我们什么时候走? ";
			link.l1 = "你说得对, 亲爱的, 这是个奇怪的问题... 以后我会告诉你我们什么时候去。 我们首先需要准备自己。 ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "我准备好了, 我的船长! 我会跟随你到天涯海角! ";
			link.l1 = "谢谢你, 我的爱人... ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// 杰森 比黄金更珍贵
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
			dialog.text = "这次又有什么骚动, 船长? 西班牙人。 海盗还是更糟? ";
			link.l1 = "更糟, 玛丽, 糟得多。 总督打算拜访一位极其昂贵的交际花, 我应该按照承诺陪他去, 作为一个有趣的人。 无聊的谈话。 高价酒和乏味的贵族。 ";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "恰恰相反, 这是一个参加社交活动的负担, 由一位贵族女士举办。 阁下让我惊讶地要求我陪他, 但说实话, 我期待着借此转移注意力。 ";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "是这样吗? ! 一位交际花? 你说得好像没什么大不了的, 嗯? 只是和阁下找点乐子? 查尔斯, 你是在... ";
			link.l1 = "玛丽, 请冷静! 我不是去那里... 那不是妓院! 好吧, 那是妓院, 但该死的, 我是个贵族, 是个守信用的人。 你真的不信任我吗? 总督只是让我帮个小忙, 我必须答应, 就这样! ";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "是的, 我听说过几个这样的'贵族'。 我也见过他们和你在一起。 对他们来说, 嫖妓是日常需求!'上流'社会,'体面'的娱乐, 去他的! 即使结婚也阻止不了他们拜访这些... 女士。 该死, 我不知道你和他们一样。 我们甚至不是... 去你的, 你们所有人! ";
			link.l1 = "玛丽, 等等! 该死的... ";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "我们确实该休假了, 没错。 你认为他们能接受看到一位穿着红外套的女士吗? 想象一下角落里的窃窃私语? 肯定有人会晕倒, 那会很有趣, 对吗? ";
			link.l1 = "玛丽, 我亲爱的, 这不是那种你带女士去的派对... 至少不是像你这样的女士。 嗯, 有点复杂, 但让我解释... ";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "哇, 别费心了。 直接告诉我: 我不够好, 不配那些戴假发的混蛋。 一个简单的女孩, 用来取乐, 嗯? 你和我在一起觉得尴尬吗? 不配参加高档派对, 对吗, 尊贵的查尔斯.德.莫尔先生? ";
			link.l1 = "不, 完全不是。 你很棒, 我不在乎我们给周围的人留下什么印象。 总督一如既往地试图借助我的帮助解决他的问题。 我在房间里会像一个珍贵的奖杯。 一个让那些无用的贵族印象深刻的有趣客人。 ";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "所以我对你来说不够好, 是吗? 我明白了, 没关系, 贵族配贵族, 农民配简单娱乐。 祝你在上流社会好运。 等你回到我们卑微的土地上, 我会和你谈谈, 嗯? ";
			link.l1 = "玛丽, 等等! 该死的... ";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "祝你在上流社会好运。 等你回到我们卑微的土地上, 我会和你谈谈, 是的。 ";
			link.l1 = "玛丽哦, 来吧! ";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "看看这个, 是的! 我们迷失在上流社会的船长! ";
			link.l1 = "... ";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "你在妓院消失了一整天, 现在镇上的人都在谈论。 查尔斯, 给我一个好理由, 为什么我现在应该和你说话, 而不是, 比如说, 把独角鲸剑插进你的... 肚子? 你不太在乎我, 是吗? ! ";
			link.l1 = "玛丽, 我稍后会解释一切。 我应该准备一下去决斗。 如果我活下来, 你可以随意杀了我。 同时, 请照顾好我们的新船, 没错? 我昨晚在牌局中赢了她作为奖品。 ";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "忘了船吧, 你说什么决斗, 是的? 当地人讲了各种各样我不听的胡说八道的故事。 他们说你要么和国王的儿子决斗, 要么和该死的教皇本人决斗。 告诉我, 现在, 到底他妈的发生了什么? ! ";
			link.l1 = "这个男人是一位非常有影响力的贵族, 德.列维.万塔杜尔伯爵的私生子。 是他首先向我挑战, 我必须在不伤害他的情况下赢得决斗, 以避免他父亲的愤怒。 ";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "而我会坐在你刚赢的 tub 上? 你疯了吗, 查尔斯? ";
			link.l1 = "恐怕不得不这样。 总督给了我几个贵族军官作为我的副手, 以避免事后的任何混乱。 为了决斗的官方完整性, 我不能带你或任何伙计去。 这太严重了, 我很抱歉。 ";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "你知道我现在要做什么吗? 我会去那艘该死的船, 喝得酩酊大醉, 是的! 你喜欢做什么就做什么, 但如果那个贵族混蛋没能杀了你, 我发誓我会亲自动手! ";
			link.l1 = "玛丽, 一切都会好的, 相信我。 现在, 等等... 该死! 我们又来这个了! ";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "他在那里! 我们一整天都没有收到你一个字! 听到市场上流传的八卦, 我们很担心。 他们说你一直在赌船和女人, 甚至和某个 crowned prince 或甚至教皇本人决斗! 到底他妈的发生了什么? ";
			link.l1 = "很复杂, 玛丽。 需要一段时间解释。 不过我确实赢了一艘护卫舰。 你得在我解决和她前主人的纠纷时照顾好她。 ";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "所以他们关于决斗的说法是对的, 嗯? 那个有资格的贵族混蛋是谁? 你为什么和他决斗? ";
			link.l1 = "我必须。 很复杂, 但简而言之: 我赢了他的船和他的... 女人。 他公开指责我作弊, 并向我挑战决斗。 这个男人是一位非常有影响力的贵族, 德.列维.万塔杜尔伯爵的私生子。 我将不得不尽力避免伤害他。 ";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "女人? 我能理解赌船, 但是... 一个女人, 真的吗? 街上的人说的是真的, 嗯? 你就那样承认了? 就像我是... 你的一个白痴水手? ";
			link.l1 = "该死的, 玛丽, 根本不是那样! 他从总督那里赢了她, 我从他那里赢回来释放她, 就是这样。 没有更多的了, 我发誓! ";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "好吧, 也许在你们贵族中这很正常, 但我不是那样的, 没错! 你喜欢做什么就做什么, 说什么就说什么... 如果你想, 就为她去死吧! 我会去你赢的那艘该死的船, 喝个烂醉。 我相信这是真的, 而且... 会永远持续下去。 我想我期望太多了! ";
			link.l1 = "玛丽, 我根本不在乎那个女人! 请等等... 该死! 我们又来这个了... ";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "查尔斯, 你来找我了, 没错! 我就知道, 从未怀疑过! 很高兴见到你! ";
			link.l1 = "我也是, 玛丽! 这一直折磨着我。 感谢上帝你没事! ";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "顺便问一下, 你到底做了什么让他们这么容易就放了我? 没有适当的争吵或射击, 没错! 当他们拖我出去时, 我看到甲板上有这位美丽的女士。 发生了什么, 查尔斯? ";
			}
			else
			{
				dialog.text = "你到底做了什么让他们就这样放了我? 没有战斗, 没有开枪, 没错! 当他们带我出来时, 我看到甲板上有一些英国孔雀。 那都是关于什么的, 查尔斯? ";
			}
			link.l1 = "最重要的是你回到我身边。 我辜负了你, 玛丽。 我很抱歉! 我希望你能从心里原谅我! 我讨厌我们最后分开的方式。 ";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "我已经原谅你了。 我也很抱歉, 没错! 要是我没把你和那个女人的事看得那么个人化... 那天晚上我本该设好警戒的。 他们绝不会那么轻易抓住我们! 我太蠢了! ";
			link.l1 = "过去的就让它过去吧。 我爱你, 我再也不会那样离开你了。 我保证! ";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "我就知道你永远不会抛弃我, 没错。 抱歉曾经怀疑你, 查尔斯! 看来, 我最好不要知道你到底做了什么, 嗯? 我们又在一起了, 这才是最重要的。 ";
			link.l1 = "我没有什么秘密瞒着你。 我会告诉你... ";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("一段时间过去了... ", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "真是个故事... 估计没人会相信, 没错! 我从一开始就知道! 我就知道你那'寻欢作乐'的夜晚肯定有猫腻! 那些贵族孔雀... 都是没心没肺的野兽! 至少我没看错你, 我就知道你不一样, 没错! ";
				link.l1 = "我敢肯定, 外面很多人觉得我更糟糕。 就像童话里的怪物一样。 ";
			}
			else
			{
				dialog.text = "真是个故事... 估计没人会相信, 没错! 我从一开始就知道! 我就知道你那'寻欢作乐'的夜晚肯定有猫腻! 政治。 间谍。 阴谋诡计。 而你又一次拯救了我们所有人, 没错! 我的英雄! ";
				link.l1 = "我不太确定。 几周后可能就会爆发与英国的战争。 但我做了该做的, 玛丽。 你对我来说就是一切。 ";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "我不在乎别人怎么想, 如果是这样, 你就做我的怪物吧, 查尔斯! 其他人要么去哭鼻子, 要么就来对付我! 记住, 我会永远陪在你身边, 没错! ";
			}
			else
			{
				dialog.text = "我知道, 查尔斯。 我一直都知道, 但听你说出来感觉真好。 记住 —我会永远陪在你身边, 没错! ";
			}
			link.l1 = "从未怀疑过, 玛丽。 我们走吧, 兄弟们都担心了。 是时候扬帆起航, 离开这个鬼地方了。 你又回到我身边了, 而地平线不会自己消失。 ";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "是, 船长! ";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // 修复 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "查尔斯, 真的是你吗? ! 我几乎都不抱希望了, 没错! 天啊, 我好想你! 求你, 求你原谅我, 嗯? ";
			link.l1 = "不, 原谅我, 我没料到会这样... 谢天谢地你没事, 玛丽! 我太高兴了! ";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "说到原谅 —说实话, 我在纠结是该开枪打你还是抱抱你。 你最好告诉我到底他妈的发生了什么, 没错? ";
			link.l1 = "我爱你, 玛丽。 这就是我想告诉你的一切。 ";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "是啊, 好像这很有用似的, 但是... 该死, 我也是, 查尔斯。 我也爱你, 嗯。 天啊, 终于, 我们在一起了! ";
			link.l1 = "而且我不想把时间浪费在谈论无关紧要的事情上。 跟我来, 今晚我不会再离开你。 即使天空要砸在这个悲惨的小镇上。 我再也不会离开你了。 永远。 ";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "看来, 我最好不要知道你到底做了什么, 嗯? 我们又在一起了, 这才是最重要的。 ";
			link.l1 = "我没有什么秘密瞒着你。 我会告诉你... ";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("一段时间过去了... ", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "你是说这位... 侯爵夫人帮你把我救回来了? 而且你差点挑起英法战争, 嗯? 别误会 —这很浪漫, 但是现在会发生什么? ";
			link.l1 = "我不知道, 玛丽。 我们又在一起了, 其他的都不重要。 如果那些掌权者没能把事情掩盖过去... 好吧, 我准备好为王室尽我的职责。 ";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "你那位侯爵夫人呢? 你也把她带回来了吗? 那个葡萄牙人对她评价很高。 他向我保证你像巴士底狱一样抵挡住了她的诱惑。 我愿意相信他, 没错, 但我必须听你亲口说! ";
			link.l1 = "我和博托夫人之间没什么, 玛丽。 我帮了她, 她帮了我, 就这样。 说到巴塞洛缪, 他在哪儿? ";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "他走了, 没错。 把我送到这里后立刻就扬帆离开了。 我绝不会去那个该死的妓院, 所以他给我租了个房间, 预付了几周的房费就走了。 哦, 我差点忘了, 没错! 有你一封信! ";
			link.l1 = "一封信? 来自葡萄牙人巴塞洛缪? 这可新鲜。 我不喜欢事情朝这个方向发展... ";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "看吧。 我去看看兄弟们。 他们可能担心了。 大家都没事吧? 希望你不介意我们在楼下喝几杯。 别再惹麻烦了, 没错! ";
			link.l1 = "当然不介意, 但求你小心点, 玛丽。 我宁愿今晚和你在一起, 也不想去把醉鬼拖回船上。 天呐, 我还不敢相信你回来了! ";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // 修复 22-03-20
		break;
		
		// 杰森 长长久久, 幸福快乐
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "海滩。 你。 我, 还有美酒 —查尔斯, 这太浪漫了! 我们应该多这样做, 没错! ";
			link.l1 = "很高兴你喜欢。 我想从现在起我们会多留些时间给彼此, 像这样的时刻。 ";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "你在说什么? 船出什么事了吗, 嗯? 为什么跪着, 我的爱人? ";
			link.l1 = "因为我爱你, 玛丽。 你知道, 我知道, 所有人都知道。 所以现在, 在大海和天空面前, 我问你, 玛丽.卡斯帕 —能否给我这个荣幸, 在上帝和众人面前, 与我共度余生。 我, 查尔斯.德.莫尔, 蒙佩尔骑士, 问你 —你愿意嫁给我吗? ";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "我一直梦想听到这句话, 没错! 我... 你知道我的答案, 查尔斯... 哦, 抱歉! ";
				link.l1 = "没关系, 只是酒而已, 而且我本来就不喜欢这件衬衫... ";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "查尔斯, 当然愿意! 愿意, 愿意, 一千次愿意!!! 你... 这个地方... 没有什么能让我更幸福了!!! 天啊, 我太高兴了, 没错! ";
				link.l1 = "你让我幸福, 玛丽。 我要为你干杯, 我炽热的加勒比太阳! ";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//关闭地点
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "为你干杯, 我的船长和未来的丈夫, 没错! 你是发生在我身上最好的事! ";
			link.l1 = "但这只是开始 —为我们! 为我们的未来! 前方还有很多! ";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "为你干杯, 我的船长和未来的丈夫, 没错! 你是发生在我身上最好的事! ";
			link.l1 = "但这只是开始 —为我们! 为我们的未来! 前方还有很多! ";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "查尔斯, 马提尼克的本诺瓦神父又在问了, 我们可以继续了, 对吗? 但我不会穿裙子, 即使为了教堂仪式, 希望你不会介意? ";
			link.l1 = "玛丽, 我爱你穿任何衣服, 还有... 你知道的。 你想穿什么就穿什么, 谁敢有意见我来处理! 不过, 我只是想和你商量一下宾客和仪式的事。 ";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "你知道, 大多数能真心为我们的幸福高兴的人, 甚至不被允许进入这座城市, 更别说教堂了, 没错。 所以 —我们就在这里按预期和重要人物举行婚礼, 然后航行到宝藏岛, 和真正的朋友好好庆祝! 你觉得怎么样, 没错? ";
				link.l1 = "好主意! 就这么办。 我会和本诺瓦神父谈谈, 但我们需要发出邀请, 还有更多... ";
				link.l1.go = "LongHappy_9";
			}
			else // 传奇故事因时间或百夫长沉没而失败
			{
				dialog.text = "你知道, 除了我们船上的兄弟, 我没什么朋友。 所以邀请你认为必要的人, 我会很高兴, 没错! ";
				link.l1 = "如你所愿, 甜心。 我会和本诺瓦神父谈, 安排好一切, 你值得最盛大的仪式。 ";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "别担心, 作为好妻子, 我会承担部分准备工作, 没错。 我会给朋友们写信, 安排好一切, 但首先, 告诉我: 你理想中的婚礼是什么样的? ";
			link.l1 = "我的理想就是你。 我和我们最亲密的朋友。 在马提尼克完成所有官方流程后, 我们会想要一些真诚的庆祝。 ";
			link.l1.go = "LongHappy_10";
			link.l2 = "我们要记住这一天。 邀请所有人! 一个都不能少! ";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "和你在一起, 在夕阳下的海面上, 由船上的牧师在甲板上主持仪式就足够了, 没错。 但是, 如果这是你想要的 —我们就庆祝! 查尔斯... 我现在要哭了, 抱抱我, 没错... ";
			link.l1 = "玛丽... ";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "好了, 我冷静了, 没错。 抱歉, 这一切都太不寻常了。 但是查尔斯, 作为好妻子, 我会负责组织。 我们还需要为兄弟们安排派对, 没错, 但整船人恐怕装不进教堂。 我会和酒馆安排, 但我们需要酒和钱 —你知道水手们多喜欢派对。 ";
			link.l1 = "好的, 就这么办。 我需要准备什么? ";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "我想, "+sti(pchar.questTemp.LongHappy.MarryMoney)+"比索应该够了, 没错。 "+sti(pchar.questTemp.LongHappy.MarryRum)+"桶朗姆酒, 没有比没酒喝更糟糕的了。 你一凑齐我们需要的东西, 就来酒馆, 剩下的我来搞定。 ";
			link.l1 = "好的, 亲爱的, 我会的。 ";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "明白了, 就这么办。 但我们得去夏普敦准备一下。 我想五十桶朗姆酒和几十桶葡萄酒就够了, 没错。 不过, 以防万一, 我需要三十万比索。 ";
			link.l1 = "这可不少, 但这场合值得。 我会凑齐的, 别担心。 现在, 我得去神父那里, 然后去夏普敦。 ";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "太好了, 我们要把所有人都聚在一起, 没错! 但我们得去夏普敦准备 —需要一整艘大帆船的酒! 我想一百桶朗姆酒和五十桶葡萄酒就够了。 不过, 以防万一, 我再加五十万比索。 如果庆祝很快就结束了, 那算什么庆祝, 对吧? ";
			link.l1 = "对, 我们的朋友不能渴着 —我会弄到所有东西, 别担心! 现在, 我得去神父那里, 然后去夏普敦。 ";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "都准备好了, 查尔斯, 对吗? 我会安排把酒卸下来, 去当地酒馆, 见见男爵, 把请柬发出去。 在这里等我, 没错? ";
			link.l1 = "你说了算, 亲爱的! 那我就在附近逛逛。 真没想到, 去缅因丛林探险都比准备婚礼容易。 ";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("几小时过去了... ", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "我们搞定了, 查尔斯, 没错! 我都安排好了, 相信我 —会很棒的! 有件事有点尴尬: 当地酒馆一周前在一场宴会上烧了。 但现在差不多重建好了, 比以前更大更好, 没错! 我们应该都能挤得下。 ";
			link.l1 = "希望我们别把这个也烧了。 我真喜欢'老啄木鸟'! 不管怎样, 我们还有很多事要做。 该扬帆了。 还有, 玛丽 —你是最棒的, 你知道的, 对吧? ";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "所以我们到了, 嗯? 宾客到了, 教堂准备好了。 我知道我们比很多夫妻都亲密, 这些只是在漂亮大厅里说的几句重要的话, 但该死的 —在那个古老的原住民城市里我都没这么紧张, 没错! ";
			link.l1 = "这很正常, 我的爱人, 非常正常。 我也紧张。 我想, 本诺瓦神父已经在等了, 我去他那儿问问仪式什么时候开始。 ";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "好的, 我在镇上走走, 准备一下, 没错! 查尔斯, 你明白这是无法回头的吧? ";
			link.l1 = "玛丽, 亲爱的, 自从我们相遇, 对我来说就已经无法回头了。 我全心全意地等待这一天。 别担心, 一切都会好的。 ";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//禁止等待
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "我愿意。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "我愿意。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "我愿意。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "我, 查尔斯.亨利.德.莫尔, 蒙佩尔骑士, 娶你, 玛丽.卡斯帕, 为我的妻子, 从今往后, 无论好坏, 贫富, 病痛健康, 直到死亡将我们分离。 在上帝面前, 我按神圣的律法许下此誓。 ";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "我, 玛丽.卡斯帕, 嫁你, 查尔斯.德.莫尔, 为我的丈夫, 从今往后, 无论好坏, 贫富, 病痛健康, 直到死亡将我们分离。 在上帝面前, 我按神圣的律法许下此誓。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "阿门。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "这太不可思议了, 没错! 我... 我哭了, 抱歉查尔斯, 我会... 我的鼻子变红了, 对吗? ";
			link.l1 = "玛丽.德.莫尔, 我的妻子, 你今天和每一天都很美! ";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "谢谢你, 查尔斯, 谢谢你... 一切都如此庄严美好! 这是我生命中最美好的一天, 没错!!! 看, 大家多开心! 但是, 现在你该去见见宾客, 接受祝贺了! 等你完了 —回来 —我们去酒馆看看兄弟们。 ";
			else dialog.text = "谢谢你, 查尔斯, 谢谢你... 一切都如此庄严美好! 这是我生命中最美好的一天, 没错!!! 看, 大家多开心! 但是, 我们在夏普敦还有人等着, 我们什么时候起航? ";
			link.l1 = "我马上就去, 甜心。 亲一个我就走! ";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "查尔斯, 我的爱人, 你已经和宾客谈过了吗? ";
			link.l1 = "还没, 耐心点, 甜心, 我很快就回来。 ";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "是的, 我从没一次性听过这么多祝贺。 你知道吗 —大多数人都是真诚的! ";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "是的, 是的! 他们也跟我说了很多暖心的话! 当然不是所有人, 有些人显然对我的穿着很惊讶, 没错! 但我太高兴了, 人们说的一半话我都没听进去。 总的来说, 大家都很可爱。 查尔斯, 酒馆里的兄弟们已经在等我们了 —我们该去了。 他们会很高兴祝贺他们的船长, 没错! ";
				link.l1 = "我们现在就去。 但我想在比港口酒馆更浪漫的地方结束这一天。 我希望, 我的妻子, 你不介意在我们的船舱里度过今晚? 而且, 现在船上没有值班... ";
			}
			else
			{
				dialog.text = "是的, 是的! 他们也跟我说了很多暖心的话! 当然不是所有人, 有些人显然对我的穿着很惊讶, 没错! 但我太高兴了, 人们说的一半话我都没听进去。 总的来说, 大家都很可爱。 查尔斯! 但我们在夏普敦有人等着, 我们什么时候起航? ";
				link.l1 = "现在就走。 我们不能让客人喝光所有补给! 我希望, 我的妻子, 你不介意在我们的船舱里度过今晚? ";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "即使在荒岛上的茅屋里也行, 但必须和你一起, 当然! ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "我知道。 我也爱你。 我们走吧, 趁兄弟们没喝光我们的朗姆酒, 把酒馆点了。 ";
			else link.l1 = "我也是。 我也爱你。 那么 —我们起航! ";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "哦, 亲爱的, 我太高兴了! 今天是美好的一天... ";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "扯下他那没洗的脑袋, 查尔斯! ";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // 修复 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "我没事, 没错! 内森怎么样, 他还活着吗? ";
			link.l1 = "好多血... 丹妮, 他还有呼吸吗? 我看到他在呼吸! ";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "快点, 亲爱的, 别浪费时间! ";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "我们赢了, 没错! 原谅我来晚了。 我们被困在楼上, 有十几个混蛋, 所以我有点忙! ";
			link.l1 = "没关系, 我解决了。 很高兴能结束和雅克的事... 终于。 他罪有应得。 ";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "那这边结束后回夏普敦! 我们得去看看内森, 没错! 他为我们冒了生命危险! ";
			link.l1 = "你说得对, 我的爱人。 走吧, 我马上来。 ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "顺便说一句, 亲爱的, 我们找到马库斯了, 没错! 他在货舱里, 被绑着, 失去了意识。 ";
			link.l1 = "他还活着? ";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "他受伤了, 但会没事的。 你打不倒我们的男爵, 没错! 他刚醒过来就又想战斗了。 ";
			link.l1 = "这才是我们的老马库斯! 好了, 这边结束后去岸边。 ";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "我很抱歉, 查尔斯, 没错, 我... 我去散步了。 我看到你回来了, 听说大家都活着, 赢了, 但我... 但我这是怎么了, 没错! ";
				link.l1 = "一切都会好的, 爱人, 一切都会好的。 我也很难过。 但我们赢了, 雅克.巴巴西翁为他的所作所为付出了代价。 ";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "我为吉诺感到很难过, 查尔斯, 没错! 当我知道时, 我简直不敢相信! 你怎么样? ";
					link.l1 = "我也不敢相信... 事情结束得太愚蠢了, 我没想到这一天会是这样。 ";
				}
				else
				{
					dialog.text = "我们又赢了, 没错! 我的丈夫是海岸兄弟会叛逆男爵的噩梦! 朋友们活着, 敌人死了 —一份光荣的礼物, 没错! ";
					link.l1 = "是啊, 这样的庆祝, 但我们做到了, 我的爱人。 我们做到了。 ";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "你几乎站不稳了, 没错! 来吧, 丹妮在郊区给我们找了间房子, 我现在不想回船上。 我们坐下来, 为我们逝去的朋友干一杯。 清醒着面对这一切太沉重了, 没错。 ";
			link.l1 = "好的, 玛丽, 我们走。 ";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "我为吉诺感到很难过, 查尔斯, 没错! 当我知道时, 我简直不敢相信! 你怎么样? ";
				link.l1 = "我也不敢相信... 事情结束得太愚蠢了, 我没想到这一天会是这样。 ";
			}
			else
			{
				dialog.text = "抱歉我来晚了, 亲爱的, 没错! 我去散步了, 然后看到你靠近, 就以最快的速度跑来了! 当吉诺说'危险结束了'时, 丹妮尔才让我出来, 没错! 我很高兴现在一切都好了! ";
				link.l1 = "我也是, 亲爱的。 而且我们赢了。 巴巴西翁死了, 男爵们在收拢残余船员。 战斗结束了。 ";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "查尔斯, 我看你几乎站不稳了, 但没人能找到提钦吉图。 ";
			link.l1 = "扬给了我个提示... 我觉得我们那位严厉的马斯科吉人去酗酒了。 我们去萨博-马蒂拉峡走走, 有人看到他朝那个方向去了。 ";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "嗯, 那就是我们严厉的原住民, 没错! 来吧, 丹妮在郊区给我们找了间房子 —你现在都在梦游了, 查尔斯, 没错! ";
			link.l1 = "就是这样... 绑架我吧, 我美丽的女野人。 希望明天这一切都像噩梦一样过去。 ";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "别误会, 我的丈夫, 教堂里的一切都很奢华, 但这里的氛围显然更贴心, 没错! 好了, 查尔斯, 现在所有麻烦都过去了, 我们可以放松了。 ";
			link.l1 = "嗯, 还不是'所有', 我的妻子 —我们的生活还在继续! 可以说, 今天才刚刚开始。 所以, 我们走, 和兄弟们喝一杯, 然后 —嗯, 你记得的: 船舱, 美酒, 还有我们... ";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // 传送至船舱
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "我的丈夫... 听起来真甜, 没错! 现在你是我的了, 永远! ";
			link.l1 = "我早就属于你了, 而且永远都是, 我的爱人... ";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "我太高兴了, 查尔斯! 现在, 我们又要出发了, 对吗? ";
			link.l1 = "当然, 甜心! 并肩前行, 永远在一起! ";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// 杰森 莫娜岛
		case "IslaMona":
			dialog.text = "恐怕这场瘟疫正在折磨你的姑娘们, 罗德里戈。 让她们忙着织毛衣什么的! ";
			link.l1 = "这谈话显然毫无进展。 我们说好明天去教堂。 祈祷... 当然。 ";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "我为你骄傲, 我的爱人! ";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "嗯, 查尔斯... ";
			link.l1 = "你又在想什么, 玛丽? ";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(笑) 事实上, 我和艾伦曾想在岛上做和你现在做的一样的事";
			link.l1 = "你的... 艾伦? ";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "是的, 他是个十足的梦想家, 如果他还活着, 你们俩可能会成为好朋友! ";
			link.l1 = "嗯, 至少我们的品味在一件事上一致! ";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "什么? 哈哈哈! 别闹了查尔斯! \n不管怎样, 这太神奇了, 我们给了这些人太多快乐! ";
			link.l1 = "我们给了他们幸福的机会, 但剩下的, 是他们自己做到的。 那么, 你在想什么? ";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "晚点来找我, 你就知道了... ";
			link.l1 = "当然会! ";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "我喜欢黑暗和狭小的空间。 这让我感到平静。 终于可以整理思绪了\n仿佛所有烦恼和麻烦... 都消失了, 是的! 我真怀念这种感觉... ";
			link.l1 = "你需要看医生。 ";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "对。 就像你回到了'刻瑞斯铁匠号'。 ";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "... 可惜我不是一个人。 安静。 黑暗。 独处, 嗯。 那才完美。 ";
			link.l1 = "继续吧, 玛丽.卡斯帕。 ";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "有一次一只螃蟹爬进我床上 —我把它切碎吃了。 嗯。 ";
			link.l1 = "继续吧, 玛丽.卡斯帕。 ";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "蒙面混蛋! 哎哟! 亲爱的帮帮我 —我们得砸开这些铁条! ";
			link.l1 = "安静点! 我在想办法呢! ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "亲爱的, 这些蒙面恶魔到处都是! 他们在船体上撞了个大洞, 像那些螃蟹一样爬进来了! 我们得把他们都砍倒, 哎! ";
			link.l1 = "玛丽, 待在这儿, 找到高级军官, 接管指挥权! 把船开出战场; 我们经不起再一次登船了! ";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "那你要去哪儿? 我可不会让你走! ";
			link.l1 = "我得去帮赫拉克勒斯和我们的船员! 相信我, 玛丽! ";
            link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "是是, 亲爱的! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "胜利了, 哎! 到我这儿来, 亲爱的! 我想要你陪我一两个小时! ";
			link.l1 = "呃... ";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "我们走! ";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "嘿, 赫拉克勒斯! 真高兴见到你, 白胡子! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "玛丽, 玛丽, 等等! 我需要你的报告! ";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "哈? 嗯, 我们赢了, 哎! 那该死的船逃跑了。 我把一个混蛋的脑袋劈成了两半! \n呼, 该死的纽扣! ";
			link.l1 = "哦, 玛丽... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "哦, 上帝, 别看着我, 亲爱的! 我要... 呼! ";
			link.l1 = "坚持住, 姑娘。 我在这儿! ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> --------------------------------- —офицeрский блок ------------------------------------------
		case "Mary_officer":
			// eсли шлялся по бордeлям - устроит нeбольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! 我得和你谈谈, 没错! 认真地谈! ";
				Link.l1 = "怎么了, 玛丽? 有什么问题吗? ";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("我在听, 我亲爱的船长! ", "是的, "+pchar.name+", 我洗耳恭听! ", "你有什么任务给我吗, "+pchar.name+"? ");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "玛丽, 我要去拜访古老的印第安城市塔亚萨尔。 我不骗你: 这次旅行非常危险, 而且 —还包括通过我跟你说过的那个神像进行传送。 你会... 跟我一起去吗? ";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначeй///////////////////////////////////////////////////////////
			// boal отчёт о кораблe
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
				Link.l11 = "玛丽, 给我一份完整的船舶报告。 ";
				Link.l11.go = "QMASTER_1";
				
				// Warship。 Автозакупка товара
				Link.l12 = "我希望每次靠港时你都购买特定货物。 ";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "玛丽, 我需要你的建议。 ";
				Link.l3.go = "fugas";
			}
			Link.l1 = "玛丽, 我有一个命令给你... ";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("亲爱的, 我现在就想要你。 你愿意吗? ", "玛丽, 我们... 待在一起一会儿怎么样? 就我们俩。 ");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("玛丽, 我们租个房间待在一起吧? ", "亲爱的, 我想和你私下待着... 我们租个房间, 把一切都忘掉几个小时怎么样? ");
				Link.l2.go = "room_sex";
			}
			link.l9 = "目前没什么事, 玛丽。 ";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		//////////////////////// отвeты для казначeя ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "查尔斯, 她很漂亮, 没错! 我们修好了水线以下那个小小的洞, 把帆晒干了。 你... 期望什么? 别那样看着我, 我从没学过当财务官。 ";
			Link.l1 = "抱歉, 玛丽, 我真的没考虑清楚。 ";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "查尔斯, 但我什么都不缺! 我已经有了我的衣柜和我的剑。 但谢谢你的关心, 你真好, 没错! ";
			link.l1 = "但我甚至不... 不管了, 忘了吧, 亲爱的, 我们没事。 ";
			link.l1.go = "exit";
		break;

		case "stay_follow":
			dialog.Text = "命令? ";
			Link.l1 = "待在这里! ";
            Link.l1.go = "Boal_Stay";
			Link.l2 = "跟着我, 跟上! ";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "玛丽, 更换火器弹药。 ";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
			dialog.Text = "遵命, 我的船长! ";
			Link.l1 = "... ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
			dialog.Text = "遵命, 我的船长! ";
			Link.l1 = "... ";
            Link.l1.go = "Exit";
        break;
		//< —--------------------------------- —офицeрский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}