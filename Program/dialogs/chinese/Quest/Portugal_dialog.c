void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "错误。 告诉开发者。 ";
		link.l1 = "好的。 ";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "哦, 又一个勇敢的水手! 我了解你们这种人, 我这只该死的眼睛就是为你准备的, 哈! 问问我为什么? ";
			link.l1 = "我会问你别的事情, 是关于你欠当地... 嗯, 场所的女主人的债务。 她让我提醒你这笔债务, 我建议你做点什么, 否则她明天就得让卫兵来做同样的事。 ";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "当地场... 哦, 该死! 约翰娜, 她不能这样对我! 你确定吗? 她真的说过会为了几个该死的硬币把我送进禁闭室? ";
			link.l1 = "绝对确定。 她就是这么说的。 我想我的任务完成了, 再见, 阿文戴尔先生。 ";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "等等! 请等等! 你看起来像个经验丰富的船长。 你肯定有一些硬币, 我破产了, 只有好心的老酒保看在我们老交情的份上让我赊账喝酒。 听听我的提议... 建议! 你帮我还债务, 我会给你分一杯羹\n有一笔生意... 非常赚钱的生意, 去他的我和我的屁股! 我对着该死的锚发誓, 相信我, 船长 --不管你叫什么名字! \n只要偿还一小笔债务, 一万比索, 你就有机会赚到足够的硬币买下整个新该死的世界的妓院! 你觉得怎么样? 你给我, 我给你, 像诚实的人那样... ";
			link.l1 = "一个承诺宝藏的破烂家伙。 饶了我吧, 我不为你这样的人做慈善。 找到钱, 否则你很快就要住在堡垒的禁闭室里了。 再见! ";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "一杯羹? 我为什么要相信一个醉鬼的话? 就因为想象中的承诺? ";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "听我说, 船长! 嗝, 如果我在撒谎就毙了我! 但我说的是实话! 想想看, 如果你发现我在撒谎, 你就用腰上挂着的那把漂亮刀剖开我的肚子! 该死, 刀柄的价值比我那可怜的债务贵五倍! 所以你怎么说? 你没什么可失去的! ";
			link.l1 = "我受够了你的演讲。 再见。 ";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "好吧, 雨果... 我冒险相信你说的废话。 但记住, 等我回来你得说服我, 确保我的钱没有白费, 否则你就麻烦了。 ";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "不需要威胁, 我明白。 我向你保证, 船长! 我们会发财的! 等这笔该死的债务还清了, 我们再谈... 对! 我们会的! 不会让你吃亏的! ";
			link.l1 = "好吧, 我会帮你还清债务, 但你最好祈祷, 雨果.阿文戴尔, 你的‘提议’能让我满意。 ";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "船长, 尽快回来 --这生意可能会跑掉。 ";
			link.l1 = "是是, 我很快就会还清你的债务。 ";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "你回来了, 船长! 看在风暴和该死的雷电的份上, 很高兴见到你! 我的债务怎么样了? ";
			link.l1 = "我已经处理了, 现在轮到你了, 雨果。 告诉我你的故事, 尽量让它稍微可信一点! ";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "别担心, 船长! 你知道我是赏金猎人吗? 或者... 曾经是。 我想我运气不好。 也许魔鬼本人及其所有行为都不如我失败。 我在上一份工作中失去了一切... 船员跑了, 我不得不因为债务卖掉船... ";
			link.l1 = "我已经知道你那英勇的过去。 直接说生意, 雨果, 别挑战我的耐心。 ";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "是是, 船长... " +GetFullName(pchar)+ ", 对吗? 我也知道一些关于你的事。 但该死的, 这很重要。 你听说过葡萄牙人巴托洛梅奥吗? ";
			link.l1 = "葡萄牙人巴特? 我当然听说过。 每个人都听说过。 据我所知, 他是个海盗。 屠夫和败类。 他在你的故事里扮演什么角色? ";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "他在故事里占该死的主要部分! 我追踪他一年半了。 荷兰公司悬赏他的人头, 价格很高。 但我失败了, 失去了一切。 最近公司把活捉他的价格提高了三倍, 该死的只要活的! ";
			link.l1 = "有充分的理由, 活捉他不是小菜一碟。 不管怎样, 我为什么要关心这个, 雨果? 看来你想坑我! ";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "我甚至没打算坑你, 船长! 你知道, 当地的彼得.范.斯塔尔医生, 一个非常好的人, 给了我一剂治头痛的药水! 所以, 医生几乎三天没回家了, 而且... ";
			link.l1 = "雨果, 我的耐心快没了! 我答应那位女士不会用刀刺你, 但我的拳头明天就能让你的头好受! 我发誓明天没有药水能治好你的头! ";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "等等, 船长! 求你了! 听我说, 我在医生家附近看到几个人, 我认出他们了。 他们是‘信天翁’号的人, 该死的葡萄牙人的护卫舰! 其中一个在谈论他们船长的健康! 现在明白了吧, " +pchar.name+ ", 巴托洛梅奥在这里, 在这个城市! 就在我们眼皮底下, 他要么受伤了, 要么生病了, 所以他们需要一个该死的医生! \n我怀疑葡萄牙人没把全体船员带到这里, 但我不能独自开始这场混乱! 你肯定知道如何使用你那该死的剑! 带几个强壮的家伙, 我们会找到那只老鼠! 然后抓住他, 交给当局! \n两千枚好金币就到我们口袋里了! ";
			link.l1 = "不, 雨果, 我受够了你的废话。 我不会参与这场混乱, 即使你是对的。 再见。 ";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "嗯, 有意思。 你知道他藏在哪里吗? 如果成功了我们可以讨论分成, 但如果你说的是真的, 我们必须现在就赶紧! ";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "不, 我不知道他在哪里, 船长。 我太害怕了, 不敢跟踪这些家伙。 如果独眼龙看到我... 呸! 但我们一起, 加上你的人, 我们可以搜查整个城镇, 召集你的人, 开始吧! 该死的, 荷兰金币在等着我们! 这种该死的机会一生只有一次, 咬我一条鲱鱼! ";
			link.l1 = "值得称赞的热情... 我希望你能从桌子旁站起来, ‘伟大的’赏金猎人。 我要立即开始搜查, 如果你想的话可以跟着我, 别太烦我。 ";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "是是, 船长, 让我喝完这杯酒就加入你... 我们从哪里开始? ";
			link.l1 = "哪里? ! ... 我要走了, 不管有没有你。 ";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "找错房子了, 伙计。 现在滚蛋! ";
			link.l1 = "嗯。 我觉得这就是正确的房子... ";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "好吧, 我警告过你... ";
			link.l1 = "... ";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "满帆前进, 高高飘扬, 儿子们... 准备大炮! ... 啊-哈-哈... 哦我的美人... ";
			link.l1 = "嗯, 他还活着算幸运... ";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "哦, 上帝, 你是谁? 请放下武器! 这里有个病人! ";
			link.l1 = "你这个‘病人’杀的人比你这辈子见过的还多, 医生。 滚开! ";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "他是我的病人, 甚至站不起来! 你没看见吗? 求你了, 放下刀! 我求你了! ";
			link.l1 = "他到底怎么了, 该死的! ? ";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "我想都是因为他的伤口, 被有毒的加勒比武器击中... 带他来的人说如果他死了, 我也得死! 但我已经尽力了, 告诉他们! ";
			link.l1 = "别担心那些人, 医生。 我的人会盯着你的房子, 我得去见总督。 我想他会高兴得尿裤子。 在我回来之前别离开这里, 医生。 ";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "我不会离开的, 别担心。 我们还是把他交给当局, 结束这场噩梦吧。 ";
			link.l1 = "当然, 我这就去。 ";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "我们做到了, 船长! 我们找到他了, 很快就会发财, 就像我告诉你的! 我们的计划是什么? ";
			link.l1 = "希望如此, 雨果。 不管怎样, 还没结束。 我想我得去见总督, 讨论我们的奖励? ";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "不不不, 船长! 别去找那个该死的托马斯! 相信我, 这个恶棍会夺走我们的囚犯, 如果我们幸运的话, 他会请我们喝杯咖啡! 总督大人是个可疑的人, 所以如果你想得到全部奖励, 就必须航行到库拉索! 否则葡萄牙人会被带到堡垒, 我们会像乞丐一样被赶走! ";
			link.l1 = "好吧, 如果你真的确定... ";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "我确定, 船长, 该死的确定! 但记住, 巴托洛梅奥的人一定在镇上某个地方, 我们也不想引起驻军的注意, 这是肯定的! 我们得决定如何把葡萄牙人弄到你的船上, 以及如何不引人注目地做到这一点。 ";
			link.l1 = "好的... 我不想在去威廉斯塔德的路上和他的护卫舰战斗。 有什么想法吗? ";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "是的, 我有一个。 我们首先需要为他找一套更高贵的衣服, 然后把他从后门拖出去, 假装成一个喝醉的军官! 没人会怀疑这是个该死的海盗, 相信我! ";
			link.l1 = "嗯, 我不确定, 但反正我们也没有更好的计划。 我会试着为我们的‘乘客’找些漂亮的布料。 你留在这里, 看好巴特和医生。 ";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1天
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "别担心, 船长。 葡萄牙人在我可靠的守卫下, 呵呵... ";
			link.l1 = "我希望如此... ";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "我没看到士兵, " + GetAddress_Form(NPChar) + "。 他们在哪里? 你说过一旦你告诉他们情况, 他就会被逮捕。 那么为什么士兵还没来? ";
			link.l1 = "不会有士兵了, 范.斯塔尔先生。 我要自己完成这项工作, 必须尽快把你的病人带到库拉索。 ";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "船长, 听着, 我治不好他的伤, 只能稍微退烧。 他大部分时间都昏迷不醒, 语无伦次, 毫无疑问, 即使没有任何干扰他也会死, 海上的颠簸几天内就会要了他的命。 我会给你一些有助于... ";
			link.l1 = "不, 医生, 你和我们一起航行。 首先, 我不擅长医学, 其次, 我怀疑你想留在这里, 向葡萄牙人的手下解释他们的船长去了哪里? ";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "... 是的, 我想你是对的。 但要知道这个海盗的生命力非常顽强, 我见过一些人只被印第安人的武器划了个小伤口, 不到三天就都死了。 据他的‘朋友’说, 他已经这种状态一个星期了! 尽管如此, 我敢肯定他在公海的船上只能存活很短的时间。 三天, 不能再长了! \n我们只有这么多时间。 ";
			link.l1 = "即使是鸟也无法在三天内到达库拉索。 但我想我知道该怎么做! 我有个... 朋友, 他住在安提瓜的圣约翰。 他知道如何治愈致命伤口。 他是现在唯一能帮助我们的人。 我们的目标很简单 --在葡萄牙人死前到达那里。 收拾东西, 医生, 我们立即起航, 接下来转移你的病人! ";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //改变模型
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//暂时为测试打开吉诺的房间, 之后移除
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "真遗憾, 船长。 我们失败了, 看不到那该死的金子了。 再见。 ";
			link.l1 = "再见, 雨果。 ";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//打开地点
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "... ";
			link.l1 = "医生, 让你的病人准备下船。 长艇准备好了。 快点! ";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "我这就来, " + GetAddress_Form(NPChar) + "。 ";
			link.l1 = "... ";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//移除计时器
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//7天后不到达 --葡萄牙人死亡
		break;
		
		case "Avendel_Room":
			dialog.text = "这房子里该死的药水味熏死人! 如果葡萄牙人在这里死了, 那才叫奇怪, 光是闻这味道就能治愈任何疾病! \n而且多亏了这股恶臭, 他的船员很容易就能找到我们! ";
			link.l1 = "雨果, 别跟我开玩笑了。 我在街上留了几个人监视房子, 但我们的‘客人’再多加一个守卫也无妨。 看好他, 尽量别骂人, 否则吉诺会让你喝他的药水, 我肯定他能治好你的毛病。 ";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "别担心, 船长! 我会以最警惕的方式看守我们的‘钱’, 即使他健康的时候也跑不掉! 我求你了, 别再弄药水了! ";
			link.l1 = "看, 你想好好说话的时候也可以。 保持警惕, 我得走了。 ";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "已经要走了, 船长? 太好了! 是时候了! 我看到几个该死的... 可疑的家伙在街上。 他们看起来不像葡萄牙人, 不过他们在找什么东西, 我们得小心, 船长! ";
			link.l1 = "好的, 谢谢你的警告, 雨果。 我们去船上吧。 ";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//安置葡萄牙人
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "船长, 我们等这次会面等得太久了! 你旁边的是谁? 葡萄牙人巴托洛梅奥, 哈, 看来‘大胆的皮埃尔’是对的 --就是他! 离远点, 船长, 我们要带走他, 没人会受伤。 ";
			link.l1 = "抱歉, 先生, 但你他妈的是谁? 让开, 否则你们谁也见不到明天! ";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "哦, 多么有威胁性的家伙, 看看他, 伙计们! 哈哈哈! 听着, 小子, 别挡在利奥.科德和他的钱之间! 我们追踪葡萄牙人快半年了, 现在终于抓到他了。 所以放下你那牙签似的刀, 趁你还活着赶紧滚! 我们没那么贪心, 死人也行, 哈哈哈! ";
			link.l1 = "够了。 让我们跳舞吧, 先生们! ";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "我就知道这里有问题! 干得好, 船长! 但该走了, 该死的利奥.科德在这里有很多匪徒, 还有一艘好船! 我们得离开这个岛! ";
				link.l1 = "说得对, 雨果, 我很高兴没有子弹打中你躲的那个洞。 ";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "真遗憾, 船长。 我们失败了, 看不到那该死的金子了。 再见。 ";
				link.l1 = "再见, 雨果。 ";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "我... 我在保护我们的后方, 船长! 没有我你也做得很好, 但如果有人从街道另一边袭击我们怎么办? 你就没有时间跑向船了。 ";
			link.l1 = "也许这就是你在这行没成功的原因? 不管怎样, 别说了, 我们得去船上! 时间不多了! ";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "船长, 葡萄牙人情况很糟糕, 我们得停下来! ";
			link.l1 = "所以我们才来这里, 范.斯塔尔先生, 我们的旅程快结束了。 我会在酒馆租个房间, 我们的囚犯在那里待几天。 ";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "船长先生, 我会照顾葡萄牙人, 他需要充分休息。 ";
			link.l1 = "我知道了, 医生, 没关系。 该死的, 我还要照顾这个海盗多久? 这对他不好, 他需要的不是这个! 看来我被雇来当保姆了... 啊, 抱歉, 医生, 只是太过分了... 我过会儿见。 ";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "先生, 你是" +GetFullName(pchar)+ "船长吗? 今天刚抵达我们港口的那位? ";
			link.l1 = "没错, 有什么可以帮忙的? ";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "我们殖民地的总督, 雅克.迪勒.杜.帕凯先生在等你。 事情很紧急! ";
			link.l1 = "好的, 先生, 我今天会去拜访总督大人。 ";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//打开地点
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "我们到达马提尼克了, 船长! 我们的钱不远了... ";
			link.l1 = "只要葡萄牙人能活到威廉斯塔德。 雨果, 我得去船上, 所以你得看好医生和他的病人。 ";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "去船上? 为什么? 能借给我几个你的人帮忙吗? 你不在的时候出了事怎么办? ";
			link.l1 = "抱歉, 不行。 我怀疑这里有什么能威胁到你。 驻军已经警戒了, 街上的士兵比平时多, 如果出了问题就叫他们。 他们在岛不远处看到一艘大船, 可能是海盗船。 总督大人让我用我的船巡逻, 加强岛上的防御。 ";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "一艘船? 海盗船? 可能是‘信天翁’号! 或者是我们老朋友利奥.科德的同伙! ";
			link.l1 = "或者只是普通的海盗船。 不管怎样, 雨果, 如果这艘船是冲着我们来的, 我最好带着当地巡逻队一起面对, 还能拿总督的金币。 这比在剩下的旅程中提防背后好多了。 如果警报是假的, 那也省得我在酒馆里坐几天。 ";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "想想吧, 船长, 在葡萄牙人的护卫舰可能在附近巡航时, 离开该死的... 葡萄牙人不管, 这明智吗? 你为了总督的钱, 在拿我们的奖励冒险! ";
			link.l1 = "够了, 雨果.阿文戴尔! 我是这里的船长, 最终决定由我来做! 所以照我说的做。 去酒馆, 看好医生和葡萄牙人, 直到我回来。 ";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//打开地点
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//关闭酒馆
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "你终于回来了, 船长! 恐怕我有坏消息 --葡萄牙人和医生都不见了! ";
			link.l1 = "怎么会? ! 那你当时在干什么, 笨蛋? ! ";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "我敢打赌那艘船是‘信天翁’号。 我看到了葡萄牙人的人, 他们进了酒馆, 我... 我就跑了。 对不起, 但遇到‘独眼狗’就算给再多钱我也受不了! ";
			link.l1 = "该死! 至少告诉我酒馆里发生了什么? ";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "我说过我什么都没看见。 我一看到弗朗茨.加尔克和他的人就从厨房跑了... 太近了! 事情发生在昨天晚上, 我不知道怎么告诉你... ";
			link.l1 = "是啊, 你真是个勇敢机智的人... 好吧, 再给你一次机会, 我们去找他们。 我救这个混蛋太久了, 现在我把他当成我的财产。 我们还有时间追上他们, 所以从酒馆开始, 也许有人看到的比你逃跑的脚后跟多。 去, 准备好! ";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以加速时间
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //计时器
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//移除医生
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//隐藏葡萄牙人
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//关闭房间
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "你听到了吗, 船长, 他在说‘独眼狗’, 我最近告诉过你。 那个口齿不清的卡斯蒂利亚人是埃尔南多.巴斯克斯, 该死的唐 --维拉克鲁斯的屠夫, 我没看见他! ";
			link.l1 = "放松, 雨果。 我肯定巴托洛梅奥还在岛上, 他可能好点了, 但仍然很虚弱。 我想我知道去哪里找他! 我们会抓到他们的, 我不会放弃我的奖励。 如果你不是懦夫就跟着我, 还没结束。 ";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//打开快速传送
			pchar.questTemp.Portugal = "PortugalLeFransua";//去勒弗朗苏瓦
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//禁止军官进入
		break;
		
		case "LeFransua_pirate":
			dialog.text = "你问太多问题了, 船长... 等等, 你不是菲利普斯堡那个狡猾的家伙吗? 你躲着我们跑了太久, 现在看 --你在这里... ";
			link.l1 = "你们真倒霉, 人渣! ";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //移除计时器
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... 你, 可怜的螃蟹屎, 你会告诉我们一切, 相信我, 你这该死的老鼠! 然后你会被吊在桅杆上代替顶帆... 你他妈的是谁? 该死的这些猿猴不可信! 总是得自己做所有事... ";
			link.l1 = "我打扰你们了吗, 先生们? ";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "我喜欢你的时机... 我想我得谢谢你让我活到今天? ";
			link.l1 = "你说得对。 我叫" +GetFullName(pchar)+ ", 而你, 葡萄牙人, 仍然是我的囚犯。 所以别问我问题, 我们得走了。 ";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "等等, 船长... 镇上有很多巴斯克斯的人, 他们不会让我们就这么走的。 给我一把剑, 我们的机会会大得多。 ";
			link.l1 = "你和你的同伙关系不好, 嗯? 好吧, 多一把刀总是好的, 拿尸体上的武器, 离我远点! ";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "别以为我会给你武器, 让你在我转身时打我! 离我远点。 ";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//关闭传送
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "别担心, 船长, 我宁愿死也不愿再落入巴斯克斯手中。 ";
			link.l1 = "好吧, 问题是, 我还不想让你死。 走吧, 时间不多了! ";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "太糟了, 如果我想让你死, 早就帮独眼龙了... ";
			link.l1 = "但你也没帮我, 所以闭嘴, 走! ";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "该死! 是他们! 杀了他们全部! ";
			link.l1 = "又来了... 来吧, 你们这些杂种! ";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//打开传送
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "太棒了! 你杀了独眼狗, 这才叫杰作! 你送多少他的人下地狱了? ";
				link.l1 = "我战斗时没数。 你去哪了, 雨果? ";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "真遗憾, 船长。 我们失败了, 看不到那该死的金子了。 再见。 ";
				link.l1 = "再见, 雨果。 ";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "我... 在确保安全撤退... 可以说是保护我们的后方。 ";
			link.l1 = "好吧, 雨果.阿文戴尔, 你的懦弱超出了我的预期, 你知道那仗对我们有多艰难吗? 我们勉强活下来! ";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "冷静点, 船长... 我承认我在躲。 但我为你找到了这个机会! 记住, 是我带你找到葡萄牙人的! 好吧... 考虑到你合理的愤怒, 我同意只拿三分之一的奖励。 ";
			link.l1 = "太棒了! 你现在还在讨价还价? 不, 我的朋友, 你在这桩生意中的角色结束了! 你把钱留在了圣皮埃尔的酒馆里。 你把它留在那里跑了, 所以现在对你来说结束了。 ";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "船长, 你明显夸张了... 好吧, 我同意四分之一... 五分之一! 百分之十! ";
			link.l1 = "别考验我的耐心! 滚蛋! 我的船员不需要懦夫, 尤其是现在时间紧迫! ";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+ pchar.name+ ", 你不觉得这有点不公平吗? ";
			link.l1 = "因果报应, 雨果... 你已经做出了选择, 再见。 吸取教训, 别再陷入这样的冒险, 显然这不适合你。 ";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // 杰森 比金子更贵
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "扔掉压舱物, 船长? 说得对, 哈... 巴斯克斯还在外面, ‘信天翁’号上有很多人和枪, 我用我漂亮的裤子打赌, 埃尔南多不会让我们逃跑的。 ";
			link.l1 = "嗯, 看来我们得自己去问候他了。 走, 葡萄牙先生, 尽量闭上嘴。 我们尽快起航。 ";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "你在等什么, 该死的? ! ";
			link.l1 = "埃尔南多.巴斯克斯在哪里? 说出来我就饶你一命。 ";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "去你妈的问题! ";
			link.l1 = "你先去... ";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "你来了, 我勇敢的朋友, 我们终于可以好好谈谈了! 恭喜你, 船长 --杀死独眼狗和摧毁‘信天翁’号可不是容易的事! 实际上, 你为救我的命做了这么多... 也许, 我甚至应该感谢你? ";
				link.l1 = "等你在绞刑架上跳舞或者威廉斯塔德为你准备的任何地方时再感谢我吧。 ";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "你来了, 我勇敢的朋友, 我们终于可以谈谈了! 恭喜你, 船长 --杀死独眼狗值得一首荣誉之歌! 实际上, 你为救我的命做了这么多... 也许, 我甚至应该感谢你? ";
				link.l1 = "等你在绞刑架上跳舞或者威廉斯塔德为你准备的任何地方时再感谢我吧。 ";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "难以置信! 你在过去两周里一直在救我的命, 把我带到你家, 在战斗中保护我... 现在你要送我去死? 我很难相信... 实际上, 我现在几乎把你当成朋友了, 哈哈。 ";
			link.l1 = "一个乞求荣誉的海盗? 葡萄牙人, 你在开玩笑吗? 我救你只有一个目的 --让这个凶手和恶棍面对法庭的审判! ";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "我的朋友... 听起来像嘲讽。 但不管怎样你是对的。 我这么做很奇怪, 葡萄牙人... ";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "哦, 够了, 船长。 我打赌你做这一切只是为了得到公司承诺的钱, 为了有幸看到我活着! 别试图装得比实际更诚实, 先生, 这不适合你。 ";
			link.l1 = "只有我能评判自己。 所以我们结束这次谈话吧。 该起航去威廉斯塔德了。 ";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "看来如今人们身上仍能找到一些诚实... 可惜金钱总是干扰 --嗯, 船长? ";
			link.l1 = "从绞刑架上的海盗嘴里听到这话真奇怪, 葡萄牙人。 我会放你走... 别问我为什么, 就在第一个港口滚蛋。 记住, 如果我们再见面, 我不会那么仁慈。 ";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//禁止对话
			pchar.questTemp.Portugal.Villemstad = "true";//交给总督
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "真的吗? 我喜欢这样, 船长! 不命令拿点朗姆酒来吗? 你知道, 只是为了庆祝你的骑士品质。 我们的关系和我的缓刑? ";
			link.l1 = "别开邪恶的玩笑了, 在第一个海岸之前你仍然是我的囚犯。 再见。 ";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//禁止对话
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "我明白了... 那么是绞刑架。 这在意料之中。 那么听着, 船长。 你如此渴望让我活着, 以便稍后正确处决我, 我很欣赏这一点。 我想如果我现在要求你改变主意, 会很愚蠢, 对吗? 如果我给你一些东西作为交换, 你会怎么说? 可以说是一笔交易, 嗯? ";
			link.l1 = "我什么也不会说, 葡萄牙人。 你是海盗和混蛋。 你将在威廉斯塔德为你的罪行负责。 ";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "一笔交易? 你能提供什么? ";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "我不需要你的交易, 就在第一个港口滚蛋。 今天算你走运。 ";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "你知道, 尽管背后有不愉快的原因, 但如此执着地救我的命仍然值得一些感激。 而葡萄牙人巴托洛梅奥知道什么是感激。 现在听着, 在你我相遇的一个月前, 我们俘获了一艘公司的船。 他们像魔鬼一样战斗到最后一个人。 但他们的货舱里只有炮弹和老鼠\n我的船员不喜欢这样, 但我在船长室里发现了一个非常有趣的箱子和文件。 她是一艘信使船, 从亚马逊河某处的矿山运送样品。 纯钻石和红宝石, 一笔真正的财富! ";
			link.l1 = "有趣的战利品... 现在我明白为什么公司对你这么感兴趣了, 但你的故事重点是什么? ";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "我的大副巴斯克斯和弗朗茨.加尔克一直在维持船员秩序, 所以我决定冒险。 我把宝石藏起来不让他们知道, 还烧了文件。 荷兰人在登船时严重损坏了我们的索具, 我们不得不把‘信天翁’号开进北部一个小岛的小海湾。 当全体船员在修理护卫舰时, 我独自深入丛林\n我把宝石埋了起来, 在那种情况下把它们留在船上太危险了。 我的计划是在第一个港口逃离我亲爱的船员, 买或偷一艘小船, 航行到岛上, 收集我的战利品, 然后... 告别我的旧生活! 欧洲, 一座体面的豪宅, 一个辣妻, 你知道剩下的... ";
			link.l1 = "让我猜猜, 出问题了。 ";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "一切都出问题了! 该死的岛原来是一群当地食人族的家园。 我一回到岸边, 他们就袭击了我们。 我们不得不尽快起航, 就在那时我被击中了。 我以为只是擦伤。 \n几天后, 我躺在那里半死, 发着高烧, 显然说了些关于宝石的话。 弗朗茨和巴斯克斯意识到我在岛上藏了东西, 但他们不知道确切位置。 他们不喜欢在那里徘徊, 不断被印第安人射击。 所以这些混蛋把我拖到最近的港口, 因为我们的医生在与荷兰人的战斗中被杀了, 他们需要一个新的。 \n我就是这样到了医生那里, 他们想让我恢复意识足够长的时间来折磨我, 找出宝石的位置。 我相信, 之后他们会把我切成块, 用我多汁的肉喂螃蟹。 ";
			link.l1 = "我不能说我评判他们 --你试图欺骗你的人。 所以我再问一次, 你为什么要告诉我这些? ";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "相信我, 这些狗不是人, 他们现在都在应得的地方 --地狱, 哈哈哈! 作为我自由和生命的代价, 我可以告诉你荷兰宝藏的确切位置。 ";
			link.l1 = "不, 巴特, 你的背叛完全让我相信了你的卑鄙。 威廉斯塔德和合法的报复在等着你。 没交易。 ";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "我应该相信那些宝石存在吗? 不管怎样, 我反正不会损失什么... 交易是这个故事的开始, 也将是它的结束。 我接受你的条件, 葡萄牙人。 ";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "就当是我谦逊的感激吧。 嗯, 我希望知道葡萄牙人巴托洛梅奥的皮在闪亮的比索中值多少钱, 哈! 我知道你的目标完全是实用的, 但还是谢谢你, 船长, 谢谢你所做的一切, 哈哈哈\n是特克斯岛, 海岸不远处的丛林。 找到一棵干枯的。 弯曲的树, 那里只有一棵这样的树。 我把箱子埋在它附近。 所以别忘了带铲子。 狩猎愉快... ";
			link.l1 = "好的, 我会记住的, 你现在可以乘长艇离开我的船了。 再见。 ";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "最后一件事, 船长。 我想那里仍然有很多野蛮人, 但你应该担心的不止他们。 巴斯克斯不在‘信天翁’号上, 对吗? 血腥的唐太聪明了... 在看到他被绞死或脑袋中枪之前, 小心你的背后。 ";
			link.l1 = "谢谢你的警告, 葡萄牙人。 现在你能好心离开我的船了吗... 别考验我的耐心。 ";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //移除计时器
			dialog.text = "哦, 这是谁啊! " +pchar.name+ "船长本人! 想喝一杯吗? ";
			link.l1 = "你知道, 我其实很高兴再次见到你。 但也许我在马提尼克对你太粗暴了。 ";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "不管怎样, 船长! 发生的事已经发生了... 但说实话, 我确实有理由让你把我赶走... 但是嘿, 你不会相信今天菲利普斯堡来了个谁! ";
			link.l1 = "别告诉我是... ";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "不不, 船长, 不是葡萄牙人。 也不是某个受伤的混蛋。 比那好得多! 是埃尔南多.巴斯克斯... 血腥的唐本人! 他作为当地总督的客人已经待了几天了。 ";
			link.l1 = "巴斯克斯? 总督的客人? 我现在明白了。 雨果, 多告诉我一些, 这到底是怎么回事? ";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "嗯, 我知道很多... 但多亏了我们的航行, 我又破产了。 也许你对这些信息的需求值得几个比索? ";
			link.l1 = "雨果, 你还是个敲诈者和无赖! 说出你知道的, 看在我们老交情的份上, 拿5000比索。 ";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "不知怎么的, 我并不惊讶。 给, 拿10000比索, 你最好希望你的信息值这么多钱! ";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "我给你一个更好的提议。 加入我的船员怎么样? 我觉得你有创造和发现有利可图交易的天赋, 所以如果你厌倦了假装是个勇敢的战士 --非常欢迎你担任我的财务官。 ";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "不, 船长, 不能这样! 你用那个该死的葡萄牙人捞了一大笔钱, 我确定。 所以就当那是我的份额, 别那么贪婪。 15000枚硬币, 一分不能少! ";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "啊, 去你的, 拿去吧! ";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "嗯, 人们说贪婪是好的... 这对你来说是不是太多了, 嗯? ";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "这才是给我的奖励! ... 听着, 巴斯克斯和我坐同一艘船航行, 但当我在清理甲板作为旅途的报酬时, 他却在船舱里休息, 所以谢天谢地, 我们很少见面, 他也没认出我。 但我立刻开始跟踪这个魔鬼... 他身上发生了一个有趣的故事。 ";
			link.l1 = "继续! 他在总督府做什么? ";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "我知道的不多, 但他到达后几天, 驻军就处于戒备状态, 那艘巨大的战船突然起锚, 匆忙离去, 我相信是向西北方向航行。 整个城镇都沉浸在猜测和流言中... ";
			link.l1 = "所以那就是我遇到的船! 很有趣... 别偏离主题, 雨果, 请继续你的故事。 ";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "嗯, 正如我所说, 船开走了, 巴斯克斯成了我们总督马丁.托马斯的客人。 我有时在镇上看到他, 他总是和几个士兵在一起。 我不知道那是他的护卫还是护航队, 哈哈。 但只有住在官邸里的人才能告诉你更多关于唐的事情。 ";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "也许你是对的。 但我们有过协议, 记得吗? 别扮演英雄, 去我的船上等我回来。 我会试着和我们好客的总督谈谈。 ";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "嗯, 那很有趣。 你真的帮了我, 雨果。 喝你的朗姆酒, 剩下的与你无关。 ";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "你是认真的吗, 船长? 你怎么了? 你用枪指着我的脸把我赶走, 现在又提出这样的提议? ";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "忘了吧, 我当时不是我自己, 对不起, 我想是贪婪吞噬了我。 给, 拿10000比索, 告诉我你知道的关于巴斯克斯的事, 我很着急。 ";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "也许我应该为此道歉。 你是个可怜的战士, 但你对硬币很在行。 我重复我的提议, 你觉得怎么样? ";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "我能说什么... 我会同意, 但只有在我得到我的份额之后, 船长。 百分之十, 记住? 你从那个恶棍那里得到了两千, 所以如果你让我加入你的船员, 你最好先还清你的债务。 百分之十, 不要争论! ";
			link.l1 = "你真是个骗子, 雨果。 我现在身上没有那么多, 但我很快就会回来。 待在这里。 ";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "我希望你的商业头脑能证明我的期望是正确的, 哈! 拿你的份额! ";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "这是你的决定, 船长。 我会在这里待一段时间。 如果你改变主意, 就回来。 ";
			link.l1 = "好的, 雨果。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "你改变主意了吗, 船长? 那我等着我的钱。 ";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "拿你的硬币, 你这个无赖哈哈! ";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "我还没有那么多钱。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 25;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //移除计时器
			dialog.text = "日安, 船长。 想要点什么吗? ";
			link.l1 = "不不, 我只是在等, 托马斯先生什么时候有空? 我在等觐见... 是的。 告诉我, 大人真的把著名海盗埃尔南多.巴斯克斯当作朋友吗? ";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "别担心, 先生, 他应该随时有空, 当然不是, 先生! 这个强盗向当局投降了, 但不知怎么的没有被绞死。 也许是通过背叛他的老犯罪伙伴来买命... 我不确定。 他在这里被关押了几天... 那是一场噩梦, 先生! 那个披着人皮的野兽住在我们的豪宅里! ";
			link.l1 = "真是一场噩梦! 那个野兽能告诉托马斯先生什么来避免绞刑? 我甚至无法想象! ";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "我也不知道, 但我可以偷偷告诉你, 当大人摆脱这样的客人时, 所有仆人都很高兴... ";
			link.l1 = "摆脱了他? 他终于得到应有的惩罚了吗? ";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "不完全是。 然而, 几天前他被带到一艘驶往威廉斯塔德的军事 brig 上。 看来托马斯先生对这个恶棍失去了兴趣, 他似乎试图欺骗他\n还有人说, 他的前船长被抓住了 --葡萄牙人巴托洛梅奥! 想想看! 看来公司想把他们一起绞死。 传言审判将在一个月后, 但为什么要等那么久? ";
			link.l1 = "葡萄牙人? ! 嗯... 谢谢你的陪伴, 朋友... 看来托马斯先生现在有空了, 我该告辞了。 ";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //改变模型
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
			SetCharacterPerk(sld, "SwordplayProfessional");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//禁止军官进入
		break;
		
		case "Vaskez":
			dialog.text = "现在你们死定了... 你们两个! ";
			link.l1 = "... ";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "现在这是我没想到会见到的人, 船长! 但这看起来不像是友好的访问, 所有这些血。 噪音和枪战, 或者这是某种有烟花的庆祝活动, 嗯? ";
				link.l1 = "别开你那邪恶的玩笑了, 葡萄牙人。 我只是不喜欢你如何利用从我这里买来的自由。 我费了那么大劲救你这个可怜的屁股, 不能让你在我们分手后就这么愚蠢地被抓住! ";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "嗯, 我很无聊! 所以我来这里拜访你。 你在这里舒服吗, 朋友! ";
				link.l2.go = "Portugal_free_1a";
				// <—— legendary edition
			}
			else
			{
				dialog.text = "小心, 朋友! 呃, 真遗憾我帮不了你! ";
				link.l1 = "... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "所以高贵有时不受硬币影响, 嗯? 哈... 小心, 就在你后面! ";
			link.l1 = "啊, 又来这一套! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <—— legendary edition
			dialog.text = "所以高贵有时不受硬币影响, 嗯? 哈... 小心, 就在你后面! ";
			link.l1 = "啊, 又来这一套! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "我警告过你这家伙是个麻烦! ";
			link.l1 = "他差点从背后把我射死! 他是怎么通过的? ";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "我看到他有一个撬锁工具, 似乎是有人给他的... 他在底层总是有联系。 好吧, 船长, 我认为我们应该离开这个地方, 你不同意吗? ";
			link.l1 = "还用你说! 好吧, 在整个驻军到达之前, 我们赶紧走。 我马上打开你的锁... ";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//允许保存
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "你知道, 船长, 这新鲜空气... 只有在你被当地巡逻队发现你的船艇后, 在 dungeon 里待上几周, 你才会开始珍惜它。 我想, 我仍然欠你救我的人情。 ";
			link.l1 = "没必要, 葡萄牙人。 我不是一个高尚的骑士, 我只是... 我做我认为正确和需要做的事。 ";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "哈, 这是一个完美的品质! 但我坚持, 给, 拿着... 这是我在监狱里唯一能藏起来的东西... 是的, 你猜对了。 这是我的护身符。 它总是在海上给我带来好运。 你是一个优秀的水手, 你或你的领航员一定能用上它, 我确信。 ";
			link.l1 = "是的, 有了那个护身符, 你足够幸运地直接落入荷兰人手中。 ";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "嘿! 我还活着, 不是吗? 而且你知道, 我不再在监狱里了。 拿着, 船长, 是时候让护身符为你服务了。 我再次感谢你! ";
			link.l1 = "那么再见了, 葡萄牙人。 还有, 请尽量远离绞刑架! 就为了我辛苦的工作, 哈哈! ";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("你收到了护身符");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//允许军官进入
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // 杰森 比金子更贵
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}