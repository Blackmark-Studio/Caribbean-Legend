#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // 调用按城市的对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 调用按城市的对话 <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // 城市 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("首次酒馆访问 " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("镇上拉响了警报, 所有人都在找你。 如果我是你, 就不会待在这里。 ", "所有城卫兵都在城里搜捕你。 我不是傻瓜, 不会和你说话! ", "快跑, 伙计/姑娘, 在士兵把你剁成碎肉之前... "),
					LinkRandPhrase("你想要什么, 恶棍/讨厌鬼? ! 城卫兵已经盯上你了, 你跑不远的, 肮脏的海盗! ", "杀人犯, 马上离开我的地方! 卫兵! ", "我不怕你, 恶棍/老鼠! 很快你就会在我们的堡垒里被绞死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("呵, 警报对我来说从来不是问题... ", "他们永远抓不到我。 "),
					RandPhraseSimple("闭上你的嘴, " + GetWorkTypeOfMan(npchar, "") + ", 不然我就把你的舌头扯下来! ", "呵, " + GetWorkTypeOfMan(npchar, "") + ", 所有人都在抓海盗! 我告诉你, 伙计: 安静坐着, 你就不会死... "));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("是你啊, 混蛋! 你以为我们会在这里给你倒朗姆酒吗? 当然不会! 伙计们! 拿起武器! 杀了这个恶棍! ", "想喝酒吗, 海盗? 哈! 不! 现在我们让你看看厉害! 伙计们, 拔出刀刃! ");
				link.l1 = RandPhraseSimple("嗯? 什么? ", "住手! ");
				link.l1.go = "fight";
				bDisableFastReload = true;//关闭传送
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, 加斯科涅的枷锁
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "先生, 我在找工作。 你有什么活计吗? ";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "我完成了你的任务。 装朗姆酒的长艇已经送到勒弗朗索瓦湾, 并交给了你的人。 ";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				FreeSitLocator("FortFrance_tavern", "sit7");
				dialog.text = "你想要什么吗, 先生? ";
				Link.l1 = "你好, 酒保, 我需要为我的船雇佣船员。 你能帮我吗? ";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "又见面了。 这次是什么事, 先生? ";
				Link.l1 = ""+npchar.name+", 我知道我在打扰你, 但还有一个问题。 我需要一名领航员 - 你知道我在哪里可以找到吗? ";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "你想要什么, 先生? ";
				Link.l1 = "我希望你能回答几个问题。 ";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "我想租个房间。 ";
					link.l2.go = "room";
				}
				break;
			}			
			//加斯科涅的枷锁
			// Addon 2016-1 Jason 海盗线
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "很高兴见到你, 先生! 有什么可以为你效劳的? 朗姆酒。 白兰地。 苏格兰威士忌? ";
				Link.l1 = "我想要一瓶你最好的法国葡萄酒和一把房间钥匙。 ";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "你已经付过钱了, 先生, 你的房间在楼上。 ";
				Link.l1 = "谢谢。 ";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - 任务"旧罪的长影" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "我能为你效劳吗, 船长? 在发生那件事后, 你可能想喝一杯。 ";
				Link.l1 = "那可以等等。 我其实想谈谈发生的事。 ";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== 任务"旧罪的长影" - Sinistra
			
			//--> 依法贸易
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "抱歉, " + GetAddress_Form(NPChar) + ", 但今天我不能给你提供一滴烈酒。 ";
				Link.l1 = "什么? 什么样的酒馆连一滴朗姆酒都舍不得? 我是不是错过了什么盛大庆典, 把你的库存都喝光了? ";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<—— 依法贸易

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("欢迎来到我简陋的酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "', 先生。 很高兴见到你。 ","为你效劳, 先生! 在我们的酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "', 我们总是很高兴欢迎新访客。 ","第一次来这里吗, 先生? 不要犹豫, 在'" + XI_ConvertString(NPChar.City + "TavernName") + "'你总是有宾至如归的感觉! "), LinkRandPhrase("进来吧, 船长先生。 我不认识你, 所以这一定是你第一次来'" + XI_ConvertString(NPChar.City + "TavernName") + "'。 ","以前没见过你, 先生。 让我们认识一下: 我是" + GetFullName(npchar) + ",'" + XI_ConvertString(NPChar.City + "TavernName") + "'的老板。 ","很高兴欢迎我们的新客人, 船长先生! 在我的酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "', 第一杯总是免费的! 我是这个地方的主人, " + GetFullName(npchar) + ", 欢迎你。 "), LinkRandPhrase("船长先生! 欢迎来到酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "'! ","哦, 一位多么耀眼的贵族来到了我们的酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "'! 先生, 这是你第一次来吗? ","下午好, 先生! 我是" + GetFullName(npchar) + ",'" + XI_ConvertString(NPChar.City + "TavernName") + "'的卑微主人, 我们很高兴欢迎你! "),LinkRandPhrase("你好, 船长先生。 我是酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "'的老板。 第一次和我们一起住吗? ","下午好, 先生。 欢迎来到酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "'。 ","很高兴见到你, 船长先生! 我们自己的酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "'向你致意! 朗姆酒。 葡萄酒, 或者我可以诱惑你, 我们有一种淘气的新荷兰烈酒叫杜松子酒? "));
				Link.l1 = LinkRandPhrase("你这里地方很舒适... 请允许我介绍自己 - " +GetFullName(pchar)+ ", 很高兴认识你。 ","" +GetFullName(pchar)+ ", 很高兴认识你。 那么, 你能给我提供什么? ","我叫" +GetFullName(pchar)+ ", 我是这个港口的新人。 告诉我, 这家酒馆最出名的是什么? ");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "啊哈, 伦巴! 是刚旅行回来, 还是要开始新的旅程? ";
					link.l1 = "你好, " + npchar.name+ "。 只是决定顺便来看看。 ";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// 神父的任务生成器。 任务#1。 Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "那么, 船长, 你给我带来" + FindRussianMoneyString(iTemp) + "了吗。 ";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "是的, 我带来了。 给你... ";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "不, 我还没有... ";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "你想要什么, 我善良的先生/女士? ";
						link.l1 = "给我那边桌子上的伙伴来瓶朗姆酒。 ";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <—— 神父的任务生成器。 任务#1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("哦, 尊贵的客人! 嘿, 你 - 挪过去, 给英勇的船长腾地方! 快点, 不然我把你扔出去, 哈哈! ","仁慈的上帝啊! 这不是" +GetFullName(pchar)+ "吗! 我刚进了一批最好的葡萄酒, 请进! ","哦, " + GetAddress_Form(NPChar) + ", 你有麻烦吗? 请允许我请你? 这瓶酒我请客。 相信我, 这是周围最好的酒... "),LinkRandPhrase("哦, 是" +GetFullName(pchar)+ "船长! 嘿, 你! 对好船长放尊重点! 这不是谷仓! 抱歉, 船长, 他们的母亲显然没教过他们礼貌。 ","好吧好吧, " + GetAddress_Form(NPChar) + " " +GetFullName(pchar)+ "! 我们要熬夜了, 哈哈! 姑娘们最好穿上你们最好的裙子! ","下午好, " +GetFullName(pchar)+ ", 很高兴见到你! 先生, 请允许我提个请求。 我刚买了新桌子, 所以今晚请不要打架。 "),LinkRandPhrase("你好, 船长。 请自便, 但记住即使Sharp船长本人在我的店里也会注意举止。 ","哦吼吼! 看看谁来了? 是" +GetFullName(pchar)+ "本人! 你不在的时候我们正开始觉得无聊呢! 你给伙计们讲个冒险故事, 我开一桶新朗姆酒怎么样, 船长? ","哦吼吼! 是" +GetFullName(pchar)+ "本人! 我希望你不会再用你伟大冒险的故事把我的顾客骗到公海上去吧? ")),LinkRandPhrase(LinkRandPhrase("" +GetFullName(pchar)+ "! 这个老水手总是很高兴在他的店里见到你! 先生, 请坐, 姑娘们会照顾你的! ","请船长自便! 总是很高兴见到我最喜欢的客人。 你想喝什么? ","很高兴再次见到你, " +GetFullName(pchar)+ "! 你想要一张单独的桌子吗? 还是想坐在吧台? "),LinkRandPhrase("下午好, 船长。 天气有点凉, 允许我给你提供一些我刚做的极好的热葡萄酒, 我请客! ","你好, " +GetFullName(pchar)+ "船长! 很高兴你又来拜访了。 你想要什么? ","很高兴有你, " + GetAddress_Form(NPChar) + " " +GetFullName(pchar)+ "! 很高兴你光顾我简陋的店! 我们尽一切努力让你满意。 "),LinkRandPhrase("船长! 欢迎, 欢迎! 我有一些适合路易国王的优质安茹葡萄酒, 专门为你保存! ","" +GetFullName(pchar)+ "! 我很高兴你来了。 要我把这些海鼠都赶走, 还是你希望他们留下? 相信我, 我很乐意为你清空整个酒馆! ","我的上帝, 这是" +GetFullName(pchar)+ "船长! 嘿, 美女们 - 把最好的桌布拿到船长的桌子上! ")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("哦, 我知道我在这里被记住了... 停, 伙计, 给我倒杯酒, 我四处看看... ","冷静点, 伙计, 今天我心情好。 我们先来点朗姆酒, 好吗? ... "),RandPhraseSimple("哦... 你不太高兴我来这里? 我希望我听错了, 哈! ","啊哈。 我希望你的酒比你的问候好? 否则我会生气的, 你知道... ")),RandPhraseSimple(RandPhraseSimple("总是很高兴拜访你, 伙计。 你有什么能让老水手暖和起来的? ","啊哈, 伙计, 你的店一天比一天好! 来这里总是一种享受... "),RandPhraseSimple("你没忘记一个老流浪汉吧? 我很荣幸, 伙计。 ","很高兴再次见到老朋友... 你还有一些朗姆酒吗? ")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("我在听, 船长。 ","我的酒馆'" + XI_ConvertString(NPChar.City + "TavernName") + "'为你服务, 船长! ","全神贯注, 船长! 你今天想要什么? ");
				Link.l1 = "岛上有愿意在海上碰碰运气的小伙子吗? ";
				Link.l1.go = "crew hire";
				Link.l2 = "我希望你能回答几个问题。 ";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "我想谈谈财务方面的事。 ";
					link.l21.go = "LoanForAll";//(转发到贷款生成器)
				}
				
				// 神父的任务生成器。 任务#2。 Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("你能告诉我最近教堂抢劫案的事吗? ", "你对最近教堂的抢劫案知道些什么? ", "你听说过最近教堂的抢劫案吗? ");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <—— 神父的任务生成器。 任务#2.
				
				//Jason --> 生成器 不幸的小偷
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "人们说你几乎知道这个殖民地的一切。 我想买" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人告诉我它在你的镇上被出售。 嗯, 有人在街头市场卖它。 你能告诉我什么吗? ";
					link.l16.go = "Device_Tavern";
				}
				// <—— 生成器 不幸的小偷
			
				//Jason --> 生成器 阳光下的地方
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "在找一个叫" + pchar.GenQuest.Sunplace.Trader.Enemyname + "的敲诈者。 我在哪里可以找到他? ";
					link.l17.go = "Sunplace_Tavern";
				}
				// <—— 生成器 阳光下的地方
			
				// --> 荷兰赌局
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "你好, " + npchar.name+ "。 我需要找到雅各布.范.伯格 - 他在哪里? 我在你的酒馆里没看到他... ";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "你好, " + npchar.name+ "。 我在找一个叫费尔南多.罗德里格斯的绅士。 他出现在你的镇上了吗? ";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <—— 荷兰赌局
			
				//Jason --> 水上飞机比赛
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "我来领取我的奖金, 奖金由你保管。 " + npchar.name+ "。 ";
					link.l19.go = "Race_Advantage";
				}
				// <—— 水上飞机比赛
			
				//Jason --> 劫持乘客
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "我想知道在哪里可以找到一个叫" + pchar.GenQuest.Marginpassenger.q2Name + "的人? 他住在你的镇上。 ";
					link.l20.go = "Marginpassenger";
				}
				// <—— 劫持乘客
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("你有空闲的房间吗, 伙计? ", "你有空闲的房间吗, 我想在这里待一段时间。 ");
					link.l3.go = "room";
				}
				Link.l4 = "唉, 我已经要走了, " + Npchar.name+ "。 再见。 ";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "啊, 好吧, 进来, 进来。 这里总是欢迎你。 ";
			link.l1 = "是的, 谢谢你。 很高兴见到你。 再见。 ";
			link.l1.go = "exit";
			Link.l2 = "我需要一些新手。 只要确保他们有能力, 好吗? ";
			Link.l2.go = "crew hire";
			link.l3 = "我想在坚实的地面上休息一下, 整理一下思绪, 而不是在我母亲在房子里忙忙碌碌的时候。 ";
			link.l3.go = "Helen_room";
			Link.l4 = "我能问你点事吗? ";
			Link.l4.go = "quests";
			link.l5 = " 我有件事要和你讨论, " + Npchar.name+ "。 ";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// 神父的任务生成器。 任务#1。 Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "你想要什么, 仁慈的先生/女士? ";
				link.l1 = "给我同桌的伙伴来瓶朗姆酒。 ";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <—— 神父的任务生成器。 任务#1.
			dialog.Text = LinkRandPhrase("我在听, 船长。 ","我能为你提供什么, 船长? ","那么船长, 要什么? ");
			Link.l1 = "我需要船员, " + NPChar.name+ "。 ";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+ ", 我们谈谈... ";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "我想谈谈财务方面的事。 ";
				link.l21.go = "LoanForAll";//(转发到贷款生成器)
			}
			// 神父的任务生成器。 任务#2。 Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("你能告诉我最近教堂抢劫案的事吗? ", "你对最近教堂的抢劫案知道些什么? ", "你听说过最近教堂的抢劫案吗? ");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <—— 神父的任务生成器。 任务#2.
			
			//Jason --> 生成器 不幸的小偷
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "人们说你几乎知道这个殖民地的一切。 我想买" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人告诉我它在你的镇上被出售。 嗯, 有人在街头市场卖它。 你能告诉我什么吗? ";
				link.l16.go = "Device_Tavern";
			}
			// <—— 生成器 不幸的小偷
			
			//Jason --> 生成器 阳光下的地方
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "告诉我一个叫" + pchar.GenQuest.Sunplace.Trader.Enemyname + "的敲诈者。 我在哪里可以找到他? ";
				link.l17.go = "Sunplace_Tavern";
			}
			// <—— 生成器 阳光下的地方
			
			//--> 荷兰赌局
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "你好, " + npchar.name+ "。 我需要找到雅各布.范.伯格 - 他在哪里? 我在你的酒馆里没看到他... ";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "你好, " + npchar.name+ "。 我在找一个叫费尔南多.罗德里格斯的绅士。 他出现在你的镇上了吗? ";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<—— 荷兰赌局
				
				//Jason --> 水上飞机比赛
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "我来领取我的奖金, 奖金由你保管。 " + npchar.name+ "。 ";
					link.l19.go = "Race_Advantage";
				}
				// <—— 水上飞机比赛
				//Jason --> 劫持乘客
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "我想知道在哪里可以找到一个叫" + pchar.GenQuest.Marginpassenger.q2Name + "的人? 他住在你的镇上。 ";
					link.l20.go = "Marginpassenger";
				}
				// <—— 劫持乘客
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("你有空闲的房间吗, 伙计? ", "你有空闲的房间吗, 我想在这里待一段时间。 ");
				link.l3.go = "room";
			}
			Link.l4 = "我想我以后再来。 ";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "你需要水手做什么, 船长? 我在港口没看到你的船。 ";
				link.l1 = RandPhraseSimple("确实... 我停错地方了。 ", "我忘了进港... ");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "通常有很多人想成为水手, 但现在太晚了 - 他们早上才会开始出现。 也许你想租个房间等他们? ";
				link.l1 = "好的。 你有空闲的房间吗? ";
				link.l1.go = "room";
				link.l2 = "我现在对房间不感兴趣。 再见。 ";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "你认为我们这里接待通缉犯吗? 庆幸我没叫卫兵。 ";
					link.l1 = "谢谢。 ";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // 布莱克伍德在城市
					{
						Dialog.text = "船长, 今天酒馆里一个人也没有。 所有愿意的人都跟布莱克伍德船长走了。 ";
						link.l1 = "真遗憾! ";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "啊, 抱歉船长, 你来得有点晚了。 所有想出海的小伙子都刚和英勇的" + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + "船长一起航行了。 ";
						link.l1 = "真遗憾! ";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //以防万一。 
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "船长, 人们说你相当吝啬。 我们这里没有人愿意加入你的船员。 ";
									link.l1 = "我明白了... ";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //以防万一。 
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //以防万一。 
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //以防万一。 
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "我洗耳恭听。 ";
			//link.l1 = "我在找工作。 你能帮我吗? ";
			//link.l1.go = "work";
			//homo 15/06/06 谣言
			link.l2 = LinkRandPhrase("你能告诉我最新的消息吗? ","这些地方发生了什么事? ",
                                    "陆地上有什么新鲜事? ");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "我来是为了别的事。 ";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "你知道我在哪里可以找到" + pchar.GenQuest.EncGirl.name +"吗? ";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "你能告诉我在哪里可以找到" + pchar.GenQuest.EncGirl.sLoverId + "吗? ";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "啊哈, 我是应你儿子的邀请来的。 "; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "那么, 你见过" + pchar.GenQuest.CaptainComission.Name + "吗? ";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "你能告诉我应该在哪里找" + pchar.GenQuest.CaptainComission.Name + "吗? ";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "你知道我在哪里可以找到" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "巡逻队的队长" + pchar.GenQuest.CaptainComission.Name + "吗? ";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "那么, 你见过" + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "吗? ";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "你知道" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "巡逻队的队长" + pchar.GenQuest.CaptainComission.Name + "的事吗? ";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "你能告诉我在哪里可以找到一个叫" + pchar.GenQuest.Hold_GenQuest.Name + "的人吗? ";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "我在附近偶然发现了一些船只文件... .";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> 总督任务 寻找逃兵
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "听着, 我在找我的一个老朋友, " + pchar.GenQuest.FindFugitive.Name + "是他的名字。 一个船长朋友告诉我他正前往你的定居点。 你碰巧见过他吗? ";
				link.l12.go = "FindFugitiveTav";
			}
			//<—— 寻找逃兵

			link.l15 = "没什么, 谢谢你, 。 ";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("你说什么? " + pchar.GenQuest.Hold_GenQuest.Name + "? 嗯... 从没听说过。 ",
						"你确定他来自我们镇吗? 我从未听说过这样的人。 ",
						"我们这个小殖民地没有这样的人。 我在这里这么久从未听说过。 ");
					link.l1 = "你确定吗? ";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "教堂";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "造船厂";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "教堂";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "放债人";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "商店";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "去" + pchar.GenQuest.Hold_GenQuest.foundStr + "看看, 他经常在那里出现。 ";
					link.l1 = "谢谢你, 我会去的。 ";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("你说什么? " + pchar.GenQuest.Hold_GenQuest.Name + "? 嗯... 从没听说过。 你确定他来自我们村子吗? 我从未听说过这样的人。 ",
						"他-他... 嗯, 现在只有上帝自己知道去哪里找他 - 在地狱还是在天堂。 他一年多前就死了, 但人们还在问起他... 这个可怜的混蛋不得安宁... "),
						RandPhraseSimple("你在活人之地找不到他 - 至少现在找不到。 他不久前死于黄热病... 愿上帝让他安息... 他曾经是多么强壮的人啊! 年轻时, 他是个伟大的冒险家! 但当死亡来找你时, 你无能为力... ",
						"哦, 你错过他了? 他很久以前就离开这些地方了。 没人知道他去了哪里 - 也许去了北美殖民地, 也许回欧洲了。 他只是收拾行李离开了。 "),
						"哦, 你在找那个" + pchar.GenQuest.Hold_GenQuest.Name + "吗? 他发财了, 在新英格兰买了房子。 你知道, 有段时间我赊给他朗姆酒 - 他还欠我钱。 人就是这么忘恩负义。 ");
					link.l1 = "我明白了。 好吧, 还是谢谢你。 ";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "嗯, 除了酒馆, 还能去哪里找他? 他是这里的常客 - 用酒来淹没他的罪恶, 他-他。 晚点再来 - 如果他出现, 我会告诉他等你。 ";	
					link.l1 = "谢谢你, 我会的。 ";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "如果我亲自认识这里的每个人, 我怎么会不确定呢。 我在这里经营酒馆不是第一年了。 " +
				"我见过他们各种状态。 有时妻子会来接丈夫, 有时他们自己离开, 有时我不得不把他们扔出去.'我确定吗? !'当然, 我确定! ";
			link.l1 = "好吧, 还是谢谢你... ";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("他是这里的常客, 但现在不在。 时不时回来 - 如果他出现, 我会告诉他在这里等你。 ","他是这里的常客。 如果你晚点回来, 一定能在这里找到他。 ","时不时回来 - 他是这里的常客。 我会让他知道你在找他。 ");
			link.l1 = "谢谢你, 我晚点再来... ";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "他已经来这里了, 所以应该在附近的某个地方... ";
			link.l1 = "谢谢。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "有谁不认识他吗? 整个定居点已经谈论他好几天了。 ";
			link.l1 = "你能告诉我更多吗? ";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "有一点, 船长被处决了, 他的一些船员也一样。 其余的人被剥夺了军衔和职位, 分散在加勒比海... 为什么? 根据法官的说法, 他在巡逻时击沉了一艘海盗船, 并把战利品藏了起来\n" +
				"问题是, 这艘船或货物的主人都没有找到... 他们一直在搜索当地的海湾和入口, 但没有结果。 ";
			link.l1 = "什么, 没有一个船员透露藏匿处的位置? ";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "一个都没有! 即使在酷刑下! 我还是不明白, 为什么总督会如此急切地相信这种诽谤。 " + pchar.GenQuest.CaptainComission.Name + "船长有良好的声誉, 他的船员训练有素。 纪律严明, 任何舰队司令都会羡慕。 ";
			link.l1 = "我该去哪里找幸存的船员? ";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "这我不知道 - 他们已经四散奔逃了... 不过... 还有一个人留下, 但我怀疑你从他那里学不到多少东西。 他严重脑震荡。 你知道, 他在" + pchar.GenQuest.CaptainComission.Name + "手下当炮手。 事故发生两天后, 他在一个海湾被发现昏迷。 起初他被送往医院, 像英雄一样治疗, 但随着阴谋的展开, 他们把他扔进了地牢并试图审问他, 但后来决定无论如何他应该先接受治疗。 ";
			link.l1 = "他现在还在这里吗? ";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "是的, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "是他的名字。 他时不时来, 把乞讨赚来的便士花在朗姆酒上。 可怜的人。 如果我看到他, 我会告诉他等你。 ";
			link.l1 = "谢谢你, 我晚点再来。 ";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "我认识他吗? 当然认识。 你需要他做什么? ";
			link.l1 = "我和他有生意... ";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = "" + GetAddress_Form(pchar) + ", 你应该对那笔'生意'谨慎些。 " + pchar.GenQuest.CaptainComission.Name + "因涉嫌海盗罪被拘留, 总督的人现在正在岛上搜捕他的同伙。 ";
			link.l1 = "你不说! 他做了什么? ";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "我不知道这是不是真的, 但他们说他藏匿了从一艘过往海盗船没收的货物, 没有上交。 而且还没有人找到那个海盗或货物。 我还是不明白, 为什么总督会如此急切地相信这种诽谤。 " + pchar.GenQuest.CaptainComission.CapName + "船长有体面的声誉, 他是个伟大的士兵, 你可以相信我的话, " + GetAddress_Form(pchar) + "。 ";
			link.l1 = "好吧, 谢谢你的警告。 再见。 ";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // 樵夫 结束
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "你需要她做什么? ";
			link.l1 = "我和她有生意... ";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "我们定居点有一半的男人似乎都和她有生意。 如果我们的女人抓住她, 会把她 naked 扔出镇门。 ";
			link.l1 = "哦, 好吧... " + GetSexPhrase("看来我排到了长队。 好吧, 如果有人再来找她, 告诉他们排在我后面。 ","我明白了") +"... ";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "他是这里的常客 - 他通常来这里找工作, 但现在不在。 时不时回来 - 如果他出现, 我会告诉他等你。 ";
			link.l1 = "谢谢你, 我晚点再来... ";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "哦, 所以你是" + GetSexPhrase("那个船长, 带来了","那个姑娘, 带来了") + "我那不肖之子和一个年轻新娘? ";
				link.l1 = "是的, 是我帮了忙。 ";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "哦, " + GetSexPhrase("他来了, 我们的恩人","她来了, 我们的女恩人") + "。 我想你是来要报酬的吧? ";
				link.l1 = "嗯, 我不需要报酬, 但只要你的感谢就好了。 ";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "我非常感谢你没有在我儿子陷入困境时抛弃他, 并帮助他摆脱了困境。 请允许我感谢你, 并请接受这笔微薄的款项和我个人的礼物。 ";
			link.l1 = "谢谢你。 帮助这对年轻夫妇是我的荣幸。 ";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感谢? 什么感谢? ! 那个笨蛋已经闲逛了半年没有工作 - 看看他, 他有足够的时间去谈恋爱! 我像他这么大的时候, 已经在经营自己的生意了! 噗! 总督有个适婚的女儿 - 而那个傻瓜带了一个没有亲友的荡妇到我家, 还敢要求我的祝福! ";
			link.l1 = "我猜你不相信一见钟情? ";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "爱情? 爱情! ? 你是在嘲笑我还是愚蠢? 你纵容年轻人的任性, 像个拉皮条的一样行事, 真可耻! 你不仅把一个女孩从家里带走, 还毁了我儿子的生活。 不会有感谢给你。 再见。 ";
			link.l1 = "那你也一样。 ";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "让我看看! 嗯... 但你自己也是船长。 我认为你应该去见港务长。 ";
				link.l1 = "谢谢你的建议。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "让我看看! 哦! 从名字判断, 这属于我的一位顾客, 相当受尊敬的绅士。 我自己可以把这些文件交给主人。 你会给我吗? ";
				link.l1	= "再想想... ";
				link.l1.go = "exit";
				link.l2 = "拿去吧。 我很高兴能帮上忙。 ";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //移除计时器 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski。 改写
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("我不在乎为谁服务, 因为金钱没有国籍。 但我不会帮助你, 因为你是打着" + NationNameGenitive(sti(pchar.nation)) + "的旗号来的。 ", "我只是个普通的酒馆老板, 但与" + NationNameAblative(sti(pchar.nation)) + "合作似乎不太吸引人。 ");
				link.l1 = RandPhraseSimple("好吧, 随你便... ", "好吧, 你喜欢就好... ");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("我们这里通常有很多乘客。 不过, 我认为不会有一个傻瓜愿意乘坐你的船。 你的坏名声 precedes you, 只有傻瓜才会和这样的恶棍一起乘船。 ", "经常有商人来找我, 需要护送。 但你的坏名声 precedes you, 我不会向任何人推荐你。 你知道, 我在乎自己的声誉。 没有人想雇狼来守护他们的羊。 ");
				link.l1 = RandPhraseSimple("哦, 真的吗, 你不应该相信所有的流言... ", "我明白了。 让所有人闭嘴很难。 ", "现在的人太软弱了... ");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "你的船在哪里? 还是你打算背着乘客游泳? ";
				link.l1 = "嘿, 你说得有道理... ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "如果你不怕去海盗定居点或敌国港口, 我可能有工作。 你在找特别的事情吗? ";
			link.l1 = "那应该没问题。 我想我可以提供护送。 ";
			link.l1.go = "work_1";
			link.l2 = "你有乘客吗? 我可以带他们去任何地方, 如果他们付钱的话。 ";
			link.l2.go = "work_2";
			link.l3 = "不, 这种工作不适合我。 谢谢。 ";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "他们通常不向我询问护送任务。 问问酒馆里的商人 - 也许他们需要你的服务。 ";
				link.l1 = "好的, 就像你说的。 ";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//当领导力低时不提供
				{
					dialog.text = "对不起, 但我没有任何人愿意和你一起旅行。 ";
					link.l1 = "我明白了。 ";
					link.l1.go = "exit";
					break;
				}
		         // 乘客
				if (hrand(6) > 1)
				{
					dialog.Text = "有一个人, 刚进来 - 他最近问过过往船只。 如果你愿意, 你可以和他谈谈。 ";
					link.l1 = RandPhraseSimple("他是谁? 也许是个恶棍? 或者, 更糟的是, 一个被通缉的海盗? ", "他是谁? 和他在一起会有麻烦吗? ");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "不, 今天没有人问过。 也许另一天。 ";
					link.l1 = RandPhraseSimple("好吧, 如果没有, 那就没有... ", "只是我的运气... 哦, 好吧, 再见。 ");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "今天没有人。 过几天再来。 ";
				link.l1 = "好的, 就像你说的。 ";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("谁能知道? 你问了 - 我回答了。 ", "嗯, 这是你要解决的。 我不会为那里的任何人担保。 ", "各种各样的人来这里。 这是个酒馆, 船长, 不是总督的庄园。 ");
			Link.l1 = "谢谢, 我们会讨价还价的。 ";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("谁能知道? 你问了 - 我回答了。 ", "嗯, 这是你要解决的。 我不会为那里的任何人担保。 ", "各种各样的人来这里。 这是个酒馆, 船长, 不是总督的庄园。 ");
			Link.l1 = "我明白了。 让我们看看这个人是谁... ";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "当然, 海伦。 你要住多久? 怎么, 和老格拉迪斯吵架了? ";
			if(!isDay())
			{
				link.l1 = "只是睡到早上。 如果我现在回家, 肯定会吵醒她。 ";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "不, 不, 我只是需要在晚上起航, 不想吵醒她。 ";
				link.l1.go = "Helen_room_night";
				link.l2 = "我想好好睡一觉, 慢慢起床。 我要租一天房间。 ";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //有人应该接近主角.
			{
				dialog.text = "房间被占用了, " + GetAddress_Form(NPChar) + ", 我帮不了你。 ";
				link.l1 = "好吧, 真遗憾... ";
				link.l1.go = "exit";
				break;
			}
			// 乌龟汤
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "亨利.蒂博先生目前在租这个房间, 他提前付了一个月的钱, 所以我帮不了你, 船长。 ";
				link.l1 = "好吧, 真遗憾... ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "房间被占用了, " + GetAddress_Form(NPChar) + ", 我帮不了你。 ";
				link.l1 = "好吧, 真遗憾... ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "房间被占用了, " + GetAddress_Form(NPChar) + ", 我帮不了你。 ";
				link.l1 = "好吧, 真遗憾... ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // 布莱克伍德在城市
			{
				Dialog.text = "唉, 不, 船长。 所有房间都被布莱克伍德和他的人占了。 ";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "啊, 真遗憾! ";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "所有房间? 这里不止一个房间吗? ";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> 任务女服务员
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "你想租房间? 没问题。 100八里亚尔, 就是你的了。 ";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "给你钱。 ";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "嗯... 我想我以后再来... ";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//任务女服务员
			{
				dialog.text = "房间是你的了。 进来放松一下。 ";
				link.l1 = "谢谢, 伙计。 ";
				link.l1.go = "exit";
				break;
			}
			//<<—— 任务女服务员
			// --> 任务"丛林中的少女"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "你想租房间? 没问题。 100八里亚尔, 就是你的了。 ";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "给你钱。 ";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "嗯... 我想我以后再来... ";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//在潘帕斯拯救阿姨的任务
				{
					dialog.text = "房间是你的了。 进来放松一下。 ";
					link.l1 = "谢谢, 伙计。 ";
					link.l1.go = "exit";
					break;
				}
			}
			// <—— 任务"丛林中的少女"

			// belamour 常住客 -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "对不起, 船长, 不幸的是没有空房间。 客人不肯离开。 而且还没付钱给我... ";
				link.l1 = "看来我们得在公共休息室过夜了... ";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "抱歉。 我们谈点别的吧。 ";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "那就叫卫兵。 这算什么客人: 不付钱, 也不想搬走... ";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<—— 常住客

			dialog.text = "你打算在这里待多久? ";
			if(!isDay())
			{
				link.l1 = "到早上。 ";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "到晚上。 ";
				link.l1.go = "room_night";
				link.l2 = "到第二天早上。 ";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
                dialog.text = "房间随你使用, 船长。 完全免费.";
                link.l1 = "谢谢你, 伙计.";
                link.l1.go = "room_day_wait";
                link.l3 = "现在不用。 我们聊点别的吧.";
                link.l3.go = "int_quests";
				break;
			}
			dialog.text = "那要花你5八里亚尔。 ";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "成交。 给你。 ";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("这个价格? 你在租皇家房间吗? 我宁愿免费待在公共休息室。 ",
            "唉, 看来睡在床上的奢侈超出了我目前的经济能力。 我想我得在公共休息室的长凳上睡了。 ");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "现在不了。 我们换个话题吧。 ";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
                dialog.text = "房间随你使用, 船长。 完全免费.";
                link.l1 = "谢谢你, 伙计.";
                link.l1.go = "room_day_wait_next";
                link.l3 = "现在不用。 我们聊点别的吧.";
                link.l3.go = "int_quests";
				break;
			}
			dialog.text = "那要花你10八里亚尔。 ";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "成交。 给你。 ";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("这个价格? 你在租皇家房间吗? 我宁愿免费待在公共休息室。 ",
            "唉, 看来睡在床上的奢侈超出了我目前的经济能力。 我想我得在公共休息室的长凳上睡了。 ");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "现在不了。 我们换个话题吧。 ";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
                dialog.text = "房间随你使用, 船长。 完全免费.";
                link.l1 = "谢谢你, 伙计.";
                link.l1.go = "room_night_wait";
                link.l3 = "现在不用。 我们聊点别的吧.";
                link.l3.go = "int_quests";
				break;
			}
			dialog.text = "那要花你5八里亚尔。 ";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "成交。 给你。 ";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("这个价格? 你在租皇家房间吗? 我宁愿免费待在公共休息室。 ",
            "唉, 看来睡在床上的奢侈超出了我目前的经济能力。 我想我得在公共休息室的长凳上睡了。 ");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "现在不了。 我们换个话题吧。 ";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour 中断夜间冒险 -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <—— 中断夜间冒险 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "滚出去, 你这个恶棍! 公共休息室可能免费, 但我们对行为举止有期望! ";
				link.l1 = "好吧, 好吧, 我走。 ";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour 中断夜间冒险 -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <—— 中断夜间冒险 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //杀手攻击
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour 中断夜间冒险 -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <—— 中断夜间冒险 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //杀手攻击
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "滚出去, 你这个恶棍! 你占了付费顾客的宝贵位置! ";
				link.l1 = "好吧, 好吧... 我走。 ";
				link.l1.go = "exit";
            }
            else
            {
				// belamour 中断夜间冒险 -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <—— 中断夜间冒险
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "立即停止在我酒馆里的这种无耻行为, 否则我叫卫兵了! ";
			link.l1 = "好吧, 好吧, 我走。 ";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* 神父任务节点。 寻找抢劫者 (任务 # 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "我对此知之甚少... 你最好问问顾客。 ";
			link.l1 = "我知道了, 谢谢。 ";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* 神父任务节点。 归还手稿 (任务 # 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "我们不提供赊账服务, 先生/小姐。 ";
			link.l1 = "我用真币支付。 你不再接受金币或银币了吗? ";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "对不起, 船长先生/小姐, 但你的朋友有债务, 我以为... ";
			link.l1 = "少想多做, 伙计。 现在, 我这位英勇的朋友欠你多少钱? ";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "如果他是个直率的人并立即付款"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", 船长先生/小姐, 他还典当了一些教堂书籍 - 这是他身上唯一有价值的东西。 ";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "这是你的硬币。 把稿件交给我。 小心点 - 这不是淫秽的木刻画集, 而是圣经! ";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "等一下... 我会带钱回来";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "如果他不是个直率的人"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", 船长先生/小姐。 ";
				link.l1 = "我会还清他的债务, 并拿走他留下的任何抵押品。 ";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// 给予手稿
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// 更改名称。 之后要改回来!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // 更改描述。 之后要改回来!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // 变量。 之后删除!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // 任务完成
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "不, 先生/小姐, 那样不行。 ";
			link.l1 = "你说'那样不行'是什么意思? 船长的债务还清了 - 他没事。 你把钱拿回来了 - 你没事。 我拿走他的抵押品 - 我没事。 大家都没事 - 为什么'那样不行'? ";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "因为, 先生/小姐船长, 我不需要钱。 因为我太了解那个船长了, 所以我实际上从未指望他会还钱并从我这里拿走这些手稿。 ";
			link.l1 = "你说你不需要钱是什么意思? 所以你从一开始就打算保留这些书? 但是, 看在上帝的份上, 为什么? ! ";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "看在上帝的份上 - 正是, 先生/小姐, 这就是原因。 我的小儿子病得很重, 我和妻子发过誓, 如果我们的主治愈孩子的发烧, 我们就向教堂捐款。 主的怜悯是无尽的, 我的儿子活了下来, 现在我们必须遵守誓言。 就在这时, " + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长出现了, 典当了这些教堂书籍。 我不能允许这样的亵渎行为 - 用圣言支付饮料 - 因此我决定把这些书交给我们教区的牧师。 ";
			link.l1 = "嗯, 这当然是一件好事, 但你也应该知道这些书实际上属于另一位神父 - 实际上, 不仅是神父, 还是一位主教, 我的精神导师。 他可能会生气, 甚至诅咒那些胆敢捐赠被盗教堂财产的人。 我想从你这里买下它们, 把它们安全地带回家。 你可以把钱捐给你的教区, 我相信上帝会同样欣赏。 ";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "先生/小姐... 先生/小姐船长... 当然, 我之前不知道! 我会把它们还给你, 而且我不会要任何钱。 你只要在主教面前为我们美言几句 - 也许他可以祝福我们, 解除我们的誓言... ";
			link.l1 = "当然, 你的誓言会被认为是遵守了! 毕竟, 你放弃了利润, 把书归还给了合法的主人。 具体的教堂不重要, 因为只有一个上帝和一个神圣的天主教使徒教会, 对吗? 好了, 把它们给我, 祝你好运... ";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// 给予手稿
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// 更改名称。 之后要改回来!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // 更改描述。 之后要改回来!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // 变量。 之后删除!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // 任务完成
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> 生成器 不幸的小偷
		case "Device_Tavern":
			dialog.text = "嗯, " + pchar.GenQuest.Device.Shipyarder.Type + "? 以前从未听说过... 实际上, 这到底是什么? 我这么久以来从未听说过这种东西。 ";
			link.l1 = "嗯, 这是一个造船工具, " + pchar.GenQuest.Device.Shipyarder.Describe + "。 有人向你提供过类似的东西吗? ";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "嗯... 是的, 确实有一个奇怪的人给我带来了那个东西。 不过他没告诉我那是什么 - 只是想用它换酒。 当然, 我拒绝了 - 我不需要那个小玩意儿。 ";
				link.l1 = "他长什么样, 去了哪里? 我非常需要那个工具。 ";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "不, 没有那样的东西。 抱歉, 我帮不了你。 问问周围的人。 ";
				link.l1 = "我知道了。 好吧 - 是时候问问周围的人了! ";
				link.l1.go = "exit";
			}
		break;
		// <—— 生成器 不幸的小偷
		
		//Jason --> 生成器 阳光下的地方
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//在商店
			{
				dialog.text = "" + pchar.GenQuest.Sunplace.Trader.Enemyname + "? 他最近在那里, 现在应该已经去找他的同伴 - 店主了。 试着在商店找他 - 他肯定在那里。 ";
				link.l1 = "谢谢! 你帮了我大忙! ";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//去钓鱼了
			{
				dialog.text = "" + pchar.GenQuest.Sunplace.Trader.Enemyname + "? 今天一大早, 他就乘他的小帆船出海了。 我打赌他现在正站在船舷旁欣赏风景。 如果你需要他, 可以试着在海上找他, 或者等他几天后回来... ";
				link.l1 = "谢谢! 我想我不会等 - 在海上找他会更容易。 祝你好运! ";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://商店
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://钓鱼
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <—— 生成器 阳光下的地方	
		
		// Jason --> 荷兰赌局
		case "HWICHollJacob_Tavern":
			dialog.text = "嘘... 你为什么大喊大叫? 他等你很久了。 他已经喝了整整一夸脱朗姆酒。 上楼到房间去, 你会在那里找到他。 ";
			link.l1 = "哦, 我知道了。 希望他还醒着。 ";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "是的, 我认识那位先生。 他应该在镇上的某个地方 - 我最近刚看到他从我窗前走过。 ";
				link.l1 = "谢谢你! 我会去找他! ";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//在街上
				{
					dialog.text = "是的, 我认识那位先生。 他应该在镇上的某个地方 - 我最近刚看到他从我窗前走过。 ";
					link.l1 = "谢谢你! 我会去找他! ";
					link.l1.go = "Fernando_Land";
				}
				else //在海上
				{
					dialog.text = "是的, 他现在在访问我们的城镇。 现在他不在这里 - 他乘他的双桅帆船出海了。 他可能在离这里不远的我们岛屿的水域里。 ";
					link.l1 = "谢谢伙计! 你帮了我大忙! ";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "费尔南多.罗德里格斯? 从未听说过。 不, 我对这个人一无所知。 ";
				link.l1 = "我知道了... 好吧, 搜索继续... .";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<—— 荷兰赌局
		
		//Jason --> 水上飞机比赛
		case "Race_Advantage":
			dialog.text = "是的, 当然。 恭喜船长。 我已经知道你的胜利了。 这是你的钱。 ";
			link.l1 = "谢谢你, " + npchar.name+ "。 ";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<—— 水上飞机比赛
		
		//Jason --> 劫持乘客
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "呃, 先生, " + pchar.GenQuest.Marginpassenger.q2Name + "大约" + LinkRandPhrase("一个月","三周","两个月") + "前去世了。 " + LinkRandPhrase("突然发烧去世","他在城门口被刺伤 - 强盗或那些红皮肤的野蛮人","他在决斗中被枪杀") + "。 愿上帝让他的灵魂安息... ";
				link.l1 = "该死的! .. 那我该怎么处理他的... 好吧, 不管了。 谢谢你的信息。 再见, " + npchar.name+ "。 ";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = "" + pchar.GenQuest.Marginpassenger.q2Name + "? 是的, 他应该在镇上的某个地方。 在街上找他。 但要记住, 每天中午前他在总督办公室, 晚上九点后他把自己锁在家里。 ";
				link.l1 = "谢谢! 我会去找他... ";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: 好人不长命 -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "到太子港, 去找黑牧师");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "到勒弗朗索瓦, 去找善良的雅克");
			}
			// <—— belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<—— 劫持乘客
		
		//Jason --> 寻找逃兵
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("看来你的船长说的是实话。 " + pchar.GenQuest.FindFugitive.Name + "确实最近到达了我们的定居点。 白天在街上找他 - 他通常在那里消磨时间。 ", "你已经问过我那个人了, 我告诉了你我所知道的一切! ", "你是在开玩笑还是真的是个白痴? ! 你已经第三次问同样的问题了! ", "想想看, 这样的白痴怎么能成为船长... ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("谢谢你, 朋友, 你帮了我大忙! ", "是的, 是的, 很好。 ", "哇, 哇, 别这么激动。 我只是忘了。 ", "嗯, 如你所见... ", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("不, 伙计, 我从未听说过那个名字。 问问周围的人 - 也许有人认识他... ", "你已经问过我那个人了, 我告诉你: 我不认识! ", "你是在开玩笑还是真的是个白痴? ! 你已经第三次问同样的问题了! ", "想想看, 这样的白痴怎么能成为船长... ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("我知道了。 好吧, 还是谢谢你。 ", "是的, 是的, 很好。 ", "哇, 哇, 别这么激动。 我只是忘了。 ", "嗯, 如你所见... ", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<—— 寻找逃兵
		
		//--> 加斯科涅的枷锁
		case "Sharlie_crew":
			dialog.text = "不幸的是, 我现在帮不了你 - 我认识的人中没有人愿意为你服务。 但我可以给你一个建议 - 和刚刚坐在你身后桌子旁的那个水手谈谈。 他和他的伙伴们刚离开一艘商船。 也许他们会同意和你一起走。 ";
			link.l1 = "好的, 我会的! 非常感谢你! ";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//雇佣水手阿隆索
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "我不能告诉你具体的情况, 朋友。 目前没有领航员经常光顾我的地方。 试着在港口问问 - 也许人们知道更多。 ";
			link.l1 = "我知道了。 好吧, 我会去和人们谈谈。 ";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//生成领航员
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<—— 加斯科涅的枷锁
		
		// Addon 2016-1 Jason 海盗线
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "马上, 先生! .. 最好的法国葡萄酒! " + sld.name + "! 去把最好的客房准备好! 那将是1000比索, 先生。 ";
			link.l1 = "给你。 ";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour 常住客 -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "滚出去, 恶棍! 你占了付费顾客的宝贵位置! ";
				link.l1 = "好吧, 好吧... 我走。 ";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "是啊 - 然后让所有顾客都知道我的卫兵把人拖出酒馆? 而且我的一些顾客不喜欢身边有士兵。 这会让他们紧张, 明白吗? 我不想毁了我的声誉... ";
				link.l1 = "嗯, 如果我解决你的问题呢? ";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "下定决心了? 他有武器, 他是某种职业雇佣兵... ";
				link.l1 = "嗯, 你说得对, 我不想和武装雇佣兵争论... ";
				link.l1.go = "Exit";
				link.l2 = "好吧, 我也不是修道院的修女... 我仍然想租个房间。 ";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "好吧, 如果你能, 呃... 说服他搬出去, 那么房间就是你的, 直到早上。 当然是免费的。 ";
				link.l1 = "你知道, 我改变主意了。 我不想说服任何人。 ";
				link.l1.go = "Exit";
				link.l2 = "你会想看看这个的。 你不想要的客人即将像一只巨大的海鸥一样飞出你的酒馆。 ";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //关闭地点
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //禁止战斗
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <—— belamour 常住客
		
		case "Helen_room_night":
			dialog.text = "我知道了。 那要5银币。 ";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "当然, 给你。 ";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "实际上, 你知道吗... 也许另一个时间。 我将整天站着度过。 ";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "明智的决定。 那要5银币, 晚安。 ";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "给你, 谢谢你 - 晚安。 ";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "再想想, 我不想睡觉。 我会在镇上逛逛, 呼吸点夜晚的空气。 ";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "当然, 海伦。 那要10比索。 ";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "当然, 给你。 ";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "实际上... 我可以用一整天做些有用的事。 也许另一个时间。 ";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "如你所愿, 海伦。 ";
			link.l1 = "嗯。 ";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "散步后你可能会觉得困。 ";
			link.l1 = "哈哈, 也许吧。 ";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "如你所愿。 ";
			link.l1 = "好吧, 下次见。 ";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "当然, 海伦, 我洗耳恭听。 ";
			link.l1 = "镇上有什么最新消息或有趣的谣言? ";
			link.l1.go = "rumours_tavern";
		break;
		
		// 贝丝女士 -->
		case "LadyBeth_Room":
			dialog.text = "他支付了通常价格的三倍, 所以... 你明白的。 我不建议拒绝他 - 他的脾气很坏。 尤其是最近。 ";
			link.l1 = "他怎么了? ";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "痴迷, 就是这样。 起初, 他是个慷慨善良的人。 他的水手会在酒馆里挥霍金钱, 给女孩买礼物。 当'贝丝女士'进港时, 会举行真正的庆祝活动。 现在呢? 现在他们只买补给品, 不加选择地招募人员。 好像他们需要的不是水手, 而是仅仅是劳动力。 好吧, 你可以自己和他谈谈。 ";
			link.l1 = "也许我会。 谢谢。 ";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// 贝丝女士 <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //不在自己的岛屿
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //不在自己的岛屿
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}