void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;
				
				float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
				if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
				
				if (GetCompanionQuantity(pchar) > 1) iTmp = true;
				if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;
				
				// 寻找最低级别的同伴
				/*for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
						if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				}*/
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("没人告诉过你不要坐这么显眼的船来这里吗! 为什么不带几艘战列舰来? 滚蛋, 换艘小船来。 ", 
						"滚出去! 否则我们就把你交给巡逻队。 ", 
						"回到你的船上离开。 ",
						"真是受够你了... ", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("好了好了, 我去换船。 ", 
						"冷静点, 我这就走。 ",
						"该死, 我还以为这行得通... ", 
						"是的, 我就是这么固执! ", npchar, Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("嘿, 你在这儿干什么, " + GetSexPhrase("伙计","姑娘") + "?",
										  RandSwear() + "你在这儿有什么事? ! ");
				Link.l1 = "放松点, 伙计, 我们做笔交易吧! ";
				Pchar.quest.Contraband.Counter = 0; // 未进行交易
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				// 按总督命令, 剿灭走私者, 仅这个分支。 
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "我是受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "总督的命令来的! 放下武器跟我走, 你们被捕了! ";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				// 如果已付款, 则交谈, 否则送走
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
					dialog.Text = RandPhraseSimple("啊, 终于来了! 我们一直在等你。 走吧, 该起航了。 ", "我们快点。 到处都是巡逻队。 我们得离开这里! ");
					// 按总督命令, 剿灭走私者, 仅这个分支。 
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "我是受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "总督的命令来的! 放下武器跟我走, 你们被捕了! ";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					// 如果载有乘客, 去花园..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "你是谁? 我们说好了只载一名乘客! ";
						Link.l1 = "哦... ";
						Link.l1.go = "Exit";
						break;
					}
					// 如果招募了同伴或自己买了船 :), 去花园..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("你是谁? 我们在等一名乘客, 不是船长。 ", "滚蛋! 在你处理掉你的船之前别回来。 ");
						Link.l1 = "该死! ";
						Link.l1.go = "Exit";
						break;
					}
					// 类似帮忙击退, 自己人... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // 战斗还在进行
						{
							dialog.Text = "该死, 巡逻队! 我们不认识你, 你也不认识我们。 ";
							Link.l1 = "好吧... ";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("感谢你的协助。 我们不会忘记的。 现在起航吧。 ", "干得好! 战斗很精彩。 我们走吧。 ");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					// 这里一切正常, 出发。 
					Link.l2 = "我这就走。 ";
					Link.l2.go = "Exit";
					// 这是巡逻队... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						// 将格雷放入地点。 
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						// 起航, 否则RemoveTravelSmugglers会破坏整个分支
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // 离开甲板的标志
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " 天过去了。 " + NewStr() + "走私者的甲板。 ",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // 替换甲板
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
					// 如果海关已经在追捕
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
						dialog.Text = RandSwear() + "巡逻队! 我们不认识你, 你也不认识我们。 ";
						Link.l1 = "好的! ";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "滚蛋! 如果你破坏我们的交易, 我们就把你开膛破肚。 ";
						Link.l1 = RandPhraseSimple("你敢威胁我, 杂种! ? ", "你会被自己的话噎死的! ");
						Link.l1.go = "Exit_fight";
						Link.l2 = "别担心, 我知道规矩。 再见。 ";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "你是背着货物来的吗? 你的船呢? ";
			Link.l1 = RandPhraseSimple("首先, 我想看看有没有陷阱。 ", "不想拿船冒险。 我更喜欢亲眼看看。 ");
			Link.l1.go = "No_ship_1";
			Link.l2 = "交易取消! ";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "我们是诚实的人, 不会骗你。 把船开到这里来, 别让巡逻队跟着你。 ";
			Link.l1 = "好的。 在这里等我。 ";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "取消? 你在开玩笑吧! ";
				Link.l1 = "我是认真的。 ";
				Link.l1.go = "Cancellation_1";
			}
			else
            {
				dialog.Text = "好吧。 反正我们今天交易得很愉快。 ";
				Link.l1 = "没错! ";
				Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "你这个混蛋! 你不能就这样骗我们! 你会用脑袋来偿还的! ";
					Link.l1 = "我看未必! ";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "你不会得逞的! ";
					Link.l1 = "去别处汪汪叫吧, 狗东西! ";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "你会后悔的! ";
				Link.l1 = "你废话太多了。 ";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			// "地铁"的计数器... 
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); // 走私者声誉下降
			}
			dialog.Text = "你会为此付出代价的! ";
			Link.l1 = "那你们都得死。 我有明确命令 - 如果你们反抗就全部消灭。 ";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("听说最新消息了吗? 当地走私者不久前被巡逻队围捕了。 你知道吗? 和他们交易的船长逃跑了! " +
				"他的船员很勇猛, 整个巡逻队都被杀了。 而我们当地的走私者就这么消失了。 岸上什么都没找到。 没有货物, 没有藏匿处, 也没有走私者。 看, 他们在这里就是这么做生意的! ", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
			// 岸上的海关
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// 开始交易 -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "你在这里干什么? 你没什么可卖的! 你货舱里的所有货物都可以在镇上合法出售! ";
				Link.l1 = "这次运气不好。 ";
				Link.l1.go = "NoGoods";
			}
			else
			{
				// 设置环境 -->
				if (sti(Pchar.quest.Contraband.Counter) == 0) // 还未交易
                {
                    if(hrand(11) == 3)
                    {
						dialog.Text = "我明白了.. 你知道吗, 我们会免费拿走你的货物。 我怀疑你反正也没法抱怨。 ";
						Link.l1 = "试试看, 败类! ";
						Link.l1.go = "Exit_fight";
                        break;
					}
					// 海上和岸上的士兵是独立的!!!
					if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
					{
                        SetCoastalGuardPursuit();
					}
					// 在地图上逃离巡逻队时 - 三艘船
					SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// 如果在港口坐着。 睡着, 那么2天
					
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
					Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
				}
				// 设置环境 <--
				dialog.text = "好吧, 让我们看看你带了什么。 ";										  
				Link.l1 = "给我们看看你带了什么。 ";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
				{
					Link.l99 = "我改变主意了。 ";
					Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour传奇版 危险货物
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour传奇版 危险货物 -->
		case "SmugglerZPQ":
			dialog.text = "交易愉快, 船长! 如果有其他有趣的货物 - 联系我们! ";										  
			Link.l1 = "我同意, 我也对我们的交易很满意。 哦, 要是能以这么好的价格买下所有货物就好了... ";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "我们为什么要以这样的价格购买普通货物, 这些在商店里可以合法买到? 但别气馁: 事实上任何产品都可以出售, 即使是普通火药! 只要知道地方, 你可以以天价出售。 ";										  
			Link.l1 = "得了吧。 谁会以天价购买火药? ";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "嗯, 这就是我告诉你的, 呵呵... 不过... 你知道, 确实有机会以天价出售火药, 但这笔交易对我们来说并不划算, 因为你需要有相当好的声誉, 而我们, 如你所知, 不是贵族。 ";										  
			Link.l1 = "嗯, 也许我可以去看看。 必要时我可以表现得很好很友善。 你能告诉我这笔交易的情况吗? ";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "在这个世界上一切都需要钱, 船长, 甚至信息。 我甚至会说, 尤其是信息。 我提议这样: 我会把这个消息以象征性的... 比如说五千比索的价格告诉你。 你觉得可以吗? ";										  
			Link.l1 = "为了关于在哪里可以高价出售火药的可疑信息支付五千比索? 不, 我想没有这个消息我也能活下去。 ";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "我想这笔交易我能赚的不止五千比索。 好吧, 我同意。 ";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "随你便, 船长。 无论如何, 我们交易得很愉快。 祝你好运... 别遇到巡逻队! ";										  
			Link.l1 = "你也是。 再见。 ";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "太好了, 船长! 你知道吗, 你是个了不起的顾客。 那么听着。 有人私下告诉我, 在缅因州的一些西班牙城市, 火药出现了问题。 不知是因为热带暴雨还是其他原因 - 总之, 守卫殖民地的堡垒里储备很少。 而这个堡垒的指挥官正在寻找能帮助他解决这个难题的人。 \n只有两个问题: 首先, 这是件敏感的事, 指挥官不会和任何骗子谈论; 其次, 我们说的是很大一批货物 - 不是每艘船都能装那么多火药, 所以你可能需要一支舰队。 而且不是每个船长都愿意把自己的船变成漂浮的炸弹, 如果被偏离的炮弹击中, 很容易摧毁整个岛屿。 ";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "抱歉, 但我已经知道这笔交易了。 无论如何, 这笔交易的价值超过金钱, 所以你应得五千比索。 ";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "有价值的信息, 谢谢。 如果我在缅因州, 我会询问当地堡垒的指挥官他们的难处。 我希望能以某种方式处理这些问题或利用它们, 呵呵。 ";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "事情就是这样。 无论如何, 我们交易得很愉快。 祝你好运... 别遇到巡逻队! ";										  
			Link.l1 = "你也是。 再见。 ";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "事情就是这样。 无论如何, 我们交易得很愉快。 祝你好运... 别遇到巡逻队! ";										  
			Link.l1 = "你也是。 再见。 ";
			Link.l1.go = "exit"; 
		break;
		// <-- 传奇版 危险货物
	}
}