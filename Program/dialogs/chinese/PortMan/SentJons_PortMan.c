// 城市对话处理
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
				dialog.text = "你有什么事? 啊哈, 你是帆船赛的参赛者! 我说得对吗? ";
				link.l1 = "没错, 先生。 我需要按照规则在这里登记。 ";
				link.l1.go = "Regata_check";
				break;
			}
			//帆船赛
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经问过我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次问同一个问题了... ",
                          "听着, 如果你没有关于港口事务的事情要告诉我, 就别用你的问题来烦我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么好说的。 "), "没关系。 ", "确实, 已经是第三次了... ", "对不起, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Portpax") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "嗯... 你违反了帆船赛规则, 我必须取消你的资格。 对不起。 你不能参加下一次航行。 我已经准备好向皇家港发送急件了。 ";
			link.l1 = "唉... 太遗憾了! 但我无能为力, 你太警觉了。 再见! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta移除中断
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.ThirdTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//玩家在1+2+3次转换中花费的小时数
			dialog.text = "让我们登记: " +GetFullName(pchar)+ "船长, 船是" + pchar.Ship.Name + "... 帆船赛用时为" + sti(pchar.questTemp.Regata.ThirdTransitionTime) + "小时。 完成, 你的成绩已登记, 你可以继续航行了。 ";
			link.l1 = "告诉我我的排名。 ";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "你在这里, 但我没看到你的船。 它在哪里? ";
			link.l1 = "对不起, 先生。 我会立即把我的船转移到港口。 ";
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
				if (pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.ThirdTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//最近对手的名字
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//他的船
				}
			}
			if (n==1)
			{
			dialog.text = "你目前领先。 恭喜! 继续保持! ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "16");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "你是最后一名。 你应该加快速度了。 ";
				link.l1 = "我正在努力! ";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "21");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "你是第二名。 领先者是" + sName + ", 船是" + sShip + "。 我想你仍然可以超过他。 ";
					link.l1 = "谢谢! 我会努力的! ";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "17");
					}
					else
					{
					dialog.text = "你的排名是第" + n + "。 你最近的对手是" + sName + ", 船是" + sShip + "。 ";
					link.l1 = "谢谢! ";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "18");
					if (n==4) AddQuestRecord("Regata", "19");
					if (n==5) AddQuestRecord("Regata", "20");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//航海
			AddCharacterExpToSkill(pchar, "Defence", 30);//防御
			AddCharacterExpToSkill(pchar, "Fortune", 30);//幸运
			AddCharacterExpToSkill(pchar, "Sneak", 30);//潜行
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Sentjons = "true";//圣约翰标记
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Check1.function = "RegataCheck";//检查1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Martinique";
			pchar.quest.Regata_Check2.function = "RegataCheck";//检查2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "Dominica";
			pchar.quest.Regata_Check3.function = "RegataCheck";//检查3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Check.function = "RegataCheck";//检查4
			pchar.questTemp.Regata.AttackIsland = "Guadeloupe";
			pchar.questTemp.Regata.AttackNation = PIRATE;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Guadeloupe";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Brigantine";//第三次伏击
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Martinique";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//马提尼克岛的特殊事件
			pchar.questTemp.Regata.Town = "Bridgetown";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back"; // mitrokosta修复错误的定位器
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//夜间进入特殊区域
			//事件
			pchar.quest.Regata_SpgGirl.win_condition.l1 = "location";
			pchar.quest.Regata_SpgGirl.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_SpgGirl.function = "RegataSpyglassGirl";//拿望远镜的女孩
			pchar.quest.Regata_Attack2.win_condition.l1 = "location";
			pchar.quest.Regata_Attack2.win_condition.l1.location = "Antigua";
			pchar.quest.Regata_Attack2.function = "RegataAttack_Brander";//双桅帆船攻击
			i = FindColony("Bridgetown");
			colonies[i].DontSetShipInPort = true; //不在港口设置船只
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Siege.function = "RegataSiege";//撤离居民任务
		break;
		//帆船赛
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部通过return退出, 别忘了卸载
}