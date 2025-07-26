// 鲨鱼: 史蒂文.多德森
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// 杰森 NSO
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "查尔斯, 搞什么鬼! ";
				link.l1 = "史蒂文, 情况重叠了。 我既来不了也没法通知你我缺席... ";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "很高兴见到你, 兄弟! 需要我帮忙吗? ";
				link.l1 = "我也很高兴见到你。 我想感谢你策划的完美行动! ";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "很高兴见到你, 兄弟! 需要我帮忙吗? ";
				link.l1 = "我有个提议给你。 海盗式的提议, 你懂的! ";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "这是我们的客户! 任务完成了, 你要找的男爵已经关在戒备森严的地牢里。 也许你想看看, 嘿嘿? ! ";
				link.l1 = "我以后有的是时间看, 哈哈。 他受到妥善对待了吗? ";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "很高兴见到你, 兄弟! 需要我帮忙吗? ";
				link.l1 = "我又来请你帮忙了。 ";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "很高兴见到你, 兄弟! 需要我帮忙吗? ";
				link.l1 = "史蒂文, 我有东西给你。 ";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "很高兴见到你, 兄弟! 需要我帮忙吗? ";
				link.l1 = "史蒂文, 我得问你点事。 你可能不喜欢, 但我需要你的帮助。 ";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "哈, 你来了, "+pchar.name+"。 我正等你呢。 森林恶魔跟我说了你在托尔图加的麻烦... ";
				link.l1 = "他还说你已经找到解决办法了。 是真的吗? ";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "最近怎么样, "+pchar.name+"? ";
				link.l1 = "到处都是秘密... 我需要你的建议, 史蒂文。 ";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour传奇版本 "幸运号" 的炫耀
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "是的, 我想给你看点东西... 愿意跟我到码头走走吗? ";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour传奇版本与鲨鱼的合作
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "啊, 我的朋友"+GetFullName(pchar)+"! 进来, 很高兴见到你! 你来做什么? ";
				link.l1 = "嗨, 史蒂文! 我如约而来。 你的船准备好了吗? ";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "你的生意怎么样了? 关于‘黄金舰队’的计划没放弃吧? ";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "啊, 我的朋友"+GetFullName(pchar)+"! 进来, 很高兴见到你! 你来做什么? ";
			link.l1 = "是的, 我因事去过伊斯莱索罗岛, 顺便过来看看。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------选项R-----------------------------------------------
		case "Chad_die":
			dialog.text = "哈! 我猜你就是昨晚的不速之客? 我得到消息时已经太晚了。 我检查了你的物品, 发现了一封森林恶魔的信。 该死, 信上都透着大陆丛林的味道\n你叫"+GetFullName(pchar)+"? 别惊讶, 我从信上看到的。 我叫史蒂文.多德森, 或者就叫鲨鱼。 ‘鲨鱼’。 我想你已经听说过我了。 我目前在这个城市或岛上担任首领, 不管这里叫什么\n我为昨晚手下的行为道歉。 我下令抓捕所有潜入货舱的人, 因为独角鲸和里瓦多斯里的小偷太多了\n我猜查德放你走了? 奇怪, 我刚准备下令放你。 你的船呢? 希望它没事? ";
			link.l1 = "查德? 据我所知, 你的水手长绝不会让我活着离开监狱。 我自己逃出来的, 还放了一个里瓦多斯的黑人。 ";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "你说的事很有意思, 兄弟。 你怎么从‘塔尔塔罗斯’逃出来的? 看来我得和查德以及他的狱警好好聊聊了... ";
			link.l1 = "你没机会聊了。 恐怕他们再也说不了话了。 查德威胁要把我永远关在笼子里, 他指责我是里瓦多斯人, 还逼我杀了黑人巫师奇米塞特来证明自己不是... ";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "搞什么鬼? ! 如此愚蠢的独断专行! 我们需要奇米塞特活着, 查德明明知道! 而且黑人都是里瓦多斯人, 他为什么会认为你是? 该死的, 他到底想干什么? ";
			link.l1 = "他想干的事你肯定不喜欢, 史蒂文。 查德给了我一把弯刀, 让我去楼下杀奇米塞特。 但老黑人告诉了我一些重要的事, 我意识到如果杀了奇米塞特, 下一个就是我... ";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "我没杀老人, 而是打开了装弹药的箱子, 和查德及其同伙打了起来。 现在明白为什么你没法和他们聊了吧? 他们都死了。 ";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "该死! 消息越来越可怕了! 我该怎么处理这烂摊子? ";
			link.l1 = "听我说, 史蒂夫。 奇米塞特告诉我查德和一些独角鲸做了交易 --据我了解这是另一个部落。 查德计划杀了你夺取你的位置。 独角鲸巴不得你死, 因为他们认定是你杀了他们的首领艾伦... 还是阿伦, 我记不清了。 ";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "胡说! 我没杀艾伦! 是别人干的, 也许就是独角鲸自己! 我觉得现任首领唐纳德.格林斯彭才是凶手! ";
			link.l1 = "不, 是查德杀的。 奇米塞特目睹了凶案 --所以他们也想杀他。 不知为何查德不想亲自下手, 好像怕什么诅咒。 所以他想让我动手。 ";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "难以置信... 查德杀了艾伦? 但为什么? ";
			link.l1 = "让你背黑锅, 让你和独角鲸成为敌人。 我猜是他散布的谣言, 不然独角鲸为什么只怪你? 史蒂文, 他们计划杀你, 而里瓦多斯部落会被嫁祸 --虽然我不知道他们具体怎么做。 奇米塞特告诉我的。 ";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "另外, 我在查德的箱子里发现了这封信。 看看吧, 虽然间接, 但像是有力的证据。 ";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "... (阅读中)... 哼! 查德背叛我并不意外。 狗娘养的一直想在岛上掌权。 但独角鲸! 真以为是我杀了艾伦! 他们以后买补给得付双倍价钱\n我本来就打算放了奇米塞特, 是时候和他们和解了。 说实话, 你让我很震惊, 兄弟... ";
			link.l1 = "我理解, 史蒂文。 我也不喜欢这种情况, 自从到了岛上就卷入了政治泥潭。 我来这只是为了找你和纳撒尼尔.霍克... ";
			link.l1.go = "Chad_die_9";
		break;
		
		// 剧情交叉节点
		case "Chad_die_9":
			dialog.text = "什么? 霍克? 他不是在牙买加吗? 他是马龙镇的男爵, 怎么会来这? ";
			link.l1 = "不, 现在是杰克曼在那掌权。 我发现霍克和我一样, 是通过库库尔坎的传送门来的。 ";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "这都什么鬼? 什么传送门? 还有你还没回答 --你的船呢? ";
			link.l1 = "我没有船。 我知道很难相信, 史蒂夫, 但我真的是通过大陆的印第安神像来的... 别这么看我 --我没疯! 我自己都不知道怎么回事, 但这是真的! ";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "";
			link.l1 = "米斯基托村的萨满看到纳撒尼尔.霍克被追兵追赶时, 跑向了那尊被称为库库尔坎的印第安神像, 然后突然消失了。 这位萨满告诉我他自己也来过这个岛, 就是通过神像来的... ";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "";
			link.l1 = "我在找内森, 所以不得不追随他的脚步。 我按萨满说的半夜来到神像前。 你都不敢信, 那天晚上石像顶部是金色的, 上面还闪着神秘的光! ";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "";
			link.l1 = "我一摸神像, 神像周围就出现了一个光圈, 燃起火焰, 然后我被吸了进去。 后来我在你船的货舱里醒来, 就在船头破损处附近... ";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "";
			link.l1 = "多亏萨满给的特殊药水才活下来。 最后还被某种怪物 --大螃蟹袭击了。 现在你信我了吧? ";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "你说的螃蟹部分? 我信。 岛周围有很多这种怪物。 我们用死鱼当诱饵, 它们常守在我们后门, 把小偷吓得屁滚尿流。 至于你说的神像 --我还没疯\n但我也不否定你的故事, 几十年来当地人都在传这种事, 而且我很久以前在里瓦多斯的船上也见过奇怪的事... 算了。 ";
			link.l1 = "我发誓全是真的。 ";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "好吧。 就这样。 告诉我, 你为什么找我和内森? 根据扬的信, 你想让我当海盗兄弟会的首领? ";
			link.l1 = "正是。 你和霍克失踪后情况变了很多。 杰克曼想在海盗中扮演核心角色。 如果我和扬不阻止他, 他就要成功了。 ";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "杰克曼在玩一场危险的血腥游戏。 我肯定是他策划了伏击和追捕纳撒尼尔, 还觉得是他杀了Blaze。 让你当海盗兄弟会的首领是阻止他的唯一办法。 ";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "听着, 我很乐意, 但我们得先离开这个岛。 我受够了。 更何况我可以让德克斯特留在这里, 我不在时他能打理生意。 我本来也没打算长留, 但我的船在和部落的战斗中被烧了\n我不会去穿什么传送门, 别想说服我, 我需要船。 ";
			link.l1 = "我不劝... 史蒂文, 米斯基托萨满说岛上有一尊库库尔坎的神像, 看起来像普通石像。 你知道在哪吗? ";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "不知道。 我从没见过那样的雕像。 问问别人吧。 ";
			link.l1 = "你看, 如果我找到这尊雕像, 不用船也能离开岛。 我不怕再试一次传送。 然后我会正常回来接你。 ";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// 剧情交叉节点
		
		case "Chad_die_20":
			dialog.text = "我明白, 但我帮不了你。 另外, 这次暗杀事件很麻烦。 查德死了, 但我怀疑独角鲸不会放弃计划。 我不想每天提心吊胆怕被偷袭。 既然你需要我活着, 而且已经卷入了这摊浑水, 我建议你调查这个阴谋\n你是新来的, 这是优势。 找到查德的同伙, 带过来或直接杀了, 我不在乎。 去和奇米塞特谈谈, 老黑人知道的比说出来的多\n小心独角鲸, 没密码别进他们的地盘。 密码每周换一次\n威胁解除后, 我会给你航行指南和所有需要的信息\n去找出幕后黑手, 恢复秩序。 我会让人清理你留下的监狱 mess。 我们需要新狱卒, 而我需要点朗姆酒, 感觉不太好。 ";
			link.l1 = "好的, 史蒂文。 我们这么办... ";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; // 里瓦多斯船只通行标志
			pchar.rvd_friend = true; // 里瓦多斯不会在需要密码的地方阻拦
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; // 给奇米塞特的节点
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; // 与埃迪谈话的中断
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("想想看: 有人杀了首领的狱警查德.卡珀。 不可能! 肯定是里瓦多斯巫师干的... ", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("听说查德.卡珀死了。 没有官方声明, 也没找到尸体。 也许首领只是派他执行秘密任务了? ", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("没看到我们的狱警查德.卡珀。 有人说他被杀了, 有人不信。 反正没人见过他的尸体。 ", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("听说首领把独角鲸的补给价格提高了一倍! 那海盗真是鲁莽! ", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
		case "Mary_Die":
			dialog.text = "那么, 你有什么消息, "+pchar.name+"? 关于独角鲸的? ";
			link.l1 = "是的。 你会高兴知道, 史蒂夫, 阴谋被揭穿了, 策划者都死了。 我有所有证据。 ";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "听到枪声我就猜到了... 详细说说, 我听着。 ";
			else dialog.text = "是吗? 听到这消息真高兴! 详细说说, 我听着。 ";
			link.l1 = "全是你水手长查德.卡珀策划的。 他在‘塔尔塔罗斯’监狱杀了艾伦.米尔罗, 还散布谣言说是你干的。 我想独角鲸真的很生气, 这对艾伦的女朋友红玛丽是个沉重打击... ";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "玛丽急着复仇, 查德.卡珀就利用了她。 他们策划了一个杀你的狡猾计划。 这里的人都知道你有每晚在‘圣奥古斯丁’船尾散步的习惯。 ";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "哼! 我得改改习惯了... 继续说。 ";
			link.l1 = "他们需要一把远程精准的滑膛枪来执行计划, 所以阿道夫.巴比尔提供了。 但他的施图岑步枪典当了, 所以玛丽和查德给了他足够的钱赎回。 阿道夫把枪赎出来了... ";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "他们雇了前皇家猎人独眼龙马塞洛来杀你。 他得拿到步枪打死你。 之后玛丽会杀了他, 用他的尸体和步枪作为里瓦多斯袭击的证据。 你知道, 独眼龙马塞洛是混血儿... ";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "这混蛋真狡猾! ";
			link.l1 = "之后, 独角鲸和海盗会攻击里瓦多斯并消灭他们。 查德会成为首领, 玛丽会成为他的情人。 不过也许他会杀了她, 因为她知道得太多了。 很可能... ";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "不管怎样, 都结束了。 阿道夫嘴很紧, 我只好在他的船舱杀了他。 我还得对付来拿枪的玛丽和独眼龙。 他们立刻认出了我, 直接攻击我。 ";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "所以他们都死在‘圣弗洛伦蒂娜’里了? ";
			link.l1 = "是的。 三个人都死了。 ";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "幸好这摊浑水没留下目击者。 我会处理尸体。 你干得不错, "+pchar.name+"! 要是你在我船上, 我肯定让你当大副。 ";
			link.l1 = "谢谢你的高度评价! 最后, 看看这些信。 我从独眼龙和可怜的玛丽尸体上找到的... ";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip ("你听说了吗? 我们那位好争吵又鲁莽的‘红玛丽’失踪了。 如果她死了, 我也不会感到惊讶... ", "弃船之城", 10, 1, "LSC", "");
			AddSimpleRumourCityTip ("他们说红玛丽失踪了。 你听说过这件事吗? ", "弃船之城", 10, 1, "LSC", "");
			AddSimpleRumourCityTip ("玛丽.卡斯帕消失了。 有人说她还在自己的船舱里, 但我不信。 距离上次里面有灯光已经太久了。 ", "弃船之城", 10, 1, "LSC", "");
			AddSimpleRumourCityTip ("他们说红玛丽被谋杀了。 可怜的女孩! 是的, 她性格坚强, 但每个人都爱她。 谁会做出如此可怕的事情呢? ", "弃船之城", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "不管怎样, 都结束了。 阿道夫嘴很紧, 我只好在他的船舱杀了他。 我还得对付来拿枪的玛丽和独眼龙。 他们立刻认出了我, 直接攻击我。 ";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "可惜你在‘艾娃’上挑起了战斗。 现在独角鲸知道是你杀了他们的人, 这不利于改善你的名声, 也不利于我的。 在解决冲突前别去见他们\n总的来说, 你干得不错, "+pchar.name+"! 要是你在我船上, 我肯定让你当大副。 ";
			link.l1 = "谢谢你的高度评价! 最后, 看看这些信。 我从独眼龙和可怜的玛丽尸体上找到的... ";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("你在这里杀了这么多人! 独角鲸不会忘记的! ", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("我理解你杀了独眼龙和两个独角鲸强盗... 但为什么杀那个女孩? 可怜的玛丽... ", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "可怜的玛丽? 你同情那个婊子? ";
			link.l1 = "我真的同情。 你看, 查德欺骗了她, 利用了她。 她无法抗拒自己的感情和天生的急躁... 结果就落得如此下场。 ";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("你获得了500杜布隆");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour传奇版本
			dialog.text = "好吧, 去找朱利安兄弟点支蜡烛... 不过我自己不会去。 好了, 不说了。 我很感激你的帮助, "+pchar.name+"。 你现在可以指望我的支持。 我想为你出色的工作付钱。 拿着, 这是五百杜布隆。 ";
			link.l1 = "太好了, 谢谢! ";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("听说首领很看重你, 先生... ", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("听说你是首领的忠实朋友。 是真的吗? ", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------选项N---------------------------------------------------
		case "entrance":
			dialog.text = "你想要什么? 我不认识你... ";
			link.l1 = "当然不认识 - 我们从没见过, 我刚到这里。 你好, 史蒂文。 真幸运! 我一直在找你, 没想到会在这里找到! ";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "等等, 兄弟, 冷静点。 找我? 我不喜欢这样。 你到底为什么找我? ";
			link.l1 = "我明白。 那再试试。 给, 拿着这封信。 是扬.斯文森写给你的。 我想你读后所有怀疑都会打消。 ";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(阅读中)... 嗯。 这下清楚了。 我还以为你会为Blaze的死来找我麻烦。 你知道, 最近很多人都想这么做。 你把船停在外围了? 你怎么知道我在这里? ";
			link.l1 = "没有。 只是运气好。 至于Blaze... 扬和我认为你不是凶手。 ";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "你说得对。 我不是。 确实有人想陷害我, 但我没杀他。 ";
			link.l1 = "那就好。 有趣的是, 我来这找纳撒尼尔.霍克, 却找到了你, 哈哈! ";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "我理解但帮不了你。 你得和岛上的老人谈谈。 去找里瓦多斯巫师奇米塞特。 老黑人知道的比说出来的多。 ";
			link.l1 = "我在哪能找到这位巫师? ";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "在我的‘塔尔塔罗斯’监狱里。 我本来就打算放了他, 是时候改善和里瓦多斯的关系了。 对! 去监狱告诉查德.卡珀, 他是狱警, 说我下令放了奇米塞特\n告诉黑人我为什么派你去, 告诉他如果他够配合我就放了他。 我肯定这会让他开口。 ";
			link.l1 = "嗯... 我是新来的。 监狱在哪? ";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "记住路线: 离开我的住所, 过桥左转, 穿过护卫舰‘卡罗琳’到帆船‘荣耀号’, 然后到‘埃斯梅拉达’。 找一个商店的标志, 从下面的门进去。 穿过船首的门就到塔尔塔罗斯了\n在‘埃斯梅拉达’要小心, 那是独角鲸部落的地盘, 虽然其他人也能去。 别惹他们的战士, 避免麻烦。 ";
			link.l1 = "这些里瓦多斯和独角鲸是谁? ";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "这些部落在这里生活了很久, 是最早定居者的后代。 独角鲸主要是英格兰。 荷兰和法国人, 里瓦多斯全是黑人。 每个部落都有首领, 占据几艘船, 不让外人进入他们的领地\n要进入必须知道密码, 每周换一次。 ";
			link.l1 = "好的。 我会处理。 他们会让我进监狱吗? ";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "会的。 这是钥匙, 查德会知道是我派你去的。 拿着。 ";
			link.l1 = "好的。 那我去和那个... 奇米塞特谈谈, 然后带结果回来。 ";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; // 给奇米塞特的节点
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // 关进封闭牢房
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; // 给卡珀的节点
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);// 禁止战斗
			// 塔尔塔罗斯定位器中断
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "那么, 你去过‘塔尔塔罗斯’了? ";
			link.l1 = "是的。 我把你的命令告诉了查德, 还和黑人谈了谈。 ";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "巫师告诉你什么有趣的事了吗? ";
			link.l1 = "哦, 是的。 他告诉我在哪能找到库库尔坎的传送门神像。 在‘圣赫罗尼莫’船上, 那艘船沉在独角鲸领地附近的浅滩里。 ";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "哈哈哈, 太好了! 所以你的‘传送门’现在在海底了? 好吧, 兄弟, 恐怕你要被困在岛上了。 加入我和我的人吧... ";
			link.l1 = "我会想办法到神像那里的。 我现在就想办法。 奇米塞特说你不该相信卡珀, 因为他亲眼看到查德杀了独角鲸首领艾伦.米尔罗。 ";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "什么? ! 查德杀了艾伦? 那巫师疯了! 不可能! ";
			link.l1 = "你知道, 史蒂夫, 奇米塞特很害怕。 我觉得他没骗我。 ";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "该死, 这消息真糟糕! 艾伦的死已经破坏了我在独角鲸中的名声 - 他们有些人认定是我干的, 现在却发现可能是我的一个军官干的! ";
			link.l1 = "看来人们总爱把不是你的罪过推给你... ";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "是啊, 真麻烦... ";
			link.l1 = "现在告诉你‘最棒’的消息 - 老人说他偷听到几次对话, 发现你的一些手下计划杀你。 他说只有你放了他才会私下告诉你更多。 ";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "太好了! 这都怪你! 别介意, 开玩笑的。 我头都大了: 查德杀了艾伦, 我的人计划杀我... 老黑人告诉你细节了吗? ";
			link.l1 = "没有。 据我理解, 他太怕查德了。 ";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "好吧。 我会告诉里瓦多斯我要见奇米塞特。 看他能告诉我什么。 至于暗杀... 好吧, 我会小心。 那么, 你现在打算做什么, "+pchar.name+"? ";
			link.l1 = "暂时没什么特别的。 我会在岛上走走, 了解一下当地人 - 也许会想出离开的办法。 我得先找到纳撒尼尔.霍克, 他是我来这的原因。 ";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "我明白。 找到离开的办法后别忘了来找我 - 我会给你航行指南, 没有它你回不来。 我还会告诉你一些重要细节。 ";
			link.l1 = "好的。 我肯定会来找你, 史蒂夫! ";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// 呼叫鲨鱼的中断
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = "很高兴你来了, "+pchar.name+"。 我一直在等你。 有坏消息。 奇米塞特死了, 查德.卡珀无影无踪。 ";
			link.l1 = "该死... 我肯定是查德杀了奇米塞特! 老黑人害怕不是没有原因的。 ";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "我对此毫不怀疑。 妈的, 情况每小时都在恶化。 我刚和黑埃迪建立了稳固直接的联系, 现在就这样。 好吧, 我们可以忘了和里瓦多斯的友谊了\n他们知道你在奇米塞特死前和他谈过, 而且认为你是我的人, 所以别和他们接触。 ";
			link.l1 = "是啊, 真遗憾... ";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "我叫你来不只是为了告诉消息。 我收到了我们的调解人兼外交官朱塞佩.法奇奥的信, 他邀请我半夜去‘卡罗琳’在他的船舱见面。 他还说我必须单独去, 因为关系到我的生命, 不能相信任何人\n这有道理, 奇米塞特警告过我身边有叛徒。 但这太可疑了... 单独, 半夜... 通常胖子会自己来找我。 不管怎样, 我想请你帮忙\n严格来说, 你不是我的人, 又是新来的。 扬说你机智勇敢, 剑术也好。 我想让你半夜护送我去赴约... ";
			link.l1 = "你不用问, 史蒂文。 我加入。 我也不喜欢这个邀请 - 闻起来像陷阱。 ";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "也许我错了, 没有陷阱, 但我最好做好准备。 很高兴你同意了。 半夜到‘圣奥古斯丁’甲板来, 我们去看法奇奥, 他的破船离这不远。 ";
			link.l1 = "成交。 我会半夜到‘圣奥古斯丁’甲板, 全副武装。 ";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // 定时器
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "很高兴见到你, "+pchar.name+"。 别浪费时间了, 看看那个胖子法奇奥想说什么。 跟我来! ";
			link.l1 = "走吧, 史蒂夫。 武器准备好... ";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "那个死胖子在哪? 他去哪了? 我们是客人, 他却不接待。 你看到他了吗, "+pchar.name+"? 也许我们该检查一下他的箱子, 他可能在里面... ";
			link.l1 = "他反正进不了世界上任何箱子。 嘘! 史蒂文! 外面有动静... ";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "该死! 你说得对。 看来我们有麻烦了, "+pchar.name+"。 ";
			link.l1 = "... ";
			link.l1.go = "caroline_4";
		break;
		
		case "caroline_4":
			DialogExit();
			LAi_SetPlayerType(pchar);
			// 启动玛丽。 查德和独角鲸 - 将会有激烈战斗
			sld = characterFromId("Capper");
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
			sld = characterFromId("Mary");
			sld.greeting = "mary_4";
			int iScl = MOD_SKILL_ENEMY_RATE*10 + 2*sti(pchar.rank);
			LAi_SetHP(sld, 250+iScl, 250+iScl); // 强化
			sld.dialog.currentnode = "caroline";
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "caroline_5":
			dialog.text = "啊! 我们做到了... 说实话, 我以为我们死定了。 ";
			link.l1 = "我遇到过比这更糟的麻烦。 但我承认, 那些混蛋很强。 奇米塞特警告得对 - 查德是叛徒。 指挥他们的那个女孩是谁? ";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "她叫玛丽.卡斯帕, 也叫红玛丽, 是已故艾伦.米尔罗的女朋友。 我明白查德为什么来这, 他想夺我的位置, 但她来干什么? ";
			link.l1 = "很清楚。 你说她是他的情人, 她的意图很明显 - 复仇。 可怜的女孩不知道自己在和杀男友的凶手一伙。 ";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "有道理。 现在他们要付出代价! 我不会再卖给他们补给 - 让他们饿死。 如果独角鲸敢围攻‘圣奥古斯丁’, 我们就把他们当狗一样打死\n他们会后悔用这种卑鄙手段对付我。 我要把法奇奥的肥屁股钉在我椅子后面的墙上! ";
			link.l1 = "等等, 史蒂夫。 似乎没那么简单。 给我一天时间调查这摊浑水。 我肯定查德是唯一的责任人。 他杀了米尔罗, 散布谣言说是你干的, 利用了艾伦的女朋友... ";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "好吧。 去调查。 也许我们还没找到所有策划者。 我去喝点朗姆酒。 还有, "+pchar.name+": 我欠你人情。 你可以在任何事上指望我。 如果你在我船上, 会当上水手长。 ";
			link.l1 = "谢谢你的高度评价! 等你当上海盗兄弟会首领我们再合作。 去休息吧, 我检查一下这个船舱, 也许能找到有用的东西。 ";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "好。 我会让手下早上前过来清理 - 我们不想用尸体吓着人。 好吧, 今晚螃蟹有大餐了! 再见! ";
			link.l1 = "再见... ";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "那么, "+pchar.name+", 你调查有成果吗? ";
			link.l1 = "可以这么说。 独角鲸没参与暗杀你, 除了玛丽和在‘卡罗琳’袭击我们的那些人。 我认为是她煽动他们攻击我们的。 法奇奥是被迫给你发邀请的。 我在他的船舱找到一封信, 解释了很多。 看看吧。 ";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(阅读中)... 嗯。 这很像法奇奥的风格。 当然, 他能拿查德怎么办... 只是为了保命。 看来都是我那个水手长搞的鬼... ";
			link.l1 = "你现在自己也看到了。 动机很清楚, 我们也知道查德为什么杀米尔罗和奇米塞特。 卡珀想当岛上的首领。 我见过独角鲸首领唐纳德.格林斯彭, 他发誓他和手下都没策划杀你。 ";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "你信他吗? ";
			link.l1 = "信。 唐纳德会为艾伦被杀的指控澄清你的名声, 他准备亲自来向你正式道歉。 你也记得, 你本来就没被冤枉吧? ";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "好吧, 宣战有点过分了。 我们没能力发动流血冲突。 而且看来只是几个败类干的, 不是整个部落\n你说唐纳德准备道歉? 好, 我们借此和独角鲸建立良好关系, 反正和里瓦多斯已经没希望了。 ";
			link.l1 = "说得对, 史蒂文。 现在正是时候。 ";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "好。 告诉唐纳德我愿意见他, 和解。 ";
			link.l1 = "我这就去。 ";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "等等, "+pchar.name+"。 你干得很好, 我想用金币奖励你。 拿着, 这是五百杜布隆。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("你获得了500杜布隆");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; // 标志 - 暗杀被阻止
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // 给唐纳德.格林斯彭的节点
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // 一天后让法奇奥回到原位
			AddSimpleRumourCityTip("听说首领很看重你, 先生... ", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("听说你是首领的忠实朋友。 是真的吗? ", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------选项M----------------------------------------------------
		case "mary":
			dialog.text = "在我的‘塔尔塔罗斯’监狱里。 你可以去那见他。 我给你钥匙, 查德.卡珀不会阻拦... ";
			link.l1 = "等等, 史蒂文。 我觉得我不该先去找查德.卡珀... ";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "为什么不该? 怎么, 你不喜欢他? ";
			link.l1 = "其实, 是他不喜欢你。 我有个坏消息, 查德.卡珀计划杀你。 ";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "什么? ! 解释清楚。 谁说的? ";
			link.l1 = "让我把整个故事告诉你, 这样更好。 ";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "好吧, 说吧... ";
			link.l1 = "我发现自己在淹没的货舱后, 从洞里出去, 在沉船间游泳找安全的地方。 最后爬上一艘旧长笛船, 进了船里。 看到一个穿红外套的女孩和两个大块头在打架... ";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // 玛丽活着
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "呵, 看来红玛丽终于惹到不该惹的人了。 ";
			link.l1 = "我帮了她, 我们解决了那些混蛋。 之后聊得很有趣... 告诉我, 史蒂夫, 这些独角鲸和里瓦多斯是谁? 她经常说这些词, 我都不好意思问具体什么意思。 ";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "是在这里生活很久的当地居民团体。 他们是岛上最早定居者的后代。 独角鲸主要是英格兰。 荷兰和法国人, 里瓦多斯全是黑人。 这些部落有自己的首领, 占据几艘船, 不让外人进入他们的领地。 如果想去部落的船, 必须知道密码, 每周换一次。 ";
			link.l1 = "现在明白了。 我猜玛丽是独角鲸的? ";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "是的, 那个有个性的女孩属于他们部落。 那她告诉你什么了? ";
			link.l1 = "查德.卡珀杀了她的情人艾伦.米尔罗, 他被你俘虏了。 之后查德散布谣言说是你干的。 查德欺骗了玛丽, 想利用她的复仇欲。 ";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "该死! 他杀了艾伦? 但为什么? 让我背锅? ";
			link.l1 = "让独角鲸与你为敌, 赢得他们的信任。 卡珀的最终目标是除掉你, 夺取你的位置。 玛丽拒绝参与他的计划, 也不想成为他的情人 - 所以他命令独角鲸杀了她。 ";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "她这么说的? ";
			link.l1 = "是的。 而且不像是说谎。 另外, 她给了我一封查德.卡珀的信。 我已经读过了, 你也该看看。 ";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "嗯。 是的, 这是查德的笔迹。 我很熟悉他的农民笔迹 (阅读中) 啊! 难以置信! 混蛋! 叛徒! 好, 我要用他的肠子吊死他! 莱顿! 召集五个人! 转念一想, 莱顿, 等等, 解散!\n我们得智取。 我一直想改善和里瓦多斯的关系, 这是个机会。 他们的巫师奇米塞特关在塔尔塔罗斯监狱。 我们让里瓦多斯自己去救他们的人, 顺便让他们杀了叛徒\n莱顿! 去塔尔塔罗斯, 把上层甲板的守卫都撤回来! "+pchar.name+", 你也参与, 我要给你分配一个非常重要的角色。 找到里瓦多斯首领黑埃迪, 和他谈判... ";
			link.l1 = "我? 嗯。 但我在这里谁都不认识! ";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "那你很快就会认识一些人了 - 实际上你会认识整个里瓦多斯部落的第一号人物。 你是执行我计划中外交部分的最合适人选。 我的海盗不容易通过里瓦多斯领地, 而且我也没有口才好的人。 ";
			link.l1 = "好吧, 我干。 我该怎么做? ";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("你获得了50杜布隆");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "拿这把钥匙, 能打开塔尔塔罗斯所有的门。 再拿这五十杜布隆。 你先去‘卡罗琳’, 花五十杜布隆买个进入里瓦多斯领地的密码。 和法奇奥谈, 他是我们的调解人。 然后去‘守护者’\n那是黑埃迪的住所。 告诉他查德.卡珀站在独角鲸一边, 不听我的命令, 还打算杀奇米塞特。 把钥匙给他, 让他带足够的战士攻击‘塔尔塔罗斯’\n我们一石二鸟: 里瓦多斯会把我们当盟友, 卡珀会死在黑人手里。 我不同情那家伙。 明白了? ";
			if (pchar.questTemp.LSC.Mary == "alive")// 玛丽活着
			{
				link.l1 = "我明白 - 但去哪找‘守护者’和‘卡罗琳’? ";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "听着, 史蒂夫, 告诉我那些里瓦多斯和独角鲸到底是谁。 你一直说他们, 但我还是不知道他们是谁。 ";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "独角鲸和里瓦多斯是当地部落。 这些部落在这里生活了很久, 是最早定居者的后代。 独角鲸主要是英格兰。 荷兰和法国人, 里瓦多斯全是黑人。 每个部落都有首领, 占据几艘船, 不让外人进入他们的领地\n要进入必须知道密码, 每周换一次。 ";
			link.l1 = "现在明白了。 告诉我 - 去哪找‘守护者’和‘卡罗琳’? ";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "简单。 离开我的住所, 过桥左转, 就是‘卡罗琳’。 找‘守护者’麻烦点: 过桥后右转, 通过木板到‘圣弗洛伦蒂娜’\n在那找到里瓦多斯士兵, 他们会要密码。 大声清楚地说出来。 然后进入‘狂怒号’, 从船尾进入‘守护者’。 ";
			link.l1 = "嗯, 现在知道了。 我想我不会找不到。 ";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "很好, 那就去吧, 朋友! ";
			link.l1 = "再见! ";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // 给埃迪的节点
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; // 改变标志
		break;
		
		case "dodson_warwait":
			dialog.text = "你还在这? 现在就去里瓦多斯那! ";
			link.l1 = "我这就去! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "呵, 看来红玛丽终于惹到不该惹的人了。 ";
			link.l1 = "是的。 她惹到查德.卡珀了。 我加入了战斗, 但不幸的是, 没能救下那女孩, 一个袭击者用军刀砍了她。 ";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "我为她难过, 当然, 但肯定是她自找的。 玛丽总是惹麻烦。 那查德.卡珀呢? 他其实是我的水手长。 ";
			link.l1 = "你的水手长? 呵呵... 给, 看看这封信。 我在女孩尸体上找到的。 你会知道是谁下令杀她, 为什么。 卡珀计划杀你。 ";
			link.l1.go = "mary_9";
		break;
		
		// 卡珀逃跑
		case "Chad_escape":
			dialog.text = "你怎么去了这么久? 我听说里瓦多斯救了他们的巫师... ";
			link.l1 = "我在‘守护者’当人质, 确保他们免遭伏击。 他们确实救了奇米塞特, 但查德跑了。 ";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = " shit! 古人说别和黑人打交道... 他们连这么简单的任务都做不好! 去他妈的里瓦多斯! ";
			link.l1 = "查德躲到独角鲸那去了... ";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "当然! 他不傻, 知道没有我的帮助里瓦多斯进不了塔尔塔罗斯。 现在他会躲起来暗中攻击。 莱顿! 加强岗哨! 时刻保持警惕! 谁解决卡珀, 我出高价! ";
			link.l1 = "好的, 史蒂文。 我得想想。 也许我能追踪到查德。 再见。 ";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // 去找玛丽
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // 没救下玛丽 - 自己去追查, 该去哪
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // 指向商店的标志 - 寻找威士忌
			}
			NextDiag.CurrentNode = "Total_wait";
			// 增加点氛围 - 让阿克塞尔到早上都不在
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // 阿克塞尔返回商店的定时器
		break;
		
		case "whiskey":
			dialog.text = "怎么了, "+pchar.name+"? 你看起来像被路西法追着跑。 ";
			link.l1 = "他们给你送威士忌桶了吗? ";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "什么桶? ";
			link.l1 = "他们给你送威士忌桶了吗? ! ";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "你吼什么, 兄弟? 没有。 怎么了? ";
			link.l1 = "谢天谢地我及时赶到... 查德.卡珀从阿克塞尔.约斯特那买了一桶布什米尔威士忌... ";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "布什米尔? 这是我最喜欢的! 我好久没喝了! ";
			link.l1 = "是是。 卡珀也知道。 他还让朋友独眼龙马塞洛从桑乔.卡彭特罗那买了些砒霜。 明白为什么吗? ";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "你认为他要毒我? ";
			link.l1 = "毫无疑问! 所以我才这么急。 如果他们给你送威士忌桶 - 别喝。 有毒。 ";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "呵, 谢谢你的警告! 我会小心的。 等等, 你现在去哪? ";
			link.l1 = "我得找卡珀和独眼龙。 我知道去哪找他们。 再见! ";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // 鲨鱼已被警告
			LAi_CharacterDisableDialog(npchar);// 禁止对话
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "哈! 很高兴见到你, 兄弟! 看来我欠你一条命。 ";
			link.l1 = "他们送威士忌了吗? ";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "送了! 正如你说的布什米尔。 我们亲爱的法奇奥真是好心... 我已经逮捕了他调查... ";
			link.l1 = "他招了吗? ";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "是的。 他说卡珀强迫他那么做。 他很害怕, 并且... 把那桶酒作为独角鲸们的礼物带给了我。 ";
			link.l1 = "卡珀死了。 我已经解决了他和他的独角鲸朋友。 现在只剩一个混蛋了 --独眼龙马塞洛... 我相信这头肥猪知道他的下落。 让我去逼问他一下! ";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "当然。 只是尽量别杀了他, 我们可怜的法西奥身体相当虚弱。 ";
			link.l1 = "我会温柔的... 非常温柔, 该死的! ";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//禁止对话
			chrDisableReloadToLocation = true;//关闭地点
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // 对话已发生
			dialog.text = "啊... " +pchar.name+ ", 朋友, 我感觉很不对劲... ";
			link.l1 = "史蒂文! 你喝威士忌了吗? 该死, 你真的喝了? ! ";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "是的... 这是最好的爱尔兰威士忌... 朱塞佩.法西奥今天带给我的。 他说这是独角鲸首领送的礼物... 一种和平的象征... 哦, 好痛... 看来我要死了。 ";
			link.l1 = "该死! 威士忌里被下了砒霜! 是查德.卡珀和独眼龙马塞洛干的! ";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "啊... 水手长最终还是搞到我了... 操! ";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "你不会死的! 听到了吗? 你不会死! 快, 拿着这个烧瓶。 这是世界上最强大的治疗药水, 能治愈一切。 喝下去... 现在! ";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "史蒂文! ";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // 鲨鱼死亡
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // 一天后德克斯特成为 admiral
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // 传奇属性: 鲨鱼已死
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("使用了科曼奇药水");
			Log_Info("毒药已被治愈! ");
			PlaySound("interface\notebook.wav");
			dialog.text = "哦... " +pchar.name+ ", 真的有用。 还是有点恶心, 但疼痛几乎消失了... ";
			link.l1 = "这种药水甚至能中和最致命的毒药。 把它全喝了! 对... ";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "奇迹... 我现在没事了。 谢谢你, 朋友, 我永远不会忘记... ";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "你现在最好休息一下。 你看起来像个死人。 那个混蛋卡珀再也不能威胁我们了 --我已经解决了他和几个独角鲸。 只剩独眼龙马塞洛了。 你说法西奥带给你威士忌, 对吗? ";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "你现在最好休息一下。 你看起来像个死人。 你说法西奥带给你威士忌, 对吗? ";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "是的。 我真的应该注意到他苍白的脸和颤抖的手... ";
			link.l1 = "看来他是被迫那么做的。 很好, 我要去拜访那头肥猪, 从他那里获取信息。 我肯定他知道我需要什么。 好好休息! ";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//禁止对话
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "是的。 我真的应该注意到他苍白的脸和颤抖的手... ";
			link.l1 = "看来他是被迫那么做的。 很好, 我最终会搞定那头肥猪, 但现在我得先处理卡珀和独眼龙。 我知道他们藏在哪里。 好好休息! ";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//禁止对话
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = ""+ PChar.name+ ", 你说什么? 我已经知道你在‘伊娃’号上解决了卡珀。 而且你甚至没清理那里, 哈哈! 说实话, 我很佩服! 杀死查德和他的人, 那可不是小事! 是的, 简称赞你是对的。 ";
			link.l1 = "我不仅解决了卡珀, 还阻止了一次对你的暗杀。 史蒂文, 你差点被毒死, 但我阻止了那些混蛋。 ";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "毒死我? 但怎么做到的? ";
			link.l1 = "查德从阿克塞尔那里买了一桶爱尔兰布什米尔威士忌... ";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "布什米尔? 这是我最喜欢的! 我好久没喝了! ";
			link.l1 = "是的是的。 卡珀也知道这一点。 他还让他的朋友, 独眼龙马塞洛, 从桑乔.卡彭特罗那里买了些砒霜。 然后他和他的伙伴们抓住法西奥, 下到‘伊娃’号的货舱。 他打算在威士忌里下毒, 强迫法西奥把它作为独角鲸的礼物带给你。 ";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "哈! 当然, 我会立刻喝一品脱威士忌... ";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "查德就指望这个。 但他失败了 --他甚至没时间放砒霜进去。 是的, 我把那桶酒拿走了。 你可以把它当作礼物。 ";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "查德就指望这个。 但他失败了 --他甚至没时间放砒霜进去。 ";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "给我看看... " +pchar.name+ ", 这是真正的布什米尔! 最好的爱尔兰威士忌! 啊, 我梦寐以求了好几年! 你, 你... 该死的! 你解决了查德, 还找到了这么好的威士忌! \n我会给你一个我最好的护身符。 这是雷神之锤, 永恒不朽。 你的炮手会喜欢的! ";
			link.l1 = "谢谢! 我也很高兴。 ";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("你获得了‘雷神之锤’护身符");
			dialog.text = "我期待着喝一品脱这种极好的威士忌... " +pchar.name+ ", 我们今晚开个派对! 你明天来看我。 同时, 我会考虑你的话和查德的行为... ";
			link.l1 = "好的, 史蒂文, 我不会打扰你... 放松的, 哈哈! ";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // 舰队司令召唤
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "你告诉了我一些非常重要的事情。 我会考虑你的话和查德的行为... 然后我会叫你。 ";
			link.l1 = "好的, 史蒂文。 我会等着! ";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "哈, 你来了, " +pchar.name+ "。 现在大家都到了, 我们可以开始了。 我召集了你和莱顿来讨论情况, 并决定如何处理独角鲸。 ";
			link.l1 = "你说‘如何处理独角鲸’是什么意思? ";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "查德组织了一次对我生命的暗杀, 他得到了独角鲸的直接支持。 我认为这是一种公开的侵略行为。 考虑到我们与里瓦多斯有短期联盟, 我提议如下\n我们与里瓦多斯结盟, 准备一次行动, 彻底消灭独角鲸 clan。 我受够了他们的强盗态度。 你, " +pchar.name+ ", 将再次扮演外交官的角色\n与黑埃迪和奇米塞特谈谈, 说服他们加入我们, 对抗我们的共同敌人。 我想他们会听你的, 他们相信你是他们的盟友\n德克斯特会制定进攻计划, 他了解岛上的所有地理情况。 莱顿, 你已经有什么想法了吗? ";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // 转移节点到德克斯特
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "好主意。 被迫撤退到圣盖博, 独角鲸可能不会很快向我们的军队屈服 --但他们会在没有补给的情况下迅速死亡, 或者被迫发动绝望的攻击。 你说呢, " +pchar.name+ "? ";
			link.l1 = "我说... 我说对独角鲸宣战在政治上是错误的一步。 ";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "你在杀了查德所有的人之后还这么说? 别忘了他们都是独角鲸! ";
			link.l1 = "不是所有的人。 那些混蛋中的第一个, 独眼龙马塞洛, 不是独角鲸。 实际上, 他忠于里瓦多斯, 也许他正计划加入他们。 毕竟他是混血儿。 我认为独角鲸对企图谋杀你不负责任 --只有几个被卡珀招募的混蛋。 ";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "那你建议怎么办? 忽略这一切? ";
			link.l1 = "我建议继续扮演我的外交官角色 --但这次我要和独角鲸的首领唐纳德谈判。 此外, 让我告诉你我对攻击独角鲸可能结果的看法。 ";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "继续。 ";
			link.l1 = "在我看来, 岛上的和平之所以可能, 只是因为两个实力几乎相等的 clan 之间的竞争。 你的战士是第三股力量, 他们可以帮助任何一方取得胜利。 但里瓦多斯和独角鲸都很强大, 无论如何, 胜利对胜者来说代价都太大。 ";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "摧毁独角鲸的代价将是你和里瓦多斯很多人的生命。 此外, 莱顿说围攻圣盖博需要很长时间, 如果我们损失太多人, 还可能面临来自里瓦多斯的侵略... ";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "别忘了两个 clan 都渴望在岛上称霸, 不久前他们还是你的敌人。 所以, 在我看来, 这场屠杀对普通居民来说将是一场真正的灾难。 ";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "嗯。 你的话听起来很明智, 但你还没有说服我。 ";
			link.l1 = "我也需要以某种方式离开这个岛, 所以我必须到达海底的库库尔坎雕像。 里瓦多斯无法帮助我 --也许独角鲸可以? 与他们战斗对我也没有帮助。 ";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "哈! 我猜你不想让独角鲸成为我们的敌人还有另一个原因。 塞瑞斯铁匠铺的那个红发女孩, 对吗, 朋友? 我说对了吗? 别担心她, " +pchar.name+ ", 既然你这么关心她 --我们会在战斗开始前把她带到安全的地方。 \n";
			else sTemp = "";
			dialog.text = "" + sTemp + " 但如果你这么坚决, 我同意。 去见独角鲸的首领唐纳德.格林斯彭。 他的住所在埃斯梅拉达的后面。 让我们看看那个恶棍会告诉我们什么。 ";
			link.l1 = "好的。 我这就去。 ";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // 格林斯彭节点
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "去吧, 伙计, 去让唐纳德舔你的靴子, 哈哈! 我会等你的。 ";
			link.l1 = "我这就去。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "那么, 你和唐纳德谈过了吗? 我看你已经... ";
			link.l1 = "是的。 他没有命令他的人伤害你。 所有参与那次企图的独角鲸都是被查德.卡珀招募的。 他非常不安, 并向我们保证独角鲸对你没有恶意。 他准备亲自为这次企图谋杀你和怀疑你谋杀艾伦向你道歉。 ";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "他准备来这里说这些话吗? ";
			link.l1 = "他对着圣经发誓了。 ";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "嘿, 也许那就行了。 看来唯一该受责备的混蛋是我的前水手长。 ";
			link.l1 = "我完全确定这一点, 史蒂文。 我们不需要这场战争。 没有人需要它。 ";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "好! 成交。 我准备接受唐纳德的道歉, 但他最好快点。 去告诉他。 ";
			link.l1 = "马上就去, 史蒂文。 ";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "带上你的玛丽去那里, 一起生活, 那里有很多自由空间。 ";
			else sTemp = "";
			dialog.text = "等等! " +pchar.name+ ", 我很高兴你出现在这个岛上。 简非常看重你, 但你已经超出了所有期望。 如果你在我的船员中... 实际上, 我提供给你卡珀的职位, 当你在这里的时候。 你将指挥我在‘塔尔塔罗斯’号上的驻军。 " + sTemp + "。 ";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "不, 史蒂文, 非常感谢, 但我不打算在这里呆很长时间。 找别人吧。 关于玛丽 --我们在‘塞瑞斯铁匠铺’过得很好。 ";
			else link.l1 = "不, 史蒂文, 非常感谢, 但我不打算在这里呆很长时间。 找别人吧。 ";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("你获得了500枚达布隆币");
			PlaySound("interface\important_item.wav");
			dialog.text = "不管怎样, 朋友。 就这样吧。 请接受我这份礼物。 我想你会发现这五百枚达布隆币很有用。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; // 标志: 企图已被阻止
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // 唐纳德.格林斯彭节点
			AddSimpleRumourCityTip("他们说舰队司令很尊重你, 先生... ", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("他们说你是舰队司令的忠实朋友。 是真的吗? ", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "我们来谈谈我们的事... 拿这些航行指南。 用它们乘船安全返回这里\n没有它, 你要么因为岛周围的礁石和风暴找不到通道, 所以你的船可能会和她的姐妹船一起留在这里。 记住, 你必须使用相对较小的船只才能通过礁石。 单桅纵帆船。 纵帆船。 双桅帆船。 双桅船... 四级, 不要更大\n你的目标是带着这些航行指南离开这个地方, 然后乘船回来接我。 一旦我回来, 我会加入你和斯文森的游戏。 不过, 我不知道你怎么能离开这个岛。 只有你自己能帮自己, 也许还有你的库库尔坎... ";
			link.l1 = "有趣的是, 我实际上指望它的帮助。 谢谢你的航行指南, 史蒂文。 我会找到离开这个岛的路的。 ";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "那祝你好运。 如果可以的话, 快点, 我的仓库很快就空了, 很快就没有补给了。 你知道饥饿的武装人员能做什么, 不是吗? ";
			link.l1 = "我知道。 现在我得走了。 再见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// 移除任务物品
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "你找到离开这个岛的路了吗, " +pchar.name+ "? ";
			link.l1 = "还没有, 史蒂文。 我还在岛上。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> 信息区块
		case "Total_wait":
			dialog.text = "那么, " +pchar.name+ ", 你有什么有趣的消息吗? ";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "史蒂文, 我想请你归还我被没收的物品。 ";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "史蒂文, 多给我讲讲这个岛。 ";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "你确定霍克不在岛上吗? 他穿过了传送门, 所以他一定在这里。 ";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "你认识一个绰号叫‘白人男孩’的人吗? ";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "这里哪些领土属于独角鲸和里瓦多斯? ";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "我怎么才能知道登上帮派船只的密码? ";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "听着, 有这个岛的地图吗? ";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "你有一把非常有趣的阔剑。 我以前从未见过这样的... ";
				link.l8.go = "blade";
			}
			link.l9 = "还没有问题。 但我可能很快会有... ";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "啊, 是的, 当然! 我完全忘了... 你的东西在楼上的箱子里。 你可以去拿。 莱顿不会阻止你的。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // 可以打开箱子
			{
				sld = characterFromId("SharkSoldInside_" + i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "这个岛一定很古老。 我在外环看到过古老的卡拉维尔帆船, 它们有一百多年的历史了。 它的存在是因为有大片浅水区和强大的水流, 把船架带到这里。 人们在这里生活了很长时间。 有些人出生在这里, 从未离开过。 \n clans 是在德贝当古探险队来到这里后形成的。 顺便说一下, 圣奥古斯丁号和塔尔塔罗斯号是那次探险的一部分。 塔尔塔罗斯号的货舱里有很多黑人奴隶。 他们以他们的领袖佩德罗.里瓦多斯的名字建立了里瓦多斯 clan。 他发起了一场起义, 试图夺取塔尔塔罗斯号, 但失败了。 这个人被判处缓慢死亡\n奴隶们在这里获得了自由, 并立即与其他当地人对立。 他们对统治的要求和非洲传统使大多数基督徒联合起来, 形成了独角鲸 clan\n独角鲸 clan 的队伍中有很多雇佣兵。 士兵。 军官和冒险家, 他们收集物资, 建立了一支小型专业军队, 准备利用人数优势与里瓦多斯作战。 从那时起, 独角鲸在接受新成员时变得非常挑剔, 里瓦多斯也限制了他们的野心。 你现在可以看到结果了。 ";
			link.l1 = "这个岛和外部世界有什么联系吗? ";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "过去十年没有任何联系。 当地人曾经和古巴进行贸易, 用黄金和贵重物品交换食物。 但他们现在不这样做了。 ";
			link.l1 = "嗯。 看来斯文森和黑牧师都是对的... 为什么人们在还有机会的时候不离开这个岛呢? ";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "有些人离开了, 但大多数人决定留下。 他们中的很多人在这里找到了家, 还有很多人出生在这里。 他们不想回去。 这个地方对他们来说似乎更好... 有些人太害怕乘坐旧船穿越风暴区了。 至于里瓦多斯 --他们别无选择, 只能留在这里。 ";
			link.l1 = "那你为什么来这里? 你放弃了你的优秀护卫舰, 选择了一艘双桅船... ";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "我被指控谋杀了Blaze Sharp。 我不知道为什么。 显然, 有人在搞鬼。 我的敌人数量迅速增加, 所以我不得不离开伊斯莱索罗岛, 在这里等待。 我知道这个地方很久了。 我离开了我的护卫舰, 因为她太大了, 无法绕过当地的礁石\n我一到这里就遭到了独角鲸和里瓦多斯的攻击。 他们不欢迎我的到来。 他们在晚上乘长船靠近我的船, 放火烧了她。 我们用大炮和火枪摧毁了他们的小船。 但火起了作用 --我的双桅船被烧毁了\n我们非常愤怒, 入侵了这个岛, 突袭了圣奥古斯丁号, 向他们展示了海盗是如何战斗的。 他们无法承受我们的压力, 很快就像懦夫一样逃跑了。 我们占领了圣奥古斯丁号, 结果发现这些笨蛋把她用作补给仓库。 现在他们必须按我定的价格向我购买\n我们还俘虏了当地的领导人: 独角鲸的首领艾伦.米罗和里瓦多斯的精神领袖奇米塞特。 莱顿花了接下来的几天时间侦察该地区, 我们攻击了塔尔塔罗斯号 --他们防御的薄弱点\n现在我们控制了这两艘船,  clans 不得不适应我们的存在。 现在, 我们在这里有了某种和平。 至于其他当地人, 他们似乎喜欢第三股力量的想法。 ";
			link.l1 = "现在我明白了。 谢谢你的故事! ";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "我不能确定, 但无论如何我在这里没见过他。 不在街上, 不在酒馆里, 也不在 clan 船上。 你是第一个告诉我霍克应该在附近的人。 但正如我已经说过的 --我怀疑。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "白人男孩? 嗯... 不, 我以前没听说过他。 但这并不意味着他不在这里。 我不需要知道所有的当地人渣, 你同意吗? ";
			link.l1 = "我同意。 好吧, 我去问别人。 ";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "这个岛被独角鲸。 里瓦多斯和我的人分割。 还有一个中立区。 我控制着圣奥古斯丁号和塔尔塔罗斯号\n里瓦多斯拥有他们的住所‘守护者’号。 兵营‘狂怒’号。 仓库‘贝拉斯科’号。 陌生人禁止通过, 你必须说一个特殊的密码才能进入\n独角鲸拥有很多船只。 埃斯梅拉达号是他们首领的住所和商店。 所谓的‘圣盖博科学中心’和凤凰平台。 最后但同样重要的是, 塞瑞斯铁匠铺 --他们的作坊。 除了埃斯梅拉达号, 每艘船都是禁区, 你必须说密码才能进去\n其余的船只被认为是中立的, 当地居民住在里面。 桑乔的酒馆位于卡拉维尔帆船‘ Fleron ’号上, 朱利安兄弟是‘ Gloria ’号大帆船上当地教堂的负责人。 ";
			link.l1 = "谢谢你的信息! ";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "实际上, 他们把密码给了他们自己感兴趣的人。 唉, 你不是其中之一。 但这几乎不是问题。 去一艘名为‘卡罗莱纳’的旧护卫舰。 那是肥狡猾的狗朱塞佩.法西奥住的地方。 他在这里是某种外交官。 我不知道他来这里之前做了什么, 但这个人有技巧\n他和每个人做生意。 clans 用他作为调解人。 贪婪。 为了一枚达布隆币准备吃掉自己, 但他从不表现出来。 向他要当前的密码, 不过这会花你钱。 ";
			link.l1 = "谢谢! 我会记住的。 ";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "德克斯特有一张。 他是我的二把手。 我们到达后, 他画了一张详细的地图。 如果你需要的话, 上楼和他谈谈。 ";
			link.l1 = "知道了。 谢谢! ";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "哈! 一把好阔剑。 某种独特的刀刃... 从独角鲸 clan 首领艾伦.米罗那里得到的战利品。 我就是这么命名的。 尤尔根, 一个独角鲸枪匠, 用他们在海底找到的某种神奇金属制造了它\n它不生锈, 永远不会变钝, 能同时切开一切和所有人。 我对这把武器非常满意, 我不打算留下它。 ";
			link.l1 = "我很好奇, 尤尔根能再做一把这样的阔剑吗? 当然是为了好价钱... ";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "嗯, 他肯定能再做一把。 但他不会。 尤尔根是独角鲸, 他忠于他的 clan , 永远不会为外人做任何事。 此外, 你需要非常特殊的铁来制造第二把剑。 这种铁只能在海底找到 --而谁能到那里去呢? 所以别想了。 ";
			link.l1 = "我明白了。 可惜。 ";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // 为玛丽制作'独角鲸'的可能性
			}
		break;
		// <—— 信息区块
		
		case "return":
			chrDisableReloadToLocation = true;//关闭地点
			dialog.text = "哈, 我在 horizon 看到了你的船帆, " +pchar.name+ "。 很高兴见到你, 朋友! 旅途怎么样? ";
			link.l1 = "很好。 ";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "好的。 嗯, 我准备好登上你的船, 驶向简.斯文森了。 莱顿将留在这里担任舰队司令, 他已经坐上了那个位置, 哈哈! 看来他不打算离开这个岛, 他喜欢这个地方。 ";
			link.l1 = "你曾经说过他做得很好。 ";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "是的, 他当然做得很好。 嗯, 我准备好了。 我们走吧? ";
			link.l1 = "登上我的船, 史蒂文。 我一完成这里的事, 我们就起航。 ";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "成交! 嗯, 我已经很久没有在像样的船甲板上感受到脚下的感觉了! ";
			link.l1 = "... ";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "我们到了, 朋友。 嗯, 我要去见斯文森了。 你也应该去见他, 讨论我们未来的计划。 哈哈! 炎热的日子等着我们, 嗯? ";
			link.l1 = "毫无疑问。 再见, 史蒂文! ";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // 270912 可以出售位置
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // 270912 可以出售钥匙
			pchar.questTemp.LSC.Dios = "true"; // 可以把位置交给 Dios
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// 过去的阴影
		case "shadows":
			dialog.text = "当然, 我会尽我所能! 继续。 ";
			link.l1 = "史蒂夫, 看看这个... 一颗鲨鱼牙。 别告诉我你不熟悉! ";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "哈! 你很聪明! 是的, 这是我的牙。 嗯, 这是我为了给一个美女留下深刻印象而杀死的鲨鱼的牙。 从那以后他们就叫我‘鲨鱼’。 只有少数人能在水下用一把简单的军刀做到这一点, 但我当时年轻愚蠢, Beatrice Sharp是加勒比海最美丽的女孩... 你怎么得到它的? ";
			link.l1 = "圣约翰的前刽子手给我的。 一个男人被它杀死了。 他的名字是... 约书亚.利德比特。 ";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "是的, 是我干的。 我用这颗牙割开了他的喉咙。 我对Beatrice的死感到震惊, 我认为利德比特是唯一活着的责任人。 后来我读了我在他身上找到的文件。 嗯, 他完全有权利复仇\nBlaze的妹妹只是在错误的时间出现在错误的地方。 面具不应该为她的死负责, 他不想要那样, 唯一的目标是屠夫。 我后悔谋杀了他。 事实是, 那个婊子杰西卡策划了整个事件。 ";
			link.l1 = "你保存那些文件了吗? ";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "我为什么要保存? 当然没有。 我不需要它们。 但如果你有时间, 我可以告诉你为什么面具一直在追屠夫。 ";
			link.l1 = "我有时间。 知道这不是什么好奇心, 我真的很感兴趣。 我甚至准备把你的故事写下来。 ";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "我知道, 你从不浪费时间。 听着。 约书亚.利德比特是一位普通的英国海军上尉, 他指挥着后来成为传奇的护卫舰‘Neptune’号... ";
			link.l1 = "... ";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("一小时后... ", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); // 旋转时间
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... 然而利德比特活了下来, 被一艘路过的船救了。 他的伤口使他的脸变得丑陋, 从那以后他一直戴着面具。 找到并惩罚所有不幸的罪魁祸首成了他一生的意义。 ";
			link.l1 = "我明白了... 我已经写下来了。 我想我应该读一下看看我写了什么。 这是一个非常悲伤的故事。 你见过那个杰西卡吗? ";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "当然! 在屠夫为了Beatrice甩了她之前, 她一直陪伴着屠夫的所有航行。 杰西无法原谅他。 他们称她为‘屠夫的护身符’, 因为有她在, 屠夫总是有运气\n信不信由你, 但一旦他在巴巴多斯摆脱了她, 他的生意就变坏了, 战利品变少了, ‘Neptune’号成了伊斯莱索罗岛造船厂的常客。 不过这可以解释为屠夫大部分时间都和Beatrice在船舱里, 而不是在后甲板上\nBeatrice不像杰西卡, 她不沉迷于冒险和战争, 尽管尼古拉斯教她击剑和航海。 是的, 她喜欢海上浪漫, 但她没有足够的性格硬度。 屠夫的‘Neptune’号不适合她。 最后, 她杀了她。 ";
			link.l1 = "那杰西卡呢? ";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "哦, 她很了不起。 ‘Neptune’号的每个水手都服从她的命令, 不仅仅是因为她是船长的女朋友。 杰西精通击剑和航海, 屠夫的努力没有白费。 她坚韧不拔, 鲁莽大胆, 而且长得很漂亮\n很多男人都想和她上床, 但她只想要屠夫, 打扰她真的很危险 --很多人实际上在自己的背上测试了结果, 对于最执着的人, 她的击剑课成了他们生命中的最后一课\n杰西有一把非常特殊的剑, 加勒比海独一无二, 我不知道她从哪里得到的。 火焰之刃。 没有人能抓住它的刀刃, 即使是最轻微的触摸也会留下可怕的伤口\n杰西不是天生的冒险家, 而是职业冒险家。 顺便说一下, 如果你需要更多地了解她, 你可以和你的一个熟人谈谈。 他能告诉你的比我多得多。 ";
			link.l1 = "真的吗? 那个人是谁? ";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "简.斯文森。 森林魔鬼永远不会承认, 但他对杰西卡有计划。 那是他已经占领了西部大陆, 他的名声令人羡慕的时候, 所以这只母老虎和他一样好\n屠夫摆脱杰西后, 简开始异常频繁地访问巴巴多斯, 给英国驻军带来了震动。 如你所知, 杰西卡是布里奇敦种植园主的女儿\n总之, 他的计划在私人圈子里是众所周知的, 但没有人敢说出自己的想法, 简现在可能坐在布鲁维尔德锡上, 但那时任何对他不利的话都会有糟糕的结果\n最后, 他们没有成功。 杰西无法忍受屠夫对待她的方式, 一年后在面具的帮助下进行了报复。 这场复仇对每个人都很糟糕: 对屠夫, 对Beatrice, 对面具, 对她自己。 他们都死了。 ";
			link.l1 = "不是所有人。 屠夫还活着。 ";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "什么? 我没听错吧? 他还活着? ! ";
			link.l1 = "是的。 屠夫船长没有被处决。 嗯, 他应该被处决, 但他活了下来, 多亏了雅各布.杰克曼和刽子手亨利, 他们恐吓了刽子手。 处决是假的。 我有证据。 ";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "不可能! 他现在在哪里? ";
			link.l1 = "他叫劳伦斯.贝尔特罗普, 住在皇家港。 不过他仍然很危险。 杰克曼, 在海岸兄弟会中引起了那么多麻烦的人, 一直在他的指挥下行动。 ";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "该死的! 军需官过了这么久才找到他的船长! 你说贝尔特罗普... 等等! 现在我明白为什么Blaze的文件中有一份奇怪的审讯记录了... 看来Blaze也发现了屠夫-贝尔特罗普... ";
			link.l1 = "你在说什么? ";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "我住进这所房子后, 翻遍了老Blaze的文件。 我找到了一份对某个塞缪尔.布鲁克斯的审讯记录。 里面有很多关于托马斯.贝尔特罗普的冒险经历, 以及他被称为海盗和Nicholas Sharp的密友。 看来他是屠夫的父亲。 ";
			link.l1 = "有趣。 看来Sharp和贝尔特罗普的孩子继承了他们父母的事业... ";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "似乎是这样... 但告诉我, 朋友, 你为什么对已故者的行为如此感兴趣? 你的关注点是什么? ";
			link.l1 = "我需要文件, 证明海伦.麦克阿瑟是Beatrice Sharp的女儿, 并且她有权使用这个姓氏。 我不在乎她也是贝尔特罗普。 ";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "无论是在利德比特的文件中, 还是在Blaze的档案中, 都没有关于海伦.麦克阿瑟的内容。 奇怪的是, Beatrice没有告诉Blaze他侄女的出生。 这不像她。 ";
			link.l1 = "听着, 也许Sharp的文件里还有别的东西? 我需要每一个细节! ";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "嗯, 我想是这样。 根据Blaze的笔记, 他一直在试图找到他妹妹去世的那个岛。 有关于利德比特惩罚性远征的文件。 没什么有趣的, 除了几个纬度数\n这条纬线穿过加勒比海的北部。 但没有经度的迹象。 显然, Blaze的搜索失败了, 你无法想象在那个纬度有多少小岛。 ";
			link.l1 = "那是什么? ";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "让我看看... 这里: 北纬21度32分。 我不知道这对你有什么帮助。 ";
			link.l1 = "会有帮助的。 好的, 史蒂文, 非常感谢你诚实的故事。 再见! ";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// 礁石可访问
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// 供喜欢自己添加定位器的人使用
			LAi_LocationDisableOfficersGen("Shore67", true);// 不允许军官进入
			// 立即中断
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// 激活亚历克斯的时钟任务
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// 海龟汤
		case "terrapin":
			dialog.text = "你可以这么说。 现在, 关于托尔图加\n这个岛之所以叫这个名字, 是因为它看起来几乎像一只海龟。 勒瓦瑟花了十二年时间加厚海龟的壳 --拉罗什堡。 正面攻击是自杀性的, 堡垒的重炮不会给任何机会。 所以, 煮这道美味的汤并不容易。 西班牙人尝试了很长时间, 从未成功。 ";
			link.l1 = "这就是我去找斯文森的原因。 那么你的计划是什么? 来吧, 史蒂文! ";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "我的人在托尔图加做了几个星期的像样工作, 他们获得了很多有趣的信息。 所以我有好消息给你, 伙计! 看来你不必对付拉罗什的大炮, 因为我们不是唯一受够勒瓦瑟的人。 他的朋友中有人也想让他死。 ";
			link.l1 = "继续... ";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "众所周知, 勒瓦瑟喜欢年轻的殖民地女孩。 他玩完后, 她们就消失了。 托尔图加的主要奴隶供应商是 ‘轻步兵’ 号大帆船的罗伯特.马滕\n他的伙伴, 勒瓦瑟的侄子亨利.蒂博在港口为他的赞助人挑选最漂亮的白人女孩。 所以, 不久前, 马滕从英国双桅船上弄来了一个非常漂亮的女孩。 名叫莫莉.琼斯。 他没有把她交给勒瓦瑟, 而是在晚上把她送到了托尔图加上的某个秘密洞穴给他的侄子\n船员们被告知这个女孩死于心脏病发作, 她的‘尸体’被扔到了船上。 看来我们的伙伴们决定自己留下这个漂亮的东西。 如果勒瓦瑟发现了莫莉, 这两个人就会有麻烦。 ";
			link.l1 = "我们怎么能相信这些信息? 显然, 他们两个都明白他们在玩火... ";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "没错。 但每条链都有一个弱点。 我为你找到了这样的弱点。 三天前,  ‘轻步兵’ 号的前水手费尔南德.卢卡斯喝多了, 在巴斯特尔的酒馆里说了很多有趣的事情\n原来莫莉.琼斯让他去圣约翰找她的哥哥帮忙。 但卢卡斯没有达到目标, 他从船长那里逃了出来, 坐在瓜德罗普岛, 用朗姆酒淹没他的懦弱\n安提瓜对法国海盗来说不是一个安全的地方。 记住! 福克斯上校准备在他的妻子被法国海盗杀害后, 在岛上的每棵棕榈树上吊死他们。 他可怕的海军陆战队员会执行指挥官的任何命令。 ";
			link.l1 = "我还不明白这和我们的事有什么关系... 我们来谈谈我们的人, 马滕和蒂博。 这样冒险的意义是什么? 是那个女人的魅力那么强, 还是这些奴隶贩子表现出了仁慈? ";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "我很了解那个人渣马滕。 如果他在冒险, 那意味着要么涉及黄金, 要么担心自己的皮肤。 我不知道我们的囚犯和这有什么关系\n也许罗伯特期望从她那里得到一大笔赎金, 这不太可能, 这个女孩看起来像个仆人。 或者也许... 哈! 我想知道谁对马滕来说比勒瓦瑟更可怕! ";
			link.l1 = "你为什么认为琼斯小姐仍然对总督隐瞒? 也许他们从她那里得到了他们想要的东西, 并把她交给了勒瓦瑟? 是的, 你有什么具体的关于这个蒂博的事情要告诉我吗? ";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "对这个人了解不多。 我只知道叔叔足够信任这个小家伙, 让他成为继承人。 他还带着一个女孩, 否则他们为什么需要所有这些阴谋? \n不清楚女孩被关在哪里, 为什么蒂博允许马滕带头。 有一个谜团可以帮助我们在不袭击托尔图加的情况下赢得这场游戏。 你是法国人, 所以我猜你更喜欢这种方式\n但你应该快点, 卢卡斯的醉话可能已经被马滕和勒瓦瑟的特工听到了, 你可以想象后果! ";
			link.l1 = "我明白了。 那么, 蒂博是勒瓦瑟的继承人? 他对他的叔叔隐瞒了一个奴隶女孩? 该死, 我猜这个年轻人渴望尽快看到叔叔死! ";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "没错。 根据卢卡斯的话, 这个莫莉是个罕见的美人, 我们勇敢的蒂博可能爱上了她。 你知道人们为了爱可以做什么。 去巴斯特尔\n找到这个喝醉的白痴, 让他说话。 另外, 你还应该了解莫莉和她哥哥的任何事情。 你可能想先去安提瓜, 莫莉派卢卡斯去那里是有目的的。 但目的是什么? ";
			link.l1 = "我明白了。 我们不要浪费时间。 谢谢你, 史蒂文。 ";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// 隐藏福克斯
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// 将罗伯特.马滕放入酒馆
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // 多 fighter
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");// 升级速度
			UpgradeShipParameter(sld, "TurnRate");// 机动性
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // 定时器
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // 定时器
			
			// 任务'陨落的星星'失败, 全部删除
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "继续! ";
			link.l1 = "我在圣约翰找到了莫莉的哥哥。 是福克斯的勤务兵。 但有件事很奇怪。 他的妹妹莫莉是一个众所周知的丑老太婆, 和你差不多高。 她是福克斯女儿凯瑟琳的女仆, 直到最近她一直和她在英国... ";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "至于凯瑟琳, 她确实以美貌著称, 她打算在她父亲生日时去看望他, 但由于伦敦中队的延误, 她迟到了... ";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "她的父亲在妻子被法国海盗袭击身亡后深受打击, 严格禁止她独自乘船离开英国。 所以莫莉.琼斯不可能是蒂博的囚犯。 那她是谁? ";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "嗯... 我也不知道。 也许她是另一个莫莉.琼斯, 不是你问的那个。 不过... 巧合太多了。 我不相信这一切只是偶然! 我有一些模糊的怀疑, 但是... 尽管很多奇怪的事情都可能发生! ";
			link.l1 = "你是什么意思? 告诉我! ";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "如果女儿不听父亲的命令, 在没有护卫的情况下起航呢? 上个月暴风雨很大, 信天翁可能受损, 成为马滕的容易猎物。 我怀疑凯瑟琳没有说出她的真名, 你应该明白为什么, 她在托尔图加被以莫莉的名字关押\n你知道如果她的真实姓名被泄露, 她会面临什么。 这开始有意义了! ";
			link.l1 = "该死的! 我从来没有想过! 莫莉... 凯瑟琳... 但这一切都吻合! ";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "这就是我在说的, 伙计。 不确定我们是否正确, 但是... ";
			link.l1 = "但这改变了一切! 也许我们应该向英国人寻求支持? 让海军陆战队的刺刀为我们开辟道路! ";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "冷静点, " +pchar.name+ "! 我们需要更确凿的证据。 我们不能确定。 真正的凯瑟琳可能在伦敦, 等待中队起航。 英国人有自己的问题, 他们不会冒险攻击拉罗什。 但如果我们的怀疑是真的, 福克斯上校会发现他的女儿发生了什么... \n他会在岛周围建立封锁, 等待中队的到来。 然后他会攻击这座城市。 海狐在近距离战斗中是一支可怕的力量。 我相信他会在三天内把英国国旗插在托尔图加的废墟上。 你真的想要这样吗? ";
			link.l1 = "不, 这不是我们的方式。 现在我明白马滕说的赎金是什么了。 ";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "我们必须谨慎行事。 我们甚至不确定马滕是否知道真正的莫莉的真实身份。 敲诈福克斯上校将是一个自杀性的想法。 尤其是当克伦威尔的中队即将到达时\n如果凯瑟琳死了, 我们也会输。 我们的兄弟会不想让福克斯上校比平时更生气。 这个人会带来很多麻烦。 如果凯瑟琳最终必须死, 我们必须确保她不是死于我们之手, 并且在她在我们的游戏中扮演角色之后\n但把可怜的女孩交给她的父亲会更好。 她的救星会得到回报。 如果不是在这个世界, 那就在另一个世界。 ";
			link.l1 = "看在上帝的份上... 史蒂文, 你是个天才! 我马上就去托尔图加! 我会弄清楚那个莫莉.琼斯是谁! 我敢肯定她是凯蒂.福克斯! ";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "也许... 不要浪费时间, " +pchar.name+ "。 如果我是对的 --确保她活着。 ";
			link.l1 = "我会尽力的。 再见! ";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // 不允许进入酒馆房间
		break;
		
		case "guardoftruth":
			dialog.text = "嗬嗬! 说出来吧, 朋友! 我们肯定会解决任何问题! ";
			link.l1 = "那我就开门见山了。 你认识米格尔.迪乔索吗? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "我认识他。 那个西班牙贵族卖给我一艘很棒的船 --一艘护卫舰。 嗯, 那是一艘多么棒的船啊, 想象一下... ";
			link.l1 = "让我猜猜, 独特的船体, 最高时速16节? ‘圣基特里亚’号? ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "你说对了她的船体和速度, 但名字不同 --‘圣马丁’号。 我付了他一大笔黄金, 那是我所有的积蓄。 我所有的 savings 都进了那个无赖的口袋。 ";
			link.l1 = "你确定她的名字是圣马丁而不是圣基特里亚? 你什么时候买的? 你为什么叫他无赖? ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "这么多问题! 我会按顺序回答: 我确定是圣马丁号。 我亲自帮助亚历克苏斯的工人从船尾取下了那块写着那个天主教名字的木板。 我给她取名‘幸运’ --对于这样的公主来说, 这个名字更合适\n我是在1654年冬天Blaze Sharp被谋杀前不久买的。 我为什么那样叫米格尔? 因为那个混蛋设法从普罗维登斯的西班牙军事基地偷了这艘船。 我们在圣胡安的堡垒前为他们安排了一场相当精彩的表演。 为了让战斗看起来更可信, 我牺牲了两艘半死的单桅纵帆船。 我们烧毁并淹没了这些船, 模拟了与护卫舰的战斗。 当夜幕降临时 --我们把圣马丁号开到了伊斯莱索罗岛.. 我得到了这艘船, 迪乔索得到了钱。 他告诉他的最高指挥部, 这艘护卫舰在与海盗的战斗中沉没了, 圣胡安的指挥官也证实了这一点。 ";
			link.l1 = "原来西班牙贵族就是这样中饱私囊的! 真是个无赖! 告诉我, 这真的发生在1654年冬天吗? 也许是春天? 护卫舰被风暴损坏了吗? ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "在冬天... 该死的, 我不太确定 --也可能是春天。 我真的不记得了。 护卫舰没有损坏, 她是全新的。 看起来是新建造的。 当我想到她时, 我只想气得哭出来... ";
			link.l1 = "为什么? 还有, 你那漂亮的护卫舰现在在哪里? ";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "因为她离开了我。 他们陷害了我, 把我的护身符放在Blaze的尸体上, 散布消息说我是凶手。 然后我听说我们的密码管理员马库斯.泰雷克斯打算给我一个黑标记。 所以我决定暂时逃离那个烂摊子, 去正义岛, 你就是在那里找到我的\n我不能乘护卫舰去那里, 所以我把她抵押给了黑牧师, 换了一艘装满补给的双桅船, 在和那个狡猾的迪乔索做交易后, 我没有多少钱了。 我希望卖掉补给, 一两个月后回到伊斯莱索罗岛... 嗯, 你知道剩下的。 ";
			link.l1 = "黑牧师没有等你, 所以他把她卖了";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "正是。 她被一个英国人买走了, 或者更准确地说, 被一个苏格兰人威廉.帕特森买走了。 我当然可以试着把她要回来, 但这个苏格兰人是个重要人物, 英国皇家海军的船长, 福克斯上校的好朋友。 此外, 他和杰克曼做生意的方式和你和斯文森一样\n这个苏格兰人有一个中队... 去他的, 我再也见不到我的船了。 ";
			link.l1 = "我明白了。 你不知道那个迪乔索现在在哪里吗? ";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "我不知道。 自从我买了我的‘幸运’号后, 我就再也没见过他。 ";
			link.l1 = "为什么米格尔没有提议把它卖给别人? 泰雷克斯。 巴尔巴宗。 Sharp呢? 或者帕特森? ";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "我不知道。 据我记得, 帕特森当时不在这里。 扎卡里亚。 雅克和马库斯永远不会同意, 而我... 我真的很喜欢这艘护卫舰! ";
			link.l1 = "我明白... 我一点也不明白。 到处都是谜题... ";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "又在钻研过去了? 这次你想拿下哪个岛? 哈哈哈! ";
			link.l1 = "有一个岛... 不过我还找不到去那里的路。 好吧, 史蒂文, 谢谢你的信息! 再见! ";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "祝你好运, " +pchar.name+ "! ";
			link.l1 = "... ";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// 小娱乐
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "我很高兴一如既往地帮助你。 这次你想要什么, " +pchar.name+ "? ";
			link.l1 = "又是关于你的老朋友米格尔.迪乔索的。 我知道有人又在伊斯莱索罗岛见过他。 你能帮我找到他吗? ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "嗬, 朋友, 实际上我并不知道。 我在这里没见过他。 自从我从他那里买了‘幸运’号后, 就再也没见过他。 你为什么需要那个西班牙贵族? ";
			link.l1 = "我需要他。 米格尔知道去一座古老印第安城市的路。 我真的很想那里。 ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "和往常一样, 我的朋友, 你又要把自己拖进烂摊子里了。 唉, 我帮不了你。 我建议你在定居点周围走走, 问问人们, 也许有人见过他。 你知道, 他在这里是个名人。 ";
			link.l1 = "嘿, 史蒂文, 你至少能告诉我他长什么样吗? ";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "嗯, 他二十五到二十八岁, 和你差不多高, 黑眼睛, 不戴假发。 右脸颊有一道军刀疤痕。 ";
			link.l1 = "嗯。 你知道, 很多人都符合这个描述。 ";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "他没有其他独特的细节。 他自信。 无礼, 而且非常危险。 关于他有一些流言... ";
			link.l1 = "我明白了。 好吧, 我会四处问问他的情况。 祝你好运, 史蒂文! ";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "嗬嗬! 你来得正是时候! 说出来吧! ";
			link.l1 = "有一个家伙不害怕海盗。 他不把他们当回事。 需要教训他一下, 让他学会尊重。 记住, 别杀了他。 ";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "哼! 不是别人, 正是老查尔斯! 我敢打赌你又卷入了什么事情! 让我们详细谈谈, 这次的目标是谁, 我们该教他什么";
			link.l1 = "一个来自欧洲的客人, 法国财政部的督察员 - 诺埃尔.福盖男爵。 他想在这里建立一家法国贸易公司, 但我和我的一个密友反对。 我们试图说服男爵, 由于荷兰人。 英国人, 尤其是在勒瓦瑟被击败后的海盗, 在这里贸易将非常危险, 但他不听。 我们需要让他感到恐惧, 让他自己亲身体验。 ";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "是的是的... 一个真正的男爵! .. 我们要袭击他的船吗? ";
			link.l1 = "计划是这样的: 他的船很快就会从太子港出发前往卡普斯特维尔。 你必须在男爵出发后拦截他, 把他扣为人质。 最好不要沉了船, 也不要杀船员。 毕竟法国人是我们的朋友。 你能处理吗? ";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "嗯, 我不能保证什么。 但我会试试。 那是什么船? ";
			link.l1 = "一艘名为‘法沃里’的双桅船。 ";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "双桅船不是我的护卫舰的对手。 我们很容易就能对付他们。 如果它投降, 我会让所有人活着。 ";
			link.l1 = "完美。 制造恐惧, 让他们投降。 之后, 把男爵送到老鼠出没的货舱。 尽量找最脏的地方, 但不要让他在那里超过一天, 否则他可能会生病死去。 然后让他住在船舱里, 去伊斯莱索罗岛, 把他锁在某个偏僻的地方。 让你的一些人打扮成被俘的法国商人, 让他们表现得像商人。 连续三天, 他们应该告诉他所有关于无情的海盗如何追逐他们。 抢劫他们。 索要赎金。 折磨他们的事情... 详细描述所有必要的细节。 ";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "哈哈哈! 这一定是我很长时间以来接过的最有趣的工作! 那么, 我会找到这样的演员, 伙计。 毫无疑问, 在他们讲完故事后, 你的男爵会吓得屁滚尿流! 他们会给他看弯刀和加热的推杆留下的伤疤... ";
			link.l1 = "对极了。 然后你要强迫他给潘西写信, 索要赎金。 对这样的大人物来说, 三十五万不算多。 ";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "好的。 接下来我们做什么? ";
			link.l1 = "然后你把男爵带到特克斯。 在那里你拿到赎金, 把男爵交给我。 另外, 你应该提到, 所有法国人都要为托尔图加和勒瓦瑟负责。 ";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "哈哈哈! 这真是个该死的诡计! 我们亲自, 嗯, 你知道我们对勒瓦瑟做了什么, 现在... 哈哈哈! .. 好吧, 伙计。 会完成的! 你说船很快就会到? ";
			link.l1 = "很快。 我们需要保持警惕。 ";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "别担心, 我不会让你失望的。 我会亲自处理。 当你听到男爵被俘虏的传言时, 来找我。 ";
			link.l1 = "好的。 谢谢你, 史蒂文。 ";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "当然, 伙计。 如约定的那样。 关于邪恶海盗的可怕故事, 屠杀无辜的法国商人, 鞭子的声音, 呻吟和尖叫。 带煤的火盆和烧焦的手铐。 就像应该的那样。 ";
			link.l1 = "好了! 等等。 我需要他活着。 ";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "别担心, 他会活着的。 他用颤抖的手写了那封信。 给你。 ";
			link.l1 = "上面写了什么? 他在乞求潘西把他救出去吗? ";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "完全正确, 伙计! 他在乞求! ";
			link.l1 = "把这封信扔掉, 或者更好 --烧掉它。 我们一周后在特克斯见面。 必须看起来好像我们需要时间筹集赎金。 ";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "明白了。 一周后, 北湾。 别忘了带钱: 这必须看起来很像。 之后, 来找我, 我们会解决这个问题。 ";
			link.l1 = "当然, 我敢打赌连海胆都能想到这一点。 回头见! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; // 移除计时器
			dialog.text = "嘿, 吃青蛙的人! 站住! ";
			link.l1 = "我不动。 ";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "这是你的男爵。 有点憔悴, 但完好无损。 是他吗? ";
			link.l1 = "是的。 ";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "完美。 现在, 把钱交出来, 否则他就完了! 别想骗我们, 我们已经瞄准你了! ";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "给你。 ";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "该死! 我把它忘在船上了... ";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "哈哈哈! 你是个聪明的孩子, 法国人。 带走你的大人。 告诉潘西, 他应该准备好钱: 所有法国混蛋都要为你们对勒瓦瑟和托尔图加所做的事付出代价。 你们的商人将用他们的货物和船只来支付我们。 哈哈哈! 别忘了给我们再带些男爵到群岛来, 他们给我们带来了很多利润! 哈哈哈! ";
			link.l1 = "请上我的船, 男爵。 ";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "船长, 甚至别想追我们。 你知道我是谁。 我还有更多的法国俘虏, 如果我不能及时回家, 他们都会被我的人杀死。 明白了吗? ";
			link.l1 = "时机一到, 我们会对付你们这些该死的亵渎者! ";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "哈哈哈哈! ";
			link.l1 = "... ";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // 关闭岛屿直到运送男爵
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);// 添加乘客
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// 特克斯恢复正常
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "你在耍我吗? ";
			link.l1 = "等一下, 我去拿... ";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "啊, 史蒂文, 你的笨蛋做了什么! ";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "查尔斯, 你在做什么? 钱在哪里? 我没告诉我的手下这不是真的... 所以这个白痴认为你想骗他们... ";
			link.l1 = "真遗憾! 男爵死了... 现在潘西会怎么做? ";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "嗯, 伙计, 这是你的错, 我希望你明白。 也许这对你来说会更好。 ";
			link.l1 = "我真是个白痴! 把一切都搞砸了。 好吧, 我去见潘西... 原谅我的愚蠢, 史蒂文, 再见。 ";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "你需要休息, 你正在失去你的能力。 有空来找我, 我会给你弄些朗姆酒和漂亮的姑娘。 ";
			link.l1 = "谢谢你, 有空我会来看你。 ";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// 特克斯恢复正常
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "不客气, 伙计。 对我来说, 这是今年最有趣的事! 我和我的伙计们笑得那么开心! .. 所以我想为此感谢你。 这是你的钱。 ";
			link.l1 = "你应该自己留一份。 ";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "算了吧。 我这么做是为了我们的友谊。 海岸兄弟会欠你更多, 但你连一个达布隆币都没要。 ";
			link.l1 = "不过, 至少拿五万作为服务和补偿。 谢谢你, 史蒂文! 我很高兴有一次在那个奇怪的沉船岛上遇见了你。 ";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "我也是。 查尔斯, 有空就来看我! ";
			link.l1 = "非常乐意! ";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "你迟到了一个星期! 我没告诉我的手下这不是真的... ! 他们拒绝再等, 决定结果你的男爵! ";
			link.l1 = "我真是个白痴! 把一切都搞砸了! 我该怎么跟潘西说? ";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "嗯, 伙计, 这是你的错, 我希望你明白。 也许这对你来说会更好。 ";
			link.l1 = "好吧, 我去见潘西... 原谅我的愚蠢, 史蒂文, 再见..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "你需要休息, 你正在失去你的能力。 有空来找我, 我会给你弄些朗姆酒和漂亮的姑娘";
			link.l1 = "谢谢你, 有空我会来看你。 ";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition 炫耀'幸运'号
		case "check_out_my_frigate":
			dialog.text = "有趣, 好奇。 好吧, 我们去走走。 ";
			link.l1 = "... ";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "真让我惊讶! 我不敢相信我的眼睛! 真的是她吗? 告诉我是不是她? 这是‘幸运’号吗? ! ";
			link.l1 = "是的, 我的朋友, 你的眼睛没有欺骗你。 就是她。 你想念她吗? ";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "哈哈哈, 我不敢相信! 成千上万的魔鬼! 但你从哪里得到它的? ";
			link.l1 = "从一个叫威廉.帕特森的苏格兰人那里。 是的, 是的, 就是从黑牧师那里买下它的那个人。 ";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "真让我惊讶... 什么, 他把‘幸运’号卖给你了? 这么漂亮的船? 在你买了它之后? ";
			link.l1 = "呵呵, 差不多。 这么说吧: 我们一点也合不来, 我把这艘船作为我们冲突造成的损失的补偿。 反正他也不需要船。 ";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "你更让我惊讶了... 他是为英国服务的军队上尉。 他的殖民地中队想抢劫就抢劫。 甚至我都不敢惹他。 你怎么检查的? 设法从中队那里夺走了‘幸运’号? ";
			link.l1 = "不, 中队沉没了。 实际上, 这并不容易。 战斗很激烈, 但发生在远离有人居住的地方, 只有我的水手和军官在场。 总的来说, 我不怕英国当局的追捕。 威廉.帕特森只是在一次常规冒险中消失了... ";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "哇... 我早就失去了再次见到我的燕子的希望。 好吧, 我希望这艘船会忠实地为你服务。 真的为你高兴, 朋友! ";
			link.l1 = "什么? 你不需要他吗? 我想把它归还给合法的主人... ";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "哈哈哈, 我的朋友, 把‘幸运’号留给你自己吧。 首先, 你是它的合法主人。 你在战斗中诚实地得到了它。 在这之后放弃这艘船不好。 其次, 我已经有了一艘新船。 当然, 当我买‘幸运’号时, 我没想到我会用别的东西代替它。 但是, 既然我已经不指望再见到她了, 我就向亚历克苏斯订购了一艘新的护卫舰。 你知道... 他该死的厉害。 我听说, 在这种情况下也少不了你的参与, 哈哈! ";
			}
			else
			{
				dialog.text = "哈哈哈, 我的朋友, 把‘幸运’号留给你自己吧。 首先, 你是它的合法主人。 你在战斗中诚实地得到了它。 在这之后放弃这艘船不好。 其次, 已经在为我建造一艘新船了。 当然, 当我买‘幸运’号时, 我没想到我会用别的东西代替它。 但是, 既然我已经不指望再见到她了, 我就向亚历克苏斯订购了一艘新的护卫舰。 我期待着有一天能踏上它的甲板。 ";
			}
			link.l1 = "那么, 我别无选择, 只能为自己保留这艘漂亮的船了, 史蒂文! ";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "正是。 我唯一要求你的是照顾好‘幸运’号。 相信我, 你在其他任何地方都找不到这样的船。 他是独一无二的。 我把它当作记忆来爱。 我会很高兴知道我的朋友拥有这艘船, 而不是某个无赖。 ";
			link.l1 = "好的, 史蒂文。 我保证我会保护‘幸运’号。 ";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "是的, 还有一件事... ";
			link.l1 = "听着。 ";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "既然你现在有了‘幸运’号, 我想给你提供一个业务。 ";
			link.l1 = "我非常仔细地听你说。 ";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "正如我所说, 亚历克苏斯目前正在为我建造一艘新的护卫舰。 当然, 他在速度上不太可能超过‘幸运’号, 但也不会差太多。 而且, 我只需要一两艘强大但快速的船只。 我自己也许能做到, 但两艘更好。 ";
				link.l1 = "太好了。 这是什么业务? ";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "正如我所说, 亚历克苏斯最近为我制造了一艘新的护卫舰。 当然, 他在速度上不太可能超过‘幸运’号, 但也不会差太多。 而且, 我只需要一两艘强大但快速的船只。 我自己也许能做到, 但两艘更好。 ";
				link.l1 = "太好了。 这是什么业务? ";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// 鲨鱼的护卫舰未建造
		case "check_out_my_frigate_12":
			dialog.text = "现在谈论它还为时过早, 因为我不知道我的新船什么时候能下船台。 亚历克苏斯似乎在材料提取方面有些困难。 顺便说一下, 如果你有机会, 你可以帮助他。 我相信他会给你丰厚的报酬: 我给了他一笔非常可观的预付款。 在他找到所有材料后, 我想一个月后我的船就会准备好。 然后我等你。 但一定要乘‘幸运’号来, 并提前装备好, 否则时间会很少! 是的, 还要确保西班牙人不想看到你的头被放在银盘子里。 我以后再告诉你所有细节。 ";
			link.l1 = "好吧, 我会问问我们的造船师他可能需要什么帮助。 在我帮助亚历克苏斯一个月后, 当你再次航行时, 我们再谈。 ";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// 鲨鱼的护卫舰已建造
		case "check_out_my_frigate_13":
			dialog.text = "现在谈论它还为时过早, 因为我的船甚至还没有下船台。 我还需要装备它。 所以我至少一个月后才会等你。 但一定要乘‘幸运’号来, 并提前装备好, 否则时间会很少! 是的, 还要确保西班牙人不想看到你的头被放在银盘子里。 我以后再告诉你所有细节。 ";
			link.l1 = "好吧, 那么我们以后再谈, 等你再次航行的时候。 ";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "好吧, 好的。 现在我要去住所, 如果你不介意的话。 事情, 正如所说, 不等人。 ";
			link.l1 = "很快见, 鲨鱼! 不说再见。 ";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition 与鲨鱼一起
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "我的准备好了, 你的呢? 我告诉过你乘‘幸运’号来。 我不知道你把它留在哪里了, 但乘坐任何其他船进行这样的赌博都太冒险了。 所以我在我们约定的船上等你。 别太紧张。 ";
				link.l1 = "该死, 我完全忘了, 混蛋! 等等: 我会回到正确的船上。 ";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "查尔斯, 搞什么鬼? 我告诉过你不要带中队。 在我想和你做的事情中, 绝对不需要额外的船只。 我不知道你怎么了, 但这样不行。 紧急把你的船队移到某个地方, 然后回来。 ";
				link.l1 = "是的, 我只是觉得这样更有可能... 好吧, 我明白你。 在这里等: 我很快就回来! ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "啊, 你来了, 朋友! 终于! 然后我开始担心了。 我的船几乎准备好了。 现在我把他送到了提拉克斯: 他必须为他装备上个月从捕获的重型大帆船上取下的32磅口径加农炮。 我已经驾驶它去特克斯又回来了, 必须说, 亚历克苏斯做得很好。 顺便说一下, 我还没有为它选择一个合适的名字, 尽管有几个选择。 你能帮我选一下吗? ";
			link.l1 = "当然我会帮忙! 船叫什么名字, 它就会怎么飞, 对吧? 你的选择是什么? ";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "到目前为止, 我已经选定了三个选项。 ";
			link.l1 = "... ";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "第一个选项是‘幻影’。 这艘护卫舰速度快, 火力强大, 有了这个名字, 从哈瓦那到库马纳的所有守财奴一提到它就会发抖! ";
			link.l1 = "是啊, 你还需要在雾中出现和消失, 让水手们肯定开始划十字, 哈哈! 好名字, 我喜欢。 ";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "我也喜欢。 第二个选项是‘鲨鱼’。 怎么样? 为什么不给我的船起个自己的绰号? 让我们和他同名, 哈哈! ";
			link.l1 = "‘鲨鱼’号上有个鲨鱼... 讽刺。 但每个人都会确切地知道这艘船属于谁。 ";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "我对此的看法差不多。 第三个选项是‘疾风’。 让每个人都害怕靠近我的船, 哈哈哈! ";
			link.l1 = "因为你可能会遇到来自侧面的疾风般的炮弹? 还有什么, 不错。 ";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "正是! 但现在我无法在这三个名字之间做出决定。 所以来吧, 帮忙。 如你所愿。 ";
			link.l1 = "我建议叫‘幻影’。 这样所有的商人一看到你在地平线上就会抛出白旗! ";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "我喜欢‘鲨鱼’这个名字。 每个人都应该知道这艘船不是某个新手, 而是海岸兄弟会的首领本人! ";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "我认为‘疾风’是个好名字。 任何战士。 私掠船船长或商人都应该知道, 如果他决定与这艘船战斗, 会发生什么。 ";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "你看 - 甚至军人也会开始这样做, 哈哈! 那么, 就这么定了。 拿着杯子, 朋友。 让我们为我的新船干杯。 为‘幻影’! ";
			link.l1 = "为‘幻影’! ";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "让他们在跨越我的道路前三思! 那么, 就这么定了。 拿着杯子, 朋友。 让我们为我的新船干杯。 为‘鲨鱼’! ";
			link.l1 = "为‘鲨鱼’! ";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "如果他仍然决定, 这样的疾风会覆盖他, 热带风暴将显得像微风! 那么, 就这么定了。 拿着杯子, 朋友。 让我们为我的新船干杯。 为‘疾风’! ";
			link.l1 = "为‘疾风’! ";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "愿这艘船忠实地服务, 不知失败的苦涩! 好吧, 现在言归正传。 ";
			link.l1 = "我仔细听你说。 ";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "告诉我, 查尔斯, 你知道‘黄金舰队’是什么吗? ";
			link.l1 = "哈-哈! .. 我已经被朗姆酒呛到了。 史蒂文, 别告诉我你要乘两艘护卫舰去抢劫加勒比海武装最严密的护航队。 ";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "嗯, 不, 当然, 我不是自杀。 我们肯定不会抢劫整个护航队。 但我们可以从那里抢点东西。 ";
			link.l1 = "史蒂文, 对不起, 当然, 但我还没准备好。 是的, 如果我们惹上他们的舰队, 西班牙人会把我们活活烧死! 你自己去吧。 ";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "好吧, 我们在哪里不消失... 我准备参加! ";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "啊! 真遗憾。 没有你, 我太冒险了。 好吧, 现在我不劝了, 但考虑一下, 好吗? 如果你决定这么做, 请告诉我。 ";
			link.l1 = "如果我决定了, 当然。 对不起, 史蒂文。 ";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "这种冒险不会放弃! 那么, 你呢? 也许改变主意了? ";
			link.l1 = "不, 朋友, 对不起, 但我还是拒绝。 ";
			link.l1.go = "exit";
			link.l2 = "好吧, 我们在哪里不消失... 我准备参加! ";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "你可能准备好了, 但你的船没有。 我告诉过你乘‘幸运’号来。 我不知道你把它留在哪里了, 但乘坐任何其他船进行这样的赌博都太冒险了。 所以我在我们约定的船上等你。 别太紧张。 ";
				link.l1 = "该死, 我完全忘了, 笨蛋! 等等: 我会回到正确的船上。 ";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "但不: 你还没准备好, 查尔斯。 我告诉过你不要带中队。 在我想和你做的事情中, 绝对不需要额外的船只。 把你的舰队移到某个地方, 然后回来。 ";
				link.l1 = "是的, 我完全忘了。 等等: 我很快就会回来, 不带中队。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "成千上万的魔鬼, 这正是我想听到的! 所以, 我建议你和我从护航队那里抢一块。 很多战利品... ";
			link.l1 = "抢, 你是说? 不被警戒船抓住? ";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "正是。 看, 你可能知道, ‘黄金舰队’在贝洛港集结, 然后从那里前往哈瓦那。 在哈瓦那之后, 拦截他就没用了: 他带着这样的护卫穿越大西洋前往西班牙, 只有完全的白痴才会把头伸过去。 在从贝洛港到哈瓦那的过渡时期, 情况也好不到哪里去。 当然, 你可以试试, 但为此你需要组建一个甚至能把堡垒像坚果一样炸开的中队。 但在贝洛港, 船只从缅因州各地汇聚而来, 在那里它们不再受到特别保护。 ";
			link.l1 = "只是现在过渡的时间和这样的船只的名字是严格保密的。 我们不会在贝洛港附近闲逛半年, 拦截所有前往港口的西班牙船只。 ";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "我们当然不会。 例如, 从卡塔赫纳出发的船只自己航行, 正如你正确指出的, 只有上帝知道它们是什么船, 什么时候出发。 但从加拉加斯出发, 旁边有一个西班牙矿场, 而且离贝洛港相当远, 船只并不完全是单独的。 ";
			link.l1 = "怎么不是完全单独的? ";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "我设法发现, 一艘装满货物的船独自或带着小护卫离开加拉加斯, 但在马拉开波湾的某个经度, 西班牙军舰会与它会合, 确保它的进一步安全。 你认为他们怎么知道什么时候。 在哪里需要见面? ";
			link.l1 = "他们一定被告知了什么... ";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "对。 在主船出发前, 一艘信使船从加拉加斯前往贝洛港, 报告会面的地点和日期, 以及西班牙船的名字。 然后它返回, 并携带确认将在正确的时间和地点与船会面。 只有在那之后, 我们与你的目标才从加拉加斯提出。 ";
			link.l1 = "但如果我们拦截了信使, 那么加拉加斯的船就不会收到确认, 也不会离开港口。 你对此有什么想法? 此外, 我们怎么去抓信使自己? 我们也不知道他什么时候离开。 ";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "这里有个小障碍。 当然, 西班牙人为此使用信使单桅纵帆船, 但这是有风险的: 他们被第一个反海盗拦截的机会太大了。 所以你可以等很久才会派船。 因此, 如果有机会, 他们会把指示和良好的强大但高速的船只一起传递 - 例如商人或走正确路线的私掠船。 \n就像密封邮件一样。 此外, 这比派遣一艘单独的信使船便宜得多, 即使是单桅纵帆船。 贪婪的西班牙官员喜欢省钱, 同时把东西塞进自己的口袋, 呵呵。 ";
			link.l1 = "我想我明白了! 我需要成为这样的商人吗? ";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "正是! 我们很幸运: 我从可靠来源得知, 加拉加斯现在正在寻找这样的信使, 在未来三周内派他带一封信。 而你正好有一艘强大而快速的船, 甚至是西班牙人建造的! 获得GVIK许可证, 为了更可信 - 一次六个月, 在加拉加斯购买足够的货物, 以便在贝洛港有利可图地转售, 然后去当地的港务局局长那里, 问你是否需要沿途带些什么。 \n如果港务局问起, 就自称是西班牙人。 还有 - 甚至不要想带中队。 我们不需要引起太多注意, 否则整个企业可能会被掩盖。 ";
			link.l1 = "从他们给我的文件中, 我会知道船和护航队会面的日期和地点? ";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "没那么简单。 我告诉你: 文件是密封的。 你不能自己打开它们。 它们将在贝洛港的港务局打开, 然后他们会写一个回复, 如果你愿意说你要回加拉加斯, 他们会让你把他带到那里。 答案当然也会被密封。 ";
			link.l1 = "那我怎么知道会面的地点和日期? ";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "你将不得不聪明一点, 以某种方式偷看... 例如, 在贝洛港打开文件并撰写回复的那一刻。 或者只是在他们给你需要带到加拉加斯的确认时偷走它们。 但这不是一个好选择: 在此之后, 一切都可能出错。 ";
			link.l1 = "当然很困难... 但我想我能处理。 ";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "反过来, 我会从马库斯那里拿我的船, 在库拉索的圣玛丽亚角锚地等你。 当你完成后, 就搬到我这里来。 我们在指定的坐标拦截这艘船, 然后立即离开那里。 现在你明白为什么需要强大但快速的船只了吧? 我根本不想与西班牙军事中队战斗。 你将不得不逃离他们。 ";
			link.l1 = "明白。 那么我出发了。 在圣玛丽亚角见! ";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "对, 我们在那里见面。 好吧, 朋友, 祝你好运! 希望我们的业务成功。 ";
			link.l1 = "我也希望如此。 无论如何, 我要走了。 ";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("探索模式: 计时器已禁用。 ");
		break;
		// 失败
		case "SharkGoldFleet_23":
			dialog.text = "该死的查尔斯! 我以为再也见不到你了! 你去哪里了? 我在约定的地方等你, 但一直没有等到。 也没有你的消息。 ";
			link.l1 = "对不起, 史蒂文。 我无法完成我的任务。 ";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "唉, 错过了这么大的一条鱼... 好吧, 别难过。 下次好运。 ";
			link.l1 = "希望如此。 ";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = ""+ PChar.name+ ", 搞什么鬼? 我告诉过你不要带中队! 明白: 我们不需要任何压舱物, 否则整个行动可能会失败! 我不知道你怎么了, 但这样不行。 紧急把你的商队送到某个地方, 然后乘一艘船回来。 我在这里等你。 ";
				link.l1 = "是的, 我只是觉得这样更有可能... 好吧, 我明白你。 在这里等: 我马上回来! ";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = ""+ PChar.name+ ", 搞什么鬼? 我告诉过你乘‘幸运’号来! 明白: 我们需要两艘快速而强大的船, 否则整个行动可能会失败! 我不知道你怎么了, 但这样不行。 紧急把你的破船换成‘幸运’号, 然后回来。 我在这里等你。 ";
				link.l1 = "是的, 我只是觉得这艘船更好... 好吧, 我明白你。 在这里等: 我马上回来! ";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "我的朋友, 你来了! 那么, 你觉得我的帅哥怎么样? ";
			link.l1 = "华丽的护卫舰, 史蒂文! 我不会拒绝这个... ";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "不, 你现在有‘幸运’号了, 哈哈! 好吧, 告诉我进展如何。 ";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "一切都很顺利: 我成功地扮演了一个诚实可靠的商人。 我把文件带到了贝洛港, 在那里我设法分散了当地港务局局长五分钟的注意力, 并为自己重写了船只与货物和军事中队会面的日期和坐标。 ";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "有一些小麻烦。 这封信是由信使送到贝洛港的。 我拦截了它, 把它交给了收件人, 甚至收到了回复, 但港务局局长猜到了我不是应该带文件的人。 我不得不打了一架才离开那里。 但我知道了船只与货物和军事中队会面的日期和坐标, 并把回复送到了加拉加斯, 所以战利品在等着我们! ";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "等一下。 你说‘船只’? ";
			link.l1 = "是的, 鲨鱼! 会有两艘! ";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "哈哈哈, 我们会中头奖的! 好吧, 我的野兽准备好接受火的洗礼了。 但他还没有参加过战斗, 所以让我们来领导这场战斗。 现在, 我将加入你的中队。 ";
			link.l1 = "我要指挥海岸兄弟会的首领史蒂文.多德森本人吗? 成交! ";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "好吧, 别太傲慢: 这只是因为我将第一次在我的船上战斗。 并注意为战利品船准备好自由军官。 因为他们的货舱会被塞满, 我的团队中没有人能独自管理这艘船... 好了, 别再废话了。 战利品在等着我们! ";
			link.l1 = "正是! 我要去我的船了。 ";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "是的, 你继承了... 那么我们需要准备好中队会在约定日期之前到达那里, 我们将不得不与所有人同时战斗。 ";
			link.l1 = "你为什么这么说? ";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "你动动脑筋。 在贝洛港, 他们知道载有货物的船肯定会离开加拉加斯, 因为你把回信带到了那里。 但既然你已经暴露了自己, 他们会尽力阻止我们拦截这艘船。 我认为中队会提前到达那里。 如果是我, 我会这么做。 所以, 让我们准备好迎接一场艰苦的战斗。 撤退晚了。 ";
			link.l1 = "别担心。 你和我是两只海狼, 我们经历过这些! ";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "你说的对。 好吧, 我的野兽准备好接受火的洗礼了。 但他还没有参加过战斗, 所以让你来领导这场战斗。 同时, 我将加入你的中队。 ";
			link.l1 = "我要指挥斯蒂芬.多德森本人, 海岸兄弟会的首领吗? 成交! ";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "没时间聊天了, " +pchar.name+ "! 我们去拿战利品吧! ";
			link.l1 = "愿运气与我们同在! ";
			link.l1.go = "exit";
		break;
		// 在岸边分配战利品
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "成千上万的魔鬼! 干得好, 查尔斯! 战利品比我最初想象的要丰富得多! 我认为这次旅行绝对值得。 ";
				link.l1 = "我完全同意你的看法, 史蒂文! 今天绝对是我们的日子! ";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "干得好, 朋友。 虽然, 我们必须承认我们损失了很多战利品。 ";
					link.l1 = "我同意, 史蒂文, 我们可以做得更好。 但那里的东西也不错! ";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "该死的! 这是个好主意... 结果这次战役的花费超过了利润。 查尔斯, 实际上我把指挥权交给了你, 而你却把一切都搞砸了! ";
					link.l1 = "什么也别说... 我自己也该死的生气。 有多少战利品从手中溜走了! ..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "好吧, 我们都做得很好。 我想出了一个计划, 并获得了关于信使的信息, 你出色地执行了这个计划。 我们都为我们的战利品平等地战斗。 因此, 我提议根据海岸兄弟会的法律来分配: 平等! ";
			link.l1 = "我们会这么做! ";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "好吧, 现在我要去伊斯莱索罗岛。 我需要修理这艘船, 并正确庆祝我新船的第一次成功航行。 祝你好运, 朋友! 总是很高兴在我的住所见到你! ";
			link.l1 = "我很高兴我们的业务如此有利可图。 我肯定会找个时间拜访你。 祝你好运! ";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "好吧, 把它都留给你自己。 如果还有什么剩下的话。 我不在乎这些小东西。 毕竟, 是我让你卷入了这一切。 ";
			link.l1 = "是的, 我也有错... 对不起, 史蒂文。 ";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "别道歉, 我仍然欠你我的命, 我不会忘记的。 现在我要去伊斯莱索罗岛。 我们需要修理这艘船并清洗它... 虽然, 有什么可清洗的... 祝你好运, 伙计! 总是很高兴在我的住所见到你! ";
			link.l1 = "好吧, 什么都可能发生, 失败也会发生。 最重要的是我们还活着。 我肯定会找个时间拜访你, 朋友! 祝你好运! ";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // 移除所有多余内容, 以免出错
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}