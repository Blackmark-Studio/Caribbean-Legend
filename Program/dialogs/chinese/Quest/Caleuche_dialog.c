void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "这肯定是个 bug。 你能告诉杰森这是什么时候以及如何发生的吗? ";
			link.l1 = "我会的。 ";
			link.l1.go = "exit";
		break;
		
		// 卡里布萨满图图阿塔帕克
		case "Tuttuat":
			dialog.text = "你为什么来我的小屋, 白人? 图图阿塔帕克不认为你是他的贵客。 ";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "向你致敬, 伟大的萨满图图阿塔帕克。 我来寻求你的帮助和建议。 请接受这把滑膛枪作为我善意的象征。 ";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "向你致敬, 伟大的萨满图图阿塔帕克。 我来寻求你的帮助和建议。 ";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "图图阿塔帕克不帮助白人。 白人是坏人。 他们杀戮和征服印第安人, 让印第安人成为奴隶。 图图阿塔帕克不会给白人建议。 你现在离开。 ";
			link.l1 = "嗯... ";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("你已赠送: "+XI_ConvertString(sTemp)+"");
			dialog.text = "你知道该给图图阿塔帕克什么, 白人。 图图阿塔帕克接受你的礼物。 他会说话。 你想寻求什么建议? ";
			link.l1 = "我听说你来自南方的遥远地方。 我有一个印第安护身符, 一位博学的人告诉我你可能知道如何使用它。 ";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "出示护身符。 ";
			link.l1 = "给你, 伟大的萨满。 ";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(看着护身符)... 你的朋友说的是实话, 白人。 这个护身符属于我的人民, 伟大的印第安人, 他们的名字是查文。 被诅咒的亵渎神灵的白脸杂种玷污了圣地并把它带到了这里。 图图阿塔帕克惩罚了那只猎犬。 ";
			link.l1 = "你剥夺了他的理智, 我猜? ";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "白人用他的知识让图图阿塔帕克惊讶。 是的, 我吞噬了那个卑鄙杂种的理智。 他和他肮脏的手下得到了应有的惩罚。 ";
			link.l1 = "我明白了... 告诉我, 萨满, 这个护身符有什么用? 也许它可以在战斗中保护人或抵御邪恶魔法? ";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "这个护身符对你没用, 白人船长。 你无法使用它的力量。 只有我们部落的伟大萨满知道如何唤醒它。 ";
			link.l1 = "嗯... 原来我长途跋涉是徒劳的。 但是, 也许你可以唤醒这个护身符的力量, 伟大的萨满? 我们当然可以达成协议... ";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "即使我唤醒了护身符, 你也无法长时间持有它的力量。 但我给你一个交易, 白人。 ";
			link.l1 = "什么样的交易? ";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "三个这样的护身符从我们的圣地被拿走。 它们有不同的力量, 但如果把它们放在一起, 它们会非常非常强大。 找到所有三个护身符并带给我, 我会奖励你。 我会给你可以永远拥有的力量。 ";
			link.l1 = "我不太明白... 你说的是什么样的力量? ";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "你会在适当的时候知道一切。 找到并把所有三个护身符带给我。 它们会在加勒比海。 寻找并找到它们。 你很容易分辨它们 --它们看起来很像。 去吧, 白人。 图图阿塔帕克会等待并请求神灵帮助你。 ";
			link.l1 = "... ";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "去吧, 白人。 找到另外两个护身符。 ";
				link.l1 = "我已经找到它们了, 伟大的萨满。 看。 ";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "去吧, 白人。 找到另外两个护身符。 ";
				link.l1 = "... ";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "你又来这里了, 白人? 你看起来像是在丛林里遇到了凶猛的美洲虎。 ";
			link.l1 = "更糟, 伟大的萨满。 当我踏入大海时, 一场巨大的风暴不知从何而来, 我遭到了一艘由亡灵驾驶的船的袭击! 他们的船长完全无敌。 首先他从我这里拿走了护身符, 差点杀了我 --我勉强活了下来。 然后他们差点击沉我的船, 只有少数船员幸存。 ";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "坏消息, 白人。 卡勒幽船又开始杀戮了。 ";
			link.l1 = "卡勒幽船? 那个亡灵船长称他的船为‘飞翔之心’。 所以, 你知道幽灵船却没有警告我? 如果我知道这艘航行的噩梦在寻找护身符, 我永远不会... ";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "图图阿塔帕克看到白人船长很沮丧。 白人船长必须冷静下来。 ";
			link.l1 = "冷静下来? ! 你疯了吗? 我怎么可能在这样的东西面前生存下来! ";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "是的。 冷静下来, 不要喊叫。 告诉我 --你仍然想从我这里获得永远与你同在的强大力量吗? ";
			link.l1 = "嗯, 当然想。 但我已经没有护身符了。 ";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "我教你如何从卡勒幽船的船长那里夺回护身符。 这并不容易。 但如果你做到了, 你将把他的船作为奖品, 找到宝贵的宝藏, 与你的人民一起赢得荣耀, 并从我这里获得奖励。 ";
			link.l1 = "该死! 我很乐意摧毁那个萎缩的怪物! 但我怎么能打败他, 如果他既不受剑伤也不受枪伤? ! ";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "你准备好听我说了吗, 白人船长? ";
			link.l1 = "是的, 我准备好了, 伟大的萨满。 ";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "当我父亲还是个年轻战士的时候, 白人乘着‘飞翔之心’号船来到我的土地。 他们去了山区。 传说中, 我们祖先的一个圣地隐藏在那里。 美洲虎战士的圣地。 白人找到了圣地和黄金, 玷污了古老的神圣之物。 他们拿走了查文的伟大宝藏 --死亡之神和美洲虎人守护神尤姆.西米尔的玉头骨\n白人来到他们的船上。 他们决定返回取更多的黄金, 但当他们的人踏上陆地时, 他在可怕的痛苦中死去。 尤姆.西米尔诅咒了船长和他的船员。 他们变得不朽, 但再也不能踏上陆地。 他们航行了很多很多个冬天, 按你们的历法算有半个世纪。 卡勒幽船就是这样出现的。 \n他们的身体枯萎, 肉腐烂, 但他们仍然活着。 如果你砍下一只手臂或一条腿, 它会重新长出来。 如果你把他们切成两半, 他们会再次合为一体。 如果他们的船沉没, 他们会在水下修好, 然后它又会航行。 ";
			link.l1 = "太好了... ";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = "卡勒幽船恐吓水手。 它无缘无故地攻击, 带来必然的厄运。 它在加勒比海不是常客。 它喜欢在我祖国的海岸航行。 我想, 它想解除诅咒。 但它永远不会解除。 ";
			link.l1 = "为什么? 需要做什么才能解除诅咒? ";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "玉头骨。 它必须回到尤姆.西米尔的圣地, 美洲虎战士的神庙。 有几个神庙。 我部落的长老说在加勒比海的一个小岛上有一个。 这就是卡勒幽船航行到那里的原因。 一旦头骨在神庙里, 尤姆.西米尔的咒语就会打破, 他们会变得凡人, 不再愈合伤口。 ";
			link.l1 = "哈! 更有可能的是, 他们不打算归还头骨! 如果他们不朽且无敌, 为什么要呢? 此外, 如果他们不被允许踏上陆地, 他们根本无法带回来, 对吗? ";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "他们没有头骨。 船长从美洲虎人圣地返回时, 把它扔在了我祖先的土地上。 玉不是黄金, 白人不需要它, 他无法拿走头骨眼睛里美丽的绿色宝石。 他把它扔掉了。 一个水手捡了起来, 他没有受到诅咒\n当水手看到卡勒幽船的船员变成什么样时, 他逃跑了。 他来到我们的村庄。 我父亲看到了那个水手和尤姆.西米尔的头骨。 然后白人带着头骨沿着海岸向北走。 ";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "一个眼窝里有绿色石头的玉头骨? 你能想象吗? 我亲手拿过它! 我自己把它给了所罗门。 但他和他的女儿去了欧洲, 似乎他把头骨带走了。 ";
				}
				else
				{
					link.l1 = "一个眼窝里有绿色宝石的玉头骨? 我的天... 我... 我亲手拿过它! 我把它卖给了一个葡萄牙人... 梅里曼之类的... 是的, 他说 --尤姆.西米尔的头骨! 他非常想要它! 他为此支付了五十万比索! ";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "一个眼窝里有绿色宝石的玉头骨? 所以这就是我需要找的? 但那个水手可能五十年前就死在丛林里了, 头骨可能永远丢失了! ";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "我知道头骨在加勒比海。 卡勒幽船来这里不是偶然的。 在过去的六个月里, 它经常在岛上被看到。 以前很多年它都不在那里。 卡勒幽船的船长能感觉到美洲虎人的神器。 他就是这样找到你和你的船的。 ";
			link.l1 = "那么, 我是否正确理解我必须再次找到这个头骨? 然后我该怎么处理它? ";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "头骨一定在这里, 在加勒比海。 卡勒幽船来这里不是偶然的。 在过去的六个月里, 它经常在岛上被看到。 以前很多年它都不在那里。 卡勒幽船的船长能感觉到美洲虎人的神器。 他就是这样找到你和你的船的。 ";
			link.l1 = "那么, 我是否正确理解我必须再次找到这个头骨? 然后我该怎么处理它? ";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "首先, 你必须找到我们说过的两个护身符。 没有它们, 你什么也做不了。 护身符会给你力量来对抗美洲虎人和任何你遇到的敌人。 ";
			link.l1 = "对抗美洲虎人? 你在说什么? ";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "你必须把玉头骨带到的神庙, 位于加勒比海的一个荒岛上。 它由美洲虎人守卫。 他们都死了但现在还活着。 没有护身符你无法通过他们。 美洲虎人生前是凶猛的战士, 死后几乎无敌。 他们的力量来自尤姆.西米尔本人。 ";
			link.l1 = "亡灵? 又是亡灵? 我真幸运... ";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "为什么这么惊讶, 白人船长? 尤姆.西米尔是死亡之神, 玉头骨赋予统治生死的力量。 加勒比海。 它由美洲虎人守卫。 没有护身符你无法通过他们。 有了护身符, 你可以进入神庙并生存下来, 你把 skull 留在那里, 然后找到卡勒幽船, 击败她的船长, 夺回他从你那里拿走的护身符。 ";
			link.l1 = "为什么卡勒幽船的船长需要这些护身符? ";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "我想他想去美洲虎人的神庙, 他认为护身符会帮助他。 但我可能错了。 尽管如此, 卡勒幽船总是被我土地上的神器所吸引。 她航行到美洲虎人神庙所在的岛屿附近, 也航行到我祖国的海岸。 ";
			link.l1 = "那个岛在哪里? ";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "首先你找到尤姆.西米尔的头骨和护身符。 然后我们再谈那个岛。 ";
			link.l1 = "好吧。 你能给我一个提示, 去哪里找玉头骨吗? ";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "我不太清楚。 但它在加勒比海这里。 护身符也在。 问问。 寻找。 找到。 ";
			link.l1 = "呵... 好吧, 我会试试。 ";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "你要小心, 白人船长。 卡勒幽船能感觉到查文的物品。 当你有护身符时, 她会寻找你。 如果她找到你, 赶紧逃跑。 如果她抓住你, 你就死定了。 ";
			link.l1 = "这艘被诅咒的船快得离谱! 它的速度大约是我见过的任何船的两倍。 但我注意到它在逆风航行时很困难。 ";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "卡勒幽船被诅咒了 --这就是它如此之快的原因。 很难逃脱。 你必须有一艘能超越卡勒幽船的船。 否则你会死。 当你找到护身符时, 把它带给我。 不要把护身符留在船上。 ";
			link.l1 = "我已经知道了。 谢谢你的故事, 伟大的萨满。 我该走了。 ";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "我会请求神灵帮助你, 从卡勒幽船手中拯救你。 ";
			link.l1 = "... ";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("你已赠送护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "(看着) 是的, 就是这个。 第二个查文护身符。 你做得很好。 你还需要找到另一个护身符。 ";
			link.l1 = "我记得, 萨满。 很快你就会得到它。 ";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "去吧, 白人。 再找一个护身符。 ";
				link.l1 = "我已经有了, 伟大的萨满。 看。 ";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "去吧, 白人。 再找一个护身符。 ";
				link.l1 = "... ";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("你已赠送护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "(看着) 是的, 就是这个。 第三个查文护身符。 你做得很好。 你已经找到了所有能通过尤姆.西米尔仆人 --死亡美洲虎战士的护身符。 ";
			link.l1 = "现在我明白了, 我需要玉头骨? ";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "你说得对。 尤姆.西米尔的玉头骨。 你必须把它带到查文神庙。 然后卡勒幽船将永远失去力量。 ";
			link.l1 = "图图阿塔帕克, 请告诉我, 去哪里找? 有什么想法吗? ";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "不。 你想想最后一次看到玉头骨是在哪里。 你把它给了谁。 从那里开始找。 ";
				link.l1 = "好的, 伟大的萨满。 我会尽我所能。 ";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "一个对尤姆.西米尔头骨感兴趣的白人术士。 他在寻找它。 他甚至来到了我们的村庄。 我听说术士住在荷兰岛上的一所房子里。 在荷兰岛上寻找术士, 你可能会知道一些事情。 ";
				link.l1 = "好的, 伟大的萨满。 我会尽我所能。 ";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "我将从库拉索开始, 在那里我把它交给了所罗门。 也许我会找到一些线索 --弄清楚头骨发生了什么。 ";
				else sTemp = "我将从访问库拉索开始 --在那里我把玉头骨卖给了约阿希姆.梅里曼。 ";
			}
			else sTemp = "图图阿塔帕克告诉我, 一个‘白人术士’对玉头骨表现出兴趣, 并建议在荷兰岛上寻找他。 那可能是谁? ";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "去吧, 白人。 寻找尤姆.西米尔的玉头骨。 ";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "我把它带来了, 伟大的萨满, 看看。 ";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "... ";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "去吧, 白人。 寻找尤姆.西米尔的玉头骨。 ";
			link.l1 = "恐怕我做不到。 我找到了术士, 但在最后一刻他带着头骨溜走了。 我完全不知道他现在可能在哪里。 ";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "这很糟糕, 白人。 现在你无法通过神庙, 也无法击败卡勒幽船。 我不会给你礼物。 现在你离开。 ";
			link.l1 = "... ";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "你现在离开, 白人。 ";
			link.l1 = "... ";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(看着) 是的, 就是这个。 非常美丽。 也非常可怕。 ";
			link.l1 = "当然... 但更有趣的是 - 我从古巴到多米尼加穿越了整个加勒比海, 当我有这个头骨时, 卡勒幽船从未试图攻击我, 我甚至没有看到它。 而当我把护身符带给你时, 我一出海它就不断追我, 几个小时内就找到了我。 ";
			link.l1.go = "Tuttuat_46a";
		break;
		
		case "Tuttuat_46a":
			dialog.text = "我认为, 卡勒幽船害怕头骨或者无法感知它。 我没有其他解释。 也许尤姆.西米尔让玉头骨对卡勒幽船非常危险 --除了诅咒之外。 也许这就是船长如此想得到我们人民的三个护身符的原因。 为了获得如何控制尤姆.西米尔咒语的智慧。 ";
			link.l1 = "那么, 只要我在船上带着玉头骨, 我就不必担心卡勒幽船的攻击? ";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "正是如此, 白脸人。 你自己也看到了。 ";
			link.l1 = "非常好! 这样我就可以指挥一艘大船, 雇佣像样的船员, 并为那个行尸走肉准备一个愉快的欢迎仪式, 当他的诅咒解除时, 不用担心他会提前拦截我... ";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "... 顺便说一下, 关于那个咒语 - 我应该把玉头骨带到哪里去? ";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "你必须把它带到查文神庙, 完成你的旅程。 我想给你讲个故事。 你准备好听了吗, 白人? ";
			link.l1 = "我的耳朵总是为你的智慧敞开, 图图阿塔帕克。 ";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "正如我祖先的传说所说, 很久以前, 当白人还没有来到我们的土地时, 查文的伟大酋长建造了一艘非常非常大的独木舟, 并派了一支战士队伍前往多岛之地。 伟大酋长的儿子带领他们, 还有一位高级萨满。 在多岛之地, 他们发现了一片荒地, 建立了一个定居点, 并为尤姆.西米尔建造了一座伟大的神庙, 只有我们的伟大祖先才能建造\n信使带回了好消息, 但再也没有人见过酋长的儿子。 萨满或战士。 传说他们留在那里生活, 但最聪明的萨满与神灵交谈后说, 那里不再有人居住, 尤姆.西米尔统治着这片土地\n多岛之地就是加勒比海, 白人。 尤姆.西米尔的神庙位于一个没有白人也没有印第安人居住的岛上。 只有尤姆.西米尔的仆人, 查维纳维, 仍然守卫着神庙的走廊。 ";
			link.l1 = "那个岛在哪里? ";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "我想它很小, 在村子的北边, 在你们称为海洋的那片大水中, 离得不远。 ";
			link.l1 = "嗯... 也许在多米尼加北部的海洋边界? 该死的 - 那是海洋中的一大片区域! 如果没人听说过, 我怎么能找到一个小岛? ";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "我不能说得更清楚了。 但我还知道另一个故事。 你可能从你的兄弟那里听说过。 大约二十年前, 白人发现了那个岛。 他和一个女人以及一个老人进入了尤姆.西米尔的神庙, 拿走了一件强大的神器 --升起的太阳之球。 在岛的海岸上, 白脸船长遭到了卡勒幽船的袭击\n白脸人很聪明。 他用升起的太阳之球使卡勒幽船的船长和船员失明。 卡勒幽船的诅咒减弱了, 船长击沉了它, 但升起的太阳之球溶解了。 如果你找到那个白脸人, 他会告诉你岛在哪里。 ";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "哈! 我想我知道那个‘白脸人’... 这个故事听起来太相似了。 那么, 卡勒幽船被击沉了? ";
			else link.l1 = "嗯... 那么, 卡勒幽船被击沉了? ";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "是的, 但诅咒保护他们免于死亡。 他们修好了它, 并继续他们的永恒旅程。 ";
			link.l1 = "好吧, 知道了。 但我在神庙里该做什么? 我该把头骨放在哪里? 我怎么打败守卫它的美洲虎战士? 如果他们像术士梅里曼召唤的那些查维纳维一样, 独自去那里会很愚蠢 --他们每个人都像十个士兵一样强壮。 ";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "他们不是。 白人术士用头骨召唤的查维纳维很弱。 比尤姆.西米尔自己召唤的要弱得多。 你永远无法伤害他们, 他们用武器一碰就能杀死你。 ";
			link.l1 = "等等 - 那个‘白脸人’是怎么进入神庙并偷走神器的? ";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "在第一个白脸人进入神庙之前, 它由死去祖先的灵魂守护。 白脸人是个强大的战士, 他打败了他们。 当他偷走升起的太阳之球时, 尤姆.西米尔非常愤怒。 他向白脸人发送了火与硫磺, 几乎摧毁了神庙, 但他带着神器逃跑了。 现在尤姆.西米尔召唤了无敌的美洲虎战士来守卫神庙。 ";
			link.l1 = "太好了! 那我该怎么溜进去? ";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "我会帮助你, 白人。 我会给你带来的两个查文护身符。 我会与祖先的灵魂交谈并强化护身符。 当你身上有一个时, 你可以像普通士兵一样与美洲虎战士战斗, 你会像他们一样, 虽然非常强壮。 护身符会保护你, 并赋予你伤害神庙查维纳维的武器力量。 ";
			link.l1 = "你确定护身符会有帮助吗? ";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "我知道。 我与祖先交谈。 我是伟大的萨满。 你要相信我。 你带上两个护身符。 一个保护。 另一个增强武器。 你必须使用一个护身符。 选择哪一个 - 由你决定。 如果你不佩戴护身符, 你会死于美洲虎战士之手\n你要记住, 在午夜时分, 尤姆.西米尔会让你杀死的所有战士复活。 你必须计算时间, 不要与他们战斗两次, 或者可以, 神灵告诉我你可以。 ";
			link.l1 = "我明白了。 ";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "你带上护身符。 给你。 你要记住, 它们的力量是有限的。 一个月后会减弱。 你还记得我说过你无法持有它们的力量吗? 只有我们部落的伟大萨满才能持有它。 ";
			link.l1 = "我记得。 那么, 我只有一个月? 一个月? ";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "是的。 当你来到尤姆.西米尔的神庙时, 你必须找到圣地和里面的巨鹰雕像。 这是神庙最重要的部分。 在这里你放置尤姆.西米尔的玉头骨, 卡勒幽船的诅咒就会解除。 当他再次攻击你时, 你可以像普通人一样击败他。 然后你把他从你那里拿走的护身符带给我。 ";
			link.l1 = "巨鹰? 那是什么? ";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "巨鹰是生活在我家乡山区的一种伟大鸟类。 为了纪念家乡, 祖先们在圣地附近建造了巨鹰雕像。 ";
			link.l1 = "好的, 我会寻找它... ";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "你要小心。 除了美洲虎战士, 神庙里还潜伏着许多危险。 ";
			link.l1 = "什么危险? ";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "我不太确定。 你自己会看到的。 可能是陷阱, 或者是... 迷惑。 进入圣地很困难。 入口被封锁, 你必须找到打开它的方法。 我的祖先不仅是伟大的战士和萨满, 也是伟大的建筑师, 要打开它你需要思考。 ";
			link.l1 = "呵! 听起来很可怕, 但让它们都来吧! 我不会浪费时间。 我马上启航! ";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "去吧, 白人战士。 我会召唤神灵帮助你对抗美洲虎战士和卡勒幽船。 记住, 如果你使用我给的护身符, 我可以帮助你, 否则你会灭亡";
			link.l1 = "谢谢你, 伟大的萨满... 我会完成它的。 ";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("你已收到两个护身符");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// 转换护身符
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // 计时器
			// 使凯尔罗阿岛可用
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "但我有一个线索: 似乎访问过查文神庙的白脸船长不是别人, 正是我的好朋友纳撒尼尔.霍克。 我记得他说过他在马龙镇有一张那个岛的地图。 我想我会去拜访纳撒尼尔。 ");
			}
			else AddQuestUserData("Caleuche", "sText", "那是海洋中的一大片区域, 但我别无选择。 我必须彻底搜索它。 萨满说在多米尼加北部, 而且不太远, 所以我可以稳步向北移动, 它很可能在东边或西边一点。 他还提到了某个摧毁了亡灵船的船长, 也许我会很幸运, 有一天能找到他, 唉, 他说我只有一个月的时间来持有这种力量或其他什么, 哦, 好吧, 就这样吧, 让搜索开始吧! ");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "我与神灵交谈过。 你已经在尤姆.西米尔的神庙所在的岛上。 你找到卡勒幽船和护身符了吗? ";
				link.l1 = "你说得对, 伟大的萨满。 我找到了那个岛, 进入了神庙, 并把玉头骨留在了里面。 ";
				link.l1.go = "Tuttuat_63";
			}
			else
			{
				dialog.text = "去吧, 白人战士。 ";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "图图阿塔帕克, 你看... 我没有及时把头骨带到神庙, 你的护身符失去了力量。 ";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "... ";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; // 移除计时器
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "你解除了卡勒幽船的诅咒。 之后她找到你了吗? ";
			link.l1 = "是的。 我们就在岛上相遇了。 我与她交战并获胜。 现在我有所有三个护身符。 给你。 ";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("你已赠送三个查文护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "你是个快速而强大的战士, 白脸人。 图图阿塔帕克不喜欢白人, 但我尊重勇敢和有技巧的战士。 你做得非常好。 你让海洋摆脱了卡勒幽船。 你给我带来了三个护身符。 我会奖励你。 ";
			link.l1 = "你承诺过一些关于‘我将能够永远拥有的力量’? ";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "你说得对。 我会给你那种力量。 加勒比海没有人知道我知道的植物秘密。 听我说, 白脸人! 在我的家乡, 有一种药用植物。 我们称之为曼加罗萨。 你听说过这种植物吗? ";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "是的。 我亲手拿过它。 吉普赛人对它表现出极大的兴趣。 其中一位, 治疗师阿米莉亚, 甚至可以... ";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "不知道... ";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "我听说过草药师阿米莉亚。 她知道一点但不多。 她不知道曼加罗萨的秘密。 只有来自我的家乡, 曼加罗萨被带到这里的伟大萨满, 才能充分利用它的力量。 ";
			link.l1 = "什么力量? ";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "这种草药生长在我的家乡, 但在加勒比海也有。 它是一种浅绿色的高大植物, 叶子像张开手指的手掌, 气味很好。 你会立即认出它, 不会与任何东西混淆。 我知道这种植物的秘密。 我可以从中提取力量。 ";
			link.l1 = "我明白, 但什么样的力量? ";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "我可以用曼加罗萨制作药水。 非常强大的药水。 在加勒比海, 除了我, 没有人能制作这些药水。 我的药水能让男人永远更强壮。 更快。 更聪明。 目光更敏锐。 更英俊。 更幸运。 我为你酿造三瓶这样的药水。 ";
			link.l1 = "非常有趣! ";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "你是伟大的战士, 所以你首先需要让你更健壮的药水和让你更快的药水。 在我制作前两种之后, 你选择第三种药水。 但你必须给我带来曼加罗萨来制作它们 --我没有。 ";
			link.l1 = "我该去哪里找曼加罗萨? ";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "曼加罗萨在加勒比海是一种稀有草药。 它生长在人们不常去的地方。 愚蠢的人会采摘它, 晒干并吸食。 非常愚蠢的人。 不要吸食它! 这是力量的浪费... 寻找丛林和海湾, 愚蠢的人不去的秘密地方。 仔细寻找。 每瓶药水我需要五根茎的曼加罗萨。 ";
			link.l1 = "好的, 伟大的萨满。 一旦我有足够的曼加罗萨, 我就会回来找你。 ";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "去吧, 白人战士。 给我带来曼加罗萨。 你不会后悔的。 我的药水是最好的。 我会告诉神灵帮助你寻找。 ";
			link.l1 = "谢谢你! 再见, 萨满! ";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "你带来了五根茎的曼加罗萨来制作药水吗? ";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "是的。 这是你需要的五株植物。 ";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "还没有, 伟大的萨满。 我的搜索还在继续... ";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "非常好。 明天太阳落山时来。 我会为你酿造增加你的反应和敏捷的药水。 ";
					link.l1 = "好的, 萨满。 我晚上来。 ";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "非常好。 明天太阳落山时来。 我会为你酿造增加你的耐力的药水。 ";
					link.l1 = "好的, 萨满。 我晚上来。 ";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "非常好。 你选择什么药水? 力量药水。 敏锐视觉药水。 智力药水。 美丽药水还是幸运药水? ";
					link.l1 = "力量药水。 ";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "敏锐视觉药水。 ";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "智力药水。 ";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "美丽药水。 ";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "幸运药水。 ";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = " 它使你的动作更快, 你更擅长使用轻便武器。 ";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = " 它使你在长途旅行中更耐寒, 你更擅长使用锋利的军刀。 ";
				dialog.text = "药水准备好了, 白脸战士。 你拿走它。 "+sTemp+"";
				link.l1 = "谢谢你, 伟大的萨满。 ";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "还没准备好, 白人。 过会儿来。 不要打扰我。 ";
				link.l1 = "好吧... ";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "我为你酿造了所有我承诺的药水。 你变得更强了。 你高兴吗? ";
				link.l1 = "是的, 伟大的萨满。 这确实是一个有价值的奖励。 ";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "你再找五根茎的曼加罗萨, 带给我。 我会给你另一种药水。 ";
				link.l1 = "我会给你带来更多的。 再见! ";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "明天像往常一样来。 我会为你酿造让你更强壮的药水, 你更擅长使用大斧头。 ";
			link.l1 = "好的。 ";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "明天像往常一样来。 我会为你酿造让你眼睛更敏锐的药水, 这样你就能看到每个目标, 你更擅长使用轰鸣的火焰武器。 ";
			link.l1 = "好的。 ";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "明天像往常一样来。 我会为你酿造让你更聪明的药水, 你更擅长躲避敌人。 ";
			link.l1 = "好的。 ";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "明天像往常一样来。 我会为你酿造让你更英俊的药水, 你更擅长说服别人。 ";
			link.l1 = "好的。 ";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "明天像往常一样来。 我会为你酿造让你更幸运的药水, 你会有好运气。 ";
			link.l1 = "好的。 ";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "我很高兴你喜欢我的艺术, 伟大萨满的艺术。 ";
			link.l1 = "说吧, 图图阿塔帕克, 你需要这三个护身符做什么? 只是好奇... ";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "你已经感受到了这两个护身符的力量。 神灵会帮助我赋予它们力量, 三个护身符一起会给伟大萨满带来我祖先查文的智慧和启示。 ";
			link.l1 = "我明白了。 好吧, 再次感谢你出色的药水。 你真是一位伟大的萨满。 现在我该走了。 再见, 图图阿塔帕克, 希望能再次见到你。 ";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "再见, 白人战士。 你不再需要寻找我了。 我要去隐居, 领悟我祖先的智慧。 愿神灵在你的旅程中帮助你! ";
			link.l1 = "那么... 哈... 愿神灵也照亮你的道路, 伟大的萨满。 再见... ";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("你已赠送护身符");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "你让我难过, 白脸人。 我与神灵举行仪式赋予这些护身符力量, 而你浪费了它。 我很难过。 你现在走吧。 图图阿塔帕克没什么再要对你说的了。 ";
			link.l1 = "对不起, 我真的很不走运... 哦, 好吧。 再见, 萨满。 ";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// 卡勒幽船船长
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "一切都是徒劳的, 水手。 你赢不了我。 我所有躺在甲板上的人都会在黎明前拼凑骨头重新站起来。 我们无法被杀死, 因为死亡永远抛弃了我们。 ";
			link.l1 = "该死! 你是死是活? 更像是还活着 --死人通常安静地躺着, 不会挥舞刀剑。 但你是谁, 为什么攻击我的船? ";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "我是‘飞翔之心’号的巴尔萨泽.德.科尔德斯。 那些对我一无所知的可怜懦夫叫我范.德.德肯, ‘飞翔的荷兰人’号船长。 但这不重要。 重要的是你身上有一个护身符, 我现在要拿走。 我需要它! 我能感觉到! 查文的伟大护身符, 三个中的一个, 终于要归我了! 在我面前跪下, 凡人! 我可能会让你死得无痛! ";
			link.l1 = "去你妈的, 尸体! ";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "真不敢相信! 我上一次看到自己的血并感觉到疼痛已经是很久以前的事了... 怎么会? ! ";
			link.l1 = "这次你输了, 巴尔萨泽.德.科尔德斯。 我知道你的故事。 玉头骨已被送回查文神庙, 尤姆.西米尔的诅咒不再笼罩你或你的船员。 你再也不能让你的水手复活了。 ";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "哦, 所以你一定认为自己是救世主, 也许? 不! 巴尔萨泽.德.科尔德斯会为他所剩无几的生命付出高昂代价! ";
			link.l1 = "‘飞翔之心’的最后旅程在这里结束, 在凯尔罗阿。 你不会像二十五年前那样把船从海底升起。 ";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "霍克! 二十五年过去了, 我仍然记得就像昨天一样。 那个球体的光芒使我们失明, 把我的船劈成两半。 那是‘飞翔之心’和巴尔萨泽.德.科尔德斯的第一次也是最后一次失败... 所以让我们最后一次交锋吧, 船长! 战死沙场是轻松而受欢迎的! ";
			link.l1 = "... ";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// --> // 我们的水手在岸边
		case "on_coast":
			dialog.text = "终于, 你醒了, 船长... 你感觉怎么样? ";
			link.l1 = "该死, 发生了什么? 我的头因疼痛而裂开... ";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "当我们进入船长室时, 你躺在地板上, 一动不动。 伙计们把你抬起来拖到我们的船上 --正好及时, 因为躺在甲板上的死人开始再次站起来\n圣母玛利亚和所有圣徒! 我们迅速切断绳索, 试图驶离, 但他们船上的一轮齐射很快把我们的旧船变成了碎片, 我们失去了对它的控制。 然后他们升起风帆, 眨眼间就不见了\n我们的船搁浅了, 所有幸存的人都乘小船到达了岸边。 今天很多好人死了... 如果我们留在船上... 但我们确信风暴会彻底摧毁这艘船。 ";
			link.l1 = "不是你们的错, 先生们。 这是正确的决定。 谢谢你们, 我会记住的。 ";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "我们把你拖进小船, 然后带到岸边。 你几乎死了... ";
			link.l1 = "我欠你们一条命。 我昏迷在这里多久了? ";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "整整一天。 我们清洗并包扎了你的伤口, 给你喂了药, 还给你灌了些朗姆酒。 你应该很快就会好起来。 ";
			link.l1 = "这次我肯定不会死。 虽然我感觉不太好... ";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "那是肯定的... 那是‘飞翔的荷兰人’号吗, 船长? 他们为什么攻击我们? 为什么他们在登船前没有向我们射击, 而是后来只用一轮齐射就几乎击沉了我们的船? ";
			link.l1 = "他们的船长需要那个护身符, 就是我和印第安萨满图图阿塔帕克谈过的那个。 这就是为什么他们没有立即击沉我们, 但当他们的首领拿走护身符后, 他们很快就解决了我们... 真是噩梦! 一艘由死人驾驶的船! 难以置信... ";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "是的, 现在轮到我们遭遇‘飞翔的荷兰人’号了。 如果有机会, 我会去教堂, 为我奇迹般的获救点一支蜡烛, 并向我们的主祈祷... ";
			link.l1 = "我也是... 我想。 但首先我要回到那个村庄。 我需要把这件事都告诉图图阿塔帕克。 那艘被诅咒的船因为护身符攻击了我们! 我确信那个红皮肤的魔鬼知道那些活死人为什么需要它。 ";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "好吧。 但要小心, 船长, 你的伤口才刚刚愈合, 至少带个人以防万一。 ";
			link.l1 = "我会小心的, 我保证。 谢谢你们没有抛弃我! ";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "你在说什么, 船长! 我们会为你走到世界的尽头, 与成千上万的亡灵战斗! 很遗憾我们损失了这么多, 但这个故事将载入史册。 ";
			link.l1 = "... ";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//打开地点
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// 弗格斯.胡珀
		case "fergus":
			dialog.text = "嘿! 我还没收集到足够的蛇皮卖给你, 所以滚蛋! ";
			link.l1 = "嗯... 你是弗格斯.胡珀吗? ";
			link.l1.go = "fergus_1";
		break;
		
		case "fergus_1":
			dialog.text = "不, 我的名字是图图阿塔帕克, 如果你不马上消失, 我会诅咒你。 所以你最好快点, 否则你会... ";
			link.l1 = "... 失去理智, 烧毁自己的船, 我的水手会杀了我并夺走我所有的财物。 对吗? ";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "呃... 你到底是谁? ! 你怎么... ";
			link.l1 = "我们有一个共同的朋友, 弗格斯。 他是一位灯塔看守人, 他的名字是"+GetFullName(sld)+"。 他告诉我关于你的事, 并派我来找你。 顺便说一句, 我个人认识萨满图图阿塔帕克, 所以你的笑话没起作用, 抱歉。 听着, 我不是来找麻烦的。 我想从你这里买些东西, 不是蛇皮。 ";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "哦, 所以你认识我的老朋友! 他怎么样? 他还没在灯塔里无聊死吗? 请坐, 水手, 和我喝一杯! ";
			link.l1 = "对不起, 弗格斯, 我真的没有太多时间。 听着, 我需要那个印第安护身符, 就是你已故船长和图图阿塔帕克从大陆拿走的那个。 我会出个好价钱, 你也能摆脱这个危险的小玩意儿。 ";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "那有什么危险? 到目前为止我没看到有什么危害。 它只是一块无用的石头";
			link.l1 = "那是因为你不再航海了。 直到最近我还拥有一个类似的护身符。 一艘幽灵船在追捕这些东西。 ";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "你在开玩笑吗, 伙计? 也许认识图图阿塔帕克已经对你造成了影响? 小心点, 船长, 那个红皮肤的魔鬼会吞噬你的思想... ";
			link.l1 = "信不信由你, 但我告诉你的是实话。 如果不是亲眼所见, 我自己也不会相信, 我可以对着圣经发誓, 或者你可以问问和我在一起的人。 我在与卡勒幽船的那次遭遇中侥幸存活。 ";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "卡勒幽船? ";
			link.l1 = "嗯, 大多数人叫它‘飞翔的荷兰人’, 但它的真名是‘飞翔之心’。 不管怎样。 把那个护身符卖给我吧。 你反正也用不上, 我知道。 ";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "没错。 这只是一个无用的小玩意儿, 虽然很漂亮。 听着, 我本来会毫不犹豫地卖给你, 但你看 - 我已经没有了。 它和其他东西一起在我去丛林打猎时被人从我的小屋里偷走了。 这是最近发生的事, 大约一个月前。 抱歉, 我帮不了你。 ";
			link.l1 = "谁偷的? ";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "你真的认为如果我知道是谁洗劫了我的家, 我还会坐在这里吗? 伯利兹城外有一群小偷和强盗, 他们在镇上有眼线。 至少指挥官是这么认为的。 我确信就是他们。 ";
			link.l1 = "指挥官知道有强盗却什么也不做? ";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "他有没有做什么, 我不知道。 我唯一确定的是我的东西不见了, 你宝贵的护身符也在其中。 试着去找这些强盗 - 也许你会在他们的口袋里找到它。 他们不太可能已经卖掉了 - 商人不需要这样的东西。 ";
			link.l1 = "好吧, 我会去见指挥官。 祝你好运, 弗格斯! ";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		// 镇上的强盗
		case "Beliz_townbandos":
			dialog.text = "嘿! 你需要什么? 我不期待任何客人。 滚蛋! ";
			link.l1 = "为什么这么粗鲁, 朋友? 我只是想问... ";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "你没听见吗? 他妈的滚出去, 否则我把你踢出去! ";
			link.l1 = "嗯... 好吧, 也许你就是我要找的人。 你看起来太紧张了, 伙计... ";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "觉得自己很聪明, 是吗? 再一次: 要么现在消失, 要么我叫卫兵, 他们会把你关进监狱! ";
			link.l1 = "把我关进监狱? 真有趣。 你知道, 现在我几乎可以肯定我找到了要找的人。 好吧, 我同意。 我们叫卫兵吧, 然后我们一起去指挥官的办公室, 像一个幸福的家庭。 我刚去过那里, 所以我记得路... 卫兵! 卫兵! ";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "去你的! 我要刺穿你! ";
			link.l1 = "哦吼吼! 好吧, 你可以试试! ";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // 以免出现NPC问题
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// 森林强盗首领
		case "Beliz_forestbandos":
			dialog.text = "嘿, 旅行者! 欢迎, 欢迎... 晚餐。 住宿 - 一切都要花钱。 所以, 准备好把口袋翻出来吧! ";
			link.l1 = "别这么快, 我的好人。 我和你有生意。 ";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "生意? 哈哈! 你唯一的生意就是把你所有的银和金给我! ";
			link.l1 = "闭嘴吧。 我给你带来了一封来自伯利兹的信, 你一直在等的。 信使无法应付卫兵, 把事情委托给了我。 ";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "给我看! ";
			link.l1 = "这里... ";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("你已赠送便条");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(阅读) 嗯... 这确实很奇怪... 你是怎么卷入的? ";
			link.l1 = "我已经告诉过你, 他们抓住了你的人, 所以我接了他的工作。 他答应给我钱和你热情的欢迎... ";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "热情的欢迎? 好吧, 朋友。 我们会让你暖和起来, 喂饱你, 给你钱, 所有那些东西 - 但你, 你也必须向我们证明你不是卫兵的走狗。 我们现在有一笔账要算\n最近有一个商人到达附近的海湾; 显然, 他想带着货物绕过海关潜入城市。 但我们仍然会向他征收关税。 我们毕竟是守法的人! 你会和我们一起去。 你知道剑的哪一端该朝哪里吗? ";
			link.l1 = "我会得到这份关税的一份吗? ";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "当然! 如果你在战斗中勇敢并且活下来。 但不要指望轻松取胜, 商人不是一个人, 他有护卫, 而且护卫很多。 好吧, 时间到了 - 我们的猎物很近了。 孩子们! 准备好武器, 我们出发! ";
			link.l1 = "... ";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//禁止等待
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "我看你不是懦夫。 做得好! 你已经赢得了你的份额。 你想要什么? 现金? 商品? 他们带了很多酒, 肯定很值钱。 ";
			link.l1 = "现金。 ";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "商品。 ";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("你已收到100达布隆");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "给你! 这个钱包是送递信件的。 ";
			link.l1 = "谢谢! 这才是我喜欢的方式! ";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("你已收到30瓶朗姆酒");
			Log_Info("你已收到12瓶葡萄酒");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "给你! 只是别喝死自己, 哈哈哈! 这个钱包是送递信件的。 ";
			link.l1 = "谢谢! 这才是我喜欢的方式! ";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("你已收到一个钱包");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "在我看来你是个正派的人。 再做一笔交易怎么样? 就是关于你给我送的那封信。 ";
			link.l1 = "当然。 ";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "那就来洞穴吧。 有两个洞穴。 到我们上次见面的丛林里, 然后走左边的路。 我们三天后在洞穴入口集合, 从午夜到一点。 明白了吗? 如果你是个好孩子, 我们会接受你加入我们的团伙。 但记住 - 如果你在镇上透露任何事情, 你就完了。 我的手很长。 ";
			link.l1 = "别再吓唬我了。 我明白了。 我会守口如瓶。 三天后等我, 我会去的。 我喜欢轻松赚钱! ";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "好吧, 朋友。 现在在卫兵来之前消失。 我们也走了。 ";
			link.l1 = "回头见, 朋友... ";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // 关闭洞穴
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // 计时器
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // 计时器
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以移动时间
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// 篝火
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// 在洞穴中打包藏匿物
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// 改变标志
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
		break;
		
		// 在洞穴中消灭了强盗
		case "Beliz_cavebandos":
			dialog.text = "什么! 我猜你决定索取我们的财产? 你不会得逞的, 你这个肮脏的蠕虫! ";
			link.l1 = "你刚才叫谁蠕虫, 你这个败类? ! ";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Harpy船长
		case "reginald":
			dialog.text = "你好, 同事! 什么风把你吹来了? ";
			link.l1 = TimeGreeting()+", 杰克逊先生。 很高兴终于找到你。 ";
			link.l1.go = "reginald_1";
		break;
		
		case "reginald_1":
			dialog.text = "‘杰克逊先生’, 哈哈! 好吧, 说实话, 很快我也会这样称呼自己。 我为这个该死的公司不停地工作... 但他们付得很好, 非常好! .. 那么, 你为什么来这里,  mate? ";
			link.l1 = "我们共同的熟人, 灯塔看守人, 告诉我你有一个古老的印第安护身符。 我猜你从来没用过它, 而我真的很需要它。 我想从你这里买它。 ";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "哦, 你是说那个漂亮的小玩意儿, 我向那个退休的水手打听过的? 是的, 朋友, 你说得对, 它实际上从来没用过, 只是看起来很漂亮。 ";
			link.l1 = "你想要多少钱? ";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "你看, 有个小问题... 让我解释一下。 我现在身上没有。 因为我从未找到用途, 所以我把它和其他物品一起留在了岸边的箱子里。 ";
			link.l1 = "哦, 这解释了你为什么还... 好吧, 没关系。 我们去你的那个箱子那里, 我从你那里买护身符。 就这么简单。 你把它放在哪里了? ";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "并不完全那么简单。 我的箱子位于巴巴多斯的灯塔塔里, 并且被安全地锁着, 这样在我不在的时候没人能利用它。 很抱歉, 根据我与荷兰人的合同, 我不能和你一起去巴巴多斯, 我必须在菲利普斯堡和皇家港之间航行, 严格遵守时间表。 而巴巴多斯不在那条航线上。 ";
			link.l1 = "那我们能做什么? 我真的真的需要那个护身符! ";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "嗯... 有一个选择。 我把箱子的钥匙给你, 你自己航行到巴巴多斯。 但你必须补偿我箱子里的所有东西, 你可以拿走它们。 很抱歉不信任你 - 但你必须理解。 我以前从未见过你。 ";
			link.l1 = "多少钱? ";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "五百金币。 不能少。 ";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "成交! 给你金子。 ";
				link.l1.go = "reginald_10";
			}
			link.l2 = "嗯... 我身上没有那么多达布隆。 ";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "那么等你筹到钱再来找我。 如果你能找到我一次, 就能再找到我。 我现在要在圣马丁和牙买加之间航行一段时间。 ";
			link.l1 = "好吧, 成交。 ";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
		break;
		
		case "reginald_9":
			dialog.text = "你又来啦, 朋友? 你有500金币吗? ";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "是的。 给你金子。 ";
				link.l1.go = "reginald_10";
			}
			link.l2 = "还没有, 但我正在努力。 ";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			Log_Info("你已支付500达布隆");
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(500);
			DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // 恢复海上任务
			dialog.text = "太好了! 这是你的钥匙。 我只有一个请求: 在你拿走里面的所有东西后, 请把钥匙留在锁里。 我不想再委托配新锁和钥匙了。 ";
			link.l1 = "好的。 ";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "那么祝你好运, 朋友! 一路顺风! ";
			link.l1 = "你也一样... 一路顺风, 杰克逊先生! ";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
			DeleteAttribute(pchar, "questTemp.Garpiya");
			GiveItem2Character(pchar, "kaleuche_key"); 
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			AddQuestRecord("Caleuche", "20");
			// 藏匿物箱子
			i = Findlocation("Mayak2");
			Locations[i].models.always.locators = "lighthouse_Blocators";
			locations[i].private1.key = "kaleuche_key";
			locations[i].private1.key.delItem = true;
			locations[i].private1.items.kaleuche_amulet3 = 1;
			locations[i].private1.items.pistol9 = 1;
			locations[i].private1.items.indian_6 = 1;
			locations[i].private1.items.map_barbados = 1;
			locations[i].private1.items.map_part2 = 1;
			locations[i].private1.items.jewelry22 = 5;
			locations[i].private1.items.jewelry17 = 6;
			locations[i].private1.items.jewelry12 = 3;
			locations[i].private1.items.jewelry16 = 2;
			locations[i].private1.items.jewelry20 = 7;
			locations[i].private1.items.jewelry53 = 11;
			locations[i].private1.items.mineral25 = 1;
			locations[i].private1.items.mineral21 = 1;
			locations[i].private1.items.mineral22 = 5;
			locations[i].private1.items.mineral26 = 1;
			locations[i].private1.items.mineral10 = 1;
			locations[i].private1.items.mineral3 = 10;
			pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
			pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
			pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;
		
		// 威廉斯塔德的修士
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "你好, "+GetFullName(pchar)+"船长。 很高兴在威廉斯塔德欢迎你。 ";
			link.l1 = "你好, 神父。 我不记得你了。 我们认识吗? ";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "你的船停泊后, 我打听了你的情况。 我想请你帮忙。 ";
			link.l1 = "非常有趣。 为什么是我? ";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "因为你为自由省共和国做了很多事。 你在公司里地位良好, 和总督是朋友。 我已经向几个部门申诉过, 都被驳回了, 但我确实希望像你这样高尚的人不会拒绝我们主的仆人的卑微请求。 ";
			}
			else
			{
				dialog.text = "因为你不为我们的总督服务。 你不为公司工作, 也与我们的军队没有往来 - 否则你很可能会像赶走一只烦人的苍蝇一样拒绝我, 因为我已经向几个部门申诉过, 都被驳回了。 ";
			}
			link.l1 = "好吧。 你的请求性质是什么? ";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "银行后面有一所房子。 住在那里的一位女士在里面租了一个房间给一个非常可疑的人, 不是本地人, 也不是荷兰人。 于是我们的修道院长, "+sld.name+"神父, 认出了他\n是若阿金.梅里曼, 一个葡萄牙人, 被宗教裁判所指控施行巫术和与邪恶力量打交道。 他在新世界躲避宗教裁判所。 你知道, 西班牙人经常为了把人绑在火刑柱上烧死, 而指控那些不受欢迎的人异端和巫术, 但... 在这种情况下他们是对的。 梅里曼是个术士\n所以, 他在威廉斯塔德住了一段时间, 然后突然消失了, 就像他出现时一样。 过了一段时间, 那个把房间租给他的女人, 再也没有走出那所房子。 再也没有! 从此再也没有人在任何地方见过她\n到了晚上, 市民们偶尔能看到二楼的窗户里闪烁着红蓝光芒, 听到奇怪的声音, 几乎像是某种邪恶的尖叫。 "+sld.name+"神父向指挥官申诉。 他派了四名士兵巡逻, 他们搜查了房子, 但什么也没找到: 既没有女房东本人, 也没有其他人, 也没有任何可疑之处\n但这些奇怪的事情还在继续发生。 女房东再也没有出现, 晚上那里仍然能看到地狱般的光芒。 此外, 最近还有两个乞丐失踪了。 我听到他们在教堂前院交谈 - 他们知道房子里没有主人, 所以决定在那里住宿。 此后再也没有人见过他们。 ";
			link.l1 = "我猜, 你想让我进入那所房子, 查明到底发生了什么? ";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "正是如此, 高贵的先生。 请帮助神圣的教会。 指挥官说我们在想象事情, 因为他的巡逻队什么也没找到。 政府也这么认为。 普通人根本不在乎, 因为他们不认为这对他们是明显的威胁。 ";
			link.l1 = "嗯... 我需要在晚上去那里? ";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "是的, 先生。 白天那里很安静, 所以士兵们什么也没找到, 我想指挥官是为他的人害怕, 我也会害怕。 但请, 我求你。 "+sld.name+"神父会感谢你, 并为你的服务奖励你。 一旦你在夜间去过那个巢穴, 请告诉他你在那里发现了什么。 我向你保证, 我们的疑虑是有根据的。 ";
			link.l1 = "好吧。 我会考虑的。 ";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "谢谢你, 船长。 我希望你不会拒绝我卑微的请求。 请以我们的主。 我们的信仰和所有神圣的事物的名义去做。 带着我的祝福去吧。 ";
			link.l1 = "... ";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//打开地点
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "拜访若阿金.梅里曼的房子, 据他说, 那里晚上会发生奇怪的事情。 想起梅里曼看着玉头骨时眼中的特殊光芒, 我感到有点毛骨悚然。 看来老犹太人无法抗拒五十万比索的金额。 不管怎样, 我不想在晚上去梅里曼以前的住所。 ";
				else sTemp = "拜访我的老熟人若阿金.梅里曼的房子, 据说那里晚上会发生奇怪的事情。 我仍然记得梅里曼看着头骨时眼中的闪光, 老实说我感到害怕。 我真的不喜欢晚上去他以前住所的想法, 谁知道那里潜伏着什么魔鬼。 ";
			}
			else sTemp = "拜访银行后面的房子, 若阿金.梅里曼曾在那里租过房间。 显然这就是图图阿塔帕克所说的那个术士。 据修士说, 这所房子在晚上会发生奇怪的事情。 我真的不愿意去拜访术士的旧居, 谁知道那里潜伏着什么魔鬼。 ";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// 洞穴旁的猎人
		case "cavehunter":
			dialog.text = "等等, 伙计。 如果你珍惜生命, 最好不要去那里。 ";
			link.l1 = "怎么回事? ";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "相信我, 你不会想知道的。 但死亡就在眼前, 我可以对着圣经发誓你不会活着回来, 那里有超出你想象的东西。 ";
			link.l1 = "好吧, 如果你这么说, 我不会冒险。 谢谢你的警告。 ";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "不客气。 远离那条路。 ";
			link.l1 = "... ";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "远离那条路, 伙计。 ";
			link.l1 = "是的, 我记得... ";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "你确定你想去那里吗? ";
			link.l1 = "绝对确定。 哈瓦那教堂的修道院长"+sld.name+"派我来这里。 我必须确定这里发生了什么, 并采取适当的措施。 ";
			link.l1.go = "cavehunter_6";
		break;
		
		case "cavehunter_6":
			dialog.text = "这里发生了什么? 恐怕一旦你亲眼看到这里发生的事情, 你会吓得发抖。 ";
			link.l1 = "你是说行尸走肉? ";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "是的。 你最好相信我的话。 ";
			link.l1 = "我相信你。 我已经在威廉斯塔德遇到过那个邪恶的东西并摧毁了它。 现在我要进去, 摧毁潜伏在这个洞穴里的所有污秽。 ";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "你要一个人去那里? 你死定了, 伙计。 你不知道那里有多少那样的东西。 好吧, 如果你必须去, 我会去教堂为你灵魂的安宁点一支蜡烛。 ";
					link.l1 = "不要急着埋葬我。 我见过更糟的。 ";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "只有你们两个? 恐怕你们走不远。 你不知道那里有多少那样的东西。 这是自杀。 ";
					link.l1 = "你只是不太了解我们, 朋友。 让开, 我们将净化这个邪恶的巢穴。 ";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "只有你们三个? 如果你们敢这么做, 一定是经验丰富的战士。 但我仍然担心你们无法成功。 你不知道那个洞穴里有多少那样的东西。 ";
					link.l1 = "你只是不太了解我们, 朋友。 让开, 我们将净化这个邪恶的巢穴。 ";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "我看你们不是懦夫。 但你们真的不知道那里有多少那样的东西。 在这种情况下, 每个人都很重要。 去他的, 我和你们一起去, 我会用我的滑膛枪射击那些污秽! ";
					link.l1 = "你是个勇敢的人, 朋友。 我不会拒绝你的帮助。 我们走! ";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// 关闭出口定位器
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "我们走! 让污秽的亡灵灭亡! ";
			link.l1 = "... ";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "刚才真是一场大屠杀! 谁能想到这个地方藏着这么多死人! 好吧, 至少我们现在可以休息了... 请把这件事告诉你的修道院长, 就是派你来的那位。 我希望宗教裁判所会在你报告后介入此事。 毕竟, 处理亡灵是他们的职责, 我只是个普通猎人。 ";
			link.l1 = "我一定会告诉他。 谢谢你的帮助, 伙计。 你是个难得的勇士, 没多少人敢与死亡本身战斗! 祝你好运! ";
			link.l1.go = "cavehunter_exit";
		break;
		
		// 失败时墓穴中的士兵
		case "cryptguard":
			dialog.text = "站在原地! 这里禁止入内! ";
			link.l1 = "呃... 里面有什么? ";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "在那里发现了一个危险的术士。 只有神父和陪同的士兵可以进入。 ";
			link.l1 = "我明白了。 术士被捕了吗? ";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "我无权回答这类问题, 先生。 你该离开了。 ";
			link.l1 = "好吧, 我知道了。 祝你好运! ";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// 查文纳维首领
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "别动, 人类! 你已身处神庙的核心, 现在回头已为时过晚。 ";
			link.l1 = "你是谁? ! ";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "我是查文纳维的首领, 这片圣地的守护者。 你不是第一个进入这座神庙的人, 但在你之前只有两男一女进入后活着离开。 这就是我屈尊与你交谈的唯一原因。 你为什么来这里, 白脸人? ";
			link.l1 = "我带来了一件古老的遗物, 玉头骨。 五十年前它从大陆深处的一座印第安神庙被夺走。 我打算找到圣坛并将遗物归还给你们的神灵。 ";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "从你这种人嘴里听到这样的话很奇怪。 我不相信你。 你们白脸人总是来索取, 从不归还。 ";
			link.l1 = "我没有说谎。 通过归还头骨, 我将解除施加在 terrorizing 加勒比海的幽灵船船长身上的诅咒, 使他重新变为凡人, 我将永远为世界除去他。 ";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "你怎么知道我们的神会解除诅咒, 白脸人? 我们的神和你说话了吗? ";
			link.l1 = "没有。 我是根据一位名叫图图阿塔帕克的伟大萨满的建议来这里的。 正如他所说, 头骨是诅咒的关键, 而这是加勒比海唯一的神庙。 你知道吗 - 我认为他确实能与过去的灵魂交谈。 也许甚至能与你, 美洲虎战士的首领交谈。 ";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "你的话让我惊讶, 白脸人, 但我仍然不能完全信任你。 然而, 如果你来到这座神庙是为了归还我们的遗物, 我们的萨满肯定告诉过你关于这个地方。 它的创造。 历史和居民的事情\n如果是这样, 你将轻松回答我所有的问题。 然后我会承认你对我是真诚的, 允许你通过, 此外还会奖励你。 ";
			link.l1 = "那就问吧! ";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "我是查文纳维的首领, 美洲虎战士的首领。 千年前我是人类; 现在我在这些密室中履行神圣的职责。 我听从哪位神灵的命令? ";
			link.l1 = "米克特兰堤库特利。 ";
			link.l1.go = "question1_l";
			link.l2 = "库库尔坎。 ";
			link.l2.go = "question1_l";
			link.l3 = "尤姆.西米尔。 ";
			link.l3.go = "question1_r";
			link.l4 = "印蒂。 ";
			link.l4.go = "question1_l";
			link.l5 = "考伊尔。 ";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "在你们白脸人到来之前, 这片土地, 从北方的大雪原到南方的大平原, 都属于我们, 同一个家族的兄弟... ";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "在你们白脸人到来之前, 这片土地, 从北方的大雪原到南方的大平原, 都属于我们, 同一个家族的兄弟... ";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "哪个印第安部落建造了这座神庙? ";
			link.l1 = "印加。 ";
			link.l1.go = "question2_l";
			link.l2 = "查文。 ";
			link.l2.go = "question2_r";
			link.l3 = "玛雅。 ";
			link.l3.go = "question2_l";
			link.l4 = "阿兹特克。 ";
			link.l4.go = "question2_l";
			link.l5 = "阿拉瓦克。 ";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "我们的人民不断进步, 学习智慧, 征服新的森林。 平原和岛屿。 建造这座神庙的人从穿越大水的林地来到这里... ";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "我们的人民不断进步, 学习智慧, 征服新的森林。 平原和岛屿。 建造这座神庙的人从穿越大水的林地来到这里... ";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "谁领导了这群光荣的人民? ";
			link.l1 = "伟大的酋长。 ";
			link.l1.go = "question3_l";
			link.l2 = "大祭司。 ";
			link.l2.go = "question3_l";
			link.l3 = "伟大酋长的儿子。 ";
			link.l3.go = "question3_r";
			link.l4 = "大祭司的儿子。 ";
			link.l4.go = "question3_l";
			link.l5 = "这群人没有领袖。 ";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "印第安人, 勇敢的战士和旅行者, 即使在新地方定居后, 也始终热爱和尊敬他们的家园。 作为对家园爱的象征, 他们在神庙中建造了一座鸟形雕像, 作为家园的象征。 它在我身后... ";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "印第安人, 勇敢的战士和旅行者, 即使在新地方定居后, 也始终热爱和尊敬他们的家园。 作为对家园爱的象征, 他们在神庙中建造了一座鸟形雕像, 作为家园的象征。 它在我身后... ";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "这只鸟叫什么名字? ";
			link.l1 = "信天翁。 ";
			link.l1.go = "question4_l";
			link.l2 = "鹰。 ";
			link.l2.go = "question4_l";
			link.l3 = "秃鹫。 ";
			link.l3.go = "question4_l";
			link.l4 = "大鹏。 ";
			link.l4.go = "question4_l";
			link.l5 = "秃鹰。 ";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "繁荣的岁月如灯焰般流逝褪色, 生命离开了这座岛屿。 只有神庙矗立在这里, 作为古代印第安人伟大力量的纪念。 最后一位萨满在基座上留下了一个神圣的太阳之球, 它赐予勇敢者力量, 惩罚邪恶者。 它被在你之前来这里的人拿走了。 ";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "繁荣的岁月如灯焰般流逝褪色, 生命离开了这座岛屿。 只有神庙矗立在这里, 作为古代印第安人伟大力量的纪念。 最后一位萨满在基座上留下了一个神圣的太阳之球, 它赐予勇敢者力量, 惩罚邪恶者。 它被在你之前来这里的人拿走了。 ";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "那个神圣之球叫什么名字? ";
			link.l1 = "闪耀太阳之球。 ";
			link.l1.go = "question5_l";
			link.l2 = "阳光之球。 ";
			link.l2.go = "question5_l";
			link.l3 = "正午太阳之球。 ";
			link.l3.go = "question5_l";
			link.l4 = "升起太阳之球。 ";
			link.l4.go = "question5_r";
			link.l5 = "落日之球。 ";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "错误的答案表明你对我撒谎, 白人! 你带着邪恶的意图来到这里! 你设法偷偷通过了神庙和圣坛的守护者, 弄清楚了门的机制如何运作 - 但你仍然无法逃避与我的生死搏斗。 准备受死吧, 白脸人! ";
				link.l1 = "好吧, 如果你坚持 - 让我们看看你是多么伟大的战士... ";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "你对我的人民和神庙的了解值得称赞, 白脸人。 现在我相信你了。 去完成你来这里的目的吧。 将神圣遗物放在秃鹰面前的基座上, 那里曾是升起太阳之球的位置\n然后回到我这里。 你对尤姆.西米尔的崇拜以及自愿归还被你兄弟偷走之物的决定应该得到奖励。 ";
				link.l1 = "感谢你的信任, 伟大的首领。 ";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "错误的答案表明你对我撒谎, 白人! 你带着邪恶的意图来到这里! 你设法偷偷通过了神庙和圣坛的守护者, 弄清楚了门的机制如何运作 - 但你仍然无法逃避与我的生死搏斗。 准备受死吧, 白脸人! ";
			link.l1 = "好吧, 如果你坚持 - 让我们看看你是多么伟大的战士... ";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "你已完成承诺, 白脸人。 我很高兴你不像你大多数兄弟那样是个骗子。 我也会信守诺言。 拿着这个来自我的礼物 - 美洲虎战士力量的象征。 尤姆.西米尔亲自用他的一部分力量赋予了这张兽皮魔力。 ";
			link.l1 = "哇! 太漂亮了! ";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("你已收到美洲虎兽皮");
			PlaySound("interface\important_item.wav");
			dialog.text = "这不是普通的兽皮。 一旦你穿上它, 就会获得美洲虎战士的力量。 你那喷火射铅的武器威力将增加十倍, 你将能在战场上横扫敌人的尸体\n但凡人无法持有尤姆.西米尔注入这张兽皮的力量。 一旦你释放它, 它只会陪伴你到下一个午夜, 然后就会失效。 珍惜它, 白脸人, 不要在小规模冲突中浪费它的力量。 ";
			link.l1 = "谢谢你! 我只会在完全被敌人包围时使用它。 ";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "现在走吧。 警告你的兄弟们不要侵犯这些神圣密室的宁静。 美洲虎战士对白脸人毫不留情, 不会给他们任何喘息之机。 ";
			link.l1 = "再见, 首领。 ";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}