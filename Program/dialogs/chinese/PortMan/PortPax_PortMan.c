// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony, sld;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			// 帆船赛
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "你有什么事? 啊哈, 你是帆船赛的参赛者! 对吗? ";
				link.l1 = "正是如此, 先生。 我需要按规则在这里登记。 ";
				link.l1.go = "Regata_check";
				break;
			}
			// 帆船赛
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事告诉我, 就别用问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		// 帆船赛
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)// 检查港口是否有船
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Beliz") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "先生! 你违反了帆船赛规则, 我必须取消你的资格。 抱歉, 你不能参加下一次航行。 我已准备好发往皇家港的急件。 ";
			link.l1 = "唉... 真遗憾! 但我无能为力, 你太严格了。 再会! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta 移除中断
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.SecondTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());// 玩家在1+2次转换中消耗的小时数
			dialog.text = "我们来登记: " +GetFullName(pchar)+ "船长, 船是" + pchar.Ship.Name + "... 帆船赛用时" + sti(pchar.questTemp.Regata.SecondTransitionTime) + "小时。 完成, 成绩已登记, 你可以继续了。 ";
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
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
				if (pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.SecondTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);// 最近对手的名字
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);// 对手的船
					pchar.questTemp.Regata.ContraIndex = sTemp;
				}
			}
			if (n==1)
			{
			dialog.text = "你目前领先。 恭喜! 继续保持! ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "10");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "你是最后一名。 得加快速度了。 ";
				link.l1 = "我这就出发! ";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "15");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "你是第二名。 领先者是" + sName + ", 船是" + sShip + "。 我想你仍能超过他。 ";
					link.l1 = "谢谢! 我会努力! ";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "11");
					}
					else
					{
					dialog.text = "你的排名是第" + n + "。 最近对手是" + sName + ", 船是" + sShip + "。 ";
					link.l1 = "谢谢! ";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "12");
					if (n==4) AddQuestRecord("Regata", "13");
					if (n==5) AddQuestRecord("Regata", "14");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);// 航海
			AddCharacterExpToSkill(pchar, "Defence", 30);// 防御
			AddCharacterExpToSkill(pchar, "Fortune", 30);// 幸运
			AddCharacterExpToSkill(pchar, "Sneak", 30);// 潜行
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Portpax = "true";// 太子港标记
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Hispaniola1";
			pchar.quest.Regata_Check1.function = "RegataCheck";// 检查1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Check2.function = "RegataCheck";// 检查2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "Nevis";
			pchar.quest.Regata_Check3.function = "RegataCheck";// 检查3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Antigua";
			pchar.quest.Regata_Check.function = "RegataCheck";// 检查4
			pchar.questTemp.Regata.AttackIsland = "PuertoRico";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";// 第二次伏击
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Nevis";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";// 尼维斯岛特殊事件
			pchar.questTemp.Regata.Town = "Sentjons";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";// 夜间进入特殊区域
			// 事件
			log_info(pchar.questTemp.Regata.ContraIndex);
			pchar.questTemp.Regata.Index = n;
			pchar.quest.Regata_Contra.win_condition.l1 = "location";
			pchar.quest.Regata_Contra.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_Contra.function = "Contra_Regata";// 加农炮对抗事件
			pchar.quest.Regata_Padre.win_condition.l1 = "location";
			pchar.quest.Regata_Padre.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_Padre.function = "Padre_Regata";// 圣约翰镇神父事件
			sld = characterFromId("SentJons_Priest");
			LAi_RemoveLoginTime(sld);
		break;
		// 帆船赛

	}
	UnloadSegment(NPChar.FileDialog2);  // 若switch内部通过return退出, 需确保执行卸载
}