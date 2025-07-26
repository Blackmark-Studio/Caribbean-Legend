#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("镇上已经拉响了警报。 每个人都在找你! 如果我是你, 我不会在这里久留。 ", "整个卫兵都在搜捕你。 我不是傻瓜, 我不会和你说话! ", "快跑, 伙计, 在士兵把你剁成肉酱之前... "),
					LinkRandPhrase("你需要什么, 恶棍? ! 城镇卫兵已经在追踪你了。 你跑不远的, 海盗! ", "肮脏的杀手, 滚出我的房子! 卫兵! ! ", "我不怕你, 狗东西! 绞索在召唤你, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("呵, 我不担心警报... ", "他们没有机会抓住我。 "),
					RandPhraseSimple("闭上你的嘴, " + GetWorkTypeOfMan(npchar, "") + ", 否则我会割掉你那该死的舌头。 ", "呵, " + GetWorkTypeOfMan(npchar, "") + ", 你也想追捕海盗吗? 听着, 伙计, 保持冷静, 你也许能活下来... "));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + "! 欢迎, " + GetAddress_Form(NPChar) + "来到洛斯-特克斯矿场酒馆。 食物。 饮料和姑娘, 全都价格实惠! 我的名字是" + GetFullName(npchar) + ", 我随时为您服务。 ";
				Link.l1 = "让我看看... 我是" + GetFullName(pchar) + "。 很高兴见到你, " + npchar.name + "。 ";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊哈, 这是我的老熟人, " + GetFullName(pchar) + "船长! 很高兴见到你, 老朋友! 朗姆酒, 姑娘们? ";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "给我倒些朗姆酒, " + npchar.name + "。 ";
					link.l1.go = "drink";
				}
				link.l2 = "我想睡一会儿。 你有空闲的房间吗? ";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("你有什么最新消息吗? ", "这附近有什么新鲜事吗? ", "在陆地上生活得怎么样? ");
				link.l3.go = "rumours_tavern";
				link.l4 = "不, 我不需要任何东西, " + npchar.name + "。 我只是顺道来和你打个招呼。 ";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "哦, 我太高兴了! 新面孔在我们城里很罕见。 我给你倒些朗姆酒, 我们聊聊天怎么样... ";
			link.l1 = "这是我第一次来这里, 我想多了解一下这个定居点。 ";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "给我倒些朗姆酒, " + npchar.name + "。 ";
				link.l2.go = "drink";
			}
			link.l3 = "我想睡一会儿。 你有空闲的房间吗? ";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "没有什么有趣的事可讲。 每天都是同样的事情: 无聊。 阳光和灰尘。 只有士兵。 黑人和印第安人住在这里。 你可能还会遇到一些冒险家和渴望黄金的强盗\n有时像你这样的绅士。 船长会来拜访我们, 用奴隶换取锭块并购买贵金属。 我们的商人是个很有趣的人, 他不仅出售金块和银块, 还出售半宝石\n他声称有特殊知识的人可能会发现这些小石子非常有用。 所以去看看我们的商店吧。 矿场本身位于山的更深处。 如果你愿意, 你可以去那里, 但我建议避免让卫兵不高兴\n不要和囚犯说话, 上帝保佑你不要偷窃。 不管怎样, 这个定居点最好的地方是我的酒馆, 这是在这个燃烧的地狱中休息的最好地方! ";
			link.l1 = "谢谢你的信息! ";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "船长, 我认为你最好停下来。 上帝保佑你在酒精的影响下不要惹事。 我们这里对此非常严格。 即使你的权威也帮不了你。 ";
				link.l1 = "嗯... 我想你是对的—— 我已经喝够了。 谢谢你的关心! ";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "不客气, 船长。 一品脱我最好的牙买加黑朗姆酒只要八块五! ";
				link.l1 = RandPhraseSimple(LinkRandPhrase("好的, 为你的健康和你机构的繁荣干杯, 伙计! ", "好的, 为海上的人们干杯! ", "好的, 为你城镇的福祉干杯! "), LinkRandPhrase("好的, 为生产的风, 为一阵运气, 让我们都生活得更轻松和富有! ", "好的, 为所有事情中总是顺风顺水! ", "好的, 为幸福。 幸运。 快乐和姑娘们干杯! "));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // 杰森
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.MinentownSex"))
			{
				dialog.text = "先生, 你已经为一个房间和一个女孩付了钱。 上楼去吧, 她已经等你一会儿了。 ";
				link.l1 = "好的。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "我们有。 你打算住多久? ";
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
		break;

		case "room_day":
			dialog.text = "那将是八块十。 你想要一个房间的女孩吗? 只要一千比索的荡妇。 ";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "不, 我不需要女孩。 给你, 这是房间的钱。 ";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "是的, 我要房间和女孩。 这是钱。 ";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "唉, 我住不起这个房间。 ";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "那将是八块十。 你想要一个房间的女孩吗? 只要一千比索的荡妇。 ";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "不, 我不需要女孩。 给你, 这是房间的钱。 ";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "好的。 我们要房间和女孩。 这是钱。 ";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "唉, 我住不起这个房间。 ";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "那将是八块十。 你想要一个房间的女孩吗? 只要一千比索的荡妇。 ";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "不, 我不需要女孩。 给你, 这是房间的钱。 ";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "好的。 我们要房间和女孩。 这是钱。 ";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "唉, 我住不起这个房间。 ";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "上楼去吧, 先生。 女孩会等你的。 祝你入住愉快! ";
			link.l1 = "谢谢, 伙计... ";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.MinentownSex = "true";
			LocatorReloadEnterDisable("Minentown_tavern", "reload1_back", true); //关闭酒馆
			LocatorReloadEnterDisable("Minentown_tavern", "reload2_back", false); //打开房间
			bDisableFastReload = true;//关闭过渡
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\Minentown_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Minentown_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "你好, 白人主人。 不要那样看着" + npchar.name + ", " + npchar.name + "知道如何做任何事情, 甚至比妓院的白人娘们做得更好。 啊, 先生, 你真帅... 答应我, 这个娘们会爱你很久。 ";
			link.l1 = "听起来不错, 给我展示你最好的印第安魅力。 我不需要雨舞就能让你湿... ";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== 光天化日之下的抢劫, 试图进入箱子 =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("光天化日之下的抢劫! ! ! 这里发生了什么? ! 等等, 等等, 伙计... ", "嘿, 你在那里做什么? ! 想抢劫我吗? 现在你完蛋了... ", "等等, 你到底在做什么? 原来你是个小偷! 认为这是穷途末路, 混蛋... ");
			link.l1 = LinkRandPhrase("魔鬼! ", "他妈的! ", "啊, 该死");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // 用腿逃跑的路被封锁
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // 对不朽的市长不起作用 :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // 幽灵士兵
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}