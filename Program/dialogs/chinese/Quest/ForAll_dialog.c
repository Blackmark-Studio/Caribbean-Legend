void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "我们没什么可谈的。 ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城镇的市民, 希望你把刀收起来。 ", "听着, 我是这个城镇的市民, 希望你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好的。 ", "当然。 ", "好吧... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, " + GetSexPhrase("伙计","姑娘") + ", 带着武器乱跑。 我会紧张的... ", "我不喜欢有" + GetSexPhrase("男人","人") + "拿着武器在我面前走。 这会吓到我... ");
				link.l1 = RandPhraseSimple("我知道了。 ", "我知道了。 ");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//------------------------- —女服务员任务 --------------------------------
		//抢劫者
		case "WaitressBerglar":
			dialog.text = "来吧, 伙计, 让我看看你的口袋。 ";
			link.l1 = "什么?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "你听到了。 快点, 少废话。 我不喜欢说话... ";
			link.l1 = "该死的! " + pchar.questTemp.different.FackWaitress.Name + "和你是一伙的吗?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "她是, 她是... 把你的钱给我, 不然我就把你开膛破肚!";
			link.l1 = "不! 我要把你开膛破肚!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "拿去吧, 混蛋! 但你不会就这么算了... ";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "当然, 这没什么好争论的。 再见, 伙计。 记住, 你还没帅到让女服务员们着迷。 下次放聪明点!";
			link.l1 = "... 快走吧。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "如你所愿... ";
			link.l1 = "那我就不客气了... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//女服务员
		case "Waitress":
			dialog.text = "我在这儿! 你需要我吗, 帅哥?";
			link.l1 = "该死, 这进展也太快了... ";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "我们别浪费时间了!";
			link.l1 = "呵, 我完全同意!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//------------------------- —追赶丢失航海日志的船长 --------------------------------
		//在城镇遇见
		case "PortmansCap":
			dialog.text = "日安。 我叫" + GetFullName(npchar) + "。 我是" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + "‘" + npchar.Ship.name + "’的船长。 "; 
			link.l1 = "太好了! 终于找到你了。 ";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "找到我?!";
			link.l1 = "是的。 嗯, 我把你落在" + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + "港口办公室的航海日志带来了。 ";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "该死! 现在我知道是在哪里弄丢的了。 这次丢失几乎在我的船上引发了哗变... ";
			link.l1 = "所以结果好就一切都好。 拿着你的航海日志, 我们谈谈我的报酬。 ";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "来得正好, 我还没开始写新的, 所以我会尽我所能支付你。 " + FindRussianMoneyString(sti(npchar.quest.money)) + ", 再接受几件我私人的珠宝。 ";
				link.l1 = "不错。 拿着吧。 ";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //降低报酬
					dialog.text = "嗯, 你知道, 我已经开始写新的航海日志了。 不过, 旧的对我仍然有价值。 所以我会付你" + FindRussianMoneyString(sti(npchar.quest.money)) + ", 再接受几件我私人的珠宝。 ";
					link.l1 = "那就成交。 拿着你的航海日志。 ";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "我已经开始写新的航海日志了。 并且把旧日志上的所有记录都转移了。 我不再需要它了, 所以没有钱给你。 ";
					link.l1 = "太好了。 所以这通追赶完全是白费力气。 ";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "谢谢你。 再见, " + GetSexPhrase("伙计","姑娘") + "。 ";
			link.l1 = "你也一样... ";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //移除出海计时器
			npchar.LifeDay = 2; //几天后移除船长
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //清理群组, 以防万一
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //释放港口管理员的个人任务标志
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "哈, 下次注意把握时机。 ";
			link.l1 = "说得对。 ";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //移除出海计时器
			npchar.LifeDay = 2; //几天后移除船长
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //清理群组, 以防万一
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //释放港口管理员的个人任务标志
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//在海上追上
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "在我的船甲板上向你致意。 说实话, 你把我吓得屁滚尿流 —我以为独眼神驹猎人在追捕我... ";
				link.l1 = "不, 船长, 我今天心情不错。 我是来帮你的。 ";
			}
			else
			{
				dialog.text = "在我的船甲板上向你致意!";
				link.l1 = "你好, 船长! 我一直在找你。 ";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "为什么?";
			link.l1 = "你把航海日志忘在" + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + "港口管理员的家里了。 ";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "该死, 原来就是那个地方! 这次丢失已经给我带来了一堆麻烦。 ";
				link.l1 = "报酬呢?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //降低报酬
					dialog.text = "该死, 现在我知道是在哪里弄丢的了! 谢谢你, 但你找我找得太久了。 我已经开始写新的航海日志了。 不过, 旧的记录仍然需要转移到新日志中... ";
					link.l1 = "那多少钱?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "我已经开始写新的航海日志了。 并且把旧日志上的所有记录都转移了。 我不再需要它了。 ";
					link.l1 = "所以你不需要旧日志了? 真的?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "我可以付你" + FindRussianMoneyString(sti(npchar.quest.money)) + "和一些我的珠宝。 这是我能负担的全部了。 ";
			link.l1 = "那好吧。 拿着你的日志。 ";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "再次感谢。 再见, 伙计。 ";
			link.l1 = "继续加油。 ";
			link.l1.go = "exit";
			npchar.LifeDay = 30; //三十天后移除船长
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //船长任务标志已完成。 遭遇会航行到目的地并消失
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //释放港口管理员的个人任务标志
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "当然。 如果你要追某人, 就得更快一点。 ";
			link.l1 = "首先别把你的航海日志弄丢了。 好吧。 ";
			link.l1.go = "exit";
			npchar.LifeDay = 30; //三十天后移除船长
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //船长任务标志已完成。 遭遇会航行到目的地并消失
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //释放港口管理员的个人任务标志
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "我以为我们已经解决了所有问题。 ";
			link.l1 = "是的, 没错。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//------------------------- —寻找被盗船只 --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "问候。 你想要什么?";
			link.l1 = "没什么, 只是想听听消息。 有什么可卖的吗?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "我没有什么可卖给你, 也没有任何消息。 顺便说一句, 我不希望你出现在这里。 明白了吗?";
			link.l1 = "明白了... 再见, 伙计。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "我告诉过你, 你在这里无事可做!";
			link.l1 = "我知道... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//登船
		case "SeekCap":
			dialog.text = "你为什么攻击我?!";
			link.l1 = "我必须把船归还给它的主人..";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "归还给什么样的主人? 我就是主人!";
			link.l1 = "不, 你不是。 我不知道这艘船的主人是谁。 但它被偷了, 我必须把它还回去。 ";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "操! 但对我来说这还没完。 至少我要杀了你... ";
			link.l1 = "你只能试试。 ";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------市民搜索任务生成器--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //船长	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //移除船长死亡中断
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除任务发布者死亡中断
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------贵族搜索任务---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "问候, " + GetAddress_Form(NPChar) + "。 我看你是一艘船的船长? 我叫" + GetFullName(npchar) + ", 想和你做个交易。 ";
			link.l1 = RandPhraseSimple("很抱歉, 我得走了。 ", "很抱歉, 我没时间和你交谈。 ");
			link.l1.go = "SCQ_exit";
			link.l2 = "我洗耳恭听。 ";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //方案A
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "那就听着。 " + SelectNB_battleText() + "\n我既没有时间也没有机会找到他。 因为, 他从不到这里来。 我想你现在明白了, 你明白我要向你提议什么吗?";
						link.l1 = LinkRandPhrase("我想, 我得去追踪某个人并把他带给你?","也许, 去找到那个混蛋并把他带给你?","你想让我找到这个人并把他带到这里来?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //方案B
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "那就听着。 " + SelectNB_battleText() + "\n我既没有时间也没有机会找到他。 因为, 他从不到这里来。 我想你现在明白了, 你明白我要向你提议什么吗?";
						link.l1 = LinkRandPhrase("我想, 你是想让我去追踪某个人并把他带给你?","也许, 去找到那个混蛋并把他带给你?","你想让我找到这个人并把他带到这里来?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //方案C
					SelectNB_peaceText(npchar);
					dialog.text = "那就听着。 实际上, " + npchar.quest.text + "在海军当船长。 他甚至不知道我也在这里!\n我想见见他, 但我既没有时间也没有机会找到他... ";
					link.l1 = "我猜你是想让我找到这位船长并告诉他你的情况?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //方案A
			dialog.text = "不完全是。 找到他, 但不需要把他带到这里来。 杀了他就够了。 把他和他肮脏的船一起沉了, 开枪打死他, 用你的刀刺死他 —我真的不在乎, 只要让这个混蛋停止用他的存在污染这个世界。 报酬会很丰厚。 ";
			link.l1 = "哈! 太简单了。 告诉我他的名字和船名。 ";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //个人任务标志
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //任何国家除了海盗
			dialog.text = "" + npchar.quest.SeekCap.capName + "的" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + "名为" + npchar.quest.SeekCap.shipName + "。 他经常光顾" + XI_ConvertString("Colony" + npchar.quest.Qcity) + "港。 我会付你" + FindRussianMoneyString(sti(npchar.quest.money)) + "金币。 ";
			link.l1 = "这就是我需要知道的。 我在海上会留意的。 当我找到你的朋友时, 我会让他...'压低声音'... 不再活着。 ";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "这种工作这钱不够。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "很高兴我们达成了协议。 我会等你回来。 ";
			link.l1 = "我在哪里能找到你? 现在就说清楚, 我不想浪费时间找你。 ";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "每天早上我都去当地教堂做礼拜。 你可以每天早上8点到9点在那里找到我。 ";
			link.l1 = "那就成交! 期待很快有结果。 ";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//删除幽灵标志, 否则城市为空
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //方案B
			dialog.text = "正是。 找到他并把他带给我。 要活的。 我想亲自处理他。 我会慷慨地报答你。 ";
			link.l1 = "好吧, 我可以试着找到他, 但需要细节。 ";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //个人任务标志
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //任何国家除了海盗
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "那个混蛋叫" + npchar.quest.SeekCap.name + "。 他在" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + "名为" + npchar.quest.SeekCap.shipName + "上服役, 由" + npchar.quest.SeekCap.capName + "指挥。 这艘船经常出现在" + XI_ConvertString("Colony" + npchar.quest.Qcity) + "港。 我会为这项工作付你" + FindRussianMoneyString(sti(npchar.quest.money)) + "金币。 ";
			link.l1 = "这对我来说足够了。 我在公海上会留意的。 ";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "这种工作这钱不够。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "很高兴我们达成了协议。 我会等你回来。 ";
			link.l1 = "我在哪里能找到你? 现在就说清楚, 我不想浪费时间找你。 ";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "每天早上我都去当地教堂做礼拜。 你可以每天早上8点到9点在那里找到我。 ";
			link.l1 = "那就成交! 期待很快有结果。 ";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//删除幽灵标志, 否则城市为空
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //方案C
			dialog.text = "正是! 找到他并告诉他我住在这个镇上。 我会为你的服务付费。 ";
			link.l1 = "嗯... 我可以试试。 告诉我细节。 ";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //个人任务标志
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //国家=任务发布者国家
			dialog.text = "他叫" + npchar.quest.SeekCap.capName + "。 他在" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + "‘" + npchar.quest.SeekCap.shipName + "’上服役。 他经常访问" + XI_ConvertString("Colony" + npchar.quest.Qcity) + "。 我会为这项工作付你" + FindRussianMoneyString(sti(npchar.quest.money)) + "金币。 ";
			link.l1 = "成交! 我想我很快就会找到你的朋友。 ";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "这对我来说不够。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "很高兴我们达成了协议。 我会等你回来。 ";
			link.l1 = "我在哪里能找到你? 现在就说清楚, 我不想浪费时间找你。 ";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "我总是去当地教堂参加晚祷。 你可以每天下午6点到8点在那里找到我。 ";
			link.l1 = "那就成交! 期待很快有结果。 ";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//删除幽灵标志, 否则城市为空
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> 陆上对话, 方案A
		case "NM_battleCap":
			dialog.text = "那么? 你想要什么, 先生?";
			link.l1 = "你是" + GetFullName(npchar) + "船长吗?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "是的, 我是。 什么事?";
			link.l1 = "有一个人对你很感兴趣, 他叫" + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + "。 记得吗?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "我听说你的货舱里有很多桃花心木。 我想买。 你会卖给我吗?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "我第一次听到这个名字。 你弄错了, 船长。 我们说完了吗?";
			link.l1 = "嗯。 好吧, 打扰了... ";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "哦, 真的吗? 但他确实清楚地记得你... 他提到了你欠他的债... ";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "什么债? 你在说什么?";
			link.l1 = "荣誉债!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "你弄错了。 我不交易任何木材。 你在这里的出现让我觉得很可疑。 我认为你最好离开我的船!";
			link.l1 = "好吧, 我只是问问。 再见。 ";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> 陆上和甲板对话相同, 方案B
		case "NM_prisonerCap":
			dialog.text = "那么? 你想要什么, 先生?";
			link.l1 = "你是" + GetFullName(npchar) + "船长吗?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//任务发布者
			dialog.text = "是的, 是我。 什么事?";
			link.l1 = "一个叫"+sld.quest.SeekCap.name+"的人在你手下服役吗?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//任务发布者
			dialog.text = "是的。 他是我的军官之一。 现在告诉我你为什么问这个?";
			link.l1 = "我当然会告诉你。 我受" + XI_ConvertString("Colony" + sld.city + "Gen") + "当局的命令寻找这个人, 我有权逮捕他并将他送到" + XI_ConvertString("Colony" + sld.city) + "。 我请求你协助我, 以便我们和平解决此事。 ";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "真的吗? 这样的人在我的船员里服役? 你是认真的?";
				link.l1 = "别费心了, " + GetAddress_FormToNPC(NPChar) + "。 我会派一艘长艇到你的船上, 我们自己带他走。 ";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "你这么说。 你知道吗, 先生, 我根本不在乎他的过去。 这不关我的事。 顺便问一下, 你是谁? 当局? 真的? 哈! 我不会把我的人交给你或其他任何人。 这次谈话结束了。 你走吧!";
				link.l1 = "错误的选择... 糟糕的选择!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "做你该做的事。 ";
			link.l1 = "正在办。 ";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//вeзeниe
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квeстодатeль
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "我们说完了吗, 船长?";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> 陆上和甲板对话相同, 方案C
		case "NM_peaceCap":
			dialog.text = "日安。 你想要什么, 船长?";
			link.l1 = "你是" + GetFullName(npchar) + "船长, 对吗?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//任务发布者
			dialog.text = "你说得对。 你有什么事吗?";
			link.l1 = "我有。 一个叫" + GetFullName(sld) + "的人在找你。 他希望你尽快去拜访他。 他住在" + XI_ConvertString("Colony" + npchar.quest.cribCity + "Voc") + "。 ";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "哈! 这么说, 他也搬到新大陆了? 那我真的应该去拜访他... 谢谢你的消息, 先生!";
			link.l1 = "不客气。 我的工作会由你的朋友支付报酬。 祝你好运, " + GetAddress_FormToNPC(NPChar) + "!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//任务发布者
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //将任务标志补充为'已完成'
			//删除船长数据库记录
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "很高兴认识你, " + GetAddress_Form(NPChar) + "!";
			link.l1 = "我也很高兴, 船长。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> 甲板相遇, 方案A
		case "NM_battleDeck":
			dialog.text = "你好, " + GetAddress_Form(NPChar) + "。 你想要什么?";
			link.l1 = "我听说你的货物里有很多红木, 我想买。 你会卖吗?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "你弄错了。 我不交易任何木材, 而且你的来访让我觉得很可疑。 我认为你最好离开我的船!";
			link.l1 = "好吧, 我只是问问。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "你想惹麻烦吗, 先生? 要我再说一遍吗?";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> 登船, 方案A
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "你为什么攻击我的船, 恶棍?";
			link.l1 = "我来这里是为了代" + XI_ConvertString("Colony" + npchar.quest.cribCity) + "的人向你问好, 他叫" + GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]) + "。 我希望你现在了解情况了。 ";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "不可能! 那我就没什么可失去的了... ";
			link.l1 = "那你的命呢?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> 登船, 方案B
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квeстодатeль
			dialog.text = "你为什么攻击我的船, 恶棍?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "有想法吗? 我曾请求你和平地把你的军官交给我。 现在我要带走他, 还有你和你的破船!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "有一个恶棍在你手下服役。 他叫" + sld.quest.SeekCap.name + "。 " + XI_ConvertString("Colony" + npchar.quest.cribCity) + "的当局非常想见他。 他将被逮捕并关进我的船舱。 ";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "这就是你在我船上大肆屠杀的原因? 混蛋! 我还有些力气... 我要杀了你!";
			link.l1 = "比你强壮的人都试过... ";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завeршeния квeста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квeста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модeль для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> 贵族任务结果
		case "SCQ_NM_result":
			dialog.text = "你说呢, 船长? 我的事有进展吗?";
			link.l1 = "还没有。 但我正在处理。 ";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://任务完成, 方案A
					dialog.text = "你说呢, 船长? 我的事有进展吗?";
					link.l1 = "有。 你会喜欢的。 " + npchar.quest.SeekCap.capName + "死了, 他的" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + "沉到了海底。 ";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://任务完成, 方案B
					dialog.text = "你说呢, 船长? 我的事有进展吗?";
					link.l1 = "有。 你会喜欢的。 " + npchar.quest.SeekCap.Name + "正被关押在我船的船舱里。 ";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://任务完成, 方案C
					dialog.text = "啊哈, 你来了。 很高兴见到你。 我得知你成功完成了任务!";
					link.l1 = "你的朋友拜访你了吗?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "太棒了! 我就知道我可以指望你。 给, 拿着你的金币。 你应得的。 ";
			link.l1 = "谢谢。 如果你再有敌人, 再跟我说。 ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 50);//运气
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "太棒了! 我会命令我的人立即把他从你的船上带走。 他现在跑不掉了! 给, 拿着你的金币。 你应得的。 ";
			link.l1 = "谢谢。 随时找我做这样的工作。 ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//航海
			AddCharacterExpToSkill(pchar, "Leadership", 150);//领导力
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "是的, 他来过, 跟我说起了你。 给, 拿着你的金币。 你应得的。 ";
			link.l1 = "谢谢。 再见, 先生!";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //移除可能的出海计时器
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //移除船长死亡中断
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//航海
			AddCharacterExpToSkill(pchar, "Leadership", 200);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 50);//运气
		break;
