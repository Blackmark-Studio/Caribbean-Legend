// 关于"嗜虐的代价"任务的对话
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "船长! 听说你出海了! 发生了什么? 有什么发现吗? 请告诉我, 快说! ";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//拿了钱
					link.l1 = "不, 我的美人, 这次突袭是应总督大人的要求进行的。 非常抱歉, 安杰洛死在堡垒的地牢里 —现在这一点毫无疑问。 坚强点! ";
					link.l1.go = "Waitress";
				}
				else
				{//杀了胡安
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "你是对的。 你弟弟被绑架了。 司令官一直像卖牲口一样把囚犯卖给一个绰号叫'嗜虐'的奴隶贩子。 但我追上了他的船, 现在他沉在海底了, 你弟弟安杰洛很快就会上岸。 不幸的是, 我没有足够的长艇让所有乘客同时上岸。 ";
						link.l1.go = "Waitress_2";
					}
					else
					{//放了胡安
						link.l1 = "你是对的。 你弟弟被绑架了。 司令官一直像卖牲口一样把囚犯卖给一个绰号叫'嗜虐'的奴隶贩子。 但我追上了他的船, 虽然没能杀死那个混蛋, 但你弟弟安杰洛很快就会上岸。 不幸的是, 我没有足够的长艇让所有乘客同时上岸。 ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "船长, 你查到安杰洛的下落了吗? ";
				link.l1 = "还没有。 但我想很快就会有消息。 你只需要等待。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // 樵夫 如果主角喝醉了..混蛋:D:D:D
			dialog.text = "先生, 你答应过要找我弟弟... 为什么还在这里喝酒浪费时间? ";
			link.l1 = "哦..对..嗝... 放松点姑娘... 耶稣在掌控一切..'咕嘟'... 耶稣在掌控。 我已经走了... 嗝..";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "下午好, 先生。 你有什么事? ";
			link.l1 = "我给司令官先生带来了一份急件, 但我必须亲自交给他。 ";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "那你去堡垒找他吧。 ";
			link.l1 = "这份急件太重要了, 不能让士兵听到看到。 也许我来得太早了, 但我可以在这里等他。 相信我, 这非常重要! ";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("技能检定失败 (40)", SKILL_SNEAK);
				dialog.text = "司令官先生通常会告诉我所有需要改变日常安排的重要事情... 你知道, 实际上, 他确实提到过这种情况。 ";
				link.l1 = "他怎么说? ";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("技能检定成功", SKILL_SNEAK);
				dialog.text = "好吧, 我相信你。 等司令官先生来确认你的话时, 我会更相信你。 但在此之前, 我会一直盯着你。 ";
				link.l1 = "你想怎么盯着我都行... ";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "他告诉我在这种情况下要叫驻军卫兵。 但我们可能自己就能处理。 孩子们! 让我们收拾他! ";
			link.l1 = "该死! ";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "你还想要什么? 决定把消息给我了吗? ";
			link.l1 = "不, 我会等司令官... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//试图偷箱子
		case "Man_FackYou":
			dialog.text = "你是个小偷! 或者, 也许是个间谍? 伙计们, 快下楼! ";
			link.l1 = "呸, 魔鬼! ";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "打扰一下, 我能和你谈谈吗? ";
			link.l1 = "说实话, 我很匆忙。 你想要什么? ";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "我无意中听到你在打听一个叫胡安的人和我们监狱里的疾病... ";
			link.l1 = "确实如此... 你能解释一下吗? ";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "别激动, 别激动! 冷静点, 别碰你的剑! 我们是一边的! 我不知道你为什么关心我们的问题, 但这必须停止! 我再也不能保持沉默了! ";
			link.l1 = "保持沉默? 关于什么? 你对'嗜虐'了解多少? ";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "我知道很多, 即使不是全部, 我会解释的 - 但不是在这里。 我们晚上熄灯后见面, 我是医疗助理, 所以被允许离开堡垒。 我们在城门外见面, 我会告诉你一切。 我求你 - 停止提问, 在你引起他们注意之前, 如果你还没有的话... 我现在得走了。 记住, 晚上在城门外。 ";
			link.l1 = "好吧, 我会去的。 嘿! 等等... ";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //关闭遭遇战
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//禁止生成军官
		break;
		
		case "Sergio_5":
			dialog.text = "感谢上帝, 你来了... 希望你没有被跟踪? ";
			link.l1 = "为什么? 你太多疑了, 也许比司令官还多疑, 所以你最好直奔主题... 你对胡安了解多少? ";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "我叫塞尔吉奥.萨尔do。 我在我们的堡垒里担任医疗助理, 并且... ";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "等等! 你听到了吗? ";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "什么? ! 哪里? ";
			link.l1 = "该死, 这里不止我们! 你带了谁来, 混蛋? ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "他们发现我们了! 你抓住医生, 我抓住另一个! ";
			link.l1 = "... ";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "收起你的剑, 结束了! 你已经看到他们也想杀我! ";
			link.l1 = "好吧, 这似乎不像是一场肮脏的把戏 - 所以, 你不是和他们一伙的。 我们刚才说到哪里了? 你是监狱医生, 对吗? ";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "是的。 我是监狱医生。 我年轻时学过医学, 这里受过教育的人不多。 这就是为什么我比任何人都清楚监狱里发生了什么! ";
			link.l1 = "那发生了什么? 囚犯呢? 你知道他们突然消失的事吗? ";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "我们的司令官在卖他们... 像卖牲口一样卖给一个叫胡安的奴隶贩子。 他挑选那些不会被寻找的人 - 穷光蛋, 随机船只的水手。 然后他们突然'死于嗜虐'- 剩下的你可以想象... ";
			link.l1 = "原来胡安是个人! 你对他了解多少? ";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "知道一点。 他过去和柏柏尔海盗在摩洛哥做生意, 他来拜访我们时喜欢讲那些时候的故事。 他就是在那里得到了'嗜虐'这个绰号 - 不想去想它的由来\n他每个月都来这里, 把所有囚犯带上船。 ";
			link.l1 = "'嗜虐'! 他们还指责我愤世嫉俗! 所以... 你们那个司令官真是个混蛋! ";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "据我所知, 你需要找一个失踪的囚犯, 否则你怎么会知道这个故事, 对吗? 如果是这样, 你得赶紧: 今晚是这个月的最后一晚。 我已经签了文件, 又有三个人'死亡', 胡安明天中午收到他们后就会起锚! ";
			link.l1 = "你签了什么? 我不太明白... ";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "我不得不这么做 - 几个月来我一直这样做! 这就是为什么我来这里阻止这一切。 你知道皮内罗医生是怎么死的吗? 在我之前治疗囚犯的那个? ";
			link.l1 = "我想有人告诉我他死于嗜虐, 不是吗? 所以, 你是被迫的。 这很合理 - 但为什么没有人向当局反映这件事? ";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "谁会相信呢? 我没有任何证据, 而且那些应该看守囚犯的士兵被慷慨地收买了, 所以即使把人卖给加勒比人当食物, 他们也不会在意\n没有人在乎囚犯, 这是司令官的王牌。 但你可以通过除掉胡安来阻止这一切, 至少暂时阻止! ";
			link.l1 = "据我所知, 岸上的那些人是他的手下, 对吗? 我怎么找到他? ";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "你的问题可能已经引起了某人的注意... 我告诉过你要更小心! 但现在这不重要了。 我对胡安的船一无所知, 但囚犯总是被送到加拉拉角, 在岛的北部。 我想奴隶贩子的船应该在附近, 你可能会追上他。 他的信使今天提到他明天中午要起航。 ";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "谢谢你, 塞尔吉奥, 你是一个真正的军官和正直的人。 我现在就起锚, 我会找到这艘肮脏的船。 你需要在他们开始找你之前回到堡垒。 ";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "好吧, 这就是我需要知道的。 如果我不想在整个新世界寻找'嗜虐', 我现在就得起锚。 同时你可以研究一下这个。 ";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "祝你好运, 船长! 别担心我 - 最重要的是至少暂时阻止这一切。 祝你好运! ";
			link.l1 = "我的大炮是治疗疾病和恶意的最佳良药。 我发誓所有囚犯会在黎明前上岸 - 胡安的船将沉在海底! ";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("你给了信件");
			PlaySound("interface\important_item.wav");
			dialog.text = "这是什么? 这里有上校的名字和一个'J'的花押字? 难以置信! 你从哪里弄来的? ";
			link.l1 = "你最好不知道, 但我想你会以最好的方式使用它。 ";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "我会的, 我以所有神圣的名义发誓! 上校将在月底前走上绞刑架! 我会亲自处理! ";
			link.l1 = "恐怕最终只会受到纪律处分, 据我所知, 这不会是他生命中的第一次。 也许, 最好开枪打死那个杂种? 这是一种非常有效的补救措施... 我现在得走了 - 不想让'嗜虐'久等。 ";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// 塞尔吉奥现在是我们的朋友, 将进行树脂交易
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // 计时器
		break;
		
		// 树脂交易生成器
		case "Sergio_20":
			dialog.text = "哦, 真是幸运的相遇! " +GetFullName(pchar)+ "先生! 很高兴见到你! ";
			link.l1 = "塞尔吉奥先生! 没想到会遇见你! 你好吗? 老司令官怎么样了? ";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "我很好, 司令官先生去了洛斯-特克斯矿场 - 他和胡安.嗜虐的肮脏勾当已经被揭露了。 ";
			link.l1 = "矿场? ! 天哪! 我从没想过他的案子会得到正义... ";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "啊, 要是那样就好了, 船长... 他只是被调职和降职了。 他现在在驻军服役, 甚至没有被剥夺军官军衔。 好吧, 至少圣何塞摆脱了这个败类。 ";
			link.l1 = "好吧, 到目前为止还不错。 不过我期望更多。 ";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "我也是... 但让我们忘记那个败类 - 他不值得谈论。 先生, 一听说你的船要进港, 我就急忙赶到码头。 我有个交易给你。 ";
			link.l1 = "真的吗? 我洗耳恭听。 ";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			dialog.text = "船长, 你看起来是个可以信任的人。 另一个非常重要的事情是你是"+GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"")+"人, 有自己的船。 我建议我们达成一项贸易协议。 ";
			link.l1 = "听起来很有希望! 什么样的协议? ";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "我们最好在另一个地方讨论 - 在灯塔的看守人小屋。 他是我的老朋友, 我信任他。 今天或明天来圣何塞的灯塔。 我会在那里等你。 我相信你会发现我的提议非常有趣! ";
			link.l1 = "好的, 塞尔吉奥先生。 我会去那里! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//关闭地点
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //取消中断
			dialog.text = "再次欢迎你, 先生。 让我向你解释这件事。 ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "正如你可能已经知道的, 我不仅是一名士兵, 还是一名医生。 为什么? 因为我是一个受过良好教育的人。 我的教育阻止了我在这里把时间浪费在女人和酒上。 相反, 我组织了几次探险, 设法在离这里不远的地方找到了一个树脂矿床\n这是一种战略资源, 这个岛是唯一能找到用于建造坚固耐用船只的特殊树脂的地方\n总督和司令官命令我把所有树脂卖给西班牙海军\n问题是, 他们只付给我市场价格的一半, 而我不能在其他地方出售。 因此, 我提议你从我这里购买。 这是非常重要的商品, 而且很难获得。 ";
			link.l1 = "我们的协议条件是什么? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "根据我的计算, 我每月可以收集60桶而不引起怀疑。 我们做个交易 - 每月的第五天, 我会来这座灯塔和我的朋友喝一杯。 如果你想买树脂, 就来加入我们。 每桶十个金杜布隆\n你支付整批货款, 一次全部拿走。 没有压力, 由你决定。 那么, 成交? ";
			link.l1 = "听起来是个该死的好交易! 当然, 成交! ";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "太好了。 那么每月的第五天, 我会和我的老朋友看守人喝一瓶加那利葡萄酒, 我们会等你。 ";
			link.l1 = "好的。 就这么办。 ";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "很高兴我们达成了协议。 再见, 船长! ";
			link.l1 = "祝你树脂生意好运, 先生! ";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "你好, 船长先生! 我想你是来买一批树脂的。 ";
			link.l1 = "没错, 塞尔吉奥先生。 都准备好了吗? ";
			link.l1.go = "oil_trade_1";
			link.l2 = "塞尔吉奥先生, 我没心情交易。 也许以后吧。 ";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "是的。 你带了2550杜布隆吗? ";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "当然。 给你。 ";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "真倒霉! 我把钱忘在船上了。 我马上拿来! ";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "是的。 你带了六百杜布隆吗? ";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "当然。 给你。 ";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "真倒霉! 我把钱忘在船上了。 我马上拿来! ";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // 增加树脂供应量
			{
				link.l4 = "塞尔吉奥先生, 我想买更多树脂。 你能提供五倍大的批次吗? ";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // 增加树脂供应量, 如果第一次没带来
			{
				link.l4 = "给, 正如我承诺的, 塞尔吉奥先生, 三千杜布隆, 如你所愿。 我相信凭借你的远见和我的投资, 这个项目将给我们双方带来可观的利润。 ";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//关闭地点
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "很高兴与你交易, 船长。 我的人会帮你把桶装上船。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "交易仍然有效。 如果你需要另一批, 一个月后再来。 ";
			link.l1 = "好的, 塞尔吉奥。 再见。 ";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // 购买计数器
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "先生"+GetSexPhrase("","ita")+", 你购买更多树脂的愿望无疑表明了你对我们业务的信任。 然而, 有一个复杂性\n随着数量的增加, 吸引岛上当局注意的风险也会增加, 控制这样的运输需要人员和安全措施, 我承认, 这并不便宜。 如果你愿意在价格上增加三千杜布隆, 作为一次性付款, 我会雇佣可靠的人来保护货物并防止信息泄露。 然后我们的路线将变得更安全, 我可以每月为你提供三百桶树脂。 为了补偿你的投资, 作为批发买家, 我会为你提供所有未来 shipments 的百分之十五的折扣。 ";
				link.l1 = "三千杜布隆来保障运输? 塞尔吉奥先生, 我不隐瞒, 这个价格似乎令人难以置信 - 好像你在提议埃斯科里亚尔的阴谋, 而不仅仅是保障树脂货物! ";
				link.l1.go = "UpgradeOil_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "先生"+GetSexPhrase("","ita")+", 我感谢你的兴趣, 但这样的大交易需要经验和谨慎。 老实说, 你在交易事务上的水平还不足以处理这么大的 volume。 我建议你多获得一点经验, 等你准备好接受更大的 shipments 时再回来找我。 然后, 也许我们会彻底讨论这个问题。 ";
				link.l1 = "很好。 我们以后再谈这个问题。 ";
				link.l1.go = "oil_trade_exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "先生"+GetSexPhrase("","ita")+", 我理解你的担忧。 但你知道, 安全从来都不便宜, 尤其是对于如此稀有的商品。 此外, 我不仅保证不泄露信息, 还提供折扣, 随着时间的推移会补偿你的投资。 这不是一个合理的妥协吗? ";
			link.l1 = "我承认: 在我们的业务中, 可靠性和保密性是昂贵的, 折扣使我们潜在的交易更具吸引力。 但三千杜布隆仍然是一笔过高的金额。 也许你可以稍微降低一点? ";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "很遗憾, 但在这种情况下, 折中是不可接受的。 要么我们确保全面保护, 要么我们冒一切风险。 金额保持不变, 只有这样我才能保证可靠性和机密性。 你不会希望整个皇家舰队先追我, 然后追你, 对吧? ";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "很好, 萨尔do先生, 你说服了我。 安全和可靠性是物有所值的。 三千杜布隆。 给你。 ";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "萨尔do先生, 你说服了我这些措施的必要性。 然而, 三千杜布隆是一笔巨款, 我现在没有。 我得等到凑够所需的金额。 ";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "这么多钱, 都可以贿赂整个舰队和大陆上的所有士兵了, 更不用说为一批普通的树脂货物雇佣 guards 了! 很抱歉, 我不能同意这样的提议。 让我们保持原样, 没有多余的开支。 ";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "那么, 先生, 我看到我们的信任是相互的。 请放心: 一切都会安排妥当。 现在细节: 300桶树脂, 和往常一样, 每月5日在特立尼达灯塔等你。 你可以用2550杜布隆购买整批货物。 ";
			link.l1 = "太好了, 塞尔吉奥先生。 别让我失望。 ";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "毫无疑问, 先生"+GetSexPhrase("","ita")+"。 一切都将以最高水平组织, 我们的共同努力将取得成果。 ";
			link.l1 = "再见。 ";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "等你有了全额再来。 我会很高兴与你达成新的交易。 ";
			link.l1 = "好的。 ";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// < —树脂生成器
	
		case "Juan_abordage":
			dialog.text = "你到底是谁! ? ";
			link.l1 = "我叫" +GetFullName(pchar)+ ", 至于你, 嗜虐, 魔鬼在等你 - 他很快就会拿到你的灵魂! ";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "这艘船会爆炸 - 火药室里的导火索已经点燃 - 我们为什么都要死? 让我们放下剑。 你有足够的时间出去, 我会跳下船, 加拉拉角离这里很近。 如果你需要金子, 拿去吧! 五百杜布隆, 现金 - 你忘了我, 我忘了你! 成交? ";
				link.l1 = "金子? 我开始这一切不是为了钱, 胡安, 而是为了杀死败类, 而你就是最大的奖励。 ";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "五百杜布隆? 你在嘲笑我, 嗜虐。 我想你在这里至少藏了两倍... 现在给我一千, 你可以下地狱, 否则... ";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "船要爆炸了, 所以我会有个好伴, 你觉得呢? ";
				link.l1 = "你说得太多了, 嗜虐, 开始干活吧! ";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "我们本可以达成协议的... 唉, 不管了! ";
			link.l1 = "你从牢房里带走这些可怜的人, 他们既无法抵抗也无法逃跑。 你是个懦夫, 嗜虐, 现在你将像懦夫一样死去。 ";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "你很有商业头脑, 朋友... 给 - 这是我所有的。 不过, 对于一条命来说, 不算多, 不是吗? ";
			link.l1 = "你的命连一颗子弹都不值, 所以这似乎是我一生中最划算的交易。 现在滚吧。 ";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("你收到了1000杜布隆");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //对话属性
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "可惜你没有时间拯救所有人并杀死我, 是吗? 导火索在燃烧, 时间在流逝... ";
			link.l1 = "该死! 我得把人救出去... 滚吧, 败类 - 你迟早会得到应有的惩罚! ";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "我还是要试试... ";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "安杰洛";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //对话属性
		break;
		
		case "Waitress":
			dialog.text = "啊... 我说不出话来... 真是噩梦! ";
			link.l1 = "唉, 我无能为力。 对不起, 姑娘。 再见。 ";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "难以置信! 你... 你真的救了他? 我不知道如何感谢你。 ";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "我能想象, 美人。 但我这边的交易现在完成了 - 只剩下一件小事。 ";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "职责所在 - 我行动了。 就这样。 ";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "我... 哦, 上帝! 你说得对。 为了他, 正如我承诺的... 上楼去房间 - 我们时间不多了。 ";
			link.l1 = "那我们快点! ";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://自然的感谢
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //关闭酒馆
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //打开房间
			bDisableFastReload = true;//关闭传送
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "我在这里, 我勇敢的骑士! 看看我带来了什么。 ";
			link.l1 = "嗯嗯, 印象深刻, 让我们打开那瓶樱桃酒! 然后我们再打开别的... 毕竟这是你的幸运日... 哈哈哈! ";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "你是真正的骑士! 绅士! 给 - 别觉得受辱, 但我希望你收下。 我攒了这笔钱来赎安杰洛, 但现在这不重要了! 请不要拒绝 - 收下吧! ";
				link.l1 = "好吧, 我会记住你的眼睛, 小姐 - 它们在幸福的泪水中比在痛苦中更美丽。 我接受你的礼物。 再见, 祝你和安杰洛好运。 ";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "你是真正的骑士! 绅士! 我会告诉所有人! 我会永远记住你! ";
				link.l1 = "好吧, 我会记住你的眼睛, 小姐 - 它们在幸福的泪水中比在痛苦中更美丽。 愿你永远快乐。 再见! ";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}