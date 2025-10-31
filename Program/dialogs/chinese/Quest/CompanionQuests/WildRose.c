void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			link.l1 = "什么都没有。";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+"嘿, 快看这边! ";
			link.l1 = "安静, "+npchar.name+", 这里可能不止我们一个人。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = " + pchar.name+"! ";
			link.l1 = " + npchar.name+"? 你一直跟在我后面吗? ";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "看来这还真不是白忙一场, 对吧! 这里发生了什么? ";
			link.l1 = "要是我早知道, "+npchar.name+", 要是我早知道就好了……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "我的天啊……";
			link.l1 = "是啊, 可怜的人, 看起来她死前受了不少苦。谁都不该有这样的结局……";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "那是谁啊, 她丈夫吗? 他们到底在丛林里干什么? ! 难道没听说过逃跑的奴隶吗? ";
			link.l1 = "恐怕他们已经无法再回答那个问题了……";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "你觉得干这事的人还在附近吗? ";
			link.l1 = "很有可能。所以我们最好小声点——我们得在他们发现我们之前先发现他们。";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "太晚了, "+pchar.name+"。看来我们已经被发现了。看看那边。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "哟哟, 伙计们, 看看这个。简直就是情人窝, 对吧, 嘿嘿。两只小情人刚撒手人寰, 马上又有一对来接替他们的位置了……";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "很聪明嘛。不过你算术好像不怎么样, 对吧? 和那些可怜虫不同, 我们可一点都不孤单。";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "嗯, 咱们这边可没那么简单, 你最好信我, 对吧……";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "我本来想说你比他们聪明——但那纯粹是胡说八道。就算你们人多, 也打不过那些混蛋。你身边的漂亮姑娘, 下场也会和倒在你脚下的那位一样……";
			link.l1 = "你说的是那些逃跑的奴隶吗? 这是其中一个? 所以, 你们是Bishop的人? ";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "你问的所有问题答案都是肯定的。我们和士兵们追了他们整整两天多, 几乎把整个岛都翻遍了。后来那些混蛋分头逃跑, 一部分往洞穴方向撤退——守卫们追了上去——剩下的则冲向了海湾。就在离这里西边半英里处, 他们设下埋伏, 我们损失了几个人, 等我们回过神来重新集结时, 他们已经在那个蠢丫头身上得逞了……";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "把你的牙签自己留着吧, 花花公子——别来烦我, 也别惹我的伙计们。我要看看, 要是你被我们在海湾干掉的那帮混蛋围上一打, 你还能有多大本事。只有一个家伙走了狗屎运——不过也蹦跶不了多久……等那混蛋落到Bishop手里……";
			link.l1 = "所以你们是他雇来的雇佣兵? ";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "嗯, 他们显然不是驻军士兵。 如果不是那些游手好闲的家伙, 我们昨天就能抓住那些恶棍了——那个傻瓜和他老婆现在还会活着…… ";
			link.l1 = "所以, 这不是你的手笔吧…… ";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "你把我们当成什么人了, 对吧? 我们可不是天使, 但要是我们想的话, 我们会去妓院, 不会去...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "他在撒谎, 满嘴谎话——这个肮脏的无赖! 别听他的, "+GetAddress_Form(NPChar)+"! 我们根本没碰那些可怜人! ";
			link.l1 = "哦, 真的吗? 那我们为什么要相信你而不是他? ";
			link.l1.go = "Naemnik_8";
			link.l2 = "行吧? 还是说其实是你在撒谎, 对吧? 你可一点也不像个圣人呢。";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "拜托, 你自己想想吧! 我们可是被那个恶魔主教追着跑, 在丛林里转悠了两天, 还得掩盖行踪——结果呢? 就为了现在去侵犯一个可怜的女人, 还让那些吸血鬼追上我们? ! 我的朋友们几乎是拖着脚才上了那片海滩, "+GetAddress_Form(NPChar)+"! 我们连开火的力气都没有了, 不然绝不会让那些混蛋为所欲为…… 全都是他们干的, 我们都看见了! ...";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "拜托, 你自己想想吧! 我们可是被那个恶魔主教追着跑, 在丛林里躲了两天, 拼命掩盖行踪——为了什么? 难道就是为了现在去羞辱一个可怜的女士, 还让那些吸血鬼追上我们? ! 我的朋友们几乎是拖着脚才上了那片海滩, "+GetAddress_Form(NPChar)+"! 我们连开火的力气都没有了, 不然绝不会让那些混蛋得逞…… 全都是他们干的, 我们亲眼所见! ..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "闭嘴, Casper, 你这只脏狗! ";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "你说什么? ! ";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "你是聋了吗, 女士? 我让他闭嘴来着。 我们家Jerry能吹牛吹上好几个小时——他可真有这本事, 没错! 主教本来想割了他的舌头让他自己吃下去, 结果后来又改主意了——那可真是个错误, 见鬼! ";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "但是…… 你刚才叫他Casper, 对吧…… ";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "听着, 小子, 去告诉你女朋友, 人嘛, 就算是像这家伙这么小的, 也不光有名字, 还有姓氏。 我是听说过不少次, 漂亮女人有时候脑袋跟稻草一样空, 但见过像她这样的, 还真是头一回…… ";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "这正是我要给你的, 对吧! ";
			link.l1 = "Mary, 等一下! 这事我自己来处理。 把你的武器收起来。 现在就收。";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "哦, 所以我们这儿有位真正的绅士, 对吧? 嗯, 你的举止可比那个小虫子的尖叫体面多了。 他叫得比他那可怜的老婆还大声——隔着那座小山都能听见,  对吧? 说真的, 他其实还帮了我们一点忙——我们就是靠着他的叫声才追踪到那帮混蛋的…… ";
			link.l1 = "在加勒比这地方, 贵族可稀罕得很。 现在大家深呼吸一下——在这儿立刻见阎王, 可一点都不高贵。";
			link.l1.go = "Naemnik_17";
			link.l2 = "这里唯一的恶棍就是你们这帮家伙。 现在就向Mary道歉, 也许我们还能避免流血。";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "这还真让人无话可说。 不过, 先冷静一下你的…… ";
			link.l1 = "她叫Mary Casper。 我觉得这已经说明了很多。";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Casper? 她是他女儿还是什么的, 哈哈? ";
			link.l1 = "我很怀疑这一点。 不过我希望你现在已经聪明到知道该收回你的话了。";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "回来了? 还是怎么的? 你要跟我决斗吗? 来啊…… 如果你不怕把你的宝贝一个人丢在丛林中央的话, 嘿嘿。 要真那样, 我和兄弟们可会——非——常——高兴呢。";
			link.l1 = "所以, 你终于露出真面目了。 你的演技也就那样, 对吧。";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "你啊, 先生, 真是个矛盾体——一方面那么温和, 另一方面却又这么粗鲁。 对吧? 不过我倒想知道, 你会去向那个红发疯丫头求原谅吗? ";
			link.l1 = "她叫Mary Casper, 要是你现在不…… ";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Casper? 哎呀, 我的天! Jerry, 这难道是你家小姑娘吗, 嗯? 哈哈哈哈! 我简直不敢相信自己的耳朵! 谁能想到啊! ";
			link.l1 = "你知道还有什么事会发生吗? 像你这种只会道听途说什么荣誉的蠢货, 对待女士就像她们是马厩里出生的一样。 可我还能指望什么呢——你脑子里全是木屑, 哪还有地方装礼貌, 对吧。";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "哟哟…… 多么放肆的小家伙啊。 告诉我, 伙计, 你那姑娘在吊床上本事怎么样? 不过, 我敢肯定她不怎么样——我倒是很乐意亲自试试…… ";
			link.l1 = "所以你还是露馅了。 没撑多久, 对吧。 准备战斗吧! ";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "你真是狠狠教训了他们一顿, "+GetAddress_Form(NPChar)+", 那些混蛋。 愿他们下地狱! 可惜我没能及时帮上你。 我来的路上看到一支火枪, 但离得太远了。 看起来是我们有人逃命时掉的。 我真希望能亲手把那个混蛋Primer打死。";
			link.l1 = "看来Primer是真的把你折腾惨了, 你才决定回来。";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "他当然干过。 多亏了那个混蛋, 我背上全是伤疤。 不过最糟糕的是, 他想让我们断水就断水。";
			link.l1 = "可惜那些混蛋一个都没活下来。 我们本来可以把他交给士兵——我敢肯定, 他们很快就会到。";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "我也不太确定为什么, 呃, "+GetAddress_Form(NPChar)+"…… ";
			link.l1 = "嗯, 你看…… 司令肯定会逼他招供, 这样你的清白就能洗清了——还有你那些牺牲朋友的名声。";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "哈哈, 当然啦。 然后 William Bishop 会把我活剥了皮——这可是我在种植园听一个黑哥们说的…… Bishop 对逃跑的人可不手软——不管你是黑的还是白的。";
			link.l1 = "恐怕你无论如何都得回种植园…… ";
			link.l1.go = "Djerry_5";
			link.l2 = "所以, 你不是心甘情愿回种植园的, 对吧? ";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "你还真会开玩笑——有人跟你说过吗, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = "别开玩笑了, "+npchar.name+"。 你以为我会无缘无故出现在这儿? 我是专门进丛林追你们小队的, 想把你带回种植园——顺便赚点金币。 可现在只剩下你一个。 你又不值几个钱, 也许我会放你走。 可你告诉我——你到底在想什么? 你就剩自己一个了, 其他人都死了。 你还指望什么, 真是见鬼? 躲在山里灌木丛里, 等着中枪、病死, 还是被美洲虎吃掉? ";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "你真会开玩笑——有人跟你说过吗, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = "别开玩笑了, "+npchar.name+"。 你以为我是碰巧在这儿的吗? 我是特意进了丛林, 想找到你们队伍, 把你们带回种植园——顺便赚点金子。 可现在只剩下你一个了。 你一个人也值不了几个钱, 所以也许我会放了你。 但你告诉我——你到底在想什么? 就剩你一个, 其他人全死了。 你还指望什么, 见鬼? 躲在山里和灌木丛里, 等着被一颗子弹打死, 或者死于热病, 还是被美洲虎吃掉? ";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "这样反而更好, 天知道, "+GetAddress_Form(NPChar)+"——要我说, 这比死在Bishop准备的那些酷刑下可强多了。 其实也没那么糟——在Ragged Point附近藏着一艘带帆的小船。";
			link.l1 = "离巴巴多斯最近的陆地是多米尼克, 那儿有土著, 还有托巴哥, 那儿有西班牙人。 我都说不清哪个对你来说更糟…… ";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "我想我还是去碰碰运气, 跟西班牙佬混吧——走私犯和海盗常常在多巴哥抛锚。 哦, 我看得出来你不赞同我的选择, "+GetAddress_Form(NPChar)+"。 我曾忠心为国效力——可如今她把我发配到采石场, 我还能怎么办? ";
			link.l1 = "我不是在评判你, "+npchar.name+"。 每个人都有自己的路。 现在多带点火药和弹药——赶紧走吧。 趁士兵还没来之前。";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "谢谢您, "+GetAddress_Form(NPChar)+"。 还有你, 小姑娘, 呃, Mary。 (鞠躬) 当然, 我们并没有什么亲戚关系, 不过在这种, 呃, 情形下遇到同姓的人…… 实在是太意外了, 而且…… ";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "我想是吧, 好吧。 现在, 再见了, Jerry。";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 你有什么心事吗? 你和你的同名道别得也太快了吧, 对吧。";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "我只是想尽快摆脱那家伙的纠缠…… 他的话漏洞百出, 对吧。";
			link.l1 = "你在说什么呢, 亲爱的? ";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "在听了主教手下那家伙说的话后, 我毫不怀疑那些可怜的人都是死在他手里的。 但在那之前…… Casper——你刚才真的有在听他说什么吗? ";
			link.l1 = "那你到底哪里觉得不对劲呀, 亲爱的? ";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "他说海滩上藏着一艘船。 但是有二十多人从种植园逃出来, 所以那船肯定挺大的, 对吧? Jerry是个海军逃兵, 他很清楚一个人操控那么大的船可不容易, 对吧…… ";
			link.l1 = "他只需要扬帆并保持航向——剩下的就交给风了。 好吧, 他确实是在冒很大的险, 但也许死在大海上, 真的比死在种植园主的刽子手手里要好。";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "好吧。 但是现在我发现还有别的地方说不通…… 据他说, 他和他的朋友们在远处看着那些雇佣兵欺负那个可怜的女孩…… ";
			link.l1 = "没有直接跑向我的船…… 好吧, 我明白你的意思了, "+npchar.name+"。 也许我该再问Casper先生几个问题…… ";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = "嘿, "+npchar.name+", 老朋友! 等一下…… ";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = "该死! ! ! Mary, 小心! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "卑鄙的家伙! 我们救了他的命, 可他却这样! 那我们算什么呢, "+pchar.name+"? 所以说, 结果就是…… ";
			link.l1 = "好了, "+npchar.name+", 现在已经没有活人知道事情的真相了…… ";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "我们得离开这里, "+pchar.name+"。 要是士兵们在这儿发现我们, 可就麻烦了, 对吧。";
			link.l1 = "你说得对, Mary。 我们走吧…… ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "你知道吗, "+pchar.name+", 经历了这一切, 我真的很想喝一杯, 对吧。";
			link.l1 = "我不跟你争了, 亲爱的。 我自己也想喝一杯, 对吧? 咱们去 'Irish Cuckold' 坐坐吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "抱歉吵醒您了, 船长…… ";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "被打倒了, 这也算点事儿, 对吧。 现在说吧——你到底想从我这里得到什么? ";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "幸好你知道敲门, 伙计。 要是你刚才直接闯进来, 现在早就被我从楼梯上扔下去了。 \n看什么呢? 有话快说——你跑这儿来干嘛? ";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "有个镇上的人想见你——Lewis Gernon。 他说有重要的事情要和你谈。";
			link.l1 = "这个名字我从没听说过。 我希望他真有重要的事, 不然就这样把我从…… 这种工作中叫走。 让他进来吧…… ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "你好, "+pchar.lastname+"先生。 Casper小姐。";
			link.l1 = ""+TimeGreeting()+", "+npchar.lastname+" 先生。 我记得我们以前没见过吧。 那你是怎么认识我们的? ";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "不记得了吗? 啊, 我明白了…… 我的脸上沾满了血和灰尘, 几个小时前我照镜子时自己都被吓了一跳…… ";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "你…… 你就是那个人, 没错, 我们找到你了, 然后…… ";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "还有我的Susan。 可怜的Suzie…… ";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "我们还以为你死了呢。 而且…… 她是你妻子, 对吧? ";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "是的, 女士。 她是我的妻子, 而我当时吓得动弹不得…… 我什么都做不了。 天啊, 天啊…… ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(抽泣) 他们打了我, 还强迫我看…… ";
			link.l1 = "站起来, "+GetAddress_Form(NPChar)+"。 这不是你的错。 面对那么多恶棍, 谁都撑不住。";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "他们实在是太多了, 太多了…… 但是, 我还是…… ";
			link.l1 = "不过你还是活下来了, 你妻子的凶手也在地狱里受苦。 这虽然聊胜于无, 但总算有点安慰, "+npchar.lastname+"先生。 不过, 我还有件事想问你…… ";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "好了, "+pchar.lastname+"先生, 对吧? ";
			link.l1 = "他们是谁? 是主教的雇佣兵, 还是逃跑的奴隶? ";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "这是 Jerry Casper 和其他逃犯干的。 你本不该责怪 Bruce Primer 和他的人。";
			link.l1 = "主教的雇佣兵? ";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "好吧。 Bruce确实是个无赖, 也为Bishop干了不少脏活——但他从来不是强奸犯。";
			link.l1 = "在我看来可不是这样。 不过我不跟你争, "+npchar.name+"。 不过既然你当时是清醒的, 也看到了全部, 你本可以站起来然后…… ";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "请原谅我, "+GetAddress_Form(NPChar)+"。 你可以叫我可怜的懦夫——但我真的动不了, 实在是太害怕了。 当那些恶棍拦住我和苏茜的路时, 一开始我只是拼命尖叫, 希望有人能来帮忙。";
			link.l1 = "然后他们把你揍了一顿。";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry用他的火枪枪托狠狠砸了我一下, 然后还说要当着Susan的面把我剁成碎片。 我…… 我都不好意思承认了, 对吧? 但我真的因为太害怕, 好像还晕了几秒钟。 就在那时候…… ";
			link.l1 = "我理解你, "+npchar.lastname+"先生。 你的行为并不丢人。 不是每个人都能承受你经历的那些事。 可惜你没有出手——不过事已至此。 至少我们成功送了你妻子的一个凶手下地狱, 这点我还是很高兴的——哪怕他差点骗过了我们。";
			link.l1.go = "Lewis_14";
			link.l2 = "所以我们差点被主教的雇佣兵杀了——就因为你害怕, 是这样吗? 真是个好借口, "+npchar.name+"。 还好最后我们总算把事情弄清楚了, 虽然有点晚…… ";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "好吧, "+GetAddress_Form(NPChar)+"。 我来是为了感谢你这件事。 即使一开始你相信了他…… ";
			link.l1 = "Bruce Primer为此付出了很多努力。 他真的该注意自己的言辞…… ";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "好吧, "+GetAddress_Form(NPChar)+"。 我来就是为了感谢你这件事。 即使一开始你相信了他…… ";
			link.l1 = "Bruce Primer为此可是下了不少功夫。 他真的该注意自己的言辞了…… ";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "唉, 那天我们都犯了错…… Susan和我本不该去Ragged Point散步, Bruce本该管住自己的嘴…… 而你也不该相信Jeremy。 不过, 多亏了Casper小姐, 正义才得以伸张。";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "我想我知道你想问我什么, "+sld.lastname+"先生。 但是那个人的事和我无关。";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "我知道, 小姐。 我一走进这个房间就明白了。 你和他之间一点都不像。 可是, Susan…… 她一直坚信, 这世上没有什么是偶然发生的。";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "你妻子说得对。 我自己也不止一次见过, 真的。 还有"+pchar.name+", 我也是。";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "没错。 不过我觉得现在不是谈哲学的时候。 我怀疑这对你有没有帮助, "+npchar.name+"。 这种事, 只有时间能帮你。";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "也许你说得对, "+pchar.lastname+"先生。 好吧, 再次感谢你, 祝你一路顺风。 我会为你和Casper小姐祈祷。";
			link.l1 = "保重, "+npchar.name+"。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"…… ";
			link.l1 = "我知道, 亲爱的, 我差点让那个混蛋逍遥法外了…… ";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "一个叫Jerry Casper的杂种。";
			link.l1 = "没错…… 等等…… 你不会是说, 你觉得他…… ";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "我知道这真的很蠢…… ";
			link.l1 = "当然啦! 要是你的姓是Smith或者Jones呢? 大街上有成千上万这样姓的人——其中有些人肯定会干坏事…… 还有那个Jerry, 让他下地狱吧——说不定他根本就不是Casper呢…… ";
			link.l1.go = "Mary_34";
			link.l2 = "没错, 亲爱的。 那个该死的Jerry完全可能用了个假姓, 对吧? ";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "可即便如此…… 我知道你不懂我的意思, 但你想象一下, 如果他也姓"+pchar.lastname+", 你会怎么想。";
			link.l1 = "这可不是一回事, Mary。"+pchar.lastname+"——那可是贵族的姓氏, 而且…… ";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "不过…… 我知道你不懂我的意思, 但你想象一下, 如果他也姓"+pchar.lastname+", 你会怎么想。";
			link.l1 = "这可不是一回事, Mary。"+pchar.lastname+"——这是个贵族姓氏, 而且…… ";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "至于Casper家嘛, 说到底, 我们就是些无名无姓、无依无靠的人, 对吧? 我想我应该每天都感谢上帝, 你竟然会注意到我, 而不是那些自以为是的家伙…… ";
			link.l1 = ""+npchar.name+", 我完全不是那个意思——你明白的。 贵族家庭的成员是血脉相连的, 这可不是仅仅和别人同姓那么简单。 就像我说过的, 有些人只是随便给自己取了个姓氏而已…… ";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "这可不仅仅是因为那个, "+pchar.name+"…… ";
			link.l1 = "亲爱的, 咱们今天可真是够累的了。 咱们在丛林里走了好几英里, 差点就死在那里…… 结果几乎一夜没怎么睡觉。 你脑子里有点奇奇怪怪的想法也不奇怪, 对吧? 咱们俩都该好好睡一觉了。";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "我一点也不觉得奇怪, 不过好吧…… 我们明天再谈。";
			link.l1 = "头脑清醒的话, 我们会更快把一切理顺。 躺下吧, 亲爱的, 我们得把这一天抛在身后。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "你还好吗, "+GetAddress_Form(NPChar)+"? 你看起来怪怪的, 好像见到鬼了一样。 要不要来点朗姆酒? 或者葡萄酒? 我们这里有很棒的选择, 你也该放松一下了。";
			link.l1 = "去他的酒。 我在找一个姑娘…… ";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "那你可来错地方了, 船长。 这是酒馆, 不是青楼。 你出去看看, 就在街对面…… ";
			link.l1 = "听着, 我现在没心情开玩笑。 我在找一个穿红色短上衣、留着红头发的女孩, 她带着武器。 她叫Mary Casper。";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "如果咱们不是在开玩笑, 那我就没什么好说的了。 我的班一个小时前就开始了, 我可没见过穿红外套的红发姑娘在这儿。";
			link.l1 = "所以她是夜里离开的…… 可是她能去哪儿呢? ! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "早安, 我的爱人! 你睡了好久呢…… ";
			link.l2 = "你刚才真让我担心了, "+npchar.name+"。 以后别再这样突然消失了, 行吗…… ";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "我不想吵醒你。 而且, 你有时候也会这样突然消失, 一句话都不说…… ";
			link.l1 = "你决定回应我的感情了吗? ";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "说真的, 我只是想一个人静静地想想事情, 对吧。 我不想让你担心。";
			link.l1 = "有什么烦心事吗? ";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "我们昨天的谈话。 关于姓氏, 血缘关系…… ";
			link.l1 = "所以, 你果然还是在生我的气, 对吧…… ";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "才不是呢, 亲爱的, 我不是那个意思。 只是我突然意识到, 我对自己的家人一无所知, 对吧? 比如你——你可是贵族世家的子弟。 船上的伙计们, 时不时都会聊聊自己的家人。 而我——我什么都说不出来。 我从没见过我的父母, 见鬼, 我甚至都不知道自己是在哪出生的…… ";
			link.l1 = "不是在Isle of Justice上吗? ";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "抚养我长大的Eric总是这么说。 可如果真是这样——为什么岛上的人从来没人跟我提起过我的父母, 连一句都没说过? 我曾经问过Donald Greenspy这事, 可他也没给我什么明确的答复。";
			link.l1 = "或者他只是根本不想说话。";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "看到了吧? 我也是这么想的, 对吧。 你知道吗, 我以前一直都是糊里糊涂地过日子, 也没怎么想过这些。 可昨天我们碰上那个混蛋Jerry的时候…… 我就在想——我父亲是谁? 我母亲是谁? 为什么从来没人跟我说起他们, 好像他们根本不存在一样? 要是我父亲其实也和Jerry那种混蛋一样呢? ";
			link.l1 = "一点都不重要, "+npchar.name+"。 你是被别人养大的——而且他们做得很好。";
			link.l1.go = "Mary_50";
			link.l1 = "我怀疑是不是这样。 而且我真看不出这有什么重要的, 毕竟你以前好像从没在意过, 对吧? ";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "但是这对我来说很重要, "+pchar.name+", 对吧。 我就是想知道, 我有权利知道我的父母是谁。 你不觉得吗? ";
			link.l1 = "我当然同意啦, 没别的办法了, 对吧? 不过, 要是你想知道关于你父母的任何事, 就得去正义岛。 毕竟, 你连他们的名字都不知道, 对吧? ";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "但这对我来说很重要, "+pchar.name+"。 对吧? 好吧。 我就是想知道, 我有权利知道我的父母是谁。 你不觉得吗? ";
			link.l1 = "我当然同意, 没别的办法了。 不过如果你想知道关于你父母的任何事情, 就必须去正义岛。 毕竟, 你连他们的名字都不知道, 对吧? ";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "没错, 亲爱的。 没人当着我的面提起过他们, 对吧。";
			link.l1 = "所以, 现在去翻查英国殖民地的城市档案还为时过早。 我们得先回到那片沉船墓地, 试着在那里找到你家族的线索。";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "我很高兴你能理解我, "+pchar.name+"。 谢谢你。";
			link.l1 = ""+npchar.name+", 你真的让我惊喜了, 对吧。 这是我能为你做的最少的事情了, 亲爱的。";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "不知怎么的, 我居然活了将近二十年, 却对他们一无所知…… ";
			// dialog.text = "最终, 二十多年里, 我根本毫不在意…… ";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "那我就再忍一会儿吧, 对吧。";
			link.l1 = "我看得出来这对你很重要, 你也需要这个, "+npchar.name+"。 所以我会尽量不让你久等。 现在, 走吧, 我们得回船上去。 我觉得你在船上我会更安心, 至少是这样。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "故乡的海岸…… 你知道吗, "+pchar.name+", 我觉得就算我们十年后再回来, 这里看起来还是会和现在一模一样, 对吧。";
			link.l1 = "也许吧, "+npchar.name+", 也许吧。 内环的船还会漂在水面上, 但这里生活的人会变得不一样。";
			link.l1.go = "Mary_62";
			link.l2 = "我严重怀疑——这里的一切全靠一个承诺维系着。 还有机械师的天才。";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "我几乎已经记不清十年、十五年前住在这些沉船上的人了。 只有那些最亲近我的人——Alan, Eric…… ";
			link.l1 = "我想事情就是这样吧。 你不可能记住所有的人和事。 名字和面孔也会从我的记忆中淡去——从我在巴黎的日子开始, 更别说加斯科涅了。 我还以为只有老人家才会这样呢。";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "而且我几乎记不起十年、十五年前住在这些残骸上的人了。 只有对我最重要的人——艾伦, 埃里克…… ";
			link.l1 = "我想这就是人生吧。 你不可能记住所有的事和所有的人。 连我自己都常常忘了在巴黎时的名字和面孔——更别说加斯科涅了。 我还以为只有老人才会这样呢。";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "但是这个地方…… 就像另一个世界, 对吧? 你能想象吗, 有些不久前才到这里的人说, 这里的时间流逝速度几乎是大陆的三倍…… ";
			link.l1 = "哈哈, 那你今年多大了? ";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "我可是认真的, 对吧。"+pchar.name+", 对吧! ";
			link.l1 = "好吧, 不过说真的, 该正经点办事了。 独角鲸里有谁比Greenspy年纪还大吗? ";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "嗯, 不, 我不这么认为。 不过我已经跟你说过了, 我问他的时候他什么都没说。";
			link.l1 = "不过, 我现在实在想不出还有谁能帮我们弄清二十年前发生的事了, 至少目前没有。 所以, 我们要驶向'Esmeralda'号。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "啊, "+pchar.name+"和Mary, 真是难得一见啊! 很高兴看到你们…… 还活得好好的, 呵呵。 过去一个月里, 外环附近已经有两三艘船失事了——最近这海可真不安分。 好了, 别再硬闯锁着的门了——你们要是把锁弄坏了, 修的可是我。 你们是来找Donald的, 对吧? ";
			link.l1 = "也祝你今天愉快, 朋友。 自言自语。 不过看那扇锁着的门, 他要么是换到别的船上去了, 要么就是不想见老朋友了。";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "都不是, 哈哈。 Greenspy现在在外圈训练呢。";
			link.l1 = "演习? 真的吗? 他是在准备和Rivadose的新战争吗? ";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "其实从来没真正消停过, "+pchar.name+"。 只是最近打架的次数没以前那么多了。 不过嘛, 在Sancho的酒馆, 时不时还是有人挨上一拳…… 有时候还会有人拔刀呢。";
			link.l1 = "嗯, 看起来以前族里的人可不会在酒馆露面。";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "嗯, 自从你离开岛上以后, 有些事情变了。 Donald和Eddie现在还能管住大家, 暂时还行。 可谁知道明天会发生什么呢? 这就是老Donny为什么要搞这一切的原因…… ";
			link.l1 = "我费尽心思阻止了岛上的大屠杀, 就只是为了让你又在这里玩当兵的游戏吗? 他在外圈晃荡了多久了? ";
			link.l1.go = "Schmidt_5";
			link.l2 = "演练当然没错, 不过这样不会让本就脆弱的停战变得更危险吗? 还有, Greenspy已经让那些小伙子们操练多久了? ";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "已经三天了。 他应该在明天中午前回来。 看他们那边擦火枪的劲头, 等到早上恐怕都快擦没了还能打什么! 哈哈! ";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "已经三天了。 他明天中午前应该就会回来。 看他们那边擦火枪的样子, 等到明天都快没枪能打了! 哈哈! ";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "我的舱房在'Ceres Smitty'上还空着吗? 还是已经有人搬进去了? ";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "一切都和你上次去的时候一样。 我们甚至连门都没开过。 说实话, 这么久也没打扫过, 也没给锁上油。 所以, 如果你需要把它撬开, 直接说一声就行。";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "当然。 谢谢你, Jurgen。";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "真的, 一切都和以前一样。 我的东西都还在原来的地方——就像我从未离开过一样…… 这里就是你我第一次见面的地方, "+pchar.name+"。 还记得吗? ";
			link.l1 = "当然啦! 你对付那两个人那么厉害, 我还以为——说不定我自己都会变成他们那样呢! ";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "根本不是那样的, 对吧! 你是真的把我从死亡边缘救出来了! ";
			link.l1 = "感觉那次相遇就是命运特意为我安排的。";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "你真的这么想吗, 亲爱的? ";
			link.l1 = "当然了, 亲爱的。 从那以后, 我每天都感谢她把我带到了 'Ceres铁匠铺' 。";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"…… 告诉我, 你第一次见到我时是怎么想的? ";
			link.l1 = "嗯…… 我只记得那时候, 我感觉心脏都要跳出来了。 你当时真的…… ";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "哪一个? ";
			link.l1 = "你和我以前认识的任何人都不一样。 你的优雅, 你的声音…… 还有那件红色紧身上衣。 我根本无法抗拒你。 我得承认, 我一直很好奇: 为什么偏偏是那个? 为什么是红色紧身上衣, 而不是裙子、衬衫或者束身衣? ";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "我九岁那年在外圈发现了它。 那时候我特别喜欢在那儿闲逛——探索所有新鲜玩意儿, 找些岛上没有的东西, 尤其是书。 我当时特别想试穿它, 对吧? 可那会儿它会把我整个吞掉。 所以我就把它藏在我放其他宝贝的地方——一个伸出水面的瞭望台里。";
			link.l1 = "等到他终于合你心意的时候, 你就记起他来了? ";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "几年前, 我在竞技场附近闲逛时, 偶然发现了一本讲述一位身穿红色外套的英勇船长的书。 他无所畏惧, 为了挚爱与数百敌人奋战, 从不知什么叫害怕。 那时候我第一次尝试成为他。 他给了我自信…… ";
			link.l1 = "还有你那让人无法抗拒的魅力, 亲爱的! 但你知道吗? 现在我只想要一件事…… 把它从你身上脱下来…… ";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "那你还等什么呢, 我勇敢的船长? ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "早安, 亲爱的。 独角鲸号的人刚刚回到了 '埃斯梅拉达号' 和 '圣加布里埃尔号' , 唐纳德也在他们当中。 我在一只小艇里看到他了, 没错。";
			link.l1 = "早安, 早安…… 说真的, 昨晚那样折腾一夜, 我本来想睡到中午的, 可你已经起床到处转悠了。";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "昨天我们聊到了那件短上衣和瞭望台, 对吧? 我以前总是把它藏在那里…… 突然间, 我就特别怀念那些日子。 那时候我会躲到上面, 远离所有人, 只为了安静地看那些讲述广阔世界的书, 对吧? 我实在忍不住, 就又跑去了那里。 我以前能在上面待上好几个小时, 可今天…… 我只是看着日出。 然后我明白了: 这个世界上, 我最想做的事情, 就是陪在你身边, 对吧? ";
			link.l1 = "我也和你在一起, "+npchar.name+"。 那么, 我们去找Donald吧? 我们有好多话要聊, 对吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, 见到你真高兴! 我已经听说你昨天来过了。 我本来还想着自己去 'Ceres铁匠铺' 看看, 结果被你这丫头抢先了。 唉, 要是我还有你这么年轻就好了…… ";
			link.l1 = "嗯, 你自己的精力也很充沛, 这我们都见识过了。 训练怎么样了? ";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "比我预想的还要好。 我们练习了跳帮登船, 冲进船舱…… 总的来说, 表现很不错。 确实, 我把伙计们操练得挺狠的, 不过这对他们有好处。 他们已经很久没活动筋骨了, 哎呀, 确实有段时间了, 哈哈。";
			link.l1 = "那我能问问, 是啥激发你干出这种事的? 在岛上待腻了, 对吧? ";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "嗯, 我能听出你语气里有点不高兴, "+pchar.name+"。 当然, 我能理解他的理由…… ";
			link.l1 = "真的吗, "+npchar.name+"? ";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "你可是在这些破烂沉船里跑了不少地方, 好让咱们别互相割喉——我可没忘记这事。 没人会忘的。";
			link.l1 = "你就是这样回报我所有的付出! 看来他们说得没错——真正的战士在世间找不到安宁。";
			link.l1.go = "Grinspy_5";
			link.l2 = "而且我得说, 我更指望你的理智, 而不是那些海盗或者里瓦达人, 对吧? ";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "让我说完。 好吧, 我们总算维持住了和平——但我们的分歧可一点没消失, 尤其是和那些黑皮肤的异教徒。 上周, 一名独角鲸成员在酒馆斗殴中被杀。 不过我们也没就这么算了…… ";
			link.l1 = "是啊是啊, 每次都是这么开始的, 对吧。";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = "让我说完。 好吧, 我们总算维持住了和平——但我们的分歧可一点没少。 至少, 对那些黑皮肤的异教徒来说是这样。 上周, 有个独角鲸成员在酒馆斗殴中被杀了。 不过我们也没就这么算了…… ";
			link.l1 = "好吧, 事情总是这样开始的。";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "你错了, 两点, "+pchar.name+"。 首先, 这不是开始, 而是延续。 如果你天真地以为你能结束这一切, 那你就错了。 其次, 我可不是那种会逆来顺受的圣人。 黑人们又闹起来了, 我可不喜欢这样。 顺便说一句, Dexter也不喜欢, 但他觉得自己是什么了不起的政客, 宁愿置身事外。 所以, 经过一番思考, 我选择了我认为最…… 无痛的方式来维持这脆弱的和平。";
			link.l1 = "你是打算用你的教义吓唬Rivadans吗? ";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "几周前, 一艘载着军用货物的英国大帆船被冲到了外环——你绝对想不到船上装了些什么…… 不过最重要的是有五十支全新的火枪, 还有上好的火药。 还有那些小艇…… 油漆都还没干呢! 旧的小艇都快散架了, 风暴过后, 能完好无损留下来的小艇可没几艘了, 跟你说啊…… ";
			link.l1 = "这一切都成了独角鲸的财产? ";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "也许我本来会跟Admiral分享的, 不过既然他自以为是这里最聪明的人, 我也不想当傻子。 对了, 我的计划成功了, 对吧? 就这样。";
			link.l1 = "Black Eddie给你送过信, 说他会不再剖你的人, 对吧? ";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "黑艾迪命令他的黑小子们安分点。 我还担心我不在的时候, 他们会变本加厉——结果完全相反: 那些rivados现在老实得很, 离我的船员和他们以前偶尔欺负的镇民都远远的。 黑人就是黑人——他们只懂得强硬。 阿兰以前总这么说, 要是他说错了, 这船现在就沉到海底去! ";
			link.l1 = "那要是过一阵子他们又开始闹事, 你会不会用你的新火枪朝Fury号和Protector号开枪, 吓唬吓唬他们, 让他们老实点? ";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "这个主意确实大胆又冒险, 但我觉得事情不会发展到那一步。 也许我们只是装作要袭击他们的船——然后Layton就会终于鼓起勇气出面了。 他最近有点自大, 没错, 但这人又不是瞎子。 不管是我们家族还是黑人帮派被毁, 对他都没好处——三个势力差不多平衡, 局势还能勉强维持。 一旦其中一个倒下, 一切就会彻底乱套。 我相信他明白这一点——可不知为什么, 偏偏得由我来替他做事。";
			link.l1 = "我们在这儿的时候我也许会去看看他——除非他又想来一场布道, 哈哈。";
			link.l1.go = "Grinspy_12";
			link.l2 = "有机会的话, 我会去找他聊聊这事。 谁知道呢, 也许他会听进去。";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "要是有人能说服他管好那些黑奴, 那一定是你, "+pchar.name+"。 不过看你们的表情, 你们可不是来聊政治的。 说吧, 你们想要什么? ";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "我的父母, Donald。";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "我不太明白你到底想从我这里得到什么, Mary。";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "跟我说说他们吧, 拜托, 对吧。 你认识他们! 我以前问过你他们的事, 可你那时候没回答我的问题…… ";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "所以你才决定把Charles拉来这里, 哈哈哈! 你这丫头可真有意思, 要是我说谎就让我天打雷劈! 如果我从没跟你提过你父母, 那只是因为我根本不认识他们, 就这么简单! ";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "但是你可是我们家族里最年长的成员, 对吧! 我记事起你就在这里了…… ";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "我是在差不多二十年前来到这座岛上的, 那时候你已经出生了。 你那会儿还只是个小家伙, 跑来爬去, 在桌子和凳子底下钻, 把可怜的Eric Udette折腾得不得安宁…… 当然啦, 我问过他, 怎么会有这么个停不下来的小家伙——他跟我说你是几年前在岛上出生的。 他从没提过你的父亲或者母亲。 如果他提过——那要么是我当时没记住, 要么就是现在已经忘了…… ";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = "这么多年过去了…… 我明白了, Donald, 行吧。";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = "真可惜Erik没和我们在一起——他比我早很久就到了这个地方。 对吧? 对了, 他以前总是说起你最近的那些疯狂举动, 还经常提到Aurelie Bertin。 那位老太太可真是特别喜欢你, 这我记得很清楚…… 我以前从没想过为什么, 但我觉得你出生的时候她就已经在岛上了。 也许她能帮你, 对吧? ";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = "也许吧。 正好有个理由去看看她——我都不记得上次去是什么时候了。 结果也不怎么好, 对吧。";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "我觉得她并没有生你的气。 但是别太逼她——我听说她身体不太好。 可别让事情变得更糟了…… ";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "安静点, Donald, 你会给我们惹麻烦的! Aurélie肯定会比我们都活得久, 对吧。";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "走吧, "+pchar.name+"! ";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "再见, "+npchar.name+"。 很快再见。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "仁慈的上帝, 我的心差点跳出来了。 你不能这样吓人, 对吧? ...";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Jillian! 没想到会在这儿见到你, 对吧。 你在这里干什么? Aurelie呢? ";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "你们好啊, Mary, 还有你, "+pchar.name+"。 Aurelie病了, 你不知道吗? 我是应Julian修士的请求照看她。 他给我送来药剂, 我就喂她喝, 可是…… 好像没什么用。 现在她在船尾的船舱里睡觉。 我把她带到那儿, 这样我就能在这里收拾一下。";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "我们也是今天才知道的, 对吧。 是Donald告诉我们的。 她怎么样了? ";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "不好。 她总说自己很虚弱, 几乎下不了床。 有时候还会含糊地嘟囔些听不懂的话, 胡言乱语…… 我都听了太多关于过去的故事, 已经数不过来了。";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "嗯, 这正是我们来听的故事。 我希望她不会拒绝和我们谈谈…… ";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "真的有这个必要吗, Mary? 我觉得她现在这个样子, 我们还是别去打扰她了。";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "这是关于我父母的事。 Aurélie可能认识他们。 这对我真的很重要, Jillian, 对吧。";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "岛上难道没有什么药能让她好起来吗? ";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Julian兄弟给她配药剂。 但是那些药只能暂时缓解。 即便如此, 她还是不肯喝, 我几乎得强行把药灌进她嘴里。 有时候我真怕她会被呛到——我甚至得逼着她把药全咽下去…… ";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "可怜的Aurélie! 岛上真的没有人能帮她吗? ";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = "你自己也知道这里根本没有真正的医生。 你又能做什么呢, 对吧? 人们常说, 岁月不饶人…… ";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", 要不要带我们船上的人一起去? ";
			link.l1 = "我担心, "+npchar.name+", 我们现在需要的不是船医, 而是一位真正的医生。";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "现在只要能帮上忙, 魔法我都愿意相信, 对吧。";
			link.l1 = "嗯…… 魔法? 也许我该去找Chimiset聊聊…… ";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Chimisetu? 那个黑巫师? "+pchar.name+", 你是认真的? ";
			link.l1 = "从没这么好过。 现在他是黑是白我才懒得管, 对吧? 我不知道还有谁能帮奥雷莉, 我猜你也一样, 对吧? 所以让开, 别想挡我的路。";
			link.l1.go = "Jillian_16";
			link.l2 = "不仅如此。 Julian修士的祈祷和任何药物都无法救Aurelie。 Chimisette是我们最后的希望。";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "我简直不敢相信自己的耳朵! 但那家伙…… 简直是个无神论者! ";
			link.l1 = "而这可是个快要死去的女人, 离忘记自己名字只差一步。 好吧, 他是个巫师, 对吧? 但我听说他们能做到很多事情, 真的很多。 如果他能让她恢复神志——现在他信仰什么真的还有关系吗? ";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "我简直不敢相信自己的耳朵! 但那是…… 个无神论者! ";
			link.l1 = "而这就是一个快要死去的女人, 已经快要连自己的名字都记不住了。 好吧, 他是个巫师, 但我听说他们什么都能做到, 什么都行, 对吧。 如果他能让她恢复神志——现在他信什么教, 真的还有关系吗? ";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = " + pchar.name+ , 听我说, 我也很关心Aurelie…… 上帝作证——我正在尽全力减轻她的痛苦! 可是你真的要让那个黑皮异教徒在这间船舱里做他的仪式吗? 要是他把船点着了, 或者在仪式中决定拿某个人祭祀怎么办? ";
			link.l1 = "我们不会让那种事发生的, "+npchar.name+", 我向你保证。";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "我向你们俩保证, 如果有人发现了这件事…… 你们知道这里会发生什么吗? 其他镇上的人肯定不会喜欢, 独角鲸们更是如此! ";
			link.l1 = "你说得对。 我们不该把Chimiseta拖过来, 应该把Aurelie带去找他。";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "你还没见过她——那老太太都快站不住了。 要是不掉进海里, 那可真是奇迹! ";
			link.l1 = "有时候我们也只能寄希望于奇迹了, 对吧。 还有, Jillian…… ";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "还有什么? ";
			link.l1 = "我希望你能保密。 你是个聪明的女人, 你判断得很对…… 岛上的骚乱很容易演变成流血事件, 没人希望那样, 对吧? ";
			link.l1.go = "Jillian_22";
			link.l2 = "一句话都别透露, 明白了吗? 我们已经信任你了——别让我们后悔。 我想你明白, 如果我们的计划不再是秘密, 这座岛上会爆发前所未有的血腥屠杀。";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "好吧。 但你得确保没人看到你把她拖上 'Protector' 号…… 否则我可得回答一些尴尬的问题了。";
			link.l1 = "我们就不让你为难地回答了。 今晚我们来解决, 对吧? ";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "好吧。 不过你得确保没人看到你把她拖上 'Protector' 号…… 否则我可得回答一些尴尬的问题了。";
			link.l1 = "我们不会让那种事发生。 我们会在晚上动手。";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "午夜过后再来。 她会在这儿。 看在上帝的份上, 小心点。";
			link.l1 = "你不用担心, "+npchar.name+", 我们会非常小心的。";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "午夜过后再来。 她会在这儿的…… ";
				link.l1 = "好吧。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "奥蕾莉已经准备好了。 你可以带她走。";
				link.l1 = "好吧。 那我们走吧。";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "年轻人, 咱们…… 咱们要去哪儿? ! 这是Rivadose的船! Eric在哪儿? ! ";
			link.l1 = "Eric和Eddie Black成了朋友, 你不知道吗? ";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "你说什么呢, 小子! Erik可受不了黑人, 知道吧! ";
			link.l1 = "哟, 你看看这个! 好吧, 那我们就去问问他到底在这里干什么吧! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "哟, 看看是谁来找我们了! "+GetFullName(pchar)+", 亲自来了! 很高兴见到我的白人兄弟, 哈哈! 那么, 你来这里有什么事? ";
			link.l1 = "也向你问好, "+npchar.name+"。 我真希望只是来喝杯朗姆酒的, 但恐怕我有紧急的事要找你——或者说, 是找Chimisetu。";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "我们永远欠你一个人情, 朋友。 我们会尽全力去做。";
			link.l1 = "好吧, 既然如此。 因为我已经没有其他人可以依靠了。";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "你需要我帮哪位女士, "+pchar.name+"? ";
			link.l1 = "我真搞不懂你是认真的还是在开玩笑, "+npchar.name+", 不过我现在可没心情开玩笑。 当然, 是Aurélie需要帮助。";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Eric! ERIC! 给我出来, 你这个老家伙! 这都什么乱七八糟的? ! 赶紧把你那瘦骨嶙峋的屁股给我滚过来! ";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "所以是真的咯…… 我的人跟我说这家伙脑袋有点问题。 现在我算是信了, 他们没骗我。 可我还是不太明白你到底想从Rivadose那里得到什么…… ";
			link.l1 = "让我和Chimiset谈谈, 你就会明白一切了…… ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "说吧, 亲爱的朋友。 我会认真听你说的。";
			link.l1 = "我长话短说, Chimisette。 Aurélie掌握着Mary和我需要的信息。 但是由于她的身体状况, 如果我没理解错的话, 主要就是年纪大了, 对吧, 我们…… 既无法从她那里得到这些知识, 也无法确定她说的是否准确。 我听说过印第安和非洲萨满都能做出奇迹——这就是我来找你帮忙的原因, Chimisette。";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "我明白你的意思, 我的朋友。 萨满拥有神秘莫测的力量, 常常超出外人, 甚至他们自己族人的理解, 更别说白人了。 有些人称之为巫术, 有些人则说是奇迹。 我们确实能做到许多事情——但没有人能让河水倒流…… 也没有人能让它停下来。";
			link.l1 = "你什么意思, Chimiset? ";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "我说的是时间之河, 朋友。 或者说生命之河——你喜欢哪个都行。 你看, 你说得完全对——这个可怜灵魂的病根就在于她的年岁, 除此之外别无他因。";
			link.l1 = "我听说过一点。 只知道这并不是什么稀罕的问题。";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "你说得对。 她这个年纪的人常常会被带到梦境的谷地, 有时甚至是噩梦的深渊。 她们会回来, 但很快又会离开——这并不完全是她们自己的意愿, 而是有神秘的力量在牵引她们。 随着时间推移, 这种病症会越来越严重——直到一个人再也记不起自己, 也记不起朋友。";
			link.l1 = "所以, 你也没办法了? ";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "要彻底驱除疾病——不行。 这超出了我的能力。 但我还能做点别的…… ";
			link.l1 = "到底是什么? ";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "等这个女人醒过来, 我就会立刻施行我事先准备好的仪式…… ";
			link.l1 = "就算不能彻底治愈, 至少能让病情减缓一点吗? ";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "不完全是。 她必须拼尽全力, 才能尽可能保持清醒。";
			link.l1 = " '尽可能长' 到底有多长呢? ";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "这不是取决于仪式, 而是取决于人。 有的人能撑上一周, 有的人能撑一个月…… 我听说有个男人, 他几乎保持清醒和记忆将近一年, 甚至可能更久…… 就在大家都以为他已经痊愈的时候, 病症又回来了——就在那天夜里带走了他。";
			link.l1 = "一个小时足够我们了解所需的信息了。 你什么时候能进行仪式, Chimiset? ";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "我现在就把那个女人带走, 带她下到船舱——那里已经设好了一个避难所…… 就是专门为这种事准备的。 之后, 就看她什么时候恢复神智了…… 不过我觉得, 等到天亮我们就能搞定。";
			link.l1 = "那我就不打扰你了。 愿你的…… 神, Chimiset, 保佑你。";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "谢谢! 帮我把那个白女人带到船舱里。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "成功了, 白人兄弟。 我们设法…… ";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "哎呀, "+GetFullName(pchar)+"! 我都不知道你和Mary已经回到岛上了! 真是个惊喜! ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimiset, 谢谢你! 我都不知道该怎么感谢你…… ";
			link.l1.go = "Chimset_14";
			link.l2 = "哟, 你看看, Chimiset还真做到了! 我可从没怀疑过你哪怕一秒…… ";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "所有Rivados人都永远欠你一个人情, 我的朋友! 'Protector'的大门永远为你敞开。";
			link.l1 = "我希望以后不会再麻烦你了…… Mary, Aurelie, 我们得回 'Pluto' 号去了。";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "所有Rivados人都永远欠你一个人情, 我的朋友! 'Protector'的大门永远为你敞开。";
			link.l1 = "我希望不会再麻烦你了…… Mary, Aurelie, 我们得回 'Pluto' 号了。";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "我甚至都记不得我是怎么离开船舱的了…… 唉, 这年纪大了, 记性真是一塌糊涂。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "哟哟, 这位小姑娘, 什么风把你吹到我的船舱来了? ";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = " Aurélie, 我…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Aurelie, 我让她在你不在的时候把这里收拾一下。 你就不用再为这些活累坏了你的膝盖和腰了…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "打扫? ! 你…… ";
			link.l1 = "Jillian, 谢谢你的努力。 (低声) 我们成功了。 Chimiset办成了。";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "不可能吧…… ";
			link.l1 = "如你所见。 现在, 请让我们谈谈吧。";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "嗯, 年轻人们, 谢谢你们护送一位老太太。 我恐怕很快就完全不能出门了。 我的可怜的腿啊, 我的腿…… ";
			link.l1 = "如果你不介意的话, "+npchar.name+", 我们会再陪你一会儿。 Mary和我有非常重要的事情要和你谈。";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "只要不用再把自己拖到另一艘船上, 我怎么帮都行。 我听着呢。";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = " Aurélie, 我想让你告诉我关于我父母的事。 还有我出生的那一天。 是在这里, 这座岛上发生的, 对吧? Donald说是这样, 但那时候他根本不在这里, 所以他也不可能真的知道。 可你在这里住得比他久多了, 对吧! 已经有二十多年了, 不是吗? ";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "慢点, 慢点, 姑娘, 别说那么快, 拜托了! 我都跟不上你了…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "好吧, 我明白了。 行, 我们再过一遍吧…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "别担心, Mary, 我还没老到那个地步呢, 哈哈…… 我听到你说的话了。 不过既然我确实在岛上待的时间比谁都长, 我还是希望你能对我的年纪多点尊重和理解…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "当然啦, Aurelie! 你怎么会有别的想法呢? ";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "唉, 我看看现在的年轻人, 然后…… 不不, 我们那时候可不会那样对待长辈。 当然, 这不包括你。 我只是想说, 如果我一个一个回答你的问题, 而不是一下子全说完, 会轻松些…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "我明白了, Aurélie。 你想怎样都可以, 对吧。 那你在我出生的时候就在岛上吗? 如果真的是在这里发生的, 当然…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "我是在1633年来到这个岛上的, 有时候那一天到现在还会出现在我的噩梦里。 那场风暴, 我们的 '复仇号' ——我和丈夫一起驶往佛罗里达的那艘弗吕特帆船——被巨浪翻搅着, 随时都可能翻船, 我们把会的祷告全都念了一遍, 甚至还现编新的…… 然后, 突然一声巨响, 然后…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "所以你在我出生前五年就已经到这里了, 对吧。";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "差不多吧。 那时候, 这里的情况有点不一样——圣赫罗尼莫号还没沉, 外圈的船只数量也许只有现在的一半, 甚至更少…… 而且这还远远不是所有还漂在水面上的船! 我跟你们说啊, 年轻人, 要是哪天你们在晴天往下看, 一定会被底下那些沉船的数量吓一跳…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "我们对我父母当年来到这里时乘坐的那艘船感兴趣。 是带着我…… 还是没有我? ";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "和你, 姑娘, 和你。";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "所以, 我果然是在大陆出生的? ";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "不, 我的意思是 '和你一起' , 但稍微有点不同。 那时候你还在你妈妈肚子里, 一周后才出生。 ";
			link.l1 = "你觉得这好笑吗, Aurélie? ";
			link.l1.go = "Oreli_32";
			link.l2 = "这些年过去了, 你的幽默感还是没变, Aurélie。";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "嗯, 我更多的时候是在嘲笑自己, 而不是别人。 对不起, Mary, 我不是故意伤你的心的。";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "嗯, 其实我更常笑自己, 而不是笑别人。 对不起, Mary, 我不是故意伤你的感情的。";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "没关系, Aurélie。 请——继续说吧, 对吧。 我出生后, 我的父母发生了什么事? ";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "之后? 哎呀, 亲爱的, 他们俩能活到那时候简直就是奇迹! 那年六月的夜里, 暴风雨有多可怕你知道吗? 等到天亮, 小船把你母亲带到了内环, 起初几乎没人敢相信自己的眼睛——一个即将分娩的女人竟然能在那样可怕的海难中活下来。 可怜的特蕾莎, 我到现在还记得那一幕, 就像昨天发生的一样…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Teresa? 她是叫这个名字吗? ";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "是的, 她就是这么介绍自己的——而这几乎是她说过的全部话。 到了那天结束时, 她就开始发烧, 一直到分娩都没有退烧。 没人确定她能挺过去, 更别说孩子能不能活着出生——毕竟她经历了那么多。 但特蕾莎挺过来了。 她挺过来了——然后她就去世了。 愿上帝安息她的灵魂…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "母亲去世了, 只剩下我和父亲? 可为什么大家都说我是被Eric Udett养大的? 还有…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, 亲爱的, 我不是说过了吗…… 别一下子问我这么多问题…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "对不起, Aurélie, 我刚才有点激动, 对吧。 我的父亲, 他也经历过海难, 不是吗? ";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "你父亲…… 你知道吗, 其实我对你父亲没什么好说的——除了我真不希望谁有那样的老爸。 你刚出生没几天, 他就消失了, 把你一个人丢下自生自灭。 还好Eric心肠那么好, 温柔善良——就像泡在朗姆酒里的饼干一样软…… ";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "至少告诉我他的名字, 对吧! ";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "哦…… 到底是Jeffrey还是John呢, 要是我能记起来就好了…… ";
			link.l1 = "所以, 你不记得了? 好吧, "+npchar.name+"? ";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "你在怀疑我的话吗, 小伙子? ! ";
			link.l1 = "安静点, "+npchar.name+", 别激动。 我没想冒犯你。 只是我觉得你对那些日子记得挺清楚的, 就这样。";
			link.l1.go = "Oreli_45";
			link.l2 = "我没有任何怀疑, "+npchar.name+"。 我只是想把所有细节都记清楚——就这样。 不过, 这一切混乱确实让事情变得有点复杂。";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "记忆可是个善变的女士, "+pchar.name+", 总是挑三拣四的。 尤其是这么多年过去以后。 特蕾莎确实难以忘怀——我整整一周都看着她受苦! 哎呀, 我当时真的很心疼她! ";
			link.l1 = "她丈夫呢, 不是和她在一起吗? ";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "记忆可是个善变的女士, "+pchar.name+", 总是很挑剔。 尤其是这么多年过去了。 特蕾莎很难让人忘记——我整整一周都看着她受苦! 哎呀, 我真的很心疼她! ";
			link.l1 = "她丈夫呢, 不是和她在一起吗? ";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "很少见到。 他大部分时间都不在——那时候岛上药品和药剂很紧缺, 他总是在外面寻找…… ";
			link.l1 = "所以, 他一定是个好丈夫——如果他曾试图帮助自己的妻子的话。";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "他也许是个好丈夫, 对吧。 我可从没说过不是, 我得说明白这一点。 别想歪曲我的话, 小子! ";
			link.l1 = "我从来没想过这种事, 我发誓, "+npchar.name+"。 很明显你对他评价不高。 而且你甚至连他的名字都记不住…… ";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "我在 'Ceres Smithy' 船舱的黑暗中, 瞥见过那个人一眼, 几乎只是个影子——那里现在是Jürgen先生住的地方。 他只在夜里来, 我几乎记不清他的脸。 至于他的名字——没人叫过他的名字, 只用姓氏。 不是 'Casper这个' , 就是 'Casper那个' …… ";
			link.l1 = "我明白你的意思, "+npchar.name+"。 所以Mary出生后, 没过几天他就消失得无影无踪。 他是被杀了吗? ";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "这个问题可不好回答, 小伙子。 你看, 在这个地方想藏点什么真不容易——大家都盯着呢。 每次哪怕船里又吵了一架, 第二天整个岛上的人都知道了。";
			link.l1 = "难怪。";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "被杀者的尸体并不总能被找到——老手们会把他们沉到水底, 把炮弹或石头绑在手脚上, 或者用链弹缠住。 水底的螃蟹会把剩下的事办完。 不过, 受害者的随身物品迟早总会以某种方式重新浮出水面。";
			link.l1 = "从底下? ! ";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "当然不是! 我的意思是那些东西只是引人注意——比如戒指、带雕刻的手枪、仪式用的军刀…… 这些东西很少有人会追问。 人都已经回不来了, 谁也不想再惹更多麻烦, 对吧? ";
			link.l1 = "Geoffrey 或 John Casper 有什么特别的随身物品吗? ";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+", 愿上帝保佑你——我连他的名字都记不清了, 你还问我这种问题! 如果真的发生了什么事, 我可从没听说那东西落到岛上其他人手里。 那时候我在酒馆当女侍, 几乎没有什么八卦能逃过我的耳朵, 对吧? 但这也不代表我什么都知道。";
			link.l1 = "当人们说某人消失得无影无踪时, 通常是指他们已经被杀了。 但是在Casper先生的情况里, 你显然并不那么确定…… ";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "我只是说, “失踪”不一定就等于“死了”, 对吧? 尤其是在那个年代, 满载走私犯和销赃者的塔塔纳帆船经常在这座岛和古巴之间来回航行…… 你知道吗, 我记不清他的脸了, 但他的眼睛…… 那是个无论在哪儿都不会迷路的男人的眼神。 或者至少, 他自己是真这么相信的。";
			link.l1 = "塔塔纳斯, 塔塔纳斯…… 没有什么是不可能的。 如果我们知道他的名字, 就可以查查那些年殖民地的档案。 不过如果我们知道他“抵达”时乘坐的船型和船名, 那就容易多了。";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "你干嘛这么看着我, 小伙子? 你以为我会记得那事吗? ";
			link.l1 = "我们也希望如此, "+npchar.name+"——毕竟你已经告诉了我们这么多。";
			link.l1.go = "Oreli_56";
			link.l2 = "嗯…… 我对此很怀疑。";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "也许你想问她有多少门大炮, 口径是多少, 对吧? 亲爱的, 你知道这些年来有多少船在这里沉没了吗? 你觉得我还能都记得清楚吗, 对吧? 再说了, 那艘船幸存下来的人屈指可数——她在海面上撑了一天都不到, 你懂的…… ";
			link.l1 = "我明白了…… 嗯, 这也说得通, 毕竟已经过去二十年了。 谢谢你至少还记得我们当时被告知的事情。";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "也许你想问她有多少门炮, 口径是多少, 对吧? 亲爱的, 你知道这些年有多少船在这里沉没了吗? 你觉得我还能都记得清楚吗, 对吧? 再说了, 那艘船只有少数人活了下来——它在水上撑了一天都算不错了, 对吧…… ";
			link.l1 = "我明白了…… 嗯, 这也说得通, 毕竟已经二十年了。 谢谢你至少还记得我们当时被告知的那些话。";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "我希望你不是在开玩笑, 也不是在取笑一个记性已经千疮百孔的老太太。";
			link.l1 = "一点也不, "+npchar.name+"。 你真的帮了我们大忙。 祝你早日康复。 好了, 我们这就走了。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "所以, Teresa…… 她就是这个名字。 可怜的妈妈, 对吧…… ";
			link.l1 = "嗯, 至少现在我们知道你那股劲儿和倔脾气是从哪来的了。 怀孕的女人还在下沉的船上…… 光是想想就让我起鸡皮疙瘩。";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "可她怎么会那副样子待在这艘船上, "+pchar.name+"? ! 光是想那么做都得疯了吧! ";
			link.l1 = "只有你的父亲能回答这个问题——John、Jack、Jacob、Jasper、Jordan…… ";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "你是在努力回忆所有以 'J' 开头的英文名字吗? Aurélie只提到了Geoffrey和John, 知道了吗。";
			link.l1 = "也许她只是忘了剩下的部分, 就像我一样, 对吧? 你懂的, 年纪大了什么的…… ";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", 你觉得…… ";
			link.l1 = "我现在可不太信得过她的记忆。 不过即便如此, 我们还得查的不只是殖民地的档案, 还要查1638年的海军档案, 这可难多了: 那些记录是机密的, 尤其涉及军官的时候。 而且我非常怀疑有哪个普通水手能偷偷把自己老婆带上船。";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "另一方面, 想查到一名军官的信息比查一个普通水手要容易得多。";
			link.l1 = "如果你知道那艘船的名字。 或者它的全名。 而不是只有 'Geoffrey 或 John, 或者最糟糕的, Jack…… ' 。 那还是我们运气好, 船是海军的船。 商船的船员名单可比这还要糟糕得多。";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "但是我们接下来该怎么办, "+pchar.name+"? 再去找Aurélie聊聊吗? 我们能从她那儿得到的都已经问出来了, 对吧? ";
			link.l1 = "不是和Aurélie。 是和Donald。";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "那他怎么帮我们呢? 他自己说了, 1638年他根本没在公正岛附近, 对吧。";
			link.l1 = "但是这里还有其他独角鲸, 对吧? ";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "我其实没太明白你的意思, 对吧? ";
			link.l1 = "你会看到的, 亲爱的, 你会看到的。 我们还有一根线可以拉, 对吧? 走吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "哦, 又是你啊! 怎么样, 你的搜寻进展得如何? ";
			link.l1 = "你好, "+npchar.name+"。 情况还能更好点——现在我们就像在这个充满秘密和谜团的洞穴里乱转。 不过我觉得出口已经很近了, 对吧。";
			link.l1.go = "Grinspy_32";
			link.l2 = "也向你问好, "+npchar.name+"一开始我可没想到会这么好。 看来…… 情况其实没那么绝望。";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "听到这个我很高兴, 真的。 可你们俩又需要我帮忙了, 对吧? 你们查到什么了? ";
			link.l1 = "Mary是在这个岛上出生的, 时间是1638年6月。 她的母亲Teresa在生下她后不久就去世了。 她的父亲——一个叫Casper的男人——在Mary出生几天后就神秘失踪了, 杳无音信。 我们只知道, 他的名字是以 'J' 开头的。 有人说, 他并没有在本地浅滩里变成螃蟹的食物, 而是乘走私贩的塔尔坦船离开了这个岛…… ";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "听到这个我很高兴, 真的。 可你们俩又有事要找我, 对吧? 那你们发现了什么? ";
			link.l1 = "Mary是在岛上出生的, 时间是1638年6月。 她的母亲Teresa在分娩后不久就去世了。 她的父亲——一个名叫Casper的男人——在Mary出生后几天内就神秘失踪了, 毫无踪迹。 关于他, 我们一无所知, 只知道他的名字是以 'J' 开头的。 有人说, 他并没有在本地浅滩变成螃蟹的食物, 而是乘走私贩的塔尔坦船离开了岛上…… ";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "那你就把你女儿丢下了吗? 这可真奇怪。";
			link.l1 = "没错。 不过, 除了这位J先生, 没人能解释这件事。";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "你觉得他还活着? 所以你才在找他吗? ";
			link.l1 = "不仅仅是为了那个。 我们想知道他是谁, 他是怎么生活的。 这对Mary来说非常重要。";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "嗯, 我明白了。 很抱歉我真的帮不上你…… ";
			link.l1 = "其实, 你可以的。 告诉我, 独角鲸们确实有记录在那个岛上失踪的船只, 对吧? ";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "我不太明白你的意思, "+pchar.name+"。";
			link.l1 = "Greenspy, Greenspy…… 别忘了你现在还能坐在那个位置, 全都是因为我。 给我个面子——别考验我的耐心。";
			link.l1.go = "Grinspy_38";
			link.l2 = "我相信你明白的, Donald。 看在我们的友谊份上, 你不会试图回避这个问题。";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "嗯…… ";
			link.l1 = "船只时不时会被冲到外环。 有些马上就沉了, 另一些还能漂一阵——这些船会被搜查, 把值钱的东西都拿走。 我不太清楚Rivados的情况, 但我怀疑Narwhals不会为了船上的每一件小玩意儿争来争去——更可能是所有东西都归入一个公共池子, 然后把所有战利品统计一遍, 只有在那之后才分赃。";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "嗯…… ";
			link.l1 = "有时候船会漂到外环。 有些船马上就沉了, 有些还能漂一阵子——这些船会被搜查, 所有值钱的东西都会被拿走。 我不太清楚Rivadans的情况, 但我觉得Narwhals应该不会为了船上的每一件小玩意儿争来抢去——更可能是所有东西都先集中到一起, 然后他们会做个详细清单, 只有在那之后才会分赃。";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "你可不傻, "+pchar.name+"。 不像这里的很多人, 对吧? 好了, 大致就是这么回事。 我个人真受不了这些文书工作, 但这规矩早在Alan Milrow那会儿就有了, 甚至在他之前的Narwhal家族首领也都是这么做的。 我们一直保留这些记录——而且不止如此: 连Rivados或者海盗们最先登上的船只我们也会登记。 不过这种情况下, 我们当然就不知道船上到底是谁或者装了什么了…… ";
			link.l1 = "从Mary的父母在船难后被带到Ceres铁匠铺这一事实来看, 应该是Narwhals发现了他们的船。 也就是说, 应该会有相关的记录。";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "也许吧。 我说不准。 而且我永远都不会知道。";
			link.l1 = "现在我不明白你的意思, "+npchar.name+"。";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "失踪船只的日志。 Dodson离开后, Layton Dexter成为海军上将, 他把那些文件从我们这里拿走了。";
			link.l1 = "就这么拿走还没收了? 你都没反对吗? ";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "首先吧, 他还算有礼貌。 其次, 他答应很快就会还回来。 第三嘛…… 我干嘛要在乎那些破文件啊? ";
			link.l1 = "还不算是最没用的笔记, 对吧。";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "我跟你说啊, 这只是个传统, 主要是为了防止我们家族的人为了船上的战利品自相残杀。 一艘船被冲上岸, 我们就把能拿的都拆下来, 列个清单, 分一部分, 剩下的藏进货舱——就这么简单。 干嘛把柜子塞得满满的? 现在柜子里空了点——我想我甚至该感谢一下海军上将呢。";
			link.l1 = "好, 明白了。 那我们就航向 'San Augustin' 吧。 不过也许我们还会再来看你, "+npchar.name+"。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "啊, "+pchar.name+", 快进来, 快进来。 你是有事找我, 朋友, 还是只是顺路来打个招呼? ";
            link.l1 = "这次是正事。 可以说, 这很私人。";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "看你这么激动, 这事对你来说也挺重要的吧。";
            link.l1 = "真的吗? 要我说, 更像是累了。 这几天我可是把你的地盘逛了个遍, 我的关节都开始抗议了——而我还傻乎乎地以为, 只有像你这样的老头才会遇到这种事呢。";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "只是有点喘不过气来, 就这样。 你看, 我可不是整天坐在椅子上的那种人。 倒是你啊, 我看你都快站不住了, 哈哈哈! ";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "你有没有想过为什么我一直坐在这把椅子上, 嘿? 你知道吗, 一旦你明白了健康是花再多岛上的财富都买不到的, 你对人生的看法就会完全变了。";
            link.l1 = "有意思——我来这儿就是想说这个的。";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "那你有没有想过为什么我一直坐在这把椅子上, 嘿? 你知道吗, 当你意识到健康是买不到的, 就算拿这座岛上所有的财富也换不来, 你看待世界的方式都会变, 对吧? ";
            link.l1 = "有趣, 这正是我来这里想说的, 对吧? ";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "关于我的健康? ";
            link.l1 = "不是, 是关于那座岛的财富。 或者更准确地说, 是关于他们的库存。 要说得再精确一点, 是关于记载这些库存的账本。";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "咳咳…… "+pchar.name+", 我有点没听明白你说的, 对吧? ";
            link.l1 = "不久前你从独角鲸那里拿走了那些在岛上搁浅船只的航海日志…… ";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "所以, 那个蠢货Greenspy居然真的让你去追他们? 胆子真大。";
            link.l1 = "完全没有, "+npchar.name+", Donald跟这事一点关系都没有。 我是带着这个问题去找他的, 他把我介绍给你了。 不过你的反应嘛, 我得承认, 真的让我觉得有趣。 能说说你为什么需要独角鲸的记录吗? ";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "那你为什么不告诉我呢? 你应该已经猜到了吧, 我对那些船本身一点兴趣都没有, 对吧? 说实话, 我对他们船舱里装的宝藏也没多大兴趣。 这里的东西够大家分了, 只要你别太贪心——我是这么想的, 对吧? 我真正感兴趣的是武器: 火枪、军刀…… 还有大炮, 最后还是大炮。 好吧, 那些聪明的家伙有时候连大炮都带走。 那些脑袋空空的黑鬼可没那脑子, 不过独角鲸们…… ";
            link.l1 = "所以你决定看看Greenspy的人们到底有多准备好迎接新一轮的冲突? ";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "还有就是暗示我和我的船员都在留意着呢。 这个信息已经很明显了, 不过考虑到Donald那套演习闹得跟马戏团一样, 他要是觉得我在惦记他的钱, 我也不会意外。";
            link.l1 = "嗯, 我看得出来事情并没有按你希望的那样发展, 对吧? 那Rivadose呢? Black Eddie有没有惹什么麻烦? ";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie…… 那些卑鄙的黑人——难怪Shark那么恨他们。";
            link.l1 = "所以这让你感到愉快。";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "就是这样, 不, 骗你我就天打雷劈! 那些黑皮肤的家伙都安静下来了, 缩在他们的船上…… ";
            link.l1 = "那你到底在烦什么啊, "+npchar.name+"? ";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "我该怎么跟你解释呢, "+pchar.name+"…… 你看, 这就像大海上的风。 有时候很温柔, 有时候很猛烈, 有时候甚至会变成真正的风暴。 但无论如何, 风总会推动船前进, 而好船长懂得如何驾驭它。";
            link.l1 = "温和的微风总比狂暴的风暴要好。";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "好吧。 不过有时候, 真的一点风都没有。 死一般的平静——任何船长都无能为力。 你只能坐在后甲板上, 盯着海面发呆, 琢磨接下来到底会发生什么鬼事。 Eddie和他那哥们Chimiset也是一样——他们肯定在搞什么鬼, 我全身都能感觉到, 绝对没好事, 我敢对天发誓! ";
            link.l1 = "也许你该动动屁股, 和Edward当面谈谈, 对吧? 或者更好, 把你们三个都叫上, 再带上Donald, 大家开诚布公地聊一聊。 这总比让岛上再次血流成河要强得多, 对吧? 好了…… 咱们回到我来这儿的正题吧。";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "所以你对独角鲸的宝藏感兴趣, 对吧? 你希望在那里找到什么呢? ";
            link.l1 = "我对这里失事船只的名单很感兴趣, 特别是1638年的。 事情是这样的, 我们正在寻找关于Mary父母的信息。 她母亲的情况还算清楚, 但她父亲就说不准了。 关于他的细节非常模糊——我们甚至连名字都不知道, 唯一的线索就是1638年六月在外环触礁的那艘船的名字…… ";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "高尚的目标——我自己也曾经因为不知道自己的父亲是谁而苦恼过。 不过恐怕我帮不了你。";
            link.l1 = "那是为什么呢, 如果你不介意我问的话? ";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "对你没有秘密, "+pchar.name+"。 这根本不是关于我的事, 是关于Donald的——他只给了我1651年以后的文件。 我问他有没有更早的记录, 至少是上一个十年的, 他说没有其他文件了。 关于这件事, 他就只继承了Alan Milrow留下的这些——至少他是这么说的。";
            link.l1 = "我觉得他没有理由撒谎。";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "我也这么觉得, 朋友。 毕竟他把新账本交给我时, 连一个问题都没问。 其实, 我觉得他甚至还有点高兴能甩掉那些破烂…… 谁知道呢, 也许Milrow只是把几十年前的文件处理掉了…… 烧了, 或者也许…… ";
            link.l1 = "不, 这不可能。";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "不, 不可能。 Alan才不会做那种事呢。";
            link.l1 = "你为什么这么肯定, "+npchar.name+"? ";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "我一直以为他更像是那种刀斧手, 而不是搞什么官僚那一套。 居然还会认字, 真让我吃惊, 对吧? ";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "他对关于这座岛的每一份记录都非常用心, 对吧? 他把它们当作岛屿故事的一部分。 而历史——不仅仅是这个地方的历史——才是Alan真正的热爱, 对吧? 他能找到的每一份史料和书籍都要研究一遍…… 有时候我觉得, 他其实更适合当学者而不是战士——我还真有一次这么跟他说过, 对吧? ";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "他对关于这座岛的每一份记录都格外用心。 他把它们当作岛屿历史的一部分。 而历史——不仅仅是这里的历史——才是Alan真正的热情所在, 对吧。 他能找到的每一份史料、每一本书都要研究…… 有时候我觉得, 他当学者比当战士更合适——有一次, 我还真这么跟他说过。";
            link.l1 = "也许他当初真的该选眼镜、纸和羽毛笔, 而不是剑和手枪——谁知道呢, 说不定他现在还在这些破烂船甲板上踱步呢。 可如果Milrow真的那么喜欢档案, 那他把那些记录放哪儿了? 就算他偶尔不小心把墨水洒在一张纸上——可那些可有几十张, 甚至上百张, 对吧? ";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "我只知道他比自己的命还要看重那些文件。 也许是被人偷走了, 或者也可能是他自己交给了别人…… ";
            link.l1 = "被偷了? 谁会需要那些早就从舰桥到龙骨都被拆得干干净净的船只的信息? 送出去——这倒更有可能, 可是送给谁了, 为了什么呢? ";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "给别的历史迷吧, 哈哈哈! 我同意Charles的看法——我也完全想不到还有谁会想要那些古老的涂鸦。";
            link.l1 = "不过, 还是有人需要它们的。 我得好好想想。 好了, "+npchar.name+", 我们就不打扰你了。 我们还会再见的。";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", 很高兴又见到你。 Mary最近怎么样? ";
			link.l1 = "我们也很高兴见到你, "+npchar.name+"。 但我们的命运如何, 就看你的了。";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "不得不承认, 这是个挺有趣的开场方式。 看你们的表情, 还有点让人不安呢。";
			link.l1 = "别害怕, "+npchar.name+", 这又不是你的错, 对吧。 我们只是有点跑累了, 在这些吱吱作响的沉船里转来转去的。 而且今天真闷热, 你不觉得吗, 对吧? ";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "这鬼天气一点都没给我们加分, 对吧? 更别说我们还得满岛找你——现在真的很需要你的帮忙。";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "咳嗯, 好吧, 现在来一阵微风就太完美了。 那, 你找我有什么事吗? ";
			link.l1 = "你看, Mary和我开始调查, 就是想弄清楚二十年前发生了什么。";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "咳嗯, 好吧, 现在要是来点微风就太完美了。 那, 你找我有什么事吗? ";
			link.l1 = "你看, Mary和我开始调查, 就是想弄清楚二十年前发生了什么。";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "听起来挺有意思的。 到底是关于什么的? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "我的父母, Antonio。 Charles和我正试图查明他们到底是谁, 还有他们身上发生了什么。 我母亲是在生我的时候去世的, 这点我们已经查清楚了。 但我父亲的事情可没那么简单…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "你是哪一年出生的, 提醒我一下…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "于1638年。 六月。";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "那时候我才十二岁, Mary。 那些日子我其实记得不是很清楚。 当然, 现在偶尔也会有一些回忆闪现脑海, 但说实话, 要把它们拼凑起来真的有点难。 很抱歉, 我恐怕帮不上你…… ";
			link.l1 = "我们并不太需要你做这个, Antonio。 但是如果你还记得Mary出生那天的任何事情, 我们会非常感激。";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "那我怎么帮你, "+pchar.name+"? ";
			link.l1 = "你跟我说过你对历史感兴趣。 不只是世界历史, 尤其是这座岛的历史。";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "这是真的。 我把能找到的书都读了, 能拿到的手稿也都研究过了…… ";
			link.l1 = "我们说的是那些手稿。 除了你之外, 岛上只有另一个人对历史和你一样充满热情…… ";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milrow。 好吧, 我们早在他还没忙着制定消灭Rivadan人、后来又要对付海盗的计划时就谈过这事了。 他是个聪明的人, 确实有些了不起的本事。";
			link.l1 = "毫无疑问, 那小子确实与众不同。 他手上有些东西, 或许对咱们有用。 而在正义岛上, 这东西对别人都没什么实际用处, 只有你们俩例外。 那些在岛附近失事船只的航海日志, 上面有打捞出来的货物和贵重物品的描述, 甚至可能还有乘客的名字…… ";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "没错。";
			link.l1 = "所以, 你看到他们了? ";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "我不仅看过那些日志——还把里面的信息抄进了我自己的笔记。 在我们的一次谈话中, 他偶然提到了这些日志的存在, 我就向他要来研究——我正试着整理类似 '正义岛编年史' 那样的东西, 而那些记录对我帮助很大。 \nAlan对我写下这个地方的历史的想法感到非常兴奋。 确实, 他没有把所有记录都给我, 把1650年代的那几本留给了自己, 但那时候, 其余的内容对我来说已经足够了。";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = "1638年的那些记录还在, 对吧? 拜托, 快告诉我还在, 好不好! ";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "我这里有一大堆这样的航海日志——最早可以追溯到1620年。 Alan说, 就是从那时候开始, 他们才有了这些记录。 对了, 1638年的也有, Mary。";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "你会让我们看看它们吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "看起来我也没得选啊, 哈哈哈! 等一下。 它们都在这柜子最下面的抽屉里。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = "请随意。 看看四周吧…… ";
			link.l1 = "我们就这么做。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "喏, "+pchar.name+", 你看, 对吧! Joshua和Teresa Casper! 简直不敢相信——我们成功了, 真的成功了, 对吧! 而且船的名字叫 'Wrangler' ! 现在我们可以查清楚我父亲的一切了——他是谁, 他怎么会来到这里…… ";
			link.l1 = "我担心, "+npchar.name+", 你太着急了…… 事情可能没你想的那么简单。 陛下的军舰…… 我们得好好想想, 谁能帮我们从皇家海军档案馆弄到情报…… ";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "想想看! 再多想想我们就能搞定了, "+pchar.name+"! 最难的部分已经过去了, 对吧! ";
			link.l1 = "也许和Young先生还有Friddick先生谈谈也有道理。 不过, 我不记得岛上有这两个名字的人。";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "因为他们不在这里, "+pchar.name+"。 那两个人在和Casper一家一起获救后的第二天夜里就死了。";
			link.l1 = "真奇怪。 那个孕妇又活了一周, 而皇家海军的两个水手却突然死了…… ";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = "他们当时就已经很糟了, 我记得。 现在我想起来了, "+pchar.name+"——其实当时我就在 '刻瑞斯铁匠铺' 附近, 他们被带上船的时候…… 好吧, 我是在 '埃斯梅拉达' 号上——我记得是和奥雷莉·贝尔坦一起。 奇米塞特也在场——就是那些黑皮异教徒的萨满, 不知怎么他也来了铁匠铺。 起初我还以为那两个水手已经死了——但他们其实是一天后才死的…… ";
			link.l1 = "嗯, 这也没办法。 不过我们已经学到了不少。 谢谢你的帮助, Antonio。";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = "这事和我没关系, "+pchar.name+"。 都是Alan干的, 都是他的主意——那些胸甲骑兵里几乎没人能真正明白这些记录的价值。 毕竟, 正是这样的文件让我们能够拼凑出历史的全貌! ";
			link.l1 = "我希望有一天我和Mary能一起读你的编年史, 伙计。 给你日记——可别弄丢了。 好了, 我们该走了。 也许我们还会再见, 朋友。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "因为他们不在这里, "+pchar.name+"。 那两个人在被和Casper一家一起救出来的第二天夜里就死了。";
			link.l1 = "真奇怪。 那个孕妇又撑过了一周, 但皇家海军的两个水手却突然死了…… ";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "很高兴又见到你, 朋友。 你来这里有什么事吗? ";
			link.l1 = "带着一个请求, "+npchar.name+"…… 或者说, 是个问题。";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "请提你的问题, 或者说出你的请求。 我会尽我所能帮你的。";
			link.l1 = "好吧。 你在这座岛上住了多久了? ";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "几十年又几十年了, 朋友。 我小时候就被带到这里了, 不过那时我已经很机灵——是在一艘奴隶船上。 我的故事和你在这里听到的许多其他人并没有太大不同。 一场暴风雨, 一次船难…… 我被关押的那艘英国大帆船甚至没能驶出外环, 就被海浪推到礁石上, 撞成了两截。";
			link.l1 = "你是怎么活下来的? 那些暗礁离外环很远啊, 说实话, 能在狂风巨浪中闯到这里, 可不是件容易的事…… ";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "那天晚上, 诸神站在我这边。 我设法挣脱了镣铐, 然后抓住了一块曾经属于船的残骸。 有个部落人和我在一起, Asana——我们一起与浪搏斗, 直到筋疲力尽昏了过去。";
			link.l1 = "你是被冲到其中一艘船上的吗? ";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "是啊, 我们钻进了货舱里的一个洞…… 我又晕过去了, 实在太虚弱了, 对吧? 等我醒来的时候, 阿萨纳已经开始尖叫——一只巨大的螃蟹爬上了我们搁浅的那艘船, 正把他撕成碎片。 我就那样站着看着, 明知道下一个就是我——被恐惧和无助冻住了, 连动一下都做不到, 对吧? ";
			link.l1 = "你本来可以试着帮你的朋友的。 但是那样的话, 我们现在就不会在这儿聊天了, 对吧? 所以你是怎么逃出来的? ";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "你运气不错, 他没先拿你开刀, "+npchar.name+"。 那你是怎么逃出来的——你是跳回水里游走的吗? ";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "阿萨娜的尖叫声被几个rivados听到了, 他们是在最近一场飓风后出来搜刮船舱的人。 他们包围了那头野兽并将其杀死。 没人能帮得了阿萨娜, 但我就幸运多了。 我就是这样来到这里的。 现在轮到你了, 我的朋友——你为什么想知道这一切? ";
			link.l1 = "其实, "+npchar.name+", 我本来想问的不是你怎么到这儿来的, 而是你是什么时候到这儿的。";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "阿萨娜的惨叫声被几名利瓦多斯人听到了, 他们在最近一场飓风后外出猎取船货。 他们包围了那头野兽并将其杀死。 阿萨娜已经无力回天, 但我就幸运多了。 这就是我为何会出现在这里的原因。 现在轮到你回答了, 我的朋友——你为什么想知道这一切? ";
			link.l1 = "其实, "+npchar.name+", 我本来想问的不是你怎么到这儿来的, 而是你是什么时候到这儿的。";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "嗯, 按照你们的历法, 那是在1623年, 夏末——我也只能说得这么具体了…… ";
			link.l1 = "没那个必要。 那么, 1638年时, 你已经在岛上待了十五年了。";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "看起来是这样, 朋友。";
			link.l1 = "那年六月, 飓风把 'Wrangler' 号双桅船冲上了外环——那是查理一世国王舰队的一艘船。 船员中只有四人生还——其中就有Mary的父母: Joshua和Teresa Casper。";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "好吧, 我记得这事, 朋友。 虽然有点模糊, 就像隔着一层雾, 但我确实记得…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "你真的记得吗? 那快告诉我! ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "我不能多说。 四个人: 一名军官, 他的妻子, 还有两个水手。 那女人当时怀孕了, 救她的人都以为她撑不到天亮——但她却像母狮一样坚强, 而那两个水手不到一天就离开了人世…… 我见过他们: 虽然很虚弱, 但身上还是有点生气的…… ";
			link.l1 = "你是说他们被杀了吗? ";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "如果是这样的话, 那就既没有目击者, 他们身上也没有伤口, 我的朋友…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "你说 '军官' , 好吧…… 我父亲真的曾是军官吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "他穿着军官制服——每当我试图回忆他的样子时, 这大概是我唯一记得的。";
			link.l1 = "如果他是个军官, 那他肯定也穿不了别的衣服——我怀疑他的衣柜能有多丰富…… 也许你还记得其他细节, "+npchar.name+"? 有什么特别的特征…… 比如说, 脸上有疤, 或者其他伤痕之类的…… ";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "我记得的不多, 朋友。 他的面容几乎已经从我的记忆中消失了——毕竟已经过去二十年了…… 但他的目光——我却记得太清楚了。 我只和这个人说过一次话, 但他那双灰色的眼睛——和Mary的一样——我永远都不会忘记。 那里面有绝望, 有像被逼入绝境的羚羊一样的恐惧, 同时——还有堪比雄狮的愤怒与决心…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "你跟他说过了, 对吧? 说了什么? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "这事发生在你出生前几个小时。 他来了这里, 来到 'Protector' , 坚持要见我。 Rivados的首领Mogedi被他的大胆惊呆了——但我却突然对这个男人产生了兴趣。 当他站在我面前时, 他跪倒在地, 求我救救他的妻子…… 在他们短暂逗留期间, 有人设法把我的事告诉了他。 我答应了, 尽管Mogedi反对…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = "所以, 我欠你一条命, 对吧? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "没有必要撒谎——我们确实找到了你母亲, 但已经太晚了: 独角鲸号的人不让我上 'Ceres Smithy' 。 你父亲设法…… 说服了他们, 但我见到可怜的Teresa时, 她已经在咽下最后一口气。 她生下了你, 如果我能早点赶到, 也许还能救她, 但是…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "妈妈死了, 对吧。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "唉。 她看了你一眼, 吐出了最后一口气。 但在那之前, 仿佛鼓起了全身的力气, 她大声呼喊着一个叫鲁珀特的人。 她用尽全力喊出了他的名字, 像是在呼救——然后她就死了。";
			link.l1 = "Ruperta? 不是Joshua? ";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "在我跟你讲这些的时候, 朋友, 我感觉自己又重新经历了一遍那个时刻。 我永远都不会忘记——无论是她临死前的尖叫, 还是她因痛苦而扭曲的脸。 没错, 她嘴里最后喊出的, 就是 '鲁珀特' 。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "我母亲漂亮吗? Chimiset, 你能描述一下她长什么样子吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = "没必要了, Mary。 你只要照照镜子就知道——你和她简直一模一样。 你从你父亲那里继承的, 只有那双犀利的眼神。 ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "那他呢, 他怎么样了? 我们查到就在我出生后没几天, 他就神秘消失了, 对吧! 可他没被杀, 对吧? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "一听说Teresa快不行了, Joshua就勃然大怒——我发誓, 就算是草原上的狮子猎食时都没有你父亲追那些不让我上长笛号的独角鲸时那么疯狂…… 得有六个人才能把他按住——而且那还是在他把两个穿着盔甲的族里战士扔进水里之后。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "那他们对他做了什么——快告诉我, 快点! ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "他们把他扔进了 'Tartarus' 号上的一个牢房。 没有人敢审判他——他们想让这件事先平息下来…… 几乎所有人都为他感到惋惜, 但很少有人愿意和这样的人一起生活。 几天后, Joshua就消失了——差不多就在那时, 有几艘走私船离开了岛上。 没有人看到他在那些船上, 这也就成了他死讯流传的开端。";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "所以你觉得他还活着, 对吧? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "我只说一句别人肯定也会告诉你的话——从来没人找到过他的尸体。 也许他真的藏在某条小船底下了, 或者他们在牢房里割了他的喉咙, 把他喂给了螃蟹…… ";
			link.l1 = "他消失的时间正好和那些商人起航的时间一致, 这更倾向于第一种可能——世上哪有这么巧的事。 也许他曾向某人透露过自己的计划? 如果他真是逃跑了, 那他就真的跑了, 把刚出生的女儿留在这里, 这么做也有他的道理——一个婴儿很可能撑不到坐那种破船去古巴…… 但他肯定是打算回来接她的。";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "我可不清楚, 朋友。 那时候如果Joshua Casper和谁说过话, 也只能是他的狱卒——不过他们早就离开了这个罪恶的世界。 哦, 对了, 有一天Domingo神父来看过他——在Julian修士之前, 他是白人的神父…… ";
			link.l1 = "他是打算忏悔什么吗? 估计是怕逃跑的时候死掉, 对吧? ";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "我不知道的事, 我可没法给你解释, 对吧, 朋友。 Domingo也不会告诉你什么——他大概十五年前就死了, 对吧。 也许是被人敲了脑袋, 也许就是喝酒喝死的——他可是挺爱喝的…… ";
			link.l1 = "不过也许Domingo记了日记…… 或者他把和Joshua的那次谈话告诉了他哥哥Julian? ";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "我们得和他谈谈, "+pchar.name+", 对吧。 越快越好。 我甚至都不想在解决这事之前回船上去。";
			link.l1 = "如果还有什么没弄清楚的地方。 Julian 可能自己都不知道——但我们一定会查个水落石出, 没问题。 谢谢你, Chimiset。";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "我永远为你效劳, 我的朋友。 不过让我给你们俩一个建议。";
			link.l1 = "那是什么样的呢? ";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "你外出打猎时, 别走得太深进灌木丛——否则可能再也找不到出路了。";
			link.l1 = "我们会记住的, 萨满。 现在——再见。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "欢迎来到上帝的庇护之所, 孩子们。 你们是来忏悔, 还是只是想祈祷? ";
			link.l1 = "你好, Julian兄弟。 我担心要列举我们所有的罪行恐怕太花时间了——可惜我们并没有那么多时间。 不过请放心——作为虔诚的天主教徒, 我们每到一个港口都会去教堂。";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "你好, Julian兄弟。 让我们以对主的祈祷, 作为虔诚天主教徒, 开始一天, 也以同样的方式结束一天。";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = "虔诚的天主教徒, 未婚却同居一屋檐下…… 这简直是亵渎啊, 孩子。 让我提醒你, 这可是死罪! ";
			link.l1 = "难道《圣经》不是说, 爱能遮盖一切罪吗? ";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = "虔诚的天主教徒却未婚同居在一个屋檐下…… 这简直就是亵渎啊, 孩子。 让我提醒你, 这可是死罪! ";
			link.l1 = "难道《圣经》不是说, 爱能遮盖一切罪吗? ";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "爱就是要遵循主的戒律——我需要提醒你这些戒律吗, 孩子? ";
			link.l1 = "改天再说吧。 我们这次是为别的事来的。";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "迷途的灵魂永远不嫌晚回归正道…… 不过我在听你们说话, 孩子们。";
			link.l1 = "我们确实有点迷路了, Julian兄弟。 迷失在过去的荆棘中。 我们希望你能帮我们找到回到光明的路。";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "很机智, 孩子。 你要记住, 引领人走向光明的不是人, 而是主——当你跟随祂时, 要记得祂的道路是神秘莫测的。";
			link.l1 = "我长话短说, Julian兄弟。 我们正在尽力查明Mary父母的所有情况。 关于她母亲Teresa, 基本上已经清楚了——她和丈夫一起抵达这座岛, 不久后一周因难产去世。 但她父亲…… Mary出生几天后就消失了, 从 'Tartarus' 逃了出来。 传言说, 他在这里最后见过的人是Domingo神父——也就是你的前任。";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "那你们可晚了十五年以上了, 孩子们。";
			link.l1 = "是的, 我们知道那位神父早在很久以前就去世了。 而那时候, Julian兄弟, 你还太年轻, 还没以正式的身份来到这座岛上, 对吧? ";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "他去世几年后, 我最终来到了这里。 在这艘船上把一切都整理好花了我不少力气, 但在上帝的帮助下, 我还是做到了, 孩子。";
			link.l1 = "你在这里处理事情的时候, 有没有碰巧发现过Domingo神父的记录? ";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "你是指什么特别的事情吗, 孩子? ";
			link.l1 = "我们正在找日记或者某种航海日志…… 希望能有奇迹出现的可能性很小, 不过神父也许在他的笔记里记录下了那次谈话的内容。 我们认为Mary的父亲是乘走私船离开岛上的——也许他曾暗示过神父, 他要去哪里, 以及什么时候会回来接他的女儿? ";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "我从来没找到过什么日记之类的东西, 这点可以肯定, 不过倒是有各种各样的记录…… 说到教会的事, 他可真是一丝不苟——不是每个主的仆人都这么较真。 他的文件里只有干巴巴的数字和名字——就这些。";
			link.l1 = "据我们所知, Joshua Casper——他就是这个名字——在妻子去世后, 一时愤怒之下, 杀了两名拒绝让rivados巫师Chimiseta见Mary母亲的Narwhal家族成员…… ";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "他们的表现简直就是教会的好孩子! 宗教裁判所的地牢正等着这个魔鬼的仆人呢! ";
			link.l1 = "天啊, 我想如果上帝知道有多少人是以祂的名义被折磨的, 祂一定会感到震惊。 Casper算是幸运的——他们只是把他扔进了 'Tartarus' 号的牢房, 但他最终也没能等到审判。";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "是的, 是的, 毫无疑问。 Casper被关进了 'Tartarus' 号的牢房, 但并没有被判刑——并不是所有人都谴责一位失去妻子的丈夫的行为。";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "接下来发生了什么——那个异教徒逃走了吗? ";
			link.l1 = "不到一周后, Joshua就消失了。 就在前一晚, Domingo神父去找过他。 那么问题来了——为什么呢? Casper肯定是新教徒, 不太可能会向天主教神父忏悔——对吧? ";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "接下来发生了什么——那个异教徒逃走了吗? ";
			link.l1 = "不到一周后, Joshua就消失了。 就在前一晚, Domingo神父来见过他。 所以问题是——为什么? Casper肯定是新教徒, 不太可能会向天主教神父忏悔——你觉得呢? ";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "回归真正的信仰永远不嫌晚, 孩子。 不过你的推理很有道理。 如果他不需要忏悔, 也许他是在和神父商量他妻子的葬礼——当然, 前提是她是天主教徒。 或者是关于他女儿的洗礼, 或者更确切地说, 是拒绝洗礼, 因为新教徒不为婴儿施洗, 他们认为一个人必须独立且有意识地做出接受洗礼的决定。";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "但是我受过洗礼, Julian兄弟。 Eric Udett跟我说过这事。";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "那只是我的猜测, 孩子。 真相我并不知晓。 主只会让我们看到真正重要且必要的事物。";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "对我来说就是这样, 对吧。 也许在Domingo神父的记录里还有什么你没注意到的东西, Julian修士? 毕竟你只是随便翻了翻, 对吧? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "那里本就与我无关, 孩子。 我看得出来, 你为此已经努力了很久, 而且非常用心——主正在引领你走上这条荆棘之路。 如果你注定要找到你所寻求的东西, 那便是主的旨意, 我也不该阻拦。 我可以把你出生那年Domingo的记录给你; perhaps you'll find something useful in them.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "那你可真是太慷慨了, Julian兄弟。 你还保留着1638年的记录吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "哎呀哎呀……  (吹掉灰尘) 。 看来就是这个了。 1638年主历的账本。";
			link.l1 = "请允许我, Julian修士…… ";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "看, "+pchar.name+": 8月3日。 那天是我和法比安受洗的日子。 我是6月22日出生的。 不过关于我父亲的事, 一句话也别说, 好吗。";
			link.l1 = "正如Julian修士说的——除了枯燥的数字和名字, 什么都没有。 有趣的是, Domingo神父在履行职责时非常热忱, 甚至还为新教徒做了临终祈祷——我可怀疑van Ekkus、Young和Friddicks是不是天主教徒。";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "他们很可能就在即将进入天国的门槛上皈依了真信仰, 孩子。";
			link.l1 = "当然了, Julian兄弟——他们还能怎么办? 尤其是如果他们像Soren和Rojas那样死去——我猜这些正是拦住Chimiset去路的独角鲸。";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "要是Domingo神父把中间名全写出来就好了, 对吧。 母亲名字和我名字后面的 'V.' 和 'J.' 到底是什么意思啊? ";
			link.l1 = "那这个 Fabian 呢, 就是和你同一天受洗的那个人? ";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "塞西尔·加拉尔的儿子。 哦, 我刚想起来! 她把我养大了, 虽然她从来不怎么亲热。 大概是因为我活下来了, 而法比安没能活下来。 他出生几个月后就死了, 对吧。";
			link.l1 = "也许我们该去和她谈谈, 毕竟这本小册子几乎没让我们学到什么有用的东西——除非你把你的出生和受洗日期也算进去。";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "她其实比Aurelie也没小多少, "+pchar.name+"。 我们只能希望她至少头脑清醒点, 对吧? 不过你打算问她什么呢, 对吧? ";
			link.l1 = "嗯, 既然她曾是你的保姆, 她可能从Domingo神父那里听说了他和Joshua谈话的一些细节。 要不是她, 他还能告诉谁呢? 也许Aurélie或者Eric也知道。 但我觉得我们已经从前者那里问出了所有能问的东西, 而后者嘛, 恐怕再也不会告诉任何人什么了。";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "这位善良的女士是这座上帝之家的虔诚信徒。 她从未错过任何一次弥撒, 还经常去忏悔。 我相信她真的能帮助你们, 孩子们。";
			link.l1 = "谢谢您, 神父。 再见。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+"和Mary Casper。 真是个令人愉快的惊喜! ";
			link.l1 = "我也是, "+npchar.name+"。 其实, 我们是特意来找你的。 有件事想和你谈谈。";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "哦, 真的吗? 好吧, 你现在完全吸引了我的注意力。";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "这是关于我父母的事, Cécile。 关于我母亲, 我们已经能查到的都查清楚了…… 她在我出生后就去世了。 可我父亲…… 他在几天后就神秘消失了, 连一点线索都没有。 我们一直觉得他没死, 对吧。";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = "嗯, 把那样的人送去见阎王, 可真不是件容易事, 对吧…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "你看到他了吗? ! 你和他说话了吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "我的姑娘, 我亲眼看见他徒手干掉了两头独角鲸, 差点儿…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "索雷诺和罗哈斯? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "那时候我忙得不可开交, 哪有空记住那些混蛋的名字——现在我一点也想不起来了。";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "好吧, 没关系。 请继续, Cécile。";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "那还能怎么继续? 他把那两个人扔下了海, 他们像石头一样沉了下去, 然后他们就把他绑起来拖到 'Tartarus' 号去了。 这样做才对——谁知道那个恶棍还会想淹死谁呢…… ";
			link.l1 = "杀人犯? 这说得有点过分了吧, Gallard夫人? 我们说的是一个男人啊, 一个刚刚失去妻子的军官, 对吧…… ";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "我看你对他评价不高——可不是每个军官都会被这样议论的。";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "军官啊, 呵呵。 我还记得他的制服, 确实挺特别的, 几乎是全新的。 不过啊, 年轻人, 我这辈子见过的军官可不少。 每一个都比那位…… 先生要体面得多。";
			link.l1 = "他还有做别的事吗? 除了杀了那两个人? ";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "军官啊, 呵呵。 我还记得他的制服, 真是特别, 几乎全新, 像是刚从裁缝手里做出来的。 不过啊, 年轻人, 我这辈子见过的军官可不少。 他们全都比这位…… 先生要体面得多。";
			link.l1 = "他还做了什么吗? 除了杀了那两个人? ";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "他在牢房里要求见一位神父——De la Cruz神父…… ";
			link.l1 = "哟, 你看看! 这正是我们想和你谈的事, 对吧? 你知道那次谈话的细节吗? ";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "当然啦, 小伙子! 那个新教徒混蛋竟然要求神父不要给他女儿施洗——尽管她母亲是爱尔兰人, 所以是天主教徒。";
			link.l1 = "我几乎是第一次听到一位英国女士这样谈论新教徒…… 咳, 打扰了, "+npchar.lastname+"夫人。";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "我以前也是新教徒, 没什么好隐瞒的。 不过Julian修士还是把我带回了正道。";
			link.l1 = "原来如此…… 真是上主的忠实仆人。 不过我们有点跑题了。 所以, Casper希望他的女儿在新教信仰中长大。";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "这正是他对我们的De la Cruz神父说的话。 而且他还命令他们给那个女孩取名叫Julia…… ";
			link.l1 = "原来'J.'代表的是这个。 Mary Julia Casper…… 可那他们为什么叫她Mary呢? ";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "因为那是她母亲的心愿, 就是这样。 当女孩从她母亲腹中被取出时, 她轻声说了一个名字——Mary。 我当时没能亲眼见证, 不过Aurélie Bertin在场。 你要是想知道, 可以去问她…… ";
			link.l1 = "所以你还是听了你母亲的意思, 对吧? ";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = "那还能怎么样呢, 对吧——所谓的父亲就这么凭空消失了, 对吧? ";
			link.l1 = "考虑到…… De la Cruz神父的本事, 就算他一直待在Tartarus号上, 我也怀疑他的意见会有多大用处。 Domingo没告诉你——他根本不知道Casper打算逃跑, 或许还会回来找那个女孩? ";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "也许你说得对。 不过, 说回多明戈神父和Casper先生的谈话——神父有没有提到Joshua是否和他谈过逃跑的事, 或者他什么时候可能会回来找他女儿? ";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = "他从来没提过这种事。 好吧, 你自己想想, "+npchar.name+", 如果你打算越狱, 你会跟第一个遇到的陌生人说吗? 那家伙绝对不会的, 我跟你说。";
			link.l1 = "所以, 这条线索也没什么结果。 嗯, 谢谢您的时间, "+npchar.lastname+"夫人。 回头见。";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = "他从来没提过这种事。 你想想看, 对吧, "+pchar.name+", 如果你打算越狱, 你会一见到陌生人就把这事说出来吗? 那家伙绝对不会这么做, 我跟你说。";
			link.l1 = "所以, 这条线索果然是死路一条。 嗯, 谢谢您的时间, "+npchar.lastname+"夫人。 回头见。";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "我们发现了不少有趣的事情, "+pchar.name+"。 但其实进展不大, 对吧。";
			link.l1 = "我们甚至还纠缠在一起过呢。 我倒想知道, 你母亲临死前喊的那个鲁珀特是谁? ";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "也许是兄弟, 或者…… 一个亲密的朋友? ";
			link.l1 = "朋友, 你说的啊…… 我倒想知道Joshua是不是早就知道他了…… ";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "你想说什么, "+pchar.name+"? ";
			link.l1 = "我们得好好把这一切想清楚, 对吧? 幸好我们还有大把时间, 一边找能帮我们的人一边慢慢想。 我们已经做了不少了, 对吧? 但还没完全结束呢。 我们自己进不了皇家海军办公室, 而且那地方远在伦敦的另一头…… 你觉得有谁能帮我们吗, 对吧? ";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "那Serge Benoit呢, Charles? ";
			link.l1 = "修道院院长? 他人脉确实广, 这倒是真的, 但我怀疑他能不能进皇家海军档案馆。";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "如果他自己做不到, 也许他会帮我们联系能做到的人, 对吧。";
			link.l1 = "我想是吧。 那我们就去圣皮埃尔。";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "现在我们只能等了, 对吧。";
			link.l1 = "我相信他一定会查明一切的, "+npchar.name+"。 时间很快就会过去, 你都不会察觉。 现在嘛——我们还有事情要做。";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "你是在暗示什么特别的事情吗, 亲爱的? ";
			link.l1 = "我们还有很多事要做, 不过要不要先回船上, 把门锁好, 咱们俩好好待一会儿? 你觉得怎么样? ";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "我就知道你会这么说, 对吧! 我的意思是: 咱们别浪费时间了! ";
			link.l1 = "来吧, 亲爱的。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "哎呀, "+pchar.name+", 你根本不知道, 你真的不知道我心里的大石头终于落地了, 对吧! ";
			link.l1 = "我能想象得到, 亲爱的——你简直在发光呢, 哈哈! 你看吧, 一切都值得了。";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "我父亲可是个有名的军官, 你能想象吗! 可惜我们从未见过面, 对吧…… 而且我们甚至都不知道他有没有抵达大陆, 唉…… ";
			link.l1 = "如果真那样, 他肯定会重新服役, 对吧? 总会有人在某个地方听到他的消息。 那样的人绝不会安分坐着——不然你又是从哪儿听说的呢? ";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "你真的觉得他死了吗? 他是落到了古巴西班牙人手里, 还是在正义岛被杀了? ";
			link.l1 = "我试着直面真相, "+npchar.name+"。 那些年, 至少和那个岛还有点联系, 对吧? 走私贩们总是很规律地驾着他们的塔尔坦船去那里。 如果他真的离开了那个岛, 我毫不怀疑, 过一段时间他一定会回来找你的。";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "把我从那里救出来。 不过那样我们就不会相遇了, 对吧。";
			link.l1 = "这就是人生嘛, 亲爱的。 你永远不知道会在哪里得到什么, 或者会在哪里失去什么。 希望你现在和我在一起不会后悔, 对吧? ";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "我这辈子从没听过比这更荒唐的事, 对吧! "+pchar.name+", 你真是太棒了, 太厉害了! 谢谢你这么努力帮我把这一切理清楚。 这对我来说真的很重要, 对吧! 不过我们还是看看这些文件吧——也许能发现我们那位朋友没告诉我们的东西…… ";
			link.l1 = "好主意。 我们现在就开始吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "那么, "+pchar.name+", 你有没有发现什么有趣的事情? ";
			link.l1 = "好吧, "+npchar.name+"。 有件事…… ";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "你这表情像是见了鬼, 对吧。";
			link.l1 = "它提到了一个叫 Rupert Northwood 的人。";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood? ! 真的是他吗? ";
			link.l1 = "安静点, "+npchar.name+", 别这么大声嚷嚷。 嗯…… 我觉得是的, 就是Chimiset说的那个人。 不会有错——哪有这么巧的事。";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "那你怎么看这一切, "+pchar.name+"? ";
			link.l1 = "这故事越来越复杂了, 对吧? 所以……  '康沃尔号' 从普利茅斯起航,  '康沃尔号' 也抵达了安提瓜, 但却是 '斗士号' 在正义岛的礁石上触礁——掌舵的还是同一个约书亚·卡斯帕, 他居然瞒着海军部偷偷娶了个女人, 而那个女人在临终时还在呼唤一个叫鲁珀特的人。";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "我完全不明白是怎么回事。 我甚至不知道还有谁能帮我们了解他。 我们越是想查清我父亲的事, 就越是陷进这个秘密和谜团的泥潭里, 对吧。";
			link.l1 = "如果有人能对此有所解释, 不是Joshua Casper, 就是Rupert Northwood。";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood? 可他已经死了, 对吧。 你不会真的以为 'Cornwall' 号抵达圣约翰时递交的报告全是谎言吧? ";
			link.l1 = "哎呀, 你这天真劲儿, "+npchar.name+"…… 我都开始觉得这整个故事里全是谎言了。 你想想看: Joshua Casper可是模范军官——奖章一大堆, 连个处分都没有。 这跟我们在公正岛上了解到的他可完全对不上号, 对吧? 他在那儿连眨眼都不带就把两个人送进了坟墓, 你不觉得奇怪吗? ";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "他为了他妻子的生命而战斗, 我的母亲, "+pchar.name+"! ";
			link.l1 = "当然啦, 不过咱们想想看——她到底是从哪儿冒出来的? 更重要的是, 他为什么要对海军部隐瞒自己的婚姻? 他可是个彻头彻尾的军人, 对职责和规章一丝不苟——不然档案也不会那么干净——可突然之间, 就发生了这种事。";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "要是这一切背后真的有个美丽又浪漫的故事呢? 这种事虽然很少见, 但也不是没有, 对吧。";
			link.l1 = "别误会, Mary, 但这听起来一点都不像爱情故事, 更像是一场表演, 我到现在都搞不明白你们到底是为了什么。 为什么在去Providence的路上要给船改名? 那可是军舰啊, 这种行为会让你上军事法庭的。";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "同意——好问题。";
			link.l1 = "而且这个Rupert Northwood明显有问题, 对吧。 那场战斗死了快一半的船员, 可奇怪的是, 没有一个军官死——除了他。 而且你母亲临终前, 为什么叫的是Rupert, 而不是她自己的丈夫Joshua? ";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "所以, 你真的确定大副不是死于和西班牙人的战斗, 对吧? 而且我根本不是Joshua Casper的女儿, 而是Rupert Northwood的——你就是这个意思, 对吧? ";
			link.l1 = "就像我之前说的——只有一个人知道真相。 要么是Joshua Casper, 他不知为何称Teresa为妻子; 要么是Rupert Northwood, 他同样莫名其妙地用了他船长的名字。";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "真是乱成一团啊, 对吧! 那我们现在怎么办, "+pchar.name+"? 现在我更想查明真相了, 对吧? 可我们已经把所有人都问得一干二净了。";
			link.l1 = "如果还有什么答案可寻, 那一定在正义岛——除了大洋彼岸, 已经没有其他有人烟的地方了, 或许那里有人曾经认识你的父母, 哪怕只是一瞬间。 我觉得我们应该再去找Aurélie Bertin谈谈——也许她还能想起什么我们能抓住的线索。";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "但是你还想从她那里打听什么呢? 她知道的好像都已经告诉我们了。";
			link.l1 = "她只是把我们问的都告诉了我们, 其实很可能漏掉了什么重要的细节。 也许你父亲脸上有疤, 或者手上少了一根手指…… 我很怀疑, 能想出那么多花招——比如改船名, 甚至可能连自己的名字都换了——的人, 会就这么无声无息地死在某个岛上, 或者卡斯蒂利亚人的地牢里。";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "也许你说得对…… ";
			link.l1 = "如果我们决定继续寻找——不是在海军部那些落满灰尘的书架上, 而是在这片群岛里——我们可不能只靠一个名字, 还是个假名字, 对吧。";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "你知道吗, 这一切让我起鸡皮疙瘩了, 对吧。 也许是因为太…… 刺激了, 或者也许是想到我父亲可能和Bishop庄园里的那个混蛋其实没什么两样, 对吧。";
			link.l1 = "总之, 我保证我们会尽全力查明真相。 别再浪费时间了, 走吧! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "走吧, "+pchar.name+", 我们别再浪费时间了, 对吧。";
			link.l1 = "我希望Aurélie在她的船舱里, 这样我们就不用在整个岛上到处找她了…… ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "看来我们又没运气了, 对吧。 这次她会去哪儿呢? ";
			link.l1 = "我希望她的脑子没有又被病魔侵蚀…… ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "哦, 你又来了。 嗯, 你好…… 怎么了, 又需要Aurelie了吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "不得不承认你挺机灵的, Jillian。 你不会正好知道她在哪儿吧? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "在教堂, 她正准备忏悔。 如果你快点, 就能在那里找到她。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "嗯, 她既然能忏悔, 那肯定是神志清醒、记忆无碍的, 对吧。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "很难说…… 这三天来, 她一直不太对劲, 怎么都安不下来。 你知道吗, 不知为什么, 她看到你们船的桅杆出现在外圈之外时, 突然变得特别激动。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "我倒想知道这是怎么回事? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "嗯, 我猜她一想到又要被你盘问就觉得不安吧。 不过你什么时候在乎过别人的烦恼呢, 对吧? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "别敢那样跟我说话, Jillian。 这次老子就饶了你, 但要是你再敢说出类似的话…… ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "多紧张的人啊, 只要事情不顺她就一直神经兮兮的, 对吧? ";
			link.l1 = "没必要无缘无故去招惹她, "+npchar.name+"。 你知道她可不是只为了好看才带那把刀的。";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "你就会眼睁睁看着那发生吗, "+pchar.name+"? ";
			link.l1 = "你只是还没见过Mary打架, "+npchar.name+"。 否则, 他们就不会自欺欺人地以为有人或什么东西能拦得住她了。 我们还会再见的。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "你大概想问我什么吧, "+pchar.name+", 对吧…… ";
			link.l1 = "说实话, 我并不在乎你们俩之间发生了什么, 不过我大概能猜到她叫什么名字。 或者说, 她以前叫什么名字。 你真的想谈谈这事吗? ";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "你和Jillian闹矛盾了吗? 或者说, 是为了某个人, 对吧? ";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "嗯, 其实也不是, 没有。";
			link.l1 = "你说什么都行。 现在我们去找Aurelie吧。";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "那个小吸血鬼永远不会原谅Alan选择了我而不是她。 其实她本可以释怀的, 毕竟他现在已经不在了…… 说实话, "+pchar.name+", 我还是不想谈这个, 好吗。";
			link.l1 = "如你所说, 亲爱的。 那我们去找Aurelie吧。";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary! 你回到岛上了, 真是太高兴了! ";
			link.l1 = "很高兴看到你身体安好, "+npchar.name+"。 其实, 我们来这座岛就是为了再和你聊聊。 不过别担心, 不会耽误你太久。";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "哎哟, 年轻人啊, 你们可真不懂得怜香惜玉。 不过我早就感觉到你会来的。 又是你父母的事, 对吧, Mary, 好吧? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "拜托了, Aurélie。 我知道过了这么久你很难想起来, 但请再为我试一次, 好吗。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "我已经把我记得的都告诉你了。 我真不知道你还想从我这儿榨出什么来。";
			link.l1 = "我们有几个问题要问你, "+npchar.name+"。 请你尽量回忆一下——任何细节, 哪怕是一点点都好。 我们不会强迫你的…… ";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "这不正是你现在正在做的事吗? ";
			link.l1 = "你已经为我们做了这么多, "+npchar.name+"…… 我们只希望在你记忆的迷宫深处, 还能找到什么能大大帮助我们的东西。";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "我们已经走了很长一段路, "+npchar.name+"。 你根本无法想象我们付出了多少努力和时间。 但是我们迷失了方向, 只有你和你的记忆才能带我们回到真理的道路上。";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "回忆…… 其实还能剩下什么呢。 有些早晨我连自己的名字都记不清, 你还想让我回忆二十年前的细节。 好吧, 你问吧。";
			link.l1 = "我们对Casper先生, 也就是Mary的父亲感兴趣。 你还记得他外貌上有什么特别的特征吗? 也许他脸上有疤, 或者走路一瘸一拐的…… ";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "记忆啊…… 其实还能剩下些什么呢。 有些早晨我连茅房怎么走都记不清了, 你还想让我回忆二十年前这些沉船上发生的细节。 好吧, 行吧, 问吧, 随你问。";
			link.l1 = "我们对Casper先生, 也就是Mary的父亲感兴趣。 你还记得他外貌上有什么特别的特征吗? 也许他脸上有疤, 或者走路一瘸一拐的…… ";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "哦…… 我想我已经说过了, 我只是在 'Ceres Smitty' 号船的货舱里、漆黑一片的时候见过他, 那时他们给可怜的Teresa铺了张床。 他绝对没有跛脚——相反, 他还挺敏捷的。";
			link.l1 = "他的年纪呢? 他是年轻, 还是已经上了年纪? ";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "我倒不觉得他算是个老头, 对吧…… 不过我其实没怎么注意他——我更担心Teresa。 他看起来挺憔悴的, 像个鬼似的。 可你得记住, 这一周他几乎都没怎么睡觉, 因为他老婆快要生了…… 他整个岛上跑来跑去, 一刻都没停下。";
			link.l1 = "所以, 他一定很爱他的妻子吧。 你和她相处了很长时间, 对吧? 她有没有提起过她的丈夫? ";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "特蕾莎一直在问他。 她经常睡觉, 有时候会说胡话, 但每当她清醒过来, 第一件事就是问他在哪里。 可怜的她真的等了他很久很久。 可是在最关键的时刻——他却始终没有出现。";
			link.l1 = "我明白了。 很明显, 他们是两情相悦…… 嗯, 谢谢你, Aurélie。 你帮了我们大忙。";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "就这样? 我还以为我们能聊上至少一两个小时呢。";
			link.l1 = "我们确实答应过不会打扰你太久。 保重, "+npchar.name+"。 多保重。";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "等等, 年轻人们! 我还有别的东西要给你们…… 或者说, 是给你, Mary。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "给你, 姑娘, 拿着吧……  我一看到你船上的风帆, 就把这顶帽子带在身边, 好让我不忘记它。 不过要走到码头上…… 我却没敢。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "怎么了, Aurélie? 一顶帽子? ...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "你母亲的帽子, 是Teresa的。 那次船难幸存者被带到 'Ceres Smithy' 时, 她还戴着呢。 Teresa去世后, 我从她床边的地上捡起了那顶帽子——好吧, 然后我就把这事忘了…… 直到今天和你聊天时才想起来。";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "奥蕾莉…… 你这些年一直都保留着! 而且…… 你没有扔掉, 也没有卖掉…… 谢谢你, 谢谢你! 你根本不知道这对我有多重要, 对吧! ";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "对不起, Mary——我早就该把它给你了…… 可我现在的记性就像个破筛子——所以…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "没有比现在更好的时机了, Aurelie! 我现在就试试, 好吧! ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "亲爱的, 你觉得我怎么样呀? ..";
			link.l1 = "你真漂亮。 还有这顶帽子…… 现在还没过时, 对吧, 所以看起来也很棒。";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "真的吗? 你喜欢我太高兴了, 对吧! ";
			link.l1 = "还能有别的办法吗? ";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "再次感谢你, Aurélie——你让今天变得更美好了! 祝一切顺利, 好好休息。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "所以真的是鲁珀特。 鲁珀特·诺斯伍德, 对吧。";
			link.l1 = "很明显啦, 亲爱的。 为了救他的妻子…… 或者是心上人, 他已经尽了全力, 对吧? 我也不确定啦, 其实也没那么重要。 重要的是, 现在我们知道要找谁了。";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "但是, 'Cornwall'号真正的船长Joshua Casper发生了什么事? ";
			link.l1 = "好问题, 不过现在不是最重要的, 对吧? 如果 Rupert 那么爱 Teresa, 为什么他没回来找你——这才更有意思。 等我们找到他, 如果他还活着, 这就是我们要问他的第一件事。 有一点可以肯定——他从没回到舰队。 他没有理由冒这个险。";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "是什么让他取了约书亚·卡斯帕这个名字? 在 '康沃尔号' 上发生了什么, 后来它变成了 '争斗者号' ? 我父亲真的可能是个罪犯吗, "+pchar.name+"? ";
			link.l1 = "我担心我们也不能排除这种可能性, "+npchar.name+"。 我们得做好万全准备。";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "我甚至都不想去想那个…… ";
			link.l1 = "现在我们得考虑别的事——去哪儿找他。 他可能加入了海盗或者走私贩。 也许他在某个城镇安顿下来, 低调行事。 什么都有可能。";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "那你说我们该怎么办? 我们要怎么找到他? 难道要跑遍每个殖民地, 把他的名字说一遍, 然后指望有人听说过Rupert Northwood? ";
			link.l1 = "或者是Joshua Casper。 他完全可能以他前任船长的身份继续生活——那位船长很可能已经死了。 不过这样做有一定风险, 因为可能会有人开始寻找那艘失踪的双桅船。 尤其是因为船上还有一箱准备送往Providence驻军的白银。";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "你说得对, 对吧。";
			link.l1 = "不过, 鲁珀特·诺斯伍德, 据说是在亚速尔群岛附近失踪的, 恐怕也不会引起谁的兴趣。 不过, 这里面肯定有什么值得深思的地方。";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "我们还要在这上面花多少时间啊, "+pchar.name+"? ! 他可能在任何地方, 任何殖民地, 对吧! ";
			link.l1 = "如果他活下来了, 当然啦。 不过我不同意你的看法, 对吧? 他大概西班牙语说得不流利, 这就意味着他根本不该去古巴或者伊斯帕尼奥拉。 他会说法语, 可以去托尔图加, 或者小安的列斯群岛的某个殖民地。 也有可能他在大陆上定居, 投靠同胞的庇护。 我们真的可能要花好几个月去找他——而且还不能保证一定能找到, 对吧? ";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "但是我不想放弃, "+pchar.name+"。 现在可不是时候, 咱们已经学到了这么多, 对吧! ";
			link.l1 = "我可从没这么说过, "+npchar.name+"。 我们没必要自己去找他——还是找个有门路的人帮忙更好。 之前试过一次, 既然有效, 为什么不再试一次呢? ";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "你是说我们还要再去找住持帮忙吗? 我记得他已经说得很清楚了, 这件事别指望他再帮忙了, 对吧。";
			link.l1 = "那样对那位老头确实有点太放肆了, 你说得对。";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "但是那我们该找谁呢? 谁有钱有关系能办这种事? ";
			link.l1 = "嗯, 这搜查肯定得我们自己出钱了, 对吧? 至于人脉…… 我想Fadey Moskovit也许能帮我们。 他肯定认识一些能在殖民地跑腿的能人对吧? 或者他会给我们指个路也说不定。";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "所以, 我们要去Basse-Terre, 对吧? ";
			link.l1 = "好吧, 我们去见见我们的朋友。 如果你问我, 对他来说这好像不算什么难事, 对吧? ";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "明天我们起锚出发, 怎么样, 对吧? 我想把今天剩下的时间和今晚都和你一起度过, 就我们两个人, 在 'Ceres Smitty' 号上。";
			link.l1 = "没人会拒绝这样的提议, 亲爱的。 我们确实该好好休息一下了。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "什么, 你这么快就要离开这座岛了? 连葬礼都不打算参加吗? ";
			link.l1 = "葬礼? ..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "哦, 原来你还没听说。 我明白了…… Aurélie Bertin昨晚去世了。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "什么? ! 这不可能——我们昨天才刚和她说过话, 她当时还好好的。 还是说有人…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "不, Mary。 Aurelie是在睡梦中去世的。 我今天去看她, 想给她带些Julian修士做的关节药膏——就是那时我发现她的。 她躺在床上, 脸上带着奇怪的微笑。 但她已经脸色苍白, 身体冰冷了。 \n过去这一周, 老太太一直有些反常, 我甚至以为那个被黑巫师驱走的病又回来了。 但她的头脑还算清醒, 看上去也没有胡言乱语。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "至少她没有受苦, 对吧。";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "那你会留下来参加葬礼吗? 葬礼明天在最远的礁石上举行——那里水够深, 螃蟹也不会爬那么远。";
			link.l1 = "我们会留下, Jillian。 Aurélie为Mary做了那么多, 我们实在不能做别的。 如果没人反对, 我们就在我们的船上举行仪式。 我们会以最高的礼仪将她海葬。";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "没人会反对。 这样更方便, 而且最终比爬过残骸要安全。";
			link.l1 = "那你就去安排葬礼吧, Mary会帮你的。 至于我, 我得和某人谈谈…… ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "你又来了, 我亲爱的朋友! 这次有什么可以帮你的? ";
			link.l1 = "你好, "+npchar.name+"。 你听说昨晚发生了什么吗? ";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "你是在说Aurelie的死吗? 我看得出来你就是在说这个, 对吧? 我当然听说了。 她住在 'Pluto' 号上, 那几乎就是Rivadose的地盘。 其他船上的人也都只谈论这件事。";
			link.l1 = "我们就在昨天还见过她, 她身体很好——当然, 除了她整周都在为某事担心。 而且当她看到我们的船时, 情绪变得更加激动了。";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "一个人能感觉到自己生命之河快要干涸的时候。 有些人会让身边所有人都看出来, 有些人则把它藏在心里, 但每个人都会以某种方式察觉到——尤其是那些懂得倾听自己内心的人。";
			link.l1 = "我觉得她身体很健康, 几乎像只小鹿一样, "+npchar.name+"。 可这里总觉得哪里不对劲…… ";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "可她显然还没到山穷水尽的地步, "+npchar.name+"。";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "朋友, 心灵和身体完全是两种不同的存在。 心灵支配着身体, 而有时候身体也会试图控制心灵。 它们关系紧密, 但其实并非真正合为一体。 一个人外表看起来很健康, 可他的灵魂也许早已走在死亡的道路上了。";
			link.l1 = "你很聪明, 我的朋友, 非常聪明。 如果你觉得真相就在眼前, 你就会像狮子追斑马一样追着不放——直到抓住为止。 我一见到你就看出来了, 就在我们初次见面的那一刻。";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "朋友, 心灵和身体是完全不同层次的东西。 心灵支配着身体, 而有时候身体也会试图控制心灵。 它们紧密相连, 但其实并非真正合为一体。 一个人外表看起来很健康, 可他的灵魂也许早已踏上了死亡之路。";
			link.l1 = "你知道吗, 我突然想到, Aurelie好像一直在等我们, 就像她早就知道我们会来找她一样。 那位老妇人本可以早一天或晚一天去世, 但她偏偏就在告诉我们关于Mary父亲的重要事情后没多久就去世了。";
			link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "你很聪明, 我的朋友, 真的很聪明。 如果你觉得真相就在眼前, 你就会像狮子追斑马一样追过去——而且在抓到它之前绝不会停下。 我第一次见到你时就意识到了这一点。";
			link.l1 = "我没有…… 等等。 你在 'Protector' 号船舱里做的那个仪式…… 其实并没有减缓Aurelie的病情, 对吧? 那你到底做了什么? ";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "你可以用石头填满一条河, 但那并不能阻止它的流动。 我知道你需要从Aurelie那里得到一些重要的东西——而且你不会立刻得到它。 但你的旅程会花多长时间, 我无法预料。 所以我筑起了一道堤坝, 召集了她全部的生命力来抵挡病痛, 直到她完成自己的使命。 而就在那一刻, 屏障崩塌了…… ";
			link.l1 = "所以说, Aurelie…… 在她死的那一刻, 她根本就不是她自己, 她没有自我意识——就像我们想的那样? ";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "她拼尽全力只为保持头脑清醒、记忆清晰, 而当她不再需要这样做时, 病痛就像巨浪一样席卷而来, 将她带入死亡的幽谷。 她的离世是否安详, 还是被往昔的幽灵和可怕的噩梦折磨着去见你的上帝——我无法说清, 因为我并不知晓。";
			link.l1 = "你明明知道这会导致什么结果, 对吧? 你为什么没提醒我会有这样的后果? ! 快说! ";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "你很清楚自己在做什么, "+npchar.name+"。 你为什么不提醒我这会导致什么后果? ";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "因为我决定帮助你, 我的朋友, 帮你了解你需要知道的事情, 也让她完成她的命运。 如果我提前告诉你她将面临什么, 你也许就不会继续下去了——而Aurélie就会把她的秘密带进坟墓。 那又有什么意义呢? 她会白白死去。 就像一只被狮子扑倒却没被吃掉、最后被秃鹫啄食的羚羊一样。";
			link.l1 = "目的、价值…… 你还真是个掌控命运的大师, "+npchar.name+"。 人间的上帝。";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "因为我决定帮助你, 我的朋友, 帮你了解你需要知道的事情, 也让她完成她的命运。 如果我提前告诉你她将面临什么, 你也许就不会继续下去了——而Aurélie就会把她的秘密带进坟墓。 那又有什么意义呢? 她会白白死去。 就像一只被狮子扑倒却没被吃掉、最后被秃鹫啄食的羚羊一样。";
			link.l1 = "目的、价值…… 你还真是个掌控命运的大师, "+npchar.name+"。 人间的上帝。";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "我听出你声音里有些不满, 我的朋友。 不过不, 我可从没把自己当成神——相信我, 就连神也不是全能的。 无论是你信仰的那位, 还是我们崇拜的那些。 神明无法赋予一个人超越天生的力量。 我们萨满只能引导那股力量朝某个方向流动——仅此而已。";
			link.l1 = "而你让他们走上了一条注定让她送命的道路…… ";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "我只是为Aurelie指引了一条路, 而她顺着这条路, 帮助了Mary——自Mary出生那天起, 她们就有着密切的联系。 毕竟, 你的同伴就是在她眼前来到这个世界的。 拜托, 别用那种我疯了的眼神看我。 你总不会说你在我身上看到了什么善良的巫师, 能挥手让时光倒流吧? ";
			link.l1 = "我都不知道该跟你说什么, "+npchar.name+"。 也许这一切真的不是白费的。 但事情本不该这样发展的。 你本该告诉我, 而我本该自己做决定。 不过, 事已至此。 那就这样吧, 朋友, 告别了。";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "唉, 我没想到我们的最后一次见面会是这样, 朋友…… ";
			link.l1 = "你凭什么觉得她是最后一个? ";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "有些河流汇入其他河流, 成为它们的一部分, 有些则干涸了, 而有些——就像我们的——最终在壮观的瀑布中迎来终结…… ";
			link.l1 = "又来谜语了, Chimiset? 我觉得今天已经够多了。 相信我们还会再见的。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "我就知道会在这里找到你, 对吧。 你来找Chimiset干什么, "+pchar.name+"? 他跟你说了什么? ";
			link.l1 = "这并不是我所期待——或者说想听到的答案。 不过, 这件事我早就有点模糊的预感了。";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "你会告诉我的, 对吧? ";
			link.l1 = "不, "+npchar.name+"。 这次不行。 守护者船舱里说的所有话都只能留在那里, 只属于我和Chimiset之间。";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "好久没在你声音里听到这么坚定的语气了, "+pchar.name+"。 不过行吧, 我们还有别的事要操心, 对吧。 葬礼定在明天, 日落时分, 七点举行。";
			link.l1 = "来吧, 我帮你把一切都准备好。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "看起来想来的人都到齐了, 对吧。";
			link.l1 = "我还以为会有更多人呢。 至少会有些安分的人吧。";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "嗯, Kurana和Rivadose可没人请来。 Abbott那个自以为是、恶心的家伙, 说他有更重要的事要做, 没空埋葬一个天主教女人, Lauderdale和Musket也嘟囔了类似的话。 Cassel那个粗人, 直接说他不会来。 不过其他人都到了。";
			link.l1 = "有些事情我永远都无法理解。 好吧, 就让上帝来评判他们吧。 朱利安修士来了…… 现在一切都开始了。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "尽管我们的内心充满悲伤, 让我们感谢上帝赐予已故Aurélie的一切恩典, 并宣告: 我们感谢祢, 我们的天父上帝\n"
							+"感谢祢赐予Aurelie与我们共度的岁月和时光\n"
							+"感谢祢赐予她神圣的洗礼, 使Aurélie成为祢的女儿\n"
							+"感谢祢赐予她的才华与知识\n"
							+"感谢她为家人和他人所做的善行\n"
							+"感谢她对我们过错的包容\n"
							+"让我们祈求上帝, 愿祂接纳我们已故的姐妹Aurélie进入祂的荣耀, 并让我们呼求: 我们求祢, 主啊\n"
							+"愿Aurelie的善行结出丰硕的果实\n"
							+"愿她所开始的事业得以延续\n"
							+"宽恕她所犯下的罪过\n"
							+"让她的记忆永存于我们心中\n"
							+"让我们祈求上帝坚固受苦者的信德与希望, 并让我们呼求祂: 主啊, 增强我们的信心\n"
							+"因祢的圣子, 祂成为了人\n"
							+"因祢的圣子, 耶稣基督, 祂以无尽的爱爱了我们\n"
							+"因祢的圣子, 祂为我们的罪接受死亡, 并为我们的得救复活\n"
							+"因祢的圣子, 祂为我们开启了通往天堂的道路\n"
							+"让我们与所有已先我们进入天乡的信徒一同, 按照救主的教导祈祷。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "全能的天主, 请垂听我们因信仰祢复活之子的祈祷, 并坚固我们的希望, 使我们能与祢已离世的仆人一同获得复活。 以上所求, 是靠我们的主耶稣基督——祢的儿子, 他与祢及圣神同为一体, 永生永王, 天主, 世世无穷。 阿门。";
			link.l1 = "天主, 全能的圣父, 十字架的奥秘是我们的力量, 而你圣子复活是我们希望的根基; освободи усопшую рабу Твою от уз смерти и сопричти её к лику спасённых. Через Христа, Господа нашего. Аминь.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", 咱们快点去船舱吧, 对吧。 我快要哭出来了…… 我不想让别人看到我这个样子。";
			link.l1 = "当然, "+npchar.name+"。 我们走吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "只有在一个人离开之后, 你才会真正开始珍惜他们——你听说过这个说法吗, "+pchar.name+"? ";
			link.l1 = "没错——而且不止一次。";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Eric以前经常这么说。 我想他指的是他的家人。 我从没问过他关于他们的事——总觉得以后有机会聊。 结果他就这么去世了, 对吧。 现在Aurélie也走了——直到现在我才意识到, 自己给她的时间和关心有多么少, 远远不及她应得的。";
			link.l1 = "这不是你的错。 我们永远无法知道主什么时候会召唤我们所爱的人去他身边。 和他们在一起的时间永远都不够。 永远不够。";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "也许吧, 对吧。 Eric常说——Aurelie也同意他——任何地方, 最重要的首先是那里的人, 不是房子, 不是树木, 不是道路, 而是人。 你想到地图上的某个地方时, 首先记住的总是住在那里的人, 或者曾经住过的人。";
			link.l1 = "我从没认真想过这个问题。 不过也许Eric说得对——毕竟, 如果你一走进家门, 就再也见不到你的父亲和兄弟了, 那家还有什么意义呢? ";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = "我可不这么认为。 每当我回想起, 比如说巴黎——脑海里浮现的都是街头的景象、空气里的气味…… 至于那些人, 我只记得寥寥几位——剩下的人几乎都淡出了我的记忆, 明明才过去几年而已。";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "我记得Erik和Aurelie确实聊过那个岛, 对吧。 还有那些很久很久以前住在这里的人。 我那时候还只是个孩子, 什么都不懂, 但现在——我全都看明白了。 毕竟, Antonio、Cecile…… 还有像Chimisette这样的Rivadan人, 他们在这里待的时间都比我长——可我从没和他们亲近过。 至于其他人: Erik、Aurelie、Alan, 还有很多很多人——他们都已经死了。";
			link.l1 = "我明白了。 世界变得…… 是不是小了一点? ";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "我记得Erik和Aurelie确实谈过那个岛, 对吧。 还有那些很久很久以前住在这里的人。 我那时候还只是个孩子, 什么都不懂, 但现在一切都看得很清楚了。 毕竟, Antonio、Cecile…… 还有一些Rivados, 比如Chimiseta, 他们在这里的时间都比我长——不过我和他们谁都不亲近。 至于其他人: Erik、Aurelie、Alan, 还有很多很多人——他们都已经不在了。";
			link.l1 = "我明白了。 世界好像…… 变得小了一点, 对吧? ";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "更像是被掏空了。 这个世界——在外环之内。 现在已经空了, 没错。 很快——也许就会彻底消失。";
			link.l1 = "你在说什么呢, Mary? ";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "你没感觉到吗, "+pchar.name+"? 就在刚才, 我们站在Aurelie的墓前的时候。";
			link.l1 = "到底是什么? ";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "我不知道该怎么解释, 对吧? 你知道暴风雨来临前空气的味道吗? 还记得吗——你刚到这里的时候, 到处都是那种紧张的气氛…… 每个人都像要撕碎对方的喉咙, 很多人甚至觉得能闻到火药和血的味道。 你杀了Chad之后, 一切都变了——呼吸都变得轻松了…… 可现在——那种感觉又回来了。";
			link.l1 = "好吧, 我也有类似的感觉。 可也许只是气氛影响吧? 毕竟, 这可是葬礼啊…… ";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "你累坏了, "+npchar.name+"。 休息一下吧——这样会轻松些。 说真的, 谁在葬礼上能有别的感觉呢, 对吧? ";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "当我们把Eric和岛上那么多人交给大海的时候, 可不是这样的, 我跟你说。 那时候有种…… 团结的感觉。 可今天——有些人看彼此的眼神像狼一样, 虽然我们嘴上都在念同一个祷词。";
			link.l1 = "你是说Leighton和Donald? ";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "当我们把Eric还有那么多岛上的人交给大海时, 可不是这样的, 我跟你说。 那时候有种…… 团结的感觉。 可今天——他们当中有些人看彼此的眼神像狼一样, 虽然嘴上都在念同一段祷词。";
			link.l1 = "你是说Leighton和Donald? ";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "所以, 你也注意到了, 对吧。";
			link.l1 = "每当Greenspy想插手操练的时候, Dexter就会变得紧张——谁能怪他呢? ";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "这可不会有好结果, 对吧。";
			link.l1 = "如果是这样的话, 那么今天不仅是Aurélie Bertin的葬礼, 也是这座…… 被遗弃之城的葬礼。";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "被遗弃之船之城? ";
			link.l1 = "原谅我, Mary, 我实在叫不出口把这地方称作正义之岛。";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "现在我见识了外面的世界, 才发现世界有多大, 这地方感觉就像…… 监狱一样, 对吧。 真难相信我是在这里长大的。";
			link.l1 = "我简直难以相信, 在这些破败的船只之间, 竟能绽放出像你这样野性又美丽的玫瑰。";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "我想和这个地方说再见, "+pchar.name+"…… 我猜我们再也不会回来了, 对吧。 我不想回来。 我也不想亲眼看到这里可能发生的事。";
			link.l1 = "我去跟Eddie和Donald聊聊。 也许我能让他们冷静点。";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "你不明白…… 这只会拖延不可避免的结局, 所以你不用费心了。 总有一天我们会回来的——而在这里\n这样其实更好, "+pchar.name+", 对吧…… 这里已经没有什么能留住我了。";
			link.l1 = "如你所说, 亲爱的。 我们会把该做的事都做完——然后就永远离开这个地方。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "鲁珀特·卡斯帕? 约书亚·诺斯伍德, 对吧? ";
			link.l1 = "一路上我一直在想这件事, "+npchar.name+"。 我得出的结论是, 你父亲不可能用他已经用过的名字和姓氏藏起来。 与此同时, 他可能又不敢完全放弃自己的真名或姓氏: 万一在关键时刻, 他没能对假名做出反应怎么办? ";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "他怎么叫自己都行, 对吧。";
			link.l1 = "他当然有可能做到, 也许他就是这么做的。 如果他在古巴活了下来, 毕竟他是搭走私商的小型帆船去的。 如果他真的到了那里, 没有变成正义岛螃蟹的口粮。 现在我们只能等——至少不用像上次那样等那么久。 我觉得我们轻轻松松就能撑一个月。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "我父亲还活着, "+pchar.name+"。 我一直都知道的, 对吧! ";
			link.l1 = "就像我一样, 亲爱的。 好了, 是时候去见这个Jerome了——越快越好。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "终于到了, 对吧。 那么, 接下来怎么办, "+pchar.name+"? ";
			link.l1 = "我们得去找Jerome。 他不是在酒馆的某个房间里闲逛, 就是租了间房子——我敢肯定他有足够的钱, 对吧? ";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "考虑到Fadey给了他那么多钱…… 我觉得他肯定选了第二个选项。";
			link.l1 = "同意。 我们可以去问问 '玻璃眼' 的老板关于他的事, 或者就在镇上的人群中打听一下。 走吧, 时间很宝贵。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "哟哟哟…… 我们的情侣在这儿呢。 好了, 伙计们, 干完这事就回去向他汇报。";
			link.l1 = "Jerome Sauvernier? 这里到底发生了什么鬼事? ! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "啊, 你们这些混蛋, 咳咳。 嗯, 没关系…… ";
				link.l1 = "要是你还想保住小命, 最好管好你的嘴巴…… ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "这个也是。 现在说吧: 到底是什么鬼让你袭击我们——而且还和Sovereignet一起, 真是不可思议…… ";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "你的国王就是个贪婪又胆小的混蛋。 Casper只需要好好教训他一顿, 再许诺给他点钱——他立马就像个乖孩子一样, 唰唰地写好了那封信, 咳咳…… ";
			link.l1 = "所以他真的找到了。";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "找到你了, 找到你了。 所以你很快就要死了。 你那小女朋友也是一样。 Casper会把你们俩剁成碎片, 嘿嘿。 我反正也活不成了, 不过我会送你们一程。 可惜等他抓到你时, 我就听不到你求饶的声音了…… ";
			link.l1 = "好吧, 我活不了多久了, 这是真的。 快说吧, 趁我还没咽下最后一口气。";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "如果你想见他, 就去切图马尔湾吧, 那是他住的地方。 你不用找他, 他自己会来找你。";
			link.l1 = "那好吧。 现在你想死多少次都行。 我走了。";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "但愿如此。 现在下地狱去吧。";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "天啊, "+pchar.name+"…… 我简直不敢相信, 真的不敢相信, 对吧! 我爸爸竟然做了这种事? ";
			link.l1 = "看起来确实是这样, 对吧。"+npchar.name+"。 我完全不知道是什么驱使了他, 也不知道他到底是谁, 对吧…… 但我很怀疑还会有别的鲁珀特·卡斯帕。 哪有那么巧的事啊。";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "那我们现在该怎么办? 当我看着他的眼睛时, 我该说什么, 对吧? ";
			link.l1 = "首先, 我们得先找到他。 很可能他已经成了通缉犯, 因为寻找他的事让人反应那么激烈。 不过, 不管怎样, 他毕竟还是你的父亲。 为了找到他, 我们已经花了大量的精力、时间和金钱。";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "但是如果他根本不愿意和我们说话怎么办? 他为什么要下令杀了我们? ";
			link.l1 = "至少, 他可能并不清楚到底是谁在追他。 Fadey 也许只是报了你的名字, 没说关于你的细节。 否则, 我怀疑我们现在就不会不得不让刀刃沾血了。";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "那现在怎么办? 我们要去切图马尔湾吗? 可是如果他在这儿给我们设了陷阱…… 谁知道那边等着我们的又是什么? ";
			link.l1 = "在他发现这里发生了什么之前, 我们有时间优势。 我们得好好利用, 对吧? 我们会驶向海湾, 然后派一支由一名军官带队的小队陆路支援我们。";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "听起来挺合理的, 对吧? 可是谁来带头呢? ";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu。 他是陆战的老兵。 没有人能比他做得更好。";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude。 他当然不会高兴, 不过他会慢慢接受的。";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule。 他最清楚这些事该怎么做, 对吧。";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy。 就算出了什么岔子, 那家伙也会找到办法脱身, 相信我。";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway。 这不是他第一次在丛林里追踪敌人。";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso。 他刀子很快, 人也不傻, 懂吧。";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichingitu认真听着, "+pchar.name+"船长。";
			link.l1 = "朋友, 你肩负着一项重要的任务。 一伙恶棍正藏身在Chetumal湾。 你需要追踪他们并将其消灭。 我们会乘船从海上接近。";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "你会带领我们的一队人穿过丛林, 从背后包抄那些混蛋。 你有什么问题要问我吗? ";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "印第安人没有问题。 明天中午小队会到位, 在那里埋伏等待。";
			link.l1 = "很好, Tichingitu。 祝你好运。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = "船长, 你叫我了吗? ";
			link.l1 = "我有个差事要交给你, Claude。";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "我们得召集一队战士, 把他们带穿丛林去切图马尔湾。 那里有个叫鲁珀特·卡斯帕的家伙带着一帮人正埋伏着等我们。 他们想给我们个难堪的惊喜。 可实际上, 咱们才是要给他们惊喜的人——更准确地说, 是你。 等我一发信号, 你就冲上去攻击他们。 还有什么问题吗? ";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "我真讨厌在丛林里跋涉。 不过, 俗话说, 命令就是命令。 明天中午左右, 我会在那里和你碰头吧。";
			link.l1 = "祝你好运, Claude。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = "我在听呢, 船长。";
			link.l1 = "Hercule, 有个活儿给你。";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "想找人给哪个不开窍的蠢货来几颗子弹? 那就是我啦, 随时待命, 你知道的, 对吧? ";
			link.l1 = "差不多了。 你需要带领我们船上的一队人马, 从船上出发, 穿过丛林去切图马尔湾。 到了那里, 你要为那伙我认为会在那里等我们的家伙设下埋伏。";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "我还以为你在说什么正经事呢, 船长。 结果你这不是差点就提议去酒馆了吗。 明天中午前, 就当我们已经在那里了。";
			link.l1 = "我在那里等你。 祝你好运, Hercule。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = "哈, 老大, 你干嘛这么严肃啊——像是要去参加葬礼似的, 对吧? ";
			link.l1 = "还在开玩笑呢, Tommy? 要不要我也来个笑话? 你这个月的工钱没了, 下个月的也别想拿。 怎么突然这么紧张啊? ";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "我连个玩笑都开不了…… ";
			link.l1 = "凡事都有时机, Tommy。 你还有很多要学的。 现在仔细听我说: 带上你的船员, 从丛林穿过去, 前往Chetumal Bay。 到了那儿, 等我的信号。";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "穿越丛林? 我们明天中午之前都到不了, 对吧。";
			link.l1 = "那么, 咱们明天中午在那里见。 没有命令别动手, 别擅自离开岗位。 明白了吗? 我看你明白了。 现在, 去忙吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Longway正在听您说话, 船长。";
			link.l1 = "嘿, 我有个活儿要你帮忙, 对吧? ";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "你会带领我们的人穿过丛林前往Chetumal湾。 那里可能会遇到敌人, 所以一定要让你的人做好准备, 对吧。";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longway什么都明白, 船长, 您不用担心。 我们大约会在明天中午抵达目的地。";
			link.l1 = "快去吧, 小心点。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "船长, 你叫我了吗? ";
			link.l1 = "好吧。 仔细听, Alonso。";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "你会带领一队战士穿过丛林, 前往切图马尔湾。 很有可能会有一帮恶棍在那里等着你们。 等我发出信号时, 你们需要就位, 从背后袭击他们。";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "小菜一碟, 船长。 不过明天中午前别在海湾登陆——我和我的船员赶不到那么早。";
			link.l1 = "做好准备, Alonso。 愿上帝保佑我们。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, 你看见了吗, 对吧? ";
			link.l1 = "看起来他们已经在等我们了。 我敢肯定他们就在前面那个拐角埋伏着。";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "不过, 我们还没被打成筛子呢。 也没人想这么做, 对吧。";
			link.l1 = "也许他还愿意先和我们谈谈。 咱们别惹他——我们自己过去, 船员会支持我们的。 走吧, 把这一切都结束掉。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "站住! 别再往前一步! 伙计们, 要是那个花花公子敢动一下, 就把他打成筛子。 别碰那姑娘。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "爸爸? ..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = "好吧, 我这漫长又艰难的一生里, 什么没见过。 每次我以为再也没有什么能让我吃惊了——结果每次都被打脸。 所以, 你居然真的在外面活下来了…… 而且你还把Teresa的帽子带回来了。 我真没想到还能再见到它。";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = "好吧, 我这漫长又艰难的一生见过太多事了。 每次我以为再也没有什么能让我吃惊的时候——每次我都错了。 所以, 你最终还是在那里活下来了, Julia…… ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "是Aurelie在她…… 去世前给我的。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "真感人啊…… 我都快哭了。 本来我还以为他们把Teresa和它一起埋了。 自从我把它送给她后, 她可是一秒都没离身过。 你母亲, 虽然只是个女仆, 但她骨子里全是冒险精神, 简直都要从耳朵里溢出来了。 我在攻下Fleur-de-Lys时找到她, 一眼就知道Teresa会为她疯狂。 她戴那顶帽子看起来很滑稽, 但她一点都不在乎: 只有睡觉才会摘下来。 可你啊, Julia, 这帽子真的很适合你。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Julia? 不, 你搞错了, 我叫Mary…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "嗯, 是这样啊。 那些混蛋果然没听我的话, 自己擅自行动了。 哼, 对那些天主教狗也不能指望什么别的。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "你…… 你…… 你真的是我父亲吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "要不是这样, 你和你那朋友早就躺在地上变成筛子了, 对吧? 我已经很久不信上帝也不信魔鬼了, 不过也许他们真的存在, 对吧? 至少第一个肯定有——毕竟祂给了你特蕾莎的容貌, 这才救了你一命, 对吧? 人们都怎么说来着? 上帝的安排总是神秘莫测, 对吧? 哈哈哈! ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "爸爸…… 我…… 我不明白, 对吧…… ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = "你才不会懂呢, 对吧…… ";
			link.l1 = "看起来你并不高兴见到你的女儿, Casper先生。 尤其是你自己都承认她是你的了。";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "你还挺机灵的嘛, 花花公子…… 你叫什么来着? ";
			link.l1 = ""+GetFullName(pchar)+"。 在我们寻找你的这段时间里, 我们一直在想, 你这段时间都是怎么过的, 你是不是还活着。 不过我看你在这里过得挺不错的, Northwood先生。";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "啊, 连这个你都挖出来了。 好吧, 我得表示敬意, 青蛙佬先生, 我还能说什么呢——毕竟我可是确保每个细节都处理得妥妥当当的。";
			link.l1 = "不仅仅是那之前的事。 我们知道 'Cornwall' , 知道它的货物, 也知道Joshua Casper, 你曾借用过他的名字, 还有他的姓——看起来你倒是把这个姓一直留着了。";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "好极了 (鼓掌) 。 我很佩服你。 你是自己全都想明白的, 还是我的宝贝孩子也帮了你? ";
			link.l1 = "要不是有Mary帮忙, 我可做不到。 她下定决心要查清自己父母的一切。 Theresa的事不难查明, 可是找到你, 我们可花了不少时间…… ";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "这一切真让人感动, 差点把我都看哭了。 好了, 女儿, 你满意了吗? 现在开心了吧? 想不想给爸爸一个拥抱? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "我不明白, 神父…… 你为什么要折磨我? 为了什么? !  (喊叫) 是你把我丢在那里——那些沉船上! 之后你甚至从没想过要回来, 对吧! 为什么? 你到底是谁, 那些站在你身后的人又是谁? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "跟我说说, "+pchar.lastname+", 她总是这么闹脾气吗? 她这是随了她妈妈。 Teresa是个很棒的姑娘, 我遇到过最好的。 但她确实爱哭闹, 爱闹腾, 没错…… 还能说啥呢…… 爱尔兰人嘛。";
			link.l1 = "你敢侮辱她试试! Mary又没害你倒霉, 对吧? 你根本不该这样对她。";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "想让老子闭嘴啊, 小崽子? ! ";
			link.l1 = "恰恰相反。 我希望你把你的故事讲给我们听。 让Mary知道这件事非常重要。 但是我不会让你侮辱她。 所以请你自重。";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "你以为我巴不得把心里话都倒给你听吗? 我的人生就是这么走过来的, 对吧? 就像你们天主教徒常说的——上帝作证——我什么都不后悔。 除了当年因为她失去了Teresa——那是唯一的遗憾。 我恨你吗, 姑娘? 也许以前恨过, 但现在我对你毫不在乎了。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "你怪我害死了妈妈? ! 你…… 那我到底有什么罪? 是因为我出生, 对吧? 好啊, 父亲, "+pchar.name+", 对吧——你把一切都说出来, 然后我们就转身离开。 我再也不会出现在你面前了, 既然你……  (开始抽泣) 。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "好吧, 你简直和Teresa一模一样。 我感觉自己年轻了二十岁, 哈哈。 该死的你。 我根本不想回忆起这些…… 所以啊, 亲爱的, 如果等这个故事讲完我决定往你额头上来一颗子弹——那你只能怪你自己了。";
			link.l1 = "那你也会中弹的, Rupert。 我可不觉得这是你的计划——你看起来挺惜命的。";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "我知道它值多少钱, 小子。 这不是一回事。 不过像你这样的人怎么会明白呢? 行吧, 咱们直说。 你想知道我的一切? 那我就告诉你。 我是在东本恩附近的一个农场出生的——那是个坐落在海峡岸边的小镇——于1611年。 也可能早一年或晚一年——我那老妈总是把日期搞混, 这也不奇怪, 毕竟她喝下去的酒可不少。";
			link.l1 = "童年很艰难? 我明白了。";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "既然是你自己问的, 那就听好了, 闭上嘴, 别耍聪明。 我从来没有父亲, 甚至都不知道为什么——但和你不一样, 小姑娘, 我根本不在乎这个。 我从他那儿得来的姓氏对我来说挺合适的。 我十三岁那年, 有一晚敦刻尔克的私掠者在海岸登陆。 好吧, 现在大家都不愿意提起那事, 但当时受害的不只是荷兰人, 还有我们——我们这些住在老英格兰东岸的人。";
			link.l1 = "我听说过那件事。 那些家伙对谁都毫不留情。 你是怎么活下来的? ";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "我知道他们的暴行。 他们不放过任何人——无论老少。 你能从那里逃出来, 真是太不可思议了。";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "那天晚上, 那些天主教混蛋烧毁了好几座农场, 包括我们家的。 我侥幸逃出来了, 可我妈呢, 她喝了太多苹果酒, 胖屁股都抬不起来, 就这样活活烧死在床上。 说到底都是她自找的——可她毕竟是我妈。";
			link.l1 = "所以你就是从那时候开始恨所有天主教徒的, 对吧? ";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "那天晚上, 那些天主教杂种烧了好几家农场, 我们家的也没逃过。 我侥幸逃出来了, 可我妈喝了太多苹果酒, 胖屁股都抬不出床, 就活活烧死在里面。 说到底也是她自找的——不过, 她毕竟还是我妈。";
			link.l1 = "那就是你开始憎恨所有天主教徒的时候吗? ";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "那时候我才学会了恨饥饿, 你这家伙。 你大概从没真正体会过那种滋味吧, 但我可体会过——真真切切地感受在自己身上, 没错。 我往北去了首都, 报名进了海军——在那里, 鞭子比饭还常见, 不过挨上几十下也就明白了。 之后我也习惯了——还爱上了海上的生活。 尤其是因为永远不会无聊嘛…… ";
			link.l1 = "是啊, 我信了。 英格兰舰队的名声总是比他们自己跑得还快。";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "1633年, 我通过了中尉考试, 被分配到康沃尔号双桅船。";
			link.l1 = "在Joshua Casper的指挥下。";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "哦, 对了…… Joshua Casper…… 整个该死的舰队里都找不到比他更混账的家伙了, 对吧。 都过了这么多年了, 那个无赖还是会出现在我的梦里。";
			link.l1 = "那他后来怎么做的? 是不是因为你太积极就让你多值班了? 还是他其实是个天主教徒, 偷偷藏着身份? ";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "那个狠心的混蛋把船员操练得要死, 累得人都直接掉下海里了。 既然你知道他的名字, 还知道他是 '康沃尔号' 的指挥官, 那你肯定见过他的证件——亮得跟猫舔过屁股似的, 对吧。 我们的英雄约书亚可是有一整箱奖章。 像你这样的天真小伙子, 想跟着他干的人可不少——怎么说都行, 可他砍起你们这些吃青蛙的家伙来, 就像雨后锋利的镰刀割湿草一样, 对吧——可一旦真上了 '康沃尔号' , 大家很快就明白自己错了。 我们早就受够了, "+pchar.lastname+"。 有些人甚至写了调职申请——可那些申请不是被扔进海军部的架子上, 就是进了他们的炉子。 不过, 命运还是给了我们机会——他们没把我们调离 '康沃尔号' , 而是把别人调上来了。 约翰·劳森——克伦威尔的心腹, 你肯定听说过他。";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "他那时候就已经会拍马屁了——说不定他和Casper还真能聊得来, 对吧? 不过我可没让那事发生。 我把小Johnny给算计了, 结果一头雾水的Joshua, 啥也不知道, 就一气之下用拐杖把那可怜孩子揍了一顿。";
			link.l1 = "对一个军官来说, 真是奇耻大辱。 Lawson把一切都告诉你父亲了吗? ";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "当然啦。 不过你看, 体制是不会自吞的。 这事儿就被压下去了——Lawson得了提前升职的好处, Joshua和 'Cornwall' 号也被打入冷宫——我们从伦敦被调到了英格兰南部的普利茅斯。 其实我们本可以继续吓唬你们这些吃青蛙的家伙, 对吧? 可 'Cornwall' 号被改成了补给船, 专门给爱尔兰小镇Dundalk运送军用物资。";
			link.l1 = "那你就是在那里遇见Teresa的? ";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "我们第一次去那里的时候。 正如我说过的, Teresa O'Fatt 是当地一家酒馆的女招待。 三天时间就足够让我们明白彼此是天作之合。 我想你会懂我的, "+pchar.lastname+", 对吧? ";
			link.l1 = "我想是吧。";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "现在看你这样, 谁能想到你懂 'love' 这个词的意思。";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "我这辈子从未遇到过比她更美好的人——无论是之前, 还是这二十年来都没有。 那是我人生中第一次真正感到幸福, 她也是——或者说, 她是这么说的。";
			link.l1 = "你让她跟你一起离开了吗? ";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "我这辈子从未遇到过比她更美好的人——无论是以前, 还是这二十年来都没有。 那是我人生中第一次真正感到幸福, 她也是——或者说, 她是这么说的。";
			link.l1 = "你让她跟你一起离开了吗? ";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "当然不可能——那根本办不到, 因为 '康沃尔号' 当时还是一艘战舰, 船长又是个混蛋。 那一周简直像过了一个世纪, 我们的双桅船才启程返回普利茅斯。 两个月后我们回到邓多克——特蕾莎用一个消息把我惊呆了: 她怀孕了。";
			link.l1 = "好吧, 把女孩哄上床, 这种事常有的, 对吧? ";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "别耍聪明了, 吃青蛙的家伙。 Teresa当时在我肩膀上哭得稀里哗啦, 我还在琢磨该怎么办呢。 我是真的很想留下来陪她, 真的——可那时候我就觉得, 这孩子绝对不会带来什么好事。 \n我试着劝Teresa趁还来得及把孩子打掉——结果她反而歇斯底里得更厉害了。 我们当时实在想不出办法——所以就决定再等两个月, 等 'Cornwall' 号下次回到Dundalk,  因为那时候海军部还没把对Casper的怒火转为宽恕。 \n我们回来之后, 我一开始没能找到她——特蕾莎的怀孕已经显而易见, 而据她打工的酒馆老板说, 她那个混蛋父亲把她痛打了一顿, 还把她锁在家里。 毋庸多言, 我把那个杂种揍得差点把 自己的肠子都吐出来。 当然, 她再也不可能继续待在那个家里了。";
			link.l1 = "你把她带上了 'Cornwall' 号? ";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "我得做出一个迅速的决定。 我知道Casper绝不会容忍船上有女人, 所以我打算在我们起航后的那个夜晚偷一艘小船, 从右舷溜走, 前往都柏林, 就在我们旁边。";
			link.l1 = "然后发生了什么? 他们抓住你了吗? ";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "正是如此。 Casper已经给自己倒了满满一杯威士忌, 所以对任何求情都充耳不闻, 直接下令把那女孩扔下海。 不管我怎么求他, 他只是笑得喘不过气来——该死, 我现在跟你说这些的时候, 脑子里还能听见他的笑声…… ";
			link.l1 = "所以你就是在那时候决定发动叛变的, 对吧? ";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "我别无选择。 趁着旁边守卫不注意, 我从他腰间抢了一把手枪, 直接在那混蛋的额头上开了个洞。 甲板上立刻爆发了一场大屠杀——没人喜欢那船长, 但对法庭的恐惧更甚。 这场混战让将近三分之一的船员丧命——等我们终于回过神来时,  '康沃尔号' 的整片甲板早已鲜血淋漓, 遍布着我们死去同伴的尸体。";
			link.l1 = "之后, 你们肯定决定不再回英格兰了。 回去只会被绞死。";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "我当时确信自己能带着 '康沃尔号' 横渡大洋。 在这里没人认识我们的面孔, 这给了我们一个重新开始新生活的机会。 说服其他军官并不难——起作用的并非只是我的威望, 而是那几只箱子里的东西, 普通水手对此一无所知。 船员们决定——约书亚·卡斯帕必须活下去。 我们几名军官决定为大家争取一些时间, 牺牲其中一只箱子, 然后驶向安提瓜, 在那里我会以他的身份出现。 之后, 我们打算设定航向前往普罗维登斯。 \n事情的确如此, 没有人怀疑身份的替换, 但当离普罗维登斯只剩几天航程时, 不知哪个杂种泄露了关于第二只箱子的事——这立刻在船员之间引发了分裂。";
			link.l1 = "所以这次水手们是要造反对付你了吗? ";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "没有, 不过愿意继续为我们光荣国王效力的人数骤减。 也没多少人想去当海盗。 所以我们找了个折中的办法——决定在法国的某个港口抛锚。 在那里, 我们打算把船卖了, 把卖船的钱和箱子里的东西分了, 然后各奔东西。";
			link.l1 = "那你就不在乎要和那些你那么厌恶的天主教徒一起生活吗? ";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "我已经不在乎我们会在哪儿登陆了: Teresa虽然表现得很坚强, 但她的感受和任何怀孕三个月、一直晕船的女人没什么两样。 而且, 就像三个月前一样, 只要我能陪在她身边, 我对天主教徒的陪伴也毫无意见。";
			link.l1 = "但是在加勒比海西北部没有法国人的定居点, 而且从来都没有过。";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "等到 '康沃尔号' 上的情况彻底失控时, 我们已经顺风航行了一半路程, 那时候已经无法改道去圣克里斯托弗了…… ";
			link.l1 = "你把托尔图加选作你的目的地? ";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "那时候, 这里还只是个普通的小村庄。 为了拖延官府可能的追捕, 我们把船尾的铭牌换了——于是 'Cornwall' 就变成了 'Wrangler' 。";
			link.l1 = "但是不知道为什么, 你始终没有到达Turtle Island。 你不可能偏离航线那么远, 结果跑到古巴以西而不是Tortuga岛了吧? ";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "跟你说啊, 我可是个有经验的领航员——比大多数人都强, 对吧? 绝对没出错, 我们一直沿着正北方向航行。 可一进风海道, 就遇上了可怕的暴风雨。 我到现在都想不明白, 咱们怎么没被拍到古巴岸上, 反而被风暴沿着岸拖着走了…… ";
			link.l1 = "简直就是个奇迹, 毫无夸张。";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "我紧紧抱着哭泣的Teresa, 满心向主祈祷, 恳求祂赐予我们救赎。 祂真的帮助了我们, 对吧。";
			link.l1 = "你被海浪冲到了正义岛上。";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "正义——哦, 当然啦! 当 '驯马者号' 撞上暗礁时, 船身断成了两截, 但不知怎么的还是浮在水面上——刚好能被海流带到那些其他残骸堆积的地方。 风暴又肆虐了将近两天, 等终于平息下来——那个可怜小岛上的人们救了我们, 对吧? ";
			link.l1 = "你、Teresa, 还有另外两个水手。 接下来发生的大致情况我们都知道了。 还是说说你是怎么从监狱里出来、又怎么离开那个岛的吧。";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "要是他们当时就把我崩了就好了…… 要是我早知道后面等着我的是什么, 我肯定会把自己锁在牢栏上, 一步都不挪。";
			link.l1 = "在塔塔纳船上真的比在双桅帆船上还不舒服, 对吧? "+npchar.name+"? ";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "可别告诉我你也是在一艘塔尔坦帆船上遇到风暴的。";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "塔塔纳船? 哈哈哈…… 好吧, 那确实是我的计划。 我当时还以为自己走运了呢。 狱警头子原来是英格兰海军的前军官, 他对我起了恻隐之心。 他把古巴走私贩的塔塔纳船都告诉了我, 还说他们正打算处决我。 你可以说他是个有荣誉感的人——正是他主动提出放我走, 让我把命运交给机会。";
			link.l1 = "我不明白…… 如果不是乘坐tartans, 那你们是怎么离开岛上的? ";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "塔尔坦船? 哈哈哈…… 好吧, 那确实是我的计划。 我还以为自己走运了呢。 狱卒头子原来是英格兰海军的前军官, 他对我的不幸产生了同情。 是他告诉我古巴走私贩的塔尔坦船的事, 还说他们打算处决我。 也许你可以说他是个有荣誉感的人——他亲自提出要放我走, 让我把命运交给机会。";
			link.l1 = "我不明白…… 如果不是乘坐tartans, 那你们是怎么离开岛上的? ";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "你要是闭嘴听我说, 就能明白了, 对吧? 我当时一直在朝那些塔塔纳船游过去, 游了好久——直到我在雨幕之外看到一道光。 那真是不可思议, 见鬼了。 它像太阳一样照亮了一艘半沉的盖伦船甲板, 我就直奔那道光去了。 那时候我还不知道, 这其实是我这辈子犯下的最大错误。 我用舷梯爬上了船——结果就和那道光面对面了。 它在一尊金像上方闪闪发亮, 然后…… ";
			link.l1 = "库库尔坎的神像。 好吧, 那时候 'San Jeronimo' 号还没沉呢…… ";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "所以, 你也看见他了, "+pchar.lastname+"? ";
			link.l1 = "不只是看见了。 我还靠它穿越了空间, 而且不止一次, 对吧。";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "你在撒谎! 好几次, 你说的? ! 那你怎么还能站在这里, 看起来这么有活力? !";
			link.l1 = "我被转移之后, 喝了一种印第安人的药水, 就是它帮我活了下来, 还恢复了体力。";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "啊, 原来是这样。 你知道我花了多长时间才恢复力气吗? 你知道吗? !";
			link.l1 = "我猜你大概是这样, 对吧? 你碰了那个神像, 然后它把你送到了多米尼加——去了印第安人的村子, 他们把你献祭给了雕像, 接着你就到了大陆, 对吧? ";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "没错。 我从来没有像那时候那样痛过, 就躺在那座雕像旁边。 真不知道该怎么形容那种痛。 也许就算有一座石头房子塌在你身上——都不会那么难受。 我刚恢复意识, 就看到一群土著又朝我冲过来。 如果我会说他们的语言——发誓, 我一定会求他们当场杀了我。";
			link.l1 = "那些是附近村子的米斯基托印第安人吗? ";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "就是他们。 他们把我拖进了一间小屋, 里面有个奇怪的土著——看起来和其他人不一样——直接往我嘴里灌了点什么。 疼痛稍微缓解了一些, 但还是没完全消失。 到了傍晚, 他们又把我拖到火堆旁, 那个涂满颜料的混蛋开始搞什么仪式。 可怜的家伙。";
			link.l1 = "蛇眼…… 你本该感激他救了你一命。";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "救我? …… 三年啊, "+pchar.lastname+"。 整整三年我几乎一动不动地躺着, 拉屎撒尿在床上, 醒来时满身都是自己的呕吐物——因为我实在受不了他们硬灌给我的那些恶臭的药汤和药酒! 后来我又花了将近一年才重新学会走路。";
			link.l1 = "真让人心碎。 不过说实话, 我差点都要同情你了。";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "把你的怜悯塞进你那胖天主教教皇的屁股里吧。 我可不需要谁的同情。 我要继续说下去吗, 还是你得先哭一会儿, 小孔雀? ";
			link.l1 = "这趟旅程可一点没让你的礼貌变好。 不过算了, 看在Mary的面子上, 我就忍了吧。 虽然我想我们已经知道最重要的部分了——不过, 还是听你说完吧。";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "我好不容易才重新站起来, 离开了那个被诅咒的村子, 前往海岸, 去了阿马蒂克湾。 在那里, 我遇到了一些走私贩, 他们的船就停在附近, 于是我加入了他们, 自称鲁珀特·卡斯帕——我不想放弃我的名字, 但我还是保留了那个毁了我人生的人的姓氏。 这样我就永远不会忘记自己为什么会落到这步田地。";
			link.l1 = "其他人都该被责怪, Northwood…… 除了你。 话说回来, 我能理解——多年的屈辱和折磨, 现在你还困在这片森林里。 很难不疯掉, 对吧? ";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "你经历了很多, Northwood——这点毫无疑问。 现在看看你自己…… 在树林里, 文明的边缘。 你不会在这里失去理智的…… ";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "我是这片森林的主人, "+pchar.lastname+"。 十五年来, 我从一名走私船上的可怜水手, 变成了他们的首领。 不只是某条小船的船长, 而是整片海岸的主人, 从阿马蒂克湾一直到厄运湾。";
			link.l1 = "嗯, 这还真是个漂亮的反击, 我承认。";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "我是这片森林的主人, "+pchar.lastname+"。 十五年来, 我从一个走私船上可怜的水手, 变成了他们的首领。 不只是某条小船的船长, 而是整个海岸的主人, 从阿马蒂克湾一直到厄运湾。";
			link.l1 = "嗯, 这还真是个漂亮的反击, 我得承认。";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "有人说这里是森林恶魔的地盘…… 真是厚颜无耻的谎言——这片土地是我的。 Swenson心里清楚, 哈哈哈。 他不止一次派人来, 想查出我的身份——可没有一个人活着回去见他。 呵呵。 能数得过来的人才知道我当初以什么名字开始走私生涯, 或者我藏在这片林子里的哪个角落。";
			link.l1 = "所以, 你现在用的是别的名字。 难怪一听说有人在找 Rupert Casper, 你就慌了。";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "慌张? 你认真的, 臭小子? 这里唯一慌张的人就是你——在我的地盘, 被我的人包围, 完全任我摆布! 我想怎么对付你都行。 还有她——就因为她让我受了那么多罪, 我也可以随便处置! ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "你疯了, 真的彻底疯了, 没错。 我可不知道有什么药或者医生能治好你, Rupert Northwood! 你确实经历了地狱般的苦难, 但是…… 你怎么能把一切都怪到我头上? !";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "我早就跟你说过了——要不是你, 这一切都不会发生, 对吧? 就承认吧, 好吗? ";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "别管他了, "+npchar.name+"。 我们已经听够了。 有些路真的不该一直走到头。 我在决定掺和进来的时候就有种不祥的预感。 但我没听从。 可惜啊。";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "是啊, 那你们俩就都不会落到这儿来, 被困住, 什么也做不了。 现在你自己感受一下, 孩子, 我当初经历的痛苦吧! ";
			link.l1 = "谁告诉你我们什么都做不了的? 队——伍——, 准备战斗! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "怎么了, 新手? 丢了谁吗? 哈哈哈…… 哈哈哈。 哈哈哈哈哈哈哈! ! ! 哎呀, 你现在的表情真有意思, 傻瓜! 嘿, Mason, 把我给客人的礼物拿过来。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "混蛋! 我的人都去哪儿了? ";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "你是说那几个以为能埋伏我的蠢货吗? 我的朋友, 酒馆老板, 及时告诉我你要来镇上的消息, 所以我好好 '招待' 了他们一番…… 有几个还是侥幸逃掉了。 可别担心——我活捉了其中一个。 这样你就能亲眼看看, 今天等着你的会是什么下场了。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "混蛋! 你会为此付出代价的!  (哭泣) 我发誓, 对吧! ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso! 见到你我太高兴了! ";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "我也很高兴见到你, 船长! 有人通风报信, 让那家伙知道你在追他——结果我们半路就被一阵霰弹打了个措手不及。 我好不容易带着几个人撤了回来, 直接跑到港口来通知你。 幸好当班的守望员看到我乘着在镇上匆忙买来的小帆船, 立刻明白发生了什么。 他很快就召集了人手——我们就赶来这里帮忙了。";
			link.l1 = "谢谢你, 我的朋友。 你救了我们一命。";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "这算什么。 接下来我们怎么办, 船长? ";
			link.l1 = "把船员都召集起来, 去船上。 我要和Mary单独待一会儿。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "天啊, "+pchar.name+"…… 我还是不能, 我真的不能相信。 我的父亲…… 他是个怪物…… 他为什么要这样对我? 他真的疯了吗? ";
			link.l1 = "他不得不忍受可怕的苦难。 '康沃尔号'上的叛变、横渡大西洋的逃亡、风暴, 还有你母亲的死。 我无法想象没有科曼奇药剂, 他是怎么靠着那些偶像的传送门活下来的——但正是那毁了他的心智。";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "那如果他一直都是那样呢? 或者说, 他其实也是个混蛋, 只是稍微温和点, 但真的爱过我妈妈? 要是这些事只是释放了他本来就有的东西呢? 如果真是这样…… 那我身上是不是也有他的影子? 这也有可能, "+pchar.name+", 对吧? ";
			link.l1 = "你确实从他身上学到了一些东西, "+npchar.name+"。 今天的战斗里我注意到了——你战斗时有着和他一样的决心, 眼里燃烧着同样的火焰, 还有那股和他一模一样的狂怒。 但你没有他的疯狂。 你完全是另一种人。 你那么鲜活、坦率, 心里想什么都写在脸上。 正因为这样, 我才会爱上你。 而且看来Northwood说得没错: 你彻彻底底继承了你母亲的精神。";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "你真的这么想吗, 亲爱的? ";
			link.l1 = "当然啦, 亲爱的。 如果我就那样遇见他, 根本不知道他是谁, 我绝对不会猜到你们是亲戚。";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "你知道吗, 在正义岛上其实没什么娱乐, 对吧? 我从小就喜欢击剑——一开始是拿木棍跟男孩子们打, 后来就和大人们用真剑了, 对吧。 我一直想和他们平起平坐…… 可不知怎么的, 即使赢了, 我还是觉得自己比他们弱。 所以我就回家继续练, 练上好几个小时, 直到手都开始发抖, 对吧。 这就是你说的那种火吗? 你说的那种愤怒, 是这个意思吗? ";
			link.l1 = "某种程度上——是的。 我觉得那股火焰给了你比你自己看到的还要多的力量。 不管你愿不愿意, 那都是你父亲留给你的礼物。 即使他从未打算给你任何东西。";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "你觉得我们挖掘过去的事情是对的吗? ";
			link.l1 = "现在我们都知道了一切…… 这主意好像也没那么好了。 不过, 如果你想知道真相, 就得做好可能不喜欢它的准备。";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "你说得对, "+pchar.name+", 好吧…… 咱们再待一会儿, 对吧? 我现在还不想回船上。 我只想…… 坐在这儿, 享受这份安静。";
			link.l1 = "当然了, 亲爱的。 我正想提一样的建议呢。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name+", 你来得正是时候, 船长"+pchar.name+"。";
			link.l1 = "我就知道可以信赖你, 我的朋友。 谢谢你, 没有人能比你做得更好。";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "丛林是"+npchar.name+"的家。"+npchar.name+"喜欢在丛林里战斗。 丛林赋予"+npchar.name+"力量。";
			link.l1 = "所以我才让你带队。 而且确实没错——你看, 他们可是早就张开双臂等着我们了。";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "船长"+pchar.name+"接下来打算做什么? ";
			link.l1 = "我和玛丽需要独处一会儿。 你把所有伤员集合起来, 带回船上。 阵亡者也一起带回去——我们会将他们葬于海中。 还有, "+npchar.name+"…… 告诉阿隆索, 要按照新教仪式安葬玛丽的父亲, 就在附近。 埋葬地点只有你和他知道, 别告诉任何人, 包括玛丽。 她不该再为此伤心。";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name+"明白了, 船长"+pchar.name+"。 提钦吉图会照办。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "这些杂碎真顽强…… 不过我们还是耍了他们, 哈哈。 就让他们在这儿烂掉, 好好反省一下是不是值得和我们作对。";
			link.l1 = "谢谢你, "+npchar.name+", 你们干得漂亮。 真不敢想象如果我没让你们守后路, 玛丽…… 还有我…… 会怎么样。";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "哈, 老大, 我了解你, 你肯定能应付得来。 看到那帮头头手上的砍刀了吗? 我可一直盯着他。 要是你不喜欢它, 送给我我也不会介意。";
			link.l1 = "哼…… 再说吧, 伙计。 现在先把活着的人集合好带回船上。 死者也一起带走——我们会把他们葬在海里。 还有…… 那个头头是玛丽的父亲。 带上阿隆索, 按照新教礼仪把他安葬在附近。 墓地的事别告诉任何人, 尤其是玛丽。 她不该再为这件事痛苦。";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "明白了, 老大。 等等…… 算了, 不现在说了…… 我这就去。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
			
		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "这里挺热闹的, 老大。 那帮杂碎得到了应有的报应。 你看到那矮子的脸了吗? 我们一出现他就吓傻了。";
			link.l1 = "他显然没料到会这样。 就像我和玛丽也没想到他竟是这种人。 但好在我当初决定守住后路, 直觉没让我失望。";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "你在加勒比混了也不是一天两天了, 早就知道这地方乌烟瘴气, 全靠第六感防身。 现在怎么办? 回船? ";
			link.l1 = "把伤员和死者都带回船上。 阵亡者就交给大海吧, 毕竟他们是它忠诚的儿子。 我和玛丽晚点回去——我们需要一些时间独处。 还有一件事: 让人照新教礼仪安葬玛丽的父亲。 你可以让阿隆索帮忙, 但别让任何人知道葬身之处。 尤其是玛丽。 她不该再为这事心碎。";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "你说得对。 她没必要再回来看这些痛苦的回忆。 放心吧, 一切都会妥当, 绝不会有外人知道。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "船长先生, 报告: 埋伏成功, 敌人已歼灭, 船长已救出。";
			link.l1 = "你觉得现在是开玩笑的时候? 这是在找死。 你想在水手面前擦甲板取乐他们? 我劝你别再试我耐性。 尤其是今天。";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "呃…… 我可是军官啊, 我…… ";
			link.l1 = "那是现在。 今天是军官, 明天可能就是水手, 后天就要饭去了。";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "明白了, "+GetFullName(pchar)+"——一脸严肃的船长。 不说笑了。 请下令, 先生? ";
			link.l1 = "把伤员带回船上。 让阿隆索带人处理我们的战友遗体——他们将归于大海。 另外, 让他照新教仪式安葬玛丽的父亲。 知道墓地位置的只能是他和帮他的人。 玛丽不能知道。 她不该再为这事痛苦。";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "好吧, 知道了…… 我会去做的。 你放心, 我嘴巴严得很。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "船长先生, 我们胜利了。 没有一个畜生逃掉。";
			link.l1 = "干得好, "+npchar.name+", 谢谢你。 我知道你值得信赖。 带上所有幸存者回船吧。 我和玛丽会在岸上多待一会儿。";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "我们该如何处理战死者的遗体? ";
			link.l1 = "我们会将他们交给大海。 告诉阿隆索, 让他负责安排葬礼。 另外, 让他按照新教传统在丛林里安葬玛丽的父亲, 最好选个偏僻的地方。 不能让任何人知道墓地位置, 尤其是玛丽。 她那性子, 肯定会想回来…… 这对她没好处。";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "我会全部转达。 您还有其他指示吗? ";
			link.l1 = "没了, 兄弟。 去吧, 好好休息, 把伤养好。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "真是一场屠杀…… 你还好吧, 老大? ";
			link.l1 = "还行吧, 只不过…… 我和玛丽亲手杀了她的父亲…… ";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "看样子, 那家伙真不是个东西…… ";
			link.l1 = "说得对, "+npchar.name+", 你说得没错。 但不管怎么说, 我们得为他举行一场像样的葬礼——按新教的方式。 你亲自处理这事。 不能让任何人知道墓地在哪里, 尤其是玛丽。";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "你是想让她远离那些痛苦的回忆? ";
			link.l1 = "也免得她自责自苦。 其他人你就送回船上治疗伤口。 战死者也带回去——我们回来后, 会在海上为他们举行仪式。 现在我和玛丽需要些独处时间。";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "我会让兄弟们别去打扰你们。";
			link.l1 = "谢了, "+npchar.name+"。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
} 
