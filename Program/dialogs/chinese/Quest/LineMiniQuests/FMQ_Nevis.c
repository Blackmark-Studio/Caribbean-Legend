// Addon-2016 Jason, 法国迷你任务 (FMK) 圣克里斯托弗
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
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", 船长。 (敬礼) 请允许我介绍自己 - "+GetFullName(npchar)+"中尉, 安提瓜海上步兵团, 驻扎在圣约翰。 我想请你帮个忙。 ";
			link.l1 = "你好, 格雷顿中尉。 我叫"+GetFullName(pchar)+"。 什么样的忙? ";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "让我简要解释一下情况。 我和四名手下从圣约翰航行到圣马丁时, 一场风暴袭击了我们的船。 恶劣天气持续时间不长, 但足以让我们的旧船出现漏水。 我们不得不改变航线, 在这里停靠修理。 这占用了我们本就不多的时间\n我们急于到达圣马丁, 具体来说是大凯斯海滩。 帮我这个忙, 船长, 我会给你丰厚的报酬! 两天的航程, 报酬优厚! ";
			link.l1 = "如果您想让我秘密将英国海军陆战队员送抵荷兰岛屿, 中尉, 这报酬确实应该很丰厚。 ";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = "先生, 这不该让您操心。 您没有危险。 您只需把我们送到海湾就好。 怎么样,成交?";
			link.l1 = "好吧, 我加入。 离这里不远。 让我听听报酬是多少。 ";
			link.l1.go = "seafox_3";
			link.l2 = "对不起, 但我在另一个方向有紧急事务, 而且我不想惹恼荷兰人。 ";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "如你所说, 船长。 那我继续寻找吧。 再见, 祝你好运! ";
			link.l1 = "再见, 中尉。 ";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("你收到了一袋达布隆金币");
			dialog.text = "一万八里亚尔。 这是预付款。 ";
			link.l1 = "很好。 让你的人上船, 我们不要浪费时间。 ";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "是, 是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // 英国人上船
			sld.location = "None";
			AddPassenger(pchar, sld, false);//添加乘客
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "感谢你平稳的航行, 船长! 非常抱歉, 但我现在无法支付你... 我们本应在这个区域有一艘纵帆船, 但她不在这里。 如你所见。 我必须再请你帮一次忙。 你能在这个海湾等待两三天吗? 我们必须去四处看看。 一旦我们回来, 把我们送到安提瓜。 福克斯上校会慷慨地奖励你。 ";
			link.l1 = "嗯……这好像和我们之前说好的不太一样……";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "请不要沮丧, 船长。 我知道你的感受, 但唉: 我完全没有钱。 我可以向你保证, 你将获得两次航行的补偿, 以及在这里等待我们的补偿。 还有福克斯上校本人的感谢! ";
			link.l1 = "我不能把你晾在一边... 很好, 格雷顿中尉。 我会等待三天, 但不能再久了。 ";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "谢谢你, 先生! 我们正在向内陆前进。 我发誓我们会在72小时内回来, 一分钟也不会多。 ";
			link.l1 = "祝你好运, 中尉。 别被抓住。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "真是巧会! 我以为你会在大凯斯海滩等我们, 德莫尔船长! ";
			link.l1 = "你好, 中尉, 我也很惊讶。 没想到看到你穿着荷兰士兵的衣服。 ";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "这是我们的伪装... 你为什么在这里, 先生? ";
			link.l1 = "这是个危险的伪装, 伙计。 间谍很可能会被即决处决, 不经审判。 说到处决, 如果你想避免自己被处决, 最好听着。 ";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "我洗耳恭听。 ";
			link.l1 = "你下船后, 我航行到菲利普斯堡, 与当地人交谈。 荷兰人在找你。 他们知道你营救那些被俘的英国高级军官的任务。 ";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "该死的! 他们到底是怎么知道的? ";
			link.l1 = "一个被俘的英国军官。 为了获得自由, 他把知道的关于营救行动的一切都告诉了荷兰人。 整个菲利普斯堡都在等你和你的人试图进入城市。 更糟的是, 一艘荷兰护卫舰正在圣马丁周围海域巡逻。 这是个陷阱, 中尉。 ";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"那个不光彩的恶棍! 我会找出那个叛徒, 在议会面前揭发他! ";
			link.l1 = "那得等一等, 格雷顿先生。 今晚回到大凯斯海滩, 在他们抓住你之前回到我的船上。 ";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "然后抛弃荷兰监狱里的英国绅士? 我宁愿死, 先生。 我不会让福克斯上校失望的。 ";
			link.l1 = "嗯, 你认为荷兰人在抓住你后会让你选择绞刑还是枪决吗? ";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "别以为他们会让你离开这里, 德莫尔船长。 我们都深陷其中。 ";
			link.l1 = "该死的, 你可能是对的。 我们一起锚的那一刻, 那艘护卫舰就会向我们冲过来... ";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "荷兰人可能知道我们要来了, 但他们不知道我们*如何*来。 我们已经准备好了伪装 - 看看这件制服。 很漂亮, 不是吗? 如果我们的计划没有被泄露, 我们就去当地监狱, 出其不意, 杀死里面的所有人。 但他们肯定在那里埋伏了。 所以我们即兴发挥\n船长, 去菲利普斯堡的教堂, 找一个叫菲利普.雅各布森的牧师。 他应该在早上六点到十点在那里。 菲利普是我们的内线之一\n告诉他这个密码:'被俘的水手多久前忏悔的?'。 之后, 告诉他情况, 并以福克斯上校的名义要求他协助。 然后你把他的回答带给我。 简单, 对你没有风险。 ";
			link.l1 = "在荷兰加尔文主义教堂询问忏悔听起来非常危险, 中尉。 牧师会试图以天主教徒的身份绞死我。 好吧, 告诉我这些制服... 你是从荷兰巡逻队那里脱下来的吗? ";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "是的, 先生。 ";
			link.l1 = "他们现在在哪里? ";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "被扣为人质, 在离这个洞穴不远的灌木丛中。 ";
			link.l1 = "明白了。 保护好他们, 我要进城了。 在这里等我, 保持低调 - 荷兰人正在丛林和海上搜寻你。 ";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "我们会像教堂老鼠一样安静, 船长。 请快点! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "你回来了? 船长, 你在这里做什么? 去镇上, 你在吸引对我们藏身之处的注意! ";
			link.l1 = "我从镇上回来。 你们英国人在玩什么把戏? ";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "你什么意思? ";
			link.l1 = "我去了教堂。 大建筑, 又好又朴素, 就像那些荷兰反偶像主义者喜欢的那样。 猜猜怎么着, 中尉? 没有叫菲利普.雅各布森的牧师。 ";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "不可能, 他每天早上都去那里-";
			link.l1 = "闭嘴听我说! 如果你的雅各布森存在的话, 他也不去教堂! 他们从未见过他! 早上没有, 晚上也没有! 该死的! 我为什么要同意这个该死的工作? ! 被一个愚蠢的。 乳臭未干的白痴中尉领导-";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "先生, 我要求为那次侮辱得到补偿。 等我们离开这里后, 我们将按照-的习俗决斗";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "都他妈闭嘴! ... 我刚听到什么声音。 ";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "天哪, 外面有人! 你! 你把荷兰人带回这里了, 恶棍! 叛徒! ";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "很高兴见到你, 先生, 有什么消息? ";
			link.l1 = "我见到了你的人。 今晚他会送一些'调味'葡萄酒到监狱驻军。 他从一个吉普赛人那里得到了一些药水, 不致命, 但他们会睡得像死猪一样。 你需要今晚进去把你被俘的先生们救出来。 顺便说一句, 这次送酒花了我二十五达布隆。 一定要在报告中提到这一点。 ";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "别担心钱的问题。 船长, 我想请你加入我们的行动, 给我们指路到监狱。 你已经去过菲利普斯堡, 所以你比我们更了解这座城市。 不需要和我们一起进监狱, 我们自己做突围工作。 只要把我们送到门口。 ";
			link.l1 = "该死的, 格雷顿先生, 这工作越来越好了。 报酬最好相应增加。 ";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "当然是这样, 船长。 你不会后悔帮助我们的。 你的船在大凯斯海滩吗? ";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "是的。 ";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "没有。 ";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "很好。 那就准备好, 晚上十一点在城门口见我们。 ";
			link.l1 = "在那里见。 ";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "一定要把她移到那里, 因为我们必须通过丛林把我们的人救出来。 由于堡垒的存在, 从港口或辛普森湾航行是不可能的。 做好一切准备, 晚上十一点在城门口见我们。 ";
			link.l1 = "在那里见。 ";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "准备好了吗, 船长? ";
			link.l1 = "是的。 ";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "那我们走吧。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "嘘... 船长! 完成了, 我们赶紧离开这里! ..";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "我不知道我们是怎么做到的, 但我们做到了! 没有你的帮助, 这一切都不可能, 先生。 现在相对容易的部分 - 我们需要活着离开圣马丁, 毫发无损。 我们去大凯斯海滩吧! ";
			link.l1 = "我们走! ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "谢谢您的帮助, 船长! 我请求您在我们殖民地停留一天, 期间我会向福克斯上校汇报。 明天请您前往会见他。 如果您不清楚——福克斯上校的指挥部就在总督府, 往左边走。";
			link.l1 = "很好, 格雷顿中尉。 请让我觉得值得。 由于你的冒险, 我需要很长时间才能修复与荷兰人的声誉。 ";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "感谢你的协助, 船长! 您"+GetSexPhrase("表现得就像个真正的英雄","真是位非常勇敢的姑娘")+", "+GetAddress_Form(NPChar)+"! 格雷顿中尉没能成功, 真是悲剧。 他作为真正的绅士和英国之子去世了。 我想请你在这里再待一天, 让我向福克斯上校汇报。 明天拜访他, 他的办公室在总督府。 ";
			link.l1 = "很好。 请让我觉得值得。 由于你的冒险, 我需要很长时间才能修复与荷兰人的声誉。 ";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "别担心, 先生。 我会在报告中给你最高的评价。 (敬礼) 很高兴认识你, 先生! ";
			link.l1 = "... ";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = ""GetFullName(pchar)+"船长? ";
			link.l1 = "嗯... 是的, 我能为你做什么? ";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "港口办公室已通知我们你船最近抵达。 菲利普斯堡总督马丁.托马斯阁下想见你。 ";
			link.l1 = "为什么? 我被捕了吗? ";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "哦不, 不, 船长先生, 你没有被捕。 总督已下令邀请每位新到的船长到他的宫殿喝咖啡和介绍。 跟我来! ";
			link.l1 = "听起来是个我无法拒绝的提议。 带路吧。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = "先生, 请告诉我们你在哪里看到这些英国士兵。 ";
			link.l1 = "他们像普通强盗一样藏在丛林里的一个洞穴里。 ";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "带路, 我们跟着你! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "等等, 船长! 你提到你在那里见过间谍 - 靠近洞穴入口? ";
			link.l1 = "是的。 他们和我谈话后, 我短暂地看到他们进去了。 ";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "很可能他们还在里面。 如果我们一起冲进去, 他们会撤退到洞穴里。 从那里把他们挖出来将是一场噩梦... 让我们聪明点。 船长, 你一个人去那里, 分散他们的注意力。 我和我的人会移动到拐角处的那口枯井。 它直接通向洞穴内部。 混蛋们不会看到我们从后面来\n你进去, 如果间谍还在那里, 和他们交谈, 问他们愚蠢的问题, 让他们忙起来。 一旦你引起了他们的绝对注意 - 尽可能肮脏地咒骂。 你是个水手, 这对你来说应该很自然。 那将是我们的信号。 我的两个人会守卫正门, 防止他们从那里逃跑。 我们会抓住他们。 ";
			link.l1 = "你的计划听起来对我的健康非常危险。 在我看来, 他们会先试图杀了我。 ";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "别担心, 船长。 你的目标是一看到敌人突袭队就尽可能大声喊叫。 如果他们攻击你 - 那就跑, 继续喊叫。 我的人训练有素, 所以别担心, 他们会在你受伤之前拿下这些间谍。 ";
			link.l1 = "他们最好如此。 我要进去了。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "他们是 tough bastards... 干得好, 船长, 英国狗被消灭了。 我们的指挥官和总督会很高兴的。 ";
			link.l1 = "你花了不少时间, 先生... ";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "怪绳子, 末端有个桶, 发出绝对的噪音。 我们必须小心。 ";
			link.l1 = "是啊... 绳子。 不管怎样。 你失踪的一支巡逻队被绑在那边的灌木丛里。 他们应该还活着。 ";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "我会去看看他们。 你应该去镇上休息一下。 明天拜访我们的总督, 到时候他会收到我的报告, 里面有对你的高度赞扬。 ";
			link.l1 = "我会的。 祝你好运, 先生。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "我能为你做什么, 我的孩子? ";
			link.l1 = "你好, 牧师, 只是好奇被俘的水手多久前忏悔的? ";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "昨天晚上, 我的孩子... (耳语) 我猜你知道计划被泄露了? ";
			link.l1 = "否则我不会站在这里。 卡斯帕.格拉顿中尉和他的人现在在丛林里。 他们都穿着荷兰士兵的衣服, 但我们需要额外的帮助, 因为监狱警卫在等他们。 ";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(大声) 我每天祈祷拯救他的英国灵魂免于诅咒! (耳语) 我有一个计划, 但我需要二十四枚金达布隆来获得我需要的一切。 ";
			link.l1 = "昂贵的计划。 钱是用来做什么的? ";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "当监狱警卫是无聊的职责。 为了保持士气, 负责的军官每天晚上都会点一些葡萄酒配晚餐。 葡萄酒是从一个我有权限进入的仓库运来的。 镇上有一个欠我债的吉普赛女人, 她会给我们做安眠药。 我需要做的就是买几瓶好酒, 加入药水, 然后在仓库里换瓶。 这就是我需要金子的原因。 ";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "我有达布隆。 拿去吧。 ";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "让我回到我的船上给你拿一些。 ";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "啊, 我的孩子, 你有我们讨论的'捐款'吗? ";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "是的, 给你。 ";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "我很快就会拿到... ";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "太好了。 明天同一时间来看我 - 我会告诉你结果。 ";
			link.l1 = "很好... ";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "问候你, 我的孩子。 ";
			link.l1 = "你也一样, 牧师。 有什么消息吗? ";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "是的。 完成了。 葡萄酒已经'调味', 警卫今晚将得到特别款待。 他们晚上九点吃晚饭, 到午夜都会睡着。 这是你做这项工作的唯一窗口, 没有第二次机会。 小心, 你不能完全依赖你的荷兰伪装。 ";
			link.l1 = "知道了。 我们不要浪费时间。 再见。 ";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}