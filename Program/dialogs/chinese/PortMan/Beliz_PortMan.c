// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//帆船赛
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "你有什么事? 啊哈, 你是帆船赛的参赛者! 对吗? ";
				link.l1 = "正是如此, 先生。 我需要按规则在这里登记。 ";
				link.l1.go = "Regata_check";
				break;
			}
			//帆船赛
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事告诉我, 就别用问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> 公正之界
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "听说有人企图暗杀你, 而你正在追查凶手? ";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "企图暗杀你的人已经被解决了, " + npchar.lastname + "先生。 你现在没有任何危险了。 ";
				link.l1.go = "GS_Portman_6";
			}
			//< —公正之界
		break;

		//帆船赛
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//检查港口是否有船
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "嗯... 你违反了帆船赛规则, 我必须取消你的资格。 抱歉, 你不能参加下一次航行。 我已准备好发往皇家港的急件。 ";
			link.l1 = "哎呀... 真遗憾! 但我无能为力, 你太严格了。 再会! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta 移除中断
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//玩家在第1段航行中消耗的小时数
			dialog.text = "我们来登记: " +GetFullName(pchar)+ "船长, 船是" + pchar.Ship.Name + "... 帆船赛用时" + sti(pchar.questTemp.Regata.FirstTransitionTime) + "小时。 完成, 成绩已登记, 你可以继续了。 ";
			link.l1 = "告诉我我的排名。 ";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "你在这里, 但我没看到你的船。 它在哪里? ";
			link.l1 = "抱歉, 先生。 我会立即把船转移到港口。 ";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//最近对手的名字
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//对手的船
				}
			}
			if (n==1)
			{
			dialog.text = "你目前领先。 恭喜! 继续保持! ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "你是最后一名。 得加快速度了。 ";
				link.l1 = "我这就出发! ";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "你是第二名。 领先者是" + sName + ", 船是" + sShip + "。 我想你仍能超过他。 ";
					link.l1 = "谢谢! 我会努力! ";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "你的排名是第" + n + "。 最近对手是" + sName + ", 船是" + sShip + "。 ";
					link.l1 = "谢谢! ";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//航海
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//伯利兹标记
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//检查1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//检查2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//检查3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//圣地亚哥附近的第一次伏击
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//哈瓦那附近的特殊事件
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//夜间进入特殊区域
		break;
		//帆船赛
		
		//--> 公正之界
		case "GS_Portman_1":
			dialog.text = "确实有人企图暗杀我, 这是事实。 至于追查... 并不完全是。 我不需要抓住逃犯 —我需要他的人头。 只有那样我才能重获安宁。 ";
			Link.l1 = "你知道是谁袭击了你, 以及为什么吗? ";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "我... 我不知道他是谁! 我不知道他从哪里来, 为什么袭击我。 但有一点很清楚 —他想让我死。 而现在... 现在我同样疯狂地渴望他的死! 你明白吗? \n所以别问我这些无意义的问题。 你的好奇心对我毫无意义 —现在只有行动能帮上忙。 悬赏两百达布隆买他的人头, 这是我的价码。 开始追捕, 或者别再浪费我的时间。 ";
			Link.l1 = "我知道恐惧和愤怒让你失去了理智, 我甚至可以原谅你的语气。 但你得冷静下来。 我没看到有多少志愿者愿意帮你解决问题, 所以收敛一下你的火气。 两百达布隆可以接受, 但在我接下这份工作之前, 我需要知道所有情况。 ";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "你的话只是空谈, 而且没有任何线索。 在丛林里寻找一个不认识的人就像大海捞针。 我不会把时间浪费在这种无意义的追捕上。 祝你好运, 你肯定需要它。 ";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "啊... 请原谅, " + GetAddress_Form(NPChar) + ", 我太紧张了... 你具体想知道什么? ";
			Link.l1 = "你注意到任何能帮你识别他的特征吗? 他是单独行动, 还是有更强大的势力支持? 你告诉我得越多, 你就能越早安心入睡。 ";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "什么敌人? ! 我没有敌人! 从来没有! 我没做过任何该在光天化日之下被当街刺杀的事\n那个恶棍... 他只是个愤世嫉俗的疯子, 在这些殖民城镇里随处可见\n至于去哪里找... 我觉得他躲在丛林里。 在那片该死的树林里很容易消失, 但我肯定他会去洞穴或海湾 —那里更容易躲藏\n至于外貌, 他脸上蒙着围巾, 头上戴着帽子, 携带的武器比国王的卫兵还多。 没时间注意其他东西了。 ";
			Link.l1 = "好吧, 信息不多, 但足够开始搜索了。 我马上出发。 把金子准备好 —我很快就回来。 ";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_5");
		break;
		
		case "GS_Portman_6":
			dialog.text = "太棒了, " +GetFullName(pchar)+ "! 简直太棒了! 你证明了自己无与伦比的能力。 这是你的奖励 —两百达布隆。 请收下! ";
			Link.l1 = "谢谢你! 但告诉我, 你有理由怀疑凶手是被你以前的某个客户雇佣的吗? ";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "以前的客户? ..胡说八道! ... 我是个诚实的人, 我的交易一直光明正大! 但既然你帮了我, 我就告诉你一件事。 不久前, 海盗来找过我\n他们出钱买商船的情报。 我拒绝了, 他们就发出威胁和诅咒, 然后怒气冲冲地走了。 我认为刺客是他们派来的。 他们不喜欢被拒绝。 ";
			Link.l1 = "既然如此, 你要照顾好自己。 谁知道这些‘海盗’还会派多少杀手来? 就此别过 —我还有事要办。 ";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "等等, 船长。 我想再次感谢你。 除了金子, 你还赢得了我的好感。 只要我还是这里的港口主管, 你的任何船只都可以在这里停泊, 时长不限, 享受五折优惠。 听起来怎么样? ";
			Link.l1 = "真是慷慨的提议! 再次感谢你! ";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "我再次感谢你的努力。 我相信只要你专注于重要的事情, 你的事业会像今天一样继续兴旺发达。 再会, 船长。 ";
			Link.l1 = "再见。 ";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_10");
		break;
		//<-- 公正之界
	}
	UnloadSegment(NPChar.FileDialog2);  // 若switch内部通过return退出, 需确保执行卸载
}