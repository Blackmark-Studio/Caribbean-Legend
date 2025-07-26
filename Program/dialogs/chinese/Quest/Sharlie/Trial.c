// 加勒比风俗任务的NPC对话
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你想要什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 热拉尔.勒克鲁阿
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; // 取下计时器
			dialog.text = "下午好。 你一定是" +GetFullName(pchar)+ "吧? ";
			link.l1 = "您说得对, 勒克鲁瓦先生。 " +GetFullName(pchar)+ "船长为您效劳。 莫斯科人法迪向我推荐了您... ";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "是的, 是的。 我亲爱的朋友法迪详细描述了您和您的情况。 我一看到门口的您就知道是您。 告诉我, 船长, 您有什么样的船? ";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "啊... 目前我没有船, 先生... ";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "我有一艘" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")) + ", 她的名字是" + pchar.ship.name + "。 ";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "哈! 那么如果您没有船, 您算哪门子船长? 抱歉, 先生, 那样的话我没有工作可以提供给您。 一切顺利, 请代我向法迪问好! ";
			link.l1 = "嗯... ";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "我目前没有船";
		break;
		
		case "lecrua_badship":
			dialog.text = "哦, 那可不行。 先生, 那不是船, 那是条船! 唉, 先生, 您不符合要求。 代我向法迪问好, 日安! ";
			link.l1 = "嗯... ";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "我的船对他来说不够大";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "我们已经讨论过所有事情了, 先生。 不是吗? ";
			link.l1 = "是的, 勒克鲁瓦先生... 我这就走。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "太好了。 那样的话您很适合我。 您准备好立即出海了吗? ";
			link.l1 = "是的, 先生, 我准备好了。 我需要做什么? ";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "您必须将一小批火药和炸弹送到法属伊斯帕尼奥拉的太子港。 指挥官已经等了一段时间了, 所以不要浪费时间, 您还剩大约十天\n尊敬的" + GetFullName(sld) + "会负责将其运送并装载到您的船上。 完成工作后, 指挥官会付给您五千八里亚尔。 ";
			link.l1 = "这就是全部工作吗? ";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "哦, 绝不是, 先生。 当您带来弹药时, 指挥官会向您解释真正的工作。 这批货物只是您前方工作的一小部分。 但不要害怕, 如果您做得好, 会赚很多钱。 ";
			link.l1 = "我全神贯注地听着, 先生。 我的船已准备好装载货物。 ";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "那么我们就不要浪费时间了, 船长! 前往您的船并准备起航。 ";
			link.l1 = "我这就去! ";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition 休闲模式跳过
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // 计时器
			else NewGameTip("探索模式: 计时器已禁用。 ");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // 计时器
			// 货物
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra 与迭戈的复活节彩蛋
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// 关闭全局地图上的所有敌对遭遇
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// 弗洛里安.肖克
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition 取下计时器
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "先生, 我能为您做什么? ";
			link.l1 = "下午好, 船长。 我猜您是弗洛里安.肖克? ";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "我是。 如果我没弄错的话, 您是来自太子港的邮船? ";
			link.l1 = "是的, 我为您带来了十五门大炮。 截止日期快到了, 我勉强赶上... ";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "嗯。 先生, 您的幽默感真奇怪! 出于某种原因, 我没有看到从您的船上卸下十五门大炮... ";
				link.l1 = "嗯, 您看, 我们的船漏水了, 不得不把一些货物扔到海里... ";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "很高兴见到您, 船长? ..";
				link.l1 = "" +GetFullName(pchar)+ "。 " +GetFullName(pchar)+ "船长。 ";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "很高兴认识您。 我们不要浪费时间, 把这些大炮装上船吧。 这不会容易, 所以我需要您的人帮忙。 ";
			link.l1 = "我们会处理的。 你们那里, 把滑轮组安装在桅杆上! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "你这个该死的白痴! 如果你连这么简单的任务都处理不了, 下次暴风雨你肯定会沉没。 回到你的船上, 船长, 做些你更擅长的事情, 比如给贵族女士送花。 最好还是航行回欧洲, 把新世界留给真正的男人。 日安, 先生! ";
			link.l1 = "但是... ";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "呼, 这是个累人的工作! 感谢您的服务, 船长! 拿着您的报酬, 二百杜布隆。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("你收到了200杜布隆。 ");
			PlaySound("interface\important_item.wav");
			dialog.text = "但这还不是全部, 船长。 您想再赚二百五十金双埃斯库多吗? ";
			link.l1 = "听起来很有希望, 但这取决于您要我做什么, 先生。 ";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "我不会撒谎, 这很危险。 正如您可能已经知道的, 我在等待一艘载有贵重货物的西班牙重型大帆船。 这艘船被停在船坞进行维修。 根据我的消息来源, 她本应昨天起航, 但没有发生\n此外, 我在贝洛港的特工没有到达约定地点提供我一直在等待的最新消息。 我怀疑西班牙人逮捕了他。 我会付钱给您潜入贝洛港, 查明两件事: 为什么大帆船还在那里, 以及我的特工发生了什么。 您加入吗? ";
			link.l1 = "恐怕我缺乏进行这种行动的适当训练。 我是个绅士, 不是间谍。 我自己可能会陷入麻烦, 也无法帮助您。 ";
			link.l1.go = "florian_deck_bye";
			link.l2 = "听起来很危险, 但有利可图。 我愿意冒险。 您的人叫什么名字, 大帆船叫什么名字? ";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "嗯, 您有资格吗? 我理解您。 那么再见, 船长, 再次感谢您的帮助! ";
			link.l1 = "一切顺利, 肖克先生。 ";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "是的, 仔细听着。 我的人名叫西尔万.拉福雷, 但在贝洛港他化名为商人海梅.西利西奥。 大帆船名为'阿拉坎塔拉'。 我建议您在夜间穿过丛林从城门进入城市。 贝洛港的守卫现在非常多疑, 更不用说西尔万的失踪对他是否还活着不是好兆头。 在西班牙巡逻队发现我们之前, 您有两天时间离开这里。 祝您好运, 先生! ";
			link.l1 = "很快见, 肖克先生... ";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;// 关闭地图
			pchar.GenQuest.MapClosedNoBattle = true; // 允许等待和航行
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("探索模式: 计时器已禁用。 ");
			// <—— legendary edition
			//Log_Info("你获得了护身符'吉普赛人的扇子'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "当您慢走时, 守卫的疑心较小! ";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "我们已经讨论过所有事情了, 船长, 不是吗? ";
			link.l1 = "是的。 我这就走。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; // 取下中断
			dialog.text = "事情进展如何, 船长? 您设法发现了什么? ";
			link.l1 = "事情进展不顺利, 肖克先生。 我不太擅长当间谍, 他们很快就发现了我。 在与一些守卫战斗后, 我不得不逃离城市。 我唯一设法发现的是您的人西尔万.拉福雷已经被捕, 被关押在监狱里。 ";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "该死的! 那不好... 您发现了关于大帆船的任何信息吗? ";
			link.l1 = "不, 没有。 ";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "该死。 我真的需要一些关于它的信息。 但这个奖品太丰厚了, 不能放弃! 无论如何, 我会尝试再派一名侦察员过去... 船长, 我请您暂时不要离开我。 我可能需要您的帮助。 您愿意等多一天, 而我去嗅探关于阿拉坎塔拉的信息吗? ";
			link.l1 = "当然, 我会等! 我想弥补那次失败。 ";
			link.l1.go = "florian_9";
			link.l2 = "我不这么认为。 显然我太不擅长这些游戏了。 我要回家了。 ";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "嗯, 那是您的选择。 一切顺利, 船长。 ";
			link.l1 = "再见, 肖克先生。 ";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; // 取下中断
			dialog.text = "事情进展如何, 船长? 您设法发现了什么? ";
			link.l1 = "事情进展不顺利, 肖克先生。 我不太擅长当间谍, 他们很快就发现了我。 我唯一设法发现的是您的人, 西尔万.拉福雷已经被捕, 被关押在某个地方。 ";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "那么前往您的船, 船长。 明天大约同一时间, 或稍晚一点, 您必须来见我。 也许到那时我会发现一些事情。 不要上岸, 在您的船上等我! ";
			link.l1 = "好的。 会的。 ";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "还有船长, 拿着这个钱包。 您的努力毕竟不是完全徒劳的。 至少我们知道可怜的老西尔万发生了什么... ";
			link.l1 = "... ";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);// 关闭岛屿	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("你收到了一个杜布隆钱包");
		break;
		
		case "florian_deck_wait":
			dialog.text = "船长, 我目前没有任何消息。 我们仍在等待... ";
			link.l1 = "好的... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; // 取下中断
			dialog.text = "事情进展如何, 船长? 您设法发现了什么? ";
			link.l1 = "完成了。 您的人, 西尔万.拉福雷被捕了, 被关押在监狱里。 他完了。 ";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "该死的! 太可怕了... 您发现了关于大帆船的任何信息吗? ";
			link.l1 = "是的。 她已经准备好出航一段时间了, 但贝洛港的总督打算将她留在船坞。 现在他在等待一艘名为'普埃布拉'的双桅纵帆船从卡塔赫纳抵达, 为'阿拉坎塔拉'运送火药货物。 根据大帆船上的一名水手说, 他们的火药不够, 总督担心海盗。 ";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "真有趣! ";
			link.l1 = "但如果普埃布拉在三天内不到达, 阿拉坎塔拉将不再等待并起航。 ";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "干得好, " +GetFullName(pchar)+ "船长! 我非常高兴! 拿着您的报酬。 您完全应得的! ";
			link.l1 = "谢谢! 您有任何其他任务给我吗? ";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			Log_Info("你收到了250杜布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "您正在读我的心思, " +GetFullName(pchar)+ "! 是的, 该死的! 由于阿拉坎塔拉火药不足, 我可以让她驶入公海, 然后迫使她进行一场持久战, 他们的火药会比我们先耗尽, 哈哈! \n您应该确保补给双桅纵帆船普埃布拉永远不会到达贝洛港。 我不能靠近海岸, 巡逻队会很容易发现我的护卫舰, 并在我拦截阿拉坎塔拉之前将我赶走\n您可以自己处理普埃布拉。 找到她并摆脱她。 击沉她或夺取她作为战利品, 我不在乎。 只要阻止她到这里! \n如果您成功了, 就去瓜德罗普见热拉尔.勒克鲁阿, 我相信您已经认识他, 不是吗? 他会付给您应得的硬币。 ";
			link.l1 = "成交! 我这就去拦截普埃布拉! ";
			link.l1.go = "florian_19";
			link.l2 = "等一下, 肖凯先生。 事实是我仍然... 这么说吧, 不太习惯海战。 而您是护卫舰的船长, 显然您背后不止一场海战。 如果对您来说不困难, 您可以... 我该怎么说... ";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "很高兴您在这里, 船长。 我刚从我的间谍那里收到信息, 我有一个重要的任务给您。 ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "阿拉坎塔拉已准备好起航, 但大帆船的船长在等待从卡塔赫纳装载弹药的双桅纵帆船'普埃布拉'抵达。 显然阿拉坎塔拉没有足够的火药, 所以西班牙人还没准备好起航。 但船长的耐心是有限的, 如果普埃布拉三天内不到, 大帆船将离开贝洛港而不等她\n阿拉坎塔拉火药不足, 我可以让她驶入公海, 然后迫使她进行一场持久战, 他们的火药会比我们先耗尽。 您的目标是拦截普埃布拉并摧毁她。 击沉她或夺取她作为战利品, 我不在乎。 只要阻止那艘补给双桅纵帆船到达这里! \n如果您成功了, 就去瓜德罗普见热拉尔.勒克鲁阿, 我相信您已经认识他, 不是吗? 他会付给您应得的硬币。 ";
			link.l1 = "成交! 我这就去拦截普埃布拉! ";
			link.l1.go = "florian_19";
			link.l2 = "等一下, 肖凯先生。 事实是我仍然... 这么说吧, 不太习惯海战。 而您是护卫舰的船长, 显然您背后不止一场海战。 如果对您来说不困难, 您可以... 我该怎么说... ";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // 打开岛屿
			bQuestDisableMapEnter = false;// 打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition 额外训练 -->
		case "florian_guide_01":
			dialog.text = "您希望我给您上一堂海战战术课吗? 非常乐意, 船长! 特别是因为这符合我自己的利益: 我想确保您能成功拦截'普埃布拉'。 ";
			link.l1 = "不, 我不是那个意思。 好吧, 忘了它: 我相信我拦截一艘双桅纵帆船不会有任何问题。 ";
			link.l1.go = "florian_19";
			link.l2 = "是的, 那正是我的意思。 我相信新知识不会对我有害。 ";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "所以您需要记住的第一件事是, 一半的战斗在开始前就已经赢了或输了。 很多事情取决于您和您的船对此的准备程度。 ";
			link.l1 = "... ";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "首先, 确保您的船已修复。 如果船体有洞, 敌人将不难将您送入海底。 如果您的帆上挂着破布, 这会严重限制您的机动性。 如果力量平衡对敌人不利, 敌人可以轻松逃离您, 或者更糟的是, 追上您并强加一场不利的战斗 - 甚至立即登船。 此外, 帆破了, 您将难以获得上风, 即到达对手的上风处, 这是您想要的位置。 ";
			link.l1 = "上风处, 知道了。 还有其他吗? ";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "确保您有足够的人手。 即使是装备42磅大炮的最强大的船, 如果您只有一个炮手跑去装填三门大炮, 根本没有人控制帆, 也会变得无用。 一般来说, 我会立即登上这样的船并夺取她。 ";
			link.l1 = "足够的人手, 知道了。 ";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "另外, 注意您的大炮: 它们会随着时间磨损并爆炸。 随着时间的推移, 炮管的状况会恶化, 如果您的大炮在战斗中开始爆炸, 可能会对您造成非常糟糕的结局。 我就很不幸: 我航行时的那批大炮被发现有几个铸造缺陷。 如果您没有及时带来替代品, 我就会放弃行动, 因为'Militant'在火力上会远不如'Alcantara'。 工具需要及时更换。 ";
			link.l1 = "现在我明白为什么它如此重要了! ";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "除了大炮, 还要注意弹药量。 阿拉坎塔拉会因为这个落入我手中。 如果她的火药库存不足, 她将无法进行长时间的战斗 - 她需要立即进入近距离战斗。 我会利用这一点: 我的护卫舰更快, 重型大帆船无法逃脱。 但我也不需要靠近: 我会在长距离进行加农炮决斗, 然后当阿拉坎塔拉的火药耗尽时, 我会靠近, 用葡萄弹扫射她, 然后登船。 ";
			link.l1 = "绝望的情况... ";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "正是如此。 注意您的火药和弹药。 如果您用完了实心弹 - 您很可能无法击沉敌船。 如果您用完了葡萄弹, 如果您寡不敌众, 就不能指望登船。 如果您没有链弹或短弹, 您将无法追上敌人或在他更快时逃离他。 所有类型的弹药都很重要。 ";
			link.l1 = "有指导意义, 谢谢。 ";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "最后, 根据您的船和敌船的类型和大小, 使用适当的战术。 海上在火力和速度之间存在权衡。 在大型慢速船上, 追逐双桅船或轻型护卫舰进行登船是没有意义的 - 您在先用链弹削弱她之前仍然无法追上。 在这种情况下, 从远处炸毁她并捡拾残骸更为明智。 如果您仍然需要登船, 最好使用快速灵活的船。 ";
			link.l1 = "... ";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "同时, 不要用双桅船与战列舰正面交锋。 像那样的怪物的一次齐射会将较小的船的船体粉碎成碎片。 利用您在速度和机动性上的优势, 扯下她的桅杆和索具, 然后如果您仍然需要登船, 用葡萄弹扫射她的甲板。 如果您需要击沉她... 这不是一项容易的任务, 但有可能。 您可以登上她, 然后点燃她的火药库, 但逃跑并不丢人。 一个好的船长会拯救他的船和船员免于 certain death, 而不是过度英雄主义。 记住, 谨慎和审慎往往是勇气的更好部分。 ";
			link.l1 = "非常感谢您, 肖凯先生! ";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("经验奖励")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("经验奖励")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("经验奖励")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("经验奖励")+": +1 ",SKILL_ACCURACY);
			dialog.text = "很高兴帮助您, 船长。 我希望这些知识将来能对您有所帮助。 ";
			link.l1 = "我相信这会有帮助。 我们出发去拦截'普埃布拉'! ";
			link.l1.go = "florian_19";
		break;
		// <—— legendary edition 额外训练

		// 酒馆里的西班牙军官
		case "tavern_officer":
			dialog.text = "您的口音很不寻常, 先生。 或者我应该说'先生'? 您想见海梅.西利西奥吗? 也许您可以分享同一个牢房。 抓住他, 孩子们! ";
			link.l1 = "嗯, 如果您不喜欢我的口音, 也许我可以向您介绍法国剑术! ";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;// 关闭地点
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}