// 堡垒指挥官对话
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 调用城市对话 -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // 调用城市对话 <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("听着, 我有重要的事和你谈。 希望你能帮忙。 ","船长, 我有个很划算的提议, 你感兴趣吗? "), RandPhraseSimple("我认为你可以在一件重要的事情上帮助我们。 ","船长, 我有个微妙的提议, 对我们双方都很有利。 "));					
				link.l1 = "好吧, 说来听听, 我们看看... ";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("我是堡垒的指挥官。 你在这里需要什么? ", "你需要什么? 为什么来这里? ");
			link.l1 = "哦, 没什么, 只是看看城镇和附近地区。 我只是碰巧来到这里。 ";
			//belamour传奇版对话, 如果英雄有军衔和国家功勋 -->
			// 有许可证的军官
			if(IsOfficerFullEquip())
			{
				dialog.text = "欢迎来到堡垒, 船长。 你需要什么吗? ";
				link.l1 = "不, 没什么, 只是随便过来看看。 ";
			}
			// 舰队副司令
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "舰队副司令 您好! 您有什么命令吗? ";
				link.l1 = "不, 军官, 没有命令。 我只是来看看堡垒。 ";
			}
			// 总督将军
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "总督将军, 大人! 堡垒内一切井然有序。 有什么命令吗? ";
				link.l1 = "很高兴你一切安好, 军官。 没有命令, 我只是顺便来检查一下堡垒。 ";
			}
			// < —legendary edition
			link.l1.go = "exit";
			//Jason --> 迷你任务 短缺商品
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "我有个有趣的消息告诉你, 军官。 你的一个士兵, " + pchar.questTemp.Wine.SName + " 让我通过我的中介在镇上购买葡萄酒。 考虑到你的命令... ";
				link.l11.go = "Wine_prison";
			}
			// < —迷你任务 短缺商品
			// 加勒比习俗
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "你好, 军官。 我从巴斯特尔殖民地来, 奉一个叫热拉尔.勒克鲁瓦的人的命令。 我的船舱里有给你的火药和炸弹货物... ";
				link.l11.go = "trial";
			}
			// 危险货物 -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "你看起来很担心, 军官。 我能帮你什么吗? ";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "我准备报告说全部火药已送达。 我的船已准备好卸货。 ";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "我想拒绝我们的火药交易。 这太麻烦了。 ";
					link.l4.go = "zpq_fld2";
				}
			}
			// < —危险货物
			NextDiag.TempNode = "First time";
		break;

		// --> 堡垒用加农炮
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("你看, 堡垒的大炮已经很破旧了。 财政部拨款更换, 但我根本不知道去哪里购买新的: 我们殖民地根本无法找到所需数量的大炮。 所以, 我想你缴获的船上的加农炮可能对我们很有用。 ","我需要更换堡垒的炮台。 资金已经到位, 但是... 在我们殖民地根本无法买到所需数量。 ","我被指派更换破旧的堡垒大炮, 但我似乎到处都找不到足够的数量。 ");
			Link.l1 = "嗯... 你能详细说明一下吗? 口径。 数量。 价格? ";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "我需要" + pchar.questTemp.PrisonGun.Text + ",  exactly " + sti(pchar.questTemp.PrisonGun.Qty) + " 门。 我会用金币支付, 每门 " + sti(pchar.questTemp.PrisonGun.Price) + " 枚。 总共 " + FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum)) + "。 你觉得如何? 哦, 还有一件事 - 我会接受整批货物, 但最早一个月后 - 钱还没到。 ";
			Link.l1 = RandPhraseSimple("不, 军官, 你的提议一点也不感兴趣... 对不起。 ","很诱人, 但我想我还是算了。 请允许我保留意见。 ");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("嗯, 这个提议确实很有趣。 成交。 ","我想我接受。 这并不难, 而且显然有利可图。 ");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "真遗憾, 船长, 我本来指望你。 还有... 我希望这次谈话只在堡垒内进行? ";
			Link.l1 = "你不必提醒我。 此致问候。 ";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "那么成交! 我不限制你具体条件, 但请尽量不要超过半年。 我希望你明白这是严格保密的? ";
			Link.l1 = "我当然明白。 再见, 指挥官。 ";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "我告诉过你至少一个月后再来! ";
				Link.l1 = "该死! 我太忙" + GetSexPhrase("","") + "了, 把时间都忘了... 对不起, 我会按约定稍后再来。 ";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "嗯... 你知道, 自从我们达成'交易'以来已经过去半年多了。 我已经购买了大炮。 你真的以为我会一直等你吗? ";
				Link.l1 = "该死! 那我现在该怎么处理它们? ";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // 城市
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "是的, 你准备好帮我了吗? ";
				if (amount < 0)
				{
					Link.l1 = "不, 还在进行中。 只是想确认我们的交易仍然有效。 ";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "是的。 整批货物都在船舱里 - " + sTemp + " 门, 如约定。 ";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "我在港口没看到你的船。 你是说要把那些大炮拖过丛林吗? 赶紧到我们的港口来, 然后再来。 ";
				link.l1 = "我的船在岛的另一边。 我会把它开到港口。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("你知道, 这真的很尴尬, 但我不得不取消我们的交易。 我们刚刚进行了财务检查, 你知道他们在这种事情上有多严格。 我什么也做不了。 对不起。 ","船长, 你知道... 嗯, 大炮已经从大都市运给我们了, 我当然不得不买下它们。 价格高得离谱, 但是... 我真的很抱歉让你失望了... 我也感觉不好... ");
				Link.l1 = "该死! 那我现在该怎么处理它们? ";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("太好了。 我会从驻军派一个小队去卸载。 ","太好了。 我的士兵会帮你卸大炮。 ");
				Link.l1 = "你准备好付款了吗? ";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "我不知道。 在造船厂卖掉它们, 装备一艘贸易船, 沉掉它们... 我真的不知道。 请不要告诉任何人这笔交易。 ";
			Link.l1 = "哦, 你这么说! 我简直无话可说! ";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "我不知道。 这是你的问题。 卖掉它们, 扔掉它们, 沉掉它们 - 我真的不在乎。 ";
			Link.l1 = "哦, 这简直是浪费时间... ";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "当然。 这是你的金子 - 自己看看。 ";
			Link.l1 = "谢谢! 和你做生意很愉快! ";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("你收到了" + FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money)) + "");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "我也一样。 你帮了大忙。 还有, 我请求你, 把这笔交易留在这个房间里。 ";
			Link.l1 = "当然。 祝你好运。 ";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// < —堡垒用加农炮

		//Jason --> 迷你任务 短缺商品
		case "Wine_prison":
			dialog.text = "什么? ! 我严格禁止在堡垒内饮酒! 好吧, 他必须为此付出代价。 我会从他的薪水中扣除1000比索, 作为你警惕性的奖励交给你。 而这个人将被拘留三天。 ";
			link.l1 = "谢谢你, " + GetAddress_FormToNPC(NPChar) + "。 阻止这种违规行为是我们的共同责任。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//取消中断
			pchar.quest.WineTraderQM.over = "yes";//取消中断
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// < —迷你任务 短缺商品
		
		// 加勒比习俗
		case "trial":
			iTest = FindColony(NPChar.City); // 城市
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "嗯。 但这批货物不完整! 怎么回事? ";
					link.l1 = "该死! 请原谅我, 这是我的错。 我会立即购买缺少的数量, 并按约定把整批货物交给你。 ";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "所以你是我们的 courier? 好的。 我们来整理一下货物, 然后你会收到进一步的指示。 ";
					link.l1 = "好的。 ";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "我在港口没看到你的船。 你是说要把货物拖过丛林吗? 赶紧到我们的港口来, 然后再来。 ";
				link.l1 = "我的船在岛的另一边。 我会把它开到港口。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour传奇版 如果有 - 取消计时器
			dialog.text = "好的, 炸弹和火药, 各2500单位... 很好。 士兵们会卸下货物, 你的人可以休息一下。 这是你运输的报酬 - 五千比索。 ";
			link.l1 = "谢谢! 我接下来该做什么? 勒克鲁瓦先生说... ";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "是的, 是的, 你现在会收到指示。 你准备好注意听了吗? ";
			link.l1 = "当然, 军官。 ";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "那么, 我们的军舰'好战号'正在西班牙殖民地贝洛港附近巡航, 在西班牙大陆的南部。 这艘船由弗洛里安.肖克指挥, 他正在准备伏击 一 艘两周后将离开贝洛港的西班牙大型帆船。 \n问题是我们的护卫舰的大炮有铸造缺陷, 我们需要更换十五门大炮来挽救任务; 否则, 帆船在加农炮和人员数量上都会超过'好战号'。 \n如果不更换, 弗洛里安.肖克将不得不无功而返。 这种情况是极不可取的。 你的任务是在十四天内运送十五门大炮来挽救任务。 ";
			link.l1 = "所以, 我需要装载十五门大炮, 前往贝洛港, 寻找护卫舰'好战号', 并把大炮交给弗洛里安.肖克船长? ";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "正是。 你说对了。 你准备好接受这个任务了吗? ";
			link.l1 = "报酬呢? ";
			link.l1.go = "trial_5";
			link.l2 = "对不起, 军官, 但我只是不想卷入其中。 请原谅我。 ";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "你有权选择, 但我本来指望你的同意。 现在我得另找一个 courier, 尽管我时间不多了... 好吧, 我不再耽误你了, 船长。 ";
			link.l1 = "此致问候。 ";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "别担心那个。 弗洛里安.肖克会从船上的金库中付给你二百金币。 此外, 我相信他会想让你和你的船为他所用 - 当然是在你同意的情况下。 ";
			link.l1 = "好吧, 我接受这个任务! 大炮在哪里? ";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "我会命令士兵立即把它们装到你的船上。 尽快起航, 先生! 祝你好运! ";
			link.l1 = "谢谢。 运气当然不会有害, 顺风也一样... ";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour传奇版
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("探索模式: 计时器已禁用。 ");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//启动拦截者
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - 任务 "会见迭戈"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// 危险货物 -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "嗯, 也许。 好吧, 由于你良好的声誉, 我愿意冒险信任你。 否则, 我甚至不会和你谈论这件事。 问题是, 我们需要一批相当大的特殊货物, 所以你需要一艘大型货船和冒险的意愿。 此外, 你必须向我保证不告诉任何人。 \n如果你觉得尴尬, 现在就告诉我。 我想我已经说明白了... ";
				link.l1 = "听起来很有趣。 如果报酬合适, 我就加入, 不过我还不知道你说的是什么货物。 无论如何, 我向你保证。 ";
				link.l1.go = "zpq_prs2";
				link.l2 = "我想我会拒绝... 如果我向你保证, 我就必须做看起来很麻烦的工作。 我不会这么做。 ";
				link.l2.go = "zpq_fld";
				Notification_Reputation(true, 71, "low");
			}
			else
			{
				dialog.text = "你的声誉我无法接受。 请你离开房间。 我们能够自己解决问题。 ";
				link.l1 = "随便, 那你们自己解决吧... ";
				link.l1.go = "exit";
				Notification_Reputation(false, 71, "low");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "好吧, 至少你诚实地拒绝了... 我不再留你了。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "嗯, 实际上我没料到你会这样。 我不得不请你离开... 记住你承诺不泄露任何信息。 ";
			link.l1 = "对不起... ";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "太好了。 问题是最近的风暴损坏了我们堡垒军火库的火药供应。 我希望不需要解释我们这里的微妙麻烦。 如果长期围困, 堡垒将无能为力。 我们撑不了多久。 ";
			link.l1 = "现在我明白了。 你需要什么货物 - 多少? ";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "我们需要15000桶火药。 我会付你10万比索... 你必须明白这是个很好的价格。 尽管说服总督的财务官很麻烦, 但我们目前的状况迫使我出这样的代价... 风暴季节不允许我们使用自己的补给线, 我们也不想让所有人都知道这个麻烦... ";
			link.l1 = "我明白... 价格确实不错。 你提到了风险... ";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "我是指运输如此大量的火药可能非常危险。 我亲眼见过几次爆炸, 有时一个火花就够了。 但如果你遇到风暴... 整个护航队通常会与潜在的火源保持距离。 如果爆炸, 所有人都死了! ";
			link.l1 = "我明白... 但我总是信守承诺, 考虑到这一点, 成交。 ";
			link.l1.go = "zpq_prs5";
			link.l2 = "嗯, 先生... 你告诉我这么可怕的事情, 我已经失去了做这份工作的任何愿望。 ";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "好的, 我很高兴我们达成了协议。 你一带来货物, 我就付你钱。 \n我一周后才能有钱, 不早于, 所以你可以慢慢来, 但请尽量不要拖延太久。 ";
			link.l1 = "我明白, 先生。 我这就去办。 ";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "终于到了! 我还以为你已经忘了我们的交易。 我会立即命令士兵开始卸你的船。 处理火药是非常微妙的事情, 哈哈! ";
			link.l1 = "太好了, 先生, 但我必须提醒你付款。 ";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "是的, 当然。 你将得到我们约定的5万比索。 ";
			link.l1 = "你可能在开玩笑吧, 先生? ! 我们约定的是10万比索! ";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(值得信赖) 我开始认为你要欺骗我, 所以没有我的12.5万比索, 我不会离开这里! ";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "嗯.. 我明白情况已经改变。 好吧, 我最好拿钱离开... ";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 35)
			{
				Notification_Skill(true, 36, SKILL_LEADERSHIP);
				dialog.text = "啊, 是的... 正是! 10万比索。 我忘了, 请原谅。 都怪我年纪大了, 你知道... sclerosis... 当然, 这是你的硬币。 和你做生意很愉快, 船长。 现在对不起, 我有很多工作要做... ";
				link.l1 = "我也一样, 先生。 再见。 ";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				Notification_Skill(false, 36, SKILL_LEADERSHIP);
				dialog.text = "什么? ! 拿着你的钱滚蛋, 否则你会在这个炮台里腐烂! ";
				link.l1 = "你这个骗子, 先生! 我建议你好好把钱给我, 否则我就把货物拿走! ";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "原谅我... 好吧, 我接受你提供的金额, 我们两清。 ";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "如此无礼! 我没疯, 我清楚地记得报价是10万比索。 \n 该死! 我不会玩你的游戏! ";
				link.l1 = "冷静点。 想想你堡垒前面那个装满火药的 ready brander。 如果我一句话, 你的堡垒就会变成废墟。 ";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "嗯-嗯... 有力的论据。 12.5万比索, 你说? 拿着, 现在原谅我, 我有工作要做... ";
			link.l1 = "再见, 先生。 ";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "什么? ! 我是一名军官! 你以为你能吓唬我吗, 小子? ! 卫兵, 抓住 "+ GetSexPhrase("他","她") +"! ";
				link.l1 = "试试吧, 炮台的老鼠们... ";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "太好了! 你做出了正确的选择。 拿着你的硬币, 再见。 很愉快! ";
			link.l1 = "再见... ";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "啊你这个混蛋! 卫兵, 抓住 "+ GetSexPhrase("他","她") +"! ";
			link.l1 = "啊! 看来我得从你喘不过气的身体里拿钱了... ";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("这里发生了可怕的事情! 据说某个囚犯从炮台逃了出来! 他屠杀了所有卫兵, 偷了国库, 然后就走了! 哇! ", SPAIN, 5, 1);
		break;
		// < —危险货物
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24磅加农炮";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "长炮";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32磅加农炮";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36磅加农炮";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "全尺寸长炮";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42磅加农炮";
		break; 
	}
}