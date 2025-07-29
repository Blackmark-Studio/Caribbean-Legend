// 海龟汤任务的NPC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你需要什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 福克斯的勤务兵 - 本杰明.琼斯
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "上校大人目前在野外进行军事演习。 你找他有什么事, 船长? ";
				link.l1 = "这次, 本, 我需要找的是你。 关于你妹妹莫莉, 我有坏消息。 那个漂亮女孩显然遇到了麻烦, 被托尔图加的海盗抓了。 她需要帮助, 并让我来警告你。 主动传递消息的人被杀了, 但他死前设法告诉了我关于你妹妹的事。 ";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "如果你是去找福克斯上校, 那就转个360度走开。 他不接待客人。 ";
				link.l1 = "那好吧。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "上校不在这里。 过会儿再来。 ";
				link.l1 = "好吧... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "哈! 你是第一个称我妹妹‘漂亮’的人。 上帝给了她掷弹兵的身材, 却把耶利哥的号角当成了她的声音。 我们的莫莉能自己战斗\n但上帝的创造力不止于她下巴以下的部分。 不, 他做的最妙的事是在她胸前安了张我们已故父亲那张多毛。 长满麻子的脸。 我得说, 先生, 我老爸的脸曾经能把马吓得晕倒。 ";
			link.l1 = "看来你并不特别难过... ";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "她为什么会出现在托尔图加? 莫莉是我们勇敢上校的女儿凯瑟琳.福克斯的仆人。 凯瑟琳从欧洲来给父亲过生日, 但她所在的船队被耽搁了\n如果你想见到真正的莫莉.琼斯和她的女主人 —顺便说一句, 她非常漂亮 —一个月后再来。 一天也不能早。 ";
			link.l1 = "原来你妹妹莫莉.琼斯一直在为福克斯小姐服务, 目前住在大西洋彼岸? ";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "正是如此! 最后一位信使告诉我们, 护国公克伦威尔亲自派遣的海军中队一个月前才从伦敦出发。 凯瑟琳乘坐的双桅船‘信天翁号’本应伴随他们。 我们将从下一艘邮船得知是否真的如此。 尽管船只尚未抵达, 而上校已严令‘信天翁号’不得单独航行\n你知道他心爱的妻子在一次法国海盗袭击中丧生吗? 这对上校来说不容易, 他仍然害怕公海的危险... 所以我帮不了你, 船长! 有很多殖民地女孩叫莫莉! 此外, 在英国姓琼斯就像没有姓一样! \n安提瓜的每个水手都认识我和我的指挥官。 有些陷入困境的可怜女孩想找我帮忙并不奇怪。 我想帮, 但我没有赎金。 上校欠我三个月工资, 我和大家的薪水都随‘信天翁号’而来。 ";
			link.l1 = "看来我弄错了。 不过还是谢谢你的说明。 ";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "不客气, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // 可能有凯蒂的选项
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// 罗伯.马丁
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "你想要什么? ! 我不想说话。 ";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "我有笔生意找你, 船长。 我看你心情不好, 也许我的提议能让你开心点。 ";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "安静点, 喝杯朗姆酒。 是我错了, 伙计。 对不起。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //取消计时器
			dialog.text = "听起来很吸引人! 而且你这张脸好像在哪儿见过... 只是想不起来在哪里见过你。 快说吧! ";
			link.l1 = "我知道你和蒂博的事... 放松点, 伙计! 你不必怕我。 我有个交易想提议给你。 ";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "该死的! 去他妈的那个酒鬼猪猡! ... 我没能... ";
			link.l1 = "你说得对。 你的水手嘴巴太大, 但他的谣言除了我没传到别处。 而且这些谣言不会再传了, 因为你已经处理了, 不是吗? ";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "天哪! 我现在认出你了! 你就是那个搞垮多利上校并夺走他整个岛屿的人! 你和荷兰西印度公司有大生意往来, 还和西梅因男爵称兄道弟... 你叫... "+GetFullName(pchar)+", 对吗? ";
			link.l1 = "你消息挺准的。 是的, 是我。 但你能先冷静一下吗, 罗伯特? ";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "啊! 我怎么冷静得下来, 群岛上最著名的海狗之一盯上了我, 不仅如此, 他还知道了我的事! 我到底哪根筋不对去袭击这艘双桅船! 我怎么会觉得这脱离船队的猎物很容易... ";
			link.l1 = "闭嘴听我说。 在我看来, 我们都想把勒瓦瑟的头放在盘子里。 那个自大的吹牛大王太膨胀了, 惹到了一些重要人物。 我打算改变岛上的权力平衡, 让德庞西取而代之, 但我不想让同胞流多余的血, 尤其是因为某个肮脏的小偷。 你可以帮我, 我也可以帮你和蒂博保住特权。 ";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "等等, 等等! 我简直不敢相信自己的耳朵! 今天幸运女神眷顾我了。 你说得对, 我们目标一致。 有你在, 事情会有趣得多... 蒂博剑法不错, 但他没胆子割开他叔叔的喉咙... 但像你这样狡猾的鲨鱼可以做到。 你的名声很响\n我不需要你的保证, 但作为回报, 我会帮你弄到那个女孩。 在我完成加勒比的生意前, 我需要她当人质。 很快, 英国护卫舰就会来追我。 我到底哪根筋不对去袭击那艘双桅船! 它看起来像是脱离船队的 easy 猎物... ";
			link.l1 = "她有什么特别的? 你瞒着勒瓦瑟藏起来的那个女孩? ";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "是的。 你必须说服蒂博和那个女孩分手。 我让他在我查明她到底是谁时照顾她, 但这个‘琼斯小姐’, 不管她叫什么, 完全把他弄晕了, 现在亨利甚至瞒着我藏她! 把那个迷人的妖女带给我, 我会在城外安排你和勒瓦瑟见面。 到时候你就有机会伏击他。 我会在鱼眼海滩等你。 ";
			link.l1 = "成交。 现在告诉我怎么抓住蒂博。 ";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "酒馆里的人可以告诉你去他家的路。 亨利相当引人注目。 威胁他要曝光, 让他把女孩带给我。 同一天我会让勒瓦瑟知道他侄子在城市地牢里藏了个罕见的美人\n我的信使会在酒馆找你。 等他找不到亨利, 总督就会带一小队人去地牢, 你就有机会和他好好聊聊了。 ";
			link.l1 = "我该把女孩送到哪里? ";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "让他自己把她送到海滩。 我会顺便跟他说几句... ";
			link.l1 = "好的。 就这么定了。 托尔图加见! ";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "如果一切按计划进行, 我们就再也不会见面了。 至少我希望如此。 再见! ";
			link.l1 = "... ";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//关闭位置
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// 创建蒂博
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
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
			sld.MultiFighter = 1.0+fMft; // 多 fighter
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // 计时器
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // 计时器
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "啊! 我没料到... 你是来取我灵魂的吧, 伙计? 我已经按约定做了! 这到底是怎么回事? ! ";
			link.l1 = "你有判决在身, 罗伯特。 这判决由我执行。 所以我来完成任务。 ";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "你这个恶魔! 这不可能! 他不可能这么快就发现一切! 他到底是怎么发现的? ! ";
			link.l1 = "你是说福克斯? 不。 不是他派我来的。 上校甚至还不知道你杀了他女儿。 是你的老伙伴亨利.蒂博想让你死。 他雇了我。 ";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "那个该死的娈童! 我早该在他在‘伏尔泰号’上时把他喂螃蟹... 那个混蛋答应了你多少钱? ";
			link.l1 = "不是每天都有人能知道自己脑袋的价码, 对吧, 罗伯特? 蒂博给你开了二十五万, 但我让他相信你更值钱。 你值三十万银币, 我的朋友。 高兴吗? ";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "等等... 我们做个交易! 我给你更多钱! ";
			link.l1 = "用什么钱, 罗伯特? 我绝对肯定你在撒谎。 你没有亨利答应我的那么多钱。 而且这也不是主要的。 如果不是因为一个事实, 我会拒绝他追杀你并结束你和蒂博的肮脏勾当的提议。 ";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "什么事实? ";
			link.l1 = "你杀了凯瑟琳.福克斯。 那个可怜女孩的唯一罪过就是生为福克斯上校的女儿。 我讨厌像你这样把 defenseless 女人置于死地的卑鄙懦夫! 我不会和你做任何交易。 想都别想。 别浪费口舌了。 ";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "去他妈的! 我还能怎么办? ! 我不能让她活着, 也不能在船上无休止地藏着她! 你是谁... 你这个流氓, 你这个混蛋, 你这个刺客, 有什么资格教训我道德! 看看你自己! 看看你的‘手段’! 你并不比我好! ";
			link.l1 = "够了。 马丁, 拔出你的刀! 是时候做个了断了。 ";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "地狱见! ";
			link.l1 = "... ";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// 蒂博, 没有凯蒂的选项
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //取消计时器
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "你在我家干什么, 先生? ";
			link.l1 = TimeGreeting()+", 蒂博先生。 我是代表你认识的一个人来的, 罗伯特.马丁船长。 ";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "嗯。 然后呢? ";
			link.l1 = "马丁船长希望你现在去鱼眼海滩见他。 但不要一个人去。 他还希望看到莫莉.琼斯和你一起。 你明白我的意思吗? ";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "唉, 先生, 我不明白。 我从没听说过什么莫莉.琼斯, 罗伯特也从没有必要派一个... 我从未见过的全权代表来找我。 告诉你吧, 先生, 我是这个岛的二把手, 仅次于我叔叔总督, 所以... ";
			link.l1 = "生活是不可预测的, 亨利... 现在你是岛上的二把手, 几小时后你可能就会被戴上镣铐关进地牢... 就为了一个连一个比索都不会给你的人的命。 你违反了你叔叔的命令, 不是吗, 蒂博先生? 对你来说什么更重要: 一个放荡的女孩还是你的命? ";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "你... 你撒谎! 你在胡说八道! ";
			link.l1 = "你和其他人一样清楚你叔叔的脾气有多暴躁。 勒瓦瑟会在日落前发现你藏了那个女孩。 别问我罗伯特是怎么知道的, 记住我的话: 他吓得要死, 准备马上起锚。 他甚至不敢进城, 而是付了我一大笔钱来给你捎这个口信。 ";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "该死... 不可能! ";
			link.l1 = "由你决定, 先生。 马丁不会等你超过两小时。 他很珍惜自己的脑袋。 他还在托尔图加海岸逗留, 而不是躲在荷兰人那里, 只是作为友谊的表示。 ";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "天哪! 我叔叔怎么会发现? ";
			link.l1 = "流言蜚语, 亨利。 流言蜚语。 连我都知道你和罗伯特抓住了那个从你同伴劫持的英国双桅船上下来的美人。 瞒着勒瓦瑟藏了她... 啧啧。 你真的怀疑只有我知道这个故事吗? ";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "看来你说的是实话, 先生。 告诉马丁... ";
			link.l1 = "我想你没明白, 亨利。 马丁不会等你。 你唯一的希望就是把那个女孩弄走, 就是你和罗伯特脖子上挂着绞索的原因。 跑到你藏她的地方, 拉着她漂亮的小手, 把她带到‘伏尔泰号’去。 快点找到她, 更快地带过来。 我不会向你叔叔透露一个字。 ";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "好吧。 那我们就这么办。 谢谢你的好意, 先生! ";
			link.l1 = "不用谢我, 先生。 我的工作是有报酬的... 我只是希望你在被煮熟之前摆脱困境。 ";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//关闭位置
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// 有凯蒂的选项
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //取消计时器
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "你在这里干什么, 先生? 我没邀请你。 ";
			link.l1 = TimeGreeting()+", 蒂博先生。 我从一个你认识的人那里来。 他叫罗伯特.马丁船长。 ";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "嗯。 然后呢? ";
			link.l1 = "马丁船长希望你现在去鱼眼海滩见他。 但不要一个人去。 他还希望看到莫莉.琼斯和你一起。 你明白我的意思吗? ";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "唉, 先生, 我不明白。 ";
			link.l1 = "这正是我预料你会说的。 当然, 我怀疑你以前是否见过福克斯上校的女儿, 你当然知道福克斯上校, 臭名昭著的‘海狐’指挥官... 加勒比海英国敌人的噩梦? 你和罗伯特捅了个马蜂窝, 没被蜇到真是奇迹! 你从英国双桅船上俘虏的那个被你瞒着勒瓦瑟藏起来的女孩莫莉.琼斯, 是福克斯上校的女儿, 凯瑟琳.福克斯! ";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "什-什么? ";
			link.l1 = "你脸色很苍白, 先生。 现在仔细听我说, 亨利, 注意: 你和你的伙伴罗伯特麻烦大了。 克伦威尔的海军中队不日就会抵达加勒比海。 他们会追捕你。 其旗舰本身就能在几小时内把你引以为傲的拉罗什号和船员炸成碎片。 你觉得怎么样? 袭击那艘英国双桅船并俘虏福克斯的女儿值得吗? ";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "但这还不是全部。 你的计划不仅被我知道了。 你亲爱的叔叔总督会发现你违反了他的严格命令, 瞒着他藏了一个老色鬼肯定想自己占有的女孩。 你觉得呢, 亨利? 你叔叔会怎么对你? 你比谁都清楚他的脾气有多暴躁... ";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "全是谎言! ";
			link.l1 = "是吗? 我亲爱的亨利, 你可以问你的朋友马丁。 是他派我来的。 勒瓦瑟会在日落前发现你藏了那个女孩。 别问我罗伯特是怎么知道的, 记住我的话: 他吓得屁滚尿流, 准备马上起锚开航。 他甚至不敢进城。 这就是为什么他让我给你捎这个口信。 ";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "马丁不会等你超过两小时。 他很珍惜自己的脑袋。 他还在托尔图加海岸逗留, 而不是躲在荷兰人那里, 只是作为友谊的表示。 然而, 那个可怜的罗伯特甚至不知道莫莉.琼斯到底是谁。 你知道吗, 你们俩对女性时尚和外貌的无知真让我惊讶! 你们连贵族小姐和她的仆人都分不清! ";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "你想要什么? ";
			link.l1 = "终于从这个年轻暴发户嘴里听到明智的话了! 好吧, 蒂博: 现在就去你藏她的地方, 轻轻拉着她洁白的小手, 赶紧和她一起走到鱼眼海滩, 马丁的‘伏尔泰号’在那里。 告诉他你的计划变了... ";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "马丁必须履行对我的承诺, 他甚至不应该试图把女孩带上自己的船。 她会在海滩等我。 告诉罗伯特, 如果他不履行义务, 或者带走凯瑟琳, 或者她漂亮的小脑袋掉了一根头发, 我会用余生找到她。 当我找到她时, 我会把她活着交给福克斯上校... 但对你们俩... 我会把你们碎尸万段。 顺便说一句, 这也包括你, 蒂博。 ";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "我是谁, 我有什么能力, 你可以问罗伯特。 他很清楚。 如果你们都照我说的做, 我们都能赢。 罗伯特可以继续他的海盗生意, 你可以保留所有特权, 并在你亲爱的叔叔咽气后继承他的遗产。 至于我... 我也不会吃亏。 清楚了吗? ";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "我宁愿在永恒的地狱之火中燃烧, 也不愿按你的命令行事... "+GetFullName(pchar)+"! 我怎么一开始没认出你? 你这个屠夫! 你不打算让我或罗伯特活着! 你的‘手段’广为人知! 我绝不会把莫莉... 或者说凯瑟琳交给你这样的垃圾! 你不会活着离开托尔图加, 混蛋! ";
			link.l1 = "... ";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "站住, 懦夫! ";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//关闭位置
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //取消中断
			pchar.quest.Terrapin_tibo_call.over = "yes"; //取消中断
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "终于来了! "+GetFullName(pchar)+"船长, 很高兴你能来。 请进, 坐下。 喝点什么? 我有个很赚钱的生意提议给你, 我的朋友... ";
			link.l1 = "嗯, 你今天心情真好啊, 蒂博先生... 我们别坐着了。 直接说重点吧。 ";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "提议是关于我以前的朋友和同伴, 你认识的罗伯特.马丁, ‘伏尔泰号’帆船的前船长... ";
			link.l1 = "所以, 你和罗伯特不再是伙伴了? 有意思。 ";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "船长, 请听我解释寻求你帮助的动机, 一切就清楚了。 如你自己所知, 马丁抓住了一艘英国双桅船, 并俘虏了一名英国女人, 某个叫莫莉.琼斯的仆人, 这就是所有麻烦的起因。 ";
			link.l1 = "当然, 我知道。 据我理解, 你已经按照我的建议把女孩带到马丁的船上了? ";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "是的, 我做了。 但我每天都在后悔。 我得告诉你, 莫莉是个非常迷人漂亮的女孩, 我从未见过像她这样的人。 我必须承认, 我爱上了她。 她也喜欢我, 她自己说的! 我不能让我叔叔带走她\n当我护送她去‘伏尔泰号’时, 我希望叔叔一发现没人瞒着他藏女孩就会安定下来, 那个老色鬼。 然后罗伯特会把她带回托尔图加, 这样我就可以安全地把她转移到我家。 不管怎样, 这是我和马丁的约定。 但结果不同\n当我得知叔叔被杀后, 藏莫莉就没有意义了, 所以我耐心等待‘伏尔泰号’带着莫莉抵达。 ";
			link.l1 = "她到了吗? ";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "到了。 不幸的是, 莫莉不在船上。 罗伯特吓坏了, 好像他和路西法本人撞了头。 在他短暂的探险中, 他不知怎么发现了一个可怕的细节: 那个女孩, 莫莉, 根本不是莫莉.琼斯, 而是凯瑟琳.福克斯! ‘海狐’指挥官, 英国精锐海军团的福克斯上校的女儿! 你知道这意味着什么! ";
			link.l1 = "真该死, 怎么会这样! 毫无疑问, 罗伯特有事要害怕了。 但怎么会变成这样? ";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "凯瑟琳被俘时, 故意隐瞒身份, 假装是登船时死亡的仆人莫莉.琼斯。 她害怕马丁发现她的真实身份。 她成功骗过了他。 但在上次航行中, 罗伯特不知怎么发现了她的真实身份。 他说他找到了她的一些信件或文件... ";
			link.l1 = "如果女孩没登上‘伏尔泰号’, 她现在在哪里? ";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "她死了。 由于害怕福克斯因袭击英国双桅船而施加的惩罚, 马丁决定把唯一的证据沉入水中。 她是他袭击‘信天翁号’的最后一个证人。 ";
			link.l1 = "那他还不如杀了所有水手... 就像费尔南德.吕克。 否则, 他们总有一天会喝醉, 在酒馆里说漏嘴... ";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "他觉得全体船员都对他血誓效忠。 也许他有部分道理。 但我了解福克斯上校! 他会一直挖下去, 直到找到绑架他女儿的人! ";
			link.l1 = "我不怀疑。 尤其是在法国海盗杀了他妻子之后。 现在他女儿也... 顺便问一句, 先生, 你确定凯瑟琳真的死了吗? 也许罗伯特把她藏起来了。 ";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "我确定。 我和‘伏尔泰号’的一个水手谈过。 我相信他。 他亲眼看到他们割开女孩的喉咙, 然后在她脚上绑了个炮弹, 扔到了海里。 ";
			link.l1 = "天哪! 那个可怜的女人... 你想让我做什么, 亨利? ";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "从那天起我就夜不能寐。 我总是看到莫莉... 不如说凯瑟琳在我眼前... "+GetFullName(pchar)+", 是我把她送上死路的! 我无法原谅自己。 此外, 我对福克斯不抱幻想。 那个人不满足, 我想他甚至不睡觉。 迟早他会找到马丁的线索, 让某人开口, 当他发现谁杀了他女儿时, 一切都会爆发。 所有与整个故事有任何关联的人都会遭殃。 ";
			link.l1 = "包括我。 ";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "是的, 也包括我。 这就是为什么我希望你在福克斯之前找到马丁。 找到那个混蛋, 杀了他。 如果可以的话, 先让他受苦。 为了可怜的凯瑟琳。 事成之后, 把他戴在手上的那枚带手指的肥戒指切下来带给我作为证明\n我很清楚他弯曲的手指和那枚戒指。 如果你能做到, 我会付你二十五万银币。 ";
			link.l1 = "看来你从安息的亲爱的叔叔那里继承了一大笔遗产, 嗯? 告诉我, 亨利, 你为什么决定请我帮忙? ";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "因为我也了解了一些关于你的事, "+GetFullName(pchar)+"。 这很容易, 你是个名人。 不过不知道你到底为谁工作, 要么是德庞西, 要么是荷兰人, 要么是英国人, 要么是扬.斯文森男爵... 但有一点很清楚: 你接受微妙。 谨慎的工作并完成它们。 然后你会得到丰厚的报酬。 最棒的是你和西班牙人没有联系\n毕竟, 你也参与了我继承叔叔遗产后的事件。 别否认... 二十五万是好钱。 我会告诉你在哪里可以找到马丁。 你只需要拦截他的船并登上去。 ";
			link.l1 = "再加十万, 我就帮你解决马丁。 ";
			link.l1.go = "tibo_34";
			link.l2 = "唉, 蒂博先生, 你得自己解决你和马丁以及福克斯上校的问题了。 我向你保证, 我不会向 colonel 透露他女儿的命运和那些对她的死负责的人。 祝你一切顺利, 先生。 ";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "先生, 敬畏上帝... 相信我, 我没有成箱的百万财富! 我知道你的服务需要花钱, 所以我一开始就给你二十五万... 好吧... 好吧, 我再加五万金币。 我不能再给了! ";
			link.l1 = "好的。 成交。 你最后一次见到马丁是在哪里? ";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "他向南航行到加拉加斯的西班牙大陆, 设法求见了总督唐.迭戈.弗朗西斯科.德.克雷斯。 看来他不知怎么贿赂了他, 因为唐.迭戈授予了罗伯特西班牙王室的保护。 他卖掉了‘伏尔泰号’, 现在是重型帆船‘因凡塔号’的船长。 他一定有很好的积蓄, 因为他能贿赂总督, 还能购买和装备那样一艘大型军舰\n所以, 接下来他将作为西班牙中队的一部分, 从加拉加斯航行到圣多明各。 这是我的特工设法查明的全部。 抓住马丁的唯一机会就是追上西班牙中队\n如果他们到达圣多明各, 就完了。 不知道罗伯特下一步会去哪里。 他会像兔子一样躲进洞穴, 我们再也找不到他了。 ";
			link.l1 = "知道了。 我会拦截他们。 ";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "别忘了带戒指的手指! 这是我们协议的必要条件! 我要绝对确定罗伯特死了! ";
			link.l1 = "好的。 别浪费时间了, 我马上起航! ";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "马丁还在加勒比海臭烘烘地活着吗, 船长? ";
			link.l1 = "他活不了多久了! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "马丁还在加勒比海臭烘烘地活着吗, 船长? ";
			link.l1 = "不了。 你不必再害怕福克斯上校了, 凯瑟琳也报仇了。 这是证据。 ";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "是的... 这无疑是马丁的手指。 你总是给人惊喜, "+GetFullName(pchar)+"船长! 你确实配得上你的名声。 ";
			link.l1 = "我们来谈谈报酬吧, 蒂博。 ";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("你收到了500枚达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "都准备好了。 拿着你的报酬。 ";
			link.l1 = "谢谢。 我很高兴你能提前准备好。 好了, 亨利, 希望你以后不要再陷入这样的困境, 将来交些更好的朋友。 祝你一切顺利! ";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "谢谢你的帮助, 船长! 我会把你推荐给我所有的朋友。 祝你好运! ";
			link.l1 = "... ";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "是的, "+GetFullName(pchar)+"先生? 你找我有事吗? ";
			link.l1 = "不, 蒂博先生。 只是决定过来一下。 再见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "啊, "+GetFullName(pchar)+"... 来吧, 你怎么这么久! 现在, 谁知道罗伯特.马丁在哪里? ! 如果福克斯上校设法发现了一切, 我想我会有大麻烦... ";
			link.l1 = "我知道。 我来晚了。 对不起, 蒂博先生, 但我被一些非常紧急的事情耽搁了。 我不浪费你的时间了。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "你想要什么, "+GetFullName(pchar)+"? 我没时间闲聊。 我有更重要的事情要做。 我必须在福克斯之前找到马丁... ";
			link.l1 = "是的, 是的。 我这就走。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// 马丁的信使
		case "envoy":
			dialog.text = "你是"+GetFullName(pchar)+"船长吗? ";
			link.l1 = "你找对人了, 伙计。 我洗耳恭听。 ";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "你的债务人让我告诉你, 事情已经完成, 鱼将在一小时内入网。 所以抓紧时间。 ";
			link.l1 = "我明白了。 谢谢你! ";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// 勒瓦瑟在洞穴里
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //取消计时器
			dialog.text = "你他妈的在这里逛什么? 你是谁? 马上回答我! ";
			link.l1 = "你他妈的是谁, 为什么问我这么愚蠢的问题? ";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "什么? ! 你这个流鼻涕的混蛋! 我是谁? 我是这个岛的总督, 弗朗索瓦.勒瓦瑟, 德.勒内.德.布瓦杜弗莱.德.莱特雷Senior! 这个岛上的一切都在我的管辖之下! 包括你在我的地盘上的时候, 小狗! ";
			link.l1 = "嗯... 大坏狼本人啊? 你有点迷路了, 勒瓦瑟, 德.勒内.德什么的。 你的时间到了。 根据总督弗朗索瓦.隆维利耶.德庞西的命令, 你被解除职务并判处立即死刑! 我既是你的法官, 也是你的刽子手! 有什么遗言吗? ";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "我想你不会放弃, 求我也没用, 所以拔剑吧! ";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "去他妈的! 是德庞西的特工! 拔剑! 杀了他! ";
			link.l1 = "我们跳舞吧。 ";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//允许战斗
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// 增援
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// 勒瓦瑟在酒馆房间里
		case "levasser_room":
			dialog.text = "你他妈的在这里干什么? 你是谁? 回答我, 现在! ";
			link.l1 = "怎么样! 没想到吧... 我猜你是勒瓦瑟先生? ";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "是的, 我是这个岛的总督, 弗朗索瓦.勒瓦瑟, 德.勒内.德.布瓦杜弗莱.德.莱特雷Senior! 这个岛上的一切都在我的管辖之下! 包括你在我的地盘上行走的时候, 你这个无赖! 回答问题! 中士, 锁上门。 这个人不怀好意! ";
			link.l1 = "你洞察力惊人, 勒瓦瑟先生, 德.勒内.德什么的。 我在这里的出现不会让你高兴。 根据总督弗朗索瓦.隆维利耶.德庞西的命令, 你被解除职务并判处立即死刑! 我既是你的法官, 也是你的刽子手! ";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "我想你不会放弃, 求我也没用, 所以拔剑吧! 你是我的工作, 没有个人恩怨。 只是为王室服务, 哈! 中士, 我不建议你在我执行总督命令时干涉! ";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "别听他的, 中士! 他是西班牙特工! 杀了他! 卫兵, 快来! 这里有西班牙人! ";
			link.l1 = "其实我从没去过西班牙, 只去过纳博讷。 ";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//允许战斗
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// 阳台上的女孩
		case "roof_girl":
			dialog.text = "哎哟! 救命! 士兵! ";
			link.l1 = "安静点, 你这个傻瓜! 如果你不尖叫, 我就不把你怎么样! ";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "别杀我! ";
			link.l1 = "别犯傻! 十分钟前有个男人跑过去了。 一个穿着讲究的贵族。 他藏在哪里? 别想告诉我你没看见! ";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "蒂博先生? ";
			link.l1 = "那么, 你认识他! 他跑到哪里去了? 你是打算回答, 还是要我好好摇醒你让你清醒点? ";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "哦不, 求你别伤害我! 蒂博先生跑了, 朝海边那个方向。 他从起重机上跳进了水里。 他可能死了, 太高了... ";
			link.l1 = "我不这么认为。 他不是那种会自杀的人。 你应该进去。 今晚在这里很危险..";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "哎哟! 啊-哎哟! 别开枪! ";
			link.l1 = "什么? ! ";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// 凯蒂
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "你是谁? 你是来杀我还是... 更糟? ";
			link.l1 = "都不是, 夫人。 我会把你, 凯瑟琳.福克斯, 送回圣约翰你父亲那里。 如果之后他因为你 disobeying 他的命令而鞭打你, 那我的过错就会重演。 不过, 我希望上校看到女儿尽管让他担心但还活着会很高兴。 ";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "感谢上帝! 我一定是在做梦! 你知道我是谁吗? 你是法国人, 是天主教徒, 却决定来这里把我从自己同胞手中救出来? 你只是为了福克斯上校的女儿就冒生命危险? ";
			link.l1 = "我来托尔图加的初衷完全不同。 但我也不能把一位美丽的女士留在一群小偷和强盗手中。 ";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "你是个高尚的绅士! 你叫什么名字, 先生? ";
			link.l1 = ""+GetFullName(pchar)+"。 "+GetFullName(pchar)+"船长。 ";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "告诉我, 船长, 你真的要带我去圣约翰见我父亲吗? ";
			link.l1 = "是的, 尽管他不喜欢法国人。 好吧, 我会提醒他, 英国也有恶棍, 包括英国军官! 我至少见过其中一个... 理查德.弗利特伍德是他的名字。 ";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "如果我们能到安提瓜, 我会尽我所能说服我父亲, 法国人中有真正的骑士。 ";
			link.l1 = "我会非常感激... 好吧, 我希望我的守护天使已经注视着我在城市屋顶上的踪迹, 正在寻找我们返回的路。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "直到现在我都不敢相信你会遵守承诺! 最近发生了那么多可怕恶心的事... 谢谢你, 船长, 让我重新相信了人性和骑士精神。 你应该找时间拜访我父亲! \n他尊重像你这样的人。 你是法国人也没关系。 我会尽一切努力说服父亲重新考虑他对贵国的态度。 ";
			link.l1 = "谢谢你, 凯瑟琳。 也许我会接受你的盛情邀请。 ";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "我真的希望你会, 船长。 再次非常感谢你为我所做的一切。 我永远不会忘记。 ";
			link.l1 = "去吧, 赶紧去找你父亲。 他见到你会很高兴的。 也许他已经从野外回来了。 好吧, 不管怎样, 我该走了。 再见! ";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // 福克斯到位
			pchar.questTemp.Terrapin_KathyReward = "true"; // 160912 救凯蒂的奖励
		break;
		
		// 我们的水手
		case "terrapin_grot":
			dialog.text = "你来了, 船长! 我们担心死了! 在瓦屋顶上猛冲, 从令人心惊的高度跳下, 那景象真壮观! 上帝作证, 我们担心你过不去... 欢迎回到船上, 船长, 长艇准备好了! ";
			link.l1 = "太好了。 凯瑟琳, 跟我来! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "你好, 先生。 你是"+GetFullName(pchar)+"船长吗? ";
			link.l1 = "是的, 是我。 怎么了? ";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "呼, 我差点没追上你... 我是代表你认识的一位名叫亨利.蒂博的先生来找你的。 ";
			link.l1 = "亨利? 他想要什么? 分享他因亲爱的叔叔去世而意外继承遗产的喜悦? ";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "蒂博先生紧急请求你尽快去托尔图加他的豪宅拜访他。 他有报酬丰厚的工作给你。 他还让我向你提到一个名字: 罗伯特.马丁。 这应该能引起你的兴趣。 ";
			link.l1 = "是吗? 亨利怎么会这么想? ";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "如果这还没说服你去拜访他, 他还让我补充以下内容: ‘罗伯特.马丁必须死’。 ";
			link.l1 = "好了, 好了... 现在开始有趣了。 两个 sworn 朋友刚吵了一架... 如你所说, 我会找机会拜访亨利。 ";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "蒂博先生请你不要拖延拜访。 ‘鱼将在十天后游出网外’是他的原话... ";
			link.l1 = "他和罗伯特说话方式一样。 好吧, 我会去拜访亨利。 ";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}