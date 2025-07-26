// 蛇眼部落的萨满
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "问候你, 我的白皮朋友。 ";
				link.l2 = "我也很高兴见到你, 红皮肤的兄弟。 我又有重要的事找你。 ";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "问候你, 我的白皮朋友。 ";
			link.l1 = "我也很高兴见到你, 蛇眼。 ";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "我带来了你要的护身符。 我们交易吧。 ";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // 曾在LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "我找到了你的手鼓, 蛇眼。 看看吧。 ";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "我找到了一个有趣的印第安烟斗, 蛇眼。 看看吧。 ";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "你好, 萨满。 我使用了雕像, 经历了一次不可思议的旅程。 你完全正确。 我找到了船只墓地。 白船长, 甚至还有装满补给的货舱! ";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "蛇眼, 我需要你的帮助。 ";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//--------------------------------------—— 第一次见面 ------------------------------------------------
		case "SnakeEye":
			dialog.text = "问候你, 我的白皮朋友。 ";
			link.l1 = "你好, 萨满。 你为什么认为我是你的朋友? ";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "我知道很多, 但不总是知道具体是什么。 你带着目的来到这里。 命运引领你到这里, 而我帮助你。 ";
			link.l1 = "很高兴知道! 我确实是来寻求你的帮助, 我的红皮肤朋友。 我直说了: 你告诉霍克的妻子关于库库尔坎的事是什么意思? ";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "即使是死鱼也会随波逐流。 而活人被命运从一个目标引向另一个目标。 那个被丛林里坏人追逐的锁链船长的目标是库库尔坎雕像。 如果他献祭了自己, 他可能已经远离这里了。 ";
			link.l1 = "我一点也不明白。 你们神的雕像到底是什么, 霍克怎么能徒步走那么远, 至今没人能找到他? ";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "如果库库尔坎吃了霍克, 那么它可能把他吐到任何地方。 也许甚至是另一个世界。 库库尔坎吃了我三次。 每次我都在不同的地方。 很久以前我来到这里, 决定不再冒险。 我没有去库库尔坎的嘴里, 也不知道它会把受害者吐到哪里。 ";
			link.l1 = "天啊, 这超出了我的理解! 你是说那个石偶像能把人传送到很远的地方? ";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "不仅如此。 库库尔坎不仅统治空间, 还统治时间。 甚至更多。 我告诉锁链船长关于吃人金雕像的事。 也许当他看到追猎者逼近时, 决定冒险... ";
			link.l1 = "等等, 雕像是石头做的。 而你说的是金色的... ";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "午夜时分, 偶像开始有了生命, 变成金色。 此时库库尔坎的灵魂居住在其中。 害怕靠近它, 否则你可能在不同的地方看到日出。 甚至星星也会改变它们在天空中的位置。 你会遇到那些还未出生的人, 或者看到那些早已死去或根本没有出生的人的诞生。 ";
			link.l1 = "什么... 谜语一个接一个... 你让我很好奇, 蛇眼。 你说你在与库库尔坎 --你所信仰的神 --的三次相遇中幸存下来。 那么为什么我不试试运气, 去接触我不信仰的神的偶像呢? ";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "可惜。 可惜你不相信。 也许库库尔坎自己召唤了你, 让你离开祖先的土地。 但你还没有听到它的声音。 一切发生都有好的理由。 如果你决定冒险, 那么你必须知道, 我每次幸存下来只是因为我有很棒的科曼奇药水。 ";
			link.l1 = "科曼奇? 那是另一个部落吗? ";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "那是敌人对我族人的称呼, 我再也见不到他们了。 药水恢复体力和耐力, 还能治愈并保护你免受强毒侵害。 你需要几瓶, 但我只剩下三瓶了。 \n原本有四瓶, 但我在一个奇怪的地方丢了一瓶, 那里看起来像白人船只的墓地。 我在那里开始了在这个世界的旅程。 也许库库尔坎把船长吐在了那里。 如果是这样, 我不羡慕他。 ";
			link.l1 = "那是什么地方? 船只墓地? ";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "奇怪的地方... 它不应该存在, 但它确实存在。 那里住着因为肤色而杀人的人。 他们把补给放在一艘大船里, 库库尔坎就是在那里把我吐出来的。 我没有进入他们保护起来以防小偷的货舱, 他们不信任邻居。 如果你到了那里 --找另一个出口, 不要进入货舱, 否则会有麻烦。 \n如果白人男孩还活着, 他会帮你找到另一个雕像。 把这个白珠子给他。 他喜欢它们。 ";
			link.l1 = "嗯。 我的头已经晕了, 而且这变得越来越有趣。 继续说, 红皮肤兄弟。 ";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("你获得了一颗白珍珠");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "如果你发现船长还活着, 他可能病得很重。 我没有时间给他药水。 在那里找我的手鼓。 我从祖父那里得到的。 我丢失的袋子里有很多东西, 但我只需要手鼓。 没有它, 很难与灵魂交流。 ";
			link.l1 = "嗯, 这个地方听起来很有趣! 希望霍克被传送到了那里... 你会给我你的药水吗? ";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "我会给你。 但是, 你要给我三个当地的护身符作为交换: " + XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian) + "。 " + XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet) + "和" + XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg) + "。 一符换一瓶。 这样公平。 等你集齐所有护身符再来。 然后我们交换。 别以为我贪婪。 或者, 也许你在寻找护身符时会重新考虑。 ";
			link.l1 = "我不会那么想。 等着我, 蛇眼, 我很快就回来。 ";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// 暂时这样
			{
				// 任务"导航星", 开始第4阶段
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// 给药水 - 去传送
		case "SnakeEye_potion":
			dialog.text = "好的, 我的朋友。 你把护身符带来了吗, 这样你就可以去找库库尔坎了? ";
			link.l1 = "是的。 我准备好踏上锁链船长纳撒尼尔走过的旅程了。 ";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("你已给出护身符");
			Log_Info("你获得了三瓶万能药水");
			PlaySound("interface\important_item.wav");
			dialog.text = "拿着这些药水。 记住, 库库尔坎把你吐出来后必须立即喝一瓶, 否则你会死或病得很重。 还要记住不要去白人存放补给的货舱。 有另一条路可以离开船。 实际上有两条路。 第一晚找一个红皮肤女人, 这非常重要。 这就是我能告诉你的全部。 ";
			link.l1 = "我会记住的, 红皮肤兄弟。 ";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "那就去吧。 午夜触摸库库尔坎, 它会吃掉你。 我会召唤灵魂来指引你。 ";
			link.l1 = "谢谢你, 蛇眼。 别担心我, 一切都会顺利的。 我们会再见面的! ";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // 传送门生效! 
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // 禁止军官进入传送门位置
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// 从LSC回来
		case "LSC_hello":
			dialog.text = "很高兴见到你, 我的朋友。 你是怎么从船只墓地回来的? ";
			link.l1 = "我在那里找到了库库尔坎的雕像, 就像你告诉我的那样。 白人男孩帮助了我 --奥莱.克里斯蒂安森。 雕像沉在海里, 但我还是能够到达它那里。 它把我传送到了多米尼加的一个印第安村庄。 ";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "在那里蒙基特库夫里迎接你了吗? ";
			link.l1 = "嗯。 蒙基特库夫里? 那是谁? ";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "他是 village chief.";
			link.l1 = "我没问他的名字。 也许他是蒙基特库夫里, 也许不是。 ";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "他头上有一个由鸟羽制成的华丽头饰吗? ";
			link.l1 = "当然, 他有。 很多羽毛... 好像他拔光了丛林里所有的鹦鹉。 ";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "他叫蒙基特库夫里。 那些不是鹦鹉羽毛, 而是鹰羽。 这个头饰是我的头饰。 当库库尔坎把我吐回来时, 我把它送给了蒙基特库夫里。 然后他们带我去了另一个雕像... ";
			link.l1 = "真是这样! 他们也把我"献祭"给了库库尔坎! 而我发现自己在这里, 靠近第一个雕像。 ";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "是的, 我的白皮朋友。 我的旅程也在这里结束了。 ";
			link.l1 = "这些偶像在循环传送... 但那有什么意义呢? 你有什么想法吗, 蛇眼? ";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "我认为这些雕像工作不正常。 目前, 它们把人传来传去, 但它们应该把人传到一个地方。 它们出了问题。 ";
			link.l1 = "你为什么这么想? ";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "因为循环传送没有意义。 库库尔坎必须把所有受害者传到一个地方, 而不是传来传去。 ";
			link.l1 = "那个地方可能是哪里? ";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "这是个大秘密, 白皮兄弟, 甚至对我来说也是如此。 ";
			link.l1 = "我明白了。 好吧, 去他的偶像。 我再也不会靠近它们了。 我已经找到了锁链船长, 不需要再通过传送门旅行了。 ";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "你在船只墓地时。 你在那里找到我的手鼓了吗? ";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "我想是的。 看看吧。 ";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "没有。 不幸的是我没找到。 但我知道那个岛在哪里, 我可以到达那里。 我会寻找你的手鼓。 ";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "寻找它吧, 我的白皮朋友。 我非常请求你。 没有我的手鼓, 我听不清灵魂的声音。 ";
			link.l1 = "好的, 蛇眼。 再见! ";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "那是我的手鼓。 谢谢你, 我的白皮朋友。 我可以报答你。 我送给你这件武器, 你们的人从现在起很长时间内都不会有。 这是我那个时代白皮人的武器。 ";
			link.l1 = "有趣! 给我看看, 红皮肤朋友... ";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("你获得了一把柯尔特左轮手枪");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "拿着它。 里面只有三发子弹, 其余的我用了。 但也许你会学会为它制作子弹。 我在船只墓地丢了几十发子弹的零件, 你可以在那里找到它们。 ";
			link.l1 = "哦! 那是一把手枪! 我以前从未见过这样的东西... 多奇怪的机器? 某种旋转装置... 五发! 不错! ";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "它叫柯尔特左轮手枪。 在你的时代没有其他像这样的手枪。 使用方便, 扳起击锤, 扣动扳机。 它射击良好。 ";
			link.l1 = "谢谢你! 谢谢你, 蛇眼! 这对我的敌人来说将是一个惊喜... 可惜只有三发子弹... ";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "试着自学如何为柯尔特左轮手枪制作子弹。 然后你将成为你那个时代的伟大战士。 啊, 我的白皮兄弟, 我忘了让你在船只墓地寻找我的烟斗。 那是一个非常漂亮的烟斗。 ";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "哈! 我一直在想这可能是谁的彩绘烟斗? 看看吧。 ";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "好的。 我也会寻找你的烟斗。 再见! ";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "这是我的烟斗, 我的兄弟。 我很高兴你找到了它。 我可以为此再送你一份礼物。 这是我那个时代白皮人的一本聪明的书。 我看不懂它。 试着找一个能读并理解这本书的聪明人。 ";
			link.l1 = "谢谢你, 蛇眼。 我想我知道有人会对这个感兴趣。 ";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("你获得了一本拉瓦锡的化学教科书");
			PlaySound("interface\important_item.wav");
			dialog.text = "把它给他, 白皮兄弟。 这本书有白皮智慧的伟大秘密。 ";
			link.l1 = "好的。 再见, 蛇眼! ";
			link.l1.go = "exit";
		break;
		
		// 治疗纳撒尼尔
		case "Saga_nathaniel":
			dialog.text = "我在听你说, 白皮兄弟。 ";
			link.l1 = "我把我在船只墓地寻找的锁链船长带来了, 他和我在一起。 他病得很重。 我知道只有你能治愈他... ";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "库库尔坎消耗了他的健康。 我想我可以帮助他治愈。 但至少需要一整个月亮。 库库尔坎很久以前就吃了船长, 疾病已经深入他的体内。 ";
			link.l1 = "请治愈他, 萨满! 我会给你带来任何你需要的东西! ";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "我会试试, 白皮兄弟。 你不必给我带任何东西。 我什么都有。 时间让病情加重, 但锁链船长一个月后会再次健康。 ";
			link.l1 = "谢谢你, 红皮肤兄弟。 你又一次救了我的命。 ";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "把锁链船长留在我的小屋里, 白皮兄弟, 放心走吧。 也把他的妻子带走, 没人能看到我的仪式。 ";
			link.l1 = "好的, 蛇眼。 我会带丹妮尔一起走。 再见! ";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "我在听, 我的朋友。 ";
			link.l1 = "还记得我们关于库库尔坎雕像的谈话吗? 你说'它们应该把人传到一个特殊的地方'。 ";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "我记得, 白皮船长。 ";
			link.l1 = "我知道那些雕像必须把被库库尔坎吃掉的人传到哪里。 ";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "哪里? ";
			link.l1 = "到古老的玛雅城市塔亚萨尔。 它位于梅因丛林的深处。 ";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "非常有趣。 你怎么知道的? ";
			link.l1 = "这是一个很长的故事, 蛇眼。 我也明白你是怎么到这里的。 你甚至还没有出生, 对吗? ";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "在你的时代, 甚至我的父亲都还没有出生。 但我生活在你的时代, 这是一个巨大的谜团。 ";
			link.l1 = "这实际上是可以解释的。 一位名叫卡内克的伊察祭司, 他住在塔亚萨尔, 召唤库库尔坎以凡人的身份降生在这个世界, 并吸收白人种族的智慧。 他还创造了一个时间洞, 将未来的几个人传送到我们的时代... ";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "让库库尔坎吸收未来人的智慧? ";
			link.l1 = "是的。 而库库尔坎计划回到过去, 将知识传递给早已死去的玛雅人。 历史将被改变, 玛雅人将统治美洲, 甚至更多... ";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "但传送门出了问题, 它们开始循环传送人, 而不是传送到塔亚萨尔。 这就是我在这里的原因, 我需要你的建议, 蛇眼。 ";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "为什么是我, 白皮船长? ";
			link.l1 = "因为你被库库尔坎吃掉过。 还因为你村庄附近的库库尔坎雕像在这张地图上有一个奇怪的标记, 这与卡内克的仪式密切相关。 ";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "给我看看这张地图? ";
			link.l1 = "给, 看看... ";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(看着) 这个圆形标志, 是吗? 它是什么意思? ";
			link.l1 = "我不知道, 萨满。 我知道三个库库尔坎雕像中只有一个有这个标记。 而有标记的雕像就是你的。 我得出的结论是, 你的雕像是特殊的。 有什么想法吗? ";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "给我到明天早上的时间, 白皮兄弟。 把这张皮革地图留给我。 我需要问灵魂。 明天回来。 ";
			link.l1 = "好的, 红皮肤兄弟。 我明天会来。 谢谢你帮助我。 ";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "过会儿再来, 白皮兄弟。 现在不要打扰我。 ";
			link.l1 = "当然, 萨满... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "我有话要告诉你, 白皮兄弟。 ";
			link.l1 = "你发现了什么吗? 或者你有什么猜测? ";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "祖先的灵魂给了我幻象, 我带着地图去找库库尔坎。 我搜索并找到了。 这一定是你在寻找的东西, 白皮兄弟。 ";
			link.l1 = "你找到了什么? ";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "库库尔坎雕像有两个铁夹和凹槽。 凹槽呈圆形, 光滑。 它指向你皮革地图上的圆形扁平物品。 ";
			link.l1 = "那是什么? ";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "我不知道。 我只知道它是圆形的, 扁平的, 大小像个小南瓜, 也许有一根手指那么厚。 你可以自己去看看凹槽和夹子。 夹子需要固定它。 ";
			link.l1 = "你有什么想法吗? 或者猜测它可能是什么? ";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "石头上有火的痕迹。 我知道发生了什么。 天火击中了它。 ";
			link.l1 = "闪电? 是闪电击中了它吗? ";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "我确信如此。 我问过米斯基托人关于这个偶像的事。 一个战士说, 很久以前, 在雕像上看到过一些漂亮的彩绘物品。 非常像岩石。 他告诉我它们是非常漂亮的红色岩石。 一个来自白人村庄的白人买了它们。 ";
			link.l1 = "嗯。 据我理解, 似乎是闪电击中了这个圆形的"东西", 把它打碎成碎片, 然后这些碎片被卖给了某个白人? ";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "似乎是这样。 ";
			link.l1 = "那个白人是谁? 你的战士告诉你了吗? ";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "他告诉我了。 他是米斯基托人的好朋友, 住在布鲁维尔德村。 他的名字是森林恶魔。 我认识他, 你一定也认识他。 ";
			link.l1 = "扬.斯文森? 等一下... 你说红漆岩石? 看来我刚好运气不错。 看这里, 萨满, 看看这些红岩石! 森林恶魔送给我的。 ";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("你已给出装饰图案碎片");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "一定是它们。 五块岩石。 看看, 白皮兄弟。 如果你像这样放置它们... (放在一起)";
			link.l1 = "... ";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... 然后我们就有了圆形物品。 看! 它们匹配。 之前它是一个物品。 ";
			link.l1 = "该死的! 这些东西在我口袋里放了这么久... 听着, 萨满, 如果我把碎片放进凹槽里... ";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "库库尔坎会像你说的那样, 把受害者吐在古老的印第安城市。 ";
			link.l1 = "那太好了! 我需要到那里去! 你认为这些碎片, 如果已经碎了, 还能起作用吗? ";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "我认为我们需要把它们拼在一起, 然后把装饰品放进凹槽里。 ";
			link.l1 = "把它们拼在一起? 但我们怎么把它们重新拼起来? ";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "把它留给我和祖先的灵魂吧, 白皮兄弟。 它们不是普通的岩石。 这是神奇的物品。 三个晚上后回来, 白皮兄弟。 我会召唤灵魂。 生者的智慧和技能, 尝试把碎片拼合起来。 ";
			link.l1 = "不可思议... 我该如何报答你, 蛇眼? ";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "以后再谢我, 白皮兄弟。 现在走吧。 三个晚上后回来。 ";
			link.l1 = "好的。 我希望你会成功... ";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "我可以让你高兴, 白皮兄弟。 ";
			link.l1 = "你能把碎片拼合起来吗? ";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "是的。 这并不容易, 日历上还留有疤痕, 但现在它完整了。 ";
			link.l1 = "日历? 你为什么叫它日历? ";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "因为这个圆形的东西是日历。 我仔细研究过它。 上面有时间计数。 来自古城的印第安人计算夜晚。 月亮。 年份和年代。 ";
			link.l1 = "不可思议... 不过, 想想玛雅祭司能做什么 --这个日历的创造似乎也没什么特别的。 ";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("你获得了一个玛雅日历");
			dialog.text = "拿着它, 白皮船长。 把它放进雕像的凹槽里。 然后也许它会把你吐在印第安城市。 ";
			link.l1 = "我该如何报答你, 蛇眼? ";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "说'谢谢你'。 神会指引你的道路, 即使你看不到。 白人说 --命运。 库库尔坎召唤了你, 神指引你。 现在走吧。 做你的事, 让善良的灵魂指引你。 ";
			link.l1 = "谢谢你, 蛇眼! 我永远不会忘记你。 ";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("你获得了四瓶万能药水");
			PlaySound("interface\important_item.wav");
			dialog.text = "等等。 我们差点忘了最重要的事。 库库尔坎吃人并消耗他的生命。 我为你制作了药水。 科曼奇药水。 我把它们给你。 我做了四瓶, 所以你可以带三个忠诚勇敢的同伴一起去。 ";
			link.l1 = "你为我做了这么多, 红皮肤兄弟... ";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "对于科曼奇部落的印第安人来说,'兄弟'不仅仅是一个词。 当从库库尔坎城回来时, 访问我们的村庄。 我们煮了很多很多的萨赖卡。 我会很高兴见到你。 ";
			link.l1 = "当然, 红皮肤兄弟! 我一定会拜访你! ";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // 皮革地图可以出售 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}