// 鲨鱼的副官莱顿.德克斯特
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
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "你想要什么, 小子? 去找鲨鱼, 他才是这里的老大。 ";
				link.l1 = "至少让我和你打个招呼吧, 这也违反规矩吗? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "莱顿, 鲨鱼说你有一张岛的地图。 你卖吗? ";
					link.l2.go = "map";
				}
				dialog.text = "啊, "+GetFullName(pchar)+"! 你是找我有事还是又想聊天? 如果是聊天, 下次带瓶朗姆酒来, 哈哈! ";
				link.l1 = "不, 没什么特别的事。 下次一定给你带朗姆酒。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "哈! 你还挺会开玩笑, 小子? 好吧... 我叫莱顿.德克斯特, 是鲨鱼的二把手, 现在是这该死的废弃船只城的代理首领。 平时我负责卖补给品, 还要想法从那个懒鬼法奇奥身上捞点钱。 ";
			link.l1 = "我叫"+GetFullName(pchar)+"。 幸会! ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 鲨鱼按选项N死亡
		case "admiral":
			dialog.text = "我猜你已经听说史蒂文死了。 是独角鲸干的。 ";
			link.l1 = "没错, 我知道... 所以呢, 你现在是首领了? ";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour传奇版本	
		break;
		
		case "admiral_1":
			dialog.text = "正是。 查德叛变到独角鲸那边, 史蒂文死了, 所以作为二把手, 我自然成了首领。 有意见吗? ";
			link.l1 = "没有。 没意见。 ";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "很好。 说说你的问题吧。 ";
			link.l1 = "你会为史蒂文的死向独角鲸复仇吗? ";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "你是说我会向他们宣战吗? 不会。 有更好的办法让他们付出代价。 首先我会把他们买补给的价格提高三倍\n如果他们攻击‘圣奥古斯丁’, 我们就狠狠反击。 然后我会和里瓦多斯谈判。 当然, 我们不能信任那些肮脏的黑鬼, 他们还在为巫师的死记恨我们, 但任何问题都能用朗姆酒和食物解决。 ";
			link.l1 = "明白了。 好了, 莱顿, 我得走了... ";
			link.l1.go = "admiral_4";
		break;
		
		// 剧情交叉节点
		case "admiral_4":
			dialog.text = "等等。 史蒂文告诉我你在想办法离开废弃船只城, 然后驾船回来? ";
			link.l1 = "这是我的计划。 ";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "拿着这些航行指南。 用它们你能安全从海上返回这里。 意思是: 你不会在礁石上搁浅, 不会被洋流卷走, 船也不会在外围撞上其他残骸\n没有它们, 你要么找不到通道, 要么船就会成为这里的新残骸。 记住必须用吃水浅的小船, 比如单桅纵帆船。 双桅纵帆船。 双桅横帆船... 不能超过四级船。 明白了吗? ";
			link.l1 = "明白。 谢谢! 这正是我需要的。 ";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "别忘了货舱装满补给品。 我会给你优惠价。 别把这文件给任何人, 我们的基地必须保密。 我给你这个文件只是因为史蒂文本来就打算给你, 而且你是扬.斯文森的朋友。 ";
			link.l1 = "放心吧。 再次感谢, 回头见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour传奇版本
			// 移除任务物品
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "你逃离废弃船只城的计划有进展吗, "+pchar.name+"? ";
			link.l1 = "还没有, 莱顿。 我正在努力。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// 鲨鱼按选项M死亡
		case "admiral_7":
			dialog.text = "你来了, "+pchar.name+"。 我有几件事要和你谈谈。 ";
			link.l1 = "据我所知, 史蒂文死后你接管了他的位置。 所以你现在是首领了? ";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "正是。 作为二把手, 现在我是首领了。 有意见吗? ";
			link.l1 = "没意见。 你完全有权担任这个职位。 ";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "很高兴我们达成共识。 需要什么就告诉我。 ";
			link.l1 = "你会为史蒂文的死向独角鲸复仇吗? ";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "你是说我会向他们宣战吗? 不会。 有更好的办法让他们付出代价。 我会把他们买补给的价格提高三倍\n如果他们攻击‘圣奥古斯丁’, 我们就狠狠反击。 另外, 我们现在和里瓦多斯关系不错, 所以独角鲸不敢轻举妄动。 ";
			link.l1 = "明白了。 你还有别的事要告诉我吗? 还是我可以走了? ";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "有。 我认为只有一个办法能搞定独角鲸。 虽然不完美, 但我别无选择。 我们将从两个方向攻击他们。 一队勇猛的杀手乘长艇登上‘刻瑞斯铁匠号’, 同时另一队联合里瓦多斯突袭‘埃斯梅拉达’。 这要么能彻底消灭他们, 要么逼他们逃到‘圣盖博’。 第二种情况最可能, 圣盖博防御坚固, 围攻需要很长时间。 但不管怎样, 我们会赢。 ";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // 鲨鱼节点
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "我们在等你和唐纳德.格林斯彭的谈话结果。 这是非常重要的事, 别浪费时间。 ";
			link.l1 = "我这就去! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "是的, 我有地图。 你想买吗? 欢迎购买, 只要二百杜布隆就归你。 ";
			link.l1 = "用比索行吗? ";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "不行。 我要金币。 没得商量。 ";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "好吧。 给你金币, 我买了。 ";
				link.l1.go = "map_2";
			}
			link.l2 = "我没那么多金币。 也许以后... ";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveDublonsFromPCharTotal(200);
			PlaySound("interface\important_item.wav");
			Log_Info("你获得了废弃船只城地图");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "好交易, 小子! 拿好地图。 这价格很值 - 我在城里爬了整整一周才画出来, 其实卖得很便宜了。 ";
			link.l1 = "便宜? ! 好吧。 不管怎样谢谢你。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// 玩家恶搞游戏的结局
		case "LSC_GameOverPrison":
			dialog.text = "站住, 伙计! 没错, 鲨鱼说得对, 这家伙疯了。 多少人因他而死... 兄弟们把他铐起来, 扔到货舱里! ";
			link.l1 = "... ";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "史蒂文让我代替他成为城市首领 - 我猜你要和他一起回加勒比。 我会留在这里继续经营, 我们不想失去这么好的基地。 我想告诉你, 这里永远欢迎你。 ";
			link.l1 = "谢谢, 莱顿。 我想我会经常回到这个岛的。 ";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "啊, 我的老朋友"+GetFullName(pchar)+"! 你用史蒂文的航行指南找到废弃船只城了, 对吧? 我非常非常高兴见到你。 这里永远欢迎你。 ";
			link.l1 = "谢谢, 莱顿。 我想我会经常回到这座城市的。 ";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "很好。 你有食物要卖吗? 我愿意以双倍价格购买。 ";
			if (iTrade > 0)
			{
				link.l1 = "有, 我可以卖给你一些补给品。 ";
				link.l1.go = "trade";
			}
			link.l2 = "可惜, 我现在没什么可卖的。 ";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // 仓库囤积上限=15000
		break;
		
		case "return_2":
			dialog.text = "真遗憾。 下次别忘了带 - 我会出高价。 ";
			link.l1 = "好的。 我会尽量记住... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "多少? ";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "该死, 你喝得烂醉如泥, 伙计! 我服了! 去睡一觉, 我们回头再交易。 ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "这么点量我连椅子都懒得挪。 多带点来! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "你船上没补给怎么航行, 伙计? 想让手下饿死吗? 至少给自己留"+FindRussianQtyString(GetCrewQuantity(pchar))+"。 ";
				link.l1 = "嗯, 你说得对。 ";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // 伐木工
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "哇, 伙计, 太多了! 我们没吃完就会腐烂。 现在最多只能拿"+iTemp+"。 ";
			 link.l1 = "随你吧。 ";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? 好。 我付你"+FindRussianMoneyString(iMoney)+"。 成交? ";
			link.l1 = "当然! 和你做生意很愉快! ";
			link.l1.go = "trade_2";
			link.l2 = "嗯。 不, 我改变主意了。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // 伐木工 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "成交。 我付你"+FindRussianMoneyString(iMoney)+"买这些货物。 够吗? ";
			link.l1 = "当然! 交易愉快! ";
			link.l1.go = "trade_4";
			link.l2 = "嗯。 不, 我改变主意了。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // 伐木工 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // 仓库囤积半年量
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "真该死! 我的仓库满了! 未来半年都不用买补给了。 ";
				link.l1 = "好。 那我半年后再给你带下一船补给。 ";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "太好了! 下次多带点来。 ";
				link.l1 = "一定! ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // 仓库囤积半年量
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "不错! 我的仓库满了。 未来半年都不用买粮食了。 ";
				link.l1 = "好。 那我半年后再给你带下一船补给。 ";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "太好了! 下次多带点来。 ";
				link.l1 = "一定! ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // 德克斯特首领的标准对话
			dialog.text = "啊, "+GetFullName(pchar)+"! 很高兴见到你! 你想要什么? ";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "想从我这儿买些补给品吗? ";
				link.l1.go = "trade";
			}
			link.l2 = "没什么, 只是想知道你过得怎么样。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}