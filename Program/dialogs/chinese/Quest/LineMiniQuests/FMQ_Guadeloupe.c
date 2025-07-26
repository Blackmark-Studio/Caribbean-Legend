// Addon-2016 Jason, 法国迷你任务 (FMK) 瓜德罗普
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明显的漏洞。 请将此事告知开发人员。 ";
			link.l1 = "好的, 我会的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// 任务发布者
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "你好, 船长! 我有一个你会觉得非常有趣的商业提议。 ";
			link.l1 = "请说, 先生。 ";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "我想雇佣你的船执行从瓜德罗普到西班牙大陆的运输任务。 ";
			link.l1 = "你想作为乘客航行到那里吗? ";
			link.l1.go = "citizen_2";
			link.l2 = "西班牙大陆? 我还是算了吧。 我们和西班牙人并不是真正的朋友。 我建议你另找一个傻瓜。 ";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "如你所说, 船长, 尽管这不是一次高风险的航行。 再见。 ";
			link.l1 = "再见。 ";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "如你所愿, 船长。 再见! ";
			link.l1 = "再见。 ";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "不完全是这样, 先生。 乘客是依赖船长意愿的人。 我想雇佣你。 你的船员和你的船, 以便让我和我的两个朋友到达巴拿马。 ";
			link.l1 = "去巴拿马? 怎么走? 你想绕整个大陆航行吗? ";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "哈哈哈! 好笑话, 船长。 当然不是。 你所要做的就是把我们送到离贝洛港不远的蚊子湾。 我们会自己想办法去巴拿马, 这不会是我们第一次穿越丛林。 ";
			link.l1 = "报酬是多少? ";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "两箱达布隆金币。 三百枚。 我们一上船你就会提前得到一箱。 我们一到达目的地, 第二箱就归你了。 ";
			link.l1 = "这么简单的工作能得到丰厚的报酬。 有什么陷阱吗, 我的朋友? ";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "船长, 时间就是金钱, 我和我的朋友没有时间了。 我们必须今晚从这里起航, 而且必须在十天内到达那里。 这将是我们的第二个任期。 那么, 你加入吗? ";
			link.l1 = "成交! ";
			link.l1.go = "citizen_6";
			link.l2 = "对不起, 先生, 但你的提议在我听来太可疑了。 你另找一个傻瓜吧。 ";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "太好了。 我的朋友们现在在丛林里, 我会告诉他们我们的协议。 今晚十点你会在卡普斯特海滩找到我们。 不要迟到, 船长! ";
			link.l1 = "好的。 卡普斯特海滩, 今晚十点。 ";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "等一下, 船长, 我们甚至还没介绍过自己。 我叫贝特朗.皮内特。 你是... ";
			link.l1 = ""+GetFullName(pchar)+"。 "+GetFullName(pchar)+"船长。 再见, 皮内特先生。 ";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = GetFullName(pchar)+"船长, 你来了。 我们可以走了吗? ";
			link.l1 = "是的。 欢迎登船。 ";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "很好。 接受你的预付款 --一箱满满的达布隆金币。 记住 --你只有十天时间把我们送到目的地。 一天也不能多! ";
			link.l1 = "我记得条款。 别担心, 我们会及时赶到的。 请就座。 ";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("你收到了一箱满满的达布隆金币");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "那么, 船长, 你已经完全履行了你的协议部分。 现在轮到我了。 接受这个箱子以及我们最深的感谢。 ";
			link.l1 = "很高兴与你做生意, 先生。 ";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("你收到了一箱满满的达布隆金币");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//导航
			AddCharacterExpToSkill(pchar, "Leadership", 200);//权威
			AddCharacterExpToSkill(pchar, "Sneak", 100);//隐蔽
			dialog.text = "我也是。 再见, "+GetFullName(pchar)+"船长。 ";
			link.l1 = "再见! ";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// 护林员 - 重新开启武器。 
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "那么, 船长, 我们到了。 你只完成了协议的一半, 所以我也会做同样的事。 把你的预付款当作全额工资吧。 我希望你不会反对, 毕竟这是你的错。 ";
			link.l1 = "不能说我喜欢这样, 但我承认你是对的。 现在我们分道扬镳吧。 ";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//导航
			AddCharacterExpToSkill(pchar, "Leadership", 50);//权威
			AddCharacterExpToSkill(pchar, "Sneak", 50);//隐蔽
			dialog.text = "不管怎样, 谢谢你的服务, "+GetFullName(pchar)+"船长。 再见! ";
			link.l1 = "再见。 ";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "哦! 真是巧会! "+TimeGreeting()+", "+GetFullName(pchar)+"! 但怎么会? ";
			link.l1 = TimeGreeting()+", 皮内特先生。 找到你可不容易。 ";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "原因是什么, 船长? ";
			link.l1 = "我的好先生, 有一个叫"+GetFullName(sld)+"的人, 他非常想见你。 我想你知道为什么。 ";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "我当然知道, 但你, 我亲爱的船长, 也一定知道我一点也不想见"+GetFullName(sld)+"先生。 你是他的赏金猎人吗? 我只是不明白。 ";
			link.l1 = "唉, 但目前我就是这样的人, 我对此并不高兴。 我犯了一个错误, 现在"+GetFullName(sld)+"先生, 该死的他, 给了我一个选择。 要么你光荣地返回瓜德罗普, 要么我作为你释放唐.卡洛斯.德.米利亚尔这一小行动的同谋倒霉。 你知道那会伤害我。 ";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "啊, 那个混蛋! 这是一种非常邪恶的敲诈方式! ... 那么, 船长, 你会怎么选, 你是会做出选择, 还是会让那样的人敲诈你? ";
			link.l1 = "你觉得呢? 我相信你会和我一起去巴斯特尔。 ";
			link.l1.go = "citizen_19";
			link.l2 = "我有选择的余地吗? ";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "哦, 我必须让你失望了, 船长。 我不想登上你漂亮的船。 你在这里使用武力不会有任何结果, 这个地方被卫兵包围着, 如果你表现出任何暴力意图, 我就会呼救。 当然, 你可以尝试刺我, 但我们的好朋友不会从一具冰冷的尸体上得到任何硬币。 所以, 目前你最明智的做法 --就是放过我。 我会允许你安然离开。 ";
			link.l1 = "你真的认为在发生了这一切之后我会就此离开吗? 你把我拖进了这个烂摊子, 混蛋, 是时候付出代价了! ";
			link.l1.go = "citizen_20";
			link.l2 = "我想你是对的。 我喜欢刺你的想法, 但这毫无意义。 甚至不要以为这就结束了。 我现在要去巴斯特尔, 在那里我会让我们的好朋友知道你的下落。 然后他会派蒙面人来追你。 ";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "啊-啊! 士兵们! 救命!! ";
			link.l1 = "... ";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "当然。 告诉你的老板管好他的蒙面人 --我最近很受欢迎。 再见, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "等等! 我投降! 我投降! ";
			link.l1 = "这就对了! 现在放下武器, 走到船上去! ";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "总是有选择的, 船长。 据我所知, 如果没有那个银行家的威胁, 你不会追捕我吧? ";
			link.l1 = "没错。 ";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "很好。 那我会为你安排一个可靠的方法来让他闭嘴。 我们写一封信, 你把它带给你的雇主。 告诉他, 如果他敢开口, 瓜德罗普的总督就会知道那个策划并投资了‘勇气号’失踪事件的人 --那是一艘执行运输大批钻石任务的信使纵帆船。 ";
			link.l1 = "嗯。 我想我开始明白了, 皮内特先生。 ";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "很高兴你这么聪明, 船长。 如果德.利昂知道‘勇气号’失踪的真相, 他会亲自把那个狡猾的吝啬鬼的头钉在城门上。 在我即将写的这封信里, 你会找到让敲诈者冷静下来的证据。 给我一分钟拿笔。 ";
			link.l1 = "好的... ";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(书写中) 给, 拿着。 这个包裹里有两封相似的信。 把一封给银行家, 让他好好看看。 另一封你自己留着, 藏好。 ";
			link.l1 = "这些信息可靠吗? ";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "我可以发誓, 你帮助了我, 现在我会帮助你。 放心吧, 敲诈者一读这封信就会放过你。 啊, 对了... 还有一件事, 船长。 既然我们和平解决了... 我有一个藏匿点, 如果你答应将来不干涉我的生意, 我就告诉你去哪里找。 反正他们也不会让我再踏上瓜德罗普的土地了。 ";
			link.l1 = "如果这封信能达到预期效果, 我当然可以答应你。 ";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "那就成交。 在瓜德罗普的山洞里的岩石中寻找。 就当是对你麻烦的小小补偿吧。 祝你好运, 船长。 ";
			link.l1 = "你也一样, 皮内特先生。 ";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// 给招募者的信使
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "你好, 先生! 你是"+GetFullName(pchar)+"船长, 对吗? ";
			link.l1 = "对的。 我能为你做什么? ";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = GetFullName(pchar)+"先生, 巴斯特尔的银行老板请你尽快去拜访他。 他命令我每天检查我们的港口办公室, 确保不会错过你的到来。 ";
			link.l1 = "有意思, 他为什么这么想见我? ";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = GetFullName(sld)+"先生会亲自告诉你为什么。 我希望你不会拒绝他的邀请。 ";
			link.l1 = "嗯... 好吧。 这些银行家都是有权有势的人, 他们从不把时间浪费在小人物身上。 我会尽快去见他。 ";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "谢谢你, 船长。 再见! ";
			link.l1 = "再见。 ";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//关闭城市出口
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// 让.德诺
		case "Juan":
			dialog.text = "啊! 你这个混蛋! 这绝不是偶然相遇... ";
			link.l1 = "说得对, 让... 请原谅, 我是说胡安。 我一直在追踪你。 现在你能乖乖进我的货舱吗? 消消气, 我们谈谈。 ";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "我已经履行了我的协议部分。 现在轮到你了。 说吧, 记住撒谎的后果。 ";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "你会在巴巴多斯的主要种植园找到贝特朗.皮内特, 具体来说。 他打算在那里继续他的生意。 种植园的 overseer 是他的朋友。 ";
			link.l1 = "什么样的生意? ";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "和他在瓜德罗普的生意一样。 半合法贸易。 走私。 奴隶。 我认为他打算做奴隶生意和蔗糖贸易, 否则他为什么要搬到种植园去? ";
			link.l1 = "我明白了。 他在英国当局中有赞助人吗? ";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "我猜是这样。 他是个很有趣的人。 总是到处都有朋友。 ";
			link.l1 = "还有别的吗? ";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "比如什么? 狡猾又聪明, 总是知道事情, 总是有王牌。 我没有太多时间了解他更多。 ";
			link.l1 = "知道了。 好的, 我得航行到布里奇敦。 你可以走了, 胡安先生。 别想警告皮内特。 如果我在那里找不到他, 你的屁股又要遭殃了。 ";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// 皮内特 - 在布里奇敦
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "对不起, 伙计。 没有个人恩怨。 你知道得太多了, 这是你的问题。 ";
			link.l1 = "... ";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // 版本修正
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}