// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "你想干什么? ";
			link.l1 = "我该走了... ";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "该死的, 你到底是谁? ";
				link.l1 = "日安, 洛佩先生。 虽然我们还没正式认识, 但现在是个好时机。 尤其是我很想帮你摆脱困境... ";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "你想干什么? ";
				link.l1 = "我该走了... ";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "帮忙? 帮我? 这剧情反转! 能告诉我, 先生, 这慷慨从何而来吗? ";
			link.l1 = "当然。 我在找你以前的船长, 埃斯贝多.卡巴纳斯, 而且时间不多... 最好能在他的秘密据点见他, 要是我能先到就更好了。 ";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "哈哈! 我就说那蠢货守不住嘴! 蓝琥珀, 对不对? ";
			link.l1 = "思路正确, 先生。 ";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "那我们得抓紧了。 如果你能想办法把我弄出去, 我就把所有细节都告诉你。 知道我怎么进的这鬼地方吗? ";
			link.l1 = "大致知道。 ";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "事发时我喝得酩酊大醉。 去他妈的酒保! 我什么都不记得了。 醒来时已经在‘坎塔沃罗’号的货舱里。 要是当时直接开溜就没事了, 总督和市长都睁一只眼闭一只眼。 但该死的埃斯贝多先生直接把我送进了监狱。 你以为他是‘主持正义’? 要是那样就好了, 那混蛋只是想独吞我的琥珀份额! 是我发现海滩下可能有更多琥珀, 是我找到采集方法, 本应拿到丰厚分成, 结果... 那狗娘养的! 唉, 不说了。 市长。 总督和托莱多先生都不想看我在这里烂掉。 要不是那农民和他的泼妇老婆惹事... 总之, 他们不会反对你帮我。 去见总督, 假装是我欧洲来的老朋友 --我会亲自作证。 对了, 你叫什么名字? ";
			link.l1 = ""+GetFullName(pchar)+"。 ";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", 太好了。 去见迭戈.德.托莱多先生, 听听他的建议。 记住, 只有三天时间, 过了这三天追‘坎塔沃罗’号就没意义了。 救我出去, 我会给你对付那混蛋卡巴纳斯所需的一切。 ";
			link.l1 = "我马上就去见总督, 洛佩先生。 我会尽力为我们俩解决这局面。 ";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // 计时器
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请按时完成! ");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; // 移除计时器
            dialog.text = "看来那奸商和他的泼妇老婆遭了报应, 我终于摆脱这鬼地方了。 先生, 我欠你一份人情, 你已经履行了承诺。 现在该我了。 ";
			link.l1 = "我洗耳恭听! ";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "很好。 上次巡逻时我们遭遇风暴偏离航线, 在西印度群岛的海滩登陆取水, 就在蚊子海岸附近。 我们在那里发现了优质的蓝琥珀矿脉。 我勘探后发现水下还有大量储量, 需要更好的设备才能采集, 所以打算稍后返回。 埃斯贝多在哈瓦那买了五艘长艇, 雇印第安人潜水采集琥珀。 后来的事你知道了 --那混蛋踢开我独自起航。 去蚊子海岸蓝礁以北找他, 动作要快 --据我估算, 你只有七天时间赶到。 希望你能在他采集时抓住那混蛋, 夺走所有琥珀, 再狠狠捅他几刀。 不过小心点, 我前船长是个熟练的战士和水手。 祝你好运, 先生。 ";
			link.l1 = "你也一样, 洛佩。 再见! ";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // 计时器
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// 罗萨里奥.古斯曼
		case "Mtr_rosario":
            dialog.text = "先生, 有什么想问的吗? ";
			link.l1 = "关于蒙托罗先生。 我们是老相识, 得知他遭遇不幸我很痛心。 迭戈.德.托莱多先生派我来找你, 说你已经尝试过救我们的共同朋友... ";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "嗯... 先生, 这有点... 意外, 但很高兴见到洛佩的朋友! 他已经倒霉很久了, 现在又出了这事... ";
			link.l1 = "我们能为他做什么? 总不能让一位高贵的绅士和社会渣滓关在一起! ";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "真是个办实事的人! 帮可怜的洛佩既简单又困难。 我和那个不幸与洛佩发生争执的奸商谈过, 他同意只要五百杜布朗就和解。 这对他和他妻子的‘损失’来说是笔巨款。 可惜我只凑到了一半 --二百五十杜布朗。 ";
			link.l1 = "所以如果我再给你二百五十杜布朗, 洛佩先生就能获释? ";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "是的。 那个贪婪的混蛋答应我会散布洛佩已经赔偿所有损失的消息, 还会请求总督赦免他。 ";
			if (PCharDublonsTotal() >= 250) // belamour传奇版本
			{
				link.l1 = "我现在就有这笔钱。 给, 让这个贪婪的资产阶级噎死吧。 ";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "我会尽快弄到钱。 ";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour传奇版本
			PlaySound("interface\important_item.wav");
            dialog.text = "难以置信! 先生, 您一定是上帝派来的! ";
			link.l1 = "他们什么时候放我们的人? ";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "很高兴听到这个, 先生。 您真是洛佩的真朋友, 一位真正的贵族。 ";
			link.l1 = "再见! ";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "钱带来了吗? ";
			if (PCharDublonsTotal() >= 250) // belamour传奇版本
			{
				link.l1 = "我现在就有这笔钱。 给, 让这个贪婪的资产阶级噎死吧。 ";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "还在想办法。 ";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "今晚我就把钱给那个狡猾的混蛋。 相信中午前就会有释放我们朋友的命令。 之后我们聚在一起庆祝如何? ";
			link.l1 = "当然, 罗萨里奥先生。 我现在得走了。 再见! ";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "我们的朋友很快就会自由了! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// 秃头杰弗里
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; // 移除中断
            dialog.text = "该死的, 你在我的船上干什么? 我可不记得邀请过你, 嗯? ";
			link.l1 = "冷静点, 杰弗里。 我是泰瑞克斯派来谈船用丝绸生意的。 ";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "啊哈, 那我们谈谈。 他有什么计划? 我已经和走私商谈过, 要我说他们给的价格很合适... ";
			link.l1 = "方便问问多少吗? ";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "一卷1300比索。 我觉得价格不错。 ";
			link.l1 = "是啊, 可泰瑞克斯要一卷20金币, 一分不能少。 我说的是杜布朗。 他让我找能出这个价的买家。 ";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "哈哈哈哈, 小子, 你运气真好! 马库斯胃口不小啊! 那你就去找这样的买家吧, 真想看看你怎么搞定。 ";
			link.l1 = "这一点都不好笑。 我看起来很开心吗? 并不。 所以建议你别笑了, 帮我一把。 ";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "好好好, 兄弟... 老天, 你还真开不起玩笑? 但我理解, 不能怪你做泰瑞克斯的白日梦, 我们都会从中分一杯羹, 相信我。 我怎么帮你? 你不能在商店卖, 也不能走海关, 只能找走私商。 还有谁需要? 有主意吗? ";
			link.l1 = "从伊斯帕尼奥拉岛开始我就在想... 不管了。 我只有两个月找固定买家, 必须想办法。 你的命令是在最近的海湾靠岸维修。 ";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "两个月? 搞什么? 啊, 去他的。 ‘毒蛇’号确实需要维修清理, 不然连三桅帆船都追不上。 嘿, 法国婊子们! 秃头杰弗里的船员要在卡普斯维尔待两个月! 哈哈哈哈... 祝你好运, 兄弟, 慢慢找你的冤大头。 要是找到愿意出马库斯价的傻子 --知道上哪找我。 ";
			link.l1 = "等等! 给我一卷丝绸, 我需要拿给潜在买家看样。 ";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "没问题。 你可以坐长艇带走... 嘿, 伙计们! 扔一卷丝绸到船长的船上! ";
			link.l1 = "很好。 找到买家后见! ";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请按时完成! ");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // 计时器
		break;
		
		case "Jeffry_8":
            dialog.text = "还有事吗, 兄弟? ";
			link.l1 = "目前没有... ";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "最近怎么样, 兄弟? ";
			link.l1 = "不错。 找到买家了, 一卷25杜布朗。 我想泰瑞克斯会满意的。 ";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "不可能! 你这狡猾的混蛋! 怎么做到的? ";
			link.l1 = "说来话长, 杰弗里。 听着, 你要在10到15号之间到牙买加的内格里尔角。 他们晚上在那里等你, 暗号是‘A merchant of Lyons’(里昂的商人)。 记住了吗? 重复一遍。 ";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "‘A merchant of Lyons’(里昂的商人), 记住了。 我让会计记下来, 他是船上唯一会写字的人。 哈哈! ";
			link.l1 = "货舱里有一百卷吗? ";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "比那还多。 ";
			link.l1 = "太好了, 现在该起航了。 别让我失望! ";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "放心, 兄弟, 一切都会办妥。 ";
			link.l1 = "一路顺风, 杰弗里。 也许还会再见。 ";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // 给泰瑞克斯
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "吼吼吼! 狡猾的查理王子, 真人现身! 很高兴再次见到你, 兄弟! ";
			link.l1 = "秃头杰弗里! 你叫我查理王子? 哈! ";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "没听过你的外号? 拉维加现在都这么叫你。 ";
			link.l1 = "查理我知道, 但为什么是王子? ";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "因为你是拉维加唯一的贵族混蛋! 哈哈哈哈! 最近怎么样? 去过帕斯夸莱的店吗? 从那老混蛋那买补给了? ";
			link.l1 = "再也不去了! ";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "哈! 不喜欢他? 他是不是把咸牛肉当朗姆酒卖给你了? ";
			link.l1 = "更糟! 他给了我一条荷兰商队运乌木的线索。 找到商队。 登船。 从几十号混蛋手里保护那堆破木头可不容易! 猜猜怎么着, 那混蛋一卷只给我150比索。 杰弗里, 那可是乌木啊! ";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "这种事常有, 兄弟, 我保证。 拉沃西耶已经坑了十几个像你这样的好小伙。 他居然还付钱给你, 这对他来说可真少见。 我们就算饿死也不接他的‘线索’。 ";
			link.l1 = "谢谢你, 朋友, 至少知道我不是第一个傻瓜! 但这次那混蛋坑了自己, 我会让他后悔见到我的那天。 ";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "嘿嘿嘿! 等等, 王子, 冷静点。 这奸商在这儿没人敢动。 敢抢他? 马库斯会找你麻烦的。 告诉我, 是泰瑞克斯派你去找拉沃西耶的? ";
			link.l1 = "嗯... 是啊... 怎么了? ";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "听着... (压低声音) 据说那四眼仔和马库斯是一伙的。 现在明白了? 所以没海盗敢袭击拉沃西耶的船, 不然就死定了。 ";
			link.l1 = "记下了。 谢谢你的警告, 杰弗里。 再见, 一路顺风! ";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "你也一样, 兄弟。 ";
			link.l1 = "... ";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // 版本修正
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // 属性 - 主角是知名海盗
			pchar.questTemp.CharleePrince = true; // 招募船员用属性
		break;
		
		case "Jeffry_22":
            dialog.text = "吼吼吼! 王子! 我还在想是谁放的烟火! 带了火枪手小队, 以防是西班牙人。 ";
			link.l1 = "杰弗里? 你也在? 怎么回事? 你也买了藏宝图? ";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "兄弟, 我才不会把钱浪费在那鬼东西上。 有人给了我一本旅行者日记, 里面写了进地牢的秘密通道。 ";
			link.l1 = "谁给你的? ";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "一个瘾君子, 只要一百比索买酒喝。 ";
			link.l1 = "在托尔图加发生的? ";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "不, 是巴巴多斯? 王子你怎么这么担心? 我们人越多, 搬宝藏越快! ";
			link.l1 = "我不喜欢这样, 不相信这种巧合。 会不会是卡米拉的父亲写的日记? ";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "卡米拉是谁? ";
			link.l1 = "就是那个卖我地图的婊子, 要了我二百比索! ";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "呵... 王子你想太多了。 我们去寻宝吧, 走吧! ";
			link.l1 = "没必要, 我已经找到了... 在地牢下面, 铁栏杆后面。 得把栏杆弄开。 听着, 杰弗里! 佩利.卡特尔也来过! ";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "卡特尔? 那我们今天走运了! 他现在在哪? ";
			link.l1 = "下面... 死了。 我在宝藏附近遇到他, 他发疯了, 大喊着贪婪, 然后和手下一起袭击我。 ";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "嗯... 佩利一碰到钱就没好运。 看到那么多金子肯定疯了。 ";
			link.l1 = "可能吧... 但杰弗里你没明白! 我们三个都到了这里! 而且线索相同! 你觉得是巧合? 显然有人想把我们聚在一起, 这地方感觉像个坟墓。 ";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "但你看到金子了吗? ";
			link.l1 = "亲眼所见, 几大箱金币和金条。 ";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "那你担心什么, 王子? 带路吧, 看看你说的栏杆。 然后分金子。 ";
			link.l1 = "啊, 也许你是对的... 走吧。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            //PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "太壮观了! 这么多金子! 现在明白卡特尔为什么发疯了。 我们太幸运了, 王子! 你觉得这里有多少金子? ";
			link.l1 = "很多。 处理完栏杆就知道了。 ";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "是的, 栅栏很结实, 徒手或用剑都弄不开。 你说得对, 兄弟 --得找工具或火药。 嘿看! 那是什么! ? ";
			link.l1 = "... ";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"真是个混蛋! ";
			link.l1 = "你这该死的毒蛇! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// 比利.西帕特
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; // 移除计时器
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "如果今年‘飞鱼’号出这事, 就让鲨鱼吞了我... 伙计们, 来客人了! 你这辈子是有多倒霉, 才会想来我这破船? ";
			link.l1 = "你好! 你就是那个叫‘壮汉比利’的人吧? ";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "听声音还听不出来吗, 船长? 以前我的声音能让英国和西班牙商人吓破胆, 那才是辉煌岁月... 现在老比利只想在心爱的小岛岸边, 坐着心爱的长艇等死... ";
			link.l1 = "我有事找你, 比利。 听说你对牙买加附近的事了如指掌, 是吗? ";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "既然你这么说, 那肯定是了, 不是吗? 别兜圈子了, 说吧, 找我什么事? ";
			link.l1 = "很好。 皇家港有个造船匠, 给客户提供特殊服务, 需要船用丝绸。 因为在这里交易违法, 他找了个非法卖家。 我想知道是谁。 怎么给他提供船用丝绸的。 ";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "吼吼吼, 看看这是谁! 给迪奥利上校干活的, 小子? ";
			link.l1 = "又来了! 不, 我和马库斯.泰瑞克斯合作。 他想在船用丝绸市场分一杯羹, 而那个造船匠不敢和‘陌生人’打交道... ";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "哦, 你给‘法典守护者’干活! 这可是大新闻... 当然前提是你没撒谎。 我才不管什么造船匠, 抓了一个还有下一个。 我只关心我的老伙计。 ‘飞鱼’号状况很差, 明白吗? 给我弄条新长艇, 再拿一卷你说的船用丝绸 --比利会用它做张像样的帆, 好躲开巡逻队, 哈哈哈哈! 作为回报, 比利会告诉你造船匠和他的丝绸来源。 相信我, 小子, 我知道你想知道的一切, 只是得先确定你是个诚实的海盗, 不是舔红毛屁股的走狗! ";
			link.l1 = "新长艇? 给你钱自己买怎么样? 我再加点。 ";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "嘿嘿, 船长, 城里可不欢迎老比利。 皇家港的人还记得我, 我可不想和老朋友们一起被吊死在岩石上。 所以, 小子, 我等你送新长艇来。 我会在内格里尔角等三天。 别忘了丝绸! ";
			link.l1 = "好的, 比利。 你会得到长艇和一卷船用丝绸, 我很快回来。 ";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = "很好, 比利会在岸边等你, 船长。 回头见! ";
			link.l1 = "... ";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // 计时器
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; // 关闭遭遇战
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请按时完成! ");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "怎么? 已经把长艇带来了? ";
			link.l1 = "你个小滑头, 比利? ";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "那么, 船长, 我的新长艇呢? ";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "搞定了, 壮汉。 长艇送来了, 货舱里还有一卷船用丝绸。 你可以把旧船沉了。 ";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "还在办。 等等。 ";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; // 移除中断
            dialog.text = "真他妈爽! 这是五年来老比利听到的最好消息! 嘿, 该开瓶庆祝了... ";
			link.l1 = "算了。 说说丝绸供应商吧? ";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "可惜, 不然可以为我的新‘飞鱼’号干一杯! 算了... 听着, 小子\n每月中旬10到15号, 有艘挂英国旗的双桅帆船到波特兰峡。 要我说绝对不是英国船! 船名‘乌得勒支’, 从库拉索方向的西南驶来, 明显是荷兰船长, 一看便知\n总是同一伙人在岸边接货, 领头的是那个狡猾造船匠的工头。 他们卸的肯定是船用丝绸, 只有荷兰人这么打包。 ";
			link.l1 = "你说每月? ";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "没错, 小子, 去年至今从未间断。 想和这群阴郁的大胡子聊聊, 就每月10到15号晚上去波特兰峡等着。 我以新长艇的丝绸帆发誓! ";
			link.l1 = "呵! 看来钱没白花。 比利, 保重, 别被巡逻队抓了, 不然我会很不高兴。 ";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "哈, 老比利要在牙买加海岸好好玩玩了! 船长, 一路顺风! 狩猎愉快! ";
			link.l1 = "你也一样, 比利! ";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//关闭地点
			locations[FindLocation("shore35")].DisableEncounters = false; // 开启遭遇战
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "约阿希姆";
				sld.lastname = "古森";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // 航行修正3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// 皇家港码头工头
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "嘿, 水手, 刚到牙买加? ";
			link.l1 = "嗯, 没错。 怎么了? ";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "看到附近海上发生什么事了吗? ";
			link.l1 = "看到了, 一艘双桅帆船和英国巡逻护卫舰打起来了。 英国人狠揍了他们, 荷兰人想扔货逃跑。 ";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "你怎么确定是荷兰人? 正常荷兰人都不会靠近皇家港... ";
			link.l1 = "挂着英国旗, 但船名... ‘乌得勒支’, 不太像英国船吧? 我说是荷兰人, 可能还是走私船。 巡逻队肯定早有预料。 ";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "该死! ";
			link.l1 = "看来你不太高兴... ";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "你在等这艘双桅帆船? ";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "我为什么要等? ";
			link.l1 = "别装了。 我知道你是谁。 你是皇家港造船厂的工头, 在等一艘特殊货船送货。 ";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "你脸上都写着呢! ";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "啊! 兄弟们, 这是巡逻队假扮的! 干掉他们, 快撤! ";
			link.l1 = "靠! 等等你搞... ";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "这么无礼, ‘海狼’? 说话小心点, 否则... ";
			link.l1 = "得了吧。 你明显很沮丧, 真在等那些荷兰人? ";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "否则怎样? 想给我上一课? ";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "就算是又怎样? 你管得着吗? ";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "我不管, 你在这儿等你的, 我走我的。 你有一辈子时间等。 ";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "我当然管得着。 我知道双桅帆船货舱里是什么。 船用丝绸。 你就是为这来的, 对不对? ";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "嗯... 一辈子? ";
			link.l1 = "从海底回来需要一辈子。 你的双桅帆船被巡逻护卫舰击沉了, 兄弟。 就这么简单。 战争有得有失, 我能从那艘荷兰船上赚一笔。 ";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "你到底怎么赚? ";
			link.l1 = "他们逃跑时扔到海里的东西。 几乎全丢了, 但珍贵的船用丝绸像 cork 一样漂着。 我捞了大部分, 明天进城找买家。 塞翁失马, 焉知非福。 ";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "等等! ";
			link.l1 = "靠! 又怎么了? ";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "你捞了多少丝绸? ";
			link.l1 = "你管这个干嘛? 这是我的丝绸! 难道你是总督的狗? 你是... ";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "把剑收起来, 水手。 我不是狗也不是告密者。 我们在本地造船厂工作... 这丝绸本是给我们的, 现在在你手里。 我从你这买下, 我们需要这丝绸, 兄弟。 ";
			link.l1 = "真的? 有意思... 多少? ";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "一卷2500比索, 这价不错, 你找不到更高的了。 ";
			link.l1 = "看来我走运了! 我有"+FindRussianQtyString(i)+"。 钱拿来, 我马上让人运上岸。 ";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "成交! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);// 运气
			AddCharacterExpToSkill(pchar, "Sneak", 300);// 隐蔽
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "嗯... 约阿希姆应该只送80卷 --你不可能捞到这么多... 要么你想耍花样, 要么... 你是告密者! 兄弟们, 杀了他, 快撤! ";
			link.l1 = "靠! ";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "交易很愉快, 兄弟! 怎么这么沮丧? 担心海底的荷兰人? 这种事常有, 别担心! ";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "是啊... 他们是我们的固定供应商。 现在上哪弄丝绸? 我们一直缺货, 而且整个贸易都在迪奥利上校直接控制下。 真他妈见鬼... ";
			link.l1 = "嗯... 听着, 朋友, 我想我能帮你。 ";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "哦? 你想怎么帮我们? 每月送一百卷? ";
			link.l1 = "我? 恐怕不行, 但马库斯.泰瑞克斯可以。 听说过他吗? ";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "哈! 这么说你是海盗? ";
			link.l1 = "不, 只是特殊情况下和他们做生意。 我知道马库斯经常收到船用丝绸, 可以卖给任何付得起钱的人。 我说的不是一卷2500比索, 如果你能付每卷25杜布朗, 他能让你淹没在丝绸里, 说话算数。 ";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "有意思... 你说马库斯.泰瑞克斯? 只要杜布朗? ... ";
			link.l1 = "得了吧, 朋友, 你从谁那买丝绸很重要吗? 钱就是钱, 你可以去银行换。 所以, 要我在‘法典守护者’耳边替你美言几句吗? 反正我要去拉维加。 ";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "好吧, 成交。 我们的条件是: 每月10到15号送一百卷。 我们在这儿等... 等等, 换个地方, 这里不安全了。 去内格里尔角, 靠近马龙镇, 那里更安全。 暗号‘A merchant of Lyons’(里昂的商人)。 ";
			link.l1 = "成交, 朋友。 这趟航行真值! 泰瑞克斯会为找到这样的买家给我奖励的! 哈哈! 好了, 我该走了。 下月等泰瑞克斯的船吧。 祝你好运, 也祝你家人好运! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "等我们教你礼貌之后, 你就不需要人生教训了。 ";
			link.l1 = "装硬气啊, 木匠? 好吧, 继续等你的双桅帆船, 不过有的等了。 ";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "嘿, 老师, 我也有课要教你! ";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "木匠? 该死, 你怎么知道的? 哈! 靠, 兄弟们, 这是巡逻队假扮的! 杀了他, 快撤! ";
			link.l1 = "靠! ";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "滚吧, 你这鱼鳞, 我们没时间理你。 快滚! ";
			link.l1 = "你们忙着等某艘荷兰船? 祝你好运, 你有一辈子时间等。 ";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "你到底在说什么? ";
			link.l1 = "我明白。 但以防你真在等, 别等了, 多亏巡逻护卫舰, 它来不了了。 我从望远镜里看到了战斗结局, 就在附近, 很快就结束了。 ";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "再说一次, 我们没在等任何东西任何人, 而... ";
			link.l1 = "听着, 我真不在乎。 我不属于城市巡逻队, 也不关心你们的事, 我自己也不是天使。 如果你们在走私 --那是你们的事。 我只是想提醒你, 祝你好运, 兄弟。 ";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "等等... 你确定‘乌得勒支’号沉了? ";
			link.l1 = "千真万确。 它想逃跑, 扔掉了货舱里的所有东西, 连珍贵的船用丝绸都没留, 但还是躲不过护卫舰的速度优势。 ";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "真可惜... 没有丝绸我们该怎么办? 该死! ";
			link.l1 = "你需要船用丝绸? ";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "问这干嘛, 你卖? ";
			link.l1 = "我不卖, 但我认识一个卖的人。 他在找大方的固定买家, 你觉得合适吗? ";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "那人是谁? ";
			link.l1 = "马库斯.泰瑞克斯, 拉维加的男爵, 更广为人知的名字是‘法典守护者’。 他经常收到船用丝绸, 所以总有货卖。 我想如果你出得起价, 他也会卖给你。 ";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "这么说你是海盗? ";
			link.l1 = "你管这个干嘛? 如果你有胆子, 我可以安排你和泰瑞克斯谈谈。 如果不敢 --再见。 ";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "好好好, 别生气。 当然有胆子。 我想和泰瑞克斯做交易。 但你图什么? ";
			link.l1 = "如果你给的价格合适, 我大概能从马库斯那拿到不错的中介费。 所以你出多少? ";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "一卷25杜布朗, 这是你能得到的最高价, 相信我。 ";
			link.l1 = "25金币? 嗯, 不错。 我想泰瑞克斯会因为找到这样的买家欠我个人情。 很好, 成交, 我会告诉他。 但如果你骗了我, 后果自负。 ";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "别担心, 我们是诚实人。 我们的条件是: 每月10到15号送一百卷。 我们在这儿等... 等等, 换个地方, 这里不安全了。 去内格里尔角, 靠近马龙镇, 那里更安全。 暗号‘A merchant of Lyons’(里昂的商人)。 ";
			link.l1 = "知道了。 下月等第一批货吧。 ";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "告诉泰瑞克斯这次可以多带点货, 我们这个月没丝绸了。 ";
			link.l1 = "我会的。 再见, 朋友。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);// 隐蔽
		break;
		
		// 佩利.卡特尔
		case "Pelly":
            dialog.text = "啊哈! 什么风把你吹到我的船上了, 朋友? ";
			link.l1 = "嘿, 卡特尔。 马库斯.泰瑞克斯派我来的, 我们要进军马拉开波。 ";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "啊, 终于来了。 看来你是这次航行的新老大。 很好, 新舰队司令叫什么? ";
			link.l1 = ""+GetFullName(pchar)+"船长。 ";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "命令呢, "+GetFullName(pchar)+"上将? ";
			link.l1 = "我们分头前往马拉开波湖。 你要在夜间抵达, 并秘密在瓜希拉峡登陆。 在那里等我, 同时建立一个小营地。 至于我, 会在西班牙港口登陆。 ";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "是, 上将! ";
			link.l1 = "你需要多久到达那里? ";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "嗯... 大约一周左右。 多一天或少一天, 全看风向。 ";
			link.l1 = "好的。 那我们别浪费时间了。 朋友, 瓜希拉峡见。 ";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "是, 上将! ";
			link.l1 = "... ";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "上将, 有什么命令? ";
			link.l1 = "目前没有。 我正忙于我们的行动。 ";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "在岸边准备一个宽敞的箱子。 我们要把武器收集起来, 给我们被囚禁的兄弟。 ";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "那么, ‘帅哥’的情况如何? 我已经手痒想流点西班牙贵族的血了! ";
				link.l1 = "比我们想象的更复杂。 他说种植园的守卫太警惕了。 唯一能偷偷运武器的方法就是藏在货物里。 我们需要紧急弄一批咖啡。 椰干或香草 --当地种植园主只经营这些。 ";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "离开营地, 召集一支突击队。 是时候行动了, 我们在夜幕掩护下进攻。 ";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "听着, 上将, 我一直在想... ";
			link.l1 = "怎么了, 泰瑞克斯付钱让你思考而不是挥舞你的军刀吗, 卡特尔? ";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "吼! 种植园要起义了, 对吗, 上将? 火光! 我们能从中捞到金子! ..";
			link.l1 = "我需要在岸边准备一个箱子, 卡特尔。 ";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "马上办, 上将! ";
			link.l1 = "... ";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// 将箱子加载到地点并更改定位器
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "马上办, 上将! ..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "士兵们已准备就绪, 上将! ";
			link.l1 = "前进! ";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "上将, 看来我们本该救的那个泰瑞克斯的朋友... 有点死了。 ";
			link.l1 = "是啊, 但那里什么也做不了。 你看到守卫了, 我们能活下来就很幸运了。 ";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "上将, 马库斯会生你的气。 现在别去找他。 我要走了。 你也该走了。 ";
			link.l1 = "是啊... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "坏消息, 上将。 有一支西班牙中队从东边向我们驶来。 我们没时间逃跑了。 ";
			link.l1 = "他们有多少艘? ";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "三艘船。 很多炮。 我们完蛋了。 "; // 最后一个樵夫
			link.l1 = "走着瞧。 "// "让.你去卡特尔的船上。 卡特尔, 升起西班牙国旗, 张满帆离开这里 --希望你能冒充商人。 而我直接去找西班牙人 --把他们从你们身边引开。 我们在拉维加的泰瑞克斯那里见。 ";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "让, 你去卡特尔的船上。 ";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"但是... ";
			link.l1 = "卡特尔, 你应该升起西班牙国旗, 然后离开这里。 我会把他们从你身边引开。 拉维加见。 ";//"退下! 卡特尔, 你要拿脑袋向泰瑞克斯为让.皮卡德负责。 所有人上船! ";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "但是... ";
			link.l1 = "没什么但是! 卡特尔, 如果皮卡德到不了泰瑞克斯那里, 你就死定了。 所有人上船! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "上将, 有什么命令? ";
			link.l1 = "准备战斗。 听我命令就进攻! ";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "是, 上将... 听你命令! ";
			link.l1 = "... ";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "吼吼! 你好啊, 王子。 什么风把你吹到托尔图加来了? ";
			link.l1 = "又是马库斯的任务。 听着, 卡特尔, 为什么住在这房子里的混蛋不让我进去? ";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "加斯帕德.戈尔登蒂斯? 他只和信得过的人合作。 其他人需要推荐才能和他合作。 想卖些闪亮的小饰品? 如果你想, 我可以为你担保... ";
			link.l1 = "这么说他是个放高利贷的? 他的利息是多少? ";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "兄弟, 你搞错了。 加斯帕德不是放高利贷的, 如果你需要可以去找"+GetFullName(characterFromId("Tortuga_usurer"))+"。 戈尔登蒂斯收购各种宝石和珠宝。 顺便说一句, 他出价很高, 而且从不问愚蠢的问题。 每个海盗船长都是他的客户。 ";
			link.l1 = "我明白了... 有人告诉我, 他们中有些人甚至把钱托付给他... ";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "哈哈! 告诉你这个的人是个骗子, 去朝他无耻的脸上吐口水吧。 加斯帕德只做珠宝生意, 一直如此。 他为什么要惹上别人的钱财问题? ";
			link.l1 = "明白了。 谢谢你, 卡特尔, 海上见! ";
			link.l1.go = "Pelly_27";
			link.l2 = "嗯, 确实。 那么, 他收购小饰品? 有意思... 你说你可以为我美言几句? ";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "海上见, 王子。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "当然! 你现在是我们的人了, 呵呵! 在这儿等一下。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "都搞定了! 现在戈尔登蒂斯知道查理王子可能会去找他卖小饰品了。 记住, 虽然他的价格不错, 但还是比那些吝啬的高利贷者低。 但他按吨收购! 而且如我所说, 没有不必要的问题。 ";
			link.l1 = "这才是我的好兄弟! 干得好, 保罗! 现在我有地方处理所有战利品了! ";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "不, 让.皮卡德才是‘帅哥’, 我是‘卡特尔’, 哈哈! 再见, 王子! ";
			link.l1 = "谢谢, 卡特尔, 海上好运! ";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "我给你抓了三只小鸟, 王子。 发现它们藏在衣柜里和床底下。 很漂亮, 对吧? 哈哈哈哈! ";
			link.l1 = "我得说确实是。 而且它们也被照顾得很好。 固执先生一定很关心它们。 ";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "该死的! 你怎么会在这里, 王子? ";
			link.l1 = "卡特尔? ..我是循着声音和噪音来的, 但没想到会是你。 你到底怎么到这儿来的? ";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "不, 你为什么会在这里! 你总是在附近! 泰瑞克斯一定是派你来找宝藏的, 对吧? 该死的, 我又晚了... ";
			link.l1 = "泰瑞克斯? 不... 我从一个婊子那里买了张地图。 她可能也卖给你了, 嗯? 在托尔图加? 多狡猾的婊子。 不过她没撒谎 --看看这堆金子! 我会带更多人来搬这些... ";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "见鬼, 这确实是一堆金子! 但它不是你的, 也不是泰瑞克斯的! 我先找到的! 它是我的! 我怎么知道的不重要! 这不关你的事! ";
			link.l1 = "冷静点, 卡特尔, 你为什么这么生气? 看看这堆金子 --里面肯定有一百万。 也许更多! 足够我们俩分了! ";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "你总是能分到更好的一块, 王子! 但这次不行! 宝藏是我的! 我先找到的! ";
			link.l1 = "该死的, 保罗, 你怎么了? 我们不能在这里做个交易吗? 即使是这堆金子的一半也是一笔财富。 你以前从未有过这么多钱。 此外, 有一天我可能会找到一个有利可图的线索, 并告诉你。 ";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "想骗我吗, 王子? 没门! 我不会给你一个硬币, 一个几内亚也不给! 你迟到了! \n啊, 我知道你想干什么了! 你休想得到这金子!!! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "滑稽。 真的。 你是个喜剧演员, 上将。 但这是真的 --马库斯不喜欢那些试图智取他的人, 就像你。 但他重视聪明人。 ";
			link.l1 = "好了, 好了。 那么, 你在想什么? ";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "有些事你和‘帅哥’显然没有考虑到。 你计划在种植园发动起义。 好主意 --如果目标是掠夺或制造混乱的话。 但是... ";
			link.l1 = "但是什么? 你反对起义? 害怕了? ";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "我? 哈! 从不。 但想想如果‘帅哥’在屠杀中送命会发生什么。 我们该怎么跟马库斯说? 我来告诉你 --我们说什么都不重要。 反正他会剥了我们的皮。 ";
			link.l1 = "嗯。 那你有什么绝妙的计划? 我们得想办法把他救出来。 ";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "我们确实需要。 这就是为什么... 为什么不买下他呢? 正式地... 我的意思是。 一把金子可以从这些混蛋手里买下任何人 --甚至他们自己的母亲。 更何况可怜的让? ";
			link.l1 = "哈! 卡特尔, 你是认真建议我走进种植园, 要求买下皮卡德吗? 为了好玩, 我是不是还应该告诉他们我为谁工作? 你疯了吗? ";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "没必要那么说。 事实上, 恰恰相反 --假装你是个商人。 当然, 你没有扮演的胆量, 但你看起来也不像海盗。 无意冒犯, 上将, 但这是事实。 只要大步走进那个种植园, 表现得自信, 然后询问让。 主人可能会怀疑你是谁, 但他不会表现出来。 正如我所说 --一把金子能堵住嘴。 ";
			link.l1 = "那么这... 一把金子需要我们花多少钱? 整座山? ";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "也许吧。 但与其掉脑袋, 不如破财。 你在岸上的时候, 我可没闲着 --我换上了不那么像海盗的衣服, 四处打听了一下种植园和它谦逊的主人。 ";
			link.l1 = "你发现了什么, 卡特尔? ";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "可以说是市场价格。 这不是第一次有贵重的囚犯落入他手中。 通常, 他们要么上绞架, 要么更糟 --进入宗教裁判所的地牢。 ";
			link.l1 = "他卖他们多少钱? ";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "对于重要的人? 五百枚硬币。 当然是杜布朗。 ";
			link.l1 = "五百? ! ";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "种植园主, 你还能指望什么? ";
			link.l1 = "这个价格, 我可以装备一支小军队了! 那我为什么还要在船上囤积武器准备起义呢? 这足够打一场小战争了。 ";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "不管怎样, 这些武器以后对你的船员会有用的。 那么, 你觉得怎么样? ";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(值得信赖) 我只能说如果泰瑞克斯的奖励比我们在这里花的少, 那就有趣了。 但你是对的 --我们的生命更有价值。 我有杜布朗。 ";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "我现在没有那么多金山。 ";
				link.l2.go = "Pelly_44_1";
				notification("Trustworthy", "Trustworthy");
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "你知道吗, 卡特尔? 忘了它吧。 我们还是海盗吗? 还有让? 或者他漂亮的脸蛋是他唯一的资产? 准备好箱子 --我们坚持原计划。 ";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "如果你有, 我会很惊讶 --这是一大笔钱。 好吧, 等你准备好, 或者如果你想出更好的办法, 来找我。 ";
			link.l1 = "会的。 在这里等我。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "那么, 上将, 你凑够救皮卡德的金子了吗? ";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "是的, 我终于凑够了。 希望这能行。 ";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "我还在努力, 卡特尔。 ";
			link.l2.go = "exit";
			link.l3 = "我不会把我辛苦赚来的钱给那些贪婪的种植园主! 准备好箱子 --我们会像财富绅士一样行动。 这是我的决定。 ";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "哇。 你刚加入我们的船员, 就已经在花这么多钱了! ";
			link.l1 = "钱不是一切。 但沐浴在泰瑞克斯的荣耀中? 无价。 ";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "这一点无可争辩。 但正如你所说, 这不仅仅是钱的问题 --还有其他重要的事情, 上将。 ";
			link.l1 = "我现在好奇了。 什么? ";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "我告诉过你我已经调查了种植园的一切。 包括这里需要的商品和市场上流通的商品。 如果你想冒充合法商人, 你最好囤积这些商品, 而不是只是把一堆金子摔在种植园主的桌子上。 ";
			link.l1 = "有道理。 我们在说什么样的商品? ";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "嗯, 除了活货, 呵呵, 当地种植园主购买。 交易和转售咖啡。 椰干和香草。 所以... ";
			link.l1 = "我需要尽快在某个地方囤积这些东西。 或者袭击一支商队, 希望它携带我需要的东西。 ";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "不是随便什么商队。 我讨厌放弃, 但我自己留了一个线索。 一支携带你需要的东西的法国商队很快就会出现。 但有一个警告... ";
			link.l1 = "哦, 现在又怎么了? ";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "它挂着法国国旗。 ";
			link.l1 = "什么? ! ";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "我理解你的沮丧, 哈哈。 决定在你... 上将。 想要细节吗? ";
			link.l1 = "该死的... 好吧, 说出来。 我们没有太多时间 --如果你或我不咬他们, 其他人会的。 ";
			link.l1.go = "Pelly_52";
			// link.l2 = "I don't touch the French unless I have no choice。 End of discussion.";
			// link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "那你最好开始自己收集所有这些商品, 并且要快, 在‘帅哥’被卖给别人之前。 我也不能在这里无限期地闲逛。 ";
			link.l1 = "我想也是。 ";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_52":
            dialog.text = "这才像话! 我就知道你有这本事... 上将。 所以, 事情是这样的: 我可靠的联系人最近报告说, 大约两周后, 一支载有咖啡和香料的法国商队将出现在瓜德罗普岛水域。 它很大, 装备精良, 所以要做好充分准备。 ";
			link.l1 = "我还有什么选择。 ";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "你看起来很沮丧, 上将。 '帅哥'呢? 一切都泡汤了吗? ";
			link.l1 = "确实。 我赚了不少钱, 但那个固执的混蛋拒绝把皮卡德卖给我 - 即使是一堆杜布朗! ";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "真是个傻瓜! 现在怎么办? ";
			link.l1 = "我已经和种植园主安排好了卸货。 我们将不得不回到原计划 - 现在或永远! ";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "但我们甚至没有为'帅哥'和其他人准备任何东西! ";
			link.l1 = "没时间了! 登上船 - 我们会把武器和药品从我们的货舱偷偷塞进货物袋里。 别忘了升起西班牙国旗! ";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "听起来像个计划。 ";
			link.l1 = "反正我们没有时间做其他事情了。 行动! 卸货很快就会发生。 ";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "看看这是谁! '帅哥'! 从你完好的脸和冷静的步伐来看, 我猜一切都很顺利? ";
			link.l1 = "顺利只是轻描淡写 - 我不仅避免了战斗并买回了让, 还赚了一些钱。 你的计划完美无缺, 保罗。 地平线上一切平静吗? ";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "尽可能平静。 回马库斯那里去? ";
			link.l1 = "对。 ";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("shore37", "boat", false);
			bQuestDisableMapEnter = false;
			AddQuestRecord("Roger_3", "29");
			pchar.questTemp.Mtraxx = "plant_success";
			QuestSetCurrentNode("Terrax", "mtraxx_27");
			//SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
			SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);
			
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			
			sld = &Locations[FindLocation("shore37")];
			sld.DisableEncounters = false;
			sld = ItemsFromID("fire");
			sld.shown = false;
			DeleteAttribute(sld, "fire");
			for (i=1; i<=4; i++)
			{
				if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
				{
					sld = characterFromId("Pelly_sailor_"+i);
					sld.lifeday = 0;
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
				}
			}
			sld = characterFromId("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 5);
			sld = characterFromId("mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
		break;
		
		case "Pelly_62":
            dialog.text = "嗯, 如你所愿, 上将。 但如果'帅哥'出了什么事, 我会确保泰瑞克斯知道你无视了我的建议。 箱子都准备好突围了吗? ";
			link.l1 = "让我再检查一下箱子里有什么。 ";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "一定要确定。 我可以帮你, 只收少量费用, 补偿我的努力, 呵呵。 ";
			link.l1 = "怎么帮? ";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "我在马拉开波有一个联系人, 一个军火商。 我会伪装自己, 偷偷进去, 付钱给他, 安排把武器偷运到这里。 但这会花费你 - 当然是金杜布朗。 ";
			link.l1 = "你为什么不早点把我介绍给这个人? 这会让我损失多少? ";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "我是否也应该把你介绍给我所有的线人? 好吧。 加上费用。 风险和我的分成... 大约和'帅哥'的赎金一样多。 ";
			link.l1 = "卡特尔, 敬畏上帝... ";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "我既不敬畏上帝也不敬畏你, 上将。 但如果我们没能救出让, 马库斯的愤怒? 那是另一回事。 那么, 你打算怎么办? 需要帮忙搬箱子吗? ";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "好吧, 去吧 - 已经浪费了足够的时间。 给, 这应该是正确的金额。 ";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "这是一大笔钱, 保罗。 我需要考虑一下。 ";
			link.l2.go = "Pelly_67";
			link.l3 = "对于一小批我可以以更便宜的价格批量购买的武器来说, 这太贵了! 不, 谢谢, 我自己处理。 ";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "好吧, 慢慢想。 但记住 - 当你在思考的时候, '帅哥'脸上和身上的瘀伤数量正在每小时增加, 呵呵呵。 ";
			link.l1 = "我会把杜布朗给你... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "这不是关于货物的大小 - 而是关于时间和风险。 但随你便。 ";
			link.l1 = "相信我, 我知道。 只要把箱子准备好 - 我从这里接手。 ";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "准备好了吗, 上将? 需要武器帮助, 还是你仍然缺钱? ";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "终于够了! 拿着, 把这事解决了 - 这让我很紧张。 ";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "注意你的语气, 卡特尔。 我准备好了, 但我需要更多时间来筹集资金。 ";
			link.l2.go = "Pelly_67";
			link.l3 = "对于一小批我可以以更便宜的价格批量购买的武器来说, 这太贵了! 不, 谢谢, 我自己处理。 ";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "哦, 这是多少杜布朗啊! 但别担心 - 每枚硬币都将用于计划。 否则, 马库斯以后会把我从坟墓里挖出来, 呵呵。 现在, 你去见'帅哥'吧, 上将, 告诉他一切都安排好了。 ";
			link.l1 = "在这里我才是发号施令的人。 现在, 行动起来。 ";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "是的, 有问题。 你打算怎么办, 海军上将?";
			link.l1 = "我需要在这里快点买到东西。 或者袭击一支商队, 希望能得到我需要的东西.";
			link.l1.go = "Pelly_49";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// 让.皮卡德
		case "rocur":
            dialog.text = "你想从我这里得到什么? ";
			link.l1 = "我的朋友, 我在找让.皮卡德。 你有机会也叫这个名字吗? ";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "有机会。 但是, 我不记得你的脸。 ";
			link.l1 = "别太粗暴, 让。 我是马库斯.泰瑞克斯派来的。 我的命令是把你从这里救出去。 ";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "马库斯? 嘘... 嘘。 对不起, 朋友, 我不知道。 但我们不应该在这里说话, 该死的守卫无处不在, 他们总是在监听... 我看你是西班牙人的贵客, 晚上在其中一间小屋里找我, 我们再谈。 我会等你, 兄弟。 ";
			link.l1 = "... ";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "嗯, 这里很安全... 你叫什么名字, 兄弟? ";
			link.l1 = ""+GetFullName(pchar)+"船长。 现在告诉我, 你是怎么落到这个地步的。 泰瑞克斯想知道一切。 ";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "在威廉斯塔德的一家酒馆里, 一个陌生人找到了我... 他让我做他的同伴, 去掠夺一些荷兰商队。 我有一艘双桅帆船, 他有一艘三桅船, 也是非常独特的。 所以我们在加拉加斯附近追上了一支商队并掠夺了它... 那是晚上, 我们正在分赃, 这时一艘巨大的西班牙大帆船在黑暗中出现\n我的同伴逃跑了, 我也逃跑了。 但我受损的双桅帆船无法从一艘大帆船和另外两艘船手中逃脱。 他们登上了我们的船, 把所有幸存者像牛一样卖到了这个地方。 ";
			link.l1 = "我明白了。 你认为这是意外吗? 我是说大帆船。 ";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "我怎么知道。 他们可能听到了枪声, 离大陆不远。 ";
			link.l1 = "嗯。 有可能。 你以前见过你以前的同伴吗? 他是谁? ";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "以前从未见过。 他说他的名字是伊格纳西奥.马可, 英国的私掠船船长。 他给人的印象是一个严肃的人, 这就是为什么我同意参与这次行动。 他是一个经验丰富的水手和船长, 这是肯定的, 他身后有一支时髦的船员, 他的三桅船是个美人, 不是每天都能看到那样的船。 ";
			link.l1 = "伊格纳西奥.马可? 英国私掠船船长? 他是西班牙人吗? ";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "他是葡萄牙人, 不是西班牙人。 英国的私掠许可证有什么问题? 你知道我们这类人中有很多西班牙人。 ";
			link.l1 = "我明白了。 好吧, 让我们谈谈你从这里逃脱的事。 有什么想法吗? ";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "你们有多少人? ";
			link.l1 = "我的船, 一艘三桅帆船, 还有佩利.卡特尔的人。 我的船停在马拉开波港。 卡特尔已经在瓜希拉峡登陆并在那里建立了营地。 ";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "嗯... ";
			link.l1 = "怎么了, 你指望泰瑞克斯派一艘战列舰来这里? ";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "我没指望什么。 事实上, 我很惊讶马库斯没有忘记我。 ";
			link.l1 = "显然, 他没有。 那么, 有什么想法? ";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "没有机会从这里逃脱 - 这个种植园守卫太森严了, 周围都是野生丛林。 强攻也没有意义, 你没有足够的人手, 而且附近还有一座堡垒。 ";
			link.l1 = "也许, 你和你的人可以从内部帮助我们? 从背后狠狠打击他们。 ";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "用什么? 赤手空拳和生锈的弯刀? ";
			link.l1 = "如果你有武器呢? ";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "那么我们会让他们地狱。 但有一个问题, 他们检查你带进去的所有东西, 没有办法走私武器。 所以我建议忘了这个。 ";
			link.l1 = "尽管如此, 这是我们目前最好的选择。 我会想办法把武器交给你和你的人... 告诉我, 你们中有多少人能战斗? ";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "三十个人, 我想。 ";
			link.l1 = "那么三十把军刀... 我相信手枪也会有所不同。 ";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "船长, 你是认真的吗? ";
			link.l1 = "我是认真的。 我是特意来这里的, 开玩笑不是我的目的。 你还需要什么? ";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "很好... 至少让我们试试。 我们需要简单的冷兵器 - 我的人没有受过使用花哨细剑之类的训练。 手枪也是如此, 最便宜的就可以。 如果你们能给我们几支火枪, 那也会对我们有很大帮助, 我有几个擅长火枪的人。 子弹, 火药。 治疗药水是最受欢迎的。 ";
			link.l1 = "知道了。 刀刃和斧头可以从船上的武器库中取出。 其余的更难弄到。 我有了一切就会告诉你。 ";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "请快点, 兄弟。 我们在这里没有半年时间, 这该死的牛工作正在一个接一个地杀死我们。 如果你需要我 - 晚上来找我。 ";
			link.l1 = "知道了, 兄弟。 坚持住, 我会尽量不让你等太久。 小心点, 别给他们一个理由把你划掉, 还没到时候。 ";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; // 移除计时器
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // 计时器
		break;
		
		case "rocur_wait":
            dialog.text = "有什么消息吗, 兄弟? 你收集武器了吗? ";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "是的。 一个装有弹药的箱子在瓜希拉峡。 剩下的就是想办法把它偷偷运进种植园。 ";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "我正在处理。 等等。 ";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "很好, 船长。 我已经在想如何执行了。 ";
			link.l1 = "很高兴听到这个。 你在想什么? ";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "这个种植园生产糖和种植可可豆。 有时园主会自己出售商品, 这样更有利可图。 向他报价吧。 不要用钱支付, 而是用货物。 比如你可以把椰干。 香草或咖啡装进箱子里。 在讨价还价上花点功夫, 但别过头了。 \n在一两个箱子里藏匿武器, 并在上面做标记。 安排在傍晚进行交换, 这样他们就不得不把箱子在外面放一整夜。 \n到了晚上, 我们会找到你做标记的箱子, 武装自己, 给西班牙人好看。 当然, 需要你的帮助。 ";
			link.l1 = "好想法, 兄弟! 非常好, 我喜欢这个计划。 就这么办吧。 ";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "最后一件事 --只提供一种商品进行交换。 商品种类越多, 守卫检查的箱子就越多。 ";
			link.l1 = "我同意。 那我就只选一种。 你说的是咖啡。 香草和椰干吗? ";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "是的。 这对种植园主来说会是个好交易。 ";
			link.l1 = "明白了。 等交易谈成了我会告诉你。 ";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "去吧, 我的朋友, 时间宝贵, 我们没有多余的时间了... ";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "... ";
			link.l1 = "(轻声地) 交易谈成了。 箱子明天傍晚送到种植园。 你需要的箱子标有‘W’字母。 其他箱子上标有字母表的其他字母。 让你的人做好准备。 我们将在黎明前大约三点钟发动攻击。 ";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "我们将以你的信号为开始... ";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "终于! 我即将再次见到大海了! 我几乎忘记了它的样子和气味。 做得好, 船长! 我欠你一个人情。 ";
			link.l1 = "别担心, 我们以后再算... 现在让我们登船离开这里! ";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "问候你, "+pchar.name+"。 很高兴再次见到你, 也很高兴在这次冒险中能有你作为同伴。 这项任务会很艰巨, 但我相信我们能挺过去。 ";
			link.l1 = "很高兴再次见到你, 皮卡德。 我洗耳恭听, 跟我说说你的这次冒险吧。 ";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "我已经告诉马库斯了, 现在我告诉你。 当我在马拉开波的种植园当奴隶时, 从西班牙人那里了解到一些事情。 他们喝醉了之后话很多... 听着, 从马拉开波湾向东南方向, 有一个小村庄。 它隐藏在两座山之间的丛林深处。 名字很糟糕: 圣地亚哥-德-洛斯-卡瓦列罗斯-德-梅里达。 我们就叫它梅里达吧。 \n听起来还不是很有趣, 是吧? 结果环绕村庄的山脉富含宝石。 祖母绿。 蛋白石和传说中的火蛋白石。 \n据我所知, 梅里达的定居者没有告诉总督关于这些宝石的事。 然而, 他很快就会知道, 这就是为什么我们应该在西班牙殖民官员到达之前访问梅里达。 ";
			link.l1 = "你想掠夺这个定居点? ";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "正是如此。 它在丛林和山脉中与世隔绝, 只有一小队驻军 --对于一支海盗小队来说很容易下手。 此外, 他们离大海很远, 除了拿着长矛和弓箭的野蛮人, 他们没料到会有任何人攻击他们。 ";
			link.l1 = "你有多确定这个定居点确实有宝石? ";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "如果我们的冒险被证明是虚假的线索, 我自己将在你的船上担任军官或水手, 我会擦洗甲板, 并在无数次登船战斗中作战, 直到我欠你和马库斯的债务还清。 ";
			link.l1 = "我明白了... 很好, 你知道怎么去梅里达吗? ";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "我当然不知道穿过丛林的确切路径, 但我们会从印第安人那里雇一个向导。 我们应该在马拉开波湖以南登陆, 找到一个印第安村庄, 然后找到那些知道如何到达那里的人。 ";
			link.l1 = "... ";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "船长, 我为我的语言深感抱歉, 但我们到底为什么还没到梅里达? 嗯? 你已经对我们的共同事业不屑一顾了! 我和小妖精要自己走了。 我会向泰瑞克斯解释一切, 你应该离开。 给, 这是5万比索, 作为你在马拉开波帮助的报酬, 我从朋友那里借来的。 再见, 真遗憾, 我原本对你期望更高。 ";
			link.l1 = "嗯... 对不起。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "我们到了。 前方就是丛林。 首先, 我们应该找到一个印第安村庄, 四处问问找个向导。 ";
			link.l1 = "那就这么办。 卢克, 你有什么要说的... 或者建议吗? ";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "梅里达的驻军已经解决了。 我预计村庄内部不会有严重的抵抗。 我们走! ";
			link.l1 = "冲锋!!! ";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "完成了! 没有幸存者了。 现在我们应该和这个‘城市’的总督谈谈。 我希望他是个能被说服的类型。 ";
			link.l1 = "我同意, 让我们‘说服’他! ..让! 跟我来! ";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //邪恶选项
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //和平选项
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "干得好, "+pchar.name+"! 是时候分赃了。 我已经算好数目了。 箱子里差不多有2000颗宝石: 1560颗祖母绿, 1032颗蛋白石和363颗火蛋白石。 你的那份是三分之一: 350颗祖母绿, 244颗蛋白石和63颗火蛋白石。 给, 拿着吧。 ";
            }
            else
           	{
           	dialog.text = "干得好, "+pchar.name+"! 是时候分赃了。 我已经算好数目了。 箱子里差不多有2000颗宝石: 1050颗祖母绿, 732颗蛋白石和189颗火蛋白石。 你的那份是三分之一: 350颗祖母绿, 244颗蛋白石和63颗火蛋白石。 给, 拿着吧。 ";
           	}
			link.l1 = "太好了! ";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "现在让我们谈谈你救我所欠的人情。 我知道你有不少开销。 你认为多少补偿才算公平? 我会从我的宝石份额中支付。 ";
			link.l1 = "你份额的三分之一就够了。 你也需要钱 --买船。 补给和支付船员... ";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "谢谢你, 朋友! 我以为你会要不少于一半。 我现在确实需要钱。 给, 拿着这些宝石。 ";
			link.l1 = "真是次成功的突袭, 让! 我们去伊斯帕尼奥拉岛, 找泰瑞克斯。 ";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // 释放修复
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// 计时40天回家
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "哦, 真是巧会! 很高兴见到你, "+pchar.name+"。 你最近怎么样? ";
			link.l1 = "相当不错。 最近刚找到红狼的宝藏。 现在正前往马提尼克岛见我们的一个共同朋友。 你想见泰瑞克斯吗? ";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "是的。 想和他谈谈帕斯夸莱.拉瓦锡的事。 马库斯派我去找那个半土匪半商人。 我照他说的做了, 可那家伙用一堆垃圾当报酬, 还声称那是非常好的付款。 我本想当场杀了那混蛋, 但马库斯让我尊重他... 那就让他自己处理这烂摊子吧。 ";
			link.l1 = "抱歉, 但马库斯不会做什么的。 四眼仔和他有生意往来。 ";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "什么鬼? ";
			link.l1 = "是啊, 但我没告诉你这个, 好吗? 拉瓦锡不久前也坑了我。 泰瑞克斯让我帮他, 就像他让你做的一样。 我在宝藏岛被警告过, 惹四眼仔就等于惹马库斯。 所以我建议你忘了这事。 你既不是第一个, 也不是最后一个遇到这种情况的人。 ";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "我明白了。 这么说你也被那两个家伙坑了? ";
			link.l1 = "嗯, 是的。 我本想在了解更多之前给四眼仔制造点麻烦。 但这不值得。 ";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "如果你知道没人会发现, 你会尝试报复那混蛋吗? ";
			link.l1 = "哈! 当然会! 尽管我不知道怎么做。 袭击拉瓦锡的船队, 总有一天你的水手会喝醉说漏嘴。 你不知道这其中的厉害吗? ";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "你现在要去马提尼克岛吗? 你什么时候再到拉维加? ";
			link.l1 = "马库斯给了我三周时间。 ";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "尽量在两周内赶到。 我会好好考虑... 14天后在戈纳夫湾找我。 直接去那里, 别进拉维加。 ";
			link.l1 = "我看你是有什么打算, 哈哈哈。 好吧。 我会尽力。 ";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "你最好做到。 再见! ";
			link.l1 = "... ";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // 测试修正3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请遵守最后期限! ");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"你的船呢? 你是从拉维加来的吗? 妈的! 我让你悄悄来这里。 我的计划现在泡汤了。 该死的! ..";
				link.l1 = "嗯... ";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "你来了, "+pchar.name+"。 很高兴你能来。 让你的伙伴们回船上吧。 这是私人谈话。 ";
				link.l1 = "很好。 ";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "你来了, "+pchar.name+"。 很高兴你能来。 我有笔生意找你。 准备好听了吗? ";
				link.l1 = "当然! ";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "我已经告诉过你了 --把你的军官们打发走! ";
				link.l1 = "是是, 我知道了。 ";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "很好。 现在我们可以自由交谈了。 我有笔生意找你。 准备好听了吗? ";
				link.l1 = "当然! ";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "你很了解拉维加吗? ";
			link.l1 = "嗯... 我想是的。 你为什么这么问? ";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "有没有注意到当地商店右边的仓库? 就是棚屋中唯一的大房子。 ";
			link.l1 = "总是关着的那个? 是的, 我见过。 怎么了? ";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "观察得很仔细 --它总是关着的。 当你在马提尼克执行任务时, 我们的共同朋友拉瓦锡作为马库斯.泰瑞克斯的客人在这里待了三天。 他们在这房子里喝朗姆酒, 寻欢作乐。 ";
			link.l1 = "嗯... ";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "然后拉瓦锡的人把一些箱子和包裹拖进了房子。 然后他就离开了。 至于马库斯, 他每天都在那个地方待几个小时。 ";
			link.l1 = "有什么建议吗? ";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "什么建议? 我敢肯定这房子一定是拉瓦锡在拉维加的基地。 我透过窗户没看到太多, 但里面储存着货物。 我认为四眼仔有办法偿还他欠我们的东西。 ";
			link.l1 = "嗯嗯... 你想闯进去? 那扇关着的门呢? 它又重又结实, 我们不可能悄无声息地闯进去。 ";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", 你觉得我是个白痴吗? 我已经解决了。 我用锁的蜡模配了把钥匙。 花了我不少钱, 但这是我的事。 ";
			link.l1 = "嘿! 那为什么等我? ";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "这样更安全, 而且你是我唯一能信任的人。 一个脑袋好, 两个脑袋更好, 四个眼睛比两个强。 ";
			link.l1 = "是啊, 惹拉瓦锡需要和他一样多的眼睛, 哈哈哈! 但泰瑞克斯呢? 如果我们检查帕斯夸莱的东西时他进了房子怎么办? ";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "他不会的。 他总是在午夜前回到自己的房子。 准备好明晚去拉维加了吗? 他们永远不会知道是谁搞砸了他们: 你还在马提尼克, 而我一周前就离开了拉维加。 ";
			link.l1 = "我很想搞砸那个四眼混蛋。 但告诉我, 让, 我们该怎么从房子里搬 barrels 和箱子? ";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "我相信我们会在那里找到比箱子和货物更有价值的物品, 而且会轻得多。 那么, 你加入吗? ";
			link.l1 = "当然加入! ";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "太好了, 很高兴我没有看错你。 现在我们休息一下, 午夜前往拉维加。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "该走了。 我们应该抢劫这个混蛋, 在黎明前离开那里。 ";
			link.l1 = "前进! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "嘘... 现在行动, 悄悄地到帕斯夸莱的房子。 跟我来。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "看看这个 --这么多东西到处都是。 我们开始吧。 检查门边的箱子, 然后上楼去一个房间。 我会待在这里: 我知道在垃圾中隐藏贵重物品的技巧。 保持警惕, 远离窗户。 ";
			link.l1 = "好的... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", 你找到了什么? 有什么有趣的东西吗? ";
			link.l1 = "过来看看。 这东西不错。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "该死的! 现在我知道为什么泰瑞克斯每天都来这个地方了。 这不仅是四眼仔的仓库, 还是个妓院。 ";
			link.l1 = "看来她是这里的奴隶。 ";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "当然。 看看她 --显然是个港口妓女... 我们真倒霉。 我们必须杀了她。 ";
			link.l1 = "我们真的必须这样做吗? ";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "她看到了我们的脸, 听到了你的名字。 她会把一切都告诉泰瑞克斯。 ";
			link.l1 = "嗯... ";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "这是你的选择。 她的生命可能会让你付出生命的代价。 ";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "别想信任这个妓女。 明天泰瑞克斯就会知道一切。 你想收到黑标记吗? ";
			link.l1 = "不, 我不想。 而且我也不想杀这个女人 --我有用得着她的地方。 她要跟我走。 ";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "别当傻瓜! 她一有机会就会逃跑。 看看她的额头, 看到那个烙印了吗? 她是个小偷。 ";
			link.l1 = "嗯。 你可能是对的, 让。 很好, 解决她, 我们离开这里。 ";
			link.l1.go = "rocur_82";
			link.l2 = "我不打算把她留在我的船上。 我有一个她永远无法逃脱的地方, 而且那里也没有耳朵听她尖叫。 她还会在那里继续她的工作... 一个免费的私人妓女, 呵呵! ";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "好了, 现在她不会对马库斯说任何话了... ";
			link.l1 = "可怜的女孩... 哈哈, 正如他们所说, 幸运女神是个婊子... ";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "你是个善良的人, "+pchar.name+"。 你为什么要自找麻烦带上她? 啊, 不管了, 这是你的选择。 确保我们离开时她保持沉默。 ";
			link.l1 = "如果她不沉默 --她就死定了。 ";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "有一点。 一个装满杜布朗的箱子, 一把红宝石, 一张伊斯帕尼奥拉岛的地图和一些朗姆酒。 ";
			else sTemp = "没什么有价值的东西。 ";
            dialog.text = "你找到了什么? ";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("你获得了两批宝藏收藏。 ");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "我这边运气更好。 给, 拿着你的那份。 我自己根本没法把这些东西都带到岸边。 四眼仔全额支付了我们。 ";
			link.l1 = "太棒了! 干得好, 让! ";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "现在快走! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "太好了。 完成了。 悄无声息。 现在, 我们回船上吧。 ";
			link.l1 = "哈, 好主意。 ";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "好了, "+pchar.name+"。 我们该分道扬镳了。 我不确定我们是否还会再见面, 但要知道认识你是我的荣幸, 朋友。 ";
			link.l1 = "啊, 得了吧, 我们会在拉维加经常见面的。 ";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "不。 我和泰瑞克斯 done 了。 和拉瓦锡的这摊烂事是最后一根稻草。 ";
			link.l1 = "嗯... 我明白了, 就忘了它吧。 我们已经得到了我们应得的。 泰瑞克斯会提供有利可图的线索, 不是吗? 上次我从红狼的宝藏中赚了超过五十万。 ";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "那告诉我, 你为找到它付出了很多努力吗? ";
			link.l1 = "嗯... 并不容易。 做了很多思考。 旅行和战斗。 我认为这是值得的。 ";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "你付给泰瑞克斯多少? ";
			link.l1 = "三分之一。 ";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "他在这笔生意中扮演了什么角色? 马库斯具体做了什么? ";
			link.l1 = "嗯... 他给了我红狼的日志... ";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "就这些? 对吗? ";
			link.l1 = "嗯... 否则我永远不会知道伍尔夫里克船长... ";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", 你还不明白吗? 泰瑞克斯让别人去做脏活! 你以为如果他自己能找到宝藏, 还会给你找宝藏的任务吗? 当然不会! 我敢打赌, 他先是自己尝试, 搞砸了之后, 才叫你来做这个工作。 而当你在思考。 在海上航行了数周。 战斗并冒着生命危险时, 这个混蛋和他那恶心的四眼朋友正在拉维加和妓女鬼混。 就因为这个, 他还得到了二十五万比索。 就那样。 \n你以为他派他的狗小妖精来帮助我们突袭梅里达吗? 不, 他是想确保他的利益安全。 马库斯自己能做的一切, 他都自己做, 要么独自行动, 要么借助卡特尔。 秃头。 小妖精和其他为了几分钱为他工作的愚蠢白痴。 像你我这样的人, 得到的是马库斯自己太蠢而无法执行的线索。 \n还记得你为他做的所有任务吗? 算算他从你身上赚了多少。 我受够了。 现在我有钱了, 有一艘很棒的护卫舰, 还有忠诚的船员... 从现在起我是自由职业者。 我要去牙买加, 也许在那里我会拿到私掠许可证。 ";
			link.l1 = "我不认为你对泰瑞克斯的看法完全正确... 但祝你好运, 让! 希望你在牙买加获得成功。 ";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "我会的。 也祝你好运, 想想我说的话。 做马库斯的走狗不是你最好的角色, 我知道你有能力做更多。 好吧... 再见, 兄弟! 一路顺风! ";
			link.l1 = "狩猎顺利, 让! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", 告诉我, 我们怎么会在丛林里花了这么多时间? 现在我的计划搞砸了。 呃... 再见, 朋友... ";
			link.l1 = "呵... ";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "伙计们, 该走了。 该死, 王子, 你让我惊讶。 烧毁了整个城市, 却在关键时候拒绝弄脏自己的手。 ";
				link.l1 = "我没有下令烧毁城市! ";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "伙计们, 该走了。 卢卡斯, 你错过了。 王子处理得很出色 --而且赚了不少钱! ";
				link.l1 = "那城市呢, 帅哥? ! 我保证过的! ";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "至少你没有试图拯救它。 否则, 我们的人会先把你开膛破肚。 这对他们来说是艰难的一天。 他们应该发泄一下。 你会习惯的。 你完全有潜力。 ";
			link.l1 = "谢谢你的建议, 但我不记得我问过。 我们走吧。 ";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = "我以为你在开玩笑。 好吧... 你太草率了。 城市完了。 当海岸兄弟会开始行动时, 总是这样。 你会习惯的。 ";
			link.l1 = "我不确定我会习惯。 好吧, 我们走吧。 ";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "兄弟... 刚才那是怎么回事? ";
			link.l1 = "怎么了, 你不明白吗? 我买了你。 你曾经说过我能接触到西班牙人, 所以我利用了这一点。 ";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "我明白了 --我不是白痴。 但我们不是在执行另一个计划吗? ";
			link.l1 = "嗯, 卡特尔和我觉得如果你在起义或追逐中死去, 会不太合适, 所以我们决定直接买下你。 ";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "哈, 别侮辱我。 毕竟我是泰瑞克斯的船长之一。 我知道如何握剑。 ";
			link.l1 = "我不怀疑这一点, 但你真的对重获自由感到不满吗? ";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "不, 不 --我很感激。 只是... 花那么多金子是不是有点过分了? 我一想到就觉得恶心。 另一方面, 那个种植园主看起来像抛光的银盘一样闪亮。 ";
			link.l1 = "是啊, ‘世纪交易’, 确实。 当然有点心疼。 但时间比金子更宝贵, 让。 为你们所有人寻找手枪和药品... ";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "我很感激, 但兄弟, 你是个傻瓜 --无意冒犯。 我告诉过你我的人不擅长用剑。 但任何人都可以扣动扳机。 你本可以从船舱里拿任何手枪和药品来, 就像弯刀和斧头一样 --他们不挑剔。 ";
			link.l1 = "嗯, 老实说, 我没想到... 不管怎样, 我们走吧 --卡特尔可能等得不耐烦了。 ";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// 卢克.勒普里康
		case "lepricon":
            dialog.text = "问候你, "+GetFullName(pchar)+"船长。 卢克.勒普里康为你服务! 听说我们要去南美大陆的丛林了。 ";
			link.l1 = "正是。 登上长艇, 我们马上出发。 ";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "让一个老海盗给你一些建议, 船长。 既然我们要去丛林 --肯定会遇到印第安人。 给他们带些礼物。 印第安战士喜欢漂亮的手枪, 尤其是决斗用的。 他们也喜欢指南针和望远镜。 他们把这些当作魔法物品。 \n他们的女人更喜欢便宜的珠宝和镜子。 扇贝壳之类的小饰品。 如果我们和他们发生战斗, 使用长号和火绳枪: 一般来说, 葡萄弹对不穿盔甲的敌人非常有效。 至于定居点本身, 我建议使用可以装纸弹药筒的枪。 ";
			link.l1 = "非常好, 卢克。 我记下你的话了。 欢迎登船。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "我们一到村子就去见酋长。 一定要带礼物, 否则毫无意义。 确保询问他的族人中是否有人知道前方丛林中的秘密通道, 并寻找那些不怕旅行的人。 我和你一起去, 遇到任何困难都可以找我。 ";
			link.l1 = "我们走! 让, 卢克 --跟我来! ";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "有什么问题吗, 船长? ";
			link.l1 = "现在没有, 卢克。 ";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "是的! 我和他们的酋长谈过了, 我送了他礼物, 后来他召集了他的红皮肤人开会。 他们中有人知道怎么去梅里达, 但没人愿意去 --他们害怕另一个叫卡彭斯的部落。 那些人把当地人吓得屁滚尿流。 那个红皮肤混蛋声称我们自己没有机会找到路, 也没有向导可雇。 那么我们现在该怎么办, 嗯? ! ";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "我有解毒剂。 ";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "嗯, 我明白了... 船长, 你必须知道, 贪婪往往能战胜恐惧。 承诺一笔丰厚的报酬, 让一个人愿意接受这份工作... 你知道吗? 试试更狡猾的选择 --他们的女人。 送给她们礼物, 问问她们的男人, 你很可能会找到我们需要的向导。 承诺给她成堆的珠子和镜子, 让她丈夫帮忙。 要慷慨, 承诺很多, 说服她们。 ";
			link.l1 = "嘿! 至少我可以试试, 尽管我不确定这是否有效... ";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "嗯, 还有另一个选择... 但这并不是一个好选择, 如果你明白我的意思。 ";
			link.l1 = "另一个选择? 告诉我! 我不太想跑到印第安女人面前, 求她们说服丈夫加入我们。 ";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "这个选择和时间一样古老。 让他们知道, 比起害怕卡彭斯, 他们更应该害怕你。 你知道... 你可以告诉酋长, 你的海盗能对村里所有女人做什么, 尤其是他的妻子和女儿。 你甚至可以威胁要折磨她们。 \n不管怎样, 我相信你会想出办法让这些印第安人害怕你。 就我个人而言, 我不喜欢这条路, 原因有几个。 ";
			link.l1 = "原因? 比如? 在我看来, 这似乎是一个非常有效和直接的解决方案。 ";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "首先, 之后我们在那里不会受欢迎。 我们可能会走进陷阱或其他麻烦。 其次, 嗯... 这感觉不对。 消灭武装对手是一回事, 但威胁妇女完全是另一回事。 我建议用更... 外交的方式处理印第安人。 ";
			link.l1 = "知道了, 我会考虑的。 也许我会试着用珠子讨好某位女士... 或者为酋长的女儿们想出一些有创意的折磨方式, 哈哈! ";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "还有一件事, 船长, 根据酋长的说法, 我们在丛林中可能会遇到一个敌对的印第安部落, 很可能只是一小群食人族, 但最好还是小心为妙。 如果是好战的部落, 他们会在武器上涂毒, 所以一定要给你的人提供解毒剂。 \n我和我的人总是随身携带大量药水。 至于你的海盗... 把解毒剂带给我, 我会确保分发给你的人。 我至少需要十几瓶药水。 确保你自己和你的军官也带一些。 ";
			link.l1 = "好的。 我会带解毒剂。 ";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// 让其出海
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // 计时器, 避免长时间停留
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "很好。 把它们给我。 我会处理剩下的。 ";
			link.l1 = "给你... ";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "四十二瓶药水足够了。 剩下的你应该自己留着。 ";
			link.l1 = "好吧... ";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "船长, 你的印第安人 --哈亚米和塔戈法等你兑现承诺的礼物太久了, 已经去另一个村庄跳舞喝卡谢里酒了。 我有一种感觉, 你的做事方式对我们没有好处。 很抱歉, 但你被排除在外了。 皮卡德将领导这次探险。 ";
			link.l1 = "去你们的吧! ";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "船长, 搞什么鬼? 我们浪费了太多时间, 一无所获! 我有一种感觉, 你的做事方式对我们没有好处。 很抱歉, 但你被排除在外了。 皮卡德将领导这次探险。 ";
			link.l1 = "去你们的吧! ";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "船长, 搞什么鬼? 你有十天时间去找皮革和木板。 附近就有马拉开波镇! 我有一种感觉, 你的做事方式对我们没有好处。 很抱歉, 但你被排除在外了。 皮卡德将领导这次探险。 ";
			link.l1 = "去你们的吧! ";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "船长, 很抱歉, 但我早就该到拉维加了, 实际上你也该到了。 你一定是忘了我和马库斯的存在。 不管怎样, 我要走了。 你应该继续做你正在做的事情, 我会向马库斯解释一切。 再见, 真遗憾, 我原本对你期望更高。 ";
			link.l1 = "哼... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "那么, 据我所知, 你们打了一架。 没能分赃, 对吗, 查理王子? ";
			link.l1 = "小妖精? 你也在这里... 不过也不奇怪。 是的, 那些贪婪的混蛋无视了《海盗法典》, 还想杀了我。 ";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "是的, 他们把你打得够惨, 王子。 你看起来像湿漉漉的屎。 \n你说《法典》? 让我告诉你: 我一直在和据说是《法典》守护者的马库斯合作, 我见过太多人无视它, 我都不敢数了。 有些人付出了可怕的代价。 有些人没有。 \n你可以做任何你想做的事, 只要回报足够。 尤其是在没人注意的时候。 ";
			link.l1 = "那么... 你也是来寻宝的? ";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "问得真蠢。 不然我还能在离伊斯帕尼奥拉岛这么远的地方做什么? 不过, 毕竟我比你们都聪明: 了解你们腐烂的海盗本性。 我只是等着, 让你们这些老鼠互相撕咬, 最后只留下一个活着但受伤疲惫的敌人。 ";
			link.l1 = "敌人? 这就是你遵守你主人《法典》的方式? ! 他为此杀人! ";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "我不受《法典》约束, 王子, 我不是海盗。 我甚至没有船 --我不得不租了个破船到这里。 我本质上只是个冒险家。 我是个猎人, 猎杀水牛, 成为冒险家。 那些声称我们法国冒险家破坏了他们生活的西班牙人, 让我不得不向马库斯寻求支持和保护。 有时我帮他做生意。 \n虽然我不是海盗, 但我和我的人战斗得很好, 你见过我们的行动。 ";
			link.l1 = "我们曾一起突袭和战斗, 小妖精。 我们互相掩护, 冒着生命危险拯救彼此。 这对你来说算什么? ";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "老实说, 王子: 我从来都不喜欢你。 你是个暴发户。 一个傲慢的年轻人, 喜欢喝酒和堕落的女人, 为泰瑞克斯做了几件赚钱的工作, 就以为自己是个伟大的海盗。 \n此外, 你本性就是个屠夫。 你以为卡塔赫纳让你在兄弟会中有了更多分量? 呵呵, 哦, 绝不, 只是在像你这样的怪物中而已。 ";
			link.l1 = "哦, 这太可笑了! 哈哈哈哈, 这可是出自一位真正的天使之口! 你这个老混蛋! ";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "我想我们现在已经把事情说清楚了。 是时候结束这场喜剧了。 地狱里的魔鬼已经等你太久了。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "你喜欢这样吗, 嗯? ";
				link.l1 = "退后! ";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "那么, 你觉得怎么样? ";
				link.l1 = "这不好笑, 小妖精。 搞什么鬼? ! 我没下令屠杀! 你不觉得这太过分了吗? ! 泰瑞克斯不会高兴的! ";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "那你为什么一脸内疚? 不喜欢吗? 让我告诉你 --事情只会变得更糟。 你以为今天的屠杀只是因为今天是那样的一天? 哈, 当然。 这是家常便饭。 皮卡德甚至连眼都没眨一下。 对他们来说, 这只是另一个做他们喜欢的事的日子。 ";
			link.l1 = "那你呢? 只是路过? ";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "我不是海盗。 我也不想参与今天的事件。 而且... 如果你对梅里达烧焦的土地上女人的尸体这么 upset, 为什么你要那样对待印第安人, 王子? ";
			link.l1 = "我该怎么做? 放下一切, 爬回马库斯那里道歉? ";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "我只是以为你已经完全接受了, 开始像泰瑞克斯的船长们那样思考和行动。 但不, 哈! 你太软弱了, 不适合这种工作。 你最好把你的份额给马库斯, 夹着尾巴离开。 这不是你的使命。 ";
			link.l1 = "轮不到你来为我做决定, 小妖精。 你当然也没有权利侮辱我。 我不会把我的份额让给任何人。 我会和泰瑞克斯公平分配。 ";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "当然。 但我们最好在你晕倒前离开。 ";
			link.l1 = "这不好笑, 该死的。 ";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "那你还不太了解他。 不过, 既然今天的事没给你带来快乐, 那就听听我的提议。 ";
			link.l1 = "在这之后你还能拿出什么提议? ! ";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "你最好用心听着, 小子。 ";
			link.l1 = "嗯, 我不喜欢你的语气, 卢卡斯, 但好吧, 说吧。 ";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "我有资格这么说 --我比你活得久, 王子。 所以我眼光很准, 不只是射击方面。 想知道我注意到了什么吗? ";
			link.l1 = "有话直说! ";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "你在这里格格不入。 是的, 你很优秀, 也在进步。 但这只是因为你是个强大的船长, 而不是因为这真的是你的使命。 我不知道你是如何转向特拉克斯的, 也不知道为什么, 但相信我, 这不是你该做的事。 ";
			link.l1 = "我有... 一个目标。 我不能告诉你是什么。 ";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "那你离它更近了吗? ";
			link.l1 = "还没有。 ";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "好吧, 如果连今天都没让你更接近它, 那在这里也没什么可获得的了。 你是个好人, 王子。 你把印第安人当人看待。 讽刺的是, 你最后却和我们在一起。 我的建议是: 把你的份额给特拉克斯以避免任何问题, 远离这一切 --趁你还能拯救自己的灵魂。 ";
			link.l1 = "我会考虑的。 ";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мeридe
		case "tagofa":
            dialog.text = "塔戈法向你问好, 海洋之子。 你想让我告诉你去山中西班牙定居点的路吗? ";
			link.l1 = "没错。 我发现你不像你的族人那样, 很擅长我们的语言。 ";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "塔戈法经常和雅拉诺人打交道... 我们大部分路程将沿着河流前行。 你需要长船。 你有吗? ";
			link.l1 = "你有吗? 我们可以借一会儿... ";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "我们的村庄很小, 我们只有很少的长船, 而且所有的长船都只适合捕鱼。 现在, 我们需要好的长船, 能够承受长途航行的船, 就像你们船上的那些。 ";
			link.l1 = "嗯... 那我们需要六条长船。 船上没有那么多。 ";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "那就造吧。 你们白人可以在岸上修理你们的巨型船只, 肯定能造几条长船。 ";
			link.l1 = "嘿, 看来你说得对, 塔戈法。 带我们去河边, 希望离这里不远? ";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "不远。 跟我来。 ";
			link.l1 = "... ";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "这就是我跟你说的那条河。 我们将从这里开始我们的旅程。 你造好船后, 我们就出发。 ";
			link.l1 = "明白了, 塔戈法。 船造好后我会告诉你。 ";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лeпрeкона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймeр, чтобы нe ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "船造好了吗, 白人酋长? ";
			link.l1 = "是的。 我的人正要上船。 ";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "很好。 和我一起上第一艘船。 塔戈法会带路。 ";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "河上的旅程结束了。 从这里到西班牙定居点不远了。 有一条小路, 沿着它走我们就不会迷路。 我们设法绕过了一个充满卡庞猎人的森林, 但这里也是他们的土地。 我们必须小心。 ";
			link.l1 = "别担心。 他们一露出丑陋的彩绘面孔, 我们就把他们消灭掉。 ";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "嘿! 塔戈法! 看! 路中间那是什么... 某种印第安人的东西。 ";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "这是卡庞人的标志。 一个警告。 它告诉你停下来, 不要再往前走。 卡庞人已经发现了我们。 ";
			link.l1 = "如果我们继续往前走会怎样? 他们会攻击我们吗? ";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "是的, 白人酋长。 你对他们来说一定看起来很有威胁性, 因为他们还没有攻击我们。 然而他们还是给你留下了这个标志。 ";
			link.l1 = "去他的标志。 我们继续前进... 所有人听好了! 准备战斗! 做好准备! 保持警惕! 如果这些野蛮人露出他们丑陋的面孔, 我们就把他们全部消灭! ";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "白人酋长和他的手下击溃了卡庞加人, 塔戈法印象深刻。 西班牙城市已经不远了。 前面有一个山谷, 你会在那里看到一个瀑布。 塔戈法不会去西班牙人的地方。 我会在瀑布附近等你。 ";
			link.l1 = "很好。 继续前进! ";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "我们回来了, 白人酋长。 塔戈法履行了他的承诺。 ";
			link.l1 = "感谢你, 塔戈法。 你做得很好。 ";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "塔戈法该走了。 哈亚米非常想念我。 再见了, 海洋之子。 ";
			link.l1 = "祝你好运, 丛林之子。 代我向你的妻子问好。 谢谢你的帮助。 ";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мeриды
		case "merida_guard":
            dialog.text = "嘿! 你是谁, 想干什么? ";
			link.l1 = "我们需要进入梅里达, 和你们的总督或者其他负责人谈谈... ";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "我们不让陌生人进入梅里达。 离开! ";
			link.l1 = "伙计, 我们划了两天的船, 然后又和成群的印第安人战斗, 不会就这么离开的。 我再说一遍, 我要和你们村子的首领谈谈! 我们有... 一个商业提议给他, 是的! 如果我们都同意, 你们的村子就会安然无恙。 ";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "你在威胁我吗, 小偷? ";
			link.l1 = "你怎么看出来的? 啊, 是的, 我确实在威胁你。 要么我们和平地得到我们想要的东西, 要么就用武力, 而你有幸决定你们村子的命运。 ";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "你永远别想进入梅里达, 你这个该死的海盗! 警报! 敌人在城门口! ";
			link.l1 = "真是个不讲理的绅士... ";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мeриды
		case "merida_head":
            dialog.text = "该死的海盗! 你们想从我们这里得到什么? ! 这是一个小而朴素的定居点。 我们既没有黄金也没有白银! 你们是怎么找到我们的? ";
			link.l1 = "哦, 别装无辜和无知了, 阁下。 全世界都在传言你们的蛋白石。 ";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "而你们却为了... 传言发动了这场无情的屠杀? ! 一个不留! 野兽... 让你们知道: 矿脉离这里很远。 你们在这里得不到任何东西。 离开。 ";
			link.l1 = "是你们发动了这场无情的屠杀。 平民和你们的士兵一起战斗。 我永远不会相信这种无谓的英雄主义只是为了保护几堵光秃秃的墙。 ";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "你知道建造这些墙花了多少努力吗? 我们没有雇佣外面的建筑工人 --我们自己一砖一瓦地建造。 每个居民都参与了。 甚至我, 用这双手。 ";
			link.l1 = "真是感人的故事... 那家具呢? 也是你们自己做的吗? 多么精致的雕花椅子。 还有桌子。 还有橱柜。 这是染色橡木吗? 还是乌木? 对于一个'朴素的定居点'来说, 有点太豪华了, 你不觉得吗? ";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "贪婪蒙蔽了你的心智, 海盗。 ";
			link.l1 = "别把事情复杂化, 总督先生。 否则你会后悔的。 ";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "你要折磨我吗, 你这个该死的海盗? 对你来说太糟糕了 --我信仰全能的上帝。 如果你做得太过分, 我会作为烈士升天的。 ";
			link.l1 = "嗯... ";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "我的朋友, 他不会这样说话的。 让我来处理。 ";
			link.l1 = "哦? ";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "我还记得那些趾高气扬的西班牙人在那个该死的种植园对我做的一切。 我很乐意给你展示, 王子。 我还会在这过程中给你讲几个故事。 你不会无聊的。 ";
			link.l1 = "如果你太过分了怎么办? ";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "他不会好好说话的。 我了解他这种人。 ";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(值得信赖) (荣誉) (领导力) 今天的血已经够多了, 让。 我自己来处理这个。 ";
				link.l1.go = "merida_head_dobro_1";
				notification("值得信赖", "Trustworthy");
				notification("信誉检查通过", "None");
				notification("技能检查通过", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("特质检查失败", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(50))+")", "None");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("技能检查失败 (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "动手吧。 我不参与。 也不想看。 ";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "如果我不欠你人情, 我会对你说几句难听的话... 该死。 动手吧。 现在是真正干活的时候了。 ";
			link.l1 = "别太拼命了。 ";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "如你所愿, 我的朋友。 看着会很有趣的。 ";
			link.l1 = "别笑得太早。 ";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "你说你会自己处理这件事, 不流血, 你这个该死的海盗? 你说什么也不能让石头凭空出现! ";
			link.l1 = "最好它们能出现, 总督。 否则, 我们会把这座城市夷为平地, 杀光所有人, 除了你。 我不喜欢这个解决方案, 但我愿意为了我的事业妥协我的荣誉。 而你的职责, 另一方面, 是保护梅里达的平民。 幸存的士兵和工人。 或者你宁愿'作为烈士升天', 以他们的痛苦为代价? 在我看来, 这可不太像上帝的行为。 ";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "该死的你... \n在... 箱子里。 放过镇上的人! ";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(潜行) 箱子里的东西都在吗? ";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("技能检查通过", SKILL_Sneak);
			}
			else
			{
				link.l1 = "我遵守我的诺言。 再见, 总督。 ";
				link.l1.go = "merida_head_dobro_5";
				notification("技能检查失败 (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "该死的你下地狱吧! \n箱子还有个假底。 把所有东西都拿走!! ";
			link.l1 = "... ";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "干得漂亮, 王子。 抱歉低估了你。 ";
			link.l1 = "满意了? ";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "干得漂亮, 王子。 ";
			link.l1 = "满意了? ";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "非常满意。 但是... 你自己会看到的。 你先走; 我再四处看看。 ";
			link.l1 = "... ";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "你答应过一旦拿到宝石就离开这个城镇... 你现在已经拿到了, 而你的海盗们却放火烧了我们的房子! 你是个骗子, 一个邪恶的海盗! 我希望地狱的火焰也能像这样灼热你!!! ";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", 尊敬的先生。 你有什么目的? ";
			link.l1 = "我来自泰瑞克斯。 有人让我护送你的船只前往布里奇敦。 你准备好了吗? ";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "终于等到了! 是的, 我的船员已经准备好立即起航! ";
			link.l1 = "太好了。 准备好船帆, 船长。 让我们起航! ";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всeгда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "感谢你的帮助, 船长! 有你在我身边, 我就像在堡垒的城墙后面一样安全。 ";
			link.l1 = "哈, 别客气, 伙计! 一切都是马库斯的功劳。 祝你好运, 朋友! ";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "向勇敢的船长致敬! 请允许我自我介绍 --英格兰的私掠船船长, 托雷罗号的伊格纳西奥.马尔科。 ";
			link.l1 = TimeGreeting()+", 朋友。 "+GetFullName(pchar)+"船长为你服务。 我能为你做什么? ";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "哦, 我知道你! "+GetFullName(pchar)+"先生! 整个群岛都在流传关于你的资源和赞助人的传闻。 我相信我的提议对你会很有吸引力。 ";
			link.l1 = "什么提议? ";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "我们去酒馆喝一杯吧。 我会告诉你一切。 这不是在街上能谈的事。 ";
			link.l1 = "很好... 我们走吧! ";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "来一轮, 船长? ";
			link.l1 = "当然! ";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "嘿, 他们这里居然不把朗姆酒和水混在一起... ";
			link.l1 = "而且也不用腐烂的鱼招待顾客, 是的-是的。 那么交易是什么? ";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "我喜欢你的直率, 先生。 告诉我, 你知道英国和荷兰之间的贸易战吗? ";
			link.l1 = "我知道。 有幸参与过。 ";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "那就不用解释了。 作为一名英国私掠船船长, 我站在他们一边战斗。 你大多是个自由职业者。 这使你在对抗哪一方时漠不关心... ";
			link.l1 = "差不多。 我不会与法国为敌, 对不起。 ";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "当然, 船长! 那么, 直截了当地说: 在库拉索岛和特立尼达岛之间有一个小有人居住的岛屿, 地图上没有标注... 最近, 我得说非常近, 荷兰人开始把它用作临时补给和修理的停靠点。 他们似乎认为只有他们知道这个岛屿。 错了。 呵呵\n几天前, 一支银矿运输队遭遇了... 风暴, 现在荷兰人正在这个岛屿上修理他们的船只。 旗舰的桅杆断了, 所以修理需要一些时间。 荷兰人正忙着修理, 船员们大多分散在岛上... ";
			link.l1 = "然后我们突然出现拯救世界? ";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "正是如此, 船长。 我一个人做不到, 但有了你-情况就完全不同了。 你愿意冒险吗? 我有一艘很棒的船, 船员也很棒, 我也有丰富的经验。 你的技能... 也值得称赞。 ";
			link.l1 = "我们有多少时间? ";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "如果我们不浪费时间并立即起航, 时间绰绰有余。 ";
			link.l1 = "那么让我们补充弹药和武器, 伊格纳西奥.马尔科船长, 然后起航。 这个岛的确切坐标是多少? ";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "北纬12度40分, 西经64度11分。 记住了吗? ";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "哈! 似曾相识... 记住了。 ";
			else link.l1 = "记住了。 ";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "前往'托雷罗号'。 我会等你的, 船长! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "真是一场激烈的战斗, 对吧, 船长? 现在是愉快的部分了: 让我们分配战利品。 一半归我和我的手下。 ";
			link.l1 = "很好, 让我们开始吧... ";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "船长, 这是怎么回事? 我们的银子呢? 你把我们的战利品弄沉了吗? ";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "嗯... ";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "不知怎么的银子不见了, 不过我们得到了一些红木。 我们把它分了吧。 ";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "嗯... 这太少了。 我原以为会多得多。 ";
				link.l1 = "我们得到了我们所能得到的。 ";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "不错, 不错。 不过, 我原以为会更多。 ";
				link.l1 = "我们得到了我们所能得到的。 ";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "干得好, 先生。 这是一笔丰厚的战利品... ";
			link.l1 = "在这一点上我不能不同意你, 船长。 ";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "看来你的脑子有严重问题。 我们走! 伙计们! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "至少我们从这当中得到了一些东西... 伙计们! 我们走! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "还可以。 我们分道扬镳吧。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "还可以。 我们分道扬镳吧。 毕竟这是一次成功, 呵呵! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "我们的会面非常成功。 也许, 这不是我们最后一次合作, 船长! ";
			link.l1 = "如果你找到更多肥硕的商人, 就叫我, 呵呵! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "我猜这不是巧合, 船长? ";
			link.l1 = "如果你没看出来, 那你就不聪明了。 你欠我一个解释。 你知道我在说什么。 另外, 你还欠我一个人情, 因为你设计了我的朋友让.皮卡德。 他在你的阴谋后被卖到了种植园... 你输了, 伊格纳西奥。 我要绞死你, 但你可以减轻你的惩罚... ";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "我很好奇 --我能做什么让你怜悯我? ";
			link.l1 = "我需要信息。 我会把你关在我的货舱里, 在那里我们会谈谈你在哈瓦那的计划... ";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" 我没想到会这样! 想都别想。 巴尔巴松很快就会知道我的背叛。 你最好不知道他对背叛他的人会做什么。 我见过。 ";
			link.l1 = "那么被绞死是更好的选择? ";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "我宁愿战死! ";
			link.l1 = "... ";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "船长! 船长! 快! 西班牙军舰在追我们! ";
			link.l1 = RandSwear()+"我就料到会这样... 皮卡德也遇到过同样的事情。 你看到外面有多少艘船了吗? ";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "是的, 船长。 三艘船。 他们的旗舰是一艘大型帆船, 是我见过的最大的, 而且它开得很快, 另外两艘是护卫舰和双桅横帆船。 ";
			link.l1 = "所有人上船。 我们可能还有机会逃脱。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индeй-кариб в гротe Порто-Бeлло
		case "grot_canib":
            dialog.text = "哈亚! 该死的雅拉诺人来到我们的森林! 杀了他! 哈亚! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пeщeры Панамы
		case "cave_bandit":
            dialog.text = "嘿! 你在这里干什么? 啊-啊, 偷别人的东西? 好吧, 你完蛋了! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "嘿! 所有人都给我站住! 否则我就用葡萄弹把你们都轰了! "+RandSwear()+"";
			link.l1 = "我们现在哪儿也不去。 但是听着, 伙计-你不可能一炮就把我们都打死。 我们中的一些人会在你装弹的时候把你碎尸万段。 我们最好现在就谈谈。 ";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "你是这里的负责人吗? 回答我! ";
			link.l1 = "我是"+GetFullName(pchar)+"船长。 而你一定是红狼不在时这里的二把手, 对吗? ";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "你在这里干什么, "+GetFullName(pchar)+"船长? 我们不邀请客人来这个地方! ";
			link.l1 = "你叫什么名字? 我想知道我在和谁说话。 ";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "我叫罗德加.扬森。 ";
			link.l1 = "我看得出你们在这里很黑暗。 你们已经没有船长了。 你们的护卫舰也没了.'芙蕾雅号'在伊斯帕尼奥拉岛附近被西班牙人炸得粉碎。 她的船员全部被杀... ";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" 伍尔夫里克... 啊-啊啊啊!!! ... 但我怎么知道你说的是真的? ";
			link.l1 = "我有你们前任船长的日志! 我们从'芙蕾雅号'的残骸中找到了一些物品。 多亏了日志, 我找到了这个岛和你们的... 据点。 ";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "嘿! 你还没回答我: 你为什么在这个不知名的地方? ";
			link.l1 = "我不打算撒谎, 伙计。 他们说红狼有相当多的财富。 我来这里是为了找到它, 因为在他的船上没有找到这样的宝藏。 我相信这些财富应该属于好人, 反正它们对伍尔夫里克已经没用了。 ";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "哈! 伙计, 我要让你失望了: 我和船员中没有人见过沃尔夫的宝藏。 问他太冒险了。 ";
			link.l1 = "那么我应该在你们的村庄里找找看。 你是要放下枪, 还是我要开始攻打村庄? 你没有机会的, 罗德加。 如果需要, 我会带来更多的人和枪。 ";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "在我们死之前, 我们会带很多你们这些混蛋下地狱! 也许还有你! ";
			link.l1 = "你确定吗? 你们没有船长, 没有船, 也没有人会来救你们。 即使我就这么离开, 你们很快也会饿死! ";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "嗯... 有什么建议吗? ";
			link.l1 = "是的, 我有。 从枪旁退一步, 管好你的人。 我发誓我不会伤害你或你的人。 如果你愿意, 你可以加入我的船员, 或者我们可以带你去文明的地方。 ";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "在你的人面前大声清楚地发誓! ";
			link.l1 = "我发誓! 我向你保证: 你和你的人不会受到伤害。 ";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "我希望你能遵守诺言, 船长。 ";
			link.l1 = "我总是遵守诺言。 你们还剩下多少人? ";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "你看到的就是全部。 三个。 其余的都死在了丛林里, 攻击你们的时候。 我告诉他们不要去, 但他们不听... ";
			link.l1 = "我明白了... ";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "食物快没了。 我们开始捕猎鹦鹉.'芙蕾雅号'离开太久了。 我们有过怀疑, 现在证实了。 ";
			link.l1 = "感谢上帝, 我决定去寻宝。 你认为他把宝藏藏在哪里了? ";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "我已经告诉过你了: 没有人见过它们。 伍尔夫里克对他的那份很小心, 从不浪费。 他对我们很公平, 但每个试图找到他藏身处的人都失踪了。 如果你愿意, 可以搜查村子。 ";
			link.l1 = "这就是我的计划。 红狼的房子在哪里? ";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "我们这里唯一的两层建筑。 ";
			link.l1 = "好的。 顺便问一下, 你是做什么工作的? ";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"),"Islamona");
            dialog.text = "我是一名木匠, 这两位是我的助手。 我们以前经常修理和改装'芙蕾雅号'。 我们在你的船员中可能会有用。 ";
			link.l1 = "我明白了。 很好, 你加入了, 我们稍后再谈细节。 从入口处拿那把枪。 还有, 罗德加, 在我寻找宝藏的时候不要离开村子。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "命令, 船长? ";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "是的。 你们船长的宝藏已经找到了。 他确实藏得很好, 但我还是智胜了他! ";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason 莫纳岛 -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "罗德加, 你觉得我们还能用这个基地做什么? ";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "罗德加, 我带来了工具。 它们应该已经送到你那里了。 ";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "欢迎! 这位是罗德里戈.希门尼斯, 来自加的斯的一个小而勤劳的社区领袖。 希门尼斯先生 kindly 同意暂时在我们的土地上定居并帮助我们建设。 ";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "罗德加, 你好吗? 你有什么好建议给我吗? ";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "罗德加, 我需要你帮个忙。 ";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && GetCharacterItem(pchar, "gold_dublon") >= 600)
			{
				link.l1 = "我给你带来了达布隆币, 别马上全浪费在酒上。 ";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "罗德加, 检查一下仓库。 我带来了药品和物资。 ";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "你好, 罗德加, 新定居点的情况怎么样? ";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // 船舶维修
			{
				link.l2 = "罗德加, 我的船需要维修。 你和你的人准备好了吗? ";
				link.l2.go = "repair";
			}
			link.l3 = "罗德加, 我想把我的一艘船留在这里。 ";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "罗德加, 我想把我的一艘船开回来。 ";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "看, 有没有空房子我可以用作仓库? ";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "罗德加, 我想看看仓库。 ";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "罗德加, 我想留一部分团队在岛上。 ";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "罗德加, 我想带我的水手们回到海上。 ";
				link.l7.go = "crew_3";
			}// <—— 莫纳岛
			link.l99 = "暂时没什么... ";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "恭喜船长。 我们接下来做什么? 我们要离开吗? ";
			link.l1 = "你在这里很久了吗? ";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "太久了。 自从伍尔夫里克让我在这里负责已经一年了。 ";
			link.l1 = "我认为这个秘密基地太好了, 不能浪费。 现在这个村庄是我的了。 如果你愿意, 我可以让你和你的人留在这里。 朗姆酒。 物资。 药品 --都是你们的。 ";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "那太好了, 船长。 我已经习惯了这个海滩。 这个岛的生活。 ";
			link.l1 = "太好了。 顺便问一下, 这个岛叫什么名字? ";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "莫纳岛。 ";
			link.l1 = "莫纳岛... 也许有一天我们会在这里建造更多的房屋和建筑... 但稍后。 现在你将在这里担任同样的角色, 但要在新船长的领导下。 ";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "成交。 你只要照顾好自己, 船长, 别忘了给我们提供物资。 ";
			link.l1 = "当然, 罗德加。 祝你好运, 我该起航去拉维加了。 ";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//----------------------------------------------------------—— 莫纳岛 ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", 不包括你的女人";
            dialog.text = "很难说, 船长。 已故的伍尔夫里克从未在这里留下超过二十多人。 现在, 我们只有三个人" + sTemp + "。 我们能做的不多。 ";
			link.l1 = "你的意思是说, 如果这里住更多人, 你可以把这个地方变成一个成熟的定居点? ";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "这个岛很小, 所以你不能在上面建立殖民地, 但建立一个定居点是完全可能的! 你可以捕鱼。 猎鸟和山羊。 采集水果。 我们可以自给自足, 但不会因此致富。 \n但有一件事我不太明白, 船长。 你为什么需要这个? ";
			link.l1 = "这是我的家, 我的土地, 我的人民。 如果我不照顾他们, 我会成为什么样的人? ";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "我想把钱投资到有价值的生意上。 ";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "这个小岛正好位于这个地区的中心。 把它变成一个成熟而秘密的军事基地是明智的。 ";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "我很担心你, 罗德加, 你们这些人现在已经完全野性了。 ";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "你是个奇怪的人。 好吧, 没关系。 至少会有事情做... ";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//防御
		break;
		
		case "IslaMona_2_2":
            dialog.text = "你是个奇怪的人。 好吧, 没关系。 至少会有事情做... ";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//贸易
		break;
		
		case "IslaMona_2_3":
            dialog.text = "你是个奇怪的人。 好吧, 没关系。 至少会有事情做... ";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//武器
		break;
		
		case "IslaMona_2_4":
            dialog.text = "你是个奇怪的人。 好吧, 没关系。 至少会有事情做... ";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//权威
		break;
		
		case "IslaMona_3":
            dialog.text = "首先, 你必须找到非常特殊的人。 那些能被说服搬到这个荒野中, 在完全与外界隔绝的情况下生活和工作多年的人。 这就是你必须寻找的那种特殊人物。 希望不止一个。 毕竟, 你不能命令你的船员住在这里, 至少现在不能。 殖民者不会想离开他们既定的家园和稳定的工作。 我们自己也不需要流浪者和其他不适合的人在这里。 \n此外, 这个岛的秘密问题将始终存在。 如果你告诉别人, 立即就会有猎人想要调查的威胁。 ";
			link.l1 = "我明白, 有什么建议吗? ";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "没有, 船长。 我在这里太久了, 已经完全与文明生活脱节了。 ";
			link.l1 = "太好了, 真有帮助! ";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "我和木头打交道, 不是和人打交道。 我对此非常高兴, 哈哈! 顺便说一下, 除了人, 你还需要带一套高质量的锻造和建筑工具到这里。 它们只在旧欧洲制造, 所以会花你一大笔钱。 问问造船厂的老板, 更大的那些。 ";
			link.l1 = "一切都清楚了。 让我们总结一下: 如果我想把这个基地变成更大的东西, 我需要带更多的定居者和工具回来? ";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "正确! ";
			link.l1 = "我会看看我能做什么。 ";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "是的, 船长! 一流的工具, 我们准备好建立殖民地了! 贵吗? ";
			link.l1 = "花了我一大笔钱, 我希望这是值得的! ";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "几年前, 我会说这非常昂贵。 但现在... 我甚至不知道。 ";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "你不能满足于你已经拥有的, 是吗? 无论如何, 准备好你的开支只会增加。 你解决了定居者的问题吗? ";
			link.l1 = "没有, 罗德加。 我还没弄清楚去哪里找他们。 毕竟, 我没有在这些水域建立定居点的主权权利。 ";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "你不能满足于你已经拥有的, 是吗? 无论如何, 准备好你的开支只会增加。 你解决了定居者的问题吗? ";
			link.l1 = "没有, 罗德加。 我还没弄清楚去哪里找他们。 毕竟, 我没有在这些水域建立定居点的主权权利。 ";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "在这些水域, 船长, 每天都有混乱。 听听人们在说什么, 你可能会看到一个隐藏的机会。 我现在会处理工具。 ";
			link.l1 = "好吧, 我会留意这类信息。 ";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("他们说一些罪犯被流放到一个无人居住的岛屿上! 看来他们是如此凶猛的怪物, 甚至刽子手和神父都不想对付他们! 但为什么他们总是把这样的人带到我们这里来? ! ", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "西班牙人? 你一定是在开玩笑, 船长。 我以为你会从勒弗朗索瓦带来游手好闲的人, 而不是这些... ";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "你来自欧洲吗? 呵呵, 不难看出来。 别担心, 你会习惯的。 ";
			link.l1 = "希门尼斯, 你会在我家待一段时间。 那里有一个地下室, 空间很大。 罗德加, 我带来了工具, 还有定居者。 接下来做什么? ";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "明天见, 船长。 我们一天后再谈, 等这些... 定居者带着他们的宝藏安顿下来。 ";
			link.l1 = "好的, 我们明天继续。 ";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "船长, 和西班牙人谈谈。 他已经完全投入到他的工作中了。 ";
			link.l1 = "知道了, 会的。 ";
			link.l1.go = "IslaMona_19";
			link.l2 = "有什么问题吗? ";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "船长, 我和这里的伙计们已经闲逛了几年。 现在, 西班牙人的忙碌活动让我很烦躁。 ";
			link.l1 = "不要冲突! 我禁止你和你的人甚至看向他们女人的方向! 至少现在... 如果事情变热, 乘小艇去... 钓几天鱼。 ";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "是, 是, 先生! ";
			link.l1 = "完美。 好的, 我去看看他在做什么。 ";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "我已经知道了, 船长。 西班牙人要我们探索这个岛? 像一群白痴一样带着地图在岩石上跳来跳去? ";
			link.l1 = "没错, 罗德加。 ";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "六百达布隆币, 我就做。 ";
			link.l1 = "你疯了吗? 你被当地的蜘蛛或毒蛇咬了吗? 在一个无人居住的岛上, 你要一箱子金子做什么? 埋了它? ";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "来吧, 船长。 总有一天我们会离开这个地方, 没有钱, 在大世界里谁会需要我们? 当然, 我们藏了一小笔钱, 但远远不够。 伍尔夫里克从未就他最后的冒险与我和伙计们结清债务。 \n在海滩上闲逛几个月, 每六个月为你的舰队服务一次是一回事。 但像一个被诅咒的海盗一样, 每天在坚实的地面上努力工作 --这是完全不同的事情! 那是一份工作, 工作有报酬。 你确实支付你的船员, 对吗, 船长? ";
			link.l1 = "听起来合理。 我会给你600达布隆币。 我希望你不指望提前付款, 对吗? ";
			link.l1.go = "IslaMona_23";
			link.l2 = "我有另一个提议。 你在陆地上工作, 而不是在海上刮船底。 现在, 我们急需那种工作。 ";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "船长, 我现在就准备开始, 但我的人看到手里的达布隆币会更努力工作。 我保证我们不会留下岛上任何一块未探索的土地。 ";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "好吧。 这是你的金子。 只是不要马上把它浪费在饮料上。 ";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "好吧, 我会给你带来达布隆币。 ";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("你赠送了600达布隆币");
			PlaySound("interface\important_item.wav");
            dialog.text = "哈哈! 你说得有道理, 船长! 哦, 我差点忘了。 现在这里住了很多人, 他们需要吃的。 你见过那些女士吗? 她们不习惯靠土地生存和觅食。 她们不会有任何帮助。 ";
			link.l1 = "只是别告诉我, 我得找更多的海盗来帮你。 ";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // 未支付达布隆币
			AddQuestRecord("IslaMona", "8");
            dialog.text = "是, 是, 船长! 我们准备在陆地上工作! 哦, 还有一件事, 我差点忘了。 现在这里住了很多人, 他们需要吃的。 你见过那些女士吗? 她们不习惯靠土地生存和觅食。 她们不会有任何帮助。 ";
			link.l1 = "别告诉我, 我还得去找海盗来帮你... ";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "不, 我们为什么要这样做? 我们会训练和准备其中最有能力的人谋生。 但在那个美妙的时刻到来之前, 你得给我们提供食物。 几千套船上的物资就足够了。 还有一公担药品以备将来之需。 把所有这些从船上卸到我们岛上的仓库里。 ";
			link.l1 = "会的。 你需要多少时间进行侦察任务? ";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "我们会在两到三天内完成, 我们已经发现了一些有趣的东西。 ";
			link.l1 = "太好了! ";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "我们一完成, 就直接去找那个大笑的西班牙人。 那个疯子需要从我们的工作中得出结论。 ";
			link.l1 = "我看你们几乎已经是朋友了。 那我三天后去拜访他。 好吧, 为了工作。 祝我们所有人好运! ";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "哇! 谢谢, 船长。 现在我们有时间让女士们为这种在野外的疯狂生活做准备。 ";
			link.l1 = "只是小心别把她们变成海盗! 谢谢你, 罗德加";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "船长! 我得说, 我开始觉得住在这里很不舒服。 ";
			link.l1 = "为什么, 罗德加? 怀念贫穷和毁灭的魅力吗? ";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "可以这么说。 现在文明甚至延伸到了这里。 像我这样的人在其中没有位置。 ";
			link.l1 = "给自己买个花边领和手杖。 你会很适合的。 ";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "不如, 我们去见你的西班牙人, 讨论侦察结果。 我还有一个疯狂的想法... ";
			link.l1 = "我刚和他谈过! 好吧, 我们走, 罗德加。 ";
			link.l1.go = "IslaMona_37";
			link.l2 = "你喜欢和他一起工作吗? ";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "受过高等教育且勤奋的人! 希门尼斯真的是个大师。 在过去, 这样的人可以换来大量黄金。 他们的女孩也很漂亮... ";
			link.l1 = "我不想听这个, 罗德加! 我们去和我们的那位大师谈谈";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "如果他们不能胜任工作, 我们就把他们卖掉。 但把女孩们留下, 哈哈! 我们去见大师.. ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "说真的, 船长? 我只是在开玩笑, 我们走... ";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "我就知道你会支持我, 船长! 我们走... ";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "他没在笑, 船长... ";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "那也是, 船长。 我们稍后再讨论... ";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "这位先生有道理, 船长。 我们谁也不会在丛林里累死。 生意可能很脏, 但不这样做, 你除了把这个地方变成海盗窝, 什么也做不成。 ";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "船长, 当你建造工厂时, 奴隶需要保护。 我的人会处理那个。 他们中的一个甚至像雷神一样用闪电射击。 没有什么比瞄准镜更能激励工作了。 我们已经有一把枪了; 现在我们需要第二把。 任何步枪都行。 ";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "我的人也需要同样数量的黄金和另外十几瓶好酒。 ";
			link.l1 = "每批你能提供多少木材? 你为什么需要黄金? ";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "嗯, 首先, 没有休闲的生活是没有意义的, 很快即使是虔诚的, 呵呵, 天主教徒也会开始爬墙。 其次, 如果岛上有一个酒馆, 你就可以把部分船员留在这里待命。 你看, 说服人们像野蛮人一样在海滩上的小屋里免费生活一整年是相当困难的。 但如果附近有一个有酒馆。 热食。 音乐和娱乐的定居点... 一个水手在岸上休假还需要什么呢? ";
			link.l1 = "妓女? ";
			link.l1.go = "IslaMona_49";
			link.l2 = "饮料? ";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "你说得对, 但让我们一次解决一个问题。 首先, 我们要重建你的房子... ";
			link.l1 = "... ";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "他甚至没有想到, 船长。 ";
			link.l1 = "谢谢你, 罗德加。 我明白现在我将能够在这个小海湾为更多的船只提供服务, 对吗? ";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "问候, 船长! 你是来讨论工作的吗? ";
			link.l1 = "不, 完全不是。 我只是想念你北方人的相貌。 ";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "我们走走好吗? 我会带你去看你的工厂。 ";
			link.l1 = "带路。 ";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "喝- 嗝! 船长, 我们在庆祝! ";
			link.l1 = "罗德加! 罗德里戈! 好吧, 该死! ";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "怎么了, 船-船-船长? 你不喜欢墙壁的颜色吗? ";
			link.l1 = "刚才我才意识到你们两个有相同的名字! 哈哈! 一个西班牙人和一个海盗, 同名, 在一个荒岛上建了一个酒馆, 像印度神会吞噬每个人并在日出前结束世界一样一起喝酒! 哈哈! 我和你们一起! ";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "哈哈! 太对了! 干杯! ";
			link.l1 = "干杯! ";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "想喝一杯吗, 船长? ";
			link.l1 = "你要成为酒馆老板吗, 罗德加? ";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "暂时的! 西班牙人特别欣赏有一个海盗来调酒 --这对他们来说是真正的异国情调和冒险。 但总的来说, 这里很好。 如果你决定在这个定居点留下任何船员作为后备, 只要告诉我 --我会安排的。 ";
			link.l1 = "不过他们住在哪里? ";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "简单 --我们会在海滩上建一些小屋。 这样, 他们就会从酒馆跑到岸边。 只是提醒一下, 这个岛最多只能容纳三百人, 所以未来要记住这一点。 有时我们会请你带朗姆酒和葡萄酒来, 所以如果你, 船长, 能提前在仓库里储备好货物, 那就太好了。 ";
			link.l1 = "我会记住的。 那么, 伙伴。 招待好西班牙人, 休息一下。 只是求你, 别喝到整个村庄都烧了 --我无法忍受那个景象! ";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // 可以留下水手
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // 标志 - 酒馆已建造并交付
			// belamour 清空水手-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // 转换为1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "船长! 我很高兴见到你! 感谢芙蕾雅, 你及时赶到了! ";
			link.l1 = "是的, 我们又陷入了另一个烂摊子。 你好, 罗德里戈! ";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "没有伤亡。 幸存的西班牙人首先到达我们这里, 报告说有可能遇到更多客人, 我们设法将该地区几乎所有的物资和设备都带到了定居点。 当然, 奴隶的情况不太好。 ";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "如果他们把我们拖入公开攻击怎么办? ";
			link.l1 = "然后我们不用枪工作。 就像在游行中, 我们一起走到门口, 然后从后面打他们。 你守住大门, 提供支援。 就这样, 祝我们好运! ";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // 与法国人相遇
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//禁止战斗
		break;
		
		case "IslaMona_70":
            dialog.text = "万岁, 船长! ";
			link.l1 = "同意! 太精彩了, 我自己都想躺下了。 伙计们, 你们在那里装了什么? ";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "双倍负载, 船长。 这样一次爆炸就能阻止他们再战斗了! ";
			link.l1 = "你不担心枪会因为这样的温柔处理而爆炸吗? ";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "我有一个从伍尔夫里克那里留下的特殊护身符。 我们家乡丹麦的一些记忆。 我们都去酒馆好吗, 船长? 今天我们都累了。 ";
			link.l1 = "好的, 那太好了。 我们玩些牌 --我们会用你的神奇护身符来赌博。 ";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "哈哈, 在今天如此神圣的表现之后, 船长, 我甚至可能会考虑那个选择! ";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "船长, 你听到了吗? 我耳朵里还在响。 那是谁悲伤的声音? ";
			link.l1 = "那, 罗德加, 是一个活问题。 把他带到工厂, 用链子拴起来, 等待进一步指示。 ";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "是, 是, 船长! ";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "船长, 你是来解决囚犯问题的吗? 我厌倦了在这里站岗。 ";
			link.l1 = "我们必须杀了他。 风险太大了, 所以我们别无选择。 否则, 我最好不要在法国殖民地露面。 ";
			link.l1.go = "IslaMona_79";
			link.l2 = "我不能放他走, 否则我最好不要在法国殖民地露面。 把他戴上镣铐, 让他在工厂工作。 这比杀了他好。 ";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "知道了! 我们快点做完。 去吧, 船长。 明天见。 ";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "哇。 你真是个邪恶的天才。 我不想成为你的敌人。 那么, 我们得先和他做些解释工作。 去吧, 船长。 明天见。 ";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// 进入工厂内部 - 设置定位器
		break;
		
		case "IslaMona_82":
            dialog.text = "真是一场屠杀! 可惜我们不能用大炮射击, 但他们冲进了你的埋伏 --看着真好! ";
			link.l1 = "是的, 我们在这片土地上洒了很多血。 但显然, 在这个世界上建立家园没有其他方式。 ";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "别想太多, 船长。 命运本身把他们带到了莫纳岛。 让我告诉你, 命运可能是个婊子! ";
			link.l1 = "命运, 还是这个岛? ";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "两者都起了作用。 ";
			link.l1 = "哈哈! 两者都很美! 好吧, 勇敢的维京人。 收集战利品, 移走这些尸体。 有尊严地埋葬他们。 毕竟, 他们是我们的同类... ";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "是的, 船长。 没错! 罗德里戈说得如此优美, 让我热泪盈眶。 很明显为什么神父们想把他的屁股放在火刑柱上! ";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "罗德里戈, 我正好在闺房里撞见了我们的主教... 告诉你, 这是圣地亚哥最好的场所! ";
			link.l1 = "如果你也喜欢主教, 那确实是最好的地方。 ";
			link.l1.go = "IslaMona_89";
		break;
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "是啊, 确实把那个恶棍和异端罗德里戈变成了真正的海盗。 ";
			link.l1 = "顺便问问, 罗德加。 为什么西班牙海盗这么少? ";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "为什么这么少? 啊, 你是说海盗船长? 嗯, 其实有很多, 他们大多在塞维利亚的贸易署 (Casa de Contratación) 旗下活动。 这就像军事情报机构, 但不知为何他们称之为贸易公司... ";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "是啊, 为什么不送个信邀请他们过来呢。 嗯, 他们都有私掠许可证, 还很理想主义。 通常不抢自己人, 除非突袭没成功, 哈哈! 他们只在太子港停靠, 还经常和帕斯特发生冲突。 \n最近有个很突出... 迭戈.德.蒙托亚。 就在我上次和伍尔夫里克一起出征时, 听说了很多他的冒险故事。 你和他有共同点, 船长。 但同时又非常不同... 不管怎样, 我在说什么呢? 再来一轮, 玩几把牌吧。 ";
			link.l1 = "你没钱了。 你不会是想拿达布隆币赌吧? ";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "我们每局赌一比索。 玩到二十点? 希门尼斯, 你加入吗? ";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "玩吗, 船长? ";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "开始吧! ";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "我也不玩了, 罗德加。 不管有没有比索, 人们都会这样输掉船, 甚至岛屿。 你们在这玩得开心, 我再四处看看。 ";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // 玩牌
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // 任务游戏属性
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// 调用游戏界面
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // 赌注
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // 离开牌桌
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "不玩了! 好吧, 我再也不跟你玩了! 我肯定你作弊了, 船长! 让骗子就这么走掉可不行! ";
				link.l1 = "我听着, 罗德加。 ";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "我赢了, 船长。 但我不能让你就这么空手走掉, 哈哈! ";
					link.l1 = "好吧, 你这个无赖。 这对我是个教训... ";
				}
				else
				{
					dialog.text = "我赢了, 船长。 但我不能让你就这么空手走掉, 哈哈! ";
					link.l1 = "好吧, 你这个无赖。 这对我是个教训... ";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "啊, 来吧! 你给了我和我的船员一个远离狭窄船舱。 变质水和被碎片击中... 脑袋的机会, 过上真正生活的机会。 拿着。 这个护身符是伍尔夫里克从遥远的丹麦带来的, 后来给了我, 让我... 嘿嘿, 别太深入他的地下室。 我现在不需要了, 但你 --哦, 你会发现它非常有用。 ";
			link.l1 = "谢谢你, 罗德加。 确实是个有用的东西, 还很漂亮... ";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "留着吧, 罗德加。 没有你, 这个地方就不会存在。 让它成为你家乡的纪念。 ";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("你获得了‘雷神之锤’");
			PlaySound("interface\important_item.wav");
            dialog.text = "很高兴你喜欢, 船长。 再来一轮? ";
			link.l1 = "你们在这放松, 我再四处看看。 ";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "如你所愿! 那我就把它送给幸运女神吧, 哈哈! 再来一轮? ";
			link.l1 = "你们在这放松, 我再四处看看。 ";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "好了, 船长。 你和西班牙人解决了问题, 我们庆祝过了, 头痛也缓解了些。 生活真好! ";
			link.l1 = "你在忙什么, 罗德加? ";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "我会和那个女人相处好的。 ";
			dialog.text = "我会像往常一样打猎, 照看我的... 我们的酒馆, 在工厂监督奴隶。 完美的退休生活。 ";
			link.l1 = "你只比我大五岁, 罗德加。 你呢, 罗德里戈? 怎么样? ";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <—— 莫纳岛
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "当然可以, 船长! 我们只需要木板和帆布。 去你的靠岸点, 命令船员准备材料。 ";
				link.l1 = "我这就去。 快点做。 ";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "当然可以, 船长, 但在我看来, 你的船现在不需要修理。 ";
				link.l1 = "只是问问... ";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "可以, 船长。 但有几个限制: 这个岛上只有两个地方适合这样做。 另外, 除了每艘船留一名军官外, 你不能留下其他人。 我们目前根本没有足够的资源在这里保留船员。 最后, 没有空间容纳一级船。 ";
			link.l1 = "知道了。 我准备在这里留一艘船。 ";
			link.l1.go = "shipstock";
			link.l2 = "很好, 我会准备好的。 ";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "船长, 码头上已经停了三艘你的船。 没有更多空间了。 ";
					link.l1 = "你说得对, 我忘了。 ";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "船长, 码头上已经停了一艘一级船。 没有更多空间了。 ";
						link.l1 = "你说得对, 我忘了。 ";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "船长, 码头上已经停了两艘你的船。 没有更多空间了。 ";
					link.l1 = "你说得对, 我忘了。 ";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "船长, 你只有一艘船。 ";
				link.l1 = "嗯... 我该少喝点了... ";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "你想在这里留哪艘船? ";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "'" + chref.Ship.Name + "'。 ";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "等等, 我改变主意了。 ";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "让我看看... ";
			Link.l1 = "很好。 ";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "等等, 我改变主意了。 ";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "让我看看... ";
			Link.l1 = "很好。 ";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "等等, 我改变主意了。 ";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "让我看看... ";
			Link.l1 = "很好。 ";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "等等, 我改变主意了。 ";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "让我看看... ";
			Link.l1 = "很好。 ";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "等等, 我改变主意了。 ";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "船长, 我之前提到过我们的锚地只能容纳一艘一级船。 它太大了, 没有足够的空间。 ";
					Link.l1 = "你说得对, 我忘了。 ";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "船长, 一级船对我们的海岸来说太大了。 我已经告诉过你了。 ";
					Link.l1 = "你说得对, 我忘了。 ";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "船长, 除了一名军官外, 把她的所有船员都带到你的旗舰上。 ";
				Link.l1 = "啊, 对! 我会的! ";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "那么, 我们要在这里保管一艘名为‘" + chref.Ship.Name + "’的" + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName + "Acc") + ", 对吗? ";
			Link.l1 = "对。 ";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "等等, 我改变主意了。 ";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
			if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				npchar.FstClassInHarbour = 1;
			}
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "很好, 我们会把它送到安全的港口。 ";
			Link.l1 = "太好了! ";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "船长, 你要取哪艘船? ";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "'" + chref.Ship.Name + "'。 ";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "等等, 我改变主意了。 ";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "船长, 你的舰队没有空间再容纳一艘船了。 ";
				link.l1 = "嗯。 看来你是对的。 ";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "你要带走她吗? ";
			link.l1 = "是的。 ";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "等等, 我改变主意了。 ";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "这里? 没有。 但伍尔夫里克在这附近建了一个巨大的谷仓。 坚固的建筑, 用棕榈叶和涂了焦油的帆布覆盖得很好。 有锁, 还有一个房间能装下足够装满十几艘贸易船的货物\n现在是空的, 但如果你想检查一下, 我有钥匙。 我们去吗? ";
			link.l1 = "当然! 顺便问一下: 这个岛上有老鼠吗? 它们会在谷仓里损坏我的货物吗? ";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "伍尔夫里克也考虑到了: 他从大陆带来了两只猫。 不过他忘了带公猫, 所以这些疯狂的毛茸茸的母猫每次发情时都会发出难听的声音。 但它们捕鼠很厉害。 别担心, 船长。 你的货物会安全免受虫害和风蚀。 ";
			link.l1 = "太好了! 我会好好利用它的。 你自己留着钥匙, 带我去看看这个仓库。 ";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "跟我来, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// 米拉贝尔
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "啊... ";
			link.l1 = "好吧... 一个女孩... 你在这里做什么? ";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "哦... ";
			link.l1 = "... ";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "先生! " +pchar.name+ "先生, 求你别杀我! 我求你了! 我什么都不会告诉泰瑞克斯的! 我恨那个野兽! 我求你了, por favor! ";
			link.l1 = "... ";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "嘿, 姑娘! 听到了吗? 你跟我走, 否则这个硬汉会杀了你。 ";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "我跟你走, 先生, 无论你带我去哪里! ";
			link.l1 = "很好。 闭上嘴, 如果你开始大喊大叫或叫泰瑞克斯, 我就杀了你。 你叫什么名字? ";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "米拉贝尔... ";
			link.l1 = "好好表现, 米拉贝尔, 这对你有好处。 靠近我, 不要发出任何声音。 ";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "我发誓不会的, 先生。 ";
			link.l1 = "... ";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "先生? ";
			link.l1 = "你做得很好, 姑娘, 我喜欢这样。 现在我们要去我的船上, 你会被关在一个小舱房里一段时间。 很抱歉, 但我不想让你跑去找泰瑞克斯, 告诉他任何事。 ";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "不可能, 先生! 我永远不会去找泰瑞克斯, 这个混蛋! 我恨他! Lo odio!!! ";
			link.l1 = "哇! 他对你做了什么? ";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "很多... 我恨他, 我恨他! ";
			link.l1 = "我明白了。 一旦我们到达, 你将住在一个相当豪华的房子里, 独自一人。 让我心情好, 就不会有人伤害你。 现在去长艇... 米拉贝尔。 ";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//添加乘客
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // 一个月到达莫纳岛
		break;
		
		case "mirabelle_14":
            dialog.text = "我们到了吗, 先生? ";
			link.l1 = "是的, 甜心。 这是我的村庄和我的房子。 这地方归我所有。 不过我很少来这里 --外面有太多工作要做。 你住在这里的时候一定要把我的房子打扫干净, 否则我会把你交给罗德加和他的木匠们。 你可以在岛上随意走动, 这里很美, 但反正也逃不掉。 ";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "好了, 我们到了。 这是我的家。 这个岛上的一切都属于我。 我不常来 --毕竟我住在船上, 但还是需要有人照看房子。 罗德加慷慨地同意把这个荣誉角色交给你。 你想怎么走都行, 甚至可以去丛林或海滩, 但一定要有同伴, 那里还有野生动物。 总之, 没有船你走不了。 ";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "我没地方可跑, " +pchar.name+ "先生。 我没有人, 也没有人需要我。 除非你把我卖给妓院... ";
			link.l1 = "壁炉那里有个活板门, 通向地下, 不要去那里, 你会掉进洞里摔断骨头, 或者回不来饿死。 那样我救你就白费力气了。 ";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <—— legendary edition
            dialog.text = "我没地方可去, " +pchar.name+ "先生。 我没有家人, 也没用。 我可能会再次沦落到妓院。 ";
			link.l1 = "有个活板门通向洞穴, 离它远点。 下面又黑又危险。 ";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "我会远离的, 先生。 ";
			link.l1 = "楼上还有间卧室。 跟我来。 ";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "好了。 我带你看了整个房子。 不比你以前住的泰瑞克斯的地方差。 希望你喜欢。 ";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "是的, 先生。 你有个很棒的房子。 我保证在你不在的时候好好照看它。 ";
			link.l1 = "很高兴你对我这么配合。 希望你是诚实的。 对我诚实, 否则你会后悔不诚实。 做个好女孩, 别让我难过, 我会对你好的。 查理.普林斯信守诺言! ";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "我相信你, 亲爱的。 我觉得你在这里比被锁在泰瑞克斯关押你的那个黑暗储藏室里更安全。 ";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "谢谢你, " +pchar.name+ "先生。 谢谢你不让你的... 同伴杀我。 你对我真好... ";
			link.l1 = "呵呵, 你也很有趣,... 而且你的脸很漂亮, 即使额头上有烙印。 我希望其他地方也没问题... 好吧, 现在让你的船长看看你能做什么。 海上颠簸后, 我们放松几个小时。 ";
			link.l1.go = "mirabelle_21";
			link.l2 = "很好。 就这样, 我有很多工作要做。 你安顿下来, 见见罗德加和其他人。 我回来后再聊。 ";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <—— legendary edition
            dialog.text = "谢谢你, " +pchar.name+ "先生。 谢谢你不让你的... 同伴杀我。 你真好。 ";
			link.l1 = "呵呵, 你这个有趣的小甜心... 尽管有印记, 脸也很漂亮。 希望其他地方也没问题.. 现在让你的船长看看你能做什么。 ";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "很好。 就这样, 我有很多工作要做。 你安顿下来, 见见罗德加和其他人。 我回来后再聊。 ";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "先生 "+pchar.name+" 你真贴心... 你真是个绅士。 想必是不久前才从欧洲来的吧。 ";
			link.l1 = "别奉承我了, 你这个小骗子, 我可吃这一套。 呵, 你真有一套, 米拉贝尔! 泰瑞克斯眼光不错嘛, 呵呵... ";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "我没有。 你是绅士。 但你出于某种原因假装粗鲁。 嗯... 我非常喜欢。 我会等着再见到你... ";
			link.l1 = "啊, 是的, 一个绅士... 财富绅士, 哈哈! 很好, 甜心, 现在先在这里安顿下来。 ";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "再见, 先生。 ";
			link.l1 = "... ";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <—— legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting() + ", " +pchar.name+ "先生! 很高兴见到你。 你好吗? ";
			link.l1 = RandSwear() + "" + RandPhraseSimple("让我发抖吧, 木头! ", "哦, 为了我飘扬的黑旗, 生死何妨! ") + " 查理.普林斯很好, 甜心。 ";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "甜心, 让船长开心点怎么样? ";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "为你做什么都可以, 先生! ";
			link.l1 = RandPhraseSimple("准备抓钩! ", "登船! ");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <—— legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "嗯... 先生, 你是个魔术师! 希望你也喜欢? 我尽力了。 ";
			link.l1 = "你做得很好, 甜心。 ";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "这不是真的, 不是真的! " +pchar.name+ "先生是善良的! 他只是假装是邪恶的海盗! 你是, " +pchar.name+ "先生? ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting() + ", " +pchar.name+ "先生! 很高兴见到你。 你好吗? 为什么这么悲伤? ";
			link.l1 = "你好, 米拉贝尔。 为什么你认为我悲伤? ";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "嗯, 我能看出来。 你不像平时的你。 想让我让你开心吗? 来吧! 我从丛林里摘了些非常甜的水果, 罗德加和他的伙伴们昨天捕的鱼已经烤好了, 还温热。 ";
			link.l1 = "等等。 我想和你谈谈。 ";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "当然, 先生, 你说什么都行。 我洗耳恭听。 ";
			link.l1 = "告诉我你是怎么落入泰瑞克斯手中的, 为什么你额头上有小偷的印记。 别害怕, 我永远不会伤害你。 我只需要听你的故事。 ";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "啊, 先生! 我的故事简短而乏味。 我出生在波多黎各, 父亲是白人绅士, 母亲是印第安人。 我从未见过父亲。 小时候我是仆人, 长大后犯了愚蠢的错误, 偷了主人的珠宝。 我从未有过自己的, 非常想拥有, 哪怕只戴一天。 当然, 他们发现了一切\n有一场审判, 我被鞭打, 烙上印记, 关进圣胡安的监狱。 我在那里待了太久: 一名军官和一个酋长做了交易, 我被以 handful of 达布隆币卖给了菲利普斯堡的一家妓院\n我在那里待了一年左右。 不幸的一天, 泰瑞克斯和他那个戴眼镜的糟糕朋友来访。 ";
			link.l1 = "帕斯夸莱.拉瓦锡... ";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "是的-是的, 他叫帕斯夸莱.拉瓦锡先生。 我不知道他们在我身上看到了什么, 但在他们来访后不久, 泰瑞克斯就从约翰娜夫人那里买下了我, 把我关在一个满是箱子和货物的锁着的房子里。 那是我一生中最糟糕的时期, 甚至比圣胡安监狱的日子还糟糕。 泰瑞克斯每天都来看我, 除非他出海, 那时我才能自由呼吸, 但每次拉瓦锡先生来, 我... 我... 。 那是最糟糕的。 " +pchar.name+ "先生, por favor, 我可以不谈论这个吗? \n我不知道在那里待了多久。 然后你来了, 把我从那个可怕的房子里带走。 我很幸运, 你这么善良。 ";
			link.l1 = "善良? 米拉贝尔, 但我对你做了同样的事: 把你带到岛上, 锁在房子里。 ";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "不, 先生, 不是这样的。 我被锁在这里了吗? 我每天都在岛上散步。 这是个美丽而宁静的地方。 我需要做很多家务吗? 一点也不, 而且我已经习惯了。 你也不像泰瑞克斯, 不像他的商人朋友。 我总是很高兴见到你, 你这么年轻英俊。 也是个绅士... ";
			link.l1 = "米拉贝尔, 你想让我带你去任何城市吗? 我会给你足够的钱。 去哪里? 选择任何殖民地。 ";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "先生, 你想赶走我吗? 求你不要, te lo ruego! ";
			link.l1 = "嗯... 我以为你想回到正常生活... ";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "啊, " +pchar.name+ "先生, 对我来说有什么正常生活? 作为一个有印记的混血儿, 我怎么结婚? 我会再次被卖给妓院。 求你, 别送我走。 我喜欢这个地方, 我在任何地方都没有像在这里这样感到平静和安全。 罗德加和他的伙伴们是好人, 我们是朋友, 他们每个人都会为我冒生命危险。 我喜欢和他们在一起, 很有趣! 有时我们在海滩上生火, 我跳桑巴舞。 求你, 先生, 我会为你做任何事, 就让我留下吧! ";
			link.l1 = "好吧, 米拉贝尔, 既然你这么喜欢这个地方, 就留下吧。 要知道你在这里不是囚犯, 你随时可以要求我带你离开。 ";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "我亲爱的好先生, 谢谢你! 谢谢你! 谢谢你! 我永远不会向你提这样的要求 --我想成为这个岛的囚犯... 还有你的囚犯,  tee-hee... 你今天真好但很悲伤! 你不像往常那样唱歌和咒骂。 ";
			link.l1 = "我可能会唱歌, 但不再咒骂了, 米拉贝尔。 还有... 如果我曾经对你粗鲁, 我很抱歉。 ";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "你会像英国领主一样严厉和严格吗? .. 啊... 先生, 你想让我今晚跳舞唱歌吗? 只为你。 现在跟我来! 没有比爱更好的治疗悲伤的方法了。 我太想你了。 ";
			link.l1 = "哈! 说得好, 我亲爱的女孩... 我们走吧。 ";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "啊, " +pchar.name+ "先生, 你今天真温柔, 嗯... 你对我满意吗, 我亲爱的船长? ";
			link.l1 = "一切都很愉快, 米拉贝尔。 ";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting() + ", " +pchar.name+ "先生! 见到你真高兴! 你好吗? ";
			link.l1 = "" + LinkRandPhrase("我也很高兴见到你, 我的女孩。 ", "嗨, 米拉贝尔。 你总是那么快乐美丽, 真是赏心悦目。 ", "你好, 美人。 你看起来美极了! ") + "我很好。 希望你也不错。 ";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar, "quest.rodgar")) // 第三阶段
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "米拉贝尔, 我已经开始想念你和你的温柔了。 你会吻你的海狼吗? ";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "啊, 我亲爱的船长, 我也想念你! 来吧, 我已经迫不及待了! ";
			link.l1 = "... ";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason 莫纳岛
		case "mirabelle_44":
			dialog.text = "船长先生! " +pchar.name+ "船长! 我太高兴了! 你会救我们的! ";
			link.l1 = "我也很高兴见到你, 米拉贝尔。 那么, 损失如何? ";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "船长, 船长, 谢谢你! 你是最棒的, 最善良的! 你不仅把我从怪物手中救了出来, 还赋予了我新生活! 为我们所有人! ";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "船长先生! ";
			link.l1 = "你好啊, 美人。 没觉得无聊吧? ";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "啊, 船长! 自从你把我从那个可怕的房子里救出来, 我的生活就有了色彩和快乐。 ";
			link.l1 = "你开心吗? ";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "当然! 我想和你分享这份快乐... 我会在楼上你的房间等你。 ";
			link.l1 = "多好的女人... ";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "船长先生! ";
			link.l1 = "你好啊, 美人。 没觉得无聊吧? ";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "啊, 船长! 自从你把我从那个可怕的房子里救出来, 我的生活就有了色彩和快乐。 ";
			link.l1 = "你开心吗? ";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "非常开心! 除了... ";
			link.l1 = "我明白了, 你想向我请求什么? ";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "是的, 船长! 我想和某个男人分享我的快乐... ";
			link.l1 = "他会介意吗? ";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "不, 不, 船长。 我们在一起会很快乐, 我确定。 只是... 你会允许吗? ";
			link.l1 = "你比任何人都值得这样。 但我不会给你们主持婚礼, 别想了! ";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "哈哈! 我的绅士! 谢谢你, 船长先生。 我不知道外面的世界怎么说你, 但我一直觉得你是最善良。 最光明的人。 ";
			link.l1 = "祝你好运, 米拉贝尔。 ";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// 卡塔赫纳总督
		case "CartahenaMayor":
            dialog.text = "该死的强盗! 不管怎样, 我们的信使已经去贝洛港了。 很快我们的舰队就会到达, 然后... ";
			link.l1 = TimeGreeting() + ", 殿下。 很高兴在如此美丽的宅邸见到您。 希望我们离开后您能保留它。 如果我是您, 我不会指望贝洛港的贵族们很快来帮您。 所以, 我们直奔主题吧? ";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "现在就谈生意? 看看窗外! 看看你的那些恶棍在街道和房子里做什么! ";
			link.l1 = "哦, 殿下, 这和如果您不够合作时他们会做的事相比算不了什么。 我希望您明白这些人是谁... ";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "我知道海盗查理.普林斯这个大坏蛋能做出什么! 我知道他的老板是谁! 总有一天, 我们会烧毁你们在伊斯帕尼奥拉的匪巢! 要多少? ";
			link.l1 = "别浪费口舌了, 我亲爱的总督。 你最好给我25万比索。 ";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "什么? ! 你太放肆了! 这是抢劫! ";
			link.l1 = "当然是抢劫。 不然还能是什么? 召集你的精英。 商人和贸易者, 把金子装进一个大箱子, 否则... 我会让你和你的人民更不好过。 ";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "该死的海盗! 混蛋! 异教徒! 滚蛋! ";
			link.l1 = "因为你肮脏的舌头, 我把赎金涨到30万。 ";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "下地狱吧, 狗娘养的!!! ";
			link.l1 = "35万。 你想继续吗? ";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "城里没有这么多钱! ";
			link.l1 = "你在撒谎。 不可能没有。 我们在这里至少能筹集到一百万, 但恐怕我们没有足够的时间。 所以我会仁慈慷慨一些。 你知道数额。 去拿吧。 ";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "我再告诉你一次, 查理.普林斯: 卡塔赫纳没有这么多钱! ";
			link.l1 = "哦... 你怎么这么无聊。 弯刀! 四处搜查, 把找到的所有人都带来。 好好搜查! 我们现在就待在这里, 阁下... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "嘿, ‘固执’先生! 你还没改变主意筹集卡塔赫纳的赎金吗? ... 怎么了, 为什么突然这么严肃? 你还好吗? 要我给你拿点水吗? ";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "据我所知, 这两位女士是您的妻子和女儿, 对吗? 第三个女孩看起来像仆人, 您似乎不太在乎她, 所以我们不会伤害她, 但这两位美人可能会引起我兄弟‘弯刀’先生的注意。 他好像很喜欢她们, 先生。 那么? 你会处理赎金吗? ";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "我... 我需要时间。 ";
			link.l1 = "啊哈! 现在你说话了! 那么谁才是混蛋? 你不在乎我的人恐吓你的市民, 但你的两个女人就完全不同了, 对吗? 你竟敢和我讨价还价, 混蛋? 我会让你知道惹查理.普林斯的下场! ";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "去筹集该死的赎金。 35万, 一分不少。 你有一天时间。 我们会留在这里喝点酒, 和这些甜美的女士们相处一下... 快点, 朋友, 否则我和我身边的‘弯刀’先生可能会爱上你的美人, 到时候你还得赎她们。 前进! 出发! ";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "拿着你的血钱, 查理.普林斯! ";
			link.l1 = "你筹集了赎金? 太好了! 但你迟到了一小时, 我亲爱的总督。 这额外的一小时让我和‘弯刀’明白, 如果没有这些美人 --她们和我们聊得那么开心 --我们的生活将多么乏味... ";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "你... 你! ";
			link.l1 = "啊, 你因为工作太紧张了, 我的朋友。 我开玩笑的... 弯刀! 我们走, 我们离开! ";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// 卡米拉
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "哦, 原来这就是查理.普林斯, 著名的海盗, 西班牙南海岸的恐怖! ";
			link.l1 = RandSwear() + "呵, 我没想到我在托尔图加这么有名。 你叫什么名字, 甜心? ";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "我叫卡米拉。 ";
			link.l1 = "卡米拉... 我以前在法国认识一个同名的女孩。 那是很久以前的事了! ";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(呕吐)... 该死的... 抱歉, 公主, 但王子今晚有点醉了。 所以... 嗯.. 你为什么来找我? ";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "有各种各样的原因。 或者也许没有原因。 ";
			link.l1 = "天哪, 这太复杂了。 你好像是个谜, 姑娘。 ";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "每个姑娘都应该有秘密。 ";
			link.l1 = "看来你想让我解开这个秘密。 不是吗? 我发誓, 我是解开女孩秘密的大师! 我们去酒馆喝杯酒怎么样? 我会给你最好的款待! ";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "嗯... 我喜欢强壮的男人。 但我不想和楼下的醉鬼一起喝酒。 给我们开个房间, 我们在那里喝聊。 ";
			link.l1 = RandSwear() + "你真辣! 跟我来! ";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "来吧... 倒酒, 别让女士等着! ";
			link.l1 = "当然, 我的甜心! ";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "嗯... 想想看, 我现在和查理.普林斯单独在一起, 喝着极好的葡萄酒... ";
			link.l1 = "你会喜欢和我一起的旅程的, 我保证! 查理.普林斯对屈服于他的女士很温柔和蔼。 你会屈服吗, 公主? ";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "嘻嘻... 当然, 甜心! 你的承诺听起来很诱人, 你知道的... ";
			link.l1 = "那么, 我们别浪费时间了, 美人? ";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "哦! 我爱! 真正的男人! ..";
			link.l1 = "... ";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "嗯... ";
			link.l1 = "你喜欢吗, 我的公主? ";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "当然! 希望你也喜欢我。 ";
			link.l1 = "呵! 现在我头脑都清醒了! ";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "王子, 我有个请求。 你会帮我吗? ";
			link.l1 = "我会为你摘天上的星星, 哈哈! 说吧。 ";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "我需要去拉维加见泰瑞克斯。 我怕他, 但你和他有生意往来。 请带我去见他。 ";
			link.l1 = "看看这个! 为什么这么甜美脆弱的女孩想见法典守护者? ";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "这个甜美脆弱的女孩想赚点钱。 我已故的父亲和兄弟没给我留下多少钱。 泰瑞克斯可以解决这个问题。 ";
			link.l1 = "哦, 真的吗? 怎么解决? 想提供西班牙大帆船的线索? 哈哈! ";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "掠夺商队和城市是强壮男人的生意, 就像你一样, 亲爱的。 我有另一笔生意给马库斯。 他买卖信息, 对吗? 我有东西... 我自己没法用, 但他可以。 我只要从中拿点小利就够开心了。 ";
			link.l1 = "有意思! 详细说说。 ";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "嗯... 我不知道... ";
			link.l1 = "哦, 来吧。 把我当成泰瑞克斯的左右手, 我已经为他做了很多调查, 相信我。 如果你的信息有价值 --我会自己买。 ";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "好吧。 我会告诉你更多, 但在收到钱之前不会透露细节。 成交吗, 亲爱的? ";
			link.l1 = "当然, 美人。 查理.普林斯不会坑合作伙伴... 你知道我的意思, 哈哈哈哈! 说吧, 我洗耳恭听。 ";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... 我父亲是一艘商船的船长。 有一天, 他不知怎么得知在大陆丛林深处有一个古老的西班牙采矿定居点。 二十年前它被地震摧毁了。 矿工们遗弃了它, 秘密通道也被遗忘了。 除了一条。 我父亲找到了它\n他带着我兄弟和一个向导去了那里, 他们发现这个地方充满了多年前开采和冶炼的黄金。 至少有一百万比索。 父亲回到船上想找人来运输黄金, 但他震惊地发现船不见了。 似乎他的大副发动了叛变, 把他和我兄弟留在了荒芜的海岸\n他们造了一艘长艇, 沿着海岸绝望地寻找有人居住的地方, 但是... (呜咽) 一场风暴袭击了他们, 我的 (呜咽) 兄弟死了。 父亲活了下来, 但回到家后没多久就去世了 --兄弟的死一天天慢慢折磨着他。 在他去世前, 他画了一张地图并给了我\n他告诉我, 等我结婚后, 我丈夫应该去那里拿到黄金, 我们就能像国王一样生活。 当然会的, 但我不会让我的男人进入那些被诅咒的丛林。 再也不会了! 我父亲说有一百万比索, 但这不是我能搞定的。 这么大的奖赏, 只有最优秀。 最强壮的男人才能得到 --像马库斯.泰瑞克斯这样的男人。 这就是我要去见他的原因。 ";
			link.l1 = "你想要多少钱买这张地图? ";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "两百达布隆币。 与奖赏相比微不足道。 泰瑞克斯会同意的, 我确定。 他像克拉苏一样富有。 ";
			link.l1 = "呵! 如果这都是骗局怎么办? ";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "我看起来像想自杀吗? 想惹泰瑞克斯? 亲爱的, 宁愿贫穷也不要没命。 那么你会带我去吗? 求你了... ";
			link.l1 = "地图在哪里? 能给我看看吗? ";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "我的牧师妥善保管着。 你给我200达布隆币, 我就给你看。 ";
			link.l1 = "很好! 我买了。 酒馆里的陌生人有时会为垃圾要更多钱。 ";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "是吗? 真的吗, 亲爱的? 我真高兴不用去拉维加了! 说实话, 我害怕马库斯。 我也有点害怕你... 但少一点。 ";
			link.l1 = "这么甜的小女孩不需要怕我。 我该把钱带到哪里? ";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "我们做个交易: 每天上午十点到下午一点在我们的教堂找我。 在这个神圣的地方保护下, 我会觉得安全得多。 我们在那里完成交易。 ";
			link.l1 = "你还怕我? 哈哈! 别害怕, 卡米拉。 我不会骗你。 查理.普林斯不会为了两百达布隆币做那种低级事, 而且我想帮你。 ";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "太好了。 那么再见, 帅哥, 我会等你的... 谢谢你今晚我们一起度过的美好时光! 很高兴我们相遇了! ";
			link.l1 = "回头见, 美人。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "那么? 你带钱来了吗, 亲爱的? ";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "是的。 拿上你的金子, 现在把地图给我。 ";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "我马上就去拿。 ";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "谢谢你, 亲爱的... 给你。 我以父亲的记忆发誓 --这张地图不是假的, 它会直接带你到该去的地方... ";
			link.l1 = "很好, 甜心。 我们像上次一样庆祝一下交易如何? ";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "我想, 王子, 但我正在准备向牧师忏悔, 因此现在必须远离任何诱惑。 下次吧。 ";
			link.l1 = "呃, 你在逗我, 姑娘。 好吧! 没时间浪费了: 我们即将起航。 我发誓如果这张地图真能带我找到黄金, 我会把你的利息加倍。 ";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "你真慷慨, 亲爱的。 一路顺风! ";
			link.l1 = "哟吼吼! ";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "你的混蛋杀了我父亲和兄弟。 你对卡塔赫纳的袭击给那里的每个家庭都带来了悲伤。 我希望你现在害怕, 像我们卡塔赫纳市民一样害怕, 当你的暴徒在街上和房子里寻欢作乐时。 你会下地狱的, 查理.普林斯。 ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// 唐.恩里科 - 民间复仇者
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "这个世界上很少有事情能像看盒子里的老鼠互相撕咬一样让我开心! \n只有最强壮。 最恶心的老鼠才能生存。 然后你只需要挤压它... ";
			link.l1 = "啊! 你是谁? ! ";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "我是唐.恩里科。 英国混蛋叫我狐狸, 荷兰人叫我 Vos, 法国人叫我雷诺。 但我更喜欢我的西班牙昵称 - 佐罗。 我惩罚那些折磨和恐吓平民的邪恶, 他们是人民中最缺乏保护的部分\n今天的审判将审判马库斯.泰瑞克斯的四个海盗: -bold Jeffry。 ‘弯刀’佩利。 ‘小妖精’卢克和查理.普林斯 - 这些匪徒对梅里达和卡塔赫纳的大屠杀负责。 最后一个叫‘英俊让’的混蛋没在这里出现, 他一定是你们这群人中最聪明的。 ";
			link.l1 = "什么? ! ";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "你是个卑鄙小人, 查理.普林斯, 但你不傻。 我想我已经弄清楚了。 这是我设的陷阱, 用假地图。 文件。 言语和金银承诺引诱你们所有人到这些地牢, 让你们被自己的恶习摧毁: 嫉妒。 贪婪。 卑鄙和肆无忌惮。 这真是天谴! ";
			link.l1 = "卡米拉... 我早该知道那个女孩有问题! ";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "一个名叫卡米拉的女孩在卡塔赫纳和她的父亲兄弟过着平静的生活, 她即将结婚时, 你和你的魔鬼袭击了这座城市。 你的海盗杀了所有她亲近的人, 所以她发誓不惜一切代价为他们报仇。 对她来说, 扮演这个角色很艰难。 她甚至不得不和一个杀害她家人的混蛋睡觉。 我不敢想象她在那过程中的感受\n这个可怜的女孩在教堂祈祷了好几天请求宽恕。 她把你给她的血腥达布隆币捐给了受你袭击影响最大的受害者。 她现在在修道院, 可怜的灵魂。 你毁了她的生活, 混蛋! 想想吧! 想想你强奸了多少卡米拉。 伊莎贝拉。 罗西塔, 让多少人成了寡妇! 杀了多少胡安。 卡洛斯。 佩德罗! \n记住梅里达! 记住你如何向镇长承诺不焚烧它, 然后把整个地方夷为平地! ";
			link.l1 = "我从没想过要那样做! 当我离开宅邸时, 火已经到处都是了。 我没下这个命令... ";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "你要为你的海盗行为负责。 死人挂在你的脖子上, 很快就会把你拖入地狱! ";
			link.l1 = "来吧! 嗯? 和我打! 这是你想要的, 对吗? 那就来吧! ";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "不, 查理.普林斯。 别拔刀, 没用的... 我可以轻易杀了你, 但像你这样的混蛋死得太快了。 你将永远留在这个地牢里。 你进来的门外面被石头堵住了, 我身后的门也会被堵住, 此外还有坚固的铁条保护。 就是这样, 除了这两扇门, 没有出路\n这是什么... 我锁了所有的门! ";
				link.l1 = "怎么回事... ";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "不, 查理.普林斯。 别拔刀, 没用的... 我可以轻易杀了你, 但像你这样的混蛋死得太快了。 你将永远留在这个地牢里。 你进来的门外面被石头堵住了, 我身后的门也会被堵住, 此外还有坚固的铁条保护。 就是这样, 除了这两扇门, 没有出路\n下面有水, 所以你有足够的时间思考你的行为。 独自在这里, 在黑暗中, 也许你会在饿死或发疯之前忏悔你所做的一切\n最后一件事 - 下面的宝藏是假的。 金锭只是涂了颜色的铅。 达布隆币是真的, 但只有很少一部分, 足够覆盖箱子里的石头。 对海盗来说是个值得的结局, 嗯? 你们为了假宝藏互相残杀, 王子。 现在永别了。 为你有罪的灵魂祈祷吧, 查理.普林斯, 如果你还记得怎么做的话... ";
		// belamour legendary edition -->
				link.l1 = "我刚杀了马库斯.泰瑞克斯的整个先锋队! 你以为这些生锈的铁条能阻止我? ! 我会用你自己的头砸开它! ";
				link.l1.go = "enrico_5a";
				link.l2 = "也许我活该。 但我不会放弃, 听到了吗? ! 我会找到办法的, 我总是能! ";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <—— legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "你说得对, 门很可靠, 虽然旧了。 谢谢你没放下闸门 - 那会耽误我。 但不会太久。 ";
			link.l1 = "赫拉克勒斯.通扎格, 秃头加斯东! 我早该猜到像你这样的人会站在王子和他那类人一边。 真幸运在这里见到你, 也是。 ";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "幸运, 你说? 嗯, 如果你急着死... 不过我以为你不会, 因为你让他饿死而不是面对他。 ";
			link.l1 = "指责我懦弱? 你真愚蠢。 正如我告诉王子的, 死亡对他来说太便宜了。 他不配和我打。 ";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "而你也不配和我打, 唐。 ";
			link.l1 = "十年前? 当然。 现在? 未必。 而且... ";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "而且什么? 为什么要戏剧性地停顿? 不过, 考虑到你的狂欢节面具... 现在就把我排除在外, 是不是太早了? ";
			link.l1 = "你破门而入, 但仅凭蛮力不足以对付我。 你的反应如何? 视力呢? 只有一只眼睛。 我还有两只。 ";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "嗯, 至少现在是这样。 呵呵。 ";
			link.l1 = "为了贝洛港, 你应得的折磨比王子更甚! ";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "哦, 所以你听说了我做的事? 估计你们那伙人会聊上一阵子。 那你知道我经历了什么。 ";
			link.l1 = "你老了, 通扎格, 这次你的傲慢会是你的末日。 是的, 我不仅听说了 - 卡塔赫纳。 梅里达都是你的杰作。 就像贝洛港一样。 ";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "本来会引以为荣, 但不, 不是我干的。 不过从远处看, 可能很像。 太业余了。 话说回来, 即使在贝洛港, 也有... 意外。 ";
			link.l1 = "意外? ! 那天死了一个人... 考虑到是你引发了那场屠杀, 我仍然责怪你, 即使你没有亲自杀了所有人。 我责怪你所有的‘意外’。 ";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "你说, 一个人... 那天死了很多人。 具体点。 ";
			link.l1 = "真的, 如果你能这么说, 你就没有心! 但我会回答: 你不该杀的那个人。 我父亲, 德.拉.维加先生。 如果他还活着, 我就不会走这条路, 你们都还活着。 ";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "闭嘴, 小子。 我亲爱的妻子... 也死在那里。 ";
			link.l1 = "期待 condolences? 你不会得到的。 这是上帝给你的惩罚。 看来你确实有一颗心 - 又小又黑。 我会用我的剑找到它。 ";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "哦, 关于我心的戏剧性。 如果你认为你见过比我更糟的, 那你就错了。 ";
			link.l1 = "你以为我只是个挥霍金钱的纨绔子弟? 听着: 我没把一个达布隆花在赌博或女人上! 我把一切都投入到与你这样的人作斗争中, 并毕生致力于此! ";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "为了什么? 看起来并不成功。 贸易路线上仍然挤满了海盗。 你独自进行十字军东征。 而他们是一个军团。 ";
			link.l1 = "总得有人做。 至少有人。 也许, 只要杀了一个海盗船长, 我就能救几个人的命。 ";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "愚蠢。 理想主义。 而且... 在某种程度上, 我得说, 如果你不是用这种方法, 你是高尚的。 不光彩, 像你的敌人一样。 最终, 你... 也好不到哪里去。 ";
			link.l1 = "别跟我说教! 荣誉是给遵守法律的人的。 我理解你。 我像你一样思考。 我惩罚。 ";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "你说得对。 教你是没有意义的。 所以, 我们不会和平分手。 但我根本不在乎你, 唐.恩里科。 你甚至不值得我花时间。 ";
			link.l1 = "你什么意... ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // 在地下洞穴射击佐罗后
            dialog.text = "你没事吧, 船长? 我警告过你要小心。 早该听我的直觉。 ";
			link.l1 = "是的, 我没事。 谢谢, 赫拉克勒斯。 只是有点... ";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "... 震惊? 别害怕承认 - 这在你这个年龄和这种情况下很正常。 此外, 那个唐是个很好的操纵者。 ";
			link.l1 = "嗯嗯。 不过, 他好像怕你。 这让我很惊讶。 但也让我回过神来。 顺便问一下, 他还活着吗? 好像是。 你不该背对着他。 ";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "活着, 但惊呆了。 正在恢复知觉。 本应瞄准头部, 而不是躯干 - 原来我们的贵族绅士在外套下穿了一件轻便但坚固的胸甲。 呵呵, 连弗利特伍德都只穿简单的皮甲。 否则这里已经有一滩血了。 ";
			link.l1 = "你怎么会在这里? 和他一样? ";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "现在没时间说这个。 他很快就会站起来。 现在, 我们把这个闸门抬起来。 ";
			link.l1 = "我们... 什么? ! 当然, 你可能是赫拉克勒斯, 但... ";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "我年轻时的人都很坚强。 这些铰链有短销。 来吧, 搭把手, 船长 - 我可能是赫拉克勒斯, 但我上年纪了。 ";
			link.l1 = "好吧, 数到三! 抬! ";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // 包围佐罗
            dialog.text = "你以为你破坏了我所有的计划并赢了吗? 当然, 这出乎意料, 但我仍然考虑到了很多! ";
			link.l1 = "就像你衣服下面的轻胸甲。 为什么穿这个而不是上面的全甲? 只是为了炫耀你的外套? ";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "我不是少女, 王子。 我的理由纯粹是实用 - 全甲太限制我的行动了。 每个人都有自己的方式。 ";
			link.l1 = "然而我, 一个法国人, 已经习惯了穿胸甲, 不像一个西班牙人。 真讽刺。 那么现在呢? 你没能困住我们。 你已经准备好一切... 决斗有没有考虑进去? 或者说, 剑 - 甚至胸甲 - 是为除了真正战斗之外的一切准备的? ";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "你也想叫我懦夫吗? 正如我所说, 你应该长期受苦, 而不是在决斗中死去。 如果你的灵魂没有时间在地球上忍受和理解你所有的罪孽, 那有什么意义? ";
			link.l1 = "常言道, 通往地狱的路是由善意铺成的... 而折磨你的受害者不会玷污你自己的灵魂吗? ";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "永远不会。 永远不会。 因为我忠于自己和我的原则。 ";
			link.l1 = "啊哈, 不像我们。 你说了这么多我们是多么卑鄙无耻, 没有一丝荣誉, 所以... 为什么不达到你的期望呢? 我们自己来处理你。 一起。 ";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "我向你提议, 唐.恩里科。 我挑战你在此地此刻决斗。 作为贵族对贵族。 ";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "嗯。 否则你们毫无胜算。 通扎格当然会很棘手... 所以我会先处理你。 ";
			link.l1 = "好像他会让你这么做一样。 ";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "你? 一个贵族? 也许你是'王子', 但我怀疑你身上有没有一滴贵族血液。 ";
			link.l1 = "你向我透露了你的真名。 我也透露我的。 我是查尔斯.德.莫尔。 我们已经互相侮辱了足够的荣誉, 我们每个人都有权要求满意。 defend yourself, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "但以后不要后悔你的决定。 ";
			link.l1 = "我一生中后悔过很多决定, 但这不会是其中之一。 准备好! ";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // 战胜佐罗后
            dialog.text = "你没事吧, 船长? 我们的贵族绅士不仅穿了胸甲 - 他还在刀刃上涂了毒。 拿着这个。 我在丛林里行走时总是带几个 - 你永远不知道什么时候会被蛇咬或被红皮肤扔毒镖。 ";
			link.l1 = "谢谢, 赫拉克勒斯。 我没事。 你的及时到来帮助我振作起来。 ";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "不客气。 我们走吧, 我带你离开这里 --他提到用石头堵住了入口。 我找到了另一条通道, 一条捷径。 ";
			link.l1 = "告诉我, 赫拉克勒斯... 贝洛港到底发生了什么? 什么时候? ";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "今天我没心情谈这个。 但也许有一天, 边喝葡萄酒或更烈的酒边聊。 现在, 我们先离开这里 --那小子说得对, 我老了。 我想在船上休息。 ";
			link.l1 = "那你带路吧。 ";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "告诉我, 弟弟 --你怎么变成了这样的怪物? 当我告诉你要熟悉海盗时, 我不是指焚烧城市。 杀害无辜平民和折磨妇女。 即使是战争, 也可以打得有荣誉和尊严\n你是我们家族的耻辱。 幸好父亲不在这里: 他要是知道儿子成了海盗和强盗, 会羞愧而死的! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "哥哥! 哥哥! \n你能听到我吗? \n两扇门后面有一条通道。 门可以打开。 钥匙在你附近! \n在楼梯上找。 在楼梯上! ..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "哈哈哈哈, 你好啊, 我勇敢的杀手! 为什么这么悲伤? 大海。 黄金。 朗姆酒和女人 --你还缺什么? 还记得我们第一次见面吗? 我当时就说过 --我需要不惧怕火药味或鲜血成河的男人。 你超出了我的所有期望! 你已经成为了真正的海盗, 查理.普林斯! 哈哈哈哈! ";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "真正的该死的海盗! 啊啊哈哈! ";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "哇哈哈哈哈哈哈!!! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "你是谁? 你在这里做什么? 快回答! ";
			link.l1 = "我来自法代, 来取一批黑骨头。 他应该警告过你。 ";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "哈! 别紧张, 朋友。 我们认出你了, 莫斯科维特详细描述过你。 他还让我们不要对价格感到冒犯。 所以, 考虑到你已经预付了1万银币。 或者, 如果你用黄金支付, 只需50达布隆。 那么, 你决定了吗? 别拖拖拉拉! ";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "我付50达布隆。 这样更划算。 ";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "我付1万比索。 ";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "抱歉, 我现在买不起奴隶。 ";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "太好了。 示意你的人来取货吧。 ";
			link.l1 = "当然。 ";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "太好了。 示意你的人来取货吧。 ";
			link.l1 = "当然。 ";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("五十名奴隶已装船至" + PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //开启遭遇战
		break;
		
		case "SlavesTrader_X":
            dialog.text = "好吧, 随你。 这种商品总会有买家的。 再见, 朋友。 ";
			link.l1 = "再见。 ";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //开启遭遇战
		break;
		// 加斯帕尔.金牙的对话 Xenon
		case "GasparGold_meeting":
            dialog.text = "你好, 船长。 如果我没认错的话, 你是查理.普林斯? 别担心, 我的墙壁没有耳朵。 说实话, 我不在乎你叫什么。 重要的是有人把你推荐给我, 这意味着我们可以做生意。 ";
			link.l1 = "你好, 加斯帕尔‘金牙’。 不过, 我也不在乎你叫什么。 听说你可能有兴趣买些小饰品? ";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		case "GasparGold_meeting_01":
            dialog.text = "没错。 没人会给你比我更好的价格。 嗯, 也许当铺老板除外, 但他们买不了多少。 我准备买下你提供的所有东西。 你甚至不必亲自把贵重物品带来: 我有一扇后门通向一个隐蔽的码头。 随便把你船上箱子里的小饰品都卖给我吧。 ";
			link.l1 = "太好了! 很高兴认识你。 ";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "那是我个人的事。 我希望你不要打探。 我只能说, 一切都在我的掌控之中, 所以你可以放心和我交易。 其余的与你无关。 ";
			link.l1 = "嗯, 安全最重要! 还有件事我想问... ";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "我能为你做什么? 想处理掉多余的珍珠或宝石? 也许是黄金。 白银。 珠宝? 我全买了。 ";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "说起来, 做赃物买家是什么感觉? 你不怕当局吗? ";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "我这里有东西... 想换些现金。 ";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "好, 我们来交换。 要比索还是达布隆? ";
			link.l1 = "要比索吧 --不需要达布隆。 普通货币到处都通用。 ";
			link.l1.go = "GasparGold_peso";
			link.l2 = "你猜对了 --我特别需要达布隆。 所以我只接受达布隆。 ";
			link.l2.go = "GasparGold_dub";
			link.l3 = "我现在没什么可卖的。 只是想确认一下你愿意买贵重物品, 等我有了再来。 再见! ";
			link.l3.go = "exit";
		break;
		
		// 交易窗口
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// 梅里达事件后与印第安部落首领的威胁对话
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "你还是用了恐吓手段, 船长? 我在外面都听到威胁了。 ";
			link.l1 = "他们没给我选择。 我给塔戈法的妻子送了礼物求他帮忙。 她根本不听。 现在让酋长去跟他们谈。 如果他不能让这些顽固的家伙清醒过来, 我就亲手把他的心从胸膛里挖出来。 顺便问一下, 雅哈胡是谁? ";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "你不该破坏和印第安人的关系。 我们海盗只有剑和船作为盟友。 但既然这是你的决定, 那就这样吧。 雅哈胡是个邪恶的恶魔。 其他的我就不知道了。 ";
			link.l1 = "... ";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "花时间说服, 小妖精 --不明智。 或者你想放弃丰厚的战利品, 维持和印第安人的良好关系? ";
			link.l1 = "... ";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "我想两者兼得。 ";
			link.l1 = "脚踏两条船行不通。 这次不行。 争论够了, 事情已经做了。 明天酋长会告诉我们塔戈法的决定, 希望他不会让我失望。 否则... 我将不得不采取极端措施。 当然, 我希望避免那样。 ";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //允许休息
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "那么, 情况如何? 我们有向导了吗? ";
			link.l1 = "没有, 让, 我们没有。 酋长和整个部落都像魔鬼怕香火一样害怕卡蓬人。 看来我们得放弃计划了。 ";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "泰瑞克斯不会喜欢这个转折的。 ";
			link.l1 = "你以为我对事情变成这样很开心吗? 懦弱的洛科诺人不想惹卡蓬人。 无论是劝说还是奖励都打动不了他们。 ";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "那我们就得用威胁。 告诉他们你会把他们该死的村庄烧成平地, 折磨幸存者直到有人同意带我们走。 ";
			link.l1 = "让, 你完全疯了吗? 我不会烧毁无辜百姓的家园。 更不会折磨他们。 ";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "查尔斯.普林斯真是慈善家。 我从未料到你会如此温柔。 ";
			link.l1 = "这不是温柔, ‘英俊’。 嗯, 我们可以把某个印第安人折磨个半死。 出于报复, 他会把我们直接带入卡蓬人的手中, 然后沿着只有他知道的小路消失。 我不会拿我的人冒险。 ";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "既然如此, 小妖精和我就先走了。 这是五万银币, 感谢你把我从马拉开波种植园救出来。 我本来想用它买艘新船。 给你个建议: 暂时避开马库斯的视线。 再见, 查尔斯.普林斯。 ";
			link.l1 = "再见, 让。 ";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// 内梅西达。 火药桶爆炸后与军官的对话
		// 通扎格
		case "Nemezida_Tonzag_1":
            dialog.text = "这一带的人现在都会冲向这里! 你确定炸掉那些树是个好主意吗, 船长? ";
			link.l1 = "该死! 也许大家用斧头砍会更好... 但现在说什么都晚了。 ";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "没错。 我们得处理眼前的情况。 准备好。 ";
			link.l1 = "你也一样, 赫拉克勒斯。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "他们还在往这边来。 那么, 我们也处理掉这些? ";
			link.l1 = "如果没完没了怎么办? 我们来这儿不是为了惹这种麻烦的。 ";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "嗯, 凡事都有尽头... 但你说得对。 我们撤退吧。 快点。 ";
			link.l1 = "我们赶紧走! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "他们穷追不舍, 追上我们了。 这里有条小路, 我们进去吗? 在里面更容易坚守。 ";
			link.l1 = "等等, 赫拉克勒斯。 你听到了吗? 里面已经有人了。 你和弟兄们在这里处理。 我进去, 在他们拿走宝藏之前 --我怀疑不会有人偶然闯进去。 ";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "好的。 但小心点, 我有不好的预感。 ";
			link.l1 = "你也小心! 我去那边了。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // 在岸边
            dialog.text = "你想说什么吗, 船长? 从营地到船上的整个路上你都在沉思。 ";
			link.l1 = "没错。 我在想我最近都在做什么。 关于泰瑞克斯和... 这把我引向了哪里。 我离救我弟弟更近了吗? 或者回家? ..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "嗯... 好问题。 你的答案是什么? ";
			link.l1 = "只是另一个问题。 如果之前是徒劳的, 这次也会是徒劳的吗? 泰瑞克斯不会帮我。 无论是救我弟弟, 还是夺回托尔图加。 ";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "可能不会。 他对那些事没兴趣。 奇怪你现在才意识到。 但你的下一个问题是什么? ";
			link.l1 = "我他妈的为什么要像哈巴狗一样跟着泰瑞克斯, 一直为他火中取栗? ! ";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "这才是个好问题。 一个恰当的问题。 这次你有答案了吗? ";
			link.l1 = "更像是一个决心。 我今天很幸运。 但下次还会幸运吗? 知道何时停止很重要。 还有... 尊重自己。 我受够了。 ";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "决定和泰瑞克斯结束合作关系了? ";
			link.l1 = "是的。 我有更重要的事情要做。 家人, 朋友。 和他们一起, 我才能实现目标。 而不是用这种方式。 即使我真的做到了... 也不会和马库斯一起。 我要做自己的主人。 我要自己做决定。 ";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "我曾经追随的那个人又说话了。 别再和错误的人纠缠。 别浪费曾经让我感兴趣的潜力。 ";
			link.l1 = "知道了, 赫拉克勒斯。 再次感谢。 这次, 谢谢你帮我彻底认清了。 我不再是普林斯, 那个跟班。 我是查尔斯.德.莫尔, 一个骄傲的贵族。 我们上船吧 --我们都累了。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// 克尼佩尔
		case "Nemezida_Knippel_1":
            dialog.text = "那爆炸可真够猛的, 先生 --我的船尾都震了! 听起来就像‘瓦尔基里’号的齐射。 但恐怕那边的家伙也注意到了... ";
			link.l1 = "如果他们注意到了, 那是他们的问题。 没人邀请他们来。 准备好教训他们了吗, 查理? ";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "时刻准备着, 先生! ";
			link.l1 = "太好了。 我们上。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "恐怕我们要有更多‘客人’了, 船长。 你有什么命令? ";
			link.l1 = "我们往丛林深处走, 躲起来 --没办法把他们全击退, 而且我们来这儿也不是为了打架。 ";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "是, 先生。 ";
			link.l1 = "那就行动起来! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "他们追上来了, 船长! 但我们可以在这里躲避 --看来这条小路通向某个地方, 不过我觉得里面已经有人了。 ";
			link.l1 = "我们不躲避! 看来有人也盯上了宝藏。 计划是: 我去看看发生了什么, 在他们把东西全拿走之前, 你带弟兄们在这里挡住他们! ";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "是, 先生。 ";
			link.l1 = "太好了。 我现在下去! 相信你能处理好这里。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // 在岸边
            dialog.text = "咳咳... 你... 没事吧, 先生? ";
			link.l1 = "查理! 你选了个好时候担心我。 省省吧。 你怎么样? 我真该把你留在船上, 多带些人... ";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "啊, 只是点小伤, 先生。 有点累。 这辈子都没这么打过, 就算年轻的时候也没有! 但我把他们打得屁滚尿流, 他们这辈子都忘不了! ";
			link.l1 = "皇家海军, 老派作风! 看来你像头狮子一样战斗, 查理。 但你都快站不住了。 别硬撑 --伤得有多重? ";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "不严重, 船长, 只是累了。 你身后的入口几乎立刻就塌了, 我们拼命抵挡了好久。 最后只剩下我一个人, 受了伤。 所以我就往这边走, 想清路并找点急救。 ";
			link.l1 = "明白了。 你今天尽到了职责。 至于我... 我失败了。 我们都被耍了, 为了某人的消遣互相残杀 --那里甚至没有宝藏。 而且我不是唯一的傻瓜。 ";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "你失败了? .. 但你还活着, 先生。 发生了什么? 你逃出来了? ";
			link.l1 = "不, 但也算是跑了一段。 抱歉, 老朋友, 里面发生的事, 我不会告诉任何人 --即使是我最亲近的朋友。 不过, 我已经得出了必要的结论。 ";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "什么样的结论, 先生? 我不太理解你的逻辑。 我的哲学很简单 --一门好的 culverin 炮和桅杆上的 knippels。 ";
			link.l1 = "告诉我, 你以前一定杀过西班牙人, 就像我最近做的那样。 在你皇家海军的时候。 后来, 和弗利特伍德一起的时候。 ";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "杀过。 西班牙人, 荷兰人 --还有很多其他人。 就像迪克曾经告诉我的, 我们的职业既危险又苛刻。 但你为什么问这个? 你的重点是什么? ";
			link.l1 = "我会解释。 但首先, 另一个问题。 你有没有怀疑过你在做什么, 以及为什么这么做, 查理? ";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "嗯... 我告诉自己是为了王室的利益。 担心命令是吃力不讨好的 --反正你都得服从。 ";
			link.l1 = "王室... 好吧, 你有你的理由。 我甚至连那个都没有 --米歇尔让我接近泰瑞克斯。 但这一切值得吗? 这对我或他有帮助吗? 是的, 是的, 我们不喜欢老爷们... 但我们都是人。 ";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "我想我开始明白你的意思了, 先生。 ";
			link.l1 = "很好。 告诉我, 弗利特伍德离开时, 你是否高兴不再需要向荷兰商人开炮? 他们中有些人是诚实的人。 ";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "我从没想过这个, 船长。 但我要说 --我一直很喜欢和你一起服役, 先生。 如果我说谎, 就让 knippel 绕着我的脖子吊死! ";
			link.l1 = "哈哈哈哈, 好吧。 但告诉我 --你觉得谁更惨? 你, 服从命令? 还是我, 没人强迫我做我所做的? ";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "我不知道, 先生... ";
			link.l1 = "我也不知道。 但这不重要。 重要的是我不再想和泰瑞克斯有任何瓜葛。 够了。 不再有查理.普林斯。 只有查尔斯.德.莫尔。 ";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "但这不是你救弟弟计划的一部分吗? ";
			link.l1 = "曾经是。 但最终, 这对我毫无帮助。 所以如果我以后再做类似的事 --那只能是我的决定。 而且只有当它真的能让我更接近目标时。 ";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "我希望你知道自己在做什么, 船长。 希望你不会落得像泰瑞克斯那样的下场。 或者上绞架。 ";
			link.l1 = "我也希望如此。 但我确定的是, 从现在起, 我的目标和利益将放在第一位。 现在, 我们来处理你的伤口。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// 朗韦
		case "Nemezida_Longway_1":
            dialog.text = "你的爆炸引起了注意, 船长阁下。 一支敌军小队似乎正在接近我们。 ";
			link.l1 = "该死的树根! ... 你觉得有更好的办法处理那些树吗? 你会怎么做? ";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "我不知道。 但我知道现在该做什么 --处理那些人。 ";
			link.l1 = "好吧, 说得对。 我想我们确实要这么做。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "新人又来了, 船长阁下。 ";
			link.l1 = "是的, 我注意到了, 谢谢你, 朗韦。 但我们没时间对付这些人, 所以撤退到丛林里 --也许他们会跟丢我们。 ";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "嗯, 我们当然可以对付他们, 但如你所说。 ";
			link.l1 = "我们不需要这场战斗, 所以行动吧。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "他们不会放过我们, 会追上的, 船长阁下! 我告诉过你, 我们早该解决他们。 我们在那个洞穴里设伏如何? 虽然看起来已经有人在里面了。 ";
			link.l1 = "最好和弟兄们在这里设伏! 我不想错过宝藏。 看来有人也听说了宝藏的事... 所以我要亲自去看看。 ";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "小心, 船长阁下。 记住, 即使是巨龙也曾死在金山上。 ";
			link.l1 = "我会记住的, 朗韦。 希望我们今天都别死。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // 在岸边
            dialog.text = "船长阁下, 看来你从那里逃出来了。 ";
			link.l1 = "惊讶吗, 朗韦? 不过我得承认, 我自己也有点惊讶。 看起来你是唯一活着出来的人。 你怎么做到的? ";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "一群好斗的猫打不过老虎。 一窝蛇杀不死龙。 在白人中, 很少有人配做我的对手。 ";
			link.l1 = "但记住, 朗韦, 一群狗能撕碎狮子。 ";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "现在船长阁下要和朗韦分享他的智慧了? 可惜你之前没听我的建议。 ";
			link.l1 = "关于金山上的巨龙? 没错, 我差点就成了 --差点死了。 但不是死在金山上 --那里根本没有黄金。 我找到的是别的东西, 同样重要。 ";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "下次‘差点’可能就真的死了。 你找到了什么, 船长阁下? ";
			link.l1 = "是的, 我现在明白了。 我找到的是... 智慧。 经验。 理解。 一个决定。 告诉我, 朗韦, 我们最近在做什么? ";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "我们是海盗。 为你的新主人泰瑞克斯工作。 走私, 掠夺城镇, 杀人, 救人, 帮助他的人。 ";
			link.l1 = "他不是我的主人, 你知道。 但该死的, 你描述得太完美了! 我忘了骄傲。 自尊, 像哈巴狗一样跟着他。 ";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "朗韦理解你, 船长阁下。 我也曾为范.默登和罗登堡工作, 为了一个珍贵的目标, 忘记了荣誉。 骄傲和尊重。 ";
			link.l1 = "告诉我, 你为此谴责自己吗? 你恨自己吗? ";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "谴责? 有时会。 恨? 不。 我知道并记得我是谁。 我记得我的目标, 我的指路明灯。 生活中没有什么比这更重要。 你有目标吗? ";
			link.l1 = "不像你有指路明灯, 但也有一个重要的目标 --救我弟弟。 但我偏离了那个目标。 这是我不能再犯的错误。 ";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "让我与你分享另一段来自天朝上国的智慧。 没有完全的好人或坏人。 每个人都拥有阴 --黑暗和无知 --和阳 --光明和智慧。 每个人体内的平衡都会变化。 ";
			link.l1 = "所以, 我的阳是查尔斯.德.莫尔。 我的阴是查理.普林斯。 不过也许连查尔斯.德.莫尔有一天也不得不做出黑暗而艰难的决定。 ";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "这就是生活, 船长阁下。 每个人都注定要做出或黑暗或光明的选择。 ";
			link.l1 = "然而, 普林斯的面具几乎和我融为一体。 但我会摘掉它。 查尔斯.德.莫尔是贵族, 不是跑腿的。 从现在起, 只能是这样。 我要重拾我的骄傲和尊严。 从现在起, 我是自己的主人。 ";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "朗韦赞成你的决定, 船长阁下。 ";
			link.l1 = "谢谢你, 朗韦。 顺便问一下, 你不后悔不当自由船长吗? 像你说的, 为我‘主人’服务? ";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "嗯... 朗韦怀念指挥自己的船。 但朗韦认可你。 因为你对我表现出尊重和智慧, 不像典型的白人野蛮人。 也许朗韦想要不同的生活。 但朗韦不后悔帮助你。 ";
			link.l1 = "很高兴听到这个, 朗韦。 现在... 我们离开这个地方, 离开阴的道路。 让我们为生活带来更多的阳。 我说得对吗? ";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "是的, 正确。 希望你以后能遵循更好的道。 ";
			link.l1 = "道? ";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "道, 船长阁下。 或者本质。 但在我们的情况下 --道路。 ";
			link.l1 = "无论我未来的道路如何, 我不会再偏离真正重要的东西。 我们离开这里吧, 朗韦。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// 蒂钦吉图
		case "Nemezida_Tichingitu_1":
            dialog.text = "查尔斯船长, 很多人往这边来了。 你的烟雾信号把他们吸引过来了。 而且他们显然不是我们的朋友。 ";
			link.l1 = "哦, 要是只是你说的‘烟雾信号’就好了 --整个丛林都听到了爆炸声。 别无选择 --我们自卫吧。 我们绝对不需要被整个小队从背后袭击。 ";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "是的, 查尔斯船长。 先下手为强! ";
			link.l1 = "进攻! 别节省子弹! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "更多人来了! 越来越多。 ";
			link.l1 = "撤退到丛林里, 蒂钦吉图! 我们躲起来 --没办法击退所有人, 而且我们来这儿不是为了打架! ";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "如果需要, 我们可以在丛林里设伏。 ";
			link.l1 = "说得对。 现在, 我们走 --快点, 但要安静。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "查尔斯船长, 看! 前面有个入口! 我能听到里面有脚步声和说话声。 ";
			link.l1 = "听着 --我们被跟踪了。 我去前面看看, 你带弟兄们挡住他们! ";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "我们试试! 你去吧! ";
			link.l1 = "我就靠你了! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // 在岸边
            dialog.text = "查尔斯船长! 你活下来了! 蒂钦吉图为此高兴。 ";
			link.l1 = "谢谢你, 我的朋友。 我也很高兴。 很高兴我活下来了, 你也没事。 看起来整个小队就剩你一个了。 他们人很多吗? 你真的顶住了。 ";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "很多。 但我是我们马斯科吉村庄最好的战士之一。 你在那里发生了什么? 找到你要找的宝藏了吗? ";
			link.l1 = "没有, 蒂钦吉图。 我们被骗了 --没有宝藏。 告诉我, 你怎么看我们最近所做的一切? ";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "我们在做什么, 查尔斯船长? 航行。 打败你的敌人。 ";
			link.l1 = "看来你没明白我的意思。 告诉我, 被部落流放你难过吗? 你想回去吗, 想念你的兄弟吗? ";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "当然, 我想念我的朋友和家人。 但回去? 没有... 她, 我的家就不存在了。 此外, 还有那个邪恶的郊狼, 萨满! ";
			link.l1 = "抱歉, 我不该提那个。 你知道, 我最近也加入了一个部落, 可以这么说。 一个像我这样的船长的部落。 但最终, 我意识到那只是一群自认为是海狼的豺狼... ";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "然后发生了什么? 我们现在做什么? ";
			link.l1 = "好问题。 我差点和那些豺狼一起变成豺狼。 所以, 我受够了。 我的朋友和我的船员 --那才是我的‘部落’。 ";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "蒂钦吉图很高兴你找到了你的部落, 查尔斯船长。 ";
			link.l1 = "谢谢, 我的朋友。 我需要说出来。 你和我都是自己的领袖和部落。 现在是时候回到真正重要的事情上了。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// 艾恩斯
		case "Nemezida_Irons_1":
            dialog.text = "有人来了! 听声音, 不是来和我们一起庆祝感恩节的。 ";
			link.l1 = "该死的树根! 好吧, 我们现在得处理这些混蛋 --最好现在解决, 而不是在我们把宝藏运到船上的时候。 ";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "你说得对。 准备好了吗? ";
			link.l1 = "你不必问。 我们别无选择。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "他们到处都是, 像伦敦贫民窟的老鼠一样, 法官大人! 计划是什么 --我们和弟兄们坚守阵地, 开枪射击? ";
			link.l1 = "现在不行, 撤退! 我们来这儿是为了宝藏, 不是来打架的! ";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "呵, 我没意见。 ";
			link.l1 = "那就加快步伐! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "嘿, 船长, 看 --这条小路通向某个地方。 听声音, 那边很热闹! ";
			link.l1 = "会不会是有人也听说了宝藏的事? 汤米, 你听到了吗? 他们追上我们了。 好吧, 我往前去, 你们在这儿好好‘欢迎’他们! ";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "现在我听到了! 不管他们是谁, 你最好快点, 呵呵。 否则, 我们大老远跑来这儿是为了什么? ! ";
			link.l1 = "哦, 我可不想那样。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // 在岸边
            dialog.text = "啊, 是你, 船长! 哇, 你活下来了。 我说实话 --没料到。 但我很高兴, 别误会, 呵呵。 ";
			link.l1 = "我也没料到, 我也说实话。 但你活下来了 --我一点也不惊讶。 你逃跑了? ";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "你冤枉我了! 汤米.艾恩斯从不逃跑! 只是回去搬救兵。 但没必要 --我和弟兄们自己解决了, 不过, 再一次, 我是唯一活下来的, 呵呵... ";
			link.l1 = "也许这次你该去搬救兵。 但我... 我逃跑了。 ";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "你逃跑了? 呵呵, 又让我惊讶了。 但其实我一解决完就想冲向你! 我比任何救兵都强, 你知道的。 只是... ";
			link.l1 = "怎么了, 汤姆? ";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "该死, 我磨蹭的时候, 你身后的入口被岩石堵住了。 我过不去。 花了好长时间清路, 还没来得及帮你。 我自己找路回去带弟兄们帮忙搬石头时有点迷路... 等我回去, 你已经回来了。 ";
			link.l1 = "是啊, 也许我会羞于承认今天发生在我身上的事。 ";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "发生了什么? 别害怕, 告诉我。 但如果是有趣的事, 我会笑的, 先告诉你。 不然朋友怎么能搭着肩膀, 笑着用胳膊肘碰你呢。 ";
			link.l1 = "嗯, 你确实知道如何安慰人。 告诉我, 汤米。 你说你喜欢当海盗。 很高兴和我一起重操旧业吗? ";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "我这么说吧。 不管我是不是海盗, 我他妈的一直喜欢冒险! 看来我的回答没让你满意。 这种大事, 不是我的菜。 ";
			link.l1 = "不是不满意。 但我想讨论的不是这个。 你知道... 我意识到跟着泰瑞克斯, 我完全偏离了目标。 还有... 查理.普林斯有点像个跟班, 不是勇敢的海盗船长, 你明白吗, 汤姆? 我受够了。 ";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "我明白。 所以我很惊讶你让泰瑞克斯那样控制你。 那不像你。 ";
			link.l1 = "也许那时我真的是查理.普林斯。 但无论我们是否回到海盗生涯, 都由我决定! 而且只有当这真的符合我的利益, 让我更接近目标时! ";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "这才像话! 但我想说, 无论是查理.普林斯还是查尔斯.德.莫尔 --都是你。 所以和你在一起, 总是他妈的很有趣! ";
			link.l1 = "很高兴听到这个, 汤米。 ";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "记住, 除了自己, 几乎没人会帮你。 最好做自己喜欢的事, 即使独自一人, 也不要让别人为你做决定! ";
			link.l1 = "对。 这正是我在泰瑞克斯身上感受到的。 即使我以后再追随某人, 也只会在值得的条件下, 而不是像个该死的跑腿的! ";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "你说得对! 现在, 我们离开这儿 --我的腿都软了。 ";
			link.l1 = "嘿, 我正想说这个, 哈哈。 但你说得对, 我们走。 我们前面有很多重要的工作, 汤姆。 不是这种事。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// 阿隆索
		case "Nemezida_Alonso_1":
            dialog.text = "船长, 看来我们有伴了! 我们不是唯一在这里的人。 ";
			link.l1 = "正是我们需要的... 好吧, 我们现在处理他们。 以后只会更麻烦。 ";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "是, 船长。 ";
			link.l1 = "准备好! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "越来越多了! ";
			link.l1 = "那继续下去就没意义了! 撤退! 我们甩掉他们, 直奔宝藏! ";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "是, 船长! ";
			link.l1 = "行动, 行动! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "船长, 这里好像有个入口! 而且里面已经有人了。 ";
			link.l1 = "仔细听 --我们被跟踪了。 我进去看看, 你们守住这里。 掩护我, 弟兄们! ";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "是, 船长! ";
			link.l1 = "坚守阵地。 祝我们好运! ";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> 试图打开箱子的反应模块
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你果然是个小偷! 卫兵, 抓住他! ", "你果然是个小偷! 卫兵, 抓住她! ", "真不敢相信! 我一转身 --你就翻我的东西! 抓小偷!!! ", "卫兵! 抢劫! 抓小偷!!! ");
			link.l1 = "啊啊啊, 魔鬼!!! ";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- 试图打开箱子的反应模块
		
		// <-- legendary edition
	}
}