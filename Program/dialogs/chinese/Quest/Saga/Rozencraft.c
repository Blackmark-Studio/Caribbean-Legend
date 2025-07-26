// 米哈伊尔.罗森克拉夫特 - 荷兰船长, 巴考特任务买家
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "嗯... 莫利根在哪儿? 他不想亲自见我吗? ";
				link.l1 = "我们可怜的保罗发烧了。 他没心情交易。 我代替他来。 ";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "你想要什么, 先生? ";
				link.l1 = "我猜你在等著买些铁木? ";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "谁告诉你的鬼话, 先生? 我没在等任何人或任何东西。 我的船按威廉斯塔德总督的命令在当地巡逻。 所以, 劳驾离开我的船, 你一定搞错了。 ";
			link.l1 = "嗯... 我明白了。 抱歉打扰你。 ";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "我们不是已经谈过这个了吗, 先生? ";
			link.l1 = "是, 是。 我这就离开并登上我的船。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "你是谁? ";
			link.l1 = "你不在乎和谁交易吗? 我带了铁木来卖。 多少钱? ";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "根据协议 - 每件四十杜布隆。 ";
			link.l1 = "嗯... ";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "兄弟, 我和莫利根有协议。 这是个好价格, 你找不到更好的了。 所以别像店里的农夫一样。 你有多少铁木? ";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+"。 ";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "太棒了。 这比我预期的多。 给, 拿上金子。 如果你有更多铁木, 去圣马丁的酒馆找... 你知道是谁。 他会为我们安排会面。 我看你比那个白痴莫利根强多了。 ";
				link.l1 = "好的。 成交。 ";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // 巴考特销售生成器
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "很好。 给, 拿上金子。 如果你有更多铁木, 去菲利普斯堡的酒馆找... 你知道是谁。 他会和我联系。 我看我们和你做生意不比和那个白痴莫利根差。 ";
				link.l1 = "好的。 成交。 ";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // 巴考特销售生成器
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "嗯... 我期望更多。 好吧。 给, 拿上金子。 告诉莫利根下次必须带不少于一百件的货。 ";
				link.l1 = "好的。 我会告诉他。 ";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "你在开玩笑吗? 我和莫利根有协议, 批次不能少于五十件! 滚开, 等你有足够了再回来。 ";
			link.l1 = "好, 好, 冷静点。 ";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // 不再纠缠, 在生成器中移除
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// 计算我们该给斯文森多少
				int ibak = makeint((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // 扬的份额
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "此外, 如果我得到铁木, 我可以通过菲利普斯堡酒馆的人安排与迈克尔.罗森克拉夫特会面来出售。 ");
				pchar.questTemp.Saga = "removebakaut";
				// 保存罗森克拉夫特的船, AI会检查是否到达
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; // 移除中断
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; // 移除中断
				// 为罗森克拉夫特沉船设置新的中断
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------巴考特销售生成器-----------------------------------------------
		case "bakaut":
			dialog.text = "哦, 我的老朋友! 有铁木要卖吗? ";
			link.l1 = "正是, 迈克尔。 我们交易吧。 ";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "你有多少? 我需要不少于"+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+"的批次。 ";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "我知道。 我有"+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SANDAL))+"你急着要的铁木。 ";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "嗯。 不幸的是我没有那么多。 ";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "该死的, 他们没警告你吗? 还是老鼠吃了木头? 我需要"+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+"一根也不能少。 下次按我的代理人告诉你的数量带。 希望你不会再让我失望, 否则我不得不拒绝你的服务。 ";
				link.l1 = "好的, 先生, 我以后会更注意。 ";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "你第二次耍我了。 我不喜欢这样。 知道这是最后警告, 下次我会拒绝你的服务。 ";
					link.l1 = "该死的老鼠损坏了我的货物! 我向你保证, 迈克尔, 这是最后一次。 ";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "现在我的耐心耗尽了! 我不想再和你做生意了。 滚开, 忘了我。 ";
					link.l1 = "但是先生... ";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; // 移除中断
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // 超额
				dialog.text = "哇! 抱歉, 朋友, 但我只能买"+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", 我没有钱买你所有的货物。 我期望的是每批"+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+"件, 每件四十杜布隆... ";
				link.l1 = "好的。 现在拿"+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", 剩下的下次再卖。 ";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "很好。 价格照旧, 每件四十杜布隆。 ";
				link.l1 = "对我来说可行。 拿你的批次。 ";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "与你做生意很愉快。 如果你想卖更多铁木, 再来见我。 ";
			link.l1 = "再见, 先生。 我们的合作对我很有利。 再见! ";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; // 移除中断
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}