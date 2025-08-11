void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你想要什么? ";
			link.l1 = "目前没什么事。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//在商店寻找助手
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "先生, 您需要什么吗? ";
			link.l1 = "你是格拉拉姆.拉沃伊, 对吗? ";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "谁问的? 先生, 别在我喝朗姆酒时打扰我。 我没心情聊天。 ";
			link.l1 = "我不会占用你太多时间。 我是被圣皮埃尔的一位商人派来的。 你曾是他的员工。 他在找你, 并且... ";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "哈, 他在找我? ! 那个该死的吝啬鬼可真有意思! 他真以为我会一辈子为这么微薄的薪水工作吗? 他是加勒比海最贪婪的守财奴! 我为他卖命五年, 他除了能省就省, 从没多付过一分钱! 呸, 连买杯酒都不够! \n现在他可以自己数货了, 我辞职了。 圣皮埃尔没人会为那个吝啬鬼工作, 这是肯定的。 他只关心一件事 —为自己多赚钱, 少给员工发工资。 ";
			link.l1 = "我猜你不打算回去为他工作了? ";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "是的, 上帝作证, 我绝不回去! 我就待在勒弗朗索瓦等船来, 如果他们愿意, 我就签约当事务长。 如果不行, 那就当个普通水手。 我甚至连看都不想看那个守财奴一眼。 如果我要受穷, 那至少要是个自由人... ";
			link.l1 = "我明白了, 这就是我想知道的。 祝你好运, 格拉拉姆! ";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "先生, 请让开。 你挡着我了! ";
			link.l1 = "就一个问题, 先生。 你是格拉拉姆.拉沃伊吗? ";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "哈! 是我。 你想干什么? ";
			link.l1 = "圣皮埃尔的一位商人在找你。 你曾是他的员工, 对吗? ";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "哈哈! 真可笑! 那位‘陛下’找我有什么事? 他是决定付我最后两周没给的工资了吗? 还是他在数桶数和欺骗顾客的同时遇到麻烦了, 嗯? 哈哈哈! ";
			link.l1 = "他让我找你, 想弄清楚你为什么不再去他店里工作了。 ";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "为什么? 因为他是个该死的吝啬鬼, 还是个糟糕的雇主! 我现在是海岸兄弟会的一员, 不再是奴隶, 而是自由人! 看看周围, 我现在过得很开心! \n很快我就要起航, 数从西班牙人那里抢来的比索和达布隆, 而不是数香蕉箱! 至于那个吝啬鬼 —我怀疑他找不到人代替我。 圣皮埃尔没人蠢到愿意为他工作, 我们已经把他的名声传遍了岛上所有学徒, 哈哈! ";
			link.l1 = "我明白了。 这就是我想知道的。 祝你好运, 格拉拉姆! ";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "我能为你做什么? ";
			link.l1 = "下午好。 我猜你是格拉拉姆.拉沃伊? ";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "是的。 你想要什么, 先生? ";
			link.l1 = "圣皮埃尔的一位商人在找你。 你曾是他的员工, 对吗? ";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "嗯, 让他接着找吧。 我不欠他任何东西。 他还欠我两周工资, 但我都懒得去要。 我希望他被自己的铜板噎死。 ";
			link.l1 = "嗯。 所以你是永远离开他了, 对吗? ";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "你说得对, 先生。 我的前雇主是个罕见的吝啬鬼, 简直是圣经级别的。 我现在是海岸兄弟会的成员, 新伙伴们很看重我的才能。 我现在挣的是以前的两倍, 还有奖金\n我怀疑我们的好朋友找不到人代替我。 圣皮埃尔的人都知道他贪婪, 没人蠢到愿意为他工作。 ";
			link.l1 = "我知道了。 这就是我想知道的。 祝你好运, 格拉拉姆! ";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //取消计时器
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "你好, 先生。 我不想太唐突, 但我认为我的资质非常适合你提供的职位。 ";
			link.l1 = "下午好。 你为什么这么认为呢? ";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "先生, 您好! 请允许我介绍一下自己。 ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "愿您身体健康, 亲爱的先生。 您是在招聘商人职位吗? ";
			link.l1 = "是的。 你能介绍一下自己吗? ";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "我曾在弗朗西斯.迪布瓦船长手下担任军需官。 他对我的技能相当满意, 但我在战斗中受伤, 不得不休假治疗。 现在我已经完全康复, 但一想到波涛汹涌的大海就恶心。 不, 我现在唯一的愿望就是留在陆地上\n (小声说) 如果你选择我, 我会额外支付五百比索和二十五枚金达布隆。 ";
			link.l1 = "我知道了。 我会考虑的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "我以前是个小贩, 但为了躲避一些债主, 我出海在一艘商船上当事务长。 命运把我带到了这个村庄。 反正我也不太喜欢水手的生活, 我很乐意接受你的提议\n (小声说) 如果你选择我, 我不仅会给你五百比索, 还有这包沉甸甸的琥珀。 ";
			link.l1 = "我知道了。 我会考虑的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "我曾在格拉斯哥的一个港口仓库当职员。 我来到加勒比海寻找财富, 设法赚了足够的钱, 能体面地安度晚年。 但我厌倦了海上航行, 想在岸上过平静的生活\n (小声说) 如果你选择我, 我会给你五百比索, 再加两千五百比索作为额外报酬。 ";
			link.l1 = "我知道了。 我会考虑的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "先生, 请做出正确的选择。 别忘了那些达布隆... ";
			link.l1 = "我决定选你了。 收拾一下, 我们去圣皮埃尔。 ";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "我还没决定呢... ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "我希望你选我, 先生。 琥珀也是很有价值。 很有用的东西... ";
			link.l1 = "我决定选你了。 收拾一下, 我们去圣皮埃尔。 ";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "我还没决定呢... ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "商人不会对我的工作失望的。 别忘了你的奖金。 ";
			link.l1 = "我决定选你了。 收拾一下, 我们去圣皮埃尔。 ";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "我还没决定呢... ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "让我收拾一下东西! 我会在酒馆门口等你。 ";
			link.l1 = "... ";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "我马上就来, 先生! 我会在酒馆门口等你。 ";
			link.l1 = "... ";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "我去拿我的旧手提箱, 然后在酒馆门口等你, 先生! ";
			link.l1 = "... ";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //取消中断
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("返回圣皮埃尔... ", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "那么, 我想从现在起这里就是我工作的地方了? 谢谢您选择我, 先生。 这是您的五百比索和承诺的奖金。 ";
			link.l1 = "我很感激... 让我把你介绍给你的雇主。 ";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//朗姆酒走私
		case "Rum_Cap_Over":
			dialog.text = "先生, 我必须请你立即离开我的船。 我们正在起锚开航! ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //取消计时器
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "嗯? 你是谁, 伙计? ";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "喝杯朗姆酒吧, 水手! 哈哈! 欢迎登上我的小帆船。 你是来取货的? ";
			link.l1 = "是的。 不然我来这儿干嘛? ";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "喝杯朗姆酒吧, 水手! 哈哈! 欢迎登上我的小帆船。 你是来取货的? ";
				link.l1 = "是的。 不然我来这儿干嘛? ";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "哎呀, 真是个嫩小子! 伙计们, 这家伙看起来像个新兵蛋子! 把他扔到海里去! ";
				link.l1 = "哼! ";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "伙计们! 把箱子装到小艇上! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "所有朗姆酒 crate 都在你的小艇上了。 勒弗朗索瓦港就在这里的正南方。 抓紧时间, 我也该起锚了! ";
			link.l1 = "别浪费时间了, 先生们! 祝你们好运! ";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "你也一样, 伙计... ";
			link.l1 = "... ";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("将朗姆酒运到勒弗朗索瓦。 继续绕岛航行。 ");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//首次出海的福利
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//首次出海的福利
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "我们一直在等你, 先生。 事情怎么样了? 你拿到 crate 了吗? ";
			link.l1 = "一切顺利。 朗姆酒 crate 已经在小艇上了。 ";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "很好。 剩下的我们来处理。 你去圣皮埃尔的酒馆领报酬。 夜里在丛林里要留意并保持警惕。 ";
			link.l1 = "祝你们一切顺利, 先生们。 ";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, 新的目的地标记
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//从妓院送女孩
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "下午好, 先生! 我说, 你看起来不像通常在我们殖民地闲逛的那些破烂恶棍。 从你的穿着来看, 你一定走了很远的路... 从欧洲来的, 是吗? ";
			link.l1 = "正是, 先生。 "+GetFullName(pchar)+", 为您效劳。 您需要什么? ";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "请允许我介绍自己 - "+GetFullName(npchar)+"。 几年前我从法国来到这个可怕的地方。 但那无关紧要。 我有一件非常微妙的事情要拜托你\n请理解, 如果我不确定你是位绅士, 我绝不会提出这样的请求。 ";
			link.l1 = "请说出你的请求, 先生。 如果在我能力范围内, 我当然会尽力帮助。 ";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "很高兴听到你这么说, 德.莫尔先生。 现在, 怎么说才得体呢... 这个镇上有一家妓院。 最近那里来了个新女孩; 年轻。 皮肤白皙。 金发碧眼, 美得惊人! 现在, 我已经观察她好几个星期了... 非常渴望能和她私下待一段时间\n但我的身份和地位让我去这种地方很... 不方便。 想想那些流言蜚语! \n这就是我向你求助的原因。 简单地说, 你是岛上的新来者, 人们不认识你, 也不在乎你做什么... 目前是这样。 你可以帮我一个大忙, 先生。 ";
			link.l1 = "我想我明白你的意思了。 ";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "感谢你的谨慎, 先生。 我不能去找那个女孩, 所以女孩必须来我这里。 到我家来。 我请你去妓院和老鸨谈妥, 让她允许你安排金发女孩‘上门服务’一晚\n奥罗拉不会拒绝的, 她以提供这种送货服务而闻名, 尽管通常要贵一点。 之后你把女孩带到我家。 作为报酬, 我会给你六千比索。 奥罗拉通常收取三千或三千五百比索用于女孩上门服务一晚。 你可以保留额外的部分作为辛苦费。 ";
			link.l1 = "听起来不算太复杂。 我可以做。 ";
			link.l1.go = "GigoloMan_4";
			link.l2 = "先生, 我和你一样看重自己作为绅士的声誉。 请原谅, 但我不能完成你的请求。 我必须拒绝。 我可能应该去酒馆看看老板有没有工作给我。 ";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);//妓院开放
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);//妓院
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);//酒馆
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "我很高兴听到你这么说。 现在听着, 女孩的名字叫露西尔。 我请你在天黑后送她到我家, 不早于晚上十一点, 以免引起任何旁观者的注意。 敲门, 我会开门。 \n我的房子位于总督官邸的左侧, 背对着它 —一栋有红色屋顶的两层豪宅。 你很容易找到, 附近还有一家商店。 事实上, 我现在正要回家; 你可以跟着我看看房子的样子和具体位置, 这样晚上就不会迷路了。 \n关于手头的事 —给, 拿六千比索。 我期待你按约定时间到达! ";
			link.l1 = "我们说定了。 你金发的露西尔今晚会到你家门口。 ";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);//妓院开放
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);//妓院
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "日安, 先生。 怎么, 你是今晚雇我的人吗? 哎呀, 我得说, 我真幸运能遇到这么英俊潇洒的绅士, 不像那些从码头来的浑身焦油和汗水臭味的粗人... ";
				link.l1 = "抱歉, 露西尔, 今晚不是我。 我是代表我的好朋友来的, 他因为很多复杂的原因不能出门, 所以我来把你带给他。 别难过, 他是个温和的人, 对你很有好感。 我想你最终会开心的。 ";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "嗯... 你说得对, 亲爱的。 我们走吧? ";
				link.l2.go = "GigoloGirl_1a";
				// < —legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "先生, 我希望你明白, 我不能晚上陪你闲逛。 你需要尽快带我去你朋友家, 否则我就直接回老鸨那里, 你就要浪费钱了。 ";
				link.l1 = "好吧, 我明白。 跟我来! ";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //关闭位置
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// < —legendary edition
			dialog.text = "太遗憾了... 我一眼就喜欢你了, 先生。 我本来想和你共度一晚的... 也许下次吧。 我们走? ";
			link.l1 = "是的。 跟我来! ";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "多宏伟的房子啊。 是这里吗? ";
			link.l1 = "是的。 进来吧。 别害怕, 我的朋友是个好人。 ";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "你低估我了, 先生。 我不怕, 我知道怎么保护自己。 现在, 也许过段时间你可以付钱给老鸨, 和我共度一晚? 我保证那将是你一生中最美好的夜晚! ";
			link.l1 = "一切皆有可能, 露西尔。 也许我们会再见面。 再见! ";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//带着被俘西班牙人的海盗
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//取消计时器
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//取消计时器
			// Rebbebion, 新的目的地标记
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "这是什么情况? ! 你是谁? 你在这里想干什么? 快点, 滚出去! ";
			link.l1 = "你不太礼貌啊, 老兄。 ";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "听着, 小子, 我没被教过要礼貌, 就像我没学过读书写字一样, 但用弯刀劈开你的脑袋对我来说就像妓女向后倒一样容易。 我以我的灵魂发誓, 如果你不马上离开这里, 你就会被抬出去。 明白了吗? ";
			link.l1 = "不, 你听着, 你这个无赖。 你的阴谋已经暴露了。 我需要那个人活着, 所以放下武器逃跑吧。 我的身后丛林里有一队法国士兵。 如果你跑得够快, 也许能保住你那可怜的命。 ";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "好吧, 好吧, 冷静点。 我这就走。 ";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//取消中断
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "哇-什么? 你在虚张声势, 伙计! 拿下他, 伙计们, 拿起武器! ";
			link.l1 = "那你就自作自受了, 看招! ";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//被俘的西班牙人
		case "CaptiveSpain":
			dialog.text = "感谢上帝! 啊, 你是法国人? 妈的, 你对付那些强盗的样子真帅。 但别以为我会就此屈服投降, 我会让你看看西班牙人怎么战斗! 圣地亚哥! ";
			link.l1 = "不, 等等, 求你了! ";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "我宁死也不愿被法国人抓住。 你战斗的时候我从一具尸体上拿了把弯刀... 现在我要让你跳西班牙方阵舞! ";
			link.l1 = "你们西班牙人固执得像骡子! ";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "该死的... 你赢了。 我投降, 该死的法国人。 我听凭你处置。 ";
			link.l1 = "收起你的刀, 让我说话, 你这个固执的卡斯蒂利亚人! 我不想你死, 也不打算把你送进监狱! ";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "那你想干什么? 你为什么杀了那些海盗? 你的士兵在哪里? ";
			link.l1 = "没有士兵。 我试图欺骗那些恶棍, 但如你所见, 没成功。 我是按照你老朋友的请求独自来的。 他叫"+pchar.questTemp.Sharlie.Captive.Name+", 是圣皮埃尔的一位银行家。 ";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? 我不认识叫这个名字的人... ";
			link.l1 = "我也对你和你的被俘一无所知。 我是从他那里得知你要被转移到一艘英国船上的。 我的任务是把你交给他, 我发誓会完成! 现在, 如果你想活下去, 就跟我来。 ";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "反正我也没得选... 你那个银行家朋友再差也不会比英国人及其糟糕的厨艺更差... ";
			link.l1 = "你终于做了个明智的决定。 现在别再说了, 我们去圣皮埃尔。 离我远点, 别迷路。 如果你跑, 我会抓住你, 再把你揍个半死。 ";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//夜间进入
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, 新的目的地标记。 belamour 修正 - 之前方向错误
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//有失踪女儿的市民
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //取消中断
			dialog.text = "你需要什么, 先生? 我没时间闲聊, 长话短说。 ";
			link.l1 = "你是普罗斯珀.特鲁巴尔, 对吗? ";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "是的, 是我。 但你占了上风。 请告诉我你是谁, 你到底想要什么。 ";
			link.l1 = "我叫"+GetFullName(pchar)+"。 港口管理员"+GetFullName(characterFromId("Fortfrance_portman"))+"派我来找你。 他说你急需帮助... ";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "我的上帝, 是的! 那个无赖指挥官甚至没听我的投诉! 他要么太懒, 要么太胆小, 不肯帮忙。 你真的是来帮我的吗? 如果是这样, 我不会让你白帮忙的! ";
			link.l1 = "是的, 普罗斯珀。 告诉我发生了什么, 我该怎么帮你。 我听说你女儿失踪了... ";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "是的, 我亲爱的女儿塞莱娜已经失踪两天了。 她去附近的堡垒散步, 但没回来, 于是我自己去了堡垒, 士兵们告诉我她根本没去过那里! \n但我回来时遭到了两个野蛮印第安人的袭击! 他们挥舞着棍棒扑向我, 试图殴打我\n但我不是小猫, 所以我一拳打在其中一个人脸上, 争取到足够时间拔出手枪射击。 我没打中, 但把他们吓跑了。 我设法到达城门, 告诉卫兵这次袭击。 他们跑到丛林里, 但野蛮人已经跑远了\n我确定他们要为塞莱娜的失踪负责。 此外, 上周又有两个人失踪了 —塞萨尔.布兰切特和吉尔伯特.库西! 一个前往海湾, 另一个前往勒弗朗索瓦。 他们再也没有回来。 ";
			link.l1 = "所以印第安人就在城门口袭击市民? 这太胆大了... ";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "与此同时, 我自己到丛林里找她, 在城市北面发现了一个洞穴。 我发现那些混蛋就蹲在里面。 我在入口处看到几个印第安人, 里面肯定还有一些\n我听到一个女孩在尖叫... 那是我的塞莱娜, 我确定, 是她的声音! 我强忍着没有立刻冲进去 —形势对我不利, 他们会杀了我。 我死了对她也没用。 ";
			link.l1 = "但他们到底为什么攻击并俘虏市民? ";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "我不知道... 也许是卖给海盗或奴隶贩子? 也许他们会活活吃掉他们, 毕竟他们是野蛮人。 ";
			link.l1 = "天啊, 他们是食人族? 我以为那些只是欧洲用来吓唬孩子的故事... ";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "故事? 好吧, 有些像你这样的人也这么想, 直到加勒比人把他们放在火上烤着吃了... 所以, 我立刻去找指挥官, 请求派一支惩罚性的突袭队来救我的塞莱娜。 他拒绝了! 他说女孩失踪, 可能是跟男孩跑了, 不是印第安人干的。 他建议我去当地的干草棚找找\n至于另外两个失踪的人... 他说其中一个有走私嫌疑, 另一个可能在勒弗朗索瓦的酒馆里喝死了。 总之, 我一无所获, 决定自己行动。 ";
			link.l1 = "你打算怎么做? ";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "我要去那里, 把那些红毛混蛋全部杀死。 我只希望塞莱娜还活着。 如你所见, 我买了一支滑膛枪 —而且我知道怎么用。 为此花了很多钱, 但我不在乎\n如果你能陪我一起, 我的任务会容易得多。 如果你能在我装弹时掩护我, 我们可以毫不费力地解决那些野蛮人。 你愿意和我一起去救我女儿吗? ";
			link.l1 = "当然! 这是荣誉问题! 我不能让一个女孩死在野蛮人的刀下。 ";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "嗯。 你知道, 我觉得指挥官的话有道理。 也许我们还是应该先听从他的建议? ";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "先生, 你的刀呢? ";
			link.l1 = "我好像放错地方了。 ";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "那可不行。 我会等到晚上, 建议你去求总督帮忙。 ";
			link.l1 = "求他帮忙, 嗯? 好吧, 如你所愿... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "那么, 先生? 你弄到武器了吗? ";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "还没有, 请再等一会儿... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "弄到了。 我准备好帮你了! ";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "我的上帝, 你在逃跑吗? 不! 滚出去! 懦夫! ";
			link.l1 = "嘿嘿, 冷静点, 你这个傻瓜! 我最好去圣皮埃尔的街上看看有没有贵族需要帮助。 ";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//跑来一个带有"应召女孩"任务的贵族
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "很高兴这个镇上至少还有一个勇敢的人。 给, 拿着这三瓶。 这些是强身健体的草药, 我从我们的草药师那里买的。 在战斗中对你会有很大帮助。 ";
			link.l1 = "你呢? ";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "别担心, 我还有更多。 你准备好了吗? ";
			link.l1 = "是的, 别浪费时间了。 前进! ";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//堡垒
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//丛林
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//丛林
		break;
		
		case "Prosper_11":
			dialog.text = "我们快到了, "+pchar.name+"。 转过这个弯就是洞穴的入口。 靠近点, 我告诉你我们的计划。 ";
			link.l1 = "我听着呢, 普罗斯珀。 ";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "我需要用这把沉重的火绳枪稳定瞄准, 但如果你能给我争取时间, 我不会失手。 如果我必须进行肉搏战, 就别指望火力支援了, 我只能用枪管当棍子防身。 这场战斗将取决于你的剑术。 ";
			link.l1 = "你想说什么? ";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "你只需要分散他们的注意力, 让我把他们都射死。 我不能边移动边射击, 所以我会待在一个位置。 洞穴入口附近有三个混蛋。 你应该手持刀剑尽快冲向他们\n攻击其中一个, 让他们追你。 把他们引开。 如果三个人都专注于你, 我可以在你格挡和躲避时像打鸟一样把他们射倒。 但如果那些野蛮人扑向我, 我们就完了。 你准备好了吗? ";
			link.l1 = "这不是我第一次用剑了, 这些野蛮人不足为惧。 ";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "哈! 别担心我。 就像在勒芒打猎一样! 只是别误伤到我! ";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "你先走, 我在你后面。 记住: 你不能让他们靠近我! ";
			link.l1 = "我记住了, 我们走。 前进! ";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// < —legendary edition
			dialog.text = "那就准备行动。 你先走, 我在你后面。 记住: 你不能让他们靠近我! ";
			link.l1 = "我记住了。 我会尽力的。 前进! ";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("前方有一场艰苦的战斗。 (F6) 快速保存。 ");
		break;
		
		case "Prosper_16":
			dialog.text = "干得好, "+pchar.name+"! 这些异教野蛮人再也不能杀人了。 现在是主要事件 —洞穴。 我相信里面有三四个, 但我不确定。 现在听着\n十年前我去过那里。 洞穴里有一条狭窄的隧道。 它通向一个小石窟, 中间有一堵墙, 墙上有个洞。 我们重复之前的计划。 我站在入口附近不动, 你冲进去\n激怒他们, 不要试图同时和所有人战斗, 只要阻止他们攻击我。 在我提到的隧道里占据位置, 那里很窄, 所以一次只能有一两个人和你战斗\n我会从你肩上向他们射击。 准备好了吗? ";
			link.l1 = "前进! 让我们端掉这个野蛮人巢穴! ";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "我女儿还活着! 感谢上帝! 我们及时赶到了, "+pchar.name+"。 我欠你一个人情, 先生。 你是个勇敢的人, 也是个好战士! ";
			link.l1 = "我很高兴有个圆满的结局, 普罗斯珀。 消灭所有那些印第安人可真是血腥的工作。 ";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "再次向你表示最深的感谢, "+pchar.name+"! 现在我们回镇上吧。 我女儿的生命是无价的, 无法用金钱衡量, 但我想用我剩下的积蓄来感谢你。 我们一到圣皮埃尔, 我就很高兴地把它们给你。 甚至别想拒绝! ";
			link.l1 = "我不会拒绝的, 普罗斯珀。 尽管帮助你不是为了钱。 ";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "你是真正的基督骑士, "+pchar.name+"! 现在我们别在这里闲逛了。 让我们尽快回家吧! ";
			link.l1 = "... ";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("回到镇上... ", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "我们到了, 查尔斯。 我再次感谢你的帮助, 并将这适中的比索和金达布隆与我的话联系起来。 我建议你不要浪费达布隆, 留着用于特殊场合。 我知道, 对于你为我提供的服务来说, 这钱不算多, 但这是我的心意。 也拿着这个护身符, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "谢谢你! 再见, 普罗斯珀, 祝你和你亲爱的女儿幸福! ";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//堡垒
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//丛林
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//丛林
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("你收到了15枚达布隆");
			Log_Info("你收到了一个护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "啊, 像你这样的丈夫会对她很好。 她所做的只是被一群瘦腿。 无下巴的花花公子在镇上追来追去。 真可惜, 他们都消失了... 真是太好了。 祝你好运, 查尔斯! ";
			link.l1 = "... ";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//权威
			AddCharacterExpToSkill(pchar, "Fortune", 70);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 70);//隐蔽
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, 法国迷你任务 (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra 需要用于任务 "与印第安人相识"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "啊! 上帝保佑我! (哭泣) 你... 你甚至无法想象这里发生的恐怖! 这些... 这些印第安人把我们拖到这里来杀了我们吃掉! 塞萨尔.布兰切特曾经在这里... 野蛮人带走了他... 他们进行了一些可怕的魔鬼仪式, 然后... 主啊, 我甚至说不出口! 我应该是下一个! 他们打算明天杀了我... ";
			link.l1 = "冷静点, 塞莱娜。 一切都结束了。 那些混蛋得到了应有的下场, 他们再也不会伤害任何人了。 ";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "吉尔伯特.库西也在这里。 在那边... 他, 嗯... 他还没恢复过来。 和他谈谈... 然后我们赶紧离开这里! ";
			link.l1 = "好了, 好了。 没事了, 孩子。 别哭了。 一切都好。 你有一个很棒的父亲。 他不会让任何人伤害你... 出去吧, 我会帮... 嗯... 吉尔伯特出去, 稍后我会赶上你。 ";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "上帝和圣母听到了我的祈祷! 你是来救我们的吗? ";
			link.l1 = "你... 你叫塞莱娜, 对吗? ";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "是的... (哭泣) 你... 你甚至无法想象这里发生的恐怖! 这些... 这些印第安人把我们拖到这里来杀了我们吃掉! 塞萨尔.布兰切特曾经在这里... 他们带走了他... 他们进行了一些魔鬼仪式, 然后... 主啊, 我甚至说不出口! 我应该是下一个! 他们打算明天杀了我... ";
			link.l1 = "冷静点, 小女孩... 很抱歉, 但我给你带来了坏消息。 我是和你父亲一起来的。 我们为了救你而战斗时, 他在外面被那些红皮肤的野蛮人杀死了。 他牺牲了自己的生命来救你。 ";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "什么? ! 我父亲... 哦, 上帝! 我... 我... (呜咽) ";
			link.l1 = "节哀顺变, 塞莱娜。 还有一个人和你在一起, 对吗? ";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = " (含泪) 是的... 吉尔伯特.库西。 他在那里... 他还没恢复过来。 去和他谈谈... 然后我们赶紧离开这里! ";
			link.l1 = "是的, 当然。 我们不能在这里浪费一分钟。 ";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "我父亲... 我可怜的。 亲爱的父亲! 啊, 先生, 我甚至还没感谢你救了我... ";
			link.l1 = "塞莱娜, 我很高兴你和吉尔伯特活着走出了那个洞穴。 你父亲的英勇牺牲没有白费。 ";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = " (哭泣) 求你了, 先生, 带我们回镇上吧。 我们得派人去叫士兵来收我父亲的尸体, 这样他才能得到 proper 的基督教葬礼... ";
			link.l1 = "当然, 塞莱娜。 跟我来! ";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "谢谢你, 先生, 谢谢你陪我可怜的父亲... 谢谢你把我从死亡边缘救了出来。 我... 我... 拿着这袋达布隆。 我在家里父亲的箱子里找到的。 请不要拒绝! ";
			link.l1 = "谢谢你, 塞莱娜。 我很高兴我们成功救了你。 对你父亲的去世, 我表示诚挚的哀悼。 ";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "你是个高尚的人, 先生。 我永远不会忘记你。 再见! ";
			link.l1 = "再见, 塞莱娜。 ";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//权威
			AddCharacterExpToSkill(pchar, "Fortune", 50);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 50);//隐蔽
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra 需要用于任务 "与印第安人相识"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "哦, 主啊, 真的都结束了吗? 我甚至不敢相信... 你救了我和塞莱娜。 如果不是你, 明天塞莱娜就会和不幸的塞萨尔一样遭遇, 再过几天就轮到我了。 ";
			link.l1 = "这些印第安人, 他们真的是食人族吗? ! ";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "你怀疑吗? 如果你胃口好, 看看他们烹饪火的灰烬。 你会在那里找到可怜的老塞萨尔。 现在他只是一些被咬过的骨头... ";
			link.l1 = "神圣的圣礼... 不, 我还是算了。 我刚从欧洲来到这里, 甚至无法想象地球上还会发生如此卑鄙邪恶的事情。 ";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "加勒比海发生了很多奇怪的事情, 那些在旧世界只听到传闻的事情... 印第安巫医。 魔法。 萨满和秘密仪式。 在这里待久了, 你会看到各种各样的魔鬼行为。 但请原谅我, 我还没感谢你救了我 —我还在震惊中\n你救了我的命, 我不仅要口头表达感谢, 还要用金子。 护送塞莱娜和我到城里。 在那里, 我会以你应得的方式感谢你, 先生。 ";
			link.l1 = "好的。 出去吧。 我先在这里看看。 ";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "请允许我再次向你表达我对你救了我的深切感谢, 先生! 正如承诺的那样, 我在口头感谢之外, 还以银币和金达布隆的形式表达物质上的感谢。 ";
			link.l1 = "我很高兴一切都有最好的结果, 吉尔伯特。 ";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("你收到了20枚达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "你无法想象我对此有多高兴! 再次感谢你, 请允许我告辞, 先生。 ";
			link.l1 = "祝你好运, 吉尔伯特! 顺便问一下, 你知道圣皮埃尔还有谁需要帮助吗? ";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "我不知道, 但是... 你可以问问街上的市民, 先生。 普通市民, 甚至富裕的人也不太可能提供任何有价值的东西, 但富有的贵族... 他们可能有一些工作给你。 ";
			link.l1 = "明白了, 吉尔伯特, 谢谢。 再见! ";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//跑来一个带有"应召女孩"任务的贵族
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//对citizen类型角色展示武器的注意事项
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的守法公民。 我必须请你不要像强盗一样露着刀走来走去。 ", "先生, 请注意, 法律明确规定, 男人不得在城墙内携带武器。 ");
			link.l1 = LinkRandPhrase("好的。 ", "很好。 ", "如你所愿... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "它增加耐力并给予第二次机会。 ";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "它增强对战斗伤口的恢复能力。 ";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "它提高你武器的攻击强度。 ";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "它使火器更具杀伤力。 ";
		break;
	}
}