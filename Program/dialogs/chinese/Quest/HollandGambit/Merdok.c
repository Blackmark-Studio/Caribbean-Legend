// 约翰.默多克, 即约汉.范.默登, 罗登堡的同伙
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "先生, 你选了个该死的糟糕时间来闲聊。 整个驻军都在找你。 你最好赶紧离开... ";
			link.l1 = "别担心。 我不会待很久。 ";
			link.l1.go = "exit";
			break;
		}
		// 出售炼金套件, 如果失败了甘比特
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "欢迎, 船长。 你对一个有趣的提议感兴趣吗? ";
				link.l1 = "这里各种各样的人似乎都有这样的提议, 而我是个好奇的人。 是什么? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// 真理卫士
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "日安。 欢迎来到我的药店。 我有治疗大多数疾病和不适的药物。 我能为你提供什么? ";
			link.l1 = "听着, 约翰, 有传言说有人住在你二楼的地方... ";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------前往荷兰------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "日安。 我很高兴在我的药店见到你。 我有治疗大多数疾病和不适的药物。 我能为你提供什么? ";
				link.l1 = "你好, 默多克先生。 我代表卢卡斯.罗登堡来这里。 他派我来和你讨论关于理查德.弗利特伍德的事情。 ";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "下午好。 你有什么问题? 我既有止咳合剂又有止泻粉! ";
				link.l1 = "你好, 默多克先生。 我代表卢卡斯.罗登堡来这里。 他派我来和你讨论关于理查德.弗利特伍德的事情。 ";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "啊, 罗登堡的走狗来了... 赫拉克勒斯, 龙威 - 请你们出来好吗? \n杀了这个人! ";
				link.l1 = "等等, 我有处方! ";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "下午好。 我很高兴在我的药店见到你。 我有治疗大多数疾病和不适的药物。 我能为你提供什么? ";
			link.l1 = "目前没什么, 谢谢。 我感觉很好。 ";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------前往英国---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "你好, 不速之客。 你没有戴面具, 看起来也不像强盗。 因此我得出结论, 你需要这个可怜的药剂师提供其他东西。 也许是治腹泻的? ";
			link.l1 = "你好, 约汉.范.默登。 我带来了赫拉克勒斯.通扎格的问候。 我看你知道这个名字。 ";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------对抗所有人--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "啊, 你来了。 那么, 你见过赫拉克勒斯了吗? ";
					link.l1 = "是的。 我们达成了协议。 约翰, 我要帮助赫拉克勒斯, 关于理查德.弗利特伍德我有几个问题要问你。 ";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "你好! 很高兴见到你, " +pchar.name+ "! ";
					link.l1 = "你好, 约翰。 你挖到弗利特伍德的什么消息了吗? ";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //移除计时器
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "你迟到了。 鸟儿已经飞出笼子了。 查理.克尼佩尔访问了威廉斯塔德, 从那里给理查德带了个女孩。 现在他们正和一支军事中队在一两天内驶往英国。 弗利特伍德走了, 你这辈子再也见不到他了。 ";
					link.l1 = "该死的。 我完全忘了理查德, 还忘了时间。 再见。 ";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "欢迎回来, " +pchar.name+ "! 现在没你的事。 没有弗利特伍德的消息, 查理.克尼佩尔也还没从库拉索回来... ";
					link.l1 = "他永远不会回来了。 他和他的双桅帆船都不会。 ";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "啊, 我们有客人了! 你好, 查理! 下午好, 小姐! ";
					link.l1 = "下午好, 约翰! 让我给你介绍我的女伴, 理查德的未婚妻, 迷人的阿比盖尔.施努尔。 ";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "小声点... 你接下来打算做什么? ";
					link.l1 = "接下来? 我宁愿睡一会儿, 但不幸的是没有时间了。 我要把弗利特伍德从他藏身的洞里挖出来, 完成赫拉克勒斯的工作。 ";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "你写完了吗? 让我看看... 我的上帝, 查理, 你真是个疯子! 你不觉得你写得太详细了吗? 我是说, 关于施努尔小姐的手指。 耳朵和脸的部分? 你肯定有某种病态的天赋。 该死的, 我都快吐了! ";
					link.l1 = "我在虚张声势, 约翰。 我不会杀那个女孩。 我可以让她失去一根手指... 但不会更多。 毕竟她还有九根。 ";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "进展顺利吗? 我从你眼里就能看出来 - 你做到了! ";
					link.l1 = "是的。 弗利特伍德接受了我的条件。 陷阱的 jaws 正在闭合。 现在我们只需等待。 ";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "啊, 欢迎回来, 我的朋友! 你能告诉我什么? ";
					link.l1 = "弗利特伍德死了。 一切按计划进行。 他到达了岛上, 我在海滩上组织了伏击。 他反抗得很激烈, 但没用。 我们中只有一个人从海滩上走了出来。 ";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "好了, " +pchar.name+ ", 我有个严肃的提议给你。 我要谈的事情非常危险, 但考虑到你解决掉弗利特伍德的方式, 我相信你能处理。 你有一种... 解决难题的罕见天赋。 ";
					link.l1 = "我很荣幸。 继续说。 ";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "欢迎回来, " +pchar.name+ "! 有什么好消息给我吗? ";
					link.l1 = "约翰, 从现在起你可以不用在枕头下放刀睡觉了。 卢卡斯不再是你的威胁了。 他已经被捕并被关押, 不久将被送往荷兰, 在那里他将因叛乱。 企图谋杀和其他罪行受审。 ";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "很高兴见到你, " +pchar.name+ "! 你还活着 - 这是件好事。 有什么消息吗? ";
					link.l1 = "是的。 范.贝格永远消失了。 正如你所说, 他追踪到我, 在最不方便的时候攻击了我。 范.贝格是个硬骨头, 但最终我还是解决了他。 ";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "你还需要别的吗? ";
			link.l1 = "不, 约翰, 没什么。 我要走了。 ";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "下午好。 我很高兴在我的药店见到你。 我有治疗大多数疾病和不适的药物。 我能为你提供什么? ";
			link.l1 = "目前没什么, 谢谢。 我感觉很好。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------前往荷兰-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "我不知道你在说什么, 先生。 什么卢卡斯.罗登堡? 我和荷兰人没有往来。 你一定是弄错了。 ";
			link.l1 = "什么? 罗登堡先生派我来见你! ";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "我再告诉你一次 - 我不认识任何叫罗登堡先生的人。 至于荷兰人, 我不和他们打交道。 在这个世界上我只有两件事无法忍受: 不宽容他人文化的人, 以及荷兰人。 所以如果你不需要任何药物, 请让我继续工作。 ";
			link.l1 = "越来越奇怪了... ";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "嗯嗯... 你是罗登堡先生派来的? 好吧。 我听你说。 ";
			link.l1 = "我需要在一个隐蔽的地方组织与弗利特伍德船长的会面。 我从雅各布.范.贝格那里借了'幻影'号, 就是弗利特伍德先生非常想捕获的那个荷兰私掠船。 我想通知他,'幻影'号不久将在多米尼加海岸附近方便地停泊。 ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "雅各布把他的船给你了? 嗯, 现在你需要有人告诉弗利特伍德先生,'幻影'号不久将在多米尼加海岸附近停泊, 因为你由于特殊原因不能亲自告诉理查德... ";
			link.l1 = "正是。 罗登堡先生建议我就此事与你联系。 ";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "在这种情况下, 你需要的人是查理.克尼佩尔。 弗利特伍德的忠实朋友... 也是他的间谍。 和他谈谈, 把你想让理查德知道的一切都告诉他。 小心点, 克尼佩尔看起来很单纯, 但他不是傻瓜。 \n你可以在离海边不远的一间小屋里找到他。 他一定在那里。 ";
			link.l1 = "我明白了。 谢谢你, 默多克先生。 再见! ";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//中国佬出现了
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//敌人
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//朋友
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//中立 - 只是没有
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------前往英国-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "真的吗? 我以为可怜的加斯东已经在地狱里烧了好一阵子了。 ";
			link.l1 = "很可能, 但显然没有人像加斯东那样。 我在一个老犹太人的秘密岛上的宝藏里找到了他的头。 但他还是设法向你问好。 他还提到我们有一个共同的敌人: 罗登堡先生。 通扎格说你可能有对卢卡斯很重要的文件, 可以把他从库拉索的藏身之处引出来。 ";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "他说得对。 正是我的档案让罗登堡彻夜难眠。 看来他还在附近晃悠只是因为这个。 事实上, 他曾被承诺在联合省的公司董事会里谋个轻松的职位。 如果这个档案里的信息 --其中包含很多关于卢卡斯过去和现在的有趣事情 --被广泛知晓, 他的职业抱负就会破灭。 在那种情况下, 他最好的希望就是被斩首而不是绞死。 ";
			link.l1 = "把档案给我, 我会处理我们的敌人。 ";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "你一定觉得我是个傻瓜。 我还活着只是因为我还留着它。 我怎么知道你现在不是在为卢卡斯工作? ";
			link.l1 = "你只能相信我的话 - 或者死。 ";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "回答错误, 你现在就会死在这里! 龙威, 攻击! ";
			link.l1 = "哦吼, 中国佬从阴影里出现了! 别担心, 我会把你们俩都做成炒杂碎! ";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------对抗所有人-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "终于, 你醒了。 我还担心你不会醒过来呢。 ";
			link.l1 = "什么... ? 你是谁? 我到底在哪里? 我是怎么到这里的? ";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "冷静点, 不要一下子问这么多问题, 太激动对你不好。 我叫约翰.默多克, 是圣约翰这里的药剂师。 你在和弗利特伍德的人打架时失去了意识。 我得说, 他们把你打得很惨... 是赫拉克勒斯把你带到我药店来的, 嗯, 我用我的药水和药物治愈了你的伤口。 ";
			link.l1 = "赫拉克勒斯? 谁? 在街上帮我的那个人? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "是的。 就是他。 顺便说一句, 他想和你谈谈。 你需要在镇上见他。 你还能走路吗? 很好。 晚上出去 - 使用我家一楼门后开始的秘密隧道。 天黑前不要出去 - 弗利特伍德的人在找你。 ";
			link.l1 = "好的... 我的船在哪里? ";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "你的船被扣押了, 你的船员因为害怕被弗利特伍德的人杀死而四散了。 我很抱歉。 ";
				link.l1 = "该死的... ";
			}
			else
			{
				dialog.text = "她在港口, 在她通常的位置。 ";
				link.l1 = "呼... 很高兴听到这个。 我以为我失去她了。 ";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "你应该见见赫拉克勒斯。 晚上通过秘密隧道进城。 他会接近你。 现在休息一下, 我得回去工作了。 ";
			link.l1 = "好的, 约翰。 还有... 谢谢你的帮助和治疗! ";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//新的任务标志
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//重绘布里奇敦的酒保
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//关闭从药店通过门的出口
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//打开从房子到地下室的通道
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//打开从地下室到房子的通道
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "弗利特伍德? 你想知道他什么? ";
			link.l1 = "一切。 告诉我你知道的一切。 在我看来, 赫拉克勒斯为什么来安提瓜对你来说不是秘密。 我站在他那边。 ";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "很好。 皇家-我的意思是英联邦海军的理查德.弗利特伍德船长... 该死, 我总是忘记那个狂热的克伦威尔掌权并改了名字。 不管怎样, 弗利特伍德是个优秀的战士和经验丰富的水手。 他指挥着一艘名为'瓦尔基里'的双桅船 - 我得说, 这是一艘出色的船, 船员都是精英水手和海军陆战队员。 他对联合省, 特别是荷兰西印度公司发动了一场私人战争。 他掠夺了无数荷兰商船, 使保险费用飙升。 库拉索的总督悬赏捉拿他, 金额破了纪录。 ";
			link.l1 = "嗯... 这似乎有点不寻常, 一个'英联邦海军'的军官去当海盗... ";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "是的, 确实。 他在走钢丝。 英国人不正式承认他的行为, 拒绝与他有任何关系, 但实际上在背后鼓励他。 我有理由认为他与加勒比海的英国间谍网有某种联系, 而那些恶棍是不好惹的";
			link.l1 = "一个严肃的人... 这就是全部吗? 赫拉克勒斯告诉过我他的一个助手... 另一个查理... 他叫什么名字... 坎尼斯特? 坎农鲍尔? ";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "克尼佩尔? 是的, 有这么个人。 查理.克尼佩尔曾是英国海军的主炮手, 现在退休了。 现在他在海边过着平静的生活。 他是弗利特伍德在圣约翰的耳目, 所以小心他, 甚至不要想过问他关于理查德的事 - 你最终会进监狱或更糟。 ";
			link.l1 = "我明白了。 你能告诉我关于弗利特伍德的其他值得一提的事情吗? ";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "安提瓜从十六到六十岁的所有女人的偶像。 似乎这就是关于他的全部了。 嗯, 我想你知道他现在发生了什么。 他卧床不起, 舔舐伤口。 ";
			link.l1 = "他一定有一些弱点或恶习... ";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "你是什么意思? ";
			link.l1 = "嗯, 也许他喜欢赌博或酗酒, 或者无法抗拒女性 - 诸如此类的事情。 他结婚了吗? ";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "没有, 单身汉。 至于你提到的事情 - 他没有任何这些名声。 ";
			link.l1 = "我明白了。 但是, 也许他仍然有什么特别之处? 即使是这样的人也一定有一些弱点! ";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "我不知道。 听着, 我们这样做吧。 一周后来看我, 我会调查弗利特伍德的私生活。 成交? ";
			link.l1 = "成交。 谢谢你, 约翰! 我一周后到这里。 ";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//以免迟到
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//打开从药店的出口
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "是的, 但不幸的是不多。 而且我担心这无论如何也没什么用。 ";
			link.l1 = "说出来! 如果与弗利特伍德有关, 每一个细节都非常重要。 ";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "不久前, 理查德从一个未知的岛屿上救了两个犹太难民 - 一个老人和他的女儿, 他们正航行到威廉斯塔德。 他们乘坐的船被海盗击沉了。 弗利特伍德冒着自己的生命危险秘密将他们带到了库拉索。 从那以后已经有几个月了。 现在他派了他忠实的狗查理.克尼佩尔去威廉斯塔德... ";
			link.l1 = "嗯... 这有什么联系? ";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "我设法了解到查理接到命令要把一个来自威廉斯塔德的女孩送到这里, 一个叫阿比盖尔.施努尔的犹太女人。 是的, 就是那个岛上的同一个女孩。 看起来理查德爱上了她, 因为他派了他最好的特工去接她。 \n就是这样。 不知道这是否有帮助。 ";
			link.l1 = "哦吼吼! 哈哈哈! 看来我们这位坚定的单身汉已经爱上了这位犹太女子的狡猾魅力。 这是出色的工作, 约翰, 谢谢你! 现在我们的朋友克尼佩尔什么时候出发去库拉索? ";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "他昨天出发了。 ";
			link.l1 = "乘哪艘船? ";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "我就知道你会问这个。 他在一艘由英联邦-哦, 去他的,'皇家海军'委托的双桅帆船上。 她的名字是'泽卡夫'。 ";
			link.l1 = "'泽卡夫'? 对于一艘英国船来说, 这是个很荷兰的名字... 哦, 我明白了。 ";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "你思维很快... 她以前的名字是'皇家玛丽', 但这次航行她被命名为'泽卡夫'。 而且她挂着荷兰国旗。 ";
			link.l1 = "你的帮助非常宝贵, 约翰。 我现在出发。 我很快就会回来, 我需要你二楼的房间, 就是我康复时你让我住的地方。 ";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "你在搞什么? ";
			link.l1 = "我回来后会告诉你一切。 祝我好运, 约翰! 再见。 ";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//关闭查理的小屋
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "真的吗? 你为什么这么确定? ";
			link.l1 = "因为查理在海底喂鱼。 我登上了'泽卡夫'号, 把克尼佩尔送到了地狱。 当然, 在此之前我审问了他... 他身上有一封信, 这让我在和我们的犹太女子阿比盖尔, 我们勇敢的理查德的心上人谈话时可以假扮成克尼佩尔。 ";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "嗯... 这很聪明。 那么, 你是说... ";
			link.l1 = "是的。 我把犹太女子带到了安提瓜。 她在我的船上。 现在我在与弗利特伍德的牌局中有了一张王牌! 他会为她做任何事... ";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "你确定吗? 可能一切并不像你暗示的那么简单... ";
			link.l1 = "哦是的, 我绝对确定。 从信中我发现阿比盖尔的父亲因为钱反对她和理查德的婚姻。 我知道, 典型的犹太岳父。 所以弗利特伍德决定给她父亲一笔嫁妆 - 20万比索! 现在告诉我, 世界上有多少女孩值那么多钱? ";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "嘿! 当然不是犹太女子! 我这辈子还没见过值那么多钱的基督教女孩, 这是肯定的。 " +pchar.name+ ", 你是个狡猾的恶棍。 你会怎么处理她? ";
			link.l1 = "我会把犹太女子带到这里, 我们把她留在你的房间里。 我会告诉她理查德出海了还没回来, 所以她会做我们一周的客人。 她以为我是查理.克尼佩尔。 ";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "这很有趣。 所以你决定把女孩留在我家? 嗯... ";
			link.l1 = "约翰, 她是犹太人。 一个从荷兰殖民地带来的无国籍流浪者。 她在圣约翰这里是个无名小卒, 没人认识她。 放心, 我们可以为所欲为, 她不敢说一个字。 她名下没有一分钱或一个朋友。 而且无论如何, 她不会做我们的客人太久。 我会用她作为诱饵引出弗利特伍德, 之后就不再需要她了。 ";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "你开始让我害怕了, 查尔斯。 你不打算利用这个女孩, 是吗? 或者把她带到和克尼佩尔一样的结局? ";
			link.l1 = "不, 当然不.'狡猾的恶棍'我可能是, 但我不是美丽女孩的敌人 - 无论是犹太人还是基督徒。 或者说, 对于丑陋的女孩也是如此。 如果她规规矩矩, 这一切结束后我会把她送到威廉斯塔德她父亲那里。 那个老守财奴可能会跪在我面前, 感谢我把她从那个背信弃义的英国人手中救出来。 ";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "她在这场闹剧中有一个角色。 当戏演完后, 我就不再需要她了。 ";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "我明白了, 所以现在我得照顾她。 ";
			link.l1 = "我不会坚持, 伙计。 如果你完全反对这样做, 她可以留在我的船上。 但那样我就得为了安全把她铐起来, 把她和老鼠一起关在货舱里, 以保护她免受我的船员伤害。 你知道, 他们有女人在船上是件新鲜事。 那样对待一个可爱的女孩太可惜了。 ";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <—— legendary edition
			dialog.text = "我明白了, 所以现在我得照顾她。 ";
			link.l1 = "我不会坚持, 伙计。 如果你完全反对这样做, 她可以留在我的船上。 但那样我就得为了安全把她铐起来, 把她和老鼠一起关在货舱里, 以保护她免受我的船员伤害。 你知道, 他们有女人在船上是件新鲜事。 那样对待一个可爱的女孩太可惜了。 ";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "我明白。 很好, 把她带到这里。 帮助你对抗弗利特伍德是我的责任。 把她带到这里, 我会准备好她的'客房'。 ";
			link.l1 = "谢谢你, 约翰。 我知道我可以指望你。 ";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//放置凳子
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "哦! 我的荣幸。 我很高兴欢迎如此重要和... 优雅的女士。 小姐, 请你上二楼好吗? 那里有晚餐在等你, 床也铺好了。 我相信经过这么长途旅行, 你一定想好好睡一觉。 ";
			link.l1 = "是的。 阿比盖尔在从威廉斯塔德的长途航行后肯定累了。 ";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "你已经有计划了吗? ";
			link.l1 = "我有。 我们需要给理查德写一封勒索阿比盖尔的信。 安排在某个无人居住的岛上见面 - 比如特克斯岛。 如果他不遵守, 那么, 我们该怎么说, 我们会把他的希伯来甜心分块送给他。 ";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "为什么需要在无人居住的岛上搞这么复杂? ";
			link.l1 = "中立地带。 更安全。 反正我不打算带阿比盖尔去。 我需要弗利特伍德。 他肯定会在安提瓜设伏, 但在特克斯岛他没有这样的优势。 ";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "有道理。 谁来送信? 这非常危险。 ";
			link.l1 = "一个陌生人。 从酒馆里挑一个看起来可靠的醉汉。 他们为了一些朗姆酒钱愿意做任何你要求的事。 如果理查德一怒之下杀了他, 我们就再派一个。 我们会在信里附上阿比的一根手指。 这会让他更听话。 ";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = "" +pchar.name+ "... ";
			link.l1 = "别担心, 约翰。 我相信不会走到那一步。 你只需要找一个信使, 我马上就写这封信。 你有纸和墨水吗? ";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "是的, 我有。 而且我碰巧也认识一个合适的醉汉。 我推荐杰克.哈里森。 他每天晚上都在酒馆里灌朗姆酒。 你很容易找到他。 ";
			link.l1 = "好的, 给我拿笔和墨水, 我来给理查德写勒索信。 ";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "你打算什么时候把信交给他? 你会看着交付过程吗? ";
			link.l1 = "当然。 理查德不是傻瓜, 但我怀疑他会冒险。 至少, 我希望如此。 我不想伤害那个女孩, 但如果必须的话, 我会的。 好吧, 是时候找到你提到的那个醉汉了。 杰克... 他的全名是什么? ";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "他叫杰克.哈里森。 他通常在晚上去酒馆。 小心点! ";
			link.l1 = "一切都会好的。 等我。 ";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "嗯, 我不会这么说。 弗利特伍德很狡猾, 也很危险。 除此之外, 他是个剑术大师和经验丰富的水手。 他不会是容易的猎物。 ";
			link.l1 = "当我来到加勒比海时, 我就不再走轻松的路了。 好了, 约翰, 我该走了。 顺便说一句, 你提到我们勇敢的弗利特伍德有一艘好船, 是吗? ";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "他有我见过的最好的双桅船。 而且我见过不少。 ";
			link.l1 = "那很好。 我喜欢好船。 是时候起锚了! ";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//设置了舰队中存在瓦尔基里的标志。 
			if (iVal != 0)
			{
				dialog.text = "我没有要说的! 出色的组合, 伟大的想法和巧妙的实施! 恭喜你, " +pchar.name+ "! 而且你还设法把他的双桅船作为战利品! ";
				link.l1 = "谢谢你! 赫拉克勒斯在哪里? 我想见他。 我们上次见面时, 他说我可以在你的帮助下找到他。 ";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "出色的组合, 伟大的想法和巧妙的实施! 恭喜你, " +pchar.name+ "! ";
				link.l1 = "谢谢你! 赫拉克勒斯在哪里? 我想见他。 我们上次见面时, 他说我可以在你的帮助下找到他。 ";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "我随时都在等他。 他应该会通过秘密隧道来这里。 你应该向阿比盖尔解释一下。 她开始担心理查德的缺席了。 ";
			link.l1 = "好吧, 但我们不应该送她回家吗? ";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "还不行... 我需要先和你谈谈。 但首先等赫拉克勒斯的到来。 去安慰一下阿比盖尔。 给她编个故事, 随便编点什么。 然后到地下室来。 好吗? ";
			link.l1 = "是, 是, 约翰。 ";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "好了, 是时候摊牌了。 正如你已经猜到的, 我不只是一个普通的药剂师。 我的真名是约汉.范.默登, 直到最近我还是荷兰西印度公司的特工, 也是其副总裁卢卡斯.罗登堡的得力助手。 ";
			link.l1 = "真的! 这很有趣... ";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "现在不同了。 卢卡斯想退出游戏, 回到荷兰, 所以他需要埋葬所有与他过去有关的人和事\n我认为我还活着只是因为我的档案, 里面包含了卢卡斯所有罪行的信息... 比如'幽灵船'的故事, 那只是一艘由鲁莽无原则的恶棍雅各布.范.贝格指挥的普通海盗船。 罗登堡雇佣了这个人来掠夺和击沉英国商船\n范.贝格也负责击沉了载有阿比盖尔和她父亲的弗鲁伊特船。 阿比盖尔是这场游戏中的重要人物, 罗登堡也想得到她的人和心, 就像弗利特伍德一样, 所以当你把她带到这里时, 我很惊讶... ";
			link.l1 = "罗登堡... 就是阿比盖尔那位古怪的父亲一直提到的女婿! ";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "是的, 这就是为什么我想让她在这里待一会儿。 她可能是我对抗罗登堡的最后一张王牌, 尽管我不想再利用她了, 她是个好女孩, 我不想让她受苦。 我认为如果卢卡斯面临选择, 他会选择我的档案而不是她。 \n所以, 我提议你成为我对抗卢卡斯的盟友... 摆脱他, 使用任何必要的手段。 回报将是丰厚的。 ";
			link.l1 = "嗯... 我不认为这会比对付弗利特伍德更难。 ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "不, 你错了。 最后, 弗利特伍德是独狼, 独自行动。 罗登堡是公司的副总裁。 他是个非常有影响力的人, 只有库拉索的总督权力更大。 雅各布.范.贝格是他的特工, 一个非常危险的人。 卢卡斯坐在威廉斯塔德, 在公司卫兵的保护下, 他们和弗利特伍德的人一样优秀。 \n这不会容易。 ";
			link.l1 = "游戏规则是一样的 - 把老虎引出洞穴... 我已经有计划了。 关于卢卡斯, 你还能告诉我什么? ";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "嗯, 我几乎都告诉你了。 他有一艘名为'美凤'的快船 - 美丽的风。 她的船长是一个叫龙威的中国人 - 罗登堡的死党。 他也是一个你不想面对的敌人。 卢卡斯的船员中没有业余爱好者。 ";
			link.l1 = "我们从一开始就有一张王牌 - 你的档案。 如果他珍惜自己的生命胜过犹太女子, 那么他会不惜一切代价保持档案中的信息保密... 但是... 档案真的存在吗, 约翰? 你在虚张声势吗? ";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "档案确实存在。 卢卡斯也知道这一点。 你想出什么了吗? ";
			link.l1 = "我有。 约翰, 如果你真的是公司的特工, 你应该知道一些事情。 ";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "具体是什么? 问我。 ";
			link.l1 = "我需要拦截一艘公司的船。 最好是一艘没有护航的船 - 比如信使船之类的。 你能告诉我这方面的信息吗? ";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "嗯... 我没有这样的信息。 等等! 我确定公司每月有一艘邮船在菲利普斯堡和威廉斯塔德之间的航线上。 她运送商业文件。 她是一艘名为'希望'的双桅帆船。 \n她今天或明天将离开菲利普斯堡。 ";
			link.l1 = "好的, 就是它了! 我只需要去圣克里斯托弗海岸。 去库拉索的海路正好经过那里。 ";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "祝你好运, " +pchar.name+ "。 我不会问你计划的细节。 我会等你回来! ";
			link.l1 = "一切都会好的, 约翰。 照顾好犹太女子, 好好待她! ";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//设置生成遭遇的计时器
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//计时器
		break;
		
		case "Lucas_10":
			dialog.text = "难以置信! 我不敢相信我的耳朵! 那是怎么发生的? ";
			link.l1 = "我捕获了邮船, 代表弗利特伍德给卢卡斯送了一封信, 信中我声称我已经占有了某个来自圣约翰的药剂师的档案, 不久之后, 从这里到阿姆斯特丹和伦敦, 他的每一个罪行的证据都将为人所知。 我原以为他会开始追捕我, 但结果却相反。 ";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "卢卡斯指控马蒂亚斯.贝克背叛并与英国人交易, 将他关进监狱, 并住进了总督府。 他很可能干掉了双桅帆船的船长。 然后他告诉他忠实的中国佬'美凤'号的船长去击沉载有公司董事彼得.斯特伊弗桑特的船! ";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "罗登堡是个无情的人。 但即使是我也没想到他会走到这一步... ";
			link.l1 = "我捕获了'美凤'号, 审问了龙威。 他告诉了我一切。 我找到了斯特伊弗桑特, 警告了他罗登堡的意图, 我们一起航行了威廉斯塔德。 斯特伊弗桑特释放了贝克, 逮捕了卢卡斯。 他现在在监狱里。 ";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "嘿! 你有真正的天赋, 我的朋友... 你应该在公司海军或联合省的政界谋个职业 - 你完全有机会成为总督! 你对龙威做了什么? ";
			link.l1 = "我放了他。 他体面地投降了, 所以我没有伤害他。 ";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "那很好。 龙威是个好人, 不像他以前的老板。 好吧, " +pchar.name+ ", 你做得很好! 我会准备你的奖励, 但我需要一些时间... 同时... ";
			link.l1 = "约翰, 说实话, 有个小麻烦。 龙威和后来的罗登堡都告诉我雅各布.范.贝格在追捕我。 那有多糟? ";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "雅各布.范.贝格? 查理, 这很严重。 他是个无情的海盗, 一个熟练的水手和战士, 让弗利特伍德看起来像个胆小鬼。 一个专业的猎人。 他是那个按罗登堡的命令破坏航运的人。 \n他会找到你, 所以你必须准备好。 我应该为自己采取预防措施。 ";
			link.l1 = "我怎么才能找到这个范.贝格? ";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "我不知道。 卢卡斯和龙威是唯一知道在哪里可以找到他的两个人。 所以只要小心准备好\n我要关闭这个地方。 如果你想见我, 就通过秘密隧道。 把犹太女子带走, 她留在这里太危险了。 ";
			link.l1 = "别担心, 约翰。 让他出现, 我会处理他。 阿比盖尔在哪里? ";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "她去教堂了。 我为她感到难过。 她最近很不安。 ";
			link.l1 = "嗯... 这是个惊喜。 也许她意识到基督是她的人民长期期待的弥赛亚。 好了, 是时候把她送回她父亲那里了。 ";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "她想见你。 我相信她会要求你送她回家。 ";
			link.l1 = "阿比, 嗯? ";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "嗯, 我得承认我们已经成为朋友了。 我不后悔她住在我家, 感谢上帝她永远不会知道她为什么被带到这里。 ";
			link.l1 = "好了, 约翰, 我要去教堂见阿比盖尔。 然后我前往威廉斯塔德。 ";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//阿比 - 去教堂
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//关闭药店
		break;
		
		case "Final":
			dialog.text = "你... 解决了他? 哦 - 一个比喻。 好吧, 不管怎样, 你做到了! 恭喜! ";
			link.l1 = "我不会对你撒谎, 呵呵。 现在你可以安心了, 约翰。 ";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "终于! 我认为最好放弃所有这些政治游戏和阴谋。 现在是时候谈谈你完成工作的奖励了。 ";
			link.l1 = "嗯, 我当然很感激。 ";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "我要永远离开加勒比海。 作为对你帮助我并把我从罗登堡手中救出来的感谢, 我把这所房子和我的药店的所有权证书给你。 它们都是你的了。 拿着钥匙。 ";
			link.l1 = "那太好了! 我很高兴。 你有一个非常舒适的房子和一个舒适的地窖... ";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//钥匙
			dialog.text = "还有, 请接受这10万比索的微薄款项和这把步枪。 它曾经忠实地为我服务, 也会很好地为你服务。 ";
			link.l1 = "我不拒绝这样的礼物! ";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//打开药店
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // 打开房间
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//到吉诺房间的定位器
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "在楼上的房间里你会找到一个年轻的自然哲学家。 他是我认识的最好的药剂师。 正是他制作了这些混合物, 帮助你在几天内康复。 照顾好他的津贴, 他的知识将以利息补偿你所有的费用。 ";
			link.l1 = "我自己的私人书呆子? 很好, 我会照顾他的。 ";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "现在我得说再见了。 我要去地下室收拾我的东西。 明天我就不在这里了 - 我要离开安提瓜。 我很高兴见到你, 也很高兴你在我这边而不是我的敌人那边。 ";
			link.l1 = "我也很高兴见到你, 约翰。 也许我们会再见面... ";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "这辈子不会了, 我的朋友。 我要去收拾行李了。 再见, " +pchar.name+ "! ";
			link.l1 = "再见, 约翰! 祝你好运! ";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
			CheckPortugalHWIC();
		break;
		
		// 真理卫士
		case "guardoftruth":
			dialog.text = "啊, 好先生, 别听这些愚蠢的传言。 那里没有人。 那是我的实验室, 正在配制合剂, 你知道的... ";
			link.l1 = "别开玩笑了, 约翰。 吉诺.格维内利这个名字你有印象吗? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "嗯... ";
			link.l1 = "啊哈! 我从你眼里看出来了 --我是对的... 他就住在那里, 而且你在为他准备草药! ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "先生, 我再告诉你一次 --这里没人。 ";
			link.l1 = "别找借口了, 约翰。 我不会伤害你的炼金师 --但如果圣地亚哥的文森特神父找到他, 我就不敢保证了。 审判官已经计划派他的‘多米尼.卡内斯’到安提瓜了... ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "你想从他那里得到什么? ";
			link.l1 = "只是谈谈。 他有对我很重要的信息。 我保证不会把他交给宗教法庭, 也不会伤害他。 ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "吉诺是个善良的人。 别相信文森特神父告诉你的任何关于他的话。 记住 --我会保护我的炼金师。 ";
			link.l1 = "我向你保证。 这还不够吗? ";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "那你上楼吧。 门是开着的。 希望你能信守诺言。 ";
			link.l1 = "放心, 我会的。 ";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// 炼金术套件
		case "alchemy":
			dialog.text = "船长, 你不想了解一下炼金术吗? 这可能对你很有用。 ";
			link.l1 = "抱歉, 我的职业有些不同。 我习惯手握剑柄 --而不是烧瓶或试管。 ";
			link.l1.go = "alchemy_exit";
			link.l2 = "'天地之间存在着更多的事物, 超出你的哲学想象.'当然想了解。 需要什么? ";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "如你所愿。 我只是提议... ";
			link.l1 = "... ";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "你应该学会自己混合草药。 但没有炼金工具包你是不会成功的。 看看这个包。 里面有初学者需要的一切 --试管。 烧瓶。 蒸馏器。 刮刀。 玻璃管。 燃烧器和很多类似的东西... ";
			link.l1 = "非常有趣! 我能用它制作什么? ";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "嗯, 你不能把铅变成黄金, 但你可以根据各种配方混合原料, 从而获得药水和其他有用的东西。 ";
			link.l1 = "配方? ";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "没错。 要制作药水或物品, 你必须知道配方。 配方可以从商人那里购买或在任何地方找到。 一旦你研究了一个配方, 你就应该收集所需的每一种原料, 并严格按照说明操作\n使用你的炼金工具, 找到或购买研钵和杵, 寻找坩埚, 可惜我没有多余的可以给你。 草药。 烈酒。 药水。 矿物。 废料 --只要你有正确的配方和工具, 一切都可以用。 ";
			link.l1 = "非常有趣。 这个工具包你要多少钱? ";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "两万比索。 这是一个非常好的工具包, 很快就能回本。 ";
			link.l1 = "你在嘲笑我吧? 一个装玻璃器皿的手提包要价相当于一艘小帆船? 不, 我不要。 ";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "我同意。 我觉得尝试自己制作东西会很有趣。 ";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("你获得了炼金工具包。 ");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "我绝对相信你不会后悔这个购买。 毫无疑问, 根据需要自己制作药水比每次去草药摊零买要划算得多。 此外, 并非总能买到你需要的所有东西。 ";
			link.l1 = "我们开始学习吧。 我想我能做到! ";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("要制作自己的草药和护身符, 你必须拥有炼金术技能! ");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> 处理试图偷宝箱的反应模块
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是个" + GetSexPhrase("小偷, 先生! 卫兵, 抓住他","小偷, 女士! 卫兵, 抓住她") + "!!!", "看看那个! 我一沉思, 你就决定检查我的箱子! 抓住那个小偷! ", "卫兵! 抢劫! 抓住那个小偷! ");
			link.l1 = "该死的! ";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- 处理试图偷宝箱的反应模块
	}
}