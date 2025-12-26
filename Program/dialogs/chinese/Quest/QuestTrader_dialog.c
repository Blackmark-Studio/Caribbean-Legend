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
	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		bool ok = CheckFreeSitFront(npchar);
			if(hrand(11) > 8 && ok && !CheckAttribute(pchar, "GenQuest.Racing.Go") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0)//水上飞机竞赛
			{
				dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 我叫" + GetFullName(NPChar) + ", 是一名船长。 看来您也是船长。 愿意和我一起喝一杯吗? 我请客。 ";
				link.l1 = "为什么不呢? 和志同道合的人喝几杯也不错。 ";
				link.l1.go = "Race_prepare";
				link.l2 = "抱歉, 我赶时间。 下次吧。 ";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//商船护航
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(NPChar) + ", 一名商人。 看您像是位船长。 想赚几千比索吗? ";
					link.l1 = "我总是很乐意赚点钱。 您说的是什么工作? ";
					link.l1.go = "Escort_choice";
					link.l2 = "商人能提供什么工作? 保护您那破旧的船吗? 我可不帮奸商。 ";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 最近如何? 需要什么吗? ";
					link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + "。 不, 不需要。 只是打个招呼, 祝您愉快! ";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "船长, 我们之前谈过, 对吧? 您说'不帮奸商', 现在找我做什么? ";
			link.l1 = "是的, 您说得对。 好吧, 您就坐在这儿喝朗姆酒吧, 我得走了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_distress";
		break;
		
		case "Escort_choice"://首次分支 - 在城市。 海湾和荒岛之间选择
			pchar.GenQuest.Escort.Trader.StartCity = GetCurrentTown();//起始城市
			pchar.GenQuest.Escort.Trader.ShipType = TraderShipType(&iTemp);//商人船只类型
			pchar.GenQuest.Escort.Trader.Nation = npchar.nation;//商人国家
			switch (hrand(2))
			{
				case 0://友好城市
					pchar.GenQuest.Escort.Trader.City = FindFriendCityToMC(false);//目标城市
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), GetArealByCityName(pchar.GenQuest.Escort.Trader.City))+5;//天数
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//报酬 (基于距离和船只等级) 
					pchar.GenQuest.Escort.Trader.Type1 = "true";//任务类型
					pchar.GenQuest.Escort.Trader.Chance = rand(1);
					pchar.GenQuest.Escort.Trader.Add = "到" + XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen") + "";
					dialog.text = "我想请您在" + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + "内护送我到" + XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen") + "。 我会付您" + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + "。 ";
					link.l1 = "为什么不呢? 一起航行更安全, 我理解。 我同意。 ";
					link.l1.go = "EscortType";
					link.l2 = "我很乐意帮忙, 但我要去不同的方向。 ";
					link.l2.go = "Escort_exit";
				break;
				case 1://海湾
					GetEscortTraderShore();//目标海湾
					while(pchar.GenQuest.Escort.Trader.City == "Terks" || pchar.GenQuest.Escort.Trader.City == "caiman" || pchar.GenQuest.Escort.Trader.City == "dominica" 
							|| pchar.GenQuest.Escort.Trader.City == "Pearl" || pchar.GenQuest.Escort.Trader.City == "Tenotchitlan")
					{
						GetEscortTraderShore();
					} // patch-6
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//天数
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//报酬
					pchar.GenQuest.Escort.Trader.Type2 = "true";//任务类型
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "到" + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen") + ", 就在" + XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen") + "附近";
					dialog.text = "我想请您在" + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + "内护送我到" + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen") + ", 就在" + XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen") + "附近。 我会付您" + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + "。 ";
					link.l1 = "为什么不呢? 一起航行更安全, 我理解。 我同意。 ";
					link.l1.go = "EscortType";
					link.l2 = "我很乐意帮忙, 但我要去不同的方向。 ";
					link.l2.go = "Escort_exit";
				break;
				case 2://荒岛
					pchar.GenQuest.Escort.Trader.Island = DesIsland();//目标岛屿
					pchar.GenQuest.Escort.Trader.Shore = SelectQuestShoreLocationFromSea(pchar.GenQuest.Escort.Trader.Island);//岛上的海湾
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//天数
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//报酬
					pchar.GenQuest.Escort.Trader.Type3 = "true";//任务类型
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "到" + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen") + ", 在荒岛" + XI_ConvertString(pchar.GenQuest.Escort.Trader.Island) + "上";
					dialog.text = "我想请您在" + FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)) + "内护送我到荒岛" + XI_ConvertString(pchar.GenQuest.Escort.Trader.Island) + "的" + XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen") + "。 我会付您" + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + "。 ";
					link.l1 = "为什么不呢? 一起航行更安全, 我理解。 但我从没听说过那里有商店或贸易站。 ";
					link.l1.go = "EscortType";
					link.l2 = "我很乐意帮忙, 但我要去不同的方向。 ";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "您准备好起航了吗, 船长? 我在等您的命令。 ";
			link.l1 = "是的, 我们现在起航。 港口见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "太好了! 很高兴我们达成协议。 希望我们的旅程安全顺利。 ";
			link.l1 = "我也希望如此。 是时候起航了! ";
			link.l1.go = "EscortType_go";
			NextDiag.CurrentNode = "Trader_wait";
		break;
		
		case "EscortType_go":
			//通用参数
			DialogExit();
			pchar.GenQuest.Escort.Trader.id = npchar.id;
			CreateTraderShipAndAdd(npchar);//加入商船
			pchar.GenQuest.Escort.Trader.ShipMaxHP = sti(npchar.ship.HP);
			ReOpenQuestHeader("TraderEscort");
			AddQuestRecord("TraderEscort", "1");
			AddQuestUserData("TraderEscort", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)));
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddQuestUserData("TraderEscort", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.StartCity+"Gen"));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.Add);
			pchar.GenQuest.Escort.Trader = "begin";
			//特殊参数
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type1"))//到友好城市
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.City+"_tavern";
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) TraderHunterOnMap(true);
				else TraderHunterOnMap(false);//在大地图上启动AI
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2"))//到海湾
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2) TraderHunterOnMap(false);
				else
				{
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "EscortTraderAttackInShore";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type3"))//到荒岛
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0) TraderHunterOnMap(false);
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) 
				{
					if(sti(RealShips[sti(pchar.Ship.Type)].Class) >= sti(RealShips[sti(pchar.GenQuest.Escort.Trader.ShipType)].Class) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3)//比较船只
					{//亲自攻击
						pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
						pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
						pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
					}
					else TraderHunterOnMap(true);
				}
				else
				{//设伏 + 亲自攻击
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
				}
			}
			pchar.quest.EscortTrader_Complete.win_condition.l1 = "location";
			pchar.quest.EscortTrader_Complete.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Location;
			pchar.quest.EscortTrader_Complete.function = "EscortTraderComplete";
			SetFunctionTimerCondition("EscortTrader_Over", 0, 0, sti(pchar.GenQuest.Escort.Trader.DaysQty), false);
			pchar.quest.EscortTrader_fail.win_condition.l1 = "NPC_Death";//护送船只沉没中断
			pchar.quest.EscortTrader_fail.win_condition.l1.character = pchar.GenQuest.Escort.Trader.id;
			pchar.quest.EscortTrader_fail.function = "EscortTrader_failed";
		break;
		
		case "EscortTrader_complete"://完成任务
			sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/4))//如果船体剩余少于1/4 - 首次检查
			{
				dialog.text = "船长, 告诉我为什么我要雇您? 看看我的船! 成什么样了? 都毁了! 勉强浮在水面上。 您没看见吗? 我不明白 - 到底是谁护送谁? 总之, 您别想拿到报酬了, 忘了吧。 ";
				link.l1 = "要不是我, 您现在早喂螃蟹了, 你这个愚蠢的商人。 好吧, 算您走运, 但世界很小, 我们迟早会在海上见面的! ";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//如果船体剩余少于1/2 - 二次检查
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "船长, 告诉我为什么我要雇您? 看看我的船! 成什么样了? 都毁了! 勉强浮在水面上。 您没看见吗? 总之, 我只付您一半报酬。 别想多要! ";
				link.l1 = "嗯... 好吧, 我同意。 您的船确实... 有点损坏... ";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//不用钱 - 给线索
			{
				dialog.text = "船长, 您看... 我没钱付您报酬。 但请别担心, 我想给您另一种报酬, 比之前承诺的要丰厚得多! ";
				link.l1 = "嗯... 其实我现在就想拿到钱。 但如果是这样的话, 我洗耳恭听。 ";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "非常感谢您, 船长。 尽管危险重重, 但和您一起航行很安全。 这是您的报酬。 ";
			link.l1 = "不客气... 我只是做了我的工作。 ";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "别想吓唬我! 您的战斗技巧让您的威胁显得可笑。 再见! ";
			link.l1 = "趁您还能走, 赶紧滚吧, 奸商... ";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//运气
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "是的, 很明智的观察... 这是您的" + FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)) + ", 再见。 ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//运气
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "您做得很好! 现在我得走了。 再见, 船长! ";
			link.l1 = "祝您好运, " + npchar.name+ "! ";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "6");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 80);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 50);//潜行
		break;
		
		case "EscortTrader_complete_4":
			pchar.GenQuest.Escort.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");
			GetEnemyTraderGoods();
			pchar.GenQuest.Escort.Trader.EnIsland = DesIsland();
			dialog.text = "有个商人 - " + pchar.GenQuest.Escort.Trader.Enemyname + "。 他拥有并指挥一艘长笛船。 我得到消息, 两周后他会抵达荒岛" + XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland) + ", 补充淡水并和当地印第安人交易。 他船上会有很多" + pchar.GenQuest.Escort.Trader.add + "。 他战斗力很弱, 夺取他的船毫无困难\n总之您会从中获利的, 船长。 ";
			link.l1 = "人对人是狼? ";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "什么? ";
			link.l1 = "您如此轻松坦诚地'出卖'同行... 但我不在乎您的良心, 感谢您的情报。 祝您好运, 先生! ";
			link.l1.go = "EscortTrader_complete_6";
		break;
		
		case "EscortTrader_complete_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//移除两个中断
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			AddQuestRecord("TraderEscort", "7");
			AddQuestUserData("TraderEscort", "sIsland", XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.add);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1 = "Timer";
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l2 = "location";
			pchar.quest.EscortTrader_EnTrader.win_condition.l2.location = pchar.GenQuest.Escort.Trader.EnIsland;
			pchar.quest.EscortTrader_EnTrader.function = "Create_EnemyTraderFleut";
			SetFunctionTimerCondition("EscortTraderEnemy_Over", 0, 0, 16, false); // 计时器
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 80);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 50);//潜行
		break;
		
		case "complete_exit":
			DialogExit();
			CloseQuestHeader("TraderEscort");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//移除两个中断
			pchar.quest.EscortTrader_Attack.over = "yes"; // patch-8
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Race_prepare":
			NextDiag.TempNode = "Race_begin";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "exit_sit":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		case "Race_begin"://水上飞机竞赛
			dialog.text = "呃, 咱们喝杯老朗姆吧, 船长! 最近怎么样, 生意还好吗? ";
			link.l1 = "我其实不算商人。 但我过得不错。 ";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "那最重要了! 考虑到公海的危险。 ";
			link.l1 = "是的, 您说得对。 尤其是对你们商人来说, 很多人觊觎您的货物。 你们既跑不过也打不过, 因为您把利润放在首位, 船慢炮小。 只有组成四五个船的护航队才能安全。 ";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "呃, 不是所有商人都这样, 朋友。 我总是独自航行, 不需要任何压舱物。 我非常了解加勒比海, 可以说我在导航。 驾驶和指挥船员方面都很擅长。 任何海盗都追不上我。 ";
			link.l1 = "真的吗? 我很难相信。 满载货物? 用商船? 您是说能逃脱海盗双桅船。 小帆船或快速护卫舰? ";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "看来您怀疑我的船能开得快? 好吧。 我跟您打个赌。 ";
			link.l1 = "什么样的赌? ";
			link.l1.go = "Race_begin_4";
		break;
		
		case "Race_begin_4"://设置所有参数
			if (!CheckAttribute(pchar, "GenQuest.Racing")) pchar.GenQuest.Racing.Count = 0;
			pchar.GenQuest.Racing.Go.Nation = npchar.nation;
			pchar.GenQuest.Racing.Go.StartCity = GetCurrentTown();
			pchar.GenQuest.Racing.Go.City = FindFriendCityToMC(false);//目标友好城市
			pchar.GenQuest.Racing.Go.Island = GetIslandByCityName(pchar.GenQuest.Racing.Go.City);
			pchar.GenQuest.Racing.Go.DaysQty = makeint((GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Racing.Go.StartCity), GetArealByCityName(pchar.GenQuest.Racing.Go.City)))/1.3);//天数
			pchar.GenQuest.Racing.Go.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			if (sti(pchar.GenQuest.Racing.Go.DaysQty) < 1) pchar.GenQuest.Racing.Go.DaysQty = 1; // patch-8
			dialog.text = "听着。 我今天就起航去" + XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City) + "。 我说我会在" + FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty) + "内到达。 试试超过我, 早点到" + XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City) + "。 时间现在开始计算。 敢赌吗? 还是对您来说太难了? ";
			link.l1 = "对谁? 对我? 别开玩笑了。 您觉得能在那个时间内到达? 荒谬。 好吧, 我接受赌注。 您准备输多少? ";
			link.l1.go = "Race_begin_5";
			link.l2 = "我太忙了, 没时间因为无聊的吹嘘参加竞赛。 ";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "嗯... 您是害怕输吗? 随便吧。 但别轻易评判别人, 商人中也有很多经验丰富的水手... 比您有经验得多。 ";
			link.l1 = "好了好了, 别给我上哲学课了。 再见... ";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "这是您的选择, 船长。 ";
			iTemp = 1;
			for (i=5; i>=1; i--)
			{
					sTemp = "l"+iTemp;
					link.(sTemp) = ""+FindRussianMoneyString(sti(10000*i))+"";
					link.(sTemp).go = "Racing_rate"+i;
					iTemp++;
			}
		break;
		
		case "Racing_rate5"://50 000
			if (hrand(9, "&RacRa") > 6)
			{
			dialog.text = "好。 我同意。 请拿出您的硬币。 这是我的赌注。 ";
			link.l1 = "让我拿一下钱包... ";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "船长, 这提议太荒谬了吧? 这么多钱都能买艘纵帆船, 喝一个月朗姆酒了。 出个合理的数目。 ";
			link.l1 = "这数目对我来说很合理, 我可不想为了更少的钱浪费时间。 我们不是乞丐, 不会为了几个比索打赌。 好吧... 谈够了。 如果您不敢赌, 那是您的选择... 吹嘘是要付出代价的。 ";
			link.l1.go = "Race_exit";
			link.l2 = "真的吗? 好吧。 让我想想... ";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "好。 我同意。 请拿出您的硬币。 这是我的赌注。 ";
			link.l1 = "让我拿一下钱包... ";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "船长, 这提议太荒谬了吧? 这么多钱都能买艘三桅帆船, 喝一个月朗姆酒了。 出个合理的数目。 ";
			link.l1 = "这数目对我来说很合理, 我可不想为了更少的钱浪费时间。 我们不是乞丐, 不会为了几个比索打赌。 好吧... 谈够了。 如果您不敢赌, 那是您的选择... 吹嘘是要付出代价的。 ";
			link.l1.go = "Race_exit";
			link.l2 = "真的吗? 好吧。 让我想想... ";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "好。 我同意。 请拿出您的硬币。 这是我的赌注。 ";
			link.l1 = "让我拿一下钱包... ";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "船长, 这提议太荒谬了吧? 这么多钱都能买艘小帆船, 喝一个月朗姆酒了。 出个合理的数目。 ";
			link.l1 = "这数目对我来说很合理, 我可不想为了更少的钱浪费时间。 我们不是乞丐, 不会为了几个比索打赌。 好吧... 谈够了。 如果您不敢赌, 那是您的选择... 吹嘘是要付出代价的。 ";
			link.l1.go = "Race_exit";
			link.l2 = "真的吗? 好吧。 让我想想... ";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "好。 我同意。 请拿出您的硬币。 这是我的赌注。 ";
			link.l1 = "让我拿一下钱包... ";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "船长, 这提议太荒谬了吧? 这么多钱都能买艘小帆船, 喝一个月朗姆酒了。 出个合理的数目。 ";
			link.l1 = "这数目对我来说很合理, 我可不想为了更少的钱浪费时间。 我们不是乞丐, 不会为了几个比索打赌。 好吧... 谈够了。 如果您不敢赌, 那是您的选择... 吹嘘是要付出代价的。 ";
			link.l1.go = "Race_exit";
			link.l2 = "真的吗? 好吧。 让我想想... ";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "好。 我同意。 请拿出您的硬币。 这是我的赌注。 ";
			link.l1 = "让我拿一下钱包... ";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "那么? ";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "给你! ";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "嗯... 看来我没那么多钱。 ";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "嗯, 您知道我们不是乞丐, 不会为了几个比索打赌, 还是说您只是害怕? 好吧, 去你的。 但别轻易评判别人, 商人中也有很多经验丰富的水手... 比您有经验得多。 ";
			link.l1 = "好了好了, 别给我上哲学课了。 再见... ";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "那您为什么不看看钱包, 或者下小点的赌注? ";
			link.l1 = "好吧, 我想想我有多少钱... ";
			link.l1.go = "Race_begin_5";
			link.l2 = "我改变主意了。 ";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "改变主意了? 是不是害怕了? 好吧, 去你的。 但别轻易评判别人, 商人中也有很多经验丰富的水手... 比您有经验得多。 ";
			link.l1 = "好了好了, 别给我上哲学课了。 再见... ";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "那我们就打赌了! 如果您不介意, 我们叫酒保来见证, 把赌注交给他。 胜者回来拿走全部赌注。 作弊是不可能的, 因为流言蜚语在群岛传播很快, 他会知道谁是胜者。 ";
			link.l1 = "我同意。 这很合理。 ";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "嗯, 我想我们该上船起航了, 时间在流逝。 我不知道您怎样, 但我马上就要起航了。 哦, 我的船是长笛船, 名叫" + pchar.GenQuest.Racing.Go.ShipName + "。 您到港口后应该很容易认出她。 ";
			link.l1 = "别高兴得太早。 在" + XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen") + "的酒馆见! ";
			link.l1.go = "Racing_Go_2";
		break;
		
		case "Racing_Go_2":
			DialogExit();
			npchar.lifeday = 0;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.GenQuest.Racing.Go.StartCity + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "exit_sit", -1);
			//只能通过克隆正确工作 :(
			sTemp = npchar.model;
			int iNation = sti(npchar.Nation);
			sld = GetCharacter(NPC_GenerateCharacter("RaceTrader", sTemp, "man", "man", sti(PChar.rank)+5, iNation, -1, true, "quest"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.Dialog.Filename = "Quest\QuestTrader_dialog.c";
			pchar.quest.Racing_Timer.win_condition.l1 = "Timer";
			pchar.quest.Racing_Timer.win_condition.l1.date.hour  = sti(GetTime()+rand(6));
			pchar.quest.Racing_Timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.function = "TraderRaceInTargetCity";
			pchar.quest.Racing_Finish.win_condition.l1 = "location";
			pchar.quest.Racing_Finish.win_condition.l1.location = pchar.GenQuest.Racing.Go.City + "_town";
			pchar.quest.Racing_Finish.function = "MCRaceInTargetCity";
			SetFunctionTimerCondition("RacingTimeOver", 0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty)+10, false);
			ReOpenQuestHeader("Racing");
			AddQuestRecord("Racing", "1");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			AddQuestUserData("Racing", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen"));
			AddQuestUserData("Racing", "sDay", FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty));
			AddQuestUserData("Racing", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Racing.Go.Money)));
		break;
		
		case "Racing_Finished":
			if (CheckAttribute(pchar, "GenQuest.Racing.Go.MCWin"))
			{
			dialog.text = "嘿! 其实我很惊讶... 恭喜您, 船长! 您确实比我快。 人们说天外有天, 对吧? ";
			link.l1 = "没错, 先生。 但我想说, 作为商船船长, 您的经验和技巧令人惊讶。 不是每个商人都能在这么短时间内用长笛船航行这么远。 ";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "嗯, 您惊讶吗, 船长? 正如我说的, 我非常了解大海, 驾驶我的船也很在行。 现在看到了吧? ";
			link.l1 = "啊! 难以置信! 用长笛船... 这么远, 这么快... 恭喜您, 船长! ";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "嗯, 您是胜者。 现在, 您得回到" + XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity) + "从酒保那里拿您的钱。 您当之无愧! ";
			link.l1 = "我这就去。 很高兴认识您。 再见! ";
			link.l1.go = "Racing_end";
			pchar.GenQuest.Racing.Count = sti(pchar.GenQuest.Racing.Count)+1;
			//启动帆船赛
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.GenQuest.Racing.Count) == 3)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//适合举办帆船赛的城市
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			pchar.GenQuest.Racing.Go.Advantage = "true";
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Sailing", 200);//航海
			AddCharacterExpToSkill(pchar, "Fortune", 200);//运气
			AddCharacterExpToSkill(pchar, "Leadership", 100);//领导力
			ChangeCharacterComplexReputation(pchar,"authority", 3);
			ChangeOfficersLoyality("good_all", 3);
		break;
		
		case "Racing_Finished_2":
			dialog.text = "没什么秘密, 只是技巧和经验。 我得去" + XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc") + "领我的奖金了。 ";
			link.l1 = "您应得的。 再见! ";
			link.l1.go = "Racing_end";
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//航海
			AddCharacterExpToSkill(pchar, "Fortune", 50);//运气
			AddCharacterExpToSkill(pchar, "Leadership", 20);//领导力
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddQuestRecord("Racing", "5");
			CloseQuestHeader("Racing");
		break;
		
		case "Racing_end":
			DialogExit();
			NextDiag.currentNode = "Racing_end_repeat";
			pchar.quest.Racing_fail.over = "yes";
			Group_DeleteGroup("RacingTrader");
			sld = characterFromId("RaceTraderSkiper");
			sld.lifeday = 0;
		break;
		
		case "Racing_end_repeat":
			dialog.text = "您还有什么想聊的吗? ";
			link.l1 = "不, 没什么了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Racing_end_repeat";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

