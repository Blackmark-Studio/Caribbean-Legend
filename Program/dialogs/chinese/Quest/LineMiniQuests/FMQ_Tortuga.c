// Addon-2016 Jason, 法国迷你任务 (FMK) 托尔图加
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
			dialog.text = "明显的程序错误, 请告知开发者。 ";
			link.l1 = "我会的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "哦, 先生您好! 欢迎来到托尔图加! 像您这样高贵的船长在这里可是稀客... ";
			link.l1 = "问候您, 小姐。 感谢您热情的欢迎。 但为何这么说? 我原以为这样重要的港口总会吸引比我高贵得多的幸运绅士们。 ";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "啊, 先生... 您显然是新来的, 对吗? 您会明白的。 您不知道在总督府举办一场舞会, 找到配得上的男伴有多难。 也许您可以陪我... ? ";
			link.l1 = "我该如何为如此美丽的女士效劳? ";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "天哪, 如此殷勤! (咯咯笑) 也许, 您能在今晚六点来拜访我们吗? 总督夫人定期在宫殿仆人区举办非正式聚会。 对我们来说, 这是难得的机会, 能为这类活动找到有趣的伴儿。 您会来拜访吗? 请一定来, 我们会非常高兴。 ";
			link.l1 = "我很荣幸, 小姐。 今晚我会来拜访。 ";
			link.l1.go = "girl_3";
			link.l2 = "原谅我, 小姐, 但我有急事要处理。 也许下次吧? ";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "真遗憾。 我得去找别人来陪伴我和我的女友们了... 再见。 ";
			link.l1 = "再见。 ";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "谢谢! 我向您保证, 这将是您永生难忘的夜晚, 先生! 再见! ";
			link.l1 = "回见... ";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "嘿, 水手! 今天是什么幸运风把你吹到这里的? 在托尔图加很少见到这么英俊的男人。 ";
			link.l1 = "你也好, 小姐, 你的赞美让我脸红了。 我是一艘船的船长, 很忙, 但我相信这个岛能给像我这样的流浪者提供足够的娱乐。 ";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(咯咯笑) 哦是的, 先生, 我相信我们能帮上忙! 托尔图加总是有东西可以提供。 我也是... 为什么, 我听了一个好的海员故事后, 几乎可以做任何事*。 我太喜欢它们了! 有一次一位船长给我讲了一个荒诞的故事, 说他如何用海龟做木筏逃离荒岛。 多么勇敢! 你能吗? ";
			link.l1 = "我能做什么? ";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(咯咯笑) 你能用海龟做木筏吗? ";
			link.l1 = "我能做得更好。 有一次我和一个逃亡的学徒只用一把斧头就俘获了英国海军最快的船。 我还能屏住呼吸十分钟。 想看看吗? ";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "也许以后吧。 我在总督府当仆人。 今晚六点来, 在凉亭里找我和我的朋友。 那时你可以给我们讲讲你的冒险经历... ";
			link.l1 = "听起来是个不容拒绝的展示邀请。 今晚六点见。 ";
			link.l1.go = "girl_9";
			link.l2 = "潜入总督府? 听起来对我来说太奢侈了。 我还是算了, 亲爱的。 如果你想要真正的男人陪伴, 去酒馆找我。 哟吼吼! ";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "呸。 不管怎样, 我会找到比你更好更大的男人。 毕竟你的护裆看起来太小了。 滚吧。 ";
			link.l1 = "即使是战舰在穿过你的向风海峡时也会显得渺小。 ";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "期待见到你! ";
			link.l1 = "... ";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "啊, 你来了! " +GetFullName(pchar)+ "船长! 很高兴见到你, 好久没有如此高贵和有地位的客人来访了! ";
			link.l1 = "能与您共处是我的荣幸, 夫人。 但其他客人呢? 我来得太早了吗? ";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "哦, 他们身体不适, 不能来。 但别想他们了, 我们喝酒聊天吧... 啊, 要是您知道我在这里有多无聊和孤独就好了! 托尔图加是一个肮脏的巢穴, 充满了人渣。 恶棍和海盗! 海盗! 最后, 我家里来了一位值得尊敬的绅士! 我希望我丈夫能多和您这样有阶级和才能的人做生意! 但不, 到处都是海盗, 海盗! 您听说过巴黎国王宫廷里流行的新时尚吗? 您对此有什么看法? ";
			link.l1 = "对不起, 我具体对什么有看法? 海盗? 还是时尚? ";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "哦, 先生, 您太了解我了! 我简直不敢相信。 我丈夫只给我几分钱, 而他从海盗那里赚了数百万, 想象一下! 海盗! 我不得不订购衣服送到这个肮脏的地方, 但当它们到达时已经过时六个月了! 像我这样身份的女人怎么能穿这样的破烂? 哦, 我多么想看看并穿上巴黎的这些时尚! 您认为我穿那些会好看吗? ";
			link.l1 = "夫人, 您看起来非常可爱。 您不需要巴黎的时尚来证明这一点, 这个美丽岛上的每个男人都清楚这一点。 ";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "您对我太好了... 船长, 我必须承认, 我遇到了大麻烦。 但您会帮助一个可怜的女人, 对吗? ";
			link.l1 = "当然, 夫人。 您希望我做什么都可以。 ";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "小心点, 船长先生, 否则我会失去理智的! (风骚的咯咯笑) 我丈夫最近一分钱都不给我。 那个畜生带普通妓女回家, 根本不理我! \n我知道他把一些不义之财藏在哪里, 在他办公室的一个箱子里。 作为妻子和女人, 这是我的钱。 帮我拿到他欠我的东西, 您会得到回报的... 用金子和... 其他令人愉快的东西。 ";
			link.l1 = "这是个有趣的提议。 好吧, 夫人, 我会帮您。 这个箱子在哪里, 我怎么打开它? ";
			link.l1.go = "wife_5";
			link.l2 = "好吧, 夫人, 我会把箱子里的东西给您。 我们拿到钱后, 会有一个非常愉快的'谈话'。 哪个男人能拒绝这样的提议? 这个箱子在哪里, 怎么打开? ";
			link.l2.go = "wife_6";
			link.l3 = "夫人, 您在引诱我。 对不起, 但我的荣誉要求我拒绝您的提议。 我同情您, 您值得更好的, 但您得为您的计划另找演员了。 ";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "真遗憾。 那我们没什么好谈的了, 先生。 离开并记住: 你对我丈夫说一个字, 你会后悔的! ";
			link.l1 = "再见。 ";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // 版本1
			dialog.text = "我没料到您会这样... 箱子... 以后再说, 首先我们必须找到一把被肮脏海盗偷走的备用钥匙。 他现在正在当地的巢穴里狂欢, 像猪一样喝酒。 赶紧把备用钥匙给我带回来。 我会等您。 ";
			link.l1 = "那就别浪费时间了! ";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // 版本2
			dialog.text = "您不会后悔的, 船长。 首先, 我们必须找到一把被肮脏海盗偷走的备用钥匙。 他现在正在当地的巢穴里狂欢, 像猪一样喝酒。 赶紧把备用钥匙给我带回来。 我会等您。 ";
			link.l1 = "那就别浪费时间了! ";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = GetFullName(pchar) + "船长! 天哪! 我私人房间里的男人! 您惊讶吗? 今晚您是唯一的客人。 (咯咯笑) ";
			link.l1 = "我很惊讶, 夫人。 但我一点也不介意。 这是关于生意还是娱乐? ";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "多么直接的方式! 我喜欢您这样的男人。 我有一个商业提议给您, 船长。 如果您成功了, 我会想办法补偿您的努力。 ";
			link.l1 = "请说。 ";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "啊... 我丈夫有一个装满钱和珠宝的箱子。 我恨他, 我想要更多的零用钱来减轻我的痛苦。 ";
			link.l1 = "夫人, 您看起来很可爱。 您不需要更多的珠宝或巴黎的时尚来证明这一点, 伊斯帕尼奥拉岛上的每个男人都清楚这一点。 ";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "您对我太好了... 船长, 我必须承认, 我遇到了大麻烦。 您会帮助一个陷入困境的女人吗? ";
			link.l1 = "当然, 夫人。 荣誉要求我这样做。 您希望我做什么都可以。 ";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "小心点, 船长先生, 否则我会失去理智的! (风骚的咯咯笑) 我丈夫最近一分钱都不给我。 那个畜生带普通妓女回家, 根本不理我! \n我知道他把一些不义之财藏在哪里, 在他办公室的一个箱子里。 作为妻子和女人, 这是我的钱。 帮我拿到他欠我的东西, 您会得到回报的... 用金子和... 其他令人愉快的东西。 ";
			link.l1 = "好的。 我会做的。 这个箱子在哪里, 我怎么打开它? ";
			link.l1.go = "wife_13";
			link.l2 = "哈! 对您这样的女人, 我没有问题。 您不会后悔的, 亲爱的。 我们拿到钱后, 会有一段非常愉快的时光。 这个箱子在哪里, 怎么打开? ";
			link.l2.go = "wife_14";
			link.l3 = "我不, 夫人。 我不是那种在一个晚上既给男人戴绿帽又抢劫他的绅士。 不管怎样, 不是以这种方式。 为您的计划另找演员吧。 ";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // 版本1
			dialog.text = "哦... 我越来越喜欢您了... 首先, 我们应该拿回被一个肮脏海盗偷走的备用钥匙。 他正在当地的巢穴里狂欢, 像猪一样喝酒。 赶紧把备用钥匙给我带回来。 我会等您。 ";
			link.l1 = "那就别浪费时间了! ";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // 版本2
			dialog.text = "保持冷静, 先生, 以后有的是时间。 (咯咯笑) 首先, 我们应该拿回被一个肮脏海盗偷走的备用钥匙。 他正在当地的巢穴里狂欢, 像猪一样喝酒。 赶紧把备用钥匙给我带回来。 我会等您。 您确定能做到吗? ";
			link.l1 = "别怀疑我, 我已经在路上了。 ";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "假正经的混蛋! 滚出我的视线! 别想告诉我丈夫这件事, 否则你会后悔的! ";
			link.l1 = "再见, 甜心。 ";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "船长! 您拿到钥匙了吗? ";
			link.l1 = "是的, 我拿到了。 箱子在哪里? ";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "哦! 我邪恶的丈夫真的要得到应有的惩罚了吗? 您是个不可思议的人, 船长! 您知道吗, 您前途无量? 忘了箱子吧。 我自己来做。 明天来见我拿您的报酬。 您不会后悔的, 船长... ";
			link.l1 = "好的。 如您所愿。 期待明天见到您。 ";
			link.l1.go = "wife_17";
			link.l2 = "不, 我是个忙人, 不想浪费时间等待。 为什么要等? 告诉我该做什么, 我会做的。 我不能让这么漂亮的女人弄脏她的小手去摆弄锁和钥匙。 ";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "六点前来看我, 我勇敢的骑士... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "您确定吗? 这可能对您很危险。 为什么您要冒生命危险, 船长? ";
			link.l1 = "好的。 如您所愿。 期待明天见到您。 ";
			link.l1.go = "wife_17";
			link.l2 = "我已经做了决定。 我到底该做什么? ";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "狮子心! ... 去我丈夫的办公室, 您会在那里找到箱子。 用备用钥匙。 晚上这个时候没人在上面, 所以慢慢来。 箱子里有... 钻石。 大量的钻石。 把它们都拿走, 回到我身边。 我会等您。 请不要背叛我的信任... ";
			link.l1 = "我很快就回来。 ";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // 允许访问箱子
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "哦, 船长! 我... 您... 完成了吗? 哦, 这是谁? ! 啊-啊! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "哦, 天哪! 船长, 您救了我! 您... 您是我的英雄! 那是我丈夫的暴徒, 他想杀了您! 我求他不要! 您受伤了吗? 您带来钻石了吗? ";
			link.l1 = "哈。 真的吗? 您丈夫是个嫉妒的人... 不管怎样。 去他的, 我拿到宝石了。 ";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "哦, 船长! 我... 您... 完成了吗? ";
			link.l1 = "有个小麻烦, 但已经解决了。 为什么您脸色苍白, 夫人? 您还好吗? 我拿到珠宝了, 那应该让您高兴起来, 对吗? ";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "感谢上帝! 我报仇了! 我的骑士! 箱子里有多少钻石? ";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "您的骑士带着满满一袋战利品回来了。 他会把一半留给女士, 这样她就可以从巴黎买到最好的时尚。 我遵守了对您的承诺。 ";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "哦, 有很多钻石, 但您什么也得不到。 您雇了一个刺客来杀我, 你这个婊子! 您真的相信在这之后我会和您分享吗? 公开这件事, 您丈夫会知道您计划抢劫和背叛他。 所以闭嘴。 ";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "无赖! 混蛋! 您不会得逞的! ";
			link.l1 = "是嘛, 我以前听过这话。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("您已赠送钻石");
			PlaySound("interface\important_item.wav");
			dialog.text = "您和... 其他人不一样。 您得到了想要的。 您前途光明。 我知道您是个忙人, 但... 您能和我待一会儿吗? 我保证没人会打扰我们。 ";
			link.l1 = "我总是有时间陪伴像您这样美丽的女人。 要我打开一瓶您丈夫的酒吗? ";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, 用于"导航星"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("您已赠送钻石");
			PlaySound("interface\important_item.wav");
			dialog.text = "我想没有它们我也能活下去。 这里有很多花钱的选择。 托尔图加有很多英俊和有价值的男人... 感谢您所做的一切, 船长。 只是让您知道, 请对这件事保持沉默, 否则我丈夫会看到您被吊死在绞刑架上。 他不是个好人。 再见。 ";
			link.l1 = "就这样? 那是一次有教育意义的经历。 再见, 夫人, 我建议您也对这件事保持沉默, 我也不是好人。 但您已经知道了, 对吗? ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, 用于"导航星"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "你是谁, 在这里做什么? ";
			link.l1 = "你在玩什么把戏? 我们有过交易... ";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "什么交易, 先生? 我是已婚妇女, 我不和其他男人做生意! 现在离开我的房间, 否则我叫我丈夫和他的卫兵! ";
			link.l1 = "就这样, 是吗? 很好, 我想我会让您的好丈夫知道的! ";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "现在离开, 你这个无礼的家伙, 否则我的人会把你扔进拉罗什堡的地牢! 我不在乎你的威胁! 滚出去! ";
			link.l1 = "... ";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, 用于"导航星"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "你是谁? 啊, 不管了。 别相信女人, 伙计。 就像圣经说的... 即使是最愚蠢的妓女也能用她们的操纵把你拖入地狱。 坐下, 伙计, 喝一杯! ";
			link.l1 = "乐意之至! ";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "你在盯着什么? 倒酒!! ";
			link.l1 = "敬你! .. 嘿, 朋友, 我不想在这里浪费时间。 我需要你有的那把备用钥匙, 你知道我在说什么。 把它给我, 我们就分道扬镳: 你继续喝酒, 我继续帮助落难的少女。 ";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "哦, 伙计! 你没听我刚才说的话吗! 你看起来比实际聪明... 为那个婊子工作。 你知道她丈夫是谁吗? 最近, 勒瓦瑟总督派他忠诚的黑人坎帕乔去'拜访'一位当地备受尊敬的商人。 那个黑人在自己的店里把可怜的混蛋打死了! 这位商人在舞会上对总督夫人表现出某种轻微的不尊重。 而这个婊子用她的美貌和他的达布隆诱惑了我\n备用钥匙存在。 我在法国时曾是个不错的保险箱破解者, 所以这是小儿科。 如果不是因为里昂司令官的女儿... 我永远不会当海盗。 呸! 去他的! ";
			link.l1 = "这一切都很悲伤, 但我们谈正事吧。 钥匙在哪里? ";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "你在听吗? 我退出了, 伙计! 我足够聪明, 看到了即将发生的事情! 我的船一准备好起航, 我就永远离开这个地方。 你想要钥匙, 付钱。 别在这里贪婪, 我想你很快就不需要钱了。 ";
			link.l1 = "你知道, 你是对的。 我不想成为女人的玩物。 感谢你的建议, 海上平安! ";
			link.l1.go = "pirate_4";
			link.l2 = "付钱给你? 给你? 你是个可怜的小偷和懦夫。 你应该待在那个狗屎里昂。 谁知道呢, 也许当地司令官会可怜你, 让一个堕落的小偷做他的女婿。 我肯定不会可怜你。 你可以选择轻松的方式或困难的方式把钥匙给我, 选择权在你。 ";
			link.l2.go = "pirate_5";
			link.l3 = "(叹气) 多少钱? ";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "聪明的小伙子, 这是正确的决定, 伙计。 祝你好运。 希望你有一天能找到一个真正爱你的女人。 最好是红发或金发, 对吗? ";
			link.l1 = "再见, 伙计... ";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "你侮辱我! 拔出钢刀, 混蛋! ";
			link.l1 = "让我们看看你没有手臂时如何破解保险箱! ";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// 任务钥匙从Kaleuche - 归还
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "你是个做生意的人, 我承认这一点。 你也许真的能成功。 五十达布隆。 放在桌子上。 ";
			link.l1 = "五十金币? 买一块锡? 把我 keelhaul (绑在船底拖行) 吧。 把钥匙放在桌子上。 现在。 ";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "价格不菲... 好吧。 拿去吧。 ";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "价格不菲... 好吧。 我很快带来。 待在这里。 ";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta修复明显错误
			dialog.text = "你带来五十达布隆了吗? ";
			link.l1 = "你知道, 我认为你可以没有它们活下去。 钥匙。 放在桌子上。 ";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "是的。 拿去吧。 ";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "我还在拿。 ";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "我们跳舞吗? ";
			link.l1 = "我来领舞。 ";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("您已支付50达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "好的。 用你的头脑, 你可能会带着一些八里亚尔和你的脑袋离开这里。 拿着钥匙, 听我免费的建议。 勒瓦瑟的女人笨得像条鱼, 但她相信自己很狡猾。 别相信她。 管好你的下半身, 看好你的口袋。 她不是什么对手, 只是小心点, 避免把她丈夫卷入其中\n最后一件事 - 她的凉亭里有一个箱子, 里面放着她的小饰品, 很容易撬锁。 她会把她的那份放在那里。 你听到了。 海上平安, 兄弟。 记住, 兄弟优先于女人。 ";
			link.l1 = "一路平安, 伙计... ";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// 任务钥匙从Kaleuche - 归还
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "该死! 我没料到... 去他的女人! 我的主人告诉我要避开她那种人。 但工作就是工作。 我终究会抓到你。 ";
			link.l1 = "好吧, 伙计... 看来她想欺骗我们俩, 并不惊讶。 我们为什么要继续战斗? 想要工作吗? 我有一个。 你有技能, 我需要像你这样的人在我的船员中。 膳食。 铺位。 固定工资。 朗姆酒, 以及任何战利品的公平份额。 我以我的名誉担保。 你怎么说? ";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("钢铁意志", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("模仿", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("技能检查通过", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("技能检查通过", SKILL_FORTUNE);
			dialog.text = "您有一张能说会道的嘴, 船长的名声 precedes you, 我承认这一点。 是的, 我加入。 您的船叫什么名字? ";
			link.l1 = "'" + pchar.ship.name + "'。 和水手长谈谈, 他会给你找个铺位。 欢迎上船! ";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "哈! 我在世界上步步高升。 帮我踢那个婊子一脚。 ";
			link.l1 = "... ";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification(" perk检查失败", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("技能检查失败 (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("技能检查失败 (21)", SKILL_FORTUNE);
			dialog.text = "您说得好听。 但如果您想让真正的专业人士加入您的队伍, 还不够甜。 将来记住这一点。 如果您还有未来的话。 ";
			link.l1 = "试试看。 动作快点, 我和一位女士有约会。 ";
			link.l1.go = "mercen_5";
			link.l2 = "今天没有第二次机会。 我是个忙人, 所以别弄脏地毯。 您的报酬不足以让您为某个小婊子送死。 如果他们甚至付了您钱的话。 ";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "您是对的。 还没人付我钱... 现在我就解决这个问题。 做你想做的... ";
			link.l1 = "... ";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}