//< —贵族搜索任务

		//========= 男性任务 ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("你好, 船长。 我想请求你的帮助。 ", 
				"船长! 你能帮我吗? 求你了。 ", 
				"船长, 我在请求你的帮助! ");
			link.l1 = RandPhraseSimple("我很忙。 ", "我很着急。 ");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("怎么了? ", "说说什么困扰你。 也许我能帮上忙。 ");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//减少一次下一个任务发布者主动开口的机会
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//减少一次下一个任务发布者主动开口的机会
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //船长	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //移除船长死亡中断
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除任务发布者死亡中断
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//选择任务
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "一年前, 一位船长答应带我去" + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + "。 但我在他船上时被扔进了货舱, 后来被卖为奴隶。 我勉强活了下来, 好几次都濒临死亡... 不管怎样, 我想提醒我的‘朋友’我还活着。 "; // belamour gen
					link.l1 = "你是什么意思? 确切地告诉我你想要什么。 ";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "我的妻子被绑架了。 有个船长, 据说是海盗, 一直在追求她。 由于他的跟踪, 我妻子不得不整天待在家里。 我曾试图让镇上的当局帮助我们, 但失败了。 现在... ";
					link.l1 = "现在怎样? ";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "你知道, 我在找我的同乡。 三年前我们一起从欧洲来到这里寻找更好的生活。 我们走散了。 但不久前我听说他现在是一名贸易船长! 我自己尝试找过, 但失败了。 ";
					link.l1 = "所以呢? ";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// 前奴隶被恶棍船长俘虏的任务
		case "SCQ_Slave":
			dialog.text = "我要你找到他并杀了他。 我恨他恨得吃不下饭... ";
			link.l1 = "我明白... 我想我可以帮你。 告诉我他的名字和船名。 ";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "很抱歉, 我不感兴趣。 ";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //市民个人任务标志
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "" + npchar.quest.SeekCap.capName + "的" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + "名为" + npchar.quest.SeekCap.shipName + "。 我会付你" + FindRussianMoneyString(sti(npchar.quest.money)) + ", 再加上我所有的珠宝。 "; // belamour gen
			link.l1 = "我知道了。 我在海上会留意的。 如果找到目标... 就当他死了。 ";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "就这么点钱我可不干。 找别的傻瓜去报仇吧。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "这正是我想听到的! 哦, 我现在能吃饭了! 终于! 我得去吃点东西... ";
			link.l1 = "祝你胃口好。 事情一做完我就来找你。 ";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "我会在当地教堂等你。 ";
			link.l1 = "好。 ";
			link.l1.go = "exit";
			//==> 将任务发布者设置在教堂
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//海盗绑架市民妻子的任务
		case "SCQ_RapeWife":
			dialog.text = "我当时太疏忽了, 那个混蛋抓住我妻子并把她带上了他的船。 我请求你找到这个恶棍! ";
			link.l1 = "嗯, 我为什么要和一个恶棍打架? ";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //市民个人任务标志
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - 市民妻子的名字
			forName.lastname = npchar.lastname; //姓氏和丈夫的一样
			dialog.text = "我不富有, 但我很乐意把我所有的贵重物品都给你! 如果你救回我妻子并带给我, 我会付你" + FindRussianMoneyString(sti(npchar.quest.money)) + ", 再加上我所有的珠宝。 ";
			link.l1 = "好, 我接了。 告诉我细节。 他的名字。 船名和你妻子的名字。 ";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "不, 伙计, 这么点钱我不干。 抱歉... ";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "她叫" + npchar.quest.SeekCap.name + "。 那个混蛋叫" + npchar.quest.SeekCap.capName + ", 他在" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + "名为" + npchar.quest.SeekCap.shipName + "上航行。 "; // belamour gen
			link.l1 = "伙计, 船是航行的, 不是漂浮的... ";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "是是是, 非常抱歉! 我不是水手, 希望你能理解... ";
			link.l1 = "没关系, 别担心。 不管怎样, 事情一办完我就回来。 ";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "非常感谢! 我会在当地教堂等你。 但求你快点, 我真的很担心我妻子... ";
			link.l1 = "是啊, 我也不羡慕她。 ";
			link.l1.go = "exit";
			//==> 将任务发布者设置在教堂
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//寻找同乡的任务
		case "SCQ_Friend":
			dialog.text = "问题是, 我朋友没有任何房产。 他的船就是他的家。 所以我找不到他, 因为他总是在航行。 我负担不起无意义的旅行, 我得赚钱生活。 ";
			link.l1 = "如果你没钱, 我帮不了你... ";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //市民个人任务标志
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "我可以付你" + FindRussianMoneyString(sti(npchar.quest.money)) + ", 并且把我所有的珠宝都给你。 这是我现在能负担的全部了。 ";
			link.l1 = "这个数目我接受。 我接了。 其实你可以作为乘客和我一起, 这样找到你朋友时你就能见到他了。 ";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "这对我来说不够。 找别人去做吧。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "不, 我想我还是留在这里。 我们不知道这些搜索要多久, 我可能会花光所有钱。 我在这里有工作。 ";
			link.l1 = "我明白。 现在告诉我, 你朋友是谁, 他在哪艘船上。 ";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "他叫" + npchar.quest.SeekCap.capName + "。 据我所知, 他指挥一艘" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + "名为" + npchar.quest.SeekCap.shipName + "。 "; // belamour gen
			link.l1 = "我知道了。 好吧, 如果我见到你朋友, 会把你的情况告诉他。 ";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "谢谢你。 我会在当地教堂等你到来。 事情办完你就能拿到钱。 ";
			link.l1 = "当然。 再见, 期待很快有结果。 ";
			link.l1.go = "exit";
			//==> 将任务发布者设置在教堂
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// - —男性任务结果 ---
		case "SCQ_manResult":
			dialog.text = "日安, 船长。 已经有结果了吗? ";
			link.l1 = "提醒我你的问题... ";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "我想我已经报仇了, 是吗? ";
					link.l1 = "没错。 " + npchar.quest.SeekCap.capName + "死了, 他的" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + "沉到了海底。 ";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "你找到我妻子了! 我不敢相信! 真的吗? ";
					link.l1 = "真的。 她是我的乘客。 如果" + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + "真的是你妻子... 你可以带她回去。 ";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "日安, 船长。 你找到我的同乡了吗? ";
					link.l1 = "找到了, 并且告诉他你的情况了。 ";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "什么? 你真的忘了我让你为船长" + npchar.quest.SeekCap.capName + "奴役我一年的事报仇吗? ";
					link.l1 = "不, 没忘。 ";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "我简直不敢相信自己的耳朵! 你忘了我让你找到并救回我妻子吗? 她被一个叫" + npchar.quest.SeekCap.capName + "的海盗抓走了! ";
					link.l1 = "没忘。 ";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "等等... 你忘了你答应过要找我那个叫" + npchar.quest.SeekCap.capName + "的同乡吗? ";
					link.l1 = "没忘。 ";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "太好了, 我没看错你! 那么, 正如我答应的, 这是你的" + FindRussianMoneyString(sti(npchar.quest.money)) + "和珠宝。 感谢你的帮助。 ";
			link.l1 = "不客气... ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "哦, 我的上帝! 你救了我们! 请收下你的" + FindRussianMoneyString(sti(npchar.quest.money)) + "和珠宝。 要知道我们会永远为你祈祷! ";
			link.l1 = "想祈祷就祈祷吧, 我不介意。 ";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "太棒了! ... 给, 拿着" + FindRussianMoneyString(sti(npchar.quest.money)) + "和珠宝。 谢谢你, 船长。 ";
			link.l1 = "不客气, 朋友。 再见... ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= 女性任务 ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("你好, 船长。 你能帮我吗? ", 
				"船长! 能帮一个女人吗? 你会好心... ", 
				"船长, 帮帮" + GetSexPhrase("姑娘","我") + "。 ");
			link.l1 = RandPhraseSimple("我很忙。 ", "抱歉, " + GetAddress_FormToNPC(NPChar) + ", 但我没时间... ");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("你怎么了, " + GetAddress_FormToNPC(NPChar) + "? ", "说出你的问题, " + GetAddress_FormToNPC(NPChar) + "。 我会尽力帮你。 ");
			link.l2.go = "SCQ_woman_1";
		break;
		//选择任务
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "我丈夫是个商人, 他给周围每个殖民地送货。 三个月前他出海了, 至今未归! ";
					link.l1 = "你认为他出事了吗? ";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = "" + GetSexPhrase("船长, 我看你是个勇敢的船长, 完美的无赖","船长, 我看你是个坚强的女人, 能对付任何男人") +"... ";
					link.l1 = "你为什么这么说, " + GetAddress_FormToNPC(NPChar) + "? ";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "船长, 求你帮帮我! 我丈夫被抓了! 你能救他吗? ";
					link.l1 = "等等, 我没明白。 谁被谁抓了? ";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//女人寻找商人丈夫的任务
		case "SCQ_Hasband":
			dialog.text = "我不知道, 但我仍然希望他只是太忙了没时间给我写信。 他本可以给我寄封信的, 他知道我担心他! ";
			link.l1 = "海上不安全, 什么事都可能发生... ";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //市民个人任务标志
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "正是! 你明白我在说什么。 你看起来像个" + GetSexPhrase("勇敢的船长","勇敢的姑娘") + ", 所以我想请你找到我丈夫。 我准备付你" + FindRussianMoneyString(sti(npchar.quest.money)) + ", 再加上我所有的珠宝。 ";
			link.l1 = "好。 如果我在海上或其他地方遇到你丈夫, 会把你的担心告诉他。 告诉我他的名字和船名。 ";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "这么点钱我不感兴趣。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "他叫" + npchar.quest.SeekCap.capName + "。 他在" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + "名为" + npchar.quest.SeekCap.shipName + "上航行。 ";  // belamour gen
			link.l1 = "我知道了。 现在你需要等待, 尽量多待在教堂, 这样我才能找到你。 ";
			link.l1.go = "exit";
			//==> 将任务发布者设置在教堂
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//被拒绝女人的复仇任务
		case "SCQ_Revenge":
			dialog.text = "" + GetSexPhrase("我这么说, 先生, 是因为我想雇你做你擅长的事... 这么说吧。 ","我想请你帮我, 希望你能以女人的身份理解我。 ") +"有个船长惹恼了我, 我想让他死。 ";
			link.l1 = "那个可怜人对你做了什么? ";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "这个混蛋骗了我。 他假装爱我, 甚至向我求爱。 而他这么做的原因, 是为了从我丈夫那里得到有价值的东西! 当这只狗得到他想要的东西后, 他告诉我那没什么意义... 我们只是朋友! ";
			link.l1 = "嗯, 也许他是对的? ";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "我看起来像个傻瓜吗? ! 你认为我分不清求爱和空谈的区别吗? ";
			link.l1 = "你当然分得清... ";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "他利用了我, 那个恶棍! 我永远不会原谅他! ";
			link.l1 = "是的, 男人就是这样。 但是, 也许你可以冷静下来? 那没什么大不了的... ";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "没什么大不了? ! " + GetSexPhrase("你是某种道德家, 不是真正的海盗! ","看来你从未经历过这种情况! 哦, 是的, 谁会冒险... 而我只是个弱女子... ");
			link.l1 = "好, 够了。 我只是想知道, 你的意图有多认真。 ";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "该死的, " + GetSexPhrase("你根本不知道被拒绝的女人的报复是什么样子","你是个女人, 应该明白被拒绝的滋味! 我要报复") + "! ";
			link.l1 = "" + GetSexPhrase("确实, 从未有过这种经历","嗯, 你知道, 她只会哭一会儿, 打碎些玻璃, 然后就结束了") +"... ";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = "" + GetSexPhrase("算你幸运。 被拒绝和欺骗的女人是复仇女神, 裙子里的魔鬼! 世界上没有什么能平息她的愤怒","而我不是她。 没有什么能平息我的愤怒") + "! \n所以我要你亲自杀了他。 在他死之前, 他必须知道是谁在为他的死买单... ";
			link.l1 = "嗯, 我甚至不知道该说什么... 你打算付多少钱? ";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //市民个人任务标志
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "我所有的一切。 我会把珠宝和" + FindRussianMoneyString(sti(npchar.quest.money)) + "都给你! 成交? ";
			link.l1 = "我感兴趣。 告诉我他的名字和船名。 ";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "不感兴趣。 再见。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "那个恶棍叫" + npchar.quest.SeekCap.capName + ", 他在" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + "名为" + npchar.quest.SeekCap.shipName + "上航行。 "; // belamour gen
			link.l1 = "包在我身上, " + GetAddress_FormToNPC(NPChar) + "。 在当地教堂等我。 希望你能稍微冷静一下... ";
			link.l1.go = "exit";
			//==> 将任务发布者设置在教堂
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//女人的丈夫被海盗俘虏的任务
		case "SCQ_Pirates":
			dialog.text = "我解释一下。 问题是我丈夫只是个普通人, 被海盗抓了! 他们见人就杀, 一个不留... ";
			link.l1 = "看来船长敢于反抗, 否则他们会放过船员的。 ";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "也许吧, 但我丈夫是个无辜的人, 他只是船上的乘客。 为了保命, 他不得不告诉他们自己很有钱。 海盗放过了他, 甚至没把他关进货舱。 ";
			link.l1 = "你怎么知道的? ";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "他设法给我寄了封信, 说他很好, 被关在船舱里, 不像其他囚犯。 ";
			link.l1 = "你打算怎么办? 不能就这样下去, 海盗迟早会看穿他的。 ";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "你也是海盗吗? 是是, 我知道... 我求你, 帮帮我们, 救救我丈夫! 他描述了那艘海盗船, 还写了船长的名字。 你找到他们不难! ";
			link.l1 = "不像你想的那么容易。 所有囚犯都是俘虏他们的船长的合法战利品, 而且这需要时间。 ";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "但你至少可以试试! 再说, 你有足够的时间搜索。 我丈夫不是傻瓜, 他假装是来自旧大陆的商人, 所以那些海盗现在还没向他要钱。 如果你救了他, 我会把所有的一切都给你! ";
			link.l1 = "你有什么? ";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //市民个人任务标志
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "不多, " + FindRussianMoneyString(sti(npchar.quest.money)) + "和我所有的珠宝... 但我会永远为你的灵魂祈祷! ";
			link.l1 = "是的, 确实不多... 好吧, 我准备帮你。 ";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "抱歉, 这对我来说不够。 ";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "谢谢你, 非常感谢! ";
			link.l1 = "如果成功了你再谢我, 所以现在别谢。 你最好告诉我你丈夫的名字和你知道的关于那些海盗的一切。 ";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - 市民妻子的名字
			forName.lastname = npchar.lastname; //姓氏和妻子的一样
			dialog.text = "他叫" + GetFullName(forName) + "。 船长" + npchar.quest.SeekCap.capName + ", 他在" + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + "名为" + npchar.quest.SeekCap.shipName + "上航行。 "; // belamour gen
			link.l1 = "我知道了。 现在你应该等待, 希望我能成功找到他。 待在教堂里, 等待并祈祷... ";
			link.l1.go = "exit";
			//==> 将任务发布者设置在教堂
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// - —女性任务结果 ---
		case "SCQ_womanResult":
			dialog.text = "哦, 船长, 见到你真高兴! 现在告诉我, 关于我的任务你有什么要告诉我? ";
			link.l1 = "嗯, 提醒我, " + GetAddress_FormToNPC(NPChar) + ", 你说的是什么任务? ";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "啊, 船长, 我收到我丈夫的信了! 他写道你找到了他。 ";
					link.l1 = "是的, 没错, " + GetAddress_FormToNPC(NPChar) + "。 你丈夫" + npchar.quest.SeekCap.capName + "很好, 很健康, 只是太忙了... ";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "你想说什么, 船长? 你按我要求的做了吗? " + npchar.quest.SeekCap.capName + "船长死了吗? ";
					link.l1 = "是的, 他死了, " + GetAddress_FormToNPC(NPChar) + "。 我告诉了他是谁让他死的。 他生命中听到的最后一个名字就是你的。 ";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "你救了我丈夫! 求你告诉我这是真的! ";
					link.l1 = "是真的。 他现在在我船上。 如果" + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + "真的是你丈夫... 你可以见他。 ";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "你真的忘了你答应过要找我丈夫吗? 他叫" + npchar.quest.SeekCap.capName + "! ";
					link.l1 = "哦, 是的, 当然... 没忘。 ";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "我不明白! 你忘了你必须杀了我那个叫" + npchar.quest.SeekCap.capName + "的冒犯者吗? ! ";
					link.l1 = "哦, 拜托, 当然没忘。 你的命令正在执行, 请等待... ";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "天啊, 船长, 你忘了你答应过要救我丈夫吗? ";
					link.l1 = "没忘。 你还记得...'等待并祈祷!'。 等着吧, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + "。 ";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "哦, 上帝, 我太感激了! 是的, 拿着你的" + FindRussianMoneyString(sti(npchar.quest.money)) + "。 再次感谢! ";
			link.l1 = "嗯, 不客气... ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "太好了! 那么, 拿着你的" + FindRussianMoneyString(sti(npchar.quest.money)) + "和珠宝。 再见... ";
			link.l1 = "再见。 ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "当然是他! 哦, 上帝, 船长, 我太感激了。 拿着你的" + FindRussianMoneyString(sti(npchar.quest.money)) + "。 我这辈子每天都会为你祈祷! ";
			link.l1 = "听起来不错... ";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除市民任务发布者死亡中断
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= 被搜索的奴隶贸易船长 ===========
		case "CitizCap": //陆上相遇
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "向我的同行问好。 想要什么" + GetSexPhrase(", 伙计",", 姑娘") + "? ";
					link.l1 = "你叫" + GetFullName(npchar) + ", 对吗? ";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "是的, 你说对了! ";
			link.l1 = "你倒霉了。 我告诉你一个名字, 你最好记住。 " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "。 记得他吗? ";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "嗯, 我记得... ";
			link.l1 = "现在听着, 他对你很生气, 伙计。 是时候为把一个自由人卖为奴隶付出代价了。 ";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "付出代价? ! 你他妈在说什么? ";
			link.l1 = "我的意思是我要在这里杀了你。 ";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "想想看, 你在为谁工作? ! 那个人很可怜, 他的位置应该在甘蔗种植园! ";
			link.l1 = "嗯, 这不关你的事。 现在你必须为你所做的事负责! ";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "哈! 我只会用我通常的方式回应! ";
			link.l1 = "来吧... ";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //甲板相遇
			dialog.text = "你想要什么? ";
			link.l1 = "我想问你, 你载乘客吗? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "这和你有什么关系? ";
			link.l1 = "只是问问。 ";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "只是问问... 听着, 你最好趁我还给你机会的时候离开这里。 我不喜欢你! ";
			link.l1 = "好的好的, 冷静点。 我这就走... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "我们已经谈过了, 别试探我! ";
			link.l1 = "我不会的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= 绑架他人妻子的被搜索船长 ===========
		case "RapeWifeCap":  //陆上相遇
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "问候你, 同行! 你想要什么? ";
			link.l1 = "我想知道, 你是不是从" + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + "带走了一个叫" + GetFullName(sld) + "的女人? ";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "呵, 你说对了, 她在我船舱里! 辣妹, 腿很棒... 你为什么问这个? ";
			link.l1 = "伙计, 这个女人已经结婚了。 你这样做不对。 ";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "那又怎样? 我喜欢她, 就这样。 我不会让某个衣衫褴褛的白痴因为是她丈夫就来干涉我们的关系! ";
			link.l1 = "让我告诉你, 兄弟会不赞成这种事, 如果某些人听说了你做的事, 你会被标记。 ";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "你打算开始说教我吗? ";
			link.l1 = "冷静点, 我只是好奇... 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "我们已经谈过那个女人了。 我不想再讨论这件事! ";
			link.l1 = "随便... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //甲板相遇
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "很高兴在我的甲板上迎接同行! 你想要什么? ";
			link.l1 = "我想知道你是否绑架了来自" + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + "名叫" + GetFullName(sld) + "的女人? ";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "呵, 你说对了, 她在我船舱里! 辣妹, 腿很棒... 你为什么问这个? ";
			link.l1 = "伙计, 这个女人已经结婚了。 你这样做不对。 ";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "那又怎样? 我喜欢她, 就这样。 我不会让某个衣衫褴褛的家伙因为是她丈夫就来干涉我们的关系! ";
			link.l1 = "让我告诉你, 兄弟会不赞成这种事, 如果某些人听说了你做的事, 你会被标记。 ";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "你打算开始说教我吗? ";
			link.l1 = "冷静点, 我只是好奇... 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //登船
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "你想干什么, 人渣? ! ";
			link.l1 = "我是为你从她丈夫那里偷来的女人来的。 还记得" + XI_ConvertString("Colony"+npchar.quest.cribCity) + "吗? 她叫" + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + "。 ";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "该死! 你再也见不到她了, 就像你再也见不到自己的耳朵一样! ";
			link.l1 = "蠢货。 我能在镜子里看到它们。 而我要割下你的! ";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // 重要方法
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //任务标志给NPC
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//NPC的国家
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //NPC的模型
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //NPC的来源城市
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //NPC的姓名
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= 被绑架的妻子 ===========
		case "manRapeWife_Board":
			dialog.text = "你是谁? ";
			link.l1 = "你好。 我是受你丈夫之托来接你。 现在你自由了, 我可以带你去见他。 ";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "这是梦吗? ! 是真的吗? ! ";
			link.l1 = "是真的, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "感谢上帝! 我准备好了, 我们离开这里吧! ";
			link.l1 = "当然, " + GetAddress_FormToNPC(NPChar) + ", 准备好安全回到你丈夫身边。 ";
			link.l1.go = "exit";
			//将妻子从船舱移除
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //将任务标志补全为"已完成"
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= 被寻找的同乡贸易船长 ===========
		case "FriendCap": //陆上相遇
			dialog.text = "你好! 很高兴在陆地上见到同行... ";
			link.l1 = TimeGreeting() + ", 我有点事找你。 ";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "我在听。 ";
			link.l1 = "你的一个同乡在找你。 你们一起航行从旧大陆来到这里。 " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ", 记得吗? ";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "哈, 当然记得! 他现在住在哪里? ";
			link.l1 = "在" + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = "谢谢你! 你知道吗, 我还以为你是海盗! ";
			link.l1 = "我是, 也不是。 但不管怎样, 我今天心情好, 所以你没什么好担心的。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //移除设置的出海计时器
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除船长死亡中断
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //将任务标志补全为"已完成"
			//从船长数据库中删除记录
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "有什么问题吗? 抱歉, 我有点紧张... ";
			link.l1 = "没事, 伙计。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //甲板相遇
			dialog.text = TimeGreeting() + "。 你想从我这里得到什么? 我只是个普通商人, 而且... ";
			link.l1 = "我知道, 伙计。 别这么担心, 据说这对健康不好。 我有点事找你。 ";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "什么事? ";
			link.l1 = "你的一个朋友在找你。 他叫" + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "。 你认识他吗? ";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "哦, 终于等到了! 太好了... 很抱歉刚才的无礼问候, 但我以为你是海盗。 ";
			link.l1 = "我是, 也不是。 但不管怎样, 我今天心情好, 所以你没什么好担心的。 我受人之托给你带个口信, 任务完成了。 你的同乡住在" + XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc") + "。 "; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "真的吗! 你是个正直的人。 谢谢你! ";
			link.l1 = "不客气。 再见, 保重, 伙计。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //到达指定点后消失
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //将任务标志补全为"已完成"
			//从船长数据库中删除记录
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= 被寻找的商人丈夫 ===========
		case "HasbandCap": //陆上相遇
			dialog.text = "你好。 想要什么? ";
			link.l1 = "你叫" + GetFullName(npchar) + ", 对吗? ";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "是的, 是我。 ";
			link.l1 = "这可能听起来很愚蠢, 但你妻子让我告诉你她很担心你。 ";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "哈! 我知道了... 其实, 我太忙了, 有很多赚钱的机会, 我不能因为妻子太担心就失去可能的收入。 ";
			link.l1 = "但你至少可以给她写封信, 告诉她你没事。 ";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "是的, 你说得对。 我马上给她写信! 谢谢你参与我们的家庭事务! ";
			link.l1 = "不客气, 伙计。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //移除设置的出海计时器
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除船长死亡中断
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //将任务标志补全为"已完成"
			//从船长数据库中删除记录
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //甲板相遇
			dialog.text = "日安。 我能为你做什么? ";
			link.l1 = "你叫" + GetFullName(npchar) + ", 对吗? ";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "是的, 是我。 ";
			link.l1 = "这可能听起来很愚蠢, 但你妻子让我告诉你她很担心你。 ";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "呵, 该死! 我还以为是著名的赏金猎人来找我, 他叫独眼神史蒂夫。 还好我错了\n你看, 我工作太忙了, 没时间顾及她。 一直有赚钱的机会, 我不能因为妻子的担心就拒绝。 ";			
			link.l1 = "你说得对, 当然。 但你至少可以给她写封信, 告诉她你没事。 ";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "是的, 你说得对。 我到第一个港口就写... 谢谢你参与我们的家庭事务! ";
			link.l1 = "不客气, 伙计。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //到达指定点后消失
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //将任务标志补全为"已完成"
			//从船长数据库中删除记录
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "谢谢你, 船长... ";
			link.l1 = "不客气。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= 被寻找的欺骗船长 ===========
		case "RevengeCap": //陆上相遇
			dialog.text = "很高兴在这个镇上见到你, 船长。 你需要我做什么吗? ";
			link.l1 = "" + GetSexPhrase("你知道吗, 船长... 呵, 我甚至不知道怎么说! ","是的, 我有。 ") + "";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = "" + GetSexPhrase("有话直说。 ","有趣, 是什么事? ") + "";
			link.l1 = "我有个问题问你。 你认识一个叫" + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "的女人吗? ";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "呵, 认识。 认识她算我倒霉。 一个愚蠢的女孩, 我告诉你... ";
			link.l1 = "嗯... 是的, 这个愚蠢的女孩让我来杀你。 就是这样... .";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "胡说八道。 ";
			link.l1 = "" + GetSexPhrase("我同意。 抱歉, 但有人悬赏你的脑袋","不是胡说。 确实有悬赏") + "。 而我要拿到它。 ";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "呵呵! ... 你在开玩笑吗, 船长? ";
			link.l1 = "" + GetSexPhrase("不, 朋友。 ","连想都没想过! ") + "";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = "" + GetSexPhrase("你不是我朋友, 白痴! 你甚至不能称自己为船长。 你是这个愚蠢泼妇的玩具! ","该死! 一个泼妇雇了另一个! 这世界到底怎么了? ") + "! ";
			link.l1 = "" + GetSexPhrase("注意你的嘴, 混蛋。 ","你利用了她, 所以不要惊讶她决定报复。 ") + "";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = "" + GetSexPhrase("我戳到痛处了? ","女人团结? ! ") + "";
			link.l1 = "我们结束这个吧! ";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //任务标志用于记录杀人中断
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "我已经和你谈过了。 滚吧, 蠢货! ";
			link.l1 = "蠢货? ! 好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //甲板相遇
			dialog.text = "很高兴在船上见到你, 船长。 你想要什么? ";
			link.l1 = "我有个问题问你。 你认识一个叫" + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "的女人吗? ";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "呵, 认识。 认识她算我倒霉。 一个愚蠢的女孩, 我告诉你... ";
			link.l1 = "是的, 这个愚蠢的女孩让我来杀你。 ";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "船长, 别让我笑。 如果你没什么正经事, 那我就告辞了。 ";
			link.l1 = "那么, 再见。 但考虑一下我告诉你的话。 ";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "当然, 船长, 还能怎样? ! ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //任务标志用于记录杀人中断
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "我不想再谈这件事了, 船长。 这太荒谬了。 ";
			link.l1 = "随你怎么说... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //登船
			dialog.text = "这里到底怎么了? ! 你为什么攻击我的船? ";
			link.l1 = "受一位名叫" + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "的女士之托。 你认识她吗? ";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "该死的! 真不敢相信... ";
			link.l1 = "你必须相信! 你不了解女人吗, 伙计? 她们会咬人。 ";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "好吧, 我不会就这样死的。 谢谢你的聊天, 现在我恢复了一些力气。 ";
			link.l1 = "那也帮不了你。 ";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> 更改原始船长的任务标志
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // 重要方法
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= 从海盗囚禁中解救丈夫 =========
		case "PiratesCap_inDeck": //甲板相遇
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "很高兴在船上见到你。 我能帮你吗? ";
			link.l1 = "你可以。 我在找一个叫" + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + "的人。 ";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "这个人是我的囚犯, 我打算勒索赎金。 ";
			link.l1 = "我想带走他。 ";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "很遗憾, 这不可能。 如果没别的事, 我请你离开我的船。 ";
			link.l1 = "好吧, 船长, 如你所愿。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "我们已经谈过我的囚犯了。 没什么变化。 ";
			link.l1 = "我知道了... ";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //陆上相遇
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "很高兴见到你。 我能帮你吗? ";
			link.l1 = "你可以。 我在找一个叫" + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + "的人。 ";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "这个人是我的囚犯, 我打算勒索赎金。 ";
			link.l1 = "我想带走他。 ";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "抱歉, 这不可能。 ";
			link.l1 = "太遗憾了... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //登船
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "该死的! 怎么回事? ! ";
			link.l1 = "我需要你那个叫" + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + "的囚犯。 ";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "哈! 没门, 除非我死! ";
			link.l1 = "既然你这么说了... ";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // 重要方法
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //任务标志给NPC
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//NPC的国家
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //NPC的模型
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //NPC的来源城市
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //NPC的姓名
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= 被囚禁的丈夫 ===========
		case "womanPirates_Board":
			dialog.text = "你是谁? ";
			link.l1 = "我是" +GetFullName(pchar)+ "船长。 别担心, 我是来接你去见你妻子的。 ";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "该死, 我一定是在做梦! ";
			link.l1 = "我向你保证不是... 好了, 现在一切都结束了, 我们离开这里。 ";
			link.l1.go = "exit";
			//将丈夫从船舱移除
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //将任务标志补全为"已完成"
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("我累坏了, 帮帮我。 ", "我再也没有力气这样生活了! "), RandPhraseSimple("这工作要把我们累死了。 ", "该死的守卫把我背上打得没一块好皮! "));				
				link.l1 = RandPhraseSimple("真遗憾。 ", "是的, 生活就是个婊子。 ");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11。 && Jason 10.02.12 系列迷你任务"荣誉之事" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "制服的荣誉"。 
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "哦, 船长, 过来和我坐一起。 我请客! ";
					link.l1 = "我很荣幸。 ";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "荣誉的奴隶"。 
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "你好, 船长。 你是船长, 对吗? 也许甚至是海军船长? \n是的, 你一定很会用剑, 不像我那没用的儿子, 他明天就要死了... 因为这个好色的混蛋看上了我儿子喜欢的女人! ";
						link.l1 = "是的, 我是船长, 我的剑已经救了我很多次, 但你那令人沮丧的演讲剩下的部分呢? 愿意解释一下吗? ";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "美女与海盗"。 
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "你好, 船长。 请问, 你不会是海盗吧? 哦, 当然不是! 你不是。 海盗都长得难看, 行为像动物, 还有那股臭味... ";
						link.l1 = "你对海盗有怨恨吗? ";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "傲慢的蠢货"。 
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: 这是什么奇怪的条件? 像是 - 首都? 除了哈瓦那, 任务在其他城市都不会触发 - 其他城市本来就不合适。 我去掉。 没必要用一个城市限制。 
							dialog.text = "嘿, 你! 是的, 就是你, 告诉我, 你的礼貌在哪里? 你到底为什么站在这里打扰我? 不, 看看他, 真是个蠢货! 我在跟你说话! 让开! 这里外人太多了! ";
							link.l1 = "冷静点, 我不是故意打扰你。 请原谅。 ";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "注意你的舌头, 否则我就割下来, 先生。 ";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "狼与羊"。 
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "你好, 船长。 我有事要拜托你。 如果你是个有荣誉的人, 就不会袖手旁观。 \n那么, 长话短说: 一个贵族一个月前住在我们酒馆。 结果他是个放荡的混蛋! 更过分的是, 他是个杀人犯! ";
						link.l1 = "据我所知, 谋杀无辜的人会被绞死。 在法庭上, 放荡和混蛋也不会有什么好处。 对吗? ";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "懦弱的剑客"。 
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "船长, 等等, 我求你。 你看起来像个熟练的剑客, 比我强多了。 所以我想请你代替我。 ";
						link.l1 = "有趣。 继续说。 ";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "上帝的审判"。 
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "求你了, 别走开! 等等... 你能帮一个可怜的灵魂吗, 这件事需要像你这样勇敢的军官干预? \n事情是这样的, 我和邻居因为当地的葡萄园发生了争吵, 顺便说一句, 他涉嫌走私。 是的, 是的, 他甚至可能和海盗有交易, 否则他怎么能这么快发财? \n一年前他只有一艘三桅帆船, 现在却想夺走我的葡萄园, 你在听吗? ! 我的葡萄园! ";
						link.l1 = "我为你的葡萄园感到难过。 真的。 再见。 ";
						link.l1.go = "exit";
						link.l2 = "抱歉, 但你不能向当地当局求助吗? ";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "纠缠不休的骑士"。 
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "船长, 船长, 我求你! 保护一个无辜女孩的荣誉! ";
						link.l1 = "我没时间在酒馆里安抚醉汉。 去找指挥官, 他们付钱让他解决这种事。 ";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "你好, 女士。 别这么发抖! 发生了什么事? ";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "错误。 请告知开发人员。 ";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "船长, 我被我们驻军的一名军官以最露骨的方式跟踪。 你可能听到了他散布的关于我的肮脏谣言, 试图让我蒙羞! \n唉, 我没有能保护我清白名声的朋友! 我绝望了! 哦, 上帝, 那就是他! 帮帮我! ";
			link.l1 = "别担心, 我会处理的。 ";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: 我们不需要破烂 - 制作酷战士
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // 多面手战士
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // 我们还有机会。 
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "啊, 你在这儿, 我的女士! 又一个骑士, 我猜? 你打算什么时候安定下来? 也许永远不会... 去妓院工作吧, 那最适合你... ";
			link.l1 = "军官, 闭上你的嘴, 别再喷脏言秽语, 否则我会用我的特殊方式让你闭嘴! ";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "嗯... 你是谁? 啊, 海上的勇士, 小船的勇敢船长, 对吗? 你打算怎么做, 海上... 小家伙? ";
			link.l1 = "这位女士是我的朋友! 我会给你一副手套! ";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "什么? ! 你要因为这个... ";
			link.l1 = "够了! 两小时后我在灯塔附近等你。 别忘了带剑! ";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: 按约定延迟2小时
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "啊, 我都知道了, 先生! 你不知道我有多感激你! 愿上帝保佑你! ";
			link.l1 = "很高兴能帮到你。 祝你好运! ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "啊, 你和他们一样, 离开我! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "或者在妓院 ";
			dialog.text = "哦, " + GetAddress_Form(NPChar) + "... 我不敢奢望, 但也许你的剑这次能保护我的家人? \n正如我所说, 我儿子不是剑客, 但他第二天早上就要去决斗了。 啊, 要不是为了他的女人和该死的荣誉\n但他不能退缩, 现在他注定要失败, 你明白吗? 我绝望了, 他是我唯一的儿子和继承人, 因此我请求你在黎明前杀了那个挑战我儿子的混蛋。 你会在" + sTemp + "酒馆找到那个人 - 像他那样的混蛋在那里消磨时间... 我求你了... ";
			link.l1 = "我既不关心你也不关心你儿子。 让我走! ";
			link.l1.go = "exit";
			link.l2 = "嗯... 就这样? 好吧, 我们走着瞧。 ";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "你真的会帮我儿子吗? 哦, " + GetAddress_Form(NPChar) + "! 我会为你和你的运气祈祷! ";
			link.l1 = "我看没什么坏处... 等我! ";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: 我们不需要破烂 - 制作酷战士
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // 多面手战士
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // 我们还有机会。 
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "你他妈想从我这里得到什么? 我在这里休息, 不想被打扰。 有很多空位和空闲的耳朵, 所以别烦我, 先生! ";
			link.l1 = "不幸的是, 你得休息到更好的时候了。 ";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "什么? ! 你算老几, 敢告诉我该做什么? ! ";
			link.l1 = "你忘了我吗, 嗯? 但我记得你! 我的观点是, 像你这样的恶棍存在于世只是在毒害我们的世界! ";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "啊? ! 水手, 看来你喝多了! 我第一次见你! 但我不会忽视你的行为! 这是你拯救你可怜生命的最后机会! 现在道歉, 你这个臃肿的鲱鱼, 我会忘记你无礼的言辞! ";
			link.l1 = "我只向可敬的人道歉, 不向肮脏的猪道歉! ";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "你他妈说什么? ! 你在自找麻烦吗, 厕所里的虱子? ";
			link.l1 = "我会用你的话堵住你该死的喉咙, 老鼠! 两小时后我在灯塔附近等你, 别忘了带上你腰带上那堆生锈的垃圾! ";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "哈! 我会去的! ";
			link.l1 = "一会儿见! ";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: 按约定延迟2小时
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "哦, 是你! 你还活着, 这意味着... ";
			link.l1 = "是的, 我活着, 你儿子明天早上不需要决斗了... ";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "多好的一天! 我该去告诉妻子这个好消息! \n船长, 命运派你来帮助我。 拿着这些硬币, 接受我们全家的感激! ";
			link.l1 = "谢谢你! ";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("你收到了" + FindRussianDublonString(iTemp) + "");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "滚开, 杀孩子的凶手! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "我? 感谢上帝, 我很好, 但我妹妹就没那么幸运了。 她在一家酒馆服务\n有个私掠船船长经常去那里, 是个非常危险的人。 海盗! 他的船至少航行了一周。 这个人喝酒, 威胁别人, 并承诺如果她不满足他的肮脏愿望, 就杀了所有试图讲道理的人! 最糟糕的是, 我妹妹告诉我, 他吹嘘说如果她不满足他, 就把她偷走, 带到鬼知道哪里去! \n我不知道该怎么办! 当局不关心某个 servant 女孩, 像我这样的普通公民害怕这个私掠船船长。 请帮我们处理他! ";
			link.l1 = "我没时间在酒馆里安抚醉汉。 去找指挥官, 他们付钱让他解决这种事。 ";
			link.l1.go = "exit";
			link.l2 = "嗯, 一个威胁人的私掠船船长? 好吧, 我来处理。 ";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "啊, 谢谢你, 船长! 我相信他会像水手听水手那样听你的! 让他永远离开我妹妹! 我们不富有, 但会为你的麻烦付足够的钱! ";
			link.l1 = "好的, 好的... 我这就去解决你的问题。 等我! ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: 我们不需要破烂 - 制作酷战士
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // 多面手战士
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // 我们还有机会。 
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "那又怎样? 你和那个海盗谈过了吗? 他会离开我们吗? 我妹妹告诉我他离开了酒馆, 没再回来... ";
			link.l1 = "谈过了。 那家伙有点粗鲁, 但我的论点很合理且有说服力。 你妹妹现在没什么好怕的了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "你想要什么? 没看到我在这里休息吗? ";
			link.l1 = "嗯, 嗯... 看哪, 啤酒杯的伟大主人, 女孩的偷猎者, 这个小镇的风暴化身, 对吗? 你在镇外也会这么勇敢吗? 灯塔附近, 两小时后, 决斗? ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "哦-吼-吼! 你在假装英雄吗? 不管怎样, 伙计, 我今天心情好, 所以原谅你。 去给我买几品脱麦芽酒! ";
			link.l1 = "我不是你的伙计。 需要给你这样的白痴重复一遍吗? 你在酒馆里表现得很勇敢, 敢不敢来决斗? ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "你在挑战我? ! 你怎么了? 活腻了, 想找死吗, 杂种? 好吧, 如果你真的想, 我会走到灯塔, 撕开你的内脏, 然后把这个该死的酒馆也毁了! ";
			link.l1 = "光说不练, 剑可不会, 记得带一把! ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "那怎样? 你和那个海盗谈过了吗? 他会离开我们吗? 我妹妹告诉我他离开了酒馆, 没再回来... ";
			link.l1 = "我谈过了。 那家伙有点粗鲁, 但我的论点很合理且有说服力。 你妹妹现在没什么好怕的了。 ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "这... 结束了吗? 我们现在可以自由呼吸了吗? 谢谢你, 船长! 那... 那个恶棍在哪里? ";
			link.l1 = "他... 在他的船上。 他决定尽快离开这个小镇。 ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "你为这个殖民地的公民做了一件大好事! 这是给你帮助的报酬! 虽然不多, 但你会得到我所有朋友的尊重, 相信我, 我朋友很多! ";
			link.l1 = "谢谢! 祝你和你妹妹好运。 希望她能嫁给一个可敬的人。 再见! ";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "哦, 真的吗? 你打算怎么阻止我? ";
			link.l1 = "当然是用我的剑, 这是对付你这样无礼的猪唯一合适的方式。 ";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "太好了! 两小时后我在灯塔附近等你。 ";
			link.l1 = "好! 我一定会到。 ";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // 我们还有机会。 
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: 按约定延迟2小时
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "让开, 懦夫! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "船长, 那个混蛋不简单, 汤姆, 我的老朋友, 在和他的决斗中死了, 被指控作弊! 他是无辜的, 我发誓。 但总督说那场该死的决斗中没有犯罪。 ";
			link.l1 = "嗯... 这都是你朋友的错。 作弊可能会对健康造成不良后果。 ";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "是吗? 过去两周我们镇上已经有四个作弊者了。 他们都想欺骗我们的贵族? 你对此怎么说? 我的观点是这个贵族自己就是个作弊者。 如果你不相信我, 就自己去看看。 ";
			link.l1 = "你是说和他赌博? 不, 我不喜欢赌博。 没门。 ";
			link.l1.go = "exit";
			link.l2 = "我想我会去... 这里面肯定有问题。 ";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "船长, 我和朋友们凑了一笔钱, 要付给揭露那个贵族并为他所有行为复仇的人。 一旦事情完成, 我会在镇上等你给你报酬。 ";
			link.l1 = "如果正如你所说, 我会去做。 ";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: 我们不需要破烂 - 制作酷战士
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // 多面手战士
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // 我们还有机会。 
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "尊敬的先生! 我看您是位贵族, 或许还是个赌徒? 想玩一局吗? ";
			link.l1 = "当然! 我们谈谈赌注吧。 50枚硬币如何? ";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "你大概在开玩笑吧? 你根本没有那么多钱! ";
				link.l1 = "你说得对... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "赌注不重要, 我们是来赌博的, 这才是最有趣的部分。 因为当地的蠢货, 我都快忘了牌是什么样子了。 ";
				link.l1 = "好吧, 开始吧。 ";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "那么, 赌注是50枚硬币。 ";
			link.l1 = "... ";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "等一下, 这是什么? .. 不可能! 先生, 你是个骗子! 把我的硬币还给我! ";
			link.l1 = "你必须有充分的理由指责我, " + GetAddress_FormToNPC(NPChar) + "。 你最好现在就说清楚, 否则就决斗! ";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "啊, 就这样? 好吧, 那就决斗! 今天, 两小时后, 在灯塔附近! ";
			link.l1 = "成交! ";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: 按约定延迟2小时
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "有什么消息吗, 船长? ";
			link.l1 = "你说得对, 我也被指责作弊, 所以我不得不在决斗中解决了那个混蛋。 ";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "看到了吧? 我就知道! 我和朋友们都非常感谢你! 拿着你的报酬吧, 船长。 ";
			link.l1 = "谢谢你。 ";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "我有没有告诉过你, 我来这里是为了申请击剑教练的职位? 没有? 那么, 当地的总督正在为他的侄子找教练, 这对我来说再合适不过了。 我了解这门艺术的基础知识, 但从未实际练习过\n我几乎已经得到了这份工作, 但后来发现当地的商人遇到了麻烦, 一个看起来很危险的无赖在威胁他。 总督命令我处理这件事, 以测试我的专业技能。 ";
			link.l1 = "那就去做吧。 再见。 ";
			link.l1.go = "exit";
			link.l2 = "那么这个恶棍想从商人那里得到什么, 你又为什么需要我? ";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "我以为那个人是雇佣兵, 而你总是可以和雇佣兵达成协议。 旧债或其他什么... 但那个人对继续向商人施压是认真的。 我想请你帮助商人和我, 把他从雇佣兵手中救出来, 并完成总督的命令\n我真的需要这个职位, 我自己无法摆脱那个雇佣兵。 请帮助我, 我会把我存的每一分钱都给你, 否则我将不得不羞愧地离开这座城市! ";
			link.l1 = "好吧, 好吧, 我会帮你...'击剑大师'。 ";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: 我们不需要破烂 - 制作酷战士
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // 多面手战士
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // 我们还有机会。 
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "你想要什么? 没看到我正忙着吗? ! ";
			link.l1 = "打扰某位可敬的商人并制造噪音! ? ";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "呸! 又一个守护者? 每天雇保镖还不如付钱给我。 与追债相比, 我不太喜欢杀人, 所以如果你是这样的英雄, 那就到灯塔来, 我们在决斗中测试一下彼此。 如果你不是, 那就别再惹我。 ";
			link.l1 = "成交! 我会在那里等你。 ";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "看来你比我还胆小... ";
			link.l1 = "是的, 我是。 ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "有什么消息吗, 船长? ";
			link.l1 = "那个雇佣兵死了。 我希望现在这个职位是你的了? ";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "哦, 船长, 感谢你! 拿着你的报酬, 我会向总督报告! ";
			link.l1 = "再见... 大师。 ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("你收到了一个装满杜布隆的箱子");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "再来一杯? ";
			link.l1 = "干杯。 ";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "再来! ";
			link.l1 = "等一下! 你急着去哪里? ";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "别问问题了! 喝吧! ";
			link.l1 = "好吧, 但也许你稍后会告诉我你发生了什么事? ";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "你真的感兴趣吗? 那就趁我还能说话的时候听着! 过几天我就不能说话了, 因为我会死... 是的, 死! 都怪朗姆酒。 太多的朗姆酒和这个军官, 显然是魔鬼派来折磨我的! \n如果我清醒或至少没有那么醉, 我肯定不会和我们驻军乃至整个城市最好的击剑手决斗。 但现在呢? 我完了, 毁了, 我死定了! 我真是个愚蠢的傻瓜... ";
			link.l1 = "是的, 那太愚蠢了。 但你将来可能会表现得更聪明... 当然, 如果你能在决斗中幸存下来的话。 再见。 ";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "酗酒也不是最好的选择, 军官。 我相信这个麻烦有解决的办法。 ";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "什么样的解决办法? 开小差, 失去我的声誉和军官制服? 还是自杀, 以免像猪一样被宰杀? 你有什么建议? ";
			link.l1 = "两者都不是。 我会帮助你, 并尝试在决斗前阻止你的对手伤害你。 我在哪里可以找到他? ";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "你是认真的吗? 你会这么做? ! 哦, 我发誓, 我会让你觉得值得的! \n他可以在城里找到。 他的情妇住在这里, 所有军官都听说过她, 但可惜不知道她的地址... 所以我打赌你也可以在那里找到他。 ";
			link.l1 = "够了。 在这里等我。 我去和这个...'最佳击剑手'谈谈。 ";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "有什么消息给我吗, 先生? 好消息还是... 不太好? ";
			link.l1 = "我还没有消息。 在这里等。 一切都会好的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "有什么消息给我吗, 先生? 好消息还是... 不太好? ";
			link.l1 = "结束了。 你潜在的对手再也不能伤害任何人了... 你现在安全了。 但我希望你能从这次教训中吸取经验, 不再对不认识的人咄咄逼人。 ";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "你不是在开玩笑吧, 对吗? 我.. 我真的很感激, " + GetAddress_Form(NPChar) + "! 拿着, 这是我所有的东西。 这是我的工资, 全拿去吧! \n你说的教训? 是的, 该死的, 你说得对! 这种事再也不会发生了! 我向你保证, 再次感谢你给了我另一次机会! ";
			link.l1 = "那好吧。 再见, 军官... ";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("你收到了一个装有杜布隆的钱包");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "再次感谢你, " + GetAddress_Form(NPChar) + "的帮助! ";
			link.l1 = "不客气... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "嘿, 搞什么鬼? 你在我女人的房间里做什么? 离开这里, 否则我就强行把你拖出去! ";
			link.l1 = "我想去哪就去哪, 而且我不会向你报告这种行为! 强行? 那就试试! ";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "如此无礼! 前所未闻的厚颜无耻! 先生, 你真的错了! 立即离开这所房子, 否则我发誓你会后悔活着! ";
			link.l1 = "光说不练! 你会后悔的, 不是我, " + GetAddress_FormToNPC(NPChar) + "! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "真的吗? 那就小心了! 如果我在这所房子里杀了你, 那就是谋杀。 所以你的死不会损害我的名誉, 有荣誉的人会在灯塔附近解决这种事! \n我向你挑战, " + GetAddress_Form(NPChar) + ", 你这个无礼的人! 你要为你的话负责! 那么, 两小时后决斗? ";
			link.l1 = "当然, " + GetAddress_FormToNPC(NPChar) + "大胆的家伙。 ";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "那你一定要准时到那里。 你还有时间从我们的牧师那里订购安魂曲。 ";
			link.l1 = "为你订购安魂曲? 你连一个比索都不值。 灯塔附近见! ";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: 按约定延迟2小时
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "滚开! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "你是指总督吗? 哈! ‘上帝的审判’是总督对我投诉的回应! 决斗! 你觉得怎么样? 我只是一个安静。 爱好和平的种植园主, 不是强盗或战士\n这将是谋杀, 不是决斗! 而且你无疑比我更擅长这种事情。 因此, 我请求你在即将到来的决斗中代表我。 相信我, 我不会欠债的。 ";
			link.l1 = "决斗是什么时候? ";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "今天午夜前在灯塔附近。 你会帮助我吗? ";
			link.l1 = "好吧, 我会帮助你。 在镇上等我! ";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: 我们不需要破烂 - 制作酷战士
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // 多面手战士
			LAi_SetImmortal(sld, true); // 我们还有机会。 
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "告诉我那里发生了什么? 我们... 对不起, 你赢了吗? ";
			link.l1 = "我相信你会感兴趣的是, 那里有一个埋伏。 也许你的邻居决定通过邀请更多的代表而不是一个来投保, 而且他们都是经验丰富的强盗。 幸运的是, 我是一个经验丰富的击剑手。 ";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "这样的混蛋! 现在, 我想我们的总督不会有任何理由拒绝我逮捕那个恶棍的请求! 谢谢你! 拿着你的报酬, 我得去官邸了。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("你收到了几袋杜布隆");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// 决斗前对话 -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "没有bug玩起来很有趣, 因为那些婊子很难找。 ";
			link.l1 = "放松, 我会通知开发人员。 ";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "啊, 你来了。 这些是我的朋友和助手。 我们开始吧? ";
					link.l1 = "我听候你的吩咐! ";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "所有人都到齐了。 你准备好了吗? ";
					link.l1 = "是的, 我们可以开始了! ";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "终于! 我还以为我得走这么长的路却一无所获... 让我们快点结束, 我在酒馆里留了一杯朗姆酒和一个辣妹! ";
					link.l1 = "我相信你再也不需要它们了! ";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "Jackanapes":
					dialog.text = "所以你决定来了? 终于! 那我们开始吧! ";
					link.l1 = "别那么着急, 你可能会倒在刀刃上。 ";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "这些是我的助手, 先生。 现在准备去死吧! ";
					link.l1 = "你先请。 ";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "CowardFencer":
					dialog.text = "我们到了。 准备好你的剑, 先生! ";
					link.l1 = "乐意之至, 愿强者获胜! ";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "CoatHonor":
					dialog.text = "太好了, 大家都到了... 开始吧, 先生! ";
					link.l1 = "让我们起舞吧! ";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "GodJudgement":
					dialog.text = "你是谁? 你看起来不像普通公民, 伙计... ";
					link.l1 = "那又怎样? 我和你有场决斗安排好了? ! ";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1";
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "哈! 决斗! 看来你是我们的客户。 伙计们, 我们捅他一刀, 然后去拿我们的报酬。 干掉他! ";
			link.l1 = "埋伏? 真可悲, 你们需要比这更多的人才能打倒我... ";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("助手将参战");
			}
			// 在"上帝的审判"任务中总是攻击。 
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("全面屠杀");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// < —决斗前对话。 
		
		// 决斗后对话 -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "你不认为我们会让你杀了我们的朋友然后就这样离开吧? 拿起武器! ";
				link.l1 = "我早该料到这种可怜的混蛋会这样! ";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "船长, 荣誉已恢复, 你赢了。 但请允许我给你一个好建议 - 离开这座城市, 一段时间内不要出现... ";
				link.l1 = "那有什么问题??";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "这都是出于荣誉, 现在让我们去带走我们的朋友。 ";
				link.l1 = "当然, 我不会阻止你... ";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "问题是你杀了我们指挥官的一名 orderly。 他是个坏人, 没人会为他的死感到遗憾... 但指挥官真的很喜欢他, 他永远不会原谅你杀了他的朋友。 ";
			link.l1 = "谢谢你的建议, 我一定会留意的。 再见。 ";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// < —决斗后对话。 
		//=====================================================================================================================================
		// < —"荣誉之事"系列迷你任务。 
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//创建船长
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //选择任务时分析敌船
	sld.DontRansackCaptain = true; //不投降
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//加入船长的海上团队
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
//将数据写入市民和船长的结构体
	npchar.quest.SeekCap.capId = sld.id //被寻找船长的Id
	npchar.quest.SeekCap.capName = GetFullName(sld); //被寻找船长的姓名
	npchar.quest.SeekCap.shipName = sld.Ship.name; //被劫船只的名称
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //被劫船只的类型名称
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //奖励金额
	sld.quest = "InMap"; //被寻找船长的个人标志
	sld.quest.SeekCap = npchar.quest.SeekCap; //将任务标志写入船长数据
	sld.quest.nation = iNation; //记录船长的基础国家
	sld.city = SelectAnyColony(npchar.city); //确定船长出现的殖民地
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //确定船长的目的地殖民地
	//Log_TestInfo("被寻找船长 " + sld.id + " 从: " + sld.city + " 出发并前往: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //任务发布者所在城市
	npchar.quest.Qcity = sld.city;
	//==> 地图设置
	sld.mapEnc.type = "trade";
	//地图上船只类型选择
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //днeй доeхать даeм с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//船长死亡中断
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//任务发布者死亡中断
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//将船长Id写入NPC船长数据库
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //任务标识符
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //记录任务发布者Id以便必要时清除
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //任务簿标题
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //任务簿中的任务名称
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "有个混蛋利用我妹妹的天真诱惑了她, 得逞后就抛弃了她。 我不能让他逍遥法外, 于是向他挑战。 他吓得驾船逃走了" break;
		case 1: sText = "有个无耻之徒跟我赌博输了一大笔钱, 然后驾船跑了" break;
		case 2: sText = "有个无赖向我借钱, 趁我不在家时用假币还给我的仆人。 现在他躲在船上某处" break;
		case 3: sText = "有个恶棍试图在总督面前败坏我的名声, 但谎言被揭穿后, 这个混蛋驾船逃跑了" break;
		case 4: sText = "是我犯了错, 雇了个流氓当会计。 他挪用了大笔款项, 买了艘船跑了" break;
		case 5: sText = "我以前的守卫从妻子的闺房偷了一个装满珠宝的盒子跑了。 现在我知道他哪来的钱买船了" break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "有个混蛋利用我妹妹的天真诱惑了她, 得逞后就抛弃了她。 我不能让他逍遥法外, 于是向他挑战。 但他受聘成为船长后就扬帆逃走了";
			npchar.quest.text1 = "玷污了一位女性后懦弱地逃跑了";
		break;
		case 1:
			npchar.quest.text = "有个无耻之徒跟我赌博输了一大笔钱却不还, 我听说他受聘成为炮手后跑了";
			npchar.quest.text1 = "赌博输光了钱却不想还债";
		break;
		case 2:
			npchar.quest.text = "有个无赖向我借钱, 趁我不在家时用假币还给我的仆人。 现在他在某艘船上当军需官躲着我";
			npchar.quest.text1 = "伪造货币的罪犯";
		break;
		case 3:
			npchar.quest.text = "有个恶棍试图在总督面前败坏我的名声, 但谎言被揭穿了。 幸运的是这个混蛋受聘成为某艘船的医生后跑了";
			npchar.quest.text1 = "造谣中伤。 企图败坏良民声誉的阴谋家";
		break;
		case 4:
			npchar.quest.text = "是我犯了错, 雇了个流氓当会计。 他挪用了大笔款项, 现在在某艘船上当军需官躲着我";
			npchar.quest.text1 = "被指控挪用和侵吞财产";
		break;
		case 5:
			npchar.quest.text = "我以前的守卫从妻子的闺房偷了一个装满珠宝的盒子跑了。 他受聘成为某艘船的登船队军官";
			npchar.quest.text1 = "一个普通的小偷, 他该进监狱。 他偷了自己雇主的珠宝";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "我的老朋友, 在旧世界时是我亲密的朋友";
			npchar.quest.text1 = "他是你的老朋友";
		break;
		case 1:
			npchar.quest.text = "一个基本上像我父亲一样的人";
			npchar.quest.text1 = "你对他就像父亲一样";
		break;
		case 2:
			npchar.quest.text = "我的异父兄弟, 年轻时就离开了旧世界";
			npchar.quest.text1 = "你是他的异父兄弟";
		break;
		case 3:
			npchar.quest.text = "在旧世界时真正帮助过我的人";
			npchar.quest.text1 = "你曾大力帮助过他";
		break;
		case 4:
			npchar.quest.text = "我妹妹的丈夫, 在旧世界时是我的朋友";
			npchar.quest.text1 = "你是他妹妹的丈夫";
		break;
		case 5:
			npchar.quest.text = "我的朋友, 旧世界时的战友";
			npchar.quest.text1 = "你们曾是战友";
		break;
	}
}