float ShipFactorMC()//玩家船只等级系数
{
	float f;
	switch (sti(RealShips[sti(pchar.Ship.Type)].Class))
	{
		case 1: f = 1.0 break;
		case 2: f = 1.2 break;
		case 3: f = 1.5 break;
		case 4: f = 2.2 break;
		case 5: f = 3.0 break;
		case 6: f = 4.5 break;
		case 7: f = 5.5 break;
	}
	return f;
}

int TraderShipType(ref iShipCoef)//商人船只类型
{
	int iRank = sti(pchar.rank);
	int iShip;
	
	if(iRank < 5)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_LUGGER;
				iShipCoef = 3;
			break;
			case 2:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
		}
	}
	if(iRank >= 5 && iRank < 11)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
			case 2:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
		}
	}
	if(iRank >= 11 && iRank < 18)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
			case 1:
				iShip = SHIP_FLEUT;
				iShipCoef = 6;
			break;
			case 2:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 3:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
		}
	}
	if(iRank >= 18 && iRank < 25)
	{
		switch (rand(4))
		{
			case 0:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 1:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
			case 2:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 3:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 4:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
		}
	}
	if(iRank >= 25)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 1:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 2:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
			case 3:
				iShip = SHIP_NAVIO;
				iShipCoef = 12;
			break;
		}
	}
	return iShip;
}

void GetEnemyTraderGoods()//选择货物
{
switch (rand(6))
	{
		case 0:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_EBONY;
			pchar.GenQuest.Escort.Trader.add = "乌木";
			break;
		case 1:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_MAHOGANY;
			pchar.GenQuest.Escort.Trader.add = "红木";
			break;
		case 2:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_TOBACCO;
			pchar.GenQuest.Escort.Trader.add = "烟草";
			break;
		case 3:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_COFFEE;
			pchar.GenQuest.Escort.Trader.add = "咖啡";
			break;
		case 4:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CINNAMON;
			pchar.GenQuest.Escort.Trader.add = "肉桂";
			break;
		case 5:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_FOOD;
			pchar.GenQuest.Escort.Trader.add = "粮食";
			break;
		case 6:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CHOCOLATE;
			pchar.GenQuest.Escort.Trader.add = "可可";
			break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter;
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}