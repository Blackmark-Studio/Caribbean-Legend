void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

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
		
		case "BM_Contra_1":
			dialog.text = "你是谁, 你到底在这儿鬼鬼祟祟干什么? ! ";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "冷静点, 伙计。 我只是路过。 我不会干涉你的... 不管这是什么。 ";
			}
			else
			{
				link.l1 = "嗯? 这灯塔是你的? 下次在棕榈树上挂个带名字的牌子, 或者建个该死的篱笆。 ";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "离开这里! 如果你把客户吓跑搞砸了交易, 我... ";
			}
			else
			{
				dialog.text = "听着, 小子, 别逼我和我的兄弟们叫你出来看看你的刀刃是否和你的舌头一样锋利。 消失吧, 并且... ";
			}
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "好吧, 弗兰基, 是哪一个? ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "不... 我该死, 但我不认识这些家伙中的任何一个。 ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "什么? ! 你确定吗? ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "你以为我瞎了吗? ! 我告诉你, 什么... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "搞什么鬼? ! ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "谁开的枪? ! ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "你以为我们是傻瓜吗, 败类? 把你们的枪都放在地上, 所有人! 还有你! ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "冷静点, 军官。 不是我们, 你看不出来吗? 我们的枪还在原来的地方。 你也别碰你的枪! ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "你在给我下命令吗, 混蛋? ! 马上逮捕他们所有人! ";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "去你的! 那不可能发生。 伙计们, 拿起武器! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "嘿, 嘿, 小心点! 如果你继续这么疯狂地挥舞那杆枪, 可能会有人被杀。 ";
			link.l1 = "哈, 谁? ";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "我, 当然。 ";
			link.l1 = "什么... ? 你到底是谁? ";
			link.l1.go = "BM_Irons_4";
			link.l2 = "这正是我想做的。 我们开始吧? ";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "我是汤米! 汤米.艾恩斯。 我想。 你是谁? 你是个勇敢的女人, 我告诉你, 像那样四处走动, 呵呵。 ";
				link.l1 = "确实勇敢。 如果有必要, 我也不怕让你闭嘴。 这地方很热, 所以我穿得很轻便 —不是为了取悦你或你这样的人。 我叫海伦.麦克阿瑟。 朋友们可能叫我伦巴, 但你肯定不是我的朋友。 那句'我想'是怎么回事? ";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "我是汤米! 汤米.艾恩斯。 我想。 你呢? ";
				link.l1 = ""+GetFullName(pchar)+"。 那句'我想'到底是什么意思? ";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "那正是它的意思。 我失去了记忆 —在战斗中被打得很惨。 你知道, 有时你会失去一切。 不过我很幸运。 我只是忘了自己的名字。 幸运的是, 我脖子上戴着这个吊坠, 上面写着'托马斯'。 但我更喜欢汤米。 还有艾恩斯。 我为克伦威尔的铁甲军打过仗, 记得吗。 但'铁甲军'太笨重了。 艾恩斯好多了。 ";
			link.l1 = "我知道你的问题了, 汤米。 那么, 告诉我 —那是什么? 你是特意瞄准某人吗? 你打中目标了吗? 还是你只是为了好玩而射击? 我不会感到惊讶。 ";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "我打中了, 而且打得很狠! 在各方面。 还记得那些穿着花哨裤子的人吗? 他跟踪我的踪迹, 还带了士兵来。 整整一个小队, 就因为我和他妻子睡了。 ";
			link.l1 = "你确实打中了, 呵呵。 我想他是当场抓住你们俩了? ";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "哈! 你不会相信的 —没有。 那个女人后来坦白了。 良心不安, 或者也许她不像我那样享受, 呵呵。 谁知道女人脑子里在想什么? 我真的不在乎, 哈哈哈! ";
			link.l1 = ""+GetSexPhrase("嗯, 她是个怪人。 ","男人... 前一分钟你还在试图弄清楚我们在想什么, 下一分钟你就说你不在乎。 但有一点你说得对 —她的所作所为很奇怪。 她应该像做了个噩梦一样离开并忘记。 如果到了那种地步, 我也会这么做。 ")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "正是! 人们说我有问题。 我为死去的士兵感到难过。 我知道这一点, 我自己也曾是个小兵。 我没告诉过你吗? ";
			link.l1 = "是的, 你说了。 来自铁甲军。 克伦威尔。 ";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "哦, 是吗? 我不记得我说过没有。 你知道我是怎么来到新世界的吗? 要我告诉你吗? ";
			link.l1 = "不, 而且我也不会感兴趣, 汤米。 ";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "会的, 会的。 我会告诉你。 ";
			link.l1 = "好吧, 管它呢, 开枪吧。 我是说, 继续。 ";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "那就别打断我! 我刚才说到哪了? 对, 我受伤了, 明白吗? 因为我在胜利的一方, 所以得到了正式的辞职。 但你应该看看那些办公室老鼠的表情! 他们认为我在假装, 假装失去记忆。 他们一直问我关于家人的事。 ";
			link.l1 = "那么, 你告诉他们什么了? ";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "我告诉他们什么了? 我告诉他们我不记得了。 而且我没有撒谎 —我从来不知道我的家人。 我是在街头长大的, 由贫民窟的工人和仆人抚养长大。 我为了他们加入了革命。 尽管人们的忘恩负义令人惊讶 —如果我失去了一条胳膊或一条腿, 他们就不得不让像我这样的英雄立即退休。 顺便说一句, 我差点掉了脑袋, 真的! ";
			link.l1 = "那么, 战争英雄, 你是怎么来到新世界的? ";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "你怀疑吗? 为普通人而战 —这有什么不英雄的? 我希望有一天像你这样的娘娘腔会知道什么是真正的自由! ";
			link.l1 = "虽然自由是件好事, 但不知怎的你说得像个威胁。 好吧, 汤米, 继续。 ";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "是的。 革命胜利后我得到了辞职, 然后我意识到除了射击和打人, 我什么也做不了。 而且你不能重新参军 —他们会嘲笑你, 尤其是在我为辞职而努力奋斗之后。 呵呵, 在我看来, 即使我真的失去了一条胳膊或一条腿, 那些办公室老鼠仍然会认为我把它们藏在某个地方, 等拿到离职文件后再缝回去, 哈哈哈! ";
			link.l1 = "真有趣。 但你还没告诉我你是怎么到这里来的。 ";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "哦, 你真无聊。 他们没教过你耐心吗, " + GetSexPhrase("年轻人","我的女孩") + "? 我在家里除了射鸭子和鹿什么也没做, 所以我去了新世界。 为了好玩, 我和海盗一起航行了一段时间, 当我厌倦了无法无天时, 我成了一名雇佣兵。 ";
			link.l1 = "不是很原创的故事。 ";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "也许你有更好的故事? 你碰巧不需要保镖吗? 因为你看起来... 很虚弱。 我担心你走不远, 呵呵。 记住, 是随从造就了国王。 而糟糕的随从会让他们垮台。 ";
			link.l1 = "有你这样的随从, 我会成为什么样的" + GetSexPhrase("国王","女王") + "? " + GetSexPhrase("国王","女王") + " of the dung heap? ";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "不, 不! 我在给你一个真正的提议, 而你... ";
			link.l1 = "我还没有收到任何提议。 你为你的服务要价多少, 汤米? ";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "预付二百五十达布隆! 以确保我知道你是认真的, 而不仅仅是个失败者。 之后还有月费。 我想我们可以达成协议。 ";
			link.l1 = "你不... ";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... 觉得你有勇气吗? 呵呵, 我甚至不会和你争论 —你看到我是怎么从灯塔射死那个奸夫的吗? 第一枪! 也没有讨价还价, 如果你是这么想的。 你需要证明你能雇得起像我这样的专业人士。 ";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "是的, 我可以! 二百五十金币。 给你。 ";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "你那一枪很幸运。 现在你试图用吹嘘来抬高自己的价值。 没有像你这样的专业人士我也能行。 这太荣幸了, 也太贵了。 ";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "我现在买不起, 因为我口袋里没带那么多。 待在这里别到处走 —我会从船上拿金子回来。 ";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "你不像我想的那么差! 但你最好确保我不会感到无聊。 浪费我的才能, 不是吗? 汤米和" +pchar.name+ "! 让我们震撼加勒比海! ";
			link.l1 = "学会尊重指挥系统, 汤米。 其次, 对你来说我是船长。 明白吗? ";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "呵呵, 我明白, 无聊的船长, " + GetSexPhrase("先生","小姐") + "。 ";
			link.l1 = "哦, 我已经开始后悔了... ";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
			
			// Продолжение через неделю в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "好吧, 你是个白痴, 年轻的" + GetSexPhrase("男人","女人") + "! 而且完全缺乏判断力。 我建议你解决这个问题, 否则你活不了多久。 尤其是在群岛上。 ";
			link.l1 = "没有你我也能行, 汤米。 再见。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "你是认真的吗? 天才! 这里刚死了一群士兵! 他们可能很快会再派一个小队来。 不, 我可以锁上灯塔的门, 组织防御, 但我想这么做吗? 不。 ";
			link.l1 = "那你建议怎么办? ";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "在丛林里的一个洞穴见我。 我给你几天时间赚足够的钱来支付我的服务 —你知道如何握剑, 也许你能做到。 ";
			link.l1 = "你是认真的吗? 你在那里会像一只被困住的老鼠。 ";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "只有当他们专门用大部队搜捕我时才会。 所以我想我会没事的。 现在我必须走了 —他们很快就会到这里。 回头见。 ";
			link.l1 = "是的, 以防万一, 我也得走了。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "是的, 你来了! 我开始觉得你没有赚钱的能力。 有时我认为像你这样的人天生就有。 如果没有, 他们就会像诚实的人一样不工作一天就死于贫困。 ";
			link.l1 = "好了, 好了, 汤米。 如果你不想加入我的船员, 那就不加入。 我看你喜欢在这个洞里筑巢。 ";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "显然你没在爱尔兰雨季躲在坑里过, " + GetSexPhrase("年轻人","我的女孩") + "! 但和你一起走比躲在这里好。 现在, 关于那笔金子... ";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "这是你的金子。 ";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "我还没拿到。 我想看看你是否跑到别的地方去了。 ";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "现在我们在谈! 接下来我们做什么... 船长? ";
			link.l1 = "首先, 让我们离开这个潮湿的地方, 否则我要开始打喷嚏了。 ";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "哦, 你应该试试战争。 我在这种地方几乎有宾至如归的感觉。 ";
			link.l1 = "我明白了, 所以你得到辞职后就忘记了尊重和服从, 嗯, 汤米? 别担心, 如果有必要, 我会毫不犹豫地再教你一次。 现在我们走吧。 ";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "呵呵, 汤米.艾恩斯从不逃跑! 他信守诺言。 你会信守你的诺言吗? ";
			link.l1 = "正在努力。 ";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "你带金子了吗? ";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "这是你的金子。 ";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "我还没拿到。 我想看看你是否跑到别的地方去了。 ";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "听着, 船长... ";
			link.l1 = "怎么了, 汤米? ";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "你身上有没有多余的弹药? 不只是一颗子弹, 而是一整发, 用纸包着的子弹。 ";
			link.l1 = "这又是你的一个笑话吗? 我定期给你子弹和弹药, 你需要什么就给什么。 为什么正好是一发子弹, 而不是一把? ";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Why are you taking my request so badly? I ain't asking for bloody pearls, just a cartridge. I even waited for the right moment so I wouldn’t distract you from business or get in your way like some lunatic, hehe. So... got a bullet?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "是的, 我有一发。 给你。 只是别用那颗子弹跟我开愚蠢的玩笑。 明白吗, 汤米? ";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "目前没有。 我又不是在口袋里装着一发子弹, 想着万一汤米要呢... ? ";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "嗯, 这是个好点, 你反应很快, 呵呵。 但恐怕我们要在这里分道扬镳了。 ";
			link.l1 = "你是认真的吗? 你为了一颗子弹生气? 来吧, 我们去船上拿一颗。 如果你这么急需, 我给你一颗, 十颗, 随便你需要多少。 ";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "不。 毕竟你没什么特别的。 一个好船长总能为他的船员提供所需的一切。 所以我要走了。 ";
			link.l1 = "如果我们在海上, 朗姆酒喝完了, 你想要更多? 你会解开小艇自己划走吗? 还是跳进水里? ";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "哈哈哈! 我笑了, 但在这个悲伤的时刻, 即使是一个好笑话也无济于事。 再见, 无聊的船长。 ";
			link.l1 = "好吧, 去你的, 汤米。 再见。 ";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "不能保证什么, 嘿嘿。 好笑话能让事情轻松。 但当然要谢谢你。 ";
			link.l1 = "好了, 我们走吧, 你这个爱开玩笑的人。 ";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			ReturnOfficer_Irons();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "嘿, 船长! ";
			link.l1 = "怎么了, 汤米? ";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "还有纸包子弹吗? ";
			link.l1 = "上一发怎么了? 那个子弹笑话是怎么回事? 我等了你两周的愚蠢笑话, 但什么也没有。 ";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "哦, 这将是一个致命的笑话, 相信我。 你会喜欢的, 呵呵。 只是还没把它组合起来。 那么子弹呢? ";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "给你。 我希望我真的喜欢你即将到来的恶作剧。 你把上一发子弹放在哪里了? 我给了你很多。 或者你把战斗用的弹药和笑话用的分开存放? ";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "我没带弹药来应付你愚蠢的笑话, 汤米! 你本可以在两周前要一整批而不是一发子弹! ";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "我做了! 我以为那个自称是我船长的人总是备有船员需要的东西。 ";
			link.l1 = "我没有假装什么, 汤米。 很久以前我就选择做自己。 谁觉得和我在一起舒服, 很好。 如果不, 也没关系。 ";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "呵呵, 在这方面你我很像。 但我对我的船长有一定的要求。 而你不再满足这些要求了, 年轻人。 我们就在这里分道扬镳吧。 ";
			link.l1 = "你是认真的吗? 就因为我没有该死的纸包子弹? ";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "这是毫无疑问的。 我通常建议人们做他们喜欢的事, 从生活中获取他们想要的东西。 我建议你以后多为你的人着想。 再见。 ";
			link.l1 = "我也建议你照顾好你的头 —他们对你的伤害比你意识到的要大。 再见, 汤米。 ";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "你会发现的。 一切都会及时的, 呵呵。 ";
			link.l1 = "哦, 我有一种不好的感觉, 汤米... ";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			ReturnOfficer_Irons();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "我有个问题要问你, 船长。 ";
			link.l1 = "怎么了, 汤米? ";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "你没猜到吗? 猜测是一项有用的技能, 呵呵。 你, 我, 丛林... 大约两周前, 我们有过这样的对话。 我需要另一发纸包子弹。 ";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "这正在成为一个有趣的传统, 不是吗? 已经两周了 —汤米要子弹。 给你。 你的那个笑话还需要多少发? ";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "还要多久, 汤米? ! 这要持续多久? 你们铁甲军每次战斗前只拿一发子弹吗? ! 你知道, 我不必一直为你的怪癖保留一发子弹! ";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "实际上, 作为我的船长, 你有责任为我提供战斗及更多所需的一切。 ";
			link.l1 = "你搞错了, 汤米。 服从船长的命令是你的职责。 我总是为你们所有人提供一切 —药品。 弹药。 朗姆酒。 你不及时拿你需要的东西, 然后表现得像个乞丐, 这完全是你的错! ";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "你真聪明 —为什么你到现在还没有在这里取得任何显著成就? 我来告诉你为什么。 因为你不提前思考, 而且对任何事情都没有准备。 你不知道自己在做什么, 你这个无聊透顶的人。 我不会承认这样的人是我的指挥官, 所以再见。 ";
			link.l1 = "而你根本不动脑子! 滚吧, 你这个该死的小丑! ";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "这发就够了, 呵呵。 ";
			link.l1 = "那么你终于准备好了? 但为了什么? ";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "我只是在跟你开玩笑, 看看你是否会变回你那暴躁的样子。 呵呵。 但还是谢谢你的子弹。 ";
			link.l1 = "你的笑话很奇怪, 汤米。 ";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "那也是个笑话。 我不是在收集它们; 我在挑选它们。 需要一发接近完美的子弹。 这发就行。 是的, 有了这发子弹, 子弹会飞得又远又准。 就像我打爆老雷斯雷的头时一样, 哈哈哈! ";
			link.l1 = "老雷斯雷, 你说... 弗兰基那个奸夫, 是吗? 那么, 你们认识很久了? ";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "什么? 哦, 该死, 我说漏嘴了。 但我不在乎 —我从来都不擅长撒谎或保守秘密。 ";
			link.l1 = "我猜第二发子弹是专门为某人准备的, 是吗, 汤米? ";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "对, 天才。 嗯, 我了解自己和我的目标, 我并不羞耻。 这就是为什么我不在乎你怎么想 —我会告诉你整个故事, 为什么不呢。 ";
			link.l1 = "那么, 告诉我吧。 知道你在做什么也没什么坏处。 ";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "好吧, 别像往常一样打断我。 和我在一起的公司里有两个混蛋 —弗朗西斯.雷斯雷和加布里埃尔.卡洛。 真正的老鼠! 比那些不给我辞职的办公室老鼠还要糟糕, 你知道, 那并不容易得到。 ";
			link.l1 = "他们做了什么? 尤其是第二个, 卡洛。 你也和他妻子睡了吗? 他也派士兵追你? ";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "闭上你的嘴, 好吗? 虽然... 我不介意, 呵呵。 但没有。 那天保皇党袭击了我们。 还有骑兵。 他们人数多得多。 盖比和弗兰基像受惊的兔子一样跑了。 但我和兄弟们留了下来。 我是唯一的幸存者。 我忘记了很多童年和青年时期的事情, 但不是那件事。 ";
			link.l1 = "你想要复仇是因为他们逃跑了? 不是每个人都为了一个想法而战斗。 每个人都想生存。 或者几乎每个人。 即使有人为革命而战, 他们可能是偶然加入并后悔了。 ";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "哈, 如果我追捕每个懦夫, 我就得射杀全世界。 懦夫, 去他们的。 但他们背叛了我。 他们告诉每个人我背叛了革命, 并在国王支持者的命令下屠杀了我们整个连队。 我骗了你一件事, 船长。 ";
			link.l1 = "是什么? 除了你谎称弗兰基只是因为你和他妻子的所作所为而追捕你? ";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "不, 不! 我没有骗你, 我只是没有告诉你一切。 这是有区别的。 我撒谎的是辞职。 没有辞职。 有一个法庭。 幸运的老汤米 —他们决定不绞死他, 而是把他送到南部殖民地的采石场。 确切地说是巴巴多斯。 ";
			link.l1 = "是的, 那很幸运。 你在那里工作了多少年? ";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "没有。 既然世俗法庭因为那些卑鄙小人判了我的刑, 天上的那个法庭便决定救我。 我们一进入群岛, 就感受到了它的氛围 —我们的船被海盗登船了。 ";
			link.l1 = "所以, 你没有去巴巴多斯的采石场和种植园, 而是被海盗卖为奴隶? 但你说你从未在采石场工作过。 ";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "我就是这么说的 —楼上有人决定救我。 这是多么的救援啊, 呵呵! 你说得对 —海盗战胜了那些喜欢虐待被捆绑和锁链束缚的人的人。 但这仍然是一场激烈的战斗, 和这里的太阳一样热。 我们的救星遭受了一些伤亡。 所以他们邀请每个愿意的人加入他们。 ";
			link.l1 = "你加入他们了吗? 你说你和海盗一起航行过。 ";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "当然! 我生命中最美好的时光。 杰克.米尔斯是个真正的船长 —我希望有一天你能像他一样。 我在他的'起重机'号上航行了大约两年, 直到... ";
			link.l1 = "... 直到你像你说的那样厌倦了无法无天? 你为什么说那些是你生命中最美好的时光? ";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "呃... 直到我听说那两个叛徒也来到了群岛。 是的, 我知道, 我说过我厌倦了公海海盗之类的。 而且我已经告诉过你我不在乎你怎么想。 这仍然是真的, 但我们第一次见面时我不太了解你。 不知道你会有什么反应。 这就是为什么我说了不同的话。 ";
			link.l1 = "你是个骗子, 汤米! 但好吧, 你为什么离开'起重机'号? ";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "因为杰克是个真正的领导者, 所以他说他不会为了一个人绕道而行, 等他, 玩复仇, 惹英国海军的高级军官, 而不是攻击肥胖的商船。 ";
			link.l1 = "高级军官? 弗兰克是个平民, 我想。 ";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "呃, 他并不总是这样。 他总是有点, 你知道, 阴暗。 当他试图陷害某人时, 他被不光彩地赶了出去。 他试图驾驶一艘商船, 但诚实的工作不适合他。 最后他在这里定居了。 ";
			link.l1 = "仍然不会称他为高级军官。 ";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "别忘了盖比。 他在国内当上了中尉。 他在皇家港获得了委任, 担任'Principio'号船长。 ";
			link.l1 = "听起来不太像英语。 ";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "说得好! 这艘船像港口少女一样易主, 所以它见证了各种各样的事情。 但她仍然适航。 而且盖比是个熟练的船长, 该死的他。 ";
			link.l1 = "杰克害怕和他打交道吗? 他真的像你说的那么好吗? ";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "好吧, 好吧! 更像是他不想为了我浪费时间。 说到杰克, 我喜欢我第一次从他那里看到的几个传统 —木板和发放黑色印记。 这让我当时有了一个有趣的想法。 ";
			link.l1 = "黑色... 标记? 你是说一个黑点, 对吗? 那是什么, 汤米? 我不认为如果你递给他一个黑点, 他会知道该怎么办。 是这样吗? 你想交给他, 他一看到你就攻击你, 所以你跑到灯塔, 他带了一队士兵, 告诉他们你是海盗? ";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "我更喜欢称之为黑色印记。 听起来更好。 一个简单的黑色印记不会让他意识到什么。 但用我们的丝绸手帕做成的黑色印记, 这是我们连队的一个显著特征 —他会明白的。 我小心翼翼地把它塞进他的口袋。 然后我确保他看到我走向灯塔。 你知道剩下的。 ";
			link.l1 = "那走私者呢? ";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "错误的时间, 错误的地点。 我甚至有点为他们感到难过。 但只是一点点, 呵呵。 ";
			link.l1 = "那弗兰基呢? ";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "现在谁在乎? 我们有更大的鱼要煎。 剩下的就是盖比了。 这将是棘手的。 我们需要... ";
			link.l1 = "我们? ";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "嗯, 了解一个有趣的故事是一回事, 自己创造一个故事是另一回事! 所以计划是这样的。 我们需要给盖比留下另一个特殊的黑色印记 —我已经做了一个。 然后我们将跟踪他的踪迹到波特兰峡, 在那里我们将处理他, 不留下任何痕迹。 ";
			link.l1 = "我们要把它种在哪里? ";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "哈哈哈, 这就是我所说的, 船长, 我希望你更像杰克。 来吧, 别那么无聊, 我可以看到你的眼睛在燃烧! ";
			link.l1 = "更确切地说, 我实际上对你的故事有点感兴趣。 ";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "当然是在他的房子里! 这是什么问题? 他在皇家港定居了。 所以你和我将在海湾停泊, 这样如果出了什么问题, 我们可以离开岛屿。 ";
			link.l1 = "你知道他的房子在哪里吗? ";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "不知道。 但不难找到。 我们会问酒鬼 —如果你给他们买一两杯酒, 他们会卖掉他们的母亲。 那么, 你觉得我的计划怎么样? ";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "如果他是一艘前往牙买加的船的船长, 他一直在岛屿水域巡逻。 用假旗攻击比在城市里尝试任何事情都好。 ";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "这并非没有缺陷, 你太依赖运气了。 但总的来说, 可行。 我支持你, 汤米。 你解决了一个, 不能让另一个跑了, 对吧? ";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "我不想卷入你的复仇, 为了这个冒险而冒险破坏我与英国的关系, 汤米。 ";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "你是个敢于冒险的人, 船长! 我开始喜欢你了。 但是老'Principio'号上的盖比不是容易的猎物 —他比那样的船上的其他船长危险得多。 ";
			link.l1 = "你以为我是什么, 懦夫吗, 汤米? 我们会亲自登上他的船, 你可以和他进行一次心与心的交流。 在他被废黜之前给他黑点。 ";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "呵呵, 你可能不是懦夫, 但他是, 尽管他很聪明。 他不会攻击比他的船更大的士兵甚至海盗。 如果他在地平线上看到那样的东西, 他会躲在堡垒的翅膀下。 ";
			link.l1 = "嗯, 商船呢? ";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "是的, 那可能行得通! 但同样, 没有比三桅帆船或小型三桅帆船更大的! 盖比不仅是个懦夫 —他从来没有贪婪到让贪婪超过他的谨慎。 ";
			link.l1 = "希望如此, 汤米。 那么, 悬挂西班牙或荷兰旗帜的五等三桅帆船或小型三桅帆船。 准备好迎接你的老战友吧! ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "我就知道我可以指望你! 有一天你甚至可能成为比杰克更好的船长。 至于我的运气... 它让我走到了这一步, 所以我会再次依靠它。 那么我们走吧? ";
			link.l1 = "是的, 我们不要拖得太久。 结束得越快越好。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "呵呵, 我希望不然, 但我预料到了 —你没有勇气做这种事, " + GetSexPhrase("年轻人","我的女孩") + "。 任何真正的船长都至少有几次这样的情况, 他谨慎地处理了老鼠。 有时甚至是他们自己的老鼠。 ";
			link.l1 = "我想我应该落入那个陷阱, 说我改变了主意, 并证明我是一个真正的船长, 嗯, 汤米? 但我理解你复仇的愿望。 我不会像杰克那样强迫你离开船员。 你需要多少时间? 到那时我会去牙买加。 ";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "哈哈哈, 你在成长。 我几乎因为你没有落入陷阱而尊重你。 但你不必等我然后来接我 —我会自己完成这件事。 毕竟, 我曾经想要的只是有人愿意作为我的船长为我做些事情。 所以再见。 照顾好英国, 哈哈。 ";
			link.l1 = "你真的很奇怪。 但如你所愿。 再见! 祝你复仇顺利, 汤米。 ";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "太好了, 如果有需要, 我们可以从这里快速撤退。 拿着这个 —一旦你发现盖比住在哪里以及他什么时候在家, 就把这张纸条和一个黑色印记给他。 ";
			link.l1 = "哦, 所以现在你在发号施令, 汤米。 但记住, 我仍然是你的船长。 我在城里的时候你打算做什么? ";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "呵呵, 我怎么会忘记呢, 无聊的船长? 如果盖比在街上看到我, 他要么会发出警报, 要么会溜出岛屿, 那个该死的懦夫。 别担心, 我会在这里设下埋伏, 呵呵呵。 ";
			link.l1 = "你说埋伏。 好吧, 汤米。 让我们给你的老战友一个恰当的重逢, 哈哈哈哈! ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = " 嗝! 那是很棒的朗姆酒! 嗝... 干杯! ";
				link.l1 = "听着, 伙计, 关于加布里埃尔.卡洛船长, 镇上有什么说法? ";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "老盖比? ! 只有好话! 为什么,  嗝, 那是什么? ";
			link.l1 = "哦, 真的吗? 很高兴听到。 嗯, 有个海盗麻烦。 指挥官主要处理陆地事务, 我不想打扰大人。 ";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "那你就直接去找盖比, 我告诉你! 镇上没有比盖比更诚实或勇敢的船长了。 甚至多伊利上校也很看重他。 他驾驶的船曾经属于Nicholas Sharp本人, 你能相信吗? ";
			link.l1 = "我还没醉到现在就相信, 伙计。 ";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "是-是的, 但你是! 是Principio号! 听起来耳熟吗, 嗯? ";
			link.l1 = "一艘西班牙战利品船, 是吗? 为什么? ";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "А你上次亲眼看到粉红色是什么时候, 嗯? 我知道我在说什么,  eek! ";
			link.l1 = "嗯, 我不知道这艘船的设计是否那么不寻常。 ";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "但它是! 现在没有人会指挥这样的垃圾, 周围都是新设计! 他们几乎在三十年前就停止在造船厂建造它们了! 尼克自己驾驶过她, 我告诉你。 ";
			link.l1 = "好吧, 我接受。 那么, 她就是那艘船。 这艘残骸怎么还没散架? ";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "我们的";
			else sStr = "你们的";
			dialog.text = "嗯, 她不像她最好的岁月那么快了 —就像我再喝一杯后一样, 哈哈哈! 但一个好船长仍然可以从这位老妇人身上得到一些东西。 盖比也尽量不让她置身于火线。 ";
			link.l1 = "那么为什么这艘船没有被重新命名? 也许在" + sStr + "旧政权下叫'鞭打号'陛下的船? ";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "传统... 传统-传统-传统,  eek! 尼克自己从古巴的一个西班牙种植园逃跑后从未重新命名过她。 他不想忘记这段经历 —西班牙人也没有! 让我告诉你, 在滕代尔斯海岸附近的那场战斗... ";
			if (startHeroType == 4)
			{
				link.l1 = "滕代尔斯, 对吗? 嗯, 我还是个孩子的时候最后一次听到这个名字。 我没想到现在还有人知道并记得这些现在被遗弃的岩石。 ";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "滕代尔斯? 那是哪里? ";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "或者是, 呃, 海岩岛? 不, 肯定不是那里... 不管怎样, 这不重要! 尼克在那艘粉红色船上战斗并获胜, 对阵德斯蒙德.雷.贝尔特罗普海盗男爵派来的‘墨鱼’号双桅船, 取得了难以置信的胜利。 他们互相厮杀了很久, 直到尼克亲手砍倒了德斯蒙德。 ";
			if (startHeroType == 4)
			{
				link.l1 = "哇, 太令人印象深刻了! 尽管, 你不会对尼古拉斯有别的期待。 嗯, Sharp家族和贝尔特罗普家族总是分分合合 —显然, 历史确实会时不时重演。 ";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "令人印象深刻。 那么, Sharp是怎么处理这艘船的? 在造船厂卖掉了? ";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "不。 那次登船后, 她开始漏水, 所以尼克遗弃了她。 然后随着大潮, 这艘粉红色船被冲到岸边, 就在城镇附近。 ";
			link.l1 = "好像有人会对那堆残骸感兴趣似的。 ";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "哦, 但海军感兴趣! 讲究实际的家伙们。 他们看到一艘挂着英国国旗却有西班牙名字的船, 就产生了兴趣。 尼克几年后去世了, 但他的船继续航行, 易主多次, 总是伴随着血腥。 ";
			link.l1 = "这只是另一个幽灵船的故事, 而盖比的船长职位是非常真实的。 所以, 我想我会去见他。 你知道他住在哪里吗? ";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "哈哈! 当然知道, 呃, 我知道! 每个人都知道! 老盖比住在老风车旁边。 绕过酒馆然后抬头看... 呃! ";
			link.l1 = "他什么时候在家? 听起来他是个忙碌的人。 ";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "没错, 伙计! 他有很多事情要做。 他只在晚上十点后在家。 而且他每天六点准时起床, 自己起来。 钢铁般的纪律! ";
			link.l1 = "非常感谢! 我现在已经听够了这些海盗故事。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "你真的是... 伦巴? 我听说过你... 但你以前从未背叛过自己人! ";
				link.l1 = "我也没有。 我和我的国家没有争执。 我和你有争执, 盖比。 ";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "你不是商人... ";
				link.l1 = "惊喜吧, 盖比! 有人告诉我你很谨慎, 甚至有些懦弱。 贪婪蒙蔽了你的判断, 不是吗? 没有商人会像我这样寻求登船。 ";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "和我? 有什么问题? 我们可以在我家或者甚至你家好好谈谈。 像船长一样, 还有... 你在这里做什么? ! ";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "确实。 那么你是谁? 不, 去你的。 那是谁... ";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "托马斯, 是你吗... ? ";
			link.l1 = "哦是的, 盖比。 我来是为了惩罚你那天对我所做的事。 ";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "惩罚我? ! 注意你的言辞, 托马斯! 如果我们中有谁该受惩罚, 那就是你! 你说你会带援军来! 而我们在等待, 死在国王骑兵的子弹和剑下! ";
			link.l1 = "我拼命跑去求援! 但我被另一股该死的力量追上了! 查理的该死支持者无处不在! 他们把我困住了, 我差点死了! 幸好他们以为我死了。 但你知道我看到了什么吗, 盖比? ! ";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "看到什么, 汤姆? 你愿意编造任何故事来让这个人相信你吗? ! ";
			link.l1 = "呵呵, 反正那个人不会背叛我。 他不像某些人是老鼠。 ";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "他别无选择! 攻击英国海军的船! ";
			link.l1 = "哦, 他从一开始就有选择。 他选择帮助我。 你和弗兰基也有选择。 你们选择逃跑, 这样就不会死。 然后你们回来发现我半死不活。 你们在法庭上撒下恶毒的谎言。 你们知道没人会听我的, 因为我被击中头部失去了记忆! ";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "反正没人会听你的。 你总是个... 脑子坏掉的, 托马斯。 ";
			link.l1 = "哦, 所以你不否认你那天的所作所为。 我有东西给你, 盖比。 一个黑色印记。 但现在船已经被征用, 我们正要让你吐露实情, 嘿嘿嘿嘿嘿嘿... ";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "嗯, 盖比被废黜了, 呵呵。 这句话我早就想说了。 可惜你再也听不到了, 伙计。 哦等等! 你可能会 - 从地狱里。 ";
			link.l1 = "得了吧, 汤米。 即使他没听到, 他也看到并知道这正是你的计划和复仇。 而且他对此无能为力。 ";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "呵呵, 你说得对! 该死的对! 谢谢你在这件事上帮了我。 你知道, 我原以为你只是个穿着华丽服装的被宠坏的女孩, 得到一艘船只是为了兜风。 但你是个该死的好船长! 我敢打赌你能和杰克一较高下。 ";
			}
			else
			{
				dialog.text = "呵呵, 你说得对! 该死的对! 谢谢你在这件事上帮了我。 你知道, 我认为你和杰克一样是个好船长。 或者更好! ";
			}
			link.l1 = "哦, 现在你在奉承我。 谢谢。 我想。 ";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "一点也不。 完全没有奉承。 正如你可能已经注意到的, 我很少那样赞扬别人。 所以闭嘴, 庆幸我如此看重你";
			link.l1 = "我不会说我喜欢你的表达方式, 尽管我很高兴你总体上认为我是个好船长。 但是... 指挥系统, 汤米, 指挥系统。 ";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "哦, 得了吧! 我觉得我们经历的一切让我们更亲近了, 艾莉。 我们可以不只是船长和军官。 承认吧 - 即使只是对自己承认, 你也有同样的感觉。 ";
				link.l1 = "只有在你最疯狂的梦里, 汤米。 我叫海伦, 不是艾莉。 但我想现在你可以叫我伦巴了。 ";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "哦, 得了吧, 你这个无聊的人! 在我看来, 我们不再只是船长和他的军官, 而是最真正的朋友。 你不这么认为吗? ! ";
				link.l1 = "呵呵。 也许吧。 做你的朋友比做你的敌人好。 既然礼仪显然不是你的强项, 我想我只能习惯了。 ";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "我有个... 礼物给你, 船长。 ";
			link.l1 = "哇, 看看那个! 一个黑点? 你也想让我被废黜吗, 汤米? 你想自己当船长? 哈哈哈哈! 我以为你说过我们是伙伴。 ";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "这是个黑色印记, 你这个蠢货。 你知道, 我开始觉得一旦我在这条围巾上绣上骷髅头和骨头, 它就开始给我带来好运。 我无法解释。 拿着它。 还有... 如果你愿意, 你可以随时借用我可靠的剑和盔甲... 剩下的部分, 哈哈! 它会派上用场的! 你会走得很远。 而我想见证这一切。 我不想让你被流弹打死。 ";
			link.l1 = "谢谢, 伙伴! 我会尽力的。 而你 - 看着并欣赏吧, 哈哈哈! ";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "欣赏, 当然, 哈哈哈。 是的。 那么, 你决定怎么处理这艘船? 一方面, 它已经没什么用了。 另一方面, 再也没有像它这样的船了。 我认为以后也不会有了。 ";
			if (startHeroType == 4) 
			{
				link.l1 = "我还没决定... 你知道, 汤米, 我对这艘船有一种联系。 我无法解释。 所以, 让我们先把这具发臭的尸体弄走。 如果货舱没有漏水, 我可能会自己留下这个女孩。 ";
			}
			else
			{
				link.l1 = "我不知道, 汤米。 我还没决定。 与此同时, 让我们处理掉盖比的尸体。 以防我们真的保留这艘船。 ";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "嗯, 你在那艘古老的船上干得相当不错, 船长! 虽然我想亲手解决盖比, 但我不会因为轻视这场胜利而触怒造物主。 ";
			link.l1 = "那没有必要, 汤米。 我希望你的灵魂现在得到安宁。 ";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "我觉得我们经历的一切让我们更亲近了, 艾莉。 我们可以不只是船长和军官。 承认吧 - 即使只是对自己承认, 你也有同样的感觉。 ";
				link.l1 = "只有在你最疯狂的梦里, 汤米。 我叫海伦, 不是艾莉。 但我想如果你停止这种奉承, 现在可以叫我伦巴了。 ";
			}
			else
			{
				dialog.text = "我这辈子从未如此开心过! 谢谢你帮我度过这个难关。 你知道, 我认为你作为船长和杰克一样好。 或者更好! ";
				link.l1 = "哦, 你过奖了。 也谢谢你的比较, 我想。 ";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "一点也不。 完全没有奉承。 正如你现在可能已经注意到的, 我很少那样赞扬别人。 所以闭嘴, 庆幸我如此看重你。 ";
				link.l1 = "我不会说我喜欢你的表达方式, 但我很高兴你总体上认为我是个好船长。 但是... 指挥系统, 汤米, 指挥系统。 ";
			}
			else
			{
				dialog.text = "一点也不。 完全没有奉承。 正如你现在可能已经注意到的, 我很少那样赞扬别人。 所以闭嘴, 庆幸我如此看重你。 ";
				link.l1 = "我不会说我喜欢你的表达方式, 但我很高兴你总体上认为我是个好船长。 但是... 指挥系统, 汤米, 指挥系统。 ";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "哦, 得了吧, 你这个无聊的人! 在我看来, 你和我不再只是船长和他的军官, 而是最真正的朋友。 你不这么认为吗? ! ";
				link.l1 = "呵呵。 也许吧。 做你的朋友比做你的敌人好。 既然礼仪显然不是你的强项, 我想我只能习惯了。 ";
			}
			else
			{
				dialog.text = "哦, 得了吧, 你这个无聊的人! 在我看来, 你和我不再只是船长和他的军官, 而是最真正的朋友。 你不这么认为吗? ! ";
				link.l1 = "呵呵。 也许吧。 做你的朋友比做你的敌人好。 既然礼仪显然不是你的强项, 我想我只能习惯了。 ";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "我有个... 礼物给你, 船长。 ";
			}
			else
			{
				dialog.text = "我有个... 礼物给你, 船长。 ";
			}
			link.l1 = "哇, 看看那个! 一个黑点? 你也想让我被废黜吗, 汤米? 你想自己当船长? 哈哈哈哈! 我以为你说过我们是伙伴。 ";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "这是个黑色印记, 你这个蠢货。 你知道, 我开始觉得一旦我在这条围巾上绣上骷髅头和骨头, 它就开始给我带来好运。 我无法解释。 拿着它。 还有... 如果你愿意, 你可以随时借用我可靠的剑和盔甲... 剩下的部分, 哈哈! 它会派上用场的! 你会走得很远。 而我想见证这一切。 我不想让你被流弹打死。 ";
			link.l1 = "谢谢, 伙伴! 我会尽力的。 而你 - 看着并欣赏吧, 哈哈哈! ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Reputation Check Passed", "None");
			if (startHeroType == 4)
			{
				dialog.text = "谁会相信这种事... 对不起, 小姐。 " +TimeGreeting()+ "。 我能为你做什么? 你看起来很担心。 ";
			}
			else
			{
				dialog.text = "什么? 谁在这么晚的时候来? 你看起来相当担心, 先生。 我能为你做什么? ";
			}
			link.l1 = "很抱歉打扰你休息, 卡洛船长。 我叫" +GetFullName(pchar)+ ", 我代表你的一位老战友而来。 ";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "哪位战友? 我有很多, 无论是在旧世界还是新世界。 ";
			link.l1 = "起初, 我只打算在你的一个箱子里留下点东西。 或者也许放在桌子上, 这样你能早点注意到。 这关乎你过去的一个人。 给, 看看并自己读吧。 ";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "一个黑点? 我不记得我的战友中有海盗。 或者是有些小伙子落入了那种生活? 黑色丝绸? 真的... 哦, 托马斯。 我很惊讶像你这样的人会和那个无赖有来往。 ";
			link.l1 = "对不起, 但轮不到你称他为无赖。 你逃离战场并诽谤汤姆。 也许你后来悔改了, 在群岛这里成为了一名模范军官, 但这无法改变过去。 ";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "他这么告诉你的? 不奇怪 - 他总是知道如何找到合适的人来编造他的故事。 托马斯能言善辩。 你不了解他或真实的故事, 也不了解你卷入了什么。 我可以告诉你 - 既然反正我现在也睡不着。 ";
			link.l1 = "倾听总是没错的。 请继续, 卡洛船长。 ";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "所以, 托马斯声称我逃跑了, 然后诽谤他? 好吧, 你应该知道事实恰恰相反! 当国王的骑兵逼近时, 汤姆说他去搬援军。 所以我们没有撤退 - 我们在等待。 我们整个连队都被杀了! 如果我们没有等待他承诺的援军, 我们本可以撤退并活下来! 最后, 只有我。 弗兰基和该死的托马斯活了下来。 ";
			link.l1 = "所以你的意思是... ";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "我是说我们那些小伙子的血同样流在汤姆和保皇党的手上。 他很幸运被判服苦役而不是绞刑! 现在他竟然有胆量怀恨在心并挑战我决斗! 他不配! ";
			link.l1 = "所以你不去? 你意识到这意味着什么。 荣誉法则对每个人都是适用的。 ";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "我当然知道。 这就是为什么我会去。 我们需要完成我们的共和法庭因为汤姆过去的军事荣誉而无法完成的事情。 而你... 你看起来是个正派的人。 我建议你更明智地选择你的熟人。 不要和汤姆之流有来往。 ";
			link.l1 = "但托马斯现在是我的下属, 我船上的一名军官。 "+GetSexPhrase("如果他在与你的交锋中幸存下来, 我会盯着他, 不让他再自取其辱。 ","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "如果处在我的位置, 你会怎么做, 卡洛船长? ";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "呃, 如果汤姆能让你相信他的故事, 他会毫不费力地再次做到。 托马斯有三寸不烂之舌。 ";
			link.l1 = ""+GetSexPhrase("但根据荣誉法则, 我不能背叛他。 我","我")+"对我的人负责.. 如果他幸存下来, 我会更加小心和批判地对待他。 ";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "这是个艰难的决定。 但我不会试图改变你的想法。 好吧, 再见, "+GetSexPhrase("先生","小姐")+" - 我仍然需要准备迎接汤姆。 ";
			link.l1 = "再见, 卡洛船长。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "让正义得以伸张! 帮助我打倒托马斯, "+pchar.lastname+"。 他是个罕见的无赖和懦夫, 但却是个神射手 - 这不会容易。 但我们一起... ";
			link.l1 = "嗯, 帮助你击败托马斯? 这样的决斗有多少荣誉可言? 你们可以自己解决, 我会置身事外。 ";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "了解他的为人, 我怀疑我能否得到一场公平的决斗。 保持中立, 你只是在纵容不公。 对吗? ";
			link.l1 = "看来你比我更了解汤姆, 以及他的真实为人。 你说得对 - 他已经在波特兰峡设下埋伏, 并且指望我的帮助 - 就像你现在一样。 ";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "那这就不是决斗, 而是斗殴。 但我不是建议我们自己杀了托马斯。 我们要逮捕他! 我会带士兵来, 我们要完成在旧世界未能完成的事。 如果他们再次试图赦免他, 我会写信给上校, 甚至带他来这里受审。 如果托马斯不放下武器, 那是他自己的错。 ";
			link.l1 = "这听起来好多了。 ";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "很高兴听到你这么说, "+pchar.lastname+"! 我知道做出这样的决定对你来说可能并不容易, 但我向你保证, 你做出了正确的选择。 为了确保这一点, 我要在其他方面帮助你。 ";
			link.l1 = "是什么, 卡洛船长? ";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "给, 拿着这个。 不是礼物, 而是借用 - 正如我所说, 托马斯是个非常优秀的战士, 最好用一把合适的武器面对他, 而不是一把生锈的破铁。 这把漂亮的剑是多伊利上校亲自给我的, 但对于真正的战斗, 我总是会选择阔剑。 ";
			link.l1 = "确实, 这是一把华丽的细剑。 谢谢你。 ";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "不用谢我 - 我是借给你, 不是送给你, 记住? 现在前往海湾, 和我们亲爱的汤姆扮演好你的角色, 而我去召集援军。 在那里见。 ";
			link.l1 = "在那里见, 卡洛船长。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "你是谁, 小姐? 你一定是找错地址了。 我, 呃, 没有订购任何过夜服务。 ";
				link.l1 = "海伦.麦克阿瑟。 请控制你的欲望, 卡洛先生。 我是个体面的女孩。 我们的气候让我即使在晚上也感到热。 你对一个陌生女孩说那种话不感到羞耻吗? 我听说你是个模范军官。 ";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "你是谁, 你想要什么? 我不喜欢你的冷笑, 先生。 ";
				link.l1 = "" +GetFullName(pchar)+ "。 而你不太好客, 卡洛先生。 ";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "你在这个时候用不同的方式迎接陌生人吗? ";
			link.l1 = "我听说你在其他时间不在家。 ";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "当然不在 - 我有公务。 职责和诚实的劳动, 从你的外表来看, 这些词似乎不为你所知。 ";
			link.l1 = "如此自信! 但话又说回来, 否则你也不会让多伊利上校和其他人相信你的诚实。 我不需要你任何东西, 盖比, 但你的一个老熟人需要。 给你。 ";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "相信? 盖比? 我说! 一个黑点? 所以你是海盗? 等一下... 黑色丝绸... 这可能是... 哦, 我明白了。 托马斯, 你这个该死的混蛋, 还在为我和弗兰克举报你而生气, 哈哈哈哈! ";
			link.l1 = "我说! 汤姆是我船上的一名军官, 应该受到尊重。 他是群岛上最好的射手之一。 ";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "我没说他射得不好。 但我看你不太了解托马斯。 他才是背叛我们所有人的人。 但我看和你争论没有意义 - 你们显然是天造地设的一对。 ";
			link.l1 = "我不在乎。 把你的故事留给多伊利和所有那些天真的傻瓜吧。 如果你像他们说的那样勇敢和正直, 你会接受挑战并现在就来。 那么, 你接受吗? ";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "我接受, 我接受。 现在滚出我的房子, 否则我叫卫兵了。 ";
			link.l1 = "这将是我的荣幸, 盖比。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "你为什么这么紧张? 你害怕了, 还是怎么了? ";
				link.l1 = "看到一个拿着滑膛枪的人朝自己跑来, 任何人都会紧张 - 我一开始没认出是你。 你在这里做什么, 汤米? ";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "怎么样了? 嘿, 嘿, 你为什么那样看着我? 你吓了我一跳, 呵呵。 ";
				link.l1 = "谁吓谁呢! 谁像那样跑出来? ! 我们约好在海湾见客人的! ";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "呵呵, 也许吧。 我等腻了 - 等我们亲爱的客人和你。 我觉得这个地方更适合设伏。 毕竟, 我是个猎人, 不是决斗者。 ";
			link.l1 = "我明白了。 ";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "是的。 那么, 你把我的礼物留在盖比的房子了吗? 你花了太长时间。 如果我能进城, 我会快得多。 你为什么眼神闪烁, 船长? 怎么了? ";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(值得信赖) 我很紧张。 盖比是个懦夫, 但他不傻。 如果来的不是他, 而是一整个排的士兵怎么办? 或者他们接近海湾并先击沉我们的船怎么办? ";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l2 = "盖比看到我了。 我不得不跑。 ";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Perk Check Failed", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "呵呵, 我明白了 - 我自己也不完全确定这会奏效。 这对你来说是第一次发生这么大的事, 嗯? 没关系, 这很正常。 我都计划好了。 如果士兵不带盖比来, 我们就离开。 如果他们带盖比来, 我就把子弹射进他的眼睛, 同样, 我们离开。 如果有船来到海湾, 我们就跑到马龙镇 - 他们不敢去那里, 然后我们再决定下一步怎么做。 ";
			link.l1 = "我看你真的把一切都考虑到了, 汤米。 ";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "我当然考虑到了。 现在让我们等待我们的客人... ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "哈哈, 你和我一样是个小偷, 就像我是个保皇党一样。 但你为什么不敢直视我的眼睛... 船长? 你和盖比谈过了, 是吗? ";
			link.l1 = "不, 你在说什么? 我为什么要和他谈? ";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "因为你们都是夸夸其谈的人。 你们只会说。 那么, 我们亲爱的盖比告诉你什么了? ";
			link.l1 = "这重要吗, 汤米? ";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "坦率地说, 不重要。 如果你不背后捅我一刀, 就不重要。 但看起来你已经这么做了。 他说服你站在他那边了, 是吗? ";
			link.l1 = "不。 不完全是。 放下枪, 汤米。 我向你保证, 没有什么不可挽回的事必须发生。 你可能会去采石场工作, 也许。 我会请求盖比手下留情。 如果有必要, 我甚至会请求多伊利上校。 ";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "你真是个好人。 表现出怜悯, 让我在采石场咳了几年肺之后? 我不会再回到监狱船上去。 再也不会。 而你... 我早该知道你只是另一只老鼠。 你看人的样子就有问题。 我会先处理你, 这样稍后对付盖比就更容易了。 ";
			link.l1 = "你让我们别无选择! ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "嗯, 我看到你已经动手了, "+GetSexPhrase("先生","小姐")+"。 我正在召集一个小队, 想着人数上的优势会让汤姆三思而后行, 放下武器。 ";
			link.l1 = "而你却磨磨蹭蹭, 卡洛船长。 ";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "我告诉过你, 我在召集人手。 我们驻军中最优秀的。 毕竟汤姆是个老兵。 但我在跟谁讲这些呢? 干得好, "+GetSexPhrase("先生","小姐")+" "+pchar.lastname+"。 "+GetSexPhrase("我为你骄傲, 年轻人","我必须承认, 你兼具美貌。 智慧和技巧, 年轻女士")+"。 正如我们第一次见面时我所说, 你做出了正确的选择。 现在正义得到了伸张。 ";
			link.l1 = "这对你来说太顺利了。 感觉自豪吗? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "嗯, 我不是老兵, 但我会战斗, 正如你可能刚刚注意到的。 但谢谢你, 先生。 正义对我来说不是一句空话。 ";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "这是值得称赞的, "+GetSexPhrase("年轻人","年轻小姐")+"。 然而, 要完成这美好的一天, 还有一件事要做。 ";
			link.l1 = "嗯, 那是什么? 毕竟汤姆已经被击败了。 ";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "你有属于我的东西。 请把我漂亮的意大利细剑还给我。 毕竟它不只是牙签, 而是纪念品 - 多伊利上校亲自送的礼物。 ";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "呃... 是这样的, 卡洛船长... 那把细剑不见了。 我弄丢了。 对不起。 ";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "啊, 当然。 请。 我没打算偷它。 不过说实话 - 我想留下它。 但给你, 卡洛船长。 ";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "我有个更好的提议给你, 船长。 ";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "但你刚才称它为牙签。 此外, 你说过你甚至不喜欢细剑。 而我, 另一方面, 应该得到奖励。 ";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "任何人都会想留下这把美丽的剑! 谢谢你把她还给我。 在你这种情况下, 很多人会固执己见。 ";
			link.l1 = "它是你的。 我想我们在这里结束了? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "我不感兴趣。 把细剑还给我, 我们就愉快地分手, "+GetSexPhrase("先生","小姐")+" "+pchar.lastname+"。 ";
			link.l1 = "我猜这把细剑对你来说很珍贵, 因为你喜欢有历史的武器, 对吗? 我有一把和它一样的, 而这把是你想携带的, 而不是放在抽屉里。 ";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "是这样吗? 好吧, 我不能保证我们会达成协议, 但我在听。 我确实对有历史的武器感兴趣。 但这把细剑是上校送的礼物。 这就是为什么它对我如此珍贵。 ";
			link.l1 = "你提到你喜欢阔剑。 给。 这属于我们亲爱的汤米。 想象一下这把武器多年来经历了什么。 以及它将与你一起继续经历什么。 ";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "你很有说服力, 年轻人! 挥舞着托马斯的剑... 多么讽刺。 啊, 好吧。 拿去吧。 记住, 我不是轻易放弃它的。 ";
			link.l1 = "很高兴我们能达成协议。 我想这是再见了, 卡洛船长? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "什么? ! 你怎么能... 你怎么能把一整把该死的细剑弄丢了? ! 你是个白痴! ";
			link.l1 = "冷静点! 只是一把细剑。 反正你也不会用。 汤姆死了 - 这不是现在唯一重要的事吗? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "只是一把细剑? ! 它是我的宝贝! 多伊利上校亲自送的礼物! 我不在乎我是否用它! ";
			link.l1 = "那你就不该把它给我, 不是吗? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "现在你该闭嘴了, "+GetSexPhrase("先生","小姐")+" "+pchar.lastname+"。 我们本可以和平分手。 但现在... 现在我想给你一个教训, "+GetSexPhrase("年轻人","年轻小姐")+"。 ";
			link.l1 = "墓地里满是像你这样的老师。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "当然, 你应该得到奖励。 但你不能因为帮了他一手就拿走一位军官的个人武器, 不是吗? ";
			link.l1 = "我同意, 但你反正也不用它。 它只会挂在你房间的钉子上。 而对我来说, 它会得到有价值的使用。 多伊利上校不会检查你是否把它放错地方了, 对吧? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "这不是商量的事, 年轻人。 我一开始就告诉你, 这不是礼物。 把细剑给我。 现在。 ";
			link.l1 = ""+GetSexPhrase("我不是你的玩具士兵","我不是你的港口妓女")+", 听你命令。 我和你一样是船长。 无论你喜不喜欢,细剑我留下了。 ";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "看来托马斯对你影响很大。 那么, 如果你这么想要它, 就为此而死吧。 ";
			link.l1 = "我正是这么想的! ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "给, 拿着这个。 我根本不需要它。 这将是你今天的纪念品。 试着以后少一些轻信。 不要让任何像托马斯这样的无赖让你卷入他们的肮脏勾当中。 ";
			link.l1 = "呵呵, 你在给我一个黑点吗, 卡洛船长? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "嗯, 我们都不是海盗, 对吧, "+pchar.name+"? 让它作为一个提醒。 保重, 群岛需要像你这样的人。 "+GetSexPhrase("也许我会建议你加入海军, 并给多伊利上校写封推荐信... ","")+"";
			link.l1 = "很遗憾我不能接受你的提议, 船长。 ";
			if (startHeroType == 3)
			{
				link.l1 = "嗯。 我会好好考虑的。 非常认真地考虑。 ";
			}
			if (startHeroType == 4)
			{
				link.l1 = "再见, 先生。 ";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "随你便。 好吧, 再见, "+GetSexPhrase("先生","小姐")+" "+pchar.lastname+"。 你值得继承铁甲军剩下的一切。 再见。 ";
			link.l1 = "再见, 先生。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "我不喜欢你的语气, "+GetSexPhrase("先生","小姐")+"。 你的重点是什么? ";
			link.l1 = "你一直在故意拖延, 召集你的‘最佳人手’。 为了什么? 逮捕一个人? 你本应该抓住几个在城里巡逻的士兵, 立即来帮助我! ";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "带炮灰来? ! 汤姆不仅仅是像他们一样的城市卫兵。 他有完全不同的训练和经验 - 他是个该死的铁甲军, 就像我一样! 你怎么会不明白? ";
			link.l1 = "哦, 正相反, 我明白。 这就是为什么你和我在这里 - 与汤姆交锋, 让小伙子们活捉他。 此外, 你也是铁甲军。 甚至是同一个连队。 你就这么害怕亲自和他战斗? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "你怎么敢指责我懦弱, 年轻的"+GetSexPhrase("男人","小姐")+"! 问问任何人, 他们会详细告诉你我为这个城市做了哪些壮举。 ";
			link.l1 = "我还没说完。 我开始怀疑这些‘壮举’是否是你亲手完成的。 你想让汤姆和我自相残杀, 这样你就可以独占所有荣誉。 你以前这么做过, 不是吗? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "我受够了你的指责, "+GetSexPhrase("先生","小姐")+" "+pchar.lastname+"。 你想要冲突? 你会得到的。 就是现在。 ";
			link.l1 = "真相伤人, 不是吗, 盖比? ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "盖比! 已经这么久了, 这么多萧瑟的寒冬! 看看你 - 仍然带着同样 smug 的表情, 该死的你! ";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "托马斯! 我应该高兴, 因为今天我终于要亲手完成我们的司法系统多年来未能完成的事。 而且由于我心情不错, 我允许你放下武器跟我们走。 你甚至可能被送回服苦役。 在那种情况下, 我会亲自带你去那里。 ";
			link.l1 = "呵呵, 让我试试! 你以为你旁边的几个家伙能阻止我!! ";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "谁说只有他们和我在一起? 我说的是现在站在你旁边的那个人。 ";
			link.l1 = "什么? ";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "托马斯, 托马斯, 托马斯... 你一如既往地在这个世界上孤身一人。 我几乎为你感到难过! ";
			link.l1 = "该死的老鼠! 混蛋! ";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "那是什么意思? ! 他那是什么意思? ! ";
			link.l1 = "汤米, 听着... ";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "我正在这么做! 告诉我他在撒谎! ";
			link.l1 = "不幸的是, 他是对的。 放下武器。 今天没有人必须死。 我会亲自为你说好话, 这样你就不会被绞死。 有一天你甚至可以重返诚实的生活。 ";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "这轮不到你来决定! 当然也不是你! 有你这样的指挥官, 谁还需要敌人! 又是一个该死的老鼠。 ";
			link.l1 = "来吧, 汤米。 像你这样的人没有干净的退路。 ";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = "在你的船员中, 在你的船上有一个位置是个开始, 如果你愿意为你的人挺身而出! 但这已经不重要了。 该死的你们所有人! 我会把你这胆小的内脏挖出来, 你这只小老鼠。 还有你, 盖比, 我会试着带你一起走... ";
			link.l1 = "等等, 汤米, 不! ";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "恭喜你, "+GetSexPhrase("年轻人","年轻小姐")+"! 我很惊讶你能让托马斯觉得一切都在按他的计划进行 - 他对背叛有敏锐的嗅觉。 ";
			link.l1 = "啊, 谢谢你, 当然, 卡洛船长。 ";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "有什么困扰你吗, "+GetSexPhrase("先生","小姐")+" "+pchar.lastname+"? ";
			link.l1 = "汤姆... 他不仅仅是生气我站在你这边。 他的声音里有真正的绝望和不解, 好像... ";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "... 好像他是这里的受害者。 这是意料之中的。 记住, 查尔斯, 怪物也会感到疼痛。 但它不会停止成为怪物。 许多罪犯往往真诚地相信自己的正确性和无辜。 ";
			link.l1 = "我会努力记住这一点。 我想我们在这里结束了, 不是吗, 船长? ";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "总的来说, 是的, 但要完成这美好的一天, 还有一件事要做。 ";
			link.l1 = "哦? 是什么? ";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "你花了太长时间。 所以我想我该侦察一下。 不管怎样, 我认为在这里设伏比在海滩上扮演花哨的决斗者更好。 我希望你能找到盖比的房子并把一切都放在显眼的地方? ";
			link.l1 = "我当然做到了, 你把我当成什么了, 白痴? 我实际上是你的船长, 汤米。 如果你为一个白痴服务, 那你会是什么? ";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "哈哈哈哈, 你不会相信在服役期间我不得不处理多少次这样的废话! 但在我们的情况下, 幸运的是, 情况并非如此。 好吧, 那么。 我们在等客人。 准备好了吗? ";
			link.l1 = "嗯, 除非整个舰队或皇家港的驻军出现在这里, 否则我准备好了。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "托马斯? 真的是你... ";
			link.l1 = "当然是我, 不然你以为是谁, 盖比? 呵呵, 你脸色苍白, 好像见了鬼。 你也比在旧英格兰时胖了。 ";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "现在我终于确信真的是你。 一如既往的粗鲁。 但没关系, 我很快就会永远让你这肮脏的嘴闭嘴, 你这个混蛋。 ";
			link.l1 = "哈哈, 这才像话! 你知道, 你实际上让我失望了, 盖比。 再一次! 显然, 即使只对付我一个人, 你也需要带更多的人来。 而且我们有两个人! 或者这就是他们能给你派的全部, 你这个懦夫? ";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "够了! 我认为我们没有必要再谈了。 ";
			link.l1 = "在这一点上我同意你! " +pchar.name+ "! 战斗吧, 船长! ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "呵呵, 你来了! 安息吧, 你这个混蛋。 ";
			link.l1 = "好吧, 你满意了吗, 汤米? 你知道, 很多人在复仇之后只会变得更糟。 ";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "哈, 你从哪里读到的? 我从不理解这种娘娘腔。 呸! 我满意吗? 我高兴得快要尿裤子了! 那些混蛋是我最大不幸的根源! ";
			link.l1 = "我为你高兴。 你还有其他人需要复仇吗? 我还能期待你更多的纸子弹笑话吗? ";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "冷静点, 盖比是最后一个。 关于笑话 - 别担心, 不会再有了, 至少不会针对你。 ";
			link.l1 = "那我们回船上吧? ";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "无论我是否还有人需要复仇, 我们反正都会回到她那里。 不过... 等一下... ";
			link.l1 = "哦, 所以还没结束... ";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "结束了, 结束了。 有件事我想告诉你。 这是我很少对人说的话。 而且我不会再说一遍。 如果你嘲笑我, 我会非常生你的气。 ";
			link.l1 = "我保证不笑。 不管怎样, 我觉得你的笑话比有趣更紧张。 ";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "很好。 那么。 我非常感激你决定帮助我, 而不是像杰克那样做。 你是个真正的朋友, 船长。 谢谢你。 还有... 如果你愿意, 你可以借用我可靠的剑, 还有我的盔甲... 剩下的部分, 哈哈! 它会派上用场的! 你会走得很远。 而我想见证这一切。 我不想让你被流弹打死。 ";
			link.l1 = "好吧, 谢谢你这么说。 不是每天都能从你的军官那里听到这样的话。 来吧, 伙伴。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> --------------------------------- —офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "啊啊-是, 船长? ";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "那么, 伦巴, 今晚我们要在谁的骨头上跳舞? ";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "是的, 艾莉? ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "我洗耳恭听, 船长。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "汤米, 我想问你一件非常严肃的事。 有一个... 红皮肤人的石头偶像。 我需要帮助。 我只能向我最亲密的朋友求助, 比如你。 新手或我还不太信任的人不行。 ";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "汤米, 别再数海鸥了。 你把所有货物都清点了吗? 给我一份完整的报告和预测。 ";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship。 Автозакупка товара
				Link.l12 = "汤米, 从今天开始, 我需要你在港口购买特定货物。 ";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "汤米, 你能报告船上的一切吗? ";
					Link.l12 = "汤米, 我很累了。 你能在每个港口储备一些货物吗? ";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "汤米, 准备一份关于船的状况和上面所有东西的报告。 ";
					Link.l12 = "我们靠港时你能储备一些货物吗? ";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "数一数我船上的所有东西, 并报告其总体状况。 ";
					Link.l12 = "我需要你在每个港口停靠时购买这些货物。 ";
				}
			}
			//////
			Link.l1 = "仔细听我的命令! ";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "肯定有人。 但现在, 听我的命令。 ";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "听我的命令... 汤米。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "很好, 因为我有新的命令给你, 汤米。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "听我的命令, 汤姆。 ";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "没什么, 汤米。 稍息。 ";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "我们走着瞧, 汤米。 ";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "不, 汤姆, 没什么。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "不, 没什么。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "没什么, 一切都好。 ";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "我甚至还没开始盘点库存。 你应该庆幸我至少在计算盈亏, 更别说还要和那些贪婪的商人讨价还价了。 盘点不是我的事, 在军队里就没做过, 现在也不会开始。 ";
			Link.l1 = "这不是军队, 汤米。 但好吧, 我懂了, 不勉强你。 ";
			if (startHeroType == 4)
			{
				dialog.Text = "我不是文书, 艾莉。 我以前认识个叫丹尼尔.克里姆森的家伙, 总说自己是文书, 但几乎没上过战场。 不过那家伙打起架来像头野兽。 但我不是他, 也不会撒谎。 盘点真不是我的菜。 看在你的份上我已经在做账目了, 别逼我。 ";
				Link.l1 = "好吧, 汤米, 不逼你。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "听着, 我不是文书。 就算在军队里, 也从没人要求我们普通士兵做这个。 别坏了规矩。 ";
				Link.l1 = "行, 不坏规矩。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "我唯一会数的就是打死了多少敌人, 哈哈哈。 有时候还会数错。 我就是个普通士兵, 你懂的。 谁懂船啊 —我这辈子大部分时间都是旱鸭子。 ";
				Link.l1 = "看来我得自己来了。 ";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "你把我当什么了, 街头小军需官? 我们老家的人对那些软蛋懦夫只有鄙视。 我也许不是贵族, 但好歹还有点尊严。 ";
			link.l1 = "行行行, 你不愿意就算了。 ";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "听着, 我就是个单纯诚实的士兵, 不是军需官, 姑娘。 我不懂也不想学。 这就像让你按时拆装滑膛枪一样离谱。 ";
				Link.l1 = "我能把船上的索具零件背得滚瓜烂熟。 但随你吧, 汤姆。 这事到此为止。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "我做不来。 也许你忘了或者根本不知道, 我解释一下: 这对你可能是常规任务, 但在我们军队里, 后勤补给人员地位不高。 别把我归到那类人里。 ";
				Link.l1 = "哈哈, 好, 好。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "听着, 我当然尊重你, 但我不会勉强自己做不会做也讨厌的事。 我当年刚学会数数, 你就想让我当正经军需官? 顺便说, 我们可不喜欢他们 —总在弹药。 水和食物上克扣。 ";
				Link.l1 = "嗯, 好吧, 忘了这事。 ";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("哦, 下命令啊? 你喜欢操练那套军队作风, 是吧? 不如直接说要干嘛。 ","你跟个中士似的。 这不适合你 —你这么漂亮。 在军队里一天都活不下去。 但我听着。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "看来你是真喜欢制服。 操练那一套。 不过好吧, 说吧。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "哪条命令? ";
			}
			
            Link.l1 = ""+GetSexPhrase("别乱走别乱动 —就看着, 懂吗? 我还不了解你。 ","待在原地, 明白吗? ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "就站在这, 别乱走, 别碰任何东西。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "待在这, 别让任何人通过。 ";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("跟着我, 别分心 —不管是偶遇的女人还是突然冒出来的老战友。 ","跟紧点, 好吗? 我需要有人掩护。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "跟着我。 看你魂不守舍的。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "跟着我, 不然你又不知道为啥停下了。 ";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "这次你得换种弹药。 ";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "接下来的战斗你得换弹药。 ";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "下一场战斗你用不同的弹药。 ";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "给你的滑膛枪换弹药类型。 ";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "战斗时优先使用的武器。 ";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "你和敌人保持一定距离。 ";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "汤米, 你和敌人保持一定距离。 ";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "汤米, 你自己和敌人保持距离。 ";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("哪种弹药? 希望你每颗都精心打磨过, 谁知道会打到哪, 呵呵。 ","我啥都能为你射。 不管是啥, 反正别是空包弹, 呵呵。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "感觉有好戏! 说吧, 哪种? ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "又要打架了... 说吧, 哪种? ";
			}
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

		case "SetMusketBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "战斗开始时使用: ";
			Link.l1 = "刀剑";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "滑膛枪";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("就算你在那边被打趴了, 呵呵? 知道了, 我就看着。 ","想让我当保镖? 你要是被打了怎么办? ")+"";
            Link.l1 = ""+GetSexPhrase("嘿, 注意点! 真到那步再说。 ","你不会就干看着吧? 要是你说的船长那么厉害, 你总得做点什么。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "就算被爆头? 行行行, 别这么看我, 知道了。 ";
				Link.l1 = "最好是。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "别怕, 没人能过去。 ";
				Link.l1 = "当然别放任何人过去。 不过好。 ";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("真有意思。 但我懂你的意思。 ","哦, 别担心, 我一直盯着你的背呢, 呵呵。 ")+"";
            Link.l1 = ""+GetSexPhrase("好。 ","天啊, 你真烦, 汤姆。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "嗯, 我在想很重要的事。 然后发现自己忘了 —毕竟失忆了, 想也没用。 好了, 走吧。 ";
				Link.l1 = "挺会说啊。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "是你之前命令我站在这的。 来了, 来了。 ";
				Link.l1 = "嗯, 行, 行。 ";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("什么距离? 记住二十码外我可瞄不准。 除非你不指望我打中什么, 呵呵。 ","跟你混久了, 谁还想靠近那些臭男人。 说吧, 多远? 但记住, 超过二十码谁也瞄不准。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "好, 多远? 但提醒你, 战斗中超过二十米我没法精准慢速射击。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "好。 什么? 记住超过... 得了, 你我都清楚。 ";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("别冷嘲热讽了。 ","想跟我学幽默还早着呢, 姑娘。 不过有进步! ")+"";
				link.l1 = ""+GetSexPhrase("奇怪, 别人都说我很幽默。 ","真有意思, 汤米。 ")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "这笑话不算最烂。 也许哪天你能不这么刻薄, 呵呵。 ";
					Link.l1 = "好吧。 ";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "哈哈哈, 好笑话。 ";
					Link.l1 = "其实我只是... 好吧。 ";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "那我就原地不动坚守阵地。 要是你离太远被打, 那是你自己倒霉, 呵呵。 ";
				link.l1 = "别讽刺了, 坚守阵地正是我要你做的。 ";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "呵, 你直接说坚守阵地就行, 别扯什么距离数字。 ";
					Link.l1 = "总之你明白就好。 ";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "知道了, 我在这坚守。 你把敌人引过来让我射。 ";
					Link.l1 = "没问题。 ";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "听着, 我知道你希望我每次都像在灯塔那次一样精准, 但不可能。 那次位置好, 冷静稳定。 战斗中可复制不了。 ";
				link.l1 = "嗯。 那保持二十码距离。 ";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "我知道你想, 大家都想, 但像灯塔那次不可能了。 我需要好位置, 还得没人打扰, 不然会紧张。 ";
					Link.l1 = "嗯, 好吧。 ";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "我技术是进步了, 但不可能的事还是不可能 —战斗中绝不可能复制灯塔那次的射击, 就算有轮锁步枪也不行。 ";
					Link.l1 = "没什么不可能, 汤米。 但好吧, 不勉强。 ";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("很好。 我会精准保持那个距离, 但要是在酒馆或洞穴里战斗, 我会到外面保持距离, 呵呵。 ", "尽量吧。 但甲板和狭窄空间可能由不得我。 ");
			link.l1 = ""+GetSexPhrase("不好笑, 汤米。 随机应变, 但别开玩笑或搞你那些蠢恶作剧。 ","我知道, 托马斯, 我不傻。 ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "我会记住的。 ";
				Link.l1 = "好, 我指望你了。 ";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "是, 船长。 ";
				Link.l1 = "稍息, 汤米。 ";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//< —задать дистанцию стрельбы
	//< —--------------------------------- —офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "帮什么, 偷吗? 但为啥? 当然我很荣幸, 但你早该说了。 快说吧。 ";
			link.l1 = "嘴巴放干净点? 算了 —只要你站我这边, 怎么说话我不在乎。 那个偶像, 通过它能... 魔法般地到另一个地方。 别这么看我 —我知道听起来荒谬。 但我经历过, 亲眼见过。 只要喝一种灵药就... 安全。 ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "看来你喝了不少。 不过不像, 你挺清醒。 他们还说我总说胡话... ";
			link.l1 = "你到底跟不跟我去? 据说偶像能把我们带到古玛雅城市, 谁知道那边有什么? 我认为危难时刻能信赖的人里有你, 现在就是危难时刻。 ";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "我觉得这事不靠谱。 要不是你是船长, 我会说你该进疯人院。 接下来你该说上帝存在了。 ";
			link.l1 = "上帝存在, 汤米。 而且在这群岛上我惊讶地发现, 不止我们的上帝存在。 你自己也见过这里的妖魔鬼怪, 也注意到受祝福或诅咒的小玩意的影响。 ";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "老家也有妖魔鬼怪, 但总有正常解释。 抱歉船长, 我不会跟你围着石头偶像跳舞。 开枪打敌人 —没问题。 我可能失忆了, 但脑子没坏, 至少我这么认为。 ";
			link.l1 = "好吧, 不能强迫你。 所以... 随你吧, 汤米。 ";
			link.l1.go = "tieyasal_5";
			link.l2 = "要是你连靠近偶像都不敢, 我怀疑你有没有胆子开枪打他们, 你这胆小鬼。 ";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "好啦好啦, 别撅嘴。 这样吧, 要是你围着偶像跳完舞还能回来, 下次我会考虑。 ";
			link.l1 = "可能没下次了。 回船上吧, 汤姆。 ";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "我不是害怕, 别误会。 但我习惯听直觉, 这些年从没错过。 现在直觉告诉我没好事。 而且... 算了, 说了你会生气。 ";
			link.l1 = "说吧。 ";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "那好吧! 我答应过和你并肩战斗。 但假设这东西真有用呢? 要是被诅咒了呢? 抱歉, 我不会为任何人送命。 ";
			link.l1 = "现在你暴露了, 汤米。 我现在需要最忠诚的人, 而你不是。 我要去了, 你... 爱干嘛干嘛。 ";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "看看, 到底还是生气了。 ";
			link.l1 = "闭嘴。 要是你觉得我们这么恶心, 就别回船上了。 ";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "哇! 说真的? 也许这样最好。 我不想跟连笑话都不懂的扫兴鬼待一起。 那么... 再见了, 大人。 ";
			link.l1 = "再见, 汤米。 滚吧。 ";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 