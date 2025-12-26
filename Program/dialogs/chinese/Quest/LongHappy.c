// 人物对话关于任务《长久与幸福》
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
		
		// 港口的信使船长
		case "cureer":
			dialog.text = "德.莫尔先生, 太幸运了! 我找了你好几个月了! ";
			link.l1 = "亲爱的, 我不买假地图。 不可靠的信息和自制朗姆酒 - 谢谢! 或者你是赏金猎人? 现在我的人头值多少钱? ";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "哦, 先生, 我... 我不做垃圾买卖也不杀人 - 别碰剑, 你不需要它, 我没有恶意! 一切都很平常 - 我是信差船的船长。 我分发邮件。 而给你, 我有一封重要的信件! ";
			link.l1 = "一封信? 请问发件人是谁? ";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "一位修道院院长把它交给我, 并要求亲手交给德.莫尔船长。 我已经失去找到你的所有希望, 想把它留在圣皮埃尔的港口办公室, 但太幸运了 - 你在这里! ";
			link.l1 = "是的, 我在这里, 我等着 - 把信给我。 ";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "有一个问题... 修道院院长说送货费由收件人支付。 所以你欠九千二百比索。 ";
			link.l1 = "为了这么多钱, 它应该在公海上连早餐咖啡一起送到我的船舱! 你可以把信留给自己。 ";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "我为什么不做邮件投递呢? 这比当海盗还赚钱! 给你银币, 亲爱的, 把信封给我。 ";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "和你交易很愉快! 本诺伊修道院院长向你致以最美好的祝愿! 再见, 德.莫尔先生! ";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "如你所愿。 我会把信封留在港口办公室。 但我警告你, 这会影响价格。 还有, 本诺伊修道院院长向你致以最美好的祝愿。 ";
			link.l1 = "本诺伊修道院院长的信? 你为什么不一开始就说! 这一定很重要! ";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "那就去港口负责人那里取吧。 别忘了提前贷款。 再见, 德.莫尔船长。 ";
			link.l1 = "我知道海盗比你更真诚。 祝你好运, 亲爱的。 ";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// 圣地亚哥的西班牙军官
		case "spa_officer":
			dialog.text = "神圣的父亲, 你今天比平时早。 请, 你的护卫在等你。 而你, 德.莫尔先生 - 文森托神父发现你在城里, 恳请你和他一起吃晚餐。 ";
			link.l1 = "恐怕宗教裁判官将独自用餐。 我希望这不会让他的胃口变差。 而且本诺伊修道院院长也会缺席。 你知道我是谁, 所以我建议你.让我们毫无冲突地通过, 并向帕洛蒂神父转达我最美好的祝愿。 ";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // 进行荣誉和知名度的计算
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "是的, 我听说了很多关于你的事, 而且我有明确的指示, 如果你固执己见, 不要把城市变成血泊。 你可以通过。 但文森托神父会... 不满意。 记住这一点。 ";
				link.l1 = "你做得很理智, 先生。 我会以某种方式挺过宗教裁判官神父不满意带来的心痛。 祝你晚上好! ";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "是的, 我听说过你... 很多有趣的事情。 然而, 拒绝这样的邀请对健康有害, 先生。 就像绑架文森托神父的客人一样。 抓住他们! ";
				link.l1 = "每个人都有自己的选择。 很抱歉不得不这样。 拔剑吧, 骑士! ";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// 扬.斯文森神父
		case "Svenson":
			dialog.text = "查尔斯, 恭喜! 你知道 - 我一直喜欢你, 海伦对我来说就像女儿一样, 所以我为你们俩高兴。 该死的... 在教堂里掉眼泪是我一直想要的, 我是变老了还是怎么了? ";
			link.l1 = "一切都很好, 扬, 我在祭坛附近差点哭了。 大概是熏香的缘故? ";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "对, 樟脑, 该死的。 我一直在想 - 为什么我的眼睛刺痛, 鼻子发痒! 好吧, 我们在夏普敦再谈, 拥抱格拉迪斯, 然后去见其他人。 他们的表情就像我们在签署《威斯特伐利亚和约》。 ";
			link.l1 = "谢谢你来这里, 扬。 我很高兴见到你, 这对海伦意义重大。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 伊斯莱.特索罗的扬.斯文森
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "你终于来了, 查尔斯! 我的护卫舰几乎比你早到一天 - 相当值得骄傲。 ";
			link.l1 = "欢迎你, 扬, 但格拉迪斯和你妻子在哪里? ";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "我让格拉迪斯乘商船回蓝维尔了 - 她不赞成所有这些时髦的派对。 乔安娜没能来 - 哦, 我在马提尼克没有时间告诉你! 想象一下 - 在我年老的时候, 我将成为一个合法的父亲, 怎么样? 看, 如果你快点, 我们的后代几乎会同龄, 哈哈哈! ";
			link.l1 = "扬, 我恭喜你, 这是好消息! 我们应该为此干杯! ";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "当然! 但首先, 为你和你的另一半干杯! 嘿, 你们在那里, 闭嘴! 老森林魔鬼必须发表演讲! \n咳咳... 所以, 我们亲爱的德.莫尔先生和夫人... 去他的! 我不能这样说话! 查尔斯, 海伦 - 你们俩对我来说就像自己的孩子, 我知道这个房间里没有人不为你们的结合感到高兴! 所以让我们干杯, 我的兄弟们, 为我们忠实朋友的幸福, 为他们帆船上的顺风, 为命运女神的爱, 就像他们对彼此的感情一样强烈! 干杯! ";
			link.l1 = "干杯! 谢谢, 扬... 哦, 这朗姆酒比平时烈多了... 内森在里面混了什么? ";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "我不知道, 但它确实很烈。 老霍克通常是饮料专家。 来吧, 去见其他人, 我需要为一百个渴望畅饮的灵魂调制饮料。 ";
			link.l1 = "森林魔鬼倒饮料 - 这样的景象! 谢谢你亲自组织派对。 我一定会回来的, 一旦我见完所有人 - 也许, 有人需要帮助。 ";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "一切都好吗, 查尔斯? ";
			link.l1 = "完美, 扬! ";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "你终于来了! 马提尼克的情况如何? 你觉得你的生活永远改变了吗? ";
			link.l1 = "它改变得更早, 扬。 但一切都进行得异常顺利。 乔安娜和... ";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "海伦? 女孩一知道我们在做什么就起航了, 朝着地平线驶去。 她向你传达了各种热烈的祝贺, 但仍然... 你伤了她的心, 哦, 你真的做到了。 不过, 一切都会好的, 只是年轻而已。 ";
			link.l1 = "嗯, 心之所向, 你明白的。 ";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "我明白。 好吧, 乔安娜没能来, 想象一下 - 在我年老的时候, 我将成为一个合法的父亲, 怎么样? 看, 如果你快点, 我们的后代几乎会同龄, 哈哈哈! ";
			link.l1 = "扬, 我恭喜你, 这是好消息! 我们应该为此干杯! ";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "当然! 但首先, 为你和你的另一半干杯! 嘿, 你们在那里, 闭嘴! 老森林魔鬼必须发表演讲! \n查尔斯和玛丽, 整个兄弟会现在都在为你们举杯! 真正朋友的幸福让任何海狼的灵魂都感到愉悦, 几乎和西班牙黄金的辉煌一样, 哈哈! 航行顺利, 愿顺风伴随你们的家庭旅程! 干杯! ";
			link.l1 = "干杯! 谢谢, 扬... 哦, 这朗姆酒比平时烈多了... 内森在里面混了什么? ";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "我不知道, 但它确实很烈。 老霍克通常是饮料专家。 来吧, 去见其他人, 我需要为一百个渴望畅饮的灵魂调制饮料。 ";
			link.l1 = "这个酒馆肯定需要改名 -'森林魔鬼本人曾站在柜台后面'! 谢谢你, 扬, 我一定会回来的, 一旦我见完所有人 - 也许, 有人需要帮助。 ";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "你好吗, 查尔斯? 婚礼怎么样? ";
			link.l1 = "非常温馨, 扬。 我很高兴我们能把大家都带到这里。 看来霍克的朗姆酒桶开始见底了, 不是吗? ";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "是的, 它们是! 所以, 是时候打开你带来的东西了。 还有一件事 - 那些一开始帮助我的人在后面的房间里喝得太醉了。 你似乎还站着, 新郎 - 你能拿一箱雪利酒来吗? ";
			link.l1 = "当然, 告诉我去哪里。 也许我会在路上找到几个清醒的头脑来帮助我。 不过, 我的大多数人可能已经烂醉如泥了。 ";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "葡萄酒堆在造船厂下面的地窖里, 还记得吗? 霍克说要放在远走廊里,'留到假期'- 他说。 他还说那里有完美的温度和湿度, 说那将是一个完美的酒窖。 嗯, 他是个大牌。 ";
			link.l1 = "他做了正确的决定, 扬。 我会去, 但首先, 告诉我 - 你见过我妻子吗? ";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "她和丹妮去了某个地方。 让女孩们谈谈, 查尔斯, 我们必须开始真正的派对。 去地窖, 而我处理食物。 因为闻起来很快我们就要吃煤而不是羊排了! ";
			link.l1 = "好吧, 去救肉, 我会带我们的酒。 ";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "查尔斯, 内森, 发生了什么事, 你们开始醉酒打架了? ! ";
			link.l1 = "不, 扬, 我们在地下室又一起与一些武装快艇战斗。 我们解决了他们, 但他们只是侦察兵 - 主力部队就在我们后面! ";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "中队? 你在说什么? ! 马库斯, 过来! 查尔斯, 来吧, 告诉我们一切。 ";
			link.l1 = "就像我说的: 造船厂下面的地牢里有一些混蛋。 装备精良。 内森和我与他们战斗, 奇迹般地把所有人都放倒了。 但路上还有更多 - 我听说, 其中一个被派去寻求帮助。 是的, 其中一个记得某个雅克。 ";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "我认得他们的脸... 这个, 还有躺在门边的那个混蛋。 他们是‘好心人’雅克的暴徒。 不记得他们的名字, 但我确定。 ";
			link.l1 = "所以这是巴尔巴宗的错? 他疯了还是怎么了? ! ";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "我不知道, 但似乎‘好心人’决定利用这个机会, 在兄弟会的男爵中进行一次彻底的重组。 ";
			link.l1 = "在这种情况下, 我希望他自己出现 - 我一直梦想着在他身上打几个洞。 混蛋, 毁了我的婚礼, 想想看! 我们走吧, 到街上! 我们会为我们的客人准备一个适当的欢迎仪式! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "这是我们疲惫的英雄! 哈, 查尔斯, 那是什么! 雅克, 这样的老鼠! 看他如何安排一切 - 他几乎成功了! ";
			link.l1 = "是的, 也许, 当我们解决了杰克曼之后, 我们应该杀了那个混蛋。 然而, 一切都结束了。 巴尔巴宗死了。 ";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "嗯, 不能说一切都结束了 - 我们的生活还在继续! 虽然我觉得自己完全毁了。 我太老了, 不能从着火的船上跳进海里, 游一个小时到岸边, 还要提防鲨鱼。 我希望我们还有一些朗姆酒... ";
			else dialog.text = "嗯, 不能说一切都结束了 - 我们的生活还在继续! 该死的, 我觉得自己年轻了十岁! 我很久没有那样战斗了! 我希望你的朗姆酒和葡萄酒库存没有在混乱中被盗 - 我们需要为此好好喝一杯! ";
			link.l1 = "是的, 我也想喝, 但首先我必须检查住所, 我不知道你是否被告知... ";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "是关于你的印第安伙伴吗? 是的, 我听说了, 怎么发生的? ";
				link.l1 = "他跳起来掩护我妻子和丹妮尔免受一个混蛋的子弹。 我们应该走了, 我在路上告诉你。 ";
			}
			else
			{
				dialog.text = "是关于内森吗? 是的, 我听说了, 只是不明白怎么发生的? ";
				link.l1 = "他跳起来掩护我们的妻子免受一个混蛋的子弹。 我们应该走了, 我在路上告诉你。 ";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "保持坚强, 查尔斯。 我真的为你的兄弟们感到难过。 今天, 许多好人走了, 对于他们每个人, 在地狱里, 巴尔巴宗的锅炉里会加入更多的油。 ";
				link.l1 = "这没有意义... 该死的! 很难, 扬... 我已经失去了朋友, 但我无法习惯。 我不知道我是否还能继续。 ";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "那么那个安静的医生家伙? 对不起, 查尔斯, 真诚地。 他是个好人。 ";
					link.l1 = "是的, 扬, 我也是。 但是, 恐怕科学界的损失远不止我。 他是个天才... 像他们所有人一样复杂, 但是... 该死的... ";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "你的印第安人";
					else sTemp = "内森";
					dialog.text = "嗯, 似乎结束了。 今天, 许多好人走了, 对于他们每个人, 在地狱里, 巴尔巴宗的锅炉里会加入更多的油, 但"+sTemp+"会没事的, 这是最主要的。 ";
					link.l1 = "你说得对, 扬, 这让我如释重负。 其他男爵怎么样? 他们没事吧? ";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "雅克.巴尔巴宗的最后污秽。 你说得对, 如果我们之前杀了他, 一切可能会不同。 ";
			link.l1 = "但后悔过去有什么用? 过去无法改变。 其他男爵怎么样? 每个人都幸存下来了吗? ";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "没有人能习惯。 我们为我们的兄弟们干杯好吗? 我在桌子上找到一瓶, 它奇迹般地在这场混乱中幸存下来。 ";
			link.l1 = "倒吧, 我... 该死的... 一千次诅咒! ";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "告诉我关于他们的事。 这个医生看起来很聪明。 他表达得如此明智。 ";
			link.l1 = "他确实如此。 但是, 恐怕科学界的损失远不止我。 他是个天才... 像他们所有人一样复杂。 奇迹的主人! ";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "关于印第安人? 你在哪里找到他的? ";
			link.l1 = "在瓜德罗普的监狱里救了他, 几乎在我到达后立即。 真的很有趣和愚蠢的故事。 所以, 他和我在一起。 他选择了, 我给了他自由, 但他留在我身边 - 我救了他, 他认为他欠我直到生命的尽头。 沉默寡言, 穿着奇怪, 但比任何骑士都忠诚, 他也有天赋, 他可以在任何距离用滑膛枪击中空中的硬币。 ";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "嗯, 他偿还了你的债务, 我能说什么。 从那个混蛋手中救了"+sld.name+"和丹妮尔。 在我看来 - 这是这样一个勇敢的战士应得的结局。 ";
			link.l1 = "是的, 扬。 让我们为倒下的人干杯... 愿他们找到安宁。 其他男爵怎么样? 他们没事吧? ";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "这个夜晚让我们付出了沉重的代价。 我甚至不知道兄弟会何时能从这场屠杀中恢复过来。 ‘好心人’完美地选择了时间和地点进行打击。 他几乎成功了 - 再一点, 一切都结束了。 但我们的损失比可能的要少得多。 ";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "鲨鱼在医务室, 他的船受到二十四磅的 volley。 他飞过船舷, 断了几根肋骨, 吞下了海水, 但他还活着, 几天后就会恢复如初。 ";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // 曾是旺桑
			else link.l1.go = "Svenson_36"; // 到结束
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "伯纳德只是受了几处轻伤 - 他在保卫海岸并清除地下墓穴。 现在, 他在港口, 为伤员组织医院, 为不幸的人组织葬礼。 ";
			else dialog.text = "伯纳德不走运, 他在清除地下墓穴袭击后的房屋时, 在仓库里遇到了一群这些混蛋。 他中了一枪, 直接击中头部。 真遗憾, 他是个好船长... 泰雷克斯发现后会很生气。 ";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // 到结束
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "伯纳德只是受了几处轻伤 - 他在保卫海岸并清除地下墓穴。 现在, 他在港口, 为伤员组织医院, 为不幸的人组织葬礼。 ";
			else dialog.text = "伯纳德不走运, 他在清除地下墓穴袭击后的房屋时, 在仓库里遇到了一群这些混蛋。 他中了一枪, 直接击中头部。 真遗憾, 他是个好船长... 泰雷克斯发现后会很生气。 ";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // 到结束
		break;
		
		case "Svenson_36":
			dialog.text = "关于霍克你知道。 丹妮至少一个月内不会允许他离开岛屿, 这是肯定的。 他有一件事在我们脑海中... 哦, 好吧。 ";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "马库斯一如既往地好。 他一上岸, 就立即开始拷问那些忽视所有这些污秽的哨兵的灵魂。 他仍然设法指挥镇上的秩序恢复。 铁人, 不然。 ";
				link.l1 = "铁更软。 我猜, 我们的男爵是由科学尚未知晓的金属制成的, 哈哈! ";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "只有马库斯不清楚, 他的船被登船, 但幸存者声称他设法跳海了。 我已经派长艇去搜索海湾。 我希望我们的男爵足够坚强, 不会轻易放弃。 ";
				link.l1 = "那很糟糕, 但为他哭泣还为时过早, 马库斯不会那么轻易地放弃我们。 让我们等待搜索结果。 ";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "马库斯在他的船沉没后游到了岸边。 嗯, 你知道, 泰雷克斯不是那种会因为这样的小事而淹死的人。 现在他在镇上的某个地方。 可能在拷问那些忽视所有这些污秽的哨兵的灵魂。 铁人, 不然。 ";
				link.l1 = "铁会沉没。 我猜, 我们的男爵是由科学尚未知晓的材料制成的, 哈哈! ";
			}
			else
			{
				dialog.text = "马库斯一如既往地好。 他一上岸, 就立即开始拷问那些忽视所有这些污秽的哨兵的灵魂。 他仍然设法指挥镇上的秩序恢复。 铁人, 不然。 ";
				link.l1 = "铁更软。 我猜, 我们的男爵是由科学尚未知晓的金属制成的, 哈哈! ";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "就这样。 嗯, 情况可能更糟。 甚至你的婚礼, 查尔斯, 也出来了... 战斗。 重要的是你们俩都还活着。 一般来说, 一个小建议... 爱... 而且你不敢放弃为它而战! ";
			link.l1 = "谢谢, 扬。 感谢你们所有人... 我必须承认, 我忘了我们是以庆祝开始的。 ";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "所以, 这是一个提醒。 ";
			link.l1 = "是的, 那是一个... 疯狂的派对。 ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "哦, 是的, 当然, 等一下。 有件事 - 你好像有一个印第安人跟着你, 总是在你身边或环顾四周, 好像有人在瞄准你。 穿着滑稽, 在人群中非常显眼。 ";
			link.l1 = "是的, 提钦吉图, 在混乱开始时他就消失了, 老实说, 我开始担心了。 你知道什么吗? ";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "好像是。 我们的酒保在吵吵嚷嚷说他的侄女被绑架了, 据说是在袭击前。 他说他们看到她和某个印第安人在一起, 他沿着镇东边的海岸把她扛在肩上。 我没有在‘好心人’的败类中注意到任何印第安人, 但听到时我想起了你的, 所以我什么也没说。 你应该去, 找他什么的, 直到他遇到麻烦。 因为酒保威胁说如果他先找到他就杀了他。 他是个好人, 但为了他的侄女, 他会拧下任何脑袋。 ";
			link.l1 = "是的, 我知道这种人, 别担心, 谢谢, 扬, 我会马上去找他。 ";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "嗯, 总的来说, 像这样的事情... 对不起, 我不擅长演讲。 现在更糟了 - 这个夜晚把每个人都榨干了。 我们都应该至少休息一天 - 然后我们将决定如何进行。 ";
			link.l1 = "你说得对, 扬。 我应该走了, 我需要清醒一下头脑。 ";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "看起来不错, 查尔斯。 睡得好吗? ";
			link.l1 = "是的, 我们在镇外得到了一间舒适的房子。 我甚至以为我梦见了昨天发生的所有疯狂事情。 而你在这里, 扬, 你看起来很糟糕。 还发生了什么? ";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "哦, 不, 没什么, 我只是还没睡。 你知道... 在发生了这一切之后整理城市是一项艰巨的任务。 ";
			link.l1 = "丹妮和内森怎么样? 大家都在哪里? ";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "在休息。 不要打扰他们, 丹妮警告大家她今天带着枪上床... 多德森在海上, 出发寻找更多船只来保卫岛屿, 这样就不会再发生这种情况, 其他人在岛的北部埋葬逝者。 ";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "马库斯还没有找到, 但我们可以处理, 别担心。 你为我们大家做了这么多, 所以不要麻烦自己。 泰雷克斯迟早会回来 - 我们会找到他。 ";
			else dialog.text = "马库斯在这里完成后, 乘坐某人的小帆船前往伊斯帕尼奥拉岛。 有必要解决巴尔巴宗死后出现的一些问题。 他向你和你的妻子致以问候和最美好的祝愿。 ";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "嗯, 兄弟会经受住了这次打击。 很快, 我们将比以往任何时候都更强大地崛起。 ‘好心人’和杰克曼动摇我们的团结太久了, 现在他们走了, 我的心感觉到 - 我们会让加勒比海不止一次地退缩。 对于那些不喜欢法律和国王的人来说, 黄金时代即将到来, 记住我的话。 ";
			link.l1 = "那太好了。 我不确定我是否还能承受旧世界。 我从没想过当我来到这里时, 我会爱上大海的自由, 这些疯狂的日落和日出的颜色, 我会找到世界上最好的女人和... 我愿意以生命相托的朋友。 ";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "嗯, 你知道方向, 只要下定决心。 在我们家里, 你总是受欢迎的。 ";
			link.l1 = "谢谢, 扬。 这对我意义重大。 ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "但首先, 还有一件重要的事情。 查尔斯, 当你睡觉时, 我们聚在一起, 我们决定\n既然巴尔巴宗死了, 兄弟会需要一位新男爵。 由于我们这里有明显的多数, 并且决定是一致的, 所以就是这样。 恭喜 - 你是勒弗朗索瓦的新男爵。 但是等等... 我明白 - 你是一个世俗的人, 你没有时间在这个好地方处理事务, 所以我们在那里安排了一个值得信赖的人, 你想做什么就做什么。 只要记住 - 你现在在兄弟会中有发言权。 ";
			link.l1 = "扬, 我... 我无言以对... 这是巨大的荣誉, 我甚至不知道... ";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "来吧! 你在和泰雷克斯在一起时已经完美地证明了自己, 然后在Sharp遗产的所有故事中也是如此。 你是上帝自己的祝福。 对你来说, 没有什么会改变 - 按计划行事, 在你不在的时候, 你的人将负责所有事务\n有一个有前途的家伙扬.大卫, 他是海盗之一。 法国人, 诚实的家伙, 有才华的头脑, 并且知道如何使用它, 就像你一样。 但我需要一些时间才能找到他 - 似乎他被西班牙人俘虏了, 但这可以解决, 别担心。 我会确保他一适应业务就把你的部分寄给你。 ";
			link.l1 = "我真的没想到一切会是这样。 好吧, 既然你已经决定了, 那就这样吧。 海盗男爵查尔斯.德.莫尔! ";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "男爵万岁! 如果有人配得上这个名字, 那应该是你。 自豪地佩戴它, 别忘了 - 你现在是我们中的一员, 无论你穿多么漂亮的制服, 在这里, 就在它下面, 跳动着一颗真正海盗的心。 ";
			link.l1 = "我不知道, 也许你夸张了... 但我会尽我所能来证明你的信任是正确的。 ";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "你现在打算做什么? 回到欧洲, 回到你父亲那里, 介绍他和你的妻子? ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "是的, 但首先我必须和某人告别... 你知道我的意思。 ";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "也许不会那么快。 我会再一次航行穿过群岛, 我想最后一次呼吸这种自由的空气。 ";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "嗯, 你有船, 你可以随时回家。 ";
			link.l1 = "我希望如此。 谢谢, 扬, 谢谢你们所有人, 再见, 我的老朋友! 向霍克斯和鲨鱼问好! ";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "他们值得";
			else sTemp = "他值得";
			dialog.text = "是的, 很难, 但我们必须这样做。 去海边? ";
			link.l1 = "不, 我会航行到安提瓜。 "+sTemp+"在一个成为我们家一段时间的地方安息。 ";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "也替我多说几句好话。 别担心 - 从现在开始我们可以自己处理。 一切都会好起来的。 ";
			link.l1 = "谢谢, 扬。 很快见, 我的老朋友! 向霍克斯和鲨鱼致以最美好的祝愿! ... 好吧, 就去安提瓜。 ";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// 格拉迪斯
		case "Gladis":
			dialog.text = "年轻人, 你今天在我眼中更加成长了。 你为海伦做了这么多, 没有什么感激的话语足够。 我只希望你能继续照顾她。 如果她的父亲还活着, 看到这一切, 他会多么高兴... 哦, 对不起。 ";
			link.l1 = "没关系, 格拉迪斯。 你穿越群岛来支持海伦这一天。 我们俩都非常感谢你和扬的来访, 谢谢。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 弗尔热 - 玛丽的父亲
		case "forge":
			dialog.text = "德.莫尔先生, 请原谅我的熟悉, 但我会这样说 - 查尔斯, 我的朋友, 我真诚地为你高兴! 如果我能为你或你的新娘做些什么, 只要说出来! ";
			link.l1 = "谢谢你, 男爵, 我很高兴, 我父亲想要作为嫁妆的葡萄园, 我想我可以赎回自己 - 幸运的是, 我在新世界期间的财务状况有了很大改善。 ";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "是的, 我想你几乎可以负担得起任何你想要的东西, 查尔斯。 对不起, 但我将作为代表父亲做出我的贡献 - 今天, 我要给我财政部长的好朋友写信。 你的天选之人将被授予贵族头衔, 我想, 我们会为她找到一些好的庄园, 比如说在加斯科尼, 在那些因债务被没收的庄园中, 并追溯分配给她。 所以没有人会敢说德.蒙佩尔骑士找到了一个地位低下的妻子! ";
			link.l1 = "我不认为我关心这样的流言蜚语, 但谢谢, 男爵。 不过, 你不应该";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "我不止应该! 现在去吧, 查尔斯, 把你的注意力分享给其余的客人。 再一次, 接受我最诚挚的祝贺! ";
			link.l1 = "我和我的妻子谢谢你。 再见, 男爵。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 弗尔热 - 总督的父亲
		case "forge_3":
			dialog.text = "德.莫尔先生, 请原谅我的熟悉, 但我会这样说 - 查尔斯, 我的朋友, 我真诚地为你高兴! 如果我能为你或你的新娘做些什么, 只要说出来! ";
			link.l1 = "谢谢你, 男爵, 但你已经为我做了很多。 你回应了邀请, 这对我们来说就足够了。 ";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "我怎么能不回应呢, 查尔斯! 但是听着 - 我想送给你和你美丽的新娘一份有价值的礼物, 但我想不出任何你不能用金钱或剑为自己得到的东西。 因此, 我会给我在巴黎的财政部长朋友写信, 等你到达欧洲时, 你将等待签署提升德.蒙佩尔名字为德.蒙佩尔男爵头衔的皇家法令! 不, 一句话也别说, 这是我能为你做的最少的事。 ";
			link.l1 = "我甚至不知道该说什么, 男爵... 父亲会很高兴的。 真诚地感谢你。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 弗尔热客人
		case "forge_5":
			dialog.text = "查尔斯, 请接受我诚挚的祝贺! 你的天选之人简直是个奇迹! 我想, 今天, 殖民地时尚受到了强烈的... 新方向的冲击。 你的创意一直让我着迷! 愿你和你的美丽另一半永远幸福! ";
			link.l1 = "谢谢你, 男爵。 你来访是我们的荣幸。 ";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "我的朋友, 我怎么能缺席呢? 我们一起经历了很多, 我很自豪地称你为我的朋友, 查尔斯。 记住 - 我的门永远为你敞开, 无论发生什么。 ";
			link.l1 = "德.蒙佩尔家族的门也将永远为你敞开, 男爵。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 普安斯玛丽的父亲
		case "puancie":
			dialog.text = "查尔斯, 我的朋友, 这是一个非常重要的日子, 我很高兴你邀请我与你分享。 你和我走过了漫长而艰难的道路, 成为小姐的代表父亲... 请原谅我 - 德.莫尔夫人, 这对我来说是一种荣誉, 相信我。 我衷心祝愿你幸福! \n请告诉我你什么时候去欧洲 - 作为你天选之人的代表父亲, 我会把所有必要的结婚礼物寄给你父亲。 相信我, 没有人会说德.蒙佩尔骑士的新娘贫穷或不配! ";
			link.l1 = "如果我可以问, 在德.蒙佩尔庄园以北几英里处, 有好的葡萄园, 它们属于拉布里涅家族, 我... ";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "一句话也别说, 我的朋友, 一句话也别说! 我会立即给我在里昂的授权代表写信 - 你到达时, 这些葡萄园将被送给你的天选之人。 ";
			link.l1 = "谢谢你, 骑士。 你是对的 - 我们的... 友谊, 经历了... 很多。 但是, 我真的很高兴你与我们分享了这一天。 再见, 再次感谢! ";
			link.l1.go = "Guests_block";
		break;
		
		// 普安斯总督的父亲
		case "puancie_2":
			dialog.text = "查尔斯, 我的朋友, 这是一个非常重要的日子, 我很高兴你邀请我与你分享。 我们走过了漫长而艰难的道路, 今天在你的婚礼上作证是我的荣幸。 我衷心祝愿你幸福! 让我知道你什么时候去欧洲 - 我会给你父亲送去年合适的结婚礼物。 ";
			link.l1 = "这没有必要, 骑士。 感谢你回应我的邀请。 ";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("你得到了宝石");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "正如我所说 - 这是我的荣幸! 但是等等, 我的朋友, 我想在这个场合送给你一些东西 - 我相信这会让你和你的天选之人都高兴。 来自我们新圭亚那矿山的美丽石头 - 给它们挑选一个体面的框架, 德.莫尔夫人即使在皇家招待会上也会光彩照人! 当然, 如果你说服她穿裙子... ";
			link.l1 = "哦, 你真的不应该, 骑士。 再次感谢你。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 普安斯客人
		case "puancie_4":
			dialog.text = "查尔斯, 我的朋友, 让我祝贺你! 我们走过了漫长而艰难的道路, 我真诚地很高兴今天在这里。 我们的主是见证 - 你值得拥有你的幸福! 保持它并保护它 - 祝你未来许多幸福的岁月! ";
			link.l1 = "谢谢你, 骑士, 我和我的妻子非常感激。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 法德伊父亲
		case "fadey":
			dialog.text = "查尔斯, 这样的庆祝活动, 还有多少重要的人! 让我衷心祝愿你幸福安康, 还有孩子带来的快乐! 正如我们所说 -'gor'ko'! ";
			link.l1 = "谢谢你, 法德伊, 你同意来是我的荣幸。 ";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "但是, 我不太明白为什么有这么多人, 好像我们不是在结婚, 而是在达成一笔大交易, 而且这里的啤酒和伏特加还不够我的口味... 哈哈! 好吧, 我在开玩笑, 查尔斯, 你为什么脸色完全苍白? 给我一个拥抱, 你这个已婚船长! ";
			link.l1 = "哇... 法德伊, 你像熊一样强壮! ";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("你得到了三把波斯军刀");
			PlaySound("interface\important_item.wav");
			dialog.text = "等等, 查尔斯, 别走 - 客人来参加婚礼没有礼物是不值得的。 这里, 拿着它们。 我知道 - 你试图找到所有这些刀片, 有些, 你显然喜欢。 所以接受它们 - 把它们挂在家族庄园里, 记住法德伊.莫斯科维特的好话! ";
			link.l1 = "这是一份真正的礼物! 谢谢你, 法德伊。 这些确实是很棒的武器, 它们将在德.蒙佩尔庄园占据应有的位置, 我保证! ";
			link.l1.go = "Guests_block";
		break;
		
		// 法德伊客人
		case "fadey_3":
			dialog.text = "查尔斯, 这样的庆祝活动, 还有多少重要的人! 让我衷心祝愿你幸福安康, 还有孩子带来的快乐! 正如我们所说 -'gor'ko'! 给我一个拥抱, 你这个已婚船长! ";
			link.l1 = "哇... 法德伊, 你像熊一样强壮! ";
			link.l1.go = "Guests_block";
		break;
		
		// 普罗斯珀.特鲁巴尔
		case "Prosper":
			dialog.text = "查尔斯, 我不能错过, 我衷心祝贺你和你的天选之人! 祝你幸福! 你知道, 几个月前我把女儿嫁给了一个好人, 彼此相爱, 但老实说, 我很沮丧那不是你... 好吧, 好吧... 我在说什么 - 恭喜! 愿你永远幸福! ";
			link.l1 = "谢谢, 普罗斯珀, 我很高兴你来了。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 提钦吉图
		case "Tichingitu":
			dialog.text = "恭喜, 船长! 一个奇怪的仪式, 但很漂亮 - 提钦吉图喜欢它。 虽然, 船长应该只是绑架他的女人, 并向她的亲戚发送赎金。 ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "嗯, 在某种程度上, 我做到了, 这只是一种形式。 谢谢你, 我的朋友! ";
			else link.l1 = "嗯, 在某种程度上, 我做到了, 这只是一种形式。 谢谢你, 我的朋友! 你和我将在夏普敦谈更多 - 那里将少很多正式, 多很多真诚的乐趣, 我保证! ";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "又喝火水? 提钦吉图不能说他喜欢它。 也许, 庆祝登船会更好, 或者至少围着篝火跳舞? ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "我希望在结束前不会有围着篝火跳舞, 我宁愿不登船。 好吧, 耐心点 - 就剩一点了, 我们马上搬到酒馆去。 ";
			else link.l1 = "恐怕在结束前会有围着篝火跳舞, 我宁愿不登船。 好吧, 耐心点 - 就剩一点了, 我们马上航行到夏普敦。 ";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "船长, 再次恭喜! 提钦吉图比上一次更喜欢这个庆祝活动。 船长知道如何选择朋友 - 这里有更多的真诚, 更少的虚伪和假发。 ";
			link.l1 = "谢谢你, 我的朋友! 只是不要喝火水 - 这里很难。 ";
			link.l1.go = "Tichingitu_4";
			link.l2 = "谢谢你, 我的朋友! 我们喝一杯好吗? 我知道你不喜欢, 但今天, 你应该试试! ";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "提钦吉图不喜欢火水, 但如果船长坚持, 今天可以试试。 为你的幸福和你的女人! ";
			link.l1 = "也为你, 提钦吉图! 为我们的友谊和忠诚! ";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "不错的派对, 船长。 ";
			link.l1 = "我很高兴你满意。 ";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "船长, 出来看星星? 夜晚有望非常美丽。 提钦吉图喜欢海上的夜晚。 非常宁静。 ";
			link.l1 = "很高兴看到你还站着, 我的朋友! 我和纳撒尼尔需要你的帮助 - 酒馆里的人没酒了, 我们需要从造船厂下面的仓库里拿几箱饮料。 ";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "带路, 船长。 提钦吉图像往常一样跟着你。 ";
			link.l1 = "好吧, 我们走! ";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "船长, 有人, 他们有武器, 提钦吉图听到他们武器的咔嗒声, 而且声音每秒都在变大。 我不喜欢。 我们躲起来吧。 ";
			link.l1 = "来吧, 伙伴 - 这是夏普敦, 在这里甚至去洗手间的人都带着手枪。 嘿, 内森... 嗯, 妈的! 那个瓶子不见了。 如果这样下去, 你会打碎所有的瓶子! 站起来, 该死的! 哈哈! ";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "船长... 你... 提钦吉图的头像暴风雨中的桅杆一样被破坏了。 发生了什么事? ";
			link.l1 = "我想问你同样的问题! 你这段时间在哪里? ! ";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "提钦吉图一小时前因为这个女孩的哭声醒来。 她几乎赤身裸体地沿着海滩跑, 尖叫着什么绑架者和野蛮人... 但这里除了我们没有其他人。 你有水吗? 不再是火的了, 提钦吉图现在讨厌它? ";
			link.l1 = "某处有一个烧瓶, 如果我没有在战斗中失去它... 给你。 你是怎么做到的? 她的叔叔, 当地的酒保, 正在寻找绑架他侄女的印第安人, 并威胁要扯下他羽毛覆盖的空脑袋。 你认为他在说谁? ";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "提钦吉图想起来了。 她在酒馆里帮助森林魔鬼准备婚礼。 我们和你喝了火水, 提钦吉图想要更多。 然后, 这个女人... 她很可爱, 而且... 船长, 我想我想起来了! 提钦吉图想娶她... 他想造一艘独木舟, 把她带走... 仁慈的灵魂! 非常坏的人带着火水来了。 也许, 是恶魔或邪灵! 提钦吉图再也不会... ";
			link.l1 = "带走她? 造独木舟? ! 啊哈, 你是个浪漫主义者, 我的朋友... 哈哈... 哈哈哈哈哈哈... 哦, 我停不下来... 我笑个不停! ";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "船长, 提钦吉图偷了这个女人, 是的... 但是, 我们可以, 嗯... 现在不结婚吗? 她是... 大声, 像一只papagallo鸟, 而且... 不是那么漂亮。 ";
			link.l1 = "是的, 我的朋友, 玩了一整夜的女人, 早上看起来很可怜。 别担心, 英雄情人, 我们会想出办法的。 来吧, 我们必须回到夏普敦, 你错过了你的假日登船... ";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "登船? 船长之前提到过战斗。 思想仍然不服从提钦吉图。 镇上发生了什么? ";
			link.l1 = "陆地上和海上的真正战斗。 枪声响了一整夜, 我猜, 甚至在圣何塞都能听到。 然而, 你忙于另一场‘战斗’, 我可以理解一切都好... 来吧, 我在路上告诉你一切。 ";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "谢谢, 船长... 提钦吉图永远不会... ";
			link.l1 = "是的, ‘来自遥远平原的种马’你绝对不应该再喝了。 去睡吧。 我也已经站不住了。 ";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "船长, 再次恭喜! 提钦吉图比上一次更喜欢这个庆祝活动。 船长知道如何选择朋友 - 这里有更多的真诚, 更少的虚伪和假发。 ";
			link.l1 = "而且更多的火水。 顺便说一句, 你会和我喝一杯吗? 我知道你不喜欢, 但我们有不寻常的场合! ";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "提钦吉图不喜欢火水, 但如果船长坚持, 今天可以试试。 为你的幸福和你的女人! 愿你们走同一条路, 让太阳和月亮永远照耀在上面。 ";
			link.l1 = "谢谢你, 我的朋友。 为你干杯, 提钦吉图! 为我们的友谊! ";
			link.l1.go = "Tichingitu_4";
		break;
		
		// 总督们
		// 圣皮埃尔
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "伟大的... 庆祝活动, 我为你感到非常高兴, 查尔斯。 虽然, 我仍然不理解你... 把无价的玫瑰握在手中, 却把它换成... 野花。 但心之所向... 祝你幸福, 我的朋友。 愿你永远幸福! ";
				link.l1 = "在你手中的花中, 最美丽的是你对它的感觉。 没有它, 它只是一团凋谢的肉。 很高兴你进来了, 大人。 ";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "美好的一天, 我的朋友, 一个美好的场合! 接受我诚挚的祝贺! 我结过三次婚, 每次都像第一次一样颤抖, 啊, 青春... ";
				link.l1 = "先生, 你还远未衰老, 不要气馁。 谢谢你来, 雅克! ";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "等等, 查尔斯。 你误解我了, 我是真心为你高兴! 是的... 拿着。 我们共同的... 朋友, 确实要求你今天一定要拿到这个。 ";
			link.l1 = "我猜我知道这是谁给的。 谢谢你, 回头见。 ";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// 巴斯特尔
		case "BasTer_Mayor":
			dialog.text = "一场令人愉快的礼拜, 不是吗, 查尔斯? 我真心为你高兴! 我个人以及巴斯特尔的所有市民 - 向你和你... 迷人的妻子表示祝贺。 你们是很棒的一对! 愿你们永远幸福! ";
			link.l1 = "谢谢您, 大人。 很高兴您喜欢。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 太子港
		case "PortPax_Mayor":
			dialog.text = "多么精彩的仪式, 德.莫尔先生, 太精彩了! 新娘穿着这件衣服是如此... 独特。 我代表我们城市的所有居民 - 接受我最诚挚的祝贺! 祝你未来许多幸福的岁月! ";
			link.l1 = "谢谢您, 大人。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 托尔图加
		case "Tortuga_Mayor":
			dialog.text = "太可爱了 - 你和你的新娘, 德.莫尔先生, 看起来如此与众不同! 不过, 你本来就是个与众不同的人。 祝你有一个长久幸福的家庭生活。 愿你们永远幸福! ";
			link.l1 = "非常感谢您, 大人。 ";
			link.l1.go = "Guests_block";
		break;
		
		// 德奥伊里
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "为了你的婚礼, 穿越加勒比海是值得的! 船长, 代表所有英国殖民地的居民祝贺你! 你和你的新娘, 抱歉, 已经是妻子了, 是很棒的一对! ";
			link.l1 = "感谢您的来访和亲切的话语, 上校! ";
			link.l1.go = "Guests_block";
		break;
		
		// 伊斯莱.特索罗
		// 泰雷克斯
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "这个已婚的花花公子在我的海盗海滩上做什么, 嗯? 告诉我, 先生, 你把我的老朋友 - 严厉的海盗查理王子怎么样了? ";
					link.l1 = "查理王子死了, 你记得的, 马库斯... 哈哈哈过来你这个海魔鬼! 很高兴见到你! 你们在这里怎么样, 大家都到齐了吗? ";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "这个已婚的花花公子在我的海盗海滩上做什么, 嗯? 告诉我, 先生, 你把我的老朋友 - 严厉的查尔斯.德.莫尔船长怎么样了? ";
					link.l1 = "你好, 马库斯, 我也很高兴见到你! 你们在这里怎么样, 大家都到齐了吗? ";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "这个已婚的花花公子在我的海盗海滩上做什么, 嗯? 告诉我, 先生, 你把我的老朋友 - 严厉的查尔斯.德.莫尔船长怎么样了? ";
				link.l1 = "你好, 马库斯, 我也很高兴见到你! 你们在这里怎么样, 大家都到齐了吗? ";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "是的, 森林魔鬼昨天刚到, 马上就开始指挥 - 客人都到了, 庆祝活动也准备好了。 你的船在礁石附近被发现, 伙计们忍不住 - 冲进了酒馆, 很可能已经打开了霍克的那个酒桶。 快点, 也许我们还有机会喝一杯 - 内森尼尔吹嘘说那是某种特殊的朗姆酒! ";
			link.l1 = "这就对了 - 从船上直接去派对! 我等我最好的另一半, 我们马上跟上你, 马库斯! ";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "是的, 森林魔鬼昨天刚到, 马上就开始指挥 - 客人都到了, 庆祝活动也准备好了。 你的船在礁石附近被发现, 伙计们忍不住 - 冲进了酒馆, 很可能已经打开了霍克的那个酒桶。 快点, 也许我们还有机会喝一杯 - 内森尼尔吹嘘说那是某种特殊的朗姆酒! ";
			link.l1 = "这就对了 - 从船上直接去派对! 我等我最好的另一半, 我们马上跟上你, 马库斯! ";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "已婚的查尔斯.德.莫尔 - 还是不习惯... 先是斯文森, 现在是你 - 接下来呢? 马洛牧师, 还是‘好心人’雅克? ";
			link.l1 = "你忘了霍克斯。 那你呢, 马库斯? 当孤独的海狼不累吗? ";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "丹妮和内森是老情况了 - 我已经接受了, 但你让我惊讶, 没什么可说的! 不过, 森林魔鬼的学生很漂亮 - 没什么可说的, 随时准备用言语和枪, 还能应对任何风暴。 你不太可能找到比她更值得的女人。 你很幸运, 船长 - 照顾好她! ";
			}
			else
			{
				dialog.text = "丹妮和内森是老情况了 - 我已经接受了, 但你让我惊讶, 没什么可说的! 不过, 正如我听说, 你的玛丽对剑很了解, 而且显然知道如何使用它们 - 我表示敬意! 真正的战斗女友。 我告诉你一个秘密, 为了这样的女孩, 我自己也可以重新考虑我作为单身汉的信念。 你很幸运, 船长 - 照顾好她! ";
			}
			link.l1 = "我知道, 她是个奇迹, 我又一次幸福得飘飘然 - 就像我们第一次见面的那些日子! ";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "那么, 干杯! ... 为了爱情! ... 但不是驱使我们跨过门槛走向地平线的那种爱! ... 而是在门槛处等待我们的那种爱! 为了爱, 那种即使从世界尽头和黄金山也要回到它身边的爱! 与它共存并幸福! ";
			link.l1 = "干杯, 马库斯, 谢谢! ";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "干杯, 为你的婚礼伙伴! ";
			link.l1 = "谢谢, 马库斯... ";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "雅克? 这绝对不是好事... ";
			link.l1 = "马库斯, 你觉得... ";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "没时间了! 他们在门后面! 所有人, 拿起武器! ";
			link.l1 = "开始吧! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "我不记得上次在派对上这么开心是什么时候了! 还没结束呢! 你听到了吗? 外面有人在开枪! 让我们把他们的血洒在街上! ";
			link.l1 = "等等! 他们到底是谁? ! 他们到底想要什么? ! ";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// 纳撒尼尔.霍克
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "已婚的德.莫尔船长, 我很少遇到更真诚的干杯理由。 举杯吧 - 这不是普通的卷心菜饮料。 它用东印度的红茶浸泡, 并用真正的波斯香料调味! ";
			link.l1 = "我一直在想为什么我的喉咙像喝了熔化的铅一样灼烧。 好吧, 内森, 干杯... ";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "等等, 先干杯! 嘿, 先生们, 举起你们的杯子! 今天, 我们的朋友和伙伴查尔斯.德.莫尔正在步入家庭生活的道路。 接受我们最深切的哀悼... 哦, 丹妮求你了, 放下枪! 当然是恭喜! 现在, 你们是同一艘船的帆, 所以带领她穿越任何风暴, 到达最肥沃的海岸! ";
			link.l1 = "谢谢你, 内森, 真诚地。 你和丹妮尔是我们追随的榜样。 ";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "很高兴听到。 我和妻子可能不是世界上最好的夫妻, 但我们在一起很幸福, 你为我们做了这么多, 所以如果你问我, 你是我家庭的一部分, 无论何时你需要我, 我都会在这里。 要幸福, 请喝一杯! ";
			link.l1 = "那我们喝吧! 哦... 这种朗姆酒应该在宗教裁判所的武器库中占有一席之地。 该死的! 它一路燃烧... 啊! ... 呼! ... 我喜欢它! ";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "你看起来很像二十年前的我和丹妮! ";
			link.l1 = "再来一杯, 内森! ";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "什么! ? 扬派你去地窖拿酒? 我们走走, 我帮你一点, 新鲜空气也有用。 ";
			link.l1 = "但丹妮和"+sld.name+"在哪里? 扬告诉我他们去谈话了。 ";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "是的, 丹妮知道, 即使有最好的女战士在场, 也不会让幸运的先生们有足够的时间放松。 所以她们听了所有收到的赞美, 然后去了住所, 让伙计们尽情享受。 ";
			link.l1 = "那么, 我们走吧! 我已经喝了几杯, 但该死的, 现在真的该好好喝醉了! ";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//打开位置
			bDisableFastReload = true;//关闭传送
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "那么, 这是箱子。 我们能拿多少拿多少, 然后回去, 直到这个老脾气把我们锁在这里。 ";
			link.l1 = "你夸张了, 内森。 他没那么坏... 等等, 你听到了吗? ";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "扬可能找到了更多的人, 派他们来帮助我们。 该死! ";
			link.l1 = "来吧, 瓶子为幸运者破碎。 再拿一个, 我们走。 ";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//禁止战斗
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "到底发生了什么, 这些混蛋是谁? 你明白什么吗, 查尔斯? ";
			link.l1 = "我不知道, 内森, 但其中一个跑去求助了, 我好像听到更多的脚步声。 我们必须回到酒馆! ";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "我们把这些混蛋打倒了, 但海上有炮声, 你听到了吗? 我们只有两艘船的船员准备好了战斗, 在马库斯的护卫舰和扬的轻型护卫舰上。 我。 丹妮和其他人已经让我们的人上岸了 - 毕竟是婚礼 - 所以‘百夫长’号没算在内。 你的船呢? 我们必须决定做什么, 而且要快! ";
			link.l1 = "我让一半的船员上岸了, 希望其余的人是清醒的。 但首先, 我必须找到我的妻子, 确保她没事。 ";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "是的, 丹妮也不见踪影。 那我们就这样行动 - 泰雷克斯和斯文森已经冲向港口, 他们会乘船到达他们的船。 我们去住所接妻子, 其余的人 - 让他们在岸边组织防御。 你能派几个军官去你的船上召集人员吗? 那里的帮助显然不会有害。 ";
			link.l1 = "好的, 大家行动起来! 每一秒都很重要! ";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "快点, 楼上! 丹妮和"+sld.name+"一定在那里! 如果这些混蛋伤害了她们... ";
			link.l1 = "甚至不要去想! 楼上! 我们走! ";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "该死的! 你的伙伴, 他直接冲向枪口, 这样那个混蛋就不会向女孩们开枪! ";
			link.l1 = "他中了子弹... 等等, 内森... 他在呼吸! 他还活着! 该死的, 我需要吉诺! "+sld.name+", 亲爱的, 你怎么样? ";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "我们没事, 查尔斯! 我要解开她。 我听到港口的炮声 - 你和内森需要去那里, 否则巴尔巴宗会摧毁我们所有的船。 不要浪费时间! ";
			link.l1 = "我会找到吉诺, 派他来这里, 他会帮助... 他必须! "+sld.name+", 亲爱的, 待在这里, 照顾好他, 你们俩。 ";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "查尔斯, 快点! 不管你决定什么, 现在时间就是黄金! 如果雅克的船突破到岸边, 一切都将白费! ";
			link.l1 = "是的, 我知道。 该死的混蛋! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "快点, 我们没时间说话了! ";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "废话! 原谅我, 查尔斯。 我们被困在楼上, 有十几个这些混蛋... 很遗憾我没能及时赶到, 但我看到, 你以最好的方式处理了情况。 ";
			link.l1 = "我不能说这很容易, 但是, 妈的, 当我杀了这个‘好心人’时, 我得到了极大的乐趣! 是时候上岸了, 内森, 我们的人在那里等我们! ";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "是的, 我们需要去看望你的印第安男孩, 在这里结束, 然后去夏普敦。 ";
			link.l1 = "你说得对, 我跟在你后面。 ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "顺便说一句, 我们找到了马库斯! 他在货舱里, 被绑着, 失去了知觉。 ";
			link.l1 = "他还活着? ";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "他情况很糟, 但会没事的。 泰雷克斯比棺材钉还结实, 所以别担心, 他已经被转移到你的船上, 并要了一把军刀。 ";
			link.l1 = "终于有好消息了! 好吧, 让我们在这里结束, 然后回去。 ";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// 丹妮尔.霍克
		case "Danielle":
			dialog.text = "你好, 查尔斯。 让我看看你 - 变帅了, 不错! 几乎像内森, 大约十年前! 进来, 别站在门口, 大家都在等你! ";
			link.l1 = "谢谢你, 丹妮, 很高兴见到你! 我稍后会来找你和内森, 然后我们再聊! ";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "查尔斯, 坐下 - 内森和我为你高兴! 马库斯。 扬和我丈夫为你准备了一些东西 - 但礼物稍后再说。 现在, 让我祝贺你并祝你幸福! 你的天选之人简直是个奇迹! 告诉我, 你在马提尼克没能让她穿上白色连衣裙, 是吗? ";
			link.l1 = "谢谢, 丹妮。 是的, 连衣裙的事很有趣 - 我相信在上流社会, 我们的婚礼引发了许多丑闻谣言。 每个人都诚实地移开视线, 假装没有什么不寻常的事情发生。 礼仪之类的 - 但我不在乎流言蜚语, 我爱她, 这是最重要的。 ";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "你完全正确! 我也是佩着剑, 腰带后面插着两把手枪走向祭坛的。 但那是在皇家港, 甚至在它成为体面的殖民地住所之前。 那些时候很有趣, 甚至比勒瓦瑟尔统治下的托尔图加还有趣, 而且没有人感到惊讶... 嗯。 不过, 我一直在聊天 - 去见见客人, 大家都在这里等你, 只给我一个拥抱! ";
			link.l1 = "啊, 丹妮, 我怎么能拒绝你哈哈! 你甚至无法想象我和我妻子见到你们有多高兴! ";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "你们是一对美丽的夫妻, 查尔斯! ";
			link.l1 = "谢谢, 丹妮... ";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "查尔斯, 他是对的... 你别无选择。 如果‘好心人’雅克对付泰雷克斯和其他人, 我不相信他的仁慈。 你知道必须做什么。 ";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "别听他的! 如果‘好心人’决定做这种疯狂的事, 他不会放过任何人! ";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "我们没事, 查尔斯! 我会解开她。 我听到港口的大炮声, 你和内森需要去那里, 否则巴尔巴宗会像桶里的小鸭子一样把我们的船淹死。 你不应该浪费任何时间! ";
			link.l1 = "我会找到吉诺, 派他来这里, 他会帮助... 他必须, 该死的! "+sld.name+", 亲爱的, 待在这里, 照顾提钦吉图。 ";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "内森, 不!!! ";
			link.l1 = "他抓住机会, 冲向枪口为你掩护, 丹妮... "+sld.name+", 亲爱的, 你怎么样? ";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "是的, 查尔斯, 他还活着! 心脏几乎不跳了, 但他还活着! 我们该怎么办? ! ";
			link.l1 = "我们需要吉诺, 马上! 我会找到他, 派他来这里, 他会帮助... 他必须! ";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "查尔斯, 我们没时间了! 如果雅克的船突破到岸边, 一切都将白费! 我丈夫... 他做了他必须做的。 现在轮到你了。 我会和他待在一起。 你们两个应该去找到吉诺! ";
			link.l1 = "是的, 我知道。 该死的混蛋, 他会为此付出代价! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "你终于来了! 大家都好吗? ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "我们很好, 丹妮, 别担心。 雅克死了, 他的船在海底。 提钦吉图怎么样? ";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "我们很好, 丹妮, 别担心。 雅克死了, 他的船在海底。 内森怎么样? ";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "他很好! 你的意大利医生是个天才! 内森在楼上睡觉, 但根据吉诺的说法, 没有什么威胁到他。 在床上躺一两周, 喝红酒, 正如他所说‘一位对他有好感的女士的拜访’ 咳咳... 总之 - 一切都好, 你又救了我们, 查尔斯, 我该如何感谢你? ";
				link.l1 = "是内森尼尔救了我妻子和你。 我将永远为此欠他。 你无法想象听到他正在康复我有多高兴。 让他休息, 我稍后再来看你。 ";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "他很好, 子弹直接穿过了, 我们‘百夫长’号的医生就在附近。 他从所有这些混乱中躲了起来。 所以内森会活下来, 在床上躺几周 - 小麻烦! ";
				link.l1 = "丹妮, 他为我妻子和你挡了子弹, 我将永远为此欠他。 你无法想象听到他正在康复我有多高兴。 让他休息, 我稍后再来看你。 ";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "当然! 但是, 我必须离开你, 我得去我丈夫那里... 你不介意我们借用你的朋友吧? 当内森好一点, 我自己会把他带到安提瓜。 ‘百夫长’号不知怎么奇迹般地幸存下来, 她只需要招募一个新团队。 ";
			link.l1 = "好的, 丹妮, 向吉诺和内森问好。 我该走了。 ";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "当然, 查尔斯, 但是... 我有坏消息。 那个意大利人, 圭内利, 在你婚礼上的那个... 他的尸体在酒馆的一个房间里被发现。 我... 我很抱歉, 查尔斯。 ";
			link.l1 = "什么? 吉诺? ! 不! 怎么会? ";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "我不知道, 可能是那些穿过地下墓穴袭击城镇的混蛋之一。 显然, 他们躲在那里, 寻找逃跑的机会, 然后发现了他... ";
			link.l1 = "操! 不, 我不相信... ";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "对不起, 查尔斯。 这是一场该死的血战, 他不是战士... 如果你愿意, 我们会把他的尸体送到你的船上, 带他回家, 按应有的方式埋葬他。 我真的很抱歉... ";
			link.l1 = "谢谢, 丹妮。 下令把尸体装上船。 我现在该走了... 我需要... 思考。 向内森问好。 ";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "他很好! 你的意大利医生是个天才! 他在楼上的房间里睡觉, 吉诺在照顾他。 他说‘一两周后他就会好的’。 ";
				link.l1 = "好消息! 我想我现在不能去看他? ";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "我很抱歉, 查尔斯。 我找到了我们‘百夫长’号的医生, 但他无能为力... 你的朋友几小时前去世了。 ";
				link.l1 = "提钦吉图? ! 不! 我不相信!!! ";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "不, 意大利人严格禁止打扰他, 让他休息, 吉诺在所有的担忧后也应该休息。 当我们发现一切都会好起来时, 我甚至告诉"+sld.name+"出去散步\n还有一件事... 你的朋友, 他为我挡了子弹。 我甚至不知道如何感谢他, 告诉他从现在起他也是我们家庭的一部分, 而你 - 你又救了我们, 查尔斯! ";
			link.l1 = "结果好就一切都好, 丹妮。 去内森那里, 他在等你, 我会在这里休息一下, 找找我的"+sld.name+"。 ";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "对不起, 我做了我所能做的, 还有"+sld.name+"也是。 他为我们挡了那颗子弹, 我永远不会忘记, 相信我。 ";
			link.l1 = "... 很久以前他说他会为我而死... 我猜他从不知道他会为我们大家牺牲自己的生命... 现在他是英雄, 我会记住他... "+sld.name+"在哪里? 她没事吧? ";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "我不能这么说... 我的意思是, 身体上是的。 但是... 你知道... 她说她出去散步, 理清思绪。 可能, 她看到你靠岸了, 很快就会回来。 ";
			link.l1 = "诅咒你, 雅克.巴尔巴宗... 我们应该早点杀了他! ";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "等等... 还不止这些。 那个意大利人, 圭内利, 是的? 那个安静的年轻人。 他被... 他的尸体在酒馆里被发现... 我不知道, 可能是那些穿过地下墓穴袭击城镇的混蛋之一。 显然, 他们躲在那里, 寻找逃跑的机会, 然后发现了他... ";
			link.l1 = "还有吉诺? ! 今天真是个雨天... ";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "对不起, 查尔斯... 如果你愿意, 我们会把他们的尸体送到你的船上, 把他们带回家, 按应有的方式埋葬他们。 我真的很抱歉... ";
			link.l1 = "谢谢, 丹妮。 这么做... 我该走了... 我需要... 思考。 ";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// 多德森
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "查尔斯, 你能想象你的这场婚礼打破了多少女孩的心吗? 是的, 群岛上一半的女孩一定在你婚礼后哀悼, 哈哈! ";
			link.l1 = "我能做什么 - 我只需要一个, 而且我得到了她。 但女孩们现在难过还为时过早, 因为她们还有你, 史蒂文。 ";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "这是真的! 我们在这里结束后, 我会立即照顾她们, 该死的! 来吧, 查尔斯, 让我们为你的运气和家庭生活干杯。 所以, 正如他们所说, 永远幸福! ";
			link.l1 = "谢谢你, 我的朋友! ";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "为了幸福的家庭生活, 哈哈! ";
			link.l1 = "干杯! ";
			link.l1.go = "Dodson_2";
		break;
		
		// 旺桑
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "查尔斯, 你能想象你的这场婚礼打破了多少女孩的心吗? 是的, 群岛上一半的女孩一定在你婚礼后哀悼, 哈哈! ";
			link.l1 = "我能做什么 - 我只需要一个, 而且我得到了她。 但女孩们现在难过还为时过早, 因为她们还有你, 伯纳德。 ";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "这是真的! 我们在这里结束后, 我会立即照顾她们, 该死的! 来吧, 查尔斯, 让我们为你的运气和家庭生活干杯。 所以, 正如他们所说, 永远幸福! ";
			link.l1 = "永远幸福! ";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "为了幸福的家庭生活, 哈哈! ";
			link.l1 = "干杯! ";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "哈, 查尔斯, 所以你也变得已婚和无聊了, 像我们的老内森一样! 热门事务和其他一切现在都成为过去了, 嗯? 近似的居家男人! ";
			link.l1 = "等着吧, 伯纳德! 我的妻子不是那种会坐在家庭残骸的窗户下感到无聊的人! 唯一会改变的是从这里到库拉索的妓院女孩们的钱包的饱满度! ";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "我说, 损失不大! 一个金币比一袋镍币好。 我们喝一杯! 为你和你的妻子干杯! 保住你的黄金, 幸福生活! ";
			link.l1 = "谢谢, 伯纳德。 哦, 这真是强烈的朗姆酒。 呼! ";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "为你的新娘, 我的意思是, 已经是妻子了! ";
			link.l1 = "谢谢你! ";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "你来得正是时候, 查尔斯, 谢谢! ";
			link.l1 = "这里有什么趣事? 我以为你已经在港口的船上装货了。 ";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "马库斯留下我在岸边组织防御。 我们缺人, 港口的伙计们需要火药。 我想我会进来, 拿几桶... 然后这些暴徒。 哈, 他们躲起来了, 我猜, 想等着或抢劫某人。 而且我还满是霍克的朗姆酒, 所以没有你, 我不知道, 我是否还能活着。 ";
			link.l1 = "随时欢迎。 好吧, 伯纳德, 你确保城镇安全, 我该走了, 保持安全! ";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// 吉诺
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "船长, 让我衷心祝贺你和你的爱人在这个吉祥的日子! 要幸福, 互相照顾! ";
			link.l1 = "谢谢, 吉诺。 很高兴你决定来! 我希望当地的... 色彩, 不会困扰你? ";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "这是... 一次非常有教育意义的旅行。 我必须说 - 我很久没有离开安提瓜了, 在这个社会中, 我很难感到舒适。 但是, 你总是知道如何理解人, 所以我会努力保持冷静, 因为我信任你。 ";
			link.l1 = "也许你需要喝些更烈的东西? 放松一下, 找个人聊聊? ";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "谢谢你, 船长, 我已经喝了足够的稀释葡萄酒。 我必须警告你, 酒精对肝脏可能还有心脏都不是很好。 至于谈话, 我试图和那边的那位先生讨论Chirik-Sanango的治疗特性, 它也被称为Manaka。 缅因州的当地人用它来... ";
			link.l1 = "让我猜猜 - 那位先生无法支持讨论? 吉诺, 为了我, 而且只在今天 - 试试那边扬在柜台倒的朗姆酒。 如果你能猜出它的所有成分, 那边的纳撒尼尔.霍克会非常印象深刻。 我相信他会很高兴与你作伴, 就像柜台那边的斯文森一样, 他们都尊重受过教育的人。 ";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "为你的健康和你迷人配偶的健康! ";
			link.l1 = "谢谢, 朋友! ";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "船长, 是你, 谢天谢地! 那些蒙面人, 我看到他们就躲在这里, 他们试图破门... ";
			link.l1 = "没事的, 吉诺, 没人会再伤害你了。 很幸运我找到了你, 我需要你的帮助。 我的朋友受伤了 - 他被枪击了, 流了很多血。 我们必须快点! ";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "枪击... 流血... 好的, 船长。 来这里的时候, 我抓起了我的野营箱, 里面有所有处理伤口的工具。 带我去见他, 我会看看能做什么。 还有这些... 蒙面人, 也许他们还潜伏在别的地方? ";
			link.l1 = "我确定, 他们是最后一批。 吉诺, 港口有战斗, 我现在需要去那里。 你必须自己去住所, 不远。 拐角处的大房子 - 你不会错过的。 不要害怕 - 街上到处都是我们的人, 快点, 我求你了! ";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "船长, 让我衷心祝贺您和您的爱人在这个吉祥的日子! 愿你们幸福并彼此照顾。 ";
			link.l1 = "谢谢你, 吉诺。 很高兴你决定来! 我希望旅程顺利? ";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "一切都好, 船长, 感谢关心。 我必须说 - 我很久没有离开安提瓜了, 在精英阶层中我... 感觉不太自在。 但前来的理由让我没有选择。 顺便说 - 仪式非常出色, 我为你们俩感到非常高兴! 新娘穿这件衣服很迷人 - 这是新时尚吗? 原来我已经跟不上生活了, 但我真的喜欢。 ";
			link.l1 = "时尚... 在某种程度上是的, 或者至少很快会成为时尚。 好的, 玩得开心, 吉诺, 如果高贵的对话者让你感到无聊, 那就去港口。 全体船员都在酒馆里。 伙计们会很高兴见到你。 ";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "船长, 再次祝贺您和您美丽的妻子! 愿你们在一起长久幸福! ";
			link.l1 = "谢谢你, 吉诺。 很高兴你来了! 我希望当地的... 特色不会困扰你? ";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "在这个社会中我很难感到自在。 但是, 你总是知道如何选择朋友, 所以我会努力保持冷静, 因为我信任你。 ";
			link.l1 = "也许你需要喝些更烈的东西? 放松一下, 找个人聊聊? ";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "谢谢你, 船长, 我已经喝了足够的稀释葡萄酒。 我必须警告您, 酒精对肝脏可能还有心脏都不是很好。 至于谈话, 我试图和那位先生讨论Chirik-Sanango的治疗特性, 它也被称为Manaka。 缅因州的当地人用它来... ";
			link.l1 = "让我猜猜 - 那位先生无法支持讨论? 吉诺, 为了我, 而且只在今天 - 试试那边扬在柜台倒的朗姆酒。 如果你能猜出它的所有成分, 那边的纳撒尼尔.霍克会非常印象深刻。 我相信他会很高兴与你作伴, 就像柜台那边的斯文森一样, 他们都尊重受过教育的人。 ";
			link.l1.go = "Jino_3";
		break;
		
		// 朗韦
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "'独在异乡为异客, 每逢佳节倍思亲'";
			link.l1 = "朗韦, 从没想过你是个语言大师! ";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "抱歉, 船长, 我思考了很多。 这是王维的诗句 - 一位在很久以前统治我家乡的唐朝诗人。 ";
			link.l1 = "这些话太美了。 我希望有一天你能再次见到你的故乡... ";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''安能以此尚论列, 愿借辩口如悬河。 不然快剑斫断生蛟鼍.'不, 船长, 你知道的 - 朗韦不打算回家了。 现在, 这里是我的家, 我们今天有一件大事! 我向您和您美丽的新娘致以最美好的祝愿! 愿您的幸福如长江般绵长, 如繁星点缀, 如莲花般璀璨。 ";
			link.l1 = "谢谢你, 我的老朋友。 你的话不逊于王维的诗句。 ";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "我们喝一杯吧, 船长! 这种朗姆酒消除悲伤。 增添喜悦的效果不亚于茅台。 ";
			link.l1 = "为你的健康, 朗韦! ";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "很棒的婚礼, 船长! ";
			link.l1 = "喝吧, 玩得开心! ";
			link.l1.go = "Longway_4";
		break;
		
		// 克尼佩尔
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "给我来发链弹! 我们所有人都祝贺你! 仪式进行得如何? ";
				link.l1 = "一切都好, 查理! 现在我正式结婚了, 成了体面人, 我的大副现在是德.蒙佩尔夫人了。 ";
			}
			else
			{
				dialog.text = "来发链弹吧, 船长, 这么大的事! 几乎所有的兄弟会男爵都在这里! 我猜, 每个西班牙清教徒都把地狱想象成这样! 还有朗姆酒, 真是特别, 给我的枪管来发链弹! ";
				link.l1 = "是的, 这里的人不是最守法的, 但我们自己也不是天使, 查理, 这些人每个都以自己的方式让我珍视。 ";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "太棒了, 给我屁股来发链弹! 船长, 我是说, 这个庆典是为您举办的, 嗯, 我... 我, 祝贺, 我是说... 还有... 幸福和... 这个, 我不擅长演讲。 但您必须知道我们都爱你们俩, 我们会追随您直到地狱, 船长! ";
				link.l1 = "谢谢你, 老朋友。 ";
			}
			else
			{
				dialog.text = "等等, 我是说... 我到底是什么意思, 给我屁股来发链弹? ! 船长, 我的意思是这一天是为您举办的, 嗯, 我... 我祝贺您... 还有... 我祝您幸福和... 抱歉, 船长, 我可能喝得太醉了, 没法演讲, 给我脖子来发链弹, 我已经有一阵子没清醒过了哈哈哈哈! ";
				link.l1 = "哈! 没关系... 谢谢你, 老朋友。 ";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("你获得了宝石");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "啊! 还有, 船长, 请接受这个。 给您和您的女士。 我留着这些宝石以备不时之需... 我知道您不缺黄金, 但它们也不会多余, 对吧? ";
			link.l1 = "查理, 你真是个慷慨的人, 这些翡翠在德.蒙佩尔夫人的家族耳环里会看起来很棒! ";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "那么, 让我们为此干杯, 给我... 嗯。 只要幸福就好, 您和您的美人, 船长! ";
			link.l1 = "我们会的, 查理! ";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "很棒的婚礼, 船长! ";
			link.l1 = "喝吧, 玩得开心! ";
			link.l1.go = "Knippel_4";
		break;
		
		// 通扎格
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "我从没想过, 船长, 我会看到你结婚。 通常, 我们选择的道路会沿着一条孤独的小径直通孤独的坟墓。 在我的记忆中, 你是第一个设法摆脱它的人。 这值得额外干一杯, 不是吗? ";
			link.l1 = "就是这样, 伙计! 说真的, 我很高兴这部分生活已经成为过去。 干杯! ";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "为你和你长久幸福的生活干杯! 该死, 看着你, 我想起我自己也曾结过婚。 ";
			link.l1 = "你? 结婚? 你告诉我的事真有趣! 但发生了什么? ";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "怎么, 你以为我总是这个闻着火药和血腥味的老独眼龙吗, 船长? 但不是。 通扎格夫人她... 我猜她爱过我。 但后来发生了一件不愉快的事。 通扎格夫妇在那件事中'死了', 只有带着伤疤的秃头加斯东活了下来。 ";
			link.l1 = "对不起, 赫拉克勒斯, 我不知道... ";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "忘了吧, 船长, 那个故事发生在很久以前。 但现在, 看着你, 我认为我的故事仍然可以有一个好的结局。 所以, 让我们为此干杯! ";
			link.l1 = "让我们干杯, 伙计。 你知道 - 自从我遇见你的那天起, 我就把你看作自己的父亲, 所以也许有一天你会有机会成为曾祖父。 不管怎样, 干杯! 我必须去见其他人了, 我们稍后再聊。 ";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "很棒的庆典, 船长! ";
			link.l1 = "喝吧, 玩得开心! ";
			link.l1.go = "Tonzag_4";
		break;
		
		// 贝克
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "我们的船长在这儿! 恭喜, 您和您的妻子是美丽的一对! 愿你们永远幸福! ";
			link.l1 = "谢谢你, 雷蒙德。 ";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "夏普敦";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "圣皮埃尔";
			dialog.text = "看起来您在自己的婚礼上太清醒了, 船长。 想改变一下吗? 我在吧台拿了一瓶极好的雪利酒。 与当地朗姆酒混合效果很好! ";
			link.l1 = "我想喝, 但总得有人在这里看着事情。 否则, 在" + sTemp + ", 早上来的时候不仅酒馆会不见了。 ";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "出色的食物和出色的朗姆酒, 船长! 为您和您年轻的妻子干杯! ";
			link.l1 = "谢谢! ";
			link.l1.go = "Baker_2";
		break;
		
		// 亚历苏斯
		case "Alexus":
			dialog.text = "年轻人, 请问你们为什么闯进来? 造船厂关门了, 没注意到吗? 明天再来。 ";
			link.l1 = "大师, 很抱歉打扰您, 我们只是想穿过地牢。 有婚礼的补给, 酒馆几乎没酒了。 ";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "哦, 查尔斯.德.莫尔和纳撒尼尔.霍克本人! 你们好像在庆祝某人的婚礼, 对吧? 好吧 - 去拿你们的补给吧。 年轻人应该玩乐 - 这在任何时候都是法则。 回来时别把瓶子弄得叮当响 - 我要睡觉了! ";
			link.l1 = "谢谢您, 大师, 我们会像最平静的河流一样安静。 ";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "来吧, 别站着, 走! 那么, 船长, 您对一切满意吗? ";
			link.l1 = "... ";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// 地牢里的海盗
		case "DungeonPirate":
			dialog.text = "搞什么鬼? ! 雅克说‘没人下来这里’! 雨果 - 跑回去, 叫其他人, 我们来清路。 杀了这些家伙! ";
			link.l1 = "该死! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// 杀手
		case "killer":
			dialog.text = "伙计们, 忘了箱子吧, 我们有客人! ";
			link.l1 = "我以为像你这样的混蛋已经和杰克曼一起被杀了。 好吧, 让我们做个了断! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "靠... 我们被发现了! 警报! ";
			link.l1 = "让开, 混蛋! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// 安热兰
		case "Shivo":
			dialog.text = "德.莫尔先生, 晚上好, 或者已经快天亮了? 进来, 请坐。 ";
			link.l1 = "安热兰.德.谢沃! 果然是你! 这个只会和女人打架的小人物! 你还把她们绑起来了? ! 现在我要完成在马提尼克那场决斗中开始的事! ";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "冷静点, 年轻人, 看到这把枪了吗? 有两个弹仓。 也许我击剑不好, 但我射击很准 - 放下你的剑, 否则你会失去几位美丽的女士, 我向你保证。 ";
			link.l1 = "混蛋... 该死的你。 ";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "还有你, 海盗先生, 也放下武器, 就那样, 对。 现在 - 坐下, 你可以倒酒 - 在那边的桌子上。 我们得等一会儿, 直到巴尔巴宗先生砸烂你朋友们的船, 那些海盗男爵的船。 然后我们再决定你和我如何解决我们的... 嗯, 分歧。 ";
			link.l1 = "解决分歧? 怎么解决? 你想决斗? ";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "别这么可笑, 查尔斯。 你和博托夫人给我惹了很多麻烦, 我打算全额偿还。 尽管她给我惹的麻烦比你多得多... 不过如果你和这位威风的海盗先生安静地坐着, 那么我以名誉担保 - 你们的妻子会活着。 我想在缅因的西班牙殖民地, 这样的奴隶很有价值。 即使是非正式的。 但这仍然是生活, 不是吗? ";
			link.l1 = "安热兰, 你是个懦夫, 混蛋和... 靠, 任何语言中都还没有适合你的词! ";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "你知道的, 你没有选择。 我只能保证这会很快。 所以, 如果你爱这些女人 - 规矩点, 救她们的命, 也让你自己的命运好过些。 还有 - 如果不太麻烦的话, 把门锁上。 谢谢。 ";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "真是好斗的女士们。 我还是请你们谨慎些。 我从不喜欢杀女人。 ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "靠... ";
			link.l1 = "去死吧混蛋! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// 迪萨克
		case "Dussak":
			dialog.text = "查尔斯.德.莫尔船长, 霍克男爵 - 真是个惊喜! 让我介绍一下自己 - 莫里茨.迪萨克, 这是我的名字。 ";
			link.l1 = "让开, 混蛋! 我妻子在哪里? ! ";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "冷静点, 先生们! 看到这把枪了吗? 有两个弹仓。 我被这样称呼是有原因的 - 我当然喜欢军刀... 但我射击也很好, 相信我。 放下你们的剑, 否则你们会失去几位女士! ";
			link.l1 = "我要把你像猪一样宰了, 人渣... ";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "但你很快就会成为鳏夫。 你不希望这样吧? 那就冷静点, 放下武器。 霍克男爵, 请把门锁上。 我们冷静一下, 等一会儿, 雅克.巴尔巴宗在港口解决完你们的兄弟会领袖们。 ";
			link.l1 = "然后呢? 我们拥抱一起看日落? ";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "我不这么认为。 为了你们的囚禁, 雅克会给我大量黄金, 幸运的话, 也许我会成为男爵。 至于你们的女人, 也许我们会放了她们, 但至于你 - 唉... 如果你幸运, 我会请求亲自杀了你的权利, 船长。 你是著名的击剑手 - 测试你会很有趣。 你知道, 我也认为自己是大师。 ";
			link.l1 = "一个晚上破门而入并捆绑熟睡女人的大师? 你是条虫, 而且 - 是条古怪的虫! ";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "听着, 夫人, 我从没杀过女人, 别让我开始, 好吗? 你让船长和你丈夫很不安... 该死! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "妈的... ";
			link.l1 = "去死吧混蛋! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// 巴尔巴宗
		case "Barbazon_boarding":
			dialog.text = "该死的法国人, 没有军刀或子弹吗? ! ";
			link.l1 = "你知道的, 雅克, 我都有。 老实说, 当我发现你和杰克曼的诡计后, 我几乎后悔没杀了你。 但现在我要解决它。 ";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "你只有和一群人在一起时才这么勇敢? 让我们改变一下情况! 我稍后再处理男爵们, 但你别想活着离开这里, 老鼠! ";
			link.l1 = "不出所料... ";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// 支援
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// 女服务员
		case "waitress":
			dialog.text = "船长, 救命, 这个野蛮人绑架了我! 我... 我需要回家 - 叔叔可能已经把整个镇子翻了个底朝天! ";
			link.l1 = "冷静点, 美人, 一切都会好的。 让开, 我需要和你的‘野蛮人’谈谈。 ";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "谢谢你, 船长! 你救了我! 今天早上我在这个海滩醒来时, 我... 不敢相信我差点嫁给这个野蛮人, 他... ";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "是的, 清晨是夜晚希望之晶的严厉锤子。 明白。 但他来自穆斯科格部落, 按照他土地的严酷法律生活。 他在你同意的情况下偷走了你, 你们一起过了夜。 所以现在, 在他的神眼中, 你们是夫妻。 我们去收拾你的东西, 我会和你叔叔解决赎金问题。 ";
				link.l1.go = "waitress_2";
			}
			link.l2 = "对此我很抱歉。 提钦吉图按他部落的法律生活, 但他是个好人。 请忘记这个绑架故事。 ";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "妻子? 在他的神眼中? ! 不, 船长, 我求你, 救我摆脱这个! 这只是... 一场冒险, 他那么勇敢和迷人, 不像这些乡巴佬... 但结婚? 我还太年轻, 不能搬到野蛮人的茅屋里! ";
			link.l1 = "他是我的军官和最好的朋友, 所以别担心, 我给他高薪, 你会有你想要的最好的茅屋。 提钦吉图是个好猎手, 他会为你获取食物, 你会生儿育女。 ";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "孩子? 获取食物? ! 不, 船长, 求你别这样对我! ";
			link.l1 = "好吧, 也许我可以说服他。 但这不容易。 穆斯科格部落对这类事情非常认真, 如果有人发现他偷了女人却没结婚... ";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "你必须试试, 求你了! 我不会告诉任何人, 没人会知道! 我会骗叔叔, 这不是第一次了! ";
			link.l1 = "好吧, 你该走了, 美丽的女人。 我会尽量让我的朋友远离。 ";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "他像... 像从谷仓里偷山羊一样偷了我! 我会告诉所有人! 叔叔会杀了他! 他生气时很可怕! 他以前抢劫过西班牙船只 - 和他开不得玩笑! ";
			link.l1 = "好了, 嘘, 美丽的女士, 嘘。 也许两万个‘理由’让你原谅他会比我的话更有说服力? 或者我该把它们给你叔叔, 作为妻子的赎金? 毕竟, 所有人都在岛上, 对吧? 明天我们可以再组织一场婚礼... ";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "不不, 船长, 等等! 你说服了我。 我会想办法让叔叔不生气。 再见! 还有再见, 我来自遥远平原的骏马! 下次你来时见... ";
			link.l1 = "这就对了。 很高兴我们达成一致。 跑回家吧, 美人。 ";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// 圣皮埃尔酒馆老板
		case "tavernkeeper":
			dialog.text = "那么, 船长, 您对一切满意吗? 有最好的朗姆酒, 羊排, 猪腿, 甚至为您的科学家朋友准备了我个人储备的优质葡萄酒! 还有 - 我向您和您美丽的妻子表示祝贺! ";
			link.l1 = "谢谢! 我必须承认, 你把一切都组织得很完美。 我希望你的地窖里有足够的朗姆酒储备, 离天亮还远。 ";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "别担心, 如果桶见底了, 我会派助手去港口仓库。 玩得开心, 先生, 什么都不用担心。 ";
			link.l1 = "好的, " + npchar.name+ "。 那我去见我的客人了。 ";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "您想要什么, 船长? 炸排骨。 烟熏火腿还是牛胸肉? 也许给您的另一半来杯葡萄酒? ";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// 圣皮埃尔酒馆里的水手
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("为船长和他妻子的健康! ", "愿船长您永远幸福! ", "祝你们俩长寿幸福! "), LinkRandPhrase("为船长和他的美人欢呼! ", "愿幸运伴随船长和他的配偶一生! ", "祝你们家庭生活一帆风顺, 船长! "));
			link.l1 = LinkRandPhrase("谢谢! ", "谢谢你! ", "干杯! ");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// 勒弗朗索瓦的老板
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("你疯了吗? 想扮演屠夫? 所有海盗都生你的气, 伙计, 所以你最好离开这个地方。 ", "看来, 伙计, 你发疯了。 想活动一下手脚? 无意冒犯, 但你在这里没事可做。 滚吧! ");
				link.l1 = RandPhraseSimple("听着, 我想解决这个问题... ", "帮我解决这个问题... ");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "啊, 我一直在等您的来访, 老板。 扬.斯文森警告说您肯定会来检查勒弗朗索瓦的情况。 我已经把一切都揽在自己身上, 以雷霆发誓, 这个村庄会比和该死的‘好心人’在一起时生活得更好, 愿魔鬼在地狱最黑暗的地窖里和他作乐! ";
					link.l1 = "你是让.大卫, 对吧? 斯文森说过我的份额... ";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting() + " 老板。 勒弗朗索瓦一切如常。 您为什么来? 我能帮您什么吗? ";
					link.l1 = "只是顺道来看看情况如何。 ";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "我的份额呢? ";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting() + " 伙计。 您为什么来? 我能帮您什么吗? ";
				link.l1 = "只是顺道来打个招呼。 ";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "为您效劳, 老板! 至于份额 - 每个月的第五天, 您将从我们伙计的收入中扣除一部分金币, 它会等您来取, 要多少有多少。 从下个月开始您可以来取。 ";
			link.l1 = "不错! ";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "其余的我会处理。 森林魔鬼说您没有时间参与像勒弗朗索瓦这样的小事... ";
			link.l1 = "他说得对。 好的, 让, 我信任你, 希望你不会让我失望。 ";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "一切都会好的, 老板。 这里一切都在控制之中, 哈哈, 如果我搞砸了, 愿我到死都不能喝朗姆酒! ";
			link.l1 = "好的, 再见! ";
			link.l1.go = "JanDavid_1";
			// 启动份额计算
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "在等您呢, 老板。 这段时间我们为您收集了" + FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney)) + "。 拿着吧。 ";
			link.l1 = "哈, 不错。 干得好, 让。 ";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "我尽力了, 老板。 下个月再来或随时来 - 您的钱在我这里很安全。 ";
			link.l1 = "好的, 再见, 让。 ";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "解决问题? 你知道你做了什么吗? 无论如何, 给我一百万比索, 我会说服伙计们忘记你的行为。 如果不喜欢这个主意, 那你可以下地狱。 ";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "好的, 我准备付钱。 ";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "知道了。 我走。 ";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//关闭传送
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "好! 算你干净了。 但我希望你不会再做这种恶心的事了。 ";
			link.l1 = "不会了。 这对我来说太贵了。 再见... ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}